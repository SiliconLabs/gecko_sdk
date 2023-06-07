/***************************************************************************//**
 * @file
 * @brief ZigBee 3.0 ota server test harness functionality
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

#include "test-harness-z3-core.h"
#include "app/framework/plugin/ota-server/ota-server.h"
#include "app/framework/plugin/ota-storage-common/ota-storage.h"
// -----------------------------------------------------------------------------
extern void emberAfSetNoReplyForNextMessage(bool set);
#ifndef EZSP_HOST
static EmberAfOtaImageId loadedOtaImageId = {
  INVALID_MANUFACTURER_ID,
  INVALID_DEVICE_ID,
  INVALID_FIRMWARE_VERSION,
  INVALID_EUI64,
};
static EmberAfOtaHeader loadedOTAFileHeader = {
  // Magic Number omitted since it is always the same.
  .headerVersion = 0x0100,
  .headerLength  = 0x0038,
  .fieldControl  = 0x0000,
  .manufacturerId = 0xffff,
  .imageTypeId    = 0xffff,           // a.k.a. Device ID
  .firmwareVersion = 0xffffffff,
  .zigbeeStackVersion = 0x0002,

  /**
   * @brief The spec. does NOT require that the string be NULL terminated in the
   *   header stored on disk.  Therefore we make sure we can support a
   *   32-character string without a NULL terminator by adding +1 in the data
   *   structure.
   */
  //.headerString[EMBER_AF_OTA_MAX_HEADER_STRING_LENGTH + 1] = {0},

  /**
   * @brief When reading the header this will be the complete length of
   *  the file. When writing the header, this must be set to
   *  the length of the MFG image data portion including all tags.
   */
  .imageSize = 0,

  /**
   * @brief The remaining four fields are optional. The field control should be checked
   *   to determine if their values are valid.
   */
  .securityCredentials = 0,
  .upgradeFileDestination = { 0xff },
  .minimumHardwareVersion = 0,
  .maximumHardwareVersion = 0
};
#endif
// OTA Server commands
// plugin test-harness z3 ota-server activate <shortAddress:2> <endpoint:1> <manufacturereCode:2> <imageType:2> <fileVersion:4> <fileSize:4>
//static EmberAfOtaImageId otaImageId;
void sli_zigbee_af_test_harness_z3_ota_server_activate_command(SL_CLI_COMMAND_ARG)
{
  EmberStatus status = EMBER_INVALID_CALL;
#ifndef EZSP_HOST
  EmberNodeId shortAddress = sl_cli_get_argument_uint16(arguments, 0);
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 1);
  loadedOTAFileHeader.manufacturerId = sl_cli_get_argument_uint16(arguments, 2);
  loadedOTAFileHeader.imageTypeId = sl_cli_get_argument_uint16(arguments, 3);
  loadedOTAFileHeader.firmwareVersion = sl_cli_get_argument_uint32(arguments, 4);
  loadedOTAFileHeader.imageSize = sl_cli_get_argument_uint32(arguments, 5);

  loadedOtaImageId.manufacturerId = loadedOTAFileHeader.manufacturerId;
  loadedOtaImageId.imageTypeId = loadedOTAFileHeader.imageTypeId;
  loadedOtaImageId.firmwareVersion = loadedOTAFileHeader.firmwareVersion;

  status = emberAfOtaServerSendImageNotifyCallback(shortAddress,
                                                   endpoint,
                                                   0x03,//payloadType,
                                                   60,//jitter,
                                                   &loadedOtaImageId);

#endif /* EZSP_HOST */
  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Ota Server activate",
                     status);
}

// plugin test-harness z3 ota-server deactivate
void sli_zigbee_af_test_harness_z3_ota_server_de_activate_command(SL_CLI_COMMAND_ARG)
{
  EmberStatus status = EMBER_INVALID_CALL;
#ifndef EZSP_HOST
  EmberAfOtaImageId InvalidId = {
    INVALID_MANUFACTURER_ID,
    INVALID_DEVICE_ID,
    INVALID_FIRMWARE_VERSION,
    INVALID_EUI64,
  };
  loadedOtaImageId = InvalidId;
  status = EMBER_SUCCESS;
#endif /* EZSP_HOST */

  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Ota Server Deactivate",
                     status);
}
