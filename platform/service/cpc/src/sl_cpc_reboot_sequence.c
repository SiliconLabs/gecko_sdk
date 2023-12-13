/***************************************************************************/ /**
 * @file
 * @brief CPC Primary Reboot Sequence implementation.
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include "sl_cpc_weak_prototypes.h"
#include "sli_cpc_fwu.h"
#include "sli_cpc_reboot_sequence.h"
#include "sli_cpc_bootloader.h"
#include "sl_cpc_system_primary.h"
#include "sli_cpc_system_primary.h"
#include "sli_cpc.h"
#include "sli_cpc_trace.h"
#include "sli_cpc_drv.h"
#if defined(SL_CATALOG_CPC_DRIVER_UART_PRESENT)
#include "sl_cpc_drv_uart_config.h"
#endif

#include <string.h>
#include <inttypes.h>

static bool ignore_reset_reason = true;
static bool set_reset_mode_ack = false;
static bool reset_ack = false;
static bool reset_reason_received = false;
static bool rx_capability_received = false;
static bool tx_capability_transmited = false;
static bool protocol_version_received = false;
static bool capabilities_received = false;
static bool secondary_cpc_version_received = false;
static bool bootloader_info_received_or_not_available = false;
static bool secondary_bus_max_bitrate_received = false;
static bool failed_to_receive_secondary_bus_max_bitrate = false;
static bool secondary_app_version_received_or_not_available = false;

static char *secondary_app_version = NULL;
static uint16_t rx_capability = 0;
static uint8_t  secondary_protocol_version = 0;
static uint32_t capabilities = 0;
static sl_cpc_bootloader_t secondary_bootloader_type = SL_CPC_BOOTLOADER_UNKNOWN;

static enum {
  SET_NORMAL_REBOOT_MODE,
  WAIT_NORMAL_REBOOT_MODE_ACK,
  WAIT_NORMAL_RESET_ACK,
  WAIT_RESET_REASON,
  WAIT_FOR_CAPABILITIES,
  WAIT_FOR_RX_CAPABILITY,
  WAIT_FOR_TX_CAPABILITY,
  WAIT_FOR_BOOTLOADER_INFO,
  WAIT_FOR_SECONDARY_CPC_VERSION,
  WAIT_FOR_SECONDARY_APP_VERSION,
  WAIT_FOR_PROTOCOL_VERSION,
  WAIT_FOR_SECONDARY_BUS_MAX_BITRATE,
  RESET_SEQUENCE_DONE,
  RESET_SEQUENCE_NOT_OK_TO_RUN
}
#if defined(SLI_CPC_DEVICE_UNDER_TEST)
// Skip reset sequence in Unit tests
reset_sequence_state = RESET_SEQUENCE_DONE;
#else
reset_sequence_state = SET_NORMAL_REBOOT_MODE;
#endif

static enum {
  SET_BOOTLOADER_REBOOT_MODE,
  WAIT_BOOTLOADER_REBOOT_MODE_ACK,
  WAIT_BOOTLOADER_RESET_ACK,
  RESET_BOOTLOADER_SEQUENCE_DONE
} reset_bootloader_sequence_state = SET_BOOTLOADER_REBOOT_MODE;

static sli_cpc_system_reboot_mode_t pending_reboot_mode;

static void property_set_reset_mode_callback(sli_cpc_property_id_t property_id,
                                             void *property_value,
                                             size_t property_length,
                                             void *on_reply_arg,
                                             sl_status_t status);

void reset_callback(sl_status_t status,
                    sl_cpc_system_status_t reset_status);

static void property_get_rx_capability_callback(sli_cpc_property_id_t property_id,
                                                void *property_value,
                                                size_t property_length,
                                                void *on_reply_arg,
                                                sl_status_t status);

static void property_set_tx_capability_callback(sli_cpc_property_id_t property_id,
                                                void *property_value,
                                                size_t property_length,
                                                void *on_reply_arg,
                                                sl_status_t status);

static void property_get_protocol_version_callback(sli_cpc_property_id_t property_id,
                                                   void *property_value,
                                                   size_t property_length,
                                                   void *on_reply_arg,
                                                   sl_status_t status);

static void property_get_capabilities_callback(sli_cpc_property_id_t property_id,
                                               void *property_value,
                                               size_t property_length,
                                               void *on_reply_arg,
                                               sl_status_t status);

static void property_get_secondary_cpc_version_callback(sli_cpc_property_id_t property_id,
                                                        void *property_value,
                                                        size_t property_length,
                                                        void *on_reply_arg,
                                                        sl_status_t status);

static void property_get_secondary_bootloader_info_callback(sli_cpc_property_id_t property_id,
                                                            void *property_value,
                                                            size_t property_length,
                                                            void *on_reply_arg,
                                                            sl_status_t status);

static void property_get_secondary_bus_max_bitrate_callback(sli_cpc_property_id_t property_id,
                                                            void *property_value,
                                                            size_t property_length,
                                                            void *on_reply_arg,
                                                            sl_status_t status);

static void property_get_secondary_app_version_callback(sli_cpc_property_id_t property_id,
                                                        void *property_value,
                                                        size_t property_length,
                                                        void *on_reply_arg,
                                                        sl_status_t status);

/***************************************************************************/ /**
 * Perform checks between the protocol version of the secondary and the primary
 ******************************************************************************/
