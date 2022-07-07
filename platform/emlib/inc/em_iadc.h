/***************************************************************************//**
 * @file
 * @brief Incremental Analog to Digital Converter (IADC) peripheral API
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

#ifndef EM_IADC_H
#define EM_IADC_H

#include "em_device.h"
#include "em_gpio.h"
#if defined(IADC_COUNT) && (IADC_COUNT > 0)

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup iadc
 * @{
 ******************************************************************************/

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** Warm-up mode. */
typedef enum {
  /** IADC shutdown after each conversion. */
  iadcWarmupNormal        = _IADC_CTRL_WARMUPMODE_NORMAL,

  /** ADC is kept in standby mode between conversion.  */
  iadcWarmupKeepInStandby = _IADC_CTRL_WARMUPMODE_KEEPINSTANDBY,

  /** ADC and reference selected for scan mode kept warmup, allowing
      continuous conversion. */
  iadcWarmupKeepWarm      = _IADC_CTRL_WARMUPMODE_KEEPWARM
} IADC_Warmup_t;

/** IADC result alignment. */
typedef enum {
  /** IADC results 12-bit right aligned  */
  iadcAlignRight12 = _IADC_SCANFIFOCFG_ALIGNMENT_RIGHT12,

  /** IADC results 12-bit left aligned  */
  iadcAlignLeft12 = _IADC_SCANFIFOCFG_ALIGNMENT_LEFT12,

#if defined(IADC_SINGLEFIFOCFG_ALIGNMENT_RIGHT16)
  /** IADC results 16-bit right aligned  */
  iadcAlignRight16 = _IADC_SCANFIFOCFG_ALIGNMENT_RIGHT16,

  /** IADC results 16-bit left aligned  */
  iadcAlignLeft16 = _IADC_SCANFIFOCFG_ALIGNMENT_LEFT16,
#endif

#if defined(IADC_SINGLEFIFOCFG_ALIGNMENT_RIGHT20)
  /** IADC results 20-bit right aligned  */
  iadcAlignRight20 = _IADC_SCANFIFOCFG_ALIGNMENT_RIGHT20,

  /** IADC results 20-bit left aligned  */
  iadcAlignLeft20 = _IADC_SCANFIFOCFG_ALIGNMENT_LEFT20,
#endif
} IADC_Alignment_t;

/** IADC negative input selection. */
typedef enum {
  /** Ground  */
  iadcNegInputGnd     = (_IADC_SCAN_PORTNEG_GND << (_IADC_SCAN_PORTNEG_SHIFT - _IADC_SCAN_PINNEG_SHIFT))
                        | 1,
  /** Ground using even mux */
  iadcNegInputGndaux  = (_IADC_SCAN_PORTNEG_GND << (_IADC_SCAN_PORTNEG_SHIFT - _IADC_SCAN_PINNEG_SHIFT)),

#if defined(_IADC_SCAN_PORTNEG_DAC1)
  /** Direct connection to DAC_1 input pin */
  iadcNegInputDac1 = (_IADC_SCAN_PORTNEG_DAC1 << (_IADC_SCAN_PORTNEG_SHIFT - _IADC_SCAN_PINNEG_SHIFT)),
#endif
#if defined(_IADC_SCAN_PORTNEG_PADANA1)
  /** Direct connection to Pad_ana_1 input pin */
  iadcNegInputPadAna1 = (_IADC_SCAN_PORTNEG_PADANA1 << (_IADC_SCAN_PORTNEG_SHIFT - _IADC_SCAN_PINNEG_SHIFT)),
#endif
#if defined(_IADC_SCAN_PORTNEG_PADANA3)
  /** Direct connection to Pad_ana_3 input pin */
  iadcNegInputPadAna3 = (_IADC_SCAN_PORTNEG_PADANA3 << (_IADC_SCAN_PORTNEG_SHIFT - _IADC_SCAN_PINNEG_SHIFT)),
#endif
#if defined(_IADC_SCAN_PORTNEG_PADREFNEG)
  /** Negative reference pin 0  */
  iadcNegInputNegRef  = (_IADC_SCAN_PORTNEG_PADREFNEG << (_IADC_SCAN_PORTNEG_SHIFT - _IADC_SCAN_PINNEG_SHIFT)),
#endif
  /** GPIO port A pin 0 */
  iadcNegInputPortAPin0  = (_IADC_SCAN_PORTNEG_PORTA << (_IADC_SCAN_PORTNEG_SHIFT - _IADC_SCAN_PINNEG_SHIFT)),

  /** GPIO port A pin 1 */
  iadcNegInputPortAPin1,

  /** GPIO port A pin 2 */
  iadcNegInputPortAPin2,

  /** GPIO port A pin 3 */
  iadcNegInputPortAPin3,

  /** GPIO port A pin 4 */
  iadcNegInputPortAPin4,

  /** GPIO port A pin 5 */
  iadcNegInputPortAPin5,

  /** GPIO port A pin 6 */
  iadcNegInputPortAPin6,

  /** GPIO port A pin 7 */
  iadcNegInputPortAPin7,

  /** GPIO port A pin 8 */
  iadcNegInputPortAPin8,

  /** GPIO port A pin 9 */
  iadcNegInputPortAPin9,

  /** GPIO port A pin 10 */
  iadcNegInputPortAPin10,

  /** GPIO port A pin 11 */
  iadcNegInputPortAPin11,

  /** GPIO port A pin 12 */
  iadcNegInputPortAPin12,

  /** GPIO port A pin 13 */
  iadcNegInputPortAPin13,

  /** GPIO port A pin 14 */
  iadcNegInputPortAPin14,

  /** GPIO port A pin 15 */
  iadcNegInputPortAPin15,

  /** GPIO port B pin 0 */
  iadcNegInputPortBPin0,

  /** GPIO port B pin 1 */
  iadcNegInputPortBPin1,

  /** GPIO port B pin 2 */
  iadcNegInputPortBPin2,

  /** GPIO port B pin 3 */
  iadcNegInputPortBPin3,

  /** GPIO port B pin 4 */
  iadcNegInputPortBPin4,

  /** GPIO port B pin 5 */
  iadcNegInputPortBPin5,

  /** GPIO port B pin 6 */
  iadcNegInputPortBPin6,

  /** GPIO port B pin 7 */
  iadcNegInputPortBPin7,

  /** GPIO port B pin 8 */
  iadcNegInputPortBPin8,

  /** GPIO port B pin 9 */
  iadcNegInputPortBPin9,

  /** GPIO port B pin 10 */
  iadcNegInputPortBPin10,

  /** GPIO port B pin 11 */
  iadcNegInputPortBPin11,

  /** GPIO port B pin 12 */
  iadcNegInputPortBPin12,

  /** GPIO port B pin 13 */
  iadcNegInputPortBPin13,

  /** GPIO port B pin 14 */
  iadcNegInputPortBPin14,

  /** GPIO port B pin 15 */
  iadcNegInputPortBPin15,

  /** GPIO port C pin 0 */
  iadcNegInputPortCPin0,

  /** GPIO port C pin 1 */
  iadcNegInputPortCPin1,

  /** GPIO port C pin 2 */
  iadcNegInputPortCPin2,

  /** GPIO port C pin 3 */
  iadcNegInputPortCPin3,

  /** GPIO port C pin 4 */
  iadcNegInputPortCPin4,

  /** GPIO port C pin 5 */
  iadcNegInputPortCPin5,

  /** GPIO port C pin 6 */
  iadcNegInputPortCPin6,

  /** GPIO port C pin 7 */
  iadcNegInputPortCPin7,

  /** GPIO port C pin 8 */
  iadcNegInputPortCPin8,

  /** GPIO port C pin 9 */
  iadcNegInputPortCPin9,

  /** GPIO port C pin 10 */
  iadcNegInputPortCPin10,

  /** GPIO port C pin 11 */
  iadcNegInputPortCPin11,

  /** GPIO port C pin 12 */
  iadcNegInputPortCPin12,

  /** GPIO port C pin 13 */
  iadcNegInputPortCPin13,

  /** GPIO port C pin 14 */
  iadcNegInputPortCPin14,

  /** GPIO port C pin 15 */
  iadcNegInputPortCPin15,

  /** GPIO port D pin 0 */
  iadcNegInputPortDPin0,

  /** GPIO port D pin 1 */
  iadcNegInputPortDPin1,

  /** GPIO port D pin 2 */
  iadcNegInputPortDPin2,

  /** GPIO port D pin 3 */
  iadcNegInputPortDPin3,

  /** GPIO port D pin 4 */
  iadcNegInputPortDPin4,

  /** GPIO port D pin 5 */
  iadcNegInputPortDPin5,

  /** GPIO port D pin 6 */
  iadcNegInputPortDPin6,

  /** GPIO port D pin 7 */
  iadcNegInputPortDPin7,

  /** GPIO port D pin 8 */
  iadcNegInputPortDPin8,

  /** GPIO port D pin 9 */
  iadcNegInputPortDPin9,

  /** GPIO port D pin 10 */
  iadcNegInputPortDPin10,

  /** GPIO port D pin 11 */
  iadcNegInputPortDPin11,

  /** GPIO port D pin 12 */
  iadcNegInputPortDPin12,

  /** GPIO port D pin 13 */
  iadcNegInputPortDPin13,

  /** GPIO port D pin 14 */
  iadcNegInputPortDPin14,

  /** GPIO port D pin 15 */
  iadcNegInputPortDPin15
} IADC_NegInput_t;

