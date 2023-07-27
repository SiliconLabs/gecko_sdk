/***************************************************************************//**
 * @file
 * @brief L2CAP transfer interface
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
#include <string.h>
#include "em_core.h"
#include "sl_common.h"
#include "sl_slist.h"
#include "sl_bt_l2cap_transfer.h"
#include "sli_bt_l2cap_transfer_adaptation.h"
#include "sl_bt_l2cap_transfer_config.h"

// -----------------------------------------------------------------------------
// Definitions
#define INVALID_CONNECTION_HANDLE 0
#define INVALID_CID               0
#define DEFAULT_CREDIT_VALUE      1
#define L2CAP_SDU_SIZE_LENGTH     sizeof(uint16_t)

// Adaptation definitions
#define ADAPTATION_RELEASE() sli_bt_l2cap_transfer_adaptation_release()
#define ADAPTATION_PROCEED() sli_bt_l2cap_transfer_adaptation_proceed()
#define ADAPTATION_IF_ACQUIRED()  if (sli_bt_l2cap_transfer_adaptation_acquire())

// -----------------------------------------------------------------------------
// Local variables
// State list. They are used to store transfers in a linked list - based on
// their current state

// Store channel open request
static sl_slist_node_t *request_transfer_list;
// Store pending open request
static sl_slist_node_t *request_pending_transfer_list;
// Store all active data transfers
static sl_slist_node_t *active_list;

// Store request responses
static sl_slist_node_t *request_response_transfer_list;
// Store pending request responses
static sl_slist_node_t *request_response_buffer_transfer_list;
// Store transfer which are receiving data
static sl_slist_node_t *receive_active_transfer_list;

#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
// Default of transfer tampletes for prior channels
static const sl_bt_l2cap_transfer_transfer_t transfer_template_default = {
  .cid = INVALID_CID,
  .connection = INVALID_CONNECTION_HANDLE,
  .credit = DEFAULT_CREDIT_VALUE
};

// Transfer template for prior channels
static sl_bt_l2cap_transfer_transfer_t transfer_template[SL_BT_L2CAP_TRANSFER_CONFIG_PRIOR_CHANNEL_COUNT];

#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1

// -----------------------------------------------------------------------------
//  Forward declaration of private functions

/******************************************************************************
 * Open transfer channel on request.
 *****************************************************************************/
static sl_status_t open_channel(void);

/******************************************************************************
 * Check if the transfer instance is valid (all necessary parameters are set)
 *
 * @param[in] transfer Pointer to the transfer object
 *
 * @retval SL_STATUS_OK Success.
 * @retval SL_STATUS_INVALID_HANDLE Connection handle is invalid.
 * @retval SL_STATUS_NULL_POINTER One of the callback functions is not set for
 *                                the transfer object, or the transfer object is
 *                                not set
 * @retval SL_STATUS_INVALID_PARAMETER One of the following parameters is not
 *                                     set in the transfer object: max_pdu,
 *                                     max_sdu, data, data_length, mode
 *
 *****************************************************************************/
static sl_status_t check_transfer_init_conditions(sl_bt_l2cap_transfer_transfer_t *transfer);

/******************************************************************************
 * Set up a channel open request.
 *
 * @param[in] data Pointer to the le_channel_open_response event
 *
 * @return SL_STATUS_OK if successful. Error code otherwise
 *****************************************************************************/
static sl_status_t create_channel_open_response(sl_bt_evt_l2cap_le_channel_open_request_t *request_event);

/******************************************************************************
 * Moves pending transfers to active state / sender or receiver.
 *
 * @param[in] data Pointer to the le_channel_open_request event
 *
 *                       An L2CAP error code as the outcome of the connection
 *                       request.
 *
 *                       Result @ref sl_bt_l2cap_connection_result_successful
 *                       indicates the connection request was accepted and
 *                       the logical channel is established. Other error code
 *                       value indicates the connection request was refused
 *                       by the peer device and other parameters of this
 *                       event must be ignored.
 *
 *****************************************************************************/
static void register_open_response_from_server(sl_bt_evt_l2cap_le_channel_open_response_t *response_event);

/******************************************************************************
 * Select transfer by connection handle and channel ID
 *
 * @param[in] connection connection handle
 * @param[in] cid Channel ID
 * @param[in] head_node Pointer to the transfer list containing the transfer
 *
 * @return sl_bt_l2cap_transfer_transfer_t The selected transfer object
 *****************************************************************************/
static sl_bt_l2cap_transfer_transfer_t *select_transfer_by_cid(uint8_t         connection,
                                                               uint16_t        cid,
                                                               sl_slist_node_t *head_node);

/******************************************************************************
 * Remove transfer by connection handle and channel ID
 *
 * @param[in] connection connection handle
 * @param[in] cid Channel ID
 * @param[in] head_node Pointer to the transfer list reference
 *****************************************************************************/
static void remove_transfer(uint8_t connection,
                            uint16_t cid,
                            sl_slist_node_t **head_node);

/******************************************************************************
 * Select transfer by connection handle - it will stop at the result
 *
 * @param[in] connection connection handle
 * @param[in] head_node Pointer to the transfer list containing the transfer
 *
 * @return sl_bt_l2cap_transfer_transfer_t The selected transfer object
 *****************************************************************************/
