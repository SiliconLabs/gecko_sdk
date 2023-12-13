/***************************************************************************/ /**
 * @file
 * @brief CPC Firmware Upgrade Driver Interface
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

#ifndef SLI_CPC_DRV_FWU_H
#define SLI_CPC_DRV_FWU_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "sl_status.h"
#include "sl_common.h"

#include "sl_cpc_primary_config.h"

#ifdef __cplusplus
extern "C"
{
#endif

/***************************************************************************//**
 * The firmware upgrade process action called by the main CPC process action
 ******************************************************************************/
void sli_cpc_fwu_process_action(void);

/***************************************************************************//**
 * Gets whether or not a firmware upgrade is in progress
 *
 * @return bool : Firmware upgrade in progress
 ******************************************************************************/
bool sli_cpc_is_fwu_in_progress(void);

/***************************************************************************//**
 * Checks if the bootloader is currently running
 *
 * @return bool :
 *   true : The bootloader responded to the poke.
 *   false : The bootloader did not respond to the poke.
 ******************************************************************************/
bool sli_cpc_is_bootloader_running(void);

/***************************************************************************//**
 * The main firmware upgrade finite state machine
 *
 * @return sl_status_t :
 *   SL_STATUS_IN_PROGRESS : The firmware upgrade is still and progress.
 *                           This funcion needs do be called again
 *   SL_STATUS_OK          : The firmware update is done
 ******************************************************************************/
sl_status_t sli_cpc_drv_fwu_step(void);

/***************************************************************************//**
 * Initialize the firmware update driver
 ******************************************************************************/
void sli_cpc_drv_fwu_init();

/***************************************************************************//**
 * Starts the firmware upgrade process of the secondary.
 *
 * @return sl_status :
 *   SL_STATUS_OK : The firmware update process has successfuly started. The CPC API will
 *                  now be blocked and the 'sl_cpc_get_fwu_chunk' callback implemented by the
 *                  user will now be continuously called until the firmware image has been
 *                  completely transfered.
 *
 *  If not SL_STATUS_OK, the return value will be the one returned by
 *  sl_cpc_is_firmware_upgrade_startable()
 ******************************************************************************/
sl_status_t sl_cpc_fwu_start(void);

/***************************************************************************//**
 * Checks if a firmware upgrade can be started
 *
 * @return sl_status :
 *   SL_STATUS_OK : If a firmware upgrade can be started
 *   SL_STATUS_IN_PROGRESS : If a firmware upgrade is already in progress
 *   SL_STATUS_NOT_READY : If the firmware upgrade cannot yet be started. This
 *     would be because the reset sequence is not yet finished.
 *   SL_STATUS_NOT_AVAILABLE : If the user did not provide an implementation for
 *     "sl_cpc_get_fwu_chunk()"
 *   SL_STATUS_NOT_SUPPORTED : If after the reset sequence, the secondary returned
 *     that is does not have a suitable gecko bootloader.
 ******************************************************************************/
sl_status_t sl_cpc_is_fwu_startable(void);

#if (SL_CPC_PRIMARY_FIRMWARE_UPGRADE_RECOVERY_PINS_SUPPORT_ENABLED >= 1)
/***************************************************************************//**
 * Uses the bootloader recovery pins to reset the secondary and force the
 * bootloader to stay in bootloader mode to perform a firmware upgrade
 ******************************************************************************/
void sli_cpc_drv_fwu_enter_bootloader_via_recovery_pins(void);
#endif

/** @} (end addtogroup cpc) */

#ifdef __cplusplus
}
#endif

#endif // SLI_CPC_DRV_FWU_H
