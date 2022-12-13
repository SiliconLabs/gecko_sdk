/**
 * @file
 * Command Class Door Lock source file
 * @copyright 2019 Silicon Laboratories Inc.
 */
/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include <CC_DoorLock.h>
#include <ZW_TransportMulticast.h>
#include <string.h>
#include "ZAF_tx_mutex.h"
#include <zpal_nvm.h>
#include <ZAF_file_ids.h>
#include <ZAF_TSE.h>
#include <ZAF_nvm_app.h>
#include <ZAF_nvm.h>
#include <cc_door_lock_config_api.h>
#include <cc_door_lock_io.h>
#include <Assert.h>

//#define DEBUGPRINT
#include "DebugPrint.h"
/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/
#define SUPPORTED_OPERATIONS_LENGTH_BITMASK 0x1F  /**< Bitmask for Supported Opertation Type Length (5 bits)*/

#define CC_DOOR_LOCK_BOLT_FLAG    (1U << 1)  ///< Bitmask for bolt condition
#define CC_DOOR_LOCK_LATCH_FLAG   (1U << 2)  ///< Bitmask for latch condition

/* private function prototypes */
static void prepare_operation_report(ZW_APPLICATION_TX_BUFFER *pTxBuffer);
static void prepare_configuration_report(ZW_APPLICATION_TX_BUFFER *pTxBuffer);

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/
/**
 * Command Class Door lock
 */
cc_door_lock_data_t door_lock_data = { 0 };
/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/
/**
 * Returns current mode of the node
 * @return DOOR_MODE_SECURED if bolt is locked, DOOR_MODE_UNSECURE otherwize
 */
static door_lock_mode_t 
getCurrentMode()
{
  if(0 == (CC_DOOR_LOCK_BOLT_FLAG & door_lock_data.condition))
  {
    /* if bolt lock -> mode is DOOR_MODE_SECURED*/
    return DOOR_MODE_SECURED;
  }

  return DOOR_MODE_UNSECURE;
}

static void 
BoltLock(cc_door_lock_data_t * pDoorLock)
{
  pDoorLock->condition &= 0xFD; /* Clear bolt condition bit (0 -> bold locked) */
}

static void 
BoltUnlock(cc_door_lock_data_t * pDoorLock)
{
  pDoorLock->condition |= 0x02; /* Set bolt condition bit (1 -> bold unlocked) */
}

/**
 * @brief Stores the current status of the lock on/off
 * in the application NVM file system.
 */
static void
SaveStatus(void)
{
  bool status;

  status = cc_door_lock_write(&door_lock_data);
  ASSERT(status);
}

/**
 * Called upon receiving a Door Lock Capabilities Get frame.
 *
 * @param pData Pointer to the data that will be included in the Capabilities Report frame.
 */
static void 
CC_DoorLock_CapabilitiesGet_handler(cc_door_lock_capabilities_report_t* pData)
{
  pData->reserved = 0; // Reserved fields must be set to zero.
  pData->lengthSupportedOperationType = 0x01;
  pData->supportedOperationTypeBitmask = 1 << DOOR_OPERATION_CONST;
  pData->lengthSupportedDoorLockModeList = 2;
  pData->supportedDoorLockModeList[0] = DOOR_MODE_UNSECURE;
  pData->supportedDoorLockModeList[1] =  DOOR_MODE_SECURED;
  pData->supportedOutsideHandleModes = cc_door_lock_get_supported_outside_handles();
  pData->supportedInsideHandleModes = cc_door_lock_get_supported_inside_handles();
  pData->supportedDoorComponents = DOOR_COMPONENT_LATCH | DOOR_COMPONENT_BOLT;
  pData->autoRelockSupport = 0;
  pData->holdAndReleaseSupport = 0;
  pData->twistAssistSupport = 0;
  pData->blockToBlockSupport = 0;
}

/**
 * Called upon receiving a Door Lock Operation Set frame.
 *
 * This function supports only a subset of the door lock modes in the "Door Lock Operation Set"
 * command. The following modes are supported:
 *
 * - 0x00: Door Unsecured
 * - 0xFF: Door Secured
 * 
 * @param mode The mode that the door lock must enter upon receiving this command.
 *
 * @return CMD_HANDLER_RETURN_CODE
 */
