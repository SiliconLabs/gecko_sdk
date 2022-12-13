/***************************************************************************//**
 * @file
 * @brief DCDC Coulomb Counter (DCDC_COULOMB_COUNTER) peripheral API
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef PERIPHERAL_DCDC_COULOMB_COUNTER_H
#define PERIPHERAL_DCDC_COULOMB_COUNTER_H

#include "em_device.h"
#include "em_cmu.h"
#include "em_emu.h"

#if defined(DCDC_COUNT) && (DCDC_COUNT > 0) && defined(DCDC_CCCTRL_CCEN)

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup dcdccoulombcounter
 * @{
 ******************************************************************************/

/*******************************************************************************
 *********************************   ENUM   ************************************
 ******************************************************************************/

/** DCDC_COULOMB_COUNTER supported energy mode. */
typedef enum {
  SL_DCDC_COULOMB_COUNTER_EM0 = 0, /**< EM0/1 energy mode. */
  SL_DCDC_COULOMB_COUNTER_EM2 = 1, /**< EM2/3 energy mode. */
} sl_dcdc_coulomb_counter_emode_t;

/** DCDC_COULOMB_COUNTER Calibration Load Current Level setting. */
typedef enum {
  SL_DCDC_COULOMB_COUNTER_CAL_LOAD0 = _DCDC_CCCALCTRL_CCLVL_LOAD0, /**< Nominal Load 0.25mA. */
  SL_DCDC_COULOMB_COUNTER_CAL_LOAD1 = _DCDC_CCCALCTRL_CCLVL_LOAD1, /**< Nominal Load 0.50mA. */
  SL_DCDC_COULOMB_COUNTER_CAL_LOAD2 = _DCDC_CCCALCTRL_CCLVL_LOAD2, /**< Nominal Load 1.00mA. */
  SL_DCDC_COULOMB_COUNTER_CAL_LOAD3 = _DCDC_CCCALCTRL_CCLVL_LOAD3, /**< Nominal Load 1.50mA. */
  SL_DCDC_COULOMB_COUNTER_CAL_LOAD4 = _DCDC_CCCALCTRL_CCLVL_LOAD4, /**< Nominal Load 2.00mA. */
  SL_DCDC_COULOMB_COUNTER_CAL_LOAD5 = _DCDC_CCCALCTRL_CCLVL_LOAD5, /**< Nominal Load 4.00mA. */
  SL_DCDC_COULOMB_COUNTER_CAL_LOAD6 = _DCDC_CCCALCTRL_CCLVL_LOAD6, /**< Nominal Load 6.00mA. */
  SL_DCDC_COULOMB_COUNTER_CAL_LOAD7 = _DCDC_CCCALCTRL_CCLVL_LOAD7, /**< Nominal Load 8.00mA. */
} sl_dcdc_coulomb_counter_calibration_load_level_t;

/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/// DCDC_COULOMB_COUNTER configuration structure.
typedef struct {
  uint16_t counter_threshold_em0;      ///< Coulomb Counter Threshold in EM0.
  uint16_t counter_threshold_em2;      ///< Coulomb Counter Threshold in EM2.
} sl_dcdc_coulomb_counter_config_t;

/// DCDC_COULOMB_COUNTER calibration configuration structure.
typedef struct {
  CMU_Select_TypeDef reference_clk;                                 ///< Coulomb Counter Calibration Reference Clock.
  int8_t cal_count;                                                 ///< Coulomb Counter Calibration Reference Count.
  sl_dcdc_coulomb_counter_emode_t cal_emode;                        ///< Coulomb Counter Calibration Energy Mode.
  sl_dcdc_coulomb_counter_calibration_load_level_t cal_load_level;  ///< Coulomb Counter Calibration Power Load.
} sl_dcdc_coulomb_counter_calibration_config_t;

/// Suggested default values for DCDC_COULOMB_COUNTER configuration structure.
#define DCDC_COULOMB_COUNTER_CONFIG_DEFAULT                              \
  {                                                                      \
    0x8000,                         /* Coulomb Counter EM0 Threshold. */ \
    0x8000,                         /* Coulomb Counter EM2 Threshold. */ \
  }

