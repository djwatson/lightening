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

# define fn(x) jit_fpr_regno(x)

#define _FA(o,d,a,b,c,x)		FA(o,d,a,b,c,x,0)
#define _FA_(o,d,a,b,c,x)		FA(o,d,a,b,c,x,1)
static uint32_t FA(int,int,int,int,int,int,int);

#define _FXFL(o,m,b,x)			FXFL(o,m,b,x,0)
#define _FXFL_(o,m,b,x)			FXFL(o,m,b,x,1)
static uint32_t FXFL(int,int,int,int,int) maybe_unused;

#  define _FABS(d,b)			_FX(63,d,0,b,264)
#  define _FABS_(d,b)			_FX_(63,d,0,b,264)
#  define _FADD(d,a,b)			_FA(63,d,a,b,0,21)
#  define _FADD_(d,a,b)			_FA_(63,d,a,b,0,21)
#  define _FADDS(d,a,b)			_FA(59,d,a,b,0,21)
#  define _FADDS_(d,a,b)		_FA_(59,d,a,b,0,21)
#  define _FCFID(d,b)			_FX(63,d,0,b,846)
#  define _FCMPO(cr,a,b)		_FC(63,cr,0,a,b,32)
#  define _FCMPU(cr,a,b)    		_FC(63,cr,0,a,b,0)
#  define _FCTIW(d,b)			_FX(63,d,0,b,14)
#  define _FCTIW_(d,b)			_FX_(63,d,0,b,14)
#  define _FCTIWZ(d,b)			_FX(63,d,0,b,15)
#  define _FCTIWZ_(d,b)			_FX_(63,d,0,b,15)
#  define _FCTID(d,b)			_FX(63,d,0,b,814)
#  define _FCTID_(d,b)			_FX_(63,d,0,b,814)
#  define _FCTIDZ(d,b)			_FX(63,d,0,b,815)
#  define _FCTIDZ_(d,b)			_FX_(63,d,0,b,815)
#  define _FDIV(d,a,b)			_FA(63,d,a,b,0,18)
#  define _FDIV_(d,a,b)			_FA_(63,d,a,b,0,18)
#  define _FDIVS(d,a,b)			_FA(59,d,a,b,0,18)
#  define _FDIVS_(d,a,b)    		_FA_(59,d,a,b,0,18)
#  define _FMADD(d,a,b,c)		_FA(63,d,a,b,c,29)
#  define _FMADD_(d,a,b,c)		_FA(63,d,a,b,c,29)
#  define _FMADDS(d,a,b,c)		_FA(59,d,a,b,c,29)
#  define _FMADDS_(d,a,b,c)		_FA(59,d,a,b,c,29)
#  define _FMR(d,b)			_FX(63,d,0,b,72)
#  define _FMR_(d,b)			_FX_(63,d,0,b,72)
#  define _FMSUB(d,a,b,c)		_FA(63,d,a,b,c,28)
#  define _FMSUB_(d,a,b,c)		_FA(63,d,a,b,c,28)
#  define _FMSUBS(d,a,b,c)		_FA(59,d,a,b,c,28)
#  define _FMSUBS_(d,a,b,c)		_FA(59,d,a,b,c,28)
#  define _FMUL(d,a,c)			_FA(63,d,a,0,c,25)
#  define _FMUL_(d,a,c)			_FA_(63,d,a,0,c,25)
#  define _FMULS(d,a,c)			_FA(59,d,a,0,c,25)
#  define _FMULS_(d,a,c)    		_FA_(59,d,a,0,c,25)
#  define _FNABS(d,b)			_FX(63,d,0,b,136)
#  define _FNABS_(d,b)			_FX_(63,d,0,b,136)
#  define _FNEG(d,b)			_FX(63,d,0,b,40)
#  define _FNEG_(d,b)			_FX_(63,d,0,b,40)
#  define _FNMADD(d,a,b,c)		_FA(63,d,a,b,c,31)
#  define _FNMADD_(d,a,b,c)		_FA_(63,d,a,b,c,31)
#  define _FNMADDS(d,a,b,c)		_FA(59,d,a,b,c,31)
#  define _FNMADDS_(d,a,b,c)		_FA_(59,d,a,b,c,31)
#  define _FNMSUB(d,a,b,c)		_FA(63,d,a,b,c,30)
#  define _FNMSUB_(d,a,b,c)		_FA_(63,d,a,b,c,30)
#  define _FNMSUBS(d,a,b,c)		_FA(59,d,a,b,c,30)
#  define _FNMSUBS_(d,a,b,c)		_FA_(59,d,a,b,c,30)
#  define _FRES(d,b)			_FA(59,d,0,b,0,24)
#  define _FRES_(d,b)			_FA_(59,d,0,b,0,24)
#  define _FRSP(d,b)			_FA(63,d,0,b,0,12)
#  define _FRSP_(d,b)			_FA_(63,d,0,b,0,12)
#  define _FRSQTRE(d,b)			_FA(63,d,0,b,0,26)
#  define _FRSQTRE_(d,b)	    	_FA_(63,d,0,b,0,26)
#  define _FSEL(d,a,b,c)    		_FA(63,d,a,b,c,23)
#  define _FSEL_(d,a,b,c)		_FA_(63,d,a,b,c,23)
#  define _FSQRT(d,b)			_FA(63,d,0,b,0,22)
#  define _FSQRT_(d,b)			_FA_(63,d,0,b,0,22)
#  define _FSQRTS(d,b)			_FA(59,d,0,b,0,22)
#  define _FSQRTS_(d,b)			_FA_(59,d,0,b,0,22)
#  define _FSUB(d,a,b)			_FA(63,d,a,b,0,20)
#  define _FSUB_(d,a,b)			_FA(63,d,a,b,0,20)
#  define _FSUBS(d,a,b)			_FA(59,d,a,b,0,20)
#  define _FSUBS_(d,a,b)    		_FA(59,d,a,b,0,20)
#  define _LFD(d,a,s)			_FDs(50,d,a,s)
#  define _LFDU(d,a,s)			_FDs(51,d,a,s)
#  define _LFDUX(d,a,b)			_FX(31,d,a,b,631)
#  define _LFDX(d,a,b)			_FX(31,d,a,b,599)
#  define _LFS(d,a,s)			_FDs(48,d,a,s)
#  define _LFSU(d,a,s)			_FDs(49,d,a,s)
#  define _LFSUX(d,a,b)			_FX(31,d,a,b,567)
#  define _LFSX(d,a,b)			_FX(31,d,a,b,535)
#  define _MCRFS(d,s)			_FXL(63,d<<2,(s)<<2,64)
#  define _MFFS(d)			_FX(63,d,0,0,583)
#  define _MFFS_(d)			_FX_(63,d,0,0,583)
#  define _MTFSB0(d)			_FX(63,d,0,0,70)
#  define _MTFSB0_(d)			_FX_(63,d,0,0,70)
#  define _MTFSB1(d)			_FX(63,d,0,0,38)
#  define _MTFSB1_(d)			_FX_(63,d,0,0,38)
#  define _MTFSF(m,b)			_FXFL(63,m,b,711)
#  define _MTFSF_(m,b)			_FXFL_(63,m,b,711)
#  define _MTFSFI(d,i)			_FX(63,d<<2,0,i<<1,134)
#  define _MTFSFI_(d,i)			_FX_(63,d<<2,0,i<<1,134)
#  define _STFD(s,a,d)			_FDs(54,s,a,d)
#  define _STFDU(s,a,d)			_FDs(55,s,a,d)
#  define _STFDUX(s,a,b)	    	_FX(31,s,a,b,759)
#  define _STFDX(s,a,b)			_FX(31,s,a,b,727)
#  define _STFIWX(s,a,b)    		_FX(31,s,a,b,983)
#  define _STFS(s,a,d)			_FDs(52,s,a,d)
#  define _STFSU(s,a,d)			_FDs(53,s,a,d)
#  define _STFSUX(s,a,b)    		_FX(31,s,a,b,695)
#  define _STFSX(s,a,b)			_FX(31,s,a,b,663)

