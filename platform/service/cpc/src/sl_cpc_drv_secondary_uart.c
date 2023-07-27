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

#include "ecode.h"
#include "sl_sleeptimer.h"
#include "sli_cpc_system_common.h"

#include "em_core.h"
#include "sl_assert.h"
#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#include "sl_cpc_drv_secondary_uart_config.h"
#if defined(SL_CPC_DRV_PERIPH_IS_EUSART)
#include "em_eusart.h"
#else
#include "em_usart.h"
#endif

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
#include "sli_cpc.h"

/*******************************************************************************
 ********************************   DATATYPE   *********************************
 ******************************************************************************/
typedef struct {
  sl_slist_node_t node;
  sl_cpc_buffer_handle_t *handle;
  uint16_t payload_len;
} sli_buf_entry_t;

/*******************************************************************************
 *********************************   DEFINES   *********************************
 ******************************************************************************/
#define SL_CPC_CONCAT_PASTER(first, second, third)  first ##  second ## third
#define SL_CPC_PERIPH_CLOCK(first, second)  first ##  second

#if defined(SL_CPC_DRV_PERIPH_IS_EUSART)
#define WITH_HWFC eusartHwFlowControlCtsAndRts_D
#define WITHOUT_HWFC eusartHwFlowControlNone_D

#if defined(EUART_COUNT) && (EUART_COUNT > 0)
#define SL_CPC_UART_CLOCK(periph)                  SL_CPC_PERIPH_CLOCK(cmuClock_EUART, periph)
#define SL_CPC_TX_IRQn(periph_nbr)                 SL_CPC_CONCAT_PASTER(EUART, periph_nbr, _TX_IRQn)
#define SL_CPC_ISR_TX_HANDLER(periph_nbr)          SL_CPC_CONCAT_PASTER(EUART, periph_nbr, _TX_IRQHandler)
#else
#define SL_CPC_UART_CLOCK(periph)                  SL_CPC_PERIPH_CLOCK(cmuClock_EUSART, periph)
#define SL_CPC_TX_IRQn(periph_nbr)                 SL_CPC_CONCAT_PASTER(EUSART, periph_nbr, _TX_IRQn)
#define SL_CPC_ISR_TX_HANDLER(periph_nbr)          SL_CPC_CONCAT_PASTER(EUSART, periph_nbr, _TX_IRQHandler)
#endif

#if defined(EUART_COUNT) && (EUART_COUNT > 0)
#define SL_CPC_LDMA_RX_PERIPH_TRIGGER(periph_nbr)   SL_CPC_CONCAT_PASTER(ldmaPeripheralSignal_EUART, periph_nbr, _RXFL)
#define SL_CPC_LDMA_TX_PERIPH_TRIGGER(periph_nbr)   SL_CPC_CONCAT_PASTER(ldmaPeripheralSignal_EUART, periph_nbr, _TXFL)
#else
#define SL_CPC_LDMA_RX_PERIPH_TRIGGER(periph_nbr)   SL_CPC_CONCAT_PASTER(ldmaPeripheralSignal_EUSART, periph_nbr, _RXFL)
#define SL_CPC_LDMA_TX_PERIPH_TRIGGER(periph_nbr)   SL_CPC_CONCAT_PASTER(ldmaPeripheralSignal_EUSART, periph_nbr, _TXFL)
#endif

#else
#define WITH_HWFC usartHwFlowControlCtsAndRts_D
#define WITHOUT_HWFC usartHwFlowControlNone_D

#define SL_CPC_USART_CLOCK(periph)                 SL_CPC_PERIPH_CLOCK(cmuClock_USART, periph)
#define SL_CPC_TX_IRQn(periph_nbr)                 SL_CPC_CONCAT_PASTER(USART, periph_nbr, _TX_IRQn)
#define SL_CPC_ISR_TX_HANDLER(periph_nbr)          SL_CPC_CONCAT_PASTER(USART, periph_nbr, _TX_IRQHandler)

#define SL_CPC_LDMA_RX_PERIPH_TRIGGER(periph_nbr)   SL_CPC_CONCAT_PASTER(ldmaPeripheralSignal_USART, periph_nbr, _RXDATAV)
#define SL_CPC_LDMA_TX_PERIPH_TRIGGER(periph_nbr)   SL_CPC_CONCAT_PASTER(ldmaPeripheralSignal_USART, periph_nbr, _TXBL)
#endif

/// Maximum length of one LDMA transfer.
#define DMA_MAX_XFER_LEN (((_LDMA_CH_CTRL_XFERCNT_MASK >> _LDMA_CH_CTRL_XFERCNT_SHIFT) + 1))
#define RX_DMA_DESCRIPTOR_QTY      (2)

#if ((SLI_CPC_RX_DATA_MAX_LENGTH > 2048) \
  && (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITHOUT_HWFC))
#error  Buffer larger than 2048 bytes without Hardware Flow Control is not supported
#endif

#if (SL_CPC_DRV_UART_RX_QUEUE_SIZE > SL_CPC_RX_BUFFER_MAX_COUNT)
#error  Invalid configuration SL_CPC_RX_BUFFER_MAX_COUNT must be greater than SL_CPC_DRV_UART_RX_QUEUE_SIZE
#endif

#define SL_CPC_DRV_UART_RX_MAX_BUFFER_SIZE (SL_MIN(SLI_CPC_RX_FRAME_MAX_LENGTH, DMA_MAX_XFER_LEN))

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
static unsigned int read_channel;
static unsigned int write_channel;

static LDMA_TransferCfg_t rx_config;
static LDMA_TransferCfg_t tx_config;

static LDMA_Descriptor_t rx_descriptor[RX_DMA_DESCRIPTOR_QTY];

static LDMA_Descriptor_t *rx_descriptor_head = NULL;

#if (SL_CPC_ENDPOINT_SECURITY_ENABLED >= 1)
/* An extra DMA descriptor is needed for the security tag */
static LDMA_Descriptor_t tx_descriptor[5u];
#else
static LDMA_Descriptor_t tx_descriptor[4u];
#endif

static sl_slist_node_t *rx_free_list_head;
static sl_slist_node_t *rx_free_no_buffer_handle_list_head;
static sl_slist_node_t *rx_pending_list_head;

static sl_slist_node_t *tx_free_list_head;
static sl_slist_node_t *tx_submitted_list_head;
static sl_slist_node_t *tx_complete_list_head;

static sli_buf_entry_t rx_buf_entries_tbl[SL_CPC_DRV_UART_RX_QUEUE_SIZE];
static sli_buf_entry_t tx_buf_entries_tbl[SL_CPC_DRV_UART_TX_QUEUE_SIZE];

static bool tx_ready = true;

static uint16_t next_rx_size = 0;
static bool header_expected_next = true;
static bool need_rx_buffer = false;
static bool rx_need_rx_entry = false;

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITHOUT_HWFC)
static struct {
  uint8_t *spilled_buffer;
  void *active_buffer;
  bool out_of_sync;
  uint16_t offset;
  sli_buf_entry_t* entry;
  uint16_t recovered_payloads;
  bool misaligned_payload;
  bool recovery_completed;
  uint8_t invalid_hdlc_header[SLI_CPC_HDLC_HEADER_RAW_SIZE];
  uint8_t hdlc_header_out_of_sync_sliding_window[SLI_CPC_HDLC_HEADER_RAW_SIZE * 2];
  uint8_t out_of_sync_extra_bytes[SLI_CPC_HDLC_HEADER_RAW_SIZE];
  uint8_t out_of_sync_extra_bytes_len;
} recovery_context;

static sl_cpc_dispatcher_handle_t recovery_dispatcher_handle;
#endif

static sl_cpc_dispatcher_handle_t dispatcher_handle;

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/

static sl_status_t prepare_next_tx(void);

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITHOUT_HWFC)
static sl_status_t resize_current_dma_descriptor(uint16_t new_length);

static bool rx_dma_complete_no_hwfc(unsigned int channel,
                                    unsigned int sequenceNo,
                                    void *userParam);

static void recovery(void *data);

static void swap_descriptors(void);

static void update_dma_desc_link_abs(LDMA_Descriptor_t *current_dma_desc,
                                     LDMA_Descriptor_t *next_dma_desc,
                                     bool enable_link);

#else
static void resize_current_dma_descriptor(void *pre_loaded_rx_buffer, uint16_t offset, uint16_t new_length);

static bool rx_dma_complete_hwfc(unsigned int channel,
                                 unsigned int sequenceNo,
                                 void *userParam);
#endif

static void notify_core_error(sli_buf_entry_t * entry, sl_cpc_reject_reason_t reason);

static void restart_dma(void);
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

  // Enable peripheral clocks
#if defined(_CMU_HFPERCLKEN0_MASK)
  CMU_ClockEnable(cmuClock_HFPER, true);
#endif

  CMU_ClockEnable(cmuClock_GPIO, true);

#if defined(SL_CPC_DRV_PERIPH_IS_EUSART)
  CMU_ClockEnable(SL_CPC_UART_CLOCK(SL_CPC_DRV_UART_PERIPHERAL_NO), true);
  #if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2) \
  || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_7)
  CMU_ClockEnable(cmuClock_EM01GRPACLK, true);
#if defined(EUART_PRESENT)
  if (SL_CPC_UART_CLOCK(SL_CPC_DRV_UART_PERIPHERAL_NO) == cmuClock_EUART0) {
    CMU_CLOCK_SELECT_SET(EUART0CLK, EM01GRPACLK);
  }
#elif defined(EUSART_PRESENT)
  if (SL_CPC_UART_CLOCK(SL_CPC_DRV_UART_PERIPHERAL_NO) == cmuClock_EUSART0) {
    CMU_CLOCK_SELECT_SET(EUSART0CLK, EM01GRPACLK);
  }
#endif
#elif (_SILICON_LABS_32B_SERIES_2_CONFIG >= 3)
  CMU_CLOCK_SELECT_SET(EM01GRPCCLK, HFRCODPLL);
  if (SL_CPC_UART_CLOCK(SL_CPC_DRV_UART_PERIPHERAL_NO) == cmuClock_EUSART0) {
    CMU_CLOCK_SELECT_SET(EUSART0CLK, EM01GRPCCLK);
  }
#else
  EFM_ASSERT(false);
  return SL_STATUS_NOT_SUPPORTED;
#endif

#else
  CMU_ClockEnable(SL_CPC_USART_CLOCK(SL_CPC_DRV_UART_PERIPHERAL_NO), true);
