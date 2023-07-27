/*
 *  Copyright (c) 2023, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * @file
 * @brief This file defines the vendor posix cli command lists that are registered
 *        with the OpenThread CLI library as user commands.
 */

#include <openthread/cli.h>
#include "common/code_utils.hpp"

#ifdef SL_OPENTHREAD_ANT_DIV_CLI_ENABLE
extern "C" otError antennaCommand(void *aContext, uint8_t aArgsLength, char *aArgs[]);
#endif // SL_OPENTHREAD_ANT_DIV_CLI_ENABLE

#ifdef SL_OPENTHREAD_COEX_CLI_ENABLE
extern "C" otError coexCommand(void *aContext, uint8_t aArgsLength, char *aArgs[]);
#endif // SL_OPENTHREAD_COEX_CLI_ENABLE

#ifdef SL_OPENTHREAD_TEST_CLI_ENABLE
extern "C" otError testCommand(void *aContext, uint8_t aArgsLength, char *aArgs[]);
#endif

#ifdef SL_OPENTHREAD_EFR32_CLI_ENABLE
extern "C" otError efr32Command(void *aContext, uint8_t aArgsLength, char *aArgs[]);
#endif

//-----------------------------------------------------------------------------
// Extern CLI symbol definitions
//-----------------------------------------------------------------------------
extern const otCliCommand sl_ot_custom_commands[] = {
#ifdef SL_OPENTHREAD_ANT_DIV_CLI_ENABLE
    {"antenna", antennaCommand},
#endif // SL_OPENTHREAD_ANT_DIV_CLI_ENABLE
#ifdef SL_OPENTHREAD_COEX_CLI_ENABLE
    {"coexistence", coexCommand},
#endif // SL_OPENTHREAD_COEX_CLI_ENABLE
#ifdef SL_OPENTHREAD_TEST_CLI_ENABLE
    {"test", testCommand},
#endif // SL_OPENTHREAD_TEST_CLI_ENABLE
#ifdef SL_OPENTHREAD_EFR32_CLI_ENABLE
    {"efr32", efr32Command},
#endif // SL_OPENTHREAD_EFR32_CLI_ENABLE
};

uint8_t sl_ot_custom_commands_count = OT_ARRAY_LENGTH(sl_ot_custom_commands);

void otCliVendorSetUserCommands(void)
{
    if (sl_ot_custom_commands_count > 0)
    {
        IgnoreError(otCliSetUserCommands(sl_ot_custom_commands, sl_ot_custom_commands_count, nullptr));
    }
}