static sl_bt_l2cap_transfer_transfer_t *select_transfer_by_connection(uint8_t         connection,
                                                                      sl_slist_node_t *head_node);

/******************************************************************************
 * Send data through L2CAP data channel - data is loaded from transfer object
 *
 * @param[in] transfer Transfer object containing all information for
 *            data transfer
 *
 *****************************************************************************/
static void send_data(sl_bt_l2cap_transfer_transfer_t *transfer);

/******************************************************************************
 * Process incoming data
 *
 * @param[in] data Incoming data - contaning connection handle, CID and the data
 *
 * @return SL_STATUS_OK if successful. Error code otherwise.
 *****************************************************************************/
static sl_status_t process_received_data(sl_bt_evt_l2cap_channel_data_t *data);

/******************************************************************************
 * Remove registered transfer from all state-lists
 *
 * @param[in] connection connection handle
 * @param[in] cid Channel ID
 *****************************************************************************/
static void remove_transfer_from_everywhere(uint16_t connection, uint16_t cid);

/******************************************************************************
 * Close selected transfer - by connection handle and channel ID and remove
 * from state-lists.
 *
 * @param[in] connection connection handle
 * @param[in] cid Channel ID
 * @param[in] reason  The disconnection reason
 *****************************************************************************/
static void close_transfer(uint16_t connection,
                           uint16_t cid,
                           sl_status_t error);

/******************************************************************************
 * Search transfer through all available state-lists.
 *
 * @param[in] connection connection handle
 * @param[in] cid Channel ID
 *
 * @return sl_bt_l2cap_transfer_transfer_t The searched transfer object
 *****************************************************************************/
static sl_bt_l2cap_transfer_transfer_t *search_for_transfer(uint16_t connection,
                                                            uint16_t cid);

#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1

/******************************************************************************
 * Get template prior channel for a connection handle
 *
 * @param[in] connection connection handle
 *
 * @return transfer or NULL if not found
 *****************************************************************************/
static sl_bt_l2cap_transfer_transfer_t *get_template(uint8_t connection);

/******************************************************************************
 * Set template prior channel to defaults
 *
 * @param[in] template template transfer for the prior channel
 *****************************************************************************/
static void set_template_defaults(sl_bt_l2cap_transfer_transfer_t *template);

#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
// -----------------------------------------------------------------------------
// Public functions

/******************************************************************************
 * Close all transfers for a connection
 *
 * @param[in] connection connection handle
 * @param[in] reason     reason of the close event
 *****************************************************************************/
static void close_all_by_connection(uint8_t     connection,
                                    sl_status_t reason);

/******************************************************************************
 * Search for transfer by connection
 *
 * @param[in] con connection handle
 *
 * @return transfer or NULL if not found
 *****************************************************************************/
sl_bt_l2cap_transfer_transfer_t *search_for_transfer_by_connection(uint8_t con);

/*******************************************************************************
 * Event handler
 ******************************************************************************/
void sli_bt_l2cap_transfer_on_bt_event(sl_bt_msg_t *evt)
{
  sl_bt_l2cap_transfer_transfer_t *transfer;

  switch (SL_BT_MSG_ID(evt->header)) {
#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
    case sl_bt_evt_system_boot_id:
      ADAPTATION_IF_ACQUIRED() {
        // Set defaults for all prior channel transfer template
        for (uint8_t i = 0; i < SL_BT_L2CAP_TRANSFER_CONFIG_PRIOR_CHANNEL_COUNT; i++) {
          set_template_defaults(&transfer_template[i]);
        }
        ADAPTATION_PROCEED();
        ADAPTATION_RELEASE();
      }
      break;
    case sl_bt_evt_connection_opened_id:
      ADAPTATION_IF_ACQUIRED() {
        // Get empty slot for the connection
        transfer = get_template(INVALID_CONNECTION_HANDLE);
        if (transfer != NULL) {
          // Set the connection for the prior channel template transfer
          transfer->connection = evt->data.evt_connection_opened.connection;
        }
        ADAPTATION_PROCEED();
        ADAPTATION_RELEASE();
      }
      break;
#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
    case sl_bt_evt_connection_closed_id:
      ADAPTATION_IF_ACQUIRED() {
        // Remove conections
        close_all_by_connection(evt->data.evt_connection_closed.connection,
                                evt->data.evt_connection_closed.reason);
        ADAPTATION_PROCEED();
        ADAPTATION_RELEASE();
      }
      break;
    case sl_bt_evt_l2cap_le_channel_open_request_id:
      // Responder
      ADAPTATION_IF_ACQUIRED() {
        create_channel_open_response(&evt->data.evt_l2cap_le_channel_open_request);
        // Move on with the transfer process
        ADAPTATION_PROCEED();
        ADAPTATION_RELEASE();
      }
      break;

    case sl_bt_evt_l2cap_le_channel_open_response_id:
      // Initiator
      ADAPTATION_IF_ACQUIRED() {
        register_open_response_from_server(&evt->data.evt_l2cap_le_channel_open_response);
        // Move on with the process
        ADAPTATION_PROCEED();
        ADAPTATION_RELEASE();
      }
      break;

    case sl_bt_evt_l2cap_channel_data_id:
      ADAPTATION_IF_ACQUIRED() {
        process_received_data(&evt->data.evt_l2cap_channel_data);
        // Move on with the process
        ADAPTATION_PROCEED();
        ADAPTATION_RELEASE();
      }
      break;

    case sl_bt_evt_l2cap_channel_credit_id:
      ADAPTATION_IF_ACQUIRED() {
        transfer = select_transfer_by_cid(evt->data.evt_l2cap_channel_credit.connection,
                                          evt->data.evt_l2cap_channel_credit.cid,
                                          active_list);
        if (transfer != NULL) {
          transfer->credit += evt->data.evt_l2cap_channel_credit.credit;
          // Move on with the process
          ADAPTATION_PROCEED();
        }
        ADAPTATION_RELEASE();
      }
      break;

    case sl_bt_evt_l2cap_command_rejected_id:
      // Remote rejected the command.
      break;

    case sl_bt_evt_l2cap_channel_closed_id:
      ADAPTATION_IF_ACQUIRED() {
        close_transfer(evt->data.evt_l2cap_channel_closed.connection,
                       evt->data.evt_l2cap_channel_closed.cid,
                       evt->data.evt_l2cap_channel_closed.reason);
#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
        // Get and reset to defaults
        transfer = get_template(evt->data.evt_l2cap_channel_closed.connection);
        if (transfer != NULL && transfer->cid == evt->data.evt_l2cap_channel_closed.cid) {
          set_template_defaults(transfer);
        }
#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
        // Move on with the process after close
        ADAPTATION_PROCEED();
        ADAPTATION_RELEASE();
      }
      break;
    default:
      break;
  }
}