#endif

  NVIC_EnableIRQ(SL_CPC_TX_IRQn(SL_CPC_DRV_UART_PERIPHERAL_NO));

  sl_slist_init(&rx_free_list_head);
  sl_slist_init(&rx_free_no_buffer_handle_list_head);
  sl_slist_init(&rx_pending_list_head);
  sl_slist_init(&tx_free_list_head);
  sl_slist_init(&tx_submitted_list_head);
  sl_slist_init(&tx_complete_list_head);

  sli_cpc_dispatcher_init_handle(&dispatcher_handle);

  for (buf_cnt = 0; buf_cnt < SL_CPC_DRV_UART_RX_QUEUE_SIZE; buf_cnt++) {
    sli_buf_entry_t *entry = &rx_buf_entries_tbl[buf_cnt];
    if (sli_cpc_get_buffer_handle_for_rx(&entry->handle) != SL_STATUS_OK) {
      EFM_ASSERT(false);
      return SL_STATUS_ALLOCATION_FAILED;
    }
    sli_cpc_push_buffer_handle(&rx_free_list_head, &entry->node, entry->handle);
  }

  for (buf_cnt = 0; buf_cnt < SL_CPC_DRV_UART_TX_QUEUE_SIZE; buf_cnt++) {
    sli_buf_entry_t *entry = &tx_buf_entries_tbl[buf_cnt];
    sl_slist_push(&tx_free_list_head, &entry->node);
  }

  // Configure TX and RX GPIOs
  GPIO_PinModeSet(SL_CPC_DRV_UART_TX_PORT, SL_CPC_DRV_UART_TX_PIN, gpioModePushPull, 1);
  GPIO_PinModeSet(SL_CPC_DRV_UART_RX_PORT, SL_CPC_DRV_UART_RX_PIN, gpioModeInputPull, 1);

#if defined(SL_CPC_DRV_PERIPH_IS_EUSART)
  EUSART_UartInit_TypeDef init = EUSART_UART_INIT_DEFAULT_HF;
  EUSART_AdvancedInit_TypeDef advancedSettings = EUSART_ADVANCED_INIT_DEFAULT;
  init.enable = eusartEnable;
#else
  USART_InitAsync_TypeDef init = USART_INITASYNC_DEFAULT;
  init.enable = usartDisable;
#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITHOUT_HWFC)
  init.hwFlowControl = (USART_HwFlowControl_TypeDef)WITHOUT_HWFC;
#elif (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITH_HWFC)
  init.hwFlowControl = (USART_HwFlowControl_TypeDef)WITH_HWFC;
#endif
#endif

  init.baudrate = SL_CPC_DRV_UART_BAUDRATE;

#if defined(SL_CPC_DRV_PERIPH_IS_EUSART)

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITHOUT_HWFC)
  advancedSettings.hwFlowControl = eusartHwFlowControlNone;
#elif (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITH_HWFC)
  advancedSettings.hwFlowControl = eusartHwFlowControlCtsAndRts;
#endif

  init.advancedSettings = &advancedSettings;
  init.baudrate = SL_CPC_DRV_UART_BAUDRATE;

#if defined(EUART_COUNT) && (EUART_COUNT > 0)
  GPIO->EUARTROUTE->ROUTEEN = GPIO_EUART_ROUTEEN_TXPEN;
  GPIO->EUARTROUTE->TXROUTE = (SL_CPC_DRV_UART_TX_PORT << _GPIO_EUART_TXROUTE_PORT_SHIFT)
                              | (SL_CPC_DRV_UART_TX_PIN << _GPIO_EUART_TXROUTE_PIN_SHIFT);
  GPIO->EUARTROUTE->RXROUTE = (SL_CPC_DRV_UART_RX_PORT << _GPIO_EUART_RXROUTE_PORT_SHIFT)
                              | (SL_CPC_DRV_UART_RX_PIN << _GPIO_EUART_RXROUTE_PIN_SHIFT);
#else
  GPIO->EUSARTROUTE[SL_CPC_DRV_UART_PERIPHERAL_NO].ROUTEEN = GPIO_EUSART_ROUTEEN_TXPEN;
  GPIO->EUSARTROUTE[SL_CPC_DRV_UART_PERIPHERAL_NO].TXROUTE =
    (SL_CPC_DRV_UART_TX_PORT << _GPIO_EUSART_TXROUTE_PORT_SHIFT)
    | (SL_CPC_DRV_UART_TX_PIN << _GPIO_EUSART_TXROUTE_PIN_SHIFT);
  GPIO->EUSARTROUTE[SL_CPC_DRV_UART_PERIPHERAL_NO].RXROUTE =
    (SL_CPC_DRV_UART_RX_PORT << _GPIO_EUSART_RXROUTE_PORT_SHIFT)
    | (SL_CPC_DRV_UART_RX_PIN << _GPIO_EUSART_RXROUTE_PIN_SHIFT);
#endif

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITH_HWFC)
  GPIO_PinModeSet(SL_CPC_DRV_UART_CTS_PORT, SL_CPC_DRV_UART_CTS_PIN, gpioModeInputPull, 0);
#if defined(EUART_COUNT) && (EUART_COUNT > 0)
  GPIO->EUARTROUTE_SET->CTSROUTE = (SL_CPC_DRV_UART_CTS_PORT << _GPIO_EUART_CTSROUTE_PORT_SHIFT)
                                   | (SL_CPC_DRV_UART_CTS_PIN << _GPIO_EUART_CTSROUTE_PIN_SHIFT);
#else
  GPIO->EUSARTROUTE_SET[SL_CPC_DRV_UART_PERIPHERAL_NO].CTSROUTE =
    (SL_CPC_DRV_UART_CTS_PORT << _GPIO_EUSART_CTSROUTE_PORT_SHIFT)
    | (SL_CPC_DRV_UART_CTS_PIN << _GPIO_EUSART_CTSROUTE_PIN_SHIFT);
#endif

  GPIO_PinModeSet(SL_CPC_DRV_UART_RTS_PORT, SL_CPC_DRV_UART_RTS_PIN, gpioModePushPull, 0);
#if defined(EUART_COUNT) && (EUART_COUNT > 0)
  GPIO->EUARTROUTE_SET->ROUTEEN = GPIO_EUART_ROUTEEN_RTSPEN;
  GPIO->EUARTROUTE_SET->RTSROUTE = (SL_CPC_DRV_UART_RTS_PORT << _GPIO_EUART_RTSROUTE_PORT_SHIFT)
                                   | (SL_CPC_DRV_UART_RTS_PIN << _GPIO_EUART_RTSROUTE_PIN_SHIFT);
#else
  GPIO->EUSARTROUTE_SET[SL_CPC_DRV_UART_PERIPHERAL_NO].ROUTEEN = GPIO_EUSART_ROUTEEN_RTSPEN;
  GPIO->EUSARTROUTE_SET[SL_CPC_DRV_UART_PERIPHERAL_NO].RTSROUTE =
    (SL_CPC_DRV_UART_RTS_PORT << _GPIO_EUSART_RTSROUTE_PORT_SHIFT)
    | (SL_CPC_DRV_UART_RTS_PIN << _GPIO_EUSART_RTSROUTE_PIN_SHIFT);
#endif
#endif

  EUSART_UartInitHf(SL_CPC_DRV_UART_PERIPHERAL, &init);

  // Enabled TX complete interrupt
  EUSART_IntEnable(SL_CPC_DRV_UART_PERIPHERAL, EUSART_IEN_TXC);

  SL_CPC_DRV_UART_PERIPHERAL->CMD_SET = EUSART_CMD_CLEARTX;

  NVIC_EnableIRQ(SL_CPC_TX_IRQn(SL_CPC_DRV_UART_PERIPHERAL_NO));
#else

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

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITH_HWFC)
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
#endif

  // Enabled TX complete interrupt
  USART_IntEnable(SL_CPC_DRV_UART_PERIPHERAL, USART_IF_TXC);

  USART_IntClear(SL_CPC_DRV_UART_PERIPHERAL, 0xFFFFFFFF);

  // Discard false frames and/or IRQs
  SL_CPC_DRV_UART_PERIPHERAL->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;

  USART_Enable(SL_CPC_DRV_UART_PERIPHERAL, usartEnable);

#endif

  // Init DMA
  ecode = DMADRV_Init();
  if (ecode != ECODE_EMDRV_DMADRV_OK && ecode != ECODE_EMDRV_DMADRV_ALREADY_INITIALIZED) {
    EFM_ASSERT(false);
    return SL_STATUS_INITIALIZATION;
  }

  // Allocate read and write channel
  ecode = DMADRV_AllocateChannel(&read_channel, NULL);
  if (ecode != ECODE_OK) {
    EFM_ASSERT(false);
    return SL_STATUS_ALLOCATION_FAILED;
  }

  ecode = DMADRV_AllocateChannel(&write_channel, NULL);
  if (ecode != ECODE_OK) {
    DMADRV_FreeChannel(read_channel);
    EFM_ASSERT(false);
    return SL_STATUS_ALLOCATION_FAILED;
  }

  // Configure DMA transfer
  rx_config = (LDMA_TransferCfg_t)LDMA_TRANSFER_CFG_PERIPHERAL(SL_CPC_LDMA_RX_PERIPH_TRIGGER(SL_CPC_DRV_UART_PERIPHERAL_NO));
  tx_config = (LDMA_TransferCfg_t)LDMA_TRANSFER_CFG_PERIPHERAL(SL_CPC_LDMA_TX_PERIPH_TRIGGER(SL_CPC_DRV_UART_PERIPHERAL_NO));

  rx_config.ldmaDbgHalt = true;
  tx_config.ldmaDbgHalt = true;

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITHOUT_HWFC)
  void *buffer_ptr;

  if (sli_cpc_get_raw_rx_buffer(&buffer_ptr) != SL_STATUS_OK) {
    EFM_ASSERT(false);
    return SL_STATUS_ALLOCATION_FAILED;
  }
  rx_descriptor[0] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(&(SL_CPC_DRV_UART_PERIPHERAL->RXDATA), buffer_ptr, SL_MIN(SLI_CPC_RX_FRAME_MAX_LENGTH, DMA_MAX_XFER_LEN));

  if (sli_cpc_get_raw_rx_buffer(&buffer_ptr) != SL_STATUS_OK) {
    EFM_ASSERT(false);
    return SL_STATUS_ALLOCATION_FAILED;
  }
  rx_descriptor[1] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(&(SL_CPC_DRV_UART_PERIPHERAL->RXDATA), buffer_ptr, SL_MIN(SLI_CPC_RX_FRAME_MAX_LENGTH, DMA_MAX_XFER_LEN));
  rx_descriptor[0].xfer.doneIfs = 0;
  rx_descriptor[1].xfer.doneIfs = 0;

  update_dma_desc_link_abs(&rx_descriptor[0], &rx_descriptor[1], false);
  update_dma_desc_link_abs(&rx_descriptor[1], &rx_descriptor[0], false);
  rx_descriptor_head = &rx_descriptor[0];

  memset(&recovery_context, 0x00, sizeof(recovery_context));

  // Get two receive queue items and don't give them back.
  // These will ensure that there are always two RX buffers available for the
  // driver.
  sl_cpc_receive_queue_item_t *item;
  if (sli_cpc_get_receive_queue_item(&item) != SL_STATUS_OK) {
    return SL_STATUS_ALLOCATION_FAILED;
  }
  if (sli_cpc_get_receive_queue_item(&item) != SL_STATUS_OK) {
    return SL_STATUS_ALLOCATION_FAILED;
  }

