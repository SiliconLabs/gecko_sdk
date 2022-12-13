/***************************************************************************//**
 * @file
 * @brief Clock Management Unit Private API definition.
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

#ifndef SLI_EM_CMU_H
#define SLI_EM_CMU_H

#ifdef __cplusplus
extern "C" {
#endif

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
#if defined(_SILICON_LABS_32B_SERIES_2)

/***************************************************************************//**
 * @brief Performs pre-clock-selection operations to initialize the system clock.
 *
 * @note FOR INTERNAL USE ONLY.
 *
 * @note This function is needed for macro expansion of CMU_CLOCK_SELECT_SET when
 *       the clock is SYSCLK.
 ******************************************************************************/
void sli_em_cmu_SYSCLKInitPreClockSelect(void);

/***************************************************************************//**
 * @brief Performs post-clock-selection operations to initialize the system clock.
 *
 * @note FOR INTERNAL USE ONLY.
 *
 * @note This function is needed for macro expansion of CMU_CLOCK_SELECT_SET when
 *       the clock is SYSCLK.
 ******************************************************************************/
void sli_em_cmu_SYSCLKInitPostClockSelect(void);

/***************************************************************************//**
 * @brief Sets the HFXO0 FORCEEN bit.
 *
 * @note FOR INTERNAL USE ONLY.
 *
 * @note This function is needed for macro expansion of CMU_CLOCK_SELECT_SET when
 *       the clock is SYSCLK and the selected clock source is HFXO.
 ******************************************************************************/
void sli_em_cmu_HFXOSetForceEnable(void);

/***************************************************************************//**
 * @brief This function will set the SYSCFG->CFGSYSTIC<SYSTICEXTCLKEN> bit.
 *
 * @note FOR INTERNAL USE ONLY.
 *
 * @note This function is needed for macro expansion of CMU_CLOCK_SELECT_SET when
 *       the clock is SYSTICK.
 ******************************************************************************/
void sli_em_cmu_SYSTICEXTCLKENSet(void);

/***************************************************************************//**
 * @brief This function will clear the SYSCFG->CFGSYSTIC<SYSTICEXTCLKEN> bit.
 *
 * @note FOR INTERNAL USE ONLY.
 *
 * @note This function is needed for macro expansion of CMU_CLOCK_SELECT_SET when
 *       the clock is SYSTICK.
 ******************************************************************************/
void sli_em_cmu_SYSTICEXTCLKENClear(void);

#define CMU_SYSCLK_SELECT_HFRCODPLL                                    \
  do {                                                                 \
    sli_em_cmu_SYSCLKInitPreClockSelect();                             \
    CMU->SYSCLKCTRL = (CMU->SYSCLKCTRL & ~_CMU_SYSCLKCTRL_CLKSEL_MASK) \
                      | CMU_SYSCLKCTRL_CLKSEL_HFRCODPLL;               \
    sli_em_cmu_SYSCLKInitPostClockSelect();                            \
  } while (0)

#define CMU_SYSCLK_SELECT_HFXO                                         \
  do {                                                                 \
    sli_em_cmu_HFXOSetForceEnable();                                   \
    sli_em_cmu_SYSCLKInitPreClockSelect();                             \
    CMU->SYSCLKCTRL = (CMU->SYSCLKCTRL & ~_CMU_SYSCLKCTRL_CLKSEL_MASK) \
                      | CMU_SYSCLKCTRL_CLKSEL_HFXO;                    \
    sli_em_cmu_SYSCLKInitPostClockSelect();                            \
    if ((HFXO0->CTRL & HFXO_CTRL_DISONDEMAND) == 0) {                  \
      HFXO0->CTRL_CLR = HFXO_CTRL_FORCEEN;                             \
    }                                                                  \
  } while (0)

#define CMU_SYSCLK_SELECT_CLKIN0                                       \
  do {                                                                 \
    sli_em_cmu_SYSCLKInitPreClockSelect();                             \
    CMU->SYSCLKCTRL = (CMU->SYSCLKCTRL & ~_CMU_SYSCLKCTRL_CLKSEL_MASK) \
                      | CMU_SYSCLKCTRL_CLKSEL_CLKIN0;                  \
    sli_em_cmu_SYSCLKInitPostClockSelect();                            \
  } while (0)

#define CMU_SYSCLK_SELECT_FSRCO                                        \
  do {                                                                 \
    sli_em_cmu_SYSCLKInitPreClockSelect();                             \
    CMU->SYSCLKCTRL = (CMU->SYSCLKCTRL & ~_CMU_SYSCLKCTRL_CLKSEL_MASK) \
                      | CMU_SYSCLKCTRL_CLKSEL_FSRCO;                   \
    sli_em_cmu_SYSCLKInitPostClockSelect();                            \
  } while (0)

#if defined(RFFPLL_PRESENT)

#define CMU_SYSCLK_SELECT_RFFPLLSYS                                    \
  do {                                                                 \
    sli_em_cmu_SYSCLKInitPreClockSelect();                             \
    CMU->SYSCLKCTRL = (CMU->SYSCLKCTRL & ~_CMU_SYSCLKCTRL_CLKSEL_MASK) \
                      | CMU_SYSCLKCTRL_CLKSEL_RFFPLL0SYS;              \
    sli_em_cmu_SYSCLKInitPostClockSelect();                            \
  } while (0)

#endif /* RFFPLL_PRESENT */

#if defined(IADC_PRESENT)
#define CMU_IADCCLK_SELECT_EM01GRPACLK                                    \
  do {                                                                    \
    CMU->IADCCLKCTRL = (CMU->IADCCLKCTRL & ~_CMU_IADCCLKCTRL_CLKSEL_MASK) \
                       | CMU_IADCCLKCTRL_CLKSEL_EM01GRPACLK;              \
  } while (0)

#define CMU_IADC0_SELECT_EM01GRPACLK CMU_IADCCLK_SELECT_EM01GRPACLK

#if defined(HFRCOEM23_PRESENT)
#define CMU_IADCCLK_SELECT_HFRCOEM23                                      \
  do {                                                                    \
    CMU->IADCCLKCTRL = (CMU->IADCCLKCTRL & ~_CMU_IADCCLKCTRL_CLKSEL_MASK) \
                       | CMU_IADCCLKCTRL_CLKSEL_HFRCOEM23;                \
  } while (0)

#define CMU_IADC0_SELECT_HFRCOEM23 CMU_IADCCLK_SELECT_HFRCOEM23
#endif /* HFRCOEM23_PRESENT */

#define CMU_IADCCLK_SELECT_FSRCO                                          \
  do {                                                                    \
    CMU->IADCCLKCTRL = (CMU->IADCCLKCTRL & ~_CMU_IADCCLKCTRL_CLKSEL_MASK) \
                       | CMU_IADCCLKCTRL_CLKSEL_FSRCO;                    \
  } while (0)

#define CMU_IADC0_SELECT_FSRCO CMU_IADCCLK_SELECT_FSRCO
#endif /* IADC_PRESENT */

#define CMU_EM01GRPACLK_SELECT_HFRCODPLL                                              \
  do {                                                                                \
    CMU->EM01GRPACLKCTRL = (CMU->EM01GRPACLKCTRL & ~_CMU_EM01GRPACLKCTRL_CLKSEL_MASK) \
                           | CMU_EM01GRPACLKCTRL_CLKSEL_HFRCODPLL;                    \
  } while (0)

#define CMU_TIMER0_SELECT_HFRCODPLL CMU_EM01GRPACLK_SELECT_HFRCODPLL
#define CMU_TIMER1_SELECT_HFRCODPLL CMU_EM01GRPACLK_SELECT_HFRCODPLL
#define CMU_TIMER2_SELECT_HFRCODPLL CMU_EM01GRPACLK_SELECT_HFRCODPLL
#define CMU_TIMER3_SELECT_HFRCODPLL CMU_EM01GRPACLK_SELECT_HFRCODPLL
#if TIMER_COUNT > 4
#define CMU_TIMER4_SELECT_HFRCODPLL CMU_EM01GRPACLK_SELECT_HFRCODPLL
#endif /* TIMER_COUNT > 4 */
#if TIMER_COUNT > 7
#define CMU_TIMER5_SELECT_HFRCODPLL CMU_EM01GRPACLK_SELECT_HFRCODPLL
#define CMU_TIMER6_SELECT_HFRCODPLL CMU_EM01GRPACLK_SELECT_HFRCODPLL
#define CMU_TIMER7_SELECT_HFRCODPLL CMU_EM01GRPACLK_SELECT_HFRCODPLL
#endif /* TIMER_COUNT > 7 */
#if defined(KEYSCAN_PRESENT)
#define CMU_KEYSCAN_SELECT_HFRCODPLL CMU_EM01GRPACLK_SELECT_HFRCODPLL
#endif /* KEYSCAN_PRESENT*/

#define CMU_EM01GRPACLK_SELECT_HFXO                                                   \
  do {                                                                                \
    CMU->EM01GRPACLKCTRL = (CMU->EM01GRPACLKCTRL & ~_CMU_EM01GRPACLKCTRL_CLKSEL_MASK) \
                           | CMU_EM01GRPACLKCTRL_CLKSEL_HFXO;                         \
  } while (0)

#define CMU_TIMER0_SELECT_HFXO CMU_EM01GRPACLK_SELECT_HFXO
#define CMU_TIMER1_SELECT_HFXO CMU_EM01GRPACLK_SELECT_HFXO
#define CMU_TIMER2_SELECT_HFXO CMU_EM01GRPACLK_SELECT_HFXO
#define CMU_TIMER3_SELECT_HFXO CMU_EM01GRPACLK_SELECT_HFXO
#if TIMER_COUNT > 4
#define CMU_TIMER4_SELECT_HFXO CMU_EM01GRPACLK_SELECT_HFXO
#endif /* TIMER_COUNT > 4 */
#if TIMER_COUNT > 7
#define CMU_TIMER5_SELECT_HFXO CMU_EM01GRPACLK_SELECT_HFXO
#define CMU_TIMER6_SELECT_HFXO CMU_EM01GRPACLK_SELECT_HFXO
#define CMU_TIMER7_SELECT_HFXO CMU_EM01GRPACLK_SELECT_HFXO
#endif /* TIMER_COUNT > 7 */
#if defined(KEYSCAN_PRESENT)
#define CMU_KEYSCAN_SELECT_HFXO CMU_EM01GRPACLK_SELECT_HFXO
#endif /* KEYSCAN_PRESENT*/

#if defined(HFRCOEM23_PRESENT)
#define CMU_EM01GRPACLK_SELECT_HFRCOEM23                                              \
  do {                                                                                \
    CMU->EM01GRPACLKCTRL = (CMU->EM01GRPACLKCTRL & ~_CMU_EM01GRPACLKCTRL_CLKSEL_MASK) \
                           | CMU_EM01GRPACLKCTRL_CLKSEL_HFRCOEM23;                    \
  } while (0)

#define CMU_TIMER0_SELECT_HFRCOEM23 CMU_EM01GRPACLK_SELECT_HFRCOEM23
#define CMU_TIMER1_SELECT_HFRCOEM23 CMU_EM01GRPACLK_SELECT_HFRCOEM23
#define CMU_TIMER2_SELECT_HFRCOEM23 CMU_EM01GRPACLK_SELECT_HFRCOEM23
#define CMU_TIMER3_SELECT_HFRCOEM23 CMU_EM01GRPACLK_SELECT_HFRCOEM23
#if TIMER_COUNT > 4
#define CMU_TIMER4_SELECT_HFRCOEM23 CMU_EM01GRPACLK_SELECT_HFRCOEM23
#endif /* TIMER_COUNT > 4 */
#if TIMER_COUNT > 7
#define CMU_TIMER5_SELECT_HFRCOEM23 CMU_EM01GRPACLK_SELECT_HFRCOEM23
#define CMU_TIMER6_SELECT_HFRCOEM23 CMU_EM01GRPACLK_SELECT_HFRCOEM23
#define CMU_TIMER7_SELECT_HFRCOEM23 CMU_EM01GRPACLK_SELECT_HFRCOEM23
#endif /* TIMER_COUNT > 7 */
#if defined(KEYSCAN_PRESENT)
#define CMU_KEYSCAN_SELECT_HFRCOEM23 CMU_EM01GRPACLK_SELECT_HFRCOEM23
#endif /* KEYSCAN_PRESENT*/
#endif /* HFRCOEM23_PRESENT */

#define CMU_EM01GRPACLK_SELECT_FSRCO                                                  \
  do {                                                                                \
    CMU->EM01GRPACLKCTRL = (CMU->EM01GRPACLKCTRL & ~_CMU_EM01GRPACLKCTRL_CLKSEL_MASK) \
                           | CMU_EM01GRPACLKCTRL_CLKSEL_FSRCO;                        \
  } while (0)

#define CMU_TIMER0_SELECT_FSRCO CMU_EM01GRPACLK_SELECT_FSRCO
#define CMU_TIMER1_SELECT_FSRCO CMU_EM01GRPACLK_SELECT_FSRCO
#define CMU_TIMER2_SELECT_FSRCO CMU_EM01GRPACLK_SELECT_FSRCO
#define CMU_TIMER3_SELECT_FSRCO CMU_EM01GRPACLK_SELECT_FSRCO
#if TIMER_COUNT > 4
#define CMU_TIMER4_SELECT_FSRCO CMU_EM01GRPACLK_SELECT_FSRCO
#endif /* TIMER_COUNT > 4 */
#if TIMER_COUNT > 7
#define CMU_TIMER5_SELECT_FSRCO CMU_EM01GRPACLK_SELECT_FSRCO
#define CMU_TIMER6_SELECT_FSRCO CMU_EM01GRPACLK_SELECT_FSRCO
#define CMU_TIMER7_SELECT_FSRCO CMU_EM01GRPACLK_SELECT_FSRCO
#endif /* TIMER_COUNT > 7 */
#if defined(KEYSCAN_PRESENT)
#define CMU_KEYSCAN_SELECT_FSRCO CMU_EM01GRPACLK_SELECT_FSRCO
#endif /* KEYSCAN_PRESENT*/

