/***************************************************************************//**
 * @file
 * @brief ETAMPDET (External Tamper Detection) peripheral API
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

#ifndef PERIPHERAL_ETAMPDET_H
#define PERIPHERAL_ETAMPDET_H

#include "em_device.h"

#if defined(ETAMPDET_PRESENT)

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "peripheral_etampdet_compat.h"
#include "sl_enum.h"

/***************************************************************************//**
 * @addtogroup etampdet
 * @{
 ******************************************************************************/

/*******************************************************************************
 *********************************   ENUM   ************************************
 ******************************************************************************/

/** ETAMPDET channels. */
SL_ENUM(sl_hal_etampdet_channel_t) {
  /** Channel 0. */
  channel_0 = 0,

  /** Channel 1. */
  channel_1,
};

/** ETAMPDET filter thresholds. */
SL_ENUM(sl_hal_etampdet_channel_cnt_mismatch_threshold_t) {
  /** Raise detect flag after seeing 1 event before reset counter expire. */
  detect_filt_threshold_1 = _ETAMPDET_CNTMISMATCHMAX_CHNLCNTMISMATCHMAX0_DetectFilterThreshold1,

  /** Raise detect flag after seeing 2 events before reset counter expire. */
  detect_filt_threshold_2 = _ETAMPDET_CNTMISMATCHMAX_CHNLCNTMISMATCHMAX0_DetectFilterThreshold2,

  /** Raise detect flag after seeing 3 events before reset counter expire. */
  detect_filt_threshold_3 = _ETAMPDET_CNTMISMATCHMAX_CHNLCNTMISMATCHMAX0_DetectFilterThreshold3,

  /** Raise detect flag after seeing 4 events before reset counter expire. */
  detect_filt_threshold_4 = _ETAMPDET_CNTMISMATCHMAX_CHNLCNTMISMATCHMAX0_DetectFilterThreshold4,

  /** Raise detect flag after seeing 5 events before reset counter expire. */
  detect_filt_threshold_5 = _ETAMPDET_CNTMISMATCHMAX_CHNLCNTMISMATCHMAX0_DetectFilterThreshold5,

  /** Raise detect flag after seeing 6 events before reset counter expire. */
  detect_filt_threshold_6 = _ETAMPDET_CNTMISMATCHMAX_CHNLCNTMISMATCHMAX0_DetectFilterThreshold6,

  /** Raise detect flag after seeing 7 events before reset counter expire. */
  detect_filt_threshold_7 = _ETAMPDET_CNTMISMATCHMAX_CHNLCNTMISMATCHMAX0_DetectFilterThreshold7,

  /** Raise detect flag after seeing 8 events before reset counter expire. */
  detect_filt_threshold_8 = _ETAMPDET_CNTMISMATCHMAX_CHNLCNTMISMATCHMAX0_DetectFilterThreshold8,
};