#endif
  next_rx_size = SLI_CPC_HDLC_HEADER_RAW_SIZE;

  // Start the DMA for the first time
  restart_dma();

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

  *capabilities = (sli_cpc_drv_capabilities_t){ 0 };
  capabilities->preprocess_hdlc_header = true;
  capabilities->use_raw_rx_buffer = true;
  capabilities->uart_flowcontrol = SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITH_HWFC;
}

/***************************************************************************/ /**
 * Read bytes from UART.
 ******************************************************************************/
sl_status_t sli_cpc_drv_read_data(sl_cpc_buffer_handle_t **buffer_handle, uint16_t *payload_rx_len)
{
  sl_status_t status;
  MCU_DECLARE_IRQ_STATE;

  MCU_ENTER_ATOMIC();
  sli_buf_entry_t *entry = (sli_buf_entry_t *)SLI_CPC_POP_BUFFER_HANDLE_LIST(&rx_pending_list_head, sli_buf_entry_t);
  if (entry == NULL) {
    MCU_EXIT_ATOMIC();
    return SL_STATUS_EMPTY;
  }

  *buffer_handle = entry->handle;
  *payload_rx_len = SLI_CPC_RX_DATA_MAX_LENGTH;

  status = sli_cpc_get_buffer_handle_for_rx(&entry->handle);
  if (status == SL_STATUS_OK) {
    sli_cpc_push_buffer_handle(&rx_free_list_head, &entry->node, entry->handle);
    if (rx_need_rx_entry) {
      rx_need_rx_entry = false;
      if (need_rx_buffer == false) {
        restart_dma();
      }
    }
  } else {
    sl_slist_push(&rx_free_no_buffer_handle_list_head, &entry->node);
  }
  MCU_EXIT_ATOMIC();

  return SL_STATUS_OK;
}

/***************************************************************************/ /**
 * Write bytes to UART.
 ******************************************************************************/
sl_status_t sli_cpc_drv_transmit_data(sl_cpc_buffer_handle_t *buffer_handle, uint16_t payload_tx_len)
{
  sl_status_t status;
  sli_buf_entry_t *entry;
  MCU_DECLARE_IRQ_STATE;

  MCU_ENTER_ATOMIC();
  entry = (sli_buf_entry_t *)sl_slist_pop(&tx_free_list_head);
  MCU_EXIT_ATOMIC();

  if (entry == NULL) {
    return SL_STATUS_NOT_READY;
  }

  entry->handle = buffer_handle;
  entry->payload_len = payload_tx_len;

  EFM_ASSERT(buffer_handle->hdlc_header != NULL);

  MCU_ENTER_ATOMIC();
  sli_cpc_push_back_buffer_handle(&tx_submitted_list_head, &entry->node, entry->handle);

  status = prepare_next_tx();
  MCU_EXIT_ATOMIC();

  return status;
}

/***************************************************************************/ /**
 * Checks if driver is ready to transmit.
 ******************************************************************************/
bool sli_cpc_drv_is_transmit_ready(void)
{
  sl_slist_node_t *head;
  bool flag;

  MCU_ATOMIC_LOAD(flag, tx_ready);
  MCU_ATOMIC_LOAD(head, tx_free_list_head);

  return (head != NULL
          && flag);
}

/***************************************************************************//**
 * Get currently configured bus bitrate
 ******************************************************************************/
uint32_t sli_cpc_drv_get_bus_bitrate(void)
{
  return SL_CPC_DRV_UART_BAUDRATE;
}

/***************************************************************************//**
 * Get maximum bus bitrate
 ******************************************************************************/
uint32_t sli_cpc_drv_get_bus_max_bitrate(void)
{
  return SL_CPC_DRV_UART_BAUDRATE;
}

/***************************************************************************/ /**
 * Prepare for transmission of next buffer.
 ******************************************************************************/
static sl_status_t prepare_next_tx(void)
{
  sli_buf_entry_t *entry;
  Ecode_t code;
  uint8_t idx = 0;
  MCU_DECLARE_IRQ_STATE;

  MCU_ENTER_ATOMIC();
  entry = (sli_buf_entry_t *)tx_submitted_list_head;
  if (entry == NULL) {
    MCU_EXIT_ATOMIC();
    return SL_STATUS_EMPTY;
  }

  EFM_ASSERT(entry->handle->hdlc_header != NULL);

  if (entry->payload_len > 0u) {
    /* First TX descriptor is for the header */
    tx_descriptor[idx++] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_M2P_BYTE(
      entry->handle->hdlc_header,
      &(SL_CPC_DRV_UART_PERIPHERAL->TXDATA),
      SLI_CPC_HDLC_HEADER_RAW_SIZE,
      1u);

    /* next descriptor(s) are for the payload */
    if (entry->payload_len <= DMADRV_MAX_XFER_COUNT) {
      tx_descriptor[idx++] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_M2P_BYTE(
        entry->handle->data,
        &(SL_CPC_DRV_UART_PERIPHERAL->TXDATA),
        entry->payload_len,
        1u);
    } else if (entry->payload_len <= (DMADRV_MAX_XFER_COUNT * 2)) {
      tx_descriptor[idx++] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_M2P_BYTE(
        entry->handle->data,
        &(SL_CPC_DRV_UART_PERIPHERAL->TXDATA),
        DMADRV_MAX_XFER_COUNT,
        1u);
      tx_descriptor[idx++] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_M2P_BYTE(
        &((uint8_t *)entry->handle->data)[DMADRV_MAX_XFER_COUNT],
        &(SL_CPC_DRV_UART_PERIPHERAL->TXDATA),
        (entry->payload_len - DMADRV_MAX_XFER_COUNT),
        1u);
    } else {
      MCU_EXIT_ATOMIC();
      return SL_STATUS_INVALID_PARAMETER;
    }

#if (SL_CPC_ENDPOINT_SECURITY_ENABLED >= 1)
    /*
     * If the security is enabled and there is a security tag to send, send it
     * before the FCS.
     */
    if (entry->handle->security_tag) {
      tx_descriptor[idx++] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_M2P_BYTE(
        (uint8_t *)entry->handle->security_tag,
        &(SL_CPC_DRV_UART_PERIPHERAL->TXDATA),
        SLI_SECURITY_TAG_LENGTH_BYTES,
        1u);
    }
#endif

    /* Caution: last descriptor, don't increment idx */
    tx_descriptor[idx] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_M2P_BYTE(
      entry->handle->fcs,
      &(SL_CPC_DRV_UART_PERIPHERAL->TXDATA),
      SLI_CPC_HDLC_FCS_SIZE);
  } else {
    /*
     * This buffer has no payload, header only.
     * Caution: last descriptor, don't increment idx
     */
    tx_descriptor[idx] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_M2P_BYTE(
      entry->handle->hdlc_header,
      &(SL_CPC_DRV_UART_PERIPHERAL->TXDATA),
      SLI_CPC_HDLC_HEADER_RAW_SIZE);
  }

  /* Clear doneIfs */
  for (uint8_t doneIfIndex = 0; doneIfIndex <= idx; doneIfIndex++) {
    tx_descriptor[doneIfIndex].xfer.doneIfs = 0u;
  }

  tx_ready = false;

  code = DMADRV_LdmaStartTransfer(write_channel,
                                  &tx_config,
                                  tx_descriptor,
                                  NULL,
                                  NULL);
  EFM_ASSERT(code == ECODE_OK);

  MCU_EXIT_ATOMIC();

  return SL_STATUS_OK;
}

/***************************************************************************/ /**
 * Notification when RX buffer becomes free.
 ******************************************************************************/
void sli_cpc_memory_on_rx_buffer_free(void)
{
  sl_status_t status;
  MCU_DECLARE_IRQ_STATE;
  MCU_ENTER_ATOMIC();

  do {
    if (rx_free_no_buffer_handle_list_head == NULL) {
      break;
    }

    sli_buf_entry_t *entry = (sli_buf_entry_t *)rx_free_no_buffer_handle_list_head;

    status = sli_cpc_get_buffer_handle_for_rx(&entry->handle);
    if (status == SL_STATUS_OK) {
      (void)sl_slist_pop(&rx_free_no_buffer_handle_list_head);
      sli_cpc_push_buffer_handle(&rx_free_list_head, &entry->node, entry->handle);
      if (rx_need_rx_entry) {
        rx_need_rx_entry = false;
      }
    }
  } while (status == SL_STATUS_OK && rx_free_no_buffer_handle_list_head != NULL);

  // Restart DMA if we previously ran out of buffers
  if (need_rx_buffer && !rx_need_rx_entry) {
    need_rx_buffer = false;
    restart_dma();
  }

  MCU_EXIT_ATOMIC();
}

/***************************************************************************//**
 * Dispatcher function, to notify core that packets have been transmitted
 ******************************************************************************/
static void sli_cpc_drv_dispatch_function(void *data)
{
  sli_buf_entry_t *entry;
  MCU_DECLARE_IRQ_STATE;

  (void)data;

  // When the entry is popped from tx_complete_list_head, it will decrease
  // entry->handle->ref_count. If an ack is received at this moment, the buffer
  // might get freed before sli_cpc_drv_notify_tx_complete is called, meaning
  // that this function would do a use-after-free operation. To prevent that,
  // popping off the list and calling the notify function must be done atomically.
  MCU_ENTER_ATOMIC();

  entry = (sli_buf_entry_t *)SLI_CPC_POP_BUFFER_HANDLE_LIST(&tx_complete_list_head, sli_buf_entry_t);
  while (entry != NULL) {
    sli_cpc_drv_notify_tx_complete(entry->handle);
    MCU_EXIT_ATOMIC();

    // release atomic section in case sli_cpc_drv_notify_tx_complete was long

    // these two lines could be separated in two atomic sections as they are
    // not related to one another, but as they both are very short, group them
    // together for shortness and readability
    MCU_ENTER_ATOMIC();
    sl_slist_push(&tx_free_list_head, &entry->node);
    entry = (sli_buf_entry_t *)SLI_CPC_POP_BUFFER_HANDLE_LIST(&tx_complete_list_head, sli_buf_entry_t);
  }

  MCU_EXIT_ATOMIC();
}

/***************************************************************************//**
 * TX IRQ handler.
 ******************************************************************************/
