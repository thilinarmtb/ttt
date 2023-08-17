#if !defined(__LIBXXX_IMPL_H__)
#define __LIBXXX_IMPL_H__

#define _POSIX_C_SOURCE 200809L

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <xxx.h>

/**
 * @defgroup xxx_internal_api Internal API functions
 *
 * @brief xxx API functions defined in `xxx-impl.h`.
 */

/**
 * xxx handle returned by xxx_init().
 */
struct xxx_t {
  unsigned verbose; /**< Verbosity level. */
};

/**
 * @ingroup xxx_internal_api
 *
 * @brief Allocate memory.
 *
 * @param T Type of the memory to be allocated.
 * @param n Number of elements of type T to be allocated.
 *
 * @return Pointer to the allocated memory.
 */
#define xxx_calloc(T, n) ((T *)calloc(n, sizeof(T)))

XXX_INTERN void xxx_free_(void **ptr);

#define xxx_free(p) xxx_free_((void **)p)

#endif // __LIBXXX_IMPL_H__
