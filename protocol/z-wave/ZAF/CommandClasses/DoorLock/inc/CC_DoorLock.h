/**
 * @file
 * Handler for Command Class Door Lock.
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _CC_DOORLOCK_H_
#define _CC_DOORLOCK_H_

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include <ZW_typedefs.h>
#include <ZW_classcmd.h>
#include <CC_Common.h>
#include <ZW_TransportEndpoint.h>
#include <ZAF_types.h>
#include "ZAF_CC_Invoker.h"

/**
 * @addtogroup CC
 * @{
 * @addtogroup DoorLock
 * @{
 */

/****************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                       */
/****************************************************************************/
/**
 * Door Lock Mode (8 bit) will set the door lock device in unsecured or
 * secured mode as well as other peripheral settings.
 *
 * 1) Constant mode. Door will be unsecured until set back to secured mode by Command.
 * 2) Timeout mode. Fallback to secured mode after timeout has expired (set by Door Lock Configuration Set).
 * 3) This is Read Only State, i.e. Bolt is not fully retracted/engaged
 */
typedef enum
{
  DOOR_MODE_UNSECURE = DOOR_LOCK_OPERATION_SET_DOOR_UNSECURED_V2,	/**< Door Unsecured 1)*/                                                                                            //!< DOOR_MODE_UNSECURE
  DOOR_MODE_UNSECURE_TIMEOUT = DOOR_LOCK_OPERATION_SET_DOOR_UNSECURED_WITH_TIMEOUT_V2,	/**< Door Unsecured with timeout 2)*/                                                          //!< DOOR_MODE_UNSECURE_TIMEOUT
  DOOR_MODE_UNSECURE_INSIDE = DOOR_LOCK_OPERATION_SET_DOOR_UNSECURED_FOR_INSIDE_DOOR_HANDLES_V2,	/**< Door Unsecured for inside Door Handles 1)*/                                     //!< DOOR_MODE_UNSECURE_INSIDE
  DOOR_MODE_UNSECURE_INSIDE_TIMEOUT = DOOR_LOCK_OPERATION_SET_DOOR_UNSECURED_FOR_INSIDE_DOOR_HANDLES_WITH_TIMEOUT_V2,	/**< Door Unsecured for inside Door Handles with timeout 2)*/   //!< DOOR_MODE_UNSECURE_INSIDE_TIMEOUT
  DOOR_MODE_UNSECURE_OUTSIDE = DOOR_LOCK_OPERATION_SET_DOOR_UNSECURED_FOR_OUTSIDE_DOOR_HANDLES_V2,	/**< Door Unsecured for outside Door Handles 1)*/                                  //!< DOOR_MODE_UNSECURE_OUTSIDE
  DOOR_MODE_UNSECURE_OUTSIDE_TIMEOUT = DOOR_LOCK_OPERATION_SET_DOOR_UNSECURED_FOR_OUTSIDE_DOOR_HANDLES_WITH_TIMEOUT_V2,	/**< Door Unsecured for outside Door Handles with timeout 2)*///!< DOOR_MODE_UNSECURE_OUTSIDE_TIMEOUT
  DOOR_MODE_UNKNOWN = DOOR_LOCK_OPERATION_SET_DOOR_LOCK_STATE_UNKNOWN_V2, /**<	Door/Lock State Unknown 3). (Version 2)*/                                                           //!< DOOR_MODE_UNKNOWN
  DOOR_MODE_SECURED = DOOR_LOCK_OPERATION_SET_DOOR_SECURED_V2	/**< Door Secured*/                                                                                                  //!< DOOR_MODE_SECURED
} door_lock_mode_t;

/**
 * Operation mode (1byte).
 * The Operation Type field can be set to either constant or timed operation. When
 * timed operation is set, the Lock Timer Minutes and Lock Timer Seconds fields
 * MUST be set to valid values.
 */
typedef enum
{
  DOOR_OPERATION_CONST = 0x01,   /**< Constant operation*/
  DOOR_OPERATION_TIMED = 0x02,   /**< Timed operation*/
  DOOR_OPERATION_RESERVED = 0x03 /**< 0X03..0XFF  Reserved*/
}
cc_door_lock_operation_type_t;

