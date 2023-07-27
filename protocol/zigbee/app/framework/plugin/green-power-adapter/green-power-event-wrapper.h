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

#ifndef _SILABS_GREEN_POWER_EVENT_WRAPPER_H_
#define _SILABS_GREEN_POWER_EVENT_WRAPPER_H_
#include PLATFORM_HEADER

#ifdef SL_COMPONENT_CATALOG_PRESENT
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#include "green-power-adapter-config.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

/***************************************************************************
* Events stub functions
* Customer should define these in their own application code
* if they want to use custom events functionality
***************************************************************************/

#if (EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_EVENT_SYSTEM == 1)

// by default adapter plugin uses green-power-adapter-type.h, which is supplied by SDK. Customer has
// to duplicate that file with different name into their project and define their own data type
// required to use green power plugins
#include EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_CUSTOM_EVENT_SYSTEM_HEADER

typedef void (*pluginGPAdatperEventHandler_t)(sl_zigbee_event_wrapper_t *);

void sl_zigbee_event_init_wrapper(sl_zigbee_event_wrapper_t *event, pluginGPAdatperEventHandler_t handler);
void sl_zigbee_event_set_delay_ms_wrapper(sl_zigbee_event_wrapper_t *event, uint32_t delayMs);
void sl_zigbee_event_set_inactive_wrapper(sl_zigbee_event_wrapper_t *event);
bool sl_zigbee_event_is_active_wrapper(sl_zigbee_event_wrapper_t *event);
bool sl_zigbee_event_is_scheduled_wrapper(sl_zigbee_event_wrapper_t *event);

#ifdef sl_zigbee_event_t
#undef sl_zigbee_event_t
#endif
#define sl_zigbee_event_t sl_zigbee_event_wrapper_t

#ifdef sl_zigbee_event_init
#undef sl_zigbee_event_init
#endif
#define sl_zigbee_event_init(...) sl_zigbee_event_init_wrapper(__VA_ARGS__)

#ifdef sl_zigbee_event_set_delay_ms
#undef sl_zigbee_event_set_delay_ms
#endif
#define sl_zigbee_event_set_delay_ms(...) sl_zigbee_event_set_delay_ms_wrapper(__VA_ARGS__)

#ifdef sl_zigbee_event_set_inactive
#undef sl_zigbee_event_set_inactive
#endif
#define sl_zigbee_event_set_inactive(...) sl_zigbee_event_set_inactive_wrapper(__VA_ARGS__)

#ifdef sl_zigbee_event_is_active
#undef sl_zigbee_event_is_active
#endif
#define sl_zigbee_event_is_active(...) sl_zigbee_event_is_active_wrapper(__VA_ARGS__)

#ifdef sl_zigbee_event_is_scheduled
#undef sl_zigbee_event_is_scheduled
#endif
#define sl_zigbee_event_is_scheduled(...) sl_zigbee_event_is_scheduled_wrapper(__VA_ARGS__)

#endif // (EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_EVENT_SYSTEM == 1)

#endif //_SILABS_GREEN_POWER_EVENT_WRAPPER_H_
