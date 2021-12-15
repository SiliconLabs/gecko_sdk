/***************************************************************************//**
 * @file
 * @brief Location calculation engine.
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

#ifndef AOA_LOC_H
#define AOA_LOC_H

#include "sl_status.h"
#include "aoa_types.h"
#include "sl_rtl_clib_api.h"
#include "aoa_corr_angles.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Enums.

/// Represents the considered axes.
enum axis_list{
  AXIS_X,
  AXIS_Y,
  AXIS_Z,
  AXIS_COUNT
};

// -----------------------------------------------------------------------------
// Type definitions.

/// Locator struct
typedef struct {
  aoa_id_t id;
  struct sl_rtl_loc_locator_item item;
} aoa_locator_t;

/// Asset tag struct
typedef struct {
  aoa_id_t id;
  uint32_t *loc_id;                         // assigned by RTL lib
  sl_rtl_loc_libitem loc;
  sl_rtl_util_libitem filter[AXIS_COUNT];
  aoa_position_t position;
  void *aoa_state;                         //Only if Angle calculation is needed from IQ report
} aoa_asset_tag_t;

/// Init struct
typedef struct {
  size_t locator_count;
  enum sl_rtl_loc_estimation_mode estimation_mode;
  enum sl_rtl_loc_measurement_validation_method validation_method;
  float estimation_interval_sec;
  bool filtering_enabled;
  float filtering_amount;
  bool is_feedback_enabled;
} aoa_loc_config_t;

// -----------------------------------------------------------------------------
// Public variables.

/// Configuration parameters
extern aoa_loc_config_t aoa_loc_config;

// -----------------------------------------------------------------------------
// Public functions.

/**************************************************************************//**
 * Initializes the expected angle count.
 *****************************************************************************/
void aoa_loc_init_expected_angle_count(void);

/**************************************************************************//**
 * Adds a new locator to the database.
 *
 * @param[in] locator_id ID of the locator.
 * @param[in] item Contains the locator coordinates and orientations.
 * @param[in] locator Pointer to the created entry.
 *
 * @retval SL_STATUS_ALLOCATION_FAILED - Memory allocation failure.
 * @retval SL_STATUS_OK - Entry added.
 *****************************************************************************/
sl_status_t aoa_loc_add_locator(aoa_id_t locator_id,
                                struct sl_rtl_loc_locator_item item,
                                aoa_locator_t **locator);

/**************************************************************************//**
 * Gets a locator from the database.
 *
 * @param[in] locator_id The desired locator id.
 * @param[in] locator_idx Locator entry index in the list.
 * @param[in] locator Pointer to the entry.
 *
 * @retval SL_STATUS_NOT_FOUND - Entry not found.
 * @retval SL_STATUS_OK - Entry found.
 *****************************************************************************/
sl_status_t aoa_loc_get_locator_by_id(aoa_id_t locator_id,
                                      uint32_t *locator_idx,
                                      aoa_locator_t **locator);

/**************************************************************************//**
 * Gets a locator from the database by index.
 *
 * @param[in] locator_idx Locator entry position in the list.
 * @param[in] locator Pointer to the entry.
 *
 * @retval SL_STATUS_NOT_FOUND - Entry not found.
 * @retval SL_STATUS_OK - Entry added.
 *****************************************************************************/
sl_status_t aoa_loc_get_locator_by_index(uint32_t locator_idx,
                                         aoa_locator_t **locator);

/**************************************************************************//**
 * Returns the number of locators on the list.
 *
 * @retval Number of locators
 *****************************************************************************/
size_t aoa_loc_get_number_of_locators(void);

/**************************************************************************//**
 * Adds a new asset tag to the database.
 *
 * @param[in] tag_id Tag id.
 * @param[in] tag Pointer to the created entry.
 *
 * @retval SL_STATUS_ALLOCATION_FAILED - Memory allocation failure.
 * @retval SL_STATUS_FAIL - RTL lib initialization failed.
 * @retval SL_STATUS_OK - Entry added.
 *****************************************************************************/
sl_status_t aoa_loc_add_asset_tag(aoa_id_t tag_id,
                                  aoa_asset_tag_t **tag);

/**************************************************************************//**
 * Gets a tag from the database by its id.
 *
 * @param[in] tag_id The desired tag id.
 * @param[in] tag Pointer to the entry.
 *
 * @retval SL_STATUS_NOT_FOUND - Entry not found.
 * @retval SL_STATUS_OK - Entry found.
 *****************************************************************************/
sl_status_t aoa_loc_get_tag_by_id(aoa_id_t tag_id,
                                  aoa_asset_tag_t **tag);

/**************************************************************************//**
 * Gets a tag from the database by its index.
 *
 * @param[in] index The desired tag index.
 * @param[in] tag Pointer to the entry.
 *
 * @retval SL_STATUS_NOT_FOUND - Entry not found.
 * @retval SL_STATUS_OK - Entry found.
 *****************************************************************************/
sl_status_t aoa_loc_get_tag_by_index(uint32_t index,
                                     aoa_asset_tag_t **tag);

/**************************************************************************//**
 * Calculates the asset tag position and notify the app.
 *
 * @param[in] tag Pointer to the entry.
 * @param[in] start_slot The correlated angle slot to start the calc from.
 * @param[in] corr_angles_array Pointer to the correlated angles array.
 * @param[in] last_updated_slot The slot that was last updated.
 *
 * @retval SL_STATUS_FAIL - Position calculation failed in the RTL lib.
 * @retval SL_STATUS_OK - Calculation was succesful.
 *****************************************************************************/
sl_status_t aoa_loc_calc_position(aoa_asset_tag_t *tag,
                                  int32_t start_slot,
                                  aoa_corr_angles_t *corr_angles_array,
                                  uint32_t *last_updated_slot);

/**************************************************************************//**
 * Destroys the module database.
 *****************************************************************************/
void aoa_loc_destroy(void);

/**************************************************************************//**
 * Position ready callback.
 *
 * @param[in] tag Pointer to the tag entry.
 *****************************************************************************/
void aoa_loc_on_position_ready(aoa_asset_tag_t *tag);

/**************************************************************************//**
 * Correction ready callback.
 *
 * @param[in] tag Pointer to the tag entry.
 * @param[in] sequence Sequence number of the correlated angle.
 * @param[in] locator_id Locator id.
 * @param[in] loc_idx Locator index.
 * @param[in] correction Pointer to the correction structure.
 *****************************************************************************/
void aoa_loc_on_correction_ready(aoa_asset_tag_t *tag,
                                 int32_t sequence,
                                 aoa_id_t locator_id,
                                 uint32_t loc_idx,
                                 aoa_correction_t *correction);

/**************************************************************************//**
 * Angle init callback. Used when angle calculation is needed from IQ report.
 *
 * @param[in] tag Pointer to the tag entry.
 * @param[in] locator_count Number of locators
 *****************************************************************************/
void aoa_loc_angle_init(aoa_asset_tag_t *tag,
                        uint32_t locator_count);

/**************************************************************************//**
 * Angle deinit callback. Used when angle calculation is needed from IQ report.
 *
 * @param[in] tag Pointer to the tag entry.
 * @param[in] locator_count Number of locators
 *****************************************************************************/
void aoa_loc_angle_deinit(aoa_asset_tag_t *tag,
                          uint32_t locator_count);

#ifdef __cplusplus
};
#endif

#endif /* AOA_LOC_H */