/**
 * Supported Door Components
 * Bitmask of supported door components. Set to 1 if corresponding component is supported.
 */
typedef enum
{
  DOOR_COMPONENT_DOOR = 0x01,
  DOOR_COMPONENT_BOLT = 0x02,
  DOOR_COMPONENT_LATCH = 0x04
} cc_door_lock_door_component_t;

/**
 * Supported Door Handles
 * Bitmask of supported door handles. Set to 1 if corresponding handle is supported.
 */
typedef enum
{
  DOOR_HANDLE_DISABLED = 0x00,
  DOOR_HANDLE_1 = 0x01,
  DOOR_HANDLE_2 = 0x02,
  DOOR_HANDLE_3 = 0x04,
  DOOR_HANDLE_4 = 0x08
} cc_door_lock_handle_t;

/**
 * Door Lock Capabilities Report data structure.
 * --------------------------------------------
 *
 * This allows the Application to inform the Command Class handler of the capabilities
 * of the Door Lock.
 *
 * The \ref supportedOperationTypeBitmask field indicates the Supported Operations Modes:
 *   - Bit 0 in Bit Mask 1: Reserved
 *   - Bit 1 in Bit Mask 1: Constant Operation
 *   - Bit 2 in Bit Mask 1: Timed Operation.
 *
 * The \ref supportedDoorLockModeList indicates the Supported Door Lock Modes:
 *   - 0x00: Door Unsecured
 *   - 0x01: Door unsecured with timeout
 *   - 0x10: Door Unsecured for Inside Door Handles
 *   - 0x11: Door Unsecured for Inside Door Handles with timeout
 *   - 0x20: Door Unsecured for Outside Door Handles
 *   - 0x21: Door Unsecured for Outside Door Handles with timeout
 *   - 0xFF: Door Secured
 *
 *
 * Inside/outside Door Handles Modes supported
 * These mode bits indicate which handles are supported on the Door Lock.
 *
 * The mode of the four inside and four outside door handles are encoded in
 * \ref supportedInsideHandleModes and \ref supportedOutsideHandleModes as:
 * - Bit 0: Handle 1
 * - Bit 1: Handle 2
 * - Bit 2: Handle 3
 * - Bit 3: Handle 4
 * Values:
 * - 0: disabled
 * - 1: enabled
 *
 * Supported Door Components.
 * The \ref supportedDoorComponents field indicates the supported Door Lock components:
 * such as bolt and latch states.
 * - Bit 0: Door
 * - Bit 1: Bolt
 * - Bit 2: Latch
 * - Bit 3-7: Reserved
 *
 * Auto Relock Support
 * The \ref autoRelockSupport flag indicates if the Door Lock Supports Auto Relock (1=supported, 0=not supported).
 *
 * Hold And Release Support
 * The \ref holdAndReleaseSupport flag indicates if the Door Lock Supports * Hold And Releaese (1=supported, 0=not supported),
 *
 * Twist Assist Support
 * The \ref twistAssistSupport flag indicates if the Door Lock Supports Twist Assist (1=supported, 0=not supported),
 *
 * Block To Block Support
 * The \ref blockToBlockSupport flag indicates if the Door Lock Supports Block To Block (1=supported, 0=not supported),
 */
