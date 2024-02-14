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
 *   This file implements the OpenThread platform abstraction for the diagnostics.
 *
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>

#include <openthread-core-config.h>
#include <utils/code_utils.h>
#include <openthread/cli.h>
#include <openthread/platform/alarm-milli.h>
#include <openthread/platform/diag.h>
#include <openthread/platform/radio.h>
#include "common/code_utils.hpp"
#include "common/debug.hpp"
#include "common/logging.hpp"

#include "diag.h"
#include "em_gpio.h"
#include "platform-band.h"
#include "platform-efr32.h"
#include "rail_ieee802154.h"

#include "sl_status.h"

#if OPENTHREAD_CONFIG_DIAG_ENABLE

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT
#include "sl_rail_util_ant_div.h"
#endif

#define GPIO_PIN_BITMASK    0xFFFFUL
#define GPIO_PORT_BITMASK   (0xFFFFUL << 16)
#define GET_GPIO_PIN(x)     (x & GPIO_PIN_BITMASK)
#define GET_GPIO_PORT(x)    ((x & GPIO_PORT_BITMASK) >> 16)

// To cache the transmit power, so that we don't override it while loading the
// channel config or setting the channel.
static int8_t sTxPower = OPENTHREAD_CONFIG_DEFAULT_TRANSMIT_POWER;

struct PlatformDiagCommand
{
    const char *mName;
    otError (*mCommand)(otInstance *aInstance, uint8_t aArgsLength, char *aArgs[], char *aOutput, size_t aOutputMaxLen);
};

// Diagnostics mode variables.
static bool sDiagMode = false;

// *****************************************************************************
// Helper functions
// *****************************************************************************
static void appendErrorResult(otError aError, char *aOutput, size_t aOutputMaxLen)
{
    if (aError != OT_ERROR_NONE)
    {
        snprintf(aOutput, aOutputMaxLen, "failed\r\nstatus %#x\r\n", aError);
    }
}

// *****************************************************************************
// CLI functions
// *****************************************************************************
static otError processAddressMatch(otInstance *aInstance,
                                   uint8_t     aArgsLength,
                                   char       *aArgs[],
                                   char       *aOutput,
                                   size_t      aOutputMaxLen)
{
    OT_UNUSED_VARIABLE(aInstance);

    otError error = OT_ERROR_INVALID_ARGS;

    VerifyOrExit(otPlatDiagModeGet(), error = OT_ERROR_INVALID_STATE);
    VerifyOrExit(aArgsLength > 0, error = OT_ERROR_INVALID_ARGS);

    if (strcmp(aArgs[0], "enable") == 0)
    {
        error = otPlatDiagRadioAddressMatch(true);
    }
    else if (strcmp(aArgs[0], "disable") == 0)
    {
        error = otPlatDiagRadioAddressMatch(false);
    }

exit:
    appendErrorResult(error, aOutput, aOutputMaxLen);
    return error;
}

static otError processAutoAck(otInstance *aInstance,
                              uint8_t     aArgsLength,
                              char       *aArgs[],
                              char       *aOutput,
                              size_t      aOutputMaxLen)
{
    OT_UNUSED_VARIABLE(aInstance);

    otError error = OT_ERROR_INVALID_ARGS;

    VerifyOrExit(otPlatDiagModeGet(), error = OT_ERROR_INVALID_STATE);
    VerifyOrExit(aArgsLength > 0, error = OT_ERROR_INVALID_ARGS);

    if (strcmp(aArgs[0], "enable") == 0)
    {
        error = otPlatDiagRadioAutoAck(true);
    }
    else if (strcmp(aArgs[0], "disable") == 0)
    {
        error = otPlatDiagRadioAutoAck(false);
    }

exit:
    appendErrorResult(error, aOutput, aOutputMaxLen);
    return error;
}

// *****************************************************************************
// Add more platform specific diagnostic's CLI features here.
// *****************************************************************************
const struct PlatformDiagCommand sCommands[] = {
    {"addr-match", &processAddressMatch},
    {"auto-ack", &processAutoAck},
};

