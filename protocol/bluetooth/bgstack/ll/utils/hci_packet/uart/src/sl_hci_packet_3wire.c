#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sl_common.h"
#include "sl_hci_common_transport.h"
#include "sl_hci_uart.h"
#include "sl_btctrl_hci_packet.h"
#include "sl_sleeptimer.h"
#include "sl_hci_packet_3wire_config.h"
// Only VCOM instance is supported.
#include "sl_uartdrv_usart_vcom_config.h"

// Special characters of the SLIP layer.
#define SLIP_DELIM      0xc0
#define SLIP_ESC        0xdb
#define SLIP_ESC_DELIM  0xdc
#define SLIP_ESC_ESC    0xdd

// Packet payload length is represented on 12 bits, this is the theoretical maximum.
#define MAX_PAYLOAD_LENGTH 4095
// Parameter for dynamic buffer allocation
#define DEFAULT_ALLOC_SIZE_HCI 64
// Maximum length of link type packets considering SLIP escape bytes too.
#define DEFAULT_ALLOC_SIZE_INTERNAL 8

// The maximum time in milliseconds it takes to transmit the largest packet.
// Derived from the actual baud rate. Only VCOM instance is supported.
#define T_MAX_MS (MAX_PAYLOAD_LENGTH * 10 * 1000 / SL_UARTDRV_USART_VCOM_BAUDRATE)
// Recommended timeout for acknowledgment packets.
#define DEFAULT_ACK_TIMEOUT_MS (2 * T_MAX_MS)
// Recommended timeout for resending reliable packets.
#define DEFAULT_RESEND_TIMEOUT_MS (3 * T_MAX_MS)

#if SL_HCI_PACKET_3WIRE_OVERRIDE_ACK_TIMEOUT
#define ACK_TIMEOUT_MS SL_HCI_PACKET_3WIRE_ACK_TIMEOUT_MS
#else
#define ACK_TIMEOUT_MS DEFAULT_ACK_TIMEOUT_MS
#endif

#if SL_HCI_PACKET_3WIRE_OVERRIDE_RESEND_TIMEOUT
#define RESEND_TIMEOUT_MS SL_HCI_PACKET_3WIRE_RESEND_TIMEOUT_MS
#else
#define RESEND_TIMEOUT_MS DEFAULT_RESEND_TIMEOUT_MS
#endif

// HCI packet types defined in Three-wire
#define HCI_PACKET_TYPE_ACK  0
#define HCI_PACKET_TYPE_LINK 15

// Configuration field, all parameters must be unchanged!
#define CFG_TX_WINDOW            1 /* Range: 1, 7 */
#define CFG_OOF_FLOW_CTRL        0 /* Range: 0, 1 */
#define CFG_DATA_INTEGRITY_CHECK 0 /* Range: 0, 1 */
#define CFG_VERSION              0
#define CFG_FIELD                    \
  (CFG_TX_WINDOW                     \
   | (CFG_OOF_FLOW_CTRL << 3)        \
   | (CFG_DATA_INTEGRITY_CHECK << 4) \
   | (CFG_VERSION << 5) )

#define is_reliable_packet(t) (          \
    ((t) == hci_packet_type_command)     \
    || ((t) == hci_packet_type_acl_data) \
    || ((t) == hci_packet_type_event)    \
    || ((t) == hci_packet_type_iso_data))

#define is_3wire_packet(t) (     \
    ((t) == HCI_PACKET_TYPE_ACK) \
    || ((t) == HCI_PACKET_TYPE_LINK))

#define rx_data_equal(x)     (memcmp(hci_3wire.rx_buf.data, x, sizeof(x)) == 0)
#define send_link_packet(x)  hci_3wire_tx_internal(HCI_PACKET_TYPE_LINK, x, sizeof(x))

