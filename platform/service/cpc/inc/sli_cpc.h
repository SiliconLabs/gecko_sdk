/***************************************************************************/ /**
 * @file
 * @brief CPC Internal Definitions
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

#ifndef SLI_CPC_H
#define SLI_CPC_H

#include <stddef.h>
#include <stdarg.h>

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#include "sl_status.h"
#include "sl_enum.h"
#include "sl_slist.h"
#include "sli_mem_pool.h"
#include "sli_cpc_types.h"
#include "sli_cpc_timer.h"
#include "sl_cpc.h"
#include "sl_cpc_config.h"
#include "sli_cpc_system_common.h"
#if defined(SL_CATALOG_CPC_SECURITY_PRESENT)
#include "sl_cpc_security.h"
#include "sl_cpc_security_config.h"
#include "sli_cpc_security.h"
#endif

#if defined(SL_CATALOG_CPC_JOURNAL_PRESENT)
#include "sl_cpc_journal.h"
#else
#define SL_CPC_JOURNAL_RECORD_ERROR(string, value) ((void)(string), (void)(value))
#define SL_CPC_JOURNAL_RECORD_WARNING(string, value) ((void)(string), (void)(value))
#define SL_CPC_JOURNAL_RECORD_INFO(string, value) ((void)(string), (void)(value))
#define SL_CPC_JOURNAL_RECORD_DEBUG(string, value) ((void)(string), (void)(value))
#define SL_CPC_JOURNAL_RECORD_TRACE(string, value) ((void)(string), (void)(value))
#endif

#if (!defined(SL_CATALOG_EMLIB_CORE_PRESENT))
#include "mcu.h"
#else
#include "em_core.h"
#include "sl_atomic.h"

#define MCU_DECLARE_IRQ_STATE   CORE_DECLARE_IRQ_STATE
#define MCU_ENTER_CRITICAL      CORE_ENTER_CRITICAL
#define MCU_EXIT_CRITICAL       CORE_EXIT_CRITICAL
#define MCU_ATOMIC_SECTION      CORE_ATOMIC_SECTION
#define MCU_ENTER_ATOMIC        CORE_ENTER_ATOMIC
#define MCU_EXIT_ATOMIC         CORE_EXIT_ATOMIC
#define MCU_ATOMIC_LOAD         sl_atomic_load
#define MCU_ATOMIC_STORE        sl_atomic_store
#endif

#define SLI_CPC_PROTOCOL_VERSION            (5)

#define SLI_CPC_ENDPOINT_SYSTEM             (1)

#if (!defined(SL_CATALOG_CPC_SECURITY_PRESENT))
#define SL_CPC_ENDPOINT_SECURITY_ENABLED    (0)
#else
#if (SL_CPC_SECURITY_ENABLED >= 1)
#define SL_CPC_ENDPOINT_SECURITY_ENABLED    (1)
#else
#define SL_CPC_ENDPOINT_SECURITY_ENABLED    (0)
#endif
#endif

#if defined(SL_CATALOG_BLUETOOTH_NCP_PRESENT)
#define SLI_CPC_ENDPOINT_BLUETOOTH_ENABLED  (1)
#else
#define SLI_CPC_ENDPOINT_BLUETOOTH_ENABLED  (0)
#endif

#if defined(SL_CATALOG_RAIL_NCP_PRESENT)
#define SLI_CPC_ENDPOINT_RAIL_ENABLED (2)
#else
#define SLI_CPC_ENDPOINT_RAIL_ENABLED (0)
#endif

#if defined(SL_CATALOG_ZIGBEE_NCP_PRESENT)
#define SLI_CPC_ENDPOINT_ZIGBEE_ENABLED (1)
#else
#define SLI_CPC_ENDPOINT_ZIGBEE_ENABLED (0)
#endif

#if defined(SL_CATALOG_ZWAVE_NCP_PRESENT)
#define SLI_CPC_ENDPOINT_ZWAVE_ENABLED  (1)
#else
#define SLI_CPC_ENDPOINT_ZWAVE_ENABLED  (0)
#endif

#if defined(SL_CATALOG_CONNECT_NCP_PRESENT)
#define SLI_CPC_ENDPOINT_CONNECT_ENABLED  (1)
#else
#define SLI_CPC_ENDPOINT_CONNECT_ENABLED  (0)
#endif

#if defined(SL_CATALOG_GPIO_NCP_PRESENT)
#define SLI_CPC_ENDPOINT_GPIO_ENABLED  (1)
#else
#define SLI_CPC_ENDPOINT_GPIO_ENABLED  (0)
#endif

#if defined(SL_CATALOG_OPENTHREAD_NCP_PRESENT)
#define SLI_CPC_ENDPOINT_OPENTHREAD_ENABLED (1)
#else
#define SLI_CPC_ENDPOINT_OPENTHREAD_ENABLED (0)
#endif

#if defined(SL_CATALOG_WISUN_NCP_PRESENT)
#define SLI_CPC_ENDPOINT_WISUN_ENABLED  (1)
#else
#define SLI_CPC_ENDPOINT_WISUN_ENABLED  (0)
#endif

#if defined(SL_CATALOG_WIFI_NCP_PRESENT)
#define SLI_CPC_ENDPOINT_WIFI_ENABLED  (1)
#else
#define SLI_CPC_ENDPOINT_WIFI_ENABLED  (0)
#endif

#if defined(SL_CATALOG_15_4_NCP_PRESENT)
#define SLI_CPC_ENDPOINT_15_4_ENABLED  (1)
#else
#define SLI_CPC_ENDPOINT_15_4_ENABLED  (0)
#endif

#if defined(SL_CATALOG_CLI_NCP_PRESENT)
#define SLI_CPC_ENDPOINT_CLI_ENABLED  (1)
#else
#define SLI_CPC_ENDPOINT_CLI_ENABLED  (0)
#endif

#if defined(SL_CATALOG_CLI_NCP_PRESENT)
#define SLI_CPC_ENDPOINT_CLI_ENABLED  (1)
#else
#define SLI_CPC_ENDPOINT_CLI_ENABLED  (0)
#endif

#if defined(SL_CATALOG_BLUETOOTH_RCP_PRESENT)
#define SL_CPC_ENDPOINT_BLUETOOTH_RCP_ENABLED  (1)
#else
#define SL_CPC_ENDPOINT_BLUETOOTH_RCP_ENABLED  (0)
#endif

#if defined(SL_CATALOG_ACP_PRESENT)
#define SL_CPC_ENDPOINT_ACP_ENABLED  (1)
#else
#define SL_CPC_ENDPOINT_ACP_ENABLED  (0)
#endif

#if defined(SL_CATALOG_SE_CPC_PRESENT)
#define SL_CPC_ENDPOINT_SE_ENABLED  (1)
#else
#define SL_CPC_ENDPOINT_SE_ENABLED  (0)
#endif

#if defined(SL_CATALOG_CPC_NVM3_PRESENT)
#define SL_CPC_ENDPOINT_NVM3_ENABLED  (1)
#else
#define SL_CPC_ENDPOINT_NVM3_ENABLED  (0)
#endif

// Frame Flags
// I-Frame is enabled by default; this flag MUST be set to disable the I-Frame support by the endpoint
#define SL_CPC_ENDPOINT_FLAG_IFRAME_DISABLE             (0x01 << 0)
// U-Frame is disabled by default; this flag MUST be set to enable U-Frame support by the endpoint
#define SL_CPC_ENDPOINT_FLAG_UFRAME_ENABLE              (0x01 << 1)
// Disable non-poll/final U-Frame
#define SL_CPC_ENDPOINT_FLAG_UFRAME_INFORMATION_DISABLE (0x01 << 2)
// Disable encryption
// SL_CPC_ENDPOINT_FLAG_DISABLE_ENCRYPTION              (0x01 << 3) is defined in public header
// Endpoint was opened using legacy API
#define SL_CPC_ENDPOINT_FLAG_LEGACY_API                 (0x01 << 4)

// Legacy Flags
#define SL_CPC_OPEN_ENDPOINT_FLAG_IFRAME_DISABLE        SL_CPC_ENDPOINT_FLAG_IFRAME_DISABLE
#define SL_CPC_OPEN_ENDPOINT_FLAG_UFRAME_ENABLE         SL_CPC_ENDPOINT_FLAG_UFRAME_ENABLE
#define SL_CPC_OPEN_ENDPOINT_FLAG_UFRAME_INFORMATION_DISABLE SL_CPC_ENDPOINT_FLAG_UFRAME_INFORMATION_DISABLE
// SL_CPC_OPEN_ENDPOINT_FLAG_DISABLE_ENCRYPTION         is defined in public header

// SL_CPC_FLAG_NO_BLOCK = 0x01 << 0
#define SL_CPC_FLAG_UNNUMBERED_INFORMATION      (0x01 << 1)
#define SL_CPC_FLAG_UNNUMBERED_POLL_FINAL       (0x01 << 2)
#define SL_CPC_FLAG_UNNUMBERED_ACKNOWLEDGE      (0x01 << 3)
#define SL_CPC_FLAG_INFORMATION_POLL_FINAL      (0x01 << 4)
#define SL_CPC_FLAG_BLOCKING_WRITE              (0x01 << 5)

/// @brief Enumeration representing the possible id
SL_ENUM(sl_cpc_service_endpoint_id_t){
  SL_CPC_ENDPOINT_SYSTEM = 0,          ///< System control
#if (SL_CPC_ENDPOINT_SECURITY_ENABLED >= 1)
  SL_CPC_ENDPOINT_SECURITY = 1,        ///< Security - related functionality
#endif
#if (SLI_CPC_ENDPOINT_BLUETOOTH_ENABLED >= 1)
  SL_CPC_ENDPOINT_BLUETOOTH = 2,       ///< Bluetooth endpoint
#endif
#if (SLI_CPC_ENDPOINT_RAIL_ENABLED >= 1)
  SL_CPC_SLI_CPC_ENDPOINT_RAIL_DOWNSTREAM = 3, ///< RAIL downstream endpoint
  SL_CPC_SLI_CPC_ENDPOINT_RAIL_UPSTREAM = 4,   ///< RAIL upstream endpoint
#endif
#if (SLI_CPC_ENDPOINT_ZIGBEE_ENABLED >= 1)
  SL_CPC_ENDPOINT_ZIGBEE = 5,          ///< ZigBee EZSP endpoint
#endif
#if (SLI_CPC_ENDPOINT_ZWAVE_ENABLED >= 1)
  SL_CPC_ENDPOINT_ZWAVE = 6,           ///< Z-Wave endpoint
#endif
#if (SLI_CPC_ENDPOINT_CONNECT_ENABLED >= 1)
  SL_CPC_ENDPOINT_CONNECT = 7,         ///< Connect endpoint
  #endif
#if (SLI_CPC_ENDPOINT_GPIO_ENABLED >= 1)
  SL_CPC_ENDPOINT_GPIO = 8,            ///< GPIO endpoint for controlling GPIOs on SECONDARYs
#endif
#if (SLI_CPC_ENDPOINT_OPENTHREAD_ENABLED >= 1)
  SL_CPC_ENDPOINT_OPENTHREAD = 9,      ///< Openthread Spinel endpoint
#endif
#if (SLI_CPC_ENDPOINT_WISUN_ENABLED >= 1)
  SL_CPC_ENDPOINT_WISUN = 10,           ///< WiSun endpoint
#endif
#if (SLI_CPC_ENDPOINT_WIFI_ENABLED >= 1)
  SL_CPC_ENDPOINT_WIFI = 11,           ///< WiFi endpoint(main control)
#endif
#if (SLI_CPC_ENDPOINT_15_4_ENABLED >= 1)
  SL_CPC_ENDPOINT_15_4 = 12,           ///< 802.15.4 endpoint
#endif
#if (SLI_CPC_ENDPOINT_CLI_ENABLED >= 1)
  SL_CPC_ENDPOINT_CLI = 13,            ///< Ascii based CLI for stacks / applications
#endif
#if (SL_CPC_ENDPOINT_BLUETOOTH_RCP_ENABLED >= 1)
  SL_CPC_ENDPOINT_BLUETOOTH_RCP = 14,  ///< Bluetooth RCP endpoint
#endif
#if (SL_CPC_ENDPOINT_ACP_ENABLED >= 1)
  SL_CPC_ENDPOINT_ACP = 15,            ///< ACP endpoint
#endif
#if (SL_CPC_ENDPOINT_SE_ENABLED >= 1)
  SL_CPC_ENDPOINT_SE = 16,             ///< Secure Engine endpoint
#endif
#if (SL_CPC_ENDPOINT_NVM3_ENABLED >= 1)
  SL_CPC_ENDPOINT_NVM3 = 17,           ///< NVM3 endpoint
#endif
  SL_CPC_ENDPOINT_LAST_ID_MARKER,      // DO NOT USE THIS ENDPOINT ID
};

#define SLI_CPC_SERVICE_ENDPOINT_ID_START     ((uint8_t)SL_CPC_ENDPOINT_SYSTEM)
#define SLI_CPC_SERVICE_ENDPOINT_ID_END       ((uint8_t)SL_CPC_ENDPOINT_LAST_ID_MARKER - 1)
#define SLI_CPC_SERVICE_ENDPOINT_MAX_COUNT    (SLI_CPC_SERVICE_ENDPOINT_ID_END - SLI_CPC_SERVICE_ENDPOINT_ID_START + 1)

/***************************************************************************//**
 * The maximum size of a system endpoint command buffer.
 *
 * @note
 *   For the moment, this value must be manually set.
 *
 * @note : it is set to the size of the payload of a
 * CMD_PROPERTY_GET::PROP_ENDPOINT_STATES.
 *
 ******************************************************************************/
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define SL_CPC_ENDPOINT_MAX_COUNT  256

