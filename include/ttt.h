#if !defined(__LIBTTT_H__)
#define __LIBTTT_H__

/**
 * @defgroup ttt_user_api_macros User API macros
 *
 * @brief User API macros defined in `ttt.h`.
 */

/**
 * @ingroup ttt_user_api_macros
 *
 * @def TTT_VISIBILITY
 *
 * @brief Set the visibility of a symbol.
 * @param mode Visibility mode (hidden, default, etc.).
 */
#define TTT_VISIBILITY(mode) __attribute__((visibility(#mode)))

/**
 * @ingroup ttt_user_api_macros
 *
 * @def TTT_EXTERN
 *
 * @brief Declare a symbol as external.
 */
#if defined(__cplusplus)
#define TTT_EXTERN extern "C" TTT_VISIBILITY(default)
#else
#define TTT_EXTERN extern TTT_VISIBILITY(default)
#endif

/**
 * @ingroup ttt_user_api_macros
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

struct ttt_t;

/**
 * @defgroup ttt_user_api_functions User API functions
 *
 * @brief User API functions defined in `ttt.h`.
 */

TTT_EXTERN struct ttt_t *ttt_init(int *argc, char **argv[]);

TTT_EXTERN void ttt_finalize(struct ttt_t **ttt);

#endif // __LIBTTT_H__