#if defined(CMU_EM01GRPACLKCTRL_CLKSEL_HFRCODPLLRT)
#define CMU_EM01GRPACLK_SELECT_HFRCODPLLRT                                            \
  do {                                                                                \
    CMU->EM01GRPACLKCTRL = (CMU->EM01GRPACLKCTRL & ~_CMU_EM01GRPACLKCTRL_CLKSEL_MASK) \
                           | CMU_EM01GRPACLKCTRL_CLKSEL_HFRCODPLLRT;                  \
  } while (0)

#define CMU_TIMER0_SELECT_HFRCODPLLRT CMU_EM01GRPACLK_SELECT_HFRCODPLLRT
#define CMU_TIMER1_SELECT_HFRCODPLLRT CMU_EM01GRPACLK_SELECT_HFRCODPLLRT
#define CMU_TIMER2_SELECT_HFRCODPLLRT CMU_EM01GRPACLK_SELECT_HFRCODPLLRT
#define CMU_TIMER3_SELECT_HFRCODPLLRT CMU_EM01GRPACLK_SELECT_HFRCODPLLRT
#if TIMER_COUNT > 4
#define CMU_TIMER4_SELECT_HFRCODPLLRT CMU_EM01GRPACLK_SELECT_HFRCODPLLRT
#endif /* TIMER_COUNT > 4 */
#if TIMER_COUNT > 7
#define CMU_TIMER5_SELECT_HFRCODPLLRT CMU_EM01GRPACLK_SELECT_HFRCODPLLRT
#define CMU_TIMER6_SELECT_HFRCODPLLRT CMU_EM01GRPACLK_SELECT_HFRCODPLLRT
#define CMU_TIMER7_SELECT_HFRCODPLLRT CMU_EM01GRPACLK_SELECT_HFRCODPLLRT
#endif /* TIMER_COUNT > 7 */
#if defined(KEYSCAN_PRESENT)
#define CMU_KEYSCAN_SELECT_HFRCODPLLRT CMU_EM01GRPACLK_SELECT_HFRCODPLLRT
#endif /* KEYSCAN_PRESENT*/
#endif /* CMU_EM01GRPACLKCTRL_CLKSEL_HFRCODPLLRT */

#if defined(CMU_EM01GRPACLKCTRL_CLKSEL_HFXORT)
#define CMU_EM01GRPACLK_SELECT_HFXORT                                                 \
  do {                                                                                \
    CMU->EM01GRPACLKCTRL = (CMU->EM01GRPACLKCTRL & ~_CMU_EM01GRPACLKCTRL_CLKSEL_MASK) \
                           | CMU_EM01GRPACLKCTRL_CLKSEL_HFXORT;                       \
  } while (0)

#define CMU_TIMER0_SELECT_HFXORT CMU_EM01GRPACLK_SELECT_HFXORT
#define CMU_TIMER1_SELECT_HFXORT CMU_EM01GRPACLK_SELECT_HFXORT
#define CMU_TIMER2_SELECT_HFXORT CMU_EM01GRPACLK_SELECT_HFXORT
#define CMU_TIMER3_SELECT_HFXORT CMU_EM01GRPACLK_SELECT_HFXORT
#if TIMER_COUNT > 4
#define CMU_TIMER4_SELECT_HFXORT CMU_EM01GRPACLK_SELECT_HFXORT
#endif /* TIMER_COUNT > 4 */
#if TIMER_COUNT > 7
#define CMU_TIMER5_SELECT_HFXORT CMU_EM01GRPACLK_SELECT_HFXORT
#define CMU_TIMER6_SELECT_HFXORT CMU_EM01GRPACLK_SELECT_HFXORT
#define CMU_TIMER7_SELECT_HFXORT CMU_EM01GRPACLK_SELECT_HFXORT
#endif /* TIMER_COUNT > 7 */
#if defined(KEYSCAN_PRESENT)
#define CMU_KEYSCAN_SELECT_HFXORT CMU_EM01GRPACLK_SELECT_HFXORT
#endif /* KEYSCAN_PRESENT*/
#endif /* CMU_EM01GRPACLKCTRL_CLKSEL_HFXORT */

#define CMU_SYSTICK_SELECT_EM23GRPACLK                             \
  do {                                                             \
    sli_em_cmu_SYSTICEXTCLKENSet();                                \
    SysTick->CTRL = (SysTick->CTRL & ~SysTick_CTRL_CLKSOURCE_Msk); \
  } while (0)

#define CMU_SYSTICK_SELECT_LFXO CMU_SYSTICK_SELECT_EM23GRPACLK
#define CMU_SYSTICK_SELECT_LFRCO CMU_SYSTICK_SELECT_EM23GRPACLK
#define CMU_SYSTICK_SELECT_ULFRCO CMU_SYSTICK_SELECT_EM23GRPACLK

#define CMU_SYSTICK_SELECT_HCLK                                    \
  do {                                                             \
    sli_em_cmu_SYSTICEXTCLKENClear();                              \
    SysTick->CTRL = (SysTick->CTRL | ~SysTick_CTRL_CLKSOURCE_Msk); \
  } while (0)

#define CMU_EM23GRPACLK_SELECT_LFRCO                                                  \
  do {                                                                                \
    CMU->EM23GRPACLKCTRL = (CMU->EM23GRPACLKCTRL & ~_CMU_EM23GRPACLKCTRL_CLKSEL_MASK) \
                           | CMU_EM23GRPACLKCTRL_CLKSEL_LFRCO;                        \
  } while (0)

#define CMU_LETIMER0_SELECT_LFRCO CMU_EM23GRPACLK_SELECT_LFRCO
#if defined(LESENSE_PRESENT)
#define CMU_LESENSE_SELECT_LFRCO CMU_EM23GRPACLK_SELECT_LFRCO
#define CMU_LESENSECLK_SELECT_LFRCO CMU_EM23GRPACLK_SELECT_LFRCO
#endif /* LESENSE_PRESENT */

#if defined(LFRCO_PRECISION_MODE) && (LFRCO_PRECISION_MODE == 1)
#define CMU_EM23GRPACLK_SELECT_PLFRCO                                                 \
  do {                                                                                \
    CMU->EM23GRPACLKCTRL = (CMU->EM23GRPACLKCTRL & ~_CMU_EM23GRPACLKCTRL_CLKSEL_MASK) \
                           | CMU_EM23GRPACLKCTRL_CLKSEL_LFRCO;                        \
  } while (0)

#define CMU_LETIMER0_SELECT_PLFRCO CMU_EM23GRPACLK_SELECT_PLFRCO
#if defined(LESENSE_PRESENT)
#define CMU_LESENSE_SELECT_PLFRCO CMU_EM23GRPACLK_SELECT_PLFRCO
#define CMU_LESENSECLK_SELECT_PLFRCO CMU_EM23GRPACLK_SELECT_PLFRCO
#endif /* LESENSE_PRESENT */
#endif /* LFRCO_PRECISION_MODE */

#define CMU_EM23GRPACLK_SELECT_LFXO                                                   \
  do {                                                                                \
    CMU->EM23GRPACLKCTRL = (CMU->EM23GRPACLKCTRL & ~_CMU_EM23GRPACLKCTRL_CLKSEL_MASK) \
                           | CMU_EM23GRPACLKCTRL_CLKSEL_LFXO;                         \
  } while (0)

#define CMU_LETIMER0_SELECT_LFXO CMU_EM23GRPACLK_SELECT_LFXO
#if defined(LESENSE_PRESENT)
#define CMU_LESENSE_SELECT_LFXO CMU_EM23GRPACLK_SELECT_LFXO
#define CMU_LESENSECLK_SELECT_LFXO CMU_EM23GRPACLK_SELECT_LFXO
#endif /* LESENSE_PRESENT */

#define CMU_EM23GRPACLK_SELECT_ULFRCO                                                 \
  do {                                                                                \
    CMU->EM23GRPACLKCTRL = (CMU->EM23GRPACLKCTRL & ~_CMU_EM23GRPACLKCTRL_CLKSEL_MASK) \
                           | CMU_EM23GRPACLKCTRL_CLKSEL_ULFRCO;                       \
  } while (0)

#define CMU_LETIMER0_SELECT_ULFRCO CMU_EM23GRPACLK_SELECT_ULFRCO
#if defined(LESENSE_PRESENT)
#define CMU_LESENSE_SELECT_ULFRCO CMU_EM23GRPACLK_SELECT_ULFRCO
#define CMU_LESENSECLK_SELECT_ULFRCO CMU_EM23GRPACLK_SELECT_ULFRCO
#endif /* LESENSE_PRESENT */

#define CMU_EM4GRPACLK_SELECT_LFRCO                                                \
  do {                                                                             \
    CMU->EM4GRPACLKCTRL = (CMU->EM4GRPACLKCTRL & ~_CMU_EM4GRPACLKCTRL_CLKSEL_MASK) \
                          | CMU_EM4GRPACLKCTRL_CLKSEL_LFRCO;                       \
  } while (0)

#define CMU_BURTC_SELECT_LFRCO CMU_EM4GRPACLK_SELECT_LFRCO

#if defined(LFRCO_PRECISION_MODE) && (LFRCO_PRECISION_MODE == 1)
#define CMU_EM4GRPACLK_SELECT_PLFRCO                                               \
  do {                                                                             \
    CMU->EM4GRPACLKCTRL = (CMU->EM4GRPACLKCTRL & ~_CMU_EM4GRPACLKCTRL_CLKSEL_MASK) \
                          | CMU_EM4GRPACLKCTRL_CLKSEL_LFRCO;                       \
  } while (0)

#define CMU_BURTC_SELECT_PLFRCO CMU_EM4GRPACLK_SELECT_PLFRCO
#endif /* LFRCO_PRECISION_MODE */

#define CMU_EM4GRPACLK_SELECT_LFXO                                                 \
  do {                                                                             \
    CMU->EM4GRPACLKCTRL = (CMU->EM4GRPACLKCTRL & ~_CMU_EM4GRPACLKCTRL_CLKSEL_MASK) \
                          | CMU_EM4GRPACLKCTRL_CLKSEL_LFXO;                        \
  } while (0)

#define CMU_BURTC_SELECT_LFXO CMU_EM4GRPACLK_SELECT_LFXO

#define CMU_EM4GRPACLK_SELECT_ULFRCO                                               \
  do {                                                                             \
    CMU->EM4GRPACLKCTRL = (CMU->EM4GRPACLKCTRL & ~_CMU_EM4GRPACLKCTRL_CLKSEL_MASK) \
                          | CMU_EM4GRPACLKCTRL_CLKSEL_ULFRCO;                      \
  } while (0)

#define CMU_BURTC_SELECT_ULFRCO CMU_EM4GRPACLK_SELECT_ULFRCO

#if defined(_CMU_EM01GRPBCLKCTRL_CLKSEL_MASK)
#define CMU_EM01GRPBCLK_SELECT_HFRCODPLL                                              \
  do {                                                                                \
    CMU->EM01GRPBCLKCTRL = (CMU->EM01GRPBCLKCTRL & ~_CMU_EM01GRPBCLKCTRL_CLKSEL_MASK) \
                           | CMU_EM01GRPBCLKCTRL_CLKSEL_HFRCODPLL;                    \
  } while (0)

#define CMU_PDMREF_SELECT_HFRCODPLL CMU_EM01GRPBCLK_SELECT_HFRCODPLL

#define CMU_EM01GRPBCLK_SELECT_HFXO                                                   \
  do {                                                                                \
    CMU->EM01GRPBCLKCTRL = (CMU->EM01GRPBCLKCTRL & ~_CMU_EM01GRPBCLKCTRL_CLKSEL_MASK) \
                           | CMU_EM01GRPBCLKCTRL_CLKSEL_HFXO;                         \
  } while (0)

#define CMU_PDMREF_SELECT_HFXO CMU_EM01GRPBCLK_SELECT_HFXO

#define CMU_EM01GRPBCLK_SELECT_FSRCO                                                  \
  do {                                                                                \
    CMU->EM01GRPBCLKCTRL = (CMU->EM01GRPBCLKCTRL & ~_CMU_EM01GRPBCLKCTRL_CLKSEL_MASK) \
                           | CMU_EM01GRPBCLKCTRL_CLKSEL_FSRCO;                        \
  } while (0)

#define CMU_PDMREF_SELECT_FSRCO CMU_EM01GRPBCLK_SELECT_FSRCO

#define CMU_EM01GRPBCLK_SELECT_CLKIN0                                                 \
  do {                                                                                \
    CMU->EM01GRPBCLKCTRL = (CMU->EM01GRPBCLKCTRL & ~_CMU_EM01GRPBCLKCTRL_CLKSEL_MASK) \
                           | CMU_EM01GRPBCLKCTRL_CLKSEL_CLKIN0;                       \
  } while (0)

#define CMU_PDMREF_SELECT_CLKIN0 CMU_EM01GRPBCLK_SELECT_CLKIN0

#define CMU_EM01GRPBCLK_SELECT_HFRCODPLLRT                                            \
  do {                                                                                \
    CMU->EM01GRPBCLKCTRL = (CMU->EM01GRPBCLKCTRL & ~_CMU_EM01GRPBCLKCTRL_CLKSEL_MASK) \
                           | CMU_EM01GRPBCLKCTRL_CLKSEL_HFRCODPLLRT;                  \
  } while (0)

#define CMU_PDMREF_SELECT_HFRCODPLLRT CMU_EM01GRPBCLK_SELECT_HFRCODPLLRT

