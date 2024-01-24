#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <em_device.h>
#include <em_gpio.h>
#include <em_core.h>
#include <em_ldma.h>
#include "sl_component_catalog.h"
#include "sl_uartdrv_instances.h"
#include "sl_uartdrv_usart_vcom_config.h"
#include "sl_btctrl_linklayer.h"
#include "sl_hci_common_transport.h"
#include "sl_hci_uart.h"

#define UART_RX_BUFFER_CHUNK_SIZE   128
#define UART_RX_CHUNKS_N            3
#define UART_RX_BUFFER_SIZE         (UART_RX_CHUNKS_N * UART_RX_BUFFER_CHUNK_SIZE)
#define LDMA_RX_DESCRIPTORS_N       6

static bool sleep_disabled = false;
static UARTDRV_Handle_t handle = NULL;
static LDMA_Descriptor_t ldma_rx_descriptors[LDMA_RX_DESCRIPTORS_N];
static void (*tx_complete)(uint32_t);
static uint8_t rx_buffer[UART_RX_BUFFER_SIZE];
static uint16_t rx_write_idx;
static uint16_t rx_read_idx;

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
// Power manager transition events of interest.
#define POWER_MANAGER_EVENTS_OF_INTEREST            \
  (SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM1   \
   | SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM2 \
   | SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM1  \
   | SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM2)

static void energy_mode_transition_cb(sl_power_manager_em_t from,
                                      sl_power_manager_em_t to);

static sl_power_manager_em_transition_event_handle_t pm_handle;
static sl_power_manager_em_transition_event_info_t pm_event_info =
{ POWER_MANAGER_EVENTS_OF_INTEREST, energy_mode_transition_cb };
#endif // SL_CATALOG_POWER_MANAGER_PRESENT

static void start_rx(UARTDRV_Handle_t handle);
static void tx_callback(UARTDRV_Handle_t handle, Ecode_t status, uint8_t *buffer, UARTDRV_Count_t count);
static void enable_usart_irq(void);
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
static void energy_mode_transition_cb(sl_power_manager_em_t from,
                                      sl_power_manager_em_t to)
{
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_ATOMIC();

  if (from == SL_POWER_MANAGER_EM0 && to == SL_POWER_MANAGER_EM1) {
    if (sl_hci_uart_rx_buffered_length() > 0 || sleep_disabled) {
      /* Wake the device up immediately by setting the RXFULL interrupt.
         Setting the RXDATAV interrupt does not wake the device up as
         expected, hence why RXFULL is used here. */
      USART_IntEnable(SL_UARTDRV_USART_VCOM_PERIPHERAL, USART_IF_RXFULL);
      USART_IntSet(SL_UARTDRV_USART_VCOM_PERIPHERAL, USART_IF_RXFULL);
    } else {
      USART_IntClear(SL_UARTDRV_USART_VCOM_PERIPHERAL, USART_IF_RXDATAV);
      USART_IntEnable(SL_UARTDRV_USART_VCOM_PERIPHERAL, USART_IF_RXDATAV);
    }
  }
  if (from <= SL_POWER_MANAGER_EM1 && to == SL_POWER_MANAGER_EM2) {
    USART_Enable(SL_UARTDRV_USART_VCOM_PERIPHERAL, usartDisable);
  }
  if (from == SL_POWER_MANAGER_EM1 && to == SL_POWER_MANAGER_EM0) {
    USART_IntDisable(SL_UARTDRV_USART_VCOM_PERIPHERAL, USART_IF_RXFULL | USART_IF_RXDATAV);
  }
  if (from == SL_POWER_MANAGER_EM2) {
    USART_Enable(SL_UARTDRV_USART_VCOM_PERIPHERAL, usartEnable);
  }

  CORE_EXIT_ATOMIC();
}
#endif // SL_CATALOG_POWER_MANAGER_PRESENT

void sl_hci_uart_init(void)
{
  memset(rx_buffer, 0, sizeof(rx_buffer));
  rx_write_idx = 0;
  rx_read_idx = 0;
  handle = sl_uartdrv_get_default();
  enable_usart_irq();
  start_rx(handle);
  USART_Enable(SL_UARTDRV_USART_VCOM_PERIPHERAL, usartEnable);
  #if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
  sl_power_manager_subscribe_em_transition_event(&pm_handle, &pm_event_info);
  #endif // SL_CATALOG_POWER_MANAGER_PRESENT
}