typedef struct
{
  uint8_t reserved : 3; /**< Reserved (2 bits)*/
  uint8_t lengthSupportedOperationType : 5; /**< Length of Supported Operation Type Bitmask (5 bits)*/
  uint8_t supportedOperationTypeBitmask; /**< Supported Operation Types. Max. length fixed to 1 byte. Enough to hold both defined types defined in SDS13781. */
  uint8_t lengthSupportedDoorLockModeList; /**<  Length of supported Door Lock Mode List. */
  uint8_t supportedDoorLockModeList[8]; /**< List of Supported Door Lock Modes. Max. Length fixed to 8 byte. Enough to hold all modes defined in SDS13781. */
  uint8_t supportedOutsideHandleModes : 4; /**< Supported Outside Handle Modes bitmask (4 bits) */
  uint8_t supportedInsideHandleModes : 4; /**< Supported Inside Handle Modes bitmask (4 bits) */
  uint8_t supportedDoorComponents; /**< Supported Door Components */
  uint8_t autoRelockSupport : 1; /**< Indicates if the lock supports Auto Relock*/
  uint8_t holdAndReleaseSupport : 1; /**< Indicates if the lock supports Hold And Release */
  uint8_t twistAssistSupport : 1; /**< Indicates if the lock supports Twist Assist */
  uint8_t blockToBlockSupport : 1; /**< Indicates if the lock supports Twist Assist */
} cc_door_lock_capabilities_report_t;

/**
 * Door Lock Configuration Get/Set Structure
 * -----------------------------------------
 *
 * Inside/outside Door Handles Mode
 * These fields are used to configure if each individual outside and inside door handle can
 * open the door locally.
 *
 * The mode of the four inside and four outside door handles are encoded in
 * \ref insideDoorHandleMode and \ref outsideDoorHandleMode as:
 * - Bit 0: Handle 1
 * - Bit 1: Handle 2
 * - Bit 2: Handle 3
 * - Bit 3: Handle 4
 * Values:
 * - 0: disabled
 * - 1: enabled
 */
typedef struct
{
  uint8_t type; /** Operation mode - \ref cc_door_lock_operation_type_t */
  uint8_t insideDoorHandleMode : 4; /**< Inside Door Handles Mode (4 bits)*/
  uint8_t outsideDoorHandleMode : 4; /**< Outside Door Handles Mode (4 bits)*/
  uint8_t lockTimeoutMin; /**< Lock Timeout Minutes, valid values 1-254 decimal*/
  uint8_t lockTimeoutSec; /**< Lock Timeout Seconds, valid 1-59 decimal*/
  uint8_t autoRelockTime1; /**< Auto-relock time in seconds MSB */
  uint8_t autoRelockTime2; /**< Auto-relock time in seconds LSB */
  uint8_t holdAndReleaseTime1; /**< Hold and release time in seconds MSB */
  uint8_t holdAndReleaseTime2; /**< Hold and release time in seconds LSB */
  uint8_t reservedOptionsFlags; /**< Bit 0: Twist assist, bit 1: Block to block, others reserved */
} cc_door_lock_configuration_t;

/**
 * Cmd Class Door Lock data structure.
 * -----------------------------------
 *
 * - Inside/outside Door Handles Mode
 *   These mode bits indicate if the actual handle can open the door locally.
 *
 *   The mode of the four inside and four outside door handles are encoded in
 *   \ref insideDoorHandleMode and \ref outsideDoorHandleMode as:
 *   - Bit 0: Handle 1
 *   - Bit 1: Handle 2
 *   - Bit 2: Handle 3
 *   - Bit 3: Handle 4
 *   - Values:
 *     - 0: disabled
 *     - 1: enabled
 *
 * - Inside/outside Door Handles State
 *   These fields indicate if a door handle has been activated.
 *   The state of the four inside and four outside door handles are encoded in
 *   \ref insideDoorHandleState and \ref outsideDoorHandleState as follows:
 *   - Bit 0: Handle 1
 *   - Bit 1: Handle 2
 *   - Bit 2: Handle 3
 *   - Bit 3: Handle 4
 *   - Values:
 *     - 0: inactive
 *     - 1: activated
 *
 * @note Field \ref condition is used only for saving data to NVM.
 *       For needs of Operation Report, this bitmask is calculated based
 *       on actual latch/bolt/door values.
 *       It's recommended to use \ref door_lock_hw_data_t for hardware data.
 *
 * Door condition.
 * The \ref condition field indicates the status of the door lock components
 * such as bolt and latch states.
 * - Bit 0: Door
 *   - 0: Open
 *   - 1: Closed
 * - Bit 1: Bolt
 *   - 0: Locked
 *   - 1: Unlocked
 * - Bit 2: Latch
 *   - 0: Open
 *   - 1: Closed
 * - Bit 3-7: Reserved
 */
