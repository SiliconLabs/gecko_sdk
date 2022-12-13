/***************************************************************************//**
 * @file
 * @brief Silicon Labs TrustZone secure MSC service.
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

#ifndef __SLI_TZ_MSC_VENEERS_H__
#define __SLI_TZ_MSC_VENEERS_H__

#include <stdint.h>
#include <stdbool.h>

#include "sli_tz_util.h"
#include "psa/crypto_types.h"
#include "psa/client.h"
#include "sli_tz_funcs_sids_autogen.h"

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
// Function declarations

uint32_t sli_tz_msc_get_locked(void);

uint32_t sli_tz_msc_set_locked(void);

uint32_t sli_tz_msc_set_unlocked(void);

uint32_t sli_tz_msc_get_readctrl(void);

uint32_t sli_tz_msc_set_readctrl(uint32_t value);

uint32_t sli_tz_msc_set_pagelock(uint32_t page_number);

uint32_t sli_tz_msc_get_pagelock(uint32_t page_number);

uint32_t sli_tz_msc_get_userdata_size(void);

uint32_t sli_tz_msc_get_misclockword(void);

uint32_t sli_tz_msc_set_misclockword(uint32_t value);

uint32_t sli_tz_msc_init(void);

uint32_t sli_tz_msc_deinit(void);

uint32_t sli_tz_msc_erase_page(uint32_t startAddress);

//-------------------------------------
// Full services (IOVEC usage)

int32_t sli_tz_msc_write_word(sli_tz_invec in_vec[],
                              size_t in_len,
                              sli_tz_outvec out_vec[],
                              size_t out_len);

int32_t sli_tz_msc_write_word_dma(sli_tz_invec in_vec[],
                                  size_t in_len,
                                  sli_tz_outvec out_vec[],
                                  size_t out_len);

#ifdef __cplusplus
}
#endif

#endif // __SLI_TZ_MSC_VENEERS_H__
