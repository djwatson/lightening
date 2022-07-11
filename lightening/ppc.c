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
 *	Paulo Cesar Pereira de Andrade
 */

# define JIT_RA0                _R3
# define JIT_FA0                _F1
# define JIT_RET                _R3
# define JIT_FRET               _F1

# define rn(x) jit_gpr_regno(x)

#define jit_arg_reg_p(i)		((i) >= 0 && (i) < 8)
#define jit_arg_f_reg_p(i)		((i) >= 0 && (i) < 13)
#if __BYTE_ORDER == __LITTLE_ENDIAN
#  define C_DISP			0
#  define S_DISP			0
#  define I_DISP			0
#  define F_DISP			0
#else
#  define C_DISP			(__WORDSIZE >> 3) - sizeof(int8_t)
#  define S_DISP			(__WORDSIZE >> 3) - sizeof(int16_t)
#  define I_DISP			(__WORDSIZE >> 3) - sizeof(int32_t)
#  define F_DISP			(__WORDSIZE >> 3) - sizeof(jit_float32_t)
#endif

static const jit_gpr_t abi_gpr_args[] = {
	_R3, _R4, _R5, _R6, _R7, _R8, _R9, _R10
};

static const jit_fpr_t abi_fpr_args[] = {
	_F1, _F2, _F3, _F4, _F5, _F6, _F7, _F8, _F9, _F10, _F11, _F12, _F13
};

static const int abi_gpr_arg_count = sizeof(abi_gpr_args) / sizeof(abi_gpr_args[0]);
static const int abi_fpr_arg_count = sizeof(abi_fpr_args) / sizeof(abi_fpr_args[0]);

/*
 * Types
 */
typedef jit_pointer_t jit_va_list_t;

/* libgcc */
extern void __clear_cache(void *, void *);

#define em_wp(_jit, x) emit_u32_with_pool(_jit, (x))

// TODO fill in
typedef union {
#if __BYTE_ORDER == __BIG_ENDIAN
	struct {
		uint32_t po:6;
		uint32_t ft:5;
		uint32_t fa:5;
		uint32_t fb:5;
		uint32_t fc:5;
		uint32_t xo:5;
		uint32_t rc:1;
	} A;

	struct {
		uint32_t po:6;
		uint32_t rt:5;
		uint32_t ra:5;
		uint32_t rb:5;
		uint32_t u0:1;
		uint32_t xo:9;
		uint32_t u1:1;
	} XO;

	struct {
		uint32_t po:6;
		uint32_t rx:5;
		uint32_t ra:5;
		uint32_t d:16;
	} D;

	struct {
		uint32_t po:6;
		uint32_t f0:5;
		uint32_t ra:5;
		uint32_t rb:5;
		uint32_t xo:10;
		uint32_t u0:1;
	} X;

	struct {
		uint32_t po:6;
		int32_t li:24;
		uint32_t aa:1;
		uint32_t lk:1;
	} I;

	struct {
		uint32_t po:6;
		uint32_t bo:5;
		uint32_t bi:5;
		int32_t bd:14;
		uint32_t aa:1;
		uint32_t lk:1;
	} B;

	struct {
		uint32_t po:6;
		uint32_t bo:5;
		uint32_t ba:5;
		uint32_t bb:5;
		uint32_t xo:10;
		uint32_t lk:1;
	} XL;

	struct {
		uint32_t po:6;
		uint32_t rs:5;
		uint32_t fx:10;
		uint32_t xo:10;
		uint32_t u0:1;
	} XFX;

	struct {
		uint32_t po:6;
		uint32_t l:1;
		uint32_t fm:8;
		uint32_t w:1;
		uint32_t fb:5;
		uint32_t xo:10;
		uint32_t rc:1;
	} XFL;

	struct {
		uint32_t po:6;
		uint32_t rs:5;
		uint32_t ra:5;
		uint32_t rb:5;
		uint32_t mb:5;
		uint32_t me:5;
		uint32_t rc:1;
	} M;

#if __WORDSIZE == 64
	struct {
		uint32_t po:6;
		uint32_t rs:5;
		uint32_t ra:5;
		uint32_t rb:5;
		uint32_t mx:6;
		uint32_t xo:4;
		uint32_t rc:1;
	} MDS;

	struct {
		uint32_t po:6;
		uint32_t rs:5;
		uint32_t ra:5;
		uint32_t s0:5;
		uint32_t mx:6;
		uint32_t xo:3;
		uint32_t s1:1;
		uint32_t rc:1;
	} MD;

	struct {
		uint32_t po:6;
		uint32_t rs:5;
		uint32_t ra:5;
		uint32_t s0:5;
		uint32_t xo:9;
		uint32_t s1:1;
		uint32_t rc:1;
	} XS;
#endif
#else
	struct {
		uint32_t rc:1;
		uint32_t xo:5;
		uint32_t fc:5;
		uint32_t fb:5;
		uint32_t fa:5;
		uint32_t ft:5;
		uint32_t po:6;
	} A;

	struct {
		uint32_t u1:1;
		uint32_t xo:9;
		uint32_t u0:1;
		uint32_t rb:5;
		uint32_t ra:5;
		uint32_t rt:5;
		uint32_t po:6;
	} XO;

	struct {
		uint32_t d:16;
		uint32_t ra:5;
		uint32_t rx:5;
		uint32_t po:6;
	} D;

	struct {
		uint32_t u0:1;
		uint32_t xo:10;
		uint32_t rb:5;
		uint32_t ra:5;
		uint32_t f0:5;
		uint32_t po:6;
	} X;

	struct {
		uint32_t lk:1;
		uint32_t aa:1;
		int32_t li:24;
		uint32_t po:6;
	} I;

	struct {
		uint32_t lk:1;
		uint32_t aa:1;
		int32_t bd:14;
		uint32_t bi:5;
		uint32_t bo:5;
		uint32_t po:6;
	} B;

	struct {
		uint32_t lk:1;
		uint32_t xo:10;
		uint32_t bb:5;
		uint32_t ba:5;
		uint32_t bo:5;
		uint32_t po:6;
	} XL;

	struct {
		uint32_t u0:1;
		uint32_t xo:10;
		uint32_t fx:10;
		uint32_t rs:5;
		uint32_t po:6;
	} XFX;

	struct {
		uint32_t rc:1;
		uint32_t xo:10;
		uint32_t fb:5;
		uint32_t w:1;
		uint32_t fm:8;
		uint32_t l:1;
		uint32_t po:6;
	} XFL;

	struct {
		uint32_t rc:1;
		uint32_t me:5;
		uint32_t mb:5;
		uint32_t rb:5;
		uint32_t ra:5;
		uint32_t rs:5;
		uint32_t po:6;
	} M;

#if __WORDSIZE == 64
	struct {
		uint32_t rc:1;
		uint32_t xo:4;
		uint32_t mx:6;
		uint32_t rb:5;
		uint32_t ra:5;
		uint32_t rs:5;
		uint32_t po:6;
	} MDS;

	struct {
		uint32_t rc:1;
		uint32_t s1:1;
		uint32_t xo:3;
		uint32_t mx:6;
		uint32_t s0:5;
		uint32_t ra:5;
		uint32_t rs:5;
		uint32_t po:6;
	} MD;

	struct {
		uint32_t rc:1;
		uint32_t s1:1;
		uint32_t xo:9;
		uint32_t s0:5;
		uint32_t ra:5;
		uint32_t rs:5;
		uint32_t po:6;
	} XS;
#endif
#endif
	uint32_t w;
} instr_t;

