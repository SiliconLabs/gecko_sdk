/***************************************************************************//**
 * @file
 * @brief Energy Management Unit (EMU) Peripheral API
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

#include <limits.h>

#include "em_emu.h"
#if defined(EMU_PRESENT) && (EMU_COUNT > 0)

#include "em_assert.h"
#include "em_cmu.h"
#include "em_common.h"
#include "em_core.h"
#include "em_system.h"
#include "em_ramfunc.h"

/* Consistency check, since restoring assumes similar bit positions in */
/* CMU OSCENCMD and STATUS regs. */
#if (CMU_STATUS_AUXHFRCOENS != CMU_OSCENCMD_AUXHFRCOEN)
#error Conflict in AUXHFRCOENS and AUXHFRCOEN bitpositions
#endif
#if (CMU_STATUS_HFXOENS != CMU_OSCENCMD_HFXOEN)
#error Conflict in HFXOENS and HFXOEN bitpositions
#endif
#if (CMU_STATUS_LFRCOENS != CMU_OSCENCMD_LFRCOEN)
#error Conflict in LFRCOENS and LFRCOEN bitpositions
#endif
#if (CMU_STATUS_LFXOENS != CMU_OSCENCMD_LFXOEN)
#error Conflict in LFXOENS and LFXOEN bitpositions
#endif

/*******************************************************************************
 ******************************   DEFINES   ************************************
 ******************************************************************************/

#if defined(_SILICON_LABS_32B_SERIES_0)
/* Fix for errata EMU_E107 - non-WIC interrupt masks. */
#if defined(_EFM32_GECKO_FAMILY)
#define ERRATA_FIX_EMU_E107_ENABLE
#define NON_WIC_INT_MASK_0    (~(0x0dfc0323U))
#define NON_WIC_INT_MASK_1    (~(0x0U))

#elif defined(_EFM32_TINY_FAMILY)
#define ERRATA_FIX_EMU_E107_ENABLE
#define NON_WIC_INT_MASK_0    (~(0x001be323U))
#define NON_WIC_INT_MASK_1    (~(0x0U))

#elif defined(_EFM32_GIANT_FAMILY)
#define ERRATA_FIX_EMU_E107_ENABLE
#define NON_WIC_INT_MASK_0    (~(0xff020e63U))
#define NON_WIC_INT_MASK_1    (~(0x00000046U))

#elif defined(_EFM32_WONDER_FAMILY)
#define ERRATA_FIX_EMU_E107_ENABLE
#define NON_WIC_INT_MASK_0    (~(0xff020e63U))
#define NON_WIC_INT_MASK_1    (~(0x00000046U))

#elif defined(_EFM32_ZERO_FAMILY)
#define ERRATA_FIX_EMU_E107_ENABLE
#define NON_WIC_INT_MASK_0    (~(0x00005c6bU))
#define NON_WIC_INT_MASK_1    (~(0x00000000U))

#elif defined(_EFM32_HAPPY_FAMILY)
#define ERRATA_FIX_EMU_E107_ENABLE
#define NON_WIC_INT_MASK_0    (~(0x00085c6bU))
#define NON_WIC_INT_MASK_1    (~(0x00000000U))

#endif
#endif

#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_74) \
  || (defined(_SILICON_LABS_32B_SERIES_0)         \
  && (defined(_EFM32_HAPPY_FAMILY) || defined(_EFM32_ZERO_FAMILY)))
// Fix for errata EMU_E110 - Potential Hard Fault when Exiting EM2.
#define ERRATA_FIX_EMU_E110_ENABLE
#endif

/* Fix for errata EMU_E108 - High Current Consumption on EM4 Entry. */
#if defined(_SILICON_LABS_32B_SERIES_0) && defined(_EFM32_HAPPY_FAMILY)
#define ERRATA_FIX_EMU_E108_ENABLE
#endif

/* Fix for errata EMU_E208 - Occasional Full Reset After Exiting EM4H. */
#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80)
#define ERRATA_FIX_EMU_E208_ENABLE
#endif

/* Enable FETCNT tuning errata fix. */
#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80)
#define ERRATA_FIX_DCDC_FETCNT_SET_ENABLE
#endif

/* Enable LN handshake errata fix. */
#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80)
#define ERRATA_FIX_DCDC_LNHS_BLOCK_ENABLE
typedef enum {
  errataFixDcdcHsInit,
  errataFixDcdcHsTrimSet,
  errataFixDcdcHsBypassLn,
  errataFixDcdcHsLnWaitDone
} errataFixDcdcHs_TypeDef;
static errataFixDcdcHs_TypeDef errataFixDcdcHsState = errataFixDcdcHsInit;
#endif

/* Fix for errata for EFM32GG11 and EFM32TG11. If a device is entering EM4S
 * while powering the analog peripherals from DVDD, firmware must switch
 * over to powering the analog peripherals from AVDD and delay the EM4S entry
 * with 30 us. */
#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_100) \
  || defined(_SILICON_LABS_GECKO_INTERNAL_SDID_103)
#define ERRATA_FIX_EM4S_DELAY_ENTRY
#endif

#if defined(_SILICON_LABS_32B_SERIES_1)             \
  && !defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80) \
  && !defined(ERRATA_FIX_EMU_E220_DECBOD_IGNORE)
/* EMU_E220 DECBOD Errata fix. DECBOD Reset can occur
 * during voltage scaling after EM2/3 wakeup. */
#define ERRATA_FIX_EMU_E220_DECBOD_ENABLE
#define EMU_PORBOD                   (*(volatile uint32_t *) (EMU_BASE + 0x14C))
#define EMU_PORBOD_GMC_CALIB_DISABLE (0x1UL << 31)
#endif

/* Used to figure out if a memory address is inside or outside of a RAM block.
 * A memory address is inside a RAM block if the address is greater than the
 * RAM block address. */
#define ADDRESS_NOT_IN_BLOCK(addr, block)  ((addr) <= (block) ? 1UL : 0UL)

/* RAM Block layout for various device families. Note that some devices
 * have special layout in RAM0 and some devices have a special RAM block
 * at the end of their block layout. */
#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_84)
#define RAM1_BLOCKS            2U
#define RAM1_BLOCK_SIZE  0x10000U // 64 kB blocks
#define RAM2_BLOCKS            1U
#define RAM2_BLOCK_SIZE    0x800U // 2 kB block
#elif defined(_SILICON_LABS_GECKO_INTERNAL_SDID_89)
#define RAM0_BLOCKS            2U
#define RAM0_BLOCK_SIZE   0x4000U
#define RAM1_BLOCKS            2U
#define RAM1_BLOCK_SIZE   0x4000U // 16 kB blocks
#define RAM2_BLOCKS            1U
#define RAM2_BLOCK_SIZE    0x800U // 2 kB block
#elif defined(_SILICON_LABS_GECKO_INTERNAL_SDID_95)
#define RAM0_BLOCKS            1U
#define RAM0_BLOCK_SIZE   0x4000U // 16 kB block
#define RAM1_BLOCKS            1U
#define RAM1_BLOCK_SIZE   0x4000U // 16 kB block
#define RAM2_BLOCKS            1U
#define RAM2_BLOCK_SIZE    0x800U // 2 kB block
#elif defined(_SILICON_LABS_GECKO_INTERNAL_SDID_103)
#define RAM0_BLOCKS            4U
#define RAM0_BLOCK_SIZE   0x2000U //  8 kB blocks
#elif defined(_SILICON_LABS_32B_SERIES_0) && defined(_EFM32_GIANT_FAMILY)
#define RAM0_BLOCKS            4U
#define RAM0_BLOCK_SIZE   0x8000U // 32 kB blocks
#elif defined(_SILICON_LABS_32B_SERIES_0) && defined(_EFM32_GECKO_FAMILY)
#define RAM0_BLOCKS            4U
#define RAM0_BLOCK_SIZE   0x1000U //  4 kB blocks
#elif defined(_SILICON_LABS_GECKO_INTERNAL_SDID_100)
#define RAM0_BLOCKS            8U
#define RAM0_BLOCK_SIZE   0x4000U // 16 kB blocks
#define RAM1_BLOCKS            8U
#define RAM1_BLOCK_SIZE   0x4000U // 16 kB blocks
#define RAM2_BLOCKS            4U
#define RAM2_BLOCK_SIZE  0x10000U // 64 kB blocks
#elif defined(_SILICON_LABS_GECKO_INTERNAL_SDID_106)
#define RAM0_BLOCKS            4U
#define RAM0_BLOCK_SIZE   0x4000U // 16 kB blocks
#define RAM1_BLOCKS            4U
#define RAM1_BLOCK_SIZE   0x4000U // 16 kB blocks
#define RAM2_BLOCKS            4U
#define RAM2_BLOCK_SIZE   0x4000U // 16 kB blocks
#elif defined(_SILICON_LABS_32B_SERIES_2_CONFIG_1)
#define RAM0_BLOCKS            6U
#define RAM0_BLOCK_SIZE   0x4000U // 16 kB blocks
#elif defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)
#define RAM0_BLOCKS            2U
#define RAM0_BLOCK_SIZE   0x4000U // 16 kB blocks
#elif defined(_SILICON_LABS_32B_SERIES_2_CONFIG_3)
#define RAM0_BLOCKS            4U
#define RAM0_BLOCK_SIZE   0x4000U // 16 kB blocks
#elif defined(_SILICON_LABS_32B_SERIES_2_CONFIG_4)
#define RAM0_BLOCKS           16U
#define RAM0_BLOCK_SIZE   0x4000U // 16 kB blocks
#elif defined(_SILICON_LABS_32B_SERIES_2_CONFIG_5)
#define RAM0_BLOCKS           16U
#define RAM0_BLOCK_SIZE   0x8000U // 32 kB blocks
#endif

#if defined(_SILICON_LABS_32B_SERIES_0)
/* RAM_MEM_END on Gecko devices have a value larger than the SRAM_SIZE. */
#define RAM0_END    (SRAM_BASE + SRAM_SIZE - 1)
#else
#define RAM0_END    RAM_MEM_END
#endif

#if defined(CMU_STATUS_HFXOSHUNTOPTRDY)
#define HFXO_STATUS_READY_FLAGS  (CMU_STATUS_HFXOPEAKDETRDY | CMU_STATUS_HFXOSHUNTOPTRDY)
#elif defined(CMU_STATUS_HFXOPEAKDETRDY)
#define HFXO_STATUS_READY_FLAGS  (CMU_STATUS_HFXOPEAKDETRDY)
#endif

#if defined(_EMU_DCDCCTRL_MASK)
#if !defined(PWRCFG_DCDCTODVDD_VMIN)
/** DCDCTODVDD output range maximum. */
#define PWRCFG_DCDCTODVDD_VMIN          1800U
#endif
#if !defined(PWRCFG_DCDCTODVDD_VMAX)
/** DCDCTODVDD output range minimum. */
#define PWRCFG_DCDCTODVDD_VMAX          3000U
#endif
#endif

#if defined(ERRATA_FIX_DCDC_FETCNT_SET_ENABLE) || defined(_EMU_DCDCCTRL_MASK)
#define DCDC_LP_PFET_CNT        7
#define DCDC_LP_NFET_CNT        7
#endif

#if defined(ERRATA_FIX_DCDC_LNHS_BLOCK_ENABLE)
#define EMU_DCDCSTATUS  (*(volatile uint32_t *)(EMU_BASE + 0x7C))
#endif

#if defined(_EMU_DCDCCTRL_MASK)
/* Translate fields with different names across platform generations to common names. */
#if defined(_EMU_DCDCMISCCTRL_LPCMPBIAS_MASK)
#define _GENERIC_DCDCMISCCTRL_LPCMPBIASEM234H_MASK      _EMU_DCDCMISCCTRL_LPCMPBIAS_MASK
#define _GENERIC_DCDCMISCCTRL_LPCMPBIASEM234H_SHIFT     _EMU_DCDCMISCCTRL_LPCMPBIAS_SHIFT
#elif defined(_EMU_DCDCMISCCTRL_LPCMPBIASEM234H_MASK)
#define _GENERIC_DCDCMISCCTRL_LPCMPBIASEM234H_MASK      _EMU_DCDCMISCCTRL_LPCMPBIASEM234H_MASK
#define _GENERIC_DCDCMISCCTRL_LPCMPBIASEM234H_SHIFT     _EMU_DCDCMISCCTRL_LPCMPBIASEM234H_SHIFT
#endif
#if defined(_EMU_DCDCLPCTRL_LPCMPHYSSEL_MASK)
#define _GENERIC_DCDCLPCTRL_LPCMPHYSSELEM234H_MASK      _EMU_DCDCLPCTRL_LPCMPHYSSEL_MASK
#define _GENERIC_DCDCLPCTRL_LPCMPHYSSELEM234H_SHIFT     _EMU_DCDCLPCTRL_LPCMPHYSSEL_SHIFT
#elif defined(_EMU_DCDCLPCTRL_LPCMPHYSSELEM234H_MASK)
#define _GENERIC_DCDCLPCTRL_LPCMPHYSSELEM234H_MASK      _EMU_DCDCLPCTRL_LPCMPHYSSELEM234H_MASK
#define _GENERIC_DCDCLPCTRL_LPCMPHYSSELEM234H_SHIFT     _EMU_DCDCLPCTRL_LPCMPHYSSELEM234H_SHIFT
#endif

/* Disable LP mode hysteresis in the state machine control. */
#define EMU_DCDCMISCCTRL_LPCMPHYSDIS (0x1UL << 1)
/* Comparator threshold on the high side. */
#define EMU_DCDCMISCCTRL_LPCMPHYSHI  (0x1UL << 2)
#define EMU_DCDCSMCTRL  (*(volatile uint32_t *)(EMU_BASE + 0x44))

#define DCDC_TRIM_MODES ((uint8_t)dcdcTrimMode_LN + 1)
#endif

#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80)
#define EMU_TESTLOCK         (*(volatile uint32_t *) (EMU_BASE + 0x190))
#define EMU_BIASCONF         (*(volatile uint32_t *) (EMU_BASE + 0x164))
#define EMU_BIASTESTCTRL     (*(volatile uint32_t *) (EMU_BASE + 0x19C))
#define CMU_ULFRCOCTRL       (*(volatile uint32_t *) (CMU_BASE + 0x03C))
#endif

#if defined(_EMU_TEMP_TEMP_MASK)
/* As the energy mode at which a temperature measurement was taken at is
 * not known, the chosen constant for the TEMPCO calculation is midway between
 * the EM0/EM1 constant and the EM2/EM3/EM4 constant.
 */
#define EMU_TEMPCO_CONST (0.273f)
#endif

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

/* Static user configuration. */
#if defined(_EMU_DCDCCTRL_MASK)
static uint16_t dcdcMaxCurrent_mA;
static uint16_t dcdcEm01LoadCurrent_mA;
static EMU_DcdcLnReverseCurrentControl_TypeDef dcdcReverseCurrentControl;
#endif
#if defined(EMU_VSCALE_EM01_PRESENT)
static EMU_EM01Init_TypeDef vScaleEM01Config = { false };
#endif

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/

#if defined(EMU_VSCALE_EM01_PRESENT)
/* Convert from level to EM0/1 command bit */
__STATIC_INLINE uint32_t vScaleEM01Cmd(EMU_VScaleEM01_TypeDef level)
{
#if defined(_SILICON_LABS_32B_SERIES_2)
  return EMU_CMD_EM01VSCALE1 << ((uint32_t)level - _EMU_STATUS_VSCALE_VSCALE1);
#else
  return EMU_CMD_EM01VSCALE0 << (_EMU_STATUS_VSCALE_VSCALE0 - (uint32_t)level);
#endif
}
#endif

#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_205) \
  || defined(ERRATA_FIX_EMU_E110_ENABLE)
SL_RAMFUNC_DECLARATOR static void __attribute__ ((noinline)) ramWFI(void);
SL_RAMFUNC_DEFINITION_BEGIN
static void __attribute__ ((noinline)) ramWFI(void)
{
#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_205)
  __WFI();                      // Enter EM2 or EM3
  if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk) {
    for (volatile int i = 0; i < 6; i++) {
    }                           // Dummy wait loop ...
  }

#else
  __WFI();                      // Enter EM2 or EM3
  *(volatile uint32_t*)4;       // Clear faulty read data after wakeup
#endif
}
SL_RAMFUNC_DEFINITION_END
#endif

#if defined(ERRATA_FIX_EMU_E220_DECBOD_ENABLE)
SL_RAMFUNC_DECLARATOR static void __attribute__ ((noinline)) ramWFI(void);
SL_RAMFUNC_DEFINITION_BEGIN
static void __attribute__ ((noinline)) ramWFI(void)
{
  /* Second part of EMU_E220 DECBOD Errata fix. Calibration needs to be disabled
   * quickly when coming out of EM2/EM3. Ram execution is needed to meet timing.
   * Calibration is re-enabled after voltage scaling completes. */
  uint32_t temp = EMU_PORBOD | EMU_PORBOD_GMC_CALIB_DISABLE;
  __WFI();
  EMU_PORBOD = temp;
}
SL_RAMFUNC_DEFINITION_END
#endif

#if (_SILICON_LABS_32B_SERIES < 2)
/***************************************************************************//**
 * @brief
 *   Save/restore/update oscillator, core clock and voltage scaling configuration on
 *   EM2 or EM3 entry/exit.
 *
 * @details
 *   Hardware may automatically change the oscillator and the voltage scaling configuration
 *   when going into or out of an energy mode. Static data in this function keeps track of
 *   such configuration bits and is used to restore state if needed.
 *
 ******************************************************************************/
typedef enum {
  emState_Save,         /* Save EMU and CMU state. */
  emState_Restore,      /* Restore and unlock.     */
} emState_TypeDef;

static void emState(emState_TypeDef action)
{
  uint32_t oscEnCmd;
  uint32_t cmuLocked;
  static uint32_t cmuStatus;
  static CMU_Select_TypeDef hfClock;
#if defined(EMU_VSCALE_PRESENT)
  static uint8_t vScaleStatus;
  static uint32_t hfrcoCtrl;
#endif

  /* Save or update state. */
  if (action == emState_Save) {
    /* Save configuration. */
    cmuStatus = CMU->STATUS;
    hfClock = CMU_ClockSelectGet(cmuClock_HF);
#if defined(EMU_VSCALE_PRESENT)
    /* Save vscale. */
    EMU_VScaleWait();
    vScaleStatus = (uint8_t)((EMU->STATUS & _EMU_STATUS_VSCALE_MASK)
                             >> _EMU_STATUS_VSCALE_SHIFT);
    hfrcoCtrl = CMU->HFRCOCTRL;
#endif
  } else { /* Restore state. */
    /* Apply saved configuration. */
#if defined(EMU_VSCALE_PRESENT)
#if defined(_SILICON_LABS_32B_SERIES_1)
    if (EMU_LDOStatusGet() == true)
    /* Restore voltage scaling level if LDO regulator is on. */
#endif
    {
      /* Restore EM0 and 1 voltage scaling level.
         @ref EMU_VScaleWait() is called later,
         just before HF clock select is set. */
      EMU->CMD = vScaleEM01Cmd((EMU_VScaleEM01_TypeDef)vScaleStatus);
    }
#endif
    /* CMU registers may be locked. */
    cmuLocked = CMU->LOCK & CMU_LOCK_LOCKKEY_LOCKED;
    CMU_Unlock();

#if defined(_CMU_OSCENCMD_MASK)
    /* AUXHFRCO are automatically disabled (except if using debugger). */
    /* HFRCO, USHFRCO and HFXO are automatically disabled. */
    /* LFRCO/LFXO may be disabled by SW in EM3. */
    /* Restore according to status prior to entering energy mode. */
    oscEnCmd = 0;
    oscEnCmd |= (cmuStatus & CMU_STATUS_HFRCOENS) != 0U
                ? CMU_OSCENCMD_HFRCOEN : 0U;
    oscEnCmd |= (cmuStatus & CMU_STATUS_AUXHFRCOENS) != 0U
                ? CMU_OSCENCMD_AUXHFRCOEN : 0U;
    oscEnCmd |= (cmuStatus & CMU_STATUS_LFRCOENS) != 0U
                ? CMU_OSCENCMD_LFRCOEN : 0U;
    oscEnCmd |= (cmuStatus & CMU_STATUS_HFXOENS) != 0U
                ? CMU_OSCENCMD_HFXOEN : 0U;
    oscEnCmd |= (cmuStatus & CMU_STATUS_LFXOENS) != 0U
                ? CMU_OSCENCMD_LFXOEN : 0U;
#if defined(_CMU_STATUS_USHFRCOENS_MASK)
    oscEnCmd |= (cmuStatus & CMU_STATUS_USHFRCOENS) != 0U
                ? CMU_OSCENCMD_USHFRCOEN : 0U;
#endif
    CMU->OSCENCMD = oscEnCmd;
#endif

#if defined(_EMU_STATUS_VSCALE_MASK)
    /* Wait for upscale to complete and then restore selected clock. */
    EMU_VScaleWait();
    if ((EMU->CTRL & _EMU_CTRL_EM23VSCALEAUTOWSEN_MASK) != 0U) {
      /* Restore HFRCO frequency which was automatically adjusted by hardware. */
      while ((CMU->SYNCBUSY & CMU_SYNCBUSY_HFRCOBSY) != 0U) {
      }
      CMU->HFRCOCTRL = hfrcoCtrl;
      if (hfClock == cmuSelect_HFRCO) {
        /* Optimize wait state after EM2/EM3 wakeup because hardware has
         * modified them. */
        CMU_UpdateWaitStates(SystemHfrcoFreq, (int)EMU_VScaleGet());
      }
    }
#endif

    if (hfClock != cmuSelect_HFRCO) {
      CMU_ClockSelectSet(cmuClock_HF, hfClock);
    }

#if defined(_CMU_OSCENCMD_MASK)
    /* If HFRCO was disabled before entering Energy Mode, turn it off again */
    /* as it is automatically enabled by wake up */
    if ((cmuStatus & CMU_STATUS_HFRCOENS) == 0U) {
      CMU->OSCENCMD = CMU_OSCENCMD_HFRCODIS;
    }
#endif

    /* Restore CMU register locking */
    if (cmuLocked != 0U) {
      CMU_Lock();
    }
  }
}
#endif

