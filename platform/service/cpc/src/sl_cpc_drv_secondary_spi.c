/***************************************************************************/ /**
 * @file
 * @brief CPC SPI SECONDARY implementation.
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

#ifdef CPC_TEST_SPI_DRIVER_CRC_ERROR_INJECTION
#include "stdio.h"
#endif

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif
#include "sl_status.h"
#include "sl_atomic.h"
#include "sl_slist.h"
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
#include "sl_power_manager.h"
#endif
#include "em_ldma.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_prs.h"
#include "dmadrv.h"

#include "sli_cpc.h"
#include "sli_cpc_drv.h"
#include "sli_cpc_hdlc.h"
#include "sli_cpc_crc.h"
#include "sli_cpc_debug.h"
#include "sl_cpc_config.h"
#include "sl_cpc_drv_secondary_spi_config.h"

/*******************************************************************************
 *********************************   DEFINES   *********************************
 ******************************************************************************/

#if !defined(SL_CPC_DRV_SPI_IS_EUSART) && !defined(SL_CPC_DRV_SPI_IS_USART)
#error "SPI driver needs to be configured for EUSART or USART"
#endif

#if defined(_SILICON_LABS_32B_SERIES_1) && defined(SL_CPC_DRV_SPI_IS_EUSART)
#error "Invalid configuration. EUSART does not exist on Series 1"
#endif

#if !defined(_SILICON_LABS_32B_SERIES_1) && !defined(_SILICON_LABS_32B_SERIES_2)
#error "This driver is only compatible with Series 1 & 2"
#endif

#if defined(SL_CPC_DRV_SPI_IS_EUSART)
#define PRS_SIGNAL_EXTI(cs_pin_no)          SL_CONCAT_PASTER_2(prsSignalGPIO_PIN, cs_pin_no)
#define PRS_SIGNAL_USART(periph_no, signal) SL_CONCAT_PASTER_4(prsSignalEUSART, periph_no, _, signal)
#define SPI_CMU_CLOCK(periph_no)            SL_CONCAT_PASTER_2(cmuClock_EUSART, periph_no)
#define DMA_SIGNAL_TX(periph_no)            SL_CONCAT_PASTER_3(dmadrvPeripheralSignal_EUSART, periph_no, _TXBL)
#define DMA_SIGNAL_RX(periph_no)            SL_CONCAT_PASTER_3(dmadrvPeripheralSignal_EUSART, periph_no, _RXDATAV)
#define GPIO_PORT_SHIFT(route)              SL_CONCAT_PASTER_3(_GPIO_EUSART_, route, _PORT_SHIFT)
#define GPIO_PIN_SHIFT(route)               SL_CONCAT_PASTER_3(_GPIO_EUSART_, route, _PIN_SHIFT)
#define GPIO_ROUTEEN                        (GPIO_EUSART_ROUTEEN_TXPEN | GPIO_EUSART_ROUTEEN_RXPEN | GPIO_EUSART_ROUTEEN_SCLKPEN | GPIO_EUSART_ROUTEEN_CSPEN)
#define EUSART_OR_USART_ROUTE               EUSARTROUTE
#define EUSART_TX_IRQHandler(periph_no)     SL_CONCAT_PASTER_3(EUSART, periph_no, _TX_IRQHandler)
#define EUSART_TX_IRQn(periph_no)           SL_CONCAT_PASTER_3(EUSART, periph_no, _TX_IRQn)
#elif defined(SL_CPC_DRV_SPI_IS_USART)
#define PRS_SIGNAL_USART(periph, signal)    SL_CONCAT_PASTER_4(prsSignalUSART, periph, _, signal)
#define SPI_CMU_CLOCK(periph_no)            SL_CONCAT_PASTER_2(cmuClock_USART, periph_no)
#define DMA_SIGNAL_TX(periph_no)            SL_CONCAT_PASTER_3(dmadrvPeripheralSignal_USART, periph_no, _TXBL)
#define DMA_SIGNAL_RX(periph_no)            SL_CONCAT_PASTER_3(dmadrvPeripheralSignal_USART, periph_no, _RXDATAV)
#define GPIO_PORT_SHIFT(route)              SL_CONCAT_PASTER_3(_GPIO_USART_, route, _PORT_SHIFT)
#define GPIO_PIN_SHIFT(route)               SL_CONCAT_PASTER_3(_GPIO_USART_, route, _PIN_SHIFT)
#define GPIO_ROUTEEN                        (GPIO_USART_ROUTEEN_TXPEN | GPIO_USART_ROUTEEN_RXPEN | GPIO_USART_ROUTEEN_CLKPEN | GPIO_USART_ROUTEEN_CSPEN)
#define EUSART_OR_USART_ROUTE               USARTROUTE
#endif

#define IRQ_PIN_SET_MASK  (1UL << SL_CPC_DRV_SPI_RX_IRQ_PIN)
#define TX_READY_WINDOW_TRIG_BIT_MASK (1 << SL_CPC_DRV_SPI_TX_AVAILABILITY_SYNCTRIG_CH)

#if defined(_SILICON_LABS_32B_SERIES_2)
static const uint32_t irq_set_addr = (uint32_t)&GPIO->P_SET[SL_CPC_DRV_SPI_RX_IRQ_PORT].DOUT;
static const uint32_t irq_clr_addr = (uint32_t)&GPIO->P_CLR[SL_CPC_DRV_SPI_RX_IRQ_PORT].DOUT;
#elif defined(_SILICON_LABS_32B_SERIES_1)
// On Series 1 devices, peripherals don't have SET/CLEAR registers. Instead, SET/CLR is done through a special memory range by adding a special offset to the address.
static const uint32_t irq_set_addr = (uint32_t)(&GPIO->P[SL_CPC_DRV_SPI_RX_IRQ_PORT].DOUT) | (PER_BITSET_MEM_BASE - PER_MEM_BASE); // added offset of 0x06000000;
static const uint32_t irq_clr_addr = (uint32_t)(&GPIO->P[SL_CPC_DRV_SPI_RX_IRQ_PORT].DOUT) | (PER_BITCLR_MEM_BASE - PER_MEM_BASE); // added offset of 0x04000000;
#endif

enum header_situation{
  HEADER_CORRUPTED,
  HEADER_NULL,
  HEADER_VALID
};

/*******************************************************************************
 *******************   LOGIC ANALYZER MACROS   *********************************
 ******************************************************************************/

#ifdef LOGIC_ANALYZER_TRACES

#define LOGIC_ANALYZER_TRACE_HEADER_TRANSFER_ISR_START              \
  GPIO_PinOutSet(LOGIC_ANALYZER_TRACE_HEADER_TRANSFER_ISR_PIN_PORT, \
                 LOGIC_ANALYZER_TRACE_HEADER_TRANSFER_ISR_PIN_PIN)

#define LOGIC_ANALYZER_TRACE_HEADER_TRANSFER_ISR_END                  \
  GPIO_PinOutClear(LOGIC_ANALYZER_TRACE_HEADER_TRANSFER_ISR_PIN_PORT, \
                   LOGIC_ANALYZER_TRACE_HEADER_TRANSFER_ISR_PIN_PIN)

#define LOGIC_ANALYZER_TRACE_PAYLOAD_TRANSFER_ISR_START              \
  GPIO_PinOutSet(LOGIC_ANALYZER_TRACE_PAYLOAD_TRANSFER_ISR_PIN_PORT, \
                 LOGIC_ANALYZER_TRACE_PAYLOAD_TRANSFER_ISR_PIN_PIN)

#define LOGIC_ANALYZER_TRACE_PAYLOAD_TRANSFER_ISR_END                  \
  GPIO_PinOutClear(LOGIC_ANALYZER_TRACE_PAYLOAD_TRANSFER_ISR_PIN_PORT, \
                   LOGIC_ANALYZER_TRACE_PAYLOAD_TRANSFER_ISR_PIN_PIN)

#define LOGIC_ANALYZER_TRACE_TX_DMA_ARMED                        \
  do {                                                           \
    GPIO_PinOutSet(LOGIC_ANALYZER_TRACE_TX_DMA_ARMED_PIN_PORT,   \
                   LOGIC_ANALYZER_TRACE_TX_DMA_ARMED_PIN_PIN);   \
    GPIO_PinOutClear(LOGIC_ANALYZER_TRACE_TX_DMA_ARMED_PIN_PORT, \
                     LOGIC_ANALYZER_TRACE_TX_DMA_ARMED_PIN_PIN); \
  } while (0)

#define LOGIC_ANALYZER_TRACE_TX_FLUSHED                        \
  do {                                                         \
    GPIO_PinOutSet(LOGIC_ANALYZER_TRACE_TX_FLUSHED_PIN_PORT,   \
                   LOGIC_ANALYZER_TRACE_TX_FLUSHED_PIN_PIN);   \
    GPIO_PinOutClear(LOGIC_ANALYZER_TRACE_TX_FLUSHED_PIN_PORT, \
                     LOGIC_ANALYZER_TRACE_TX_FLUSHED_PIN_PIN); \
  } while (0)

#define LOGIC_ANALYZER_TRACE_PIN_INIT                                 \
  GPIO_PinModeSet(LOGIC_ANALYZER_TRACE_HEADER_TRANSFER_ISR_PIN_PORT,  \
                  LOGIC_ANALYZER_TRACE_HEADER_TRANSFER_ISR_PIN_PIN,   \
                  gpioModePushPull, 0);                               \
  GPIO_PinModeSet(LOGIC_ANALYZER_TRACE_PAYLOAD_TRANSFER_ISR_PIN_PORT, \
                  LOGIC_ANALYZER_TRACE_PAYLOAD_TRANSFER_ISR_PIN_PIN,  \
                  gpioModePushPull, 0);                               \
  GPIO_PinModeSet(LOGIC_ANALYZER_TRACE_TX_DMA_ARMED_PIN_PORT,         \
                  LOGIC_ANALYZER_TRACE_TX_DMA_ARMED_PIN_PIN,          \
                  gpioModePushPull, 0);                               \
  GPIO_PinModeSet(LOGIC_ANALYZER_TRACE_TX_FLUSHED_PIN_PORT,           \
                  LOGIC_ANALYZER_TRACE_TX_FLUSHED_PIN_PIN,            \
                  gpioModePushPull, 0);

#else

#define LOGIC_ANALYZER_TRACE_HEADER_TRANSFER_ISR_START  (void)0
#define LOGIC_ANALYZER_TRACE_HEADER_TRANSFER_ISR_END    (void)0
#define LOGIC_ANALYZER_TRACE_PAYLOAD_TRANSFER_ISR_START (void)0
#define LOGIC_ANALYZER_TRACE_PAYLOAD_TRANSFER_ISR_END   (void)0
#define LOGIC_ANALYZER_TRACE_TX_DMA_ARMED               (void)0
#define LOGIC_ANALYZER_TRACE_TX_FLUSHED                 (void)0
#define LOGIC_ANALYZER_TRACE_PIN_INIT                   (void)0

