#include <stdio.h>

#include "ttt-test.h"

int main(int argc, char **argv) {
  // ttt_init() must succeed.
  struct ttt_t *ttt = ttt_init(&argc, &argv);
  ttt_test_assert(ttt != NULL);

  // ttt_finalize() must succeed.
  ttt_test_assert(ttt_finalize(&ttt) == TTT_SUCCESS);

  // Finalizing again should return invalid input error.
  ttt_test_assert(ttt_finalize(&ttt) == TTT_INVALID_USER_INPUT);

  return 0;
}
