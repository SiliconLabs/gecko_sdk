/***************************************************************************//**
 * @file
 * @brief ESL Tag TLV type definitions and interface provided to the user space.
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
#ifndef ESL_TAG_TLV_H
#define ESL_TAG_TLV_H

/***********************************************************************************************//**
 * @addtogroup esl_tag_core
 * @{
 **************************************************************************************************/
#include <stdint.h>

/// @typedef ESL Tag TLV type: consists of Tag and Length values
typedef uint8_t                         tlv_t;

/// @typedef ESL Tag TLV 'Tag' type
typedef uint8_t                         tlv_tag_t;

/// @typedef ESL Tag TLV 'Length' type
typedef uint8_t                         tlv_length_t;

/// Mask for getting the Tag value from an ESL TLV
#define ESL_TLV_TAG_MASK                ((tlv_t)0x0F)

/// Mask for getting the Length value from an ESL TLV
#define ESL_TLV_LEN_MASK                ((tlv_t)0xF0)

/**************************************************************************//**
 * Function like macro getter for 'Tag' field from an ESL TLV
 * @param[in] tlv_byte Tag Length Value to get the Tag value from
 * @return tlv_tag_t 'Tag' value of the TLV
 *****************************************************************************/
#define \
  esl_core_get_tlv_tag(tlv_byte)        ((tlv_t)tlv_byte & ESL_TLV_TAG_MASK)

/**************************************************************************//**
 * Function like macro getter for real 'Length' value from an ESL TLV
 * @param[in] tlv_byte Tag Length Value to get the Length value from
 * @return tlv_length_t 'Length' value of the TLV
 *****************************************************************************/
#define                                        \
  esl_core_get_tlv_len(tlv_byte)      ((tlv_t) \
                                       ((tlv_byte & ESL_TLV_LEN_MASK) >> 4) + 1)

/**************************************************************************//**
 * Function like macro for setting the 'Tag' value of a TLV
 * @param[out] tlv ESL Tag Length Value to set the 'Tag' part for
 * @param[in] tag Tag value to be set
 *****************************************************************************/
#define                                    \
  esl_core_set_tlv_tag(_tlv, _tag)    do { \
    _tlv &= (tlv_t)(~ESL_TLV_TAG_MASK);    \
    _tlv |= (((tlv_t)(_tag))               \
             & ESL_TLV_TAG_MASK);          \
  } while (0)

/**************************************************************************//**
 * Function like macro for setting the 'Length' value of a TLV
 * @param[out] tlv ESL Tag Length Value to set the 'Length' part for
 * @param[in] len real data length value to be set
 *****************************************************************************/
#define                                          \
  esl_core_set_tlv_len(_tlv, _len)    do {       \
    _tlv &= (tlv_t)(~ESL_TLV_LEN_MASK);          \
    _tlv |= _tlv | (((tlv_t)(((_len) - 1) << 4)) \
                    & ESL_TLV_LEN_MASK);         \
  } while (0)

/** @} (end addtogroup esl_tag_core) */
#endif // ESL_TAG_TLV_H
