#include <getopt.h>
#include <stdio.h>

#include "ttt_impl.h"

static void ttt_print_help(const char *name) {
  fprintf(stderr, "Usage: %s [OPTIONS]\n", name);
  fprintf(stderr, "Options:\n");
  fprintf(stderr,
          "  --ttt-verbose=<verbose level>, Verbose level (0, 1, 2, ...), "
          "Default: %d.\n",
          TTT_VERBOSE);
  fprintf(stderr, "  --ttt-help, Prints this help message and exit.\n");
}

static int ttt_parse_opts(ttt_t ttt, int *argc, char ***argv_) {
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
      ttt_error(!end || *end != '\0' || optarg == end, TTT_ERROR_INVALID_INPUT,
                "Invalid string for verbose level: %s\n", optarg);
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

  return TTT_SUCCESS;
}

/**
 * @ingroup ttt_user_api_functions
 *
 * @brief Initialize ttt. Returns a pointer to a newly allocated ttt_t.
 *
 * @param ttt  Pointer to the ttt_t handle which will be initialized.
 * @param argc Pointer to the number of commnad line arguments.
 * @param argv Pointer to the array of command line arguments.
 *
 * @return int
 */
int ttt_init(ttt_t *ttt, int *argc, char **argv[]) {
  ttt_log_init(TTT_VERBOSE);

  ttt_check_ptr(ttt);
  *ttt = ttt_calloc(struct ttt, 1);

  if (argc != NULL && argv != NULL) ttt_check(ttt_parse_opts(*ttt, argc, argv));

  ttt_log_set_type((*ttt)->verbose);
  ttt_info("verbose = %d", (*ttt)->verbose);

  return TTT_SUCCESS;
}

/**
 * @ingroup ttt_user_api_functions
 *
 * @brief Finalize ttt. Frees the memory allocated for the ttt_t
 * returned by ttt_init() and sets the pointer to NULL.
 *
 * @param ttt Pointer to the ttt_t to be freed.
 */
int ttt_finalize(ttt_t *ttt) {
  ttt_check(ttt_log_finalize());

  ttt_check_ptr(ttt);
  ttt_check_ptr2(ttt);
  ttt_free(ttt);

  return TTT_SUCCESS;
}
