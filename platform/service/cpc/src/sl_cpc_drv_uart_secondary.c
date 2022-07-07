/***************************************************************************/ /**
 * @file
 * @brief CPC UART SECONDARY implementation.
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

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif
#include "em_usart.h"
#include "em_ldma.h"
#include "em_cmu.h"
#include "em_gpio.h"

#include "dmadrv.h"

#include "sl_status.h"
#include "sl_atomic.h"
#include "sl_slist.h"

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
#include "sl_power_manager.h"
#endif

#include "sli_cpc_drv.h"
#include "sli_cpc_hdlc.h"
#include "sli_cpc_debug.h"
#include "sli_cpc_crc.h"
#include "sl_cpc_config.h"
#include "sl_cpc_drv_uart_secondary_config.h"
#include "sli_cpc.h"

/*******************************************************************************
 *********************************   DEFINES   *********************************
 ******************************************************************************/

typedef struct {
  sl_slist_node_t node;
  sl_cpc_buffer_handle_t *handle;
  uint16_t payload_len;
} sli_buf_entry_t;

#define SL_CPC_CONCAT_PASTER(first, second, third)  first ##  second ## third
#define SL_CPC_PERIPH_CLOCK(first, second)  first ##  second

#define SL_CPC_USART_CLOCK(periph)                 SL_CPC_PERIPH_CLOCK(cmuClock_USART, periph)
#define SL_CPC_RX_IRQn(periph_nbr)                 SL_CPC_CONCAT_PASTER(USART, periph_nbr, _RX_IRQn)
#define SL_CPC_TX_IRQn(periph_nbr)                 SL_CPC_CONCAT_PASTER(USART, periph_nbr, _TX_IRQn)
#define SL_CPC_ISR_RX_HANDLER(periph_nbr)          SL_CPC_CONCAT_PASTER(USART, periph_nbr, _RX_IRQHandler)
#define SL_CPC_ISR_TX_HANDLER(periph_nbr)          SL_CPC_CONCAT_PASTER(USART, periph_nbr, _TX_IRQHandler)

#define SL_CPC_LDMA_RX_PERIPH_TRIGGER(periph_nbr)   SL_CPC_CONCAT_PASTER(ldmaPeripheralSignal_USART, periph_nbr, _RXDATAV)
#define SL_CPC_LDMA_TX_PERIPH_TRIGGER(periph_nbr)   SL_CPC_CONCAT_PASTER(ldmaPeripheralSignal_USART, periph_nbr, _TXBL)

/// Maximum length of one LDMA transfer.
#define DMA_MAX_XFER_LEN (((_LDMA_CH_CTRL_XFERCNT_MASK >> _LDMA_CH_CTRL_XFERCNT_SHIFT) + 1))

#define RX_DMA_DESCRIPTOR_PER_BUF  ((SLI_CPC_RX_DATA_MAX_LENGTH + DMA_MAX_XFER_LEN - 1) / DMA_MAX_XFER_LEN)
#define RX_DMA_DESCRIPTOR_QTY      (SL_CPC_DRV_UART_RX_QUEUE_SIZE * RX_DMA_DESCRIPTOR_PER_BUF)

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

static unsigned int read_channel;
static unsigned int write_channel;

static LDMA_TransferCfg_t rx_config;
static LDMA_TransferCfg_t tx_config;

static LDMA_Descriptor_t rx_descriptor[RX_DMA_DESCRIPTOR_QTY];
static LDMA_Descriptor_t *rx_descriptor_head = NULL;
static LDMA_Descriptor_t *rx_descriptor_tail = NULL;

static LDMA_Descriptor_t tx_descriptor[4u];

static sl_slist_node_t *rx_free_list_head;
static sl_slist_node_t *rx_free_no_buf_list_head;
static sl_slist_node_t *rx_pending_list_head;

static sl_slist_node_t *tx_free_list_head;
static sl_slist_node_t *tx_submitted_list_head;

static sli_buf_entry_t rx_buf_entries_tbl[SL_CPC_DRV_UART_RX_QUEUE_SIZE];
static sli_buf_entry_t tx_buf_entries_tbl[SL_CPC_DRV_UART_TX_QUEUE_SIZE];

static sli_buf_entry_t *current_rx_entry;

static bool tx_ready = true;

static sli_mem_pool_handle_t mempool_rx_dma_desc;
static uint16_t next_rx_buf_tot_len = 0;
static bool header_expected_next = true;
static uint16_t next_rx_payload_len = 0;

static uint16_t nb_desc_free = 0u;

static uint8_t rx_synch_header[SLI_CPC_HDLC_HEADER_RAW_SIZE];
static uint16_t rx_synch_byte_cnt = 0;
static bool rx_need_desc = false;
static bool rx_need_rx_entry = false;

volatile uint16_t already_recvd_cnt_worst = 0;

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/

//static void sli_cpc_uart_read_data_idle(void);
static sl_status_t prepare_next_tx(void);

static bool rx_dma_complete(unsigned int channel,
                            unsigned int sequenceNo,
                            void *userParam);

static void force_current_rx_dma_length(uint16_t new_length);

static bool update_current_rx_dma_length(uint16_t new_length);

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == usartHwFlowControlNone_D)
static bool update_current_rx_dma_large_payload_length(uint16_t new_length);

static void rx_buffer_free_from_isr(void);

static void push_back_new_rx_dma_desc(LDMA_Descriptor_t *new_dma_desc,
                                      void *buffer);

static void update_dma_desc_link_abs(LDMA_Descriptor_t *current_dma_desc,
                                     LDMA_Descriptor_t *next_dma_desc);
#endif

static void notify_core_error(sl_cpc_reject_reason_t reason);

static void start_re_synch(void);

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************/ /**
 * Initiate UART Hardware.
 ******************************************************************************/
