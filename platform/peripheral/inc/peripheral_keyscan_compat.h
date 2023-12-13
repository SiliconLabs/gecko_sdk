/***************************************************************************//**
 * @file
 * @brief KEYSCAN Compatibility Layer.
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

#ifndef PERIPHERAL_KEYSCAN_COMPAT_H
#define PERIPHERAL_KEYSCAN_COMPAT_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *********************************   DEFINES   *********************************
 ******************************************************************************/

// Enum.
#define SL_KEYSCAN_DELAY_2MS                          SL_HAL_KEYSCAN_DELAY_2MS
#define SL_KEYSCAN_DELAY_4MS                          SL_HAL_KEYSCAN_DELAY_4MS
#define SL_KEYSCAN_DELAY_6MS                          SL_HAL_KEYSCAN_DELAY_6MS
#define SL_KEYSCAN_DELAY_8MS                          SL_HAL_KEYSCAN_DELAY_8MS
#define SL_KEYSCAN_DELAY_10MS                         SL_HAL_KEYSCAN_DELAY_10MS
#define SL_KEYSCAN_DELAY_12MS                         SL_HAL_KEYSCAN_DELAY_12MS
#define SL_KEYSCAN_DELAY_14MS                         SL_HAL_KEYSCAN_DELAY_14MS
#define SL_KEYSCAN_DELAY_16MS                         SL_HAL_KEYSCAN_DELAY_16MS
#define SL_KEYSCAN_DELAY_18MS                         SL_HAL_KEYSCAN_DELAY_18MS
#define SL_KEYSCAN_DELAY_20MS                         SL_HAL_KEYSCAN_DELAY_20MS
#define SL_KEYSCAN_DELAY_22MS                         SL_HAL_KEYSCAN_DELAY_22MS
#define SL_KEYSCAN_DELAY_24MS                         SL_HAL_KEYSCAN_DELAY_24MS
#define SL_KEYSCAN_DELAY_26MS                         SL_HAL_KEYSCAN_DELAY_26MS
#define SL_KEYSCAN_DELAY_28MS                         SL_HAL_KEYSCAN_DELAY_28MS
#define SL_KEYSCAN_DELAY_30MS                         SL_HAL_KEYSCAN_DELAY_30MS
#define SL_KEYSCAN_DELAY_32MS                         SL_HAL_KEYSCAN_DELAY_32MS
#define sl_keyscan_delay_t                            sl_hal_keyscan_delay_t

// Structure.
#define sl_keyscan_config_t                           sl_hal_keyscan_config_t

// Function.
#define sl_keyscan_init                               sl_hal_keyscan_init
#define sl_keyscan_enable                             sl_hal_keyscan_enable
#define sl_keyscan_disable                            sl_hal_keyscan_disable
#define sl_keyscan_wait_ready                         sl_hal_keyscan_wait_ready
#define sl_keyscan_wait_sync                          sl_hal_keyscan_wait_sync
#define sl_keyscan_start_scan                         sl_hal_keyscan_start_scan
#define sl_keyscan_stop_scan                          sl_hal_keyscan_stop_scan
#define sl_keyscan_reset                              sl_hal_keyscan_reset
#define sl_keyscan_get_status                         sl_hal_keyscan_get_status
#define sl_keyscan_enable_interrupts                  sl_hal_keyscan_enable_interrupts
#define sl_keyscan_disable_interrupts                 sl_hal_keyscan_disable_interrupts
#define sl_keyscan_clear_interrupts                   sl_hal_keyscan_clear_interrupts
#define sl_keyscan_get_interrupts                     sl_hal_keyscan_get_interrupts
#define sl_keyscan_get_enabled_interrupts             sl_hal_keyscan_get_enabled_interrupts
#define sl_keyscan_set_interrupts                     sl_hal_keyscan_set_interrupts

#ifdef __cplusplus
}
#endif

#endif // PERIPHERAL_KEYSCAN_COMPAT_H
