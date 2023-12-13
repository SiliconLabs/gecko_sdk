/**
 * @file
 * Handler for Command Class Version.
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include <ZW_TransportEndpoint.h>
#include <ZW_TransportSecProtocol.h>
#include "ZW_application_transport_interface.h"
#include <string.h>
#include "ZAF_Common_interface.h"
#include <zaf_config_api.h>
#include <zpal_bootloader.h>
#include <zpal_misc.h>
#include "zw_build_no.h"
//#define DEBUGPRINT
#include "DebugPrint.h"

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                             WEAK FUNCTIONS                               */
/****************************************************************************/

/**
 * Get firmware version of given firmware target index.
 *
 * This function is weakly defined so that an application can implement it in case of support for
 * more firmware targets.
 *
 * @param[in] firmwareTargetIndex Firmware target index of the custom firmware target.
 * @param[out] pVariantgroup returns pointer to application version group number n.
 */
ZW_WEAK void CC_Version_GetFirmwareVersion_handler(
    __attribute__((unused)) uint8_t firmwareTargetIndex,
    __attribute__((unused)) VG_VERSION_REPORT_V2_VG* pVariantgroup)
{
}

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/

static void
CC_Version_add_bootloader(
  VG_VERSION_REPORT_V2_VG *pVariantgroup)
{
  zpal_bootloader_info_t bootloader_info = { 0 };

  zpal_bootloader_get_info(&bootloader_info);
  pVariantgroup->firmwareVersion =
    ((uint8_t)((bootloader_info.version & ZPAL_BOOTLOADER_VERSION_MAJOR_MASK) >> ZPAL_BOOTLOADER_VERSION_MAJOR_SHIFT));
  pVariantgroup->firmwareSubVersion =
    ((uint8_t)((bootloader_info.version & ZPAL_BOOTLOADER_VERSION_MINOR_MASK) >> ZPAL_BOOTLOADER_VERSION_MINOR_SHIFT));
}