#define CMU_EM01GRPBCLK_SELECT_HFXORT                                                 \
  do {                                                                                \
    CMU->EM01GRPBCLKCTRL = (CMU->EM01GRPBCLKCTRL & ~_CMU_EM01GRPBCLKCTRL_CLKSEL_MASK) \
                           | CMU_EM01GRPBCLKCTRL_CLKSEL_HFXORT;                       \
  } while (0)

#define CMU_PDMREF_SELECT_HFXORT CMU_EM01GRPBCLK_SELECT_HFXORT
#endif /* defined(_CMU_EM01GRPBCLKCTRL_CLKSEL_MASK) */

#define CMU_WDOG0_SELECT_LFRCO                                               \
  do {                                                                       \
    CMU->WDOG0CLKCTRL = (CMU->WDOG0CLKCTRL & ~_CMU_WDOG0CLKCTRL_CLKSEL_MASK) \
                        | CMU_WDOG0CLKCTRL_CLKSEL_LFRCO;                     \
  } while (0)

#define CMU_WDOG0CLK_SELECT_LFRCO CMU_WDOG0_SELECT_LFRCO

#if defined(LFRCO_PRECISION_MODE) && (LFRCO_PRECISION_MODE == 1)
#define CMU_WDOG0_SELECT_PLFRCO                                              \
  do {                                                                       \
    CMU->WDOG0CLKCTRL = (CMU->WDOG0CLKCTRL & ~_CMU_WDOG0CLKCTRL_CLKSEL_MASK) \
                        | CMU_WDOG0CLKCTRL_CLKSEL_LFRCO;                     \
  } while (0)

#define CMU_WDOG0CLK_SELECT_PLFRCO CMU_WDOG0_SELECT_PLFRCO
#endif /* LFRCO_PRECISION_MODE */

#define CMU_WDOG0_SELECT_LFXO                                                \
  do {                                                                       \
    CMU->WDOG0CLKCTRL = (CMU->WDOG0CLKCTRL & ~_CMU_WDOG0CLKCTRL_CLKSEL_MASK) \
                        | CMU_WDOG0CLKCTRL_CLKSEL_LFXO;                      \
  } while (0)

#define CMU_WDOG0CLK_SELECT_LFXO CMU_WDOG0_SELECT_LFXO

#define CMU_WDOG0_SELECT_ULFRCO                                              \
  do {                                                                       \
    CMU->WDOG0CLKCTRL = (CMU->WDOG0CLKCTRL & ~_CMU_WDOG0CLKCTRL_CLKSEL_MASK) \
                        | CMU_WDOG0CLKCTRL_CLKSEL_ULFRCO;                    \
  } while (0)

#define CMU_WDOG0CLK_SELECT_ULFRCO CMU_WDOG0_SELECT_ULFRCO

#define CMU_WDOG0_SELECT_HCLKDIV1024                                         \
  do {                                                                       \
    CMU->WDOG0CLKCTRL = (CMU->WDOG0CLKCTRL & ~_CMU_WDOG0CLKCTRL_CLKSEL_MASK) \
                        | CMU_WDOG0CLKCTRL_CLKSEL_HCLKDIV1024;               \
  } while (0)

#define CMU_WDOG0CLK_SELECT_HCLKDIV1024 CMU_WDOG0_SELECT_HCLKDIV1024

#if defined(_CMU_WDOG1CLKCTRL_CLKSEL_MASK)
#define CMU_WDOG1_SELECT_LFRCO                                               \
  do {                                                                       \
    CMU->WDOG1CLKCTRL = (CMU->WDOG1CLKCTRL & ~_CMU_WDOG1CLKCTRL_CLKSEL_MASK) \
                        | CMU_WDOG1CLKCTRL_CLKSEL_LFRCO;                     \
  } while (0)

#define CMU_WDOG1CLK_SELECT_LFRCO CMU_WDOG1_SELECT_LFRCO

#if defined(LFRCO_PRECISION_MODE) && (LFRCO_PRECISION_MODE == 1)
#define CMU_WDOG1_SELECT_PLFRCO                                              \
  do {                                                                       \
    CMU->WDOG1CLKCTRL = (CMU->WDOG1CLKCTRL & ~_CMU_WDOG1CLKCTRL_CLKSEL_MASK) \
                        | CMU_WDOG1CLKCTRL_CLKSEL_LFRCO;                     \
  } while (0)

#define CMU_WDOG1CLK_SELECT_PLFRCO CMU_WDOG1_SELECT_PLFRCO
#endif /* LFRCO_PRECISION_MODE */

#define CMU_WDOG1_SELECT_LFXO                                                \
  do {                                                                       \
    CMU->WDOG1CLKCTRL = (CMU->WDOG1CLKCTRL & ~_CMU_WDOG1CLKCTRL_CLKSEL_MASK) \
                        | CMU_WDOG1CLKCTRL_CLKSEL_LFXO;                      \
  } while (0)

#define CMU_WDOG1CLK_SELECT_LFXO CMU_WDOG1_SELECT_LFXO

#define CMU_WDOG1_SELECT_ULFRCO                                              \
  do {                                                                       \
    CMU->WDOG1CLKCTRL = (CMU->WDOG1CLKCTRL & ~_CMU_WDOG1CLKCTRL_CLKSEL_MASK) \
                        | CMU_WDOG1CLKCTRL_CLKSEL_ULFRCO;                    \
  } while (0)

#define CMU_WDOG1CLK_SELECT_ULFRCO CMU_WDOG1_SELECT_ULFRCO

#define CMU_WDOG1_SELECT_HCLKDIV1024                                         \
  do {                                                                       \
    CMU->WDOG1CLKCTRL = (CMU->WDOG1CLKCTRL & ~_CMU_WDOG1CLKCTRL_CLKSEL_MASK) \
                        | CMU_WDOG1CLKCTRL_CLKSEL_HCLKDIV1024;               \
  } while (0)

#define CMU_WDOG1CLK_SELECT_HCLKDIV1024 CMU_WDOG1_SELECT_HCLKDIV1024
#endif /* defined(_CMU_WDOG1CLKCTRL_CLKSEL_MASK) */

#define CMU_DPLLREFCLK_SELECT_HFXO                                                 \
  do {                                                                             \
    CMU->DPLLREFCLKCTRL = (CMU->DPLLREFCLKCTRL & ~_CMU_DPLLREFCLKCTRL_CLKSEL_MASK) \
                          | CMU_DPLLREFCLKCTRL_CLKSEL_HFXO;                        \
  } while (0)

#define CMU_DPLLREFCLK_SELECT_LFXO                                                 \
  do {                                                                             \
    CMU->DPLLREFCLKCTRL = (CMU->DPLLREFCLKCTRL & ~_CMU_DPLLREFCLKCTRL_CLKSEL_MASK) \
                          | CMU_DPLLREFCLKCTRL_CLKSEL_LFXO;                        \
  } while (0)

#define CMU_DPLLREFCLK_SELECT_CLKIN0                                               \
  do {                                                                             \
    CMU->DPLLREFCLKCTRL = (CMU->DPLLREFCLKCTRL & ~_CMU_DPLLREFCLKCTRL_CLKSEL_MASK) \
                          | CMU_DPLLREFCLKCTRL_CLKSEL_CLKIN0;                      \
  } while (0)

#define CMU_DPLLREFCLK_SELECT_DISABLED                                             \
  do {                                                                             \
    CMU->DPLLREFCLKCTRL = (CMU->DPLLREFCLKCTRL & ~_CMU_DPLLREFCLKCTRL_CLKSEL_MASK) \
                          | CMU_DPLLREFCLKCTRL_CLKSEL_DISABLED;                    \
  } while (0)

#if (defined(_SILICON_LABS_32B_SERIES_2_CONFIG_4)  \
  || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_5)  \
  || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_7)  \
  || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_8)) \
  && defined(CoreDebug_DEMCR_TRCENA_Msk)
#define CMU_TRACECLK_RESTORE_TRACE_PRE()                             \
  bool restoreTrace = CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk; \
  if (restoreTrace) {                                                \
    CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk;                 \
  }                                                                  \
  do {} while (0)

#define CMU_TRACECLK_RESTORE_TRACE_POST()           \
  if (restoreTrace) {                               \
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; \
  }                                                 \
  do {} while (0)

#else
#define CMU_TRACECLK_RESTORE_TRACE_PRE() do {} while (0)
#define CMU_TRACECLK_RESTORE_TRACE_POST() do {} while (0)
#endif

#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_1)
#define CMU_TRACECLK_SELECT_HCLK                                             \
  do {                                                                       \
    CMU_TRACECLK_RESTORE_TRACE_PRE();                                        \
    CMU->TRACECLKCTRL = (CMU->TRACECLKCTRL & ~_CMU_TRACECLKCTRL_CLKSEL_MASK) \
                        | CMU_TRACECLKCTRL_CLKSEL_HCLK;                      \
    CMU_TRACECLK_RESTORE_TRACE_POST();                                       \
  } while (0)

#endif /* _SILICON_LABS_32B_SERIES_2_CONFIG_1 */

#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_4)  \
  || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_5) \
  || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_7) \
  || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_8)
  #define CMU_TRACECLK_SELECT_SYSCLK                                         \
  do {                                                                       \
    CMU_TRACECLK_RESTORE_TRACE_PRE();                                        \
    CMU->TRACECLKCTRL = (CMU->TRACECLKCTRL & ~_CMU_TRACECLKCTRL_CLKSEL_MASK) \
                        | CMU_TRACECLKCTRL_CLKSEL_SYSCLK;                    \
    CMU_TRACECLK_RESTORE_TRACE_POST();                                       \
  } while (0)

#define CMU_TRACECLK_SELECT_HFRCODPLLRT                                      \
  do {                                                                       \
    CMU_TRACECLK_RESTORE_TRACE_PRE();                                        \
    CMU->TRACECLKCTRL = (CMU->TRACECLKCTRL & ~_CMU_TRACECLKCTRL_CLKSEL_MASK) \
                        | CMU_TRACECLKCTRL_CLKSEL_HFRCODPLLRT;               \
    CMU_TRACECLK_RESTORE_TRACE_POST();                                       \
  } while (0)

#endif

#if defined(CMU_TRACECLKCTRL_CLKSEL_HFRCOEM23)
#define CMU_TRACECLK_SELECT_HFRCOEM23                                        \
  do {                                                                       \
    CMU_TRACECLK_RESTORE_TRACE_PRE();                                        \
    CMU->TRACECLKCTRL = (CMU->TRACECLKCTRL & ~_CMU_TRACECLKCTRL_CLKSEL_MASK) \
                        | CMU_TRACECLKCTRL_CLKSEL_HFRCOEM23;                 \
    CMU_TRACECLK_RESTORE_TRACE_POST();                                       \
  } while (0)

#endif /* CMU_TRACECLKCTRL_CLKSEL_HFRCOEM23 */

#if defined(_CMU_EUART0CLKCTRL_CLKSEL_MASK)
#define CMU_EUART0_SELECT_EM01GRPACLK                                           \
  do {                                                                          \
    CMU->EUART0CLKCTRL = (CMU->EUART0CLKCTRL & ~_CMU_EUART0CLKCTRL_CLKSEL_MASK) \
                         | _CMU_EUART0CLKCTRL_CLKSEL_EM01GRPACLK;               \
  } while (0)

#define CMU_EUART0CLK_SELECT_EM01GRPACLK CMU_EUART0_SELECT_EM01GRPACLK

#define CMU_EUART0_SELECT_EM23GRPACLK                                           \
  do {                                                                          \
    CMU->EUART0CLKCTRL = (CMU->EUART0CLKCTRL & ~_CMU_EUART0CLKCTRL_CLKSEL_MASK) \
                         | _CMU_EUART0CLKCTRL_CLKSEL_EM23GRPACLK;               \
  } while (0)

#define CMU_EUART0CLK_SELECT_EM23GRPACLK CMU_EUART0_SELECT_EM23GRPACLK
#endif /* _CMU_EUART0CLKCTRL_CLKSEL_MASK */

#if defined(EUSART_PRESENT)
#if defined(_CMU_EUSART0CLKCTRL_CLKSEL_EM01GRPACLK)
#define CMU_EUSART0_SELECT_EM01GRPACLK                                             \
  do {                                                                             \
    CMU->EUSART0CLKCTRL = (CMU->EUSART0CLKCTRL & ~_CMU_EUSART0CLKCTRL_CLKSEL_MASK) \
                          | _CMU_EUSART0CLKCTRL_CLKSEL_EM01GRPACLK;                \
  } while (0)

#define CMU_EUSART0CLK_SELECT_EM01GRPACLK CMU_EUSART0_SELECT_EM01GRPACLK
#endif /* _CMU_EUSART0CLKCTRL_CLKSEL_EM01GRPACLK */

#if defined(_CMU_EUSART0CLKCTRL_CLKSEL_EM01GRPCCLK)
#define CMU_EUSART0_SELECT_EM01GRPCCLK                                             \
  do {                                                                             \
    CMU->EUSART0CLKCTRL = (CMU->EUSART0CLKCTRL & ~_CMU_EUSART0CLKCTRL_CLKSEL_MASK) \
                          | _CMU_EUSART0CLKCTRL_CLKSEL_EM01GRPCCLK;                \
  } while (0)

#define CMU_EUSART0CLK_SELECT_EM01GRPCCLK CMU_EUSART0_SELECT_EM01GRPCCLK
#endif /* _CMU_EUSART0CLKCTRL_CLKSEL_EM01GRPCCLK */

#if defined(_CMU_EUSART0CLKCTRL_CLKSEL_EM23GRPACLK)
#define CMU_EUSART0_SELECT_EM23GRPACLK                                             \
  do {                                                                             \
    CMU->EUSART0CLKCTRL = (CMU->EUSART0CLKCTRL & ~_CMU_EUSART0CLKCTRL_CLKSEL_MASK) \
                          | _CMU_EUSART0CLKCTRL_CLKSEL_EM23GRPACLK;                \
  } while (0)

