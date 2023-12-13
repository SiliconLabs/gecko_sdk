/**
 * @file
 * Handler for Command Class Binary Switch.
 * @copyright 2018 Silicon Laboratories Inc.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#include <CC_BinarySwitch.h>
#include <string.h>
#include "CC_Supervision.h"
#include "Assert.h"
#include "ZAF_TSE.h"
#include "zaf_config_api.h"

//#define DEBUGPRINT
#include "DebugPrint.h"

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

static cc_binary_switch_t * mp_switches;
static uint8_t m_switch_count;

static void
CC_BinarySwitch_report_stx(zaf_tx_options_t *tx_options, void* p_switch);

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/

static cc_binary_switch_t * find_switch_by_endpoint(uint8_t endpoint)
{
  ASSERT(NULL != mp_switches);
  ASSERT(0 != m_switch_count);
  cc_binary_switch_t * p_switch = mp_switches;
  for(uint8_t i = 0; i < m_switch_count; i++, p_switch++)
  {
    if (endpoint == p_switch->endpoint)
    {
      return p_switch;
    }
  }
  return NULL;
}

static cc_binary_switch_t * find_switch_by_actuator(s_Actuator * p_actuator)
{
  ASSERT(NULL != mp_switches);
  ASSERT(0 != m_switch_count);
  cc_binary_switch_t * p_switch = mp_switches;
  for(uint8_t i = 0; i < m_switch_count; i++, p_switch++) {
    if (p_actuator == &p_switch->actuator) {
      return p_switch;
    }
  }
  return NULL;
}

/**
 * Encodes and returns the given value from [1,99] to 255.
 *
 * Any other value will be returned as is.
 *
 * @param[in] value Value to encode.
 * @return Returns the encoded value.
 */
static uint8_t encode_value(uint8_t value)
{
  if (1 <= value && 100 > value) {
    return 255;
  }
  return value;
}

static void actuator_callback(s_Actuator * p_actuator)
{
  DPRINT("\nactuator_callback()");
  cc_binary_switch_t * p_switch = find_switch_by_actuator(p_actuator);

  uint8_t current_value = ZAF_Actuator_GetCurrentValue(p_actuator);
  /*
   * CC:0025.02.03.11.002 states "The advertised Current Value MUST NOT be updated to the Target
   * Value before the hardware actuator has actually reached the Target Value." Hence, don't do
   * anything until the current value has reached the target value.
   */
  if (current_value == ZAF_Actuator_GetTargetValue(p_actuator)) {
    if (NULL != p_switch->callback) {
      p_switch->callback(p_switch);
    }

    // Encode current value in accordance with CC:0025.02.03.11.001.
    current_value = encode_value(current_value);

    /*
     * Save the current value so that we can report the old value during a future transition.
     * (CC:0025.02.03.11.002)
     */
    p_switch->old_value = current_value;

    DPRINT("\nCurrent value == Target value");
    // Reached the final value => Trigger True Status
    if (!ZAF_TSE_Trigger(CC_BinarySwitch_report_stx, (void *)p_switch, true)) {
      DPRINT("\nTSE fail");
    }

    /*
     * Transmit Supervision Report only if:
     * 1. Supervision is active
     * 2. The use of status update is enabled
     * 3. The frame was not received as multicast
     */
    if (p_switch->rxOpt.bSupervisionActive && p_switch->rxOpt.statusUpdate && !is_multicast(&p_switch->rxOpt)) {
      /*
       * Transmit Supervision Report, but ignore return value. The transmitter of Supervision Get
       * must retransmit if not receiving a Supervision Report.
       */
      zaf_tx_options_t tx_options = { 0 };
      zaf_transport_rx_to_tx_options(&p_switch->rxOpt, &tx_options);
      CmdClassSupervisionReportSend(&tx_options,
                                    p_switch->rxOpt.sessionId, // This is last status update, no need to set anything.
                                    CC_SUPERVISION_STATUS_SUCCESS,
                                    0); // durationRemaining should always be 0 at this point
      DPRINTF("\n%s: TX Supervision Report", __func__);
    }
  }
}