typedef struct
{
  door_lock_mode_t mode;
  cc_door_lock_operation_type_t type;
  uint8_t insideDoorHandleMode : 4; /**< Inside Door Handles Mode (4 bits)*/
  uint8_t outsideDoorHandleMode : 4; /**< Outside Door Handles Mode (4 bits)*/
  uint8_t insideDoorHandleState : 4; /**< Inside Door Handles State (4 bits)*/
  uint8_t outsideDoorHandleState : 4; /**< Outside Door Handles State (4 bits)*/
  uint8_t condition; /**< Door condition (8 bits)*/
  uint8_t lockTimeoutMin; /**< Lock Timeout Minutes, valid values 1-254 decimal*/
  uint8_t lockTimeoutSec; /**< Lock Timeout Seconds, valid 1-59 decimal*/
} cc_door_lock_data_t;

/**
 * Physical components of Door Lock.
 * Structure follows but it's not limited to requirement CC:0062.04.03.11.006
 * Structure can be expanded with additional HW components.
 */
typedef struct _door_lock_hw_data_t
{
  // bool door_closed;   /// true for Closed, false for Open
  bool bolt_unlocked;  /// True for unlocked, false for locked
  bool latch_closed;   /// True for Closed, false for Open
  bool handle_pressed; /// True for pressed, false for not pressed
                       /// @note This is simplified implementation of handle.
                       /// Specification defines inside and outside multiple handles
} door_lock_hw_data_t;

/**
 * Disabling Lock timeout minutes and seconds.
 */
#define DOOR_LOCK_OPERATION_SET_TIMEOUT_NOT_SUPPORTED 0xFE

/**
 * @addtogroup DoorLockEvents
 * @{
 */

#define CC_DOOR_LOCK_CODE_EVENT_TOGGLE        1
#define CC_DOOR_LOCK_EVENT_OPERATION_SET_DONE 2 /// Command class done (CC Door Lock -> CC Supervision)
#define CC_DOOR_LOCK_EVENT_HW_OPERATION_DONE  3 /// Hardware completed the change (HW -> CC)
/// @}

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/


/****************************************************************************/
/*                           EXPORTED FUNCTIONS                             */
/****************************************************************************/

/**
 * Latch status handler. Called when latch status is changed.
 *
 * @param[in] opened Latch status. True if latch is opened, false if closed.
 */
void cc_door_lock_latch_set(bool opened);

/**
 *
 * @param opened
 */
void cc_door_lock_handle_set(bool opened);

/**
 * Bolt status handler. Called when bolt status is changed.
 *
 * @param[in] locked Bolt status. True if bolt is locked, false if unlocked.
 */
void cc_door_lock_bolt_set(bool locked);

/**
 * Sets the Outside Door Handle State for a specific handle
 * 
 * @param handle handle to be set
 */
void CC_DoorLock_SetOutsideDoorHandleState(cc_door_lock_handle_t handle);

/**
 * Clears the Outside Door Handle State for a specific handle
 * 
 * @param handle handle to be cleared
 */
void CC_DoorLock_ClearOutsideDoorHandleState(cc_door_lock_handle_t handle);

/**
 * Initiates change on the hardware that changes door lock mode.
 * Can be called after operation has been triggered locally, or
 * valid Operation Set command was received
 *
 * @param mode Door Lock Mode to be set
 *
 * @return Remaining duration in seconds
 */
extern uint8_t cc_door_lock_mode_hw_change(door_lock_mode_t mode);

/**
 * Returns bolt state.
 * @return True if unlocked, false if locked
 */
extern bool door_lock_hw_bolt_is_unlocked(void);

/**
 *
 * @return
 */
extern bool door_lock_hw_latch_is_closed(void);

/**
 *
 * @return
 */
extern bool door_lock_hw_handle_is_pressed(void);

/**
 * @}
 * @}
 */ 


#endif /* _CC_DOORLOCK_H_ */