static e_cmd_handler_return_code_t 
CC_DoorLock_OperationSet_handler(door_lock_mode_t mode)
{
  DPRINTF("\r\nCC Door Lock Operation Set - mode: %#02x\r\n", (uint8_t)mode);

  if (getCurrentMode() == mode)
  {
    //Nothing to do, return success
    DPRINTF("%s(): Already in mode %#02x\r\n", __func__, mode);
    return E_CMD_HANDLER_RETURN_CODE_HANDLED;
  }

  if (DOOR_MODE_SECURED == mode)
  {
    DPRINTF("%s(): Switch to Secured mode %#02x\r\n", __func__, mode);
    BoltLock(&door_lock_data);
  }
  else if (DOOR_MODE_UNSECURE == mode)
  {
    DPRINTF("%s(): Switch to Unsecured mode %#02x\r\n", __func__, mode);
    BoltUnlock(&door_lock_data);
  }
  else
  {
    DPRINTF("%s(): Mode %#02x not supported, failing \r\n", __func__, mode);
    //Receive mode not supported or it's a reserved value
    return E_CMD_HANDLER_RETURN_CODE_FAIL;
  }

  CC_DoorLock_update();
  SaveStatus();

  return E_CMD_HANDLER_RETURN_CODE_WORKING;
}

/**
 * Called upon receiving a Door Lock Configuration Set frame.
 *
 * This function supports only a subset of the "Door Lock Configuration Set" command.
 *
 * The following stuff can be configured:
 * - Operation type: Constant operation
 * - Outside door handles mode: Handle 1 can be enabled or disabled *
 * 
 * @param pData Pointer to the data in the Configuration Set frame.
 *
 * @return CMD_HANDLER_RETURN_CODE
 */
e_cmd_handler_return_code_t CC_DoorLock_ConfigurationSet_handler(cc_door_lock_configuration_t * pData)
{
  DPRINT("Door Lock Configuration Set\n");

  if ((DOOR_OPERATION_CONST == pData->type) &&
      !(~cc_door_lock_get_supported_inside_handles() & pData->insideDoorHandleMode) && // Fail if non-supported inside handles are set
      !(~cc_door_lock_get_supported_outside_handles() & pData->outsideDoorHandleMode) &&  // Fail if non-supported outside handles are set
      !(cc_door_lock_get_max_auto_relock_time() < ((pData->autoRelockTime1 << 8) + pData->autoRelockTime2)) && // Fail if non-supported auto-relock time
      !(cc_door_lock_get_max_hold_and_release_time() < ((pData->holdAndReleaseTime1 << 8) + pData->holdAndReleaseTime2)) && // Fail if non-supported hold and release time
      !(~cc_door_lock_get_options_flags() & pData->reservedOptionsFlags )  // Fail if non-supported options flags
     )
  {
    door_lock_data.insideDoorHandleMode  = pData->insideDoorHandleMode;
    door_lock_data.outsideDoorHandleMode = pData->outsideDoorHandleMode;

    CC_DoorLock_update();

    SaveStatus();
    return E_CMD_HANDLER_RETURN_CODE_HANDLED;
  }
  return E_CMD_HANDLER_RETURN_CODE_FAIL;
}

/**
 * Called upon receiving a Door Lock Configuration Get frame.
 *
 * @param pData Pointer to the data that will be included in the Configuration Report frame.
 */
static void
CC_DoorLock_ConfigurationGet_handler(cc_door_lock_configuration_t* pData)
{
  DPRINT("Door Lock Configuration Get\n");

  memset(pData, 0, sizeof(*pData));

  pData->type = door_lock_data.type;
  pData->insideDoorHandleMode = door_lock_data.insideDoorHandleMode;
  pData->outsideDoorHandleMode = door_lock_data.outsideDoorHandleMode;
  pData->lockTimeoutMin = DOOR_LOCK_OPERATION_SET_TIMEOUT_NOT_SUPPORTED;
  pData->lockTimeoutSec = DOOR_LOCK_OPERATION_SET_TIMEOUT_NOT_SUPPORTED;
  pData->autoRelockTime1 = 0;
  pData->autoRelockTime2 = 0;
  pData->holdAndReleaseTime1 = 0;
  pData->holdAndReleaseTime2 = 0;
  pData->reservedOptionsFlags = 0;
}

