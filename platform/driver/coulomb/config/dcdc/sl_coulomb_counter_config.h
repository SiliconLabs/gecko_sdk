/***************************************************************************//**
 * @file
 * @brief Coulomb counter configuration file.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_COULOMB_COUNTER_CONFIG_H
#define SL_COULOMB_COUNTER_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

#define SL_COULOMB_COUNTER_DRIVER_PERIPHERAL_DCDC   0
#define SL_COULOMB_COUNTER_DRIVER_PERIPHERAL_EFP    1
#define SL_COULOMB_COUNTER_DRIVER_PERIPHERAL        SL_COULOMB_COUNTER_DRIVER_PERIPHERAL_DCDC

// <e SL_COULOMB_COUNTER_OUTPUT_USE_DCDC_EM0> Measure DCDC's output in EM0
// <i> Measure Coulomb for DCDC's output
// <i> Default: 1
#define SL_COULOMB_COUNTER_OUTPUT_USE_DCDC_EM0        1
// </e>

// <e SL_COULOMB_COUNTER_OUTPUT_USE_DCDC_EM2> Measure DCDC's output in EM2
// <i> Measure Coulomb for DCDC's output
// <i> Default: 1
#define SL_COULOMB_COUNTER_OUTPUT_USE_DCDC_EM2        1
// </e>

// <o SL_COULOMB_COUNTER_THRESHOLD> Threshold value to set counter full flag
//   <SL_COULOMB_COUNTER_THRESHOLD_50=>   50%
//   <SL_COULOMB_COUNTER_THRESHOLD_62=>   62.5%
//   <SL_COULOMB_COUNTER_THRESHOLD_75=>   75%
//   <SL_COULOMB_COUNTER_THRESHOLD_87=>   87.5%
// <i>Selects threshold value
#define SL_COULOMB_COUNTER_THRESHOLD                  SL_COULOMB_COUNTER_THRESHOLD_50

// <<< end of configuration section >>>

#endif /* SL_COULOMB_COUNTER_CONFIG_H */
