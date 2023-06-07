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
 * @brief This file contains initialization routines for non-CPC NCP interfaces
 */

#if !OPENTHREAD_CONFIG_NCP_CPC_ENABLE

#include "openthread-core-config.h"

#include <openthread/ncp.h>

#include "common/code_utils.hpp"
#include "common/new.hpp"

#include "ncp/ncp_config.h"

#if OPENTHREAD_CONFIG_NCP_SPI_ENABLE
#include "ncp_spi.hpp"
#else
#include "ncp_hdlc.hpp"
#include "utils/uart.h"

void otPlatUartReceived(const uint8_t *aBuf, uint16_t aBufLength) { otNcpHdlcReceive(aBuf, aBufLength); }
void otPlatUartSendDone(void) { otNcpHdlcSendDone(); }
#endif

/**
 * otNcpSpiInit and otNcpHdlcInit are not defined when OPENTHREAD_ENABLE_NCP_VENDOR_HOOK
 * is configured. In addition, otAppNcpInit must be implemented when OPENTHREAD_ENABLE_NCP_VENDOR_HOOK
 * is configured.
 */
#if OPENTHREAD_ENABLE_NCP_VENDOR_HOOK

namespace ot {
namespace Ncp {

#if OPENTHREAD_CONFIG_NCP_HDLC_ENABLE
static int NcpSend(const uint8_t *aBuf, uint16_t aBufLength)
{
    IgnoreError(otPlatUartSend(aBuf, aBufLength));
    return aBufLength;
}
#endif

#if OPENTHREAD_CONFIG_NCP_SPI_ENABLE
static OT_DEFINE_ALIGNED_VAR(sNcpRaw, sizeof(NcpSpi), uint64_t);

extern "C" void otNcpSpiInit(otInstance *aInstance)
{
    NcpSpi   *ncpSpi   = nullptr;
    Instance *instance = static_cast<Instance *>(aInstance);

    ncpSpi = new (&sNcpRaw) NcpSpi(instance);

    if (ncpSpi == nullptr || ncpSpi != NcpBase::GetNcpInstance())
    {
        OT_ASSERT(false);
    }
}

#elif OPENTHREAD_CONFIG_NCP_HDLC_ENABLE
static OT_DEFINE_ALIGNED_VAR(sNcpRaw, sizeof(NcpHdlc), uint64_t);

extern "C" void otNcpHdlcInit(otInstance *aInstance, otNcpHdlcSendCallback aSendCallback)
{
    NcpHdlc  *ncpHdlc  = nullptr;
    Instance *instance = static_cast<Instance *>(aInstance);

    ncpHdlc = new (&sNcpRaw) NcpHdlc(instance, aSendCallback);

    if (ncpHdlc == nullptr || ncpHdlc != NcpBase::GetNcpInstance())
    {
        OT_ASSERT(false);
    }
}

#endif // OPENTHREAD_CONFIG_NCP_SPI_ENABLE

extern "C" void otAppNcpInit(otInstance *aInstance)
{

#if OPENTHREAD_CONFIG_NCP_SPI_ENABLE
    otNcpSpiInit(aInstance);
#elif OPENTHREAD_CONFIG_NCP_HDLC_ENABLE
    IgnoreError(otPlatUartEnable());
    otNcpHdlcInit(aInstance, NcpSend);
#endif
}

} // namespace Ncp
} // namespace ot

#endif // OPENTHREAD_ENABLE_NCP_VENDOR_HOOK
#endif // !OPENTHREAD_CONFIG_NCP_CPC_ENABLE
