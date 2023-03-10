/***************************************************************************//**
 * @file
 * @brief Bridge application.
 *
 * This application serves as a bridge between CPCd and btattach. As CPC
 * communication is available through libcpc.so API calls, and BlueZ stack
 * can only attach through btattach command to a UART interface, this app
 * serves as a bridge between the two communication interfaces.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "sl_cpc.h"
#include "sl_btctrl_hci_packet.h"
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

// set this to 1 for more runtime log messages
#define DEBUG 0

#define SUCCESS             0
#define FAILURE             (-1)
#define TIMEOUT_IN_SEC      0
#define TIMEOUT_IN_USEC     5000

#define TO_CPC_BUF_SIZE     256
#define FROM_CPC_BUF_SIZE   SL_CPC_READ_MINIMUM_SIZE
#define INST_NAME_LEN       100
#define RETRY_COUNT         10
#define CPC_RETRY_SLEEP_NS  100000000L
#define CPC_RESET_SLEEP_NS  10000L
#define THREAD_SLEEP_NS     1L
#define CPC_TRANSMIT_WINDOW 1
#define SYMLINK_PATH        "pts_hci"

#define MAX(x, y) ((x) > (y) ? (x) : (y))

// cpc related structures
static cpc_handle_t lib_handle;
static cpc_endpoint_t endpoint;
// tx/rx buffers
static uint8_t data_to_cpc[TO_CPC_BUF_SIZE];
static uint8_t data_from_cpc[FROM_CPC_BUF_SIZE];
// cpc instance name
static char cpc_instance[INST_NAME_LEN];

static int pty_m;
static int pty_s;
static int ep_sock_fd;

// end the receiving loop if signal is received.
static volatile bool run = true;
// signal if the controller was reset
static volatile sig_atomic_t has_reset = false;

static void reset_callback(void);
static int cpc_poll_fds(void);
static void print_buffer(const uint8_t *packet_buf, const ssize_t packet_len);
static int parse_hci_packet(const uint8_t *hci_buffer, const ssize_t hci_buffer_len);

// Custom signal handler.
static void signal_handler(int sig)
{
  (void)sig;
  run = false;
}

/**************************************************************************//**
 * Starts CPC and pty.
 *****************************************************************************/
uint32_t startup(void)
{
  int ret;
  uint8_t retry;

  // Initialize CPC communication
  retry = 0;
  do {
    ret = cpc_init(&lib_handle, cpc_instance, false, reset_callback);
    if (ret == 0) {
      break;
    }
    nanosleep((const struct timespec[]){ { 0, CPC_RETRY_SLEEP_NS } }, NULL);
    retry++;
  } while (retry < RETRY_COUNT);

  if (ret < 0) {
    perror("Failed to cpc_init ");
    return (uint32_t)ret;
  }

  // Open Bluetooth endpoint
  retry = 0;
  do {
    ret = cpc_open_endpoint(lib_handle,
                            &endpoint,
                            SL_CPC_ENDPOINT_BLUETOOTH_RCP,
                            CPC_TRANSMIT_WINDOW);
    if (ret > 0) {
      ep_sock_fd = ret;
      break;
    }
    nanosleep((const struct timespec[]){ { 0, CPC_RETRY_SLEEP_NS } }, NULL);
    retry++;
  } while (retry < RETRY_COUNT);

  if (ret < 0) {
    perror("Failed to cpc_open_endpoint ");
    return (uint32_t)ret;
  }

  // Open virtual UART device
  ret = openpty(&pty_m, &pty_s, NULL, NULL, NULL);
  if (ret >= 0) {
    int flags = fcntl(pty_m, F_GETFL, 0);
    flags = flags | O_NONBLOCK;
    fcntl(pty_m, F_SETFL, flags);
    char *pName = ttyname(pty_s);
    printf("Name of secondary pty side is <%s>\n", pName);
    remove(SYMLINK_PATH);
    if (symlink(pName, SYMLINK_PATH) != 0) {
      fprintf(stderr,
              "Error creating symlink (%s): %s\n",
              SYMLINK_PATH,
              strerror(errno));
    }
  }

  return (uint32_t)ret;
}

/**************************************************************************//**
 * Callback to register reset from other end.
 *****************************************************************************/
static void reset_callback(void)
{
  has_reset = true;
}

/**************************************************************************//**
 * Reset CPC communication after other end restarted.
 *****************************************************************************/
int reset_cpc(void)
{
  int ret;
  uint8_t retry;

  if (DEBUG) {
    printf("\n\nRESET\n\n");
  }

  // Close previously opened Bluetooth endpoint
  if (ep_sock_fd > 0) {
    ret = cpc_close_endpoint(&endpoint);
    if (ret == 0) {
      ep_sock_fd = -1;
    } else {
      perror("Failed to cpc_close_endpoint ");
      return ret;
    }
  }

  // Restart connection to CPCd
  retry = 0;
  do {
    ret = cpc_restart(&lib_handle);
    if (ret == 0) {
      break;
    }
    nanosleep((const struct timespec[]){ { 0, CPC_RETRY_SLEEP_NS } }, NULL);
    retry++;
  } while (retry < RETRY_COUNT);

  if (ret < 0) {
    perror("Failed to cpc_restart ");
    return ret;
  }

  // Open Bluetooth endpoint
  retry = 0;
  do {
    ret = cpc_open_endpoint(lib_handle,
                            &endpoint,
                            SL_CPC_ENDPOINT_BLUETOOTH_RCP,
                            CPC_TRANSMIT_WINDOW);
    if (ret > 0) {
      ep_sock_fd = ret;
      break;
    }
    nanosleep((const struct timespec[]){ { 0, CPC_RETRY_SLEEP_NS } }, NULL);
    retry++;
  } while (retry < RETRY_COUNT);

  if (ret < 0) {
    perror("Failed to cpc_open_endpoint ");
  }

  return ret;
}