#endif

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

static unsigned int rx_dma_channel;
static unsigned int tx_dma_channel;

static LDMA_TransferCfg_t rx_dma_config;
static LDMA_TransferCfg_t tx_dma_config;

// List of "sli_buf_entry_t" which have an EMPTY "sl_cpc_buffer_handle_t" attached to them.
// Those are entries that are available for receiving a frame. When arming a reception,
// the driver picks the first one and configures the DMA to write the data into its
// attached buffer.
static sl_slist_node_t *rx_free_list_head;

// List of "sli_buf_entry_t" which have a "sl_cpc_buffer_handle_t" attached to them.
// Those are entries that have fully received frame written in the attached
// "sl_cpc_buffer_handle_t". They are waiting for the core to pick them up.
static sl_slist_node_t *rx_pending_list_head;

// List of "sli_buf_entry_t" which have a FILLED "sl_cpc_buffer_handle_t" attached to them.
// Those are entries that are waiting for its buffer to be sent on the wire.
static sl_slist_node_t *tx_submitted_list_head;

static uint16_t tx_buf_available_count = SL_CPC_DRV_SPI_TX_QUEUE_SIZE;

// When not null, points to the first entry in "rx_free_list_head" when the driver
// Set itself up to receive a new frame. During the transaction, it is in this entry's
// buffer that the DMA writes the data.
static sl_cpc_buffer_handle_t *currently_receiving_rx_buffer_handle = NULL;

// When not null,
static sl_cpc_buffer_handle_t *currently_transmiting_buffer_handle = NULL;

static bool pending_late_header = false;

static uint64_t header_buffer = 0;

static volatile uint32_t tx_frame_complete = 0;

/***************************************************************************//**
 * DMA descriptors
 ******************************************************************************/

// Reception descriptors
static LDMA_Descriptor_t rx_desc_wait_cs_high_after_header;
static LDMA_Descriptor_t rx_desc_wait_cs_low_before_payload;
static LDMA_Descriptor_t rx_desc_set_irq_high;
static LDMA_Descriptor_t rx_desc_recv_payload;
#if (SLI_CPC_RX_DATA_MAX_LENGTH > LDMA_DESCRIPTOR_MAX_XFER_SIZE)
static LDMA_Descriptor_t rx_desc_recv_payload_large_buf;
#endif
static LDMA_Descriptor_t rx_desc_wait_cs_high_after_payload;
static LDMA_Descriptor_t rx_desc_flush_fifo;
static LDMA_Descriptor_t rx_desc_wait_cs_low_before_header;
static LDMA_Descriptor_t rx_desc_clear_availability_sync_bit;
static LDMA_Descriptor_t rx_desc_set_irq_high_after_header_cs_low;
static LDMA_Descriptor_t rx_desc_recv_header;
#if defined(_SILICON_LABS_32B_SERIES_1)
static LDMA_Descriptor_t rx_desc_clear_cs_and_cs_inv_sync_bits;
#endif
#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_5)
static LDMA_Descriptor_t rx_desc_inv_cs_before_payload;
static LDMA_Descriptor_t rx_desc_revert_cs_before_payload;
static LDMA_Descriptor_t rx_desc_inv_cs_before_header;
static LDMA_Descriptor_t rx_desc_revert_cs_before_header;
#endif
// Transmission descriptors
static LDMA_Descriptor_t tx_desc_wait_availability_sync_bit;
static LDMA_Descriptor_t tx_desc_set_irq_low;
static LDMA_Descriptor_t tx_desc_xfer_header;
static LDMA_Descriptor_t tx_desc_wait_header_tranfered;
static LDMA_Descriptor_t tx_desc_set_tx_frame_complete_variable_after_header;
static LDMA_Descriptor_t tx_desc_xfer_payload;
#if (SLI_CPC_RX_DATA_MAX_LENGTH > LDMA_DESCRIPTOR_MAX_XFER_SIZE)
static LDMA_Descriptor_t tx_desc_xfer_payload_large_buf;
#endif
#if (SL_CPC_ENDPOINT_SECURITY_ENABLED == 1)
static LDMA_Descriptor_t tx_desc_xfer_tag;
#endif
static LDMA_Descriptor_t tx_desc_xfer_checksum;
static LDMA_Descriptor_t tx_desc_wait_checksum_tranfered;
static LDMA_Descriptor_t tx_desc_set_tx_frame_complete_variable_after_checksum;

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/

static void flush_rx(void);
static void flush_tx(void);

static bool rx_dma_callback(unsigned int channel, unsigned int sequenceNo, void *userParam);

static void end_of_header_xfer(void);
static bool end_of_payload_xfer(void);

static void prime_dma_for_transmission(void);

/***************************************************************************/ /**
 * Initialize only the SPI peripheral to be used in a standalone manner
 * (during the bootloader poking)
 ******************************************************************************/
