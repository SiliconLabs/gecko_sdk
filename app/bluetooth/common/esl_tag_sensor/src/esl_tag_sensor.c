/***************************************************************************//**
 * @file
 * @brief ESL Tag Sensor implementation
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
#include <stdio.h>
#include <string.h>
#include "em_emu.h"
#include "gatt_db.h"
#include "em_common.h"
#include "sl_sleeptimer.h"
#include "esl_tag_log.h"
#include "esl_tag_sensor.h"
#include "esl_tag_response.h"
#include "esl_tag_sensor_core.h"
#include "esl_tag_sensor_config.h"
#include "esl_tag_battery_internal.h"

// ESL Sensor Information Characteristics minimum length (by specification)
#define ESL_SENSOR_INFO_MINIMUM_SIZE  3

// ESL Sensor Information Characteristics: absolute maximum number of sensors
#define ESL_SENSOR_MAX_COUNT          (ESL_SENSOR_INFO_POOL_SIZE \
                                       / ESL_SENSOR_INFO_MINIMUM_SIZE)
// Sensor Information type - same format as defined in ESL Specification:
// Sensor Information Characteristic definition
PACKSTRUCT(struct esl_sensor_info_s {
  esl_sensor_size_t size;                         // one octet
  union {
    esl_sensor_standard_id_t mesh_property_id;    // only two octets
    esl_sensor_vendor_id_t   vendor_specific;     // four octets
  };
});

/// ESL Sensor Object abstract data type pointer
typedef struct esl_sensor_info_s *esl_sensor_info_p;

// Sensor object type for internal use
typedef PACKSTRUCT (struct {
  esl_sensor_info_p info;
}) esl_sensor_object_t;

// Internal sensor registry type
typedef PACKSTRUCT (struct {
  esl_sensor_object_t *next_object;
  uint8_t             sensor_count;
}) esl_sensor_registry_t;

// Sensor info array - max. number of elements is defined in config header
static uint8_t                sensor_info[ESL_SENSOR_INFO_POOL_SIZE];

// Sensor object array for internal use
static esl_sensor_object_t    sensor_object[ESL_SENSOR_MAX_COUNT];

// Sensor registry structure
static esl_sensor_registry_t  sensor_registry;

/******************************************************************************
 * Sensor info getter - returns with all sensor data in a format which can be
 * easily write to the ESL Sensor Information characteristic.
 * @param[out] uint16_t* size of the ESL sensor info data
 * @param[out] void** pointer to the serialized ESL Sensor Information data
 *****************************************************************************/
static inline void esl_sensor_get_all_info(uint16_t *data_size, void **out)
{
  *data_size = (uint16_t)((uint8_t *)sensor_registry.next_object->info
                          - sensor_info);

  // having the characteristic with zero length of data is invalid!
  if (*data_size == 0) {
    // this is an 'user error' condition, still the GATT req. shall succeed once
    // the ESL access point tries to read it, thus we need at least one full set
    // to be reported even if this "shadow" sensor itself will be invalid
    // and hence non-functioning without registering at least one during
    // the ESL boot event, properly
    *data_size = ESL_SENSOR_INFO_MINIMUM_SIZE;
  }

  *out = (void *)sensor_info;
}

void esl_sensor_init(void)
{
  // clear all sensor data
  memset(sensor_info, 0, sizeof(sensor_info));
  memset(sensor_object, 0, sizeof(sensor_object));

  // initialize zero sensor count, prepare sensor creation / allocation
  sensor_registry.next_object  = sensor_object;
  sensor_registry.sensor_count = 0;
  sensor_object[0].info        = (esl_sensor_info_p)sensor_info;
}

