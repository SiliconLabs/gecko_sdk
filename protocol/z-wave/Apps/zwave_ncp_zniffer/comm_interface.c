/**
 * @file
 * @copyright 2022 Silicon Laboratories Inc.
 */

#include "comm_interface.h"
#include "zpal_uart.h"
#include "SwTimer.h"
#include <string.h>
#include "AppTimer.h"
#include "Assert.h"
#include "Zniffer_hw.h"

#include <ZW_application_transport_interface.h>

#define DEFAULT_BYTE_TIMEOUT_MS 150
#define HEADER_LEN              2

#define COMM_INT_TX_BUFFER_SIZE 200
#define COMM_INT_RX_BUFFER_SIZE 200

typedef enum
{
  COMM_INTERFACE_STATE_SOF    = 0,
  COMM_INTERFACE_STATE_CMD    = 1,
  COMM_INTERFACE_STATE_LEN    = 2,
  COMM_INTERFACE_STATE_DATA   = 3,
} comm_interface_state_t;

typedef struct
{
  transport_t transport;
  SSwTimer byte_timer;
  bool byte_timeout;
  uint32_t byte_timeout_ms;
  comm_interface_state_t state;
  uint8_t expect_bytes;
  uint8_t buffer_len;
  uint8_t buffer[RECEIVE_BUFFER_SIZE];
  bool rx_active;
  uint8_t rx_wait_count;
} comm_interface_t;

static comm_interface_t comm_interface;
comm_interface_frame_ptr const serial_frame = (comm_interface_frame_ptr)comm_interface.buffer;

static uint8_t tx_data[COMM_INT_TX_BUFFER_SIZE];
static uint8_t rx_data[COMM_INT_RX_BUFFER_SIZE];

static void set_expect_bytes(uint8_t level)
{
  vPortEnterCritical();

  if (zpal_uart_get_available(comm_interface.transport.handle) >= level)
  {
    comm_interface.expect_bytes = 0;
  }
  else
  {
    comm_interface.expect_bytes = level;
  }

  vPortExitCritical();
}

static void receive_callback(__attribute__((unused)) const zpal_uart_handle_t handle, size_t available)
{
  if (available >= comm_interface.expect_bytes)
  {
    comm_interface.expect_bytes = 0;
  }
}

static void byte_timer_cb(__attribute__((unused)) SSwTimer *timer)
{
  comm_interface.byte_timeout = true;
}


static zpal_status_t comm_interface_transmit(transport_t *transport, const uint8_t *data, size_t len, transmit_done_cb_t cb)
{
  if (transport)
  {
    switch (transport->type)
    {
      case TRANSPORT_TYPE_UART:
        return zpal_uart_transmit(transport->handle, data, len, cb);

      default:
        break;
    }
  }

  return ZPAL_STATUS_FAIL;
}

void comm_interface_transmit_frame(uint8_t cmd, uint8_t type, const uint8_t *payload, uint8_t len, transmit_done_cb_t cb)
{
  TimerStop(&comm_interface.byte_timer);

  comm_interface.byte_timeout = false;

  switch (type)
  {
    case CMD_FRAME:
    {
      tx_cmd_frame_t frame;
      frame.sof = SOF;
      frame.cmd = cmd;
      frame.len = len;
      memcpy(frame.payload, payload, len);
      set_expect_bytes(0);
      comm_interface_transmit(&comm_interface.transport, (uint8_t *)&frame, frame.len + 3, cb);
    }
    break;

    case DATA_FRAME:
    {
      tx_data_frame_t* frame = (tx_data_frame_t*)payload;
      set_expect_bytes(0);
      comm_interface_transmit(&comm_interface.transport, (uint8_t *)frame, frame->len + 10, cb);
    }
    break;

    case BEAM_FRAME:
    {
      if (BEAM_START == cmd)
      {
        tx_beam_start_frame_t* frame = (tx_beam_start_frame_t*)payload;
        set_expect_bytes(0);
        comm_interface_transmit(&comm_interface.transport, (uint8_t *)frame, 11, cb);
      }
      else
      {
        tx_beam_stop_frame_t* frame = (tx_beam_stop_frame_t*)payload;
        set_expect_bytes(0);
        comm_interface_transmit(&comm_interface.transport, (uint8_t *)frame, 7, cb);
      }
    }
    break;

    default:
      break;
  }

}

void comm_interface_wait_transmit_done(void)
{
  while(zpal_uart_transmit_in_progress(comm_interface.transport.handle));
}