void SL_CPC_ISR_TX_HANDLER(SL_CPC_DRV_UART_PERIPHERAL_NO)(void)
{
#if defined(SL_CPC_DRV_PERIPH_IS_EUSART)
  uint32_t flag = EUSART_IntGet(SL_CPC_DRV_UART_PERIPHERAL);
  EUSART_IntClear(SL_CPC_DRV_UART_PERIPHERAL, flag & EUSART_IF_TXC);
#else
  uint32_t flag = USART_IntGet(SL_CPC_DRV_UART_PERIPHERAL);
  USART_IntClear(SL_CPC_DRV_UART_PERIPHERAL, flag & USART_IF_TXC);
#endif

#if defined(SL_CPC_DRV_PERIPH_IS_EUSART)
  if (flag & EUSART_IF_TXC) {
#else
  if (flag & USART_IF_TXC) {
#endif
    sli_buf_entry_t *entry;

    EFM_ASSERT(LDMA_TransferDone(write_channel));

    tx_ready = true;

    // these two lines keep entry->handle->ref_count equals to 1
    // and prevent it from being dropped by the core
    entry = (sli_buf_entry_t *)SLI_CPC_POP_BUFFER_HANDLE_LIST(&tx_submitted_list_head, sli_buf_entry_t);
    EFM_ASSERT(entry != NULL);
    sli_cpc_push_back_buffer_handle(&tx_complete_list_head, &entry->node, entry->handle);

    // it's possible that this interrupt handler is called twice (or more)
    // before the dispatch function is called. In that case, the second call
    // to sli_cpc_dispatcher_push would return an error, that's why the return
    // code is ignored here.
    sli_cpc_dispatcher_push(&dispatcher_handle,
                            sli_cpc_drv_dispatch_function,
                            NULL);

    if (tx_submitted_list_head) {
      prepare_next_tx();
    }
  }
}

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITHOUT_HWFC)
static void get_already_received_cnt(uint32_t *already_recvd_cnt)
{
  *already_recvd_cnt = LDMA->CH[read_channel].DST - rx_descriptor_head->xfer.dstAddr;
  EFM_ASSERT(*already_recvd_cnt <= SL_CPC_DRV_UART_RX_MAX_BUFFER_SIZE);
}

static void swap_descriptors(void)
{
  rx_descriptor_head = (LDMA_Descriptor_t *)(rx_descriptor_head->xfer.linkAddr << _LDMA_CH_LINK_LINKADDR_SHIFT);
}
#endif

static bool find_valid_header(uint8_t *buffer, uint16_t buffer_size, uint16_t *header_flag_position)
{
  uint16_t hcs = 0;

  EFM_ASSERT(buffer_size >= SLI_CPC_HDLC_HEADER_RAW_SIZE);

  for (uint16_t i = 0; i <= buffer_size - SLI_CPC_HDLC_HEADER_RAW_SIZE; i++) {
    if (buffer[i] == SLI_CPC_HDLC_FLAG_VAL) {
      hcs = sli_cpc_hdlc_get_hcs(&buffer[i]);
      if (sli_cpc_validate_crc_sw(&buffer[i], SLI_CPC_HDLC_HEADER_SIZE, hcs)) {
        if (header_flag_position != NULL) {
          *header_flag_position = i;
        }
        return true;
      }
    }
  }

  return false;
}

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITHOUT_HWFC)
static void dispatch_recovery(void)
{
  uint32_t chMask = 1UL << (uint8_t)read_channel;
  sl_status_t dispatch_status = SL_STATUS_FAIL;

  dispatch_status = sli_cpc_dispatcher_push(&recovery_dispatcher_handle, recovery, NULL);
  EFM_ASSERT(dispatch_status == SL_STATUS_OK);

  LDMA->CH[read_channel].LINK &= ~LDMA_CH_LINK_LINK;

  // Disable interrupts
#ifdef _LDMA_CH_CTRL_DONEIFSEN_MASK
  LDMA->CH[read_channel].CTRL &= ~_LDMA_CH_CTRL_DONEIFSEN_MASK;
#else
  LDMA->CH[read_channel].CTRL &= ~_LDMA_CH_CTRL_DONEIEN_MASK;
#endif
  LDMA->IEN &= ~chMask;

  // Clear any pending ISR
  LDMA_IntClear(chMask);
}

