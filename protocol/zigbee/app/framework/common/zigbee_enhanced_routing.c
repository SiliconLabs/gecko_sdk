/***************************************************************************//**
 * @brief Zigbee Enhanced Routing with LQI source code
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

#include <stdbool.h>

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif //SL_COMPONENT_CATALOG_PRESENT

bool zigbee_enhanced_routing_is_active(void)
{
  #ifdef SL_COMPONENT_CATALOG_ZIGBEE_R23_SUPPORT_PRESENT
  return true;
  #else // USE R22 LQI caclulation
  return false;
  #endif //SL_COMPONENT_CATALOG_ZIGBEE_R23_SUPPORT_PRESENT
}
