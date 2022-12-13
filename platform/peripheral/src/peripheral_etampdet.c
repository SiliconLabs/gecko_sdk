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

#include "peripheral_etampdet.h"
#if defined(ETAMPDET_PRESENT)

/***************************************************************************//**
 * @addtogroup etampdet ETAMPDET - External Tamper Detect
 * @brief External Tamper Detect (ETAMPDET) Peripheral API
 * @details
 *  This module contains functions to control the ETAMPDET peripheral of Silicon
 *  Labs 32-bit MCUs and SoCs. The ETAMPDET can alert the system to unauthorized
 *  physical access with very low current consumption.
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * Initialize ETAMPDET.
 ******************************************************************************/
void sl_etampdet_init(const sl_etampdet_config_t *config)
{
  // Wait for synchronization to finish
  sl_etampdet_wait_sync();

  if (ETAMPDET->EN & ETAMPDET_EN_EN) {
    // Disable ETAMDET before initialization
    sl_etampdet_disable();
    // Wait for disablement to finish
    sl_etampdet_wait_ready();
  }

  // Set upper and lower clock prescaler
  ETAMPDET->CLKPRESCVAL = ((uint32_t)config->upper_clk_presc_val << _ETAMPDET_CLKPRESCVAL_UPPERPRESC_SHIFT)
                          | ((uint32_t)config->lower_clk_presc_val << _ETAMPDET_CLKPRESCVAL_LOWERPRESC_SHIFT);
}

/***************************************************************************//**
 * Initialize ETAMPDET channel.
 ******************************************************************************/
void sl_etampdet_init_channel(const sl_etampdet_config_channel_t *config_channel)
{
  uint32_t temp = 0;
  // Wait for synchronization to finish
  sl_etampdet_wait_sync();

  if (ETAMPDET->EN & ETAMPDET_EN_EN) {
    // Disable ETAMDET before initialization
    sl_etampdet_disable();
    // Wait for disablement to finish
    sl_etampdet_wait_ready();
  }

  // Set enable channel value
  temp |= (uint32_t)config_channel->channel_pad_en << _ETAMPDET_CFG_CHNLPADEN0_SHIFT;
  // Set channel tamper detect filtering value
  temp |= (uint32_t)config_channel->channel_tampdet_filt_en << _ETAMPDET_CFG_CHNLTAMPDETFILTEN0_SHIFT;
  // Set 1 clock delay to TX value
  temp |= (uint32_t)config_channel->channel_cmp_dly_en << _ETAMPDET_CFG_CHNLCMPDLYEN0_SHIFT;
  // Set channel configuration register
  ETAMPDET->CFG_CLR = (_ETAMPDET_CFG_CHNLPADEN0_MASK
                       | _ETAMPDET_CFG_CHNLTAMPDETFILTEN0_MASK
                       | _ETAMPDET_CFG_CHNLCMPDLYEN0_MASK) << (config_channel->channel * _ETAMPDET_CFG_CHNLCMPDLYEN1_SHIFT);
  ETAMPDET->CFG_SET = temp << (config_channel->channel * _ETAMPDET_CFG_CHNLCMPDLYEN1_SHIFT);

  if (config_channel->channel_tampdet_filt_en) {
    // Set filter threshold register
    ETAMPDET->CNTMISMATCHMAX_CLR = _ETAMPDET_CNTMISMATCHMAX_CHNLCNTMISMATCHMAX0_MASK
                                   << (config_channel->channel * _ETAMPDET_CNTMISMATCHMAX_CHNLCNTMISMATCHMAX1_SHIFT);
    ETAMPDET->CNTMISMATCHMAX_SET = (uint32_t)config_channel->channel_cnt_mismatch
                                   << (config_channel->channel * _ETAMPDET_CNTMISMATCHMAX_CHNLCNTMISMATCHMAX1_SHIFT);

    // Set moving window size register
    ETAMPDET->CHNLFILTWINSIZE_CLR = _ETAMPDET_CHNLFILTWINSIZE_CHNLFILTWINSIZE0_MASK
                                    << (config_channel->channel * _ETAMPDET_CHNLFILTWINSIZE_CHNLFILTWINSIZE1_SHIFT);
    ETAMPDET->CHNLFILTWINSIZE_SET = (uint32_t)config_channel->channel_filt_win_size
                                    << (config_channel->channel * _ETAMPDET_CHNLFILTWINSIZE_CHNLFILTWINSIZE1_SHIFT);
  }

  // Set EM4 wakeup enable value
  ETAMPDET->EM4WUEN_CLR = _ETAMPDET_EM4WUEN_CHNLEM4WUEN0_MASK
                          << (config_channel->channel * _ETAMPDET_EM4WUEN_CHNLEM4WUEN1_SHIFT);
  ETAMPDET->EM4WUEN_SET = (uint32_t)config_channel->em4_wakeup_en
                          << (config_channel->channel * _ETAMPDET_EM4WUEN_CHNLEM4WUEN1_SHIFT);

  // Set Seed value
  if (config_channel->channel == channel_0) {
    ETAMPDET->CHNLSEEDVAL0 = config_channel->channel_seed_val;
  } else {
    ETAMPDET->CHNLSEEDVAL1 = config_channel->channel_seed_val;
  }
}

/** @} (end addtogroup etampdet) */
#endif /* defined(ETAMPDET_PRESENT) */