#if defined(ERRATA_FIX_EMU_E107_ENABLE)
/* Get enable conditions for errata EMU_E107 fix. */
__STATIC_INLINE bool getErrataFixEmuE107En(void)
{
#if defined(_EFM32_HAPPY_FAMILY)   \
  || defined(_EFM32_TINY_FAMILY)   \
  || defined(_EFM32_WONDER_FAMILY) \
  || defined(_EFM32_ZERO_FAMILY)
  // all revisions have the errata
  return true;
#else
  /* SYSTEM_ChipRevisionGet() could have been used here, but a faster implementation
   * would be needed in this case.
   */
  uint16_t majorMinorRev;

  /* CHIP MAJOR bit [3:0]. */
  majorMinorRev = ((ROMTABLE->PID0 & _ROMTABLE_PID0_REVMAJOR_MASK)
                   >> _ROMTABLE_PID0_REVMAJOR_SHIFT)
                  << 8;
  /* CHIP MINOR bit [7:4]. */
  majorMinorRev |= ((ROMTABLE->PID2 & _ROMTABLE_PID2_REVMINORMSB_MASK)
                    >> _ROMTABLE_PID2_REVMINORMSB_SHIFT)
                   << 4;
  /* CHIP MINOR bit [3:0]. */
  majorMinorRev |= (ROMTABLE->PID3 & _ROMTABLE_PID3_REVMINORLSB_MASK)
                   >> _ROMTABLE_PID3_REVMINORLSB_SHIFT;

#if defined(_EFM32_GECKO_FAMILY)
  // all GECKO revisions except Revision E have the errata
  return (majorMinorRev <= 0x0103);
#elif defined(_EFM32_GIANT_FAMILY)
  // all LEOPARD GECKO (Major = 0x01 Or 0x02) revisions have the errata
  // all GIANT GECKO (Major = 0x01) revisions except Revision E have the errata
  return (majorMinorRev <= 0x0103) || (majorMinorRev == 0x0204) || (majorMinorRev == 0x0205);
#else
  /* Invalid configuration. */
  EFM_ASSERT(false);
  /* Return when assertions are disabled. */
  return false;
#endif
#endif /* #if defined(_EFM32_ZERO_FAMILY) || defined(_EFM32_HAPPY_FAMILY) #else */
}
#endif /* #if defined(ERRATA_FIX_EMU_E107_ENABLE) */

#if defined(ERRATA_FIX_EMU_E110_ENABLE)
/* Get enable conditions for errata EMU_E110 fix. */
__STATIC_INLINE bool getErrataFixEmuE110En(void)
{
  /* SYSTEM_ChipRevisionGet() could have been used here, but a faster implementation
   * would be needed in this case.
   */
  uint16_t majorMinorRev;

  /* CHIP MAJOR bit [3:0]. */
  majorMinorRev = ((ROMTABLE->PID0 & _ROMTABLE_PID0_REVMAJOR_MASK)
                   >> _ROMTABLE_PID0_REVMAJOR_SHIFT)
                  << 8;
  /* CHIP MINOR bit [7:4]. */
  majorMinorRev |= ((ROMTABLE->PID2 & _ROMTABLE_PID2_REVMINORMSB_MASK)
                    >> _ROMTABLE_PID2_REVMINORMSB_SHIFT)
                   << 4;
  /* CHIP MINOR bit [3:0]. */
  majorMinorRev |= (ROMTABLE->PID3 & _ROMTABLE_PID3_REVMINORLSB_MASK)
                   >> _ROMTABLE_PID3_REVMINORLSB_SHIFT;

#if defined(_SILICON_LABS_32B_SERIES_0) && defined(_EFM32_ZERO_FAMILY)
  return (majorMinorRev == 0x0100);
#elif defined(_SILICON_LABS_32B_SERIES_0) && defined(_EFM32_HAPPY_FAMILY)
  return ((majorMinorRev == 0x0100 || majorMinorRev == 0x0101));
#elif defined(_SILICON_LABS_32B_SERIES_0) && defined(_EFM32_WONDER_FAMILY)
  return (majorMinorRev == 0x0100);
#elif defined(_SILICON_LABS_32B_SERIES_0) && defined(_EFM32_GIANT_FAMILY)
  return (majorMinorRev == 0x0204);
#else
  /* Invalid configuration. */
  EFM_ASSERT(false);
  /* Return when assertions are disabled. */
  return false;
#endif
}
#endif /* #if defined(ERRATA_FIX_EMU_E110_ENABLE) */

/* LP prepare / LN restore P/NFET count. */
#if defined(ERRATA_FIX_DCDC_FETCNT_SET_ENABLE)
static void currentLimitersUpdate(void);
static void dcdcFetCntSet(bool lpModeSet)
{
  uint32_t tmp;
  static uint32_t emuDcdcMiscCtrlReg;

  if (lpModeSet) {
    emuDcdcMiscCtrlReg = EMU->DCDCMISCCTRL;
    tmp  = EMU->DCDCMISCCTRL
           & ~(_EMU_DCDCMISCCTRL_PFETCNT_MASK | _EMU_DCDCMISCCTRL_NFETCNT_MASK);
    tmp |= (DCDC_LP_PFET_CNT << _EMU_DCDCMISCCTRL_PFETCNT_SHIFT)
           | (DCDC_LP_NFET_CNT << _EMU_DCDCMISCCTRL_NFETCNT_SHIFT);
    EMU->DCDCMISCCTRL = tmp;
    currentLimitersUpdate();
  } else {
    EMU->DCDCMISCCTRL = emuDcdcMiscCtrlReg;
    currentLimitersUpdate();
  }
}
#endif

#if defined(ERRATA_FIX_DCDC_LNHS_BLOCK_ENABLE)
static void dcdcHsFixLnBlock(void)
{
  if ((errataFixDcdcHsState == errataFixDcdcHsTrimSet)
      || (errataFixDcdcHsState == errataFixDcdcHsBypassLn)) {
    /* Wait for LNRUNNING */
    if ((EMU->DCDCCTRL & _EMU_DCDCCTRL_DCDCMODE_MASK) == EMU_DCDCCTRL_DCDCMODE_LOWNOISE) {
      while (!(EMU_DCDCSTATUS & (0x1 << 16))) {
      }
    }
    errataFixDcdcHsState = errataFixDcdcHsLnWaitDone;
  }
}
#endif

#if defined(_EMU_CTRL_EM23VSCALE_MASK) && defined(EMU_CTRL_EM23VSCALEAUTOWSEN)
/* Configure EMU and CMU for EM2 and 3 voltage downscale. */
static void vScaleDownEM23Setup(void)
{
#if defined(_SILICON_LABS_32B_SERIES_1)
  if (EMU_LDOStatusGet() == false) {
    /* Skip voltage scaling if the LDO regulator is turned off. */
    return;
  }
#endif

  /* Wait until previous scaling is done. */
  EMU_VScaleWait();

  uint32_t em23vs = (EMU->CTRL & _EMU_CTRL_EM23VSCALE_MASK) >> _EMU_CTRL_EM23VSCALE_SHIFT;
  uint32_t em01vs = (EMU->STATUS & _EMU_STATUS_VSCALE_MASK) >> _EMU_STATUS_VSCALE_SHIFT;

  /* Inverse coding. */
  if (em23vs > em01vs) {
    EMU->CTRL |= EMU_CTRL_EM23VSCALEAUTOWSEN;
#if defined(_MSC_RAMCTRL_RAMWSEN_MASK)
    /* Set RAM wait states for safe EM2 wakeup. */
    BUS_RegMaskedSet(&MSC->RAMCTRL, (MSC_RAMCTRL_RAMWSEN
                                     | MSC_RAMCTRL_RAM1WSEN
                                     | MSC_RAMCTRL_RAM2WSEN));
#endif
  } else {
    EMU->CTRL &= ~EMU_CTRL_EM23VSCALEAUTOWSEN;
  }
}

/* Handle automatic HFRCO adjustment that may have occurred during EM2/EM3. */
static void vScaleAfterWakeup(void)
{
  if ((EMU->CTRL & EMU_CTRL_EM23VSCALEAUTOWSEN) != 0U) {
    /* The hardware may have updated the HFRCOCTRL register during EM2/EM3
     * entry if voltage scaling in EM2/EM3 is enabled. The hardware would
     * then update the HFRCO frequency to 19 MHz automatically. */
    uint32_t freqRange = (CMU->HFRCOCTRL & _CMU_HFRCOCTRL_FREQRANGE_MASK)
                         >> _CMU_HFRCOCTRL_FREQRANGE_SHIFT;
    if (freqRange == 0x08U) {
      SystemHfrcoFreq = 19000000;
    }
  }
}
#endif

#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)
typedef enum {
  dpllState_Save,         /* Save DPLL state. */
  dpllState_Restore,      /* Restore DPLL.    */
} dpllState_TypeDef;

