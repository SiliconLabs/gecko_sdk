/**
 *
 * @file
 * Power Level Command Class source file
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#include <ZW_basis_api.h>
#include <ZW_TransportSecProtocol.h>
#include <ZW_TransportEndpoint.h>
#include <AppTimer.h>
#include <SwTimer.h>
#include <QueueNotifying.h>
#include <misc.h>
#include <string.h>
#include <CC_Supervision.h>
#include <ZAF_Common_interface.h>
//#define DEBUGPRINT
#include "DebugPrint.h"
#include <zpal_radio.h>
#include "zaf_transport_tx.h"

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

static node_id_t  testNodeID = ZW_TEST_NOT_A_NODEID;
static uint8_t    testPowerLevel;
static node_id_t  testSourceNodeID;
static uint16_t   testFrameSuccessCount;
static uint8_t    testState = POWERLEVEL_TEST_NODE_REPORT_ZW_TEST_FAILED;

static SSwTimer   timerPowerLevel;
static uint8_t    timerPowerLevelSec = 0;
static SSwTimer   delayTestFrameTimer;
static uint16_t   testFrameCount;
static uint8_t    currentPower = ZPAL_RADIO_TX_POWER_DEFAULT;

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/

static void ZCB_DelayTestFrame(SSwTimer* pTimer);
static void SendTestReport(void);
static void ZCB_SendTestDone(void *callback_param);
static void ZCB_PowerLevelTimeout(SSwTimer* pTimer);
static void SetRadioAttenuation(uint8_t adjustTxPower);

/*===========================   SendTestReport   ============================
 **    Send current Powerlevel test results
 **
 **    This is an application function example
 **
 **--------------------------------------------------------------------------*/
static void
SendTestReport(void)
{
  zaf_tx_options_t tx_options = {
    .dest_node_id = testSourceNodeID,
    .source_endpoint = 0,
    .dest_endpoint = 0,
    .tx_options = ZWAVE_PLUS_TX_OPTIONS,
    .security_key = GetHighestSecureLevel(ZAF_GetSecurityKeys()),
    .bit_addressing = false,
    .use_supervision = false
  };

  ZW_APPLICATION_TX_BUFFER txBuf = {
    .ZW_PowerlevelTestNodeReportFrame.cmdClass = COMMAND_CLASS_POWERLEVEL,
    .ZW_PowerlevelTestNodeReportFrame.cmd = POWERLEVEL_TEST_NODE_REPORT,
    .ZW_PowerlevelTestNodeReportFrame.testNodeid = (uint8_t)testNodeID,   // Z-Wave only (not for Z-Wave LR)
    .ZW_PowerlevelTestNodeReportFrame.statusOfOperation = testState,
    .ZW_PowerlevelTestNodeReportFrame.testFrameCount1 = (uint8_t)(testFrameSuccessCount >> 8),
    .ZW_PowerlevelTestNodeReportFrame.testFrameCount2 = (uint8_t)testFrameSuccessCount
  };

  tx_options.use_supervision = true;

  (void) zaf_transport_tx((uint8_t*)&txBuf,
                          sizeof(txBuf.ZW_PowerlevelTestNodeReportFrame),
                          NULL, &tx_options);
}

/**
 * @brief Test frame has been transmitted to DUT and the result is noted for later reporting. If
 * not finished then another Test frame is transmitted. If all test frames has been transmitted
 * then the test is stopped and the final result is reported to the PowerlevelTest initiator.
 * @param bStatus Status of transmission.
 * @param txStatusReport Status report.
 */
static void
ZCB_SendTestDone (void *callback_param)
{

  transmission_result_t *tmp = callback_param;

  uint8_t bStatus = tmp->status;

  if (bStatus == TRANSMIT_COMPLETE_OK)
  {
    testFrameSuccessCount++;
  }

  TimerStop(&delayTestFrameTimer);

  if (testFrameCount && (--testFrameCount))
  {
    TimerStart(&delayTestFrameTimer, 40);
  }
  else
  {
    if (testFrameSuccessCount)
    {
      testState = POWERLEVEL_TEST_NODE_REPORT_ZW_TEST_SUCCES;
    }
    else
    {
      testState = POWERLEVEL_TEST_NODE_REPORT_ZW_TEST_FAILED;
    }
    SendTestReport();
  }
}