// Convenience macros for setting and getting header values.
#define HDR_SIZE                 4
#define HDR_SET_SEQ(hdr, seq)    ((hdr)[0] |= (seq))
#define HDR_SET_ACK(hdr, ack)    ((hdr)[0] |= (ack) << 3)
#define HDR_SET_RELIABLE(hdr)    ((hdr)[0] |= 1 << 7)
#define HDR_SET_TYPE(hdr, type)  ((hdr)[1] |= (type))
#define HDR_SET_LEN(hdr, len)    (((hdr)[1] |= ((len) & 0x0f) << 4), ((hdr)[2] |= (len) >> 4))
#define HDR_SET_CHECKSUM(hdr)    ((hdr)[3] = ~(((hdr)[0] + (hdr)[1] + (hdr)[2]) & 0xff))
#define HDR_GET_SEQ(hdr)         ((hdr)[0] & 0x07)
#define HDR_GET_ACK(hdr)         (((hdr)[0] >> 3) & 0x07)
#define HDR_GET_CRC(hdr)         (((hdr)[0] >> 6) & 0x01)
#define HDR_GET_RELIABLE(hdr)    (((hdr)[0] >> 7) & 0x01)
#define HDR_GET_TYPE(hdr)        ((hdr)[1] & 0x0f)
#define HDR_GET_LEN(hdr)         ((((hdr)[1] >> 4) & 0x0f) + ((hdr)[2] << 4))
#define HDR_GET_CHECKSUM(hdr)    ((((hdr)[0] + (hdr)[1] + (hdr)[2] + (hdr)[3]) & 0xff) == 0xff)

static const uint8_t sync_req[] = { 0x01, 0x7e };
static const uint8_t sync_rsp[] = { 0x02, 0x7d };
static const uint8_t conf_req[] = { 0x03, 0xfc, CFG_FIELD };
static const uint8_t conf_rsp[] = { 0x04, 0x7b, CFG_FIELD };
static const uint8_t wake_up[] = { 0x05, 0xfa };
static const uint8_t woken[] = { 0x06, 0xf9 };
static const uint8_t sleep[] = { 0x07, 0x78 };

#define RX_BUFFER_LEN 64
SL_ALIGN(4)
static uint8_t hci_rx_buffer[RX_BUFFER_LEN] SL_ATTRIBUTE_ALIGN(4);

typedef struct {
  uint8_t *data;
  uint16_t len;  // Allocated length
  uint16_t used; // Used length
} buffer_t;

static struct {
  buffer_t rx_buf; // Dynamic buffer contains only the packet payload.
  uint8_t rx_header[HDR_SIZE]; // Header has its dedicated static buffer.
  uint16_t rx_pending; // Number of bytes remaining from the actual packet.
  enum {
    RX_STATE_DELIMITER,
    RX_STATE_START,
    RX_STATE_HEADER,
    RX_STATE_PAYLOAD,
    RX_STATE_CRC
  } rx_state;
  bool slip_esc;

  buffer_t tx_buf; // Dynamic buffer for Link Layer messages.
  buffer_t tx_buf_internal; // Dynamic buffer for three-wire specific messages.
  bool tx_busy_internal; // Flag to protect three-wire TX buffer.
  uint8_t tx_ack;
  uint8_t tx_seq;

  enum {
    LINK_STATE_UNINIT,
    LINK_STATE_INIT,
    LINK_STATE_ACTIVE
  } link_state;

  sl_sleeptimer_timer_handle_t ack_timer;
  bool ack_timeout;
  bool ack_pending;

  sl_sleeptimer_timer_handle_t resend_timer;
  bool resend_timeout;
  bool resend_pending;

  bool sync_request;
} hci_3wire;

static uint16_t slip_length(const uint8_t *data, uint16_t length);
static sl_status_t buffer_allocate(buffer_t *buffer, uint16_t length);
static void buffer_put(buffer_t *dst, uint8_t byte);
static void buffer_slip_copy(buffer_t *dst, const uint8_t *src, uint16_t length);
static sl_status_t hci_3wire_tx(buffer_t *buffer,
                                uint8_t type,
                                const uint8_t *payload,
                                uint16_t length,
                                void (*tx_complete)(uint32_t));