static received_frame_status_t CC_DoorLock_handler(
  RECEIVE_OPTIONS_TYPE_EX *rxOpt,
  ZW_APPLICATION_TX_BUFFER *pCmd,
  uint8_t cmdLength,
  ZW_APPLICATION_TX_BUFFER *pFrameOut,
  uint8_t * pFrameOutLength)
{
  UNUSED(pFrameOut);
  UNUSED(pFrameOutLength);
  ZAF_TRANSPORT_TX_BUFFER  TxBuf;
  ZW_APPLICATION_TX_BUFFER *pTxBuf = &(TxBuf.appTxBuf);
  TRANSMIT_OPTIONS_TYPE_SINGLE_EX *pTxOptionsEx;
  UNUSED(cmdLength);
  e_cmd_handler_return_code_t return_code;
  switch (pCmd->ZW_Common.cmd)
  {

    case DOOR_LOCK_OPERATION_SET_V4:
      return_code = CC_DoorLock_OperationSet_handler(pCmd->ZW_DoorLockOperationSetV2Frame.doorLockMode);

      /* If handler has finished, call TSE */
      if (E_CMD_HANDLER_RETURN_CODE_FAIL == return_code || E_CMD_HANDLER_RETURN_CODE_HANDLED == return_code)
      {
        // Build up new CC data structure
        void* pZAF_TSE_doorLockData = CC_Doorlock_prepare_zaf_tse_data(rxOpt);
        if (false == ZAF_TSE_Trigger(CC_DoorLock_operation_report_stx, pZAF_TSE_doorLockData, true))
        {
          DPRINTF("%s(): ZAF_TSE_Trigger failed\n", __func__);
        }
      }
      else if (E_CMD_HANDLER_RETURN_CODE_WORKING == return_code)
      {
       /* If the status is working, inform the application so it can make the TSE trigger later on */
        CC_DoorLock_operation_report_notifyWorking(rxOpt);
      }

      if (E_CMD_HANDLER_RETURN_CODE_FAIL == return_code)
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      break;

    case DOOR_LOCK_OPERATION_GET_V4:
      if (true == Check_not_legal_response_job(rxOpt))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      RxToTxOptions(rxOpt, &pTxOptionsEx);
      prepare_operation_report(pTxBuf);

      if(ZAF_ENQUEUE_STATUS_SUCCESS != Transport_SendResponseEP(
          (uint8_t *)pTxBuf,
          sizeof(ZW_DOOR_LOCK_OPERATION_REPORT_V4_FRAME),
          pTxOptionsEx,
          NULL))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      break;

    case DOOR_LOCK_CONFIGURATION_SET_V2:
      return_code = CC_DoorLock_ConfigurationSet_handler(
          (cc_door_lock_configuration_t *)&(pCmd->ZW_DoorLockConfigurationSetV2Frame.operationType));

      if(E_CMD_HANDLER_RETURN_CODE_FAIL == return_code || E_CMD_HANDLER_RETURN_CODE_HANDLED == return_code)
      {
        // Build up new CC data structure
        void* pZAF_TSE_doorLockData = CC_Doorlock_prepare_zaf_tse_data(rxOpt);
        if (false == ZAF_TSE_Trigger(CC_DoorLock_configuration_report_stx, pZAF_TSE_doorLockData, true))
        {
          DPRINTF("%s(): ZAF_TSE_Trigger failed\n", __func__);
        }
      }

      if (E_CMD_HANDLER_RETURN_CODE_FAIL == return_code)
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      break;

    case DOOR_LOCK_CONFIGURATION_GET_V2:
      if (true == Check_not_legal_response_job(rxOpt))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      RxToTxOptions(rxOpt, &pTxOptionsEx);
      prepare_configuration_report(pTxBuf);

      if(ZAF_ENQUEUE_STATUS_SUCCESS != Transport_SendResponseEP(
          (uint8_t *)pTxBuf,
          sizeof(ZW_DOOR_LOCK_CONFIGURATION_REPORT_V4_FRAME),
          pTxOptionsEx,
          NULL))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      break;

    case DOOR_LOCK_CAPABILITIES_GET_V4:
      if (true == Check_not_legal_response_job(rxOpt))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      memset((uint8_t*)pTxBuf, 0, sizeof(ZW_APPLICATION_TX_BUFFER) );

      RxToTxOptions(rxOpt, &pTxOptionsEx);
      pTxBuf->ZW_DoorLockCapabilitiesReport1byteV4Frame.cmdClass = COMMAND_CLASS_DOOR_LOCK_V4;
      pTxBuf->ZW_DoorLockCapabilitiesReport1byteV4Frame.cmd = DOOR_LOCK_CAPABILITIES_REPORT_V4;
      cc_door_lock_capabilities_report_t capabilities_report;
      memset((uint8_t *)&capabilities_report, 0x00, sizeof(capabilities_report));
      CC_DoorLock_CapabilitiesGet_handler(&capabilities_report);
      pTxBuf->ZW_DoorLockCapabilitiesReport1byteV4Frame.properties1 = 1 & SUPPORTED_OPERATIONS_LENGTH_BITMASK; // Length fixed to 1
      uint8_t *ptr = &pTxBuf->ZW_DoorLockCapabilitiesReport1byteV4Frame.supportedOperationTypeBitMask1;
      *ptr++ = capabilities_report.supportedOperationTypeBitmask;
      *ptr++ = capabilities_report.lengthSupportedDoorLockModeList;
      for (unsigned int i = 0; i < capabilities_report.lengthSupportedDoorLockModeList; i++)
      {
        *ptr++ = capabilities_report.supportedDoorLockModeList[i];
      }
      *ptr++ = (uint8_t)((capabilities_report.supportedOutsideHandleModes << 4) | capabilities_report.supportedInsideHandleModes);
      *ptr++ = capabilities_report.supportedDoorComponents;
      *ptr++ = (uint8_t)((capabilities_report.autoRelockSupport << 3)
                       | (capabilities_report.holdAndReleaseSupport << 2)
                       | (capabilities_report.twistAssistSupport << 1)
                       |  capabilities_report.blockToBlockSupport);
      size_t send_length = (size_t)(ptr - (uint8_t*)pTxBuf);
      if(ZAF_ENQUEUE_STATUS_SUCCESS != Transport_SendResponseEP(
          (uint8_t *)pTxBuf,
          send_length,
          pTxOptionsEx,
          NULL))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      break;
    default:
      return RECEIVED_FRAME_STATUS_NO_SUPPORT;
  }
  return RECEIVED_FRAME_STATUS_SUCCESS;
}