/** IADC positive port selection. */
typedef enum {
  /** Ground  */
  iadcPosInputGnd       = (_IADC_SCAN_PORTPOS_GND << (_IADC_SCAN_PORTPOS_SHIFT - _IADC_SCAN_PINPOS_SHIFT)),

  /** Avdd  */
  iadcPosInputAvdd      = (_IADC_SCAN_PORTPOS_SUPPLY << (_IADC_SCAN_PORTPOS_SHIFT - _IADC_SCAN_PINPOS_SHIFT))
                          | 0,

  /** Vddio  */
  iadcPosInputVddio     = (_IADC_SCAN_PORTPOS_SUPPLY << (_IADC_SCAN_PORTPOS_SHIFT - _IADC_SCAN_PINPOS_SHIFT))
                          | 1,

  /** Vss  */
  iadcPosInputVss       = (_IADC_SCAN_PORTPOS_SUPPLY << (_IADC_SCAN_PORTPOS_SHIFT - _IADC_SCAN_PINPOS_SHIFT))
                          | 2,

  /** Vss  */
  iadcPosInputVssaux    = (_IADC_SCAN_PORTPOS_SUPPLY << (_IADC_SCAN_PORTPOS_SHIFT - _IADC_SCAN_PINPOS_SHIFT))
                          | 3,

  /** Dvdd  */
  iadcPosInputDvdd      = (_IADC_SCAN_PORTPOS_SUPPLY << (_IADC_SCAN_PORTPOS_SHIFT - _IADC_SCAN_PINPOS_SHIFT))
                          | 4,

  /** Decouple  */
  iadcPosInputDecouple  = (_IADC_SCAN_PORTPOS_SUPPLY << (_IADC_SCAN_PORTPOS_SHIFT - _IADC_SCAN_PINPOS_SHIFT))
                          | 7,

#if defined(_IADC_SCAN_PORTPOS_DAC0)
  /** Direct connection to DAC_0 input pin */
  iadcPosInputDac0      = (_IADC_SCAN_PORTPOS_DAC0 << (_IADC_SCAN_PORTPOS_SHIFT - _IADC_SCAN_PINPOS_SHIFT)),
#endif
#if defined(_IADC_SCAN_PORTPOS_PADANA0)
  /** Direct connection to Pad_ana_0 input pin */
  iadcPosInputPadAna0   = (_IADC_SCAN_PORTPOS_PADANA0 << (_IADC_SCAN_PORTPOS_SHIFT - _IADC_SCAN_PINPOS_SHIFT)),
#endif
#if defined(_IADC_SCAN_PORTPOS_PADANA2)
  /** Direct connection to Pad_ana_2 input pin */
  iadcPosInputPadAna2   = (_IADC_SCAN_PORTPOS_PADANA2 << (_IADC_SCAN_PORTPOS_SHIFT - _IADC_SCAN_PINPOS_SHIFT)),
#endif
#if defined(_IADC_SCAN_PORTPOS_PADREFPOS)
  /** Positive reference pin 0  */
  iadcPosInputPosRef    = (_IADC_SCAN_PORTPOS_PADREFPOS << (_IADC_SCAN_PORTPOS_SHIFT - _IADC_SCAN_PINPOS_SHIFT)),
#endif

  /** GPIO port A pin 0 */
  iadcPosInputPortAPin0 = (_IADC_SCAN_PORTPOS_PORTA << (_IADC_SCAN_PORTPOS_SHIFT - _IADC_SCAN_PINPOS_SHIFT)),

  /** GPIO port A pin 1 */
  iadcPosInputPortAPin1,

  /** GPIO port A pin 2 */
  iadcPosInputPortAPin2,

  /** GPIO port A pin 3 */
  iadcPosInputPortAPin3,

  /** GPIO port A pin 4 */
  iadcPosInputPortAPin4,

  /** GPIO port A pin 5 */
  iadcPosInputPortAPin5,

  /** GPIO port A pin 6 */
  iadcPosInputPortAPin6,

  /** GPIO port A pin 7 */
  iadcPosInputPortAPin7,

  /** GPIO port A pin 8 */
  iadcPosInputPortAPin8,

  /** GPIO port A pin 9 */
  iadcPosInputPortAPin9,

  /** GPIO port A pin 10 */
  iadcPosInputPortAPin10,

  /** GPIO port A pin 11 */
  iadcPosInputPortAPin11,

  /** GPIO port A pin 12 */
  iadcPosInputPortAPin12,

  /** GPIO port A pin 13 */
  iadcPosInputPortAPin13,

  /** GPIO port A pin 14 */
  iadcPosInputPortAPin14,

  /** GPIO port A pin 15 */
  iadcPosInputPortAPin15,

  /** GPIO port B pin 0 */
  iadcPosInputPortBPin0,

  /** GPIO port B pin 1 */
  iadcPosInputPortBPin1,

  /** GPIO port B pin 2 */
  iadcPosInputPortBPin2,

  /** GPIO port B pin 3 */
  iadcPosInputPortBPin3,

  /** GPIO port B pin 4 */
  iadcPosInputPortBPin4,

  /** GPIO port B pin 5 */
  iadcPosInputPortBPin5,

  /** GPIO port B pin 6 */
  iadcPosInputPortBPin6,

  /** GPIO port B pin 7 */
  iadcPosInputPortBPin7,

  /** GPIO port B pin 8 */
  iadcPosInputPortBPin8,

  /** GPIO port B pin 9 */
  iadcPosInputPortBPin9,

  /** GPIO port B pin 10 */
  iadcPosInputPortBPin10,

  /** GPIO port B pin 11 */
  iadcPosInputPortBPin11,

  /** GPIO port B pin 12 */
  iadcPosInputPortBPin12,

  /** GPIO port B pin 13 */
  iadcPosInputPortBPin13,

  /** GPIO port B pin 14 */
  iadcPosInputPortBPin14,

  /** GPIO port B pin 15 */
  iadcPosInputPortBPin15,

  /** GPIO port C pin 0 */
  iadcPosInputPortCPin0,

  /** GPIO port C pin 1 */
  iadcPosInputPortCPin1,

  /** GPIO port C pin 2 */
  iadcPosInputPortCPin2,

  /** GPIO port C pin 3 */
  iadcPosInputPortCPin3,

  /** GPIO port C pin 4 */
  iadcPosInputPortCPin4,

  /** GPIO port C pin 5 */
  iadcPosInputPortCPin5,

  /** GPIO port C pin 6 */
  iadcPosInputPortCPin6,

  /** GPIO port C pin 7 */
  iadcPosInputPortCPin7,

  /** GPIO port C pin 8 */
  iadcPosInputPortCPin8,

  /** GPIO port C pin 9 */
  iadcPosInputPortCPin9,

  /** GPIO port C pin 10 */
  iadcPosInputPortCPin10,

  /** GPIO port C pin 11 */
  iadcPosInputPortCPin11,

  /** GPIO port C pin 12 */
  iadcPosInputPortCPin12,

  /** GPIO port C pin 13 */
  iadcPosInputPortCPin13,

  /** GPIO port C pin 14 */
  iadcPosInputPortCPin14,

  /** GPIO port C pin 15 */
  iadcPosInputPortCPin15,

  /** GPIO port D pin 0 */
  iadcPosInputPortDPin0,

  /** GPIO port D pin 1 */
  iadcPosInputPortDPin1,

  /** GPIO port D pin 2 */
  iadcPosInputPortDPin2,

  /** GPIO port D pin 3 */
  iadcPosInputPortDPin3,

  /** GPIO port D pin 4 */
  iadcPosInputPortDPin4,

  /** GPIO port D pin 5 */
  iadcPosInputPortDPin5,

  /** GPIO port D pin 6 */
  iadcPosInputPortDPin6,

  /** GPIO port D pin 7 */
  iadcPosInputPortDPin7,

  /** GPIO port D pin 8 */
  iadcPosInputPortDPin8,

  /** GPIO port D pin 9 */
  iadcPosInputPortDPin9,

  /** GPIO port D pin 10 */
  iadcPosInputPortDPin10,

  /** GPIO port D pin 11 */
  iadcPosInputPortDPin11,

  /** GPIO port D pin 12 */
  iadcPosInputPortDPin12,

  /** GPIO port D pin 13 */
  iadcPosInputPortDPin13,

  /** GPIO port D pin 14 */
  iadcPosInputPortDPin14,

  /** GPIO port D pin 15 */
  iadcPosInputPortDPin15
} IADC_PosInput_t;

