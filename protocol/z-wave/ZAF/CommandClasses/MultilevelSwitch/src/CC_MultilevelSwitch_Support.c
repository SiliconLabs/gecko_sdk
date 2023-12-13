/**
 * @file
 * Handler for Command Class Multilevel Switch.
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#include <CC_MultilevelSwitch_Support.h>
#include <ZW_basis_api.h>
#include <ZW_TransportLayer.h>
#include <string.h>
//#define DEBUGPRINT
#include "DebugPrint.h"
#include <ZAF_TSE.h>
#include <CC_Supervision.h>
#include "cc_multilevel_switch_support_io.h"
#include "zaf_transport_tx.h"

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

// The CC spec and Actuator module defines up as false and down as true.
#define DIRECTION_UP false
#define DIRECTION_DOWN true

#define CC_MULTILEVEL_SWITCH_ACTUATOR_MIN_VALUE 0
#define CC_MULTILEVEL_SWITCH_ACTUATOR_MAX_VALUE 99

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/

static cc_multilevel_switch_t * mp_switches;
static uint8_t m_switch_count;

static void CC_MultilevelSwitch_report_stx(
    zaf_tx_options_t *tx_options,
    void * p_switch);
static e_cmd_handler_return_code_t cc_multilevel_switch_set_handler(
    uint8_t value,
    uint8_t duration,
    uint8_t endpoint);

/**
 * Return index of color given by colorId in the array s_colorComponents
 * Used to fill in Report
 * @param Specific endpoint
 * @param colorId Unique color ID
 * @return pointer to the color structure that contains colorId color.
 */
static cc_multilevel_switch_t * find_switch_by_endpoint(uint8_t endpoint)
{
  ASSERT(NULL != mp_switches);
  ASSERT(0 != m_switch_count);
  cc_multilevel_switch_t * p_switch = mp_switches;
  for(uint8_t i = 0; i < m_switch_count; i++, p_switch++)
  {
    if (endpoint == p_switch->endpoint)
    {
      return p_switch;
    }
  }
  return NULL;
}

static int16_t find_switch_index_by_actuator(s_Actuator * p_actuator)
{
  ASSERT(NULL != mp_switches);
  ASSERT(0 != m_switch_count);
  cc_multilevel_switch_t * p_switch = mp_switches;
  for(uint8_t i = 0; i < m_switch_count; i++, p_switch++) {
    if (p_actuator == &p_switch->actuator) {
      return i;
    }
  }
  return -1;
}

static void actuator_callback(s_Actuator * p_actuator)
{
  cc_multilevel_switch_t * p_switch;
  int16_t multilevel_component_id;

  DPRINT("\nactuator_callback()");
  multilevel_component_id = find_switch_index_by_actuator(p_actuator);
  p_switch = &mp_switches[multilevel_component_id];

  cc_multilevel_switch_support_cb(p_switch);
  if (ZAF_Actuator_GetCurrentValue(p_actuator) == ZAF_Actuator_GetTargetValue(p_actuator)) {
    cc_multilevel_switch_write((uint8_t) multilevel_component_id, p_switch);
    DPRINT("\nCurrent value == Target value");
    // Reached the final value => Trigger True Status
    if (!ZAF_TSE_Trigger(CC_MultilevelSwitch_report_stx, (void *)p_switch, true)) {
      DPRINT("\nTSE fail");
    }

    if (p_switch->rxOpt.bSupervisionActive && p_switch->rxOpt.statusUpdate && !is_multicast(&p_switch->rxOpt)) {
      zaf_tx_options_t tx_options;
      zaf_transport_rx_to_tx_options(&p_switch->rxOpt, &tx_options);
      // Send Supervision Report Success if actuation was not triggered with a multicast.
      CmdClassSupervisionReportSend(&tx_options,
                                    p_switch->rxOpt.sessionId, // This is last status update, no need to set anything.
                                    CC_SUPERVISION_STATUS_SUCCESS,
                                    0); // durationRemaining should always be 0 at this point
      DPRINTF("\n%s: TX Supervision Report", __func__);
    }
  }
}

