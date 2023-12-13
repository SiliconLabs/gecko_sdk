/***************************************************************************//**
 * @file
 * @brief
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
#ifndef __SL_WISUN_CONFIG_H__
#define __SL_WISUN_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "sl_wisun_types.h"

//! Wi-SUN network name
#define WISUN_CONFIG_NETWORK_NAME               "Wi-SUN Network"

//! Wi-SUN network size
#define WISUN_CONFIG_NETWORK_SIZE               SL_WISUN_NETWORK_SIZE_SMALL

//! Wi-SUN allowed channels
#define WISUN_CONFIG_ALLOWED_CHANNELS           "0-255"
extern const sl_wisun_channel_mask_t wisun_config_allowed_channels_mask;

//! Wi-SUN default PHY - FAN1.1 profile
#define WISUN_CONFIG_DEFAULT_PHY_FAN11

//! Wi-SUN default PHY - Regulatory domain
#define WISUN_CONFIG_REGULATORY_DOMAIN          1

//! Wi-SUN default PHY - Channel Plan ID
#define WISUN_CONFIG_CHANNEL_PLAN_ID            1

//! Wi-SUN default PHY - PHY Mode ID
#define WISUN_CONFIG_PHY_MODE_ID                2

//! Wi-SUN Broadcast retries
#define WISUN_CONFIG_BROADCAST_RETRIES          2

//! Wi-SUN Device private key
extern const uint8_t wisun_config_device_private_key[];

//! Wi-SUN Device certificate
extern const uint8_t wisun_config_device_certificate[];

//! Wi-SUN CA certificate
extern const uint8_t wisun_config_ca_certificate[];

#ifdef __cplusplus
}
#endif

#endif /* __SL_WISUN_CONFIG_H__ */