/** IADC Commands. */
typedef enum {
  /** Start single queue  */
  iadcCmdStartSingle  = IADC_CMD_SINGLESTART,

  /** Stop single queue  */
  iadcCmdStopSingle   = IADC_CMD_SINGLESTOP,

  /** Start scan queue  */
  iadcCmdStartScan    = IADC_CMD_SCANSTART,

  /** Stop scan queue  */
  iadcCmdStopScan     = IADC_CMD_SCANSTOP,

  /** Enable Timer  */
  iadcCmdEnableTimer  = IADC_CMD_TIMEREN,

  /** Disable Timer  */
  iadcCmdDisableTimer = IADC_CMD_TIMERDIS
} IADC_Cmd_t;

/** IADC Configuration. */
typedef enum {
  /** Normal mode  */
  iadcCfgModeNormal        = _IADC_CFG_ADCMODE_NORMAL,
#if defined(_IADC_CFG_ADCMODE_HIGHSPEED)
  /** High Speed mode  */
  iadcCfgModeHighSpeed     = _IADC_CFG_ADCMODE_HIGHSPEED,
#endif
#if defined(_IADC_CFG_ADCMODE_HIGHACCURACY)
  /** High Accuracy mode  */
  iadcCfgModeHighAccuracy  = _IADC_CFG_ADCMODE_HIGHACCURACY
#endif
} IADC_CfgAdcMode_t;

/** IADC Over sampling rate for high speed. */
typedef enum {
  /** High speed oversampling of 2x */
  iadcCfgOsrHighSpeed2x  = _IADC_CFG_OSRHS_HISPD2,

  /** High speed oversampling of 4x */
  iadcCfgOsrHighSpeed4x  = _IADC_CFG_OSRHS_HISPD4,

  /** High speed oversampling of 8x */
  iadcCfgOsrHighSpeed8x  = _IADC_CFG_OSRHS_HISPD8,

  /** High speed oversampling of 16x */
  iadcCfgOsrHighSpeed16x  = _IADC_CFG_OSRHS_HISPD16,

  /** High speed oversampling of 32x */
  iadcCfgOsrHighSpeed32x  = _IADC_CFG_OSRHS_HISPD32,

  /** High speed oversampling of 64x */
  iadcCfgOsrHighSpeed64x  = _IADC_CFG_OSRHS_HISPD64
} IADC_CfgOsrHighSpeed_t;

