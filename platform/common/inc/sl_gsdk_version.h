/*******************************************************************************
 * @file
 * @brief Retreive GSDK version
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef SL_GSDK_VERSION_H

#define SL_GSDK_MAJOR_VERSION     4
#define SL_GSDK_MINOR_VERSION     0
#define SL_GSDK_PATCH_VERSION     2

#define SL_GSDK_VERSION      ((SL_GSDK_MAJOR_VERSION <<  8)   \
                              | (SL_GSDK_MINOR_VERSION <<  4) \
                              | (SL_GSDK_PATCH_VERSION))

#define STR(s)  #s
#define XSTR(s)  STR(s)

#define SL_GSDK_VERSION_STR       \
  XSTR(SL_GSDK_MAJOR_VERSION)     \
  "." XSTR(SL_GSDK_MINOR_VERSION) \
  "." XSTR(SL_GSDK_PATCH_VERSION)

#endif
