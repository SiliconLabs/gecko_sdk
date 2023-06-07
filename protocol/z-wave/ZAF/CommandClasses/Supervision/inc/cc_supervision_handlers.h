/**
 * @file
 * Command Class Supervision Handler Callbacks
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef CC_SUPERVISION_HANDLERS_H
#define CC_SUPERVISION_HANDLERS_H

#include <CC_Supervision.h>
#include <stdint.h>

/**
 * @addtogroup CC
 * @{
 * @addtogroup Supervision
 * @{
 */

/**
 * @brief Invoked upon reception of a Supervision Get
 * This function is weakly defined in CC_Supervision.c and can be defined in the application if desired.
 * 
 * @param pArgs parameters for the handler
 */
void cc_supervision_get_received_handler(SUPERVISION_GET_RECEIVED_HANDLER_ARGS * pArgs);

/**
 * @brief Invoked upon reception of a Supervision Report
 * This function is weakly defined in CC_Supervision.c and can be defined in the application if desired.
 * 
 * @param status the required status
 * @param duration the required duration
 */
void cc_supervision_report_recived_handler(cc_supervision_status_t status, uint8_t duration);

/**
 * @}
 * @}
 */ 

#endif /* CC_SUPERVISION_HANDLERS_H */