otError otPlatDiagProcess(otInstance *aInstance,
                          uint8_t     aArgsLength,
                          char       *aArgs[],
                          char       *aOutput,
                          size_t      aOutputMaxLen)
{
    otError error = OT_ERROR_INVALID_COMMAND;
    size_t  i;

    for (i = 0; i < otARRAY_LENGTH(sCommands); i++)
    {
        if (strcmp(aArgs[0], sCommands[i].mName) == 0)
        {
            error = sCommands[i].mCommand(aInstance,
                                          aArgsLength - 1,
                                          aArgsLength > 1 ? &aArgs[1] : NULL,
                                          aOutput,
                                          aOutputMaxLen);
            break;
        }
    }

    return error;
}

// *****************************************************************************
// Implement platform specific diagnostic's APIs.
// *****************************************************************************

void otPlatDiagModeSet(bool aMode)
{
    sDiagMode = aMode;
}

bool otPlatDiagModeGet()
{
    return sDiagMode;
}

static RAIL_Status_t startTxStream(RAIL_StreamMode_t aMode)
{
    uint16_t      txChannel;
    RAIL_Status_t status;

    SuccessOrExit(status = RAIL_GetChannel(gRailHandle, &txChannel));

#ifdef SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT
    RAIL_TxOptions_t txOptions = RAIL_TX_OPTIONS_DEFAULT;
    // Translate Tx antenna diversity mode into RAIL Tx Antenna options:
    // If enabled, use the currently-selected antenna, otherwise leave
    // both options 0 so Tx antenna tracks Rx antenna.
    if (sl_rail_util_ant_div_get_tx_antenna_mode() != SL_RAIL_UTIL_ANTENNA_MODE_DISABLED)
    {
        txOptions |= ((sl_rail_util_ant_div_get_tx_antenna_selected() == SL_RAIL_UTIL_ANTENNA_SELECT_ANTENNA1)
                          ? RAIL_TX_OPTION_ANTENNA0
                          : RAIL_TX_OPTION_ANTENNA1);
    }

    status = RAIL_StartTxStreamAlt(gRailHandle, txChannel, aMode, txOptions);
#else  // !SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT
    status = RAIL_StartTxStream(gRailHandle, txChannel, aMode);
#endif // SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT

exit:
    return status;
}

static RAIL_Status_t stopTxStream(void)
{
    RAIL_Status_t        status;
    uint16_t             currentChannel;
    RAIL_SchedulerInfo_t rxSchedulerInfo = {
        .priority = RADIO_SCHEDULER_BACKGROUND_RX_PRIORITY,
    };

    SuccessOrExit(status = RAIL_StopTxStream(gRailHandle));
    // Since start transmit stream turn off the radio state,
    // call the RAIL_StartRx to turn on radio
    IgnoreError(RAIL_GetChannel(gRailHandle, &currentChannel));

    status = RAIL_StartRx(gRailHandle, currentChannel, &rxSchedulerInfo);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);

exit:
    return status;
}

otError otPlatDiagRadioTransmitCarrier(otInstance *aInstance, bool aEnable)
{
    OT_UNUSED_VARIABLE(aInstance);

    RAIL_Status_t status;

    if (aEnable)
    {
        otLogInfoPlat("Diag CARRIER-WAVE/Tone start");
        status = startTxStream(RAIL_STREAM_CARRIER_WAVE);
    }
    else
    {
        otLogInfoPlat("Diag CARRIER-WAVE/Tone stop");
        status = stopTxStream();
    }
    return (status != RAIL_STATUS_NO_ERROR ? OT_ERROR_FAILED : OT_ERROR_NONE);
}

otError otPlatDiagRadioTransmitStream(otInstance *aInstance, bool aEnable)
{
    OT_UNUSED_VARIABLE(aInstance);

    RAIL_Status_t status;

    if (aEnable)
    {
        otLogInfoPlat("Diag Stream PN9 start");
        status = startTxStream(RAIL_STREAM_PN9_STREAM);
    }
    else
    {
        otLogInfoPlat("Diag Stream stop");
        status = stopTxStream();
    }
    return (status != RAIL_STATUS_NO_ERROR ? OT_ERROR_FAILED : OT_ERROR_NONE);
}

otError otPlatDiagRadioAddressMatch(bool aEnable)
{
    RAIL_Status_t status;

    otLogInfoPlat("Diag address-match %s", aEnable ? "enable" : "disable");

    status = RAIL_IEEE802154_SetPromiscuousMode(gRailHandle, !aEnable);
    return (status != RAIL_STATUS_NO_ERROR ? OT_ERROR_FAILED : OT_ERROR_NONE);
}

