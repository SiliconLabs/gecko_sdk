/**
 * @file serialapi_file.c
 * @copyright 2022 Silicon Laboratories Inc.
 * @brief Z-Wave Switch On/Off Sample Application
 * @details This sample application is a Z-Wave slave node which has an LED (D2
 * on ZDP03A) that can be turned on or off from another Z-Wave node by sending
 * a Basic Set On or a Basic Set Off command.
 *
 * It can be included and excluded from a Z-Wave network by pressing S1 switch
 * on the ZDP03A board 3 times. S2 switch toggles LED D2. S3 switch transmits
 * a Node Information Frame (NIF).
 * @author Someone who started this sample application at some point in time.
 * @author Thomas Roll (TRO)
 * @author Christian Salmony Olsen (COLSEN)
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#include <serialapi_file.h>
#include <string.h>
#include "SizeOf.h"
#include "Assert.h"
#include "DebugPrintConfig.h"
//#define DEBUGPRINT
//#include "DebugPrint.h"
#include "SyncEvent.h"
#include <ZW_system_startup_api.h>
#include <ZW_application_transport_interface.h>
#include <serialappl.h>
#include <ZAF_file_ids.h>
#include <zpal_nvm.h>
#include <zpal_misc.h>

#define APPLICATIONSIZE (4*1024)

#define APPL_DATA_FILE_SIZE            512

#define APP_VERSION_NO_20DBM_SUPPORT   0x00070F02

// Used by the application data file.
typedef struct SApplicationData
{
  uint8_t extNvm[APPL_DATA_FILE_SIZE];
} SApplicationData;
  /* listening | generic | specific | parmLength | nodeParms[] */
typedef struct SApplicationSettings
{
  uint8_t listening;  
  uint8_t generic;  
  uint8_t specific;
} SApplicationSettings;

typedef struct SApplicationCmdClassInfo
{
  uint8_t UnSecureIncludedCCLen;
  uint8_t UnSecureIncludedCC[APPL_NODEPARM_MAX];  
  uint8_t SecureIncludedUnSecureCCLen;
  uint8_t SecureIncludedUnSecureCC[APPL_NODEPARM_MAX];
  uint8_t SecureIncludedSecureCCLen;
  uint8_t SecureIncludedSecureCC[APPL_NODEPARM_MAX];

} SApplicationCmdClassInfo;

typedef struct SApplicationConfiguration
{
  zpal_radio_region_t rfRegion;
  int8_t              iTxPower;
  int8_t              ipower0dbmMeasured;
  uint8_t             radio_debug_enable;
  int16_t             maxTxPower;
} SApplicationConfiguration;

#define FILE_SIZE_APPLICATIONDATA        (sizeof(SApplicationData))
#define FILE_SIZE_APPLICATIONSETTINGS     (sizeof(SApplicationSettings))
#define FILE_SIZE_APPLICATIONCMDINFO     (sizeof(SApplicationCmdClassInfo))
#define FILE_SIZE_APPLICATIONCONFIGURATION (sizeof(SApplicationConfiguration))

static void WriteDefault(void);

// Application file system
static zpal_nvm_handle_t pFileSystemApplication;

uint8_t SerialApiFileInit(void)
{
  // Init application filesystem
  pFileSystemApplication = zpal_nvm_init(ZPAL_NVM_AREA_APPLICATION);
  if (pFileSystemApplication == NULL)
  {
    //DPRINTF("Failed Init App File System return value =%x\r\n",retvalue);
    ASSERT(false); //Assert has been kept for debugging , can be removed from production code. This error can only be caused by some internal flash HW failure
  }

  uint32_t appVersion;
  const zpal_status_t status = zpal_nvm_read(pFileSystemApplication, ZAF_FILE_ID_APP_VERSION, &appVersion, ZAF_FILE_SIZE_APP_VERSION);

  if (ZPAL_STATUS_OK == status)
  {
    if (zpal_get_app_version() != appVersion)
    {
      // Add code for migration of file system to higher version here.


      // If current version is 7.15.2 or older then update the FILE_ID_APPLICATIONCONFIGURATION file to the current format
      if (APP_VERSION_NO_20DBM_SUPPORT >= appVersion) {
        //Get length of legacy file
        size_t   dataLen;
        zpal_nvm_get_object_size(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &dataLen);

        //Read legacy file to first members of tApplicationConfiguration
        SApplicationConfiguration tApplicationConfiguration;
        zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, dataLen);

        //Write default values to new members of tApplicationConfiguration and update the file.
        tApplicationConfiguration.radio_debug_enable = 0;
        tApplicationConfiguration.maxTxPower = 140;
        zpal_nvm_write(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
      }
      appVersion = zpal_get_app_version();
      zpal_nvm_write(pFileSystemApplication, ZAF_FILE_ID_APP_VERSION, &appVersion, ZAF_FILE_SIZE_APP_VERSION);
    }
  }
  else
  {
    WriteDefault();
    return false;
  }
  return true;
}

