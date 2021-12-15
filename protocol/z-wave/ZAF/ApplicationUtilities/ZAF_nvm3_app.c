/**
 * @file
 * @brief ZWave FileSystem Application module
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */
#include "ZAF_nvm3_app.h"

#include <stdbool.h>
#include <stdint.h>
#include "Assert.h"

//#define DEBUGPRINT
#include "DebugPrint.h"
#include <nvm3_hal_flash.h>


#define NVM3_APP_CACHE_SIZE  10
#ifdef ZWAVE_SERIES_800
#define NVM3_APP_NVM_SIZE    ((8192) * 3) // Page size 8KB * 3
#else
#define NVM3_APP_NVM_SIZE    12288
#endif
#define NVM3_APP_DEFAULT_REPACK_HEADROOM 0

#if defined (__ICCARM__)

#ifndef __NVM3APP__
#define __NVM3APP__ "SIMEE"
#endif

__root uint8_t nvm3AppStorage[NVM3_APP_NVM_SIZE] @ __NVM3APP__;

#elif defined (__GNUC__)

#ifndef __NVM3APP__
#ifdef BUILDING_WITH_UC
#define __NVM3APP__ ".zwavenvm"
extern uint32_t linker_zwave_nvm_begin;
#define ZW_NVM_BASE (&linker_zwave_nvm_begin)
#else
#define __NVM3APP__ ".nvm3App"
#define ZW_NVM_BASE (nvm3AppStorage)
#endif
#endif

__attribute__((used)) static const uint8_t nvm3AppStorage[NVM3_APP_NVM_SIZE] __attribute__ ((section(__NVM3APP__)));

#else
#error "Unsupported toolchain"
#endif

static nvm3_Handle_t  nvm3_appdefaultHandleData;

static nvm3_CacheEntry_t appdefaultCache[NVM3_APP_CACHE_SIZE];

static const nvm3_Init_t nvm3_appdefaultInitData =
{
  .nvmAdr          = (nvm3_HalPtr_t) ZW_NVM_BASE,
  .nvmSize         = NVM3_APP_NVM_SIZE,
  .cachePtr        = appdefaultCache,
  .cacheEntryCount = NVM3_APP_CACHE_SIZE,
  .maxObjectSize   = NVM3_MAX_OBJECT_SIZE_DEFAULT,
  .repackHeadroom  = NVM3_APP_DEFAULT_REPACK_HEADROOM,
  .halHandle       = &nvm3_halFlashHandle
};

bool ApplicationFileSystemInit(nvm3_Handle_t** pFileSystemApplication)
{
  uint32_t retvalue; 
  DPRINT("Init App NVM3 File System\r\n");

  retvalue = nvm3_open(&nvm3_appdefaultHandleData, &nvm3_appdefaultInitData);
  if(ECODE_NVM3_OK != retvalue)
  {
	  DPRINTF("Failed Init App File System return value =%x\r\n",retvalue);
	  ASSERT(false); //Assert has been kept for debugging , can be removed from production code. This error can only be caused by some internal flash HW failure

	  return false;
  }

  // Set application file system handle
  *pFileSystemApplication = &nvm3_appdefaultHandleData;

  return true;
}

nvm3_Handle_t * ZAF_GetFileSystemHandle(void)
{
  return &nvm3_appdefaultHandleData;
}
