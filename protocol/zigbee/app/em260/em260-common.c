/***************************************************************************//**
 * @file
 * @brief Public common code for NCP applications.
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

#include PLATFORM_HEADER

#include "stack/include/ember.h"

#include "hal/hal.h"

#include "app/util/ezsp/ezsp-enum.h"
#include "app/util/ezsp/ezsp-frame-utilities.h"
#include "stack/config/ember-configuration-defaults.h"

#define DEFAULT_TC_POLICY (EZSP_DECISION_ALLOW_JOINS | EZSP_DECISION_ALLOW_UNSECURED_REJOINS)
extern uint8_t sli_zigbee_num_multi_pan_forks;
extern uint16_t trustCenterPolicies[];

//------------------------------------------------------------------------------
// Common APIs

void sli_zigbee_xncp_init(void)
{
#ifdef EMBER_MULTI_NETWORK_STRIPPED
  trustCenterPolicies[0] = DEFAULT_TC_POLICY;
#else // EMBER_MULTI_NETWORK_STRIPPED
  for (uint8_t i = 0; i < sli_zigbee_num_multi_pan_forks; i++) {
    trustCenterPolicies[i] = DEFAULT_TC_POLICY;
  }
#endif  // EMBER_MULTI_NETWORK_STRIPPED

  EmberStatus status = emberSetRadioIeee802154CcaMode(EMBER_RADIO_802154_CCA_MODE);
  emberDebugPrintf("Init: default CCA mode set to %d: 0x%X",
                   EMBER_RADIO_802154_CCA_MODE,
                   status);
#ifndef DEBUG_ROUTINES_PRESENT
  (void)status;
#endif // DEBUG_ROUTINES_PRESENT
}

// *****************************************
// Convenience Stubs
// *****************************************

// The stub when the AF Support component is not present.
WEAK(bool sli_zigbee_af_get_endpoint_description(uint8_t endpoint,
                                                 EmberEndpointDescription *result))
{
  (void)endpoint;
  (void)result;
  // always return false if AF Support component is not present
  return false;
}

WEAK(uint16_t sli_zigbee_af_get_endpoint_cluster(uint8_t endpoint,
                                                 EmberClusterListId listId,
                                                 uint8_t listIndex))
{
  (void)endpoint;
  (void)listId;
  (void)listIndex;
  // always return 0xFFFF if AF Support component is not present
  return 0xFFFF;
}

WEAK(uint8_t sli_zigbee_af_get_endpoint(uint8_t index))
{
  (void)index;
  // always return 0xFF if AF Support component is not present
  return 0xFF;
}

// Hook from command handler for the af support related commands
WEAK(bool sli_zigbee_af_process_ezsp_af_support_commands(uint16_t commandId))
{
  (void)commandId;
  return false;
}

#ifndef __NCP_CONFIG__

#ifndef EMBER_APPLICATION_HAS_SET_OR_GET_EZSP_TOKEN_HANDLER
void emberSetOrGetEzspTokenCommandHandler(bool isSet)
{
  appendInt8u(EMBER_INVALID_CALL);
}
#endif

#endif /* __NCP_CONFIG__ */
