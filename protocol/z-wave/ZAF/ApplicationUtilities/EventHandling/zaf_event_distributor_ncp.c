/**
 * @file
 * @brief ZAF Event distributor source file
 * @copyright 2019 Silicon Laboratories Inc.
 */
#include <AppTimer.h>
#include <EventDistributor.h>
#include <SyncEvent.h>
#include <SizeOf.h>
#include <ZW_typedefs.h>
#include <ZAF_ApplicationEvents.h>
#include <ZAF_Common_helper.h>
#include <ZAF_Common_interface.h>
#include <zaf_event_distributor_ncp.h>
#include <zaf_event_helper.h>
#include <zaf_job_helper.h>
#include <ZW_TransportSecProtocol.h>

//#define DEBUGPRINT
#include "DebugPrint.h"

// Event distributor object
static SEventDistributor g_EventDistributor;

static void EventHandlerZwRx(void);
static void EventHandlerZwCommandStatus(void);

// Event distributor event handler table
static const EventDistributorEventHandler g_aEventHandlerTable[6] =
{
  EventHandlerZwRx,                         // EAPPLICATIONEVENT_ZWRX = 0
  EventHandlerZwCommandStatus,              // EAPPLICATIONEVENT_ZWCOMMANDSTATUS = 1
  zaf_event_distributor_app_state_change,   // EAPPLICATIONEVENT_STATECHANGE  = 2
  zaf_event_distributor_app_serial_data_rx, // EAPPLICATIONEVENT_SERIALDATARX = 3
  zaf_event_distributor_app_serial_timeout, // EAPPLICATIONEVENT_SERIALTIMEOUT = 4
  AppTimerNotificationHandler
};

static void EventHandlerZwRx(void)
{
  SApplicationHandles* pAppHandles;
  SZwaveReceivePackage RxPackage;

  pAppHandles = ZAF_getAppHandle();

  // Handle incoming replies
  while (xQueueReceive(pAppHandles->ZwRxQueue, (uint8_t *)(&RxPackage), 0) == pdTRUE) {
    DPRINTF("Incoming Rx %x \r\n", RxPackage.eReceiveType);

    switch (RxPackage.eReceiveType) {
#ifdef ZW_CONTROLLER_BRIDGE
      case EZWAVERECEIVETYPE_MULTI:
#endif // #ifdef ZW_CONTROLLER_BRIDGE
#ifdef ZW_SLAVE
      case EZWAVERECEIVETYPE_SECURITY_EVENT:
#endif
      case EZWAVERECEIVETYPE_STAY_AWAKE:
      case EZWAVERECEIVETYPE_NODE_UPDATE:
      case EZWAVERECEIVETYPE_SINGLE:
        break;

      default:
        DPRINTF("Invalid Receive Type: %d", RxPackage.eReceiveType);
        break;
    }

    zaf_event_distributor_app_zw_rx(&RxPackage);
  }
}

/**
 * @brief Triggered when protocol puts a message on the ZwCommandStatusQueue.
 */
static void EventHandlerZwCommandStatus(void)
{
  SApplicationHandles* pAppHandles;
  SZwaveCommandStatusPackage Status;

  pAppHandles = ZAF_getAppHandle();

  // Handle incoming replies
  while (xQueueReceive(pAppHandles->ZwCommandStatusQueue, (uint8_t*)(&Status), 0) == pdTRUE) {
    {
      DPRINTF("Incoming Status msg %x\r\n", Status.eStatusType);

      switch (Status.eStatusType) {
        case EZWAVECOMMANDSTATUS_TX:
        {
          SZWaveTransmitStatus *pTxStatus = &Status.Content.TxStatus;
          if (!pTxStatus->bIsTxFrameLegal) {
            DPRINT("Auch - not sure what to do\r\n");
          } else {
            DPRINT("Tx Status received\r\n");
            if (pTxStatus->Handle) {
              ZW_TX_Callback_t pCallback = (ZW_TX_Callback_t)pTxStatus->Handle;
              pCallback(pTxStatus->TxStatus, &pTxStatus->ExtendedTxStatus);
            }
          }

          break;
        }

#ifdef ZW_CONTROLLER
        case EZWAVECOMMANDSTATUS_REPLACE_FAILED_NODE_ID:
        case EZWAVECOMMANDSTATUS_REMOVE_FAILED_NODE_ID:
        case EZWAVECOMMANDSTATUS_NETWORK_MANAGEMENT:
#if SUPPORT_ZW_SET_SLAVE_LEARN_MODE
        case EZWAVECOMMANDSTATUS_SET_SLAVE_LEARN_MODE:
#endif
#endif
        case EZWAVECOMMANDSTATUS_LEARN_MODE_STATUS:
        case EZWAVECOMMANDSTATUS_SET_DEFAULT:
          break;

        case EZWAVECOMMANDSTATUS_INVALID_TX_REQUEST:
          DPRINTF("Invalid TX Request to protocol - %d\r\n", Status.Content.InvalidTxRequestStatus.InvalidTxRequest);
          break;

        case EZWAVECOMMANDSTATUS_INVALID_COMMAND:
          DPRINTF("Invalid command to protocol - %d\r\n", Status.Content.InvalidCommandStatus.InvalidCommand);
          break;

        default:
          DPRINTF("Unknown / Unexpected  CMD - %d\r\n", Status.eStatusType);
          break;
      }
      zaf_event_distributor_app_zw_command_status(&Status);
    }
  }
}

void zaf_event_distributor_init(void)
{
  EventDistributorConfig(
    &g_EventDistributor,
    sizeof_array(g_aEventHandlerTable),
    g_aEventHandlerTable,
    NULL);
}

const SEventDistributor *zaf_event_distributor_get(void)
{
  return &g_EventDistributor;
}

ZW_WEAK void
zaf_event_distributor_app_zw_rx(SZwaveReceivePackage *RxPackage)
{
  UNUSED(RxPackage);
}

ZW_WEAK void
zaf_event_distributor_app_zw_command_status(SZwaveCommandStatusPackage *Status)
{
  UNUSED(Status);
}