/**
 * Prepares payload for operation report to be sent
 * @param pTxBuffer Output payload
 */
static void prepare_operation_report(ZW_APPLICATION_TX_BUFFER *pTxBuffer)
{
  memset((uint8_t*)pTxBuffer, 0, sizeof(ZW_APPLICATION_TX_BUFFER) );

  pTxBuffer->ZW_DoorLockOperationReportV4Frame.cmdClass = COMMAND_CLASS_DOOR_LOCK_V4;
  pTxBuffer->ZW_DoorLockOperationReportV4Frame.cmd = DOOR_LOCK_OPERATION_REPORT_V4;
  cc_door_lock_operation_report_t operation_report;
  CC_DoorLock_OperationGet_handler(&operation_report);
  pTxBuffer->ZW_DoorLockOperationReportV4Frame.currentDoorLockMode = (uint8_t)operation_report.mode;
  pTxBuffer->ZW_DoorLockOperationReportV4Frame.properties1 =
      (uint8_t)((operation_report.outsideDoorHandleMode << 4) | operation_report.insideDoorHandleMode);
  pTxBuffer->ZW_DoorLockOperationReportV4Frame.doorCondition = operation_report.condition;
  pTxBuffer->ZW_DoorLockOperationReportV4Frame.lockTimeoutMinutes = operation_report.lockTimeoutMin;
  pTxBuffer->ZW_DoorLockOperationReportV4Frame.lockTimeoutSeconds = operation_report.lockTimeoutSec;
  pTxBuffer->ZW_DoorLockOperationReportV4Frame.targetDoorLockMode = operation_report.targetMode;
  pTxBuffer->ZW_DoorLockOperationReportV4Frame.duration = operation_report.duration;
}

/**
 * Prepares payload for configuration report to be sent
 * @param pTxBuffer Output payload
 */