/** ETAMPDET filter moving window size. */
SL_ENUM(sl_hal_etampdet_channel_filt_win_size_t) {
  /** Detect filter moving window size 2. */
  detect_filt_win_size_2 = _ETAMPDET_CHNLFILTWINSIZE_CHNLFILTWINSIZE0_DetectFilterMovingWinSize2,

  /** Detect filter moving window size 3. */
  detect_filt_win_size_3 = _ETAMPDET_CHNLFILTWINSIZE_CHNLFILTWINSIZE0_DetectFilterMovingWinSize3,

  /** Detect filter moving window size 4. */
  detect_filt_win_size_4 = _ETAMPDET_CHNLFILTWINSIZE_CHNLFILTWINSIZE0_DetectFilterMovingWinSize4,

  /** Detect filter moving window size 5. */
  detect_filt_win_size_5 = _ETAMPDET_CHNLFILTWINSIZE_CHNLFILTWINSIZE0_DetectFilterMovingWinSize5,

  /** Detect filter moving window size 6. */
  detect_filt_win_size_6 = _ETAMPDET_CHNLFILTWINSIZE_CHNLFILTWINSIZE0_DetectFilterMovingWinSize6,

  /** Detect filter moving window size 7. */
  detect_filt_win_size_7 = _ETAMPDET_CHNLFILTWINSIZE_CHNLFILTWINSIZE0_DetectFilterMovingWinSize7,

  /** Detect filter moving window size 8. */
  detect_filt_win_size_8 = _ETAMPDET_CHNLFILTWINSIZE_CHNLFILTWINSIZE0_DetectFilterMovingWinSize8,

  /** Detect filter moving window size 9. */
  detect_filt_win_size_9 = _ETAMPDET_CHNLFILTWINSIZE_CHNLFILTWINSIZE0_DetectFilterMovingWinSize9,

  /** Detect filter moving window size 10. */
  detect_filt_win_size_10 = _ETAMPDET_CHNLFILTWINSIZE_CHNLFILTWINSIZE0_DetectFilterMovingWinSize10,

  /** Detect filter moving window size 11. */
  detect_filt_win_size_11 = _ETAMPDET_CHNLFILTWINSIZE_CHNLFILTWINSIZE0_DetectFilterMovingWinSize11,

  /** Detect filter moving window size 12. */
  detect_filt_win_size_12 = _ETAMPDET_CHNLFILTWINSIZE_CHNLFILTWINSIZE0_DetectFilterMovingWinSize12,

  /** Detect filter moving window size 13. */
  detect_filt_win_size_13 = _ETAMPDET_CHNLFILTWINSIZE_CHNLFILTWINSIZE0_DetectFilterMovingWinSize13,

  /** Detect filter moving window size 14. */
  detect_filt_win_size_14 = _ETAMPDET_CHNLFILTWINSIZE_CHNLFILTWINSIZE0_DetectFilterMovingWinSize14,

  /** Detect filter moving window size 15. */
  detect_filt_win_size_15 = _ETAMPDET_CHNLFILTWINSIZE_CHNLFILTWINSIZE0_DetectFilterMovingWinSize15,

  /** Detect filter moving window size 16. */
  detect_filt_win_size_16 = _ETAMPDET_CHNLFILTWINSIZE_CHNLFILTWINSIZE0_DetectFilterMovingWinSize16,
};

/** ETAMPDET upper part of divider ripple counter. */
SL_ENUM(sl_hal_etampdet_upper_clk_presc_t) {
  /** Ripple counter divider bypassed. */
  upper_clk_prescaler_bypass = _ETAMPDET_CLKPRESCVAL_UPPERPRESC_Bypass,

  /** Divide by 2. */
  upper_clk_prescaler_divide_2 = _ETAMPDET_CLKPRESCVAL_UPPERPRESC_DivideBy2,

  /** Divide by 4. */
  upper_clk_prescaler_divide_4 = _ETAMPDET_CLKPRESCVAL_UPPERPRESC_DivideBy4,

  /** Divide by 8. */
  upper_clk_prescaler_divide_8 = _ETAMPDET_CLKPRESCVAL_UPPERPRESC_DivideBy8,

  /** Divide by 16. */
  upper_clk_prescaler_divide_16 = _ETAMPDET_CLKPRESCVAL_UPPERPRESC_DivideBy16,

  /** Divide by 32. */
  upper_clk_prescaler_divide_32 = _ETAMPDET_CLKPRESCVAL_UPPERPRESC_DivideBy32,

  /** Divide by 64. */
  upper_clk_prescaler_divide_64 = _ETAMPDET_CLKPRESCVAL_UPPERPRESC_DivideBy64,
};

