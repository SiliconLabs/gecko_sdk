/*******************************************************************************
 * @file
 * @brief Simple argparse implementation
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
// -----------------------------------------------------------------------------
// Includes

#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "simple_argparse.h"

// -----------------------------------------------------------------------------
// Macros and Typedefs

typedef enum {
  OPTION_NONE,
  OPTION_TYPE_UNDEFINED,
  OPTION_TYPE_KNOWN
} simple_argparse_option_types_t;

struct argparse_handle_s {
  char                               *arguments_copy;
  simple_argparse_descriptor_p       argparse_descriptor;
  size_t                             valid_commands_count;
  simple_argparse_parameter_pair_p   parsed_pairs;
};

// -----------------------------------------------------------------------------
// Static Function Declarations

/******************************************************************************
 * Tokenize string - re-entrant version of C STDLIB strtok()
 * @param[in] str string input to tokenize
 * @param[in] delim list of delimiters
 * @param[in|out] nextp tokenizer context pointer
 *
 * @return Next string token or NULL if str end has been reached.
 *****************************************************************************/
static char *strtok_re(char *str, const char *delim, char **nextp);

/******************************************************************************
 * Check if string is empty
 * @param[in] str string to check whether it's empty or not
 *
 * @return True if empty, false otherwise
 * @note: All whitespace strings will be considered as empty strings!
 *****************************************************************************/
static bool is_empty_string(const char *str);

/******************************************************************************
 * Search for an argument in arguments descriptor list
 * @param[in] hnd simple argparse handle
 * @param[in] arg string to search for in the argument descriptor list
 *
 * @return positive value if the argument is found, negative value otherwise
 *****************************************************************************/
static int search_arg_index(simple_argparse_handle_p hnd, char *const arg);

/******************************************************************************
 * Check if the input string is a valid option for given argument
 * @param[in] hnd simple argparse handle
 * @param[in] index of argument in the argument descriptor list
 *
 * @return True if valid, false otherwise
 *****************************************************************************/
static bool is_option_valid(simple_argparse_handle_p hnd,
                            const int index,
                            const char* const str);
// -----------------------------------------------------------------------------
// Public Function Definitions

/******************************************************************************
 * Init simple argument parser
 *****************************************************************************/
sl_status_t simple_argparse_init(const simple_argparse_descriptor_p descriptor_list, simple_argparse_handle_p *hnd)
{
  sl_status_t result = SL_STATUS_NULL_POINTER;

  if (descriptor_list != NULL && hnd != NULL) {
    result = SL_STATUS_FAIL;
  }
  if (result != SL_STATUS_NULL_POINTER) {
    result = SL_STATUS_ALLOCATION_FAILED;

    if ((*hnd = (simple_argparse_handle_p)malloc(sizeof(struct argparse_handle_s)))) {
      uint32_t max_cmd_count = 0;

      // explore descriptor
      while (descriptor_list[max_cmd_count].arg != NULL) {
        max_cmd_count++;
      }

      (*hnd)->valid_commands_count = max_cmd_count;
      (*hnd)->argparse_descriptor = descriptor_list;

      // allocate memory for maximum number of argparse_parameter_pair_s items
      if (((*hnd)->parsed_pairs = (simple_argparse_parameter_pair_p)malloc(max_cmd_count * sizeof(struct argparse_parameter_pair_s)))) {
        memset((*hnd)->parsed_pairs, 0, max_cmd_count * sizeof(struct argparse_parameter_pair_s));
        result = SL_STATUS_OK;
      } else {
        free(*hnd);
        *hnd = NULL;
      }
    }
  }
  return result;
}

/******************************************************************************
 * Deinit simple argument parser
 *****************************************************************************/
sl_status_t simple_argparse_deinit(simple_argparse_handle_p handle)
{
  sl_status_t result = SL_STATUS_NULL_POINTER;

  if (handle) {
    free(handle->arguments_copy);
    free(handle->parsed_pairs);
    free(handle);
    result = SL_STATUS_OK;
  }

  return result;
}

/******************************************************************************
 * Validate full argument string
 *****************************************************************************/
