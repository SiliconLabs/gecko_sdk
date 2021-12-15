/***************************************************************************//**
 * @file
 * @brief Media interface for Mass Storage class Device (MSD).
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "application_properties.h"

#include "em_usb.h"

#include "msdd.h"
#include "msddmedia.h"

#include "em_msc.h"
#include "em_core.h"
#include "gbl_fat12_disk.h"

#include "btl_interface.h"

// -----------------------------------------------------------------------------
// Defines
#define FLASH_PAGESIZE    8192             // To ensure large enough size for all kits
#define BLOCK_SIZE        512              // Size of a sector

// -----------------------------------------------------------------------------
// Local variables
static uint32_t numSectors;
static uint8_t *diskStorage;
static uint8_t flashPageBuf[((FLASH_PAGESIZE) +3) & ~3];

// -----------------------------------------------------------------------------
// Global variables
uint32_t flashPageSize;
flashStat flashStatus;

// -----------------------------------------------------------------------------
// Local function definitions

/***************************************************************************//**
 * @brief
 *   Erase and rewrite a flash page.
 ******************************************************************************/
static int32_t FlushFlash(void)
{
  int32_t ret;

  // Erase flash page
  ret = bootloader_eraseRawStorage((uint32_t)flashStatus.pPageBase, flashPageSize);

  if (ret & BOOTLOADER_ERROR_STORAGE_BASE) {
    return ret;
  }

  // Program flash page
  ret = bootloader_writeRawStorage((uint32_t)flashStatus.pPageBase, flashPageBuf, flashPageSize);
  return ret;
}

// -----------------------------------------------------------------------------
// Global function definitions

/***************************************************************************//**
 * @brief
 *   Get pointer to the flash buffer storage
 *
 * @return
 *   Pointer to the flash buffer storage
 ******************************************************************************/
uint8_t* MSDDMEDIA_getFlashBuffer(void)
{
  return flashPageBuf;
}

/***************************************************************************//**
 * @brief
 *   Get pointer to the disk storage
 *
 * @return
 *   Pointer to the disk storage
 ******************************************************************************/
uint8_t* MSDDMEDIA_getDiskStorage(void)
{
  return diskStorage;
}

/***************************************************************************//**
 * @brief
 *   Check if a media access is legal, prepare for later data transmissions.
 *
 * @param[in] pCmd
 *   Points to a MSDD_CmdStatus_TypeDef structure which holds info about the
 *   current transfer.
 *
 * @param[in] lba
 *   Media "Logical Block Address".
 *
 * @param[in] sectors
 *   Number of 512 byte sectors to transfer.
 *
 * @return
 *   True if legal access, false otherwise.
 ******************************************************************************/
bool MSDDMEDIA_CheckAccess(MSDD_CmdStatus_TypeDef *pCmd,
                           uint32_t lba, uint32_t sectors)
{
  if ((lba + sectors) > numSectors) {
    return false;
  }

  pCmd->lba   = lba;
  pCmd->pData = &diskStorage[lba * BLOCK_SIZE];
  if (pCmd->direction && !flashStatus.pendingWrite) {
    pCmd->xferType = XFER_MEMORYMAPPED;
  } else {
    pCmd->xferType = XFER_INDIRECT;
    pCmd->maxBurst = MEDIA_BUFSIZ;
  }

  pCmd->xferLen = sectors * BLOCK_SIZE;

  return true;
}

/***************************************************************************//**
 * @brief
 *   Flush pending media writes.
 ******************************************************************************/
void MSDDMEDIA_Flush(void)
{
  if (flashStatus.pendingWrite) {
    flashStatus.pendingWrite = false;
    FlushFlash();
  }
}

/***************************************************************************//**
 * @brief
 *   Get number of 512 byte sectors on the media.
 *
 * @return
 *   Number of sectors on media.
 ******************************************************************************/
