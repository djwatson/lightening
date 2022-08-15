#include "test.h"

#if __WORDSIZE == 64
#  define I7f		0x7fffffffffffffff
#  define I80		0x8000000000000000
#  define I81		0x8000000000000001
#  define Iff		0xffffffffffffffff
#else
#  define I7f		0x7fffffff
#  define I80		0x80000000
#  define I81		0x80000001
#  define Iff		0xffffffff
#endif

#define NaN (0.0 / 0.0)

#if defined(DEBUG)
#define dump_args(comp, r0, r1)\
	jit_calli_1(_jit, puts,\
		jit_operand_imm(JIT_OPERAND_ABI_POINTER,\
			(jit_imm_t)#comp " " #r0 " " #r1));
#else
#define dump_args(comp, r0, r1)
#endif

#define BOP(N, Ls, Rs, Lu, Ru, R0, R1)			\
{							\
	dump_args(N##r, Ls, Rs);			\
	jit_movi(_jit, R0, Ls);				\
	jit_movi(_jit, R1, Rs);				\
	jit_reloc_t r = jit_b##N##r(_jit, R0, R1);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##i, Ls, Rs);			\
	jit_movi(_jit, R0, Ls);				\
	jit_reloc_t r = jit_b##N##i(_jit, R0, Rs);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##r_u, Lu, Ru);			\
	jit_movi(_jit, R0, Lu);				\
	jit_movi(_jit, R1, Ru);				\
	jit_reloc_t r = jit_b##N##r_u(_jit, R0, R1);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##i_u, Lu, Ru);			\
	jit_movi(_jit, R0, Lu);				\
	jit_reloc_t r = jit_b##N##i_u(_jit, R0, Ru);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}

#define EB(N, L, R, R0, R1)				\
{							\
	dump_args(N##r, L, R);				\
	jit_movi(_jit, R0, L);				\
	jit_movi(_jit, R1, R);				\
	jit_reloc_t r = jit_b##N##r(_jit, R0, R1);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##i, L, R);				\
	jit_movi(_jit, R0, L);				\
	jit_reloc_t r = jit_b##N##i(_jit, R0, R);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\

#define XEB(N, L, R, R0, R1)				\
{							\
	dump_args(N##r, L, R);				\
	jit_movi(_jit, R0, L);				\
	jit_movi(_jit, R1, R);				\
	jit_reloc_t r = jit_b##N##r(_jit, R0, R1);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##i, L, R);				\
	jit_movi(_jit, R0, L);				\
	jit_reloc_t r = jit_b##N##i(_jit, R0, R);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}

#define XBOP(N, Ls, Rs, Lu, Ru, R0, R1)			\
{							\
	dump_args(N##r, Ls, Rs);			\
	jit_movi(_jit, R0, Ls);				\
	jit_movi(_jit, R1, Rs);				\
	jit_reloc_t r = jit_b##N##r(_jit, R0, R1);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##i, Ls, Rs);			\
	jit_movi(_jit, R0, Ls);				\
	jit_reloc_t r = jit_b##N##i(_jit, R0, Rs);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##r_u, Lu, Ru);			\
	jit_movi(_jit, R0, Lu);				\
	jit_movi(_jit, R1, Ru);				\
	jit_reloc_t r = jit_b##N##r_u(_jit, R0, R1);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##i_u, Lu, Ru);			\
	jit_movi(_jit, R0, Lu);				\
	jit_reloc_t r = jit_b##N##i_u(_jit, R0, Ru);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}

#define BOPI(N, Ls, Rs, Lu, Ru)				\
	BOP(N, Ls, Rs, Lu, Ru, JIT_V0, JIT_V1)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_V0, JIT_V2)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_V0, JIT_R0)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_V0, JIT_R1)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_V0, JIT_R2)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_V1, JIT_V0)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_V1, JIT_V2)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_V1, JIT_R0)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_V1, JIT_R1)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_V1, JIT_R2)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_V2, JIT_V0)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_V2, JIT_V1)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_V2, JIT_R0)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_V2, JIT_R1)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_V2, JIT_R2)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_R0, JIT_V0)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_R0, JIT_V1)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_R0, JIT_V2)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_R0, JIT_R1)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_R0, JIT_R2)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_R1, JIT_V0)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_R1, JIT_V1)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_R1, JIT_V2)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_R1, JIT_R0)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_R1, JIT_R2)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_R2, JIT_V0)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_R2, JIT_V1)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_R2, JIT_V2)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_R2, JIT_R0)		\
	BOP(N, Ls, Rs, Lu, Ru, JIT_R2, JIT_R1)

