/***************************************************************************//**
 * @file
 * @brief Decode the af support related commands
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#include PLATFORM_HEADER
#include "af.h"
#include "ezsp-enum.h"
#include "ezsp-frame-utilities.h"
#include "attribute-storage.h"
#include "attribute-table.h"

#if defined(SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT)
extern bool sli_zigbee_af_green_power_server_gp_sink_commissioning_mode_command_handler(uint8_t options,
                                                                                        uint16_t gpmAddrForSecurity,
                                                                                        uint16_t gpmAddrForPairing,
                                                                                        uint8_t sinkEndpoint);
extern void sli_zigbee_af_gp_trans_table_clear_translation_table();
extern EmberStatus sli_zigbee_af_gp_test_security(void);

static void processReadAttributeCommand()
{
  EmberStatus status;
  uint8_t endpoint;
  uint16_t cluster;
  uint16_t attributeId;
  uint8_t mask;
  uint16_t manufacturerCode;
  uint8_t readLength;
  uint8_t dataType;
  // EZSP MAX LENGTH - sizeof(status) - sizeof(dataType) - sizeof(readLength)
  // 200 - 1 - 1 - 1 = 197
  uint8_t data[197] = { 0 };

  endpoint = fetchInt8u();
  cluster = fetchInt16u();
  attributeId = fetchInt16u();
  mask = fetchInt8u();
  manufacturerCode = fetchInt16u();
  readLength = fetchInt8u();

  if (readLength > sizeof(data)) {
    readLength = sizeof(data);
  }

  status = sli_zigbee_af_read_attribute(endpoint, cluster, attributeId,
                                        mask, manufacturerCode, data, readLength, &dataType);

  if (status == EMBER_SUCCESS) {
    if (emberAfIsStringAttributeType(dataType)) {
      readLength = emberAfStringLength(data);
    } else if (emberAfIsLongStringAttributeType(dataType)) {
      readLength = emberAfLongStringLength(data);
    } else {
      readLength = emberAfGetDataSize(dataType);
    }
  } else {
    // Indicating failed to read attribute.
    readLength = 0;
    dataType = 0;
  }

  appendInt8u(status);
  appendInt8u(dataType);
  appendInt8u(readLength);
  appendInt8uArray(readLength, data);
}

static void processWriteAttributeCommand()
{
  EmberStatus status;
  uint8_t endpoint;
  uint16_t cluster;
  uint16_t attributeId;
  uint8_t mask;
  uint16_t manufacturerCode;
  uint8_t overrideReadOnlyAndDataType;
  uint8_t justTest;
  uint8_t dataType;
  uint8_t dataLength;
  uint8_t *data;

  endpoint = fetchInt8u();
  cluster = fetchInt16u();
  attributeId = fetchInt16u();
  mask = fetchInt8u();
  manufacturerCode = fetchInt16u();
  overrideReadOnlyAndDataType = fetchInt8u();
  justTest = fetchInt8u();
  dataType = fetchInt8u();
  dataLength = fetchInt8u();
  data = (uint8_t*)fetchInt8uPointer(dataLength);

  status = sli_zigbee_af_write_attribute(endpoint, cluster, attributeId,
                                         mask, manufacturerCode, data, dataType, overrideReadOnlyAndDataType, justTest);

  appendInt8u(status);
}

// Hook from command handler for the af support related commands
bool sli_zigbee_af_process_ezsp_af_support_commands(uint16_t commandId)
{
  switch (commandId) {
    case EZSP_READ_ATTRIBUTE:
      processReadAttributeCommand();
      break;
    case EZSP_WRITE_ATTRIBUTE:
      processWriteAttributeCommand();
      break;
#ifdef SL_CATALOG_ZIGBEE_GREEN_POWER_SERVER_PRESENT
    case EZSP_GP_SINK_COMMISSION: {
      EmberStatus status = EMBER_ERR_FATAL;
      uint8_t options = fetchInt8u();
      uint16_t gpmAddressSecurity = fetchInt16u();
      uint16_t gpmAddressPairing = fetchInt16u();
      uint8_t endpoint = fetchInt8u();
      bool ret =   sli_zigbee_af_green_power_server_gp_sink_commissioning_mode_command_handler(options,
                                                                                               gpmAddressSecurity,
                                                                                               gpmAddressPairing,
                                                                                               endpoint);
      if (ret == true) {
        status = EMBER_SUCCESS;;
      }
      appendInt8u(status);
      break;
    }
#if (EMBER_AF_PLUGIN_GREEN_POWER_SERVER_SECURITY_TEST_VECTORS == 1)
    case EZSP_GP_SECURITY_TEST_VECTORS: {
      EmberStatus status = sli_zigbee_af_gp_test_security();
      appendInt8u(status);
      break;
    }
#endif // (EMBER_AF_PLUGIN_GREEN_POWER_SERVER_SECURITY_TEST_VECTORS == 1)
#endif // SL_CATALOG_ZIGBEE_GREEN_POWER_SERVER_PRESENT

#ifdef SL_CATALOG_ZIGBEE_GREEN_POWER_TRANSLATION_TABLE_PRESENT
    case EZSP_GP_TRANSLATION_TABLE_CLEAR: {
      sli_zigbee_af_gp_trans_table_clear_translation_table();
      break;
    }
#endif // SL_CATALOG_ZIGBEE_GREEN_POWER_TRANSLATION_TABLE_PRESENT

    default:
      return false;
  }
  return true;
}
#endif // defined(SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT)
