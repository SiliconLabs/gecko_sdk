/***************************************************************************//**
 * @file
 * @brief Ultra Low Energy Timer/Counter (CRYOTIMER) peripheral API
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef EM_CRYOTIMER_H
#define EM_CRYOTIMER_H

#include <stdbool.h>
#include "em_device.h"
#include "em_bus.h"

#if defined(CRYOTIMER_PRESENT) && (CRYOTIMER_COUNT == 1)

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup cryotimer CRYOTIMER - Ultra Low Energy Timer
 * @brief Ultra Low Energy Timer/Counter (CRYOTIMER) Peripheral API
 *
 * @details
 *   The CRYOTIMER is a 32 bit counter, which operates on a low-frequency
 *   oscillator and is capable of running in all Energy Modes. It can provide
 *   periodic wakeup events and PRS signals, which can be used to wake up
 *   peripherals from any energy mode. The CRYOTIMER provides a wide range
 *   of periods for the interrupts facilitating flexible ultra-low energy
 *   operation. Because of its simplicity, the CRYOTIMER is a lower energy
 *   solution for periodically waking up the MCU compared to the RTCC.
 *
 *   To configure the CRYOTIMER, call the @ref CRYOTIMER_Init function.
 *   This function will configure the CRYOTIMER peripheral according to the
 *   user configuration.
 *
 * @details
 *   When using the CRYOTIMER, choose which oscillator to use
 *   as the CRYOTIMER clock. The CRYOTIMER supports 3 low-frequency clocks
 *   LFXO, LFRCO, and ULFRCO. The oscillator that is chosen must be
 *   enabled and ready before calling this @ref CRYOTIMER_Init function.
 *   See @ref CMU_OscillatorEnable for details of how to enable and wait for an
 *   oscillator to become ready. Note that ULFRCO is always ready while LFRCO
 *   @ref cmuOsc_LFRCO and LFXO @ref cmuOsc_LFXO must be enabled by the user.
 *
 * @details
 *   Note that the only oscillator which is running in EM3 is ULFRCO. Keep this
 *   in mind when choosing which oscillator to use for the CRYOTIMER.
 *
 *   This example shows how to use the CRYOTIMER to generate an interrupt
 *   at a configurable period.
 *
 * @include em_cryotimer_period.c
 *
 * @details
 *   To use the CRYOTIMER in EM4, enable EM4 wakeup in the
 *   CRYOTIMER. This can be done either in the @ref CRYOTIMER_Init_TypeDef
 *   structure when initializing the CRYOTIMER or at a later time by using
 *   @ref CRYOTIMER_EM4WakeupEnable.
 *
 *   Note that when using the CRYOTIMER to wake up from EM4, the application has
 *   the responsibility to clear the wakeup event by calling
 *   @ref CRYOTIMER_IntClear. If the you do not clear the wakeup event,
 *   the wakeup event will stay pending and will cause an immediate wakeup the
 *   next time the application attempts to enter EM4.
 *
 *   This example shows how to use the CRYOTIMER to wake up from EM4 after
 *   a configurable amount of time.
 *
 * @include em_cryotimer_em4.c
 *
 * @details
 *   All the low frequency oscillators can be used in EM4, however, the
 *   oscillator that is used must be be configured to be retained when going
 *   into EM4 by using functions in the @ref emu module.
 *   See @ref EMU_EM4Init and @ref EMU_EM4Init_TypeDef. If an oscillator is
 *   retained in EM4, users are also responsible for unlatching the retained
 *   configuration on a wakeup from EM4.
 *
 * @{
 ******************************************************************************/

/*******************************************************************************
 *********************************   ENUM   ************************************
 ******************************************************************************/

/** Prescaler selection. */
typedef enum {
  cryotimerPresc_1     = _CRYOTIMER_CTRL_PRESC_DIV1,      /**< Divide clock by 1. */
  cryotimerPresc_2     = _CRYOTIMER_CTRL_PRESC_DIV2,      /**< Divide clock by 2. */
  cryotimerPresc_4     = _CRYOTIMER_CTRL_PRESC_DIV4,      /**< Divide clock by 4. */
  cryotimerPresc_8     = _CRYOTIMER_CTRL_PRESC_DIV8,      /**< Divide clock by 8. */
  cryotimerPresc_16    = _CRYOTIMER_CTRL_PRESC_DIV16,     /**< Divide clock by 16. */
  cryotimerPresc_32    = _CRYOTIMER_CTRL_PRESC_DIV32,     /**< Divide clock by 32. */
  cryotimerPresc_64    = _CRYOTIMER_CTRL_PRESC_DIV64,     /**< Divide clock by 64. */
  cryotimerPresc_128   = _CRYOTIMER_CTRL_PRESC_DIV128,    /**< Divide clock by 128. */
} CRYOTIMER_Presc_TypeDef;

