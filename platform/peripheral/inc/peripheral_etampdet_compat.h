/***************************************************************************//**
 * @file
 * @brief ETAMPDET Compatibility Layer.
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

#ifndef PERIPHERAL_ETAMPDET_COMPAT_H
#define PERIPHERAL_ETAMPDET_COMPAT_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *********************************   DEFINES   *********************************
 ******************************************************************************/

// Enum.
#define sl_etampdet_channel_t                         sl_hal_etampdet_channel_t
#define sl_etampdet_channel_cnt_mismatch_threshold_t  sl_hal_etampdet_channel_cnt_mismatch_threshold_t
#define sl_etampdet_channel_filt_win_size_t           sl_hal_etampdet_channel_filt_win_size_t
#define sl_etampdet_upper_clk_presc_t                 sl_hal_etampdet_upper_clk_presc_t
#define sl_etampdet_lower_clk_presc_t                 sl_hal_etampdet_lower_clk_presc_t

// Structure.
#define sl_etampdet_config_channel_t                  sl_hal_etampdet_config_channel_t
#define sl_etampdet_config_t                          sl_hal_etampdet_config_t

// Function.
#define sl_etampdet_init                              sl_hal_etampdet_init
#define sl_etampdet_init_channel                      sl_hal_etampdet_init_channel
#define sl_etampdet_wait_sync                         sl_hal_etampdet_wait_sync
#define sl_etampdet_wait_ready                        sl_hal_etampdet_wait_ready
#define sl_etampdet_enable                            sl_hal_etampdet_enable
#define sl_etampdet_disable                           sl_hal_etampdet_disable
#define sl_etampdet_load                              sl_hal_etampdet_load
#define sl_etampdet_start                             sl_hal_etampdet_start
#define sl_etampdet_stop                              sl_hal_etampdet_stop
#define sl_etampdet_enable_interrupts                 sl_hal_etampdet_enable_interrupts
#define sl_etampdet_disable_interrupts                sl_hal_etampdet_disable_interrupts
#define sl_etampdet_set_interrupts                    sl_hal_etampdet_set_interrupts
#define sl_etampdet_clear_interrupts                  sl_hal_etampdet_clear_interrupts
#define sl_etampdet_get_interrupts                    sl_hal_etampdet_get_interrupts
#define sl_etampdet_get_enabled_interrupts            sl_hal_etampdet_get_enabled_interrupts
#define sl_etampdet_lock                              sl_hal_etampdet_lock
#define sl_etampdet_unlock                            sl_hal_etampdet_unlock
#define sl_etampdet_get_status                        sl_hal_etampdet_get_status
#define sl_etampdet_set_seed_value                    sl_hal_etampdet_set_seed_value
#define sl_etampdet_get_seed_value                    sl_hal_etampdet_get_seed_value

#ifdef __cplusplus
}
#endif

#endif // PERIPHERAL_ETAMPDET_COMPAT_H
