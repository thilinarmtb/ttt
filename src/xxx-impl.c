#include <getopt.h>
#include <xxx-impl.h>

// Dynamic memory free function.
void xxx_free_(void **ptr) { free(*ptr), *ptr = NULL; }

static void print_help(const char *name) {
  printf("Usage: %s [OPTIONS]\n", name);
  printf("Options:\n");
  printf("  --xxx-verbose=<verbose level>, Verbose level (0, 1, 2, ...).\n");
  printf("  --xxx-help, Prints this help message and exit.\n");
}

static void xxx_parse_opts(struct xxx_t *xxx, int *argc, char ***argv_) {
  xxx->verbose = 0;

  static struct option long_options[] = {
      {"xxx-verbose", optional_argument, 0, 10},
      {"xxx-help", no_argument, 0, 99},
      {0, 0, 0, 0}};

  char *end = NULL;
  char **argv = *argv_;
  for (;;) {
    int opt = getopt_long(*argc, argv, "", long_options, NULL);
    if (opt == -1)
      break;

    switch (opt) {
    case 10:
      xxx->verbose = strtol(optarg, &end, 10);
      if (!end || *end != '\0' || optarg == end)
        xxx_error("Invalid string for verbose level: %s\n", optarg);
      break;
    case 99:
      print_help(argv[0]);
      exit(EXIT_SUCCESS);
      break;
    default:
      print_help(argv[0]);
      exit(EXIT_FAILURE);
      break;
    }
  }

  // Remove parsed arguments from argv. We just need to update the pointers
  // since command line arguments are not transient and available until the
  // end of the program.
  for (int i = optind; i < *argc; i++)
    argv[i - optind] = argv[i];
  *argc -= optind;
}

struct xxx_t *xxx_init(int *argc, char **argv[]) {
  struct xxx_t *xxx = xxx_calloc(struct xxx_t, 1);

  xxx_parse_opts(xxx, argc, argv);

  return xxx;
}

void xxx_debug(int verbose, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  if (verbose > 0)
    vprintf(fmt, args);
  va_end(args);
}

void xxx_assert_(int cond, const char *msg, const char *file,
                 const unsigned line) {
  if (!cond) {
    printf("%s:%d Assertion failure: %s", file, line, msg);
    exit(EXIT_FAILURE);
  }
}

void xxx_error(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  int nchars = vfprintf(stderr, fmt, args);
  va_end(args);
  xxx_assert(nchars >= 0, "vfprintf failed");
  exit(EXIT_FAILURE);
}

void xxx_finalize(struct xxx_t **xxx) { xxx_free(xxx); }
