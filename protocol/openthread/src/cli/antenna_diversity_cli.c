/***************************************************************************/
/**
 * @file
 * @brief Antenna Diversity CLI support
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

#if SL_OPENTHREAD_ANT_DIV_CLI_ENABLE

#include <openthread/cli.h>
#include "common/code_utils.hpp"
#include "radio_extension.h"
#include "sl_ot_custom_cli.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

static otError helpCommand(void *context, uint8_t argc, char *argv[]);

//-----------------------------------------------------------------------------
// Get TX antenna mode (0-don't switch,1-primary,2-secondary,3-TX antenna diversity)
// Console Command : "antenna get-tx-mode"
// Console Response: "TX antenna mode:<antennaMode>"
static otError getAntennaTxModeCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);
    OT_UNUSED_VARIABLE(argc);
    OT_UNUSED_VARIABLE(argv);

    otError error = OT_ERROR_NONE;
    uint8_t antennaMode;

    SuccessOrExit(error = otPlatRadioExtensionGetTxAntennaMode(&antennaMode));
    otCliOutputFormat("TX antenna mode:%d", antennaMode);
    otCliOutputFormat("\r\n");

exit:
    return error;
}

//-----------------------------------------------------------------------------
// Set TX antenna mode (0-don't switch,1-primary,2-secondary,3-TX antenna diversity)
// Console Command : "antenna set-tx-mode <antennaMode>"
// Console Response: none
static otError setAntennaTxModeCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);

    otError error = OT_ERROR_NONE;
    VerifyOrExit(argc == 1, error = OT_ERROR_INVALID_ARGS);

    uint8_t antennaMode = (uint8_t)strtoul(argv[0], NULL, 10);

    SuccessOrExit(error = otPlatRadioExtensionSetTxAntennaMode(antennaMode));
    otCliOutputFormat("\r\n");

exit:
    return error;
}


//-----------------------------------------------------------------------------
// Get RX antenna mode (0-don't switch,1-primary,2-secondary,3-RX antenna diversity)
// Console Command : "antenna get-rx-mode"
// Console Response: "RX Antenna Mode:<antennaMode>"
static otError getAntennaRxModeCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);
    OT_UNUSED_VARIABLE(argc);
    OT_UNUSED_VARIABLE(argv);

    otError error = OT_ERROR_NONE;
    uint8_t antennaMode;

    SuccessOrExit(error = otPlatRadioExtensionGetRxAntennaMode(&antennaMode));
    otCliOutputFormat("RX antenna mode:%d", antennaMode);
    otCliOutputFormat("\r\n");

exit:
    return error;
}


//-----------------------------------------------------------------------------
// Set RX antenna mode (0-don't switch,1-primary,2-secondary,3-RX antenna diversity)
// Console Command : "antenna set-rx-mode <antennaMode>"
// Console Response: none
static otError setAntennaRxModeCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);
    otError error = OT_ERROR_NONE;
    VerifyOrExit(argc == 1, error = OT_ERROR_INVALID_ARGS);

    uint8_t antennaMode = (uint8_t)strtoul(argv[0], NULL, 10);

    if (otPlatRadioExtensionSetRxAntennaMode(antennaMode) != OT_ERROR_NONE) {
        otCliOutputFormat("Requires switching from standard PHY to diversity PHY. Not supported.");
    }
    otCliOutputFormat("\r\n");

exit:
    return error;
}

//-----------------------------------------------------------------------------
// Get Active Phy (0-Default, 1-Ant Div,2-Coex, 3-Ant Div Coex, 4-Invalid)
// Console Command : "antenna get-active-phy"
// Console Response: "Active Radio PHY:<activePhy>"

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

static otError getActivePhyCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);
    OT_UNUSED_VARIABLE(argc);
    OT_UNUSED_VARIABLE(argv);

    otError error = OT_ERROR_NONE;
    uint8_t activePhy;

    SuccessOrExit(error = otPlatRadioExtensionGetActivePhy(&activePhy));

    if (activePhy >= PHY_COUNT) {
        activePhy = PHY_COUNT;
    }
    otCliOutputFormat("Active Radio PHY:%s", phyNames[activePhy]);
    otCliOutputFormat("\r\n");

exit:
    return error;
}

//-----------------------------------------------------------------------------

static otCliCommand antennaCommands[] = {
    {"help", &helpCommand},
    {"get-tx-mode", &getAntennaTxModeCommand},
    {"set-tx-mode", &setAntennaTxModeCommand},
    {"get-rx-mode", &getAntennaRxModeCommand},
    {"set-rx-mode", &setAntennaRxModeCommand},
    {"get-active-phy", &getActivePhyCommand},
};

otError antennaCommand(void *context, uint8_t argc, char *argv[])
{
    otError error = processCommand(context, argc, argv, OT_ARRAY_LENGTH(antennaCommands), antennaCommands);

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
    printCommands(antennaCommands, OT_ARRAY_LENGTH(antennaCommands));

    return OT_ERROR_NONE;
}
#endif // SL_OPENTHREAD_ANT_DIV_CLI_ENABLE
