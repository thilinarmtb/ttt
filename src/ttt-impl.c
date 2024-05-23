#include <stdarg.h>
#include <stdio.h>

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
  if (verbose > ttt_level) return;

  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  fflush(stderr);
  va_end(args);
}
