/***************************************************************************//**
 * # License
 * <b> Copyright 2023 Silicon Laboratories Inc. www.silabs.com </b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of the Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * https://www.silabs.com/about-us/legal/master-software-license-agreement
 * By installing, copying or otherwise using this software, you agree to the
 * terms of the MSLA.
 *
 ******************************************************************************/

/**
 * @file
 * Defines configuration extension for zpal-zwave-nvm.
 */

#ifndef _ZPAL_ZWAVE_NVM_SECTION_H_
#define _ZPAL_ZWAVE_NVM_SECTION_H_

#ifdef ZWAVE_SERIES_700
#include <stddef.h>

/**
 * @brief Function used to get the cache size for the zwave nvm instance.
 * Need a function because this definition is used by zpal (which is build
 * with the z-wave stack), but it is set by the application (which is not
 * available when the stack is built)
 *
 * @return cache size in object count.
 */
size_t zpal_zwave_nvm_get_cache_size(void);

/**
 * @brief Function used to get a pointer on the RAM area reserved for the
 * cache.
 * Need a function because this definition is used by zpal (which is build
 * with the z-wave stack), but it is set by the application (which is not
 * available when the stack is built)
 *
 * @return a pointer on the cache, or NULL if no cache is set.
 */
void* zpal_zwave_nvm_get_cache_pointer(void);

/**
 * @brief Function used to get the size of the largest object stored in the
 * zwave nvm instance.
 * Need a function because this definition is used by zpal (which is build
 * with the z-wave stack), but it is set by the application (which is not
 * available when the stack is built)
 *
 * @return size of the largest object stored in the zwave nvm instance (in bytes)
 */
size_t zpal_zwave_nvm_get_max_object_size(void);

/**
 * @brief Function used to get the repack headroom for the zwave nvm instance.
 * Need a function because this definition is used by zpal (which is build
 * with the z-wave stack), but it is set by the application (which is not
 * available when the stack is built)
 *
 * @return repack headroom for the zwave nvm instance (in bytes)
 */
size_t zpal_zwave_nvm_get_repack_headroom(void);

#endif /*ZWAVE_SERIES_700*/
#endif /*_ZPAL_ZWAVE_NVM_SECTION_H_*/

