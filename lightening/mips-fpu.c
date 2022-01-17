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
#define FMT_S			0x10		/* float32 */
#define FMT_D			0x11		/* float64 */
#define FMT_W			0x14		/* int32 */
#define FMT_L			0x15		/* int64 */
#define FMT_P			0x16		/* 2 x float32 */
#define FMT_S_PU		0x20
#define FMT_S_PL		0x26
#define FUN_ADD			0x00
#define FUN_LWXC1		0x00
#define FUN_SUB			0x01
#define FUN_LDXC1		0x01
#define FUN_MUL			0x02
#define FUN_DIV			0x03
#define FUN_SQRT		0x04
#define FUN_ABS			0x05
#define FUN_LUXC1		0x05
#define FUN_MOV			0x06
#define FUN_NEG			0x07
#define FUN_SWXC1		0x08
#define FUN_ROUND_L		0x08
#define FUN_TRUNC_L		0x09
#define FUN_SDXC1		0x09
#define FUN_CEIL_L		0x0a
#define FUN_FLOOR_L		0x0b
#define FUN_ROUND_W		0x0c
#define FUN_TRUNC_W		0x0d
#define FUN_SUXC1		0x0d
#define FUN_CEIL_W		0x0e
#define FUN_FLOOR_W		0x0f
#define FUN_RECIP		0x15
#define FUN_RSQRT		0x16
#define FUN_ALNV_P		0x1e
#define FUN_CVT_S		0x20
#define FUN_CVT_D		0x21
#define FUN_CVT_W		0x24
#define FUN_CVT_L		0x25
#define FUN_PLL			0x2c
#define FUN_PLU			0x2d
#define FUN_PUL			0x2e
#define FUN_PUU			0x2f
#define FUN_MADD_S		(0x20 | FMT_S)
#define FUN_MADD_D		(0x20 | FMT_D)
#define FUN_MADD_P		(0x20 | FMT_P)
#define FUN_MSUB_S		(0x28 | FMT_S)
#define FUN_MSUB_D		(0x28 | FMT_D)
#define FUN_MSUB_P		(0x28 | FMT_P)
#define FUN_NMADD_S		(0x30 | FMT_S)
#define FUN_NMADD_D		(0x30 | FMT_D)
#define FUN_NMADD_P		(0x30 | FMT_P)
#define FUN_NMSUB_S		(0x38 | FMT_S)
#define FUN_NMSUB_D		(0x38 | FMT_D)
#define FUN_NMSUB_P		(0x38 | FMT_P)
#define COND_F			0x30
#define COND_UN			0x31
#define COND_EQ			0x32
#define COND_UEQ		0x33
#define COND_OLT		0x34
#define COND_ULT		0x35
#define COND_OLE		0x36
#define COND_ULE		0x37
#define COND_SF			0x38
#define COND_NGLE		0x39
#define COND_SEQ		0x3a
#define COND_NGL		0x3b
#define COND_LT			0x3c
#define COND_NGE		0x3d
#define COND_LE			0x3e
#define COND_UGT		0x3f