static void init_and_reset(bool force_write)
{
  uint8_t default_duration;
  uint8_t min_value;
  uint8_t max_value;

  mp_switches = cc_multilevel_switch_support_config_get_switches();
  m_switch_count = cc_multilevel_switch_support_config_get_length_switches();

  default_duration = cc_multilevel_switch_support_config_get_default_duration();
  min_value = cc_multilevel_switch_get_min_value();
  max_value = cc_multilevel_switch_get_max_value();

  for (uint8_t i = 0; i < m_switch_count; i++)
  {
    // Set the rxStatus to Multicast to prevent True Status
    mp_switches[i].rxOpt.rxStatus = RECEIVE_STATUS_TYPE_MULTI;
    ZAF_Actuator_Init(&(mp_switches[i].actuator), min_value, max_value, 20, default_duration, actuator_callback);
    ZAF_Actuator_Set(&(mp_switches[i].actuator), max_value, 0);
    if(force_write || !cc_multilevel_switch_read(i, &mp_switches[i])) {
      cc_multilevel_switch_write((uint8_t) i, &mp_switches[i]);
    }
  }
}

static void init(void)
{
  init_and_reset(false);
}

static void reset(void)
{
  init_and_reset(true);
}

static received_frame_status_t CC_MultilevelSwitch_handler(
    cc_handler_input_t * input,
    cc_handler_output_t * output)
{
  e_cmd_handler_return_code_t return_code;

  switch (input->frame->ZW_Common.cmd)
  {
    case SWITCH_MULTILEVEL_GET:

      if (true == Check_not_legal_response_job(input->rx_options))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      cc_multilevel_switch_t * p_switch = find_switch_by_endpoint(input->rx_options->destNode.endpoint);

      if (NULL == p_switch) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      output->frame->ZW_SwitchMultilevelReportV4Frame.cmdClass     = COMMAND_CLASS_SWITCH_MULTILEVEL;
      output->frame->ZW_SwitchMultilevelReportV4Frame.cmd          = SWITCH_MULTILEVEL_REPORT;
      output->frame->ZW_SwitchMultilevelReportV4Frame.currentValue = ZAF_Actuator_GetCurrentValue(&p_switch->actuator);
      output->frame->ZW_SwitchMultilevelReportV4Frame.targetValue  = ZAF_Actuator_GetTargetValue(&p_switch->actuator);
      output->frame->ZW_SwitchMultilevelReportV4Frame.duration     = ZAF_Actuator_GetDurationRemaining(&p_switch->actuator);

      output->length = sizeof(ZW_SWITCH_MULTILEVEL_REPORT_V4_FRAME);
      break;

    case SWITCH_MULTILEVEL_SET:
    {
      cc_multilevel_switch_t * p_switch = find_switch_by_endpoint(input->rx_options->destNode.endpoint);
      if (NULL == p_switch) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      p_switch->rxOpt = *input->rx_options;

      if (3 == input->length) {
        /*
         * Use the default dimming duration set by the application If the length is 3 because then
         * the CC version is 1. Hence, duration is not supported.
         */
        input->frame->ZW_SwitchMultilevelSetV3Frame.duration = 0xFF;
      }

      if (0 == input->frame->ZW_SwitchMultilevelSetV3Frame.duration) {
        /*
         * Disable Supervision status updates as the change will be instant with a duration of zero.
         *
         * Setting the Supervision status update to zero will purposely disable the transmission
         * of a Supervision Report in the actuator callback.
         */
        p_switch->rxOpt.statusUpdate = 0;
      }

      return_code = cc_multilevel_switch_set_handler(input->frame->ZW_SwitchMultilevelSetV3Frame.value,
                                       input->frame->ZW_SwitchMultilevelSetV3Frame.duration,
                                       input->rx_options->destNode.endpoint);

      if (E_CMD_HANDLER_RETURN_CODE_WORKING == return_code
          && p_switch->rxOpt.bSupervisionActive && !is_multicast(&p_switch->rxOpt)) {

        output->duration =  ZAF_Actuator_GetDurationRemaining(&p_switch->actuator);
        return RECEIVED_FRAME_STATUS_WORKING;
      } else if (E_CMD_HANDLER_RETURN_CODE_FAIL == return_code) {
        return RECEIVED_FRAME_STATUS_FAIL;
      } else {
        // Do nothing. The CC handler returns success per default.
      }
    }
      break;

    case SWITCH_MULTILEVEL_START_LEVEL_CHANGE:
    {
      if (input->length < 4) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V4_FRAME * p_frame =
            (ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V4_FRAME *)input->frame;

      bool ignore_start_level = (0 != (p_frame->properties1 & SWITCH_MULTILEVEL_START_LEVEL_CHANGE_LEVEL_IGNORE_START_LEVEL_BIT_MASK));
      cc_multilevel_switch_t * p_switch = find_switch_by_endpoint(input->rx_options->destNode.endpoint);

      if (NULL == p_switch) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      // Update the object RX options for use with TSE and Supervision in callback.
      p_switch->rxOpt = *input->rx_options;

      bool direction = DIRECTION_DOWN;

      if (input->length == 6) {
        // Version 3

        if (!(input->frame->ZW_SwitchMultilevelStartLevelChangeV3Frame.properties1&
            SWITCH_MULTILEVEL_START_LEVEL_CHANGE_PROPERTIES1_UP_DOWN_MASK_V3))
        {
          direction = DIRECTION_UP;
        }
        else if  ((input->frame->ZW_SwitchMultilevelStartLevelChangeV3Frame.properties1 &
            SWITCH_MULTILEVEL_START_LEVEL_CHANGE_PROPERTIES1_UP_DOWN_MASK_V3) > 0x40)
        {
          /*We should ignore the frame if the  up/down primary switch bit field value is either reserved or no up/down motion*/
          break;
        }
      }
      else
      {
        if (input->length == 4) /*version 1*/
        {
          // Use the default duration set by the application when CC version doesn't support it.
          input->frame->ZW_SwitchMultilevelStartLevelChangeV3Frame.dimmingDuration = 0xFF;
        }
        if (!(input->frame->ZW_SwitchMultilevelStartLevelChangeFrame.level
            & SWITCH_MULTILEVEL_START_LEVEL_CHANGE_LEVEL_UP_DOWN_BIT_MASK))
        {
          direction = DIRECTION_UP;
        }
      }

      eActuatorState actuator_state;
      actuator_state = ZAF_Actuator_StartChange(&p_switch->actuator,
                                                ignore_start_level,
                                                direction,
                                                input->frame->ZW_SwitchMultilevelStartLevelChangeFrame.startLevel,
                                                input->frame->ZW_SwitchMultilevelStartLevelChangeV3Frame.dimmingDuration);
      if (EACTUATOR_FAILED == actuator_state) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      // All done with SUCCESS. If needed, Supervision CC will take care of sending Supervision report,
      // so clear supervision flag here.
      p_switch->rxOpt.bSupervisionActive = 0;
    }
    break;

    case SWITCH_MULTILEVEL_STOP_LEVEL_CHANGE:
    {
      if (2 != input->length)
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      cc_multilevel_switch_t * p_switch = find_switch_by_endpoint(input->rx_options->destNode.endpoint);

      if (NULL == p_switch) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      if (EACTUATOR_CHANGING == ZAF_Actuator_StopChange(&p_switch->actuator)) {
        ZAF_TSE_Trigger(CC_MultilevelSwitch_report_stx, (void *)p_switch, true);
      }
    }
      break;
    case SWITCH_MULTILEVEL_SUPPORTED_GET_V3:
      if(Check_not_legal_response_job(input->rx_options))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      output->frame->ZW_SwitchMultilevelSupportedReportV3Frame.cmdClass = COMMAND_CLASS_SWITCH_MULTILEVEL;
      output->frame->ZW_SwitchMultilevelSupportedReportV3Frame.cmd = SWITCH_MULTILEVEL_SUPPORTED_REPORT_V3;

      // Primary Switch Type SHOULD be Up/Down (0x02) according to SDS13781-14.
      output->frame->ZW_SwitchMultilevelSupportedReportV3Frame.properties1 = 0x02;

      // The secondary switch type is deprecated, thus the value should be not supported (0x02).
      output->frame->ZW_SwitchMultilevelSupportedReportV3Frame.properties2 = 0x00;

      output->length = sizeof(ZW_SWITCH_MULTILEVEL_SUPPORTED_REPORT_V3_FRAME);
      break;

    default:
      return RECEIVED_FRAME_STATUS_NO_SUPPORT;
  }
  return RECEIVED_FRAME_STATUS_SUCCESS;
}

