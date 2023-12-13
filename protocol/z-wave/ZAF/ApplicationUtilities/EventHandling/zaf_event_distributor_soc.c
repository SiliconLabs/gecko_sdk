/**
 * @file
 * @brief ZAF Event distributor source file
 * @copyright 2022 Silicon Laboratories Inc.
 */
#include <AppTimer.h>
#include <EventDistributor.h>
#include <SizeOf.h>
#include <ZW_typedefs.h>
#include <ZAF_ApplicationEvents.h>
#include <ZAF_Common_helper.h>
#include <ZAF_Common_interface.h>
#include <zaf_event_distributor_soc.h>
#include <zaf_event_distributor_soc_config.h>
#if defined(ZAF_USE_LEGACY_JOB_HELPER)
#include <zaf_job_helper.h>
#endif /* defined(ZAF_USE_LEGACY_JOB_HELPER) */
#include <ZW_TransportSecProtocol.h>
#include <ev_man.h>
#include <board_indicator.h>
#include <ZAF_Common_interface.h>
#include <ZAF_network_learn.h>
#include <zaf_nvm_soc.h>
#include <ZAF_file_ids.h>
#include <zpal_misc.h>
#include <zpal_watchdog.h>
#include <CC_DeviceResetLocally.h>
#include <CC_Indicator.h>

//#define DEBUGPRINT
#include "DebugPrint.h"

/**
 * This is the first of the registered app handlers
 */
extern const zaf_event_distributor_cc_event_handler_map_latest_t __start__zaf_event_distributor_cc_event_handler;
#define cc_event_handler_start __start__zaf_event_distributor_cc_event_handler
/**
 * This marks the end of the handlers. The element
 * after the last element. This means that this element
 * is not valid.
 */
extern const zaf_event_distributor_cc_event_handler_map_latest_t __stop__zaf_event_distributor_cc_event_handler;
#define cc_event_handler_stop __stop__zaf_event_distributor_cc_event_handler

/**
 * Callback type for zaf_event_distributor_cc_event_handler_for_each().
 *
 * The ZAF Event Distributor Handler Map must always be the latest available version.
 */
typedef void (*cc_event_handler_invoker_callback_t)(zaf_event_distributor_cc_event_handler_map_latest_t const * const handler_entry, void* args);

// Event distributor object
static SEventDistributor g_EventDistributor = { 0 };

/**
 * The following four variables are used for the application event queue.
 */
static SQueueNotifying m_AppEventNotifyingQueue = { 0 };
static StaticQueue_t m_AppEventQueueObject = { 0 };
static uint8_t m_AppEventQueueStorage[ZAF_EVENT_DISTRIBUTOR_SOC_CONFIG_APP_QUEUE_SIZE];
static QueueHandle_t m_AppEventQueue = { 0 };

/**
 * The following four variables are used for the command class event queue.
 */
static SQueueNotifying m_CCEventNotifyingQueue = { 0 };
static StaticQueue_t m_CCEventQueueObject = { 0 };
static event_cc_t m_CCEventQueueStorage[ZAF_EVENT_DISTRIBUTOR_SOC_CONFIG_CC_QUEUE_SIZE] = { { 0 } };
static QueueHandle_t m_CCEventQueue = { 0 };

static bool learnModeInProgress;
static bool resetInProgress;

static void
set_protocol_default(void)
{
  /* Reset protocol */
  SZwaveCommandPackage CommandPackage;
  SApplicationHandles* pAppHandles;
  EQueueNotifyingStatus Status;

  CommandPackage.eCommandType = EZWAVECOMMANDTYPE_SET_DEFAULT;
  pAppHandles = ZAF_getAppHandle();

  DPRINT("\nDisabling watchdog during reset\n");
  zpal_enable_watchdog(false);

  Status = QueueNotifyingSendToBack(pAppHandles->pZwCommandQueue, (uint8_t*)&CommandPackage, 500);
  ASSERT(EQUEUENOTIFYING_STATUS_SUCCESS == Status);
}

