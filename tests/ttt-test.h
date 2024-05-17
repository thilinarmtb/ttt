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

#define ttt_test_assert(COND) ttt_test_assert_(COND, __FILE__, __LINE__)

#endif // __LIBTTT_TEST_H__
