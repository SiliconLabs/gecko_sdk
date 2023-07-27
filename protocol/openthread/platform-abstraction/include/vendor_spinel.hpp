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

#ifndef _NCP_SPINEL_HPP
#define _NCP_SPINEL_HPP

#include "lib/spinel/spinel.h"

namespace ot {
namespace Spinel {
namespace Vendor {

enum
{
    SPINEL_PROP_VENDOR_ANTENNA = (SPINEL_PROP_VENDOR__BEGIN + 0),
    SPINEL_PROP_VENDOR_COEX    = (SPINEL_PROP_VENDOR__BEGIN + 1),
    SPINEL_PROP_VENDOR_TEST    = (SPINEL_PROP_VENDOR__BEGIN + 2),
    SPINEL_PROP_VENDOR_EFR32   = (SPINEL_PROP_VENDOR__BEGIN + 3),
};
} // namespace Vendor
} // namespace Spinel

namespace Vendor {
namespace Antenna {
enum
{
    ANT_TX_MODE_COMMAND,
    ANT_RX_MODE_COMMAND,
    ANT_ACTIVE_PHY_COMMAND,
};

} // namespace Antenna

namespace Coex {
enum
{
    COEX_DP_STATE_COMMAND,
    COEX_GPIO_INPUT_OVERRIDE_COMMAND,
    COEX_ACTIVE_RADIO_COMMAND,
    COEX_PHY_SELECT_TIMEOUT_COMMAND,
    COEX_PTA_OPTIONS_COMMAND,
    COEX_CONSTANT_OPTIONS_COMMAND,
    COEX_PTA_STATE_COMMAND,
    COEX_PWM_STATE_COMMAND,
    COEX_COUNTERS_COMMAND,
    COEX_RADIO_HOLDOFF_COMMAND,
};

} // namespace Coex

namespace Test {
enum
{
    GEN_PTI_RADIO_CONFIG_COMMAND,
    GEN_CCA_MODE_COMMAND,
};

} // namespace Test

namespace Efr32 {
enum
{
    EFR32_RADIO_COUNTERS_COMMAND,
};

} // namespace Efr32
} // namespace Vendor
} // namespace ot
#endif // _NCP_SPINEL_HPP
