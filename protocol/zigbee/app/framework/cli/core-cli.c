/***************************************************************************//**
 * @file
 * @brief Core CLI commands used by all applications regardless of profile.
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

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#include "app/framework/include/af.h"
#include "app/framework/util/common.h"
#include "app/framework/util/af-main.h"
#include "app/util/serial/sl_zigbee_command_interpreter.h"
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#include "library.h"
#ifdef SL_CATALOG_RAIL_UTIL_IEEE802154_PHY_SELECT_PRESENT
#include "rail_ieee802154.h"
#endif
#ifdef EMBER_AF_HAS_SECURITY_PROFILE_SE
  #include "stack/include/cbke-crypto-engine.h"  // emberGetCertificate()
#endif

#ifdef SL_CATALOG_KERNEL_PRESENT
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#endif //#ifdef SL_CATALOG_KERNEL_PRESENT

extern uint8_t sli_zigbee_af_cli_network_index;

#ifdef SL_CATALOG_ZIGBEE_TEST_HARNESS_Z3_PRESENT
extern void sli_get_ztt_version_number_string(char *versionString);
#endif

#ifdef SL_CATALOG_RAIL_UTIL_IEEE802154_PHY_SELECT_PRESENT
void  sli_get_pti_radio_config(sl_cli_command_arg_t *arguments)
{
  sl_zigbee_core_debug_println("Current Config: %0x", RAIL_IEEE802154_GetPtiRadioConfig(emberGetRailHandle()));
}

#endif

void sli_zigbee_cli_config_cca_mode_command(sl_cli_command_arg_t *arguments)
{
  uint8_t ccaMode = sl_cli_get_argument_uint8(arguments, 0);
  EmberStatus status = emberSetRadioIeee802154CcaMode(ccaMode);
  sl_zigbee_core_debug_println("Set CCA mode to %d: %0x",
                               ccaMode,
                               status);
}

void sli_cli_pre_cmd_hook(sl_cli_command_arg_t* arguments)
{
  (void)arguments;
  emberAfPushNetworkIndex(sli_zigbee_af_cli_network_index);

#if defined(SL_CATALOG_BLUETOOTH_PRESENT)
  //Do not lock/unlock kernel for BLE commands
  uint8_t cmd_count = sl_cli_get_command_count(arguments);
  if (cmd_count >= 2) {
    char *cmd1_ptr = sl_cli_get_command_string(arguments, 0);
    char *cmd2_ptr =  sl_cli_get_command_string(arguments, 1);
    // condition below should be true for any cli that starts with plug ble
    // strncmp returns 0 when the comparison results in a match
    if ( (strncmp(cmd1_ptr, "plug", 4) == 0) && (strncmp(cmd2_ptr, "ble", 3) == 0) ) {
      return;
    }
  }
#endif //#if defined(SL_CATALOG_BLUETOOTH_PRESENT)

  // Lock OS kernel to prevent CLI task from calling ember functions
  // CLI task is lower priority than zigbee and can be preempted
  #if defined(SL_CATALOG_KERNEL_PRESENT)
  (void)osKernelLock();
  #endif //#if defined(SL_CATALOG_KERNEL_PRESENT)
}
void sli_cli_post_cmd_hook(sl_cli_command_arg_t* arguments)
{
  (void)arguments;

  emberAfPopNetworkIndex();

#if defined(EMBER_QA)
  sl_zigbee_core_debug_println("CLI Finished");
#endif

#ifdef SL_CATALOG_KERNEL_PRESENT
  (void)osKernelUnlock();
#endif //#ifdef SL_CATALOG_KERNEL_PRESENT

#ifdef SL_CATALOG_KERNEL_PRESENT
  // After every CLI command we wake up the ZigBee task so that it can be
  // processed in a timely fashion.
  sl_zigbee_common_rtos_wakeup_stack_task();
#endif // SL_CATALOG_KERNEL_PRESENT
}

#if !defined SL_CATALOG_ZIGBEE_TEST_HARNESS_Z3_PRESENT || defined EMBER_TEST
static void printMfgString(void)
{
  uint8_t mfgString[MFG_STRING_MAX_LENGTH + 1];
  emberAfFormatMfgString(mfgString);

  // Note: We use '%s' here because this is a RAM string. Normally,
  // most strings are literals or constants in flash and use '%p'.
  sl_zigbee_core_debug_print("MFG String: %s", mfgString);
}
#endif

static void printPacketBuffers(void)
{
  sl_zigbee_core_debug_println("Buffs: %d / %d",
                               sli_zigbee_af_get_packet_buffer_free_count(),
                               sli_zigbee_af_get_packet_buffer_total_count());
}

static bool printSmartEnergySecurityInfo(void)
{
#ifdef EMBER_AF_HAS_SECURITY_PROFILE_SE
  bool securityGood = true;
  sl_zigbee_core_debug_print("SE Security Info [");
  {
    // For SE security, print the state of ECC, CBKE, and the programmed Cert.
    EmberCertificateData cert;
    EmberStatus status = emberGetCertificate(&cert);

    // Check the status of the ECC library.
    if ((emberGetLibraryStatus(EMBER_ECC_LIBRARY_ID)
         & EMBER_LIBRARY_PRESENT_MASK) != 0U) {
      sl_zigbee_core_debug_print("Real163k1ECC ");
    } else {
      sl_zigbee_core_debug_print("No163k1ECC ");
      securityGood = false;
    }

    // Status of EMBER_LIBRARY_NOT_PRESENT means the CBKE is not present
    // in the image and that no information is known about the certificate.
    if (status == EMBER_LIBRARY_NOT_PRESENT) {
      sl_zigbee_core_debug_print("No163k1Cbke UnknownCert ");
      securityGood = false;
    } else {
      sl_zigbee_core_debug_print("Real163k1Cbke ");

      // Status of EMBER_SUCCESS means the Cert is good.
      if (status == EMBER_SUCCESS) {
        sl_zigbee_core_debug_print("GoodCert");
      }
      // Status of EMBER_ERR_FATAL means the Cert failed.
      else if (status == EMBER_ERR_FATAL) {
        sl_zigbee_core_debug_print("BadCert");
        securityGood = false;
      } else {
        // MISRA requires ..else if.. to have a terminating else.
      }
    }
    sl_zigbee_core_debug_println("]");
  }
  emberAfAppFlush();
  return securityGood;
#else
  return false;
#endif
}

static bool printSmartEnergySecurityInfo283k1(void)
{
#ifdef EMBER_AF_HAS_SECURITY_PROFILE_SE
  bool securityGood = true;
  sl_zigbee_core_debug_print("SE Security 283k1 Info [");
  {
    // For SE security, print the state of ECC, CBKE, and the programmed Cert.
    EmberCertificate283k1Data cert;
    // This is a temporary step until the EZSP frames are added
    // to the EZSP code.
    EmberStatus status = EMBER_LIBRARY_NOT_PRESENT;
    status = emberGetCertificate283k1(&cert);
    // Check the status of the ECC library.
    if ((emberGetLibraryStatus(EMBER_ECC_LIBRARY_283K1_ID)
         & EMBER_LIBRARY_PRESENT_MASK) != 0U) {
      sl_zigbee_core_debug_print("Real283k1ECC ");
    } else {
      sl_zigbee_core_debug_print("No283k1ECC ");
      securityGood = false;
    }

    // Status of EMBER_LIBRARY_NOT_PRESENT means the CBKE is not present
    // in the image and that no information is known about the certificate.
    if (status == EMBER_LIBRARY_NOT_PRESENT) {
      sl_zigbee_core_debug_print("No283k1Cbke UnknownCert");
      securityGood = false;
    } else {
      sl_zigbee_core_debug_print("Real283k1Cbke ");

      // Status of EMBER_SUCCESS means the Cert is good.
      if (status == EMBER_SUCCESS) {
        sl_zigbee_core_debug_print("GoodCert");
      }
      // Status of EMBER_ERR_FATAL means the Cert failed.
      else if (status == EMBER_ERR_FATAL) {
        sl_zigbee_core_debug_print("BadCert");
        securityGood = false;
      } else {
        // MISRA requires ..else if.. to have a terminating else.
      }
    }
    sl_zigbee_core_debug_println("]");
  }
  emberAfAppFlush();
  return securityGood;
#else
  return false;
#endif
}
#if defined(EMBER_TEST) && !defined(EZSP_HOST)
extern void blacklist_mask(uint32_t channel_mask);
void blackListCommand(sl_cli_command_arg_t *arguments)
{
  uint32_t channel_mask = sl_cli_get_argument_uint32(arguments, 0);
  blacklist_mask(channel_mask);
}
#endif

#if defined SL_CATALOG_ZIGBEE_TEST_HARNESS_Z3_PRESENT && !defined EMBER_TEST
// ZTT Firmware application version - displayed on LCD (for WSTK) and for "info" command.

void sli_get_ztt_version_number_string(char *versionString)
{
  MEMCOPY(versionString, ZTT_FIRMWARE_APPLICATION_VERSION, strlen(ZTT_FIRMWARE_APPLICATION_VERSION));
}
#endif

void sli_zigbee_af_cli_info_command(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  EmberNodeType nodeTypeResult = 0xFF;
  EmberEUI64 myEui64;
  EmberNetworkParameters networkParams;
  uint8_t numPhyInterfaces;
#if defined SL_CATALOG_ZIGBEE_TEST_HARNESS_Z3_PRESENT && !defined EMBER_TEST
  char versionString[10] = { 0 };
  sli_get_ztt_version_number_string(versionString);
  sl_zigbee_app_debug_println("Silicon Labs ZTT Firmware Application v%p", versionString);
#else
  printMfgString();
#endif
  sl_zigbee_core_debug_println("AppBuilder MFG Code: 0x%04X", EMBER_AF_MANUFACTURER_CODE);
  emberAfGetEui64(myEui64);
  emberAfGetNetworkParameters(&nodeTypeResult, &networkParams);
  sl_zigbee_core_debug_print("node [");
  emberAfAppDebugExec(emberAfPrintBigEndianEui64(myEui64));
  emberAfAppFlush();
  sl_zigbee_core_debug_println("] chan [%d] pwr [%d]",
                               networkParams.radioChannel,
                               networkParams.radioTxPower);

  numPhyInterfaces = emberGetPhyInterfaceCount();

  if ((numPhyInterfaces > 1) && (255 != numPhyInterfaces)) {
    EmberMultiPhyRadioParameters multiPhyRadioParams;
    uint8_t i;
    EmberStatus status;

    sl_zigbee_core_debug_println("Additional interfaces");
    for (i = 1; i < numPhyInterfaces; ++i) {
      sl_zigbee_core_debug_print("  %d: ", i);
      status = emberGetRadioParameters(i, &multiPhyRadioParams);
      switch (status) {
        case EMBER_SUCCESS:
          sl_zigbee_core_debug_println("page [%d] chan [%d] pwr [%d]",
                                       multiPhyRadioParams.radioPage,
                                       multiPhyRadioParams.radioChannel,
                                       multiPhyRadioParams.radioTxPower);
          break;
        case EMBER_NETWORK_DOWN:
        case EMBER_NOT_JOINED:
          sl_zigbee_core_debug_println("not active");
          break;
        default:
          sl_zigbee_core_debug_println("error 0x%2X", status);
          break;
      }
    }
  }

  sl_zigbee_core_debug_print("panID [0x%04X] nodeID [0x%04X] ",
                             networkParams.panId,
                             emberAfGetNodeId());
  emberAfAppFlush();
  sl_zigbee_core_debug_print("xpan [0x");
  emberAfAppDebugExec(emberAfPrintBigEndianEui64(networkParams.extendedPanId));
  sl_zigbee_core_debug_println("]");
  emberAfAppFlush();

  #ifndef EZSP_HOST
  sl_zigbee_core_debug_println("parentID [0x%04X] parentRssi [%d]", emberGetParentId(), emberGetAvgParentRssi());
  emberAfAppFlush();
  #endif // EZSP_HOST

#if !defined SL_CATALOG_ZIGBEE_TEST_HARNESS_Z3_PRESENT
  sli_zigbee_af_cli_version_command();
#endif

  sl_zigbee_core_debug_print("nodeType [");
  if (nodeTypeResult != 0xFF) {
    sl_zigbee_core_debug_print("0x%02X", nodeTypeResult);
  } else {
    sl_zigbee_core_debug_print("unknown");
  }
  sl_zigbee_core_debug_println("]");
  emberAfAppFlush();

  sl_zigbee_core_debug_println("Security level [%x]", emberAfGetSecurityLevel());

  printSmartEnergySecurityInfo();
  printSmartEnergySecurityInfo283k1();

  sl_zigbee_core_debug_print("network state [%02X] ", emberNetworkState());
  printPacketBuffers();

  // EMZIGBEE-5125: apps with lots of endpoints will wdog while printing
  halResetWatchdog();
  // Print the endpoint information.
  {
    uint8_t i, j;
    sl_zigbee_core_debug_println("Ep cnt: %d", emberAfEndpointCount());
    // Loop for each endpoint.
    for (i = 0; i < emberAfEndpointCount(); i++) {
      EmberAfEndpointType *et = sli_zigbee_af_endpoints[i].endpointType;
      sl_zigbee_core_debug_print("ep %d [endpoint %s, device %s] ",
                                 emberAfEndpointFromIndex(i),
                                 (emberAfEndpointIndexIsEnabled(i)
                                  ? "enabled"
                                  : "disabled"),
                                 (emberAfIsDeviceEnabled(emberAfEndpointFromIndex(i))
                                  ? "enabled"
                                  : "disabled"));
      sl_zigbee_core_debug_println("nwk [%d] profile [0x%04X] devId [0x%04X] ver [0x%x]",
                                   emberAfNetworkIndexFromEndpointIndex(i),
                                   emberAfProfileIdFromIndex(i),
                                   emberAfDeviceIdFromIndex(i),
                                   emberAfDeviceVersionFromIndex(i));
      // Loop for the clusters within the endpoint.
      for (j = 0; j < et->clusterCount; j++) {
        EmberAfCluster *zc = &(et->cluster[j]);
        sl_zigbee_core_debug_print("    %s cluster: 0x%04X ",
                                   (emberAfClusterIsClient(zc)
                                    ? "out(client)"
                                    : "in (server)"),
                                   zc->clusterId);
        emberAfAppDebugExec(emberAfDecodeAndPrintClusterWithMfgCode(zc->clusterId, sli_zigbee_af_get_manufacturer_code_for_cluster(zc)));
        sl_zigbee_core_debug_println("");
        emberAfAppFlush();
      }
      emberAfAppFlush();
      // EMZIGBEE-5125
      halResetWatchdog();
    }
    // EMZIGBEE-5125
    halResetWatchdog();
  }

  {
    const char * names[] = {
      EMBER_AF_GENERATED_NETWORK_STRINGS
    };
    uint8_t i;
    sl_zigbee_core_debug_println("Nwk cnt: %d", EMBER_SUPPORTED_NETWORKS);
    for (i = 0; i < EMBER_SUPPORTED_NETWORKS; i++) {
      emberAfPushNetworkIndex(i);
      sl_zigbee_core_debug_println("nwk %d [%s]", i, names[i]);
      if (sli_zigbee_af_pro_is_current_network()) {
        sl_zigbee_core_debug_println("  nodeType [0x%02X]",
                                     sli_zigbee_af_current_zigbee_pro_network->nodeType);
        sl_zigbee_core_debug_println("  securityProfile [0x%02X]",
                                     sli_zigbee_af_current_zigbee_pro_network->securityProfile);
      }
      emberAfPopNetworkIndex();
    }
  }
}

void sli_zigbee_cli_version_command(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  // Print the Version
  sli_zigbee_af_cli_version_command();
}

void resetCommand(sl_cli_command_arg_t *arguments)
{
  halReboot();
}

void endpointPrint(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
  uint8_t i;
  for (i = 0; i < emberAfEndpointCount(); i++) {
    sl_zigbee_core_debug_print("EP %d: %s ",
                               sli_zigbee_af_endpoints[i].endpoint,
                               (emberAfEndpointIndexIsEnabled(i)
                                ? "Enabled"
                                : "Disabled"));
    sli_zigbee_af_print_ezsp_endpoint_flags(sli_zigbee_af_endpoints[i].endpoint);
    sl_zigbee_core_debug_println("");
  }
}

void enableDisableEndpoint(sl_cli_command_arg_t *arguments)
{
  uint8_t endpoint = (uint8_t)sl_cli_get_argument_uint32(arguments, 0);
  bool enable = (sl_cli_get_command_string(arguments, 1)[0] == 'e'
                 ? true
                 : false);
  if (!emberAfEndpointEnableDisable(endpoint,
                                    enable)) {
    sl_zigbee_core_debug_println("Error:  Unknown endpoint.");
  }
}

#if SL_ZIGBEE_EVENT_DEBUG_ENABLED
#ifndef EVENT_QUEUE_LIST_END
#define EVENT_QUEUE_LIST_END ((EmberEvent *) 1)
#endif
#endif

void printEvents(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
#if SL_ZIGBEE_EVENT_DEBUG_ENABLED

  EmberEvent *finger = sli_zigbee_af_app_event_queue.events;

  while (finger != EVENT_QUEUE_LIST_END) {
    sl_zigbee_core_debug_print("Event %s : ", (finger->actions.name == NULL
                                               ? "?"
                                               : finger->actions.name));
    // Get NWK Index
    if (sli_zigbee_event_is_network_event(finger)) {
      sl_zigbee_core_debug_print("NWK %d : ", sli_zigbee_event_get_network_index(finger));
    }

    // Get Endpoint
    if (sli_zigbee_event_is_endpoint_event(finger)) {
      sl_zigbee_core_debug_print("EP %d : ", sli_zigbee_event_get_endpoint(finger));
    }

    // Get Remaining Time
    sl_zigbee_core_debug_println("%d ms", sl_zigbee_event_get_remaining_ms(finger));
    finger = finger->next;
  }
#else
  sl_zigbee_core_debug_print("Enable event debug info in Core CLI component");
#endif // SL_ZIGBEE_EVENT_DEBUG_ENABLED
}