sl_status_t sli_cpc_drv_hw_init(void)
{
  // Enable the clocks of all the peripheral used in this driver
  CMU_ClockEnable(cmuClock_PRS, true);
  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(cmuClock_LDMA, true);
  CMU_ClockEnable(SPI_CMU_CLOCK(SL_CPC_DRV_SPI_PERIPHERAL_NO), true);
#if defined(SL_CPC_DRV_SPI_IS_USART) && defined(_CMU_HFPERCLKEN0_MASK)
  CMU_ClockEnable(cmuClock_HFPER, true);
#endif

  // Set pin modes and drive characteristics for the SPI mode 0
  GPIO_PinModeSet(SL_CPC_DRV_SPI_TX_PORT, SL_CPC_DRV_SPI_TX_PIN, gpioModeInput, 0);
  GPIO_PinModeSet(SL_CPC_DRV_SPI_RX_PORT, SL_CPC_DRV_SPI_RX_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(SL_CPC_DRV_SPI_CLK_PORT, SL_CPC_DRV_SPI_CLK_PIN, gpioModeInputPull, 0);
  GPIO_PinModeSet(SL_CPC_DRV_SPI_CS_PORT, SL_CPC_DRV_SPI_CS_PIN, gpioModeInputPull, 1);
  // Initialize IRQ pin, initial value is HIGH (no frame to send)
  GPIO_PinModeSet(SL_CPC_DRV_SPI_RX_IRQ_PORT, SL_CPC_DRV_SPI_RX_IRQ_PIN, gpioModePushPull, 1);

  // Configure the GPIO routing to the SPI peripheral
  {
  #if defined(_USART_ROUTELOC0_MASK)
    SL_CPC_DRV_SPI_PERIPHERAL->ROUTELOC0 =
      (SL_CPC_DRV_SPI_TX_LOC  << _USART_ROUTELOC0_TXLOC_SHIFT)
      | (SL_CPC_DRV_SPI_RX_LOC  << _USART_ROUTELOC0_RXLOC_SHIFT)
      | (SL_CPC_DRV_SPI_CLK_LOC << _USART_ROUTELOC0_CLKLOC_SHIFT)
      | (SL_CPC_DRV_SPI_CS_LOC  << _USART_ROUTELOC0_CSLOC_SHIFT);

    SL_CPC_DRV_SPI_PERIPHERAL->ROUTEPEN =
      USART_ROUTEPEN_TXPEN
      | USART_ROUTEPEN_RXPEN
      | USART_ROUTEPEN_CLKPEN
      | USART_ROUTEPEN_CSPEN;
  #elif defined(_GPIO_USART_ROUTEEN_MASK) || defined(_GPIO_EUSART_ROUTEEN_MASK)
    // Route MISO to the EUSART
    GPIO->EUSART_OR_USART_ROUTE[SL_CPC_DRV_SPI_PERIPHERAL_NO].TXROUTE =
      ((uint32_t)SL_CPC_DRV_SPI_TX_PORT << GPIO_PORT_SHIFT(TXROUTE))
      | ((uint32_t)SL_CPC_DRV_SPI_TX_PIN  << GPIO_PIN_SHIFT(TXROUTE));

    // Route MOSI to the EUSART
    GPIO->EUSART_OR_USART_ROUTE[SL_CPC_DRV_SPI_PERIPHERAL_NO].RXROUTE =
      ((uint32_t)SL_CPC_DRV_SPI_RX_PORT << GPIO_PORT_SHIFT(RXROUTE))
      | ((uint32_t)SL_CPC_DRV_SPI_RX_PIN  << GPIO_PIN_SHIFT(RXROUTE));

    // Route SCLK to the EUSART
  #if defined(SL_CPC_DRV_SPI_IS_USART)
    GPIO->EUSART_OR_USART_ROUTE[SL_CPC_DRV_SPI_PERIPHERAL_NO].CLKROUTE =
      ((uint32_t)SL_CPC_DRV_SPI_CLK_PORT << GPIO_PORT_SHIFT(CLKROUTE))
      | ((uint32_t)SL_CPC_DRV_SPI_CLK_PIN  << GPIO_PIN_SHIFT(CLKROUTE));
  #elif defined(SL_CPC_DRV_SPI_IS_EUSART)
    GPIO->EUSART_OR_USART_ROUTE[SL_CPC_DRV_SPI_PERIPHERAL_NO].SCLKROUTE =
      ((uint32_t)SL_CPC_DRV_SPI_CLK_PORT << GPIO_PORT_SHIFT(SCLKROUTE))
      | ((uint32_t)SL_CPC_DRV_SPI_CLK_PIN  << GPIO_PIN_SHIFT(SCLKROUTE));
  #endif

    // Route CS to the EUSART
    GPIO->EUSART_OR_USART_ROUTE[SL_CPC_DRV_SPI_PERIPHERAL_NO].CSROUTE =
      ((uint32_t)SL_CPC_DRV_SPI_CS_PORT << GPIO_PORT_SHIFT(CSROUTE))
      | ((uint32_t)SL_CPC_DRV_SPI_CS_PIN  << GPIO_PIN_SHIFT(CSROUTE));

    // Activate the routes to the EUSART
    GPIO->EUSART_OR_USART_ROUTE[SL_CPC_DRV_SPI_PERIPHERAL_NO].ROUTEEN = GPIO_ROUTEEN;
  #endif
  }

  // Init of the E/USART
  {
  #if defined(SL_CPC_DRV_SPI_IS_EUSART)
    // MSB first, EUSART in SPI mode
    SL_CPC_DRV_SPI_PERIPHERAL->CFG0 = EUSART_CFG0_MSBF | EUSART_CFG0_SYNC;

    // TX and RX FIFO level interrupt of 1.
    SL_CPC_DRV_SPI_PERIPHERAL->CFG1 = EUSART_CFG1_RXFIW_ONEFRAME | EUSART_CFG1_TXFIW_ONEFRAME;

    // Slave mode 0 (cpol 0, cpha 0)
    SL_CPC_DRV_SPI_PERIPHERAL->CFG2 = EUSART_CFG2_FORCELOAD | EUSART_CFG2_CLKPHA_SAMPLELEADING | EUSART_CFG2_CLKPOL_IDLELOW | _EUSART_CFG2_MASTER_SLAVE;

    // 8 bits per byte
    SL_CPC_DRV_SPI_PERIPHERAL->FRAMECFG = EUSART_FRAMECFG_DATABITS_EIGHT;

    // 0s sent when nothing to send
    SL_CPC_DRV_SPI_PERIPHERAL->DTXDATCFG = EUSART_DTXDATCFG_DTXDAT_DEFAULT;

    // Default setup window of 5 is recommended when bitrate < 5Mhz
    // TODO Implement logic for CPC-468 to set to recommended value 4 if the negotiated bitrate is > 5MHz
    SL_CPC_DRV_SPI_PERIPHERAL->TIMINGCFG = EUSART_TIMINGCFG_SETUPWINDOW_DEFAULT;

    // Enable EUSART
    SL_CPC_DRV_SPI_PERIPHERAL->EN = EUSART_EN_EN;

    // Enable RX and TX
    SL_CPC_DRV_SPI_PERIPHERAL->CMD = EUSART_CMD_RXEN | EUSART_CMD_TXEN;

    // Activate Load Error and TX overflow interrupts for monitoring
    SL_CPC_DRV_SPI_PERIPHERAL->IEN = EUSART_IF_LOADERR | EUSART_IF_TXOF;

    // Wait until all operations are synch'ed
    while (SL_CPC_DRV_SPI_PERIPHERAL->SYNCBUSY & _EUSART_SYNCBUSY_MASK) ;

  #elif defined(SL_CPC_DRV_SPI_IS_USART)

    #if defined(USART_EN_EN)
    SL_CPC_DRV_SPI_PERIPHERAL->EN_SET = USART_EN_EN;
    #endif

    SL_CPC_DRV_SPI_PERIPHERAL->CTRL = USART_CTRL_SYNC | USART_CTRL_CLKPOL_IDLELOW | USART_CTRL_CLKPHA_SAMPLELEADING | USART_CTRL_MSBF;

    SL_CPC_DRV_SPI_PERIPHERAL->FRAME = USART_FRAME_DATABITS_EIGHT;

    SL_CPC_DRV_SPI_PERIPHERAL->CMD = USART_CMD_RXEN | USART_CMD_TXEN;
  #endif
  }

  return SL_STATUS_OK;
}

/***************************************************************************/ /**
 * Initialize the rest of the driver after the SPI peripheral has been
 * initialized in sli_cpc_drv_hw_init.
 ******************************************************************************/
sl_status_t sli_cpc_drv_init(void)
{
  // Initialize the lists
  {
    sl_slist_init(&rx_free_list_head);
    sl_slist_init(&rx_pending_list_head);
    sl_slist_init(&tx_submitted_list_head);

    for (uint32_t buf_cnt = 0; buf_cnt < SL_CPC_DRV_SPI_RX_QUEUE_SIZE; buf_cnt++) {
      sl_cpc_buffer_handle_t *buffer_handle;
      if (sli_cpc_get_buffer_handle_for_rx(&buffer_handle) != SL_STATUS_OK) {
        EFM_ASSERT(false);
        return SL_STATUS_ALLOCATION_FAILED;
      }
      sli_cpc_push_driver_buffer_handle(&rx_free_list_head, buffer_handle);
    }

    tx_buf_available_count = SL_CPC_DRV_SPI_TX_QUEUE_SIZE;
  }

  // Init the DMA and allocate two channels
  {
    Ecode_t ret;
    ret = DMADRV_Init();
    if (ret != ECODE_EMDRV_DMADRV_OK && ret != ECODE_EMDRV_DMADRV_ALREADY_INITIALIZED) {
      EFM_ASSERT(false);
      return SL_STATUS_INITIALIZATION;
    }

    ret = DMADRV_AllocateChannel(&tx_dma_channel, NULL);
    if (ret != ECODE_EMDRV_DMADRV_OK) {
      EFM_ASSERT(false);
      return SL_STATUS_ALLOCATION_FAILED;
    }

    ret = DMADRV_AllocateChannel(&rx_dma_channel, NULL);
    if (ret != ECODE_EMDRV_DMADRV_OK) {
      EFM_ASSERT(false);
      return SL_STATUS_ALLOCATION_FAILED;
    }

    //The DMA channel that serves receive buffer should have higher priority than the DMA channel that serves transmit buffer.
    if (rx_dma_channel > tx_dma_channel) {
      // A lower number DMA channel is higher priority. If the allocated DMA channels from SPIDRV init gave us
      // a inverted priority, switch those channels. They have been allocated, its safe to just switch them.
      unsigned int tmp = rx_dma_channel;
      rx_dma_channel = tx_dma_channel;
      tx_dma_channel = tmp;
    }
  }

  // Setup a PRS channel to connect the E/USART TXC signal
  {
    PRS_Signal_t signal;

    // Make sure the SYNCTRIG/PRS combination is within bound
    EFM_ASSERT(SL_CPC_DRV_SPI_TXC_SYNCTRIG_PRS_CH <= 7);

    // Retrieve the connected signal
    #if defined(_PRS_ASYNC_CH_CTRL_SOURCESEL_MASK)
    signal = (PRS_Signal_t) (PRS->ASYNC_CH[SL_CPC_DRV_SPI_TXC_SYNCTRIG_PRS_CH].CTRL
                             & (_PRS_ASYNC_CH_CTRL_SOURCESEL_MASK | _PRS_ASYNC_CH_CTRL_SIGSEL_MASK));
    #else
    signal = (PRS_Signal_t) (PRS->CH[SL_CPC_DRV_SPI_TXC_SYNCTRIG_PRS_CH].CTRL
                             & (_PRS_CH_CTRL_SOURCESEL_MASK | _PRS_CH_CTRL_SIGSEL_MASK));
    #endif

    // The configured TXC SYNCTRIG bit works with its corresponding PRS Channel number. Make sure that PRS Channel is not used.
    EFM_ASSERT(signal == prsSignalNone);

    // The PRS Channel was free, now configure it
    PRS_ConnectSignal(SL_CPC_DRV_SPI_TXC_SYNCTRIG_PRS_CH, prsTypeAsync, PRS_SIGNAL_USART(SL_CPC_DRV_SPI_PERIPHERAL_NO, TXC));
  }

  // This driver needs to route the incoming Chip Select signal to a PRS channel.
  // Setup a PRS channel to connect the UART Chip Select signal
  {
    PRS_Signal_t signal;

    // Make sure the SYNCTRIG/PRS combination is within bound
    EFM_ASSERT(SL_CPC_DRV_SPI_CS_SYNCTRIG_PRS_CH <= 7);

    #if defined(_PRS_ASYNC_CH_CTRL_SOURCESEL_MASK)
    signal = (PRS_Signal_t) (PRS->ASYNC_CH[SL_CPC_DRV_SPI_CS_SYNCTRIG_PRS_CH].CTRL
                             & (_PRS_ASYNC_CH_CTRL_SOURCESEL_MASK | _PRS_ASYNC_CH_CTRL_SIGSEL_MASK));
    #else
    signal = (PRS_Signal_t) (PRS->CH[SL_CPC_DRV_SPI_CS_SYNCTRIG_PRS_CH].CTRL
                             & (_PRS_CH_CTRL_SOURCESEL_MASK | _PRS_CH_CTRL_SIGSEL_MASK));
    #endif

    // The configured CS SYNCTRIG bit works with its corresponding PRS Channel number. Make sure that PRS Channel is not used.
    EFM_ASSERT(signal == prsSignalNone);

    #if defined(SL_CPC_DRV_SPI_IS_EUSART)
    {
      // EUSART is only present on Series 2
      // It has a quirk that needs to be dealt with differently then USART
      // The only way of routing the incoming CS signal to a PRS channel is
      // via the External Interrupt route.

      // We need to chose an EXTI interrupt number for the CS pin.
      // The limitation is the following :
      // pins 0-3   (interrupt number 0-3)
      // pins 4-7   (interrupt number 4-7)

      #if (SL_CPC_DRV_SPI_CS_EXTI_NUMBER >= 0 && SL_CPC_DRV_SPI_CS_EXTI_NUMBER <= 3)
        #if !(SL_CPC_DRV_SPI_CS_PIN >= 0 && SL_CPC_DRV_SPI_CS_PIN <= 3)
          #error "For an EXTI0..3, only pin Px0..3 can be used as CS"
        #endif
      #elif (SL_CPC_DRV_SPI_CS_EXTI_NUMBER >= 4 && SL_CPC_DRV_SPI_CS_EXTI_NUMBER <= 7)
        #if !(SL_CPC_DRV_SPI_CS_PIN >= 4 && SL_CPC_DRV_SPI_CS_PIN <= 7)
          #error "For an EXTI4..7, only pin Px4..7 can be used as CS"
        #endif
      #else
        #error "Only EXTI0..7 can be used because the PRS only support those as inputs"
      #endif

      GPIO_ExtIntConfig(SL_CPC_DRV_SPI_CS_PORT,
                        SL_CPC_DRV_SPI_CS_PIN,
                        SL_CPC_DRV_SPI_CS_EXTI_NUMBER,
                        false, // don't care about rising edge
                        false, // don't care about falling edge
                        false); // don't enable the interrupt; we don't care about
                                // the interrupt, only configuring the signal path
                                // from the pin to a EXTI channel, which in turn
                                // can be selected as input to a PRS channel.

      PRS_ConnectSignal(SL_CPC_DRV_SPI_CS_SYNCTRIG_PRS_CH, prsTypeAsync, PRS_SIGNAL_EXTI(SL_CPC_DRV_SPI_CS_EXTI_NUMBER));
    }
    #elif defined(SL_CPC_DRV_SPI_IS_USART)
    {
      // For the USART, unlike the EUSART, the CS signal can be retrieved via the prsSignalUSARTx_CS. No need to
      // pass through the EXTI mechanism
      PRS_ConnectSignal(SL_CPC_DRV_SPI_CS_SYNCTRIG_PRS_CH, prsTypeAsync, PRS_SIGNAL_USART(SL_CPC_DRV_SPI_PERIPHERAL_NO, CS));

      #if defined(_SILICON_LABS_32B_SERIES_1)
      // For USART on Series 1, have an additional PRS channel connected to the same CS signal.
      // The reason why a second channel PRS with the same signal connected to it is needed will be further
      // explained in the RX DMA chain initialization below.

      // Make sure the SYNCTRIG/PRS combination is within bound
      EFM_ASSERT(SL_CPC_DRV_SPI_CS_INV_SYNCTRIG_PRS_CH <= 7);

      PRS_Signal_t signal = (PRS_Signal_t) (PRS->CH[SL_CPC_DRV_SPI_CS_INV_SYNCTRIG_PRS_CH].CTRL
                                            & (_PRS_CH_CTRL_SOURCESEL_MASK | _PRS_CH_CTRL_SIGSEL_MASK));

      // The configured CS_INV SYNCTRIG bit works with its corresponding PRS Channel number. Make sure that PRS Channel is not used.
      EFM_ASSERT(signal == prsSignalNone);

      PRS_ConnectSignal(SL_CPC_DRV_SPI_CS_INV_SYNCTRIG_PRS_CH, prsTypeAsync, PRS_SIGNAL_USART(SL_CPC_DRV_SPI_PERIPHERAL_NO, CS));

      // Now, this channel needs to be inverted
      PRS->CH[SL_CPC_DRV_SPI_CS_INV_SYNCTRIG_PRS_CH].CTRL |= PRS_CH_CTRL_INV;
      #endif
    }
    #endif
  }

  // SPI DMA configuration
  {
    // Create DMA configs for TX/RX from the DMA-REQ signals the SPIDRV gave us
    rx_dma_config = (LDMA_TransferCfg_t)LDMA_TRANSFER_CFG_PERIPHERAL(DMA_SIGNAL_RX(SL_CPC_DRV_SPI_PERIPHERAL_NO));
    tx_dma_config = (LDMA_TransferCfg_t)LDMA_TRANSFER_CFG_PERIPHERAL(DMA_SIGNAL_TX(SL_CPC_DRV_SPI_PERIPHERAL_NO));

    rx_dma_config.ldmaDbgHalt = true;
    tx_dma_config.ldmaDbgHalt = true;
  }

  // Configure the LDMA SYNCTRIG mechanism
  {
    // There is a crucial difference in the LDMA between Series 1 and 2 :
    // On Series 2, a unique PRS channel is able to Set AND Clear its corresponding
    // LDMA SYNCTRIG bit on the rising or falling edge. This allows the incoming CS signal
    // to set its SYNC bit on the rising edge, and clear it on the falling edge.
    // This cannot be done on Series 1 : A PRS channel can either SET its SYNC bit on the
    // rising edge, OR CLEAR it on the rising edge, not both at the same time.
    //
    // To achieve the same result we need in Series 2, with Series 1 we need a second
    // PRS channel where we invert CS and use that in the descriptor chain to sync
    // like we need on high and lows of CS.

    #if defined(_SILICON_LABS_32B_SERIES_2)
    {
      // Enable the "usart_txc_prs_channel" PRS channel (a.k.a the USART TXC signal) to
      // be able to SET its corresponding SYNCTRIG[] bit
      LDMA->SYNCHWEN_SET = (1UL << SL_CPC_DRV_SPI_TXC_SYNCTRIG_PRS_CH) << _LDMA_SYNCHWEN_SYNCSETEN_SHIFT;
      // The "usart_txc_prs_channel" SYNCTRIG bit don't need SYNCHWSEL modification (rising-edge to SET by default)

      // Enable the "usart_cs_prs_channel" PRS channel (a.k.a the USART CS signal) to
      // be able to SET and CLEAR its corresponding SYNCTRIG[] bit
      LDMA->SYNCHWEN_SET =   ((1UL << SL_CPC_DRV_SPI_CS_SYNCTRIG_PRS_CH) << _LDMA_SYNCHWEN_SYNCSETEN_SHIFT)  // CS will SET its SYNC bit
                           | ((1UL << SL_CPC_DRV_SPI_CS_SYNCTRIG_PRS_CH) << _LDMA_SYNCHWEN_SYNCCLREN_SHIFT); // CS will [also] CLEAR its SYNC bit.

      // Configure how USART CS will set/clear its SYNC bit
      // With this configuration, the SYNCTRIG[usart_txc_prs_channel] bit will reflect the state of the USART CS line :
      // == 1 when CS is high, and == 0 when CS is low
      LDMA->SYNCHWSEL_SET =   ((_LDMA_SYNCHWSEL_SYNCSETEDGE_RISE << SL_CPC_DRV_SPI_CS_SYNCTRIG_PRS_CH) << _LDMA_SYNCHWSEL_SYNCSETEDGE_SHIFT)  // CS will SET its SYNC bit on rising edge
                            | ((_LDMA_SYNCHWSEL_SYNCSETEDGE_FALL << SL_CPC_DRV_SPI_CS_SYNCTRIG_PRS_CH) << _LDMA_SYNCHWSEL_SYNCCLREDGE_SHIFT); // CS will CLR its SYNC bit on falling edge
    }
    #elif defined(_SILICON_LABS_32B_SERIES_1)
    {
      // Enable all 3 PRS channels to SET their corresponding LDMA SYNCTRIG bit.
      LDMA->CTRL |=    (1UL << SL_CPC_DRV_SPI_TXC_SYNCTRIG_PRS_CH)
                    | (1UL << SL_CPC_DRV_SPI_CS_SYNCTRIG_PRS_CH)
                    | (1UL << SL_CPC_DRV_SPI_CS_INV_SYNCTRIG_PRS_CH) << _LDMA_CTRL_SYNCPRSSETEN_SHIFT;
    }
    #endif
  }

  // Prepare the reception DMA descriptor chain.
  {
    #define ENABLE_SYNC_ON_CS_PRS_CHANNEL     (1 << SL_CPC_DRV_SPI_CS_SYNCTRIG_PRS_CH)
    #define CLEAR_CS_PRS_CHANNEL_UPON_LOAD    (1 << SL_CPC_DRV_SPI_CS_SYNCTRIG_PRS_CH)
    #define SYNC_ON_CS_PRS_CHANNEL_EQUAL_ONE  (1 << SL_CPC_DRV_SPI_CS_SYNCTRIG_PRS_CH)
    #define SYNC_ON_CS_PRS_CHANNEL_EQUAL_ZERO (0 << SL_CPC_DRV_SPI_CS_SYNCTRIG_PRS_CH)

    #if defined(_SILICON_LABS_32B_SERIES_1)
    #define ENABLE_SYNC_ON_CS_INVERTED_PRS_CHANNEL     (1 << SL_CPC_DRV_SPI_CS_INV_SYNCTRIG_PRS_CH)
    #define SYNC_ON_CS_INVERTED_PRS_CHANNEL_EQUAL_ONE  (1 << SL_CPC_DRV_SPI_CS_INV_SYNCTRIG_PRS_CH)
    #define CLEAR_CS_INVERTED_PRS_CHANNEL_UPON_LOAD    (1 << SL_CPC_DRV_SPI_CS_INV_SYNCTRIG_PRS_CH)
    #endif

    // Sync descriptor to wait for the CS high between the header and the payload
    {
      rx_desc_wait_cs_high_after_header = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKABS_SYNC(
        0x0,
        0x0,
        SYNC_ON_CS_PRS_CHANNEL_EQUAL_ONE,
        ENABLE_SYNC_ON_CS_PRS_CHANNEL);
    }
    #if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_5)
    // The LDMA on xG25 has an issue where the SYNC descriptors do not
    // block when waiting for a 0 SYNC signal. To circumvent this, we always wait on
    // a 1 SYNC signal by inverting CS using the PRS logical functions, so that
    // when when CS goes low, the SYNC signal will go high.

    // Fixed branching of previous descriptor
    rx_desc_wait_cs_high_after_header.sync.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_inv_cs_before_payload);

    // Invert CS polarity using PRS FNSEL
    {
      rx_desc_inv_cs_before_payload = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKABS_WRITE(
        _PRS_ASYNC_CH_CTRL_FNSEL_MASK, // Toggle FNSEL bits of PRS ASYNC Channel register to invert logic
        &PRS->ASYNC_CH_TGL[SL_CPC_DRV_SPI_CS_SYNCTRIG_PRS_CH].CTRL
        );

      // Fixed branching
      rx_desc_inv_cs_before_payload.wri.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_wait_cs_low_before_payload);
    }

    // Sync descriptor to wait for the CS low before payload clocking
    {
      rx_desc_wait_cs_low_before_payload = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKABS_SYNC(
        0x0,
      #if defined(_SILICON_LABS_32B_SERIES_1)
        CLEAR_CS_INVERTED_PRS_CHANNEL_UPON_LOAD,
        SYNC_ON_CS_INVERTED_PRS_CHANNEL_EQUAL_ONE,
        ENABLE_SYNC_ON_CS_INVERTED_PRS_CHANNEL);
      #elif defined(_SILICON_LABS_32B_SERIES_2)
        0x0,
        SYNC_ON_CS_PRS_CHANNEL_EQUAL_ONE,
        ENABLE_SYNC_ON_CS_PRS_CHANNEL);
      #endif

      // Fixed branching
      rx_desc_wait_cs_low_before_payload.sync.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_revert_cs_before_payload);
    }

    // Revert CS polarity using PRS FNSEL
    {
      rx_desc_revert_cs_before_payload = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKABS_WRITE(
        _PRS_ASYNC_CH_CTRL_FNSEL_MASK, // Toggle FNSEL bits of PRS ASYNC Channel register to invert logic
        &PRS->ASYNC_CH_TGL[SL_CPC_DRV_SPI_CS_SYNCTRIG_PRS_CH].CTRL
        );

      // Fixed branching
      rx_desc_revert_cs_before_payload.wri.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_set_irq_high);
    }
    #else
    // Fixed branching of previous descriptor
    rx_desc_wait_cs_high_after_header.sync.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_wait_cs_low_before_payload);

    // Sync descriptor to wait for the CS low before payload clocking
    {
      rx_desc_wait_cs_low_before_payload = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKABS_SYNC(
        0x0,
      #if defined(_SILICON_LABS_32B_SERIES_1)
        CLEAR_CS_INVERTED_PRS_CHANNEL_UPON_LOAD,
        SYNC_ON_CS_INVERTED_PRS_CHANNEL_EQUAL_ONE,
        ENABLE_SYNC_ON_CS_INVERTED_PRS_CHANNEL);
      #elif defined(_SILICON_LABS_32B_SERIES_2)
        0x0,
        SYNC_ON_CS_PRS_CHANNEL_EQUAL_ZERO,
        ENABLE_SYNC_ON_CS_PRS_CHANNEL);
      #endif

      // Fixed branching
      rx_desc_wait_cs_low_before_payload.sync.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_set_irq_high);
    }
    #endif

    // WRITE descriptor to set the IRQ pin high after the falling edge of CS of payload
    {
      rx_desc_set_irq_high = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKABS_WRITE(
        IRQ_PIN_SET_MASK,
        irq_set_addr);

      // This descriptor's branching address is computed before each time this chain is armed
      // If there is a payload to receive, it branches to the payload descriptor
      // If there is NO payload to receive, it branches to the sync descriptor that waits
      // for the rising edge of CS after the payload
    }

    // Transfer descriptor to receive the payload
    {
      rx_desc_recv_payload = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKREL_P2M_BYTE(
        &(SL_CPC_DRV_SPI_PERIPHERAL->RXDATA),
        0, // place holder for data pointer
        0, // place holder for length
        1); // Will be overridden below

      // The macro LDMA_DESCRIPTOR_LINKABS_P2M_BYTE does not exist for whatever reason.
      // Force this descriptor to use absolute linking
      rx_desc_recv_payload.xfer.linkMode = ldmaLinkModeAbs;

      // Override .doneIfs; the interrupts are generated somewhere else
      rx_desc_recv_payload.xfer.doneIfs = 0;

      // When NOT large buffer, this descriptor's branching remains fixed
      // When large buffer, the branching is computed before each arming
      rx_desc_recv_payload.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_wait_cs_high_after_payload);
    }

    #if (SLI_CPC_RX_DATA_MAX_LENGTH > LDMA_DESCRIPTOR_MAX_XFER_SIZE)
    // Transfer descriptor to receive the large buffer payload
    {
      rx_desc_recv_payload_large_buf = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKREL_P2M_BYTE(
        &(SL_CPC_DRV_SPI_PERIPHERAL->RXDATA),
        0, // place holder for data pointer
        0, // place holder for length
        1); // Will be overridden below

      // The macro LDMA_DESCRIPTOR_LINKABS_P2M_BYTE does not exist for whatever reason.
      // Force this descriptor to use absolute linking
      rx_desc_recv_payload_large_buf.xfer.linkMode = ldmaLinkModeAbs;

      // Override .doneIfs; the interrupts are generated somewhere else
      rx_desc_recv_payload_large_buf.xfer.doneIfs = 0;

      // Fixed branching
      rx_desc_recv_payload_large_buf.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_wait_cs_high_after_payload);
    }
    #endif

    // Sync descriptor to wait for the rising edge of the UART CS following the payload.
    {
      rx_desc_wait_cs_high_after_payload = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKABS_SYNC(
        0x0,
      #if defined(_SILICON_LABS_32B_SERIES_1)
        CLEAR_CS_PRS_CHANNEL_UPON_LOAD,
      #elif defined(_SILICON_LABS_32B_SERIES_2)
        0x0,
      #endif
        SYNC_ON_CS_PRS_CHANNEL_EQUAL_ONE,
        ENABLE_SYNC_ON_CS_PRS_CHANNEL);

      // Override .doneIfs : Yes, generate an interrupt when this descriptor unblocks
      rx_desc_wait_cs_high_after_payload.sync.doneIfs = 1;

      // Fixed branching
      rx_desc_wait_cs_high_after_payload.sync.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_flush_fifo);
    }

    // Transfer descriptor to flush the USART FIFO
    // We don't need the bytes clocked from the primary all the time from the previous
    // payload descriptor(s) (i.e. when zero header or corrupt header received). They
    // still end up in the FIFO if they are not read (which is what we do by skipping linking
    // payload descriptor(s) in the cases listed previously). We need to flush them from the
    // FIFO to prevent those bytes from being read as the following header.
    {
      // Dummy byte to throw away the bytes from the FIFO
      static uint8_t dummy_byte;

      #if defined(SL_CPC_DRV_SPI_IS_EUSART)
      #define FIFO_SIZE 16 // EUSART's FIFO size
      #elif defined(SL_CPC_DRV_SPI_IS_USART)
      #define FIFO_SIZE 3  // USART's FIFO size
      #endif

      // Even if we read from a peripheral register, use a M2M descriptor because we want all those
      // reads to execute right now without a peripheral trigger
      rx_desc_flush_fifo = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKABS_M2M_BYTE(
        &(SL_CPC_DRV_SPI_PERIPHERAL->RXDATA),
        &dummy_byte,
        FIFO_SIZE);

      // As opposed to a M2M, keep the source to be the RXDATA register (we flush the FIFO)
      rx_desc_flush_fifo.xfer.srcInc = ldmaCtrlSrcIncNone;

      // As opposed to a M2M, keep the destination to be the void byte. We throw away those bytes
      rx_desc_flush_fifo.xfer.dstInc = ldmaCtrlSrcIncNone;
    }

    #if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_5)
    // The LDMA on xG25 has an issue where the SYNC descriptors do not
    // block when waiting for a 0 SYNC signal. To circumvent this, we always wait on
    // a 1 SYNC signal by inverting CS using the PRS logical functions, so that
    // when when CS goes low, the SYNC signal will go high.

    // Fixed branching of previous descriptor
    rx_desc_flush_fifo.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_inv_cs_before_header);

    // Invert CS polarity using PRS FNSEL
    {
      rx_desc_inv_cs_before_header = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKABS_WRITE(
        _PRS_ASYNC_CH_CTRL_FNSEL_MASK,  // Toggle FNSEL bits of PRS ASYNC Channel register to invert logic
        &PRS->ASYNC_CH_TGL[SL_CPC_DRV_SPI_CS_SYNCTRIG_PRS_CH].CTRL
        );

      // Fixed branching
      rx_desc_inv_cs_before_header.wri.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_wait_cs_low_before_header);
    }

    // Sync descriptor to wait for the falling edge of the UART CS of the next header.
    {
      rx_desc_wait_cs_low_before_header = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKABS_SYNC(
        TX_READY_WINDOW_TRIG_BIT_MASK, // Set TX READY WINDOW trig bit when loaded
      #if defined(_SILICON_LABS_32B_SERIES_1)
        CLEAR_CS_INVERTED_PRS_CHANNEL_UPON_LOAD,
        SYNC_ON_CS_INVERTED_PRS_CHANNEL_EQUAL_ONE,
        ENABLE_SYNC_ON_CS_INVERTED_PRS_CHANNEL);
      #elif defined(_SILICON_LABS_32B_SERIES_2)
        0x0,
        SYNC_ON_CS_PRS_CHANNEL_EQUAL_ONE,
        ENABLE_SYNC_ON_CS_PRS_CHANNEL);
      #endif

      // Fixed branching
      rx_desc_wait_cs_low_before_header.sync.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_revert_cs_before_header);
    }

    // Revert CS polarity using PRS FNSEL
    {
      // Toggle FNSEL bits of PRS ASYNC Channel register to invert logic
      rx_desc_revert_cs_before_header = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKABS_WRITE(
        _PRS_ASYNC_CH_CTRL_FNSEL_MASK,
        &PRS->ASYNC_CH_TGL[SL_CPC_DRV_SPI_CS_SYNCTRIG_PRS_CH].CTRL
        );
      // Fixed branching
      rx_desc_revert_cs_before_header.wri.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_clear_availability_sync_bit);
    }
    #else
    // Fixed branching of previous descriptor
    rx_desc_flush_fifo.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_wait_cs_low_before_header);

    // Sync descriptor to wait for the falling edge of the UART CS of the next header.
    {
      rx_desc_wait_cs_low_before_header = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKABS_SYNC(
        TX_READY_WINDOW_TRIG_BIT_MASK, // Set TX READY WINDOW trig bit when loaded
      #if defined(_SILICON_LABS_32B_SERIES_1)
        CLEAR_CS_INVERTED_PRS_CHANNEL_UPON_LOAD,
        SYNC_ON_CS_INVERTED_PRS_CHANNEL_EQUAL_ONE,
        ENABLE_SYNC_ON_CS_INVERTED_PRS_CHANNEL);
      #elif defined(_SILICON_LABS_32B_SERIES_2)
        0x0,
        SYNC_ON_CS_PRS_CHANNEL_EQUAL_ZERO,
        ENABLE_SYNC_ON_CS_PRS_CHANNEL);
      #endif

      // Fixed branching
      rx_desc_wait_cs_low_before_header.sync.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_clear_availability_sync_bit);
    }
    #endif

    // Sync descriptor to clear the SYNCTRIG[7] bit
    {
      rx_desc_clear_availability_sync_bit = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKABS_SYNC(
        0x0,
        TX_READY_WINDOW_TRIG_BIT_MASK, // Clears TX READY WINDOW trig bit when loaded
        0x0,
        0x0);

      // Fixed branching
      rx_desc_clear_availability_sync_bit.sync.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_set_irq_high_after_header_cs_low);
    }

    // Immediate write to set the IRQ pin high.
    {
      rx_desc_set_irq_high_after_header_cs_low = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKABS_WRITE(
        IRQ_PIN_SET_MASK,
        irq_set_addr);

      // Fixed branching
      rx_desc_set_irq_high_after_header_cs_low.sync.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_recv_header);
    }

    // Transfer the received header. Because its a _SINGLE_ descriptor, the
    // .doneIfs bit is set and an interrupt will fire after it gets executed
    {
      rx_desc_recv_header = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(
        &(SL_CPC_DRV_SPI_PERIPHERAL->RXDATA),
        &header_buffer,
        SLI_CPC_HDLC_HEADER_RAW_SIZE);

      #if defined(_SILICON_LABS_32B_SERIES_1)
      // In case of Series 1, this descriptor is not the end of the chain and needs to
      // branch to the following one
      rx_desc_recv_header.wri.link = 1;

      // The macro LDMA_DESCRIPTOR_LINKABS_P2M_BYTE does not exist for whatever reason.
      // Force this descriptor to use absolute linking
      rx_desc_recv_header.xfer.linkMode = ldmaLinkModeAbs;

      // Override .doneIfs : Don't trigger an interrupt at the end of this descriptor
      rx_desc_recv_header.xfer.doneIfs = 0;

      // Fixed branching
      rx_desc_recv_header.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_clear_cs_and_cs_inv_sync_bits);
      #endif
    }

    #if defined(_SILICON_LABS_32B_SERIES_1)
    // SYNC descriptor that just clears the CS and CS_INV sync bits
    // With Series 2, the CS SYNC bit sets and clears itself because the LDMA supports that feature
    // With Series 1, that feature does not exist. 2 SYNC bits are used for the CS tracking, the second one is inverted
    // Each time a rising/falling edge is recorded, that SYNC bit needs to be 'manually' cleared afterward.
    // Each SYNC descriptor that syncs on the 2 CS SYNC bits clears the bit of the prior sync upon being loaded.
    // The first SYNC on CS doesn't have a SYNC before it to clear its bit because its the first one.
    // This last SYNC descriptor therefore do that : its job is to clear the CS SYNC bit for the
    // first SYNC descriptor when this chain is re-armed.
    {
      rx_desc_clear_cs_and_cs_inv_sync_bits = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_SINGLE_SYNC(
        0,
        CLEAR_CS_INVERTED_PRS_CHANNEL_UPON_LOAD | CLEAR_CS_PRS_CHANNEL_UPON_LOAD,
        0,
        0);

      // Override the .doneIfs bit that normally comes with a _SINGLE_ descriptor.
      // The "end of chain" interrupt is already set by the preceding descriptor
      rx_desc_clear_cs_and_cs_inv_sync_bits.sync.doneIfs = 0;
    }
    #endif
  }

  // Prepare the transmission DMA descriptor chain
  {
    #define ENABLE_SYNC_ON_TX_READY_WINDOW     TX_READY_WINDOW_TRIG_BIT_MASK
    #define SYNC_ON_TX_READY_WINDOW_EQUAL_ONE  TX_READY_WINDOW_TRIG_BIT_MASK

    // Sync descriptor to wait to be in the TX_AVAILABLE region
    {
      tx_desc_wait_availability_sync_bit = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKABS_SYNC(
        0x0,
        0x0,
        SYNC_ON_TX_READY_WINDOW_EQUAL_ONE,
        ENABLE_SYNC_ON_TX_READY_WINDOW);

      // Fixed branching
      tx_desc_wait_availability_sync_bit.sync.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&tx_desc_set_irq_low);
    }

    // Set the IRQ pin LOW
    {
      tx_desc_set_irq_low = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKABS_WRITE(
        IRQ_PIN_SET_MASK,
        irq_clr_addr);

      tx_desc_set_irq_low.wri.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&tx_desc_xfer_header);
    }

    // Send header
    {
      tx_desc_xfer_header = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKREL_M2P_BYTE(
        NULL, //Place holder for header buffer address
        &(SL_CPC_DRV_SPI_PERIPHERAL->TXDATA),
        SLI_CPC_HDLC_HEADER_RAW_SIZE,
        1); // Overridden below

      // The macro LDMA_DESCRIPTOR_LINKABS_M2P_BYTE does not exist for whatever reason.
      // Force this descriptor to use absolute linking
      tx_desc_xfer_header.xfer.linkMode = ldmaLinkModeAbs;

      // Override .doneIfs : Don't trigger an interrupt at the end of this descriptor
      tx_desc_xfer_header.xfer.doneIfs = 0;

      // conditional branching
    }

    // Branch if no payload

    // Wait until the header has been sent on the wire
    {
      #define ENABLE_SYNC_ON_TXC_PRS_CHANNEL     (1 << SL_CPC_DRV_SPI_TXC_SYNCTRIG_PRS_CH)
      #define SYNC_ON_TXC_PRS_CHANNEL_EQUAL_ONE  (1 << SL_CPC_DRV_SPI_TXC_SYNCTRIG_PRS_CH)
      #define CLEAR_TXC_PRS_CHANNEL_UPON_LOAD    (1 << SL_CPC_DRV_SPI_TXC_SYNCTRIG_PRS_CH)

      tx_desc_wait_header_tranfered = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKABS_SYNC(
        0x0,
        CLEAR_TXC_PRS_CHANNEL_UPON_LOAD,
        SYNC_ON_TXC_PRS_CHANNEL_EQUAL_ONE,
        ENABLE_SYNC_ON_TXC_PRS_CHANNEL);

      // Fixed branching
      tx_desc_wait_header_tranfered.sync.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&tx_desc_set_tx_frame_complete_variable_after_header);
    }

    // Write descriptor to set the "tx_frame_complete" variable to 1.
    {
      tx_desc_set_tx_frame_complete_variable_after_header = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_SINGLE_WRITE(
        1,
        &tx_frame_complete);

      // If this descriptor has been branched to, this is the end of the chain
      tx_desc_set_tx_frame_complete_variable_after_header.wri.doneIfs = 0;
    }

    // Branch if there is a payload

    // Transfer descriptor for the payload
    {
      tx_desc_xfer_payload = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKREL_M2P_BYTE(
        NULL, // Place holder for the payload address
        &(SL_CPC_DRV_SPI_PERIPHERAL->TXDATA),
        0, // Place holder for the payload length
        1); // Overridden below

      // The macro LDMA_DESCRIPTOR_LINKABS_M2P_BYTE does not exist for whatever reason.
      // Force this descriptor to use absolute linking
      tx_desc_xfer_payload.xfer.linkMode = ldmaLinkModeAbs;

      // Override .doneIfs : Don't trigger an interrupt at the end of this descriptor
      tx_desc_xfer_payload.xfer.doneIfs = 0;

      // In the case of NO large buffer and NO security, this descriptor branches  to the
      // send checksum descriptor no matter what, else its link address is computed each
      // time the chain is arms. In the case it never changes, set it right now
      tx_desc_xfer_payload.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&tx_desc_xfer_checksum);
    }

    #if (SLI_CPC_RX_DATA_MAX_LENGTH > LDMA_DESCRIPTOR_MAX_XFER_SIZE)
    // Transfer descriptor for the large buffer payload
    {
      tx_desc_xfer_payload_large_buf = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKREL_M2P_BYTE(
        NULL, // Place holder for the payload address
        &(SL_CPC_DRV_SPI_PERIPHERAL->TXDATA),
        0, // Place holder for the payload length
        1);

      // The macro LDMA_DESCRIPTOR_LINKABS_M2P_BYTE does not exist for whatever reason.
      // Force this descriptor to use absolute linking
      tx_desc_xfer_payload_large_buf.xfer.linkMode = ldmaLinkModeAbs;

      // Override .doneIfs : Don't trigger an interrupt at the end of this descriptor
      tx_desc_xfer_payload_large_buf.xfer.doneIfs = 0;

      // In the case of large buffer and NO security, this descriptor branches  to the
      // send checksum descriptor no matter what, else its link address is computed each
      // time the chain is arms. In the case it never changes, set it right now
      tx_desc_xfer_payload_large_buf.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&tx_desc_xfer_checksum);
    }
    #endif

    #if (SL_CPC_ENDPOINT_SECURITY_ENABLED == 1)
    // If the security is enabled and there is a security tag to send, send it before the payload checksum.
    {
      tx_desc_xfer_tag = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKREL_M2P_BYTE(
        NULL,                                /* Place holder for the tag address */
        &(SL_CPC_DRV_SPI_PERIPHERAL->TXDATA),
        SLI_SECURITY_TAG_LENGTH_BYTES,
        1u);

      // The macro LDMA_DESCRIPTOR_LINKABS_M2P_BYTE does not exist for whatever reason.
      // Force this descriptor to use absolute linking
      tx_desc_xfer_tag.xfer.linkMode = ldmaLinkModeAbs;

      // Override .doneIfs : Don't trigger an interrupt at the end of this descriptor
      tx_desc_xfer_tag.xfer.doneIfs = 0;

      // Fixed branching
      tx_desc_xfer_tag.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&tx_desc_xfer_checksum);
    }
    #endif

    // Send the checksum
    {
      tx_desc_xfer_checksum = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKREL_M2P_BYTE(
        NULL, // Placeholder for the checksum
        &(SL_CPC_DRV_SPI_PERIPHERAL->TXDATA),
        SLI_CPC_HDLC_FCS_SIZE,
        1u);

      // The macro LDMA_DESCRIPTOR_LINKABS_M2P_BYTE does not exist for whatever reason.
      // Force this descriptor to use absolute linking
      tx_desc_xfer_checksum.xfer.linkMode = ldmaLinkModeAbs;

      // Override .doneIfs : Don't trigger an interrupt at the end of this descriptor
      tx_desc_xfer_checksum.xfer.doneIfs = 0;

      // Fixed branching
      tx_desc_xfer_checksum.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&tx_desc_wait_checksum_tranfered);
    }

    // Wait until the checksum has been sent on the wire
    {
      tx_desc_wait_checksum_tranfered = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_LINKABS_SYNC(
        0x0,
        CLEAR_TXC_PRS_CHANNEL_UPON_LOAD,
        SYNC_ON_TXC_PRS_CHANNEL_EQUAL_ONE,
        ENABLE_SYNC_ON_TXC_PRS_CHANNEL);

      // Fixed branching
      tx_desc_wait_checksum_tranfered.sync.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&tx_desc_set_tx_frame_complete_variable_after_checksum);
    }

    // Write descriptor to set the "tx_frame_complete" variable to 1.
    {
      tx_desc_set_tx_frame_complete_variable_after_checksum = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_SINGLE_WRITE(
        1,
        &tx_frame_complete);

      // If this descriptor has been branched to, this is the end of the chain
      tx_desc_set_tx_frame_complete_variable_after_checksum.wri.doneIfs = 0;
    }
  }

  LOGIC_ANALYZER_TRACE_PIN_INIT;

  #if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
  sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
  #endif

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Start reception
 ******************************************************************************/
