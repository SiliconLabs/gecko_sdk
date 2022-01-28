/***************************************************************************//**
 * @file
 * @brief AoA configuration parser.
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

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "aoa_util.h"
#include "aoa_parse.h"

// -----------------------------------------------------------------------------
// Defines

#define CHECK_TYPE(x, t)  if (((x) == NULL) || ((x)->type != (t))) return SL_STATUS_FAIL

// -----------------------------------------------------------------------------
// Private variables

static cJSON *root = NULL;
static int locator_index;

static int allowlist_index;
static int azimuth_mask_index;
static int elevation_mask_index;

// -----------------------------------------------------------------------------
// Private function declarations

static sl_status_t aoa_parse_find_locator_config(cJSON **locator,
                                                 aoa_id_t locator_id);

// -----------------------------------------------------------------------------
// Public function definitions

/**************************************************************************//**
 * Load file into memory.
 *****************************************************************************/
char* aoa_parse_load_file(const char *filename)
{
  FILE *f = NULL;
  long fsize = 0;
  char *buffer = NULL;

  f = fopen(filename, "rb");
  if (f != NULL) {
    fseek(f, 0, SEEK_END);
    fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    buffer = malloc(fsize + 1);
    if (buffer != NULL) {
      fread(buffer, 1, fsize, f);
      buffer[fsize] = 0;
    }
    fclose(f);
  }
  return buffer;
}

/**************************************************************************//**
 * Initialise parser module.
 *****************************************************************************/
sl_status_t aoa_parse_init(const char *config)
{
  // Check preconditions.
  if (NULL != root) {
    return SL_STATUS_ALREADY_INITIALIZED;
  }
  if (NULL == config) {
    return SL_STATUS_NULL_POINTER;
  }

  root = cJSON_Parse(config);
  if (NULL == root) {
    return SL_STATUS_INITIALIZATION;
  }

  locator_index = 0;
  allowlist_index = 0;
  azimuth_mask_index = 0;
  elevation_mask_index = 0;

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Parse positioning config.
 *****************************************************************************/
sl_status_t aoa_parse_positioning(aoa_id_t id)
{
  cJSON *param;

  // Check preconditions.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if (NULL == id) {
    return SL_STATUS_NULL_POINTER;
  }

  param = cJSON_GetObjectItem(root, "id");
  CHECK_TYPE(param, cJSON_String);
  aoa_id_copy(id, param->valuestring);

  return SL_STATUS_OK;
}

#ifdef RTL_LIB
/**************************************************************************//**
 * Parse next item from the locator config list.
 *****************************************************************************/
sl_status_t aoa_parse_locator(aoa_id_t id,
                              struct sl_rtl_loc_locator_item *loc)
{
  cJSON *array;
  cJSON *item;
  cJSON *param;
  cJSON *subparam;
  uint8_t address[ADR_LEN];
  uint8_t address_type;

  // Check preconditions.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if ((NULL == id) || (NULL == loc)) {
    return SL_STATUS_NULL_POINTER;
  }

  array = cJSON_GetObjectItem(root, "locators");
  CHECK_TYPE(array, cJSON_Array);
  // Check if locator index is valid.
  if (locator_index >= cJSON_GetArraySize(array)) {
    return SL_STATUS_NOT_FOUND;
  }
  // Get next locator element from the array.
  item = cJSON_GetArrayItem(array, locator_index);
  CHECK_TYPE(item, cJSON_Object);

  // Parse locator ID.
  param = cJSON_GetObjectItem(item, "id");
  CHECK_TYPE(param, cJSON_String);
  aoa_id_copy(id, param->valuestring);

  // Convert the id to address and back. This will take care about the case.
  aoa_id_to_address(id, address, &address_type);
  aoa_address_to_id(address, address_type, id);

  // Parse position.
  param = cJSON_GetObjectItem(item, "coordinate");
  CHECK_TYPE(param, cJSON_Object);
  subparam = cJSON_GetObjectItem(param, "x");
  CHECK_TYPE(subparam, cJSON_Number);
  loc->coordinate_x = (float)subparam->valuedouble;
  subparam = cJSON_GetObjectItem(param, "y");
  CHECK_TYPE(subparam, cJSON_Number);
  loc->coordinate_y = (float)subparam->valuedouble;
  subparam = cJSON_GetObjectItem(param, "z");
  CHECK_TYPE(subparam, cJSON_Number);
  loc->coordinate_z = (float)subparam->valuedouble;

  // Parse orientation.
  param = cJSON_GetObjectItem(item, "orientation");
  CHECK_TYPE(param, cJSON_Object);
  subparam = cJSON_GetObjectItem(param, "x");
  CHECK_TYPE(subparam, cJSON_Number);
  loc->orientation_x_axis_degrees = (float)subparam->valuedouble;
  subparam = cJSON_GetObjectItem(param, "y");
  CHECK_TYPE(subparam, cJSON_Number);
  loc->orientation_y_axis_degrees = (float)subparam->valuedouble;
  subparam = cJSON_GetObjectItem(param, "z");
  CHECK_TYPE(subparam, cJSON_Number);
  loc->orientation_z_axis_degrees = (float)subparam->valuedouble;

  // Increment locator index.
  ++locator_index;

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Parse AoX mode.
 *****************************************************************************/
