/***************************************************************************//**
 * @file
 * @brief ESL Tag RAM Image component configuration macros
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
#ifndef ESL_TAG_IMAGE_CONFIG_H
#define ESL_TAG_IMAGE_CONFIG_H

/***********************************************************************************************//**
 * @addtogroup esl_tag_nvm_image
 * @{
 **************************************************************************************************/

// <<< Use Configuration Wizard in Context Menu >>>

// <h> ESL Tag Image configuration

// <o ESL_TAG_MAX_IMAGES> Image objects <1-256>
// <i> Default: 1
// <i> Define the maximum number of images the ESL Tag can handle.
#define ESL_TAG_MAX_IMAGES            (1)

// <o ESL_TAG_RAM_IMAGE_POOL_SIZE> Image pool size <1024-32768>
// <i> Default: 2048
// <i> Define the size of the statically allocated RAM area for image object storage on the ESL Tag.
// <i> Please note that the maximum storage size is limited by the amount of RAM available and the needs of the application!
#define ESL_TAG_RAM_IMAGE_POOL_SIZE   (2048)

// </h>

// <<< end of configuration section >>>

/** @} (end addtogroup esl_tag_nvm_image) */
#endif // ESL_TAG_IMAGE_CONFIG_H
