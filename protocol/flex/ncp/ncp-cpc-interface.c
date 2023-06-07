/***************************************************************************//**
 * @brief CPC handlers and initialization for the Connect stack NCP secondary
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

#include "sli_cpc.h"
#include "sl_cpc.h"
#include <time.h>
#include "stack/include/ember.h"
#include "ncp-cpc-interface.h"
#include "csp-format.h"
#include "csp-command-utils.h"
#include "csp-api-enum-gen.h"

static sl_cpc_endpoint_handle_t connect_endpoint_handle;
static bool connected = false;
EmberEventControl sl_connect_ncp_endpoint_deconnection_event;

//------------------------------------------------------------------------------
// Forward declarations

bool connect_cpc_open_endpoint(void);

bool sli_connect_is_ncp_connected(void)
{
  return connected;
}

//------------------------------------------------------------------------------
// CPC Callbacks

static void on_write_completed(sl_cpc_user_endpoint_id_t endpoint_id, void *buffer, void *arg, sl_status_t status)
{
  (void) endpoint_id; // Could be used if the same callback is registered for multiple endpoints and we need to distinguish them.
  (void) arg;        // Per-call-to-write supplied argument. Could be used in scenarios where we need to perform a specific operation only
  // when we know the remote has received our frame.
  if (status != SL_STATUS_OK) {
    //Reset the NCP
    NVIC_SystemReset();
  }
  //CPC is done using the buffer, free it as it is not used anymore
  free(buffer);
}

void sli_connect_ncp_process_incoming_api_command(uint8_t *apiCommandData)
{
  // This API must be called from the stack task.
  assert(isCurrentTaskStackTask());
  uint16_t commandId = emberFetchHighLowInt16u(apiCommandData);

  handleIncomingApiCommand(commandId, apiCommandData);
}

static void cpc_read_command(uint8_t endpoint_id, void *arg)
{
  (void) endpoint_id;
  (void) arg;
  sl_status_t status;
  uint8_t *read_array;
  uint16_t size;

  status = sl_cpc_read(&connect_endpoint_handle,
                       (void **)&read_array,
                       &size,
                       0, // Timeout : relevent only when using a kernel with blocking
                       0); // flags : relevent only when using a kernel to specify a non-blocking operation (polling).

  if (status != SL_STATUS_OK) {
    //do something
  } else if (!connected) {
    connected = true;
    sl_cpc_free_rx_buffer(read_array);
  } else {
    sli_connect_ncp_process_incoming_api_command(read_array);
    sl_cpc_free_rx_buffer(read_array);
  }
}

static void cpc_error_cb(uint8_t endpoint_id, void *arg)
{
  (void)endpoint_id;
  (void)arg;
  uint8_t state = sl_cpc_get_endpoint_state(&connect_endpoint_handle);
  if (state == SL_CPC_STATE_ERROR_DESTINATION_UNREACHABLE) {
    sl_status_t status = sl_cpc_close_endpoint(&connect_endpoint_handle);
    assert(status == SL_STATUS_OK);
    connected = false;
    emberEventControlSetActive(sl_connect_ncp_endpoint_deconnection_event);
  }
}

void sli_connect_cpc_send_command(uint8_t *command, uint16_t length)
{
  //message queue is managed by CPC
  sl_status_t status = sl_cpc_write(&connect_endpoint_handle,
                                    command,
                                    length,
                                    0,        // no flags
                                    NULL);   // no callback argument
  if (status != SL_STATUS_OK) {
    //do something
  }
}

#if defined(SL_CATALOG_CPC_SECURITY_PRESENT)
uint64_t sl_cpc_security_on_unbind_request(bool is_link_encrypted)
{
  return SL_CPC_SECURITY_OK_TO_UNBIND;
}
#endif

//------------------------------------------------------------------------------
// CPC Deconnection Event

void sl_connect_ncp_endpoint_deconnection_handler(void)
{
  if (sl_cpc_get_endpoint_state(&connect_endpoint_handle) == SL_CPC_STATE_FREED) {
    if (connect_cpc_open_endpoint()) {
      emberEventControlSetInactive(sl_connect_ncp_endpoint_deconnection_event);
    }
  }
}

//------------------------------------------------------------------------------
// CPC Init

bool connect_cpc_open_endpoint(void)
{
  sl_status_t status;
  uint8_t window_size = 1;
  uint8_t flags = 0;

  status = sl_cpc_open_user_endpoint(&connect_endpoint_handle,
                                     SL_CPC_ENDPOINT_CONNECT,
                                     flags,
                                     window_size);
  if (status != SL_STATUS_OK) {
    return false;
  }
  status = sl_cpc_set_endpoint_option(&connect_endpoint_handle,
                                      SL_CPC_ENDPOINT_ON_IFRAME_WRITE_COMPLETED,
                                      (void *)on_write_completed);
  if (status != SL_STATUS_OK) {
    return false;
  }
  status = sl_cpc_set_endpoint_option(&connect_endpoint_handle,
                                      SL_CPC_ENDPOINT_ON_IFRAME_RECEIVE,
                                      (void *)cpc_read_command);
  if (status != SL_STATUS_OK) {
    return false;
  }

  status = sl_cpc_set_endpoint_option(&connect_endpoint_handle,
                                      SL_CPC_ENDPOINT_ON_ERROR,
                                      (void*)cpc_error_cb);
  return(status == SL_STATUS_OK);
}

void connect_stack_cpc_init(void)
{
  assert(connect_cpc_open_endpoint());
}
