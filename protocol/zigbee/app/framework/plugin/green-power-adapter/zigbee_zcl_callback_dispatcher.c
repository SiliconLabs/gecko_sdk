/***************************************************************************//**
 * @file zigbee_zcl_callback_dispatcher.c
 * @brief ZCL callback dispatcher definitions.
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

#include PLATFORM_HEADER
#include "af.h"
#include "zigbee_zcl_callback_dispatcher.h"

// Reset Attributes
void sli_zigbee_af_reset_attributes(uint8_t endpointId)
{
  (void)endpointId;
}

// Pre command received
bool sli_zigbee_af_pre_command_received(EmberAfClusterCommand* cmd)
{
  return (
    emberAfPreCommandReceivedCallback(cmd)
    );
}

// Pre ZDO message received
bool sli_zigbee_af_pre_zdo_message_received(EmberNodeId nodeId, EmberApsFrame* apsFrame, uint8_t* message, uint16_t length)
{
  return (
    emberAfPreZDOMessageReceivedCallback(nodeId, apsFrame, message, length)
    );
}

// ZDO message received
void sli_zigbee_af_zdo_message_received(EmberNodeId sender, EmberApsFrame* apsFrame, uint8_t* message, uint16_t length)
{
  (void)sender;
  (void)apsFrame;
  (void)message;
  (void)length;
}

// Retrieve attribute and craft response
bool sli_zigbee_af_retrieve_attribute_and_craft_response(uint8_t endpoint, EmberAfClusterId clusterId, EmberAfAttributeId attrId, uint8_t mask, uint16_t manufacturerCode, uint16_t readLength)
{
  (void)endpoint;
  (void)clusterId;
  (void)attrId;
  (void)mask;
  (void)manufacturerCode;
  (void)readLength;

  return (false
#ifdef SL_CATALOG_ZIGBEE_GREEN_POWER_CLIENT_PRESENT
          || sli_zigbee_af_green_power_client_retrieve_attribute_and_craft_response(endpoint, clusterId, attrId, mask, manufacturerCode, readLength)
#endif //SL_CATALOG_ZIGBEE_GREEN_POWER_CLIENT_PRESENT
#ifdef SL_CATALOG_ZIGBEE_GREEN_POWER_SERVER_PRESENT
          || sli_zigbee_af_green_power_server_retrieve_attribute_and_craft_response(endpoint, clusterId, attrId, mask, manufacturerCode, readLength)
#endif //SL_CATALOG_ZIGBEE_GREEN_POWER_SERVER_PRESENT
          );
}

// Read attributes response
bool sli_zigbee_af_read_attributes_response(EmberAfClusterId clusterId, uint8_t* buffer, uint16_t bufLen)
{
  return (
    emberAfReadAttributesResponseCallback(clusterId, buffer, bufLen)
    );
}

// Report attributes
bool sli_zigbee_af_report_attributes(EmberAfClusterId clusterId, uint8_t * buffer, uint16_t bufLen)
{
  return (
    emberAfReportAttributesCallback(clusterId, buffer, bufLen)
    );
}