#if defined(_IADC_CFG_ADCMODE_HIGHACCURACY)
/** IADC Over sampling rate for high accuracy. */
typedef enum {
  /** High accuracy oversampling of 16x */
  iadcCfgOsrHighAccuracy16x  = _IADC_CFG_OSRHA_HIACC16,

  /** High accuracy oversampling of 32x */
  iadcCfgOsrHighAccuracy32x  = _IADC_CFG_OSRHA_HIACC32,

  /** High accuracy oversampling of 64x */
  iadcCfgOsrHighAccuracy64x  = _IADC_CFG_OSRHA_HIACC64,

  /** High accuracy oversampling of 92x */
  iadcCfgOsrHighAccuracy92x  = _IADC_CFG_OSRHA_HIACC92,

  /** High accuracy oversampling of 128x */
  iadcCfgOsrHighAccuracy128x  = _IADC_CFG_OSRHA_HIACC128,

  /** High accuracy oversampling of 256x */
  iadcCfgOsrHighAccuracy256x  = _IADC_CFG_OSRHA_HIACC256
} IADC_CfgOsrHighAccuracy_t;
#endif

/** IADC Analog Gain. */
typedef enum {
#if defined(_IADC_CFG_ANALOGGAIN_ANAGAIN0P25)
  /** Analog gain of 0.25x */
  iadcCfgAnalogGain0P25x  = _IADC_CFG_ANALOGGAIN_ANAGAIN0P25,
#endif
  /** Analog gain of 0.5x */
  iadcCfgAnalogGain0P5x  = _IADC_CFG_ANALOGGAIN_ANAGAIN0P5,

  /** Analog gain of 1x */
  iadcCfgAnalogGain1x    = _IADC_CFG_ANALOGGAIN_ANAGAIN1,

  /** Analog gain of 2x */
  iadcCfgAnalogGain2x    = _IADC_CFG_ANALOGGAIN_ANAGAIN2,

  /** Analog gain of 3x */
  iadcCfgAnalogGain3x    = _IADC_CFG_ANALOGGAIN_ANAGAIN3,

  /** Analog gain of 4x */
  iadcCfgAnalogGain4x    = _IADC_CFG_ANALOGGAIN_ANAGAIN4
} IADC_CfgAnalogGain_t;

/** IADC Reference */
typedef enum {
  /** Internal 1.2V Band Gap Reference (buffered) to ground */
  iadcCfgReferenceInt1V2     = _IADC_CFG_REFSEL_VBGR,

  /** External reference (unbuffered) VREFP to VREFN. Up to 1.25V. */
  iadcCfgReferenceExt1V25    = _IADC_CFG_REFSEL_VREF,

#if defined(_IADC_CFG_REFSEL_VREF2P5)
  /** External reference (unbuffered) VREFP to VREFN. Up to 1.25V. */
  iadcCfgReferenceExt2V5     = _IADC_CFG_REFSEL_VREF2P5,
#endif

  /** VDDX (unbuffered) to ground. */
  iadcCfgReferenceVddx       = _IADC_CFG_REFSEL_VDDX,

  /** 0.8 * VDDX (buffered) to ground. */
  iadcCfgReferenceVddX0P8Buf = _IADC_CFG_REFSEL_VDDX0P8BUF,

#if defined(_IADC_CFG_REFSEL_VREFBUF)
  /** pad_vrefp (buffered) to pad_vrefn (pad_refp < vddx - 0.3) */
  iadcCfgReferenceBuf        = _IADC_CFG_REFSEL_VREFBUF,
#endif

#if defined(_IADC_CFG_REFSEL_VREF0P8BUF)
  /** pad_vref (buffered) * 0.8 to pad_vrefn (LPF pad_refp noise) */
  iadcCfgReference0P8Buf     = _IADC_CFG_REFSEL_VREF0P8BUF,
#endif
} IADC_CfgReference_t;

/** IADC Two's complement results */
typedef enum {
  /** Automatic. Single ended => Unipolar, Differential => Bipolar */
  iadcCfgTwosCompAuto     = _IADC_CFG_TWOSCOMPL_AUTO,

  /** All results in unipolar format. Negative diff input gives 0 as result. */
  iadcCfgTwosCompUnipolar = _IADC_CFG_TWOSCOMPL_FORCEUNIPOLAR,

  /** All results in bipolar (2's complement) format. Half range for SE. */
  iadcCfgTwosCompBipolar  = _IADC_CFG_TWOSCOMPL_FORCEBIPOLAR
} IADC_CfgTwosComp_t;

/** IADC trigger action */
typedef enum {
  /** Start single/scan queue immediately */
  iadcTriggerSelImmediate  = _IADC_TRIGGER_SCANTRIGSEL_IMMEDIATE,

  /** Timer starts single/scan queue */
  iadcTriggerSelTimer  = _IADC_TRIGGER_SCANTRIGSEL_TIMER,

  /** PRS0 from timer in same clock group starts single/scan queue  */
  iadcTriggerSelPrs0SameClk  = _IADC_TRIGGER_SCANTRIGSEL_PRSCLKGRP,

  /** PRS0 positive edge starts single/scan queue  */
  iadcTriggerSelPrs0PosEdge  = _IADC_TRIGGER_SCANTRIGSEL_PRSPOS,

  /** PRS0 negative edge starts single/scan queue  */
  iadcTriggerSelPrs0NegEdge  = _IADC_TRIGGER_SCANTRIGSEL_PRSNEG,

#if defined(_IADC_TRIGGER_SCANTRIGSEL_LESENSE)
  /** LESENSE starts scan queue  */
  iadcTriggerSelLesense  = _IADC_TRIGGER_SCANTRIGSEL_LESENSE
#endif
} IADC_TriggerSel_t;

/** IADC trigger action */
typedef enum {
  /** Convert single/scan queue once per trigger  */
  iadcTriggerActionOnce  = _IADC_TRIGGER_SCANTRIGACTION_ONCE,

  /** Convert single/scan queue continuously  */
  iadcTriggerActionContinuous  = _IADC_TRIGGER_SCANTRIGACTION_CONTINUOUS,
} IADC_TriggerAction_t;

