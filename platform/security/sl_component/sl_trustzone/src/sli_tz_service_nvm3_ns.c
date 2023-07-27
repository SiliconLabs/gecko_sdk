/***************************************************************************//**
 * @file
 * @brief Silicon Labs TrustZone secure NVM3 service (non-secure side).
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

#if defined(TZ_SERVICE_CONFIG_PRESENT)
  #include "tz_service_config_autogen.h"
#endif

#include "tfm_ns_interface.h"
#include "sli_tz_s_interface.h"

#include "sli_tz_service_nvm3.h"
#include "nvm3.h"
#include "nvm3_default_config.h"
#include "sl_mpu.h"

// The default handles are located in S together with the rest of the NVM3 code.
// However, the NVM3 API requires the handle pointer to be sent in explicitly,
// which NS does not know. We therefore use a magic value in the nvmAdr member,
// which makes the NVM3 service in the secure library use its internal default
// handle.
nvm3_Handle_t placeholder_default_handle = {
  .nvmAdr = (nvm3_HalPtr_t)SLI_TZ_SERVICE_NVM3_DEFAULT_HANDLE_MAGIC
};
nvm3_Handle_t *nvm3_defaultHandle = &placeholder_default_handle;

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

nvm3_Init_t nvm3_defaultInitData =
{
  .nvmAdr = (nvm3_HalPtr_t)NVM3_BASE,
  .nvmSize = NVM3_DEFAULT_NVM_SIZE,
  // The secure library owns the NVM3 cache. Setting the cache pointer to NULL
  // here indicates that the cache on the secure side should be used.
  .cachePtr = NULL,
  .cacheEntryCount = NVM3_DEFAULT_CACHE_SIZE,
  .maxObjectSize = NVM3_DEFAULT_MAX_OBJECT_SIZE,
  .repackHeadroom = NVM3_DEFAULT_REPACK_HEADROOM,
  // The secure library owns the flash handle. Setting the flash handle to NULL
  // here indicates that the flash handle on the secure side should be used.
  .halHandle = NULL,
};

nvm3_Init_t *nvm3_defaultInit = &nvm3_defaultInitData;

Ecode_t nvm3_initDefault(void)
{
  Ecode_t nvm3_status;
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_INITDEFAULT_SID;

  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    // Pass the defaultInitData from NS and have S set it up for the default
    // instance in S.
    { nvm3_defaultInit, sizeof(nvm3_defaultInitData) },
  };

  nvm3_status = tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                                          (uint32_t)in_vec, IOVEC_LEN(in_vec),
                                          (uint32_t)NULL, 0);
  if (nvm3_status != ECODE_NVM3_OK) {
    return nvm3_status;
  }

  sl_status_t sl_status = sl_mpu_disable_execute((uint32_t)
                                                 (nvm3_defaultInit->nvmAdr),
                                                 (uint32_t)
                                                 (nvm3_defaultInit->nvmAdr)
                                                 + nvm3_defaultInit->nvmSize - 1u,
                                                 nvm3_defaultInit->nvmSize);
  if (sl_status != SL_STATUS_OK) {
    nvm3_status = ECODE_NVM3_ERR_INT_ADDR_INVALID;
  }
  return nvm3_status;
}

Ecode_t nvm3_deinitDefault(void)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_DEINITDEFAULT_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
  };

  return tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                                   (uint32_t)in_vec, IOVEC_LEN(in_vec),
                                   (uint32_t)NULL, 0);
}

#if defined(TZ_SERVICE_NVM3_PRESENT)
Ecode_t nvm3_readPartialData(nvm3_Handle_t* h, nvm3_ObjectKey_t key, void* value, size_t ofs, size_t len)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_READPARTIALDATA_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    { h, sizeof(nvm3_Handle_t) },
    { &key, sizeof(key) },
    { &ofs, sizeof(ofs) },
  };
  sli_tz_outvec out_vec[] = {
    { value, len },
  };

  return tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                                   (uint32_t)in_vec, IOVEC_LEN(in_vec),
                                   (uint32_t)out_vec, IOVEC_LEN(out_vec));
}

Ecode_t nvm3_readData(nvm3_Handle_t *h, nvm3_ObjectKey_t key, void *value, size_t len)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_READDATA_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    { h, sizeof(nvm3_Handle_t) },
    { &key, sizeof(key) },
  };
  sli_tz_outvec out_vec[] = {
    { value, len },
  };

  return tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                                   (uint32_t)in_vec, IOVEC_LEN(in_vec),
                                   (uint32_t)out_vec, IOVEC_LEN(out_vec));
}

Ecode_t nvm3_writeData(nvm3_Handle_t *h, nvm3_ObjectKey_t key, const void *value, size_t len)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_WRITEDATA_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    { h, sizeof(nvm3_Handle_t) },
    { &key, sizeof(key) },
    { value, len },
  };

  return tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                                   (uint32_t)in_vec, IOVEC_LEN(in_vec),
                                   (uint32_t)NULL, 0);
}

Ecode_t nvm3_deleteObject(nvm3_Handle_t *h, nvm3_ObjectKey_t key)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_DELETEOBJECT_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    { h, sizeof(nvm3_Handle_t) },
    { &key, sizeof(key) },
  };

  return tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                                   (uint32_t)in_vec, IOVEC_LEN(in_vec),
                                   (uint32_t)NULL, 0);
}

Ecode_t nvm3_open(nvm3_Handle_t *h, const nvm3_Init_t *i)
{
  if (h == nvm3_defaultHandle) {
    if (i != nvm3_defaultInit) {
      // The NVM3 default handle is special in the sense that it is actually owned by
      // the secure library, and the nvm3_defaultHandle here is just used to indicate that
      // the internal default handle should be used. However, we need to use nvm3_initDefault()
      // to indicate to the secure library that the special default handle should be
      // initialized. This can't be done currently if the init struct is anything other than
      // the default init struct.
      return ECODE_NVM3_ERR_PARAMETER;
    }
    return nvm3_initDefault();
  }

  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_OPEN_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    { i, sizeof(nvm3_Init_t) },
  };
  sli_tz_outvec out_vec[] = {
    { h, sizeof(nvm3_Handle_t) },
  };

  Ecode_t nvm3_status =
    tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                              (uint32_t)in_vec, IOVEC_LEN(in_vec),
                              (uint32_t)out_vec, IOVEC_LEN(out_vec));

  sl_status_t sl_status = sl_mpu_disable_execute((uint32_t)(i->nvmAdr),
                                                 (uint32_t)(i->nvmAdr)
                                                 + i->nvmSize - 1u,
                                                 i->nvmSize);
  if (sl_status != SL_STATUS_OK) {
    nvm3_status = ECODE_NVM3_ERR_INT_ADDR_INVALID;
  }

  return nvm3_status;
}

Ecode_t nvm3_close(nvm3_Handle_t *h)
{
  if (h == nvm3_defaultHandle) {
    return nvm3_deinitDefault();
  }

  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_CLOSE_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    { h, sizeof(nvm3_Handle_t) },
  };

  return tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                                   (uint32_t)in_vec, IOVEC_LEN(in_vec),
                                   (uint32_t)NULL, 0);
}

Ecode_t nvm3_getObjectInfo(nvm3_Handle_t *h, nvm3_ObjectKey_t key,
                           uint32_t *type, size_t *len)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_GETOBJECTINFO_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    { h, sizeof(nvm3_Handle_t) },
    { &key, sizeof(key) },
  };
  sli_tz_outvec out_vec[] = {
    { type, sizeof(uint32_t) },
    { len, sizeof(size_t) },
  };

  return tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                                   (uint32_t)in_vec, IOVEC_LEN(in_vec),
                                   (uint32_t)out_vec, IOVEC_LEN(out_vec));
}

Ecode_t nvm3_writeCounter(nvm3_Handle_t *h, nvm3_ObjectKey_t key, uint32_t value)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_WRITECOUNTER_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    { h, sizeof(nvm3_Handle_t) },
    { &key, sizeof(key) },
    { &value, sizeof(value) },
  };

  return tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                                   (uint32_t)in_vec, IOVEC_LEN(in_vec),
                                   (uint32_t)NULL, 0);
}

Ecode_t nvm3_readCounter(nvm3_Handle_t *h, nvm3_ObjectKey_t key, uint32_t *value)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_READCOUNTER_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    { h, sizeof(nvm3_Handle_t) },
    { &key, sizeof(key) },
  };
  sli_tz_outvec out_vec[] = {
    { value, sizeof(uint32_t) },
  };

  return tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                                   (uint32_t)in_vec, IOVEC_LEN(in_vec),
                                   (uint32_t)out_vec, IOVEC_LEN(out_vec));
}

Ecode_t nvm3_incrementCounter(nvm3_Handle_t *h, nvm3_ObjectKey_t key, uint32_t *newValue)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_INCREMENTCOUNTER_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    { h, sizeof(nvm3_Handle_t) },
    { &key, sizeof(key) },
  };
  sli_tz_outvec out_vec[] = {
    // Make sure to set the length to 0 if newValue is NULL, otherwise
    // the IOVEC check will return an error.
    { newValue, (newValue == NULL) ? 0 : sizeof(uint32_t) },
  };

  return tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                                   (uint32_t)in_vec, IOVEC_LEN(in_vec),
                                   (uint32_t)out_vec, IOVEC_LEN(out_vec));
}

Ecode_t nvm3_eraseAll(nvm3_Handle_t *h)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_ERASEALL_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    { h, sizeof(nvm3_Handle_t) },
  };

  return tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                                   (uint32_t)in_vec, IOVEC_LEN(in_vec),
                                   (uint32_t)NULL, 0);
}

Ecode_t nvm3_getEraseCount(nvm3_Handle_t *h, uint32_t *eraseCnt)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_GETERASECOUNT_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    { h, sizeof(nvm3_Handle_t) },
  };
  sli_tz_outvec out_vec[] = {
    { eraseCnt, sizeof(uint32_t) },
  };

  return tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                                   (uint32_t)in_vec, IOVEC_LEN(in_vec),
                                   (uint32_t)out_vec, IOVEC_LEN(out_vec));
}

void nvm3_setEraseCount(uint32_t eraseCnt)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_SETERASECOUNT_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    { &eraseCnt, sizeof(uint32_t) },
  };

  tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                            (uint32_t)in_vec, IOVEC_LEN(in_vec),
                            (uint32_t)NULL, 0);
}

Ecode_t nvm3_repack(nvm3_Handle_t *h)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_REPACK_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    { h, sizeof(nvm3_Handle_t) },
  };

  return tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                                   (uint32_t)in_vec, IOVEC_LEN(in_vec),
                                   (uint32_t)NULL, 0);
}

bool nvm3_repackNeeded(nvm3_Handle_t *h)
{
  bool ret_val = false;
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_REPACKNEEDED_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    { h, sizeof(nvm3_Handle_t) },
  };
  sli_tz_outvec out_vec[] = {
    { &ret_val, sizeof(ret_val) },
  };

  Ecode_t nvm3_status = tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                                                  (uint32_t)in_vec, IOVEC_LEN(in_vec),
                                                  (uint32_t)out_vec, IOVEC_LEN(out_vec));

  // false is returned if parameter validation failed.
  if (nvm3_status != ECODE_NVM3_OK) {
    return false;
  }

  return ret_val;
}

Ecode_t nvm3_resize(nvm3_Handle_t *h, nvm3_HalPtr_t newAddr, size_t newSize)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_RESIZE_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    { h, sizeof(nvm3_Handle_t) },
    { &newAddr, sizeof(newAddr) },
    { &newSize, sizeof(newSize) },
  };

  return tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                                   (uint32_t)in_vec, IOVEC_LEN(in_vec),
                                   (uint32_t)NULL, 0);
}

size_t nvm3_enumObjects(nvm3_Handle_t *h,
                        nvm3_ObjectKey_t *keyListPtr, size_t keyListSize,
                        nvm3_ObjectKey_t keyMin, nvm3_ObjectKey_t keyMax)
{
  size_t ret_val = 0;
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_ENUMOBJECTS_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    { h, sizeof(nvm3_Handle_t) },
    { &keyListSize, sizeof(keyListSize) },
    { &keyMin, sizeof(keyMin) },
    { &keyMax, sizeof(keyMax) },
  };
  sli_tz_outvec out_vec[] = {
    { &ret_val, sizeof(ret_val) },
    // Make sure to set the length to 0 if keyListPtr is NULL, otherwise
    // the IOVEC check will return an error.
    { keyListPtr, (keyListPtr == NULL) ? 0 : sizeof(nvm3_ObjectKey_t) },
  };

  Ecode_t status = tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                                             (uint32_t)in_vec, IOVEC_LEN(in_vec),
                                             (uint32_t)out_vec, IOVEC_LEN(out_vec));

  // Zero is returned if parameter validation failed.
  if (status != ECODE_NVM3_OK) {
    return 0;
  }

  return ret_val;
}

size_t nvm3_enumDeletedObjects(nvm3_Handle_t *h,
                               nvm3_ObjectKey_t *keyListPtr, size_t keyListSize,
                               nvm3_ObjectKey_t keyMin, nvm3_ObjectKey_t keyMax)
{
  size_t ret_val = 0;
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_NVM3_ENUMDELETEDOBJECTS_SID;
  sli_tz_invec in_vec[] = {
    { &fn_id, sizeof(sli_tz_fn_id) },
    { h, sizeof(nvm3_Handle_t) },
    { &keyListSize, sizeof(keyListSize) },
    { &keyMin, sizeof(keyMin) },
    { &keyMax, sizeof(keyMax) },
  };
  sli_tz_outvec out_vec[] = {
    { &ret_val, sizeof(ret_val) },
    // Make sure to set the length to 0 if keyListPtr is NULL, otherwise
    // the IOVEC check will return an error.
    { keyListPtr, (keyListPtr == NULL) ? 0 : sizeof(nvm3_ObjectKey_t) },
  };

  Ecode_t status = tfm_ns_interface_dispatch((veneer_fn)sli_tz_s_interface_dispatch_nvm3,
                                             (uint32_t)in_vec, IOVEC_LEN(in_vec),
                                             (uint32_t)out_vec, IOVEC_LEN(out_vec));

  // Zero is returned if parameter validation failed.
  if (status != ECODE_NVM3_OK) {
    return 0;
  }

  return ret_val;
}
#endif // defined(TZ_SERVICE_NVM3_PRESENT)