static void protocol_version_check(void)
{
  if (secondary_protocol_version != SLI_CPC_PROTOCOL_VERSION) {
    WARN("Secondary Protocol v%u doesn't match Primary Protocol v%u",
         secondary_protocol_version, SLI_CPC_PROTOCOL_VERSION);
    extern bool secondary_protocol_version_mismatch;
    secondary_protocol_version_mismatch = true;
  }
}

/***************************************************************************/ /**
 * Perform checks between the version of the secondary and the primary
 *
 * @return is ok to run, or if app version mismatch, is it still okay to run
 ******************************************************************************/
static bool application_version_check(void)
{
  const char * primary_app_version = sl_cpc_primary_app_version();

  if (primary_app_version && secondary_app_version) {
    if (strcmp(primary_app_version, secondary_app_version) != 0) {
      WARN("Secondary APP v%s doesn't match the provided APP v%s",
           secondary_app_version, primary_app_version);

      if (sl_cpc_user_is_ok_to_run) {
        if (sl_cpc_user_is_ok_to_run(primary_app_version, secondary_app_version)) {
          extern bool secondary_application_version_mismatch;
          secondary_application_version_mismatch = true;
          return false;
        }
      }
    }
  }

  return true;
}

/***************************************************************************/ /**
 * Perform checks between the capabilities of the secondary and the primary
 ******************************************************************************/
static void capabilities_checks(void)
{
  extern bool secondary_capabilities_mismatch;

#if defined(SL_CATALOG_CPC_SECURITY_PRESENT)
  const bool use_encryption = true;
#else
  const bool use_encryption = false;
#endif

#if defined(SL_CATALOG_CPC_DRIVER_UART_PRESENT)
  bool uart_hardflow = false;

#if defined(SL_CPC_DRV_PERIPH_IS_EUSART) && (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == eusartHwFlowControlCtsAndRts_D)
  uart_hardflow = true;
#elif defined(SL_CPC_DRV_PERIPH_IS_USART) && (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == usartHwFlowControlCtsAndRts_D)
  uart_hardflow = true;
#endif

  if (uart_hardflow != (bool)(capabilities & CPC_CAPABILITIES_UART_FLOW_CONTROL_MASK)) {
    WARN("UART flow control configuration mismatch between Primary (%s) and Secondary (%s)",
         uart_hardflow ? "enabled" : "disabled",
         (bool)(capabilities & CPC_CAPABILITIES_UART_FLOW_CONTROL_MASK) ? "enabled" : "disabled");
    secondary_capabilities_mismatch = true;
  }
#endif

  if (use_encryption != (bool)(capabilities & CPC_CAPABILITIES_SECURITY_ENDPOINT_MASK)) {
    WARN("Security configuration mismatch between Primary (%s) and Secondary (%s)",
         use_encryption ? "enabled" : "disabled",
         (bool)(capabilities & CPC_CAPABILITIES_SECURITY_ENDPOINT_MASK) ? "enabled" : "disabled");
    secondary_capabilities_mismatch = true;
  }
}

/***************************************************************************/ /**
 * Returns the state of the reset sequence
 *
 * @return Whether the reset and boot sequence is completed
 ******************************************************************************/
bool sli_cpc_reboot_is_sequence_done(void)
{
  return reset_sequence_state == RESET_SEQUENCE_DONE;
}

/***************************************************************************/ /**
 * Returns the state of the reset bootloader sequence
 *
 * @return Whether the secondary has rebooted in bootloader mode or not
 ******************************************************************************/