static
bool ObjectExist(zpal_nvm_object_key_t key)
{
  zpal_status_t status;
  size_t   tDataLen;

  status = zpal_nvm_get_object_size(pFileSystemApplication, key, &tDataLen);
  if (ZPAL_STATUS_OK != status)
  {
    return false;
  }
  return true;
}

/**
 * @brief Reads application data from file system.
 */
uint8_t SerialApiNvmReadAppData(uint32_t offset, uint8_t* pAppData, uint32_t iLength)
{ 
  SApplicationData tApplicationData;

  uint8_t dataIsRead = false;
  zpal_status_t status;

  if (ObjectExist(FILE_ID_APPLICATIONDATA))
  {
    status = zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONDATA, &tApplicationData, FILE_SIZE_APPLICATIONDATA);
    if (ZPAL_STATUS_OK == status)
    {
      dataIsRead = true;
      for (uint32_t i = 0; i < iLength; i++)
      {
        pAppData[i] = tApplicationData.extNvm[i+  offset];
      }
    }
  }
  return dataIsRead;

}

/**
 * @brief Writes application data to file system.
 */
uint8_t SerialApiNvmWriteAppData(uint32_t offset, const uint8_t* pAppData, uint32_t iLength)
{
  SApplicationData tApplicationData;
  uint8_t dataIsWritten = false;
  zpal_status_t status;

  status = zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONDATA, &tApplicationData, FILE_SIZE_APPLICATIONDATA);
  if (ZPAL_STATUS_OK == status)
  {
    memcpy((uint8_t *)&tApplicationData + offset, pAppData, iLength);
    status = zpal_nvm_write(pFileSystemApplication, FILE_ID_APPLICATIONDATA, &tApplicationData, FILE_SIZE_APPLICATIONDATA);
    if (ZPAL_STATUS_OK == status)
    {
      dataIsWritten = true;
    }
  }
  return dataIsWritten;
}

uint8_t
SaveApplicationSettings(uint8_t bListening,
                        uint8_t bGeneric,
                        uint8_t bSpecific
                       )
{
  SApplicationSettings tApplicationSettings;
  uint8_t dataIsWritten = false;
  zpal_status_t status;

  status = zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONSETTINGS, &tApplicationSettings, FILE_SIZE_APPLICATIONSETTINGS);
  if (ZPAL_STATUS_OK == status)
  {
    tApplicationSettings.listening = bListening;
    tApplicationSettings.generic = bGeneric;
    tApplicationSettings.specific = bSpecific;
    status = zpal_nvm_write(pFileSystemApplication, FILE_ID_APPLICATIONSETTINGS, &tApplicationSettings, FILE_SIZE_APPLICATIONSETTINGS);
    if (ZPAL_STATUS_OK == status)
    {
      dataIsWritten = true;
    }
  }
  return dataIsWritten;
}


uint8_t
ReadApplicationSettings(uint8_t* pListening,
                        uint8_t* pGeneric,
                        uint8_t* pSpecific
                       )
{
  SApplicationSettings tApplicationSettings;
  uint8_t dataIsRead = false;
  zpal_status_t status;

  if (ObjectExist(FILE_ID_APPLICATIONSETTINGS))
  {
    status = zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONSETTINGS, &tApplicationSettings, FILE_SIZE_APPLICATIONSETTINGS);
    if (ZPAL_STATUS_OK == status)
    {
      *pListening = tApplicationSettings.listening;
      *pGeneric = tApplicationSettings.generic ;
      *pSpecific = tApplicationSettings.specific;
      dataIsRead = true;
    }
  }
  return dataIsRead;

}


