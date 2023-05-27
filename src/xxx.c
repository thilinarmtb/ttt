#include <getopt.h>
#include <xxx-impl.h>

// Dynamic memory free function.
void xxx_free_(void **p) { free(*p), *p = NULL; }

static void print_help(const char *name) {
  printf("Usage: %s [OPTIONS]\n", name);
  printf("Options:\n");
  printf("  --verbose=<VERBOSITY>, Verbose level. Values: 0, 1, 2, ...\n");
  printf("  --help, Prints this help message.\n");
}

struct xxx_t *xxx_init(int argc, char **argv) {
  static struct option long_options[] = {{"verbose", optional_argument, 0, 10},
                                         {"help", no_argument, 0, 99},
                                         {0, 0, 0, 0}};

  struct xxx_t *xxx = (struct xxx_t *)calloc(1, sizeof(struct xxx_t));
  xxx->verbose = 0;

  for (;;) {
    int c = getopt_long(argc, argv, "", long_options, NULL);
    if (c == -1)
      break;

    switch (c) {
    case 10:
      xxx->verbose = atoi(optarg);
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

  return xxx;
}

void xxx_finalize(struct xxx_t **xxx) { xxx_free(xxx); }