#define SLI_CPC_SYSTEM_COMMAND_BUFFER_SIZE \
  (sizeof(sli_cpc_system_cmd_t)            \
   + sizeof(sli_cpc_system_property_cmd_t) \
   + SL_CPC_ENDPOINT_MAX_COUNT * sizeof(sl_cpc_endpoint_state_t) / 2)

#ifndef SLI_CPC_SYSTEM_COMMAND_BUFFER_COUNT
#define SLI_CPC_SYSTEM_COMMAND_BUFFER_COUNT 5
#endif

#ifndef SLI_CPC_SYSTEM_COMMAND_HANDLE_COUNT
#define SLI_CPC_SYSTEM_COMMAND_HANDLE_COUNT 2
#endif

#if (SL_CPC_ENDPOINT_SECURITY_ENABLED >= 1)
#define SLI_CPC_RX_DATA_MAX_LENGTH          (SL_CPC_RX_PAYLOAD_MAX_LENGTH + 2 + SLI_SECURITY_TAG_LENGTH_BYTES)
#else
#define SLI_CPC_RX_DATA_MAX_LENGTH             (SL_CPC_RX_PAYLOAD_MAX_LENGTH + 2)
#endif
#define SLI_CPC_HDLC_REJECT_MAX_COUNT          ((SL_CPC_RX_BUFFER_MAX_COUNT / 2) + 1)
#define SLI_CPC_RX_QUEUE_ITEM_MAX_COUNT        (SL_CPC_RX_BUFFER_MAX_COUNT - 1)
#define SLI_CPC_TX_QUEUE_ITEM_SFRAME_MAX_COUNT (SLI_CPC_RX_QUEUE_ITEM_MAX_COUNT)
#define SLI_CPC_BUFFER_HANDLE_MAX_COUNT        (SL_CPC_TX_QUEUE_ITEM_MAX_COUNT + SL_CPC_RX_BUFFER_MAX_COUNT + SLI_CPC_TX_QUEUE_ITEM_SFRAME_MAX_COUNT)
#define SLI_CPC_RE_TRANSMIT                    (10)
#define SLI_CPC_INIT_RE_TRANSMIT_TIMEOUT_MS    (100)
#define SLI_CPC_MAX_RE_TRANSMIT_TIMEOUT_MS     (5000)
#define SLI_CPC_MIN_RE_TRANSMIT_TIMEOUT_MS     (5)
#define SLI_CPC_DISCONNECTION_NOTIFICATION_TIMEOUT_MS  (1000)
#define SLI_CPC_MIN_RE_TRANSMIT_TIMEOUT_MINIMUM_VARIATION_MS (5)
#define SLI_CPC_SYSTEM_CMD_TIMEOUT_MS           (10000)

