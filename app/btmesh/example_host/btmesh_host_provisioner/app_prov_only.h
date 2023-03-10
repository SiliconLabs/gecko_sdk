/***************************************************************************//**
 * @file
 * @brief BT Mesh Host Provisioner command line build only.
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

#ifndef APP_PROV_ONLY_H
#define APP_PROV_ONLY_H

#ifdef __cplusplus
extern "C" {
#endif

// If CBP is not used, define its macros
#ifndef SL_CATALOG_APP_PROV_CBP_PRESENT
#define CBP_OPTLENGTH 0
#define CBP_OPTSTRING
#define CBP_USAGE
#define CBP_OPTIONS
#endif

// Remote provisioning is not used if this header is included
#define REMOTE_PROV_OPTLENGTH 0

// Size of long options struct array size
#define LONG_OPT_SIZE       PROV_OPTLENGTH + CBP_OPTLENGTH + LAST_OPTION_ELEMENT

// Optstring argument for getopt.
#define OPTSTRING           NCP_HOST_OPTSTRING PROV_OPTSTRING CBP_OPTSTRING "h"

// Usage info.
#define USAGE               "\n%s " NCP_HOST_USAGE PROV_USAGE CBP_USAGE " [-h]\n"

// Options info.
#define OPTIONS            \
  "\nConnection options\n" \
  NCP_HOST_OPTIONS         \
  PROV_OPTIONS             \
  CBP_OPTIONS              \
  "    -h  Print this help message.\n"

#ifdef __cplusplus
};
#endif

#endif // APP_PROV_ONLY_H