static void recovery(void *data)
{
  typedef enum {
    RECOVERY_FAILED = 0,
    RECOVERY_FOUND_HEADER,
    RECOVERY_FOUND_HEADER_NO_PAYLOAD,
    RECOVERY_FOUND_PAYLOAD
  } recovery_state_t;

  MCU_DECLARE_IRQ_STATE;
  (void)data;
  bool misaligned_payload = false;
  recovery_state_t recovery_state = RECOVERY_FAILED;
  void *rx_buffer_ptr;
  uint32_t already_recvd_cnt = 0;
  uint16_t header_flag_position = 0;
  sl_status_t status;
  bool exit = true;
  bool notify_core = false;
  bool resynced = false;
  bool header_found = false;

  MCU_ENTER_ATOMIC();

  do {
    misaligned_payload = false;
    recovery_state = RECOVERY_FAILED;
    already_recvd_cnt = 0;
    header_flag_position = 0;
    exit = true;
    notify_core = false;

    EFM_ASSERT(recovery_context.spilled_buffer != NULL);

    // Allocate a RX entry if necessary
    if (recovery_context.entry == NULL && header_expected_next) {
      recovery_context.entry = (sli_buf_entry_t *)SLI_CPC_POP_BUFFER_HANDLE_LIST(&rx_free_list_head, sli_buf_entry_t);
      if (recovery_context.entry == NULL) {
        // Stop and wait for buffer
        recovery_context.spilled_buffer = NULL; // Will be reused by the ISR
        rx_need_rx_entry = true;
        DMADRV_StopTransfer(read_channel);
        MCU_EXIT_ATOMIC();
        return;
      }
    }

    //===========================================================================
    //
    //  Driver is out of sync. Attempt a recovery by fetching potential HDLC headers
    //  and place them in a sliding window.
    //
    //===========================================================================
    if (recovery_context.out_of_sync) {
      do {
        //===========================================================================
        //
        // First we load the sliding window with data received by the ISR and check if
        // any valid header is found
        //
        //  ┌───────────────────┬───────────────────┐
        //  │ Previous ISR data │  Current ISR data │
        //  └───────────────────┴───────────────────┘
        //
        //===========================================================================
        // Slide and load the resync window with contents from the DMA complete ISR
        memmove(recovery_context.hdlc_header_out_of_sync_sliding_window, recovery_context.hdlc_header_out_of_sync_sliding_window + SLI_CPC_HDLC_HEADER_RAW_SIZE, SLI_CPC_HDLC_HEADER_RAW_SIZE);
        memcpy(recovery_context.hdlc_header_out_of_sync_sliding_window + SLI_CPC_HDLC_HEADER_RAW_SIZE, recovery_context.invalid_hdlc_header, SLI_CPC_HDLC_HEADER_RAW_SIZE);

        // Search for a header in these 14 bytes
        if (find_valid_header(recovery_context.hdlc_header_out_of_sync_sliding_window + 1, sizeof(recovery_context.hdlc_header_out_of_sync_sliding_window) - 1, &header_flag_position)) {
          header_flag_position += 1; // We skipped the first byte

          // Copy the contents of the recovered header
          memcpy(recovery_context.entry->handle->hdlc_header, recovery_context.hdlc_header_out_of_sync_sliding_window + header_flag_position, SLI_CPC_HDLC_HEADER_RAW_SIZE);
          recovery_context.entry->handle->data_length = sli_cpc_hdlc_get_length(recovery_context.entry->handle->hdlc_header);

          // Remember the bytes at the end of the sliding window.
          // They are not part of the spill buffer and could be the begining of a payload or another header
          recovery_context.out_of_sync_extra_bytes_len = sizeof(recovery_context.hdlc_header_out_of_sync_sliding_window) - (header_flag_position + SLI_CPC_HDLC_HEADER_RAW_SIZE);
          memcpy(recovery_context.out_of_sync_extra_bytes, recovery_context.hdlc_header_out_of_sync_sliding_window + SLI_CPC_HDLC_HEADER_RAW_SIZE + header_flag_position, recovery_context.out_of_sync_extra_bytes_len);

          // Resync was a success, reset the sliding window
          memset(recovery_context.hdlc_header_out_of_sync_sliding_window, 0x00, sizeof(recovery_context.hdlc_header_out_of_sync_sliding_window));

          recovery_context.out_of_sync = false;
          resynced = true; // We will be using this header
          break;
        }

        // We are still out of sync, another 7 bytes
        if (resize_current_dma_descriptor(SLI_CPC_HDLC_HEADER_RAW_SIZE) == SL_STATUS_OK) {
          sli_cpc_push_back_buffer_handle(&rx_free_list_head, &recovery_context.entry->node, recovery_context.entry->handle);
          recovery_context.spilled_buffer = NULL;
          recovery_context.offset = 0;
          recovery_context.entry = NULL;
          recovery_context.spilled_buffer = NULL;
          // We can exit here, another 7 bytes will be loaded by the DMA and an interrupt will be generated
          MCU_EXIT_ATOMIC();
          return;
        }

        //===========================================================================
        //
        // We are still out of sync, but there are 7 more bytes available in
        // the spill buffer, slide the window once more and load them.
        //
        //  ┌───────────────────┬───────────────────┐
        //  │ Current ISR data  │ Spill buffer data │
        //  └───────────────────┴───────────────────┘
        //
        //===========================================================================

        memcpy(recovery_context.hdlc_header_out_of_sync_sliding_window, recovery_context.hdlc_header_out_of_sync_sliding_window + SLI_CPC_HDLC_HEADER_RAW_SIZE, SLI_CPC_HDLC_HEADER_RAW_SIZE);
        memcpy(recovery_context.hdlc_header_out_of_sync_sliding_window + SLI_CPC_HDLC_HEADER_RAW_SIZE, recovery_context.spilled_buffer, SLI_CPC_HDLC_HEADER_RAW_SIZE);

        // Search for a header in these 14 bytes
        if (find_valid_header(recovery_context.hdlc_header_out_of_sync_sliding_window, sizeof(recovery_context.hdlc_header_out_of_sync_sliding_window), &header_flag_position)) {
          // Copy the contents of the recovered header
          memcpy(recovery_context.entry->handle->hdlc_header, recovery_context.hdlc_header_out_of_sync_sliding_window + header_flag_position, SLI_CPC_HDLC_HEADER_RAW_SIZE);
          recovery_context.entry->handle->data_length = sli_cpc_hdlc_get_length(recovery_context.entry->handle->hdlc_header);

          // It's possible that the header began in the first part of the sliding window and ended in the second.
          // If that is the case, we need to add an offset to the spill buffer
          recovery_context.offset = header_flag_position;

          // Resync was a success, reset the sliding window
          memset(recovery_context.hdlc_header_out_of_sync_sliding_window, 0x00, sizeof(recovery_context.hdlc_header_out_of_sync_sliding_window));

          recovery_context.out_of_sync = false;
          resynced = true; // We will be using this header
          break;
        }

        // We are still out of sync, update the window and load another 7 bytes
        if (resize_current_dma_descriptor(SLI_CPC_HDLC_HEADER_RAW_SIZE) == SL_STATUS_OK) {
          // Remember the last 7 bytes
          memcpy(recovery_context.hdlc_header_out_of_sync_sliding_window + SLI_CPC_HDLC_HEADER_RAW_SIZE,
                 recovery_context.spilled_buffer + (already_recvd_cnt - SLI_CPC_HDLC_HEADER_RAW_SIZE),
                 SLI_CPC_HDLC_HEADER_RAW_SIZE);

          sli_cpc_push_back_buffer_handle(&rx_free_list_head, &recovery_context.entry->node, recovery_context.entry->handle);
          recovery_context.spilled_buffer = NULL;
          recovery_context.offset = 0;
          recovery_context.entry = NULL;
          recovery_context.spilled_buffer = NULL;

          // We can exit here, another 7 bytes will be loaded by the DMA and an interrupt will be generated
          MCU_EXIT_ATOMIC();
          return;
        }

        //===========================================================================
        //
        // We are still out of sync, but there are 7 more bytes available in
        // the spill buffer. This means we can scan the remaining contents of
        // the spill buffer without worrying about any sliding window
        //
        //  ┌───────────────────────────────────────┐
        //  │          Spill buffer data            │
        //  └───────────────────────────────────────┘
        //
        //===========================================================================
        get_already_received_cnt(&already_recvd_cnt);
        if (find_valid_header(recovery_context.spilled_buffer, already_recvd_cnt, &header_flag_position)) {
          // Copy the contents from the spilled_buffer with the offset found from the header_flag_position
          memcpy(recovery_context.entry->handle->hdlc_header, recovery_context.spilled_buffer + header_flag_position, SLI_CPC_HDLC_HEADER_RAW_SIZE);
          recovery_context.entry->handle->data_length = sli_cpc_hdlc_get_length(recovery_context.entry->handle->hdlc_header);

          // Reset the sliding window
          memset(recovery_context.hdlc_header_out_of_sync_sliding_window, 0x00, sizeof(recovery_context.hdlc_header_out_of_sync_sliding_window));

          recovery_context.offset = SLI_CPC_HDLC_HEADER_RAW_SIZE + header_flag_position;
          recovery_context.out_of_sync = false;
          resynced = true;
          break;
        } else {
          // We are still out of sync and scanned the entire spill buffer, load another 7 bytes
          if (resize_current_dma_descriptor(SLI_CPC_HDLC_HEADER_RAW_SIZE + already_recvd_cnt) == SL_STATUS_OK) {
            // Remember the last 7 bytes
            memcpy(recovery_context.hdlc_header_out_of_sync_sliding_window + SLI_CPC_HDLC_HEADER_RAW_SIZE,
                   recovery_context.spilled_buffer + (already_recvd_cnt - SLI_CPC_HDLC_HEADER_RAW_SIZE),
                   SLI_CPC_HDLC_HEADER_RAW_SIZE);

            sli_cpc_push_back_buffer_handle(&rx_free_list_head, &recovery_context.entry->node, recovery_context.entry->handle);
            recovery_context.spilled_buffer = NULL;
            recovery_context.offset = already_recvd_cnt;
            recovery_context.entry = NULL;
            recovery_context.spilled_buffer = NULL;
            // We can exit here, another 7 bytes will be loaded by the DMA and an interrupt will be generated
            MCU_EXIT_ATOMIC();
            return;
          } else {
            // If we end up here, we traversed through the entire spill buffer and did not resync.
            // We need to drop the spill buffer and restart the DMA
            sli_cpc_push_back_buffer_handle(&rx_free_list_head, &recovery_context.entry->node, recovery_context.entry->handle);
            recovery_context.entry = NULL;
            recovery_context.spilled_buffer = NULL;
            if (!need_rx_buffer) {
              restart_dma();
            }
            MCU_EXIT_ATOMIC();
            return;
          }
        }
      } while (false); // Used for breaking out of if(recovery_context.out_of_sync)
    }
    EFM_ASSERT(recovery_context.out_of_sync_extra_bytes_len <= SLI_CPC_HDLC_HEADER_RAW_SIZE);

    //===========================================================================
    //
    //  Driver is in sync. Attempt to recover a header that has spilled
    //
    //===========================================================================
    // Do we need to re-align a payload ?
    if (recovery_context.misaligned_payload) {
      misaligned_payload = true;
      recovery_context.misaligned_payload = false;
    }

    if (header_expected_next) {
      // Expect a header
      if (resynced) {
        // A resync previously occured, and a header was found. Use it now.
        resynced = false;
        header_found = true;
      } else {
        get_already_received_cnt(&already_recvd_cnt);
        if (recovery_context.out_of_sync_extra_bytes_len > 0) {
          if (already_recvd_cnt >= (uint8_t)(SLI_CPC_HDLC_HEADER_RAW_SIZE - recovery_context.out_of_sync_extra_bytes_len)) {
            // A resync previously occured, and there was extra bytes in the sliding window.
            // We need to recover them by prepending them to the spill buffer
            EFM_ASSERT(recovery_context.out_of_sync_extra_bytes_len < SLI_CPC_HDLC_HEADER_RAW_SIZE);

            memcpy(recovery_context.entry->handle->hdlc_header,
                   recovery_context.out_of_sync_extra_bytes,
                   recovery_context.out_of_sync_extra_bytes_len);

            memcpy((uint8_t *)recovery_context.entry->handle->hdlc_header + recovery_context.out_of_sync_extra_bytes_len,
                   recovery_context.spilled_buffer,
                   SLI_CPC_HDLC_HEADER_RAW_SIZE - recovery_context.out_of_sync_extra_bytes_len);

            recovery_context.offset += (SLI_CPC_HDLC_HEADER_RAW_SIZE - recovery_context.out_of_sync_extra_bytes_len);
            recovery_context.out_of_sync_extra_bytes_len = 0;

            if (find_valid_header(recovery_context.entry->handle->hdlc_header, SLI_CPC_HDLC_HEADER_RAW_SIZE, NULL)) {
              recovery_context.entry->handle->data_length = sli_cpc_hdlc_get_length(recovery_context.entry->handle->hdlc_header);
              header_found = true;
            }
          }
        } else if (already_recvd_cnt >= SLI_CPC_HDLC_HEADER_RAW_SIZE ) {
          if (find_valid_header(recovery_context.spilled_buffer + recovery_context.offset, already_recvd_cnt - recovery_context.offset, &header_flag_position)) {
            // Copy the contents of the header to an entry and obtain payload length
            memcpy(recovery_context.entry->handle->hdlc_header,
                   recovery_context.spilled_buffer + recovery_context.offset + header_flag_position,
                   SLI_CPC_HDLC_HEADER_RAW_SIZE);

            recovery_context.entry->handle->data_length = sli_cpc_hdlc_get_length(recovery_context.entry->handle->hdlc_header);
            recovery_context.offset += SLI_CPC_HDLC_HEADER_RAW_SIZE + header_flag_position;
            header_found = true;
          }
        }
      }

      if (header_found) {
        if (recovery_context.entry->handle->data_length == 0) {
          recovery_state = RECOVERY_FOUND_HEADER_NO_PAYLOAD;
          sli_cpc_push_back_buffer_handle(&rx_pending_list_head, &recovery_context.entry->node, recovery_context.entry->handle);
          notify_core = true;
        } else if (recovery_context.entry->handle->data_length > SLI_CPC_RX_DATA_MAX_LENGTH) {
          notify_core_error(recovery_context.entry, SL_CPC_REJECT_ERROR);
        } else {
          recovery_state = RECOVERY_FOUND_HEADER;
          header_expected_next = false;
        }
        header_found = false;
      }
    } else {
      //===========================================================================
      //
      //  Driver is in sync. Attempt to recover a payload that has spilled
      //
      //===========================================================================

      if (recovery_context.out_of_sync_extra_bytes_len >= recovery_context.entry->handle->data_length) {
        //===========================================================================
        //
        //  There was recently a resync and the sliding resync window had enough
        //  extra bytes to populate a payload
        //
        //===========================================================================
        status = sli_cpc_get_raw_rx_buffer(&rx_buffer_ptr);
        if (status == SL_STATUS_OK) {
          memcpy(rx_buffer_ptr, recovery_context.out_of_sync_extra_bytes,
                 recovery_context.entry->handle->data_length);
          memmove(recovery_context.out_of_sync_extra_bytes,
                  recovery_context.out_of_sync_extra_bytes + recovery_context.entry->handle->data_length,
                  recovery_context.out_of_sync_extra_bytes_len - recovery_context.entry->handle->data_length);

          recovery_context.out_of_sync_extra_bytes_len -= recovery_context.entry->handle->data_length;

          recovery_context.entry->handle->data = rx_buffer_ptr;
          recovery_state = RECOVERY_FOUND_PAYLOAD;
          recovery_context.offset += recovery_context.entry->handle->data_length;
          sli_cpc_push_back_buffer_handle(&rx_pending_list_head, &recovery_context.entry->node, recovery_context.entry->handle);
          notify_core = true;
          header_expected_next = true;
        } else {
          // Stop and wait for buffer
          need_rx_buffer = true;
          recovery_context.out_of_sync_extra_bytes_len = 0;
          DMADRV_StopTransfer(read_channel);
        }
      } else if (misaligned_payload) {
        //===========================================================================
        //
        //  A misaligned_payload is when a partial payload was previously recovered
        //  but a DMA IRQ was required to receive the second part
        //
        //                         Resize               ISR
        //                          ▲                   ▲
        //                          │                   │
        //       ┌─────────┬────────┼───────────────────┤
        //       │ Header  │    P1  │         P2        │
        //       └─────────┴────────┴───────────────────┘
        //                       Payload (part 1 & 2)
        //
        //===========================================================================
        EFM_ASSERT(recovery_context.entry->handle->data_length > recovery_context.out_of_sync_extra_bytes_len);

        memmove(recovery_context.spilled_buffer + recovery_context.out_of_sync_extra_bytes_len,
                recovery_context.spilled_buffer + recovery_context.offset,
                recovery_context.entry->handle->data_length - recovery_context.out_of_sync_extra_bytes_len);

        memcpy(recovery_context.spilled_buffer,
               recovery_context.out_of_sync_extra_bytes,
               recovery_context.out_of_sync_extra_bytes_len);
        recovery_context.out_of_sync_extra_bytes_len = 0;

        recovery_context.entry->handle->data = recovery_context.spilled_buffer;
        recovery_context.spilled_buffer = recovery_context.active_buffer;
        recovery_state = RECOVERY_FOUND_PAYLOAD;
        sli_cpc_push_back_buffer_handle(&rx_pending_list_head, &recovery_context.entry->node, recovery_context.entry->handle);
        notify_core = true;
        header_expected_next = true;
        recovery_context.offset = 0; // Offset is zero because we just came back from an ISR
      } else {
        //===========================================================================
        //
        //  Check if the payload is completely in the spill buffer
        //
        //===========================================================================
        get_already_received_cnt(&already_recvd_cnt);

        if (already_recvd_cnt + recovery_context.out_of_sync_extra_bytes_len >= recovery_context.entry->handle->data_length + recovery_context.offset) {
          status = sli_cpc_get_raw_rx_buffer(&rx_buffer_ptr);
          if (status == SL_STATUS_OK) {
            // When we did a resync we probably had a few bytes extra in the sliding window.
            // These bytes are part of the payload.
            if (recovery_context.out_of_sync_extra_bytes_len > 0) {
              memcpy(rx_buffer_ptr,
                     recovery_context.out_of_sync_extra_bytes,
                     recovery_context.out_of_sync_extra_bytes_len);

              memcpy((uint8_t*)rx_buffer_ptr + recovery_context.out_of_sync_extra_bytes_len,
                     recovery_context.spilled_buffer + recovery_context.offset,
                     recovery_context.entry->handle->data_length - recovery_context.out_of_sync_extra_bytes_len);
              recovery_context.out_of_sync_extra_bytes_len = 0;
            } else {
              memcpy(rx_buffer_ptr, recovery_context.spilled_buffer + recovery_context.offset, recovery_context.entry->handle->data_length);
            }
            recovery_context.entry->handle->data = rx_buffer_ptr;
            recovery_state = RECOVERY_FOUND_PAYLOAD;
            recovery_context.offset += recovery_context.entry->handle->data_length;
            sli_cpc_push_back_buffer_handle(&rx_pending_list_head, &recovery_context.entry->node, recovery_context.entry->handle);
            notify_core = true;
            header_expected_next = true;
          } else {
            // Stop and wait for buffer
            need_rx_buffer = true;
            DMADRV_StopTransfer(read_channel);
          }
        }
      }
    }

    if (recovery_state == RECOVERY_FOUND_HEADER) {
      EFM_ASSERT(header_expected_next == false);
      EFM_ASSERT(recovery_context.entry != NULL);

      if (recovery_context.entry->handle->data_length + recovery_context.offset > SL_CPC_DRV_UART_RX_MAX_BUFFER_SIZE) {
        recovery_state = RECOVERY_FAILED;
      } else {
        if (recovery_context.entry->handle->data_length <= recovery_context.out_of_sync_extra_bytes_len) {
          // We will recover the payload from the out of sync extra bytes
          exit = false;
        } else {
          status = resize_current_dma_descriptor(recovery_context.offset + recovery_context.entry->handle->data_length - recovery_context.out_of_sync_extra_bytes_len);
          if (status == SL_STATUS_OK) {
            recovery_context.misaligned_payload = true; // We will need to re-align the payload outside of the ISR context
          } else if (status == SL_STATUS_ALREADY_EXISTS) {
            exit = false;
          }
        }
      }
    }

    if ((recovery_state == RECOVERY_FOUND_PAYLOAD || recovery_state == RECOVERY_FOUND_HEADER_NO_PAYLOAD) && need_rx_buffer == false) {
      if ((uint16_t)(SLI_CPC_HDLC_HEADER_RAW_SIZE + recovery_context.offset) > SL_CPC_DRV_UART_RX_MAX_BUFFER_SIZE) {
        recovery_state = RECOVERY_FAILED;
      } else {
        status = resize_current_dma_descriptor(recovery_context.offset + SLI_CPC_HDLC_HEADER_RAW_SIZE);
        if (status == SL_STATUS_OK) {
          recovery_context.spilled_buffer = NULL; // Will be reused by the ISR
          recovery_context.recovery_completed = true;
        } else if (status == SL_STATUS_ALREADY_EXISTS) {
          exit = false;
        }
      }
    }

    if (notify_core) {
      sli_cpc_drv_notify_rx_data();
      recovery_context.entry = NULL;
    }

    if (recovery_state == RECOVERY_FAILED) {
      if (recovery_context.entry != NULL) {
        sli_cpc_push_back_buffer_handle(&rx_free_list_head, &recovery_context.entry->node, recovery_context.entry->handle);
        recovery_context.entry = NULL;
      }
      recovery_context.spilled_buffer = NULL;

      if (!need_rx_buffer) {
        restart_dma();
      }
    }
  } while (exit == false);

  MCU_EXIT_ATOMIC();
}
#endif

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITH_HWFC)
static bool rx_dma_complete_hwfc(unsigned int channel,
                                 unsigned int sequenceNo,
                                 void *userParam)
{
  MCU_DECLARE_IRQ_STATE;

  static sli_buf_entry_t *active_dma_rx_entry = NULL;
  LDMA_Descriptor_t *completed_desc = NULL;
  void *rx_buffer = NULL;
  uint8_t *active_rx_buffer = NULL;
  bool notify_core = false;
  bool found_header = false;
  uint16_t header_flag_position = 0;
  static bool out_of_sync = false;
  static bool was_out_of_sync = false;
  static uint8_t out_of_sync_extra_bytes = 0;
  static uint8_t hdlc_header_sliding_window[SLI_CPC_HDLC_HEADER_RAW_SIZE * 2];

  (void)channel;
  (void)sequenceNo;
  (void)userParam;

  MCU_ENTER_ATOMIC();
  completed_desc = rx_descriptor_head;
  EFM_ASSERT(completed_desc != NULL);

  if (was_out_of_sync) {
    active_rx_buffer = (uint8_t *)(completed_desc->xfer.dstAddr) - out_of_sync_extra_bytes;
    out_of_sync_extra_bytes = 0;
    was_out_of_sync = false;
  } else {
    active_rx_buffer = (uint8_t *)(completed_desc->xfer.dstAddr);
  }

  //===========================================================================
  //
  //  Resync
  //
  //===========================================================================
  if (out_of_sync) {
    // Update the sliding window
    memcpy(hdlc_header_sliding_window + SLI_CPC_HDLC_HEADER_RAW_SIZE, active_rx_buffer, SLI_CPC_HDLC_HEADER_RAW_SIZE);

    // Look for a header, no need to check the first byte or else we would have resynced on the last attempt
    found_header = find_valid_header(hdlc_header_sliding_window + 1, (SLI_CPC_HDLC_HEADER_RAW_SIZE * 2) - 1, &header_flag_position);
    if (!found_header) {
      // No header found. Slide the window, prime the DMA for another header.
      memcpy(hdlc_header_sliding_window, active_rx_buffer, SLI_CPC_HDLC_HEADER_RAW_SIZE);

      sli_cpc_free_raw_rx_buffer(active_rx_buffer);

      // Get more bytes to populate the sliding window used to resync
      resize_current_dma_descriptor(NULL, 0, SLI_CPC_HDLC_HEADER_RAW_SIZE);

      MCU_EXIT_ATOMIC();
      return false;
    }

    header_flag_position += 1; // We skipped the first byte

    // Reconstruct the valid header
    memcpy(active_rx_buffer, hdlc_header_sliding_window + header_flag_position, SLI_CPC_HDLC_HEADER_RAW_SIZE);

    // Resync completed
    out_of_sync = false;
    was_out_of_sync = true;
  }

  //===========================================================================
  //
  //  Process HDLC header
  //
  //===========================================================================
  if (header_expected_next) {
    EFM_ASSERT(out_of_sync == false);
    active_dma_rx_entry = (sli_buf_entry_t *)SLI_CPC_POP_BUFFER_HANDLE_LIST(&rx_free_list_head, sli_buf_entry_t);
    if (active_dma_rx_entry == NULL) {
      rx_need_rx_entry = true;
      DMADRV_StopTransfer(read_channel);
      MCU_EXIT_ATOMIC();
      return false;
    }

    // Validate HCS
    if (!was_out_of_sync && !find_valid_header(active_rx_buffer, SLI_CPC_HDLC_HEADER_RAW_SIZE, NULL)) {
      EFM_ASSERT(!was_out_of_sync); // If we just resynced, the header should be valid

      // Remember this invalid header when we will attempt a resync
      memcpy(hdlc_header_sliding_window, active_rx_buffer, SLI_CPC_HDLC_HEADER_RAW_SIZE);
      sli_cpc_free_raw_rx_buffer(active_rx_buffer);
      sli_cpc_push_back_buffer_handle(&rx_free_list_head, &active_dma_rx_entry->node, active_dma_rx_entry->handle);
      out_of_sync = true;

      // Get more bytes to populate the sliding window used to resync
      resize_current_dma_descriptor(NULL, 0, SLI_CPC_HDLC_HEADER_RAW_SIZE);

      MCU_EXIT_ATOMIC();
      return false;
    }

    active_dma_rx_entry->handle->data_length = sli_cpc_hdlc_get_length(active_rx_buffer);
    active_dma_rx_entry->payload_len = active_dma_rx_entry->handle->data_length;

    // Copy useful fields of header. Unfortunately with this method the header must always be copied
    memcpy(active_dma_rx_entry->handle->hdlc_header, active_rx_buffer, SLI_CPC_HDLC_HEADER_RAW_SIZE);

    // Free the unused buffer
    sli_cpc_free_raw_rx_buffer(active_rx_buffer);

    if (active_dma_rx_entry->handle->data_length == 0) {
      notify_core = true;
      header_expected_next = true;
      next_rx_size = SLI_CPC_HDLC_HEADER_RAW_SIZE;
    } else if (next_rx_size > SLI_CPC_RX_DATA_MAX_LENGTH) {
      SLI_CPC_DEBUG_TRACE_CORE_DRIVER_PACKET_DROPPED();
      notify_core_error(active_dma_rx_entry, SL_CPC_REJECT_ERROR);
      header_expected_next = true;
      active_dma_rx_entry = NULL;
      next_rx_size = SLI_CPC_HDLC_HEADER_RAW_SIZE;
    } else {
      header_expected_next = false;
      next_rx_size = active_dma_rx_entry->handle->data_length;
      active_dma_rx_entry->payload_len = next_rx_size;
    }

    if (was_out_of_sync) {
      // The resync sliding window might contain data that belongs to another header or another payload
      // Prepare a buffer with the extra bytes already pre-loaded
      sl_status_t status = sli_cpc_get_raw_rx_buffer(&rx_buffer);

      if (status == SL_STATUS_OK) {
        // Calculate how many bytes of the next payload are already in the header resync window
        out_of_sync_extra_bytes = (2 * SLI_CPC_HDLC_HEADER_RAW_SIZE) - (header_flag_position + SLI_CPC_HDLC_HEADER_RAW_SIZE);

        if (out_of_sync_extra_bytes >= next_rx_size) {
          EFM_ASSERT(active_dma_rx_entry->handle->data_length > 0);

          // We already have all the bytes that we need to process a payload, no need to resize the DMA
          out_of_sync_extra_bytes -= next_rx_size;

          // Populate the payload buffers with the contents of the resync sliding window
          memcpy(rx_buffer, hdlc_header_sliding_window + SLI_CPC_HDLC_HEADER_RAW_SIZE + header_flag_position, next_rx_size);

          // Add to current rx handle
          EFM_ASSERT(active_dma_rx_entry != NULL);
          notify_core = true;
          active_dma_rx_entry->handle->data = rx_buffer;

          if (out_of_sync_extra_bytes > 0) {
            // There are still bytes available in the resync window
            // Prepare a buffer with the remaining bytes to prefix the next header
            sl_status_t status = sli_cpc_get_raw_rx_buffer(&rx_buffer);

            if (status == SL_STATUS_OK) {
              memcpy(rx_buffer, hdlc_header_sliding_window + SLI_CPC_HDLC_HEADER_RAW_SIZE + header_flag_position + next_rx_size, out_of_sync_extra_bytes);
              next_rx_size = SLI_CPC_HDLC_HEADER_RAW_SIZE;
              resize_current_dma_descriptor(rx_buffer, out_of_sync_extra_bytes, SLI_CPC_HDLC_HEADER_RAW_SIZE);
            } else {
              // Drop the extra bytes and wait for a new buffer
              DMADRV_StopTransfer(read_channel);
              out_of_sync_extra_bytes = 0;
              next_rx_size = SLI_CPC_HDLC_HEADER_RAW_SIZE;
              need_rx_buffer = true;
              MCU_EXIT_ATOMIC();
              return false;
            }
            out_of_sync_extra_bytes = 0;
          } else {
            next_rx_size = SLI_CPC_HDLC_HEADER_RAW_SIZE;
            resize_current_dma_descriptor(NULL, 0, SLI_CPC_HDLC_HEADER_RAW_SIZE);
          }

          // A header is always expected after a payload
          header_expected_next = true;
        } else {
          // The contents of the next payload are not fully in the resync
          // window. We need to resize the DMA to generate an interrupt on
          // the rest of the bytes.
          memcpy(rx_buffer, hdlc_header_sliding_window + SLI_CPC_HDLC_HEADER_RAW_SIZE + header_flag_position, out_of_sync_extra_bytes);
          resize_current_dma_descriptor(rx_buffer, out_of_sync_extra_bytes, next_rx_size);
        }
      } else {
        // Could not allocate a buffer for the next payload
        EFM_ASSERT(0);
        DMADRV_StopTransfer(read_channel);
        out_of_sync_extra_bytes = 0;
        next_rx_size = SLI_CPC_HDLC_HEADER_RAW_SIZE;
        need_rx_buffer = true;
        MCU_EXIT_ATOMIC();
        return false;
      }
    } else {
      resize_current_dma_descriptor(NULL, 0, next_rx_size);
    }

    //===========================================================================
    //
    //  Process payload
    //
    //===========================================================================
  } else {
    // Add to current rx handle
    EFM_ASSERT(active_dma_rx_entry != NULL);
    active_dma_rx_entry->handle->data = active_rx_buffer;

    next_rx_size = SLI_CPC_HDLC_HEADER_RAW_SIZE;
    resize_current_dma_descriptor(NULL, 0, SLI_CPC_HDLC_HEADER_RAW_SIZE);

    notify_core = true;

    // A header is always expected after a payload
    header_expected_next = true;
  }

  if (notify_core) {
    // Push rx_entry to pending list
    sli_cpc_push_back_buffer_handle(&rx_pending_list_head, &active_dma_rx_entry->node, active_dma_rx_entry->handle);

    // Notify core
    sli_cpc_drv_notify_rx_data();
  }

  MCU_EXIT_ATOMIC();
  return false;
}
#endif

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITHOUT_HWFC)
static bool rx_dma_complete_no_hwfc(unsigned int channel,
                                    unsigned int sequenceNo,
                                    void *userParam)
{
  MCU_DECLARE_IRQ_STATE;

  static sli_buf_entry_t *active_dma_rx_entry = NULL;
  sl_status_t update_status = SL_STATUS_FAIL;
  LDMA_Descriptor_t *completed_desc = NULL;
  uint8_t *active_rx_buffer = NULL;
  uint8_t *rx_data = NULL;
  uint8_t *spill_buffer;
  bool notify_core = false;

  (void)channel;
  (void)sequenceNo;
  (void)userParam;

  MCU_ENTER_ATOMIC();
  EFM_ASSERT(recovery_dispatcher_handle.submitted == false);

  completed_desc = rx_descriptor_head;
  EFM_ASSERT(completed_desc != NULL);

  active_rx_buffer = (uint8_t *)(completed_desc->xfer.dstAddr);
  rx_data = active_rx_buffer;

  if (recovery_context.recovery_completed || recovery_context.out_of_sync) {
    EFM_ASSERT(header_expected_next);
    rx_data += recovery_context.offset;
    next_rx_size = SLI_CPC_HDLC_HEADER_RAW_SIZE;
  }

  // Every time a RX complete ISR occurs, the LDMA automatically loads the linkAddr
  // register. On our side we need to sync with it by swapping the descriptor
  // so that our rx_descriptor_head matches the descriptor currently being used
  // The previously active descriptor now becomes the spill descriptor and vice versa
  swap_descriptors();
  spill_buffer = (uint8_t *)(rx_descriptor_head->xfer.dstAddr);

  void *new_buffer;
  sl_status_t status = sli_cpc_get_raw_rx_buffer(&new_buffer);
  if (status == SL_STATUS_OK) {
    completed_desc->xfer.dstAddr = (uint32_t)new_buffer;
  } else {
    // We always need two buffers, one active and one used for spillage.
    // There is no point in going any further here..

    // If we were processing a misaligned_payload (header and payload in same buffer, the rx entry was previously allocated)
    if (recovery_context.misaligned_payload) {
      sli_cpc_push_back_buffer_handle(&rx_free_list_head, &recovery_context.entry->node, recovery_context.entry->handle);
      recovery_context.entry = NULL;
      recovery_context.misaligned_payload = false;
      recovery_context.spilled_buffer = NULL;
    } else {
      if (header_expected_next == false) {
        sli_cpc_push_back_buffer_handle(&rx_free_list_head, &active_dma_rx_entry->node, active_dma_rx_entry->handle);
        active_dma_rx_entry = NULL;
      }
    }

    need_rx_buffer = true;

    if (header_expected_next == false) {
      DMADRV_StopTransfer(read_channel);
      recovery_context.recovery_completed = false;
      MCU_EXIT_ATOMIC();
      return false;
    }
  }

  if (recovery_context.misaligned_payload) {
    // We need to re-align the entry outside of the ISR context
    recovery_context.spilled_buffer = active_rx_buffer;
    recovery_context.active_buffer = spill_buffer;
    dispatch_recovery();
    MCU_EXIT_ATOMIC();
    return false;
  }

  //===========================================================================
  //
  //  Process HDLC header
  //
  //===========================================================================
  if (header_expected_next) {
    active_dma_rx_entry = (sli_buf_entry_t *)SLI_CPC_POP_BUFFER_HANDLE_LIST(&rx_free_list_head, sli_buf_entry_t);
    if (active_dma_rx_entry == NULL) {
      rx_need_rx_entry = true;
      DMADRV_StopTransfer(read_channel); // Without an entry we can't do much..

      if (!need_rx_buffer) {
        // Can free the buffer right away
        sli_cpc_free_raw_rx_buffer(active_rx_buffer);
      }

      recovery_context.recovery_completed = false;
      MCU_EXIT_ATOMIC();
      return false;
    }

    // Copy useful fields of header
    memcpy(active_dma_rx_entry->handle->hdlc_header, rx_data, SLI_CPC_HDLC_HEADER_RAW_SIZE);

    // Can free the buffer right away
    sli_cpc_free_raw_rx_buffer(active_rx_buffer);

    // We freed the buffer used to capture the HDLC header, reclaim it if we previously failed to allocate one
    if (need_rx_buffer) {
      need_rx_buffer = false;
      sl_status_t status = sli_cpc_get_raw_rx_buffer(&new_buffer);
      if (status == SL_STATUS_OK) {
        completed_desc->xfer.dstAddr = (uint32_t)new_buffer;
      } else {
        EFM_ASSERT(false); //This should not happen.. we just freed a buffer
      }
    }

    // Validate HCS
    if (!find_valid_header(active_dma_rx_entry->handle->hdlc_header, SLI_CPC_HDLC_HEADER_RAW_SIZE, NULL)) {
      memcpy(recovery_context.invalid_hdlc_header, active_dma_rx_entry->handle->hdlc_header, SLI_CPC_HDLC_HEADER_RAW_SIZE);

      sli_cpc_push_back_buffer_handle(&rx_free_list_head, &active_dma_rx_entry->node, active_dma_rx_entry->handle);
      active_dma_rx_entry = NULL;
      recovery_context.entry = NULL;
      recovery_context.recovery_completed = false;
      recovery_context.out_of_sync = true;
      recovery_context.spilled_buffer = spill_buffer;
      recovery_context.offset = 0;
      dispatch_recovery();

      MCU_EXIT_ATOMIC();
      return false;
    }

    recovery_context.out_of_sync = false;

    active_dma_rx_entry->handle->data_length = sli_cpc_hdlc_get_length(active_dma_rx_entry->handle->hdlc_header);
    active_dma_rx_entry->payload_len = active_dma_rx_entry->handle->data_length;

    // Prepare the size of the next transfer, according to the payload field of the HDLC header
    if (active_dma_rx_entry->payload_len == 0) {
      header_expected_next = true;
      notify_core = true;
      next_rx_size = SLI_CPC_HDLC_HEADER_RAW_SIZE;
    } else if (active_dma_rx_entry->payload_len > SLI_CPC_RX_DATA_MAX_LENGTH) {
      SLI_CPC_DEBUG_TRACE_CORE_DRIVER_PACKET_DROPPED();
      notify_core_error(active_dma_rx_entry, SL_CPC_REJECT_ERROR);
      active_dma_rx_entry = NULL;
      header_expected_next = true;
      next_rx_size = SLI_CPC_HDLC_HEADER_RAW_SIZE;
    } else {
      header_expected_next = false;
      next_rx_size = active_dma_rx_entry->handle->data_length;
    }

    // Attempt a resize of the currently active descriptor to generate an interrution on completion
    update_status = resize_current_dma_descriptor(next_rx_size);
    if (update_status == SL_STATUS_ALREADY_EXISTS) {
      recovery_context.spilled_buffer = spill_buffer;
      recovery_context.offset = 0;

      if (notify_core) {
        // Push rx_entry to pending list
        sli_cpc_push_back_buffer_handle(&rx_pending_list_head, &active_dma_rx_entry->node, active_dma_rx_entry->handle);

        // Notify core
        sli_cpc_drv_notify_rx_data();
        recovery_context.entry = NULL;
      } else {
        if (header_expected_next) {
          sli_cpc_push_back_buffer_handle(&rx_free_list_head, &active_dma_rx_entry->node, active_dma_rx_entry->handle);
          recovery_context.entry = NULL;
        } else {
          recovery_context.entry = active_dma_rx_entry;
        }
      }
      active_dma_rx_entry = NULL;
      dispatch_recovery();

      recovery_context.recovery_completed = false;
      MCU_EXIT_ATOMIC();
      return false;
    }
    //===========================================================================
    //
    //  Process payload
    //
    //===========================================================================
  } else {
    // Add to current rx handle
    EFM_ASSERT(active_dma_rx_entry != NULL);

    active_dma_rx_entry->handle->data = rx_data;
    notify_core = true;

    // A header is always expected after a payload
    header_expected_next = true;
    next_rx_size = SLI_CPC_HDLC_HEADER_RAW_SIZE;
    update_status = resize_current_dma_descriptor(SLI_CPC_HDLC_HEADER_RAW_SIZE);
    if (update_status == SL_STATUS_ALREADY_EXISTS) {
      header_expected_next = true;

      recovery_context.spilled_buffer = spill_buffer;
      recovery_context.entry = NULL; // Allocate an entry during recovery, because this one will be used for the payload
      recovery_context.offset = 0;

      dispatch_recovery();
    }
  }

  if (notify_core) {
    // Push rx_entry to pending list
    sli_cpc_push_back_buffer_handle(&rx_pending_list_head, &active_dma_rx_entry->node, active_dma_rx_entry->handle);

    // Notify core
    sli_cpc_drv_notify_rx_data();
    active_dma_rx_entry = NULL;
  }

  recovery_context.recovery_completed = false;
  MCU_EXIT_ATOMIC();
  return false;
}
#endif

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITHOUT_HWFC)
/***************************************************************************/ /**
 * Update dma desccriptor link absolute address.
 *
 * @param current_dma_desc DMA descriptor to update.
 *
 * @param next_dma_desc DMA descriptor to link to.
 ******************************************************************************/
