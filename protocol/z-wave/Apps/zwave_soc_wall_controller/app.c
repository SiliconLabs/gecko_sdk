/**
 * Z-Wave Certified Application Wall Controller
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#include <stdbool.h>
#include <stdint.h>
#include "Assert.h"
#include "MfgTokens.h"
#include "DebugPrintConfig.h"
//#define DEBUGPRINT
#include "DebugPrint.h"
#include "ZW_system_startup_api.h"
#include "CC_Basic.h"
#include "CC_CentralScene.h"
#include "CC_MultilevelSwitch_Control.h"
#include "ZAF_Common_helper.h"
#include "ZAF_Common_interface.h"
#include "ZAF_network_learn.h"
#include "events.h"
#include "zpal_watchdog.h"
#include "app_hw.h"
#include "board_indicator.h"
#include "ZAF_ApplicationEvents.h"
#include "zaf_event_distributor_soc.h"
#include "zpal_misc.h"
#include "zw_build_no.h"
#include "zaf_protocol_config.h"
#ifdef DEBUGPRINT
#include "ZAF_PrintAppInfo.h"
#endif

typedef enum {
  KEY01,
  KEY02,
  KEY03,
  NUMBER_OF_KEYS
} key_id_t;

/// Map key number into scene number
#define SCENE_NUMBER(x) ((x)+1)

typedef enum
{
  KEY_EVENT_SHORT_PRESS,
  KEY_EVENT_HOLD,
  KEY_EVENT_UP
} key_event_t;

#define EVENT_APP_CC_NO_JOB 0xFF

/**
 * Application states. Function zaf_event_distributor_app_event_manager(..) includes the state
 * event machine.
 */
typedef enum
{
  STATE_APP_IDLE,
  STATE_APP_STARTUP,
  STATE_APP_AWAIT_KEYPRESS,          // Unused
  STATE_APP_LEARN_MODE,
  STATE_APP_GET_NEXT_NODE,           // Unused
  STATE_APP_INITIATE_TRANSMISSION,   // Unused
  STATE_APP_AWAIT_TRANSMIT_CALLBACK, // Unused
  STATE_APP_RESET,
  STATE_APP_TRANSMIT_DATA
} STATE_APP;

/**
 * Holds the latest button action.
 * The action is used to distinguish between which action to perform:
 * - Press    => Switch on/off
 * - Hold     => Start dimming
 * - Release  => Stop dimming
 */
static key_event_t keyEventGlobal;

static CCMLS_PRIMARY_SWITCH_T multiLevelDirection[NUMBER_OF_KEYS] = {CCMLS_PRIMARY_SWITCH_DOWN, CCMLS_PRIMARY_SWITCH_DOWN, CCMLS_PRIMARY_SWITCH_DOWN};
static uint8_t buttonStates[NUMBER_OF_KEYS] = {0, 0, 0};

#ifdef DEBUGPRINT
static uint8_t m_aDebugPrintBuffer[96];
#endif

void ApplicationTask(SApplicationHandles* pAppHandles);

/**
 * @brief Prepares the transmission of commands stored in the AGI table.
 *
 * @param profile The profile key.
 * @param activeButton The button that is changing state
 */
static void
AGITransmission(uint8_t profile, key_id_t activeButton)
{
  agi_profile_t agi_profile;

  DPRINTF("\r\nAGITransmission %d", keyEventGlobal);

  agi_profile.profile_MS = ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL;
  agi_profile.profile_LS = profile;

  if (KEY_EVENT_SHORT_PRESS == keyEventGlobal) {
    if (0xFF == buttonStates[activeButton]) {
      /*
       * If button is on, turn device off.
       */
      buttonStates[activeButton] = 0x00;
      DPRINT("\r\nBasic OFF");
    } else {
      /*
       * If button is off, turn device on.
       */
      buttonStates[activeButton] = 0xFF;
      DPRINT("\r\nBasic ON");
    }
    (void) CC_Basic_Set_tx(&agi_profile, ENDPOINT_ROOT, buttonStates[activeButton], 
                            true, NULL);
  } else if (KEY_EVENT_HOLD == keyEventGlobal) {
    if (CCMLS_PRIMARY_SWITCH_UP == multiLevelDirection[activeButton]) {
      multiLevelDirection[activeButton] = CCMLS_PRIMARY_SWITCH_DOWN;
    } else {
      multiLevelDirection[activeButton] = CCMLS_PRIMARY_SWITCH_UP;
    }
    (void) CmdClassMultilevelSwitchStartLevelChange(&agi_profile, ENDPOINT_ROOT,
                                                      NULL, 
                                                      multiLevelDirection[activeButton], 
                                                      CCMLS_IGNORE_START_LEVEL_TRUE,
                                                      CCMLS_SECONDARY_SWITCH_NO_INC_DEC, 
                                                      0, 2, 0);
  } else if (KEY_EVENT_UP == keyEventGlobal) {
    DPRINT("\r\npre BUTTON_UP EVENT_APP_CC_SWITCH_MULTILEVEL_JOB");
    (void) CmdClassMultilevelSwitchStopLevelChange(&agi_profile, ENDPOINT_ROOT,
                                                    NULL);
  }
}

