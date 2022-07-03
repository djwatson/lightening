/*
 * Copyright (C) 2012-2017, 2019  Free Software Foundation, Inc.
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

#  if __WORDSIZE == 32
#    define gpr_save_area		72	/* r14~r31 = 18 * 4 */
#    define params_offset		24
#    define can_sign_extend_int_p(im)	1
#    define can_zero_extend_int_p(im)	1
#    define fits_uint32_p(im)		1
#  else
#    define gpr_save_area		144	/* r14~r31 = 18 * 8 */
#    if ABI_ELFv2
#      define params_offset		32
#    else
#      define params_offset		48
#    endif
#    define can_sign_extend_int_p(im)					\
	(((im) >= 0 && (long)(im) <=  0x7fffffffL) ||			\
	 ((im) <  0 && (long)(im) >= -0x80000000L))
#    define can_zero_extend_int_p(im)					\
	((im) >= 0 && (im) < 0x80000000L)
#    define fits_uint32_p(im)		((im & 0xffffffff00000000L) == 0)
#  endif
#  define fpr_save_area			64
#  define alloca_offset			-(gpr_save_area + fpr_save_area)

#  define can_sign_extend_short_p(im)	((im) >= -32768 && (im) <= 32767)
#  define can_zero_extend_short_p(im)	((im) >= 0 && (im) <= 65535)
#  define can_sign_extend_jump_p(im)	((im) >= -33554432 && (im) <= 33554431)

#define simm14_p(i0) ((i0) <= 0x1fff && (i0) >= -0x2000)
#define simm24_p(i0) ((i0) <= 0x7ffff && (i0) >= -0x800000)

#  define _FXO(o,d,a,b,e,x)		FXO(o,d,a,b,e,x,0)
#  define _FXO_(o,d,a,b,e,x)		FXO(o,d,a,b,e,x,1)
#  define _FDs(o,d,a,s)			FDs(o,d,a,s)
#  define _FDu(o,d,a,s)			FDu(o,d,a,s)
#  define _FX(o,d,a,b,x)			FX(o,d,a,b,x,0)
#  define _FX_(o,d,a,b,x)		FX(o,d,a,b,x,1)
#  define _FI(o,t,a,k)			FI(o,t,a,k)
#  define _FB(o,bo,bi,t,a,k)		FB(o,bo,bi,t,a,k)
#  define _FXL(o,bo,bi,x)		FXL(o,bo,bi,x,0)
#  define _FXL_(o,bo,bi,x)		FXL(o,bo,bi,x,1)
#  define _FC(o,d,l,a,b,x)		FC(o,d,l,a,b,x)
#  define _FCI(o,d,l,a,s)		FCI(o,d,l,a,s)
#  define _FXFX(o,s,x,f)			FXFX(o,s,x,f)
#  define _FM(o,s,a,h,b,e,r)		FM(o,s,a,h,b,e,r)
#  if __WORDSIZE == 64
#    define _FMDS(o,s,a,b,e,x)		FMDS(o,s,a,b,e,x,0)
#    define _FMDS_(o,s,a,b,e,x)		FMDS(o,s,a,b,e,x,1)
#    define _FMD(o,s,a,h,b,x,i)		FMD(o,s,a,h,b,x,i,0)
#    define _FMD_(o,s,a,h,b,x,i)		FMD(o,s,a,h,b,x,i,1)
#  define _FXS(o,d,a,h,x,i)		FXS(o,d,a,h,x,i,0)
#  define _FXS_(o,d,a,h,x,i)		FXS(o,d,a,h,x,i,1)
#  endif

static uint32_t FXO(int,int,int,int,int,int,int);
static uint32_t FDs(int,int,int,int);
static uint32_t FDu(int,int,int,int);
static uint32_t FX(int,int,int,int,int,int);
static uint32_t FI(int,int,int,int);
static uint32_t FB(int,int,int,int,int,int);
static uint32_t FXL(int,int,int,int,int);
static uint32_t FC(int,int,int,int,int,int);
static uint32_t FCI(int,int,int,int,int);
static uint32_t FXFX(int,int,int,int);
static uint32_t FM(int,int,int,int,int,int,int);

#  if __WORDSIZE == 64
static uint32_t FMD(int,int,int,int,int,int,int,int);
static uint32_t FXS(int,int,int,int,int,int,int);
#  endif

#  define CR_0				0
#  define CR_1				1
#  define CR_2				2
#  define CR_3				3
#  define CR_4				4
#  define CR_5				5
#  define CR_6				6
#  define CR_7				7
#  define CR_LT				0
#  define CR_GT				1
#  define CR_EQ				2
#  define CR_SO				3
#  define CR_UN				3
#  define BCC_F				4
#  define BCC_T				12
#  define _ADD(d,a,b)			_FXO(31,d,a,b,0,266)
#  define _ADD_(d,a,b)			_FXO_(31,d,a,b,0,266)
#  define _ADDO(d,a,b)			_FXO(31,d,a,b,1,266)
#  define _ADDO_(d,a,b)			_FXO_(31,d,a,b,1,266)
#  define _ADDC(d,a,b)			_FXO_(31,d,a,b,0,10)
#  define _ADDC_(d,a,b)			_FXO_(31,d,a,b,0,10)
#  define _ADDCO(d,a,b)			_FXO(31,d,a,b,1,10)
#  define _ADDCO_(d,a,b)			_FXO_(31,d,a,b,1,10)
#  define _ADDE(d,a,b)			_FXO(31,d,a,b,0,138)
#  define _ADDE_(d,a,b)			_FXO_(31,d,a,b,0,138)
#  define _ADDEO(d,a,b)			_FXO(31,d,a,b,1,138)
#  define _ADDEO_(d,a,b)			_FXO_(31,d,a,b,1,138)
#  define _ADDI(d,a,s)			_FDs(14,d,a,s)
#  define _ADDIC(d,a,s)			_FDs(12,d,a,s)
#  define _ADDIC_(d,a,s)			_FDs(13,d,a,s)
#  define _ADDIS(d,a,s)			_FDs(15,d,a,s)
#  define _LIS(d,s)			_ADDIS(d,0,s)
#  define _ADDME(d,a)			_FXO(31,d,a,0,0,234)
#  define _ADDME_(d,a)			_FXO_(31,d,a,0,0,234)
#  define _ADDMEO(d,a)			_FXO(31,d,a,0,1,234)
#  define _ADDMEO_(d,a)			_FXO_(31,d,a,0,1,234)
#  define _ADDZE(d,a)			_FXO(31,d,a,0,0,202)
#  define _ADDZE_(d,a)			_FXO_(31,d,a,0,0,202)
#  define _ADDZEO(d,a)			_FXO(31,d,a,0,1,202)
#  define _ADDZEO_(d,a)			_FXO_(31,d,a,0,1,202)
#  define _AND(d,a,b)			_FX(31,a,d,b,28)
#  define _ANDC(d,a,b)			_FXO(31,a,d,b,0,60)
#  define _ANDC_(d,a,b)			_FXO_(31,a,d,b,0,60)
#  define _AND_(d,a,b)			_FX_(31,a,b,d,28)
#  define _ANDI_(d,a,u)			_FDu(28,a,d,u)
#  define _ANDIS_(d,a,u)			_FDu(29,a,d,u)
#  define _B(t)				_FI(18,t,0,0)
#  define _BA(t)				_FI(18,t,1,0)
#  define _BL(t)				_FI(18,t,0,1)
#  define _BLA(t)			_FI(18,t,1,1)
#  define _BC(o,i,t)			_FB(16,o,i,t,0,0)
#  define _BCA(o,i,t)			_FB(16,o,i,t,1,0)
#  define _BCL(o,i,t)			_FB(16,o,i,t,0,1)
#  define _BCLA(o,i,t)			_FB(16,o,i,t,1,1)
#  define _BLT(t)			_BC(BCC_T,CR_LT,t)
#  define _BLE(t)			_BC(BCC_F,CR_GT,t)
#  define _BEQ(t)			_BC(BCC_T,CR_EQ,t)
#  define _BGE(t)			_BC(BCC_F,CR_LT,t)
#  define _BGT(t)			_BC(BCC_T,CR_GT,t)
#  define _BNE(t)			_BC(BCC_F,CR_EQ,t)
#  define _BUN(t)			_BC(BCC_T,CR_UN,t)
#  define _BNU(t)			_BC(BCC_F,CR_UN,t)
#  define _BCCTR(o,i)			_FXL(19,o,i,528)
#  define _BCCTRL(o,i)			_FXL_(19,o,i,528)
#  define _BLTCTR()			_BCCTR(BCC_T,CR_LT)
#  define _BLECTR()			_BCCTR(BCC_F,CR_GT)
#  define _BEQCTR()			_BCCTR(BCC_T,CR_EQ)
#  define _BGECTR()			_BCCTR(BCC_F,CR_LT)
#  define _BGTCTR()			_BCCTR(BCC_T,CR_GT)
#  define _BNECTR()			_BCCTR(BCC_F,CR_EQ)
#  define _BCTR()			_BCCTR(20,0)
#  define _BCTRL()			_BCCTRL(20,0)
#  define _BCLR(o,i)			_FXL(19,o,i,16)
#  define _BCLRL(o,i)			_FXL_(19,o,i,16)
#  define _BLTLR()			_BCLR(BCC_T,CR_LT)
#  define _BLELR()			_BCLR(BCC_F,CR_GT)
#  define _BEQLR()			_BCLR(BCC_T,CR_EQ)
#  define _BGELR()			_BCLR(BCC_F,CR_LT)
#  define _BGTLR()			_BCLR(BCC_T,CR_GT)
#  define _BNELR()			_BCLR(BCC_F,CR_EQ)
#  define _BLR()				_BCLR(20,0)
#  define _BLRL()			_BCLRL(20,0)
#  define _XCMP(cr,l,a,b)		_FC(31,cr,l,a,b,0)
#  define _CMPD(a,b)			_XCMP(0,1,a,b)
#  define _CMPW(a,b)			_XCMP(0,0,a,b)
#  define _XCMPI(cr,l,a,s)		_FCI(11,cr,l,a,s)
#  define _CMPDI(a,s)			_XCMPI(0,1,a,s)
#  define _CMPWI(a,s)			_XCMPI(0,0,a,s)
#  define _XCMPL(cr,l,a,b)		_FC(31,cr,l,a,b,32)
#  define _CMPLD(a,b)			_XCMPL(0,1,a,b)
#  define _CMPLW(a,b)			_XCMPL(0,0,a,b)
#  define _XCMPLI(cr,l,a,u)		_FCI(10,cr,l,a,u)
#  define _CMPLDI(a,s)			_XCMPLI(0,1,a,s)
#  define _CMPLWI(a,s)			_XCMPLI(0,0,a,s)
#  define _CNTLZW(a,s)			_FX(31,s,a,0,26)
#  define _CNTLZW_(a,s)			_FX_(31,s,a,0,26)
#  define _CRAND(d,a,b)			_FX(19,d,a,b,257)
#  define _CRANDC(d,a,b)			_FX(19,d,a,b,129)
#  define _CREQV(d,a,b)			_FX(19,d,a,b,289)
#  define _CRSET(d)			_CREQV(d,d,d)
#  define _CRNAND(d,a,b)			_FX(19,d,a,b,225)
#  define _CRNOR(d,a,b)			_FX(19,d,a,b,33)
#  define _CRNOT(d,a)			_CRNOR(d,a,a)
#  define _CROR(d,a,b)			_FX(19,d,a,b,449)
#  define _CRMOVE(d,a)			_CROR(d,a,a)
#  define _CRORC(d,a,b)			_FX(19,d,a,b,417)
#  define _CRXOR(d,a,b)			_FX(19,d,a,b,193)
#  define _CRCLR(d)			_CRXOR(d,d,d)
#  define _DCBA(a,b)			_FX(31,0,a,b,758)
#  define _DCBF(a,b)			_FX(31,0,a,b,86)
#  define _DCBI(a,b)			_FX(31,0,a,b,470)
#  define _DCBST(a,b)			_FX(31,0,a,b,54)
#  define _DCBT(a,b)			_FX(31,0,a,b,278)
#  define _DCBTST(a,b)			_FX(31,0,a,b,246)
#  define _DCBZ(a,b)			_FX(31,0,a,b,1014)
#  define _DIVW(d,a,b)			_FXO(31,d,a,b,0,491)
#  define _DIVW_(d,a,b)			_FXO_(31,d,a,b,0,491)
#  define _DIVWO(d,a,b)			_FXO(31,d,a,b,1,491)
#  define _DIVWO_(d,a,b)			_FXO_(31,d,a,b,1,491)
#  define _DIVWU(d,a,b)			_FXO(31,d,a,b,0,459)
#  define _DIVWU_(d,a,b)			_FXO_(31,d,a,b,0,459)
#  define _DIVWUO(d,a,b)			_FXO(31,d,a,b,1,459)
#  define _DIVWUO_(d,a,b)		_FXO_(31,d,a,b,1,459)
#  define _DIVD(d,a,b)			_FXO(31,d,a,b,0,489)
#  define _DIVD_(d,a,b)			_FXO_(31,d,a,b,0,489)
#  define _DIVDO(d,a,b)			_FXO(31,d,a,b,1,489)
#  define _DIVDO_(d,a,b)			_FXO_(31,d,a,b,1,489)
#  define _DIVDU(d,a,b)			_FXO(31,d,a,b,0,457)
#  define _DIVDU_(d,a,b)			_FXO_(31,d,a,b,0,457)
#  define _DIVDUO(d,a,b)			_FXO(31,d,a,b,1,457)
#  define _DIVDUO_(d,a,b)		_FXO_(31,d,a,b,1,457)
#  define _ECIWX(d,a,b)			_FX(31,d,a,b,310)
#  define _ECOWX(s,a,b)			_FX(31,s,a,b,438)
#  define _EIEIO()			_FX(31,0,0,0,854)
#  define _EQV(d,a,b)			_FX(31,a,d,b,284)
#  define _EQV_(d,a,b)			_FX_(31,a,d,b,284)
#  define _EXTSB(d,a)			_FX(31,a,d,0,954)
#  define _EXTSB_(d,a)			_FX_(31,a,d,0,954)
#  define _EXTSH(d,a)			_FX(31,a,d,0,922)
#  define _EXTSH_(d,a)			_FX_(31,a,d,0,922)
#  define _EXTSW(d,a)			_FX(31,a,d,0,986)
#  define _EXTSW_(d,a)			_FX_(31,a,d,0,986)
#  define _ICIB(a,b)			_FX(31,0,a,b,982)
#  define _ISYNC()			_FXL(19,0,0,150)
#  define _LBZ(d,a,s)			_FDs(34,d,a,s)
#  define _LBZU(d,a,s)			_FDs(35,d,a,s)
#  define _LBZUX(d,a,b)			_FX(31,d,a,b,119)
#  define _LBZX(d,a,b)			_FX(31,d,a,b,87)
#  define _LHA(d,a,s)			_FDs(42,d,a,s)
#  define _LHAU(d,a,s)			_FDs(43,d,a,s)
#  define _LHAUX(d,a,b)			_FX(31,d,a,b,375)
#  define _LHAX(d,a,b)			_FX(31,d,a,b,343)
#  define _LHRBX(d,a,b)			_FX(31,d,a,b,790)
#  define _LHZ(d,a,s)			_FDs(40,d,a,s)
#  define _LHZU(d,a,s)			_FDs(41,d,a,s)
#  define _LHZUX(d,a,b)			_FX(31,d,a,b,311)
#  define _LHZX(d,a,b)			_FX(31,d,a,b,279)
#  define _LA(d,a,s)			_ADDI(d,a,s)
#  define _LI(d,s)			_ADDI(d,0,s)
#  define _LMW(d,a,s)			_FDs(46,d,a,s)
#  define _LSWI(d,a,n)			_FX(31,d,a,n,597)
#  define _LSWX(d,a,b)			_FX(31,d,a,b,533)
#  define _LWARX(d,a,b)			_FX(31,d,a,b,20)
#  define _LWBRX(d,a,b)			_FX(31,d,a,b,534)
#  define _LWA(d,a,s)			_FDs(58,d,a,s|2)
#  define _LWAUX(d,a,b)			_FX(31,d,a,b,373)
#  define _LWAX(d,a,b)			_FX(31,d,a,b,341)
#  define _LWZ(d,a,s)			_FDs(32,d,a,s)
#  define _LWZU(d,a,s)			_FDs(33,d,a,s)
#  define _LWZUX(d,a,b)			_FX(31,d,a,b,55)
#  define _LWZX(d,a,b)			_FX(31,d,a,b,23)
#  define _LD(d,a,s)			_FDs(58,d,a,s)
#  define _LDX(d,a,b)			_FX(31,d,a,b,21)
#  define _MCRF(d,s)			_FXL(19,d<<2,(s)<<2,0)
/* In case instruction is emulated, check the kernel can handle it.
   Will only generate it if DEBUG is enabled.
"""
Chapter 6. Optional Facilities and Instructions that are being
Phased Out of the Architecture
...
6.1 Move To Condition Register from XER
The mcrxr instruction is being phased out of the archi-
tecture. Its description is included here as an aid to
constructing operating system code to emulate it.

Move to Condition Register from XER
X-form
mcrxr BF
31	BF	//	///	///	512	/
0	6	9	11	16	21	31
CR(4xBF:4xBF+3) <- XER(32:35)
XER(32:35) <- 0b0000
The contents of XER(32:35) are copied to Condition Reg-
ister field BF. XER(32:35) are set to zero.
Special Registers Altered:
CR field BF XER(32:35)

Programming Note
Warning: This instruction has been phased out of
the architecture. Attempting to execute this
instruction will cause the system illegal instruction
error handler to be invoked
"""
 */