#if (SL_CPC_ENDPOINT_SECURITY_ENABLED >= 1)
#if (SL_CPC_RX_PAYLOAD_MAX_LENGTH > 4079)
  #error Invalid SL_CPC_RX_PAYLOAD_MAX_LENGTH; Must be less or equal to 4079
#endif
#else
#if (SL_CPC_RX_PAYLOAD_MAX_LENGTH > 4087)
  #error Invalid SL_CPC_RX_PAYLOAD_MAX_LENGTH; Must be less or equal to 4087
#endif
#endif

#if !defined(SLI_CPC_ENDPOINT_TEMPORARY_MAX_COUNT)
#if defined(SL_CATALOG_CPC_PERF_PRESENT)
#define SLI_CPC_ENDPOINT_TEMPORARY_MAX_COUNT      (10)
#else
#define SLI_CPC_ENDPOINT_TEMPORARY_MAX_COUNT      (0) // Not yet available
#endif
#endif

#define SLI_CPC_TEMPORARY_ENDPOINT_ID_START   100
#define SLI_CPC_TEMPORARY_ENDPOINT_ID_END     SLI_CPC_TEMPORARY_ENDPOINT_ID_START + SLI_CPC_ENDPOINT_TEMPORARY_MAX_COUNT - 1
#if (SLI_CPC_TEMPORARY_ENDPOINT_ID_END > 254)
#error Invalid TEMPORARY ENDPOINT COUNT
#endif

