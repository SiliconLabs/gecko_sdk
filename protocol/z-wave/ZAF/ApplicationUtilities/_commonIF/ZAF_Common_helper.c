/**
 * @file
 * @copyright 2018 Silicon Laboratories Inc.
 */

#include "ZAF_Common_helper.h"
#include "ZAF_Common_interface.h"
#include "ZAF_ApplicationEvents.h"

#include "ZW_TransportSecProtocol.h"
#include <ZW_TransportMulticast.h>
#include "ZAF_TSE.h"
#include <ZAF_CmdPublisher.h>
#include "ZAF_CC_Invoker.h"
#include "AppTimer.h"
#include "board_init.h"
#include "board_indicator.h"
#include <ZAF_nvm_app.h>
#include <ZAF_nvm.h>
#include "zpal_nvm.h"
#include "zpal_power_manager.h"
#include "zaf_config_api.h"
#include <zaf_cc_list_generator.h>
#include <ZW_system_startup_api.h>
#include "zaf_event_distributor.h"
#include "zaf_protocol_config.h"
#include "zaf_transport_tx.h"
#include "ZAF_AppName.h"

//#define DEBUGPRINT
#include "DebugPrint.h"

static TaskHandle_t m_AppTaskHandle;
static SCommandClassSet_t m_CCSet;

/*
 * Max number of subscribers. Those are known so far:
 * ApplicationCommandHandler + Security Discovery + Multicast = 3
 */
#define CP_MAX_SUBSCRIBERS  3

#define PM_STAY_AWAKE_DURATION_LEARN_MODE   (1000 * 10)         // [ms]

static void ZAF_FLiRS_StayAwake(void);
static void portable_controller_stay_awake(void);

static bool invoke_init(CC_handler_map_latest_t const * const p_cc_entry, __attribute__((unused)) zaf_cc_context_t context)
{
  if (NULL != p_cc_entry->init)
  {
    p_cc_entry->init();
  }
  return false;
}

