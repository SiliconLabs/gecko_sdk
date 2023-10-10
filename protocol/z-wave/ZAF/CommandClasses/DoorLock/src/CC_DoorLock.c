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
#include <zpal_nvm.h>
#include <ZAF_file_ids.h>
#include <ZAF_TSE.h>
#include <ZAF_nvm_app.h>
#include <ZAF_nvm.h>
#include <cc_door_lock_config_api.h>
#include <cc_door_lock_io.h>
#include <Assert.h>
#include "zaf_event_distributor_soc.h"
#include "zaf_transport_tx.h"
#include <CC_Supervision.h>

//#define DEBUGPRINT
#include "DebugPrint.h"
/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/
#define SUPPORTED_OPERATIONS_LENGTH_BITMASK 0x1F  /**< Bitmask for Supported Opertation Type Length (5 bits)*/

/**
 * @addtogroup DoorLockCondition
 *
 * Door Lock Condition. Requirement  CC:0062.04.03.11.006
 * @{
 */
#define CC_DOOR_LOCK_BOLT_FLAG    (1U << 1)  ///< Bitmask for bolt condition
#define CC_DOOR_LOCK_LATCH_FLAG   (1U << 2)  ///< Bitmask for latch condition
/// @}

/* private function prototypes */
static void prepare_operation_report(ZW_APPLICATION_TX_BUFFER *pTxBuffer);
static uint8_t get_inside_outside_door_handle_mode(door_lock_mode_t mode);
static void prepare_configuration_report(ZW_APPLICATION_TX_BUFFER *pTxBuffer);

static void CC_DoorLock_configuration_report_stx(zaf_tx_options_t *tx_options, void* pData);
static void CC_DoorLock_operation_report_stx(zaf_tx_options_t *tx_options, void* pData);
static uint8_t operation_report_condition_get();

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/
/**
 * Command Class Door lock
 */
static cc_door_lock_data_t door_lock_data = { 0 };

/// Last used RX options. Used by TSE and supervision.
static RECEIVE_OPTIONS_TYPE_EX door_lock_rx_option;

// Remaining duration from the lock change.
static uint8_t remaining_duration = 0;

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/

/// Used when the change was triggered by local action.
/// In that case existing RX data must be cleared so that all Lifeline destinations are informed
static inline void doorlock_clear_rxopt()
{
  memset(&door_lock_rx_option, 0, sizeof(RECEIVE_OPTIONS_TYPE_EX));
}

/// Checks whether given mode is supported or not
static inline bool is_mode_valid(door_lock_mode_t mode)
{
  return ((mode == DOOR_MODE_UNSECURE) || (mode == DOOR_MODE_SECURED)) ? true : false;
}

/**
 * Returns current mode of the node
 * @return DOOR_MODE_SECURED if bolt is locked, DOOR_MODE_UNSECURE otherwize
 */
static door_lock_mode_t
getCurrentMode()
{
  return door_lock_hw_bolt_is_unlocked() ? DOOR_MODE_UNSECURE : DOOR_MODE_SECURED;
}


/**
 * @brief Stores the current status of the lock on/off
 * in the application NVM file system.
 */