void comm_interface_init(void)
{
  const zpal_uart_config_t uart_config =
  {
    .tx_buffer = tx_data,
    .tx_buffer_len = COMM_INT_TX_BUFFER_SIZE,
    .rx_buffer = rx_data,
    .rx_buffer_len = COMM_INT_RX_BUFFER_SIZE,
    .id = ZPAL_UART0,
    .baud_rate = 115200,
    .data_bits = 8,
    .parity_bit = ZPAL_UART_NO_PARITY,
    .stop_bits = ZPAL_UART_STOP_BITS_1,
    .receive_callback = receive_callback,
    .ptr = Zniffer_get_uart_config_ext(),
  };

  comm_interface_set_byte_timeout_ms(DEFAULT_BYTE_TIMEOUT_MS);

  zpal_status_t status = zpal_uart_init(&uart_config, &comm_interface.transport.handle);
  ASSERT(status == ZPAL_STATUS_OK);
  status = zpal_uart_enable(comm_interface.transport.handle);
  ASSERT(status == ZPAL_STATUS_OK);
  comm_interface.transport.type = TRANSPORT_TYPE_UART;

  AppTimerRegister(&comm_interface.byte_timer, false, byte_timer_cb);
  TimerStop(&comm_interface.byte_timer);

  comm_interface.state = COMM_INTERFACE_STATE_SOF;
  comm_interface.buffer_len = 0;
  set_expect_bytes(HEADER_LEN);
}

uint32_t comm_interface_get_byte_timeout_ms(void)
{
  return comm_interface.byte_timeout_ms;
}

void comm_interface_set_byte_timeout_ms(uint32_t t)
{
  comm_interface.byte_timeout_ms = t;
}

static void store_byte(uint8_t byte)
{
  if (TimerIsActive(&comm_interface.byte_timer))
    TimerRestart(&comm_interface.byte_timer);
  else
    TimerStart(&comm_interface.byte_timer, comm_interface_get_byte_timeout_ms());

  comm_interface.byte_timeout = false;
  comm_interface.buffer[comm_interface.buffer_len] = byte;
  comm_interface.buffer_len++;
}

static void handle_sof(uint8_t input)
{
  if (input == SOF)
  {
    comm_interface.state = COMM_INTERFACE_STATE_CMD;
    comm_interface.buffer_len = 0;
    comm_interface.rx_active = true; // now we're receiving - check for timeout
    store_byte(input);
  }
}

static void handle_cmd(uint8_t input)
{
  store_byte(input);
  comm_interface.state = COMM_INTERFACE_STATE_LEN;
}

static void handle_len(uint8_t input)
{
  store_byte(input);
  comm_interface.state = COMM_INTERFACE_STATE_DATA;
  comm_interface.rx_wait_count = input;
}

static comm_interface_parse_result_t handle_data(uint8_t input)
{
  if (comm_interface.rx_wait_count > 0)
  {
    comm_interface.rx_wait_count--;
    store_byte(input);
  }

  if ((comm_interface.buffer_len >= RECEIVE_BUFFER_SIZE) ||
      (comm_interface.buffer_len > serial_frame->len))      //buffer_len - sizeof(sof) >= serial_frame->len
  {
    TimerStop(&comm_interface.byte_timer);
    comm_interface.byte_timeout = false;
    comm_interface.state = COMM_INTERFACE_STATE_SOF; // Restart looking for SOF
    comm_interface.rx_active = false;  // Not really active
    return PARSE_FRAME_RECEIVED;
  }

  return PARSE_IDLE;
}

static void handle_default(void)
{
  comm_interface.state = COMM_INTERFACE_STATE_SOF; // Restart looking for SOF
  comm_interface.rx_active = false;  // Not really active now...
  comm_interface.byte_timeout = false;
  TimerStop(&comm_interface.byte_timer);
}

comm_interface_parse_result_t comm_interface_parse_data(void)
{
  uint8_t rx_byte;
  comm_interface_parse_result_t result = PARSE_IDLE;

  while ((result == PARSE_IDLE) && zpal_uart_get_available(comm_interface.transport.handle))
  {
    zpal_uart_receive(comm_interface.transport.handle, &rx_byte, sizeof(rx_byte));

    switch (comm_interface.state)
    {
      case COMM_INTERFACE_STATE_SOF:
        handle_sof(rx_byte);
        break;

      case COMM_INTERFACE_STATE_CMD:
        handle_cmd(rx_byte);
        break;

      case COMM_INTERFACE_STATE_LEN:
        handle_len(rx_byte);
        if (0 < rx_byte)
        {
          break;
        }
        // fall through

      case COMM_INTERFACE_STATE_DATA:
        result = handle_data(rx_byte);
        break;

      default:
        handle_default();
        break;
    }
  }

  /* Check for timeouts - if no other events detected */
  if (result == PARSE_IDLE)
  {
    /* Are we in the middle of collecting a frame and have we timed out? */
    if (comm_interface.rx_active && comm_interface.byte_timeout)
    {
      comm_interface.byte_timeout = false;
      /* Reset to SOF hunting */
      comm_interface.state = COMM_INTERFACE_STATE_SOF;
      comm_interface.rx_active = false; /* Not inframe anymore */
      result = PARSE_RX_TIMEOUT;
    }
  }

  /*Check how many bytes we need depending on state.*/
  switch(comm_interface.state)
  {
    case COMM_INTERFACE_STATE_SOF:
      set_expect_bytes(HEADER_LEN);
      break;

    case COMM_INTERFACE_STATE_CMD:
      set_expect_bytes(HEADER_LEN - 1);
      break;

    case COMM_INTERFACE_STATE_LEN:
      set_expect_bytes(HEADER_LEN - 2);
      break;

    case COMM_INTERFACE_STATE_DATA:
      set_expect_bytes(comm_interface.rx_wait_count);
      break;

    default:
      break;
  }

  return result;
}