/** ETAMPDET lower part of divider binary counter. */
SL_ENUM(sl_hal_etampdet_lower_clk_presc_t) {
  /** Divider is bypassed. */
  lower_clk_prescaler_bypass = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_Bypass,

  /** Divide by 2. */
  lower_clk_prescaler_divide_2 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy2,

  /** Divide by 3. */
  lower_clk_prescaler_divide_3 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy3,

  /** Divide by 4. */
  lower_clk_prescaler_divide_4 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy4,

  /** Divide by 5. */
  lower_clk_prescaler_divide_5 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy5,

  /** Divide by 6. */
  lower_clk_prescaler_divide_6 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy6,

  /** Divide by 7. */
  lower_clk_prescaler_divide_7 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy7,

  /** Divide by 8. */
  lower_clk_prescaler_divide_8 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy8,

  /** Divide by 9. */
  lower_clk_prescaler_divide_9 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy9,

  /** Divide by 10. */
  lower_clk_prescaler_divide_10 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy10,

  /** Divide by 11. */
  lower_clk_prescaler_divide_11 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy11,

  /** Divide by 12. */
  lower_clk_prescaler_divide_12 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy12,

  /** Divide by 13. */
  lower_clk_prescaler_divide_13 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy13,

  /** Divide by 14. */
  lower_clk_prescaler_divide_14 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy14,

  /** Divide by 15. */
  lower_clk_prescaler_divide_15 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy15,

  /** Divide by 16. */
  lower_clk_prescaler_divide_16 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy16,

  /** Divide by 17. */
  lower_clk_prescaler_divide_17 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy17,

  /** Divide by 18. */
  lower_clk_prescaler_divide_18 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy18,

  /** Divide by 19. */
  lower_clk_prescaler_divide_19 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy19,

  /** Divide by 20. */
  lower_clk_prescaler_divide_20 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy20,

  /** Divide by 21. */
  lower_clk_prescaler_divide_21 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy21,

  /** Divide by 22. */
  lower_clk_prescaler_divide_22 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy22,

  /** Divide by 23. */
  lower_clk_prescaler_divide_23 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy23,

  /** Divide by 24. */
  lower_clk_prescaler_divide_24 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy24,

  /** Divide by 25. */
  lower_clk_prescaler_divide_25 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy25,

  /** Divide by 26. */
  lower_clk_prescaler_divide_26 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy26,

  /** Divide by 27. */
  lower_clk_prescaler_divide_27 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy27,

  /** Divide by 28. */
  lower_clk_prescaler_divide_28 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy28,

  /** Divide by 29. */
  lower_clk_prescaler_divide_29 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy29,

  /** Divide by 30. */
  lower_clk_prescaler_divide_30 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy30,

  /** Divide by 31. */
  lower_clk_prescaler_divide_31 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy31,

  /** Divide by 32. */
  lower_clk_prescaler_divide_32 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy32,

  /** Divide by 33. */
  lower_clk_prescaler_divide_33 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy33,

  /** Divide by 34. */
  lower_clk_prescaler_divide_34 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy34,

  /** Divide by 35. */
  lower_clk_prescaler_divide_35 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy35,

  /** Divide by 36. */
  lower_clk_prescaler_divide_36 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy36,

  /** Divide by 37. */
  lower_clk_prescaler_divide_37 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy37,

  /** Divide by 38. */
  lower_clk_prescaler_divide_38 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy38,

  /** Divide by 39. */
  lower_clk_prescaler_divide_39 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy39,

  /** Divide by 40. */
  lower_clk_prescaler_divide_40 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy40,

  /** Divide by 41. */
  lower_clk_prescaler_divide_41 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy41,

  /** Divide by 42. */
  lower_clk_prescaler_divide_42 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy42,

  /** Divide by 43. */
  lower_clk_prescaler_divide_43 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy43,

  /** Divide by 44. */
  lower_clk_prescaler_divide_44 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy44,

  /** Divide by 45. */
  lower_clk_prescaler_divide_45 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy45,

  /** Divide by 46. */
  lower_clk_prescaler_divide_46 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy46,

  /** Divide by 47. */
  lower_clk_prescaler_divide_47 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy47,

  /** Divide by 48. */
  lower_clk_prescaler_divide_48 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy48,

  /** Divide by 49. */
  lower_clk_prescaler_divide_49 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy49,

  /** Divide by 50. */
  lower_clk_prescaler_divide_50 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy50,

  /** Divide by 51. */
  lower_clk_prescaler_divide_51 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy51,

  /** Divide by 52. */
  lower_clk_prescaler_divide_52 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy52,

  /** Divide by 53. */
  lower_clk_prescaler_divide_53 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy53,

  /** Divide by 54. */
  lower_clk_prescaler_divide_54 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy54,

  /** Divide by 55. */
  lower_clk_prescaler_divide_55 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy55,

  /** Divide by 56. */
  lower_clk_prescaler_divide_56 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy56,

  /** Divide by 57. */
  lower_clk_prescaler_divide_57 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy57,

  /** Divide by 58. */
  lower_clk_prescaler_divide_58 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy58,

  /** Divide by 59. */
  lower_clk_prescaler_divide_59 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy59,

  /** Divide by 60. */
  lower_clk_prescaler_divide_60 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy60,

  /** Divide by 61. */
  lower_clk_prescaler_divide_61 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy61,

  /** Divide by 62. */
  lower_clk_prescaler_divide_62 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy62,

  /** Divide by 63. */
  lower_clk_prescaler_divide_63 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy63,

  /** Divide by 64. */
  lower_clk_prescaler_divide_64 = _ETAMPDET_CLKPRESCVAL_LOWERPRESC_DivideBy64,
};