sl_status_t sli_cpc_drv_init(void)
{
  uint32_t buf_cnt;
  Ecode_t ecode;
  USART_InitAsync_TypeDef init = USART_INITASYNC_DEFAULT;
  uint32_t dma_desc_cnt = 0;
  LDMA_Descriptor_t *current_desc;
  LDMA_Descriptor_t *previous_desc = NULL;
  void *buffer_ptr;

  // Enable peripheral clocks
#if defined(_CMU_HFPERCLKEN0_MASK)
  CMU_ClockEnable(cmuClock_HFPER, true);
#endif

  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(SL_CPC_USART_CLOCK(SL_CPC_DRV_UART_PERIPHERAL_NO), true);

  NVIC_EnableIRQ(SL_CPC_TX_IRQn(SL_CPC_DRV_UART_PERIPHERAL_NO));
  NVIC_EnableIRQ(SL_CPC_RX_IRQn(SL_CPC_DRV_UART_PERIPHERAL_NO));

  sl_slist_init(&rx_free_list_head);
  sl_slist_init(&rx_free_no_buf_list_head);
  sl_slist_init(&rx_pending_list_head);
  sl_slist_init(&tx_free_list_head);
  sl_slist_init(&tx_submitted_list_head);

  current_rx_entry = NULL;

  for (buf_cnt = 0; buf_cnt < SL_CPC_DRV_UART_RX_QUEUE_SIZE; buf_cnt++) {
    sli_buf_entry_t *entry = &rx_buf_entries_tbl[buf_cnt];
    EFM_ASSERT(sli_cpc_get_rx_buffer(&entry->handle) == SL_STATUS_OK);
    sli_cpc_push_buffer_handle(&rx_free_list_head, &entry->node, entry->handle);
  }

  for (buf_cnt = 0; buf_cnt < SL_CPC_DRV_UART_TX_QUEUE_SIZE; buf_cnt++) {
    sli_buf_entry_t *entry = &tx_buf_entries_tbl[buf_cnt];
    sl_slist_push(&tx_free_list_head, &entry->node);
  }

  // Configure TX and RX GPIOs
  GPIO_PinModeSet(SL_CPC_DRV_UART_TX_PORT, SL_CPC_DRV_UART_TX_PIN, gpioModePushPull, 1);
  GPIO_PinModeSet(SL_CPC_DRV_UART_RX_PORT, SL_CPC_DRV_UART_RX_PIN, gpioModeInputPull, 1);

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == usartHwFlowControlNone_D)
  init.hwFlowControl = usartHwFlowControlNone;
#elif (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == usartHwFlowControlCtsAndRts_D)
  init.hwFlowControl = usartHwFlowControlCtsAndRts;
#endif

  init.baudrate = SL_CPC_DRV_UART_BAUDRATE;
  init.enable = usartDisable;

  // Initialize an UART driver instance.
  USART_InitAsync(SL_CPC_DRV_UART_PERIPHERAL, &init);

#if defined(USART_ROUTEPEN_TXPEN)
  SL_CPC_DRV_UART_PERIPHERAL->ROUTELOC0 = (SL_CPC_DRV_UART_PERIPHERAL->ROUTELOC0
                                           & ~(_USART_ROUTELOC0_TXLOC_MASK
                                               | _USART_ROUTELOC0_RXLOC_MASK))
                                          | (SL_CPC_DRV_UART_TX_LOC
                                             << _USART_ROUTELOC0_TXLOC_SHIFT)
                                          | (SL_CPC_DRV_UART_RX_LOC
                                             << _USART_ROUTELOC0_RXLOC_SHIFT);

  SL_CPC_DRV_UART_PERIPHERAL->ROUTEPEN = USART_ROUTEPEN_TXPEN
                                         | USART_ROUTEPEN_RXPEN;
#elif defined(USART_ROUTE_TXPEN)
  SL_CPC_DRV_UART_PERIPHERAL->ROUTE = USART_ROUTE_TXPEN
                                      | USART_ROUTE_RXPEN
                                      | (SL_CPC_DRV_UART_RX_LOC
                                         << _USART_ROUTE_LOCATION_SHIFT);
#elif defined(GPIO_USART_ROUTEEN_TXPEN)
  GPIO->USARTROUTE[SL_CPC_DRV_UART_PERIPHERAL_NO].ROUTEEN = GPIO_USART_ROUTEEN_TXPEN
                                                            | GPIO_USART_ROUTEEN_RXPEN;
  GPIO->USARTROUTE[SL_CPC_DRV_UART_PERIPHERAL_NO].TXROUTE =
    (SL_CPC_DRV_UART_TX_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT)
    | (SL_CPC_DRV_UART_TX_PIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[SL_CPC_DRV_UART_PERIPHERAL_NO].RXROUTE =
    (SL_CPC_DRV_UART_RX_PORT << _GPIO_USART_RXROUTE_PORT_SHIFT)
    | (SL_CPC_DRV_UART_RX_PIN << _GPIO_USART_RXROUTE_PIN_SHIFT);
#endif

  if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == usartHwFlowControlCtsAndRts_D) {
    GPIO_PinModeSet(SL_CPC_DRV_UART_CTS_PORT, SL_CPC_DRV_UART_CTS_PIN, gpioModeInputPull, 0);

#if defined(_USART_ROUTEPEN_RTSPEN_MASK) && defined(_USART_ROUTEPEN_CTSPEN_MASK)
    SL_CPC_DRV_UART_PERIPHERAL->ROUTELOC1 = (SL_CPC_DRV_UART_CTS_LOC << _USART_ROUTELOC1_CTSLOC_SHIFT);
    SL_CPC_DRV_UART_PERIPHERAL->CTRLX    |= USART_CTRLX_CTSEN;
    SL_CPC_DRV_UART_PERIPHERAL->ROUTEPEN |= USART_ROUTEPEN_CTSPEN;
#elif defined(_GPIO_USART_ROUTEEN_MASK)
    GPIO->USARTROUTE_SET[SL_CPC_DRV_UART_PERIPHERAL_NO].CTSROUTE = (SL_CPC_DRV_UART_CTS_PORT << _GPIO_USART_CTSROUTE_PORT_SHIFT)
                                                                   | (SL_CPC_DRV_UART_CTS_PIN << _GPIO_USART_CTSROUTE_PIN_SHIFT);
    SL_CPC_DRV_UART_PERIPHERAL->CTRLX_SET = USART_CTRLX_CTSEN;
#endif

    GPIO_PinModeSet(SL_CPC_DRV_UART_RTS_PORT, SL_CPC_DRV_UART_RTS_PIN, gpioModePushPull, 0);

#if defined(_USART_ROUTEPEN_RTSPEN_MASK) && defined(_USART_ROUTEPEN_CTSPEN_MASK)
    SL_CPC_DRV_UART_PERIPHERAL->ROUTELOC1 |= (SL_CPC_DRV_UART_RTS_LOC << _USART_ROUTELOC1_RTSLOC_SHIFT);
    SL_CPC_DRV_UART_PERIPHERAL->ROUTEPEN |= USART_ROUTEPEN_RTSPEN;

#elif defined(_GPIO_USART_ROUTEEN_MASK)
    GPIO->USARTROUTE_SET[SL_CPC_DRV_UART_PERIPHERAL_NO].ROUTEEN = GPIO_USART_ROUTEEN_RTSPEN;
    GPIO->USARTROUTE_SET[SL_CPC_DRV_UART_PERIPHERAL_NO].RTSROUTE = (SL_CPC_DRV_UART_RTS_PORT << _GPIO_USART_RTSROUTE_PORT_SHIFT)
                                                                   | (SL_CPC_DRV_UART_RTS_PIN << _GPIO_USART_RTSROUTE_PIN_SHIFT);
#endif
  }

  // Enabled TX complete interrupt
  USART_IntEnable(SL_CPC_DRV_UART_PERIPHERAL, USART_IF_TXC);

  USART_IntClear(SL_CPC_DRV_UART_PERIPHERAL, 0xFFFFFFFF);

  // Discard false frames and/or IRQs
  SL_CPC_DRV_UART_PERIPHERAL->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;

  USART_Enable(SL_CPC_DRV_UART_PERIPHERAL, usartEnable);

  // Init DMA
  DMADRV_Init();

  // Allocate read and write channel
  ecode = DMADRV_AllocateChannel(&read_channel, NULL);
  EFM_ASSERT(ecode == ECODE_OK);
  ecode = DMADRV_AllocateChannel(&write_channel, NULL);
  EFM_ASSERT(ecode == ECODE_OK);

  // Configure DMA transfer
  rx_config = (LDMA_TransferCfg_t)LDMA_TRANSFER_CFG_PERIPHERAL(SL_CPC_LDMA_RX_PERIPH_TRIGGER(SL_CPC_DRV_UART_PERIPHERAL_NO));
  tx_config = (LDMA_TransferCfg_t)LDMA_TRANSFER_CFG_PERIPHERAL(SL_CPC_LDMA_TX_PERIPH_TRIGGER(SL_CPC_DRV_UART_PERIPHERAL_NO));

  sli_mem_pool_create(&mempool_rx_dma_desc,
                      sizeof(LDMA_Descriptor_t),
                      RX_DMA_DESCRIPTOR_QTY,
                      rx_descriptor,
                      sizeof(rx_descriptor));

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == usartHwFlowControlCtsAndRts_D)
  (void)dma_desc_cnt;
  (void)previous_desc;
  (void)nb_desc_free;

  sl_status_t status;

  status = sli_cpc_get_raw_rx_buffer(&buffer_ptr);
  EFM_ASSERT(status == SL_STATUS_OK);

  current_desc = (LDMA_Descriptor_t *)sli_mem_pool_alloc(&mempool_rx_dma_desc);
  *current_desc = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(&(SL_CPC_DRV_UART_PERIPHERAL->RXDATA), buffer_ptr, (SLI_CPC_RX_DATA_MAX_LENGTH < DMA_MAX_XFER_LEN) ? SLI_CPC_RX_DATA_MAX_LENGTH : DMA_MAX_XFER_LEN);

  rx_descriptor_tail = current_desc;
