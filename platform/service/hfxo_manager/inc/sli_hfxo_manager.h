/***************************************************************************//**
 * @file
 * @brief HFXO Manager API definition.
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

#ifndef SLI_HFXO_MANAGER_H
#define SLI_HFXO_MANAGER_H

#include <stdbool.h>
#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#if defined(SL_CATALOG_SLEEPTIMER_PRESENT) && defined(SYSRTC_PRESENT)
#include "sli_sleeptimer.h"
#if (SL_SLEEPTIMER_PERIPHERAL == SL_SLEEPTIMER_PERIPHERAL_SYSRTC)
#define HFXO_MANAGER_SLEEPTIMER_SYSRTC_INTEGRATION_ON
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * HFXO Manager module hardware specific initialization.
 ******************************************************************************/
void sli_hfxo_manager_init_hardware(void);

/***************************************************************************//**
 * Function to call just before starting HFXO, to save current tick count.
 ******************************************************************************/
void sli_hfxo_manager_begin_startup_measurement(void);

#if defined(HFXO_MANAGER_SLEEPTIMER_SYSRTC_INTEGRATION_ON)
/***************************************************************************//**
 * Function to call when a SYSRTC compare match event produces a PRS signal to
   start HFXO.
 ******************************************************************************/
void sli_hfxo_manager_retrieve_begining_startup_measurement(void);
#endif

/***************************************************************************//**
 * Function to call just after HFXO becomes ready, to save current tick count
 * and calculate HFXO startup time.
 ******************************************************************************/
void sli_hfxo_manager_end_startup_measurement(void);

/***************************************************************************//**
 * Retrieves HFXO startup time average value.
 ******************************************************************************/
uint32_t sli_hfxo_manager_get_startup_time(void);

/***************************************************************************//**
 * Retrieves HFXO startup time latest value.
 ******************************************************************************/
uint32_t sli_hfxo_manager_get_latest_startup_time(void);

/***************************************************************************//**
 * Checks if HFXO is ready and, if needed, waits for it to be.
 *
 * @param  wait  True, to wait for HFXO to be ready.
 *               False, otherwise.
 *
 * @return True, if HFXO is ready.
 *         False, otherwise.
 *
 * @note This will also make sure we are not in the process of restarting HFXO
 *       with different settings.
 ******************************************************************************/
bool sli_hfxo_manager_is_hfxo_ready(bool wait);

#ifdef __cplusplus
}
#endif

#endif /* SLI_HFXO_MANAGER_H */