/**
 * @brief See description for function prototype in ZW_basis_api.h.
 */
ZW_APPLICATION_STATUS
ApplicationInit(__attribute__((unused)) EResetReason_t eResetReason)
{
  SRadioConfig_t* RadioConfig;

  DPRINT("Enabling watchdog\n");
  zpal_enable_watchdog(true);

#ifdef DEBUGPRINT
  zpal_debug_init();
  DebugPrintConfig(m_aDebugPrintBuffer, sizeof(m_aDebugPrintBuffer), zpal_debug_output);
  DebugPrintf("ApplicationInit eResetReason = %d\n", eResetReason);
#endif

  RadioConfig = zaf_get_radio_config();

  // Read Rf region from MFG_ZWAVE_COUNTRY_FREQ
  zpal_radio_region_t regionMfg;
  ZW_GetMfgTokenDataCountryFreq((void*) &regionMfg);
  if (isRfRegionValid(regionMfg)) {
    RadioConfig->eRegion = regionMfg;
  } else {
    ZW_SetMfgTokenDataCountryRegion((void*) &RadioConfig->eRegion);
  }

  /*************************************************************************************
   * CREATE USER TASKS  -  ZW_ApplicationRegisterTask() and ZW_UserTask_CreateTask()
   *************************************************************************************
   * Register the main APP task function.
   *
   * ATTENTION: This function is the only task that can call ZAF API functions!!!
   * Failure to follow guidelines will result in undefined behavior.
   *
   * Furthermore, this function is the only way to register Event Notification
   * Bit Numbers for associating to given event handlers.
   *
   * ZW_UserTask_CreateTask() can be used to create additional tasks.
   * @see zwave_soc_sensor_pir example for more info.
   *************************************************************************************/
  bool bWasTaskCreated = ZW_ApplicationRegisterTask(
                                                    ApplicationTask,
                                                    EAPPLICATIONEVENT_ZWRX,
                                                    EAPPLICATIONEVENT_ZWCOMMANDSTATUS,
                                                    zaf_get_protocol_config()
                                                    );
  ASSERT(bWasTaskCreated);

  return(APPLICATION_RUNNING);
}

/**
 * A pointer to this function is passed to ZW_ApplicationRegisterTask() making it the FreeRTOS
 * application task.
 */
void
ApplicationTask(SApplicationHandles* pAppHandles)
{
  ZAF_Init(xTaskGetCurrentTaskHandle(), pAppHandles);

#ifdef DEBUGPRINT
  ZAF_PrintAppInfo();
#endif

  app_hw_init();

  /* Enter SmartStart*/
  /* Protocol will commence SmartStart only if the node is NOT already included in the network */
  ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION_SMARTSTART);

  // Wait for and process events
  DPRINT("WallController Event processor Started\r\n");
  for (;;)
  {
    if (!zaf_event_distributor_distribute())
    {
      return;
    }
  }
}

/**
 * @brief The core state machine of this sample application.
 * @param event The event that triggered the call of zaf_event_distributor_app_event_manager.
 */