bool sli_cpc_reboot_is_bootloader_sequence_done(void)
{
  return reset_bootloader_sequence_state == RESET_BOOTLOADER_SEQUENCE_DONE;
}

/***************************************************************************/ /**
 * Returns whether or not the Gecko bootlaoder has been detected on the secondary
 ******************************************************************************/
bool sli_cpc_is_gecko_bootloader_present(void)
{
  return secondary_bootloader_type == SL_CPC_BOOTLOADER_GECKO;
}

/***************************************************************************/ /**
 * Reset state machine of the reboot sequence to re-run it
 ******************************************************************************/
void sli_cpc_reboot_sequence_start(void)
{
  reset_sequence_state = SET_NORMAL_REBOOT_MODE;

  ignore_reset_reason = true;
  set_reset_mode_ack = false;
  reset_ack = false;
  reset_reason_received = false;
  rx_capability_received = false;
  tx_capability_transmited = false;
  protocol_version_received = false;
  capabilities_received = false;
  secondary_cpc_version_received = false;
  bootloader_info_received_or_not_available = false;
  secondary_bus_max_bitrate_received = false;
  failed_to_receive_secondary_bus_max_bitrate = false;
  secondary_app_version_received_or_not_available = false;

  free(secondary_app_version);
  secondary_app_version = NULL;

  rx_capability = 0;
  secondary_protocol_version = 0;
  capabilities = 0;
  secondary_bootloader_type = SL_CPC_BOOTLOADER_UNKNOWN;
}

/***************************************************************************/ /**
 * The bare metal process action function.
 ******************************************************************************/
