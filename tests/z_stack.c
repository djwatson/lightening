#include "test.h"

#if defined(DEBUG)
#define dump_args(N, M, T)					\
	jit_calli_1(_jit, puts,					\
	jit_operand_imm(JIT_OPERAND_ABI_POINTER,		\
	(jit_imm_t)#N " " #M " " #T));
#else
#define dump_args(N, M, T)
#endif

#define szof_c			1
#define szof_uc			szof_c
#define szof_s			2
#define szof_us			szof_s
#define szof_i			4
#if __WORDSIZE == 64
#  define szof_ui		szof_i
#  define szof_l		8
#endif
#define szof_max		8

#define operand_c JIT_OPERAND_ABI_INT8
#define operand_uc JIT_OPERAND_ABI_UINT8
#define operand_s JIT_OPERAND_ABI_INT16
#define operand_us JIT_OPERAND_ABI_UINT16
#define operand_i JIT_OPERAND_ABI_INT32
#define operand_ui JIT_OPERAND_ABI_UINT32
#define operand_l JIT_OPERAND_ABI_INT64
#define operand_ul JIT_OPERAND_ABI_UINT64
#define operand_f JIT_OPERAND_ABI_FLOAT
#define operand_d JIT_OPERAND_ABI_DOUBLE

#define FILL(T)							\
	void *fill##T = jit_address(_jit);			\
{								\
	size_t frame = jit_enter_jit_abi(_jit, 2, 0, 0);	\
	jit_load_args_2(_jit,					\
	jit_operand_gpr(JIT_OPERAND_ABI_POINTER, JIT_V0),	\
	jit_operand_gpr(JIT_OPERAND_ABI_UINT32, JIT_R0));	\
								\
	jit_muli(_jit, JIT_R0, JIT_R0, szof##T);		\
	jit_addr(_jit, JIT_V1, JIT_V0, JIT_R0);			\
	jit_movi(_jit, JIT_R0, 0);				\
								\
	void *loop = jit_address(_jit);				\
	jit_reloc_t done = jit_bger(_jit, JIT_V0, JIT_V1);	\
	jit_str##T(_jit, JIT_V0, JIT_R0);			\
	jit_addi(_jit, JIT_R0, JIT_R0, 1);			\
	jit_addi(_jit, JIT_V0, JIT_V0, szof##T);		\
	jit_jmpi(_jit, loop);					\
								\
	jit_patch_here(_jit, done);				\
	jit_leave_jit_abi(_jit, 2, 0, frame);			\
	jit_ret(_jit);						\
}

#define fill_uc		fill_c
#define fill_us		fill_s
#define fill_ui		fill_i

#define ARG(  T, N) jit_operand_mem(operand##T, JIT_SP, - ((N + 1) * szof_max))

#define ARG1( K, T)			ARG##K(T, 0)
#define ARG2( K, T)	ARG1( K, T),	ARG##K(T, 1)
#define ARG3( K, T)	ARG2( K, T),	ARG##K(T, 2)
#define ARG4( K, T)	ARG3( K, T),	ARG##K(T, 3)
#define ARG5( K, T)	ARG4( K, T),	ARG##K(T, 4)
#define ARG6( K, T)	ARG5( K, T),	ARG##K(T, 5)
#define ARG7( K, T)	ARG6( K, T),	ARG##K(T, 6)
#define ARG8( K, T)	ARG7( K, T),	ARG##K(T, 7)
#define ARG9( K, T)	ARG8( K, T),	ARG##K(T, 8)
#define ARG10(K, T)	ARG9( K, T),	ARG##K(T, 9)
#define ARG11(K, T)	ARG10(K, T),	ARG##K(T, 10)
#define ARG12(K, T)	ARG11(K, T),	ARG##K(T, 11)
#define ARG13(K, T)	ARG12(K, T),	ARG##K(T, 12)
#define ARG14(K, T)	ARG13(K, T),	ARG##K(T, 13)
#define ARG15(K, T)	ARG14(K, T),	ARG##K(T, 14)
#define ARG16(K, T)	ARG15(K, T),	ARG##K(T, 15)
#define ARG_c(N)			ARG##N( , _c)
#define ARG_uc(N)			ARG##N( , _uc)
#define ARG_s(N)			ARG##N( , _s)
#define ARG_us(N)			ARG##N( , _us)
#define ARG_i(N)			ARG##N( , _i)
#define ARG_ui(N)			ARG##N( , _ui)
#define ARG_l(N)			ARG##N( , _l)
#define ARG_f(N)			ARG##N(F, _f)
#define ARG_d(N)			ARG##N(F, _d)

#define CHK(N, T, V)								\
{										\
	jit_ldxi##T(_jit, JIT_R0, JIT_SP, arg_space - ((V + 1) * szof_max));	\
	jit_ldxi##T(_jit, JIT_R1, JIT_V0, (V * szof##T));			\
	jit_reloc_t r = jit_beqr(_jit, JIT_R0, JIT_R1);				\
	jit_calli_0(_jit, abort);						\
	jit_patch_here(_jit, r);						\
}

#define GET1( K, N, T, V)				CHK##K(N, T, 0)
#define GET2( K, N, T, V)	GET1( K, N, T, V)	CHK##K(N, T, 1)
#define GET3( K, N, T, V)	GET2( K, N, T, V)	CHK##K(N, T, 2)
#define GET4( K, N, T, V)	GET3( K, N, T, V)	CHK##K(N, T, 3)
#define GET5( K, N, T, V)	GET4( K, N, T, V)	CHK##K(N, T, 4)
#define GET6( K, N, T, V)	GET5( K, N, T, V)	CHK##K(N, T, 5)
#define GET7( K, N, T, V)	GET6( K, N, T, V)	CHK##K(N, T, 6)
#define GET8( K, N, T, V)	GET7( K, N, T, V)	CHK##K(N, T, 7)
#define GET9( K, N, T, V)	GET8( K, N, T, V)	CHK##K(N, T, 8)
#define GET10(K, N, T, V)	GET9( K, N, T, V)	CHK##K(N, T, 9)
#define GET11(K, N, T, V)	GET10(K, N, T, V)	CHK##K(N, T, 10)
#define GET12(K, N, T, V)	GET11(K, N, T, V)	CHK##K(N, T, 11)
#define GET13(K, N, T, V)	GET12(K, N, T, V)	CHK##K(N, T, 12)
#define GET14(K, N, T, V)	GET13(K, N, T, V)	CHK##K(N, T, 13)
#define GET15(K, N, T, V)	GET14(K, N, T, V)	CHK##K(N, T, 14)
#define GET16(K, N, T, V)	GET15(K, N, T, V)	CHK##K(N, T, 15)

#define GET_c(N, M)		GET##N( , c##N,  _c,  M)
#define GET_uc(N, M)		GET##N( , uc##N, _uc, M)
#define GET_s(N, M)		GET##N( , s##N,  _s,  M)
#define GET_us(N, M)		GET##N( , us##N, _us, M)
#define GET_i(N, M)		GET##N( , i##N,  _i,  M)
#define GET_ui(N, M)		GET##N( , ui##N, _ui, M)
#define GET_l(N, M)		GET##N( , l##N,  _l,  M)
#define GET_f(N, M)		GET##N(F, f##N,  _f,  M)
#define GET_d(N, M)		GET##N(F, d##N,  _d,  M)

#define PUSH(  T, V) jit_operand_imm(operand##T, V)
#define PUSH0( K, T)		/**/
#define PUSH1( K, T)					PUSH##K(T, 0)
#define PUSH2( K, T)		PUSH1( K, T),		PUSH##K(T, 1)
#define PUSH3( K, T)		PUSH2( K, T),		PUSH##K(T, 2)
#define PUSH4( K, T)		PUSH3( K, T),		PUSH##K(T, 3)
#define PUSH5( K, T)		PUSH4( K, T),		PUSH##K(T, 4)
#define PUSH6( K, T)		PUSH5( K, T),		PUSH##K(T, 5)
#define PUSH7( K, T)		PUSH6( K, T),		PUSH##K(T, 6)
#define PUSH8( K, T)		PUSH7( K, T),		PUSH##K(T, 7)
#define PUSH9( K, T)		PUSH8( K, T),		PUSH##K(T, 8)
#define PUSH10(K, T)		PUSH9( K, T),		PUSH##K(T, 9)
#define PUSH11(K, T)		PUSH10(K, T),		PUSH##K(T, 10)
#define PUSH12(K, T)		PUSH11(K, T),		PUSH##K(T, 11)
#define PUSH13(K, T)		PUSH12(K, T),		PUSH##K(T, 12)
#define PUSH14(K, T)		PUSH13(K, T),		PUSH##K(T, 13)
#define PUSH15(K, T)		PUSH14(K, T),		PUSH##K(T, 14)
#define PUSH16(K, T)		PUSH15(K, T),		PUSH##K(T, 15)

#define PUSH_c( N)		PUSH##N( , _c)
#define PUSH_uc(N)		PUSH##N( , _uc)
#define PUSH_s( N)		PUSH##N( , _s)
#define PUSH_us(N)		PUSH##N( , _us)
#define PUSH_i( N)		PUSH##N( , _i)
#define PUSH_ui(N)		PUSH##N( , _ui)
#define PUSH_l( N)		PUSH##N( , _l)
#define PUSH_f( N)		PUSH##N(F, _f)
#define PUSH_d( N)		PUSH##N(F, _d)

/* bottom function */
#define DEF0(T)							\
	void *test##T##_0 = jit_address(_jit);			\
{								\
	size_t frame = jit_enter_jit_abi(_jit, 0, 0, 0);	\
	dump_args(0, 0, T);					\
	jit_leave_jit_abi(_jit, 0, 0, frame);			\
	jit_ret(_jit);						\
}

/*
 * stack frame:
 * | lightening reserved stuff - frame |
 * |-----------------------------------| <- JIT_SP at entry
 * | argument save area - arg_space    |
 * |-----------------------------------| <- JIT_SP during argument validation
 * | stack buffer - stack              |
 * |-----------------------------------| <- JIT_SP during next call
 *
 * at entry, first push arguments in ascending order (0, 1, 2, ...)
 * to stack, and afterwards move JIT_SP forward to not mess with the internal
 * load_args stuff.
 */
#define DEFN(N, M, T)						\
	void *test##T##_##N = jit_address(_jit);		\
{								\
	size_t frame = jit_enter_jit_abi(_jit, 3, 0, 0);	\
	jit_operand_t args[] =					\
	{jit_operand_gpr(JIT_OPERAND_ABI_POINTER, JIT_V0),	\
	 ARG##T(N)};						\
	jit_load_args(_jit, N + 1, args);			\
								\
	size_t arg_space = jit_align_stack(_jit, N * szof_max);	\
								\
	dump_args(N, M, T);					\
								\
	/* validate arguments */				\
	GET##T(N, M)						\
								\
	/* heap buffer in %v1 */				\
	jit_calli_1(_jit, malloc,				\
	jit_operand_imm(JIT_OPERAND_ABI_UINT32, N * szof##T));	\
	jit_retval(_jit, JIT_V1);				\
								\
	/* copy stack buffer to heap buffer */			\
	jit_calli_3(_jit, memcpy,				\
	jit_operand_gpr(JIT_OPERAND_ABI_POINTER, JIT_V1),	\
	jit_operand_gpr(JIT_OPERAND_ABI_POINTER, JIT_V0),	\
	jit_operand_imm(JIT_OPERAND_ABI_UINT32, N * szof##T));	\
								\
	/* stack buffer for next function in %v2 */		\
	size_t stack = jit_align_stack(_jit, M * szof##T);	\
	jit_movr(_jit, JIT_V2, JIT_SP);				\
								\
	/* fill stack buffer for next function */		\
	jit_calli_2(_jit, fill##T,				\
	jit_operand_gpr(JIT_OPERAND_ABI_POINTER, JIT_V2),	\
	jit_operand_imm(JIT_OPERAND_ABI_UINT32, M));		\
								\
	/* call next function */				\
	jit_operand_t call_args[] =				\
	{jit_operand_gpr(JIT_OPERAND_ABI_POINTER, JIT_V2),	\
	 PUSH##T(M)};						\
	jit_calli(_jit, test##T##_##M, M + 1, call_args);	\
								\
	/* validate stack buffer */				\
	jit_calli_3(_jit, memcmp,				\
	jit_operand_gpr(JIT_OPERAND_ABI_POINTER, JIT_V1),	\
	jit_operand_gpr(JIT_OPERAND_ABI_POINTER, JIT_V0),	\
	jit_operand_imm(JIT_OPERAND_ABI_UINT32, N * szof##T));	\
	jit_retval(_jit, JIT_R0);				\
	jit_reloc_t r = jit_beqi(_jit, JIT_R0, 0);		\
	jit_calli_0(_jit, abort);				\
	jit_patch_here(_jit, r);				\
								\
	/* release heap bufer */				\
	jit_calli_1(_jit, free,					\
	jit_operand_gpr(JIT_OPERAND_ABI_POINTER, JIT_V1));	\
	jit_shrink_stack(_jit, arg_space);			\
	jit_shrink_stack(_jit, stack);				\
	jit_leave_jit_abi(_jit, 3, 0, frame);			\
	jit_ret(_jit);						\
}

/* top function */
#define DEFX(T)							\
	void *test##T##_17 = jit_address(_jit);			\
{								\
	size_t frame = jit_enter_jit_abi(_jit, 3, 0, 0);	\
	size_t arg_space = jit_align_stack(_jit, 16 * szof##T);	\
								\
	dump_args(17, top, T)					\
								\
	/* heap buffer in %v1 */				\
	jit_calli_1(_jit, malloc,				\
	jit_operand_imm(JIT_OPERAND_ABI_UINT32, 16 * szof##T));	\
	jit_retval(_jit, JIT_V1);				\
								\
	/* stack buffer for next function in %v2 */		\
	size_t stack = jit_align_stack(_jit, 16 * szof##T);	\
	jit_movr(_jit, JIT_V2, JIT_SP);				\
								\
	/* fill stack buffer for next function */		\
	jit_calli_2(_jit, fill##T,				\
	jit_operand_gpr(JIT_OPERAND_ABI_POINTER, JIT_V2),	\
	jit_operand_imm(JIT_OPERAND_ABI_UINT32, 16));		\
								\
	/* copy stack buffer to heap buffer */			\
	jit_calli_3(_jit, memcpy,				\
	jit_operand_gpr(JIT_OPERAND_ABI_POINTER, JIT_V1),	\
	jit_operand_gpr(JIT_OPERAND_ABI_POINTER, JIT_V2),	\
	jit_operand_imm(JIT_OPERAND_ABI_UINT32, 16 * szof##T));	\
								\
	/* call next function */				\
	jit_operand_t args[] =					\
	{jit_operand_gpr(JIT_OPERAND_ABI_POINTER, JIT_V2),	\
	 PUSH##T(16)};						\
	jit_calli(_jit, test##T##_16, 17, args);		\
								\
	/* validate stack buffer */				\
	jit_calli_3(_jit, memcmp,				\
	jit_operand_gpr(JIT_OPERAND_ABI_POINTER, JIT_V1),	\
	jit_operand_gpr(JIT_OPERAND_ABI_POINTER, JIT_V2),	\
	jit_operand_imm(JIT_OPERAND_ABI_UINT32, 16 * szof##T));	\
	jit_retval(_jit, JIT_R0);				\
	jit_reloc_t r = jit_beqi(_jit, JIT_R0, 0);		\
	jit_calli_0(_jit, abort);				\
	jit_patch_here(_jit, r);				\
								\
	/* release heap bufer */				\
	jit_calli_1(_jit, free,					\
	jit_operand_gpr(JIT_OPERAND_ABI_POINTER, JIT_V1));	\
	/* technically speaking not necessary */		\
	/* jit_leave_jit_abi will shrink stack for us */	\
	jit_shrink_stack(_jit, arg_space);			\
	jit_shrink_stack(_jit, stack);				\
	jit_leave_jit_abi(_jit, 3, 0, frame);			\
	jit_ret(_jit);						\
}

#define DEF(  T)						\
	DEF0( T)						\
	DEFN( 1,  0, T)						\
	DEFN( 2,  1, T)						\
	DEFN( 3,  2, T)						\
	DEFN( 4,  3, T)						\
	DEFN( 5,  4, T)						\
	DEFN( 6,  5, T)						\
	DEFN( 7,  6, T)						\
	DEFN( 8,  7, T)						\
	DEFN( 9,  8, T)						\
	DEFN(10,  9, T)						\
	DEFN(11, 10, T)						\
	DEFN(12, 11, T)						\
	DEFN(13, 12, T)						\
	DEFN(14, 13, T)						\
	DEFN(15, 14, T)						\
	DEFN(16, 15, T)						\
	DEFX(T)

#define CALL(T)			jit_calli_0(_jit, test##T##_17);

static size_t
run_test(jit_state_t *_jit, uint8_t *arena_base, size_t arena_size)
{
	jit_begin(_jit, arena_base, arena_size);
	int32_t (*function)();
	
	jit_reloc_t main = jit_jmp(_jit);

	FILL(_c)
	FILL(_s)
	FILL(_i)
#if __WORDSIZE == 64
	FILL(_l)
#endif

	DEF(_c)
	DEF(_uc)
	DEF(_s)
	DEF(_us)
	DEF(_i)
#if __WORDSIZE == 64
	DEF(_ui)
	DEF(_l)
#endif

	jit_patch_here(_jit, main);
	/* not sure about the actual number of registers, but too many can't
	 * hurt. */
	size_t frame = jit_enter_jit_abi(_jit, 3, 0, 0);

	CALL(_c)
	CALL(_uc)
	CALL(_s)
	CALL(_us)
	CALL(_i)
#if __WORDSIZE == 64
	CALL(_ui)
	CALL(_l)
#endif

	jit_leave_jit_abi(_jit, 3, 0, frame);
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
