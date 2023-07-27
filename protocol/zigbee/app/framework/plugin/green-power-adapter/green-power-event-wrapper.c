/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "green-power-event-wrapper.h"

#if (EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_EVENT_SYSTEM == 1)
WEAK(void sl_zigbee_event_init_wrapper(sl_zigbee_event_wrapper_t *event, pluginGPAdatperEventHandler_t handler))
{
}

WEAK(void sl_zigbee_event_set_delay_ms_wrapper(sl_zigbee_event_wrapper_t *event, uint32_t delayMs))
{
}

WEAK(void sl_zigbee_event_set_inactive_wrapper(sl_zigbee_event_wrapper_t *event))
{
}

WEAK(bool sl_zigbee_event_is_active_wrapper(sl_zigbee_event_wrapper_t *event))
{
  return false;
}
WEAK(bool sl_zigbee_event_is_scheduled_wrapper(sl_zigbee_event_wrapper_t *event))
{
  return false;
}

#endif // (EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_EVENT_SYSTEM == 1)