static void mcrxr(jit_state_t*, int32_t);
#  define _MFCR(d)			_FX(31,d,0,0,19)
#  define _MFMSR(d)			_FX(31,d,0,0,83)
#  define _MFSPR(d,s)			_FXFX(31,d,s<<5,339)
#  define _MFXER(d)			_MFSPR(d,1)
#  define _MFLR(d)			_MFSPR(d,8)
#  define _MFCTR(d)			_MFSPR(d,9)
#  define _MFSR(d,s)			_FX(31,d,s,0,595)
#  define _MFSRIN(d,b)			_FX(31,d,0,b,659)
#  define _MFTB(d,x,y)			_FXFX(31,d,(x)|((y)<<5),371)
#  define _MFTBL(d)			_MFTB(d,8,12)
#  define _MFTBU(d)			_MFTB(d,8,13)
#  define _MTCRF(c,s)			_FXFX(31,s,c<<1,144)
#  define _MTCR(s)			_MTCRF(0xff,s)
#  define _MTMSR(s)			_FX(31,s,0,0,146)
#  define _MTSPR(d,s)			_FXFX(31,d,s<<5,467)
#  define _MTXER(d)			_MTSPR(d,1)
#  define _MTLR(d)			_MTSPR(d,8)
#  define _MTCTR(d)			_MTSPR(d,9)
#  define _MTSR(r,s)			_FX(31,s<<1,r,0,210)
#  define _MTSRIN(r,b)			_FX(31,r<<1,0,b,242)
#  define _MULLI(d,a,s)			_FDs(07,d,a,s)
#  define _MULHW(d,a,b)			_FXO(31,d,a,b,0,75)
#  define _MULHW_(d,a,b)			_FXO_(31,d,a,b,0,75)
#  define _MULHWU(d,a,b)			_FXO(31,d,a,b,0,11)
#  define _MULHWU_(d,a,b)		_FXO_(31,d,a,b,0,11)
#  define _MULLW(d,a,b)			_FXO(31,d,a,b,0,235)
#  define _MULLW_(d,a,b)			_FXO_(31,d,a,b,0,235)
#  define _MULLWO(d,a,b)			_FXO(31,d,a,b,1,235)
#  define _MULLWO_(d,a,b)		_FXO_(31,d,a,b,1,235)
#  define _MULHD(d,a,b)			_FXO(31,d,a,b,0,73)
#  define _MULHD_(d,a,b)			_FXO_(31,d,a,b,0,73)
#  define _MULHDU(d,a,b)			_FXO(31,d,a,b,0,9)
#  define _MULHDU_(d,a,b)		_FXO_(31,d,a,b,0,9)
#  define _MULLD(d,a,b)			_FXO(31,d,a,b,0,233)
#  define _MULLD_(d,a,b)			_FXO_(31,d,a,b,0,233)
#  define _MULLDO(d,a,b)			_FXO(31,d,a,b,1,233)
#  define _MULLDO_(d,a,b)		_FXO_(31,d,a,b,1,233)
#  define _NAND(d,a,b)			_FX(31,a,d,b,476)
#  define _NAND_(d,a,b)			_FX_(31,a,d,b,476)
#  define _NEG(d,a)			_FXO(31,d,a,0,0,104)
#  define _NEG_(d,a)			_FXO_(31,d,a,0,0,104)
#  define _NEGO(d,a)			_FXO(31,d,a,0,1,104)
#  define _NEGO_(d,a)			_FXO_(31,d,a,0,1,104)
#  define _NOR(d,a,b)			_FX(31,a,d,b,124)
#  define _NOR_(d,a,b)			_FX_(31,a,d,b,124)
#  define _NOT(d,s)			_NOR(d,s,s)
#  define _OR(d,a,b)			_FX(31,a,d,b,444)
#  define _OR_(d,a,b)			_FX_(31,a,d,b,444)
#  define _MR(d,a)			_OR(d,a,a)
#  define _ORC(d,a,b)			_FX(31,a,d,b,412)
#  define _ORC_(d,a,b)			_FX_(31,a,d,b,412)
#  define _ORI(d,a,u)			_FDu(24,a,d,u)
#  define _NOP()				_ORI(0,0,0)
#  define _ORIS(d,a,u)			_FDu(25,a,d,u)
#  define _RFI()				_FXL(19,0,0,50)
#  define _RLWIMI(d,s,h,b,e)		_FM(20,s,d,h,b,e,0)
#  define _RLWIMI_(d,s,h,b,e)		_FM(20,s,d,h,b,e,1)
#  define _INSLWI(a,s,n,b)		_RLWIMI(a,s,32-b,b,b+n-1)
#  define _INSRWI(a,s,n,b)		_RLWIMI(a,s,32-(b+n),b,(b+n)-1)
#  define _RLWINM(a,s,h,b,e)		_FM(21,s,a,h,b,e,0)
#  define _RLWINM_(a,s,h,b,e)		_FM(21,s,a,h,b,e,1)
#  define _EXTLWI(a,s,n,b)		_RLWINM(a,s,b,0,n-1)
#  define _EXTRWI(a,s,n,b)		_RLWINM(a,s,b+n,32-n,31)
#  define _ROTLWI(a,s,n)			_RLWINM(a,s,n,0,31)
#  define _ROTRWI(a,s,n)			_RLWINM(a,s,32-n,0,31)
#  define _SLWI(a,s,n)			_RLWINM(a,s,n,0,31-n)
#  define _SRWI(a,s,n)			_RLWINM(a,s,32-n,n,31)
#  define _CLRLWI(a,s,n)			_RLWINM(a,s,0,n,31)
#  define _CLRRWI(a,s,n)			_RLWINM(a,s,0,0,31-n)
#  define _CLRLSWI(a,s,b,n)		_RLWINM(a,s,n,b-n,31-n)
#  define _RLWNM(a,s,b,m,e)		_FM(23,s,a,b,m,e,0)
#  define _RLWNM_(a,s,b,m,e)		_FM(23,s,a,b,m,e,1)
#  define _ROTLW(a,s,b)			_RLWNM(a,s,b,0,31)
#  define _SC()				_FDu(17,0,0,2)
#  define _SLW(a,s,b)			_FX(31,s,a,b,24)
#  define _SLW_(a,s,b)			_FX_(31,s,a,b,24)
#  define _SRAW(a,s,b)			_FX(31,s,a,b,792)
#  define _SRAW_(a,s,b)			_FX_(31,s,a,b,792)
#  define _SRAWI(a,s,h)			_FX(31,s,a,h,824)
#  define _SRAWI_(a,s,h)			_FX_(31,s,a,h,824)
#  define _SRW(a,s,b)			_FX(31,s,a,b,536)
#  define _SRW_(a,s,b)			_FX_(31,s,a,b,536)
#  if __WORDSIZE == 64
#    define _RLDICL(a,s,h,b)		_FMD(30,s,a,h&~32,b,0,h>>5)
#    define _RLDICL_(a,s,h,b)		_FMD_(30,s,a,h&~32,b,0,h>>5)
#    define _EXTRDI(x,y,n,b)		_RLDICL(x,y,(b+n),(64-n))
#    define _SRDI(x,y,n)			_RLDICL(x,y,(64-n),n)
#    define _CLRLDI(x,y,n)		_RLDICL(x,y,0,n)
#    define _RLDICR(a,s,h,e)		_FMD(30,s,a,h&~32,e,1,h>>5)
#    define _RLDICR_(a,s,h,e)		_FMD_(30,s,a,h&~32,e,1,h>>5)
#    define _EXTRLI(x,y,n,b)		_RLDICR(x,y,b,(n-1))
#    define _SLDI(x,y,n)			_RLDICR(x,y,n,(63-n))
#    define _CLRRDI(x,y,n)		_RLDICR(x,y,0,(63-n))
#    define _RLDIC(a,s,h,b)		_FMD(30,s,a,h&~32,b,2,h>>5)
#    define _RLDIC_(a,s,h,b)		_FMD_(30,s,a,h&~32,b,2,h>>5)
#    define _CLRLSLDI(x,y,b,n)		_RLDIC(x,y,n,(b-n))
#    define _RLDCL(a,s,h,b)		_FMDS(30,s,a,h,b,8)
#    define _RLDCL_(a,s,h,b)		_FMDS_(30,s,a,h,b,8)
#    define _ROTLD(x,y,z)		_RLDCL(x,y,z,0)
#    define _RLDCR(a,s,b,e)		_FMDS(30,s,a,b,e,0)
#    define _RLDCR_(a,s,b,e)		_FMDS_(30,s,a,b,e,0)
#    define _RLDIMI(a,s,h,b)		_FMD(30,s,a,h&~32,b,3,h>>5)
#    define _RLDIMI_(a,s,h,b)		_FMD_(30,s,a,h&~32,b,3,h>>5)
#    define _INSRDI(x,y,n,b)		_RLDIMI(x,y,(64-(b+n)),b)
#    define _SLD(a,s,b)			_FX(31,s,a,b,27)
#    define _SLD_(a,s,b)			_FX_(31,s,a,b,27)
#    define _SRD(a,s,b)			_FX(31,s,a,b,539)
#    define _SRD_(a,s,b)			_FX_(31,s,a,b,539)
#    define _SRADI(a,s,h)		_FXS(31,s,a,h&~32,413,h>>5)
#    define _SRADI_(a,s,h)		_FXS_(31,s,a,h&~32,413,h>>5)
#    define _SRAD(a,s,b)			_FX(31,s,a,b,794)
#    define _SRAD_(a,s,b)		_FX_(31,s,a,b,794)
#  endif
#  define _STB(s,a,d)			_FDs(38,s,a,d)
#  define _STBU(s,a,d)			_FDs(39,s,a,d)
#  define _STBUX(s,a,b)			_FX(31,s,a,b,247)
#  define _STBX(s,a,b)			_FX(31,s,a,b,215)
#  define _STH(s,a,d)			_FDs(44,s,a,d)
#  define _STHBRX(s,a,b)			_FX(31,s,a,b,918)
#  define _STHU(s,a,d)			_FDs(45,s,a,d)
#  define _STHUX(s,a,b)			_FX(31,s,a,b,439)
#  define _STHX(s,a,b)			_FX(31,s,a,b,407)
#  define _STMW(s,a,d)			_FDs(47,s,a,d)
#  define _STWSI(s,a,nb)			_FX(31,s,a,nb,725)
#  define _STSWX(s,a,b)			_FX(31,s,a,b,661)
#  define _STW(s,a,d)			_FDs(36,s,a,d)
#  define _STWBRX(s,a,b)			_FX(31,s,a,b,662)
#  define _STWCX_(s,a,b)			_FX_(31,s,a,b,150)
#  define _STWU(s,a,d)			_FDs(37,s,a,d)
#  define _STWUX(s,a,b)			_FX(31,s,a,b,183)
#  define _STWX(s,a,b)			_FX(31,s,a,b,151)
#  define _STD(s,a,d)			_FDs(62,s,a,d)
#  define _STDX(s,a,b)			_FX(31,s,a,b,149)
#  define _STDCX(s,a,b)                 _FX_(31,s,a,b,214)
#  define _STDU(s,a,d)			_FDs(62,s,a,d|1)
#  define _STDUX(s,a,b)			_FX(31,s,a,b,181)
#  define _SUBF(d,a,b)			_FXO(31,d,a,b,0,40)
#  define _SUBF_(d,a,b)			_FXO_(31,d,a,b,0,40)
#  define _SUBFO(d,a,b)			_FXO(31,d,a,b,1,40)
#  define _SUBFO_(d,a,b)			_FXO_(31,d,a,b,1,40)
#  define _SUB(d,a,b)			_SUBF(d,b,a)
#  define _SUB_(d,a,b)			_SUBF_(d,b,a)
#  define _SUBO(d,a,b)			_SUBFO(d,b,a)
#  define _SUBO_(d,a,b)			_SUBFO_(d,b,a)
#  define _SUBI(d,a,s)			_ADDI(d,a,-s)
#  define _SUBIS(d,a,s)			_ADDIS(d,a,-s)
#  define _SUBFC(d,a,b)			_FXO(31,d,a,b,0,8)
#  define _SUBFC_(d,a,b)			_FXO_(31,d,a,b,0,8)
#  define _SUBFCO(d,a,b)			_FXO(31,d,a,b,1,8)
#  define _SUBFCO_(d,a,b)		_FXO_(31,d,a,b,1,8)
#  define _SUBC(d,a,b)			_SUBFC(d,b,a)
#  define _SUBIC(d,a,s)			_ADDIC(d,a,-s)
#  define _SUBIC_(d,a,s)			_ADDIC_(d,a,-s)
#  define _SUBFE(d,a,b)			_FXO(31,d,a,b,0,136)
#  define _SUBFE_(d,a,b)			_FXO_(31,d,a,b,0,136)
#  define _SUBFEO(d,a,b)			_FXO(31,d,a,b,1,136)
#  define _SUBFEO_(d,a,b)		_FXO_(31,d,a,b,1,136)
#  define _SUBE(d,a,b)			_SUBFE(d,b,a)
#  define _SUBFIC(d,a,s)			_FDs(8,d,a,s)
#  define _SUBFME(d,a)			_FXO(31,d,a,0,0,232)
#  define _SUBFME_(d,a)			_FXO_(31,d,a,0,0,232)
#  define _SUBFMEO(d,a)			_FXO(31,d,a,0,1,232)
#  define _SUBFMEO_(d,a)			_FXO_(31,d,a,0,1,232)
#  define _SUBFZE(d,a)			_FXO(31,d,a,0,0,200)
#  define _SUBFZE_(d,a)			_FXO_(31,d,a,0,0,200)
#  define _SUBFZEO(d,a)			_FXO(31,d,a,0,1,200)
#  define _SUBFZEO_(d,a)			_FXO_(31,d,a,0,1,200)
#  define _SYNC(l, sc)			_FX(31,l,sc,0,598)
#  define _TLBIA()			_FX(31,0,0,0,370)
#  define _TLBIE(b)			_FX(31,0,0,b,306)
#  define _TLBSYNC()			_FX(31,0,0,0,566)
#  define _TW(t,a,b)			_FX(31,t,a,b,4)
#  define _TWEQ(a,b)			_FX(31,4,a,b,4)
#  define _TWLGE(a,b)			_FX(31,5,a,b,4)
#  define _TRAP()			_FX(31,31,0,0,4)
#  define _TWI(t,a,s)			_FDs(3,t,a,s)
#  define _TWGTI(a,s)			_TWI(8,a,s)
#  define _TWLLEI(a,s)			_TWI(6,a,s)
#  define _XOR(d,a,b)			_FX(31,a,d,b,316)
#  define _XOR_(d,a,b)			_FX_(31,a,d,b,316)
#  define _XORI(s,a,u)			_FDu(26,a,s,u)
#  define _XORIS(s,a,u)			_FDu(27,a,s,u)

