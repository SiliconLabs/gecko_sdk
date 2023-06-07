/***************************************************************************//**
 * @file
 * @brief ESL Tag interface declarations for OTS image transfer functionalities.
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
#ifndef ESL_TAG_OTS_SERVER_H
#define ESL_TAG_OTS_SERVER_H
#include <stdint.h>
#include "sl_status.h"
#include "sl_bt_ots_datatypes.h"
#include "esl_tag_image_core.h"

/// Object property reserved for internal read-only image objects (if any)
#define ESL_OTS_EMBEDDED_IMAGE    SL_BT_OTS_WRITE_MODE_NONE

/// Object property for standard ESL Image objects
#define ESL_OTS_IMAGE_OBJECT      (SL_BT_OTS_OBJECT_PROPERTY_WRITE_MASK \
                                   | SL_BT_OTS_OBJECT_PROPERTY_TRUNCATE_MASK)

/// Custom UUID for 1 bit / pixel images (usually black and white bitmaps)
extern const sl_bt_ots_object_type_t esl_image_type_1b;

/// Custom UUID for 2 bits / pixel imaged (usually red, black and white bitmaps)
extern const sl_bt_ots_object_type_t esl_image_type_2b;

/**************************************************************************//**
 * Bluetooth stack event handler for ESL OTS Server component.
 * This one runs parallel to the user implementation (usually in app.c).
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void esl_tag_ots_server_bt_on_event(sl_bt_msg_t *evt);

/**************************************************************************//**
 * Add an ESL Tag image to the list of available OTS objects. Any images on a
 * Tag can be only written after adding it to the OTS object list. This function
 * has to be called from @ref esl_image_add method.
 *
 * @param[in] poperties      OTS Object property flags
 * @param[in] allocated_size Allocated size for ESL Image static object
 * @param[in] type           Pointer to an OTS Object Type descriptor
 * @return    sl_status_t
 *****************************************************************************/
sl_status_t esl_tag_ots_add_object(const sl_bt_ots_object_type_t* type,
                                   uint32_t allocated_size,
                                   uint32_t properties);

#endif // ESL_TAG_OTS_SERVER_H
