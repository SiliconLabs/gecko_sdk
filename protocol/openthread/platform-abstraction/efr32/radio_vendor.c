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

/**
 * @file
 *   This file implements the OpenThread platform abstraction for vendor additions to radio communication.
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "radio_vendor.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifndef SL_CATALOG_OT_SIMULATION_PRESENT

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
#include "coexistence.h"
#include "coexistence-802154.h"
#endif // SL_CATALOG_RAIL_UTIL_COEX_PRESENT

#ifdef SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT
#include "sl_rail_util_ant_div.h"
#endif // SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT

#ifdef SL_CATALOG_RAIL_UTIL_IEEE802154_PHY_SELECT_PRESENT
#include "sl_rail_util_ieee802154_phy_select.h"
#endif // SL_CATALOG_RAIL_UTIL_IEEE802154_PHY_SELECT

#ifdef SL_CATALOG_OPENTHREAD_TEST_CLI_PRESENT
#include "rail_ieee802154.h"
#endif // SL_CATALOG_OPENTHREAD_TEST_CLI_PRESENT

#else // SL_CATALOG_OT_SIMULATION_PRESENT

#include "rail_util_simulation.h"

#endif // SL_CATALOG_OT_SIMULATION_PRESENT

#include "common/code_utils.hpp"

#ifdef SL_CATALOG_OPENTHREAD_ANT_DIV_PRESENT
otError otPlatRadioVendorGetTxAntennaMode(uint8_t *aMode)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT
    VerifyOrExit(aMode != NULL, error = OT_ERROR_INVALID_ARGS);
    *aMode = (uint8_t)sl_rail_util_ant_div_get_tx_antenna_mode();
#else
    OT_UNUSED_VARIABLE(aMode);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

otError otPlatRadioVendorSetTxAntennaMode(uint8_t aMode)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT
    sl_status_t status = sl_rail_util_ant_div_set_tx_antenna_mode(aMode);
    VerifyOrExit(status == SL_STATUS_OK, error = OT_ERROR_FAILED);
#else
    OT_UNUSED_VARIABLE(aMode);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

otError otPlatRadioVendorGetRxAntennaMode(uint8_t *aMode)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT
    VerifyOrExit(aMode != NULL, error = OT_ERROR_INVALID_ARGS);
    *aMode = (uint8_t)sl_rail_util_ant_div_get_rx_antenna_mode();
#else
    OT_UNUSED_VARIABLE(aMode);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

otError otPlatRadioVendorSetRxAntennaMode(uint8_t aMode)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT
    sl_status_t status = sl_rail_util_ant_div_set_rx_antenna_mode(aMode);
    VerifyOrExit(status == SL_STATUS_OK, error = OT_ERROR_FAILED);
#else
    OT_UNUSED_VARIABLE(aMode);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

otError otPlatRadioVendorGetActivePhy(uint8_t *aActivePhy)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT
    VerifyOrExit(aActivePhy != NULL, error = OT_ERROR_INVALID_ARGS);
    *aActivePhy = (uint8_t)sl_rail_util_ieee802154_get_active_radio_config();
#else
    OT_UNUSED_VARIABLE(aActivePhy);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}
#endif // SL_CATALOG_OPENTHREAD_ANT_DIV_PRESENT

#ifdef SL_CATALOG_OPENTHREAD_COEX_PRESENT

otError otPlatRadioVendorGetDpState(uint8_t *aDpPulse)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    VerifyOrExit(aDpPulse != NULL, error = OT_ERROR_INVALID_ARGS);
    *aDpPulse = (uint8_t)sl_rail_util_coex_get_directional_priority_pulse_width();
#else
    OT_UNUSED_VARIABLE(aDpPulse);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

otError otPlatRadioVendorSetDpState(uint8_t aDpPulse)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    sl_status_t status = sl_rail_util_coex_set_directional_priority_pulse_width(aDpPulse);
    VerifyOrExit(status == SL_STATUS_OK, error = OT_ERROR_FAILED);
#else
    OT_UNUSED_VARIABLE(aDpPulse);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

otError otPlatRadioVendorGetGpioInputOverride(uint8_t aGpioIndex, bool *aEnabled)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    VerifyOrExit((COEX_GpioIndex_t)aGpioIndex < COEX_GPIO_INDEX_COUNT, error = OT_ERROR_INVALID_ARGS);
    VerifyOrExit(aEnabled != NULL, error = OT_ERROR_INVALID_ARGS);
    *aEnabled = sl_rail_util_coex_get_gpio_input_override(aGpioIndex);
#else
    OT_UNUSED_VARIABLE(aGpioIndex);
    OT_UNUSED_VARIABLE(aEnabled);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

otError otPlatRadioVendorSetGpioInputOverride(uint8_t aGpioIndex, bool aEnabled)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    sl_status_t status;
    VerifyOrExit((COEX_GpioIndex_t)aGpioIndex < COEX_GPIO_INDEX_COUNT, error = OT_ERROR_INVALID_ARGS);
    status = sl_rail_util_coex_set_gpio_input_override((COEX_GpioIndex_t)aGpioIndex, aEnabled);
    VerifyOrExit(status == SL_STATUS_OK, error = OT_ERROR_FAILED);
#else
    OT_UNUSED_VARIABLE(aGpioIndex);
    OT_UNUSED_VARIABLE(aEnabled);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

otError otPlatRadioVendorGetActiveRadio(uint8_t *aActivePhy)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    VerifyOrExit(aActivePhy != NULL, error = OT_ERROR_INVALID_ARGS);
    *aActivePhy = (uint8_t)sl_rail_util_ieee802154_get_active_radio_config();
#else
    OT_UNUSED_VARIABLE(aActivePhy);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

otError otPlatRadioVendorGetPhySelectTimeout(uint8_t *aTimeout)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    VerifyOrExit(aTimeout != NULL, error = OT_ERROR_INVALID_ARGS);
    *aTimeout = sl_rail_util_coex_get_phy_select_timeout();
#else
    OT_UNUSED_VARIABLE(aTimeout);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

otError otPlatRadioVendorSetPhySelectTimeout(uint8_t aTimeout)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    sl_status_t status = sl_rail_util_coex_set_phy_select_timeout(aTimeout);
    VerifyOrExit(status == SL_STATUS_OK, error = OT_ERROR_FAILED);
#else
    OT_UNUSED_VARIABLE(aTimeout);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

otError otPlatRadioVendorGetCoexOptions(uint32_t *aPtaOptions)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    VerifyOrExit(aPtaOptions != NULL, error = OT_ERROR_INVALID_ARGS);
    *aPtaOptions = (uint32_t)sl_rail_util_coex_get_options();
#else
    OT_UNUSED_VARIABLE(aPtaOptions);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

otError otPlatRadioVendorSetCoexOptions(uint32_t aPtaOptions)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    sl_status_t status = sl_rail_util_coex_set_options(aPtaOptions);
    VerifyOrExit(status != SL_STATUS_INVALID_PARAMETER, error = OT_ERROR_INVALID_ARGS);
    VerifyOrExit(status == SL_STATUS_OK, error = OT_ERROR_FAILED);
#else
    OT_UNUSED_VARIABLE(aPtaOptions);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

otError otPlatRadioVendorGetCoexConstantOptions(uint32_t *aPtaOptions)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    VerifyOrExit(aPtaOptions != NULL, error = OT_ERROR_INVALID_ARGS);
    *aPtaOptions = (uint32_t)sl_rail_util_coex_get_constant_options();
#else
    OT_UNUSED_VARIABLE(aPtaOptions);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

otError otPlatRadioVendorIsCoexEnabled(bool *aPtaState)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    VerifyOrExit(aPtaState != NULL, error = OT_ERROR_INVALID_ARGS);
    *aPtaState = sl_rail_util_coex_is_enabled();
#else
    OT_UNUSED_VARIABLE(aPtaState);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

otError otPlatRadioVendorSetCoexEnable(bool aPtaState)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    sl_status_t status = sl_rail_util_coex_set_enable(aPtaState);
    VerifyOrExit(status == SL_STATUS_OK, error = OT_ERROR_FAILED);
#else
    OT_UNUSED_VARIABLE(aPtaState);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

otError otPlatRadioVendorGetRequestPwmArgs(uint8_t *aPwmComposite, uint8_t *aPwmPulseDc, uint8_t *aPwmPeriodHalfMs)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    const sl_rail_util_coex_pwm_args_t *p;
    VerifyOrExit(aPwmComposite != NULL, error = OT_ERROR_INVALID_ARGS);
    VerifyOrExit(aPwmPulseDc != NULL, error = OT_ERROR_INVALID_ARGS);
    VerifyOrExit(aPwmPeriodHalfMs != NULL, error = OT_ERROR_INVALID_ARGS);
    p = sl_rail_util_coex_get_request_pwm_args();
    VerifyOrExit(p != NULL, error = OT_ERROR_FAILED);
    *aPwmComposite = p->req;
    *aPwmPulseDc = p->dutyCycle;
    *aPwmPeriodHalfMs = p->periodHalfMs;
#else
    OT_UNUSED_VARIABLE(aPwmComposite);
    OT_UNUSED_VARIABLE(aPwmPulseDc);
    OT_UNUSED_VARIABLE(aPwmPeriodHalfMs);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

otError otPlatRadioVendorSetRequestPwmArgs(uint8_t aPwmComposite, uint8_t aPwmPulseDc, uint8_t aPwmPeriodHalfMs)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    sl_status_t status = sl_rail_util_coex_set_request_pwm(aPwmComposite,
                                                           NULL,
                                                           aPwmPulseDc,
                                                           aPwmPeriodHalfMs);
    VerifyOrExit(status == SL_STATUS_OK, error = OT_ERROR_FAILED);
#else
    OT_UNUSED_VARIABLE(aPwmComposite);
    OT_UNUSED_VARIABLE(aPwmPulseDc);
    OT_UNUSED_VARIABLE(aPwmPeriodHalfMs);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

#if defined(SL_CATALOG_RAIL_UTIL_COEX_PRESENT) && SL_OPENTHREAD_COEX_COUNTER_ENABLE
extern void efr32RadioGetCoexCounters(uint32_t (*aCoexCounters)[SL_RAIL_UTIL_COEX_EVENT_COUNT]);
extern void efr32RadioClearCoexCounters(void);
#endif

otError otPlatRadioVendorClearCoexCounters(void)
{
    otError error = OT_ERROR_NONE;

#if defined(SL_CATALOG_RAIL_UTIL_COEX_PRESENT) && SL_OPENTHREAD_COEX_COUNTER_ENABLE
    efr32RadioClearCoexCounters();
#else
    error = OT_ERROR_NOT_IMPLEMENTED;
#endif

    return error;
}

otError otPlatRadioVendorGetCoexCounters(uint8_t aNumEntries, uint32_t aCoexCounters[])
{
    otError error = OT_ERROR_NONE;

#if defined(SL_CATALOG_RAIL_UTIL_COEX_PRESENT) && SL_OPENTHREAD_COEX_COUNTER_ENABLE
    VerifyOrExit(aNumEntries == OT_PLAT_RADIO_VENDOR_COEX_EVENT_COUNT, error = OT_ERROR_INVALID_ARGS);
    VerifyOrExit(aCoexCounters != NULL, error = OT_ERROR_INVALID_ARGS);
    _Static_assert((uint8_t)OT_PLAT_RADIO_VENDOR_COEX_EVENT_COUNT == (uint8_t)SL_RAIL_UTIL_COEX_EVENT_COUNT);
    efr32RadioGetCoexCounters((uint32_t(*)[SL_RAIL_UTIL_COEX_EVENT_COUNT]) aCoexCounters);
#else
    OT_UNUSED_VARIABLE(aNumEntries);
    OT_UNUSED_VARIABLE(aCoexCounters);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}

otError otPlatRadioVendorSetRadioHoldoff(bool aEnabled)
{
    otError error = OT_ERROR_NONE;

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    sl_status_t status = sl_rail_util_coex_set_radio_holdoff(aEnabled);
    VerifyOrExit(status == SL_STATUS_OK, error = OT_ERROR_FAILED);
#else
    OT_UNUSED_VARIABLE(aEnabled);
    ExitNow(error = OT_ERROR_NOT_IMPLEMENTED);
#endif

exit:
    return error;
}
#endif // SL_CATALOG_OPENTHREAD_COEX_PRESENT

#ifdef SL_CATALOG_OPENTHREAD_TEST_CLI_PRESENT
extern RAIL_IEEE802154_PtiRadioConfig_t efr32GetPtiRadioConfig(void);
extern RAIL_Status_t efr32RadioSetCcaMode(uint8_t aMode);

otError otPlatRadioVendorGetPtiRadioConfig(uint16_t *radioConfig)
{
    otError error = OT_ERROR_NONE;

    VerifyOrExit(radioConfig != NULL, error = OT_ERROR_INVALID_ARGS);
    *radioConfig = (uint16_t)efr32GetPtiRadioConfig();

exit:
    return error;
}

otError otPlatRadioVendorSetCcaMode(uint8_t aMode)
{
    otError error = OT_ERROR_NONE;

    RAIL_Status_t status = efr32RadioSetCcaMode(aMode);
    VerifyOrExit(status != RAIL_STATUS_INVALID_PARAMETER, error = OT_ERROR_INVALID_ARGS);
    VerifyOrExit(status == RAIL_STATUS_NO_ERROR, error = OT_ERROR_FAILED);

exit:
    return error;
}
#endif // SL_CATALOG_OPENTHREAD_TEST_CLI_PRESENT
