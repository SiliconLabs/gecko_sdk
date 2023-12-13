/***************************************************************************//**
 * @file
 * @brief Setters and getters for host apps to access certain configuration
 * values from ember-configuration.c.  Host definitions for these APIs wrap
 * around EZSP configuration access calls.

 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include "ember-types.h"
#include "ezsp-enum.h"
#include "app/util/ezsp/ezsp-utils.h"
#include "app/framework/include/af-types.h"
#include "app/util/ezsp/command-prototypes.h"
#include "app/framework/util/af-main.h"

sl_status_t sl_zigbee_set_multicast_table_size(uint8_t size)
{
  EzspStatus status = emberAfSetEzspConfigValue(EZSP_CONFIG_APS_ACK_TIMEOUT,
                                                (size),
                                                "APS ACK timeout");
  if (status == EZSP_SUCCESS) {
    return SL_STATUS_OK;
  }
  return SL_STATUS_FAIL;
}

uint8_t sl_zigbee_get_multicast_table_size(void)
{
  uint8_t multicast_table_size;
  (void) ezspGetConfigurationValue(EZSP_CONFIG_MULTICAST_TABLE_SIZE,
                                   (uint16_t*)&multicast_table_size);
  return multicast_table_size;
}

EmberMulticastTableEntry* sl_zigbee_get_multicast_table(EmberMulticastTableEntry* table)
{
  uint8_t multicast_table_size = sl_zigbee_get_multicast_table_size();
  for (int i = 0; i < multicast_table_size; i++) {
    (void) ezspGetMulticastTableEntry(i, &(table[i]));
  }
  return table;
}

sl_status_t sl_zigbee_set_multicast_table(EmberMulticastTableEntry* entry)
{
  uint8_t multicast_table_size = sl_zigbee_get_multicast_table_size();
  for (int i = 0; i < multicast_table_size; i++) {
    EzspStatus status = ezspSetMulticastTableEntry(i, &(entry[i]));
    if (status != EZSP_SUCCESS) {
      return SL_STATUS_FAIL;
    }
  }
  return SL_STATUS_OK;
}

void sl_zigbee_set_aps_ack_timeout_ms(uint16_t timeout)
{
  (void) emberAfSetEzspConfigValue(EZSP_CONFIG_APS_ACK_TIMEOUT,
                                   (timeout),
                                   "APS ACK timeout");
}

uint16_t sl_zigbee_get_aps_ack_timeout_ms(void)
{
  uint16_t timeout_ms;
  (void) ezspGetConfigurationValue(EZSP_CONFIG_APS_ACK_TIMEOUT, &(timeout_ms));
  return timeout_ms;
}

sl_status_t sl_zigbee_set_binding_table_size(uint8_t size)
{
  EzspStatus status = emberAfSetEzspConfigValue(EZSP_CONFIG_BINDING_TABLE_SIZE,
                                                (size),
                                                "binding table size");
  if (status == EZSP_SUCCESS) {
    return SL_STATUS_OK;
  }
  return SL_STATUS_FAIL;
}

uint8_t sl_zigbee_get_binding_table_size(void)
{
  uint8_t binding_table_size;
  (void) ezspGetConfigurationValue(EZSP_CONFIG_BINDING_TABLE_SIZE, (uint16_t*)&(binding_table_size));
  return binding_table_size;
}

sl_status_t sl_zigbee_set_max_end_device_children(uint8_t max)
{
  EzspStatus status = emberAfSetEzspConfigValue(EZSP_CONFIG_MAX_END_DEVICE_CHILDREN,
                                                (max),
                                                "max end device children");
  if (status == EZSP_SUCCESS) {
    return SL_STATUS_OK;
  }
  return SL_STATUS_FAIL;
}

uint8_t sl_zigbee_get_max_end_device_children(void)
{
  uint8_t max_end_device_children;
  (void) ezspGetConfigurationValue(EZSP_CONFIG_MAX_END_DEVICE_CHILDREN,
                                   (uint16_t*)&(max_end_device_children));
  return max_end_device_children;
}

sl_status_t sl_zigbee_set_transient_device_table_timeout_ms(uint16_t timeout)
{
  EzspStatus status = EZSP_SUCCESS;
#ifdef SL_CATALOG_ZIGBEE_DELAYED_JOIN_PRESENT
  if (timeout < SL_ZIGBEE_TRANSIENT_DEVICE_MINIMUM_TIMEOUT_MS) {
    return SL_STATUS_FAIL;
  }
  status = emberAfSetEzspValue(EZSP_VALUE_TRANSIENT_DEVICE_TIMEOUT,
                               2,
                               (uint8_t*)&timeout,
                               "default timeout for transient device table");
#endif
  if (status == EZSP_SUCCESS) {
    return SL_STATUS_OK;
  }
  return SL_STATUS_FAIL;
}

uint16_t sl_zigbee_get_transient_device_table_timeout_ms(void)
{
  uint16_t transient_device_timeout = 0;
  uint8_t valueLength = 2;
  (void) ezspGetValue(EZSP_VALUE_TRANSIENT_DEVICE_TIMEOUT,
                      &valueLength,
                      (uint8_t*)&(transient_device_timeout));
  return transient_device_timeout;
}