#define CMU_EUSART0CLK_SELECT_EM23GRPACLK CMU_EUSART0_SELECT_EM23GRPACLK
#endif /* _CMU_EUSART0CLKCTRL_CLKSEL_EM23GRPACLK */

#if defined(_CMU_EUSART0CLKCTRL_CLKSEL_FSRCO)
#define CMU_EUSART0_SELECT_FSRCO                                                   \
  do {                                                                             \
    CMU->EUSART0CLKCTRL = (CMU->EUSART0CLKCTRL & ~_CMU_EUSART0CLKCTRL_CLKSEL_MASK) \
                          | _CMU_EUSART0CLKCTRL_CLKSEL_FSRCO;                      \
  } while (0)

#define CMU_EUSART0CLK_SELECT_FSRCO CMU_EUSART0_SELECT_FSRCO
#endif /* _CMU_EUSART0CLKCTRL_CLKSEL_FSRCO */

#if defined(_CMU_EUSART0CLKCTRL_CLKSEL_HFRCOEM23)
#define CMU_EUSART0_SELECT_HFRCOEM23                                               \
  do {                                                                             \
    CMU->EUSART0CLKCTRL = (CMU->EUSART0CLKCTRL & ~_CMU_EUSART0CLKCTRL_CLKSEL_MASK) \
                          | _CMU_EUSART0CLKCTRL_CLKSEL_HFRCOEM23;                  \
  } while (0)

#define CMU_EUSART0CLK_SELECT_HFRCOEM23 CMU_EUSART0_SELECT_HFRCOEM23
#endif /* _CMU_EUSART0CLKCTRL_CLKSEL_HFRCOEM23 */

#if defined(_CMU_EUSART0CLKCTRL_CLKSEL_LFRCO)
#define CMU_EUSART0_SELECT_LFRCO                                                   \
  do {                                                                             \
    CMU->EUSART0CLKCTRL = (CMU->EUSART0CLKCTRL & ~_CMU_EUSART0CLKCTRL_CLKSEL_MASK) \
                          | _CMU_EUSART0CLKCTRL_CLKSEL_LFRCO;                      \
  } while (0)

#define CMU_EUSART0CLK_SELECT_LFRCO CMU_EUSART0_SELECT_LFRCO

#if defined(LFRCO_PRECISION_MODE) && (LFRCO_PRECISION_MODE == 1)
#define CMU_EUSART0_SELECT_PLFRCO                                                  \
  do {                                                                             \
    CMU->EUSART0CLKCTRL = (CMU->EUSART0CLKCTRL & ~_CMU_EUSART0CLKCTRL_CLKSEL_MASK) \
                          | _CMU_EUSART0CLKCTRL_CLKSEL_LFRCO;                      \
  } while (0)

#define CMU_EUSART0CLK_SELECT_PLFRCO CMU_EUSART0_SELECT_PLFRCO
#endif /* LFRCO_PRECISION_MODE */
#endif /* _CMU_EUSART0CLKCTRL_CLKSEL_LFRCO */

#if defined(_CMU_EUSART0CLKCTRL_CLKSEL_LFXO)
#define CMU_EUSART0_SELECT_LFXO                                                    \
  do {                                                                             \
    CMU->EUSART0CLKCTRL = (CMU->EUSART0CLKCTRL & ~_CMU_EUSART0CLKCTRL_CLKSEL_MASK) \
                          | _CMU_EUSART0CLKCTRL_CLKSEL_LFXO;                       \
  } while (0)

#define CMU_EUSART0CLK_SELECT_LFXO CMU_EUSART0_SELECT_LFXO
#endif /* _CMU_EUSART0CLKCTRL_CLKSEL_LFXO */
#endif /* EUSART_PRESENT */

#if defined(_CMU_EM01GRPCCLKCTRL_MASK)
#define CMU_EM01GRPCCLK_SELECT_HFRCODPLL                                              \
  do {                                                                                \
    CMU->EM01GRPCCLKCTRL = (CMU->EM01GRPCCLKCTRL & ~_CMU_EM01GRPCCLKCTRL_CLKSEL_MASK) \
                           | _CMU_EM01GRPCCLKCTRL_CLKSEL_HFRCODPLL;                   \
  } while (0)

#if defined(EUSART_PRESENT) && EUSART_COUNT > 1
#define CMU_EUSART1_SELECT_HFRCODPLL CMU_EM01GRPCCLK_SELECT_HFRCODPLL
#endif /* EUSART_PRESENT && EUSART_COUNT > 1 */
#if defined(EUSART_PRESENT) && EUSART_COUNT > 2
#define CMU_EUSART2_SELECT_HFRCODPLL CMU_EM01GRPCCLK_SELECT_HFRCODPLL
#endif /* EUSART_PRESENT && EUSART_COUNT > 2 */
#if defined(EUSART_PRESENT) && EUSART_COUNT > 3
#define CMU_EUSART3_SELECT_HFRCODPLL CMU_EM01GRPCCLK_SELECT_HFRCODPLL
#endif /* EUSART_PRESENT && EUSART_COUNT > 3 */
#if defined(EUSART_PRESENT) && EUSART_COUNT > 4
#define CMU_EUSART4_SELECT_HFRCODPLL CMU_EM01GRPCCLK_SELECT_HFRCODPLL
#endif /* EUSART_PRESENT && EUSART_COUNT > 4 */

#if defined(CMU_EM01GRPCCLKCTRL_CLKSEL_HFRCODPLLRT)
#define CMU_EM01GRPCCLK_SELECT_HFRCODPLLRT                                            \
  do {                                                                                \
    CMU->EM01GRPCCLKCTRL = (CMU->EM01GRPCCLKCTRL & ~_CMU_EM01GRPCCLKCTRL_CLKSEL_MASK) \
                           | CMU_EM01GRPCCLKCTRL_CLKSEL_HFRCODPLLRT;                  \
  } while (0)

#if defined(EUSART_PRESENT) && EUSART_COUNT > 1
#define CMU_EUSART1_SELECT_HFRCODPLLRT CMU_EM01GRPCCLK_SELECT_HFRCODPLLRT
#endif /* EUSART_PRESENT && EUSART_COUNT > 1 */
#if defined(EUSART_PRESENT) && EUSART_COUNT > 2
#define CMU_EUSART2_SELECT_HFRCODPLLRT CMU_EM01GRPCCLK_SELECT_HFRCODPLLRT
#endif /* EUSART_PRESENT && EUSART_COUNT > 2 */
#if defined(EUSART_PRESENT) && EUSART_COUNT > 3
#define CMU_EUSART3_SELECT_HFRCODPLLRT CMU_EM01GRPCCLK_SELECT_HFRCODPLLRT
#endif /* EUSART_PRESENT && EUSART_COUNT > 3 */
#if defined(EUSART_PRESENT) && EUSART_COUNT > 4
#define CMU_EUSART4_SELECT_HFRCODPLLRT CMU_EM01GRPCCLK_SELECT_HFRCODPLLRT
#endif /* EUSART_PRESENT && EUSART_COUNT > 4 */
#endif /* CMU_EM01GRPCCLKCTRL_CLKSEL_HFRCODPLLRT */

#define CMU_EM01GRPCCLK_SELECT_HFRCOEM23                                              \
  do {                                                                                \
    CMU->EM01GRPCCLKCTRL = (CMU->EM01GRPCCLKCTRL & ~_CMU_EM01GRPCCLKCTRL_CLKSEL_MASK) \
                           | _CMU_EM01GRPCCLKCTRL_CLKSEL_HFRCOEM23;                   \
  } while (0)

#if defined(EUSART_PRESENT) && EUSART_COUNT > 1
#define CMU_EUSART1_SELECT_HFRCOEM23 CMU_EM01GRPCCLK_SELECT_HFRCOEM23
#endif /* EUSART_PRESENT && EUSART_COUNT > 1 */
#if defined(EUSART_PRESENT) && EUSART_COUNT > 2
#define CMU_EUSART2_SELECT_HFRCOEM23 CMU_EM01GRPCCLK_SELECT_HFRCOEM23
#endif /* EUSART_PRESENT && EUSART_COUNT > 2 */
#if defined(EUSART_PRESENT) && EUSART_COUNT > 3
#define CMU_EUSART3_SELECT_HFRCOEM23 CMU_EM01GRPCCLK_SELECT_HFRCOEM23
#endif /* EUSART_PRESENT && EUSART_COUNT > 3 */
#if defined(EUSART_PRESENT) && EUSART_COUNT > 4
#define CMU_EUSART4_SELECT_HFRCOEM23 CMU_EM01GRPCCLK_SELECT_HFRCOEM23
#endif /* EUSART_PRESENT && EUSART_COUNT > 4 */

#define CMU_EM01GRPCCLK_SELECT_FSRCO                                                  \
  do {                                                                                \
    CMU->EM01GRPCCLKCTRL = (CMU->EM01GRPCCLKCTRL & ~_CMU_EM01GRPCCLKCTRL_CLKSEL_MASK) \
                           | _CMU_EM01GRPCCLKCTRL_CLKSEL_FSRCO;                       \
  } while (0)

#if defined(EUSART_PRESENT) && EUSART_COUNT > 1
#define CMU_EUSART1_SELECT_FSRCO CMU_EM01GRPCCLK_SELECT_FSRCO
#endif /* EUSART_PRESENT && EUSART_COUNT > 1 */
#if defined(EUSART_PRESENT) && EUSART_COUNT > 2
#define CMU_EUSART2_SELECT_FSRCO CMU_EM01GRPCCLK_SELECT_FSRCO
#endif /* EUSART_PRESENT && EUSART_COUNT > 2 */
#if defined(EUSART_PRESENT) && EUSART_COUNT > 3
#define CMU_EUSART3_SELECT_FSRCO CMU_EM01GRPCCLK_SELECT_FSRCO
#endif /* EUSART_PRESENT && EUSART_COUNT > 3 */
#if defined(EUSART_PRESENT) && EUSART_COUNT > 4
#define CMU_EUSART4_SELECT_FSRCO CMU_EM01GRPCCLK_SELECT_FSRCO
#endif /* EUSART_PRESENT && EUSART_COUNT > 4 */

#define CMU_EM01GRPCCLK_SELECT_HFXO                                                   \
  do {                                                                                \
    CMU->EM01GRPCCLKCTRL = (CMU->EM01GRPCCLKCTRL & ~_CMU_EM01GRPCCLKCTRL_CLKSEL_MASK) \
                           | _CMU_EM01GRPCCLKCTRL_CLKSEL_HFXO;                        \
  } while (0)

#if defined(EUSART_PRESENT) && EUSART_COUNT > 1
#define CMU_EUSART1_SELECT_HFXO CMU_EM01GRPCCLK_SELECT_HFXO
#endif /* EUSART_PRESENT && EUSART_COUNT > 1 */
#if defined(EUSART_PRESENT) && EUSART_COUNT > 2
#define CMU_EUSART2_SELECT_HFXO CMU_EM01GRPCCLK_SELECT_HFXO
#endif /* EUSART_PRESENT && EUSART_COUNT > 2 */
#if defined(EUSART_PRESENT) && EUSART_COUNT > 3
#define CMU_EUSART3_SELECT_HFXO CMU_EM01GRPCCLK_SELECT_HFXO
#endif /* EUSART_PRESENT && EUSART_COUNT > 3 */
#if defined(EUSART_PRESENT) && EUSART_COUNT > 4
#define CMU_EUSART4_SELECT_HFXO CMU_EM01GRPCCLK_SELECT_HFXO
#endif /* EUSART_PRESENT && EUSART_COUNT > 4 */

#if defined(CMU_EM01GRPCCLKCTRL_CLKSEL_HFXORT)
#define CMU_EM01GRPCCLK_SELECT_HFXORT                                                 \
  do {                                                                                \
    CMU->EM01GRPCCLKCTRL = (CMU->EM01GRPCCLKCTRL & ~_CMU_EM01GRPCCLKCTRL_CLKSEL_MASK) \
                           | _CMU_EM01GRPCCLKCTRL_CLKSEL_HFXORT;                      \
  } while (0)

#if defined(EUSART_PRESENT) && EUSART_COUNT > 1
#define CMU_EUSART1_SELECT_HFXORT CMU_EM01GRPCCLK_SELECT_HFXORT
#endif /* EUSART_PRESENT && EUSART_COUNT > 1 */
#if defined(EUSART_PRESENT) && EUSART_COUNT > 2
#define CMU_EUSART2_SELECT_HFXORT CMU_EM01GRPCCLK_SELECT_HFXORT
#endif /* EUSART_PRESENT && EUSART_COUNT > 2 */
#if defined(EUSART_PRESENT) && EUSART_COUNT > 3
#define CMU_EUSART3_SELECT_HFXORT CMU_EM01GRPCCLK_SELECT_HFXORT
#endif /* EUSART_PRESENT && EUSART_COUNT > 3 */
#if defined(EUSART_PRESENT) && EUSART_COUNT > 4
#define CMU_EUSART4_SELECT_HFXORT CMU_EM01GRPCCLK_SELECT_HFXORT
#endif /* EUSART_PRESENT && EUSART_COUNT > 4 */
#endif /* CMU_EM01GRPCCLKCTRL_CLKSEL_HFXORT */
#endif /* _CMU_EM01GRPCCLKCTRL_MASK */

#if defined (RTCC_PRESENT)
#define CMU_RTCC_SELECT_LFRCO                                             \
  do {                                                                    \
    CMU->RTCCCLKCTRL = (CMU->RTCCCLKCTRL & ~_CMU_RTCCCLKCTRL_CLKSEL_MASK) \
                       | CMU_RTCCCLKCTRL_CLKSEL_LFRCO;                    \
  } while (0)

