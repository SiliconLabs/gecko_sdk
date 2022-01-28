/***************************************************************************/ /**
 * @file
 * @brief CPC
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

#ifndef SL_CPC_H
#define SL_CPC_H

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#include "sl_enum.h"
#include "sl_status.h"
#include "sl_slist.h"
#include "sl_cpc_config.h"
#include "sl_cpc_security.h"
#include <stddef.h>
#include <stdarg.h>

#if defined(SL_CATALOG_KERNEL_PRESENT)
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#endif

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
#include "sl_power_manager.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/***************************************************************************/ /**
 * @addtogroup cpc CPC
 * @brief CPC
 * @details
 * ## Overview
 *
 *   TODO
 *
 * ## Initialization
 *
 *   TODO
 *
 * @{
 ******************************************************************************/

// -----------------------------------------------------------------------------
// Data Types

/// @brief Enumeration representing user endpoint.
SL_ENUM(sl_cpc_user_endpoint_id_t){
  SL_CPC_ENDPOINT_USER_ID_0 = 90, ///< User endpoint ID 0
  SL_CPC_ENDPOINT_USER_ID_1 = 91, ///< User endpoint ID 1
  SL_CPC_ENDPOINT_USER_ID_2 = 92, ///< User endpoint ID 2
  SL_CPC_ENDPOINT_USER_ID_3 = 93, ///< User endpoint ID 3
  SL_CPC_ENDPOINT_USER_ID_4 = 94, ///< User endpoint ID 4
  SL_CPC_ENDPOINT_USER_ID_5 = 95, ///< User endpoint ID 5
  SL_CPC_ENDPOINT_USER_ID_6 = 96, ///< User endpoint ID 6
  SL_CPC_ENDPOINT_USER_ID_7 = 97, ///< User endpoint ID 7
  SL_CPC_ENDPOINT_USER_ID_8 = 98, ///< User endpoint ID 8
  SL_CPC_ENDPOINT_USER_ID_9 = 99, ///< User endpoint ID 9
};

/// @brief Enumeration representing the possible endpoint state.
SL_ENUM(sl_cpc_endpoint_state_t){
  SL_CPC_STATE_OPEN = 0,                      ///< State open
  SL_CPC_STATE_CLOSED,                        ///< State close
  SL_CPC_STATE_CLOSING,                       ///< State closing
  SL_CPC_STATE_ERROR_DESTINATION_UNREACHABLE, ///< Error state, destination unreachable
  SL_CPC_STATE_ERROR_SECURITY_INCIDENT,       ///< Error state, security incident
  SL_CPC_STATE_ERROR_FAULT,                   ///< Error state, fault
  SL_CPC_STATE_FREED,                         ///< State freed
};

/// @brief Enumeration representing the possible configurable options for an endpoint.
SL_ENUM(sl_cpc_endpoint_option_t){
  SL_CPC_ENDPOINT_ON_IFRAME_RECEIVE = 0,     ///< Option: iframe receive
  SL_CPC_ENDPOINT_ON_IFRAME_RECEIVE_ARG,     ///< Option: iframe receive argument
  SL_CPC_ENDPOINT_ON_UFRAME_RECEIVE,         ///< Option: uframe receive
  SL_CPC_ENDPOINT_ON_UFRAME_RECEIVE_ARG,     ///< Option: uframe receive argument
  SL_CPC_ENDPOINT_ON_IFRAME_WRITE_COMPLETED, ///< Option: iframe write completed
  SL_CPC_ENDPOINT_ON_UFRAME_WRITE_COMPLETED, ///< Option: uframe write completed
  SL_CPC_ENDPOINT_ON_POLL,                   ///< Option: on poll
  SL_CPC_ENDPOINT_ON_POLL_ARG,               ///< Option: on poll argument
  SL_CPC_ENDPOINT_ON_FINAL,                  ///< Option: on final
  SL_CPC_ENDPOINT_ON_FINAL_ARG,              ///< Option: on final argument
  SL_CPC_ENDPOINT_ON_ERROR,                  ///< Option: on error
  SL_CPC_ENDPOINT_ON_ERROR_ARG,              ///< Option: on error argument
};

// S-frame: Supervisory frames are used for flow and error control; Always required
// I-frame: Information frames are used to transfert data that is guarranteed to be received by the other side; Include retransmisttion and acknolegment
// U-frame: Un-numberred frames are used to transmit miscellaneous information without retransmission and acknowledgement services.
#define SL_CPC_OPEN_ENDPOINT_FLAG_NONE              0           // I-frame enabled and u-frame disabled; s-frame are always required and can be disabled.

