/***************************************************************************//**
 * @file
 * @brief SYSRTC Compatibility Layer.
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

#ifndef PERIPHERAL_SYSRTC_COMPAT_H
#define PERIPHERAL_SYSRTC_COMPAT_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *********************************   DEFINES   *********************************
 ******************************************************************************/

// Enum.
#define SL_SYSRTC_CAPTURE_EDGE_RISING                 SL_HAL_SYSRTC_CAPTURE_EDGE_RISING
#define SL_SYSRTC_CAPTURE_EDGE_FALLING                SL_HAL_SYSRTC_CAPTURE_EDGE_FALLING
#define SL_SYSRTC_CAPTURE_EDGE_BOTH                   SL_HAL_SYSRTC_CAPTURE_EDGE_BOTH
#define SL_SYSRTC_COMPARE_MATCH_OUT_ACTION_CLEAR      SL_HAL_SYSRTC_COMPARE_MATCH_OUT_ACTION_CLEAR
#define SL_SYSRTC_COMPARE_MATCH_OUT_ACTION_SET        SL_HAL_SYSRTC_COMPARE_MATCH_OUT_ACTION_SET
#define SL_SYSRTC_COMPARE_MATCH_OUT_ACTION_PULSE      SL_HAL_SYSRTC_COMPARE_MATCH_OUT_ACTION_PULSE
#define SL_SYSRTC_COMPARE_MATCH_OUT_ACTION_TOGGLE     SL_HAL_SYSRTC_COMPARE_MATCH_OUT_ACTION_TOGGLE
#define SL_SYSRTC_COMPARE_MATCH_OUT_ACTION_CMPIF      SL_HAL_SYSRTC_COMPARE_MATCH_OUT_ACTION_CMPIF
#define sl_sysrtc_capture_edge_t                      sl_hal_sysrtc_capture_edge_t
#define sl_sysrtc_compare_match_out_action_t          sl_hal_sysrtc_compare_match_out_action_t

// Structure.
#define sl_sysrtc_config_t                            sl_hal_sysrtc_config_t
#define sl_sysrtc_group_channel_compare_config_t      sl_hal_sysrtc_group_channel_compare_config_t
#define sl_sysrtc_group_channel_capture_config_t      sl_hal_sysrtc_group_channel_capture_config_t
#define sl_sysrtc_group_config_t                      sl_hal_sysrtc_group_config_t

// Function.
#define sl_sysrtc_init                                sl_hal_sysrtc_init
#define sl_sysrtc_enable                              sl_hal_sysrtc_enable
#define sl_sysrtc_disable                             sl_hal_sysrtc_disable
#define sl_sysrtc_wait_sync                           sl_hal_sysrtc_wait_sync
#define sl_sysrtc_wait_ready                          sl_hal_sysrtc_wait_ready
#define sl_sysrtc_start                               sl_hal_sysrtc_start
#define sl_sysrtc_stop                                sl_hal_sysrtc_stop
#define sl_sysrtc_reset                               sl_hal_sysrtc_reset
#define sl_sysrtc_get_status                          sl_hal_sysrtc_get_status
#define sl_sysrtc_lock                                sl_hal_sysrtc_lock
#define sl_sysrtc_unlock                              sl_hal_sysrtc_unlock
#define sl_sysrtc_get_counter                         sl_hal_sysrtc_get_counter
#define sl_sysrtc_set_counter                         sl_hal_sysrtc_set_counter
#define sl_sysrtc_init_group                          sl_hal_sysrtc_init_group
#define sl_sysrtc_enable_group_interrupts             sl_hal_sysrtc_enable_group_interrupts
#define sl_sysrtc_disable_group_interrupts            sl_hal_sysrtc_disable_group_interrupts
#define sl_sysrtc_clear_group_interrupts              sl_hal_sysrtc_clear_group_interrupts
#define sl_sysrtc_get_group_interrupts                sl_hal_sysrtc_get_group_interrupts
#define sl_sysrtc_get_group_enabled_interrupts        sl_hal_sysrtc_get_group_enabled_interrupts
#define sl_sysrtc_set_group_interrupts                sl_hal_sysrtc_set_group_interrupts
#define sl_sysrtc_get_group_compare_channel_value     sl_hal_sysrtc_get_group_compare_channel_value
#define sl_sysrtc_set_group_compare_channel_value     sl_hal_sysrtc_set_group_compare_channel_value
#define sl_sysrtc_get_group_capture_channel_value     sl_hal_sysrtc_get_group_capture_channel_value

#ifdef __cplusplus
}
#endif

#endif // PERIPHERAL_SYSRTC_COMPAT_H