#define SLI_CPC_ENDPOINT_MIN_COUNT  (SLI_CPC_ENDPOINT_SYSTEM + SL_CPC_ENDPOINT_SECURITY_ENABLED)

#define SLI_CPC_ENDPOINT_INTERNAL_COUNT                 (SLI_CPC_ENDPOINT_SYSTEM + SL_CPC_ENDPOINT_SECURITY_ENABLED + SLI_CPC_ENDPOINT_BLUETOOTH_ENABLED          \
                                                         + SLI_CPC_ENDPOINT_RAIL_ENABLED + SLI_CPC_ENDPOINT_ZIGBEE_ENABLED + SLI_CPC_ENDPOINT_ZWAVE_ENABLED       \
                                                         + SLI_CPC_ENDPOINT_CONNECT_ENABLED + SLI_CPC_ENDPOINT_GPIO_ENABLED + SLI_CPC_ENDPOINT_OPENTHREAD_ENABLED \
                                                         + SLI_CPC_ENDPOINT_WISUN_ENABLED + SLI_CPC_ENDPOINT_WIFI_ENABLED + SLI_CPC_ENDPOINT_CLI_ENABLED          \
                                                         + SL_CPC_ENDPOINT_BLUETOOTH_RCP_ENABLED + SL_CPC_ENDPOINT_ACP_ENABLED + SL_CPC_ENDPOINT_SE_ENABLED       \
                                                         + SL_CPC_ENDPOINT_NVM3_ENABLED)

#if !defined(SLI_CPC_ENDPOINT_COUNT)
#define SLI_CPC_ENDPOINT_COUNT          (SLI_CPC_ENDPOINT_INTERNAL_COUNT + SL_CPC_USER_ENDPOINT_MAX_COUNT + SLI_CPC_ENDPOINT_TEMPORARY_MAX_COUNT)
#endif

#if (SLI_CPC_ENDPOINT_COUNT > SL_CPC_ENDPOINT_MAX_COUNT)
  #error Invalid SLI_CPC_ENDPOINT_COUNT; Must be less than SL_CPC_ENDPOINT_MAX_COUNT
#elif (SLI_CPC_ENDPOINT_COUNT < SLI_CPC_ENDPOINT_MIN_COUNT)
  #error Invalid SLI_CPC_ENDPOINT_COUNT; Must be greater than SLI_CPC_ENDPOINT_MIN_COUNT
#endif

