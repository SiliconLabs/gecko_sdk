/***************************************************************************/ /**
 * @file
 * @brief CPC system endpoint secondary part
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

#ifndef SLI_CPC_SYSTEM_SECONDARY_H
#define SLI_CPC_SYSTEM_SECONDARY_H

#include "sli_cpc_system_common.h"
#include "sl_common.h"

SL_NORETURN void cpc_system_reset(sli_cpc_system_reboot_mode_t reboot_mode);

/***************************************************************************//**
 * Get a a system command buffer.
 *
 * @param[out] item Address of the variable that will receive the item pointer.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_get_system_command_buffer(sli_cpc_system_cmd_t **item);

/***************************************************************************//**
 * Free CPC system command buffer.
 *
 * @param[in] item Pointer to system command buffer to free.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_free_command_buffer(sli_cpc_system_cmd_t *item);

#endif
