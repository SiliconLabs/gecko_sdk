/***************************************************************************//**
 * @brief Functionality for rolling the network key by broadcasting the key update
 * and the NWK key switch messages.
 * This is the preferred mechanism for Home Automation and another networks
 * without individual link keys per device.
 *
 * The process is pretty straightforward.
 *   1. Broadcast new NWK key (randomly generated)
 *   2. Wait until the broadcast fades out of the network (~20 seconds)
 *   3. Broadcast NWK key switch message
 *
 * Note: This does not PERIODICALLY update the NWK key.  It just manages the
 * process when it is told to initate the key change.  Another software
 * module must determine the policy for periodically initiating this process
 * (such as the 'Trust Center NWK Key Update Periodic' App Framework Plugin).
 *
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories, Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of  Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software  is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include "app/framework/include/af.h"
#include "app/framework/util/common.h"
#include "app/framework/util/util.h"

#include "trust-center-nwk-key-update-broadcast.h"
#include "stack/include/zigbee-security-manager.h"

// *****************************************************************************
// Globals

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
sl_zigbee_event_t emberAfPluginTrustCenterNwkKeyUpdateBroadcastMyEvent;
#define myEvent (&emberAfPluginTrustCenterNwkKeyUpdateBroadcastMyEvent)
void emberAfPluginTrustCenterNwkKeyUpdateBroadcastMyEventHandler(sl_zigbee_event_t * event);

#if defined(SL_CATALOG_ZIGBEE_TEST_HARNESS_PRESENT)
extern EmberStatus emberAfTrustCenterStartBroadcastNetworkKeyUpdate(void);
// For testing, we need to support a single application that can do
// unicast AND broadcast key updates.  So we re-map the function name
// so both can be compiled in without conflict.
#define emberAfTrustCenterStartNetworkKeyUpdate emberAfTrustCenterStartBroadcastNetworkKeyUpdate
#endif

// *****************************************************************************

void emberAfPluginTrustCenterNwkKeyUpdateBroadcastMyEventHandler(sl_zigbee_event_t * event)
{
  EmberStatus status;
  sl_zigbee_event_set_inactive(myEvent);

  status = emberBroadcastNetworkKeySwitch();
  if (status != EMBER_SUCCESS) {
    emberAfSecurityPrintln("Failed to broadcast NWK key switch");
  }
  emberAfSecurityPrintln("Sent NWK key switch.");
  emberAfNetworkKeyUpdateCompleteCallback(status);
}

static bool nextNetworkKeyIsNewer(EmberKeyStruct* nextNwkKey)
{
  sl_status_t status;
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_key_t plaintext_key;
  sl_zb_sec_man_network_key_info_t key_info;

  sl_zb_sec_man_init_context(&context);
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_NETWORK;
  context.key_index = 1;

  status = sl_zb_sec_man_export_key(&context, &plaintext_key);
  MEMMOVE(&(nextNwkKey->key),
          &plaintext_key.key,
          EMBER_ENCRYPTION_KEY_SIZE);

  // It is assumed that the current nwk key has valid data.
  (void)sl_zb_sec_man_get_network_key_info(&key_info);
  if (status != SL_STATUS_OK
      || (timeGTorEqualInt8u(key_info.network_key_sequence_number,
                             key_info.alt_network_key_sequence_number))) {
    return false;
  }

  return true;
}

EmberStatus emberAfTrustCenterStartNetworkKeyUpdate(void)
{
  EmberKeyStruct nextNwkKey;
  EmberStatus status;

  if (emberAfGetNodeId() != EMBER_TRUST_CENTER_NODE_ID
      || emberAfNetworkState() != EMBER_JOINED_NETWORK
      || sl_zigbee_event_is_scheduled(myEvent)
      ) {
    return EMBER_INVALID_CALL;
  }

  if (!nextNetworkKeyIsNewer(&nextNwkKey)) {
    // Setting the key to all zeroes tells the stack
    // to randomly generate a new key and use that.
    MEMSET(emberKeyContents(&(nextNwkKey.key)),
           0,
           EMBER_ENCRYPTION_KEY_SIZE);
  }

  status = emberBroadcastNextNetworkKey(&(nextNwkKey.key));
  if (status != EMBER_SUCCESS) {
    emberAfSecurityPrintln("Failed to broadcast next NWK key");
  } else {
    emberAfSecurityPrintln("Broadcasting next NWK key");
    // The +2 is a fuzz factor
    sl_zigbee_event_set_delay_qs(myEvent,
                                 EMBER_BROADCAST_TABLE_TIMEOUT_QS + 2);
  }
  return status;
}

void sli_zigbee_af_trust_center_nwk_key_update_broadcast_init_callback(uint8_t init_level)
{
  (void)init_level;

  sl_zigbee_event_init(myEvent,
                       emberAfPluginTrustCenterNwkKeyUpdateBroadcastMyEventHandler);
}
