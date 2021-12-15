/***************************************************************************//**
 * @file
 * @brief Gecko Bootloader USB host MSD loader example.
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
#include <inttypes.h>
#include <application_properties.h>

#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_core.h"
#include "bsp.h"
#include "bsp_trace.h"
#include "retargetserial.h"
#include "em_usb.h"
#include "msdh.h"
#include "ff.h"
#include "btl_interface.h"

// -----------------------------------------------------------------------------
// Defines
#define USBBUFSIZE         1024
#define FLASH_PAGESIZE     FLASH_PAGE_SIZE

#define FILE_EXT_UPP       "GBL"
#define FILE_EXT_LOW       "gbl"

#define SLOT_ID            0             // Bootloader default storage space ID
#define PATH_LENGTH        260

// -----------------------------------------------------------------------------
// Local Global Variables

// Bootloader storage space address
static uint8_t *diskStorage;

// File system
static FATFS Fatfs;
static FIL   fh;

// USB related data
STATIC_UBUF(tmpBuf, USBBUFSIZE);

// Read data buffer
static char flashPageBuf[((FLASH_PAGESIZE) +3) & ~3];
static UINT bufRead;

/*
 * The path array length is important when running checkValidGbl(path).
 * checkValidGbl is recursive and will traverse the directory tree.
 * The length of "path" need to be equal the maximum "path + filename"
 * length existing on the disk.
 * Max path length on MSDOS FAT12/16 is 260, on FAT32 there is no limit.
 * The files with path name longer than 260 will not be found.
 * Keep in mind that the FatFs library uses 8.3 name notation.
 *
 * When using checkValidGbl on large directory trees the default stacksize
 * might be too small due to checkValidGbl recursive operation.
 */
static char path[PATH_LENGTH];
static BootloaderInformation_t info;

//extern const ApplicationProperties_t sl_app_properties;

/// Unique ID (e.g. UUID or GUID) for the product this application is built for (uint8_t[16])
#define APP_PROPERTIES_ID { 0 }

const ApplicationProperties_t sl_app_properties = {
  /// @brief Magic value indicating that this is an ApplicationProperties_t struct.
  /// Must equal @ref APPLICATION_PROPERTIES_MAGIC
  .magic = APPLICATION_PROPERTIES_MAGIC,
  /// Version number of this struct
  .structVersion = APPLICATION_PROPERTIES_VERSION,
  /// Type of signature this application is signed with
  .signatureType = APPLICATION_SIGNATURE_NONE,
  /// Location of the signature. Typically a pointer to the end of the application
  .signatureLocation = 0,
  /// Information about the application
  .app = {
    /// Bitfield representing type of application, e.g. @ref APPLICATION_TYPE_BLUETOOTH_APP
    .type = APPLICATION_TYPE_MCU,
    /// Version number for this application
    .version = APP_PROPERTIES_VERSION,
    /// Capabilities of this application
    .capabilities = 0,
    /// Unique ID (e.g. UUID or GUID) for the product this application is built for
    .productId = APP_PROPERTIES_ID,
  },
};



// -----------------------------------------------------------------------------
// Local Function Prototypes
static int32_t flushFlash(uint32_t addr);
static bool reprogramGBLStorage(char* path, char* fileName);
static bool checkValidGbl(char* path);
static void reProgramBLApp(void);
static int32_t eraseStorageSlot(uint32_t slotID);

/***************************************************************************//**
 * @brief
 *   This function is required by the FAT file system in order to provide
 *   timestamps for created files. Since we do not have a reliable clock we
 *   hardcode a value here.
 *
 *   Refer to reptile/fatfs/doc/en/fattime.html for the format of this DWORD.
 *
 * @return
 *    A DWORD containing the current time and date as a packed datastructure.
 ******************************************************************************/
DWORD get_fattime(void)
{
  return (28 << 25) | (2 << 21) | (1 << 16);
}

