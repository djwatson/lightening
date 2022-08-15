#include "test.h"

/* do not bother about result of operations, only ensure valid arguments
 * and that registers not modified by the operation are not clobbered  */

#define IV0		0x10000
#define IV1		0x10001
#define IV2		0x10002
#define IV3		0x10003
#define IV4		0x10004
#define IV5		0x10005
#define FV0		100.0
#define FV1		101.0
#define FV2		102.0
#define FV3		103.0
#define FV4		104.0
#define FV5		105.0
#define IR0		JIT_R0
#define IR1		JIT_R1
#define IR2		JIT_R2
#define IR3		JIT_V0
#define IR4		JIT_V1
#define IR5		JIT_V2
#define FR0		JIT_F0
#define FR1		JIT_F1
#define FR2		JIT_F2
#define FR3		JIT_F3
#define FR4		JIT_F4
#define FR5		JIT_F5

#define setup()							\
	jit_movi(_jit, JIT_R0, IV0);				\
	jit_movi(_jit, JIT_R1, IV1);				\
	jit_movi(_jit, JIT_R2, IV2);				\
	jit_movi(_jit, JIT_V0, IV3);				\
	jit_movi(_jit, JIT_V1, IV4);				\
	jit_movi(_jit, JIT_V2, IV5);

#define setup_f()						\
	jit_movi_f(_jit, JIT_F0, FV0);				\
	jit_movi_f(_jit, JIT_F1, FV1);				\
	jit_movi_f(_jit, JIT_F2, FV2);				\
	jit_movi_f(_jit, JIT_F3, FV3);				\
	jit_movi_f(_jit, JIT_F4, FV4);				\
	jit_movi_f(_jit, JIT_F5, FV5);

#define setup_d()						\
	jit_movi_d(_jit, JIT_F0, FV0);				\
	jit_movi_d(_jit, JIT_F1, FV1);				\
	jit_movi_d(_jit, JIT_F2, FV2);				\
	jit_movi_d(_jit, JIT_F3, FV3);				\
	jit_movi_d(_jit, JIT_F4, FV4);				\
	jit_movi_d(_jit, JIT_F5, FV5);

