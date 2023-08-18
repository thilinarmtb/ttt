#include <getopt.h>
#include <xxx-impl.h>

static void print_help(const char *name) {
  printf("Usage: %s [OPTIONS]\n", name);
  printf("Options:\n");
  printf("  --xxx-verbose=<verbose level>, Verbose level (0, 1, 2, ...).\n");
  printf("  --xxx-help, Prints this help message and exit.\n");
}

static void xxx_parse_opts(struct xxx_t *xxx, int *argc, char ***argv_) {
  xxx->verbose = 0;

  enum xxx_input_t { XXX_INPUT_VERBOSE = 0, XXX_INPUT_HELP = 99 };
  static struct option long_options[] = {
      {"xxx-verbose", optional_argument, 0, XXX_INPUT_VERBOSE},
      {"xxx-help", no_argument, 0, XXX_INPUT_HELP},
      {0, 0, 0, 0}};

  char *end = NULL;
  char **argv = *argv_;
  for (;;) {
    int opt = getopt_long(*argc, argv, "", long_options, NULL);
    if (opt == -1)
      break;

    switch (opt) {
    case XXX_INPUT_VERBOSE:
      // NOLINTNEXTLINE
      xxx->verbose = strtol(optarg, &end, 10);
      if (!end || *end != '\0' || optarg == end)
        xxx_error("Invalid string for verbose level: %s\n", optarg);
      break;
    case XXX_INPUT_HELP:
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

/**
 * @ingroup xxx_user_api_functions
 *
 * @brief Initialize xxx. Returns a pointer to a newly allocated struct xxx_t.
 *
 * @param argc Pointer to the number of commnad line arguments.
 * @param argv Pointer to the array of command line arguments.
 *
 * @return struct xxx_t*
 */
struct xxx_t *xxx_init(int *argc, char **argv[]) {
  struct xxx_t *xxx = xxx_calloc(struct xxx_t, 1);

  xxx_parse_opts(xxx, argc, argv);

  return xxx;
}

/**
 * @ingroup xxx_user_api_functions
 *
 * @brief Finalize xxx. Frees the memory allocated for the struct xxx_t
 * returned by xxx_init() and sets the pointer to NULL.
 *
 * @param xxx Pointer to the struct xxx_t* to be freed.
 */
void xxx_finalize(struct xxx_t **xxx) { xxx_free(xxx); }
