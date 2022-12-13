/***************************************************************************//**
 * @file
 * @brief MQTT mock implementation.
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

#include "app_log.h"
#include "mqtt.h"

/**************************************************************************//**
 * Initialize MQTT client.
 *****************************************************************************/
sl_status_t mqtt_init(mqtt_handle_t *handle)
{
  (void)handle;
  app_log_warning("######## MQTT mock. Only for testing! ########" APP_LOG_NL);
  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Publish an MQTT message on a topic.
 *****************************************************************************/
sl_status_t mqtt_publish(mqtt_handle_t *handle,
                         const char *topic,
                         const char *payload,
                         bool retain)
{
  (void)handle;
  (void)retain;
  app_log("%s: %s" APP_LOG_NL, topic, payload);
  return SL_STATUS_OK;
}

/**************************************************************************//**
 * MQTT step processes.
 *****************************************************************************/
sl_status_t mqtt_step(mqtt_handle_t *handle)
{
  (void)handle;
  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Subscribe to an MQTT topic.
 *****************************************************************************/
sl_status_t mqtt_subscribe(mqtt_handle_t *handle, const char *topic)
{
  (void)handle;
  (void)topic;
  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Unsubscribe from an MQTT topic.
 *****************************************************************************/
sl_status_t mqtt_unsubscribe(mqtt_handle_t *handle, const char *topic)
{
  (void)handle;
  (void)topic;
  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Unsubscribe from all MQTT topic.
 *****************************************************************************/
sl_status_t mqtt_unsubscribe_all(mqtt_handle_t *handle)
{
  (void)handle;
  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Deinitialize MQTT client.
 *****************************************************************************/
sl_status_t mqtt_deinit(mqtt_handle_t *handle)
{
  (void)handle;
  return SL_STATUS_OK;
}
