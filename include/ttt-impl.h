#if !defined(__LIBTTT_IMPL_H__)
#define __LIBTTT_IMPL_H__

#define _POSIX_C_SOURCE 200809L

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ttt.h>

/**
 * @defgroup ttt_internal_api_macros Internal API macros
 *
 * @brief Internal API macros defined in `ttt-impl.h`.
 */

/**
 * @defgroup ttt_internal_api_functions Internal API functions
 *
 * @brief Internal API functions defined in `ttt-impl.h`.
 */

/**
 * @ingroup ttt_internal_api_macros
 *
 * @def TTT_INTERN
 *
 * @brief Declare a symbol as internal.
 */
#if defined(__cplusplus)
#define TTT_INTERN extern "C" TTT_VISIBILITY(hidden)
#else
#define TTT_INTERN extern TTT_VISIBILITY(hidden)
#endif

/**
 * ttt handle returned by ttt_init().
 */
struct ttt_t {
  unsigned verbose; /**< Verbosity level. */
};

/**
 * @ingroup ttt_internal_api_macros
 *
 * @brief Macro for allocating memory. This macro calls C standard library
 * function `calloc()` and casts the returned pointer as a pointer to type `T`.
 *
 * @param T Type of the memory to be allocated.
 * @param n Number of elements of type T to be allocated.
 *
 * @return Pointer to the allocated memory.
 */
#define ttt_calloc(T, n) ((T *)calloc(n, sizeof(T)))

TTT_INTERN void ttt_free_(void **ptr);

/**
 * @ingroup ttt_internal_api_macros
 *
 * @brief Macro for freeing memory. This macro calls ttt_free_() function.
 *
 * @param p Pointer to the memory to be freed.
 */
#define ttt_free(p) ttt_free_((void **)p)

TTT_INTERN void ttt_debug(int verbose, const char *fmt, ...);

TTT_INTERN void ttt_assert_(int cond, const char *fmt, const char *file,
                            unsigned line);
/**
 * @ingroup ttt_internal_api_macros
 *
 * @brief Macro for asserting a condition. This macro calls ttt_assert_()
 * function.
 *
 * @param COND Condition to be asserted.
 * @param MSG Message to be printed if the condition is not met.
 */
#define ttt_assert(COND, MSG) ttt_assert_(COND, MSG, __FILE__, __LINE__)

TTT_INTERN void ttt_error(const char *fmt, ...);

#endif // __LIBTTT_IMPL_H__