sl_status_t sli_cpc_drv_start_rx(void)
{
  // The initial reception priming is special because we prime the RX DMA channel from
  // a descriptor in the middle of the chain.
  Ecode_t ecode = DMADRV_LdmaStartTransfer(rx_dma_channel,
                                           &rx_dma_config,
                                           &rx_desc_flush_fifo, // This is important
                                           rx_dma_callback,
                                           (void*)true); // Give a special "initial_pass" = true parameter.
  EFM_ASSERT(ecode == ECODE_OK);
  return SL_STATUS_OK;
}

/***************************************************************************/ /**
 * Gets CPC driver capabilities.
 ******************************************************************************/
sl_status_t sli_cpc_drv_get_capabilities(sli_cpc_drv_capabilities_t *capabilities)
{
  if (capabilities == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  *capabilities = (sli_cpc_drv_capabilities_t){.use_raw_rx_buffer = false,
                                               .preprocess_hdlc_header = true,
                                               .uart_flowcontrol = false };
  return SL_STATUS_OK;
}

/***************************************************************************/ /**
 * Read bytes from SPI.
 ******************************************************************************/
sl_status_t sli_cpc_drv_read_data(sl_cpc_buffer_handle_t **buffer_handle)
{
  sl_status_t status;
  MCU_DECLARE_IRQ_STATE;

  sl_cpc_buffer_handle_t *new_buffer_handle;

  MCU_ENTER_ATOMIC();
  sl_cpc_buffer_handle_t *pending_buffer_handle = sli_cpc_pop_driver_buffer_handle(&rx_pending_list_head);
  if (pending_buffer_handle == NULL) {
    MCU_EXIT_ATOMIC();
    return SL_STATUS_EMPTY;
  }
  MCU_EXIT_ATOMIC();

  *buffer_handle = pending_buffer_handle;

  MCU_ENTER_ATOMIC();
  status = sli_cpc_get_buffer_handle_for_rx(&new_buffer_handle);
  if (status == SL_STATUS_OK) {
    sli_cpc_push_driver_buffer_handle(&rx_free_list_head, new_buffer_handle);
  }
  MCU_EXIT_ATOMIC();

  return SL_STATUS_OK;
}

/**************************************************************************/ /**
 * Write bytes to SPI.
 ******************************************************************************/
sl_status_t sli_cpc_drv_transmit_data(sl_cpc_buffer_handle_t *buffer_handle)
{
  MCU_DECLARE_IRQ_STATE;

  MCU_ENTER_ATOMIC();
  if (tx_buf_available_count == 0) {
    MCU_EXIT_ATOMIC();
    return SL_STATUS_NOT_READY;
  }
  tx_buf_available_count--;
  sli_cpc_push_back_driver_buffer_handle(&tx_submitted_list_head, buffer_handle);

  prime_dma_for_transmission();

  MCU_EXIT_ATOMIC();

  return SL_STATUS_OK;
}

/**************************************************************************/ /**
 * Checks if driver is ready to transmit.
 ******************************************************************************/
bool sli_cpc_drv_is_transmit_ready(void)
{
  uint16_t tx_free;
  MCU_ATOMIC_LOAD(tx_free, tx_buf_available_count);
  return (tx_free > 0);
}

/***************************************************************************//**
 * Get currently configured bus bitrate
 ******************************************************************************/
uint32_t sli_cpc_drv_get_bus_bitrate(void)
{
  // Stub function : In the case of the SPI driver, this value is meaningless
  return 0;
}

/***************************************************************************//**
 * Get maximum bus bitrate
 ******************************************************************************/
uint32_t sli_cpc_drv_get_bus_max_bitrate(void)
{
  uint32_t max_bitrate;

#if defined(SL_CPC_DRV_SPI_IS_USART)
  // The max speed of the USART in mode secondary is the peripheral clock feeding the USART / 6
  max_bitrate = CMU_ClockFreqGet(cmuClock_USART0) / 10; // Use cmuClock_USART0 for any USART as they are all connected to the same PCLK

#elif defined(SL_CPC_DRV_SPI_IS_EUSART)
  // The max bitrate of the EUSART in secondary mode is 10MHz no matter what.
  max_bitrate = 10000000;
#endif

  return max_bitrate;
}

/**************************************************************************/ /**
 * Notification when RX buffer handle becomes free.
 ******************************************************************************/
void sli_cpc_drv_on_rx_buffer_free(void)
{
  sl_status_t status;
  MCU_DECLARE_IRQ_STATE;

  MCU_ENTER_ATOMIC();
  do {
    sl_cpc_buffer_handle_t *buffer_handle;

    status = sli_cpc_get_buffer_handle_for_rx(&buffer_handle);
    if (status == SL_STATUS_OK) {
      sli_cpc_push_driver_buffer_handle(&rx_free_list_head, buffer_handle);
    }
  } while (status == SL_STATUS_OK);
  MCU_EXIT_ATOMIC();
}

/***************************************************************************//**
 * Reconfigure only what needs to be reconfigured in the RX DMA descriptor chain
 * and start the RX DMA channel
 ******************************************************************************/
static void prime_dma_for_reception(size_t payload_size, enum header_situation last_header_situation)
{
  if (last_header_situation == HEADER_NULL || last_header_situation == HEADER_CORRUPTED) {
    // We received a header full of 0s or a corrupted header.
    // First, its not worth retrieving a rx_buffer_entry just yet.
    // Second, we will configure the reception descriptor chain
    // to skip the payload(s) descriptors
    rx_desc_set_irq_high.wri.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_wait_cs_high_after_payload);

    goto start_transfer;
  }

  // Since we received a valid header, we are going to need a rx_entry to place it into
  if (currently_receiving_rx_buffer_handle == NULL) {
    currently_receiving_rx_buffer_handle = sli_cpc_pop_driver_buffer_handle(&rx_free_list_head);
  }

  if (currently_receiving_rx_buffer_handle == NULL) {
    // running out of buffer. We will drop this frame.
    // Configure the reception chain to skip the payload.
    // Having currently_receiving_rx_buffer_handle == NULL when flushing_rx will drop this frame
    rx_desc_set_irq_high.wri.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_wait_cs_high_after_payload);
    SL_CPC_JOURNAL_RECORD_DEBUG("[DRV] Dropping frame due to lack of RX buffers", __LINE__);

    goto start_transfer;
  }

  // Copy the valid header from the static header buffer into the buffer_handle
  *(uint64_t*)currently_receiving_rx_buffer_handle->hdlc_header = header_buffer;

  if (payload_size == 0) {
    // If we won't receive a payload, skip over the payload descriptor(s)
    rx_desc_set_irq_high.wri.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_wait_cs_high_after_payload);

    // Keep indent small, we are done so go to the end of this function directly
    goto start_transfer;
  }

  // If we expect to receive a payload, configure the reception descriptor chain
  // to include the payload reception descriptor
  rx_desc_set_irq_high.wri.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_recv_payload);

  // Set the RX buffer address in the payload descriptor
  rx_desc_recv_payload.xfer.dstAddr = (uint32_t) currently_receiving_rx_buffer_handle->data;

  #if (SLI_CPC_RX_DATA_MAX_LENGTH <= LDMA_DESCRIPTOR_MAX_XFER_SIZE) // Non-large-buffer
  {
    // Configure the length of the payload to receive
    rx_desc_recv_payload.xfer.xferCnt = payload_size - 1;

    // In non-large-buffer, the branching address of the payload descriptor never changes. Nothing more to do
  }
  #else // Large-buffer
  {
    if (payload_size <= LDMA_DESCRIPTOR_MAX_XFER_SIZE) {
      // We have large buffer compiled, but this payload doesn't span 2 descriptors.
      // load the first descriptor, and jump over the large-buffer reception descriptor.
      rx_desc_recv_payload.xfer.xferCnt = payload_size - 1;
      rx_desc_recv_payload.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_wait_cs_high_after_payload);
    } else {
      // We have large buffer compiled, and the payload spans the two payload descriptors
      // load the first descriptor to the max, and link to the one right under it
      rx_desc_recv_payload.xfer.xferCnt = LDMA_DESCRIPTOR_MAX_XFER_SIZE - 1;
      rx_desc_recv_payload.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&rx_desc_recv_payload_large_buf);

      // We have large buffer compiled, and the payload spans the two payload descriptors
      // load the first descriptor to the max, and link to the one right under it
      rx_desc_recv_payload_large_buf.xfer.dstAddr = (uint32_t) &((uint8_t*)currently_receiving_rx_buffer_handle->data)[LDMA_DESCRIPTOR_MAX_XFER_SIZE];
      rx_desc_recv_payload_large_buf.xfer.xferCnt = (payload_size - LDMA_DESCRIPTOR_MAX_XFER_SIZE) - 1;
    }
  }
  #endif

  Ecode_t ecode;

  start_transfer:

  ecode = DMADRV_LdmaStartTransfer(rx_dma_channel,
                                   &rx_dma_config,
                                   &rx_desc_wait_cs_high_after_header,
                                   rx_dma_callback,
                                   NULL);
  EFM_ASSERT(ecode == ECODE_OK);
}