static void hci_3wire_tx_internal(uint8_t type, const uint8_t *payload, uint16_t length);
static void hci_3wire_tx_complete_internal(uint32_t status);
static void hci_3wire_rx(uint8_t *data, uint16_t length);
static sl_status_t hci_3wire_rx_process(uint8_t byte);
static void hci_3wire_rx_unslip(uint8_t byte);
static void hci_3wire_rx_reset(void);
static void hci_3wire_rx_complete(void);
static sl_status_t hci_3wire_rx_link(void);
static void hci_3wire_peer_reset(void);
static void ack_timeout(sl_sleeptimer_timer_handle_t *handle, void *data);
static void resend_timeout(sl_sleeptimer_timer_handle_t *handle, void *data);

/**
 * Calculate the SLIP escaped length of a data buffer
 *
 * @param data Data buffer
 * @param length Length of the data buffer
 * @return SLIP escaped length
 */
static uint16_t slip_length(const uint8_t *data, uint16_t length)
{
  uint16_t ret = 0;
  for (int i = 0; i < length; i++) {
    switch (data[i]) {
      case SLIP_DELIM:
      case SLIP_ESC:
        ret += 2;
        break;
      default:
        ret += 1;
        break;
    }
  }
  return ret;
}

/**
 * Make sure that the requested buffer size is available.
 *
 * Reserve only the necessary amount of memory while keeping the number of
 * reallocations at a minimum level. If the requested length is already
 * available, the buffer is not changed.
 *
 * @param buffer Buffer to allocate
 * @param length Requested buffer length
 * @retval SL_STATUS_OK on success
 * @retval SL_STATUS_ALLOCATION_FAILED if dynamic memory allocation failed
 */
static sl_status_t buffer_allocate(buffer_t *buffer, uint16_t length)
{
  if ((length > buffer->len) || (buffer->data == NULL)) {
    buffer->len = length;
    buffer->data = realloc(buffer->data, buffer->len);
  }
  if (buffer->data == NULL) {
    return SL_STATUS_ALLOCATION_FAILED;
  }
  // Reset buffer.
  memset(buffer->data, 0, buffer->len);
  buffer->used = 0;
  return SL_STATUS_OK;
}

/**
 * Put a single byte into the buffer
 *
 * The available length is not checked, it has to be guaranteed in advance!
 *
 * @param dst Destination buffer
 * @param byte Data byte
 */
static void buffer_put(buffer_t *dst, uint8_t byte)
{
  dst->data[dst->used] = byte;
  dst->used++;
}

/**
 * Copy bytes from a source buffer with SLIP escaping
 *
 * The available length is not checked, it has to be guaranteed in advance!
 *
 * @param dst Destination buffer
 * @param src Source buffer
 * @param length Length of the source buffer
 */
static void buffer_slip_copy(buffer_t *dst, const uint8_t *src, uint16_t length)
{
  for (int16_t i = 0; i < length; i++) {
    switch (src[i]) {
      case SLIP_DELIM:
        dst->data[dst->used] = SLIP_ESC;
        dst->used++;
        dst->data[dst->used] = SLIP_ESC_DELIM;
        dst->used++;
        break;
      case SLIP_ESC:
        dst->data[dst->used] = SLIP_ESC;
        dst->used++;
        dst->data[dst->used] = SLIP_ESC_ESC;
        dst->used++;
        break;
      default:
        dst->data[dst->used] = src[i];
        dst->used++;
        break;
    }
  }
}

/**
 * Compose and send packet.
 *
 * @param buffer Transmit buffer to be used.
 * @param type Packet type.
 * @param payload Packet payload buffer.
 * @param length Length of the payload buffer.
 * @param tx_complete Transmit complete callback.
 * @return Status of the transmission.
 */
