/*
 * Copyright (C) 2012-2019  Free Software Foundation, Inc.
 *
 * This file is part of GNU lightning.
 *
 * GNU lightning is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU lightning is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * Authors:
 *      Paulo Cesar Pereira de Andrade
 */

#include "mips-cpu.c"
#include "mips-fpu.c"

static const jit_gpr_t abi_gpr_args[] = {
  _A0, _A1, _A2, _A3,
#if NEW_ABI
  _A4, _A5, _A6, _A7,
#endif
};

static const jit_fpr_t abi_fpr_args[] = {
#if NEW_ABI
  _F12, _F13, _F14, _F15, _F16, _F17, _F18, _F19
#else
  _F12, _F14
#endif
};

static const int abi_gpr_arg_count =
    sizeof(abi_gpr_args) / sizeof(abi_gpr_args[0]);
static const int abi_fpr_arg_count =
    sizeof(abi_fpr_args) / sizeof(abi_fpr_args[0]);

struct abi_arg_iterator {
  const jit_operand_t *args;
  int argc;

  int arg_idx;
#if !NEW_ABI
  int gpr_used;
  int gpr_idx;
  int fpr_idx;
#endif
  jit_word_t stack_size;
  int stack_padding;
};

static size_t page_size;

/*
 * Implementation
 */

static jit_bool_t
has_fpu()
{
#if __mips_hard_float
  return 1;
#else
  return 0;
#endif
}

jit_bool_t
jit_get_cpu(void)
{
  page_size = sysconf(_SC_PAGE_SIZE);
  /*
   * TODO: extensions? 
   */
  return has_fpu();
}

jit_bool_t
jit_init(jit_state_t * _jit)
{
  (void) _jit;
  return has_fpu();
}

static size_t
jit_initial_frame_size(void)
{
  return 0;
}

static void
reset_abi_arg_iterator(struct abi_arg_iterator *iter, size_t argc,
		       const jit_operand_t * args)
{
  memset(iter, 0, sizeof(*iter));
  iter->argc = argc;
  iter->args = args;
#if !NEW_ABI
  iter->stack_size = 16;
#endif
}

#if !NEW_ABI
static int
jit_operand_abi_sizeof(enum jit_operand_abi abi)
{
  switch (abi) {
  case JIT_OPERAND_ABI_UINT8:
  case JIT_OPERAND_ABI_INT8:
    return 1;
  case JIT_OPERAND_ABI_UINT16:
  case JIT_OPERAND_ABI_INT16:
    return 2;
  case JIT_OPERAND_ABI_UINT32:
  case JIT_OPERAND_ABI_INT32:
    return 4;
  case JIT_OPERAND_ABI_UINT64:
  case JIT_OPERAND_ABI_INT64:
    return 8;
  case JIT_OPERAND_ABI_POINTER:
    return CHOOSE_32_64(4, 8);
  case JIT_OPERAND_ABI_FLOAT:
    return 4;
  case JIT_OPERAND_ABI_DOUBLE:
    return 8;
  default:
    abort();
  }
}
#endif

static void
next_abi_arg(struct abi_arg_iterator *iter, jit_operand_t * arg)
{
  ASSERT(iter->arg_idx < iter->argc);
  enum jit_operand_abi abi = iter->args[iter->arg_idx].abi;
#if NEW_ABI
  int idx = iter->arg_idx++;
  /*
   * on new abi the first eight arguments of any type are passed in
   * registers 
   */
  if (is_gpr_arg(abi) && idx < 8) {
    *arg = jit_operand_gpr(abi, abi_gpr_args[idx]);
    return;
  }

  if (is_fpr_arg(abi) && idx < 8) {
    *arg = jit_operand_fpr(abi, abi_fpr_args[idx]);
    return;
  }

  *arg = jit_operand_mem(abi, JIT_SP, iter->stack_size);
  iter->stack_size += 8;
#else
  /*
   * O32 argument passing is a bit of a mess 
   */
  iter->arg_idx++;
  if (is_gpr_arg(abi) && iter->gpr_idx < abi_gpr_arg_count) {
    *arg = jit_operand_gpr(abi, abi_gpr_args[iter->gpr_idx]);
    iter->gpr_used = 1;
    iter->gpr_idx++;
    return;
  }

  if (is_fpr_arg(abi) && iter->gpr_idx <= 2) {
    if (iter->gpr_idx % 2 != 0)
      iter->gpr_idx++;

    if (!iter->gpr_used)
      *arg = jit_operand_fpr(abi, abi_fpr_args[iter->fpr_idx]);
    else if (abi == JIT_OPERAND_ABI_FLOAT) {
      *arg = jit_operand_gpr(abi, abi_gpr_args[iter->gpr_idx]);
    } else {
      *arg = jit_operand_gpr_pair(abi,
				  abi_gpr_args[iter->gpr_idx +
					       0],
				  abi_gpr_args[iter->gpr_idx + 1]);
    }

    iter->fpr_idx++;
    iter->gpr_idx += 2;
    return;
  }

  size_t abi_size = jit_operand_abi_sizeof(abi);
  iter->stack_size = jit_align_up(iter->stack_size, abi_size);
  *arg = jit_operand_mem(abi, JIT_SP, iter->stack_size);
  iter->stack_size += abi_size;
#endif

}

static void
jit_flush(void *fptr, void *tptr)
{
  jit_word_t f = (jit_word_t) fptr & -page_size;
  jit_word_t t = (((jit_word_t) tptr) + page_size - 1) & -page_size;
  __clear_cache((void *) f, (void *) t);
}

static inline size_t
jit_stack_alignment(void)
{
#if NEW_ABI
  return 16;
#else
  return 8;
#endif
}

static void
jit_try_shorten(jit_state_t * _jit, jit_reloc_t reloc, jit_pointer_t addr)
{
  (void) _jit;
  (void) reloc;
  (void) addr;
}

static void *
bless_function_pointer(void *ptr)
{
  return ptr;
}

/*
 * Jumps around the veneer
 */

static void
patch_jmp_without_veneer(jit_state_t * _jit, uint32_t * loc)
{
  fprintf(stderr, "patch_jmp_without_veneer\n");
  patch_jmp_offset(loc, _jit->pc.ui - loc);
}

static uint32_t *
jmp_without_veneer(jit_state_t * _jit)
{
  uint32_t *loc = _jit->pc.ui;
  emit_u32(_jit, _BEQ(rn(_ZERO), rn(_ZERO), 0));
  return loc;
}

/*
 * Load from pool offset
 */
static void
patch_load_from_pool_offset(uint32_t * loc, int32_t v)
{
  /*
   * not used by this backend 
   */
  (void) loc;
  (void) v;
  abort();
}

static int32_t
read_load_from_pool_offset(uint32_t * loc)
{
  /*
   * not used by this backend 
   */
  (void) loc;
  abort();
  return 0;
}
