/***************************************************************************//**
 * @file
 * @brief Dispatching 802.15.4 scan results to interested parties.
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

#include "scan-dispatch.h"

// -----------------------------------------------------------------------------
// Global variables

static sl_zigbee_event_t scanNetworkEvents[EMBER_SUPPORTED_NETWORKS];
static void scanNetworkEventHandler(sl_zigbee_event_t * event);

// -----------------------------------------------------------------------------
// Internal implementation elements

static uint8_t head = 0;
static uint8_t tail = 0;
static uint8_t count = 0;
static EmberAfPluginScanDispatchScanData handlerQueue[EMBER_AF_PLUGIN_SCAN_DISPATCH_SCAN_QUEUE_SIZE];
#define handlerQueueIsEmpty() (!count)
#define handlerQueueIsFull()  (count == EMBER_AF_PLUGIN_SCAN_DISPATCH_SCAN_QUEUE_SIZE)

// We save 12 bytes of text by having this as a function.
static uint8_t handlerQueueNextIndex(uint8_t i)
{
  return (++i % EMBER_AF_PLUGIN_SCAN_DISPATCH_SCAN_QUEUE_SIZE);
}

static void maybeCallNextHandler(uint8_t statusOrRssi,
                                 uint8_t channelOrLqi,
                                 EmberNetworkScanType scanType,
                                 bool isComplete,
                                 bool isFailure,
                                 EmberZigbeeNetwork *network)
{
  if (!handlerQueueIsEmpty()) {
    EmberAfPluginScanDispatchScanResults results = {
      .status = statusOrRssi,
      .rssi = statusOrRssi,
      .channel = channelOrLqi,
      .lqi = channelOrLqi,
      .network = network,
      .mask = (scanType
               | (isComplete
                  ? EM_AF_PLUGIN_SCAN_DISPATCH_SCAN_RESULTS_MASK_COMPLETE
                  : 0)
               | (isFailure
                  ? EM_AF_PLUGIN_SCAN_DISPATCH_SCAN_RESULTS_MASK_FAILURE
                  : 0)),
    };
    handlerQueue[head].handler(&results);
  }
}

// -----------------------------------------------------------------------------
// Public API

EmberStatus emberAfPluginScanDispatchScheduleScan(EmberAfPluginScanDispatchScanData *data)
{
  EmberStatus status = EMBER_ERR_FATAL;

  if (!handlerQueueIsFull()) {
    handlerQueue[tail] = *data;
    tail = handlerQueueNextIndex(tail);
    count++;
    status = EMBER_SUCCESS;
    sl_zigbee_event_set_active(scanNetworkEvents);
  }

  return status;
}

void emberAfPluginScanDispatchClear(void)
{
  emberStopScan();
  head = tail = count = 0;
}

// -----------------------------------------------------------------------------
// Internal and public callbacks

void sli_zigbee_af_scan_dispatch_init_callback(uint8_t init_level)
{
  (void)init_level;

  sl_zigbee_network_event_init(scanNetworkEvents,
                               scanNetworkEventHandler);
}

static void scanNetworkEventHandler(sl_zigbee_event_t * event)
{
  sl_status_t status;

  sl_zigbee_event_set_inactive(scanNetworkEvents);

  // If there is a handler in the queue, start a scan for it.
  // If we are already scanning, we should try again.
  // If there is an error, we abort the scan and tell the consumer.
  if (!handlerQueueIsEmpty()) {
    status = emberStartScan(handlerQueue[head].scanType,
                            handlerQueue[head].channelMask,
                            handlerQueue[head].duration);

    if (status != SL_STATUS_MAC_SCANNING) {
      if (status != SL_STATUS_OK) {
        maybeCallNextHandler(status,
                             0,     // channel. 0 indicating that the actual scan was not started
                             handlerQueue[head].scanType,
                             true,     // complete?
                             true,     // failure?
                             NULL);     // network
        head = handlerQueueNextIndex(head);
        count--;
        sl_zigbee_event_set_active(scanNetworkEvents);
      }
    }
  }
}

void sli_zigbee_af_scan_dispatch_energy_scan_result_callback(uint8_t channel, int8_t rssi)
{
  maybeCallNextHandler((uint8_t)rssi,
                       channel,
                       EMBER_ENERGY_SCAN,
                       false,     // complete?
                       false,     // failure?
                       NULL);     // network
}

void sli_zigbee_af_scan_dispatch_network_found_callback(EmberZigbeeNetwork *networkFound,
                                                        uint8_t lqi,
                                                        int8_t rssi)
{
  maybeCallNextHandler((uint8_t)rssi,
                       lqi,
                       EMBER_ACTIVE_SCAN,
                       false,     // complete?
                       false,     // failure?
                       networkFound);
}

void sli_zigbee_af_scan_dispatch_scan_complete_callback(uint8_t channel, EmberStatus status)
{
  maybeCallNextHandler(status,
                       channel,
                       handlerQueue[head].scanType,
                       true,     // complete?
                       false,     // failure?
                       NULL);     // network

  // The scan is done when the status is set to EMBER_SUCCESS.
  // See documentation for the emberScanCompleteHandler callback.
  // For Active scan we call the EMBER_ACTIVE_SCAN_XX anyways,
  // beacuse of the change in network-steering code which
  // continues to schedule a scan on the next channel after a failure
  if ((status == EMBER_SUCCESS) && !handlerQueueIsEmpty()) {
    head = handlerQueueNextIndex(head);
    count--;
    sl_zigbee_event_set_active(scanNetworkEvents);
  }
}
