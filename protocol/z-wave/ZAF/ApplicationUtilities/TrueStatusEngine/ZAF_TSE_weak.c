/**
 * TSE : Allows building applications without TSE module being included.
 * @copyright 2022 Silicon Laboratories Inc.
 */

#include "ZAF_TSE.h"


ZW_WEAK bool ZAF_TSE_Trigger( __attribute__((unused)) zaf_tse_callback_t pCallback,
                              __attribute__((unused)) void* pData,
                              __attribute__((unused)) bool overwrite_previous_trigger)
{
  return true;
}


ZW_WEAK bool ZAF_TSE_Init(void)
{
  return true;
}


ZW_WEAK void ZAF_TSE_TXCallback(__attribute__((unused)) transmission_result_t * pTransmissionResult)
{
}
