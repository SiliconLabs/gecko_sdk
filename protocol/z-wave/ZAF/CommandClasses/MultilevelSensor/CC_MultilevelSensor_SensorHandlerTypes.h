/***************************************************************************//**
 * @file CC_MultilevelSensor_SensorHandlerTypes.h
 * @brief CC_MultilevelSensor_SensorHandlerTypes.h
 * @copyright 2020 Silicon Laboratories Inc.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#ifndef CC_MULTILEVELSENSOR_SENSORHANDLER_TYPES_H
#define CC_MULTILEVELSENSOR_SENSORHANDLER_TYPES_H
// -----------------------------------------------------------------------------
//                   Includes
// -----------------------------------------------------------------------------
#include <stdint.h>
#include <stdbool.h>
#include "CC_MultilevelSensor_Configuration.h"
// -----------------------------------------------------------------------------
//                Macros and Typedefs
// -----------------------------------------------------------------------------
#define SL_SENSOR_SCALE_DEFAULT        0x00
#define SL_SENSOR_SCALE_CELSIUS        0x00
#define SL_SENSOR_SCALE_FAHRENHEIT     0x01
#define SL_SENSOR_SCALE_PERCENTAGE     0x00
#define SL_SENSOR_SCALE_DIMENSIONLESS  0x01
#define SL_SENSOR_SCALE_LUX            0x01
#define SL_SENSOR_SCALE_WATT           0x00
#define SL_SENSOR_SCALE_BTU_H          0x01 /*Btu/h*/
#define SL_SENSOR_SCALE_ABSOLUTE_HUMIDITY  0x01 /*g/m3*/

/**
 * Defined possible sensor types
 */
typedef enum sl_sensor_name{
  SL_SENSOR_NAME_AIR_TEMPERATURE,
  SL_SENSOR_NAME_GENERAL_PURPOSE,
  SL_SENSOR_NAME_ILLUMINANCE,
  SL_SENSOR_NAME_POWER,
  SL_SENSOR_NAME_HUMIDITY,
  SL_SENSOR_NAME_MAX_COUNT
}sl_sensor_name_t;

/**
 * Structure that holds the attributes of a sensor type.
 */
typedef struct _sl_sensor_type{
  uint8_t value;        ///< Sensor type id from SDS13812 
  uint8_t byte_offset;    ///< Supported bitmask byte number from SDS13812 
  uint8_t bit_mask;       ///< Supported bitmask bit number from SDS13812 
  uint8_t max_scale_value;  ///< Maximum supported scale number from SDS13812
}sl_sensor_type_t;

/**
 * Defined possible sensor read size
 */
typedef enum {
  SL_SENSOR_READ_RESULT_SIZE_1 = 1,
  SL_SENSOR_READ_RESULT_SIZE_2 = 2,
  SL_SENSOR_READ_RESULT_SIZE_4 = 4,
  SL_SENSOR_READ_RESULT_SIZE_END = 5
}sl_sensor_read_result_size_t;

/**
 * Defined possible sensor read precision
 */
typedef enum {
  SL_SENSOR_READ_RESULT_PRECISION_1 = 1,
  SL_SENSOR_READ_RESULT_PRECISION_2,
  SL_SENSOR_READ_RESULT_PRECISION_3,
  SL_SENSOR_READ_RESULT_PRECISION_END
}sl_sensor_read_result_precision;

/**
 * Structure that holds a read result from the read interface.
 */
#define SLI_MAX_RAW_RESULT_BYTES 4
typedef struct _sl_sensor_read_result {
  uint8_t raw_result[SLI_MAX_RAW_RESULT_BYTES];   ///< The raw buffer which holds the result.
  sl_sensor_read_result_precision precision;     ///< The precision which the raw result should be interpret with
  sl_sensor_read_result_size_t size_bytes;     ///< The size which the raw result should be interpret with
}sl_sensor_read_result_t;

/**
 * Structure that holds a read result from the read interface.
 */
