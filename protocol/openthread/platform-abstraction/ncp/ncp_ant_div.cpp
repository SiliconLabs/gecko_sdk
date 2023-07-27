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
 * @brief This file contains definitions for a spinel extension to support antenna diversity.
 */

#include "ncp_ant_div.hpp"
#include "vendor_spinel.hpp"
#include "radio_extension.h"

#include "common/code_utils.hpp"

namespace AntennaCmd = ot::Vendor::Antenna;

namespace ot {
namespace Ncp {
namespace Vendor {
namespace Antenna {

static otError getTxAntennaMode(Spinel::Encoder &aEncoder);
static otError setTxAntennaMode(Spinel::Decoder &aDecoder);
static otError getRxAntennaMode(Spinel::Encoder &aEncoder);
static otError setRxAntennaMode(Spinel::Decoder &aDecoder);
static otError getActivePhy(Spinel::Encoder &aEncoder);

otError getAntennaProperty(Spinel::Decoder &aDecoder, Spinel::Encoder &aEncoder)
{
    otError error = OT_ERROR_NOT_FOUND;
    uint8_t cmdKey;

    SuccessOrExit(aDecoder.ReadUint8(cmdKey));

    switch(cmdKey)
    {
        case AntennaCmd::ANT_TX_MODE_COMMAND:
            error = getTxAntennaMode(aEncoder);
            break;
        case AntennaCmd::ANT_RX_MODE_COMMAND:
            error = getRxAntennaMode(aEncoder);
            break;
        case AntennaCmd::ANT_ACTIVE_PHY_COMMAND:
            error = getActivePhy(aEncoder);
            break;
    }

exit:
    return error;
}

otError setAntennaProperty(Spinel::Decoder &aDecoder)
{
    otError error = OT_ERROR_NOT_FOUND;
    uint8_t cmdKey;

    SuccessOrExit(aDecoder.ReadUint8(cmdKey));

    switch(cmdKey)
    {
        case AntennaCmd::ANT_TX_MODE_COMMAND:
            error = setTxAntennaMode(aDecoder);
            break;
        case AntennaCmd::ANT_RX_MODE_COMMAND:
            error = setRxAntennaMode(aDecoder);
            break;
    }

exit:
    return error;
}

otError getTxAntennaMode(Spinel::Encoder &aEncoder)
{
    uint8_t mode = 0;

    IgnoreError(otPlatRadioExtensionGetTxAntennaMode(&mode));

    return (aEncoder.WriteUint8(mode));
}

otError setTxAntennaMode(Spinel::Decoder &aDecoder)
{
    uint8_t mode  = 0;
    otError error = OT_ERROR_NONE;

    SuccessOrExit(error = aDecoder.ReadUint8(mode));
    
    error = otPlatRadioExtensionSetTxAntennaMode(mode);

exit:
    return error;
}

otError getRxAntennaMode(Spinel::Encoder &aEncoder)
{
    uint8_t mode = 0;

    IgnoreError(otPlatRadioExtensionGetRxAntennaMode(&mode));

    return (aEncoder.WriteUint8(mode));
}

otError setRxAntennaMode(Spinel::Decoder &aDecoder)
{
    uint8_t mode  = 0;
    otError error = OT_ERROR_NONE;

    SuccessOrExit(error = aDecoder.ReadUint8(mode));
    
    error = otPlatRadioExtensionSetRxAntennaMode(mode);

exit:
    return error;
}

otError getActivePhy(Spinel::Encoder &aEncoder)
{
    uint8_t activePhy = 0;

    IgnoreError(otPlatRadioExtensionGetActivePhy(&activePhy));

    return (aEncoder.WriteUint8(activePhy));
}

} // namespace Antenna
} // namespace Vendor
} // namespace Ncp
} // namespace ot