uint32_t MSDDMEDIA_GetSectorCount(void)
{
  return numSectors;
}

/***************************************************************************//**
 * @brief
 *   Initialize the storage media interface and prepare FAT12 image
 ******************************************************************************/
bool MSDDMEDIA_Init(void)
{
  BootloaderStorageInformation_t infoStorage;
  BootloaderStorageSlot_t storageSlot;
  bootloader_getStorageInfo(&infoStorage);
  if (bootloader_getStorageSlotInfo(SLOT_ID, &storageSlot) & BOOTLOADER_ERROR_STORAGE_BASE) {
    EFM_ASSERT(false);
  }

  flashPageSize = infoStorage.info->pageSize;
  diskStorage = (uint8_t*)storageSlot.address;
  numSectors = storageSlot.length / BLOCK_SIZE;
  flashStatus.pendingWrite = false;
  gblfat12disk_setMostRecentLBA(0);

  MSC_Init();
  gblfat12disk_prepareFAT12Img(diskStorage, numSectors, flashPageBuf);
  return true;
}

/***************************************************************************//**
 * @brief
 *   Read from indirectly accessed media.
 *
 * @param[in] pCmd
 *   Points to a MSDD_CmdStatus_TypeDef structure which holds info about the
 *   current transfer.
 *
 * @param[in] data
 *   Pointer to data buffer.
 *
 * @param[in] sectors
 *   Number of 512 byte sectors to read from media.
 ******************************************************************************/
void MSDDMEDIA_Read(MSDD_CmdStatus_TypeDef *pCmd, uint8_t *data, uint32_t sectors)
{
  // Write pending data to flash before starting the read operation.
  MSDDMEDIA_Flush();
  bootloader_readRawStorage((uint32_t)pCmd->pData, data, sectors * BLOCK_SIZE);
  pCmd->pData += sectors * BLOCK_SIZE;
}

/***************************************************************************//**
 * @brief
 *   Write to indirectly accessed media.
 *
 * @param[in] pCmd
 *   Points to a MSDD_CmdStatus_TypeDef structure which holds info about the
 *   current transfer.
 *
 * @param[in] data
 *   Pointer to data buffer.
 *
 * @param[in] sectors
 *   Number of 512 byte sectors to write to media.
 ******************************************************************************/
void MSDDMEDIA_Write(MSDD_CmdStatus_TypeDef *pCmd, uint8_t *data, uint32_t sectors)
{
  unsigned int i;
  uint32_t offset;

  i = 0;
  while (i < sectors) {
    gblfat12disk_setMostRecentLBA(pCmd->lba + i);

    // Marking the reception of the data blocks for later checking
    gblfat12disk_setLBABit(pCmd->lba + i);

    if (!flashStatus.pendingWrite) {
      // Copy an entire flash page to the page buffer
      flashStatus.pendingWrite = true;
      flashStatus.pPageBase    = (uint8_t*)((uint32_t)pCmd->pData & ~(flashPageSize - 1));
      offset                    = pCmd->pData - flashStatus.pPageBase;
      bootloader_readRawStorage((uint32_t)flashStatus.pPageBase, flashPageBuf, flashPageSize);

      // Write the received data in the page buffer
      memcpy(flashPageBuf + offset, data, BLOCK_SIZE);
      data        += BLOCK_SIZE;
      pCmd->pData += BLOCK_SIZE;
    } else {
      // Check if current sector is located in the page buffer.
      offset = pCmd->pData - flashStatus.pPageBase;
      if (offset >= flashPageSize) {
        /*
         * Current sector not located in page buffer, flush pending data
         * before continuing.
         */
        MSDDMEDIA_Flush();
        i--;
      } else {
        // Write the received data in the page buffer
        memcpy(flashPageBuf + offset, data, BLOCK_SIZE);
        data        += BLOCK_SIZE;
        pCmd->pData += BLOCK_SIZE;
      }
    }
    i++;
  }
}
