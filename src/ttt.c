#include <getopt.h>

#include "ttt-impl.h"

static void ttt_print_help(const char *name) {
  fprintf(stderr, "Usage: %s [OPTIONS]\n", name);
  fprintf(stderr, "Options:\n");
  fprintf(stderr,
          "  --ttt-verbose=<verbose level>, Verbose level (0, 1, 2, ...), "
          "Default: %d.\n",
          TTT_VERBOSE);
  fprintf(stderr, "  --ttt-help, Prints this help message and exit.\n");
}

static void ttt_parse_opts(struct ttt_t *ttt, int *argc, char ***argv_) {
  ttt->verbose = TTT_VERBOSE;
  ttt_log_init(ttt->verbose);

  enum ttt_input_t { TTT_INPUT_VERBOSE = 0, TTT_INPUT_HELP = 99 };
  static struct option long_options[] = {
      {"ttt-verbose", optional_argument, 0, TTT_INPUT_VERBOSE},
      {"ttt-help", no_argument, 0, TTT_INPUT_HELP},
      {0, 0, 0, 0}};

  char  *end  = NULL;
  char **argv = *argv_;
  int    verbose_temp;
  for (;;) {
    int opt = getopt_long(*argc, argv, "", long_options, NULL);
    if (opt == -1) break;

    switch (opt) {
    case TTT_INPUT_VERBOSE:
      // NOLINTNEXTLINE
      verbose_temp = strtol(optarg, &end, 10);
      if (!end || *end != '\0' || optarg == end)
        ttt_log(TTT_ERROR, "Invalid string for verbose level: %s\n", optarg);
      else
        ttt->verbose = verbose_temp;
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
int ttt_finalize(struct ttt_t **ttt) {
  if (ttt == NULL || *ttt == NULL) return TTT_INVALID_USER_INPUT;
  ttt_free(ttt);
  return TTT_SUCCESS;
}
