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

typedef union {
#if __BYTE_ORDER == __LITTLE_ENDIAN
	struct {
		uint32_t funct : 6;
		uint32_t shamt : 5;
		uint32_t rd : 5;
		uint32_t rt : 5;
		uint32_t rs : 5;
		uint32_t op : 6;
	} R;

	struct {
		int32_t i0 : 16;
		uint32_t rt : 5;
		uint32_t rs : 5;
		uint32_t op : 6;
	} I;

	struct {
		uint32_t addr : 26;
		uint32_t op : 6;
	} J;
#else
	struct {
		uint32_t op : 6;
		uint32_t rs : 5;
		uint32_t rt : 5;
		uint32_t rd : 5;
		uint32_t shamt : 5;
		uint32_t funct : 6;
	} R;

	struct {
		uint32_t op : 6;
		uint32_t rs : 5;
		uint32_t rt : 5;
		int32_t i0 : 16;
	} I;

	struct {
		uint32_t op : 6;
		uint32_t addr : 26;
	} J;
#endif
	uint32_t w;
} instr_t;

#define can_sign_extend_short_p(im)	((im) >= -32678 && (im) <= 32767)
#define can_zero_extend_short_p(im)	((im) >= 0 && (im) <= 65535)
#if __WORDSIZE == 32
#  define can_sign_extend_int_p(im)	1
#  define can_zero_extend_int_p(im)	1
#else
#  define can_sign_extend_int_p(im)					\
      (((im) >= 0 && (im) <=  0x7fffffffL) ||				\
       ((im) <  0 && (im) >= -0x80000000L))
#  define can_zero_extend_int_p(im)	((im) >= 0 && (im) <= 0xffffffff)
#endif

#define simm16_p(i0) ((i0) <= 0x7fff && (i0) >= -0x8000)
#define simm18_p(i0) ((i0) <= 0x1ffff && (i0) >= -0x20000)
#define simm26_p(i0) ((i0) <= 0x1ffffff && (i0) >= -0x2000000)

#define uimm16_p(i0) (!((i0) & ~0xffff))
#define uimm18_p(i0) (!((i0) & ~0x3ffff))
#define uimm26_p(i0) (!((i0) & ~0x3ffffff))

#define op_p(op) (!((op) & ~0x3f))
#define reg_p(r) (!((r) & ~0x1f))

#define em_wp(jit, inst)	emit_u32_with_pool(jit, inst)

	static uint32_t
Rtype(int32_t op, int32_t rs, int32_t rt, int32_t rd, int32_t shamt, int32_t funct)
{
	instr_t i;
	assert(op_p(op));
	assert(reg_p(rs));
	assert(reg_p(rt));
	assert(reg_p(rd));
	assert(!(shamt & ~0x1f));
	assert(!(funct & ~0x3f));
	i.R.op = op;
	i.R.rs = rs;
	i.R.rt = rt;
	i.R.rd = rd;
	i.R.shamt = shamt;
	i.R.funct = funct;
	return i.w;
}

	static uint32_t
Itype(int32_t op, int32_t rs, int32_t rt, int32_t i0)
{
	instr_t i;
	assert(op_p(op));
	assert(reg_p(rs));
	assert(reg_p(rt));
	assert(simm16_p(i0) || uimm16_p(i0));
	i.I.op = op;
	i.I.rs = rs;
	i.I.rt = rt;
	i.I.i0 = i0;
	return i.w;
}

	static uint32_t
Jtype(int32_t op, int32_t addr)
{
	instr_t i;
	assert(op_p(op));
	assert(simm26_p(addr) || uimm26_p(addr));
	i.J.op = op;
	i.J.addr = addr;
	return i.w;
}

/* FIXME */
#define jit_mips2_p()			0x00
#define OP_SPECIAL			0x00
#define OP_REGIMM			0x01
#define OP_J				0x02
#define OP_SRL			0x02
#define OP_JAL			0x03
#define OP_SRA			0x03
#define OP_BEQ			0x04
#define OP_BNE			0x05
#define OP_BLEZ			0x06
#define OP_BGTZ			0x07
#define OP_ADDI			0x08
#define OP_ADDIU			0x09
#define OP_SLTI			0x0a
#define OP_SLTIU			0x0b
#define OP_ANDI			0x0c
#define OP_ORI			0x0d
#define OP_XORI			0x0e
#define OP_LUI			0x0f
#define OP_COP0			0x10
#define OP_COP1			0x11
#define OP_COP2			0x12
#define OP_COP1X			0x13
#define OP_BEQL			0x14
#define OP_BNEL			0x15
#define OP_BLEZL			0x16
#define OP_BGTZL			0x17
#define OP_DADDI			0x18
#define OP_DADDIU			0x19
#define OP_LDL			0x1a
#define OP_LDR			0x1b
#define OP_SPECIAL2			0x1c
#define OP_JALX			0x1d
#define OP_SPECIAL3			0x1f
#define OP_LB				0x20
#define OP_LH				0x21
#define OP_LWL			0x22
#define OP_LW				0x23
#define OP_LBU			0x24
#define OP_LHU			0x25
#define OP_LWR			0x26
#define OP_LWU			0x27
#define OP_SB				0x28
#define OP_SH				0x29
#define OP_SWL			0x2a
#define OP_SW				0x2b
#define OP_SWR			0x2e
#define OP_CACHE			0x2f
#define OP_LL				0x30
#define OP_LWC1			0x31
#define OP_LWC2			0x32
#define OP_PREF			0x33
#define OP_LLD			0x34
#define OP_LDC1			0x35
#define OP_LDC2			0x36
#define OP_LD				0x37
#define OP_SC				0x38
#define OP_SCD			0x3c
#define OP_SDC1			0x3d
#define OP_SDC2			0x3e
#define OP_SWC1			0x39
#define OP_SWC2			0x3a
#define OP_SD				0x3f
#define OP_MF				0x00
#define OP_MFH				0x03
#define OP_DMF			0x01
#define OP_CF				0x02
#define OP_MFH			0x03
#define OP_MT				0x04
#define OP_MTH				0x07
#define OP_DMT			0x05
#define OP_CT				0x06
#define OP_MTH			0x07
#define OP_BC				0x08
#define OP_WRPGPR			0x0e
#define OP_BGZAL			0x11
#define OP_MFMC0			0x11
#define OP_BCF			0x00
#define OP_BLTZ			0x00
#define OP_BCT			0x01
#define OP_BGEZ			0x01
#define OP_BCFL			0x02
#define OP_BLTZL			0x02
#define OP_BCTL			0x03
#define OP_BGEZL			0x03
#define OP_TGEI			0x08
#define OP_TGEIU			0x09
#define OP_TLTI			0x0a
#define OP_TLTIU			0x0b
#define OP_TEQI			0x0c
#define OP_TNEI			0x0e
#define OP_BLTZAL			0x10
#define OP_BGEZAL			0x11
#define OP_BLTZALL			0x12
#define OP_BGEZALL			0x13
#define OP_SYNCI			0x1f
#define OP_WSBH			0x02
#define OP_DBSH			0x02
#define OP_DSHD			0x05
#define OP_SEB			0x10
#define OP_SEH			0x18
#define OP_MADD			0x00
#define OP_SLL			0x00
#define OP_EXT			0x00
#define OP_DEXTM			0x01
#define OP_MADDU			0x01
#define OP_MOVFT			0x01
#define OP_TLBR			0x01
#define OP_MUL			0x02
#define OP_DEXTU			0x02
#define OP_TLBWI			0x02
#define OP_DEXT			0x03
#define OP_SLLV			0x04
#define OP_INS			0x04
#define OP_MSUB			0x04
#define OP_DINSM			0x05
#define OP_MSUBU			0x05
#define OP_SRLV			0x06
#define OP_DINSU			0x06
#define OP_TLBWR			0x06
#define OP_SRAV			0x07
#define OP_DINS			0x07
#define OP_JR				0x08
#define OP_TLBP			0x08
#define OP_JALR			0x09
#define OP_MOVZ			0x0a
#define OP_MOVN			0x0b
#define OP_SYSCALL			0x0c
#define OP_BREAK			0x0d
#define OP_PREFX			0x0f
#define OP_SYNC			0x0f
#define OP_MFHI			0x10
#define OP_MTHI			0x11
#define OP_MFLO			0x12
#define OP_MTLO			0x13
#define OP_DSLLV			0x14
#define OP_DSRLV			0x16
#define OP_DSRAV			0x17
#define OP_MULT			0x18
#define OP_ERET			0x18
#define OP_MULTU			0x19
#define OP_DIV			0x1a
#define OP_DIVU			0x1b
#define OP_DMULT			0x1c
#define OP_DMULTU			0x1d
#define OP_DDIV			0x1e
#define OP_DDIVU			0x1f
#define OP_DERET			0x1f
#define OP_ADD			0x20
#define OP_CLZ			0x20
#define OP_BSHFL			0x20
#define OP_ADDU			0x21
#define OP_CLO			0x21
#define OP_SUB			0x22
#define OP_SUBU			0x23
#define OP_AND			0x24
#define OP_DCLZ			0x24
#define OP_DBSHFL			0x24
#define OP_OR				0x25
#define OP_DCLO			0x25
#define OP_XOR			0x26
#define OP_NOR			0x27
#define OP_SLT			0x2a
#define OP_SLTU			0x2b
#define OP_PCREL		0x2b
#define OP_DADD			0x2c
#define OP_DADDU			0x2d
#define OP_DSUB			0x2e
#define OP_DSUBU			0x2f
#define OP_TGE			0x30
#define OP_TGEU			0x31
#define OP_TLT			0x32
#define OP_TLTU			0x33
#define OP_TEQ			0x34
#define OP_TNE			0x36
#define OP_DSLL			0x38
#define OP_DSRL			0x3a
#define OP_DSRA			0x3b
#define OP_DSLL32			0x3c
#define OP_DSRL32			0x3e
#define OP_AUIPC			0x3e
#define OP_DSRA32			0x3f
#define OP_SDBBP			0x3f