void sli_cpc_reboot_sequence_process(void)
{
  sl_status_t status;

  switch (reset_sequence_state) {
    case RESET_SEQUENCE_DONE:
      return;

    case SET_NORMAL_REBOOT_MODE:
      PRINT_INFO("Connecting to Secondary...");

      // Send a request to the secondary to set the reboot mode to 'application'
      // Keep track that the reboot mode that was requested is application mode
      pending_reboot_mode = REBOOT_APPLICATION;

      status = sli_cpc_system_cmd_property_set(property_set_reset_mode_callback,
                                               NULL,
                                               PROP_BOOTLOADER_REBOOT_MODE,
                                               1,      // retry once
                                               2000,   // 2s between retries
                                               &pending_reboot_mode,
                                               sizeof(pending_reboot_mode),
                                               SYSTEM_EP_UFRAME);

      if (status == SL_STATUS_OK) {
        reset_sequence_state = WAIT_NORMAL_REBOOT_MODE_ACK;
        TRACE_RESET("Reboot mode sent");
      }
      break;

    case WAIT_NORMAL_REBOOT_MODE_ACK:
      if (set_reset_mode_ack == true) {
        // request a reset
        status = sli_cpc_system_cmd_reboot(reset_callback,
                                           NULL,
                                           5,    // 5 retries
                                           1000  // 1s between retries
                                           );

        if (status == SL_STATUS_OK) {
          reset_sequence_state = WAIT_NORMAL_RESET_ACK;

          // Set it back to false because it will be used for the bootloader reboot sequence
          set_reset_mode_ack = false;

          TRACE_RESET("Reboot mode reply received, reset request sent");
        }
      }
      break;

    case WAIT_NORMAL_RESET_ACK:

      if (reset_ack == true) {
        reset_sequence_state = WAIT_RESET_REASON;

        // Set it back to false because it will be used for the bootloader reboot sequence
        reset_ack = false;

        TRACE_RESET("Reset request acknowledged");
      }
      break;

    case WAIT_RESET_REASON:

      TRACE_RESET("Waiting for reset reason");

      if (reset_reason_received) {
        TRACE_RESET("Reset reason received");

        status = sli_cpc_system_cmd_property_get(property_get_rx_capability_callback,
                                                 NULL,
                                                 PROP_RX_CAPABILITY,
                                                 5,     // 5 retries
                                                 1000,  // 1s between retries
                                                 SYSTEM_EP_UFRAME);
        if (status == SL_STATUS_OK) {
          reset_sequence_state = WAIT_FOR_RX_CAPABILITY;
        }
      }
      break;

    case WAIT_FOR_RX_CAPABILITY:
      if (rx_capability_received) {
        TRACE_RESET("Obtained RX capability");

        const uint16_t tx_capability = SL_CPC_RX_PAYLOAD_MAX_LENGTH;
        status = sli_cpc_system_cmd_property_set(property_set_tx_capability_callback,
                                                 NULL,
                                                 PROP_TX_CAPABILITY,
                                                 5,      // 5 retries
                                                 1000,   // 1s between retries
                                                 &tx_capability,
                                                 sizeof(pending_reboot_mode),
                                                 SYSTEM_EP_UFRAME);
        if (status == SL_STATUS_OK) {
          reset_sequence_state = WAIT_FOR_TX_CAPABILITY;
        }
      }
      break;

    case WAIT_FOR_TX_CAPABILITY:
      if (tx_capability_transmited) {
        TRACE_RESET("Transmitted TX capability");
        PRINT_INFO("Connected to Secondary");

        status = sli_cpc_system_cmd_property_get(property_get_protocol_version_callback,
                                                 NULL,
                                                 PROP_PROTOCOL_VERSION,
                                                 5,      // 5 retries
                                                 1000,   // 1s between retries
                                                 SYSTEM_EP_UFRAME);
        if (status == SL_STATUS_OK) {
          reset_sequence_state = WAIT_FOR_PROTOCOL_VERSION;
        }
      }
      break;

    case WAIT_FOR_PROTOCOL_VERSION:
      if (protocol_version_received) {
        TRACE_RESET("Obtained Protocol version");

        protocol_version_check();

        status = sli_cpc_system_cmd_property_get(property_get_capabilities_callback,
                                                 NULL,
                                                 PROP_CAPABILITIES,
                                                 5,      // 5 retries
                                                 1000,   // 1s between retries
                                                 SYSTEM_EP_UFRAME);
        if (status == SL_STATUS_OK) {
          reset_sequence_state = WAIT_FOR_CAPABILITIES;
        }
      }
      break;

    case WAIT_FOR_CAPABILITIES:
      if (capabilities_received) {
        TRACE_RESET("Obtained Capabilities");

        capabilities_checks();

        status = sli_cpc_system_cmd_property_get(property_get_secondary_bootloader_info_callback,
                                                 NULL,
                                                 PROP_BOOTLOADER_INFO,
                                                 5,       // 5 retries
                                                 100000,  // 1s between retries
                                                 SYSTEM_EP_UFRAME);
        if (status == SL_STATUS_OK) {
          reset_sequence_state = WAIT_FOR_BOOTLOADER_INFO;
        }
      }
      break;

    case WAIT_FOR_BOOTLOADER_INFO:
      if (bootloader_info_received_or_not_available) {
        TRACE_RESET("Obtained secondary bootloader information");

        status = sli_cpc_system_cmd_property_get(property_get_secondary_cpc_version_callback,
                                                 NULL,
                                                 PROP_SECONDARY_CPC_VERSION,
                                                 5,       // 5 retries
                                                 100000,  // 1s between retries
                                                 SYSTEM_EP_UFRAME);
        if (status == SL_STATUS_OK) {
          reset_sequence_state = WAIT_FOR_SECONDARY_CPC_VERSION;
        }
      }
      break;

    case WAIT_FOR_SECONDARY_CPC_VERSION:
      if (secondary_cpc_version_received) {
        TRACE_RESET("Obtained Secondary CPC version");

        status = sli_cpc_system_cmd_property_get(property_get_secondary_bus_max_bitrate_callback,
                                                 NULL,
                                                 PROP_BUS_MAX_BITRATE_VALUE,
                                                 5,       // 5 retries
                                                 100000,  // 1s between retries
                                                 SYSTEM_EP_UFRAME);
        if (status == SL_STATUS_OK) {
          reset_sequence_state = WAIT_FOR_SECONDARY_BUS_MAX_BITRATE;
        }
      }
      break;

    case WAIT_FOR_SECONDARY_BUS_MAX_BITRATE:
      if (secondary_bus_max_bitrate_received || failed_to_receive_secondary_bus_max_bitrate) {
        status = sli_cpc_system_cmd_property_get(property_get_secondary_app_version_callback,
                                                 NULL,
                                                 PROP_SECONDARY_APP_VERSION,
                                                 5,       // 5 retries
                                                 100000,  // 1s between retries
                                                 SYSTEM_EP_UFRAME);
        if (status == SL_STATUS_OK) {
          reset_sequence_state = WAIT_FOR_SECONDARY_APP_VERSION;
        }
      }
      break;

    case WAIT_FOR_SECONDARY_APP_VERSION:
      if (secondary_app_version_received_or_not_available) {
        if (secondary_app_version) {
          TRACE_RESET("Obtained Secondary APP version");
        }

        bool ok_to_run = application_version_check();

        if (!ok_to_run) {
          // By setting the reset sequence state to RESET_SEQUENCE_NOT_OK_TO_RUN, we are
          // blocking CPC from running, thus preventing the app from running.
          // The user will likely then do a firmware upgrade in this scenario
          reset_sequence_state = RESET_SEQUENCE_NOT_OK_TO_RUN;
        } else {
          reset_sequence_state = RESET_SEQUENCE_DONE;

#if defined(ENABLE_ENCRYPTION)
          security_init();
#endif
          PRINT_INFO("Primary startup was successful. Waiting for client connections");
        }
      }
      break;

    case RESET_SEQUENCE_NOT_OK_TO_RUN:
      // Do nothing, stay in this state to prevent the user from engaging with the CPC API since the app is not ok to run.
      // TODO CPC-1166 still allow for firmware update
      break;

    default:
      BUG();
      break;
  }
}

