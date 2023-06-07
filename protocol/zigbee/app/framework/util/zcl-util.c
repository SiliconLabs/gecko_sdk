/***************************************************************************//**
 * @file
 * @brief This file contains ZCL routines used throughout application framework
 * code.
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

#include "../include/af.h"
#include "app/framework/util/util.h"

bool emberAfProcessMessageIntoZclCmd(EmberApsFrame* apsFrame,
                                     EmberIncomingMessageType type,
                                     uint8_t* message,
                                     uint16_t messageLength,
                                     EmberNodeId source,
                                     InterPanHeader* interPanHeader,
                                     EmberAfClusterCommand* returnCmd)
{
  uint8_t minLength = (message[0] & ZCL_MANUFACTURER_SPECIFIC_MASK
                       ? EMBER_AF_ZCL_MANUFACTURER_SPECIFIC_OVERHEAD
                       : EMBER_AF_ZCL_OVERHEAD);

  if (messageLength < minLength) {
    emberAfAppPrintln("%pRX pkt too short: %d < %d", "ERROR: ", messageLength, minLength);
    return false;
  }

  // Populate the cluster command struct for processing.
  returnCmd->apsFrame        = apsFrame;
  returnCmd->type            = type;
  returnCmd->source          = source;
  returnCmd->buffer          = message;
  returnCmd->bufLen          = messageLength;
  returnCmd->clusterSpecific = (message[0] & ZCL_CLUSTER_SPECIFIC_COMMAND);
  returnCmd->mfgSpecific     = (message[0] & ZCL_MANUFACTURER_SPECIFIC_MASK);
  returnCmd->direction       = ((message[0] & ZCL_FRAME_CONTROL_DIRECTION_MASK)
                                ? ZCL_DIRECTION_SERVER_TO_CLIENT
                                : ZCL_DIRECTION_CLIENT_TO_SERVER);
  returnCmd->payloadStartIndex = 1u;
  if (returnCmd->mfgSpecific) {
    returnCmd->mfgCode = emberAfGetInt16u(message, returnCmd->payloadStartIndex, messageLength);
    returnCmd->payloadStartIndex += 2u;
  } else {
    returnCmd->mfgCode = EMBER_AF_NULL_MANUFACTURER_CODE;
  }
  returnCmd->seqNum         = message[returnCmd->payloadStartIndex++];
  returnCmd->commandId      = message[returnCmd->payloadStartIndex++];
  if ( returnCmd->payloadStartIndex > returnCmd->bufLen ) {
    emberAfAppPrintln("%pRX pkt malformed: %d < %d", "ERROR: ", returnCmd->bufLen, returnCmd->payloadStartIndex);
    return false;
  }
  returnCmd->interPanHeader = interPanHeader;
  returnCmd->networkIndex   = emberGetCurrentNetwork();
  return true;
}
