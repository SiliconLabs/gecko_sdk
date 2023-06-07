/***************************************************************************//**
 * @file
 * @brief MVP configuration file.
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

// <<< Use Configuration Wizard in Context Menu >>>

#ifndef SL_NN_MVP_CONFIG_H
#define SL_NN_MVP_CONFIG_H

// <o SL_MVP_OPTIMIZE_SPEED> Enable additional speed optimizations for MVP operations
// <i> By enabling this, the MVP will attempt to optimize select operations
// <i> to run faster. (The configuration value is a bitmask of options).
//
// <0=> Default
// <1=> Optimize Conv2D with increased RAM usage to store intermediate values
// <2=> Reduce numerical accuracy for Average pooling with large filters
// <0xFFFFFFFF=> Enable all optimizations
//
// <i> Note that RAM usage option may lead to greatly increased RAM usage.
// <i> Default: 0
#define SL_MVP_OPTIMIZE_SPEED  0

#endif /* SL_NN_MVP_CONFIG_H */

// <<< end of configuration section >>>
