/***************************************************************************//**
 * @file
 * @brief This plugin unicasts a permit joins message to joining devices.
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

// Procedure:

// When a device is attempting to the join the network:
// 1.If the node isn't an end device AND already in the joiningDeviceList,
// we record the node in the joiningDeviceList and set of a timer for
// EMBER_AF_PLUGIN_PERMIT_JOIN_MANAGER_DEVICE_ANNOUNCE_TIMEOUT milliseconds.
// 2. If we receive a device Announce from the message AND
// if we have an entry in the joining device table,
// we unicast a Permit Joins message to the device and remove it from the queue.
// 3. Else if the timer expires, we unicast a permit Joins message to the device and
// dequeue it.

#include "app/framework/include/af.h"
#include "app/util/zigbee-framework/zigbee-device-common.h"
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#ifdef SL_CATALOG_ZIGBEE_PERMIT_JOIN_MANAGER_PRESENT
#include "permit-join-manager-config.h"
#else
#include "app/framework/plugin/permit-join-manager/config/permit-join-manager-config.h"
#endif

//=============================================================================
// Globals

//The following globals are defined for unit tests.

#if !defined(EMBER_AF_PLUGIN_PERMIT_JOIN_MANAGER_JOINING_DEVICES_QUEUE_LENGTH)
  #define EMBER_AF_PLUGIN_PERMIT_JOIN_MANAGER_JOINING_DEVICES_QUEUE_LENGTH 4
#endif

#if !defined(EMBER_AF_PLUGIN_PERMIT_JOIN_MANAGER_PERMIT_JOINS_DURATION)
  #define EMBER_AF_PLUGIN_PERMIT_JOIN_MANAGER_PERMIT_JOINS_DURATION 40
#endif

#if !defined(EMBER_AF_PLUGIN_PERMIT_JOIN_MANAGER_DEVICE_ANNOUNCE_TIMEOUT)
  #define EMBER_AF_PLUGIN_PERMIT_JOIN_MANAGER_DEVICE_ANNOUNCE_TIMEOUT 1000
#endif

sl_zigbee_event_t emberAfPluginPermitJoinManagerTimeoutNetworkEvents[EMBER_SUPPORTED_NETWORKS];
void emberAfPluginPermitJoinManagerTimeoutNetworkEventHandler(sl_zigbee_event_t * event);
static EmberAfJoiningDevice joiningDeviceList[EMBER_AF_PLUGIN_PERMIT_JOIN_MANAGER_JOINING_DEVICES_QUEUE_LENGTH];

// With device announce there is only the ZDO sequence number, there is no status code.
#define DEVICE_ANNOUNCE_NODE_ID_OFFSET 1
#define DEVICE_ANNOUNCE_EUI64_OFFSET   (DEVICE_ANNOUNCE_NODE_ID_OFFSET + 2)
#define DEVICE_ANNOUNCE_CAPABILITIES_OFFSET (DEVICE_ANNOUNCE_EUI64_OFFSET + EUI64_SIZE)

#define RECEIVER_ON_WHEN_IDLE 0x08
//============================================================================
// Forward Declarations
static EmberStatus sendPermitJoinsRequest(EmberNodeId emberNodeId);
static void addDeviceToJoiningList(EmberNodeId emberNodeId);
//============================================================================

static EmberStatus sendPermitJoinsRequest(EmberNodeId emberNodeId)
{
  EmberStatus status;
  uint8_t duration;

  duration = EMBER_AF_PLUGIN_PERMIT_JOIN_MANAGER_PERMIT_JOINS_DURATION;
  status = emberPermitJoiningRequest(emberNodeId,
                                     duration,
                                     0x01,   // TC significance is always 1
                                     0);
  return status;
}

static void addDeviceToJoiningList(EmberNodeId emberNodeId)
{
  int i = 0;

  for (i = 0; i < EMBER_AF_PLUGIN_PERMIT_JOIN_MANAGER_JOINING_DEVICES_QUEUE_LENGTH; i++) {
    if (emberNodeId == joiningDeviceList[i].emberNodeId) {
      //fprintf(stderr, "Found emberNodeId %u\n", emberNodeId);
      return;
    }
  }
  for (i = 0; i < EMBER_AF_PLUGIN_PERMIT_JOIN_MANAGER_JOINING_DEVICES_QUEUE_LENGTH; i++) {
    if (joiningDeviceList[i].emberNodeId == EMBER_NULL_NODE_ID) {
      emberAfCorePrintln("Adding to queue at index %u", i);
      joiningDeviceList[i].emberNodeId = emberNodeId;
      joiningDeviceList[i].timeStamp = halCommonGetInt32uMillisecondTick();
      sl_zigbee_event_set_delay_ms(emberAfPluginPermitJoinManagerTimeoutNetworkEvents,
                                   EMBER_AF_PLUGIN_PERMIT_JOIN_MANAGER_DEVICE_ANNOUNCE_TIMEOUT);

      return;
    }
  }
  emberAfCorePrintln("Ran out of space on Joining device queue");
}

static void removeDeviceFromJoiningList(EmberNodeId emberNodeId)
{
  int i = 0;
  for (i = 0; i < EMBER_AF_PLUGIN_PERMIT_JOIN_MANAGER_JOINING_DEVICES_QUEUE_LENGTH; i++) {
    if (joiningDeviceList[i].emberNodeId == emberNodeId) {
      //fprintf(stderr,"\r\nFound node Id %u at index %u",emberNodeId,i);
      joiningDeviceList[i].emberNodeId = EMBER_NULL_NODE_ID;
      joiningDeviceList[i].timeStamp = 0;
      return;
    }
  }
}

static EmberNodeId findDeviceInJoiningList(EmberNodeId emberNodeId)
{
  int i = 0;
  for (i = 0; i < EMBER_AF_PLUGIN_PERMIT_JOIN_MANAGER_JOINING_DEVICES_QUEUE_LENGTH; i++) {
    if (joiningDeviceList[i].emberNodeId == emberNodeId) {
      return emberNodeId;
    }
  }
  return EMBER_NULL_NODE_ID;
}

void emberAfPluginPermitJoinManagerInitCallback(uint8_t init_level)
{
  switch (init_level) {
    case SL_ZIGBEE_INIT_LEVEL_EVENT:
    {
      sl_zigbee_network_event_init(emberAfPluginPermitJoinManagerTimeoutNetworkEvents,
                                   emberAfPluginPermitJoinManagerTimeoutNetworkEventHandler);
      break;
    }

    case SL_ZIGBEE_INIT_LEVEL_LOCAL_DATA:
    {
      int i = 0;
      for (i = 0; i < EMBER_AF_PLUGIN_PERMIT_JOIN_MANAGER_JOINING_DEVICES_QUEUE_LENGTH; i++) {
        joiningDeviceList[i].emberNodeId = EMBER_NULL_NODE_ID;
        joiningDeviceList[i].timeStamp = 0;
      }
      break;
    }
  }
}

bool emberAfPluginPermitJoinManagerZdoMessageReceivedCallback(EmberNodeId emberNodeId,
                                                              EmberApsFrame* apsFrame,
                                                              uint8_t* message,
                                                              uint16_t length)
{
  if (apsFrame->clusterId == END_DEVICE_ANNOUNCE) {
    if ((message[DEVICE_ANNOUNCE_CAPABILITIES_OFFSET] & RECEIVER_ON_WHEN_IDLE) == 0) {
      //fprintf(stderr,"Ignoring sleep end device");
      return true;
    }

    //Dropping nodes that aren't in our list. We have probably already sent a permit Joins Request
    //because we didn't hear a Device Announce within the designated time.
    if (findDeviceInJoiningList(emberNodeId) == EMBER_NULL_NODE_ID) {
      return true;
    }

    sendPermitJoinsRequest(emberNodeId);
    // fprintf(stderr,"\r\nDevice Announce heard,Sending Join Request %u\r\n",emberNodeId);
    removeDeviceFromJoiningList(emberNodeId);
    //Doesn't matter if we can't Unicast the request.
    //TODO: investigate if it should matter.  The original comment doesn't say why.
    return true;
  }
  return false;
}

void emberAfPluginPermitJoinManagerTimeoutNetworkEventHandler(sl_zigbee_event_t * event)
{
  sl_zigbee_event_set_inactive(emberAfPluginPermitJoinManagerTimeoutNetworkEvents);
  int i = 0;
  static int j = 0;
  for (i = 0; i < EMBER_AF_PLUGIN_PERMIT_JOIN_MANAGER_JOINING_DEVICES_QUEUE_LENGTH; i++) {
    if (joiningDeviceList[i].emberNodeId != EMBER_NULL_NODE_ID
        && (elapsedTimeInt32u(joiningDeviceList[i].timeStamp, halCommonGetInt32uMillisecondTick())
            >= EMBER_AF_PLUGIN_PERMIT_JOIN_MANAGER_JOINING_DEVICES_QUEUE_LENGTH)) {
      j++;
      //fprintf(stderr,"\r\nNo device announce yet time, sending to %u count %u \r\n",joiningDeviceList[i].emberNodeId,j);
      //TODO: should we check the return value?
      sendPermitJoinsRequest(joiningDeviceList[i].emberNodeId);
      removeDeviceFromJoiningList(joiningDeviceList[i].emberNodeId);
      return;
    }
  }
}

void emberAfPluginPermitJoinManagerTrustCenterJoinCallback(EmberNodeId newNodeId,
                                                           EmberEUI64 newNodeEui64,
                                                           EmberNodeId parentOfNewNode,
                                                           EmberDeviceUpdate status,
                                                           EmberJoinDecision decision)
{
  if (decision == EMBER_DENY_JOIN) {
    emberAfCorePrintln("Join denied, not queueing for permit joining %u", newNodeId);
  } else if (decision == EMBER_USE_PRECONFIGURED_KEY
             || decision == EMBER_SEND_KEY_IN_THE_CLEAR) {
    emberAfCorePrintln("Adding device to the queue");
    addDeviceToJoiningList(newNodeId);
  } // else (decision == EMBER_NO_ACTION)
}
