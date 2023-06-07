/***************************************************************************//**
 * @file
 * @brief Simple argument parser API definitions
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
#ifndef SIMPLE_ARGPARSE_H
#define SIMPLE_ARGPARSE_H

// -----------------------------------------------------------------------------
// Includes

#include "sl_status.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Macros and Typedefs

/// List of acceptable delitmiters between arguments and options
#define SIMPLE_ARGPARSE_ARGUMENT_DELIMITERS      ",:= "

/// Argument mandatory prefix - DO NOT use this for argument options
#define SIMPLE_ARGPARSE_ARGUMENT_PREFIX          '-'

/// @typedef Pointer to argument-option pair structure
typedef struct argparse_parameter_pair_s   *simple_argparse_parameter_pair_p;

/// @typedef Pointer to argument descriptor structure
typedef struct argparse_descriptor_s       *simple_argparse_descriptor_p;

/// @typedef Pointer to internal simple argparse handle
typedef struct argparse_handle_s           *simple_argparse_handle_p;

/// @typedef Argument-option pair structure
struct argparse_parameter_pair_s{
  char *arg;
  char *opt;
};

/// @typedef Argument-option descriptor structure
struct argparse_descriptor_s{
  char *arg;
  char *valid_options;
};

// -----------------------------------------------------------------------------
// Public Function Declarations

/**************************************************************************//**
 * Init simple argument parser
 * @note: uses malloc, @ref argparse_deinit() must be called after use!
 *
 * @param[in]  descriptor_list Pointer to a valid @ref argparse_descriptor_s
 *                             structure
 * @param[out] handle Pointer to a @ref simple_argparse_handle_p type object instance
 * @return sl_status_t SL_STATUS_OK on success, SL_STATUS_NULL_POINTER if
 *         either descriptor_list or handle is NULL, SL_STATUS_ALLOCATION_FAILED
 *         if allocation on heap doesn't succeed.
 *****************************************************************************/
sl_status_t simple_argparse_init(const simple_argparse_descriptor_p descriptor_list,
                                 simple_argparse_handle_p *handle);

/**************************************************************************//**
 * Deinit simple argument parser
 *
 * @param[in] handle Argparse object handle
 * @return sl_status_t SL_STATUS_OK on success or SL_STATUS_NULL_POINTER if
 *         handle is NULL.
 *****************************************************************************/
sl_status_t simple_argparse_deinit(simple_argparse_handle_p handle);

/**************************************************************************//**
 * Validate full argument string with simple argument parser
 *
 * @param[in] handle Argparse object handle
 * @param[in] str String to validate for known / acceptable key:value pairs
 * @param[out] pResult Array of @ref argparse_parameter_pair_s structures
 * @param[out] result_count Either the number of valid pairs or the index to
 *             the first erroneous data within the input string in case of
 *             validation error
 * @return sl_status_t SL_STATUS_OK on success, various SL_STATUS error codes
 *         otherwise, depending on the error
 * @note: uses malloc during the validation, do not forget to call @ref
 *        argparse_deinit() once at the end of the argparse session!
 *****************************************************************************/
sl_status_t simple_argparse_validate(simple_argparse_handle_p handle,
                                     char *str,
                                     simple_argparse_parameter_pair_p *pResult,
                                     int *result_count);

/**************************************************************************//**
 * Usage (debug) example
 * @code
 #include <stdio.h>
 #include <stdlib.h>
 #include "simple_argparse.h"

   // OPTION ITEMS MUST BE SEPARATED BY ONE AND ONLY ONE OF THE SPECIFIED DELIMITERS!
   static struct argparse_descriptor_s arg_descriptor[] =
   {
    {"-connection", "ip,serial"},   // define whatever key-value pairs you like
    {"-device", ""},                // empty string as option allows anything
    {"-baud", "115200,921600"},
    {"-handshake", "no,ctsrts,hw"}, // more options can be given where it's needed
    {NULL, NULL}
   };

   //========================================================================================
   //                      MAIN
   //========================================================================================
   int main(int argc, char *argv[])
   {
    simple_argparse_parameter_pair_p parsed;
    simple_argparse_handle_p handle;
    int parsed_count;

    char* argv_dbg1 = "-connection:serial -device=COM4 -baud=115200 -handshake:ctsrts";      // valid
    char* argv_dbg2 = "-connection";                                                         // invalid, incomplete connection option
    char* argv_dbg3 = "-connection:serial -device= -baud=115200 -handshake:ctsrts";          // invalid, missing device option
    char* argv_dbg4 = "-connection:serial -device=COM1 -baud=115200 -hand5hake:no";          // invalid, typo (hand5hake)
    char* argv_dbg5 = "-device=\\\\.\\COM10 -connection:serial -handshake:no -baud=115200 "; // valid (note the mixed parameter order)
    char* argv_dbg6 = "-connection:serial -device=\\\\.\\COM10 -baud=11520 -handshake:no";   // invalid, implausible baud rate

    char* argv_dbg = argv_dbg4;

    simple_argparse_init(arg_descriptor, &handle);
    int r = simple_argparse_validate(handle, argv_dbg, &parsed, &parsed_count);

    if (r)
    {
      printf("### Argument parser error: status=%d, \"%s\" \n", r, &argv_dbg[parsed_count]);
      simple_argparse_deinit(handle);
      return -1;
    }
    else
    {
      printf("%d parsed commands:\n", parsed_count);
      size_t i;
      for (i = 0; i < parsed_count; ++i)
      {
        printf("%s : %s\n", parsed[i].arg, parsed[i].opt);
      }
    }

    simple_argparse_deinit(handle);
    return 0;
   }
 * @endcode
 *****************************************************************************/
#ifdef __cplusplus
};
#endif

#endif  // SIMPLE_ARGPARSE_H
