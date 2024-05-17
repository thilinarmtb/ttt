#include "ttt-impl.h"

/**
 * @ingroup ttt_internal_api_functions
 *
 * @brief Function for freeing memory. ttt_free_() calls C standard library
 * function `free()` and sets the pointer to NULL.
 *
 * @param ptr Pointer to the memory address (pointer to a pointer) to be freed.
 */
void ttt_free_(void **ptr) { free(*ptr), *ptr = NULL; }

static ttt_log_type_t ttt_level = TTT_NONE;

/**
 * @ingroup ttt_internal_api_functions
 *
 * @brief Set the verbose level for logging.
 *
 * @param level Verbosity level.
 *
 * @return int
 */
void ttt_log_init(const ttt_log_type_t level) {
  if (level < TTT_NONE || level > TTT_INFO) return;
  ttt_level = level;
}

/**
 * @ingroup ttt_internal_api_functions
 *
 * @brief Print a debug message if the verbosity level is greater than 0.
 *
 * @param verbose Verbosity level.
 * @param fmt Format string.
 * @param ... Format string arguments.
 */
void ttt_log(const ttt_log_type_t verbose, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  if (verbose <= ttt_level) vprintf(fmt, args);
  va_end(args);
}

/**
 * @ingroup ttt_internal_api_functions
 *
 * @brief Assert a condition to be true and print a message if the assertion
 * fails. Use the macro ttt_assert() instead of using this function directly.
 *
 * @param cond Condition to be asserted.
 * @param msg Message to be printed if the assertion fails.
 * @param file Name of the file where the assertion is made.
 * @param line Line number where the assertion is made.
 */
void ttt_assert_(int cond, const char *msg, const char *file,
                 const unsigned line) {
  if (cond) return;
  fprintf(stderr, "%s:%d Assertion failure: %s", file, line, msg);
  exit(EXIT_FAILURE);
}
