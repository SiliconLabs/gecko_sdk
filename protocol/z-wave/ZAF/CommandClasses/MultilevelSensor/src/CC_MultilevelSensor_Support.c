/***************************************************************************//**
 * @file CC_MultilevelSensor_Support.c
 * @brief CC_MultilevelSensor_Support.c
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

// -----------------------------------------------------------------------------
//                   Includes
// -----------------------------------------------------------------------------
#include <misc.h>
#include <string.h>
#include <stddef.h>
#include <ZAF_TSE.h>
#include <AppTimer.h>
#include <ZW_classcmd.h>
#include <CC_Supervision.h>
#include <Assert.h>
#include <ZW_typedefs.h>
#include "ZW_TransportEndpoint.h"
#include "CC_MultilevelSensor_Support.h"
#include "CC_MultilevelSensor_SensorHandler.h"
#include "CC_MultilevelSensor_SensorHandlerTypes.h"
#include <cc_multilevel_sensor_config_api.h>
// -----------------------------------------------------------------------------
//                Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//              Static Function Declarations
// -----------------------------------------------------------------------------
static void
cc_multilevel_sensor_autoreport_callback(SSwTimer *pTimer);

static void
cc_multilevel_sensor_operation_report_stx(zaf_tx_options_t *tx_options, void* pData);

static received_frame_status_t
cc_multilevel_sensor_cmd_sensor_multilevel_get(  RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                                    const ZW_APPLICATION_TX_BUFFER *pCmd,
                                                    uint8_t cmdLength,
                                                    ZW_APPLICATION_TX_BUFFER * pFrameOut,
                                                    uint8_t * pLengthOut);
static received_frame_status_t
cc_multilevel_sensor_cmd_sensor_multilevel_get_supported_sensor( RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                                                    const ZW_APPLICATION_TX_BUFFER *pCmd,
                                                                    uint8_t cmdLength,
                                                                    ZW_APPLICATION_TX_BUFFER * pFrameOut,
                                                                    uint8_t * pLengthOut);
static received_frame_status_t
cc_multilevel_sensor_cmd_sensor_multilevel_get_supported_scale( RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                                                   const ZW_APPLICATION_TX_BUFFER *pCmd,
                                                                   uint8_t cmdLength,
                                                                   ZW_APPLICATION_TX_BUFFER * pFrameOut,
                                                                   uint8_t * pLengthOut);

// -----------------------------------------------------------------------------
//                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                Static Variables
// -----------------------------------------------------------------------------
/**< Software timer instance which handles the periodic reporting to the lifeline. */
static SSwTimer cc_multilevel_sensor_autoreport_timer = { 0 };
// -----------------------------------------------------------------------------
//              Public Function Definitions
// -----------------------------------------------------------------------------
static received_frame_status_t
CC_MultilevelSensor_handler(RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                            ZW_APPLICATION_TX_BUFFER *pCmd,
                            uint8_t cmdLength,
                            __attribute__((unused)) ZW_APPLICATION_TX_BUFFER * pFrameOut,
                            __attribute__((unused)) uint8_t * pLengthOut)
{
  received_frame_status_t return_value = RECEIVED_FRAME_STATUS_SUCCESS;

  switch (pCmd->ZW_Common.cmd)
  {
    case SENSOR_MULTILEVEL_GET_V11:
      return_value = cc_multilevel_sensor_cmd_sensor_multilevel_get(pRxOpt, pCmd, cmdLength, pFrameOut, pLengthOut);
    break;
    case SENSOR_MULTILEVEL_SUPPORTED_GET_SENSOR_V11:
      return_value = cc_multilevel_sensor_cmd_sensor_multilevel_get_supported_sensor(pRxOpt, pCmd, cmdLength, pFrameOut, pLengthOut);
    break;
    case SENSOR_MULTILEVEL_SUPPORTED_GET_SCALE_V11:
      return_value = cc_multilevel_sensor_cmd_sensor_multilevel_get_supported_scale(pRxOpt, pCmd, cmdLength, pFrameOut, pLengthOut);
    break;
    default:
      return_value = RECEIVED_FRAME_STATUS_NO_SUPPORT;
      break;
  }

  return return_value;
}

