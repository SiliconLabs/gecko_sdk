/**
 * @file
 * Handler for Command Class Basic.
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _CC_BASIC_H_
#define _CC_BASIC_H_

#include "ZAF_types.h"

/**
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup Basic
 * @{
 */

/**
 * Invoked upon reception of a Basic Set command.
 *
 * This function is weakly defined in CC_Basic.c and thus can be defined in the application in case
 * it's desired that application handles the Basic Set mapping.
 *
 * @deprecated This function is no longer required to be implemented in the application as the
 *             Basic Set mapping is done automatically by ZAF assuming that all relevant command
 *             classes implement as Basic Set mapper function. The function will be removed in
 *             7.20.0.
 *
 * @param[in] val parmeter dependent of the application device class
 * @param[in] endpoint is the destination endpoint
 * @return command handler return code
 */
e_cmd_handler_return_code_t CC_Basic_Set_handler(
  uint8_t val,
  uint8_t endpoint
);

/**
 * Send unsolicited command class Basic report
 * @param[in] pProfile pointer to AGI profile
 * @param[in] sourceEndpoint source endpoint
 * @param[in] bValue Basic Report value
 * @param[out] callback callback function pointer returning status on job. Can be initialized to NULL.
 * @return status of the job of type JOB_STATUS
 */
JOB_STATUS CC_Basic_Report_tx(
  AGI_PROFILE* pProfile,
  uint8_t sourceEndpoint,
  uint8_t bValue,
  ZAF_TX_Callback_t callback);

/**
 * Sends an unsolicited Basic Set command.
 *
 * @param[in] p_profile Pointer to an AGI profile defined in the configuration of CC AGI.
 * @param[in] source_endpoint Source endpoint if the sending device use endpoints. Otherwise 0.
 * @param[in] value Value as defined in the specification of the command.
 * @param[in] use_supervision Use Supervision for transmission of this Basic Set.
 * @param[out] callback Callback function pointer giving a result of the transmission.
 * @return Status on whether the transmission could be initiated.
 */
zaf_job_status_t CC_Basic_Set_tx(
  agi_profile_t const * const p_profile,
  const uint8_t source_endpoint,
  const uint8_t value,
  const bool use_supervision,
  ZAF_TX_Callback_t callback);

/**
 * @}
 * @}
 */

#endif
