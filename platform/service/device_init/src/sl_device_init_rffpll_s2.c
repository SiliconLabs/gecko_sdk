/***************************************************************************//**
 * @file
 * @brief Device initialization for RFFPLL.
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
#include "sl_device_init_rffpll.h"
#include "sl_device_init_rffpll_config.h"

#include "em_cmu.h"

typedef struct {
  uint32_t frequency;  // Host target frequency.
  uint8_t divider_y;   // Divider Y for digital.
  uint8_t divider_x;   // Divider X for Radio.
  uint8_t divider_n;   // Feedback divider N.
} sl_device_init_rffpll_config_t;

// Table of possible radio frequency bands and their associated settings.
sl_device_init_rffpll_config_t rffpll_band_config_39MHz[] = {
  { 97500000, 23, 7, 115 }, // Band 450 MHz
  { 98380000, 22, 7, 111 }, // Band 470 MHz
  { 97500000, 23, 7, 115 }, // Band 780 MHz
  { 97500000, 20, 6, 100 }, // Band 863 MHz
  { 97500000, 23, 7, 115 }, // Band 896 MHz
  { 96520000, 20, 6, 99 },  // Band 928 MHz
  { 97500000, 20, 6, 100 }  // Band 9xx MHz (covers from 901 to 928 MHz)
};

sl_status_t sl_device_init_rffpll(void)
{
  CMU_RFFPLL_Init_TypeDef rffpll_init = CMU_RFFPLL_DEFAULT;

  // Overwrite default configurations.
#if (SL_DEVICE_INIT_RFFPLL_CUSTOM_BAND == 1)
  // Custom settings provided by the user.
  rffpll_init.frequency = SL_DEVICE_INIT_RFFPLL_FREQ;
  rffpll_init.dividerY = SL_DEVICE_INIT_RFFPLL_DIV_Y;
  rffpll_init.dividerX = SL_DEVICE_INIT_RFFPLL_DIV_X;
  rffpll_init.dividerN = SL_DEVICE_INIT_RFFPLL_DIV_N;
#else
  // Pre-determined settings.
  rffpll_init.frequency = rffpll_band_config_39MHz[SL_DEVICE_INIT_RFFPLL_BAND].frequency;
  rffpll_init.dividerY = rffpll_band_config_39MHz[SL_DEVICE_INIT_RFFPLL_BAND].divider_y;
  rffpll_init.dividerX = rffpll_band_config_39MHz[SL_DEVICE_INIT_RFFPLL_BAND].divider_x;
  rffpll_init.dividerN = rffpll_band_config_39MHz[SL_DEVICE_INIT_RFFPLL_BAND].divider_n;
#endif

  // Initialize RFFPLL.
  CMU_RFFPLLInit(&rffpll_init);

  // Select the clock source for SYSCLK. SYSCLK can be sourced by the RFFPLLSYS input clock.
  // This SYSCLK clock selection overwrites the one done in sl_device_init_clocks().
  if (SL_DEVICE_INIT_SYSCLK_SOURCE == cmuSelect_RFFPLLSYS) {
    CMU_CLOCK_SELECT_SET(SYSCLK, RFFPLLSYS);
    // Update HCLK frequency software reference if the SYSCLK clock source is RFFPLLSYS.
    SystemRFFPLLClockSet(rffpll_init.frequency);
  } else if (SL_DEVICE_INIT_SYSCLK_SOURCE == cmuSelect_HFXO) {
    CMU_CLOCK_SELECT_SET(SYSCLK, HFXO);
  } else if (SL_DEVICE_INIT_SYSCLK_SOURCE == cmuSelect_HFRCODPLL) {
    CMU_CLOCK_SELECT_SET(SYSCLK, HFRCODPLL);
  }

  return SL_STATUS_OK;
}
