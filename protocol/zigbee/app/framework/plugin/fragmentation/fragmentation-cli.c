/***************************************************************************//**
 * @file
 * @brief CLI commands related to the fragmentation code.
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
#ifdef SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
    #include "app/framework/include/af.h"
#else
    #include "sl_cli.h"
    #include "ember-types.h"
    #include "app/framework/common/zigbee_app_framework_common.h"
#endif //SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "app/util/serial/sl_zigbee_command_interpreter.h"

#include "fragmentation.h"
//------------------------------------------------------------------------------
// CLI stuff

#ifdef EZSP_HOST
void sli_zigbee_af_reset_and_init_ncp(void);
#endif //EZSP_HOST

//------------------------------------------------------------------------------
// Functions

void sli_zigbee_af_fragmentation_set_window_size_command(sl_cli_command_arg_t *args)
{
  emberFragmentWindowSize = sl_cli_get_argument_uint8(args, 0);
  sl_zigbee_core_debug_println("Fragmentation RX window size set to %d",
                               emberFragmentWindowSize);
#ifdef EZSP_HOST
  sli_zigbee_af_reset_and_init_ncp();
#endif //EZSP_HOST
}

void sli_zigbee_af_fragmentation_artificial_block_drop_command(sl_cli_command_arg_t *args)
{
#if defined(EMBER_TEST) || defined(EMBER_GOLDEN_UNIT)
  sli_zigbee_af_fragmentation_artificially_drop_block_number = sl_cli_get_argument_uint8(args, 0);
#endif
}