sl_status_t aoa_parse_aox_mode(enum sl_rtl_aox_mode *aox_mode,
                               aoa_id_t locator_id)
{
  cJSON *param;
  cJSON *locator;
  sl_status_t sc;

  // Check preconditions.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if (NULL == aox_mode) {
    return SL_STATUS_NULL_POINTER;
  }

  // Check for locator in positioning config
  sc = aoa_parse_find_locator_config(&locator, locator_id);
  if (sc != SL_STATUS_OK) {
    // Try to parse as single locator config
    locator = root;
  }

  // Try parse locator specific config
  param = cJSON_GetObjectItem(locator, "aoxMode");
  if (NULL == param) {
    return SL_STATUS_NOT_FOUND;
  }
  CHECK_TYPE(param, cJSON_String);

  if (strcmp(param->valuestring,
             "SL_RTL_AOX_MODE_ONE_SHOT_BASIC") == 0) {
    *aox_mode = SL_RTL_AOX_MODE_ONE_SHOT_BASIC;
  } else if (strcmp(param->valuestring,
                    "SL_RTL_AOX_MODE_ONE_SHOT_BASIC_LIGHTWEIGHT") == 0) {
    *aox_mode = SL_RTL_AOX_MODE_ONE_SHOT_BASIC_LIGHTWEIGHT;
  } else if (strcmp(param->valuestring,
                    "SL_RTL_AOX_MODE_ONE_SHOT_FAST_RESPONSE") == 0) {
    *aox_mode = SL_RTL_AOX_MODE_ONE_SHOT_FAST_RESPONSE;
  } else if (strcmp(param->valuestring,
                    "SL_RTL_AOX_MODE_ONE_SHOT_HIGH_ACCURACY") == 0) {
    *aox_mode = SL_RTL_AOX_MODE_ONE_SHOT_HIGH_ACCURACY;
  } else if (strcmp(param->valuestring,
                    "SL_RTL_AOX_MODE_ONE_SHOT_BASIC_AZIMUTH_ONLY") == 0) {
    *aox_mode = SL_RTL_AOX_MODE_ONE_SHOT_BASIC_AZIMUTH_ONLY;
  } else if (strcmp(param->valuestring,
                    "SL_RTL_AOX_MODE_ONE_SHOT_FAST_RESPONSE_AZIMUTH_ONLY") == 0) {
    *aox_mode = SL_RTL_AOX_MODE_ONE_SHOT_FAST_RESPONSE_AZIMUTH_ONLY;
  } else if (strcmp(param->valuestring,
                    "SL_RTL_AOX_MODE_ONE_SHOT_HIGH_ACCURACY_AZIMUTH_ONLY") == 0) {
    *aox_mode = SL_RTL_AOX_MODE_ONE_SHOT_HIGH_ACCURACY_AZIMUTH_ONLY;
  } else if (strcmp(param->valuestring,
                    "SL_RTL_AOX_MODE_REAL_TIME_FAST_RESPONSE") == 0) {
    *aox_mode = SL_RTL_AOX_MODE_REAL_TIME_FAST_RESPONSE;
  } else if (strcmp(param->valuestring,
                    "SL_RTL_AOX_MODE_REAL_TIME_BASIC") == 0) {
    *aox_mode = SL_RTL_AOX_MODE_REAL_TIME_BASIC;
  } else if (strcmp(param->valuestring,
                    "SL_RTL_AOX_MODE_REAL_TIME_HIGH_ACCURACY") == 0) {
    *aox_mode = SL_RTL_AOX_MODE_REAL_TIME_HIGH_ACCURACY;
  } else {
    return SL_STATUS_INVALID_CONFIGURATION;
  }

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Parse Antenna mode.
 *****************************************************************************/
