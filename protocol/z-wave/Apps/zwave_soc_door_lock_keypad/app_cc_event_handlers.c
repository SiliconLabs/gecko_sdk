/**
 * Z-Wave Certified Application Door Lock Key Pad Command Classes Events
 * Handlers
 *
 * This implements the application logic for Command Classes communication.
 * i.e. having a command class react on another command class event.
 *
 * @copyright 2023 Silicon Laboratories Inc.
 */

#include <stdint.h>

#include "CC_DoorLock.h"
#include "CC_UserCode.h"
#include "CC_Supervision.h"
#include "zaf_event_distributor_soc.h"

static void
user_code_app_event_handler(__attribute__((unused)) const uint8_t event, __attribute__((unused)) const void *data)
{
  switch (event) {
    case CC_USER_CODE_EVENT_VALIDATE_VALID:
      zaf_event_distributor_enqueue_cc_event(COMMAND_CLASS_DOOR_LOCK, CC_DOOR_LOCK_CODE_EVENT_TOGGLE, NULL);
      break;
  }
}

static void
door_lock_app_event_handler(const uint8_t event, const void *data)
{
  switch (event) {
    case CC_DOOR_LOCK_EVENT_OPERATION_SET_DONE:
    {
      zaf_event_distributor_enqueue_cc_event(COMMAND_CLASS_SUPERVISION, CC_SUPERVISION_EVENT_SUCCESS, data);
      break;
    }
  }
}

ZAF_EVENT_DISTRIBUTOR_REGISTER_CC_EVENT_HANDLER(COMMAND_CLASS_USER_CODE, user_code_app_event_handler);
ZAF_EVENT_DISTRIBUTOR_REGISTER_CC_EVENT_HANDLER(COMMAND_CLASS_DOOR_LOCK, door_lock_app_event_handler);