uint8_t
SaveApplicationCCInfo (uint8_t        bUnSecureIncludedCCLen,
                       const uint8_t* pUnSecureIncludedCC,
                       uint8_t        bSecureIncludedUnSecureCCLen,
                       const uint8_t* pSecureIncludedUnSecureCC,
                       uint8_t        bSecureIncludedSecureCCLen,
                       const uint8_t* pSecureIncludedSecureCC)
{
  SApplicationCmdClassInfo tApplicationCmdClassInfo;
  uint8_t dataIsWritten = false;
  zpal_status_t status;

  status = zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONCMDINFO, &tApplicationCmdClassInfo, FILE_SIZE_APPLICATIONCMDINFO);
  if (ZPAL_STATUS_OK == status)
  {

    tApplicationCmdClassInfo.UnSecureIncludedCCLen = bUnSecureIncludedCCLen;
    tApplicationCmdClassInfo.SecureIncludedUnSecureCCLen = bSecureIncludedUnSecureCCLen;
    tApplicationCmdClassInfo.SecureIncludedSecureCCLen = bSecureIncludedSecureCCLen;

    for (uint8_t i = 0; i < APPL_NODEPARM_MAX; i++)
    {
      if (i < bUnSecureIncludedCCLen)
      {
        tApplicationCmdClassInfo.UnSecureIncludedCC[i] = pUnSecureIncludedCC[i];
      }
      else
      {
        tApplicationCmdClassInfo.UnSecureIncludedCC[i] = 0;
      }

      if (i < bSecureIncludedUnSecureCCLen)
      {
        tApplicationCmdClassInfo.SecureIncludedUnSecureCC[i] = pSecureIncludedUnSecureCC[i];
      }
      else
      {
        tApplicationCmdClassInfo.SecureIncludedUnSecureCC[i] = 0;
      }

      if (i < bSecureIncludedSecureCCLen)
      {
        tApplicationCmdClassInfo.SecureIncludedSecureCC[i] = pSecureIncludedSecureCC[i];
      }
      else
      {
        tApplicationCmdClassInfo.SecureIncludedSecureCC[i] = 0;
      }

      }
      status = zpal_nvm_write(pFileSystemApplication, FILE_ID_APPLICATIONCMDINFO, &tApplicationCmdClassInfo, FILE_SIZE_APPLICATIONCMDINFO);
      if (ZPAL_STATUS_OK == status)
      {
        dataIsWritten = true;
      }
  }
  return dataIsWritten;

}


uint8_t
ReadApplicationCCInfo (uint8_t* pUnSecureIncludedCCLen,
                       uint8_t* pUnSecureIncludedCC,
                       uint8_t* pSecureIncludedUnSecureCCLen,
                       uint8_t* pSecureIncludedUnSecureCC,
                       uint8_t* pSecureIncludedSecureCCLen,
                       uint8_t* pSecureIncludedSecureCC)
{
  SApplicationCmdClassInfo tApplicationCmdClassInfo;
  uint8_t dataIsRead = false;
  zpal_status_t status;

  if (ObjectExist(FILE_ID_APPLICATIONCMDINFO))
  {
    status = zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONCMDINFO, &tApplicationCmdClassInfo, FILE_SIZE_APPLICATIONCMDINFO);
    if (ZPAL_STATUS_OK == status)
    {
      dataIsRead = true;
      *pUnSecureIncludedCCLen = tApplicationCmdClassInfo.UnSecureIncludedCCLen;
      *pSecureIncludedUnSecureCCLen = tApplicationCmdClassInfo.SecureIncludedUnSecureCCLen;
      *pSecureIncludedSecureCCLen = tApplicationCmdClassInfo.SecureIncludedSecureCCLen;
      for (uint8_t i = 0; i < APPL_NODEPARM_MAX; i++)
      {
        if (i < *pUnSecureIncludedCCLen)
        {
          pUnSecureIncludedCC[i] = tApplicationCmdClassInfo.UnSecureIncludedCC[i] ;
        }
        else
        {
          pUnSecureIncludedCC[i] = 0;
        }

        if (i < *pSecureIncludedUnSecureCCLen)
        {
          pSecureIncludedUnSecureCC[i] = tApplicationCmdClassInfo.SecureIncludedUnSecureCC[i];
        }
        else
        {
          pSecureIncludedUnSecureCC[i] = 0;
        }

        if (i < *pSecureIncludedSecureCCLen)
        {
          pSecureIncludedSecureCC[i] = tApplicationCmdClassInfo.SecureIncludedSecureCC[i];
        }
        else
        {
          pSecureIncludedSecureCC[i] = 0;
        }

      }
    }
  }
  return dataIsRead;

}