sl_status_t sl_bt_l2cap_transfer_start_data_transfer(sl_bt_l2cap_transfer_transfer_t *transfer,
                                                     bool                            opening_channel)
{
  sl_status_t sc = SL_STATUS_OK;

  ADAPTATION_IF_ACQUIRED() {
    sc = check_transfer_init_conditions(transfer);

    if (sc == SL_STATUS_OK) {
      // Set the current pointer to zero
      transfer->pointer = 0;
      transfer->sdu_pointer = 0;
      transfer->sdu_size = 0;
      transfer->cid = INVALID_CID;
#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      sl_bt_l2cap_transfer_transfer_t *template;
      template = get_template(transfer->connection);
      if (template != NULL && template->cid != INVALID_CID) {
        // Copy template
        transfer->cid = template->cid;
        transfer->spsm = template->spsm;
        transfer->max_sdu = template->max_sdu;
        transfer->max_pdu = template->max_pdu;
        if (transfer->mode == SL_BT_L2CAP_TRANSFER_MODE_TRANSMIT) {
          sl_slist_push(&active_list, &transfer->node);
        } else {
          sc = sl_bt_l2cap_channel_send_credit(transfer->connection,
                                               transfer->cid,
                                               transfer->credit);
          if (sc == SL_STATUS_OK) {
            sl_slist_push(&receive_active_transfer_list, &transfer->node);
          }
        }
      } else {
#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      if (opening_channel == true) {
        sl_slist_push_back(&request_transfer_list, &transfer->node);
      } else {
        sl_slist_push_back(&request_response_transfer_list, &transfer->node);
      }
#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
    }
#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      ADAPTATION_PROCEED();
    }
    ADAPTATION_RELEASE();
  } else {
    sc = SL_STATUS_BUSY;
  }

  return sc;
}

// Looping
void sli_bt_l2cap_transfer_process_action(void)
{
  sl_slist_node_t *iterator;

  // Initiator
  if (request_transfer_list != NULL) {
    ADAPTATION_IF_ACQUIRED() {
      open_channel();
      ADAPTATION_PROCEED();
      ADAPTATION_RELEASE();
    }
  }

  // Neutral
  if (active_list != NULL) {
    ADAPTATION_IF_ACQUIRED() {
      SL_SLIST_FOR_EACH(active_list, iterator) {
        if (((sl_bt_l2cap_transfer_transfer_t *)iterator)->mode == SL_BT_L2CAP_TRANSFER_MODE_TRANSMIT) {
          send_data((sl_bt_l2cap_transfer_transfer_t *)iterator);
        }
      }
      ADAPTATION_PROCEED();
      ADAPTATION_RELEASE();
    }
  }
}

void sli_bt_l2cap_transfer_init(void)
{
  // No adaptation required as this method is called before scheduling start.
  sli_bt_l2cap_transfer_adaptation_init();

  sl_slist_init(&request_transfer_list);
  sl_slist_init(&request_pending_transfer_list);
  sl_slist_init(&active_list);

  sl_slist_init(&request_response_transfer_list);
  sl_slist_init(&request_response_buffer_transfer_list);
  sl_slist_init(&receive_active_transfer_list);
}

sl_status_t sl_bt_l2cap_transfer_increase_credit(sl_bt_l2cap_transfer_transfer_t *transfer,
                                                 uint16_t                        credit)
{
  sl_status_t sc = SL_STATUS_NULL_POINTER;

  if (transfer != NULL) {
    ADAPTATION_IF_ACQUIRED() {
      sc = sl_bt_l2cap_channel_send_credit(transfer->connection,
                                           transfer->cid, credit);
      ADAPTATION_RELEASE();
    } else {
      sc = SL_STATUS_BUSY;
    }
  }

  return sc;
}