#define check(label, rn)					\
{								\
	jit_reloc_t r = jit_beqi(_jit, IR##rn, IV##rn);		\
	jit_calli_0(_jit, abort);				\
	jit_patch_here(_jit, r);				\
}

#define check1(k, l, i0)					\
	check(k##l##i0##_0, i0)

#define check2(k, l, i0, i1)					\
	check(k##l##i0##i1##_0, i0)				\
	check(k##l##i0##i1##_1, i1)

#define check3(k, l, i0, i1, i2)				\
	check(k##l##i0##i1##i2##_0, i0)				\
	check(k##l##i0##i1##i2##_1, i1)				\
	check(k##l##i0##i1##i2##_2, i2)

#define check4(k, l, i0, i1, i2, i3)				\
	check(k##l##i0##i1##i2##i3##_0, i0)			\
	check(k##l##i0##i1##i2##i3##_1, i1)			\
	check(k##l##i0##i1##i2##i3##_2, i2)			\
	check(k##l##i0##i1##i2##i3##_3, i3)

#define check5(k, l, i0, i1, i2, i3, i4)			\
	check(k##l##i0##i1##i2##i3##i4##_0, i0)			\
	check(k##l##i0##i1##i2##i3##i4##_1, i1)			\
	check(k##l##i0##i1##i2##i3##i3##_2, i2)			\
	check(k##l##i0##i1##i2##i3##i4##_3, i3)			\
	check(k##l##i0##i1##i2##i3##i4##_4, i4)

#define check6(k, l, i0, i1, i2, i3, i4, i5)			\
	check(k##l##i0##i1##i2##i3##i4##i5##_0, i0)		\
	check(k##l##i0##i1##i2##i3##i4##i5##_1, i1)		\
	check(k##l##i0##i1##i2##i3##i3##i5##_2, i2)		\
	check(k##l##i0##i1##i2##i3##i4##i5##_3, i3)		\
	check(k##l##i0##i1##i2##i3##i4##i5##_4, i4)		\
	check(k##l##i0##i1##i2##i3##i4##i5##_5, i5)

/* slightly hacky, lightning only uses JIT_F0-F5, and since all lightening
 * platforms (at least at the moment) support JIT_F6, we can use it as a
 * temporary register to get the value to compare agains in to the beqrf.
 */
#define checkf(f, label, rn)					\
{								\
	jit_movi##f(_jit, JIT_F6, FV##rn);			\
	jit_reloc_t r = jit_beqr##f(_jit, FR##rn, JIT_F6);	\
	jit_calli_0(_jit, abort);				\
	jit_patch_here(_jit, r);				\
}

#define checkf1(f, k, l, i0)					\
	checkf(f, f##k##l##i0##_0, i0)

#define checkf2(f, k, l, i0, i1)				\
	checkf(f, f##k##l##i0##i1##_0, i0)			\
	checkf(f, f##k##l##i0##i1##_1, i1)

#define checkf3(f, k, l, i0, i1, i2)				\
	checkf(f, f##k##l##i0##i1##i2##_0, i0)			\
	checkf(f, f##k##l##i0##i1##i2##_1, i1)			\
	checkf(f, f##k##l##i0##i1##i2##_2, i2)

#define checkf4(f, k, l, i0, i1, i2, i3)			\
	checkf(f, f##k##l##i0##i1##i2##i3##_0, i0)		\
	checkf(f, f##k##l##i0##i1##i2##i3##_1, i1)		\
	checkf(f, f##k##l##i0##i1##i2##i3##_2, i2)		\
	checkf(f, f##k##l##i0##i1##i2##i3##_3, i3)

#define checkf5(f, k, l, i0, i1, i2, i3, i4)			\
	checkf(f, f##k##l##i0##i1##i2##i3##i4##_0, i0)		\
	checkf(f, f##k##l##i0##i1##i2##i3##i4##_1, i1)		\
	checkf(f, f##k##l##i0##i1##i2##i3##i3##_2, i2)		\
	checkf(f, f##k##l##i0##i1##i2##i3##i4##_3, i3)		\
	checkf(f, f##k##l##i0##i1##i2##i3##i4##_4, i4)

#define checkf6(f, k, l, i0, i1, i2, i3, i4, i5)		\
	checkf(f, f##k##l##i0##i1##i2##i3##i4##i5##_0, i0)	\
	checkf(f, f##k##l##i0##i1##i2##i3##i4##i5##_1, i1)	\
	checkf(f, f##k##l##i0##i1##i2##i3##i3##i5##_2, i2)	\
	checkf(f, f##k##l##i0##i1##i2##i3##i4##i5##_3, i3)	\
	checkf(f, f##k##l##i0##i1##i2##i3##i4##i5##_4, i4)	\
	checkf(f, f##k##l##i0##i1##i2##i3##i4##i5##_5, i5)

#define alui(l, op, i0, i1, i2, i3, i4, i5)			\
	setup()							\
	jit_movi(_jit, IR##i0, 1);				\
	jit_##op##i(_jit, IR##i1, IR##i0, 1);			\
	check4(i, l, i2, i3, i4, i5)

#define aluic(l, op, i0, i1, i2, i3, i4, i5)			\
	setup()							\
	jit_movi(_jit, IR##i0, 1);				\
	jit_##op##i(_jit, IR##i0, IR##i0, 1);			\
	check5(ic, l, i1, i2, i3, i4, i5)

#define alur(l, op, i0, i1, i2, i3, i4, i5)			\
	setup()							\
	jit_movi(_jit, IR##i0, 1);				\
	jit_movi(_jit, IR##i1, 1);				\
	jit_##op##r(_jit, IR##i2, IR##i0, IR##i1);		\
	check3(r, l, i3, i4, i5)

#define alurc0(l, op, i0, i1, i2, i3, i4, i5)			\
	setup()							\
	jit_movi(_jit, IR##i0, 1);				\
	jit_movi(_jit, IR##i1, 1);				\
	jit_##op##r(_jit, IR##i0, IR##i0, IR##i1);		\
	check4(r0, l, i2, i3, i4, i5)

#define alurc1(l, op, i0, i1, i2, i3, i4, i5)			\
	setup()							\
	jit_movi(_jit, IR##i0, 1);				\
	jit_movi(_jit, IR##i1, 1);				\
	jit_##op##r(_jit, IR##i1, IR##i0, IR##i1);		\
	check4(r1, l, i2, i3, i4, i5)

#define alurc2(l, op, i0, i1, i2, i3, i4, i5)			\
	setup()							\
	jit_movi(_jit, IR##i0, 1);				\
	jit_##op##r(_jit, IR##i0, IR##i0, IR##i0);		\
	check5(r2, l, i1, i2, i3, i4, i5)

#define   xalu(l, op, i0, i1, i2, i3, i4, i5)			\
	  alui(l, op, i0, i1,	i2, i3, i4, i5)			\
	 aluic(l, op, i0,		i1, i2, i3, i4, i5)	\
	  alur(l, op, i0, i1, i2,	i3, i4, i5)		\
	alurc0(l, op, i0, i1,	i2, i3, i4, i5)			\
	alurc1(l, op, i0, i1,	i2, i3, i4, i5)			\
	alurc2(l, op, i0,		i1, i2, i3, i4, i5)

#if __ia64__
#  define alu(l, op)						\
	 xalu(l, op, 0, 1, 2, 3, 4, 5)
#else
#  define alu(l, op)						\
	 xalu(l, op, 0, 1, 2, 3, 4, 5)				\
	 xalu(l, op, 1, 2, 3, 4, 5, 0)				\
	 xalu(l, op, 2, 3, 4, 5, 0, 1)				\
	 xalu(l, op, 3, 4, 5, 0, 1, 2)				\
	 xalu(l, op, 4, 5, 0, 1, 2, 3)				\
	 xalu(l, op, 5, 0, 1, 2, 3, 4)
#endif

#define fopi(f, l, op, f0, f1, f2, f3, f4, f5)			\
	setup##f()						\
	jit_movi##f(_jit, FR##f0, 1.0);				\
	jit_movi##f(_jit, JIT_F6, 1.0);				\
	jit_##op##r##f(_jit, FR##f1, FR##f0, JIT_F6);		\
	checkf4(f, i, l, f2, f3, f4, f5)

#define fopic(f, l, op, f0, f1, f2, f3, f4, f5)			\
	setup##f()						\
	jit_movi##f(_jit, FR##f0, 1.0);				\
	jit_movi##f(_jit, JIT_F6, 1.0);				\
	jit_##op##r##f(_jit, FR##f0, FR##f0, JIT_F6);		\
	checkf5(f, ic, l, f1, f2, f3, f4, f5)

#define fopr(f, l, op, f0, f1, f2, f3, f4, f5)			\
	setup##f()						\
	jit_movi##f(_jit, FR##f0, 1.0);				\
	jit_movi##f(_jit, FR##f1, 1.0);				\
	jit_##op##r##f(_jit, FR##f2, FR##f0, FR##f1);		\
	checkf3(f, r, l, f3, f4, f5)

#define foprc0(f, l, op, f0, f1, f2, f3, f4, f5)		\
	setup##f()						\
	jit_movi##f(_jit, FR##f0, 1.0);				\
	jit_movi##f(_jit, FR##f1, 1.0);				\
	jit_##op##r##f(_jit, FR##f0, FR##f0, FR##f1);		\
	checkf4(f, r0, l, f2, f3, f4, f5)

#define foprc1(f, l, op, f0, f1, f2, f3, f4, f5)		\
	setup##f()						\
	jit_movi##f(_jit, FR##f0, 1.0);				\
	jit_movi##f(_jit, FR##f1, 1.0);				\
	jit_##op##r##f(_jit, FR##f1, FR##f0, FR##f1);		\
	checkf4(f, r1, l, f2, f3, f4, f5)

#define foprc2(f, l, op, f0, f1, f2, f3, f4, f5)		\
	setup##f()						\
	jit_movi##f(_jit, FR##f0, 1.0);				\
	jit_##op##r##f(_jit, FR##f0, FR##f0, FR##f0);		\
	checkf5(f, r2, l, f1, f2, f3, f4, f5)

#define   xfop(f, l, op, f0, f1, f2, f3, f4, f5)		\
	  fopi(f, l, op, f0, f1, f2,		f3, f4, f5)	\
	 fopic(f, l, op, f0, f1, f2,		f3, f4, f5)	\
	  fopr(f, l, op, f0, f1, f2,		f3, f4, f5)	\
	foprc0(f, l, op, f0, f1,		f2, f3, f4, f5)	\
	foprc1(f, l, op, f0, f1,		f2, f3, f4, f5)	\
	foprc2(f, l, op, f0, f1,		f2, f3, f4, f5)
#if __ia64__
#  define xxfop(l, op, f, f0, f1, f2, f3, f4, f5)		\
	   xfop(_f, l, op, f0, f1, f2, f3, f4, f5)
#else
#  define xxfop(l, op, f, f0, f1, f2, f3, f4, f5)		\
	   xfop(_f, l, op, f0, f1, f2, f3, f4, f5)		\
	   xfop(_d, l, op, f0, f1, f2, f3, f4, f5)
#endif
#if __ia64__
#  define fop(l, op)						\
	xxfop(l, op, f, 0, 1, 2, 3, 4, 5)
#else
#  define fop(l, op)						\
	xxfop(l, op, f, 0, 1, 2, 3, 4, 5)			\
	xxfop(l, op, f, 1, 2, 3, 4, 5, 0)			\
	xxfop(l, op, f, 2, 3, 4, 5, 0, 1)			\
	xxfop(l, op, f, 3, 4, 5, 0, 1, 2)			\
	xxfop(l, op, f, 4, 5, 0, 1, 2, 3)			\
	xxfop(l, op, f, 5, 0, 1, 2, 3, 4)
#endif

#define aluxii(l, op, i0, i1, i2, i3, i4, i5)			\
	setup()							\
	jit_movi(_jit, IR##i0, 1);				\
	jit_##op##ci(_jit, IR##i1, IR##i0, 1);			\
	jit_##op##xi(_jit, IR##i2, IR##i0, 1);			\
	check3(ii, l, i3, i4, i5)

#define aluxir(l, op, i0, i1, i2, i3, i4, i5)			\
	setup()							\
	jit_movi(_jit, IR##i0, 1);				\
	jit_##op##ci(_jit, IR##i1, IR##i0, 1);			\
	jit_##op##xr(_jit, IR##i2, IR##i0, IR##i1);		\
	check3(ir, l, i3, i4, i5)

#define aluxri(l, op, i0, i1, i2, i3, i4, i5)			\
	setup()							\
	jit_movi(_jit, IR##i0, 1);				\
	jit_movi(_jit, IR##i1, 1);				\
	jit_##op##cr(_jit, IR##i2, IR##i0, IR##i1);		\
	jit_##op##xi(_jit, IR##i0, IR##i1, 1);			\
	check3(ri, l, i3, i4, i5)

#define aluxrr(l, op, i0, i1, i2, i3, i4, i5)			\
	setup()							\
	jit_movi(_jit, IR##i0, 1);				\
	jit_movi(_jit, IR##i1, 1);				\
	jit_##op##cr(_jit, IR##i2, IR##i0, IR##i1);		\
	jit_##op##xr(_jit, IR##i2, IR##i0, IR##i1);		\
	check3(rr, l, i3, i4, i5)

#define  xalux(l, op, i0, i1, i2, i3, i4, i5)			\
	aluxii(l, op, i0, i1, i2,	i3, i4, i5)		\
	aluxir(l, op, i0, i1, i2,	i3, i4, i5)		\
	aluxri(l, op, i0, i1, i2,	i3, i4, i5)		\
	aluxrr(l, op, i0, i1, i2,	i3, i4, i5)
#if __ia64__
#  define alux(l, op)						\
	 xalux(l, op, 0, 1, 2, 3, 4, 5)
#else
#  define alux(l, op)						\
	 xalux(l, op, 0, 1, 2, 3, 4, 5)				\
	 xalux(l, op, 1, 2, 3, 4, 5, 0)				\
	 xalux(l, op, 2, 3, 4, 5, 0, 1)				\
	 xalux(l, op, 3, 4, 5, 0, 1, 2)				\
	 xalux(l, op, 4, 5, 0, 1, 2, 3)				\
	 xalux(l, op, 5, 0, 1, 2, 3, 4)
#endif

#define alui_u(l, op, i0, i1, i2, i3, i4, i5)			\
	setup()							\
	jit_movi(_jit, IR##i0, 1);				\
	jit_##op##i_u(_jit, IR##i1, IR##i0, 1);			\
	check4(i_u, l, i2, i3, i4, i5)

#define aluic_u(l, op, i0, i1, i2, i3, i4, i5)			\
	setup()							\
	jit_movi(_jit, IR##i0, 1);				\
	jit_##op##i_u(_jit, IR##i0, IR##i0, 1);			\
	check5(ic_u, l, i1, i2, i3, i4, i5)

#define alur_u(l, op, i0, i1, i2, i3, i4, i5)			\
	setup()							\
	jit_movi(_jit, IR##i0, 1);				\
	jit_movi(_jit, IR##i1, 1);				\
	jit_##op##r_u(_jit, IR##i2, IR##i0, IR##i1);		\
	check3(r_u, l, i3, i4, i5)

#define alurc0_u(l, op, i0, i1, i2, i3, i4, i5)			\
	setup()							\
	jit_movi(_jit, IR##i0, 1);				\
	jit_movi(_jit, IR##i1, 1);				\
	jit_##op##r_u(_jit, IR##i0, IR##i0, IR##i1);		\
	check4(r0_u, l, i2, i3, i4, i5)

#define alurc1_u(l, op, i0, i1, i2, i3, i4, i5)			\
	setup()							\
	jit_movi(_jit, IR##i0, 1);				\
	jit_movi(_jit, IR##i1, 1);				\
	jit_##op##r_u(_jit, IR##i1, IR##i0, IR##i1);		\
	check4(r1_u, l, i2, i3, i4, i5)

#define alurc2_u(l, op, i0, i1, i2, i3, i4, i5)			\
	setup()							\
	jit_movi(_jit, IR##i0, 1);				\
	jit_##op##r_u(_jit, IR##i0, IR##i0, IR##i0);		\
	check5(r2_u, l, i1, i2, i3, i4, i5)

#define   xalu_u(l, op, i0, i1, i2, i3, i4, i5)			\
	  alui_u(l, op, i0, i1,	i2, i3, i4, i5)			\
	 aluic_u(l, op, i0,		i1, i2, i3, i4, i5)	\
	  alur_u(l, op, i0, i1, i2,	i3, i4, i5)		\
	alurc0_u(l, op, i0, i1,	i2, i3, i4, i5)			\
	alurc1_u(l, op, i0, i1,	i2, i3, i4, i5)			\
	alurc2_u(l, op, i0,		i1, i2, i3, i4, i5)
#if __ia64__
#  define alu_u(l, op)						\
	 xalu_u(l, op, 0, 1, 2, 3, 4, 5)
#else
#  define alu_u(l, op)						\
	 xalu_u(l, op, 0, 1, 2, 3, 4, 5)			\
	 xalu_u(l, op, 1, 2, 3, 4, 5, 0)			\
	 xalu_u(l, op, 2, 3, 4, 5, 0, 1)			\
	 xalu_u(l, op, 3, 4, 5, 0, 1, 2)			\
	 xalu_u(l, op, 4, 5, 0, 1, 2, 3)			\
	 xalu_u(l, op, 5, 0, 1, 2, 3, 4)
#endif

#define unir(l, op, i0, i1, i2, i3, i4, i5)			\
	setup()							\
	jit_movi(_jit, IR##i0, 1);				\
	jit_##op(_jit, IR##i1, IR##i0);				\
	check4(rr, l, i2, i3, i4, i5)

#define unirc(l, op, i0, i1, i2, i3, i4, i5)			\
	setup()							\
	jit_movi(_jit, IR##i0, 1);				\
	jit_##op(_jit, IR##i0, IR##i0);				\
	check5(rc, l, i1, i2, i3, i4, i5)

#define   xuni(l, op, i0, i1, i2, i3, i4, i5)			\
	  unir(l, op, i0, i1,	i2, i3, i4, i5)			\
	 unirc(l, op, i0,		i1, i2, i3, i4, i5)
#if __ia64__
#  define uni(l, op)						\
	 xuni(l, op, 0, 1, 2, 3, 4, 5)
#else
#  define uni(l, op)						\
	 xuni(l, op, 0, 1, 2, 3, 4, 5)				\
	 xuni(l, op, 1, 2, 3, 4, 5, 0)				\
	 xuni(l, op, 2, 3, 4, 5, 0, 1)				\
	 xuni(l, op, 3, 4, 5, 0, 1, 2)				\
	 xuni(l, op, 4, 5, 0, 1, 2, 3)				\
	 xuni(l, op, 5, 0, 1, 2, 3, 4)
#endif

#define unfr(f, l, op, f0, f1, f2, f3, f4, f5)			\
	setup##f()						\
	jit_movi##f(_jit, FR##f0, 1);				\
	jit_##op##f(_jit, FR##f1, FR##f0);			\
	checkf4(f, rr, l, f2, f3, f4, f5)

#define unfrc(f, l, op, f0, f1, f2, f3, f4, f5)			\
	setup##f()						\
	jit_movi##f(_jit, FR##f0, 1);				\
	jit_##op##f(_jit, FR##f0, FR##f0);			\
	checkf5(f, rc, l, f1, f2, f3, f4, f5)

#define   xunf(f, l, op, f0, f1, f2, f3, f4, f5)		\
	  unfr(f, l, op, f0, f1,	f2, f3, f4, f5)		\
	 unfrc(f, l, op, f0,		f1, f2, f3, f4, f5)
#define xxunf(l, op, f0, f1, f2, f3, f4, f5)			\
	 xunf(_f, l, op, f0, f1, f2, f3, f4, f5)		\
	 xunf(_d, l, op, f0, f1, f2, f3, f4, f5)
#if __ia64__
#  define unf(l, op)						\
	xxunf(l, op, 0, 1, 2, 3, 4, 5)
#else
#  define unf(l, op)						\
	xxunf(l, op, 0, 1, 2, 3, 4, 5)				\
	xxunf(l, op, 1, 2, 3, 4, 5, 0)				\
	xxunf(l, op, 2, 3, 4, 5, 0, 1)				\
	xxunf(l, op, 3, 4, 5, 0, 1, 2)				\
	xxunf(l, op, 4, 5, 0, 1, 2, 3)				\
	xxunf(l, op, 5, 0, 1, 2, 3, 4)
#endif

#define fcpi(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	setup()							\
	setup##f()						\
	jit_movi##f(_jit, FR##f0, 1.0);				\
	jit_movi##f(_jit, JIT_F6, 1.0);				\
	jit_##op##r##f(_jit, IR##r0, FR##f0, JIT_F6);		\
	check5(i##f##f0, l, r1, r2, r3, r4, r5)			\
	checkf5(f, i##r0, l, f1, f2, f3, f4, f5)

#define fcpr(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	setup()							\
	setup##f()						\
	jit_movi##f(_jit, FR##f0, 1.0);				\
	jit_movi##f(_jit, FR##f1, 1.0);				\
	jit_##op##r##f(_jit, IR##r0, FR##f0, FR##f1);		\
	check5(r##f##f0, l, r1, r2, r3, r4, r5)			\
	checkf4(f, r##r0, l, f2, f3, f4, f5)

#define fcprc(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	setup()							\
	setup##f()						\
	jit_movi##f(_jit, FR##f0, 1.0);				\
	jit_##op##r##f(_jit, IR##r0, FR##f0, FR##f0);		\
	check5(rc##f##f0, l, r1, r2, r3, r4, r5)		\
	checkf5(f, rc##r0, l, f1, f2, f3, f4, f5)

#if __ia64__
#  define ifcp(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  fcpi(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)
#else
#  define ifcp(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  fcpi(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  fcpr(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	 fcprc(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  fcpi(f, l, op, r1,r2,r3,r4,r5,r0, f0,f1,f2,f3,f4,f5)	\
	  fcpr(f, l, op, r1,r2,r3,r4,r5,r0, f0,f1,f2,f3,f4,f5)	\
	 fcprc(f, l, op, r1,r2,r3,r4,r5,r0, f0,f1,f2,f3,f4,f5)	\
	  fcpi(f, l, op, r2,r3,r4,r5,r0,r1, f0,f1,f2,f3,f4,f5)	\
	  fcpr(f, l, op, r2,r3,r4,r5,r0,r1, f0,f1,f2,f3,f4,f5)	\
	 fcprc(f, l, op, r2,r3,r4,r5,r0,r1, f0,f1,f2,f3,f4,f5)	\
	  fcpi(f, l, op, r3,r4,r5,r0,r1,r2, f0,f1,f2,f3,f4,f5)	\
	  fcpr(f, l, op, r3,r4,r5,r0,r1,r2, f0,f1,f2,f3,f4,f5)	\
	 fcprc(f, l, op, r3,r4,r5,r0,r1,r2, f0,f1,f2,f3,f4,f5)	\
	  fcpi(f, l, op, r4,r5,r0,r1,r2,r3, f0,f1,f2,f3,f4,f5)	\
	  fcpr(f, l, op, r4,r5,r0,r1,r2,r3, f0,f1,f2,f3,f4,f5)	\
	 fcprc(f, l, op, r4,r5,r0,r1,r2,r3, f0,f1,f2,f3,f4,f5)	\
	  fcpi(f, l, op, r5,r0,r1,r2,r3,r4, f0,f1,f2,f3,f4,f5)	\
	  fcpr(f, l, op, r5,r0,r1,r2,r3,r4, f0,f1,f2,f3,f4,f5)	\
	 fcprc(f, l, op, r5,r0,r1,r2,r3,r4, f0,f1,f2,f3,f4,f5)
#endif
#if __ia64__
#  define xfcp(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  ifcp(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)
#else
#  define xfcp(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  ifcp(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  ifcp(f, l, op, r0,r1,r2,r3,r4,r5, f1,f2,f3,f4,f5,f0)	\
	  ifcp(f, l, op, r0,r1,r2,r3,r4,r5, f2,f3,f4,f5,f0,f1)	\
	  ifcp(f, l, op, r0,r1,r2,r3,r4,r5, f3,f4,f5,f0,f1,f2)	\
	  ifcp(f, l, op, r0,r1,r2,r3,r4,r5, f4,f5,f0,f1,f2,f3)	\
	  ifcp(f, l, op, r0,r1,r2,r3,r4,r5, f5,f0,f1,f2,f3,f4)
#endif
#if __ia64__
#  define fcmp(l, op)						\
	  xfcp(_f, l, op, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5)
#else
#  define fcmp(l, op)						\
	  xfcp(_f, l, op, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5)	\
	  xfcp(_d, l, op, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5)
#endif

#define imvi(l, i0, i1, i2, i3, i4, i5)				\
	setup()							\
	jit_movi(_jit, IR##i0, 1);					\
	check5(i, l, i1, i2, i3, i4, i5)

#define imvr(l, i0, i1, i2, i3, i4, i5)				\
	setup()							\
	jit_movi(_jit, IR##i1, 1);				\
	jit_movr(_jit, IR##i0, IR##i1);				\
	check4(r, l, i2, i3, i4, i5)

#define xmvi(l, i0, i1, i2, i3, i4, i5)				\
	imvi(l, i0,	i1, i2, i3, i4, i5)			\
	imvr(l, i0, i1,	i2, i3, i4, i5)
#if __ia64__
#  define mvi(l)						\
	 xmvi(l, 0, 1, 2, 3, 4, 5)
#else
#  define mvi(l)						\
	 xmvi(l, 0, 1, 2, 3, 4, 5)				\
	 xmvi(l, 1, 2, 3, 4, 5, 0)				\
	 xmvi(l, 2, 3, 4, 5, 0, 1)				\
	 xmvi(l, 3, 4, 5, 0, 1, 2)				\
	 xmvi(l, 4, 5, 0, 1, 2, 3)				\
	 xmvi(l, 5, 0, 1, 2, 3, 4)
#endif

#define fmvi(f, l, f0, f1, f2, f3, f4, f5)			\
	setup##f()						\
	jit_movi##f(_jit, FR##f0, 1);				\
	checkf5(f, i, l, f1, f2, f3, f4, f5)

#define fmvr(f, l, f0, f1, f2, f3, f4, f5)			\
	setup##f()						\
	jit_movi##f(_jit, FR##f1, 1);				\
	jit_movr##f(_jit, FR##f0, FR##f1);			\
	checkf4(f, r, l, f2, f3, f4, f5)

#define xmvf(f, l, f0, f1, f2, f3, f4, f5)			\
	fmvi(f, l, f0, f1, f2, f3, f4, f5)			\
	fmvr(f, l, f0, f1,	f2, f3, f4, f5)
#if __ia64__
#  define xxmvf(f, l)						\
	  xmvf(f, l, 0, 1, 2, 3, 4, 5)
#else
#  define xxmvf(f, l)						\
	   xmvf(f, l, 0, 1, 2, 3, 4, 5)				\
	   xmvf(f, l, 1, 2, 3, 4, 5, 0)				\
	   xmvf(f, l, 2, 3, 4, 5, 0, 1)				\
	   xmvf(f, l, 3, 4, 5, 0, 1, 2)				\
	   xmvf(f, l, 4, 5, 0, 1, 2, 3)				\
	   xmvf(f, l, 5, 0, 1, 2, 3, 4)
#endif
#define   mvf(l)						\
	xxmvf(_f, l)						\
	xxmvf(_d, l)

#define f2fr(f, l, op, f0, f1, f2, f3, f4, f5)			\
	setup##f()						\
	jit_movi##f(_jit, FR##f0, 1);				\
	jit_##op(_jit, FR##f1, FR##f0);				\
	checkf4(f, rr, l, f2, f3, f4, f5)

#define f2frc(f, l, op, f0, f1, f2, f3, f4, f5)			\
	setup##f()						\
	jit_movi##f(_jit, FR##f0, 1);				\
	jit_##op(_jit, FR##f0, FR##f0);				\
	checkf5(f, rc, l, f1, f2, f3, f4, f5)

#define  xf2f(f, l, op, f0, f1, f2, f3, f4, f5)			\
	 f2fr(f, l, op, f0, f1,	f2, f3, f4, f5)			\
	f2frc(f, l, op, f0,		f1, f2, f3, f4, f5)
#if __ia64__
#  define f2f(l, f, op)						\
	 xf2f(f, l, op, 0, 1, 2, 3, 4, 5)
#else
#  define f2f(l, f, op)						\
	 xf2f(f, l, op, 0, 1, 2, 3, 4, 5)			\
	 xf2f(f, l, op, 1, 2, 3, 4, 5, 0)			\
	 xf2f(f, l, op, 2, 3, 4, 5, 0, 1)			\
	 xf2f(f, l, op, 3, 4, 5, 0, 1, 2)			\
	 xf2f(f, l, op, 4, 5, 0, 1, 2, 3)			\
	 xf2f(f, l, op, 5, 0, 1, 2, 3, 4)
#endif

#define f2ir(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	setup()							\
	setup##f()						\
	jit_movi##f(_jit, FR##f0, 1);				\
	jit_##op##f(_jit, IR##r0, FR##f0);			\
	check5(r##f##f0, l, r1, r2, r3, r4, r5)			\
	checkf5(f, i##r0, l, f1, f2, f3, f4, f5)

#if __ia64__
#  define if2i(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  f2ir(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)
#  define xf2i(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  if2i(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)
#else
#  define if2i(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  f2ir(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  f2ir(f, l, op, r1,r2,r3,r4,r5,r0, f0,f1,f2,f3,f4,f5)	\
	  f2ir(f, l, op, r2,r3,r4,r5,r0,r1, f0,f1,f2,f3,f4,f5)	\
	  f2ir(f, l, op, r3,r4,r5,r0,r1,r2, f0,f1,f2,f3,f4,f5)	\
	  f2ir(f, l, op, r4,r5,r0,r1,r2,r3, f0,f1,f2,f3,f4,f5)	\
	  f2ir(f, l, op, r5,r0,r1,r2,r3,r4, f0,f1,f2,f3,f4,f5)
#  define xf2i(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  if2i(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  if2i(f, l, op, r0,r1,r2,r3,r4,r5, f1,f2,f3,f4,f5,f0)	\
	  if2i(f, l, op, r0,r1,r2,r3,r4,r5, f2,f3,f4,f5,f0,f1)	\
	  if2i(f, l, op, r0,r1,r2,r3,r4,r5, f3,f4,f5,f0,f1,f2)	\
	  if2i(f, l, op, r0,r1,r2,r3,r4,r5, f4,f5,f0,f1,f2,f3)	\
	  if2i(f, l, op, r0,r1,r2,r3,r4,r5, f5,f0,f1,f2,f3,f4)
#endif
#define f2i(l, op)						\
	xf2i(_f, l, op, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5)	\
	xf2i(_d, l, op, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5)

#define i2fr(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	setup()							\
	setup##f()						\
	jit_movi(_jit, IR##r0, 1);				\
	jit_##op##f(_jit, FR##f0, IR##r0);			\
	check5(r##f##f0, l, r1, r2, r3, r4, r5)			\
	checkf5(f, i##r0, l, f1, f2, f3, f4, f5)
#if __ia64__
#  define ii2f(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  i2fr(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)
#  define xi2f(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  ii2f(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)
#else
#  define ii2f(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  i2fr(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  i2fr(f, l, op, r1,r2,r3,r4,r5,r0, f0,f1,f2,f3,f4,f5)	\
	  i2fr(f, l, op, r2,r3,r4,r5,r0,r1, f0,f1,f2,f3,f4,f5)	\
	  i2fr(f, l, op, r3,r4,r5,r0,r1,r2, f0,f1,f2,f3,f4,f5)	\
	  i2fr(f, l, op, r4,r5,r0,r1,r2,r3, f0,f1,f2,f3,f4,f5)	\
	  i2fr(f, l, op, r5,r0,r1,r2,r3,r4, f0,f1,f2,f3,f4,f5)
#  define xi2f(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  ii2f(f, l, op, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  ii2f(f, l, op, r0,r1,r2,r3,r4,r5, f1,f2,f3,f4,f5,f0)	\
	  ii2f(f, l, op, r0,r1,r2,r3,r4,r5, f2,f3,f4,f5,f0,f1)	\
	  ii2f(f, l, op, r0,r1,r2,r3,r4,r5, f3,f4,f5,f0,f1,f2)	\
	  ii2f(f, l, op, r0,r1,r2,r3,r4,r5, f4,f5,f0,f1,f2,f3)	\
	  ii2f(f, l, op, r0,r1,r2,r3,r4,r5, f5,f0,f1,f2,f3,f4)
#endif
#define i2f(l, op)						\
	xi2f(_f, l, op, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5)	\
	xi2f(_d, l, op, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5)

#define off_c		1
#define off_uc		off_c
#define off_s		2
#define off_us		off_s
#define off_i		4
#define off_ui		off_i
#define off_l		8
#define off_f		4
#define off_d		8

#define ildi(i, l, r0, r1, r2, r3, r4, r5)			\
	setup()							\
	jit_##ldi##i(_jit, IR##r0, buff);			\
	check5(ldi##i, l, r1, r2, r3, r4, r5)

#define ildr(i, l, r0, r1, r2, r3, r4, r5)			\
	setup()							\
	jit_movi(_jit, IR##r1, (jit_imm_t)buff);		\
	jit_##ldr##i(_jit, IR##r0, IR##r1);			\
	check4(ldr##i, l, r2, r3, r4, r5)

#define ildr0(i, l, r0, r1, r2, r3, r4, r5)			\
	setup()							\
	jit_movi(_jit, IR##r0, (jit_imm_t)buff);		\
	jit_##ldr##i(_jit, IR##r0, IR##r0);			\
	check5(ldr##i, l, r1, r2, r3, r4, r5)

#define ildxi(i, l, r0, r1, r2, r3, r4, r5)			\
	setup()							\
	jit_movi(_jit, IR##r1, (jit_imm_t)buff);		\
	jit_ldxi##i(_jit, IR##r0, IR##r1, off##i); 		\
	check4(ldxi##i, l, r2, r3, r4, r5)

#define ildxr(i, l, r0, r1, r2, r3, r4, r5)			\
	setup()							\
	jit_movi(_jit, IR##r1, (jit_imm_t)buff);		\
	jit_movi(_jit, IR##r2, off##i);				\
	jit_ldxr##i(_jit, IR##r0, IR##r1, IR##r2);		\
	check3(ldxr##i, l, r3, r4, r5)

#define ildxr0(i, l, r0, r1, r2, r3, r4, r5)			\
	setup()							\
	jit_movi(_jit, IR##r1, (jit_imm_t)buff);		\
	jit_movi(_jit, IR##r0, off##i);				\
	jit_ldxr##i(_jit, IR##r0, IR##r1, IR##r0);		\
	check4(ldxr0##i, l, r2, r3, r4, r5)

#define ildxr1(i, l, r0, r1, r2, r3, r4, r5)			\
	setup()							\
	jit_movi(_jit, IR##r0, (jit_imm_t)buff);		\
	jit_movi(_jit, IR##r1, off##i);				\
	jit_ldxr##i(_jit, IR##r0, IR##r0, IR##r1);		\
	check4(ldxr1##i, l, r2, r3, r4, r5)

#define  xxldi(i, l, r0, r1, r2, r3, r4, r5)			\
	  ildi(i, l, r0, r1, r2, r3, r4, r5)			\
	  ildr(i, l, r0, r1, r2, r3, r4, r5)			\
	 ildr0(i, l, r0, r1, r2, r3, r4, r5)			\
	 ildxi(i, l, r0, r1, r2, r3, r4, r5)			\
	 ildxr(i, l, r0, r1, r2, r3, r4, r5)			\
	ildxr0(i, l, r0, r1, r2, r3, r4, r5)			\
	ildxr1(i, l, r0, r1, r2, r3, r4, r5)
#if __WORDSIZE == 32
#define xxxldi(l, r0, r1, r2, r3, r4, r5)
#else
#define xxxldi(l, r0, r1, r2, r3, r4, r5)			\
	 xxldi(_ui, l, r0, r1, r2, r3, r4, r5)			\
	 xxldi( _l, l, r0, r1, r2, r3, r4, r5)
#endif
#define   xldi(l, r0, r1, r2, r3, r4, r5)			\
	 xxldi( _c, l, r0, r1, r2, r3, r4, r5)			\
	 xxldi(_uc, l, r0, r1, r2, r3, r4, r5)			\
	 xxldi( _s, l, r0, r1, r2, r3, r4, r5)			\
	 xxldi(_us, l, r0, r1, r2, r3, r4, r5)			\
	 xxldi( _i, l, r0, r1, r2, r3, r4, r5)			\
	xxxldi(l, r0, r1, r2, r3, r4, r5)
#if __ia64__
#  define ldi(l)						\
	 xldi(l, 0, 1, 2, 3, 4, 5)
#else
#  define ldi(l)						\
	 xldi(l, 0, 1, 2, 3, 4, 5)				\
	 xldi(l, 1, 2, 3, 4, 5, 0)				\
	 xldi(l, 2, 3, 4, 5, 0, 1)				\
	 xldi(l, 3, 4, 5, 0, 1, 2)				\
	 xldi(l, 4, 5, 0, 1, 2, 3)				\
	 xldi(l, 5, 0, 1, 2, 3, 4)
#endif

#define fldi(f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	setup()							\
	setup##f()						\
	jit_ldi##f(_jit, FR##f0, buff);				\
	check6(ldi##f##r0##f0, l, r0, r1, r2, r3, r4, r5)	\
	checkf5(f, ldi##r0##f0, l, f1, f2, f3, f4, f5)

#define fldr(f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	setup()							\
	setup##f()						\
	jit_movi(_jit, IR##r0, (jit_imm_t)buff);		\
	jit_ldr##f(_jit, FR##f0, IR##r0);			\
	check5(ldr##f##r0##f0, l, r1, r2, r3, r4, r5)		\
	checkf5(f, ldr##r0##f0, l, f1, f2, f3, f4, f5)

#define fldxi(f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	setup()							\
	setup##f()						\
	jit_movi(_jit, IR##r0, (jit_imm_t)buff);		\
	jit_ldxi##f(_jit, FR##f0, IR##r0, off##f); 		\
	check5(ldxi##f##r0##f0, l, r1, r2, r3, r4, r5)		\
	checkf5(f, ldxi##r0##f0, l, f1, f2, f3, f4, f5)

#define fldxr(f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	setup()							\
	setup##f()						\
	jit_movi(_jit, IR##r0, (jit_imm_t)buff);		\
	jit_movi(_jit, IR##r1, off##f);				\
	jit_ldxr##f(_jit, FR##f0, IR##r0, IR##r1); 		\
	check4(ldxr##f##r0##f0, l, r2, r3, r4, r5)		\
	checkf5(f, ldxr##r0##f0, l, f1, f2, f3, f4, f5)

#define	  xldf(f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	fldi(f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	fldr(f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	fldxi(f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	fldxr(f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)

#define	 xxldf(l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)		\
	  xldf(_f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  xldf(_d, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)
#if __ia64__
#  define ixldf(l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  xxldf(l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)
#else
#  define fxldf(l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  xxldf(l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  xxldf(l, r0,r1,r2,r3,r4,r5, f1,f2,f3,f4,f5,f0)	\
	  xxldf(l, r0,r1,r2,r3,r4,r5, f2,f3,f4,f5,f0,f1)	\
	  xxldf(l, r0,r1,r2,r3,r4,r5, f3,f4,f5,f0,f1,f2)	\
	  xxldf(l, r0,r1,r2,r3,r4,r5, f4,f5,f0,f1,f2,f3)	\
	  xxldf(l, r0,r1,r2,r3,r4,r5, f5,f0,f1,f2,f3,f4)
#  define ixldf(l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  fxldf(l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  fxldf(l, r1,r2,r3,r4,r5,r0, f0,f1,f2,f3,f4,f5)	\
	  fxldf(l, r2,r3,r4,r5,r0,r1, f0,f1,f2,f3,f4,f5)	\
	  fxldf(l, r3,r4,r5,r0,r1,r2, f0,f1,f2,f3,f4,f5)	\
	  fxldf(l, r4,r5,r0,r1,r2,r3, f0,f1,f2,f3,f4,f5)	\
	  fxldf(l, r5,r0,r1,r2,r3,r4, f0,f1,f2,f3,f4,f5)
#endif
#define   ldf(l)						\
	ixldf(l, 0,1,2,3,4,5, 0,1,2,3,4,5)

#define isti(i, l, r0, r1, r2, r3, r4, r5)			\
	setup()							\
	jit_sti##i(_jit, buff, IR##r0);				\
	check5(sti##i, l, r1, r2, r3, r4, r5)

#define istr(i, l, r0, r1, r2, r3, r4, r5)			\
	setup()							\
	jit_movi(_jit, IR##r1, (jit_imm_t)buff);		\
	jit_str##i(_jit, IR##r1, IR##r0);			\
	check4(str##i, l, r2, r3, r4, r5)

#define istr0(i, l, r0, r1, r2, r3, r4, r5)			\
	setup()							\
	jit_movi(_jit, IR##r1, (jit_imm_t)buff);		\
	jit_str##i(_jit, IR##r1, IR##r0);			\
	check4(str0##i, l, r2, r3, r4, r5)

#define istxi(i, l, r0, r1, r2, r3, r4, r5)			\
	setup()							\
	jit_movi(_jit, IR##r1, (jit_imm_t)buff);		\
	jit_stxi##i(_jit, off##i, IR##r1, IR##r0); 		\
	check4(stxi##i, l, r2, r3, r4, r5)

#define istxr(i, l, r0, r1, r2, r3, r4, r5)			\
	setup()							\
	jit_movi(_jit, IR##r1, (jit_imm_t)buff);		\
	jit_movi(_jit, IR##r2, off##i);				\
	jit_stxr##i(_jit, IR##r2, IR##r1, IR##r0);		\
	check3(stxr##i, l, r3, r4, r5)

#define istxr0(i, l, r0, r1, r2, r3, r4, r5)			\
	setup()							\
	jit_movi(_jit, IR##r1, (jit_imm_t)buff);		\
	jit_movi(_jit, IR##r0, off##i);				\
	jit_stxr##i(_jit, IR##r0, IR##r1, IR##r0);		\
	check4(stxr0##i, l, r2, r3, r4, r5)

#define istxr1(i, l, r0, r1, r2, r3, r4, r5)			\
	setup()							\
	jit_movi(_jit, IR##r0, (jit_imm_t)buff);		\
	jit_movi(_jit, IR##r1, off##i);				\
	jit_stxr##i(_jit, IR##r1, IR##r0, IR##r0);		\
	check4(stxr1##i, l, r2, r3, r4, r5)

#define  xxsti(i, l, r0, r1, r2, r3, r4, r5)			\
	  isti(i, l, r0, r1, r2, r3, r4, r5)			\
	  istr(i, l, r0, r1, r2, r3, r4, r5)			\
	 istr0(i, l, r0, r1, r2, r3, r4, r5)			\
	 istxi(i, l, r0, r1, r2, r3, r4, r5)			\
	 istxr(i, l, r0, r1, r2, r3, r4, r5)			\
	istxr0(i, l, r0, r1, r2, r3, r4, r5)			\
	istxr1(i, l, r0, r1, r2, r3, r4, r5)
#if __WORDSIZE == 32
#define xxxsti(l, r0, r1, r2, r3, r4, r5)
#else
#define xxxsti(l, r0, r1, r2, r3, r4, r5)			\
	 xxsti( _l, l, r0, r1, r2, r3, r4, r5)
#endif
#define   xsti(l, r0, r1, r2, r3, r4, r5)			\
	 xxsti( _c, l, r0, r1, r2, r3, r4, r5)			\
	 xxsti( _s, l, r0, r1, r2, r3, r4, r5)			\
	 xxsti( _i, l, r0, r1, r2, r3, r4, r5)			\
	xxxsti(l, r0, r1, r2, r3, r4, r5)
#if __ia64__
#  define sti(l)						\
	 xsti(l, 0, 1, 2, 3, 4, 5)
#else
#  define sti(l)						\
	 xsti(l, 0, 1, 2, 3, 4, 5)				\
	 xsti(l, 1, 2, 3, 4, 5, 0)				\
	 xsti(l, 2, 3, 4, 5, 0, 1)				\
	 xsti(l, 3, 4, 5, 0, 1, 2)				\
	 xsti(l, 4, 5, 0, 1, 2, 3)				\
	 xsti(l, 5, 0, 1, 2, 3, 4)
#endif

#define fsti(f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	setup()							\
	setup##f()						\
	jit_sti##f(_jit, buff, FR##f0);				\
	check6(sti##f##r0##f0, l, r0, r1, r2, r3, r4, r5)	\
	checkf5(f, sti##r0##f0, l, f1, f2, f3, f4, f5)

#define fstr(f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	setup()							\
	setup##f()						\
	jit_movi(_jit, IR##r0, (jit_imm_t)buff);		\
	jit_str##f(_jit, IR##r0, FR##f0);			\
	check5(str##f##r0##f0, l, r1, r2, r3, r4, r5)		\
	checkf5(f, str##r0##f0, l, f1, f2, f3, f4, f5)

#define fstxi(f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	setup()							\
	setup##f()						\
	jit_movi(_jit, IR##r0, (jit_imm_t)buff);		\
	jit_stxi##f(_jit, off##f, IR##r0, FR##f0); 		\
	check5(stxi##f##r0##f0, l, r1, r2, r3, r4, r5)		\
	checkf5(f, stxi##r0##f0, l, f1, f2, f3, f4, f5)

#define fstxr(f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	setup()							\
	setup##f()						\
	jit_movi(_jit, IR##r0, (jit_imm_t)buff);		\
	jit_movi(_jit, IR##r1, off##f);				\
	jit_stxr##f(_jit, IR##r1, IR##r0, FR##f0); 		\
	check4(stxr##f##r0##f0, l, r2, r3, r4, r5)		\
	checkf5(f, stxr##r0##f0, l, f1, f2, f3, f4, f5)

#define	  xstf(f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	fsti(f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	fstr(f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	fstxi(f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	fstxr(f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)
#define	 xxstf(l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)		\
	  xstf(_f, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  xstf(_d, l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)
#if __ia64__
#  define ixstf(l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  xxstf(l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)
#else
#  define fxstf(l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  xxstf(l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  xxstf(l, r0,r1,r2,r3,r4,r5, f1,f2,f3,f4,f5,f0)	\
	  xxstf(l, r0,r1,r2,r3,r4,r5, f2,f3,f4,f5,f0,f1)	\
	  xxstf(l, r0,r1,r2,r3,r4,r5, f3,f4,f5,f0,f1,f2)	\
	  xxstf(l, r0,r1,r2,r3,r4,r5, f4,f5,f0,f1,f2,f3)	\
	  xxstf(l, r0,r1,r2,r3,r4,r5, f5,f0,f1,f2,f3,f4)
# define ixstf(l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)		\
	  fxstf(l, r0,r1,r2,r3,r4,r5, f0,f1,f2,f3,f4,f5)	\
	  fxstf(l, r1,r2,r3,r4,r5,r0, f0,f1,f2,f3,f4,f5)	\
	  fxstf(l, r2,r3,r4,r5,r0,r1, f0,f1,f2,f3,f4,f5)	\
	  fxstf(l, r3,r4,r5,r0,r1,r2, f0,f1,f2,f3,f4,f5)	\
	  fxstf(l, r4,r5,r0,r1,r2,r3, f0,f1,f2,f3,f4,f5)	\
	  fxstf(l, r5,r0,r1,r2,r3,r4, f0,f1,f2,f3,f4,f5)
#endif
#define   stf(l)						\
	ixstf(l, 0,1,2,3,4,5, 0,1,2,3,4,5)

#define bri(l, op, u, il, ir, r0, r1, r2, r3, r4, r5)		\
{								\
	setup()							\
	jit_movi(_jit, IR##r0, il); 				\
	jit_reloc_t r = jit_b##op##i##u(_jit, IR##r0, ir);	\
	jit_calli_0(_jit, abort);				\
	jit_patch_here(_jit, r);				\
	check5(i, l, r1, r2, r3, r4, r5)			\
}

#define brr(l, op, u, il, ir, r0, r1, r2, r3, r4, r5)		\
{								\
	setup()							\
	jit_movi(_jit, IR##r0, il);				\
	jit_movi(_jit, IR##r1, ir);				\
	jit_reloc_t r = jit_b##op##r##u(_jit, IR##r0, IR##r1);	\
	jit_calli_0(_jit, abort);				\
	jit_patch_here(_jit, r);				\
	check4(r, l, r2, r3, r4, r5)				\
}

#define  xjmpi(l, op, u, il, ir, r0, r1, r2, r3, r4, r5)	\
	   bri(l, op, u, il, ir, r0, r1, r2, r3, r4, r5)	\
	   brr(l, op, u, il, ir, r0, r1, r2, r3, r4, r5)
#if __ia64__
#  define jmpi(l, op, u, il, ir)				\
	 xjmpi(l, op, u, il, ir, 0, 1, 2, 3, 4, 5)
#else
#  define jmpi(l, op, u, il, ir)				\
	 xjmpi(l, op, u, il, ir, 0, 1, 2, 3, 4, 5)		\
	 xjmpi(l, op, u, il, ir, 1, 2, 3, 4, 5, 0)		\
	 xjmpi(l, op, u, il, ir, 2, 3, 4, 5, 0, 1)		\
	 xjmpi(l, op, u, il, ir, 3, 4, 5, 0, 1, 2)		\
	 xjmpi(l, op, u, il, ir, 4, 5, 0, 1, 2, 3)		\
	 xjmpi(l, op, u, il, ir, 5, 0, 1, 2, 3, 4)
#endif

#define bfi(f, l, op, il, ir, f0, f1, f2, f3, f4, f5)		\
{								\
	setup##f()						\
	jit_movi##f(_jit, FR##f0, il); 				\
	jit_movi##f(_jit, JIT_F6, ir);				\
	jit_reloc_t r = jit_b##op##r##f(_jit, FR##f0, JIT_F6);	\
	jit_calli_0(_jit, abort);				\
	jit_patch_here(_jit, r);				\
	checkf5(f, i, l, f1, f2, f3, f4, f5)			\
}

#define bff(f, l, op, il, ir, f0, f1, f2, f3, f4, f5)		\
{								\
	setup##f()						\
	jit_movi##f(_jit, FR##f0, il);				\
	jit_movi##f(_jit, FR##f1, ir);				\
	jit_reloc_t r = jit_b##op##r##f(_jit, FR##f0, FR##f1);	\
	jit_calli_0(_jit, abort);				\
	jit_patch_here(_jit, r);				\
	checkf4(f, r, l, f2, f3, f4, f5)			\
}

#define  xjmpf(f, l, op, il, ir, f0, f1, f2, f3, f4, f5)	\
	   bfi(f, l, op, il, ir, f0, f1, f2, f3, f4, f5)	\
	   bff(f, l, op, il, ir, f0, f1, f2, f3, f4, f5)
#define xxjmpf(l, op, il, ir, f0, f1, f2, f3, f4, f5)		\
	 xjmpf(_f, l, op, il, ir, f0, f1, f2, f3, f4, f5)	\
	 xjmpf(_d, l, op, il, ir, f0, f1, f2, f3, f4, f5)
#if __ia64__
#  define jmpf(l, op, il, ir)					\
	xxjmpf(l, op, il, ir, 0, 1, 2, 3, 4, 5)
#else
#  define jmpf(l, op, il, ir)					\
	xxjmpf(l, op, il, ir, 0, 1, 2, 3, 4, 5)			\
	xxjmpf(l, op, il, ir, 1, 2, 3, 4, 5, 0)			\
	xxjmpf(l, op, il, ir, 2, 3, 4, 5, 0, 1)			\
	xxjmpf(l, op, il, ir, 3, 4, 5, 0, 1, 2)			\
	xxjmpf(l, op, il, ir, 4, 5, 0, 1, 2, 3)			\
	xxjmpf(l, op, il, ir, 5, 0, 1, 2, 3, 4)
#endif

static size_t
run_test(jit_state_t *_jit, uint8_t *arena_base, size_t arena_size)
{
	jit_begin(_jit, arena_base, arena_size);
	size_t frame = jit_enter_jit_abi(_jit, 0, 0, 0);

	void (*function)(void);

	char *buff = malloc(16);
	ASSERT(buff);

	  alu(__LINE__, add)
	 alux(__LINE__, add)
	  fop(__LINE__, add)
	  alu(__LINE__, sub)
	 alux(__LINE__, sub)
	  fop(__LINE__, sub)
	  alu(__LINE__, mul)
	  fop(__LINE__, mul)
	  alu(__LINE__, div)
	alu_u(__LINE__, div)
	  fop(__LINE__, div)
	  alu(__LINE__, rem)
	alu_u(__LINE__, rem)
	  alu(__LINE__, and)
	  alu(__LINE__, or)
	  alu(__LINE__, xor)
	  alu(__LINE__, lsh)
	  alu(__LINE__, rsh)
	alu_u(__LINE__, rsh)
	  uni(__LINE__, negr)
	  unf(__LINE__, negr)
	  uni(__LINE__, comr)
	  unf(__LINE__, absr)
	  unf(__LINE__, sqrtr)
	  mvi(__LINE__)
	  mvf(__LINE__)
	  uni(__LINE__, extr_c)
	  uni(__LINE__, extr_uc)
	  uni(__LINE__, extr_s)
	  uni(__LINE__, extr_us)
#if __WORDSIZE == 64
	  uni(__LINE__, extr_ui)
#endif
	  uni(__LINE__, bswapr_us)
	  uni(__LINE__, bswapr_ui)
#if __WORDSIZE == 64
	  uni(__LINE__, bswapr_ul)
#endif
	  f2f(__LINE__, _f, extr_d_f)
	  f2f(__LINE__, _d, extr_f_d)
	  f2i(__LINE__, truncr)
	  i2f(__LINE__, extr)
	  ldi(__LINE__)
	  ldf(__LINE__)
	  sti(__LINE__)
	  stf(__LINE__)
	 jmpi(__LINE__, lt,   ,  0,  1)
	 jmpi(__LINE__, lt, _u,  0,  1)
	 jmpf(__LINE__, lt,      0,  1)
	 jmpi(__LINE__, le,   ,  1,  1)
	 jmpi(__LINE__, le, _u,  1,  1)
	 jmpf(__LINE__, le,      1,  1)
	 jmpi(__LINE__, eq,   , -1, -1)
	 jmpf(__LINE__, eq,     -1, -1)
	 jmpi(__LINE__, ge,   ,  2,  2)
	 jmpi(__LINE__, ge, _u,  2,  2)
	 jmpf(__LINE__, ge,      2,  2)
	 jmpi(__LINE__, gt,   ,  2,  1)
	 jmpi(__LINE__, gt, _u,  2,  1)
	 jmpf(__LINE__, gt,      2,  1)
	 jmpi(__LINE__, ne,   ,  3,  2)
	 jmpf(__LINE__, ne,      3,  2)
	 jmpi(__LINE__, ms, , 1, 1)
	 jmpi(__LINE__, mc, , 1, 2)
#if __WORDSIZE == 32
#  define ix7f		0x7fffffff
#  define ix80		0x80000000
#  define ixff		0xffffffff
#else
#  define ix7f		0x7fffffffffffffff
#  define ix80		0x8000000000000000
#  define ixff		0xffffffffffffffff
#endif
	 jmpi(__LINE__, oadd,   , ix7f, 1)
	 jmpi(__LINE__, oadd, _u, ixff, 1)
	 jmpi(__LINE__, xadd,   , ix80, 1)
	 jmpi(__LINE__, xadd, _u, ix7f, 1)
	 jmpi(__LINE__, osub,   , ix80, 1)
	 jmpi(__LINE__, osub, _u,    0, 1)
	 jmpi(__LINE__, xsub,   , ix7f, 1)
	 jmpi(__LINE__, xsub, _u, ix80, 1)
	 jmpf(__LINE__, unlt,        0, 1)
	 jmpf(__LINE__, unle,        1, 1)
	 jmpf(__LINE__, uneq,        2, 2)
	 jmpf(__LINE__, unge,        3, 3)
	 jmpf(__LINE__, ungt,        4, 3)
	 jmpf(__LINE__, ltgt,        5, 4)
	 jmpf(__LINE__, ord,         0, 0)
	 jmpf(__LINE__, unord,       0, (0.0 / 0.0))

	jit_leave_jit_abi(_jit, 0, 0, frame);	
	jit_ret(_jit);

	size_t size = 0;
	function = jit_end(_jit, &size);

	if (function)
		(*function)();
	else {
		free(buff);
		return size;
	}

	free(buff);
	return 0;
}

int main(int argc, char *argv[])
{
	return main_compiler(argc, argv, run_test);
}
