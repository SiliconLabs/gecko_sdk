/***************************************************************************//**
 * @file sli_bt_accept_list_config.c
 * @brief Configuration instance for "accept_list"
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

#include "sl_component_catalog.h"
#include "sli_bt_accept_list_config.h"

#if defined(SL_CATALOG_BLUETOOTH_FEATURE_ACCEPT_LIST_PRESENT)
#include "sl_bt_accept_list_config.h"

SLI_BT_DEFINE_FEATURE_CONFIG(bt, accept_list, sli_bt_accept_list_config_t) = {
  .accept_list_size = SL_BT_CONFIG_ACCEPT_LIST_SIZE
};

#endif // SL_CATALOG_BLUETOOTH_FEATURE_ACCEPT_LIST_PRESENT