static void 
CC_MultilevelSwitch_report_stx(zaf_tx_options_t *tx_options, void* p_switch)
{
  DPRINT("\nCC_MultilevelSwitch_report_stx()");
  /* Prepare payload for report */
  cc_multilevel_switch_t *p_switch_data = (cc_multilevel_switch_t *)p_switch;

  ZW_APPLICATION_TX_BUFFER txBuf = {
    .ZW_SwitchMultilevelReportV4Frame.cmdClass     = COMMAND_CLASS_SWITCH_MULTILEVEL,
    .ZW_SwitchMultilevelReportV4Frame.cmd          = SWITCH_MULTILEVEL_REPORT,
    .ZW_SwitchMultilevelReportV4Frame.currentValue = ZAF_Actuator_GetCurrentValue(&p_switch_data->actuator),
    .ZW_SwitchMultilevelReportV4Frame.targetValue  = ZAF_Actuator_GetTargetValue(&p_switch_data->actuator),
    .ZW_SwitchMultilevelReportV4Frame.duration     = ZAF_Actuator_GetDurationRemaining(&p_switch_data->actuator)
  };
  tx_options->use_supervision = true;
  (void) zaf_transport_tx((uint8_t *)&txBuf,
                          sizeof(ZW_SWITCH_MULTILEVEL_REPORT_V4_FRAME),
                          ZAF_TSE_TXCallback,
                          tx_options);
}