/// Suggested default values for DCDC_COULOMB_COUNTER calibration configuration structure.
#define DCDC_COULOMB_COUNTER_CALIBRATION_CONFIG_DEFAULT                                          \
  {                                                                                              \
    cmuSelect_HFXO,                         /* Coulomb Counter Calibration Reference Clock.   */ \
    8,                                      /* Coulomb Counter Calibration Reference Count.   */ \
    SL_DCDC_COULOMB_COUNTER_EM0,            /* Coulomb Counter Calibration DC-DC energy mode. */ \
    SL_DCDC_COULOMB_COUNTER_CAL_LOAD3,      /* Coulomb Counter Calibration Load.              */ \
  }

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

/***************************************************************************//**
 * Initializes DCDC_COULOMB_COUNTER module.
 *
 * @param[in] p_config  A pointer to the DCDC_COULOMB_COUNTER initialization
 *                      structure variable.
 ******************************************************************************/
void sl_dcdc_coulomb_counter_init(const sl_dcdc_coulomb_counter_config_t *p_config);

/***************************************************************************//**
 * Enables DCDC_COULOMB_COUNTER module.
 ******************************************************************************/
__STATIC_INLINE void sl_dcdc_coulomb_counter_enable(void)
{
  EMU_DCDCSync(_DCDC_SYNCBUSY_MASK);
  DCDC->CCCTRL_SET = DCDC_CCCTRL_CCEN;
}

/***************************************************************************//**
 * Disables DCDC_COULOMB_COUNTER module.
 ******************************************************************************/
void sl_dcdc_coulomb_counter_disable(void);

/***************************************************************************//**
 * Waits for the DCDC_COULOMB_COUNTER to complete START command.
 ******************************************************************************/
__STATIC_INLINE void sl_dcdc_coulomb_counter_wait_start(void)
{
  EMU_DCDCSync(_DCDC_SYNCBUSY_MASK);
  while ((DCDC->CCSTATUS & _DCDC_CCSTATUS_CCRUNNING_MASK) == 0U) {
    /* Wait for counters to start. */
  }
}

/***************************************************************************//**
 * Waits for the DCDC_COULOMB_COUNTER to complete STOP command.
 ******************************************************************************/
__STATIC_INLINE void sl_dcdc_coulomb_counter_wait_stop(void)
{
  EMU_DCDCSync(_DCDC_SYNCBUSY_MASK);
  while ((DCDC->CCSTATUS & _DCDC_CCSTATUS_CCRUNNING_MASK) == DCDC_CCSTATUS_CCRUNNING) {
    /* Wait for counters to stop. */
  }
}

/***************************************************************************//**
 * Waits for the DCDC_COULOMB_COUNTER to complete CLR command.
 ******************************************************************************/
__STATIC_INLINE void sl_dcdc_coulomb_counter_wait_clear_counters(void)
{
  EMU_DCDCSync(_DCDC_SYNCBUSY_MASK);
  while ((DCDC->CCSTATUS & _DCDC_CCSTATUS_CLRBSY_MASK) == DCDC_CCSTATUS_CLRBSY) {
    /* Wait for counters to clear. */
  }
}

/***************************************************************************//**
 * Starts DCDC_COULOMB_COUNTER operation.
 *
 * @note This function will send a start command to the DCDC_COULOMB_COUNTER peripheral.
 *       The sl_dcdc_coulomb_counter_wait_start() function can be used to wait for the start
 *       command to be executed.
 *
 * @note This function requires the DCDC_COULOMB_COUNTER to be enabled.
 ******************************************************************************/
__STATIC_INLINE void sl_dcdc_coulomb_counter_start(void)
{
  EMU_DCDCSync(_DCDC_SYNCBUSY_MASK);
  DCDC->CCCMD_SET = DCDC_CCCMD_START;
}

/***************************************************************************//**
 * Stops the DCDC_COULOMB_COUNTER operation.
 *
 * @note This function will send a stop command to the DCDC_COULOMB_COUNTER peripheral.
 *       The sl_dcdc_coulomb_counter_wait_stop() function can be used to wait for the stop
 *       command to be executed.
 *
 * @note This function requires the DCDC_COULOMB_COUNTER to be enabled.
 ******************************************************************************/
__STATIC_INLINE void sl_dcdc_coulomb_counter_stop(void)
{
  EMU_DCDCSync(_DCDC_SYNCBUSY_MASK);
  DCDC->CCCMD_SET = DCDC_CCCMD_STOP;
}

