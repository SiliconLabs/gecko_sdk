/*
 *  Copyright (c) 2021, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   This file implements the OpenThread platform abstraction for the diagnostics.
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>

#include "common/code_utils.hpp"
#include <openthread/cli.h>
#include <openthread-core-config.h>
#include <openthread/platform/alarm-milli.h>
#include <openthread/platform/diag.h>
#include <openthread/platform/radio.h>
#include "platform-efr32.h"

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
#include "coexistence-802154.h"
#endif // SL_CATALOG_RAIL_UTIL_COEX_PRESENT

#if OPENTHREAD_CONFIG_DIAG_ENABLE

/**
 * Diagnostics mode variables.
 *
 */
static bool sDiagMode = false;

void otPlatDiagModeSet(bool aMode)
{
    sDiagMode = aMode;
}

bool otPlatDiagModeGet()
{
    return sDiagMode;
}

void otPlatDiagChannelSet(uint8_t aChannel)
{
    OT_UNUSED_VARIABLE(aChannel);
}

void otPlatDiagTxPowerSet(int8_t aTxPower)
{
    OT_UNUSED_VARIABLE(aTxPower);
}

void otPlatDiagRadioReceived(otInstance *aInstance, otRadioFrame *aFrame, otError aError)
{
    OT_UNUSED_VARIABLE(aInstance);
    OT_UNUSED_VARIABLE(aFrame);
    OT_UNUSED_VARIABLE(aError);
}

void otPlatDiagAlarmCallback(otInstance *aInstance)
{
    OT_UNUSED_VARIABLE(aInstance);
}

//coex
otError otPlatDiagCoexSetPriorityPulseWidth(uint8_t pulseWidthUs)
{   
  #ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT  
  //Actual call on rcp side
  sl_status_t status = sl_rail_util_coex_set_directional_priority_pulse_width(pulseWidthUs);

  return (status != SL_STATUS_OK) ? OT_ERROR_FAILED : OT_ERROR_NONE;
  #endif //SL_CATALOG_RAIL_UTIL_COEX_PRESENT
  return OT_ERROR_FAILED; 
}

otError otPlatDiagCoexSetRadioHoldoff(bool enabled)
{
  #ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT  
        //Actual call on rcp side
  sl_status_t status = sl_rail_util_coex_set_radio_holdoff(enabled);

  return (status != SL_STATUS_OK) ? OT_ERROR_FAILED : OT_ERROR_NONE;
  #endif //SL_CATALOG_RAIL_UTIL_COEX_PRESENT
  return OT_ERROR_FAILED;        
}

otError otPlatDiagCoexSetRequestPwm(uint8_t ptaReq,
                                              void* ptaCb,
                                              uint8_t dutyCycle,
                                              uint8_t periodHalfMs)
{
  OT_UNUSED_VARIABLE(ptaCb);
  #ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT  
  sl_status_t status = sl_rail_util_coex_set_request_pwm(ptaReq,
                                            NULL,
                                            dutyCycle,
                                            periodHalfMs);
  return (status != SL_STATUS_OK) ? OT_ERROR_FAILED : OT_ERROR_NONE;   
  #endif //SL_CATALOG_RAIL_UTIL_COEX_PRESENT
  return OT_ERROR_FAILED;        
}
otError otPlatDiagCoexSetPhySelectTimeout(uint8_t timeoutMs) 
{
  #ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT    
  sl_status_t status = sl_rail_util_coex_set_phy_select_timeout(timeoutMs);
  return (status != SL_STATUS_OK) ? OT_ERROR_FAILED : OT_ERROR_NONE;
  #endif //SL_CATALOG_RAIL_UTIL_COEX_PRESENT
  return OT_ERROR_FAILED;
}  

otError otPlatDiagCoexSetOptions(uint32_t options)
{
  #ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT  
  sl_status_t status = sl_rail_util_coex_set_options(options);
  return (status != SL_STATUS_OK) ? OT_ERROR_FAILED : OT_ERROR_NONE;
  #endif //SL_CATALOG_RAIL_UTIL_COEX_PRESENT
  return OT_ERROR_FAILED;
}

otError otPlatDiagCoexGetPhySelectTimeout(uint8_t* timeoutMs) 
{
  #ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
  if(timeoutMs != NULL){ 
    *timeoutMs = sl_rail_util_coex_get_phy_select_timeout();
    return OT_ERROR_NONE; 
  }
  #endif //SL_CATALOG_RAIL_UTIL_COEX_PRESENT
  return OT_ERROR_FAILED;
}  

otError otPlatDiagCoexGetOptions(uint32_t* options)
{
  #ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
  if(options != NULL){ 
    *options = sl_rail_util_coex_get_options();
    return OT_ERROR_NONE; 
  }
  #endif //SL_CATALOG_RAIL_UTIL_COEX_PRESENT
  return OT_ERROR_FAILED;
}

otError otPlatDiagCoexGetPriorityPulseWidth(uint8_t* pulseWidthUs)
{
    #ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    if(pulseWidthUs != NULL){ 
      *pulseWidthUs = sl_rail_util_coex_get_directional_priority_pulse_width();
      return OT_ERROR_NONE;
    }
    #endif //SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    return OT_ERROR_FAILED;
}

otError otPlatDiagCoexGetRequestPwmArgs(  uint8_t* req,
  uint8_t* dutyCycle,
  uint8_t* periodHalfMs)
{
  #ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
  if(req != NULL
     && dutyCycle != NULL 
     && periodHalfMs != NULL){ 
    const sl_rail_util_coex_pwm_args_t *p = sl_rail_util_coex_get_request_pwm_args();
    *req = p->req ;
    *dutyCycle = p->dutyCycle ;
    *periodHalfMs = p->periodHalfMs ;
    return OT_ERROR_NONE;
  } 
  #endif //SL_CATALOG_RAIL_UTIL_COEX_PRESENT
  return OT_ERROR_FAILED;
}
#endif // #if OPENTHREAD_CONFIG_DIAG_ENABLE
