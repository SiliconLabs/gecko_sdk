/***************************************************************************//**
 * @file
 * @brief Application interface to the bootloader.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include "btl_interface.h"

// -----------------------------------------------------------------------------
// Veneer NSC functions

extern int32_t bootloader_nsc_getInfo(sli_tz_invec *in_vec, size_t in_len,
                                      sli_tz_outvec *out_vec, size_t out_len);
extern int32_t bootloader_nsc_init(void);
extern int32_t bootloader_nsc_deinit(void);
extern int32_t bootloader_nsc_rebootAndInstall(void);
extern int32_t bootloader_nsc_parseImageInfo(sli_tz_invec *in_vec, size_t in_len,
                                             sli_tz_outvec *out_vec, size_t out_len);
extern uint32_t bootloader_nsc_parserContextSize(void);
extern int32_t bootloader_nsc_verifyApplication(uint32_t startAddress, uint32_t notUsed);
extern int32_t bootloader_nsc_secureBootEnforced(void);
extern int32_t bootloader_nsc_getUpgradeLocation(sli_tz_invec *in_vec, size_t in_len,
                                                 sli_tz_outvec *out_vec, size_t out_len);
extern uint32_t bootloader_nsc_remainingApplicationUpgrades(void);
extern int32_t bootloader_nsc_getCertificateVersion(sli_tz_invec *in_vec, size_t in_len,
                                                    sli_tz_outvec *out_vec, size_t out_len);
extern int32_t bootloader_nsc_getStorageInfo(sli_tz_invec *in_vec, size_t in_len,
                                             sli_tz_outvec *out_vec, size_t out_len);
extern int32_t bootloader_nsc_getStorageSlotInfo(sli_tz_invec *in_vec, size_t in_len,
                                                 sli_tz_outvec *out_vec, size_t out_len);
extern int32_t bootloader_nsc_readStorage(sli_tz_invec *in_vec, size_t in_len,
                                          sli_tz_outvec *out_vec, size_t out_len);
extern int32_t bootloader_nsc_writeStorage(sli_tz_invec *in_vec, size_t in_len,
                                           sli_tz_outvec *out_vec, size_t out_len);
extern int32_t bootloader_nsc_eraseWriteStorage(sli_tz_invec *in_vec, size_t in_len,
                                                sli_tz_outvec *out_vec, size_t out_len);
extern int32_t bootloader_nsc_eraseStorageSlot(uint32_t slotId, uint32_t notUsed);
extern int32_t bootloader_nsc_initChunkedEraseStorageSlot(sli_tz_invec *in_vec, size_t in_len,
                                                          sli_tz_outvec *out_vec, size_t out_len);
extern int32_t bootloader_nsc_chunkedEraseStorageSlot(sli_tz_invec *in_vec, size_t in_len,
                                                      sli_tz_outvec *out_vec, size_t out_len);
extern int32_t bootloader_nsc_setImageToBootload(int32_t slotId, uint32_t notUsed);
extern int32_t bootloader_nsc_setImagesToBootload(sli_tz_invec *in_vec, size_t in_len,
                                                  sli_tz_outvec *out_vec, size_t out_len);
extern int32_t bootloader_nsc_getImagesToBootload(sli_tz_invec *in_vec, size_t in_len,
                                                  sli_tz_outvec *out_vec, size_t out_len);
extern int32_t bootloader_nsc_appendImageToBootloadList(int32_t slotId, uint32_t notUsed);
extern int32_t bootloader_nsc_initVerifyImage(uint32_t slotId, uint32_t notUsed);
extern int32_t bootloader_nsc_continueVerifyImage(void);
extern int32_t bootloader_nsc_verifyImage(uint32_t slotId, uint32_t notUsed);
extern int32_t bootloader_nsc_getImageInfo(sli_tz_invec *in_vec, size_t in_len,
                                           sli_tz_outvec *out_vec, size_t out_len);
extern int32_t bootloader_nsc_storageIsBusy(void);
extern int32_t bootloader_nsc_getAllocatedDMAChannel(void);
extern uint32_t bootloader_nsc_getResetReason(void);

// -----------------------------------------------------------------------------
// Functions

BootloaderResetCause_t bootloader_getResetReason(void)
{
  BootloaderResetCause_t resetReason = { 0U };
  uint32_t ret = sli_tz_ns_interface_dispatch_noarg(
    (sli_tz_veneer_noarg_fn) bootloader_nsc_getResetReason
    );
  resetReason.reason    = (ret >> 16U);
  resetReason.signature = (ret & 0xFFFFU);
  return resetReason;
}

void bootloader_getInfo(BootloaderInformation_t *info)
{
  sli_tz_outvec out_vec[] = {
    { .base = info, .len = sizeof(BootloaderInformation_t) }
  };

  sli_tz_ns_interface_dispatch(
    (sli_tz_veneer_fn) bootloader_nsc_getInfo,
    0U, 0U, (uint32_t) out_vec, IOVEC_LEN(out_vec)
    );
}

int32_t bootloader_init(void)
{
  return sli_tz_ns_interface_dispatch_noarg(bootloader_nsc_init);
}

int32_t bootloader_deinit(void)
{
  return sli_tz_ns_interface_dispatch_noarg(bootloader_nsc_deinit);
}

void bootloader_rebootAndInstall(void)
{
  sli_tz_ns_interface_dispatch_noarg(
    (sli_tz_veneer_noarg_fn) bootloader_nsc_rebootAndInstall
    );
}

int32_t bootloader_parseImageInfo(uint8_t           data[],
                                  size_t            numBytes,
                                  ApplicationData_t *appInfo,
                                  uint32_t          *bootloaderVersion)
{
  sli_tz_invec in_vec[] = {
    { .base = data, .len = numBytes }
  };
  sli_tz_outvec out_vec[] = {
    { .base = appInfo, .len = sizeof(ApplicationData_t) },
    { .base = bootloaderVersion, .len = sizeof(bootloaderVersion[0]) }
  };

  return sli_tz_ns_interface_dispatch(
    (sli_tz_veneer_fn) bootloader_nsc_parseImageInfo,
    (uint32_t) in_vec, IOVEC_LEN(in_vec), (uint32_t) out_vec, IOVEC_LEN(out_vec)
    );
}

uint32_t bootloader_parserContextSize(void)
{
  return (uint32_t) sli_tz_ns_interface_dispatch_noarg(
    (sli_tz_veneer_noarg_fn) bootloader_nsc_parserContextSize
    );
}

bool bootloader_verifyApplication(uint32_t startAddress)
{
  return (bool) sli_tz_ns_interface_dispatch_simple(
    (sli_tz_veneer_simple_fn) bootloader_nsc_verifyApplication,
    startAddress,
    0U
    );
}

bool bootloader_secureBootEnforced(void)
{
  return (bool) sli_tz_ns_interface_dispatch_noarg(
    (sli_tz_veneer_noarg_fn) bootloader_nsc_secureBootEnforced
    );
}

bool bootloader_getUpgradeLocation(uint32_t *location)
{
  sli_tz_outvec out_vec[] = {
    { .base = location, .len = sizeof(location[0]) }
  };

  return (bool) sli_tz_ns_interface_dispatch(
    (sli_tz_veneer_fn) bootloader_nsc_getUpgradeLocation,
    0U, 0U, (uint32_t) out_vec, IOVEC_LEN(out_vec)
    );
}

uint32_t bootloader_remainingApplicationUpgrades(void)
{
  return (uint32_t) sli_tz_ns_interface_dispatch_noarg(
    (sli_tz_veneer_noarg_fn) bootloader_nsc_remainingApplicationUpgrades
    );
}

bool bootloader_getCertificateVersion(uint32_t *version)
{
  sli_tz_outvec out_vec[] = {
    { .base = version, .len = sizeof(version[0]) }
  };

  return (bool) sli_tz_ns_interface_dispatch(
    (sli_tz_veneer_fn) bootloader_nsc_getCertificateVersion,
    0U, 0U, (uint32_t) out_vec, IOVEC_LEN(out_vec)
    );
}

void bootloader_getStorageInfo(BootloaderStorageInformation_t *info)
{
  sli_tz_outvec out_vec[] = {
    { .base = info, .len = sizeof(BootloaderStorageInformation_t) }
  };

  sli_tz_ns_interface_dispatch(
    (sli_tz_veneer_fn) bootloader_nsc_getStorageInfo,
    0U, 0U, (uint32_t) out_vec, IOVEC_LEN(out_vec)
    );
}

int32_t bootloader_getStorageSlotInfo(uint32_t                slotId,
                                      BootloaderStorageSlot_t *slot)
{
  sli_tz_invec in_vec[] = {
    { .base = &slotId, .len = sizeof(slotId) }
  };
  sli_tz_outvec out_vec[] = {
    { .base = slot, .len = sizeof(BootloaderStorageSlot_t) }
  };

  return sli_tz_ns_interface_dispatch(
    (sli_tz_veneer_fn) bootloader_nsc_getStorageSlotInfo,
    (uint32_t) in_vec, IOVEC_LEN(in_vec), (uint32_t) out_vec, IOVEC_LEN(out_vec)
    );
}

int32_t bootloader_readStorage(uint32_t slotId,
                               uint32_t offset,
                               uint8_t  *buffer,
                               size_t   length)
{
  sli_tz_invec in_vec[] = {
    { .base = &slotId, .len = sizeof(slotId) },
    { .base = &offset, .len = sizeof(offset) }
  };
  sli_tz_outvec out_vec[] = {
    { .base = buffer, .len = length }
  };

  return sli_tz_ns_interface_dispatch(
    (sli_tz_veneer_fn) bootloader_nsc_readStorage,
    (uint32_t) in_vec, IOVEC_LEN(in_vec), (uint32_t) out_vec, IOVEC_LEN(out_vec)
    );
}

int32_t bootloader_writeStorage(uint32_t slotId,
                                uint32_t offset,
                                uint8_t  *buffer,
                                size_t   length)
{
  sli_tz_invec in_vec[] = {
    { .base = &slotId, .len = sizeof(slotId) },
    { .base = &offset, .len = sizeof(offset) },
    { .base = buffer, .len = length }
  };

  return sli_tz_ns_interface_dispatch(
    (sli_tz_veneer_fn) bootloader_nsc_writeStorage,
    (uint32_t) in_vec, IOVEC_LEN(in_vec), 0U, 0U
    );
}

int32_t bootloader_eraseWriteStorage(uint32_t slotId,
                                     uint32_t offset,
                                     uint8_t  *buffer,
                                     size_t   length)
{
  sli_tz_invec in_vec[] = {
    { .base = &slotId, .len = sizeof(slotId) },
    { .base = &offset, .len = sizeof(offset) },
    { .base = buffer, .len = length }
  };

  return sli_tz_ns_interface_dispatch(
    (sli_tz_veneer_fn) bootloader_nsc_eraseWriteStorage,
    (uint32_t) in_vec, IOVEC_LEN(in_vec), 0U, 0U
    );
}

int32_t bootloader_eraseStorageSlot(uint32_t slotId)
{
  return sli_tz_ns_interface_dispatch_simple(
    (sli_tz_veneer_simple_fn) bootloader_nsc_eraseStorageSlot,
    slotId,
    0U
    );
}

int32_t bootloader_initChunkedEraseStorageSlot(uint32_t                slotId,
                                               BootloaderEraseStatus_t *eraseStat)
{
  sli_tz_invec in_vec[] = {
    { .base = &slotId, .len = sizeof(slotId) }
  };
  sli_tz_outvec out_vec[] = {
    { .base = eraseStat, .len = sizeof(BootloaderEraseStatus_t) }
  };

  return sli_tz_ns_interface_dispatch(
    (sli_tz_veneer_fn) bootloader_nsc_initChunkedEraseStorageSlot,
    (uint32_t) in_vec, IOVEC_LEN(in_vec), (uint32_t) out_vec, IOVEC_LEN(out_vec)
    );
}

int32_t bootloader_chunkedEraseStorageSlot(BootloaderEraseStatus_t *eraseStat)
{
  sli_tz_invec in_vec[] = {
    { .base = (const void *) eraseStat->currentPageAddr, .len = eraseStat->pageSize }
  };
  sli_tz_outvec out_vec[] = {
    { .base = eraseStat, .len = sizeof(BootloaderEraseStatus_t) }
  };

  return sli_tz_ns_interface_dispatch(
    (sli_tz_veneer_fn) bootloader_nsc_chunkedEraseStorageSlot,
    (uint32_t) in_vec, IOVEC_LEN(in_vec), (uint32_t) out_vec, IOVEC_LEN(out_vec)
    );
}

int32_t bootloader_setImageToBootload(int32_t slotId)
{
  return sli_tz_ns_interface_dispatch_simple(
    (sli_tz_veneer_simple_fn) bootloader_nsc_setImageToBootload,
    (uint32_t) slotId,
    0U
    );
}

int32_t bootloader_setImagesToBootload(int32_t *slotIds, size_t length)
{
  sli_tz_invec in_vec[] = {
    { .base = slotIds, .len = length * sizeof(slotIds[0]) }
  };

  return sli_tz_ns_interface_dispatch(
    (sli_tz_veneer_fn) bootloader_nsc_setImagesToBootload,
    (uint32_t) in_vec, IOVEC_LEN(in_vec), 0U, 0U
    );
}

int32_t bootloader_getImagesToBootload(int32_t *slotIds, size_t length)
{
  sli_tz_outvec out_vec[] = {
    { .base = slotIds, .len = length * sizeof(slotIds[0]) }
  };

  return sli_tz_ns_interface_dispatch(
    (sli_tz_veneer_fn) bootloader_nsc_getImagesToBootload,
    0U, 0U, (uint32_t) out_vec, IOVEC_LEN(out_vec)
    );
}

int32_t bootloader_appendImageToBootloadList(int32_t slotId)
{
  return sli_tz_ns_interface_dispatch_simple(
    (sli_tz_veneer_simple_fn) bootloader_nsc_appendImageToBootloadList,
    (uint32_t) slotId,
    0U
    );
}

int32_t bootloader_initVerifyImage(uint32_t slotId)
{
  return sli_tz_ns_interface_dispatch_simple(
    (sli_tz_veneer_simple_fn) bootloader_nsc_initVerifyImage,
    slotId,
    0U
    );
}

int32_t bootloader_continueVerifyImage(void)
{
  return sli_tz_ns_interface_dispatch_noarg(
    (sli_tz_veneer_noarg_fn) bootloader_nsc_continueVerifyImage
    );
}

int32_t bootloader_verifyImage(uint32_t slotId)
{
  return sli_tz_ns_interface_dispatch_simple(
    (sli_tz_veneer_simple_fn) bootloader_nsc_verifyImage,
    slotId,
    0U
    );
}

int32_t bootloader_getImageInfo(uint32_t          slotId,
                                ApplicationData_t *appInfo,
                                uint32_t          *bootloaderVersion)
{
  sli_tz_invec in_vec[] = {
    { .base = &slotId, .len = sizeof(slotId) }
  };
  sli_tz_outvec out_vec[] = {
    { .base = appInfo, .len = sizeof(ApplicationData_t) },
    { .base = bootloaderVersion, .len = sizeof(bootloaderVersion[0]) }
  };

  return sli_tz_ns_interface_dispatch(
    (sli_tz_veneer_fn) bootloader_nsc_getImageInfo,
    (uint32_t) in_vec, IOVEC_LEN(in_vec), (uint32_t) out_vec, IOVEC_LEN(out_vec)
    );
}

bool bootloader_storageIsBusy(void)
{
  return (bool) sli_tz_ns_interface_dispatch_noarg(
    (sli_tz_veneer_noarg_fn) bootloader_nsc_storageIsBusy
    );
}

int32_t bootloader_getAllocatedDMAChannel(void)
{
  return sli_tz_ns_interface_dispatch_noarg(
    (sli_tz_veneer_noarg_fn) bootloader_nsc_getAllocatedDMAChannel
    );
}