/***************************************************************************//**
 * Reconfigure only what needs to be reconfigured in the TX DMA descriptor chain
 * and start the TX DMA channel.
 *
 * We assume the TX DMA channel is not running and we are in interrupt context
 ******************************************************************************/
static void prime_dma_for_transmission(void)
{
  if (currently_transmiting_buffer_handle) {
    // There is already a frame programmed to be sent. Do nothing now, when the
    // frame currently programmed in the TX DMA chain gets tx_flushed(), the
    // frame for which this function was called will be cocked in.
    return;
  }

  // Pick the next frame to send
  currently_transmiting_buffer_handle = SL_SLIST_ENTRY(tx_submitted_list_head, sl_cpc_buffer_handle_t, driver_node);

  // Bug if this function is called but there is nothing in the submitted list
  EFM_ASSERT(currently_transmiting_buffer_handle != NULL);

  #if defined(CPC_TEST_SPI_DRIVER_CRC_ERROR_INJECTION)
  {
    // De-phase a bit
    static size_t count = CPC_TEST_SPI_DRIVER_CRC_ERROR_INJECTION_FREQUENCY / 4;
    static uint64_t bad_crc_header;

    count++;

    if ( count % CPC_TEST_SPI_DRIVER_CRC_ERROR_INJECTION_FREQUENCY == 0) {
      count = 0;

      printf("Invalidated the transmit header CRC\n");

      // Make a copy of the good header we are going to transmit
      // We have to make a copy, because otherwise if we modify the good header itself,
      // we will retransmit a bad header indefinitely.
      bad_crc_header = *(uint64_t*)currently_transmiting_buffer_handle->hdlc_header;

      // Invert a byte to corrupt the CRC
      ((uint8_t*)&bad_crc_header)[4] = ~((uint8_t*)&bad_crc_header)[4];

      // set header source address to the bad header
      tx_desc_xfer_header.xfer.srcAddr = (uint32_t) &bad_crc_header;
    } else {
      tx_desc_xfer_header.xfer.srcAddr = (uint32_t) currently_transmiting_buffer_handle->hdlc_header;
    }
  }
  #else
  // set header source address
  tx_desc_xfer_header.xfer.srcAddr = (uint32_t) currently_transmiting_buffer_handle->hdlc_header;
  #endif

  if (currently_transmiting_buffer_handle->data_length == 0) {
    tx_desc_xfer_header.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&tx_desc_wait_header_tranfered);

    // Keep indent small, we are done so go to the end of this function directly
    goto start_transfer;
  }

  tx_desc_xfer_header.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&tx_desc_xfer_payload);

  // Set the payload source address
  tx_desc_xfer_payload.xfer.srcAddr = (uint32_t) currently_transmiting_buffer_handle->data;

  #if (SLI_CPC_RX_DATA_MAX_LENGTH <= LDMA_DESCRIPTOR_MAX_XFER_SIZE) //Non-large-buffer
  {
    tx_desc_xfer_payload.xfer.xferCnt = currently_transmiting_buffer_handle->data_length - 1;

    #if (SL_CPC_ENDPOINT_SECURITY_ENABLED == 1)
    {
      if (currently_transmiting_buffer_handle->security_tag) {
        tx_desc_xfer_payload.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&tx_desc_xfer_tag);
        tx_desc_xfer_tag.xfer.srcAddr = (uint32_t) currently_transmiting_buffer_handle->security_tag;
      } else {
        tx_desc_xfer_payload.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&tx_desc_xfer_checksum);
      }
      tx_desc_xfer_checksum.xfer.srcAddr = (uint32_t) currently_transmiting_buffer_handle->fcs;
    }
    #endif
  }
  #else // Large-buffer
  {
    if (currently_transmiting_buffer_handle->data_length <= LDMA_DESCRIPTOR_MAX_XFER_SIZE) {
      // We have large buffer compiled, but this payload doesn't span 2 descriptors.
      // load the first descriptor, and jump over the one that follows.
      tx_desc_xfer_payload.xfer.xferCnt = currently_transmiting_buffer_handle->data_length - 1;

      #if (SL_CPC_ENDPOINT_SECURITY_ENABLED == 1)
      {
        if (currently_transmiting_buffer_handle->security_tag) {
          tx_desc_xfer_payload.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&tx_desc_xfer_tag);
          tx_desc_xfer_tag.xfer.srcAddr = (uint32_t) currently_transmiting_buffer_handle->security_tag;
        } else {
          tx_desc_xfer_payload.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&tx_desc_xfer_checksum);
        }
      }
      #else
      {
        tx_desc_xfer_payload.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&tx_desc_xfer_checksum);
      }
      #endif
    } else {
      // We have large buffer compiled, and the payload spans the two payload descriptors
      // load the first payload descriptor to the max, and link it to the large buffer payload descriptor
      tx_desc_xfer_payload.xfer.xferCnt = LDMA_DESCRIPTOR_MAX_XFER_SIZE - 1;
      tx_desc_xfer_payload.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&tx_desc_xfer_payload_large_buf);

      // Load the large buffer payload descriptor with the remaining data
      tx_desc_xfer_payload_large_buf.xfer.srcAddr = (uint32_t) &((uint8_t*)currently_transmiting_buffer_handle->data)[LDMA_DESCRIPTOR_MAX_XFER_SIZE];
      tx_desc_xfer_payload_large_buf.xfer.xferCnt = (currently_transmiting_buffer_handle->data_length - LDMA_DESCRIPTOR_MAX_XFER_SIZE) - 1;

      #if (SL_CPC_ENDPOINT_SECURITY_ENABLED == 1)
      {
        if (currently_transmiting_buffer_handle->security_tag) {
          tx_desc_xfer_payload_large_buf.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&tx_desc_xfer_tag);
          tx_desc_xfer_tag.xfer.srcAddr = (uint32_t) currently_transmiting_buffer_handle->security_tag;
        } else {
          tx_desc_xfer_payload_large_buf.xfer.linkAddr = LDMA_DESCRIPTOR_LINKABS_ADDR_TO_LINKADDR(&tx_desc_xfer_checksum);
        }
      }
      #endif
    }
  }
  #endif

  // Finally load the checksum descriptor
  tx_desc_xfer_checksum.xfer.srcAddr = (uint32_t) currently_transmiting_buffer_handle->fcs;

  Ecode_t ecode;

  start_transfer:

  ecode = DMADRV_LdmaStartTransfer(tx_dma_channel,
                                   &tx_dma_config,
                                   &tx_desc_wait_availability_sync_bit,
                                   NULL,
                                   NULL);
  EFM_ASSERT(ecode == ECODE_OK);

  LOGIC_ANALYZER_TRACE_TX_DMA_ARMED;
}

