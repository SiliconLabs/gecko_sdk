/***************************************************************************/
/**
 * @file
 * @brief Efr32 CLI
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#if SL_OPENTHREAD_EFR32_CLI_ENABLE

#include <openthread/cli.h>
#include <string.h>
#include "common/code_utils.hpp"
#include "radio_extension.h"
#include "sl_ot_custom_cli.h"
#include "radio_counters.h"

#define PRINT_RADIO_COUNTER_FIELD(label, counter) \
    (otCliOutputFormat("  %-s:%*s%12u\r\n", label, (40 - strlen(label)), "", counter));

static otError helpCommand(void *context, uint8_t argc, char *argv[]);

//-----------------------------------------------------------------------------
// List of accepted counter labels
static const char *counterLabels[] = 
{
    "radio",
};

//-----------------------------------------------------------------------------
// Prints radio debug counter values
static otError getRadioCountersCommand(void)
{
    otError error = OT_ERROR_NONE;
    efr32RadioCounters counters;

    SuccessOrExit(error = otPlatRadioExtensionGetRadioCounters(&counters));

    PRINT_RADIO_COUNTER_FIELD("RailPlatTxTriggered",                   counters.mRailPlatTxTriggered);
    PRINT_RADIO_COUNTER_FIELD("RailPlatRadioReceiveDoneCbCount",       counters.mRailPlatRadioReceiveDoneCbCount);
    PRINT_RADIO_COUNTER_FIELD("RailPlatRadioReceiveProcessedCount",    counters.mRailPlatRadioReceiveProcessedCount);
    PRINT_RADIO_COUNTER_FIELD("RailPlatRadioEnergyScanDoneCbCount",    counters.mRailPlatRadioEnergyScanDoneCbCount);
    PRINT_RADIO_COUNTER_FIELD("RailPlatRadioTxDoneCbCount",            counters.mRailPlatRadioTxDoneCbCount);
    PRINT_RADIO_COUNTER_FIELD("RailTxStarted",                         counters.mRailTxStarted);
    PRINT_RADIO_COUNTER_FIELD("RailTxStartFailed",                     counters.mRailTxStartFailed);
    PRINT_RADIO_COUNTER_FIELD("RailEventAcksReceived",                 counters.mRailEventAcksReceived);
    PRINT_RADIO_COUNTER_FIELD("RailEventConfigScheduled",              counters.mRailEventConfigScheduled);
    PRINT_RADIO_COUNTER_FIELD("RailEventConfigUnScheduled",            counters.mRailEventConfigUnScheduled);
    PRINT_RADIO_COUNTER_FIELD("RailEventPacketSent",                   counters.mRailEventPacketSent);
    PRINT_RADIO_COUNTER_FIELD("RailEventChannelBusy",                  counters.mRailEventChannelBusy);
    PRINT_RADIO_COUNTER_FIELD("RailEventEnergyScanCompleted",          counters.mRailEventEnergyScanCompleted);
    PRINT_RADIO_COUNTER_FIELD("RailEventCalNeeded",                    counters.mRailEventCalNeeded);
    PRINT_RADIO_COUNTER_FIELD("RailEventPacketReceived",               counters.mRailEventPacketReceived);
    PRINT_RADIO_COUNTER_FIELD("RailEventNoAck",                        counters.mRailEventNoAck);
    PRINT_RADIO_COUNTER_FIELD("RailEventTxAbort",                      counters.mRailEventTxAbort);
    PRINT_RADIO_COUNTER_FIELD("RailEventSchedulerStatusError",         counters.mRailEventSchedulerStatusError);
    PRINT_RADIO_COUNTER_FIELD("RailEventsSchedulerStatusTransmitBusy", counters.mRailEventsSchedulerStatusTransmitBusy);
    PRINT_RADIO_COUNTER_FIELD("RailEventsSchedulerStatusLastStatus",   counters.mRailEventsSchedulerStatusLastStatus);
    PRINT_RADIO_COUNTER_FIELD("RailEventsEnhAckTxFailed",              counters.mRailEventsEnhAckTxFailed);
    PRINT_RADIO_COUNTER_FIELD("RailEventsScheduledTxTriggeredCount",   counters.mRailEventsScheduledTxTriggeredCount);
    PRINT_RADIO_COUNTER_FIELD("RailEventsScheduledTxStartedCount",     counters.mRailEventsScheduledTxStartedCount);

exit:
    return error;
}

//-----------------------------------------------------------------------------
// Clears radio debug counter values
static otError clearRadioCountersCommand(void)
{
    return otPlatRadioExtensionClearRadioCounters();
}

//-----------------------------------------------------------------------------
// Compares an unvalidated char array argument to string literal
static bool literalMatch(const char *literal, char *arg)
{
    return (strncmp(literal, arg, strlen(literal)) == 0);
}

//-----------------------------------------------------------------------------
// Prints accepted counter labels
// Console Command: "efr32 counters"
// Console Response" "[labels]"
static otError countersHelpCommand(uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(argv);

    otError error = OT_ERROR_INVALID_ARGS;

    if (argc == 0)
    {
        error = OT_ERROR_NONE;
    }

    for (size_t i = 0; i < OT_ARRAY_LENGTH(counterLabels); i++)
    {
        otCliOutputFormat("%s\r\n", counterLabels[i]);
    }

    return error;
}

//-----------------------------------------------------------------------------
// Prints requested counter values
// Console Command: "efr32 counters [label]"
// Console Response: "[counter IDs]: [counter values]"
static otError countersGetCommand(uint8_t argc, char *argv[])
{
    otError error = OT_ERROR_INVALID_ARGS;

    if (literalMatch(counterLabels[0], argv[0]))
    {
        error = getRadioCountersCommand();
    }

    return error;
}

//-----------------------------------------------------------------------------
// Clears requested counter values
// Console Command: "efr32 counters [label] reset"
// Console Response: none
static otError countersClearCommand(uint8_t argc, char *argv[])
{
    otError error = OT_ERROR_INVALID_ARGS;

    if (literalMatch("reset", argv[1]))
    {
        if (literalMatch(counterLabels[0], argv[0]))
        {
            error = clearRadioCountersCommand();
        }
    }

    return error;
}


//-----------------------------------------------------------------------------
// Handles argument count and selects appropriate counter subcommand
static otError countersCommand(void *context, uint8_t argc, char *argv[])
{
    OT_UNUSED_VARIABLE(context);
    otError error = OT_ERROR_NONE;

    switch(argc)
    {
        case 1:
            error = countersGetCommand(argc, argv);
            break;
        case 2:
            error = countersClearCommand(argc, argv); 
            break;
        default:
            error = countersHelpCommand(argc, argv);
    }

    return error;
}

//-----------------------------------------------------------------------------

static otCliCommand efr32Commands[] = {
    {"help", &helpCommand},
    {"counters", &countersCommand},
};

otError efr32Command(void *context, uint8_t argc, char *argv[])
{
    otError error = processCommand(context, argc, argv, OT_ARRAY_LENGTH(efr32Commands), efr32Commands);
    
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
    printCommands(efr32Commands, OT_ARRAY_LENGTH(efr32Commands));

    return OT_ERROR_NONE;
}

#endif // SL_OPENTHREAD_EFR32_CLI_ENABLE
