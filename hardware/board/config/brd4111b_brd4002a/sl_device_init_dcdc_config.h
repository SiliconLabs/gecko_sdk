/***************************************************************************//**
 * @file
 * @brief DEVICE_INIT_DCDC Config
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

#ifndef SL_DEVICE_INIT_DCDC_CONFIG_H
#define SL_DEVICE_INIT_DCDC_CONFIG_H

#include "sl_device_init_dcdc.h"
#include "em_device.h"

// <<< Use Configuration Wizard in Context Menu >>>

// <q SL_DEVICE_INIT_DCDC_ENABLE> Enable DC/DC Converter
// <i>
// <i> Default: 1
#define SL_DEVICE_INIT_DCDC_ENABLE         1

// <o SL_DEVICE_INIT_DCDC_TYPE> DC/DC Type
// <SL_DEVICE_INIT_DCDC_TYPE_BUCK=> Buck
// <SL_DEVICE_INIT_DCDC_TYPE_BOOST=> Boost
// <i>
// <i> Default: SL_DEVICE_INIT_DCDC_TYPE_BUCK
#define SL_DEVICE_INIT_DCDC_TYPE         SL_DEVICE_INIT_DCDC_TYPE_BOOST

// <h> DC/DC Buck Settings

// <q SL_DEVICE_INIT_DCDC_BYPASS> Set DC/DC Converter in Bypass Mode
// <i>
// <i> Default: 0
#define SL_DEVICE_INIT_DCDC_BYPASS         0

// <q SL_DEVICE_INIT_DCDC_PFMX_IPKVAL_OVERRIDE> Override for DCDC PFMX Mode Peak Current Setting
// <i>
// <i> Default: 0
#define SL_DEVICE_INIT_DCDC_PFMX_IPKVAL_OVERRIDE  0

// <o SL_DEVICE_INIT_DCDC_PFMX_IPKVAL> DCDC PFMX Mode Peak Current Setting <0-15>
// <i>
// <i> Default: DCDC_PFMXCTRL_IPKVAL_DEFAULT
#define SL_DEVICE_INIT_DCDC_PFMX_IPKVAL    DCDC_PFMXCTRL_IPKVAL_DEFAULT

// </h>

// <<< end of configuration section >>>

#endif // SL_DEVICE_INIT_DCDC_CONFIG_H
