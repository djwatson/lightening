/*
 * Copyright (C) 2012-2017  Free Software Foundation, Inc.
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

#ifndef _jit_mips_h
#define _jit_mips_h

#if _MIPS_SIM != _ABIO32
#    define NEW_ABI		1
#endif

#define JIT_NEEDS_LITERAL_POOL 1
#define JIT_USE_IMMEDIATE_RELOC 1

#if !NEW_ABI
#define JIT_PASS_DOUBLES_IN_GPR_PAIRS 1
#define JIT_PASS_FLOATS_IN_GPRS 1
#endif

#define _ZERO	JIT_GPR(0)
#define _AT	JIT_GPR(1)
#define _V0	JIT_GPR(2)
#define _V1	JIT_GPR(3)
#define _A0	JIT_GPR(4)
#define _A1	JIT_GPR(5)
#define _A2	JIT_GPR(6)
#define _A3	JIT_GPR(7)
#define _A4	JIT_GPR(8)

#if NEW_ABI
#define _A5	JIT_GPR(9)
#define _A6	JIT_GPR(10)
#define _A7	JIT_GPR(11)
#else
#define _T0	JIT_GPR(9)
#define _T1	JIT_GPR(10)
#define _T2	JIT_GPR(11)
#endif

#define _T4	JIT_GPR(12)
#define _T5	JIT_GPR(13)
#define _T6	JIT_GPR(14)
#define _T7	JIT_GPR(15)

#define _S0	JIT_GPR(16)
#define _S1	JIT_GPR(17)
#define _S2	JIT_GPR(18)
#define _S3	JIT_GPR(19)
#define _S4	JIT_GPR(20)
#define _S5	JIT_GPR(21)
#define _S6	JIT_GPR(22)
#define _S7	JIT_GPR(23)

#define _T8	JIT_GPR(24)
#define _T9	JIT_GPR(25)

/* k0-k1 reserved for kernel usage */

#define _GP	JIT_GPR(28)
#define _SP	JIT_GPR(29)
#define _FP	JIT_GPR(30)

#define _RA	JIT_GPR(31)

#define _F0	JIT_FPR(0)
#define _F1	JIT_FPR(1)
#define _F2	JIT_FPR(2)
#define _F3	JIT_FPR(3)
#define _F4	JIT_FPR(4)
#define _F5	JIT_FPR(5)
#define _F6	JIT_FPR(6)
#define _F7	JIT_FPR(7)
#define _F8	JIT_FPR(8)
#define _F9	JIT_FPR(9)
#define _F10	JIT_FPR(10)
#define _F11	JIT_FPR(11)
#define _F12	JIT_FPR(12)
#define _F13	JIT_FPR(13)
#define _F14	JIT_FPR(14)
#define _F15	JIT_FPR(15)
#define _F16	JIT_FPR(16)
#define _F17	JIT_FPR(17)
#define _F18	JIT_FPR(18)
#define _F19	JIT_FPR(19)
#define _F20	JIT_FPR(20)
#define _F21	JIT_FPR(21)
#define _F22	JIT_FPR(22)
#define _F23	JIT_FPR(23)
#define _F24	JIT_FPR(24)
#define _F25	JIT_FPR(25)
#define _F26	JIT_FPR(26)
#define _F27	JIT_FPR(27)
#define _F28	JIT_FPR(28)
#define _F29	JIT_FPR(29)
#define _F30	JIT_FPR(30)
#define _F31	JIT_FPR(31)

#define JIT_LR	_RA
#define JIT_SP	_SP
#define JIT_FP	_FP

#define JIT_R0	_A0
#define JIT_R1	_A1
#define JIT_R2	_A2
#define JIT_R3	_A3

#if NEW_ABI
#define JIT_R4	_A4
#define JIT_R5	_A5
#define JIT_R6	_A6
#define JIT_R7	_A7
#else
#define JIT_R4	_T0
#define JIT_R5	_T1
#define JIT_R6	_T2
#define JIT_R7	_T3
#endif

#define JIT_CARRY	_T4
#define JIT_TMP0	_T5
#define JIT_TMP1	_T6
#define JIT_TMP2	_T7
#define JIT_TMP3	_T8
#define JIT_TMP4	_T9

#define JIT_V0	_S0
#define JIT_V1	_S1
#define JIT_V2	_S2
#define JIT_V3	_S3
#define JIT_V4	_S4
#define JIT_V5	_S5
#define JIT_V6	_S6
#define JIT_V7	_S7

#define JIT_F0	_F0
#define JIT_F1	_F2
#define JIT_F2	_F4
#define JIT_F3	_F6
#define JIT_F4	_F8
#define JIT_F5	_F10
#define JIT_F6	_F12
#define JIT_F7	_F14
#define JIT_F8	_F16
#define JIT_FTMP	_F18

#if NEW_ABI
#define JIT_F9	_F20
#define JIT_F10	_F22
#else
#define JIT_VF4	_F20

#if NEW_ABI
#define JIT_F9	_F20
#define JIT_F10	_F22
#else
#define JIT_VF4	_F20
#define JIT_VF6	_F22
#endif
#define JIT_VF6	_F22
#endif

#define JIT_VF0	_F24
#define JIT_VF1	_F26
#define JIT_VF2	_F28
#define JIT_VF3	_F30

#if NEW_ABI
/* _RA is in some documents referred to as caller-save, but storing it
 * in the function stack frame works equally well, which is what we do here
 * (gcc apparently does this)
 * */
#define JIT_PLATFORM_CALLEE_SAVE_GPRS _SP, _FP, _GP, _RA
#else
#define JIT_PLATFORM_CALLEE_SAVE_GPRS _SP, _FP, _RA
#endif
#endif /* _jit_mips_h */