/**************************************************************************//**
 * Main.
 *****************************************************************************/
int main(int argc, char *argv[])
{
  int ret;

  // Set up custom signal handler for user interrupt and termination request.
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);

  // Set device unique name if different from default
  if (argc > 1) {
    strcpy(cpc_instance, argv[1]);
  } else {
    strcpy(cpc_instance, "cpcd_0");
  }

  // Start CPC and PTY communication
  if (startup() < 0) {
    exit(EXIT_FAILURE);
  }

  // Reset cpc communication if daemon signals
  while (run) {
    if (has_reset) {
      has_reset = false;
      ret = reset_cpc();
      if (ret < 0) {
        perror("Failed to reset_cpc ");
        exit(EXIT_FAILURE);
      }
    } else {
      ret = cpc_poll_fds();
      if (ret < 0) {
        perror("select error");
      }
    }
  }
}

/**************************************************************************//**
 * Prints the buffer passed in the arguments
 *****************************************************************************/
static void print_buffer(const uint8_t *packet_buf, const ssize_t packet_len)
{
  printf("[ ");
  for (ssize_t i = 0; i < packet_len; i++) {
    printf("0x%02x ", packet_buf[i]);
  }
  printf("]\n");
}

/**************************************************************************//**
 * Returns the length of the first HCI packet in the buffer
 *****************************************************************************/
static int parse_hci_packet(const uint8_t *hci_buffer, const ssize_t hci_buffer_len)
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
    printf("Warning: possibly malformed HCI packet received\n");
    printf("hci_packet_buf=");
    print_buffer(hci_buffer, hci_packet_len);
    return hci_buffer_len;
  }

  // Calculate the actual size of the HCI packet in the buffer
  hci_packet_len = hci_packet_type_and_header_size + payload_packet_len;
  if (DEBUG && (hci_buffer_len != hci_packet_len)) {
    printf("Parsed packet from multiple in buffer; hci_packet_len='%ld' hci_buffer_len='%ld'\n", hci_packet_len, hci_buffer_len);
  }
  return hci_packet_len;
}

int cpc_poll_fds(void)
{
  int ret;
  int max_fd;
  ssize_t size = 0;
  ssize_t size2 = 0;
  uint8_t *hci_packet_buf;
  ssize_t hci_packet_len;
  struct timeval tv;
  tv.tv_sec  = TIMEOUT_IN_SEC;
  tv.tv_usec = TIMEOUT_IN_USEC;

  fd_set readfds;

  FD_ZERO(&readfds);
  FD_SET(pty_m, &readfds);
  FD_SET(ep_sock_fd, &readfds);

  max_fd = MAX(pty_m, ep_sock_fd);

  ret = select(max_fd + 1, &readfds, NULL, NULL, &tv);
  if ((ret < 0) && (errno != EINTR)) {
    return ret;
  }

  if (FD_ISSET(pty_m, &readfds)) {
    size = read(pty_m, data_to_cpc, TO_CPC_BUF_SIZE);
    if (size > 0) {
      // Parse all HCI packets from the buffer and send them separately to CPC
      hci_packet_buf = data_to_cpc;
      do {
        hci_packet_len = parse_hci_packet(data_to_cpc, size);
        if (DEBUG) {
          printf("cpc_write - size='%02zd' ", hci_packet_len);
          printf("data_to_cpc=");
          print_buffer(data_to_cpc, hci_packet_len);
        }
        size2 = cpc_write_endpoint(endpoint, hci_packet_buf, hci_packet_len, 0);
        if (size2 < 0) {
          perror("Failed to cpc_write_endpoint");
          return FAILURE;
        }
        size -= hci_packet_len;
        hci_packet_buf += hci_packet_len;
      } while (size >= hci_packet_len);
    } else if (errno != EAGAIN && errno != ECONNRESET) {
      perror("pty operation failed");
      return FAILURE;
    }
  }

  if (FD_ISSET(ep_sock_fd, &readfds)) {
    size = cpc_read_endpoint(endpoint,
                             &data_from_cpc[0],
                             FROM_CPC_BUF_SIZE,
                             CPC_ENDPOINT_READ_FLAG_NON_BLOCKING);
    if (size > 0) {
      if (DEBUG) {
        printf("cpc_read  - size='%02zd' ", size);
        printf("data_from_cpc=");
        print_buffer(data_from_cpc, size);
      }
      // Write data to pty
      write(pty_m, &data_from_cpc[0], size);
      memset(&data_from_cpc[0], 0, FROM_CPC_BUF_SIZE);
    } else if ((int)size != -EAGAIN && (int)size != -ECONNRESET) {
      perror("pty operation failed");
      return FAILURE;
    }
  }

  return SUCCESS;
}