/***************************************************************************/ /**
 * The callback when a reply to a property set reset mode is received
 ******************************************************************************/
static void property_set_reset_mode_callback(sli_cpc_property_id_t property_id,
                                             void* property_value,
                                             size_t property_length,
                                             void *on_reply_arg,
                                             sl_status_t status)
{
  (void) on_reply_arg;
  (void) property_id;

  switch (status) {
    case SL_STATUS_IN_PROGRESS:
    case SL_STATUS_OK:

      EFM_ASSERT(property_length == sizeof(sli_cpc_system_reboot_mode_t));

      sli_cpc_system_reboot_mode_t* mode = (sli_cpc_system_reboot_mode_t*) property_value;

      switch (*mode) {
        case REBOOT_APPLICATION:
          // Make sure the secondary confirms it will reboot into application
          EFM_ASSERT(pending_reboot_mode == REBOOT_APPLICATION);
          break;
        case REBOOT_BOOTLOADER:
          // Make sure the secondary confirms it will reboot into bootloader
          EFM_ASSERT(pending_reboot_mode == REBOOT_BOOTLOADER);
          break;
        default:
          EFM_ASSERT(false);
          break;
      }

      set_reset_mode_ack = true;
      break;

    case SL_STATUS_TIMEOUT:
    case SL_STATUS_ABORT:
      PRINT_INFO("Failed to connect, secondary seems unresponsive");

      ignore_reset_reason = false; // Don't ignore a secondary that resets
      reset_sequence_state = SET_NORMAL_REBOOT_MODE;
      break;
    default:
      // Un-handled property_set_reset_mode_callback status
      EFM_ASSERT(false);
      break;
  }
}

/***************************************************************************/ /**
 * The callback when a reply to a reset command is received
 ******************************************************************************/
void reset_callback(sl_status_t status,
                    sl_cpc_system_status_t reset_status)
{
  ignore_reset_reason = false;

  switch (status) {
    case SL_STATUS_IN_PROGRESS:
    case SL_STATUS_OK:

      TRACE_RESET("Reset request response received : %ld", reset_status);

      if (reset_status == SL_STATUS_OK) {
        reset_ack = true;
      }
      break;

    case SL_STATUS_TIMEOUT:
    case SL_STATUS_ABORT:
      TRACE_RESET("Failed to reset Secondary");
      ignore_reset_reason = false; // Don't ignore a secondary that resets
      reset_sequence_state = SET_NORMAL_REBOOT_MODE;
      break;
    default:
      // Un-handled reset_callback status
      EFM_ASSERT(false);
      break;
  }
}

/***************************************************************************/ /**
 * The callback when an unsolicited last status is received
 ******************************************************************************/
void sl_cpc_system_unsolicited_last_status_callback(sl_cpc_system_status_t status)
{
  if (ignore_reset_reason) {
    ignore_reset_reason = false;
    TRACE_RESET("Ignored reset reason : %lu", status);
    return;
  }

  if (status <= STATUS_RESET_WATCHDOG && status >= STATUS_RESET_POWER_ON) {
    TRACE_RESET("Received reset reason : %lu", status);
    TRACE_RESET("Reset sequence: %u", reset_sequence_state);

    if (reset_sequence_state == WAIT_RESET_REASON) {
      reset_reason_received = true;
    } else {
      //TODO CPC-847: deal with the scenario where the secondary has reset spuriously later.
      sli_cpc_system_notify_reset(status);
    }
  }
}