#define EBI(N, L, R)					\
	EB(N, L, R, JIT_V0, JIT_V1)			\
	EB(N, L, R, JIT_V0, JIT_V2)			\
	EB(N, L, R, JIT_V0, JIT_R0)			\
	EB(N, L, R, JIT_V0, JIT_R1)			\
	EB(N, L, R, JIT_V0, JIT_R2)			\
	EB(N, L, R, JIT_V1, JIT_V0)			\
	EB(N, L, R, JIT_V1, JIT_V2)			\
	EB(N, L, R, JIT_V1, JIT_R0)			\
	EB(N, L, R, JIT_V1, JIT_R1)			\
	EB(N, L, R, JIT_V1, JIT_R2)			\
	EB(N, L, R, JIT_V2, JIT_V0)			\
	EB(N, L, R, JIT_V2, JIT_V1)			\
	EB(N, L, R, JIT_V2, JIT_R0)			\
	EB(N, L, R, JIT_V2, JIT_R1)			\
	EB(N, L, R, JIT_V2, JIT_R2)			\
	EB(N, L, R, JIT_R0, JIT_V0)			\
	EB(N, L, R, JIT_R0, JIT_V1)			\
	EB(N, L, R, JIT_R0, JIT_V2)			\
	EB(N, L, R, JIT_R0, JIT_R1)			\
	EB(N, L, R, JIT_R0, JIT_R2)			\
	EB(N, L, R, JIT_R1, JIT_V0)			\
	EB(N, L, R, JIT_R1, JIT_V1)			\
	EB(N, L, R, JIT_R1, JIT_V2)			\
	EB(N, L, R, JIT_R1, JIT_R0)			\
	EB(N, L, R, JIT_R1, JIT_R2)			\
	EB(N, L, R, JIT_R2, JIT_V0)			\
	EB(N, L, R, JIT_R2, JIT_V1)			\
	EB(N, L, R, JIT_R2, JIT_V2)			\
	EB(N, L, R, JIT_R2, JIT_R0)			\
	EB(N, L, R, JIT_R2, JIT_R1)


#define XEBI(N, L, R)					\
	XEB(N, L, R, JIT_V0, JIT_V1)			\
	XEB(N, L, R, JIT_V0, JIT_V2)			\
	XEB(N, L, R, JIT_V0, JIT_R0)			\
	XEB(N, L, R, JIT_V0, JIT_R1)			\
	XEB(N, L, R, JIT_V0, JIT_R2)			\
	XEB(N, L, R, JIT_V1, JIT_V0)			\
	XEB(N, L, R, JIT_V1, JIT_V2)			\
	XEB(N, L, R, JIT_V1, JIT_R0)			\
	XEB(N, L, R, JIT_V1, JIT_R1)			\
	XEB(N, L, R, JIT_V1, JIT_R2)			\
	XEB(N, L, R, JIT_V2, JIT_V0)			\
	XEB(N, L, R, JIT_V2, JIT_V1)			\
	XEB(N, L, R, JIT_V2, JIT_R0)			\
	XEB(N, L, R, JIT_V2, JIT_R1)			\
	XEB(N, L, R, JIT_V2, JIT_R2)			\
	XEB(N, L, R, JIT_R0, JIT_V0)			\
	XEB(N, L, R, JIT_R0, JIT_V1)			\
	XEB(N, L, R, JIT_R0, JIT_V2)			\
	XEB(N, L, R, JIT_R0, JIT_R1)			\
	XEB(N, L, R, JIT_R0, JIT_R2)			\
	XEB(N, L, R, JIT_R1, JIT_V0)			\
	XEB(N, L, R, JIT_R1, JIT_V1)			\
	XEB(N, L, R, JIT_R1, JIT_V2)			\
	XEB(N, L, R, JIT_R1, JIT_R0)			\
	XEB(N, L, R, JIT_R1, JIT_R2)			\
	XEB(N, L, R, JIT_R2, JIT_V0)			\
	XEB(N, L, R, JIT_R2, JIT_V1)			\
	XEB(N, L, R, JIT_R2, JIT_V2)			\
	XEB(N, L, R, JIT_R2, JIT_R0)			\
	XEB(N, L, R, JIT_R2, JIT_R1)

