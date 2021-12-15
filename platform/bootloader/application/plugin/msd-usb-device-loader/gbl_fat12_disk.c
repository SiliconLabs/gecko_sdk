/***************************************************************************//**
 * @file
 * @brief Gecko Bootloader FAT12 disk API
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
#include "em_usb.h"
#include "gbl_fat12_disk.h"
#include "msddmedia.h"
#include "btl_interface.h"
#include "application_properties.h"

// -----------------------------------------------------------------------------
// Defines
//#define MAX_FILESIZE               FLASH_SIZE

// FAT 12 header: Boot block + FAT Table + Root directory
// NB: needs to be bigger than a page size of flash
#define DISK_HEADER_SPACE          7168

#define DIR_ENTRY_FILESIZE_OFFS    0x1C
#define DIR_ENTRY_STARTCLUST_OFFS  0x1A

#define BOOT_BLOCK_FATNR           1
#define BOOT_BLOCK_FATSIZE         6
#define DIR_ENTRY_SIZE             32
#define BOOT_BLOCK_BLOCKSIZE       512
#define BOOT_BLOCK_ROOTNR          112

#define FATINDEX_2_LBA(x) (14 + (x))  // Assuming 1 sector per cluster

#define FILE_EXT_UPP "GBL"
#define FILE_EXT_LOW "gbl"

extern const ApplicationProperties_t sl_app_properties;

// -----------------------------------------------------------------------------
// Local variables
static uint8_t fatTable[6 * 512]; // FAT 12 table size

static uint16_t mostRecentLBA; // Most recent LBA received

// INDEX: [7 ... 0][15 ... 8][23 ... 16]...
static uint8_t lbaReceived[MAX_FILESIZE / (BOOT_BLOCK_BLOCKSIZE * 8)];

static const uint8_t minimalMBR[] __attribute__ ((aligned(4))) =
{
  0xeb, 0x3c, 0x90, 0x6d, 0x6b, 0x64, 0x6f, 0x73,
  0x66, 0x73, 0x00, 0x00, 0x02, 0x01, 0x01, 0x00,
  0x01, 0x70, 0x00, 0x00, 0x08, 0xf8, 0x06, 0x00,
  0x20, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0xe8,
  0x96, 0x3d, 0x18, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x46, 0x41,
  0x54, 0x31, 0x32, 0x20, 0x20, 0x20, 0xff, 0xff
};

// -----------------------------------------------------------------------------
// Local Function Prototypes
static uint8_t getLBABit(uint16_t index);
static uint32_t getEntryPtr(void);
static uint32_t getFirstEntryRootDir(void);
static uint16_t getFirstClusterNr(uint8_t *entry);
static uint32_t getFileSize(uint8_t *entry);
static void saveFATtable(void);
static uint16_t nextCluster(uint16_t cluster);
static bool fileTransferComplete(void);
static int32_t eraseStorageSlot(uint32_t slotID);
static void reProgramBLApp(void);

// -----------------------------------------------------------------------------
// Local function definitions

/**************************************************************************//**
 * @brief
 *   Get bit from a byte array at the given index
 *
 * @param[in] bitMap
 *   Byte array
 *.
 * @param[in] index
 *   Index of the bit to be read
 *
 * @return
 *   1 if the bit is set, otherwise 0
 *****************************************************************************/
static uint8_t getLBABit(uint16_t index)
{
  if (lbaReceived[index / 8] & (0x1 << (index % 8))) {
    return 1;
  }
  return 0;
}

/**************************************************************************//**
 * @brief
 *   Find the address to the first entry with the given file extension
 *.
 * @return
 *   Address to the entry
 *****************************************************************************/
static uint32_t getEntryPtr(void)
{
  uint8_t  entries[DIR_ENTRY_SIZE];
  uint8_t  *entryPtr;
  uint16_t nrEntries;

  entryPtr = (uint8_t*)getFirstEntryRootDir();

  // Check if a root directory flush is pending.
  // Root directory is found between lba 7 and lba 13.
  if (flashStatus.pendingWrite && (mostRecentLBA >= 7 && mostRecentLBA <= 13)) {
    MSDDMEDIA_Flush();
  }

  for (nrEntries = 0; nrEntries < BOOT_BLOCK_ROOTNR; nrEntries++) {
    bootloader_readRawStorage((uint32_t)entryPtr, entries, DIR_ENTRY_SIZE);

    if (entries[0] != 0xE5 && entries[0] != 0x2E
        && (strncmp((char *)&entries[8], FILE_EXT_UPP, 3) == 0)) {
      break;
    }

    // No file found.
    if (nrEntries == BOOT_BLOCK_ROOTNR - 1) {
      return 0;
    }

    entryPtr += DIR_ENTRY_SIZE;
  }

  return (uint32_t)entryPtr;
}