/***************************************************************************/ /**
 * The callback when a reply to a property get rx capability is received
 ******************************************************************************/
static void property_get_rx_capability_callback(sli_cpc_property_id_t property_id,
                                                void *property_value,
                                                size_t property_length,
                                                void *on_reply_arg,
                                                sl_status_t status)
{
  (void)on_reply_arg;

  EFM_ASSERT(property_id == PROP_RX_CAPABILITY);
  EFM_ASSERT(status == SL_STATUS_OK || status == SL_STATUS_IN_PROGRESS);
  EFM_ASSERT(property_value != NULL && property_length == sizeof(uint16_t));

  rx_capability = *((uint16_t *)property_value);
  rx_capability_received = true;

  sli_cpc_set_remote_tx_max_payload_length(rx_capability);

  PRINT_INFO("RX capability is %u bytes", rx_capability);
}

/***************************************************************************/ /**
 * The callback when a reply to a property set tx capability is received
 ******************************************************************************/
static void property_set_tx_capability_callback(sli_cpc_property_id_t property_id,
                                                void *property_value,
                                                size_t property_length,
                                                void *on_reply_arg,
                                                sl_status_t status)
{
  (void)on_reply_arg;

  EFM_ASSERT(property_id == PROP_TX_CAPABILITY);
  EFM_ASSERT(status == SL_STATUS_OK || status == SL_STATUS_IN_PROGRESS);
  EFM_ASSERT(property_value != NULL && property_length == sizeof(uint16_t));
  EFM_ASSERT(*(uint16_t*)property_value == SL_CPC_RX_PAYLOAD_MAX_LENGTH);

  tx_capability_transmited = true;
}

/***************************************************************************/ /**
 * The callback when a reply to a property get protocol version is received
 ******************************************************************************/
static void property_get_protocol_version_callback(sli_cpc_property_id_t property_id,
                                                   void *property_value,
                                                   size_t property_length,
                                                   void *on_reply_arg,
                                                   sl_status_t status)
{
  uint8_t* version = (uint8_t*)property_value;

  (void) on_reply_arg;

  if ((property_id != PROP_PROTOCOL_VERSION)
      || (status != SL_STATUS_OK && status != SL_STATUS_IN_PROGRESS)
      || (property_value == NULL || property_length != sizeof(uint8_t))) {
    // Cannot get Secondary Protocol version (obsolete RCP firmware?)
    EFM_ASSERT(false);
  }

  secondary_protocol_version = *version;

  PRINT_INFO("Secondary Protocol v%d", secondary_protocol_version);

  protocol_version_received = true;
}

/***************************************************************************/ /**
 * The callback when a reply to a property get capabilities is received
 ******************************************************************************/
static void property_get_capabilities_callback(sli_cpc_property_id_t property_id,
                                               void *property_value,
                                               size_t property_length,
                                               void *on_reply_arg,
                                               sl_status_t status)
{
  (void)on_reply_arg;

  EFM_ASSERT(property_id == PROP_CAPABILITIES);
  EFM_ASSERT(status == SL_STATUS_OK || status == SL_STATUS_IN_PROGRESS);
  EFM_ASSERT(property_value != NULL && property_length == sizeof(uint32_t));

  capabilities = *((uint32_t *)property_value);

  if (capabilities & CPC_CAPABILITIES_SECURITY_ENDPOINT_MASK) {
    TRACE_RESET("Received capability : Security endpoint");
  }

  if (capabilities & CPC_CAPABILITIES_PACKED_ENDPOINT_MASK) {
    TRACE_RESET("Received capability : Packed endpoint");
  }

  if (capabilities & CPC_CAPABILITIES_GPIO_ENDPOINT_MASK) {
    TRACE_RESET("Received capability : GPIO endpoint");
  }

  if (capabilities & CPC_CAPABILITIES_UART_FLOW_CONTROL_MASK) {
    TRACE_RESET("Received capability : UART flow control");
  }

  capabilities_received = true;
}

/***************************************************************************/ /**
 * The callback when a reply to a property get cpc version is received
 ******************************************************************************/
