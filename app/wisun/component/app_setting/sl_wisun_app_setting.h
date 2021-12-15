/***************************************************************************//**
 * @file
 * @brief Wi-SUN Application Core CLI
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

#ifndef __SL_WISUN_APP_SETTING_H__
#define __SL_WISUN_APP_SETTING_H__

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include "sl_status.h"
#include "sl_wisun_api.h"

/**************************************************************************//**
 * @defgroup SL_WISUN_APP_CORE_CLI Application Core CLI
 * @ingroup SL_WISUN_APP_CORE
 * @{
 *****************************************************************************/

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Wi-SUN default network name size
 *****************************************************************************/
#define MAX_SIZE_OF_NETWORK_NAME        (SL_WISUN_NETWORK_NAME_SIZE + 1)

/**************************************************************************//**
 * @brief Wisun setting structure
 *****************************************************************************/
typedef struct {
  char network_name[SL_WISUN_NETWORK_NAME_SIZE + 1];
  uint8_t network_size;
  int8_t tx_power;
}app_setting_wisun_t;

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Initialize Wi-SUN setting
 *****************************************************************************/
void app_wisun_setting_init(void);

/**************************************************************************//**
 * @brief Get the Wi-SUN settings.
 * @param[out] *wisun_setting is the obtained Wi-SUN setting
 * @return sl_status_t if the getting is successful it returns SL_STATUS_OK, otherwise
 * error code.
 *****************************************************************************/
sl_status_t app_wisun_setting_get(app_setting_wisun_t *const wisun_setting);

/**************************************************************************//**
 * @brief Set the Wi-SUN network name.
 * @param[out] *name is the network name that will be set.
 * @return sl_status_t if the set is successful it returns SL_STATUS_OK, otherwise
 * error code.
 *****************************************************************************/
sl_status_t app_wisun_setting_set_network_name(const char *const name);

/**************************************************************************//**
 * @brief Set the Wi-SUN network size.
 * @param[out] *name is the network size that will be set.
 * @return sl_status_t if the set is successful it returns SL_STATUS_OK, otherwise
 * error code.
 *****************************************************************************/
sl_status_t app_wisun_setting_set_network_size(const uint8_t *const size);

/**************************************************************************//**
 * @brief Set the Wi-SUN TX power.
 * @param[out] *name is the TX power that will be set.
 * @return sl_status_t if the set is successful it returns SL_STATUS_OK, otherwise
 * error code.
 *****************************************************************************/
sl_status_t app_wisun_setting_set_tx_power(const int8_t *const tx_power);

/**************************************************************************//**
 * @brief Get the Wi-SUN network name.
 * @param[out] *name pointer where the name is copied onto
 * @param[oin] length is the size of the name buffer
 * @return sl_status_t it is successful if it returns SL_STATUS_OK otherwise
 *         it is not.
 *****************************************************************************/
sl_status_t app_wisun_setting_get_network_name(char *const name, uint8_t size);

/**************************************************************************//**
 * @brief Get the Wi-SUN network size.
 * @param[out] *size pointer where the network size is copied onto
 * @return sl_status_t it is successful if it returns SL_STATUS_OK otherwise
 *         it is not.
 *****************************************************************************/
sl_status_t app_wisun_setting_get_network_size(uint8_t *const size);

/**************************************************************************//**
 * @brief Get the Wi-SUN TX power.
 * @param[out] *tx_power pointer where the TX power is copied onto
 * @return sl_status_t it is successful if it returns SL_STATUS_OK otherwise
 *         it is not.
 *****************************************************************************/
sl_status_t app_wisun_setting_get_tx_power(int8_t *const tx_power);

#ifdef __cplusplus
}
#endif
#endif