/**
 * Timer callback which makes sure that the RF transmit powerlevel is set back to
 * ZPAL_RADIO_TX_POWER_DEFAULT after the designated time period.
 */
static void
ZCB_PowerLevelTimeout (SSwTimer* pTimer)
{
  timerPowerLevelSec -= 1;
  if (0 == timerPowerLevelSec)
  {
    currentPower = ZPAL_RADIO_TX_POWER_DEFAULT; /* Reset powerlevel to ZPAL_RADIO_TX_POWER_DEFAULT */
    SetRadioAttenuation(currentPower);
    TimerStop(pTimer);
  }
}

/**
 * Starts the power level test.
 */
static void StartTest(void)
{
  testState = POWERLEVEL_TEST_NODE_REPORT_ZW_TEST_INPROGRESS;

  AppTimerRegister(&delayTestFrameTimer, false, ZCB_DelayTestFrame);
  TimerStart(&delayTestFrameTimer, 40);
}

/**
 * This function is called when the delay timer triggers.
 */
static void
ZCB_DelayTestFrame (__attribute__((unused)) SSwTimer* pTimer)
{
  SQueueNotifying* pTxQueueNotifying = ZAF_getZwTxQueue();

  // Create transmit frame package
  SZwaveTransmitPackage FramePackage = {
    .uTransmitParams.Test.DestNodeId = testNodeID,
    .uTransmitParams.Test.PowerLevel = testPowerLevel,
    .uTransmitParams.Test.Handle = ZCB_SendTestDone,
    .eTransmitType = EZWAVETRANSMITTYPE_TESTFRAME
  };

  // Put the package on queue (and dont wait for it)
  if (EQUEUENOTIFYING_STATUS_TIMEOUT == QueueNotifyingSendToBack(pTxQueueNotifying, (uint8_t*)&FramePackage, 0))
  {
      transmission_result_t rs = {
        .status = TRANSMIT_COMPLETE_FAIL,
        .isFinished = TRANSMISSION_RESULT_UNKNOWN
      };
    ZCB_SendTestDone(&rs);
  }
}

static void loadStatusPowerLevel(void)
{
  timerPowerLevelSec = 0;
}

static void loadInitStatusPowerLevel(void)
{
  testNodeID = 0;
  testPowerLevel = 0;
  testFrameCount = 0;
  testSourceNodeID = 0;
  testState = POWERLEVEL_TEST_NODE_REPORT_ZW_TEST_FAILED;

  currentPower = ZPAL_RADIO_TX_POWER_DEFAULT;
  SetRadioAttenuation(currentPower);

  timerPowerLevelSec = 0;
  // Stop the timer if active
  if (TimerIsActive(&timerPowerLevel))
  {
    TimerStop(&timerPowerLevel);
  }
}