#define CMU_RTCCCLK_SELECT_LFRCO CMU_RTCC_SELECT_LFRCO

#if defined(LFRCO_PRECISION_MODE) && (LFRCO_PRECISION_MODE == 1)
#define CMU_RTCC_SELECT_PLFRCO                                            \
  do {                                                                    \
    CMU->RTCCCLKCTRL = (CMU->RTCCCLKCTRL & ~_CMU_RTCCCLKCTRL_CLKSEL_MASK) \
                       | CMU_RTCCCLKCTRL_CLKSEL_LFRCO;                    \
  } while (0)

#define CMU_RTCCCLK_SELECT_PLFRCO CMU_RTCC_SELECT_PLFRCO
#endif /* LFRCO_PRECISION_MODE */

#define CMU_RTCC_SELECT_LFXO                                              \
  do {                                                                    \
    CMU->RTCCCLKCTRL = (CMU->RTCCCLKCTRL & ~_CMU_RTCCCLKCTRL_CLKSEL_MASK) \
                       | CMU_RTCCCLKCTRL_CLKSEL_LFXO;                     \
  } while (0)

#define CMU_RTCCCLK_SELECT_LFXO CMU_RTCC_SELECT_LFXO

#define CMU_RTCC_SELECT_ULFRCO                                            \
  do {                                                                    \
    CMU->RTCCCLKCTRL = (CMU->RTCCCLKCTRL & ~_CMU_RTCCCLKCTRL_CLKSEL_MASK) \
                       | CMU_RTCCCLKCTRL_CLKSEL_ULFRCO;                   \
  } while (0)

#define CMU_RTCCCLK_SELECT_ULFRCO CMU_RTCC_SELECT_ULFRCO

#endif /* RTCC_PRESENT */

#if defined(SYSRTC_PRESENT)
#define CMU_SYSRTC_SELECT_LFRCO                                                    \
  do {                                                                             \
    CMU->SYSRTC0CLKCTRL = (CMU->SYSRTC0CLKCTRL & ~_CMU_SYSRTC0CLKCTRL_CLKSEL_MASK) \
                          | CMU_SYSRTC0CLKCTRL_CLKSEL_LFRCO;                       \
  } while (0)

#define CMU_SYSRTCCLK_SELECT_LFRCO CMU_SYSRTC_SELECT_LFRCO

#if defined(LFRCO_PRECISION_MODE) && (LFRCO_PRECISION_MODE == 1)
#define CMU_SYSRTC_SELECT_PLFRCO                                                   \
  do {                                                                             \
    CMU->SYSRTC0CLKCTRL = (CMU->SYSRTC0CLKCTRL & ~_CMU_SYSRTC0CLKCTRL_CLKSEL_MASK) \
                          | CMU_SYSRTC0CLKCTRL_CLKSEL_LFRCO;                       \
  } while (0)

#define CMU_SYSRTCCLK_SELECT_PLFRCO CMU_SYSRTC_SELECT_PLFRCO
#endif /* LFRCO_PRECISION_MODE */

#define CMU_SYSRTC_SELECT_LFXO                                                     \
  do {                                                                             \
    CMU->SYSRTC0CLKCTRL = (CMU->SYSRTC0CLKCTRL & ~_CMU_SYSRTC0CLKCTRL_CLKSEL_MASK) \
                          | CMU_SYSRTC0CLKCTRL_CLKSEL_LFXO;                        \
  } while (0)

#define CMU_SYSRTCCLK_SELECT_LFXO CMU_SYSRTC_SELECT_LFXO

#define CMU_SYSRTC_SELECT_ULFRCO                                                   \
  do {                                                                             \
    CMU->SYSRTC0CLKCTRL = (CMU->SYSRTC0CLKCTRL & ~_CMU_SYSRTC0CLKCTRL_CLKSEL_MASK) \
                          | CMU_SYSRTC0CLKCTRL_CLKSEL_ULFRCO;                      \
  } while (0)

#define CMU_SYSRTCCLK_SELECT_ULFRCO CMU_SYSRTC_SELECT_ULFRCO
#endif /* SYSRTC_PRESENT */

#if defined(LCD_PRESENT)
#define CMU_LCD_SELECT_LFRCO                                             \
  do {                                                                   \
    CMU->LCDCLKCTRL =  (CMU->LCDCLKCTRL  & ~_CMU_LCDCLKCTRL_CLKSEL_MASK) \
                      | CMU_LCDCLKCTRL_CLKSEL_LFRCO;                     \
  } while (0)

#define CMU_LCDCLK_SELECT_LFRCO CMU_LCD_SELECT_LFRCO

#if defined(LFRCO_PRECISION_MODE) && (LFRCO_PRECISION_MODE == 1)
#define CMU_LCD_SELECT_PLFRCO                                            \
  do {                                                                   \
    CMU->LCDCLKCTRL =  (CMU->LCDCLKCTRL  & ~_CMU_LCDCLKCTRL_CLKSEL_MASK) \
                      | CMU_LCDCLKCTRL_CLKSEL_LFRCO;                     \
  } while (0)

#define CMU_LCDCLK_SELECT_PLFRCO CMU_LCD_SELECT_PLFRCO
#endif /* LFRCO_PRECISION_MODE */

#define CMU_LCD_SELECT_LFXO                                              \
  do {                                                                   \
    CMU->LCDCLKCTRL =  (CMU->LCDCLKCTRL  & ~_CMU_LCDCLKCTRL_CLKSEL_MASK) \
                      | CMU_LCDCLKCTRL_CLKSEL_LFXO;                      \
  } while (0)

#define CMU_LCDCLK_SELECT_LFXO CMU_LCD_SELECT_LFXO

#define CMU_LCD_SELECT_ULFRCO                                            \
  do {                                                                   \
    CMU->LCDCLKCTRL =  (CMU->LCDCLKCTRL  & ~_CMU_LCDCLKCTRL_CLKSEL_MASK) \
                      | CMU_LCDCLKCTRL_CLKSEL_ULFRCO;                    \
  } while (0)

#define CMU_LCDCLK_SELECT_ULFRCO CMU_LCD_SELECT_ULFRCO
#endif /* LCD_PRESENT */

#if defined(VDAC_PRESENT)
#define CMU_VDAC0_SELECT_FSRCO                                               \
  do {                                                                       \
    CMU->VDAC0CLKCTRL = (CMU->VDAC0CLKCTRL & ~_CMU_VDAC0CLKCTRL_CLKSEL_MASK) \
                        | CMU_VDAC0CLKCTRL_CLKSEL_FSRCO;                     \
  } while (0)

#define CMU_VDAC0CLK_SELECT_FSRCO CMU_VDAC_SELECT_FSRCO

#define CMU_VDAC0_SELECT_HFRCOEM23                                           \
  do {                                                                       \
    CMU->VDAC0CLKCTRL = (CMU->VDAC0CLKCTRL & ~_CMU_VDAC0CLKCTRL_CLKSEL_MASK) \
                        | CMU_VDAC0CLKCTRL_CLKSEL_HFRCOEM23;                 \
  } while (0)

#define CMU_VDAC0CLK_SELECT_HFRCOEM23 CMU_VDAC_SELECT_HFRCOEM23

#define CMU_VDAC0_SELECT_EM01GRPACLK                                         \
  do {                                                                       \
    CMU->VDAC0CLKCTRL = (CMU->VDAC0CLKCTRL & ~_CMU_VDAC0CLKCTRL_CLKSEL_MASK) \
                        | CMU_VDAC0CLKCTRL_CLKSEL_EM01GRPACLK;               \
  } while (0)

#define CMU_VDAC0CLK_SELECT_EM01GRPACLK CMU_VDAC_SELECT_EM01GRPACLK

#define CMU_VDAC0_SELECT_EM23GRPACLK                                         \
  do {                                                                       \
    CMU->VDAC0CLKCTRL = (CMU->VDAC0CLKCTRL & ~_CMU_VDAC0CLKCTRL_CLKSEL_MASK) \
                        | CMU_VDAC0CLKCTRL_CLKSEL_EM23GRPACLK;               \
  } while (0)

#define CMU_VDAC0CLK_SELECT_EM23GRPACLK CMU_VDAC_SELECT_EM23GRPACLK

#if (VDAC_COUNT > 1)
#define CMU_VDAC1_SELECT_FSRCO                                               \
  do {                                                                       \
    CMU->VDAC1CLKCTRL = (CMU->VDAC1CLKCTRL & ~_CMU_VDAC1CLKCTRL_CLKSEL_MASK) \
                        | CMU_VDAC1CLKCTRL_CLKSEL_FSRCO;                     \
  } while (0)

#define CMU_VDAC1CLK_SELECT_FSRCO CMU_VDAC1_SELECT_FSRCO

#define CMU_VDAC1_SELECT_HFRCOEM23                                           \
  do {                                                                       \
    CMU->VDAC1CLKCTRL = (CMU->VDAC1CLKCTRL & ~_CMU_VDAC1CLKCTRL_CLKSEL_MASK) \
                        | CMU_VDAC1CLKCTRL_CLKSEL_HFRCOEM23;                 \
  } while (0)

#define CMU_VDAC1CLK_SELECT_HFRCOEM23 CMU_VDAC1_SELECT_HFRCOEM23

#define CMU_VDAC1_SELECT_EM01GRPACLK                                         \
  do {                                                                       \
    CMU->VDAC1CLKCTRL = (CMU->VDAC1CLKCTRL & ~_CMU_VDAC1CLKCTRL_CLKSEL_MASK) \
                        | CMU_VDAC1CLKCTRL_CLKSEL_EM01GRPACLK;               \
  } while (0)

#define CMU_VDAC1CLK_SELECT_EM01GRPACLK CMU_VDAC1_SELECT_EM01GRPACLK

#define CMU_VDAC1_SELECT_EM23GRPACLK                                         \
  do {                                                                       \
    CMU->VDAC1CLKCTRL = (CMU->VDAC1CLKCTRL & ~_CMU_VDAC1CLKCTRL_CLKSEL_MASK) \
                        | CMU_VDAC1CLKCTRL_CLKSEL_EM23GRPACLK;               \
  } while (0)

#define CMU_VDAC1CLK_SELECT_EM23GRPACLK CMU_VDAC1_SELECT_EM23GRPACLK
#endif /* VDAC_COUNT > 1 */
#endif /* VDAC_PRESENT */

#if defined(PCNT_PRESENT)
#define CMU_PCNT0_SELECT_EM23GRPACLK                                         \
  do {                                                                       \
    CMU->PCNT0CLKCTRL = (CMU->PCNT0CLKCTRL & ~_CMU_PCNT0CLKCTRL_CLKSEL_MASK) \
                        | CMU_PCNT0CLKCTRL_CLKSEL_EM23GRPACLK;               \
  } while (0)

#define CMU_PCNT0CLK_SELECT_EM23GRPACLK CMU_PCNT0_SELECT_EM23GRPACLK

#define CMU_PCNT0_SELECT_PCNTEXTCLK                                          \
  do {                                                                       \
    CMU->PCNT0CLKCTRL = (CMU->PCNT0CLKCTRL & ~_CMU_PCNT0CLKCTRL_CLKSEL_MASK) \
                        | CMU_PCNT0CLKCTRL_CLKSEL_PCNTS0;                    \
  } while (0)

#define CMU_PCNT0CLK_SELECT_PCNTEXTCLK CMU_PCNT0_SELECT_PCNTEXTCLK
#endif /* PCNT_PRESENT */

#if defined(LESENSE_PRESENT)
#define CMU_LESENSEHFCLK_SELECT_FSRCO                                                    \
  do {                                                                                   \
    CMU->LESENSEHFCLKCTRL = (CMU->LESENSEHFCLKCTRL & ~_CMU_LESENSEHFCLKCTRL_CLKSEL_MASK) \
                            | CMU_LESENSEHFCLKCTRL_CLKSEL_FSRCO;                         \
  } while (0)

#define CMU_LESENSEHFCLK_SELECT_HFRCOEM23                                                \
  do {                                                                                   \
    CMU->LESENSEHFCLKCTRL = (CMU->LESENSEHFCLKCTRL & ~_CMU_LESENSEHFCLKCTRL_CLKSEL_MASK) \
                            | CMU_LESENSEHFCLKCTRL_CLKSEL_HFRCOEM23;                     \
  } while (0)
#endif /* LESENSE_PRESENT */

#if defined(USB_PRESENT)
#define CMU_USB_SELECT_USBPLL0                                            \
  do {                                                                    \
    CMU->USB0CLKCTRL = (CMU->USB0CLKCTRL & ~_CMU_USB0CLKCTRL_CLKSEL_MASK) \
                       | CMU_USB0CLKCTRL_CLKSEL_USBPLL0;                  \
  } while (0)

#define CMU_USB_SELECT_LFXO                                               \
  do {                                                                    \
    CMU->USB0CLKCTRL = (CMU->USB0CLKCTRL & ~_CMU_USB0CLKCTRL_CLKSEL_MASK) \
                       | CMU_USB0CLKCTRL_CLKSEL_LFXO;                     \
  } while (0)

#define CMU_USB_SELECT_LFRCO                                              \
  do {                                                                    \
    CMU->USB0CLKCTRL = (CMU->USB0CLKCTRL & ~_CMU_USB0CLKCTRL_CLKSEL_MASK) \
                       | CMU_USB0CLKCTRL_CLKSEL_LFRCO;                    \
  } while (0)
#endif /* USB_PRESENT */

#elif defined(_SILICON_LABS_32B_SERIES_1) || defined(_SILICON_LABS_32B_SERIES_0)