static void
learn_mode_finished_or_stop(void)
{
  Board_IndicateStatus(BOARD_STATUS_IDLE);
  //Go back to smart start if the node was never included.
  //Protocol will not commence SmartStart if the node is already included in the network.
  ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION_SMARTSTART);

  learnModeInProgress = false;

  /* If we are in a network and the Identify LED state was changed to idle due to learn mode, report it to lifeline */
  if (!Board_IsIndicatorActive()) {
    CC_Indicator_RefreshIndicatorProperties();
  }
}

/**
 * @brief Called when protocol puts a frame on the ZwRxQueue.
 */
static void
EventHandlerZwRx(void)
{
  SApplicationHandles* pAppHandles;
  SZwaveReceivePackage RxPackage;

  pAppHandles = ZAF_getAppHandle();

  // Handle incoming replies
  while (xQueueReceive(pAppHandles->ZwRxQueue, (uint8_t*)(&RxPackage), 0) == pdTRUE) {
    DPRINT("Incoming Rx msg\r\n");

    switch (RxPackage.eReceiveType) {
      case EZWAVERECEIVETYPE_SINGLE:
        ZAF_CP_CommandPublish(ZAF_getCPHandle(), (void *) &RxPackage);
        break;

      case EZWAVERECEIVETYPE_NODE_UPDATE:
      case EZWAVERECEIVETYPE_STAY_AWAKE:
      {
        zaf_stay_awake();
        break;
      }
      case EZWAVERECEIVETYPE_SECURITY_EVENT:
      default:
        break;
    }

    zaf_event_distributor_app_zw_rx(&RxPackage);
  }
}

/**
 * @brief Triggered when protocol puts a message on the ZwCommandStatusQueue.
 */
