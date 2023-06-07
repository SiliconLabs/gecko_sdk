/***************************************************************************/ /**
 * @file
 * @brief CPC GPIO Endpoint API implementation.
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
#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#include "sl_cpc.h"
#include "sli_cpc.h"

#if defined(SL_CATALOG_KERNEL_PRESENT)
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#include "sl_cpc_gpio_expander_kernel_config.h"
#endif
#include "sl_cpc_gpio_expander.h"
#include "sl_cpc_gpio_expander_config.h"

#include "sl_assert.h"
#include "sl_enum.h"
#include "em_core.h"
#include "em_gpio.h"
#include "em_system.h"
#include "string.h"

/*******************************************************************************
 **************************   DEFINES   ****************************************
 ******************************************************************************/
#define CPC_GPIO_EXPANDER_API_VERSION_MAJOR 1
#define CPC_GPIO_EXPANDER_API_VERSION_MINOR 0
#define CPC_GPIO_EXPANDER_API_VERSION_PATCH 0

#ifndef CPC_GPIO_EXPANDER_OS_DELAY_MS
#define CPC_GPIO_EXPANDER_OS_DELAY_MS 1
#endif

/*******************************************************************************
 **************************   ENUMS   ******************************************
 ******************************************************************************/
/// @brief Enumeration representing command types from the host.
SL_ENUM_GENERIC(host_cmd_t, uint8_t){
  HOST_CMD_GET_VERSION = 0,
  HOST_CMD_GET_UNIQUE_ID = 1,
  HOST_CMD_GET_CHIP_LABEL = 2,
  HOST_CMD_GET_GPIO_COUNT = 3,
  HOST_CMD_GET_GPIO_NAME = 4,
  HOST_CMD_GET_GPIO_VALUE = 5,
  HOST_CMD_SET_GPIO_VALUE = 6,
  HOST_CMD_SET_GPIO_CONFIG = 7,
  HOST_CMD_SET_GPIO_DIRECTION = 8,
};

/// @brief Enumeration representing command types from the secondary.
SL_ENUM_GENERIC(secondary_cmd_t, uint8_t){
  SECONDARY_CMD_VERSION_IS = 128,
  SECONDARY_CMD_STATUS_IS = 129,
  SECONDARY_CMD_UNIQUE_ID_IS = 130,
  SECONDARY_CMD_CHIP_LABEL_IS = 131,
  SECONDARY_CMD_GPIO_COUNT_IS = 132,
  SECONDARY_CMD_GPIO_NAME_IS = 133,
  SECONDARY_CMD_GPIO_VALUE_IS = 134,
  SECONDARY_CMD_UNSUPPORTED_CMD_IS = UINT8_MAX,
};

/// @brief Enumeration representing gpio config types.
SL_ENUM_GENERIC(gpio_config_t, uint8_t){
  GPIO_CONFIG_BIAS_DISABLE = 0,
  GPIO_CONFIG_BIAS_PULL_DOWN = 1,
  GPIO_CONFIG_BIAS_PULL_UP = 2,
  GPIO_CONFIG_DRIVE_OPEN_DRAIN = 3,
  GPIO_CONFIG_DRIVE_OPEN_SOURCE = 4,
  GPIO_CONFIG_DRIVE_PUSH_PULL = 5,
};

/// @brief Enumeration representing gpio direction types.
SL_ENUM_GENERIC(gpio_direction_t, uint8_t){
  GPIO_DIRECTION_OUTPUT = 0,
  GPIO_DIRECTION_INPUT = 1,
  GPIO_DIRECTION_DISABLED = 2,
};

/// @brief Enumeration representing gpio status types.
SL_ENUM_GENERIC(gpio_status_t, uint8_t){
  GPIO_STATUS_OK = 0,
  GPIO_STATUS_NOT_SUPPORTED = 1,
  GPIO_STATUS_INVALID_PIN = 2,
  GPIO_STATUS_UNKNOWN = UINT8_MAX,
};

/// @brief Enumeration representing endpoint state types.
SL_ENUM_GENERIC(endpoint_state_t, uint8_t){
  ENDPOINT_STATE_INIT,
  ENDPOINT_STATE_RESTART,
  ENDPOINT_STATE_WRITE_COMPLETED,
  ENDPOINT_STATE_WRITE_PENDING,
  ENDPOINT_STATE_REPLY_READY,
};

/*******************************************************************************
 **************************   STRUCTS   ****************************************
 ******************************************************************************/
/// @brief Struct representing a header.
typedef struct __attribute__((packed)) {
  uint8_t cmd;
  uint8_t len;
} header_t;

/// @brief Struct representing a host header.
typedef struct __attribute__((packed)) {
  uint8_t seq;
} host_header_t;

/// @brief Struct representing a secondary header.
typedef struct __attribute__((packed)) {
  uint8_t seq;
} secondary_header_t;

/// @brief Struct representing a get version request from the host.
typedef struct __attribute__((packed)) {
  header_t header;
} get_version_t;

typedef struct __attribute__((packed)){
  uint8_t major;
  uint8_t minor;
  uint8_t patch;
} version_t;

