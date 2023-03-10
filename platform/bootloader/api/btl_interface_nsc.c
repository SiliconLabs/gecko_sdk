/***************************************************************************//**
 * @file
 * @brief Application NSC interface to the bootloader.
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

#include <arm_cmse.h>
#include <string.h>
#include "btl_interface.h"
#include "btl_interface_storage.h"
#include "btl_reset_info.h"

#include "sli_tz_iovec_check.h"

#include "sl_common.h"
#include "fih.h"

// -----------------------------------------------------------------------------
// Defines

#define BL_MPU_WRAPPER(func_name, ...) \
  disable_mpu();                       \
  func_name(__VA_ARGS__);              \
  enable_mpu();

#define BL_MPU_WRAPPER_RET(func_name, ret, ...) \
  disable_mpu();                                \
  ret = func_name(__VA_ARGS__);                 \
  enable_mpu();

// -----------------------------------------------------------------------------
// Global variable

static bool mpu_enabled = false;

// -----------------------------------------------------------------------------
// Global context buffer

static uint8_t context_buffer[BOOTLOADER_STORAGE_VERIFICATION_CONTEXT_SIZE] SL_ATTRIBUTE_ALIGN(4) = { 0 };

// -----------------------------------------------------------------------------
// Static functions

static void disable_mpu(void)
{
  mpu_enabled = (bool)(MPU->CTRL & MPU_CTRL_ENABLE_Msk);
  if (mpu_enabled) {
    ARM_MPU_Disable();
  }
}

static void enable_mpu(void)
{
  if (mpu_enabled) {
    ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk);
  }
}

static void bl_fatal_assert_action(void)
{
  BootloaderResetCause_t* resetCause = (BootloaderResetCause_t*) (RAM_MEM_BASE);
  resetCause->reason = BOOTLOADER_RESET_REASON_TZ_FAULT;
  resetCause->signature = BOOTLOADER_RESET_SIGNATURE_VALID;
  NVIC_SystemReset();
  __builtin_unreachable();
}

static fih_int bl_assert_tz_iovecs_in_ns(sli_tz_invec *in_vec, size_t in_len,
                                         sli_tz_outvec *out_vec, size_t out_len,
                                         sli_tz_iovec_params_t *iovec_copy_ptr)
{
  fih_int fih_rc = FIH_FAILURE;
  uint32_t status = sli_tz_iovecs_live_in_ns(in_vec,
                                             in_len,
                                             out_vec,
                                             out_len,
                                             iovec_copy_ptr);
  if (status != SLI_TZ_IOVEC_OK) {
    bl_fatal_assert_action();
  }
  fih_rc = FIH_SUCCESS;
  FIH_RET(fih_rc);
}

// -----------------------------------------------------------------------------
// NSC functions

__attribute__((cmse_nonsecure_entry))
uint32_t bootloader_nsc_getResetReason(void)
{
  BootloaderResetCause_t resetReason = { 0 };
  BL_MPU_WRAPPER_RET(bootloader_getResetReason, resetReason);
  return (resetReason.reason << 16) | resetReason.signature;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_getInfo(sli_tz_invec *in_vec, size_t in_len,
                               sli_tz_outvec *out_vec, size_t out_len)
{
  fih_int fih_rc = FIH_FAILURE;
  (void) fih_rc;
  if (out_vec[0].len != sizeof(BootloaderInformation_t)) {
    bl_fatal_assert_action();
  }

  sli_tz_iovec_params_t iovec_copy = { 0 };
  FIH_CALL(bl_assert_tz_iovecs_in_ns, fih_rc, in_vec, in_len, out_vec, out_len, &iovec_copy);

  BootloaderInformation_t *info = (BootloaderInformation_t *) iovec_copy.out_vec[0].base;

  BL_MPU_WRAPPER(bootloader_getInfo, info);
  return 0; // Workaround for -Wcast-function-type
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_init(void)
{
  int32_t ret = -1;
  BL_MPU_WRAPPER_RET(bootloader_init, ret);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_deinit(void)
{
  int32_t ret = -1;
  BL_MPU_WRAPPER_RET(bootloader_deinit, ret);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_rebootAndInstall(void)
{
  bootloader_rebootAndInstall();
  return 0; // Workaround for -Wcast-function-type
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_parseImageInfo(sli_tz_invec *in_vec, size_t in_len,
                                      sli_tz_outvec *out_vec, size_t out_len)
{
  fih_int fih_rc = FIH_FAILURE;
  (void) fih_rc;
  if ((out_vec[0].len != sizeof(ApplicationData_t))
      || (out_vec[1].len != sizeof(uint32_t))) {
    bl_fatal_assert_action();
  }

  sli_tz_iovec_params_t iovec_copy = { 0 };
  FIH_CALL(bl_assert_tz_iovecs_in_ns, fih_rc, in_vec, in_len, out_vec, out_len, &iovec_copy);

  uint8_t *data               = (uint8_t *) iovec_copy.in_vec[0].base;
  size_t numBytes             = iovec_copy.in_vec[0].len;
  ApplicationData_t *appInfo  = (ApplicationData_t *) iovec_copy.out_vec[0].base;
  uint32_t *bootloaderVersion = (uint32_t *) iovec_copy.out_vec[1].base;

  int32_t ret = -1;

  BL_MPU_WRAPPER_RET(bootloader_initParser,
                     ret,
                     (BootloaderParserContext_t *)context_buffer,
                     BOOTLOADER_STORAGE_VERIFICATION_CONTEXT_SIZE);

  if (ret != BOOTLOADER_OK) {
    return ret;
  }

  BL_MPU_WRAPPER_RET(bootloader_parseImageInfo,
                     ret,
                     (BootloaderParserContext_t *)context_buffer,
                     data,
                     numBytes,
                     appInfo,
                     bootloaderVersion);

  memset(context_buffer, 0u, BOOTLOADER_STORAGE_VERIFICATION_CONTEXT_SIZE);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
uint32_t bootloader_nsc_parserContextSize(void)
{
  uint32_t ret = 0xFFFFFFFFUL;
  BL_MPU_WRAPPER_RET(bootloader_parserContextSize, ret);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
bool bootloader_nsc_verifyApplication(uint32_t startAddress, uint32_t notUsed)
{
  (void) notUsed;
  bool ret = false;
  BL_MPU_WRAPPER_RET(bootloader_verifyApplication, ret, startAddress);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_secureBootEnforced(void)
{
  bool ret = false;
  BL_MPU_WRAPPER_RET(bootloader_secureBootEnforced, ret);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_getUpgradeLocation(sli_tz_invec *in_vec, size_t in_len,
                                          sli_tz_outvec *out_vec, size_t out_len)
{
  fih_int fih_rc = FIH_FAILURE;
  (void) fih_rc;
  if (out_vec[0].len != sizeof(uint32_t)) {
    bl_fatal_assert_action();
  }

  sli_tz_iovec_params_t iovec_copy = { 0 };
  FIH_CALL(bl_assert_tz_iovecs_in_ns, fih_rc, in_vec, in_len, out_vec, out_len, &iovec_copy);

  uint32_t *location = (uint32_t *) iovec_copy.out_vec[0].base;

  bool ret = false;
  BL_MPU_WRAPPER_RET(bootloader_getUpgradeLocation, ret, location);
  return (int32_t) ret;
}

__attribute__((cmse_nonsecure_entry))
uint32_t bootloader_nsc_remainingApplicationUpgrades(void)
{
  uint32_t ret = 0xFFFFFFFFUL;
  BL_MPU_WRAPPER_RET(bootloader_remainingApplicationUpgrades, ret);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_getCertificateVersion(sli_tz_invec *in_vec, size_t in_len,
                                             sli_tz_outvec *out_vec, size_t out_len)
{
  fih_int fih_rc = FIH_FAILURE;
  (void) fih_rc;
  if (out_vec[0].len != sizeof(uint32_t)) {
    bl_fatal_assert_action();
  }

  sli_tz_iovec_params_t iovec_copy = { 0 };
  FIH_CALL(bl_assert_tz_iovecs_in_ns, fih_rc, in_vec, in_len, out_vec, out_len, &iovec_copy);

  uint32_t *version = (uint32_t *) iovec_copy.out_vec[0].base;

  bool ret = false;
  BL_MPU_WRAPPER_RET(bootloader_getCertificateVersion, ret, version);
  return (int32_t) ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_getStorageInfo(sli_tz_invec *in_vec, size_t in_len,
                                      sli_tz_outvec *out_vec, size_t out_len)
{
  fih_int fih_rc = FIH_FAILURE;
  (void) fih_rc;
  if (out_vec[0].len != sizeof(BootloaderStorageInformation_t)) {
    bl_fatal_assert_action();
  }

  sli_tz_iovec_params_t iovec_copy = { 0 };
  FIH_CALL(bl_assert_tz_iovecs_in_ns, fih_rc, in_vec, in_len, out_vec, out_len, &iovec_copy);

  BootloaderStorageInformation_t *info = (BootloaderStorageInformation_t *) iovec_copy.out_vec[0].base;

  BL_MPU_WRAPPER(bootloader_getStorageInfo, info);
  return 0; // Workaround for -Wcast-function-type
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_getStorageSlotInfo(sli_tz_invec *in_vec, size_t in_len,
                                          sli_tz_outvec *out_vec, size_t out_len)
{
  fih_int fih_rc = FIH_FAILURE;
  (void) fih_rc;
  if ((in_vec[0].len != sizeof(uint32_t))
      || (out_vec[0].len != sizeof(BootloaderStorageSlot_t))) {
    bl_fatal_assert_action();
  }

  sli_tz_iovec_params_t iovec_copy = { 0 };
  FIH_CALL(bl_assert_tz_iovecs_in_ns, fih_rc, in_vec, in_len, out_vec, out_len, &iovec_copy);

  uint32_t slotId               = *((uint32_t *) iovec_copy.in_vec[0].base);
  BootloaderStorageSlot_t *slot = (BootloaderStorageSlot_t *) iovec_copy.out_vec[0].base;

  int32_t ret = -1;
  BL_MPU_WRAPPER_RET(bootloader_getStorageSlotInfo, ret, slotId, slot);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_readStorage(sli_tz_invec *in_vec, size_t in_len,
                                   sli_tz_outvec *out_vec, size_t out_len)
{
  fih_int fih_rc = FIH_FAILURE;
  (void) fih_rc;
  if ((in_vec[0].len != sizeof(uint32_t))
      || (in_vec[1].len != sizeof(uint32_t))) {
    bl_fatal_assert_action();
  }

  sli_tz_iovec_params_t iovec_copy = { 0 };
  FIH_CALL(bl_assert_tz_iovecs_in_ns, fih_rc, in_vec, in_len, out_vec, out_len, &iovec_copy);

  uint32_t slotId  = *((uint32_t *) iovec_copy.in_vec[0].base);
  uint32_t offset  = *((uint32_t *) iovec_copy.in_vec[1].base);
  uint8_t  *buffer = (uint8_t *) iovec_copy.out_vec[0].base;
  size_t length    = iovec_copy.out_vec[0].len;

  int32_t ret = -1;
  BL_MPU_WRAPPER_RET(bootloader_readStorage, ret, slotId, offset, buffer, length);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_writeStorage(sli_tz_invec *in_vec, size_t in_len,
                                    sli_tz_outvec *out_vec, size_t out_len)
{
  fih_int fih_rc = FIH_FAILURE;
  (void) fih_rc;
  if ((in_vec[0].len != sizeof(uint32_t))
      || (in_vec[1].len != sizeof(uint32_t))) {
    bl_fatal_assert_action();
  }

  sli_tz_iovec_params_t iovec_copy = { 0 };
  FIH_CALL(bl_assert_tz_iovecs_in_ns, fih_rc, in_vec, in_len, out_vec, out_len, &iovec_copy);

  uint32_t slotId  = *((uint32_t *) iovec_copy.in_vec[0].base);
  uint32_t offset  = *((uint32_t *) iovec_copy.in_vec[1].base);
  uint8_t  *buffer = (uint8_t *) iovec_copy.in_vec[2].base;
  size_t length    = iovec_copy.in_vec[2].len;

  int32_t ret = -1;
  BL_MPU_WRAPPER_RET(bootloader_writeStorage, ret, slotId, offset, buffer, length);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_eraseWriteStorage(sli_tz_invec *in_vec, size_t in_len,
                                         sli_tz_outvec *out_vec, size_t out_len)
{
  fih_int fih_rc = FIH_FAILURE;
  (void) fih_rc;
  if ((in_vec[0].len != sizeof(uint32_t))
      || (in_vec[1].len != sizeof(uint32_t))) {
    bl_fatal_assert_action();
  }

  sli_tz_iovec_params_t iovec_copy = { 0 };
  FIH_CALL(bl_assert_tz_iovecs_in_ns, fih_rc, in_vec, in_len, out_vec, out_len, &iovec_copy);

  uint32_t slotId  = *((uint32_t *) iovec_copy.in_vec[0].base);
  uint32_t offset  = *((uint32_t *) iovec_copy.in_vec[1].base);
  uint8_t  *buffer = (uint8_t *) iovec_copy.in_vec[2].base;
  size_t length    = iovec_copy.in_vec[2].len;

  int32_t ret = -1;
  BL_MPU_WRAPPER_RET(bootloader_eraseWriteStorage, ret, slotId, offset, buffer, length);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_eraseStorageSlot(uint32_t slotId, uint32_t notUsed)
{
  (void) notUsed;
  int32_t ret = -1;
  BL_MPU_WRAPPER_RET(bootloader_eraseStorageSlot, ret, slotId);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_initChunkedEraseStorageSlot(sli_tz_invec *in_vec, size_t in_len,
                                                   sli_tz_outvec *out_vec, size_t out_len)
{
  fih_int fih_rc = FIH_FAILURE;
  (void) fih_rc;
  if ((in_vec[0].len != sizeof(uint32_t))
      || (out_vec[0].len != sizeof(BootloaderEraseStatus_t))) {
    bl_fatal_assert_action();
  }

  sli_tz_iovec_params_t iovec_copy = { 0 };
  FIH_CALL(bl_assert_tz_iovecs_in_ns, fih_rc, in_vec, in_len, out_vec, out_len, &iovec_copy);

  uint32_t slotId                    = *((uint32_t *) iovec_copy.in_vec[0].base);
  BootloaderEraseStatus_t *eraseStat = (BootloaderEraseStatus_t *) iovec_copy.out_vec[0].base;

  int32_t ret = -1;
  BL_MPU_WRAPPER_RET(bootloader_initChunkedEraseStorageSlot, ret, slotId, eraseStat);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_chunkedEraseStorageSlot(sli_tz_invec *in_vec, size_t in_len,
                                               sli_tz_outvec *out_vec, size_t out_len)
{
  fih_int fih_rc = FIH_FAILURE;
  (void) fih_rc;
  if (out_vec[0].len != sizeof(BootloaderEraseStatus_t)) {
    bl_fatal_assert_action();
  }

  sli_tz_iovec_params_t iovec_copy = { 0 };
  FIH_CALL(bl_assert_tz_iovecs_in_ns, fih_rc, in_vec, in_len, out_vec, out_len, &iovec_copy);

  uint32_t currentPageAddrChecked    = (uint32_t) iovec_copy.in_vec[0].base;
  size_t pageSizeChecked             = iovec_copy.in_vec[0].len;
  BootloaderEraseStatus_t *eraseStat = (BootloaderEraseStatus_t *) iovec_copy.out_vec[0].base;

  // Make sure that the values of eraseStat->currentPageAddr and eraseStat->pageSize
  // are verified and do not result in any erase operation that touches Secure flash
  if ((eraseStat->pageSize == 0U)
      || (pageSizeChecked != eraseStat->pageSize)
      || (currentPageAddrChecked != eraseStat->currentPageAddr)) {
    bl_fatal_assert_action();
  }

  int32_t ret = -1;
  BL_MPU_WRAPPER_RET(bootloader_chunkedEraseStorageSlot, ret, eraseStat);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_setImageToBootload(int32_t slotId, uint32_t notUsed)
{
  (void) notUsed;
  int32_t ret = -1;
  BL_MPU_WRAPPER_RET(bootloader_setImageToBootload, ret, slotId);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_setImagesToBootload(sli_tz_invec *in_vec, size_t in_len,
                                           sli_tz_outvec *out_vec, size_t out_len)
{
  fih_int fih_rc = FIH_FAILURE;
  (void) fih_rc;
  sli_tz_iovec_params_t iovec_copy = { 0 };
  FIH_CALL(bl_assert_tz_iovecs_in_ns, fih_rc, in_vec, in_len, out_vec, out_len, &iovec_copy);

  int32_t *slotIds = (int32_t *) iovec_copy.in_vec[0].base;
  size_t length    = iovec_copy.in_vec[0].len / sizeof(slotIds[0]);

  int32_t ret = -1;
  BL_MPU_WRAPPER_RET(bootloader_setImagesToBootload, ret, slotIds, length);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_getImagesToBootload(sli_tz_invec *in_vec, size_t in_len,
                                           sli_tz_outvec *out_vec, size_t out_len)
{
  fih_int fih_rc = FIH_FAILURE;
  (void) fih_rc;
  sli_tz_iovec_params_t iovec_copy = { 0 };
  FIH_CALL(bl_assert_tz_iovecs_in_ns, fih_rc, in_vec, in_len, out_vec, out_len, &iovec_copy);

  int32_t *slotIds = (int32_t *) iovec_copy.out_vec[0].base;
  size_t length    = iovec_copy.out_vec[0].len / sizeof(slotIds[0]);

  int32_t ret = -1;
  BL_MPU_WRAPPER_RET(bootloader_getImagesToBootload, ret, slotIds, length);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_appendImageToBootloadList(int32_t slotId, uint32_t notUsed)
{
  (void) notUsed;
  int32_t ret = -1;
  BL_MPU_WRAPPER_RET(bootloader_appendImageToBootloadList, ret, slotId);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_initVerifyImage(uint32_t slotId, uint32_t notUsed)
{
  (void) notUsed;
  int32_t ret = -1;
  BL_MPU_WRAPPER_RET(bootloader_initVerifyImage,
                     ret,
                     slotId,
                     context_buffer,
                     BOOTLOADER_STORAGE_VERIFICATION_CONTEXT_SIZE);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_continueVerifyImage(void)
{
  int32_t ret = -1;
  BL_MPU_WRAPPER_RET(bootloader_continueVerifyImage,
                     ret,
                     context_buffer,
                     NULL);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_verifyImage(uint32_t slotId, uint32_t notUsed)
{
  (void) notUsed;
  int32_t ret = -1;
  BL_MPU_WRAPPER_RET(bootloader_verifyImage,
                     ret,
                     slotId,
                     NULL);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_getImageInfo(sli_tz_invec *in_vec, size_t in_len,
                                    sli_tz_outvec *out_vec, size_t out_len)
{
  fih_int fih_rc = FIH_FAILURE;
  (void) fih_rc;
  if ((in_vec[0].len != sizeof(uint32_t))
      || (out_vec[0].len != sizeof(ApplicationData_t))
      || (out_vec[1].len != sizeof(uint32_t))) {
    bl_fatal_assert_action();
  }

  sli_tz_iovec_params_t iovec_copy = { 0 };
  FIH_CALL(bl_assert_tz_iovecs_in_ns, fih_rc, in_vec, in_len, out_vec, out_len, &iovec_copy);

  uint32_t slotId             = *((uint32_t *) iovec_copy.in_vec[0].base);
  ApplicationData_t *appInfo  = (ApplicationData_t *) iovec_copy.out_vec[0].base;
  uint32_t *bootloaderVersion = (uint32_t *) iovec_copy.out_vec[1].base;

  int32_t ret = -1;
  BL_MPU_WRAPPER_RET(bootloader_getImageInfo,
                     ret,
                     slotId,
                     appInfo,
                     bootloaderVersion);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_storageIsBusy(void)
{
  bool ret = false;
  BL_MPU_WRAPPER_RET(bootloader_storageIsBusy,
                     ret);
  return ret;
}

__attribute__((cmse_nonsecure_entry))
int32_t bootloader_nsc_getAllocatedDMAChannel(void)
{
  int32_t ret = -1;
  BL_MPU_WRAPPER_RET(bootloader_getAllocatedDMAChannel,
                     ret);
  return ret;
}