/** Low frequency oscillator selection. */
typedef enum {
  cryotimerOscLFRCO   = _CRYOTIMER_CTRL_OSCSEL_LFRCO,  /**< Select Low-frequency RC Oscillator. */
  cryotimerOscLFXO    = _CRYOTIMER_CTRL_OSCSEL_LFXO,   /**< Select Low-frequency Crystal Oscillator. */
  cryotimerOscULFRCO  = _CRYOTIMER_CTRL_OSCSEL_ULFRCO, /**< Select Ultra Low Frequency RC Oscillator. */
} CRYOTIMER_Osc_TypeDef;

/** Period selection value */
typedef enum {
  cryotimerPeriod_1     = 0,    /**< Wakeup event after every Pre-scaled clock cycle. */
  cryotimerPeriod_2     = 1,    /**< Wakeup event after 2 Pre-scaled clock cycles. */
  cryotimerPeriod_4     = 2,    /**< Wakeup event after 4 Pre-scaled clock cycles. */
  cryotimerPeriod_8     = 3,    /**< Wakeup event after 8 Pre-scaled clock cycles. */
  cryotimerPeriod_16    = 4,    /**< Wakeup event after 16 Pre-scaled clock cycles. */
  cryotimerPeriod_32    = 5,    /**< Wakeup event after 32 Pre-scaled clock cycles. */
  cryotimerPeriod_64    = 6,    /**< Wakeup event after 64 Pre-scaled clock cycles. */
  cryotimerPeriod_128   = 7,    /**< Wakeup event after 128 Pre-scaled clock cycles. */
  cryotimerPeriod_256   = 8,    /**< Wakeup event after 256 Pre-scaled clock cycles. */
  cryotimerPeriod_512   = 9,    /**< Wakeup event after 512 Pre-scaled clock cycles. */
  cryotimerPeriod_1k    = 10,   /**< Wakeup event after 1k Pre-scaled clock cycles. */
  cryotimerPeriod_2k    = 11,   /**< Wakeup event after 2k Pre-scaled clock cycles. */
  cryotimerPeriod_4k    = 12,   /**< Wakeup event after 4k Pre-scaled clock cycles. */
  cryotimerPeriod_8k    = 13,   /**< Wakeup event after 8k Pre-scaled clock cycles. */
  cryotimerPeriod_16k   = 14,   /**< Wakeup event after 16k Pre-scaled clock cycles. */
  cryotimerPeriod_32k   = 15,   /**< Wakeup event after 32k Pre-scaled clock cycles. */
  cryotimerPeriod_64k   = 16,   /**< Wakeup event after 64k Pre-scaled clock cycles. */
  cryotimerPeriod_128k  = 17,   /**< Wakeup event after 128k Pre-scaled clock cycles. */
  cryotimerPeriod_256k  = 18,   /**< Wakeup event after 256k Pre-scaled clock cycles. */
  cryotimerPeriod_512k  = 19,   /**< Wakeup event after 512k Pre-scaled clock cycles. */
  cryotimerPeriod_1m    = 20,   /**< Wakeup event after 1m Pre-scaled clock cycles. */
  cryotimerPeriod_2m    = 21,   /**< Wakeup event after 2m Pre-scaled clock cycles. */
  cryotimerPeriod_4m    = 22,   /**< Wakeup event after 4m Pre-scaled clock cycles. */
  cryotimerPeriod_8m    = 23,   /**< Wakeup event after 8m Pre-scaled clock cycles. */
  cryotimerPeriod_16m   = 24,   /**< Wakeup event after 16m Pre-scaled clock cycles. */
  cryotimerPeriod_32m   = 25,   /**< Wakeup event after 32m Pre-scaled clock cycles. */
  cryotimerPeriod_64m   = 26,   /**< Wakeup event after 64m Pre-scaled clock cycles. */
  cryotimerPeriod_128m  = 27,   /**< Wakeup event after 128m Pre-scaled clock cycles. */
  cryotimerPeriod_256m  = 28,   /**< Wakeup event after 256m Pre-scaled clock cycles. */
  cryotimerPeriod_512m  = 29,   /**< Wakeup event after 512m Pre-scaled clock cycles. */
  cryotimerPeriod_1024m = 30,   /**< Wakeup event after 1024m Pre-scaled clock cycles. */
  cryotimerPeriod_2048m = 31,   /**< Wakeup event after 2048m Pre-scaled clock cycles. */
  cryotimerPeriod_4096m = 32,   /**< Wakeup event after 4096m Pre-scaled clock cycles. */
} CRYOTIMER_Period_TypeDef;

