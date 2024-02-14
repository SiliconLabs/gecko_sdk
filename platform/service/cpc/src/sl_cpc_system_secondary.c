/***************************************************************************/ /**
 * @file
 * @brief CPC System Endpoint RCP API implementation.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#include <stdbool.h>
#include <string.h>

#include "sl_component_catalog.h"

#include "em_chip.h"
#include "em_rmu.h"
#include "sli_cpc.h"
#include "sli_cpc_bootloader.h"
#include "sli_cpc_drv.h"
#include "sli_cpc_hdlc.h"
#include "sli_cpc_system_secondary.h"
#include "sli_cpc_system_common.h"
#include "sli_mem_pool.h"
#include "sl_atomic.h"
#include "sl_cpc.h"
#include "sl_cpc_config.h"
#include "sl_gsdk_version.h"
#include "sl_common.h"

#if (defined(SL_CATALOG_EMLIB_CORE_PRESENT))
#include "em_core.h"
#include "em_chip.h"
#include "em_rmu.h"
#if defined(EMU_PRESENT)
#include "em_emu.h"
#endif
#endif

#if (defined(SL_CATALOG_CPC_SECURITY_PRESENT))
#include "sli_cpc_security.h"
#endif

#define CPC_PACKED_ENDPOINT_PRESENT 0   // Not yet implemented

#define SLI_CPC_PROPERTY_LENGTH_MAX   (SLI_CPC_SYSTEM_COMMAND_BUFFER_SIZE \
                                       - sizeof(sli_cpc_system_cmd_t)     \
                                       - sizeof(sli_cpc_system_property_cmd_t))
// On write complete argument magic words
#define ON_WRITE_COMPLETE_RESET       0xDEADBEEF
#define ON_WRITE_COMPLETE_CONNECT     0xCAFEBABE
#define ON_WRITE_COMPLETE_SHUTDOWN    0xBEEFBABE
#define ON_WRITE_COMPLETE_EP_ID_MASK  0xFF
/*******************************************************************************
 ***************************  GLOBAL VARIABLES   ********************************
 ******************************************************************************/

extern sli_cpc_drv_capabilities_t sli_cpc_driver_capabilities;

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

static sli_cpc_system_primary_version_t primary_version;

static bool restart_flag = false;

static bool reset_sequence_done = false;

static uint32_t enter_irq_end_ms;
static sli_cpc_timer_handle_t enter_irq_timer;

#ifdef CPC_TEST_HEADER_SYNC
static bool process_uframes_flag = true;
#else
static bool process_uframes_flag = false;
#endif

static uint32_t fc_validation_value;

/***************************************************************************//**
 * System endpoint handle
 ******************************************************************************/
static sl_cpc_endpoint_handle_t system_ep = { .ep = NULL };

/***************************************************************************//**
 * bootloader_reboot_mode.
 * 0 - At the next reboot application is executed.
 * 1 -  At the next reboot bootloader is executed. Depending on the
 *      configuration of the bootloader, it either updates the application or
 *      starts an NCP mode.
 ******************************************************************************/
static sli_cpc_system_reboot_mode_t prop_bootloader_reboot_mode = REBOOT_APPLICATION;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

static void on_write_completed(sl_cpc_user_endpoint_id_t endpoint_id,
                               void *buffer,
                               void *arg,
                               sl_status_t status);

static sl_status_t open_endpoint(void);
static void on_system_ep_error(sl_cpc_user_endpoint_id_t endpoint_id);

sl_status_t send_endpoint_state(uint8_t endpoint_id, sl_cpc_endpoint_state_t state);

#if (!defined(SLI_CPC_DEVICE_UNDER_TEST))
static void send_reset_reason(void);
#endif

static void on_poll(uint8_t endpoint_id,
                    void *arg,
                    void *poll_data,
                    uint32_t poll_data_length,
                    void **reply_data,
                    uint32_t * reply_data_length,
                    void **on_write_complete_arg);

static void enter_irq_timer_callback(sli_cpc_timer_handle_t *handle,
                                     void *data);

#if defined(SLI_CPC_ENABLE_TEST_FEATURES)
SL_WEAK void system_on_information_received(uint8_t endpoint_id, void *arg);
#endif
SL_WEAK const char* sl_cpc_secondary_app_version(void);

/***************************************************************************//**
 * Called when secondary app version is requested.
 * The format is up to the user. The string should be null terminated.
 ******************************************************************************/
SL_WEAK const char* sl_cpc_secondary_app_version(void)
{
  return "UNDEFINED";
}

/***************************************************************************//**
 * Initialize CPC System
 ******************************************************************************/
static sl_status_t open_endpoint(void)
{
  sl_status_t status;

  status = sli_cpc_open_service_endpoint(&system_ep, SL_CPC_ENDPOINT_SYSTEM, SL_CPC_ENDPOINT_FLAG_UFRAME_ENABLE, 1);
  if (status == SL_STATUS_ALREADY_EXISTS) {
    return SL_STATUS_ALREADY_INITIALIZED;
  } else if (status != SL_STATUS_OK) {
    return status;
  }

  status = sl_cpc_set_endpoint_option(&system_ep, SL_CPC_ENDPOINT_ON_POLL, (void *)on_poll);
  if (status != SL_STATUS_OK) {
    sl_cpc_close_endpoint(&system_ep);
    return status;
  }

#if defined(SLI_CPC_ENABLE_TEST_FEATURES)
  if (system_on_information_received) {
    status = sl_cpc_set_endpoint_option(&system_ep, SL_CPC_ENDPOINT_ON_UFRAME_RECEIVE, (void *)system_on_information_received);
    if (status != SL_STATUS_OK) {
      sl_cpc_close_endpoint(&system_ep);
      return status;
    }
  }
#endif

  status = sl_cpc_set_endpoint_option(&system_ep, SL_CPC_ENDPOINT_ON_UFRAME_WRITE_COMPLETED, (void *)on_write_completed);
  if (status != SL_STATUS_OK) {
    sl_cpc_close_endpoint(&system_ep);
    return status;
  }

  status = sl_cpc_set_endpoint_option(&system_ep, SL_CPC_ENDPOINT_ON_IFRAME_WRITE_COMPLETED, (void *)on_write_completed);
  if (status != SL_STATUS_OK) {
    sl_cpc_close_endpoint(&system_ep);
    return status;
  }

  status = sl_cpc_set_endpoint_option(&system_ep, SL_CPC_ENDPOINT_ON_ERROR, (void *)on_system_ep_error);
  if (status != SL_STATUS_OK) {
    sl_cpc_close_endpoint(&system_ep);
    return status;
  }

  return SL_STATUS_OK;
}

/***************************************************************************/ /**
 * Returns the state of the reset sequence
 ******************************************************************************/
bool sli_cpc_reboot_is_sequence_done(void)
{
  return reset_sequence_done;
}

/***************************************************************************//**
 * Process the system endpoint
 ******************************************************************************/
void sli_cpc_system_process(void)
{
  sl_cpc_endpoint_state_t state;

  if (restart_flag) {
    state = sl_cpc_get_endpoint_state(&system_ep);

    if (state == SL_CPC_STATE_FREED) {
      if (open_endpoint() == SL_STATUS_OK) {
        restart_flag = false;
      } else {
        EFM_ASSERT(false);
        restart_flag = true;
      }
    } else {
      if (state != SL_CPC_STATE_CLOSED) {
        sl_cpc_close_endpoint(&system_ep);
      }
    }
  }

  if (process_uframes_flag) {
    void *data;
    uint16_t data_length;
    sl_status_t status = sl_cpc_read(&system_ep, &data, &data_length, 0, SL_CPC_FLAG_NO_BLOCK | SL_CPC_FLAG_UNNUMBERED_INFORMATION);
    if (status == SL_STATUS_OK) {
      if (data_length > 0) {
        fc_validation_value += ((uint8_t *)data)[0];
      }
      sl_cpc_free_rx_buffer(data);
    }
  }
}

