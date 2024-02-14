/***************************************************************************//**
 * @file
 * @brief Routines for bootloading an SOC.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "app/framework/include/af.h"
#include "app/framework/plugin/ota-storage-common/ota-storage.h"

#ifndef EMBER_TEST
#include "api/btl_interface.h"
#include "api/btl_interface_storage.h"
#endif // !EMBER_TEST
//------------------------------------------------------------------------------
// Globals

//------------------------------------------------------------------------------
EmberStatus bootloaderInstallNewImage(void)
{
#ifndef EMBER_TEST
  int32_t storageSlot = DEFAULT_SLOT;
  if (bootloader_setImagesToBootload(&storageSlot, 1) == BOOTLOADER_OK) {
    // should not return
    bootloader_rebootAndInstall();
  }
#endif // SL_CATALOG_SLOT_MANAGER_PRESENT
  return EMBER_ERR_FATAL;
}

uint8_t emberAfOtaBootloadCallback(const EmberAfOtaImageId* id,
                                   uint16_t ncpUpgradeTagId)
{
  bootloaderInstallNewImage();

  emberAfCorePrintln("Bootloading failed!");

  // If we got here, it is a failure.
  return 1;
}
