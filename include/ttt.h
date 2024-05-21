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

/**
 * @defgroup ttt_error_codes Error codes returned to the user
 *
 * @brief Different error codes returned to the the user by ttt user API
 * calls.
 */

/**
 * @ingroup ttt_error_codes
 *
 * @brief ttt API call was successful.
 */
#define TTT_SUCCESS 0

/**
 * @ingroup ttt_error_codes
 *
 * @brief User input provided to ttt API is invalid.
 */
#define TTT_INVALID_USER_INPUT -128

typedef struct ttt *ttt_t;

/**
 * @defgroup ttt_user_api_functions User API functions
 *
 * @brief User API functions defined in `ttt.h`.
 */

TTT_EXTERN ttt_t ttt_init(int *argc, char **argv[]);

TTT_EXTERN int ttt_finalize(ttt_t *ttt);

#endif // __LIBTTT_H__
