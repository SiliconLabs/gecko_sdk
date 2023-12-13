/***************************************************************************//**
 * @file
 * @brief DCDC_COULOMB_COUNTER Compatibility Layer.
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

#ifndef PERIPHERAL_DCDC_COULOMB_COUNTER_COMPAT_H
#define PERIPHERAL_DCDC_COULOMB_COUNTER_COMPAT_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *********************************   DEFINES   *********************************
 ******************************************************************************/

// Enum.
#define SL_DCDC_COULOMB_COUNTER_EM0                         SL_HAL_DCDC_COULOMB_COUNTER_EM0
#define SL_DCDC_COULOMB_COUNTER_EM2                         SL_HAL_DCDC_COULOMB_COUNTER_EM2
#define SL_DCDC_COULOMB_COUNTER_CAL_LOAD0                   SL_HAL_DCDC_COULOMB_COUNTER_CAL_LOAD0
#define SL_DCDC_COULOMB_COUNTER_CAL_LOAD1                   SL_HAL_DCDC_COULOMB_COUNTER_CAL_LOAD1
#define SL_DCDC_COULOMB_COUNTER_CAL_LOAD2                   SL_HAL_DCDC_COULOMB_COUNTER_CAL_LOAD2
#define SL_DCDC_COULOMB_COUNTER_CAL_LOAD3                   SL_HAL_DCDC_COULOMB_COUNTER_CAL_LOAD3
#define SL_DCDC_COULOMB_COUNTER_CAL_LOAD4                   SL_HAL_DCDC_COULOMB_COUNTER_CAL_LOAD4
#define SL_DCDC_COULOMB_COUNTER_CAL_LOAD5                   SL_HAL_DCDC_COULOMB_COUNTER_CAL_LOAD5
#define SL_DCDC_COULOMB_COUNTER_CAL_LOAD6                   SL_HAL_DCDC_COULOMB_COUNTER_CAL_LOAD6
#define SL_DCDC_COULOMB_COUNTER_CAL_LOAD7                   SL_HAL_DCDC_COULOMB_COUNTER_CAL_LOAD7
#define sl_dcdc_coulomb_counter_emode_t                     sl_hal_dcdc_coulomb_counter_emode_t
#define sl_dcdc_coulomb_counter_calibration_load_level_t    sl_hal_dcdc_coulomb_counter_calibration_load_level_t

// Structure.
#define sl_dcdc_coulomb_counter_config_t                    sl_hal_dcdc_coulomb_counter_config_t
#define sl_dcdc_coulomb_counter_calibration_config_t        sl_hal_dcdc_coulomb_counter_calibration_config_t

// Function.
#define sl_dcdc_coulomb_counter_init                        sl_hal_dcdc_coulomb_counter_init
#define sl_dcdc_coulomb_counter_enable                      sl_hal_dcdc_coulomb_counter_enable
#define sl_dcdc_coulomb_counter_disable                     sl_hal_dcdc_coulomb_counter_disable
#define sl_dcdc_coulomb_counter_wait_start                  sl_hal_dcdc_coulomb_counter_wait_start
#define sl_dcdc_coulomb_counter_wait_stop                   sl_hal_dcdc_coulomb_counter_wait_stop
#define sl_dcdc_coulomb_counter_wait_clear_counters         sl_hal_dcdc_coulomb_counter_wait_clear_counters
#define sl_dcdc_coulomb_counter_start                       sl_hal_dcdc_coulomb_counter_start
#define sl_dcdc_coulomb_counter_stop                        sl_hal_dcdc_coulomb_counter_stop
#define sl_dcdc_coulomb_counter_clear_counters              sl_hal_dcdc_coulomb_counter_clear_counters
#define sl_dcdc_coulomb_counter_get_count                   sl_hal_dcdc_coulomb_counter_get_count
#define sl_dcdc_coulomb_counter_get_status                  sl_hal_dcdc_coulomb_counter_get_status
#define sl_dcdc_coulomb_counter_enable_interrupts           sl_hal_dcdc_coulomb_counter_enable_interrupts
#define sl_dcdc_coulomb_counter_disable_interrupts          sl_hal_dcdc_coulomb_counter_disable_interrupts
#define sl_dcdc_coulomb_counter_clear_interrupts            sl_hal_dcdc_coulomb_counter_clear_interrupts
#define sl_dcdc_coulomb_counter_get_interrupts              sl_hal_dcdc_coulomb_counter_get_interrupts
#define sl_dcdc_coulomb_counter_get_enabled_interrupts      sl_hal_dcdc_coulomb_counter_get_enabled_interrupts
#define sl_dcdc_coulomb_counter_set_interrupts              sl_hal_dcdc_coulomb_counter_set_interrupts
#define sl_dcdc_coulomb_counter_cal_init                    sl_hal_dcdc_coulomb_counter_cal_init
#define sl_dcdc_coulomb_counter_cal_start                   sl_hal_dcdc_coulomb_counter_cal_start
#define sl_dcdc_coulomb_counter_cal_stop                    sl_hal_dcdc_coulomb_counter_cal_stop
#define sl_dcdc_coulomb_counter_enable_cal_load             sl_hal_dcdc_coulomb_counter_enable_cal_load
#define sl_dcdc_coulomb_counter_disable_cal_load            sl_hal_dcdc_coulomb_counter_disable_cal_load
#define sl_dcdc_coulomb_counter_set_cal_load_level          sl_hal_dcdc_coulomb_counter_set_cal_load_level
#define sl_dcdc_coulomb_counter_get_cal_load_current        sl_hal_dcdc_coulomb_counter_get_cal_load_current
#define sl_dcdc_coulomb_counter_get_cal_reference_freq      sl_hal_dcdc_coulomb_counter_get_cal_reference_freq
#define sl_dcdc_coulomb_counter_set_calhalt                 sl_hal_dcdc_coulomb_counter_set_calhalt
#define sl_dcdc_coulomb_counter_calhalt_is_set              sl_hal_dcdc_coulomb_counter_calhalt_is_set

#ifdef __cplusplus
}
#endif

#endif // PERIPHERAL_DCDC_COULOMB_COUNTER_COMPAT_H