/***************************************************************************//**
 * This is the callback called by the DMADRV IRQ handler when the RX DMA channel
 * fires an interrupt. Note that thanks to the synchronization between TX and RX
 * channels, only the RX channel triggers interrupts, not the TX channel; it
 * silently finishes its descriptor chain
 ******************************************************************************/
static bool rx_dma_callback(unsigned int channel, unsigned int sequenceNo, void *userParam)
{
  EFM_ASSERT(channel == rx_dma_channel);

  // The very first time this callback is called, the sequenceNumber needs to be
  // swapped. When starting a transfer, the DMADRV resets to 1 the sequence
  // number, but the first interrupt will be for a header, and it will be number
  // 2, except the first time, so override it to 2.
  bool initial_pass = (bool) userParam;
  if (initial_pass) {
    sequenceNo = 2;
  }

  if (sequenceNo == 2) {
    end_of_header_xfer();
  } else if (sequenceNo == 1) {
    if (end_of_payload_xfer()) {
      end_of_header_xfer();
    }
  } else {
    EFM_ASSERT(false);
  }

  return false;
}

static enum header_situation received_header_situation;

static void end_of_header_xfer(void)
{
  size_t rx_payload_length = 0;
  MCU_DECLARE_IRQ_STATE;

  MCU_ENTER_ATOMIC();

  LOGIC_ANALYZER_TRACE_HEADER_TRANSFER_ISR_START;

  #if defined(CPC_TEST_SPI_DRIVER_CRC_ERROR_INJECTION)
  {
    static size_t count = 0;

    if (header_buffer != 0) {
      count++;

      if ( count % CPC_TEST_SPI_DRIVER_CRC_ERROR_INJECTION_FREQUENCY == 0) {
        count = 0;

        printf("Invalidated the CRC\n");

        // Mess with the CRC by inverting a byte
        ((uint8_t*)&header_buffer)[4] = ~((uint8_t*)&header_buffer)[4];
      }
    }
  }
  #endif

  if (header_buffer == 0) {
    received_header_situation = HEADER_NULL;
  } else {
    bool valid_header = sli_cpc_validate_crc_sw((void*)&header_buffer,
                                                SLI_CPC_HDLC_HEADER_SIZE,
                                                sli_cpc_hdlc_get_hcs((void*)&header_buffer));
    if (valid_header) {
      received_header_situation = HEADER_VALID;
      rx_payload_length = sli_cpc_hdlc_get_length((void*)&header_buffer);
    } else {
      received_header_situation = HEADER_CORRUPTED;
    }
  }

  prime_dma_for_reception(rx_payload_length, received_header_situation);

  // Clear the IRQ line to send the signal to the primary that we are done with
  // this interrupt critical section. The primary is now free to start clocking
  // us data.
  GPIO_PinOutClear(SL_CPC_DRV_SPI_RX_IRQ_PORT, SL_CPC_DRV_SPI_RX_IRQ_PIN);

  LOGIC_ANALYZER_TRACE_HEADER_TRANSFER_ISR_END;

  MCU_EXIT_ATOMIC();
}

