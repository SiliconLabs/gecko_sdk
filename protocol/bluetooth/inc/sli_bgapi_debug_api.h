/***************************************************************************//**
* @brief SLI_BGAPI_DEBUG_API command declarations
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


#ifndef SLI_BGAPI_DEBUG_API_H
#define SLI_BGAPI_DEBUG_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sl_status.h"
#include "sl_bgapi.h"


/**
 * @addtogroup sl_bgapi_debug_trace BGAPI tracing
 * @{
 *
 * @brief BGAPI tracing
 *
 * The events in this class are used by the BGAPI trace tool to record extra
 * metadata in the BGAPI traces. These events are never delivered to the
 * application.
 */

/* Command and Response IDs */

/**
 * @brief Specifies the full type of a BGAPI message.
 */
typedef enum
{
  sl_bgapi_debug_trace_message_type_command  = 0x0, /**< (0x0) The message is a
                                                         BGAPI command */
  sl_bgapi_debug_trace_message_type_response = 0x1, /**< (0x1) The message is a
                                                         BGAPI response */
  sl_bgapi_debug_trace_message_type_event    = 0x2  /**< (0x2) The message is a
                                                         BGAPI event */
} sl_bgapi_debug_trace_message_type_t;

/**
 * @addtogroup sl_bgapi_debug_evt_trace_message_metadata sl_bgapi_debug_evt_trace_message_metadata
 * @{
 * @brief This event is emitted by the BGAPI Trace component to the RTT trace
 * whenever a BGAPI message is output to the trace
 *
 * The message metadata event specifies the full type and the timestamp of the
 * BGAPI message that follows the metadata event.
 */

/** @brief Identifier of the message_metadata event */
#define sl_bgapi_debug_evt_trace_message_metadata_id                          0x000000b0

/***************************************************************************//**
 * @brief Data structure of the message_metadata event
 ******************************************************************************/
PACKSTRUCT( struct sl_bgapi_debug_evt_trace_message_metadata_s
{
  uint8_t  type;         /**< Enum @ref sl_bgapi_debug_trace_message_type_t. The
                              type of the message that follows. Values:
                                - <b>sl_bgapi_debug_trace_message_type_command
                                  (0x0):</b> The message is a BGAPI command
                                - <b>sl_bgapi_debug_trace_message_type_response
                                  (0x1):</b> The message is a BGAPI response
                                - <b>sl_bgapi_debug_trace_message_type_event
                                  (0x2):</b> The message is a BGAPI event */
  uint64_t timestamp_us; /**< Timestamp of the message that follows. The value
                              is a monotonically increasing number of
                              microseconds that have elapsed after the device
                              booted up. */
});

typedef struct sl_bgapi_debug_evt_trace_message_metadata_s sl_bgapi_debug_evt_trace_message_metadata_t;

/** @} */ // end addtogroup sl_bgapi_debug_evt_trace_message_metadata

/** @} */ // end addtogroup sl_bgapi_debug_trace


/***************************************************************************//**
 * @addtogroup sl_bgapi_debug_common_types BGAPI_DEBUG Common Types
 * @{
 *  @brief BGAPI_DEBUG common types
 */

/**
 * @brief Data structure of BGAPI_DEBUG API messages
 */
PACKSTRUCT( struct sl_bgapi_debug_msg {
  /** API protocol header consisting of event identifier and data length */
  uint32_t   header;

  /** Union of API event types */
  union {
    uint8_t handle;
    sl_bgapi_debug_evt_trace_message_metadata_t                  evt_trace_message_metadata; /**< Data field for trace message_metadata event*/
    uint8_t payload[SL_BGAPI_MAX_PAYLOAD_SIZE];
  } data;
});

/**
 * @brief Type definition for the data structure of BGAPI_DEBUG API messages
 */
typedef struct sl_bgapi_debug_msg sl_bgapi_debug_msg_t;

/** @} */ // end addtogroup sl_bgapi_debug_common_types
/******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif