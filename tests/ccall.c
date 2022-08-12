#include "test.h"

#define _QUOTE(x) #x
#define QUOTE(x) _QUOTE(x)

#if defined(DEBUG)
#define DEBUG(x) DEBUG(x);
#else
#define DEBUG(x)
#endif

#define _w0			0
#define _w1			1
#define _w2			(_w1-2)
#define _w3			(_w2-3)
#define _w4			(_w3-4)
#define _w5			(_w4-5)
#define _w6			(_w5-6)
#define _w7			(_w6-7)
#define _w8			(_w7-8)
#define _w9			(_w8-9)
#define _w10			(_w9-10)
#define _w11			(_w10-11)
#define _w12			(_w11-12)
#define _w13			(_w12-13)
#define _w14			(_w13-14)
#define _w15			(_w14-15)
#define _c0			_w0
#define _c1			_w1
#define _c2			_w2
#define _c3			_w3
#define _c4			_w4
#define _c5			_w5
#define _c6			_w6
#define _c7			_w7
#define _c8			_w8
#define _c9			_w9
#define _c10			_w10
#define _c11			_w11
#define _c12			_w12
#define _c13			_w13
#define _c14			_w14
#define _c15			_w15
#define _uc0			(_w0&0xff)
#define _uc1			(_w1&0xff)
#define _uc2			(_w2&0xff)
#define _uc3			(_w3&0xff)
#define _uc4			(_w4&0xff)
#define _uc5			(_w5&0xff)
#define _uc6			(_w6&0xff)
#define _uc7			(_w7&0xff)
#define _uc8			(_w8&0xff)
#define _uc9			(_w9&0xff)
#define _uc10			(_w10&0xff)
#define _uc11			(_w11&0xff)
#define _uc12			(_w12&0xff)
#define _uc13			(_w13&0xff)
#define _uc14			(_w14&0xff)
#define _uc15			(_w15&0xff)
#define _s0			_w0
#define _s1			_w1
#define _s2			_w2
#define _s3			_w3
#define _s4			_w4
#define _s5			_w5
#define _s6			_w6
#define _s7			_w7
#define _s8			_w8
#define _s9			_w9
#define _s10			_w10
#define _s11			_w11
#define _s12			_w12
#define _s13			_w13
#define _s14			_w14
#define _s15			_w15
#define _us0			(_w0&0xffff)
#define _us1			(_w1&0xffff)
#define _us2			(_w2&0xffff)
#define _us3			(_w3&0xffff)
#define _us4			(_w4&0xffff)
#define _us5			(_w5&0xffff)
#define _us6			(_w6&0xffff)
#define _us7			(_w7&0xffff)
#define _us8			(_w8&0xffff)
#define _us9			(_w9&0xffff)
#define _us10			(_w10&0xffff)
#define _us11			(_w11&0xffff)
#define _us12			(_w12&0xffff)
#define _us13			(_w13&0xffff)
#define _us14			(_w14&0xffff)
#define _us15			(_w15&0xffff)
#define _i0			_w0
#define _i1			_w1
#define _i2			_w2
#define _i3			_w3
#define _i4			_w4
#define _i5			_w5
#define _i6			_w6
#define _i7			_w7
#define _i8			_w8
#define _i9			_w9
#define _i10			_w10
#define _i11			_w11
#define _i12			_w12
#define _i13			_w13
#define _i14			_w14
#define _i15			_w15
#if __WORDSIZE == 64
#  define _ui0			(_w0&0xffffffff)
#  define _ui1			(_w1&0xffffffff)
#  define _ui2			(_w2&0xffffffff)
#  define _ui3			(_w3&0xffffffff)
#  define _ui4			(_w4&0xffffffff)
#  define _ui5			(_w5&0xffffffff)
#  define _ui6			(_w6&0xffffffff)
#  define _ui7			(_w7&0xffffffff)
#  define _ui8			(_w8&0xffffffff)
#  define _ui9			(_w9&0xffffffff)
#  define _ui10			(_w10&0xffffffff)
#  define _ui11			(_w11&0xffffffff)
#  define _ui12			(_w12&0xffffffff)
#  define _ui13			(_w13&0xffffffff)
#  define _ui14			(_w14&0xffffffff)
#  define _ui15			(_w15&0xffffffff)
#  define _l0			_w0
#  define _l1			_w1
#  define _l2			_w2
#  define _l3			_w3
#  define _l4			_w4
#  define _l5			_w5
#  define _l6			_w6
#  define _l7			_w7
#  define _l8			_w8
#  define _l9			_w9
#  define _l10			_w10
#  define _l11			_w11
#  define _l12			_w12
#  define _l13			_w13
#  define _l14			_w14
#  define _l15			_w15
#endif

