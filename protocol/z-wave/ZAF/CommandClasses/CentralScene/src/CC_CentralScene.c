/**
 * @file CC_CentralScene.c
 * @brief Handler for Command Class Central Scene.
 * @copyright 2018 Silicon Laboratories Inc.
 */

#include <ZW_TransportLayer.h>
#include <CC_CentralScene.h>
#include "cc_central_scene_io.h"
#include <string.h>

//#define DEBUGPRINT
#include "DebugPrint.h"
#include <ZAF_TSE.h>
#include "AppTimer.h"
#include "zaf_transport_tx.h"

s_CC_centralScene_data_t centralSceneData = { 0 };

static central_scene_configuration_t cc_central_scene_configuration = { 0 };

static uint8_t sequenceNumber = 0;

/// Timer used to send consecutive CENTRAL_SCENE_NOTIFICATION
static SSwTimer central_scene_notification_timer = { 0 };

/// Holds the number of last active scene
/// Used for sending CENTRAL_SCENE_NOTIFICATION
/// when CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_HELD_DOWN event happen
static uint8_t last_scene_number;

static void prepare_configuration_report(ZW_APPLICATION_TX_BUFFER *pTxBuffer);
static uint8_t get_supported_key_attributes(ZW_CENTRAL_SCENE_SUPPORTED_REPORT_1BYTE_V3_FRAME * pData);
static void central_scene_notification_timer_cb(SSwTimer *pTimer);
static void CC_CentralScene_configuration_report_stx(zaf_tx_options_t *tx_options, void* pData);

static received_frame_status_t
CC_CentralScene_handler(
  RECEIVE_OPTIONS_TYPE_EX *rxOpt,
  ZW_APPLICATION_TX_BUFFER *pCmd,
  __attribute__((unused)) uint8_t cmdLength,
  ZW_APPLICATION_TX_BUFFER *pFrameOut,
  uint8_t * pFrameOutLength)
{
  switch (pCmd->ZW_Common.cmd)
  {
    case CENTRAL_SCENE_SUPPORTED_GET_V2:
      if (false == Check_not_legal_response_job(rxOpt))
      {
        size_t numberOfBytesWithKeyAttributes = get_supported_key_attributes(
            &(pFrameOut->ZW_CentralSceneSupportedReport1byteV3Frame));

        pFrameOut->ZW_CentralSceneSupportedReport1byteV3Frame.cmdClass = COMMAND_CLASS_CENTRAL_SCENE_V3;
        pFrameOut->ZW_CentralSceneSupportedReport1byteV3Frame.cmd = CENTRAL_SCENE_SUPPORTED_REPORT_V3;
        // Forced to always support slow refresh.
        pFrameOut->ZW_CentralSceneSupportedReport1byteV3Frame.properties1 |= 0x80;
        *pFrameOutLength = sizeof(ZW_CENTRAL_SCENE_SUPPORTED_REPORT_1BYTE_V3_FRAME) - 4 + numberOfBytesWithKeyAttributes;

        return RECEIVED_FRAME_STATUS_SUCCESS;
      }
      return RECEIVED_FRAME_STATUS_FAIL;
      break;

    case CENTRAL_SCENE_CONFIGURATION_GET_V3:
      if (false == Check_not_legal_response_job(rxOpt))
      {
        prepare_configuration_report(pFrameOut);
        *pFrameOutLength = sizeof(ZW_CENTRAL_SCENE_CONFIGURATION_REPORT_V3_FRAME);

        return RECEIVED_FRAME_STATUS_SUCCESS;
      }
      return RECEIVED_FRAME_STATUS_FAIL;
      break;

    case CENTRAL_SCENE_CONFIGURATION_SET_V3:
    {
      central_scene_configuration_t configuration = {
        .slowRefresh = (pCmd->ZW_CentralSceneConfigurationSetV3Frame.properties1 >> 7)
      };

      cc_central_scene_write(&configuration);
      cc_central_scene_configuration.slowRefresh = configuration.slowRefresh;

      // Build up new CC data structure
      memset(&centralSceneData, 0, sizeof(centralSceneData));
      centralSceneData.rxOptions = *rxOpt;

      if (false == ZAF_TSE_Trigger(CC_CentralScene_configuration_report_stx,
                                    (void *)&centralSceneData,
                                    true))
      {
        DPRINTF("%s(): ZAF_TSE_Trigger failed\n", __func__);
      }
    }
    return RECEIVED_FRAME_STATUS_SUCCESS;
    break;
  }
  return RECEIVED_FRAME_STATUS_NO_SUPPORT;
}

