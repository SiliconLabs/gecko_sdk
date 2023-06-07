/***************************************************************************//**
 * @file  sl_math_mvp.h
 * @brief MVP Math functions.
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
#ifndef SL_MATH_MVP_H
#define SL_MATH_MVP_H

// Utilities
#include "sl_math_mvp_util.h"

// Matrix
#include "sl_math_mvp_complex_matrix_mult.h"
#include "sl_math_mvp_matrix_add.h"
#include "sl_math_mvp_matrix_mult.h"
#include "sl_math_mvp_matrix_scale.h"
#include "sl_math_mvp_matrix_sub.h"
#include "sl_math_mvp_matrix_transpose.h"
#include "sl_math_mvp_matrix_vector_mult.h"

// Vector
#include "sl_math_mvp_complex_vector_conjugate.h"
#include "sl_math_mvp_complex_vector_dot_product.h"
#include "sl_math_mvp_complex_vector_mult.h"
#include "sl_math_mvp_complex_vector_magnitude_squared.h"
#include "sl_math_mvp_vector_abs.h"
#include "sl_math_mvp_vector_add.h"
#include "sl_math_mvp_vector_clamp.h"
#include "sl_math_mvp_vector_clip.h"
#include "sl_math_mvp_vector_copy.h"
#include "sl_math_mvp_vector_dot_product.h"
#include "sl_math_mvp_vector_fill.h"
#include "sl_math_mvp_vector_mult.h"
#include "sl_math_mvp_vector_negate.h"
#include "sl_math_mvp_vector_scale.h"
#include "sl_math_mvp_vector_sub.h"

/* *INDENT-OFF* */
/************ THIS SECTION IS FOR DOCUMENTATION ONLY !**********************//**
 *
 * @defgroup math_mvp_vector Vector functions
 * @defgroup math_mvp_matrix Matrix functions
 *
 * @mainpage Introduction
 * @{

@section math_mvp_background Background
Some of the Silicon Labs parts have included what is called the Matrix Vector
Processor, MVP. The MVP is a hardware accelerator designed to execute certain
operations faster than the CPU. In particular, vector and matrix operatons are
usually good candidates for acceleraton. The purpose with this math
library is to offer functions that utilize the MVP to speed up the operations.

The MVP supports 8 bit integers and 16 bit floating point numbers, and this
library contains only functions that can be accelerated on the MVP.

Similar or identical functions can be found in the
[ARM CMSIS-DSP](https://www.keil.com/pack/doc/CMSIS/DSP/html/index.html)
library.

For more information on the MVP hardware, please refer to the reference manual
for the actual part.

@section math_mvp_memory_alignment Memory alignment
The MVP will read and write to the system memory without using the CPU. When using 16-bit
floating point variables, there are certain rules to follow:
-# Scalar variables (single 16-bit values) must be aligned to an even address; 0, 2, 4, etc.
-# Complex variables (double 16-bit values) must be aligned to a 4-byte word address; 0, 4, 8, etc.

@note Please note that if functions that are working on scalar values get 4-byte
word addresses for all of the function arguments, it will in many cases be able to
process two values pr cycle. That will nearly double the speed of the operation,
and is highly recommended.

@section math_mvp_using_the_library Using the library
The library is delivered as source code. It can easily be used by including the
math_mvp component to the project and just calling the functions.

The library requires that the MVP driver has been initialized by calling the
sli_mvp_init() function. If the project has included the sl_system, this
function will be called automatically, else it hs to be called by the user
application before any of the other mvp math functions are used.

The library is divided into a number of functions in one of the categories:
@li Matrix functions
@li Vector functions

Each of the library functions has a separate header file, but for convenience,
the **sl_math_mvp.h** file contains everything the application needs to use the
library.

@code{.c}
#include "sl_math_mvp.h"

static float16_t input_a[256] SL_ATTRIBUTE_ALIGN(4);
static float16_t input_b[256] SL_ATTRIBUTE_ALIGN(4);
static float16_t output[256] SL_ATTRIBUTE_ALIGN(4);

void example()
{
  sl_status_t status;
  status = sl_math_mvp_vector_fill_f16(input_a, 1.0f, 6);
  ...
  status = sl_math_mvp_vector_add_f16(input_a, input_b, output, 6);
  ...
  sl_math_matrix_init_f16(&matrix_a, 3, 4, input_a);
  sl_math_matrix_init_f16(&matrix_b, 4, 3, input_b);
  sl_math_matrix_init_f16(&matrix_z, 3, 3, output);
  status = sl_math_mvp_matrix_mult_f16(&matrix_a, &matrix_b, &matrix_z);
  ...
}
@endcode

Please take a look at the **math_mvp_demo** example in the GSDK. It shows various examples of how to use the functions.

@section math_mvp_error_handling Error handling
In general all math functions in the library will return one of these
codes defined in **sl_status.h**:
@code{.c}
#define SL_STATUS_OK                 ((sl_status_t)0x0000)  // No error.
#define SL_STATUS_FAIL               ((sl_status_t)0x0001)  // Generic error.
#define SL_STATUS_INVALID_PARAMETER  ((sl_status_t)0x0021)  // Generic invalid argument or consequence of invalid argument.
@endcode

<b>@c SL_STATUS_INVALID_PARAMETER</b> is returned when the call was made with invalid input parameters.

<b>@c SL_STATUS_FAIL</b> is returned when execution on the MVP processor led to unrecoverable errors.

<b>@c SL_STATUS_OK</b> is returned when MVP program execution succeeded. In this case execution may have
generated math exceptions such as overflow, underflow or inifinty etc.

An MVP program can produce these errors/exceptions:
@code{.c}
#define SL_STATUS_COMPUTE_MATH_FAULT       ((sl_status_t)0x1511)   // MATH Critical fault
#define SL_STATUS_COMPUTE_MATH_NAN         ((sl_status_t)0x1512)   // MATH NaN encountered
#define SL_STATUS_COMPUTE_MATH_INFINITY    ((sl_status_t)0x1513)   // MATH Infinity encountered
#define SL_STATUS_COMPUTE_MATH_OVERFLOW    ((sl_status_t)0x1514)   // MATH numeric overflow
#define SL_STATUS_COMPUTE_MATH_UNDERFLOW   ((sl_status_t)0x1515)   // MATH numeric underflow
@endcode

To investigate which (if any) math exceptions occured use:
@code{.c}
sl_status_t sl_math_mvp_get_error(sl_status_t *error_code, char *error_message, uint32_t buffer_length);
@endcode
As several exception may be present, you can call this function repeatedly to retrieve error codes.
The function will return <b>@c SL_STATUS_OK</b> when a valid error code is returned via *error_code, until
<b>@c SL_STATUS_NOT_FOUND</b> is returned.
@code{.c}
void example()
{
  sl_status_t error_code;

  while (sl_math_mvp_get_error(&error_code, NULL, 0) == SL_STATUS_OK) {
    printf("Error code is: %X\n", error_code);
  }
}
@endcode

If you add the **status_string** component to your application, the error function will also return
descriptive error strings for the different exceptions. This might be handy for debugging.
@code{.c}
void example()
{
  char error_string[100];
  sl_status_t error_code;

  while (sl_math_mvp_get_error(&error_code, error_string, sizeof(error_string)) == SL_STATUS_OK) {
    printf("Error code / message is: %X / %s\n", error_code, error_string);
  }
}
@endcode

@note Errors and exceptions will accumulate across calls of MVP Math functions. This means that in many cases
it will be sufficient to check for errors/exceptions after a sequence of MVP Math functions have been executed.
The following function is handy to make sure all errors/exceptions are cleared before commencing on
a long sequence of MVP Math function calls:

@code{.c}
void sl_math_mvp_clear_errors(void);
@endcode

 * @} */

#endif // SL_MATH_MVP_H