// Atomics
#  define _LDARX(rt, ra, rb)            _FX(31, rt, ra, rb, 84)
#  define _HWSYNC()                     _SYNC(0, 0)

#if __WORDSIZE == 64
#  define _STX(r0, r1) _STD(r0, r1, 0)
#  define _LXX(r0, r1) _LD(r0, r1, 0)
#  define _CMPX(r0, r1) _CMPD(r0, r1)
#  define _LXARX(r0, r1) _LDARX(r0, 0, r1)
#  define _STXCX(r0, r1) _STDCX(r0, 0, r1)
#else
#  define _STX(r0, r1) _STW(r0, r1, 0)
#  define _LXX(r0, r1) _LW(r0, r1, 0)
#  define _CMPX(r0, r1) _CMPW(r0, r1)
#  define _LXARX(r0, r1) _LWARX(r0, 0, r1)
#  define _STXCX(r0, r1) _STWCX(r0, 0, r1)
#endif

static void nop(jit_state_t*,int32_t);
static void movr(jit_state_t*,int32_t,int32_t);
static void movi(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t mov_addr(jit_state_t *,int32_t);
static jit_reloc_t movi_from_immediate(jit_state_t*,int32_t);
static void emit_immediate_reloc(jit_state_t*,int32_t,jit_bool_t);

static void bswapr_us(jit_state_t*,int32_t,int32_t);
static void bswapr_ui(jit_state_t*,int32_t,int32_t);
static void bswapr_ul(jit_state_t*,int32_t,int32_t);

static void addr(jit_state_t*,int32_t,int32_t,int32_t);
static void addi(jit_state_t*,int32_t,int32_t,jit_word_t);

static void addcr(jit_state_t*,int32_t,int32_t,int32_t);
static void addci(jit_state_t*,int32_t,int32_t,jit_word_t);

static void addxr(jit_state_t*,int32_t,int32_t,int32_t);
static void addxi(jit_state_t*,int32_t,int32_t,jit_word_t);

static void subr(jit_state_t*,int32_t,int32_t,int32_t);
static void subi(jit_state_t*,int32_t,int32_t,jit_word_t);

static void subcr(jit_state_t*,int32_t,int32_t,int32_t);
static void subci(jit_state_t*,int32_t,int32_t,jit_word_t);

static void subxr(jit_state_t*,int32_t,int32_t,int32_t);
static void subxi(jit_state_t*,int32_t,int32_t,jit_word_t);

#  if __WORDSIZE == 32
#    define _MULR(r0,r1,r2)		_MULLW(r0,r1,r2)
#    define _MULLR(r0,r1,r2)		_MULLW(r0,r1,r2)
#    define _MULHR(r0,r1,r2)		_MULHW(r0,r1,r2)
#    define _MULHR_U(r0,r1,r2)		_MULHWU(r0,r1,r2)
#  else
#    define _MULR(r0,r1,r2)		_MULLD(r0,r1,r2)
#    define _MULLR(r0,r1,r2)		_MULLD(r0,r1,r2)
#    define _MULHR(r0,r1,r2)		_MULHD(r0,r1,r2)
#    define _MULHR_U(r0,r1,r2)		_MULHDU(r0,r1,r2)
#  endif

static void mulr(jit_state_t*,int32_t,int32_t,int32_t);
static void muli(jit_state_t*,int32_t,int32_t,jit_word_t);

static void qmulr(jit_state_t*,int32_t,int32_t,int32_t,int32_t);
static void qmulr_u(jit_state_t*,int32_t,int32_t,int32_t,int32_t);
static void iqmulr(jit_state_t*,int32_t,int32_t,
		    int32_t,int32_t,jit_bool_t);

static void qmuli(jit_state_t*,int32_t,int32_t,int32_t,jit_word_t);
static void qmuli_u(jit_state_t*,int32_t,int32_t,int32_t,jit_word_t);
static void iqmuli(jit_state_t*,int32_t,int32_t,
		    int32_t,jit_word_t,jit_bool_t);
#  if __WORDSIZE == 32
#    define _DIVR(r0,r1,r2)		_DIVW(r0,r1,r2)
#  else
#    define _DIVR(r0,r1,r2)		_DIVD(r0,r1,r2)
#  endif

static void divr(jit_state_t*,int32_t,int32_t,int32_t);
static void divi(jit_state_t*,int32_t,int32_t,jit_word_t);

#  if __WORDSIZE == 32
#    define _DIVR_U(r0,r1,r2)		_DIVWU(r0,r1,r2)
#  else
#    define _DIVR_U(r0,r1,r2)		_DIVDU(r0,r1,r2)
#  endif

static void divr_u(jit_state_t*,int32_t,int32_t,int32_t);
static void divi_u(jit_state_t*,int32_t,int32_t,jit_word_t);

static void qdivr(jit_state_t*,int32_t,int32_t,int32_t,int32_t);
static void qdivr_u(jit_state_t*,int32_t,int32_t,int32_t,int32_t);
static void iqdivr(jit_state_t*,int32_t,int32_t,
		    int32_t,int32_t,jit_bool_t);

static void qdivi(jit_state_t*,int32_t,int32_t,int32_t,jit_word_t);
static void qdivi_u(jit_state_t*,int32_t,int32_t,int32_t,jit_word_t);
static void iqdivi(jit_state_t*,int32_t,int32_t,
		    int32_t,jit_word_t,jit_bool_t);

static void remr(jit_state_t*,int32_t,int32_t,int32_t);
static void remi(jit_state_t*,int32_t,int32_t,jit_word_t);
static void remr_u(jit_state_t*,int32_t,int32_t,int32_t);
static void remi_u(jit_state_t*,int32_t,int32_t,jit_word_t);

static void andr(jit_state_t*,int32_t,int32_t,int32_t);
static void andi(jit_state_t*,int32_t,int32_t,jit_word_t);

static void orr(jit_state_t*,int32_t,int32_t,int32_t);
static void ori(jit_state_t*,int32_t,int32_t,jit_word_t);

static void xorr(jit_state_t*,int32_t,int32_t,int32_t);
static void xori(jit_state_t*,int32_t,int32_t,jit_word_t);

#  if __WORDSIZE == 32
#    define _LSHR(r0,r1,r2)		_SLW(r0,r1,r2)
#  else
#    define _LSHR(r0,r1,r2)		_SLD(r0,r1,r2)
#  endif

static void lshr(jit_state_t*,int32_t,int32_t,int32_t);
static void lshi(jit_state_t*,int32_t,int32_t,jit_word_t);

#  if __WORDSIZE == 32
#    define _RSHR(r0,r1,r2)		_SRAW(r0,r1,r2)
#  else
#    define _RSHR(r0,r1,r2)		_SRAD(r0,r1,r2)
#  endif

static void rshr(jit_state_t*,int32_t,int32_t,int32_t);
static void rshi(jit_state_t*,int32_t,int32_t,jit_word_t);

#  if __WORDSIZE == 32
#    define _RSHR_U(r0,r1,r2)		_SRW(r0,r1,r2)
#  else
#    define _RSHR_U(r0,r1,r2)		_SRD(r0,r1,r2)
#  endif

static void rshr_u(jit_state_t*,int32_t,int32_t,int32_t);
static void rshi_u(jit_state_t*,int32_t,int32_t,jit_word_t);

static jit_reloc_t bltr(jit_state_t*,int32_t,int32_t);
static jit_reloc_t blti(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t bltr_u(jit_state_t*,int32_t,int32_t);
static jit_reloc_t blti_u(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t bler(jit_state_t*,int32_t,int32_t);
static jit_reloc_t blei(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t bler_u(jit_state_t*,int32_t,int32_t);
static jit_reloc_t blei_u(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t beqr(jit_state_t*,int32_t,int32_t);
static jit_reloc_t beqi(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t bger(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bgei(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t bger_u(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bgei_u(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t bgtr(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bgti(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t bgtr_u(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bgti_u(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t bner(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bnei(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t bmsr(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bmsi(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t bmcr(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bmci(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t boaddr(jit_state_t*,int32_t,int32_t);
static jit_reloc_t boaddi(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t bxaddr(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bxaddi(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t bosubr(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bosubi(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t bxsubr(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bxsubi(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t boaddr_u(jit_state_t*,int32_t,int32_t);
static jit_reloc_t boaddi_u(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t bxaddr_u(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bxaddi_u(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t bosubr_u(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bosubi_u(jit_state_t*,int32_t,jit_word_t);
static jit_reloc_t bxsubr_u(jit_state_t*,int32_t,int32_t);
static jit_reloc_t bxsubi_u(jit_state_t*,int32_t,jit_word_t);

static void ldr_c(jit_state_t*,int32_t,int32_t);
static void ldi_c(jit_state_t*,int32_t,jit_word_t);
static void ldxr_c(jit_state_t*,int32_t,int32_t,int32_t);
static void ldxi_c(jit_state_t*,int32_t,int32_t,jit_word_t);
static void ldr_uc(jit_state_t*,int32_t,int32_t);
static void ldi_uc(jit_state_t*,int32_t,jit_word_t);
static void ldxr_uc(jit_state_t*,int32_t,int32_t,int32_t);
static void ldxi_uc(jit_state_t*,int32_t,int32_t,jit_word_t);
static void ldr_s(jit_state_t*,int32_t,int32_t);
static void ldi_s(jit_state_t*,int32_t,jit_word_t);
static void ldxr_s(jit_state_t*,int32_t,int32_t,int32_t);
static void ldxi_s(jit_state_t*,int32_t,int32_t,jit_word_t);
static void ldr_us(jit_state_t*,int32_t,int32_t);
static void ldi_us(jit_state_t*,int32_t,jit_word_t);
static void ldxr_us(jit_state_t*,int32_t,int32_t,int32_t);
static void ldxi_us(jit_state_t*,int32_t,int32_t,jit_word_t);

#  if __WORDSIZE == 32
#    define _LDR_I(r0,r1)		_LWZX(r0, rn(_R0), r1)
#  else
#    define _LDR_I(r0,r1)		_LWAX(r0, rn(_R0), r1)
#  endif

static void ldr_i(jit_state_t*,int32_t,int32_t);
static void ldi_i(jit_state_t*,int32_t,jit_word_t);
static void ldxr_i(jit_state_t*,int32_t,int32_t,int32_t);
static void ldxi_i(jit_state_t*,int32_t,int32_t,jit_word_t);

#  if __WORDSIZE == 64
static void ldr_ui(jit_state_t*,int32_t,int32_t);
static void ldi_ui(jit_state_t*,int32_t,jit_word_t);
static void ldxr_ui(jit_state_t*,int32_t,int32_t,int32_t);
static void ldxi_ui(jit_state_t*,int32_t,int32_t,jit_word_t);
static void ldr_l(jit_state_t*,int32_t,int32_t);
static void ldi_l(jit_state_t*,int32_t,jit_word_t);
static void ldxr_l(jit_state_t*,int32_t,int32_t,int32_t);
static void ldxi_l(jit_state_t*,int32_t,int32_t,jit_word_t);
#  endif

static void str_c(jit_state_t*,int32_t,int32_t);
static void sti_c(jit_state_t*,jit_word_t,int32_t);
static void stxr_c(jit_state_t*,int32_t,int32_t,int32_t);
static void stxi_c(jit_state_t*,jit_word_t,int32_t,int32_t);
static void str_s(jit_state_t*,int32_t,int32_t);
static void sti_s(jit_state_t*,jit_word_t,int32_t);
static void stxr_s(jit_state_t*,int32_t,int32_t,int32_t);
static void stxi_s(jit_state_t*,jit_word_t,int32_t,int32_t);
static void str_i(jit_state_t*,int32_t,int32_t);
static void sti_i(jit_state_t*,jit_word_t,int32_t);
static void stxr_i(jit_state_t*,int32_t,int32_t,int32_t);
static void stxi_i(jit_state_t*,jit_word_t,int32_t,int32_t);

#  if __WORDSIZE == 64
static void str_l(jit_state_t*,int32_t,int32_t);
static void sti_l(jit_state_t*,jit_word_t,int32_t);
static void stxr_l(jit_state_t*,int32_t,int32_t,int32_t);
static void stxi_l(jit_state_t*,jit_word_t,int32_t,int32_t);
#  endif

static jit_reloc_t jmp(jit_state_t*);
static void jmpr(jit_state_t*,int32_t);
static void jmpi(jit_state_t*,jit_word_t);
static void callr(jit_state_t*,int32_t);
static void calli(jit_state_t*,jit_word_t);

static void push_link_register(jit_state_t *);
static void pop_link_register(jit_state_t *);

#  define _u16(v)			((v) & 0xffff)
#  define _u26(v)			((v) & 0x3ffffff)
static uint32_t
FXO(int o, int d, int a, int b, int e, int x, int r)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(d & ~((1 << 5) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    assert(!(b & ~((1 << 5) - 1)));
    assert(!(e & ~((1 << 1) - 1)));
    assert(!(x & ~((1 << 9) - 1)));
    assert(!(r & ~((1 << 1) - 1)));
    instr_t ins = {.XO = {.po = o, .rt = d, .ra = a, .rb = b, .u0 = e, .xo = x, .u1 = r}};
    return ins.w;
}

static uint32_t
FDs(int o, int d, int a, int s)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(d & ~((1 << 5) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    assert(can_sign_extend_short_p(s));
    instr_t ins = {.D = {.po = o, .rx = d, .ra = a, .d = _u16(s)}};
    return ins.w;
}

static uint32_t
FDu(int o, int d, int a, int s)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(d & ~((1 << 5) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    assert(can_zero_extend_short_p(s));
    instr_t ins = {.D = {.po = o, .rx = d, .ra = a, .d = _u16(s)}};
    return ins.w;
}

static uint32_t
FX(int o, int s, int a, int b, int x, int r)
{
    assert(!(o & ~((1 <<  6) - 1)));
    assert(!(s & ~((1 <<  5) - 1)));
    assert(!(a & ~((1 <<  5) - 1)));
    assert(!(b & ~((1 <<  5) - 1)));
    assert(!(x & ~((1 << 10) - 1)));
    assert(!(r & ~((1 <<  1) - 1)));
    instr_t ins = {.X = {.po = o, .f0 = s, .ra = a, .rb = b, .xo = x, .u0 = r}};
    return ins.w;
}

static uint32_t
FI(int o, int t, int a, int k)
{
    assert(!(o & ~(( 1 <<  6) - 1)));
    assert(!(t & 3) && can_sign_extend_jump_p(t));
    assert(!(a & ~(( 1 <<  1) - 1)));
    assert(!(k & ~(( 1 <<  1) - 1)));
    instr_t ins = {.I = {.po = o, .li = _u26(t), .aa = a, .lk = k}};
    return ins.w;
}

static uint32_t
FB(int o, int bo, int bi, int t, int a, int k)
{
    assert(!( o & ~((1 <<  6) - 1)));
    assert(!(bo & ~((1 <<  5) - 1)));
    assert(!(bi & ~((1 <<  5) - 1)));
    assert(!(t & 3) && can_sign_extend_short_p(t));
    assert(!(a & ~(( 1 <<  1) - 1)));
    assert(!(k & ~(( 1 <<  1) - 1)));
    instr_t ins = {.B = {.po = o, .bo = bo, .bi = bi, .bd = _u16(t), .aa = a, .lk = k}};
    return ins.w;
}

static uint32_t
FXL(int o, int bo, int bi, int x, int k)
{
    assert(!( o & ~((1 <<  6) - 1)));
    assert(!(bo & ~((1 <<  5) - 1)));
    assert(!(bi & ~((1 <<  5) - 1)));
    assert(!(x & ~(( 1 << 10) - 1)));
    assert(!(k & ~(( 1 <<  1) - 1)));
    instr_t ins = {.XL = {.po = o, .bo = bo, .ba = bi, .bb = 0, .xo = x, .lk = k}};
    return ins.w;
}

static uint32_t
FC(int o, int d, int l, int a, int b, int x)
{
    // NOTE: this seems to one variation on the X format
    assert(!(o & ~((1 <<  6) - 1)));
    assert(!(d & ~((1 <<  3) - 1)));
    assert(!(l & ~((1 <<  1) - 1)));
    assert(!(a & ~((1 <<  5) - 1)));
    assert(!(b & ~((1 <<  5) - 1)));
    assert(!(x & ~((1 << 10) - 1)));
    instr_t ins = {.X = {.po = o, .f0 = d << 3 | l, .ra = a, .rb = b, .xo = x, .u0 = 0}};
    return ins.w;
}

static uint32_t
FCI(int o, int d, int l, int a, int s)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(d & ~((1 << 3) - 1)));
    assert(!(l & ~((1 << 1) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    if (o == 11)	assert(can_sign_extend_short_p(s));
    else if (o == 10)	assert(can_zero_extend_short_p(s));
#if DEBUG
    else		abort();
#endif
    instr_t ins = {.D = {.po = o, .rx = d << 2 | l, .ra = a, .d = _u16(s)}};
    return ins.w;
}

static uint32_t
FXFX(int o, int d, int x, int f)
{
    assert(!(o & ~((1 <<  6) - 1)));
    assert(!(d & ~((1 <<  5) - 1)));
    assert(!(x & ~((1 << 10) - 1)));
    assert(!(f & ~((1 << 10) - 1)));
    instr_t ins = {.XFX = {.po = o, .rs = d, .fx = x, .xo = f, .u0 = 0}};
    return ins.w;
}

static uint32_t
FM(int o, int s, int a, int h, int b, int e, int r)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(s & ~((1 << 5) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    assert(!(h & ~((1 << 5) - 1)));
    assert(!(b & ~((1 << 5) - 1)));
    assert(!(e & ~((1 << 5) - 1)));
    assert(!(r & ~((1 << 1) - 1)));
    instr_t ins = {.M = {.po = o, .rs = s, .ra = a, .rb = h, .mb = b, .me = e, .rc = r}};
    return ins.w;
}

#  if __WORDSIZE == 64
static uint32_t
FMD(int o, int s, int a, int h, int e, int x, int i, int r)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(s & ~((1 << 5) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    assert(!(h & ~((1 << 5) - 1)));
    assert(!(e & ~((1 << 6) - 1)));
    assert(!(x & ~((1 << 3) - 1)));
    assert(!(i & ~((1 << 1) - 1)));
    assert(!(r & ~((1 << 1) - 1)));
    e = (e >> 5) | ((e << 1) & 63);
    instr_t ins = {.MD = {.po = o, .rs = s, .ra = a, .s0 = h, .mx = e, .xo = x, .s1 = i, .rc = r}};
    return ins.w;
}

static uint32_t
FXS(int o, int s, int a, int h, int x, int i, int r)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(s & ~((1 << 5) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    assert(!(h & ~((1 << 5) - 1)));
    assert(!(x & ~((1 << 9) - 1)));
    assert(!(i & ~((1 << 1) - 1)));
    assert(!(r & ~((1 << 1) - 1)));
    instr_t ins = {.XS = {.po = o, .rs = s, .ra = a, .s0 = h, .xo = x, .s1 = i, .rc = r}};
    return ins.w;
}
#endif

#if !DEBUG
/*
 * Use the sequence commented at
 * http://tenfourfox.blogspot.com/2011/04/attention-g5-owners-your-javascript-no.html
 */
static void
mcrxr(jit_state_t *_jit, int32_t cr)
{
    int32_t reg = rn(get_temp_gpr(_jit));
    em_wp(_jit, _MFXER(reg));
    em_wp(_jit, _MTCRF(128, reg));
    em_wp(_jit, _RLWINM(reg, reg, 0, 0, 28));
    em_wp(_jit, _MTXER(reg));
    unget_temp_gpr(_jit);
}

#else
static void
mcrxr(jit_state_t *_jit, int32_t cr)
{
    em_wp(_jit, _FX(31, cr << 2, 0, 0, 512));
}
#endif

static int32_t
read_jmp_offset(uint32_t *loc)
{
    // FIXME unsigned to signed?
    instr_t *i = (instr_t *)loc;
    return i->I.li;
}

static int32_t
read_jcc_offset(uint32_t *loc)
{
    instr_t *i = (instr_t *)loc;
    return i->B.bd;
}

static void
patch_jmp_offset(uint32_t *loc, ptrdiff_t offset)
{
    assert(simm24_p(offset));
    instr_t *i = (instr_t *)loc;
    i->I.li = offset;
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
    jit_pointer_t veneer = jit_address(_jit);

    jit_gpr_t reg = get_temp_gpr(_jit);
    emit_immediate_reloc(_jit, rn(reg), 1);

    // see mips-cpu.c:emit_veneer()
    if (!jit_has_overflow(_jit))
	patch_veneer(veneer, target);

    emit_u32(_jit, _MTCTR(rn(reg)));
    emit_u32(_jit, _BCTR());
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
    return simm24_p(offset);
}

static int
offset_in_jcc_range(ptrdiff_t offset, int flags)
{
    (void)flags;
    return simm14_p(offset);
}

static void
patch_jcc_offset(uint32_t *loc, ptrdiff_t offset)
{
    assert(simm14_p(offset));
    instr_t *i = (instr_t *)loc;
    i->B.bd = offset;
}

static uint32_t
patch_cc_jump(uint32_t inst, int32_t offset)
{
    instr_t i;
    i.w = inst;
    i.B.bd = offset;
    return i.w;
}

static jit_reloc_t
emit_cc_jump(jit_state_t *_jit, uint32_t inst)
{
    while (1) {
	uint8_t *pc_base = _jit->pc.uc;
	int32_t off = ((uint8_t *)jit_address(_jit)) - pc_base;
	jit_reloc_t w = jit_reloc(_jit, JIT_RELOC_JCC_WITH_VENEER, 0, _jit->pc.uc,
		pc_base,
		2);
	uint8_t jump_width = 16;

	if (add_pending_literal(_jit, w, jump_width - 1)) {
	    em_wp(_jit, patch_cc_jump(inst, off >> 2));
	    return w;
	}
    }
}

static jit_reloc_t
emit_atomic_jump(jit_state_t *_jit, uint32_t inst)
{
    while (1) {
	uint8_t *pc_base = _jit->pc.uc;
	int32_t off = ((uint8_t *)jit_address(_jit)) - pc_base;
	jit_reloc_t w = jit_reloc(_jit, JIT_RELOC_JCC_WITH_VENEER, 0, _jit->pc.uc,
		pc_base,
		2);
	uint8_t jump_width = 16;

	// TODO is JCC_WITH_VENEER fine here?
	if (add_pending_literal(_jit, w, jump_width - 1)) {
	    emit_u32(_jit, patch_cc_jump(inst, off >> 2));
	    return w;
	}
    }
}

static uint32_t patch_jump(uint32_t inst, int32_t offset)
{
    instr_t i;
    i.w = inst;
    i.I.li = offset;
    return i.w;
}

static jit_reloc_t
emit_jump(jit_state_t *_jit, uint32_t inst)
{
    while(1) {
	uint8_t *pc_base = _jit->pc.uc;
	int32_t off = ((uint8_t *)jit_address(_jit)) - pc_base;
	jit_reloc_t w = jit_reloc(_jit, JIT_RELOC_JMP_WITH_VENEER, 0, _jit->pc.uc,
		pc_base,
		2);
	uint8_t jump_width = 26;

	if (add_pending_literal(_jit, w, jump_width - 1)) {
	    em_wp(_jit, patch_jump(inst, off >> 2));
	    return w;
	}
    }
}

static void
nop(jit_state_t *_jit, int32_t i0)
{
    for (; i0 > 0; i0 -= 4)
	em_wp(_jit, _NOP());
    assert(i0 == 0);
}

static void
movr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    if (r0 != r1)
	em_wp(_jit, _MR(r0, r1));
}

static void
movi(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    if (can_sign_extend_short_p(i0))
	em_wp(_jit, _LI(r0, i0));
    else {
	if (can_sign_extend_int_p(i0))
	    em_wp(_jit, _LIS(r0, (int16_t)(i0 >> 16)));
	else if (can_zero_extend_int_p(i0)) {
	    if (i0 & 0xffff0000) {
		em_wp(_jit, _ORI(r0, r0, (uint16_t)(i0 >> 16)));
		em_wp(_jit, _SLWI(r0, r0, 16));
	    }
	}
#  if __WORDSIZE == 64
	else {
	    movi(_jit, r0, (uint32_t)(i0 >> 32));
	    if (i0 & 0xffff0000) {
		em_wp(_jit, _SLDI(r0, r0, 16));
		em_wp(_jit, _ORI(r0, r0, (uint16_t)(i0 >> 16)));
		em_wp(_jit, _SLDI(r0, r0, 16));
	    }
	    else
		em_wp(_jit, _SLDI(r0, r0, 32));
	}
#  endif
	if (i0 & 0xffff)
	    em_wp(_jit, _ORI(r0, r0, (uint16_t)i0));
    }
}

typedef struct {
#if __WORDSIZE == 64
	instr_t lis0;
	instr_t ori0;
	instr_t sldi0;

	instr_t ori1;
	instr_t sldi1;
	instr_t ori2;
#else
	instr_t lis;
	instr_t ori;
#endif
} immediate_t;

static void
patch_immediate_reloc(uint32_t *loc, jit_pointer_t addr)
{
    immediate_t *i = (immediate_t *)loc;
    jit_word_t a = (jit_word_t)addr;
#if __WORDSIZE == 64
    i->lis0.D.d = a >> 48;
    i->ori0.D.d = a >> 32;
    i->ori1.D.d = a >> 16;
    i->ori2.D.d = a & 0xffff;
#else
    i->lis.D.d = a >> 16;
    i->ori.D.d = a & 0xffff;
#endif
}

static void
emit_immediate_reloc(jit_state_t *_jit, int32_t r0, jit_bool_t in_veneer)
{
    void (*emit)(jit_state_t * _jit, uint32_t u32) =
	    in_veneer ? emit_u32 : emit_u32_with_pool;

    emit(_jit, _LIS(r0, 0));
    emit(_jit, _ORI(r0, r0, 0));
#  if __WORDSIZE == 64
    emit(_jit, _SLDI(r0, r0, 16));
    emit(_jit, _ORI(r0, r0, 0));
    emit(_jit, _SLDI(r0, r0, 16));
    emit(_jit, _ORI(r0, r0, 0));
#  endif
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
negr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	em_wp(_jit, _NEG(r0, r1));
}

static void
comr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	em_wp(_jit, _NOT(r0, r1));
}

static void
extr_c(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _EXTSB(r0, r1));
}

static void
extr_uc(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _ANDI_(r0, r1, 0xff));
}

static void
extr_s(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _EXTSH(r0, r1));
}

static void
extr_us(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _ANDI_(r0, r1, 0xffff));
}

#  if __BYTE_ORDER == __LITTLE_ENDIAN
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
    jit_gpr_t reg = get_temp_gpr(_jit);
    em_wp(_jit, _ROTLWI(rn(reg), r1, 8));
    em_wp(_jit, _RLWIMI(rn(reg), r1, 24, 0, 7));
    em_wp(_jit, _RLWIMI(rn(reg), r1, 24, 16, 23));
    em_wp(_jit, _CLRLDI(r0, rn(reg), 32));
    unget_temp_gpr(_jit);
}

#    if __WORDSIZE == 64
static void
bswapr_ul(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    rshi_u(_jit, rn(reg), r1, 32);
    bswapr_ui(_jit, r0, r1);
    bswapr_ui(_jit, rn(reg), rn(reg));
    lshi(_jit, r0, r0, 32);
    orr(_jit, r0, r0, rn(reg));
    unget_temp_gpr(_jit);
}
#    endif
#  endif

static void
addr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _ADD(r0, r1, r2));
}

static void
addi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (can_sign_extend_short_p(i0))
	em_wp(_jit, _ADDI(r0, r1, i0));
    else if (can_zero_extend_int_p(i0) && !(i0 & 0x0000ffff))
	em_wp(_jit, _ADDIS(r0, r1, i0 >> 16));
    else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	em_wp(_jit, _ADD(r0, r1, rn(reg)));
	unget_temp_gpr(_jit);
    }
}

static void
addcr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _ADDC(r0, r1, r2));
}

static void
addci(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (can_sign_extend_short_p(i0))
	em_wp(_jit, _ADDIC(r0, r1, i0));
    else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	addcr(_jit, r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
addxr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _ADDE(r0, r1, r2));
}

static void
addxi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    movi(_jit, rn(reg), i0);
    addxr(_jit, r0, r1, rn(reg));
    unget_temp_gpr(_jit);
}

static void
subr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _SUB(r0, r1, r2));
}

static void
subi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    jit_word_t ni0 = -i0;
    if (can_sign_extend_short_p(ni0)) {
	em_wp(_jit, _ADDI(r0, r1, ni0));
    } else if (can_zero_extend_int_p(ni0) && !(ni0 & 0x0000ffff)) {
	em_wp(_jit, _ADDIS(r0, r1, ni0 >> 16));
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	subr(_jit, r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
subcr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _SUBC(r0, r1, r2));
}

static void
subci(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    movi(_jit, rn(reg), i0);
    subcr(_jit, r0, r1, rn(reg));
    unget_temp_gpr(_jit);
}

static void
subxr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _SUBFE(r0, r2, r1));
}

static void
subxi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    movi(_jit, rn(reg), i0);
    subxr(_jit, r0, rn(reg), r1);
    unget_temp_gpr(_jit);
}

static void
mulr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _MULR(r0, r1, r2));
}

static void
muli(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (can_sign_extend_short_p(i0))
	em_wp(_jit, _MULLI(r0, r1, i0));
    else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	mulr(_jit, r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
iqmulr(jit_state_t *_jit, int32_t r0, int32_t r1,
	int32_t r2, int32_t r3, jit_bool_t sign)
{
    jit_gpr_t reg;
    if (r0 == r2 || r0 == r3) {
	reg = get_temp_gpr(_jit);
	em_wp(_jit, _MULLR(rn(reg), r2, r3));
    } else {
	em_wp(_jit, _MULLR(r0, r2, r3));
    }

    if (sign)
	em_wp(_jit, _MULHR(r1, r2, r3));
    else
	em_wp(_jit, _MULHR_U(r1, r2, r3));

    if (r0 == r2 || r0 == r3) {
	movr(_jit, r0, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
qmulr(jit_state_t *_jit, int32_t r0, int32_t r1,
	int32_t r2, int32_t r3)
{
    iqmulr(_jit, r0, r1, r2, r3, 1);
}

static void
qmulr_u(jit_state_t *_jit, int32_t r0, int32_t r1,
	int32_t r2, int32_t r3)
{
    iqmulr(_jit, r0, r1, r2, r3, 0);
}

static void
iqmuli(jit_state_t *_jit, int32_t r0, int32_t r1,
	int32_t r2, jit_word_t i0, jit_bool_t sign)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    movi(_jit, rn(reg), i0);
    iqmulr(_jit, r0, r1, r2, rn(reg), sign);
    unget_temp_gpr(_jit);
}

static void
qmuli(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2,
	jit_word_t i0)
{
    iqmuli(_jit, r0, r1, r2, i0, 1);
}

static void
qmuli_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2,
	jit_word_t i0)
{
    iqmuli(_jit, r0, r1, r2, i0, 0);
}

static void
divr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _DIVR(r0, r1, r2));
}

static void
divi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    movi(_jit, rn(reg), i0);
    divr(_jit, r0, r1, rn(reg));
    unget_temp_gpr(_jit);
}

static void
divr_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _DIVR_U(r0, r1, r2));
}

static void
divi_u(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    movi(_jit, rn(reg), i0);
    divr_u(_jit, r0, r1, rn(reg));
    unget_temp_gpr(_jit);
}

static void
iqdivr(jit_state_t *_jit, int32_t r0, int32_t r1,
	int32_t r2, int32_t r3, jit_bool_t sign)
{
    jit_gpr_t sv0; int32_t rg0;
    jit_gpr_t sv1; int32_t rg1;

    if (r0 == r2 || r0 == r3) {
	sv0 = get_temp_gpr(_jit);
	rg0 = rn(sv0);
    } else {
	rg0 = r0;
    }

    if (r1 == r2 || r1 == r3) {
	sv1 = get_temp_gpr(_jit);
	rg1 = rn(sv1);
    } else {
	rg1 = r1;
    }

    if (sign)
	divr(_jit, rg0, r2, r3);
    else
	divr_u(_jit, rg0, r2, r3);

    mulr(_jit, rg1, r3, rg0);
    subr(_jit, rg1, r2, rg1);

    if (rg0 != r0) {
	movr(_jit, r0, rg0);
	unget_temp_gpr(_jit);
    }

    if (rg1 != r1) {
	movr(_jit, r1, rg1);
	unget_temp_gpr(_jit);
    }
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
iqdivi(jit_state_t *_jit, int32_t r0, int32_t r1,
	int32_t r2, jit_word_t i0, jit_bool_t sign)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    movi(_jit, rn(reg), i0);
    iqdivr(_jit, r0, r1, r2, rn(reg), sign);
    unget_temp_gpr(_jit);
}

static void
qdivi(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, jit_word_t i0)
{
    iqdivi(_jit, r0, r1, r2, i0, 1);
}

static void
qdivi_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, jit_word_t u0)
{
    iqdivi(_jit, r0, r1, r2, u0, 0);
}

static void
remr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    if (r0 == r1 || r0 == r2) {
	jit_gpr_t reg = get_temp_gpr(_jit);
	divr(_jit, rn(reg), r1, r2);
	mulr(_jit, rn(reg), r2, rn(reg));
	subr(_jit, r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
    else {
	divr(_jit, r0, r1, r2);
	mulr(_jit, r0, r2, r0);
	subr(_jit, r0, r1, r0);
    }
}

static void
remi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    movi(_jit, rn(reg), i0);
    remr(_jit, r0, r1, rn(reg));
    unget_temp_gpr(_jit);
}

static void
remr_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    if (r0 == r1 || r0 == r2) {
	jit_gpr_t reg = get_temp_gpr(_jit);
	divr_u(_jit, rn(reg), r1, r2);
	mulr(_jit, rn(reg), r2, rn(reg));
	subr(_jit, r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
    else {
	divr_u(_jit, r0, r1, r2);
	mulr(_jit, r0, r2, r0);
	subr(_jit, r0, r1, r0);
    }
}

static void
remi_u(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    movi(_jit, rn(reg), i0);
    remr_u(_jit, r0, r1, rn(reg));
    unget_temp_gpr(_jit);
}

static void
andr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _AND(r0, r1, r2));
}

static void
andi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (can_zero_extend_short_p(i0)) {
	em_wp(_jit, _ANDI_(r0, r1, i0));
    } else if (can_zero_extend_int_p(i0) && !(i0 & 0x0000ffff)) {
	em_wp(_jit, _ANDIS_(r0, r1, (jit_uword_t)i0 >> 16));
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	em_wp(_jit, _AND(r0, r1, rn(reg)));
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
    if (can_zero_extend_short_p(i0)) {
	em_wp(_jit, _ORI(r0, r1, i0));
    } else if (can_zero_extend_int_p(i0) && !(i0 & 0x0000ffff)) {
	em_wp(_jit, _ORIS(r0, r1, (jit_uword_t)i0 >> 16));
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	orr(_jit, r0, r1, rn(reg));
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
    if (can_zero_extend_short_p(i0)) {
	em_wp(_jit, _XORI(r0, r1, i0));
    } else if (can_zero_extend_int_p(i0) && !(i0 & 0x0000ffff)) {
	em_wp(_jit, _XORIS(r0, r1, (jit_uword_t)i0 >> 16));
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	xorr(_jit, r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
lshr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _LSHR(r0, r1, r2));
}

static void
lshi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (i0 == 0) {
	movr(_jit, r0, r1);
    } else {
#  if __WORDSIZE == 32
	em_wp(_jit, _SLWI(r0, r1, i0));
#  else
	em_wp(_jit, _SLDI(r0, r1, i0));
#  endif
    }
}

static void
rshr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _RSHR(r0, r1, r2));
}

static void
rshi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (i0 == 0) {
	movr(_jit, r0, r1);
    } else {
#  if __WORDSIZE == 32
	em_wp(_jit, _SRAWI(r0, r1, i0));
#  else
	em_wp(_jit, _SRADI(r0, r1, i0));
#  endif
    }
}

static void
rshr_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    em_wp(_jit, _RSHR_U(r0, r1, r2));
}

static void
rshi_u(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (i0 == 0) {
	movr(_jit, r0, r1);
    } else {
#  if __WORDSIZE == 32
	em_wp(_jit, _SRWI(r0, r1, i0));
#  else
	em_wp(_jit, _SRDI(r0, r1, i0));
#  endif
    }
}

static jit_reloc_t
bltr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _CMPW(r0, r1));
    return emit_cc_jump(_jit, _BLT(0));
}

static jit_reloc_t
blti(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    if (can_sign_extend_short_p(i1)) {
	em_wp(_jit, _CMPWI(r0, i1));
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i1);
	em_wp(_jit, _CMPW(r0, rn(reg)));
	unget_temp_gpr(_jit);
    }

    return emit_cc_jump(_jit, _BLT(0));
}

static jit_reloc_t
bltr_u(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _CMPLW(r0, r1));
    return emit_cc_jump(_jit, _BLT(0));
}

static jit_reloc_t
blti_u(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    if (can_zero_extend_short_p(i1)) {
	em_wp(_jit, _CMPLWI(r0, i1));
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i1);
	em_wp(_jit, _CMPLW(r0, rn(reg)));
	unget_temp_gpr(_jit);
    }

    return emit_cc_jump(_jit, _BLT(0));
}

static jit_reloc_t
bler(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _CMPW(r0, r1));
    return emit_cc_jump(_jit, _BLE(0));
}

static jit_reloc_t
blei(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    if (can_sign_extend_short_p(i1)) {
	em_wp(_jit, _CMPWI(r0, i1));
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i1);
	em_wp(_jit, _CMPW(r0, rn(reg)));
	unget_temp_gpr(_jit);
    }

    return emit_cc_jump(_jit, _BLE(0));
}

static jit_reloc_t
bler_u(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _CMPLW(r0, r1));
    return emit_cc_jump(_jit, _BLE(0));
}

static jit_reloc_t
blei_u(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    if (can_zero_extend_short_p(i1)) {
	em_wp(_jit, _CMPLWI(r0, i1));
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i1);
	em_wp(_jit, _CMPLW(r0, rn(reg)));
	unget_temp_gpr(_jit);
    }

    return emit_cc_jump(_jit, _BLE(0));
}

static jit_reloc_t
beqr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _CMPW(r0, r1));
    return emit_cc_jump(_jit, _BEQ(0));
}