#include "ppc-cpu.c"
#include "ppc-fpu.c"

struct abi_arg_iterator
{
  const jit_operand_t *args;
  size_t argc;

  size_t arg_idx;
  size_t gpr_idx;
  size_t fpr_idx;

  size_t stack_size;
  size_t stack_counter;
};

static size_t page_size;

/*
 * Implementation
 */
static jit_bool_t
jit_get_cpu(void)
{
	page_size = sysconf(_SC_PAGE_SIZE);
	// FIXME check hardware fp support?
	return 1;
}

static jit_bool_t
jit_init(jit_state_t *_jit)
{
	return 1;
}

static size_t
jit_initial_frame_size(void)
{
	return 16;
}

static size_t
jit_stack_alignment()
{
	return 16;
}

static void
jit_flush(void *fptr, void *tptr)
{
#if defined(__GNUC__)
    __clear_cache((void *)fptr, (void *)tptr);
#endif
}

static void
patch_jmp_without_veneer(jit_state_t *_jit, uint32_t *loc)
{
	patch_jmp_offset(loc, _jit->pc.ui - loc);
}

static uint32_t *
jmp_without_veneer(jit_state_t *_jit)
{
	uint32_t *loc = _jit->pc.ui;
	emit_u32(_jit, _B(0));
	return loc;
}

static void
patch_load_from_pool_offset(uint32_t *loc, int32_t v)
{
	/*
	 * not used by this backend
	 */
	(void)loc;
	(void)v;
	abort();
}

static int32_t
read_load_from_pool_offset(uint32_t *loc)
{
	/*
	 * not used by this backend
	 */
	(void)loc;
	abort();
	return 0;
}

static void
jit_try_shorten(jit_state_t *_jit, jit_reloc_t reloc, jit_pointer_t addr)
{
	(void)_jit;
	(void)reloc;
	(void)addr;
}

static void *
bless_function_pointer(void *ptr)
{
	return ptr;
}

static void
reset_abi_arg_iterator(struct abi_arg_iterator *iter, size_t argc,
		const jit_operand_t *args)
{
	memset(iter, 0, sizeof(*iter));
	iter->argc = argc;
	iter->args = args;
	iter->stack_size = 32;
	iter->stack_counter = 32;
}

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

static void
next_abi_arg(struct abi_arg_iterator *iter, jit_operand_t *arg)
{
	ASSERT(iter->arg_idx < iter->argc);
	enum jit_operand_abi abi = iter->args[iter->arg_idx].abi;
	iter->stack_counter += 8;
	iter->arg_idx++;

	if (is_gpr_arg(abi) && iter->gpr_idx < abi_gpr_arg_count) {
		*arg = jit_operand_gpr(abi, abi_gpr_args[iter->gpr_idx++]);
		return;
	}

	if (is_fpr_arg(abi) && iter->fpr_idx < abi_fpr_arg_count) {
		*arg = jit_operand_fpr(abi, abi_fpr_args[iter->fpr_idx++]);
		iter->gpr_idx++;
		return;
	}

	iter->stack_size = iter->stack_counter - 8;
	*arg = jit_operand_mem(abi, JIT_SP, iter->stack_size);
}

// Prepare _R0 to be saved to stack. Slightly hacky?
static void
jit_prolog(jit_state_t *_jit)
{
	pop_link_register(_jit);
}

static void
jit_epilog(jit_state_t *_jit)
{
	push_link_register(_jit);
}