static received_frame_status_t CC_Version_handler(
    RECEIVE_OPTIONS_TYPE_EX *rxOpt,
    ZW_APPLICATION_TX_BUFFER *pCmd,
    __attribute__((unused)) uint8_t cmdLength,
    ZW_APPLICATION_TX_BUFFER * pFrameOut,
    uint8_t * pLengthOut)
{
  SApplicationHandles * pAppHandles;

  if(true == Check_not_legal_response_job(rxOpt))
  {
    /*Do not support endpoint bit-addressing */
    return RECEIVED_FRAME_STATUS_FAIL;
  }

  switch (pCmd->ZW_VersionGetFrame.cmd)
  {
    case VERSION_GET_V2:
    {
      uint8_t firmwareTargetIndex;/*firmware target number 1..N */
      uint8_t numberOfFirmwareTargets;
      pFrameOut->ZW_VersionReport1byteV2Frame.cmdClass = COMMAND_CLASS_VERSION_V2;
      pFrameOut->ZW_VersionReport1byteV2Frame.cmd = VERSION_REPORT_V2;

      pAppHandles = ZAF_getAppHandle();
      pFrameOut->ZW_VersionReport1byteV2Frame.zWaveLibraryType = pAppHandles->pProtocolInfo->eLibraryType;
      pFrameOut->ZW_VersionReport1byteV2Frame.zWaveProtocolVersion = pAppHandles->pProtocolInfo->ProtocolVersion.Major;
      pFrameOut->ZW_VersionReport1byteV2Frame.zWaveProtocolSubVersion = pAppHandles->pProtocolInfo->ProtocolVersion.Minor;
      pFrameOut->ZW_VersionReport1byteV2Frame.firmware0Version = zpal_get_app_version_major();
      pFrameOut->ZW_VersionReport1byteV2Frame.firmware0SubVersion = zpal_get_app_version_minor();
      pFrameOut->ZW_VersionReport1byteV2Frame.hardwareVersion = zaf_config_get_hardware_version();
      numberOfFirmwareTargets = zaf_config_get_firmware_target_count();
      if(zaf_config_get_bootloader_upgradable()) {
        numberOfFirmwareTargets++;
      }
      pFrameOut->ZW_VersionReport1byteV2Frame.numberOfFirmwareTargets = numberOfFirmwareTargets - 1;/*-1 : Firmware version 0*/

      for (firmwareTargetIndex = 1; firmwareTargetIndex < numberOfFirmwareTargets; firmwareTargetIndex++)
      {
        uint8_t * pFrame = (uint8_t *)&(pFrameOut->ZW_VersionReport1byteV2Frame.variantgroup1);
        if(zaf_config_get_bootloader_upgradable() && zaf_config_get_bootloader_target_id() == firmwareTargetIndex) {     
          CC_Version_add_bootloader((VG_VERSION_REPORT_V2_VG *)(pFrame + 2 * (firmwareTargetIndex - 1)));
        } else {
          CC_Version_GetFirmwareVersion_handler(firmwareTargetIndex, (VG_VERSION_REPORT_V2_VG *)(pFrame + 2 * (firmwareTargetIndex - 1)));
        }
      }

      *pLengthOut = sizeof(pFrameOut->ZW_VersionReport1byteV2Frame) + (numberOfFirmwareTargets - 1)* sizeof(VG_VERSION_REPORT_V2_VG) - sizeof(VG_VERSION_REPORT_V2_VG); /*-1 is Firmware version 0*/

      return RECEIVED_FRAME_STATUS_SUCCESS;
    }
    case VERSION_COMMAND_CLASS_GET_V2:
      pFrameOut->ZW_VersionCommandClassReportFrame.cmdClass = COMMAND_CLASS_VERSION_V2;
      pFrameOut->ZW_VersionCommandClassReportFrame.cmd = VERSION_COMMAND_CLASS_REPORT_V2;
      pFrameOut->ZW_VersionCommandClassReportFrame.requestedCommandClass = pCmd->ZW_VersionCommandClassGetFrame.requestedCommandClass;

      pAppHandles = ZAF_getAppHandle();
      uint8_t version = 0xFF;
      uint8_t cc = pCmd->ZW_VersionCommandClassGetFrame.requestedCommandClass;

      zaf_cc_list_t *cc_list = GetCommandClassList(false, SECURITY_KEY_NONE, 0);

      /*
        * Transport Service, Security S0 and S2 versions must be returned only if they are
        * listed in the NIF. Since these command classes must always be in the non-secure list, we
        * can use that list to check it.
        */
      if (memchr(cc_list->cc_list,
                  cc,
                  cc_list->list_size))
      {
        // CC is in the list
        switch (pCmd->ZW_VersionCommandClassGetFrame.requestedCommandClass)
        {
          case COMMAND_CLASS_TRANSPORT_SERVICE:
            version = pAppHandles->pProtocolInfo->CommandClassVersions.TransportServiceVersion;
            break;
          case COMMAND_CLASS_SECURITY:
            version = pAppHandles->pProtocolInfo->CommandClassVersions.SecurityVersion;
            break;
          case COMMAND_CLASS_SECURITY_2:
            version = pAppHandles->pProtocolInfo->CommandClassVersions.Security2Version;
            break;
          default:
            // Do nothing.
            break;
        }
      }

      pFrameOut->ZW_VersionCommandClassReportFrame.commandClassVersion = version;

      if (0xFF == pFrameOut->ZW_VersionCommandClassReportFrame.commandClassVersion)
      {
        /*
        * When every CC uses the REGISTER_CC() macro, the compiler creates a section in the code.
        * Also two variables are automatically created and these represent the beginning and the end
        * of the section. The variables can be used to loop through the section.
        */
        CC_handler_map_latest_t const * iter = &cc_handlers_start;
        for ( ; iter < &cc_handlers_stop; ++iter)
        {
          if (pCmd->ZW_VersionCommandClassGetFrame.requestedCommandClass == iter->CC)
          {
            DPRINTF("\r\nCC: %#x - Version: %d\r\n", iter->CC, iter->version);
            pFrameOut->ZW_VersionCommandClassReportFrame.commandClassVersion = iter->version;
          }
        }
        if (0xFF == pFrameOut->ZW_VersionCommandClassReportFrame.commandClassVersion)
        {
          pFrameOut->ZW_VersionCommandClassReportFrame.commandClassVersion = 0; // Value if not found
        }
      }

      *pLengthOut = sizeof(pFrameOut->ZW_VersionCommandClassReportFrame);

      return RECEIVED_FRAME_STATUS_SUCCESS;
    case VERSION_CAPABILITIES_GET_V3:
      pFrameOut->ZW_VersionCapabilitiesReportV3Frame.cmdClass    = COMMAND_CLASS_VERSION_V3;
      pFrameOut->ZW_VersionCapabilitiesReportV3Frame.cmd         = VERSION_CAPABILITIES_REPORT_V3;

      /*
       * The following pointer constellation might seem unnecessary, but it's done to make the
       * code more readable and to enable/disable each flags easier.
       *
       * Sigma Designs' Z-Wave applications support all commands, but the support can be toggled
       * corresponding to the Version Command Class specification
       */
      {
        uint8_t * pProperties = &(pFrameOut->ZW_VersionCapabilitiesReportV3Frame.properties1);
        *pProperties = 0x00;

        *pProperties |= VERSION_CAPABILITIES_REPORT_PROPERTIES1_VERSION_BIT_MASK_V3;
        *pProperties |= VERSION_CAPABILITIES_REPORT_PROPERTIES1_COMMAND_CLASS_BIT_MASK_V3;
        *pProperties |= VERSION_CAPABILITIES_REPORT_PROPERTIES1_Z_WAVE_SOFTWARE_BIT_MASK_V3;
      }

      *pLengthOut = sizeof(pFrameOut->ZW_VersionCapabilitiesReportV3Frame);

      return RECEIVED_FRAME_STATUS_SUCCESS;
    case VERSION_ZWAVE_SOFTWARE_GET_V3:
    {
      uint16_t zaf_build_no;
      zaf_build_no = zaf_config_get_build_no();
      uint16_t protocol_build_no;
      protocol_build_no = ZW_GetProtocolBuildNumber();

      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.cmdClass    = COMMAND_CLASS_VERSION_V3;
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.cmd         = VERSION_ZWAVE_SOFTWARE_REPORT_V3;

      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.sdkVersion1 = SDK_VERSION_MAJOR;
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.sdkVersion2 = SDK_VERSION_MINOR;
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.sdkVersion3 = SDK_VERSION_PATCH;

      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.applicationFrameworkApiVersion1 = ZAF_VERSION_MAJOR;
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.applicationFrameworkApiVersion2 = ZAF_VERSION_MINOR;
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.applicationFrameworkApiVersion3 = ZAF_VERSION_PATCH;

      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.applicationFrameworkBuildNumber1 = (uint8_t)(ZAF_BUILD_NO >> 8);
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.applicationFrameworkBuildNumber2 = (uint8_t)ZAF_BUILD_NO;

      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.hostInterfaceVersion1 = 0;
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.hostInterfaceVersion2 = 0;
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.hostInterfaceVersion3 = 0;
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.hostInterfaceBuildNumber1 = (uint8_t)(0 >> 8);
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.hostInterfaceBuildNumber2 = (uint8_t)0;

      pAppHandles = ZAF_getAppHandle();
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.zWaveProtocolVersion1 = pAppHandles->pProtocolInfo->ProtocolVersion.Major;
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.zWaveProtocolVersion2 = pAppHandles->pProtocolInfo->ProtocolVersion.Minor;
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.zWaveProtocolVersion3 = pAppHandles->pProtocolInfo->ProtocolVersion.Revision;
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.zWaveProtocolBuildNumber1 = (uint8_t)(protocol_build_no >> 8);
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.zWaveProtocolBuildNumber2 = (uint8_t)protocol_build_no;

      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.applicationVersion1 = zpal_get_app_version_major();
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.applicationVersion2 = zpal_get_app_version_minor();
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.applicationVersion3 = zpal_get_app_version_patch();
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.applicationBuildNumber1 = (uint8_t)(zaf_build_no >> 8);
      pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame.applicationBuildNumber2 = (uint8_t)zaf_build_no;

      *pLengthOut = sizeof(pFrameOut->ZW_VersionZwaveSoftwareReportV3Frame);

      return RECEIVED_FRAME_STATUS_SUCCESS;
    }

    default:
      // Do nothing.
      break;
  }
  return RECEIVED_FRAME_STATUS_NO_SUPPORT;
}

REGISTER_CC_V2(COMMAND_CLASS_VERSION, VERSION_VERSION_V3, CC_Version_handler);
