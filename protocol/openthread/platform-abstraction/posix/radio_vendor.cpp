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

#include "radio_vendor.h"
#include "posix_vendor_spinel_interface.hpp"

#include "common/code_utils.hpp"

namespace VendorSpinel  = ot::Spinel::Vendor;

/**
 * @file
 *   This file implements the OpenThread platform abstraction for vendor additions to radio communication.
 *
 */

namespace AntennaSpinel = VendorSpinel::Antenna;

otError otPlatRadioVendorGetTxAntennaMode(uint8_t *aMode)
{
    otError error = OT_ERROR_INVALID_ARGS;
    VerifyOrExit(aMode != nullptr);
    error = AntennaSpinel::getTxAntennaMode(*aMode);
exit:
    return error;
}

otError otPlatRadioVendorSetTxAntennaMode(uint8_t aMode)
{
    return AntennaSpinel::setTxAntennaMode(aMode);
}

otError otPlatRadioVendorGetRxAntennaMode(uint8_t *aMode)
{
    otError error = OT_ERROR_INVALID_ARGS;
    VerifyOrExit(aMode != nullptr);
    error = AntennaSpinel::getRxAntennaMode(*aMode);
exit:
    return error;
}

otError otPlatRadioVendorSetRxAntennaMode(uint8_t aMode)
{
    return AntennaSpinel::setRxAntennaMode(aMode);
}

otError otPlatRadioVendorGetActivePhy(uint8_t *aActivePhy)
{
    otError error = OT_ERROR_INVALID_ARGS;
    VerifyOrExit(aActivePhy != nullptr);
    error = AntennaSpinel::getActivePhy(*aActivePhy);
exit:
    return error;
}

namespace CoexSpinel    = VendorSpinel::Coex;

otError otPlatRadioVendorGetDpState(uint8_t *aDpPulse)
{
    otError error = OT_ERROR_INVALID_ARGS;
    VerifyOrExit(aDpPulse != nullptr);
    error = CoexSpinel::getDpState(*aDpPulse);
exit:
    return error;
}

otError otPlatRadioVendorSetDpState(uint8_t aDpPulse)
{
    return CoexSpinel::setDpState(aDpPulse);
}

otError otPlatRadioVendorGetGpioInputOverride(uint8_t aGpioIndex, bool *aEnabled)
{
    otError error = OT_ERROR_INVALID_ARGS;
    uint8_t gpioStates;

    VerifyOrExit(aEnabled != nullptr);
    SuccessOrExit(error = CoexSpinel::getGpioInputOverride(gpioStates));

    *aEnabled = (bool)((gpioStates >> aGpioIndex) & 0x01);
exit:
    return error;
}

otError otPlatRadioVendorSetGpioInputOverride(uint8_t aGpioIndex, bool aEnabled)
{
    return CoexSpinel::setGpioInputOverride(aGpioIndex, aEnabled);
}

otError otPlatRadioVendorGetActiveRadio(uint8_t *aActivePhy)
{
    otError error = OT_ERROR_INVALID_ARGS;
    VerifyOrExit(aActivePhy != nullptr);
    error = CoexSpinel::getActiveRadio(*aActivePhy);
exit:
    return error;
}

otError otPlatRadioVendorGetPhySelectTimeout(uint8_t *aTimeout)
{
    otError error = OT_ERROR_INVALID_ARGS;
    VerifyOrExit(aTimeout != nullptr);
    error = CoexSpinel::getPhySelectTimeout(*aTimeout);
exit:
    return error;
}

otError otPlatRadioVendorSetPhySelectTimeout(uint8_t aTimeout)
{
    return CoexSpinel::setPhySelectTimeout(aTimeout);
}

otError otPlatRadioVendorGetCoexOptions(uint32_t *aPtaOptions)
{
    otError error = OT_ERROR_INVALID_ARGS;
    VerifyOrExit(aPtaOptions != nullptr);
    error = CoexSpinel::getOptions(*aPtaOptions);
exit:
    return error;
}

otError otPlatRadioVendorSetCoexOptions(uint32_t aPtaOptions)
{
    return CoexSpinel::setOptions(aPtaOptions);
}

otError otPlatRadioVendorGetCoexConstantOptions(uint32_t *aPtaOptions)
{
    otError error = OT_ERROR_INVALID_ARGS;
    VerifyOrExit(aPtaOptions != nullptr);
    error = CoexSpinel::getConstantOptions(*aPtaOptions);
exit:
    return error;
}

otError otPlatRadioVendorIsCoexEnabled(bool *aPtaState)
{
    otError error = OT_ERROR_INVALID_ARGS;
    VerifyOrExit(aPtaState != nullptr);
    error = CoexSpinel::isEnabled(*aPtaState);
exit:
    return error;
}

otError otPlatRadioVendorSetCoexEnable(bool aPtaState)
{
    return CoexSpinel::setEnable(aPtaState);
}

otError otPlatRadioVendorGetRequestPwmArgs(uint8_t *aPwmComposite, uint8_t *aPwmPulseDc, uint8_t *aPwmPeriodHalfMs)
{
    otError error = OT_ERROR_INVALID_ARGS;
    VerifyOrExit(aPwmComposite != nullptr && aPwmPulseDc != nullptr && aPwmPeriodHalfMs != nullptr);
    error = CoexSpinel::getRequestPwmArgs(*aPwmComposite, *aPwmPulseDc, *aPwmPeriodHalfMs);
exit:
    return error;
}

otError otPlatRadioVendorSetRequestPwmArgs(uint8_t aPwmComposite, uint8_t aPwmPulseDc, uint8_t aPwmPeriodHalfMs)
{
    return CoexSpinel::setRequestPwmArgs(aPwmComposite, aPwmPulseDc, aPwmPeriodHalfMs);
}

otError otPlatRadioVendorClearCoexCounters(void)
{
    return CoexSpinel::clearCoexCounters();
}

otError otPlatRadioVendorGetCoexCounters(uint8_t aNumEntries, uint32_t aCoexCounters[])
{
    otError error = OT_ERROR_INVALID_ARGS;
    VerifyOrExit(aNumEntries == OT_PLAT_RADIO_VENDOR_COEX_EVENT_COUNT);
    VerifyOrExit(aCoexCounters != nullptr);
    error = CoexSpinel::getCoexCounters(aCoexCounters);
exit:
    return error;
}

otError otPlatRadioVendorSetRadioHoldoff(bool aEnabled)
{
    return CoexSpinel::setRadioHoldoff(aEnabled);
}

namespace TestSpinel = VendorSpinel::Test;

otError otPlatRadioVendorGetPtiRadioConfig(uint16_t *radioConfig)
{
    otError error = OT_ERROR_INVALID_ARGS;
    VerifyOrExit(radioConfig != nullptr);
    error = TestSpinel::getPtiRadioConfig(*radioConfig);
exit:
    return error;
}

otError otPlatRadioVendorSetCcaMode(uint8_t aMode)
{
    return TestSpinel::setCcaMode(aMode);
}
