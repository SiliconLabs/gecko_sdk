/***************************************************************************//**
 * @file
 * @brief Set of APIs for the sl_connect_ota_bootloader_interface component.
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

#include PLATFORM_HEADER
#include "stack/include/ember.h"
#include "sl_connect_sdk_btl-interface.h"
#include "btl_interface.h"
#include "app_log.h"
#include "stack/core/sl-connect-watchdog.h"

static bool isBootloaderInitialized = false;
static uint32_t storageSlotStartAddress = 0UL;

#define STORAGE_SLOT_0 (0)

//------------------------------------------------------------------------------
// APIs

bool emberAfPluginBootloaderInterfaceIsBootloaderInitialized(void)
{
  return isBootloaderInitialized;
}

void emberAfPluginBootloaderInterfaceGetVersion(uint16_t *blVersion)
{
  BootloaderInformation_t info = { .type = SL_BOOTLOADER, .version = 0L, .capabilities = 0L };
  bootloader_getInfo(&info);
  *blVersion = info.version;
}

// HACK: Currently, bootloaderIsCommonBootloader() is not exposed.
// According to Jerome, info->type == SL_BOOTLOADER will guarantee a Gecko bootloader.
static bool isGeckoBootloader(void)
{
  BootloaderInformation_t bootloaderInfo;
  MEMSET(&bootloaderInfo, 0, sizeof(BootloaderInformation_t));
  bootloader_getInfo(&bootloaderInfo);

  return bootloaderInfo.type == SL_BOOTLOADER;
}

bool emberAfPluginBootloaderInterfaceInit(void)
{
  BootloaderStorageInformation_t storageInfo;
  BootloaderStorageSlot_t storageSlotInfo;
  int32_t retval = 1L;

  retval = bootloader_init();

  if (retval != BOOTLOADER_OK) {
    app_log_error("bootloader_init failed!\n");
    return false;
  }

  bootloader_getStorageInfo(&storageInfo);

  // Single image space
  if (storageInfo.numStorageSlots > 0) {
    if ( bootloader_getStorageSlotInfo(STORAGE_SLOT_0, &storageSlotInfo)
         == BOOTLOADER_OK ) {
      storageSlotStartAddress = storageSlotInfo.address;
    }
  }

  isBootloaderInitialized = true;
  return true;
}

void emberAfPluginBootloaderInterfaceSleep(void)
{
  // USART need to be init'ed to send proper shutdown
  // command to EEPROM.
  if (!isBootloaderInitialized) {
    emberAfPluginBootloaderInterfaceInit();
  }
  bootloader_deinit();
  isBootloaderInitialized = false;
}

static bool legacyBootloaderChipErase(void)
{
  bool result = true;

  WDOGn_Feed(DEFAULT_WDOG);

  if (BOOTLOADER_OK != bootloader_eraseStorageSlot(0)) {
    result = false;
    goto DONE;
  }

  app_log_info("\n");

  DONE:
  if (result) {
    app_log_info("flash erase successful!\n");
  } else {
    app_log_error("flash erase failed!\n");
  }

  return result;
}

static bool geckoBootloaderChipEraseSlot(uint32_t slot)
{
  BootloaderStorageInformation_t storageInfo;
  BootloaderStorageSlot_t storageSlotInfo;
  int32_t retVal = BOOTLOADER_OK;
  uint32_t address;
  uint32_t bytesToErase;

  bootloader_getStorageInfo(&storageInfo);
  if (slot >= storageInfo.numStorageSlots) {
    app_log_error("ERROR: invalid erase slot number(%ld)!\n", slot);
    return false;
  }

  // Get information on Slot
  retVal = bootloader_getStorageSlotInfo(slot, &storageSlotInfo);
  if (BOOTLOADER_OK != retVal) {
    return false;
  }

  bytesToErase = (storageSlotInfo.length / storageInfo.info->pageSize)
                 * storageInfo.info->pageSize;

  // Check for a misaligned slot
  // This shouldn't happen unless the user configures something improperly, and
  // even then, the bootloader may complain when being compiled/run
  if (storageSlotInfo.length % storageInfo.info->pageSize) {
    app_log_warning("Erase: slot length (%ld) not aligned "
                    "to page size (%ld). The entire slot will not be erased.\n",
                    storageSlotInfo.length,
                    storageInfo.info->pageSize);
  }
  address = storageSlotInfo.address;

  // Erase the slot in page chunks
  while ((BOOTLOADER_OK == retVal)
         && ((address - storageSlotInfo.address) < bytesToErase)) {
    WDOGn_Feed(DEFAULT_WDOG);
    app_log_info(".");
    retVal = bootloader_eraseRawStorage(address, storageInfo.info->pageSize);
    address += storageInfo.info->pageSize;
  }

  app_log_info("\n");

  if (BOOTLOADER_OK != retVal) {
    app_log_error("Erase: failed to erase %ld bytes in slot at "
                  "address 0x%4lx (error 0x%lx)\n",
                  storageInfo.info->pageSize,
                  address - storageInfo.info->pageSize,
                  retVal);
  }
  return (BOOTLOADER_OK == retVal);
}

// Erase all Gecko bootloader storage slots
static bool geckoBootloaderChipEraseSlotAll(void)
{
  bool retVal = true;
  bool result = true;
  BootloaderStorageInformation_t storageInfo;
  MEMSET(&storageInfo, 0, sizeof(BootloaderStorageInformation_t));
  bootloader_getStorageInfo(&storageInfo);
  for (uint32_t index = 0; index < storageInfo.numStorageSlots; index++) {
    app_log_info("flash erasing slot %ld started\n", index);
    result = geckoBootloaderChipEraseSlot(index);

    if (result) {
      app_log_info("flash erase successful!\n");
    } else {
      app_log_error("flash erase failed!\n");
    }

    retVal &= result;
  }

  return retVal;
}

bool emberAfPluginBootloaderInterfaceChipErase(void)
{
  bool result = true;
  if (isGeckoBootloader()) {
    result = geckoBootloaderChipEraseSlotAll();
  } else {
    result = legacyBootloaderChipErase();
  }

  return result;
}

bool emberAfPluginBootloaderInterfaceChipEraseSlot(uint32_t slot)
{
  return geckoBootloaderChipEraseSlot(slot);
}

uint16_t emberAfPluginBootloaderInterfaceValidateImage(void)
{
  uint16_t result;

  app_log_info("Verifying image");

  WDOGn_Feed(DEFAULT_WDOG);

  result = bootloader_verifyImage(0, NULL);

  if (result != BOOTLOADER_OK) {
    app_log_error("failed!\n");
  } else {
    app_log_info("done!\n");
  }

  return result;
}

void emberAfPluginBootloaderInterfaceBootload(void)
{
  int32_t result;

  if (emberAfPluginBootloaderInterfaceValidateImage() != BOOTLOADER_OK) {
    app_log_error("Invalid image!\n");
    return;
  }

  app_log_info("Installing new image and rebooting...\n");
  sl_sleeptimer_delay_millisecond(500);

  result = bootloader_setImageToBootload(0);

  if (result != BOOTLOADER_OK) {
    app_log_error("Failed to set bootload image (error 0x%lx)!\n", result);
    return;
  }
  app_log_info("Bootload image set!\n");

  bootloader_rebootAndInstall();
}

bool emberAfPluginBootloaderInterfaceRead(uint32_t startAddress,
                                          uint32_t length,
                                          uint8_t *buffer)
{
  uint32_t address;
  uint32_t remainingLength;
  uint8_t result;
  uint8_t len;

  address = startAddress;
  remainingLength = length;

  if (isBootloaderInitialized) {
    // Implement block read so we can take care of the watchdog reset.
    while (remainingLength) {
      WDOGn_Feed(DEFAULT_WDOG);
      len = (remainingLength > 255) ? 255 : (uint8_t)remainingLength;
      result = bootloader_readRawStorage((storageSlotStartAddress + address), buffer + address - startAddress, len);

      if (BOOTLOADER_OK != result) {
        return false;
      }

      remainingLength -= len;
      address += len;
    }
    return true;
  }

  return false;
}

bool emberAfPluginBootloaderInterfaceWrite(uint32_t startAddress,
                                           uint32_t length,
                                           const uint8_t *buffer)
{
  uint32_t address;
  uint32_t remainingLength;
  uint8_t result;
  uint8_t len;

  address = startAddress;
  remainingLength = length;

  if (isBootloaderInitialized) {
    // Implement block write so we can take care of the watchdog reset.
    while (remainingLength) {
      WDOGn_Feed(DEFAULT_WDOG);
      len = (remainingLength > 255) ? 255 : (uint8_t)remainingLength;
      result = bootloader_writeRawStorage((storageSlotStartAddress + address), ((uint8_t *)buffer) + address - startAddress, len);

      if (BOOTLOADER_OK != result) {
        return false;
      }

      remainingLength -= len;
      address += len;
    }

    return true;
  }

  return false;
}