/* lightning uses these, but it's not a complete implementation */
#define _NOP(i0)			Rtype(OP_SPECIAL, 0, 0, 0, 0, OP_SLL)
#define _LUI(rt, i0)			Itype(OP_LUI, 0, rt, i0)
#define _ADDU(rd, rs, rt)		Rtype(OP_SPECIAL, rs, rt, rd, 00, OP_ADDU)
#define _DADDU(rd, rs, rt)		Rtype(OP_SPECIAL, rs, rt, rd, 00, OP_DADDU)
#define _ADDIU(rt, rs, i0)		Itype(OP_ADDIU, rs, rt, i0)
#define _DADDIU(rt, rs, i0)		Itype(OP_DADDIU, rs, rt, i0)
#define _SUBU(rd, rs, rt)		Rtype(OP_SPECIAL, rs, rt, rd, 00, OP_SUBU)
#define _DSUBU(rd, rs, rt)		Rtype(OP_SPECIAL, rs, rt, rd, 00, OP_DSUBU)
#define _MULT(rs, rt)			Rtype(OP_SPECIAL, rs, rt, 00, 00, OP_MULT)
#define _MULTU(rs, rt)			Rtype(OP_SPECIAL, rs, rt, 00, 00, OP_MULTU)
#define _DMULT(rs, rt)			Rtype(OP_SPECIAL, rs, rt, 00, 00, OP_DMULT)
#define _DMULTU(rs, rt)			Rtype(OP_SPECIAL, rs, rt, 00, 00, OP_DMULTU)
#define _DIV(rs, rt)			Rtype(OP_SPECIAL, rs, rt, 00, 00, OP_DIV)
#define _DIVU(rs, rt)			Rtype(OP_SPECIAL, rs, rt, 00, 00, OP_DIVU)
#define _DDIV(rs, rt)			Rtype(OP_SPECIAL, rs, rt, 00, 00, OP_DDIV)
#define _DDIVU(rs, rt)			Rtype(OP_SPECIAL, rs, rt, 00, 00, OP_DDIVU)
#define _SLLV(rd, rt, rs)		Rtype(OP_SPECIAL, rs, rt, rd, 00, OP_SLLV)
#define _SLL(rd, rt, sa)		Rtype(OP_SPECIAL, 00, rt, rd, sa, OP_SLL)
#define _DSLLV(rd, rt, rs)		Rtype(OP_SPECIAL, rs, rt, rd, 00, OP_DSLLV)
#define _DSLL(rd, rt, sa)		Rtype(OP_SPECIAL, 00, rt, rd, sa, OP_DSLL)
#define _DSLL32(rd, rt, sa)		Rtype(OP_SPECIAL, 00, rt, rd, sa, OP_DSLL32)
#define _SRAV(rd, rt, rs)		Rtype(OP_SPECIAL, rs, rt, rd, 00, OP_SRAV)
#define _SRA(rd, rt, sa)		Rtype(OP_SPECIAL, 00, rt, rd, sa, OP_SRA)
#define _SRLV(rd, rt, rs)		Rtype(OP_SPECIAL, rs, rt, rd, 00, OP_SRLV)
#define _SRL(rd, rt, sa)		Rtype(OP_SPECIAL, 00, rt, rd, sa, OP_SRL)
#define _DSRAV(rd, rt, rs)		Rtype(OP_SPECIAL, rs, rt, rd, 00, OP_DSRAV)
#define _DSRA(rd, rt, sa)		Rtype(OP_SPECIAL, 00, rt, rd, sa, OP_DSRA)
#define _DSRA32(rd, rt, sa)		Rtype(OP_SPECIAL, 00, rt, rd, sa, OP_DSRA32)
#define _DSRLV(rd, rt, rs)		Rtype(OP_SPECIAL, rs, rt, rd, 00, OP_DSRLV)
#define _DSRL(rd, rt, sa)		Rtype(OP_SPECIAL, 00, rt, rd, sa, OP_DSRL)
#define _DSRL32(rd, rt, sa)		Rtype(OP_SPECIAL, 00, rt, rd, sa, OP_DSRL32)
#define _INS(rt, rs, pos, size)		Rtype(OP_SPECIAL3, rs, rt, \
						pos + size - 1, pos, 0x04)
#define _DINS(rt, rs, pos, size)	Rtype(OP_SPECIAL3, rs, rt, \
						pos + size - 1, pos, 0x07)
#define _ROTR(rd, rs, sa)		Rtype(OP_SPECIAL, 01, rt, rd, sa, OP_SRL)
#define _DROTR(rd, rs, sa)		Rtype(OP_SPECIAL, 01, rt, rd, sa, OP_DSRL)
#define _MFHI(rd)			Rtype(OP_SPECIAL, 00, 00, rd, 00, OP_MFHI)
#define _MFLO(rd)			Rtype(OP_SPECIAL, 00, 00, rd, 00, OP_MFLO)
#define _MTHI(rs)			Rtype(OP_SPECIAL, rs, 00, 00, 00, OP_MTHI)
#define _MTLO(rs)			Rtype(OP_SPECIAL, rs, 00, 00, 00, OP_MTLO)
#define _AND(rd, rs, rt)		Rtype(OP_SPECIAL, rs, rt, rd, 00, OP_AND)
#define _ANDI(rt, rs, i0)		Itype(OP_ANDI, rs, rt, i0)
#define _OR(rd, rs, rt)			Rtype(OP_SPECIAL, rs, rt, rd, 00, OP_OR)
#define _ORI(rt, rs, i0)		Itype(OP_ORI, rs, rt, i0)
#define _XOR(rd, rs, rt)		Rtype(OP_SPECIAL, rs, rt, rd, 0, OP_XOR)
#define _XORI(rt, rs, i0)		Itype(OP_XORI, rs, rt, i0)
#define _LB(rt, of, bs)			Itype(OP_LB, bs, rt, of)
#define _LBU(rt, of,  bs)		Itype(OP_LBU, bs, rt, of)
#define _LH(rt, of, bs)			Itype(OP_LH, bs, rt, of)
#define _LHU(rt, of, bs)		Itype(OP_LHU, bs, rt, of)
#define _LW(rt, of, bs)			Itype(OP_LW, bs, rt, of)
#define _LWU(rt, of, bs)		Itype(OP_LWU, bs, rt, of)
#define _LD(rt, of, bs)			Itype(OP_LD, bs, rt, of)
#define _SB(rt, of, bs)			Itype(OP_SB, bs, rt, of)
#define _SH(rt, of, bs)			Itype(OP_SH, bs, rt, of)
#define _SW(rt, of, bs)			Itype(OP_SW, bs, rt, of)
#define _SD(rt, of, bs)			Itype(OP_SD, bs, rt, of)
#define _WSBH(rd, rt)			Rtype(OP_SPECIAL3, 00, rt, rd, OP_WSBH, OP_BSHFL)
#define _SEB(rd, rt)			Rtype(OP_SPECIAL3, 00, rt, rd, OP_SEB, OP_BSHFL)
#define _SEH(rd, rt)			Rtype(OP_SPECIAL3, 00, rt, rd, OP_SEH, OP_BSHFL)
#define _SLT(rd, rs, rt)		Rtype(OP_SPECIAL, rs, rt, rd, 00, OP_SLT)
#define _SLTU(rd, rs, rt)		Rtype(OP_SPECIAL, rs, rt, rd, 00, OP_SLTU)
#define _SLTI(rt, rs, i0)		Itype(OP_SLTI, rs, rt, i0)
#define _SLTIU(rt, rs, i0)		Itype(OP_SLTIU, rs, rt, i0)
#define _BLTZ(rs, of)			Itype(OP_REGIMM, rs, OP_BLTZ, of)
#define _BLEZ(rs, of)			Itype(OP_BLEZ, rs, 00, of)
#define _BEQ(rs, rt, of)		Itype(OP_BEQ, rs, rt, of)
#define _BGEZ(rs, of)			Itype(OP_REGIMM, rs, OP_BGEZ, of)
#define _BGTZ(rs, of)			Itype(OP_BGTZ, rs, 00, of)
#define _BNE(rs, rt, of)		Itype(OP_BNE, rs, rt, of)
#define _JALR(rd, rs)			Rtype(OP_SPECIAL, rs, 00, rd, 00, OP_JALR)
#define _JR(rs)				Rtype(OP_SPECIAL, rs, 00, 00, 00, OP_JALR)
#define _J(t)				Jtype(OP_J, t)
#define _MOVZ(rd, rs, rt)		Rtype(OP_SPECIAL, rs, rt, rd, 00, OP_MOVZ)