typedef void (*sl_cpc_on_write_completed_t)(sl_cpc_user_endpoint_id_t endpoint_id,
                                            void *buffer,
                                            void *arg,
                                            sl_status_t status);

typedef void (*sl_cpc_on_data_reception_t)(uint8_t endpoint_id, void *arg);

typedef void (*sl_cpc_on_error_callback_t)(uint8_t endpoint_id, void *arg);

typedef void (*sl_cpc_on_poll_t)(uint8_t endpoint_id, void *arg,
                                 void *poll_data, uint32_t poll_data_length,    // Rx buffer is freed once this on_poll function return
                                 void **reply_data, uint32_t *reply_data_lenght,
                                 void **on_write_complete_arg);

typedef void (*sl_cpc_on_final_t)(uint8_t endpoint_id, void *arg, void *answer, uint32_t answer_lenght);

/// @brief Struct representing an CPC endpoint handle.
typedef struct {
  void *ep;
  uint8_t id;
  uint32_t ref_count;
} sl_cpc_endpoint_handle_t;

/// @brief Struct representing CPC Core debug stats.
typedef struct {
  uint32_t rxd_packet;
  uint32_t rxd_data_frame;
  uint32_t rxd_data_frame_queued;
  uint32_t rxd_data_frame_dropped;

  uint32_t rxd_supervisory_frame;
  uint32_t rxd_supervisory_frame_processed;
  uint32_t rxd_supervisory_frame_dropped;

  uint32_t rxd_unnumbered_frame;
  uint32_t rxd_unnumbered_frame_processed;
  uint32_t rxd_unnumbered_frame_dropped;

  uint32_t rxd_duplicate_data_frame;
  uint32_t rxd_ack;
  uint32_t rxd_reject_destination_unreachable;
  uint32_t rxd_reject_seq_mismatch;
  uint32_t rxd_reject_checksum_mismatch;
  uint32_t rxd_reject_security_issue;
  uint32_t rxd_reject_out_of_memory;
  uint32_t rxd_reject_fault;

  uint32_t txd_data_frame;
  uint32_t txd_ack;
  uint32_t txd_reject_destination_unreachable;
  uint32_t txd_reject_seq_mismatch;
  uint32_t txd_reject_checksum_mismatch;
  uint32_t txd_reject_security_issue;
  uint32_t txd_reject_out_of_memory;
  uint32_t txd_reject_fault;

  uint32_t retxd_data_frame;

  uint32_t frame_transmit_submitted;
  uint32_t frame_transmit_completed;
  uint32_t data_frame_transmit_completed;
  uint32_t supervisory_frame_transmit_completed;
} sl_cpc_endpoint_debug_counters_t;

/// @brief Struct representing CPC Core debug counters.
typedef struct {
  uint32_t endpoint_opened;
  uint32_t endpoint_closed;
  uint32_t rxd_frame;
  uint32_t rxd_valid_iframe;
  uint32_t rxd_valid_uframe;
  uint32_t rxd_valid_sframe;
  uint32_t rxd_data_frame_dropped;
  uint32_t txd_reject_destination_unreachable;
  uint32_t txd_reject_error_fault;
  uint32_t txd_completed;
  uint32_t retxd_data_frame;
  uint32_t driver_error;
  uint32_t driver_packet_dropped;
  uint32_t invalid_header_checksum;
  uint32_t invalid_payload_checksum;
} sl_cpc_core_debug_counters_t;

/// @brief Struct representing a memory pool handle.
typedef struct sl_cpc_mem_pool_handle_t {
  void *pool_handle;
  uint32_t used_block_cnt;
} sl_cpc_mem_pool_handle_t;

/// @brief Struct representing a memory pool debug.
typedef struct {
  sl_cpc_mem_pool_handle_t *buffer_handle;
  sl_cpc_mem_pool_handle_t *hdlc_header;
  sl_cpc_mem_pool_handle_t *hdlc_reject;
  sl_cpc_mem_pool_handle_t *rx_buffer;
  sl_cpc_mem_pool_handle_t *endpoint;
  sl_cpc_mem_pool_handle_t *rx_queue_item;
  sl_cpc_mem_pool_handle_t *tx_queue_item;
  sl_cpc_mem_pool_handle_t *endpoint_closed_arg_item;
  sl_cpc_mem_pool_handle_t *system_command;
} sl_cpc_debug_memory_t;