static void movr_f(jit_state_t*,int32_t,int32_t);
static void movr_d(jit_state_t*,int32_t,int32_t);

static void movi_f(jit_state_t*,int32_t,jit_float32_t);
static void movi_d(jit_state_t*,int32_t,jit_float64_t);

static void extr_f(jit_state_t*,int32_t,int32_t);
static void extr_d(jit_state_t*,int32_t,int32_t);

static void truncr_f_i(jit_state_t*,int32_t,int32_t);
static void truncr_d_i(jit_state_t*,int32_t,int32_t);

#  if __WORDSIZE == 64
static void truncr_f_l(jit_state_t*,int32_t,int32_t);
static void truncr_d_l(jit_state_t*,int32_t,int32_t);
#  endif

static void extr_d_f(jit_state_t*,int32_t,int32_t);
static void extr_f_d(jit_state_t*,int32_t,int32_t);

static void absr_f(jit_state_t*,int32_t,int32_t);
static void absr_d(jit_state_t*,int32_t,int32_t);

static void negr_f(jit_state_t*,int32_t,int32_t);
static void negr_d(jit_state_t*,int32_t,int32_t);

static void sqrtr_f(jit_state_t*,int32_t,int32_t);
static void sqrtr_d(jit_state_t*,int32_t,int32_t);