#define SLI_CPC_HDLC_HEADER_MAX_COUNT       (SL_CPC_RX_BUFFER_MAX_COUNT                                       \
                                             + (MIN(SL_CPC_TRANSMIT_WINDOW_MAX_SIZE * SLI_CPC_ENDPOINT_COUNT, \
                                                    SLI_CPC_BUFFER_HANDLE_MAX_COUNT)))

#if SL_CPC_USER_ENDPOINT_MAX_COUNT > 10
#error "SL_CPC_USER_ENDPOINT_MAX_COUNT must be less than 10"
#endif

// Signal count max = closing signal per endpoint + tx queue items + rx queue items
#define EVENT_SIGNAL_MAX_COUNT    SLI_CPC_ENDPOINT_COUNT + SL_CPC_TX_QUEUE_ITEM_MAX_COUNT + SLI_CPC_RX_QUEUE_ITEM_MAX_COUNT

SL_ENUM(sl_cpc_signal_type_t) {
  SL_CPC_SIGNAL_RX,
  SL_CPC_SIGNAL_TX,
  SL_CPC_SIGNAL_CLOSED,
  SL_CPC_SIGNAL_SYSTEM,
};

SL_ENUM(sl_cpc_reject_reason_t){
  SL_CPC_REJECT_NO_ERROR = 0,
  SL_CPC_REJECT_CHECKSUM_MISMATCH,
  SL_CPC_REJECT_SEQUENCE_MISMATCH,
  SL_CPC_REJECT_OUT_OF_MEMORY,
  SL_CPC_REJECT_SECURITY_ISSUE,
  SL_CPC_REJECT_UNREACHABLE_ENDPOINT,
  SL_CPC_REJECT_ERROR
};

SL_ENUM(sl_cpc_buffer_handle_type_t) {
  SL_CPC_UNKNOWN_BUFFER_HANDLE,
  SL_CPC_RX_INTERNAL_BUFFER_HANDLE,
  SL_CPC_RX_USER_BUFFER_HANDLE,
  SL_CPC_TX_REJECT_BUFFER_HANDLE,
  SL_CPC_TX_DATA_BUFFER_HANDLE,
  SL_CPC_TX_SFRAME_BUFFER_HANDLE,
};

typedef void (*sl_cpc_dispatcher_fnct_t)(void *data);

/**
 * @brief This structure defines cpc dispatcher handle.
 */
typedef struct {
  sl_slist_node_t node;                            ///< node
  sl_cpc_dispatcher_fnct_t fnct;                   ///< fnct
  void *data;                                      ///< data
  bool submitted;                                  ///< submitted
} sl_cpc_dispatcher_handle_t;

/**
 * @brief This structure defines cpc buffer handle.
 */
typedef struct {
  void *hdlc_header;                               ///< hdlc header
  void *data;                                      ///< data
#if (SL_CPC_ENDPOINT_SECURITY_ENABLED >= 1)
  void *security_tag;
#endif
  uint16_t data_length;                            ///< data_length
  uint8_t fcs[2];                                  ///< fcs
  uint8_t control;                                 ///< control
  uint8_t address;                                 ///< address
  uint8_t ref_count;                               ///< ref count
  sl_cpc_buffer_handle_type_t type;                ///< buffer handle type
  sl_cpc_endpoint_t *endpoint;                     ///< endpoint
  sl_cpc_reject_reason_t reason;                   ///< reason
  void *arg;                                       ///< arg
  bool on_write_complete_pending;                  ///< on write complete pending
  sl_status_t write_status;                        ///< write status
  sl_slist_node_t driver_node;                     ///< driver node
  sl_slist_node_t core_node;                       ///< core node
} sl_cpc_buffer_handle_t;

/**
 * @brief This structure defines cpc receive queue item.
 */
typedef struct {
  sl_slist_node_t node;                            ///< node
  void *data;                                      ///< data
  uint16_t data_length;                            ///< data length
  sl_cpc_buffer_handle_type_t buffer_type;         ///< buffer handle type
} sl_cpc_receive_queue_item_t;

