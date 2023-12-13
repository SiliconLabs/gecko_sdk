/***************************************************************************//**
 * @file
 * @brief ZLL test harness functions for the Test Harness Z3 plugin.
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

//
// test-harness-z3-zll.c
//
// Wednesday, December 9, 2015
//
// ZigBee 3.0 touchlink test harness functionality
//

// -----------------------------------------------------------------------------
// Internal constants

#define EM_AF_PLUGIN_TEST_HARNESS_Z3_ZLL_SERVER_TO_CLIENT_FRAME_CONTROL \
  (ZCL_CLUSTER_SPECIFIC_COMMAND                                         \
   | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT                                 \
   | ZCL_DISABLE_DEFAULT_RESPONSE_MASK)
#define EM_AF_PLUGIN_TEST_HARNESS_Z3_ZLL_CLIENT_TO_SERVER_FRAME_CONTROL \
  (ZCL_CLUSTER_SPECIFIC_COMMAND                                         \
   | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER                                 \
   | ZCL_DISABLE_DEFAULT_RESPONSE_MASK)

// -----------------------------------------------------------------------------
// Framework-internal callbacks

void sli_zigbee_af_test_harness_z3_zll_stack_status_callback(EmberStatus status);

void sli_zigbee_af_test_harness_z3_zll_network_found_callback(const EmberZllNetwork *networkInfo);
bool sli_zigbee_af_test_harness_z3_zll_scan_complete_callback(EmberStatus status);
EmberPacketAction sli_zigbee_af_test_harness_z3_zll_command_callback(uint8_t *command,
                                                                     EmberEUI64 sourceEui64);
EmberPacketAction sli_zigbee_af_test_harness_z3_zll_modify_interpan_command(uint8_t *commandData,
                                                                            uint8_t macHeaderLength);