static void enable_usart_irq(void)
{
#if SL_UARTDRV_USART_VCOM_PERIPHERAL_NO == 0
  NVIC_EnableIRQ(USART0_RX_IRQn);
#elif SL_UARTDRV_USART_VCOM_PERIPHERAL_NO == 1
  NVIC_EnableIRQ(USART1_RX_IRQn);
#elif SL_UARTDRV_USART_VCOM_PERIPHERAL_NO == 2
  NVIC_EnableIRQ(USART2_RX_IRQn);
#elif SL_UARTDRV_USART_VCOM_PERIPHERAL_NO == 3
  NVIC_EnableIRQ(USART3_RX_IRQn);
#else
#error Unsupported VCOM device
#endif
}

#if SL_UARTDRV_USART_VCOM_PERIPHERAL_NO == 0
void USART0_RX_IRQHandler()
#elif SL_UARTDRV_USART_VCOM_PERIPHERAL_NO == 1
void USART1_RX_IRQHandler()
#elif SL_UARTDRV_USART_VCOM_PERIPHERAL_NO == 2
void USART2_RX_IRQHandler()
#elif SL_UARTDRV_USART_VCOM_PERIPHERAL_NO == 3
void USART3_RX_IRQHandler()
#else
#error Unsupported VCOM device
#endif
{
  int irq = USART_IntGet(SL_UARTDRV_USART_VCOM_PERIPHERAL);
  if (irq & USART_IF_RXDATAV) {
    USART_IntClear(SL_UARTDRV_USART_VCOM_PERIPHERAL, USART_IF_RXDATAV);
  } else if (irq & USART_IF_RXFULL) {
    USART_IntClear(SL_UARTDRV_USART_VCOM_PERIPHERAL, USART_IF_RXFULL);
  }
}

// Setup LDMA to transfer data to rx buffer with flow control
// Will still work if remote ignores the RTS line and LL reads HCI fast enough
static void start_rx(UARTDRV_Handle_t handle)
{
  LDMA_Descriptor_t *descr = ldma_rx_descriptors;
  LDMA_TransferCfg_t xferCfg = LDMA_TRANSFER_CFG_PERIPHERAL(handle->rxDmaSignal);
  uint8_t *src = (uint8_t *) &handle->peripheral.uart->RXDATA;
  const uint32_t size = UART_RX_BUFFER_CHUNK_SIZE;
#ifdef _SILICON_LABS_32B_SERIES_2
  // better to use CTRLX_SET so LDMA can't accidentally overwrite other bits
  volatile uint32_t* uartCfgPtr = &handle->peripheral.uart->CTRLX_SET;
  const uint32_t setRts = USART_CTRLX_RTSINV; // invert signal logic to pull high RTS
#endif
#ifdef _SILICON_LABS_32B_SERIES_1 /* series 1 doesn't have SET/CLR registers */
  volatile uint32_t* uartCfgPtr = &handle->peripheral.uart->CTRLX;
  const uint32_t setRts = handle->peripheral.uart->CTRLX | USART_CTRLX_RTSINV;
#endif
  // in these templates link address points to next descriptor
  LDMA_Descriptor_t xferTemplate = LDMA_DESCRIPTOR_LINKREL_P2M_BYTE(src, NULL, size, 1);
  xferTemplate.xfer.doneIfs = 0; // don't trigger interrupt
  const LDMA_Descriptor_t wriTemplate = LDMA_DESCRIPTOR_LINKREL_WRITE(setRts, uartCfgPtr, 1);

  // each XFER descriptor writes to its 1/3 of the buffer
  descr[0] = xferTemplate;
  descr[0].xfer.dstAddr = (uint32_t) &rx_buffer[0];
  descr[2] = xferTemplate;
  descr[2].xfer.dstAddr = (uint32_t) &rx_buffer[size];
  descr[4] = xferTemplate;
  descr[4].xfer.dstAddr = (uint32_t) &rx_buffer[2 * size];

  // create intermediate WRI descriptors to stop data from remote
  descr[1] = wriTemplate;
  descr[3] = wriTemplate;
  // last descriptor links to 1st one
  descr[5] = wriTemplate;
  descr[5].wri.linkAddr = -(LDMA_RX_DESCRIPTORS_N - 1)
                          * LDMA_DESCRIPTOR_NON_EXTEND_SIZE_WORD;

  LDMA_StartTransfer(handle->rxDmaCh, &xferCfg, descr);
}

/**
 * @brief set rx_write_idx to the current value
 */
