/***************************************************************************/
/**
 * @file
 * @brief Coexistence CLI support
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 *
 * https://www.silabs.com/about-us/legal/master-software-license-agreement
 *
 * This software is distributed to you in Source Code format and is governed by
 * the sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/


#if SL_OPENTHREAD_COEX_CLI_ENABLE

#include <openthread/cli.h>
#include "common/code_utils.hpp"
#include "radio_extension.h"
#include "sl_ot_custom_cli.h"

static otError helpCommand(void *context, uint8_t argc, char *argv[]);

//------------------------------------------------------------------------------
// Get Directional PRIORITY state from console
// Console Command : "coexistence get-dp-state"
// Console Response: "Directional PRIORITY: <ENABLED|DISABLED>, <pulseWidth>(us)"
static otError getDpStateCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);
    OT_UNUSED_VARIABLE(argc);
    OT_UNUSED_VARIABLE(argv);

    otError error = OT_ERROR_NONE;
    // if Directional PRIORITY compiled in:
    // 1. Enabled = pulse-width!=0, Disabled = pulse-width==0
    // 2. Pulse-width is adjustable in us resolution (1-255)
    uint8_t dpPulse = 0U;
    SuccessOrExit(error = otPlatRadioExtensionGetDpState(&dpPulse));
    otCliOutputFormat("Directional PRIORITY: %s, %u (us)",
                      (dpPulse > 0u) ? "ENABLED" : "DISABLED",
                      dpPulse);
    otCliOutputFormat("\r\n");

exit:
    return error;
}

//------------------------------------------------------------------------------
// Set Directional PRIORITY state from console
// Console Command : "coexistence set-dp-state <pulseWidth>"
// Console Response: none
static otError setDpStateCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);

    otError error = OT_ERROR_NONE;
    VerifyOrExit(argc == 1, error = OT_ERROR_INVALID_ARGS);
    // if Directional PRIORITY compiled in:
    // 1. Enabled = pulse-width!=0, Disabled = pulse-width==0
    // 2. Pulse-width is adjustable in us resolution (1-255)
    uint8_t dpPulse = (uint8_t)strtoul(argv[0], NULL, 10);
    SuccessOrExit(error = otPlatRadioExtensionSetDpState(dpPulse));
    otCliOutputFormat("\r\n");

exit:
    return error;
}

//------------------------------------------------------------------------------
// Get GPIO Input override from console
// Console Command : "coexistence get-gpio-input <gpioIndex>"
// Console Response: "<GPIO NAME> GPIO: <ENABLED|DISABLED>"

static const char * const gpioNames[] = {
  "COEX_GPIO_INDEX_RHO",
  "COEX_GPIO_INDEX_REQ",
  "COEX_GPIO_INDEX_GNT",
  "COEX_GPIO_INDEX_PHY_SELECT"
};

static otError getGpioInputOverrideCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);

    otError error = OT_ERROR_NONE;
    VerifyOrExit(argc == 1, error = OT_ERROR_INVALID_ARGS);
    uint8_t gpioIndex = (uint8_t)strtoul(argv[0], NULL, 10);
    if (gpioIndex >= (sizeof(gpioNames)/sizeof(gpioNames[0]))) {
        otCliOutputFormat("GPIO index is out of range.\r\n");
        ExitNow(error = OT_ERROR_INVALID_ARGS);
    }
    bool enabled;
    SuccessOrExit(error = otPlatRadioExtensionGetGpioInputOverride(gpioIndex, &enabled));
    otCliOutputFormat("%s GPIO: %s", gpioNames[gpioIndex], enabled ? "ENABLED" : "DISABLED");
    otCliOutputFormat("\r\n");

exit:
    return error;
}

//------------------------------------------------------------------------------
// Set GPIO Input override from console
// Console Command : "coexistence set-gpio-input <gpioIndex>"
// Console Response: none
static otError setGpioInputOverrideCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);

    otError error = OT_ERROR_NONE;
    VerifyOrExit(argc == 2, error = OT_ERROR_INVALID_ARGS);
    uint8_t gpioIndex = (uint8_t)strtoul(argv[0], NULL, 10);
    bool enabled = (bool)strtoul(argv[1], NULL, 10);
    if (gpioIndex >= (sizeof(gpioNames)/sizeof(gpioNames[0]))) {
        otCliOutputFormat("GPIO index is out of range.\r\n");
        ExitNow(error = OT_ERROR_INVALID_ARGS);
    }
    SuccessOrExit(error = otPlatRadioExtensionSetGpioInputOverride(gpioIndex, enabled));
    otCliOutputFormat("\r\n");

exit:
    return error;
}

//------------------------------------------------------------------------------
// Get PHY select state from console
// Console Command : "coexistence get-phy-state"
// Console Response: "Active Radio PHY:<activePhy>
//                    PHY Select: <ENABLED|DISABLED>, <timeout> (ms)"

static const char * const phyNames[] = {
  "RADIO_CONFIG_154_2P4_DEFAULT",
  "RADIO_CONFIG_154_2P4_ANTDIV",
  "RADIO_CONFIG_154_2P4_COEX",
  "RADIO_CONFIG_154_2P4_ANTDIV_COEX",
  "RADIO_CONFIG_154_2P4_FEM",
  "RADIO_CONFIG_154_2P4_ANTDIV_FEM",
  "RADIO_CONFIG_154_2P4_COEX_FEM",
  "RADIO_CONFIG_154_2P4_ANTDIV_COEX_FEM",
  "INVALID_PHY_SELECTION",
};

#define PHY_COUNT ((sizeof(phyNames) / sizeof(phyNames[0])) - 1)

static otError getPhyStateCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);
    OT_UNUSED_VARIABLE(argc);
    OT_UNUSED_VARIABLE(argv);

    otError error = OT_ERROR_NONE;
    uint8_t activePhy;
    uint8_t timeout;

    SuccessOrExit(error = otPlatRadioExtensionGetActiveRadio(&activePhy));
    if (activePhy >= PHY_COUNT) {
        activePhy = PHY_COUNT;
    }
    otCliOutputFormat("Active Radio PHY:%s", phyNames[activePhy]);
    otCliOutputFormat("\r\n");

    SuccessOrExit(error = otPlatRadioExtensionGetPhySelectTimeout(&timeout));
    otCliOutputFormat("PHY Select: %s, %u (ms)",
                      (timeout > 0u) ? "ENABLED" : "DISABLED",
                      timeout);
    otCliOutputFormat("\r\n");

exit:
    return error;
}

//------------------------------------------------------------------------------
// Set PHY select timeout from console
// Console Command : "coexistence set-phy-state <timeout>"
// Console Response: none
static otError setPhyStateCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);

    otError error = OT_ERROR_NONE;
    VerifyOrExit(argc == 1, error = OT_ERROR_INVALID_ARGS);
    uint8_t timeout = (uint8_t)strtoul(argv[0], NULL, 10);

    // Set PHY select timeout in milliseconds
    // case 1. timeoutMs == 0 -> disable COEX optimized PHY
    // case 2. 0 < timeoutMs < PTA_PHY_SELECT_TIMEOUT_MAX -> disable COEX optimized PHY
    //   if there is no WiFi activity for timeoutMs
    // case 3. timeoutMs == PTA_PHY_SELECT_TIMEOUT_MAX -> enable COEX optimize PHY
    if ((error = otPlatRadioExtensionSetPhySelectTimeout(timeout)) != OT_ERROR_NONE) {
        otCliOutputFormat("Error switching between default and coexistence PHY.");
    }
    otCliOutputFormat("\r\n");

exit:
    return error;
}

//-----------------------------------------------------------------------------
// Get ptaOptions and print hex value to console
// Console Command : "coexistence get-pta-options"
// Console Response: "PTA Configuration Option: 0x<ptaOptions>"

#define PTA_OPTION_FIELDS 16
#define PTA_OPTION_LINE_MAX 80

static const char * const ptaHelp[PTA_OPTION_FIELDS + 1] = {
  "Field                             Bit Position  Size(bits)  Value",
  "RX retry timeout ms              ",
  "Disable ACK if nGRANT||RHO||nREQ ",
  "Abort mid TX if grant is lost    ",
  "TX request is high priority      ",
  "RX request is high priority      ",
  "RX retry request is high priority",
  "RX retry request is enabled      ",
  "Radio holdoff is enabled         ",
  "Reserved                         ",
  "Disable REQ (force holdoff)      ",
  "Synch MAC to GRANT (MAC holdoff) ",
  "REQ/PRI Assert (PreSync/AddrDet) ",
  "CCA/GRANT TX PRI Escalation Thres",
  "Reserved                         ",
  "MAC Fail TX PRI Escalation Thresh",
  "Reserved                         "
};

static const uint8_t ptaBitShift[PTA_OPTION_FIELDS + 1] = { 0, 8, 9, 10, 11, 12, 13,
                                                            14, 15, 16, 17, 18, 20, 23, 25, 27, 32 };
static const uint32_t ptaBitMask[PTA_OPTION_FIELDS] = { 0xFF, 0x1, 0x1, 0x1, 0x1,
                                                        0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x3, 0x7, 0x3, 0x3, 0x1F };

static otError getPtaOptionsCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);
    OT_UNUSED_VARIABLE(argc);
    OT_UNUSED_VARIABLE(argv);

    otError error = OT_ERROR_NONE;
    uint32_t ptaOptions;
    uint8_t i;
    uint32_t value;

    SuccessOrExit(error = otPlatRadioExtensionGetCoexOptions(&ptaOptions));
    otCliOutputFormat("PTA Configuration Option: 0x%04x\r\n", ptaOptions);
    otCliOutputFormat("%s\r\n", ptaHelp[0]);
    for (i = 0; i < PTA_OPTION_FIELDS; i++) {
        value = (ptaOptions >> ptaBitShift[i]) & ptaBitMask[i];
        otCliOutputFormat("%s %02d            %d          %d\r\n",
                          ptaHelp[i + 1],
                          ptaBitShift[i],
                          (ptaBitShift[i + 1] - ptaBitShift[i]),
                          value);
    }
    otCliOutputFormat("\r\n");

exit:
    return error;
}

//-----------------------------------------------------------------------------
// Set ptaOptions from console
// Console Command : "coexistence set-pta-options 0x<ptaOptions>"
// Console Response: none
static otError setPtaOptionsCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);

    otError error = OT_ERROR_NONE;
    VerifyOrExit(argc == 1, error = OT_ERROR_INVALID_ARGS);
    uint32_t ptaOptions = (uint32_t)strtoul(argv[0], NULL, 16);

    if ((error = otPlatRadioExtensionSetCoexOptions(ptaOptions)) == OT_ERROR_INVALID_ARGS)
    {
        uint32_t constant_options;
        uint32_t current_options;
        SuccessOrExit(error = otPlatRadioExtensionGetCoexConstantOptions(&constant_options));
        SuccessOrExit(error = otPlatRadioExtensionGetCoexOptions(&current_options));
        otCliOutputFormat("Error: OT_ERROR_INVALID_ARGS\r\n");
        otCliOutputFormat("Constant options: 0x%08x\r\n", constant_options);
        otCliOutputFormat("Desired  options: 0x%08x\r\n", ptaOptions);
        otCliOutputFormat("Invalid  options: 0x%08x\r\n", ((current_options & constant_options) ^ (ptaOptions & constant_options)));
    }

exit:
    return error;
}

//-----------------------------------------------------------------------------
// Get PTA state (enabled/disabled)
// Console Command : "coexistence get-pta-state"
// Console Response: "PTA is <ENABLED|DISABLED>"
static otError getPtaStateCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);
    OT_UNUSED_VARIABLE(argc);
    OT_UNUSED_VARIABLE(argv);

    otError error = OT_ERROR_NONE;
    bool ptaState;

    SuccessOrExit(error = otPlatRadioExtensionIsCoexEnabled(&ptaState));
    otCliOutputFormat("PTA is %s", (ptaState  ? "ENABLED" : "DISABLED"));
    otCliOutputFormat("\r\n");

exit:
    return error;
}

//-----------------------------------------------------------------------------
// Set PTA state (disabled=0/enabled=1)
// Console Command : "coexistence set-pta-state <0|1>"
// Console Response: none
static otError setPtaStateCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);

    otError error = OT_ERROR_NONE;
    VerifyOrExit(argc == 1, error = OT_ERROR_INVALID_ARGS);
    bool ptaState = (bool)strtoul(argv[0], NULL, 10);

    SuccessOrExit(error = otPlatRadioExtensionSetCoexEnable(ptaState));
    otCliOutputFormat("\r\n");

exit:
    return error;
}

//-----------------------------------------------------------------------------
// Get PWM state from console
// Console Command : "coexistence get-pwm-state"
// Console Response: "PTA PWM (ENABLE|DISABLED): <period> (PERIOD in 0.5ms),
//                             <duty-cycle> (%DC), <0|1> (<LOW|HIGH> PRIORITY)"
static otError getPwmStateCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);
    OT_UNUSED_VARIABLE(argc);
    OT_UNUSED_VARIABLE(argv);

    otError error = OT_ERROR_NONE;
    uint8_t pwmReq;
    uint8_t pwmDutyCycle;
    uint8_t pwmPeriodHalfMs;
    bool pwmPriority;

    SuccessOrExit(error = otPlatRadioExtensionGetRequestPwmArgs(&pwmReq, &pwmDutyCycle, &pwmPeriodHalfMs));

    switch (pwmReq) {
        case 0x00:
            pwmDutyCycle = 0;
            pwmPriority = false;
            break;

        case 0x80:
            pwmPriority = false;
            break;

        case 0x82:
            pwmPriority = true;
            break;

        default:
            otCliOutputFormat("Invalid PWM state variable: %u\n", pwmReq);
            ExitNow(error = OT_ERROR_NONE);
    }

    otCliOutputFormat("PTA PWM (%s): %u (PERIOD in 0.5ms), %u (%%DC), %u (%s PRIORITY)",
                      ((pwmDutyCycle > 0u) ? "ENABLED" : "DISABLED"),
                      pwmPeriodHalfMs,
                      pwmDutyCycle,
                      pwmPriority,
                      (pwmPriority ? "HIGH" : "LOW"));
    otCliOutputFormat("\r\n");

exit:
    return error;
}

//------------------------------------------------------------------------------
// Set PWM state from console
// Console Command : "coexistence set-pta-state <periodHalfms>
//                                              <duty-cycle %> <priority, 0|1>"
// Console Response: none
static otError setPwmStateCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);

    otError error = OT_ERROR_NONE;
    VerifyOrExit(argc == 3, error = OT_ERROR_INVALID_ARGS);

    uint8_t pwmPeriodHalfMs = (uint8_t)strtoul(argv[0], NULL, 10);
    uint8_t pwmDutyCycle = (uint8_t)strtoul(argv[1], NULL, 10);
    uint8_t pwmPriority = (bool)strtoul(argv[2], NULL, 10);
    uint8_t pwmReq = (pwmDutyCycle > 0u) ? (pwmPriority ? 0x82 : 0x80) : 0x00;

    SuccessOrExit(error = otPlatRadioExtensionSetRequestPwmArgs(pwmReq, pwmDutyCycle, pwmPeriodHalfMs));
    otCliOutputFormat("\r\n");

exit:
    return error;
}

//------------------------------------------------------------------------------
// Clear coex counters
// Console Command : "coexistence reset-counters
// Console Response: none
static otError clearCountersCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);
    OT_UNUSED_VARIABLE(argc);
    OT_UNUSED_VARIABLE(argv);

    otError error = OT_ERROR_NONE;

    SuccessOrExit(error = otPlatRadioExtensionClearCoexCounters());
    otCliOutputFormat("coex counters cleared");
    otCliOutputFormat("\r\n");

exit:
    return error;
}

//------------------------------------------------------------------------------
// Print counter results
// Console Command : "coexistence get-counters
// Console Response:
// coexistence get-counters
// COEX Lo Pri Req: <count>
// COEX Hi Pri Req: <count>
// COEX Lo Pri Denied: <count>
// COEX Hi Pri Denied: <count>
// COEX Lo Pri Tx Abrt: <count>
// COEX Hi Pri Tx Abrt: <count>

static otError getCountersCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);
    OT_UNUSED_VARIABLE(argc);
    OT_UNUSED_VARIABLE(argv);

    otError error = OT_ERROR_NONE;
    uint32_t coexCounters[OT_PLAT_RADIO_EXTENSION_COEX_EVENT_COUNT] = {0};
    SuccessOrExit(error = otPlatRadioExtensionGetCoexCounters(OT_PLAT_RADIO_EXTENSION_COEX_EVENT_COUNT, coexCounters));
    otCliOutputFormat("COEX %s: %lu\r\n", "Lo Pri Req",     coexCounters[OT_PLAT_RADIO_EXTENSION_COEX_EVENT_LO_PRI_REQUESTED]);
    otCliOutputFormat("COEX %s: %lu\r\n", "Hi Pri Req",     coexCounters[OT_PLAT_RADIO_EXTENSION_COEX_EVENT_HI_PRI_REQUESTED]);
    otCliOutputFormat("COEX %s: %lu\r\n", "Lo Pri Denied",  coexCounters[OT_PLAT_RADIO_EXTENSION_COEX_EVENT_LO_PRI_DENIED]);
    otCliOutputFormat("COEX %s: %lu\r\n", "Hi Pri Denied",  coexCounters[OT_PLAT_RADIO_EXTENSION_COEX_EVENT_HI_PRI_DENIED]);
    otCliOutputFormat("COEX %s: %lu\r\n", "Lo Pri Tx Abrt", coexCounters[OT_PLAT_RADIO_EXTENSION_COEX_EVENT_LO_PRI_TX_ABORTED]);
    otCliOutputFormat("COEX %s: %lu\r\n", "Hi Pri Tx Abrt", coexCounters[OT_PLAT_RADIO_EXTENSION_COEX_EVENT_HI_PRI_TX_ABORTED]);

exit:
    return error;
}

//------------------------------------------------------------------------------

static otCliCommand coexCommands[] = {
    {"help", &helpCommand},
    {"get-dp-state", &getDpStateCommand},
    {"get-gpio-input", &getGpioInputOverrideCommand},
    {"get-phy-state", &getPhyStateCommand},
    {"get-pta-options", &getPtaOptionsCommand},
    {"get-pta-state", &getPtaStateCommand},
    {"get-pwm-state", &getPwmStateCommand},
    {"set-dp-state", &setDpStateCommand},
    {"set-gpio-input", &setGpioInputOverrideCommand},
    {"set-phy-state", &setPhyStateCommand},
    {"set-pta-options", &setPtaOptionsCommand},
    {"set-pta-state", &setPtaStateCommand},
    {"set-pwm-state", &setPwmStateCommand},
    {"reset-counters", &clearCountersCommand},
    {"get-counters", &getCountersCommand},
};

otError coexCommand(void *context, uint8_t argc, char *argv[])
{
    otError error = processCommand(context, argc, argv, OT_ARRAY_LENGTH(coexCommands), coexCommands);

    if (error == OT_ERROR_INVALID_COMMAND)
    {
        (void) helpCommand(NULL, 0, NULL);
    }

    return error;
}

static otError helpCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);
    OT_UNUSED_VARIABLE(argc);
    OT_UNUSED_VARIABLE(argv);
    printCommands(coexCommands, OT_ARRAY_LENGTH(coexCommands));

    return OT_ERROR_NONE;
}
#endif // SL_OPENTHREAD_COEX_CLI_ENABLE
