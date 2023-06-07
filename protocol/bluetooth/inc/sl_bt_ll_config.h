/***************************************************************************//**
 * @brief Bluetooth Link Layer configuration
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_BT_BLUETOOTH_LL_PRIORITIES_DEFINED
#define SL_BT_BLUETOOTH_LL_PRIORITIES_DEFINED

typedef struct {
  uint8_t scan_min;
  uint8_t scan_max;
  uint8_t adv_min;
  uint8_t adv_max;
  uint8_t conn_min;
  uint8_t conn_max;
  uint8_t init_min;
  uint8_t init_max;
  uint8_t rail_mapping_offset;
  uint8_t rail_mapping_range;
  uint8_t _reserved;
  uint8_t adv_step;
  uint8_t scan_step;
  uint8_t pawr_tx_min;
  uint8_t pawr_tx_max;
  uint8_t pawr_rx_min;
  uint8_t pawr_rx_max;
} sl_bt_bluetooth_ll_priorities;

//Default priority configuration
#define SL_BT_BLUETOOTH_PRIORITIES_DEFAULT { 191, 143, 175, 127, 135, 0, 55, 15, 16, 16, 0, 4, 4, 15, 5, 20, 10 }

#define SL_BT_BLUETOOTH_PA_AUTOMODE 0xff

#include "sl_common.h"
SL_PACK_START(1)
typedef struct {
  int8_t golden_rssi_min_1m; //<! Golden range lowest RSSI for 1M PHY.
  int8_t golden_rssi_max_1m; //<! Golden range highest RSSI for 1M PHY.

  int8_t golden_rssi_min_2m; //<! Golden range lowest RSSI for 2M PHY.
  int8_t golden_rssi_max_2m; //<! Golden range highest RSSI for 2M PHY.

  int8_t golden_rssi_min_coded_s8; //<! Golden range lowest RSSI for Coded PHY w/ S=8.
  int8_t golden_rssi_max_coded_s8; //<! Golden range highest RSSI for Coded PHY w/ S=8.

  int8_t golden_rssi_min_coded_s2; //<! Golden range lowest RSSI for Coded PHY w/ S=2.
  int8_t golden_rssi_max_coded_s2; //<! Golden range highest RSSI for Coded PHY w/ S=2.

  uint8_t activate_power_control;
} SL_ATTRIBUTE_PACKED sl_bt_ll_power_control_config_t;
SL_PACK_END()

#define SL_BT_USE_MAX_POWER_LEVEL_SUPPORTED_BY_RADIO 0x7fff
#define SL_BT_USE_MIN_POWER_LEVEL_SUPPORTED_BY_RADIO 0x7fff

#endif