static sl_status_t hci_3wire_tx(buffer_t *buffer,
                                uint8_t type,
                                const uint8_t *payload,
                                uint16_t length,
                                void (*tx_complete)(uint32_t))
{
  sl_status_t status;
  uint8_t header[HDR_SIZE];
  uint16_t slip_len;

  // Stop acknowledgment timer. Ignore if it wasn't running.
  (void)sl_sleeptimer_stop_timer(&hci_3wire.ack_timer);
  if (hci_3wire.ack_pending) {
    hci_3wire.ack_pending = false;
    hci_3wire.tx_ack = (hci_3wire.tx_ack + 1) % 8;
  }

  // Compose packet header
  memset(header, 0, sizeof(header));
  HDR_SET_ACK(header, hci_3wire.tx_ack);
  if (is_reliable_packet(type)) {
    HDR_SET_RELIABLE(header);
    HDR_SET_SEQ(header, hci_3wire.tx_seq);
    // Increment sequence number
    hci_3wire.tx_seq = (hci_3wire.tx_seq + 1) % 8;
  }
  HDR_SET_TYPE(header, type);
  HDR_SET_LEN(header, length);
  HDR_SET_CHECKSUM(header);

  // Calculate SLIP packet length and allocate transmit buffer accordingly
  slip_len = 2; // SLIP packet delimiters
  slip_len += slip_length(header, sizeof(header));
  slip_len += slip_length(payload, length);
  status = buffer_allocate(buffer, slip_len);
  if (status != SL_STATUS_OK) {
    return status;
  }

  // Fill transmit buffer
  buffer_put(buffer, SLIP_DELIM);
  buffer_slip_copy(buffer, header, sizeof(header));
  buffer_slip_copy(buffer, payload, length);
  buffer_put(buffer, SLIP_DELIM);

  if (sl_hci_uart_write(buffer->data, buffer->used, tx_complete) != 0) {
    return SL_STATUS_FAIL;
  }

  if (is_reliable_packet(type)) {
    hci_3wire.resend_pending = true;
    (void)sl_sleeptimer_restart_periodic_timer_ms(&hci_3wire.resend_timer,
                                                  RESEND_TIMEOUT_MS,
                                                  resend_timeout,
                                                  NULL,
                                                  0,
                                                  0);
  }
  return SL_STATUS_OK;
}

static void hci_3wire_tx_internal(uint8_t type, const uint8_t *payload, uint16_t length)
{
  if (hci_3wire.tx_busy_internal) {
    return;
  }
  hci_3wire.tx_busy_internal = true;
  if (hci_3wire_tx(&hci_3wire.tx_buf_internal,
                   type,
                   payload,
                   length,
                   hci_3wire_tx_complete_internal) != SL_STATUS_OK) {
    hci_3wire.tx_busy_internal = false;
  }
}

static void hci_3wire_tx_complete_internal(uint32_t status)
{
  (void)status;
  hci_3wire.tx_busy_internal = false;
}

static void ack_timeout(sl_sleeptimer_timer_handle_t *handle, void *data)
{
  (void)handle;
  (void)data;
  hci_3wire.ack_timeout = true;
}

static void resend_timeout(sl_sleeptimer_timer_handle_t *handle, void *data)
{
  (void)handle;
  (void)data;
  hci_3wire.resend_timeout = true;
}

/**
 * Receiver state machine.
 *
 * @param data Received data buffer.
 * @param length Received data length.
 */
static void hci_3wire_rx(uint8_t *data, uint16_t length)
{
  uint16_t i = 0; // Current position of the data processing.

  while (i < length) {
    if (hci_3wire.rx_pending > 0) {
      if (data[i] == SLIP_DELIM) {
        // Unexpected end of packet.
        // This byte has to be passed to hci_3wire_rx_process to detect start of packet.
        // I.e., no need to increment buffer position yet.
        hci_3wire_rx_reset();
      } else {
        hci_3wire_rx_unslip(data[i]);
        i++;
      }
      continue;
    }
    switch (hci_3wire_rx_process(data[i])) {
      case SL_STATUS_OK:
        // Nothing to do.
        break;
      case SL_STATUS_IN_PROGRESS:
        // Jump to the next data byte.
        i++;
        break;
      default:
        // Unrecoverable error happened, abort reception.
        return;
    }
  }
}

/**
 * Called when all pending bytes of the actual packet element have arrived
 * or there are no bytes pending.
 *
 * @param byte Actual data byte.
 * @retval SL_STATUS_OK Packet element processed successfully.
 * @retval SL_STATUS_IN_PROGRESS Data byte dropped.
 * @retval SL_STATUS_ALLOCATION_FAILED Buffer allocation failed.
 */