static void update_dma_desc_link_abs(LDMA_Descriptor_t *current_dma_desc,
                                     LDMA_Descriptor_t *next_dma_desc,
                                     bool enable_link)
{
  uint32_t link = 0;
  uint32_t *current_dma_buffer = (uint32_t *)current_dma_desc;

  link = (uint32_t)next_dma_desc;
  link |= ldmaLinkModeAbs;

  if (enable_link) {
    link |= LDMA_CH_LINK_LINK;
  }

  current_dma_buffer[3] = link;
}

/***************************************************************************/ /**
 * Update XferCnt of the current DMA xfer with the length passed as argument.
 *
 * @param new_length Total length of next transfer.
 *
 * @return SL_STATUS_OK if new length successfully applied.
 *         SL_STATUS_ALREADY_EXISTS if the DMA already transferred the requested bytes or more.
 ******************************************************************************/
static sl_status_t resize_current_dma_descriptor(uint16_t new_length)
{
  MCU_DECLARE_IRQ_STATE;

  MCU_ENTER_ATOMIC();
  uint32_t chMask = 1UL << (uint8_t)read_channel;
  uint32_t ctrl;

  if (new_length > DMA_MAX_XFER_LEN) {
    EFM_ASSERT(false);
  }

  uint32_t already_recvd_cnt;
  uint16_t remaining;

  // Adjust current dma xfer with new_length
  // For safety we momentarily pause the DMA. If we are afraid of suspending
  // it for too long and loosing bytes, we could use a critical section to make
  // sure there are not higher priority interrupt until we resume it.
  DMADRV_PauseTransfer(read_channel);

  ctrl = LDMA->CH[read_channel].CTRL;
  get_already_received_cnt(&already_recvd_cnt);

  if (already_recvd_cnt >= new_length) {
    DMADRV_ResumeTransfer(read_channel);
    MCU_EXIT_ATOMIC();
    return SL_STATUS_ALREADY_EXISTS;
  }

  remaining = new_length - already_recvd_cnt;

  // Update xfercnt
  ctrl &= ~_LDMA_CH_CTRL_XFERCNT_MASK;
  ctrl |= ((remaining - 1) << _LDMA_CH_CTRL_XFERCNT_SHIFT) & _LDMA_CH_CTRL_XFERCNT_MASK;
  LDMA->CH[read_channel].CTRL = ctrl;

  LDMA->CH[read_channel].LINK |= LDMA_CH_LINK_LINK;

  // Enable interrupts
#ifdef _LDMA_CH_CTRL_DONEIEN_MASK
  LDMA->CH[read_channel].CTRL |= LDMA_CH_CTRL_DONEIEN;
#else
  LDMA->CH[read_channel].CTRL |= LDMA_CH_CTRL_DONEIFSEN;
#endif

  LDMA_IntEnable(chMask);

  // Disable linking from the next descriptor
  LDMA_Descriptor_t *next = (LDMA_Descriptor_t *)(LDMA->CH[read_channel].LINK & _LDMA_CH_LINK_LINKADDR_MASK);
  next->xfer.link &= ~LDMA_CH_LINK_LINK;
  next_rx_size = new_length;

  DMADRV_ResumeTransfer(read_channel);

  EFM_ASSERT(already_recvd_cnt + remaining <= SL_CPC_DRV_UART_RX_MAX_BUFFER_SIZE);

  MCU_EXIT_ATOMIC();
  return SL_STATUS_OK;
}
#else
static void resize_current_dma_descriptor(void *pre_loaded_rx_buffer, uint16_t offset, uint16_t new_length)
{
  Ecode_t ecode;
  void *buffer_ptr;
  sl_status_t status;

  EFM_ASSERT(new_length > offset);
  next_rx_size = (new_length - offset);

  if (pre_loaded_rx_buffer == NULL) {
    status = sli_cpc_get_raw_rx_buffer(&buffer_ptr);
    if (status != SL_STATUS_OK) {
      DMADRV_StopTransfer(read_channel);
      need_rx_buffer = true;
      return;
    }
  } else {
    buffer_ptr = pre_loaded_rx_buffer;
  }

  if (new_length <= DMA_MAX_XFER_LEN) {
    rx_descriptor[0u] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(&(SL_CPC_DRV_UART_PERIPHERAL->RXDATA), (uint8_t *)buffer_ptr + offset, new_length - offset);
  } else {
    rx_descriptor[0u] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_P2M_BYTE(&(SL_CPC_DRV_UART_PERIPHERAL->RXDATA), (uint8_t *)buffer_ptr + offset, DMA_MAX_XFER_LEN - offset, 1u);
    rx_descriptor[1u] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(&(SL_CPC_DRV_UART_PERIPHERAL->RXDATA), &((uint8_t *)buffer_ptr)[DMA_MAX_XFER_LEN], (new_length - DMA_MAX_XFER_LEN));
    rx_descriptor[0u].xfer.doneIfs = 0u;
    rx_descriptor[1u].xfer.doneIfs = 1u;
  }

  // Start read channel
  ecode = DMADRV_LdmaStartTransfer(read_channel,
                                   &rx_config,
                                   rx_descriptor_head,
                                   rx_dma_complete_hwfc,
                                   0);
  EFM_ASSERT(ecode == ECODE_OK);

  return;
}
#endif