void esl_sensor_bt_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;
  (void)sc; // suppress the compiler warning if sl_bt_esl_assert disabled

  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_bt_evt_system_boot_id:
      // here we're checking that we precede the esl_core_bt_on_event invocation
      if (esl_core_get_status() == esl_state_boot) {
        // register sensors which are enabled in the configuration
#if (ESL_SENSOR_INPUT_VOLTAGE_ENABLE)
        sc = esl_sensor_add(ESL_SENSOR_MESH_DEVICE,
                            PRESENT_INPUT_VOLTAGE);
        sl_bt_esl_assert(sc == SL_STATUS_OK);
#endif // (ESL_SENSOR_INPUT_VOLTAGE_ENABLE)
#if (ESL_SENSOR_OPERATING_TEMPERATURE_ENABLE)
        sc = esl_sensor_add(ESL_SENSOR_MESH_DEVICE,
                            PRESENT_DEVICE_OPERATING_TEMPERATURE);
        sl_bt_esl_assert(sc == SL_STATUS_OK);
#endif // (ESL_SENSOR_OPERATING_TEMPERATURE_ENABLE)
#if (ESL_SENSOR_FW_REVISION_ENABLE)
        sc = esl_sensor_add(ESL_SENSOR_MESH_DEVICE,
                            DEVICE_FIRMWARE_REVISION);
        sl_bt_esl_assert(sc == SL_STATUS_OK);
#endif // (ESL_SENSOR_FW_REVISION_ENABLE)
#if (ESL_SENSOR_MANUFACTURING_DATE_ENABLE)
        sc = esl_sensor_add(ESL_SENSOR_MESH_DEVICE,
                            DEVICE_DATE_OF_MANUFACTURE);
        sl_bt_esl_assert(sc == SL_STATUS_OK);
#endif // (ESL_SENSOR_MANUFACTURING_DATE_ENABLE)
#if (ESL_SENSOR_DEVICE_TEMPERATURE_RANGE_ENABLE)
        sc = esl_sensor_add(ESL_SENSOR_MESH_DEVICE,
                            DEVICE_OPERATING_TEMPERATURE_RANGE_SPECIFICATION);
        sl_bt_esl_assert(sc == SL_STATUS_OK);
#endif // (ESL_SENSOR_DEVICE_TEMPERATURE_RANGE_ENABLE)
      }
      break;

    case sl_bt_evt_gatt_server_user_read_request_id:
      if (evt->data.evt_gatt_server_user_read_request.characteristic == gattdb_esl_sensor_info) {
        uint8_t*  raw_info;
        uint16_t  raw_size, offset;
        uint16_t  mtu_size;
        sl_status_t sc;
        (void)sc; // suppress the compiler warning if sl_bt_esl_assert disabled

        // get pointer first to the beginning of the sensor_info packed struct
        esl_sensor_get_all_info(&raw_size, (void *)&raw_info);
        // then get the offset value from the request
        offset = evt->data.evt_gatt_server_user_read_request.offset;
        // finally, adjust offset and size
        raw_info += offset;
        raw_size -= offset;

        // check current ATT_MTU limits
        sc = sl_bt_gatt_server_get_mtu(evt->data.evt_gatt_server_user_read_request.connection, &mtu_size);
        sl_bt_esl_assert(sc == SL_STATUS_OK);

        // sl_bt_gatt_server_send_user_read_response allows (ATT_MTU - 1) size
        --mtu_size; // of data to be sent at once!

        // and limit the actual data size to be sent accordingly
        raw_size = raw_size > mtu_size ? mtu_size : raw_size;

        // send data (chunk, maybe more read reqs. with offset != 0 will follow)
        sc = sl_bt_gatt_server_send_user_read_response(evt->data.evt_gatt_server_user_read_request.connection,
                                                       evt->data.evt_gatt_server_user_read_request.characteristic,
                                                       SL_STATUS_OK,
                                                       raw_size,
                                                       raw_info,
                                                       NULL);
        sl_bt_esl_assert(sc == SL_STATUS_OK);
      }
      break;

    default:
      break;
  }
}