/***************************************************************************/ /**
 * Notifies the core when a frame has been sent on the wire.
 *
 * @return true  : "end_of_header_xfer" needs to be tail chained to this routine
 *         false : The DMA callback can return after this function
 ******************************************************************************/
static bool end_of_payload_xfer(void)
{
  MCU_DECLARE_IRQ_STATE;

  MCU_ENTER_ATOMIC();

  LOGIC_ANALYZER_TRACE_PAYLOAD_TRANSFER_ISR_START;

  // Check if we had a late header transmission situation
  if (currently_transmiting_buffer_handle) {
    // At this point, a header have been exchanged and we realize a TX entry is registered for transmission
    // We need to know is this "currently_transmiting_buffer_handle" had the chance to have its header clocked in the header
    // exchange that just happened
    if (tx_frame_complete == 0) {
      // This "currently_transmiting_buffer_handle" has arrived lated. Yes it is at this point the current active TX frame, but
      // at the moment the primary started clocking the header, its header did't go through. Mark this current
      // TX entry transmission as a "pending_late_header" so that we don't try to flush this "currently_transmiting_buffer_handle"
      // as having been sent on the wire.
      pending_late_header = true;
    }
  }

  // Reset that variable which is set to 1 by the TX DMA chain
  tx_frame_complete = 0;

  flush_rx();
  flush_tx();

  if (tx_submitted_list_head) {
    if (pending_late_header) {
      pending_late_header = false;
    } else {
      prime_dma_for_transmission();
    }
  }

  LOGIC_ANALYZER_TRACE_PAYLOAD_TRANSFER_ISR_END;

  if (LDMA_TransferDone(rx_dma_channel)) {
    MCU_EXIT_ATOMIC();
    return true;
  } else {
    MCU_EXIT_ATOMIC();
    return false;
  }
}

