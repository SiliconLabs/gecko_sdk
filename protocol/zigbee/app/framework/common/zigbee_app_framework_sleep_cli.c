/***************************************************************************//**
 * @brief Zigbee Application Framework sleep code.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#include PLATFORM_HEADER

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && !defined(SL_CATALOG_ZIGBEE_PRO_COMPLIANCE_PRESENT)

#include PLATFORM_HEADER
#include "sl_cli.h"
#include "zigbee_app_framework_common.h"
#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#include "sl_zigbee_debug_print.h"
#endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT

extern bool sli_zigbee_af_stay_awake_when_not_joined;
extern bool sli_zigbee_af_force_end_device_to_stay_awake;
extern void emberAfForceEndDeviceToStayAwake(bool stayAwake);

void emberAfPluginIdleSleepStatusCommand(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  sl_zigbee_core_debug_println("Stay awake when not joined: %s",
                               (sli_zigbee_af_stay_awake_when_not_joined ? "yes" : "no"));
  sl_zigbee_core_debug_println("Forced stay awake:          %s",
                               (sli_zigbee_af_force_end_device_to_stay_awake ? "yes" : "no"));
}

void emberAfPluginIdleSleepStayAwakeCommand(sl_cli_command_arg_t *arguments)
{
  bool stayAwake = (bool)sl_cli_get_argument_uint8(arguments, 0);
  if (stayAwake) {
    sl_zigbee_core_debug_println("Forcing device to stay awake");
  } else {
    sl_zigbee_core_debug_println("Allowing device to go to sleep");
  }
  emberAfForceEndDeviceToStayAwake(stayAwake);
}

void emberAfPluginIdleSleepAwakeWhenNotJoinedCommand(sl_cli_command_arg_t *arguments)
{
  sli_zigbee_af_stay_awake_when_not_joined = (bool)sl_cli_get_argument_uint8(arguments, 0);
}

#endif //#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && !defined(SL_CATALOG_ZIGBEE_PRO_COMPLIANCE_PRESENT)
