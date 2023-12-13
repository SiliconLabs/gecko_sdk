/*****************************************************************************/
/**
 * Copyright 2021 Silicon Laboratories, Inc.
 *
 *****************************************************************************/
//
// *** Generated file. Do not edit! ***
//
// Description: Handlers for the EZSP frames that directly correspond to Ember
// API calls.

#include PLATFORM_HEADER
#include "stack/include/ember-types.h"
#include "ezsp-enum.h"
#include "app/em260/command-context.h"
#include "stack/include/cbke-crypto-engine.h"
#include "stack/include/zigbee-security-manager.h"
#include "stack/include/mfglib.h"
#include "stack/include/binding-table.h"
#include "stack/include/message.h"
#include "app/util/ezsp/ezsp-frame-utilities.h"
#include "app/em260/command-handlers-cbke.h"
#include "app/em260/command-handlers-binding.h"
#include "app/em260/command-handlers-mfglib.h"
#include "app/em260/command-handlers-security.h"
#include "app/em260/command-handlers-zll.h"
#include "app/em260/command-handlers-zigbee-pro.h"
#include "child.h"
#include "message.h"
#include "zll-api.h"
#include "security.h"
#include "stack-info.h"
#include "network-formation.h"
#include "zigbee-device-stack.h"
#include "ember-duty-cycle.h"
#include "multi-phy.h"
#include "stack/gp/gp-sink-table.h"
#include "stack/gp/gp-proxy-table.h"