static void prepare_configuration_report(ZW_APPLICATION_TX_BUFFER *pTxBuffer)
{
  memset((uint8_t*)pTxBuffer, 0, sizeof(ZW_APPLICATION_TX_BUFFER) );

  pTxBuffer->ZW_DoorLockConfigurationReportV4Frame.cmdClass = COMMAND_CLASS_DOOR_LOCK_V4;
  pTxBuffer->ZW_DoorLockConfigurationReportV4Frame.cmd = DOOR_LOCK_CONFIGURATION_REPORT_V4;
  cc_door_lock_configuration_t configuration;
  CC_DoorLock_ConfigurationGet_handler(&configuration);
  pTxBuffer->ZW_DoorLockConfigurationReportV4Frame.operationType = configuration.type;
  pTxBuffer->ZW_DoorLockConfigurationReportV4Frame.properties1 =
      (uint8_t)((configuration.outsideDoorHandleMode << 4) | configuration.insideDoorHandleMode);
  pTxBuffer->ZW_DoorLockConfigurationReportV4Frame.lockTimeoutMinutes = configuration.lockTimeoutMin;
  pTxBuffer->ZW_DoorLockConfigurationReportV4Frame.lockTimeoutSeconds = configuration.lockTimeoutSec;
  pTxBuffer->ZW_DoorLockConfigurationReportV4Frame.autoRelockTime1 = configuration.autoRelockTime1;
  pTxBuffer->ZW_DoorLockConfigurationReportV4Frame.autoRelockTime2 = configuration.autoRelockTime2;
  pTxBuffer->ZW_DoorLockConfigurationReportV4Frame.holdAndReleaseTime1 = configuration.holdAndReleaseTime1;
  pTxBuffer->ZW_DoorLockConfigurationReportV4Frame.holdAndReleaseTime2 = configuration.holdAndReleaseTime2;
  pTxBuffer->ZW_DoorLockConfigurationReportV4Frame.properties2 = configuration.reservedOptionsFlags;
}

/*
 * This function converts the command from being a Basic Set command (not shown here)
 * to becoming a command for this Command Class.
 *
 * After this function is called by Basic CC, the handler function of this CC is called
 * to execute the command held in this frame.
 */
static void basic_set_mapper(ZW_APPLICATION_TX_BUFFER* pFrame)
{
  // All of the different types of frames start by having the command class and command in the first two bytes.
  pFrame->ZW_DoorLockOperationSetV4Frame.cmdClass = COMMAND_CLASS_DOOR_LOCK;
  pFrame->ZW_DoorLockOperationSetV4Frame.cmd      = DOOR_LOCK_OPERATION_SET;
}

/*
 * Maps Basic Get/Report to CC Door Lock in accordance with DT:01.11.0004.1.
 */
static void basic_get_mapper(uint8_t endpoint,
                             uint8_t * p_current_value,
                             uint8_t * p_target_value,
                             uint8_t * p_duration)
{
  UNUSED(endpoint); // Ignore endpoint as this implementation of CC Door Lock doesn't support endpoints.
  *p_current_value = (getCurrentMode() == DOOR_MODE_UNSECURE) ? 0x00 : 0xFF;

  /*
   * Target value is not covered by DT:01.11.0004.1 and since this CC doesn't specify any transition
   * value, the target value is set to the current value.
   */
  *p_target_value  = *p_current_value;

  // No transition, hence duration is set to zero.
  *p_duration = 0;
}

static uint8_t lifeline_reporting(ccc_pair_t * p_ccc_pair)
{
  p_ccc_pair->cmdClass = COMMAND_CLASS_DOOR_LOCK;
  p_ccc_pair->cmd      = DOOR_LOCK_OPERATION_REPORT;
  p_ccc_pair++;
  p_ccc_pair->cmdClass = COMMAND_CLASS_DOOR_LOCK;
  p_ccc_pair->cmd      = DOOR_LOCK_CONFIGURATION_REPORT;
  return 2;
}

static void reset(void)
{
  bool status;

  memset(&door_lock_data, 0x00, sizeof(door_lock_data));
  door_lock_data.type = cc_door_lock_get_operation_type();;
  door_lock_data.insideDoorHandleMode  = cc_door_lock_get_supported_inside_handles();  /* all supported inside handles enabled */
  door_lock_data.outsideDoorHandleMode = cc_door_lock_get_supported_outside_handles();  /* all supported outside handles enabled */
  door_lock_data.lockTimeoutMin = DOOR_LOCK_OPERATION_SET_TIMEOUT_NOT_SUPPORTED;
  door_lock_data.lockTimeoutSec = DOOR_LOCK_OPERATION_SET_TIMEOUT_NOT_SUPPORTED;
  door_lock_data.outsideDoorHandleState = 0; /* Handles not being pressed */
  door_lock_data.insideDoorHandleState = 0; /* Handles not being pressed */
  door_lock_data.condition = CC_DOOR_LOCK_BOLT_FLAG; /*Set bolt unsecured by default. (must clear reserved bits 7..3) */

  status = cc_door_lock_write(&door_lock_data);
  ASSERT(status);

  CC_DoorLock_update();
}