static void addr_f(jit_state_t*,int32_t,int32_t,int32_t);
static void addr_d(jit_state_t*,int32_t,int32_t,int32_t);

static void subr_f(jit_state_t*,int32_t,int32_t,int32_t);
static void subr_d(jit_state_t*,int32_t,int32_t,int32_t);

static void mulr_f(jit_state_t*,int32_t,int32_t,int32_t);
static void mulr_d(jit_state_t*,int32_t,int32_t,int32_t);

static void divr_f(jit_state_t*,int32_t,int32_t,int32_t);
static void divr_d(jit_state_t*,int32_t,int32_t,int32_t);

static jit_reloc_t bltr_f(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bltr_d(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bler_f(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bler_d(jit_state_t*,int32_t,int32_t);
static jit_reloc_t beqr_f(jit_state_t*,int32_t,int32_t);
static jit_reloc_t beqr_d(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bger_f(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bger_d(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bgtr_f(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bgtr_d(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bner_f(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bner_d(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bunltr_f(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bunltr_d(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bunler_f(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bunler_d(jit_state_t*,int32_t,int32_t);
static jit_reloc_t buneqr_f(jit_state_t*,int32_t,int32_t);
static jit_reloc_t buneqr_d(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bunger_f(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bunger_d(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bungtr_f(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bungtr_d(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bltgtr_f(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bltgtr_d(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bordr_f(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bordr_d(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bunordr_f(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bunordr_d(jit_state_t*,int32_t,int32_t);

static void ldr_f(jit_state_t*,int32_t,int32_t);
static void ldi_f(jit_state_t*,int32_t,jit_word_t);

static void ldxr_f(jit_state_t*,int32_t,int32_t,int32_t);
static void ldxi_f(jit_state_t*,int32_t,int32_t,jit_word_t);

static void str_f(jit_state_t*,int32_t,int32_t);
static void sti_f(jit_state_t*,jit_word_t,int32_t);

static void stxr_f(jit_state_t*,int32_t,int32_t,int32_t);
static void stxi_f(jit_state_t*,jit_word_t,int32_t,int32_t);

static void ldr_d(jit_state_t*,int32_t,int32_t);
static void ldi_d(jit_state_t*,int32_t,jit_word_t);

static void ldxr_d(jit_state_t*,int32_t,int32_t,int32_t);
static void ldxi_d(jit_state_t*,int32_t,int32_t,jit_word_t);

static void str_d(jit_state_t*,int32_t,int32_t);
static void sti_d(jit_state_t*,jit_word_t,int32_t);

static void stxr_d(jit_state_t*,int32_t,int32_t,int32_t);
static void stxi_d(jit_state_t*,jit_word_t,int32_t,int32_t);

#  define _u16(v)			((v) & 0xffff)
static uint32_t
FA(int o, int d, int a, int b, int c, int x, int r)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(d & ~((1 << 5) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    assert(!(b & ~((1 << 5) - 1)));
    assert(!(c & ~((1 << 5) - 1)));
    assert(!(x & ~((1 << 5) - 1)));
    assert(!(r & ~((1 << 1) - 1)));
    instr_t i = {.A = {o, d, a, b, c, x, r}};
    return i.w;
}

static uint32_t
FXFL(int o, int m, int b, int x, int r)
{
    assert(!(o & ~((1 <<  6) - 1)));
    assert(!(m & ~((1 <<  8) - 1)));
    assert(!(b & ~((1 <<  5) - 1)));
    assert(!(x & ~((1 << 10) - 1)));
    assert(!(r & ~((1 <<  1) - 1)));
    instr_t i = {.XFL = {o, m, b, x, r}};
    return i.w;
}

static void
movr_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    if (r0 != r1)
	em_wp(_jit, _FMR(r0,r1));
}

static void
movr_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    movr_d(_jit, r0, r1);
}

static void
movi_f(jit_state_t *_jit, int32_t r0, jit_float32_t i0)
{
    union {
	int32_t	 i;
	jit_float32_t	 f;
    } data;

    data.f = i0;
    jit_fpr_t reg = get_temp_fpr(_jit);
    movi(_jit, fn(reg), data.i & 0xffffffff);
    stxi_i(_jit, alloca_offset - 4, rn(_FP), fn(reg));
    unget_temp_fpr(_jit);

    ldxi_f(_jit, r0, rn(_FP), alloca_offset - 4);
}

static void
movi_d(jit_state_t *_jit, int32_t r0, jit_float64_t i0)
{
    union {
	int32_t	 i[2];
	jit_word_t	 w;
	jit_float64_t	 d;
    } data;

    data.d = i0;
    jit_gpr_t reg = get_temp_gpr(_jit);
#  if __WORDSIZE == 32
    movi(_jit, rn(reg), data.i[0]);
    stxi_i(_jit, alloca_offset - 8, rn(_FP), rn(reg));
    movi(_jit, rn(reg), data.i[1]);
    stxi_i(_jit, alloca_offset - 4, rn(_FP), rn(reg));
#  else
    movi(_jit, rn(reg), data.w);
    stxi_l(_jit, alloca_offset - 8, rn(_FP), rn(reg));
#  endif
    unget_temp_gpr(_jit);
    ldxi_d(_jit, r0, rn(_FP), alloca_offset - 8);
}

/* should only work on newer ppc (fcfid is a ppc64 instruction) */
static void
extr_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
#  if __WORDSIZE == 32
    jit_gpr_t reg = get_temp_gpr(_jit);
    rshi(_jit, rn(reg), r1, 31);
    /* use reserved 8 bytes area */
    stxi_i(_jit, alloca_offset - 4, rn(_FP), r1);
    stxi_i(_jit, alloca_offset - 8, rn(_FP), rn(reg));
    unget_temp_gpr(_jit);
#  else
    stxi_l(_jit, alloca_offset - 8, rn(_FP), r1);
#  endif
    ldxi_d(_jit, r0, rn(_FP), alloca_offset - 8);
    em_wp(_jit, _FCFID(r0, r0));
}

static void
extr_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    extr_d(_jit, r0, r1);
}

static void
extr_d_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FRSP(r0, r1));
}

static void
extr_f_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    movr_d(_jit, r0, r1);
}

static void
absr_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FABS(r0, r1));
}

static void
absr_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    absr_d(_jit, r0, r1);
}

static void
sqrtr_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FSQRT(r0, r1));
}

static void
sqrtr_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FSQRTS(r0, r1));
}

static void
addr_d(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _FADD(r0, r1, r2));
}

static void
addr_f(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _FADDS(r0, r1, r2));
}

static void
subr_f(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _FSUBS(r0, r1, r2));
}

static void
subr_d(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _FSUB(r0, r1, r2));
}

static void
negr_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FNEG(r0, r1));
}

static void
negr_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    negr_d(_jit, r0, r1);
}

static void
mulr_f(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _FMULS(r0, r1, r2));
}

static void
mulr_d(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _FMUL(r0, r1, r2));
}

static void
divr_f(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _FDIVS(r0, r1, r2));
}

