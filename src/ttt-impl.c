#include <stdarg.h>
#include <stdio.h>
#include <string.h>

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

static ttt_log_type_t ttt_type = TTT_NONE;

/**
 * @ingroup ttt_internal_api_functions
 *
 * @brief Set the priority level for logging. All the calls to ttt_log() using
 * a log type with a higher priority than \p type will generate output on
 * stderr.
 *
 * @param type Log type with the lowest priority which will generate output.
 *
 * @return int
 */
void ttt_log_init(const ttt_log_type_t type) {
  if (type < TTT_NONE || type > TTT_INFO) return;
  ttt_type = type;
}

/**
 * @ingroup ttt_internal_api_functions
 *
 * @brief Set the priority level for logging. All the calls to ttt_log() using
 * a log type with a higher priority than \p type will generate output on
 * stderr.
 *
 * @param type Log type with the lowest priority which will generate output.
 *
 * @return int
 */
void ttt_log_set_type(const ttt_log_type_t type) {
  if (type < TTT_NONE || type > TTT_INFO) return;
  ttt_type = type;
}

typedef struct ttt_err_log {
  int   error_id;
  char *msg;
} ttt_err_log_t;

static size_t          ttt_log_size     = 0;
static size_t          ttt_log_capacity = 0;
static ttt_err_log_t **ttt_log_errs     = NULL;

/**
 * @ingroup ttt_internal_api_functions
 *
 * @brief Output a message to the stderr if the log type \p type has a higher
 * priority than the type set during ttt_log_init(). In addition, all the log
 * messages which has a type of TTT_ERROR is stored so that they could be later
 * queried by the user using the integer id returned by ttt_log_(). ttt_log_()
 * returns 0 for all other log types and the respective message is not stored.
 *
 * Users must use ttt_log() macro instead of directly calling ttt_log_().
 *
 * @param type Log type.
 * @param error_id Error number or id (e.g., TTT_INVALID_USER_INPUT).
 * @param fmt_ Format string for the log message.
 * @param ... printf() arguments: file name, line number and other optional
 * arguments if any.
 *
 * @return int
 */
int ttt_log_(const ttt_log_type_t type, const int error_id, const char *fmt_,
             ...) {
  if (type > ttt_type && type != TTT_ERROR) return TTT_SUCCESS;

#define LOG_PREFIX "%s:%d "
#define LOG_SUFFIX "\n"

  const size_t input_fmt_size = strnlen(fmt_, BUFSIZ);
  const size_t prefix_size    = strnlen(LOG_PREFIX, BUFSIZ);
  const size_t suffix_size    = strnlen(LOG_SUFFIX, BUFSIZ);
  const size_t fmt_size       = prefix_size + input_fmt_size + suffix_size + 1;
  char        *fmt            = ttt_calloc(char, fmt_size);

  strncpy(fmt, LOG_PREFIX, prefix_size + 1);
  strncpy(fmt + prefix_size, fmt_, input_fmt_size + 1);
  strncpy(fmt + prefix_size + input_fmt_size, LOG_SUFFIX, suffix_size + 1);

#undef LOG_SUFFIX
#undef LOG_PREFIX

  char    msg[BUFSIZ] = {0};
  va_list args;
  va_start(args, fmt_);
  vsnprintf(msg, BUFSIZ, fmt, args);
  va_end(args);

  ttt_free(&fmt);

  if (type <= ttt_type) fprintf(stderr, "%s", msg), fflush(stderr);
  if (type != TTT_ERROR) return TTT_SUCCESS;

  size_t size = strnlen(msg, BUFSIZ);

  if (ttt_log_size < ttt_log_capacity) goto store_msg;
  // We have ttt_log_size == ttt_log_capacity, so we reallocate memory.
  ttt_log_capacity = (3 * ttt_log_size) / 2 + 1;
  ttt_log_errs = ttt_realloc(ttt_err_log_t *, ttt_log_errs, ttt_log_capacity);

store_msg:
  ttt_log_errs[ttt_log_size]           = ttt_calloc(ttt_err_log_t, 1);
  ttt_log_errs[ttt_log_size]->error_id = error_id;
  ttt_log_errs[ttt_log_size]->msg      = ttt_calloc(char, size + 1);
  strncpy(ttt_log_errs[ttt_log_size]->msg, msg, size);
  ttt_log_size++;

  return ttt_log_size;
}

static int ttt_check_error_index(const int index) {
  if (index == 0 || ttt_log_size == 0) return TTT_SUCCESS;

  ttt_error(index < 0 || index > (int)ttt_log_size, TTT_INVALID_ERROR_INDEX,
            "Error index (%d) passed to ttt_get_error_id() is out of range.",
            index);
  return TTT_SUCCESS;
}

/**
 * @ingroup ttt_internal_api_functions
 *
 * @brief Get the error id given the error index returned by a ttt API call.
 *
 * @param error_id Error id corresponding to the index \p index.
 * @param index Error index returned by a ttt API call.
 *
 * @return int
 */
int ttt_get_error_id(int *error_id, const int index) {
  ttt_check(ttt_check_error_index(index));

  ttt_check_ptr(error_id);

  *error_id = ttt_log_errs[index - 1]->error_id;

  return TTT_SUCCESS;
}

/**
 * @ingroup ttt_internal_api_functions
 *
 * @brief Get the error message given the error index returned by a ttt API
 * call.
 *
 * @param error_msg Error message corresponding to the index \p index.
 * @param index Error index returned by a ttt API call.
 *
 * @return int
 */

int ttt_get_error_message(char **error_msg, const int index) {
  ttt_check(ttt_check_error_index(index));

  ttt_check_ptr(error_msg);

  const size_t size = strnlen(ttt_log_errs[index - 1]->msg, BUFSIZ) + 1;
  *error_msg        = ttt_calloc(char, size);
  strncpy(*error_msg, ttt_log_errs[index - 1]->msg, size);

  return TTT_SUCCESS;
}

/**
 * @ingroup ttt_internal_api_functions
 *
 * @brief Release the memory allocated for the stored error messages and reset
 * the log type used as the priority.
 *
 * @return int
 */
int ttt_log_finalize(void) {
  for (size_t i = 0; i < ttt_log_size; i++)
    ttt_free(&ttt_log_errs[i]->msg), ttt_free(&ttt_log_errs[i]);
  ttt_free(&ttt_log_errs);

  ttt_type     = TTT_NONE;
  ttt_log_size = ttt_log_capacity = 0;

  return TTT_SUCCESS;
}
