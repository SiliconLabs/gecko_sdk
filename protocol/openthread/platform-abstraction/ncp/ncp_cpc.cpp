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
 * @brief This file contains definitions for a CPC based NCP interface to the OpenThread stack.
 */

#include "ncp_cpc.hpp"

#include <stdio.h>

#include <openthread/ncp.h>
#include <openthread/platform/logging.h>
#include <openthread/platform/misc.h>

#include "openthread-core-config.h"
#include "openthread-system.h" // for otSysEventSignalPending()
#include "common/code_utils.hpp"
#include "common/debug.hpp"
#include "common/new.hpp"
#include "instance/instance.hpp"

#if OPENTHREAD_CONFIG_NCP_CPC_ENABLE

namespace ot {
namespace Ncp {

static OT_DEFINE_ALIGNED_VAR(sNcpRaw, sizeof(NcpCPC), uint64_t);

extern "C" void otAppNcpInit(otInstance *aInstance)
{
    NcpCPC *  ncpCPC   = nullptr;
    Instance *instance = static_cast<Instance *>(aInstance);

    ncpCPC = new (&sNcpRaw) NcpCPC(instance);

    if (ncpCPC == nullptr || ncpCPC != NcpBase::GetNcpInstance())
    {
        OT_ASSERT(false);
    }
}

NcpCPC::NcpCPC(Instance *aInstance)
    : NcpBase(aInstance)
    , mIsReady(false)
    , mIsWriting(false)
    , mCpcSendTask(*aInstance, SendToCPC)
    , mCpcEndpointErrorTask(*aInstance, HandleEndpointError)
    , mCpcOpenEndpointTask(*aInstance, HandleOpenEndpoint)
{
}

void NcpCPC::HandleOpenEndpoint(Tasklet &aTasklet)
{
    OT_UNUSED_VARIABLE(aTasklet);
    static_cast<NcpCPC *>(GetNcpInstance())->HandleOpenEndpoint();
}

void NcpCPC::HandleOpenEndpoint(void)
{
    sl_status_t status = sli_cpc_open_service_endpoint(&mUserEp, SL_CPC_ENDPOINT_15_4, 0, 1);

    if (status == SL_STATUS_ALREADY_EXISTS)
    {
        return;
    }
    else if (status == SL_STATUS_BUSY)
    {
        static_cast<NcpCPC *>(GetNcpInstance())->mCpcOpenEndpointTask.Post();
        return;
    }

    OT_ASSERT(status == SL_STATUS_OK);

    status = sl_cpc_set_endpoint_option(&mUserEp, SL_CPC_ENDPOINT_ON_IFRAME_WRITE_COMPLETED,
                                        reinterpret_cast<void *>(HandleCPCSendDone));

    OT_ASSERT(status == SL_STATUS_OK);

    status = sl_cpc_set_endpoint_option(&mUserEp, SL_CPC_ENDPOINT_ON_IFRAME_RECEIVE,
                                        reinterpret_cast<void *>(HandleCPCReceive));

    OT_ASSERT(status == SL_STATUS_OK);

    status = sl_cpc_set_endpoint_option(&mUserEp, SL_CPC_ENDPOINT_ON_ERROR,
                                        reinterpret_cast<void *>(HandleCPCEndpointError));

    OT_ASSERT(status == SL_STATUS_OK);

    mTxFrameBuffer.SetFrameAddedCallback(HandleFrameAddedToNcpBuffer, this);
}

void NcpCPC::HandleFrameAddedToNcpBuffer(void *                   aContext,
                                         Spinel::Buffer::FrameTag aTag,
                                         Spinel::Buffer::Priority aPriority,
                                         Spinel::Buffer *         aBuffer)
{
    OT_UNUSED_VARIABLE(aBuffer);
    OT_UNUSED_VARIABLE(aTag);
    OT_UNUSED_VARIABLE(aPriority);

    static_cast<NcpCPC *>(aContext)->HandleFrameAddedToNcpBuffer();
}

void NcpCPC::HandleFrameAddedToNcpBuffer(void)
{
    if (mIsReady && !mIsWriting)
        mCpcSendTask.Post();
}

void NcpCPC::SendToCPC(Tasklet &aTasklet)
{
    OT_UNUSED_VARIABLE(aTasklet);
    static_cast<NcpCPC *>(GetNcpInstance())->SendToCPC();
}

// may need to be updated to handle sleepy devices. Refer to NcpUart::EncodeAndSendToUart
void NcpCPC::SendToCPC(void)
{
    Spinel::Buffer &txFrameBuffer = mTxFrameBuffer;
    uint16_t        bufferLen;
    uint16_t        offset = 0;

    VerifyOrExit(mIsReady && !mIsWriting && !txFrameBuffer.IsEmpty());

    mIsWriting = true;

    // Concatenate multiple spinel buffers for efficiency over CPC.
    while (!txFrameBuffer.IsEmpty())
    {
        IgnoreError(txFrameBuffer.OutFrameBegin());
        bufferLen = txFrameBuffer.OutFrameGetLength();
        if (offset + sizeof(uint16_t) + bufferLen < kCpcTxBufferSize) {
            Encoding::BigEndian::WriteUint16(bufferLen, mCpcTxBuffer + offset);
            offset += sizeof(uint16_t);
            txFrameBuffer.OutFrameRead(bufferLen, mCpcTxBuffer + offset);
            offset += bufferLen;
            IgnoreError(txFrameBuffer.OutFrameRemove());
        }
        else
        {
          break;
        }
    }

    if (sl_cpc_write(&mUserEp, mCpcTxBuffer, offset, 0, NULL) != SL_STATUS_OK)
    {
        mIsWriting = false;
    }

exit:
    // If the CPCd link isn't ready yet, just remove the frame from
    // the queue so that it doesn't fill up unnecessarily
    if (!mIsReady)
    {
        IgnoreError(txFrameBuffer.OutFrameRemove());
    }

    return;
}

void NcpCPC::HandleCPCSendDone(sl_cpc_user_endpoint_id_t endpoint_id, void *buffer, void *arg, sl_status_t status)
{
    OT_UNUSED_VARIABLE(endpoint_id);
    OT_UNUSED_VARIABLE(buffer);
    OT_UNUSED_VARIABLE(arg);
    OT_UNUSED_VARIABLE(status);

    static_cast<NcpCPC *>(GetNcpInstance())->HandleSendDone();
}

void NcpCPC::HandleSendDone(void)
{
    mIsWriting = false;
    memset(mCpcTxBuffer, 0, sizeof(mCpcTxBuffer));

    if (!mTxFrameBuffer.IsEmpty())
        mCpcSendTask.Post();
}

void NcpCPC::HandleCPCReceive(sl_cpc_user_endpoint_id_t endpoint_id, void *arg)
{
    OT_UNUSED_VARIABLE(endpoint_id);
    OT_UNUSED_VARIABLE(arg);
    otSysEventSignalPending(); // wakeup ot task
}

void NcpCPC::HandleCPCEndpointError(uint8_t endpoint_id, void *arg)
{
    OT_UNUSED_VARIABLE(endpoint_id);
    OT_UNUSED_VARIABLE(arg);

    // Can't close and open endpoints in this context
    static_cast<NcpCPC *>(GetNcpInstance())->mCpcEndpointErrorTask.Post();
}

void NcpCPC::HandleEndpointError(Tasklet &aTasklet)
{
    OT_UNUSED_VARIABLE(aTasklet);
    static_cast<NcpCPC *>(GetNcpInstance())->HandleEndpointError();
}

void NcpCPC::HandleEndpointError(void)
{
    OT_ASSERT(sl_cpc_close_endpoint(&mUserEp) == SL_STATUS_OK);
    mIsReady = false;
}

extern "C" void efr32CpcProcess(void)
{
    NcpCPC *ncpCPC = static_cast<NcpCPC *>(NcpBase::GetNcpInstance());

    if (ncpCPC != nullptr)
    {
        ncpCPC->ProcessCpc();
    }
}

void NcpCPC::ProcessCpc(void)
{
    sl_status_t status;
    void *      data;
    uint16_t    dataLength;

    HandleOpenEndpoint();

    status = sl_cpc_read(&mUserEp, &data, &dataLength, 0,
                         SL_CPC_FLAG_NO_BLOCK); // In bare-metal read is always
                                                // non-blocking, but with rtos
                                                // since this function is called
                                                // in the cpc task, it must not
                                                // block.

    SuccessOrExit(status);

    if (!mIsReady)
    {
        mIsReady = true;
    }

    super_t::HandleReceive(static_cast<uint8_t *>(data), dataLength);

    status = sl_cpc_free_rx_buffer(data);
    OT_ASSERT(status == SL_STATUS_OK);

exit:
    if (mIsReady && !mTxFrameBuffer.IsEmpty())
        mCpcSendTask.Post();
}

} // namespace Ncp
} // namespace ot

#endif // OPENTHREAD_CONFIG_NCP_CPC_ENABLE
