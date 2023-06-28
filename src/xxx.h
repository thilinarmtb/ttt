#if !defined(__LIBXXX_H__)
#define __LIBXXX_H__

struct xxx_t;
struct xxx_t *xxx_init(int *argc, char **argv[]);
void xxx_debug(const int verbose, const char *fmt, ...);
void xxx_finalize(struct xxx_t **xxx);

#endif // __LIBXXX_H__
