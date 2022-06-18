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

#ifndef _jit_ppc_h
#define _jit_ppc_h

#define JIT_NEEDS_LITERAL_POOL 1

#if __powerpc__
#  if _CALL_ELF == 2
/* __BYTE_ORDER == __LITTLE_ENDIAN */
#    define ABI_ELFv2		1
#  endif
#endif

#define _R0 JIT_GPR(0)
#define _R1 JIT_GPR(1)
#define _R2 JIT_GPR(2)
#define _R3 JIT_GPR(3)
#define _R4 JIT_GPR(4)
#define _R5 JIT_GPR(5)
#define _R6 JIT_GPR(6)
#define _R7 JIT_GPR(7)
#define _R8 JIT_GPR(8)
#define _R9 JIT_GPR(9)
#define _R10 JIT_GPR(10)
#define _R11 JIT_GPR(11)
#define _R12 JIT_GPR(12)
#define _R13 JIT_GPR(13)
#define _R14 JIT_GPR(14)
#define _R15 JIT_GPR(15)
#define _R16 JIT_GPR(16)
#define _R17 JIT_GPR(17)
#define _R18 JIT_GPR(18)
#define _R19 JIT_GPR(19)
#define _R20 JIT_GPR(20)
#define _R21 JIT_GPR(21)
#define _R22 JIT_GPR(22)
#define _R23 JIT_GPR(23)
#define _R24 JIT_GPR(24)
#define _R25 JIT_GPR(25)
#define _R26 JIT_GPR(26)
#define _R27 JIT_GPR(27)
#define _R28 JIT_GPR(28)
#define _R29 JIT_GPR(29)
#define _R30 JIT_GPR(30)
#define _R31 JIT_GPR(31)

#define _F0 JIT_FPR(0)
#define _F1 JIT_FPR(1)
#define _F2 JIT_FPR(2)
#define _F3 JIT_FPR(3)
#define _F4 JIT_FPR(4)
#define _F5 JIT_FPR(5)
#define _F6 JIT_FPR(6)
#define _F7 JIT_FPR(7)
#define _F8 JIT_FPR(8)
#define _F9 JIT_FPR(9)
#define _F10 JIT_FPR(10)
#define _F11 JIT_FPR(11)
#define _F12 JIT_FPR(12)
#define _F13 JIT_FPR(13)
#define _F14 JIT_FPR(14)
#define _F15 JIT_FPR(15)
#define _F16 JIT_FPR(16)
#define _F17 JIT_FPR(17)
#define _F18 JIT_FPR(18)
#define _F19 JIT_FPR(19)
#define _F20 JIT_FPR(20)
#define _F21 JIT_FPR(21)
#define _F22 JIT_FPR(22)
#define _F23 JIT_FPR(23)
#define _F24 JIT_FPR(24)
#define _F25 JIT_FPR(25)
#define _F26 JIT_FPR(26)
#define _F27 JIT_FPR(27)
#define _F28 JIT_FPR(28)
#define _F29 JIT_FPR(29)
#define _F30 JIT_FPR(30)
#define _F31 JIT_FPR(31)

#define JIT_R0 _R3
#define JIT_R1 _R4
#define JIT_R2 _R5
#define JIT_R3 _R6
#define JIT_R4 _R7
#define JIT_R5 _R8
#define JIT_R6 _R9
#define JIT_R7 _R10

#define JIT_V0 _R14
#define JIT_V1 _R15
#define JIT_V2 _R16
#define JIT_V3 _R17
#define JIT_V4 _R18
#define JIT_V5 _R19
#define JIT_V6 _R20
#define JIT_V7 _R21
#define JIT_V8 _R22
#define JIT_V9 _R23
#define JIT_V10 _R24
#define JIT_V11 _R25
#define JIT_V12 _R26
#define JIT_V13 _R27
#define JIT_V14 _R28
#define JIT_TMP1 _R29
#define JIT_TMP0 _R30

#define JIT_FP _R31
#define JIT_SP _R1

#define JIT_F0 _F0
#define JIT_F1 _F1
#define JIT_F2 _F2
#define JIT_F3 _F3
#define JIT_F4 _F4
#define JIT_F5 _F5
#define JIT_F6 _F6
#define JIT_F7 _F7
#define JIT_F8 _F8
#define JIT_F9 _F9
#define JIT_F10 _F10
#define JIT_F11 _F11
#define JIT_F12 _F12
#define JIT_F13 _F13

#define JIT_VF0 _F14
#define JIT_VF1 _F15
#define JIT_VF2 _F16
#define JIT_VF3 _F17
#define JIT_VF4 _F18
#define JIT_VF5 _F19
#define JIT_VF6 _F20
#define JIT_VF7 _F21
#define JIT_VF8 _F22
#define JIT_VF9 _F23
#define JIT_VF10 _F24
#define JIT_VF11 _F25
#define JIT_VF12 _F26
#define JIT_VF13 _F27
#define JIT_VF14 _F28
#define JIT_VF15 _F29
#define JIT_VF16 _F30
#define JIT_FTMP _F31

#define JIT_PLATFORM_CALLEE_SAVE_GPRS JIT_SP, JIT_FP, JIT_TMP0, JIT_TMP1, JIT_FTMP

#endif /* _jit_ppc_h */
