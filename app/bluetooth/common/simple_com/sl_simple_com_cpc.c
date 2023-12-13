/***************************************************************************//**
 * @file
 * @brief Simple Communication Interface (CPC)
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

#include <string.h>
#include "sl_simple_com.h"
#include "sl_simple_com_config.h"
#include "sli_cpc.h"

// Transmit buffer
static uint8_t tx_buf[SL_SIMPLE_COM_TX_BUF_SIZE] = { 0 };

static sl_cpc_endpoint_handle_t endpoint_handle;
static bool cpc_opened = false;
static bool cpc_connected = false;

// Write completed signal
typedef struct {
  uint8_t     write_completed;
  sl_status_t wr_comp_status;
} sig_wr_comp;

// Signals to handle communication between callback functions
static uint16_t signal_write = 0;
static sig_wr_comp signal_wr_comp = { 0 };
static uint8_t signal_read = 0;

static void cpc_on_tx(sl_cpc_user_endpoint_id_t endpoint_id,
                      void *buffer,
                      void *arg,
                      sl_status_t status);
static void cpc_on_rx(uint8_t endpoint_id, void *arg);
static void cpc_on_error(uint8_t endpoint_id, void *arg);
static void cpc_on_connect(uint8_t endpoint_id, void *arg);

// -----------------------------------------------------------------------------
// Public functions (API implementation)

/**************************************************************************//**
 * Simple COM initialization function
 *****************************************************************************/
void sl_simple_com_init(void)
{
  sl_status_t status;

  // clear TX buffer
  memset(tx_buf, 0, sizeof(tx_buf));

  status = sli_cpc_open_service_endpoint(&endpoint_handle,
                                         SL_CPC_ENDPOINT_BLUETOOTH, 0, 1);
  EFM_ASSERT(status == SL_STATUS_OK);
  status = sl_cpc_set_endpoint_option(&endpoint_handle,
                                      SL_CPC_ENDPOINT_ON_IFRAME_WRITE_COMPLETED,
                                      (void *)cpc_on_tx);
  EFM_ASSERT(status == SL_STATUS_OK);
  status = sl_cpc_set_endpoint_option(&endpoint_handle,
                                      SL_CPC_ENDPOINT_ON_IFRAME_RECEIVE,
                                      (void *)cpc_on_rx);
  EFM_ASSERT(status == SL_STATUS_OK);
  status = sl_cpc_set_endpoint_option(&endpoint_handle,
                                      SL_CPC_ENDPOINT_ON_ERROR,
                                      (void*)cpc_on_error);
  EFM_ASSERT(status == SL_STATUS_OK);
  status = sl_cpc_set_endpoint_option(&endpoint_handle,
                                      SL_CPC_ENDPOINT_ON_CONNECT,
                                      (void*)cpc_on_connect);
  EFM_ASSERT(status == SL_STATUS_OK);

  cpc_opened = true;
}

/**************************************************************************//**
 * Simple COM step function
 *****************************************************************************/
void sl_simple_com_step(void)
{
  // Check if the endpoint is open. If not, we need to reopen it,
  // but first we need to check if it has been freed by CPC
  if (!cpc_opened) {
    if (sl_cpc_get_endpoint_state(&endpoint_handle) == SL_CPC_STATE_FREED) {
      sl_simple_com_init();
    } else {
      sl_simple_com_os_task_proceed();
      return;
    }
  }

  // If tx buffer is not empty, and primary device has connected, transmit it
  if ((signal_write > 0) && cpc_connected) {
    (void)sl_cpc_write(&endpoint_handle, tx_buf, signal_write, 0, NULL);
    signal_write = 0;
  }

  if (signal_read > 0) {
    sl_status_t status;
    uint8_t *data;
    uint16_t data_length;
    status = sl_cpc_read(&endpoint_handle, (void **)&data, &data_length, 0, 0);
    if (status == SL_STATUS_OK) {
      // Send data to upper layers
      sl_simple_com_receive_cb(status, data_length, data);
      sl_cpc_free_rx_buffer(data);
    }
    signal_read--;
  }

  if (signal_wr_comp.write_completed > 0) {
    if (cpc_connected) {
      memset(tx_buf, 0, sizeof(tx_buf));
      sl_simple_com_transmit_cb(signal_wr_comp.wr_comp_status);
      signal_wr_comp.wr_comp_status = SL_STATUS_FAIL;
      signal_wr_comp.write_completed--;
    }
  }
}

