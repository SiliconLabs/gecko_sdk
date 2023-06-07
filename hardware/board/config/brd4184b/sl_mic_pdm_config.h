/***************************************************************************//**
 * @file
 * @brief MIC_PDM config
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_MIC_PDM_CONFIG_H
#define SL_MIC_PDM_CONFIG_H

// <<< Use Configuration Wizard in Context Menu
// <h> MIC PDM config
// <o> PDM down sampling rate <3-73>
// <i> Defines the ratio between PDM reference clock and the sampling frequency
#define SL_MIC_PDM_DSR           32
// </h> end MIC_PDM config
// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>

// <pdm signal=DAT0,CLK> SL_MIC_PDM
// $[PDM_SL_MIC_PDM]
#define SL_MIC_PDM_PERIPHERAL                    PDM

// PDM DAT0 on PB01
#define SL_MIC_PDM_DAT0_PORT                     gpioPortB
#define SL_MIC_PDM_DAT0_PIN                      1

// PDM CLK on PB00
#define SL_MIC_PDM_CLK_PORT                      gpioPortB
#define SL_MIC_PDM_CLK_PIN                       0

// [PDM_SL_MIC_PDM]$
// <<< sl:end pin_tool >>>

#endif // SL_MIC_PDM_CONFIG_H
