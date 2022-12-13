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
