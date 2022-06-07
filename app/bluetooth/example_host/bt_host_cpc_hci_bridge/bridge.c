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
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <pty.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

// set this to 1 for more runtime log messages
#define DEBUG 0

#define TO_CPC_BUF_SIZE     256
#define FROM_CPC_BUF_SIZE   SL_CPC_READ_MINIMUM_SIZE
#define INST_NAME_LEN       100
#define RETRY_COUNT         10
#define CPC_RETRY_SLEEP_NS  100000000L
#define CPC_RESET_SLEEP_NS  10000L
#define THREAD_SLEEP_NS     1L
#define CPC_TRANSMIT_WINDOW 1
#define SYMLINK_PATH        "pts_hci"

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

// end the receiving loop if signal is received.
static volatile bool run = true;
// signal if the controller was reset
static volatile bool has_reset = false;

static void reset_callback(void);

// two worker threads
static pthread_t thread_rx;
static pthread_t thread_tx;

// Static receive function
static void *cpc_to_pty_func(void *ptr);
static void *pty_to_cpc_func(void *ptr);

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
  uint8_t retry = 0;

  // Initialize CPC communication
  do {
    ret = cpc_init(&lib_handle, cpc_instance, false, reset_callback);
    if (ret == 0) {
      // speed up boot process if everything seems ok
      break;
    }
    nanosleep((const struct timespec[]){{ 0, CPC_RETRY_SLEEP_NS } }, NULL);
    retry++;
  } while ((ret != 0) && (retry < RETRY_COUNT));

  if (ret < 0) {
    perror("cpc_init: ");
    return ret;
  }

  // Start Bluetooth endpoint
  ret = cpc_open_endpoint(lib_handle,
                          &endpoint,
                          SL_CPC_ENDPOINT_BLUETOOTH_RCP,
                          CPC_TRANSMIT_WINDOW);
  if (ret < 0) {
    perror("cpc_open_endpoint ");
    return ret;
  }

  // Open virtual UART device
  ret = openpty(&pty_m, &pty_s, NULL, NULL, NULL);
  if (ret >= 0) {
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
  return ret;
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
  uint8_t retry = 0;

  if (DEBUG) {
    printf("\n\nRESET\n\n");
  }

  // Restart cpp communication
  do {
    ret = cpc_restart(&lib_handle);
    if (ret == 0) {
      // speed up boot process if everything seems ok
      break;
    }
    nanosleep((const struct timespec[]){{ 0, CPC_RETRY_SLEEP_NS } }, NULL);
    retry++;
  } while ((ret != 0) && (retry < RETRY_COUNT));
  has_reset = false;

  if (ret < 0) {
    perror("cpc restart ");
    return ret;
  }

  // Open Bluetooth endpoint
  ret = cpc_open_endpoint(lib_handle,
                          &endpoint,
                          SL_CPC_ENDPOINT_BLUETOOTH_RCP,
                          CPC_TRANSMIT_WINDOW);
  if (ret < 0) {
    perror(" open endpoint ");
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
  // Creating receiving working threads
  ret = pthread_create(&thread_rx, NULL, cpc_to_pty_func, NULL);
  if (ret) {
    printf("Error - pthread_create(thread_rx) return code: %d\n", ret);
    exit(EXIT_FAILURE);
  }
  ret = pthread_create(&thread_tx, NULL, pty_to_cpc_func, NULL);
  if (ret) {
    printf("Error - pthread_create(thread_tx) return code: %d\n", ret);
    exit(EXIT_FAILURE);
  }

  if (DEBUG) {
    printf("\nCPC - VHCI bridge working, main thread is going to sleep\n\n");
  }

  // Reset cpc communication if daemon signals
  while (run) {
    if (has_reset) {
      ret = reset_cpc();
      if (ret < 0) {
        perror("reset ");
        exit(EXIT_FAILURE);
      }
    }
    nanosleep((const struct timespec[]){{ 0, CPC_RESET_SLEEP_NS } }, NULL);
  }
}

/**************************************************************************//**
 * Working thread from CPCd
 *****************************************************************************/
void *cpc_to_pty_func(void *ptr)
{
  ssize_t size = 0;

  // unused variable
  (void)ptr;

  while (run) {
    // Read data from cpc
    size = cpc_read_endpoint(endpoint,
                             &data_from_cpc[0],
                             FROM_CPC_BUF_SIZE,
                             SL_CPC_FLAG_NON_BLOCK);
    if (size > 0) {
      if (DEBUG) {
        printf("Len from cpc %zd\n", size);
        printf("Data from cpc: ");
        for (int i = 0; i < size; i++) {
          printf("%x ", data_from_cpc[i]);
        }
        printf("\n");
      }
      // Write data to pty
      write(pty_m, &data_from_cpc[0], size);
      memset(&data_from_cpc[0], 0, FROM_CPC_BUF_SIZE);
    } else if (has_reset) {
      // intentionally left blank
    } else if (errno != EAGAIN && errno != ECONNRESET) {
      perror("cpc_to_pty_func error ");
      exit(-1);
    }
    nanosleep((const struct timespec[]){{ 0, THREAD_SLEEP_NS } }, NULL);
  }
  return NULL;
}

/**************************************************************************//**
 * Working thread to CPCd
 *****************************************************************************/
void *pty_to_cpc_func(void *ptr)
{
  ssize_t size = 0;

  // unused variable
  (void)ptr;

  while (run) {
    // Read data from pty
    size = read(pty_m, data_to_cpc, TO_CPC_BUF_SIZE);
    if (size > 0) {
      if (DEBUG) {
        printf("Len to cpc %zd\n", size);
        printf("Data to cpc: ");
        for (int i = 0; i < size; i++) {
          printf("%x ", data_to_cpc[i]);
        }
        printf("\n");
      }
      // Write data to cpc
      cpc_write_endpoint(endpoint, &data_to_cpc[0], size, 0);
      memset(&data_to_cpc[0], 0, TO_CPC_BUF_SIZE);
    } else if (has_reset) {
      // intentionally left blank
    } else if (errno != EAGAIN && errno != ECONNRESET) {
      perror("pty_to_cpc_func error");
      exit(-1);
    }
    nanosleep((const struct timespec[]){{ 0, THREAD_SLEEP_NS } }, NULL);
  }
  return NULL;
}