#define XBOPI(N, Ls, Rs, Lu, Ru)			\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_V0, JIT_V1)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_V0, JIT_V2)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_V0, JIT_R0)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_V0, JIT_R1)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_V0, JIT_R2)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_V1, JIT_V0)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_V1, JIT_V2)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_V1, JIT_R0)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_V1, JIT_R1)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_V1, JIT_R2)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_V2, JIT_V0)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_V2, JIT_V1)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_V2, JIT_R0)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_V2, JIT_R1)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_V2, JIT_R2)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_R0, JIT_V0)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_R0, JIT_V1)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_R0, JIT_V2)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_R0, JIT_R1)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_R0, JIT_R2)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_R1, JIT_V0)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_R1, JIT_V1)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_R1, JIT_V2)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_R1, JIT_R0)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_R1, JIT_R2)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_R2, JIT_V0)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_R2, JIT_V1)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_R2, JIT_V2)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_R2, JIT_R0)		\
	XBOP(N, Ls, Rs, Lu, Ru, JIT_R2, JIT_R1)

#define TBOPF(N, T, L, R)				\
{							\
	dump_args(N##r##_##T, L, R);			\
	jit_movi_##T(_jit, JIT_F0, L);			\
	jit_movi_##T(_jit, JIT_F1, R);			\
	jit_reloc_t r =					\
	jit_b##N##r##_##T(_jit, JIT_F0, JIT_F1);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##i##_##T, L, R);			\
	jit_movi_##T(_jit, JIT_F0, L);			\
	jit_movi_##T(_jit, JIT_F1, R);			\
	jit_reloc_t r =					\
	jit_b##N##r##_##T(_jit, JIT_F0, JIT_F1);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##r##_##T, L, NaN);			\
	jit_movi_##T(_jit, JIT_F0, L);			\
	jit_movi_##T(_jit, JIT_F1, NaN);		\
	jit_reloc_t err =				\
	jit_b##N##r##_##T(_jit, JIT_F0, JIT_F1);	\
	jit_reloc_t ok = jit_jmp(_jit);			\
	jit_patch_here(_jit, err);			\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, ok);			\
}							\
{							\
	dump_args(N##i##_##T, L, NaN);			\
	jit_movi_##T(_jit, JIT_F0, L);			\
	jit_movi_##T(_jit, JIT_F1, NaN);		\
	jit_reloc_t err =				\
	jit_b##N##r##_##T(_jit, JIT_F0, JIT_F1);	\
	jit_reloc_t ok = jit_jmp(_jit);			\
	jit_patch_here(_jit, err);			\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, ok);			\
}

#define BOPF(N, L, R)					\
	TBOPF(N, f, L, R)				\
	TBOPF(N, d, L, R)

