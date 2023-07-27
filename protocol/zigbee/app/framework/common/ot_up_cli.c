/***************************************************************************//**
 * @file ot_up_cli.c
 * @brief Silabs implementation of OpenThread CLI
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

#include "app/framework/include/af.h"
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif //SL_COMPONENT_CATALOG_PRESENT

#if defined(OPENTHREAD_FTD)
#include "dataset.h"
#include "instance.h"
#include "dataset_ftd.h"
#include "ip6.h"
#include "thread.h"
#include "history_tracker.h"
#include "ip6.h"
#include "ping_sender.h"

static otOperationalDataset sDataset;
extern otInstance *otGetInstance(void);
extern void otSysEventSignalPending(void);

typedef enum  {
  OT_CLI_INVALID = 0,
  OT_CLI_FACTORY_RESET,
  OT_CLI_THREAD_IPADDR,
  OT_CLI_THREAD_PING_IPADDR,
  OT_CLI_DATASET_INIT_NEW,
  // Below is not only a CLI command, but a way to get NVM params
  // into the dataset so it prints correctly after reset
  OT_CLI_DATASET_GET_ACTIVE,
  OT_CLI_DATASET_COMMIT_ACTIVE,
  OT_CLI_DATASET_NETWORKKEY,
  OT_CLI_DATASET_CHANNEL,
  OT_CLI_DATASET_PANID,
  OT_CLI_DATASET_EXTPANID,
  OT_CLI_IFCONFIG_UP,
  OT_CLI_THREAD_START,
  OT_CLI_THREAD_STATE,
  OT_CLI_DATASET,
} ot_cli_t;

static ot_cli_t ot_cli_to_execute = OT_CLI_DATASET_GET_ACTIVE;
static otPingSenderConfig config;
static void HandlePingStatistics(const otPingSenderStatistics *aStatistics, void *aContext);
static void HandlePingReply(const otPingSenderReply *aReply, void *aContext);

void factory_reset(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  ot_cli_to_execute = OT_CLI_FACTORY_RESET;
  otSysEventSignalPending();
}
void dataset_get_active(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  ot_cli_to_execute = OT_CLI_DATASET_GET_ACTIVE;
  otSysEventSignalPending();
}
void thread_ipaddr(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  ot_cli_to_execute = OT_CLI_THREAD_IPADDR;
  otSysEventSignalPending();
}
void thread_ping_ipaddr(sl_cli_command_arg_t *arguments)
{
  memset(&config, 0, sizeof(config));

  uint8_t length;
  uint8_t * paramPtr = sl_zigbee_cli_get_argument_string_and_length(arguments, 0, &length);

  if (length) {
    otIp6AddressFromString((char*)paramPtr, &config.mDestination);
    config.mStatisticsCallback = HandlePingStatistics;
    config.mReplyCallback      = HandlePingReply;
  } else {
    sl_zigbee_app_debug_println("Incorrect argument format");
  }
  ot_cli_to_execute = OT_CLI_THREAD_PING_IPADDR;
  otSysEventSignalPending();
}
void dataset_init_new(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  ot_cli_to_execute = OT_CLI_DATASET_INIT_NEW;
  otSysEventSignalPending();
}
void dataset_networkkey(sl_cli_command_arg_t *arguments)
{
  size_t paramLength;
  uint8_t *paramPtr;
  paramPtr = sl_cli_get_argument_hex(arguments, 0, &paramLength);
  if (paramLength == OT_NETWORK_KEY_SIZE) {
    memcpy(&sDataset.mNetworkKey.m8, paramPtr, OT_NETWORK_KEY_SIZE);
    sDataset.mComponents.mIsNetworkKeyPresent = true;
  } else {
    sl_zigbee_app_debug_println("Incorrect argument format");
  }
  ot_cli_to_execute = OT_CLI_DATASET_NETWORKKEY;
  otSysEventSignalPending();
}
void dataset_channel(sl_cli_command_arg_t *arguments)
{
  sDataset.mChannel = sl_cli_get_argument_uint8(arguments, 0);
  sDataset.mComponents.mIsChannelPresent = true;
  ot_cli_to_execute = OT_CLI_DATASET_CHANNEL;
  otSysEventSignalPending();
}
void dataset_pan_id(sl_cli_command_arg_t *arguments)
{
  sDataset.mPanId = sl_cli_get_argument_uint16(arguments, 0);
  sDataset.mComponents.mIsPanIdPresent = true;
  ot_cli_to_execute = OT_CLI_DATASET_PANID;
  otSysEventSignalPending();
}
void dataset_extended_pan_id(sl_cli_command_arg_t *arguments)
{
  size_t paramLength;
  uint8_t *paramPtr;
  paramPtr = sl_cli_get_argument_hex(arguments, 0, &paramLength);
  if (paramLength == OT_EXT_PAN_ID_SIZE) {
    memcpy(&sDataset.mExtendedPanId.m8, paramPtr, OT_EXT_PAN_ID_SIZE);
    sDataset.mComponents.mIsExtendedPanIdPresent = true;
  } else {
    sl_zigbee_app_debug_println("Incorrect argument format");
  }
  ot_cli_to_execute = OT_CLI_DATASET_EXTPANID;
  otSysEventSignalPending();
}
void dataset_commit_active(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  ot_cli_to_execute = OT_CLI_DATASET_COMMIT_ACTIVE;
  otSysEventSignalPending();
}

void ifconfig_up(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  ot_cli_to_execute = OT_CLI_IFCONFIG_UP;
  otSysEventSignalPending();
}

void thread_start(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  ot_cli_to_execute = OT_CLI_THREAD_START;
  otSysEventSignalPending();
}

void thread_state(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  ot_cli_to_execute = OT_CLI_THREAD_STATE;
  otSysEventSignalPending();
}

void OutputBytesLine(uint8_t *bytes, uint8_t bytes_len)
{
  for (uint8_t i = 0; i < bytes_len; i++) {
    sl_zigbee_app_debug_print("%02X", bytes[i]);
  }
  sl_zigbee_app_debug_print("\n");
  otSysEventSignalPending();
}
void dataset_print(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  ot_cli_to_execute = OT_CLI_DATASET;
  otSysEventSignalPending();
}

// All CLI handlers execute from the RTOS CLI task
// OpenThread APIs are not thread-safe. Therefore, we set the command
// to execute in the CLI handler and then execute the actual functionality
// from within the OT RTOS Task context. Not doing this can result in random
// symptoms whose root causes are extremely difficult to pin-point such as
// memory management, usage faults and asserts.

void sl_ot_rtos_application_tick(void)
{
  switch (ot_cli_to_execute) {
    case OT_CLI_DATASET_GET_ACTIVE:
    {
      otError error = otDatasetGetActive(otGetInstance(), &sDataset);
      sl_zigbee_app_debug_println("Dataset fetch status : 0x%0x", error);
      break;
    }
    case OT_CLI_THREAD_IPADDR:
    {
      char addressString[OT_IP6_ADDRESS_STRING_SIZE + 4];
      const otNetifAddress *unicastAddrs = otIp6GetUnicastAddresses(otGetInstance());

      for (const otNetifAddress *addr = unicastAddrs; addr; addr = addr->mNext) {
        otIp6AddressToString(&addr->mAddress, addressString, sizeof(addressString));
        if (!addr->mNext) {
          sl_zigbee_app_debug_print("IP address:%s\n", addressString);
        }
      }
      break;
    }
    case OT_CLI_FACTORY_RESET:
    {
      otInstanceFactoryReset(otGetInstance());
      break;
    }

    case OT_CLI_DATASET_INIT_NEW:
    {
      otError error = OT_ERROR_INVALID_ARGS;
      error = otDatasetCreateNewNetwork(otGetInstance(), &sDataset);
      sl_zigbee_app_debug_println("Status: 0x%0x", error);
      break;
    }

    case OT_CLI_DATASET_COMMIT_ACTIVE:
    {
      otError error = OT_ERROR_INVALID_ARGS;
      error = otDatasetSetActive(otGetInstance(), &sDataset);
      sl_zigbee_app_debug_println("Status: 0x%0x", error);
      break;
    }
    case OT_CLI_IFCONFIG_UP:
    {
      otError error = OT_ERROR_INVALID_ARGS;
      error = otIp6SetEnabled(otGetInstance(), true);
      sl_zigbee_app_debug_println("Status: 0x%0x", error);
      break;
    }

    case OT_CLI_THREAD_START:
    {
      otError error = OT_ERROR_INVALID_ARGS;
      error = otThreadSetEnabled(otGetInstance(), true);
      sl_zigbee_app_debug_println("Status: 0x%0x", error);
      break;
    }
    case OT_CLI_THREAD_STATE:
    {
      sl_zigbee_app_debug_println("%s", otThreadDeviceRoleToString(otThreadGetDeviceRole(otGetInstance())));
      break;
    }
    case OT_CLI_THREAD_PING_IPADDR:
    {
      otError error = otPingSenderPing(otGetInstance(), &config);
      sl_zigbee_app_debug_println("Status: 0x%0x", error);
      break;
    }
    case OT_CLI_DATASET:
    {
      if (sDataset.mComponents.mIsExtendedPanIdPresent) {
        sl_zigbee_app_debug_print("Ext PAN ID: ");
        OutputBytesLine(sDataset.mExtendedPanId.m8, 8);
      }

      if (sDataset.mComponents.mIsChannelPresent) {
        sl_zigbee_app_debug_println("Channel: %d", sDataset.mChannel);
      }

      if (sDataset.mComponents.mIsNetworkKeyPresent) {
        sl_zigbee_app_debug_print("Network Key: ");
        OutputBytesLine(sDataset.mNetworkKey.m8, 16);
      }

      if (sDataset.mComponents.mIsNetworkNamePresent) {
        sl_zigbee_app_debug_print("Network Name: ");
        sl_zigbee_app_debug_println("%s", sDataset.mNetworkName.m8);
      }

      if (sDataset.mComponents.mIsPanIdPresent) {
        sl_zigbee_app_debug_println("PAN ID: 0x%04X", sDataset.mPanId);
      }
      break;
    }
    default:
      break;
  }
  ot_cli_to_execute = OT_CLI_INVALID;
}
static void HandlePingStatistics(const otPingSenderStatistics *aStatistics, void *aContext)
{
  sl_zigbee_app_debug_println("%u packets transmitted, %u packets received.", aStatistics->mSentCount, aStatistics->mReceivedCount);
}
static void HandlePingReply(const otPingSenderReply *aReply, void *aContext)
{
  char addressString[OT_IP6_ADDRESS_STRING_SIZE + 4];
  otIp6AddressToString(&aReply->mSenderAddress, addressString, sizeof(addressString));
  sl_zigbee_app_debug_println("sender  %s", addressString);
}
#endif //#if defined(OPENTHREAD_FTD)