/***************************************************************************//**
 * @brief This function configures the HFLE wait-states and divider suitable
 *        for the System Core Clock.
 *
 * @note FOR INTERNAL USE ONLY.
 *
 * @note This function is needed for macro expansion of CMU_CLOCK_SELECT_SET when
 *       the clock source is HFCLKLE.
 ******************************************************************************/
void sli_em_cmu_SetHFLEConfigSystemCoreClock(void);

/***************************************************************************//**
 * @brief This function configures the HFLE wait-states and divider suitable
 *        for the HF Clock.
 *
 * @note FOR INTERNAL USE ONLY.
 *
 * @note This function is needed for macro expansion of CMU_CLOCK_SELECT_SET when
 *       the clock source is HFCLKLE.
 ******************************************************************************/
void sli_em_cmu_SetHFLEConfigHFClock(void);

/***************************************************************************//**
 * @brief This function is used to initialize the HF clock and selecting
 *        an LF clock source.
 *
 * @note FOR INTERNAL USE ONLY.
 *
 * @param[in]osc
 *  Reference to a low-frequency oscillator. One of the following values is valid:
 *  - cmuOsc_LFXO
 *  - cmuOsc_LFRCO
 *
 * @note This function is needed for macro expansion of CMU_CLOCK_SELECT_SET when
 *       the clock is HF and LFXO or LFRCO is selected as the clock source.
 ******************************************************************************/
void sli_em_cmu_HFClockSelectLFOsc(uint8_t osc);

/***************************************************************************//**
 * @brief This function is used to initialize the HF clock and selecting
 *        HFXO as the clock source.
 *
 * @note FOR INTERNAL USE ONLY.
 *
 * @note This function is needed for macro expansion of CMU_CLOCK_SELECT_SET when
 *       the clock is HF and HFXO is selected as the clock source.
 ******************************************************************************/
void sli_em_cmu_HFClockSelectHFXO(void);

/***************************************************************************//**
 * @brief This function is used to initialize the HF clock and selecting
 *        HFRCO as the clock source.
 *
 * @note FOR INTERNAL USE ONLY.
 *
 * @note This function is needed for macro expansion of CMU_CLOCK_SELECT_SET when
 *       the clock is HF and HFRCO is selected as the clock source.
 ******************************************************************************/
void sli_em_cmu_HFClockSelectHFRCO(void);

#if defined(CMU_CMD_HFCLKSEL_USHFRCODIV2)
/***************************************************************************//**
 * @brief This function is used to initialize the HF clock and selecting
 *        USHFRCODIV2 as the clock source.
 *
 * @note FOR INTERNAL USE ONLY.
 *
 * @note This function is needed for macro expansion of CMU_CLOCK_SELECT_SET when
 *       the clock is HF and USHFRCODIV2 is selected as the clock source.
 ******************************************************************************/
void sli_em_cmu_HFClockSelectUSHFRCODIV2(void);
#endif

#if defined(CMU_HFCLKSTATUS_SELECTED_HFRCODIV2)
/***************************************************************************//**
 * @brief This function is used to initialize the HF clock and selecting
 *        HFRCODIV2 as the clock source.
 *
 * @note FOR INTERNAL USE ONLY.
 *
 * @note This function is needed for macro expansion of CMU_CLOCK_SELECT_SET when
 *       the clock is HF and HFRCODIV2 is selected as the clock source.
 ******************************************************************************/
void sli_em_cmu_HFClockSelectHFRCODIV2(void);
#endif

#if defined(CMU_HFCLKSTATUS_SELECTED_CLKIN0)
/***************************************************************************//**
 * @brief This function is used to initialize the HF clock and selecting
 *        CLKIN0 as the clock source.
 *
 * @note FOR INTERNAL USE ONLY.
 *
 * @note This function is needed for macro expansion of CMU_CLOCK_SELECT_SET when
 *       the clock is HF and CLKIN0 is selected as the clock source.
 ******************************************************************************/
void sli_em_cmu_HFClockSelectCLKIN0(void);
#endif

#if defined(CMU_HFCLKSTATUS_SELECTED_USHFRCO)
/***************************************************************************//**
 * @brief This function is used to initialize the HF clock and selecting
 *        USHFRCO as the clock source.
 *
 * @note FOR INTERNAL USE ONLY.
 *
 * @note This function is needed for macro expansion of CMU_CLOCK_SELECT_SET when
 *       the clock is HF and USHFRCO is selected as the clock source.
 ******************************************************************************/
void sli_em_cmu_HFClockSelectUSHFRCO(void);
#endif

#define CMU_HF_SELECT_LFXO                               \
  do {                                                   \
    sli_em_cmu_HFClockSelectLFOsc((uint8_t)cmuOsc_LFXO); \
  } while (0)

#define CMU_HF_SELECT_LFRCO                               \
  do {                                                    \
    sli_em_cmu_HFClockSelectLFOsc((uint8_t)cmuOsc_LFRCO); \
  } while (0)

#define CMU_HF_SELECT_HFXO          \
  do {                              \
    sli_em_cmu_HFClockSelectHFXO(); \
  } while (0)

#define CMU_HF_SELECT_HFRCO          \
  do {                               \
    sli_em_cmu_HFClockSelectHFRCO(); \
  } while (0)

#if defined(CMU_CMD_HFCLKSEL_USHFRCODIV2)
#define CMU_HF_SELECT_USHFRCODIV2          \
  do {                                     \
    sli_em_cmu_HFClockSelectUSHFRCODIV2(); \
  } while (0)
#endif

#if defined(CMU_HFCLKSTATUS_SELECTED_HFRCODIV2)
#define CMU_HF_SELECT_HFRCODIV2          \
  do {                                   \
    sli_em_cmu_HFClockSelectHFRCODIV2(); \
  } while (0)
#endif

#if defined(CMU_HFCLKSTATUS_SELECTED_CLKIN0)
#define CMU_HF_SELECT_CLKIN0          \
  do {                                \
    sli_em_cmu_HFClockSelectCLKIN0(); \
  } while (0)
#endif

#if defined(CMU_HFCLKSTATUS_SELECTED_USHFRCO)
#define CMU_HF_SELECT_USHFRCO          \
  do {                                 \
    sli_em_cmu_HFClockSelectUSHFRCO(); \
  } while (0)
#endif

#if defined(_SILICON_LABS_32B_SERIES_1)
#define CMU_LFA_SELECT_DISABLED                   \
  do {                                            \
    CMU->LFACLKSEL = _CMU_LFACLKSEL_LFA_DISABLED; \
  } while (0)

#define CMU_LFA_SELECT_LFXO                        \
  do {                                             \
    CMU_OscillatorEnable(cmuOsc_LFXO, true, true); \
    CMU->LFACLKSEL = _CMU_LFACLKSEL_LFA_LFXO;      \
  } while (0)

#define CMU_LFA_SELECT_LFRCO                        \
  do {                                              \
    CMU_OscillatorEnable(cmuOsc_LFRCO, true, true); \
    CMU->LFACLKSEL = _CMU_LFACLKSEL_LFA_LFRCO;      \
  } while (0)

#define CMU_LFA_SELECT_ULFRCO                   \
  do {                                          \
    CMU->LFACLKSEL = _CMU_LFACLKSEL_LFA_ULFRCO; \
  } while (0)

#if defined(CMU_OSCENCMD_PLFRCOEN)
#define CMU_LFA_SELECT_PLFRCO                        \
  do {                                               \
    CMU_OscillatorEnable(cmuOsc_PLFRCO, true, true); \
    CMU->LFACLKSEL = _CMU_LFACLKSEL_LFA_PLFRCO;      \
  } while (0)
#endif /* CMU_OSCENCMD_PLFRCOEN */

#define CMU_LFB_SELECT_DISABLED                   \
  do {                                            \
    CMU->LFBCLKSEL = _CMU_LFBCLKSEL_LFB_DISABLED; \
  } while (0)

#define CMU_LFB_SELECT_LFXO                        \
  do {                                             \
    CMU_OscillatorEnable(cmuOsc_LFXO, true, true); \
    CMU->LFBCLKSEL = _CMU_LFBCLKSEL_LFB_LFXO;      \
  } while (0)

#define CMU_LFB_SELECT_LFRCO                        \
  do {                                              \
    CMU_OscillatorEnable(cmuOsc_LFRCO, true, true); \
    CMU->LFBCLKSEL = _CMU_LFBCLKSEL_LFB_LFRCO;      \
  } while (0)

#define CMU_LFB_SELECT_HFCLKLE                                        \
  do {                                                                \
    sli_em_cmu_SetHFLEConfigHFClock();                                \
    BUS_RegBitWrite(&CMU->HFBUSCLKEN0, _CMU_HFBUSCLKEN0_LE_SHIFT, 1); \
    CMU->LFBCLKSEL = _CMU_LFBCLKSEL_LFB_HFCLKLE;                      \
  } while (0)

#define CMU_LFB_SELECT_ULFRCO                   \
  do {                                          \
    CMU->LFBCLKSEL = _CMU_LFBCLKSEL_LFB_ULFRCO; \
  } while (0)

#if defined(CMU_OSCENCMD_PLFRCOEN)
#define CMU_LFB_SELECT_PLFRCO                        \
  do {                                               \
    CMU_OscillatorEnable(cmuOsc_PLFRCO, true, true); \
    CMU->LFBCLKSEL = _CMU_LFBCLKSEL_LFB_PLFRCO;      \
  } while (0)
#endif /* CMU_OSCENCMD_PLFRCOEN */

#if defined(_CMU_LFCCLKSEL_MASK)
#define CMU_LFC_SELECT_DISABLED                   \
  do {                                            \
    CMU->LFCCLKSEL = _CMU_LFCCLKSEL_LFC_DISABLED; \
  } while (0)

#define CMU_LFC_SELECT_LFXO                        \
  do {                                             \
    CMU_OscillatorEnable(cmuOsc_LFXO, true, true); \
    CMU->LFCCLKSEL = _CMU_LFCCLKSEL_LFC_LFXO;      \
  } while (0)

#define CMU_LFC_SELECT_LFRCO                        \
  do {                                              \
    CMU_OscillatorEnable(cmuOsc_LFRCO, true, true); \
    CMU->LFCCLKSEL = _CMU_LFCCLKSEL_LFC_LFRCO;      \
  } while (0)

#define CMU_LFC_SELECT_ULFRCO                   \
  do {                                          \
    CMU->LFCCLKSEL = _CMU_LFCCLKSEL_LFC_ULFRCO; \
  } while (0)

#endif /* _CMU_LFCCLKSEL_MASK */

#define CMU_LFE_SELECT_DISABLED                   \
  do {                                            \
    CMU->LFECLKSEL = _CMU_LFECLKSEL_LFE_DISABLED; \
  } while (0)

#define CMU_LFE_SELECT_LFXO                        \
  do {                                             \
    CMU_OscillatorEnable(cmuOsc_LFXO, true, true); \
    CMU->LFECLKSEL = _CMU_LFECLKSEL_LFE_LFXO;      \
  } while (0)

#define CMU_LFE_SELECT_LFRCO                        \
  do {                                              \
    CMU_OscillatorEnable(cmuOsc_LFRCO, true, true); \
    CMU->LFECLKSEL = _CMU_LFECLKSEL_LFE_LFRCO;      \
  } while (0)

#define CMU_LFE_SELECT_ULFRCO                   \
  do {                                          \
    CMU->LFECLKSEL = _CMU_LFECLKSEL_LFE_ULFRCO; \
  } while (0)

#if defined(CMU_OSCENCMD_PLFRCOEN)
#define CMU_LFE_SELECT_PLFRCO                        \
  do {                                               \
    CMU_OscillatorEnable(cmuOsc_PLFRCO, true, true); \
    CMU->LFECLKSEL = _CMU_LFECLKSEL_LFE_PLFRCO;      \
  } while (0)
#endif /* CMU_OSCENCMD_PLFRCOEN */
#endif /* _SILICON_LABS_32B_SERIES_1 */

#if defined(_SILICON_LABS_32B_SERIES_0)
#if defined(_CMU_LFCLKSEL_LFAE_MASK)
#define CMU_LFA_SELECT_DISABLED                                               \
  do {                                                                        \
    CMU->LFCLKSEL = (CMU->LFCLKSEL                                            \
                     & ~(_CMU_LFCLKSEL_LFA_MASK | _CMU_LFCLKSEL_LFAE_MASK))   \
                    | (_CMU_LFCLKSEL_LFA_DISABLED << _CMU_LFCLKSEL_LFA_SHIFT) \
                    | (0 << _CMU_LFCLKSEL_LFAE_SHIFT);                        \
  } while (0)

#define CMU_LFA_SELECT_LFXO                                                 \
  do {                                                                      \
    CMU_OscillatorEnable(cmuOsc_LFXO, true, true);                          \
    CMU->LFCLKSEL = (CMU->LFCLKSEL                                          \
                     & ~(_CMU_LFCLKSEL_LFA_MASK | _CMU_LFCLKSEL_LFAE_MASK)) \
                    | (_CMU_LFCLKSEL_LFA_LFXO << _CMU_LFCLKSEL_LFA_SHIFT)   \
                    | (0 << _CMU_LFCLKSEL_LFAE_SHIFT);                      \
  } while (0)

#define CMU_LFA_SELECT_LFRCO                                                \
  do {                                                                      \
    CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);                         \
    CMU->LFCLKSEL = (CMU->LFCLKSEL                                          \
                     & ~(_CMU_LFCLKSEL_LFA_MASK | _CMU_LFCLKSEL_LFAE_MASK)) \
                    | (_CMU_LFCLKSEL_LFA_LFRCO << _CMU_LFCLKSEL_LFA_SHIFT)  \
                    | (0 << _CMU_LFCLKSEL_LFAE_SHIFT);                      \
  } while (0)

