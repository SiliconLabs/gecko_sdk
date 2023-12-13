/**
 * @file
 *
 * @copyright 2023 Silicon Laboratories Inc.
 */

#include <string.h>
#include "zaf_transport_config.h"
#include "zaf_transport_tx.h"
#include "ZW_TransportMulticast.h"
#include "ZW_TransportSecProtocol.h"
#include "ZAF_Common_interface.h"
#include "misc.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "association_plus_base.h"
//#define DEBUGPRINT
#include "DebugPrint.h"
#include "DebugPrintConfig.h"

typedef struct {
  zaf_tx_callback_t callback;
  ZW_APPLICATION_TX_BUFFER frame;
  zaf_tx_options_t zaf_tx_options;
  uint8_t frame_length;
} transport_queue_item_t;

#define ZAF_TRANSPORT_QUEUE_ITEM_SIZE sizeof(transport_queue_item_t)

static bool transport_busy;
static bool transport_queue_paused;
static StaticQueue_t transport_queue = { 0 };
static uint8_t transport_queue_buffer[ZAF_TRANSPORT_CONFIG_QUEUE_SIZE * ZAF_TRANSPORT_QUEUE_ITEM_SIZE];
static QueueHandle_t transport_queue_handle = { 0 };
static zaf_tx_callback_t transport_pending_callback;

static void transport_tx(void);

static void
transport_callback(transmission_result_t * transmission_result)
{
  DPRINTF("Transport callback: Status:%d Finished:%d\n",
          transmission_result->status, transmission_result->isFinished);

  if (transmission_result->isFinished != TRANSMISSION_RESULT_NOT_FINISHED) {
    /* Handle callback before transmitting again */
    if (transport_pending_callback) {
      transport_pending_callback(transmission_result);
    }

    /* Maybe a pause request came in while a tranmission is happening */
    if (!transport_queue_paused) {
      transport_tx();
    } else {
      transport_busy = false;
    }
  }
}

static void
transport_tx_failed(node_id_t node_id)
{
  transmission_result_t transmission_result = {
    .nodeId = node_id,
    .status = TRANSMIT_COMPLETE_FAIL,
    .isFinished = TRANSMISSION_RESULT_FINISHED
  };
  transport_callback(&transmission_result);
}

static void
transport_tx(void)
{
  transport_queue_item_t queue_item = { 0 };
  TRANSMIT_OPTIONS_TYPE_EX *tx_options_ex;
  TRANSMIT_OPTIONS_TYPE_SINGLE_EX tx_options_single_ex = { 0 };
  MULTICHAN_NODE_ID node_id = { 0 };

  if (xQueueReceive(transport_queue_handle, &queue_item, 0) == pdPASS) {
    DPRINT("Transmitting frame\n");
    transport_busy = true;

    transport_pending_callback = queue_item.callback;
    if (queue_item.zaf_tx_options.dest_node_id) {
      /* Setup tx_options_ex like ReqNodeList does */
      if (queue_item.zaf_tx_options.use_supervision) {
        tx_options_single_ex.txSecOptions = S2_TXOPTION_VERIFY_DELIVERY;
      } else {
        tx_options_single_ex.txSecOptions = 0;
      }
      tx_options_single_ex.txOptions = queue_item.zaf_tx_options.tx_options;
      tx_options_single_ex.sourceEndpoint = queue_item.zaf_tx_options.source_endpoint;
      tx_options_single_ex.pDestNode = &node_id;

      /* Setup destination node information */
      node_id.node.nodeId = queue_item.zaf_tx_options.dest_node_id;
      node_id.node.BitAddress = queue_item.zaf_tx_options.bit_addressing;
      node_id.node.endpoint = queue_item.zaf_tx_options.dest_endpoint & 0x7FU;
      node_id.nodeInfo.BitMultiChannelEncap = (queue_item.zaf_tx_options.source_endpoint) ? true : false;
      node_id.nodeInfo.security = queue_item.zaf_tx_options.security_key;

      if (ZAF_Transmit((uint8_t *) &queue_item.frame,
                       queue_item.frame_length,
                       &tx_options_single_ex,
                       transport_callback) != ZAF_ENQUEUE_STATUS_SUCCESS) {
        transport_tx_failed(queue_item.zaf_tx_options.dest_node_id);
      }
    } else {
      /* Get transmit options (node list) */
      tx_options_ex = ReqNodeList(queue_item.zaf_tx_options.agi_profile,
                                  (cc_group_t *)&queue_item.frame,
                                  queue_item.zaf_tx_options.source_endpoint);
      if (!tx_options_ex || ZW_TransportMulticast_SendRequest(
            (uint8_t *) &queue_item.frame,
            queue_item.frame_length,
            queue_item.zaf_tx_options.use_supervision,
            tx_options_ex,
            transport_callback) != ETRANSPORTMULTICAST_ADDED_TO_QUEUE) {
        transport_tx_failed(queue_item.zaf_tx_options.dest_node_id);
      }
    }
  } else {
    DPRINT("No more frames to transmit\n");
    transport_busy = false;
  }
}

bool
zaf_transport_tx(const uint8_t *frame, uint8_t frame_length,
                 zaf_tx_callback_t callback, zaf_tx_options_t *zaf_tx_options)
{
  BaseType_t ret;
  transport_queue_item_t queue_item = {
    .callback = callback,
    .frame_length = frame_length
  };
  memcpy(&queue_item.frame, frame, frame_length);
  memcpy(&queue_item.zaf_tx_options, zaf_tx_options, sizeof(zaf_tx_options_t));

  DPRINT("Adding new frame to queue\n");
  ret = xQueueSend(transport_queue_handle, &queue_item, 0);
  if (ret == pdFAIL) {
    DPRINT("Failed to add new frame to queue\n");
    return false;
  }

  if (!transport_busy && !transport_queue_paused) {
    transport_tx();
  }

  return true;
}

void
zaf_transport_init(void)
{
  transport_busy = false;
  transport_queue_paused = false;
  memset(transport_queue_buffer, 0, sizeof(transport_queue_buffer));
  transport_queue_handle = xQueueCreateStatic(ZAF_TRANSPORT_CONFIG_QUEUE_SIZE,
                                              ZAF_TRANSPORT_QUEUE_ITEM_SIZE,
                                              transport_queue_buffer,
                                              &transport_queue);
  DPRINT("zaf transport init\n");
}

void
zaf_transport_resume(void)
{
  DPRINTF("zaf transport resumed %d\n", transport_busy);
  transport_queue_paused = false;
  if (!transport_busy) {
    transport_tx();
  }
}

void
zaf_transport_pause(void)
{
  DPRINTF("zaf transport paused %d\n", transport_busy);
  transport_queue_paused = true;
}

void
zaf_transport_rx_to_tx_options(RECEIVE_OPTIONS_TYPE_EX *rx_options,
                               zaf_tx_options_t* tx_options)
{
  tx_options->dest_node_id = rx_options->sourceNode.nodeId;
  tx_options->dest_endpoint = rx_options->sourceNode.endpoint;
  tx_options->bit_addressing = rx_options->sourceNode.endpoint != 0;
  tx_options->security_key = rx_options->securityKey;

  tx_options->tx_options = TRANSMIT_OPTION_ACK | TRANSMIT_OPTION_EXPLORE | ZWAVE_PLUS_TX_OPTIONS;
  if (rx_options->rxStatus & RECEIVE_STATUS_LOW_POWER) {
    tx_options->tx_options |= TRANSMIT_OPTION_LOW_POWER;
  }
  tx_options->source_endpoint = rx_options->destNode.endpoint;
  tx_options->use_supervision = false;
}
