/**
 * @file
 * @copyright 2018 Silicon Laboratories Inc.
 */

#include "ZAF_Common_interface.h"
#include "zaf_protocol_config.h"
//#define DEBUGPRINT
#include "DebugPrint.h"

static SApplicationHandles * m_pAppHandles;
static zpal_pm_handle_t m_PowerLock;
static CP_Handle_t m_CmdPublisherHandle;
static zaf_wake_up_callback_t wake_up_callback;

void ZAF_setAppHandle(SApplicationHandles* pAppHandle)
{
  m_pAppHandles = pAppHandle;
}

void ZAF_setPowerLock(zpal_pm_handle_t powerLock)
{
  m_PowerLock = powerLock;
}

void ZAF_SetCPHandle(CP_Handle_t handle)
{
  m_CmdPublisherHandle = handle;
}

// getters

SApplicationHandles* ZAF_getAppHandle()
{
  ASSERT(m_pAppHandles);
  return m_pAppHandles;
}

const SProtocolInfo* ZAF_getProtocolInfo()
{
  ASSERT(m_pAppHandles);
  return m_pAppHandles->pProtocolInfo;
}

SQueueNotifying* ZAF_getZwTxQueue()
{
  ASSERT(m_pAppHandles);
  return m_pAppHandles->pZwTxQueue;
}

SQueueNotifying* ZAF_getZwCommandQueue()
{
  ASSERT(m_pAppHandles);
  return m_pAppHandles->pZwCommandQueue;
}

const zpal_radio_network_stats_t* ZAF_getNetworkStatistics()
{
  ASSERT(m_pAppHandles);
  return m_pAppHandles->pNetworkStatistics;
}

zpal_pm_handle_t ZAF_getPowerLock()
{
  ASSERT(m_PowerLock);
  return m_PowerLock;
}

uint8_t ZAF_GetSecurityKeys(void)
{
  ASSERT(m_pAppHandles);
  return m_pAppHandles->pNetworkInfo->SecurityKeys;
}

CP_Handle_t ZAF_getCPHandle()
{
  ASSERT(m_CmdPublisherHandle);
  return m_CmdPublisherHandle;
}

bool isFLiRS(__attribute__((unused)) const SAppNodeInfo_t * pAppNodeInfo)
{
  return zaf_get_app_node_info()->DeviceOptionsMask & (APPLICATION_FREQ_LISTENING_MODE_1000ms ^ APPLICATION_FREQ_LISTENING_MODE_250ms);
}

EInclusionState_t ZAF_GetInclusionState(void)
{
  ASSERT(m_pAppHandles);
  return m_pAppHandles->pNetworkInfo->eInclusionState;
}

node_id_t ZAF_GetNodeID(void)
{
  ASSERT(m_pAppHandles);
  return m_pAppHandles->pNetworkInfo->NodeId;
}

uint32_t ZAF_GetHomeID(void)
{
  ASSERT(m_pAppHandles);
  return m_pAppHandles->pNetworkInfo->HomeId;
}

node_id_t ZAF_GetSucNodeId(void)
{
  ASSERT(m_pAppHandles);
  return m_pAppHandles->pNetworkInfo->SucNodeId;
}

EInclusionMode_t ZAF_GetInclusionMode(void)
{
  node_id_t currentNodeID = ZAF_GetNodeID();

  if (currentNodeID == 0)
  {
    return EINCLUSIONMODE_NOT_SET;
  }
  else if (currentNodeID <= ZW_MAX_NODES  // Included as regular Z-Wave
      && currentNodeID > 1)  // Only controller can have node id 1.
  {
    return EINCLUSIONMODE_ZWAVE_CLS;
  }
  else if (currentNodeID >= LOWEST_LONG_RANGE_NODE_ID
      && currentNodeID <= HIGHEST_LONG_RANGE_NODE_ID)  // Included as Z-Wave Long Range
  {
    return EINCLUSIONMODE_ZWAVE_LR;
  }
  DPRINTF("NodeID %d is out of bounds and the InclusionMode cannot be determined", currentNodeID);
  return EINCLUSIONMODE_NOT_SET;
}

bool isRfRegionValid(zpal_radio_region_t region)
{
  if (REGION_US_LR >= region ||
      REGION_US_LR_END_DEVICE == region ||
      REGION_JP == region ||
      REGION_KR == region) {
    return true;
  } else {
    return false;
  }
}

void zaf_set_stay_awake_callback(zaf_wake_up_callback_t callback) {
  wake_up_callback = callback;
}

zaf_wake_up_callback_t zaf_get_stay_awake_callback(void) {
  return wake_up_callback;
}
