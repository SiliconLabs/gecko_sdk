/***************************************************************************//**
 * @file
 * @brief MQTT mock API.
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

#ifndef MQTT_H
#define MQTT_H

#include <stddef.h>
#include <stdbool.h>
#include "sl_status.h"

// Forward declarations
typedef struct mqtt_handle_s mqtt_handle_t;

// On successful connection callback function prototype (handle)
typedef void (*mqtt_on_connect_t)(mqtt_handle_t *);

// On message callback function prototype (handle, topic, payload)
typedef void (*mqtt_on_message_t)(mqtt_handle_t *, const char *, const char *);

// MQTT client instance
struct mqtt_handle_s {
  char *host;
  int port;
  char *client_id;
  mqtt_on_connect_t on_connect;
  mqtt_on_message_t on_message;
};

#define MQTT_DEFAULT_HANDLE \
  {                         \
    .host = "localhost",    \
    .port = 1883,           \
    .client_id = NULL,      \
    .on_connect = NULL,     \
    .on_message = NULL      \
  }

#ifdef __cplusplus
extern "C" {
#endif

// Public functions
/**************************************************************************//**
 * Initialize MQTT client.
 *
 * @param handle MQTT client instance
 * @retval SL_STATUS_OK No error
 *****************************************************************************/
sl_status_t mqtt_init(mqtt_handle_t *handle);

/**************************************************************************//**
 * Publish an MQTT message on a topic.
 *
 * @param handle MQTT client instance
 * @param topic MQTT topic
 * @param payload Message to send
 * @param retain Set to true to make the message retained
 * @retval SL_STATUS_OK No error
 *
 * @note The message is a null-terminated string.
 *****************************************************************************/
sl_status_t mqtt_publish(mqtt_handle_t *handle,
                         const char *topic,
                         const char *payload,
                         bool retain);

/**************************************************************************//**
 * Subscribe to an MQTT topic.
 *
 * @param handle MQTT client instance
 * @param topic MQTT topic
 * @retval SL_STATUS_OK No error
 *****************************************************************************/
sl_status_t mqtt_subscribe(mqtt_handle_t *handle, const char *topic);

/**************************************************************************//**
 * Unsubscribe from a MQTT topic.
 *
 * @param handle MQTT client instance
 * @param topic MQTT topic
 * @retval SL_STATUS_OK No error
 *****************************************************************************/
sl_status_t mqtt_unsubscribe(mqtt_handle_t *handle, const char *topic);

/**************************************************************************//**
 * Unsubscribe from all MQTT topics.
 *
 * @param handle MQTT client instance
 * @retval SL_STATUS_OK No error
 *****************************************************************************/
sl_status_t mqtt_unsubscribe_all(mqtt_handle_t *handle);

/**************************************************************************//**
 * MQTT step processes.
 *
 * @param handle MQTT client instance
 * @retval SL_STATUS_OK No error
 *****************************************************************************/
sl_status_t mqtt_step(mqtt_handle_t *handle);

/**************************************************************************//**
 * Deinitialize MQTT client.
 *
 * @param handle MQTT client instance
 * @retval SL_STATUS_OK No error
 *****************************************************************************/
sl_status_t mqtt_deinit(mqtt_handle_t *handle);

#ifdef __cplusplus
};
#endif

#endif // MQTT_H