#define _SDBBP()			Rtype(OP_SPECIAL2, 0, 0, 0, 0, OP_SDBBP)
#define _AUIPC(rs, im)			Itype(OP_PCREL, rs, OP_AUIPC, im)
#define _SYNC(st)			Rtype(OP_SPECIAL, 0, 0, 0, st, OP_SYNC)
/* note: these use pre-release 6 formats, should probably eventually add in some
 * detection */
#define _LL(rt, of, bs)			Itype(OP_LL, bs, rt, of)
#define _LLD(rt, of, bs)		Itype(OP_LLD, bs, rt, of)
#define _SC(rt, of, bs)			Itype(OP_SC, bs, rt, of)
#define _SCD(rt, of, bs)		Itype(OP_SCD, bs, rt, of)

#if __WORDSIZE == 64
#define _WADDR(rd, rs, rt)		_DADDU(rd, rs, rt)
#define _WADDIU(rd, rs, i0)		_DADDIU(rd, rs, i0)
#define	_WSUBR(rd, rs, rt)		_DSUBU(rd, rs, rt)
#define _WMULT(rs, rt)			_DMULT(rs, rt)
#define _WMULTU(rs, rt)			_DMULTU(rs, rt)
#define _WDIV(rs, rt)			_DDIV(rs, rt)
#define _WDIVU(rs, rt)			_DDIVU(rs, rt)
#define _WSLLV(rd, rt, rs)		_DSLLV(rd, rt, rs)
#define _WSRAV(rd, rt, rs)		_DSRAV(rd, rt, rs)
#define _WSRLV(rd, rt, rs)		_DSRLV(rd, rt, rs)
#define _WLD(rt, of, bs)		_LD(rt, of, bs)
#define _WLL(rt, of, bs)		_LLD(rt, of, bs)
#define _WSC(rt, of, bs)		_SCD(rt, of, bs)
#else
#define _WADDR(rd, rs, rt)		_ADDU(rd, rs, rt)
#define _WADDIU(rd, rs, i0)		_ADDIU(rd, rs, i0)
#define _WSUBR(rd, rs, rt)		_SUBU(rd, rs, rt)
#define _WMULT(rs, rt)			_MULT(rs, rt)
#define _WMULTU(rs, rt)			_MULTU(rs, rt)
#define _WDIV(rs, rt)			_DIV(rs, rt)
#define _WDIVU(rs, rt)			_DIVU(rs, rt)
#define _WSLLV(rd, rt, rs)		_SLLV(rd, rt, rs)
#define _WSRAV(rd, rt, rs)		_SRAV(rd, rt, rs)
#define _WSRLV(rd, rt, rs)		_SRLV(rd, rt, rs)
#define _WLD(rt, of, bs)		_LW(rt, of, bs)
#define _WLL(rt, of, bs)		_LL(rt, of, bs)
#define _WSC(rt, of, bs)		_SC(rt, of, bs)
#endif

static void addr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void addi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);
static void addcr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void addci(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);
static void addxr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void addxi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);

static void subr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void subi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);
static void subcr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void subci(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);
static void subxr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void subxi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);

static void mulr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void muli(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);

static void divr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void divi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);
static void divr_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void divi_u(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);

static void remr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void remi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);
static void remr_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void remi_u(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);

static void andr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void andi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);
static void orr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void ori(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);
static void xorr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void xori(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);
static void lshr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void lshi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);
static void rshr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void rshi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);
static void rshr_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void rshi_u(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);

static void qmulr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, int32_t r3);
static void qmulr_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, int32_t r3);
static void qmuli(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, jit_word_t i0);
static void qmuli_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, jit_word_t i0);

static void qdivr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, int32_t r3);
static void qdivr_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, int32_t r3);
static void qdivi(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, jit_word_t i0);
static void qdivi_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, jit_word_t i0);

static void negr(jit_state_t *_jit, int32_t r0, int32_t r1);
static void comr(jit_state_t *_jit, int32_t r0, int32_t r1);

static void movr(jit_state_t *_jit, int32_t r0, int32_t r1);
static void movi(jit_state_t *_jit, int32_t r0, jit_word_t i0);

static jit_reloc_t mov_addr(jit_state_t *_jit, int32_t r0);
static jit_reloc_t movi_from_immediate(jit_state_t *_jit, int32_t r0);
static void emit_immediate_reloc(jit_state_t *_jit, int32_t r0, jit_bool_t in_veneer);

static void extr_c(jit_state_t *_jit, int32_t r0, int32_t r1);
static void extr_uc(jit_state_t *_jit, int32_t r0, int32_t r1);
static void extr_s(jit_state_t *_jit, int32_t r0, int32_t r1);
static void extr_us(jit_state_t *_jit, int32_t r0, int32_t r1);

#if __WORDSIZE == 64
static void extr_i(jit_state_t *_jit, int32_t r0, int32_t r1);
static void extr_ui(jit_state_t *_jit, int32_t r0, int32_t r1);
#endif