/***************************************************************************//**
 * Start CPC System
 ******************************************************************************/
sl_status_t sli_cpc_system_start(void)
{
  sl_status_t status;
  status = open_endpoint();
  if (status != SL_STATUS_OK) {
    EFM_ASSERT(false);
    return status;
  }
#if (!defined(SLI_CPC_DEVICE_UNDER_TEST))
  send_reset_reason();
#endif
  return status;
}

/***************************************************************************//**
 * Initialize CPC System
 ******************************************************************************/
sl_status_t sli_cpc_system_init(void)
{
#if defined(SLI_CPC_DEVICE_UNDER_TEST)
  reset_sequence_done = true;
#endif
  return SL_STATUS_OK;
}

/***************************************************************************//**
 * System endpoint on error callback
 ******************************************************************************/
static void on_system_ep_error(sl_cpc_user_endpoint_id_t endpoint_id)
{
  EFM_ASSERT(endpoint_id == SL_CPC_ENDPOINT_SYSTEM);
  restart_flag = true;
}

/***************************************************************************//**
 * Reset system; Should not return
 ******************************************************************************/
SL_WEAK void cpc_system_reset(sli_cpc_system_reboot_mode_t reboot_mode)
{
  (void)reboot_mode;
#if (defined(SL_CATALOG_EMLIB_CORE_PRESENT))
#if (defined(SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT))
  // The reset command asked to perform a reset.
  BootloaderResetCause_t* resetCause = (BootloaderResetCause_t*) (RAM_MEM_BASE);

  // Set reset reason to bootloader entry
  switch (reboot_mode) {
    case REBOOT_APPLICATION:
      resetCause->reason = BOOTLOADER_RESET_REASON_GO;
      break;
    case REBOOT_BOOTLOADER:
      resetCause->reason = BOOTLOADER_RESET_REASON_BOOTLOAD;
      break;
    default:
      EFM_ASSERT(false);
      break;
  }

  resetCause->signature = BOOTLOADER_RESET_SIGNATURE_VALID;
#endif  // SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT

#if defined(RMU_PRESENT)
// Clear resetcause
  RMU->CMD = RMU_CMD_RCCLR;
// Trigger a software system reset
  RMU->CTRL = (RMU->CTRL & ~_RMU_CTRL_SYSRMODE_MASK) | RMU_CTRL_SYSRMODE_EXTENDED;
#endif  // RMU_PRESENT

  CHIP_Reset();
#else
  EFM_ASSERT(false);
#endif  // SL_CATALOG_EMLIB_CORE_PRESENT
  exit(1);
}

/***************************************************************************//**
 * System endpoint on write completed callback
 ******************************************************************************/
static void on_write_completed(sl_cpc_user_endpoint_id_t endpoint_id,
                               void *buffer,
                               void *arg,
                               sl_status_t status)
{
  uint32_t magic;
  uint8_t cmd_ep_id;
  (void) endpoint_id;

  // Unnumbered ACK has no payload
  if (buffer != NULL) {
    sli_cpc_free_command_buffer(buffer);
  }

  magic = (uint32_t)arg;

  if (magic == ON_WRITE_COMPLETE_RESET) {
    // status is irrelevant, the MCU will reset in cpc_system_reset.
    cpc_system_reset(prop_bootloader_reboot_mode);
  } else if ((magic & ~ON_WRITE_COMPLETE_EP_ID_MASK)
             == (ON_WRITE_COMPLETE_CONNECT & ~ON_WRITE_COMPLETE_EP_ID_MASK)) {
    cmd_ep_id = magic & ON_WRITE_COMPLETE_EP_ID_MASK;

    sli_cpc_remote_connected(cmd_ep_id, status);
  } else if ((magic & ~ON_WRITE_COMPLETE_EP_ID_MASK)
             == (ON_WRITE_COMPLETE_SHUTDOWN & ~ON_WRITE_COMPLETE_EP_ID_MASK)) {
    cmd_ep_id = magic & ON_WRITE_COMPLETE_EP_ID_MASK;

    // status is irrelevant. If remote failed to ACK the final disconnection message,
    // go to disconnected state regardless.
    sli_cpc_endpoint_disconnected(cmd_ep_id);
  }
}

sl_status_t send_endpoint_state(uint8_t endpoint_id, sl_cpc_endpoint_state_t state)
{
  sli_cpc_system_property_cmd_t *tx_prop_command;
  sl_cpc_endpoint_state_t *ep_state;
  sli_cpc_system_cmd_t *tx_command;
  sl_status_t status;

  status = sli_cpc_get_system_command_buffer(&tx_command);
  if (status != SL_STATUS_OK) {
    return status;
  }

  tx_command->command_id = CMD_SYSTEM_PROP_VALUE_IS;
  tx_command->seq = 0;
  tx_command->length = sizeof(sli_cpc_system_property_cmd_t) + sizeof(sl_cpc_endpoint_state_t);

  tx_prop_command = (sli_cpc_system_property_cmd_t*)(tx_command->payload);
  tx_prop_command->property_id = EP_ID_TO_PROPERTY_STATE(endpoint_id);

  ep_state = (sl_cpc_endpoint_state_t *)tx_prop_command->payload;
  *ep_state = state;

  status = sl_cpc_write(&system_ep,
                        (void *)tx_command,
                        SIZEOF_SYSTEM_COMMAND(tx_command),
                        SL_CPC_FLAG_NO_BLOCK,
                        NULL);
  return status;
}

/***************************************************************************//**
 * Endpoint was opened, notify the host/primary
 ******************************************************************************/
sl_status_t sli_cpc_send_opening_notification(uint8_t endpoint_id)
{
  return send_endpoint_state(endpoint_id, SL_CPC_STATE_OPEN);
}

/***************************************************************************//**
 * Endpoint connection was terminated, notify the host
 ******************************************************************************/
sl_status_t sli_cpc_send_terminate_notification(uint8_t endpoint_id)
{
  return send_endpoint_state(endpoint_id, SL_CPC_STATE_CLOSED);
}

/***************************************************************************//**
 * Endpoint is requesting a shutdown, notify the host
 ******************************************************************************/
sl_status_t sli_cpc_send_shutdown_request(uint8_t endpoint_id)
{
  return send_endpoint_state(endpoint_id, SL_CPC_STATE_DISCONNECTED);
}

/***************************************************************************//**
 * Get system reset reason.
 ******************************************************************************/