/***************************************************************************//**
 * @brief
 *   Erase and rewrite a flash page.
 *
 * @param[in] addr
 *   Address of the flash memory to be rewritten
 *
 * @return
 *   Bootloader error code
 ******************************************************************************/
static int32_t flushFlash(uint32_t addr)
{
  int32_t ret;

  // Erase flash page
  ret = bootloader_eraseRawStorage(addr, FLASH_PAGESIZE);

  if (ret & BOOTLOADER_ERROR_STORAGE_BASE) {
    return ret;
  }

  // Program flash page
  ret = bootloader_writeRawStorage(addr, (uint8_t*)flashPageBuf, FLASH_PAGESIZE);
  return ret;
}

/***************************************************************************//**
 * @brief
 *   Process a file and reprogram the bootloader storage area
 *
 * @param[in] path
 *   Path of the file to be processed
 *
 * @param[in] fileName
 *   Name of the file to be processed
 *
 * @return
 *   True if the reprogrammed image is valid, otherwise false
 ******************************************************************************/
static bool reprogramGBLStorage(char* path, char* fileName)
{
  int32_t  ret;
  uint8_t* flashAddr = diskStorage;
  FRESULT  res;
  char     fileDir[PATH_LENGTH];

  strcpy(fileDir, path);
  strcat(fileDir, "/");
  strcat(fileDir, fileName);

  res = f_open(&fh, fileDir, FA_READ);
  if (res == FR_OK) {
    while (1) {
      res = f_read(&fh, flashPageBuf, FLASH_PAGESIZE, &bufRead);
      if ((res == FR_OK) && (bufRead > 0)) {
        ret = flushFlash((uint32_t)flashAddr);
        if (ret != BOOTLOADER_OK) {
          printf("Writing to the flash failed %ld\n", ret);
          break;
        }
        flashAddr += bufRead;
      } else {
        break;
      }
    }
  } else {
    printf("Failed to open %s\n", fileDir);
  }
  f_close(&fh);

  if (bootloader_verifyImage(SLOT_ID, NULL) == BOOTLOADER_OK) {
    return true;
  }
  return false;
}

/***************************************************************************//**
 * @brief
 *   Scan files recursively from the disk
 *
 * @param[in] path
 *   Path to traverse
 *
 * @return
 *   True if a valid GBL file is found, otherwise false
 ******************************************************************************/
static bool checkValidGbl(char* path)
{
  DIR         dir;
  FRESULT     res;
  FILINFO     fno;
  int         pathLen, fnLen;
  char        *fn;
  bool        returnVal;

  returnVal = false;
  res = f_opendir(&dir, path);
  if (res == FR_OK) {
    pathLen = strlen(path);
    while (1) {
      res = f_readdir(&dir, &fno);
      if (res != FR_OK || fno.fname[0] == 0) {
        break;
      }
      if (fno.fname[0] == '.') {
        continue;
      }
      fn = fno.fname;
      fnLen = strlen(fn);

      if ((fno.fattrib & AM_DIR)
          && (pathLen + fnLen + 1) <= PATH_LENGTH) {
        sprintf(&path[pathLen], "/%s", fn);
        returnVal = checkValidGbl(path);
        if (returnVal) {
          break;
        }
        path[pathLen] = 0;
      } else {
        if (strncmp((char *)&fn[fnLen - 3], FILE_EXT_UPP, 3) == 0
            && (pathLen + fnLen + 1) <= PATH_LENGTH) {
          returnVal = reprogramGBLStorage(path, fn);
          if (returnVal) {
            return true;
          }
        }
      }
    }
  } else {
    printf("f_opendir failure %d\n", res);
  }
  return returnVal;
}

/***************************************************************************//**
 * @brief
 *   Find a valid GBL file and reprogram the flash.
 ******************************************************************************/