/*******************************************************************************
 *******************************   STRUCTURES   ***********************************
 ******************************************************************************/

/** CRYOTIMER initialization structure. */
typedef struct {
  /** Enable/disable counting when initialization is complete. */
  bool                      enable;

  /** Enable/disable timer counting during debug halt. */
  bool                      debugRun;

  /** Enable/disable EM4 Wakeup. */
  bool                      em4Wakeup;

  /** Select the oscillator for the CRYOTIMER. */
  CRYOTIMER_Osc_TypeDef     osc;

  /** Prescaler. */
  CRYOTIMER_Presc_TypeDef   presc;

  /** A period between a wakeup event/interrupt. */
  CRYOTIMER_Period_TypeDef  period;
} CRYOTIMER_Init_TypeDef;

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

/** Default CRYOTIMER init structure. */
#define CRYOTIMER_INIT_DEFAULT                                                                      \
  {                                                                                                 \
    true,                  /* Start counting when the initialization is done.                    */ \
    false,                 /* Disable CRYOTIMER during debug halt.              */                  \
    false,                 /* Disable EM4 wakeup.                               */                  \
    cryotimerOscLFRCO,     /* Select Low Frequency RC Oscillator.               */                  \
    cryotimerPresc_1,      /* LF Oscillator frequency undivided.                */                  \
    cryotimerPeriod_4096m, /* Wakeup event after 4096 M pre-scaled clock cycles. */                 \
  }

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Clear the CRYOTIMER period interrupt.
 *
 * @param[in] flags
 *   CRYOTIMER interrupt sources to clear. Use CRYOTIMER_IFC_PERIOD.
 ******************************************************************************/
__STATIC_INLINE void CRYOTIMER_IntClear(uint32_t flags)
{
  CRYOTIMER->IFC = flags & _CRYOTIMER_IFC_MASK;
}

/***************************************************************************//**
 * @brief
 *   Get the CRYOTIMER interrupt flag.
 *
 * @note
 *   This function does not clear event bits.
 *
 * @return
 *   Pending CRYOTIMER interrupt sources. The only interrupt source available
 *   for the CRYOTIMER is CRYOTIMER_IF_PERIOD.
 ******************************************************************************/
__STATIC_INLINE uint32_t CRYOTIMER_IntGet(void)
{
  return CRYOTIMER->IF;
}

/***************************************************************************//**
 * @brief
 *   Get enabled and pending CRYOTIMER interrupt flags.
 *   Useful for handling more interrupt sources in the same interrupt handler.
 *
 * @note
 *    This function does not clear interrupt flags.
 *
 * @return
 *   Pending and enabled CRYOTIMER interrupt sources.
 *   The return value is the bitwise AND of
 *   - the enabled interrupt sources in CRYOTIMER_IEN and
 *   - the pending interrupt flags CRYOTIMER_IF
 ******************************************************************************/
__STATIC_INLINE uint32_t CRYOTIMER_IntGetEnabled(void)
{
  uint32_t ien;

  ien = CRYOTIMER->IEN & _CRYOTIMER_IEN_MASK;
  return CRYOTIMER->IF & ien;
}

/***************************************************************************//**
 * @brief
 *   Enable one or more CRYOTIMER interrupts.
 *
 * @param[in] flags
 *   CRYOTIMER interrupt sources to enable. Use CRYOTIMER_IEN_PERIOD.
 ******************************************************************************/
__STATIC_INLINE void CRYOTIMER_IntEnable(uint32_t flags)
{
  CRYOTIMER->IEN |= (flags & _CRYOTIMER_IEN_MASK);
}

