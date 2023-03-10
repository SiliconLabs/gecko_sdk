/***************************************************************************//**
 * @file
 * @brief Silicon Labs TrustZone non-secure interface dispatch functionality.
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

#ifndef __SLI_TZ_IOVEC_CHECK_H__
#define __SLI_TZ_IOVEC_CHECK_H__

#include "sli_tz_iovec.h"
#include "sl_assert.h"
#include <stdint.h>

#if defined(TZ_SERVICE_PSA_ITS_PRESENT) || defined(TZ_SERVICE_NVM3_PRESENT)
#include "nvm3.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
// Status codes

#define SLI_TZ_IOVEC_OK     (0x55aa55aa)
#define SLI_TZ_IOVEC_ERROR  (0x00000000)

//------------------------------------------------------------------------------
// Macros

/**
 * \brief Validate the number of IOVECs passed.
 */
#define SLI_TZ_IOVEC_ASSERT_N_IOVECS(expected_invecs, expected_outvecs) \
  EFM_ASSERT(in_len == expected_invecs);                                \
  EFM_ASSERT(out_len == expected_outvecs);

/**
 * \brief Validate the number of IOVECs passed.
 */
#define SLI_TZ_IOVEC_ASSERT_STRUCT_SIZE(iovec, expected_struct_type) \
  EFM_ASSERT(iovec.len == sizeof(expected_struct_type));

//------------------------------------------------------------------------------
// Typedefs

// Structure used for temporarily copying iovec parameters from NS client.
typedef struct {
  sli_tz_invec in_vec[SLI_TZ_MAX_IOVEC];
  sli_tz_outvec out_vec[SLI_TZ_MAX_IOVEC];
} sli_tz_iovec_params_t;

//------------------------------------------------------------------------------
// Function declarations

/**
 * \brief Check whether the iovec parameters live in a non-secure region.
 *
 * \return Return /ref SLI_TZ_IOVEC_OK if all the iovec parameters live in a
 *         NonSecure region, otherwise /ref SLI_TZ_IOVEC_ERROR.
 */
uint32_t sli_tz_iovecs_live_in_ns(sli_tz_invec in_vec[],
                                  size_t in_len,
                                  sli_tz_outvec out_vec[],
                                  size_t out_len,
                                  sli_tz_iovec_params_t *iovec_copy);

#if defined(TZ_SERVICE_PSA_ITS_PRESENT) || defined(TZ_SERVICE_NVM3_PRESENT)

/**
 * \brief Check that all pointers passed through nvm3_Init_t structs point to
 *        non-secure memory regions.
 *
 * \return Return /ref SLI_TZ_IOVEC_OK if all the iovec parameters live in a
 *         NonSecure region, otherwise /ref SLI_TZ_IOVEC_ERROR.
 */
uint32_t sli_tz_nvm3_init_struct_points_to_ns(nvm3_Init_t *init_copy);

/**
 * \brief Check that all pointers passed through nvm3_Handle_t structs point to
 *        non-secure memory regions.
 *
 * \return Return /ref SLI_TZ_IOVEC_OK if all the iovec parameters live in a
 *         NonSecure region, otherwise /ref SLI_TZ_IOVEC_ERROR.
 */
uint32_t sli_tz_nvm3_handle_struct_points_to_ns(nvm3_Handle_t *handle_copy);

#endif // TZ_SERVICE_PSA_ITS_PRESENT || TZ_SERVICE_NVM3_PRESENT

#ifdef __cplusplus
}
#endif

#endif // __SLI_TZ_IOVEC_CHECK_H__
