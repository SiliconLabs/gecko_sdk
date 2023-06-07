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

#ifndef SL_SE_CPC_SECONDARY_H
#define SL_SE_CPC_SECONDARY_H

#include <stddef.h>
#include "sl_status.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * @brief
 *   Parse and execute serialised SE command.
 *
 * @param[in] command_request
 *   A buffer holding the serialised SE command.
 *
 * @param[in] command_request_size
 *   Size of the serialised SE command.
 *
 * @param[out] command_response
 *   A buffer to store the SE command response.
 *
 * @param[in] command_response_buffer_size
 *   Size of the buffer to store the SE command response.
 *
 * @param[out] command_response_size
 *   Size of the SE command response.
 *
 * @return
 *   PSA_SUCCESS if SE executes the command properly as expected,
 *   otherwise an error. The return code does not represent the SE command
 *   response.
 ******************************************************************************/
sl_status_t sl_cpc_se_execute_command(const uint8_t *command_request,
                                      size_t        command_request_size,
                                      uint8_t       *command_response,
                                      size_t        command_response_buffer_size,
                                      size_t        *command_response_size);

#ifdef __cplusplus
}
#endif

#endif // SL_SE_CPC_SECONDARY_H