static void cc_multilevel_sensor_init(void)
{
  cc_multilevel_sensor_config_register_instances();
  cc_multilevel_sensor_init_all_sensor();
  AppTimerDeepSleepPersistentRegister(&cc_multilevel_sensor_autoreport_timer, false, cc_multilevel_sensor_autoreport_callback);
  AppTimerDeepSleepPersistentStart(&cc_multilevel_sensor_autoreport_timer, MULTILEVEL_SENSOR_DEFAULT_AUTOREPORT_PEDIOD_MS);
}

typedef struct tse_data_t {
  RECEIVE_OPTIONS_TYPE_EX zaf_tse_local_actuation;
  sensor_interface_iterator_t* sensor_interface;
} tse_data_t;


static tse_data_t tse_data[MULTILEVEL_SENSOR_REGISTERED_SENSOR_NUMBER_LIMIT] = {0};

/**
 * This is a callback for the autoreport timer to trigger periodically the lifeline
 * report of the sensors' measured values.
 * @param[in] pTimer timer instance which called the callback
 */
static void cc_multilevel_sensor_autoreport_callback(__attribute__((unused)) SSwTimer *pTimer)
{
  cc_multilevel_sensor_send_sensor_data();
  AppTimerDeepSleepPersistentStart(&cc_multilevel_sensor_autoreport_timer, MULTILEVEL_SENSOR_DEFAULT_AUTOREPORT_PEDIOD_MS);
}

/**
 * Sends Multilevel Sensor report when TSE was triggered
 * @param[in] txOptions TxOptions, filled in by TSE
 * @param[in] pData this parameter is not used in this case
 */
static void
cc_multilevel_sensor_operation_report_stx(zaf_tx_options_t *tx_options, void* pData)
{
  if (NULL == pData)
  {
    ASSERT(0);  // this only for debugging purpose.
    return;
  }

  sensor_interface_iterator_t *sensor_interface_iterator = ((tse_data_t *)pData)->sensor_interface;
  if (NULL == sensor_interface_iterator) {
    ASSERT(0);  // this only for debugging purpose.
    return;
  }

  ZW_APPLICATION_TX_BUFFER txBuf = {
    .ZW_SensorMultilevelReport1byteV11Frame.cmdClass = COMMAND_CLASS_SENSOR_MULTILEVEL_V11,
    .ZW_SensorMultilevelReport1byteV11Frame.cmd = SENSOR_MULTILEVEL_REPORT_V11,
    .ZW_SensorMultilevelReport1byteV11Frame.sensorType = sensor_interface_iterator->sensor_type->value
  };

  if (sensor_interface_iterator->read_value != NULL)
  {
    uint8_t scale;
    sensor_read_result_t read_result;
    scale = cc_multilevel_sensor_check_scale(sensor_interface_iterator, 0);
    if (true == sensor_interface_iterator->read_value(&read_result, scale))
    {
      txBuf.ZW_SensorMultilevelReport1byteV11Frame.level = (uint8_t)(read_result.precision << 5) |
                                                           (uint8_t)(scale << 3) |
                                                           (uint8_t)read_result.size_bytes;
      memcpy(&txBuf.ZW_SensorMultilevelReport1byteV11Frame.sensorValue1, read_result.raw_result, read_result.size_bytes);
      tx_options->use_supervision = true;

      (void) zaf_transport_tx((uint8_t *)&txBuf,
                              sizeof(ZW_SENSOR_MULTILEVEL_REPORT_1BYTE_V11_FRAME) - 1 + read_result.size_bytes,
                              ZAF_TSE_TXCallback,
                              tx_options);
    }
  }
}