/***************************************************************************//**
 * @brief
 *   Disable one or more CRYOTIMER interrupts.
 *
 * @param[in] flags
 *   CRYOTIMER interrupt sources to disable. Use CRYOTIMER_IEN_PERIOD.
 ******************************************************************************/
__STATIC_INLINE void CRYOTIMER_IntDisable(uint32_t flags)
{
  CRYOTIMER->IEN &= ~(flags & _CRYOTIMER_IEN_MASK);
}

/***************************************************************************//**
 * @brief
 *   Set the CRYOTIMER period interrupt flag.
 *
 * @note
 *   Writes 1 to the interrupt flag set register.
 *
 * @param[in] flags
 *   CRYOTIMER interrupt sources to set to pending. Use
 *   CRYOTIMER_IFS_PERIOD.
 ******************************************************************************/
__STATIC_INLINE void CRYOTIMER_IntSet(uint32_t flags)
{
  CRYOTIMER->IFS = flags & _CRYOTIMER_IFS_MASK;
}

/***************************************************************************//**
 * @brief
 *   Set the CRYOTIMER period select.
 *
 * @note
 *   Sets the duration between the interrupts/wakeup events based on
 *   the pre-scaled clock.
 *
 * @param[in] period
 *   2^period is the number of clock cycles before a wakeup event or
 *   interrupt is triggered. The CRYOTIMER_Periodsel_TypeDef enumeration can
 *   be used a convenience type when calling this function.
 ******************************************************************************/
__STATIC_INLINE void CRYOTIMER_PeriodSet(uint32_t period)
{
  CRYOTIMER->PERIODSEL = period & _CRYOTIMER_PERIODSEL_MASK;
}

/***************************************************************************//**
 * @brief
 *   Get the CRYOTIMER period select value.
 *
 * @note
 *   Gets the duration between the interrupts/wakeup events in the
 *   CRYOTIMER.
 *
 * @return
 *   Duration between the interrupts/wakeup events. Returns the value
 *   of the PERIODSEL register. The number of clock cycles can be calculated
 *   as the 2^n where n is the return value of this function.
 ******************************************************************************/
__STATIC_INLINE uint32_t CRYOTIMER_PeriodGet(void)
{
  return CRYOTIMER->PERIODSEL;
}

/***************************************************************************//**
 * @brief
 *   Get the CRYOTIMER counter value.
 *
 * @return
 *   Returns the current CRYOTIMER counter value.
 ******************************************************************************/
__STATIC_INLINE uint32_t CRYOTIMER_CounterGet(void)
{
  return CRYOTIMER->CNT;
}

/***************************************************************************//**
 * @brief
 *   Enable/disable EM4 wakeup capability.
 *
 * @param[in] enable
 *   True to enable EM4 wakeup, false to disable.
 ******************************************************************************/
__STATIC_INLINE void CRYOTIMER_EM4WakeupEnable(bool enable)
{
  BUS_RegBitWrite((&CRYOTIMER->EM4WUEN),
                  _CRYOTIMER_EM4WUEN_EM4WU_SHIFT,
                  (uint32_t)enable);
}

/***************************************************************************//**
 * @brief
 *   Enable/disable the CRYOTIMER.
 *
 * @param[in] enable
 *   True to enable the CRYOTIMER, false to disable.
 ******************************************************************************/
__STATIC_INLINE void CRYOTIMER_Enable(bool enable)
{
  BUS_RegBitWrite((&CRYOTIMER->CTRL),
                  _CRYOTIMER_CTRL_EN_SHIFT,
                  (uint32_t)enable);
}

/***************************************************************************//**
 * @brief
 *   Initialize the CRYOTIMER.
 *
 * @details
 *   Use this function to initialize the CRYOTIMER.
 *   Select a prescaler setting and select a low-frequency oscillator.
 *   See the configuration structure @ref CRYOTIMER_Init_TypeDef for more
 *   details.
 *
 * @param[in] init
 *   A pointer to the initialization structure.
 ******************************************************************************/
void CRYOTIMER_Init(const CRYOTIMER_Init_TypeDef *init);

#ifdef __cplusplus
}
#endif

/** @} (end addtogroup cryotimer) */

#endif /* defined(CRYOTIMER_PRESENT) && (CRYOTIMER_COUNT == 1) */
#endif /* EM_CRYOTIMER_H */