static jit_reloc_t
beqi(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    if (can_sign_extend_short_p(i1)) {
	em_wp(_jit, _CMPWI(r0, i1));
    } else if (can_zero_extend_short_p(i1)) {
	em_wp(_jit, _CMPLWI(r0, i1));
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i1);
	em_wp(_jit, _CMPW(r0, rn(reg)));
	unget_temp_gpr(_jit);
    }

    return emit_cc_jump(_jit, _BEQ(0));
}

static jit_reloc_t
bger(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _CMPW(r0, r1));
    return emit_cc_jump(_jit, _BGE(0));
}

static jit_reloc_t
bgei(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    if (can_sign_extend_short_p(i1)) {
	em_wp(_jit, _CMPWI(r0, i1));
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i1);
	em_wp(_jit, _CMPW(r0, rn(reg)));
	unget_temp_gpr(_jit);
    }

    return emit_cc_jump(_jit, _BGE(0));
}

static jit_reloc_t
bger_u(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _CMPLW(r0, r1));
    return emit_cc_jump(_jit, _BGE(0));
}

static jit_reloc_t
bgei_u(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    if (can_zero_extend_short_p(i1)) {
	em_wp(_jit, _CMPLWI(r0, i1));
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i1);
	em_wp(_jit, _CMPLW(r0, rn(reg)));
	unget_temp_gpr(_jit);
    }
    return emit_cc_jump(_jit, _BGE(0));
}

