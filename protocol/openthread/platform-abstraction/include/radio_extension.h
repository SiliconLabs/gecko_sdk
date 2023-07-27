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
 * @brief
 *   This file defines the Silicon Labs extension to the openthread
 *   platform radio interface.
 *
 */

#ifndef _RADIO_EXTENSION_H
#define _RADIO_EXTENSION_H

#include <stdint.h>
#include <openthread/error.h>

#include "radio_counters.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup plat-radio
 *
 * @{
 *
 */

/**
 * @defgroup radio-extension Radio Extension
 *
 * @brief
 *   This module includes the Silicon Labs extension to the openthread
 *   platform radio interface.
 *
 * The functions in this modules provide an API that can be called from 
 * SoC or host based openthread applications.
 *
 * @note Many of the functions defined in this module are wrappers on
 * top of the Silicon Labs RAIL API. For additional information on the
 * RAIl API please refer to the `Silicon Labs RAIL API Reference Guide`. 
 * Those functions that are wrappers to RAIL functions include a
 * reference to the underlying RAIL function.
 *
 * @{
 *
 */

/**
 * Get the antenna diversity transmit antenna mode.
 *
 * Requires the `ot_ant_div` component.
 *
 * @sa  RAIL API: **sl_rail_util_ant_div_get_tx_antenna_mode()**
 *
 * @param[out]  aMode  A pointer to the location where the current transmit
 *                     antenna mode will be returned. Antenna modes are
 *                     defined by the RAIL `sl_rail_util_antenna_mode_t`
 *                     enumeration.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully obtained the transmit antenna mode.
 * @retval  OT_ERROR_INVALID_ARGS     The @p aMode parameter is NULL.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Antenna diversity is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionGetTxAntennaMode(uint8_t *aMode);

/**
 * Set the antenna diversity transmit antenna mode.
 *
 * Requires the `ot_ant_div` component.
 *
 * @sa  RAIL API: **sl_rail_util_ant_div_set_tx_antenna_mode()**
 *
 * @param[in]  aMode  The antenna mode to use for transmit. Antenna modes are
 *                    defined by the RAIL `sl_rail_util_antenna_mode_t`
 *                    enumeration.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully set the transmit antenna mode.
 * @retval  OT_ERROR_FAILED           The specified transmit antenna mode is not supported.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Antenna diversity is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionSetTxAntennaMode(uint8_t aMode);

/**
 * Get the antenna diversity receive antenna mode.
 *
 * Requires the `ot_ant_div` component.
 *
 * @sa  RAIL API: **sl_rail_util_ant_div_get_rx_antenna_mode()**
 *
 * @param[out]  aMode  A pointer to the location where the current receive
 *                     antenna mode will be returned. Antenna modes are
 *                     defined by the RAIL `sl_rail_util_antenna_mode_t`
 *                     enumeration.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully obtained the receive antenna mode.
 * @retval  OT_ERROR_INVALID_ARGS     The @p aMode parameter is NULL.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Antenna diversity is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionGetRxAntennaMode(uint8_t *aMode);

/**
 * Set the antenna diversity receive antenna mode.
 *
 * Requires the `ot_ant_div` component.
 *
 * @sa  RAIL API: **sl_rail_util_ant_div_set_rx_antenna_mode()**
 *
 * @param[in]  aMode  The antenna mode to use for receive. Antenna modes are
 *                    defined by the RAIL `sl_rail_util_antenna_mode_t`
 *                    enumeration.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully set the receive antenna mode.
 * @retval  OT_ERROR_FAILED           The specified receive antenna mode is not supported.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Antenna diversity is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionSetRxAntennaMode(uint8_t aMode);

/**
 * Get the antenna diversity active phy state.
 *
 * Requires the `ot_ant_div` component.
 *
 * @sa  RAIL API: **sl_rail_util_ieee802154_get_active_radio_config()**
 *
 * @param[out]  aActivePhy  A pointer to the location where the current phy
 *                          state will be returned. Phy states are defined by
 *                          the RAIL `sl_rail_util_ieee802154_radio_config_t`
 *                          enumeration.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully obtained the phy state.
 * @retval  OT_ERROR_INVALID_ARGS     The @p aActivePhy parameter is NULL.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Antenna diversity is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionGetActivePhy(uint8_t *aActivePhy);

/**
 * Get the coexistence directional priority state and pulse width.
 *
 * Requires the `ot_coex` component.
 *
 * @sa  RAIL API: **sl_rail_util_coex_get_directional_priority_pulse_width()**
 *
 * @param[out]  aDpPulse  A pointer to the location where the current directional
 *                        priority state will be returned. If @p aDpPulse is 0
 *                        then directional priority is disabled.  If @p aDpPulse is
 *                        not 0 then directional priority is enabled and the value
 *                        is the pulse width in microseconds.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully obtained the directional priority.
 * @retval  OT_ERROR_INVALID_ARGS     The @p aDpPulse parameter is NULL.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Coexistence is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionGetDpState(uint8_t *aDpPulse);

/**
 * Set the coexistence directional priority state and pulse width.
 *
 * Requires the `ot_coex` component.
 *
 * @sa  RAIL API: **sl_rail_util_coex_set_directional_priority_pulse_width()**
 *
 * @param[in]  aDpPulse  The directional priority state to set. If @p aDpPulse is 0
 *                       then directional priority will be disabled.  If @p aDpPulse is
 *                       not 0 then directional priority will be enabled and the value
 *                       will be the pulse width to use in microseconds.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully set the directional priority.
 * @retval  OT_ERROR_FAILED           The @p aDpPulse is invalid.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Coexistence is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionSetDpState(uint8_t aDpPulse);

/**
 * Get the override input value of a GPIO.
 *
 * Requires the `ot_coex` component.
 *
 * @sa  RAIL API: **sl_rail_util_coex_get_gpio_input_override()**
 *
 * @param[in]   aGpioIndex  The GPIO index
 *                          - 0x00 = Radio Holdoff GPIO index
 *                          - 0x01 = Request GPIO index
 *                          - 0x02 = Grant GPIO index
 *                          - 0x03 = PHY Select index
 * @param[out]  aEnabled    A pointer to the location where the boolean override input
 *                          value will be returned. A TRUE value indicating the 
 *                          override input value is enabled, FALSE disabled. The return
 *                          is inverted if the selected GPIO is active low.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully obtained the override input value.
 * @retval  OT_ERROR_INVALID_ARGS     The @p aGpioIndex parameter is invalid and/or @p aDpPulse parameter is NULL.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Coexistence is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionGetGpioInputOverride(uint8_t aGpioIndex, bool *aEnabled);

/**
 * Set the override input value of a GPIO.
 *
 * Requires the `ot_coex` component.
 *
 * @sa  RAIL API: **sl_rail_util_coex_set_gpio_input_override()**
 *
 * @param[in]  aGpioIndex  The GPIO index
 *                         - 0x00 = Radio Holdoff GPIO index
 *                         - 0x01 = Request GPIO index
 *                         - 0x02 = Grant GPIO index
 *                         - 0x03 = PHY Select index
 * @param[in]  aEnabled    The boolean override input value. A TRUE value indicating the 
 *                         override input value is enabled, FALSE disabled.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully set the override input value.
 * @retval  OT_ERROR_INVALID_ARGS     The @p aGpioIndex parameter is invalid.
 * @retval  OT_ERROR_FAILED           The override input value of the specified GPIO can not be set.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Coexistence is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionSetGpioInputOverride(uint8_t aGpioIndex, bool aEnabled);

/**
 * Get the coexistence active phy state.
 *
 * Requires the `ot_coex` component.
 *
 * @sa  RAIL API: **sl_rail_util_ieee802154_get_active_radio_config()**
 *
 * @param[out]  aActivePhy  A pointer to the location where the current phy
 *                          state will be returned. Phy states are defined by
 *                          the RAIL `sl_rail_util_ieee802154_radio_config_t`
 *                          enumeration.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully obtained the phy state.
 * @retval  OT_ERROR_INVALID_ARGS     The @p aActivePhy parameter is NULL.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Coexistence is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionGetActiveRadio(uint8_t *aActivePhy);

/**
 * Get the coexistence phy select state and timeout.
 *
 * Requires the `ot_coex` component.
 *
 * @sa  RAIL API: **sl_rail_util_coex_get_phy_select_timeout()**
 *
 * @param[out]  aTimeout  A pointer to the location where the current phy
 *                        select state will be returned. If @p aTimeout is 0
 *                        then phy select is disabled.  If @p aTimeout is
 *                        not 0 then phy select is enabled and the value
 *                        is the timeout in milliseconds.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully obtained the phy select state.
 * @retval  OT_ERROR_INVALID_ARGS     The @p aTimeout parameter is NULL.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Coexistence is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionGetPhySelectTimeout(uint8_t *aTimeout);

/**
 * Set the coexistence phy select state and timeout.
 *
 * Requires the `ot_coex` component.
 *
 * @sa  RAIL API: **sl_rail_util_coex_set_phy_select_timeout()**
 *
 * @param[in]  aTimeout  The phy select state to set. If @p aTimeout is 0
 *                       then phy select will be disabled.  If @p aTimeout is
 *                       not 0 then phy select will be enabled and the value
 *                       will be the timeout to use in milliseconds.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully set the directional priority.
 * @retval  OT_ERROR_FAILED           The @p aTimeout is invalid.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Coexistence is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionSetPhySelectTimeout(uint8_t aTimeout);

/**
 * Get the coexistence bitmask of features.
 *
 * Requires the `ot_coex` component.
 *
 * @sa  RAIL API: **sl_rail_util_coex_get_options()**
 *
 * @param[out]  aPtaOptions  A pointer to the location where the coexistence
 *                           feature bitmask will be returned. The feature 
 *                           bitmask is defined by the set of macros making up
 *                           the RAIL `sl_rail_util_coex_options_t` type.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully obtained the bitmask of features.
 * @retval  OT_ERROR_INVALID_ARGS     The @p aPtaOptions parameter is NULL.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Coexistence is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionGetCoexOptions(uint32_t *aPtaOptions);

/**
 * Set the coexistence bitmask of features.
 *
 * Requires the `ot_coex` component.
 *
 * @sa  RAIL API: **sl_rail_util_coex_set_options()**
 *
 * @param[in]  aPtaOptions  The coexistence feature bitmask to set. The feature 
 *                          bitmask is defined by the set of macros making up
 *                          the RAIL `sl_rail_util_coex_options_t` type.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully set the bitmask of features.
 * @retval  OT_ERROR_INVALID_ARGS     The @p aPtaOptions is invalid.
 * @retval  OT_ERROR_FAILED           The bitmask of features can not be set.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Coexistence is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionSetCoexOptions(uint32_t aPtaOptions);

/**
 * Get the coexistence bitmask of constant PTA features that can not be modified using public APIs.
 *
 * Requires the `ot_coex` component.
 *
 * @sa  RAIL API: **sl_rail_util_coex_get_constant_options()**
 *
 * @param[out]  aPtaOptions  A pointer to the location where the coexistence
 *                           constant PTA feature bitmask will be returned. The feature 
 *                           bitmask is defined by the set of macros making up
 *                           the RAIL `sl_rail_util_coex_options_t` type.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully obtained the bitmask of of constant PTA features.
 * @retval  OT_ERROR_INVALID_ARGS     The @p aPtaOptions parameter is NULL.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Coexistence is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionGetCoexConstantOptions(uint32_t *aPtaOptions);

/**
 * Get the coexistence enabled status.
 *
 * Requires the `ot_coex` component.
 *
 * @sa  RAIL API: **sl_rail_util_coex_is_enabled()**
 *
 * @param[out]  aPtaState  A pointer to the location where the coexistence
 *                         enabled status will be returned.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully obtained the coexistence status.
 * @retval  OT_ERROR_INVALID_ARGS     The @p aPtaState parameter is NULL.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Coexistence is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionIsCoexEnabled(bool *aPtaState);

/**
 * Set the coexistence enabled status.
 *
 * Requires the `ot_coex` component.
 *
 * @sa  RAIL API: **sl_rail_util_coex_set_enable()**
 *
 * @param[in]  aPtaState  The coexistence enabled status.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully set the coexistence status.
 * @retval  OT_ERROR_FAILED           The coexistence status can not be set.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Coexistence is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionSetCoexEnable(bool  aPtaState);

/**
 * Get the coexistence PWM configuration.
 *
 * Requires the `ot_coex` component.
 *
 * @sa  RAIL API: **sl_rail_util_coex_get_request_pwm_args()**
 *
 * @param[out]  aPwmReq           A pointer to the location where the coexistence
 *                                PWM request is returned.  The value is defined 
 *                                as a bitmap using shift values from the RAIL 
 *                                `COEX_Req_t` enumeration.
 * @param[out]  aPwmDutyCycle     A pointer to the location where the coexistence
 *                                PWM duty cycle value is returned. 
 * @param[out]  aPwmPeriodHalfMs  A pointer to the location where the coexistence
 *                                PWM period half MS value is returned.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully obtained the PWM configuration.
 * @retval  OT_ERROR_INVALID_ARGS     One or more of the parameters @p aPwmReq, 
 *                                    @p aPwmDutyCycle, or @p aPwmPeriodHalfMs is NULL.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Coexistence is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionGetRequestPwmArgs(uint8_t *aPwmReq, uint8_t *aPwmDutyCycle, uint8_t *aPwmPeriodHalfMs);

/**
 * Set the coexistence PWM configuration.
 *
 * Requires the `ot_coex` component.
 *
 * @sa  RAIL API: **sl_rail_util_coex_set_request_pwm()**
 *
 * @param[in]  aPwmReq           The coexistence PWM request.  The value is defined 
 *                               as a bitmap using shift values from the RAIL 
 *                               `COEX_Req_t` enumeration.
 * @param[in]  aPwmDutyCycle     The coexistence PWM duty cycle. 
 * @param[in]  aPwmPeriodHalfMs  The coexistencec PWM period half MS.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully set the PWM configuration.
 * @retval  OT_ERROR_FAILED           The coexistence radio PWM configuration can not be set/\.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Coexistence is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionSetRequestPwmArgs(uint8_t aPwmReq, uint8_t aPwmDutyCycle, uint8_t aPwmPeriodHalfMs);

/**
 * Clear the coexistence counters.
 *
 * Requires the `ot_coex` component.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully cleared the coexistence counters.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Coexistence is not implemented or `SL_OPENTHREAD_COEX_COUNTER_ENABLE`
 *                                    is not enabled.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionClearCoexCounters(void);

/**
 * Get the coexistence counters.
 *
 * Requires the `ot_coex` component.
 *
 * @param[in]   aNumEntries    The number of entries in @p aCoexCounters
 *                             array where counters will be returned.
 * @param[out]  aCoexCounters  A pointer to an array where the coexistence
 *                             counters will be returned. See @ref 
 *                             otPlatRadioExtensionCoexEvent_t which defines
 *                             what coexistence counter each array element stores.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully obtained the coexistence counters.
 * @retval  OT_ERROR_INVALID_ARGS     @p aNumEntries is not `OT_PLAT_RADIO_EXTENSION_COEX_EVENT_COUNT`
 *                                    or @p aCoexCounters is NULL.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Coexistence is not implemented or `SL_OPENTHREAD_COEX_COUNTER_ENABLE`
 *                                    is not enabled.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionGetCoexCounters(uint8_t aNumEntries, uint32_t aCoexCounters[]);

/**
 * Set the coexistence radio holdoff status.
 *
 * Requires the `ot_coex` component.
 *
 * @sa  RAIL API: **sl_rail_util_coex_set_radio_holdoff()**
 *
 * @param[in]  aEnabled  The coexistence radio holdoff status.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully set the coexistence radio holdoff status.
 * @retval  OT_ERROR_FAILED           The coexistence radio holdoff status can not be set.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  Coexistence is not implemented.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionSetRadioHoldoff(bool aEnabled);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/**
 * Get the PTI (Packet Trace Information) radio config.
 *
 * Requires the `ot_test_custom_cli` component.
 *
 * @sa  RAIL API: **RAIL_IEEE802154_GetPtiRadioConfig()**
 *
 * @param[out]  aRadioConfig  A pointer to the location where the PTI radio
 *                            config will be returned.  The value is defined
 *                            by the RAIL `RAIL_IEEE802154_PtiRadioConfig_t`
 *                            enumeration.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully obtained the PTI radio config.
 * @retval  OT_ERROR_INVALID_ARGS     The @p aRadioConfig parameter is NULL.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionGetPtiRadioConfig(uint16_t *aRadioConfig);

/**
 * Set the radio CCA mode.
 *
 * Requires the `ot_test_custom_cli` component.
 *
 * @sa  RAIL API: **RAIL_IEEE802154_ConfigCcaMode()**
 *
 * @param[in]  aMode  The CCA mode to set. Modes are defined by the RAIL
 *                    `RAIL_IEEE802154_CcaMode_t` enumeration.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully set the CCA mode.
 * @retval  OT_ERROR_FAILED           The @p aTimeout is invalid.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionSetCcaMode(uint8_t aMode);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
/**
 * This enumeration defines the coex event counters and can be used as an
 * index into the `aCoexCounters` table returned in a call to 
 * @ref otPlatRadioExtensionGetCoexCounters.
 *
 */
typedef enum {
  /** Low priority request initiated */
  OT_PLAT_RADIO_EXTENSION_COEX_EVENT_LO_PRI_REQUESTED,
  /** High priority request initiated */
  OT_PLAT_RADIO_EXTENSION_COEX_EVENT_HI_PRI_REQUESTED,
  /** Low priority request denied */
  OT_PLAT_RADIO_EXTENSION_COEX_EVENT_LO_PRI_DENIED,
  /** High priority request denied */
  OT_PLAT_RADIO_EXTENSION_COEX_EVENT_HI_PRI_DENIED,
  /** Low priority transmission aborted mid packet */
  OT_PLAT_RADIO_EXTENSION_COEX_EVENT_LO_PRI_TX_ABORTED,
  /** High priority transmission aborted mid packet */
  OT_PLAT_RADIO_EXTENSION_COEX_EVENT_HI_PRI_TX_ABORTED,
  /** Number of coexistence events */
  OT_PLAT_RADIO_EXTENSION_COEX_EVENT_COUNT,
} otPlatRadioExtensionCoexEvent_t;

/**
 * Get RAIL debug counter values.
 *
 * Requires the `ot_efr32_custom_cli` component.
 *
 * @param[out] *aCounters  Pointer to struct to store counter values.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully obtained radio counter values.
 * @retval  OT_ERROR_INVALID_ARGS     @p aCounters is NULL.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT is not enabled.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionGetRadioCounters(efr32RadioCounters *aCounters);

/**
 * Clear the RAIL debug counters.
 *
 * Requires the `ot_efr32_custom_cli` component.
 *
 * @return Error code indicating success of the function call.
 *
 * @retval  OT_ERROR_NONE             Successfully cleared radio counter values.
 * @retval  OT_ERROR_NOT_IMPLEMENTED  RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT is not enabled.
 * @retval  OT_ERROR_NOT_FOUND        Returned to host applications when the coprocessor
 *                                    is not built with the required component.
 *
 */
otError otPlatRadioExtensionClearRadioCounters(void);

/**
 * @}
 *
 */

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif
#endif // _RADIO_EXTENSION_H
