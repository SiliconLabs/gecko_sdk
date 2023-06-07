/***************************************************************************//**
 * @file
 * @brief CLI for the DRLC plugin.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "app/framework/include/af.h"
#include "app/framework/plugin/drlc-server/drlc-server.h"

// plugin drlc-server slce <endpoint:1> <index:1> <length:1> <load control event bytes>
// load control event bytes are expected as 23 raw bytes in the form
// {<eventId:4> <deviceClass:2> <ueg:1> <startTime:4> <duration:2> <criticalityLevel:1>
//  <coolingTempOffset:1> <heatingTempOffset:1> <coolingTempSetPoint:2> <heatingTempSetPoint:2>
//  <afgLoadPercentage:1> <dutyCycle:1> <eventControl:1> } all multibyte values should be
// little endian as though they were coming over the air.
// Example: plug drlc-server slce 0 23 { ab 00 00 00 ff 0f 00 00 00 00 00 01 00 01 00 00 09 1a 09 1a 0a 00 }
void emberAfPluginDrlcServerSlceCommand(sl_cli_command_arg_t *arguments)
{
  EmberAfLoadControlEvent event;
  EmberStatus status;
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  uint8_t index = sl_cli_get_argument_uint8(arguments, 1);
  uint8_t length = sl_cli_get_argument_uint8(arguments, 2);
  uint8_t slceBuffer[sizeof(EmberAfLoadControlEvent)];
  status = sli_zigbee_af_get_scheduled_load_control_event(endpoint, index, &event);

  if (status != EMBER_SUCCESS) {
    emberAfDemandResponseLoadControlClusterPrintln("slce fail: 0x%x", status);
    return;
  }
  if (length > sizeof(EmberAfLoadControlEvent)) {
    emberAfDemandResponseLoadControlClusterPrintln("slce fail, length: %x, max: %x", length, sizeof(EmberAfLoadControlEvent));
    return;
  }

  sl_zigbee_copy_hex_arg(arguments, 3, slceBuffer, length, false);

  event.eventId = emberAfGetInt32u(slceBuffer, 0, length);
  event.deviceClass = emberAfGetInt16u(slceBuffer, 4, length);
  event.utilityEnrollmentGroup = emberAfGetInt8u(slceBuffer, 6, length);
  event.startTime = emberAfGetInt32u(slceBuffer, 7, length);
  event.duration = emberAfGetInt16u(slceBuffer, 11, length);
  event.criticalityLevel = emberAfGetInt8u(slceBuffer, 13, length);
  event.coolingTempOffset = emberAfGetInt8u(slceBuffer, 14, length);
  event.heatingTempOffset = emberAfGetInt8u(slceBuffer, 15, length);
  event.coolingTempSetPoint = emberAfGetInt16u(slceBuffer, 16, length);
  event.heatingTempSetPoint = emberAfGetInt16u(slceBuffer, 18, length);
  event.avgLoadPercentage = emberAfGetInt8u(slceBuffer, 20, length);
  event.dutyCycle = emberAfGetInt8u(slceBuffer, 21, length);
  event.eventControl = emberAfGetInt8u(slceBuffer, 22, length);
  event.source[0] = 0x00; //activate the event in the table
  status = sli_zigbee_af_set_scheduled_load_control_event(endpoint, index, &event);
  emberAfDemandResponseLoadControlClusterPrintln("DRLC event scheduled on server: 0x%x", status);
}

// plugin drlc-server lce-schedule-mand <endpoint:1> <index:1> <eventId:4> <class:2> <ueg:1> <startTime:4>
//                <durationMins:2> <criticalLevel:1> <eventCtrl:1>
void emberAfPluginDrlcServerScheduleMandatoryLce(sl_cli_command_arg_t *arguments)
{
  EmberAfLoadControlEvent event;
  EmberStatus status;

  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  uint8_t index = sl_cli_get_argument_uint8(arguments, 1);
  status = sli_zigbee_af_get_scheduled_load_control_event(endpoint, index, &event);
  if ( status != EMBER_SUCCESS ) {
    emberAfDemandResponseLoadControlClusterPrintln("Error: Get LCE status=0x%x", status);
  }
  event.eventId                 = sl_cli_get_argument_uint32(arguments, 2);
  event.deviceClass             = sl_cli_get_argument_uint16(arguments, 3);
  event.utilityEnrollmentGroup  = sl_cli_get_argument_uint8(arguments, 4);
  event.startTime               = sl_cli_get_argument_uint32(arguments, 5);
  event.duration                = sl_cli_get_argument_uint16(arguments, 6);
  event.criticalityLevel        = sl_cli_get_argument_uint8(arguments, 7);
  event.eventControl            = sl_cli_get_argument_uint8(arguments, 8);
  // Optionals
  event.coolingTempOffset = 0xFF;
  event.heatingTempOffset = 0xFF;
  event.coolingTempSetPoint = 0x8000;
  event.heatingTempSetPoint = 0x8000;
  event.avgLoadPercentage = 0x80;
  event.dutyCycle = 0xFF;

  event.source[0] = 0x00; //activate the event in the table
  status = sli_zigbee_af_set_scheduled_load_control_event(endpoint, index, &event);
  if ( status == EMBER_SUCCESS ) {
    emberAfDemandResponseLoadControlClusterPrintln("DRLC event scheduled");
  } else {
    emberAfDemandResponseLoadControlClusterPrintln("Error: Schedule DRLC event: 0x%x", status);
  }
}

// plugin drlc-server sslce <nodeId:2> <srcEndpoint:1> <dstEndpoint:1> <index:1>
void emberAfPluginDrlcServerSslceCommand(sl_cli_command_arg_t *arguments)
{
  sli_zigbee_af_drlc_server_slce_message((EmberNodeId)sl_cli_get_argument_uint16(arguments, 0),
                                         sl_cli_get_argument_uint8(arguments, 1),
                                         sl_cli_get_argument_uint8(arguments, 2),
                                         sl_cli_get_argument_uint8(arguments, 3));
}
// plugin drlc-server print <endpoint:1>
void emberAfPluginDrlcServerPrintCommand(sl_cli_command_arg_t *arguments)
{
  sli_zigbee_af_drlc_server_print_info(sl_cli_get_argument_uint8(arguments, 0));
}

// plugin drlc-server cslce <endpoint:1>
void emberAfPluginDrlcServerCslceCommand(sl_cli_command_arg_t *arguments)
{
  sli_zigbee_af_clear_scheduled_load_control_events(sl_cli_get_argument_uint8(arguments, 0));
}