sl_status_t sl_bt_l2cap_transfer_abort_transfer(sl_bt_l2cap_transfer_transfer_t *transfer)
{
  sl_status_t sc = SL_STATUS_NULL_POINTER;

  if (transfer != NULL) {
    ADAPTATION_IF_ACQUIRED() {
      transfer->channel_error = SL_STATUS_ABORT;
#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      sl_bt_l2cap_transfer_transfer_t *template;
      template = get_template(transfer->connection);
      if (template != NULL && transfer->cid == template->cid) {
        close_transfer(transfer->connection, transfer->cid, transfer->channel_error);
      } else {
        (void)sl_bt_l2cap_close_channel(transfer->connection, transfer->cid);
      }
#else // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      (void)sl_bt_l2cap_close_channel(transfer->connection, transfer->cid);
#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      sc = SL_STATUS_OK;
      ADAPTATION_RELEASE();
    } else {
      sc = SL_STATUS_BUSY;
    }
  }

  return sc;
}

sl_status_t sl_bt_l2cap_transfer_check_progress(sl_bt_l2cap_transfer_transfer_t *transfer)
{
  sl_status_t sc = SL_STATUS_OK;
  if (transfer == NULL) {
    sc = SL_STATUS_NULL_POINTER;
  } else if (transfer->mode == SL_BT_L2CAP_TRANSFER_MODE_TRANSMIT
             || transfer->mode == SL_BT_L2CAP_TRANSFER_MODE_RECEIVE) {
    ADAPTATION_IF_ACQUIRED() {
      // Search for the transfer
      sl_bt_l2cap_transfer_transfer_t *transfer_found = search_for_transfer(transfer->connection,
                                                                            transfer->cid);
      // Status is in progress only if identical
      if (transfer_found == transfer) {
        sc = SL_STATUS_IN_PROGRESS;
      }
      ADAPTATION_RELEASE();
    } else {
      sc = SL_STATUS_BUSY;
    }
  }
  return sc;
}

sl_status_t sl_bt_l2cap_transfer_open_prior_channel(sl_bt_l2cap_transfer_transfer_t *transfer)
{
#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
  sl_status_t sc = SL_STATUS_NO_MORE_RESOURCE;

  if (transfer == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  if (transfer->connection == SL_BT_INVALID_CONNECTION_HANDLE) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sl_bt_l2cap_transfer_transfer_t *template;
  template = get_template(transfer->connection);
  if (template != NULL && template->cid == INVALID_CID) {
    ADAPTATION_IF_ACQUIRED() {
      memcpy(template,
             transfer,
             sizeof(sl_bt_l2cap_transfer_transfer_t));
      // Open channel for the template
      sl_slist_push_back(&request_transfer_list, &template->node);
      sc = SL_STATUS_OK;
      ADAPTATION_RELEASE();
    } else {
      sc = SL_STATUS_BUSY;
    }
  }
  return sc;
#else // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
  (void)transfer;
  return SL_STATUS_NOT_SUPPORTED;
#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
}

#ifdef SL_CATALOG_POWER_MANAGER_PRESENT

sl_power_manager_on_isr_exit_t sli_bt_l2cap_transfer_sleep_on_isr_exit()
{
  sl_power_manager_on_isr_exit_t ret = SL_POWER_MANAGER_IGNORE;

  // Sleep should be avoided if there is an active transfer
  if ((request_transfer_list != NULL)
      || (request_pending_transfer_list != NULL)
      || (active_list != NULL)) {
    ret = SL_POWER_MANAGER_WAKEUP;
  }

  return ret;
}

bool sli_bt_l2cap_transfer_is_ok_to_sleep()
{
  bool ret = false;

  // Sleep should be avoided if there is an active transfer
  if ((request_transfer_list == NULL)
      && (request_pending_transfer_list == NULL)
      && (active_list == NULL)) {
    ret = true;
  }
  return ret;
}

#endif // SL_CATALOG_POWER_MANAGER_PRESENT

// -----------------------------------------------------------------------------
// Private functions

static sl_status_t create_channel_open_response(sl_bt_evt_l2cap_le_channel_open_request_t *request_event)
{
  sl_status_t sc = SL_STATUS_FAIL;
  sl_bt_l2cap_transfer_transfer_t *transfer = NULL;

  transfer = select_transfer_by_connection(request_event->connection,
                                           request_response_transfer_list);

#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
  sl_bt_l2cap_transfer_transfer_t *template = NULL;
  if (transfer == NULL) {
    // Get the template
    template = get_template(request_event->connection);
    if (template != NULL && template->cid == INVALID_CID) {
      transfer = template;
      transfer->max_sdu = request_event->max_sdu;
      transfer->max_pdu = request_event->max_pdu;
    }
  }
#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1

  if (transfer != NULL) {
    transfer->connection = request_event->connection;
    transfer->cid = request_event->cid;
    transfer->spsm = request_event->spsm;

    if (transfer->max_sdu > request_event->max_sdu) {
      transfer->max_sdu = request_event->max_sdu;
    }

    if (transfer->max_pdu > request_event->max_pdu) {
      transfer->max_pdu = request_event->max_pdu;
    }

    if (transfer->mode == SL_BT_L2CAP_TRANSFER_MODE_TRANSMIT) {
      // The RECEIVER opened the l2cap channel, its value should be used
      transfer->credit = (request_event->credit != 0) ? request_event->credit : DEFAULT_CREDIT_VALUE;
    } else if (transfer->mode == SL_BT_L2CAP_TRANSFER_MODE_RECEIVE) {
      // The TRANSMITTER opened the l2cap channel, credit is stored in transfer obj
      // or is overwritten to default value, if its 0
      if (transfer->credit == 0) {
        transfer->credit = DEFAULT_CREDIT_VALUE;
      }
    }

    // When parameters are set, send open response
    sc = sl_bt_l2cap_send_le_channel_open_response(transfer->connection,
                                                   transfer->cid,
                                                   transfer->max_sdu,
                                                   transfer->max_pdu,
                                                   transfer->credit,
                                                   sl_bt_l2cap_connection_result_successful);

    if (sc == SL_STATUS_OK) {
#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      if (transfer != template) {
#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      if (transfer->mode == SL_BT_L2CAP_TRANSFER_MODE_TRANSMIT) {
        sl_slist_push(&active_list, &transfer->node);
      } else {
        sl_slist_push(&receive_active_transfer_list, &transfer->node);
      }
#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
    }
#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      if (transfer->callbacks && transfer->callbacks->on_open) {
        transfer->callbacks->on_open(transfer);
      }
    } else {
      transfer->channel_error = sc;
      (void)sl_bt_l2cap_close_channel(transfer->connection, transfer->cid);
    }
  } else {
    sc = sl_bt_l2cap_send_le_channel_open_response(request_event->connection,
                                                   request_event->cid,
                                                   request_event->max_sdu,
                                                   request_event->max_pdu,
                                                   request_event->credit,
                                                   sl_bt_l2cap_connection_result_no_resources_available);
  }

  return sc;
}

