/***************************************************************************//**
 * @brief Enumerations for vNCP.
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

// *** Generated file. Do not edit! ***
// vNCP Version: 1.0

#ifndef __CSP_API_ENUM_GEN_H__
#define __CSP_API_ENUM_GEN_H__

#define VNCP_CMD_ID 0x6900 //i
#define STACK_CALLBACK_ID 0x6300 //c

#define VNCP_VERSION 0x0100
//------------------------------------------------------------------------------
// Frame IDs
enum {
// Core
  EMBER_NETWORK_STATE_IPC_COMMAND_ID                                   = VNCP_CMD_ID + 0x02,
  EMBER_STACK_IS_UP_IPC_COMMAND_ID                                     = VNCP_CMD_ID + 0x03,
  EMBER_SET_SECURITY_KEY_IPC_COMMAND_ID                                = VNCP_CMD_ID + 0x04,
  EMBER_GET_SECURITY_KEY_IPC_COMMAND_ID                                = VNCP_CMD_ID + 0x4F,
  EMBER_SET_PSA_SECURITY_KEY_IPC_COMMAND_ID                            = VNCP_CMD_ID + 0x4C,
  EMBER_REMOVE_PSA_SECURITY_KEY_IPC_COMMAND_ID                         = VNCP_CMD_ID + 0x4D,
  EMBER_SET_NCP_SECURITY_KEY_PERSISTENT_IPC_COMMAND_ID                 = VNCP_CMD_ID + 0x52,
  EMBER_SET_NCP_SECURITY_KEY_IPC_COMMAND_ID                            = VNCP_CMD_ID + 0x4E,
  EMBER_GET_KEY_ID_IPC_COMMAND_ID                                      = VNCP_CMD_ID + 0x50,
  EMBER_GET_COUNTER_IPC_COMMAND_ID                                     = VNCP_CMD_ID + 0x05,
  EMBER_SET_RADIO_CHANNEL_EXTENDED_IPC_COMMAND_ID                      = VNCP_CMD_ID + 0x4B,
  EMBER_SET_RADIO_CHANNEL_IPC_COMMAND_ID                               = VNCP_CMD_ID + 0x06,
  EMBER_GET_RADIO_CHANNEL_IPC_COMMAND_ID                               = VNCP_CMD_ID + 0x07,
  EMBER_SET_RADIO_POWER_IPC_COMMAND_ID                                 = VNCP_CMD_ID + 0x08,
  EMBER_GET_RADIO_POWER_IPC_COMMAND_ID                                 = VNCP_CMD_ID + 0x09,
  EMBER_SET_RADIO_POWER_MODE_IPC_COMMAND_ID                            = VNCP_CMD_ID + 0x0A,
  EMBER_SET_MAC_PARAMS_IPC_COMMAND_ID                                  = VNCP_CMD_ID + 0x0B,
  EMBER_CURRENT_STACK_TASKS_IPC_COMMAND_ID                             = VNCP_CMD_ID + 0x0C,
  EMBER_OK_TO_NAP_IPC_COMMAND_ID                                       = VNCP_CMD_ID + 0x0D,
  EMBER_OK_TO_HIBERNATE_IPC_COMMAND_ID                                 = VNCP_CMD_ID + 0x0E,
  EMBER_GET_EUI64_IPC_COMMAND_ID                                       = VNCP_CMD_ID + 0x0F,
  EMBER_MAC_GET_PARENT_ADDRESS_IPC_COMMAND_ID                          = VNCP_CMD_ID + 0x3A,
  EMBER_IS_LOCAL_EUI64_IPC_COMMAND_ID                                  = VNCP_CMD_ID + 0x10,
  EMBER_GET_NODE_ID_IPC_COMMAND_ID                                     = VNCP_CMD_ID + 0x11,
  EMBER_GET_PAN_ID_IPC_COMMAND_ID                                      = VNCP_CMD_ID + 0x12,
  EMBER_GET_PARENT_ID_IPC_COMMAND_ID                                   = VNCP_CMD_ID + 0x13,
  EMBER_GET_NODE_TYPE_IPC_COMMAND_ID                                   = VNCP_CMD_ID + 0x14,
  EMBER_GET_CSP_VERSION_IPC_COMMAND_ID                                 = VNCP_CMD_ID + 0x15,
  EMBER_CALIBRATE_CURRENT_CHANNEL_IPC_COMMAND_ID                       = VNCP_CMD_ID + 0x2F,
  EMBER_CALIBRATE_CURRENT_CHANNEL_EXTENDED_IPC_COMMAND_ID              = VNCP_CMD_ID + 0x46,
  EMBER_APPLY_IR_CALIBRATION_IPC_COMMAND_ID                            = VNCP_CMD_ID + 0x47,
  EMBER_TEMP_CALIBRATION_IPC_COMMAND_ID                                = VNCP_CMD_ID + 0x48,
  EMBER_GET_CAL_TYPE_IPC_COMMAND_ID                                    = VNCP_CMD_ID + 0x49,
  EMBER_GET_MAXIMUM_PAYLOAD_LENGTH_IPC_COMMAND_ID                      = VNCP_CMD_ID + 0x30,
  EMBER_SET_INDIRECT_QUEUE_TIMEOUT_IPC_COMMAND_ID                      = VNCP_CMD_ID + 0x4A,
  EMBER_GET_VERSION_INFO_IPC_COMMAND_ID                                = VNCP_CMD_ID + 0x53,
  EMBER_STACK_STATUS_HANDLER_IPC_COMMAND_ID                            = STACK_CALLBACK_ID + 0x00,
  EMBER_CHILD_JOIN_HANDLER_IPC_COMMAND_ID                              = STACK_CALLBACK_ID + 0x01,
  EMBER_RADIO_NEEDS_CALIBRATING_HANDLER_IPC_COMMAND_ID                 = STACK_CALLBACK_ID + 0x30,
// Messaging
  EMBER_MESSAGE_SEND_IPC_COMMAND_ID                                    = VNCP_CMD_ID + 0x16,
  EMBER_POLL_FOR_DATA_IPC_COMMAND_ID                                   = VNCP_CMD_ID + 0x17,
  EMBER_MAC_MESSAGE_SEND_IPC_COMMAND_ID                                = VNCP_CMD_ID + 0x2B,
  EMBER_MAC_SET_PAN_COORDINATOR_IPC_COMMAND_ID                         = VNCP_CMD_ID + 0x38,
  EMBER_SET_POLL_DESTINATION_ADDRESS_IPC_COMMAND_ID                    = VNCP_CMD_ID + 0x2D,
  EMBER_REMOVE_CHILD_IPC_COMMAND_ID                                    = VNCP_CMD_ID + 0x31,
  EMBER_GET_CHILD_FLAGS_IPC_COMMAND_ID                                 = VNCP_CMD_ID + 0x32,
  EMBER_GET_CHILD_INFO_IPC_COMMAND_ID                                  = VNCP_CMD_ID + 0x33,
  EMBER_PURGE_INDIRECT_MESSAGES_IPC_COMMAND_ID                         = VNCP_CMD_ID + 0x2E,
  EMBER_MAC_ADD_SHORT_TO_LONG_ADDRESS_MAPPING_IPC_COMMAND_ID           = VNCP_CMD_ID + 0x3E,
  EMBER_MAC_CLEAR_SHORT_TO_LONG_ADDRESS_MAPPINGS_IPC_COMMAND_ID        = VNCP_CMD_ID + 0x3F,
  EMBER_NETWORK_LEAVE_IPC_COMMAND_ID                                   = VNCP_CMD_ID + 0x40,
  EMBER_MESSAGE_SENT_HANDLER_IPC_COMMAND_ID                            = STACK_CALLBACK_ID + 0x02,
  EMBER_INCOMING_MESSAGE_HANDLER_IPC_COMMAND_ID                        = STACK_CALLBACK_ID + 0x03,
  EMBER_INCOMING_MAC_MESSAGE_HANDLER_IPC_COMMAND_ID                    = STACK_CALLBACK_ID + 0x0B,
  EMBER_MAC_MESSAGE_SENT_HANDLER_IPC_COMMAND_ID                        = STACK_CALLBACK_ID + 0x0C,
// Network Management
  EMBER_NETWORK_INIT_IPC_COMMAND_ID                                    = VNCP_CMD_ID + 0x18,
  EMBER_START_ACTIVE_SCAN_IPC_COMMAND_ID                               = VNCP_CMD_ID + 0x19,
  EMBER_START_ENERGY_SCAN_IPC_COMMAND_ID                               = VNCP_CMD_ID + 0x1A,
  EMBER_SET_APPLICATION_BEACON_PAYLOAD_IPC_COMMAND_ID                  = VNCP_CMD_ID + 0x1B,
  EMBER_SET_SELECTIVE_JOIN_PAYLOAD_IPC_COMMAND_ID                      = VNCP_CMD_ID + 0x3C,
  EMBER_CLEAR_SELECTIVE_JOIN_PAYLOAD_IPC_COMMAND_ID                    = VNCP_CMD_ID + 0x3D,
  EMBER_FORM_NETWORK_IPC_COMMAND_ID                                    = VNCP_CMD_ID + 0x1C,
  EMBER_JOIN_NETWORK_EXTENDED_IPC_COMMAND_ID                           = VNCP_CMD_ID + 0x1D,
  EMBER_JOIN_NETWORK_IPC_COMMAND_ID                                    = VNCP_CMD_ID + 0x1E,
  EMBER_MAC_FORM_NETWORK_IPC_COMMAND_ID                                = VNCP_CMD_ID + 0x3B,
  EMBER_PERMIT_JOINING_IPC_COMMAND_ID                                  = VNCP_CMD_ID + 0x1F,
  EMBER_JOIN_COMMISSIONED_IPC_COMMAND_ID                               = VNCP_CMD_ID + 0x20,
  EMBER_RESET_NETWORK_STATE_IPC_COMMAND_ID                             = VNCP_CMD_ID + 0x21,
  EMBER_GET_STANDALONE_BOOTLOADER_INFO_IPC_COMMAND_ID                  = VNCP_CMD_ID + 0x22,
  EMBER_LAUNCH_STANDALONE_BOOTLOADER_IPC_COMMAND_ID                    = VNCP_CMD_ID + 0x23,
  EMBER_FREQUENCY_HOPPING_SET_CHANNEL_MASK_IPC_COMMAND_ID              = VNCP_CMD_ID + 0x2C,
  EMBER_FREQUENCY_HOPPING_START_SERVER_IPC_COMMAND_ID                  = VNCP_CMD_ID + 0x26,
  EMBER_FREQUENCY_HOPPING_START_CLIENT_IPC_COMMAND_ID                  = VNCP_CMD_ID + 0x27,
  EMBER_FREQUENCY_HOPPING_STOP_IPC_COMMAND_ID                          = VNCP_CMD_ID + 0x28,
  EMBER_SET_AUXILIARY_ADDRESS_FILTERING_ENTRY_IPC_COMMAND_ID           = VNCP_CMD_ID + 0x29,
  EMBER_GET_AUXILIARY_ADDRESS_FILTERING_ENTRY_IPC_COMMAND_ID           = VNCP_CMD_ID + 0x2A,
  EMBER_START_TX_STREAM_IPC_COMMAND_ID                                 = VNCP_CMD_ID + 0x43,
  EMBER_STOP_TX_STREAM_IPC_COMMAND_ID                                  = VNCP_CMD_ID + 0x44,
  EMBER_SET_ACTIVE_SCAN_DURATION_IPC_COMMAND_ID                        = VNCP_CMD_ID + 0x41,
  EMBER_GET_ACTIVE_SCAN_DURATION_IPC_COMMAND_ID                        = VNCP_CMD_ID + 0x42,
  EMBER_GET_DEFAULT_CHANNEL_IPC_COMMAND_ID                             = VNCP_CMD_ID + 0x45,
  EMBER_INCOMING_BEACON_HANDLER_IPC_COMMAND_ID                         = STACK_CALLBACK_ID + 0x39,
  EMBER_ACTIVE_SCAN_COMPLETE_HANDLER_IPC_COMMAND_ID                    = STACK_CALLBACK_ID + 0x05,
  EMBER_ENERGY_SCAN_COMPLETE_HANDLER_IPC_COMMAND_ID                    = STACK_CALLBACK_ID + 0x06,
  EMBER_GET_STANDALONE_BOOTLOADER_INFO_RETURN_IPC_COMMAND_ID           = STACK_CALLBACK_ID + 0x07,
  EMBER_LAUNCH_STANDALONE_BOOTLOADER_RETURN_IPC_COMMAND_ID             = STACK_CALLBACK_ID + 0x08,
  EMBER_FREQUENCY_HOPPING_START_CLIENT_COMPLETE_HANDLER_IPC_COMMAND_ID = STACK_CALLBACK_ID + 0x0A,
// EMBER_TEST
  EMBER_ECHO_IPC_COMMAND_ID                                            = VNCP_CMD_ID + 0x24,
  EMBER_ECHO_RETURN_IPC_COMMAND_ID                                     = STACK_CALLBACK_ID + 0x09,
// APP_USES_SOFTWARE_FLOW_CONTROL
  EMBER_START_XON_XOFF_TEST_IPC_COMMAND_ID                             = VNCP_CMD_ID + 0x25,
};

#endif // __CSP_API_ENUM_GEN_H__