static jit_reloc_t
bgtr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _CMPW(r0, r1));
    return emit_cc_jump(_jit, _BGT(0));
}

static jit_reloc_t
bgti(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    if (can_sign_extend_short_p(i1)) {
	em_wp(_jit, _CMPWI(r0, i1));
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i1);
	em_wp(_jit, _CMPW(r0, rn(reg)));
	unget_temp_gpr(_jit);
    }
    return emit_cc_jump(_jit, _BGT(0));
}

static jit_reloc_t
bgtr_u(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _CMPLW(r0, r1));
    return emit_cc_jump(_jit, _BGT(0));
}

static jit_reloc_t
bgti_u(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    if (can_zero_extend_short_p(i1)) {
	em_wp(_jit, _CMPLWI(r0, i1));
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i1);
	em_wp(_jit, _CMPLW(r0, rn(reg)));
	unget_temp_gpr(_jit);
    }

    return emit_cc_jump(_jit, _BGT(0));
}

static jit_reloc_t
bner(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _CMPW(r0, r1));
    return emit_cc_jump(_jit, _BNE(0));
}

static jit_reloc_t
bnei(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    if (can_sign_extend_short_p(i1)) {
	em_wp(_jit, _CMPWI(r0, i1));
    } else if (can_zero_extend_short_p(i1)) {
	em_wp(_jit, _CMPLWI(r0, i1));
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i1);
	em_wp(_jit, _CMPW(r0, rn(reg)));
	unget_temp_gpr(_jit);
    }

    return emit_cc_jump(_jit, _BNE(0));
}

