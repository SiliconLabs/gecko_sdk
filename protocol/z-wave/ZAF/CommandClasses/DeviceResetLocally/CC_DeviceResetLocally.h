/**
 * @file
 * Handler for Command Class Device Reset Locally.
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _CC_DEVICE_RESET_LOCALLY_H_
#define _CC_DEVICE_RESET_LOCALLY_H_

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include <ZW_classcmd.h>
#include <CC_Common.h>

/****************************************************************************/
/*                       PUBLIC TYPES and DEFINITIONS                       */
/****************************************************************************/

// Nothing here.

/****************************************************************************/
/*                            PUBLIC FUNCTIONS                              */
/****************************************************************************/

/**
 * Transmits a Device Reset Locally Notification.
 * @param[in] pProfile Pointer to AGI profile.
 * @param[in] pCallback Callback function pointer. Use the callback call to reset the node.
 * This function callback MUST be implemented.
 */
void CC_DeviceResetLocally_notification_tx(
  const agi_profile_t * pProfile,
  void(* pCallback)(transmission_result_t * pTransmissionResult));

#endif