/* Save or restore and relock DPLL. */
static void dpllState(dpllState_TypeDef action)
{
  CMU_ClkDiv_TypeDef div;
  static uint32_t dpllRefClk = CMU_DPLLREFCLKCTRL_CLKSEL_DISABLED;

  if (action == dpllState_Save) {
    dpllRefClk = CMU_DPLLREFCLKCTRL_CLKSEL_DISABLED;
    CMU->CLKEN0_SET = CMU_CLKEN0_DPLL0;
    if (DPLL0->EN == DPLL_EN_EN) {
      /* DPLL is in use, save reference clock selection. */
      dpllRefClk = CMU->DPLLREFCLKCTRL;
    }
  } else { /* Restore */
    if ((dpllRefClk != CMU_DPLLREFCLKCTRL_CLKSEL_DISABLED)
        && (DPLL0->EN != DPLL_EN_EN)) {
      /* Restore DPLL reference clock selection. */
      CMU->DPLLREFCLKCTRL = dpllRefClk;
      /* Only wait for DPLL lock if HFRCODPLL is used as SYSCLK. */
      if (CMU_ClockSelectGet(cmuClock_SYSCLK) == cmuSelect_HFRCODPLL) {
        /* Set HCLK prescaler to safe value to avoid overclocking while locking. */
        div = CMU_ClockDivGet(cmuClock_HCLK);
        if (div == 1U) {
          CMU_ClockDivSet(cmuClock_HCLK, 2U);
        }

        /* Relock DPLL and wait for ready. */
        DPLL0->IF_CLR = DPLL_IF_LOCK | DPLL_IF_LOCKFAILLOW | DPLL_IF_LOCKFAILHIGH;
        DPLL0->EN_SET = DPLL_EN_EN;
        while ((DPLL0->IF & DPLL_IF_LOCK) == 0U) {
        }

        /* Restore HCLK prescaler. */
        if (div == 1U) {
          CMU_ClockDivSet(cmuClock_HCLK, 1U);
        }
      } else {
        /* Relock DPLL and exit without waiting for ready. */
        DPLL0->EN_SET = DPLL_EN_EN;
      }
    }
  }
}
#endif

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup emu EMU - Energy Management Unit
 * @brief Energy Management Unit (EMU) Peripheral API
 * @details
 *  This module contains functions to control the EMU peripheral of Silicon
 *  Labs 32-bit MCUs and SoCs. The EMU handles the different low energy modes
 *  in Silicon Labs microcontrollers.
 * @{
 ******************************************************************************/

#if defined(EMU_VSCALE_EM01_PRESENT)
/***************************************************************************//**
 * @brief
 *   Update the EMU module with Energy Mode 0 and 1 configuration.
 *
 * @param[in] em01Init
 *    Energy Mode 0 and 1 configuration structure.
 ******************************************************************************/
void EMU_EM01Init(const EMU_EM01Init_TypeDef *em01Init)
{
  vScaleEM01Config.vScaleEM01LowPowerVoltageEnable =
    em01Init->vScaleEM01LowPowerVoltageEnable;
  EMU_VScaleEM01ByClock(0, true);
}
#endif

/***************************************************************************//**
 * @brief
 *   Update the EMU module with Energy Mode 2 and 3 configuration.
 *
 * @param[in] em23Init
 *    Energy Mode 2 and 3 configuration structure.
 ******************************************************************************/
void EMU_EM23Init(const EMU_EM23Init_TypeDef *em23Init)
{
#if defined(_EMU_CTRL_EMVREG_MASK)
  EMU->CTRL = em23Init->em23VregFullEn ? (EMU->CTRL | EMU_CTRL_EMVREG)
              : (EMU->CTRL & ~EMU_CTRL_EMVREG);
#elif defined(_EMU_CTRL_EM23VREG_MASK)
  EMU->CTRL = em23Init->em23VregFullEn ? (EMU->CTRL | EMU_CTRL_EM23VREG)
              : (EMU->CTRL & ~EMU_CTRL_EM23VREG);
#else
  (void)em23Init;
#endif

#if defined(EMU_VSCALE_PRESENT)
  EMU->CTRL = (EMU->CTRL & ~_EMU_CTRL_EM23VSCALE_MASK)
              | ((uint32_t)em23Init->vScaleEM23Voltage << _EMU_CTRL_EM23VSCALE_SHIFT);
#if defined(CMU_HFXOCTRL_AUTOSTARTSELEM0EM1)
  if (em23Init->vScaleEM23Voltage == emuVScaleEM23_LowPower) {
    /* Voltage scaling is not compatible with HFXO auto start and select. */
    EFM_ASSERT((CMU->HFXOCTRL & CMU_HFXOCTRL_AUTOSTARTSELEM0EM1) == 0U);
  }
#endif
#endif
}

/***************************************************************************//**
 * @brief
 *   Energy mode 2/3 pre-sleep hook function.
 *
 * @details
 *   This function is called by EMU_EnterEM2() and EMU_EnterEM3() functions
 *   just prior to execution of the WFI instruction. The function implementation
 *   does not perform anything, but it is SL_WEAK so that it can be re-
 *   implemented in application code if actions are needed.
 ******************************************************************************/
SL_WEAK void EMU_EM23PresleepHook(void)
{
}

/***************************************************************************//**
 * @brief
 *   EFP's Energy mode 2/3 pre-sleep hook function.
 *
 * @details
 *   This function is similar to @ref EMU_EM23PresleepHook() but is reserved
 *   for EFP usage.
 *
 * @note
 *   The function is primarily meant to be used in systems with EFP circuitry.
 *   (EFP = Energy Friendly Pmic (PMIC = Power Management IC)).
 *   In such systems there is a need to drive certain signals to EFP pins to
 *   notify about energy mode transitions.
 ******************************************************************************/
SL_WEAK void EMU_EFPEM23PresleepHook(void)
{
}

/***************************************************************************//**
 * @brief
 *   Energy mode 2/3 post-sleep hook function.
 *
 * @details
 *   This function is called by EMU_EnterEM2() and EMU_EnterEM3() functions
 *   just after wakeup from the WFI instruction. The function implementation
 *   does not perform anything, but it is SL_WEAK so that it can be re-
 *   implemented in application code if actions are needed.
 ******************************************************************************/
SL_WEAK void EMU_EM23PostsleepHook(void)
{
}

/***************************************************************************//**
 * @brief
 *   EFP's Energy mode 2/3 post-sleep hook function.
 *
 * @details
 *   This function is similar to @ref EMU_EM23PostsleepHook() but is reserved
 *   for EFP usage.
 *
 * @note
 *   The function is primarily meant to be used in systems with EFP circuitry.
 *   (EFP = Energy Friendly Pmic (PMIC = Power Management IC)).
 *   In such systems there is a need to drive certain signals to EFP pins to
 *   notify about energy mode transitions.
 ******************************************************************************/
SL_WEAK void EMU_EFPEM23PostsleepHook(void)
{
}

/***************************************************************************//**
 * @brief
 *   Enter energy mode 2 (EM2).
 *
 * @details
 *   When entering EM2, high-frequency clocks are disabled, i.e., HFXO, HFRCO
 *   and AUXHFRCO (for AUXHFRCO, see exception note below). When re-entering
 *   EM0, HFRCO is re-enabled and the core will be clocked by the configured
 *   HFRCO band. This ensures a quick wakeup from EM2.
 *
 *   However, prior to entering EM2, the core may have been using another
 *   oscillator than HFRCO. The @p restore parameter gives the user the option
 *   to restore all HF oscillators according to state prior to entering EM2,
 *   as well as the clock used to clock the core. This restore procedure is
 *   handled by SW. However, since handled by SW, it will not be restored
 *   before completing the interrupt function(s) waking up the core!
 *
 * @note
 *   If restoring core clock to use the HFXO oscillator, which has been
 *   disabled during EM2 mode, this function will stall until the oscillator
 *   has stabilized. Stalling time can be reduced by adding interrupt
 *   support detecting stable oscillator, and an asynchronous switch to the
 *   original oscillator. See CMU documentation. Such a feature is however
 *   outside the scope of the implementation in this function.
 * @note
 *   If ERRATA_FIX_EMU_E110_ENABLE is active, the core's SLEEPONEXIT feature
 *   can not be used.
 * @par
 *   If HFXO is re-enabled by this function, and NOT used to clock the core,
 *   this function will not wait for HFXO to stabilize. This must be considered
 *   by the application if trying to use features relying on that oscillator
 *   upon return.
 * @par
 *   If a debugger is attached, the AUXHFRCO will not be disabled if enabled
 *   upon entering EM2. It will thus remain enabled when returning to EM0
 *   regardless of the @p restore parameter.
 * @par
 *   If HFXO autostart and select is enabled by using CMU_HFXOAutostartEnable(),
 *   the automatic starting and selecting of the core clocks will be done,
 *   regardless of the @p restore parameter, when waking up on the wakeup
 *   sources corresponding to the autostart and select setting.
 * @par
 *   If voltage scaling is supported, the restore parameter is true and the EM0
 *   voltage scaling level is set higher than the EM2 level, then the EM0 level is
 *   also restored.
 * @par
 *   On Series 2 Config 2 devices (EFRxG22), this function will also relock the
 *   DPLL if the DPLL is used and @p restore is true.
 *
 *   Note that the hardware will automatically update the HFRCO frequency in the
 *   case where voltage scaling is used in EM2/EM3 and not in EM0/EM1. When the
 *   restore argument to this function is true then software will restore the
 *   original HFRCO frequency after EM2/EM3 wake up. If the restore argument is
 *   false then the HFRCO frequency is 19 MHz when coming out of EM2/EM3 and
 *   all wait states are at a safe value.
 *
 * @param[in] restore
 *   @li true - save and restore oscillators, clocks and voltage scaling, see
 *   function details.
 *   @li false - do not save and restore oscillators and clocks, see function
 *   details.
 * @par
 *   The @p restore option should only be used if all clock control is done
 *   via the CMU API.
 ******************************************************************************/
void EMU_EnterEM2(bool restore)
{
#if defined(ERRATA_FIX_EMU_E107_ENABLE)
  bool errataFixEmuE107En;
  uint32_t nonWicIntEn[2];
#endif

#if defined(ERRATA_FIX_EMU_E110_ENABLE)
  bool errataFixEmuE110En;
#endif

#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)
  if (restore) {
    dpllState(dpllState_Save);
  }
#endif

#if (_SILICON_LABS_32B_SERIES < 2)
  /* Only save EMU and CMU state if restored on wake-up. */
  if (restore) {
    emState(emState_Save);
  }
#endif

#if defined(_EMU_CTRL_EM23VSCALE_MASK) && defined(EMU_CTRL_EM23VSCALEAUTOWSEN)
  vScaleDownEM23Setup();
#endif

  /* Enter Cortex deep sleep mode. */
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

  /* Fix for errata EMU_E107 - store non-WIC interrupt enable flags.
     Disable the enabled non-WIC interrupts. */
#if defined(ERRATA_FIX_EMU_E107_ENABLE)
  errataFixEmuE107En = getErrataFixEmuE107En();
  if (errataFixEmuE107En) {
    nonWicIntEn[0] = NVIC->ISER[0] & NON_WIC_INT_MASK_0;
    NVIC->ICER[0] = nonWicIntEn[0];
#if (NON_WIC_INT_MASK_1 != (~(0x0U)))
    nonWicIntEn[1] = NVIC->ISER[1] & NON_WIC_INT_MASK_1;
    NVIC->ICER[1] = nonWicIntEn[1];
#endif
  }
#endif

#if defined(ERRATA_FIX_DCDC_FETCNT_SET_ENABLE)
  dcdcFetCntSet(true);
#endif
#if defined(ERRATA_FIX_DCDC_LNHS_BLOCK_ENABLE)
  dcdcHsFixLnBlock();
#endif

  EMU_EM23PresleepHook();
  EMU_EFPEM23PresleepHook();
#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_205) \
  || defined(ERRATA_FIX_EMU_E110_ENABLE)
#if defined(ERRATA_FIX_EMU_E110_ENABLE)
  errataFixEmuE110En = getErrataFixEmuE110En();
  if (errataFixEmuE110En) {
#endif
  CORE_CRITICAL_SECTION(ramWFI(); )
#if defined(ERRATA_FIX_EMU_E110_ENABLE)
}
#endif
#elif defined(ERRATA_FIX_EMU_E220_DECBOD_ENABLE)
  // Apply errata fix if voltage scaling in EM2 is used.
  if ((EMU->CTRL & EMU_CTRL_EM23VSCALEAUTOWSEN) != 0U) {
    CORE_CRITICAL_SECTION(ramWFI(); )
  } else {
    __WFI();
  }
#else
  __WFI();
#endif
  EMU_EFPEM23PostsleepHook();
  EMU_EM23PostsleepHook();

#if defined(ERRATA_FIX_DCDC_FETCNT_SET_ENABLE)
  dcdcFetCntSet(false);
#endif

  /* Fix for errata EMU_E107 - restore state of non-WIC interrupt enable flags. */
#if defined(ERRATA_FIX_EMU_E107_ENABLE)
  if (errataFixEmuE107En) {
    NVIC->ISER[0] = nonWicIntEn[0];
#if (NON_WIC_INT_MASK_1 != (~(0x0U)))
    NVIC->ISER[1] = nonWicIntEn[1];
#endif
  }
#endif

#if (_SILICON_LABS_32B_SERIES < 2)
  /* Restore oscillators/clocks and voltage scaling if supported. */
  if (restore) {
    emState(emState_Restore);
  }
#if defined(_EMU_CTRL_EM23VSCALE_MASK) && defined(EMU_CTRL_EM23VSCALEAUTOWSEN)
  else {
    vScaleAfterWakeup();
  }
#if defined(ERRATA_FIX_EMU_E220_DECBOD_ENABLE)
  /* Third part of EMU_E220 DECBOD Errata fix. Calibration needs to be enabled
   * after voltage scaling completes. */
  EMU_PORBOD &= ~(EMU_PORBOD_GMC_CALIB_DISABLE);
#endif
#endif
#endif

#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)
  if (restore) {
    dpllState(dpllState_Restore);
  }
#endif

  if (!restore) {
    /* If not restoring, and the original clock was not HFRCO, the CMSIS */
    /* core clock variable must be updated since HF clock has changed */
    /* to HFRCO. */
    SystemCoreClockUpdate();
  }
}

/***************************************************************************//**
 * @brief
 *   Enter energy mode 3 (EM3).
 *
 * @details
 *   When entering EM3, the high-frequency clocks are disabled by hardware, i.e., HFXO,
 *   HFRCO, and AUXHFRCO (for AUXHFRCO, see exception note below). In addition,
 *   the low-frequency clocks, i.e., LFXO and LFRCO are disabled by software. When
 *   re-entering EM0, HFRCO is re-enabled and the core will be clocked by the
 *   configured HFRCO band. This ensures a quick wakeup from EM3.
 *
 *   However, prior to entering EM3, the core may have been using an
 *   oscillator other than HFRCO. The @p restore parameter gives the user the option
 *   to restore all HF/LF oscillators according to state prior to entering EM3,
 *   as well as the clock used to clock the core. This restore procedure is
 *   handled by software. However, since it is handled by software, it will not be restored
 *   before completing the interrupt function(s) waking up the core!
 *
 * @note
 *   If restoring core clock to use an oscillator other than HFRCO, this
 *   function will stall until the oscillator has stabilized. Stalling time
 *   can be reduced by adding interrupt support detecting stable oscillator,
 *   and an asynchronous switch to the original oscillator. See CMU
 *   documentation. This feature is, however, outside the scope of the
 *   implementation in this function.
 * @note
 *   If ERRATA_FIX_EMU_E110_ENABLE is active, the core's SLEEPONEXIT feature
 *   can't be used.
 * @par
 *   If HFXO/LFXO/LFRCO are re-enabled by this function, and NOT used to clock
 *   the core, this function will not wait for those oscillators to stabilize.
 *   This must be considered by the application if trying to use features
 *   relying on those oscillators upon return.
 * @par
 *   If a debugger is attached, the AUXHFRCO will not be disabled if enabled
 *   upon entering EM3. It will, therefore, remain enabled when returning to EM0
 *   regardless of the @p restore parameter.
 * @par
 *   If voltage scaling is supported, the restore parameter is true and the EM0
 *   voltage scaling level is set higher than the EM3 level, then the EM0 level is
 *   also restored.
 * @par
 *   On Series 2 Config 2 devices (EFRxG22), this function will also relock the
 *   DPLL if the DPLL is used and @p restore is true.
 *
 * @param[in] restore
 *   @li true - save and restore oscillators, clocks and voltage scaling, see
 *   function details.
 *   @li false - do not save and restore oscillators and clocks, see function
 *   details.
 * @par
 *   The @p restore option should only be used if all clock control is done
 *   via the CMU API.
 ******************************************************************************/
void EMU_EnterEM3(bool restore)
{
#if defined(ERRATA_FIX_EMU_E107_ENABLE)
  bool errataFixEmuE107En;
  uint32_t nonWicIntEn[2];
#endif

#if defined(ERRATA_FIX_EMU_E110_ENABLE)
  bool errataFixEmuE110En;
#endif

#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)
  if (restore) {
    dpllState(dpllState_Save);
  }
#endif

#if (_SILICON_LABS_32B_SERIES < 2)
  /* Only save EMU and CMU state if restored on wake-up. */
  if (restore) {
    emState(emState_Save);
  }
#endif

#if defined(_EMU_CTRL_EM23VSCALE_MASK) && defined(EMU_CTRL_EM23VSCALEAUTOWSEN)
  vScaleDownEM23Setup();
#endif

#if defined(_CMU_OSCENCMD_MASK)
  uint32_t cmuLocked;
  cmuLocked = CMU->LOCK & CMU_LOCK_LOCKKEY_LOCKED;
  CMU_Unlock();

  /* Disable LF oscillators. */
  CMU->OSCENCMD = CMU_OSCENCMD_LFXODIS | CMU_OSCENCMD_LFRCODIS;

  /* Restore CMU register locking. */
  if (cmuLocked != 0U) {
    CMU_Lock();
  }
#endif

  /* Enter Cortex deep sleep mode. */
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

  /* Fix for errata EMU_E107 - store non-WIC interrupt enable flags.
     Disable the enabled non-WIC interrupts. */
#if defined(ERRATA_FIX_EMU_E107_ENABLE)
  errataFixEmuE107En = getErrataFixEmuE107En();
  if (errataFixEmuE107En) {
    nonWicIntEn[0] = NVIC->ISER[0] & NON_WIC_INT_MASK_0;
    NVIC->ICER[0] = nonWicIntEn[0];
#if (NON_WIC_INT_MASK_1 != (~(0x0U)))
    nonWicIntEn[1] = NVIC->ISER[1] & NON_WIC_INT_MASK_1;
    NVIC->ICER[1] = nonWicIntEn[1];
#endif
  }
#endif

#if defined(ERRATA_FIX_DCDC_FETCNT_SET_ENABLE)
  dcdcFetCntSet(true);
#endif
#if defined(ERRATA_FIX_DCDC_LNHS_BLOCK_ENABLE)
  dcdcHsFixLnBlock();
#endif

  EMU_EM23PresleepHook();
#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_205) \
  || defined(ERRATA_FIX_EMU_E110_ENABLE)
#if defined(ERRATA_FIX_EMU_E110_ENABLE)
  errataFixEmuE110En = getErrataFixEmuE110En();
  if (errataFixEmuE110En) {
#endif
  CORE_CRITICAL_SECTION(ramWFI(); )
#if defined(ERRATA_FIX_EMU_E110_ENABLE)
}
#endif
#elif defined(ERRATA_FIX_EMU_E220_DECBOD_ENABLE)
  // Apply errata fix if voltage scaling in EM2 is used.
  if ((EMU->CTRL & EMU_CTRL_EM23VSCALEAUTOWSEN) != 0U) {
    CORE_CRITICAL_SECTION(ramWFI(); )
  } else {
    __WFI();
  }
#else
  __WFI();
#endif
  EMU_EM23PostsleepHook();

#if defined(ERRATA_FIX_DCDC_FETCNT_SET_ENABLE)
  dcdcFetCntSet(false);
#endif

  /* Fix for errata EMU_E107 - restore state of non-WIC interrupt enable flags. */
#if defined(ERRATA_FIX_EMU_E107_ENABLE)
  if (errataFixEmuE107En) {
    NVIC->ISER[0] = nonWicIntEn[0];
#if (NON_WIC_INT_MASK_1 != (~(0x0U)))
    NVIC->ISER[1] = nonWicIntEn[1];
#endif
  }
#endif

#if (_SILICON_LABS_32B_SERIES < 2)
  /* Restore oscillators/clocks and voltage scaling if supported. */
  if (restore) {
    emState(emState_Restore);
  }
#if defined(_EMU_CTRL_EM23VSCALE_MASK) && defined(EMU_CTRL_EM23VSCALEAUTOWSEN)
  else {
    vScaleAfterWakeup();
  }
#if defined(ERRATA_FIX_EMU_E220_DECBOD_ENABLE)
  /* Third part of EMU_E220 DECBOD Errata fix. Calibration needs to be enabled
   * after voltage scaling completes. */
  EMU_PORBOD &= ~(EMU_PORBOD_GMC_CALIB_DISABLE);
#endif
#endif
#endif

#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)
  if (restore) {
    dpllState(dpllState_Restore);
  }
#endif

  if (!restore) {
    /* If not restoring, and the original clock was not HFRCO, the CMSIS */
    /* core clock variable must be updated since HF clock has changed */
    /* to HFRCO. */
    SystemCoreClockUpdate();
  }
}

/***************************************************************************//**
 * @brief
 *   Save the CMU HF clock select state, oscillator enable, and voltage scaling
 *   (if available) before @ref EMU_EnterEM2() or @ref EMU_EnterEM3() are called
 *   with the restore parameter set to false. Calling this function is
 *   equivalent to calling @ref EMU_EnterEM2() or @ref EMU_EnterEM3() with the
 *   restore parameter set to true, but it allows the state to be saved without
 *   going to sleep. The state can be restored manually by calling
 *   @ref EMU_Restore().
 ******************************************************************************/
void EMU_Save(void)
{
#if (_SILICON_LABS_32B_SERIES < 2)
  emState(emState_Save);
#endif
#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)
  dpllState(dpllState_Save);
#endif
}

/***************************************************************************//**
 * @brief
 *   Restore CMU HF clock select state, oscillator enable, and voltage scaling
 *   (if available) after @ref EMU_EnterEM2() or @ref EMU_EnterEM3() are called
 *   with the restore parameter set to false. Calling this function is
 *   equivalent to calling @ref EMU_EnterEM2() or @ref EMU_EnterEM3() with the
 *   restore parameter set to true, but it allows the application to evaluate the
 *   wakeup reason before restoring state.
 ******************************************************************************/
void EMU_Restore(void)
{
#if (_SILICON_LABS_32B_SERIES < 2)
  emState(emState_Restore);
#endif
#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)
  dpllState(dpllState_Restore);
#endif
}

#if defined(_EMU_EM4CONF_MASK) || defined(_EMU_EM4CTRL_MASK)
/***************************************************************************//**
 * @brief
 *   Update the EMU module with Energy Mode 4 configuration.
 *
 * @param[in] em4Init
 *    Energy Mode 4 configuration structure.
 ******************************************************************************/
void EMU_EM4Init(const EMU_EM4Init_TypeDef *em4Init)
{
#if defined(_EMU_EM4CONF_MASK)
  /* Initialization for platforms with EMU->EM4CONF register. */
  uint32_t em4conf = EMU->EM4CONF;

  /* Clear fields that will be reconfigured. */
  em4conf &= ~(_EMU_EM4CONF_LOCKCONF_MASK
               | _EMU_EM4CONF_OSC_MASK
               | _EMU_EM4CONF_BURTCWU_MASK
               | _EMU_EM4CONF_VREGEN_MASK
               | _EMU_EM4CONF_BUBODRSTDIS_MASK);

  /* Configure new settings. */
  em4conf |= (em4Init->lockConfig << _EMU_EM4CONF_LOCKCONF_SHIFT)
             | (em4Init->osc)
             | (em4Init->buRtcWakeup << _EMU_EM4CONF_BURTCWU_SHIFT)
             | (em4Init->vreg << _EMU_EM4CONF_VREGEN_SHIFT)
             | (em4Init->buBodRstDis << _EMU_EM4CONF_BUBODRSTDIS_SHIFT);

  /* Apply configuration. Note that lock can be set after this stage. */
  EMU->EM4CONF = em4conf;

#elif defined(_EMU_EM4CTRL_EM4STATE_MASK)
  /* Initialization for platforms with EMU->EM4CTRL register and EM4H and EM4S. */

  uint32_t em4ctrl = EMU->EM4CTRL;

  em4ctrl &= ~(_EMU_EM4CTRL_RETAINLFXO_MASK
               | _EMU_EM4CTRL_RETAINLFRCO_MASK
               | _EMU_EM4CTRL_RETAINULFRCO_MASK
               | _EMU_EM4CTRL_EM4STATE_MASK
               | _EMU_EM4CTRL_EM4IORETMODE_MASK);

  em4ctrl |= (em4Init->retainLfxo     ? EMU_EM4CTRL_RETAINLFXO : 0U)
             | (em4Init->retainLfrco  ? EMU_EM4CTRL_RETAINLFRCO : 0U)
             | (em4Init->retainUlfrco ? EMU_EM4CTRL_RETAINULFRCO : 0U)
             | (em4Init->em4State == emuEM4Hibernate
                ? EMU_EM4CTRL_EM4STATE_EM4H : 0U)
             | ((uint32_t)em4Init->pinRetentionMode);

  EMU->EM4CTRL = em4ctrl;
#elif defined(_EMU_EM4CTRL_MASK)
  EMU->EM4CTRL = (EMU->EM4CTRL & ~_EMU_EM4CTRL_EM4IORETMODE_MASK)
                 | (uint32_t)em4Init->pinRetentionMode;
#endif

#if defined(_EMU_CTRL_EM4HVSCALE_MASK)
  EMU->CTRL = (EMU->CTRL & ~_EMU_CTRL_EM4HVSCALE_MASK)
              | ((uint32_t)em4Init->vScaleEM4HVoltage << _EMU_CTRL_EM4HVSCALE_SHIFT);
#endif
}
#endif

/***************************************************************************//**
 * @brief
 *   Energy mode 4 pre-sleep hook function.
 *
 * @details
 *   This function is called by @ref EMU_EnterEM4() just prior to the sequence
 *   of writes to put the device in EM4. The function implementation does not
 *   perform anything, but it is SL_WEAK so that it can be re-implemented in
 *   application code if actions are needed.
 ******************************************************************************/
SL_WEAK void EMU_EM4PresleepHook(void)
{
}

/***************************************************************************//**
 * @brief
 *   EFP's Energy mode 4 pre-sleep hook function.
 *
 * @details
 *   This function is similar to @ref EMU_EM4PresleepHook() but is reserved for
 *   EFP usage.
 *
 * @note
 *   The function is primarily meant to be used in systems with EFP circuitry.
 *   (EFP = Energy Friendly Pmic (PMIC = Power Management IC)).
 *   In such systems there is a need to drive certain signals to EFP pins to
 *   notify about energy mode transitions.
 ******************************************************************************/
SL_WEAK void EMU_EFPEM4PresleepHook(void)
{
}

/***************************************************************************//**
 * @brief
 *   Enter energy mode 4 (EM4).
 *
 * @note
 *   Only a power on reset or external reset pin can wake the device from EM4.
 ******************************************************************************/
void EMU_EnterEM4(void)
{
  int i;

#if defined(_EMU_EM4CTRL_EM4ENTRY_SHIFT)
  uint32_t em4seq2 = (EMU->EM4CTRL & ~_EMU_EM4CTRL_EM4ENTRY_MASK)
                     | (2U << _EMU_EM4CTRL_EM4ENTRY_SHIFT);
  uint32_t em4seq3 = (EMU->EM4CTRL & ~_EMU_EM4CTRL_EM4ENTRY_MASK)
                     | (3U << _EMU_EM4CTRL_EM4ENTRY_SHIFT);
#else
  uint32_t em4seq2 = (EMU->CTRL & ~_EMU_CTRL_EM4CTRL_MASK)
                     | (2U << _EMU_CTRL_EM4CTRL_SHIFT);
  uint32_t em4seq3 = (EMU->CTRL & ~_EMU_CTRL_EM4CTRL_MASK)
                     | (3U << _EMU_CTRL_EM4CTRL_SHIFT);
#endif

  /* Make sure that the register write lock is disabled. */
  EMU_Unlock();

#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80)
  /* The DCDC is not supported in EM4S. EFM32xG1 and EFR32xG1 devices should
   * switch to bypass mode before entering EM4S. Other devices handle this
   * automatically at the hardware level. */
  if ((EMU->EM4CTRL & _EMU_EM4CTRL_EM4STATE_MASK) == EMU_EM4CTRL_EM4STATE_EM4S) {
    uint32_t dcdcMode = EMU->DCDCCTRL & _EMU_DCDCCTRL_DCDCMODE_MASK;
    if (dcdcMode == EMU_DCDCCTRL_DCDCMODE_LOWNOISE
        || dcdcMode == EMU_DCDCCTRL_DCDCMODE_LOWPOWER) {
      EMU_DCDCModeSet(emuDcdcMode_Bypass);
    }
  }
#endif

#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)  \
  || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_3) \
  || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_4) \
  || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_5)
  /* Workaround for bug that may cause a Hard Fault on EM4 entry */
  CMU_ClockSelectSet(cmuClock_SYSCLK, cmuSelect_FSRCO);
  /* Switch from DCDC regulation mode to bypass mode before entering EM4. */
  EMU_DCDCModeSet(emuDcdcMode_Bypass);
#endif

#if defined(_EMU_EM4CTRL_MASK) && defined(ERRATA_FIX_EMU_E208_ENABLE)
  if (EMU->EM4CTRL & EMU_EM4CTRL_EM4STATE_EM4H) {
    /* Fix for errata EMU_E208 - Occasional Full Reset After Exiting EM4H.
     * Full description of errata fix can be found in the errata document. */
    __disable_irq();
    *(volatile uint32_t *)(EMU_BASE + 0x190UL)  = 0x0000ADE8UL;
    *(volatile uint32_t *)(EMU_BASE + 0x198UL) |= (0x1UL << 7);
    *(volatile uint32_t *)(EMU_BASE + 0x88UL)  |= (0x1UL << 8);
  }
#endif

#if defined(ERRATA_FIX_EMU_E108_ENABLE)
  /* Fix for errata EMU_E108 - High Current Consumption on EM4 Entry. */
  __disable_irq();
  *(volatile uint32_t *)0x400C80E4 = 0;
#endif

#if defined(ERRATA_FIX_DCDC_FETCNT_SET_ENABLE)
  dcdcFetCntSet(true);
#endif
#if defined(ERRATA_FIX_DCDC_LNHS_BLOCK_ENABLE)
  dcdcHsFixLnBlock();
#endif

#if defined(ERRATA_FIX_EM4S_DELAY_ENTRY)
  /* Fix for errata where firmware must clear ANASW and delay EM4S entry by 30 us. */
  if ((EMU->EM4CTRL & _EMU_EM4CTRL_EM4STATE_MASK) == EMU_EM4CTRL_EM4STATE_EM4S) {
    if ((EMU->PWRCTRL & _EMU_PWRCTRL_ANASW_MASK) == EMU_PWRCTRL_ANASW_DVDD) {
      BUS_RegMaskedClear(&EMU->PWRCTRL, _EMU_PWRCTRL_ANASW_MASK);
      /* Switch to 1 MHz HFRCO. This delays enough to meet the 30 us requirement
       * before entering EM4. */
      uint32_t freqCal = (DEVINFO->HFRCOCAL0 & ~_CMU_HFRCOCTRL_CLKDIV_MASK)
                         | CMU_HFRCOCTRL_CLKDIV_DIV4;
      while ((CMU->SYNCBUSY & CMU_SYNCBUSY_HFRCOBSY) != 0UL) {
      }
      CMU->HFRCOCTRL = freqCal;
      CMU->OSCENCMD = CMU_OSCENCMD_HFRCOEN;
      while ((CMU->STATUS & CMU_STATUS_HFRCORDY) == 0U) {
      }
      CMU->HFCLKSEL = CMU_HFCLKSEL_HF_HFRCO;
      __NOP();
    }
  }
#endif

  EMU_EM4PresleepHook();
  EMU_EFPEM4PresleepHook();

  for (i = 0; i < 4; i++) {
#if defined(_EMU_EM4CTRL_EM4ENTRY_SHIFT)
    EMU->EM4CTRL = em4seq2;
    EMU->EM4CTRL = em4seq3;
  }
  EMU->EM4CTRL = em4seq2;
#else
    EMU->CTRL = em4seq2;
    EMU->CTRL = em4seq3;
  }
  EMU->CTRL = em4seq2;
#endif
}

#if defined(_EMU_EM4CTRL_MASK)
/***************************************************************************//**
 * @brief
 *   Enter energy mode 4 hibernate (EM4H).
 *
 * @note
 *   Retention of clocks and GPIO in EM4 can be configured using
 *   @ref EMU_EM4Init before calling this function.
 ******************************************************************************/
void EMU_EnterEM4H(void)
{
#if defined(_EMU_EM4CTRL_EM4STATE_MASK)
  BUS_RegBitWrite(&EMU->EM4CTRL, _EMU_EM4CTRL_EM4STATE_SHIFT, 1);
#endif
  EMU_EnterEM4();
}

/***************************************************************************//**
 * @brief
 *   Enter energy mode 4 shutoff (EM4S).
 *
 * @note
 *   Retention of clocks and GPIO in EM4 can be configured using
 *   @ref EMU_EM4Init before calling this function.
 ******************************************************************************/
void EMU_EnterEM4S(void)
{
#if defined(_EMU_EM4CTRL_EM4STATE_MASK)
  BUS_RegBitWrite(&EMU->EM4CTRL, _EMU_EM4CTRL_EM4STATE_SHIFT, 0);
#endif
  EMU_EnterEM4();
}
#endif

/***************************************************************************//**
 * @brief
 *   Power down memory block.
 *
 * @param[in] blocks
 *   Specifies a logical OR of bits indicating memory blocks to power down.
 *   Bit 0 selects block 1, bit 1 selects block 2, and so on. Memory block 0 cannot
 *   be disabled. See the reference manual for available
 *   memory blocks for a device.
 *
 * @note
 *   Only a POR reset can power up the specified memory block(s) after power down.
 *
 * @deprecated
 *   This function is deprecated, use @ref EMU_RamPowerDown() instead which
 *   maps a user provided memory range into RAM blocks to power down.
 ******************************************************************************/
void EMU_MemPwrDown(uint32_t blocks)
{
#if defined(_EMU_MEMCTRL_MASK)
  EMU->MEMCTRL = blocks & _EMU_MEMCTRL_MASK;
#elif defined(_EMU_RAM0CTRL_MASK)
  EMU->RAM0CTRL = blocks & _EMU_RAM0CTRL_MASK;
#else
  (void)blocks;
#endif
}

/***************************************************************************//**
 * @brief
 *   Power down RAM memory blocks.
 *
 * @details
 *   This function will power down all the RAM blocks that are within a given
 *   range. The RAM block layout is different between device families, so this
 *   function can be used in a generic way to power down a RAM memory region
 *   which is known to be unused.
 *
 *   This function will only power down blocks which are completely enclosed
 *   by the memory range given by [start, end).
 *
 *   This is an example to power down all RAM blocks except the first
 *   one. The first RAM block is special in that it cannot be powered down
 *   by the hardware. The size of the first RAM block is device-specific.
 *   See the reference manual to find the RAM block sizes.
 *
 * @code
 *   EMU_RamPowerDown(SRAM_BASE, SRAM_BASE + SRAM_SIZE);
 * @endcode
 *
 * @note
 *   Only a reset can power up the specified memory block(s) after power down
 *   on a series 0 device. The specified memory block(s) will stay off
 *   until a call to EMU_RamPowerUp() is done on series 1/2.
 *
 * @param[in] start
 *   The start address of the RAM region to power down. This address is
 *   inclusive.
 *
 * @param[in] end
 *   The end address of the RAM region to power down. This address is
 *   exclusive. If this parameter is 0, all RAM blocks contained in the
 *   region from start to the upper RAM address will be powered down.
 ******************************************************************************/
