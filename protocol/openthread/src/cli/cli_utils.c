/***************************************************************************/
/**
 * @file
 * @brief Utility functions for handling CLI list of CLI commands
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_ot_custom_cli.h"
#include "common/code_utils.hpp"
#include <string.h>

otError processCommand(void *aContext,
                       uint8_t            aArgsLength,
                       char              *aArgs[],
                       uint8_t            aCommandsLength,
                       const otCliCommand aCommands[])
{
    otError error = OT_ERROR_INVALID_COMMAND;

    VerifyOrExit(aArgs && aArgsLength != 0 && aCommands && aCommandsLength != 0);

    for (size_t i = 0; i < aCommandsLength; i++)
    {
        if (strcmp(aArgs[0], aCommands[i].mName) == 0)
        {
            // Command found, call command handler
            error = (aCommands[i].mCommand)(aContext, aArgsLength - 1, (aArgsLength > 1) ? &aArgs[1] : NULL);
            ExitNow();
        }
    }

exit:
    return error;
}

void printCommands(otCliCommand commands[], size_t commandCount)
{
    for (size_t i = 0; i < commandCount; i++) {
        otCliOutputFormat("%s\r\n", commands[i].mName);
    }
}