static jit_reloc_t
bmsr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    andr(_jit, rn(reg), r0, r1);
    jit_reloc_t w = bnei(_jit, rn(reg), 0);
    unget_temp_gpr(_jit);
    return w;
}

static jit_reloc_t
bmsi(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    andi(_jit, rn(reg), r0, i1);
    jit_reloc_t w = bnei(_jit, rn(reg), 0);
    unget_temp_gpr(_jit);
    return w;
}

static jit_reloc_t
bmcr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    andr(_jit, rn(reg), r0, r1);
    jit_reloc_t w = beqi(_jit, rn(reg), 0);
    unget_temp_gpr(_jit);
    return w;
}

static jit_reloc_t
bmci(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    andi(_jit, rn(reg), r0, i1);
    jit_reloc_t w = beqi(_jit, rn(reg), 0);
    unget_temp_gpr(_jit);
    return w;
}

static jit_reloc_t
boaddr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _ADDO(r0, r0, r1));
    mcrxr(_jit, CR_0);
    return emit_cc_jump(_jit, _BGT(0));				/* GT = bit 1 of XER = OV */
}

static jit_reloc_t
boaddi(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    movi(_jit, rn(reg), i1);
    jit_reloc_t w = boaddr(_jit, r0, rn(reg));
    unget_temp_gpr(_jit);
    return w;
}

static jit_reloc_t
bxaddr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _ADDO(r0, r0, r1));
    mcrxr(_jit, CR_0);
    return emit_cc_jump(_jit, _BLE(0));
}

static jit_reloc_t
bxaddi(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    movi(_jit, rn(reg), i1);
    jit_reloc_t w = bxaddr(_jit, r0, rn(reg));
    unget_temp_gpr(_jit);
    return w;
}

static jit_reloc_t
bosubr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _SUBO(r0, r0, r1));
    mcrxr(_jit, CR_0);
    return emit_cc_jump(_jit, _BGT(0));
}

static jit_reloc_t
bosubi(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    movi(_jit, rn(reg), i1);
    jit_reloc_t w = bosubr(_jit, r0, rn(reg));
    unget_temp_gpr(_jit);
    return w;
}

static jit_reloc_t
bxsubr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _SUBO(r0, r0, r1));
    mcrxr(_jit, CR_0);
    return emit_cc_jump(_jit, _BLE(0));
}

static jit_reloc_t
bxsubi(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    movi(_jit, rn(reg), i1);
    jit_reloc_t w = bxsubr(_jit, r0, rn(reg));
    unget_temp_gpr(_jit);
    return w;
}

static jit_reloc_t
boaddr_u(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _ADDC(r0, r0, r1));
    mcrxr(_jit, CR_0);
    return emit_cc_jump(_jit, _BEQ(0));				/* EQ = bit 2 of XER = CA */
}

