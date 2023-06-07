/***************************************************************************//**
 * @file
 * @brief Token defines for the Green Power Server plugin.
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

#include "green-power-server-config.h"

#if (EMBER_AF_PLUGIN_GREEN_POWER_SERVER_USE_TOKENS == 1)

#define CREATOR_GPS_NETWORK_STATE      (0x872F)

// NVM3 indexed tokens need special consideration for key number assigment
// Ref :
//     Section 3.1.2  Special Considerations for Indexed Tokens
//  of an1135-using-third-generation-nonvolatile-memory.pdf

// Basic Tokens
#define NVM3KEY_GPS_NETWORK_STATE      (NVM3KEY_DOMAIN_ZIGBEE | 0x892B)

#ifdef DEFINETYPES
// Define token types
#endif //DEFINETYPES

#ifdef DEFINETOKENS
// Define the actual token storage information here
DEFINE_BASIC_TOKEN(GPS_NETWORK_STATE, uint8_t, 0x00)
#endif //DEFINETOKENS
#endif // EMBER_AF_PLUGIN_GREEN_POWER_SERVER_USE_TOKENS
