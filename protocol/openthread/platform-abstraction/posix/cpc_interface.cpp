/*
 *  Copyright (c) 2018, The OpenThread Authors.
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

/**
 * @file
 *   This file includes the implementation for the CPCd interface to radio (RCP).
 */

#include "cpc_interface.hpp"

#include "vendor_interface.hpp"
#include "platform-posix.h"

#include "sl_cpc.h"

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <syslog.h>
#include <termios.h>
#include <unistd.h>

#include "common/code_utils.hpp"
#include "common/logging.hpp"
#include "common/new.hpp"
#include "lib/spinel/spinel.h"

#if OPENTHREAD_POSIX_CONFIG_RCP_BUS == OT_POSIX_RCP_BUS_VENDOR

using ot::Spinel::SpinelInterface;

namespace ot {
namespace Posix {

// ----------------------------------------------------------------------------
// `CpcInterfaceImpl` API
// ----------------------------------------------------------------------------

volatile sig_atomic_t CpcInterfaceImpl::sCpcResetReq = false;
bool CpcInterfaceImpl::sIsCpcInitialized = false;

CpcInterfaceImpl::CpcInterfaceImpl(SpinelInterface::ReceiveFrameCallback aCallback,
                           void *                                aCallbackContext,
                           SpinelInterface::RxFrameBuffer &      aFrameBuffer)
    : mReceiveFrameCallback(aCallback)
    , mReceiveFrameContext(aCallbackContext)
    , mReceiveFrameBuffer(aFrameBuffer)
    , mSockFd(-1)
{
    memset(&mInterfaceMetrics, 0, sizeof(mInterfaceMetrics));
    mInterfaceMetrics.mRcpInterfaceType = OT_POSIX_RCP_BUS_VENDOR;
    mCpcBusSpeed                        = kCpcBusSpeed;
}

otError CpcInterfaceImpl::Init(const Url::Url &aRadioUrl)
{
    otError     error = OT_ERROR_NONE;
    const char *value;
    OT_UNUSED_VARIABLE(aRadioUrl);

    VerifyOrExit(mSockFd == -1, error = OT_ERROR_ALREADY);

    if (!sIsCpcInitialized)
    {
        if (cpc_init(&mHandle, aRadioUrl.GetPath(), false, HandleSecondaryReset) != 0)
        {
            otLogCritPlat("CPC init failed. Ensure radio-url argument has the form 'spinel+cpc://cpcd_0?iid=<1..3>'");
            DieNow(OT_EXIT_FAILURE);
        }

        mSockFd = cpc_open_endpoint(mHandle, &mEndpoint, mId, 1);

        if (mSockFd < 0)
        {
            otLogCritPlat("CPC endpoint open failed");
            error = OT_ERROR_FAILED;
        }
    }
    else
    {
        // Re-initialize the CPC interface.
        SetCpcResetReq(true);
        CheckAndReInitCpc();
    }

    if ((value = aRadioUrl.GetValue("cpc-bus-speed")))
    {
        mCpcBusSpeed = static_cast<uint32_t>(atoi(value));
    }

    otLogCritPlat("mCpcBusSpeed = %d", mCpcBusSpeed);
    sIsCpcInitialized = true;

exit:
    return error;
}

void CpcInterfaceImpl::HandleSecondaryReset(void)
{
    SetCpcResetReq(true);
}

CpcInterfaceImpl::~CpcInterfaceImpl(void)
{
    Deinit();
}

void CpcInterfaceImpl::Deinit(void)
{
    VerifyOrExit(0 == cpc_close_endpoint(&mEndpoint), perror("close cpc endpoint"));

    // Invalidate file descriptor
    mSockFd = -1;

exit:
    return;
}

void CpcInterfaceImpl::Read(uint64_t aTimeoutUs)
{
    uint8_t  buffer[kMaxFrameSize];
    uint8_t *ptr = buffer;
    ssize_t  bytesRead;
    bool     block = false;
    int      ret   = 0;

    if (aTimeoutUs > 0)
    {
        cpc_timeval_t timeout;

        timeout.seconds      = static_cast<int>(aTimeoutUs / US_PER_S);
        timeout.microseconds = static_cast<int>(aTimeoutUs % US_PER_S);

        block = true;
        ret   = cpc_set_endpoint_option(mEndpoint, CPC_OPTION_BLOCKING, &block, sizeof(block));
        OT_ASSERT(ret == 0);
        ret = cpc_set_endpoint_option(mEndpoint, CPC_OPTION_RX_TIMEOUT, &timeout, sizeof(timeout));
        OT_ASSERT(ret == 0);
    }
    else
    {
        ret = cpc_set_endpoint_option(mEndpoint, CPC_OPTION_BLOCKING, &block, sizeof(block));
        OT_ASSERT(ret == 0);
    }
    bytesRead = cpc_read_endpoint(mEndpoint, buffer, sizeof(buffer), CPC_ENDPOINT_READ_FLAG_NONE);

    if (bytesRead > 0)
    {
        // Unpack concatenated spinel frames (see ncp_cpc.cpp)
        while (bytesRead > 0)
        {
            if (bytesRead < 2)
            {
                break;
            }
            uint16_t bufferLen = Encoding::BigEndian::ReadUint16(ptr);
            ptr += 2;
            bytesRead -= 2;
            if (bytesRead < bufferLen)
            {
                break;
            }
            for (uint16_t i = 0; i < bufferLen; i++)
            {
                if (!mReceiveFrameBuffer.CanWrite(1) || (mReceiveFrameBuffer.WriteByte(*(ptr++)) != OT_ERROR_NONE))                  
                {
                    mReceiveFrameBuffer.DiscardFrame();    
                    return;
                }
            }
            bytesRead -= bufferLen;
            mReceiveFrameCallback(mReceiveFrameContext);
        }
    }
    else if (bytesRead == -ECONNRESET)
    {
        SetCpcResetReq(true);
    }
    else if ((bytesRead != -EAGAIN) && (bytesRead != -EINTR))
    {
        DieNow(OT_EXIT_ERROR_ERRNO);
    }
}

otError CpcInterfaceImpl::SendFrame(const uint8_t *aFrame, uint16_t aLength)
{
    otError error;

    CheckAndReInitCpc();
    error = Write(aFrame, aLength);
    return error;
}

otError CpcInterfaceImpl::Write(const uint8_t *aFrame, uint16_t aLength)
{
    otError error = OT_ERROR_NONE;

    // We are catching the SPINEL reset command and returning
    // a SPINEL reset response immediately
    if (IsSpinelResetCommand(aFrame, aLength))
    {
        SendResetResponse();
        return error;
    }

    while (aLength)
    {
        ssize_t bytesWritten = cpc_write_endpoint(mEndpoint, aFrame, aLength, CPC_ENDPOINT_WRITE_FLAG_NON_BLOCKING);

        if (bytesWritten == aLength)
        {
            break;
        }
        else if (bytesWritten > 0)
        {
            aLength -= static_cast<uint16_t>(bytesWritten);
            aFrame += static_cast<uint16_t>(bytesWritten);
        }
        else if (bytesWritten < 0)
        {
            VerifyOrExit((bytesWritten == -EPIPE), SetCpcResetReq(true));
            VerifyOrDie((bytesWritten == -EAGAIN) || (bytesWritten == -EWOULDBLOCK) || (bytesWritten == -EINTR),
                        OT_EXIT_ERROR_ERRNO);
        }
    }

exit:
    return error;
}

otError CpcInterfaceImpl::WaitForFrame(uint64_t aTimeoutUs)
{
    otError error = OT_ERROR_NONE;

    CheckAndReInitCpc();
    Read(aTimeoutUs);

    return error;
}

void CpcInterfaceImpl::UpdateFdSet(void *aMainloopContext)
{
    otSysMainloopContext *context = reinterpret_cast<otSysMainloopContext *>(aMainloopContext);
    OT_ASSERT(context != nullptr);

    FD_SET(mSockFd, &context->mReadFdSet);

    if (context->mMaxFd < mSockFd)
    {
        context->mMaxFd = mSockFd;
    }
}

void CpcInterfaceImpl::Process(const void *aMainloopContext)
{
    OT_UNUSED_VARIABLE(aMainloopContext);
    CheckAndReInitCpc();
    Read(0);
}

void CpcInterfaceImpl::CheckAndReInitCpc(void)
{
    int result;
    int attempts;

    // Check if CPC needs to be restarted
    VerifyOrExit(sCpcResetReq);

    // Clear the flag
    SetCpcResetReq(false);

    // Check if the endpoint was previously opened
    if (mSockFd > 0)
    {
      // Close endpoint
      result = cpc_close_endpoint(&mEndpoint);
      // If the close failed, exit
      VerifyOrDie(result == 0, OT_EXIT_ERROR_ERRNO);
      // Invalidate file descriptor
      mSockFd = -1;
    }

    // Restart communication with cpcd
    attempts = 0;
    do
    {
        // Add some delay before attempting to restart
        usleep(kMaxSleepDuration);
        // Try to restart CPC
        result = cpc_restart(&mHandle);
        // Mark how many times the restart was attempted
        attempts++;
        // Continue to try and restore CPC communication until we
        // have exhausted the retries or restart was successful
    } while ((result != 0) && (attempts < kMaxRestartAttempts));

    // If the restart failed, exit
    VerifyOrDie(result == 0, OT_EXIT_ERROR_ERRNO);

    // Reopen the endpoint
    attempts = 0;
    do
    {
        // Add some delay before attempting to open the endpoint
        usleep(kMaxSleepDuration);
        // Try to open the endpoint
        mSockFd = cpc_open_endpoint(mHandle, &mEndpoint, mId, 1);
        // Mark how many times the open was attempted
        attempts++;
        // Continue to try and open the endpoint until we
        // have exhausted the retries or open was successful
    } while ((mSockFd <= 0) && (attempts < kMaxRestartAttempts));

    // If the open failed, exit
    VerifyOrDie(mSockFd > 0, OT_EXIT_ERROR_ERRNO);

    otLogCritPlat("Restarted CPC successfully");

exit:
    return;
}

void CpcInterfaceImpl::SendResetResponse(void)
{
    // Put CPC Reset call here

    for (int i = 0; i < kResetCMDSize; ++i)
    {
        if (mReceiveFrameBuffer.CanWrite(sizeof(uint8_t)))
        {
            IgnoreError(mReceiveFrameBuffer.WriteByte(mResetResponse[i]));
        }
    }

    mReceiveFrameCallback(mReceiveFrameContext);
}

// ----------------------------------------------------------------------------
// `VendorInterface` API
// ----------------------------------------------------------------------------

static OT_DEFINE_ALIGNED_VAR(sCpcInterfaceImplRaw, sizeof(CpcInterfaceImpl), uint64_t);

VendorInterface::VendorInterface(SpinelInterface::ReceiveFrameCallback aCallback,
                           void *                                aCallbackContext,
                           SpinelInterface::RxFrameBuffer &      aFrameBuffer)
{
    new (&sCpcInterfaceImplRaw) CpcInterfaceImpl(aCallback, aCallbackContext, aFrameBuffer);
}

otError VendorInterface::Init(const Url::Url &aRadioUrl)
{
    return reinterpret_cast<CpcInterfaceImpl*>(&sCpcInterfaceImplRaw)->Init(aRadioUrl);
}

uint32_t VendorInterface::GetBusSpeed(void) const
{
    return reinterpret_cast<CpcInterfaceImpl*>(&sCpcInterfaceImplRaw)->GetBusSpeed();
}

VendorInterface::~VendorInterface(void)
{
    reinterpret_cast<CpcInterfaceImpl*>(&sCpcInterfaceImplRaw)->Deinit();
}

void VendorInterface::Deinit(void)
{
    reinterpret_cast<CpcInterfaceImpl*>(&sCpcInterfaceImplRaw)->Deinit();
}

otError VendorInterface::SendFrame(const uint8_t *aFrame, uint16_t aLength)
{
    return reinterpret_cast<CpcInterfaceImpl*>(&sCpcInterfaceImplRaw)->SendFrame(aFrame, aLength);
}

otError VendorInterface::WaitForFrame(uint64_t aTimeoutUs)
{
    return reinterpret_cast<CpcInterfaceImpl*>(&sCpcInterfaceImplRaw)->WaitForFrame(aTimeoutUs);
}

void VendorInterface::UpdateFdSet(void *aMainloopContext)
{
    reinterpret_cast<CpcInterfaceImpl*>(&sCpcInterfaceImplRaw)->UpdateFdSet(aMainloopContext);
}

void VendorInterface::Process(const void *aMainloopContext)
{
    reinterpret_cast<CpcInterfaceImpl*>(&sCpcInterfaceImplRaw)->Process(aMainloopContext);
}

otError VendorInterface::HardwareReset(void)
{
    return reinterpret_cast<CpcInterfaceImpl*>(&sCpcInterfaceImplRaw)->HardwareReset();
}

const otRcpInterfaceMetrics *VendorInterface::GetRcpInterfaceMetrics(void) const
{
    return reinterpret_cast<CpcInterfaceImpl*>(&sCpcInterfaceImplRaw)->GetRcpInterfaceMetrics();
}

} // namespace Posix
} // namespace ot
#endif // OPENTHREAD_POSIX_CONFIG_RCP_BUS == OT_POSIX_RCP_BUS_VENDOR
