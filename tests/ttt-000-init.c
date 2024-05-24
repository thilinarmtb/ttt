#include <stdio.h>

#include "ttt-test.h"

int main(int argc, char **argv) {
  int err = 0;

  // ttt_init() must succeed.
  ttt_t ttt;
  ttt_test_check(ttt_init(&ttt, &argc, &argv), err);

  // ttt_finalize() must succeed.
  ttt_test_check(ttt_finalize(&ttt), err);

  // Finalizing again should return invalid input error.
  ttt_test_assert(ttt_finalize(&ttt) == TTT_INVALID_USER_INPUT, err);

  return err;
}
