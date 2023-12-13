/***************************************************************************//**
 * @file sl_wisun_util.c
 * @brief Wi-SUN utilities
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#include <stddef.h>
#include <stdint.h>
#include "rail_config.h"
#include "sl_wisun_api.h"
#include "sl_wisun_util.h"
#include "sli_wisun_internal_api.h"

#define VERSION_WISUN_FAN1_0  0
#define VERSION_WISUN_FAN1_1  1

#define SLI_WISUN_ERROR_CHECK_SET_STATUS(__result, __value)\
do {\
  if (!(__result)){\
    status = __value;\
    goto error_handler;\
  }\
} while(0)

#define SLI_WISUN_ERROR_SET_STATUS(__value)\
do {\
  status = __value;\
  goto error_handler;\
} while(0)

#define PHY_TYPE_FSK      0
#define PHY_TYPE_FSK_FEC  1
#define PHY_TYPE_OFDM1    2
#define PHY_TYPE_OFDM2    3
#define PHY_TYPE_OFDM3    4
#define PHY_TYPE_OFDM4    5

#define GET_PHY_TYPE(_phy_mode_id)  (((_phy_mode_id) >> 4) & 0xf)
#define GET_PHY_MODE(_phy_mode_id)  ((_phy_mode_id) & 0xf)
#define IS_FSK(_phy_mode_id)  ((GET_PHY_TYPE(_phy_mode_id) == PHY_TYPE_FSK) || (GET_PHY_TYPE(_phy_mode_id) == PHY_TYPE_FSK_FEC))
#define IS_OFDM(_phy_mode_id)  ((GET_PHY_TYPE(_phy_mode_id) >= PHY_TYPE_OFDM1) && (GET_PHY_TYPE(_phy_mode_id) <= PHY_TYPE_OFDM4))

const uint8_t fsk_phy_mode_to_op_mode[9] = {
  0xFF, 0x1a, 0x1b, 0x2a, 0x2b, 0x3, 0x4a, 0x4b, 0x5
};

sl_status_t sl_wisun_util_get_rf_settings(uint8_t *reg_domain, uint8_t *op_class, uint16_t *op_mode)
{
  sl_status_t status;
  sl_wisun_phy_config_t phy_config;

  status = sl_wisun_util_get_phy_config(&phy_config);
  SLI_WISUN_ERROR_CHECK_SET_STATUS(status == SL_STATUS_OK, status);

  // Check this is a FAN1.0 configuration.
  SLI_WISUN_ERROR_CHECK_SET_STATUS(phy_config.type == SL_WISUN_PHY_CONFIG_FAN10, SL_STATUS_INVALID_CONFIGURATION);

  // FEC is not handled.
  SLI_WISUN_ERROR_CHECK_SET_STATUS(!phy_config.config.fan10.fec, SL_STATUS_INVALID_CONFIGURATION);

  *reg_domain = phy_config.config.fan10.reg_domain;
  *op_class = phy_config.config.fan10.op_class;
  *op_mode = phy_config.config.fan10.op_mode;

error_handler:

  return status;
}

sl_status_t sl_wisun_util_get_phy_config(sl_wisun_phy_config_t *phy_config)
{
  sl_status_t status;
  RAIL_Handle_t rail_handle;
  const RAIL_ChannelConfig_t *channel_config;
  const uint8_t *stack_info;
  RAIL_Status_t ret;
  uint8_t phy_type;
  uint8_t phy_mode;

  status = sli_wisun_get_rail_handle(&rail_handle);
  SLI_WISUN_ERROR_CHECK_SET_STATUS(status == SL_STATUS_OK, SL_STATUS_FAIL);

  // Take first RAIL configuration as reference.
  channel_config = channelConfigs[0];
  ret = RAIL_ConfigChannels(rail_handle, channel_config, NULL);
  SLI_WISUN_ERROR_CHECK_SET_STATUS(ret == RAIL_STATUS_NO_ERROR, SL_STATUS_FAIL);

  stack_info = channel_config->configs[0].stackInfo;

  // Check this is a Wi-SUN configuration.
  SLI_WISUN_ERROR_CHECK_SET_STATUS(stack_info[0] == RAIL_PTI_PROTOCOL_WISUN, SL_STATUS_INVALID_CONFIGURATION);

  phy_type = GET_PHY_TYPE(stack_info[1]);
  phy_mode = GET_PHY_MODE(stack_info[1]);

  switch (stack_info[2]) {
    case VERSION_WISUN_FAN1_0:
      SLI_WISUN_ERROR_CHECK_SET_STATUS(IS_FSK(stack_info[1]), SL_STATUS_FAIL);
      SLI_WISUN_ERROR_CHECK_SET_STATUS(phy_mode >= 1 && phy_mode <= 8, SL_STATUS_FAIL);
      phy_config->type = SL_WISUN_PHY_CONFIG_FAN10;
      phy_config->config.fan10.reg_domain = stack_info[4];
      phy_config->config.fan10.op_class = stack_info[3];
      phy_config->config.fan10.op_mode = fsk_phy_mode_to_op_mode[phy_mode];
      phy_config->config.fan10.fec = phy_type == PHY_TYPE_FSK_FEC;
      break;
    case VERSION_WISUN_FAN1_1:
      SLI_WISUN_ERROR_CHECK_SET_STATUS(IS_FSK(stack_info[1]) || IS_OFDM(stack_info[1]), SL_STATUS_FAIL);
      phy_config->type = SL_WISUN_PHY_CONFIG_FAN11;
      phy_config->config.fan11.reg_domain = stack_info[4];
      phy_config->config.fan11.chan_plan_id = stack_info[3];
      phy_config->config.fan11.phy_mode_id = stack_info[1];
      break;
    default:
      // Unsupported version.
      SLI_WISUN_ERROR_SET_STATUS(SL_STATUS_FAIL);
  }

error_handler:

  return status;
}

sl_status_t sl_wisun_util_connect(const uint8_t * network_name)
{
  sl_status_t status;
  sl_wisun_phy_config_t phy_config;

  status = sl_wisun_util_get_phy_config(&phy_config);
  SLI_WISUN_ERROR_CHECK_SET_STATUS(status == SL_STATUS_OK, SL_STATUS_FAIL);

  status = sl_wisun_join(network_name, &phy_config);

error_handler:

  return status;
}
