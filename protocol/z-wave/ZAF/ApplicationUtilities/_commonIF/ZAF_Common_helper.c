/**
 * @file
 * @copyright 2018 Silicon Laboratories Inc.
 */

#include "ZAF_Common_helper.h"

#include "ZW_TransportSecProtocol.h"
#include <ZW_TransportMulticast.h>
#include <CC_Common.h>
#include "ZAF_TSE.h"
#include <ZAF_CmdPublisher.h>
#include <ZAF_PM_Wrapper.h>

//#define DEBUGPRINT
#include "DebugPrint.h"

/*
 * Max number of subscribers. Those are known so far:
 * ApplicationCommandHandler + Security Discovery + Multicast = 3
 */
#define CP_MAX_SUBSCRIBERS  3

static SPowerLock_t powerLock;

void ZAF_Init(TaskHandle_t pAppTaskHandle,
              SApplicationHandles* pAppHandle,
              const SProtocolConfig_t * pAppProtocolConfig,
              void (*updateStayAwakePeriodFunc)(void)
              )
{
  DPRINT("* ZAF_Init *\r\n");
  ZAF_setApplicationData(pAppTaskHandle, pAppHandle, pAppProtocolConfig);

  // in case of FLiRS, which is currently only DoorLock, do some additional initialization
  if (isFLiRS(ZAF_getAppNodeInfo()))
  {
    DPRINT("Initialize power lock for FLiRS \r\n");
    ZAF_setPowerLock(&powerLock);
    ZAF_PM_Register(ZAF_getPowerLock(), PM_TYPE_RADIO);
  }

  ZW_TransportMulticast_Init(NULL);
  ZW_TransportEndpoint_Init(NULL, updateStayAwakePeriodFunc);


  //Initializing TSE timers
  ZAF_TSE_Init();

  static ZAF_CP_STORAGE(content, CP_MAX_SUBSCRIBERS);
  ZAF_SetCPHandle(ZAF_CP_Init((void*) &content, CP_MAX_SUBSCRIBERS));
  if (false == ZAF_CP_SubscribeToAll(ZAF_getCPHandle(), NULL, (zaf_cp_subscriberFunction_t)ApplicationCommandHandler))
  {
    DPRINT("Subscription to Command Publisher failed!\r\n");
    ASSERT(false);
  }

  // more common function calls can be added here
}


void ZAF_FLiRS_StayAwake()
{
  DPRINT("\r\nZAF_FLiRS_StayAwake\r\n");
  ZAF_PM_StayAwake(ZAF_getPowerLock(), 2000);
}
