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
 * @brief This file contains definitions for a spinel extension to support coex commands.
 */

#include "ncp_coex.hpp"
#include "vendor_spinel.hpp"
#include "radio_extension.h"

#include "common/code_utils.hpp"

namespace CoexCmd = ot::Vendor::Coex;

namespace ot {
namespace Ncp {
namespace Vendor {
namespace Coex {

static otError getDpState(Spinel::Encoder &aEncoder);
static otError setDpState(Spinel::Decoder &aDecoder);
static otError getGpioInputOverride(Spinel::Encoder &aEncoder);
static otError setGpioInputOverride(Spinel::Decoder &aDecoder);
static otError getActiveRadio(Spinel::Encoder &aEncoder);
static otError getPhySelectTimeout(Spinel::Encoder &aEncoder);
static otError setPhySelectTimeout(Spinel::Decoder &aDecoder);
static otError getPtaOptions(Spinel::Encoder &aEncoder);
static otError setPtaOptions(Spinel::Decoder &aDecoder);
static otError getConstantOptions(Spinel::Encoder &aEncoder);
static otError getPtaState(Spinel::Encoder &aEncoder);
static otError setPtaState(Spinel::Decoder &aDecoder);
static otError getPwmState(Spinel::Encoder &aEncoder);
static otError setPwmState(Spinel::Decoder &aDecoder);
static otError getCounters(Spinel::Encoder &aEncoder);
static otError resetCounters(void);
static otError setRadioHoldoff(Spinel::Decoder &aDecoder);

otError getCoexProperty(Spinel::Decoder &aDecoder, Spinel::Encoder &aEncoder)
{
    otError error = OT_ERROR_NOT_FOUND;
    uint8_t cmdKey;

    SuccessOrExit(aDecoder.ReadUint8(cmdKey));

    switch(cmdKey)
    {
        case CoexCmd::COEX_DP_STATE_COMMAND:
            error = getDpState(aEncoder);
            break;
        case CoexCmd::COEX_GPIO_INPUT_OVERRIDE_COMMAND:
            error = getGpioInputOverride(aEncoder);
            break;
        case CoexCmd::COEX_ACTIVE_RADIO_COMMAND:
            error = getActiveRadio(aEncoder);
            break;
        case CoexCmd::COEX_PHY_SELECT_TIMEOUT_COMMAND:
            error = getPhySelectTimeout(aEncoder);
            break;
        case CoexCmd::COEX_PTA_OPTIONS_COMMAND:
            error = getPtaOptions(aEncoder);
            break;
        case CoexCmd::COEX_CONSTANT_OPTIONS_COMMAND:
            error = getConstantOptions(aEncoder);
            break;
        case CoexCmd::COEX_PTA_STATE_COMMAND:
            error = getPtaState(aEncoder);
            break;
        case CoexCmd::COEX_PWM_STATE_COMMAND:
            error = getPwmState(aEncoder);
            break;
        case CoexCmd::COEX_COUNTERS_COMMAND:
            error = getCounters(aEncoder);
            break;
    }

exit:
    return error;
}

otError setCoexProperty(Spinel::Decoder &aDecoder)
{
    otError error = OT_ERROR_NOT_FOUND;
    uint8_t cmdKey;

    SuccessOrExit(aDecoder.ReadUint8(cmdKey));

    switch(cmdKey)
    {
        case CoexCmd::COEX_DP_STATE_COMMAND:
            error = setDpState(aDecoder);
            break;
        case CoexCmd::COEX_GPIO_INPUT_OVERRIDE_COMMAND:
            error = setGpioInputOverride(aDecoder);
            break;
        case CoexCmd::COEX_PHY_SELECT_TIMEOUT_COMMAND:
            error = setPhySelectTimeout(aDecoder);
            break;
        case CoexCmd::COEX_PTA_OPTIONS_COMMAND:
            error = setPtaOptions(aDecoder);
            break;
        case CoexCmd::COEX_PTA_STATE_COMMAND:
            error = setPtaState(aDecoder);
            break;
        case CoexCmd::COEX_PWM_STATE_COMMAND:
            error = setPwmState(aDecoder);
            break;
        case CoexCmd::COEX_COUNTERS_COMMAND:
            error = resetCounters();
            break;
        case CoexCmd::COEX_RADIO_HOLDOFF_COMMAND:
            error = setRadioHoldoff(aDecoder);
            break;
    }

exit:
    return error;
}

otError getDpState(Spinel::Encoder &aEncoder)
{
    uint8_t dpPulse = 0;

    IgnoreError(otPlatRadioExtensionGetDpState(&dpPulse));

    return (aEncoder.WriteUint8(dpPulse));
}

otError setDpState(Spinel::Decoder &aDecoder)
{
    uint8_t dpPulse  = 0;
    otError error    = OT_ERROR_NONE;

    SuccessOrExit(error = aDecoder.ReadUint8(dpPulse));
    
    error = otPlatRadioExtensionSetDpState(dpPulse);

exit:
    return error;
}

otError getGpioInputOverride(Spinel::Encoder &aEncoder)
{
    uint8_t inputOverrides = 0;

    for (uint8_t ind = 0; ind < (sizeof(inputOverrides) * 8); ind++)
    {
        uint8_t enabled = 0;
        SuccessOrExit(otPlatRadioExtensionGetGpioInputOverride(ind, (bool*)&enabled));
        inputOverrides |= (((uint8_t)enabled & 0x01) << (uint8_t)ind);
    }

exit:
    return (aEncoder.WriteUint8(inputOverrides));
}

otError setGpioInputOverride(Spinel::Decoder &aDecoder)
{
    uint8_t gpioIndex = 0;
    bool enabled      = false;
    otError error     = OT_ERROR_NONE;

    SuccessOrExit(error = aDecoder.ReadUint8(gpioIndex));
    SuccessOrExit(error = aDecoder.ReadBool(enabled));

    error = otPlatRadioExtensionSetGpioInputOverride(gpioIndex, enabled);

exit:
    return error;
}

otError getActiveRadio(Spinel::Encoder &aEncoder)
{
    uint8_t activePhy = 0;

    IgnoreError(otPlatRadioExtensionGetActiveRadio(&activePhy));

    return aEncoder.WriteUint8(activePhy);
}

otError getPhySelectTimeout(Spinel::Encoder &aEncoder)
{
    uint8_t timeout = 0;

    IgnoreError(otPlatRadioExtensionGetPhySelectTimeout(&timeout));
    
    return aEncoder.WriteUint8(timeout);
}

otError setPhySelectTimeout(Spinel::Decoder &aDecoder)
{
    uint8_t timeoutMs = 0;
    otError error     = OT_ERROR_NONE;

    SuccessOrExit(error = aDecoder.ReadUint8(timeoutMs));

    error = otPlatRadioExtensionSetPhySelectTimeout(timeoutMs);

exit:
    return error;
}

otError getPtaOptions(Spinel::Encoder &aEncoder)
{
    uint32_t ptaOptions;

    IgnoreError(otPlatRadioExtensionGetCoexOptions(&ptaOptions));

    return aEncoder.WriteUint32(ptaOptions);
}

otError setPtaOptions(Spinel::Decoder &aDecoder)
{
    uint32_t ptaOptions = 0;
    otError error       = OT_ERROR_NONE;

    SuccessOrExit(error = aDecoder.ReadUint32(ptaOptions));

    error = otPlatRadioExtensionSetCoexOptions(ptaOptions);

exit:
    return error;
}

otError getConstantOptions(Spinel::Encoder &aEncoder)
{
    uint32_t ptaOptions;

    IgnoreError(otPlatRadioExtensionGetCoexConstantOptions(&ptaOptions));

    return aEncoder.WriteUint32(ptaOptions);
}

otError getPtaState(Spinel::Encoder &aEncoder)
{
    bool ptaState;

    IgnoreError(otPlatRadioExtensionIsCoexEnabled(&ptaState));

    return aEncoder.WriteBool(ptaState);
}

otError setPtaState(Spinel::Decoder &aDecoder)
{
    bool ptaState = 0;
    otError error = OT_ERROR_NONE;

    SuccessOrExit(error = aDecoder.ReadBool(ptaState));

    error = otPlatRadioExtensionSetCoexEnable(ptaState);

exit:
    return error;
}

otError getPwmState(Spinel::Encoder &aEncoder)
{
    uint8_t ptaReq, dutyCycle, periodHalfMs;
    otError error = OT_ERROR_FAILED;

    SuccessOrExit(error = otPlatRadioExtensionGetRequestPwmArgs(&ptaReq, &dutyCycle, &periodHalfMs));

    SuccessOrExit(error = aEncoder.WriteUint8(ptaReq));
    SuccessOrExit(error = aEncoder.WriteUint8(dutyCycle));
    SuccessOrExit(error = aEncoder.WriteUint8(periodHalfMs));

exit:
    return error;
}

otError setPwmState(Spinel::Decoder &aDecoder)
{
    uint8_t ptaReq, dutyCycle, periodHalfMs;
    otError error = OT_ERROR_NONE;

    SuccessOrExit(error = aDecoder.ReadUint8(ptaReq));
    SuccessOrExit(error = aDecoder.ReadUint8(dutyCycle));
    SuccessOrExit(error = aDecoder.ReadUint8(periodHalfMs));

    error = otPlatRadioExtensionSetRequestPwmArgs(ptaReq, dutyCycle, periodHalfMs);

exit:
    return error;
}

otError getCounters(Spinel::Encoder &aEncoder)
{
    uint32_t coexCounters[OT_PLAT_RADIO_EXTENSION_COEX_EVENT_COUNT] = {0};
    otError error                                                = OT_ERROR_NONE;
    
    SuccessOrExit(error = otPlatRadioExtensionGetCoexCounters(OT_PLAT_RADIO_EXTENSION_COEX_EVENT_COUNT, coexCounters));

    for (uint8_t ind = 0; ind < (uint8_t)OT_PLAT_RADIO_EXTENSION_COEX_EVENT_COUNT; ind++)
    {
        SuccessOrExit(error = aEncoder.WriteUint32(coexCounters[ind]));
    }

exit:
    return error;
}

otError resetCounters(void)
{
    return otPlatRadioExtensionClearCoexCounters();
}

otError setRadioHoldoff(Spinel::Decoder &aDecoder)
{
    bool enabled;
    otError error = OT_ERROR_NONE;

    SuccessOrExit(error = aDecoder.ReadBool(enabled));

    error = otPlatRadioExtensionSetRadioHoldoff(enabled);

exit:
    return error;
}

} // namespace Coex
} // namespace Vendor
} // namespace Ncp
} // namespace ot
