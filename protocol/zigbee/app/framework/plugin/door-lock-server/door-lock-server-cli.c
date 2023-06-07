/***************************************************************************//**
 * @file
 * @brief CLI for the Door Lock Server plugin.
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

#include "af.h"

#include "app/util/serial/sl_zigbee_command_interpreter.h"
#include "door-lock-server.h"

#define ISO_639_1_STRING_LENGTH 3

static const char *getLockStateName(EmberAfDoorLockState state)
{
  const char *stateNames[] = {
    "Not Fully Locked",
    "Locked",
    "Unlocked",
  };
  return (state < COUNTOF(stateNames) ? stateNames[state] : "?????");
}

#ifdef ZCL_USING_DOOR_LOCK_CLUSTER_SOUND_VOLUME_ATTRIBUTE
static const char *getSoundVolumeName(uint8_t volume)
{
  const char *soundVolumeNames[] = {
    "Silent",
    "Low",
    "High",
  };
  return (volume < COUNTOF(soundVolumeNames)
          ? soundVolumeNames[volume]
          : "?????");
}
#endif

// plugin door-lock-server status
void sli_zigbee_af_door_lock_server_status_command(sl_cli_command_arg_t *arguments)
{
  uint8_t state;
  EmberAfStatus status = emberAfReadServerAttribute(DOOR_LOCK_SERVER_ENDPOINT,
                                                    ZCL_DOOR_LOCK_CLUSTER_ID,
                                                    ZCL_LOCK_STATE_ATTRIBUTE_ID,
                                                    (uint8_t *)&state,
                                                    sizeof(state));
  if (status == EMBER_ZCL_STATUS_SUCCESS) {
    emberAfAppPrintln("State: %s", getLockStateName(state));
  } else {
    emberAfAppPrintln("Error: cannot read attribute: 0x%X", status);
  }

#ifdef ZCL_USING_DOOR_LOCK_CLUSTER_LANGUAGE_ATTRIBUTE
  uint8_t string[ISO_639_1_STRING_LENGTH + 1]; // + 1 for nul-terminator
  status = emberAfReadServerAttribute(DOOR_LOCK_SERVER_ENDPOINT,
                                      ZCL_DOOR_LOCK_CLUSTER_ID,
                                      ZCL_LANGUAGE_ATTRIBUTE_ID,
                                      string,
                                      sizeof(string));
  string[sizeof(string) - 1] = '\0';
  if (status == EMBER_ZCL_STATUS_SUCCESS) {
    emberAfAppPrintln("Language: %s", &string[1]); // skip the length byte
  } else {
    emberAfAppPrintln("Error: cannot read attribute: 0x%X", status);
  }
#endif

#ifdef ZCL_USING_DOOR_LOCK_CLUSTER_SOUND_VOLUME_ATTRIBUTE
  uint8_t volume;
  status = emberAfReadServerAttribute(DOOR_LOCK_SERVER_ENDPOINT,
                                      ZCL_DOOR_LOCK_CLUSTER_ID,
                                      ZCL_SOUND_VOLUME_ATTRIBUTE_ID,
                                      &volume,
                                      sizeof(volume));
  if (status == EMBER_ZCL_STATUS_SUCCESS) {
    emberAfAppPrintln("Volume: %s", getSoundVolumeName(volume));
  } else {
    emberAfAppPrintln("Error: cannot read attribute: 0x%X", status);
  }
#endif
}

// plugin door-lock-server lock <userId:2>
// plugin door-lock-server unlock <userId:2>
void sli_zigbee_af_door_lock_server_lock_or_unlock_command(sl_cli_command_arg_t *arguments)
{
  bool doLock = memcmp(arguments->argv[arguments->arg_ofs - 1], "lock", strlen("lock")) == 0;
  uint16_t userId = sl_cli_get_argument_uint16(arguments, 0);
  uint8_t state = (doLock
                   ? EMBER_ZCL_DOOR_LOCK_STATE_LOCKED
                   : EMBER_ZCL_DOOR_LOCK_STATE_UNLOCKED);
  EmberAfStatus status = emberAfWriteServerAttribute(DOOR_LOCK_SERVER_ENDPOINT,
                                                     ZCL_DOOR_LOCK_CLUSTER_ID,
                                                     ZCL_LOCK_STATE_ATTRIBUTE_ID,
                                                     (uint8_t *)&state,
                                                     ZCL_ENUM8_ATTRIBUTE_TYPE);

  const char *action = (doLock ? "lock" : "unlock");
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfAppPrintln("Failed to %s door: 0x%X", action, status);
  } else {
    emberAfAppPrintln("Door is now %sed", action);

    if (!emberAfPluginDoorLockServerAddLogEntry(EMBER_ZCL_DOOR_LOCK_EVENT_TYPE_OPERATION,
                                                EMBER_ZCL_DOOR_LOCK_EVENT_SOURCE_MANUAL,
                                                (doLock
                                                 ? EMBER_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_LOCK
                                                 : EMBER_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_UNLOCK),
                                                userId,
                                                0,
                                                NULL)) { // pin...nah
      emberAfAppPrintln("Could not add log entry");
    }
  }
}

// plugin door-lock-server open
// plugin door-lock-server close
void sli_zigbee_af_door_lock_server_open_or_close_command(sl_cli_command_arg_t *arguments)
{
  static uint8_t eventCount = 0;
  uint8_t PIN[] = "";
  bool doOpen = memcmp(arguments->argv[arguments->arg_ofs - 1], "open", strlen("open")) == 0;
  EmberAfDoorState state = (doOpen
                            ? EMBER_ZCL_DOOR_STATE_OPEN
                            : EMBER_ZCL_DOOR_STATE_CLOSED);
  EmberAfStatus status = sli_zigbee_af_door_lock_server_note_door_state_changed(state);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    emberAfAppPrintln("Failed to %s door: 0x%X",
                      (doOpen ? "open" : "close"),
                      status);
  } else {
    emberAfAppPrintln("Door is now %s", (doOpen ? "open" : "closed"));
    emberAfFillCommandDoorLockClusterOperationEventNotification(EMBER_ZCL_DOOR_LOCK_EVENT_SOURCE_MANUAL,
                                                                (doOpen
                                                                 ? EMBER_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_MANUAL_UNLOCK
                                                                 : EMBER_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_MANUAL_LOCK),
                                                                0 /* userId */, PIN, eventCount++ /*timestamp*/, PIN);

    EmberApsFrame *apsFrame = emberAfGetCommandApsFrame();
    apsFrame->sourceEndpoint = 1; //emberAfCurrentEndpoint();

    SEND_COMMAND_UNICAST_TO_BINDINGS();
  }
}

// plugin door-lock-server apply-pin <pin:?>
// plugin door-lock-server apply-rfid <rfid:?>
void sli_zigbee_af_door_lock_server_apply_code_command(sl_cli_command_arg_t *arguments)
{
  bool isPin = memcmp(arguments->argv[arguments->arg_ofs - 1], "apply-pin", strlen("apply-pin")) == 0;

  uint8_t *code = (uint8_t*)sl_cli_get_argument_string(arguments, 0);
  uint8_t codeLength = emberAfStringLength(code);

  EmberAfStatus status
    = (isPin
       ? emberAfPluginDoorLockServerApplyPin(code, codeLength)
       : emberAfPluginDoorLockServerApplyRfid(code, codeLength));
  emberAfAppPrintln("Apply %s: 0x%X", (isPin ? "PIN" : "RFID"), status);
}