void EMU_RamPowerDown(uint32_t start, uint32_t end)
{
  uint32_t mask = 0;
  (void) start;

  if (end == 0U) {
    end = SRAM_BASE + SRAM_SIZE;
  }

  // Check to see if something in RAM0 can be powered down.
  if (end > RAM0_END) {
#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_84) // EFM32xG12 and EFR32xG12
    // Block 0 is 16 kB and cannot be powered off.
    mask |= ADDRESS_NOT_IN_BLOCK(start, 0x20004000UL) << 0; // Block 1, 16 kB
    mask |= ADDRESS_NOT_IN_BLOCK(start, 0x20008000UL) << 1; // Block 2, 16 kB
    mask |= ADDRESS_NOT_IN_BLOCK(start, 0x2000C000UL) << 2; // Block 3, 16 kB
    mask |= ADDRESS_NOT_IN_BLOCK(start, 0x20010000UL) << 3; // Block 4, 64 kB
#elif defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80) // EFM32xG1 and EFR32xG1
    // Block 0 is 4 kB and cannot be powered off.
    mask |= ADDRESS_NOT_IN_BLOCK(start, 0x20001000UL) << 0; // Block 1, 4 kB
    mask |= ADDRESS_NOT_IN_BLOCK(start, 0x20002000UL) << 1; // Block 2, 8 kB
    mask |= ADDRESS_NOT_IN_BLOCK(start, 0x20004000UL) << 2; // Block 3, 8 kB
    mask |= ADDRESS_NOT_IN_BLOCK(start, 0x20006000UL) << 3; // Block 4, 7 kB
#elif defined(RAM0_BLOCKS)
    // These platforms have equally-sized RAM blocks.
    for (unsigned i = 1; i < RAM0_BLOCKS; i++) {
      mask |= ADDRESS_NOT_IN_BLOCK(start, RAM_MEM_BASE + (i * RAM0_BLOCK_SIZE)) << (i - 1U);
    }
#endif
  }

  // Power down the selected blocks.
#if defined(_EMU_MEMCTRL_MASK)
  EMU->MEMCTRL = EMU->MEMCTRL   | mask;
#elif defined(_EMU_RAM0CTRL_MASK)
  EMU->RAM0CTRL = EMU->RAM0CTRL | mask;
#elif defined(_SILICON_LABS_32B_SERIES_2)
#if defined(CMU_CLKEN0_SYSCFG)
  CMU->CLKEN0_SET = CMU_CLKEN0_SYSCFG;
#endif
#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)
  SYSCFG->DMEM0RETNCTRL = SYSCFG->DMEM0RETNCTRL | (mask << 1);
#else
  SYSCFG->DMEM0RETNCTRL = SYSCFG->DMEM0RETNCTRL | mask;
#endif
#else
  // These devices are unable to power down RAM blocks.
  (void) mask;
  (void) start;
#endif

#if defined(RAM1_MEM_END)
  mask = 0;
  if (end > RAM1_MEM_END) {
    for (unsigned i = 0; i < RAM1_BLOCKS; i++) {
      mask |= ADDRESS_NOT_IN_BLOCK(start, RAM1_MEM_BASE + (i * RAM1_BLOCK_SIZE)) << i;
    }
  }
  EMU->RAM1CTRL |= mask;
#endif

#if defined(RAM2_MEM_END)
  mask = 0;
  if (end > RAM2_MEM_END) {
    for (unsigned i = 0; i < RAM2_BLOCKS; i++) {
      mask |= ADDRESS_NOT_IN_BLOCK(start, RAM2_MEM_BASE + (i * RAM2_BLOCK_SIZE)) << i;
    }
  }
  EMU->RAM2CTRL |= mask;
#endif
}

/***************************************************************************//**
 * @brief
 *   Power up all available RAM memory blocks.
 *
 * @details
 *   This function will power up all the RAM blocks on a device, this means
 *   that the RAM blocks are retained in EM2/EM3. Note that this functionality
 *   is not supported on Series 0 devices. Only a reset will power up the RAM
 *   blocks on a series 0 device.
 ******************************************************************************/
void EMU_RamPowerUp(void)
{
#if defined(_EMU_RAM0CTRL_MASK)
  EMU->RAM0CTRL = 0x0UL;
#endif
#if defined(_EMU_RAM1CTRL_MASK)
  EMU->RAM1CTRL = 0x0UL;
#endif
#if defined(_EMU_RAM2CTRL_MASK)
  EMU->RAM2CTRL = 0x0UL;
#endif
#if defined(_SYSCFG_DMEM0RETNCTRL_MASK)
#if defined(CMU_CLKEN0_SYSCFG)
  CMU->CLKEN0_SET = CMU_CLKEN0_SYSCFG;
#endif
  SYSCFG->DMEM0RETNCTRL = 0x0UL;
#endif
}

#if defined(_EMU_EM23PERNORETAINCTRL_MASK)
/***************************************************************************//**
 * @brief
 *   Set EM2 3 peripheral retention control.
 *
 * @param[in] periMask
 *  A peripheral select mask. Use | operator to select multiple peripherals, for example
 *  @ref emuPeripheralRetention_LEUART0 | @ref emuPeripheralRetention_VDAC0.
 * @param[in] enable
 *  Peripheral retention enable (true) or disable (false).
 *
 *
 * @note
 *   Only peripheral retention disable is currently supported. Peripherals are
 *   enabled by default and can only be disabled.
 ******************************************************************************/
void EMU_PeripheralRetention(EMU_PeripheralRetention_TypeDef periMask, bool enable)
{
  EFM_ASSERT(!enable);
  EMU->EM23PERNORETAINCTRL = (uint32_t)periMask
                             & (uint32_t)emuPeripheralRetention_ALL;
}
#endif

/***************************************************************************//**
 * @brief
 *   Update EMU module with CMU oscillator selection/enable status.
 *
 * @deprecated
 *   Oscillator status is saved in @ref EMU_EnterEM2() and @ref EMU_EnterEM3().
 ******************************************************************************/
void EMU_UpdateOscConfig(void)
{
#if (_SILICON_LABS_32B_SERIES < 2)
  emState(emState_Save);
#endif
}

#if defined(_SILICON_LABS_32B_SERIES_2) && defined(EMU_VSCALE_EM01_PRESENT)
/***************************************************************************//**
 * @brief
 *   Energy mode 01 voltage scaling hook function.
 *
 * @param[in] voltage
 *   Voltage scaling level requested.
 *
 * @details
 *   This function is called by EMU_VScaleEM01 to let EFP know that voltage scaling
 *   is requested.
 ******************************************************************************/
SL_WEAK void EMU_EFPEM01VScale(EMU_VScaleEM01_TypeDef voltage)
{
  (void)voltage;
}
#endif

#if defined(EMU_VSCALE_EM01_PRESENT)
/***************************************************************************//**
 * @brief
 *   Voltage scale in EM0 and 1 by clock frequency.
 *
 * @param[in] clockFrequency
 *   Use CMSIS HF clock if 0 or override to custom clock. Providing a
 *   custom clock frequency is required if using a non-standard HFXO
 *   frequency.
 * @param[in] wait
 *   Wait for scaling to complete.
 *
 * @note
 *   This function is primarily needed by the @ref cmu.
 ******************************************************************************/
void EMU_VScaleEM01ByClock(uint32_t clockFrequency, bool wait)
{
  uint32_t hfSrcClockFrequency;

#if defined(_SILICON_LABS_32B_SERIES_1)
  if (EMU_LDOStatusGet() == false) {
    /* Skip voltage scaling if the LDO regulator is turned off. */
    return;
  }
#endif

  /* VSCALE frequency is HFSRCCLK. */
  if (clockFrequency == 0U) {
#if defined(_SILICON_LABS_32B_SERIES_2)
    hfSrcClockFrequency = SystemSYSCLKGet();
#else
    uint32_t hfPresc = 1U + ((CMU->HFPRESC & _CMU_HFPRESC_PRESC_MASK)
                             >> _CMU_HFPRESC_PRESC_SHIFT);
    hfSrcClockFrequency = SystemHFClockGet() * hfPresc;
#endif
  } else {
    hfSrcClockFrequency = clockFrequency;
  }

  /* Apply EM0 and 1 voltage scaling command. */
  if (vScaleEM01Config.vScaleEM01LowPowerVoltageEnable
      && (hfSrcClockFrequency <= CMU_VSCALEEM01_LOWPOWER_VOLTAGE_CLOCK_MAX)) {
    EMU_VScaleEM01(emuVScaleEM01_LowPower, wait);
  } else {
    EMU_VScaleEM01(emuVScaleEM01_HighPerformance, wait);
  }
}
#endif

#if defined(EMU_VSCALE_EM01_PRESENT)
/***************************************************************************//**
 * @brief
 *   Force voltage scaling in EM0 and 1 to a specific voltage level.
 *
 * @param[in] voltage
 *   Target VSCALE voltage level.
 * @param[in] wait
 *   Wait for scaling to complete.
 *
 * @note
 *   This function is useful for upscaling before programming Flash from @ref msc
 *   and downscaling after programming is done. Flash programming is only supported
 *   at @ref emuVScaleEM01_HighPerformance.
 *
 * @note
 *  This function ignores vScaleEM01LowPowerVoltageEnable set from @ref
 *  EMU_EM01Init().
 ******************************************************************************/
void EMU_VScaleEM01(EMU_VScaleEM01_TypeDef voltage, bool wait)
{
  uint32_t hfFreq;
  uint32_t hfSrcClockFrequency;

#if defined(_SILICON_LABS_32B_SERIES_1)
  if (EMU_LDOStatusGet() == false) {
    /* Skip voltage scaling if the LDO regulator is turned off. */
    return;
  }
#endif

  if (EMU_VScaleGet() == voltage) {
    /* Voltage is already at the correct level. */
    return;
  }

#if defined(_SILICON_LABS_32B_SERIES_2)
  (void)wait;
  CORE_DECLARE_IRQ_STATE;

  hfFreq = SystemSYSCLKGet();
  hfSrcClockFrequency = hfFreq;

  if (voltage == emuVScaleEM01_LowPower) {
    EFM_ASSERT(hfSrcClockFrequency <= CMU_VSCALEEM01_LOWPOWER_VOLTAGE_CLOCK_MAX);
    /* Update wait states before scaling down voltage. */
    CMU_UpdateWaitStates(hfFreq, VSCALE_EM01_LOW_POWER);
  }

  CORE_ENTER_CRITICAL();
  EMU->IF_CLR = EMU_IF_VSCALEDONE;
  EMU_EFPEM01VScale(voltage);
  EMU->CMD = vScaleEM01Cmd(voltage);

  // Note that VSCALEDONE interrupt flag must be used instead of VSCALEBUSY
  // because hardware does not set the VSCALEBUSY flag immediately.
  while (((EMU->IF & EMU_IF_VSCALEDONE) == 0U)
         && ((EMU->STATUS & EMU_STATUS_VSCALEFAILED) == 0U)) {
    EFM_ASSERT((EMU->STATUS & EMU_STATUS_VSCALEFAILED) == 0U);
    // Wait for VSCALE completion.
    // SRAM accesses will fault the core while scaling.
  }
  CORE_EXIT_CRITICAL();

#else
  uint32_t hfPresc = 1U + ((CMU->HFPRESC & _CMU_HFPRESC_PRESC_MASK)
                           >> _CMU_HFPRESC_PRESC_SHIFT);
  hfFreq = SystemHFClockGet();
  hfSrcClockFrequency = hfFreq * hfPresc;

  if (voltage == emuVScaleEM01_LowPower) {
    EFM_ASSERT(hfSrcClockFrequency <= CMU_VSCALEEM01_LOWPOWER_VOLTAGE_CLOCK_MAX);
    /* Update wait states before scaling down voltage. */
    CMU_UpdateWaitStates(hfFreq, VSCALE_EM01_LOW_POWER);
  }

  EMU->CMD = vScaleEM01Cmd(voltage);

  if (wait) {
    EMU_VScaleWait();
  }
#endif

  if (voltage == emuVScaleEM01_HighPerformance) {
    /* Update wait states after scaling up voltage. */
    CMU_UpdateWaitStates(hfFreq, VSCALE_EM01_HIGH_PERFORMANCE);
  }
}
#endif

#if defined(BU_PRESENT) && defined(_SILICON_LABS_32B_SERIES_0)
/***************************************************************************//**
 * @brief
 *   Configure Backup Power Domain settings.
 *
 * @param[in] bupdInit
 *   Backup power domain initialization structure.
 ******************************************************************************/
void EMU_BUPDInit(const EMU_BUPDInit_TypeDef *bupdInit)
{
  uint32_t reg;

  /* Set the power connection configuration. */
  reg = EMU->PWRCONF & ~(_EMU_PWRCONF_PWRRES_MASK
                         | _EMU_PWRCONF_VOUTSTRONG_MASK
                         | _EMU_PWRCONF_VOUTMED_MASK
                         | _EMU_PWRCONF_VOUTWEAK_MASK);

  reg |= bupdInit->resistor
         | (bupdInit->voutStrong << _EMU_PWRCONF_VOUTSTRONG_SHIFT)
         | (bupdInit->voutMed    << _EMU_PWRCONF_VOUTMED_SHIFT)
         | (bupdInit->voutWeak   << _EMU_PWRCONF_VOUTWEAK_SHIFT);

  EMU->PWRCONF = reg;

  /* Set the backup domain inactive mode configuration. */
  reg = EMU->BUINACT & ~(_EMU_BUINACT_PWRCON_MASK);
  reg |= (bupdInit->inactivePower);
  EMU->BUINACT = reg;

  /* Set the backup domain active mode configuration. */
  reg = EMU->BUACT & ~(_EMU_BUACT_PWRCON_MASK);
  reg |= (bupdInit->activePower);
  EMU->BUACT = reg;

  /* Set the power control configuration */
  reg = EMU->BUCTRL & ~(_EMU_BUCTRL_PROBE_MASK
                        | _EMU_BUCTRL_BODCAL_MASK
                        | _EMU_BUCTRL_STATEN_MASK
                        | _EMU_BUCTRL_EN_MASK);

  /* Note the use of ->enable to enable BUPD. Use BU_VIN pin input and
     release reset. */
  reg |= bupdInit->probe
         | (bupdInit->bodCal          << _EMU_BUCTRL_BODCAL_SHIFT)
         | (bupdInit->statusPinEnable << _EMU_BUCTRL_STATEN_SHIFT)
         | (bupdInit->enable          << _EMU_BUCTRL_EN_SHIFT);

  /* Enable configuration. */
  EMU->BUCTRL = reg;

  /* If enable is true, enable BU_VIN input power pin. If not, disable it.  */
  EMU_BUPinEnable(bupdInit->enable);

  /* If enable is true, release BU reset. If not, keep reset asserted. */
  BUS_RegBitWrite(&(RMU->CTRL), _RMU_CTRL_BURSTEN_SHIFT, !bupdInit->enable);
}

/***************************************************************************//**
 * @brief
 *   Configure the Backup Power Domain BOD Threshold value.
 * @note
 *   These values are precalibrated.
 * @param[in] mode Active or Inactive mode
 * @param[in] value
 ******************************************************************************/
void EMU_BUThresholdSet(EMU_BODMode_TypeDef mode, uint32_t value)
{
  EFM_ASSERT(value < 8);
  EFM_ASSERT(value <= (_EMU_BUACT_BUEXTHRES_MASK >> _EMU_BUACT_BUEXTHRES_SHIFT));

  switch (mode) {
    case emuBODMode_Active:
      EMU->BUACT = (EMU->BUACT & ~_EMU_BUACT_BUEXTHRES_MASK)
                   | (value << _EMU_BUACT_BUEXTHRES_SHIFT);
      break;
    case emuBODMode_Inactive:
      EMU->BUINACT = (EMU->BUINACT & ~_EMU_BUINACT_BUENTHRES_MASK)
                     | (value << _EMU_BUINACT_BUENTHRES_SHIFT);
      break;
  }
}

/***************************************************************************//**
 * @brief
 *  Configure the Backup Power Domain BOD Threshold Range.
 * @note
 *  These values are precalibrated.
 * @param[in] mode Active or Inactive mode
 * @param[in] value
 ******************************************************************************/
void EMU_BUThresRangeSet(EMU_BODMode_TypeDef mode, uint32_t value)
{
  EFM_ASSERT(value < 4);
  EFM_ASSERT(value <= (_EMU_BUACT_BUEXRANGE_MASK >> _EMU_BUACT_BUEXRANGE_SHIFT));

  switch (mode) {
    case emuBODMode_Active:
      EMU->BUACT = (EMU->BUACT & ~_EMU_BUACT_BUEXRANGE_MASK)
                   | (value << _EMU_BUACT_BUEXRANGE_SHIFT);
      break;
    case emuBODMode_Inactive:
      EMU->BUINACT = (EMU->BUINACT & ~_EMU_BUINACT_BUENRANGE_MASK)
                     | (value << _EMU_BUINACT_BUENRANGE_SHIFT);
      break;
  }
}
#endif

#if defined(BU_PRESENT) && defined(_SILICON_LABS_32B_SERIES_1)
/***************************************************************************//**
 * @brief
 *   Configure Backup Power Domain settings.
 *
 * @param[in] buInit
 *   Backup power domain initialization structure.
 ******************************************************************************/
void EMU_BUInit(const EMU_BUInit_TypeDef *buInit)
{
  uint32_t reg = 0;

  /* Set the backup power configuration. */
  reg |= (buInit->disMaxComp << _EMU_BUCTRL_DISMAXCOMP_SHIFT);
  reg |= (uint32_t)(buInit->inactivePwrCon);
  reg |= (uint32_t)(buInit->activePwrCon);
  reg |= (uint32_t)(buInit->pwrRes);
  reg |= (uint32_t)(buInit->voutRes);
  reg |= (buInit->buVinProbeEn << _EMU_BUCTRL_BUVINPROBEEN_SHIFT);
  reg |= (buInit->staEn << _EMU_BUCTRL_STATEN_SHIFT);
  reg |= (buInit->enable << _EMU_BUCTRL_EN_SHIFT);
  EMU->BUCTRL = reg;
}
#endif

#if defined(_EMU_BUCTRL_DISMAXCOMP_MASK)
/***************************************************************************//**
 * @brief
 *   Disable Main Backup Power Domain comparator.
 *
 * @param[in] disableMainBuComparator
 *   True to disable main BU comparator.
 ******************************************************************************/
void EMU_BUDisMaxCompSet(bool disableMainBuComparator)
{
  uint32_t reg;

  reg = EMU->BUCTRL & ~(_EMU_BUCTRL_DISMAXCOMP_MASK);
  reg |= (disableMainBuComparator << _EMU_BUCTRL_DISMAXCOMP_SHIFT);
  EMU->BUCTRL = reg;
}
#endif

#if defined(_EMU_BUCTRL_BUINACTPWRCON_MASK)
/***************************************************************************//**
 * @brief
 *   Configure power connection configuration when not in Backup mode.
 *
 * @param[in] inactPwrCon
 *   Inactive power configuration.
 ******************************************************************************/
void EMU_BUBuInactPwrConSet(EMU_BUBuInactPwrCon_TypeDef inactPwrCon)
{
  uint32_t reg;

  reg = EMU->BUCTRL & ~(_EMU_BUCTRL_BUINACTPWRCON_MASK);
  reg |= (uint32_t)(inactPwrCon);
  EMU->BUCTRL = reg;
}
#endif

#if defined(_EMU_BUCTRL_BUACTPWRCON_MASK)
/***************************************************************************//**
 * @brief
 *   Configure power connection configuration when in Backup mode.
 *
 * @param[in] actPwrCon
 *   Active power configuration.
 ******************************************************************************/
void EMU_BUBuActPwrConSet(EMU_BUBuActPwrCon_TypeDef actPwrCon)
{
  uint32_t reg;

  reg = EMU->BUCTRL & ~(_EMU_BUCTRL_BUACTPWRCON_MASK);
  reg |= (uint32_t)(actPwrCon);
  EMU->BUCTRL = reg;
}
#endif

#if defined(_EMU_BUCTRL_PWRRES_MASK)
/***************************************************************************//**
 * @brief
 *   Power domain resistor selection.
 *
 * @param[in] pwrRes
 *   Resistor selection.
 ******************************************************************************/
void EMU_BUPwrResSet(EMU_BUPwrRes_TypeDef pwrRes)
{
  uint32_t reg;

  reg = EMU->BUCTRL & ~(_EMU_BUCTRL_PWRRES_MASK);
  reg |= (uint32_t)(pwrRes);
  EMU->BUCTRL = reg;
}
#endif

#if defined(_EMU_BUCTRL_VOUTRES_MASK)
/***************************************************************************//**
 * @brief
 *   B_VOUT resistor select.
 *
 * @param[in] resistorSel
 *   Resistor selection.
 ******************************************************************************/
void EMU_BUVoutResSet(EMU_BUVoutRes_TypeDef resistorSel)
{
  uint32_t reg;

  reg = EMU->BUCTRL & ~(_EMU_BUCTRL_VOUTRES_MASK);
  reg |= (uint32_t)(resistorSel);
  EMU->BUCTRL = reg;
}
#endif

#if defined(_EMU_BUCTRL_BUVINPROBEEN_MASK)
/***************************************************************************//**
 * @brief
 *   Enable BU_VIN probing
 *
 * @param[in] enable
 *   True to enable BU_VIN probing. False to disable.
 ******************************************************************************/
void EMU_BUBuVinProbeEnSet(bool enable)
{
  uint32_t reg;

  reg = EMU->BUCTRL & ~(_EMU_BUCTRL_BUVINPROBEEN_MASK);
  reg |= (enable << _EMU_BUCTRL_BUVINPROBEEN_SHIFT);
  EMU->BUCTRL = reg;
}
#endif

#if defined(_EMU_BUCTRL_STATEN_MASK)
/***************************************************************************//**
 * @brief
 *   Enable backup mode status export.
 *
 * @param[in] enable
 *   True to enable status export. False to disable.
 ******************************************************************************/