/** IADC data valid level before requesting DMA transfer */
typedef enum {
  /** Data valid level is 1 before requesting DMA transfer */
  iadcFifoCfgDvl1  = _IADC_SCANFIFOCFG_DVL_VALID1,

  /** Data valid level is 2 before requesting DMA transfer */
  iadcFifoCfgDvl2  = _IADC_SCANFIFOCFG_DVL_VALID2,

  /** Data valid level is 3 before requesting DMA transfer */
  iadcFifoCfgDvl3  = _IADC_SCANFIFOCFG_DVL_VALID3,

  /** Data valid level is 4 before requesting DMA transfer */
  iadcFifoCfgDvl4  = _IADC_SCANFIFOCFG_DVL_VALID4,

#if _SILICON_LABS_32B_SERIES_2_CONFIG > 2
  /** Data valid level is 5 before requesting DMA transfer */
  iadcFifoCfgDvl5  = _IADC_SCANFIFOCFG_DVL_VALID5,

  /** Data valid level is 6 before requesting DMA transfer */
  iadcFifoCfgDvl6  = _IADC_SCANFIFOCFG_DVL_VALID6,

  /** Data valid level is 7 before requesting DMA transfer */
  iadcFifoCfgDvl7  = _IADC_SCANFIFOCFG_DVL_VALID7,
#endif

#if _SILICON_LABS_32B_SERIES_2_CONFIG > 3
  /** Data valid level is 8 before requesting DMA transfer */
  iadcFifoCfgDvl8  = _IADC_SCANFIFOCFG_DVL_VALID8
#endif
} IADC_FifoCfgDvl_t;

#if defined(_IADC_CFG_DIGAVG_MASK)
/** IADC digital averaging function. */
typedef enum {
  /** Average over 1 sample (no averaging). */
  iadcDigitalAverage1 = _IADC_CFG_DIGAVG_AVG1,

  /** Average over 2 samples. */
  iadcDigitalAverage2 = _IADC_CFG_DIGAVG_AVG2,

  /** Average over 4 samples. */
  iadcDigitalAverage4 = _IADC_CFG_DIGAVG_AVG4,

  /** Average over 8 samples. */
  iadcDigitalAverage8 = _IADC_CFG_DIGAVG_AVG8,

  /** Average over 16 samples. */
  iadcDigitalAverage16 = _IADC_CFG_DIGAVG_AVG16
} IADC_DigitalAveraging_t;
#endif

/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** IADC init structure, common for single conversion and scan sequence. */
typedef struct {
  bool                          iadcClkSuspend0;       /**< Suspend IADC_CLK until PRS0 trigger. */
  bool                          iadcClkSuspend1;       /**< Suspend IADC_CLK until PRS1 trigger. */
  bool                          debugHalt;             /**< Halt IADC during debug mode. */
  IADC_Warmup_t                 warmup;                /**< IADC warmup mode. */
  uint8_t                       timebase;              /**< IADC clock cycles (timebase+1) corresponding to 1us.
                                                          Used as time reference for IADC delays, e.g. warmup.
                                                          If the user sets timebase to 0, then IADC_Init() will
                                                          calculate the timebase using the currently defined CMU
                                                          clock setting for the IADC. */
  uint8_t                       srcClkPrescale;        /**< User requested source clock divider (prescale+1) which
                                                          will be used if the calculated prescaler value is less. */
  uint16_t                      timerCycles;           /**< Number of ADC_CLK cycles per TIMER event. */
  uint16_t                      greaterThanEqualThres; /**< Digital window comparator greater-than or equal threshold. */
  uint16_t                      lessThanEqualThres;    /**< Digital window comparator less-than or equal threshold. */
} IADC_Init_t;

/** Default config for IADC init structure. */
#define IADC_INIT_DEFAULT                                                   \
  {                                                                         \
    false,                       /* IADC clock not disabled on PRS0*/       \
    false,                       /* IADC clock not disabled on PRS1 */      \
    false,                       /* Do not halt during debug */             \
    iadcWarmupNormal,            /* IADC shutdown after each conversion. */ \
    0,                           /* Calculate timebase. */                  \
    0,                           /* Max IADC clock rate. */                 \
    _IADC_TIMER_TIMER_DEFAULT,   /* Use HW default value. */                \
    _IADC_CMPTHR_ADGT_DEFAULT,   /* Use HW default value. */                \
    _IADC_CMPTHR_ADLT_DEFAULT,   /* Use HW default value. */                \
  }

/** IADC config structure */
typedef struct {
  IADC_CfgAdcMode_t          adcMode;         /**< IADC mode; Normal, High speed or High Accuracy. */
  IADC_CfgOsrHighSpeed_t     osrHighSpeed;    /**< Over sampling ratio for High Speed and Normal modes. */
#if defined(_IADC_CFG_ADCMODE_HIGHACCURACY)
  IADC_CfgOsrHighAccuracy_t  osrHighAccuracy; /**< Over sampling ratio for High Accuracy mode. */
#endif
  IADC_CfgAnalogGain_t       analogGain;      /**< Analog gain. */
  IADC_CfgReference_t        reference;       /**< Reference selection. */
  IADC_CfgTwosComp_t         twosComplement;  /**< Two's complement reporting. */
  uint32_t                   adcClkPrescale;  /**< ADC_CLK divider (prescale+1). */
  uint32_t                   vRef;            /**< Vref magnitude expressed in millivolts. */
#if defined(_IADC_CFG_DIGAVG_MASK)
  IADC_DigitalAveraging_t    digAvg;          /**< Digital average mode. */
#endif
} IADC_Config_t;

#if defined(_IADC_CFG_DIGAVG_MASK)
#if defined(_IADC_CFG_ADCMODE_HIGHACCURACY)
/** Default IADC config structure. */
#define IADC_CONFIG_DEFAULT                                               \
  {                                                                       \
    iadcCfgModeNormal,            /* Normal mode for IADC. */             \
    iadcCfgOsrHighSpeed2x,        /* 2x high speed over sampling. */      \
    iadcCfgOsrHighAccuracy92x,    /* 92x high accuracy over sampling. */  \
    iadcCfgAnalogGain1x,          /* 1x analog gain. */                   \
    iadcCfgReferenceInt1V2,       /* Internal 1.2V band gap reference. */ \
    iadcCfgTwosCompAuto,          /* Automatic Two's Complement. */       \
    0,                            /* Max IADC analog clock rate. */       \
    1210,                         /* Vref expressed in millivolts. */     \
    iadcDigitalAverage1           /* No averaging. */                     \
  }