SL_WEAK sl_cpc_system_status_t cpc_get_reset_reason(void)
{
  sl_cpc_system_status_t last_status = STATUS_RESET_UNKNOWN;
  uint32_t reset_cause = RMU_ResetCauseGet();

  RMU_ResetCauseClear();

#if defined(RMU_PRESENT)

 #if defined(_RMU_RSTCAUSE_MASK)
  if (reset_cause & RMU_RSTCAUSE_PORST) {
    last_status = STATUS_RESET_POWER_ON;
  } else if (reset_cause & RMU_RSTCAUSE_AVDDBOD) {
    last_status = STATUS_RESET_FAULT;
  } else if (reset_cause & RMU_RSTCAUSE_DVDDBOD) {
    last_status = STATUS_RESET_FAULT;
  } else if (reset_cause & RMU_RSTCAUSE_DECBOD) {
    last_status = STATUS_RESET_FAULT;
  } else if (reset_cause & RMU_RSTCAUSE_EXTRST) {
    last_status = STATUS_RESET_EXTERNAL;
  } else if (reset_cause & RMU_RSTCAUSE_WDOGRST) {
    last_status = STATUS_RESET_WATCHDOG;
  } else if (reset_cause & RMU_RSTCAUSE_LOCKUPRST) {
    last_status = STATUS_RESET_CRASH;
  } else if (reset_cause & RMU_RSTCAUSE_SYSREQRST) {
    last_status = STATUS_RESET_SOFTWARE;
  } else if (reset_cause & RMU_RSTCAUSE_EM4RST) {
    last_status = STATUS_RESET_OTHER;
  }
  #endif

#elif defined(EMU_PRESENT)

 #if defined(_EMU_RSTCTRL_AVDDBODRMODE_MASK)
  if (reset_cause & rmuResetAVDD) {
    last_status = STATUS_RESET_FAULT;
  }
 #endif
 #if defined(_EMU_RSTCTRL_IOVDD0BODRMODE_MASK)
  if (reset_cause & rmuResetIOVDD0) {
    last_status = STATUS_RESET_FAULT;
  }
 #endif
 #if defined(_EMU_RSTCTRL_DECBODRMODE_MASK)
  if (reset_cause & rmuResetDecouple) {
    last_status = STATUS_RESET_FAULT;
  }
 #endif
 #if defined(_EMU_RSTCTRL_WDOG0RMODE_MASK)
  if (reset_cause & rmuResetWdog0) {
    last_status = STATUS_RESET_WATCHDOG;
  }
 #endif
 #if defined(_EMU_RSTCTRL_WDOG1RMODE_MASK)
  if (reset_cause & rmuResetWdog1) {
    last_status = STATUS_RESET_WATCHDOG;
  }
 #endif
 #if defined(_EMU_RSTCTRL_LOCKUPRMODE_MASK)
  if (reset_cause & rmuResetCoreLockup) {
    last_status = STATUS_RESET_CRASH;
  }
 #endif
 #if defined(_EMU_RSTCTRL_SELOCKUPRMODE_MASK)
  if (reset_cause & rmuResetSELockup) {
    last_status = STATUS_RESET_CRASH;
  }
 #endif
 #if defined(_EMU_RSTCTRL_SYSRMODE_MASK)
  if (reset_cause & rmuResetSys) {
    last_status = STATUS_RESET_SOFTWARE;
  }
 #endif
 #if defined(_EMU_RSTCTRL_SESYSRMODE_MASK)
  if (reset_cause & rmuResetSESys) {
    last_status = STATUS_RESET_SOFTWARE;
  }
 #endif
#endif

  return last_status;
}

/***************************************************************************//**
 * Send reset reason
 ******************************************************************************/
#if (!defined(SLI_CPC_DEVICE_UNDER_TEST))
static void send_reset_reason(void)
{
  sl_status_t status;
  sli_cpc_system_cmd_t *tx_command;
  sli_cpc_system_property_cmd_t *tx_prop_command;
  sl_cpc_system_status_t *tx_prop_last_status;

  status = sli_cpc_get_system_command_buffer(&tx_command);
  EFM_ASSERT(status == SL_STATUS_OK);

  tx_command->command_id = CMD_SYSTEM_PROP_VALUE_IS;

  /* Seq is irrelevant in u-frame information */
  tx_command->seq = 0;

  tx_prop_command = (sli_cpc_system_property_cmd_t*)(tx_command->payload);

  tx_prop_command->property_id = PROP_LAST_STATUS;

  tx_prop_last_status = (sl_cpc_system_status_t*)tx_prop_command->payload;

  *tx_prop_last_status = cpc_get_reset_reason();

  tx_command->length = sizeof(sli_cpc_system_property_cmd_t) + sizeof(sl_cpc_system_status_t);

  status = sl_cpc_write(&system_ep,
                        (void *)tx_command,
                        SIZEOF_SYSTEM_COMMAND(tx_command),
                        SL_CPC_FLAG_NO_BLOCK | SL_CPC_FLAG_UNNUMBERED_INFORMATION,
                        NULL);

  EFM_ASSERT(status == SL_STATUS_OK); //Ignore error
  SL_CPC_JOURNAL_RECORD_INFO("Sent reset reason", 0);
}
#endif

/*******************************************************************************
 ***************************  PROPERTY-GET HANDLERS  ***************************
 ******************************************************************************/

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_GET
 * Property ID: PROP_LAST_STATUS
 *   When replying to any CMD_PROPERTY_GET/SET which result in an unsuccessful
 *   operation, the RCP will reply with PROP_LAST_STATUS instead. Here, this
 *   property is specifically queried. There is nothing more meaningful than
 *   to reply with a STATUS_OK.
 ******************************************************************************/
