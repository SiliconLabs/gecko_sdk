/*****************************************************************************/
/**
 * Copyright 2021 Silicon Laboratories, Inc.
 *
 *****************************************************************************/
//
// Originally generated using Studio and AFv6 apps, now hand mantained
//
// Description: Handlers for the EZSP frames that directly correspond to Ember
// API calls.

#include PLATFORM_HEADER
#include "stack/include/ember-types.h"
#include "app/em260/command-context.h"
#include "stack/include/cbke-crypto-engine.h"
#include "stack/include/mfglib.h"
#include "stack/include/binding-table.h"
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

extern void halReboot(void);
#ifdef EMBER_TEST
#define halReboot()
#endif // EMBER_TEST

// Extern for the auto generated handler as specified in the ezsp.yaml
extern bool sli_zigbee_af_process_ezsp_command_token_interface(uint16_t commandId);

// The handler that is not generated as specified in the ezsp.yaml
static void emberAfTokenInterfaceSetOrGetEzspHandler(bool set)
{
  uint32_t token = fetchInt32u();
  uint32_t index = fetchInt32u();
  if (!set) {
    EmberTokenData tokenData;
    tokenData.data = ezspWritePointer + 1 + 4;
    EmberStatus status = emberGetTokenData(token,
                                           index,
                                           &tokenData);
    appendInt8u(status);
    appendInt32u(tokenData.size);
    ezspWritePointer = ezspWritePointer + tokenData.size;
  } else {
    EmberTokenData tokenData;
    tokenData.size = fetchInt32u();
    tokenData.data = ezspReadPointer;
    EmberStatus status = emberSetTokenData(token,
                                           index,
                                           &tokenData);
    appendInt8u(status);
  }
}

// Hook from command handler for the Token interface commands
bool sli_zigbee_af_process_ezsp_token_interface_commands(uint16_t commandId)
{
  switch (commandId) {
    case EZSP_RESET_NODE:
      halReboot();
      break;
    case EZSP_SET_TOKEN_DATA:
    case EZSP_GET_TOKEN_DATA:
      emberAfTokenInterfaceSetOrGetEzspHandler(commandId
                                               == EZSP_SET_TOKEN_DATA);
      break;
    default:
      return sli_zigbee_af_process_ezsp_command_token_interface(commandId);
      break;
  }
  return true;
}
