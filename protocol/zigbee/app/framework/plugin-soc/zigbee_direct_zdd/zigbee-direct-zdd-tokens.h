/***************************************************************************//**
 * @file zigbee-direct-zdd-tokens.h
 * @brief Tokens for the Zigbee Direct ZDD plugin.
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
#include "zigbee_direct_zdd_config.h"
/* custom application tokens */
#define CREATOR_PLUGIN_ZDD_AUTH_STATUS  (0x3001)
#define CREATOR_PLUGIN_ZDD_JOIN_TIMEOUT  (0x3002)

#define NVM3KEY_PLUGIN_ZDD_AUTH_STATUS (NVM3KEY_DOMAIN_ZIGBEE | 0x3001)
#define NVM3KEY_PLUGIN_ZDD_JOIN_TIMEOUT (NVM3KEY_DOMAIN_ZIGBEE | 0x3002)

#ifdef DEFINETYPES
// Include or define any typedef for tokens here
#endif //DEFINETYPES

#ifdef DEFINETOKENS
// Define the actual token storage information here
DEFINE_BASIC_TOKEN(PLUGIN_ZDD_AUTH_STATUS, uint8_t, 0x00)
DEFINE_BASIC_TOKEN(PLUGIN_ZDD_JOIN_TIMEOUT, uint32_t, SL_ZIGBEE_DIRECT_ZDD_DEFAULT_JOIN_TIMEOUT_SEC)
#endif //DEFINETOKENS
