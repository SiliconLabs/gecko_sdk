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

#ifndef NCP_CPC_HPP_
#define NCP_CPC_HPP_

#include "openthread-core-config.h"

#include "sl_cpc.h"
#include "sli_cpc.h"

#include "ncp/ncp_base.hpp"

#if OPENTHREAD_CONFIG_NCP_CPC_ENABLE
#if (SL_CPC_ENDPOINT_SECURITY_ENABLED >= 1)
#define SL_CPC_APP_DATA_MAX_LENGTH SL_CPC_TX_PAYLOAD_MAX_LENGTH
#else
#define SL_CPC_APP_DATA_MAX_LENGTH SL_CPC_TX_PAYLOAD_MAX_LENGTH_WITH_SECURITY
#endif

static_assert(OPENTHREAD_CONFIG_NCP_CPC_TX_CHUNK_SIZE <= SL_CPC_APP_DATA_MAX_LENGTH, 
              "TX buffer size is too large!");

namespace ot {
namespace Ncp {

class NcpCPC : public NcpBase
{
    typedef NcpBase super_t;

public:
    /**
     * Constructor
     *
     * @param[in]  aInstance  The OpenThread instance structure.
     *
     */
    explicit NcpCPC(Instance *aInstance);

    /**
     * This method is called to transmit and receive data.
     *
     */
    void ProcessCpc(void);

private:
    enum
    {
        kCpcTxBufferSize = OPENTHREAD_CONFIG_NCP_CPC_TX_CHUNK_SIZE
    };

    void HandleFrameAddedToNcpBuffer(void);

    static void HandleFrameAddedToNcpBuffer(void *                   aContext,
                                            Spinel::Buffer::FrameTag aTag,
                                            Spinel::Buffer::Priority aPriority,
                                            Spinel::Buffer *         aBuffer);

    void        SendToCPC(void);
    static void SendToCPC(Tasklet &aTasklet);
    static void HandleCPCSendDone(sl_cpc_user_endpoint_id_t endpoint_id, void *buffer, void *arg, sl_status_t status);
    void        HandleSendDone(void);
    static void HandleCPCReceive(sl_cpc_user_endpoint_id_t endpoint_id, void *arg);
    static void HandleCPCEndpointError(uint8_t endpoint_id, void *arg);
    static void HandleEndpointError(Tasklet &aTasklet);
    void        HandleEndpointError(void);
    static void HandleOpenEndpoint(Tasklet &aTasklet);
    void        HandleOpenEndpoint(void);

    uint8_t                  mCpcTxBuffer[kCpcTxBufferSize];
    bool                     mIsReady;
    bool                     mIsWriting;
    sl_cpc_endpoint_handle_t mUserEp;
    Tasklet                  mCpcSendTask;
    Tasklet                  mCpcEndpointErrorTask;
    Tasklet                  mCpcOpenEndpointTask;
};

} // namespace Ncp
} // namespace ot

#endif // OPENTHREAD_CONFIG_NCP_CPC_ENABLE
#endif // NCP_CPC_HPP_
