/***************************************************************************//**
 * @file
 * @brief CLI for the Smart Energy Registration plugin.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "app/framework/include/af.h"
#include "smart-energy-registration.h"
#include "app/util/serial/sl_zigbee_command_interpreter.h"

void setRegistrationDelayPeriod(sl_cli_command_arg_t *arguments)
{
#ifdef EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_DELAY_PERIOD
  sli_zigbee_af_smart_energy_registration_discovery_period =
    sl_cli_get_argument_uint32(arguments, 0) * MILLISECOND_TICKS_PER_SECOND;

  emberAfAppPrintln("Smart energy registration discovery period set to 0x%4x",
                    sli_zigbee_af_smart_energy_registration_discovery_period);
#else
  emberAfAppPrintln("Not supported.");
#endif //EMBER_AF_PLUGIN_SMART_ENERGY_REGISTRATION_DELAY_PERIOD
}