#else
/** Default IADC config structure. */
#define IADC_CONFIG_DEFAULT                                               \
  {                                                                       \
    iadcCfgModeNormal,            /* Normal mode for IADC. */             \
    iadcCfgOsrHighSpeed2x,        /* 2x high speed over sampling. */      \
    iadcCfgAnalogGain1x,          /* 1x analog gain. */                   \
    iadcCfgReferenceInt1V2,       /* Internal 1.2V band gap reference. */ \
    iadcCfgTwosCompAuto,          /* Automatic Two's Complement. */       \
    0,                            /* Max IADC analog clock rate. */       \
    1210,                         /* Vref expressed in millivolts. */     \
    iadcDigitalAverage1           /* No averaging. */                     \
  }
#endif
#else
#if defined(_IADC_CFG_ADCMODE_HIGHACCURACY)
/** Default IADC config structure. */
#define IADC_CONFIG_DEFAULT                                               \
  {                                                                       \
    iadcCfgModeNormal,            /* Normal mode for IADC. */             \
    iadcCfgOsrHighSpeed2x,        /* 2x high speed over sampling. */      \
    iadcCfgOsrHighAccuracy92x,    /* 92x high speed over sampling. */     \
    iadcCfgAnalogGain1x,          /* 1x analog gain. */                   \
    iadcCfgReferenceInt1V2,       /* Internal 1.2V band gap reference. */ \
    iadcCfgTwosCompAuto,          /* Automatic Two's Complement. */       \
    0,                            /* Max IADC analog clock rate. */       \
    1210                          /* Vref expressed in millivolts. */     \
  }
#else
/** Default IADC config structure. */
#define IADC_CONFIG_DEFAULT                                               \
  {                                                                       \
    iadcCfgModeNormal,            /* Normal mode for IADC. */             \
    iadcCfgOsrHighSpeed2x,        /* 2x high speed over sampling. */      \
    iadcCfgAnalogGain1x,          /* 1x analog gain. */                   \
    iadcCfgReferenceInt1V2,       /* Internal 1.2V band gap reference. */ \
    iadcCfgTwosCompAuto,          /* Automatic Two's Complement. */       \
    0,                            /* Max IADC analog clock rate. */       \
    1210                          /* Vref expressed in millivolts. */     \
  }
#endif
#endif

/** Structure for all IADC configs. */
typedef struct {
  /** All IADC configs. */
  IADC_Config_t configs[IADC0_CONFIGNUM];
} IADC_AllConfigs_t;

/** Default IADC sructure for all configs. */
#define IADC_ALLCONFIGS_DEFAULT \
  {                             \
    {                           \
      IADC_CONFIG_DEFAULT,      \
      IADC_CONFIG_DEFAULT       \
    }                           \
  }

/** IADC scan init structure */
typedef struct {
  IADC_Alignment_t            alignment;      /**< Alignment of data in FIFO. */
  bool                        showId;         /**< Tag FIFO entry with scan table entry id. */
  IADC_FifoCfgDvl_t           dataValidLevel; /**< Data valid level before requesting DMA transfer. */
  bool                        fifoDmaWakeup;  /**< Wake-up DMA when FIFO reaches data valid level. */
  IADC_TriggerSel_t           triggerSelect;  /**< Trigger selection. */
  IADC_TriggerAction_t        triggerAction;  /**< Trigger action. */
  bool                        start;          /**< Start scan immediately. */
} IADC_InitScan_t;

/** Default config for IADC scan init structure. */
#define IADC_INITSCAN_DEFAULT                                                \
  {                                                                          \
    iadcAlignRight12,              /* Results 12-bit right aligned */        \
    false,                         /* Do not show ID in result */            \
    iadcFifoCfgDvl4,               /* Use HW default value. */               \
    false,                         /* Do not wake up DMA on scan FIFO DVL */ \
    iadcTriggerSelImmediate,       /* Start scan immediately on trigger */   \
    iadcTriggerActionOnce,         /* Convert once on scan trigger */        \
    false                          /* Do not start scan queue */             \
  }

/** IADC single init structure */
typedef struct {
  IADC_Alignment_t              alignment;      /**< Alignment of data in FIFO. */
  bool                          showId;         /**< Tag FIFO entry with single indicator (0x20). */
  IADC_FifoCfgDvl_t             dataValidLevel; /**< Data valid level before requesting DMA transfer. */
  bool                          fifoDmaWakeup;  /**< Wake-up DMA when FIFO reaches data valid level. */
  IADC_TriggerSel_t             triggerSelect;  /**< Trigger selection. */
  IADC_TriggerAction_t          triggerAction;  /**< Trigger action. */
  bool                          singleTailgate; /**< If true, wait until end of SCAN queue
                                                   before single queue warmup and conversion. */
  bool                          start;          /**< Start scan immediately. */
} IADC_InitSingle_t;

/** Default config for IADC single init structure. */
#define IADC_INITSINGLE_DEFAULT                                                  \
  {                                                                              \
    iadcAlignRight12,                /* Results 12-bit right aligned */          \
    false,                           /* Do not show ID in result */              \
    iadcFifoCfgDvl4,                 /* Use HW default value. */                 \
    false,                           /* Do not wake up DMA on single FIFO DVL */ \
    iadcTriggerSelImmediate,         /* Start single immediately on trigger */   \
    iadcTriggerActionOnce,           /* Convert once on single trigger */        \
    false,                           /* No tailgating */                         \
    false                            /* Do not start single queue */             \
  }

/** IADC single input selection structure */
typedef struct {
  IADC_NegInput_t         negInput; /**< Port/pin input for the negative side of the ADC.  */
  IADC_PosInput_t         posInput; /**< Port/pin input for the positive side of the ADC.  */
  uint8_t                 configId; /**< Configuration id. */
  bool                    compare;  /**< Perform digital window comparison on the result from this entry. */
} IADC_SingleInput_t;

/** Default config for IADC single input structure. */
#define IADC_SINGLEINPUT_DEFAULT                              \
  {                                                           \
    iadcNegInputGnd,             /* Negative input GND */     \
    iadcPosInputGnd,             /* Positive input GND */     \
    0,                           /* Config 0 */               \
    false                        /* Do not compare results */ \
  }

/** IADC scan table entry structure */
typedef struct {
  IADC_NegInput_t       negInput; /**< Port/pin input for the negative side of the ADC.  */
  IADC_PosInput_t       posInput; /**< Port/pin input for the positive side of the ADC.  */
  uint8_t               configId; /**< Configuration id. */
  bool                  compare;  /**< Perform digital window comparison on the result from this entry. */
  bool                  includeInScan; /**< Include this scan table entry in scan operation. */
} IADC_ScanTableEntry_t;

/** Default config for IADC scan table entry structure. */
#define IADC_SCANTABLEENTRY_DEFAULT              \
  {                                              \
    iadcNegInputGnd,/* Negative input GND */     \
    iadcPosInputGnd,/* Positive input GND */     \
    0,              /* Config 0 */               \
    false,          /* Do not compare results */ \
    false           /* Do not include in scan */ \
  }

