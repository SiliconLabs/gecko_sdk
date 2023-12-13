/**
* Controlling implementation of Basic Command Class.
*
* @copyright 2018 Silicon Laboratories Inc.
*/

#include "CC_Basic.h"
#include "CC_Common.h"

zaf_job_status_t CC_Basic_Set_tx(
  agi_profile_t const * const p_profile,
  const uint8_t source_endpoint,
  const uint8_t value,
  const bool use_supervision,
  ZAF_TX_Callback_t callback)
{
  ccc_pair_t ccc_pair = {
    .cmdClass=COMMAND_CLASS_BASIC,
    .cmd=BASIC_SET
  };

  return cc_engine_multicast_request(
      p_profile,
      source_endpoint,
      &ccc_pair,
      (uint8_t *)&value,
      sizeof(value),
      use_supervision,
      callback);
}
