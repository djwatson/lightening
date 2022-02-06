#include "test.h"

static double f(int32_t a, double b) {
  return b + a;
}

static void
run_test(jit_state_t *j, uint8_t *arena_base, size_t arena_size)
{
  jit_begin(j, arena_base, arena_size);
  size_t align = jit_enter_jit_abi(j, 0, 0, 0);
  jit_load_args_2(j, jit_operand_gpr (JIT_OPERAND_ABI_POINTER, JIT_R0),
		  jit_operand_gpr (JIT_OPERAND_ABI_POINTER, JIT_R1));

  jit_operand_t args[2] = {
    jit_operand_mem(JIT_OPERAND_ABI_INT32, JIT_R0, 0),
    jit_operand_mem(JIT_OPERAND_ABI_DOUBLE, JIT_R1, 0)
  };
  jit_calli(j, f, 2, args);
  jit_retval_d(j, JIT_F0);
  jit_leave_jit_abi(j, 0, 0, align);
  jit_retr_d(j, JIT_F0);

  size_t size = 0;
  void* ret = jit_end(j, &size);

  double (*f)(int32_t*, double*) = ret;

  double d = 22.0f;
  int32_t i = 20;
  ASSERT(f(&i, &d) == 42.0f);
}

int
main (int argc, char *argv[])
{
  return main_helper(argc, argv, run_test);
}
