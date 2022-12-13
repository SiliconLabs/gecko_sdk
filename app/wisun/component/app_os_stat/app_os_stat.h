/***************************************************************************//**
 * @file
 * @brief OS memory debug for application
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

#ifndef SL_APP_OS_STAT_H
#define SL_APP_OS_STAT_H

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#include "sl_status.h"
#include "app_os_stat_config.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * @brief Initialize App OS statistic service
 * @details Init thread and staistic storage
 ******************************************************************************/
void app_os_stat_init(void);

#if APP_OS_STAT_MANUAL_REGISTER_THREADS
/***************************************************************************//**
 * @brief Register thread to track
 * @details Thread stack usage is tracked
 * @param[in] thr_id Thread ID
 * @return sl_status_t SL_STATUS_OK on success, SL_STATUS_FAIL on error
 ******************************************************************************/
sl_status_t app_os_stat_register_thread(const osThreadId_t thr_id);

/***************************************************************************//**
 * @brief Remove thread from list
 * @details Remove thread from tracked thread list
 * @param[in] thr_id Thread ID
 * @return sl_status_t SL_STATUS_OK on success, SL_STATUS_FAIL on error
 ******************************************************************************/
sl_status_t app_os_stat_remove_thread(const osThreadId_t thr_id);
#endif

#ifdef __cplusplus
}
#endif
#endif /* SL_APP_OS_STAT_H */
