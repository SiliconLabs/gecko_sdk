/***************************************************************************//**
 * @file
 * @brief Core interrupt handling API (Generic)
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef EM_CORE_GENERIC_H
#define EM_CORE_GENERIC_H

#include <stdbool.h>
#include <stdint.h>

/***************************************************************************//**
 * @addtogroup core
 * @{
 ******************************************************************************/

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

/** Use PRIMASK register to disable interrupts in ATOMIC sections. */
#define CORE_ATOMIC_METHOD_PRIMASK  0

/** Use BASEPRI register to disable interrupts in ATOMIC sections. */
#define CORE_ATOMIC_METHOD_BASEPRI  1

#if !defined(CORE_ATOMIC_BASE_PRIORITY_LEVEL)
/** The interrupt priority level disabled within ATOMIC regions. Interrupts
 *  with priority level equal to or lower than this definition will be disabled
 *  within ATOMIC regions. */
#define CORE_ATOMIC_BASE_PRIORITY_LEVEL  3
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 ************************   MACRO API   ***************************************
 ******************************************************************************/

//
//  CRITICAL section macro API.
//

/** Allocate storage for PRIMASK or BASEPRI value for use by
 *  CORE_ENTER/EXIT_ATOMIC() and CORE_ENTER/EXIT_CRITICAL() macros. */
#define CORE_DECLARE_IRQ_STATE        CORE_irqState_t irqState

/** CRITICAL style interrupt disable. */
#define CORE_CRITICAL_IRQ_DISABLE() CORE_CriticalDisableIrq()

/** CRITICAL style interrupt enable. */
#define CORE_CRITICAL_IRQ_ENABLE()  CORE_CriticalEnableIrq()

/** Convenience macro for implementing a CRITICAL section. */
#define CORE_CRITICAL_SECTION(yourcode) \
  {                                     \
    CORE_DECLARE_IRQ_STATE;             \
    CORE_ENTER_CRITICAL();              \
    {                                   \
      yourcode                          \
    }                                   \
    CORE_EXIT_CRITICAL();               \
  }

/** Enter CRITICAL section. Assumes that a @ref CORE_DECLARE_IRQ_STATE exist in
 *  scope. */
#define CORE_ENTER_CRITICAL()   irqState = CORE_EnterCritical()

/** Exit CRITICAL section. Assumes that a @ref CORE_DECLARE_IRQ_STATE exist in
 *  scope. */
#define CORE_EXIT_CRITICAL()    CORE_ExitCritical(irqState)

/** CRITICAL style yield. */
#define CORE_YIELD_CRITICAL()   CORE_YieldCritical()

//
//  ATOMIC section macro API.
//

/** ATOMIC style interrupt disable. */
#define CORE_ATOMIC_IRQ_DISABLE()   CORE_AtomicDisableIrq()

/** ATOMIC style interrupt enable. */
#define CORE_ATOMIC_IRQ_ENABLE()    CORE_AtomicEnableIrq()

/** Convenience macro for implementing an ATOMIC section. */
#define CORE_ATOMIC_SECTION(yourcode) \
  {                                   \
    CORE_DECLARE_IRQ_STATE;           \
    CORE_ENTER_ATOMIC();              \
    {                                 \
      yourcode                        \
    }                                 \
    CORE_EXIT_ATOMIC();               \
  }

/** Enter ATOMIC section. Assumes that a @ref CORE_DECLARE_IRQ_STATE exist in
 *  scope. */
#define CORE_ENTER_ATOMIC()   irqState = CORE_EnterAtomic()

/** Exit ATOMIC section. Assumes that a @ref CORE_DECLARE_IRQ_STATE exist in
 *  scope. */
#define CORE_EXIT_ATOMIC()    CORE_ExitAtomic(irqState)

/** ATOMIC style yield. */
#define CORE_YIELD_ATOMIC()   CORE_YieldAtomic()

/** Check if IRQ is disabled. */
#define CORE_IRQ_DISABLED()       CORE_IrqIsDisabled()

/** Check if inside an IRQ handler. */
#define CORE_IN_IRQ_CONTEXT()     CORE_InIrqContext()

/*******************************************************************************
 *************************   TYPEDEFS   ****************************************
 ******************************************************************************/

/** Storage for PRIMASK or BASEPRI value. */
typedef uint32_t CORE_irqState_t;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

void CORE_CriticalDisableIrq(void);
void CORE_CriticalEnableIrq(void);
void CORE_ExitCritical(CORE_irqState_t irqState);
void CORE_YieldCritical(void);
CORE_irqState_t CORE_EnterCritical(void);

void  CORE_AtomicDisableIrq(void);
void  CORE_AtomicEnableIrq(void);
void  CORE_ExitAtomic(CORE_irqState_t irqState);
void  CORE_YieldAtomic(void);
CORE_irqState_t CORE_EnterAtomic(void);

bool  CORE_InIrqContext(void);
bool  CORE_IrqIsDisabled(void);

#ifdef __cplusplus
}
#endif

/** @} (end addtogroup core) */

#endif /* EM_CORE_GENERIC_H */