/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** ETAMPDET channel configuration structure. */
typedef struct {
  /** Seed value to load into channel LFSR. */
  uint32_t channel_seed_val;

  /** Channel id */
  sl_hal_etampdet_channel_t channel;

  /** Channel Filter moving window size. */
  sl_hal_etampdet_channel_filt_win_size_t channel_filt_win_size;

  /** Channel filter threshold value where a tamper detect will be triggered. */
  sl_hal_etampdet_channel_cnt_mismatch_threshold_t channel_cnt_mismatch;

  /** Enable channel driving pad. */
  bool channel_pad_en;

  /** Enable channel tamper detect filtering feature. */
  bool channel_tampdet_filt_en;

  /** Enable 1 clock delay to the TX value used for comparison. This is to
   * support trace propagation delay more than 1 clock cycle. */
  bool channel_cmp_dly_en;

  /** Set to enable EM4 wakeup when channel tamper detect is set. */
  bool em4_wakeup_en;
} sl_hal_etampdet_config_channel_t;

/** ETAMPDET configuration structure. */
typedef struct {
  /** Upper clock prescaler value. */
  sl_hal_etampdet_upper_clk_presc_t upper_clk_presc_val;

  /** Lower clock prescaler value. */
  sl_hal_etampdet_lower_clk_presc_t lower_clk_presc_val;
} sl_hal_etampdet_config_t;

/** ETAMPDET default channel configuration. */
#define ETAMPDET_CONFIG_CHANNEL_DEFAULT                                            \
  {                                                                                \
    0x13579BDF,                                 /* Set default seed value. */      \
    channel_0,                                  /* Choose channel 0.*/             \
    detect_filt_win_size_2,                     /* Set default filter win size. */ \
    detect_filt_threshold_1,                    /* Set Detect filter threshold. */ \
    false,                                      /* Enable channel driving pad. */  \
    false,                                      /* Disable channel filtering. */   \
    false,                                      /* Disable 1 clock delay. */       \
    false,                                      /* Enable EM4 wakeup. */           \
  }                                                                                \

/** ETAMPDET default configuration. */
#define ETAMPDET_CONFIG_DEFAULT                               \
  {                                                           \
    upper_clk_prescaler_bypass, /* Bypass upper prescaler. */ \
    lower_clk_prescaler_bypass, /* Bypass lower prescaler.*/  \
  }                                                           \

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

/***************************************************************************//**
 * Initialize ETAMPDET.
 *
 * @param[in] config  The pointer to the initialization structure.
 *
 * @note User should call @ref sl_hal_etampdet_init_channel() for full initialization.
 *       This function should be called before @ref sl_hal_etampdet_init_channel()
 *
 * @note The control registers setting of the GPIOs to be used by ETAMPDET
 *       should be at the default values to ensure that other clients
 *       are not accidentally driving the GPIOs that ETAMPDET is using.
 ******************************************************************************/
void sl_hal_etampdet_init(const sl_hal_etampdet_config_t *config);

/***************************************************************************//**
 * Initialize ETAMPDET channel.
 *
 * @param[in] config_channel  The pointer to the  channel initialization structure.
 *
 * @note User should call @ref sl_hal_etampdet_init() for full initialization.
 ******************************************************************************/
void sl_hal_etampdet_init_channel(const sl_hal_etampdet_config_channel_t *config_channel);

/***************************************************************************//**
 * Wait for the ETAMPDET to complete all synchronization of register changes
 * and commands.
 ******************************************************************************/