static void property_get_secondary_cpc_version_callback(sli_cpc_property_id_t property_id,
                                                        void *property_value,
                                                        size_t property_length,
                                                        void *on_reply_arg,
                                                        sl_status_t status)
{
  uint32_t version[3];

  (void) on_reply_arg;

  memcpy(version, property_value, sizeof(version));

  if ( (property_id != PROP_SECONDARY_CPC_VERSION)
       || (status != SL_STATUS_OK && status != SL_STATUS_IN_PROGRESS)
       || (property_value == NULL || property_length != 3 * sizeof(uint32_t))) {
    // Cannot get Secondary CPC version (obsolete RCP firmware?)
    EFM_ASSERT(false);
  }

  PRINT_INFO("Secondary CPC v%lu.%lu.%lu", version[0], version[1], version[2]);
  secondary_cpc_version_received = true;
}

#if defined(SL_CPC_DEBUG_TRACES)
/***************************************************************************/ /**
 * Returns a string corresponding to the bootlaoder type
 ******************************************************************************/
static const char* sl_cpc_system_bootloader_type_to_str(sl_cpc_bootloader_t bootloader)
{
  switch (bootloader) {
    case SL_CPC_BOOTLOADER_NONE:
      return "None";
    case SL_CPC_BOOTLOADER_EMBER_APPLICATION:
      return "Ember Application";
    case SL_CPC_BOOTLOADER_EMBER_STANDALONE:
      return "Ember Standalone";
    case SL_CPC_BOOTLOADER_GECKO:
      return "Gecko SDK";
    case SL_CPC_BOOTLOADER_UNKNOWN:
      return "Unknown";
    default:
      return "Unexpected Value";
  }
}
#endif

/***************************************************************************/ /**
 * The callback when a reply to a property get bootloader info is received
 ******************************************************************************/
static void property_get_secondary_bootloader_info_callback(sli_cpc_property_id_t property_id,
                                                            void *property_value,
                                                            size_t property_length,
                                                            void *on_reply_arg,
                                                            sl_status_t status)
{
  (void) on_reply_arg;

  if ((status == SL_STATUS_OK || status == SL_STATUS_IN_PROGRESS) && property_id == PROP_BOOTLOADER_INFO) {
    EFM_ASSERT(property_value != NULL);
    EFM_ASSERT(property_length == 3 * sizeof(uint32_t));

    // property_value:
    //  [0]: bootloader type
    //  [1]: version (unused for now)
    //  [2]: capability mask (unused for now)
    secondary_bootloader_type = (sl_cpc_bootloader_t) ((uint32_t *)property_value)[0];
    EFM_ASSERT(secondary_bootloader_type < SL_CPC_BOOTLOADER_UNKNOWN);

    PRINT_INFO("Secondary bootloader: %s", sl_cpc_system_bootloader_type_to_str((sl_cpc_bootloader_t)secondary_bootloader_type));
  } else if ((status == SL_STATUS_OK || status == SL_STATUS_IN_PROGRESS) && property_id == PROP_LAST_STATUS) {
    PRINT_INFO("Secondary doesn't implement bootloader information");
    secondary_bootloader_type = SL_CPC_BOOTLOADER_UNKNOWN;
  } else {
    PRINT_INFO("Cannot get secondary bootloader information");
    secondary_bootloader_type = SL_CPC_BOOTLOADER_UNKNOWN;
  }

  bootloader_info_received_or_not_available = true;
}

/***************************************************************************/ /**
 * The callback when a reply to a property get bus max bitrate is received
 ******************************************************************************/
static void property_get_secondary_bus_max_bitrate_callback(sli_cpc_property_id_t property_id,
                                                            void *property_value,
                                                            size_t property_length,
                                                            void *on_reply_arg,
                                                            sl_status_t status)
{
  uint32_t max_bus_bitrate = 0;

  (void) on_reply_arg;

  if ((status == SL_STATUS_OK || status == SL_STATUS_IN_PROGRESS) && property_id == PROP_BUS_MAX_BITRATE_VALUE) {
    EFM_ASSERT(property_value != NULL);
    EFM_ASSERT(property_length == sizeof(uint32_t));

    memcpy(&max_bus_bitrate, property_value, sizeof(uint32_t));

    #if defined(SL_CATALOG_CPC_DRIVER_SPI_PRESENT)
    PRINT_INFO("Secondary max bus bitrate is %" PRIu32, max_bus_bitrate);

    // If the spi bitrate is not specific in the config file, use the max bitrate returned by the secondary
    uint32_t actual_spi_bitrate = sli_cpc_drv_get_bus_bitrate();

    if (actual_spi_bitrate == 0) {
      sli_cpc_drv_set_bus_bitrate(max_bus_bitrate);
    } else {
      if (actual_spi_bitrate > max_bus_bitrate) {
        PRINT_INFO("The actual SPI bitrate (%" PRIu32 ") is greater than the maximum supported bitrate returned by the secondary (%" PRIu32 "). Falling back to the value returned by the secondary", actual_spi_bitrate, max_bus_bitrate);
        sli_cpc_drv_set_bus_bitrate(max_bus_bitrate);
      } else if (actual_spi_bitrate < max_bus_bitrate) {
        PRINT_INFO("The actual SPI bitrate (%" PRIu32 ") is lesser than the maximum supported bitrate returned by the secondary (%" PRIu32 "). For performance reason, consider raising it.", actual_spi_bitrate, max_bus_bitrate);
      }
    }

    PRINT_INFO("The applied SPI bitrate is %" PRIu32, sli_cpc_drv_get_bus_bitrate());
#endif

    secondary_bus_max_bitrate_received = true;
  } else {
    PRINT_INFO("Could not obtain the secondary's max bus bitrate");
    failed_to_receive_secondary_bus_max_bitrate = true;
  }
}

