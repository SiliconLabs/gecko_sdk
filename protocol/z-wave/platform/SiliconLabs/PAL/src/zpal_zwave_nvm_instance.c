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
 * @brief This file contains definition and declaration for Z-Wave NVM instance.
 * Because most of this declaration are depending on the application, this file
 * cannot be compiled with the stack. It must be compiled with the application.
 * Content of zpal_zwave_nvm_instance_config.h may be changed from configurator
 * tool of simplicity studio.
 */

#ifdef ZWAVE_SERIES_700
#include "zpal_zwave_nvm_instance.h"
#include "zpal_zwave_nvm_instance_config.h"
#include <nvm3.h>

#if 0 != ZPAL_ZW_NVM_CACHE_SIZE
/* cache used by NVM3 library for the z-wave nvm instance.
Cannot be declared in a file compiled with ZPAL because it depend on the application.*/
static nvm3_CacheEntry_t zpal_zwNvmCache[ZPAL_ZW_NVM_CACHE_SIZE] = {{ 0 }};
#endif

size_t zpal_zwave_nvm_get_cache_size(void)
{
  return ZPAL_ZW_NVM_CACHE_SIZE;
}

void* zpal_zwave_nvm_get_cache_pointer(void)
{
#if 0 != ZPAL_ZW_NVM_CACHE_SIZE
  return (void *) zpal_zwNvmCache;
#else
  return NULL;
#endif
}

size_t zpal_zwave_nvm_get_max_object_size(void)
{
  return ZPAL_ZW_NVM_MAX_OBJECT_SIZE;
}

size_t zpal_zwave_nvm_get_repack_headroom(void)
{
  return ZPAL_ZW_NVM_INSTANCE_REPACK_HEADROOM;
}

#endif