/***************************************************************************//**
 * Clears the DCDC_COULOMB_COUNTER counters.
 *
 * @note This function will send a clear command to the DCDC_COULOMB_COUNTER peripheral.
 *       The sl_dcdc_coulomb_counter_wait_clear_counters() function can be used
 *       to wait for the clear command to be executed.
 *
 * @note This function requires the DCDC_COULOMB_COUNTER to be enabled.
 ******************************************************************************/
__STATIC_INLINE void sl_dcdc_coulomb_counter_clear_counters(void)
{
  EMU_DCDCSync(_DCDC_SYNCBUSY_MASK);
  DCDC->CCCMD_SET = DCDC_CCCMD_CLR;
}

/***************************************************************************//**
 * Gets the DCDC_COULOMB_COUNTER count for the selected energy mode.
 *
 * @param[in] emode  The energy mode requested will select the appropriate counter.
 *
 * @return Coulomb Counter Count Value.
 ******************************************************************************/
uint32_t sl_dcdc_coulomb_counter_get_count(sl_dcdc_coulomb_counter_emode_t emode);

/***************************************************************************//**
 * Gets DCDC_COULOMB_COUNTER STATUS register value.
 *
 * @return  Current STATUS register value.
 ******************************************************************************/
__STATIC_INLINE uint32_t sl_dcdc_coulomb_counter_get_status(void)
{
  return DCDC->CCSTATUS;
}

/***************************************************************************//**
 * Enables one or more DCDC_COULOMB_COUNTER interrupts.
 *
 * @note  Depending on the use, a pending interrupt may already be set prior to
 *        enabling the interrupt. To ignore a pending interrupt, consider using
 *        sl_dcdc_coulomb_counter_clear_interrupts() prior to enabling the interrupt.
 *
 * @param[in] flags   DCDC_COULOMB_COUNTER interrupt sources to enable.
 *                    Use a set of interrupt flags OR-ed together to set
 *                    multiple interrupt sources.
 ******************************************************************************/
__STATIC_INLINE void sl_dcdc_coulomb_counter_enable_interrupts(uint32_t flags)
{
  DCDC->CCIEN_SET = flags;
}

/***************************************************************************//**
 * Disables one or more DCDC_COULOMB_COUNTER interrupts.
 *
 * @param[in] flags   DCDC_COULOMB_COUNTER interrupt sources to disable.
 *                    Use a set of interrupt flags OR-ed together to disable
 *                    multiple interrupt sources.
 ******************************************************************************/
__STATIC_INLINE void sl_dcdc_coulomb_counter_disable_interrupts(uint32_t flags)
{
  DCDC->CCIEN_CLR = flags;
}

/***************************************************************************//**
 * Clears one or more pending DCDC_COULOMB_COUNTER interrupts.
 *
 * @param[in] flags   DCDC_COULOMB_COUNTER interrupt sources to clear.
 *                    Use a set of interrupt flags OR-ed together to clear
 *                    multiple interrupt sources.
 ******************************************************************************/
__STATIC_INLINE void sl_dcdc_coulomb_counter_clear_interrupts(uint32_t flags)
{
  DCDC->CCIF_CLR = flags;
}

/***************************************************************************//**
 * Gets pending DCDC_COULOMB_COUNTER interrupt flags.
 *
 * @note  Event bits are not cleared by using this function.
 *
 * @return  Pending DCDC_COULOMB_COUNTER interrupt sources.
 *          Returns a set of interrupt flags OR-ed together for multiple
 *          interrupt sources.
 ******************************************************************************/
__STATIC_INLINE uint32_t sl_dcdc_coulomb_counter_get_interrupts(void)
{
  return DCDC->CCIF;
}

/***************************************************************************//**
 * Gets enabled and pending DCDC_COULOMB_COUNTER interrupt flags.
 * Useful for handling more interrupt sources in the same interrupt handler.
 *
 * @note  Interrupt flags are not cleared by using this function.
 *
 * @return  Pending and enabled DCDC_COULOMB_COUNTER interrupt sources.
 *          The return value is the bitwise AND of
 *          - the enabled interrupt sources in DCDC_COULOMB_COUNTER_IEN and
 *          - the pending interrupt flags DCDC_COULOMB_COUNTER_IF.
 ******************************************************************************/
__STATIC_INLINE uint32_t sl_dcdc_coulomb_counter_get_enabled_interrupts(void)
{
  uint32_t ccif = DCDC->CCIF & _DCDC_CCIF_MASK;
  uint32_t ccien = DCDC->CCIEN & _DCDC_CCIEN_MASK;

  return ccif & ccien;
}