static void
divr_d(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _FDIV(r0, r1, r2));
}

static void
truncr_d_i(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    jit_fpr_t reg = get_temp_fpr(_jit);
    em_wp(_jit, _FCTIWZ(fn(reg), r1));
    /* use reserved 8 bytes area */
    stxi_d(_jit, alloca_offset - 8, rn(_FP), fn(reg));
    ldxi_i(_jit, r0, rn(_FP), alloca_offset - 4);
    unget_temp_fpr(_jit);
}

static void
truncr_f_i(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    truncr_d_i(_jit, r0, r1);
}

#  if __WORDSIZE == 64
static void
truncr_d_l(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    jit_fpr_t reg = get_temp_fpr(_jit);
    em_wp(_jit, _FCTIDZ(fn(reg), r1));
    /* use reserved 8 bytes area */
    stxi_d(_jit, alloca_offset - 8, rn(_FP), fn(reg));
    ldxi_l(_jit, r0, rn(_FP), alloca_offset - 8);
    unget_temp_fpr(_jit);
}

static void
truncr_f_l(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    truncr_d_l(_jit, r0, r1);
}
#  endif


static jit_reloc_t
bltr_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FCMPO(CR_0, r0, r1));
    return emit_cc_jump(_jit, _BLT(0));
}

static jit_reloc_t
bltr_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    return bltr_d(_jit, r0, r1);
}