void
zaf_event_distributor_app_event_manager(const uint8_t event)
{
  DPRINTF("zaf_event_distributor_app_event_manager Ev: %d\r\n", event);

  switch(event) {
      /**************************************************************************************
       * KEY 1
       *************************************************************************************/
    case EVENT_APP_KEY01_SHORT_PRESS:
      DPRINT("\r\nK1SHORT_PRESS\r\n");

      keyEventGlobal = KEY_EVENT_SHORT_PRESS;
      AGITransmission(ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY01, KEY01);
      (void)cc_central_scene_notification_tx(
          NULL,
          CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_PRESSED_1_TIME_V2,
          SCENE_NUMBER(KEY01),
          NULL);
      break;

    case EVENT_APP_KEY01_HOLD:
      DPRINT("\r\nK1HOLD\r\n");
      cc_central_scene_handle_notification_timer(true, SCENE_NUMBER(KEY01));

      keyEventGlobal = KEY_EVENT_HOLD;
      AGITransmission(ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY01, KEY01);
      // Call once. Next calls, if needed, will be handled by CC Central Scene timer
      (void)cc_central_scene_notification_tx(
          NULL,
          CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_HELD_DOWN_V2,
          SCENE_NUMBER(KEY01),
          NULL);
      break;

    case EVENT_APP_KEY01_RELEASE:
      DPRINT("\r\nK1UP\r\n");
      cc_central_scene_handle_notification_timer(false, SCENE_NUMBER(KEY01));

      keyEventGlobal = KEY_EVENT_UP;
      AGITransmission(ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY01, KEY01);
      (void)cc_central_scene_notification_tx(
          NULL,
          CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_RELEASED_V2,
          SCENE_NUMBER(KEY01),
          NULL);
      break;

      /**************************************************************************************
       * KEY 2
       *************************************************************************************/

    case EVENT_APP_KEY02_SHORT_PRESS:
      DPRINT("\r\nK2SHORT_PRESS\r\n");

      keyEventGlobal = KEY_EVENT_SHORT_PRESS;
      AGITransmission(ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY02, KEY02);
      (void)cc_central_scene_notification_tx(
              NULL,
              CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_PRESSED_1_TIME_V2,
              SCENE_NUMBER(KEY02),
              NULL);
      break;

    case EVENT_APP_KEY02_HOLD:
      DPRINT("\r\nK2HOLD\r\n");
      cc_central_scene_handle_notification_timer(true, SCENE_NUMBER(KEY02));

      keyEventGlobal = KEY_EVENT_HOLD;
      AGITransmission(ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY02, KEY02);
      // Call once. Next calls, if needed, will be handled by CC Central Scene timer
      (void)cc_central_scene_notification_tx(
          NULL,
          CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_HELD_DOWN_V2,
          SCENE_NUMBER(KEY02),
          NULL);
      break;

    case EVENT_APP_KEY02_RELEASE:
      DPRINT("\r\nK2UP\r\n");
      cc_central_scene_handle_notification_timer(false, SCENE_NUMBER(KEY02));

      keyEventGlobal = KEY_EVENT_UP;
      AGITransmission(ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY02, KEY02);
      (void)cc_central_scene_notification_tx(
          NULL,
          CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_RELEASED_V2,
          SCENE_NUMBER(KEY02),
          NULL);
      break;

      /**************************************************************************************
       * KEY 3
       *************************************************************************************/

    case EVENT_APP_KEY03_SHORT_PRESS:
      DPRINT("\r\nK3SHORT_PRESS\r\n");

      keyEventGlobal = KEY_EVENT_SHORT_PRESS;
      AGITransmission(ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY03, KEY03);
      (void)cc_central_scene_notification_tx(
              NULL,
              CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_PRESSED_1_TIME_V2,
              SCENE_NUMBER(KEY03),
              NULL);
      break;

    case EVENT_APP_KEY03_HOLD:
      DPRINT("\r\nK3HOLD\r\n");
      cc_central_scene_handle_notification_timer(true, SCENE_NUMBER(KEY03));

      keyEventGlobal = KEY_EVENT_HOLD;
      AGITransmission(ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY03, KEY03);
      // Call once. Next calls, if needed, will be handled by CC Central Scene timer
      (void)cc_central_scene_notification_tx(
          NULL,
          CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_HELD_DOWN_V2,
          SCENE_NUMBER(KEY03),
          NULL);

      break;

    case EVENT_APP_KEY03_RELEASE:
      DPRINT("\r\nK3UP\r\n");
      cc_central_scene_handle_notification_timer(false, SCENE_NUMBER(KEY03));

      keyEventGlobal = KEY_EVENT_UP;
      AGITransmission(ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY03, KEY03);
      (void)cc_central_scene_notification_tx(
          NULL,
          CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_RELEASED_V2,
          SCENE_NUMBER(KEY03),
          NULL);
      break;
      break;

    default:
      // Do nothing.
      break;
  }
}
