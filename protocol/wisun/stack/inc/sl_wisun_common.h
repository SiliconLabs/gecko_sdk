/***************************************************************************//**
 * @file sl_wisun_common.h
 * @brief Wi-SUN common declarations
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

#ifndef SL_WISUN_COMMON_H
#define SL_WISUN_COMMON_H

#include "ns_types.h"

#define CMSIS_RTOS_ERROR_MASK       0x80000000

#define SLI_WISUN_ERROR_CHECK(__result)\
do {\
  if (!(__result)){\
    goto error_handler;\
  }\
} while(0)

#define SLI_WISUN_ERROR_CHECK_SET_STATUS(__result, __value)\
do {\
  if (!(__result)){\
    status = __value;\
    goto error_handler;\
  }\
} while(0)

#define SLI_WISUN_ERROR_SET_STATUS(__value)\
do {\
  status = __value;\
  goto error_handler;\
} while(0)

// Macro for suppressing a warning about pointless integer comparisons
// since some the limits used in SLI_WISUN_PARAM_CHECK_LIMITS may be
// the minimum/maximum integer value.
#ifdef __ICCARM__
#define SUPPRESS_CHECK_LIMITS_WARNING _Pragma ("diag_suppress=Pa084")
#define RESTORE_CHECK_LIMITS_WARNING _Pragma ("diag_default=Pa084")
#else
#define SUPPRESS_CHECK_LIMITS_WARNING
#define RESTORE_CHECK_LIMITS_WARNING
#endif

/**
 * @brief Helper macro for SLI_WISUN_PARAM_CHECK_LIMITS
 *
 * This macro must not be used alone, it is needed to support limits defined as
 * macros (expand arguments first).
 */
#define SLI_WISUN_PARAM_CHECK_LIMITS_HELPER(PARAM, MIN, MAX) \
SUPPRESS_CHECK_LIMITS_WARNING \
if ((PARAM < MIN) || (PARAM > MAX)) { \
    param_check_success = false; \
    tr_error("Invalid value for parameter " #PARAM "(min=" #MIN ", max=" #MAX ")"); \
} \
RESTORE_CHECK_LIMITS_WARNING

/**
 * @brief Check lower and upper limits for a parameter
 *
 * The variable param_check_success must be defined as bool and initialized to
 * true, it is set to false if the check fails.
 *
 * @param PARAM Parameter to check
 * @param MIN Minimum value
 * @param MAX Maximum value
 */
#define SLI_WISUN_PARAM_CHECK_LIMITS(PARAM, ...) SLI_WISUN_PARAM_CHECK_LIMITS_HELPER(PARAM, __VA_ARGS__)

int64_t divide_integer(int64_t dividend, int32_t divisor);

// Seconds to milliseconds
#define S_TO_MS(x) (((int64_t)x)*1000)
// Milliseconds to seconds
#define MS_TO_S(x) divide_integer(x, 1000)
// Seconds to microseconds
#define S_TO_US(x) (((int64_t)x)*1000000)
// Microseconds to seconds
#define US_TO_S(x) divide_integer(x, 1000000)
// Milliseconds to microseconds
#define MS_TO_US(x) (((int64_t)x)*1000)
// Microseconds to milliseconds
#define US_TO_MS(x) divide_integer(x, 1000)
// Milliseconds to nanoseconds
#define MS_TO_NS(x) (((int64_t)x)*1000000)
// Nanoseconds to milliseconds
#define NS_TO_MS(x) divide_integer(x, 1000000)
// Microseconds to nanoseconds
#define US_TO_NS(x) (((int64_t)x)*1000)
// Nanoseconds to microseconds
#define NS_TO_US(x) divide_integer(x, 1000)

/// Convert months to minutes (month of 30 days)
#define MONTH_TO_MIN(x) ((x) * 30 * 24 * 60)

/// Convert days to seconds
#define DAY_TO_SEC(x) ((x) * 24 * 3600)

/// Convert hours to minutes
#define HOUR_TO_MIN(x) ((x) * 60)

/// Convert minutes to seconds
#define MIN_TO_SEC(x) ((x) * 60)

/// Convert hours to seconds
#define HOUR_TO_SEC(x) ((x) * 3600)

/// Convert seconds to milliseconds
#define SEC_TO_MS(x) ((x) * 1000)

/// Convert signal level in dBm to RSL range from -174 (0) to +80 (254) dBm
#define DBM_TO_RSL_RANGE(x)  (174 + (x))

#define ABSOLUTE_DIFF(a, b) ((a) > (b)) ? (a) - (b) : (b) - (a)

#define MIN(a, b) (((a) <= (b)) ? (a) : (b))

#define MAX(a, b) (((a) >= (b)) ? (a) : (b))

#define container_of(ptr, type, member)  (type *)((uintptr_t)(ptr) - ((uintptr_t)(&((type *)0)->member)))

/// Get the number of elements in an array (must not be used with pointers)
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#endif