static jit_reloc_t
bler_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FCMPO(CR_0, r0, r1));
    em_wp(_jit, _CREQV(CR_GT, CR_GT, CR_UN));
    return emit_cc_jump(_jit, _BGT(0));
}

static jit_reloc_t
bler_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    return bler_d(_jit, r0, r1);
}

static jit_reloc_t
beqr_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FCMPO(CR_0, r0, r1));
    return emit_cc_jump(_jit, _BEQ(0));
}

static jit_reloc_t
beqr_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    return beqr_d(_jit, r0, r1);
}

static jit_reloc_t
bger_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FCMPO(CR_0, r0, r1));
    em_wp(_jit, _CREQV(CR_LT, CR_LT, CR_UN));
    return emit_cc_jump(_jit, _BLT(0));
}

static jit_reloc_t
bger_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    return bger_d(_jit, r0, r1);
}

static jit_reloc_t
bgtr_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FCMPO(CR_0, r0, r1));
    return emit_cc_jump(_jit, _BGT(0));
}

static jit_reloc_t
bgtr_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    return bgtr_d(_jit, r0, r1);
}

static jit_reloc_t
bner_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FCMPO(CR_0, r0, r1));
    return emit_cc_jump(_jit, _BNE(0));
}

static jit_reloc_t
bner_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    return bner_d(_jit, r0, r1);
}

static jit_reloc_t
bunltr_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FCMPU(CR_0, r0, r1));
    em_wp(_jit, _CROR(CR_LT, CR_LT, CR_UN));
    return emit_cc_jump(_jit, _BLT(0));
}

static jit_reloc_t
bunltr_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    return bunltr_d(_jit, r0, r1);
}

static jit_reloc_t
bunler_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FCMPU(CR_0, r0, r1));
    return emit_cc_jump(_jit, _BLE(0));
}

static jit_reloc_t
bunler_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    return bunler_d(_jit, r0, r1);
}

static jit_reloc_t
buneqr_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FCMPU(CR_0, r0, r1));
    em_wp(_jit, _CROR(CR_EQ, CR_EQ, CR_UN));
    return emit_cc_jump(_jit, _BEQ(0));
}

static jit_reloc_t
buneqr_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    return buneqr_d(_jit, r0, r1);
}

static jit_reloc_t
bunger_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FCMPU(CR_0, r0, r1));
    return emit_cc_jump(_jit, _BGE(0));
}

static jit_reloc_t
bunger_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    return bunger_d(_jit, r0, r1);
}

