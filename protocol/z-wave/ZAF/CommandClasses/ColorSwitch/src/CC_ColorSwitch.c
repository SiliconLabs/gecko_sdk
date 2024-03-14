/**
 * @file
 * Handler for Command Class Color Switch.
 * @copyright 2020 Silicon Laboratories Inc.
 */

#include "CC_ColorSwitch.h"
#include <misc.h>
#include <string.h>
#include <cc_color_switch_config_api.h>
#include <cc_color_switch_io.h>
#include <CC_Supervision.h>
#include <ZAF_TSE.h>
#include <Assert.h>
//#define DEBUGPRINT
#include <DebugPrint.h>
#include "ZW_TransportEndpoint.h"
#include "zaf_transport_tx.h"

/**< Pointer to array of supported colors defined in the app */
static s_colorComponent *pColorComponents;
/**< Number of supported colors in pColorComponents */
static uint8_t colorsSupportedCount = 0;
/**< bitmask of colors that changes currently. Used to check if there is active change for any color */
static uint16_t colorsChangingBitmask;

static uint16_t colorsComponentsMask(uint8_t endpoint);
static s_colorComponent* findColorComponentByColorID(uint8_t colorId, uint8_t endpoint);
static int16_t findColorComponentIndexByObj(s_Actuator *pObj);
static void CC_ColorSwitch_ColorChanged_cb(s_Actuator *pObj);
static void CC_ColorSwitch_report_stx(zaf_tx_options_t *tx_options, void* pData);

/**
 * Optional. Can be used as single cb function for all colors. Defined in the app.
 * Called when change takes place in driver and app needs to update LED status
 */
ZW_WEAK void cc_color_switch_refresh_cb()
{
}

typedef void (*color_callback_t)(s_colorComponent *colorComponent);

/**
 * Initializes data needed for Color Switch CC, including setting supported colors in colorSwitch_colorsSupported
 */
static void init_and_reset(void)
{
  uint8_t durationDefault;

  colorsChangingBitmask = 0;
  pColorComponents = cc_color_switch_get_colorComponents();
  colorsSupportedCount = cc_color_switch_get_length_colorComponents();
  durationDefault = cc_color_switch_get_default_duration();

  ASSERT(pColorComponents);

  if (0 == colorsSupportedCount || colorsSupportedCount > ECOLORCOMPONENT_COLOR_UNDEFINED)
  {
    ASSERT(false);
  }
  for (uint8_t i = 0; i < colorsSupportedCount; i++)
  {
    ZAF_Actuator_Init(&pColorComponents[i].obj, 0 , 0xFF, 20, durationDefault, &CC_ColorSwitch_ColorChanged_cb);
    // Try to read the color switch data.
    // If read fails it is the first initialization
    // therefore persist the initial data
    if(!cc_color_switch_read(i, &pColorComponents[i])) {
      ZAF_Actuator_Set(&pColorComponents[i].obj, 0xFF, 0);
      cc_color_switch_write((uint8_t) i, &pColorComponents[i]);
    }
  }
}