static received_frame_status_t
CC_Powerlevel_handler(
  RECEIVE_OPTIONS_TYPE_EX *rxOpt,
  ZW_APPLICATION_TX_BUFFER *pCmd,
  __attribute__((unused)) uint8_t cmdLength,
  ZW_APPLICATION_TX_BUFFER * pFrameOut,
  uint8_t * pLengthOut)
{
  switch (pCmd->ZW_Common.cmd)
  {
    case POWERLEVEL_SET:
      if (pCmd->ZW_PowerlevelSetFrame.powerLevel > ZPAL_RADIO_TX_POWER_MINUS9_DBM)
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      if (0 == pCmd->ZW_PowerlevelSetFrame.timeout)
      {
        // A timeout value of zero is invalid.
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      AppTimerRegister(&timerPowerLevel, true, ZCB_PowerLevelTimeout);
      TimerStop(&timerPowerLevel); /* Stop any ongoing POWERLEVEL_SET operation */

      if (ZPAL_RADIO_TX_POWER_DEFAULT == pCmd->ZW_PowerlevelSetFrame.powerLevel)
      {
        // If the power level is set to normal, we ignore the timeout.
        timerPowerLevelSec = 0;
      }
      else
      {
        // Otherwise start the timer with 1 sec timeout period
        timerPowerLevelSec = pCmd->ZW_PowerlevelSetFrame.timeout;
        TimerStart(&timerPowerLevel, 1 * 1000);
      }

      /*
       * For now we just store the power level value locally without
       * actually setting the power level in the radio driver
       */
      currentPower = pCmd->ZW_PowerlevelSetFrame.powerLevel;
      SetRadioAttenuation(currentPower);
      return RECEIVED_FRAME_STATUS_SUCCESS;
    break;

    case POWERLEVEL_GET:

      if (true == Check_not_legal_response_job(rxOpt))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      pFrameOut->ZW_PowerlevelReportFrame.cmdClass = COMMAND_CLASS_POWERLEVEL;
      pFrameOut->ZW_PowerlevelReportFrame.cmd = POWERLEVEL_REPORT;
      pFrameOut->ZW_PowerlevelReportFrame.powerLevel = currentPower;
      pFrameOut->ZW_PowerlevelReportFrame.timeout = timerPowerLevelSec;

      *pLengthOut = sizeof(ZW_POWERLEVEL_REPORT_FRAME);

      return RECEIVED_FRAME_STATUS_SUCCESS;
    break;

    case POWERLEVEL_TEST_NODE_SET:
      if (POWERLEVEL_TEST_NODE_REPORT_ZW_TEST_INPROGRESS == testState) // 0x02
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      testFrameCount = (uint16_t)((((uint16_t)pCmd->ZW_PowerlevelTestNodeSetFrame.testFrameCount1) << 8)
                                  | (uint16_t)pCmd->ZW_PowerlevelTestNodeSetFrame.testFrameCount2);

      if (0 == testFrameCount)
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      testSourceNodeID = rxOpt->sourceNode.nodeId;
      testNodeID = (node_id_t)pCmd->ZW_PowerlevelTestNodeSetFrame.testNodeid;
      testPowerLevel = pCmd->ZW_PowerlevelTestNodeSetFrame.powerLevel;
      testFrameSuccessCount = 0;

      StartTest();
      return RECEIVED_FRAME_STATUS_SUCCESS;
    break;

    case POWERLEVEL_TEST_NODE_GET:
      {
        if (true == Check_not_legal_response_job(rxOpt))
        {
          /*Do not support endpoint bit-addressing */
          return RECEIVED_FRAME_STATUS_FAIL;
        }

        pFrameOut->ZW_PowerlevelTestNodeReportFrame.cmdClass = COMMAND_CLASS_POWERLEVEL;
        pFrameOut->ZW_PowerlevelTestNodeReportFrame.cmd = POWERLEVEL_TEST_NODE_REPORT;
        pFrameOut->ZW_PowerlevelTestNodeReportFrame.testNodeid = (uint8_t)testNodeID;
        pFrameOut->ZW_PowerlevelTestNodeReportFrame.statusOfOperation = testState;
        pFrameOut->ZW_PowerlevelTestNodeReportFrame.testFrameCount1 = (uint8_t)(testFrameSuccessCount >> 8);
        pFrameOut->ZW_PowerlevelTestNodeReportFrame.testFrameCount2 = (uint8_t)(testFrameSuccessCount);

        *pLengthOut = sizeof(ZW_POWERLEVEL_TEST_NODE_REPORT_FRAME);
      }
      return RECEIVED_FRAME_STATUS_SUCCESS;
    break;

    default:
      break;
  }
  return RECEIVED_FRAME_STATUS_NO_SUPPORT;
}

static void SetRadioAttenuation(uint8_t adjustTxPower)
{
  const SApplicationHandles * pAppHandle = ZAF_getAppHandle();
  SZwaveCommandPackage cmdPackage = {
    .eCommandType = EZWAVECOMMANDTYPE_ZW_SET_TX_ATTENUATION,
    .uCommandParams.SetTxAttenuation.value = adjustTxPower
  };
  EQueueNotifyingStatus QueueStatus = QueueNotifyingSendToBack(pAppHandle->pZwCommandQueue, (uint8_t *)&cmdPackage, 500);
  ASSERT(EQUEUENOTIFYING_STATUS_SUCCESS == QueueStatus);
}

static void init(void)
{
  loadStatusPowerLevel();
}

static void reset(void)
{
  loadInitStatusPowerLevel();
}

REGISTER_CC_V4(COMMAND_CLASS_POWERLEVEL, POWERLEVEL_VERSION, CC_Powerlevel_handler, NULL, NULL, NULL, 0, init, reset);