static void register_open_response_from_server(sl_bt_evt_l2cap_le_channel_open_response_t *response_event)
{
  sl_bt_l2cap_transfer_transfer_t *transfer = NULL;
  uint16_t error_code = response_event->errorcode;

  // Check if the response was coming from the right connection
  transfer = select_transfer_by_cid(response_event->connection,
                                    response_event->cid,
                                    request_pending_transfer_list);

  if (transfer != NULL) {
    transfer->max_pdu = response_event->max_pdu;
    transfer->max_sdu = response_event->max_sdu;
    transfer->credit = response_event->credit;

    if (error_code == sl_bt_l2cap_connection_result_successful) {
#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      sl_bt_l2cap_transfer_transfer_t *template = NULL;
      // Get prior channel transfer template if present
      template = get_template(transfer->connection);
      // Check if this channel is the prior channel
      if (template != NULL && transfer == template) {
        transfer->callbacks->on_open(transfer);
      } else {
#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      if (transfer->mode == SL_BT_L2CAP_TRANSFER_MODE_TRANSMIT) {
        sl_slist_push(&active_list, &transfer->node);
      } else {
        sl_slist_push(&receive_active_transfer_list, &transfer->node);
      }
      if (transfer->callbacks->on_open) {
        transfer->callbacks->on_open(transfer);
      }
#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
    }
#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
    } else {
      transfer->channel_error = error_code;
      close_transfer(transfer->connection, transfer->cid, error_code);
#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      sl_bt_l2cap_transfer_transfer_t *template = NULL;
      // Reset to defaults if template present
      template = get_template(transfer->connection);
      if (template != NULL) {
        set_template_defaults(template);
      }
#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
    }
    // Remove transfer from the pending list
    sl_slist_remove(&request_pending_transfer_list, &transfer->node);
  }
}