#else
  // Prime rx dma channel will all available descriptors.
  while (dma_desc_cnt < RX_DMA_DESCRIPTOR_QTY) {
    sl_status_t status;

    status = sli_cpc_get_raw_rx_buffer(&buffer_ptr);
    EFM_ASSERT(status == SL_STATUS_OK);

    current_desc = (LDMA_Descriptor_t *)sli_mem_pool_alloc(&mempool_rx_dma_desc);
    *current_desc = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(&(SL_CPC_DRV_UART_PERIPHERAL->RXDATA), buffer_ptr, (SLI_CPC_RX_DATA_MAX_LENGTH < DMA_MAX_XFER_LEN) ? SLI_CPC_RX_DATA_MAX_LENGTH : DMA_MAX_XFER_LEN);

    if (dma_desc_cnt == 0) {
      rx_descriptor_tail = current_desc;
    }

    if (previous_desc) {
      update_dma_desc_link_abs(current_desc, previous_desc);
    }

    dma_desc_cnt++;
    previous_desc = current_desc;
  }
#endif

  current_desc->xfer.xferCnt = SLI_CPC_HDLC_HEADER_RAW_SIZE - 1u;
  next_rx_buf_tot_len = SLI_CPC_HDLC_HEADER_RAW_SIZE;
  header_expected_next = true;

  rx_descriptor_head = current_desc;

  // Start read channel
  ecode = DMADRV_LdmaStartTransfer(read_channel,
                                   &rx_config,
                                   current_desc,
                                   rx_dma_complete,
                                   0);
  EFM_ASSERT(ecode == ECODE_OK);

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
  sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
#endif

  return SL_STATUS_OK;
}

/***************************************************************************/ /**
 * Gets CPC driver capabilities.
 ******************************************************************************/
void sli_cpc_drv_get_capabilities(sli_cpc_drv_capabilities_t *capabilities)
{
  if (capabilities == NULL) {
    return;
  }

  *capabilities = (sli_cpc_drv_capabilities_t){0 };
  capabilities->preprocess_hdlc_header = true;
  capabilities->use_raw_rx_buffer = true;
}

/***************************************************************************/ /**
 * Read bytes from UART.
 ******************************************************************************/
sl_status_t sli_cpc_drv_read_data(sl_cpc_buffer_handle_t **buffer_handle, uint16_t *payload_rx_len)
{
  sl_status_t status;
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_ATOMIC();
  sli_buf_entry_t *entry = (sli_buf_entry_t *)SLI_CPC_POP_BUFFER_HANDLE_LIST(&rx_pending_list_head, sli_buf_entry_t);
  if (entry == NULL) {
    CORE_EXIT_ATOMIC();
    return SL_STATUS_EMPTY;
  }
  CORE_EXIT_ATOMIC();

  *buffer_handle = entry->handle;
  *payload_rx_len = SLI_CPC_RX_DATA_MAX_LENGTH;

  CORE_ENTER_ATOMIC();
  status = sli_cpc_get_rx_buffer(&entry->handle);
  if (status == SL_STATUS_OK) {
    sli_cpc_push_buffer_handle(&rx_free_list_head, &entry->node, entry->handle);
    if (rx_need_rx_entry) {
      rx_need_rx_entry = false;
      USART_IntEnable(SL_CPC_DRV_UART_PERIPHERAL, USART_IF_RXDATAV);
    }
  } else {
    sl_slist_push(&rx_free_no_buf_list_head, &entry->node);
  }
  CORE_EXIT_ATOMIC();

  return SL_STATUS_OK;
}

/***************************************************************************/ /**
 * Write bytes to UART.
 ******************************************************************************/
sl_status_t sli_cpc_drv_transmit_data(sl_cpc_buffer_handle_t *buffer_handle, uint16_t payload_tx_len)
{
  sl_status_t status;
  sli_buf_entry_t *entry;
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_ATOMIC();
  entry = (sli_buf_entry_t *)sl_slist_pop(&tx_free_list_head);
  CORE_EXIT_ATOMIC();

  if (entry == NULL) {
    return SL_STATUS_NOT_READY;
  }

  entry->handle = buffer_handle;
  entry->payload_len = payload_tx_len;

  CORE_ENTER_ATOMIC();
  sli_cpc_push_back_buffer_handle(&tx_submitted_list_head, &entry->node, entry->handle);

  status = prepare_next_tx();
  if (status == SL_STATUS_RECEIVE) {
    status = SL_STATUS_OK;
  }
  CORE_EXIT_ATOMIC();

  return status;
}

