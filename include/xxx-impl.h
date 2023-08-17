#if !defined(__LIBXXX_IMPL_H__)
#define __LIBXXX_IMPL_H__

#define _POSIX_C_SOURCE 200809L

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <xxx.h>

/**
 * @defgroup xxx_internal_api_macros Internal API macros
 *
 * @brief Internal API macros defined in `xxx-impl.h`.
 */

/**
 * @defgroup xxx_internal_api_functions Internal API functions
 *
 * @brief Internal API functions defined in `xxx-impl.h`.
 */

/**
 * @ingroup xxx_internal_api_macros
 *
 * @def XXX_INTERN
 *
 * @brief Declare a symbol as internal.
 */
#if defined(__cplusplus)
#define XXX_INTERN extern "C" XXX_VISIBILITY(hidden)
#else
#define XXX_INTERN extern XXX_VISIBILITY(hidden)
#endif

/**
 * xxx handle returned by xxx_init().
 */
struct xxx_t {
  unsigned verbose; /**< Verbosity level. */
};

/**
 * @ingroup xxx_internal_api_macros
 *
 * @brief Macro for allocating memory. This macro calls C standard library
 * function `calloc()` and casts the returned pointer as a pointer to type `T`.
 *
 * @param T Type of the memory to be allocated.
 * @param n Number of elements of type T to be allocated.
 *
 * @return Pointer to the allocated memory.
 */
#define xxx_calloc(T, n) ((T *)calloc(n, sizeof(T)))

XXX_INTERN void xxx_free_(void **ptr);

/**
 * @ingroup xxx_internal_api_macros
 *
 * @brief Macro for freeing memory. This macro calls xxx_free_() function.
 *
 * @param p Pointer to the memory to be freed.
 */
#define xxx_free(p) xxx_free_((void **)p)

XXX_INTERN void xxx_debug(int verbose, const char *fmt, ...);

XXX_INTERN void xxx_assert_(int cond, const char *fmt, const char *file,
                            unsigned line);
/**
 * @ingroup xxx_internal_api_macros
 *
 * @brief Macro for asserting a condition. This macro calls xxx_assert_()
 * function.
 *
 * @param COND Condition to be asserted.
 * @param MSG Message to be printed if the condition is not met.
 */
#define xxx_assert(COND, MSG) xxx_assert_(COND, MSG, __FILE__, __LINE__)

XXX_INTERN void xxx_error(const char *fmt, ...);

#endif // __LIBXXX_IMPL_H__
