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
 * @brief This file contains definitions for functions to interact with the
 *        posix spinel interface to build vendor specific spinel frames.
 */

#ifndef _POSIX_VENDOR_SPINEL_INTERFACE_HPP
#define _POSIX_VENDOR_SPINEL_INTERFACE_HPP

#include <openthread/error.h>
#include <cstdint>

#include "radio_counters.h"

namespace ot {
namespace Spinel {
namespace Vendor {

namespace Antenna {
otError getTxAntennaMode(uint8_t &aMode);
otError setTxAntennaMode(uint8_t aMode);
otError getRxAntennaMode(uint8_t &aMode);
otError setRxAntennaMode(uint8_t aMode);
otError getActivePhy(uint8_t &aActivePhy);
}

namespace Coex {
otError getDpState(uint8_t &dpPulse);
otError setDpState(uint8_t dpPulse);
otError getGpioInputOverride(uint8_t &enabled);
otError setGpioInputOverride(uint8_t gpioIndex, bool enabled);
otError getActiveRadio(uint8_t &activePhy);
otError getPhySelectTimeout(uint8_t &timeout);
otError setPhySelectTimeout(uint8_t timeout);
otError getOptions(uint32_t &ptaOptions);
otError setOptions(uint32_t ptaOptions);
otError getConstantOptions(uint32_t &ptaOptions);
otError isEnabled(bool &ptaState);
otError setEnable(bool ptaState);
otError getRequestPwmArgs(uint8_t &pwmReq, uint8_t &pwmDutyCycle, uint8_t &pwmPeriodHalfMs);
otError setRequestPwmArgs(uint8_t pwmReq, uint8_t pwmDutyCycle, uint8_t pwmPeriodHalfMs);
otError clearCoexCounters();
otError getCoexCounters(uint32_t coexCounters[]);
otError setRadioHoldoff(bool enabled);
}

namespace Test {
otError getPtiRadioConfig(uint16_t &aRadioConfig);
otError setCcaMode(uint8_t aMode);
}

namespace Efr32 {
otError getRadioCounters(efr32RadioCounters &aCounters);
otError clearRadioCounters(void);
}

} // namespace Vendor
} // namespace Spinel
} // namespace ot
#endif // _POSIX_VENDOR_SPINEL_INTERFACE_HPP
