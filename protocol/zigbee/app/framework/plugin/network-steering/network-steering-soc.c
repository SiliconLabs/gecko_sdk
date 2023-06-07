/***************************************************************************//**
 * @file
 * @brief SoC routines for the Network Steering plugin.
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
#include "network-steering.h"
#include "network-steering-internal.h"

//============================================================================
// Globals

static EmberMessageBuffer storedNetworks = EMBER_NULL_MESSAGE_BUFFER;

#define MAX_NETWORKS (PACKET_BUFFER_SIZE >> 1)  // 16

#define NULL_PAN_ID 0xFFFF

#define PLUGIN_NAME sli_zigbee_af_network_steering_plugin_name

//============================================================================
// Forward Declarations

//============================================================================

uint8_t sli_zigbee_af_network_steering_get_max_possible_pan_ids(void)
{
  return MAX_NETWORKS;
}

void sli_zigbee_af_network_steering_clear_stored_pan_ids(void)
{
  if (storedNetworks != EMBER_NULL_MESSAGE_BUFFER) {
    emberReleaseMessageBuffer(storedNetworks);
    storedNetworks = EMBER_NULL_MESSAGE_BUFFER;
  }
}

uint16_t* sli_zigbee_af_network_steering_get_stored_pan_id_pointer(uint8_t index)
{
  if (index >= MAX_NETWORKS) {
    return NULL;
  }

  if (storedNetworks == EMBER_NULL_MESSAGE_BUFFER) {
    storedNetworks = sli_legacy_buffer_manager_allocate_buffer(PACKET_BUFFER_SIZE);
    if (storedNetworks == EMBER_NULL_MESSAGE_BUFFER) {
      emberAfCorePrintln("Error: %p failed to allocate stack buffer.", PLUGIN_NAME);
      return NULL;
    }
    MEMSET(emberMessageBufferContents(storedNetworks), 0xFF, PACKET_BUFFER_SIZE);
  }

  return (uint16_t*)(emberMessageBufferContents(storedNetworks) + (index * sizeof(uint16_t)));
}

void emberAfPluginNetworkSteeringMarker(void)
{
  sli_legacy_buffer_manager_mark_buffer(&storedNetworks);
}