static jit_reloc_t
boaddi_u(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    if (can_sign_extend_short_p(i1)) {
	em_wp(_jit, _ADDIC(r0, r0, i1));
	mcrxr(_jit, CR_0);
	return emit_cc_jump(_jit, _BEQ(0));
    }

    jit_gpr_t reg = get_temp_gpr(_jit);
    movi(_jit, rn(reg), i1);
    jit_reloc_t w = boaddr_u(_jit, r0, rn(reg));
    unget_temp_gpr(_jit);
    return w;
}

static jit_reloc_t
bxaddr_u(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _ADDC(r0, r0, r1));
    mcrxr(_jit, CR_0);
    return emit_cc_jump(_jit, _BNE(0));
}

static jit_reloc_t
bxaddi_u(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    if (can_sign_extend_short_p(i1)) {
	em_wp(_jit, _ADDIC(r0, r0, i1));
	mcrxr(_jit, CR_0);
	return emit_cc_jump(_jit, _BNE(0));
    }

    jit_gpr_t reg = get_temp_gpr(_jit);
    movi(_jit, rn(reg), i1);
    jit_reloc_t w = bxaddr_u(_jit, r0, rn(reg));
    unget_temp_gpr(_jit);
    return w;
}

static jit_reloc_t
bosubr_u(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _SUBC(r0, r0, r1));
    mcrxr(_jit, CR_0);
    return emit_cc_jump(_jit, _BNE(0));				/* PPC uses "carry" not "borrow" */
}

static jit_reloc_t
bosubi_u(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    movi(_jit, rn(reg), i1);
    jit_reloc_t w = bosubr_u(_jit, r0, rn(reg));
    unget_temp_gpr(_jit);
    return w;
}

static jit_reloc_t
bxsubr_u(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _SUBC(r0, r0, r1));
    mcrxr(_jit, CR_0);
    return emit_cc_jump(_jit, _BEQ(0));
}

static jit_reloc_t
bxsubi_u(jit_state_t *_jit, int32_t r0, jit_word_t i1)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    movi(_jit, rn(reg), i1);
    jit_reloc_t w = bxsubr_u(_jit, r0, rn(reg));
    unget_temp_gpr(_jit);
    return w;
}

#if __WORDSIZE == 64
static void
extr_i(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _EXTSW(r0, r1));
}

static void
extr_ui(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _CLRLDI(r0, r1, 32));
}
#endif

static void
ldr_c(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    ldr_uc(_jit, r0, r1);
    extr_c(_jit, r0, r0);
}

static void
ldi_c(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    ldi_uc(_jit, r0, i0);
    extr_c(_jit, r0, r0);
}

static void
ldxr_c(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    ldxr_uc(_jit, r0, r1, r2);
    extr_c(_jit, r0, r0);
}

static void
ldxi_c(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    ldxi_uc(_jit, r0, r1, i0);
    extr_c(_jit, r0, r0);
}

static void
ldr_uc(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _LBZX(r0, rn(_R0), r1));
}