#if ((SL_CPC_DEBUG_CORE_EVENT_COUNTERS == 1) \
  || (SL_CPC_DEBUG_MEMORY_ALLOCATOR_COUNTERS == 1))
typedef struct {
#if (SL_CPC_DEBUG_MEMORY_ALLOCATOR_COUNTERS == 1)
  sl_cpc_debug_memory_t memory_pool;
#endif
#if (SL_CPC_DEBUG_CORE_EVENT_COUNTERS == 1)
  sl_cpc_core_debug_counters_t core_counters;
#endif
} sl_cpc_core_debug_t;
#endif

#define SL_CPC_USER_ENDPOINT_ID_START     ((uint8_t)SL_CPC_ENDPOINT_USER_ID_0)
#define SL_CPC_USER_ENDPOINT_ID_END       ((uint8_t)(SL_CPC_ENDPOINT_USER_ID_0 + SL_CPC_USER_ENDPOINT_MAX_COUNT - 1))

#define SL_CPC_FLAG_NO_BLOCK    0x01

#define SL_CPC_APP_DATA_MAX_LENGTH  2048u

#define SL_CPC_TRANSMIT_WINDOW_MIN_SIZE  1u
#define SL_CPC_TRANSMIT_WINDOW_MAX_SIZE  1u

#if ((SL_CPC_DEBUG_CORE_EVENT_COUNTERS == 1) \
  || (SL_CPC_DEBUG_MEMORY_ALLOCATOR_COUNTERS == 1))
extern sl_cpc_core_debug_t sl_cpc_core_debug;
#endif

// -----------------------------------------------------------------------------
// Prototypes

/***************************************************************************/ /**
 * Initialize CPC module.
 *
 * @return Status code
 ******************************************************************************/
sl_status_t sl_cpc_init(void);

/***************************************************************************/ /**
 *  The baremetal process action function.
 ******************************************************************************/
#if !defined(SL_CATALOG_KERNEL_PRESENT)
void sl_cpc_process_action(void);
#endif

/***************************************************************************/ /**
 * Open endpoint
 *
 * @param[in] endpoint_handle  Endpoint handle
 *
 * @param[in] id  Endpoint ID
 *
 * @param[in] flags   Endpoint type flags
 *
 * @param[in] tx_window_size  Transmit window size
 *
 * @return Status code
 ******************************************************************************/
sl_status_t sl_cpc_open_user_endpoint(sl_cpc_endpoint_handle_t *endpoint_handle,
                                      sl_cpc_user_endpoint_id_t id,
                                      uint8_t flags,
                                      uint8_t tx_window_size);

/***************************************************************************/ /**
 * Set endpoint option
 *
 * @param[in] endpoint_handle  Endpoint handle
 *
 * @param[in] option  Endpoint Option to set
 *
 * @param[in] value   Option value
 *
 * @return Status code
 *
 * @note Options are as follow:
 *
 * SL_CPC_ENDPOINT_ON_IFRAME_RECEIVE: Set an on iframe receive callback.
 *                                    value is a sl_cpc_on_data_reception_t type.
 *
 * SL_CPC_ENDPOINT_ON_IFRAME_RECEIVE_ARG: Set an on iframe receive argument.
 *
 * SL_CPC_ENDPOINT_ON_UFRAME_RECEIVE: Set an on uframe receive callback.
 *                                    value is a sl_cpc_on_data_reception_t type.
 *
 * SL_CPC_ENDPOINT_ON_UFRAME_RECEIVE_ARG: Set an on uframe receive argument.
 *
 * SL_CPC_ENDPOINT_ON_IFRAME_WRITE_COMPLETED: Set an on iframe write completed
 *                                            callback. value is a
 *                                            sl_cpc_on_write_completed_t type.
 *
 * SL_CPC_ENDPOINT_ON_UFRAME_WRITE_COMPLETED: Set an on uframe write completed
 *                                            callback. value is a
 *                                            sl_cpc_on_write_completed_t type.
 *
 * SL_CPC_ENDPOINT_ON_POLL: Set an on poll callback. value is a sl_cpc_on_poll_t
 *                          type.
 *
 * SL_CPC_ENDPOINT_ON_POLL_ARG: Set an on poll callback argument.
 *
 * SL_CPC_ENDPOINT_ON_FINAL: Set an on final callback. value is a
 *                           sl_cpc_on_final_t type.
 *
 * SL_CPC_ENDPOINT_ON_FINAL_ARG: Set an on final callback argument.
 *
 * SL_CPC_ENDPOINT_ON_ERROR: Set an on error callback. value is a
 *                           sl_cpc_on_error_callback_t type.
 *
 * SL_CPC_ENDPOINT_ON_ERROR_ARG: Set an on error callback argument.
 ******************************************************************************/