sl_status_t aoa_parse_antenna_mode(enum sl_rtl_aox_array_type *antenna_mode,
                                   aoa_id_t locator_id)
{
  cJSON *param;
  cJSON *locator;
  sl_status_t sc;

  // Check preconditions.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if (NULL == antenna_mode) {
    return SL_STATUS_NULL_POINTER;
  }

  // Check for locator in positioning config
  sc = aoa_parse_find_locator_config(&locator, locator_id);
  if (sc != SL_STATUS_OK) {
    // Try to parse as single locator config
    locator = root;
  }

  // Try parse locator specific config
  param = cJSON_GetObjectItem(locator, "antennaMode");
  if (NULL == param) {
    return SL_STATUS_NOT_FOUND;
  }
  CHECK_TYPE(param, cJSON_String);

  if (strcmp(param->valuestring,
             "SL_RTL_AOX_ARRAY_TYPE_4x4_URA") == 0) {
    *antenna_mode = SL_RTL_AOX_ARRAY_TYPE_4x4_URA;
  } else if (strcmp(param->valuestring,
                    "SL_RTL_AOX_ARRAY_TYPE_3x3_URA") == 0) {
    *antenna_mode = SL_RTL_AOX_ARRAY_TYPE_3x3_URA;
  } else if (strcmp(param->valuestring,
                    "SL_RTL_AOX_ARRAY_TYPE_1x4_ULA") == 0) {
    *antenna_mode = SL_RTL_AOX_ARRAY_TYPE_1x4_ULA;
  } else if (strcmp(param->valuestring,
                    "SL_RTL_AOX_ARRAY_TYPE_4x4_DP_URA") == 0) {
    *antenna_mode = SL_RTL_AOX_ARRAY_TYPE_4x4_DP_URA;
  } else if (strcmp(param->valuestring,
                    "SL_RTL_AOX_ARRAY_TYPE_COREHW_15x15_DP") == 0) {
    *antenna_mode = SL_RTL_AOX_ARRAY_TYPE_COREHW_15x15_DP;
  } else if (strcmp(param->valuestring,
                    "SL_RTL_AOX_ARRAY_TYPE_COREHW_12x12_DP") == 0) {
    *antenna_mode = SL_RTL_AOX_ARRAY_TYPE_COREHW_12x12_DP;
  } else {
    return SL_STATUS_INVALID_CONFIGURATION;
  }

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Parse location estimation mode.
 *****************************************************************************/
sl_status_t aoa_parse_loc_estimation_mode(enum sl_rtl_loc_estimation_mode *estimation_mode)
{
  cJSON *param;

  // Check preconditions.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if (NULL == estimation_mode) {
    return SL_STATUS_NULL_POINTER;
  }

  param = cJSON_GetObjectItem(root, "estimationModeLocation");
  if (NULL == param) {
    return SL_STATUS_NOT_FOUND;
  }

  if (strcmp(param->valuestring,
             "SL_RTL_LOC_ESTIMATION_MODE_THREE_DIM_FAST_RESPONSE") == 0) {
    *estimation_mode = SL_RTL_LOC_ESTIMATION_MODE_THREE_DIM_FAST_RESPONSE;
  } else if (strcmp(param->valuestring,
                    "SL_RTL_LOC_ESTIMATION_MODE_THREE_DIM_HIGH_ACCURACY") == 0) {
    *estimation_mode = SL_RTL_LOC_ESTIMATION_MODE_THREE_DIM_HIGH_ACCURACY;
  } else {
    return SL_STATUS_INVALID_CONFIGURATION;
  }

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Parse location validation mode.
 *****************************************************************************/
