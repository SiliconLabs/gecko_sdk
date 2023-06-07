/***************************************************************************//**
 * @file
 * @brief Math type definitions.
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
#ifndef SL_MATH_TYPES_H
#define SL_MATH_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN
/***************************************************************************//**
 * @addtogroup math_types Data types
 * @{
 ******************************************************************************/

// Define the half precision floating point type, if not defined elsewhere.
// It will default to the 16 bits encoded in binary16 format.
#if !defined(SL_MATH_TYPE_F16)
#define SL_MATH_TYPE_F16 __fp16
#endif

// float16_t is a half precision floating point type.
typedef SL_MATH_TYPE_F16 float16_t;

// Complex float16_t type.
typedef struct {
  float16_t real;
  float16_t imag;
} sl_math_complex_f16_t;

/** @} (end addtogroup math_types) */
/// @endcond

#ifdef __cplusplus
}
#endif

#endif // SL_MATH_TYPES_H
