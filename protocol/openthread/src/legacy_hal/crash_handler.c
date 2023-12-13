/***************************************************************************/
/**
 * @file
 *
 * @brief This implements a crash handler that save some register and stack data
 * and prints it on the following boot
 *
 * @note This is heavily based on the crash handler in the `legacy_hal_soc` component
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include PLATFORM_HEADER

#include <stdint.h>

#include "crash_handler.h"

#ifdef CORTEXM3
#include "cortexm3/diagnostic.h"
#endif

#include "em_chip.h"

void sl_ot_crash_handler_init(void)
{
  halInternalClassifyReset();

  // To be able to give more details on errors, we want faults enabled so
  // they're not all forced into hard faults.
  SCB->SHCSR |= (SCB_SHCSR_BUSFAULTENA_Msk
                 | SCB_SHCSR_MEMFAULTENA_Msk
#ifdef SCB_SHCSR_SECUREFAULTENA_Msk
                 | SCB_SHCSR_SECUREFAULTENA_Msk
#endif
                 | SCB_SHCSR_USGFAULTENA_Msk);

  //Fill the unused portion of the memory reserved for the stack.
  //memset() is not being used to do this in case it uses the stack
  //to store the return address.
  volatile uint32_t *dataDestination;
  //This code assumes that the __get_MSP() return value and
  //_CSTACK_SEGMENT_BEGIN are both 32-bit aligned values.
  dataDestination = (uint32_t*) (__get_MSP() - 4U);
  //Start at current stack ptr fill up until CSTACK_SEGMENT_BEGIN
  while (dataDestination >= _CSTACK_SEGMENT_BEGIN) {
    //Fill with magic value interpreted by C-SPY's Stack View
    *dataDestination-- = STACK_FILL_VALUE;
  }

}