static e_cmd_handler_return_code_t cc_multilevel_switch_set_handler(uint8_t value,
                                                                    uint8_t duration,
                                                                    uint8_t endpoint)
{
  cc_multilevel_switch_t * p_switch = find_switch_by_endpoint(endpoint);

  if (NULL == p_switch) {
    return E_CMD_HANDLER_RETURN_CODE_FAIL;
  }

  if (0xFF == value) {
    value = ZAF_Actuator_GetLastOnValue(&p_switch->actuator);
  }

  eActuatorState actuator_state = ZAF_Actuator_Set(&p_switch->actuator,
                                                   value,
                                                   duration);

  if (EACTUATOR_CHANGING == actuator_state) {
    return E_CMD_HANDLER_RETURN_CODE_WORKING;
  } else if (EACTUATOR_NOT_CHANGING == actuator_state) {
    return E_CMD_HANDLER_RETURN_CODE_HANDLED;
  }

  return E_CMD_HANDLER_RETURN_CODE_FAIL;
}

static uint8_t cc_multilevel_switch_get_current_value_handler(uint8_t endpoint)
{
  cc_multilevel_switch_t * p_switch = find_switch_by_endpoint(endpoint);

  if (NULL == p_switch) {
    return 0;
  }

  return ZAF_Actuator_GetCurrentValue(&p_switch->actuator);
}

static uint8_t cc_multilevel_switch_get_target_value_handler(uint8_t endpoint)
{
  cc_multilevel_switch_t * p_switch = find_switch_by_endpoint(endpoint);

  if (NULL == p_switch) {
    return 0;
  }

  return ZAF_Actuator_GetTargetValue(&p_switch->actuator);
}

static uint8_t cc_multilevel_switch_get_duration_handler(uint8_t endpoint)
{
  cc_multilevel_switch_t * p_switch = find_switch_by_endpoint(endpoint);

  if (NULL == p_switch) {
    return 0;
  }

  return ZAF_Actuator_GetDurationRemaining(&p_switch->actuator);
}

