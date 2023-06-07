/***************************************************************************//**
 * @file
 * @brief Silicon Labs Secure Engine mailbox over CPC
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

#ifndef SL_SE_CPC_PRIMARY_H
#define SL_SE_CPC_PRIMARY_H

#include <stddef.h>
#include "sl_status.h"
#include "sl_se_manager_types.h"
#include "sl_cpc.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @brief
 *   Open the Secure Engine endpoint.
 *
 * @param[out] lib_handle
 *   CPC library handle.
 *
 * @return On error, a negative value of errno is returned.
 *          On success, the file descriptor of the socket is returned.
 ******************************************************************************/
int sl_cpc_se_init(cpc_handle_t *lib_handle);

/***************************************************************************//**
 * @brief
 *   Execute and wait for SE mailbox command to complete.
 *
 * @details
 *   This function serialises the content of the input structure and its members.
 *   Once the serialisation is complete, it writes to the CPC endpoint using the
 *   endpoint handle stored in the input structure. The CPC endpoint write
 *   operation will be blocking and waits for command response before proceeding.
 *
 * @param[in] cmd_ctx
 *   Pointer to a filled-out SE command structure.
 ******************************************************************************/
sl_status_t sli_se_execute_and_wait(sl_se_command_context_t *cmd_ctx);

#ifdef __cplusplus
}
#endif

#endif // SL_SE_CPC_PRIMARY_H
