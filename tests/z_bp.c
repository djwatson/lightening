#include "test.h"

static size_t
run_test(jit_state_t *_jit, uint8_t *arena_base, size_t arena_size)
{
	int32_t (*function)(int32_t);

	jit_begin(_jit, arena_base, arena_size);

	void *entry = jit_address(_jit);
	size_t frame = jit_enter_jit_abi(_jit, 3, 0, 0);

	jit_load_args_1(_jit, jit_operand_gpr(JIT_OPERAND_ABI_INT32, JIT_R0));

	jit_reloc_t out1 = jit_beqi(_jit, JIT_R0, 0);
	jit_movr(_jit, JIT_V0, JIT_R0);
	jit_movi(_jit, JIT_R0, 1);

	jit_reloc_t out2 = jit_blei_u(_jit, JIT_V0, 2);
	jit_subi(_jit, JIT_V1, JIT_V0, 1);
	jit_subi(_jit, JIT_V2, JIT_V0, 2);

	jit_calli_1(_jit, entry, jit_operand_gpr(JIT_OPERAND_ABI_INT32, JIT_V1));
	jit_retval(_jit, JIT_V1);

	jit_calli_1(_jit, entry, jit_operand_gpr(JIT_OPERAND_ABI_INT32, JIT_V2));
	jit_retval(_jit, JIT_R0);

	jit_addr(_jit, JIT_R0, JIT_R0, JIT_V1);

	jit_patch_here(_jit, out1);
	jit_patch_here(_jit, out2);
	jit_leave_jit_abi(_jit, 3, 0, frame);
	jit_retr(_jit, JIT_R0);

	size_t size = 0;
	function = jit_end(_jit, &size);

	if (function) {
		ASSERT((*function)(1) == 1);
		ASSERT((*function)(2) == 1);
		ASSERT((*function)(3) == 2);
		ASSERT((*function)(4) == 3);
		ASSERT((*function)(5) == 5);
		ASSERT((*function)(6) == 8);
		ASSERT((*function)(7) == 13);
		ASSERT((*function)(8) == 21);
		ASSERT((*function)(9) == 34);

		ASSERT((*function)(32) == 2178309);
	} else {
		return size;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	return main_compiler(argc, argv, run_test);
}