void EMU_BUStatEnSet(bool enable)
{
  uint32_t reg;

  reg = EMU->BUCTRL & ~(_EMU_BUCTRL_STATEN_MASK);
  reg |= (enable << _EMU_BUCTRL_STATEN_SHIFT);
  EMU->BUCTRL = reg;
}
#endif

#if defined(_EMU_BUCTRL_EN_MASK)
/***************************************************************************//**
 * @brief
 *   Enable backup mode.
 *
 * @param[in] enable
 *   True to enable backup mode. False to disable.
 ******************************************************************************/
void EMU_BUEnableSet(bool enable)
{
  uint32_t reg;

  reg = EMU->BUCTRL & ~(_EMU_BUCTRL_EN_MASK);
  reg |= (enable << _EMU_BUCTRL_EN_SHIFT);
  EMU->BUCTRL = reg;
}
#endif

#if defined(_EMU_DCDCCTRL_MASK)
/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
/* Internal DCDC trim modes. */
typedef enum {
  dcdcTrimMode_EM234H_LP = 0,
#if defined(_EMU_DCDCLPEM01CFG_LPCMPBIASEM01_MASK)
  dcdcTrimMode_EM01_LP,
#endif
  dcdcTrimMode_LN,
} dcdcTrimMode_TypeDef;

/** @endcond */

/***************************************************************************//**
 * @brief
 *   Load DCDC calibration constants from the DI page. A constant means that calibration
 *   data that does not change depending on other configuration parameters.
 *
 * @return
 *   False if calibration registers are locked.
 ******************************************************************************/
static bool dcdcConstCalibrationLoad(void)
{
#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80)
  uint32_t val;
  volatile uint32_t *reg;

  /* DI calibration data in Flash. */
  volatile uint32_t* const diCal_EMU_DCDCLNFREQCTRL =  (volatile uint32_t *)(0x0FE08038);
  volatile uint32_t* const diCal_EMU_DCDCLNVCTRL =     (volatile uint32_t *)(0x0FE08040);
  volatile uint32_t* const diCal_EMU_DCDCLPCTRL =      (volatile uint32_t *)(0x0FE08048);
  volatile uint32_t* const diCal_EMU_DCDCLPVCTRL =     (volatile uint32_t *)(0x0FE08050);
  volatile uint32_t* const diCal_EMU_DCDCTRIM0 =       (volatile uint32_t *)(0x0FE08058);
  volatile uint32_t* const diCal_EMU_DCDCTRIM1 =       (volatile uint32_t *)(0x0FE08060);

  if (DEVINFO->DCDCLPVCTRL0 != UINT_MAX) {
    val = *(diCal_EMU_DCDCLNFREQCTRL + 1);
    reg = (volatile uint32_t *)*diCal_EMU_DCDCLNFREQCTRL;
    *reg = val;

    val = *(diCal_EMU_DCDCLNVCTRL + 1);
    reg = (volatile uint32_t *)*diCal_EMU_DCDCLNVCTRL;
    *reg = val;

    val = *(diCal_EMU_DCDCLPCTRL + 1);
    reg = (volatile uint32_t *)*diCal_EMU_DCDCLPCTRL;
    *reg = val;

    val = *(diCal_EMU_DCDCLPVCTRL + 1);
    reg = (volatile uint32_t *)*diCal_EMU_DCDCLPVCTRL;
    *reg = val;

    val = *(diCal_EMU_DCDCTRIM0 + 1);
    reg = (volatile uint32_t *)*diCal_EMU_DCDCTRIM0;
    *reg = val;

    val = *(diCal_EMU_DCDCTRIM1 + 1);
    reg = (volatile uint32_t *)*diCal_EMU_DCDCTRIM1;
    *reg = val;

    return true;
  }
  EFM_ASSERT(false);
  /* Return when assertions are disabled. */
  return false;

#else
  return true;
#endif
}

/***************************************************************************//**
 * @brief
 *   Set recommended and validated current optimization and timing settings.
 *
 ******************************************************************************/
static void dcdcValidatedConfigSet(void)
{
  uint32_t lnForceCcm;

#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80)
  uint32_t dcdcTiming;
  SYSTEM_ChipRevision_TypeDef rev;
#endif

  /* Enable duty cycling of the bias. */
  EMU->DCDCLPCTRL |= EMU_DCDCLPCTRL_LPVREFDUTYEN;

  /* Set low-noise RCO for LNFORCECCM configuration.
   * LNFORCECCM is default 1 for EFR32
   * LNFORCECCM is default 0 for EFM32
   */
  lnForceCcm = BUS_RegBitRead(&EMU->DCDCMISCCTRL, _EMU_DCDCMISCCTRL_LNFORCECCM_SHIFT);
  if (lnForceCcm != 0U) {
    /* 7 MHz is recommended for LNFORCECCM = 1. */
    EMU_DCDCLnRcoBandSet(emuDcdcLnRcoBand_7MHz);
  } else {
    /* 3 MHz is recommended for LNFORCECCM = 0. */
    EMU_DCDCLnRcoBandSet(emuDcdcLnRcoBand_3MHz);
  }

#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80)
  EMU->DCDCTIMING &= ~_EMU_DCDCTIMING_DUTYSCALE_MASK;
  EMU->DCDCMISCCTRL |= EMU_DCDCMISCCTRL_LPCMPHYSDIS
                       | EMU_DCDCMISCCTRL_LPCMPHYSHI;

  SYSTEM_ChipRevisionGet(&rev);
  if ((rev.major == 1)
      && (rev.minor < 3)
      && (errataFixDcdcHsState == errataFixDcdcHsInit)) {
    /* LPCMPWAITDIS = 1 */
    EMU_DCDCSMCTRL |= 1;

    dcdcTiming = EMU->DCDCTIMING;
    dcdcTiming &= ~(_EMU_DCDCTIMING_LPINITWAIT_MASK
                    | _EMU_DCDCTIMING_LNWAIT_MASK
                    | _EMU_DCDCTIMING_BYPWAIT_MASK);

    dcdcTiming |= ((180 << _EMU_DCDCTIMING_LPINITWAIT_SHIFT)
                   | (12 << _EMU_DCDCTIMING_LNWAIT_SHIFT)
                   | (180 << _EMU_DCDCTIMING_BYPWAIT_SHIFT));
    EMU->DCDCTIMING = dcdcTiming;

    errataFixDcdcHsState = errataFixDcdcHsTrimSet;
  }
#endif
}

/***************************************************************************//**
 * @brief
 *   Compute current limiters:
 *     LNCLIMILIMSEL: LN current limiter threshold
 *     LPCLIMILIMSEL: LP current limiter threshold
 *     DCDCZDETCTRL:  zero detector limiter threshold
 ******************************************************************************/
static void currentLimitersUpdate(void)
{
  uint32_t lncLimSel;
  uint32_t zdetLimSel;
  uint32_t pFetCnt;
  uint16_t maxReverseCurrent_mA;

  /* 80 mA as recommended peak in Application Note AN0948.
     The peak current is the average current plus 50% of the current ripple.
     Hence, a 14 mA average current is recommended in LP mode. Since LP PFETCNT is also
     a constant, lpcLimImSel = 1. The following calculation is provided
     for documentation only. */
  const uint32_t lpcLim = (((14 + 40) + ((14 + 40) / 2))
                           / (5 * (DCDC_LP_PFET_CNT + 1)))
                          - 1;
  const uint32_t lpcLimSel = lpcLim << _EMU_DCDCMISCCTRL_LPCLIMILIMSEL_SHIFT;

  /* Get enabled PFETs. */
  pFetCnt = (EMU->DCDCMISCCTRL & _EMU_DCDCMISCCTRL_PFETCNT_MASK)
            >> _EMU_DCDCMISCCTRL_PFETCNT_SHIFT;

  /* Compute the LN current limiter threshold from the nominal user input current and
     LN PFETCNT as described in the register description for
     EMU_DCDCMISCCTRL_LNCLIMILIMSEL. */
  lncLimSel = ((((uint32_t)dcdcMaxCurrent_mA + 40U)
                + (((uint32_t)dcdcMaxCurrent_mA + 40U) / 2U))
               / (5U * (pFetCnt + 1U)))
              - 1U;

  /* Saturate the register field value. */
  lncLimSel = SL_MIN(lncLimSel,
                     _EMU_DCDCMISCCTRL_LNCLIMILIMSEL_MASK
                     >> _EMU_DCDCMISCCTRL_LNCLIMILIMSEL_SHIFT);

  lncLimSel <<= _EMU_DCDCMISCCTRL_LNCLIMILIMSEL_SHIFT;

  /* Check for overflow. */
  EFM_ASSERT((lncLimSel & ~_EMU_DCDCMISCCTRL_LNCLIMILIMSEL_MASK) == 0x0U);
  EFM_ASSERT((lpcLimSel & ~_EMU_DCDCMISCCTRL_LPCLIMILIMSEL_MASK) == 0x0U);

  EMU->DCDCMISCCTRL = (EMU->DCDCMISCCTRL & ~(_EMU_DCDCMISCCTRL_LNCLIMILIMSEL_MASK
                                             | _EMU_DCDCMISCCTRL_LPCLIMILIMSEL_MASK))
                      | (lncLimSel | lpcLimSel);

  /* Compute the reverse current limit threshold for the zero detector from the user input
     maximum reverse current and LN PFETCNT as described in the register description
     for EMU_DCDCZDETCTRL_ZDETILIMSEL. */
  if (dcdcReverseCurrentControl >= 0) {
    /* If dcdcReverseCurrentControl < 0, EMU_DCDCZDETCTRL_ZDETILIMSEL is "don't care". */
    maxReverseCurrent_mA = (uint16_t)dcdcReverseCurrentControl;

    zdetLimSel = ((((uint32_t)maxReverseCurrent_mA + 40U)
                   + (((uint32_t)maxReverseCurrent_mA + 40U) / 2U))
                  / ((2U * (pFetCnt + 1U)) + ((pFetCnt + 1U) / 2U)));
    /* Saturate the register field value. */
    zdetLimSel = SL_MIN(zdetLimSel,
                        _EMU_DCDCZDETCTRL_ZDETILIMSEL_MASK
                        >> _EMU_DCDCZDETCTRL_ZDETILIMSEL_SHIFT);

    zdetLimSel <<= _EMU_DCDCZDETCTRL_ZDETILIMSEL_SHIFT;

    /* Check for overflow. */
    EFM_ASSERT((zdetLimSel & ~_EMU_DCDCZDETCTRL_ZDETILIMSEL_MASK) == 0x0U);

    EMU->DCDCZDETCTRL = (EMU->DCDCZDETCTRL & ~_EMU_DCDCZDETCTRL_ZDETILIMSEL_MASK)
                        | zdetLimSel;
  }
}

/***************************************************************************//**
 * @brief
 *   Set static variables that hold the user set maximum peak current
 *   and reverse current. Update limiters.
 *
 * @param[in] maxCurrent_mA
 *   Set the maximum peak current that the DCDC can draw from the power source.
 * @param[in] reverseCurrentControl
 *   Reverse the current control as defined by
 *   @ref EMU_DcdcLnReverseCurrentControl_TypeDef. Positive values have unit mA.
 ******************************************************************************/
static void userCurrentLimitsSet(uint32_t maxCurrent_mA,
                                 EMU_DcdcLnReverseCurrentControl_TypeDef reverseCurrentControl)
{
  dcdcMaxCurrent_mA = (uint16_t)maxCurrent_mA;
  dcdcReverseCurrentControl = reverseCurrentControl;
}

/***************************************************************************//**
 * @brief
 *   Set DCDC low noise compensator control register.
 *
 * @param[in] comp
 *   Low-noise mode compensator trim setpoint.
 ******************************************************************************/
static void compCtrlSet(EMU_DcdcLnCompCtrl_TypeDef comp)
{
  switch (comp) {
    case emuDcdcLnCompCtrl_1u0F:
      EMU->DCDCLNCOMPCTRL = 0x57204077UL;
      break;

    case emuDcdcLnCompCtrl_4u7F:
      EMU->DCDCLNCOMPCTRL = 0xB7102137UL;
      break;

    default:
      EFM_ASSERT(false);
      break;
  }
}

/***************************************************************************//**
 * @brief
 *   Load EMU_DCDCLPCTRL_LPCMPHYSSEL depending on LP bias, LP feedback
 *   attenuation, and DEVINFOREV.
 *
 * @param[in] lpAttenuation
 *   LP feedback attenuation.
 * @param[in] lpCmpBias
 *   lpCmpBias selection.
 * @param[in] trimMode
 *   DCDC trim mode.
 ******************************************************************************/
static bool lpCmpHystCalibrationLoad(bool lpAttenuation,
                                     uint8_t lpCmpBias,
                                     dcdcTrimMode_TypeDef trimMode)
{
  uint32_t lpcmpHystSel;
#if !defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80)
  (void)lpAttenuation;
#endif

  /* Get calibration data revision. */
#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80)
  uint8_t devinfoRev = SYSTEM_GetDevinfoRev();

  /* Load LPATT indexed calibration data. */
  if (devinfoRev < 4) {
    lpcmpHystSel = DEVINFO->DCDCLPCMPHYSSEL0;

    if (lpAttenuation) {
      lpcmpHystSel = (lpcmpHystSel & _DEVINFO_DCDCLPCMPHYSSEL0_LPCMPHYSSELLPATT1_MASK)
                     >> _DEVINFO_DCDCLPCMPHYSSEL0_LPCMPHYSSELLPATT1_SHIFT;
    } else {
      lpcmpHystSel = (lpcmpHystSel & _DEVINFO_DCDCLPCMPHYSSEL0_LPCMPHYSSELLPATT0_MASK)
                     >> _DEVINFO_DCDCLPCMPHYSSEL0_LPCMPHYSSELLPATT0_SHIFT;
    }
  } else
#endif
  {
    /* devinfoRev >= 4: load LPCMPBIAS indexed calibration data. */
    lpcmpHystSel = DEVINFO->DCDCLPCMPHYSSEL1;
    switch (lpCmpBias) {
      case 0:
        lpcmpHystSel = (lpcmpHystSel & _DEVINFO_DCDCLPCMPHYSSEL1_LPCMPHYSSELLPCMPBIAS0_MASK)
                       >> _DEVINFO_DCDCLPCMPHYSSEL1_LPCMPHYSSELLPCMPBIAS0_SHIFT;
        break;

      case 1:
        lpcmpHystSel = (lpcmpHystSel & _DEVINFO_DCDCLPCMPHYSSEL1_LPCMPHYSSELLPCMPBIAS1_MASK)
                       >> _DEVINFO_DCDCLPCMPHYSSEL1_LPCMPHYSSELLPCMPBIAS1_SHIFT;
        break;

      case 2:
        lpcmpHystSel = (lpcmpHystSel & _DEVINFO_DCDCLPCMPHYSSEL1_LPCMPHYSSELLPCMPBIAS2_MASK)
                       >> _DEVINFO_DCDCLPCMPHYSSEL1_LPCMPHYSSELLPCMPBIAS2_SHIFT;
        break;

      case 3:
        lpcmpHystSel = (lpcmpHystSel & _DEVINFO_DCDCLPCMPHYSSEL1_LPCMPHYSSELLPCMPBIAS3_MASK)
                       >> _DEVINFO_DCDCLPCMPHYSSEL1_LPCMPHYSSELLPCMPBIAS3_SHIFT;
        break;

      default:
        EFM_ASSERT(false);
        /* Return when assertions are disabled. */
        return false;
    }
  }

  /* Set trims. */
  if (trimMode == dcdcTrimMode_EM234H_LP) {
    /* Make sure the sel value is within the field range. */
    lpcmpHystSel <<= _GENERIC_DCDCLPCTRL_LPCMPHYSSELEM234H_SHIFT;
    if ((lpcmpHystSel & ~_GENERIC_DCDCLPCTRL_LPCMPHYSSELEM234H_MASK) != 0U) {
      EFM_ASSERT(false);
      /* Return when assertions are disabled. */
      return false;
    }
    EMU->DCDCLPCTRL = (EMU->DCDCLPCTRL & ~_GENERIC_DCDCLPCTRL_LPCMPHYSSELEM234H_MASK) | lpcmpHystSel;
  }

#if defined(_EMU_DCDCLPEM01CFG_LPCMPHYSSELEM01_MASK)
  if (trimMode == dcdcTrimMode_EM01_LP) {
    /* Make sure the sel value is within the field range. */
    lpcmpHystSel <<= _EMU_DCDCLPEM01CFG_LPCMPHYSSELEM01_SHIFT;
    if ((lpcmpHystSel & ~_EMU_DCDCLPEM01CFG_LPCMPHYSSELEM01_MASK) != 0U) {
      EFM_ASSERT(false);
      /* Return when assertions are disabled. */
      return false;
    }
    EMU->DCDCLPEM01CFG = (EMU->DCDCLPEM01CFG & ~_EMU_DCDCLPEM01CFG_LPCMPHYSSELEM01_MASK) | lpcmpHystSel;
  }
#endif

  return true;
}

/***************************************************************************//**
 * @brief
 *   Load LPVREF low and high from DEVINFO.
 *
 * @param[out] vrefL
 *   LPVREF low from DEVINFO.
 * @param[out] vrefH
 *   LPVREF high from DEVINFO.
 * @param[in] lpAttenuation
 *   LP feedback attenuation.
 * @param[in] lpcmpBias
 *   lpcmpBias to look up in DEVINFO.
 ******************************************************************************/
static void lpGetDevinfoVrefLowHigh(uint32_t *vrefL,
                                    uint32_t *vrefH,
                                    bool lpAttenuation,
                                    uint8_t lpcmpBias)
{
  uint32_t vrefLow = 0;
  uint32_t vrefHigh = 0;

  /* Find VREF high and low in DEVINFO indexed by LPCMPBIAS (lpcmpBias)
     and LPATT (lpAttenuation) */
  uint32_t switchVal = ((uint32_t)lpcmpBias << 8) | (lpAttenuation ? 1U : 0U);
  switch (switchVal) {
    case ((0 << 8) | 1):
      vrefLow  = DEVINFO->DCDCLPVCTRL2;
      vrefHigh = (vrefLow & _DEVINFO_DCDCLPVCTRL2_3V0LPATT1LPCMPBIAS0_MASK)
                 >> _DEVINFO_DCDCLPVCTRL2_3V0LPATT1LPCMPBIAS0_SHIFT;
      vrefLow  = (vrefLow & _DEVINFO_DCDCLPVCTRL2_1V8LPATT1LPCMPBIAS0_MASK)
                 >> _DEVINFO_DCDCLPVCTRL2_1V8LPATT1LPCMPBIAS0_SHIFT;
      break;

    case ((1 << 8) | 1):
      vrefLow  = DEVINFO->DCDCLPVCTRL2;
      vrefHigh = (vrefLow & _DEVINFO_DCDCLPVCTRL2_3V0LPATT1LPCMPBIAS1_MASK)
                 >> _DEVINFO_DCDCLPVCTRL2_3V0LPATT1LPCMPBIAS1_SHIFT;
      vrefLow  = (vrefLow & _DEVINFO_DCDCLPVCTRL2_1V8LPATT1LPCMPBIAS1_MASK)
                 >> _DEVINFO_DCDCLPVCTRL2_1V8LPATT1LPCMPBIAS1_SHIFT;
      break;

    case ((2 << 8) | 1):
      vrefLow  = DEVINFO->DCDCLPVCTRL3;
      vrefHigh = (vrefLow & _DEVINFO_DCDCLPVCTRL3_3V0LPATT1LPCMPBIAS2_MASK)
                 >> _DEVINFO_DCDCLPVCTRL3_3V0LPATT1LPCMPBIAS2_SHIFT;
      vrefLow  = (vrefLow & _DEVINFO_DCDCLPVCTRL3_1V8LPATT1LPCMPBIAS2_MASK)
                 >> _DEVINFO_DCDCLPVCTRL3_1V8LPATT1LPCMPBIAS2_SHIFT;
      break;

    case ((3 << 8) | 1):
      vrefLow  = DEVINFO->DCDCLPVCTRL3;
      vrefHigh = (vrefLow & _DEVINFO_DCDCLPVCTRL3_3V0LPATT1LPCMPBIAS3_MASK)
                 >> _DEVINFO_DCDCLPVCTRL3_3V0LPATT1LPCMPBIAS3_SHIFT;
      vrefLow  = (vrefLow & _DEVINFO_DCDCLPVCTRL3_1V8LPATT1LPCMPBIAS3_MASK)
                 >> _DEVINFO_DCDCLPVCTRL3_1V8LPATT1LPCMPBIAS3_SHIFT;
      break;

    case ((0 << 8) | 0):
      vrefLow  = DEVINFO->DCDCLPVCTRL0;
      vrefHigh = (vrefLow & _DEVINFO_DCDCLPVCTRL0_1V8LPATT0LPCMPBIAS0_MASK)
                 >> _DEVINFO_DCDCLPVCTRL0_1V8LPATT0LPCMPBIAS0_SHIFT;
      vrefLow  = (vrefLow & _DEVINFO_DCDCLPVCTRL0_1V2LPATT0LPCMPBIAS0_MASK)
                 >> _DEVINFO_DCDCLPVCTRL0_1V2LPATT0LPCMPBIAS0_SHIFT;
      break;

    case ((1 << 8) | 0):
      vrefLow  = DEVINFO->DCDCLPVCTRL0;
      vrefHigh = (vrefLow & _DEVINFO_DCDCLPVCTRL0_1V8LPATT0LPCMPBIAS1_MASK)
                 >> _DEVINFO_DCDCLPVCTRL0_1V8LPATT0LPCMPBIAS1_SHIFT;
      vrefLow  = (vrefLow & _DEVINFO_DCDCLPVCTRL0_1V2LPATT0LPCMPBIAS1_MASK)
                 >> _DEVINFO_DCDCLPVCTRL0_1V2LPATT0LPCMPBIAS1_SHIFT;
      break;

    case ((2 << 8) | 0):
      vrefLow  = DEVINFO->DCDCLPVCTRL1;
      vrefHigh = (vrefLow & _DEVINFO_DCDCLPVCTRL1_1V8LPATT0LPCMPBIAS2_MASK)
                 >> _DEVINFO_DCDCLPVCTRL1_1V8LPATT0LPCMPBIAS2_SHIFT;
      vrefLow  = (vrefLow & _DEVINFO_DCDCLPVCTRL1_1V2LPATT0LPCMPBIAS2_MASK)
                 >> _DEVINFO_DCDCLPVCTRL1_1V2LPATT0LPCMPBIAS2_SHIFT;
      break;

    case ((3 << 8) | 0):
      vrefLow  = DEVINFO->DCDCLPVCTRL1;
      vrefHigh = (vrefLow & _DEVINFO_DCDCLPVCTRL1_1V8LPATT0LPCMPBIAS3_MASK)
                 >> _DEVINFO_DCDCLPVCTRL1_1V8LPATT0LPCMPBIAS3_SHIFT;
      vrefLow  = (vrefLow & _DEVINFO_DCDCLPVCTRL1_1V2LPATT0LPCMPBIAS3_MASK)
                 >> _DEVINFO_DCDCLPVCTRL1_1V2LPATT0LPCMPBIAS3_SHIFT;
      break;

    default:
      EFM_ASSERT(false);
      break;
  }
  *vrefL = vrefLow;
  *vrefH = vrefHigh;
}

