/***************************************************************************//**
 * @file
 * @brief Silicon Labs TrustZone IOVEC definitions.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef __SLI_TZ_IOVEC_H__
#define __SLI_TZ_IOVEC_H__

#include <stddef.h>   // size_t

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Maximum number of input and output vectors for a call from NS to S.
 */
#define SLI_TZ_MAX_IOVEC     (6u)

/**
 * \brief Number of elements in array.
 */
#if !defined(IOVEC_LEN)
  #define IOVEC_LEN(arr) ((uint32_t)(sizeof(arr) / sizeof(arr[0])))
#endif

/**
 * A read-only input memory region provided to an RoT Service.
 */
typedef struct sli_tz_invec {
  const void *base;           /*!< the start address of the memory buffer */
  size_t len;                 /*!< the size in bytes                      */
} sli_tz_invec;

/**
 * A writable output memory region provided to an RoT Service.
 */
typedef struct sli_tz_outvec {
  void *base;                 /*!< the start address of the memory buffer */
  size_t len;                 /*!< the size in bytes                      */
} sli_tz_outvec;

#ifdef __cplusplus
}
#endif

#endif /* __SLI_TZ_IOVEC_H__ */
