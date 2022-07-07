/**************************************************************************//**
 * @file
 * @brief CMSIS Cortex-M Peripheral Access Layer for Silicon Laboratories
 *        microcontroller devices
 *
 * This is a convenience header file for defining the part number on the
 * build command line, instead of specifying the part specific header file.
 *
 * @verbatim
 * Example: Add "-DEFM32G890F128" to your build options, to define part
 *          Add "#include "em_device.h" to your source files

 *
 * @endverbatim
 ******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories, Inc. www.silabs.com</b>
 ******************************************************************************
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
 *****************************************************************************/

#ifndef EM_DEVICE_H
#define EM_DEVICE_H
#if defined(EFR32FG23A010F128GM40)
#include "efr32fg23a010f128gm40.h"

#elif defined(EFR32FG23A010F256GM40)
#include "efr32fg23a010f256gm40.h"

#elif defined(EFR32FG23A010F256GM48)
#include "efr32fg23a010f256gm48.h"

#elif defined(EFR32FG23A010F512GM40)
#include "efr32fg23a010f512gm40.h"

#elif defined(EFR32FG23A010F512GM48)
#include "efr32fg23a010f512gm48.h"

#elif defined(EFR32FG23A011F512GM40)
#include "efr32fg23a011f512gm40.h"

#elif defined(EFR32FG23A020F128GM40)
#include "efr32fg23a020f128gm40.h"

#elif defined(EFR32FG23A020F256GM40)
#include "efr32fg23a020f256gm40.h"

#elif defined(EFR32FG23A020F256GM48)
#include "efr32fg23a020f256gm48.h"

#elif defined(EFR32FG23A020F512GM40)
#include "efr32fg23a020f512gm40.h"

#elif defined(EFR32FG23A020F512GM48)
#include "efr32fg23a020f512gm48.h"

#elif defined(EFR32FG23A021F512GM40)
#include "efr32fg23a021f512gm40.h"

#elif defined(EFR32FG23B010F128GM40)
#include "efr32fg23b010f128gm40.h"

#elif defined(EFR32FG23B010F512GM48)
#include "efr32fg23b010f512gm48.h"

#elif defined(EFR32FG23B010F512IM40)
#include "efr32fg23b010f512im40.h"

#elif defined(EFR32FG23B010F512IM48)
#include "efr32fg23b010f512im48.h"

#elif defined(EFR32FG23B020F128GM40)
#include "efr32fg23b020f128gm40.h"

#elif defined(EFR32FG23B020F512IM40)
#include "efr32fg23b020f512im40.h"

#elif defined(EFR32FG23B020F512IM48)
#include "efr32fg23b020f512im48.h"

#else
#error "em_device.h: PART NUMBER undefined"
#endif
#endif /* EM_DEVICE_H */