__STATIC_INLINE void sl_hal_etampdet_wait_sync(void)
{
  while (ETAMPDET->SYNCBUSY != 0U) {
    // Wait for all synchronizations to finish
  }
}

/***************************************************************************//**
 * Wait for the ETAMPDET to complete disabling procedure.
 ******************************************************************************/
__STATIC_INLINE void sl_hal_etampdet_wait_ready(void)
{
#if defined(ETAMPDET_EN_DISABLING)
  while ((ETAMPDET->EN & ETAMPDET_EN_DISABLING) || (ETAMPDET->SYNCBUSY != 0U)) {
    // Wait for disabling to finish
  }
#else
  while (ETAMPDET->SYNCBUSY != 0U) {
    // Wait for all synchronizations to finish
  }
#endif
}

/***************************************************************************//**
 * Enable ETAMPDET.
 ******************************************************************************/
__STATIC_INLINE void sl_hal_etampdet_enable(void)
{
  // Wait for synchronization to complete if necessary
  sl_hal_etampdet_wait_sync();

  // Enable ETAMPDET
  ETAMPDET->EN_SET = ETAMPDET_EN_EN;
}

/***************************************************************************//**
 * Disable ETAMPDET.
 ******************************************************************************/
__STATIC_INLINE void sl_hal_etampdet_disable(void)
{
  if (ETAMPDET->EN != ETAMPDET_EN_EN) {
    return;
  }

  // Disable ETAMPDET
  ETAMPDET->EN_CLR = ETAMPDET_EN_EN;
}

/***************************************************************************//**
 * Load seed value into channel LFSR.
 *
 * @param[in] channel  The channel number.
 ******************************************************************************/
__STATIC_INLINE void sl_hal_etampdet_load(sl_hal_etampdet_channel_t channel)
{
  // Wait for synchronization to complete if necessary
  sl_hal_etampdet_wait_sync();

  ETAMPDET->CMD |= ETAMPDET_CMD_CHNLLOAD0 << (channel * _ETAMPDET_CMD_CHNLSTART1_SHIFT);
}

/***************************************************************************//**
 * Start ETAMPDET channel.
 *
 * @param[in] channel  The channel number.
 ******************************************************************************/
__STATIC_INLINE void sl_hal_etampdet_start(sl_hal_etampdet_channel_t channel)
{
  // Wait for synchronization to complete if necessary
  sl_hal_etampdet_wait_sync();

  ETAMPDET->CMD |= ETAMPDET_CMD_CHNLSTART0 << (channel * _ETAMPDET_CMD_CHNLSTART1_SHIFT);
}

/***************************************************************************//**
 * Stop ETAMPDET channel.
 *
 * @param[in] channel  The channel number.
 ******************************************************************************/
__STATIC_INLINE void sl_hal_etampdet_stop(sl_hal_etampdet_channel_t channel)
{
  // Wait for synchronization to complete if necessary
  sl_hal_etampdet_wait_sync();

  ETAMPDET->CMD |= ETAMPDET_CMD_CHNLSTOP0 << (channel * _ETAMPDET_CMD_CHNLSTART1_SHIFT);
}

/***************************************************************************//**
 * Enable ETAMPDET interrupts.
 *
 * @param[in] interrupts  The interrupts flags to enable.
 ******************************************************************************/
__STATIC_INLINE void sl_hal_etampdet_enable_interrupts(uint32_t interrupts)
{
  ETAMPDET->IEN_SET = interrupts;
}

/***************************************************************************//**
 * Disable ETAMPDET interrupts.
 *
 * @param[in] interrupts  The interrupts flags to disable.
 ******************************************************************************/
__STATIC_INLINE void sl_hal_etampdet_disable_interrupts(uint32_t interrupts)
{
  ETAMPDET->IEN_CLR = interrupts;
}

/***************************************************************************//**
 * Set ETAMPDET interrupts.
 *
 * @param[in] interrupts  The interrupts flags to set.
 ******************************************************************************/
__STATIC_INLINE void sl_hal_etampdet_set_interrupts(uint32_t interrupts)
{
  ETAMPDET->IF_SET = interrupts;
}

/***************************************************************************//**
 * Clear ETAMPDET interrupts.
 *
 * @param[in] interrupts  The interrupts flags to clear.
 ******************************************************************************/
