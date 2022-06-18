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

/*
 * Types
 */
typedef jit_pointer_t jit_va_list_t;

/* libgcc */
extern void __clear_cache(void *, void *);

#include "ppc-cpu.c"
#include "ppc-fpu.c"

static const jit_gpr_t abi_gpr_args[] = {
	_R3, _R4, _R5, _R6, _R7, _R8, _R9, _R10
};
static const size_t abi_gpr_arg_count = sizeof(abi_gpr_args) / sizeof(abi_gpr_args[0]);

struct abi_arg_iterator
{
  const jit_operand_t *args;
  size_t argc;

  size_t arg_idx;
  size_t gpr_idx;
  uint32_t vfp_used_registers;
  size_t stack_size;
  size_t stack_padding;
};

static size_t page_size;

/*
 * Implementation
 */
jit_bool_t
jit_get_cpu(void)
{
	page_size = sysconf(_SC_PAGE_SIZE);
	// FIXME check hardware fp support?
	return 1;
}

jit_bool_t
jit_init(jit_state_t *_jit)
{
	return 1;
}

static size_t
jit_initial_frame_size(void)
{
	// FIXME check
	return 0;
}

void
jit_flush(void *fptr, void *tptr)
{
#if defined(__GNUC__)
    __clear_cache((void *)f, (void *)t);
#endif
}
