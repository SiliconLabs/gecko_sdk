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
 * @brief This file contains definitions for an extended NCP spinel interface to the OpenThread stack.
 */

#include "ncp/ncp_base.hpp"
#include "vendor_spinel.hpp"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT
#include "ncp_ant_div.hpp"
#endif // SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
#include "ncp_coex.hpp"
#endif // SL_CATALOG_RAIL_UTIL_COEX_PRESENT

#ifdef SL_CATALOG_OPENTHREAD_TEST_CLI_PRESENT
#include "ncp_test.hpp"
#endif // SL_CATALOG_OPENTHREAD_TEST_CLI_PRESENT

#ifdef SL_CATALOG_OPENTHREAD_EFR32_CLI_PRESENT
#include "ncp_efr32.hpp"
#endif // SL_CATALOG_OPENTHREAD_EFR32_CLI_PRESENT

#if OPENTHREAD_ENABLE_NCP_VENDOR_HOOK

namespace SpinelProp    = ot::Spinel::Vendor;

namespace ot {
namespace Ncp {

// ----------------------------------------------------------------------------
// `NcpBase` Vendor Extension API
// ----------------------------------------------------------------------------

otError NcpBase::VendorCommandHandler(uint8_t aHeader, unsigned int aCommand)
{
    otError error = OT_ERROR_NONE;

    switch (aCommand)
    {
        // TODO: Implement command handlers here.

    default:
        error = PrepareLastStatusResponse(aHeader, SPINEL_STATUS_INVALID_COMMAND);
    }

    return error;
}

void NcpBase::VendorHandleFrameRemovedFromNcpBuffer(Spinel::Buffer::FrameTag aFrameTag)
{
    // This method is a callback which mirrors `NcpBase::HandleFrameRemovedFromNcpBuffer()`.
    // It is called when a spinel frame is sent and removed from NCP buffer.
    //
    // (a) This can be used to track and verify that a vendor spinel frame response is
    //     delivered to the host (tracking the frame using its tag).
    //
    // (b) It indicates that NCP buffer space is now available (since a spinel frame is
    //     removed). This can be used to implement reliability mechanisms to re-send
    //     a failed spinel command response (or an async spinel frame) transmission
    //     (failed earlier due to NCP buffer being full).

    OT_UNUSED_VARIABLE(aFrameTag);
}

otError NcpBase::VendorGetPropertyHandler(spinel_prop_key_t aPropKey)
{
    otError error = OT_ERROR_NONE;

    switch (aPropKey)
    {
        // Get handler should retrieve the property value and then encode and write the
        // value into the NCP buffer. If the "get" operation itself fails, handler should
        // write a `LAST_STATUS` with the error status into the NCP buffer. `OT_ERROR_NO_BUFS`
        // should be returned if NCP buffer is full and response cannot be written.

    #ifdef SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT
    case SpinelProp::SPINEL_PROP_VENDOR_ANTENNA:
        error = Vendor::Antenna::getAntennaProperty(mDecoder, mEncoder);
        break;
    #endif // SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT

    #ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    case SpinelProp::SPINEL_PROP_VENDOR_COEX:
        error = Vendor::Coex::getCoexProperty(mDecoder, mEncoder);
        break;
    #endif // SL_CATALOG_RAIL_UTIL_COEX_PRESENT

    #ifdef SL_CATALOG_OPENTHREAD_TEST_CLI_PRESENT
    case SpinelProp::SPINEL_PROP_VENDOR_TEST:
        error = Vendor::Test::getTestProperty(mDecoder, mEncoder);
        break;
    #endif // SL_CATALOG_OPENTHREAD_TEST_CLI_PRESENT

    #ifdef SL_CATALOG_OPENTHREAD_EFR32_CLI_PRESENT
    case SpinelProp::SPINEL_PROP_VENDOR_EFR32:
        error = Vendor::Efr32::getEfr32Property(mDecoder, mEncoder);
        break;
    #endif // SL_CATALOG_OPENTHREAD_EFR32_CLI_PRESENT
    default:
        error = OT_ERROR_NOT_FOUND;
        break;
    }

    if (error != OT_ERROR_NONE && error != OT_ERROR_NOT_FOUND)
    {
        error = mEncoder.OverwriteWithLastStatusError(ThreadErrorToSpinelStatus(error));
    }

    return error;
}

otError NcpBase::VendorSetPropertyHandler(spinel_prop_key_t aPropKey)
{
    otError error = OT_ERROR_NONE;

    switch (aPropKey)
    {
        // Set handler should first decode the value from the input Spinel frame and then
        // perform the corresponding set operation. The handler should not prepare the
        // spinel response and therefore should not write anything to the NCP buffer.
        // The error returned from handler (other than `OT_ERROR_NOT_FOUND`) indicates the
        // error in either parsing of the input or the error of the set operation. In case
        // of a successful "set", `NcpBase` set command handler will invoke the
        // `VendorGetPropertyHandler()` for the same property key to prepare the response.

    #ifdef SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT
    case SpinelProp::SPINEL_PROP_VENDOR_ANTENNA:
        error = Vendor::Antenna::setAntennaProperty(mDecoder);
        break;
    #endif // SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT

    #ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    case SpinelProp::SPINEL_PROP_VENDOR_COEX:
        error = Vendor::Coex::setCoexProperty(mDecoder);
        break;
    #endif // SL_CATALOG_RAIL_UTIL_COEX_PRESENT

    #ifdef SL_CATALOG_OPENTHREAD_TEST_CLI_PRESENT
    case SpinelProp::SPINEL_PROP_VENDOR_TEST:
        error = Vendor::Test::setTestProperty(mDecoder);
        break;
    #endif // SL_CATALOG_OPENTHREAD_TEST_CLI_PRESENT

    #ifdef SL_CATALOG_OPENTHREAD_EFR32_CLI_PRESENT
    case SpinelProp::SPINEL_PROP_VENDOR_EFR32:
        error = Vendor::Efr32::setEfr32Property(mDecoder);
        break;
    #endif // SL_CATALOG_OPENTHREAD_EFR32_CLI_PRESENT
    default:
        error = OT_ERROR_NOT_FOUND;
        break;
    }

    return error;
}

} // namespace Ncp
} // namespace ot

#endif // OPENTHREAD_ENABLE_NCP_VENDOR_HOOK