/***************************************************************************//**
 * Sets one or more pending DCDC_COULOMB_COUNTER interrupts from Software.
 *
 * @param[in] flags   DCDC_COULOMB_COUNTER interrupt sources to set to pending.
 *                    Use a set of interrupt flags OR-ed together to set
 *                    multiple interrupt sources.
 ******************************************************************************/
__STATIC_INLINE void sl_dcdc_coulomb_counter_set_interrupts(uint32_t flags)
{
  DCDC->CCIF_SET = flags;
}

/***************************************************************************//**
 * Initializes the calibration of the DCDC Coulomb Counter.
 *
 * @param[in] config  DCDC_COULOMB_COUNTER calibration configuration structure.
 *
 * @note The charge per pulse is measured using known on-chip calibration
 *       loads, a PRS channel, and the CMU RC oscillator calibration circuitry.
 ******************************************************************************/
void sl_dcdc_coulomb_counter_cal_init(sl_dcdc_coulomb_counter_calibration_config_t config);

/***************************************************************************//**
 * Starts DCDC_COULOMB_COUNTER calibration sequence.
 ******************************************************************************/
void sl_dcdc_coulomb_counter_cal_start(void);

/***************************************************************************//**
 * Stops DCDC_COULOMB_COUNTER calibration sequence.
 *
 * @note The Calibration Load will be disabled.
 ******************************************************************************/
void sl_dcdc_coulomb_counter_cal_stop(void);

/***************************************************************************//**
 * Enables the Calibration Load.
 ******************************************************************************/
void sl_dcdc_coulomb_counter_enable_cal_load(void);

/***************************************************************************//**
 * Disables the Calibration Load.
 ******************************************************************************/
void sl_dcdc_coulomb_counter_disable_cal_load(void);

/***************************************************************************//**
 * Sets the Calibration Load level.
 *
 * @param[in] emode       The energy mode requested will adjust the compensation circuit.
 * @param[in] load_level  The load level to adjust the load current.
 ******************************************************************************/
void sl_dcdc_coulomb_counter_set_cal_load_level(sl_dcdc_coulomb_counter_emode_t emode,
                                                sl_dcdc_coulomb_counter_calibration_load_level_t load_level);

/***************************************************************************//**
 * Gets the calibration load current from the stored value
 * in DEVINFO as measured during production testing.
 *
 * @param[in] load_level  The load level requested.
 *
 * @return The calibration load current.
 *
 * @note The returned value can be converted into uA by dividing by 5.
 *
 * @note Each calibration load setting is a 16-bit value
 *       with each LSB representing 200 nA.
 ******************************************************************************/
uint16_t sl_dcdc_coulomb_counter_get_cal_load_current(sl_dcdc_coulomb_counter_calibration_load_level_t load_level);

/***************************************************************************//**
 * Gets the frequency (in Hz) of the CMU Calibration Up-Counter source.
 *
 * @return The frequency (in Hz) of the currently selected CMU Up-Counter clock
 *         source.
 ******************************************************************************/
uint32_t sl_dcdc_coulomb_counter_get_cal_reference_freq(void);

/***************************************************************************//**
 * Sets the calibration Halt Flag.
 ******************************************************************************/
__STATIC_INLINE void sl_dcdc_coulomb_counter_set_calhalt(void)
{
  DCDC->CCCALCTRL_SET = DCDC_CCCALCTRL_CCCALHALT;
}

/***************************************************************************//**
 * Gets the calibration Halt Flag.
 *
 * @return true if Halt Flag is set.
 ******************************************************************************/
__STATIC_INLINE bool sl_dcdc_coulomb_counter_calhalt_is_set(void)
{
  return (DCDC->CCCALCTRL & _DCDC_CCCALCTRL_CCCALHALT_MASK) == DCDC_CCCALCTRL_CCCALHALT;
}

/** @} (end addtogroup dcdccoulombcounter) */

#ifdef __cplusplus
}
#endif

#endif /* defined(DCDC_COULOMB_COUNTER_COUNT) && (DCDC_COULOMB_COUNTER_COUNT > 0) && defined(DCDC_CCCTRL_CCEN) */
#endif /* PERIPHERAL_DCDC_COULOMB_COUNTER_H */
