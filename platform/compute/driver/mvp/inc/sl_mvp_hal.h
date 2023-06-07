/***************************************************************************//**
 * @file
 * @brief MVP HAL Driver.
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
#ifndef SL_MVP_HAL_H
#define SL_MVP_HAL_H

#include "sl_status.h"
#include <stdbool.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN

typedef void (*sli_mvp_enable_callback)(void);
typedef void (*sli_mvp_disable_callback)(void);
typedef bool (*sli_mvp_isr_callback)(void);

/**
 * MVP configuration parameters.
 */
typedef struct {
  bool use_dma;
  unsigned dma_ch;
} sli_mvp_hal_config_t;

/**
 * @brief
 *   Initialize the MVP hardware.
 *
 * @details
 *   This function must be called once before any of the other functions are
 *   used. This function will configure the MVP hardware based on the content
 *   of the sl_driver_mvp_config.h file.
 *
 * @param[in] enable Pointer to the function that will be called when the MVP shall be enabled.
 * @param[in] disable Pointer to the function that will be called when the MVP shall be disabled.
 * @param[in] isr Pointer to the function that will be called when an interrupt occurs.
 *
 * @return
 *   SL_STATUS_OK on success, other value on failure.
 */
sl_status_t sli_mvp_hal_init(sli_mvp_enable_callback enable, sli_mvp_disable_callback disable, sli_mvp_isr_callback isr);

/**
 * @brief
 *   De-Initialize the MVP hardware.
 *
 * @details
 *   This function can be called when the MVP hardware is no longer being used.
 *
 * @return
 *   SL_STATUS_OK on success, other value on failure.
 */
sl_status_t sli_mvp_hal_deinit(void);

/**
 * @brief
 *   Configure the operation of the MVP driver.
 *
 * @details
 *   This function can be used to reconfigure the MVP driver behavior after
 *   sli_mvp_init is called. This function can be used to switch between using
 *   DMA and CPU to load programs at runtime.
 *
 * @return
 *   SL_STATUS_OK on success, other value on failure.
 */
sl_status_t sli_mvp_hal_config(sli_mvp_hal_config_t *config);

/**
 * @brief
 *   Load a program into the MVP registers.
 *
 * @param[in] src Pointer to the program.
 * @param[in] dst Pointer to the MVP register where the program shall be loaded.
 * @param[in] length Length of the program in bytes.
 *
 * @return
 *   SL_STATUS_OK on success, other value on failure.
 */
sl_status_t sli_mvp_hal_load_program(void *src, void *dst, size_t length);

/**
 * @brief
 *   Enable the MVP for program execution. This function must be called before
 *   the MVP command is set and the program is started.
 */
void sli_mvp_hal_cmd_enable(void);

/**
 * @brief
 *   Check if a program is running.
 *
 * @return
 *   True if a program is running, else false.
 */
bool sli_mvp_hal_cmd_is_busy(void);

/**
 * @brief
 *   If there is a program running, wait for it to to complete.
 */
void sli_mvp_hal_cmd_wait_for_completion(void);

/// @endcond

#ifdef __cplusplus
}
#endif

#endif //SL_MVP_HAL_H