sl_status_t esl_sensor_add(esl_sensor_company_id_t company,
                           esl_sensor_sensor_code_t code)
{
  sl_status_t result = SL_STATUS_INVALID_STATE;
  esl_state_t state  = esl_core_get_status();

  // ESL Sensor: adding sensors after the boot event is disallowed!
  sl_bt_esl_assert(esl_state_boot == state);

  if (state == esl_state_boot) {
    const uint8_t remaining = (uint8_t)(&sensor_info[ESL_SENSOR_INFO_POOL_SIZE]
                                        - (uint8_t *)sensor_registry.next_object->info);
    const uint8_t info_size = ((company == ESL_SENSOR_MESH_DEVICE)
                               ? ESL_SENSOR_INFO_MINIMUM_SIZE
                               : (sizeof(esl_sensor_vendor_id_t) + 1));
    const bool    is_custom = info_size != ESL_SENSOR_INFO_MINIMUM_SIZE;

    result = SL_STATUS_NO_MORE_RESOURCE;

    if (remaining > info_size) {
      uint8_t* current_info_ptr = (uint8_t *)sensor_object[sensor_registry.sensor_count].info;

      if (is_custom) {
        sensor_registry.next_object->info->size = ESL_SENSOR_SIZE_VENDOR_SPECIFIC;
        sensor_registry.next_object->info->vendor_specific.company_id = company;
        sensor_registry.next_object->info->vendor_specific.sensor_code = code;
      } else {
        sensor_registry.next_object->info->size = ESL_SENSOR_SIZE_MESH_DEVICE;
        sensor_registry.next_object->info->mesh_property_id = code;
      }

      // increase packed sensor info pointer
      current_info_ptr += info_size;
      // increase sensor count
      ++sensor_registry.sensor_count;
      // setup next object
      sensor_object[sensor_registry.sensor_count].info = (esl_sensor_info_p)current_info_ptr;
      // get next object in registry
      ++sensor_registry.next_object;
      result = SL_STATUS_OK;
    } else {
      sl_bt_esl_log(ESL_LOG_COMPONENT_SENSOR,
                    ESL_LOG_LEVEL_ERROR,
                    "Unable to add more sensor, ESL_SENSOR_INFO_POOL_SIZE might be low.");
    }
  }

  return result;
}