/** Structure for IADC scan table. */
typedef struct {
  /** IADC scan table entries. */
  IADC_ScanTableEntry_t entries[IADC0_ENTRIES];
} IADC_ScanTable_t;

/** Default IADC structure for scan table */
#define IADC_SCANTABLE_DEFAULT     \
  {                                \
    {                              \
      IADC_SCANTABLEENTRY_DEFAULT, \
      IADC_SCANTABLEENTRY_DEFAULT, \
      IADC_SCANTABLEENTRY_DEFAULT, \
      IADC_SCANTABLEENTRY_DEFAULT, \
      IADC_SCANTABLEENTRY_DEFAULT, \
      IADC_SCANTABLEENTRY_DEFAULT, \
      IADC_SCANTABLEENTRY_DEFAULT, \
      IADC_SCANTABLEENTRY_DEFAULT, \
      IADC_SCANTABLEENTRY_DEFAULT, \
      IADC_SCANTABLEENTRY_DEFAULT, \
      IADC_SCANTABLEENTRY_DEFAULT, \
      IADC_SCANTABLEENTRY_DEFAULT, \
      IADC_SCANTABLEENTRY_DEFAULT, \
      IADC_SCANTABLEENTRY_DEFAULT, \
      IADC_SCANTABLEENTRY_DEFAULT, \
      IADC_SCANTABLEENTRY_DEFAULT  \
    }                              \
  }

/** Structure holding IADC result, including data and ID */
typedef struct {
  uint32_t data;  /**< ADC sample data. */
  uint8_t  id;    /**< Id of FIFO entry; Scan table entry id or single indicator (0x20). */
} IADC_Result_t;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

void IADC_init(IADC_TypeDef *iadc, const IADC_Init_t *init,
               const IADC_AllConfigs_t *allConfigs);
void IADC_reset(IADC_TypeDef *iadc);
void IADC_initScan(IADC_TypeDef *iadc,
                   const IADC_InitScan_t *init,
                   const IADC_ScanTable_t *scanTable);
void IADC_updateScanEntry(IADC_TypeDef *iadc,
                          uint8_t id,
                          IADC_ScanTableEntry_t *entry);
void IADC_setScanMask(IADC_TypeDef *iadc, uint32_t mask);
void IADC_initSingle(IADC_TypeDef *iadc,
                     const IADC_InitSingle_t *init,
                     const IADC_SingleInput_t *input);
void IADC_updateSingleInput(IADC_TypeDef *iadc,
                            const IADC_SingleInput_t *input);
uint8_t IADC_calcSrcClkPrescale(IADC_TypeDef *iadc,
                                uint32_t srcClkFreq,
                                uint32_t cmuClkFreq);
uint32_t IADC_calcAdcClkPrescale(IADC_TypeDef *iadc,
                                 uint32_t adcClkFreq,
                                 uint32_t cmuClkFreq,
                                 IADC_CfgAdcMode_t adcMode,
                                 uint8_t srcClkPrescaler);
uint8_t IADC_calcTimebase(IADC_TypeDef *iadc, uint32_t cmuClkFreq);
IADC_Result_t IADC_readSingleResult(IADC_TypeDef *iadc);
IADC_Result_t IADC_pullSingleFifoResult(IADC_TypeDef *iadc);
IADC_Result_t IADC_readScanResult(IADC_TypeDef *iadc);
IADC_Result_t IADC_pullScanFifoResult(IADC_TypeDef *iadc);

/***************************************************************************//**
 * @brief
 *   Pull data from single data FIFO. If showId was set when initializing
 *   single mode, the results will contain the ID (0x20).
 *
 * @note
 *   Check data valid flag before calling this function.
 *
 * @param[in] iadc
 *   Pointer to IADC peripheral register block.
 *
 * @return
 *   Single conversion data.
 ******************************************************************************/
__STATIC_INLINE uint32_t IADC_pullSingleFifoData(IADC_TypeDef *iadc)
{
  return iadc->SINGLEFIFODATA;
}

/***************************************************************************//**
 * @brief
 *   Read most recent single conversion data. If showId was set when
 *   initializing single mode, the data will contain the ID (0x20). Calling
 *   this function will not affect the state of the single data FIFO.
 *
 * @note
 *   Check data valid flag before calling this function.
 *
 * @param[in] iadc
 *   Pointer to IADC peripheral register block.
 *
 * @return
 *   Single conversion data.
 ******************************************************************************/
__STATIC_INLINE uint32_t IADC_readSingleData(IADC_TypeDef *iadc)
{
  return iadc->SINGLEDATA;
}

/***************************************************************************//**
 * @brief
 *   Pull data from scan data FIFO. If showId was set for the scan entry
 *   initialization, the data will contain the ID of the scan entry.
 *
 * @note
 *   Check data valid flag before calling this function.
 *
 * @param[in] iadc
 *   Pointer to IADC peripheral register block.
 *
 * @return
 *   Scan conversion data.
 ******************************************************************************/
__STATIC_INLINE uint32_t IADC_pullScanFifoData(IADC_TypeDef *iadc)
{
  return iadc->SCANFIFODATA;
}

/***************************************************************************//**
 * @brief
 *   Read most recent scan conversion data. If showId was set for the scan
 *   entry initialization, the data will contain the ID of the scan entry.
 *   Calling this function will not affect the state of the scan data FIFO.
 *
 * @note
 *   Check data valid flag before calling this function.
 *
 * @param[in] iadc
 *   Pointer to IADC peripheral register block.
 *
 * @return
 *   Scan conversion data.
 ******************************************************************************/
__STATIC_INLINE uint32_t IADC_readScanData(IADC_TypeDef *iadc)
{
  return iadc->SCANDATA;
}

