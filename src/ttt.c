#include <getopt.h>

#include "ttt-impl.h"

static void ttt_print_help(const char *name) {
  printf("Usage: %s [OPTIONS]\n", name);
  printf("Options:\n");
  printf("  --ttt-verbose=<verbose level>, Verbose level (0, 1, 2, ...), "
         "Default: %d.\n",
         TTT_VERBOSE);
  printf("  --ttt-help, Prints this help message and exit.\n");
}

static void ttt_parse_opts(struct ttt_t *ttt, int *argc, char ***argv_) {
  ttt->verbose = TTT_VERBOSE;

  enum ttt_input_t { TTT_INPUT_VERBOSE = 0, TTT_INPUT_HELP = 99 };
  static struct option long_options[] = {
      {"ttt-verbose", optional_argument, 0, TTT_INPUT_VERBOSE},
      {"ttt-help", no_argument, 0, TTT_INPUT_HELP},
      {0, 0, 0, 0}};

  char *end = NULL;
  char **argv = *argv_;
  for (;;) {
    int opt = getopt_long(*argc, argv, "", long_options, NULL);
    if (opt == -1) break;

    switch (opt) {
    case TTT_INPUT_VERBOSE:
      // NOLINTNEXTLINE
      ttt->verbose = strtol(optarg, &end, 10);
      if (!end || *end != '\0' || optarg == end)
        ttt_error("Invalid string for verbose level: %s\n", optarg);
      break;
    case TTT_INPUT_HELP:
      ttt_print_help(argv[0]);
      exit(EXIT_SUCCESS);
      break;
    default:
      ttt_print_help(argv[0]);
      exit(EXIT_FAILURE);
      break;
    }
  }

  // Remove parsed arguments from argv. We just need to update the pointers
  // since command line arguments are not transient and available until the
  // end of the program.
  for (int i = optind; i < *argc; i++) argv[i - optind] = argv[i];
  *argc -= optind;
}

/**
 * @ingroup ttt_user_api_functions
 *
 * @brief Initialize ttt. Returns a pointer to a newly allocated struct ttt_t.
 *
 * @param argc Pointer to the number of commnad line arguments.
 * @param argv Pointer to the array of command line arguments.
 *
 * @return struct ttt_t*
 */
struct ttt_t *ttt_init(int *argc, char **argv[]) {
  struct ttt_t *ttt = ttt_calloc(struct ttt_t, 1);

  ttt_parse_opts(ttt, argc, argv);

  return ttt;
}

/**
 * @ingroup ttt_user_api_functions
 *
 * @brief Finalize ttt. Frees the memory allocated for the struct ttt_t
 * returned by ttt_init() and sets the pointer to NULL.
 *
 * @param ttt Pointer to the struct ttt_t* to be freed.
 */
void ttt_finalize(struct ttt_t **ttt) { ttt_free(ttt); }