static void update_buffer_status(UARTDRV_Handle_t handle)
{
  uint16_t dma_idx;
  uint32_t remaining;
  LDMA_Descriptor_t *link;

  // find current descriptor based on the link address
  // (redo if DMA moved to next descriptor)
  do {
    // NOTE: `LINK` field doesn't point exactly to next descriptor, but pointer
    // difference will still work because integer division truncates results
    link = (LDMA_Descriptor_t *) LDMA->CH[handle->rxDmaCh].LINK;
    remaining = LDMA_TransferRemainingCount(handle->rxDmaCh);
  } while (link != (LDMA_Descriptor_t *) LDMA->CH[handle->rxDmaCh].LINK);

  // use fact that every descriptor points to next one cyclically
  dma_idx = link - ldma_rx_descriptors;
  dma_idx = (dma_idx + LDMA_RX_DESCRIPTORS_N - 1) % LDMA_RX_DESCRIPTORS_N; // dma_idx--

  if (dma_idx % 2 == 0) {
    dma_idx = (dma_idx / 2) * UART_RX_BUFFER_CHUNK_SIZE + (UART_RX_BUFFER_CHUNK_SIZE - remaining);
  } else {
    dma_idx = (dma_idx / 2) * UART_RX_BUFFER_CHUNK_SIZE;
  }
  rx_write_idx = dma_idx;
}

void sl_hci_disable_sleep(bool set_sleep_disabled)
{
  sleep_disabled = set_sleep_disabled;
}

static uint16_t readable_bytes(uint16_t read_idx, uint16_t write_idx, uint16_t size)
{
  int d = write_idx - read_idx;

  if (d < 0) {
    d += size;
  }

  return d;
}

int sl_hci_uart_read(uint8_t *data, uint16_t len)
{
  uint16_t bytes_left;
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_ATOMIC();

  update_buffer_status(handle);

  CORE_EXIT_ATOMIC();

  const uint16_t can_read = readable_bytes(rx_read_idx, rx_write_idx, UART_RX_BUFFER_SIZE);
  if (len > can_read) {
    len = can_read;
  }
  bytes_left = len;

  const uint8_t old_read_chunk = rx_read_idx / UART_RX_BUFFER_CHUNK_SIZE;
  while (bytes_left > 0) {
    uint16_t bytes;
    if (bytes_left < UART_RX_BUFFER_SIZE - rx_read_idx) {
      bytes = bytes_left;
    } else {
      bytes = UART_RX_BUFFER_SIZE - rx_read_idx;
    }
    memcpy(data, &rx_buffer[rx_read_idx], bytes);
    data += bytes;
    rx_read_idx += bytes;
    if (rx_read_idx >= UART_RX_BUFFER_SIZE) { // wrap index
      rx_read_idx = 0;
    }
    bytes_left -= bytes;
  }

  // pull down RTS (allow remote to send data) if write ptr is far away enough
  // * assuming write ptr doesn't overtake read ptr (because of rts)
  // * assuming remote sends at most 1 chunk after rts is raised
  const uint8_t write_chunk = rx_write_idx / UART_RX_BUFFER_CHUNK_SIZE;
  const uint8_t read_chunk = rx_read_idx / UART_RX_BUFFER_CHUNK_SIZE;
  if (old_read_chunk != read_chunk // crossed chunk border?
      && (read_chunk == write_chunk // write chunk in current read chunk or next one?
          || (read_chunk + 1) % UART_RX_CHUNKS_N == write_chunk)) {
#ifdef _SILICON_LABS_32B_SERIES_2
    handle->peripheral.uart->CTRLX_CLR = USART_CTRLX_RTSINV;
#endif
#ifdef _SILICON_LABS_32B_SERIES_1 /* series 1 doesn't have SET/CLR registers */
    handle->peripheral.uart->CTRLX &= ~USART_CTRLX_RTSINV;
#endif
  }

  return len;
}

/* Peek how much data buffered in rx that can be immediately read out */
int sl_hci_uart_rx_buffered_length()
{
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_ATOMIC();

  update_buffer_status(handle);

  CORE_EXIT_ATOMIC();

  return readable_bytes(rx_read_idx, rx_write_idx, UART_RX_BUFFER_SIZE);
}

static void tx_callback(UARTDRV_Handle_t handle, Ecode_t status, uint8_t *buffer, UARTDRV_Count_t count)
{
  (void)handle;
  (void)status;
  (void)buffer;
  (void)count;
  if (tx_complete != NULL) {
    // Ignore UART callback status
    tx_complete(SL_STATUS_OK);
  }
}

Ecode_t sl_hci_uart_write(uint8_t *data, uint16_t len, void (*callback)(uint32_t))
{
  Ecode_t status;
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_ATOMIC();

  tx_complete = callback;
  status = UARTDRV_Transmit(handle, data, len, tx_callback);

  CORE_EXIT_ATOMIC();
  return status;
}

void sl_btctrl_hci_transport_get_port_pin(uint8_t *port, uint8_t *pin)
{
  *port = SL_UARTDRV_USART_VCOM_RX_PORT;
  *pin = SL_UARTDRV_USART_VCOM_RX_PIN;
}
