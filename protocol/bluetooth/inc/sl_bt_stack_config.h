/***************************************************************************//**
 * @brief Bluetooth stack configuration
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

#ifndef SL_BT_STACK_CONFIG_H
#define SL_BT_STACK_CONFIG_H

#include <stdint.h>
#include "sl_bt_ll_config.h"

typedef struct {
  uint8_t max_connections;    //!< Maximum number of connections to support, if 0 defaults to 4
  uint8_t max_advertisers;    //!< Maximum number of advertisers to support, if 0 defaults to 1
  uint8_t max_periodic_sync;  //!< Maximum number of periodic synchronizations to support, if 0 defaults to 0
  uint8_t max_l2cap_coc;      //!< Maximum number of L2cap Connection-oriented channels to support, if 0 defaults to 0
  uint32_t max_buffer_memory; //!< Maximum number of bytes to use for data buffers
  uint32_t linklayer_config;
  sl_bt_bluetooth_ll_priorities * linklayer_priorities; //Priority configuration, if NULL uses default values
}sl_bt_stack_config_t;

/** Value indicating the PA configuration is disabled  */
#define SL_BT_RADIO_PA_CONFIG_DISABLED 0

/** Value indicating the PA configuration is enabled  */
#define SL_BT_RADIO_PA_CONFIG_ENABLED  1

/** PA configuration - PAVDD input from battery supply. Voltage: ~ 3300 mV */
#define SL_BT_RADIO_PA_INPUT_VBAT      0

/** PA configuration - PAVDD input from DCDC supply. Voltage: ~ 1800 mV */
#define SL_BT_RADIO_PA_INPUT_DCDC      1

typedef struct {
  uint8_t config_enable; // Non-zero value indicates this is a valid PA config

  uint8_t input;         // PAVDD input, either SL_BT_RADIO_PA_INPUT_VBAT or SL_BT_RADIO_PA_INPUT_DCDC
                         // default: SL_BT_RADIO_PA_INPUT_DCDC

  uint8_t pa_mode;       // Selected PA power mode.
                         // See power mode definitions in RAIL rail_chip_specific.h. If the given mode is not
                         // supported by the device the stack will try with a lower mode. If power mode eventually
                         // failed to configure, an error will be returned from sl_bt_stack_init or sl_bt_init.
                         // Default value: RAIL_TX_POWER_MODE_2P4_HP
}sl_bt_radio_pa_config_t;

/** Flag indicating Bluetooth runs in RTOS */
#define SL_BT_CONFIG_FLAG_RTOS                         256

/** Flag indicating Bluetooth can allow EM2 with inaccurate LF clock */
#define SL_BT_CONFIG_FLAG_INACCURATE_LFCLK_EM2           512

typedef void (*sl_bt_priority_schedule_callback)(void);
typedef void (*sl_bt_stack_schedule_callback)(void);

#define SL_BT_RF_CONFIG_ANTENNA                        (1 << 0)
typedef struct {
  int16_t tx_gain; // RF TX gain. Unit: 0.1 dBm. For example, -20 means -2.0 dBm (signal loss).
  int16_t rx_gain; // RF RX gain. Unit: 0.1 dBm.
  uint8_t flags; // bit 0 is enabling antenna config, other bits 1-7 are reserved.
  uint8_t antenna; // A configuration for antenna selection.
                   // Value should be come from RAIL_AntennaSel_t enum.
                   // See antenna path selection in RAIL rail_chip_specific.h.
  int16_t tx_min_power; // Minimum TX power level. Unit: 0.1 dBm.
  int16_t tx_max_power; // Maximum TX power level. Unit: 0.1 dBm.
} sl_bt_rf_config_t;

typedef struct {
  uint32_t config_flags;
  sl_bt_stack_config_t bluetooth;

  // GATT database (pointer of "sli_bt_gattdb_t*" type)
  const void* gattdb;

  //Callback for priority scheduling, used for RTOS support. If NULL uses pendsv irq.
  //This is called from Interrupt context
  sl_bt_priority_schedule_callback scheduler_callback;

  //Callback for requesting Bluetooth stack scheduling, used for RTOS support
  //This is called from Interrupt context
  sl_bt_stack_schedule_callback stack_schedule_callback;

  sl_bt_radio_pa_config_t pa;

  uint8_t max_timers;  // Max number of soft timers, up to 16, the application will use through SL_BT_API. Default: 4
  sl_bt_rf_config_t rf;
}sl_bt_configuration_t;

#endif