__STATIC_INLINE void sl_hal_etampdet_clear_interrupts(uint32_t interrupts)
{
  ETAMPDET->IF_CLR = interrupts;
}

/***************************************************************************//**
 * Gets pending ETAMPDET interrupt flags.
 *
 * @note  Event bits are not cleared by using this function.
 *
 * @return  Pending ETAMPDET interrupt sources.
 *          Returns a set of interrupt flags OR-ed together for multiple
 *          interrupt sources.
 ******************************************************************************/
__STATIC_INLINE uint32_t sl_hal_etampdet_get_interrupts(void)
{
  return ETAMPDET->IF;
}

/***************************************************************************//**
 * Gets enabled and pending ETAMPDET interrupt flags.
 * Useful for handling more interrupt sources in the same interrupt handler.
 *
 * @note  Interrupt flags are not cleared by using this function.
 *
 * @return  Pending and enabled ETAMPDET interrupt sources.
 *          The return value is the bitwise AND of
 *          - the enabled interrupt sources in ETAMPDET_IEN and
 *          - the pending interrupt flags ETAMPDET_IF.
 ******************************************************************************/
__STATIC_INLINE uint32_t sl_hal_etampdet_get_enabled_interrupts(void)
{
  uint32_t ien = 0;
  ien = ETAMPDET->IEN;
  return ETAMPDET->IF & ien;
}

/***************************************************************************//**
 * Lock ETAMPDET registers.
 *
 * @note  When ETAMPDET registers are locked, ETAMPDET_EN, ETAMPDET_CFG, ETAMPDET_CMD,
 *        ETAMPDET_CHNLSEEDVALx, ETAMPDET_CNTMISMATCHMAX, ETAMPDET_CHNLFILTWINSIZE,
 *        ETAMPDET_EM4WUEN and ETAMPDET_CLKPRESCVAL registers cannot be written to.
 ******************************************************************************/
__STATIC_INLINE void sl_hal_etampdet_lock(void)
{
  ETAMPDET->LOCK = ~ETAMPDET_LOCK_LOCKKEY_UNLOCK;
}

/***************************************************************************//**
 * Unlock ETAMPDET registers.
 *
 * @note  When ETAMPDET registers are unlocked, registers are writable.
 ******************************************************************************/
__STATIC_INLINE void sl_hal_etampdet_unlock(void)
{
  ETAMPDET->LOCK = ETAMPDET_LOCK_LOCKKEY_UNLOCK;
}

/***************************************************************************//**
 * Gets ETAMPDET STATUS register value.
 *
 * @return  Current STATUS register value.
 ******************************************************************************/
__STATIC_INLINE uint32_t sl_hal_etampdet_get_status(void)
{
  return ETAMPDET->STATUS;
}

/***************************************************************************//**
 * Set ETAMPDET channel seed value.
 *
 * @param[in] channel  The channel to set seed value.
 *
 * @param[in] seed_value  The seed value to set into LFSR of the channel.
 *
 * @note  It is recommended to get the random seed value using TRNG (True random
 *        Number Generator) peripheral.
 ******************************************************************************/
__STATIC_INLINE void sl_hal_etampdet_set_seed_value(uint32_t seed_value, sl_hal_etampdet_channel_t channel)
{
  if (channel == channel_0) {
    ETAMPDET->CHNLSEEDVAL0 = seed_value;
  } else {
    ETAMPDET->CHNLSEEDVAL1 = seed_value;
  }
}

/***************************************************************************//**
 * Get ETAMPDET channel seed value.
 *
 * @param[in] channel  The channel to get seed value from.
 *
 * @return  The seed value of the channel.
 ******************************************************************************/
__STATIC_INLINE uint32_t sl_hal_etampdet_get_seed_value(sl_hal_etampdet_channel_t channel)
{
  if (channel == channel_0) {
    return ETAMPDET->CHNLSEEDVAL0;
  } else {
    return ETAMPDET->CHNLSEEDVAL1;
  }
}

/** @} (end addtogroup etampdet) */

#ifdef __cplusplus
}
#endif

#endif /* defined(ETAMPDET_PRESENT) */
#endif /* PERIPHERAL_ETAMPDET_H */