static jit_reloc_t bltr(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t blti(jit_state_t *_jit, int32_t r0, jit_word_t i1);
static jit_reloc_t bltr_u(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t blti_u(jit_state_t *_jit, int32_t r0, jit_word_t i1);
static jit_reloc_t bler(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t blei(jit_state_t *_jit, int32_t r0, jit_word_t i1);
static jit_reloc_t bler_u(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t blei_u(jit_state_t *_jit, int32_t r0, jit_word_t i1);
static jit_reloc_t beqr(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t beqi(jit_state_t *_jit, int32_t r0, jit_word_t i1);
static jit_reloc_t bger(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bgei(jit_state_t *_jit, int32_t r0, jit_word_t i1);
static jit_reloc_t bger_u(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bgei_u(jit_state_t *_jit, int32_t r0, jit_word_t i1);
static jit_reloc_t bgtr(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bgti(jit_state_t *_jit, int32_t r0, jit_word_t i1);
static jit_reloc_t bgtr_u(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bgti_u(jit_state_t *_jit, int32_t r0, jit_word_t i1);
static jit_reloc_t bner(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bnei(jit_state_t *_jit, int32_t r0, jit_word_t i1);

static jit_reloc_t bmsr(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bmsi(jit_state_t *_jit, int32_t r0, jit_word_t i1);
static jit_reloc_t bmcr(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bmci(jit_state_t *_jit, int32_t r0, jit_word_t i1);
static jit_reloc_t boaddr(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t boaddi(jit_state_t *_jit, int32_t r0, jit_word_t i1);
static jit_reloc_t boaddr_u(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t boaddi_u(jit_state_t *_jit, int32_t r0, jit_word_t i1);
static jit_reloc_t bxaddr(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bxaddi(jit_state_t *_jit, int32_t r0, jit_word_t i1);
static jit_reloc_t bxaddr_u(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bxaddi_u(jit_state_t *_jit, int32_t r0, jit_word_t i1);
static jit_reloc_t bosubr(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bosubi(jit_state_t *_jit, int32_t r0, jit_word_t i1);
static jit_reloc_t bosubr_u(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bosubi_u(jit_state_t *_jit, int32_t r0, jit_word_t i1);
static jit_reloc_t bxsubr(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bxsubi(jit_state_t *_jit, int32_t r0, jit_word_t i1);
static jit_reloc_t bxsubr_u(jit_state_t *_jit, int32_t r0, int32_t r1);
static jit_reloc_t bxsubi_u(jit_state_t *_jit, int32_t r0, jit_word_t i1);

static void str_c(jit_state_t *_jit, int32_t r0, int32_t r1);
static void str_s(jit_state_t *_jit, int32_t r0, int32_t r1);
static void str_i(jit_state_t *_jit, int32_t r0, int32_t r1);
#if __WORDSIZE == 64
static void str_l(jit_state_t *_jit, int32_t r0, int32_t r1);
#endif

static void sti_c(jit_state_t *_jit, jit_word_t i0, int32_t r0);
static void sti_s(jit_state_t *_jit, jit_word_t i0, int32_t r0);
static void sti_i(jit_state_t *_jit, jit_word_t i0, int32_t r0);
#if __WORDSIZE == 64
static void sti_l(jit_state_t *_jit, jit_word_t i0, int32_t r0);
#endif

static void stxr_c(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void stxr_s(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void stxr_i(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
# if __WORDSIZE == 64
static void stxr_l(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
#endif

static void stxi_c(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1);
static void stxi_s(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1);
static void stxi_i(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1);
# if __WORDSIZE == 64
static void stxi_l(jit_state_t *_jit,jit_word_t i0,int32_t r0,int32_t r1);
# endif

static void ldr_c(jit_state_t *_jit, int32_t r0, int32_t r1);
static void ldr_uc(jit_state_t *_jit, int32_t r0, int32_t r1);
static void ldr_s(jit_state_t *_jit, int32_t r0, int32_t r1);
static void ldr_us(jit_state_t *_jit, int32_t r0, int32_t r1);
static void ldr_i(jit_state_t *_jit, int32_t r0, int32_t r1);
# if __WORDSIZE == 64
static void ldr_ui(jit_state_t *_jit, int32_t r0, int32_t r1);
static void ldr_l(jit_state_t *_jit, int32_t r0, int32_t r1);
# endif

static void ldi_c(jit_state_t *_jit, int32_t r0, jit_word_t i0);
static void ldi_uc(jit_state_t *_jit, int32_t r0, jit_word_t i0);
static void ldi_s(jit_state_t *_jit, int32_t r0, jit_word_t i0);
static void ldi_us(jit_state_t *_jit, int32_t r0, jit_word_t i0);
static void ldi_i(jit_state_t *_jit, int32_t r0, jit_word_t i0);
# if __WORDSIZE == 64
static void ldi_ui(jit_state_t *_jit, int32_t r0, jit_word_t i0);
static void ldi_l(jit_state_t *_jit, int32_t r0, jit_word_t i0);
# endif

static void ldxr_c(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void ldxr_uc(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void ldxr_s(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void ldxr_us(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void ldxr_i(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
#  if __WORDSIZE == 64
static void ldxr_ui(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
static void ldxr_l(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2);
#endif

static void ldxi_c(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);
static void ldxi_uc(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);
static void ldxi_us(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);
static void ldxi_s(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);
static void ldxi_i(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);
#  if __WORDSIZE == 64
static void ldxi_ui(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0);
static void ldxi_l(jit_state_t *_jit,int32_t r0,int32_t r1,jit_word_t i0);
#endif

static void ret(jit_state_t *_jit);
static void retr(jit_state_t *_jit, int32_t r0);
static void reti(jit_state_t *_jit, jit_word_t i0);
static void retval_c(jit_state_t *_jit, int32_t r0);
static void retval_uc(jit_state_t *_jit, int32_t r0);
static void retval_s(jit_state_t *_jit, int32_t r0);
static void retval_us(jit_state_t *_jit, int32_t r0);
static void retval_i(jit_state_t *_jit, int32_t r0);
#  if __WORDSIZE == 64
static void retval_ui(jit_state_t *_jit, int32_t r0);
static void retval_l(jit_state_t *_jit, int32_t r0);
#endif

static uint32_t patch_jump(uint32_t inst, int32_t offset);
static jit_reloc_t emit_jump(jit_state_t *_jit, uint32_t inst);

static void callr(jit_state_t *_jit, int32_t r0);
static void calli(jit_state_t *_jit, jit_word_t i0);
static void jmpi_with_link(jit_state_t *_jit, jit_word_t i0);
static void pop_link_register(jit_state_t *_jit);
static void push_link_register(jit_state_t *_jit);
static void jmpr(jit_state_t *_jit, int32_t r0);
static void jmpi(jit_state_t *_jit, jit_word_t i0);
static jit_reloc_t jmp(jit_state_t *_jit);

static void ldr_atomic(jit_state_t *_jit, int32_t dst, int32_t loc);
static void str_atomic(jit_state_t *_jit, int32_t loc, int32_t val);
static void swap_atomic(jit_state_t *_jit, int32_t dst, int32_t loc,
		int32_t val);
static void cas_atomic(jit_state_t *_jit, int32_t dst, int32_t loc,
		int32_t expected, int32_t desired);

static void bswapr_us(jit_state_t *_jit, int32_t r0, int32_t r1);
static void bswapr_ui(jit_state_t *_jit, int32_t r0, int32_t r1);
#  if __WORDSIZE == 64
static void
bswapr_ul(jit_state_t *_jit, int32_t r0, int32_t r1);
#endif

static void nop(jit_state_t *_jit, int32_t i0);
static void breakpoint(jit_state_t *_jit);

#define rn(x)	jit_gpr_regno(x)

	static void
addr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
	em_wp(_jit, _WADDR(r0, r1, r2));
}

	static void
addi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	if(i0 == 0)
		movr(_jit, r0, r1);
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		movi(_jit, rn(t0), i0);
		em_wp(_jit, _WADDR(r0, r1, rn(t0)));
		unget_temp_gpr(_jit);
	}
}

	static void
addcr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
	if(r0 == r1) {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		em_wp(_jit, _WADDR(rn(t0), r1, r2));
		em_wp(_jit, _SLTU(rn(JIT_CARRY), rn(t0), r1));
		movr(_jit, r0, rn(t0));
		unget_temp_gpr(_jit);
	}
	else {
		em_wp(_jit, _WADDR(r0, r1, r2));
		em_wp(_jit, _SLTU(rn(JIT_CARRY), r0, r1));
	}
}

	static void
addci(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	if (r0 == r1) {
		if (can_sign_extend_short_p(i0))
			em_wp(_jit, _WADDIU(rn(t0), r1, i0));
		else {
			movi(_jit, rn(t0), i0);
			em_wp(_jit, _WADDR(rn(t0), r1, rn(t0)));
		}
		em_wp(_jit, _SLTU(rn(JIT_CARRY), rn(t0), r1));
		movr(_jit, r0, rn(t0));
	}
	else {
		if (can_sign_extend_short_p(i0))
			em_wp(_jit, _WADDIU(r0, r1, i0));
		else {
			movi(_jit, rn(t0), i0);
			em_wp(_jit, _WADDR(r0, r1, rn(t0)));
		}
		em_wp(_jit, _SLTU(rn(JIT_CARRY), r0, r1));
	}

	unget_temp_gpr(_jit);
}

	static void
addxr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movr(_jit, rn(t0), rn(JIT_CARRY));
	addcr(_jit, r0, r1, r2);
	addcr(_jit, r0, r0, rn(t0));
	unget_temp_gpr(_jit);
}

	static void
addxi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movr(_jit, rn(t0), rn(JIT_CARRY));
	addci(_jit, r0, r1, i0);
	addcr(_jit, r0, r0, rn(t0));
	unget_temp_gpr(_jit);
}

	static void
subr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
	em_wp(_jit, _WSUBR(r0, r1, r2));
}

	static void
subi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	if (i0 == 0)
		movr(_jit, r0, r1);
	else if (can_sign_extend_short_p(i0) && (i0 & 0xffff) != 0x8000)
		em_wp(_jit, _WADDIU(r0, r1, -i0));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		movi(_jit, rn(t0), i0);
		em_wp(_jit, _WSUBR(r0, r1, rn(t0)));
		unget_temp_gpr(_jit);
	}
}

	static void
subcr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
	if (r0 == r1) {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		em_wp(_jit, _WSUBR(rn(t0), r1, r2));
		em_wp(_jit, _SLTU(rn(JIT_CARRY), r1, rn(t0)));
		movr(_jit, r0, rn(t0));
		unget_temp_gpr(_jit);
	}
	else {
		em_wp(_jit, _WSUBR(r0, r1, r2));
		em_wp(_jit, _SLTU(rn(JIT_CARRY), r1, r0));
	}
}

	static void
subci(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	if (r0 == r1) {
		if (can_sign_extend_short_p(i0) && (i0 & 0xffff) != 0x8000)
			em_wp(_jit, _WADDIU(rn(t0), r1, -i0));
		else {
			movi(_jit, rn(t0), i0);
			em_wp(_jit, _WSUBR(rn(t0), r1, rn(t0)));
		}
		em_wp(_jit, _SLTU(rn(JIT_CARRY), r1, rn(t0)));
		movr(_jit, r0, rn(t0));
	}
	else {
		if (can_sign_extend_short_p(i0) && (i0 & 0xffff) != 0x8000)
			em_wp(_jit, _WADDIU(r0, r1, -i0));
		else {
			movi(_jit, rn(t0), i0);
			em_wp(_jit, _WSUBR(r0, r1, rn(t0)));
		}
		em_wp(_jit, _SLTU(rn(JIT_CARRY), r1, r0));
	}
	unget_temp_gpr(_jit);
}

	static void
subxr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movr(_jit, rn(t0), rn(JIT_CARRY));
	subcr(_jit, r0, r1, r2);
	subcr(_jit, r0, r0, rn(t0));
	unget_temp_gpr(_jit);
}

	static void
subxi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movr(_jit, rn(t0), rn(JIT_CARRY));
	subci(_jit, r0, r1, i0);
	subcr(_jit, r0, r0, rn(t0));
	unget_temp_gpr(_jit);
}

	static void
mulr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
	em_wp(_jit, _WMULTU(r1, r2));
	em_wp(_jit, _MFLO(r0));
}

	static void
muli(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	mulr(_jit, r0, r1, rn(t0));
	unget_temp_gpr(_jit);
}

	static void
divr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
	em_wp(_jit, _WDIV(r1, r2));
	em_wp(_jit, _MFLO(r0));
}

	static void
divi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	divr(_jit, r0, r1, rn(t0));
	unget_temp_gpr(_jit);
}

	static void
divr_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
	em_wp(_jit, _WDIVU(r1, r2));
	em_wp(_jit, _MFLO(r0));
}

	static void
divi_u(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	divr_u(_jit, r0, r1, rn(t0));
	unget_temp_gpr(_jit);
}

	static void
remr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
	em_wp(_jit, _WDIV(r1, r2));
	em_wp(_jit, _MFHI(r0));
}

	static void
remi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	remr(_jit, r0, r1, rn(t0));
	unget_temp_gpr(_jit);
}

	static void
remr_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
	em_wp(_jit, _WDIVU(r1, r2));
	em_wp(_jit, _MFHI(r0));
}

	static void
remi_u(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	remr_u(_jit, r0, r1, rn(t0));
	unget_temp_gpr(_jit);
}

	static void
lshr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
	em_wp(_jit, _WSLLV(r0, r1, r2));
}

	static void
rshr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
	em_wp(_jit, _WSRAV(r0, r1, r2));
}

	static void
rshr_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
	em_wp(_jit, _WSRLV(r0, r1, r2));
}


#if __WORDSIZE == 64
	static void
lshi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	assert(i0 >= 0 && i0 <= 63);
	if (i0 < 32)
		em_wp(_jit, _DSLL(r0, r1, i0));
	else
		em_wp(_jit, _DSLL32(r0, r1, i0 - 32));
}

	static void
rshi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	assert(i0 >= 0 && i0 <= 63);
	if (i0 < 32)
		em_wp(_jit, _DSRA(r0, r1, i0));
	else
		em_wp(_jit, _DSRA32(r0, r1, i0 - 32));
}

	static void
rshi_u(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	assert(i0 >= 0 && i0 <= 63);
	if (i0 < 32)
		em_wp(_jit, _DSRL(r0, r1, i0));
	else
		em_wp(_jit, _DSRL32(r0, r1, i0 - 32));
}
#else
static void
lshi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	em_wp(_jit, _SLL(r0, r1, i0));
}

	static void
rshi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	em_wp(_jit, _SRA(r0, r1, i0));
}

	static void
rshi_u(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	em_wp(_jit, _SRL(r0, r1, i0));
}
#endif

	static void
iqmulr(jit_state_t *_jit, int32_t r0, int32_t r1,
		int32_t r2, int32_t r3, jit_bool_t sign)
{
	if (sign)
		em_wp(_jit, _WMULT(r2, r3));
	else
		em_wp(_jit, _WMULTU(r2, r3));

	em_wp(_jit, _MFLO(r0));
	em_wp(_jit, _MFHI(r1));
}

	static void
iqmuli(jit_state_t *_jit, int32_t r0, int32_t r1,
		int32_t r2, jit_word_t i0, jit_bool_t sign)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	iqmulr(_jit, r0, r1, r2, rn(t0), sign);
	unget_temp_gpr(_jit);
}

	static void
qmulr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, int32_t r3)
{
	iqmulr(_jit, r0, r1, r2, r3, 1);
}

	static void
qmulr_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, int32_t r3)
{
	iqmulr(_jit, r0, r1, r2, r3, 0);
}

	static void
