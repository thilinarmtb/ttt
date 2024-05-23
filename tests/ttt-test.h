#if !defined(__LIBTTT_TEST_H__)
#define __LIBTTT_TEST_H__

#include <stdio.h>
#include <stdlib.h>

#include "ttt.h"

inline static void ttt_test_assert_(int cond, const char *file,
                                    const unsigned line) {
  if (cond) return;
  fprintf(stderr, "Assertion failure at %s:%d.\n", file, line);
  exit(EXIT_FAILURE);
}

#define ttt_test_assert(cond) ttt_test_assert_(cond, __FILE__, __LINE__)

#define ttt_test_check(call)                                                   \
  {                                                                            \
    int status = (call);                                                       \
    ttt_test_assert(status == TTT_SUCCESS);                                    \
  }

#endif // __LIBTTT_TEST_H__
