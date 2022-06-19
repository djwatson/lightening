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

#define em_wp(_jit, x) emit_u32_with_pool(_jit, (x))

// TODO fill in
typedef union {
#if __BYTE_ORDER == __LITTLE_ENDIAN
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
		uint32_t li:24;
		uint32_t aa:1;
		uint32_t lk:1;
	} I;

	struct {
		uint32_t po:6;
		uint32_t bo:5;
		uint32_t bi:5;
		uint32_t bd:14;
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
	struct {} XO;
	struct {} D;
	struct {} X;
	struct {} I;
	struct {} B;
	struct {} XL;
	struct {} C;
	struct {} CI;
	struct {} XFX;
	struct {} M;
#if __WORDSIZE == 64
	struct {} MDS;
	struct {} MD;
	struct {} XS;
#endif
#endif
	uint32_t w;
} instr_t;

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
