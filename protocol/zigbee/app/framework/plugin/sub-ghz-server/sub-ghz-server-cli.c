/***************************************************************************//**
 * @file
 * @brief CLI for the Sub-Ghz Server plugin.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include "app/framework/include/af.h"
#include "app/util/serial/sl_zigbee_command_interpreter.h"

#include "stack/include/ember-duty-cycle.h"
#include "sub-ghz-server.h"

//-----------------------------------------------------------------------------
// Forward Declarations
#ifndef UC_BUILD
void emAfSubGhzServerCliChannelChangePrint(void);
void emAfSubGhzServerCliChannelChangeSet(void);
void emAfSubGhzServerCliChannelMaskPrint(void);
void emAfSubGhzServerCliChannelMaskSet(void);
void emAfSubGhzServerCliDutyCycleLimitsPrint(void);
void emAfSubGhzServerCliDutyCycleLimitsSet(void);
void emAfSubGhzServerCliSuspendZclMessages(void);
void emAfSubGhzServerCliClientStatus(void);
EmberCommandEntry emberAfSubGhzServerCommands[] = {
  emberCommandEntryActionWithDetails("channel-change print", emAfSubGhzServerCliChannelChangePrint, "", "Print out the status of the sub-GHz channel change attribute.", NULL),
  emberCommandEntryActionWithDetails("channel-change set", emAfSubGhzServerCliChannelChangeSet, "w", "Set the status of the sub-GHz channel change attribute.", emAfSubGhzServerCliChannelChangeSetArguments),
  emberCommandEntryActionWithDetails("channel-mask print", emAfSubGhzServerCliChannelMaskPrint, "", "Print out the status of all sub-GHz channel masks.", NULL),
  emberCommandEntryActionWithDetails("channel-mask set", emAfSubGhzServerCliChannelMaskSet, "wwww", "Set one or more sub-GHz channel mask(s).", emAfSubGhzServerCliChannelMaskSetArguments),
  emberCommandEntryActionWithDetails("limits print", emAfSubGhzServerCliDutyCycleLimitsPrint, "", "Print the current Duty Cycle limits.", NULL),
  emberCommandEntryActionWithDetails("limits set", emAfSubGhzServerCliDutyCycleLimitsSet, "vvv", "Set the current Duty Cycle limits.", emAfSubGhzServerCliDutyCycleLimitsSetArguments),
  emberCommandEntryActionWithDetails("suspend-zcl-messages", emAfSubGhzServerCliSuspendZclMessages, "vuu", "Send the SuspendZCLMessages command to the given client.", emAfSubGhzServerCliSuspendZclMessagesArguments),
  emberCommandEntryActionWithDetails("client-status", emAfSubGhzServerCliClientStatus, "v", "Print the given Sub-GHZ given client's current status.", emAfSubGhzServerCliClientStatusArguments),
  emberCommandEntryTerminator()
};
#endif

//-----------------------------------------------------------------------------
// Globals Declarations

const char * emAfSubGhzServerCliChannelChangeSetArguments[] = {
  "Channel change attribute (bit mask)",
  NULL
};

const char * emAfSubGhzServerCliChannelMaskSetArguments[] = {
  "Channel 28 mask",
  "Channel 29 mask",
  "Channel 30 mask",
  "Channel 31 mask",
  NULL
};

const char * emAfSubGhzServerCliDutyCycleLimitsSetArguments[] = {
  "'Limited' Duty Cycle state threshold in % * 100 (i.e. 150 = 1.5%, 10000 = 100.00%)",
  "'Critical' Duty Cycle state threshold in % * 100",
  "'Suspended' Duty Cycle state threshold in % * 100",
  NULL
};

const char * emAfSubGhzServerCliSuspendZclMessagesArguments[] = {
  "Node ID of the given client",
  "Endpoint of the given client",
  "Period in minutes",
  NULL
};

const char * emAfSubGhzServerCliClientStatusArguments[] = {
  "Node ID of the given client",
  NULL
};

//-----------------------------------------------------------------------------
// Private functions

/** @brief Print "Success" or "Error"
 *
 * Simples.
 */
static void printSuccessOrError(EmberStatus status)
{
  if (status == EMBER_SUCCESS) {
    emberAfCorePrintln("OK");
  } else {
    emberAfCorePrintln("Error %d (0x%x)", status, status);
  }
}

/** @brief Read and print a set of attributes
 *
 * We are lucky that all the attributes are in the server and they are all the same type.
 * It simplifies the implementation.
 */
static void printAttributes(const uint16_t attributeIds[], int n)
{
  const uint8_t endpoint = emberAfPrimaryEndpointForCurrentNetworkIndex();
  uint32_t      value;
  uint8_t       type;
  int           i;

  for (i = 0; i < n; ++i) {
    const EmberAfStatus status = emberAfReadAttribute(endpoint,
                                                      ZCL_SUB_GHZ_CLUSTER_ID,
                                                      attributeIds[i],
                                                      CLUSTER_MASK_SERVER,
                                                      (uint8_t*)&value,
                                                      sizeof value,
                                                      &type);
    if (status == (EmberAfStatus)EMBER_SUCCESS) {
      emberAfCorePrintln("0x%4x", value);
    } else {
      emberAfCorePrintln("Error reading attribute");
    }
  }
}