static jit_reloc_t
bungtr_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FCMPU(CR_0, r0, r1));
    em_wp(_jit, _CROR(CR_GT, CR_GT, CR_UN));
    return emit_cc_jump(_jit, _BGT(0));
}

static jit_reloc_t
bungtr_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    return bungtr_d(_jit, r0, r1);
}

static jit_reloc_t
bltgtr_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FCMPU(CR_0, r0, r1));
    em_wp(_jit, _CROR(CR_EQ, CR_LT, CR_GT));
    return emit_cc_jump(_jit, _BEQ(0));
}

static jit_reloc_t
bltgtr_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    return bltgtr_d(_jit, r0, r1);
}

static jit_reloc_t
bordr_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FCMPU(CR_0, r0, r1));
    return emit_cc_jump(_jit, _BNU(0));
}

static jit_reloc_t
bordr_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    return bordr_d(_jit, r0, r1);
}

static jit_reloc_t
bunordr_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _FCMPU(CR_0, r0, r1));
    return emit_cc_jump(_jit, _BUN(0));
}

static jit_reloc_t
bunordr_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    return bunordr_f(_jit, r0, r1);
}

static void
ldr_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _LFSX(r0, rn(_R0), r1));
}

static void
ldi_f(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    if (can_sign_extend_short_p(i0)) {
	em_wp(_jit, _LFS(r0, rn(_R0), i0));
    } else if (can_sign_extend_int_p(i0)) {
	jit_word_t hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	jit_word_t lo = (int16_t)(i0 - (hi << 16));
	jit_gpr_t reg = get_temp_gpr(_jit);
	em_wp(_jit, _LIS(rn(reg), hi));
	em_wp(_jit, _LFS(r0, rn(reg), lo));
	unget_temp_gpr(_jit);
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	ldr_f(_jit, r0, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldr_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _LFDX(r0, rn(_R0), r1));
}

static void
ldi_d(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    if (can_sign_extend_short_p(i0)) {
	em_wp(_jit, _LFD(r0, rn(_R0), i0));
    } else if (can_sign_extend_int_p(i0)) {
	jit_word_t hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	jit_word_t lo = (int16_t)(i0 - (hi << 16));
	jit_gpr_t reg = get_temp_gpr(_jit);
	em_wp(_jit, _LIS(rn(reg), hi));
	em_wp(_jit, _LFD(r0, rn(reg), lo));
	unget_temp_gpr(_jit);
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	ldr_d(_jit, r0, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldxr_f(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    if (r1 == rn(_R0)) {
	if (r2 != rn(_R0)) {
	    em_wp(_jit, _LFSX(r0, r2, r1));
	} else {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _LFSX(r0, rn(reg), r2));
	    unget_temp_gpr(_jit);
	}
    } else {
	em_wp(_jit, _LFSX(r0, r1, r2));
    }
}

static void
ldxr_d(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    if (r1 == rn(_R0)) {
	if (r2 != rn(_R0)) {
	    em_wp(_jit, _LFDX(r0, r2, r1));
	} else {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _LFDX(r0, rn(reg), r2));
	    unget_temp_gpr(_jit);
	}
    } else {
	em_wp(_jit, _LFDX(r0, r1, r2));
    }
}

static void
ldxi_f(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (i0 == 0) {
	ldr_f(_jit, r0, r1);
    } else if (can_sign_extend_short_p(i0)) {
	if (r1 == rn(_R0)) {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _LFS(r0, rn(reg), i0));
	    unget_temp_gpr(_jit);
	} else {
	    em_wp(_jit, _LFS(r0, r1, i0));
	}
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	ldxr_f(_jit, r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldxi_d(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (i0 == 0) {
	ldr_d(_jit, r0, r1);
    } else if (can_sign_extend_short_p(i0)) {
	if (r1 == rn(_R0)) {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _LFD(r0, rn(reg), i0));
	    unget_temp_gpr(_jit);
	} else {
	    em_wp(_jit, _LFD(r0, r1, i0));
	}
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	ldxr_d(_jit, r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
str_f(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _STFSX(r1, rn(_R0), r0));
}

static void
sti_f(jit_state_t *_jit, jit_word_t i0, int32_t r0)
{
    if (can_sign_extend_short_p(i0)) {
	em_wp(_jit, _STFS(r0, rn(_R0), i0));
    } else if (can_sign_extend_int_p(i0)) {
	jit_word_t hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	jit_word_t lo = (int16_t)(i0 - (hi << 16));
	jit_gpr_t reg = get_temp_gpr(_jit);
	em_wp(_jit, _LIS(rn(reg), hi));
	em_wp(_jit, _STFS(r0, rn(reg), lo));
	unget_temp_gpr(_jit);
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	str_f(_jit, rn(reg), r0);
	unget_temp_gpr(_jit);
    }
}

static void
str_d(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _STFDX(r1, rn(_R0), r0));
}

static void
sti_d(jit_state_t *_jit, jit_word_t i0, int32_t r0)
{
    if (can_sign_extend_short_p(i0)) {
	em_wp(_jit, _STFD(r0, rn(_R0), i0));
    } else if (can_sign_extend_int_p(i0)) {
	jit_word_t hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	jit_word_t lo = (int16_t)(i0 - (hi << 16));
	jit_gpr_t reg = get_temp_gpr(_jit);
	em_wp(_jit, _LIS(rn(reg), hi));
	em_wp(_jit, _STFD(r0, rn(reg), lo));
	unget_temp_gpr(_jit);
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	str_d(_jit, rn(reg), r0);
	unget_temp_gpr(_jit);
    }
}

static void
stxr_f(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    if (r0 == rn(_R0)) {
	if (r1 != rn(_R0)) {
	    em_wp(_jit, _STFSX(r2, r1, r0));
	} else {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _STFSX(r2, rn(reg), r0));
	    unget_temp_gpr(_jit);
	}
    } else {
	em_wp(_jit, _STFSX(r2, r0, r1));
    }
}

static void
stxr_d(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    if (r0 == rn(_R0)) {
	if (r1 != rn(_R0)) {
	    em_wp(_jit, _STFDX(r2, r1, r0));
	} else {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r0);
	    em_wp(_jit, _STFDX(r2, rn(reg), r1));
	    unget_temp_gpr(_jit);
	}
    } else {
	em_wp(_jit, _STFDX(r2, r0, r1));
    }
}

static void
stxi_f(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    if (i0 == 0) {
	str_f(_jit, r0, r1);
    } else if (can_sign_extend_short_p(i0)) {
	if (r0 == rn(_R0)) {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), i0);
	    em_wp(_jit, _STFS(r1, rn(reg), i0));
	    unget_temp_gpr(_jit);
	} else {
	    em_wp(_jit, _STFS(r1, r0, i0));
	}
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	stxr_f(_jit, rn(reg), r0, r1);
	unget_temp_gpr(_jit);
    }
}

static void
stxi_d(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    if (i0 == 0) {
	str_d(_jit, r0, r1);
    } else if (can_sign_extend_short_p(i0)) {
	if (r0 == rn(_R0)) {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), i0);
	    em_wp(_jit, _STFD(r1, rn(reg), i0));
	    unget_temp_gpr(_jit);
	} else {
	    em_wp(_jit, _STFD(r1, r0, i0));
	}
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	stxr_d(_jit, rn(reg), r0, r1);
	unget_temp_gpr(_jit);
    }
}

static void
retr_f(jit_state_t *_jit, int32_t r0)
{
    if (rn(JIT_RET) != r0)
	movr_f(_jit, fn(JIT_FRET), r0);

    ret(_jit);
}

static void
retr_d(jit_state_t *_jit, int32_t r0)
{
    if (fn(JIT_FRET) != r0)
	movr_d(_jit, fn(JIT_FRET), r0);

    ret(_jit);
}

static void
retval_d(jit_state_t *_jit, int32_t r0)
{
    if (r0 != fn(JIT_FRET))
	movr_d(_jit, r0, fn(JIT_FRET));
}

static void
retval_f(jit_state_t *_jit, int32_t r0)
{
    retval_d(_jit, r0);
}