/*
 * Types
 */
typedef signed char		_c;
typedef unsigned char		_uc;
typedef signed short		_s;
typedef unsigned short		_us;
typedef signed int		_i;
#if __WORDSIZE == 64
typedef unsigned int		_ui;
typedef jit_word_t		_l;
#endif
typedef float			_f;
typedef double			_d;

#define prt0(T)			T C##T##0(void);
#define prt1(T)			prt0(T)					\
				T C##T##1(T);
#define prt2(T)			prt1(T)					\
				T C##T##2(T,T);
#define prt3(T)			prt2(T)					\
				T C##T##3(T,T,T);
#define prt4(T)			prt3(T)					\
				T C##T##4(T,T,T,T);
#define prt5(T)			prt4(T)					\
				T C##T##5(T,T,T,T,T);
#define prt6(T)			prt5(T)					\
				T C##T##6(T,T,T,T,T,T);
#define prt7(T)			prt6(T)					\
				T C##T##7(T,T,T,T,T,T,T);
#define prt8(T)			prt7(T)					\
				T C##T##8(T,T,T,T,T,T,T,T);
#define prt9(T)			prt8(T)					\
				T C##T##9(T,T,T,T,T,T,T,T,T);
#define prt10(T)		prt9(T)					\
				T C##T##10(T,T,T,T,T,T,T,T,T,T);
#define prt11(T)		prt10(T)				\
				T C##T##11(T,T,T,T,T,T,T,T,T,T,T);
#define prt12(T)		prt11(T)				\
				T C##T##12(T,T,T,T,T,T,T,T,T,T,T,T);
#define prt13(T)		prt12(T)				\
				T C##T##13(T,T,T,T,T,T,T,T,T,T,T,T,T);
#define prt14(T)		prt13(T)				\
				T C##T##14(T,T,T,T,T,T,T,T,T,T,T,T,T,T);
#define prt15(T)		prt14(T)				\
				T C##T##15(T,T,T,T,T,T,T,T,T,T,T,T,T,T,T);
#define prt(T)			prt15(T)
prt(_c)
prt(_uc)
prt(_s)
prt(_us)
prt(_i)
#if __WORDSIZE == 64
prt(_ui)
prt(_l)
#endif
prt(_f)
prt(_d)
#undef prt
#undef prt15
#undef prt14
#undef prt13
#undef prt12
#undef prt11
#undef prt10
#undef prt9
#undef prt8
#undef prt7
#undef prt6
#undef prt5
#undef prt4
#undef prt3
#undef prt2
#undef prt1
#undef prt0

#define prtn(N,T)		T J##T##n(void);
#define prt0(T)			prtn(0,T)
#define prt1(T)			prt0(T)			prtn(1,T)
#define prt2(T)			prt1(T)			prtn(2,T)
#define prt3(T)			prt2(T)			prtn(3,T)
#define prt4(T)			prt3(T)			prtn(4,T)
#define prt5(T)			prt4(T)			prtn(5,T)
#define prt6(T)			prt5(T)			prtn(6,T)
#define prt7(T)			prt6(T)			prtn(7,T)
#define prt8(T)			prt7(T)			prtn(8,T)
#define prt9(T)			prt8(T)			prtn(9,T)
#define prt10(T)		prt9(T)			prtn(10,T)
#define prt11(T)		prt10(T)		prtn(11,T)
#define prt12(T)		prt11(T)		prtn(12,T)
#define prt13(T)		prt12(T)		prtn(13,T)
#define prt14(T)		prt13(T)		prtn(14,T)
#define prt15(T)		prt14(T)		prtn(15,T)
#define prt(T)			prt15(T)
prt(_c)
prt(_uc)
prt(_s)
prt(_us)
prt(_i)
#if __WORDSIZE == 64
prt(_ui)
prt(_l)
#endif
prt(_f)
prt(_d)
#undef prt
#undef prt15
#undef prt14
#undef prt13
#undef prt12
#undef prt11
#undef prt10
#undef prt9
#undef prt8
#undef prt7
#undef prt6
#undef prt5
#undef prt4
#undef prt3
#undef prt2
#undef prt1
#undef prt0
#undef prtn

/*
 * Initialization
 */

#define dat0(T)			T (*j##T##0)(void);

