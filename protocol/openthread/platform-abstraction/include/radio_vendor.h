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

#ifndef _RADIO_VENDOR_H
#define _RADIO_VENDOR_H

#include <stdint.h>
#include <openthread/error.h>

#ifdef __cplusplus
extern "C" {
#endif

otError otPlatRadioVendorGetTxAntennaMode(uint8_t *aMode);
otError otPlatRadioVendorSetTxAntennaMode(uint8_t aMode);
otError otPlatRadioVendorGetRxAntennaMode(uint8_t *aMode);
otError otPlatRadioVendorSetRxAntennaMode(uint8_t aMode);
otError otPlatRadioVendorGetActivePhy(uint8_t *aActivePhy);

otError otPlatRadioVendorGetDpState(uint8_t *aDpPulse);
otError otPlatRadioVendorSetDpState(uint8_t aDpPulse);
otError otPlatRadioVendorGetGpioInputOverride(uint8_t aGpioIndex, bool *aEnabled);
otError otPlatRadioVendorSetGpioInputOverride(uint8_t aGpioIndex, bool aEnabled);
otError otPlatRadioVendorGetActiveRadio(uint8_t *aRadioConfig);
otError otPlatRadioVendorGetPhySelectTimeout(uint8_t *aTimeout);
otError otPlatRadioVendorSetPhySelectTimeout(uint8_t aTimeout);
otError otPlatRadioVendorGetCoexOptions(uint32_t *aPtaOptions);
otError otPlatRadioVendorSetCoexOptions(uint32_t aPtaOptions);
otError otPlatRadioVendorGetCoexConstantOptions(uint32_t *aPtaOptions);
otError otPlatRadioVendorIsCoexEnabled(bool *aPtaState);
otError otPlatRadioVendorSetCoexEnable(bool  aPtaState);
otError otPlatRadioVendorGetRequestPwmArgs(uint8_t *aPwmComposite, uint8_t *aPwmPulseDc, uint8_t *aPwmPeriodHalfMs);
otError otPlatRadioVendorSetRequestPwmArgs(uint8_t aPwmComposite, uint8_t aPwmPulseDc, uint8_t aPwmPeriodHalfMs);
otError otPlatRadioVendorClearCoexCounters(void);
otError otPlatRadioVendorGetCoexCounters(uint8_t aNumEntries, uint32_t aCoexCounters[]);
otError otPlatRadioVendorSetRadioHoldoff(bool aEnabled);

otError otPlatRadioVendorGetPtiRadioConfig(uint16_t *radioConfig);
otError otPlatRadioVendorSetCcaMode(uint8_t aMode);

typedef enum {
  /** Low priority request initiated */
  OT_PLAT_RADIO_VENDOR_COEX_EVENT_LO_PRI_REQUESTED,
  /** High priority request initiated */
  OT_PLAT_RADIO_VENDOR_COEX_EVENT_HI_PRI_REQUESTED,
  /** Low priority request denied */
  OT_PLAT_RADIO_VENDOR_COEX_EVENT_LO_PRI_DENIED,
  /** High priority request denied */
  OT_PLAT_RADIO_VENDOR_COEX_EVENT_HI_PRI_DENIED,
  /** Low priority transmission aborted mid packet */
  OT_PLAT_RADIO_VENDOR_COEX_EVENT_LO_PRI_TX_ABORTED,
  /** High priority transmission aborted mid packet */
  OT_PLAT_RADIO_VENDOR_COEX_EVENT_HI_PRI_TX_ABORTED,
  /** Number of coexistence events */
  OT_PLAT_RADIO_VENDOR_COEX_EVENT_COUNT,
} otPlatRadioVendorCoexEvent_t;

#ifdef __cplusplus
}
#endif
#endif // _RADIO_VENDOR_H