/**************************************************************************//**
 * @brief
 *   Find the address to the first entry in the root directory
 *
 * @return
 *   Address to the first entry
 *****************************************************************************/
static uint32_t getFirstEntryRootDir(void)
{
  uint8_t *entryPtr;

  entryPtr = MSDDMEDIA_getDiskStorage() \
             + BOOT_BLOCK_BLOCKSIZE * (BOOT_BLOCK_FATSIZE * BOOT_BLOCK_FATNR + 1);
  return (uint32_t)entryPtr;
}

/**************************************************************************//**
 * @brief
 *   Get first cluster number for the given entry in the root directory
 *
 * @return
 *   Total number of clusters
 *****************************************************************************/
static uint16_t getFirstClusterNr(uint8_t *entry)
{
  uint16_t cluster;
  bootloader_readRawStorage((uint32_t)&entry[DIR_ENTRY_STARTCLUST_OFFS], (uint8_t *)&cluster, 2);

  return cluster;
}

/**************************************************************************//**
 * @brief
 *   Get file size for the given entry in the root directory
 *
 * @return
 *   File size
 *****************************************************************************/
static uint32_t getFileSize(uint8_t *entry)
{
  uint32_t fileSize;
  bootloader_readRawStorage((uint32_t)&entry[DIR_ENTRY_FILESIZE_OFFS], (uint8_t *)&fileSize, 4);

  return fileSize;
}

/**************************************************************************//**
 * @brief
 *   Copy the FAT12 table from the disk located in flash to a buffer in RAM
 *****************************************************************************/
static void saveFATtable(void)
{
  uint8_t *fatAddr;

  fatAddr = MSDDMEDIA_getDiskStorage() + BOOT_BLOCK_BLOCKSIZE;

  // Check if FAT flush is pending.
  // Root directory is found between lba 1 and lba 6
  if (flashStatus.pendingWrite && (mostRecentLBA >= 1 && mostRecentLBA <= 6)) {
    MSDDMEDIA_Flush();
  }

  bootloader_readRawStorage((uint32_t)fatAddr, fatTable, BOOT_BLOCK_FATSIZE * BOOT_BLOCK_BLOCKSIZE);
}

/**************************************************************************//**
 * @brief
 *   Find next cluster in cluster chain.
 *
 * @param[in] cluster
 *   Current cluster.
 *
 * @return
 *   Next cluster in cluster chain, zero if error
 *****************************************************************************/
static uint16_t nextCluster(uint16_t cluster)
{
  int i, nextCluster;

  i = (3 * cluster) / 2;
  if ( cluster & 1 ) {
    nextCluster  = (fatTable[i] & 0xF0) >> 4;
    nextCluster |= fatTable[1 + i] << 4;
  } else {
    nextCluster  = fatTable[i];
    nextCluster |= (fatTable[1 + i] & 0xF) << 8;
  }

  return (uint16_t)nextCluster;
}

/**************************************************************************//**
 * @brief
 *   Check if a file transfer to the disk has been completed.
 *
 * @return
 *   True if file transfer has been completed, otherwise false.
 *****************************************************************************/
static bool fileTransferComplete(void)
{
  bool     endOfFile;
  uint8_t  *lastEntry;
  uint16_t cluster;
  uint32_t fileSize;
  int      burst;

  endOfFile = false;

  lastEntry = (uint8_t*)getEntryPtr();

  // Check if a valid file with the given file extension has been found.
  if (lastEntry != 0) {
    fileSize = getFileSize(lastEntry);
    cluster = getFirstClusterNr(lastEntry);

    saveFATtable(); // Update the FAT table

    // This while loop is used for traversing the cluster chain
    while (fileSize) {
      // Check if the data area with the given cluster number has been received.
      if (!getLBABit(FATINDEX_2_LBA(cluster - 2))) {
        break;
      }

      burst = (BOOT_BLOCK_BLOCKSIZE <= fileSize) ? BOOT_BLOCK_BLOCKSIZE : fileSize;
      fileSize -= burst;
      cluster = nextCluster(cluster);

      // Check for EOF mark in the cluster chain
      if ((cluster >= 0xFF8 && cluster <= 0xFFF) && fileSize == 0) {
        endOfFile = true;
      }
    }
  }

  return endOfFile;
}

