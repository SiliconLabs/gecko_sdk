/***************************************************************************//**
 * @file
 * @brief CPC-HCI bridge
 *
 * This application serves as a bridge between CPCd and btattach. As CPC
 * communication is available through libcpc.so API calls, and BlueZ stack
 * can only attach through btattach command to a UART interface, this app
 * serves as a bridge between the two communication interfaces.
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
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <pty.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>

#include "config.h"
#include "sl_cpc.h"
#include "sl_btctrl_hci_packet.h"
#include "app_log.h"

#define SUCCESS 0
#define FAILURE (-1)
#define MAX(x, y) ((x) > (y) ? (x) : (y))

// CPC related variables
static cpc_handle_t cpc_lib_handle;
static cpc_endpoint_t cpc_endpoint;
// Tx/Rx buffer
static uint8_t cpc_tx_buffer[CPC_TX_BUF_SIZE];
static uint8_t cpc_rx_buffer[CPC_RX_BUF_SIZE];

// Master and slave file decriptors for the PTY
static int pty_master_fd;
static int pty_slave_fd;
// CPC socket file descriptor
static int cpc_sock_fd;

// Represents whether the main loop should run
static volatile sig_atomic_t is_running = true;
// Signals that the CPC side has reset
static volatile sig_atomic_t cpc_reset_requested = false;

static void signal_handler(int sig);
static int cpc_hci_bridge_init(const char *cpc_instance_name);
static void cpc_reset_callback(void);
static int cpc_hci_bridge_reset(void);
static int cpc_hci_bridge_loop(void);
static int transfer_data_from_pty_to_cpc(void);
static int transfer_data_from_cpc_to_pty(void);
static int parse_hci_packet(const uint8_t *hci_buffer, const ssize_t hci_buffer_len);
static void debug_log_buffer(const char *name, const uint8_t *buf, const ssize_t size);

/**************************************************************************//**
 * Entry point of the application
 *
 * @param[in] argc number of command line arguments
 * @param[in] argv pointer to the array of the command line aguments
 *****************************************************************************/
int main(int argc, char *argv[])
{
  app_log_info("Silicon Labs | CPC-HCI bridge\n");
  // Set up custom signal handler for user interrupt and termination request
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);

  // Set the CPC instance name
  char *cpc_instance_name = CPC_DEFAULT_INSTANCE_NAME;
  if (argc > 1) {
    cpc_instance_name = argv[1];
  }

  // Initialize
  if (cpc_hci_bridge_init(cpc_instance_name) < 0) {
    exit(EXIT_FAILURE);
  }

  // Main loop
  while (is_running) {
    if (cpc_reset_requested) {
      cpc_reset_requested = false;
      if (cpc_hci_bridge_reset() < 0) {
        app_log_error("cpc_hci_bridge_reset failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
      }
      app_log_debug("Bridge reset successful\n");
      continue;
    }

    if (cpc_hci_bridge_loop() < 0) {
      app_log_error("Runtime error: %s\n", strerror(errno));
    }
  }
}

/**************************************************************************//**
 * Custom signal handler
 *
 * @param[in] sig an integer representing the received signal
 *****************************************************************************/
void signal_handler(int sig)
{
  (void)sig;
  is_running = false;
}

/**************************************************************************//**
 * Initializes the bridge by opening the CPC connection and
 * creating the PTY device file
 *
 * @param[in] cpc_instance_name name of the CPC instance to initialize
 *
 * @return zero if successful, error code otherwise
 *****************************************************************************/
int cpc_hci_bridge_init(const char *cpc_instance_name)
{
  int ret = 0;
  uint8_t retry = 0u;

  // Initialize CPC communication
  do {
    ret = cpc_init(&cpc_lib_handle, cpc_instance_name, false, cpc_reset_callback);
    if (ret == 0) {
      break;
    }
    nanosleep((const struct timespec[]){ { 0, CPC_RETRY_SLEEP_NS } }, NULL);
    retry++;
  } while (retry < RETRY_COUNT);

  if (ret < 0) {
    app_log_error("cpc_init failed with '%s': %s\n", cpc_instance_name, strerror(errno));
    return ret;
  }
  app_log_info("CPC successfully initialized with '%s'\n", cpc_instance_name);

  // Open the CPC Bluetooth endpoint
  retry = 0;
  do {
    ret = cpc_open_endpoint(cpc_lib_handle,
                            &cpc_endpoint,
                            SL_CPC_ENDPOINT_BLUETOOTH_RCP,
                            CPC_TRANSMIT_WINDOW);
    if (ret > 0) {
      cpc_sock_fd = ret;
      break;
    }
    nanosleep((const struct timespec[]){ { 0, CPC_RETRY_SLEEP_NS } }, NULL);
    retry++;
  } while (retry < RETRY_COUNT);

  if (ret < 0) {
    app_log_error("cpc_open_endpoint failed: %s\n", strerror(errno));
    return ret;
  }
  app_log_info("CPC Bluetooth endpoint opened\n");

  // Open the TTY device file
  ret = openpty(&pty_master_fd, &pty_slave_fd, NULL, NULL, NULL);
  if (ret >= 0) {
    int flags = fcntl(pty_master_fd, F_GETFL, 0);
    flags = flags | O_NONBLOCK;
    fcntl(pty_master_fd, F_SETFL, flags);
    char *pName = ttyname(pty_slave_fd);
    app_log_info("PTY device file opened at '%s'\n", pName);
    remove(SYMLINK_PATH);
    if (symlink(pName, SYMLINK_PATH) != 0) {
      app_log_error("Error creating symlink (%s): %s\n", SYMLINK_PATH, strerror(errno));
    }
  }

  return ret;
}