#define TUBOPF(N, T, L, R)				\
{							\
	dump_args(N##r##_##T, L, R);			\
	jit_movi_##T(_jit, JIT_F0, L);			\
	jit_movi_##T(_jit, JIT_F1, R);			\
	jit_reloc_t r =					\
	jit_b##N##r##_##T(_jit, JIT_F0, JIT_F1);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##i##_##T, L, R);			\
	jit_movi_##T(_jit, JIT_F0, L);			\
	jit_movi_##T(_jit, JIT_F1, R);			\
	jit_reloc_t r =					\
	jit_b##N##r##_##T(_jit, JIT_F0, JIT_F1);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##r##_##T, L, NaN);			\
	jit_movi_##T(_jit, JIT_F0, L);			\
	jit_movi_##T(_jit, JIT_F1, NaN);		\
	jit_reloc_t r =					\
	jit_b##N##r##_##T(_jit, JIT_F0, JIT_F1);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##i##_##T, L, NaN);			\
	jit_movi_##T(_jit, JIT_F0, L);			\
	jit_movi_##T(_jit, JIT_F1, NaN);		\
	jit_reloc_t r =					\
	jit_b##N##r##_##T(_jit, JIT_F0, JIT_F1);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}

#define UBOPF(N, L, R)					\
	TUBOPF(N, f, L, R)				\
	TUBOPF(N, d, L, R)

#define ARGB(N, L, R)					\
{							\
	dump_args(N##r, L, R);				\
	jit_movi(_jit, JIT_R0, L);			\
	jit_movi(_jit, JIT_R1, R);			\
	jit_reloc_t r =					\
	jit_b##N##r(_jit, JIT_R0, JIT_R1);		\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##i, L, R);				\
	jit_movi(_jit, JIT_R0, L);			\
	jit_reloc_t r = jit_b##N##i(_jit, JIT_R0, R);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##r_u, R, L);			\
	jit_movi(_jit, JIT_R0, R);			\
	jit_movi(_jit, JIT_R1, L);			\
	jit_reloc_t r =					\
	jit_b##N##r_u(_jit, JIT_R0, JIT_R1);\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##i_u, R, L);			\
	jit_movi(_jit, JIT_R0, R);			\
	jit_reloc_t r = jit_b##N##i_u(_jit, JIT_R0, L);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}

#define ARGBS()						\
	ARGB(lt, -1, 1)					\
	ARGB(le, -1, -1)				\
	ARGB(ge, -1, -1)				\
	ARGB(gt, 1, -1)					\

#define OVFGB(N, L, R, U, D)				\
{							\
	dump_args(N##r, L, );				\
	jit_movi(_jit, JIT_R0, L);			\
	jit_movi(_jit, JIT_R1, 1);			\
	jit_reloc_t r =					\
	jit_b##N##r(_jit, JIT_R0, JIT_R1);		\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##r_u, R, );				\
	jit_movi(_jit, JIT_R0, R);			\
	jit_movi(_jit, JIT_R1, 1);			\
	jit_reloc_t r =					\
	jit_b##N##r_u(_jit, JIT_R0, JIT_R1);		\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##i, U, );				\
	jit_movi(_jit, JIT_R0, U);			\
	jit_reloc_t r =					\
	jit_b##N##i(_jit, JIT_R0, 1);			\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##i_u, D, );				\
	jit_movi(_jit, JIT_R0, D);			\
	jit_reloc_t r =					\
	jit_b##N##i_u(_jit, JIT_R0, 1);			\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}

#define OVFGBS()					\
	OVFGB(oadd, I7f, Iff, I7f, Iff)			\
	OVFGB(xadd, I80, I7f, I80, I7f)			\
	OVFGB(osub, I80, 0x0, I80, 0x0)			\
	OVFGB(xsub, I81, I80, I81, I80)

#define MGB(N, L, R)					\
{							\
	dump_args(N##r, L, R);				\
	jit_movi(_jit, JIT_R0, L);			\
	jit_movi(_jit, JIT_R1, R);			\
	jit_reloc_t r =					\
	jit_b##N##r(_jit, JIT_R0, JIT_R1);		\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##i, L, R);				\
	jit_movi(_jit, JIT_R0, L);			\
	jit_reloc_t r = jit_b##N##i(_jit, JIT_R0, R);	\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}

#define MBGS()						\
	MGB(ms, 1, 3)					\
	MGB(mc, 1, 2)					\
	MGB(ne, -3, 3)					\
	MGB(eq, 3, 3)

#define ARFGB(N, L, R)					\
{							\
	dump_args(N##r_f, L, R);			\
	jit_movi_f(_jit, JIT_F0, L);			\
	jit_movi_f(_jit, JIT_F1, R);			\
	jit_reloc_t r =					\
	jit_b##N##r_f(_jit, JIT_F0, JIT_F1);		\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}							\
{							\
	dump_args(N##i_f, L, R);			\
	jit_movi_f(_jit, JIT_F0, L);			\
	jit_movi_f(_jit, JIT_F1, R);			\
	jit_reloc_t r =					\
	jit_b##N##r_f(_jit, JIT_F0, JIT_F1);		\
	jit_calli_0(_jit, abort);			\
	jit_patch_here(_jit, r);			\
}

#define ARFGBS()					\
	ARFGB(lt, 1, 2)					\
	ARFGB(le, -1, -1)				\
	ARFGB(ge, -3, -3)				\
	ARFGB(gt, 2, 1)					\
	ARFGB(eq, -2, -2)				\
	ARFGB(ne, 0, 2)

static size_t
run_test(jit_state_t *_jit, uint8_t *arena_base, size_t arena_size)
{
	void (*function)();
	jit_begin(_jit, arena_base, arena_size);
	size_t frame = jit_enter_jit_abi(_jit, 0, 0, 0);

	ARGBS();
	MBGS();
	OVFGBS();
	ARFGBS();

	BOPI(lt, -1, 1, 1, -1)
	BOPI(le, -1, -1, 1, 1)
	EBI(eq, 32, 32)
	BOPI(ge, -2, -2, 2, 2)
	BOPI(gt, 2, -2, -2, 2)
	EBI(ne, 3, -3)
	XEBI(ms, 1, 3)
	XEBI(mc, 1, 2)
	XBOPI(oadd, I7f, 1, Iff, 1)
	XBOPI(xadd, I80, 1, I7f, 1)
	XBOPI(osub, I80, 1, 0, 1)
	XBOPI(xsub, I81, 1, I80, 1)
	BOPF(lt, 1, 2)
	BOPF(le, 2, 2)
	BOPF(eq, 3, 3)
	BOPF(ge, 3, 3)
	BOPF(gt, 4, 3)
	UBOPF(ne, 4, 3)
	UBOPF(unlt, 1, 2)
	UBOPF(unle, 2, 2)
	UBOPF(uneq, 3, 3)
	UBOPF(unge, 3, 3)
	UBOPF(ungt, 4, 3)
	BOPF(ltgt, 4, 3)

	{
		dump_args(ordr, 5, 5);
		jit_movi_f(_jit, JIT_F0, 5);
		jit_movi_f(_jit, JIT_F1, 5);
		jit_reloc_t r = jit_bordr_f(_jit, JIT_F0, JIT_F1);
		jit_calli_0(_jit, abort);
		jit_patch_here(_jit, r);
	}
	{
		dump_args(ordr, 5, 1);
		jit_movi_f(_jit, JIT_F0, 5);
		jit_movi_f(_jit, JIT_F1, 1);
		jit_reloc_t r = jit_bordr_f(_jit, JIT_F0, JIT_F1);
		jit_calli_0(_jit, abort);
		jit_patch_here(_jit, r);
	}
	{
		dump_args(ordr, 5, NaN);
		jit_movi_f(_jit, JIT_F0, 5);
		jit_movi_f(_jit, JIT_F1, NaN);
		jit_reloc_t err = jit_bordr_f(_jit, JIT_F0, JIT_F1);
		jit_reloc_t ok = jit_jmp(_jit);
		jit_patch_here(_jit, err);
		jit_calli_0(_jit, abort);
		jit_patch_here(_jit, ok);
	}
	{
		dump_args(unordr, 5, 5);
		jit_movi_f(_jit, JIT_F0, 5);
		jit_movi_f(_jit, JIT_F1, 5);
		jit_reloc_t err = jit_bunordr_f(_jit, JIT_F0, JIT_F1);
		jit_reloc_t ok = jit_jmp(_jit);
		jit_patch_here(_jit, err);
		jit_calli_0(_jit, abort);
		jit_patch_here(_jit, ok);
	}
	{
		dump_args(unordr, 5, 1);
		jit_movi_f(_jit, JIT_F0, 5);
		jit_movi_f(_jit, JIT_F1, 1);
		jit_reloc_t err = jit_bunordr_f(_jit, JIT_F0, JIT_F1);
		jit_reloc_t ok = jit_jmp(_jit);
		jit_patch_here(_jit, err);
		jit_calli_0(_jit, abort);
		jit_patch_here(_jit, ok);
	}
	{
		dump_args(unordr, 5, NaN);
		jit_movi_f(_jit, JIT_F0, 5);
		jit_movi_f(_jit, JIT_F1, NaN);
		jit_reloc_t r = jit_bunordr_f(_jit, JIT_F0, JIT_F1);
		jit_calli_0(_jit, abort);
		jit_patch_here(_jit, r);
	}

	jit_leave_jit_abi(_jit, 0, 0, frame);
	jit_ret(_jit);

	size_t size;
	function = jit_end(_jit, &size);

	if (function)
		(*function)();
	else
		return size;

	return 0;
}

int main(int argc, char *argv[])
{
	return main_compiler(argc, argv, run_test);
}