/***************************************************************************//**
 * @brief
 *   Configure the DCDC regulator.
 *
 * @note
 * Do not call this function if the power circuit is configured for NODCDC as
 * described in the Power Configurations section of the Reference Manual.
 * Instead, call @ref EMU_DCDCPowerOff().
 *
 * @param[in] dcdcInit
 *  The DCDC initialization structure.
 *
 * @return
 *   True if initialization parameters are valid.
 ******************************************************************************/
bool EMU_DCDCInit(const EMU_DCDCInit_TypeDef *dcdcInit)
{
  uint32_t lpCmpBiasSelEM234H;

#if defined(_EMU_PWRCFG_MASK)
  /* Set the external power configuration. This enables writing to the other
     DCDC registers. */
  EMU->PWRCFG = EMU_PWRCFG_PWRCFG_DCDCTODVDD;

  /* EMU->PWRCFG is write-once and POR reset only. Check that
     the desired power configuration was set. */
  if ((EMU->PWRCFG & _EMU_PWRCFG_PWRCFG_MASK) != EMU_PWRCFG_PWRCFG_DCDCTODVDD) {
    /* If this assert triggers unexpectedly, power cycle the
       kit to reset the power configuration. */
    EFM_ASSERT(false);
    /* Return when assertions are disabled. */
    return false;
  }
#endif

  /* Load DCDC calibration data from the DI page. */
  (void)dcdcConstCalibrationLoad();

  /* Check current parameters */
  EFM_ASSERT(dcdcInit->maxCurrent_mA <= 200U);
  EFM_ASSERT(dcdcInit->em01LoadCurrent_mA <= dcdcInit->maxCurrent_mA);
  EFM_ASSERT(dcdcInit->reverseCurrentControl <= 200);

  if (dcdcInit->dcdcMode == emuDcdcMode_LowNoise) {
    /* DCDC low-noise supports max 200 mA. */
    EFM_ASSERT(dcdcInit->em01LoadCurrent_mA <= 200U);
  }
#if (_SILICON_LABS_GECKO_INTERNAL_SDID != 80)
  else if (dcdcInit->dcdcMode == emuDcdcMode_LowPower) {
    /* Up to 10 mA is supported for EM01-LP mode. */
    EFM_ASSERT(dcdcInit->em01LoadCurrent_mA <= 10U);
  }
#endif
  else {
    /* No need to check the EM01 load limit. */
  }

  /* EM2/3/4 current above 10 mA is not supported. */
  EFM_ASSERT(dcdcInit->em234LoadCurrent_uA <= 10000U);

  if (dcdcInit->em234LoadCurrent_uA < 75U) {
    lpCmpBiasSelEM234H  = 0;
  } else if (dcdcInit->em234LoadCurrent_uA < 500U) {
    lpCmpBiasSelEM234H  = 1U << _GENERIC_DCDCMISCCTRL_LPCMPBIASEM234H_SHIFT;
  } else if (dcdcInit->em234LoadCurrent_uA < 2500U) {
    lpCmpBiasSelEM234H  = 2U << _GENERIC_DCDCMISCCTRL_LPCMPBIASEM234H_SHIFT;
  } else {
    lpCmpBiasSelEM234H  = 3U << _GENERIC_DCDCMISCCTRL_LPCMPBIASEM234H_SHIFT;
  }

  /* ==== THESE NEXT STEPS ARE STRONGLY ORDER DEPENDENT ==== */

  /* Set DCDC low-power mode comparator bias selection. */

  /* 1. Set DCDC low-power mode comparator bias selection and forced CCM.
        => Updates DCDCMISCCTRL_LNFORCECCM */
  EMU->DCDCMISCCTRL = (EMU->DCDCMISCCTRL & ~(_GENERIC_DCDCMISCCTRL_LPCMPBIASEM234H_MASK
                                             | _EMU_DCDCMISCCTRL_LNFORCECCM_MASK))
                      | ((uint32_t)lpCmpBiasSelEM234H
                         | (dcdcInit->reverseCurrentControl >= 0
                            ? EMU_DCDCMISCCTRL_LNFORCECCM : 0U));
#if defined(_EMU_DCDCLPEM01CFG_LPCMPBIASEM01_MASK)
  /* Only 10 mA EM01-LP current is supported. */
  EMU->DCDCLPEM01CFG = (EMU->DCDCLPEM01CFG & ~_EMU_DCDCLPEM01CFG_LPCMPBIASEM01_MASK)
                       | EMU_DCDCLPEM01CFG_LPCMPBIASEM01_BIAS3;
#endif

  /* 2. Set recommended and validated current optimization settings.
        <= Depends on LNFORCECCM
        => Updates DCDCLNFREQCTRL_RCOBAND */
  dcdcEm01LoadCurrent_mA = dcdcInit->em01LoadCurrent_mA;
  dcdcValidatedConfigSet();

  /* 3. Updated static currents and limits user data.
        Limiters are updated in @ref EMU_DCDCOptimizeSlice(). */
  userCurrentLimitsSet(dcdcInit->maxCurrent_mA,
                       dcdcInit->reverseCurrentControl);

  /* 4. Optimize LN slice based on the given user input load current.
        <= Depends on DCDCMISCCTRL_LNFORCECCM and DCDCLNFREQCTRL_RCOBAND
        <= Depends on dcdcInit->maxCurrent_mA and dcdcInit->reverseCurrentControl
        => Updates DCDCMISCCTRL_P/NFETCNT
        => Updates DCDCMISCCTRL_LNCLIMILIMSEL and DCDCMISCCTRL_LPCLIMILIMSEL
        => Updates DCDCZDETCTRL_ZDETILIMSEL */
  EMU_DCDCOptimizeSlice(dcdcInit->em01LoadCurrent_mA);

  /* ======================================================= */

  /* Set DCDC low noise mode compensator control register. */
  compCtrlSet(dcdcInit->dcdcLnCompCtrl);

  /* Set DCDC output voltage. */
  if (!EMU_DCDCOutputVoltageSet(dcdcInit->mVout, true, true)) {
    EFM_ASSERT(false);
    /* Return when assertions are disabled. */
    return false;
  }

#if (_SILICON_LABS_GECKO_INTERNAL_SDID == 80)
  /* Select analog peripheral power supply. This must be done before
     DCDC mode is set for all EFM32xG1 and EFR32xG1 devices. */
  BUS_RegBitWrite(&EMU->PWRCTRL,
                  _EMU_PWRCTRL_ANASW_SHIFT,
                  dcdcInit->anaPeripheralPower ? 1 : 0);
#endif

#if defined(_EMU_PWRCTRL_REGPWRSEL_MASK)
  /* Select DVDD as input to the digital regulator. The switch to DVDD will take
     effect once the DCDC output is stable. */
  EMU->PWRCTRL |= EMU_PWRCTRL_REGPWRSEL_DVDD;
#endif

  /* Set EM0 DCDC operating mode. Output voltage set in
     @ref EMU_DCDCOutputVoltageSet() above takes effect if mode
     is changed from bypass/off mode. */
  EMU_DCDCModeSet(dcdcInit->dcdcMode);

#if (_SILICON_LABS_GECKO_INTERNAL_SDID != 80)
  /* Select the analog peripheral power supply. This must be done after
     DCDC mode is set for all devices other than EFM32xG1 and EFR32xG1. */
  BUS_RegBitWrite(&EMU->PWRCTRL,
                  _EMU_PWRCTRL_ANASW_SHIFT,
                  dcdcInit->anaPeripheralPower
                  == emuDcdcAnaPeripheralPower_DCDC ? 1U : 0U);
#endif

  return true;
}

/***************************************************************************//**
 * @brief
 *   Set DCDC regulator operating mode.
 *
 * @param[in] dcdcMode
 *   DCDC mode.
 ******************************************************************************/
void EMU_DCDCModeSet(EMU_DcdcMode_TypeDef dcdcMode)
{
  bool dcdcLocked;
  uint32_t currentDcdcMode;

  dcdcLocked = (EMU->PWRLOCK == EMU_PWRLOCK_LOCKKEY_LOCKED);
  EMU_PowerUnlock();

  /* Wait for any previous write sync to complete and read DCDC mode. */
  while ((EMU->DCDCSYNC & EMU_DCDCSYNC_DCDCCTRLBUSY) != 0U) {
  }
  currentDcdcMode = (EMU->DCDCCTRL & _EMU_DCDCCTRL_DCDCMODE_MASK);

  /* Enable bypass current limiter when not in bypass mode to prevent
     excessive current between VREGVDD and DVDD supplies when reentering bypass mode.  */
  if (currentDcdcMode != EMU_DCDCCTRL_DCDCMODE_BYPASS) {
    BUS_RegBitWrite(&EMU->DCDCCLIMCTRL, _EMU_DCDCCLIMCTRL_BYPLIMEN_SHIFT, 1);
  }

  if ((EMU_DcdcMode_TypeDef)currentDcdcMode == dcdcMode) {
    /* Mode already set. If already in bypass, make sure the bypass current limiter
       is disabled. */
    if (dcdcMode == emuDcdcMode_Bypass) {
      BUS_RegBitWrite(&EMU->DCDCCLIMCTRL, _EMU_DCDCCLIMCTRL_BYPLIMEN_SHIFT, 0);
    }
    return;
  }

#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80)

  /* Fix for errata DCDC_E203. */
  if ((currentDcdcMode == EMU_DCDCCTRL_DCDCMODE_BYPASS)
      && (dcdcMode == emuDcdcMode_LowNoise)) {
    errataFixDcdcHsState = errataFixDcdcHsBypassLn;
  }
#endif // (_SILICON_LABS_GECKO_INTERNAL_SDID_80)

#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_84)

  /* Fix for errata DCDC_E204. */
  if (((currentDcdcMode == EMU_DCDCCTRL_DCDCMODE_OFF) || (currentDcdcMode == EMU_DCDCCTRL_DCDCMODE_BYPASS))
      && ((dcdcMode == emuDcdcMode_LowPower) || (dcdcMode == emuDcdcMode_LowNoise))) {
    /* Always start in LOWNOISE. Switch to LOWPOWER mode once LOWNOISE startup is complete. */
    EMU_IntClear(EMU_IFC_DCDCLNRUNNING);
    while ((EMU->DCDCSYNC & EMU_DCDCSYNC_DCDCCTRLBUSY) != 0U) {
    }
    EMU->DCDCCTRL = (EMU->DCDCCTRL & ~_EMU_DCDCCTRL_DCDCMODE_MASK) | EMU_DCDCCTRL_DCDCMODE_LOWNOISE;
    while ((EMU_IntGet() & EMU_IF_DCDCLNRUNNING) == 0U) {
    }
  }
#endif // (_SILICON_LABS_GECKO_INTERNAL_SDID_84)

  /* Set user-requested mode. */
  while ((EMU->DCDCSYNC & EMU_DCDCSYNC_DCDCCTRLBUSY) != 0UL) {
  }
  EMU->DCDCCTRL = (EMU->DCDCCTRL & ~_EMU_DCDCCTRL_DCDCMODE_MASK)
                  | (uint32_t)dcdcMode;

  /* Disable bypass current limiter after bypass mode is entered.
     Enable the limiter if any other mode is entered. */
  while ((EMU->DCDCSYNC & EMU_DCDCSYNC_DCDCCTRLBUSY) != 0U) {
  }
  BUS_RegBitWrite(&EMU->DCDCCLIMCTRL,
                  _EMU_DCDCCLIMCTRL_BYPLIMEN_SHIFT,
                  dcdcMode == emuDcdcMode_Bypass ? 0U : 1U);

  if (dcdcLocked) {
    EMU_PowerLock();
  }
}

#if defined(EMU_DCDCCTRL_DCDCMODEEM23)
/***************************************************************************//**
 * @brief
 *   Set DCDC Mode EM23 operating mode.
 *
 * @param[in] dcdcModeEM23
 *   DCDC mode EM23.
 ******************************************************************************/
void EMU_DCDCModeEM23Set(EMU_DcdcModeEM23_TypeDef dcdcModeEM23)
{
  bool dcdcLocked;

  dcdcLocked = (EMU->PWRLOCK == EMU_PWRLOCK_LOCKKEY_LOCKED);
  EMU_PowerUnlock();

  /* Set user-requested mode. */
  while ((EMU->DCDCSYNC & EMU_DCDCSYNC_DCDCCTRLBUSY) != 0UL) {
  }
  EMU->DCDCCTRL = (EMU->DCDCCTRL & ~_EMU_DCDCCTRL_DCDCMODEEM23_MASK)
                  | (uint32_t)dcdcModeEM23;

  if (dcdcLocked) {
    EMU_PowerLock();
  }
}
#endif

/***************************************************************************//**
 * @brief
 *   Power off the DCDC regulator.
 *
 * @details
 *   This function powers off the DCDC controller. This function should only be
 *   used if the external power circuit is wired for no DCDC. If the external power
 *   circuit is wired for DCDC usage, use @ref EMU_DCDCInit() and set the
 *   DCDC in bypass mode to disable DCDC.
 *
 * @return
 *   Return false if the DCDC could not be disabled.
 ******************************************************************************/
bool EMU_DCDCPowerOff(void)
{
  bool dcdcModeSet;

#if defined(_EMU_PWRCFG_MASK)
  /* Set DCDCTODVDD only to enable write access to EMU->DCDCCTRL. */
  EMU->PWRCFG = EMU_PWRCFG_PWRCFG_DCDCTODVDD;
#endif

  /* Select DVDD as input to the digital regulator. */
#if defined(EMU_PWRCTRL_IMMEDIATEPWRSWITCH)
  EMU->PWRCTRL |= EMU_PWRCTRL_REGPWRSEL_DVDD | EMU_PWRCTRL_IMMEDIATEPWRSWITCH;
#elif defined(EMU_PWRCTRL_REGPWRSEL_DVDD)
  EMU->PWRCTRL |= EMU_PWRCTRL_REGPWRSEL_DVDD;
#endif

  /* Set DCDC to OFF and disable LP in EM2/3/4. Verify that the required
     mode could be set. */
  while ((EMU->DCDCSYNC & EMU_DCDCSYNC_DCDCCTRLBUSY) != 0U) {
  }
  EMU->DCDCCTRL = EMU_DCDCCTRL_DCDCMODE_OFF;

  dcdcModeSet = (EMU->DCDCCTRL == EMU_DCDCCTRL_DCDCMODE_OFF);
  EFM_ASSERT(dcdcModeSet);

  return dcdcModeSet;
}

/***************************************************************************//**
 * @brief
 *   Set DCDC LN regulator conduction mode.
 *
 * @param[in] conductionMode
 *   DCDC LN conduction mode.
 * @param[in] rcoDefaultSet
 *   The default DCDC RCO band for the conductionMode will be used if true.
 *   Otherwise, the current RCO configuration is used.
 ******************************************************************************/
void EMU_DCDCConductionModeSet(EMU_DcdcConductionMode_TypeDef conductionMode,
                               bool rcoDefaultSet)
{
  EMU_DcdcMode_TypeDef currentDcdcMode
    = (EMU_DcdcMode_TypeDef)((uint32_t)
                             (EMU->DCDCCTRL & _EMU_DCDCCTRL_DCDCMODE_MASK));
  EMU_DcdcLnRcoBand_TypeDef rcoBand
    = (EMU_DcdcLnRcoBand_TypeDef)((uint32_t)
                                  ((EMU->DCDCLNFREQCTRL
                                    & _EMU_DCDCLNFREQCTRL_RCOBAND_MASK)
                                   >> _EMU_DCDCLNFREQCTRL_RCOBAND_SHIFT));

  /* Set bypass mode and wait for bypass mode to settle before
     EMU_DCDCMISCCTRL_LNFORCECCM is set. Restore current DCDC mode. */
  EMU_IntClear(EMU_IFC_DCDCINBYPASS);
  EMU_DCDCModeSet(emuDcdcMode_Bypass);
  while ((EMU->DCDCSYNC & EMU_DCDCSYNC_DCDCCTRLBUSY) != 0U) {
  }
  while ((EMU_IntGet() & EMU_IF_DCDCINBYPASS) == 0U) {
  }
  if (conductionMode == emuDcdcConductionMode_DiscontinuousLN) {
    EMU->DCDCMISCCTRL &= ~EMU_DCDCMISCCTRL_LNFORCECCM;
    if (rcoDefaultSet) {
      EMU_DCDCLnRcoBandSet(emuDcdcLnRcoBand_3MHz);
    } else {
      /* emuDcdcConductionMode_DiscontinuousLN supports up to 4MHz LN RCO. */
      EFM_ASSERT(rcoBand <= emuDcdcLnRcoBand_4MHz);
    }
  } else {
    EMU->DCDCMISCCTRL |= EMU_DCDCMISCCTRL_LNFORCECCM;
    if (rcoDefaultSet) {
      EMU_DCDCLnRcoBandSet(emuDcdcLnRcoBand_7MHz);
    }
  }
  EMU_DCDCModeSet(currentDcdcMode);
  /* Update slice configuration as it depends on conduction mode and RCO band.*/
  EMU_DCDCOptimizeSlice(dcdcEm01LoadCurrent_mA);
}

/***************************************************************************//**
 * @brief
 *   Set the DCDC output voltage.
 *
 * @note
 *   The DCDC is not characterized for the entire valid output voltage range.
 *   For that reason an upper limit of 3.0V output voltage is enforced.
 *
 * @param[in] mV
 *   Target DCDC output voltage in mV.
 *
 * @param[in] setLpVoltage
 *   Update LP voltage
 *
 * @param[in] setLnVoltage
 *   Update LN voltage
 *
 * @return
 *   True if the mV parameter is valid.
 ******************************************************************************/
