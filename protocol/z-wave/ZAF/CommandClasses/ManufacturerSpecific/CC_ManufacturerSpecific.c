/**
 * @file
 * Handler for Command Class Manufacturer Specific.
 * @copyright 2022 Silicon Laboratories Inc.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#include "ZAF_types.h"
#include "ZW_TransportEndpoint.h"
#include "zaf_config_api.h"
#include "zpal_misc.h"

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

#define DEVICE_ID_TYPE_SERIAL_NUMBER 1
#define DEVICE_ID_DATA_FORMAT_BINARY 1

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

// Nothing here.

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

// Nothing here.

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/

static received_frame_status_t
CC_ManufacturerSpecific_handler(
    RECEIVE_OPTIONS_TYPE_EX *rxOpt,
    ZW_APPLICATION_TX_BUFFER *pFrameIn,
    __attribute__((unused)) uint8_t cmdLength,
    ZW_APPLICATION_TX_BUFFER * pFrameOut,
    uint8_t * pLengthOut
)
{
  if (true == Check_not_legal_response_job(rxOpt))
  {
    // None of the following commands support endpoint bit addressing.
    return RECEIVED_FRAME_STATUS_FAIL;
  }

  switch(pFrameIn->ZW_Common.cmd)
  {
    case MANUFACTURER_SPECIFIC_GET_V2:
      pFrameOut->ZW_ManufacturerSpecificReportV2Frame.cmdClass = COMMAND_CLASS_MANUFACTURER_SPECIFIC_V2;
      pFrameOut->ZW_ManufacturerSpecificReportV2Frame.cmd      = MANUFACTURER_SPECIFIC_REPORT_V2;

      uint16_t manufacturerID = zaf_config_get_manufacturer_id();
      uint16_t productID      = zaf_config_get_product_id();
      uint16_t productTypeID  = zaf_config_get_product_type_id();

      pFrameOut->ZW_ManufacturerSpecificReportV2Frame.manufacturerId1 = (uint8_t)(manufacturerID >> 8);
      pFrameOut->ZW_ManufacturerSpecificReportV2Frame.manufacturerId2 = (uint8_t)(manufacturerID &  0xFF);
      pFrameOut->ZW_ManufacturerSpecificReportV2Frame.productTypeId1  = (uint8_t)(productTypeID  >> 8);
      pFrameOut->ZW_ManufacturerSpecificReportV2Frame.productTypeId2  = (uint8_t)(productTypeID  &  0xFF);
      pFrameOut->ZW_ManufacturerSpecificReportV2Frame.productId1      = (uint8_t)(productID      >> 8);
      pFrameOut->ZW_ManufacturerSpecificReportV2Frame.productId2      = (uint8_t)(productID      &  0xFF);

      *pLengthOut = (uint8_t)sizeof(ZW_MANUFACTURER_SPECIFIC_REPORT_V2_FRAME);

      return RECEIVED_FRAME_STATUS_SUCCESS;
    case DEVICE_SPECIFIC_GET_V2:
      pFrameOut->ZW_DeviceSpecificReport1byteV2Frame.cmdClass = COMMAND_CLASS_MANUFACTURER_SPECIFIC_V2;
      pFrameOut->ZW_DeviceSpecificReport1byteV2Frame.cmd      = DEVICE_SPECIFIC_REPORT_V2;

      uint8_t deviceIDType       = DEVICE_ID_TYPE_SERIAL_NUMBER;
      uint8_t deviceIDDataFormat = DEVICE_ID_DATA_FORMAT_BINARY;
      uint8_t deviceIDDataLength = (uint8_t)zpal_get_serial_number_length();
      zpal_get_serial_number(&pFrameOut->ZW_DeviceSpecificReport1byteV2Frame.deviceIdData1);

      pFrameOut->ZW_DeviceSpecificReport1byteV2Frame.properties1 = deviceIDType & 0x07;
      pFrameOut->ZW_DeviceSpecificReport1byteV2Frame.properties2 = (uint8_t)(deviceIDDataFormat << 5) & 0xE0;
      uint8_t length_masked = deviceIDDataLength & 0x1F; // Silence conversion warning with separate line.
      pFrameOut->ZW_DeviceSpecificReport1byteV2Frame.properties2 |= length_masked;

      *pLengthOut = sizeof(ZW_DEVICE_SPECIFIC_REPORT_1BYTE_V2_FRAME) + (pFrameOut->ZW_DeviceSpecificReport1byteV2Frame.properties2 & 0x1F) - 1;
      return RECEIVED_FRAME_STATUS_SUCCESS;
    default:
      return RECEIVED_FRAME_STATUS_NO_SUPPORT;
  }
}

REGISTER_CC_V2(COMMAND_CLASS_MANUFACTURER_SPECIFIC, MANUFACTURER_SPECIFIC_VERSION_V2, CC_ManufacturerSpecific_handler);