/** @brief Write a set of attributes read from the command line
 *
 * All the attributes are in the server and they are all the same type.
 */
#ifndef UC_BUILD
static void setAttributes(const uint16_t attributeIds[], int n)
#else // !UC_BUILD
static void setAttributes(sl_cli_command_arg_t *arguments, const uint16_t attributeIds[], int n)
#endif  // UC_BUILD
{
  const uint8_t endpoint = emberAfPrimaryEndpointForCurrentNetworkIndex();
  uint32_t      value;
  int           i;

  for (i = 0; i < n; ++i) {
    value = emberUnsignedCommandArgument(i);
    const EmberAfStatus status = emberAfWriteAttribute(endpoint,
                                                       ZCL_SUB_GHZ_CLUSTER_ID,
                                                       attributeIds[i],
                                                       CLUSTER_MASK_SERVER,
                                                       (uint8_t*)&value,
                                                       ZCL_BITMAP32_ATTRIBUTE_TYPE);
    if (status != (EmberAfStatus)EMBER_SUCCESS) {
      emberAfCorePrintln("Error writing attribute");
    }
  }
}

/** @brief Print a value supplied in hectopercent (i.e % * 100)
 *
 * For example, 1.5% = 150 hectopercent, 99.99% = 9999 hectopercent.
 */
static void printHectoPercent(EmberDutyCycleHectoPct value)
{
  emberAfCorePrint("%d.%d%d%%", value / 100, (value % 100) / 10, value % 10);
}

//-----------------------------------------------------------------------------
// Public functions

/** @brief A set of definition and fuctions to print/set the Sub-GHz cluster's
 * 'Channel Change' attributes.
 */
static const uint16_t ChannelChangeAttribs[] = {
  ZCL_SUB_GHZ_CLUSTER_CHANNEL_CHANGE_ATTRIBUTE_ID
};

#ifndef UC_BUILD
void emAfSubGhzServerCliChannelChangePrint(void)
#else
void emAfSubGhzServerCliChannelChangePrint(sl_cli_command_arg_t *arguments)
#endif
{
  printAttributes(ChannelChangeAttribs,
                  sizeof ChannelChangeAttribs / sizeof ChannelChangeAttribs[0]);
}
#ifndef UC_BUILD
void emAfSubGhzServerCliChannelChangeSet(void)
#else
void emAfSubGhzServerCliChannelChangeSet(sl_cli_command_arg_t *arguments)
#endif
{
#ifndef UC_BUILD
  setAttributes(ChannelChangeAttribs,
                sizeof ChannelChangeAttribs / sizeof ChannelChangeAttribs[0]);
#else // !UC_BUILD
  setAttributes(arguments, ChannelChangeAttribs,
                sizeof ChannelChangeAttribs / sizeof ChannelChangeAttribs[0]);
#endif  // UC_BUILD
}

/** @brief A set of definition and fuctions to print/set the Sub-GHz cluster's
 * 'Channel Mask' attributes.
 */
static const uint16_t ChannelMaskAttribs[] = {
  ZCL_SUB_GHZ_CLUSTER_PAGE_28_CHANNEL_MASK_ATTRIBUTE_ID,
  ZCL_SUB_GHZ_CLUSTER_PAGE_29_CHANNEL_MASK_ATTRIBUTE_ID,
  ZCL_SUB_GHZ_CLUSTER_PAGE_30_CHANNEL_MASK_ATTRIBUTE_ID,
  ZCL_SUB_GHZ_CLUSTER_PAGE_31_CHANNEL_MASK_ATTRIBUTE_ID
};
#ifndef UC_BUILD
void emAfSubGhzServerCliChannelMaskPrint(void)
#else
void emAfSubGhzServerCliChannelMaskPrint(sl_cli_command_arg_t *arguments)
#endif
{
  printAttributes(ChannelMaskAttribs,
                  sizeof ChannelMaskAttribs / sizeof ChannelMaskAttribs[0]);
}
#ifndef UC_BUILD
void emAfSubGhzServerCliChannelMaskSet(void)
#else
void emAfSubGhzServerCliChannelMaskSet(sl_cli_command_arg_t *arguments)
#endif
{
#ifndef UC_BUILD
  setAttributes(ChannelMaskAttribs,
                sizeof ChannelMaskAttribs / sizeof ChannelMaskAttribs[0]);
#else // !UC_BUILD
  setAttributes(arguments, ChannelMaskAttribs,
                sizeof ChannelMaskAttribs / sizeof ChannelMaskAttribs[0]);
#endif  // UC_BUILD
}

/** @brief Print the current Duty Cycle limits
 */