static void
EventHandlerZwCommandStatus(void)
{
  SApplicationHandles* pAppHandles;
  SZwaveCommandStatusPackage Status;

  pAppHandles = ZAF_getAppHandle();

  // Handle incoming replies
  while (xQueueReceive(pAppHandles->ZwCommandStatusQueue, (uint8_t*)(&Status), 0) == pdTRUE) {
    DPRINT("Incoming Status msg\r\n");

    switch (Status.eStatusType) {
      case EZWAVECOMMANDSTATUS_TX:
      {
        SZWaveTransmitStatus* pTxStatus = &Status.Content.TxStatus;
        if (!pTxStatus->bIsTxFrameLegal) {
          DPRINT("Auch - not sure what to do\r\n");
        } else {
          DPRINTF("Tx Status received: %#02x\r\n", pTxStatus->TxStatus);
          if (pTxStatus->Handle) {
            ZAF_TX_Callback_t callback = (ZAF_TX_Callback_t)pTxStatus->Handle;
            transmission_result_t result = {
              .status = pTxStatus->TxStatus,
              .isFinished = TRANSMISSION_RESULT_UNKNOWN
            };
            callback(&result);
            zaf_stay_awake();
          }
        }

        break;
      }

      case EZWAVECOMMANDSTATUS_GENERATE_RANDOM:
      {
        DPRINT("Generate Random status\r\n");
        break;
      }

      case EZWAVECOMMANDSTATUS_LEARN_MODE_STATUS:
      {
        DPRINTF("Learn status %d\r\n", Status.Content.LearnModeStatus.Status);
        if (ELEARNSTATUS_ASSIGN_COMPLETE == Status.Content.LearnModeStatus.Status) {
          // When security S0 or higher is set, remove all settings which happen before secure inclusion
          // calling function zafi_event_distributor_set_default_configuration(). The same function is used when there is an
          // EINCLUSIONSTATE_EXCLUDED.
          if ((EINCLUSIONSTATE_EXCLUDED == pAppHandles->pNetworkInfo->eInclusionState)
              || (SECURITY_KEY_NONE != GetHighestSecureLevel(pAppHandles->pNetworkInfo->SecurityKeys))) {
            zafi_nvm_app_set_default_configuration();
          }
          zaf_event_distributor_enqueue_app_event(EVENT_SYSTEM_LEARNMODE_FINISHED);
          ZAF_Transport_OnLearnCompleted();
        } else if (ELEARNSTATUS_SMART_START_IN_PROGRESS == Status.Content.LearnModeStatus.Status) {
          zaf_event_distributor_enqueue_app_event(EVENT_SYSTEM_SMARTSTART_IN_PROGRESS);
        } else if (ELEARNSTATUS_LEARN_MODE_COMPLETED_TIMEOUT == Status.Content.LearnModeStatus.Status) {
          zaf_event_distributor_enqueue_app_event(EVENT_SYSTEM_LEARNMODE_FINISHED);
        } else if (ELEARNSTATUS_LEARN_MODE_COMPLETED_FAILED == Status.Content.LearnModeStatus.Status) {
          //Reformats protocol and application NVM. Then soft reset.
          zaf_event_distributor_enqueue_app_event(EVENT_SYSTEM_RESET);
        }
        break;
      }

      case EZWAVECOMMANDSTATUS_NETWORK_LEARN_MODE_START:
      {
        break;
      }

      case EZWAVECOMMANDSTATUS_SET_DEFAULT:
      { // Received when protocol is started (not implemented yet), and when SetDefault command is completed
        DPRINT("Protocol Ready\r\n");
        zaf_event_distributor_enqueue_app_event(EVENT_SYSTEM_FLUSHMEM_READY);

        break;
      }

      case EZWAVECOMMANDSTATUS_INVALID_TX_REQUEST:
      {
        DPRINTF("ERROR: Invalid TX Request to protocol - %d", Status.Content.InvalidTxRequestStatus.InvalidTxRequest);
        break;
      }

      case EZWAVECOMMANDSTATUS_INVALID_COMMAND:
      {
        DPRINTF("ERROR: Invalid command to protocol - %d", Status.Content.InvalidCommandStatus.InvalidCommand);
        break;
      }

      case EZWAVECOMMANDSTATUS_ZW_SET_MAX_INCL_REQ_INTERVALS:
      {
        // Status response from calling the ZAF_SetMaxInclusionRequestIntervals function
        DPRINTF("SetMaxInclusionRequestIntervals status: %s\r\n",
                Status.Content.NetworkManagementStatus.statusInfo[0] == true ? "SUCCESS" : "FAIL");
        break;
      }

      case EZWAVECOMMANDSTATUS_ZW_SET_TX_ATTENUATION:
      {
        if (false == Status.Content.SetTxAttenuation.result) {
          DPRINT("Not allowed to attenuate tx-power\r\n");
        }
        break;
      }

      default:
        break;
    }

    zaf_event_distributor_app_zw_command_status(&Status);
  }
}

static void
event_manager(const uint8_t event)
{
  // Handle here only system events
  switch (event) {
    case EVENT_SYSTEM_LEARNMODE_TOGGLE:
      if (learnModeInProgress) {
        zaf_event_distributor_enqueue_app_event(EVENT_SYSTEM_LEARNMODE_STOP);
      } else {
        zaf_event_distributor_enqueue_app_event(EVENT_SYSTEM_LEARNMODE_START);
      }
      break;
    case EVENT_SYSTEM_LEARNMODE_START:
    {
      SApplicationHandles *appHandles;

      appHandles = ZAF_getAppHandle();
      if (EINCLUSIONSTATE_EXCLUDED != appHandles->pNetworkInfo->eInclusionState) {
        DPRINT("LEARN_MODE_EXCLUSION\r\n");
        ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_EXCLUSION_NWE);
      } else {
        DPRINT("LEARN_MODE_INCLUSION\r\n");
        ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION);
      }
      learnModeInProgress = true;
      Board_IndicateStatus(BOARD_STATUS_LEARNMODE_ACTIVE);
      break;
    }
    case EVENT_SYSTEM_LEARNMODE_STOP:
      ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_DISABLE);

      learn_mode_finished_or_stop();
      break;
    case EVENT_SYSTEM_LEARNMODE_FINISHED:
      zaf_learn_mode_finished();

      learn_mode_finished_or_stop();
      break;
    case EVENT_SYSTEM_FLUSHMEM_READY:
      zafi_nvm_app_reset();
      if (resetInProgress) {
        resetInProgress = false;
        /* Soft reset */
        zpal_reboot();
      } else {
        zafi_nvm_app_load_configuration();
      }
      break;
    case EVENT_SYSTEM_RESET:
      resetInProgress = true;
      if (zaf_event_distributor_is_primary_controller()) {
        DPRINT("Primary controller. Skip Device Reset Locally Notification.\n");
        set_protocol_default();
      } else {
        /* Send reset notification*/
        CC_DeviceResetLocally_notification_tx();
      }
      break;

    default:
      break;
  }
  zaf_event_distributor_app_event_manager(event);
}