static received_frame_status_t
CC_ColorSwitch_handler(
    cc_handler_input_t * input,
    cc_handler_output_t * output)
{
  switch (input->frame->ZW_Common.cmd)
  {
    case SWITCH_COLOR_SUPPORTED_GET:
    {
      if(true == Check_not_legal_response_job(input->rx_options))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      output->frame->ZW_SwitchColorSupportedReportV3Frame.cmdClass = COMMAND_CLASS_SWITCH_COLOR;
      output->frame->ZW_SwitchColorSupportedReportV3Frame.cmd = SWITCH_COLOR_SUPPORTED_REPORT;
      uint16_t colorCompMask = colorsComponentsMask(input->rx_options->destNode.endpoint);
      output->frame->ZW_SwitchColorSupportedReportV3Frame.colorComponentMask1 = (uint8_t)(colorCompMask & 0xFF);
      output->frame->ZW_SwitchColorSupportedReportV3Frame.colorComponentMask2 = (uint8_t)(colorCompMask >> 8);

      output->length = sizeof(ZW_SWITCH_COLOR_SUPPORTED_REPORT_V3_FRAME);
    }
    break;
    case SWITCH_COLOR_GET:
    {
      if(true == Check_not_legal_response_job(input->rx_options))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      s_colorComponent *color = findColorComponentByColorID(input->frame->ZW_SwitchColorGetV3Frame.colorComponentId,
                                                            input->rx_options->destNode.endpoint);
      if (NULL == color)
      {
        // If requested color was not found, send REPORT of first defined color.
        color = findColorComponentByColorID(pColorComponents->colorId, input->rx_options->destNode.endpoint);
      }
      DPRINTF("Prepare report for %d color\n", color->colorId);
      output->frame->ZW_SwitchColorReportV3Frame.cmdClass = COMMAND_CLASS_SWITCH_COLOR;
      output->frame->ZW_SwitchColorReportV3Frame.cmd = SWITCH_COLOR_REPORT_V3;
      output->frame->ZW_SwitchColorReportV3Frame.colorComponentId = color->colorId;
      output->frame->ZW_SwitchColorReportV3Frame.currentValue = ZAF_Actuator_GetCurrentValue(&color->obj);
      output->frame->ZW_SwitchColorReportV3Frame.targetValue = ZAF_Actuator_GetTargetValue(&color->obj);
      output->frame->ZW_SwitchColorReportV3Frame.duration = ZAF_Actuator_GetDurationRemaining(&color->obj);

      output->length = sizeof(ZW_SWITCH_COLOR_REPORT_V3_FRAME);
    }
    break;
    case SWITCH_COLOR_SET:
    {
      // Read five least significant bits (4-0) from ZW_SwitchColorSet4byteV3Frame.properties1 to get Color Count
      uint8_t colorCount = input->frame->ZW_SwitchColorSet4byteV3Frame.properties1 & 0x1F;
      if (0 == colorCount)
      {
        DPRINTF("%s SET: colorCount = 0, nothing to do.\n", __func__);
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      uint8_t duration;
      if ((3 + 2*colorCount) == input->length)// (CC + CMD + colorCount + 2*colorCount)
      {
        duration = 0;
      }
      else if ((3 + 2*colorCount + 1) == input->length)
      {
        duration = *((uint8_t *)(&input->frame->ZW_Common.cmdClass) + input->length - 1);
      }
      else
      {
        DPRINTF("SWITCH_COLOR_SET: Unknown frame length = %#d\n", input->length);
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      uint8_t *pRxFrame = (uint8_t *)&(input->frame->ZW_SwitchColorSet4byteV3Frame.variantgroup1);
      EColorComponents colorChangeInProgress = ECOLORCOMPONENT_COLOR_UNDEFINED;
      uint8_t status = EACTUATOR_NOT_CHANGING;
      s_colorComponent *color;
      for (int i = 0; i < colorCount; i++)
      {
        // save the values to be passed to set function
        EColorComponents colorID = *(pRxFrame++);
        uint8_t value = *(pRxFrame++);
        color = findColorComponentByColorID(colorID, input->rx_options->destNode.endpoint);
        if (NULL == color)
        {
          DPRINTF("Color %x not supported!\n", colorID);
          return RECEIVED_FRAME_STATUS_FAIL;
        }
        color->rxOpt = *(input->rx_options);
        colorsChangingBitmask |= (uint16_t)(1 << color->colorId);

        if (0 == duration) {
          /*
           * Disable Supervision status updates as the change will be instant with a duration of
           * zero.
           *
           * Setting the Supervision status update to zero will purposely disable the transmission
           * of a Supervision Report in the actuator callback.
           */
          color->rxOpt.statusUpdate = 0;
        }

        status = ZAF_Actuator_Set(&color->obj, value, duration);
        if ((EACTUATOR_CHANGING != status) && (colorsChangingBitmask & (1 << color->colorId))) {
          // Current color is in its final state. If there was any change, the flag in colorsChangingBitmask
          // would have been cleared in CC_ColorSwitch_ColorChanged_cb(). If flag is still on, just clear it.
          colorsChangingBitmask &= (uint16_t)~((uint16_t)1 << color->colorId);
        }
        if (EACTUATOR_FAILED == status) {
          return RECEIVED_FRAME_STATUS_FAIL;
        }
        if (EACTUATOR_CHANGING == status)
        {
          colorChangeInProgress = colorID;
        }
      }
      if (ECOLORCOMPONENT_COLOR_UNDEFINED == colorChangeInProgress)
      {
        DPRINT("No ongoing color change, done.\n");
        break;
      }
      if (!input->rx_options->bSupervisionActive || is_multicast(&color->rxOpt))
      {
        // Supervision is not active, or this is multicast.
        DPRINT("Supervision report not needed, done.\n");
        break;
      }

      color = findColorComponentByColorID((uint8_t)colorChangeInProgress, input->rx_options->destNode.endpoint);
      output->duration = ZAF_Actuator_GetDurationRemaining(&color->obj);
      DPRINTF("Remaining duration %#2X, superv properties = %X\n", output->duration,
              color->rxOpt.sessionId | (color->rxOpt.statusUpdate << 7));
      return RECEIVED_FRAME_STATUS_WORKING;
      break;
    }
    case SWITCH_COLOR_START_LEVEL_CHANGE:
    {
      uint8_t upDown = input->frame->ZW_SwitchColorStartLevelChangeV3Frame.properties1 & (1 << 6);
      uint8_t ignoreStartLevel = input->frame->ZW_SwitchColorStartLevelChangeV3Frame.properties1 & (1 << 5);
      s_colorComponent *color = findColorComponentByColorID(
          input->frame->ZW_SwitchColorStartLevelChangeV3Frame.colorComponentId,
          input->rx_options->destNode.endpoint);
      if( NULL == color)
      {
        DPRINTF("Color %x not supported!\n", input->frame->ZW_SwitchColorStartLevelChangeV3Frame.colorComponentId);
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      uint8_t startLevel = input->frame->ZW_SwitchColorStartLevelChangeV3Frame.startLevel;
      uint8_t duration;
      if (5 == input->length) // (CC + CMD + properties + colorId + startLevel (+ duration))
      {
        duration = 0xFF; // Notify Actuator to use factory default duration
      }
      else if (6 == input->length)
      {
        duration = input->frame->ZW_SwitchColorStartLevelChangeV3Frame.duration;
      }
      else
      {
        DPRINTF("SWITCH_COLOR_START_LEVEL_CHANGE: Unknown frame length = %#d\n", input->length);
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      color->rxOpt = *(input->rx_options);
      colorsChangingBitmask |= (uint16_t)(1 << color->colorId);
      uint8_t status = ZAF_Actuator_StartChange(&color->obj, ignoreStartLevel, upDown, startLevel, duration);
      if ((EACTUATOR_CHANGING != status) && (colorsChangingBitmask & (1 << color->colorId))) {
        // Current color is in its final state. If there was any change, the flag in colorsChangingBitmask
        // would have been cleared in CC_ColorSwitch_ColorChanged_cb(). If flag is still on, just clear it.
        colorsChangingBitmask &= (uint16_t)~((uint16_t)1 << color->colorId);
      }
      if (EACTUATOR_FAILED == status) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      // All done with SUCCESS. If needed, Supervision CC will take care of sending Supervision report,
      // so clear supervision flag here.
      color->rxOpt.bSupervisionActive = 0;
    }
    break;
    case SWITCH_COLOR_STOP_LEVEL_CHANGE:
    {
      if (3 != input->length)
      {
        DPRINTF("%s(): Invalid frame length %d\n", __func__, input->length);
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      s_colorComponent *color = findColorComponentByColorID(input->frame->ZW_SwitchColorStopLevelChangeV3Frame.colorComponentId,
                                                            input->rx_options->destNode.endpoint);
      if (NULL == color)
      {
        DPRINTF("Color %x not supported!\n", input->frame->ZW_SwitchColorStartLevelChangeV3Frame.colorComponentId);
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      if (ZAF_Actuator_StopChange(&color->obj))
      {
        colorsChangingBitmask &= (uint16_t)~((uint16_t)1 << color->colorId);
        if (false == ZAF_TSE_Trigger(CC_ColorSwitch_report_stx,
                                     (void *)color,
                                     false))
        {
          DPRINTF("%s(): ZAF_TSE_Trigger failed\n", __func__);
        }
      }
    }
    break;
    default:
      return RECEIVED_FRAME_STATUS_NO_SUPPORT;
  }
  return RECEIVED_FRAME_STATUS_SUCCESS;
}

/**
 * Color Component mask. Used for SWITCH_COLOR_SUPPORTED_REPORT
 * @param Specific endpoint
 * @return bitmask with all supported colors (n-th bit =n-th color. See @ref EColorComponents)
 */
static uint16_t colorsComponentsMask(uint8_t endpoint)
{
  uint8_t colorMask = 0;
  s_colorComponent *pColor = pColorComponents;
  for(uint8_t i = 0; i < colorsSupportedCount; i++, pColor++)
  {
    if (endpoint == pColor->ep)
    {
      colorMask |= (uint8_t)(1 << pColor->colorId);
    }
  }
  return colorMask;
}

/**
 * Return index of color given by colorId in the array s_colorComponents
 * Used to fill in Report
 * @param Specific endpoint
 * @param colorId Unique color ID
 * @return pointer to the color structure that contains colorId color.
 */
static s_colorComponent* findColorComponentByColorID(uint8_t colorId, uint8_t endpoint)
{
  s_colorComponent *pColor = pColorComponents;
  for(uint8_t i = 0; i < colorsSupportedCount; i++, pColor++)
  {
    if (colorId == pColor->colorId && endpoint == pColor->ep)
    {
      return pColor;
    }
  }
  return NULL;
}

/**
 * 
 * Returns color component index in the array s_colorComponents given by actuator object
 * @param[in] pObj Pointer to actuator object
 * @return int16_t -1 if not found else the index in the array
 */
static int16_t findColorComponentIndexByObj(s_Actuator *pObj)
{
  s_colorComponent *pColor = pColorComponents;
  for(uint8_t i = 0; i < colorsSupportedCount; i++, pColor++)
  {
    if (pObj == &pColor->obj)
    {
      return i;
    }
  }
  return -1;
}

/**
 * Function triggered after some change happened in Actuator module
 * @details
 * Responsible for informing the app about the change and triggering TSE if one of the colors reached its final state.
 * In case of supervision timed change,it also sends Supervision Report with final state
 *
 * @param pObj pointer to object that was processed by Actuator
 */
static void CC_ColorSwitch_ColorChanged_cb(s_Actuator *pObj)
{
  s_colorComponent *color;
  int16_t color_component_id;
  
  color_component_id = findColorComponentIndexByObj(pObj);
  
  color = &pColorComponents[color_component_id];
  // We ended up here so it must be that current value has changed. Inform the app about it.
  if(NULL != color->cb)
  {
    color_callback_t cb = color->cb;
    cb(color);
  }
  else
  {
    cc_color_switch_refresh_cb();
  }

  if(ZAF_Actuator_GetTargetValue(&color->obj) == ZAF_Actuator_GetCurrentValue(&color->obj))
  {
    if (0 == colorsChangingBitmask)
    {
      // Shouldn't ever happen, but indicates that callback function was called more times than predicted
      return;
    }

    cc_color_switch_write((uint8_t) color_component_id, color);

    colorsChangingBitmask &= (uint16_t)~((uint16_t)1 << color->colorId);
    DPRINTF("Trigger TSE for color %x\n", color->colorId);
    if (false == ZAF_TSE_Trigger(CC_ColorSwitch_report_stx,
                                 (void *)color,
                                 false))
    {
      DPRINTF("%s(): ZAF_TSE_Trigger failed\n", __func__);
    }
    if (0 == colorsChangingBitmask)
    {
      if(color->rxOpt.bSupervisionActive && color->rxOpt.statusUpdate && !is_multicast(&color->rxOpt))
      {
        zaf_tx_options_t tx_options;
        zaf_transport_rx_to_tx_options(&color->rxOpt, &tx_options);
        // Send Supervision Report Success if not triggered with a multicast.
        CmdClassSupervisionReportSend(&tx_options,
                                      color->rxOpt.sessionId, // This is last status update, no need to set anything.
                                      CC_SUPERVISION_STATUS_SUCCESS,
                                      0); // durationRemaining should always be 0 at this point
        DPRINTF("%sSupervision report success sent.\n", __func__);
      }
    }
  }
}

static void 
CC_ColorSwitch_report_stx(zaf_tx_options_t *tx_options, void* pData)
{
  DPRINTF("* %s() *\n"
      "\ttxOpt.src = %d\n"
      "\ttxOpt.options %#02x\n",
      __func__, tx_options->source_endpoint, tx_options->tx_options);

  /* Prepare payload for report */
  ZW_APPLICATION_TX_BUFFER txBuf;
  memset((uint8_t*)&txBuf, 0, sizeof(ZW_APPLICATION_TX_BUFFER) );

  s_colorComponent *color = (s_colorComponent *)pData;
  DPRINTF("Sending report for colorId: %u\n", color->colorId);

  txBuf.ZW_SwitchColorReportV3Frame.cmdClass = COMMAND_CLASS_SWITCH_COLOR;
  txBuf.ZW_SwitchColorReportV3Frame.cmd = SWITCH_COLOR_REPORT_V3;
  txBuf.ZW_SwitchColorReportV3Frame.colorComponentId = color->colorId;
  txBuf.ZW_SwitchColorReportV3Frame.currentValue = ZAF_Actuator_GetCurrentValue(&color->obj);
  txBuf.ZW_SwitchColorReportV3Frame.targetValue = ZAF_Actuator_GetTargetValue(&color->obj);
  txBuf.ZW_SwitchColorReportV3Frame.duration = ZAF_Actuator_GetDurationRemaining(&color->obj);

  tx_options->use_supervision = true;

  (void) zaf_transport_tx((uint8_t *)&txBuf,
                          sizeof(ZW_SWITCH_COLOR_REPORT_V3_FRAME),
                          ZAF_TSE_TXCallback,
                          tx_options);
}

static uint8_t lifeline_reporting(ccc_pair_t * p_ccc_pair)
{
  p_ccc_pair->cmdClass = COMMAND_CLASS_SWITCH_COLOR;
  p_ccc_pair->cmd      = SWITCH_COLOR_REPORT;
  return 1;
}

REGISTER_CC_V5(COMMAND_CLASS_SWITCH_COLOR, SWITCH_COLOR_VERSION_V3, CC_ColorSwitch_handler, NULL, NULL, lifeline_reporting, 0, init_and_reset, init_and_reset);