static void reProgramBLApp(void)
{
  FRESULT res;
  bool    gblFound;
  uint32_t appVersionNewImg, imgInfoVersion;
  ApplicationData_t appinfo;

  // Initialize filesystem
  res = f_mount(0, &Fatfs);
  if (res != FR_OK) {
    printf("FAT-mount failed: %d\n", res);
    return;
  } else {
    printf("FAT-mount successful\n");
  }

  gblFound = checkValidGbl(path);
  if (gblFound) {
    if (bootloader_setImageToBootload(SLOT_ID) == BOOTLOADER_OK) {
      bootloader_getImageInfo(SLOT_ID, &appinfo, &imgInfoVersion);
      appVersionNewImg = appinfo.version;

      if (appVersionNewImg > sl_app_properties.app.version) {
        printf("\nA valid GBL with a newer application version found, reprogramming the flash\n");
        f_mount(0, NULL);
        USBTIMER_DelayMs(500); // Wait 500 ms before system reset
        bootloader_rebootAndInstall();
      } else {
        printf("\nThe GBL file contains an application upgrade image with same/older version\n");
      }
    }
  } else {
    printf("No valid GBL file found\n");
  }
  // Clean the bootloader storage space
  printf("Erasing the bootloader storage space...\n");
  if (eraseStorageSlot(SLOT_ID) == BOOTLOADER_OK) {
    printf("Erasing the bootloader storage space completed\n");
  }
  // UNMOUNT drive
  printf("USB un-mounting...\n");
  if (f_mount(0, NULL) == FR_OK) {
    printf("USB un-mounted\n");
  }
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

/***************************************************************************//**
 * @brief main
 ******************************************************************************/
int main(void)
{
  int connectionResult;
  USBH_Init_TypeDef is = USBH_INIT_DEFAULT;
  BootloaderStorageSlot_t storageSlot;
  CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_DEFAULT;

  // Chip errata
  CHIP_Init();
  BSP_Init(BSP_INIT_DEFAULT);

  // If first word of user data page is non-zero, enable Energy Profiler trace
  BSP_TraceProfilerSetup();
  CMU_HFXOInit(&hfxoInit);
  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);

  RETARGET_SerialInit();
  RETARGET_SerialCrLf(1);
  printf("\n\n***USBH Loader Demo***\n");

  // Initialize USB HOST stack
  USBH_Init(&is);
  bootloader_getInfo(&info);
  printf("\nCurrent Bootloader Version: %lx \n", info.version);
  if (info.type == NO_BOOTLOADER) {
    printf("\nNo bootloader is present (first stage or main stage invalid)\n");
    EFM_ASSERT(false);
  }

  // Initialize Boot Loader
  if (bootloader_init() & BOOTLOADER_ERROR_INIT_BASE) {
    EFM_ASSERT(false);
  }

  if (bootloader_getStorageSlotInfo(SLOT_ID, &storageSlot) & BOOTLOADER_ERROR_STORAGE_BASE) {
    EFM_ASSERT(false);
  }
  printf("\nCurrent APP version: %" PRIu32 "\n", sl_app_properties.app.version);
  diskStorage = (uint8_t*)storageSlot.address;
  while (1) {
    // Wait for device connection
    printf("\nWaiting for USB MSD device plug-in...\n");
    connectionResult = USBH_WaitForDeviceConnectionB(tmpBuf, 0);

    if (connectionResult == USB_STATUS_OK) {
      printf("A device was attached");

      if (MSDH_Init(tmpBuf, sizeof(tmpBuf))) {
        reProgramBLApp();
      } else {
        printf("\nMSD initialization error, please remove device\n");
      }
    } else if (connectionResult == USB_STATUS_DEVICE_MALFUNCTION) {
      printf("\nA malfunctioning device was attached, please remove device\n");
    } else if (connectionResult == USB_STATUS_PORT_OVERCURRENT) {
      printf("\nVBUS overcurrent condition, please remove device\n");
    }

    while (USBH_DeviceConnected()) ;
    printf("\nDevice removal detected");
  }
}
