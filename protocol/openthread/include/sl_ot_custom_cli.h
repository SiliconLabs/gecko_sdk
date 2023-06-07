/***************************************************************************//**
 * @file
 * @brief Provides definitions required to support CLI in both SoC and RCP
 * builds
 *
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 *
 * https://www.silabs.com/about-us/legal/master-software-license-agreement
 *
 * This software is distributed to you in Source Code format and is governed by
 * the sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include <openthread/cli.h>

extern otCliCommand sl_ot_custom_commands[];
extern const uint8_t sl_ot_custom_commands_count;

/**
 * Iterates over list of commands in @p aCommands to match the name
 * of the command referred to in @p aArgs and execute the handler
 * function if found.
 *
 * @param[in] *aContext	        Pointer to openthread instance
 * @param[in]  aArgsLength      Number of arguments in @p aArgs
 * @param[in] *aArgs[]          Array of arguments to pass to handler
 * @param[in]  aCommandsLength  Number of subcommands in @p aCommands
 * @param[in]  aCommands[]      List of subcommands registered by cli module
 *
 * @returns The result of the executed handler, or OT_ERROR_INVALID_ARGS if command was not found.
 */

otError processCommand(void *aContext,
                       uint8_t aArgsLength,
                       char *aArgs[],
                       uint8_t aCommandsLength,
                       const otCliCommand aCommands[]);

/**
 * Print all commands in @p commands
 *
 * @param[in]  commands         list of commands
 * @param[in]  commandCount     number of commands in @p commands
 *
 */
void printCommands(otCliCommand commands[], size_t commandCount);
