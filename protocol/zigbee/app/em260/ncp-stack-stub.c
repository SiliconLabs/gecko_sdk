/***************************************************************************//**
 * @file
 * @brief NCP stack stubs.
 * This is a generic file which provides the STACK stub definitions for NCP
 * if the respective component is not present in application.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#include "stack/include/ember-types.h"
#include "app/util/ezsp/ezsp-frame-utilities.h"
#include "stack/include/stack-info.h"
#ifndef SL_CATALOG_ZIGBEE_BINDING_TABLE_PRESENT
WEAK(bool sli_zigbee_af_process_ezsp_command_binding(uint16_t commandId))
{
  (void)commandId;
  return false;
}
#endif  // SL_CATALOG_ZIGBEE_BINDING_TABLE_PRESENT

#ifndef SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT
WEAK(bool sli_zigbee_af_process_ezsp_command_zll(uint16_t commandId))
{
  (void)commandId;
  return false;
}
#endif  // SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT

#ifndef SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT
WEAK(bool sli_zigbee_af_process_ezsp_command_green_power(uint16_t commandId))
{
  (void)commandId;
  return false;
}
#endif

#ifndef SL_CATALOG_ZIGBEE_MFGLIB_PRESENT
WEAK(bool sli_zigbee_af_process_ezsp_command_mfglib(uint16_t commandId))
{
  (void)commandId;
  return false;
}
#endif

#ifndef SL_CATALOG_ZIGBEE_CBKE_CORE_PRESENT
WEAK(bool sli_zigbee_af_process_ezsp_command_certificate_based_key_exchange_cbke(uint16_t commandId))
{
  (void)commandId;
  appendInt8u(EMBER_LIBRARY_NOT_PRESENT);
  return true;
}
#endif  // SL_CATALOG_ZIGBEE_CBKE_CORE_PRESENT

// ToDo: Change this catalog option to stack_common after EMZIGBEE-7033
// gets merged to migration branch.
#ifndef SL_CATALOG_ZIGBEE_STACK_COMMON_PRESENT
bool sli_zigbee_af_process_ezsp_command_messaging(uint16_t commandId)
{
  (void)commandId;
  return false;
}

bool sli_zigbee_af_process_ezsp_command_networking(uint16_t commandId)
{
  (void)commandId;
  return false;
}

bool sli_zigbee_af_process_ezsp_command_security(uint16_t commandId)
{
  (void)commandId;
  return false;
}

bool sli_zigbee_af_process_ezsp_command_trust_center(uint16_t commandId)
{
  (void)commandId;
  return false;
}
#endif  // SL_CATALOG_ZIGBEE_STACK_COMMON_PRESENT

// The weak stub for the command-handler when the token interface
// component is not present.
WEAK(bool sli_zigbee_af_process_ezsp_token_interface_commands(uint16_t commandId))
{
  (void)commandId;
  return false;
}

// The stub when the cbke is not present.
WEAK(void sli_zigbee_mark_command_handler_cbke_buffers(void))
{
}