#define CMU_LFA_SELECT_HFCLKLE                                                       \
  do {                                                                               \
    sli_em_cmu_SetHFLEConfigSystemCoreClock();                                       \
    BUS_RegBitWrite(&CMU->HFCORECLKEN0, _CMU_HFCORECLKEN0_LE_SHIFT, 1);              \
    CMU->LFCLKSEL = (CMU->LFCLKSEL                                                   \
                     & ~(_CMU_LFCLKSEL_LFA_MASK | _CMU_LFCLKSEL_LFAE_MASK))          \
                    | (_CMU_LFCLKSEL_LFA_HFCORECLKLEDIV2 << _CMU_LFCLKSEL_LFA_SHIFT) \
                    | (0 << _CMU_LFCLKSEL_LFAE_SHIFT);                               \
  } while (0)

#if defined(CMU_LFCLKSEL_LFAE_ULFRCO)
#define CMU_LFA_SELECT_ULFRCO                                                 \
  do {                                                                        \
    CMU->LFCLKSEL = (CMU->LFCLKSEL                                            \
                     & ~(_CMU_LFCLKSEL_LFA_MASK | _CMU_LFCLKSEL_LFAE_MASK))   \
                    | (_CMU_LFCLKSEL_LFA_DISABLED << _CMU_LFCLKSEL_LFA_SHIFT) \
                    | (1 << _CMU_LFCLKSEL_LFAE_SHIFT);                        \
  } while (0)
#endif

#else
#define CMU_LFA_SELECT_DISABLED                                                \
  do {                                                                         \
    CMU->LFCLKSEL = (CMU->LFCLKSEL & ~_CMU_LFCLKSEL_LFA_MASK)                  \
                    | (_CMU_LFCLKSEL_LFA_DISABLED << _CMU_LFCLKSEL_LFA_SHIFT); \
  } while (0)

#define CMU_LFA_SELECT_LFXO                                                \
  do {                                                                     \
    CMU_OscillatorEnable(cmuOsc_LFXO, true, true);                         \
    CMU->LFCLKSEL = (CMU->LFCLKSEL & ~_CMU_LFCLKSEL_LFA_MASK)              \
                    | (_CMU_LFCLKSEL_LFA_LFXO << _CMU_LFCLKSEL_LFA_SHIFT); \
  } while (0)

#define CMU_LFA_SELECT_LFRCO                                                \
  do {                                                                      \
    CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);                         \
    CMU->LFCLKSEL = (CMU->LFCLKSEL & ~_CMU_LFCLKSEL_LFA_MASK)               \
                    | (_CMU_LFCLKSEL_LFA_LFRCO << _CMU_LFCLKSEL_LFA_SHIFT); \
  } while (0)

#define CMU_LFA_SELECT_HFCLKLE                                                        \
  do {                                                                                \
    sli_em_cmu_SetHFLEConfigSystemCoreClock();                                        \
    BUS_RegBitWrite(&CMU->HFCORECLKEN0, _CMU_HFCORECLKEN0_LE_SHIFT, 1);               \
    CMU->LFCLKSEL = (CMU->LFCLKSEL & ~_CMU_LFCLKSEL_LFA_MASK)                         \
                    | (_CMU_LFCLKSEL_LFA_HFCORECLKLEDIV2 << _CMU_LFCLKSEL_LFA_SHIFT); \
  } while (0)

#if defined(CMU_LFCLKSEL_LFAE_ULFRCO)
#define CMU_LFA_SELECT_ULFRCO                                                  \
  do {                                                                         \
    CMU->LFCLKSEL = (CMU->LFCLKSEL & ~_CMU_LFCLKSEL_LFA_MASK)                  \
                    | (_CMU_LFCLKSEL_LFA_DISABLED << _CMU_LFCLKSEL_LFA_SHIFT); \
  } while (0)
#endif /* CMU_LFA_SELECT_HFCLKLE */
#endif /* _CMU_LFCLKSEL_LFAE_MASK */

#if defined(_CMU_LFCLKSEL_LFBE_MASK)
#define CMU_LFB_SELECT_DISABLED                                               \
  do {                                                                        \
    CMU->LFCLKSEL = (CMU->LFCLKSEL                                            \
                     & ~(_CMU_LFCLKSEL_LFB_MASK | _CMU_LFCLKSEL_LFBE_MASK))   \
                    | (_CMU_LFCLKSEL_LFB_DISABLED << _CMU_LFCLKSEL_LFB_SHIFT) \
                    | (0 << _CMU_LFCLKSEL_LFBE_SHIFT);                        \
  } while (0)

#define CMU_LFB_SELECT_LFXO                                                 \
  do {                                                                      \
    CMU_OscillatorEnable(cmuOsc_LFXO, true, true);                          \
    CMU->LFCLKSEL = (CMU->LFCLKSEL                                          \
                     & ~(_CMU_LFCLKSEL_LFB_MASK | _CMU_LFCLKSEL_LFBE_MASK)) \
                    | (_CMU_LFCLKSEL_LFB_LFXO << _CMU_LFCLKSEL_LFB_SHIFT)   \
                    | (0 << _CMU_LFCLKSEL_LFBE_SHIFT);                      \
  } while (0)

#define CMU_LFB_SELECT_LFRCO                                                \
  do {                                                                      \
    CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);                         \
    CMU->LFCLKSEL = (CMU->LFCLKSEL                                          \
                     & ~(_CMU_LFCLKSEL_LFB_MASK | _CMU_LFCLKSEL_LFBE_MASK)) \
                    | (_CMU_LFCLKSEL_LFB_LFRCO << _CMU_LFCLKSEL_LFB_SHIFT)  \
                    | (0 << _CMU_LFCLKSEL_LFBE_SHIFT);                      \
  } while (0)

#define CMU_LFB_SELECT_HFCLKLE                                                       \
  do {                                                                               \
    sli_em_cmu_SetHFLEConfigSystemCoreClock();                                       \
    BUS_RegBitWrite(&CMU->HFCORECLKEN0, _CMU_HFCORECLKEN0_LE_SHIFT, 1);              \
    CMU->LFCLKSEL = (CMU->LFCLKSEL                                                   \
                     & ~(_CMU_LFCLKSEL_LFB_MASK | _CMU_LFCLKSEL_LFBE_MASK))          \
                    | (_CMU_LFCLKSEL_LFB_HFCORECLKLEDIV2 << _CMU_LFCLKSEL_LFB_SHIFT) \
                    | (0 << _CMU_LFCLKSEL_LFBE_SHIFT);                               \
  } while (0)

#if defined(CMU_LFCLKSEL_LFBE_ULFRCO)
#define CMU_LFB_SELECT_ULFRCO                                                 \
  do {                                                                        \
    CMU->LFCLKSEL = (CMU->LFCLKSEL                                            \
                     & ~(_CMU_LFCLKSEL_LFB_MASK | _CMU_LFCLKSEL_LFBE_MASK))   \
                    | (_CMU_LFCLKSEL_LFB_DISABLED << _CMU_LFCLKSEL_LFB_SHIFT) \
                    | (1 << _CMU_LFCLKSEL_LFBE_SHIFT);                        \
  } while (0)
#endif

#else
#define CMU_LFB_SELECT_DISABLED                                                \
  do {                                                                         \
    CMU->LFCLKSEL = (CMU->LFCLKSEL & ~_CMU_LFCLKSEL_LFB_MASK)                  \
                    | (_CMU_LFCLKSEL_LFB_DISABLED << _CMU_LFCLKSEL_LFB_SHIFT); \
  } while (0)

#define CMU_LFB_SELECT_LFXO                                                \
  do {                                                                     \
    CMU_OscillatorEnable(cmuOsc_LFXO, true, true);                         \
    CMU->LFCLKSEL = (CMU->LFCLKSEL & ~_CMU_LFCLKSEL_LFB_MASK)              \
                    | (_CMU_LFCLKSEL_LFB_LFXO << _CMU_LFCLKSEL_LFB_SHIFT); \
  } while (0)

#define CMU_LFB_SELECT_LFRCO                                                \
  do {                                                                      \
    CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);                         \
    CMU->LFCLKSEL = (CMU->LFCLKSEL & ~_CMU_LFCLKSEL_LFB_MASK)               \
                    | (_CMU_LFCLKSEL_LFB_LFRCO << _CMU_LFCLKSEL_LFB_SHIFT); \
  } while (0)

#define CMU_LFB_SELECT_HFCLKLE                                                        \
  do {                                                                                \
    sli_em_cmu_SetHFLEConfigSystemCoreClock();                                        \
    BUS_RegBitWrite(&CMU->HFCORECLKEN0, _CMU_HFCORECLKEN0_LE_SHIFT, 1);               \
    CMU->LFCLKSEL = (CMU->LFCLKSEL & ~_CMU_LFCLKSEL_LFB_MASK)                         \
                    | (_CMU_LFCLKSEL_LFB_HFCORECLKLEDIV2 << _CMU_LFCLKSEL_LFB_SHIFT); \
  } while (0)

#if defined(CMU_LFCLKSEL_LFBE_ULFRCO)
#define CMU_LFB_SELECT_ULFRCO                                                  \
  do {                                                                         \
    CMU->LFCLKSEL = (CMU->LFCLKSEL & ~_CMU_LFCLKSEL_LFB_MASK)                  \
                    | (_CMU_LFCLKSEL_LFB_DISABLED << _CMU_LFCLKSEL_LFB_SHIFT); \
  } while (0)
#endif /* CMU_LFCLKSEL_LFBE_ULFRCO */
#endif /* _CMU_LFCLKSEL_LFBE_MASK */

#define CMU_LFC_SELECT_DISABLED                                                \
  do {                                                                         \
    CMU->LFCLKSEL = (CMU->LFCLKSEL & ~_CMU_LFCLKSEL_LFC_MASK)                  \
                    | (_CMU_LFCLKSEL_LFC_DISABLED << _CMU_LFCLKSEL_LFC_SHIFT); \
  } while (0)

#define CMU_LFC_SELECT_LFXO                                                \
  do {                                                                     \
    CMU_OscillatorEnable(cmuOsc_LFXO, true, true);                         \
    CMU->LFCLKSEL = (CMU->LFCLKSEL & ~_CMU_LFCLKSEL_LFC_MASK)              \
                    | (_CMU_LFCLKSEL_LFC_LFXO << _CMU_LFCLKSEL_LFC_SHIFT); \
  } while (0)

#define CMU_LFC_SELECT_LFRCO                                                \
  do {                                                                      \
    CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);                         \
    CMU->LFCLKSEL = (CMU->LFCLKSEL & ~_CMU_LFCLKSEL_LFC_MASK)               \
                    | (_CMU_LFCLKSEL_LFC_LFRCO << _CMU_LFCLKSEL_LFC_SHIFT); \
  } while (0)
#endif /* _SILICON_LABS_32B_SERIES_0 */

#if defined(_CMU_DBGCLKSEL_DBG_MASK)
#define CMU_DBG_SELECT_AUXHFRCO                  \
  do {                                           \
    CMU->DBGCLKSEL = CMU_DBGCLKSEL_DBG_AUXHFRCO; \
  } while (0)

#define CMU_DBG_SELECT_HFCLK                  \
  do {                                        \
    CMU->DBGCLKSEL = CMU_DBGCLKSEL_DBG_HFCLK; \
  } while (0)
#endif /* _CMU_DBGCLKSEL_DBG_MASK */

#if defined(CMU_CTRL_DBGCLK)
#define CMU_DBG_SELECT_AUXHFRCO                        \
  do {                                                 \
    CMU->CTRL = (CMU->CTRL & ~(_CMU_CTRL_DBGCLK_MASK)) \
                | CMU_CTRL_DBGCLK_AUXHFRCO;            \
  } while (0)

#define CMU_DBG_SELECT_HFCLK                           \
  do {                                                 \
    CMU->CTRL = (CMU->CTRL & ~(_CMU_CTRL_DBGCLK_MASK)) \
                | CMU_CTRL_DBGCLK_HFCLK;               \
  } while (0)
#endif /* CMU_CTRL_DBGCLK */

#if defined(USB_PRESENT) && defined(_CMU_HFCORECLKEN0_USBC_MASK)
#define CMU_USBC_SELECT_LFXO                               \
  do {                                                     \
    CMU_OscillatorEnable(cmuOsc_LFXO, true, true);         \
    CMU->CMD = CMU_CMD_USBCCLKSEL_LFXO;                    \
    while ((CMU->STATUS & CMU_STATUS_USBCLFXOSEL) == 0) {} \
  } while (0)

#define CMU_USBC_SELECT_LFRCO                               \
  do {                                                      \
    CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);         \
    CMU->CMD = CMU_CMD_USBCCLKSEL_LFRCO;                    \
    while ((CMU->STATUS & CMU_STATUS_USBCLFRCOSEL) == 0) {} \
  } while (0)

#if defined(CMU_STATUS_USBCHFCLKSEL)
#define CMU_USBC_SELECT_HFCLK                               \
  do {                                                      \
    CMU->CMD = CMU_CMD_USBCCLKSEL_HFCLKNODIV;               \
    while ((CMU->STATUS & CMU_STATUS_USBCHFCLKSEL) == 0) {} \
  } while (0)
#endif /* CMU_STATUS_USBCHFCLKSEL */

#if defined(CMU_CMD_USBCCLKSEL_USHFRCO)
#define CMU_USBC_SELECT_USHFRCO                               \
  do {                                                        \
    CMU_OscillatorEnable(cmuOsc_USHFRCO, true, true);         \
    CMU->CMD = CMU_CMD_USBCCLKSEL_USHFRCO;                    \
    while ((CMU->STATUS & CMU_STATUS_USBCUSHFRCOSEL) == 0) {} \
  } while (0)
#endif /* CMU_CMD_USBCCLKSEL_USHFRCO */
#endif /* USB_PRESENT && _CMU_HFCORECLKEN0_USBC_MASK */

