/***************************************************************************//**
 * @file
 * @brief Dot matrix display SSD2119 interface using EBI
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

#ifndef __DMD_IF_SSD2119_EBI_H_
#define __DMD_IF_SSD2119_EBI_H_

#include <stdint.h>
#include "em_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/* Module Prototypes */
EMSTATUS DMDIF_init(uint32_t cmdRegAddr, uint32_t dataRegAddr);
EMSTATUS DMDIF_writeReg(uint8_t reg, uint16_t data);
uint16_t DMDIF_readDeviceCode(void);
EMSTATUS DMDIF_prepareDataAccess(void);
EMSTATUS DMDIF_writeData(uint32_t data);
EMSTATUS DMDIF_writeDataRepeated(uint32_t data, int len);
uint32_t DMDIF_readData(void);
EMSTATUS DMDIF_delay(uint32_t ms);

/** @endcond */

#ifdef __cplusplus
}
#endif

#endif