static received_frame_status_t
cc_multilevel_sensor_cmd_sensor_multilevel_get( RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                                   const ZW_APPLICATION_TX_BUFFER *pCmd,
                                                   __attribute__((unused)) uint8_t cmdLength,
                                                   ZW_APPLICATION_TX_BUFFER * pFrameOut,
                                                   uint8_t * pLengthOut)
{

  if(true == Check_not_legal_response_job(pRxOpt))
  {
    return RECEIVED_FRAME_STATUS_FAIL;
  }

  sensor_interface_t* sensor_interface;
  uint8_t sensor_type_value =  pCmd->ZW_SensorMultilevelGetV11Frame.sensorType;
  uint8_t scale             = (pCmd->ZW_SensorMultilevelGetV11Frame.properties1 >> 3) & 0x03;

  pFrameOut->ZW_SensorMultilevelReport4byteV11Frame.cmdClass = COMMAND_CLASS_SENSOR_MULTILEVEL_V11;
  pFrameOut->ZW_SensorMultilevelReport4byteV11Frame.cmd      = SENSOR_MULTILEVEL_REPORT_V11;

  if( CC_MULTILEVEL_SENSOR_RETURN_VALUE_NOT_FOUND ==
      cc_multilevel_sensor_check_sensor_type_registered(sensor_type_value))
  {
    cc_multilevel_sensor_get_default_sensor_type(&sensor_type_value);
  }

  pFrameOut->ZW_SensorMultilevelReport4byteV11Frame.sensorType = sensor_type_value;

  if(CC_MULTILEVEL_SENSOR_RETURN_VALUE_OK ==
     cc_multilevel_sensor_get_interface(sensor_type_value, &sensor_interface))
  {
    sensor_read_result_t read_result;

    scale = cc_multilevel_sensor_check_scale(sensor_interface, scale);
    if( (sensor_interface->read_value != NULL) && (true == sensor_interface->read_value(&read_result, scale)))
    {
      pFrameOut->ZW_SensorMultilevelReport4byteV11Frame.level =  (uint8_t)(read_result.precision << 5) |
                                                                              (uint8_t)(scale << 3) |
                                                              (uint8_t)read_result.size_bytes;
      // TODO: Why memset 4 bytes to 0 instead of setting the correct size to pLengthOut ?
      memset(&pFrameOut->ZW_SensorMultilevelReport4byteV11Frame.sensorValue1, 0, SLI_MAX_RAW_RESULT_BYTES);
      memcpy(&pFrameOut->ZW_SensorMultilevelReport4byteV11Frame.sensorValue1,
              read_result.raw_result,
              read_result.size_bytes);

      *pLengthOut = sizeof(pFrameOut->ZW_SensorMultilevelReport4byteV11Frame);
    }
    else
    {
      return RECEIVED_FRAME_STATUS_FAIL;
    }
  }
  else
  {
    return RECEIVED_FRAME_STATUS_FAIL;
  }

  return RECEIVED_FRAME_STATUS_SUCCESS;
}

static received_frame_status_t
cc_multilevel_sensor_cmd_sensor_multilevel_get_supported_sensor( RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                                                    __attribute__((unused)) const ZW_APPLICATION_TX_BUFFER *pCmd,
                                                                    __attribute__((unused)) uint8_t cmdLength,
                                                                    ZW_APPLICATION_TX_BUFFER * pFrameOut,
                                                                    uint8_t * pLengthOut)
{
  if(true == Check_not_legal_response_job(pRxOpt))
  {
    return RECEIVED_FRAME_STATUS_FAIL;
  }

  uint8_t send_buffer_length_bytes = 2   /*header*/;
  size_t payload_length           = 11; /*payload*/
  uint8_t* raw_buffer_payload     = (uint8_t*)&pFrameOut->ZW_SensorMultilevelSupportedSensorReport4byteV11Frame.bitMask1;
  pFrameOut->ZW_SensorMultilevelSupportedSensorReport4byteV11Frame.cmdClass = COMMAND_CLASS_SENSOR_MULTILEVEL_V11;
  pFrameOut->ZW_SensorMultilevelSupportedSensorReport4byteV11Frame.cmd      = SENSOR_MULTILEVEL_SUPPORTED_SENSOR_REPORT_V11;
  cc_multilevel_sensor_get_supported_sensors(&pFrameOut->ZW_SensorMultilevelSupportedSensorReport4byteV11Frame.bitMask1);
  while(payload_length)
  {
    if(raw_buffer_payload[payload_length - 1] != 0){break;}
    payload_length--;
  }
  send_buffer_length_bytes += payload_length;
  *pLengthOut = send_buffer_length_bytes;

  return RECEIVED_FRAME_STATUS_SUCCESS;
}

