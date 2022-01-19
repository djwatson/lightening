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

#  include "mips-cpu.c"
#  include "mips-fpu.c"

static const jit_gpr_t abi_gpr_args[] = {
	_A0, _A1, _A2, _A3, _A4,
#if NEW_ABI
	_A5, _A6, _A7,
#endif
};

static const jit_fpr_t abi_fpr_args[] = {
#if NEW_ABI
	_F12, _F13, _F14, _F15, _F16, _F17, _F18, _F19
#else
	_F12, _F14
#endif
};

static const int abi_gpr_arg_count = sizeof(abi_gpr_args) / sizeof(abi_gpr_args[0]);
static const int abi_fpr_arg_count = sizeof(abi_fpr_args) / sizeof(abi_fpr_args[0]);

struct abi_arg_iterator {
	const jit_operand_t *args;
	int argc;

	int arg_idx;
	int stack_size;
	int stack_padding;
};

static size_t page_size;

/*
 * Implementation
 */
jit_bool_t
jit_get_cpu(void)
{
	page_size = sysconf(_SC_PAGE_SIZE);
	/* TODO: extensions? */
	return 1;
}

jit_bool_t
jit_init(jit_state_t *_jit)
{
	(void)_jit;
	return 1;
}

static size_t
jit_initial_frame_size(void)
{
	return 0;
}

static void
reset_abi_arg_iterator(struct abi_arg_iterator *iter, size_t argc,
		const jit_operand_t *args)
{
	memset(iter, 0, sizeof(*iter));
	iter->argc = argc;
	iter->args = args;
}

static void
next_abi_arg(struct abi_arg_iterator *iter, jit_operand_t *arg)
{
	ASSERT(iter->arg_idx < iter->argc);
	enum jit_operand_abi abi = iter->args[iter->arg_idx].abi;
	int idx = iter->arg_idx++;
#if NEW_ABI
	if(is_gpr_arg(abi) && idx < 8) {
		*arg = jit_operand_gpr(abi, abi_gpr_args[idx]);
		return;
	}

	if(is_fpr_arg(abi) && idx < 8) {
		*arg = jit_operand_fpr(abi, abi_fpr_args[idx]);
		return;
	}
#else
	/* TODO: old argument passing is a mess */
#endif

	*arg = jit_operand_mem(abi, JIT_SP, iter->stack_size);
	iter->stack_size += sizeof(intmax_t);
}

static void
jit_flush(void *fptr, void *tptr)
{
	jit_word_t f = (jit_word_t)fptr & -page_size;
	jit_word_t t = (((jit_word_t)tptr) + page_size - 1) & -page_size;
	__clear_cache((void *)f, (void *)t);
}

static inline size_t
jit_stack_alignment(void)
{
#if NEW_ABI
	return 8;
#else
	return 4;
#endif
}

static void
jit_try_shorten(jit_state_t *_jit, jit_reloc_t reloc, jit_pointer_t addr)
{
	(void)_jit;
	(void)reloc;
	(void)addr;
}

static void*
bless_function_pointer(void *ptr)
{
	return ptr;
}


/*
 * Jumps around the veneer
 */

static void
patch_jmp_without_veneer(jit_state_t *_jit, uint32_t *loc)
{
	patch_jmp_offset(loc, _jit->pc.ui - loc);
}

static uint32_t*
jmp_without_veneer(jit_state_t *_jit)
{
	uint32_t *loc = _jit->pc.ui;
	emit_u32(_jit, _BEQ(rn(_ZERO), rn(_ZERO), 0));
	return loc;
}

/*
 * Load from pool offset
 */
static void
patch_load_from_pool_offset(uint32_t *loc, int32_t v)
{
	(void)loc; (void)v;
	/* not used by this backend */
	abort();
}

static int32_t
read_load_from_pool_offset(uint32_t *loc)
{
	(void)loc;
	abort();
	return 0;
	/* not used by this backend */
}
