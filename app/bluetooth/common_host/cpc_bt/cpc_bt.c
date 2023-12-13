/***************************************************************************//**
 * @file
 * @brief CPC communication (POSIX only)
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

#include "sl_cpc.h"
#include "app_log.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <pty.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define RETRY_COUNT         10
#define CPC_RETRY_SLEEP_NS  100000000L
#define CPC_RESET_SLEEP_NS  10000L
#define CPC_TRANSMIT_WINDOW 1
#define FROM_CPC_BUF_SIZE   SL_CPC_READ_MINIMUM_SIZE
#define perror_errno(str, errno) app_log_error("%s: %s" APP_LOG_NL, str, strerror(errno))

// cpc related structures
static cpc_handle_t lib_handle;
static cpc_endpoint_t endpoint;

// cpc endpoint fd
static int ep_sock_fd;

// temporary rx buffer
typedef struct {
  int32_t len;
  uint8_t buf[FROM_CPC_BUF_SIZE];
} buf_t;

static buf_t buf_rx = { 0 };

// end the receiving loop if signal is received.
static volatile bool run = true;
// signal if the controller was reset
static volatile sig_atomic_t has_reset = false;

// two worker threads
static pthread_t sv;

// -----------------------------------------------------------------------------
// Private Function Declarations

static void reset_callback(void);
static int reset_cpc(void);
static void *supervisor(void *ptr);

// -----------------------------------------------------------------------------
// Public Function Definitions

int32_t cpc_bt_open(void *handle, char *cpc_instance)
{
  (void)handle;
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
    perror_errno("cpc_init failed", -ret);
    return ret;
  }

  // Open Bluetooth endpoint
  retry = 0;
  do {
    ret = cpc_open_endpoint(lib_handle,
                            &endpoint,
                            SL_CPC_ENDPOINT_BLUETOOTH,
                            CPC_TRANSMIT_WINDOW);
    if (ret > 0) {
      ep_sock_fd = ret;
      break;
    }
    nanosleep((const struct timespec[]){ { 0, CPC_RETRY_SLEEP_NS } }, NULL);
    retry++;
  } while (retry < RETRY_COUNT);

  if (ret < 0) {
    perror_errno("cpc_open_endpoint failed", -ret);
    return ret;
  }

  // Create supervisory thread
  ret = pthread_create(&sv, NULL, supervisor, NULL);
  if (ret) {
    perror("pthread_create failed");
    return ret;
  }

  return ret;
}

int32_t cpc_bt_tx(void *handle, uint32_t data_length, uint8_t *data)
{
  (void)handle;
  ssize_t size = 0;

  if (!has_reset) {
    size = cpc_write_endpoint(endpoint, &data[0], data_length, CPC_ENDPOINT_WRITE_FLAG_NONE);
    if (size < 0) {
      perror_errno("cpc_write_endpoint failed", -size);
    }
  } else {
    // In case of reset we don't care if send was successful or not
    size = data_length;
  }

  return (int32_t)size;
}

int32_t cpc_bt_rx(void *handle, uint32_t data_length, uint8_t *data)
{
  (void)handle;
  (void)data_length;

  if (buf_rx.len > 0) {
    memcpy(data, buf_rx.buf, buf_rx.len);
  }

  return buf_rx.len;
}

int32_t cpc_bt_rx_peek(void *handle)
{
  (void)handle;
  ssize_t size;

  if (!has_reset) {
    // Return if the endpoint has not been reopened after the reset
    if (ep_sock_fd <= 0) {
      return 0;
    }

    // Make read blocking - possible because threaded structure in host_comm
    size = cpc_read_endpoint(endpoint, &buf_rx.buf,
                             FROM_CPC_BUF_SIZE, CPC_ENDPOINT_READ_FLAG_NONE);

    if (size < 0) {
      // Swallow errors like EINVAL and ECONNRESET because the fd will be
      // invalid while the device is starting up after the reset.
      buf_rx.len = 0;
    } else {
      buf_rx.len = (int32_t)size;
    }
  } else {
    // If in reset, don't try to read
    buf_rx.len = 0;
  }

  return buf_rx.len;
}

int32_t cpc_bt_close(void *handle)
{
  (void)handle;
  int ret;

  ret = cpc_close_endpoint(&endpoint);
  if (ret == 0) {
    ep_sock_fd = -1;
  } else {
    perror_errno("cpc_close_endpoint failed", -ret);
  }

  return ret;
}

// -----------------------------------------------------------------------------
// Private Function Definitions

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
static int reset_cpc(void)
{
  int ret;
  uint8_t retry;

  app_log_debug("RESET" APP_LOG_NL);

  // Close previously opened Bluetooth endpoint
  if (ep_sock_fd > 0) {
    ret = cpc_close_endpoint(&endpoint);
    if (ret == 0) {
      ep_sock_fd = -1;
    } else {
      perror_errno("cpc_close_endpoint failed", -ret);
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
    perror_errno("cpc_restart failed", -ret);
    return ret;
  }

  // Open Bluetooth endpoint
  retry = 0;
  do {
    ret = cpc_open_endpoint(lib_handle,
                            &endpoint,
                            SL_CPC_ENDPOINT_BLUETOOTH,
                            CPC_TRANSMIT_WINDOW);
    if (ret > 0) {
      ep_sock_fd = ret;
      break;
    }
    nanosleep((const struct timespec[]){ { 0, CPC_RETRY_SLEEP_NS } }, NULL);
    retry++;
  } while (retry < RETRY_COUNT);

  if (ret < 0) {
    perror_errno("cpc_open_endpoint failed", -ret);
    return ret;
  }

  return ret;
}

/**************************************************************************//**
 * Supervisor thread
 *****************************************************************************/
static void *supervisor(void *ptr)
{
  (void)ptr;
  int ret;

  while (run) {
    if (has_reset) {
      has_reset = false;
      ret = reset_cpc();
      if (ret < 0) {
        // Better to die here than continue to work falsely
        exit(ret);
      }
    }

    nanosleep((const struct timespec[]){ { 0, CPC_RESET_SLEEP_NS } }, NULL);
  }
  return NULL;
}
