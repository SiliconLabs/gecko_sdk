/***************************************************************************//**
 * @file
 * @brief ESL Tag Error definitions and interface declarations
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
#ifndef ESL_TAG_ERRORS_H
#define ESL_TAG_ERRORS_H

/***********************************************************************************************//**
 * @addtogroup esl_tag_core
 * @{
 **************************************************************************************************/
#include <stdint.h>
#include "sl_status.h"

/// @typedef ESL Tag Error type
typedef uint8_t                           esl_error_t;

/// Unspecified Error: any error condition that is not covered by a specific
/// error code below
#define ESL_ERROR_UNSPECIFIED             ((esl_error_t)0x01)

/// Invalid Opcode: The opcode was not recognized
#define ESL_ERROR_INVALID_OPCODE          ((esl_error_t)0x02)

/// Invalid State: The request was not valid for the present ESL state
#define ESL_ERROR_INVALID_STATE           ((esl_error_t)0x03)

/// Invalid Image Index: The Image_Index value was out of range
#define ESL_ERROR_INVALID_IMAGE_INDEX     ((esl_error_t)0x04)

/// Image Not Available: The requested image contained no image data
#define ESL_ERROR_IMAGE_NOT_AVAILABLE     ((esl_error_t)0x05)

/// Invalid Parameter(s): The parameter value(s) or length did not match the
/// opcode
#define ESL_ERROR_INVALID_PARAMETER       ((esl_error_t)0x06)

/// Capacity Limit: The required response could not be sent as it would exceed
/// the payload size limit
#define ESL_ERROR_CAPACITY_LIMIT          ((esl_error_t)0x07)

/// Insufficient Battery: The request could not be processed because of a lack
/// of battery charge
#define ESL_ERROR_INSUFFICIENT_BATTERY    ((esl_error_t)0x08)

/// Insufficient Resources: The request could not be processed because of a lack
/// of resources. This may be a temporary condition.
#define ESL_ERROR_INSUFFICIENT_RESOURCES  ((esl_error_t)0x09)

/// Retry: The ESL is temporarily not able to give a full response (e.g.,
/// because the required sensor hardware was asleep) and the AP is asked to try
/// the same command again.
#define ESL_ERROR_RETRY                   ((esl_error_t)0x0A)

/// Queue Full: The ESL is temporarily unable to add a further timed command to
/// the queue of pending commands Â­the queue has reached its limit.
#define ESL_ERROR_QUEUE_FULL              ((esl_error_t)0x0B)

/// Implausible time: The Absolute Time parameter value in the command would
/// result in a delay longer than 48 days (that is, it's a possible overflow)
#define ESL_ERROR_IMPLAUSIBLE_TIME        ((esl_error_t)0x0C)

/// No Error: 0xFF is reserved for 'no error' indication. For internal use only,
/// and it is Silicon Labs specific.
#define ESL_ERROR_VENDOR_NOERROR          ((esl_error_t)0xFF)

/// No report: 0xFE is reserved for 'no error report needed for timed commands'
/// indication. For internal use only, and it is Silicon Labs specific.
#define ESL_ERROR_VENDOR_NOREPORT         ((esl_error_t)0xFE)

/**************************************************************************//**
 * Wrapper around @ref esl_core_set_last_error() to clear the last error
 *****************************************************************************/
#define esl_core_clear_last_error() \
  esl_core_set_last_error(ESL_ERROR_VENDOR_NOERROR)

/**************************************************************************//**
 * Wrapper around @ref esl_core_get_last_error() to check if there's no error
 *****************************************************************************/
#define esl_core_has_no_error() \
  (ESL_ERROR_VENDOR_NOERROR != esl_core_get_last_error)

/**************************************************************************//**
 * Gets the last error code
 * @return esl_error_t_t
 *****************************************************************************/
esl_error_t esl_core_get_last_error(void);

/**************************************************************************//**
 * Sets the last error code
 * @param[in] esl_error_t error code
 *****************************************************************************/
void esl_core_set_last_error(esl_error_t error_code);

/** @} (end addtogroup esl_tag_core) */
#endif // ESL_TAG_ERRORS_H