JOB_STATUS
cc_central_scene_notification_tx(
    AGI_PROFILE* pProfile,
    uint8_t keyAttribute,
    uint8_t sceneNumber,
    ZAF_TX_Callback_t pCbFunc)
{
  ccc_pair_t ccc_pair = {COMMAND_CLASS_CENTRAL_SCENE_V3, CENTRAL_SCENE_NOTIFICATION_V3};
  uint8_t payload[] = {
    sequenceNumber++,
    (uint8_t)((cc_central_scene_configuration.slowRefresh << 7) | (keyAttribute & 0x87)),
    sceneNumber
  };

  return cc_engine_multicast_request(
      pProfile,
      ENDPOINT_ROOT,
      &ccc_pair,
      payload,
      sizeof(payload),
      true,
      pCbFunc);
}

/**
 * Send report when change happen via lifeLine.
 *
 * Callback used by TSE module. Refer to @ref ZAF_TSE.h for more details.
 *
 * @param txOptions txOptions
 * @param pData Command payload for the report
 */
static void
CC_CentralScene_configuration_report_stx(zaf_tx_options_t *tx_options, __attribute__((unused)) void* pData)
{
  DPRINTF("* %s() *\n"
      "\ttxOpt.src = %d\n"
      "\ttxOpt.options %#02x\n",
      __func__, tx_options->source_endpoint, tx_options->tx_options);

  /* Prepare payload for report */
  ZW_APPLICATION_TX_BUFFER txBuf = { 0 };

  prepare_configuration_report(&txBuf);
  tx_options->use_supervision = true;

  (void) zaf_transport_tx((uint8_t *)&txBuf,
                          sizeof(ZW_CENTRAL_SCENE_CONFIGURATION_REPORT_V3_FRAME),
                          ZAF_TSE_TXCallback,
                          tx_options);
}

static void reset(void)
{
  cc_central_scene_configuration.slowRefresh = 1; // CC:005B.03.00.21.001 - Slow refresh must be enabled after inclusion
  cc_central_scene_write(&cc_central_scene_configuration);
}

static void init(void)
{
  central_scene_configuration_t saved_configuration = { 0 };
  cc_central_scene_migrate();

  bool status = cc_central_scene_read(&saved_configuration);
  if(status)
  {
    cc_central_scene_configuration.slowRefresh = saved_configuration.slowRefresh;
  }
  else
  {
    reset();
  }

  AppTimerRegister(&central_scene_notification_timer, true, central_scene_notification_timer_cb);
}

static void prepare_configuration_report(ZW_APPLICATION_TX_BUFFER *pTxBuffer)
{
  memset(pTxBuffer, 0, sizeof(*pTxBuffer) );

  pTxBuffer->ZW_CentralSceneConfigurationReportV3Frame.cmdClass = COMMAND_CLASS_CENTRAL_SCENE_V3;
  pTxBuffer->ZW_CentralSceneConfigurationReportV3Frame.cmd = CENTRAL_SCENE_CONFIGURATION_REPORT_V3;
  pTxBuffer->ZW_CentralSceneConfigurationReportV3Frame.properties1 = ((uint8_t) (cc_central_scene_configuration.slowRefresh << 7));

}

