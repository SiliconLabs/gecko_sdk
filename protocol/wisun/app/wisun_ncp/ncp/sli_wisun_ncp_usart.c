/***************************************************************************//**
 * @file sli_wisun_ncp_usart.c
 * @brief Wi-SUN NCP USART handling
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include "sl_uartdrv_instances.h"
#include "sl_uartdrv_usart_vcom_config.h"
#include "sli_wisun_ncp_usart.h"

#define SLI_WISUN_NCP_UART_BUFFER_SIZE 1500

#if SL_UARTDRV_USART_VCOM_PERIPHERAL_NO == 0
#define SLI_WISUN_NCP_USART_RX_IRQHandler   USART0_RX_IRQHandler
#define SLI_WISUN_NCP_USART_RX_IRQn         USART0_RX_IRQn
#elif SL_UARTDRV_USART_VCOM_PERIPHERAL_NO == 1
#define SLI_WISUN_NCP_USART_RX_IRQHandler   USART1_RX_IRQHandler
#define SLI_WISUN_NCP_USART_RX_IRQn         USART1_RX_IRQn
#elif SL_UARTDRV_USART_VCOM_PERIPHERAL_NO == 2
#define SLI_WISUN_NCP_USART_RX_IRQHandler   USART2_RX_IRQHandler
#define SLI_WISUN_NCP_USART_RX_IRQn         USART2_RX_IRQn
#elif SL_UARTDRV_USART_VCOM_PERIPHERAL_NO == 3
#define SLI_WISUN_NCP_USART_RX_IRQHandler   USART3_RX_IRQHandler
#define SLI_WISUN_NCP_USART_RX_IRQn         USART3_RX_IRQn
#else
#error "Unsupported UART port!"
#endif


static uint8_t sli_wisun_ncp_uart_tx_buf[SLI_WISUN_NCP_UART_BUFFER_SIZE] = { 0 };
static uint8_t sli_wisun_ncp_uart_rx_buf[SLI_WISUN_NCP_UART_BUFFER_SIZE] = { 0 };
static uint32_t ncp_uart_rx_timeout_count;

static void sli_wisun_ncp_uart_transmit_complete_cb(UARTDRV_Handle_t handle,
                                                    Ecode_t transferStatus,
                                                    uint8_t *data,
                                                    UARTDRV_Count_t transferCount);
static void sli_wisun_ncp_uart_receive_complete_cb(UARTDRV_Handle_t handle,
                                                   Ecode_t transferStatus,
                                                   uint8_t *data,
                                                   UARTDRV_Count_t transferCount);
static int sli_wisun_ncp_uart_receive_timeout_cb(UARTDRV_Handle_t handle,
                                                 uint32_t timeout_count,
                                                 uint8_t *data,
                                                 UARTDRV_Count_t transferCount);
static Ecode_t UARTDRV_Abort_receive_timeout(UARTDRV_Handle_t handle);
static Ecode_t GetTailBuffer(UARTDRV_Buffer_FifoQueue_t *queue,
                             UARTDRV_Buffer_t **buffer);
static Ecode_t DequeueBuffer(UARTDRV_Buffer_FifoQueue_t *queue,
                             UARTDRV_Buffer_t **buffer);
static void DisableReceiver(UARTDRV_Handle_t handle);

void sli_wisun_ncp_uart_init(void)
{
  memset(sli_wisun_ncp_uart_rx_buf, 0, sizeof(sli_wisun_ncp_uart_rx_buf));
  memset(sli_wisun_ncp_uart_tx_buf, 0, sizeof(sli_wisun_ncp_uart_tx_buf));

  CORE_SetNvicRamTableHandler(SLI_WISUN_NCP_USART_RX_IRQn, (void *)SLI_WISUN_NCP_USART_RX_IRQHandler);

  // Clear pending RX interrupt flag in NVIC
  NVIC_ClearPendingIRQ(SLI_WISUN_NCP_USART_RX_IRQn);
  NVIC_EnableIRQ(SLI_WISUN_NCP_USART_RX_IRQn);

  // Setup RX timeout to 255 bit-time
  sl_uartdrv_usart_vcom_handle->peripheral.uart->TIMECMP1 = \
    USART_TIMECMP1_TSTOP_RXACT
    | USART_TIMECMP1_TSTART_RXEOF
    | USART_TIMECMP1_RESTARTEN
    | (0xff << _USART_TIMECMP1_TCMPVAL_SHIFT);

  // Clear any USART interrupt flags
  USART_IntClear(sl_uartdrv_usart_vcom_handle->peripheral.uart,
                 USART_IF_TCMP1);
  USART_IntEnable(sl_uartdrv_usart_vcom_handle->peripheral.uart,
                  USART_IF_TCMP1);
}

void sli_wisun_ncp_uart_transmit(uint32_t len, const uint8_t* data)
{
  // Make a copy of the data to be sent to guarantee its integrity until
  // transmission completes.
  memcpy((void*)sli_wisun_ncp_uart_tx_buf, (const void*)data, (size_t)len);

  // Transmit data using a non-blocking transmit function
  assert(UARTDRV_Transmit(sl_uartdrv_usart_vcom_handle,
                          sli_wisun_ncp_uart_tx_buf,
                          len,
                          sli_wisun_ncp_uart_transmit_complete_cb) == ECODE_EMDRV_UARTDRV_OK);
}

void sli_wisun_ncp_uart_receive(void)
{
  ncp_uart_rx_timeout_count = 0;

  // Setup RX timeout to 255 bit-time
  sl_uartdrv_usart_vcom_handle->peripheral.uart->TIMECMP1 = \
    USART_TIMECMP1_TSTOP_RXACT
    | USART_TIMECMP1_TSTART_RXEOF
    | USART_TIMECMP1_RESTARTEN
    | (0xff << _USART_TIMECMP1_TCMPVAL_SHIFT);

  UARTDRV_Receive(sl_uartdrv_usart_vcom_handle,
                  sli_wisun_ncp_uart_rx_buf,
                  sizeof(sli_wisun_ncp_uart_rx_buf),
                  sli_wisun_ncp_uart_receive_complete_cb);
}

SL_WEAK void sli_wisun_ncp_uart_transmit_cb(sl_status_t status)
{
  (void)status;
}

SL_WEAK void sli_wisun_ncp_uart_receive_cb(sl_status_t status,
                                           uint32_t len,
                                           const uint8_t* data)
{
  (void)status;
  (void)data;
  (void)len;
}

SL_WEAK int sli_wisun_ncp_uart_timeout_cb(uint32_t timeout_count,
                                          uint32_t len,
                                          const uint8_t *data)
{
  (void)timeout_count;
  (void)data;
  (void)len;

  return 1;
}

static void sli_wisun_ncp_uart_transmit_complete_cb(UARTDRV_Handle_t handle,
                                                    Ecode_t transferStatus,
                                                    uint8_t *data,
                                                    UARTDRV_Count_t transferCount)
{
  (void)handle;
  (void)data;
  (void)transferCount;

  // Call public callback API
  sli_wisun_ncp_uart_transmit_cb(ECODE_EMDRV_UARTDRV_OK == transferStatus
                                 ? SL_STATUS_OK : SL_STATUS_FAIL);
  // Clear TX buffer
  memset(sli_wisun_ncp_uart_tx_buf, 0, sizeof(sli_wisun_ncp_uart_tx_buf));
}

static void sli_wisun_ncp_uart_receive_complete_cb(UARTDRV_Handle_t handle,
                                                   Ecode_t transferStatus,
                                                   uint8_t *data,
                                                   UARTDRV_Count_t transferCount)
{
  (void)handle;

  // Call public callback API
  sli_wisun_ncp_uart_receive_cb(ECODE_EMDRV_UARTDRV_OK == transferStatus
                                ? SL_STATUS_OK : SL_STATUS_FAIL,
                                transferCount,
                                data);
  // Clear RX buffer
  memset(sli_wisun_ncp_uart_rx_buf, 0, sizeof(sli_wisun_ncp_uart_rx_buf));
}

static int sli_wisun_ncp_uart_receive_timeout_cb(UARTDRV_Handle_t handle,
                                                 uint32_t timeout_count,
                                                 uint8_t *data,
                                                 UARTDRV_Count_t transferCount)
{
  (void)handle;

  return sli_wisun_ncp_uart_timeout_cb(timeout_count, transferCount, data);
}

// TODO: this should be provided by UARTDRV
void SLI_WISUN_NCP_USART_RX_IRQHandler(void)
{
  uint8_t *buffer;
  UARTDRV_Count_t bytesReceived;
  UARTDRV_Count_t bytesRemaining;

  // RX timeout
  if (sl_uartdrv_usart_vcom_handle->peripheral.uart->IF & USART_IF_TCMP1) {
    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_ATOMIC();

    ++ncp_uart_rx_timeout_count;

    // Current transfer status
    UARTDRV_GetReceiveStatus(sl_uartdrv_usart_vcom_handle,
                             &buffer,
                             &bytesReceived,
                             &bytesRemaining);

    // Clear timer interrupt
    USART_IntClear(sl_uartdrv_usart_vcom_handle->peripheral.uart, USART_IF_TCMP1);

    // Let application decide if enough data has been received or if timeout
    // has been exceeded.
    if (sli_wisun_ncp_uart_receive_timeout_cb(sl_uartdrv_usart_vcom_handle,
                                              ncp_uart_rx_timeout_count,
                                              buffer,
                                              bytesReceived)) {
      // Stop the timer
      sl_uartdrv_usart_vcom_handle->peripheral.uart->TIMECMP1 &= ~_USART_TIMECMP1_TSTART_MASK;
      // Stop RX and handle what we got in buffer
      UARTDRV_Abort_receive_timeout(sl_uartdrv_usart_vcom_handle);
      // Start RX
      sli_wisun_ncp_uart_receive();
    }

    CORE_EXIT_ATOMIC();
  }
}

// TODO: this should be provided by UARTDRV
static Ecode_t UARTDRV_Abort_receive_timeout(UARTDRV_Handle_t handle)
{
  UARTDRV_Buffer_t *rxBuffer;
  Ecode_t status;
  CORE_DECLARE_IRQ_STATE;

  if (handle == NULL) {
    return ECODE_EMDRV_UARTDRV_ILLEGAL_HANDLE;
  }

  CORE_ENTER_ATOMIC();
  if (handle->rxQueue->used == 0) {
    CORE_EXIT_ATOMIC();
    return ECODE_EMDRV_UARTDRV_IDLE;
  }

  // Stop the current transfer
  DMADRV_StopTransfer(handle->rxDmaCh);
  handle->rxDmaActive = false;
  // Update the transfer status of the active transfer
  status = GetTailBuffer(handle->rxQueue, &rxBuffer);
  // If an abort was in progress when DMA completed, the ISR could be deferred
  // until after the critical section. In this case, the buffers no longer
  // exist, even though the DMA complete callback was called.
  if (status == ECODE_EMDRV_UARTDRV_QUEUE_EMPTY) {
    return ECODE_EMDRV_UARTDRV_QUEUE_EMPTY;
  }
  EFM_ASSERT(rxBuffer != NULL);
  DMADRV_TransferRemainingCount(handle->rxDmaCh,
                                (int*)&rxBuffer->itemsRemaining);
  rxBuffer->transferStatus = ECODE_EMDRV_UARTDRV_ABORTED;

  // Dequeue all transfers and call callback
  while (handle->rxQueue->used > 0) {
    DequeueBuffer(handle->rxQueue, &rxBuffer);
    // Call the callback
    if (rxBuffer->callback != NULL) {
      if (rxBuffer->callback != NULL) {
        rxBuffer->callback(handle,
                           ECODE_EMDRV_UARTDRV_OK,
                           rxBuffer->data,
                           rxBuffer->transferCount - rxBuffer->itemsRemaining);
      }
    }
  }

  // Disable the receiver
  if (handle->fcType != uartdrvFlowControlHwUart) {
    DisableReceiver(handle);
  }
  CORE_EXIT_ATOMIC();

  return ECODE_EMDRV_UARTDRV_OK;
}

static Ecode_t GetTailBuffer(UARTDRV_Buffer_FifoQueue_t *queue,
                             UARTDRV_Buffer_t **buffer)
{
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_ATOMIC();
  if (queue->used == 0) {
    *buffer = NULL;
    CORE_EXIT_ATOMIC();
    return ECODE_EMDRV_UARTDRV_QUEUE_EMPTY;
  }
  *buffer = &queue->fifo[queue->tail];

  CORE_EXIT_ATOMIC();
  return ECODE_EMDRV_UARTDRV_OK;
}

static Ecode_t DequeueBuffer(UARTDRV_Buffer_FifoQueue_t *queue,
                             UARTDRV_Buffer_t **buffer)
{
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_ATOMIC();
  if (queue->used == 0) {
    *buffer = NULL;
    CORE_EXIT_ATOMIC();
    return ECODE_EMDRV_UARTDRV_QUEUE_EMPTY;
  }
  *buffer = &queue->fifo[queue->tail];
  queue->tail = (queue->tail + 1) % queue->size;
  queue->used--;
  CORE_EXIT_ATOMIC();

  return ECODE_EMDRV_UARTDRV_OK;
}

static void DisableReceiver(UARTDRV_Handle_t handle)
{
#if (defined(LEUART_COUNT) && (LEUART_COUNT > 0) && !defined(_SILICON_LABS_32B_SERIES_2)) \
  || (defined(EUART_COUNT) && (EUART_COUNT > 0) )
  if (handle->type == uartdrvUartTypeUart)
#endif
  {
    // Disable Rx route
#if defined(USART_ROUTEPEN_RXPEN)
    handle->peripheral.uart->ROUTEPEN &= ~USART_ROUTEPEN_RXPEN;
#elif defined(USART_ROUTE_RXPEN)
    handle->peripheral.uart->ROUTE &= ~USART_ROUTE_RXPEN;
#elif defined(GPIO_USART_ROUTEEN_RXPEN)
    GPIO->USARTROUTE_CLR[handle->uartNum].ROUTEEN = GPIO_USART_ROUTEEN_RXPEN;
#endif
    // Disable Rx
    handle->peripheral.uart->CMD = USART_CMD_RXDIS;
  }
#if defined(LEUART_COUNT) && (LEUART_COUNT > 0) && !defined(_SILICON_LABS_32B_SERIES_2)
  else if (handle->type == uartdrvUartTypeLeuart) {
    // Wait for prevous register writes to sync
    while ((handle->peripheral.leuart->SYNCBUSY & LEUART_SYNCBUSY_CMD) != 0U) {
    }

    // Disable Rx route
#if defined(LEUART_ROUTEPEN_RXPEN)
    handle->peripheral.leuart->ROUTEPEN &= ~LEUART_ROUTEPEN_RXPEN;
#else
    handle->peripheral.leuart->ROUTE &= ~LEUART_ROUTE_RXPEN;
#endif
    // Disable Rx
    handle->peripheral.leuart->CMD = LEUART_CMD_RXDIS;
  }
#elif defined(EUART_COUNT) && (EUART_COUNT > 0)
  else if (handle->type == uartdrvUartTypeEuart) {
    if (EUSART_StatusGet(handle->peripheral.euart) &  EUSART_STATUS_TXENS) {
      EUSART_Enable(handle->peripheral.euart, eusartEnableTx);
    } else {
      EUSART_Enable(handle->peripheral.euart, eusartDisable);
    }
  }
#endif
}