/// @brief Struct representing a version response from the secondary.
typedef struct __attribute__((packed)) {
  header_t header;
  version_t version;
} version_is_t;

/// @brief Struct representing a status response from the secondary.
typedef struct __attribute__((packed)) {
  header_t header;
  secondary_header_t secondary_header;
  gpio_status_t status;
} status_is_t;

/// @brief Struct representing a get unique identifier request from the host.
typedef struct __attribute__((packed)) {
  header_t header;
  host_header_t host_header;
} get_unique_id_t;

/// @brief Struct representing a get unique identifier response from the secondary.
typedef struct __attribute__((packed)) {
  header_t header;
  secondary_header_t secondary_header;
  uint64_t unique_id;
} unique_id_is_t;

/// @brief Struct representing a get chip label request from the host.
typedef struct __attribute__((packed)) {
  header_t header;
  host_header_t host_header;
} get_chip_label_t;

/// @brief Struct representing a get chip label response from the secondary.
typedef struct __attribute__((packed)) {
  header_t header;
  secondary_header_t secondary_header;
  char chip_label[];
} chip_label_is_t;

/// @brief Struct representing a get gpio count request from the host.
typedef struct __attribute__((packed)) {
  header_t header;
  host_header_t host_header;
} get_gpio_count_t;

/// @brief Struct representing a gpio count response from the secondary.
typedef struct __attribute__((packed)) {
  header_t header;
  secondary_header_t secondary_header;
  uint8_t count;
} gpio_count_is_t;

/// @brief Struct representing a get gpio name request from the host.
typedef struct __attribute__((packed)) {
  header_t header;
  host_header_t host_header;
  uint8_t pin;
} get_gpio_name_t;

/// @brief Struct representing a gpio name response from the secondary.
typedef struct __attribute__((packed)) {
  header_t header;
  secondary_header_t secondary_header;
  char name[];
} gpio_name_is_t;

/// @brief Struct representing a get gpio value request from the host.
typedef struct __attribute__((packed)) {
  header_t header;
  host_header_t host_header;
  uint8_t pin;
} get_gpio_value_t;

/// @brief Struct representing a gpio value response from the secondary.
typedef struct __attribute__((packed)) {
  header_t header;
  secondary_header_t secondary_header;
  uint8_t value;
} gpio_value_is_t;

/// @brief Struct representing a set gpio value request from the host.
typedef struct __attribute__((packed)) {
  header_t header;
  host_header_t host_header;
  uint8_t pin;
  uint8_t value;
} set_gpio_value_t;

/// @brief Struct representing a set gpio config request from the host.
typedef struct __attribute__((packed)) {
  header_t header;
  host_header_t host_header;
  uint8_t pin;
  gpio_config_t config;
} set_gpio_config_t;

/// @brief Struct representing a set gpio direction request from the host.
typedef struct __attribute__((packed)) {
  header_t header;
  host_header_t host_header;
  uint8_t pin;
  gpio_direction_t direction;
} set_gpio_direction_t;

/// @brief Struct representing an unsupported cmd response from the secondary.
typedef struct __attribute__((packed)) {
  header_t header;
  uint8_t unsupported_cmd;
} unsupported_cmd_is_t;

/// @brief Struct representing a reply buffer.
typedef struct {
  uint8_t buffer[64];
  uint16_t buffer_len;
} tx_buffer_t;

/*******************************************************************************
 **************************   GLOBAL VARIABLES   *******************************
 ******************************************************************************/

// GPIO Expander table
extern sl_cpc_gpio_expander_handle_t sl_cpc_gpio_expander_handle_table[];
extern uint32_t sl_cpc_gpio_expander_handle_count;

#if defined(SLI_CPC_GPIO_EXPANDER_UNDER_TEST)
// Sequence number offset, injected during testing
extern uint8_t sli_cpc_gpio_expander_under_test_seq_offset;
#endif

/*******************************************************************************
 **************************   LOCAL VARIABLES   ********************************
 ******************************************************************************/
#if defined(SL_CATALOG_KERNEL_PRESENT)
#define THREAD_STACK_SIZE   (SL_CPC_GPIO_EXPANDER_TASK_STACK_SIZE * sizeof(void *)) & 0xFFFFFFF8u
__ALIGNED(4) static uint8_t thread_cb[osThreadCbSize];
__ALIGNED(8) static uint8_t thread_stack[THREAD_STACK_SIZE];
__ALIGNED(4) static uint8_t semaphore_cb[osSemaphoreCbSize];

// Thread handle
static osThreadId_t thread_id;

// Endpoint state change signal
static osSemaphoreId_t state_change_signal;
#endif

// Endpoint restart flag
static bool restart_flag = false;

// Endpoint state
static endpoint_state_t state = ENDPOINT_STATE_INIT;

// Endpoint handle
static sl_cpc_endpoint_handle_t ep_gpio;

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/
static void on_gpio_write_completed(sl_cpc_user_endpoint_id_t endpoint_id,
                                    void *buffer, void *arg, sl_status_t status);