#define _ADD_S(fd, fs, ft)	Rtype(FUN_COP1, FMT_S, ft, fs, fd, FMT_ADD)
#define _ADD_D(fd, fs, ft)	Rtype(FUN_COP1, FMT_D, ft, fs, fd, FMT_ADD)
#define _SUB_S(fd, fs, ft)	Rtype(FUN_COP1, FMT_S, ft, fs, fd, FMT_SUB)
#define _SUB_D(fd, fs, ft)	Rtype(FUN_COP1, FMT_D, ft, fs, fd, FMT_SUB)
#define _MUL_S(fd, fs, ft)	Rtype(FUN_COP1, FMT_S, ft, fs, fd, FMT_MUL)
#define _MUL_D(fd, fs, ft)	Rtype(FUN_COP1, FMT_D, ft, fs, fd, FMT_MUL)
#define _DIV_S(fd, fs, ft)	Rtype(FUN_COP1, FMT_S, ft, fs, fd, FMT_DIV)
#define _DIV_D(fd, fs, ft)	Rtype(FUN_COP1, FMT_D, ft, fs, fd, FMT_DIV)
#define _ABS_S(fd, fs)		Rtype(FUN_COP1, FMT_S, 00, fs, fd, FMT_ABS)
#define _ABS_D(fd, fs)		Rtype(FUN_COP1, FMT_D, 00, fs, fd, FMT_ABS)
#define _NEG_S(fd, fs)		Rtype(FUN_COP1, FMT_S, 00, fs, fd, FMT_NEG)
#define _NEG_D(fd, fs)		Rtype(FUN_COP1, FMT_D, 00, fs, fd, FMT_NEG)
#define _SQRT_S(fd, fs)		Rtype(FUN_COP1, FMT_S, 00, fs, fd, FMT_SQRT)
#define _SQRT_D(fd, fs)		Rtype(FUN_COP1, FMT_D, 00, fs, fd, FMT_SQRT)
#define _MFC1(rt, fs)		Rtype(FUN_COP1, OP_MF, rt, fs, 00, 00)
#define _MTC1(rt, fs)		Rtype(FUN_COP1, OP_MT, rt, fs, 00, 00)
#define _DMFC1(rt, fs)		Rtype(FUN_COP1, OP_DMF, rt, fs, 00, 00)
#define _DMTC1(rt, fs)		Rtype(FUN_COP1, OP_DMT, rt, fs, 00, 00)
#define _CVT_D_S(fd, fs)	Rtype(FUN_COP1, FMT_S, 0, fs, fd, FMT_CVT_D)
#define _CVT_D_W(fd, fs)	Rtype(FUN_COP1, FMT_W, 0, fs, fd, FMT_CVT_D)
#define _CVT_D_L(fd, fs)	Rtype(FUN_COP1, FMT_L, 0, fs, fd, FMT_CVT_D)
#define _CVT_L_S(fd, fs)	Rtype(FUN_COP1, FMT_S, 0, fs, fd, FMT_CVT_L)
#define _CVT_L_D(fd, fs)	Rtype(FUN_COP1, FMT_D, 0, fs, fd, FMT_CVT_L)
#define _CVT_P_S(fd, fs)	Rtype(FUN_COP1, FMT_S, 0, fs, fd, FMT_CVT_P)
#define _CVT_S_D(fd, fs)	Rtype(FUN_COP1, FMT_D, 0, fs, fd, FMT_CVT_S)
#define _CVT_S_W(fd, fs)	Rtype(FUN_COP1, FMT_W, 0, fs, fd, FMT_CVT_S)
#define _CVT_S_L(fd, fs)	Rtype(FUN_COP1, FMT_L, 0, fs, fd, FMT_CVT_S)
#define _CVT_S_PL(fd, fs)	Rtype(FUN_COP1, FMT_P, 0, fs, fd, FMT_CVT_S_PL)
#define _CVT_S_PU(fd, fs)	Rtype(FUN_COP1, FMT_P, 0, fs, fd, FMT_CVT_S_PU)
#define _CVT_W_S(fd, fs)	Rtype(FUN_COP1, FMT_S, 0, fs, fd, FMT_CVT_W)
#define _CVT_W_D(fd, fs)	Rtype(FUN_COP1, FMT_D, 0, fs, fd, FMT_CVT_W)
#define _TRUNC_L_S(fd, fs)	Rtype(FUN_COP1, FMT_S, 0, fs, fd, FMT_TRUNC_L)
#define _TRUNC_L_D(fd, fs)	Rtype(FUN_COP1, FMT_D, 0, fs, fd, FMT_TRUNC_L)
#define _TRUNC_W_S(fd, fs)	Rtype(FUN_COP1, FMT_S, 0, fs, fd, FMT_TRUNC_W)
#define _TRUNC_W_D(fd, fs)	Rtype(FUN_COP1, FMT_D, 0, fs, fd, FMT_TRUNC_W)
#define _LWC1(rt, of, rb)	Itype(FUN_LWC1, rb, rt, of)
#define _SWC1(rt, of, rb)	Itype(FUN_SWC1, rb, rt, of)
#define _LDC1(rt, of, rb)	Itype(FUN_LDC1, rb, rt, of)
#define _SDC1(rt, of, rb)	Itype(FUN_SDC1, rb, rt, of)
#define _MOV_S(fd, fs)		Rtype(FUN_COP1, FMT_S, 0, fs, fd, FMT_MOV)
#define _MOV_D(fd, fs)		Rtype(FUN_COP1, FMT_D, 0, fs, fd, FMT_MOV)
#define _BC1F(im)		Itype(FUN_COP1, OP_BC, OP_BCF, im)
#define _BC1T(im)		Itype(FUN_COP1, OP_BC, OP_BCT, im)
#define _C_F_S(fs, ft)		Rtype(FUN_COP1, FMT_S, ft, fs, COND_F)
#define _C_F_D(fs, ft)		Rtype(FUN_COP1, FMT_D, ft, fs, COND_F)
#define _C_F_P(fs, ft)		Rtype(FUN_COP1, FMT_P, ft, fs, CONF_F)
#define _C_UN_S(fs, ft)		Rtype(FUN_COP1, FMT_S, ft, fs, COND_UN)
#define _C_UN_D(fs, ft)		Rtype(FUN_COP1, FMT_D, ft, fs, COND_UN)
#define _C_UN_P(fs, ft)		Rtype(FUN_COP1, FMT_P, ft, fs, COND_UN)
#define _C_EQ_S(fs, ft)		Rtype(FUN_COP1, FMT_S, ft, fs, COND_EQ)
#define _C_EQ_D(fs, ft)		Rtype(FUN_COP1, FMT_D, ft, fs, COND_EQ)
#define _C_EQ_P(fs, ft)		Rtype(FUN_COP1, FMT_P, ft, fs, COND_EQ)
#define _C_UEQ_S(fs, ft)	Rtype(FUN_COP1, FMT_S, ft, fs, COND_UEQ)
#define _C_UEQ_D(fs, ft)	Rtype(FUN_COP1, FMT_D, ft, fs, COND_UEQ)
#define _C_UEQ_P(fs, ft)	Rtype(FUN_COP1, FMT_P, ft, fs, COND_UEQ)
#define _C_OLT_S(fs, ft)	Rtype(FUN_COP1, FMT_S, ft, fs, CONF_OLT)
#define _C_OLT_D(fs, ft)	Rtype(FUN_COP1, FMT_D, ft, fs, CONF_OLT)
#define _C_OLT_P(fs, ft)	Rtype(FUN_COP1, FMT_P, ft, fs, CONF_OLT)
#define _C_ULT_S(fs, ft)	Rtype(FUN_COP1, FMT_S, ft, fs, CONF_ULT)
#define _C_ULT_D(fs, ft)	Rtype(FUN_COP1, FMT_D, ft, fs, CONF_ULT)
#define _C_ULT_P(fs, ft)	Rtype(FUN_COP1, FMT_P, ft, fs, CONF_ULT)
#define _C_OLE_S(fs, ft)	Rtype(FUN_COP1, FMT_S, ft, fs, CONF_OLE)
#define _C_OLE_D(fs, ft)	Rtype(FUN_COP1, FMT_D, ft, fs, CONF_OLE)
#define _C_OLE_P(fs, ft)	Rtype(FUN_COP1, FMT_P, ft, fs, CONF_OLE)
#define _C_ULE_S(fs, ft)	Rtype(FUN_COP1, FMT_S, ft, fs, CONF_ULE)
#define _C_ULE_D(fs, ft)	Rtype(FUN_COP1, FMT_D, ft, fs, CONF_ULE)
#define _C_ULE_P(fs, ft)	Rtype(FUN_COP1, FMT_D, ft, fs, CONF_ULE)
#define _C_SF_S(fs, ft)		Rtype(FUN_COP1, FMT_S, ft, fs, CONF_SF)
#define _C_SF_D(fs, ft)		Rtype(FUN_COP1, FMT_D, ft, fs, CONF_SF)
#define _C_SF_P(fs, ft)		Rtype(FUN_COP1, FMT_P, ft, fs, CONF_SF)
#define _C_NGLE_S(fs, ft)	Rtype(FUN_COP1, FMT_S, ft, fs, CONF_NGLE)
#define _C_NGLE_D(fs, ft)	Rtype(FUN_COP1, FMT_D, ft, fs, CONF_NGLE)
#define _C_NGLE_P(fs, ft)	Rtype(FUN_COP1, FMT_P, ft, fs, CONF_NGLE)
#define _C_SEQ_S(fs, ft)	Rtype(FUN_COP1, FMT_S, ft, fs, CONF_SEQ)
#define _C_SEQ_D(fs, ft)	Rtype(FUN_COP1, FMT_D, ft, fs, CONF_SEQ)
#define _C_SEQ_P(fs, ft)	Rtype(FUN_COP1, FMT_P, ft, fs, CONF_SEQ)
#define _C_NGL_S(fs, ft)	Rtype(FUN_COP1, FMT_S, ft, fs, CONF_NGL)
#define _C_NGL_D(fs, ft)	Rtype(FUN_COP1, FMT_D, ft, fs, CONF_NGL)
#define _C_NGL_P(fs, ft)	Rtype(FUN_COP1, FMT_P, ft, fs, CONF_NGL)
#define _C_NLT_S(fs, ft)	Rtype(FUN_COP1, FMT_S, ft, fs, CONF_NLT)
#define _C_NLT_D(fs, ft)	Rtype(FUN_COP1, FMT_D, ft, fs, CONF_NLT)
#define _C_NLT_P(fs, ft)	Rtype(FUN_COP1, FMT_P, ft, fs, CONF_NLT)
#define _C_NGE_S(fs, ft)	Rtype(FUN_COP1, FMT_S, ft, fs, CONF_NGE)
#define _C_NGE_D(fs, ft)	Rtype(FUN_COP1, FMT_D, ft, fs, CONF_NGE)
#define _C_NGE_P(fs, ft)	Rtype(FUN_COP1, FMT_P, ft, fs, CONF_NGE)
#define _C_NLE_S(fs, ft)	Rtype(FUN_COP1, FMT_S, ft, fs, CONF_NLE)
#define _C_NLE_D(fs, ft)	Rtype(FUN_COP1, FMT_D, ft, fs, CONF_NLE)
#define _C_NLE_P(fs, ft)	Rtype(FUN_COP1, FMT_P, ft, fs, CONF_NLE)
#define _C_UGT_S(fs, ft)	Rtype(FUN_COP1, FMT_S, ft, fs, CONF_UGT)
#define _C_UGT_D(fs, ft)	Rtype(FUN_COP1, FMT_D, ft, fs, CONF_UGT)
#define _C_UGT_P(fs, ft)	Rtype(FUN_COP1, FMT_SP, ft, fs, CONF_UGT)