/***************************************************************************/ /**
 * Checks if driver is ready to transmit.
 ******************************************************************************/
bool sli_cpc_drv_is_transmit_ready(void)
{
  sl_slist_node_t *head;
  bool flag;

  sl_atomic_load(flag, tx_ready);
  sl_atomic_load(head, tx_free_list_head);

  return (head != NULL
          && flag);
}

/***************************************************************************/ /**
 * Prepare for transmission of next buffer.
 ******************************************************************************/
static sl_status_t prepare_next_tx(void)
{
  Ecode_t code;
  sli_buf_entry_t *entry;
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_ATOMIC();
  entry = (sli_buf_entry_t *)tx_submitted_list_head;
  if (entry == NULL) {
    CORE_EXIT_ATOMIC();
    return SL_STATUS_EMPTY;
  }

  if (entry->payload_len <= DMADRV_MAX_XFER_COUNT && entry->payload_len != 0u) {
    tx_descriptor[0u] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_M2P_BYTE(entry->handle->hdlc_header, &(SL_CPC_DRV_UART_PERIPHERAL->TXDATA), SLI_CPC_HDLC_HEADER_RAW_SIZE, 1);
    tx_descriptor[1u] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_M2P_BYTE(entry->handle->data, &(SL_CPC_DRV_UART_PERIPHERAL->TXDATA), entry->payload_len, 1u);
    tx_descriptor[2u] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_M2P_BYTE(entry->handle->fcs, &(SL_CPC_DRV_UART_PERIPHERAL->TXDATA), 2u);
    tx_descriptor[0u].xfer.doneIfs = 0u;
    tx_descriptor[1u].xfer.doneIfs = 0u;
    tx_descriptor[2u].xfer.doneIfs = 1u;
  } else if (entry->payload_len <= (DMADRV_MAX_XFER_COUNT * 2) && entry->payload_len > 0u) {
    tx_descriptor[0u] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_M2P_BYTE(entry->handle->hdlc_header, &(SL_CPC_DRV_UART_PERIPHERAL->TXDATA), SLI_CPC_HDLC_HEADER_RAW_SIZE, 1);
    tx_descriptor[1u] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_M2P_BYTE(entry->handle->data, &(SL_CPC_DRV_UART_PERIPHERAL->TXDATA), DMADRV_MAX_XFER_COUNT, 1u);
    tx_descriptor[2u] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_M2P_BYTE(&((uint8_t *)entry->handle->data)[DMADRV_MAX_XFER_COUNT], &(SL_CPC_DRV_UART_PERIPHERAL->TXDATA), (entry->payload_len - DMADRV_MAX_XFER_COUNT), 1u);
    tx_descriptor[3u] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_M2P_BYTE(entry->handle->fcs, &(SL_CPC_DRV_UART_PERIPHERAL->TXDATA), 2u);
    tx_descriptor[0u].xfer.doneIfs = 0u;
    tx_descriptor[1u].xfer.doneIfs = 0u;
    tx_descriptor[2u].xfer.doneIfs = 0u;
    tx_descriptor[3u].xfer.doneIfs = 1u;
  } else if (entry->payload_len == 0u) {
    tx_descriptor[0u] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_M2P_BYTE(entry->handle->hdlc_header, &(SL_CPC_DRV_UART_PERIPHERAL->TXDATA), SLI_CPC_HDLC_HEADER_RAW_SIZE);
    tx_descriptor[0u].xfer.doneIfs = 1u;
  } else {
    CORE_EXIT_ATOMIC();
    return SL_STATUS_INVALID_PARAMETER;
  }

  tx_ready = false;

  code = DMADRV_LdmaStartTransfer(write_channel,
                                  &tx_config,
                                  tx_descriptor,
                                  NULL,
                                  NULL);
  EFM_ASSERT(code == ECODE_OK);

  CORE_EXIT_ATOMIC();

  return SL_STATUS_OK;
}

/***************************************************************************/ /**
 * Notification when RX buffer becomes free.
 ******************************************************************************/
void sli_cpc_memory_on_rx_buffer_free(void)
{
  sl_status_t status;
  bool resource_allocation_flag = false;
  void *buffer_ptr = NULL;
  LDMA_Descriptor_t *current_desc = NULL;
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_ATOMIC();
  do {
    if (rx_free_no_buf_list_head == NULL) {
      break;
    }

    sli_buf_entry_t *entry = (sli_buf_entry_t *)rx_free_no_buf_list_head;

    status = sli_cpc_get_rx_buffer(&entry->handle);
    if (status == SL_STATUS_OK) {
      (void)sl_slist_pop(&rx_free_no_buf_list_head);
      sli_cpc_push_buffer_handle(&rx_free_list_head, &entry->node, entry->handle);
    }
  } while (status == SL_STATUS_OK && rx_free_no_buf_list_head != NULL);

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == usartHwFlowControlNone_D)
  do {
    current_desc = (LDMA_Descriptor_t *)sli_mem_pool_alloc(&mempool_rx_dma_desc);
    if (current_desc == NULL) {
      break;
    }

    status = sli_cpc_get_raw_rx_buffer(&buffer_ptr);
    if (status != SL_STATUS_OK) {
      sli_mem_pool_free(&mempool_rx_dma_desc, (void *)current_desc);
      break;
    }

    resource_allocation_flag = true;

    push_back_new_rx_dma_desc(current_desc, buffer_ptr);
  } while (true);

  // Start re-synch, if we ran out of DMA descriptor earlier,
  // a descriptor is available to be used and the DMA has been stopped.
  if (rx_need_desc
      && (LDMA->CHEN & (1 << read_channel)) == 0
      && resource_allocation_flag) {
    rx_need_desc = false;
    USART_IntEnable(SL_CPC_DRV_UART_PERIPHERAL, USART_IF_RXDATAV);
  }
#else
  (void)resource_allocation_flag;
  (void)buffer_ptr;
  (void)current_desc;
#endif

  CORE_EXIT_ATOMIC();
}

/***************************************************************************//**
 * RX IRQ handler.
 ******************************************************************************/