otError otPlatDiagRadioAutoAck(bool aAutoAckEnabled)
{
    otLogInfoPlat("Diag auto-ack %s", aAutoAckEnabled ? "enable" : "disable");

    RAIL_PauseRxAutoAck(gRailHandle, !aAutoAckEnabled);

    return OT_ERROR_NONE;
}

void otPlatDiagChannelSet(uint8_t aChannel)
{
    otError       error = OT_ERROR_NONE;
    RAIL_Status_t status;

    RAIL_SchedulerInfo_t bgRxSchedulerInfo = {
    .priority = RADIO_SCHEDULER_BACKGROUND_RX_PRIORITY,
    // sliptime/transaction time is not used for bg rx
    };

    error = efr32RadioLoadChannelConfig(aChannel, sTxPower);
    OT_ASSERT(error == OT_ERROR_NONE);

    status = RAIL_StartRx(gRailHandle, aChannel, &bgRxSchedulerInfo);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
}

void otPlatDiagTxPowerSet(int8_t aTxPower)
{
    RAIL_Status_t status;

    // RAIL_SetTxPowerDbm() takes power in units of deci-dBm (0.1dBm)
    // Multiply by 10 because aPower is supposed be in units dBm
    status = RAIL_SetTxPowerDbm(gRailHandle, ((RAIL_TxPower_t)aTxPower) * 10);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
    sTxPower = aTxPower;
}

void otPlatDiagRadioReceived(otInstance *aInstance, otRadioFrame *aFrame, otError aError)
{
    OT_UNUSED_VARIABLE(aInstance);
    OT_UNUSED_VARIABLE(aFrame);
    OT_UNUSED_VARIABLE(aError);
}

void otPlatDiagAlarmCallback(otInstance *aInstance)
{
    OT_UNUSED_VARIABLE(aInstance);
}

static otError getGpioPortAndPin(uint32_t aGpio, uint16_t *aPort, uint16_t *aPin)
{
    otError error = OT_ERROR_NONE;
    *aPort = GET_GPIO_PORT(aGpio);
    *aPin = GET_GPIO_PIN(aGpio);

    if (*aPort > GPIO_PORT_MAX || *aPin > GPIO_PIN_MAX)
    {
        ExitNow(error = OT_ERROR_INVALID_ARGS);
    }

exit:
    return error;
}

otError otPlatDiagGpioSet(uint32_t aGpio, bool aValue)
{
    otError error;
    uint16_t port;
    uint16_t pin;

    SuccessOrExit(error = getGpioPortAndPin(aGpio, &port, &pin));

    if (aValue)
    {
        GPIO_PinOutSet((GPIO_Port_TypeDef)port, pin);
    }
    else
    {
        GPIO_PinOutClear((GPIO_Port_TypeDef)port, pin);
    }

  exit:
      return error;
}

otError otPlatDiagGpioGet(uint32_t aGpio, bool *aValue)
{
    otError error;
    uint16_t port;
    uint16_t pin;

    SuccessOrExit(error = getGpioPortAndPin(aGpio, &port, &pin));

    *aValue = GPIO_PinInGet((GPIO_Port_TypeDef)port, pin);

exit:
    return error;
}

otError otPlatDiagGpioSetMode(uint32_t aGpio, otGpioMode aMode)
{
    otError error;
    uint16_t port;
    uint16_t pin;
    GPIO_Mode_TypeDef mode;

    SuccessOrExit(error = getGpioPortAndPin(aGpio, &port, &pin));

    mode = (aMode == OT_GPIO_MODE_INPUT) ? gpioModeInput : gpioModePushPull;


    GPIO_PinModeSet((GPIO_Port_TypeDef)port, pin, mode, 0 /*out*/);

exit:
    return error;
}

otError otPlatDiagGpioGetMode(uint32_t aGpio, otGpioMode *aMode)
{
    otError error;
    uint16_t port;
    uint16_t pin;
    GPIO_Mode_TypeDef mode;

    SuccessOrExit(error = getGpioPortAndPin(aGpio, &port, &pin));

    mode = GPIO_PinModeGet((GPIO_Port_TypeDef) port, pin);

    *aMode = (mode == gpioModeInput) ? OT_GPIO_MODE_INPUT : OT_GPIO_MODE_OUTPUT;

exit:
    return error;

}
#endif // OPENTHREAD_CONFIG_DIAG_ENABLE