void ZAF_Init(TaskHandle_t AppTaskHandle, SApplicationHandles *pAppHandles)
{
  zaf_cc_list_t *unsecure_included_cc;
  zaf_cc_list_t *secure_included_unsecure_cc;
  zaf_cc_list_t *secure_included_secure_cc;

  DPRINT("* ZAF_Init *\r\n");

  // Set ZAF variables as soon as possible
  ZAF_setAppHandle(pAppHandles);
  m_AppTaskHandle = AppTaskHandle;

  zafi_cc_list_generator_generate();

  // Convert from zaf_cc_list_t to SCommandClassSet_t which is the type
  // used in the protocol interface
  zafi_cc_list_generator_get_lists(0, &unsecure_included_cc, &secure_included_unsecure_cc, &secure_included_secure_cc);

  m_CCSet.UnSecureIncludedCC.iListLength = unsecure_included_cc->list_size;
  m_CCSet.UnSecureIncludedCC.pCommandClasses = unsecure_included_cc->cc_list;

  m_CCSet.SecureIncludedUnSecureCC.iListLength = secure_included_unsecure_cc->list_size;
  m_CCSet.SecureIncludedUnSecureCC.pCommandClasses = secure_included_unsecure_cc->cc_list;

  m_CCSet.SecureIncludedSecureCC.iListLength = secure_included_secure_cc->list_size;
  m_CCSet.SecureIncludedSecureCC.pCommandClasses = secure_included_secure_cc->cc_list;

  ZW_system_startup_SetCCSet(&m_CCSet);

  zaf_transport_init();

  AppTimerInit(EAPPLICATIONEVENT_TIMER, AppTaskHandle);

  /* hardware initialization */
  Board_Init();

  /* board led initialiaztion */
  Board_IndicatorInit();

  // Init file system
  ZAF_nvm_app_init();
  ZAF_nvm_init();

  // Store the application's name in NVM if the feature is enabled
  ZAF_AppName_Write();

  ZW_TransportEndpoint_Init();

  //Initializing TSE timers
  ZAF_TSE_Init();

  static ZAF_CP_STORAGE(content, CP_MAX_SUBSCRIBERS);
  ZAF_SetCPHandle(ZAF_CP_Init((void*) &content, CP_MAX_SUBSCRIBERS));
  if (false == ZAF_CP_SubscribeToAll(ZAF_getCPHandle(), NULL, (zaf_cp_subscriberFunction_t)ApplicationCommandHandler))
  {
    DPRINT("Subscription to Command Publisher failed!\r\n");
    ASSERT(false);
  }

  // Reset the wake up callback.
  zaf_set_stay_awake_callback(NULL);

  // Initialize command classes that have registered an init function.
  // Don't pass a context because invoke_init() doesn't require it.
  ZAF_CC_foreach(invoke_init, NULL);

  // Check if the wake up callback was NOT set by a command class (CC Wake Up).
  if (NULL == zaf_get_stay_awake_callback()) {
    // The wake up callback was NOT set. Hence, CC Wake Up is not linked. Now check the role type.

    uint8_t role_type = zaf_config_get_role_type();

    if ((ZWAVEPLUS_INFO_REPORT_ROLE_TYPE_SLAVE_SLEEPING_LISTENING == role_type) ||
        (ZWAVEPLUS_INFO_REPORT_ROLE_TYPE_CONTROLLER_PORTABLE == role_type)) {
      zpal_pm_handle_t power_lock = zpal_pm_register(ZPAL_PM_TYPE_USE_RADIO);
      ZAF_setPowerLock(power_lock);
    }

    if (ZWAVEPLUS_INFO_REPORT_ROLE_TYPE_SLAVE_SLEEPING_LISTENING == role_type) {
      // Role type is "sleeping listening" (FLiRS) - set the stay awake callback.
      zaf_set_stay_awake_callback(ZAF_FLiRS_StayAwake);
    } else if (ZWAVEPLUS_INFO_REPORT_ROLE_TYPE_CONTROLLER_PORTABLE == role_type) {
      // Role type is a portable controller - set the stay awake callback.
      zaf_set_stay_awake_callback(portable_controller_stay_awake);
    } else {
      // Role type doesn't require a stay awake function - do nothing.
    }
  } else {
    // The wake up callback was set by a command class - do nothing.
  }

  Transport_OnApplicationInitSW();

  ZW_TransportMulticast_init();

  zaf_event_distributor_init();
}

static bool invoke_reset(CC_handler_map_latest_t const * const p_cc_entry, __attribute__((unused)) zaf_cc_context_t context)
{
  if (NULL != p_cc_entry->reset)
  {
    p_cc_entry->reset();
  }
  return false;
}

void ZAF_Reset(void)
{
  // Don't pass a context because invoke_reset() doesn't require it.
  ZAF_CC_foreach(invoke_reset, NULL);
}

/**
 * Keeps a FLiRS application awake for 2 seconds.
 *
 * The 2 seconds are specified for the Listening Sleeping role type.
 */
static void ZAF_FLiRS_StayAwake(void)
{
  DPRINT("\r\nZAF_FLiRS_StayAwake\r\n");
  zpal_pm_stay_awake(ZAF_getPowerLock(), 2000);
}

static void portable_controller_stay_awake(void) {
  /* Don't sleep the next 10 seconds */
  zpal_pm_stay_awake(ZAF_getPowerLock(), PM_STAY_AWAKE_DURATION_LEARN_MODE);
}

TaskHandle_t ZAF_getAppTaskHandle(void)
{
  ASSERT(m_AppTaskHandle);
  return m_AppTaskHandle;
}

void zaf_stay_awake(void) {
  zaf_wake_up_callback_t callback = zaf_get_stay_awake_callback();

  if (NULL != callback) {
    callback();
  }
}

ZW_WEAK void
zaf_learn_mode_finished(void)
{

}