sl_status_t sl_cpc_set_endpoint_option(sl_cpc_endpoint_handle_t *endpoint_handle,
                                       sl_cpc_endpoint_option_t option,
                                       void *value);

/***************************************************************************/ /**
 * Close endpoint
 *
 * @param[in] endpoint_handle  Endpoint handle
 *
 * @return Status code
 ******************************************************************************/
sl_status_t sl_cpc_close_endpoint(sl_cpc_endpoint_handle_t *endpoint_handle);

/***************************************************************************/ /**
 * Abort read
 *
 * @param[in] endpoint_handle   Endpoint handle
 *
 * @return Status code
 *
 * @note This function can be called from an ISR.
 ******************************************************************************/
#if defined(SL_CATALOG_KERNEL_PRESENT)
sl_status_t sl_cpc_abort_read(sl_cpc_endpoint_handle_t *endpoint_handle);
#endif

/***************************************************************************/ /**
 * Read Data
 *
 * @param[in] endpoint_handle   Endpoint handle
 * @param[out] data             Address of the variable that will receive the data pointer.
 * @param[out] data_length      Length of the data contained in the buffer.
 * @param[in] timeout           Timeout in ticks for the read operation. (Requires RTOS)
 *                              Note: No effect if SL_CPC_FLAG_NO_BLOCK is provided as a flag
 * @param[in] flags             Optional flags. i.g. SL_CPC_FLAG_NO_BLOCK
 *                              Note: SL_CPC_FLAG_NO_BLOCK will cause the function to return
 *                                    SL_STATUS_EMPTY on baremetal applications
 *
 * @return Status code
 ******************************************************************************/
sl_status_t sl_cpc_read(sl_cpc_endpoint_handle_t *endpoint_handle,
                        void **data,
                        uint16_t *data_length,
                        uint32_t timeout,
                        uint8_t flags);

/***************************************************************************/ /**
 * Write Data
 *
 * @param[in] endpoint_handle   Endpoint handle
 * @param[in] data              Pointer to data buffer.
 * @param[in] data_length       Length of the data contained in the buffer.
 * @param[in] flags             Optional flags.
 * @param[in] on_write_completed_arg  Argument that will be passed to on_write_completed().
 *
 * @return Status code
 *
 * @note This function cannot be called from an ISR.
 ******************************************************************************/
sl_status_t sl_cpc_write(sl_cpc_endpoint_handle_t *endpoint_handle,
                         void* data,
                         uint16_t data_length,
                         uint8_t flag,
                         void *on_write_completed_arg);

/***************************************************************************/ /**
 * Get endpoint state
 *
 * @param[in] endpoint_handle   Endpoint handle
 *
 * @return Endpoint state
 ******************************************************************************/
sl_cpc_endpoint_state_t sl_cpc_get_endpoint_state(sl_cpc_endpoint_handle_t *endpoint_handle);

/***************************************************************************//**
 * Free buffer returned by sl_cpc_read().
 *
 * @param[in] data  Pointer to data buffer to free.
 *
 * @return Status code
 ******************************************************************************/
sl_status_t sl_cpc_free_rx_buffer(void *data);

/***************************************************************************/ /**
 * Determines if CPC is ok to enter sleep mode.
 *
 * @return true if no CPC actions to process. False otherwise.
 ******************************************************************************/
#if !defined(SL_CATALOG_KERNEL_PRESENT) && defined(SL_CATALOG_POWER_MANAGER_PRESENT)
bool sl_cpc_is_ok_to_sleep(void);
#endif

/***************************************************************************//**
 * Determines if CPC is ok to return to sleep mode on ISR exit.
 *
 * @return SL_POWER_MANAGER_IGNORE if no CPC actions to process.
 *         SL_POWER_MANAGER_WAKEUP if CPC actions have to be processed.
 ******************************************************************************/
#if !defined(SL_CATALOG_KERNEL_PRESENT) && defined(SL_CATALOG_POWER_MANAGER_PRESENT)
sl_power_manager_on_isr_exit_t sl_cpc_sleep_on_isr_exit(void);
#endif

/** @} (end addtogroup cpc) */

#ifdef __cplusplus
}
#endif

#endif // SL_CPC_H