/***************************************************************************/ /**
 * Notifies the core when a frame has been sent on the wire.
 ******************************************************************************/
static void flush_rx(void)
{
  if (currently_receiving_rx_buffer_handle && received_header_situation == HEADER_VALID) {
    #if defined(CPC_TEST_SPI_DRIVER_CRC_ERROR_INJECTION)
    {
      // Start the payload CRC error injection out of phase with the header error
      static size_t count = CPC_TEST_SPI_DRIVER_CRC_ERROR_INJECTION_FREQUENCY / 2;

      if (sli_cpc_hdlc_get_length((void*)&header_buffer) != 0) {
        count++;

        if ( count % CPC_TEST_SPI_DRIVER_CRC_ERROR_INJECTION_FREQUENCY == 0) {
          count = 0;

          printf("Invalidated the payload CRC\n");

          //Mess with the first byte of the payload CRC by inverting it
          ((uint8_t*)currently_receiving_rx_buffer_handle->data)[0] = ~((uint8_t*)currently_receiving_rx_buffer_handle->data)[0];
        }
      }
    }
    #endif

    sli_cpc_push_back_driver_buffer_handle(&rx_pending_list_head, currently_receiving_rx_buffer_handle);

    currently_receiving_rx_buffer_handle = NULL;

    sli_cpc_notify_rx_data_from_drv();
  }
}

/***************************************************************************/ /**
 * Notifies the core when a frame has been sent on the wire.
 ******************************************************************************/
static void flush_tx(void)
{
  MCU_DECLARE_IRQ_STATE;
  if (currently_transmiting_buffer_handle == NULL) {
    // Nothing to notify the core about if there is no current TX entry
    return;
  }

  if (pending_late_header) {
    // There is a TX entry, but we realized the header couldn't be sent in time
    return;
  }

  // Remove the first entry from the TX submitted list.
  sl_cpc_buffer_handle_t *buffer_handle = sli_cpc_pop_driver_buffer_handle(&tx_submitted_list_head);

  // Paranoia. The first entry in the TX submitted list NEEDS to be the currently_transmiting_buffer_handle
  EFM_ASSERT(buffer_handle == currently_transmiting_buffer_handle);

  // Notify the core that this entry has been sent on the wire. It will detach its buffer
  sli_cpc_notify_tx_data_by_drv(buffer_handle);

  MCU_ENTER_ATOMIC();
  ++tx_buf_available_count;
  EFM_ASSERT(tx_buf_available_count <= SL_CPC_DRV_SPI_TX_QUEUE_SIZE);
  MCU_EXIT_ATOMIC();

  // Important to set this back to NULL
  currently_transmiting_buffer_handle = NULL;

  LOGIC_ANALYZER_TRACE_TX_FLUSHED;
}