sl_status_t aoa_parse_loc_validation_mode(enum sl_rtl_loc_measurement_validation_method *validation_mode)
{
  cJSON *param;

  // Check preconditions.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if (NULL == validation_mode) {
    return SL_STATUS_NULL_POINTER;
  }

  param = cJSON_GetObjectItem(root, "validationModeLocation");
  if (NULL == param) {
    return SL_STATUS_NOT_FOUND;
  }

  if (strcmp(param->valuestring,
             "SL_RTL_LOC_MEASUREMENT_VALIDATION_MINIMUM") == 0) {
    *validation_mode = SL_RTL_LOC_MEASUREMENT_VALIDATION_MINIMUM;
  } else if (strcmp(param->valuestring,
                    "SL_RTL_LOC_MEASUREMENT_VALIDATION_MEDIUM") == 0) {
    *validation_mode = SL_RTL_LOC_MEASUREMENT_VALIDATION_MEDIUM;
  } else if (strcmp(param->valuestring,
                    "SL_RTL_LOC_MEASUREMENT_VALIDATION_FULL") == 0) {
    *validation_mode = SL_RTL_LOC_MEASUREMENT_VALIDATION_FULL;
  } else {
    return SL_STATUS_INVALID_CONFIGURATION;
  }

  return SL_STATUS_OK;
}

#endif //RTL_LIB

/**************************************************************************//**
 * Parse float configuration.
 *****************************************************************************/
sl_status_t aoa_parse_float_config(float *config_value,
                                   char *config_name)
{
  cJSON *param;

  // Check preconditions.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if (NULL == config_value) {
    return SL_STATUS_NULL_POINTER;
  }

  param = cJSON_GetObjectItem(root, config_name);
  if (NULL == param) {
    return SL_STATUS_NOT_FOUND;
  }
  CHECK_TYPE(param, cJSON_Number);

  *config_value = param->valuedouble;

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Parse bool configuration.
 *****************************************************************************/
sl_status_t aoa_parse_bool_config(bool *config_value,
                                  char *config_name)
{
  cJSON *param;

  // Check preconditions.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if (NULL == config_value) {
    return SL_STATUS_NULL_POINTER;
  }

  param = cJSON_GetObjectItem(root, config_name);
  if (NULL == param) {
    return SL_STATUS_NOT_FOUND;
  }

  if (param->type == cJSON_False) {
    *config_value = false;
  } else if (param->type == cJSON_True) {
    *config_value = true;
  } else {
    return SL_STATUS_INVALID_CONFIGURATION;
  }

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Check if a config exists in the JSON.
 *****************************************************************************/