#ifdef __cplusplus
extern "C"
{
#endif
// -----------------------------------------------------------------------------
// Prototypes

/***************************************************************************//**
 * Initialize Silicon Labs Internal Service endpoint.
 *
 * @param[in] endpoint_handle  Endpoint Handle.
 *
 * @param[in] id  Endpoint ID.
 *
 * @param[in] flags  Initialization flags. Reserved for future used
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_init_service_endpoint(sl_cpc_endpoint_handle_t *endpoint_handle,
                                          sl_cpc_service_endpoint_id_t id,
                                          uint8_t flags);

/***************************************************************************//**
 * Initialize temporary endpoint.
 *
 * @param[in] endpoint_handle  Endpoint Handle.
 *
 * @param[out] id  Endpoint ID.
 *
 * @param[in] flags  Initialization flags. Reserved for future used
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_init_temporary_endpoint(sl_cpc_endpoint_handle_t *endpoint_handle,
                                            uint8_t *id,
                                            uint8_t flags);

/***************************************************************************//**
 * Open Silicon Labs Internal Service endpoint.
 *
 * @param[in] endpoint_handle  Endpoint Handle.
 *
 * @param[in] id  Endpoint ID.
 *
 * @param[in] flags  Endpoint flags.
 *                      SL_CPC_OPEN_ENDPOINT_FLAG_NONE                Default behaviors
 *                      SL_CPC_OPEN_ENDPOINT_FLAG_DISABLE_ENCRYPTION  Disable encryption on the endpoint
 *                      SL_CPC_OPEN_ENDPOINT_FLAG_IFRAME_DISABLE      Discard I - frame received on the endpoint
 *                      SL_CPC_OPEN_ENDPOINT_FLAG_UFRAME_ENABLE       Enable reception of U-frame on the endpoint
 *                      SL_CPC_OPEN_ENDPOINT_FLAG_UFRAME_INFORMATION_DISABLE  Only allow U-frame of type P/F
 *
 * @param[in] tx_window_size  Endpoint TX Window size.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_open_service_endpoint (sl_cpc_endpoint_handle_t *endpoint_handle,
                                           sl_cpc_service_endpoint_id_t id,
                                           uint8_t flags,
                                           uint8_t tx_window_size);

/***************************************************************************//**
 * Open temporary endpoint.
 *
 * @param[in] endpoint_handle  Endpoint Handle.
 *
 * @param[out] id  Endpoint ID.
 *
 * @param[in] flags  Endpoint flags:
 *                      SL_CPC_OPEN_ENDPOINT_FLAG_NONE                Default behaviors
 *                      SL_CPC_OPEN_ENDPOINT_FLAG_DISABLE_ENCRYPTION  Disable encryption on the endpoint
 *                      SL_CPC_OPEN_ENDPOINT_FLAG_IFRAME_DISABLE      Discard I-frame received on the endpoint
 *                      SL_CPC_OPEN_ENDPOINT_FLAG_UFRAME_ENABLE       Enable reception of u-frame on the endpoint
 *                      SL_CPC_OPEN_ENDPOINT_FLAG_UFRAME_INFORMATION_DISABLE  Only allow U-frame of type P/F
 *
 * @param[in] tx_window_size  Endpoint TX Window size.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_open_temporary_endpoint(sl_cpc_endpoint_handle_t *endpoint_handle,
                                            uint8_t *id,
                                            uint8_t flags,
                                            uint8_t tx_window_size);

/***************************************************************************//**
 * Initialize CPC buffers' handling module.
 ******************************************************************************/
sl_status_t sli_cpc_memory_init(void);

/***************************************************************************//**
 * @brief Get a handle to a CPC write buffer.
 *
 * Retrieves a handle for write operations. In environments with RTOS,
 * it handles semaphore acquisition based on the given timeout.
 *
 * @param[out] handle  Pointer to store the retrieved buffer handle.
 * @param[in] block    If true, the function blocks until the buffer is available or
 *                     timeout occurs; non-blocking otherwise.
 * @param[in] timeout  Timeout for buffer availability in milliseconds used only when
 *                     RTOS is used.
 *
 * @return             Status code indicating operation result
 ******************************************************************************/
sl_status_t sli_cpc_get_write_buffer_handle(sl_cpc_buffer_handle_t **handle, bool block, uint32_t timeout);

/***************************************************************************//**
 * Get a CPC buffer handle.
 *
 * @param[out] handle  Address of the variable that will receive the handle
 *                     pointer.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_get_buffer_handle(sl_cpc_buffer_handle_t **handle, sl_cpc_buffer_handle_type_t type);

/***************************************************************************//**
 * Get a CPC header buffer.
 *
 * @param[out] buffer  Address of the variable that will receive the buffer
 *                     pointer.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_get_hdlc_header_buffer(void **buffer);

/***************************************************************************//**
 * Get a CPC header and buffer for transmitting a reject packet.
 *
 * @param[out] handle  Address of the variable that will receive the buffer
 *                     pointer.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_get_reject_buffer(sl_cpc_buffer_handle_t **handle);

/***************************************************************************//**
 * Get a CPC RAW buffer for reception.
 *
 * @param[out] handle  Address of the variable that will receive the RAW buffer
 *                     pointer.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_get_raw_rx_buffer(void **raw_rx_buffer);

/***************************************************************************//**
 * Free a CPC RAW rx buffer.
 *
 * @param[out] handle  Address of the variable that will receive the RAW buffer.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_free_raw_rx_buffer(void *raw_rx_buffer);

/***************************************************************************//**
 * Get a CPC buffer for reception. This also allocates a buffer for the HDLC
 * header and a RX buffer if necessary.
 *
 * @param[out] handle  Address of the variable that will receive the buffer
 *                     pointer.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_get_buffer_handle_for_rx(sl_cpc_buffer_handle_t **handle);

/***************************************************************************//**
 * Free header, buffer and handle.
 *
 * @param[in] handle  Handle to free.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_free_buffer_handle(sl_cpc_buffer_handle_t *handle);

/***************************************************************************//**
 * Allocate queue item and push data buffer in receive queue then free
 * header and buffer handle.
 *
 * @param[in] handle  Handle to free.
 * @param[in] head    Queue head pointer.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_push_back_rx_data_in_receive_queue(sl_cpc_buffer_handle_t *handle,
                                                       sl_slist_node_t **head,
                                                       uint16_t data_length);

/***************************************************************************//**
 * Free CPC HDLC header.
 *
 * @param[in] buffer  Pointer to hdlc header to free.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_free_hdlc_header(void *data);

/***************************************************************************//**
 * Get a receive queue item.
 *
 * @param[out] item  Address of the variable that will receive the item pointer.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_get_receive_queue_item(sl_cpc_receive_queue_item_t **item);

/***************************************************************************//**
 * Push receive queue item queued to the postponed free list
 *
 * @param[in] item  Pointer to item to free.
 *
 * @param[out] data  Pointer to variable that will receive the rx buffer pointer.
 *
 * @param[out] data_length  Pointer to variable that will receive the data length.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_push_receive_queue_item_to_postponed_list(sl_cpc_receive_queue_item_t *rx_queue_item,
                                                              void **data,
                                                              uint16_t * data_length);

/***************************************************************************//**
 * Free receive queue item and data buffer.
 *
 * @param[in] item  Pointer to item to free.
 ******************************************************************************/
void sli_cpc_free_receive_queue_item(sl_cpc_receive_queue_item_t *item);

/***************************************************************************//**
 * Get an endoint.
 *
 * @param[out] endpoint  Address of the variable that will receive the item pointer.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_get_endpoint(sl_cpc_endpoint_t **endpoint);

/***************************************************************************//**
 * Free endpoint.
 *
 * @param[in] endpoint  Pointer to endpoint to free.
 ******************************************************************************/
void sli_cpc_free_endpoint(sl_cpc_endpoint_t *endpoint);

/***************************************************************************//**
 * Free internal rx buffer; Not pushed in RX Queue .
 *
 * @param[in] data  Pointer to data buffer to free.
 *
 * @return Status code .
 ******************************************************************************/
sl_status_t sli_cpc_free_rx_buffer(void *data);

/***************************************************************************//**
 * Signal process needed.
 ******************************************************************************/
void sli_cpc_signal_event(sl_cpc_signal_type_t signal_type);

/***************************************************************************//**
 * Push back a list item containing an allocated buffer handle for the core
 ******************************************************************************/
void sli_cpc_push_back_core_buffer_handle(sl_slist_node_t **head, sl_cpc_buffer_handle_t *buf_handle);

/***************************************************************************//**
 * Pop a buffer handle from a list owned by the CPC core
 ******************************************************************************/
sl_cpc_buffer_handle_t* sli_cpc_pop_core_buffer_handle(sl_slist_node_t **head);

/***************************************************************************//**
 * Remove a list item containing an allocated buffer handle for the core
 ******************************************************************************/
void sli_cpc_remove_core_buffer_handle(sl_slist_node_t **head, sl_cpc_buffer_handle_t *buffer_handle);

/***************************************************************************//**
 * Push a list item containing an allocated buffer handle for the core
 ******************************************************************************/
void sli_cpc_push_core_buffer_handle(sl_slist_node_t **head, sl_cpc_buffer_handle_t *buf_handle);

/***************************************************************************//**
 * Pop a buffer handle from a list owned by the CPC driver
 ******************************************************************************/
sl_cpc_buffer_handle_t* sli_cpc_pop_driver_buffer_handle(sl_slist_node_t **head);

/***************************************************************************//**
 * Remove a buffer handle from a list owned by the CPC driver
 ******************************************************************************/
void sli_cpc_remove_driver_buffer_handle(sl_slist_node_t **head, sl_cpc_buffer_handle_t *buffer_handle);

/***************************************************************************//**
 * Push a buffer handle to a list.
 ******************************************************************************/
void sli_cpc_push_back_driver_buffer_handle(sl_slist_node_t **head, sl_cpc_buffer_handle_t *buf_handle);

/***************************************************************************//**
 * Push a list item containing an allocated buffer handle for the driver
 ******************************************************************************/
void sli_cpc_push_driver_buffer_handle(sl_slist_node_t **head, sl_cpc_buffer_handle_t *buf_handle);

/***************************************************************************//**
 * Get a buffer to store a security tag.
 *
 * @param[out] tag_buffer  Address of the variable that will receive the argument
 *                         tag_buffer pointer.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_get_security_tag_buffer(void **tag_buffer);

/***************************************************************************//**
 * Free a security tag buffer.
 *
 * @param[in] tag_buffer  Pointer to the buffer to free.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_free_security_tag_buffer(void *tag_buffer);

/***************************************************************************//**
 * Initialize CPC System Endpoint.
 *
 * @brief
 *   This function initializes the system endpoint module.
 ******************************************************************************/
sl_status_t sli_cpc_system_init(void);

/***************************************************************************//**
 * Start CPC System Endpoint.
 *
 * @brief
 *   This function starts the system endpoint module by opening the system
 *   endpoint. This function must be called after CPC init.
 ******************************************************************************/
sl_status_t sli_cpc_system_start(void);

/***************************************************************************//**
 * Process the system endpoint.
 *
 * @brief
 *   This function reads incoming commands on the system endpoint and processes
 *   them accordingly.
 ******************************************************************************/
void sli_cpc_system_process(void);

/***************************************************************************//**
 * Initialize the dispatcher handle.
 *
 * @param[in] handle  Dispatch queue node.
 ******************************************************************************/
void sli_cpc_dispatcher_init_handle(sl_cpc_dispatcher_handle_t *handle);

/***************************************************************************//**
 * Push function in dispatch queue along with the data to be passed when
 * dispatched.
 *
 * @param[in] handle  Dispatch queue node.
 * @param[in] fnct    Function to be dispatched.
 * @param[in] data    Data to pass to the function.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_dispatcher_push(sl_cpc_dispatcher_handle_t *handle,
                                    sl_cpc_dispatcher_fnct_t fnct,
                                    void *data);

/***************************************************************************//**
 * Remove function from dispatch queue along with the data to be passed when
 * dispatched.
 *
 * @param[in] handle  Dispatch queue node.
 ******************************************************************************/
void sli_cpc_dispatcher_cancel(sl_cpc_dispatcher_handle_t *handle);

/***************************************************************************//**
 * Process the dispatch queue.
 *
 * @brief
 *   This function empty the dispatch queue by calling all the functions
 *   registered.
 ******************************************************************************/
void sli_cpc_dispatcher_process(void);

/***************************************************************************//**
 * Notify the core that remote is connecting to this endpoint if ready.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_remote_connecting(uint8_t endpoint_id, sl_cpc_endpoint_state_t *reply_state);

/***************************************************************************//**
 * Notify the user that an endpoint was opened by the host/primary.
 ******************************************************************************/
void sli_cpc_remote_connected(uint8_t endpoint_id, sl_status_t status);

/***************************************************************************//**
 * Notify the core that the remote has requested a connection shutdown.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_remote_shutdown(uint8_t endpoint_id, sl_cpc_endpoint_state_t *reply_state);

/***************************************************************************//**
 * Completed the endpoint disconnection handshake.
 *
 * @note Endpoint must be locked by caller.
 ******************************************************************************/
void sli_cpc_endpoint_disconnected(uint8_t endpoint_id);

/***************************************************************************//**
 * Notify the user that an endpoint on the host has closed.
 ******************************************************************************/
void sli_cpc_remote_terminated(uint8_t endpoint_id, sl_cpc_endpoint_state_t *reply_state);

/***************************************************************************//**
 * Endpoint was opened, notify the host.
 ******************************************************************************/
sl_status_t sli_cpc_send_opening_notification(uint8_t endpoint_id);

/***************************************************************************//**
 * Endpoint connection was terminated, notify the host.
 ******************************************************************************/
sl_status_t sli_cpc_send_terminate_notification(uint8_t endpoint_id);

/***************************************************************************//**
 * Endpoint connection shutdown, notify the host.
 ******************************************************************************/
sl_status_t sli_cpc_send_shutdown_request(uint8_t endpoint_id);

/***************************************************************************//**
 * Called on re-transmition of frame.
 ******************************************************************************/
void sli_cpc_on_frame_retransmit(sl_cpc_buffer_handle_t* frame);

/***************************************************************************//**
 * Called on expiration of retransmit timer
 ******************************************************************************/
void sli_cpc_on_retransmit_timer_expiration(sl_cpc_buffer_handle_t *frame);

#if defined(SL_CATALOG_CPC_PRIMARY_PRESENT)
/***************************************************************************//**
 * Notify the core that the remote sent an unsolicited opening notification.
 ******************************************************************************/
void sli_cpc_remote_open_unsolicited(uint8_t id);

/***************************************************************************//**
 * Notify the core that the remote sent an unsolicited shutdown request.
 ******************************************************************************/
void sli_cpc_remote_shutdown_unsolicited(uint8_t id);

/***************************************************************************//**
 * Called when the secondary has reset.
 ******************************************************************************/
void sli_cpc_reset(void);

/***************************************************************************/ /**
 * Checks if CPC has been initialized
 *
 * @retval  SL_STATUS_OK              If sl_cpc_init was called
 * @retval  SL_STATUS_NOT_INITIALIZED If sl_cpc_init has not yet been called
 ******************************************************************************/
sl_status_t sli_cpc_is_initialized(void);
#endif

/***************************************************************************//**
 * Set the maximum payload length that the remote can receive
 ******************************************************************************/
void sli_cpc_set_remote_tx_max_payload_length(uint16_t remote_tx_max_payload_length);
// -----------------------------------------------------------------------------
// Driver to core notifications

/***************************************************************************//**
 * Notifies core of rx completion.
 ******************************************************************************/
void sli_cpc_notify_rx_data_from_drv(void);

/***************************************************************************//**
 * Notifies core of tx completion by the driver.
 *
 * @param buffer_handle Pointer to the buffer handle that was transmitted.
 ******************************************************************************/
void sli_cpc_notify_tx_data_by_drv(sl_cpc_buffer_handle_t *buffer_handle);

#if defined(SL_CATALOG_KERNEL_PRESENT)
/***************************************************************************//**
 * Notifies core of a freed transmit item
 ******************************************************************************/
void sli_cpc_notify_tx_item_freed(void);

/***************************************************************************//**
 * Notifies core of a freed buffer handle
 ******************************************************************************/
void sli_cpc_notify_buffer_handle_freed(void);
#endif

/** @} (end addtogroup cpc) */

#ifdef __cplusplus
}
#endif

#endif // SLI_CPC_H
