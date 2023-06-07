/***************************************************************************//**
 * @file
 * @brief Dot matrix display driver for LCD controller SSD2119
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

#ifndef __DMD_SSD2119_H
#define __DMD_SSD2119_H

#include "dmd/dmd.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/** Frame update frequency of display */
#define DMD_FRAME_FREQUENCY    80
/** Horizontal size of the display */
#define DMD_HORIZONTAL_SIZE    320
/** Vertical size of the display */
#define DMD_VERTICAL_SIZE      240

EMSTATUS DMDIF_init(uint32_t cmdRegAddr, uint32_t dataRegAddr);

/** @endcond */

#ifdef __cplusplus
}
#endif

#endif