void SL_CPC_ISR_RX_HANDLER(SL_CPC_DRV_UART_PERIPHERAL_NO)(void)
{
  uint32_t flag = USART_IntGet(SL_CPC_DRV_UART_PERIPHERAL);

  USART_IntClear(SL_CPC_DRV_UART_PERIPHERAL, flag);

  if (flag & USART_IF_RXDATAV) {
    EFM_ASSERT(header_expected_next == true); // Can't resync when waiting for a payload

    uint8_t data = SL_CPC_DRV_UART_PERIPHERAL->RXDATA;

    if (((rx_synch_byte_cnt < SLI_CPC_HDLC_HEADER_RAW_SIZE)
         && (rx_synch_byte_cnt > 0))
        || (data == SLI_CPC_HDLC_FLAG_VAL)) {
      rx_synch_header[rx_synch_byte_cnt++] = data;
    }

    if (rx_synch_byte_cnt == SLI_CPC_HDLC_HEADER_RAW_SIZE) {
      // Validate HCS
      uint16_t hcs = sli_cpc_hdlc_get_hcs(rx_synch_header);
      if (!sli_cpc_validate_crc_sw(rx_synch_header, SLI_CPC_HDLC_HEADER_SIZE, hcs)) {
        uint8_t i;
        bool valid_byte = false;
        for (i = 1; i < SLI_CPC_HDLC_HEADER_RAW_SIZE; i++) {
          if (rx_synch_header[i] == SLI_CPC_HDLC_FLAG_VAL) {
            memmove(&rx_synch_header[0], &rx_synch_header[i], SLI_CPC_HDLC_HEADER_RAW_SIZE - i);
            valid_byte = true;
            break;
          }
        }

        if (valid_byte) {
          rx_synch_byte_cnt = SLI_CPC_HDLC_HEADER_RAW_SIZE - i;
        } else {
          rx_synch_byte_cnt = 0;
        }

        return;
      }

      rx_synch_byte_cnt = 0;

      USART_IntDisable(SL_CPC_DRV_UART_PERIPHERAL, USART_IF_RXDATAV);

      uint16_t payload_len = sli_cpc_hdlc_get_length(rx_synch_header);

      if (payload_len > 0) {
        header_expected_next = false;
      }

      if (current_rx_entry == NULL) {
        current_rx_entry = (sli_buf_entry_t *)SLI_CPC_POP_BUFFER_HANDLE_LIST(&rx_free_list_head, sli_buf_entry_t);
        if (current_rx_entry == NULL) {
          rx_need_rx_entry = true;
          return;
          // Need to wait for a available buffer and re-synch
        }
      }

      force_current_rx_dma_length(header_expected_next ? SLI_CPC_HDLC_HEADER_RAW_SIZE : payload_len);

      // Copy useful fields of header. Unfortunately with this method the header must always be copied
      // Copy only useful bytes
      ((uint8_t *)current_rx_entry->handle->hdlc_header)[1] = rx_synch_header[1];
      ((uint8_t *)current_rx_entry->handle->hdlc_header)[2] = rx_synch_header[2];
      ((uint8_t *)current_rx_entry->handle->hdlc_header)[3] = rx_synch_header[3];
      ((uint8_t *)current_rx_entry->handle->hdlc_header)[4] = rx_synch_header[4];
      current_rx_entry->handle->data_length = payload_len;

      next_rx_payload_len = payload_len;

      if (payload_len == 0) {
        // Push rx_entry to pending list
        sli_cpc_push_back_buffer_handle(&rx_pending_list_head, &current_rx_entry->node, current_rx_entry->handle);
        // Notify core
        sli_cpc_drv_notify_rx_data();
      }
    }
  }
}

/***************************************************************************//**
 * TX IRQ handler.
 ******************************************************************************/
void SL_CPC_ISR_TX_HANDLER(SL_CPC_DRV_UART_PERIPHERAL_NO)(void)
{
  CORE_DECLARE_IRQ_STATE;

  uint32_t flag = USART_IntGet(SL_CPC_DRV_UART_PERIPHERAL);

  USART_IntClear(SL_CPC_DRV_UART_PERIPHERAL, flag);

  if (flag & USART_IF_TXC) {
    DMADRV_StopTransfer(write_channel);

    tx_ready = true;

    sli_buf_entry_t *entry;

    CORE_ENTER_ATOMIC();
    entry = (sli_buf_entry_t *)SLI_CPC_POP_BUFFER_HANDLE_LIST(&tx_submitted_list_head, sli_buf_entry_t);
    CORE_EXIT_ATOMIC();

    // Notify core
    sli_cpc_drv_notify_tx_complete(entry->handle);

    CORE_ENTER_ATOMIC();
    sl_slist_push(&tx_free_list_head, &entry->node);

    if (tx_submitted_list_head) {
      (void)prepare_next_tx();
    }

    CORE_EXIT_ATOMIC();
  }
}

/***************************************************************************/ /**
 * Rx DMA xfer completed. Need to determine what was received and update the
 * XferCnt of the current DMA xfer ASAP.
 ******************************************************************************/
static bool rx_dma_complete(unsigned int channel,
                            unsigned int sequenceNo,
                            void *userParam)
{
  LDMA_Descriptor_t *completed_desc = rx_descriptor_head;
  uint8_t *rx_buffer = (uint8_t *)(completed_desc->xfer.dstAddr);
  uint16_t current_rx_buffer_offset = 0;
  uint16_t current_rx_buf_tot_len = next_rx_buf_tot_len;
  bool rx_buf_free = true;

  (void)channel;
  (void)sequenceNo;
  (void)userParam;

  EFM_ASSERT(completed_desc != NULL);

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == usartHwFlowControlNone_D)
  rx_descriptor_head = (LDMA_Descriptor_t *)(uint32_t)(rx_descriptor_head->xfer.linkAddr << _LDMA_CH_LINK_LINKADDR_SHIFT);
