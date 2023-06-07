/***************************************************************************//**
 * @file
 * @brief Configuration types for "accept_list"
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

#ifndef SLI_BT_ACCEPT_LIST_CONFIG_H
#define SLI_BT_ACCEPT_LIST_CONFIG_H

#include "sli_bt_config_defs.h"

/**
 * @brief Configuration structure used by "accept_list"
 *
 * See "sl_bt_accept_list_config.h" for detailed description of each
 * configuration parameter.
 */
typedef struct {
  uint8_t accept_list_size; ///< Set to value of SL_BT_CONFIG_ACCEPT_LIST_SIZE
} sli_bt_accept_list_config_t;

#endif // SLI_BT_ACCEPT_LIST_CONFIG_H