/***************************************************************************//**
 * @brief
 *   Erase the bootloader storage slot
 ******************************************************************************/
static int32_t eraseStorageSlot(uint32_t slotID)
{
  int32_t retVal;
  uint32_t eraseOffset;
  BootloaderStorageInformation_t infoStorage;
  bootloader_getStorageInfo(&infoStorage);
  uint32_t flashPageSize = infoStorage.info->pageSize;

  BootloaderStorageSlot_t storageSlot;
  retVal = bootloader_getStorageSlotInfo(slotID, &storageSlot);
  if (retVal != BOOTLOADER_OK) {
    return retVal;
  }
  uint32_t storageSpaceAddr = storageSlot.address;
  uint8_t storageBuf[1];

  while (storageSpaceAddr < (storageSlot.address + storageSlot.length)) {
    bootloader_readRawStorage(storageSpaceAddr, storageBuf, 1);
    if (storageBuf[0] == 0xFF) {
      storageSpaceAddr += 1;
    } else {
      eraseOffset = (storageSpaceAddr & ~(flashPageSize - 1));
      storageSpaceAddr = eraseOffset + flashPageSize;
      retVal = bootloader_eraseRawStorage(eraseOffset, flashPageSize);
      if (retVal != BOOTLOADER_OK) {
        return retVal;
      }
    }
  }
  return BOOTLOADER_OK;
}

/**************************************************************************//**
 * @brief
 *   Reprogram app. and upgrade bootloader using GBL from the storage memory.
 *****************************************************************************/
static void reProgramBLApp(void)
{
  uint8_t   *rootDirBlock, *rootDirLastBlock, *pSrc, *pDest, *pFlash;
  uint32_t  fileSize, appVersionNewImg, imgInfoVersion;
  int       burst;
  uint16_t  cluster;

  BootloaderInformation_t info;
  ApplicationData_t appinfo;

  // Write pending data to flash before starting the read operation.
  if (flashStatus.pendingWrite) {
    MSDDMEDIA_Flush();
  }

  rootDirBlock = (uint8_t*)getFirstEntryRootDir();
  rootDirLastBlock = rootDirBlock + (DIR_ENTRY_SIZE * BOOT_BLOCK_ROOTNR);

  rootDirBlock = (uint8_t*)getEntryPtr();
  cluster = getFirstClusterNr(rootDirBlock);
  fileSize  = getFileSize(rootDirBlock);
  fileSize = (fileSize + 3) & ~3;  // Making file size divisible of the Word length (4 bytes)

  pDest    = MSDDMEDIA_getFlashBuffer();
  pFlash   = MSDDMEDIA_getDiskStorage();

  saveFATtable();
  while (fileSize) {
    burst = (BOOT_BLOCK_BLOCKSIZE <= fileSize) ? BOOT_BLOCK_BLOCKSIZE : fileSize;

    // The first two cluster's are non-existent, the first cluster on the disk is cluster no. 2
    pSrc = (cluster - 2) * BOOT_BLOCK_BLOCKSIZE + rootDirLastBlock;
    bootloader_readRawStorage((uint32_t)pSrc, pDest, burst);
    pDest += burst;

    if (pDest == MSDDMEDIA_getFlashBuffer() + flashPageSize) {
      bootloader_eraseRawStorage((uint32_t)pFlash, flashPageSize);
      bootloader_writeRawStorage((uint32_t)pFlash, MSDDMEDIA_getFlashBuffer(), flashPageSize);
      pDest   = MSDDMEDIA_getFlashBuffer();
      pFlash += flashPageSize;
    }

    fileSize -= burst;
    cluster = nextCluster(cluster);
  }

  if (pDest != MSDDMEDIA_getFlashBuffer()) {
    bootloader_eraseRawStorage((uint32_t)pFlash, flashPageSize);
    bootloader_writeRawStorage((uint32_t)pFlash, MSDDMEDIA_getFlashBuffer(), pDest - MSDDMEDIA_getFlashBuffer());
  }

  // Verify the Bootloader image
  if (bootloader_verifyImage(SLOT_ID, NULL) == BOOTLOADER_OK) {
    if (bootloader_setImageToBootload(SLOT_ID) == BOOTLOADER_OK) {
      bootloader_getInfo(&info);
      bootloader_getImageInfo(SLOT_ID, &appinfo, &imgInfoVersion);
      appVersionNewImg = appinfo.version;

      if (appVersionNewImg > sl_app_properties.app.version) {
        printf("\nA valid GBL with a newer application version found, rebooting\n");
        bootloader_rebootAndInstall();
      } else {
        printf("\nThe GBL file contains an application upgrade image with same/older version\n");
      }
    }
  } else {
    printf("The upgrade image is invalid\n");
  }

  // Clean the bootloader storage space
  printf("Erasing the bootloader storage space...\n");
  if (eraseStorageSlot(SLOT_ID) == BOOTLOADER_OK) {
    printf("Erasing the bootloader storage space completed\n");
  }

  USBTIMER_DelayMs(1000); // Wait 1s before system reset
  NVIC_SystemReset();
}

