/**
 * @file
 * Common types and definitions for all command classes.
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _COMMANDCLASS_COMMON_H_
#define _COMMANDCLASS_COMMON_H_

#include <stdint.h>
#include <ZW_typedefs.h>
#include "ZAF_types.h"

/**
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup Common
 * @{
 */

/**
 * Initiates the transmission of a multicast request
 * 
 * @param[in] pProfile pointer to AGI profile or NULL for lifeline
 * @param[in] endpoint source endpoint
 * @param[in] pcmdGrp command class and command
 * @param[in] pPayload payload
 * @param[in] size size of payload
 * @param[in] fSupervisionEnable enable or not supervision
 * @param[in] pCbFunc Callback function to be called when transmission is done/failed.
 * @return JOB_STATUS Status of the job.
 */
JOB_STATUS cc_engine_multicast_request(const AGI_PROFILE* pProfile,
                                       uint8_t endpoint,
                                       CMD_CLASS_GRP *pcmdGrp,
                                       uint8_t* pPayload,
                                       uint8_t size,
                                       uint8_t fSupervisionEnable,
                                       void (*pCbFunc)(TRANSMISSION_RESULT * pTransmissionResult));

/**
 * @}
 * @}
 */
#endif /* _COMMANDCLASS_COMMON_H_ */
