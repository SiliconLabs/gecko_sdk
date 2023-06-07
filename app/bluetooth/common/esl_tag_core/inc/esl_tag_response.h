/***************************************************************************//**
 * @file
 * @brief ESL Tag responses macro definitions and interface declaration
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
#ifndef ESL_TAG_RESPONSE_H
#define ESL_TAG_RESPONSE_H

/***********************************************************************************************//**
 * @addtogroup esl_tag_core
 * @{
 **************************************************************************************************/
#include "sl_status.h"
#include "esl_tag_tlv.h"

/// The command could not be processed successfully
#define ESL_TLV_RESPONSE_ERROR          ((tlv_t)0x00)

/// Acknowledgment of a request to control an LED
#define ESL_TLV_RESPONSE_LED_STATE      ((tlv_t)0x01)

/// General acknowledgment containing ESL status data
#define ESL_TLV_RESPONSE_BASIC_STATE    ((tlv_t)0x10)

/// Acknowledgment of a request to display an image
#define ESL_TLV_RESPONSE_DISPLAY_STATE  ((tlv_t)0x11)

/// Sensor report
#define ESL_TLV_RESPONSE_SENSOR_VALUE   ((tlv_t)0x0E)

/// Response data as specified by the vendor of the ESL
#define ESL_TLV_RESPONSE_VENDOR_VALUE   ((tlv_t)0x0F)

/**************************************************************************//**
 * Init ESL Tag responses queue. ESL Core component will call this during the
 * initialization of application. This call is hidden and happens automatically.
 *****************************************************************************/
void esl_core_respones_init();

/**************************************************************************//**
 * Create response byte stream for single TLV based on input data and error
 * status (if any) then puts the response stream into a circular buffer.
 * The resulting output length of a single TLV will be the length encoded in
 * that particular TLV + 1 byte as per ESL specification. Multiple response
 * streams will be then concatenated on consecutive calls up to the maximum
 * length limit of 48 bytes for multiple response data.
 * @param[in] tlv The TLV to create the response stream for
 * @param[in] input_data can be a pointer to the basic status, led status etc.
 * @note the actual length of the input data length MUST be in correspondence
 *       with the TLV passed as the first parameter!
 *
 * @return sl_tatus_t
 *****************************************************************************/
sl_status_t esl_core_build_response(tlv_t tlv, const void *input_data);

/**************************************************************************//**
 * Copy all possible responses from internal circular buffer to a temporary
 * linear buffer.
 * Circular buffer drops the successfully read out data, while it might keep
 * remaining responses which doesn't fit into the target buffer. Consistency of
 * any response will be kept, that is, it might copy less data than the allowed
 * maximum length passed as the first parameter, if there are responses left
 * still in the internal circular buffer which otherwise wont fit into the
 * target buffer.
 * @param[in] remaining_length size of data out buffer
 * @param[out] buf_p pointer to data buffer to copy the responses into
 *
 * @return overall length of responses, might be 0 if there's no response
 *****************************************************************************/
uint8_t esl_core_get_responses(uint8_t remaining_length, uint8_t *buf_p);

/** @} (end addtogroup esl_tag_core) */
#endif // ESL_TAG_RESPONSE_H