static void init(void)
{
  bool status;
  cc_door_lock_data_t savedDoorLock;

  cc_door_lock_migrate();

  status = cc_door_lock_read(&savedDoorLock);

  if(status) {
    door_lock_data.condition = savedDoorLock.condition;
    door_lock_data.type = savedDoorLock.type;
    door_lock_data.insideDoorHandleMode = savedDoorLock.insideDoorHandleMode;
    door_lock_data.outsideDoorHandleMode = savedDoorLock.outsideDoorHandleMode;
    /* NB: Door handle states (insideDoorHandleState and outsideDoorHandleState)
     * are not really part of the configuration. For that reason we do not
     * set them here even though they are part of the saved config data.
     */
    door_lock_data.lockTimeoutMin = savedDoorLock.lockTimeoutMin;
    door_lock_data.lockTimeoutSec = savedDoorLock.lockTimeoutSec;

    CC_DoorLock_update();
  } else {
    reset();
  }
}

JOB_STATUS CC_DoorLock_OperationReport_tx(
  AGI_PROFILE* pProfile,
  uint8_t sourceEndpoint,
  cc_door_lock_operation_report_t* pData,
  void(*pCallback)(TRANSMISSION_RESULT * pTransmissionResult))
{
  CMD_CLASS_GRP cmdGrp = {COMMAND_CLASS_DOOR_LOCK_V2, DOOR_LOCK_OPERATION_REPORT_V2};

  return cc_engine_multicast_request(
      pProfile,
      sourceEndpoint,
      &cmdGrp,
      (uint8_t*)pData,
      sizeof(cc_door_lock_operation_report_t),
      true,
      pCallback);
}

void CC_DoorLock_operation_report_stx(TRANSMIT_OPTIONS_TYPE_SINGLE_EX txOptions, void* pData)
{
  UNUSED(pData);
  DPRINTF("* %s() *\n"
      "\ttxOpt.src = %d\n"
      "\ttxOpt.options %#02x\n"
      "\ttxOpt.secOptions %#02x\n",
      __func__, txOptions.sourceEndpoint, txOptions.txOptions, txOptions.txSecOptions);

  /* Prepare payload for report */
  ZAF_TRANSPORT_TX_BUFFER  TxBuf;
  ZW_APPLICATION_TX_BUFFER *pTxBuf = &(TxBuf.appTxBuf);
  prepare_operation_report(pTxBuf);

  if (ZAF_ENQUEUE_STATUS_SUCCESS != Transport_SendRequestEP((uint8_t *)pTxBuf,
                                                                sizeof(ZW_DOOR_LOCK_OPERATION_REPORT_V4_FRAME),
                                                                &txOptions,
                                                                ZAF_TSE_TXCallback))
  {
    //sending request failed
    DPRINTF("%s(): Transport_SendRequestEP() failed. \n", __func__);
  }
}

void CC_DoorLock_configuration_report_stx(TRANSMIT_OPTIONS_TYPE_SINGLE_EX txOptions, void* pData)
{
  UNUSED(pData);
  DPRINTF("* %s() *\n"
      "\ttxOpt.src = %d\n"
      "\ttxOpt.options %#02x\n"
      "\ttxOpt.secOptions %#02x\n",
      __func__, txOptions.sourceEndpoint, txOptions.txOptions, txOptions.txSecOptions);

  /* Prepare payload for report */
  ZAF_TRANSPORT_TX_BUFFER  TxBuf;
  ZW_APPLICATION_TX_BUFFER *pTxBuf = &(TxBuf.appTxBuf);
  prepare_configuration_report(pTxBuf);

  if (ZAF_ENQUEUE_STATUS_SUCCESS != Transport_SendRequestEP((uint8_t *)pTxBuf,
                                                                sizeof(ZW_DOOR_LOCK_CONFIGURATION_REPORT_V4_FRAME),
                                                                &txOptions,
                                                                ZAF_TSE_TXCallback))
  {
    //sending request failed
    DPRINTF("%s(): Transport_SendRequestEP() failed. \n", __func__);
  }
}