qmuli(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, jit_word_t i0)
{
	iqmuli(_jit, r0, r1, r2, i0, 1);
}

	static void
qmuli_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, jit_word_t i0)
{
	iqmuli(_jit, r0, r1, r2, i0, 0);
}

	static void
iqdivr(jit_state_t *_jit, int32_t r0, int32_t r1,
		int32_t r2, int32_t r3, jit_bool_t sign)
{
	if (sign)
		em_wp(_jit, _WDIV(r2, r3));
	else
		em_wp(_jit, _WDIVU(r2, r3));

	em_wp(_jit, _MFLO(r0));
	em_wp(_jit, _MFHI(r1));
}

	static void
iqdivi(jit_state_t *_jit, int32_t r0, int32_t r1,
		int32_t r2, jit_word_t i0, jit_bool_t sign)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	iqdivr(_jit, r0, r1, r2, rn(t0), sign);
	unget_temp_gpr(_jit);
}


	static void
qdivr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, int32_t r3)
{
	iqdivr(_jit, r0, r1, r2, r3, 1);
}

	static void
qdivr_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, int32_t r3)
{
	iqdivr(_jit, r0, r1, r2, r3, 0);
}

	static void
qdivi(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, jit_word_t i0)
{
	iqdivi(_jit, r0, r1, r2, i0, 1);
}

	static void
qdivi_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, jit_word_t i0)
{
	iqdivi(_jit, r0, r1, r2, i0, 0);
}

	static void
negr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	subr(_jit, r0, rn(_ZERO), r1);
}

	static void
comr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	xori(_jit, r0, r1, -1);
}

	static void
andr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
	em_wp(_jit, _AND(r0, r1, r2));
}

	static void
andi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	if (can_zero_extend_short_p(i0))
		em_wp(_jit, _ANDI(r0, r1, i0));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		movi(_jit, rn(t0), i0);
		em_wp(_jit, _AND(r0, r1, rn(t0)));
		unget_temp_gpr(_jit);
	}
}

	static void
orr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
	em_wp(_jit, _OR(r0, r1, r2));
}

	static void
ori(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	if (can_zero_extend_short_p(i0))
		em_wp(_jit, _ORI(r0, r1, i0));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		movi(_jit, rn(t0), i0);
		orr(_jit, r0, r1, rn(t0));
		unget_temp_gpr(_jit);
	}
}

	static void
xorr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
	em_wp(_jit, _XOR(r0, r1, r2));
}

	static void
xori(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	if (can_zero_extend_short_p(i0))
		em_wp(_jit, _XORI(r0, r1, i0 & 0xffff));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		movi(_jit, rn(t0), i0);
		xorr(_jit, r0, r1, rn(t0));
		unget_temp_gpr(_jit);
	}
}

	static void
movr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	if(r0 != r1)
		em_wp(_jit, _OR(r0, r1, rn(_ZERO)));
}

	static void
movi(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	if (i0 == 0)
		em_wp(_jit, _OR(r0, rn(_ZERO), rn(_ZERO)));
	else if (can_sign_extend_short_p(i0))
		em_wp(_jit, _WADDIU(r0, rn(_ZERO), i0));
	else if (can_zero_extend_short_p(i0))
		em_wp(_jit, _ORI(r0, rn(_ZERO), i0));
	else {
		if (can_sign_extend_int_p(i0))
			em_wp(_jit, _LUI(r0, i0 >> 16));
		else if (can_zero_extend_int_p(i0)) {
			if (i0 & 0xffff0000) {
				em_wp(_jit, _ORI(r0, rn(_ZERO), (i0 >> 16) & 0xffff));
				lshi(_jit, r0, r0, 16);
			}
		}
#  if __WORDSIZE == 64
		else {
			movi(_jit, r0, (jit_uword_t)i0 >> 32);
			if (i0 & 0xffff0000) {
				lshi(_jit, r0, r0, 16);
				em_wp(_jit, _ORI(r0, r0, (i0 >> 16) & 0xffff));
				lshi(_jit, r0, r0, 16);
			}
			else
				lshi(_jit, r0, r0, 32);
		}
#  endif
		if (i0 & 0xffff)
			em_wp(_jit, _ORI(r0, r0, i0 & 0xffff));
	}
}

typedef struct {
#if __WORDSIZE == 64
	instr_t lui;
	instr_t ori2;
	instr_t dsl1;
	instr_t ori1;
	instr_t dsl0;
#else
	instr_t lui;
#endif
	instr_t ori0;
} immediate_t;

/* TODO: does this work for both BE and LE? */
	static void
patch_immediate_reloc(uint32_t *loc, jit_pointer_t addr)
{
	immediate_t *i = (immediate_t *)loc;
	jit_word_t a = (jit_word_t)addr;
#if __WORDSIZE == 64
	i->lui.I.i0 = a >> 48;
	i->ori2.I.i0 = a >> 32;
	i->ori1.I.i0 = a >> 16;
#else
	i->lui.I.i0 = a >> 16;
#endif
	i->ori0.I.i0 = a & 0xffff;
}

	static void
emit_immediate_reloc(jit_state_t *_jit, int32_t r0, jit_bool_t in_veneer)
{
	void (*emit)(jit_state_t *_jit, uint32_t u32) =
		in_veneer ? emit_u32 : emit_u32_with_pool;

#if __WORDSIZE == 64
	emit(_jit, _LUI(r0, 0));
	emit(_jit, _ORI(r0, r0, 0));
	emit(_jit, _DSLL(r0, r0, 16));
	emit(_jit, _ORI(r0, r0, 0));
	emit(_jit, _DSLL(r0, r0, 16));
#else
	emit(_jit, _LUI(r0, 0));
#endif
	emit(_jit, _ORI(r0, r0, 0));
}

	static jit_reloc_t
movi_from_immediate(jit_state_t *_jit, int32_t r0)
{
	uint8_t *pc_base = _jit->pc.uc;
	jit_reloc_t w = jit_reloc(_jit, JIT_RELOC_IMMEDIATE, 0, _jit->pc.uc, pc_base, 0);
	emit_immediate_reloc(_jit, r0, 0);

	return w;
}

	static jit_reloc_t
mov_addr(jit_state_t *_jit, int32_t r0)
{
	return movi_from_immediate(_jit, r0);
}

	static void
ldr_c(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	em_wp(_jit, _LB(r0, 0, r1));
}

	static void
ldr_uc(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	em_wp(_jit, _LBU(r0, 0, r1));
}

	static void
ldr_s(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	em_wp(_jit, _LH(r0, 0, r1));
}

	static void
ldr_us(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	em_wp(_jit, _LHU(r0, 0, r1));
}

	static void
ldr_i(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	em_wp(_jit, _LW(r0, 0, r1));
}

#if __WORDSIZE == 64
	static void
ldr_ui(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	em_wp(_jit, _LWU(r0, 0, r1));
}

	static void
ldr_l(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	em_wp(_jit, _LD(r0, 0, r1));
}
#endif

	static void
ldi_c(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _LB(r0, i0, rn(_ZERO)));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		movi(_jit, rn(t0), i0);
		ldr_c(_jit, r0, rn(t0));
		unget_temp_gpr(_jit);
	}
}

	static void