// -----------------------------------------------------------------------------
// Global function definitions

/**************************************************************************//**
 * @brief
 *   Set bit in a byte array at the given index
 *.
 * @param[in] index
 *   Index of the bit to be set
 *****************************************************************************/
void gblfat12disk_setLBABit(uint16_t index)
{
  lbaReceived[index / 8] |= 0x1 << (index % 8);
}

/**************************************************************************//**
 * @brief
 *   Set most recent LBA received
 *
 * @param[in] blockNr
 *   Block number
 *****************************************************************************/
void gblfat12disk_setMostRecentLBA(uint16_t blockNr)
{
  mostRecentLBA = blockNr;
}

/**************************************************************************//**
 * @brief
 *   Check if a file has been completely transferred and
 *   if there is no pending activity in the MSD, perform a reprogram
 *
 * @param[in] msddState
 *   State of Mass Storage class Device
 *****************************************************************************/
void gblfat12disk_reProgramCheck(bool msddIdle)
{
  static bool endOfFile = false;

  if (!msddIdle) {
    endOfFile = fileTransferComplete();
  }

  if (endOfFile && msddIdle) {
    printf("File transfer completed\n");
    endOfFile = false;
    USBTIMER_DelayMs(100); // Wait 100 ms before disconnecting USB
    USBD_Stop();
    printf("USB disconnected\n");
    printf("Start reprogramming the bootloader storage space\n");
    reProgramBLApp();
  }
}

/**************************************************************************//**
 * @brief
 *   Preparing FAT 12 image on the disk
 *
 * @param[in] diskStorage
 *   Pointer to the disk storage
 *
 * @param[in] flashPageBuf
 *   Flash page buffer storage
 *****************************************************************************/
void gblfat12disk_prepareFAT12Img(uint8_t *diskStorage,
                                  uint32_t numBlocks,
                                  uint8_t *flashPageBuf)
{
  // Erase the two first flash pages
  uint32_t diskStorageOffset = 0UL;
  while (diskStorageOffset < DISK_HEADER_SPACE) {
    bootloader_eraseRawStorage((uint32_t)diskStorage + diskStorageOffset, flashPageSize);
    diskStorageOffset += flashPageSize;
  }

  // Prepare FAT12 image
  memset(flashPageBuf, 0xFF, flashPageSize);
  // Copy the first part of the boot block.
  memcpy(flashPageBuf, (uint8_t*)minimalMBR, 19);
  // Total number of blocks in the entire disk.
  flashPageBuf[19] = numBlocks & 0x000000FF;
  flashPageBuf[20] = (numBlocks & 0x0000FF00) >> 8;
  // Copy the second part of the boot block.
  memcpy(&flashPageBuf[21], (uint8_t*)&minimalMBR[21], sizeof(minimalMBR) - 21);
  flashPageBuf[508] = 0xFF;
  flashPageBuf[509] = 0xFF;
  flashPageBuf[510] = 0x55;
  flashPageBuf[511] = 0xAA;
  // Flash the boot block table.
  bootloader_writeRawStorage((uint32_t)diskStorage, flashPageBuf, BOOT_BLOCK_BLOCKSIZE);

  flashPageBuf[0] = 0xF8;
  flashPageBuf[1] = 0xFF;
  flashPageBuf[2] = 0xFF;
  flashPageBuf[3] = 0x00;
  bootloader_writeRawStorage((uint32_t)diskStorage + 0x0200, flashPageBuf, 4);
  memset(flashPageBuf, 0, flashPageSize);
  bootloader_writeRawStorage((uint32_t)diskStorage + 0x0204, flashPageBuf, 0x9FC);
  bootloader_writeRawStorage((uint32_t)diskStorage + 0x0C00, flashPageBuf, 0x1000);
}