/**************************************************************************//**
 * Reset callback for CPC - called when the CPC daemon has been reset
 *****************************************************************************/
void cpc_reset_callback(void)
{
  cpc_reset_requested = true;
}

/**************************************************************************//**
 * Resets the CPC communication
 *
 * @return zero if successful, error code otherwise
 *****************************************************************************/
int cpc_hci_bridge_reset(void)
{
  int ret;
  uint8_t retry;

  app_log_debug("Bridge reset requested\n");

  // Close previously opened Bluetooth endpoint
  if (cpc_sock_fd > 0) {
    ret = cpc_close_endpoint(&cpc_endpoint);
    if (ret == 0) {
      cpc_sock_fd = -1;
    } else {
      app_log_error("cpc_close_endpoint failed: %s\n", strerror(errno));
      return ret;
    }
  }

  // Restart connection with CPC
  retry = 0;
  do {
    ret = cpc_restart(&cpc_lib_handle);
    if (ret == 0) {
      break;
    }
    nanosleep((const struct timespec[]){ { 0, CPC_RETRY_SLEEP_NS } }, NULL);
    retry++;
  } while (retry < RETRY_COUNT);

  if (ret < 0) {
    app_log_error("cpc_restart failed: %s\n", strerror(errno));
    return ret;
  }

  // Open the Bluetooth endpoint
  retry = 0;
  do {
    ret = cpc_open_endpoint(cpc_lib_handle,
                            &cpc_endpoint,
                            SL_CPC_ENDPOINT_BLUETOOTH_RCP,
                            CPC_TRANSMIT_WINDOW);
    if (ret > 0) {
      cpc_sock_fd = ret;
      break;
    }
    nanosleep((const struct timespec[]){ { 0, CPC_RETRY_SLEEP_NS } }, NULL);
    retry++;
  } while (retry < RETRY_COUNT);

  if (ret < 0) {
    app_log_error("cpc_open_endpoint failed: %s\n", strerror(errno));
  }

  return ret;
}

/**************************************************************************//**
 * Transfers data between the PTY device file and the CPC
 *
 * @return SUCCESS if successful, error code otherwise
 *****************************************************************************/
int cpc_hci_bridge_loop(void)
{
  struct timeval tv;
  tv.tv_sec  = TIMEOUT_SEC;
  tv.tv_usec = TIMEOUT_USEC;

  fd_set readfds;
  FD_ZERO(&readfds);
  FD_SET(pty_master_fd, &readfds);
  FD_SET(cpc_sock_fd, &readfds);

  int max_fd = MAX(pty_master_fd, cpc_sock_fd);

  // Check if any of the file descriptors have data available
  int ret = select(max_fd + 1, &readfds, NULL, NULL, &tv);
  if ((ret < 0) && (errno != EINTR)) {
    return ret;
  }

  if (FD_ISSET(pty_master_fd, &readfds)) {
    if (transfer_data_from_pty_to_cpc() < SUCCESS) {
      return FAILURE;
    }
  }

  if (FD_ISSET(cpc_sock_fd, &readfds)) {
    if (transfer_data_from_cpc_to_pty() < SUCCESS) {
      return FAILURE;
    }
  }

  return SUCCESS;
}

/**************************************************************************//**
 * Reads data from PTY and writes it to CPC
 *
 * @return SUCCESS if successful, FAILURE otherwise
 *****************************************************************************/