static sl_status_t hci_3wire_rx_process(uint8_t byte)
{
  sl_status_t status = SL_STATUS_OK; // Data is not processed here by default.
  uint8_t *hdr = hci_3wire.rx_header; // Shortcut for the packet header.

  switch (hci_3wire.rx_state) {
    //  Wait until the first SLIP packet delimiter arrives.
    case RX_STATE_DELIMITER:
      status = SL_STATUS_IN_PROGRESS;
      if (byte == SLIP_DELIM) {
        hci_3wire.rx_state = RX_STATE_START;
      }
      break;
    // Start receiving the header. Omit consecutive SLIP packet delimiters.
    case RX_STATE_START:
      if (byte == SLIP_DELIM) {
        status = SL_STATUS_IN_PROGRESS;
      } else {
        hci_3wire.rx_state = RX_STATE_HEADER;
        hci_3wire.rx_pending = HDR_SIZE;
      }
      break;
    // Header received.
    case RX_STATE_HEADER:
      if (!HDR_GET_CHECKSUM(hdr)) {
        // Invalid header checksum.
        hci_3wire_rx_reset();
        break;
      }
      if (hci_3wire.link_state != LINK_STATE_ACTIVE
          && HDR_GET_TYPE(hdr) != HCI_PACKET_TYPE_LINK) {
        // Only link control packets are allowed in non-active state.
        hci_3wire.sync_request = true;
        hci_3wire_rx_reset();
        break;
      }
      if (HDR_GET_RELIABLE(hdr) && HDR_GET_SEQ(hdr) != hci_3wire.tx_ack) {
        // Out-of-order packet.
        hci_3wire_rx_reset();
        break;
      }
      hci_3wire.rx_state = RX_STATE_PAYLOAD;
      hci_3wire.rx_pending = HDR_GET_LEN(hdr);
      status = buffer_allocate(&hci_3wire.rx_buf, hci_3wire.rx_pending);
      if (status != SL_STATUS_OK) {
        // Failed to allocate buffer for the packet payload.
        hci_3wire_rx_reset();
      }
      break;
    // Payload received.
    case RX_STATE_PAYLOAD:
      if (HDR_GET_CRC(hdr)) {
        hci_3wire.rx_state = RX_STATE_CRC;
        hci_3wire.rx_pending = 2;
      } else {
        hci_3wire_rx_complete();
      }
      break;
    // CRC received.
    case RX_STATE_CRC:
      // In case of CRC support, CRC value can be checked here.
      hci_3wire_rx_complete();
      break;
    // Any other state is invalid.
    default:
      hci_3wire_rx_reset();
      status = SL_STATUS_INVALID_STATE;
      break;
  }
  return status;
}

/**
 * Remove SLIP escaping and store data byte in the RX buffer.
 *
 * @param byte Actual data byte.
 */
static void hci_3wire_rx_unslip(uint8_t byte)
{
  uint8_t unslipped = byte;

  if (!hci_3wire.slip_esc && byte == SLIP_ESC) {
    // Start of an escape sequence detected.
    hci_3wire.slip_esc = true;
    return;
  }

  if (hci_3wire.slip_esc) {
    // The previous byte indicated the start of an escape sequence.
    hci_3wire.slip_esc = false;
    switch (byte) {
      case SLIP_ESC_DELIM:
        unslipped = SLIP_DELIM;
        break;
      case SLIP_ESC_ESC:
        unslipped = SLIP_ESC;
        break;
      default:
        // Invalid escape sequence.
        hci_3wire_rx_reset();
        return;
    }
  }

  // Find the correct buffer.
  switch (hci_3wire.rx_state) {
    case RX_STATE_HEADER:
      hci_3wire.rx_header[HDR_SIZE - hci_3wire.rx_pending] = unslipped;
      break;
    case RX_STATE_PAYLOAD:
      buffer_put(&hci_3wire.rx_buf, unslipped);
      break;
    case RX_STATE_CRC:
      // CRC not supported, drop CRC bytes.
      break;
    default:
      // Unexpected state.
      hci_3wire_rx_reset();
      return;
  }
  hci_3wire.rx_pending--;
}

/**
 * Reset state machine for the packet reception.
 */
static void hci_3wire_rx_reset(void)
{
  hci_3wire.rx_state = RX_STATE_DELIMITER;
  hci_3wire.rx_pending = 0;
  hci_3wire.slip_esc = false;
}

