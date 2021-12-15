/***************************************************************************//**
 * @file
 * @brief Code for multi-network support.
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

#include PLATFORM_HEADER
#include "buffer_manager/buffer-management.h"
#include "stack/core/ember-stack.h"
#include "mac-types.h"
#include "mac-multi-network.h"
#include "lower-mac.h"
#include "upper-mac.h"

#ifndef EMBER_MULTI_NETWORK_STRIPPED
// Network Index to be used by the stack when certain stack calls are made by the mac.
// This value should be set to the desired index and back to 0xFF once the operation is complete.
uint8_t sl_mac_nwk_index_for_stack = 0xFF;
#endif

// Polling queue
uint8_t sl_mac_network_poll_queue[SL_MAC_MAX_SUPPORTED_NETWORKS]; // initialized in upper-mac

//------------------------------------------------------------------------------
// Multi-network polling queuing system.
//------------------------------------------------------------------------------
static uint8_t pollQueueHead = 0;

void sl_mac_add_current_network_to_polling_queue(uint8_t nwk_index)
{
  uint8_t i;
  for (i = 0; i < SL_MAC_MAX_SUPPORTED_NETWORKS; i++) {
    uint8_t index = (pollQueueHead + i) % SL_MAC_MAX_SUPPORTED_NETWORKS;

    // This network is already scheduled for polling, don't schedule it again.
    if (sl_mac_network_poll_queue[index] == NWK_INDEX) {
      break;
    }

    // Write the network index in the first empty position
    if (sl_mac_network_poll_queue[index] == 0xFF) {
      sl_mac_network_poll_queue[index] = NWK_INDEX;
      break;
    }
  }
}

uint8_t sl_mac_dequeue_polling_network(void)
{
  uint8_t pollingNetwork = sl_mac_network_poll_queue[pollQueueHead];
  assert(pollingNetwork < SL_MAC_MAX_SUPPORTED_NETWORKS);

  sl_mac_network_poll_queue[pollQueueHead] = 0xFF;
  pollQueueHead = (pollQueueHead + 1) % SL_MAC_MAX_SUPPORTED_NETWORKS;

  return pollingNetwork;
}

bool sl_mac_multi_network_poll_pending(void)
{
  return (sl_mac_network_poll_queue[pollQueueHead] != 0xFF);
}