#endif

  if (rx_descriptor_head == NULL) {
    rx_need_desc = true;
    rx_descriptor_tail = NULL;
  }

  while (current_rx_buf_tot_len > 0) {
    uint8_t *current_rx_buffer = &rx_buffer[current_rx_buffer_offset];

    if (header_expected_next) {
      uint16_t hcs;

      current_rx_buf_tot_len -= SLI_CPC_HDLC_HEADER_RAW_SIZE;

      current_rx_entry = (sli_buf_entry_t *)SLI_CPC_POP_BUFFER_HANDLE_LIST(&rx_free_list_head, sli_buf_entry_t);
      if (current_rx_entry == NULL) {
        rx_need_rx_entry = true;
        DMADRV_StopTransfer(read_channel);
        return false;
      }

      // Validate HCS
      hcs = sli_cpc_hdlc_get_hcs(current_rx_buffer);
      if (!sli_cpc_validate_crc_sw(current_rx_buffer, SLI_CPC_HDLC_HEADER_SIZE, hcs)) {
        DMADRV_StopTransfer(read_channel);

        uint16_t already_recvd_cnt;
        uint32_t dest = LDMA->CH[read_channel].DST;
        uint32_t ctrl;

        // Rewind the DMA destination to discard previously received bytes
        ctrl = LDMA->CH[read_channel].CTRL;
        dest = LDMA->CH[read_channel].DST;
        already_recvd_cnt = (((SLI_CPC_RX_DATA_MAX_LENGTH < DMA_MAX_XFER_LEN) ? SLI_CPC_RX_DATA_MAX_LENGTH : DMA_MAX_XFER_LEN) - 1) - ((ctrl & _LDMA_CH_CTRL_XFERCNT_MASK) >> _LDMA_CH_CTRL_XFERCNT_SHIFT);
        LDMA->CH[read_channel].DST = (dest - already_recvd_cnt);
        USART_IntEnable(SL_CPC_DRV_UART_PERIPHERAL, USART_IF_RXDATAV);
        SLI_CPC_DEBUG_TRACE_CORE_DRIVER_PACKET_DROPPED();
        SLI_CPC_DEBUG_TRACE_CORE_INVALID_HEADER_CHECKSUM();
        break;
      }

      next_rx_payload_len = sli_cpc_hdlc_get_length(current_rx_buffer);

      if (rx_need_desc
          && next_rx_payload_len > 0) {
        DMADRV_StopTransfer(read_channel);

        rx_descriptor_head = completed_desc;
        rx_descriptor_tail = completed_desc;

        // Rewind rx buffer to re-use it
        uint32_t dest = LDMA->CH[read_channel].DST;
        LDMA->CH[read_channel].DST = (dest - SLI_CPC_HDLC_HEADER_RAW_SIZE);

        USART_IntEnable(SL_CPC_DRV_UART_PERIPHERAL, USART_IF_RXDATAV);
        return false;
      }

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == usartHwFlowControlCtsAndRts_D)
      if (next_rx_payload_len > 0) {
        (void)update_current_rx_dma_length(next_rx_payload_len);
      } else {
        (void)update_current_rx_dma_length(SLI_CPC_HDLC_HEADER_RAW_SIZE);
      }
      (void)rx_buf_free;
#else
      if (current_rx_buf_tot_len == 0) {
        bool update_success = false;

        if ((next_rx_payload_len > 0)
            && (next_rx_payload_len <= DMA_MAX_XFER_LEN)) {
          update_success = update_current_rx_dma_length(next_rx_payload_len);
          if (!update_success) {
            // If we fall here, it's because we received more than the expected payload.
            // In that case, we need to re-synch on the next valid header.
            update_success = update_current_rx_dma_length(next_rx_payload_len + SLI_CPC_HDLC_HEADER_RAW_SIZE);
          }
        } else if ((next_rx_payload_len > 0)
                   && (next_rx_payload_len > DMA_MAX_XFER_LEN)
                   && (next_rx_payload_len <= SLI_CPC_RX_DATA_MAX_LENGTH)) {
          update_success = update_current_rx_dma_large_payload_length(next_rx_payload_len);
        } else if (!rx_need_desc) {
          update_success = update_current_rx_dma_length(SLI_CPC_HDLC_HEADER_RAW_SIZE);
        }

        if (!update_success) {
          start_re_synch();
          return false;
        }
      }
#endif

      // Copy useful fields of header. Unfortunately with this method the header must always be copied
      // Copy only useful bytes
      ((uint8_t *)current_rx_entry->handle->hdlc_header)[1] = current_rx_buffer[1];
      ((uint8_t *)current_rx_entry->handle->hdlc_header)[2] = current_rx_buffer[2];
      ((uint8_t *)current_rx_entry->handle->hdlc_header)[3] = current_rx_buffer[3];
      ((uint8_t *)current_rx_entry->handle->hdlc_header)[4] = current_rx_buffer[4];
      current_rx_entry->handle->data_length = next_rx_payload_len;

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == usartHwFlowControlCtsAndRts_D)
      sli_cpc_free_raw_rx_buffer(current_rx_buffer);
#endif

      if (next_rx_payload_len > SLI_CPC_RX_DATA_MAX_LENGTH) {
        SLI_CPC_DEBUG_TRACE_CORE_DRIVER_PACKET_DROPPED();
        notify_core_error(SL_CPC_REJECT_ERROR);
        current_rx_entry = NULL;
      } else if (next_rx_payload_len == 0) { // A header is expected next
        // Push rx_entry to pending list
        sli_cpc_push_back_buffer_handle(&rx_pending_list_head, &current_rx_entry->node, current_rx_entry->handle);

        // Notify core
        sli_cpc_drv_notify_rx_data();

        current_rx_entry = NULL;
      } else { // A payload is expected next
        header_expected_next = false;
      }

      current_rx_buffer_offset += SLI_CPC_HDLC_HEADER_RAW_SIZE;
    } else {
      current_rx_buf_tot_len -= next_rx_payload_len;

      if (current_rx_buf_tot_len == 0
          && !rx_need_desc) {
        bool update_success;

        update_success = update_current_rx_dma_length(SLI_CPC_HDLC_HEADER_RAW_SIZE);
        if (!update_success) {
          start_re_synch();
          return false;
        }
      }

      // Add to current rx handle
      EFM_ASSERT(current_rx_entry != NULL);

      if (current_rx_buffer_offset) {
        // With the current implementation limitations, we should never get here.
        memmove(rx_buffer, current_rx_buffer, next_rx_payload_len);
      }

      current_rx_entry->handle->data = rx_buffer;
      current_rx_entry->handle->data_length = next_rx_payload_len;

      // A header is expected next
      header_expected_next = true;

      // Notify core
      sli_cpc_push_back_buffer_handle(&rx_pending_list_head, &current_rx_entry->node, current_rx_entry->handle);
      sli_cpc_drv_notify_rx_data();

      current_rx_buffer_offset += next_rx_payload_len;

      // If we ended here, it means the rx_buffer was pushed to the app.
      rx_buf_free = false;
      next_rx_payload_len = 0;
    }
  }

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == usartHwFlowControlNone_D)
  if (rx_buf_free) {
    // We end up in that case when we received a header. Since the buffer has not
    // been pushed to the core, we can re-use it right away.

    push_back_new_rx_dma_desc(completed_desc, rx_buffer);
  } else {
    LDMA_Descriptor_t *desc = (LDMA_Descriptor_t *)(completed_desc->xfer.linkAddr << _LDMA_CH_LINK_LINKADDR_SHIFT);
    sli_mem_pool_free(&mempool_rx_dma_desc, (void *)completed_desc);

    for (uint16_t i = 1u; i < nb_desc_free; i++) {
      LDMA_Descriptor_t *temp_desc = desc;
      sli_mem_pool_free(&mempool_rx_dma_desc, (void *)desc);
      desc = (LDMA_Descriptor_t *)(temp_desc->xfer.linkAddr << _LDMA_CH_LINK_LINKADDR_SHIFT);
      rx_descriptor_head = desc;
    }

    nb_desc_free = 0u;
    rx_buffer_free_from_isr();
  }