static void on_gpio_error(sl_cpc_user_endpoint_id_t endpoint_id,
                          void *buffer, void *arg, sl_status_t status);

static sl_status_t init_endpoint(void);

static void restart_endpoint(void);

static endpoint_state_t wait_state_change(void);

static void signal_state_change(endpoint_state_t new_state);

static void read_packet(tx_buffer_t *tx_buffer);

static void parse_packet(void *rx_buffer, tx_buffer_t *tx_buffer);

static void transmit_packet(tx_buffer_t *tx_buffer);

static void status_is(gpio_status_t status, tx_buffer_t *tx_buffer);

static void on_get_version(void *rx_buffer, tx_buffer_t *tx_buffer);

static void on_get_gpio_count(void *rx_buffer, tx_buffer_t *tx_buffer);

static void on_get_gpio_name(void *rx_buffer, tx_buffer_t *tx_buffer);

static void on_get_gpio_value(void *rx_buffer, tx_buffer_t *tx_buffer);

static void on_set_gpio_value(void *rx_buffer, tx_buffer_t *tx_buffer);

static void on_set_gpio_config(void *rx_buffer, tx_buffer_t *tx_buffer);

static void on_set_gpio_direction(void *rx_buffer, tx_buffer_t *tx_buffer);

static void on_get_chip_label(void *rx_buffer, tx_buffer_t *tx_buffer);

static void on_unsupported_cmd(uint8_t unsupported_cmd, tx_buffer_t *tx_buffer);

/***************************************************************************//**
 * Write completed
 ******************************************************************************/
static void on_gpio_write_completed(sl_cpc_user_endpoint_id_t endpoint_id,
                                    void *buffer, void *arg, sl_status_t status)
{
  (void) buffer;
  (void) arg;
  (void) status;

  EFM_ASSERT(endpoint_id == SL_CPC_ENDPOINT_GPIO);
  signal_state_change(ENDPOINT_STATE_WRITE_COMPLETED);
}

/***************************************************************************//**
 * Error callback
 ******************************************************************************/
static void on_gpio_error(sl_cpc_user_endpoint_id_t endpoint_id,
                          void *buffer, void *arg, sl_status_t status)
{
  (void) buffer;
  (void) arg;
  (void) status;

  EFM_ASSERT(endpoint_id == SL_CPC_ENDPOINT_GPIO);
  restart_flag = true;
  signal_state_change(ENDPOINT_STATE_RESTART);
}

/***************************************************************************//**
 * Initialize endpoint
 ******************************************************************************/