static void
EventHandlerApp(void)
{
  uint8_t event;

  while (xQueueReceive(m_AppEventQueue, (uint8_t*)(&event), 0) == pdTRUE) {
    DPRINTF("Event: %d\r\n", event);
    event_manager(event);
  }
}

/**
 * Call the handler for a given table entry and pass the event and the data
 *
 * @param[in] handler_entry An entry in the map
 * @param[in] args Arguments passed to the handler. See \ref context_t.
 */
static void
call_handler(zaf_event_distributor_cc_event_handler_map_latest_t const * const handler_entry, void* args)
{
  event_cc_t *event_cc;

  event_cc = (event_cc_t*)args;
  if (handler_entry->command_class == event_cc->command_class && handler_entry->handler) {
    handler_entry->handler(event_cc->event, event_cc->data);
  }
}

static void
cc_handlers_for_each(cc_event_handler_invoker_callback_t callback, void* args)
{
  zaf_event_distributor_cc_event_handler_map_latest_t const * iter = &cc_event_handler_start;
  for (; iter < &cc_event_handler_stop; ++iter) {
    callback(iter, args);
  }
}

static void
EventHandlerCC(void)
{
  event_cc_t event_cc = { 0 };

  while (xQueueReceive(m_CCEventQueue, (uint8_t*)(&event_cc), 0) == pdTRUE) {
    DPRINTF("CC:%d Event: %d\n", event_cc.command_class, event_cc.event);
    cc_handlers_for_each(call_handler, &event_cc);
  }
}

/*
 * Initialized all modules related to event queuing, task notifying and job registering.
 */
static void
EventQueueInit(void)
{
  // Initialize Queue Notifier for events in the application.
  m_AppEventQueue = xQueueCreateStatic(
    sizeof_array(m_AppEventQueueStorage),
    sizeof(m_AppEventQueueStorage[0]),
    (uint8_t*)m_AppEventQueueStorage,
    &m_AppEventQueueObject
    );

  // Initialize Queue Notifier for events in the application.
  m_CCEventQueue = xQueueCreateStatic(
    sizeof_array(m_CCEventQueueStorage),
    sizeof(m_CCEventQueueStorage[0]),
    (uint8_t*)m_CCEventQueueStorage,
    &m_CCEventQueueObject
    );

  /*
   * Registers events with associated data, and notifies
   * the specific task about a pending job!
   */
  QueueNotifyingInit(
    &m_AppEventNotifyingQueue,
    m_AppEventQueue,
    ZAF_getAppTaskHandle(),
    EAPPLICATIONEVENT_APP);

  /*
   * Registers events with associated data, and notifies
   * the specific task about a pending job
   */
  QueueNotifyingInit(
    &m_CCEventNotifyingQueue,
    m_CCEventQueue,
    ZAF_getAppTaskHandle(),
    EAPPLICATIONEVENT_CC);

#if defined(ZAF_USE_LEGACY_JOB_HELPER)
  /*
   * Creates an internal queue to store no more than @ref JOB_QUEUE_BUFFER_SIZE jobs.
   * This module has no notification feature
   */
  ZAF_JobHelperInit();
#endif /* defined(ZAF_USE_LEGACY_JOB_HELPER) */
}

