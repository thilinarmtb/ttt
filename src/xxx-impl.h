#if !defined(__LIBXXX_IMPL_H__)
#define __LIBXXX_IMPL_H__

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <xxx.h>

struct xxx_t {
  unsigned verbose;
};

// Dynamic memory allocation macro.
#define xxx_calloc(T, n) ((T *)calloc(n, sizeof(T)))

// Dynamic memory deallocation macro.
XXX_INTERN void xxx_free_(void **p);
#define xxx_free(p) xxx_free_((void **)p)

#endif // __LIBXXX_IMPL_H__