ldi_uc(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _LBU(r0, i0, rn(_ZERO)));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		movi(_jit, rn(t0), i0);
		ldr_uc(_jit, r0, rn(t0));
		unget_temp_gpr(_jit);
	}
}

	static void
ldi_s(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _LH(r0, i0, rn(_ZERO)));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		movi(_jit, rn(t0), i0);
		ldr_s(_jit, r0, rn(t0));
		unget_temp_gpr(_jit);
	}
}

	static void
ldi_us(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _LHU(r0, i0, rn(_ZERO)));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		movi(_jit, rn(t0), i0);
		ldr_us(_jit, r0, rn(t0));
		unget_temp_gpr(_jit);
	}
}

	static void
ldi_i(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _LW(r0, i0, rn(_ZERO)));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		movi(_jit, rn(t0), i0);
		ldr_i(_jit, r0, rn(t0));
		unget_temp_gpr(_jit);
	}
}

#if __WORDSIZE == 64
	static void
ldi_ui(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _LWU(r0, i0, rn(_ZERO)));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		movi(_jit, rn(t0), i0);
		ldr_ui(_jit, r0, rn(t0));
		unget_temp_gpr(_jit);
	}
}

	static void
ldi_l(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _LD(r0, i0, rn(_ZERO)));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		movi(_jit, rn(t0), i0);
		ldr_l(_jit, r0, rn(t0));
		unget_temp_gpr(_jit);
	}
}
#endif

	static void
ldxr_c(jit_state_t *_jit, int32_t r0, int32_t r1 ,int32_t r2)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	em_wp(_jit, _WADDR(rn(t0), r1, r2));
	ldr_c(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);
}

	static void
ldxi_c(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _LB(r0, i0, r1));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		addi(_jit, rn(t0), r1, i0);
		ldr_c(_jit, r0, rn(t0));
		unget_temp_gpr(_jit);
	}
}

	static void
ldxr_uc(jit_state_t *_jit, int32_t r0, int32_t r1 ,int32_t r2)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	em_wp(_jit, _WADDR(rn(t0), r1, r2));
	ldr_uc(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);
}

	static void
ldxi_uc(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _LBU(r0, i0, r1));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		addi(_jit, rn(t0), r1, i0);
		ldr_uc(_jit, r0, rn(t0));
		unget_temp_gpr(_jit);
	}
}

	static void
ldxr_s(jit_state_t *_jit, int32_t r0, int32_t r1 ,int32_t r2)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	em_wp(_jit, _WADDR(rn(t0), r1, r2));
	ldr_s(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);
}

	static void
ldxi_s(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _LH(r0, i0, r1));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		addi(_jit, rn(t0), r1, i0);
		ldr_s(_jit, r0, rn(t0));
		unget_temp_gpr(_jit);
	}
}

	static void
ldxr_us(jit_state_t *_jit, int32_t r0, int32_t r1 ,int32_t r2)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	em_wp(_jit, _WADDR(rn(t0), r1, r2));
	ldr_us(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);
}

	static void
ldxi_us(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _LHU(r0, i0, r1));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		addi(_jit, rn(t0), r1, i0);
		ldr_us(_jit, r0, rn(t0));
		unget_temp_gpr(_jit);
	}
}

	static void
ldxr_i(jit_state_t *_jit, int32_t r0, int32_t r1 ,int32_t r2)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	em_wp(_jit, _WADDR(rn(t0), r1, r2));
	ldr_i(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);
}

	static void
ldxi_i(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _LW(r0, i0, r1));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		addi(_jit, rn(t0), r1, i0);
		ldr_i(_jit, r0, rn(t0));
		unget_temp_gpr(_jit);
	}
}

#if __WORDSIZE == 64
	static void
ldxr_ui(jit_state_t *_jit, int32_t r0, int32_t r1 ,int32_t r2)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	em_wp(_jit, _WADDR(rn(t0), r1, r2));
	ldr_ui(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);
}

	static void
ldxi_ui(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _LWU(r0, i0, r1));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		addi(_jit, rn(t0), r1, i0);
		ldr_ui(_jit, r0, rn(t0));
		unget_temp_gpr(_jit);
	}
}

	static void
ldxr_l(jit_state_t *_jit, int32_t r0, int32_t r1 ,int32_t r2)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	em_wp(_jit, _WADDR(rn(t0), r1, r2));
	ldr_l(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);
}

	static void
ldxi_l(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _LD(r0, i0, r1));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		addi(_jit, rn(t0), r1, i0);
		ldr_l(_jit, r0, rn(t0));
		unget_temp_gpr(_jit);
	}
}
#endif

	static void
str_c(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	em_wp(_jit, _SB(r1, 0, r0));
}

	static void
str_s(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	em_wp(_jit, _SH(r1, 0, r0));
}

	static void
str_i(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	em_wp(_jit, _SW(r1, 0, r0));
}

#if __WORDSIZE == 64
	static void
str_l(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	em_wp(_jit, _SD(r1, 0, r0));
}
#endif

	static void
sti_c(jit_state_t *_jit, jit_word_t i0, int32_t r0)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _SB(r0, i0, rn(_ZERO)));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		movi(_jit, rn(t0), i0);
		str_c(_jit, rn(t0), r0);
		unget_temp_gpr(_jit);
	}
}

	static void
sti_s(jit_state_t *_jit, jit_word_t i0, int32_t r0)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _SH(r0, i0, rn(_ZERO)));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		movi(_jit, rn(t0), i0);
		str_s(_jit, rn(t0), r0);
		unget_temp_gpr(_jit);
	}
}

	static void
sti_i(jit_state_t *_jit, jit_word_t i0, int32_t r0)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _SW(r0, i0, rn(_ZERO)));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		movi(_jit, rn(t0), i0);
		str_i(_jit, rn(t0), r0);
		unget_temp_gpr(_jit);
	}
}

#if __WORDSIZE == 64
	static void
sti_l(jit_state_t *_jit, jit_word_t i0, int32_t r0)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _SD(r0, i0, rn(_ZERO)));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		movi(_jit, rn(t0), i0);
		str_l(_jit, rn(t0), r0);
		unget_temp_gpr(_jit);
	}
}
#endif

	static void
stxr_c(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	em_wp(_jit, _WADDR(rn(t0), r0, r1));
	str_c(_jit, rn(t0), r2);
	unget_temp_gpr(_jit);
}

	static void
stxi_c(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _SB(r1, i0, r0));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		addi(_jit, rn(t0), r0, i0);
		str_c(_jit, rn(t0), r1);
		unget_temp_gpr(_jit);
	}
}

	static void
stxr_s(jit_state_t *_jit, int32_t r0, int32_t r1 ,int32_t r2)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	em_wp(_jit, _WADDR(rn(t0), r0, r1));
	str_s(_jit, rn(t0), r2);
	unget_temp_gpr(_jit);
}

	static void
stxi_s(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _SH(r1, i0, r0));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		addi(_jit, rn(t0), r0, i0);
		str_s(_jit, rn(t0), r1);
		unget_temp_gpr(_jit);
	}
}

	static void
stxr_i(jit_state_t *_jit, int32_t r0, int32_t r1 ,int32_t r2)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	em_wp(_jit, _WADDR(rn(t0), r0, r1));
	str_i(_jit, rn(t0), r2);
	unget_temp_gpr(_jit);
}

	static void
stxi_i(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _SW(r1, i0, r0));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		addi(_jit, rn(t0), r0, i0);
		str_i(_jit, rn(t0), r1);
		unget_temp_gpr(_jit);
	}
}

#if __WORDSIZE == 64
	static void
stxr_l(jit_state_t *_jit, int32_t r0, int32_t r1 ,int32_t r2)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	em_wp(_jit, _WADDR(rn(t0), r0, r1));
	str_l(_jit, rn(t0), r2);
	unget_temp_gpr(_jit);
}

	static void
stxi_l(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
	if (can_sign_extend_short_p(i0))
		em_wp(_jit, _SD(r1, i0, r0));
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		addi(_jit, rn(t0), r0, i0);
		str_l(_jit, rn(t0), r1);
		unget_temp_gpr(_jit);
	}
}
#endif

	static void
bswapr_us(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	rshi(_jit, rn(t0), r1, 8);
	andi(_jit, r0, r1, 0xff);
	andi(_jit, rn(t0), rn(t0), 0xff);
	lshi(_jit, r0, r0, 8);
	orr(_jit, r0, r0, rn(t0));
	unget_temp_gpr(_jit);
}

	static void
bswapr_ui(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	jit_gpr_t t1 = get_temp_gpr(_jit);
	jit_gpr_t t2 = get_temp_gpr(_jit);
	rshi(_jit, rn(t0), r1, 24);
	rshi(_jit, rn(t1), r1, 16);
	rshi(_jit, rn(t2), r1,  8);
	andi(_jit, rn(t0), rn(t0), 0xff);
	andi(_jit, rn(t1), rn(t1), 0xff);
	andi(_jit, rn(t2), rn(t2), 0xff);
	andi(_jit, r0, r1, 0xff);
	lshi(_jit, r0, r0, 24);
	lshi(_jit, rn(t1), rn(t1), 8);
	orr(_jit, r0, r0, rn(t0));
	lshi(_jit, rn(t2), rn(t2), 16);
	orr(_jit, r0, r0, rn(t1));
	orr(_jit, r0, r0, rn(t2));
	unget_temp_gpr(_jit);
	unget_temp_gpr(_jit);
	unget_temp_gpr(_jit);
}