/***************************************************************************/ /**
 * The callback when a reply to a property get secondary app version is received
 ******************************************************************************/
static void property_get_secondary_app_version_callback(sli_cpc_property_id_t property_id,
                                                        void *property_value,
                                                        size_t property_length,
                                                        void *on_reply_arg,
                                                        sl_status_t status)
{
  (void) on_reply_arg;

  if ((status == SL_STATUS_OK || status == SL_STATUS_IN_PROGRESS) && property_id == PROP_SECONDARY_APP_VERSION) {
    EFM_ASSERT(property_value != NULL);
    EFM_ASSERT(property_length != 0);

    const char *version = (const char *)property_value;

    EFM_ASSERT(secondary_app_version == NULL);

    secondary_app_version = malloc(property_length);
    EFM_ASSERT(secondary_app_version != NULL);

    strncpy(secondary_app_version, version, property_length - 1);
    secondary_app_version[property_length - 1] = '\0';
    PRINT_INFO("Secondary APP v%s", secondary_app_version);
  } else {
    FATAL("Cannot get Secondary APP version (obsolete RCP firmware?)");
  }

  secondary_app_version_received_or_not_available = true;
}

/***************************************************************************/ /**
 * The bare metal process action function for the reboot into bootloader mode.
 ******************************************************************************/
void sli_cpc_reboot_bootloader_sequence_process(void)
{
  switch (reset_bootloader_sequence_state) {
    case RESET_BOOTLOADER_SEQUENCE_DONE:
      return;

    case SET_BOOTLOADER_REBOOT_MODE:
      PRINT_INFO("Sending reboot into bootloader mode");

      // Send a request to the secondary to set the reboot mode to 'bootloader'
      // Keep track that the reboot mode that was requested is bootloader mode
      pending_reboot_mode = REBOOT_BOOTLOADER;

      sli_cpc_system_cmd_property_set(property_set_reset_mode_callback,
                                      NULL,
                                      PROP_BOOTLOADER_REBOOT_MODE,
                                      1,      // retry once
                                      2000,   // 2s between retries
                                      &pending_reboot_mode,
                                      sizeof(pending_reboot_mode),
                                      SYSTEM_EP_UFRAME);

      reset_bootloader_sequence_state = WAIT_BOOTLOADER_REBOOT_MODE_ACK;

      TRACE_RESET("Reboot mode sent");
      break;

    case WAIT_BOOTLOADER_REBOOT_MODE_ACK:
      if (set_reset_mode_ack == true) {
        // request a reset
        sli_cpc_system_cmd_reboot(reset_callback,
                                  NULL,
                                  5,    // 5 retries
                                  1000  // 1s between retries
                                  );

        reset_bootloader_sequence_state = WAIT_BOOTLOADER_RESET_ACK;

        // Set it back to false because it will be used for the bootloader reboot sequence
        set_reset_mode_ack = false;

        TRACE_RESET("Reboot mode reply received, reset request sent");
      }
      break;

    case WAIT_BOOTLOADER_RESET_ACK:

      if (reset_ack == true) {
        reset_bootloader_sequence_state = RESET_BOOTLOADER_SEQUENCE_DONE;

        // Set it back to false because it will be used for the bootloader reboot sequence
        reset_ack = false;

        TRACE_RESET("Reset request acknowledged");
      }
      break;

    default:
      BUG();
      break;
  }
}
