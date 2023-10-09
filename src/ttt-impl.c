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

/**
 * @ingroup ttt_internal_api_functions
 *
 * @brief Print a debug message if the verbosity level is greater than 0.
 *
 * @param verbose Verbosity level.
 * @param fmt Format string.
 * @param ... Format string arguments.
 */
void ttt_log(int verbose, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  if (verbose > 0)
    vprintf(fmt, args);
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
  if (!cond) {
    fprintf(stderr, "%s:%d Assertion failure: %s", file, line, msg);
    exit(EXIT_FAILURE);
  }
}

/**
 * @ingroup ttt_internal_api_functions
 *
 * @brief Print an error message and exit.
 *
 * @param fmt Format string.
 * @param ... Format string arguments.
 */
void ttt_error(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  int nchars = vfprintf(stderr, fmt, args);
  va_end(args);
  ttt_assert(nchars >= 0, "vfprintf() failed in ttt_error().");
  exit(EXIT_FAILURE);
}
