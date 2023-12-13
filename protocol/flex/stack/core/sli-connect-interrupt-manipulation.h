/***************************************************************************//**
 * @brief Include em_core in the stack for interrupt manipulation.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef __SLI_CONNECT_INTERRUPT_MANIPULATION_H__
#define __SLI_CONNECT_INTERRUPT_MANIPULATION_H__

#ifdef EMBER_TEST // Simulation stubs
#include <stdio.h>
#define CORE_DECLARE_IRQ_STATE
#define CORE_ENTER_ATOMIC()
#define CORE_EXIT_ATOMIC()
#define CORE_ATOMIC_IRQ_ENABLE()
#define CORE_ATOMIC_IRQ_DISABLE()
#define CORE_IrqIsDisabled()            true
#define CORE_ATOMIC_SECTION(some_code)  some_code
#define CORE_YIELD_ATOMIC()
#else
#include "em_core.h"
#endif // EMBER_TEST
#endif // __SLI_CONNECT_INTERRUPT_MANIPULATION_H__
