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
 * @brief This file contains definitions for a spinel extension to support efr32/platform commands.
 */

#include "ncp_efr32.hpp"
#include "vendor_spinel.hpp"
#include "radio_extension.h"
#include "radio_counters.h"

#include "common/code_utils.hpp"

namespace Efr32Cmd = ot::Vendor::Efr32;

namespace ot {
namespace Ncp {
namespace Vendor {
namespace Efr32 {

static otError getRadioCounters(Spinel::Encoder &aEncoder);
static otError clearRadioCounters(void);

otError getEfr32Property(Spinel::Decoder &aDecoder, Spinel::Encoder &aEncoder)
{
    otError error = OT_ERROR_NOT_FOUND;
    uint8_t cmdKey;

    SuccessOrExit(aDecoder.ReadUint8(cmdKey));

    switch(cmdKey)
    {
        case Efr32Cmd::EFR32_RADIO_COUNTERS_COMMAND:
            error = getRadioCounters(aEncoder);
            break;
    }

exit:
    return error;
}

otError setEfr32Property(Spinel::Decoder &aDecoder)
{
    otError error = OT_ERROR_NOT_FOUND;
    uint8_t cmdKey;

    SuccessOrExit(aDecoder.ReadUint8(cmdKey));

    switch(cmdKey)
    {
        case Efr32Cmd::EFR32_RADIO_COUNTERS_COMMAND:
            error = clearRadioCounters();
            break;
    }

exit:
    return error;
}

otError getRadioCounters(Spinel::Encoder &aEncoder)
{
    otError error = OT_ERROR_NONE;
    efr32RadioCounters radioCounters;

    SuccessOrExit(error = otPlatRadioExtensionGetRadioCounters(&radioCounters));
    SuccessOrExit(error = aEncoder.WriteDataWithLen((const uint8_t *)&radioCounters, sizeof(efr32RadioCounters)));
exit:
    return error;
}

otError clearRadioCounters(void)
{
    return otPlatRadioExtensionClearRadioCounters();
}

} // namespace Efr32
} // namespace Vendor
} // namespace Ncp
} // namespace ot

