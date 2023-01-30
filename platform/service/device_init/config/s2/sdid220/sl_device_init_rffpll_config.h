/***************************************************************************//**
 * @file
 * @brief DEVICE_INIT_RFFPLL Config
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

#ifndef SL_DEVICE_INIT_RFFPLL_CONFIG_H
#define SL_DEVICE_INIT_RFFPLL_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h>RFFPLL configuration
// <o SL_DEVICE_INIT_RFFPLL_BAND> Target RF band (with 39MHz crystal)
// <i> Radio frequency bands.
// <i> Band 9xx MHz covers from 901 to 928 MHz.
// <0=> Band 450 MHz
// <1=> Band 470 MHz
// <2=> Band 780 MHz
// <3=> Band 863 MHz
// <4=> Band 896 MHz
// <5=> Band 928 MHz
// <6=> Band 9xx MHz
// <7=> AUTO BAND
// <i> Default: 7
#define SL_DEVICE_INIT_RFFPLL_BAND                7

// <e SL_DEVICE_INIT_RFFPLL_CUSTOM_BAND> Use custom band (overrides Target RF band)
// <i> Default: 0
#define SL_DEVICE_INIT_RFFPLL_CUSTOM_BAND 0

// <o SL_DEVICE_INIT_RFFPLL_FREQ> Digital host target frequency in Hz
// <95000000-100000000:100000>
// <i> The host target frequency should range between 95 and 100 MHz.
// <i> This frequency does not relate to the radio part.
// <i> Default: 100000000
#define SL_DEVICE_INIT_RFFPLL_FREQ               100000000

// <o SL_DEVICE_INIT_RFFPLL_DIV_Y> Digital host clock output divider ratio (DIVY)
// <8-31:1>
// <i> Divider Y is used for the host target frequency using this formula: frequency = (freq HFXO * DIV_N / 2) / DIV_Y
// <i> Default: 17
#define SL_DEVICE_INIT_RFFPLL_DIV_Y               17

// <o SL_DEVICE_INIT_RFFPLL_DIV_X> Radio output divider ratio (DIVX)
// <4-15:1>
// <i> Divider X is used for the radio frequency using this formula: frequency = (freq HFXO * DIV_N / 2) / (DIV_X / 2)
// <i> Default: 6
#define SL_DEVICE_INIT_RFFPLL_DIV_X               6

// <o SL_DEVICE_INIT_RFFPLL_DIV_N> PLL feedback divider ratio (DIVN)
// <32-127:1>
// <i> Divider N is used for the host and radio frequencies using these formulas:
// <i> - Host:  frequency = (freq HFXO * DIV_N / 2) / DIV_Y
// <i> - Radio: frequency = (freq HFXO * DIV_N / 2) / DIV_X
// <i> Default: 87
#define SL_DEVICE_INIT_RFFPLL_DIV_N               87

// </e>
// </h>

// <h>SYSCLK configuration
// <o SL_DEVICE_INIT_SYSCLK_SOURCE> SYSCLK clock source selection
// <i> This clock selection may override the default host clock selection done in sl_device_init_clocks().
// <cmuSelect_RFFPLLSYS=> RFFPLL
// <cmuSelect_HFXO=> HFXO
// <cmuSelect_HFRCODPLL=> HFRCO DPLL
// <i> Default: RFFPLL
#define SL_DEVICE_INIT_SYSCLK_SOURCE           cmuSelect_RFFPLLSYS
//</h>

// <<< end of configuration section >>>
#endif // SL_DEVICE_INIT_RFFPLL_CONFIG_H