#define dat1(T)			dat0(T)					\
				T (*j##T##1)(T);			

#define dat2(T)			dat1(T)					\
				T (*j##T##2)(T,T);			

#define dat3(T)			dat2(T)					\
				T (*j##T##3)(T,T,T);			

#define dat4(T)			dat3(T)					\
				T (*j##T##4)(T,T,T,T);			

#define dat5(T)			dat4(T)					\
				T (*j##T##5)(T,T,T,T,T);		

#define dat6(T)			dat5(T)					\
				T (*j##T##6)(T,T,T,T,T,T);		

#define dat7(T)			dat6(T)					\
				T (*j##T##7)(T,T,T,T,T,T,T);		

#define dat8(T)			dat7(T)					\
				T (*j##T##8)(T,T,T,T,T,T,T,T);		

#define dat9(T)			dat8(T)					\
				T (*j##T##9)(T,T,T,T,T,T,T,T,T);	

#define dat10(T)		dat9(T)					\
				T (*j##T##10)(T,T,T,T,T,T,T,T,T,T);	

#define dat11(T)		dat10(T)				\
				T (*j##T##11)(T,T,T,T,T,T,T,T,T,T,T);	

#define dat12(T)		dat11(T)				\
				T (*j##T##12)(T,T,T,T,T,T,T,T,T,T,T,T);	

#define dat13(T)		dat12(T)				\
				T (*j##T##13)(T,T,T,T,T,T,T,T,T,T,T,T,T);

#define dat14(T)		dat13(T)				\
				T (*j##T##14)(T,T,T,T,T,T,T,T,T,T,T,T,T,T);

#define dat15(T)		dat14(T)				\
				T (*j##T##15)(T,T,T,T,T,T,T,T,T,T,T,T,T,T,T);

#define dat(T)			dat15(T)
dat(_c)
dat(_uc)
dat(_s)
dat(_us)
dat(_i)
#if __WORDSIZE == 64
dat(_ui)
dat(_l)
#endif
dat(_f)
dat(_d)
#undef dat
#undef dat15
#undef dat14
#undef dat13
#undef dat12
#undef dat11
#undef dat10
#undef dat9
#undef dat8
#undef dat7
#undef dat6
#undef dat5
#undef dat4
#undef dat3
#undef dat2
#undef dat1
#undef dat0

/*
 * Implementation
 */
#define dcl0(T)								\
T C##T##0(void)								\
{									\
    DEBUG(QUOTE(C##T##0));\
    return (0);								\
}
#define dcl1(T)								\
dcl0(T)									\
T C##T##1(T A)								\
{									\
    DEBUG(QUOTE(C##T##1));\
    return (A);								\
}
#define dcl2(T)								\
dcl1(T)									\
T C##T##2(T A,T B)							\
{									\
    DEBUG(QUOTE(C##T##2));\
    return (A-B);							\
}
#define dcl3(T)								\
dcl2(T)									\
T C##T##3(T A,T B,T C)							\
{									\
    DEBUG(QUOTE(C##T##3));\
    return (A-B-C);							\
}
#define dcl4(T)								\
dcl3(T)									\
T C##T##4(T A,T B,T C,T D)						\
{									\
    DEBUG(QUOTE(C##T##4));\
    return (A-B-C-D);							\
}
#define dcl5(T)								\
dcl4(T)									\
T C##T##5(T A,T B,T C,T D,T E)						\
{									\
    DEBUG(QUOTE(C##T##5));\
    return (A-B-C-D-E);							\
}
#define dcl6(T)								\
dcl5(T)									\
T C##T##6(T A,T B,T C,T D,T E,T F)					\
{									\
    DEBUG(QUOTE(C##T##6));\
    return (A-B-C-D-E-F);						\
}
#define dcl7(T)								\
dcl6(T)									\
T C##T##7(T A,T B,T C,T D,T E,T F,T G)					\
{									\
    DEBUG(QUOTE(C##T##7));\
    return (A-B-C-D-E-F-G);						\
}
#define dcl8(T)								\
dcl7(T)									\
T C##T##8(T A,T B,T C,T D,T E,T F,T G,T H)				\
{									\
    DEBUG(QUOTE(C##T##8));\
    return (A-B-C-D-E-F-G-H);						\
}
#define dcl9(T)								\
dcl8(T)									\
T C##T##9(T A,T B,T C,T D,T E,T F,T G,T H,T I)				\
{									\
    DEBUG(QUOTE(C##T##9));\
    return (A-B-C-D-E-F-G-H-I);						\
}
#define dcl10(T)							\
dcl9(T)									\
T C##T##10(T A,T B,T C,T D,T E,T F,T G,T H,T I,T J)			\
{									\
    DEBUG(QUOTE(C##T##10));\
    return (A-B-C-D-E-F-G-H-I-J);					\
}
#define dcl11(T)							\
dcl10(T)								\
T C##T##11(T A,T B,T C,T D,T E,T F,T G,T H,T I,T J,T K)			\
{									\
    DEBUG(QUOTE(C##T##11));\
    return (A-B-C-D-E-F-G-H-I-J-K);					\
}
#define dcl12(T)							\
dcl11(T)								\
T C##T##12(T A,T B,T C,T D,T E,T F,T G,T H,T I,T J,T K,T L)		\
{									\
    DEBUG(QUOTE(C##T##12));\
    return (A-B-C-D-E-F-G-H-I-J-K-L);					\
}
#define dcl13(T)							\
dcl12(T)								\
T C##T##13(T A,T B,T C,T D,T E,T F,T G,T H,T I,T J,T K,T L,T M)		\
{									\
    DEBUG(QUOTE(C##T##13));\
    return (A-B-C-D-E-F-G-H-I-J-K-L-M);					\
}
#define dcl14(T)							\
dcl13(T)								\
T C##T##14(T A,T B,T C,T D,T E,T F,T G,T H,T I,T J,T K,T L,T M,T N)	\
{									\
    DEBUG(QUOTE(C##T##14));\
    return (A-B-C-D-E-F-G-H-I-J-K-L-M-N);				\
}
#define dcl15(T)							\
dcl14(T)								\
T C##T##15(T A,T B,T C,T D,T E,T F,T G,T H,T I,T J,T K,T L,T M,T N,T O)	\
{									\
    DEBUG(QUOTE(C##T##15));\
    return (A-B-C-D-E-F-G-H-I-J-K-L-M-N-O);				\
}
#define dcl(T)	dcl15(T)
dcl(_c)
dcl(_uc)
dcl(_s)
dcl(_us)
dcl(_i)
#if __WORDSIZE == 64
dcl(_ui)
dcl(_l)
#endif
dcl(_f)
dcl(_d)
#undef dcl
#undef dcl15
#undef dcl14
#undef dcl13
#undef dcl12
#undef dcl11
#undef dcl10
#undef dcl9
#undef dcl8
#undef dcl7
#undef dcl6
#undef dcl5
#undef dcl4
#undef dcl3
#undef dcl2
#undef dcl1
#undef dcl0

#define dcl0(T)								\
T CJ##T##0(void)							\
{									\
    DEBUG(QUOTE(CJ##T##0));\
    return ((*j##T##0)());						\
}
#define dcl1(T)								\
dcl0(T)									\
T CJ##T##1(void)							\
{									\
    DEBUG(QUOTE(CJ##T##1));\
    return ((*j##T##1)(1));						\
}
#define dcl2(T)								\
dcl1(T)									\
T CJ##T##2(void)							\
{									\
    DEBUG(QUOTE(CJ##T##2));\
    return ((*j##T##2)(1,2));						\
}
#define dcl3(T)								\
dcl2(T)									\
T CJ##T##3(void)							\
{									\
    DEBUG(QUOTE(CJ##T##3));\
    return ((*j##T##3)(1,2,3));						\
}
#define dcl4(T)								\
dcl3(T)									\
T CJ##T##4(void)							\
{									\
    DEBUG(QUOTE(CJ##T##4));\
    return ((*j##T##4)(1,2,3,4));					\
}
#define dcl5(T)								\
dcl4(T)									\
T CJ##T##5(void)							\
{									\
    DEBUG(QUOTE(CJ##T##5));\
    return ((*j##T##5)(1,2,3,4,5));					\
}
#define dcl6(T)								\
dcl5(T)									\
T CJ##T##6(void)							\
{									\
    DEBUG(QUOTE(CJ##T##6));\
    return ((*j##T##6)(1,2,3,4,5,6));					\
}
#define dcl7(T)								\
dcl6(T)									\
T CJ##T##7(void)							\
{									\
    DEBUG(QUOTE(CJ##T##7));\
    return ((*j##T##7)(1,2,3,4,5,6,7));					\
}
#define dcl8(T)								\
dcl7(T)									\
T CJ##T##8(void)							\
{									\
    DEBUG(QUOTE(CJ##T##8));\
    return ((*j##T##8)(1,2,3,4,5,6,7,8));				\
}
#define dcl9(T)								\
dcl8(T)									\
T CJ##T##9(void)							\
{									\
    DEBUG(QUOTE(CJ##T##9));\
    return ((*j##T##9)(1,2,3,4,5,6,7,8,9));				\
}
#define dcl10(T)							\
dcl9(T)									\
T CJ##T##10(void)							\
{									\
    DEBUG(QUOTE(CJ##T##10));\
    return ((*j##T##10)(1,2,3,4,5,6,7,8,9,10));				\
}
#define dcl11(T)							\
dcl10(T)								\
T CJ##T##11(void)							\
{									\
    DEBUG(QUOTE(CJ##T##11));\
    return ((*j##T##11)(1,2,3,4,5,6,7,8,9,10,11));			\
}
#define dcl12(T)							\
dcl11(T)								\
T CJ##T##12(void)							\
{									\
    DEBUG(QUOTE(CJ##T##12));\
    return ((*j##T##12)(1,2,3,4,5,6,7,8,9,10,11,12));			\
}
#define dcl13(T)							\
dcl12(T)								\
T CJ##T##13(void)							\
{									\
    DEBUG(QUOTE(CJ##T##13));\
    return ((*j##T##13)(1,2,3,4,5,6,7,8,9,10,11,12,13));		\
}
#define dcl14(T)							\
dcl13(T)								\
T CJ##T##14(void)							\
{									\
    DEBUG(QUOTE(CJ##T##14));\
    return ((*j##T##14)(1,2,3,4,5,6,7,8,9,10,11,12,13,14));		\
}
#define dcl15(T)							\
dcl14(T)								\
T CJ##T##15(void)							\
{									\
    DEBUG(QUOTE(CJ##T##15));\
    return ((*j##T##15)(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15));		\
}
#define dcl(t)	dcl15(t)
dcl(_c)
dcl(_uc)
dcl(_s)
dcl(_us)
dcl(_i)
#if __WORDSIZE == 64
dcl(_ui)
dcl(_l)
#endif
dcl(_f)
dcl(_d)
#undef dcl
#undef dcl15
#undef dcl14
#undef dcl13
#undef dcl12
#undef dcl11
#undef dcl10
#undef dcl9
#undef dcl8
#undef dcl7
#undef dcl6
#undef dcl5
#undef dcl4
#undef dcl3
#undef dcl2
#undef dcl1
#undef dcl0

size_t
run_test(jit_state_t *_jit, uint8_t *code_base, size_t code_size)
{
    jit_reloc_t		 jmpi_main;
    void		(*function)(void);
    jit_reloc_t		 jmp;

    jit_begin(_jit, code_base, code_size);

    jmpi_main = jit_jmp(_jit);

#define calc(B,T,R,O)\
    jit_movr##B(_jit, R##1, R##0);\
    jit_ldxi##T(_jit, R##0, JIT_SP, 8 * O);\
    jit_subr##B(_jit, R##0, R##1, R##0);

#define get0(B,T,R)		jit_movi##B(_jit, R##0, 0);
#define get1(B,T,R)		jit_ldxi##T(_jit, R##0, JIT_SP, 8 * 0);
#define get2(B,T,R)							\
	get1(B,T,R);							\
	calc(B,T,R,1);
#define get3(B,T,R)							\
	get2(B,T,R);							\
	calc(B,T,R,2);
#define get4(B,T,R)							\
	get3(B,T,R);							\
	calc(B,T,R,3);
#define get5(B,T,R)							\
	get4(B,T,R);							\
	calc(B,T,R,4);
#define get6(B,T,R)							\
	get5(B,T,R);							\
	calc(B,T,R,5);
#define get7(B,T,R)							\
	get6(B,T,R);							\
	calc(B,T,R,6);
#define get8(B,T,R)							\
	get7(B,T,R);							\
	calc(B,T,R,7);
#define get9(B,T,R)							\
	get8(B,T,R);							\
	calc(B,T,R,8);
#define get10(B,T,R)							\
	get9(B,T,R);							\
	calc(B,T,R,9);
#define get11(B,T,R)							\
	get10(B,T,R);							\
	calc(B,T,R,10);
#define get12(B,T,R)							\
	get11(B,T,R);							\
	calc(B,T,R,11);
#define get13(B,T,R)							\
	get12(B,T,R);							\
	calc(B,T,R,12);
#define get14(B,T,R)							\
	get13(B,T,R);							\
	calc(B,T,R,13);
#define get15(B,T,R)							\
	get14(B,T,R);							\
	calc(B,T,R,14);

#if __WORDSIZE == 32
#  define jit_extr_i(_jit, u, v)			/**/
#else
#  define jit_extr_l(_jit, u, v)			/**/
#endif

#if __WORDSIZE == 64
#define jit_stxi_ui(_jit, u, r0, r1) jit_stxi_i(_jit, u, r0, r1)
#endif
#define jit_stxi_us(_jit, u, r0, r1) jit_stxi_s(_jit, u, r0, r1)
#define jit_stxi_uc(_jit, u, r0, r1) jit_stxi_c(_jit, u, r0, r1)

#define abi_uc JIT_OPERAND_ABI_UINT8
#define abi_c JIT_OPERAND_ABI_INT8
#define abi_us JIT_OPERAND_ABI_UINT16
#define abi_s JIT_OPERAND_ABI_INT16
#define abi_ui JIT_OPERAND_ABI_UINT32
#define abi_i JIT_OPERAND_ABI_INT32
#define abi_ul JIT_OPERAND_ABI_UINT64
#define abi_l JIT_OPERAND_ABI_INT64
#define abi_f JIT_OPERAND_ABI_FLOAT
#define abi_d JIT_OPERAND_ABI_DOUBLE

#define store0(T) jit_operand_mem(JIT_OPERAND_ABI_UINT8, JIT_SP, 0)
#define store1(T) jit_operand_mem(abi##T, JIT_SP, 0 * 8)
#define store2(T) store1(T), jit_operand_mem(abi##T, JIT_SP, 1 * 8)
#define store3(T) store2(T), jit_operand_mem(abi##T, JIT_SP, 2 * 8)
#define store4(T) store3(T), jit_operand_mem(abi##T, JIT_SP, 3 * 8)
#define store5(T) store4(T), jit_operand_mem(abi##T, JIT_SP, 4 * 8)
#define store6(T) store5(T), jit_operand_mem(abi##T, JIT_SP, 5 * 8)
#define store7(T) store6(T), jit_operand_mem(abi##T, JIT_SP, 6 * 8)
#define store8(T) store7(T), jit_operand_mem(abi##T, JIT_SP, 7 * 8)
#define store9(T) store8(T), jit_operand_mem(abi##T, JIT_SP, 8 * 8)
#define store10(T) store9(T), jit_operand_mem(abi##T, JIT_SP, 9 * 8)
#define store11(T) store10(T), jit_operand_mem(abi##T, JIT_SP, 10 * 8)
#define store12(T) store11(T), jit_operand_mem(abi##T, JIT_SP, 11 * 8)
#define store13(T) store12(T), jit_operand_mem(abi##T, JIT_SP, 12 * 8)
#define store14(T) store13(T), jit_operand_mem(abi##T, JIT_SP, 13 * 8)
#define store15(T) store14(T), jit_operand_mem(abi##T, JIT_SP, 14 * 8)

// Placeholder, won't actually be used.
#define load0(T) jit_operand_mem(JIT_OPERAND_ABI_INT8, JIT_SP, 0)
#define load1(T) jit_operand_mem(abi##T, JIT_SP, 0 * 8)
#define load2(T) load1(T), jit_operand_mem(abi##T, JIT_SP, 1 * 8)
#define load3(T) load2(T), jit_operand_mem(abi##T, JIT_SP, 2 * 8)
#define load4(T) load3(T), jit_operand_mem(abi##T, JIT_SP, 3 * 8)
#define load5(T) load4(T), jit_operand_mem(abi##T, JIT_SP, 4 * 8)
#define load6(T) load5(T), jit_operand_mem(abi##T, JIT_SP, 5 * 8)
#define load7(T) load6(T), jit_operand_mem(abi##T, JIT_SP, 6 * 8)
#define load8(T) load7(T), jit_operand_mem(abi##T, JIT_SP, 7 * 8)
#define load9(T) load8(T), jit_operand_mem(abi##T, JIT_SP, 8 * 8)
#define load10(T) load9(T), jit_operand_mem(abi##T, JIT_SP, 9 * 8)
#define load11(T) load10(T), jit_operand_mem(abi##T, JIT_SP, 10 * 8)
#define load12(T) load11(T), jit_operand_mem(abi##T, JIT_SP, 11 * 8)
#define load13(T) load12(T), jit_operand_mem(abi##T, JIT_SP, 12 * 8)
#define load14(T) load13(T), jit_operand_mem(abi##T, JIT_SP, 13 * 8)
#define load15(T) load14(T), jit_operand_mem(abi##T, JIT_SP, 14 * 8)

#define defi(T, N)							\
    {									\
    j##T##N = jit_address(_jit);					\
    size_t frame = jit_enter_jit_abi(_jit, 0, 0, 0);			\
    size_t stack = jit_align_stack(_jit, N * 8);			\
    jit_operand_t args[] = {store##N(T)};				\
    jit_load_args(_jit, N, args);					\
    get##N(,T,JIT_R)							\
    jit_extr##T(_jit, JIT_R0, JIT_R0);					\
    jit_shrink_stack(_jit, stack);					\
    jit_leave_jit_abi(_jit, 0, 0, frame);				\
    jit_retr(_jit, JIT_R0);						\
    }

#define deff(T, N)							\
    {									\
    j##T##N = jit_address(_jit);					\
    size_t frame = jit_enter_jit_abi(_jit, 0, 0, 0);			\
    size_t stack = jit_align_stack(_jit, N * 8);			\
    jit_operand_t args[] = {store##N(T)};				\
    jit_load_args(_jit, N, args);					\
    get##N(T,T,JIT_F);							\
    jit_shrink_stack(_jit, stack);					\
    jit_leave_jit_abi(_jit, 0, 0, frame);				\
    jit_retr##T(_jit, JIT_F0);						\
    }

#define  def0(X, T)				def##X(T, 0)
#define  def1(X, T)	def0(X, T)		def##X(T, 1)
#define  def2(X, T)	def1(X, T)		def##X(T, 2)
#define  def3(X, T)	def2(X, T)		def##X(T, 3)
#define  def4(X, T)	def3(X, T)		def##X(T, 4)
#define  def5(X, T)	def4(X, T)		def##X(T, 5)
#define  def6(X, T)	def5(X, T)		def##X(T, 6)
#define  def7(X, T)	def6(X, T)		def##X(T, 7)
#define  def8(X, T)	def7(X, T)		def##X(T, 8)
#define  def9(X, T)	def8(X, T)		def##X(T, 9)
#define def10(X, T)	def9(X, T)		def##X(T, 10)
#define def11(X, T)	def10(X, T)		def##X(T, 11)
#define def12(X, T)	def11(X, T)		def##X(T, 12)
#define def13(X, T)	def12(X, T)		def##X(T, 13)
#define def14(X, T)	def13(X, T)		def##X(T, 14)
#define def15(X, T)	def14(X, T)		def##X(T, 15)
#define def(T)		def15(i, T)
	def(_c)
	def(_uc)
	def(_s)
	def(_us)
	def(_i)
#if __WORDSIZE == 64
	def(_ui)
	def(_l)
#endif
#undef def
#define def(T)		def15(f, T)
	def(_f)
	def(_d)
#undef def

    jit_patch_here(_jit, jmpi_main);
    size_t frame = jit_enter_jit_abi(_jit, 0, 0, 0);
    size_t stack = jit_align_stack(_jit, 15 * 8);

#define  push0(B,T,R)	/**/
#define  push1(B,T,R)\
    jit_movi##B(_jit, R##0, 1);\
    jit_stxi##T(_jit, 0 * 8, JIT_SP, R##0);

#define  push2(B,T,R)\
    push1(B,T,R)\
    jit_movi##B(_jit, R##0, 2);\
    jit_stxi##T(_jit, 1 * 8, JIT_SP, R##0);

#define  push3(B,T,R)\
    push2(B,T,R)\
    jit_movi##B(_jit, R##0, 3);\
    jit_stxi##T(_jit, 2 * 8, JIT_SP, R##0);

#define  push4(B,T,R)\
    push3(B,T,R)\
    jit_movi##B(_jit, R##0, 4);\
    jit_stxi##T(_jit, 3 * 8, JIT_SP, R##0);

#define  push5(B,T,R)\
    push4(B,T,R)\
    jit_movi##B(_jit, R##0, 5);\
    jit_stxi##T(_jit, 4 * 8, JIT_SP, R##0);

#define  push6(B,T,R)\
    push5(B,T,R)\
    jit_movi##B(_jit, R##0, 6);\
    jit_stxi##T(_jit, 5 * 8, JIT_SP, R##0);

#define  push7(B,T,R)\
    push6(B,T,R)\
    jit_movi##B(_jit, R##0, 7);\
    jit_stxi##T(_jit, 6 * 8, JIT_SP, R##0);

#define  push8(B,T,R)\
    push7(B,T,R)\
    jit_movi##B(_jit, R##0, 8);\
    jit_stxi##T(_jit, 7 * 8, JIT_SP, R##0);

#define  push9(B,T,R)\
    push8(B,T,R)\
    jit_movi##B(_jit, R##0, 9);\
    jit_stxi##T(_jit, 8 * 8, JIT_SP, R##0);

#define  push10(B,T,R)\
    push9(B,T,R)\
    jit_movi##B(_jit, R##0, 10);\
    jit_stxi##T(_jit, 9 * 8, JIT_SP, R##0);

#define  push11(B,T,R)\
    push10(B,T,R)\
    jit_movi##B(_jit, R##0, 11);\
    jit_stxi##T(_jit, 10 * 8, JIT_SP, R##0);

#define  push12(B,T,R)\
    push11(B,T,R)\
    jit_movi##B(_jit, R##0, 12);\
    jit_stxi##T(_jit, 11 * 8, JIT_SP, R##0);

#define  push13(B,T,R)\
    push12(B,T,R)\
    jit_movi##B(_jit, R##0, 13);\
    jit_stxi##T(_jit, 12 * 8, JIT_SP, R##0);

#define  push14(B,T,R)\
    push13(B,T,R)\
    jit_movi##B(_jit, R##0, 14);\
    jit_stxi##T(_jit, 13 * 8, JIT_SP, R##0);

#define  push15(B,T,R)\
    push14(B,T,R)\
    jit_movi##B(_jit, R##0, 15);\
    jit_stxi##T(_jit, 14 * 8, JIT_SP, R##0);

#define calin(T,N)							\
    {									\
	push##N(, T, JIT_R)						\
	jit_operand_t args[] = {load##N(T)};				\
	jit_calli(_jit, C##T##N, N, args);				\
	jit_retval##T(_jit, JIT_R0);					\
	jit_movi(_jit, JIT_R1, T##N);					\
	jmp = jit_beqr(_jit, JIT_R0, JIT_R1);				\
	jit_calli_0(_jit, abort);					\
	jit_patch_here(_jit, jmp);					\
    }

#define calfn(T,N)							\
    {									\
	push##N(T, T, JIT_F)						\
	jit_operand_t args[] = {load##N(T)};				\
	jit_calli(_jit, C##T##N, N, args);				\
	jit_retval##T(_jit, JIT_F0);					\
	jit_movi##T(_jit, JIT_F1, _w##N);				\
	jmp = jit_beqr##T(_jit, JIT_F0, JIT_F1);			\
	jit_calli_0(_jit, abort);					\
	jit_patch_here(_jit, jmp);					\
    }
#define  calx0(X,T)				cal##X##n(T,0)
#define  calx1(X,T)	calx0(X,T)		cal##X##n(T,1)
#define  calx2(X,T)	calx1(X,T)		cal##X##n(T,2)
#define  calx3(X,T)	calx2(X,T)		cal##X##n(T,3)
#define  calx4(X,T)	calx3(X,T)		cal##X##n(T,4)
#define  calx5(X,T)	calx4(X,T)		cal##X##n(T,5)
#define  calx6(X,T)	calx5(X,T)		cal##X##n(T,6)
#define  calx7(X,T)	calx6(X,T)		cal##X##n(T,7)
#define  calx8(X,T)	calx7(X,T)		cal##X##n(T,8)
#define  calx9(X,T)	calx8(X,T)		cal##X##n(T,9)
#define calx10(X,T)	calx9(X,T)		cal##X##n(T,10)
#define calx11(X,T)	calx10(X,T)		cal##X##n(T,11)
#define calx12(X,T)	calx11(X,T)		cal##X##n(T,12)
#define calx13(X,T)	calx12(X,T)		cal##X##n(T,13)
#define calx14(X,T)	calx13(X,T)		cal##X##n(T,14)
#define calx15(X,T)	calx14(X,T)		cal##X##n(T,15)
#define cali(T)		calx15(i,T)
#define calf(T)		calx15(f,T)

    cali(_c)
    cali(_uc)
    cali(_s)
    cali(_us)
    cali(_i)
#if __WORDSIZE == 64
    cali(_ui)
    cali(_l)
#endif
    calf(_f)
    calf(_d)

#undef calin
#undef calfn
#define calin(T,N)							\
    {									\
	push##N(, T, JIT_R)						\
	jit_operand_t args[] = {load##N(T)};				\
	jit_calli(_jit, CJ##T##N, N, args);		    		\
	jit_retval##T(_jit, JIT_R0);				    	\
	jit_movi(_jit, JIT_R1, T##N);					\
	jmp = jit_beqr(_jit, JIT_R0, JIT_R1);				\
	jit_calli_0(_jit, abort);					\
	jit_patch_here(_jit, jmp);					\
    }

#define calfn(T,N)							\
    {									\
	push##N(T, T, JIT_F)						\
	jit_operand_t args[] = {load##N(T)};				\
	jit_calli(_jit, CJ##T##N, N, args);		    		\
	jit_retval##T(_jit, JIT_F0);					\
	jit_movi##T(_jit, JIT_F1, _w##N);				\
	jmp = jit_beqr##T(_jit, JIT_F0, JIT_F1);			\
	jit_calli_0(_jit, abort);					\
	jit_patch_here(_jit, jmp);					\
    }

    cali(_c)
    cali(_uc)
    cali(_s)
    cali(_us)
    cali(_i)
#if __WORDSIZE == 64
    cali(_ui)
    cali(_l)
#endif
    calf(_f)
    calf(_d)

    jit_shrink_stack(_jit, stack);
    jit_leave_jit_abi(_jit, 0, 0, frame);
    jit_ret(_jit);

    size_t size = 0;
    function = jit_end(_jit, &size);

    if (function)
	(*function)();
    else
	return size;

    DEBUG("ok\n");

    return 0;
}

int main(int argc, char *argv[])
{
    return main_compiler(argc, argv, run_test);
}