sl_status_t simple_argparse_validate(simple_argparse_handle_p handle,
                                     char *str,
                                     simple_argparse_parameter_pair_p *pResult,
                                     int *result_count)
{
  sl_status_t result = SL_STATUS_NULL_POINTER;
  uint32_t    arg_index = 0;
  int         current_pair_index = 0; // error indices will start from -1!
  char        *next_token = NULL;
  char        *tokenizer_context;

  // sanity check on usage
  if (handle != NULL && str != NULL && pResult != NULL && result_count != NULL) {
    result = SL_STATUS_OK;
    *result_count = 0;
  }

  // allocate memory for input string copy
  if (result == SL_STATUS_OK) {
    size_t len = strlen(str);
    handle->arguments_copy = malloc(len + 1);

    if (handle->arguments_copy == NULL) {
      result = SL_STATUS_ALLOCATION_FAILED;
    } else {
      memset(handle->arguments_copy, 0, len + 1);
      // copy input string
      memcpy(handle->arguments_copy, str, len);
      // init string tokenizer
      next_token = strtok_re(handle->arguments_copy, SIMPLE_ARGPARSE_ARGUMENT_DELIMITERS, &tokenizer_context);
    }
  }

  while (result == SL_STATUS_OK && next_token != NULL) {
    int descr_index;
    // default key:value pair has undefined value set
    simple_argparse_option_types_t option_type = OPTION_TYPE_UNDEFINED;

    // Check if current token is a valid argument
    if (next_token[0] != SIMPLE_ARGPARSE_ARGUMENT_PREFIX) {
      result = SL_STATUS_INVALID_CONFIGURATION;
      break;
    } else {
      // find argument index if exists in the descriptor, report error otherwise
      descr_index = search_arg_index(handle, next_token);
      if (descr_index < 0) {
        result = SL_STATUS_NOT_FOUND;
        current_pair_index = next_token - str;
        break;
      }
    }

    handle->parsed_pairs[current_pair_index].arg = next_token;

    // Check what argument is required for this command
    if (handle->argparse_descriptor[descr_index].valid_options == NULL) {
      option_type = OPTION_NONE;
    } else if (!is_empty_string(handle->argparse_descriptor[descr_index].valid_options)) {
      option_type = OPTION_TYPE_KNOWN;
    }

    switch (option_type) {
      case OPTION_NONE:
        handle->parsed_pairs[current_pair_index].opt = NULL;
        break;

      case OPTION_TYPE_UNDEFINED:
        // get next token since it is expected to be an undefined value for the current key
        next_token = strtok_re(NULL, SIMPLE_ARGPARSE_ARGUMENT_DELIMITERS, &tokenizer_context);
        // increase the input argument index counter (mostly for error tracking)
        arg_index++;
        // check prefix reserved for arguments and for an empty value
        if (next_token[0] == SIMPLE_ARGPARSE_ARGUMENT_PREFIX) {
          result = SL_STATUS_INVALID_PARAMETER;
          // in error case result_count will contain the index of the first unexpected input argument!
          current_pair_index = next_token - str - 1;
        } else if (is_empty_string(next_token)) {
          result = SL_STATUS_EMPTY;
          current_pair_index = handle->parsed_pairs[current_pair_index].arg - str - 1;
        } else {
          handle->parsed_pairs[current_pair_index].opt = next_token;
        }
        break;

      case OPTION_TYPE_KNOWN:
        // get next token
        next_token = strtok_re(NULL, SIMPLE_ARGPARSE_ARGUMENT_DELIMITERS, &tokenizer_context);
        // increase the input argument index counter
        arg_index++;

        if (is_option_valid(handle, descr_index, next_token)) {
          handle->parsed_pairs[current_pair_index].opt = next_token;
        } else if (is_empty_string(next_token)) {
          result = SL_STATUS_EMPTY;
          current_pair_index = handle->parsed_pairs[current_pair_index].arg - str - 1;
        } else {
          result = SL_STATUS_INVALID_PARAMETER;
          // in error case result_count will contain the index of the first unexpected input argument!
          current_pair_index = next_token - str - 1;
        }
        break;

      default:
        result = SL_STATUS_FAIL;
        break;
    }
    // get next token
    next_token = strtok_re(NULL, SIMPLE_ARGPARSE_ARGUMENT_DELIMITERS, &tokenizer_context);
    // increase counters
    arg_index++;
    current_pair_index++;
  }
  if (result_count != NULL) {
    *result_count = current_pair_index;
  }
  if (pResult != NULL) {
    if (result == SL_STATUS_OK) {
      *pResult = handle->parsed_pairs;
    } else {
      *pResult = NULL;
    }
  }

  (void)arg_index;
  return result;
}

// -----------------------------------------------------------------------------
// Static Function Definitions

/******************************************************************************
 * Tokenize string - re-entrant version of C STDLIB strtok()
 *****************************************************************************/
static char *strtok_re(char *str, const char *delim, char **nextp)
{
  char *ret = NULL;

  if (str == NULL) {
    str = *nextp;
  }

  str += strspn(str, delim);

  if (*str != '\0') {
    ret = str;
    str += strcspn(str, delim);

    if (*str) {
      *str++ = '\0';
    }

    *nextp = str;
  }

  return ret;
}

/******************************************************************************
 * Check if string is empty
 *****************************************************************************/
static bool is_empty_string(const char *str)
{
  bool result = true;   // consider empty by default
  if (str != NULL && strlen(str) != 0) {
    while (isspace((unsigned char)*str)) {
      str++;
    }
    if (*str != 0) {
      result = false; // not empty only if we didn't reach the end of the string
    }
  }

  return result;
}

/******************************************************************************
 * Search for an argument in arguments descriptor list
 *****************************************************************************/
static int search_arg_index(simple_argparse_handle_p hnd, char *const arg)
{
  int result = -1; // not found signal

  for (int i = 0; i < hnd->valid_commands_count; ++i) {
    if (!strcmp(arg, hnd->argparse_descriptor[i].arg)) {
      result = i;
      break;
    }
  }

  return result;
}

/******************************************************************************
 * Check if the input string is a valid option for given argument
 *****************************************************************************/
static bool is_option_valid(simple_argparse_handle_p hnd,
                            const int index,
                            const char *const str)
{
  bool result = false;
  char *context;
  char *token;

  if (str != NULL) {
    char *copy = malloc(strlen(hnd->argparse_descriptor[index].valid_options));
    if (copy != NULL) {
      strcpy(copy, hnd->argparse_descriptor[index].valid_options);
      token = strtok_re(copy, SIMPLE_ARGPARSE_ARGUMENT_DELIMITERS, &context);

      while (token) {
        if (!strcmp(token, str)) {
          result = true;
          break;
        }
        token = strtok_re(NULL, SIMPLE_ARGPARSE_ARGUMENT_DELIMITERS, &context);
      }

      free(copy);
    }
  }

  return result;
}