/***************************************************************************//**
 * @brief
 *   Clear one or more pending IADC interrupts.
 *
 * @param[in] iadc
 *   Pointer to IADC peripheral register block.
 *
 * @param[in] flags
 *   Pending IADC interrupt source to clear. Use a bitwise logic OR combination
 *   of valid interrupt flags for the IADC module (IADC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void IADC_clearInt(IADC_TypeDef *iadc, uint32_t flags)
{
  iadc->IF_CLR = flags;
}

/***************************************************************************//**
 * @brief
 *   Disable one or more IADC interrupts.
 *
 * @param[in] iadc
 *   Pointer to IADC peripheral register block.
 *
 * @param[in] flags
 *   IADC interrupt sources to disable. Use a bitwise logic OR combination of
 *   valid interrupt flags for the IADC module (IADC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void IADC_disableInt(IADC_TypeDef *iadc, uint32_t flags)
{
#if defined (IADC_HAS_SET_CLEAR)
  iadc->IEN_CLR = flags;
#else
  iadc->IEN &= ~flags;
#endif
}

/***************************************************************************//**
 * @brief
 *   Enable one or more IADC interrupts.
 *
 * @note
 *   Depending on the use, a pending interrupt may already be set prior to
 *   enabling the interrupt. Consider using IADC_intClear() prior to enabling
 *   if such a pending interrupt should be ignored.
 *
 * @param[in] iadc
 *   Pointer to IADC peripheral register block.
 *
 * @param[in] flags
 *   IADC interrupt sources to enable. Use a bitwise logic OR combination of
 *   valid interrupt flags for the IADC module (IADC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void IADC_enableInt(IADC_TypeDef *iadc, uint32_t flags)
{
  iadc->IEN |= flags;
}

/***************************************************************************//**
 * @brief
 *   Get pending IADC interrupt flags.
 *
 * @note
 *   The event bits are not cleared by the use of this function.
 *
 * @param[in] iadc
 *   Pointer to IADC peripheral register block.
 *
 * @return
 *   IADC interrupt sources pending. A bitwise logic OR combination of valid
 *   interrupt flags for the IADC module (IADC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t IADC_getInt(IADC_TypeDef *iadc)
{
  return iadc->IF;
}

/***************************************************************************//**
 * @brief
 *   Get enabled and pending IADC interrupt flags.
 *   Useful for handling more interrupt sources in the same interrupt handler.
 *
 * @note
 *   Interrupt flags are not cleared by the use of this function.
 *
 * @param[in] iadc
 *   Pointer to IADC peripheral register block.
 *
 * @return
 *   Pending and enabled IADC interrupt sources.
 *   The return value is the bitwise AND combination of
 *   - the OR combination of enabled interrupt sources in IADCx_IEN_nnn
 *     register (IADCx_IEN_nnn) and
 *   - the OR combination of valid interrupt flags of the IADC module
 *     (IADCx_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t IADC_getEnabledInt(IADC_TypeDef *iadc)
{
  uint32_t ien;

  /* Store IADCx->IEN in temporary variable in order to define explicit order
   * of volatile accesses. */
  ien = iadc->IEN;

  /* Bitwise AND of pending and enabled interrupts */
  return iadc->IF & ien;
}

/***************************************************************************//**
 * @brief
 *   Set one or more pending IADC interrupts from SW.
 *
 * @param[in] iadc
 *   Pointer to IADC peripheral register block.
 *
 * @param[in] flags
 *   IADC interrupt sources to set to pending. Use a bitwise logic OR combination
 *   of valid interrupt flags for the IADC module (IADC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void IADC_setInt(IADC_TypeDef *iadc, uint32_t flags)
{
  iadc->IF_SET = flags;
}

/***************************************************************************//**
 * @brief
 *   Start/stop scan sequence, single conversion and/or timer.
 *
 * @param[in] iadc
 *   Pointer to IADC peripheral register block.
 *
 * @param[in] cmd
 *   Command to be performed.
 ******************************************************************************/
__STATIC_INLINE void IADC_command(IADC_TypeDef *iadc, IADC_Cmd_t cmd)
{
  iadc->CMD = (uint32_t)cmd;
}

/***************************************************************************//**
 * @brief
 *   Get the scan mask currently used in the IADC.
 *
 * @param[in] iadc
 *   Pointer to IADC peripheral register block.
 *
 * @return
 *   Mask of scan table entries currently included in scan.
 ******************************************************************************/
__STATIC_INLINE uint32_t IADC_getScanMask(IADC_TypeDef *iadc)
{
  return (iadc->STMASK) >> _IADC_STMASK_STMASK_SHIFT;
}

/***************************************************************************//**
 * @brief
 *   Get status bits of IADC.
 *
 * @param[in] iadc
 *   Pointer to IADC peripheral register block.
 *
 * @return
 *   IADC status bits
 ******************************************************************************/
__STATIC_INLINE uint32_t IADC_getStatus(IADC_TypeDef *iadc)
{
  return iadc->STATUS;
}

/***************************************************************************//**
 * @brief
 *   Get the number of elements in the IADC single FIFO.
 *
 * @param[in] iadc
 *   Pointer to IADC peripheral register block.
 *
 * @return
 *   Number of elements in single FIFO
 ******************************************************************************/
__STATIC_INLINE uint8_t IADC_getSingleFifoCnt(IADC_TypeDef *iadc)
{
  return (uint8_t) ((iadc->SINGLEFIFOSTAT & _IADC_SINGLEFIFOSTAT_FIFOREADCNT_MASK)
                    >> _IADC_SINGLEFIFOSTAT_FIFOREADCNT_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Get the number of elements in the IADC scan FIFO.
 *
 * @param[in] iadc
 *   Pointer to IADC peripheral register block.
 *
 * @return
 *   Number of elements in scan FIFO
 ******************************************************************************/
__STATIC_INLINE uint8_t IADC_getScanFifoCnt(IADC_TypeDef *iadc)
{
  return (uint8_t) ((iadc->SCANFIFOSTAT & _IADC_SCANFIFOSTAT_FIFOREADCNT_MASK)
                    >> _IADC_SCANFIFOSTAT_FIFOREADCNT_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Convert the GPIO port/pin to IADC negative input selection.
 *
 * @param[in] port
 *   GPIO port
 *
 * @param[in] pin
 *   GPIO in
 *
 * @return
 *   IADC negative input selection
 ******************************************************************************/
__STATIC_INLINE IADC_NegInput_t IADC_portPinToNegInput(GPIO_Port_TypeDef port,
                                                       uint8_t pin)
{
  uint32_t input = (((uint32_t) port + _IADC_SCAN_PORTNEG_PORTA) << 4) | pin;

  return (IADC_NegInput_t) input;
}

/***************************************************************************//**
 * @brief
 *   Convert the GPIO port/pin to IADC positive input selection.
 *
 * @param[in] port
 *   GPIO port
 *
 * @param[in] pin
 *   GPIO in
 *
 * @return
 *   IADC positive input selection
 ******************************************************************************/
__STATIC_INLINE IADC_PosInput_t IADC_portPinToPosInput(GPIO_Port_TypeDef port,
                                                       uint8_t pin)
{
  uint32_t input = (((uint32_t) port + _IADC_SCAN_PORTPOS_PORTA) << 4) | pin;

  return (IADC_PosInput_t) input;
}

/** @} (end addtogroup iadc) */

#ifdef __cplusplus
}
#endif

#endif /* defined(IADC_COUNT) && (IADC_COUNT > 0) */
#endif /* EM_IADC_H */
