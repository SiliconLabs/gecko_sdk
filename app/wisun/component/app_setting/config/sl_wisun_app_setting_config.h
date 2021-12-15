/***************************************************************************//**
 * @file
 * @brief Wi-SUN Application Core Component Configuration Header.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_WISUN_APP_SETTING_CONFIG_H
#define SL_WISUN_APP_SETTING_CONFIG_H

#include "sl_wisun_types.h"

/**************************************************************************//**
 * @defgroup SL_WISUN_APP_CORE_CONFIG Core configuration
 * @ingroup SL_WISUN_APP_CORE
 * @{
 *****************************************************************************/

// <<< Use Configuration Wizard in Context Menu >>>

// <h>Wi-SUN network configuration
// <s.32 WISUN_NETWORK_NAME> Network Name.
// <i> Default: "Wi-SUN Network"
// <i> Definition of Wi-SUN network name (max 32 characters).
#define WISUN_NETWORK_NAME                    "Wi-SUN Network"

// <o WISUN_NETWORK_SIZE> Network Size
// <SL_WISUN_NETWORK_SIZE_AUTOMATIC=> Automatic (from PAN Adv.)
// <SL_WISUN_NETWORK_SIZE_SMALL=> Small (less than 100 nodes)
// <SL_WISUN_NETWORK_SIZE_MEDIUM=> Medium (100 to 800 nodes)
// <SL_WISUN_NETWORK_SIZE_LARGE=> Large (800 to 1500 nodes)
// <SL_WISUN_NETWORK_SIZE_TEST=> Test (a few nodes)
// <i> Default: SL_WISUN_NETWORK_SIZE_TEST
#define WISUN_NETWORK_SIZE                    SL_WISUN_NETWORK_SIZE_TEST
// </h>

// <h>Wi-SUN power configuration
// <o WISUN_TX_POWER> TX Power
// <i> Default: 20
#define WISUN_TX_POWER                        20U
// </h>

// <<< end of configuration section >>>

/** @}*/

#endif // SL_WISUN_APP_SETTING_CONFIG_H