static void on_property_get_last_status(sli_cpc_system_cmd_t *tx_command)
{
  sli_cpc_system_property_cmd_t *prop_cmd_buff;

  prop_cmd_buff = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  prop_cmd_buff->property_id = PROP_LAST_STATUS;
  *((sl_cpc_system_status_t*)(prop_cmd_buff->payload)) = STATUS_OK;

  tx_command->length = sizeof(sli_cpc_property_id_t) + sizeof(sl_cpc_system_status_t);
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_GET
 * Property ID: PROP_PROTOCOL_VERSION
 *   Ship the hardcoded protocol version number back to the primary.
 ******************************************************************************/
static void on_property_get_protocol_version(sli_cpc_system_cmd_t *tx_command)
{
  sli_cpc_system_property_cmd_t *prop_cmd_buff;

  prop_cmd_buff = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  prop_cmd_buff->property_id = PROP_PROTOCOL_VERSION;
  prop_cmd_buff->payload[0] = SLI_CPC_PROTOCOL_VERSION;

  tx_command->length = sizeof(sli_cpc_property_id_t) + sizeof(uint8_t);
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_GET
 * Property ID: PROP_SECONDARY_CPC_VERSION
 *   Ship the hardcoded major and minor version number back to the primary.
 ******************************************************************************/
static void on_property_get_secondary_cpc_version(sli_cpc_system_cmd_t *tx_command)
{
  sli_cpc_system_property_cmd_t *prop_cmd_buff;
  uint32_t* version;

  prop_cmd_buff = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  prop_cmd_buff->property_id = PROP_SECONDARY_CPC_VERSION;
  version = (uint32_t*)(prop_cmd_buff->payload);

  version[0] = SL_GSDK_MAJOR_VERSION;
  version[1] = SL_GSDK_MINOR_VERSION;
  version[2] = SL_GSDK_PATCH_VERSION;

  tx_command->length = sizeof(sli_cpc_property_id_t) + (3 * sizeof(uint32_t));
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_GET
 * Property ID: PROP_SECONDARY_APP_VERSION
 *   Send a string version of the secondary application to the primary
 ******************************************************************************/
static void on_property_get_secondary_app_version(sli_cpc_system_cmd_t *tx_command)
{
  sli_cpc_system_property_cmd_t *prop_cmd_buff;
  const char* app_version;
  uint16_t app_version_len;

  prop_cmd_buff = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  prop_cmd_buff->property_id = PROP_SECONDARY_APP_VERSION;
  app_version = sl_cpc_secondary_app_version();
  app_version_len = strlen(app_version) + 1;
  app_version_len = app_version_len > SLI_CPC_PROPERTY_LENGTH_MAX ? SLI_CPC_PROPERTY_LENGTH_MAX : app_version_len;
  memcpy(prop_cmd_buff->payload, app_version, app_version_len);

  tx_command->length = sizeof(sli_cpc_property_id_t) + app_version_len;
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_GET
 * Property ID: PROP_CAPABILITIES
 *   Send the capabilities of the secondary to the primary
 ******************************************************************************/
static void on_property_get_capabilities(sli_cpc_system_cmd_t *tx_command)
{
  sli_cpc_system_property_cmd_t *prop_cmd_buff;
  uint32_t *capabilities;

  prop_cmd_buff = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  prop_cmd_buff->property_id = PROP_CAPABILITIES;
  capabilities = (uint32_t*)(prop_cmd_buff->payload);

  *capabilities = SL_CPC_ENDPOINT_SECURITY_ENABLED * CPC_CAPABILITIES_SECURITY_ENDPOINT_MASK
                  + CPC_PACKED_ENDPOINT_PRESENT * CPC_CAPABILITIES_PACKED_ENDPOINT_MASK
                  + SLI_CPC_ENDPOINT_GPIO_ENABLED * CPC_CAPABILITIES_GPIO_ENDPOINT_MASK
                  + sli_cpc_driver_capabilities.uart_flowcontrol * CPC_CAPABILITIES_UART_FLOW_CONTROL_MASK;

  tx_command->length = sizeof(sli_cpc_property_id_t) + sizeof(uint32_t);
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_GET
 * Property ID: PROP_RX_CAPABILITY
 *   Send the rx buffer capability of the secondary to the primary
 ******************************************************************************/
static void on_property_get_rx_capabilities(sli_cpc_system_cmd_t *tx_command)
{
  sli_cpc_system_property_cmd_t *prop_cmd_buff;
  uint16_t *rx_capability;

  prop_cmd_buff = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  prop_cmd_buff->property_id = PROP_RX_CAPABILITY;
  rx_capability = (uint16_t *)(prop_cmd_buff->payload);
  *rx_capability = SL_CPC_RX_PAYLOAD_MAX_LENGTH;

  tx_command->length = sizeof(sli_cpc_property_id_t) + sizeof(uint16_t);
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_GET
 * Property ID: PROP_FC_VALIDATION_VALUE
 *   Send the flow control validation value of the secondary to the primary
 ******************************************************************************/
static void on_property_get_fc_validation_value(sli_cpc_system_cmd_t *tx_command)
{
  sli_cpc_system_property_cmd_t *prop_cmd_buff;
  uint32_t *flow_control_validation_value;

  prop_cmd_buff = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  prop_cmd_buff->property_id = PROP_FC_VALIDATION_VALUE;
  flow_control_validation_value = (uint32_t *)(prop_cmd_buff->payload);
  *flow_control_validation_value = fc_validation_value;

  tx_command->length = sizeof(sli_cpc_property_id_t) + sizeof(uint32_t);
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_GET
 * Property ID: PROP_BUS_BITRATE_VALUE
 *   Send the bus bitrate value of the secondary to the primary.
 ******************************************************************************/
static void on_property_get_bus_bitrate_value(sli_cpc_system_cmd_t *tx_command)
{
  sli_cpc_system_property_cmd_t *prop_cmd_buff;
  uint32_t *bus_bitrate_value;

  prop_cmd_buff = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  prop_cmd_buff->property_id = PROP_BUS_BITRATE_VALUE;
  bus_bitrate_value = (uint32_t *)(prop_cmd_buff->payload);
  *bus_bitrate_value = sli_cpc_drv_get_bus_bitrate();

  tx_command->length = sizeof(sli_cpc_property_id_t) + sizeof(uint32_t);
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_GET
 * Property ID: PROP_BUS_MAX_BITRATE_VALUE
 *   Send the bus max bitrate value of the secondary to the primary.
 ******************************************************************************/
static void on_property_get_bus_max_bitrate_value(sli_cpc_system_cmd_t *tx_command)
{
  sli_cpc_system_property_cmd_t *prop_cmd_buff;
  uint32_t *bus_max_bitrate_value;

  prop_cmd_buff = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  prop_cmd_buff->property_id = PROP_BUS_MAX_BITRATE_VALUE;
  bus_max_bitrate_value = (uint32_t *)(prop_cmd_buff->payload);
  *bus_max_bitrate_value = sli_cpc_drv_get_bus_max_bitrate();

  tx_command->length = sizeof(sli_cpc_property_id_t) + sizeof(uint32_t);
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_GET
 * Property ID: PROP_BOOTLOADER_INFO
 *   Reply to the PRIMARY the bootloader infos.
 ******************************************************************************/
static void on_property_get_bootloader_info(sli_cpc_system_cmd_t *tx_command)
{
  sli_cpc_system_property_cmd_t *tx_property;
  uint32_t* infos;

  tx_property = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  tx_property->property_id = PROP_BOOTLOADER_INFO;
  infos = (uint32_t*)(tx_property->payload);

#if defined(SL_CPC_HAS_BOOTLOADER_SUPPORT)
  BootloaderInformation_t bootloader_infos;

  bootloader_getInfo(&bootloader_infos);

  // set version, version might be overriden
  // below in case the bootloader is none
  infos[1] = (uint32_t)bootloader_infos.version;
  // capabilitiesMask only exist for EMBER_APPLICATION, default to 0
  infos[2] = 0;

#if (defined(SL_CATALOG_EMBER_BOOTLOADER_PRESENT))
#if (SL_EMBER_BOOTLOADER_TYPE == SL_EMBER_BOOTLOADER_TYPE_STANDALONE)
  infos[0] = (uint32_t)SL_CPC_BOOTLOADER_EMBER_STANDALONE;
#elif (SL_EMBER_BOOTLOADER_TYPE == SL_CPC_BOOTLOADER_EMBER_APPLICATION)
  infos[0] = (uint32_t)SL_CPC_BOOTLOADER_EMBER_APPLICATION;
  infos[2] = (uint32_t)bootloader_infos.capabilitiesMask;
#else
  // should never end up here, but just in case
  // make sure the returned value is sound
  infos[0] = (uint32_t)SL_CPC_BOOTLOADER_UNKNOWN;
#endif // SL_EMBER_BOOTLOADER_TYPE == SL_EMBER_BOOTLOADER_TYPE_STANDALONE
#else
  if (bootloader_infos.type == SL_BOOTLOADER) {
    infos[0] = (uint32_t)SL_CPC_BOOTLOADER_GECKO;
  } else if (bootloader_infos.type == NO_BOOTLOADER) {
    infos[0] = (uint32_t)SL_CPC_BOOTLOADER_NONE;
    infos[1] = 0xFFFFFFFF;
  } else {
    // this should never happen, just make the code ready in
    // case BootloaderType_t get extended with new values
    infos[0] = (uint32_t)SL_CPC_BOOTLOADER_UNKNOWN;
  }
#endif // SL_CATALOG_EMBER_BOOTLOADER_PRESENT

#else
  infos[0] = (uint32_t)SL_CPC_BOOTLOADER_NONE;
  infos[1] = 0xFFFFFFFF;
  infos[2] = 0xFFFFFFFF;
#endif // SL_CPC_HAS_BOOTLOADER_SUPPORT

  tx_command->length = sizeof(sli_cpc_property_id_t) + 3 * sizeof(uint32_t);
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_GET
 * Property ID: PROP_BOOTLOADER_REBOOT_MODE
 *   Reply to the PRIMARY the bootloader reboot mode.
 ******************************************************************************/
static void on_property_get_bootloader_reboot_mode(sli_cpc_system_cmd_t *tx_command)
{
  sli_cpc_system_property_cmd_t *tx_property;
  sli_cpc_system_reboot_mode_t* mode;

  tx_property = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  tx_property->property_id = PROP_BOOTLOADER_REBOOT_MODE;
  mode = (sli_cpc_system_reboot_mode_t*)(tx_property->payload);
  *mode = prop_bootloader_reboot_mode;

  tx_command->length = sizeof(sli_cpc_property_id_t) + sizeof(sli_cpc_system_reboot_mode_t);
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_GET
 * Property ID: PROP_SECURITY_STATE
 *   Reply to the PRIMARY the security state.
 ******************************************************************************/
static void on_property_get_security_state(sli_cpc_system_cmd_t *tx_command)
{
  sli_cpc_system_property_cmd_t *tx_property;
  uint32_t* security_state;

  tx_property = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  security_state = (uint32_t*)(tx_property->payload);

#ifdef SL_CATALOG_CPC_SECURITY_PRESENT
  tx_property->property_id = PROP_SECURITY_STATE;
  *security_state = sl_cpc_security_get_state();
#else
  tx_property->property_id = PROP_LAST_STATUS;
  *security_state = STATUS_UNIMPLEMENTED;
#endif

  tx_command->length = sizeof(sli_cpc_property_id_t) + sizeof(uint32_t);
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_GET
 * Property ID: PROP_ENDPOINT_STATE_x
 *   The primary queried the status of a specific endpoint number.
 ******************************************************************************/
static void on_property_get_endpoint_state(sli_cpc_system_cmd_t *tx_command,
                                           uint8_t ep_id)
{
  sli_cpc_system_property_cmd_t *reply_prop_cmd_buff;
  sl_cpc_endpoint_state_t *reply_ep_state;
  sl_cpc_endpoint_handle_t dummy_ep;

  reply_prop_cmd_buff = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  reply_ep_state = (sl_cpc_endpoint_state_t*) reply_prop_cmd_buff->payload;
  dummy_ep.ep = NULL;
  dummy_ep.id = ep_id;

  reply_prop_cmd_buff->property_id = EP_ID_TO_PROPERTY_STATE(ep_id);

  *reply_ep_state = sl_cpc_get_endpoint_state(&dummy_ep);

  tx_command->length = sizeof(sli_cpc_property_id_t) + sizeof(sl_cpc_endpoint_state_t);
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_GET
 * Property ID: PROP_ENDPOINT_ENCRYPTION_x
 *   The primary queried the encryption state of a specific endpoint number.
 ******************************************************************************/
static void on_property_get_endpoint_encryption(sli_cpc_system_cmd_t *tx_command,
                                                uint8_t ep_id)
{
  sli_cpc_system_property_cmd_t *reply_prop_cmd_buff;
  sl_cpc_endpoint_handle_t dummy_ep;
  bool *reply_ep_encryption;

  dummy_ep.ep = NULL;
  dummy_ep.id = ep_id;

  reply_prop_cmd_buff = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  reply_prop_cmd_buff->property_id = EP_ID_TO_PROPERTY_ENCRYPTION(ep_id);

  reply_ep_encryption = (bool*) reply_prop_cmd_buff->payload;
  *reply_ep_encryption = sl_cpc_get_endpoint_encryption(&dummy_ep);

  tx_command->length = sizeof(sli_cpc_property_id_t) + sizeof(bool);
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_GET
 * Property ID: PROP_ENDPOINT_STATES
 *   The primary queried the status of all endpoints.
 ******************************************************************************/
static void on_property_get_endpoint_states(sli_cpc_system_cmd_t *tx_command)
{
  sli_cpc_system_property_cmd_t *reply_prop_cmd_buff;
  uint8_t *reply_ep_states;

  reply_prop_cmd_buff = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  reply_ep_states = (uint8_t*)(reply_prop_cmd_buff->payload);
  reply_prop_cmd_buff->property_id = PROP_ENDPOINT_STATES;

  // process 2 endpoints per iteration
  for (size_t i = 0; i != SL_CPC_ENDPOINT_MAX_COUNT / 2; i++) {
    sl_cpc_endpoint_handle_t dummy_ep1 = { .ep = NULL, .id = 2 * i };
    sl_cpc_endpoint_handle_t dummy_ep2 = { .ep = NULL, .id = 2 * i + 1 };

    sl_cpc_endpoint_state_t ep1_state = sl_cpc_get_endpoint_state(&dummy_ep1);
    sl_cpc_endpoint_state_t ep2_state = sl_cpc_get_endpoint_state(&dummy_ep2);

    // Although an 'sl_cpc_endpoint_state_t' is an 8 bit value, the number of
    // values in the enum makes it possible to encode it with a nibble (4 bits)
    // as only 3 bits are required to encode those 6 values. Put the first
    // endpoint in the low nibble and the second in the high nibble.
    // This aggregation will make it possible to send all 256 endpoint states
    // in one reply as it will fit within 255 bytes (limited by the length field
    // within a command frame)
    reply_ep_states[i] = (ep2_state << 4) | ep1_state;
  }

  tx_command->length = sizeof(sli_cpc_property_id_t) + (SL_CPC_ENDPOINT_MAX_COUNT * sizeof(uint8_t) / 2);
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_GET
 * Property ID: PROP_DEBUG_COUNTERS
 *   The primary queried the debug counters.
 ******************************************************************************/
#if (SL_CPC_DEBUG_CORE_EVENT_COUNTERS == 1)
static void on_property_get_core_debug_counters(sli_cpc_system_cmd_t *tx_command)
{
  sli_cpc_system_property_cmd_t *reply_prop_cmd_buff;

  reply_prop_cmd_buff = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  memcpy(reply_prop_cmd_buff->payload, &sl_cpc_core_debug.core_counters, sizeof(sl_cpc_core_debug_counters_t));

  reply_prop_cmd_buff->property_id = PROP_CORE_DEBUG_COUNTERS;
  tx_command->length = sizeof(sli_cpc_property_id_t) + sizeof(sl_cpc_core_debug_counters_t);
}
#endif

/***************************************************************************//**
 * Handler for when the primary asks about a property not found:
 *   As with any property-get/set which is unsuccessful, the rcp replies with
 *   a property id of PROP_LAST_STATUS. Since the property the primary asked about
 *   can't be handled by the rcp, the status returned is STATUS_PROP_NOT_FOUND.
 ******************************************************************************/
static void on_property_get_set_not_found(sli_cpc_system_cmd_t *tx_command)
{
  sli_cpc_system_property_cmd_t *tx_property_cmd;

  tx_property_cmd = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  tx_property_cmd->property_id = PROP_LAST_STATUS;
  *((sl_cpc_system_status_t*)(tx_property_cmd->payload)) = STATUS_PROP_NOT_FOUND;

  tx_command->length = sizeof(sli_cpc_property_id_t) + sizeof(sl_cpc_system_status_t);
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_SET:
 * Property ID: PROP_ENDPOINT_STATE_x
 *   The primary notifies the secondary of an endpoint state change
 ******************************************************************************/
static void on_property_set_endpoint_state(uint8_t endpoint_id,
                                           sli_cpc_system_cmd_t *tx_command,
                                           sli_cpc_system_cmd_t *rx_command,
                                           void **on_write_complete_arg)
{
  sli_cpc_system_property_cmd_t *tx_prop_command = (sli_cpc_system_property_cmd_t*)(tx_command->payload);
  sli_cpc_system_property_cmd_t *rx_prop_command = (sli_cpc_system_property_cmd_t*)(rx_command->payload);
  sl_cpc_endpoint_state_t *ep_state = (sl_cpc_endpoint_state_t *)rx_prop_command->payload;
  uint32_t magic;
  sl_status_t status;

  tx_command->length = sizeof(sli_cpc_system_property_cmd_t) + sizeof(sl_cpc_endpoint_state_t);
  tx_prop_command->property_id = EP_ID_TO_PROPERTY_STATE(endpoint_id);

  if (*ep_state == SL_CPC_STATE_CLOSING || *ep_state == SL_CPC_STATE_CLOSED) {
    // Terminate notification.
    sli_cpc_remote_terminated(endpoint_id, (sl_cpc_endpoint_state_t *)tx_prop_command->payload);
  } else if (*ep_state == SL_CPC_STATE_CONNECTED) {
    // Connection request.
    status = sli_cpc_remote_connecting(endpoint_id, (sl_cpc_endpoint_state_t *)tx_prop_command->payload);
    if (status == SL_STATUS_OK) {
      // Only notify the core that the connect command has finished when it
      // is accepted.
      magic = (ON_WRITE_COMPLETE_CONNECT & ~ON_WRITE_COMPLETE_EP_ID_MASK) | endpoint_id;
      *on_write_complete_arg = (void*)magic;
    }
  } else if (*ep_state == SL_CPC_STATE_DISCONNECTED) {
    // Shutdown request
    status = sli_cpc_remote_shutdown(endpoint_id, (sl_cpc_endpoint_state_t *)tx_prop_command->payload);
    if (status == SL_STATUS_OK) {
      // endpoint successfully shutdown, go to DISCONNECTED on write completed
      magic = (ON_WRITE_COMPLETE_SHUTDOWN & ~ON_WRITE_COMPLETE_EP_ID_MASK) | endpoint_id;
      *on_write_complete_arg = (void *)magic;
    }
  } else {
    // Unsupported endpoint state
    EFM_ASSERT(false);
    tx_command->length = sizeof(sli_cpc_property_id_t);
    tx_prop_command->property_id = PROP_LAST_STATUS;
    *((sl_cpc_system_status_t*)(tx_prop_command->payload)) = STATUS_INVALID_ARGUMENT;
  }
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_SET:
 * Property ID: PROP_UFRAME_PROCESSING
 *   The primary enables/disables u-frame processing on the secondary.
 ******************************************************************************/
static void on_property_set_uframe_processing(sli_cpc_system_cmd_t *tx_command,
                                              sli_cpc_system_cmd_t *rx_command)
{
  sli_cpc_system_property_cmd_t *tx_property_command;
  sli_cpc_system_property_cmd_t *rx_property_command;

  rx_property_command = (sli_cpc_system_property_cmd_t*) rx_command->payload;
  process_uframes_flag = *(bool*)rx_property_command->payload;

  tx_property_command = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  tx_property_command->property_id = PROP_UFRAME_PROCESSING;
  tx_command->length = sizeof(sli_cpc_property_id_t);
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_SET:
 * Property ID: PROP_ENTER_IRQ
 *   The primary requests the secondary to enter IRQ in start_ms for end_ms time.
 ******************************************************************************/
static void on_property_set_enter_irq(sli_cpc_system_cmd_t *tx_command,
                                      sli_cpc_system_cmd_t *rx_command)
{
  sli_cpc_system_property_cmd_t *tx_property_command;
  sli_cpc_system_property_cmd_t *rx_property_command;
  sli_cpc_system_enter_irq_cmd_t *enter_irq_command;

  rx_property_command = (sli_cpc_system_property_cmd_t*) rx_command->payload;
  enter_irq_command = (sli_cpc_system_enter_irq_cmd_t*) rx_property_command->payload;
  enter_irq_end_ms = enter_irq_command->end_in_ms;
  sli_cpc_timer_start_timer_ms(&enter_irq_timer,
                               enter_irq_command->start_in_ms,
                               enter_irq_timer_callback,
                               &enter_irq_end_ms);

  tx_property_command = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  tx_property_command->property_id = PROP_ENTER_IRQ;
  tx_command->length = sizeof(sli_cpc_property_id_t);
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_SET:
 * Property ID: PROP_PRIMARY_VERSION_VALUE
 *   The primary sets its version.
 ******************************************************************************/
static void on_property_set_primary_version_value(sli_cpc_system_cmd_t *tx_command,
                                                  sli_cpc_system_cmd_t *rx_command)
{
  sli_cpc_system_property_cmd_t *tx_property_command;
  sli_cpc_system_property_cmd_t *rx_property_command;
  const sli_cpc_system_primary_version_t *primary_version_payload;

  rx_property_command = (sli_cpc_system_property_cmd_t*) rx_command->payload;
  primary_version_payload = (sli_cpc_system_primary_version_t*) rx_property_command->payload;
  memcpy(&primary_version, primary_version_payload, sizeof(sli_cpc_system_primary_version_t));

  tx_property_command = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  tx_property_command->property_id = PROP_PRIMARY_VERSION_VALUE;
  tx_command->length = sizeof(sli_cpc_property_id_t);
}

/***************************************************************************//**
 * Command ID:  CMD_PROPERTY_SET:
 * Property ID: PROP_BOOTLOADER_REBOOT_MODE
 *   The primary sets the reboot mode.
 ******************************************************************************/
static void on_property_set_bootloader_reboot_mode(sli_cpc_system_cmd_t *tx_command,
                                                   sli_cpc_system_cmd_t *rx_command)
{
  sli_cpc_system_property_cmd_t *tx_property_command;
  sli_cpc_system_property_cmd_t *rx_property_command;
  sli_cpc_system_reboot_mode_t *rx_mode;
  sli_cpc_system_reboot_mode_t *tx_mode;

  tx_property_command = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  rx_property_command = (sli_cpc_system_property_cmd_t*) rx_command->payload;
  rx_mode = (sli_cpc_system_reboot_mode_t*) rx_property_command->payload;
  tx_mode = (sli_cpc_system_reboot_mode_t*) tx_property_command->payload;

  tx_command->length = sizeof(sli_cpc_property_id_t);

  switch (*rx_mode) {
    case REBOOT_APPLICATION:
      /* We can always reset to the application */
      prop_bootloader_reboot_mode = REBOOT_APPLICATION;
      tx_property_command->property_id = PROP_BOOTLOADER_REBOOT_MODE;
      *tx_mode = REBOOT_APPLICATION;
      tx_command->length += sizeof(sli_cpc_system_reboot_mode_t);
      break;

    case REBOOT_BOOTLOADER:
      /* Check if the bootloader interface is present */

#if (defined(SL_CPC_HAS_BOOTLOADER_SUPPORT))
      prop_bootloader_reboot_mode = REBOOT_BOOTLOADER;
      *tx_mode = REBOOT_BOOTLOADER;
#else
      prop_bootloader_reboot_mode = REBOOT_APPLICATION; /* We don't support bootloader reboot, stay in application reboot */
      *tx_mode = REBOOT_APPLICATION; // Reply that we stay in reboot application mode
#endif
      tx_property_command->property_id = PROP_BOOTLOADER_REBOOT_MODE;
      tx_command->length += sizeof(sli_cpc_system_reboot_mode_t);
      break;

    default:
      // The requested bootloader mode doesn't exist. Reply with a
      // PROP_LAST_STATUS::STATUS_INVALID_ARGUMENT instead
      tx_property_command->property_id = PROP_LAST_STATUS;
      *((sl_cpc_system_status_t*)(tx_property_command->payload)) = STATUS_INVALID_ARGUMENT;
      tx_command->length += sizeof(sl_cpc_system_status_t);
      break;
  }
}

static void on_property_set_tx_capability(sli_cpc_system_cmd_t *tx_command,
                                          sli_cpc_system_cmd_t *rx_command)
{
  sli_cpc_system_property_cmd_t *tx_property_command;
  sli_cpc_system_property_cmd_t *rx_property_command;
  uint16_t* rx_capability;
  uint16_t* tx_capability;

  tx_property_command = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  rx_property_command = (sli_cpc_system_property_cmd_t*) rx_command->payload;
  rx_capability = (uint16_t*) rx_property_command->payload;
  tx_capability = (uint16_t*) tx_property_command->payload;

  tx_property_command->property_id = PROP_TX_CAPABILITY;
  *tx_capability = *rx_capability;

  tx_command->length = sizeof(sli_cpc_property_id_t) + sizeof(uint16_t);

  sli_cpc_set_remote_tx_max_payload_length(*rx_capability);
}

/***************************************************************************//**
 * Handler for when the primary sets a read-only property
 ******************************************************************************/
static void on_property_set_read_only(sli_cpc_system_cmd_t *tx_command)
{
  sli_cpc_system_property_cmd_t *tx_property_cmd;

  tx_property_cmd = (sli_cpc_system_property_cmd_t*) tx_command->payload;
  tx_property_cmd->property_id = PROP_LAST_STATUS;
  *((sl_cpc_system_status_t*)(tx_property_cmd->payload)) = STATUS_INVALID_COMMAND_FOR_PROP;

  tx_command->length = sizeof(sli_cpc_property_id_t) + sizeof(sl_cpc_system_status_t);
}

/*******************************************************************************
 ***************************  COMMAND HANDLERS  ********************************
 ******************************************************************************/

/***************************************************************************//**
 * Handle no-op from PRIMARY:
 *   This functions is called when a no-op command is received from the PRIMARY.
 *   The RCP simply sends a no-op back so that the primary can assert the success
 *   of the operation.
 ******************************************************************************/
static void on_noop(sli_cpc_system_cmd_t *noop,
                    uint32_t *reply_data_length)
{
  noop->command_id = CMD_SYSTEM_NOOP;
  noop->length = 0;
  *reply_data_length = SIZEOF_SYSTEM_COMMAND(noop);
}

/***************************************************************************//**
 * Handle reset request
 ******************************************************************************/
SL_WEAK sl_cpc_system_status_t cpc_secondary_on_reset_request(sli_cpc_system_reboot_mode_t reboot_mode)
{
  switch (reboot_mode) {
    case REBOOT_APPLICATION:
      // We can always reboot into application
      return STATUS_OK;
  #if (defined(SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT))
    case REBOOT_BOOTLOADER:
    {
      BootloaderInformation_t btl_info;
      bootloader_getInfo(&btl_info);

      // In case of bootloader reboot, check that a bootloader is present
      if (btl_info.type == NO_BOOTLOADER ) {
        return STATUS_FAILURE;
      }
      return STATUS_OK;
    }
  #endif
    default:
      EFM_ASSERT(false);
      break;
  }

  return STATUS_FAILURE;
}

/***************************************************************************//**
 * Handle reset from PRIMARY:
 *   This functions is called when a reset command is received from the PRIMARY.
 *   The secondary will emit back a reset command with a status indicating
 *   wheter or not it can reset in the desired mode dictated by 'prop_bootloader
 *   _reboot_mode'
 ******************************************************************************/
static void on_reset(sli_cpc_system_cmd_t *reset,
                     uint32_t *reply_data_length,
                     void **on_write_complete_arg)
{
  sl_cpc_system_status_t *reset_status;

  reset_status = (sl_cpc_system_status_t*)(reset->payload);
  reset->command_id = CMD_SYSTEM_RESET;

  reset->length = sizeof(sl_cpc_system_status_t);
  *reply_data_length = SIZEOF_SYSTEM_COMMAND(reset);

  *reset_status = cpc_secondary_on_reset_request(prop_bootloader_reboot_mode);

  // Set on_write_complete argument to ON_WRITE_COMPLETE_RESET. This will
  // indicate to the on_write_complete callback to reset the device.
  // We need to postpone the reset to after the
  // write completion.
  if (*reset_status == STATUS_OK) {
    // The reset will be able to occurre in the mode requested, provide a
    // magic number to the callback so it knows it has to reset the device
    *on_write_complete_arg = (void*)ON_WRITE_COMPLETE_RESET;
  } else {
    // The reset won't occur, don't tell the callback to reset
    *on_write_complete_arg = 0;
  }
}

/***************************************************************************//**
 * Handle property-get from PRIMARY:
 *   This functions is called when a property-get command is received from the
 *   PRIMARY. Causes the SECONDARY to emit a "CMD_PROP_VALUE_IS " command for the
 *   given property identifier.
 ******************************************************************************/
static void on_property_get(sli_cpc_system_cmd_t *rx_command,
                            sli_cpc_system_cmd_t *reply,
                            uint32_t *reply_data_length)
{
  sli_cpc_system_property_cmd_t *rx_property_cmd = (sli_cpc_system_property_cmd_t *)rx_command->payload;

  // Reply to a PROPERTY-GET with a PROPERTY-IS
  reply->command_id = CMD_SYSTEM_PROP_VALUE_IS;

  // Populate the reply command buffer according to the property_id
  switch (rx_property_cmd->property_id) {
    case PROP_LAST_STATUS:
      on_property_get_last_status(reply);
      break;

    case PROP_PROTOCOL_VERSION:
      on_property_get_protocol_version(reply);
      break;

    case PROP_SECONDARY_CPC_VERSION:
      on_property_get_secondary_cpc_version(reply);
      break;

    case PROP_SECONDARY_APP_VERSION:
      on_property_get_secondary_app_version(reply);
      reset_sequence_done = true;
      break;

    case PROP_CAPABILITIES:
      on_property_get_capabilities(reply);
      break;

    case PROP_RX_CAPABILITY:
      on_property_get_rx_capabilities(reply);
      break;

    case PROP_FC_VALIDATION_VALUE:
      on_property_get_fc_validation_value(reply);
      break;

    case PROP_BUS_BITRATE_VALUE:
      on_property_get_bus_bitrate_value(reply);
      break;

    case PROP_BUS_MAX_BITRATE_VALUE:
      on_property_get_bus_max_bitrate_value(reply);
      break;

    case PROP_BOOTLOADER_INFO:
      on_property_get_bootloader_info(reply);
      break;

    case PROP_BOOTLOADER_REBOOT_MODE:
      on_property_get_bootloader_reboot_mode(reply);
      break;

    case PROP_SECURITY_STATE:
      on_property_get_security_state(reply);
      break;

    case PROP_ENDPOINT_STATES:
      on_property_get_endpoint_states(reply);
      break;

#if (SL_CPC_DEBUG_CORE_EVENT_COUNTERS == 1)
    case PROP_CORE_DEBUG_COUNTERS:
      on_property_get_core_debug_counters(reply);
      break;
#endif

    default:
      // Deal with endpoint state range
      if (rx_property_cmd->property_id >= EP_ID_TO_PROPERTY_STATE(0)
          && rx_property_cmd->property_id <= EP_ID_TO_PROPERTY_STATE(255)) {
        uint8_t ep_id = PROPERTY_ID_TO_EP_ID(rx_property_cmd->property_id);
        on_property_get_endpoint_state(reply, ep_id);
        break;
      }

      if (rx_property_cmd->property_id >= EP_ID_TO_PROPERTY_ENCRYPTION(0)
          && rx_property_cmd->property_id <= EP_ID_TO_PROPERTY_ENCRYPTION(255)) {
        uint8_t ep_id = PROPERTY_ID_TO_EP_ID(rx_property_cmd->property_id);
        on_property_get_endpoint_encryption(reply, ep_id);
        break;
      }

      on_property_get_set_not_found(reply);
      break;
  }

  *reply_data_length = SIZEOF_SYSTEM_COMMAND(reply);
}

/***************************************************************************//**
 * Handle property-set from PRIMARY:
 *   This functions is called when a property-set command is received from the
 *   PRIMARY. Causes the RCP to emit a "CMD_PROP_VALUE_IS " command for the given
 *   property identifier.
 ******************************************************************************/
static void on_property_set(sli_cpc_system_cmd_t* rx_command,
                            sli_cpc_system_cmd_t *reply,
                            uint32_t * reply_data_length,
                            void **on_write_complete_arg)
{
  sli_cpc_system_property_cmd_t *rx_property_cmd;

  rx_property_cmd = (sli_cpc_system_property_cmd_t*)(rx_command->payload);

  // Reply to a PROPERTY-GET with a PROPERTY-IS
  reply->command_id = CMD_SYSTEM_PROP_VALUE_IS;

  // Populate the reply command buffer according to the property_id
  if (rx_property_cmd->property_id >= PROP_ENDPOINT_STATE_0
      && rx_property_cmd->property_id <= PROP_ENDPOINT_STATE_255) {
    on_property_set_endpoint_state(PROPERTY_ID_TO_EP_ID(rx_property_cmd->property_id), reply, rx_command, on_write_complete_arg);
  } else {
    switch (rx_property_cmd->property_id) {
      case PROP_LAST_STATUS:
      case PROP_PROTOCOL_VERSION:
      case PROP_SECONDARY_CPC_VERSION:
      case PROP_SECONDARY_APP_VERSION:
      case PROP_CAPABILITIES:
      case PROP_BOOTLOADER_INFO:
      case PROP_SECURITY_STATE:
      case PROP_ENDPOINT_STATES:
        // All those properties fall through read-only handling
        on_property_set_read_only(reply);
        break;

      case PROP_BOOTLOADER_REBOOT_MODE:
        on_property_set_bootloader_reboot_mode(reply, rx_command);
        break;

      case PROP_TX_CAPABILITY:
        on_property_set_tx_capability(reply, rx_command);
        break;

      case PROP_UFRAME_PROCESSING:
        on_property_set_uframe_processing(reply, rx_command);
        break;

      case PROP_ENTER_IRQ:
        on_property_set_enter_irq(reply, rx_command);
        break;

      case PROP_PRIMARY_VERSION_VALUE:
        on_property_set_primary_version_value(reply, rx_command);
        break;

      default:
        on_property_get_set_not_found(reply);
        break;
    }
  }

  *reply_data_length = SIZEOF_SYSTEM_COMMAND(reply);
}

/***************************************************************************//**
 * Called by CPC core when uframe/poll is received
 ******************************************************************************/
static void on_poll(uint8_t endpoint_id,
                    void *arg,
                    void *poll_data,
                    uint32_t poll_data_length,
                    void **reply_data,
                    uint32_t *reply_data_length,
                    void **on_write_complete_arg)
{
  uint32_t frame_type = (uint32_t)arg;
  sli_cpc_system_cmd_t *rx_command = (sli_cpc_system_cmd_t *)poll_data;
  sli_cpc_system_cmd_t *tx_command;
  *reply_data = NULL;
  *reply_data_length = 0;
  (void)endpoint_id;

  if (frame_type != SLI_CPC_HDLC_FRAME_TYPE_UNNUMBERED && frame_type != SLI_CPC_HDLC_FRAME_TYPE_INFORMATION) {
    EFM_ASSERT(false);
    return; // Drop packet
  }

  if (endpoint_id != SL_CPC_ENDPOINT_SYSTEM) {
    EFM_ASSERT(false);
    return; // Drop packet
  }
  // Make sure the length of the payload from the command matches the returned length.
  if (rx_command->length != (poll_data_length - (sizeof(sli_cpc_system_cmd_t) - PAYLOAD_LENGTH_MAX))) {
    EFM_ASSERT(false);
    return; // Drop packet
  }

  *on_write_complete_arg = NULL;

  // Allocate command buffer. Freed on acknowledgment. (On write completion callback)
  sl_status_t status = sli_cpc_get_system_command_buffer(&tx_command);

  // If no more memory, leave the reply data to NULL and let the upper layer retry later
  if (status != SL_STATUS_OK) {
    return;
  }

  *reply_data = tx_command;

  // Assign the sequence number of the request to the reply so the primary can
  // route it back to the right request.
  tx_command->seq = rx_command->seq;

  // Only the reset can be a u-frame (non encrypted)
  if (frame_type == SLI_CPC_HDLC_FRAME_TYPE_UNNUMBERED) {
    sli_cpc_system_property_cmd_t *rx_property_cmd = (sli_cpc_system_property_cmd_t *)rx_command->payload;
    switch (rx_command->command_id) {
      case CMD_SYSTEM_RESET:
        on_reset((sli_cpc_system_cmd_t *)*reply_data, reply_data_length, on_write_complete_arg);
        break;

      case CMD_SYSTEM_PROP_VALUE_GET:
        if (rx_property_cmd->property_id == PROP_RX_CAPABILITY
            || rx_property_cmd->property_id == PROP_CAPABILITIES
            || rx_property_cmd->property_id == PROP_BUS_BITRATE_VALUE
            || rx_property_cmd->property_id == PROP_BUS_MAX_BITRATE_VALUE
            || rx_property_cmd->property_id == PROP_PROTOCOL_VERSION
            || rx_property_cmd->property_id == PROP_BOOTLOADER_INFO
            || rx_property_cmd->property_id == PROP_SECONDARY_CPC_VERSION
            || rx_property_cmd->property_id == PROP_SECONDARY_APP_VERSION) {
          on_property_get(rx_command, (sli_cpc_system_cmd_t *)*reply_data, reply_data_length);
        }
        break;

      case CMD_SYSTEM_PROP_VALUE_SET:
        if (rx_property_cmd->property_id == PROP_BOOTLOADER_REBOOT_MODE
            || rx_property_cmd->property_id == PROP_TX_CAPABILITY
            || rx_property_cmd->property_id == PROP_PRIMARY_VERSION_VALUE) {
          on_property_set(rx_command, (sli_cpc_system_cmd_t *)*reply_data, reply_data_length, on_write_complete_arg);
        }
        break;

      default:
        EFM_ASSERT(false);
        return; // Drop packet
    }
  } else if (frame_type == SLI_CPC_HDLC_FRAME_TYPE_INFORMATION) {
    switch (rx_command->command_id) {
      case CMD_SYSTEM_NOOP:
        on_noop((sli_cpc_system_cmd_t *)*reply_data, reply_data_length);
        break;

      case CMD_SYSTEM_PROP_VALUE_GET:
        on_property_get(rx_command, (sli_cpc_system_cmd_t *)*reply_data, reply_data_length);
        break;

      case CMD_SYSTEM_PROP_VALUE_SET:
        on_property_set(rx_command, (sli_cpc_system_cmd_t *)*reply_data, reply_data_length, on_write_complete_arg);
        break;

      default:
        // Command not supported
        EFM_ASSERT(false);
        return; // Drop packet
    }
  } else {
    EFM_ASSERT(false);
    return; // Drop packet
  }
}

/***************************************************************************//**
 * Function called when enter_irq_timer expires.
 ******************************************************************************/
static void enter_irq_timer_callback(sli_cpc_timer_handle_t *handle,
                                     void *data)
{
  (void)handle;

  uint32_t now_ms = sli_cpc_timer_tick_to_ms(sli_cpc_timer_get_tick_count());
  uint32_t end_ms = *(uint32_t*) data;
  while ((sli_cpc_timer_tick_to_ms(sli_cpc_timer_get_tick_count()) - now_ms) <= end_ms) ;
}