#endif
  return false;
}

/***************************************************************************/ /**
 * Force a new XferCnt of the current DMA xfer with the length passed as argument.
 * This function also restart the DMA transfer.
 *
 * @param new_length Total length of next transfer.
 *
 * @return true if new length successfully applied.
 *         false if the DMA already transferred more than requested.
 ******************************************************************************/
static void force_current_rx_dma_length(uint16_t new_length)
{
  uint32_t ctrl;
  uint32_t dest;
  uint16_t already_recvd_cnt;

  ctrl = LDMA->CH[read_channel].CTRL;

  // Rewind the DMA destination to discard previously received bytes
  dest = LDMA->CH[read_channel].DST;
  already_recvd_cnt = (((SLI_CPC_RX_DATA_MAX_LENGTH < DMA_MAX_XFER_LEN) ? SLI_CPC_RX_DATA_MAX_LENGTH : DMA_MAX_XFER_LEN) - 1) - ((ctrl & _LDMA_CH_CTRL_XFERCNT_MASK) >> _LDMA_CH_CTRL_XFERCNT_SHIFT);
  LDMA->CH[read_channel].DST = (dest - already_recvd_cnt);

  ctrl &= ~_LDMA_CH_CTRL_XFERCNT_MASK;
  ctrl |= ((new_length - 1) << _LDMA_CH_CTRL_XFERCNT_SHIFT) & _LDMA_CH_CTRL_XFERCNT_MASK;

  LDMA->CH[read_channel].CTRL = ctrl;

#if defined(_LDMA_CHDIS_MASK)
  LDMA->CHDIS |= (1 << read_channel);
#else
  LDMA->IEN |= (1 << read_channel);
#endif

  LDMA->CHEN |= (1 << read_channel);

  next_rx_buf_tot_len = new_length;
}

/***************************************************************************/ /**
 * Update XferCnt of the current DMA xfer with the length passed as argument.
 *
 * @param new_length Total length of next transfer.
 *
 * @return true if new length successfully applied.
 *         false if the DMA already transferred more than requested.
 ******************************************************************************/
static bool update_current_rx_dma_length(uint16_t new_length)
{
#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == usartHwFlowControlCtsAndRts_D)
  Ecode_t ecode;
  void *buffer_ptr;
  sl_status_t status;

  status = sli_cpc_get_raw_rx_buffer(&buffer_ptr);
  EFM_ASSERT(status == SL_STATUS_OK);

  if (new_length <= DMA_MAX_XFER_LEN) {
    rx_descriptor[0u] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(&(SL_CPC_DRV_UART_PERIPHERAL->RXDATA), buffer_ptr, new_length);
  } else {
    rx_descriptor[0u] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_P2M_BYTE(&(SL_CPC_DRV_UART_PERIPHERAL->RXDATA), buffer_ptr, DMA_MAX_XFER_LEN, 1u);
    rx_descriptor[1u] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(&(SL_CPC_DRV_UART_PERIPHERAL->RXDATA), &((uint8_t *)buffer_ptr)[DMA_MAX_XFER_LEN], (new_length - DMA_MAX_XFER_LEN));
    rx_descriptor[0u].xfer.doneIfs = 0u;
    rx_descriptor[1u].xfer.doneIfs = 1u;
  }

  rx_descriptor_head = rx_descriptor;
  next_rx_buf_tot_len = new_length;

  // Start read channel
  ecode = DMADRV_LdmaStartTransfer(read_channel,
                                   &rx_config,
                                   rx_descriptor_head,
                                   rx_dma_complete,
                                   0);
  EFM_ASSERT(ecode == ECODE_OK);
#else
  uint32_t ctrl;
  uint16_t already_recvd_cnt;
  uint16_t remaining;

  // Adjust current dma xfer with new_length
  // Note this proof of concept does not support large buffers (buffer larger than the maximum supported by the LDMA)

  // For safety we momentarily pause the DMA. If we are afraid of suspending
  // it for too long and loosing bytes, we could use a critical section to make
  // sure there are not higher priority interrupt until we resume it.
  DMADRV_PauseTransfer(read_channel);

  ctrl = LDMA->CH[read_channel].CTRL;
  already_recvd_cnt = (((SLI_CPC_RX_DATA_MAX_LENGTH < DMA_MAX_XFER_LEN) ? SLI_CPC_RX_DATA_MAX_LENGTH : DMA_MAX_XFER_LEN) - 1) - ((ctrl & _LDMA_CH_CTRL_XFERCNT_MASK) >> _LDMA_CH_CTRL_XFERCNT_SHIFT);

  // For analysis purposes
  if (already_recvd_cnt > already_recvd_cnt_worst) {
    already_recvd_cnt_worst = already_recvd_cnt;
  }

  if (already_recvd_cnt >= new_length) {
    // Here we failed to update current DMA xfer on time.
    DMADRV_ResumeTransfer(read_channel);
    return false;
  }

  remaining = new_length - already_recvd_cnt;

  ctrl &= ~_LDMA_CH_CTRL_XFERCNT_MASK;
  ctrl |= ((remaining - 1) << _LDMA_CH_CTRL_XFERCNT_SHIFT) & _LDMA_CH_CTRL_XFERCNT_MASK;

  LDMA->CH[read_channel].CTRL = ctrl;

  DMADRV_ResumeTransfer(read_channel);

  next_rx_buf_tot_len = new_length;
#endif

  return true;
}

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == usartHwFlowControlNone_D)
/***************************************************************************/ /**
 * Update XferCnt of the current DMA xfer with the length passed as argument.
 *
 * @param new_length Total length of next transfer.
 *
 * @return true if new length successfully applied.
 *         false if the DMA already transferred more than requested.
 ******************************************************************************/
