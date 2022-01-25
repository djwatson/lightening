#include "test.h"

static long data[] = { 0x12121212, 0x00000000, 0x34343434 };

static void
run_test(jit_state_t *j, uint8_t *arena_base, size_t arena_size)
{
  jit_begin(j, arena_base, arena_size);
  size_t align = jit_enter_jit_abi(j, 0, 0, 0);
  jit_load_args_3(j, jit_operand_gpr (JIT_OPERAND_ABI_POINTER, JIT_R0),
                  jit_operand_gpr (JIT_OPERAND_ABI_INT32, JIT_R1),
		  jit_operand_gpr (JIT_OPERAND_ABI_INT32, JIT_R2));

  jit_cas_atomic(j, JIT_R0, JIT_R0, JIT_R1, JIT_R2);
  jit_leave_jit_abi(j, 0, 0, align);
  jit_ret(j);

  void (*f)(void*, int32_t, int32_t) = jit_end(j, NULL);

  ASSERT(data[0] == 0x12121212);
  ASSERT(data[1] == 0x00);
  ASSERT(data[2] == 0x34343434);
  f(&data[1], 0, 0x0f0f0f0f);
  ASSERT(data[0] == 0x12121212);
  ASSERT(data[1] == 0x0f0f0f0f);
  ASSERT(data[2] == 0x34343434);
}

int
main (int argc, char *argv[])
{
  return main_helper(argc, argv, run_test);
}
