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
	_F12, _F14,
#if NEW_ABI
	_F16, _F18,
#endif
};

static const int abi_gpr_arg_count = sizeof(abi_gpr_args) / sizeof(abi_gpr_args[0]);
static const int abi_fpr_arg_count = sizeof(abi_fpr_args) / sizeof(abi_fpr_args[0]);

struct abi_arg_iterator {
	const jit_operand_t *args;
	int argc;

	int arg_idx;
	int gpr_idx;
	int fpr_idx;
	int vfp_used_registers;
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
	iter->arg_idx++;
	if(is_gpr_arg(abi) && iter->gpr_idx < abi_gpr_arg_count) {
		*arg = jit_operand_gpr(abi, abi_gpr_args[iter->gpr_idx++]);
		return;
	}

	if(is_fpr_arg(abi) && iter->fpr_idx < abi_fpr_arg_count) {
		*arg = jit_operand_fpr(abi, abi_fpr_args[iter->gpr_idx++]);
		return;
	}

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
	return 8;
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

struct veneer {
	instr_t auipc;
	instr_t ld;
	instr_t jr;
#if __WORDSIZE == 64
	uint64_t address;
#else
	uint32_t address;
#endif
};

static void
emit_veneer(jit_state_t *_jit, jit_pointer_t target)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	emit_u32(_jit, _AUIPC(rn(t0), 0));
#if __WORDSIZE == 64
	emit_u32(_jit, _LD(rn(t0), rn(t0), 12));
#else
	emit_u32(_jit, _LW(rn(t0), rn(t0), 12));
#endif

	emit_u32(_jit, _JR(rn(t0)));

#if __WORDSIZE == 64
	emit_u64(_jit, (uint64_t)target);
#else
	emit_u32(_jit, (uint64_t)target);
#endif
}

static void
patch_veneer(uint32_t *loc, jit_pointer_t addr)
{
	struct veneer *v = (struct veneer *)loc;
#if __WORDSIZE == 64
	v->address = (uint64_t)addr;
#else
	v->address = (uint32_t)addr;
#endif
}

/*
 * Conditional jumps
 */
static void
patch_jcc_offset(uint32_t *loc, ptrdiff_t v)
{
	instr_t *i = (instr_t *)loc;
	i->I.i0 = v >> 2;
}

static void
patch_veneer_jcc_offset(uint32_t *loc, ptrdiff_t offset){
	patch_jcc_offset(loc, offset);
}

static int32_t
read_jcc_offset(uint32_t *loc)
{
	instr_t *i = (instr_t *)loc;
	return i->I.i0 << 2;
}

static int
offset_in_jcc_range(ptrdiff_t offset, int flags)
{
	(void)flags;

	if(offset & 0x3)
		return 0;
	else
		return simm16_p(offset);
}

/*
 * Unconditional jumps
 */
static int32_t
read_jmp_offset(uint32_t *loc)
{
	instr_t *i = (instr_t *)loc;
	return i->I.i0 << 2;
}

static int
offset_in_jmp_range(ptrdiff_t offset, int flags)
{
	(void)flags;
	if(offset & 0x3)
		return 0;

	return simm16_p(offset); /* TODO: make sure we only use branches? */
}

static void
patch_jmp_offset(uint32_t *loc, ptrdiff_t v)
{
	instr_t *i = (instr_t *)loc;
	i->I.i0 = v >> 2; /* should really check this */
}

static void
patch_veneer_jmp_offset(uint32_t *loc, ptrdiff_t offset)
{
	patch_jmp_offset(loc, offset);
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
	emit_u32(_jit, _BEQ(0, 0, 0));
	return loc;
}

/*
 * Load from pool offset
 */
static void
patch_load_from_pool_offset(uint32_t *loc, int32_t v)
{
	load_from_pool_t *i = (load_from_pool_t *)loc;
	i->inst.auipc.I.i0 = (v >> 8);
	i->inst.load.I.i0 = v & 0xffff;
}

static int32_t
read_load_from_pool_offset(uint32_t *loc)
{
	load_from_pool_t *i = (load_from_pool_t *)loc;
	return (i->inst.auipc.I.i0 << 16) + i->inst.load.I.i0;
}