/**
 * Indicate the reception of a complete packet.
 */
static void hci_3wire_rx_complete(void)
{
  sl_status_t status = SL_STATUS_FAIL;
  uint8_t type;
  uint8_t *hdr = hci_3wire.rx_header; // Shortcut for the packet header.
  bool ack_pending = hci_3wire.ack_pending; // Store previous state.
  if (HDR_GET_RELIABLE(hdr)) {
    // hci_common_transport_receive may call hci_common_transport_transmit
    // directly. The hci_common_transport_transmit uses the ack number,
    // therefore, the ack number has to be incremented before the RX status
    // is known. Therefore, only a flag is set here, that is evaluated just
    // before sending the next packet.
    hci_3wire.ack_pending = true;
  }

  // Check for acknowledged reliable packet.
  if (hci_3wire.resend_pending && (hci_3wire.tx_seq == HDR_GET_ACK(hdr))) {
    (void)sl_sleeptimer_stop_timer(&hci_3wire.resend_timer);
    hci_3wire.resend_pending = false;
    hci_3wire.resend_timeout = false;
    // Allow the upper layer to send the next packet.
    hci_common_transport_transmit_complete(SL_STATUS_OK);
  }

  type = HDR_GET_TYPE(hdr);
  switch (type) {
    case hci_packet_type_command:
    case hci_packet_type_acl_data:
    case hci_packet_type_sync_data:
    case hci_packet_type_event: // Host shouldn't send this packet type.
    case hci_packet_type_iso_data:
      // Mixing types, but only check for success, which is 0 in both cases.
      status = hci_common_transport_receive(&type, 1, false);
      if (status == SL_STATUS_OK) {
        status = hci_common_transport_receive(hci_3wire.rx_buf.data,
                                              hci_3wire.rx_buf.used,
                                              true);
      }
      break;
    case HCI_PACKET_TYPE_LINK:
      status = hci_3wire_rx_link();
      break;
    default:
      // Unknown packet type or acknowledgment.
      break;
  }
  if (HDR_GET_RELIABLE(hdr)) {
    if ((status != SL_STATUS_OK) && !ack_pending) {
      // Clear flag if the reception fails.
      hci_3wire.ack_pending = false;
    }
    if (hci_3wire.ack_pending) {
      // (Re)start acknowledge timeout after successfully receiving a reliable
      // packet. If the timer was already running it means that the sliding
      // window is bigger than 1 and the timeout restarts. If the (re)start
      // operation fails and the peer doesn't get the ack, it retransmits the
      // packet. Therefore, the return status can be ignored.
      (void)sl_sleeptimer_restart_timer_ms(&hci_3wire.ack_timer,
                                           ACK_TIMEOUT_MS,
                                           ack_timeout,
                                           NULL,
                                           0,
                                           0);
    }
  }
  hci_3wire_rx_reset();
}

/**
 * Process link packets.
 */
static sl_status_t hci_3wire_rx_link(void)
{
  if (HDR_GET_LEN(hci_3wire.rx_header) < 2) {
    // Packet too short.
    return SL_STATUS_INVALID_PARAMETER;
  }

  if (rx_data_equal(sync_req)) {
    if (hci_3wire.link_state == LINK_STATE_ACTIVE) {
      hci_3wire_peer_reset();
    }
    send_link_packet(sync_rsp);
    hci_3wire.link_state = LINK_STATE_INIT;
  } else if (rx_data_equal(sync_rsp)) {
    if (hci_3wire.link_state == LINK_STATE_ACTIVE) {
      hci_3wire_peer_reset();
    }
    hci_3wire.link_state = LINK_STATE_INIT;
    send_link_packet(conf_req);
    // Check the first 2 bytes only.
    // The config field of the host is not relevant with the current settings.
  } else if (memcmp(hci_3wire.rx_buf.data, conf_req, 2) == 0) {
    send_link_packet(conf_rsp);
    hci_3wire.link_state = LINK_STATE_ACTIVE;
  } else if (rx_data_equal(conf_rsp)) {
    hci_3wire.link_state = LINK_STATE_ACTIVE;
  } else if (rx_data_equal(wake_up)) {
    send_link_packet(woken);
  } else if (rx_data_equal(woken)) {
    // Not prepared for a sleeping host.
  } else if (rx_data_equal(sleep)) {
    // Not prepared for a sleeping host.
  } else {
    // Unknown packet.
    return SL_STATUS_INVALID_PARAMETER;
  }
  return SL_STATUS_OK;
}