static received_frame_status_t
cc_multilevel_sensor_cmd_sensor_multilevel_get_supported_scale( RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                                                   const ZW_APPLICATION_TX_BUFFER *pCmd,
                                                                   __attribute__((unused)) uint8_t cmdLength,
                                                                   ZW_APPLICATION_TX_BUFFER * pFrameOut,
                                                                   uint8_t * pLengthOut)
{
  if(true == Check_not_legal_response_job(pRxOpt))
  {
    return RECEIVED_FRAME_STATUS_FAIL;
  }
  uint8_t supported_scale   = 0;

  pFrameOut->ZW_SensorMultilevelSupportedScaleReportV5Frame.cmdClass    = COMMAND_CLASS_SENSOR_MULTILEVEL_V11;
  pFrameOut->ZW_SensorMultilevelSupportedScaleReportV5Frame.cmd         = SENSOR_MULTILEVEL_SUPPORTED_SCALE_REPORT_V11;
  pFrameOut->ZW_SensorMultilevelSupportedScaleReportV5Frame.sensorType  = pCmd->ZW_SensorMultilevelGetV11Frame.sensorType;

  supported_scale = 0;

  if(CC_MULTILEVEL_SENSOR_RETURN_VALUE_OK ==
     cc_multilevel_sensor_get_supported_scale(pCmd->ZW_SensorMultilevelGetV11Frame.sensorType, &supported_scale))
  {
    pFrameOut->ZW_SensorMultilevelSupportedScaleReportV5Frame.properties1 = supported_scale;
  }

  *pLengthOut = sizeof(pFrameOut->ZW_SensorMultilevelSupportedScaleReportV5Frame);

  return RECEIVED_FRAME_STATUS_SUCCESS;
}

static uint8_t lifeline_reporting(ccc_pair_t * p_ccc_pair)
{
  p_ccc_pair->cmdClass = COMMAND_CLASS_SENSOR_MULTILEVEL;
  p_ccc_pair->cmd      = SENSOR_MULTILEVEL_REPORT;
  return 1;
}

void cc_multilevel_sensor_send_sensor_data(void)
{
  /**
    * TSE simulated RX option for local change addressed to the Root Device
    * All applications can use this variable when triggering the TSE after
    * a local / non Z-Wave initiated change
    */
  sensor_interface_iterator_t* sensor_interface_iterator;
  cc_multilevel_sensor_init_iterator(&sensor_interface_iterator);
  uint8_t i = 0;
  while(sensor_interface_iterator)
  {
    tse_data[i].sensor_interface = sensor_interface_iterator;
    ZAF_TSE_Trigger(cc_multilevel_sensor_operation_report_stx, (void*)&tse_data[i], false);
    cc_multilevel_sensor_next_iterator(&sensor_interface_iterator);
    i++;
  }
}

ZW_WEAK void
cc_multilevel_sensor_config_register_instances(void)
{

}

REGISTER_CC_V4(COMMAND_CLASS_SENSOR_MULTILEVEL_V11, SENSOR_MULTILEVEL_VERSION_V11, CC_MultilevelSensor_handler, NULL, NULL, lifeline_reporting, 0, cc_multilevel_sensor_init, NULL);
