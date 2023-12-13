/***************************************************************************//**
 * @file
 * @brief Setters and getters to replace direct access to certain
 * data from ember-configuration.c.

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

#include "stack/include/ember.h"
#include "stack/include/error.h"
#include "stack/include/message.h"
#ifdef SL_CATALOG_ZIGBEE_DELAYED_JOIN_PRESENT
#include "stack/include/trust-center.h"
#endif

extern EmberMulticastTableEntry emberMulticastTable[];
extern uint8_t emberMulticastTableSize;
extern uint16_t emberApsAckTimeoutMs;
extern uint8_t emberBindingTableSize;
extern uint8_t sli_zigbee_max_end_device_children;
extern uint16_t sli_zigbee_transient_device_timeout;
extern uint8_t sli_zigbee_stack_compliance_revision;

EmberMulticastTableEntry* sl_zigbee_get_multicast_table(void)
{
  return emberMulticastTable;
}

sl_status_t sl_zigbee_set_multicast_table(EmberMulticastTableEntry* entry)
{
  MEMMOVE(emberMulticastTable,
          entry,
          sizeof(EmberMulticastTableEntry) * emberMulticastTableSize);
  return SL_STATUS_OK;
}

sl_status_t sl_zigbee_set_multicast_table_size(uint8_t size)
{
  emberMulticastTableSize = size;
  return SL_STATUS_OK;
}

uint8_t sl_zigbee_get_multicast_table_size(void)
{
  return emberMulticastTableSize;
}

void sl_zigbee_set_aps_ack_timeout_ms(uint16_t timeout)
{
  emberApsAckTimeoutMs = timeout;
}

uint16_t sl_zigbee_get_aps_ack_timeout_ms(void)
{
  return emberApsAckTimeoutMs;
}

sl_status_t sl_zigbee_set_binding_table_size(uint8_t size)
{
  emberBindingTableSize = size;
  return SL_STATUS_OK;
}

uint8_t sl_zigbee_get_binding_table_size(void)
{
  return emberBindingTableSize;
}

sl_status_t sl_zigbee_set_max_end_device_children(uint8_t max)
{
  sli_zigbee_max_end_device_children = max;
  return SL_STATUS_OK;
}

uint8_t sl_zigbee_get_max_end_device_children(void)
{
  return sli_zigbee_max_end_device_children;
}

sl_status_t sl_zigbee_set_transient_device_table_timeout_ms(uint16_t timeout)
{
  sl_status_t status = SL_STATUS_OK;
#ifdef SL_CATALOG_ZIGBEE_DELAYED_JOIN_PRESENT
  if (timeout >= SL_ZIGBEE_TRANSIENT_DEVICE_MINIMUM_TIMEOUT_MS) {
    sli_zigbee_transient_device_timeout = timeout;
  } else {
    status  = SL_STATUS_FAIL;
  }
#endif
  return status;
}

uint16_t sl_zigbee_get_transient_device_table_timeout_ms(void)
{
  return sli_zigbee_transient_device_timeout;
}

uint8_t sl_zigbee_get_stack_compliance_revision(void)
{
  return sli_zigbee_stack_compliance_revision;
}

void sli_zigbee_set_stack_compliance_revision(uint8_t revision)
{
  sli_zigbee_stack_compliance_revision = revision;
}
