/***************************************************************************//**
 * @file
 * @brief CLI for the Price Common plugin.
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
#include "price-common.h"

#include "sl_cli.h"
//=============================================================================
// Functions

void sli_zigbee_af_price_common_cluster_get_adjusted_start_time_cli(sl_cli_command_arg_t *arguments)
{
  uint32_t startTimeUTc = sl_cli_get_argument_uint32(arguments, 0);
  uint8_t durationType = sl_cli_get_argument_uint8(arguments, 1);
  uint32_t adjustedStartTime;
  adjustedStartTime = emberAfPluginPriceCommonClusterGetAdjustedStartTime(startTimeUTc,
                                                                          durationType);
  UNUSED_VAR(adjustedStartTime);
  emberAfPriceClusterPrintln("adjustedStartTime: 0x%4X", adjustedStartTime);
}

void sli_zigbee_af_price_common_cluster_convert_duration_to_seconds_cli(sl_cli_command_arg_t *arguments)
{
  uint32_t startTimeUtc = sl_cli_get_argument_uint32(arguments, 0);
  uint32_t duration = sl_cli_get_argument_uint32(arguments, 1);
  uint8_t durationType = sl_cli_get_argument_uint8(arguments, 2);
  emberAfPriceClusterPrintln("seconds: %d",
                             emberAfPluginPriceCommonClusterConvertDurationToSeconds(startTimeUtc,
                                                                                     duration,
                                                                                     durationType));
}