static inline void set_endpoint(cc_multilevel_switch_t * p_switch)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
  p_switch->rxOpt.destNode.endpoint = p_switch->endpoint;
#pragma GCC diagnostic pop
}

static inline void clear_rxopts(cc_multilevel_switch_t * p_switch)
{
  memset((uint8_t *)&p_switch->rxOpt, 0, sizeof(RECEIVE_OPTIONS_TYPE_EX));
}

void cc_multilevel_switch_set(cc_multilevel_switch_t * p_switch, uint8_t value, uint8_t duration)
{
  clear_rxopts(p_switch);
  set_endpoint(p_switch);
  if (0xFF == value) {
    value = ZAF_Actuator_GetLastOnValue(&p_switch->actuator);
  }
  ZAF_Actuator_Set(&p_switch->actuator,
                   value,
                   duration);
}

void cc_multilevel_switch_start_level_change(cc_multilevel_switch_t * p_switch,
                                             bool up,
                                             bool ignore_start_level,
                                             uint8_t start_level,
                                             uint8_t duration)
{
  clear_rxopts(p_switch);
  set_endpoint(p_switch);
  ZAF_Actuator_StartChange(&p_switch->actuator,
                           ignore_start_level,
                           up,
                           start_level,
                           duration);
}

void cc_multilevel_switch_stop_level_change(cc_multilevel_switch_t * p_switch)
{
  clear_rxopts(p_switch);
  set_endpoint(p_switch);
  eActuatorState state = ZAF_Actuator_StopChange(&p_switch->actuator);
  if (EACTUATOR_CHANGING == state) {
    // A change was ongoing when we stopped it. => Trigger TSE
    ZAF_TSE_Trigger(CC_MultilevelSwitch_report_stx, (void *)p_switch, false);
  }
}

uint8_t cc_multilevel_switch_get_current_value(cc_multilevel_switch_t * p_switch)
{
  set_endpoint(p_switch);
  return ZAF_Actuator_GetCurrentValue(&p_switch->actuator);
}

uint8_t cc_multilevel_switch_get_last_on_value(cc_multilevel_switch_t * p_switch)
{
  set_endpoint(p_switch);
  return ZAF_Actuator_GetLastOnValue(&p_switch->actuator);
}

uint8_t cc_multilevel_switch_get_min_value(void)
{
  return CC_MULTILEVEL_SWITCH_ACTUATOR_MIN_VALUE;
}

uint8_t cc_multilevel_switch_get_max_value(void)
{
  return CC_MULTILEVEL_SWITCH_ACTUATOR_MAX_VALUE;
}

ZW_WEAK void cc_multilevel_switch_support_cb(__attribute__((unused)) struct cc_multilevel_switch_t * p_switch)
{
}

/**************************************************************************************************
 * Linker magic - Creates a section for an array of registered CCs and mapped CCs to the Basic CC.
 *************************************************************************************************/

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
  ((uint8_t*)pFrame)[0] = COMMAND_CLASS_SWITCH_MULTILEVEL_V4;
  ((uint8_t*)pFrame)[1] = SWITCH_MULTILEVEL_SET;
}

static void basic_get_mapper(uint8_t endpoint, uint8_t * p_current_value, uint8_t * p_target_value, uint8_t * p_duration)
{
  *p_current_value = cc_multilevel_switch_get_current_value_handler(endpoint);
  *p_target_value  = cc_multilevel_switch_get_target_value_handler(endpoint);
  *p_duration      = cc_multilevel_switch_get_duration_handler(endpoint);
}

static uint8_t lifeline_reporting(ccc_pair_t * p_ccc_pair)
{
  p_ccc_pair->cmdClass = COMMAND_CLASS_SWITCH_MULTILEVEL;
  p_ccc_pair->cmd      = SWITCH_MULTILEVEL_REPORT;
  return 1;
}

REGISTER_CC_V5(COMMAND_CLASS_SWITCH_MULTILEVEL, SWITCH_MULTILEVEL_VERSION_V4, CC_MultilevelSwitch_handler, basic_set_mapper, basic_get_mapper, lifeline_reporting, 0, init, reset);