static received_frame_status_t CC_BinarySwitch_handler(
    cc_handler_input_t * input,
    cc_handler_output_t * output)
{
  uint8_t endpoint = input->rx_options->destNode.endpoint;
  cc_binary_switch_t * p_switch;

  switch (input->frame->ZW_Common.cmd)
  {
    case SWITCH_BINARY_GET:
      if (true == Check_not_legal_response_job(input->rx_options)) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      if(0 == endpoint) {
        endpoint = zaf_config_get_default_endpoint();
      }

      p_switch = find_switch_by_endpoint(endpoint);

      if (NULL == p_switch) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      output->frame->ZW_SwitchBinaryReportV2Frame.cmdClass = COMMAND_CLASS_SWITCH_BINARY_V2;
      output->frame->ZW_SwitchBinaryReportV2Frame.cmd      = SWITCH_BINARY_REPORT_V2;

      /*
       * CC:0025.01.03.12.001: This field SHOULD advertise the current value of the nodes hardware;
       * also while in transition to a new value.
       *
       * The old value is set to the current value in actuator_callback() once the current value
       * reaches the target value.
       */
      output->frame->ZW_SwitchBinaryReportV2Frame.currentValue = p_switch->old_value;

      uint8_t target_value = ZAF_Actuator_GetTargetValue(&p_switch->actuator);
      // Encode target value in accordance with CC:0025.02.03.11.004.
      target_value = encode_value(target_value);
      output->frame->ZW_SwitchBinaryReportV2Frame.targetValue  = target_value;
      output->frame->ZW_SwitchBinaryReportV2Frame.duration     = ZAF_Actuator_GetDurationRemaining(&p_switch->actuator);

      output->length = sizeof(ZW_SWITCH_BINARY_REPORT_V2_FRAME);
      break;

    case SWITCH_BINARY_SET:
    {
      if ((0x63 < input->frame->ZW_SwitchBinarySetV2Frame.targetValue) &&
          (0xFF != input->frame->ZW_SwitchBinarySetV2Frame.targetValue))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      if (2 >= input->length)
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      if(0 == endpoint) {
        endpoint = zaf_config_get_default_endpoint();
      }

      p_switch = find_switch_by_endpoint(endpoint);

      if (NULL == p_switch) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      // Save receive options for later use by Supervision and True Status.
      p_switch->rxOpt = *(input->rx_options);

      if (3 == input->length) /* version 1 (does not have duration) */
      {
        input->frame->ZW_SwitchBinarySetV2Frame.duration = p_switch->default_duration;
      }

      if (0 == input->frame->ZW_SwitchBinarySetV2Frame.duration || 0xFF == input->frame->ZW_SwitchBinarySetV2Frame.duration) {
        /*
         * Disable Supervision status updates as the change will be instant with a duration of zero or
         * default duration of 0xFF.
         *
         * Setting the Supervision status update to zero will purposely disable the transmission
         * of a Supervision Report in the actuator callback.
         */
        p_switch->rxOpt.statusUpdate = 0;
      }

      e_cmd_handler_return_code_t return_code = cc_binary_switch_set_handler(
          input->frame->ZW_SwitchBinarySetV2Frame.targetValue,
          input->frame->ZW_SwitchBinarySetV2Frame.duration,
          endpoint);

      if (E_CMD_HANDLER_RETURN_CODE_WORKING == return_code
          && p_switch->rxOpt.bSupervisionActive && !is_multicast(&p_switch->rxOpt)) {

        output->duration = ZAF_Actuator_GetDurationRemaining(&p_switch->actuator);
        return RECEIVED_FRAME_STATUS_WORKING;
      } else if (E_CMD_HANDLER_RETURN_CODE_FAIL == return_code) {
        return RECEIVED_FRAME_STATUS_FAIL;
      } else {
        // Do nothing. The CC handler returns success per default.
      }
    }
      break;
    default:
      return RECEIVED_FRAME_STATUS_NO_SUPPORT;
      break;
  }
  return RECEIVED_FRAME_STATUS_SUCCESS;
}

