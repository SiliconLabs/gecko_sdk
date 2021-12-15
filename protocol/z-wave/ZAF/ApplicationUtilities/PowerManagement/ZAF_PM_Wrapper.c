/**
 * @file
 * @brief Power Management source file
 * @copyright 2019 Silicon Laboratories Inc.
 */
#include "ZAF_PM_Wrapper.h"
#include "ZAF_Common_interface.h"

void ZAF_PM_Register (SPowerLock_t* handle, pm_type_t type)
{
  PM_Register(handle, type);
}

void ZAF_PM_StayAwake (SPowerLock_t* handle, unsigned int msec)
{
  PM_StayAwake(handle, msec);
}

void ZAF_PM_Cancel (SPowerLock_t* handle)
{
  PM_Cancel(handle);
}

void ZAF_PM_CancelFromISR (SPowerLock_t* handle)
{
  PM_Cancel(handle);
}

void ZAF_PM_SetPowerDownCallback(void (*callback)(void))
{
  SZwaveCommandPackage FramePackage;
  EQueueNotifyingStatus status;
  FramePackage.eCommandType =  EZWAVECOMMANDTYPE_PM_SET_POWERDOWN_CALLBACK;
  FramePackage.uCommandParams.PMSetPowerDownCallback.callback = callback;
  status = QueueNotifyingSendToBack(ZAF_getAppHandle()->pZwCommandQueue,
                                    (uint8_t *)&FramePackage,
                                    0);
  ASSERT(EQUEUENOTIFYING_STATUS_SUCCESS == status);
}

void ZW_UpdateCtrlNodeInformation_API_IF (uint8_t forced)
{
  // Create transmit frame package
  SZwaveCommandPackage FramePackage;
  FramePackage.eCommandType =  EZWAVECOMMANDTYPE_ZW_UPDATE_CTRL_NODE_INFORMATION;
  FramePackage.uCommandParams.UpdateCtrlNodeInformation.value = forced;
  // Put the package on queue (and dont wait for it)
  QueueNotifyingSendToBack(ZAF_getAppHandle()->pZwCommandQueue, (uint8_t *)&FramePackage, 0);
}