int transfer_data_from_pty_to_cpc(void)
{
  ssize_t size;
  ssize_t cpc_write_result;
  uint8_t *hci_packet_buf;
  ssize_t hci_packet_len;

  size = read(pty_master_fd, cpc_tx_buffer, CPC_TX_BUF_SIZE);
  if (size > 0) {
    // Parse all HCI packets from the buffer and send them separately to CPC
    hci_packet_buf = cpc_tx_buffer;
    do {
      hci_packet_len = parse_hci_packet(cpc_tx_buffer, size);
      app_log_debug("cpc_write - ");
      debug_log_buffer("cpc_tx_buffer", cpc_tx_buffer, hci_packet_len);
      // Write data to CPC
      cpc_write_result = cpc_write_endpoint(cpc_endpoint, hci_packet_buf, hci_packet_len, 0);
      if (cpc_write_result < 0) {
        app_log_error("cpc_write_endpoint failed: %s\n", strerror(errno));
        return FAILURE;
      }
      size -= hci_packet_len;
      hci_packet_buf += hci_packet_len;
    } while (size >= hci_packet_len);
  } else if (errno != EAGAIN && errno != ECONNRESET) {
    app_log_error("PTY read operation failed: %s\n", strerror(errno));
    return FAILURE;
  }
  return SUCCESS;
}

/**************************************************************************//**
 * Reads data from CPC and writes it to PTY
 *
 * @return SUCCESS if successful, FAILURE otherwise
 *****************************************************************************/
int transfer_data_from_cpc_to_pty(void)
{
  ssize_t size;
  size = cpc_read_endpoint(cpc_endpoint,
                           &cpc_rx_buffer[0],
                           CPC_RX_BUF_SIZE,
                           CPC_ENDPOINT_READ_FLAG_NON_BLOCKING);
  if (size > 0) {
    app_log_debug("cpc_read  - ");
    debug_log_buffer("cpc_rx_buffer", cpc_rx_buffer, size);
    // Write data to PTY
    write(pty_master_fd, &cpc_rx_buffer[0], size);
    memset(&cpc_rx_buffer[0], 0, CPC_RX_BUF_SIZE);
  } else if ((int)size != -EAGAIN && (int)size != -ECONNRESET) {
    app_log_error("PTY write operation failed: %s\n", strerror(errno));
    return FAILURE;
  }
  return SUCCESS;
}

/**************************************************************************//**
 * Returns the length of the first HCI packet in the buffer
 *
 * @param[in] hci_buffer pointer to the buffer containing HCI packets
 * @param[in] hci_buffer_len length of the buffer containing HCI packets
 *
 * @return the length (from 0) of the first HCI packet found in the buffer
 *****************************************************************************/
int parse_hci_packet(const uint8_t *hci_buffer, const ssize_t hci_buffer_len)
{
  // Treat the buffer as a HCI packet
  hci_packet_t *hci_packet = (hci_packet_t *)hci_buffer;
  ssize_t hci_packet_len = 0;
  ssize_t hci_packet_type_and_header_size = 0;
  uint16_t payload_packet_len = 0;

  switch (hci_packet->packet_type) {
    case hci_packet_type_acl_data:
      hci_packet_type_and_header_size = hci_acl_data_header_size + 1;
      payload_packet_len = hci_packet->acl_pkt.length;
      break;

    case hci_packet_type_command:
      hci_packet_type_and_header_size = hci_command_header_size + 1;
      payload_packet_len = hci_packet->hci_cmd.param_len;
      break;

    default:
      // Not handled type, go with the whole buffer
      return hci_buffer_len;
  }

  // If the buffer is too small to contain a whole HCI packet
  if (hci_buffer_len < hci_packet_type_and_header_size) {
    hci_packet_len = hci_buffer_len;
    app_log_warning("Warning: possibly malformed HCI packet received\n");
    debug_log_buffer("hci_packet_buf", hci_buffer, hci_packet_len);
    return hci_buffer_len;
  }

  // Calculate the actual size of the HCI packet in the buffer
  hci_packet_len = hci_packet_type_and_header_size + payload_packet_len;
  if (hci_buffer_len != hci_packet_len) {
    app_log_debug("Parsed packet from multiple in buffer; hci_packet_len='%ld' hci_buffer_len='%ld'\n", (long)hci_packet_len, (long)hci_buffer_len);
  }
  return hci_packet_len;
}

/**************************************************************************//**
 * Prints the buffer passed in the arguments at DEBUG log level
 *
 * @param[in] name name of the buffer to be printed
 * @param[in] buf pointer to the packet to be printed
 * @param[in] size length of the packet to be printed
 *****************************************************************************/
void debug_log_buffer(const char *name, const uint8_t *buf, const ssize_t size)
{
  app_log_append_debug("size='%02zd' %s=[ ", size, name);
  app_log_hexdump_debug(buf, size);
  app_log_append_debug(" ]\n");
}
