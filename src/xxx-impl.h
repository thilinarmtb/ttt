#if !defined(__LIBXXX_IMPL_H__)
#define __LIBXXX_IMPL_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <xxx.h>

#ifdef __cplusplus
extern "C" {
#endif

struct xxx_t {
  unsigned verbose;
};

// Dynamic memory allocation function.
#define xxx_calloc(T, n) (T *)calloc(n, sizeof(T))

// Dynamic memory deallocation function.
void xxx_free_(void **p);
#define xxx_free(p) xxx_free_((void **)p)

#ifdef __cplusplus
}
#endif

#endif // __LIBXXX_IMPL_H__
