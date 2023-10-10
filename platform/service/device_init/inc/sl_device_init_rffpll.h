/***************************************************************************//**
 * @file
 * @brief Device initialization for RFFPLL.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef SL_DEVICE_INIT_RFFPLL_H
#define SL_DEVICE_INIT_RFFPLL_H

#include "sl_status.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup device_init
 * @{
 * @addtogroup device_init_rffpll RFFPLL Initialization
 * @brief Initialize the Digital RFFPLL (Radio Frequency Friendly Phase Locked Loop)
 * @details
 * Configures and locks the Digital PLL using the configuration in the
 * configuration header `sl_device_init_rffpll_config.h`, where settings including
 * host target frequency and dividers are available.
 *
 * If using Simplicity Studio, this configuration header is also configurable
 * through the Project Configurator, by selecting the "Device Init: RFFPLL" configuration component.
 *
 * @{
 */

/**
 * Initialize RFFPLL
 *
 * @details
 * Configures and locks the Digital RFFPLL using the configuration in the
 * configuration header `sl_device_init_rffpll_config.h`, where settings including
 * host target frequency and dividers are available.
 *
 * @return Status code
 * @retval SL_STATUS_OK RFFPLL successfully initialized and locked
 */
sl_status_t sl_device_init_rffpll(void);

/**
 * @} device_init_rffpll
 * @} device_init
 */

#ifdef __cplusplus
}
#endif

#endif // SL_DEVICE_INIT_RFFPLL_H