static bool update_current_rx_dma_large_payload_length(uint16_t new_length)
{
  LDMA_Descriptor_t *desc;
  LDMA_Descriptor_t *temp_desc;

  // Adjust current dma xfer with new_length
  // For safety we momentarily pause the DMA. If we are afraid of suspending
  // it for too long and loosing bytes, we could use a critical section to make
  // sure there are not higher priority interrupt until we resume it.

  DMADRV_PauseTransfer(read_channel);

  uint32_t *dst_addr;
  uint8_t desc_cnt = 0u;
  uint8_t nb_desc = new_length / DMA_MAX_XFER_LEN;
  desc = rx_descriptor_head;
  temp_desc = rx_descriptor_head;
  dst_addr = (uint32_t *)LDMA->CH[read_channel].DST;

#ifdef _LDMA_CH_CTRL_DONEIFSEN_MASK
  LDMA->CH[read_channel].CTRL &= ~_LDMA_CH_CTRL_DONEIFSEN_MASK;
#else
  LDMA->CH[read_channel].CTRL &= ~_LDMA_CH_CTRL_DONEIEN_MASK;
#endif

  // Check if there enough RX descriptor available
  for (desc_cnt = 0; temp_desc != NULL; desc_cnt++) {
    if (desc_cnt == nb_desc) {
      break;
    }
    temp_desc = (LDMA_Descriptor_t *)(temp_desc->xfer.linkAddr << _LDMA_CH_LINK_LINKADDR_SHIFT);
  }

  if (desc_cnt < nb_desc) {
    DMADRV_ResumeTransfer(read_channel);
    return false;
  }

  desc_cnt = 0u;

  while (desc_cnt < nb_desc) {
    desc->xfer.doneIfs = 0u;
    desc->xfer.xferCnt = (DMA_MAX_XFER_LEN - 1u);

    if (desc_cnt >= 1u) {
      sl_cpc_free_rx_buffer((void *)desc->xfer.dstAddr);
    }

    desc->xfer.dstAddr = ((uint32_t)&dst_addr[(desc_cnt * DMA_MAX_XFER_LEN) / 4u]);
    desc = (LDMA_Descriptor_t *)(desc->xfer.linkAddr << _LDMA_CH_LINK_LINKADDR_SHIFT);
    desc_cnt++;
  }

  if (desc == NULL) {
    DMADRV_ResumeTransfer(read_channel);
    return false;
  }

  sl_cpc_free_rx_buffer((void *)desc->xfer.dstAddr);

  desc->xfer.doneIfs = 1u;
  desc->xfer.xferCnt = (new_length % DMA_MAX_XFER_LEN) - 1u;
  desc->xfer.dstAddr = ((uint32_t)&dst_addr[(desc_cnt * DMA_MAX_XFER_LEN) / 4u]);

  if ((new_length % DMA_MAX_XFER_LEN) != 0u) {
    nb_desc_free = nb_desc + 1u;
  } else {
    nb_desc_free = nb_desc;
  }

  DMADRV_ResumeTransfer(read_channel);

  next_rx_buf_tot_len = new_length;

  return true;
}
#endif

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == usartHwFlowControlNone_D)
/***************************************************************************/ /**
 * Update dma desccriptor link absolute address.
 *
 * @param current_dma_desc DMA descriptor to update.
 *
 * @param next_dma_desc DMA descriptor to link to.
 ******************************************************************************/
static void update_dma_desc_link_abs(LDMA_Descriptor_t *current_dma_desc,
                                     LDMA_Descriptor_t *next_dma_desc)
{
  uint32_t link = 0;
  uint32_t *current_dma_buffer = (uint32_t *)current_dma_desc;

  link = (uint32_t)next_dma_desc;
  link |= ldmaLinkModeAbs;
  link |= 1 << 1;

  current_dma_buffer[3] = link;
}

/***************************************************************************/ /**
 * Configure and link a new dma desccriptor to another dma descriptor.
 *
 * @param new_dma_desc DMA descriptor to configure and link to.
 *
 * @param buffer Destination buffer for new_dma_desc.
 ******************************************************************************/
static void push_back_new_rx_dma_desc(LDMA_Descriptor_t *new_dma_desc,
                                      void *buffer)
{
  *new_dma_desc = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(&(SL_CPC_DRV_UART_PERIPHERAL->RXDATA), buffer, (SLI_CPC_RX_DATA_MAX_LENGTH < DMA_MAX_XFER_LEN) ? SLI_CPC_RX_DATA_MAX_LENGTH : DMA_MAX_XFER_LEN);
  new_dma_desc->xfer.doneIfs = 1u;

  if (rx_descriptor_tail == NULL) {
    rx_descriptor_head = new_dma_desc;
  } else {
    update_dma_desc_link_abs(rx_descriptor_tail, new_dma_desc);
  }

  rx_descriptor_tail = new_dma_desc;

  if ((LDMA->CHEN & (1 << read_channel)) == 0) {
    return;
  }

  DMADRV_PauseTransfer(read_channel);
  if (LDMA->CH[read_channel].LINK == 0) {
    LDMA->CH[read_channel].LINK = (uint32_t)new_dma_desc | (1 << 1);
  }
  DMADRV_ResumeTransfer(read_channel);
}

/***************************************************************************/ /**
 * Allocate RX buffer and descriptor from ISR.
 ******************************************************************************/
static void rx_buffer_free_from_isr(void)
{
  sl_status_t status;
  void *buffer_ptr = NULL;
  LDMA_Descriptor_t *current_desc = NULL;

  do {
    current_desc = (LDMA_Descriptor_t *)sli_mem_pool_alloc(&mempool_rx_dma_desc);
    if (current_desc == NULL) {
      break;
    }

    status = sli_cpc_get_raw_rx_buffer(&buffer_ptr);
    if (status != SL_STATUS_OK) {
      sli_mem_pool_free(&mempool_rx_dma_desc, (void *)current_desc);
      break;
    }
    push_back_new_rx_dma_desc(current_desc, buffer_ptr);
  } while (true);
}
#endif

/***************************************************************************/ /**
 * Send a reject notification to CPC core.
 *
 * @param reason Reject reason.
 ******************************************************************************/
static void notify_core_error(sl_cpc_reject_reason_t reason)
{
  current_rx_entry->handle->reason = reason;

  // Push rx_entry to pending list
  sli_cpc_push_back_buffer_handle(&rx_pending_list_head, &current_rx_entry->node, current_rx_entry->handle);

  // Notify core
  sli_cpc_drv_notify_rx_data();
}

/***************************************************************************/ /**
 * Stop DMA mode and start receiving bytes in interrupt mode.
 ******************************************************************************/
static void start_re_synch(void)
{
  DMADRV_StopTransfer(read_channel);

  SLI_CPC_DEBUG_TRACE_CORE_DRIVER_PACKET_DROPPED();

  // A header is expected next
  header_expected_next = true;

  sli_cpc_push_back_buffer_handle(&rx_free_list_head, &current_rx_entry->node, current_rx_entry->handle);
  current_rx_entry = NULL;
  USART_IntEnable(SL_CPC_DRV_UART_PERIPHERAL, USART_IF_RXDATAV);
}
