#include "test.h"

#include <threads.h>

/* note non-atomic counter! */
size_t num = 0;
long lock_var = 0;
void (*spin_lock)(void);
void (*spin_unlock)(void);

/* arbitrary number, as long as its large enough to likely allow other threads
 * to spawn. */
#define THREAD_INCREMENTS 1000000
static int
loop(void *arg)
{
  for (size_t i = 0; i < THREAD_INCREMENTS; ++i) {
    (*spin_lock)();
    num++;
    (*spin_unlock)();
  }

  return 0;
}

#define NUM_THREADS 10
static void
run_loops()
{
  thrd_t threads[NUM_THREADS];
  for (size_t i = 0; i < NUM_THREADS; ++i)
    ASSERT(thrd_create(&threads[i], loop, NULL) == thrd_success);

  for (size_t i = 0; i < NUM_THREADS; ++i)
    ASSERT(thrd_join(threads[i], NULL) == thrd_success);

  ASSERT(num == NUM_THREADS * THREAD_INCREMENTS);
}

static size_t
run_test(jit_state_t *_jit, uint8_t *arena_base, size_t arena_size)
{
  jit_begin(_jit, arena_base, arena_size);

  /* based on https://rigtorp.se/spinlock/ */
  spin_lock = jit_address(_jit);
  {
    size_t frame = jit_enter_jit_abi(_jit, 0, 0, 0);
    void *do_exchange = jit_address(_jit);
    void *while_load = jit_address(_jit);
    /* do { */
    /* while (atomic_load(lock_var)); */
    jit_movi(_jit, JIT_R1, (jit_imm_t)&lock_var);
    jit_ldr_atomic(_jit, JIT_R0, JIT_R1);
    jit_patch_there(_jit, jit_bnei(_jit, JIT_R0, 0), while_load);
    /* } while (atomic_exchange(lock_var, 1)); */
    jit_movi(_jit, JIT_R0, 1);
    jit_swap_atomic(_jit, JIT_R0, JIT_R1, JIT_R0);
    jit_patch_there(_jit, jit_bnei(_jit, JIT_R0, 0), do_exchange);
    jit_leave_jit_abi(_jit, 0, 0, frame);
    jit_ret(_jit);
  }

  spin_unlock = jit_address(_jit);
  {
    size_t frame = jit_enter_jit_abi(_jit, 0, 0, 0);
    jit_movi(_jit, JIT_R0, 0);
    jit_movi(_jit, JIT_R1, (jit_imm_t)&lock_var);
    jit_str_atomic(_jit, JIT_R1, JIT_R0);
    jit_leave_jit_abi(_jit, 0, 0, frame);
    jit_ret(_jit);
  }

  size_t size;
  void *p = jit_end(_jit, &size);

  if (p)
    run_loops();
  else
    return size;

  return 0;
}

int main(int argc, char *argv[])
{
  return main_compiler(argc, argv, run_test);
}
