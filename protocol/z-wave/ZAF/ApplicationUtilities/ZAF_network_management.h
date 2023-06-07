/**
*
* @file
* Network management utility functions
*
* @copyright 2019 Silicon Laboratories Inc.
*
*/

#ifndef _ZAF_NETWORK_MANAGEMENT_H_
#define _ZAF_NETWORK_MANAGEMENT_H_

#include <stdint.h>
#include <ZW_application_transport_interface.h>

/**
 * @addtogroup ZAF
 * @{
 * @addtogroup Network
 * @{
 * @addtogroup NetworkManagement Network Management
 * @{
 */

/**
 * Command to set the maximum inclusion request interval.
 *
 * A status message with type=EZWAVECOMMANDSTATUS_ZW_SET_MAX_INCL_REQ_INTERVALS
 * is returned to the application command status queue when the command has
 * completed.
 *
 * @param intervals The maximum number of seconds in units of 128sec/tick in between
 * SmartStart inclusion requests. Valid range 0 and 5-99.
 * 0 is default value and corresponds to 512 sec.
 * The range 5-99 corresponds to 640-12672sec.
 */
void ZAF_SetMaxInclusionRequestIntervals(uint32_t intervals);

/**
 * Broadcasts an Included Node Information Frame (INIF).
 *
 * @param pCallback Pointer to a callback function that will be invoked when transmission is
 *                  successful or has failed.
 */
void ZAF_SendINIF(void (*pCallback)(uint8_t txStatus, TX_STATUS_TYPE* extendedTxStatus));

/**
 * @}
 * @}
 * @}
 */

#endif /* _ZAF_NETWORK_MANAGEMENT_H_ */