/***************************************************************************/ /**
 * Send a reject notification to CPC core.
 *
 * @param reason Reject reason.
 ******************************************************************************/
static void notify_core_error(sli_buf_entry_t * entry, sl_cpc_reject_reason_t reason)
{
  entry->handle->reason = reason;

  // Push rx_entry to pending list
  sli_cpc_push_back_buffer_handle(&rx_pending_list_head, &entry->node, entry->handle);

  // Notify core
  sli_cpc_drv_notify_rx_data();
}

/***************************************************************************/ /**
 * Stop DMA mode and start receiving bytes in interrupt mode.
 ******************************************************************************/
static void restart_dma(void)
{
  MCU_DECLARE_IRQ_STATE;

  MCU_ENTER_ATOMIC();

  DMADRV_StopTransfer(read_channel);

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITH_HWFC)
  if (need_rx_buffer) {
    MCU_EXIT_ATOMIC();
    return;
  }
#else
  SLI_CPC_DEBUG_TRACE_CORE_DRIVER_PACKET_DROPPED();

  EFM_ASSERT(recovery_dispatcher_handle.submitted == false);
  EFM_ASSERT(recovery_context.misaligned_payload == false);

  memset(&recovery_context, 0x00, sizeof(recovery_context));

  EFM_ASSERT(need_rx_buffer == false);