static sl_status_t check_transfer_init_conditions(sl_bt_l2cap_transfer_transfer_t *transfer)
{
  sl_status_t sc = SL_STATUS_OK;

  if (transfer == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  if (transfer->mode == SL_BT_L2CAP_TRANSFER_MODE_INACTIVE) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if ((transfer->connection == INVALID_CONNECTION_HANDLE)
      && (transfer->mode == SL_BT_L2CAP_TRANSFER_MODE_RECEIVE)) {
    sc = SL_STATUS_INVALID_HANDLE;
  }
  // Receiver side
  if (transfer->mode == SL_BT_L2CAP_TRANSFER_MODE_RECEIVE) {
    if (transfer->callbacks->on_finish == NULL
        || transfer->callbacks->on_receive == NULL) {
      sc = SL_STATUS_NULL_POINTER;
    }
    // Transmitter side
  } else {
    if (transfer->data_length == 0
        || ((uint64_t)transfer->data_offset + (uint64_t)transfer->data_length)
        > UINT32_MAX ) {
      sc = SL_STATUS_INVALID_PARAMETER;
    } else if (transfer->callbacks->on_finish == NULL
               || transfer->callbacks->on_transmit == NULL) {
      sc = SL_STATUS_NULL_POINTER;
    }
  }
  return sc;
}

static sl_status_t process_received_data(sl_bt_evt_l2cap_channel_data_t *data)
{
  sl_status_t sc = SL_STATUS_FAIL;
  sl_bt_l2cap_transfer_transfer_t *transfer;
  uint16_t credit = 0;
  uint16_t sdu_size;
  uint32_t data_len = data->data.len;
  uint16_t data_offset = 0;

  transfer = select_transfer_by_cid(data->connection,
                                    data->cid,
                                    receive_active_transfer_list);

  if (transfer != NULL) {
    // Register credit decrease after data was received
    if (transfer->credit > 0) {
      transfer->credit--;
    }

    // Save SDU size from the first K-Frame
    if (transfer->sdu_pointer == 0) {
      sdu_size = *((uint16_t *)data->data.data);
      transfer->sdu_size = sdu_size;
      data_len -= L2CAP_SDU_SIZE_LENGTH;
      data_offset = L2CAP_SDU_SIZE_LENGTH;
    }

    credit = transfer->callbacks->on_receive(transfer,
                                             transfer->data_offset + transfer->pointer,
                                             data_len,
                                             &data->data.data[data_offset]);

    // Check if the SDU is violated.
    if ((uint32_t)transfer->sdu_pointer + data_len > transfer->sdu_size) {
      transfer->channel_error = SL_STATUS_BT_DATA_CORRUPTED;
#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      sl_bt_l2cap_transfer_transfer_t *template;
      template = get_template(transfer->connection);
      if (template != NULL && template->cid == transfer->cid) {
        close_transfer(transfer->connection, transfer->cid, SL_STATUS_OK);
      } else {
        (void)sl_bt_l2cap_close_channel(transfer->connection, transfer->cid);
      }
#else // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      (void)sl_bt_l2cap_close_channel(transfer->connection, transfer->cid);
#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      return transfer->channel_error;
    }

    // If data is received, the offset will be shifted by the data size
    transfer->pointer += data_len;
    // SDU pointer should also be incremented
    transfer->sdu_pointer += data_len;

    // Check if it was the last packet in this SDU
    if (transfer->sdu_pointer == transfer->sdu_size) {
      // Ready for the next SDU
      transfer->sdu_pointer = 0;
    }

    if (transfer->pointer >= transfer->data_length) {
#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      sl_bt_l2cap_transfer_transfer_t *template;
      template = get_template(transfer->connection);
      if (template != NULL && template->cid == transfer->cid) {
        close_transfer(transfer->connection, transfer->cid, SL_STATUS_OK);
      } else {
        (void)sl_bt_l2cap_close_channel(transfer->connection, transfer->cid);
      }
#else // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      (void)sl_bt_l2cap_close_channel(transfer->connection, transfer->cid);
#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      transfer->mode = SL_BT_L2CAP_TRANSFER_MODE_INACTIVE;
    } else {
      // If credit increase was requested, execute it.
      if (credit > 0) {
        sc = sl_bt_l2cap_channel_send_credit(transfer->connection,
                                             transfer->cid,
                                             credit);
        if (sc != SL_STATUS_OK) {
          // An error has occured, finish transfer
          transfer->channel_error = sc;
          (void)sl_bt_l2cap_close_channel(transfer->connection, transfer->cid);
        }
      }
    }
  }

  return sc;
}

static sl_status_t open_channel(void)
{
  sl_status_t sc = SL_STATUS_FAIL;
  sl_bt_l2cap_transfer_transfer_t *transfer;

  if (request_pending_transfer_list == NULL) {
    transfer = (sl_bt_l2cap_transfer_transfer_t *) request_transfer_list;

    sc = sl_bt_l2cap_open_le_channel(transfer->connection,
                                     transfer->spsm,
                                     transfer->max_sdu,
                                     transfer->max_pdu,
                                     transfer->credit,
                                     &transfer->cid);
    // Try to open the channel only once
    sl_slist_remove(&request_transfer_list, &transfer->node);
    if (sc == SL_STATUS_OK) {
      sl_slist_push_back(&request_pending_transfer_list, &transfer->node);
    } else {
      close_transfer(transfer->connection, transfer->cid, sc);
    }
  }
  return sc;
}

static void send_data(sl_bt_l2cap_transfer_transfer_t *transfer)
{
  sl_bt_l2cap_connection_result_t sc = sl_bt_l2cap_connection_result_successful;

  uint8_t *data_ptr = NULL;
  uint32_t data_len = 0;
  uint16_t request_len = 0;

  if (transfer->credit == 0) {
    return;
  }

  // First frame in SDU
  if (transfer->sdu_pointer == 0) {
    // SDU calculation
    transfer->sdu_size = transfer->max_sdu;
    // If a single SDU can be used
    if (transfer->data_length - transfer->pointer < transfer->max_sdu) {
      transfer->sdu_size = transfer->data_length - transfer->pointer;
    }
    // PDU calculation
    request_len = transfer->max_pdu - L2CAP_SDU_SIZE_LENGTH;
    // If package size is smaller than max PDU, correct length
    if ( transfer->pointer + request_len > transfer->data_length) {
      request_len = transfer->data_length - transfer->pointer;
    }
  } else {
    // PDU calculation
    request_len = transfer->max_pdu;

    // SDU residue calculation
    if (transfer->sdu_pointer + request_len > transfer->sdu_size) {
      request_len = transfer->sdu_size - transfer->sdu_pointer;
    }
    // If package size is smaller than max PDU, correct length
    if (transfer->pointer + request_len > transfer->data_length) {
      request_len = transfer->data_length - transfer->pointer;
    }
  }

  // Get the data from the user
  transfer->callbacks->on_transmit(transfer,
                                   transfer->data_offset + transfer->pointer,
                                   request_len,
                                   &data_ptr,
                                   &data_len);

  if ((transfer->sdu_pointer != 0
       && data_len > 0
       && data_len <= transfer->max_pdu)
      || (transfer->sdu_pointer == 0
          && data_len > 0
          && data_len <= transfer->max_pdu - L2CAP_SDU_SIZE_LENGTH)) {
    if (transfer->sdu_pointer == 0) {
      // First frame in the SDU needs SDU size field
      uint8_t data_array[SL_BT_L2CAP_TRANSFER_MAX_PDU];
      // Insert SDU size
      *((uint16_t *)data_array) = transfer->sdu_size;
      // Copy data into the buffer array
      memcpy(&data_array[L2CAP_SDU_SIZE_LENGTH], data_ptr, data_len);
      // Send data through channel, then increase offset, decrease credit
      sc = (sl_bt_l2cap_connection_result_t)sl_bt_l2cap_channel_send_data(transfer->connection,
                                                                          transfer->cid,
                                                                          data_len + L2CAP_SDU_SIZE_LENGTH,
                                                                          data_array);
    } else {
      // Send data through channel, then increase offset, decrease credit
      sc = (sl_bt_l2cap_connection_result_t)sl_bt_l2cap_channel_send_data(transfer->connection,
                                                                          transfer->cid,
                                                                          data_len,
                                                                          data_ptr);
    }
    if (sc == SL_STATUS_NO_MORE_RESOURCE) {
      // Buffer is full, just wait
    } else if (sc != SL_STATUS_OK) {
      // Close channel case 1 - error
      transfer->channel_error = sc;
      (void)sl_bt_l2cap_close_channel(transfer->connection, transfer->cid);
      transfer->mode = SL_BT_L2CAP_TRANSFER_MODE_INACTIVE;
    } else {
      if (transfer->sdu_pointer == 0) {
        // Check if the SDU is violated.
        if ((uint32_t)transfer->sdu_pointer + data_len > transfer->sdu_size) {
          transfer->channel_error = SL_STATUS_BT_DATA_CORRUPTED;
          (void)sl_bt_l2cap_close_channel(transfer->connection, transfer->cid);
        }
      }

      transfer->pointer += data_len;
      transfer->sdu_pointer += data_len;
      transfer->credit--;

      if (transfer->sdu_pointer == transfer->sdu_size) {
        // Ready for the next SDU
        transfer->sdu_pointer = 0;
      }

      // Close channel case 2 - finished
      if (transfer->pointer >= transfer->data_length) {
        transfer->channel_error = sl_bt_l2cap_connection_result_successful;
        transfer->mode = SL_BT_L2CAP_TRANSFER_MODE_INACTIVE;
#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
        close_transfer(transfer->connection, transfer->cid, SL_STATUS_OK);
#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
      }
    }
  }
}

static sl_bt_l2cap_transfer_transfer_t *select_transfer_by_cid(uint8_t         connection,
                                                               uint16_t        cid,
                                                               sl_slist_node_t *head_node)
{
  sl_slist_node_t *iterator;

  SL_SLIST_FOR_EACH(head_node, iterator)
  {
    if ( ((sl_bt_l2cap_transfer_transfer_t *)(iterator))->cid == cid
         && ((sl_bt_l2cap_transfer_transfer_t *)(iterator))->connection == connection) {
      break;
    }
  }
  return (sl_bt_l2cap_transfer_transfer_t *)iterator;
}

static void remove_transfer(uint8_t connection,
                            uint16_t cid,
                            sl_slist_node_t **head_node)
{
  sl_slist_node_t *iterator;
  sl_slist_node_t *head_ptr = *head_node;

  CORE_DECLARE_IRQ_STATE;

  SL_SLIST_FOR_EACH(head_ptr, iterator)
  {
    if ( ((sl_bt_l2cap_transfer_transfer_t *)(iterator))->cid == cid
         && ((sl_bt_l2cap_transfer_transfer_t *)(iterator))->connection == connection) {
      CORE_ENTER_CRITICAL();
      sl_slist_remove(head_node, iterator);
      CORE_EXIT_CRITICAL();
    }
  }
}

static sl_bt_l2cap_transfer_transfer_t *select_transfer_by_connection(uint8_t         connection,
                                                                      sl_slist_node_t *head_node)
{
  sl_slist_node_t *iterator = NULL;

  SL_SLIST_FOR_EACH(head_node, iterator)
  {
    if (((sl_bt_l2cap_transfer_transfer_t *)(iterator))->connection == connection) {
      break;
    }
  }

  return (sl_bt_l2cap_transfer_transfer_t *) iterator;
}

static void close_transfer(uint16_t connection, uint16_t cid, sl_status_t error)
{
  sl_bt_l2cap_transfer_transfer_t *transfer;
  sl_status_t sc = error;

  bool disconnect_status = false;

  if ((sc == SL_STATUS_BT_L2CAP_REMOTE_DISCONNECTED)
      || (sc == SL_STATUS_BT_L2CAP_LOCAL_DISCONNECTED) ) {
    disconnect_status = true;
  }

  transfer = search_for_transfer(connection, cid);

  if (transfer != NULL) {
    transfer->channel_error = sc;

    // check if transfer is finished because data was transmitted
    if ((disconnect_status == true)
        && (transfer->pointer >= transfer->data_length)) {
      sc = SL_STATUS_OK;
    }

    if (transfer->callbacks && transfer->callbacks->on_finish) {
      transfer->callbacks->on_finish(transfer,
                                     sc);
    }
    remove_transfer_from_everywhere(connection, cid);
  }
}

static void close_all_by_connection(uint8_t     connection,
                                    sl_status_t reason)
{
  sl_bt_l2cap_transfer_transfer_t *transfer = NULL;
  // Get first transfer for the connection
  transfer = search_for_transfer_by_connection(connection);
  // Close if found and search for additional ones
  while (transfer != NULL) {
    close_transfer(transfer->connection,
                   transfer->cid,
                   reason);
    transfer = search_for_transfer_by_connection(connection);
  }
#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
  // Get template and reset to defaults
  transfer = get_template(connection);
  if (transfer != NULL) {
    if (transfer->cid != INVALID_CID) {
      close_transfer(transfer->connection,
                     transfer->cid,
                     reason);
    }
    set_template_defaults(transfer);
  }
#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1
}

static void remove_transfer_from_everywhere(uint16_t connection, uint16_t cid)
{
  remove_transfer(connection,
                  cid,
                  &request_transfer_list);
  remove_transfer(connection,
                  cid,
                  &request_pending_transfer_list);
  remove_transfer(connection,
                  cid,
                  &active_list);
  remove_transfer(connection,
                  cid,
                  &request_response_transfer_list);
  remove_transfer(connection,
                  cid,
                  &request_response_buffer_transfer_list);
  remove_transfer(connection,
                  cid,
                  &receive_active_transfer_list);
}

sl_bt_l2cap_transfer_transfer_t *search_for_transfer_by_connection(uint8_t con)
{
  sl_bt_l2cap_transfer_transfer_t *transfer;

  transfer = select_transfer_by_connection(con, request_transfer_list);
  if (transfer != NULL) {
    return transfer;
  }
  transfer = select_transfer_by_connection(con, request_pending_transfer_list);
  if (transfer != NULL) {
    return transfer;
  }
  transfer = select_transfer_by_connection(con, active_list);
  if (transfer != NULL) {
    return transfer;
  }
  transfer = select_transfer_by_connection(con, request_response_transfer_list);
  if (transfer != NULL) {
    return transfer;
  }
  transfer = select_transfer_by_connection(con, request_response_buffer_transfer_list);
  if (transfer != NULL) {
    return transfer;
  }
  transfer = select_transfer_by_connection(con, receive_active_transfer_list);
  return transfer;
}

static sl_bt_l2cap_transfer_transfer_t *search_for_transfer(uint16_t connection,
                                                            uint16_t cid)
{
  sl_bt_l2cap_transfer_transfer_t *transfer;

  transfer = select_transfer_by_cid(connection,
                                    cid,
                                    request_transfer_list);
  if (transfer != NULL) {
    return transfer;
  }

  transfer = select_transfer_by_cid(connection,
                                    cid,
                                    request_pending_transfer_list);
  if (transfer != NULL) {
    return transfer;
  }

  transfer = select_transfer_by_cid(connection,
                                    cid,
                                    active_list);
  if (transfer != NULL) {
    return transfer;
  }

  transfer = select_transfer_by_cid(connection,
                                    cid,
                                    request_response_transfer_list);
  if (transfer != NULL) {
    return transfer;
  }

  transfer = select_transfer_by_cid(connection,
                                    cid,
                                    request_response_buffer_transfer_list);
  if (transfer != NULL) {
    return transfer;
  }

  transfer = select_transfer_by_cid(connection,
                                    cid,
                                    receive_active_transfer_list);

  return transfer;
}

#if SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1

static sl_bt_l2cap_transfer_transfer_t *get_template(uint8_t connection)
{
  for (uint8_t i = 0; i < SL_BT_L2CAP_TRANSFER_CONFIG_PRIOR_CHANNEL_COUNT; i++) {
    if (transfer_template[i].connection == connection) {
      return &transfer_template[i];
    }
  }
  return NULL;
}

static void set_template_defaults(sl_bt_l2cap_transfer_transfer_t *template)
{
  if (template != NULL) {
    memcpy(template, &transfer_template_default, sizeof(transfer_template_default));
  }
}

#endif // SL_BT_L2CAP_TRANSFER_CONFIG_ACCEPT_PRIOR_CHANNELS == 1

// -----------------------------------------------------------------------------
// Weak implementation of adaptation functions

SL_WEAK void sli_bt_l2cap_transfer_adaptation_init(void)
{
  // No action needed for bare metal
}

SL_WEAK bool sli_bt_l2cap_transfer_adaptation_acquire(void)
{
  // No action needed for bare metal
  return true;
}

SL_WEAK void sli_bt_l2cap_transfer_adaptation_release(void)
{
  // No action needed for bare metal
}

SL_WEAK void sli_bt_l2cap_transfer_adaptation_proceed(void)
{
  // No action needed for bare metal
}