#if defined(_CMU_ADCCTRL_ADC0CLKSEL_MASK)
#define CMU_ADC0ASYNC_SELECT_DISABLED                                                     \
  do {                                                                                    \
    CMU->ADCCTRL = (CMU->ADCCTRL & ~_CMU_ADCCTRL_ADC0CLKSEL_MASK)                         \
                   | (_CMU_ADCCTRL_ADC0CLKSEL_DISABLED << _CMU_ADCCTRL_ADC0CLKSEL_SHIFT); \
  } while (0)

#define CMU_ADC0ASYNC_SELECT_AUXHFRCO                                                     \
  do {                                                                                    \
    CMU_OscillatorEnable(cmuOsc_AUXHFRCO, true, true);                                    \
    CMU->ADCCTRL = (CMU->ADCCTRL & ~_CMU_ADCCTRL_ADC0CLKSEL_MASK)                         \
                   | (_CMU_ADCCTRL_ADC0CLKSEL_AUXHFRCO << _CMU_ADCCTRL_ADC0CLKSEL_SHIFT); \
  } while (0)

#define CMU_ADC0ASYNC_SELECT_HFXO                                                     \
  do {                                                                                \
    CMU_OscillatorEnable(cmuOsc_HFXO, true, true);                                    \
    CMU->ADCCTRL = (CMU->ADCCTRL & ~_CMU_ADCCTRL_ADC0CLKSEL_MASK)                     \
                   | (_CMU_ADCCTRL_ADC0CLKSEL_HFXO << _CMU_ADCCTRL_ADC0CLKSEL_SHIFT); \
  } while (0)

#define CMU_ADC0ASYNC_SELECT_HFSRCCLK                                                     \
  do {                                                                                    \
    CMU->ADCCTRL = (CMU->ADCCTRL & ~_CMU_ADCCTRL_ADC0CLKSEL_MASK)                         \
                   | (_CMU_ADCCTRL_ADC0CLKSEL_HFSRCCLK << _CMU_ADCCTRL_ADC0CLKSEL_SHIFT); \
  } while (0)
#endif /* _CMU_ADCCTRL_ADC0CLKSEL_MASK */

#if defined(_CMU_ADCCTRL_ADC1CLKSEL_MASK)
#define CMU_ADC1ASYNC_SELECT_DISABLED                                                     \
  do {                                                                                    \
    CMU->ADCCTRL = (CMU->ADCCTRL & ~_CMU_ADCCTRL_ADC1CLKSEL_MASK)                         \
                   | (_CMU_ADCCTRL_ADC1CLKSEL_DISABLED << _CMU_ADCCTRL_ADC1CLKSEL_SHIFT); \
  } while (0)

#define CMU_ADC1ASYNC_SELECT_AUXHFRCO                                                     \
  do {                                                                                    \
    CMU_OscillatorEnable(cmuOsc_AUXHFRCO, true, true);                                    \
    CMU->ADCCTRL = (CMU->ADCCTRL & ~_CMU_ADCCTRL_ADC1CLKSEL_MASK)                         \
                   | (_CMU_ADCCTRL_ADC1CLKSEL_AUXHFRCO << _CMU_ADCCTRL_ADC1CLKSEL_SHIFT); \
  } while (0)

#define CMU_ADC1ASYNC_SELECT_HFXO                                                     \
  do {                                                                                \
    CMU_OscillatorEnable(cmuOsc_HFXO, true, true);                                    \
    CMU->ADCCTRL = (CMU->ADCCTRL & ~_CMU_ADCCTRL_ADC1CLKSEL_MASK)                     \
                   | (_CMU_ADCCTRL_ADC1CLKSEL_HFXO << _CMU_ADCCTRL_ADC1CLKSEL_SHIFT); \
  } while (0)

#define CMU_ADC1ASYNC_SELECT_HFSRCCLK                                                     \
  do {                                                                                    \
    CMU->ADCCTRL = (CMU->ADCCTRL & ~_CMU_ADCCTRL_ADC1CLKSEL_MASK)                         \
                   | (_CMU_ADCCTRL_ADC1CLKSEL_HFSRCCLK << _CMU_ADCCTRL_ADC1CLKSEL_SHIFT); \
  } while (0)
#endif /* _CMU_ADCCTRL_ADC1CLKSEL_MASK */

#if defined(_CMU_SDIOCTRL_SDIOCLKSEL_MASK)
#define CMU_SDIOREF_SELECT_HFRCO                                                          \
  do {                                                                                    \
    CMU_OscillatorEnable(cmuOsc_HFRCO, true, true);                                       \
    CMU->SDIOCTRL = (CMU->SDIOCTRL & ~_CMU_SDIOCTRL_SDIOCLKSEL_MASK)                      \
                    | (_CMU_SDIOCTRL_SDIOCLKSEL_HFRCO << _CMU_SDIOCTRL_SDIOCLKSEL_SHIFT); \
  } while (0)

#define CMU_SDIOREF_SELECT_HFXO                                                          \
  do {                                                                                   \
    CMU_OscillatorEnable(cmuOsc_HFXO, true, true);                                       \
    CMU->SDIOCTRL = (CMU->SDIOCTRL & ~_CMU_SDIOCTRL_SDIOCLKSEL_MASK)                     \
                    | (_CMU_SDIOCTRL_SDIOCLKSEL_HFXO << _CMU_SDIOCTRL_SDIOCLKSEL_SHIFT); \
  } while (0)

#define CMU_SDIOREF_SELECT_AUXHFRCO                                                          \
  do {                                                                                       \
    CMU_OscillatorEnable(cmuOsc_AUXHFRCO, true, true);                                       \
    CMU->SDIOCTRL = (CMU->SDIOCTRL & ~_CMU_SDIOCTRL_SDIOCLKSEL_MASK)                         \
                    | (_CMU_SDIOCTRL_SDIOCLKSEL_AUXHFRCO << _CMU_SDIOCTRL_SDIOCLKSEL_SHIFT); \
  } while (0)

#define CMU_SDIOREF_SELECT_USHFRCO                                                          \
  do {                                                                                      \
    CMU_OscillatorEnable(cmuOsc_USHFRCO, true, true);                                       \
    CMU->SDIOCTRL = (CMU->SDIOCTRL & ~_CMU_SDIOCTRL_SDIOCLKSEL_MASK)                        \
                    | (_CMU_SDIOCTRL_SDIOCLKSEL_USHFRCO << _CMU_SDIOCTRL_SDIOCLKSEL_SHIFT); \
  } while (0)
#endif /* _CMU_SDIOCTRL_SDIOCLKSEL_MASK */

#if defined(_CMU_QSPICTRL_QSPI0CLKSEL_MASK)
#define CMU_QSPI0REF_SELECT_HFRCO                                                           \
  do {                                                                                      \
    CMU_OscillatorEnable(cmuOsc_HFRCO, true, true);                                         \
    CMU->QSPICTRL = (CMU->QSPICTRL & ~_CMU_QSPICTRL_QSPI0CLKSEL_MASK)                       \
                    | (_CMU_QSPICTRL_QSPI0CLKSEL_HFRCO << _CMU_QSPICTRL_QSPI0CLKSEL_SHIFT); \
  } while (0)

#define CMU_QSPI0REF_SELECT_HFXO                                                           \
  do {                                                                                     \
    CMU_OscillatorEnable(cmuOsc_HFXO, true, true);                                         \
    CMU->QSPICTRL = (CMU->QSPICTRL & ~_CMU_QSPICTRL_QSPI0CLKSEL_MASK)                      \
                    | (_CMU_QSPICTRL_QSPI0CLKSEL_HFXO << _CMU_QSPICTRL_QSPI0CLKSEL_SHIFT); \
  } while (0)

#define CMU_QSPI0REF_SELECT_AUXHFRCO                                                           \
  do {                                                                                         \
    CMU_OscillatorEnable(cmuOsc_AUXHFRCO, true, true);                                         \
    CMU->QSPICTRL = (CMU->QSPICTRL & ~_CMU_QSPICTRL_QSPI0CLKSEL_MASK)                          \
                    | (_CMU_QSPICTRL_QSPI0CLKSEL_AUXHFRCO << _CMU_QSPICTRL_QSPI0CLKSEL_SHIFT); \
  } while (0)

#define CMU_QSPI0REF_SELECT_USHFRCO                                                           \
  do {                                                                                        \
    CMU_OscillatorEnable(cmuOsc_USHFRCO, true, true);                                         \
    CMU->QSPICTRL = (CMU->QSPICTRL & ~_CMU_QSPICTRL_QSPI0CLKSEL_MASK)                         \
                    | (_CMU_QSPICTRL_QSPI0CLKSEL_USHFRCO << _CMU_QSPICTRL_QSPI0CLKSEL_SHIFT); \
  } while (0)
#endif /* _CMU_QSPICTRL_QSPI0CLKSEL_MASK */

#if defined(_CMU_USBCTRL_USBCLKSEL_MASK)
#define CMU_USBR_SELECT_USHFRCO                                                        \
  do {                                                                                 \
    CMU_OscillatorEnable(cmuOsc_USHFRCO, true, true);                                  \
    CMU->USBCTRL = (CMU->USBCTRL & ~_CMU_USBCTRL_USBCLKSEL_MASK)                       \
                   | (_CMU_USBCTRL_USBCLKSEL_USHFRCO << _CMU_USBCTRL_USBCLKSEL_SHIFT); \
  } while (0)

#define CMU_USBR_SELECT_HFXO                                                        \
  do {                                                                              \
    CMU_OscillatorEnable(cmuOsc_HFXO, true, true);                                  \
    CMU->USBCTRL = (CMU->USBCTRL & ~_CMU_USBCTRL_USBCLKSEL_MASK)                    \
                   | (_CMU_USBCTRL_USBCLKSEL_HFXO << _CMU_USBCTRL_USBCLKSEL_SHIFT); \
  } while (0)

#define CMU_USBR_SELECT_HFXOX2                                                        \
  do {                                                                                \
    EFM_ASSERT(SystemHFXOClockGet() <= 25000000u);                                    \
    CMU->HFXOCTRL |= CMU_HFXOCTRL_HFXOX2EN;                                           \
    CMU_OscillatorEnable(cmuOsc_HFXO, true, true);                                    \
    CMU->USBCTRL = (CMU->USBCTRL & ~_CMU_USBCTRL_USBCLKSEL_MASK)                      \
                   | (_CMU_USBCTRL_USBCLKSEL_HFXOX2 << _CMU_USBCTRL_USBCLKSEL_SHIFT); \
  } while (0)

#define CMU_USBR_SELECT_HFRCO                                                        \
  do {                                                                               \
    CMU_OscillatorEnable(cmuOsc_HFRCO, true, true);                                  \
    CMU->USBCTRL = (CMU->USBCTRL & ~_CMU_USBCTRL_USBCLKSEL_MASK)                     \
                   | (_CMU_USBCTRL_USBCLKSEL_HFRCO << _CMU_USBCTRL_USBCLKSEL_SHIFT); \
  } while (0)

#define CMU_USBR_SELECT_LFXO                                                        \
  do {                                                                              \
    CMU_OscillatorEnable(cmuOsc_LFXO, true, true);                                  \
    CMU->USBCTRL = (CMU->USBCTRL & ~_CMU_USBCTRL_USBCLKSEL_MASK)                    \
                   | (_CMU_USBCTRL_USBCLKSEL_LFXO << _CMU_USBCTRL_USBCLKSEL_SHIFT); \
  } while (0)

#define CMU_USBR_SELECT_LFRCO                                                        \
  do {                                                                               \
    CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);                                  \
    CMU->USBCTRL = (CMU->USBCTRL & ~_CMU_USBCTRL_USBCLKSEL_MASK)                     \
                   | (_CMU_USBCTRL_USBCLKSEL_LFRCO << _CMU_USBCTRL_USBCLKSEL_SHIFT); \
  } while (0)
#endif /* _CMU_USBCTRL_USBCLKSEL_MASK */

#if defined(_CMU_PDMCTRL_PDMCLKSEL_MASK)
#define CMU_PDMREF_SELECT_USHFRCO                                                      \
  do {                                                                                 \
    CMU_OscillatorEnable(cmuOsc_USHFRCO, true, true);                                  \
    CMU->PDMCTRL = (CMU->PDMCTRL & ~_CMU_PDMCTRL_PDMCLKSEL_MASK)                       \
                   | (_CMU_PDMCTRL_PDMCLKSEL_USHFRCO << _CMU_PDMCTRL_PDMCLKSEL_SHIFT); \
  } while (0)

#define CMU_PDMREF_SELECT_HFXO                                                      \
  do {                                                                              \
    CMU_OscillatorEnable(cmuOsc_HFXO, true, true);                                  \
    CMU->PDMCTRL = (CMU->PDMCTRL & ~_CMU_PDMCTRL_PDMCLKSEL_MASK)                    \
                   | (_CMU_PDMCTRL_PDMCLKSEL_HFXO << _CMU_PDMCTRL_PDMCLKSEL_SHIFT); \
  } while (0)

#define CMU_PDMREF_SELECT_HFRCO                                                      \
  do {                                                                               \
    CMU_OscillatorEnable(cmuOsc_HFRCO, true, true);                                  \
    CMU->PDMCTRL = (CMU->PDMCTRL & ~_CMU_PDMCTRL_PDMCLKSEL_MASK)                     \
                   | (_CMU_PDMCTRL_PDMCLKSEL_HFRCO << _CMU_PDMCTRL_PDMCLKSEL_SHIFT); \
  } while (0)
#endif /* _CMU_PDMCTRL_PDMCLKSEL_MASK */
#endif /* _SILICON_LABS_32B_SERIES_2 */
/** @endcond */

#ifdef __cplusplus
}
#endif

#endif /* SLI_EM_CMU_H */