/**
 * The remote end (i.e. host) has been reset.
 */
static void hci_3wire_peer_reset(void)
{
  hci_3wire.link_state = LINK_STATE_UNINIT;
  hci_3wire.tx_ack = 0;
  hci_3wire.tx_seq = 0;
  // Stop acknowledgment timer. Ignore if it wasn't running.
  (void)sl_sleeptimer_stop_timer(&hci_3wire.ack_timer);
  hci_3wire.ack_timeout = false;
  hci_3wire.ack_pending = false;
  // Stop retransmission timer. Ignore if it wasn't running.
  (void)sl_sleeptimer_stop_timer(&hci_3wire.resend_timer);
  hci_3wire.resend_timeout = false;
  hci_3wire.resend_pending = false;
}

/*
 *  Called periodically.
 */
void sl_btctrl_hci_packet_step(void)
{
  // Check if data is available from host.
  if (sl_hci_uart_rx_buffered_length() > 0) {
    uint16_t bytes_read = sl_hci_uart_read(hci_rx_buffer, sizeof(hci_rx_buffer));
    hci_3wire_rx(hci_rx_buffer, bytes_read);
  }
  if (hci_3wire.ack_timeout) {
    hci_3wire.ack_timeout = false;
    // Send acknowledgment packet.
    (void)hci_3wire_tx_internal(HCI_PACKET_TYPE_ACK, NULL, 0);
  }
  if (hci_3wire.resend_timeout) {
    hci_3wire.resend_timeout = false;
    // Resend reliable packet.
    sl_hci_uart_write(hci_3wire.tx_buf.data, hci_3wire.tx_buf.used, NULL);
  }
  if (hci_3wire.sync_request) {
    hci_3wire.sync_request = false;
    send_link_packet(sync_req);
  }
}

/*
 * Called from higher layer to transmit a HCI package.
 */
uint32_t hci_common_transport_transmit(uint8_t *data, int16_t len)
{
  uint8_t type;
  void (*tx_complete)(uint32_t);

  if (hci_3wire.link_state != LINK_STATE_ACTIVE) {
    return SL_STATUS_NOT_READY;
  }
  if (len > MAX_PAYLOAD_LENGTH) {
    return SL_STATUS_MESSAGE_TOO_LONG;
  }
  // 1st byte of the data buffer denotes the HCI packet type, it has to be known.
  if (len < 1) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  type = *data;
  switch (type) {
    case hci_packet_type_command: // Controller shouldn't send this packet type.
    case hci_packet_type_acl_data:
    case hci_packet_type_sync_data:
    case hci_packet_type_event:
    case hci_packet_type_iso_data:
      // Packet type valid.
      break;
    default:
      return SL_STATUS_INVALID_TYPE;
  }

  if (is_reliable_packet(type)) {
    // Reliable packets need acknowledgment before sending the next packet.
    // There is no action to be done when the transfer is completed.
    tx_complete = NULL;
  } else {
    // Unreliable packets don't need acknowledgment, the next packet can be
    // sent immediately.
    tx_complete = hci_common_transport_transmit_complete;
  }
  return hci_3wire_tx(&hci_3wire.tx_buf, type, data + 1, len - 1, tx_complete);
}

void hci_common_transport_init(void)
{
  // Allocate dynamic buffers with initial size.
  // TODO: check for allocation error.
  (void)buffer_allocate(&hci_3wire.rx_buf, DEFAULT_ALLOC_SIZE_HCI);
  (void)buffer_allocate(&hci_3wire.tx_buf, DEFAULT_ALLOC_SIZE_HCI);
  (void)buffer_allocate(&hci_3wire.tx_buf_internal, DEFAULT_ALLOC_SIZE_INTERNAL);
  sl_hci_uart_init();
}
