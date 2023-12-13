/***************************************************************************/ /**
 * @file
 * @brief CPC GPIO Endpoint of the Secondary
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

#ifndef SL_CPC_GPIO_EXPANDER_H
#define SL_CPC_GPIO_EXPANDER_H

#include <stdint.h>
#include "sl_status.h"
#include "em_gpio.h"

/*******************************************************************************
 **************************   STRUCTS   ****************************************
 ******************************************************************************/
/// @brief Struct representing a cpc gpio expander handle.
typedef struct {
  const GPIO_Port_TypeDef port;                    ///< port
  const uint32_t pin;                              ///< pin
  const char *name;                                ///< name
  uint32_t config;                                 ///< config
} sl_cpc_gpio_expander_handle_t;

#ifdef __cplusplus
extern "C"
{
#endif

/***************************************************************************//**
 * GPIO endpoint init
 ******************************************************************************/
sl_status_t sl_cpc_gpio_expander_init(void);

/***************************************************************************/ /**
 * GPIO endpoint process action
 ******************************************************************************/
void sl_cpc_gpio_expander_process_action(void);

#ifdef __cplusplus
}
#endif

/** @} (end addtogroup cpc_gpio_secondary) */

#endif /* SL_CPC_GPIO_EXPANDER_H */