sl_status_t aoa_parse_check_config_exist(char *config_name,
                                         aoa_id_t locator_id)
{
  cJSON *array;
  cJSON *locator;
  sl_status_t sc;

  // Check for locator in positioning config
  sc = aoa_parse_find_locator_config(&locator, locator_id);
  if (sc != SL_STATUS_OK) {
    // Try to parse as single locator config
    locator = root;
  }

  // Try parse locator specific config
  array = cJSON_GetObjectItem(locator, config_name);
  if (NULL == array) {
    return SL_STATUS_NOT_FOUND;
  }

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Parse uint32 config.
 *****************************************************************************/
sl_status_t aoa_parse_uint32_config(uint32_t *config_value,
                                    char *config_name)
{
  cJSON *param;

  // Check preconditions.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if (NULL == config_value) {
    return SL_STATUS_NULL_POINTER;
  }

  // Try parse locator specific config
  param = cJSON_GetObjectItem(root, config_name);
  if (NULL == param) {
    return SL_STATUS_NOT_FOUND;
  }
  CHECK_TYPE(param, cJSON_Number);

  *config_value = param->valueint;

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Parse azimuth angle mask configuration.
 *****************************************************************************/
sl_status_t aoa_parse_azimuth(float *min, float *max, aoa_id_t locator_id)
{
  cJSON *array;
  cJSON *param;
  cJSON *subparam;
  cJSON *locator;
  sl_status_t sc;

  // Check preconditions.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if ((NULL == min) || (NULL == max)) {
    return SL_STATUS_NULL_POINTER;
  }

  // Check for locator in positioning config
  sc = aoa_parse_find_locator_config(&locator, locator_id);
  if (sc != SL_STATUS_OK) {
    // Try to parse as single locator config
    locator = root;
  }

  // Try parse locator specific config
  array = cJSON_GetObjectItem(locator, "azimuthMask");
  if (NULL == array) {
    return SL_STATUS_NOT_FOUND;
  }

  // Check if azimuth mask index is valid.
  if (azimuth_mask_index >= cJSON_GetArraySize(array)) {
    return SL_STATUS_NOT_FOUND;
  }

  // Get next azimuth mask from the array.
  param = cJSON_GetArrayItem(array, azimuth_mask_index);

  subparam = cJSON_GetObjectItem(param, "min");
  CHECK_TYPE(subparam, cJSON_Number);
  *min = (float)subparam->valuedouble;
  subparam = cJSON_GetObjectItem(param, "max");
  CHECK_TYPE(subparam, cJSON_Number);
  *max = (float)subparam->valuedouble;

  // Increment index.
  ++azimuth_mask_index;

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Parse elevation angle mask configuration.
 *****************************************************************************/
sl_status_t aoa_parse_elevation(float *min, float *max, aoa_id_t locator_id)
{
  cJSON *array;
  cJSON *param;
  cJSON *subparam;
  cJSON *locator;
  sl_status_t sc;

  // Check preconditions.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if ((NULL == min) || (NULL == max)) {
    return SL_STATUS_NULL_POINTER;
  }

  // Check for locator in positioning config
  sc = aoa_parse_find_locator_config(&locator, locator_id);
  if (sc != SL_STATUS_OK) {
    // Try to parse as single locator config
    locator = root;
  }

  // Try parse locator specific config
  array = cJSON_GetObjectItem(locator, "elevationMask");
  if (NULL == array) {
    return SL_STATUS_NOT_FOUND;
  }

  // Check if elevation mask index is valid.
  if (elevation_mask_index >= cJSON_GetArraySize(array)) {
    return SL_STATUS_NOT_FOUND;
  }

  // Get next elevation mask from the array.
  param = cJSON_GetArrayItem(array, elevation_mask_index);

  subparam = cJSON_GetObjectItem(param, "min");
  CHECK_TYPE(subparam, cJSON_Number);
  *min = (float)subparam->valuedouble;
  subparam = cJSON_GetObjectItem(param, "max");
  CHECK_TYPE(subparam, cJSON_Number);
  *max = (float)subparam->valuedouble;

  // Increment index.
  ++elevation_mask_index;

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Parse next item from the allowlist.
 *****************************************************************************/
sl_status_t aoa_parse_allowlist(uint8_t address[ADR_LEN],
                                uint8_t *address_type,
                                aoa_id_t locator_id)
{
  cJSON *array;
  cJSON *param;
  cJSON *locator;
  sl_status_t sc;

  // Check preconditions.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if (NULL == address || NULL == address_type) {
    return SL_STATUS_NULL_POINTER;
  }

  // Check for locator in positioning config
  sc = aoa_parse_find_locator_config(&locator, locator_id);
  if (sc != SL_STATUS_OK) {
    // Try to parse as single locator config
    locator = root;
  }

  // Try parse locator specific config
  array = cJSON_GetObjectItem(locator, "allowlist");
  if (NULL == array) {
    return SL_STATUS_NOT_FOUND;
  }

  // Check if allowlist index is valid.
  if (allowlist_index >= cJSON_GetArraySize(array)) {
    return SL_STATUS_NOT_FOUND;
  }
  // Get next allowlist element from the array.
  param = cJSON_GetArrayItem(array, allowlist_index);
  CHECK_TYPE(param, cJSON_String);
  // Convert the id to address. This will take care about the case.
  aoa_id_to_address(param->valuestring, address, address_type);

  // Increment allowlist index.
  ++allowlist_index;

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Parse antenna array.
 *****************************************************************************/
sl_status_t aoa_parse_antenna_array(uint8_t **antenna_array,
                                    uint8_t *array_length,
                                    aoa_id_t locator_id)
{
  cJSON *array;
  cJSON *param;
  cJSON *locator;
  sl_status_t sc;
  int i = 0;
  int array_size = 0;

  // Check preconditions.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if ((NULL == antenna_array) || (NULL == array_length)) {
    return SL_STATUS_NULL_POINTER;
  }

  // Check for locator in positioning config
  sc = aoa_parse_find_locator_config(&locator, locator_id);
  if (sc != SL_STATUS_OK) {
    // Try to parse as single locator config
    locator = root;
  }

  // Try parse locator specific config
  array = cJSON_GetObjectItem(locator, "antennaArray");
  if (NULL == array) {
    return SL_STATUS_NOT_FOUND;
  }
  CHECK_TYPE(array, cJSON_Array);

  array_size = cJSON_GetArraySize(array);

  *antenna_array  = realloc(*antenna_array, array_size * sizeof(uint8_t));

  while (i < array_size) {
    param = cJSON_GetArrayItem(array, i);
    (*antenna_array)[i] = param->valueint;
    i++;
  }
  *array_length = (uint8_t)array_size;

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Parse angle filtering configuration.
 *****************************************************************************/
sl_status_t aoa_parse_angle_filtering(bool *filtering_enabled,
                                      aoa_id_t locator_id)
{
  cJSON *param;
  cJSON *locator;
  sl_status_t sc;

  // Check preconditions.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if (NULL == filtering_enabled) {
    return SL_STATUS_NULL_POINTER;
  }

  // Check for locator in positioning config
  sc = aoa_parse_find_locator_config(&locator, locator_id);
  if (sc != SL_STATUS_OK) {
    //Try to parse as single locator config
    locator = root;
  }

  // Try parse locator specific config
  param = cJSON_GetObjectItem(locator, "angleFiltering");
  if (NULL == param) {
    return SL_STATUS_NOT_FOUND;
  }

  if (param->type == cJSON_False) {
    *filtering_enabled = false;
  } else if (param->type == cJSON_True) {
    *filtering_enabled = true;
  } else {
    return SL_STATUS_FAIL;
  }

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Parse angle filtering weight configuration.
 *****************************************************************************/
sl_status_t aoa_parse_angle_filtering_weight(float *filtering_weight,
                                             aoa_id_t locator_id)
{
  cJSON *param;
  cJSON *locator;
  sl_status_t sc;

  // Check preconditions.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if (NULL == filtering_weight) {
    return SL_STATUS_NULL_POINTER;
  }

  // Check for locator in positioning config
  sc = aoa_parse_find_locator_config(&locator, locator_id);
  if (sc != SL_STATUS_OK) {
    // Try to parse as single locator config
    locator = root;
  }

  // Try parse locator specific config
  param = cJSON_GetObjectItem(locator, "angleFilteringWeight");
  if (NULL == param) {
    return SL_STATUS_NOT_FOUND;
  }
  CHECK_TYPE(param, cJSON_Number);

  *filtering_weight = param->valuedouble;

  return SL_STATUS_OK;
}

