/***************************************************************************//**
 * @file
 *
 * @copyright 2022 Silicon Laboratories Inc.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef CC_CONFIGURATION_IO_H
#define CC_CONFIGURATION_IO_H

#include <stdbool.h>
#include <stddef.h>
#include <zpal_nvm.h>

/**
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup Configuration
 * @{
 */

/**
 * Write a specific amount data to nvm
 *
 * @param[in] file_id Object key
 * @param[in] data pointer to the data to be written
 * @param[in] size amount of data in byte dimension
 * @return Returns true if successfully wrote to nvm, else false
 */
bool
cc_configuration_io_write(zpal_nvm_object_key_t file_id, uint8_t const* data, size_t size);

/**
 * Read a specific amount data to nvm
 *
 * @param[in] file_id Object key
 * @param[in] data pointer to the buffer where the data will be read into
 * @param[in] size wanted amount of data in byte dimension
 * @return Returns true if successfully read from nvm, else false
 */
bool
cc_configuration_io_read(zpal_nvm_object_key_t file_id, uint8_t *data, size_t size);

/**
 * @}
 * @}
 */

#endif /* CC_CONFIGURATION_IO_H */
