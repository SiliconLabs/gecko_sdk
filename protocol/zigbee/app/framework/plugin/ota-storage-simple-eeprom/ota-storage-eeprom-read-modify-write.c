/***************************************************************************//**
 * @file
 * @brief This code is intended for EEPROM devices that support read-modify-write
 * of arbitrary page sizes, and across page boundaries.
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
#include "app/framework/plugin/ota-common/ota.h"
#include "app/framework/plugin/ota-storage-common/ota-storage.h"

#include "eeprom.h"

#define OTA_STORAGE_EEPROM_INTERNAL_HEADER
#include "ota-storage-eeprom.h"
#undef OTA_STORAGE_EEPROM_INTERNAL_HEADER

#ifdef READ_MODIFY_WRITE_SUPPORT

//------------------------------------------------------------------------------
// Globals

//------------------------------------------------------------------------------

uint32_t emberAfOtaStorageDriverRetrieveLastStoredOffsetCallback(void)
{
  uint32_t offset;

  if (!sli_zigbee_af_ota_storage_check_download_meta_data()) {
    return 0;
  }

  offset = sli_zigbee_af_ota_storage_read_int32u_from_eeprom(
    otaStorageEepromGetImageInfoStartAddress()
    + SAVED_DOWNLOAD_OFFSET_INDEX);
  if (offset == 0xFFFFFFFFL) {
    return 0;
  }
  return offset;
}

void sli_zigbee_af_storage_eeprom_update_download_offset(uint32_t offset, bool finalOffset)
{
  uint32_t oldDownloadOffset =
    emberAfOtaStorageDriverRetrieveLastStoredOffsetCallback();

  if (finalOffset
      || offset == 0
      || (offset > SAVE_RATE
          && (oldDownloadOffset + SAVE_RATE) <= offset)) {
    // The actual offset we are writing TO is the second parameter.
    // The data we are writing (first param) also happens to be an offset but
    // is not a location for the write operation in this context.
    debugFlush();
    debugPrint("Recording download offset: 0x%4X", offset);
    debugFlush();

    sli_zigbee_af_ota_storage_write_int32u_to_eeprom(offset,
                                                     otaStorageEepromGetImageInfoStartAddress()
                                                     + SAVED_DOWNLOAD_OFFSET_INDEX);
    //printImageInfoStartData();
  }
}

EmberAfOtaStorageStatus emberAfOtaStorageDriverInvalidateImageCallback(void)
{
  uint8_t zeroMagicNumber[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

  if (!sli_zigbee_af_ota_storage_check_download_meta_data()) {
    sli_zigbee_af_ota_storage_write_download_meta_data();
  }

  // Wipe out the magic number in the OTA file and the Header length field.
  // EEPROM driver requires a write of at least 8 bytes in length.
  if (!emberAfOtaStorageDriverWriteCallback(zeroMagicNumber,
                                            0,      // offset
                                            sizeof(zeroMagicNumber))) {   // length
    return EMBER_AF_OTA_STORAGE_ERROR;
  }

  // Set the offset to 0 to indicate on reboot that there is no previous image
  // to resume downloading.
  emberAfOtaStorageDriverDownloadFinishCallback(0);

  return EMBER_AF_OTA_STORAGE_SUCCESS;
}

void emberAfPluginOtaStorageSimpleEepromPageEraseEventHandler(sl_zigbee_event_t * event)
{
  // This event should never fire.
}

void sli_zigbee_af_ota_storage_eeprom_init(void)
{
  // Older drivers do not have an EEPROM info structure that we can reference
  // so we must just assume they are okay.
  if (emberAfPluginEepromInfo() != NULL) {
    // OTA code must match the capabilities of the part.  This code
    // assumes that a page erase prior to writing data is NOT required.
    assert((emberAfPluginEepromInfo()->capabilitiesMask
            & EEPROM_CAPABILITIES_PAGE_ERASE_REQD)
           == 0);
  }
}

EmberAfOtaStorageStatus emberAfOtaStorageDriverPrepareToResumeDownloadCallback(void)
{
  return EMBER_AF_OTA_STORAGE_SUCCESS;
}

#endif // READ_MODIFY_WRITE_SUPPORT