bool sli_zigbee_af_process_ezsp_command_security(uint16_t commandId)
{
  switch (commandId) {
//------------------------------------------------------------------------------

    case EZSP_SET_INITIAL_SECURITY_STATE: {
      EmberStatus success;
      EmberInitialSecurityState state;
      fetchEmberInitialSecurityState(&state);
      success = emberSetInitialSecurityState(&state);
      appendInt8u(success);
      break;
    }

    case EZSP_GET_CURRENT_SECURITY_STATE: {
      EmberStatus status;
      EmberCurrentSecurityState state;
      status = emberGetCurrentSecurityState(&state);
      appendInt8u(status);
      appendEmberCurrentSecurityState(&state);
      break;
    }

    case EZSP_EXPORT_KEY: {
      sl_zb_sec_man_context_t context;
      sl_zb_sec_man_key_t key;
      sl_status_t status;
      fetch_sl_zb_sec_man_context_t(&context);
      emberExportKey(&context, &key, status);
      append_sl_zb_sec_man_key_t(&key);
      appendInt32u(status);
      break;
    }

    case EZSP_IMPORT_KEY: {
      sl_status_t status;
      sl_zb_sec_man_context_t context;
      sl_zb_sec_man_key_t key;
      fetch_sl_zb_sec_man_context_t(&context);
      fetch_sl_zb_sec_man_key_t(&key);
      status = emberImportKey(&context, &key);
      appendInt32u(status);
      break;
    }

    case EZSP_FIND_KEY_TABLE_ENTRY: {
      uint8_t index;
      uint8_t address[8];
      bool linkKey;
      fetchInt8uArray(8, address);
      linkKey = fetchInt8u();
      index = emberFindKeyTableEntry(address, linkKey);
      appendInt8u(index);
      break;
    }

    case EZSP_SEND_TRUST_CENTER_LINK_KEY: {
      EmberStatus status;
      EmberNodeId destinationNodeId;
      uint8_t destinationEui64[8];
      destinationNodeId = fetchInt16u();
      fetchInt8uArray(8, destinationEui64);
      status = emberSendTrustCenterLinkKey(destinationNodeId, destinationEui64);
      appendInt8u(status);
      break;
    }

    case EZSP_ERASE_KEY_TABLE_ENTRY: {
      EmberStatus status;
      uint8_t index;
      index = fetchInt8u();
      status = emberEraseKeyTableEntry(index);
      appendInt8u(status);
      break;
    }

    case EZSP_CLEAR_KEY_TABLE: {
      EmberStatus status;
      status = emberClearKeyTable();
      appendInt8u(status);
      break;
    }

    case EZSP_REQUEST_LINK_KEY: {
      EmberStatus status;
      uint8_t partner[8];
      fetchInt8uArray(8, partner);
      status = emberRequestLinkKey(partner);
      appendInt8u(status);
      break;
    }

    case EZSP_UPDATE_TC_LINK_KEY: {
      EmberStatus status;
      uint8_t maxAttempts;
      maxAttempts = fetchInt8u();
      status = emberUpdateTcLinkKey(maxAttempts);
      appendInt8u(status);
      break;
    }

    case EZSP_CLEAR_TRANSIENT_LINK_KEYS: {
      emberClearTransientLinkKeys();
      break;
    }

    case EZSP_GET_NETWORK_KEY_INFO: {
      sl_status_t status;
      sl_zb_sec_man_network_key_info_t network_key_info;
      status = emberGetNetworkKeyInfo(&network_key_info);
      appendInt32u(status);
      append_sl_zb_sec_man_network_key_info_t(&network_key_info);
      break;
    }

    case EZSP_GET_APS_KEY_INFO: {
      sl_zb_sec_man_context_t context_in;
      uint8_t eui[8];
      sl_zb_sec_man_aps_key_metadata_t key_data;
      sl_status_t status;
      fetch_sl_zb_sec_man_context_t(&context_in);
      emberGetApsKeyInfo(&context_in, eui, &key_data, status);
      appendInt8uArray(8, eui);
      append_sl_zb_sec_man_aps_key_metadata_t(&key_data);
      appendInt32u(status);
      break;
    }

    case EZSP_IMPORT_LINK_KEY: {
      sl_status_t status;
      uint8_t index;
      uint8_t address[8];
      sl_zb_sec_man_key_t plaintext_key;
      index = fetchInt8u();
      fetchInt8uArray(8, address);
      fetch_sl_zb_sec_man_key_t(&plaintext_key);
      status = emberImportLinkKey(index, address, &plaintext_key);
      appendInt32u(status);
      break;
    }

    case EZSP_EXPORT_LINK_KEY_BY_INDEX: {
      uint8_t index;
      uint8_t eui[8];
      sl_zb_sec_man_key_t plaintext_key;
      sl_zb_sec_man_aps_key_metadata_t key_data;
      sl_status_t status;
      index = fetchInt8u();
      emberExportLinkKeyByIndex(index, eui, &plaintext_key, &key_data, status);
      appendInt8uArray(8, eui);
      append_sl_zb_sec_man_key_t(&plaintext_key);
      append_sl_zb_sec_man_aps_key_metadata_t(&key_data);
      appendInt32u(status);
      break;
    }

    case EZSP_EXPORT_LINK_KEY_BY_EUI: {
      uint8_t eui[8];
      sl_zb_sec_man_key_t plaintext_key;
      uint8_t index;
      sl_zb_sec_man_aps_key_metadata_t key_data;
      sl_status_t status;
      fetchInt8uArray(8, eui);
      emberExportLinkKeyByEui(eui, &plaintext_key, index, &key_data, status);
      append_sl_zb_sec_man_key_t(&plaintext_key);
      appendInt8u(index);
      append_sl_zb_sec_man_aps_key_metadata_t(&key_data);
      appendInt32u(status);
      break;
    }

    case EZSP_CHECK_KEY_CONTEXT: {
      sl_status_t status;
      sl_zb_sec_man_context_t context;
      fetch_sl_zb_sec_man_context_t(&context);
      status = emberCheckKeyContext(&context);
      appendInt32u(status);
      break;
    }

    case EZSP_IMPORT_TRANSIENT_KEY: {
      sl_status_t status;
      uint8_t eui64[8];
      sl_zb_sec_man_key_t plaintext_key;
      sl_zigbee_sec_man_flags_t flags;
      fetchInt8uArray(8, eui64);
      fetch_sl_zb_sec_man_key_t(&plaintext_key);
      flags = fetchInt8u();
      status = emberImportTransientKey(eui64, &plaintext_key, flags);
      appendInt32u(status);
      break;
    }

    case EZSP_EXPORT_TRANSIENT_KEY_BY_INDEX: {
      uint8_t index;
      sl_zb_sec_man_context_t context;
      sl_zb_sec_man_key_t plaintext_key;
      sl_zb_sec_man_aps_key_metadata_t key_data;
      sl_status_t status;
      index = fetchInt8u();
      emberExportTransientKeyByIndex(index, &context, &plaintext_key, &key_data, status);
      append_sl_zb_sec_man_context_t(&context);
      append_sl_zb_sec_man_key_t(&plaintext_key);
      append_sl_zb_sec_man_aps_key_metadata_t(&key_data);
      appendInt32u(status);
      break;
    }

    case EZSP_EXPORT_TRANSIENT_KEY_BY_EUI: {
      uint8_t eui[8];
      sl_zb_sec_man_context_t context;
      sl_zb_sec_man_key_t plaintext_key;
      sl_zb_sec_man_aps_key_metadata_t key_data;
      sl_status_t status;
      fetchInt8uArray(8, eui);
      emberExportTransientKeyByEui(eui, &context, &plaintext_key, &key_data, status);
      append_sl_zb_sec_man_context_t(&context);
      append_sl_zb_sec_man_key_t(&plaintext_key);
      append_sl_zb_sec_man_aps_key_metadata_t(&key_data);
      appendInt32u(status);
      break;
    }

//------------------------------------------------------------------------------

    default: {
      return false;
    }
  }

  return true;
}