bool EMU_DCDCOutputVoltageSet(uint32_t mV,
                              bool setLpVoltage,
                              bool setLnVoltage)
{
#if defined(_DEVINFO_DCDCLNVCTRL0_3V0LNATT1_MASK)

  bool validOutVoltage;
  bool attenuationSet;
  uint32_t mVlow = 0;
  uint32_t mVhigh = 0;
  uint32_t mVdiff;
  uint32_t vrefVal[DCDC_TRIM_MODES] = { 0 };
  uint32_t vrefLow[DCDC_TRIM_MODES] = { 0 };
  uint32_t vrefHigh[DCDC_TRIM_MODES] = { 0 };
  uint8_t lpcmpBias[DCDC_TRIM_MODES] = { 0 };

  /* Check that the set voltage is within valid range.
     Voltages are obtained from the data sheet. */
  validOutVoltage = (mV >= PWRCFG_DCDCTODVDD_VMIN)
                    && (mV <= PWRCFG_DCDCTODVDD_VMAX);

  if (!validOutVoltage) {
    EFM_ASSERT(false);
    /* Return when assertions are disabled. */
    return false;
  }

  /* Set attenuation to use and low/high range. */
  attenuationSet = mV > 1800U;
  if (attenuationSet) {
    mVlow = 1800;
    mVhigh = 3000;
    mVdiff = mVhigh - mVlow;
  } else {
    mVlow = 1200;
    mVhigh = 1800;
    mVdiff = mVhigh - mVlow;
  }

  /* Get 2-point calibration data from DEVINFO. */

  /* LN mode */
  if (attenuationSet) {
    vrefLow[dcdcTrimMode_LN]  = DEVINFO->DCDCLNVCTRL0;
    vrefHigh[dcdcTrimMode_LN] = (vrefLow[dcdcTrimMode_LN] & _DEVINFO_DCDCLNVCTRL0_3V0LNATT1_MASK)
                                >> _DEVINFO_DCDCLNVCTRL0_3V0LNATT1_SHIFT;
    vrefLow[dcdcTrimMode_LN]  = (vrefLow[dcdcTrimMode_LN] & _DEVINFO_DCDCLNVCTRL0_1V8LNATT1_MASK)
                                >> _DEVINFO_DCDCLNVCTRL0_1V8LNATT1_SHIFT;
  } else {
    vrefLow[dcdcTrimMode_LN]  = DEVINFO->DCDCLNVCTRL0;
    vrefHigh[dcdcTrimMode_LN] = (vrefLow[dcdcTrimMode_LN] & _DEVINFO_DCDCLNVCTRL0_1V8LNATT0_MASK)
                                >> _DEVINFO_DCDCLNVCTRL0_1V8LNATT0_SHIFT;
    vrefLow[dcdcTrimMode_LN]  = (vrefLow[dcdcTrimMode_LN] & _DEVINFO_DCDCLNVCTRL0_1V2LNATT0_MASK)
                                >> _DEVINFO_DCDCLNVCTRL0_1V2LNATT0_SHIFT;
  }

  /* LP EM234H mode */
  lpcmpBias[dcdcTrimMode_EM234H_LP] = (uint8_t)
                                      ((EMU->DCDCMISCCTRL & _GENERIC_DCDCMISCCTRL_LPCMPBIASEM234H_MASK)
                                       >> _GENERIC_DCDCMISCCTRL_LPCMPBIASEM234H_SHIFT);
  lpGetDevinfoVrefLowHigh(&vrefLow[dcdcTrimMode_EM234H_LP],
                          &vrefHigh[dcdcTrimMode_EM234H_LP],
                          attenuationSet,
                          lpcmpBias[dcdcTrimMode_EM234H_LP]);

#if defined(_EMU_DCDCLPEM01CFG_LPCMPBIASEM01_MASK)
  /* LP EM01 mode */
  lpcmpBias[dcdcTrimMode_EM01_LP] = (uint8_t)
                                    ((EMU->DCDCLPEM01CFG & _EMU_DCDCLPEM01CFG_LPCMPBIASEM01_MASK)
                                     >> _EMU_DCDCLPEM01CFG_LPCMPBIASEM01_SHIFT);
  lpGetDevinfoVrefLowHigh(&vrefLow[dcdcTrimMode_EM01_LP],
                          &vrefHigh[dcdcTrimMode_EM01_LP],
                          attenuationSet,
                          lpcmpBias[dcdcTrimMode_EM01_LP]);
#endif

  /* Calculate output voltage trims. */
  vrefVal[dcdcTrimMode_LN]         = ((mV - mVlow) * (vrefHigh[dcdcTrimMode_LN] - vrefLow[dcdcTrimMode_LN]))
                                     / mVdiff;
  vrefVal[dcdcTrimMode_LN]        += vrefLow[dcdcTrimMode_LN];

  vrefVal[dcdcTrimMode_EM234H_LP]  = ((mV - mVlow) * (vrefHigh[dcdcTrimMode_EM234H_LP] - vrefLow[dcdcTrimMode_EM234H_LP]))
                                     / mVdiff;
  vrefVal[dcdcTrimMode_EM234H_LP] += vrefLow[dcdcTrimMode_EM234H_LP];

#if defined(_EMU_DCDCLPEM01CFG_LPCMPBIASEM01_MASK)
  vrefVal[dcdcTrimMode_EM01_LP]    = ((mV - mVlow) * (vrefHigh[dcdcTrimMode_EM01_LP] - vrefLow[dcdcTrimMode_EM01_LP]))
                                     / mVdiff;
  vrefVal[dcdcTrimMode_EM01_LP]   += vrefLow[dcdcTrimMode_EM01_LP];
#endif

  /* Range checks */
  if ((vrefVal[dcdcTrimMode_LN] > vrefHigh[dcdcTrimMode_LN])
      || (vrefVal[dcdcTrimMode_LN] < vrefLow[dcdcTrimMode_LN])
#if defined(_EMU_DCDCLPEM01CFG_LPCMPBIASEM01_MASK)
      || (vrefVal[dcdcTrimMode_EM01_LP] > vrefHigh[dcdcTrimMode_EM01_LP])
      || (vrefVal[dcdcTrimMode_EM01_LP] < vrefLow[dcdcTrimMode_EM01_LP])
#endif
      || (vrefVal[dcdcTrimMode_EM234H_LP] > vrefHigh[dcdcTrimMode_EM234H_LP])
      || (vrefVal[dcdcTrimMode_EM234H_LP] < vrefLow[dcdcTrimMode_EM234H_LP])) {
    EFM_ASSERT(false);
    /* Return when assertions are disabled. */
    return false;
  }

  /* Update output voltage tuning for LN and LP modes. */
  if (setLnVoltage) {
    EMU->DCDCLNVCTRL = (EMU->DCDCLNVCTRL & ~(_EMU_DCDCLNVCTRL_LNVREF_MASK | _EMU_DCDCLNVCTRL_LNATT_MASK))
                       | (vrefVal[dcdcTrimMode_LN] << _EMU_DCDCLNVCTRL_LNVREF_SHIFT)
                       | (attenuationSet ? EMU_DCDCLNVCTRL_LNATT : 0U);
  }

  if (setLpVoltage) {
    /* Load LP EM234H comparator hysteresis calibration. */
    if (!(lpCmpHystCalibrationLoad(attenuationSet, lpcmpBias[dcdcTrimMode_EM234H_LP], dcdcTrimMode_EM234H_LP))) {
      EFM_ASSERT(false);
      /* Return when assertions are disabled. */
      return false;
    }

#if defined(_EMU_DCDCLPEM01CFG_LPCMPBIASEM01_MASK)
    /* Load LP EM234H comparator hysteresis calibration. */
    if (!(lpCmpHystCalibrationLoad(attenuationSet, lpcmpBias[dcdcTrimMode_EM01_LP], dcdcTrimMode_EM01_LP))) {
      EFM_ASSERT(false);
      /* Return when assertions are disabled. */
      return false;
    }

    /* LP VREF is that maximum of trims for EM01 and EM234H. */
    vrefVal[dcdcTrimMode_EM234H_LP] = SL_MAX(vrefVal[dcdcTrimMode_EM234H_LP], vrefVal[dcdcTrimMode_EM01_LP]);
#endif

    /* Don't exceed the maximum available code as specified in the reference manual for EMU_DCDCLPVCTRL. */
    vrefVal[dcdcTrimMode_EM234H_LP] = SL_MIN(vrefVal[dcdcTrimMode_EM234H_LP], 0xE7U);
    EMU->DCDCLPVCTRL = (EMU->DCDCLPVCTRL & ~(_EMU_DCDCLPVCTRL_LPVREF_MASK | _EMU_DCDCLPVCTRL_LPATT_MASK))
                       | (vrefVal[dcdcTrimMode_EM234H_LP] << _EMU_DCDCLPVCTRL_LPVREF_SHIFT)
                       | (attenuationSet ? EMU_DCDCLPVCTRL_LPATT : 0U);
  }
#endif
  return true;
}

/***************************************************************************//**
 * @brief
 *   Optimize the DCDC slice count based on the estimated average load current
 *   in EM0.
 *
 * @param[in] em0LoadCurrentmA
 *   Estimated average EM0 load current in mA.
 ******************************************************************************/
void EMU_DCDCOptimizeSlice(uint32_t em0LoadCurrentmA)
{
  uint32_t sliceCount = 0;
  uint32_t rcoBand = (EMU->DCDCLNFREQCTRL & _EMU_DCDCLNFREQCTRL_RCOBAND_MASK)
                     >> _EMU_DCDCLNFREQCTRL_RCOBAND_SHIFT;

  /* Set the recommended slice count. */
  if (((EMU->DCDCMISCCTRL & _EMU_DCDCMISCCTRL_LNFORCECCM_MASK) != 0U)
      && (rcoBand >= (uint32_t)emuDcdcLnRcoBand_5MHz)) {
    if (em0LoadCurrentmA < 20U) {
      sliceCount = 4;
    } else if ((em0LoadCurrentmA >= 20U) && (em0LoadCurrentmA < 40U)) {
      sliceCount = 8;
    } else {
      sliceCount = 16;
    }
  } else if (((EMU->DCDCMISCCTRL & _EMU_DCDCMISCCTRL_LNFORCECCM_MASK) == 0U)
             && (rcoBand <= (uint32_t)emuDcdcLnRcoBand_4MHz)) {
    if (em0LoadCurrentmA < 10U) {
      sliceCount = 4;
    } else if ((em0LoadCurrentmA >= 10U) && (em0LoadCurrentmA < 20U)) {
      sliceCount = 8;
    } else {
      sliceCount = 16;
    }
  } else if (((EMU->DCDCMISCCTRL & _EMU_DCDCMISCCTRL_LNFORCECCM_MASK) != 0U)
             && (rcoBand <= (uint32_t)emuDcdcLnRcoBand_4MHz)) {
    if (em0LoadCurrentmA < 40U) {
      sliceCount = 8;
    } else {
      sliceCount = 16;
    }
  } else {
    /* This configuration is not recommended. @ref EMU_DCDCInit() applies a recommended
       configuration. */
    EFM_ASSERT(false);
  }

  /* The selected slices are PSLICESEL + 1. */
  sliceCount--;

  /* Apply slice count to both N and P slice. */
  sliceCount = (sliceCount << _EMU_DCDCMISCCTRL_PFETCNT_SHIFT
                | sliceCount << _EMU_DCDCMISCCTRL_NFETCNT_SHIFT);
  EMU->DCDCMISCCTRL = (EMU->DCDCMISCCTRL & ~(_EMU_DCDCMISCCTRL_PFETCNT_MASK
                                             | _EMU_DCDCMISCCTRL_NFETCNT_MASK))
                      | sliceCount;

  /* Update the current limiters. */
  currentLimitersUpdate();
}

/***************************************************************************//**
 * @brief
 *   Set DCDC Low-noise RCO band.
 *
 * @param[in] band
 *   RCO band to set.
 ******************************************************************************/
void EMU_DCDCLnRcoBandSet(EMU_DcdcLnRcoBand_TypeDef band)
{
  uint32_t forcedCcm;
  forcedCcm = BUS_RegBitRead(&EMU->DCDCMISCCTRL, _EMU_DCDCMISCCTRL_LNFORCECCM_SHIFT);

  /* DCM mode supports up to 4 MHz LN RCO. */
  EFM_ASSERT(((forcedCcm == 0U) && band <= emuDcdcLnRcoBand_4MHz)
             || (forcedCcm != 0U));

  EMU->DCDCLNFREQCTRL = (EMU->DCDCLNFREQCTRL & ~_EMU_DCDCLNFREQCTRL_RCOBAND_MASK)
                        | ((uint32_t)band << _EMU_DCDCLNFREQCTRL_RCOBAND_SHIFT);

  /* Update slice configuration as this depends on the RCO band. */
  EMU_DCDCOptimizeSlice(dcdcEm01LoadCurrent_mA);
}
#endif // defined(_EMU_DCDCCTRL_MASK)

#if defined(_DCDC_CTRL_MASK)
/***************************************************************************//**
 * @brief
 *   Configure the DCDC regulator.
 *
 * @param[in] dcdcInit
 *  The DCDC initialization structure.
 *
 * @return
 *   True if initialization parameters are valid.
 ******************************************************************************/
bool EMU_DCDCInit(const EMU_DCDCInit_TypeDef *dcdcInit)
{
  bool dcdcLocked;

  CMU->CLKEN0_SET = CMU_CLKEN0_DCDC;
#if defined(_DCDC_EN_EN_MASK)
  DCDC->EN_SET    = DCDC_EN_EN;
#endif
  dcdcLocked = ((DCDC->LOCKSTATUS & DCDC_LOCKSTATUS_LOCK) != 0);
  EMU_DCDCUnlock();

  EMU->VREGVDDCMPCTRL = ((uint32_t)dcdcInit->cmpThreshold
                         << _EMU_VREGVDDCMPCTRL_THRESSEL_SHIFT)
                        | EMU_VREGVDDCMPCTRL_VREGINCMPEN;

#if defined(_DCDC_SYNCBUSY_MASK)
  EMU_DCDCSync(DCDC_SYNCBUSY_CTRL | DCDC_SYNCBUSY_EM01CTRL0 | DCDC_SYNCBUSY_EM23CTRL0);
#endif
#if defined(_DCDC_CTRL_DCMONLYEN_MASK)
  DCDC->CTRL = (DCDC->CTRL & ~(_DCDC_CTRL_IPKTMAXCTRL_MASK
                               | _DCDC_CTRL_DCMONLYEN_MASK))
               | ((uint32_t)dcdcInit->tonMax << _DCDC_CTRL_IPKTMAXCTRL_SHIFT)
               | ((uint32_t)(dcdcInit->dcmOnlyEn ? 1U : 0U) << _DCDC_CTRL_DCMONLYEN_SHIFT);
#else
  DCDC->CTRL = (DCDC->CTRL & ~(_DCDC_CTRL_IPKTMAXCTRL_MASK))
               | ((uint32_t)dcdcInit->tonMax << _DCDC_CTRL_IPKTMAXCTRL_SHIFT);
#endif
  DCDC->EM01CTRL0 = ((uint32_t)dcdcInit->driveSpeedEM01 << _DCDC_EM01CTRL0_DRVSPEED_SHIFT)
                    | ((uint32_t)dcdcInit->peakCurrentEM01 << _DCDC_EM01CTRL0_IPKVAL_SHIFT);
  DCDC->EM23CTRL0 = ((uint32_t)dcdcInit->driveSpeedEM23 << _DCDC_EM23CTRL0_DRVSPEED_SHIFT)
                    | ((uint32_t)dcdcInit->peakCurrentEM23 << _DCDC_EM23CTRL0_IPKVAL_SHIFT);

  EMU_DCDCModeSet(dcdcInit->mode);

  if (dcdcLocked) {
    EMU_DCDCLock();
  }

  return true;
}

/***************************************************************************//**
 * @brief
 *   Set DCDC regulator operating mode.
 *
 * @param[in] dcdcMode
 *   DCDC mode.
 ******************************************************************************/
void EMU_DCDCModeSet(EMU_DcdcMode_TypeDef dcdcMode)
{
  bool dcdcLocked;
  uint32_t currentDcdcMode;

  CMU->CLKEN0_SET = CMU_CLKEN0_DCDC;
#if defined(_DCDC_EN_EN_MASK)
  DCDC->EN_SET = DCDC_EN_EN;
#endif
  dcdcLocked = ((DCDC->LOCKSTATUS & DCDC_LOCKSTATUS_LOCK) != 0);
  EMU_DCDCUnlock();

  if (dcdcMode == emuDcdcMode_Bypass) {
#if defined(_DCDC_SYNCBUSY_MASK)
    EMU_DCDCSync(DCDC_SYNCBUSY_CTRL);
#endif
    currentDcdcMode = (DCDC->CTRL & _DCDC_CTRL_MODE_MASK) >> _DCDC_CTRL_MODE_SHIFT;

    if (currentDcdcMode != emuDcdcMode_Bypass) {
      /* Switch to BYPASS mode if it is not the current mode */
      DCDC->CTRL_CLR = DCDC_CTRL_MODE;
      while ((DCDC->STATUS & DCDC_STATUS_BYPSW) == 0U) {
        /* Wait for BYPASS switch enable. */
      }
    }
#if defined(_DCDC_EN_EN_MASK)
    DCDC->EN_CLR = DCDC_EN_EN;
#endif
  } else {
    while ((DCDC->STATUS & DCDC_STATUS_VREGIN) != 0U) {
      /* Wait for VREGIN voltage to rise above threshold. */
    }

    DCDC->IF_CLR = DCDC_IF_REGULATION;
    DCDC->CTRL_SET = DCDC_CTRL_MODE;
    while ((DCDC->IF & DCDC_IF_REGULATION) == 0U) {
      /* Wait for DCDC to complete it's startup. */
    }
  }

  if (dcdcLocked) {
    EMU_DCDCLock();
  }
}

/***************************************************************************//**
 * @brief
 *   Power off the DCDC regulator.
 *
 * @return
 *   Returns true.
 ******************************************************************************/
bool EMU_DCDCPowerOff(void)
{
  EMU_DCDCModeSet(emuDcdcMode_Bypass);
  return true;
}
#endif /* _DCDC_CTRL_MASK */

#if defined(_DCDC_EM01CTRL0_IPKVAL_MASK)
/***************************************************************************//**
 * @brief
 *   Set EMO1 mode Peak Current setting.
 *
 * @param[in] peakCurrentEM01
 *  Peak load current coefficient in EM01 mode.
 ******************************************************************************/
void EMU_EM01PeakCurrentSet(const EMU_DcdcPeakCurrent_TypeDef peakCurrentEM01)
{
  bool dcdcLocked = false;
  bool dcdcClkWasEnabled = false;

  dcdcClkWasEnabled = ((CMU->CLKEN0 & CMU_CLKEN0_DCDC) != 0);
  CMU->CLKEN0_SET = CMU_CLKEN0_DCDC;

#if defined(_DCDC_EN_EN_MASK)
  bool dcdcWasEnabled = ((DCDC->EN & DCDC_EN_EN) != 0);
  DCDC->EN_SET = DCDC_EN_EN;
#endif

  dcdcLocked = ((DCDC->LOCKSTATUS & DCDC_LOCKSTATUS_LOCK) != 0);
  EMU_DCDCUnlock();

#if defined(_DCDC_SYNCBUSY_MASK)
  /* Wait for synchronization before writing new value */
  EMU_DCDCSync(DCDC_SYNCBUSY_EM01CTRL0);
#endif

  BUS_RegMaskedWrite(&DCDC->EM01CTRL0,
                     _DCDC_EM01CTRL0_IPKVAL_MASK,
                     ((uint32_t)peakCurrentEM01 << _DCDC_EM01CTRL0_IPKVAL_SHIFT));

#if defined(_DCDC_EN_EN_MASK)
  if (!dcdcWasEnabled) {
    DCDC->EN_CLR = DCDC_EN_EN;
  }
#endif

  if (dcdcLocked) {
    EMU_DCDCLock();
  }

  if (!dcdcClkWasEnabled) {
    CMU->CLKEN0_CLR = CMU_CLKEN0_DCDC;
  }
}
#endif /* _DCDC_EM01CTRL0_MASK */

#if defined(_DCDC_PFMXCTRL_IPKVAL_MASK)
/***************************************************************************//**
 * @brief
 *   Set PFMX mode Peak Current setting.
 *
 * @param[in] value
 *  Peak load current coefficient in PFMX mode.
 ******************************************************************************/
void EMU_DCDCSetPFMXModePeakCurrent(uint32_t value)
{
  bool dcdcLocked = false;
  bool dcdcClkWasEnabled = false;

  /* Verification that the parameter is in range. */
  /* if not, restrict value to maximum allowed.   */
  EFM_ASSERT(value <= (_DCDC_PFMXCTRL_IPKVAL_MASK >> _DCDC_PFMXCTRL_IPKVAL_SHIFT));
  if (value > (_DCDC_PFMXCTRL_IPKVAL_MASK >> _DCDC_PFMXCTRL_IPKVAL_SHIFT)) {
    value = (_DCDC_PFMXCTRL_IPKVAL_MASK >> _DCDC_PFMXCTRL_IPKVAL_SHIFT);
  }

  dcdcClkWasEnabled = ((CMU->CLKEN0 & CMU_CLKEN0_DCDC) != 0);
  CMU->CLKEN0_SET = CMU_CLKEN0_DCDC;

  dcdcLocked = ((DCDC->LOCKSTATUS & DCDC_LOCKSTATUS_LOCK) != 0);
  EMU_DCDCUnlock();

#if defined(_DCDC_SYNCBUSY_MASK)
  /* Wait for synchronization before writing new value */
  EMU_DCDCSync(DCDC_SYNCBUSY_PFMXCTRL);
#endif

  DCDC->PFMXCTRL = ((DCDC->PFMXCTRL & ~_DCDC_PFMXCTRL_IPKVAL_MASK)
                    | value << _DCDC_PFMXCTRL_IPKVAL_SHIFT);

  if (dcdcLocked) {
    EMU_DCDCLock();
  }

  if (!dcdcClkWasEnabled) {
    CMU->CLKEN0_CLR = CMU_CLKEN0_DCDC;
  }
}
#endif /* _DCDC_PFMXCTRL_IPKVAL_MASK */

#if defined(_DCDC_PFMXCTRL_IPKTMAXCTRL_MASK)
/***************************************************************************//**
 * @brief
 *   Set Ton_max timeout control.
 *
 * @param[in] value
 *  Maximum time for peak current detection.
 ******************************************************************************/
void EMU_DCDCSetPFMXTimeoutMaxCtrl(EMU_DcdcTonMaxTimeout_TypeDef value)
{
  bool dcdcLocked = false;
  bool dcdcClkWasEnabled = false;

  dcdcClkWasEnabled = ((CMU->CLKEN0 & CMU_CLKEN0_DCDC) != 0);
  CMU->CLKEN0_SET = CMU_CLKEN0_DCDC;

  dcdcLocked = ((DCDC->LOCKSTATUS & DCDC_LOCKSTATUS_LOCK) != 0);
  EMU_DCDCUnlock();

#if defined(_DCDC_SYNCBUSY_MASK)
  /* Wait for synchronization before writing new value */
  EMU_DCDCSync(DCDC_SYNCBUSY_PFMXCTRL);
#endif

  DCDC->PFMXCTRL = ((DCDC->PFMXCTRL & ~_DCDC_PFMXCTRL_IPKTMAXCTRL_MASK)
                    | value << _DCDC_PFMXCTRL_IPKTMAXCTRL_SHIFT);

  if (dcdcLocked) {
    EMU_DCDCLock();
  }

  if (!dcdcClkWasEnabled) {
    CMU->CLKEN0_CLR = CMU_CLKEN0_DCDC;
  }
}
#endif /* _DCDC_PFMXCTRL_IPKTMAXCTRL_MASK */

#if defined(EMU_STATUS_VMONRDY)

/***************************************************************************//**
 * @brief
 *   Get the calibrated threshold value.
 *
 * @details
 *   All VMON channels have two calibration fields in the DI page that
 *   describes the threshold at 1.86 V and 2.98 V. This function will convert
 *   the uncalibrated input voltage threshold in millivolts into a calibrated
 *   threshold.
 *
 * @param[in] channel
 *   A VMON channel.
 *
 * @param[in] threshold
 *   A desired threshold in millivolts.
 *
 * @return
 *   A calibrated threshold value to use. The first digit of the return value is placed
 *   in the "fine" register fields while the next digits are placed in the
 *   "coarse" register fields.
 ******************************************************************************/
