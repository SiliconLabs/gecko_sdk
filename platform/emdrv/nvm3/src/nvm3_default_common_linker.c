/***************************************************************************//**
 * @file
 * @brief NVM3 definition of the default data structures.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "nvm3.h"
#include "nvm3_hal_flash.h"
#include "nvm3_default_config.h"

#if defined(NVM3_BASE)
/* Manually control the NVM3 address and size */

#elif defined (__ICCARM__)

__root uint8_t nvm3_default_storage[NVM3_DEFAULT_NVM_SIZE] @ "SIMEE";
#define NVM3_BASE (nvm3_default_storage)

#elif defined (__GNUC__)

extern char linker_nvm_begin;

__attribute__((used)) uint8_t nvm3_default_storage[NVM3_DEFAULT_NVM_SIZE] __attribute__ ((section(".simee")));
#define NVM3_BASE (&linker_nvm_begin)

#else
#error "Unsupported toolchain"
#endif

nvm3_Handle_t  nvm3_defaultHandleData;
nvm3_Handle_t *nvm3_defaultHandle = &nvm3_defaultHandleData;

#if (NVM3_DEFAULT_CACHE_SIZE != 0)
static nvm3_CacheEntry_t defaultCache[NVM3_DEFAULT_CACHE_SIZE];
#endif

nvm3_Init_t nvm3_defaultInitData =
{
  (nvm3_HalPtr_t)NVM3_BASE,
  NVM3_DEFAULT_NVM_SIZE,
#if (NVM3_DEFAULT_CACHE_SIZE != 0)
  defaultCache,
#else
  NULL,
#endif
  NVM3_DEFAULT_CACHE_SIZE,
  NVM3_DEFAULT_MAX_OBJECT_SIZE,
  NVM3_DEFAULT_REPACK_HEADROOM,
  &nvm3_halFlashHandle,
};

nvm3_Init_t *nvm3_defaultInit = &nvm3_defaultInitData;

Ecode_t nvm3_initDefault(void)
{
  return nvm3_open(nvm3_defaultHandle, nvm3_defaultInit);
}

Ecode_t nvm3_deinitDefault(void)
{
  return nvm3_close(nvm3_defaultHandle);
}
