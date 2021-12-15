/***************************************************************************//**
 * @file
 * @brief Correlated angle database for asset tags.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef AOA_CR_H
#define AOA_CR_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "aoa_util.h"
#include "aoa_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Type definitions.

/// Initstruct for the module.
typedef struct {
  uint32_t locator_count;       // Locator count in the system.
  uint32_t sequence_id_slots;   // Sequence id slots.
  uint32_t max_sequence_diff;   // Maximum difference from the new sequence id.
} aoa_corr_angles_config_t;

/// Correlated angles structure.
typedef struct aoa_corr_angles_s{
  int32_t sequence;
  int32_t num_angles;
  aoa_angle_t *angles;
  bool *has_angle;
} aoa_corr_angles_t;

// -----------------------------------------------------------------------------
// Public variables.

/// Configuration parameters
extern aoa_corr_angles_config_t aoa_corr_angles_config;

// -----------------------------------------------------------------------------
// Public functions.

/**************************************************************************//**
 * Creates a new database entry
 *
 * @param[in] tag_id Id which connects the stored values to a tag.
 * @param[in] corr_angles_array Pointer to the correlated angles array.
 *
 * @retval SL_STATUS_ALLOCATION_FAILED - Memory allocation failure.
 * @retval SL_STATUS_OK - Entry added.
 *****************************************************************************/
sl_status_t aoa_corr_angles_new(aoa_id_t tag_id,
                                aoa_corr_angles_t **corr_angles_array);

/**************************************************************************//**
 * Returns an entry from the database by the id.
 *
 * @param[in] tag_id id which connects the stored values to a tag.
 * @param[in] corr_angles Correlated angles array.
 *
 * @retval SL_STATUS_NOT_FOUND - Entry not found.
 * @retval SL_STATUS_OK - Entry found.
 *****************************************************************************/
sl_status_t aoa_corr_angles_get_by_id(aoa_id_t tag_id,
                                      aoa_corr_angles_t **corr_angles_array);

/**************************************************************************//**
 * Adds data to the corresponding tag id and slot number.
 *
 * @param[in] corr_angles_array Pointer to the correlated angles array.
 * @param[in] locator_idx Locator which the data came from.
 * @param[in] angle Data to be added.
 * @param[in] angle_slot Slot where the data was added.
 *
 * @retval SL_STATUS_FAIL - Slot number exceeds the maximum that can be stored.
 * @retval SL_STATUS_OK - Data added.
 *****************************************************************************/
sl_status_t aoa_corr_angles_add_data(aoa_corr_angles_t *corr_angles_array,
                                     uint32_t locator_idx,
                                     aoa_angle_t *angle,
                                     uint32_t *angle_slot);

/**************************************************************************//**
 * Cleans up already processed data.
 *
 * @param[in] corr_angles_array Pointer to the correlated angles array.
 * @param[in] cleanup_start_idx Start index for the cleanup.
 *
 * @retval SL_STATUS_FAIL - Start index higher than the slot count.
 * @retval SL_STATUS_OK - Cleanup done.
 *****************************************************************************/
sl_status_t aoa_corr_angles_cleanup(aoa_corr_angles_t *corr_angles_array,
                                    uint32_t cleanup_start_idx);

/**************************************************************************//**
 * Destroys the database and all of its entries.
 *****************************************************************************/
void aoa_corr_angles_destroy(void);

#ifdef __cplusplus
};
#endif

#endif /* AOA_CR_H */
