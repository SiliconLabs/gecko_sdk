/***************************************************************************//**
 * @brief Connect Stack callback stubs.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include "stack/include/ember.h"

//------------------------------------------------------------------------------
// Stack handlers weak definitions.

SL_WEAK void emberStackStatusHandler(EmberStatus status)
{
  (void)status;
}

SL_WEAK void emberChildJoinHandler(EmberNodeType nodeType, EmberNodeId nodeId)
{
  (void) nodeType;
  (void) nodeId;
}

SL_WEAK void emberRadioNeedsCalibratingHandler(void)
{
}

SL_WEAK void emberStackIsrHandler(void)
{
}

SL_WEAK bool emberStackIdleHandler(uint32_t *idleTimeMs)
{
  (void)idleTimeMs;

  return true;
}

SL_WEAK void emberMessageSentHandler(EmberStatus status,
                                     EmberOutgoingMessage *message)
{
  (void)status;
  (void)message;
}

SL_WEAK void emberIncomingMessageHandler(EmberIncomingMessage *message)
{
  (void)message;
}

SL_WEAK void emberMacMessageSentHandler(EmberStatus status,
                                        EmberOutgoingMacMessage *message)
{
  (void)status;
  (void)message;
}

SL_WEAK void emberIncomingMacMessageHandler(EmberIncomingMacMessage *message)
{
  (void)message;
}

SL_WEAK void emberIncomingBeaconHandler(EmberPanId panId,
                                        EmberMacAddress *source,
                                        int8_t rssi,
                                        bool permitJoining,
                                        uint8_t beaconFieldsLength,
                                        uint8_t *beaconFields,
                                        uint8_t beaconPayloadLength,
                                        uint8_t *beaconPayload)
{
  (void)panId;
  (void)source;
  (void)rssi;
  (void)permitJoining;
  (void)beaconFieldsLength;
  (void)beaconFields;
  (void)beaconPayloadLength;
  (void)beaconPayload;
}

SL_WEAK void emberActiveScanCompleteHandler(void)
{
}

SL_WEAK void emberEnergyScanCompleteHandler(int8_t mean,
                                            int8_t min,
                                            int8_t max,
                                            uint16_t variance)
{
  (void)mean;
  (void)min;
  (void)max;
  (void)variance;
}

SL_WEAK void emberFrequencyHoppingStartClientCompleteHandler(EmberStatus status)
{
  (void)status;
}

SL_WEAK void emberMarkApplicationBuffersHandler(void)
{
}
