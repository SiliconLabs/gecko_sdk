/***************************************************************************//**
 * @brief Adaptation for running Bluetooth in RTOS
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

#ifndef SL_BTCTRL_RTOS_ADAPTATION_H
#define SL_BTCTRL_RTOS_ADAPTATION_H

/***************************************************************************//**
 * @addtogroup bluetooth_controller_rtos_adaptation
 * @{
 *
 * @brief Bluetooth RTOS adaptation
 *
 * The Bluetooth Controller RTOS adaptation component implements the relevant interfaces
 * for running the Bluetooth Link Layer in an RTOS. When initialized in @ref
 * sl_btctrl_rtos_init(), the component creates the required RTOS tasks for the
 * Bluetooth controller itself
 *
 */

/**
 * @brief Initialize Bluetooth Controller for running in RTOS.
 * @return SL_STATUS_OK if succeeds, otherwise error
 */
sl_status_t sl_btctrl_rtos_init();

/**
 * @brief  Get the available stack space of the link layer thread as determined
 * by the stack watermark recorded during execution.
 * @return SL_STATUS_OK if succeeds, otherwise error
 */
uint8_t sl_btctrl_rtos_get_stack_space(uint32_t *stack_space);

/** @} end bluetooth_controller_rtos_adaptation */

#endif //SL_BTCTRL_RTOS_ADAPTATION_H