static void
ldi_uc(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    if (can_sign_extend_short_p(i0)) {
	em_wp(_jit, _LBZ(r0, rn(_R0), i0));
    } else if (can_sign_extend_int_p(i0)) {
	jit_word_t hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	jit_word_t lo = (int16_t)(i0 - (hi << 16));
	jit_gpr_t reg = get_temp_gpr(_jit);
	em_wp(_jit, _LIS(rn(reg), hi));
	em_wp(_jit, _LBZ(r0, rn(reg), lo));
	unget_temp_gpr(_jit);
    }
    else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	ldr_uc(_jit, r0, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldxr_uc(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    if (r1 == rn(_R0)) {
	if (r2 != rn(_R0)) {
	    em_wp(_jit, _LBZX(r0, r2, r1));
	} else {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _LBZX(r0, rn(reg), r2));
	    unget_temp_gpr(_jit);
	}
    } else {
	em_wp(_jit, _LBZX(r0, r1, r2));
    }
}

static void
ldxi_uc(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (i0 == 0) {
	ldr_uc(_jit, r0, r1);
    } else if (can_sign_extend_short_p(i0)) {
	if (r1 == rn(_R0)) {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _LBZ(r0, rn(reg), i0));
	    unget_temp_gpr(_jit);
	} else {
	    em_wp(_jit, _LBZ(r0, r1, i0));
	}
    }
    else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	ldxr_uc(_jit, r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldr_s(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _LHAX(r0, rn(_R0), r1));
}

static void
ldi_s(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    if (can_sign_extend_short_p(i0)) {
	em_wp(_jit, _LHA(r0, rn(_R0), i0));
    } else if (can_sign_extend_int_p(i0)) {
	jit_word_t hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	jit_word_t lo = (int16_t)(i0 - (hi << 16));
	jit_gpr_t reg = get_temp_gpr(_jit);
	em_wp(_jit, _LIS(rn(reg), hi));
	em_wp(_jit, _LHA(r0, rn(reg), lo));
	unget_temp_gpr(_jit);
    }
    else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	ldr_s(_jit, r0, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldxr_s(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    if (r1 == rn(_R0)) {
	if (r2 != rn(_R0)) {
	    em_wp(_jit, _LHAX(r0, r2, r1));
	} else {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _LHAX(r0, rn(reg), r2));
	    unget_temp_gpr(_jit);
	}
    } else {
	em_wp(_jit, _LHAX(r0, r1, r2));
    }
}

static void
ldxi_s(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (i0 == 0) {
	ldr_s(_jit, r0, r1);
    } else if (can_sign_extend_short_p(i0)) {
	if (r1 == rn(_R0)) {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _LHA(r0, rn(reg), i0));
	    unget_temp_gpr(_jit);
	} else {
	    em_wp(_jit, _LHA(r0, r1, i0));
	}
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	ldxr_s(_jit, r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldr_us(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _LHZX(r0, rn(_R0), r1));
}

static void
ldi_us(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    if (can_sign_extend_short_p(i0)) {
	em_wp(_jit, _LHZ(r0, rn(_R0), i0));
    } else if (can_sign_extend_int_p(i0)) {
	jit_word_t hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	jit_word_t lo = (int16_t)(i0 - (hi << 16));
	jit_gpr_t reg = get_temp_gpr(_jit);
	em_wp(_jit, _LIS(rn(reg), hi));
	em_wp(_jit, _LHZ(r0, rn(reg), lo));
	unget_temp_gpr(_jit);
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	ldr_us(_jit, r0, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldxr_us(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    if (r1 == rn(_R0)) {
	if (r2 != rn(_R0)) {
	    em_wp(_jit, _LHZX(r0, r2, r1));
	} else {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _LHZX(r0, rn(reg), r2));
	    unget_temp_gpr(_jit);
	}
    } else {
	em_wp(_jit, _LHZX(r0, r1, r2));
    }
}

static void
ldxi_us(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (i0 == 0) {
	ldr_us(_jit, r0, r1);
    } else if (can_sign_extend_short_p(i0)) {
	if (r1 == rn(_R0)) {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _LHZ(r0, rn(reg), i0));
	    unget_temp_gpr(_jit);
	} else {
	    em_wp(_jit, _LHZ(r0, r1, i0));
	}
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	ldxr_us(_jit, r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldr_i(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _LDR_I(r0, r1));
}

#  if __WORDSIZE == 32
static void
ldi_i(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    if (can_sign_extend_short_p(i0)) {
	LWZ(r0, rn(_R0), i0);
    } else if (can_sign_extend_int_p(i0)) {
	jit_word_t hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	jit_word_t lo = (int16_t)(i0 - (hi << 16));
	jit_gpr_t reg = get_temp_gpr(_jit);
	em_wp(_jit, _LIS(rn(reg), hi));
	em_wp(_jit, _LWZ(r0, rn(reg), lo));
	unget_temp_gpr(_jit);
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	ldr_i(_jit, r0, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldxr_i(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    if (r1 == rn(_R0)) {
	if (r2 != rn(_R0)) {
	    em_wp(_jit, _LWZX(r0, r2, r1));
	} else {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _LWZX(r0, rn(reg), r2));
	    unget_temp_gpr(_jit);
	}
    } else {
	em_wp(_jit, _LWZX(r0, r1, r2));
    }
}

static void
ldxi_i(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (i0 == 0) {
	ldr_i(_jit, r0, r1);
    } else if (can_sign_extend_short_p(i0)) {
	if (r1 == rn(_R0)) {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _LW(r0, rn(reg), i0));
	    unget_temp_gpr(_jit);
	} else {
	    em_wp(_jit, _LW(r0, r1, i0));
	}
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	ldxr_i(_jit, r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

#  else
static void
ldi_i(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    if (can_sign_extend_short_p(i0)) {
	em_wp(_jit, _LWA(r0, rn(_R0), i0));
    } else if (can_sign_extend_int_p(i0)) {
	jit_word_t hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	jit_word_t lo = (int16_t)(i0 - (hi << 16));
	jit_gpr_t reg = get_temp_gpr(_jit);
	em_wp(_jit, _LIS(rn(reg), hi));
	em_wp(_jit, _LWA(r0, rn(reg), lo));
	unget_temp_gpr(_jit);
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	ldr_i(_jit, r0, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldxr_i(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    if (r1 == rn(_R0)) {
	if (r2 != rn(_R0)) {
	    em_wp(_jit, _LWAX(r0, r2, r1));
	} else {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _LWAX(r0, rn(reg), r2));
	    unget_temp_gpr(_jit);
	}
    } else {
	em_wp(_jit, _LWAX(r0, r1, r2));
    }
}

static void
ldxi_i(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (i0 == 0) {
	ldr_i(_jit, r0, r1);
    } else if (can_sign_extend_short_p(i0)) {
	if (r1 == rn(_R0)) {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _LWA(r0, rn(reg), i0));
	    unget_temp_gpr(_jit);
	} else {
	    em_wp(_jit, _LWA(r0, r1, i0));
	}
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	ldxr_i(_jit, r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldr_ui(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _LWZX(r0, rn(_R0), r1));
}

static void
ldi_ui(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    if (can_sign_extend_short_p(i0)) {
	em_wp(_jit, _LWZ(r0, rn(_R0), i0));
    } else if (can_sign_extend_int_p(i0)) {
	jit_word_t hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	jit_word_t lo = (int16_t)(i0 - (hi << 16));
	jit_gpr_t reg = get_temp_gpr(_jit);
	em_wp(_jit, _LIS(rn(reg), hi));
	em_wp(_jit, _LWZ(r0, rn(reg), lo));
	unget_temp_gpr(_jit);
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	ldr_ui(_jit, r0, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldxr_ui(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    if (r1 == rn(_R0)) {
	if (r2 != rn(_R0)) {
	    em_wp(_jit, _LWZX(r0, r2, r1));
	} else {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _LWZX(r0, rn(reg), r2));
	    unget_temp_gpr(_jit);
	}
    } else {
	em_wp(_jit, _LWZX(r0, r1, r2));
    }
}

static void
ldxi_ui(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (i0 == 0) {
	ldr_i(_jit, r0, r1);
    } else if (can_sign_extend_short_p(i0)) {
	if (r1 == rn(_R0)) {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _LWZ(r0, rn(reg), i0));
	    unget_temp_gpr(_jit);
	} else {
	    em_wp(_jit, _LWZ(r0, r1, i0));
	}
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	ldxr_ui(_jit, r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldr_l(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _LDX(r0, rn(_R0), r1));
}

static void
ldi_l(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    if (can_sign_extend_short_p(i0)) {
	em_wp(_jit, _LD(r0, rn(_R0), i0));
    } else if (can_sign_extend_int_p(i0)) {
	jit_word_t hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	jit_word_t lo = (int16_t)(i0 - (hi << 16));
	jit_gpr_t reg = get_temp_gpr(_jit);
	em_wp(_jit, _LIS(rn(reg), hi));
	em_wp(_jit, _LD(r0, rn(reg), lo));
	unget_temp_gpr(_jit);
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	ldr_l(_jit, r0, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldxr_l(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    if (r1 == rn(_R0)) {
	if (r2 != rn(_R0)) {
	    em_wp(_jit, _LDX(r0, r2, r1));
	} else {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _LDX(r0, rn(reg), r2));
	    unget_temp_gpr(_jit);
	}
    } else {
	em_wp(_jit, _LDX(r0, r1, r2));
    }
}

static void
ldxi_l(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (i0 == 0) {
	ldr_l(_jit, r0, r1);
    } else if (can_sign_extend_short_p(i0)) {
	if (r1 == rn(_R0)) {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r1);
	    em_wp(_jit, _LD(r0, rn(reg), i0));
	    unget_temp_gpr(_jit);
	} else {
	    em_wp(_jit, _LD(r0, r1, i0));
	}
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	ldxr_l(_jit, r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}
#  endif

static void
str_c(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _STBX(r1, rn(_R0), r0));
}

static void
sti_c(jit_state_t *_jit, jit_word_t i0, int32_t r0)
{
    if (can_sign_extend_short_p(i0)) {
	em_wp(_jit, _STB(r0, rn(_R0), i0));
    } else if (can_sign_extend_int_p(i0)) {
	jit_word_t hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	jit_word_t lo = (int16_t)(i0 - (hi << 16));
	jit_gpr_t reg = get_temp_gpr(_jit);
	em_wp(_jit, _LIS(rn(reg), hi));
	em_wp(_jit, _STB(r0, rn(reg), lo));
	unget_temp_gpr(_jit);
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	str_c(_jit, rn(reg), r0);
	unget_temp_gpr(_jit);
    }
}

static void
stxr_c(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    if (r0 == rn(_R0)) {
	if (r1 != rn(_R0)) {
	    em_wp(_jit, _STBX(r2, r1, r0));
	} else {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r0);
	    em_wp(_jit, _STBX(r2, rn(reg), r1));
	    unget_temp_gpr(_jit);
	}
    } else {
	em_wp(_jit, _STBX(r2, r0, r1));
    }
}

static void
stxi_c(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    if (i0 == 0) {
	str_c(_jit, r0, r1);
    } else if (can_sign_extend_short_p(i0)) {
	if (r0 == rn(_R0)) {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), i0);
	    em_wp(_jit, _STB(r1, rn(reg), i0));
	    unget_temp_gpr(_jit);
	} else {
	    em_wp(_jit, _STB(r1, r0, i0));
	}
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	stxr_c(_jit, rn(reg), r0, r1);
	unget_temp_gpr(_jit);
    }
}

static void
str_s(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _STHX(r1, rn(_R0), r0));
}

static void
sti_s(jit_state_t *_jit, jit_word_t i0, int32_t r0)
{
    if (can_sign_extend_short_p(i0)) {
	em_wp(_jit, _STH(r0, rn(_R0), i0));
    } else if (can_sign_extend_int_p(i0)) {
	jit_word_t hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	jit_word_t lo = (int16_t)(i0 - (hi << 16));
	jit_gpr_t reg = get_temp_gpr(_jit);
	em_wp(_jit, _LIS(rn(reg), hi));
	em_wp(_jit, _STH(r0, rn(reg), lo));
	unget_temp_gpr(_jit);
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit,rn(reg), i0);
	str_s(_jit, rn(reg), r0);
	unget_temp_gpr(_jit);
    }
}

static void
stxr_s(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    if (r0 == rn(_R0)) {
	if (r1 != rn(_R0)) {
	    em_wp(_jit, _STHX(r2, r1, r0));
	} else {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r0);
	    em_wp(_jit, _STHX(r2, rn(reg), r1));
	    unget_temp_gpr(_jit);
	}
    } else {
	em_wp(_jit, _STHX(r2, r0, r1));
    }
}

static void
stxi_s(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    if (i0 == 0) {
	str_s(_jit, r0, r1);
    } else if (can_sign_extend_short_p(i0)) {
	if (r0 == rn(_R0)) {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), i0);
	    em_wp(_jit, _STH(r1, rn(reg), i0));
	    unget_temp_gpr(_jit);
	} else {
	    em_wp(_jit, _STH(r1, r0, i0));
	}
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	stxr_s(_jit, rn(reg), r0, r1);
	unget_temp_gpr(_jit);
    }
}

static void
str_i(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _STWX(r1, rn(_R0), r0));
}

static void
sti_i(jit_state_t *_jit, jit_word_t i0, int32_t r0)
{
    if (can_sign_extend_short_p(i0)) {
	em_wp(_jit, _STW(r0, rn(_R0), i0));
    } else if (can_sign_extend_int_p(i0)) {
	jit_word_t hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	jit_word_t lo = (int16_t)(i0 - (hi << 16));
	jit_gpr_t reg = get_temp_gpr(_jit);
	em_wp(_jit, _LIS(rn(reg), hi));
	em_wp(_jit, _STW(r0, rn(reg), lo));
	unget_temp_gpr(_jit);
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	str_i(_jit, rn(reg), r0);
	unget_temp_gpr(_jit);
    }
}

static void
stxr_i(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    if (r0 == rn(_R0)) {
	if (r1 != rn(_R0)) {
	    em_wp(_jit, _STWX(r2, r1, r0));
	} else {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r0);
	    em_wp(_jit, _STWX(r2, rn(reg), r1));
	    unget_temp_gpr(_jit);
	}
    } else {
	em_wp(_jit, _STWX(r2, r0, r1));
    }
}

static void
stxi_i(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    if (i0 == 0) {
	str_i(_jit, r0, r1);
    } else if (can_sign_extend_short_p(i0)) {
	if (r0 == rn(_R0)) {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), i0);
	    em_wp(_jit, _STW(r1, rn(reg), i0));
	    unget_temp_gpr(_jit);
	} else {
	    em_wp(_jit, _STW(r1, r0, i0));
	}
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	stxr_i(_jit, rn(reg), r0, r1);
	unget_temp_gpr(_jit);
    }
}

#  if __WORDSIZE == 64
static void
str_l(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    em_wp(_jit, _STDX(r1, rn(_R0), r0));
}

static void
sti_l(jit_state_t *_jit, jit_word_t i0, int32_t r0)
{
    if (can_sign_extend_short_p(i0)) {
	em_wp(_jit, _STD(r0, rn(_R0), i0));
    } else if (can_sign_extend_int_p(i0)) {
	jit_word_t hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	jit_word_t lo = (int16_t)(i0 - (hi << 16));
	jit_gpr_t reg = get_temp_gpr(_jit);
	em_wp(_jit, _LIS(rn(reg), hi));
	em_wp(_jit, _STD(r0, rn(reg), lo));
	unget_temp_gpr(_jit);
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	str_l(_jit, rn(reg), r0);
	unget_temp_gpr(_jit);
    }
}

static void
stxr_l(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    if (r0 == rn(_R0)) {
	if (r1 != rn(_R0)) {
	    em_wp(_jit, _STDX(r2, r1, r0));
	} else {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), r0);
	    em_wp(_jit, _STDX(r2, rn(reg), r1));
	    unget_temp_gpr(_jit);
	}
    } else {
	em_wp(_jit, _STDX(r2, r0, r1));
    }
}

static void
stxi_l(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    if (i0 == 0) {
	str_l(_jit, r0, r1);
    } else if (can_sign_extend_short_p(i0)) {
	if (r0 == rn(_R0)) {
	    jit_gpr_t reg = get_temp_gpr(_jit);
	    movr(_jit, rn(reg), i0);
	    em_wp(_jit, _STD(r1, rn(reg), i0));
	    unget_temp_gpr(_jit);
	} else {
	    em_wp(_jit, _STD(r1, r0, i0));
	}
    } else {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	stxr_l(_jit, rn(reg), r0, r1);
	unget_temp_gpr(_jit);
    }
}
#  endif

static void
jmpr(jit_state_t *_jit, int32_t r0)
{
    em_wp(_jit, _MTCTR(r0));
    em_wp(_jit, _BCTR());
}

static void
jmpi_with_link(jit_state_t *_jit, jit_word_t i0)
{
    calli(_jit, i0);
}

static void
jmpi(jit_state_t *_jit, jit_word_t i0)
{
    jit_gpr_t reg = get_temp_gpr(_jit);
    movi(_jit, rn(reg), i0);
    jmpr(_jit, rn(reg));
    unget_temp_gpr(_jit);
}

static jit_reloc_t
jmp(jit_state_t *_jit)
{
    return emit_jump(_jit, _B(0));
}

// TODO this might not be required in lightening?
static void
callr(jit_state_t *_jit, int32_t r0)
{
#  if __powerpc__
#    if ABI_ELFv2
    movr(_jit, rn(_R12), r0);
#    else
    stxi(_jit, sizeof(void*) * 5, rn(JIT_SP), rn(_R2));
    /* FIXME Pretend to not know about r11? */
    if (r0 == rn(_R0)) {
	movr(_jit, rn(_R11), rn(_R0));
	ldxi(_jit, rn(_R2), rn(_R11), sizeof(void*));
	ldxi(_jit, rn(_R11), rn(_R11), sizeof(void*) * 2);
    }
    else {
	ldxi(_jit, rn(_R2), r0, sizeof(void*));
	ldxi(_jit, rn(_R11), r0, sizeof(void*) * 2);
    }
    ldr(_jit, r0, r0);
#    endif
#  endif

    em_wp(_jit, _MTCTR(r0));
    em_wp(_jit, _BCTRL());

#  if __powerpc__ && !ABI_ELFv2
    ldxi(_jit, rn(_R2), rn(_SP), sizeof(void*) * 5);
#  endif
}

/* assume fixed address or reachable address */
static void
calli(jit_state_t *_jit, jit_word_t i0)
{
#  if __ppc__
    if (can_sign_extend_jump_p(i0)) {
	em_wp(_jit, _BL(i0));
    } else
#  endif
    {
	jit_gpr_t reg = get_temp_gpr(_jit);
	movi(_jit, rn(reg), i0);
	callr(_jit, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ret(jit_state_t *_jit)
{
    em_wp(_jit, _BLR());
}

static void
retr(jit_state_t *_jit, int32_t u)
{
    if (rn(JIT_RET) != u)
	movr(_jit, rn(JIT_RET), u);

    ret(_jit);
}

static void
reti(jit_state_t *_jit, jit_word_t u)
{
    movi(_jit, rn(JIT_RET), u);
    ret(_jit);
}


static void
retval_c(jit_state_t *_jit, int32_t r0)
{
    extr_c(_jit, r0, rn(JIT_RET));
}

static void
retval_uc(jit_state_t *_jit, int32_t r0)
{
    extr_uc(_jit, r0, rn(JIT_RET));
}

static void
retval_s(jit_state_t *_jit, int32_t r0)
{
    extr_s(_jit, r0, rn(JIT_RET));
}

static void
retval_us(jit_state_t *_jit, int32_t r0)
{
    extr_us(_jit, r0, rn(JIT_RET));
}

static void
retval_i(jit_state_t *_jit, int32_t r0)
{
#if __WORDSIZE == 32
    if (r0 != rn(JIT_RET))
	movr(_jit, r0, rn(JIT_RET));
#else
    extr_i(_jit, r0, rn(JIT_RET));
#endif
}

#if __WORDSIZE == 64
static void
retval_ui(jit_state_t *_jit, int32_t r0)
{
    extr_ui(_jit, r0, rn(JIT_RET));
}

static void
retval_l(jit_state_t *_jit, int32_t r0)
{
    if (r0 != rn(JIT_RET))
	movr(_jit, r0, rn(JIT_RET));
}
#endif

// TODO: atomics
static void
ldr_atomic(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    // TODO long vs int?
    emit_u32(_jit, _HWSYNC());
    emit_u32(_jit, _LXX(r0, r1));
    emit_u32(_jit, _CMPX(r0, r0));
    jit_reloc_t w = emit_cc_jump(_jit, _BNE(0));
    jit_patch_here(_jit, w);
    emit_u32(_jit, _ISYNC());
}

static void
str_atomic(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    emit_u32(_jit, _HWSYNC());
    emit_u32(_jit, _STX(r1, r0));
}

static void
swap_atomic(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    // if r0 == r1, we might overwrite something if we didn't use temporaries
    jit_gpr_t t0 = get_temp_gpr(_jit);

    emit_u32(_jit, _HWSYNC());
    jit_pointer_t a = jit_address(_jit);
    emit_u32(_jit, _LXARX(rn(t0), r1));
    emit_u32(_jit, _STXCX(r2, r1));
    jit_reloc_t w = emit_atomic_jump(_jit, _BNE(0));
    jit_patch_there(_jit, w, a);
    emit_u32(_jit, _ISYNC());
    movr(_jit, r0, rn(t0));

    unget_temp_gpr(_jit);
}

static void
cas_atomic(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2, int32_t r3)
{
    jit_gpr_t t0 = get_temp_gpr(_jit);

    emit_u32(_jit, _HWSYNC());
    jit_pointer_t loop = jit_address(_jit);
    emit_u32(_jit, _LXARX(rn(t0), r1));
    emit_u32(_jit, _CMPX(r2, rn(t0)));

    jit_reloc_t s = emit_atomic_jump(_jit, _BNE(0));

    emit_u32(_jit, _STXCX(r3, r1));

    jit_reloc_t w = emit_atomic_jump(_jit, _BNE(0));

    jit_patch_here(_jit, s);

    jit_patch_there(_jit, w, loop);

    emit_u32(_jit, _ISYNC());
    movr(_jit, r0, r1);
    unget_temp_gpr(_jit);
}

static void
pop_link_register(jit_state_t *_jit)
{
    em_wp(_jit, _MFLR(rn(_R0)));
}

static void
push_link_register(jit_state_t *_jit)
{
    em_wp(_jit, _MTLR(rn(_R0)));
}

static void
breakpoint(jit_state_t *_jit)
{
    (void)_jit;
}