#endif

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITH_HWFC)
  void *buffer_ptr;
  sl_status_t status = sli_cpc_get_raw_rx_buffer(&buffer_ptr);
  if (status != SL_STATUS_OK) {
    need_rx_buffer = true;
    MCU_EXIT_ATOMIC();
    return;
  }

  rx_descriptor[0u] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(&(SL_CPC_DRV_UART_PERIPHERAL->RXDATA), buffer_ptr, next_rx_size);
#endif
  rx_descriptor_head = &rx_descriptor[0];

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITHOUT_HWFC)
  // Without HWFC a header is always expected next when doing a restart
  // This is because a restart is usually done when we freed a rx_buffer
  // and we don't know where we are in the bytestream sent by the host.
  // i.g. we could be in the middle of a payload
  header_expected_next = true;
  next_rx_size = SLI_CPC_HDLC_HEADER_RAW_SIZE;
  rx_descriptor_head->xfer.xferCnt =  SLI_CPC_HDLC_HEADER_RAW_SIZE - 1;
#endif

  Ecode_t ecode = DMADRV_LdmaStartTransfer(read_channel,
                                           &rx_config,
                                           rx_descriptor_head,
#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITH_HWFC)
                                           rx_dma_complete_hwfc,
#else
                                           rx_dma_complete_no_hwfc,
#endif
                                           0);
  EFM_ASSERT(ecode == ECODE_OK);

  // Restore xferCnt
  rx_descriptor_head->xfer.xferCnt =  SL_MIN(SLI_CPC_RX_FRAME_MAX_LENGTH, DMA_MAX_XFER_LEN) - 1;

#if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITHOUT_HWFC)
  LDMA->CH[read_channel].LINK |= LDMA_CH_LINK_LINK;

  // Enable interrupts
#ifdef _LDMA_CH_CTRL_DONEIEN_MASK
  LDMA->CH[read_channel].CTRL |= LDMA_CH_CTRL_DONEIEN;
#else
  LDMA->CH[read_channel].CTRL |= LDMA_CH_CTRL_DONEIFSEN;
#endif

  uint32_t chMask = 1UL << (uint8_t)read_channel;
  LDMA_IntEnable(chMask);
#endif

  MCU_EXIT_ATOMIC();
}