static void
SaveStatus(void)
{
  bool status;

  door_lock_data.condition = operation_report_condition_get();
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

  // Ignore handles from the incomming frame which aren't supported by the application
  uint8_t inside_handles_to_set = cc_door_lock_get_supported_inside_handles() & pData->insideDoorHandleMode;
  uint8_t outside_handles_to_set = cc_door_lock_get_supported_outside_handles() & pData->outsideDoorHandleMode;

  if ((cc_door_lock_get_operation_type() == pData->type) &&
      !(cc_door_lock_get_max_auto_relock_time() < ((pData->autoRelockTime1 << 8) + pData->autoRelockTime2)) && // Fail if non-supported auto-relock time
      !(cc_door_lock_get_max_hold_and_release_time() < ((pData->holdAndReleaseTime1 << 8) + pData->holdAndReleaseTime2)) && // Fail if non-supported hold and release time
      !(~cc_door_lock_get_options_flags() & pData->reservedOptionsFlags )  // Fail if non-supported options flags
     )
  {
    if (door_lock_data.insideDoorHandleMode == inside_handles_to_set &&
        door_lock_data.outsideDoorHandleMode == outside_handles_to_set) {
      // Already at final state
      return E_CMD_HANDLER_RETURN_CODE_NO_CHANGE;
    }
    door_lock_data.insideDoorHandleMode  = inside_handles_to_set;
    door_lock_data.outsideDoorHandleMode = outside_handles_to_set;

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
    cc_handler_input_t *  input,
    cc_handler_output_t *  output)
{
  e_cmd_handler_return_code_t return_code;

  switch (input->frame->ZW_Common.cmd)
  {
    case DOOR_LOCK_OPERATION_SET_V4:
      if (!is_mode_valid(input->frame->ZW_DoorLockOperationSetV2Frame.doorLockMode))
      {
        DPRINTF("DOOR_LOCK_OPERATION_SET: Mode %#02x not supported, failing \r\n",
                input->frame->ZW_DoorLockOperationSetV2Frame.doorLockMode);
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      if (getCurrentMode() == input->frame->ZW_DoorLockOperationSetV2Frame.doorLockMode)
      {
        // Already at requested mode, nothing to change. Just exit with default return value
        break;
      }

      remaining_duration = cc_door_lock_mode_hw_change(
          input->frame->ZW_DoorLockOperationSetV2Frame.doorLockMode); 
      output->duration = remaining_duration;

      /* If the change was made, save rx options for later use */
      door_lock_rx_option = *(input->rx_options);

      if (0 < output->duration &&
          input->rx_options->bSupervisionActive &&
          (!is_multicast(input->rx_options)))
      {
        // Supervision is active and this is timed operation that started transition to final state
        return RECEIVED_FRAME_STATUS_WORKING;
      }
      break;

    case DOOR_LOCK_OPERATION_GET_V4:
      if (true == Check_not_legal_response_job(input->rx_options))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      prepare_operation_report(output->frame);

      output->length = sizeof(ZW_DOOR_LOCK_OPERATION_REPORT_V4_FRAME);
      break;

    case DOOR_LOCK_CONFIGURATION_SET_V2:
      return_code = CC_DoorLock_ConfigurationSet_handler(
          (cc_door_lock_configuration_t *)&(input->frame->ZW_DoorLockConfigurationSetV2Frame.operationType));

      if (E_CMD_HANDLER_RETURN_CODE_FAIL == return_code)
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      if (E_CMD_HANDLER_RETURN_CODE_NO_CHANGE == return_code)
      {
        // Nothing changed, just exit with default return value
        break;
      }
      /* If change was made, call TSE */
      if(E_CMD_HANDLER_RETURN_CODE_HANDLED == return_code)
      {
        // Build up new CC data structure
        door_lock_rx_option = *(input->rx_options);
        if (false == ZAF_TSE_Trigger(CC_DoorLock_configuration_report_stx, (void*)&door_lock_rx_option, true))
        {
          DPRINTF("%s(): ZAF_TSE_Trigger failed\n", __func__);
        }
      }
      break;

    case DOOR_LOCK_CONFIGURATION_GET_V2:
      if (true == Check_not_legal_response_job(input->rx_options))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      prepare_configuration_report(output->frame);

      output->length = sizeof(ZW_DOOR_LOCK_CONFIGURATION_REPORT_V4_FRAME);
      break;

    case DOOR_LOCK_CAPABILITIES_GET_V4:
      if (true == Check_not_legal_response_job(input->rx_options))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      output->frame->ZW_DoorLockCapabilitiesReport1byteV4Frame.cmdClass = COMMAND_CLASS_DOOR_LOCK_V4;
      output->frame->ZW_DoorLockCapabilitiesReport1byteV4Frame.cmd = DOOR_LOCK_CAPABILITIES_REPORT_V4;
      cc_door_lock_capabilities_report_t capabilities_report;
      memset((uint8_t *)&capabilities_report, 0x00, sizeof(capabilities_report));
      CC_DoorLock_CapabilitiesGet_handler(&capabilities_report);
      output->frame->ZW_DoorLockCapabilitiesReport1byteV4Frame.properties1 = 1 & SUPPORTED_OPERATIONS_LENGTH_BITMASK; // Length fixed to 1
      uint8_t *ptr = &output->frame->ZW_DoorLockCapabilitiesReport1byteV4Frame.supportedOperationTypeBitMask1;
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

      output->length = (uint8_t)(ptr - (uint8_t*)output->frame);
      break;
    default:
      return RECEIVED_FRAME_STATUS_NO_SUPPORT;
  }
  return RECEIVED_FRAME_STATUS_SUCCESS;
}

/**
 * The condition field in Door Lock Operation Report
 * Indicates the status of the door lock components such as bolt and latch states.
 * Used also to prepare data to be written to NVM
 * @return bitmask encoded by requirement CC:0062.04.03.11.006
 */
static uint8_t
operation_report_condition_get()
{
  uint8_t condition = 0;

  // Door mode is not supported

  // Bolt
  if (door_lock_hw_bolt_is_unlocked())
  {
    condition |= CC_DOOR_LOCK_BOLT_FLAG; /* Set bolt condition bit (1 -> bolt unlocked) */
  }
  else
  {
    condition &= (uint8_t)(~(CC_DOOR_LOCK_BOLT_FLAG)); /* Clear bolt condition bit (0 -> bolt locked) */
  }

  //Latch
  if (false == door_lock_hw_latch_is_closed())
  {
    condition &= (uint8_t) ~(CC_DOOR_LOCK_LATCH_FLAG);
  }
  else
  {
    condition |= CC_DOOR_LOCK_LATCH_FLAG;
  }

  DPRINTF("SetCondition con = %d\r\n", condition);
  return condition;
}

/**
 * Prepares payload for operation report to be sent
 * @param pTxBuffer Output payload
 */
static void prepare_operation_report(ZW_APPLICATION_TX_BUFFER *pTxBuffer)
{
  memset((uint8_t*)pTxBuffer, 0, sizeof(ZW_APPLICATION_TX_BUFFER) );
  ZW_DOOR_LOCK_OPERATION_REPORT_V4_FRAME * frame = (ZW_DOOR_LOCK_OPERATION_REPORT_V4_FRAME*)pTxBuffer;

  frame->cmdClass = COMMAND_CLASS_DOOR_LOCK_V4;
  frame->cmd = DOOR_LOCK_OPERATION_REPORT_V4;

  frame->currentDoorLockMode = (uint8_t)getCurrentMode();
  frame->properties1 = get_inside_outside_door_handle_mode(frame->currentDoorLockMode);
  frame->doorCondition =  operation_report_condition_get();
  frame->lockTimeoutMinutes = DOOR_LOCK_OPERATION_SET_TIMEOUT_NOT_SUPPORTED;;
  frame->lockTimeoutSeconds = DOOR_LOCK_OPERATION_SET_TIMEOUT_NOT_SUPPORTED;
  frame->targetDoorLockMode = frame->currentDoorLockMode; // Assuming instantaneous lock state change, target and current mode always equal
  frame->duration = remaining_duration; // How much time is left until state change (in seconds)
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
 * This function converts the command from being a Basic Set command
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

  memset(&door_lock_data, 0x00, sizeof(cc_door_lock_data_t));
  door_lock_data.type = cc_door_lock_get_operation_type();
  door_lock_data.insideDoorHandleMode  = cc_door_lock_get_supported_inside_handles();  /* all supported inside handles enabled */
  door_lock_data.outsideDoorHandleMode = cc_door_lock_get_supported_outside_handles();  /* all supported outside handles enabled */
  door_lock_data.lockTimeoutMin = DOOR_LOCK_OPERATION_SET_TIMEOUT_NOT_SUPPORTED;
  door_lock_data.lockTimeoutSec = DOOR_LOCK_OPERATION_SET_TIMEOUT_NOT_SUPPORTED;
  door_lock_data.outsideDoorHandleState = 0; /* Handles not being pressed */
  door_lock_data.insideDoorHandleState = 0; /* Handles not being pressed */
  door_lock_data.condition = 0;

  cc_door_lock_bolt_set(false);
  cc_door_lock_handle_set(false);
  cc_door_lock_latch_set(false);

  status = cc_door_lock_write(&door_lock_data);
  ASSERT(status);
}

static void init(void)
{
  bool status;
  cc_door_lock_data_t savedDoorLock;

  cc_door_lock_migrate();

  status = cc_door_lock_read(&savedDoorLock);

  if(status) {
    door_lock_data.type = savedDoorLock.type;
    door_lock_data.insideDoorHandleMode = savedDoorLock.insideDoorHandleMode;
    door_lock_data.outsideDoorHandleMode = savedDoorLock.outsideDoorHandleMode;
    /* NB: Door handle states (insideDoorHandleState and outsideDoorHandleState)
     * are not really part of the configuration. For that reason we do not
     * set them here even though they are part of the saved config data.
     */
    door_lock_data.lockTimeoutMin = savedDoorLock.lockTimeoutMin;
    door_lock_data.lockTimeoutSec = savedDoorLock.lockTimeoutSec;
    door_lock_data.condition = savedDoorLock.condition;

    cc_door_lock_bolt_set((savedDoorLock.condition & CC_DOOR_LOCK_BOLT_FLAG) ? false : true);
    // Always set latch to closed and handle to released
    cc_door_lock_latch_set(false);
    cc_door_lock_handle_set(false);
  } else {
    reset();
  }
}

/**
 * Called when hardware change triggered by Operation Set command is completed
 * It informs Lifeline destinations about new status
 * and triggers Supervision Report if required
 */
static void
cc_door_lock_operation_set_done()
{
  SaveStatus();

  remaining_duration = 0;

  ZAF_TSE_Trigger(
      CC_DoorLock_operation_report_stx,
      (void*)&door_lock_rx_option,
      true);

  if (!door_lock_rx_option.bSupervisionActive || !door_lock_rx_option.statusUpdate) {
    // Status update not requested, nothing to do
    return;
  }
  zaf_tx_options_t tx_options = {0};
  zaf_transport_rx_to_tx_options(&door_lock_rx_option, &tx_options);

  CmdClassSupervisionReportSend(
       &tx_options,
       door_lock_rx_option.sessionId, // This is last status update, no need to set anything.
       CC_SUPERVISION_STATUS_SUCCESS,
       0); // durationRemaining should always be 0 at this point
}

static void 
CC_DoorLock_operation_report_stx(zaf_tx_options_t *tx_options, void* pData)
{
  UNUSED(pData);
  DPRINTF("* %s() *\n"
      "\ttxOpt.src = %d\n"
      "\ttxOpt.options %#02x\n",
      __func__, tx_options->source_endpoint, tx_options->tx_options);

  /* Prepare payload for report */
  ZW_APPLICATION_TX_BUFFER txBuf;
  prepare_operation_report(&txBuf);

  (void) zaf_transport_tx((uint8_t *)&txBuf,
                          sizeof(ZW_DOOR_LOCK_OPERATION_REPORT_V4_FRAME),
                          ZAF_TSE_TXCallback,
                          tx_options);
}

static void 
CC_DoorLock_configuration_report_stx(zaf_tx_options_t *tx_options, void* pData)
{
  UNUSED(pData);
  DPRINTF("* %s() *\n"
      "\ttxOpt.src = %d\n"
      "\ttxOpt.options %#02x\n",
      __func__, tx_options->source_endpoint, tx_options->tx_options);

  /* Prepare payload for report */
  ZW_APPLICATION_TX_BUFFER txBuf;
  prepare_configuration_report(&txBuf);

  (void) zaf_transport_tx((uint8_t *)&txBuf,
                          sizeof(ZW_DOOR_LOCK_CONFIGURATION_REPORT_V4_FRAME),
                          ZAF_TSE_TXCallback,
                          tx_options);
}

/**
 * Gets Inside/Outside door handle mode in form expected by properties field of
 * ZW_DOOR_LOCK_OPERATION_REPORT_V4_FRAME
 *
 * @return properties value made of inside and outside door handle mode
 */
static uint8_t get_inside_outside_door_handle_mode(door_lock_mode_t mode)
{
  // Inside- and Outside Door Handle Mode must always report 0 if the current lock mode == SECURED
  uint8_t insideDoorHandleMode = (mode == DOOR_MODE_SECURED) ? 0 : door_lock_data.insideDoorHandleMode;
  uint8_t outsideDoorHandleMode = (mode == DOOR_MODE_SECURED) ? 0 : door_lock_data.outsideDoorHandleMode;

  return (uint8_t)((outsideDoorHandleMode << 4) | insideDoorHandleMode);
}

void CC_DoorLock_SetOutsideDoorHandleState(cc_door_lock_handle_t handle)
{
  UNUSED(handle); // Only one handle is supported
  DPRINTF("Set outsideDoorHandleState %d\r\n", handle);

  // Handle pressed
  cc_door_lock_handle_set(true);
  if (door_lock_data.outsideDoorHandleMode)
  {
    /* If handle is active/enabled, pressing the handle opens the latch
     * (req CC:0062.04.03.11.003) */
    cc_door_lock_latch_set(true);
    SaveStatus();

    //Notify the lifeline that the door handle activated
    doorlock_clear_rxopt();
    ZAF_TSE_Trigger(CC_DoorLock_operation_report_stx, &door_lock_rx_option, true);
  }
}

void CC_DoorLock_ClearOutsideDoorHandleState(cc_door_lock_handle_t handle)
{
  UNUSED(handle); // Only one handle is supported
  DPRINTF("Clear outsideDoorHandleState %d\r\n", handle);

  // Handle released
  cc_door_lock_handle_set(false);
  if (door_lock_data.outsideDoorHandleMode)
  {
    /* If handle is active/enabled, releasing the handle closes the latch
     * (req CC:0062.04.03.11.003) */
    SaveStatus();
    cc_door_lock_latch_set(false);

    //Notify the lifeline that the door handle deactivated
    doorlock_clear_rxopt();
    ZAF_TSE_Trigger(CC_DoorLock_operation_report_stx, &door_lock_rx_option, true);
  }
}

static void 
CC_DoorLock_Toggle(void)
{
  // We don't care about return value here, because there is no Supervision Report after local change
  cc_door_lock_mode_hw_change(
      (DOOR_MODE_SECURED == getCurrentMode()) ?
          DOOR_MODE_UNSECURE : DOOR_MODE_SECURED);
  SaveStatus();

  //Clean previously saved rx options.
  //TSE will be triggered automatically when the hardware is done with the change.
  doorlock_clear_rxopt();
}

ZW_WEAK void
cc_door_lock_handle_set(bool pressed)
{
  UNUSED(pressed);
}

ZW_WEAK void
cc_door_lock_bolt_set(bool locked)
{
  UNUSED(locked);
}

ZW_WEAK void
cc_door_lock_latch_set(bool opened)
{
  UNUSED(opened);
}

ZW_WEAK uint8_t
cc_door_lock_mode_hw_change(door_lock_mode_t mode)
{
  door_lock_data.mode = mode;
  // Fake that hardware change is done
  cc_door_lock_operation_set_done();
  return 2; // dummy value
}

ZW_WEAK bool door_lock_hw_bolt_is_unlocked()
{
  return true;
}

ZW_WEAK bool door_lock_hw_latch_is_closed()
{
  return true;
}

ZW_WEAK bool door_lock_hw_handle_is_pressed()
{
  return false;
}

/*
 * This will map this CC to Basic CC, so set commands by Basic CC can be routed to this Command Class for execution.
 */
REGISTER_CC_V5(COMMAND_CLASS_DOOR_LOCK, DOOR_LOCK_VERSION_V4, CC_DoorLock_handler, basic_set_mapper, basic_get_mapper, lifeline_reporting, 0, init, reset);

static void
door_lock_event_handler(const uint8_t event, const void *data)
{
  UNUSED(data);

  switch (event) {
    case CC_DOOR_LOCK_CODE_EVENT_TOGGLE:
      CC_DoorLock_Toggle();
      break;
    case CC_DOOR_LOCK_EVENT_HW_OPERATION_DONE:
      cc_door_lock_operation_set_done();
  }
}

ZAF_EVENT_DISTRIBUTOR_REGISTER_CC_EVENT_HANDLER(COMMAND_CLASS_DOOR_LOCK, door_lock_event_handler);