// Event distributor event handler table
static const EventDistributorEventHandler g_aEventHandlerTable[] =
{
  AppTimerNotificationHandler,  // EAPPLICATIONEVENT_TIMER
  EventHandlerZwRx,             // EAPPLICATIONEVENT_ZWRX
  EventHandlerZwCommandStatus,  // EAPPLICATIONEVENT_ZWCOMMANDSTATUS
  EventHandlerApp,              // EAPPLICATIONEVENT_APP
  EventHandlerCC,               // EAPPLICATIONEVENT_CC
};

void
zaf_event_distributor_init(void)
{
  learnModeInProgress = false;
  resetInProgress = false;

  EventQueueInit();

  EventDistributorConfig(&g_EventDistributor,
                         sizeof_array(g_aEventHandlerTable),
                         g_aEventHandlerTable, NULL);

  zafi_nvm_app_load_configuration();
}

ZW_WEAK uint8_t
zaf_event_distributor_is_primary_controller(void)
{
  return 0;
}

const SEventDistributor *
zaf_event_distributor_get(void)
{
  return &g_EventDistributor;
}

bool zaf_event_distributor_enqueue_app_event(const uint8_t event)
{
  EQueueNotifyingStatus Status;

  Status = QueueNotifyingSendToBack(&m_AppEventNotifyingQueue, &event, 0);
  if (Status != EQUEUENOTIFYING_STATUS_SUCCESS) {
    DPRINT("Failed to queue event\n");
    return false;
  }

  return true;
}

bool zaf_event_distributor_enqueue_app_event_from_isr(const uint8_t event)
{
  EQueueNotifyingStatus Status;

  Status = QueueNotifyingSendToBackFromISR(&m_AppEventNotifyingQueue, &event);
  if (Status != EQUEUENOTIFYING_STATUS_SUCCESS) {
    DPRINT("Failed to queue event\n");
    return false;
  }

  return true;
}

bool zaf_event_distributor_enqueue_cc_event(const uint16_t command_class,
                                            const uint8_t event,
                                            const void* data)
{
  EQueueNotifyingStatus Status;
  const event_cc_t event_cc = {
    .command_class = command_class,
    .event = event,
    .data = data
  };

  Status = QueueNotifyingSendToBack(&m_CCEventNotifyingQueue, (const uint8_t*) &event_cc, 0);
  if (Status != EQUEUENOTIFYING_STATUS_SUCCESS) {
    DPRINT("Failed to queue event\n");
    return false;
  }

  return true;
}

bool zaf_event_distributor_enqueue_cc_event_from_isr(const uint16_t command_class,
                                                     const uint8_t event,
                                                     const void* data)
{
  EQueueNotifyingStatus Status;
  const event_cc_t event_cc = {
    .command_class = command_class,
    .event = event,
    .data = data
  };

  Status = QueueNotifyingSendToBackFromISR(&m_CCEventNotifyingQueue, (const uint8_t*) &event_cc);
  if (Status != EQUEUENOTIFYING_STATUS_SUCCESS) {
    DPRINT("Failed to queue event\n");
    return false;
  }

  return true;
}

/**
 * @brief Transmission callback for Device Reset Locally call.
 * @param pTransmissionResult Result of each transmission.
 */
void
CC_DeviceResetLocally_done(TRANSMISSION_RESULT * pTransmissionResult)
{
  if (TRANSMISSION_RESULT_FINISHED == pTransmissionResult->isFinished) {
    set_protocol_default();
  }
}

ZW_WEAK void
zaf_event_distributor_app_zw_rx(__attribute__((unused)) SZwaveReceivePackage *RxPackage)
{
}

ZW_WEAK void
zaf_event_distributor_app_zw_command_status(__attribute__((unused)) SZwaveCommandStatusPackage *Status)
{
}

/* Register dummy entry to ensure that the section exists */
ZAF_EVENT_DISTRIBUTOR_REGISTER_CC_EVENT_HANDLER(0xFF, NULL);