sl_status_t esl_sensor_read(uint8_t index)
{
  sl_status_t result = SL_STATUS_INVALID_INDEX;

  if (index < sensor_registry.sensor_count) {
    esl_sensor_size_t size = sensor_object[index].info->size;
    esl_sensor_sensor_code_t code = (size == ESL_SENSOR_SIZE_MESH_DEVICE)
                                    ? sensor_object[index].info->mesh_property_id
                                    : sensor_object[index].info->vendor_specific.sensor_code;
    esl_sensor_company_id_t company = (size == ESL_SENSOR_SIZE_MESH_DEVICE)
                                      ? ESL_SENSOR_MESH_DEVICE
                                      : sensor_object[index].info->vendor_specific.company_id;
    result = esl_sensor_custom_read(index, size, code, company);

    if (result != SL_STATUS_OK && company == ESL_SENSOR_MESH_DEVICE) {
      char        report_data[ESL_SENSOR_MAX_REPORT_LENGTH + 1] = { index, 0 };
      char* const read_target = &report_data[1];
      uint8_t     report_len  = 0;

      // prepare to continue but keep existing user response, if any
      result = (result == SL_STATUS_NOT_SUPPORTED) ? SL_STATUS_OK : result;

      switch (code) {
        default:
          *read_target = 0;
          if (result == SL_STATUS_OK) {
            // change only if there's no previous user result available
            result = SL_STATUS_INVALID_PARAMETER;
          }
          break;
#if (ESL_SENSOR_INPUT_VOLTAGE_ENABLE)
        case PRESENT_INPUT_VOLTAGE: {
          uint32_t battery_millivolts = esl_sensor_get_battery_voltage_mv();
          if (battery_millivolts != ESL_TAG_BATTERY_LEVEL_UNKNOWN) {
            // convert from mV to 1/64 V of resolution: needs divide by 15.625
            // but we do the conversion with integer math, only
            voltage_t input_voltage = (1000 * battery_millivolts) / 15625;
            report_len = sizeof(voltage_t);
            memcpy(read_target, &input_voltage, report_len);
            // check if Service Needed flag has to be set (on low battery level)
            esl_sensor_core_check_battery_level();
          } else {
            result = SL_STATUS_BUSY;
            esl_core_set_last_error(ESL_ERROR_RETRY);
          }
        } break;
#endif // (ESL_SENSOR_INPUT_VOLTAGE_ENABLE)
#if (ESL_SENSOR_OPERATING_TEMPERATURE_ENABLE)
        case PRESENT_DEVICE_OPERATING_TEMPERATURE: {
          temperature_t temp = (temperature_t)((EMU_TemperatureGet() + .5f) * 100.f);
          report_len = sizeof(temperature_t);
          memcpy(read_target, &temp, report_len);
        } break;
#endif // (ESL_SENSOR_OPERATING_TEMPERATURE_ENABLE)
#if (ESL_SENSOR_FW_REVISION_ENABLE)
        case DEVICE_FIRMWARE_REVISION: {
          const uint8_t str_len = sizeof(fixed_string8);
          report_len = str_len;
          snprintf(read_target,
                   // here it's safe to leave extra space for terminating null
                   str_len + 1,
                   "%02u.%02u.%02u",
                   ESL_SENSOR_FW_REVISION_MAJOR,
                   ESL_SENSOR_FW_REVISION_MINOR,
                   ESL_SENSOR_FW_REVISION_PATCH);
        } break;
#endif // (ESL_SENSOR_FW_REVISION_ENABLE)
#if (ESL_SENSOR_MANUFACTURING_DATE_ENABLE)
        case DEVICE_DATE_OF_MANUFACTURE: {
          // GATT Service Supplement v5, Section 3.67.2 (on Date UTC format):
          const size_t utc_len = 3; // Date UTC is uint24, thus 3 bytes long
          sl_sleeptimer_timestamp_t time = 0;
          sl_sleeptimer_date_t      date;
          date_utc_t                utc_date;
          (void)sl_sleeptimer_build_datetime(&date,
                                             ESL_SENSOR_MANUFACTURING_YEAR,
                                             ESL_SENSOR_MANUFACTURING_MONTH - 1,
                                             ESL_SENSOR_MANUFACTURING_DAY,
                                             0, 0, 0, 0);
          (void)sl_sleeptimer_convert_date_to_time(&date, &time);
          utc_date = time ? (time / (24u * 60u * 60u)) : 0;
          report_len = utc_len;
          memcpy(read_target, &utc_date, utc_len);
        } break;
#endif // (ESL_SENSOR_MANUFACTURING_DATE_ENABLE)
#if (ESL_SENSOR_DEVICE_TEMPERATURE_RANGE_ENABLE)
        case DEVICE_OPERATING_TEMPERATURE_RANGE_SPECIFICATION: {
          temperature_range_t operating_range = {
            ESL_SENSOR_DEVICE_TEMPERATURE_RANGE_MIN * 100,
            ESL_SENSOR_DEVICE_TEMPERATURE_RANGE_MAX * 100
          };
          report_len = sizeof(temperature_range_t);
          memcpy(read_target, &operating_range, report_len);
        } break;
#endif // (ESL_SENSOR_DEVICE_TEMPERATURE_RANGE_ENABLE)
      }

      if (result == SL_STATUS_OK) {
        result = esl_sensor_set_report(report_len, report_data);
      }
    }
  } else {
    esl_core_set_last_error(ESL_ERROR_INVALID_PARAMETER);
  }

  return result;
}

SL_WEAK sl_status_t esl_sensor_custom_read(uint8_t index,
                                           esl_sensor_size_t size,
                                           esl_sensor_sensor_code_t sensor_id,
                                           esl_sensor_company_id_t company)
{
  (void)index;
  (void)size;
  (void)sensor_id;
  (void)company;

  // default answer is SL_STATUS_NOT_SUPPORTED
  return SL_STATUS_NOT_SUPPORTED;
}

sl_status_t esl_sensor_set_report(uint8_t report_size, void *report_data)
{
  sl_status_t result = SL_STATUS_WOULD_OVERFLOW;

  if (report_size < ESL_SENSOR_MAX_REPORT_LENGTH) {
    tlv_t tlv_result  = ESL_TLV_RESPONSE_SENSOR_VALUE;
    esl_core_set_tlv_len(tlv_result, report_size + 1); // +1 for the index!
    result = esl_core_build_response(tlv_result, report_data);
  }

  return result;
}

uint8_t esl_sensor_get_count()
{
  return sensor_registry.sensor_count;
}
