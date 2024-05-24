#if !defined(__LIBTTT_TEST_H__)
#define __LIBTTT_TEST_H__

#include <stdio.h>
#include <stdlib.h>

#include "ttt.h"

#define ttt_test_assert(cond, err)                                             \
  {                                                                            \
    int status = ((cond) != 1);                                                \
    if (status) {                                                              \
      fprintf(stderr, "Test failed in file %s at line %d.\n", __FILE__,        \
              __LINE__);                                                       \
      fflush(stderr);                                                          \
    }                                                                          \
    err |= status;                                                             \
  }

#define ttt_test_check(call, err)                                              \
  {                                                                            \
    int status = (call);                                                       \
    if (status) {                                                              \
      fprintf(stderr, "Test failed in file %s at line %d.\n", __FILE__,        \
              __LINE__);                                                       \
      fflush(stderr);                                                          \
    }                                                                          \
    err |= status;                                                             \
  }

#define ttt_test_calloc(T, n) ((T *)calloc((n), sizeof(T)))

#define ttt_test_realloc(T, ptr, n) ((T *)realloc((ptr), sizeof(T) * (n)))

#define ttt_test_free(p)                                                       \
  { free(*(p)), *(p) = NULL; }

#endif // __LIBTTT_TEST_H__
