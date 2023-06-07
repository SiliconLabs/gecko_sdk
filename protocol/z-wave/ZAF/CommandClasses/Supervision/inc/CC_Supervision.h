/**
 * @file
 * Handler for Command Class Supervision.
 * @copyright 2018 Silicon Laboratories Inc.
 *
 * @addtogroup CC
 * @{
 * @addtogroup Supervision
 * @{
 *
 * ## Description
 * CC Supervision is built into the Application Framework and handles
 * Supervision communication on S2 encapsulated frames.
 * Supervision is only supported for Set and Report commands.
 *
 * Command Class Supervision is default configuration to not support more Supervision
 * reports on a Supervision Get command. In Supervision Get command is 'more status
 * updates' field set to CC_SUPERVISION_STATUS_UPDATES_NOT_SUPPORTED.
 *
 * ### Default configuration
 * The default setting is that CC Supervision supports only one Supervision Report per Supervision Get command.
 * In Supervision Get command, the 'more status updates' field is set to CC_SUPERVISION_STATUS_UPDATES_NOT_SUPPORTED.
 *
 * ### Handle more Supervision Reports
 * Device has the possibility to inform destination node that there is an operation in progress.
 * Example is Wall controller with a display showing that a device is working (CC_SUPERVISION_STATUS_WORKING)
 * until target value is reached (CC_SUPERVISION_STATUS_SUCCESS).
 * Please see \ref cc_supervision_report_recived_handler() for more details.
 *
 * ### Control Supervision Reports
 * Device has the possibility to send more Supervision Reports to report
 * ongoing Request job. Example application Doorlock Keypad reports when Doorlock
 * operation is started and also sends a new report when it's finished.
 * For this purpose, `cc_supervision_get_received_handler()` can be used.
 * Please see \ref cc_supervision_get_received_handler() for more details.
 *
 * @}
 * @}
 */

#ifndef _COMMAND_CLASS_SUPERVISION_H_
#define _COMMAND_CLASS_SUPERVISION_H_

#include <stdint.h>
#include <ZW_classcmd.h>
#include "zaf_transport_tx.h"
#include "ZAF_CC_Invoker.h"

/**
 * @addtogroup Supervision
 * @{
 */

#define CC_SUPERVISION_EXTRACT_SESSION_ID(properties)  (properties & 0x3F) /**< extract session id from properties bits [0..5] */
#define CC_SUPERVISION_ADD_SESSION_ID(properties)  (properties & 0x3F)     /**< add session id from properties bits [0..5] */
#define CC_SUPERVISION_EXTRACT_MORE_STATUS_UPDATE(status) (status >> 7)    /**< extract more status update field bit 7, CC SUPERVISION_REPORT */
#define CC_SUPERVISION_ADD_MORE_STATUS_UPDATE(status)  (status << 7)       /**< status values: {0,1}. Set bit 7, CC SUPERVISION_REPORT */
#define CC_SUPERVISION_EXTRACT_STATUS_UPDATE(status) (status >> 7)    /**< extract more status update field bit 7, CC SUPERVISION_GET */
#define CC_SUPERVISION_ADD_STATUS_UPDATE(status)  (status << 7)       /**< status values: {0,1}. Set bit 7, CC SUPERVISION_GET */

/**
 * @addtogroup Supervision_Events Supervision Events
 *
 * Events supported by Supervision CC
 * App or other CC can trigger these events by calling \ref zaf_event_distributor_enqueue_cc_event
 * @{
 */
#define CC_SUPERVISION_EVENT_SUCCESS 1
#define CC_SUPERVISION_EVENT_FAIL    2
#define CC_SUPERVISION_EVENT_WORKING 3
/// @}

/**
 * Enum type is used in CC SUPERVISION_REPORT to allow a receiving node to advertise
 * application status updates in future Supervision Report Commands
 */
typedef enum
{
  CC_SUPERVISION_MORE_STATUS_UPDATES_THIS_IS_LAST,    ///< CC_SUPERVISION_MORE_STATUS_UPDATES_THIS_IS_LAST
  CC_SUPERVISION_MORE_STATUS_UPDATES_REPORTS_TO_FOLLOW///< CC_SUPERVISION_MORE_STATUS_UPDATES_REPORTS_TO_FOLLOW
} cc_supervision_more_status_updates_t;

/**
 * Status of Supervision.
 */