/**************************************************************************//**
 * Transmit function
 *
 * Transmits len bytes of data through CPC. If primary device has not connected
 * yet, data is reserved for later transmission. Note that the reserved data
 * will be overwritten on a subsequent transmission.
 *
 * @param[out] len Message length
 * @param[out] data Message data
 *****************************************************************************/
void sl_simple_com_transmit(uint32_t len, const uint8_t *data)
{
  EFM_ASSERT(len <= SL_SIMPLE_COM_TX_BUF_SIZE);
  // Store data in TX buffer until the write completed callback is called
  signal_write = len;
  memcpy((void *)tx_buf, (void *)data, (size_t)len);

  // Only send msg if primary device has connected to the endpoint.
  if (cpc_connected) {
    (void)sl_cpc_write(&endpoint_handle,
                       tx_buf,
                       signal_write,
                       0,
                       (void *)cpc_on_tx);
    signal_write = 0;
  }

  sl_simple_com_os_task_proceed();
}

/**************************************************************************//**
 * Receive function
 *****************************************************************************/
void sl_simple_com_receive(void)
{
  // Not needed in CPC communication
}

/**************************************************************************//**
 * Transmit completed callback
 *
 * Called after transmit is finished.
 *
 * @param[in] status Status of the transmission
 *
 * @note Weak implementation
 *  Called after DMA is complete, the UART transmission might be still ongoing
 *****************************************************************************/
SL_WEAK void sl_simple_com_transmit_cb(sl_status_t status)
{
  (void)status;
}

/**************************************************************************//**
 * Receive completed callback
 *
 * Called after receive is finished.
 *
 * @param[in] status Status of the reception
 * @param[in] len Received message length
 * @param[in] data Data received
 *
 * @note Weak implementation
 *****************************************************************************/
SL_WEAK void sl_simple_com_receive_cb(sl_status_t status,
                                      uint32_t len,
                                      uint8_t *data)
{
  (void)status;
  (void)data;
  (void)len;
}

// -----------------------------------------------------------------------------
// Private functions

/**************************************************************************//**
 * CPC receive completed callback
 *****************************************************************************/
static void cpc_on_rx(uint8_t endpoint_id, void *arg)
{
  (void)endpoint_id;
  (void)arg;

  signal_read++;
  sl_simple_com_os_task_proceed();
}

/**************************************************************************//**
 * CPC transmit completed callback
 *****************************************************************************/
static void cpc_on_tx(sl_cpc_user_endpoint_id_t endpoint_id,
                      void *buffer,
                      void *arg,
                      sl_status_t status)
{
  (void)(endpoint_id);
  (void)(buffer);
  (void)(arg);

  CORE_ATOMIC_SECTION(
    signal_wr_comp.wr_comp_status = status;
    signal_wr_comp.write_completed++;
    )
  sl_simple_com_os_task_proceed();
}

/**************************************************************************//**
 * CPC error callback
 *****************************************************************************/
static void cpc_on_error(uint8_t endpoint_id, void *arg)
{
  (void)endpoint_id;
  (void)arg;
  uint8_t state = sl_cpc_get_endpoint_state(&endpoint_handle);
  if (state == SL_CPC_STATE_ERROR_DESTINATION_UNREACHABLE) {
    sl_status_t status = sl_cpc_close_endpoint(&endpoint_handle);
    EFM_ASSERT(status == SL_STATUS_OK);
    cpc_opened = false;
    cpc_connected = false;
  }
  sl_simple_com_os_task_proceed();
}

/**************************************************************************//**
 * CPC connection callback
 *****************************************************************************/
static void cpc_on_connect(uint8_t endpoint_id, void *arg)
{
  (void)endpoint_id;
  (void)arg;
  cpc_connected = true;
  sl_simple_com_os_task_proceed();
}

/**************************************************************************//**
 * Function to trigger the OS task to proceed
 *
 * @note Weak implementation.
 *****************************************************************************/
SL_WEAK void sl_simple_com_os_task_proceed(void)
{
  // No action on bare metal implementation
}