void CC_DoorLock_OperationGet_handler(cc_door_lock_operation_report_t* pData)
{
  DPRINT("\r\nCC Door Lock Operation Get");

  pData->mode = getCurrentMode();
  // Inside- and Outside Door Handle Mode must always report 0 if the current lock mode == SECURED
  pData->insideDoorHandleMode = pData->mode == DOOR_MODE_SECURED ? 0 : door_lock_data.insideDoorHandleMode;
  pData->outsideDoorHandleMode = pData->mode == DOOR_MODE_SECURED ? 0 : door_lock_data.outsideDoorHandleMode;
  pData->condition = door_lock_data.condition;
  pData->lockTimeoutMin = DOOR_LOCK_OPERATION_SET_TIMEOUT_NOT_SUPPORTED;
  pData->lockTimeoutSec = DOOR_LOCK_OPERATION_SET_TIMEOUT_NOT_SUPPORTED;
  pData->targetMode = pData->mode; // Assuming instantaneous lock state change, target and current mode always equal
  pData->duration = 0; // Duration is always 0 with instantaneous lock state change
}

void CC_DoorLock_SetOutsideDoorHandleState(cc_door_lock_handle_t handle)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
  door_lock_data.outsideDoorHandleState |= handle;
  DPRINTF("outsideDoorHandleState %d\r\n", (door_lock_data.outsideDoorHandleState & handle));
#pragma GCC diagnostic pop

  CC_DoorLock_update();
  SaveStatus();
}

void CC_DoorLock_ClearOutsideDoorHandleState(cc_door_lock_handle_t handle)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
  door_lock_data.outsideDoorHandleState &= ~(handle);
#pragma GCC diagnostic pop
  DPRINTF("outsideDoorHandleState %d\r\n", (door_lock_data.outsideDoorHandleState & handle));

  CC_DoorLock_update();
  SaveStatus();
}

void 
CC_DoorLock_Toggle(void)
{
  door_lock_mode_t door_lock_mode = (DOOR_MODE_SECURED == getCurrentMode()) ? DOOR_MODE_UNSECURE : DOOR_MODE_SECURED;
  CC_DoorLock_OperationSet_handler(door_lock_mode);
}

void
CC_DoorLock_update(void)
{
  /*
   * Mode bit 0 value == 1  --> handle #1 can open the door
   * State bit 0 value == 1 --> handle #1 is activated
   */
  if((door_lock_data.outsideDoorHandleMode & 0x01) && (door_lock_data.outsideDoorHandleState & 0x01))
  {
    door_lock_data.condition &=  (uint8_t) ~(CC_DOOR_LOCK_LATCH_FLAG);
  }
  else
  {
    door_lock_data.condition |=  CC_DOOR_LOCK_LATCH_FLAG;
  }

  DPRINTF("SetCondition con = %d\r\n", door_lock_data.condition);

  if(CC_DOOR_LOCK_LATCH_FLAG & door_lock_data.condition)
  {
    cc_door_lock_latch_status_handler(false);
    DPRINT("Latch closed\r\n");
  }
  else
  {
    cc_door_lock_latch_status_handler(true);
    DPRINT("Latch open\r\n");
  }

  if(CC_DOOR_LOCK_BOLT_FLAG & door_lock_data.condition)
  {
    cc_door_lock_bolt_status_handler(false);
    DPRINT("Bolt unlocked\r\n");
  }
  else
  {
    cc_door_lock_bolt_status_handler(true);
    DPRINT("Bolt locked\r\n");
  }
}

ZW_WEAK void
cc_door_lock_latch_status_handler(bool opened)
{
  UNUSED(opened);
}

ZW_WEAK void
cc_door_lock_bolt_status_handler(bool locked)
{
  UNUSED(locked);
}

/*
 * This will map this CC to Basic CC, so set commands by Basic CC can be routed to this Command Class for execution.
 */
REGISTER_CC_V4(COMMAND_CLASS_DOOR_LOCK, DOOR_LOCK_VERSION_V4, CC_DoorLock_handler, basic_set_mapper, basic_get_mapper, lifeline_reporting, 0, init, reset);