#ifdef AOA_CTE
/**************************************************************************//**
 * Parse cte mode configuration.
 *****************************************************************************/
sl_status_t aoa_parse_cte_mode(aoa_cte_type_t *cte_mode, aoa_id_t locator_id)
{
  cJSON *param;
  cJSON *locator;
  sl_status_t sc;

  // Check preconditions.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if (NULL == cte_mode) {
    return SL_STATUS_NULL_POINTER;
  }

  // Check for locator in positioning config
  sc = aoa_parse_find_locator_config(&locator, locator_id);
  if (sc != SL_STATUS_OK) {
    // Try to parse as single locator config
    locator = root;
  }

  // Try parse locator specific config
  param = cJSON_GetObjectItem(locator, "cteMode");
  if (NULL == param) {
    return SL_STATUS_NOT_FOUND;
  }
  CHECK_TYPE(param, cJSON_String);

  if (strcmp(param->valuestring, "CONN") == 0) {
    *cte_mode = AOA_CTE_TYPE_CONN;
  } else if (strcmp(param->valuestring, "CONNLESS") == 0) {
    *cte_mode = AOA_CTE_TYPE_CONN_LESS;
  } else if (strcmp(param->valuestring, "SILABS") == 0) {
    *cte_mode = AOA_CTE_TYPE_SILABS;
  } else {
    return SL_STATUS_INVALID_CONFIGURATION;
  }

  return SL_STATUS_OK;
}
#endif

