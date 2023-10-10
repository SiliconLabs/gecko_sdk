/***************************************************************************//**
 * @file
 * @brief SLEEPTIMER SDK internal APIs.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SLI_SLEEPTIMER_H
#define SLI_SLEEPTIMER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "em_device.h"
#include "sl_sleeptimer_config.h"

#define SLEEPTIMER_EVENT_OF (0x01)
#define SLEEPTIMER_EVENT_COMP (0x02)

#define SLI_SLEEPTIMER_POWER_MANAGER_EARLY_WAKEUP_TIMER_FLAG 0x02
#define SLI_SLEEPTIMER_POWER_MANAGER_HF_ACCURACY_CLK_FLAG 0x04

#if SL_SLEEPTIMER_PERIPHERAL == SL_SLEEPTIMER_PERIPHERAL_DEFAULT
#if defined(RTCC_PRESENT) && RTCC_COUNT >= 1
#undef SL_SLEEPTIMER_PERIPHERAL
#define SL_SLEEPTIMER_PERIPHERAL SL_SLEEPTIMER_PERIPHERAL_RTCC
#elif defined(RTC_PRESENT) && RTC_COUNT >= 1
#undef SL_SLEEPTIMER_PERIPHERAL
#define SL_SLEEPTIMER_PERIPHERAL SL_SLEEPTIMER_PERIPHERAL_RTC
#elif defined(SYSRTC_PRESENT) && SYSRTC_COUNT >= 1
#undef SL_SLEEPTIMER_PERIPHERAL
#define SL_SLEEPTIMER_PERIPHERAL SL_SLEEPTIMER_PERIPHERAL_SYSRTC
#elif defined(BURTC_PRESENT) && BURTC_COUNT >= 1
#undef SL_SLEEPTIMER_PERIPHERAL
#define SL_SLEEPTIMER_PERIPHERAL SL_SLEEPTIMER_PERIPHERAL_BURTC
#elif defined(WTIMER_PRESENT) && WTIMER_COUNT >= 1
#undef SL_SLEEPTIMER_PERIPHERAL
#define SL_SLEEPTIMER_PERIPHERAL SL_SLEEPTIMER_PERIPHERAL_WTIMER
#elif defined(TIMER_PRESENT) && TIMER_COUNT >= 1
#undef SL_SLEEPTIMER_PERIPHERAL
#define SL_SLEEPTIMER_PERIPHERAL SL_SLEEPTIMER_PERIPHERAL_TIMER
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Hardware Abstraction Layer to perform initialization related to Power Manager.
 ******************************************************************************/
__WEAK void sli_sleeptimer_hal_power_manager_integration_init(void);

/*******************************************************************************
 * Hardware Abstraction Layer to perform initialization related to HFXO Manager.
 ******************************************************************************/
__WEAK void sli_sleeptimer_hal_hfxo_manager_integration_init(void);

/*******************************************************************************
 * Hardware Abstraction Layer to get interrupt status.
 *
 * @param local_flag Internal interrupt flag.
 *
 * @return Boolean indicating if specified interrupt is set.
 ******************************************************************************/
bool sli_sleeptimer_hal_is_int_status_set(uint8_t local_flag);

/**************************************************************************//**
 * Determines if next timer to expire has the option flag
 * "SLI_SLEEPTIMER_POWER_MANAGER_EARLY_WAKEUP_TIMER_FLAG".
 *
 * @return true if power manager will expire at next compare match,
 *         false otherwise.
 *****************************************************************************/
bool sli_sleeptimer_is_power_manager_timer_next_to_expire(void);

/***************************************************************************//**
 * Set lowest energy mode based on a project's configurations and clock source
 *
 * @note If power_manager_no_deepsleep component is included in a project, the
 *       lowest possible energy mode is EM1, else lowest energy mode is
 *       determined by clock source.
 ******************************************************************************/
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
void sli_sleeptimer_set_pm_em_requirement(void);
#endif

/***************************************************************************//**
 * @brief
 *   Update sleep_on_isr_exit flag.
 *
 * @param flag Boolean value update_sleep_on_isr_exit will be set to.
 ******************************************************************************/
void sli_sleeptimer_update_sleep_on_isr_exit(bool flag);

/*******************************************************************************
 * Gets the associated peripheral capture channel current value.
 *
 * @return Capture value
 *         0 if capture channel is not valid
 ******************************************************************************/
uint32_t sli_sleeptimer_get_capture(void);

/*******************************************************************************
 * Resets the PRS signal triggered by the associated peripheral.
 ******************************************************************************/
void sli_sleeptimer_reset_prs_signal(void);

#ifdef __cplusplus
}
#endif

#endif /* SLI_SLEEPTIMER_H */