typedef enum _SUPERVISION_STATUS_
{
  CC_SUPERVISION_STATUS_NOT_SUPPORTED,/**< SUPERVISION_STATUS_NOT_SUPPORTED */
  CC_SUPERVISION_STATUS_WORKING,      /**< SUPERVISION_STATUS_WORKING */
  CC_SUPERVISION_STATUS_FAIL,         /**< SUPERVISION_STATUS_FAIL */
  CC_SUPERVISION_STATUS_CANCEL,       /**< CC Supervision shouldn't do anything with this frame,
                                           report will be sent from somewhere else*/
  CC_SUPERVISION_STATUS_NOT_FOUND,    /**< CC handler was not found in CC handler map */
  CC_SUPERVISION_STATUS_SUCCESS = 0xFF/**< SUPERVISION_STATUS_SUCCESS */
} cc_supervision_status_t;

/**
 * This struct is used for the arguments in cc_supervision_get_receive_handler function
 * pointer in init_and_reset.
 */
typedef struct
{
  uint8_t cmdClass; /**< Input */
  uint8_t cmd; /**< Input */
  uint8_t properties1; /**< Input: bit[0..5] session id, bit[7] status update disable/enable.
                         Output: bit[0..5] session id, bit[7] more status updates of type cc_supervision_more_status_updates_t */
  cc_supervision_status_t status; /**< Output */
  uint8_t duration; /**< Output */
  RECEIVE_OPTIONS_TYPE_EX * rxOpt; /**< Input */
}
SUPERVISION_GET_RECEIVED_HANDLER_ARGS;

/**
 * Structure used by supervision_event_handler() to process upcoming events
 * Registered for CC Supervision
 */
typedef struct _cc_supervision_report_event {
  zaf_tx_options_t tx_options;  /// TX data to be used to send Supervision Report
  uint8_t session_id;             /// Supervision session Id
  bool status_update;             /// Status Update. True if more reports will follow
  uint8_t duration;               /// Remaining duration. 0 if application is in final state
} cc_supervision_report_event;

/**
 * @brief CmdClassSupervisionReportSend
 * @param[in] tx_options Transmit options of type zaf_tx_options_t
 * @param[in] properties includes:
 *  bit[0..5] Session ID
 *  bit[6] unused and
 *  bit[7] more status updates. This field is used to advertise if more Supervision Reports
 *  follow for the actual Session ID. [0] last report, [1] more report follow.
 * @param[in] status Supervision status.
 * @param[in] duration The duration must comply with the following:
 * 0x00 0 seconds. (Already at the Target Value.)
 * 0x01-0x7F  1 second (0x01) to 127 seconds (0x7F) in 1 second resolution.
 * 0x80-0xFD  1 minute (0x80) to 126 minutes (0xFD) in 1 minute resolution.
 * 0xFE Unknown duration
 * 0xFF Reserved
 * @return true if the frame was enqueued else false
 */
bool
CmdClassSupervisionReportSend(
  zaf_tx_options_t* tx_options,
  uint8_t properties,
  cc_supervision_status_t status,
  uint8_t duration);


/**
 * Creates payload for Supervision Get command by calling
 * \ref CommandClassSupervisionGetWrite and updates supervision session ID.
 * Used by Framework and should not be used be application.
 *
 * @param[in,out] pPayload pointer to supervision get payload
 */
void CommandClassSupervisionGetAdd(ZW_SUPERVISION_GET_FRAME* pPayload);


/**
 * Generates payload for Supervision Get command.
 * Used by Framework and should not be used be application.
 *
 * @param[in,out] pbuf Pointer to supervision get payload
 */
void
CommandClassSupervisionGetWrite(ZW_SUPERVISION_GET_FRAME* pbuf);

/**
 * Sets the payload length in a Supervision Get command.
 * Used by Framework when sending supervision-encapsulated frames
 *
 * @param[in] pbuf Pointer to supervision get payload
 * @param[in] payLoadlen Payload length to be set.
 */
void CommandClassSupervisionGetSetPayloadLength(ZW_SUPERVISION_GET_FRAME* pbuf, uint8_t payLoadlen);


/**
 * Gets the length of encapsulated payload from the frame.
 * Used by framework to calculate the length of the payload in supervision-encapsulated frames.
 *
 * @param pbuf Frame that contains the encapsulated command
 * @return length of the payload
 */
uint8_t CommandClassSupervisionGetGetPayloadLength(ZW_SUPERVISION_GET_FRAME* pbuf);

/// @}

#endif /*_COMMAND_CLASS_SUPERVISION_H_*/