static sl_status_t init_endpoint(void)
{
  sl_status_t status;

  status = sli_cpc_open_service_endpoint(&ep_gpio, SL_CPC_ENDPOINT_GPIO, 0, 1);
  if (status != SL_STATUS_OK) {
    EFM_ASSERT(false);
    return status;
  }

  status = sl_cpc_set_endpoint_option(&ep_gpio, SL_CPC_ENDPOINT_ON_IFRAME_WRITE_COMPLETED,
                                      (void *)on_gpio_write_completed);
  if (status != SL_STATUS_OK) {
    sl_cpc_close_endpoint(&ep_gpio);
    EFM_ASSERT(false);
    return status;
  }

  status = sl_cpc_set_endpoint_option(&ep_gpio,
                                      SL_CPC_ENDPOINT_ON_ERROR,
                                      (void *)on_gpio_error);
  if (status != SL_STATUS_OK) {
    sl_cpc_close_endpoint(&ep_gpio);
    EFM_ASSERT(false);
    return status;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Wait for state transition.
 ******************************************************************************/
static endpoint_state_t wait_state_change(void)
{
#if defined(SL_CATALOG_KERNEL_PRESENT)
  EFM_ASSERT(osSemaphoreAcquire(state_change_signal, osWaitForever) == osOK);
#endif // SL_CATALOG_KERNEL_PRESENT
  return state;
}

/***************************************************************************//**
 * Signal state transition.
 ******************************************************************************/
static void signal_state_change(endpoint_state_t new_state)
{
  state = new_state;
#if defined(SL_CATALOG_KERNEL_PRESENT)
  osSemaphoreRelease(state_change_signal);
#endif // SL_CATALOG_KERNEL_PRESENT
}

/***************************************************************************//**
 * Restart endpoint.
 ******************************************************************************/
static void restart_endpoint(void)
{
  sl_cpc_endpoint_state_t ep_state;

  ep_state = sl_cpc_get_endpoint_state(&ep_gpio);

  switch (ep_state) {
    case SL_CPC_STATE_CLOSED:
    case SL_CPC_STATE_CLOSING:
      break;
    case SL_CPC_STATE_OPEN:
      EFM_ASSERT(false);
      sl_cpc_close_endpoint(&ep_gpio);
      break;
    case SL_CPC_STATE_ERROR_DESTINATION_UNREACHABLE:
    case SL_CPC_STATE_ERROR_SECURITY_INCIDENT:
    case SL_CPC_STATE_ERROR_FAULT:
      sl_cpc_close_endpoint(&ep_gpio);
      break;
    case SL_CPC_STATE_FREED:
      restart_flag = false;
      if (init_endpoint() == SL_STATUS_OK) {
        signal_state_change(ENDPOINT_STATE_INIT);
      } else {
        restart_flag = true;
        EFM_ASSERT(false);
      }
      break;
    default:
      EFM_ASSERT(false);
      sl_cpc_close_endpoint(&ep_gpio);
      break;
  }

#if defined(SL_CATALOG_KERNEL_PRESENT)
  osDelay(((uint64_t)osKernelGetTickFreq() * CPC_GPIO_EXPANDER_OS_DELAY_MS) / 1000);
#endif // SL_CATALOG_KERNEL_PRESENT
}

/***************************************************************************//**
 * Get a status_is reply packet ready.
 ******************************************************************************/
static void status_is(gpio_status_t status, tx_buffer_t *tx_buffer)
{
  status_is_t *tx_packet = (status_is_t *) tx_buffer->buffer;

  tx_packet->header.cmd = SECONDARY_CMD_STATUS_IS;
  tx_packet->status = status;

  tx_packet->header.len = (sizeof(*tx_packet) - (sizeof(header_t)));
  tx_buffer->buffer_len = sizeof(*tx_packet);
}

/***************************************************************************//**
 * Parse HOST_CMD_GET_VERSION packet and get a reply packet ready.
 ******************************************************************************/
static void on_get_version(void *rx_buffer, tx_buffer_t *tx_buffer)
{
  get_version_t *rx_packet = (get_version_t *) rx_buffer;
  version_is_t *tx_packet = (version_is_t *) tx_buffer->buffer;

  EFM_ASSERT(rx_packet->header.len == 0);

  tx_packet->header.cmd = SECONDARY_CMD_VERSION_IS;
  tx_packet->header.len = sizeof(tx_packet->version);

  tx_packet->version.major = CPC_GPIO_EXPANDER_API_VERSION_MAJOR;
  tx_packet->version.minor = CPC_GPIO_EXPANDER_API_VERSION_MINOR;
  tx_packet->version.patch = CPC_GPIO_EXPANDER_API_VERSION_PATCH;

  tx_buffer->buffer_len = sizeof(*tx_packet);
}

/***************************************************************************//**
 * Parse unsupported packet and get a reply packet ready.
 ******************************************************************************/
static void on_unsupported_cmd(uint8_t unsupported_cmd, tx_buffer_t *tx_buffer)
{
  unsupported_cmd_is_t *tx_packet = (unsupported_cmd_is_t *) tx_buffer->buffer;

  tx_packet->header.cmd = SECONDARY_CMD_UNSUPPORTED_CMD_IS;
  tx_packet->header.len = (sizeof(*tx_packet) - (sizeof(header_t)));
  tx_packet->unsupported_cmd = unsupported_cmd;

  tx_buffer->buffer_len = sizeof(*tx_packet);
}

/***************************************************************************//**
 * Parse HOST_CMD_GET_GPIO_COUNT packet and get a reply packet ready.
 ******************************************************************************/
static void on_get_gpio_count(void *rx_buffer, tx_buffer_t *tx_buffer)
{
  get_gpio_count_t *rx_packet = (get_gpio_count_t *) rx_buffer;
  gpio_count_is_t *tx_packet = (gpio_count_is_t *) tx_buffer->buffer;

  EFM_ASSERT(rx_packet->header.len == (sizeof(*rx_packet) - (sizeof(header_t))));

  tx_packet->header.cmd = SECONDARY_CMD_GPIO_COUNT_IS;
  tx_packet->header.len = (sizeof(*tx_packet) - (sizeof(header_t)));

  tx_packet->count = sl_cpc_gpio_expander_handle_count;

  tx_packet->secondary_header.seq = rx_packet->host_header.seq;

  tx_buffer->buffer_len = sizeof(*tx_packet);
}

/***************************************************************************//**
 * Parse HOST_CMD_GET_GPIO_NAME packet and get a reply packet ready.
 ******************************************************************************/
static void on_get_gpio_name(void *rx_buffer, tx_buffer_t *tx_buffer)
{
  get_gpio_name_t *rx_packet = (get_gpio_name_t *) rx_buffer;
  gpio_name_is_t *tx_packet = (gpio_name_is_t *) tx_buffer->buffer;

  EFM_ASSERT(rx_packet->header.len == (sizeof(*rx_packet) - (sizeof(header_t))));

  tx_packet->secondary_header.seq = rx_packet->host_header.seq;

  if (rx_packet->pin < sl_cpc_gpio_expander_handle_count) {
    tx_packet->header.cmd = SECONDARY_CMD_GPIO_NAME_IS;

    const char *name = sl_cpc_gpio_expander_handle_table[rx_packet->pin].name;
    size_t len = MIN(strlen(name), sizeof(tx_buffer->buffer) - sizeof(*tx_packet) - 1);
    memcpy(tx_packet->name, name, len);
    tx_packet->name[len] = '\0';
    len = len + 1;

    tx_packet->header.len = sizeof(*tx_packet) + len - sizeof(header_t);
    tx_buffer->buffer_len = sizeof(*tx_packet) + len;
  } else {
    status_is(GPIO_STATUS_INVALID_PIN, tx_buffer);
  }
}

/***************************************************************************//**
 * Parse HOST_CMD_GET_GPIO_VALUE packet and get a reply packet ready.
 ******************************************************************************/
static void on_get_gpio_value(void *rx_buffer, tx_buffer_t *tx_buffer)
{
  get_gpio_value_t *rx_packet = (get_gpio_value_t *) rx_buffer;
  gpio_value_is_t *tx_packet = (gpio_value_is_t *) tx_buffer->buffer;

  EFM_ASSERT(rx_packet->header.len == (sizeof(*rx_packet) - (sizeof(header_t))));

  tx_packet->secondary_header.seq = rx_packet->host_header.seq;

  if (rx_packet->pin < sl_cpc_gpio_expander_handle_count) {
    tx_packet->header.cmd = SECONDARY_CMD_GPIO_VALUE_IS;

    tx_packet->value = GPIO_PinInGet(sl_cpc_gpio_expander_handle_table[rx_packet->pin].port,
                                     sl_cpc_gpio_expander_handle_table[rx_packet->pin].pin);

    tx_packet->header.len = (sizeof(*tx_packet) - (sizeof(header_t)));
    tx_buffer->buffer_len = sizeof(*tx_packet);
  } else {
    status_is(GPIO_STATUS_INVALID_PIN, tx_buffer);
  }
}

/***************************************************************************//**
 * Parse HOST_CMD_SET_GPIO_VALUE packet and get a reply packet ready.
 ******************************************************************************/
static void on_set_gpio_value(void *rx_buffer, tx_buffer_t *tx_buffer)
{
  set_gpio_value_t *rx_packet = (set_gpio_value_t *) rx_buffer;
  status_is_t *tx_packet = (status_is_t *) tx_buffer->buffer;

  EFM_ASSERT(rx_packet->header.len == (sizeof(*rx_packet) - (sizeof(header_t))));

  tx_packet->secondary_header.seq = rx_packet->host_header.seq;

  if (rx_packet->pin < sl_cpc_gpio_expander_handle_count) {
    if (rx_packet->value) {
      GPIO_PinOutSet(sl_cpc_gpio_expander_handle_table[rx_packet->pin].port,
                     sl_cpc_gpio_expander_handle_table[rx_packet->pin].pin);
    } else {
      GPIO_PinOutClear(sl_cpc_gpio_expander_handle_table[rx_packet->pin].port,
                       sl_cpc_gpio_expander_handle_table[rx_packet->pin].pin);
    }
    status_is(GPIO_STATUS_OK, tx_buffer);
  } else {
    status_is(GPIO_STATUS_INVALID_PIN, tx_buffer);
  }
}

/***************************************************************************//**
 * Parse HOST_CMD_SET_GPIO_CONFIG packet and get a reply packet ready.
 ******************************************************************************/
static void on_set_gpio_config(void *rx_buffer, tx_buffer_t *tx_buffer)
{
  set_gpio_config_t *rx_packet = (set_gpio_config_t *) rx_buffer;
  status_is_t *tx_packet = (status_is_t *) tx_buffer->buffer;

  EFM_ASSERT(rx_packet->header.len == (sizeof(*rx_packet) - (sizeof(header_t))));

  tx_packet->secondary_header.seq = rx_packet->host_header.seq;

  status_is(GPIO_STATUS_UNKNOWN, tx_buffer);

  if (rx_packet->pin < sl_cpc_gpio_expander_handle_count) {
    GPIO_Mode_TypeDef mode = GPIO_PinModeGet(sl_cpc_gpio_expander_handle_table[rx_packet->pin].port,
                                             sl_cpc_gpio_expander_handle_table[rx_packet->pin].pin);

    switch (rx_packet->config) {
      case GPIO_CONFIG_BIAS_DISABLE:
        if (mode == gpioModeInput) {
          status_is(GPIO_STATUS_OK, tx_buffer);
        } else if (mode == gpioModeDisabled) {
          sl_cpc_gpio_expander_handle_table[rx_packet->pin].config |= (1 << rx_packet->config);
          status_is(GPIO_STATUS_OK, tx_buffer);
        }
        break;
      case GPIO_CONFIG_BIAS_PULL_DOWN:
        if (mode == gpioModeInput) {
          GPIO_PinModeSet(sl_cpc_gpio_expander_handle_table[rx_packet->pin].port,
                          sl_cpc_gpio_expander_handle_table[rx_packet->pin].pin, gpioModeInputPull, 0);
          status_is(GPIO_STATUS_OK, tx_buffer);
        } else if (mode == gpioModeDisabled) {
          sl_cpc_gpio_expander_handle_table[rx_packet->pin].config |= (1 << rx_packet->config);
          status_is(GPIO_STATUS_OK, tx_buffer);
        }
        break;
      case GPIO_CONFIG_BIAS_PULL_UP:
        if (mode == gpioModeInput) {
          GPIO_PinModeSet(sl_cpc_gpio_expander_handle_table[rx_packet->pin].port,
                          sl_cpc_gpio_expander_handle_table[rx_packet->pin].pin, gpioModeInputPull, 1);
          status_is(GPIO_STATUS_OK, tx_buffer);
        } else if (mode == gpioModeDisabled) {
          sl_cpc_gpio_expander_handle_table[rx_packet->pin].config |= (1 << rx_packet->config);
          status_is(GPIO_STATUS_OK, tx_buffer);
        }
        break;
      case GPIO_CONFIG_DRIVE_OPEN_DRAIN:
        if (mode == gpioModeDisabled) {
          sl_cpc_gpio_expander_handle_table[rx_packet->pin].config |= (1 << rx_packet->config);
          status_is(GPIO_STATUS_OK, tx_buffer);
        }
        break;
      case GPIO_CONFIG_DRIVE_OPEN_SOURCE:
        if (mode == gpioModeDisabled) {
          sl_cpc_gpio_expander_handle_table[rx_packet->pin].config |= (1 << rx_packet->config);
          status_is(GPIO_STATUS_OK, tx_buffer);
        }
        break;
      case GPIO_CONFIG_DRIVE_PUSH_PULL:
        if (mode == gpioModeDisabled) {
          sl_cpc_gpio_expander_handle_table[rx_packet->pin].config |= (1 << rx_packet->config);
          status_is(GPIO_STATUS_OK, tx_buffer);
        }
        break;
      default:
        status_is(GPIO_STATUS_NOT_SUPPORTED, tx_buffer);
        break;
    }
  } else {
    status_is(GPIO_STATUS_INVALID_PIN, tx_buffer);
  }
}

/***************************************************************************//**
 * Parse HOST_CMD_SET_GPIO_DIRECTION packet and get a reply packet ready.
 ******************************************************************************/
static void on_set_gpio_direction(void *rx_buffer, tx_buffer_t *tx_buffer)
{
  set_gpio_direction_t *rx_packet = (set_gpio_direction_t *) rx_buffer;
  status_is_t *tx_packet = (status_is_t *) tx_buffer->buffer;

  EFM_ASSERT(rx_packet->header.len == (sizeof(*rx_packet) - (sizeof(header_t))));

  tx_packet->secondary_header.seq = rx_packet->host_header.seq;

  status_is(GPIO_STATUS_UNKNOWN, tx_buffer);

  if (rx_packet->pin < sl_cpc_gpio_expander_handle_count) {
    switch (rx_packet->direction) {
      case GPIO_DIRECTION_OUTPUT: {
        uint32_t config = sl_cpc_gpio_expander_handle_table[rx_packet->pin].config;
        sl_cpc_gpio_expander_handle_table[rx_packet->pin].config = 0;

        if (config & (1 << GPIO_CONFIG_DRIVE_OPEN_DRAIN)) {
          if (config & (1 << GPIO_CONFIG_BIAS_PULL_DOWN)) {
            status_is(GPIO_STATUS_NOT_SUPPORTED, tx_buffer);
          } else if (config & (1 << GPIO_CONFIG_BIAS_PULL_UP)) {
            GPIO_PinModeSet(sl_cpc_gpio_expander_handle_table[rx_packet->pin].port,
                            sl_cpc_gpio_expander_handle_table[rx_packet->pin].pin, gpioModeWiredAndPullUp, 0);
            status_is(GPIO_STATUS_OK, tx_buffer);
          } else {
            GPIO_PinModeSet(sl_cpc_gpio_expander_handle_table[rx_packet->pin].port,
                            sl_cpc_gpio_expander_handle_table[rx_packet->pin].pin, gpioModeWiredAnd, 0);
            status_is(GPIO_STATUS_OK, tx_buffer);
          }
        } else if (config & (1 << GPIO_CONFIG_DRIVE_OPEN_SOURCE)) {
          if (config & (1 << GPIO_CONFIG_BIAS_PULL_UP)) {
            status_is(GPIO_STATUS_NOT_SUPPORTED, tx_buffer);
          } else if (config & (1 << GPIO_CONFIG_BIAS_PULL_DOWN)) {
            GPIO_PinModeSet(sl_cpc_gpio_expander_handle_table[rx_packet->pin].port,
                            sl_cpc_gpio_expander_handle_table[rx_packet->pin].pin, gpioModeWiredOrPullDown, 0);
            status_is(GPIO_STATUS_OK, tx_buffer);
          } else {
            GPIO_PinModeSet(sl_cpc_gpio_expander_handle_table[rx_packet->pin].port,
                            sl_cpc_gpio_expander_handle_table[rx_packet->pin].pin, gpioModeWiredOr, 0);
            status_is(GPIO_STATUS_OK, tx_buffer);
          }
        } else if (config & (1 << GPIO_CONFIG_DRIVE_PUSH_PULL)) {
          if (config & (1 << GPIO_CONFIG_BIAS_PULL_UP)) {
            status_is(GPIO_STATUS_NOT_SUPPORTED, tx_buffer);
          } else if (config & (1 << GPIO_CONFIG_BIAS_PULL_DOWN)) {
            status_is(GPIO_STATUS_NOT_SUPPORTED, tx_buffer);
          } else {
            GPIO_PinModeSet(sl_cpc_gpio_expander_handle_table[rx_packet->pin].port,
                            sl_cpc_gpio_expander_handle_table[rx_packet->pin].pin, gpioModePushPull, 0);
            status_is(GPIO_STATUS_OK, tx_buffer);
          }
        } else {
          status_is(GPIO_STATUS_NOT_SUPPORTED, tx_buffer);
        }
      }
      break;
      case GPIO_DIRECTION_INPUT:
        GPIO_PinModeSet(sl_cpc_gpio_expander_handle_table[rx_packet->pin].port,
                        sl_cpc_gpio_expander_handle_table[rx_packet->pin].pin, gpioModeInput, 0);
        status_is(GPIO_STATUS_OK, tx_buffer);
        break;
      case GPIO_DIRECTION_DISABLED:
        GPIO_PinModeSet(sl_cpc_gpio_expander_handle_table[rx_packet->pin].port,
                        sl_cpc_gpio_expander_handle_table[rx_packet->pin].pin, gpioModeDisabled, 0);
        sl_cpc_gpio_expander_handle_table[rx_packet->pin].config = 0;
        status_is(GPIO_STATUS_OK, tx_buffer);
        break;
      default:
        status_is(GPIO_STATUS_NOT_SUPPORTED, tx_buffer);
        break;
    }
  } else {
    status_is(GPIO_STATUS_INVALID_PIN, tx_buffer);
  }
}

/***************************************************************************//**
 * Parse HOST_CMD_GET_UNIQUE_ID packet and get a reply packet ready.
 ******************************************************************************/
static void on_get_unique_id(void *rx_buffer, tx_buffer_t *tx_buffer)
{
  get_unique_id_t *rx_packet = (get_unique_id_t *) rx_buffer;
  EFM_ASSERT(rx_packet->header.len == (sizeof(*rx_packet) - (sizeof(header_t))));

  unique_id_is_t *tx_packet = (unique_id_is_t *) tx_buffer->buffer;

  tx_packet->header.cmd = SECONDARY_CMD_UNIQUE_ID_IS;
  tx_packet->header.len = (sizeof(*tx_packet) - (sizeof(header_t)));

  tx_packet->unique_id = SYSTEM_GetUnique();

  tx_packet->secondary_header.seq = rx_packet->host_header.seq;

  tx_buffer->buffer_len = sizeof(*tx_packet);
}

/***************************************************************************//**
 * Parse HOST_CMD_GET_CHIP_LABEL packet and get a reply packet ready.
 ******************************************************************************/
static void on_get_chip_label(void *rx_buffer, tx_buffer_t *tx_buffer)
{
  get_chip_label_t *rx_packet = (get_chip_label_t *) rx_buffer;
  EFM_ASSERT(rx_packet->header.len == (sizeof(*rx_packet) - (sizeof(header_t))));

  chip_label_is_t *tx_packet = (chip_label_is_t *) tx_buffer->buffer;

  tx_packet->header.cmd = SECONDARY_CMD_CHIP_LABEL_IS;
  tx_packet->secondary_header.seq = rx_packet->host_header.seq;

  const char *label = SL_CPC_GPIO_EXPANDER_CHIP_LABEL;
  size_t len = MIN(strlen(label), sizeof(tx_buffer->buffer) - sizeof(*tx_packet) - 1);
  memcpy(tx_packet->chip_label, label, len);
  tx_packet->chip_label[len] = '\0';
  len = len + 1;
  tx_packet->header.len = sizeof(*tx_packet) + len - sizeof(header_t);
  tx_buffer->buffer_len = sizeof(*tx_packet) + len;
}

/***************************************************************************//**
 * Parse packet and get a reply packet ready.
 ******************************************************************************/
static void parse_packet(void *rx_buffer, tx_buffer_t *tx_buffer)
{
  header_t *header = (header_t *) rx_buffer;
  uint8_t cmd = header->cmd;
  tx_buffer->buffer_len = 0;

  switch (cmd) {
    case HOST_CMD_GET_VERSION:
      on_get_version(rx_buffer, tx_buffer);
      break;
    case HOST_CMD_GET_UNIQUE_ID:
      on_get_unique_id(rx_buffer, tx_buffer);
      break;
    case HOST_CMD_GET_CHIP_LABEL:
      on_get_chip_label(rx_buffer, tx_buffer);
      break;
    case HOST_CMD_GET_GPIO_COUNT:
      on_get_gpio_count(rx_buffer, tx_buffer);
      break;
    case HOST_CMD_GET_GPIO_NAME:
      on_get_gpio_name(rx_buffer, tx_buffer);
      break;
    case HOST_CMD_GET_GPIO_VALUE:
      on_get_gpio_value(rx_buffer, tx_buffer);
      break;
    case HOST_CMD_SET_GPIO_VALUE:
      on_set_gpio_value(rx_buffer, tx_buffer);
      break;
    case HOST_CMD_SET_GPIO_CONFIG:
      on_set_gpio_config(rx_buffer, tx_buffer);
      break;
    case HOST_CMD_SET_GPIO_DIRECTION:
      on_set_gpio_direction(rx_buffer, tx_buffer);
      break;
    default:
      on_unsupported_cmd(cmd, tx_buffer);
      break;
  }

#if defined(SLI_CPC_GPIO_EXPANDER_UNDER_TEST)
  if (sli_cpc_gpio_expander_under_test_seq_offset && cmd != HOST_CMD_GET_VERSION) {
    secondary_header_t *secondary_header = (secondary_header_t *) (tx_buffer->buffer + (sizeof(header_t)));
    secondary_header->seq = secondary_header->seq + sli_cpc_gpio_expander_under_test_seq_offset;
    sli_cpc_gpio_expander_under_test_seq_offset = 0;
  }
#endif

  if (tx_buffer->buffer_len > 0) {
    EFM_ASSERT(tx_buffer->buffer_len <= sizeof(tx_buffer->buffer));
    signal_state_change(ENDPOINT_STATE_REPLY_READY);
  }
}

/***************************************************************************//**
 * Read an incoming packet.
 ******************************************************************************/
static void read_packet(tx_buffer_t *tx_buffer)
{
  uint16_t rx_buffer_length;
  void *rx_buffer;

  if (sl_cpc_read(&ep_gpio, &rx_buffer, &rx_buffer_length, 0, 0) == SL_STATUS_OK) {
    parse_packet(rx_buffer, tx_buffer);
    EFM_ASSERT(sl_cpc_free_rx_buffer(rx_buffer) == SL_STATUS_OK);
  }
}

/***************************************************************************//**
 * Transmit a packet.
 ******************************************************************************/
static void transmit_packet(tx_buffer_t *tx_buffer)
{
  sl_status_t status;

  status = sl_cpc_write(&ep_gpio, tx_buffer->buffer, tx_buffer->buffer_len, 0, NULL);
  if (status == SL_STATUS_OK) {
    signal_state_change(ENDPOINT_STATE_WRITE_PENDING);
  } else if (status == SL_STATUS_NO_MORE_RESOURCE) {
#if defined(SL_CATALOG_KERNEL_PRESENT)
    osDelay(((uint64_t)osKernelGetTickFreq() * CPC_GPIO_EXPANDER_OS_DELAY_MS) / 1000);
#endif // SL_CATALOG_KERNEL_PRESENT
    signal_state_change(ENDPOINT_STATE_REPLY_READY);
  }
}

/***************************************************************************//**
 * GPIO expander task
 ******************************************************************************/
#if defined(SL_CATALOG_KERNEL_PRESENT)
static void task(void *arg)
{
  (void)arg;

  if (init_endpoint() != SL_STATUS_OK) {
    EFM_ASSERT(false);
    osThreadExit();
  }

  while (true) {
    sl_cpc_gpio_expander_process_action();
  }
}
#endif

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * GPIO endpoint init
 ******************************************************************************/
sl_status_t sl_cpc_gpio_expander_init(void)
{
#if defined(SL_CATALOG_KERNEL_PRESENT)
  osThreadAttr_t task_attr = { 0 };
  osSemaphoreAttr_t semaphore_attr = { 0 };

  semaphore_attr.cb_mem = semaphore_cb;
  semaphore_attr.cb_size = osSemaphoreCbSize;
  state_change_signal = osSemaphoreNew(1, 1, &semaphore_attr);
  if (state_change_signal == 0) {
    EFM_ASSERT(false);
    return SL_STATUS_ALLOCATION_FAILED;
  }

  task_attr.name = "CPC GPIO Expander";
  task_attr.priority = SL_CPC_GPIO_EXPANDER_TASK_PRIORITY;
  task_attr.stack_mem = &thread_stack[0];
  task_attr.stack_size = THREAD_STACK_SIZE;
  task_attr.cb_mem = &thread_cb[0];
  task_attr.cb_size = osThreadCbSize;
  thread_id = osThreadNew(&task, NULL, &task_attr);
  EFM_ASSERT(thread_id != NULL);
#else
  init_endpoint();
#endif // SL_CATALOG_KERNEL_PRESENT

  return SL_STATUS_OK;
}

/***************************************************************************/ /**
 * GPIO endpoint process action
 ******************************************************************************/
void sl_cpc_gpio_expander_process_action(void)
{
  static tx_buffer_t tx_buffer;
  endpoint_state_t current_state;

  if (restart_flag) {
    restart_endpoint();
    return;
  }

  current_state = wait_state_change();

  switch (current_state) {
    case ENDPOINT_STATE_RESTART:
      break;
    case ENDPOINT_STATE_INIT:
    case ENDPOINT_STATE_WRITE_COMPLETED:
      read_packet(&tx_buffer);
      break;
    case ENDPOINT_STATE_REPLY_READY:
      transmit_packet(&tx_buffer);
      break;
    case ENDPOINT_STATE_WRITE_PENDING:
      break;
    default:
      EFM_ASSERT(false);
  }
}
