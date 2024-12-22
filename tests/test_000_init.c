#include <stdio.h>

#include "ttt_test.h"

int main(int argc, char **argv) {
  int err = 0;

  // ttt_init() must succeed.
  ttt_t ttt;
  ttt_test_check(ttt_init(&ttt, &argc, &argv), err);

  // ttt_finalize() must succeed.
  ttt_test_check(ttt_finalize(&ttt), err);

  // Finalizing again should generate an invalid user input error.
  int status = ttt_finalize(&ttt);
  ttt_test_assert(status != TTT_SUCCESS, err);

  int error_id = 0;
  ttt_test_check(ttt_get_error_id(&error_id, status), err);
  ttt_test_assert(error_id == TTT_ERROR_INVALID_INPUT, err);

  return err;
}