#ifndef UC_BUILD
void emAfSubGhzServerCliDutyCycleLimitsPrint(void)
#else
void emAfSubGhzServerCliDutyCycleLimitsPrint(sl_cli_command_arg_t *arguments)
#endif
{
  static const char* const dcStateStr[] = {
    "Off",      // EMBER_DUTY_CYCLE_TRACKING_OFF                    = 0,
    "Normal",   // EMBER_DUTY_CYCLE_LBT_NORMAL                      = 1,
    "Limited",  // EMBER_DUTY_CYCLE_LBT_LIMITED_THRESHOLD_REACHED   = 2,
    "Critical", // EMBER_DUTY_CYCLE_LBT_CRITICAL_THRESHOLD_REACHED  = 3,
    "Suspended" // EMBER_DUTY_CYCLE_LBT_SUSPEND_LIMIT_REACHED       = 4,
  };

  EmberDutyCycleLimits limits;
  EmberPerDeviceDutyCycle arrayOfDutyCycles[EMBER_MAX_CHILDREN_FOR_PER_DEVICE_DUTY_CYCLE_MONITOR + 1];
  EmberDutyCycleState dcState;

  if (emberGetDutyCycleLimits(&limits) == EMBER_SUCCESS) {
    emberAfCorePrint("Limited : ");
    printHectoPercent(limits.limitThresh);
    emberAfCorePrintln("");

    emberAfCorePrint("Critical: ");
    printHectoPercent(limits.critThresh);
    emberAfCorePrintln("");

    emberAfCorePrint("Suspend : ");
    printHectoPercent(limits.suspLimit);
    emberAfCorePrintln("");
  } else {
    emberAfCorePrintln("Could not get %p%p%p", "", "duty cycle", " limits");
  }

  if (emberGetCurrentDutyCycle(sizeof arrayOfDutyCycles / sizeof arrayOfDutyCycles[0],
                               arrayOfDutyCycles) == EMBER_SUCCESS) {
    uint8_t i;

    emberAfCorePrint("Consumed: ");
    printHectoPercent(arrayOfDutyCycles[0].dutyCycleConsumed);
    emberAfCorePrintln("");

    for (i = 1; i < sizeof arrayOfDutyCycles / sizeof arrayOfDutyCycles[0]; i++) {
      emberAfCorePrint("  (%2X: ", arrayOfDutyCycles[i].nodeId);
      printHectoPercent(arrayOfDutyCycles[i].dutyCycleConsumed);
      emberAfCorePrintln(")");
    }
  } else {
    emberAfCorePrintln("Could not get %p%p%p", "consumed ", "duty cycle", "s");
  }

  if (emberGetDutyCycleState(&dcState) == EMBER_SUCCESS) {
    emberAfCorePrintln("DC state: %s", dcStateStr[dcState]);
  } else {
    emberAfCorePrintln("Could not get %p%p%p", "current ", "duty cycle", " state");
  }
}

/** @brief Set the Duty Cycle limits
 */
#ifndef UC_BUILD
void emAfSubGhzServerCliDutyCycleLimitsSet(void)
#else
void emAfSubGhzServerCliDutyCycleLimitsSet(sl_cli_command_arg_t *arguments)
#endif
{
  EmberDutyCycleLimits limits = { 0 };
  EmberStatus          status;

  limits.limitThresh = emberUnsignedCommandArgument(0);
  limits.critThresh  = emberUnsignedCommandArgument(1);
  limits.suspLimit   = emberUnsignedCommandArgument(2);

  status = emberSetDutyCycleLimitsInStack(&limits);
  printSuccessOrError(status);
}

/** @brief Send the 'Suspend ZCL Messages' command to a given client.
 *
 * @param nodeId .... client's node ID
 * @param endpoint .. client's endpoint
 * @param period .... suspension perion in minutes
 */
#ifndef UC_BUILD
void emAfSubGhzServerCliSuspendZclMessages(void)
#else
void emAfSubGhzServerCliSuspendZclMessages(sl_cli_command_arg_t *arguments)
#endif
{
  EmberStatus status;

  EmberNodeId nodeId = (EmberNodeId)emberUnsignedCommandArgument(0);
  uint8_t endpoint = (uint8_t)emberUnsignedCommandArgument(1);
  uint8_t period = (uint8_t)emberUnsignedCommandArgument(2);

  status = emberAfPluginSubGhzServerSendSuspendZclMessagesCommand(nodeId,
                                                                  endpoint,
                                                                  period);
  printSuccessOrError(status);
}

/** @brief Print the given Sub-GHZ given client's current status.
 *
 * @param nodeId .... client's node ID
 */
#ifndef UC_BUILD
void emAfSubGhzServerCliClientStatus(void)
#else
void emAfSubGhzServerCliClientStatus(sl_cli_command_arg_t *arguments)
#endif
{
  EmberNodeId nodeId = (EmberNodeId)emberUnsignedCommandArgument(0);
  uint16_t t = emberAfPluginSubGhzServerSuspendZclMessagesStatus(nodeId);

  if (t > 0) {
    emberAfCorePrintln("%2x: %p for %d:%d%d", nodeId, "suspended", t / 60, (t % 60) / 10, t % 10);
  } else {
    emberAfCorePrintln("%2x: not %p", nodeId, "suspended");
  }
}
