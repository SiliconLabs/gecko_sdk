/***************************************************************************//**
 * @file
 * @brief ESL Tag core interface declarations for sensor functionalities.
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
#ifndef ESL_TAG_SENSOR_CORE_H
#define ESL_TAG_SENSOR_CORE_H
#include <stdint.h>
#include "sl_status.h"
#include "esl_tag_core.h"
#include "sl_btmesh_device_properties.h"

/// @typedef ESL Sensor Data Structures: Sensor_Size field
typedef uint8_t   esl_sensor_size_t;

/// @typedef ESL Sensor Data Structures: Sensor_Type field, standard sensor ID
typedef uint16_t  esl_sensor_standard_id_t;

/// @typedef ESL Sensor Data Structures: Sensor_Type sub-field for vendor ID
typedef uint16_t  esl_sensor_company_id_t;

/// @typedef ESL Sensor Data Structures: Sensor_Type sub-field for sensor code
typedef uint16_t  esl_sensor_sensor_code_t;

/// @typedef ESL Sensor Data Structure by Service Spec. v0.9, Section 3.8.1.1.2
typedef PACKSTRUCT (struct {
  esl_sensor_company_id_t  company_id;
  esl_sensor_sensor_code_t sensor_code;
}) esl_sensor_vendor_id_t;

/// @typedef ESL Sensor Data Structure abstract data type pointer
typedef struct esl_sensor_vendor_id_t *esl_sensor_vendor_id_p;

/// ESL Sensor_Size: Standard Mesh Device Property ID
#define ESL_SENSOR_SIZE_MESH_DEVICE     0x00

/// ESL Sensor_Size: Vendor Defined ESL Sensor ID
#define ESL_SENSOR_SIZE_VENDOR_SPECIFIC 0x01

/// Macro for registering a mesh device property ID
/// The only invalid company ID available - used for Sensor_Size recognition
#define ESL_SENSOR_MESH_DEVICE          (esl_sensor_company_id_t)0xFFFF

/// Company ID for a Silicon Laboratories vendor specific device
#define ESL_SENSOR_SILABS_DEVICE        (esl_sensor_company_id_t)0x02FF

/// Maximum length of the sensor data according to ESL Service Spec. v0.9
/// Section 3.10.3.5
#define ESL_SENSOR_MAX_REPORT_LENGTH    15

/**************************************************************************//**
 * Add an ESL Tag sensor to the list of available sensors. Any sensor on a Tag
 * can be only used after adding it to the internal registry.
 * @param[in] company esl_sensor_company_id_t Company Identifier, a unique 16
 *                   bit number assigned by the Bluetooth SIG to a member
 *                   company.
 *                   The Company Identifier values are defined in the Bluetooth
 *                   SIG Assigned Numbers.
 * @param[in] code esl_sensor_sensor_code_t A number assigned to a vendor­
 *                   specific sensor type by the member whose Company Identifier
 *                   is in the Company_ID sub­field.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_sensor_add(esl_sensor_company_id_t company,
                           esl_sensor_sensor_code_t code);

/**************************************************************************//**
 * Read custom ESL Sensor.
 * This is a common function for one or more vendor defined sensors (and for any
 * standard ones added by a vendor), to be implemented.
 * It's the users responsibility to actually read the sensors based on their ID,
 * then call @ref esl_sensor_set_report() with the measurement data.
 * Return sl_status_t reported by esl_sensor_set_report() or SL_STATUS_FAIL on
 * any other case (e.g. ID unknown, detectable HW error or retry needed due slow
 * device etc.) and in the latter case set the ESL error code by invoking the
 * @ref esl_set_last_error() with an appropriate error code parameter.
 * @param[in] index uint8_t index of the ESL Sensor to be read
 * @param[in] size either @ref ESL_SENSOR_SIZE_MESH_DEVICE or
 *                 @ref ESL_SENSOR_SIZE_VENDOR_SPECIFIC depending on the sensor
 *                 type to be read.
 * @param[in] sensor_id custom or standard ID depending on 'size' parameter
 * @param[in] company esl_sensor_company_id_t either @ref ESL_SENSOR_MESH_DEVICE
 *            or your Bluetooth company ID depending on the type. Check can be
 *            omitted if 'size' equals to ESL_SENSOR_SIZE_MESH_DEVICE.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_sensor_custom_read(uint8_t index,
                                   esl_sensor_size_t size,
                                   esl_sensor_sensor_code_t sensor_id,
                                   esl_sensor_company_id_t company);

/**************************************************************************//**
 * Report ESL Sensor measurement result.
 * @param[in] report_size uint8_t the (non zero!) size of data to report, up to
 *            @ref ESL_SENSOR_MAX_REPORT_LENGTH
 * @param[out] report_data void* pointer to the actual measurement result data
 *             to be reported
 * @return sl_status_t SL_STATUS_OK on success
 *****************************************************************************/
sl_status_t esl_sensor_set_report(uint8_t report_size, void *report_data);

/**************************************************************************//**
 * ESL Sensor's Bluetooth stack event handler.
 * This one runs by the user implementation (usually in app.c) in parallel.
 * Adds the built-in ESL sensors which are enabled in the configuration to the
 * beginning of the sensor list silently.
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void esl_sensor_bt_on_event(sl_bt_msg_t *evt);

#endif // ESL_TAG_SENSOR_CORE_H