/**************************************************************************//**
 * Parse cte sampling interval configuration.
 *****************************************************************************/
sl_status_t aoa_parse_simple_config(uint16_t *config_value,
                                    char *config_name,
                                    aoa_id_t locator_id)
{
  cJSON *param;
  cJSON *locator;
  sl_status_t sc;

  // Check preconditions.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if (NULL == config_value) {
    return SL_STATUS_NULL_POINTER;
  }

  // Check for locator in positioning config
  sc = aoa_parse_find_locator_config(&locator, locator_id);
  if (sc != SL_STATUS_OK) {
    // Try to parse as single locator config
    locator = root;
  }

  // Try parse locator specific config
  param = cJSON_GetObjectItem(locator, config_name);
  if (NULL == param) {
    return SL_STATUS_NOT_FOUND;
  }
  CHECK_TYPE(param, cJSON_Number);

  *config_value = param->valueint;

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Parse report mode configuration.
 *****************************************************************************/
sl_status_t aoa_parse_report_mode(aoa_report_mode_t *report_mode,
                                  aoa_id_t locator_id)
{
  cJSON *param;
  cJSON *locator;
  sl_status_t sc;

  // Check preconditions.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if (NULL == report_mode) {
    return SL_STATUS_NULL_POINTER;
  }

  // Check for locator in positioning config
  sc = aoa_parse_find_locator_config(&locator, locator_id);
  if (sc != SL_STATUS_OK) {
    // Try to parse as single locator config
    locator = root;
  }

  // Try parse locator specific config
  param = cJSON_GetObjectItem(locator, "reportMode");
  if (NULL == param) {
    return SL_STATUS_NOT_FOUND;
  }
  CHECK_TYPE(param, cJSON_String);

  if (strcmp(param->valuestring, "ANGLE") == 0) {
    *report_mode = ANGLE;
  } else if (strcmp(param->valuestring, "IQREPORT") == 0) {
    *report_mode = IQ_REPORT;
  } else {
    return SL_STATUS_INVALID_CONFIGURATION;
  }

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Deinitialise parser module.
 *****************************************************************************/
sl_status_t aoa_parse_deinit(void)
{
  // Check precondition.
  if (NULL == root) {
    return SL_STATUS_NOT_INITIALIZED;
  }

  cJSON_Delete(root);
  root = NULL;

  return SL_STATUS_OK;
}

// -----------------------------------------------------------------------------
// Private function definitions

/**************************************************************************//**
 * Checking for a locator by id
 *****************************************************************************/
static sl_status_t aoa_parse_find_locator_config(cJSON **locator,
                                                 aoa_id_t locator_id)
{
  aoa_id_t id_json;
  cJSON *param;
  cJSON *array;
  cJSON *item;
  uint32_t i = 0;

  array = cJSON_GetObjectItem(root, "locators");
  CHECK_TYPE(array, cJSON_Array);
  //Check if array of locator configs present
  if (NULL == array) {
    return SL_STATUS_NOT_FOUND;
  }

  //Check for the locator
  while (i <= cJSON_GetArraySize(array)) {
    // Get next locator element from the array.
    item = cJSON_GetArrayItem(array, i);
    CHECK_TYPE(item, cJSON_Object);

    // Parse locator ID.
    param = cJSON_GetObjectItem(item, "id");
    CHECK_TYPE(param, cJSON_String);
    aoa_id_copy(id_json, param->valuestring);

    if (aoa_id_compare(id_json, locator_id) == 0) {
      // Locator found, check for config.
      item = cJSON_GetObjectItem(item, "config");
      CHECK_TYPE(item, cJSON_Object);
      // Check if config for the locator present.
      if (NULL == item) {
        return SL_STATUS_NOT_FOUND;
      }

      // Locator config found.
      *locator = item;
      return SL_STATUS_OK;
    }

    ++i;
  }

  return SL_STATUS_NOT_FOUND;
}
