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

#ifndef SLI_SE_CPC_H
#define SLI_SE_CPC_H

// -----------------------------------------------------------------------------
// Macros

// Byte representing the SE CPC command type
#define SLI_CMD_EXECUTE_SE_COMMAND           (0x01u)

#define SLI_REQUEST_COMMAND_TYPE_OFFSET         (0u)
#define SLI_REQUEST_COMMAND_TYPE_SIZE           (1u)
#define SLI_REQUEST_COMMAND_OFFSET              (SLI_REQUEST_COMMAND_TYPE_OFFSET + SLI_REQUEST_COMMAND_TYPE_SIZE)
#define SLI_REQUEST_COMMAND_SIZE                (4u)
#define SLI_REQUEST_NUM_PARAMS_OFFSET           (SLI_REQUEST_COMMAND_OFFSET + SLI_REQUEST_COMMAND_SIZE)
#define SLI_REQUEST_NUM_PARAMS_SIZE             (1u)
#define SLI_REQUEST_PARAMS_OFFSET               (SLI_REQUEST_NUM_PARAMS_OFFSET + SLI_REQUEST_NUM_PARAMS_SIZE)
#define SLI_REQUEST_PARAMS_ELEMENT_SIZE         (4u)
#define SLI_REQUEST_NUM_INPUTS_SIZE             (1u)
#define SLI_REQUEST_INPUT_LENGTHS_ELEMENT_SIZE  (4u)
#define SLI_REQUEST_NUM_OUTPUTS_SIZE            (1u)
#define SLI_REQUEST_OUTPUT_LENGTHS_ELEMENT_SIZE (4u)

#define SLI_RESPONSE_COMMAND_TYPE_OFFSET         (0u)
#define SLI_RESPONSE_COMMAND_TYPE_SIZE           (1u)
#define SLI_RESPONSE_COMMAND_OFFSET              (SLI_RESPONSE_COMMAND_TYPE_OFFSET + SLI_RESPONSE_COMMAND_TYPE_SIZE)
#define SLI_RESPONSE_COMMAND_SIZE                (4u)
#define SLI_RESPONSE_COMMAND_RESPONSE_OFFSET     (SLI_RESPONSE_COMMAND_OFFSET + SLI_RESPONSE_COMMAND_SIZE)
#define SLI_RESPONSE_COMMAND_RESPONSE_SIZE       (4u)
#define SLI_RESPONSE_NUM_OUTPUTS_OFFSET          (SLI_RESPONSE_COMMAND_RESPONSE_OFFSET + SLI_RESPONSE_COMMAND_RESPONSE_SIZE)
#define SLI_RESPONSE_NUM_OUTPUTS_SIZE            (1u)
#define SLI_RESPONSE_OUTPUT_LENGTHS_OFFSET       (SLI_RESPONSE_NUM_OUTPUTS_OFFSET + SLI_RESPONSE_NUM_OUTPUTS_SIZE)
#define SLI_RESPONSE_OUTPUT_LENGTHS_ELEMENT_SIZE (4u)

#endif // SLI_SE_CPC_H