/**
 * Prepares a payload for CENTRAL_SCENE_SUPPORTED_REPORT
 * @param[out] pData pointer to output data
 * @return length of the paylpad
 */
static uint8_t get_supported_key_attributes(ZW_CENTRAL_SCENE_SUPPORTED_REPORT_1BYTE_V3_FRAME * pData)
{
  pData->supportedScenes = cc_central_scene_config_get_number_of_scenes(); // Number of buttons
  uint8_t identical = cc_central_scene_config_get_identical();
  pData->properties1 = 0;
  pData->properties1 |= (identical << 0);  //Indicates that all keys are identical. Using different key attributes are not supported currently in the applications
  uint8_t size_of_supported_key_attributes = CC_CENTRAL_SCENE_SIZE_OF_SUPPORTED_SCENES_ATTRIBUTES; // This value is hardcoded to work with WallController, represents "sizeof(CC_CENTRAL_SCENE_SUPPORTED_SCENES_SCENE_1)"
  pData->properties1 |= (size_of_supported_key_attributes << 1); //This field advertises the size of each “Supported Key Attributes” field measured in bytes
  pData->variantgroup1.supportedKeyAttributesForScene1 = cc_central_scene_config_get_attribute_bitmask(1);  // By default "Key Pressed 1 time", "Key Released", and "Key Held Down" are the supported scenes
  // If scenes are not identical, add supported attributes for all scenes.
  if (!identical && (pData->supportedScenes > 0)) {
    uint8_t *p = &pData->variantgroup1.supportedKeyAttributesForScene1;
    // Start from scene 2
    for (int i = 2; i <= pData->supportedScenes; i++) {
      *(++p) = cc_central_scene_config_get_attribute_bitmask(i);
    }
    return pData->supportedScenes * size_of_supported_key_attributes;
  }
  // Scenes identical or only one scene is supported
  return size_of_supported_key_attributes;
}

void
cc_central_scene_handle_notification_timer(
    bool start_timer,
    uint8_t scene_number)
{
  DPRINTF("%s timer scene %d\n", start_timer? "start":"stop", scene_number);

  if (start_timer) {
    last_scene_number = scene_number;
    TimerStart(&central_scene_notification_timer,
               (0 == cc_central_scene_configuration.slowRefresh) ? 200 : 55000);
  } else {
    // Clear saved scene number
    if(scene_number != last_scene_number) {
      // Should never happen
      DPRINTF("Warning: Last scene number is %d, now received %d\n", last_scene_number, scene_number);
    }
    last_scene_number = 0;
    TimerStop(&central_scene_notification_timer);
  }

}

static void
central_scene_notification_timer_cb(__attribute__((unused)) SSwTimer *pTimer)
{
  // This function is only triggered if timer expired while the key was held down
  (void) cc_central_scene_notification_tx(
      NULL,
      CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_HELD_DOWN_V2,
      last_scene_number,
      NULL);

  // restart timer automatically. App will stop the timer when the button is released.
  TimerStart(&central_scene_notification_timer,
             (0 == cc_central_scene_configuration.slowRefresh) ? 200 : 55000);
}

static uint8_t lifeline_reporting(ccc_pair_t * p_ccc_pair)
{
  p_ccc_pair->cmdClass = COMMAND_CLASS_CENTRAL_SCENE;
  p_ccc_pair->cmd      = CENTRAL_SCENE_NOTIFICATION;
  p_ccc_pair++;
  p_ccc_pair->cmdClass = COMMAND_CLASS_CENTRAL_SCENE;
  p_ccc_pair->cmd      = CENTRAL_SCENE_CONFIGURATION_REPORT_V3;
  return 2;
}

/*
 * This will map this CC to Basic CC, so set commands by Basic CC can be routed to this Command Class for execution.
 */
REGISTER_CC_V4(COMMAND_CLASS_CENTRAL_SCENE, CENTRAL_SCENE_VERSION_V3, CC_CentralScene_handler, NULL, NULL, lifeline_reporting, 0, init, reset);
