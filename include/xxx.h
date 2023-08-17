#if !defined(__LIBXXX_H__)
#define __LIBXXX_H__

/**
 * @defgroup xxx_user_api_macros User API macros
 *
 * @brief User API macros defined in `xxx.h`.
 */

/**
 * @ingroup xxx_user_api_macros
 *
 * @def XXX_VISIBILITY
 *
 * @brief Set the visibility of a symbol.
 * @param mode Visibility mode (hidden, default, etc.).
 */
#define XXX_VISIBILITY(mode) __attribute__((visibility(#mode)))

/**
 * @ingroup xxx_user_api_macros
 *
 * @def XXX_EXTERN
 *
 * @brief Declare a symbol as external.
 */
#if defined(__cplusplus)
#define XXX_EXTERN extern "C" XXX_VISIBILITY(default)
#else
#define XXX_EXTERN extern XXX_VISIBILITY(default)
#endif

struct xxx_t;

/**
 * @defgroup xxx_user_api_functions User API functions
 *
 * @brief User API functions defined in `xxx.h`.
 */

XXX_EXTERN struct xxx_t *xxx_init(int *argc, char **argv[]);

XXX_EXTERN void xxx_finalize(struct xxx_t **xxx);

#endif // __LIBXXX_H__
