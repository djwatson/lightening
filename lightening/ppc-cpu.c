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


static int32_t FXO(int,int,int,int,int,int,int);
static int32_t FDs(int,int,int,int);
static int32_t FDu(int,int,int,int);
static int32_t FX(int,int,int,int,int,int);
static int32_t FI(int,int,int,int);
static int32_t FB(int,int,int,int,int,int);
static int32_t FXL(int,int,int,int,int);
static int32_t FC(int,int,int,int,int,int);
static int32_t FCI(int,int,int,int,int);
static int32_t FXFX(int,int,int,int);
static int32_t FM(int,int,int,int,int,int,int);

#  if __WORDSIZE == 64
static int32_t FMDS(int,int,int,int,int,int,int);
static int32_t FMD(int,int,int,int,int,int,int,int);
static int32_t FXS(int,int,int,int,int,int,int);
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
#  define _SYNC()			_FX(31,0,0,0,598)
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
static void nop(jit_state_t*,int32_t);
static void movr(jit_state_t*,int32_t,int32_t);
static void movi(jit_state_t*,int32_t,jit_word_t);
static jit_word_t movi_p(jit_state_t*,int32_t,jit_word_t);
#  if __WORDSIZE == 64
#    define extr_i(r0,r1)		EXTSW(r0,r1)
#    define extr_ui(r0,r1)		CLRLDI(r0,r1,32)
#  endif
#  if __BYTE_ORDER == __BIG_ENDIAN
#    define bswapr_us(r0,r1)		extr_us(r0,r1)
#    if __WORDSIZE == 32
#      define bswapr_ui(r0,r1)		movr(r0,r1)
#    else
#      define bswapr_ui(r0,r1)		extr_ui(r0,r1)
#      define bswapr_ul(r0,r1)		movr(r0,r1)
#    endif
#  else
#    define bswapr_us(r0,r1)		_bswapr_us(_jit,r0,r1)
static void _bswapr_us(jit_state_t*,int32_t,int32_t);
#    define bswapr_ui(r0,r1)		_bswapr_ui(_jit,r0,r1)
static void _bswapr_ui(jit_state_t*,int32_t,int32_t);
#    if __WORDSIZE == 64
#      define bswapr_ul(r0,r1)		_bswapr_ul(_jit,r0,r1)
static void _bswapr_ul(jit_state_t*,int32_t,int32_t);
#    endif
#  endif
#  define addr(r0,r1,r2)		ADD(r0,r1,r2)
#  define addi(r0,r1,i0)		_addi(_jit,r0,r1,i0)
static void _addi(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define addcr(r0,r1,r2)		ADDC(r0,r1,r2)
#  define addci(r0,r1,i0)		_addci(_jit,r0,r1,i0)
static void _addci(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define addxr(r0,r1,r2)		ADDE(r0,r1,r2)
#  define addxi(r0,r1,i0)		_addxi(_jit,r0,r1,i0)
static void _addxi(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define subr(r0,r1,r2)		SUB(r0,r1,r2)
#  define subi(r0,r1,i0)		_subi(_jit,r0,r1,i0)
static void _subi(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define subcr(r0,r1,r2)		SUBC(r0,r1,r2)
#  define subci(r0,r1,i0)		_subci(_jit,r0,r1,i0)
static void _subci(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define subxr(r0,r1,r2)		SUBFE(r0,r2,r1)
#  define subxi(r0,r1,i0)		_subxi(_jit,r0,r1,i0)
static void _subxi(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define rsbi(r0, r1, i0)		_rsbi(_jit, r0, r1, i0)
static void _rsbi(jit_state_t*,int32_t,int32_t,jit_word_t);
#  if __WORDSIZE == 32
#    define mulr(r0,r1,r2)		MULLW(r0,r1,r2)
#    define mullr(r0,r1,r2)		MULLW(r0,r1,r2)
#    define mulhr(r0,r1,r2)		MULHW(r0,r1,r2)
#    define mulhr_u(r0,r1,r2)		MULHWU(r0,r1,r2)
#  else
#    define mulr(r0,r1,r2)		MULLD(r0,r1,r2)
#    define mullr(r0,r1,r2)		MULLD(r0,r1,r2)
#    define mulhr(r0,r1,r2)		MULHD(r0,r1,r2)
#    define mulhr_u(r0,r1,r2)		MULHDU(r0,r1,r2)
#  endif
#  define muli(r0,r1,i0)		_muli(_jit,r0,r1,i0)
static void _muli(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define qmulr(r0,r1,r2,r3)		iqmulr(r0,r1,r2,r3,1)
#  define qmulr_u(r0,r1,r2,r3)		iqmulr(r0,r1,r2,r3,0)
#  define iqmulr(r0,r1,r2,r3,cc)	_iqmulr(_jit,r0,r1,r2,r3,cc)
static void _iqmulr(jit_state_t*,int32_t,int32_t,
		    int32_t,int32_t,jit_bool_t);
#  define qmuli(r0,r1,r2,i0)		iqmuli(r0,r1,r2,i0,1)
#  define qmuli_u(r0,r1,r2,i0)		iqmuli(r0,r1,r2,i0,0)
#  define iqmuli(r0,r1,r2,i0,cc)	_iqmuli(_jit,r0,r1,r2,i0,cc)
static void _iqmuli(jit_state_t*,int32_t,int32_t,
		    int32_t,jit_word_t,jit_bool_t);
#  if __WORDSIZE == 32
#    define divr(r0,r1,r2)		DIVW(r0,r1,r2)
#  else
#    define divr(r0,r1,r2)		DIVD(r0,r1,r2)
#  endif
#  define divi(r0,r1,i0)		_divi(_jit,r0,r1,i0)
static void _divi(jit_state_t*,int32_t,int32_t,jit_word_t);
#  if __WORDSIZE == 32
#    define divr_u(r0,r1,r2)		DIVWU(r0,r1,r2)
#  else
#    define divr_u(r0,r1,r2)		DIVDU(r0,r1,r2)
#  endif
#  define divi_u(r0,r1,i0)		_divi_u(_jit,r0,r1,i0)
static void _divi_u(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define qdivr(r0,r1,r2,r3)		iqdivr(r0,r1,r2,r3,1)
#  define qdivr_u(r0,r1,r2,r3)		iqdivr(r0,r1,r2,r3,0)
#  define iqdivr(r0,r1,r2,r3,cc)	_iqdivr(_jit,r0,r1,r2,r3,cc)
static void _iqdivr(jit_state_t*,int32_t,int32_t,
		    int32_t,int32_t,jit_bool_t);
#  define qdivi(r0,r1,r2,i0)		iqdivi(r0,r1,r2,i0,1)
#  define qdivi_u(r0,r1,r2,i0)		iqdivi(r0,r1,r2,i0,0)
#  define iqdivi(r0,r1,r2,i0,cc)	_iqdivi(_jit,r0,r1,r2,i0,cc)
static void _iqdivi(jit_state_t*,int32_t,int32_t,
		    int32_t,jit_word_t,jit_bool_t);
#  define remr(r0,r1,r2)		_remr(_jit,r0,r1,r2)
static void _remr(jit_state_t*,int32_t,int32_t,int32_t);
#  define remi(r0,r1,i0)		_remi(_jit,r0,r1,i0)
static void _remi(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define remr_u(r0,r1,r2)		_remr_u(_jit,r0,r1,r2)
static void _remr_u(jit_state_t*,int32_t,int32_t,int32_t);
#  define remi_u(r0,r1,i0)		_remi_u(_jit,r0,r1,i0)
static void _remi_u(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define andr(r0,r1,r2)		AND(r0,r1,r2)
#  define andi(r0,r1,i0)		_andi(_jit,r0,r1,i0)
static void _andi(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define orr(r0,r1,r2)			OR(r0,r1,r2)
#  define ori(r0,r1,i0)			_ori(_jit,r0,r1,i0)
static void _ori(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define xorr(r0,r1,r2)		XOR(r0,r1,r2)
#  define xori(r0,r1,i0)		_xori(_jit,r0,r1,i0)
static void _xori(jit_state_t*,int32_t,int32_t,jit_word_t);
#  if __WORDSIZE == 32
#    define lshr(r0,r1,r2)		SLW(r0,r1,r2)
#  else
#    define lshr(r0,r1,r2)		SLD(r0,r1,r2)
#  endif
#  define lshi(r0,r1,i0)		_lshi(_jit,r0,r1,i0)
static void _lshi(jit_state_t*,int32_t,int32_t,jit_word_t);
#  if __WORDSIZE == 32
#    define rshr(r0,r1,r2)		SRAW(r0,r1,r2)
#  else
#    define rshr(r0,r1,r2)		SRAD(r0,r1,r2)
#  endif
#  define rshi(r0,r1,i0)		_rshi(_jit,r0,r1,i0)
static void _rshi(jit_state_t*,int32_t,int32_t,jit_word_t);
#  if __WORDSIZE == 32
#    define rshr_u(r0,r1,r2)		SRW(r0,r1,r2)
#  else
#    define rshr_u(r0,r1,r2)		SRD(r0,r1,r2)
#  endif
#  define rshi_u(r0,r1,i0)		_rshi_u(_jit,r0,r1,i0)
static void _rshi_u(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define ltr(r0,r1,r2)			_ltr(_jit,r0,r1,r2)
static void _ltr(jit_state_t*,int32_t,int32_t,int32_t);
#  define lti(r0,r1,i0)			_lti(_jit,r0,r1,i0)
static void _lti(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define ltr_u(r0,r1,r2)		_ltr_u(_jit,r0,r1,r2)
static void _ltr_u(jit_state_t*,int32_t,int32_t,int32_t);
#  define lti_u(r0,r1,i0)		_lti_u(_jit,r0,r1,i0)
static void _lti_u(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define ler(r0,r1,r2)			_ler(_jit,r0,r1,r2)
static void _ler(jit_state_t*,int32_t,int32_t,int32_t);
#  define lei(r0,r1,i0)			_lei(_jit,r0,r1,i0)
static void _lei(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define ler_u(r0,r1,r2)		_ler_u(_jit,r0,r1,r2)
static void _ler_u(jit_state_t*,int32_t,int32_t,int32_t);
#  define lei_u(r0,r1,i0)		_lei_u(_jit,r0,r1,i0)
static void _lei_u(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define eqr(r0,r1,r2)			_eqr(_jit,r0,r1,r2)
static void _eqr(jit_state_t*,int32_t,int32_t,int32_t);
#  define eqi(r0,r1,i0)			_eqi(_jit,r0,r1,i0)
static void _eqi(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define ger(r0,r1,r2)			_ger(_jit,r0,r1,r2)
static void _ger(jit_state_t*,int32_t,int32_t,int32_t);
#  define gei(r0,r1,i0)			_gei(_jit,r0,r1,i0)
static void _gei(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define ger_u(r0,r1,r2)		_ger_u(_jit,r0,r1,r2)
static void _ger_u(jit_state_t*,int32_t,int32_t,int32_t);
#  define gei_u(r0,r1,i0)		_gei_u(_jit,r0,r1,i0)
static void _gei_u(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define gtr(r0,r1,r2)			_gtr(_jit,r0,r1,r2)
static void _gtr(jit_state_t*,int32_t,int32_t,int32_t);
#  define gti(r0,r1,i0)			_gti(_jit,r0,r1,i0)
static void _gti(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define gtr_u(r0,r1,r2)		_gtr_u(_jit,r0,r1,r2)
static void _gtr_u(jit_state_t*,int32_t,int32_t,int32_t);
#  define gti_u(r0,r1,i0)		_gti_u(_jit,r0,r1,i0)
static void _gti_u(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define ner(r0,r1,r2)			_ner(_jit,r0,r1,r2)
static void _ner(jit_state_t*,int32_t,int32_t,int32_t);
#  define nei(r0,r1,i0)			_nei(_jit,r0,r1,i0)
static void _nei(jit_state_t*,int32_t,int32_t,jit_word_t);
#define bltr(i0,r0,r1)			_bltr(_jit,i0,r0,r1)
static jit_word_t _bltr(jit_state_t*,jit_word_t,int32_t,int32_t);
#define blti(i0,r0,i1)			_blti(_jit,i0,r0,i1)
static jit_word_t _blti(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define bltr_u(i0,r0,r1)		_bltr_u(_jit,i0,r0,r1)
static jit_word_t _bltr_u(jit_state_t*,jit_word_t,int32_t,int32_t);
#define blti_u(i0,r0,i1)		_blti_u(_jit,i0,r0,i1)
static jit_word_t _blti_u(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define bler(i0,r0,r1)			_bler(_jit,i0,r0,r1)
static jit_word_t _bler(jit_state_t*,jit_word_t,int32_t,int32_t);
#define blei(i0,r0,i1)			_blei(_jit,i0,r0,i1)
static jit_word_t _blei(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define bler_u(i0,r0,r1)		_bler_u(_jit,i0,r0,r1)
static jit_word_t _bler_u(jit_state_t*,jit_word_t,int32_t,int32_t);
#define blei_u(i0,r0,i1)		_blei_u(_jit,i0,r0,i1)
static jit_word_t _blei_u(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define beqr(i0,r0,r1)			_beqr(_jit,i0,r0,r1)
static jit_word_t _beqr(jit_state_t*,jit_word_t,int32_t,int32_t);
#define beqi(i0,r0,i1)			_beqi(_jit,i0,r0,i1)
static jit_word_t _beqi(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define bger(i0,r0,r1)			_bger(_jit,i0,r0,r1)
static jit_word_t _bger(jit_state_t*,jit_word_t,int32_t,int32_t);
#define bgei(i0,r0,i1)			_bgei(_jit,i0,r0,i1)
static jit_word_t _bgei(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define bger_u(i0,r0,r1)		_bger_u(_jit,i0,r0,r1)
static jit_word_t _bger_u(jit_state_t*,jit_word_t,int32_t,int32_t);
#define bgei_u(i0,r0,i1)		_bgei_u(_jit,i0,r0,i1)
static jit_word_t _bgei_u(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define bgtr(i0,r0,r1)			_bgtr(_jit,i0,r0,r1)
static jit_word_t _bgtr(jit_state_t*,jit_word_t,int32_t,int32_t);
#define bgti(i0,r0,i1)			_bgti(_jit,i0,r0,i1)
static jit_word_t _bgti(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define bgtr_u(i0,r0,r1)		_bgtr_u(_jit,i0,r0,r1)
static jit_word_t _bgtr_u(jit_state_t*,jit_word_t,int32_t,int32_t);
#define bgti_u(i0,r0,i1)		_bgti_u(_jit,i0,r0,i1)
static jit_word_t _bgti_u(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define bner(i0,r0,r1)			_bner(_jit,i0,r0,r1)
static jit_word_t _bner(jit_state_t*,jit_word_t,int32_t,int32_t);
#define bnei(i0,r0,i1)			_bnei(_jit,i0,r0,i1)
static jit_word_t _bnei(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define bmsr(i0,r0,r1)			_bmsr(_jit,i0,r0,r1)
static jit_word_t _bmsr(jit_state_t*,jit_word_t,int32_t,int32_t);
#define bmsi(i0,r0,i1)			_bmsi(_jit,i0,r0,i1)
static jit_word_t _bmsi(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define bmcr(i0,r0,r1)			_bmcr(_jit,i0,r0,r1)
static jit_word_t _bmcr(jit_state_t*,jit_word_t,int32_t,int32_t);
#define bmci(i0,r0,i1)			_bmci(_jit,i0,r0,i1)
static jit_word_t _bmci(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define boaddr(i0,r0,r1)		_boaddr(_jit,i0,r0,r1)
static jit_word_t _boaddr(jit_state_t*,jit_word_t,int32_t,int32_t);
#define boaddi(i0,r0,i1)		_boaddi(_jit,i0,r0,i1)
static jit_word_t _boaddi(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define bxaddr(i0,r0,r1)		_bxaddr(_jit,i0,r0,r1)
static jit_word_t _bxaddr(jit_state_t*,jit_word_t,int32_t,int32_t);
#define bxaddi(i0,r0,i1)		_bxaddi(_jit,i0,r0,i1)
static jit_word_t _bxaddi(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define bosubr(i0,r0,r1)		_bosubr(_jit,i0,r0,r1)
static jit_word_t _bosubr(jit_state_t*,jit_word_t,int32_t,int32_t);
#define bosubi(i0,r0,i1)		_bosubi(_jit,i0,r0,i1)
static jit_word_t _bosubi(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define bxsubr(i0,r0,r1)		_bxsubr(_jit,i0,r0,r1)
static jit_word_t _bxsubr(jit_state_t*,jit_word_t,int32_t,int32_t);
#define bxsubi(i0,r0,i1)		_bxsubi(_jit,i0,r0,i1)
static jit_word_t _bxsubi(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define boaddr_u(i0,r0,r1)		_boaddr_u(_jit,i0,r0,r1)
static jit_word_t _boaddr_u(jit_state_t*,jit_word_t,int32_t,int32_t);
#define boaddi_u(i0,r0,i1)		_boaddi_u(_jit,i0,r0,i1)
static jit_word_t _boaddi_u(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define bxaddr_u(i0,r0,r1)		_bxaddr_u(_jit,i0,r0,r1)
static jit_word_t _bxaddr_u(jit_state_t*,jit_word_t,int32_t,int32_t);
#define bxaddi_u(i0,r0,i1)		_bxaddi_u(_jit,i0,r0,i1)
static jit_word_t _bxaddi_u(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define bosubr_u(i0,r0,r1)		_bosubr_u(_jit,i0,r0,r1)
static jit_word_t _bosubr_u(jit_state_t*,jit_word_t,int32_t,int32_t);
#define bosubi_u(i0,r0,i1)		_bosubi_u(_jit,i0,r0,i1)
static jit_word_t _bosubi_u(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#define bxsubr_u(i0,r0,r1)		_bxsubr_u(_jit,i0,r0,r1)
static jit_word_t _bxsubr_u(jit_state_t*,jit_word_t,int32_t,int32_t);
#define bxsubi_u(i0,r0,i1)		_bxsubi_u(_jit,i0,r0,i1)
static jit_word_t _bxsubi_u(jit_state_t*,jit_word_t,int32_t,jit_word_t);
#  define ldr_c(r0,r1)			_ldr_c(_jit,r0,r1)
static void _ldr_c(jit_state_t*,int32_t,int32_t);
#  define ldi_c(r0,i0)			_ldi_c(_jit,r0,i0)
static void _ldi_c(jit_state_t*,int32_t,jit_word_t);
#  define ldxr_c(r0,r1,i0)		_ldxr_c(_jit,r0,r1,i0)
static void _ldxr_c(jit_state_t*,int32_t,int32_t,int32_t);
#  define ldxi_c(r0,r1,i0)		_ldxi_c(_jit,r0,r1,i0)
static void _ldxi_c(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define ldr_uc(r0,r1)			LBZX(r0, rn(_R0), r1)
#  define ldi_uc(r0,i0)			_ldi_uc(_jit,r0,i0)
static void _ldi_uc(jit_state_t*,int32_t,jit_word_t);
#  define ldxr_uc(r0,r1,r2)		_ldxr_uc(_jit,r0,r1,r2)
static void _ldxr_uc(jit_state_t*,int32_t,int32_t,int32_t);
#  define ldxi_uc(r0,r1,i0)		_ldxi_uc(_jit,r0,r1,i0)
static void _ldxi_uc(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define ldr_s(r0,r1)			LHAX(r0, rn(_R0), r1)
#  define ldi_s(r0,i0)			_ldi_s(_jit,r0,i0)
static void _ldi_s(jit_state_t*,int32_t,jit_word_t);
#  define ldxr_s(r0,r1,i0)		_ldxr_s(_jit,r0,r1,i0)
static void _ldxr_s(jit_state_t*,int32_t,int32_t,int32_t);
#  define ldxi_s(r0,r1,i0)		_ldxi_s(_jit,r0,r1,i0)
static void _ldxi_s(jit_state_t*,int32_t,int32_t,jit_word_t);
#  define ldr_us(r0,r1)			LHZX(r0, rn(_R0), r1)
#  define ldi_us(r0,i0)			_ldi_us(_jit,r0,i0)
static void _ldi_us(jit_state_t*,int32_t,jit_word_t);
#  define ldxr_us(r0,r1,i0)		_ldxr_us(_jit,r0,r1,i0)
static void _ldxr_us(jit_state_t*,int32_t,int32_t,int32_t);
#  define ldxi_us(r0,r1,i0)		_ldxi_us(_jit,r0,r1,i0)
static void _ldxi_us(jit_state_t*,int32_t,int32_t,jit_word_t);
#  if __WORDSIZE == 32
#    define ldr_i(r0,r1)		LWZX(r0, rn(_R0), r1)
#  else
#    define ldr_i(r0,r1)		LWAX(r0, rn(_R0), r1)
#  endif
#  define ldi_i(r0,i0)			_ldi_i(_jit,r0,i0)
static void _ldi_i(jit_state_t*,int32_t,jit_word_t);
#  define ldxr_i(r0,r1,i0)		_ldxr_i(_jit,r0,r1,i0)
static void _ldxr_i(jit_state_t*,int32_t,int32_t,int32_t);
#  define ldxi_i(r0,r1,i0)		_ldxi_i(_jit,r0,r1,i0)
static void _ldxi_i(jit_state_t*,int32_t,int32_t,jit_word_t);
#  if __WORDSIZE == 64
#    define ldr_ui(r0,r1)		LWZX(r0, rn(_R0), r1)
#    define ldi_ui(r0,i0)		_ldi_ui(_jit,r0,i0)
static void _ldi_ui(jit_state_t*,int32_t,jit_word_t);
#    define ldxr_ui(r0,r1,i0)		_ldxr_ui(_jit,r0,r1,i0)
static void _ldxr_ui(jit_state_t*,int32_t,int32_t,int32_t);
#    define ldxi_ui(r0,r1,i0)		_ldxi_ui(_jit,r0,r1,i0)
static void _ldxi_ui(jit_state_t*,int32_t,int32_t,jit_word_t);
#    define ldr_l(r0,r1)		LDX(r0, rn(_R0), r1)
#    define ldi_l(r0,i0)		_ldi_l(_jit,r0,i0)
static void _ldi_l(jit_state_t*,int32_t,jit_word_t);
#    define ldxr_l(r0,r1,i0)		_ldxr_l(_jit,r0,r1,i0)
static void _ldxr_l(jit_state_t*,int32_t,int32_t,int32_t);
#    define ldxi_l(r0,r1,i0)		_ldxi_l(_jit,r0,r1,i0)
static void _ldxi_l(jit_state_t*,int32_t,int32_t,jit_word_t);
#  endif
#  define str_c(r0,r1)			STBX(r1, rn(_R0), r0)
#  define sti_c(i0,r0)			_sti_c(_jit,i0,r0)
static void _sti_c(jit_state_t*,jit_word_t,int32_t);
#  define stxr_c(r0,r1,r2)		_stxr_c(_jit,r0,r1,r2)
static void _stxr_c(jit_state_t*,int32_t,int32_t,int32_t);
#  define stxi_c(i0,r0,r1)		_stxi_c(_jit,i0,r0,r1)
static void _stxi_c(jit_state_t*,jit_word_t,int32_t,int32_t);
#  define str_s(r0,r1)			STHX(r1, rn(_R0), r0)
#  define sti_s(i0,r0)			_sti_s(_jit,i0,r0)
static void _sti_s(jit_state_t*,jit_word_t,int32_t);
#  define stxr_s(r0,r1,r2)		_stxr_s(_jit,r0,r1,r2)
static void _stxr_s(jit_state_t*,int32_t,int32_t,int32_t);
#  define stxi_s(i0,r0,r1)		_stxi_s(_jit,i0,r0,r1)
static void _stxi_s(jit_state_t*,jit_word_t,int32_t,int32_t);
#  define str_i(r0,r1)			STWX(r1, rn(_R0), r0)
#  define sti_i(i0,r0)			_sti_i(_jit,i0,r0)
static void _sti_i(jit_state_t*,jit_word_t,int32_t);
#  define stxr_i(r0,r1,r2)		_stxr_i(_jit,r0,r1,r2)
static void _stxr_i(jit_state_t*,int32_t,int32_t,int32_t);
#  define stxi_i(i0,r0,r1)		_stxi_i(_jit,i0,r0,r1)
static void _stxi_i(jit_state_t*,jit_word_t,int32_t,int32_t);
#  if __WORDSIZE == 64
#    define str_l(r0,r1)		STDX(r1, rn(_R0), r0)
#    define sti_l(i0,r0)		_sti_l(_jit,i0,r0)
static void _sti_l(jit_state_t*,jit_word_t,int32_t);
#    define stxr_l(r0,r1,r2)		_stxr_l(_jit,r0,r1,r2)
static void _stxr_l(jit_state_t*,int32_t,int32_t,int32_t);
#    define stxi_l(i0,r0,r1)		_stxi_l(_jit,i0,r0,r1)
static void _stxi_l(jit_state_t*,jit_word_t,int32_t,int32_t);
#  endif
#  define jmpr(r0)			_jmpr(_jit,r0)
static void _jmpr(jit_state_t*,int32_t);
#  define jmpi(i0)			_jmpi(_jit,i0)
static jit_word_t _jmpi(jit_state_t*,jit_word_t);
#  define jmpi_p(i0)			_jmpi_p(_jit,i0)
static jit_word_t _jmpi_p(jit_state_t*,jit_word_t) maybe_unused;
#  define callr(r0)			_callr(_jit,r0)
static void _callr(jit_state_t*,int32_t);
#  define calli(i0)			_calli(_jit,i0)
static void _calli(jit_state_t*,jit_word_t);
#  define calli_p(i0)			_calli_p(_jit,i0)
static jit_word_t _calli_p(jit_state_t*,jit_word_t);

#  define _u16(v)			((v) & 0xffff)
#  define _u26(v)			((v) & 0x3ffffff)
static int32_t
FXO(int o, int d, int a, int b, int e, int x, int r)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(d & ~((1 << 5) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    assert(!(b & ~((1 << 5) - 1)));
    assert(!(e & ~((1 << 1) - 1)));
    assert(!(x & ~((1 << 9) - 1)));
    assert(!(r & ~((1 << 1) - 1)));
    return (int32_t)((o<<26)|(d<<21)|(a<<16)|(b<<11)|(e<<10)|(x<<1)|r);
}

static int32_t
FDs(int o, int d, int a, int s)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(d & ~((1 << 5) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    assert(can_sign_extend_short_p(s));
    return (int32_t)((o<<26)|(d<<21)|(a<<16)|_u16(s));
}

static int32_t
FDu(int o, int d, int a, int s)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(d & ~((1 << 5) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    assert(can_zero_extend_short_p(s));
    return (int32_t)((o<<26)|(d<<21)|(a<<16)|_u16(s));
}

static int32_t
FX(int o, int s, int a, int b, int x, int r)
{
    assert(!(o & ~((1 <<  6) - 1)));
    assert(!(s & ~((1 <<  5) - 1)));
    assert(!(a & ~((1 <<  5) - 1)));
    assert(!(b & ~((1 <<  5) - 1)));
    assert(!(x & ~((1 << 10) - 1)));
    assert(!(r & ~((1 <<  1) - 1)));
    return (int32_t)((o<<26)|(s<<21)|(a<<16)|(b<<11)|(x<<1)|r);
}

static int32_t
FI(int o, int t, int a, int k)
{
    assert(!(o & ~(( 1 <<  6) - 1)));
    assert(!(t & 3) && can_sign_extend_jump_p(t));
    assert(!(a & ~(( 1 <<  1) - 1)));
    assert(!(k & ~(( 1 <<  1) - 1)));
    return (int32_t)((o<<26)|_u26(t)|(a<<1)|k);
}

static int32_t
FB(int o, int bo, int bi, int t, int a, int k)
{
    assert(!( o & ~((1 <<  6) - 1)));
    assert(!(bo & ~((1 <<  5) - 1)));
    assert(!(bi & ~((1 <<  5) - 1)));
    assert(!(t & 3) && can_sign_extend_short_p(t));
    assert(!(a & ~(( 1 <<  1) - 1)));
    assert(!(k & ~(( 1 <<  1) - 1)));
    return (int32_t)((o<<26)|(bo<<21)|(bi<<16)|_u16(t)|(a<<1)|k);
}

static int32_t
FXL(int o, int bo, int bi, int x, int k)
{
    assert(!( o & ~((1 <<  6) - 1)));
    assert(!(bo & ~((1 <<  5) - 1)));
    assert(!(bi & ~((1 <<  5) - 1)));
    assert(!(x & ~(( 1 << 10) - 1)));
    assert(!(k & ~(( 1 <<  1) - 1)));
    return (int32_t)((o<<26)|(bo<<21)|(bi<<16)|(x<<1)|k);
}

static int32_t
FC(int o, int d, int l, int a, int b, int x)
{
    assert(!(o & ~((1 <<  6) - 1)));
    assert(!(d & ~((1 <<  3) - 1)));
    assert(!(l & ~((1 <<  1) - 1)));
    assert(!(a & ~((1 <<  5) - 1)));
    assert(!(b & ~((1 <<  5) - 1)));
    assert(!(x & ~((1 << 10) - 1)));
    return (int32_t)((o<<26)|(d<<23)|(l<<21)|(a<<16)|(b<<11)|(x<<1));
}

static int32_t
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
    return (int32_t)((o<<26)|(d<<23)|(l<<21)|(a<<16)|_u16(s));
}

static int32_t
FXFX(int o, int d, int x, int f)
{
    assert(!(o & ~((1 <<  6) - 1)));
    assert(!(d & ~((1 <<  5) - 1)));
    assert(!(x & ~((1 << 10) - 1)));
    assert(!(f & ~((1 << 10) - 1)));
    return (int32_t)((o<<26)|(d<<21)|(x<<11)|(f<<1));
}

static int32_t
FM(int o, int s, int a, int h, int b, int e, int r)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(s & ~((1 << 5) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    assert(!(h & ~((1 << 5) - 1)));
    assert(!(b & ~((1 << 5) - 1)));
    assert(!(e & ~((1 << 5) - 1)));
    assert(!(r & ~((1 << 1) - 1)));
    return (int32_t)((o<<26)|(s<<21)|(a<<16)|(h<<11)|(b<<6)|(e<<1)|r);
}

#  if __WORDSIZE == 64
static int32_t
FMDS(int o, int s, int a, int b, int e, int x, int r)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(s & ~((1 << 5) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    assert(!(b & ~((1 << 5) - 1)));
    assert(!(e & ~((1 << 6) - 1)));
    assert(!(x & ~((1 << 4) - 1)));
    assert(!(r & ~((1 << 1) - 1)));
    e = (e >> 5) | ((e << 1) & 63);
    return (int32_t)((o<<26)|(s<<21)|(a<<16)|(b<<11)|(e<<5)|(x<<1)|r);
}

static int32_t
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
    return (int32_t)((o<<26)|(s<<21)|(a<<16)|(h<<11)|(e<<5)|(x<<2)|(i<<1)|r);
}

static int32_t
FXS(int o, int s, int a, int h, int x, int i, int r)
{
    assert(!(o & ~((1 << 6) - 1)));
    assert(!(s & ~((1 << 5) - 1)));
    assert(!(a & ~((1 << 5) - 1)));
    assert(!(h & ~((1 << 5) - 1)));
    assert(!(x & ~((1 << 9) - 1)));
    assert(!(i & ~((1 << 1) - 1)));
    assert(!(r & ~((1 << 1) - 1)));
    return (int32_t)((o<<26)|(s<<21)|(a<<16)|(h<<11)|(x<<2)|(i<<1)|r);
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
    emit_u32(_jit, _MFXER(reg));
    emit_u32(_jit, _MTCRF(128, reg));
    emit_u32(_jit, _RLWINM(reg, reg, 0, 0, 28));
    emit_u32(_jit, _MTXER(reg));
    unget_temp_gpr(_jit);
}

#else
static void
mcrxr(jit_state_t *_jit, int32_t cr)
{
    emit_u32(_jit, _FX(31, cr << 2, 0, 0, 512);
}
#endif

static void
nop(jit_state_t *_jit, int32_t i0)
{
    for (; i0 > 0; i0 -= 4)
	emit_u32(_jit, _NOP());
    assert(i0 == 0);
}

static void
movr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    if (r0 != r1)
	emit_u32(_jit, _MR(r0, r1));
}

static void
movi(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    if (can_sign_extend_short_p(i0))
	emit_u32(_jit, _LI(r0, i0));
    else {
	if (can_sign_extend_int_p(i0))
	    emit_u32(_jit, _LIS(r0, (int16_t)(i0 >> 16)));
	else if (can_zero_extend_int_p(i0)) {
	    if (i0 & 0xffff0000) {
		emit_u32(_jit, _ORI(r0, r0, (uint16_t)(i0 >> 16)));
		emit_u32(_jit, _SLWI(r0, r0, 16));
	    }
	}
#  if __WORDSIZE == 64
	else {
	    movi(_jit, r0, (uint32_t)(i0 >> 32));
	    if (i0 & 0xffff0000) {
		emit_u32(_jit, _SLDI(r0, r0, 16));
		emit_u32(_jit, _ORI(r0, r0, (uint16_t)(i0 >> 16)));
		emit_u32(_jit, _SLDI(r0, r0, 16));
	    }
	    else
		emit_u32(_jit, _SLDI(r0, r0, 32));
	}
#  endif
	if (i0 & 0xffff)
	    emit_u32(_jit, _ORI(r0, r0, (uint16_t)i0));
    }
}

typedef struct {
#if __WORDSIZE == 64
	instr_t lis0;
	instr_t ori0;
	instr_t sldi0;

	instr_t lis1;
	instr_t sldi1;
	instr_t ori1;
#else
	instr_t lis;
	instr_t ori;
#endif
} immediate_t;
static void
emit_immediate_reloc(jit_state_t *_jit, int32_t r0)
{
    jit_word_t		word = _jit->pc.w;
#  if __WORDSIZE == 32
    emit_u32(_jit, _LIS(r0, (int16_t)(i0 >> 16)));
    emit_u32(_jit, _ORI(r0, r0, (uint16_t)i0));
#  else
    emit_u32(_jit, _LIS(r0, (int16_t)(i0 >> 48)));
    emit_u32(_jit, _ORI(r0, r0, (uint16_t)(i0 >> 32)));
    emit_u32(_jit, _SLDI(r0, r0, 16));
    emit_u32(_jit, _ORI(r0, r0, (uint16_t)(i0 >> 16)));
    emit_u32(_jit, _SLDI(r0, r0, 16));
    emit_u32(_jit, _ORI(r0, r0, (uint16_t)i0));
#  endif
    return (word);
}

static void
negr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	emit_u32(_jit, _NEG(r0, r1));
}

static void
comr(jit_state_t *_jit, int32_t r0, int32_t r1)
{
	emit_u32(_jit, _NOT(r0, r1));
}

#  if __BYTE_ORDER == __LITTLE_ENDIAN
static void
bswapr_us(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    int32_t		t0;
    t0 = rn(get_temp_gpr(_jit));
    rshi(rn(t0), r1, 8);
    andi(r0, r1, 0xff);
    andi(rn(t0), rn(t0), 0xff);
    lshi(r0, r0, 8);
    orr(r0, r0, rn(t0));
    unget_temp_gpr(_jit);
}

static void
bswapr_ui(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    ROTLWI(rn(reg), r1, 8);
    RLWIMI(rn(reg), r1, 24, 0, 7);
    RLWIMI(rn(reg), r1, 24, 16, 23);
    CLRLDI(r0, rn(reg), 32);
    unget_temp_gpr(_jit);
}

#    if __WORDSIZE == 64
static void
bswapr_ul(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    rshi_u(rn(reg), r1, 32);
    bswapr_ui(r0, r1);
    bswapr_ui(rn(reg), rn(reg));
    lshi(r0, r0, 32);
    orr(r0, r0, rn(reg));
    unget_temp_gpr(_jit);
}
#    endif
#  endif

static void
addi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (can_sign_extend_short_p(i0))
	ADDI(r0, r1, i0);
    else if (can_zero_extend_int_p(i0) && !(i0 & 0x0000ffff))
	ADDIS(r0, r1, i0 >> 16);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	ADD(r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
addci(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (can_sign_extend_short_p(i0))
	ADDIC(r0, r1, i0);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	ADDC(r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
addxi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    movi(rn(reg), i0);
    ADDE(r0, r1, rn(reg));
    unget_temp_gpr(_jit);
}

static void
subi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    jit_word_t		ni0 = -i0;
    if (can_sign_extend_short_p(ni0))
	ADDI(r0, r1, ni0);
    else if (can_zero_extend_int_p(ni0) && !(ni0 & 0x0000ffff))
	ADDIS(r0, r1, ni0 >> 16);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	SUB(r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
subci(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    movi(rn(reg), i0);
    SUBC(r0, r1, rn(reg));
    unget_temp_gpr(_jit);
}

static void
subxi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    movi(rn(reg), i0);
    SUBE(r0, r1, rn(reg));
    unget_temp_gpr(_jit);
}

static void
rsbi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    subi(r0, r1, i0);
    negr(r0, r0);
}

static void
muli(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (can_sign_extend_short_p(i0))
	MULLI(r0, r1, i0);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	mulr(r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
iqmulr(jit_state_t *_jit, int32_t r0, int32_t r1,
	int32_t r2, int32_t r3, jit_bool_t sign)
{
    int32_t		reg;
    if (r0 == r2 || r0 == r3) {
	reg = rn(get_temp_gpr(_jit));
	mullr(rn(reg), r2, r3);
    }
    else
	mullr(r0, r2, r3);
    if (sign)
	mulhr(r1, r2, r3);
    else
	mulhr_u(r1, r2, r3);
    if (r0 == r2 || r0 == r3) {
	movr(r0, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
iqmuli(jit_state_t *_jit, int32_t r0, int32_t r1,
	int32_t r2, jit_word_t i0, jit_bool_t sign)
{
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    movi(rn(reg), i0);
    iqmulr(r0, r1, r2, rn(reg), sign);
    unget_temp_gpr(_jit);
}

static void
divi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    movi(rn(reg), i0);
    divr(r0, r1, rn(reg));
    unget_temp_gpr(_jit);
}

static void
divi_u(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    movi(rn(reg), i0);
    divr_u(r0, r1, rn(reg));
    unget_temp_gpr(_jit);
}

static void
iqdivr(jit_state_t *_jit, int32_t r0, int32_t r1,
	int32_t r2, int32_t r3, jit_bool_t sign)
{
    int32_t		sv0, rg0;
    int32_t		sv1, rg1;

    if (r0 == r2 || r0 == r3) {
	sv0 = rn(get_temp_gpr(_jit));
	rg0 = rn(sv0);
    }
    else
	rg0 = r0;
    if (r1 == r2 || r1 == r3) {
	sv1 = rn(get_temp_gpr(_jit));
	rg1 = rn(sv1);
    }
    else
	rg1 = r1;

    if (sign)
	divr(rg0, r2, r3);
    else
	divr_u(rg0, r2, r3);
    mulr(rg1, r3, rg0);
    subr(rg1, r2, rg1);
    if (rg0 != r0) {
	movr(r0, rg0);
	unget_temp_gpr(_jit);
    }
    if (rg1 != r1) {
	movr(r1, rg1);
	unget_temp_gpr(_jit);
    }
}

static void
iqdivi(jit_state_t *_jit, int32_t r0, int32_t r1,
	int32_t r2, jit_word_t i0, jit_bool_t sign)
{
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    movi(rn(reg), i0);
    iqdivr(r0, r1, r2, rn(reg), sign);
    unget_temp_gpr(_jit);
}

static void
remr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    int32_t		reg;
    if (r0 == r1 || r0 == r2) {
	reg = rn(get_temp_gpr(_jit));
	divr(rn(reg), r1, r2);
	mulr(rn(reg), r2, rn(reg));
	subr(r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
    else {
	divr(r0, r1, r2);
	mulr(r0, r2, r0);
	subr(r0, r1, r0);
    }
}

static void
remi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    movi(rn(reg), i0);
    remr(r0, r1, rn(reg));
    unget_temp_gpr(_jit);
}

static void
remr_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    int32_t		reg;
    if (r0 == r1 || r0 == r2) {
	reg = rn(get_temp_gpr(_jit));
	divr_u(rn(reg), r1, r2);
	mulr(rn(reg), r2, rn(reg));
	subr(r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
    else {
	divr_u(r0, r1, r2);
	mulr(r0, r2, r0);
	subr(r0, r1, r0);
    }
}

static void
remi_u(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    movi(rn(reg), i0);
    remr_u(r0, r1, rn(reg));
    unget_temp_gpr(_jit);
}

static void
andi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (can_zero_extend_short_p(i0))
	ANDI_(r0, r1, i0);
    else if (can_zero_extend_int_p(i0) && !(i0 & 0x0000ffff))
	ANDIS_(r0, r1, (jit_uword_t)i0 >> 16);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	AND(r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ori(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (can_zero_extend_short_p(i0))
	ORI(r0, r1, i0);
    else if (can_zero_extend_int_p(i0) && !(i0 & 0x0000ffff))
	ORIS(r0, r1, (jit_uword_t)i0 >> 16);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	OR(r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
xori(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (can_zero_extend_short_p(i0))
	XORI(r0, r1, i0);
    else if (can_zero_extend_int_p(i0) && !(i0 & 0x0000ffff))
	XORIS(r0, r1, (jit_uword_t)i0 >> 16);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	XOR(r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
lshi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (i0 == 0)
	movr(r0, r1);
    else {
#  if __WORDSIZE == 32
	SLWI(r0, r1, i0);
#  else
	SLDI(r0, r1, i0);
#  endif
    }
}

static void
rshi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (i0 == 0)
	movr(r0, r1);
    else {
#  if __WORDSIZE == 32
	SRAWI(r0, r1, i0);
#  else
	SRADI(r0, r1, i0);
#  endif
    }
}

static void
rshi_u(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    if (i0 == 0)
	movr(r0, r1);
    else {
#  if __WORDSIZE == 32
	SRWI(r0, r1, i0);
#  else
	SRDI(r0, r1, i0);
#  endif
    }
}

static void
ltr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    CMPW(r1, r2);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_LT);
}

static void
lti(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (can_sign_extend_short_p(i0))
	CMPWI(r1, i0);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	CMPW(r1, rn(reg));
	unget_temp_gpr(_jit);
    }
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_LT);
}

static void
ltr_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    CMPLW(r1, r2);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_LT);
}

static void
lti_u(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (can_zero_extend_short_p(i0))
	CMPLWI(r1, i0);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	CMPLW(r1, rn(reg));
	unget_temp_gpr(_jit);
    }
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_LT);
}

static void
ler(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    CMPW(r1, r2);
    CRNOT(CR_GT, CR_GT);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_GT);
}

static void
lei(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (can_sign_extend_short_p(i0))
	CMPWI(r1, i0);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	CMPW(r1, rn(reg));
	unget_temp_gpr(_jit);
    }
    CRNOT(CR_GT, CR_GT);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_GT);
}

static void
ler_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    CMPLW(r1, r2);
    CRNOT(CR_GT, CR_GT);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_GT);
}

static void
lei_u(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (can_zero_extend_short_p(i0))
	CMPLWI(r1, i0);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	CMPLW(r1, rn(reg));
	unget_temp_gpr(_jit);
    }
    CRNOT(CR_GT, CR_GT);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_GT);
}

static void
eqr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    CMPW(r1, r2);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_EQ);
}

static void
eqi(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (can_sign_extend_short_p(i0))
	CMPWI(r1, i0);
    else if (can_zero_extend_short_p(i0))
	CMPLWI(r1, i0);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	CMPW(r1, rn(reg));
	unget_temp_gpr(_jit);
    }
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_EQ);
}

static void
ger(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    CMPW(r1, r2);
    CRNOT(CR_LT, CR_LT);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_LT);
}

static void
gei(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (can_sign_extend_short_p(i0))
	CMPWI(r1, i0);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	CMPW(r1, rn(reg));
	unget_temp_gpr(_jit);
    }
    CRNOT(CR_LT, CR_LT);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_LT);
}

static void
ger_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    CMPLW(r1, r2);
    CRNOT(CR_LT, CR_LT);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_LT);
}

static void
gei_u(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (can_zero_extend_short_p(i0))
	CMPLWI(r1, i0);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	CMPLW(r1, rn(reg));
	unget_temp_gpr(_jit);
    }
    CRNOT(CR_LT, CR_LT);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_LT);
}

static void
gtr(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    CMPW(r1, r2);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_GT);
}

static void
gti(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (can_sign_extend_short_p(i0))
	CMPWI(r1, i0);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	CMPW(r1, rn(reg));
	unget_temp_gpr(_jit);
    }
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_GT);
}

static void
gtr_u(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    CMPLW(r1, r2);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_GT);
}

static void
gti_u(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (can_zero_extend_short_p(i0))
	CMPLWI(r1, i0);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	CMPLW(r1, rn(reg));
	unget_temp_gpr(_jit);
    }
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_GT);
}

static void
ner(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    CMPW(r1, r2);
    CRNOT(CR_EQ, CR_EQ);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_EQ);
}

static void
nei(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (can_sign_extend_short_p(i0))
	CMPWI(r1, i0);
    else if (can_zero_extend_short_p(i0))
	CMPLWI(r1, i0);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	CMPW(r1, rn(reg));
	unget_temp_gpr(_jit);
    }
    CRNOT(CR_EQ, CR_EQ);
    MFCR(r0);
    EXTRWI(r0, r0, 1, CR_EQ);
}

static jit_word_t
bltr(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		d, w;
    CMPW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLT(d);
    return (w);
}

static jit_word_t
blti(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    int32_t		reg;
    jit_word_t		d, w;
    if (can_sign_extend_short_p(i1))
	CMPWI(r0, i1);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i1);
	CMPW(r0, rn(reg));
	unget_temp_gpr(_jit);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLT(d);
    return (w);
}

static jit_word_t
bltr_u(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		d, w;
    CMPLW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLT(d);
    return (w);
}

static jit_word_t
blti_u(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    int32_t		reg;
    jit_word_t		d, w;
    if (can_zero_extend_short_p(i1))
	CMPLWI(r0, i1);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i1);
	CMPLW(r0, rn(reg));
	unget_temp_gpr(_jit);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLT(d);
    return (w);
}

static jit_word_t
bler(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		d, w;
    CMPW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLE(d);
    return (w);
}

static jit_word_t
blei(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    int32_t		reg;
    jit_word_t		d, w;
    if (can_sign_extend_short_p(i1))
	CMPWI(r0, i1);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i1);
	CMPW(r0, rn(reg));
	unget_temp_gpr(_jit);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLE(d);
    return (w);
}

static jit_word_t
bler_u(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		d, w;
    CMPLW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLE(d);
    return (w);
}

static jit_word_t
blei_u(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    int32_t		reg;
    jit_word_t		d, w;
    if (can_zero_extend_short_p(i1))
	CMPLWI(r0, i1);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i1);
	CMPLW(r0, rn(reg));
	unget_temp_gpr(_jit);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLE(d);
    return (w);
}

static jit_word_t
beqr(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		d, w;
    CMPW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BEQ(d);
    return (w);
}

static jit_word_t
beqi(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    int32_t		reg;
    jit_word_t		d, w;
    if (can_sign_extend_short_p(i1))
	CMPWI(r0, i1);
    else if (can_zero_extend_short_p(i1))
	CMPLWI(r0, i1);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i1);
	CMPW(r0, rn(reg));
	unget_temp_gpr(_jit);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BEQ(d);
    return (w);
}

static jit_word_t
bger(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		d, w;
    CMPW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGE(d);
    return (w);
}

static jit_word_t
bgei(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    int32_t		reg;
    jit_word_t		d, w;
    if (can_sign_extend_short_p(i1))
	CMPWI(r0, i1);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i1);
	CMPW(r0, rn(reg));
	unget_temp_gpr(_jit);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGE(d);
    return (w);
}

static jit_word_t
bger_u(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		d, w;
    CMPLW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGE(d);
    return (w);
}

static jit_word_t
bgei_u(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    int32_t		reg;
    jit_word_t		d, w;
    if (can_zero_extend_short_p(i1))
	CMPLWI(r0, i1);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i1);
	CMPLW(r0, rn(reg));
	unget_temp_gpr(_jit);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGE(d);
    return (w);
}

static jit_word_t
bgtr(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		d, w;
    CMPW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGT(d);
    return (w);
}

static jit_word_t
bgti(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    int32_t		reg;
    jit_word_t		d, w;
    if (can_sign_extend_short_p(i1))
	CMPWI(r0, i1);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i1);
	CMPW(r0, rn(reg));
	unget_temp_gpr(_jit);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGT(d);
    return (w);
}

static jit_word_t
bgtr_u(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		d, w;
    CMPLW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGT(d);
    return (w);
}

static jit_word_t
bgti_u(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    int32_t		reg;
    jit_word_t		d, w;
    if (can_zero_extend_short_p(i1))
	CMPLWI(r0, i1);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i1);
	CMPLW(r0, rn(reg));
	unget_temp_gpr(_jit);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGT(d);
    return (w);
}

static jit_word_t
bner(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		d, w;
    CMPW(r0, r1);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BNE(d);
    return (w);
}

static jit_word_t
bnei(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    int32_t		reg;
    jit_word_t		d, w;
    if (can_sign_extend_short_p(i1))
	CMPWI(r0, i1);
    else if (can_zero_extend_short_p(i1))
	CMPLWI(r0, i1);
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i1);
	CMPW(r0, rn(reg));
	unget_temp_gpr(_jit);
    }
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BNE(d);
    return (w);
}

static jit_word_t
bmsr(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		w;
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    andr(rn(reg), r0, r1);
    w = bnei(i0, rn(reg), 0);
    unget_temp_gpr(_jit);
    return (w);
}

static jit_word_t
bmsi(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    jit_word_t		w;
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    andi(rn(reg), r0, i1);
    w = bnei(i0, rn(reg), 0);
    unget_temp_gpr(_jit);
    return (w);
}

static jit_word_t
bmcr(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		w;
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    andr(rn(reg), r0, r1);
    w = beqi(i0, rn(reg), 0);
    unget_temp_gpr(_jit);
    return (w);
}

static jit_word_t
bmci(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    jit_word_t		w;
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    andi(rn(reg), r0, i1);
    w = beqi(i0, rn(reg), 0);
    unget_temp_gpr(_jit);
    return (w);
}

static jit_word_t
boaddr(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		d, w;
    ADDO(r0, r0, r1);
    MCRXR(CR_0);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGT(d);				/* GT = bit 1 of XER = OV */
    return (w);
}

static jit_word_t
boaddi(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    jit_word_t		w;
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    movi(rn(reg), i1);
    w = boaddr(i0, r0, rn(reg));
    unget_temp_gpr(_jit);
    return (w);
}

static jit_word_t
bxaddr(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		d, w;
    ADDO(r0, r0, r1);
    MCRXR(CR_0);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLE(d);
    return (w);
}

static jit_word_t
bxaddi(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    jit_word_t		w;
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    movi(rn(reg), i1);
    w = bxaddr(i0, r0, rn(reg));
    unget_temp_gpr(_jit);
    return (w);
}

static jit_word_t
bosubr(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		d, w;
    SUBO(r0, r0, r1);
    MCRXR(CR_0);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BGT(d);
    return (w);
}

static jit_word_t
bosubi(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    jit_word_t		w;
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    movi(rn(reg), i1);
    w = bosubr(i0, r0, rn(reg));
    unget_temp_gpr(_jit);
    return (w);
}

static jit_word_t
bxsubr(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		d, w;
    SUBO(r0, r0, r1);
    MCRXR(CR_0);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BLE(d);
    return (w);
}

static jit_word_t
bxsubi(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    jit_word_t		w;
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    movi(rn(reg), i1);
    w = bxsubr(i0, r0, rn(reg));
    unget_temp_gpr(_jit);
    return (w);
}

static jit_word_t
boaddr_u(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		d, w;
    ADDC(r0, r0, r1);
    MCRXR(CR_0);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BEQ(d);				/* EQ = bit 2 of XER = CA */
    return (w);
}

static jit_word_t
boaddi_u(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    int32_t		reg;
    jit_word_t		d, w;
    if (can_sign_extend_short_p(i1)) {
	ADDIC(r0, r0, i1);
	MCRXR(CR_0);
	w = _jit->pc.w;
	d = (i0 - w) & ~3;
	BEQ(d);
	return (w);
    }
    reg = rn(get_temp_gpr(_jit));
    movi(rn(reg), i1);
    w = boaddr_u(i0, r0, rn(reg));
    unget_temp_gpr(_jit);
    return (w);
}

static jit_word_t
bxaddr_u(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		d, w;
    ADDC(r0, r0, r1);
    MCRXR(CR_0);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BNE(d);
    return (w);
}

static jit_word_t
bxaddi_u(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    int32_t		reg;
    jit_word_t		d, w;
    if (can_sign_extend_short_p(i1)) {
	ADDIC(r0, r0, i1);
	MCRXR(CR_0);
	w = _jit->pc.w;
	d = (i0 - w) & ~3;
	BNE(d);
	return (w);
    }
    reg = rn(get_temp_gpr(_jit));
    movi(rn(reg), i1);
    w = bxaddr_u(i0, r0, rn(reg));
    unget_temp_gpr(_jit);
    return (w);
}

static jit_word_t
bosubr_u(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		d, w;
    SUBC(r0, r0, r1);
    MCRXR(CR_0);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BNE(d);				/* PPC uses "carry" not "borrow" */
    return (w);
}

static jit_word_t
bosubi_u(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    jit_word_t		w;
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    movi(rn(reg), i1);
    w = bosubr_u(i0, r0, rn(reg));
    unget_temp_gpr(_jit);
    return (w);
}

static jit_word_t
bxsubr_u(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    jit_word_t		d, w;
    SUBC(r0, r0, r1);
    MCRXR(CR_0);
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    BEQ(d);
    return (w);
}

static jit_word_t
bxsubi_u(jit_state_t *_jit, jit_word_t i0, int32_t r0, jit_word_t i1)
{
    jit_word_t		w;
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    movi(rn(reg), i1);
    w = bxsubr_u(i0, r0, rn(reg));
    unget_temp_gpr(_jit);
    return (w);
}

static void
ldr_c(jit_state_t *_jit, int32_t r0, int32_t r1)
{
    ldr_uc(r0, r1);
    extr_c(r0, r0);
}

static void
ldi_c(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    ldi_uc(r0, i0);
    extr_c(r0, r0);
}

static void
ldxr_c(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    ldxr_uc(r0, r1, r2);
    extr_c(r0, r0);
}

static void
ldxi_c(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    ldxi_uc(r0, r1, i0);
    extr_c(r0, r0);
}

static void
ldi_uc(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    jit_bool_t		inv;
    int32_t		reg;
    jit_word_t		lo, hi;
    if (can_sign_extend_short_p(i0))
	LBZ(r0, rn(_R0), i0);
    else if (can_sign_extend_int_p(i0)) {
	hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	lo = (int16_t)(i0 - (hi << 16));
	reg = rn(get_temp_gpr(_jit));
	if ((inv = reg == _R0))		reg = rn(get_temp_gpr(_jit));
	LIS(rn(reg), hi);
	LBZ(r0, rn(reg), lo);
	unget_temp_gpr(_jit);
	if (inv)			unget_temp_gpr(_jit);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	ldr_uc(r0, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldxr_uc(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    int32_t		reg;
    if (r1 == rn(_R0)) {
	if (r2 != rn(_R0))
	    LBZX(r0, r2, r1);
	else {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), r1);
	    LBZX(r0, rn(reg), r2);
	    unget_temp_gpr(_jit);
	}
    }
    else
	LBZX(r0, r1, r2);
}

static void
ldxi_uc(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (i0 == 0)
	ldr_uc(r0, r1);
    else if (can_sign_extend_short_p(i0)) {
	if (r1 == rn(_R0)) {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), r1);
	    LBZ(r0, rn(reg), i0);
	    unget_temp_gpr(_jit);
	}
	else
	    LBZ(r0, r1, i0);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	ldxr_uc(r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldi_s(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    jit_bool_t		inv;
    int32_t		reg;
    jit_word_t		lo, hi;
    if (can_sign_extend_short_p(i0))
	LHA(r0, rn(_R0), i0);
    else if (can_sign_extend_int_p(i0)) {
	hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	lo = (int16_t)(i0 - (hi << 16));
	reg = rn(get_temp_gpr(_jit));
	if ((inv = reg == _R0))		reg = rn(get_temp_gpr(_jit));
	LIS(rn(reg), hi);
	LHA(r0, rn(reg), lo);
	unget_temp_gpr(_jit);
	if (inv)			unget_temp_gpr(_jit);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	ldr_s(r0, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldxr_s(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    int32_t		reg;
    if (r1 == rn(_R0)) {
	if (r2 != rn(_R0))
	    LHAX(r0, r2, r1);
	else {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), r1);
	    LHAX(r0, rn(reg), r2);
	    unget_temp_gpr(_jit);
	}
    }
    else
	LHAX(r0, r1, r2);
}

static void
ldxi_s(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (i0 == 0)
	ldr_s(r0, r1);
    else if (can_sign_extend_short_p(i0)) {
	if (r1 == rn(_R0)) {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), r1);
	    LHA(r0, rn(reg), i0);
	    unget_temp_gpr(_jit);
	}
	else
	    LHA(r0, r1, i0);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	ldxr_s(r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldi_us(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    jit_bool_t		inv;
    int32_t		reg;
    jit_word_t		lo, hi;
    if (can_sign_extend_short_p(i0))
	LHZ(r0, rn(_R0), i0);
    else if (can_sign_extend_int_p(i0)) {
	hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	lo = (int16_t)(i0 - (hi << 16));
	reg = rn(get_temp_gpr(_jit));
	if ((inv = reg == _R0))		reg = rn(get_temp_gpr(_jit));
	LIS(rn(reg), hi);
	LHZ(r0, rn(reg), lo);
	unget_temp_gpr(_jit);
	if (inv)			unget_temp_gpr(_jit);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	ldr_us(r0, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldxr_us(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    int32_t		reg;
    if (r1 == rn(_R0)) {
	if (r2 != rn(_R0))
	    LHZX(r0, r2, r1);
	else {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), r1);
	    LHZX(r0, rn(reg), r2);
	    unget_temp_gpr(_jit);
	}
    }
    else
	LHZX(r0, r1, r2);
}

static void
ldxi_us(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (i0 == 0)
	ldr_us(r0, r1);
    else if (can_sign_extend_short_p(i0)) {
	if (r1 == rn(_R0)) {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), r1);
	    LHZ(r0, rn(reg), i0);
	    unget_temp_gpr(_jit);
	}
	else
	    LHZ(r0, r1, i0);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	ldxr_us(r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

#  if __WORDSIZE == 32
static void
ldi_i(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    jit_bool_t		inv;
    int32_t		reg;
    jit_word_t		lo, hi;
    if (can_sign_extend_short_p(i0))
	LWZ(r0, rn(_R0), i0);
    else if (can_sign_extend_int_p(i0)) {
	hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	lo = (int16_t)(i0 - (hi << 16));
	reg = rn(get_temp_gpr(_jit));
	if ((inv = reg == _R0))		reg = rn(get_temp_gpr(_jit));
	LIS(rn(reg), hi);
	LWZ(r0, rn(reg), lo);
	unget_temp_gpr(_jit);
	if (inv)			unget_temp_gpr(_jit);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	ldr_i(r0, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldxr_i(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    int32_t		reg;
    if (r1 == rn(_R0)) {
	if (r2 != rn(_R0))
	    LWZX(r0, r2, r1);
	else {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), r1);
	    LWZX(r0, rn(reg), r2);
	    unget_temp_gpr(_jit);
	}
    }
    else
	LWZX(r0, r1, r2);
}

static void
ldxi_i(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (i0 == 0)
	ldr_i(r0, r1);
    else if (can_sign_extend_short_p(i0)) {
	if (r1 == rn(_R0)) {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), r1);
	    LWZ(r0, rn(reg), i0);
	    unget_temp_gpr(_jit);
	}
	else
	    LWZ(r0, r1, i0);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	ldxr_i(r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

#  else
static void
ldi_i(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    jit_bool_t		inv;
    int32_t		reg;
    jit_word_t		lo, hi;
    if (can_sign_extend_short_p(i0))
	LWA(r0, rn(_R0), i0);
    else if (can_sign_extend_int_p(i0)) {
	hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	lo = (int16_t)(i0 - (hi << 16));
	reg = rn(get_temp_gpr(_jit));
	if ((inv = reg == _R0))		reg = rn(get_temp_gpr(_jit));
	LIS(rn(reg), hi);
	LWA(r0, rn(reg), lo);
	unget_temp_gpr(_jit);
	if (inv)			unget_temp_gpr(_jit);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	ldr_i(r0, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldxr_i(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    int32_t		reg;
    if (r1 == rn(_R0)) {
	if (r2 != rn(_R0))
	    LWZX(r0, r2, r1);
	else {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), r1);
	    LWAX(r0, rn(reg), r2);
	    unget_temp_gpr(_jit);
	}
    }
    else
	LWZX(r0, r1, r2);
}

static void
ldxi_i(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (i0 == 0)
	ldr_i(r0, r1);
    else if (can_sign_extend_short_p(i0)) {
	if (r1 == rn(_R0)) {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), r1);
	    LWA(r0, rn(reg), i0);
	    unget_temp_gpr(_jit);
	}
	else
	    LWA(r0, r1, i0);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	ldxr_i(r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldi_ui(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    jit_bool_t		inv;
    int32_t		reg;
    jit_word_t		lo, hi;
    if (can_sign_extend_short_p(i0))
	LWZ(r0, rn(_R0), i0);
    else if (can_sign_extend_int_p(i0)) {
	hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	lo = (int16_t)(i0 - (hi << 16));
	reg = rn(get_temp_gpr(_jit));
	if ((inv = reg == _R0))		reg = rn(get_temp_gpr(_jit));
	LIS(rn(reg), hi);
	LWZ(r0, rn(reg), lo);
	unget_temp_gpr(_jit);
	if (inv)			unget_temp_gpr(_jit);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	ldr_ui(r0, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldxr_ui(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    int32_t		reg;
    if (r1 == rn(_R0)) {
	if (r2 != rn(_R0))
	    LWZX(r0, r2, r1);
	else {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), r1);
	    LWZX(r0, rn(reg), r2);
	    unget_temp_gpr(_jit);
	}
    }
    else
	LWZX(r0, r1, r2);
}

static void
ldxi_ui(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (i0 == 0)
	ldr_i(r0, r1);
    else if (can_sign_extend_short_p(i0)) {
	if (r1 == rn(_R0)) {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), r1);
	    LWZ(r0, rn(reg), i0);
	    unget_temp_gpr(_jit);
	}
	else
	    LWZ(r0, r1, i0);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	ldxr_ui(r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldi_l(jit_state_t *_jit, int32_t r0, jit_word_t i0)
{
    jit_bool_t		inv;
    int32_t		reg;
    jit_word_t		lo, hi;
    if (can_sign_extend_short_p(i0))
	LD(r0, rn(_R0), i0);
    else if (can_sign_extend_int_p(i0)) {
	hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	lo = (int16_t)(i0 - (hi << 16));
	reg = rn(get_temp_gpr(_jit));
	if ((inv = reg == _R0))		reg = rn(get_temp_gpr(_jit));
	LIS(rn(reg), hi);
	LD(r0, rn(reg), lo);
	unget_temp_gpr(_jit);
	if (inv)			unget_temp_gpr(_jit);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	ldr_l(r0, rn(reg));
	unget_temp_gpr(_jit);
    }
}

static void
ldxr_l(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    int32_t		reg;
    if (r1 == rn(_R0)) {
	if (r2 != rn(_R0))
	    LDX(r0, r2, r1);
	else {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), r1);
	    LDX(r0, rn(reg), r2);
	    unget_temp_gpr(_jit);
	}
    }
    else
	LDX(r0, r1, r2);
}

static void
ldxi_l(jit_state_t *_jit, int32_t r0, int32_t r1, jit_word_t i0)
{
    int32_t		reg;
    if (i0 == 0)
	ldr_l(r0, r1);
    else if (can_sign_extend_short_p(i0)) {
	if (r1 == rn(_R0)) {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), r1);
	    LD(r0, rn(reg), i0);
	    unget_temp_gpr(_jit);
	}
	else
	    LD(r0, r1, i0);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	ldxr_l(r0, r1, rn(reg));
	unget_temp_gpr(_jit);
    }
}
#  endif

static void
sti_c(jit_state_t *_jit, jit_word_t i0, int32_t r0)
{
    jit_bool_t		inv;
    int32_t		reg;
    jit_word_t		lo, hi;
    if (can_sign_extend_short_p(i0))
	STB(r0, rn(_R0), i0);
    else if (can_sign_extend_int_p(i0)) {
	hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	lo = (int16_t)(i0 - (hi << 16));
	reg = rn(get_temp_gpr(_jit));
	if ((inv = reg == _R0))		reg = rn(get_temp_gpr(_jit));
	LIS(rn(reg), hi);
	STB(r0, rn(reg), lo);
	unget_temp_gpr(_jit);
	if (inv)			unget_temp_gpr(_jit);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	str_c(rn(reg), r0);
	unget_temp_gpr(_jit);
    }
}

static void
stxr_c(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    int32_t		reg;
    if (r0 == rn(_R0)) {
	if (r1 != rn(_R0))
	    STBX(r2, r1, r0);
	else {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), r0);
	    STBX(r2, rn(reg), r1);
	    unget_temp_gpr(_jit);
	}
    }
    else
	STBX(r2, r0, r1);
}

static void
stxi_c(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    int32_t		reg;
    if (i0 == 0)
	str_c(r0, r1);
    else if (can_sign_extend_short_p(i0)) {
	if (r0 == rn(_R0)) {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), i0);
	    STB(r1, rn(reg), i0);
	    unget_temp_gpr(_jit);
	}
	else
	    STB(r1, r0, i0);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	stxr_c(rn(reg), r0, r1);
	unget_temp_gpr(_jit);
    }
}

static void
sti_s(jit_state_t *_jit, jit_word_t i0, int32_t r0)
{
    jit_bool_t		inv;
    int32_t		reg;
    jit_word_t		lo, hi;
    if (can_sign_extend_short_p(i0))
	STH(r0, rn(_R0), i0);
    else if (can_sign_extend_int_p(i0)) {
	hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	lo = (int16_t)(i0 - (hi << 16));
	reg = rn(get_temp_gpr(_jit));
	if ((inv = reg == _R0))		reg = rn(get_temp_gpr(_jit));
	LIS(rn(reg), hi);
	STH(r0, rn(reg), lo);
	unget_temp_gpr(_jit);
	if (inv)			unget_temp_gpr(_jit);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	str_s(rn(reg), r0);
	unget_temp_gpr(_jit);
    }
}

static void
stxr_s(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    int32_t		reg;
    if (r0 == rn(_R0)) {
	if (r1 != rn(_R0))
	    STHX(r2, r1, r0);
	else {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), r0);
	    STHX(r2, rn(reg), r1);
	    unget_temp_gpr(_jit);
	}
    }
    else
	STHX(r2, r0, r1);
}

static void
stxi_s(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    int32_t		reg;
    if (i0 == 0)
	str_s(r0, r1);
    else if (can_sign_extend_short_p(i0)) {
	if (r0 == rn(_R0)) {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), i0);
	    STH(r1, rn(reg), i0);
	    unget_temp_gpr(_jit);
	}
	else
	    STH(r1, r0, i0);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	stxr_s(rn(reg), r0, r1);
	unget_temp_gpr(_jit);
    }
}

static void
sti_i(jit_state_t *_jit, jit_word_t i0, int32_t r0)
{
    jit_bool_t		inv;
    int32_t		reg;
    jit_word_t		lo, hi;
    if (can_sign_extend_short_p(i0))
	STW(r0, rn(_R0), i0);
    else if (can_sign_extend_int_p(i0)) {
	hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	lo = (int16_t)(i0 - (hi << 16));
	reg = rn(get_temp_gpr(_jit));
	if ((inv = reg == _R0))		reg = rn(get_temp_gpr(_jit));
	LIS(rn(reg), hi);
	STW(r0, rn(reg), lo);
	unget_temp_gpr(_jit);
	if (inv)			unget_temp_gpr(_jit);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	str_i(rn(reg), r0);
	unget_temp_gpr(_jit);
    }
}

static void
stxr_i(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    int32_t		reg;
    if (r0 == rn(_R0)) {
	if (r1 != rn(_R0))
	    STWX(r2, r1, r0);
	else {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), r0);
	    STWX(r2, rn(reg), r1);
	    unget_temp_gpr(_jit);
	}
    }
    else
	STWX(r2, r0, r1);
}

static void
stxi_i(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    int32_t		reg;
    if (i0 == 0)
	str_i(r0, r1);
    else if (can_sign_extend_short_p(i0)) {
	if (r0 == rn(_R0)) {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), i0);
	    STW(r1, rn(reg), i0);
	    unget_temp_gpr(_jit);
	}
	else
	    STW(r1, r0, i0);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	stxr_i(rn(reg), r0, r1);
	unget_temp_gpr(_jit);
    }
}

#  if __WORDSIZE == 64
static void
sti_l(jit_state_t *_jit, jit_word_t i0, int32_t r0)
{
    jit_bool_t		inv;
    int32_t		reg;
    jit_word_t		lo, hi;
    if (can_sign_extend_short_p(i0))
	STD(r0, rn(_R0), i0);
    else if (can_sign_extend_int_p(i0)) {
	hi = (int16_t)((i0 >> 16) + ((uint16_t)i0 >> 15));
	lo = (int16_t)(i0 - (hi << 16));
	reg = rn(get_temp_gpr(_jit));
	if ((inv = reg == _R0))		reg = rn(get_temp_gpr(_jit));
	LIS(rn(reg), hi);
	STD(r0, rn(reg), lo);
	unget_temp_gpr(_jit);
	if (inv)			unget_temp_gpr(_jit);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	str_l(rn(reg), r0);
	unget_temp_gpr(_jit);
    }
}

static void
stxr_l(jit_state_t *_jit, int32_t r0, int32_t r1, int32_t r2)
{
    int32_t		reg;
    if (r0 == rn(_R0)) {
	if (r1 != rn(_R0))
	    STDX(r2, r1, r0);
	else {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), r0);
	    STDX(r2, rn(reg), r1);
	    unget_temp_gpr(_jit);
	}
    }
    else
	STDX(r2, r0, r1);
}

static void
stxi_l(jit_state_t *_jit, jit_word_t i0, int32_t r0, int32_t r1)
{
    int32_t		reg;
    if (i0 == 0)
	str_l(r0, r1);
    else if (can_sign_extend_short_p(i0)) {
	if (r0 == rn(_R0)) {
	    reg = rn(get_temp_gpr(_jit));
	    movr(rn(reg), i0);
	    STD(r1, rn(reg), i0);
	    unget_temp_gpr(_jit);
	}
	else
	    STD(r1, r0, i0);
    }
    else {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	stxr_l(rn(reg), r0, r1);
	unget_temp_gpr(_jit);
    }
}
#  endif

static void
jmpr(jit_state_t *_jit, int32_t r0)
{
#if 0
    MTLR(r0);
    BLR();
#else
    MTCTR(r0);
    BCTR();
#endif
}

/* pc relative jump */
static jit_word_t
jmpi(jit_state_t *_jit, jit_word_t i0)
{
    int32_t		reg;
    jit_word_t		w, d;
    w = _jit->pc.w;
    d = (i0 - w) & ~3;
    if (can_sign_extend_jump_p(d))
	B(d);
    else {
	reg = rn(get_temp_gpr(_jit));
	w = movi_p(rn(reg), i0);
	jmpr(rn(reg));
	unget_temp_gpr(_jit);
    }
    return (w);
}

/* absolute jump */
static jit_word_t
jmpi_p(jit_state_t *_jit, jit_word_t i0)
{
    jit_word_t		w;
    int32_t		reg;
    reg = rn(get_temp_gpr(_jit));
    w = movi_p(rn(reg), i0);
    jmpr(rn(reg));
    unget_temp_gpr(_jit);
    return (w);
}

static void
callr(jit_state_t *_jit, int32_t r0)
{
#  if __powerpc__
#    if ABI_ELFv2
    movr(rn(_R12), r0);
#    else
    stxi(sizeof(void*) * 5, rn(JIT_SP), rn(_R2));
    /* FIXME Pretend to not know about r11? */
    if (r0 == rn(_R0)) {
	movr(rn(_R11), rn(_R0));
	ldxi(rn(_R2), rn(_R11), sizeof(void*));
	ldxi(rn(_R11), rn(_R11), sizeof(void*) * 2);
    }
    else {
	ldxi(rn(_R2), r0, sizeof(void*));
	ldxi(rn(_R11), r0, sizeof(void*) * 2);
    }
    ldr(r0, r0);
#    endif
#  endif

    MTCTR(r0);
    BCTRL();

#  if __powerpc__ && !ABI_ELFv2
    ldxi(rn(_R2), rn(_SP), sizeof(void*) * 5);
#  endif
}

/* assume fixed address or reachable address */
static void
calli(jit_state_t *_jit, jit_word_t i0)
{
#  if __ppc__
    jit_word_t		d;
#  endif
    int32_t		reg;
#  if __ppc__
    d = (i0 - _jit->pc.w) & ~3;
    if (can_sign_extend_jump_p(d))
	BL(d);
    else
#  endif
    {
	reg = rn(get_temp_gpr(_jit));
	movi(rn(reg), i0);
	callr(rn(reg));
	unget_temp_gpr(_jit);
    }
}

#  if __powerpc__
/* order is not guaranteed to be sequential */
static int32_t save[] = {
    _R14, _R15, _R16, _R17, _R18, _R19, _R20, _R21, _R22,
    _R23, _R24, _R25, _R26, _R27, _R28, _R29, _R30, _R31,
};
#endif

void
ret(jit_state_t *_jit)
{
    jit_node_t		*instr;
    assert(_jitc->function);
    jit_inc_synth(ret);
    /* jump to epilog */
    instr = jit_jmpi();
    jit_patch_at(instr, _jitc->function->epilog);
    jit_dec_synth();
}

void
retr(jit_state_t *_jit, int32_t u)
{
    jit_inc_synth_w(retr, u);
    if (JIT_RET != u)
	jit_movr(JIT_RET, u);
    jit_live(JIT_RET);
    jit_ret();
    jit_dec_synth();
}

void
reti(jit_state_t *_jit, jit_word_t u)
{
    jit_inc_synth_w(reti, u);
    jit_movi(JIT_RET, u);
    jit_ret();
    jit_dec_synth();
}


void
_jit_retval_c(jit_state_t *_jit, int32_t r0)
{
    jit_inc_synth(retval_c);
    jit_extr_c(r0, JIT_RET);
    jit_dec_synth();
}

void
_jit_retval_uc(jit_state_t *_jit, int32_t r0)
{
    jit_inc_synth(retval_uc);
    jit_extr_uc(r0, JIT_RET);
    jit_dec_synth();
}

void
_jit_retval_s(jit_state_t *_jit, int32_t r0)
{
    jit_inc_synth(retval_s);
    jit_extr_s(r0, JIT_RET);
    jit_dec_synth();
}

void
_jit_retval_us(jit_state_t *_jit, int32_t r0)
{
    jit_inc_synth(retval_us);
    jit_extr_us(r0, JIT_RET);
    jit_dec_synth();
}

void
_jit_retval_i(jit_state_t *_jit, int32_t r0)
{
    jit_inc_synth(retval_i);
#if __WORDSIZE == 32
    if (r0 != JIT_RET)
	jit_movr(r0, JIT_RET);
#else
    jit_extr_i(r0, JIT_RET);
#endif
    jit_dec_synth();
}

#if __WORDSIZE == 64
void
_jit_retval_ui(jit_state_t *_jit, int32_t r0)
{
    jit_inc_synth(retval_ui);
    jit_extr_ui(r0, JIT_RET);
    jit_dec_synth();
}

void
_jit_retval_l(jit_state_t *_jit, int32_t r0)
{
    jit_inc_synth(retval_l);
    if (r0 != JIT_RET)
	jit_movr(r0, JIT_RET);
    jit_dec_synth();
}
#endif