typedef struct _sl_sensor_interface {
  const sl_sensor_type_t* sensor_type;                  ///< Reference of a sensor type structure
  uint8_t supported_scale;                        ///< Each bit represents a supported scale
  bool (*init)(void);                           ///< Function pointer to initialize a sensor
  bool (*deinit)(void);                           ///< Function pointer to deinitialize a sensor
  bool (*read_value)(sl_sensor_read_result_t* o_result, uint8_t i_scale); ///< Function pointer to read a sensor value
}sl_sensor_interface_t, sl_sensor_interface_iterator_t;

/**
 * Defined sensor interface return values
 */
typedef enum {
  SL_SENSOR_INTERFACE_RETURN_VALUE_OK,
  SL_SENSOR_INTERFACE_RETURN_VALUE_ALREADY_SET,
  SL_SENSOR_INTERFACE_RETURN_VALUE_INVALID_SCALE_VALUE,
  SL_SENSOR_INTERFACE_RETURN_VALUE_ERROR,
  SL_SENSOR_INTERFACE_RETURN_VALUE_END
}sl_sensor_interface_return_value_t;

/**
 * Defined Multilevel Sensor return values
 */
typedef enum {
  SL_CC_MULTILEVEL_SENSOR_RETURN_VALUE_OK,
  SL_CC_MULTILEVEL_SENSOR_RETURN_VALUE_ERROR,
  SL_CC_MULTILEVEL_SENSOR_RETURN_VALUE_NOT_FOUND,
  SL_CC_MULTILEVEL_SENSOR_RETURN_VALUE_ALREADY_REGISTRATED,
  SL_CC_MULTILEVEL_SENSOR_RETURN_VALUE_REGISTRATION_LIMIT_REACHED,
  SL_CC_MULTILEVEL_SENSOR_RETURN_VALUE_END
}sl_cc_multilevel_sensor_return_value;
 
/**
 * Structure that administrate all of the registered sensors.
 */

typedef struct _sl_sensor_administration {
  sl_sensor_interface_t* registrated_sensors[SL_MULTILEVEL_SENSOR_REGISTERED_SENSOR_NUMBER_LIMIT];  ///< Reference of the sensor interfaces
  uint8_t number_of_registrated_sensors;                  ///< Stores how many sensors are registered
}sl_sensor_administration_t;

// -----------------------------------------------------------------------------
//                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//              Public Function Declarations
// -----------------------------------------------------------------------------
/**
 * Returns a sl_sensor_type_t struct from the sensor_types config table
 * @param[in] i_sensor_name The name of the sensor type, the sensor type attributes'
 * reference will be look for based on this value
 *
 * @return sl_sensor_type_t struct which includes the type attributes.
 */
const sl_sensor_type_t*
sl_cc_multilevel_sensor_get_sensor_type(sl_sensor_name_t i_sensor_name);

/**
 * Initialize a sensor interface instance. Sets the whole struct to zero and sets
 * the reference to the appropiate sl_sensor_type_t struct.
 * @param[in] i_instance Pointer to an existing sensor interface to init
 * @param[in] i_name The name of the sensor type, the sensor type attributes'
 * reference will be look for based on this value
 *
 * @return Status of the initialization.
 */
sl_sensor_interface_return_value_t
sl_cc_multilevel_sensor_init_interface(sl_sensor_interface_t* i_instance, sl_sensor_name_t i_name);

/**
 * Adds a new scale to an existing interface. Supported scales must be set by this function during initialization.
 * @param[in] i_instance Pointer to an existing sensor interface which the new scale will be registered to
 * @param[in] i_scale The new scale which will be registered
 *
 * @return Status of the new scale value registration.
 */
sl_sensor_interface_return_value_t
sl_cc_multilevel_sensor_add_supported_scale_interface(sl_sensor_interface_t* i_instance, uint8_t i_scale);

#endif  // CC_MULTILEVELSENSOR_SENSORHANDLER_TYPES_H
