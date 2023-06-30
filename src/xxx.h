#if !defined(__LIBXXX_H__)
#define __LIBXXX_H__

#define XXX_VISIBILITY(mode) __attribute__((visibility(#mode)))

#if defined(__cplusplus)
#define XXX_EXTERN extern "C" XXX_VISIBILITY(default)
#else
#define XXX_EXTERN extern XXX_VISIBILITY(default)
#endif

#if defined(__cplusplus)
#define XXX_INTERN extern "C" XXX_VISIBILITY(hidden)
#else
#define XXX_INTERN extern XXX_VISIBILITY(hidden)
#endif

struct xxx_t;
XXX_EXTERN struct xxx_t *xxx_init(int *argc, char **argv[]);

XXX_EXTERN void xxx_debug(const int verbose, const char *fmt, ...);

XXX_EXTERN void xxx_error(const char *fmt, ...);

XXX_INTERN void xxx_assert_(int cond, const char *fmt, const char *file,
                            const unsigned line);
#define xxx_assert(COND, MSG) xxx_assert_(COND, MSG, __FILE__, __LINE__)

XXX_EXTERN void xxx_finalize(struct xxx_t **xxx);

#endif // __LIBXXX_H__