static void
CC_BinarySwitch_report_stx(zaf_tx_options_t *tx_options, void* p_switch)
{
  /* Prepare payload for report */
  cc_binary_switch_t *p_switch_data = (cc_binary_switch_t *)p_switch;

  uint8_t target_value = ZAF_Actuator_GetTargetValue(&p_switch_data->actuator);
  // Encode target value in accordance with CC:0025.02.03.11.004.
  target_value = encode_value(target_value);
  tx_options->use_supervision = true;

  ZW_APPLICATION_TX_BUFFER txBuf = {
    .ZW_SwitchBinaryReportV2Frame.cmdClass     = COMMAND_CLASS_SWITCH_BINARY,
    .ZW_SwitchBinaryReportV2Frame.cmd          = SWITCH_BINARY_REPORT,
    .ZW_SwitchBinaryReportV2Frame.currentValue = p_switch_data->old_value,
    .ZW_SwitchBinaryReportV2Frame.targetValue  = target_value,
    .ZW_SwitchBinaryReportV2Frame.duration     = ZAF_Actuator_GetDurationRemaining(&p_switch_data->actuator)
  };
  (void) zaf_transport_tx((uint8_t *)&txBuf,
                          sizeof(ZW_SWITCH_BINARY_REPORT_V2_FRAME),
                          ZAF_TSE_TXCallback,
                          tx_options);
}

e_cmd_handler_return_code_t cc_binary_switch_set_handler(uint8_t value,
                                                         uint8_t duration,
                                                         uint8_t endpoint)
{
  cc_binary_switch_t * p_switch = find_switch_by_endpoint(endpoint);

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

static inline void set_endpoint(cc_binary_switch_t * p_switch)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
  p_switch->rxOpt.destNode.endpoint = p_switch->endpoint;
#pragma GCC diagnostic pop
}

static inline void clear_rxopts(cc_binary_switch_t * p_switch)
{
  memset((uint8_t *)&p_switch->rxOpt, 0, sizeof(p_switch->rxOpt));
}

void cc_binary_switch_set(cc_binary_switch_t * p_switch, uint8_t value)
{
  clear_rxopts(p_switch);
  set_endpoint(p_switch);
  if (0xFF == value) {
    value = ZAF_Actuator_GetLastOnValue(&p_switch->actuator);
  }
  ZAF_Actuator_Set(&p_switch->actuator,
                   value,
                   p_switch->default_duration);
}

uint8_t cc_binary_switch_get_current_value(cc_binary_switch_t * p_switch)
{
  set_endpoint(p_switch);
  return ZAF_Actuator_GetCurrentValue(&p_switch->actuator);
}

ZW_WEAK void cc_binary_switch_handler(__attribute__((unused)) cc_binary_switch_t * p_switch)
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
  pFrame->ZW_SwitchBinarySetV2Frame.cmdClass = COMMAND_CLASS_SWITCH_BINARY_V2;
  pFrame->ZW_SwitchBinarySetV2Frame.cmd      = SWITCH_BINARY_SET;
}

static void basic_get_mapper(uint8_t endpoint, uint8_t * p_current_value, uint8_t * p_target_value, uint8_t * p_duration)
{
  cc_binary_switch_t * p_switch = find_switch_by_endpoint(endpoint);

  if (NULL == p_switch) {
    return;
  }

  /*
   * CC:0025.01.03.12.001: This field SHOULD advertise the current value of the node's hardware;
   * also while in transition to a new value.
   *
   * The old value is set to the current value in actuator_callback() once the current value
   * reaches the target value.
   */
  *p_current_value = p_switch->old_value;

  uint8_t target_value = ZAF_Actuator_GetTargetValue(&p_switch->actuator);
  // Encode target value in accordance with CC:0025.02.03.11.004.
  target_value = encode_value(target_value);

  *p_target_value = target_value;
  *p_duration     = ZAF_Actuator_GetDurationRemaining(&p_switch->actuator);
}

static uint8_t lifeline_reporting(ccc_pair_t * p_ccc_pair)
{
  p_ccc_pair->cmdClass = COMMAND_CLASS_SWITCH_BINARY;
  p_ccc_pair->cmd      = SWITCH_BINARY_REPORT;
  return 1;
}

static void init_and_reset(void)
{
  mp_switches = cc_binary_switch_get_config();
  m_switch_count = cc_binary_switch_get_config_length();

  cc_binary_switch_t * p_switch = mp_switches;
  for (uint32_t i = 0; i < m_switch_count; i++, p_switch++)
  {
    ZAF_Actuator_Init(&(p_switch->actuator), 0, 99, 20, p_switch->default_duration, actuator_callback);
    p_switch->old_value = ZAF_Actuator_GetCurrentValue(&p_switch->actuator);
  }
}

REGISTER_CC_V5(COMMAND_CLASS_SWITCH_BINARY, SWITCH_BINARY_VERSION_V2, CC_BinarySwitch_handler, basic_set_mapper, basic_get_mapper, lifeline_reporting, 0, init_and_reset, init_and_reset);