#if __WORDSIZE == 64
	static void
bswapr_ul(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	rshi_u(_jit, rn(t0), r1, 32);
	bswapr_ui(_jit, r0, r1);
	bswapr_ui(_jit, rn(t0), rn(t0));
	lshi(_jit, r0, r0, 32);
	orr(_jit, r0, r0, rn(t0));
	unget_temp_gpr(_jit);
}
#endif

	static void
extr_uc(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	em_wp(_jit, _ANDI(r0, r1, 0xff));
}

	static void
extr_us(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	em_wp(_jit, _ANDI(r0, r1, 0xffff));
}

	static void
extr_c(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	if (jit_mips2_p())
		em_wp(_jit, _SEB(r0, r1));
	else {
		lshi(_jit, r0, r1, __WORDSIZE - 8);
		rshi(_jit, r0, r0, __WORDSIZE - 8);
	}
}

	static void
extr_s(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	if (jit_mips2_p())
		em_wp(_jit, _SEH(r0, r1));
	else {
		lshi(_jit, r0, r1, __WORDSIZE - 16);
		rshi(_jit, r0, r0, __WORDSIZE - 16);
	}
}

#  if __WORDSIZE == 64
	static void
extr_i(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	em_wp(_jit, _SLL(r0, r1, 0));
}

	static void
extr_ui(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	lshi(_jit, r0, r1, 32);
	rshi_u(_jit, r0, r0, 32);
}
#  endif


	static jit_reloc_t