static uint32_t vmonCalibratedThreshold(EMU_VmonChannel_TypeDef channel,
                                        int threshold)
{
  uint32_t tDiff = 0;
  uint32_t tLow = 0;
  uint32_t tHigh = 0;
  uint32_t calReg;

  /* Get calibration values for 1.86 V and 2.98 V */
  switch (channel) {
    case emuVmonChannel_AVDD:
      calReg = DEVINFO->VMONCAL0;
      tLow = (10U * ((calReg & _DEVINFO_VMONCAL0_AVDD1V86THRESCOARSE_MASK)
                     >> _DEVINFO_VMONCAL0_AVDD1V86THRESCOARSE_SHIFT))
             + ((calReg & _DEVINFO_VMONCAL0_AVDD1V86THRESFINE_MASK)
                >> _DEVINFO_VMONCAL0_AVDD1V86THRESFINE_SHIFT);
      tHigh = (10U * ((calReg & _DEVINFO_VMONCAL0_AVDD2V98THRESCOARSE_MASK)
                      >> _DEVINFO_VMONCAL0_AVDD2V98THRESCOARSE_SHIFT))
              + ((calReg & _DEVINFO_VMONCAL0_AVDD2V98THRESFINE_MASK)
                 >> _DEVINFO_VMONCAL0_AVDD2V98THRESFINE_SHIFT);
      break;
    case emuVmonChannel_ALTAVDD:
      calReg = DEVINFO->VMONCAL0;
      tLow = (10U * ((calReg & _DEVINFO_VMONCAL0_ALTAVDD1V86THRESCOARSE_MASK)
                     >> _DEVINFO_VMONCAL0_ALTAVDD1V86THRESCOARSE_SHIFT))
             + ((calReg & _DEVINFO_VMONCAL0_ALTAVDD1V86THRESFINE_MASK)
                >> _DEVINFO_VMONCAL0_ALTAVDD1V86THRESFINE_SHIFT);
      tHigh = (10U * ((calReg & _DEVINFO_VMONCAL0_ALTAVDD2V98THRESCOARSE_MASK)
                      >> _DEVINFO_VMONCAL0_ALTAVDD2V98THRESCOARSE_SHIFT))
              + ((calReg & _DEVINFO_VMONCAL0_ALTAVDD2V98THRESFINE_MASK)
                 >> _DEVINFO_VMONCAL0_ALTAVDD2V98THRESFINE_SHIFT);
      break;
    case emuVmonChannel_DVDD:
      calReg = DEVINFO->VMONCAL1;
      tLow = (10U * ((calReg & _DEVINFO_VMONCAL1_DVDD1V86THRESCOARSE_MASK)
                     >> _DEVINFO_VMONCAL1_DVDD1V86THRESCOARSE_SHIFT))
             + ((calReg & _DEVINFO_VMONCAL1_DVDD1V86THRESFINE_MASK)
                >> _DEVINFO_VMONCAL1_DVDD1V86THRESFINE_SHIFT);
      tHigh = (10U * ((calReg & _DEVINFO_VMONCAL1_DVDD2V98THRESCOARSE_MASK)
                      >> _DEVINFO_VMONCAL1_DVDD2V98THRESCOARSE_SHIFT))
              + ((calReg & _DEVINFO_VMONCAL1_DVDD2V98THRESFINE_MASK)
                 >> _DEVINFO_VMONCAL1_DVDD2V98THRESFINE_SHIFT);
      break;
    case emuVmonChannel_IOVDD0:
      calReg = DEVINFO->VMONCAL1;
      tLow = (10U * ((calReg & _DEVINFO_VMONCAL1_IO01V86THRESCOARSE_MASK)
                     >> _DEVINFO_VMONCAL1_IO01V86THRESCOARSE_SHIFT))
             + ((calReg & _DEVINFO_VMONCAL1_IO01V86THRESFINE_MASK)
                >> _DEVINFO_VMONCAL1_IO01V86THRESFINE_SHIFT);
      tHigh = (10U * ((calReg & _DEVINFO_VMONCAL1_IO02V98THRESCOARSE_MASK)
                      >> _DEVINFO_VMONCAL1_IO02V98THRESCOARSE_SHIFT))
              + ((calReg & _DEVINFO_VMONCAL1_IO02V98THRESFINE_MASK)
                 >> _DEVINFO_VMONCAL1_IO02V98THRESFINE_SHIFT);
      break;
#if defined(_EMU_VMONIO1CTRL_EN_MASK)
    case emuVmonChannel_IOVDD1:
      calReg = DEVINFO->VMONCAL2;
      tLow = (10U * ((calReg & _DEVINFO_VMONCAL2_IO11V86THRESCOARSE_MASK)
                     >> _DEVINFO_VMONCAL2_IO11V86THRESCOARSE_SHIFT))
             + ((calReg & _DEVINFO_VMONCAL2_IO11V86THRESFINE_MASK)
                >> _DEVINFO_VMONCAL2_IO11V86THRESFINE_SHIFT);
      tHigh = (10U * ((calReg & _DEVINFO_VMONCAL2_IO12V98THRESCOARSE_MASK)
                      >> _DEVINFO_VMONCAL2_IO12V98THRESCOARSE_SHIFT))
              + ((calReg & _DEVINFO_VMONCAL2_IO12V98THRESFINE_MASK)
                 >> _DEVINFO_VMONCAL2_IO12V98THRESFINE_SHIFT);
      break;
#endif
#if defined(_EMU_VMONBUVDDCTRL_EN_MASK)
    case emuVmonChannel_BUVDD:
      calReg = DEVINFO->VMONCAL2;
      tLow = (10U * ((calReg & _DEVINFO_VMONCAL2_BUVDD1V86THRESCOARSE_MASK)
                     >> _DEVINFO_VMONCAL2_BUVDD1V86THRESCOARSE_SHIFT))
             + ((calReg & _DEVINFO_VMONCAL2_BUVDD1V86THRESFINE_MASK)
                >> _DEVINFO_VMONCAL2_BUVDD1V86THRESFINE_SHIFT);
      tHigh = (10U * ((calReg & _DEVINFO_VMONCAL2_BUVDD2V98THRESCOARSE_MASK)
                      >> _DEVINFO_VMONCAL2_BUVDD2V98THRESCOARSE_SHIFT))
              + ((calReg & _DEVINFO_VMONCAL2_BUVDD2V98THRESFINE_MASK)
                 >> _DEVINFO_VMONCAL2_BUVDD2V98THRESFINE_SHIFT);
      break;
#endif
    default:
      EFM_ASSERT(false);
      break;
  }

  tDiff = tHigh - tLow;
  if (tDiff > 0) {
    /* Calculate threshold.
     *
     * Note that volt is used in the reference manual. However, the results
     * should be in millivolts. The precision of Va and Vb are increased in the
     * calculation instead of using floating points.
     */
    uint32_t va = (1120U * 100U) / (tDiff);
    uint32_t vb = (1860U * 100U) - (va * tLow);
    // If (tHigh - tLow) is large, Va could be zero. Caught by CSTAT.
    if (va != 0) {
      /* Round the threshold to the nearest integer value. */
      return (((uint32_t)threshold * 100U) - vb + (va / 2U)) / va;
    }
  }

  /* Uncalibrated device guard. */
  return (uint32_t)threshold;
}

/***************************************************************************//**
 * @brief
 *   Initialize a VMON channel.
 *
 * @details
 *   Initialize a VMON channel without hysteresis. If the channel supports
 *   separate rise and fall triggers, both thresholds will be set to the same
 *   value. The threshold will be converted to a register field value based
 *   on calibration values from the DI page.
 *
 * @param[in] vmonInit
 *   The VMON initialization structure.
 ******************************************************************************/
void EMU_VmonInit(const EMU_VmonInit_TypeDef *vmonInit)
{
  uint32_t thresholdCoarse, thresholdFine;
  uint32_t threshold;

  EFM_ASSERT((vmonInit->threshold >= 1620) && (vmonInit->threshold <= 3400));

  threshold = vmonCalibratedThreshold(vmonInit->channel, vmonInit->threshold);
  thresholdFine = threshold % 10U;
  thresholdCoarse = threshold / 10U;

  /* Saturate the threshold to maximum values. */
  if (thresholdCoarse > 0xFU) {
    thresholdCoarse = 0xF;
    thresholdFine = 9;
  }

  switch (vmonInit->channel) {
    case emuVmonChannel_AVDD:
      EMU->VMONAVDDCTRL = (thresholdCoarse << _EMU_VMONAVDDCTRL_RISETHRESCOARSE_SHIFT)
                          | (thresholdFine << _EMU_VMONAVDDCTRL_RISETHRESFINE_SHIFT)
                          | (thresholdCoarse << _EMU_VMONAVDDCTRL_FALLTHRESCOARSE_SHIFT)
                          | (thresholdFine << _EMU_VMONAVDDCTRL_FALLTHRESFINE_SHIFT)
                          | (vmonInit->riseWakeup ? EMU_VMONAVDDCTRL_RISEWU : 0U)
                          | (vmonInit->fallWakeup ? EMU_VMONAVDDCTRL_FALLWU : 0U)
                          | (vmonInit->enable     ? EMU_VMONAVDDCTRL_EN     : 0U);
      break;
    case emuVmonChannel_ALTAVDD:
      EMU->VMONALTAVDDCTRL = (thresholdCoarse << _EMU_VMONALTAVDDCTRL_THRESCOARSE_SHIFT)
                             | (thresholdFine << _EMU_VMONALTAVDDCTRL_THRESFINE_SHIFT)
                             | (vmonInit->riseWakeup ? EMU_VMONALTAVDDCTRL_RISEWU : 0U)
                             | (vmonInit->fallWakeup ? EMU_VMONALTAVDDCTRL_FALLWU : 0U)
                             | (vmonInit->enable     ? EMU_VMONALTAVDDCTRL_EN     : 0U);
      break;
    case emuVmonChannel_DVDD:
      EMU->VMONDVDDCTRL = (thresholdCoarse << _EMU_VMONDVDDCTRL_THRESCOARSE_SHIFT)
                          | (thresholdFine << _EMU_VMONDVDDCTRL_THRESFINE_SHIFT)
                          | (vmonInit->riseWakeup ? EMU_VMONDVDDCTRL_RISEWU : 0U)
                          | (vmonInit->fallWakeup ? EMU_VMONDVDDCTRL_FALLWU : 0U)
                          | (vmonInit->enable     ? EMU_VMONDVDDCTRL_EN     : 0U);
      break;
    case emuVmonChannel_IOVDD0:
      EMU->VMONIO0CTRL = (thresholdCoarse << _EMU_VMONIO0CTRL_THRESCOARSE_SHIFT)
                         | (thresholdFine << _EMU_VMONIO0CTRL_THRESFINE_SHIFT)
                         | (vmonInit->retDisable ? EMU_VMONIO0CTRL_RETDIS : 0U)
                         | (vmonInit->riseWakeup ? EMU_VMONIO0CTRL_RISEWU : 0U)
                         | (vmonInit->fallWakeup ? EMU_VMONIO0CTRL_FALLWU : 0U)
                         | (vmonInit->enable     ? EMU_VMONIO0CTRL_EN     : 0U);
      break;
#if defined(_EMU_VMONIO1CTRL_EN_MASK)
    case emuVmonChannel_IOVDD1:
      EMU->VMONIO1CTRL = (thresholdCoarse << _EMU_VMONIO1CTRL_THRESCOARSE_SHIFT)
                         | (thresholdFine << _EMU_VMONIO1CTRL_THRESFINE_SHIFT)
                         | (vmonInit->retDisable ? EMU_VMONIO1CTRL_RETDIS : 0U)
                         | (vmonInit->riseWakeup ? EMU_VMONIO1CTRL_RISEWU : 0U)
                         | (vmonInit->fallWakeup ? EMU_VMONIO1CTRL_FALLWU : 0U)
                         | (vmonInit->enable     ? EMU_VMONIO1CTRL_EN     : 0U);
      break;
#endif
#if defined(_EMU_VMONBUVDDCTRL_EN_MASK)
    case emuVmonChannel_BUVDD:
      EMU->VMONBUVDDCTRL = (thresholdCoarse << _EMU_VMONBUVDDCTRL_THRESCOARSE_SHIFT)
                           | (thresholdFine << _EMU_VMONBUVDDCTRL_THRESFINE_SHIFT)
                           | (vmonInit->riseWakeup ? EMU_VMONBUVDDCTRL_RISEWU : 0U)
                           | (vmonInit->fallWakeup ? EMU_VMONBUVDDCTRL_FALLWU : 0U)
                           | (vmonInit->enable     ? EMU_VMONBUVDDCTRL_EN     : 0U);
      break;
#endif
    default:
      EFM_ASSERT(false);
      return;
  }
}

/***************************************************************************//**
 * @brief
 *   Initialize a VMON channel with hysteresis (separate rise and fall triggers).
 *
 * @details
 *   Initialize a VMON channel which supports hysteresis. The AVDD channel is
 *   the only channel to support separate rise and fall triggers. The rise and
 *   fall thresholds will be converted to a register field value based on the
 *   calibration values from the DI page.
 *
 * @param[in] vmonInit
 *   The VMON hysteresis initialization structure.
 ******************************************************************************/
void EMU_VmonHystInit(const EMU_VmonHystInit_TypeDef *vmonInit)
{
  uint32_t riseThreshold;
  uint32_t fallThreshold;

  /* VMON supports voltages between 1620 mV and 3400 mV (inclusive). */
  EFM_ASSERT((vmonInit->riseThreshold >= 1620) && (vmonInit->riseThreshold <= 3400));
  EFM_ASSERT((vmonInit->fallThreshold >= 1620) && (vmonInit->fallThreshold <= 3400));
  /* The fall threshold has to be lower than rise threshold. */
  EFM_ASSERT(vmonInit->fallThreshold <= vmonInit->riseThreshold);

  riseThreshold = vmonCalibratedThreshold(vmonInit->channel, vmonInit->riseThreshold);
  fallThreshold = vmonCalibratedThreshold(vmonInit->channel, vmonInit->fallThreshold);

  switch (vmonInit->channel) {
    case emuVmonChannel_AVDD:
      EMU->VMONAVDDCTRL = ((riseThreshold / 10U) << _EMU_VMONAVDDCTRL_RISETHRESCOARSE_SHIFT)
                          | ((riseThreshold % 10U) << _EMU_VMONAVDDCTRL_RISETHRESFINE_SHIFT)
                          | ((fallThreshold / 10U) << _EMU_VMONAVDDCTRL_FALLTHRESCOARSE_SHIFT)
                          | ((fallThreshold % 10U) << _EMU_VMONAVDDCTRL_FALLTHRESFINE_SHIFT)
                          | (vmonInit->riseWakeup ? EMU_VMONAVDDCTRL_RISEWU : 0U)
                          | (vmonInit->fallWakeup ? EMU_VMONAVDDCTRL_FALLWU : 0U)
                          | (vmonInit->enable     ? EMU_VMONAVDDCTRL_EN     : 0U);
      break;
    default:
      EFM_ASSERT(false);
      return;
  }
}

/***************************************************************************//**
 * @brief
 *   Enable or disable a VMON channel.
 *
 * @param[in] channel
 *   A VMON channel to enable/disable.
 *
 * @param[in] enable
 *   Indicates whether to enable or disable.
 ******************************************************************************/
void EMU_VmonEnable(EMU_VmonChannel_TypeDef channel, bool enable)
{
  uint32_t volatile * reg;
  uint32_t bit;

  switch (channel) {
    case emuVmonChannel_AVDD:
      reg = &(EMU->VMONAVDDCTRL);
      bit = _EMU_VMONAVDDCTRL_EN_SHIFT;
      break;
    case emuVmonChannel_ALTAVDD:
      reg = &(EMU->VMONALTAVDDCTRL);
      bit = _EMU_VMONALTAVDDCTRL_EN_SHIFT;
      break;
    case emuVmonChannel_DVDD:
      reg = &(EMU->VMONDVDDCTRL);
      bit = _EMU_VMONDVDDCTRL_EN_SHIFT;
      break;
    case emuVmonChannel_IOVDD0:
      reg = &(EMU->VMONIO0CTRL);
      bit = _EMU_VMONIO0CTRL_EN_SHIFT;
      break;
#if defined(_EMU_VMONIO1CTRL_EN_MASK)
    case emuVmonChannel_IOVDD1:
      reg = &(EMU->VMONIO1CTRL);
      bit = _EMU_VMONIO1CTRL_EN_SHIFT;
      break;
#endif
#if defined(_EMU_VMONBUVDDCTRL_EN_MASK)
    case emuVmonChannel_BUVDD:
      reg = &(EMU->VMONBUVDDCTRL);
      bit = _EMU_VMONBUVDDCTRL_EN_SHIFT;
      break;
#endif
    default:
      EFM_ASSERT(false);
      return;
  }

  BUS_RegBitWrite(reg, bit, (uint32_t)enable);
}

/***************************************************************************//**
 * @brief
 *   Get the status of a voltage monitor channel.
 *
 * @param[in] channel
 *   A VMON channel to get the status for.
 *
 * @return
 *   A status of the selected VMON channel. True if the channel is triggered.
 ******************************************************************************/
bool EMU_VmonChannelStatusGet(EMU_VmonChannel_TypeDef channel)
{
  uint32_t bit;
  switch (channel) {
    case emuVmonChannel_AVDD:
      bit = _EMU_STATUS_VMONAVDD_SHIFT;
      break;
    case emuVmonChannel_ALTAVDD:
      bit = _EMU_STATUS_VMONALTAVDD_SHIFT;
      break;
    case emuVmonChannel_DVDD:
      bit = _EMU_STATUS_VMONDVDD_SHIFT;
      break;
    case emuVmonChannel_IOVDD0:
      bit = _EMU_STATUS_VMONIO0_SHIFT;
      break;
#if defined(_EMU_VMONIO1CTRL_EN_MASK)
    case emuVmonChannel_IOVDD1:
      bit = _EMU_STATUS_VMONIO1_SHIFT;
      break;
#endif
#if defined(_EMU_VMONBUVDDCTRL_EN_MASK)
    case emuVmonChannel_BUVDD:
      bit = _EMU_STATUS_VMONBUVDD_SHIFT;
      break;
#endif
    default:
      bit = 0;
      EFM_ASSERT(false);
      break;
  }

  return BUS_RegBitRead(&EMU->STATUS, bit) != 0U;
}
#endif /* EMU_STATUS_VMONRDY */

#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80)
/***************************************************************************//**
 * @brief
 *   Adjust the bias refresh rate.
 *
 * @details
 *   This function is only meant to be used under high-temperature operation on
 *   EFR32xG1 and EFM32xG1 devices. Adjusting the bias mode will
 *   increase the typical current consumption. See application note 1027
 *   and errata documents for more details.
 *
 * @param [in] mode
 *   The new bias refresh rate.
 ******************************************************************************/
void EMU_SetBiasMode(EMU_BiasMode_TypeDef mode)
{
  uint32_t freq = 0x2u;
  bool emuTestLocked = false;

  if (mode == emuBiasMode_1KHz) {
    freq = 0x0u;
  }

  if (EMU_TESTLOCK == 0x1u) {
    emuTestLocked = true;
    EMU_TESTLOCK = 0xADE8u;
  }

  if (mode == emuBiasMode_Continuous) {
    EMU_BIASCONF &= ~0x74u;
  } else {
    EMU_BIASCONF |= 0x74u;
  }

  EMU_BIASTESTCTRL |= 0x8u;
  CMU_ULFRCOCTRL    = (CMU_ULFRCOCTRL & ~0xC00u)
                      | ((freq & 0x3u) << 10u);
  EMU_BIASTESTCTRL &= ~0x8u;

  if (emuTestLocked) {
    EMU_TESTLOCK = 0u;
  }
}
#endif

#if defined(_EMU_TEMP_TEMP_MASK)
/***************************************************************************//**
 * @brief
 *   Get temperature in degrees Celsius
 *
 * @return
 *   Temperature in degrees Celsius
 ******************************************************************************/
float EMU_TemperatureGet(void)
{
#if defined(_EMU_TEMP_TEMPLSB_MASK)
  return ((float) ((EMU->TEMP & (_EMU_TEMP_TEMP_MASK | _EMU_TEMP_TEMPLSB_MASK) )
                   >> _EMU_TEMP_TEMPLSB_SHIFT)
          ) / 4.0f - EMU_TEMP_ZERO_C_IN_KELVIN;
#else
  uint32_t val1;
  uint32_t val2;
  float tempCo;
  uint32_t diTemp, diEmu;

  // Calculate calibration temp based on DI page values
  diTemp = ((DEVINFO->CAL & _DEVINFO_CAL_TEMP_MASK) >> _DEVINFO_CAL_TEMP_SHIFT);
  diEmu = ((DEVINFO->EMUTEMP & _DEVINFO_EMUTEMP_EMUTEMPROOM_MASK) >> _DEVINFO_EMUTEMP_EMUTEMPROOM_SHIFT);
  tempCo = EMU_TEMPCO_CONST + (diEmu / 100.0f);

  // Read temperature twice to ensure a stable value
  do {
    val1 = (EMU->TEMP & _EMU_TEMP_TEMP_MASK)
           >> _EMU_TEMP_TEMP_SHIFT;
    val2 = (EMU->TEMP & _EMU_TEMP_TEMP_MASK)
           >> _EMU_TEMP_TEMP_SHIFT;
  } while (val1 != val2);

  return diTemp + tempCo * ((int) diEmu - (int) val1);
#endif
}
#endif // defined(_EMU_TEMP_TEMP_MASK)

#if defined(EMU_CTRL_EFPDIRECTMODEEN)
/***************************************************************************//**
 * @brief
 *   Enable/disable EFP Direct Mode.
 *
 * @param[in] enable
 *   True to enable direct mode.
 ******************************************************************************/
void EMU_EFPDirectModeEnable(bool enable)
{
  if (enable) {
    EMU->CTRL_SET = EMU_CTRL_EFPDIRECTMODEEN;
  } else {
    EMU->CTRL_CLR = EMU_CTRL_EFPDIRECTMODEEN;
  }
}
#endif

#if defined(EMU_CTRL_EFPDRVDECOUPLE)
/***************************************************************************//**
 * @brief
 *   Set to enable EFP to drive Decouple voltage.
 *
 * @details
 *   Once set, internal LDO will be disabled, and the EMU will control EFP for
 *   voltage-scaling. Note that because this bit disables the internal LDO
 *   powering the core, it should not be set until after EFP's DECOUPLE output has
 *   been configured and enabled.
 *
 * @param[in] enable
 *   True to enable EFP to drive Decouple voltage.
 ******************************************************************************/
void EMU_EFPDriveDecoupleSet(bool enable)
{
  if (enable) {
    EMU->CTRL_SET = EMU_CTRL_EFPDRVDECOUPLE;
  } else {
    EMU->CTRL_CLR = EMU_CTRL_EFPDRVDECOUPLE;
  }
}
#endif

#if defined(EMU_CTRL_EFPDRVDVDD)
/***************************************************************************//**
 * @brief
 *   Set to enable EFP to drive DVDD voltage.
 *
 * @details
 *   Set this if EFP's DCDC output is powering DVDD supply. This mode assumes that
 *   internal DCDC is not being used.
 *
 * @param[in] enable
 *   True to enable EFP to drive DVDD voltage.
 ******************************************************************************/
void EMU_EFPDriveDvddSet(bool enable)
{
  if (enable) {
    EMU->CTRL_SET = EMU_CTRL_EFPDRVDVDD;
  } else {
    EMU->CTRL_CLR = EMU_CTRL_EFPDRVDVDD;
  }
}
#endif

/** @} (end addtogroup emu) */
#endif /* __EM_EMU_H */
