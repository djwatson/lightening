#include "test.h"

#define operand_c JIT_OPERAND_ABI_INT8
#define operand_s JIT_OPERAND_ABI_INT16
#define operand_i JIT_OPERAND_ABI_INT32
#define operand_uc JIT_OPERAND_ABI_UINT8
#define operand_us JIT_OPERAND_ABI_UINT16
#define operand_ui JIT_OPERAND_ABI_UINT32
#define operand_l JIT_OPERAND_ABI_INT64
#define operand_f JIT_OPERAND_ABI_FLOAT
#define operand_d JIT_OPERAND_ABI_DOUBLE

#define def_wi(i)							\
	void *_w##i = jit_address(_jit);				\
{									\
	size_t frame = jit_enter_jit_abi(_jit, 0, 0, 0);		\
	jit_load_args_1(_jit, jit_operand_gpr(operand##i, JIT_R0));	\
	jit_leave_jit_abi(_jit, 0, 0, frame);				\
	jit_retr(_jit, JIT_R0);						\
}

#define def_wf(f)							\
	void *_w##f = jit_address(_jit);				\
{									\
	size_t frame = jit_enter_jit_abi(_jit, 0, 0, 0);		\
	jit_load_args_1(_jit, jit_operand_fpr(operand##f, JIT_F0));	\
	jit_truncr##f(_jit, JIT_R0, JIT_F0);				\
	jit_leave_jit_abi(_jit, 0, 0, frame);				\
	jit_retr(_jit, JIT_R0);						\
}

#define def_fi(f, i)							\
	void *f##i = jit_address(_jit);					\
{									\
	size_t frame = jit_enter_jit_abi(_jit, 0, 0, 0);		\
	jit_load_args_1(_jit, jit_operand_gpr(operand##i, JIT_R0));	\
	jit_extr##f(_jit, JIT_F0, JIT_R0);				\
	jit_leave_jit_abi(_jit, 0, 0, frame);				\
	jit_retr##f(_jit, JIT_F0);					\
}

#define def_f(f)							\
	void *f##f = jit_address(_jit);					\
{									\
	size_t frame = jit_enter_jit_abi(_jit, 0, 0, 0);		\
	jit_load_args_1(_jit, jit_operand_fpr(operand##f, JIT_F0));	\
	jit_leave_jit_abi(_jit, 0, 0, frame);				\
	jit_retr##f(_jit, JIT_F0);					\
}

#define def_ff(f, g)							\
	void *f##g = jit_address(_jit);					\
{									\
	size_t frame = jit_enter_jit_abi(_jit, 0, 0, 0);		\
	jit_load_args_1(_jit, jit_operand_fpr(operand##f, JIT_F0));	\
	jit_extr##f##g(_jit, JIT_F0, JIT_F0);				\
	jit_leave_jit_abi(_jit, 0, 0, frame);				\
	jit_retr##f(_jit, JIT_F0);					\
}

#if defined(DEBUG)
#define dump_args(n, f, i, a, r)						\
	jit_calli_1(_jit, puts,						\
	jit_operand_imm(JIT_OPERAND_ABI_POINTER,			\
	(jit_imm_t)#n " " #f " " #i " " #a " " #r))
#else
#define dump_args(n, f, i, a, r)
#endif

#define _call_w(n, i, a, r)						\
{									\
	dump_args(n, , i, a, r);					\
	jit_calli_1(_jit, _w##i, jit_operand_imm(operand##i, a));	\
	jit_retval(_jit, JIT_R0);					\
	jit_extr##i(_jit, JIT_R0, JIT_R0);				\
	jit_reloc_t ok = jit_beqi(_jit, JIT_R0, r);			\
	jit_calli_0(_jit, abort);					\
	jit_patch_here(_jit, ok);					\
}
#define call_w(n, i, a, r)		_call_w(n, i, a, r)

#define _call_wf(n, f, a, r)						\
{									\
	dump_args(n, f, , a, r);					\
	jit_movi##f(_jit, JIT_F0, (long long)a);			\
	jit_calli_1(_jit, _w##f, jit_operand_fpr(operand##f, JIT_F0));	\
	jit_retval(_jit, JIT_R0);					\
	jit_extr##f(_jit, JIT_F0, JIT_R0);				\
	jit_movi##f(_jit, JIT_F1, r);					\
	jit_reloc_t ok = jit_beqr##f(_jit, JIT_F0, JIT_F1);		\
	jit_calli_0(_jit, abort);					\
	jit_patch_here(_jit, ok);					\
}
#define call_wf(n, f, a, r)		_call_wf(n, f, a, r)

#define _call_fi(n, f, i, a, r)						\
{									\
	dump_args(n, f, i, a, r);					\
	jit_calli_1(_jit, f##i, jit_operand_imm(operand##i, a));	\
	jit_retval##f(_jit, JIT_F0);					\
	jit_movi##f(_jit, JIT_F1, r);					\
	jit_reloc_t ok = jit_beqr##f(_jit, JIT_F0, JIT_F1);		\
	jit_calli_0(_jit, abort);					\
	jit_patch_here(_jit, ok);					\
}
#define call_fi(n, f, i, a, r)		_call_fi(n, f, i, a, r)

#define _call_f(n, f, a, r)						\
{									\
	dump_args(n, f, , a, r);					\
	jit_movi##f(_jit, JIT_F0, a);					\
	jit_calli_1(_jit, f##f, jit_operand_fpr(operand##f, JIT_F0));	\
	jit_retval##f(_jit, JIT_F0);					\
	jit_movi##f(_jit, JIT_F1, r);					\
	jit_reloc_t ok = jit_beqr##f(_jit, JIT_F0, JIT_F1);		\
	jit_calli_0(_jit, abort);					\
	jit_patch_here(_jit, ok);					\
}
#define call_f(n, f, a, r)		_call_f(n, f, a, r)

#define _call_ff(n, f, g, a, r)						\
{									\
	dump_args(n, f, g, a, r);					\
	jit_movi##f(_jit, JIT_F0, a);					\
	jit_calli_1(_jit, f##g, jit_operand_fpr(operand##f, JIT_F0));	\
	jit_retval##g(_jit, JIT_F0);					\
	jit_movi##g(_jit, JIT_F1, r);					\
	jit_reloc_t ok = jit_beqr##g(_jit, JIT_F0, JIT_F1);		\
	jit_calli_0(_jit, abort);					\
	jit_patch_here(_jit, ok);					\
}
#define call_ff(n, f, g, a, r)		_call_ff(n, f, g, a, r)

#define c7f		(int8_t)0x7f
#define c80		(int8_t)0x80
#define c81		(int8_t)0x81
#define cff		(int8_t)0xff
#define s7f		(int16_t)0x7fff
#define s80		(int16_t)0x8000
#define s81		(int16_t)0x8001
#define i7f		(int32_t)0x7fffffff
#define i80		(int32_t)0x80000000
#define i81		(int32_t)0x80000001
#define iff		(int32_t)0xffffffff
#define l7f		(int64_t)0x7fffffffffffffff
#define l80		(int64_t)0x8000000000000000
#define l81		(int64_t)0x8000000000000001

#define uc7f		(uint8_t)0x7f
#define uc80		(uint8_t)0x80
#define uc81		(uint8_t)0x81
#define ucff		(uint8_t)0xff
#define us7f		(uint16_t)0x7fff
#define us80		(uint16_t)0x8000
#define us81		(uint16_t)0x8001
#define ui7f		(uint32_t)0x7fffffff
#define ui80		(uint32_t)0x80000000
#define ui81		(uint32_t)0x80000001
#define uiff		(uint32_t)0xffffffff
#define ul7f		(uint64_t)0x7fffffffffffffff
#define ul80		(uint64_t)0x8000000000000000
#define ul81		(uint64_t)0x8000000000000001

#define f7f		 127.0
#define f80		-128.0
#define f81		-127.0
#define uf80		 128.0
#define uf81		 127.0

#if __WORDSIZE == 32
#  define wc80		(long)0xffffff80
#  define wc81		(long)0xffffff81
#  define ws80		(long)0xffff8000
#  define ws81		(long)0xffff8001
#else
#  define wc80		(long)0xffffffffffffff80
#  define wc81		(long)0xffffffffffffff81
#  define ws80		(long)0xffffffffffff8000
#  define ws81		(long)0xffffffffffff8001
#  define wi80		(long)0xffffffff80000000
#  define wi81		(long)0xffffffff80000001
#endif

static size_t
run_test(jit_state_t *_jit, uint8_t *arena_base, size_t arena_size)
{
	void (*function)();
	jit_begin(_jit, arena_base, arena_size);
	jit_reloc_t main = jit_jmp(_jit);

	def_wi(_c)
	def_wi(_uc)
	def_wi(_s)
	def_wi(_us)
#if __WORDSIZE == 64
	def_wi(_i)
	def_wi(_ui)
#endif
	def_wf(_f)
	def_wf(_d)
	def_fi(_f, _c)
	def_fi(_f, _uc)
	def_fi(_f, _s)
	def_fi(_f, _us)
	def_fi(_f, _i)
#if __WORDSIZE == 64
	def_fi(_f, _ui)
	def_fi(_f, _l)
#endif
	def_fi(_d, _c)
	def_fi(_d, _uc)
	def_fi(_d, _s)
	def_fi(_d, _us)
	def_fi(_d, _i)
#if __WORDSIZE == 64
	def_fi(_d, _ui)
	def_fi(_d, _l)
#endif
	def_f(_f)
	def_f(_d)
	def_ff(_f, _d)
	def_ff(_d, _f)

	jit_patch_here(_jit, main);
	size_t frame = jit_enter_jit_abi(_jit, 0, 0, 0);

	call_w(__LINE__, _c,  c7f, c7f)
	call_w(__LINE__, _c,  c80, wc80)
	call_w(__LINE__, _c,  c81, wc81)
	call_w(__LINE__, _uc, uc7f, c7f)
	call_w(__LINE__, _uc, uc80, uc80)
	call_w(__LINE__, _uc, uc81, uc81)
	call_w(__LINE__, _s,  s7f, s7f)
	call_w(__LINE__, _s,  s80, ws80)
	call_w(__LINE__, _s,  s81, ws81)
	call_w(__LINE__, _us, us7f, us7f)
	call_w(__LINE__, _us, us80, us80)
	call_w(__LINE__, _us, us81, us81)
#if __WORDSIZE == 64
	call_w(__LINE__, _i,  i7f, i7f)
	call_w(__LINE__, _i,  i80, wi80)
	call_w(__LINE__, _i,  i81, wi81)
	call_w(__LINE__, _ui, ui7f, ui7f)
	call_w(__LINE__, _ui, ui80, ui80)
	call_w(__LINE__, _ui, ui81, ui81)
#endif
	call_wf(__LINE__, _f, c7f, f7f)
	call_wf(__LINE__, _f, wc80, f80)
	call_wf(__LINE__, _f, wc81, f81)
	call_wf(__LINE__, _d, c7f, f7f)
	call_wf(__LINE__, _d, wc80, f80)
	call_wf(__LINE__, _d, wc81, f81)
	call_fi(__LINE__, _f, _c, c7f, f7f)
	call_fi(__LINE__, _f, _c, c80, f80)
	call_fi(__LINE__, _f, _uc, uc7f, f7f)
	call_fi(__LINE__, _f, _uc, uc80, uf80)
	call_fi(__LINE__, _f, _s, c7f, f7f)
	call_fi(__LINE__, _f, _s, uc80, uf80)
	call_fi(__LINE__, _f, _us, uc7f, f7f)
	call_fi(__LINE__, _f, _us, uc80, uf80)
	call_fi(__LINE__, _f, _i, c7f, f7f)
	call_fi(__LINE__, _f, _i, uc80, uf80)
#if __WORDSIZE == 64
	call_fi(__LINE__, _f, _ui, uc7f, f7f)
	call_fi(__LINE__, _f, _ui, uc80, uf80)
	call_fi(__LINE__, _f, _l, c7f, f7f)
	call_fi(__LINE__, _f, _l, uc80, uf80)
#endif
	call_fi(__LINE__, _d, _c, c7f, f7f)
	call_fi(__LINE__, _d, _c, c80, f80)
	call_fi(__LINE__, _d, _uc, uc7f, f7f)
	call_fi(__LINE__, _d, _uc, uc80, uf80)
	call_fi(__LINE__, _d, _s, c7f, f7f)
	call_fi(__LINE__, _d, _s, uc80, uf80)
	call_fi(__LINE__, _d, _us, uc7f, f7f)
	call_fi(__LINE__, _d, _us, uc80, uf80)
	call_fi(__LINE__, _d, _i, c7f, f7f)
	call_fi(__LINE__, _d, _i, uc80, uf80)
#if __WORDSIZE == 64
	call_fi(__LINE__, _d, _ui, uc7f, f7f)
	call_fi(__LINE__, _d, _ui, uc80, uf80)
	call_fi(__LINE__, _d, _l, c7f, f7f)
	call_fi(__LINE__, _d, _l, uc80, uf80)
#endif
	call_f(__LINE__, _f, f7f, f7f)
	call_f(__LINE__, _d, f7f, f7f)
	call_ff(__LINE__, _f, _d, f80, f80)
	call_ff(__LINE__, _d, _f, f81, f81)

	jit_leave_jit_abi(_jit, 0, 0, frame);
	jit_ret(_jit);

	size_t size = 0;
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