bltr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	em_wp(_jit, _SLT(rn(t0), r0, r1));
	jit_reloc_t w = emit_jump(_jit, _BNE(rn(t0), rn(_ZERO), 0));
	em_wp(_jit, _NOP(1));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bltr_u(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	em_wp(_jit, _SLTU(rn(t0), r0, r1));
	jit_reloc_t w = emit_jump(_jit, _BNE(rn(t0), rn(_ZERO), 0));
	em_wp(_jit, _NOP(1));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
blti(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	jit_reloc_t w = bltr(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
blti_u(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	jit_reloc_t w = bltr_u(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bler(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	return bger(_jit, r1, r0);
}

	static jit_reloc_t
bler_u(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	return bger_u(_jit, r1, r0);
}

	static jit_reloc_t
blei(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	jit_reloc_t w = bler(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
blei_u(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	jit_reloc_t w = bler_u(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
beqr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	jit_reloc_t w = emit_jump(_jit, _BEQ(r0, r1, 0));
	em_wp(_jit, _NOP(1));
	return w;
}

	static jit_reloc_t
beqi(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	jit_reloc_t w = beqr(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bger(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	em_wp(_jit, _SLT(rn(t0), r0, r1));
	jit_reloc_t w = beqr(_jit, rn(t0), rn(_ZERO));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bger_u(jit_state_t *_jit, int32_t r0, int32_t r1)

{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	em_wp(_jit, _SLTU(rn(t0), r0, r1));
	jit_reloc_t w = beqr(_jit, rn(t0), rn(_ZERO));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bgei(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	jit_reloc_t w = bger(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bgei_u(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	jit_reloc_t w = bger_u(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bgtr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	return bltr(_jit, r1, r0);
}

	static jit_reloc_t
bgtr_u(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	return bltr_u(_jit, r1, r0);
}

	static jit_reloc_t
bgti(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	jit_reloc_t w = bgtr(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bgti_u(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	jit_reloc_t w = bgtr_u(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bner(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	jit_reloc_t w = emit_jump(_jit, _BNE(r0, r1, 0));
	em_wp(_jit, _NOP(1));

	return (w);
}

	static jit_reloc_t
bnei(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	jit_reloc_t w = bner(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);

	return (w);
}

static int32_t
read_jmp_offset(uint32_t *loc)
{
	instr_t *i = (instr_t *)loc;
	return (i->I.i0 + 1) << 2;
}

static int32_t
read_jcc_offset(uint32_t *loc)
{
	return read_jmp_offset(loc);
}

static void
patch_jmp_offset(uint32_t *loc, ptrdiff_t offset)
{
	assert(!(offset & 0x3));
	instr_t *i = (instr_t *)loc;
	i->I.i0 = (offset >> 2) - 1;
}

static void
patch_jcc_offset(uint32_t *loc, ptrdiff_t offset)
{
	patch_jmp_offset(loc, offset);
}

static void
patch_veneer_jmp_offset(uint32_t *loc, ptrdiff_t offset)
{
	patch_jmp_offset(loc, offset);
}

static void
patch_veneer(uint32_t *loc, jit_pointer_t addr)
{
	patch_immediate_reloc(loc, addr);
}

static void
emit_veneer(jit_state_t *_jit, jit_pointer_t target)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	emit_immediate_reloc(_jit, rn(t0), 1);
	patch_veneer(jit_address(_jit), target);
	emit_u32(_jit, _JR(rn(t0)));
	unget_temp_gpr(_jit);
}

static void
patch_veneer_jcc_offset(uint32_t *loc, ptrdiff_t offset)
{
	patch_jcc_offset(loc, offset);
}

static int
offset_in_jmp_range(ptrdiff_t offset, int flags)
{
	(void)flags;

	if(offset & 0x3)
		return 0;
	else
		return simm18_p(offset);
}

static int
offset_in_jcc_range(ptrdiff_t offset, int flags)
{
	return offset_in_jmp_range(offset, flags);
}

	static uint32_t
patch_jump(uint32_t inst, int32_t offset)
{
	assert(!(offset & 0x3));
	instr_t i;
	i.w = inst;
	i.I.i0 = (offset >> 2) - 1;
	return i.w;
}

	static jit_reloc_t
emit_jump(jit_state_t *_jit, uint32_t inst)
{
	while(1){
		uint8_t *pc_base = _jit->pc.uc;
		int32_t off = (uint8_t *)jit_address(_jit) - pc_base;
		jit_reloc_t w =
			jit_reloc(_jit, JIT_RELOC_JMP_WITH_VENEER, 0, _jit->pc.uc, pc_base, 0);
		uint8_t jump_width = 18;
		if(add_pending_literal(_jit, w, jump_width - 1)){
			em_wp(_jit, patch_jump(inst, off));
			return w;
		}
	}
}

	static void
jmpr(jit_state_t *_jit, int32_t r0)
{
	em_wp(_jit, _JR(r0));
	em_wp(_jit, _NOP(1));
}

	static void
jmpi_with_link(jit_state_t *_jit, jit_word_t i0)
{
	calli(_jit, i0);
}

	static void
jmpi(jit_state_t *_jit, jit_word_t i0)
{
	if (((_jit->pc.w + sizeof(int32_t)) & 0xf0000000) == (i0 & 0xf0000000)) {
		em_wp(_jit, _J((i0 & ~0xf0000000) >> 2));
		em_wp(_jit, _NOP(1));
	}
	else {
		jit_gpr_t t0 = get_temp_gpr(_jit);
		movi(_jit, rn(t0), i0);
		jmpr(_jit, rn(t0));
		unget_temp_gpr(_jit);
	}
}

	static void
pop_link_register(jit_state_t *_jit)
{
	(void)_jit; /* unused */
}

	static void
push_link_register(jit_state_t *_jit)
{
	(void)_jit; /* unused */
}

	static jit_reloc_t
jmp(jit_state_t *_jit)
{
	/* BEQ works as unconditional jump in this case, J and the like aren't
	 * PC relative */
	jit_reloc_t w = emit_jump(_jit, _BEQ(rn(_ZERO), rn(_ZERO), 0));
	em_wp(_jit, _NOP(1));

	return (w);
}

	static jit_reloc_t
boaddr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	/* t1 = r0 + r1;	overflow = r1 < 0 ? r0 < t1 : t1 < r0 */
	jit_gpr_t t0 = get_temp_gpr(_jit);
	jit_gpr_t t1 = get_temp_gpr(_jit);
	jit_gpr_t t2 = get_temp_gpr(_jit);

	em_wp(_jit, _SLT(rn(t0), r1, rn(_ZERO)));

	addr(_jit, rn(t1), r0, r1);

	em_wp(_jit, _SLT(rn(t2), rn(t1), r0));
	em_wp(_jit, _SLT(rn(t1), r0, rn(t1)));
	em_wp(_jit, _MOVZ(rn(t1), rn(t2), rn(t0)));
	jit_reloc_t w = emit_jump(_jit, _BNE(rn(_ZERO), rn(t1), 0));
	/* delay slot */
	addr(_jit, r0, r0, r1);

	unget_temp_gpr(_jit);
	unget_temp_gpr(_jit);
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
boaddi(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	jit_reloc_t w = boaddr(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
boaddr_u(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	jit_gpr_t t1 = get_temp_gpr(_jit);

	addr(_jit, rn(t0), r0, r1);

	em_wp(_jit, _SLTU(rn(t1), rn(t0), r0));
	jit_reloc_t w = emit_jump(_jit, _BNE(rn(_ZERO), rn(t1), 0));
	/* delay slot */
	movr(_jit, r0, rn(t0));

	unget_temp_gpr(_jit);
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
boaddi_u(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	jit_reloc_t w = boaddr_u(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bxaddr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	/* t1 = r0 + r1;	overflow = r1 < 0 ? r0 < t1 : t1 < r0 */
	jit_gpr_t t0 = get_temp_gpr(_jit);
	jit_gpr_t t1 = get_temp_gpr(_jit);
	jit_gpr_t t2 = get_temp_gpr(_jit);

	addr(_jit, rn(t0), r0, r1);
	em_wp(_jit, _SLTI(rn(t1), r1, 0));
	em_wp(_jit, _SLT(rn(t2), rn(t0), r0));
	jit_reloc_t w = emit_jump(_jit, _BEQ(rn(t1), rn(t2), 0));
	/* delay slot */
	movr(_jit, r0, rn(t0));

	unget_temp_gpr(_jit);
	unget_temp_gpr(_jit);
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bxaddi(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	jit_reloc_t w = bxaddr(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bxaddr_u(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	jit_gpr_t t1 = get_temp_gpr(_jit);

	addr(_jit, rn(t0), r0, r1);

	em_wp(_jit, _SLTU(rn(t1), rn(t0), r0));
	jit_reloc_t w = emit_jump(_jit, _BEQ(rn(_ZERO), rn(t1), 0));
	/* delay slot */
	movr(_jit, r0, rn(t0));

	unget_temp_gpr(_jit);
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bxaddi_u(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	jit_reloc_t w = bxaddr_u(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bosubr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	/* t1 = r0 - r1;	overflow = 0 < r1 ? r0 < t1 : t1 < r0 */
	jit_gpr_t t0 = get_temp_gpr(_jit);
	jit_gpr_t t1 = get_temp_gpr(_jit);
	jit_gpr_t t2 = get_temp_gpr(_jit);

	subr(_jit, rn(t0), r0, r1);

	em_wp(_jit, _SLTI(rn(t1), r1, 0));
	em_wp(_jit, _SLT(rn(t2), r0, rn(t0)));
	jit_reloc_t w = emit_jump(_jit, _BNE(rn(t1), rn(t2), 0));
	/* delay slot */
	movr(_jit, r0, rn(t0));

	unget_temp_gpr(_jit);
	unget_temp_gpr(_jit);
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bosubi(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	jit_reloc_t w = bosubr(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bosubr_u(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	jit_gpr_t t1 = get_temp_gpr(_jit);

	subr(_jit, rn(t0), r0, r1);

	em_wp(_jit, _SLTU(rn(t1), r0, rn(t0)));
	jit_reloc_t w = emit_jump(_jit, _BNE(rn(_ZERO), rn(t1), 0));
	/* delay slot */
	movr(_jit, r0, rn(t0));

	unget_temp_gpr(_jit);
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bosubi_u(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	jit_reloc_t w = bosubr_u(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bxsubr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	jit_gpr_t t1 = get_temp_gpr(_jit);
	jit_gpr_t t2 = get_temp_gpr(_jit);

	subr(_jit, rn(t0), r0, r1);

	em_wp(_jit, _SLTI(rn(t1), r1, 0));
	em_wp(_jit, _SLT(rn(t2), r0, rn(t0)));
	jit_reloc_t w = emit_jump(_jit, _BEQ(rn(t1), rn(t2), 0));
	/* delay slot */
	movr(_jit, r0, rn(t0));

	unget_temp_gpr(_jit);
	unget_temp_gpr(_jit);
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bxsubi(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	jit_reloc_t w = bxsubr(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bxsubr_u(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	jit_gpr_t t1 = get_temp_gpr(_jit);

	subr(_jit, rn(t0), r0, r1);

	em_wp(_jit, _SLTU(rn(t1), r0, rn(t0)));
	jit_reloc_t w = emit_jump(_jit, _BEQ(rn(_ZERO), rn(t1), 0));
	/* delay slot */
	movr(_jit, r0, rn(t0));

	unget_temp_gpr(_jit);
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bxsubi_u(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	jit_reloc_t w = bxsubr_u(_jit, r0, rn(t0));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bmsr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	andr(_jit, rn(t0), r0, r1);
	jit_reloc_t w = bner(_jit, rn(t0), rn(_ZERO));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bmsi(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	andi(_jit, rn(t0), r0, i0);
	jit_reloc_t w = bner(_jit, rn(t0), rn(_ZERO));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bmcr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	andr(_jit, rn(t0), r0, r1);
	jit_reloc_t w = beqr(_jit, rn(t0), rn(_ZERO));
	unget_temp_gpr(_jit);

	return (w);
}

	static jit_reloc_t
bmci(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	andi(_jit, rn(t0), r0, i0);
	jit_reloc_t w = beqr(_jit, rn(t0), rn(_ZERO));
	unget_temp_gpr(_jit);

	return (w);
}

	static void
callr(jit_state_t *_jit, int32_t r0)
{
	/*
	   if (r0 != _T9_REGNO)
	   movr(_T9_REGNO, r0);
	   */

	em_wp(_jit, _JALR(rn(_RA), r0));
	em_wp(_jit, _NOP(1));
}

	static void
calli(jit_state_t *_jit, jit_word_t i0)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	movi(_jit, rn(t0), i0);
	em_wp(_jit, _JALR(rn(_RA), rn(t0)));
	em_wp(_jit, _NOP(1));
	unget_temp_gpr(_jit);
}

	static void
ret(jit_state_t *_jit)
{
	em_wp(_jit, _JALR(rn(_ZERO), rn(_RA)));
	em_wp(_jit, _NOP(1));
}

	static void
retr(jit_state_t *_jit, int32_t r0)
{
	if(r0 != rn(_V0))
		movr(_jit, rn(_V0), r0);

	ret(_jit);
}

	static void
reti(jit_state_t *_jit, jit_word_t i0)
{
	movi(_jit, rn(_V0), i0);
	ret(_jit);
}

	static void
retval_c(jit_state_t *_jit, int32_t r0)
{
	extr_c(_jit, r0, rn(_V0));
}

	static void
retval_uc(jit_state_t *_jit, int32_t r0)
{
	extr_uc(_jit, r0, rn(_V0));
}

	static void
retval_s(jit_state_t *_jit, int32_t r0)
{
	extr_s(_jit, r0, rn(_V0));
}

	static void
retval_us(jit_state_t *_jit, int32_t r0)
{
	extr_us(_jit, r0, rn(_V0));
}

	static void
retval_i(jit_state_t *_jit, int32_t r0)
{
#if __WORDSIZE == 64
	extr_i(_jit, r0, rn(_V0));
#else
	if(r0 != rn(_V0))
		movr(_jit, r0, rn(_V0));
#endif
}

#if __WORDSIZE == 64
	static void
retval_ui(jit_state_t *_jit, int32_t r0)
{
	extr_ui(_jit, r0, rn(_V0));
}

	static void
retval_l(jit_state_t *_jit, int32_t r0)
{
	if(r0 != rn(_V0))
		movr(_jit, r0, rn(_V0));
}
#endif

	static void
ldr_atomic(jit_state_t *_jit, int32_t dst, int32_t loc)
{
	em_wp(_jit, _SYNC(0x00));
	ldr_i(_jit, dst, loc);
	em_wp(_jit, _SYNC(0x00));
}

	static void
str_atomic(jit_state_t *_jit, int32_t loc, int32_t val)
{
	em_wp(_jit, _SYNC(0x00));
	str_i(_jit, loc, val);
	em_wp(_jit, _SYNC(0x00));
}

	static void
swap_atomic(jit_state_t *_jit, int32_t dst, int32_t loc, int32_t val)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);

	em_wp(_jit, _SYNC(0x00));

	void *retry = jit_address(_jit);
	movr(_jit, rn(t0), val);
	em_wp(_jit, _WLL(dst, loc, 0));
	em_wp(_jit, _WSC(rn(t0), loc, 0));
	jit_patch_there(_jit, bner(_jit, rn(t0), rn(_ZERO)), retry);

	em_wp(_jit, _SYNC(0x00));

	unget_temp_gpr(_jit);
}

	static void
cas_atomic(jit_state_t *_jit, int32_t dst, int32_t loc, int32_t expected,
		int32_t desired)
{
	jit_gpr_t t0 = get_temp_gpr(_jit);
	jit_gpr_t t1 = get_temp_gpr(_jit);

	void *retry = jit_address(_jit);

	em_wp(_jit, _WLL(rn(t0), 0, loc));
	jit_reloc_t fail = bner(_jit, rn(t0), expected);
	em_wp(_jit, _WSC(rn(t1), desired, loc));

	jit_patch_there(_jit, bner(_jit, rn(t1), rn(_ZERO)), retry);
	jit_patch_here(_jit, fail);
	em_wp(_jit, _SYNC(0x00));

	movr(_jit, dst, rn(t0));

	unget_temp_gpr(_jit);
	unget_temp_gpr(_jit);
}

	static void
nop(jit_state_t *_jit, int32_t i0)
{
	for(; i0 > 0; i0 -= 4)
		em_wp(_jit, _NOP());

	assert(i0 == 0);
}

	static void
breakpoint(jit_state_t *_jit)
{
	/* interesting, Linux on qemu-system-mips64el 6.1.0 crashes when executing a breakpoint? */
	em_wp(_jit, _SDBBP());
}