uint8_t
SaveApplicationRfRegion(zpal_radio_region_t rfRegion)
{
  SApplicationConfiguration tApplicationConfiguration;
  uint8_t dataIsWritten = false;
  zpal_status_t status;

  status = zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
  if (ZPAL_STATUS_OK == status)
  {
    tApplicationConfiguration.rfRegion = rfRegion;
    status = zpal_nvm_write(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
    if (ZPAL_STATUS_OK == status)
    {
      dataIsWritten = true;
    }
  }
  return dataIsWritten;
}

uint8_t
ReadApplicationRfRegion(zpal_radio_region_t* rfRegion)
{
  SApplicationConfiguration tApplicationConfiguration;
  uint8_t dataIsRead = false;
  zpal_status_t status;

  if (ObjectExist(FILE_ID_APPLICATIONCONFIGURATION))
  {
    status = zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
    if (ZPAL_STATUS_OK == status)
    {
      *rfRegion = tApplicationConfiguration.rfRegion;
      dataIsRead = true;
    }
  }
  return dataIsRead;

}

uint8_t
SaveApplicationTxPowerlevel(int8_t ipower, int8_t power0dbmMeasured)
{
  SApplicationConfiguration tApplicationConfiguration;
  uint8_t dataIsWritten = false;
  zpal_status_t status;

  status = zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
  if (ZPAL_STATUS_OK == status)
  {
    tApplicationConfiguration.iTxPower = ipower;
    tApplicationConfiguration.ipower0dbmMeasured = power0dbmMeasured;
    status = zpal_nvm_write(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
    if (ZPAL_STATUS_OK == status)
    {
      dataIsWritten = true;
    }
  }
  return dataIsWritten;
}


uint8_t
ReadApplicationTxPowerlevel(int8_t *ipower, int8_t *power0dbmMeasured)
{
  SApplicationConfiguration tApplicationConfiguration;
  uint8_t dataIsRead = false;
  zpal_status_t status;

  if (ObjectExist(FILE_ID_APPLICATIONCONFIGURATION))
  {
    status = zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
    if (ZPAL_STATUS_OK == status)
    {
      *ipower = tApplicationConfiguration.iTxPower;
      *power0dbmMeasured = tApplicationConfiguration.ipower0dbmMeasured;
      dataIsRead = true;
    }
  }
  return dataIsRead;
}


uint8_t
SaveApplicationMaxLRTxPwr(int16_t maxTxPwr)
{
  SApplicationConfiguration tApplicationConfiguration;
  uint8_t dataIsWritten = false;
  zpal_status_t status;

  status = zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
  if (ZPAL_STATUS_OK == status)
  {
    tApplicationConfiguration.maxTxPower = maxTxPwr;
    status = zpal_nvm_write(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
    if (ZPAL_STATUS_OK == status)
    {
      dataIsWritten = true;
    }
  }
  return dataIsWritten;
}


uint8_t
ReadApplicationMaxLRTxPwr(int16_t *maxTxPwr)
{
  SApplicationConfiguration tApplicationConfiguration;
  uint8_t dataIsRead = false;
  zpal_status_t status;

  if (ObjectExist(FILE_ID_APPLICATIONCONFIGURATION))
  {
    status = zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
    if (ZPAL_STATUS_OK == status)
    {
      *maxTxPwr = tApplicationConfiguration.maxTxPower;
      dataIsRead = true;
    }
  }
  return dataIsRead;
}


uint8_t
SaveApplicationEnablePTI(uint8_t radio_debug_enable)
{
  SApplicationConfiguration tApplicationConfiguration;
  uint8_t dataIsWritten = false;
  zpal_status_t status;

  status = zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
  if (ZPAL_STATUS_OK == status)
  {
    tApplicationConfiguration.radio_debug_enable = radio_debug_enable;
    status = zpal_nvm_write(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
    if (ZPAL_STATUS_OK == status)
    {
      dataIsWritten = true;
    }
  }
  return dataIsWritten;
}


uint8_t
ReadApplicationEnablePTI(uint8_t *radio_debug_enable)
{
  SApplicationConfiguration tApplicationConfiguration;
  uint8_t dataIsRead = false;
  zpal_status_t status;

  if (ObjectExist(FILE_ID_APPLICATIONCONFIGURATION))
  {
    status = zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
    if (ZPAL_STATUS_OK == status)
    {
      *radio_debug_enable = tApplicationConfiguration.radio_debug_enable;
      dataIsRead = true;
    }
  }
  return dataIsRead;
}


uint32_t
ReadApplicationVersion(void)
{
  uint32_t appVersion;
  zpal_nvm_read(pFileSystemApplication, ZAF_FILE_ID_APP_VERSION, &appVersion, sizeof(appVersion));

  return appVersion;
}

static void
WriteDefaultApplicationSettings(void)
{
  zpal_status_t status;

  //Write default Application Settings file
  SApplicationSettings tApplicationSettings;
  memset(&tApplicationSettings, 0 , sizeof(SApplicationSettings));
  status = zpal_nvm_write(pFileSystemApplication, FILE_ID_APPLICATIONSETTINGS, &tApplicationSettings, sizeof(SApplicationSettings));
  ASSERT(ZPAL_STATUS_OK == status); //Assert has been kept for debugging only, can be removed from production code. This error can only be caused by some internal flash driver/Hw prroblem
}

static void
WriteDefaultApplicationCmdClassInfo(void)
{
  zpal_status_t status;

  //Write default ApplicationCmdClassInfo file
  SApplicationCmdClassInfo tApplicationCmdClassInfo;
  memset(&tApplicationCmdClassInfo, 0 , sizeof(SApplicationCmdClassInfo));
  status = zpal_nvm_write(pFileSystemApplication, FILE_ID_APPLICATIONCMDINFO, &tApplicationCmdClassInfo, sizeof(SApplicationCmdClassInfo));
  ASSERT(ZPAL_STATUS_OK == status); //Assert has been kept for debugging only, can be removed from production code. This error can only be caused by some internal flash driver/Hw prroblem
}

static void
WriteDefaultApplicationData(void)
{
  zpal_status_t status;

  //Write default Controller Info file
  SApplicationData tApplicationData;
  memset(&tApplicationData, 0 , sizeof(SApplicationData));
  status = zpal_nvm_write(pFileSystemApplication, FILE_ID_APPLICATIONDATA, &tApplicationData, sizeof(SApplicationData));
  ASSERT(ZPAL_STATUS_OK == status); //Assert has been kept for debugging only, can be removed from production code. This error can only be caused by some internal flash driver/Hw prroblem
}

static void
WriteDefaultApplicationConfiguration(void)
{
  zpal_status_t status;

  //Write default Application Configuration file
  SApplicationConfiguration tApplicationConfiguration;
  memset(&tApplicationConfiguration, 0 , sizeof(SApplicationConfiguration));
  status = zpal_nvm_write(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, sizeof(SApplicationConfiguration));
  ASSERT(ZPAL_STATUS_OK == status); //Assert has been kept for debugging only, can be removed from production code. This error can only be caused by some internal flash driver/Hw prroblem
}

static void
WriteDefaultApplicationFileSystemVersion(void)
{
  zpal_status_t status;

  //Write Application filesystem version
  uint32_t appVersion = (APP_VERSION << 16) | (APP_REVISION << 8) | APP_PATCH;
  status = zpal_nvm_write(pFileSystemApplication, ZAF_FILE_ID_APP_VERSION, &appVersion, sizeof(appVersion));
  ASSERT(ZPAL_STATUS_OK == status); //Assert has been kept for debugging only, can be removed from production code. This error can only be caused by some internal flash driver/Hw prroblem
}

static void
WriteDefault(void)
{
  WriteDefaultApplicationSettings();

  WriteDefaultApplicationCmdClassInfo();

  WriteDefaultApplicationData();

  WriteDefaultApplicationConfiguration();

  WriteDefaultApplicationFileSystemVersion();
}

zpal_nvm_handle_t SerialAPIGetFileSystemHandle(void)
{
  return pFileSystemApplication;
}