static void addr_f(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void addr_d(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void subr_f(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void subr_d(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void mulr_f(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void mulr_d(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void divr_f(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void divr_d(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);

static void sqrtr_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static void sqrtr_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static void negr_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static void negr_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static void absr_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static void absr_d(jit_state_t *_jit, int32_t r0, int32_t r1);

static void movr_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static void movr_d(jit_state_t *_jit, int32_t r0, int32_t r1);

static void retval_f(jit_state_t *_jit, int32_t r0);
static void retval_d(jit_state_t *_jit, int32_t r0);
static void retr_f(jit_state_t *_jit, int32_t u);
static void retr_d(jit_state_t *_jit, int32_t u);

static void ldr_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static void ldr_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static void ldi_f(jit_state_t *_jit, int32_t r0, jit_word_t i0);
static void ldxr_f(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void ldxi_f(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);
static void ldi_d(jit_state_t *_jit, int32_t r0, jit_word_t i0);
static void ldxr_d(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void ldxi_d(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);

static void str_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static void str_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static void sti_f(jit_state_t *_jit, jit_word_t i0, int32_t r0);
static void stxr_f(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void stxi_f(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1);
static void sti_d(jit_state_t *_jit, jit_word_t i0, int32_t r0);
static void stxr_d(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void stxi_d(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1);

static jit_reloc_t bltr_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bler_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t beqr_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bger_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bgtr_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bner_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bunltr_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bunler_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t buneqr_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bunger_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bungtr_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bltgtr_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bordr_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bunordr_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bltr_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bler_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t beqr_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bger_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bgtr_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bner_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bunltr_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bunler_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t buneqr_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bunger_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bungtr_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bltgtr_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bordr_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bunordr_d(jit_state_t *_jit, int32_t r0, int32_t r1);

static void truncr_f_l(jit_state_t *_jit, int32_t r0, int32_t r1);
static void truncr_d_l(jit_state_t *_jit, int32_t r0, int32_t r1);
static void truncr_f_i(jit_state_t *_jit, int32_t r0, jit_word_t i0);
static void truncr_d_i(jit_state_t *_jit, int32_t r0, jit_word_t i0);

static void extr_f(jit_state_t *_jit, int32_t r0, int32_t r1);
static void extr_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static void extr_f_d(jit_state_t *_jit, int32_t r0, int32_t r1);
static void extr_d_f(jit_state_t *_jit, int32_t t0, int32_t r1);

static void movi_f(jit_state_t *_jit, int32_t r0, jit_float32_t i0);
static void movi_d(jit_state_t *_jit, int32_t r0, jit_float64_t i0);
