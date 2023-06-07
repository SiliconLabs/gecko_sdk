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
