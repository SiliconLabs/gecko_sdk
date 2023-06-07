/***************************************************************************//**
 * @file
 * @brief Routines for the MN Price Passthrough plugin, which handles
 *        demonstrates client and server Price cluster passthrough on a multi-
 *        network device.
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
#include "app/framework/util/common.h"
#include "mn-price-passthrough.h"
#include "app/framework/plugin/price-common/price-common.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#include "mn-price-passthrough-config.h"
#include "zap-cluster-command-parser.h"
#ifdef SL_CATALOG_ZIGBEE_TEST_HARNESS_PRESENT
#include "test-harness.h"
#endif

#define VALID  BIT(1)

static EmberNodeId forwardingId;
static uint8_t forwardingEndpoint, proxyEsiEndpoint;
static EmberAfScheduledPrice currentPrice;

sl_zigbee_event_t emberAfPluginMnPricePassthroughPollAndForwardEsiEvent;
#define pollAndForwardEsiEventControl (&emberAfPluginMnPricePassthroughPollAndForwardEsiEvent)
void emberAfPluginMnPricePassthroughPollAndForwardEsiEventHandler(sl_zigbee_event_t * event);

static void fillPublishPriceCommand(EmberAfScheduledPrice price)
{
  char * const args[] = { "wswwuvuuwvwuwu", "wswwuvuuwvwuwuwuuuu", "wswwuvuuwvwuwuwuuuuuuuuu" };
  UNUSED_VAR(args);
  (void) emberAfFillExternalBuffer(ZCL_CLUSTER_SPECIFIC_COMMAND | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT
                                   | EMBER_AF_DEFAULT_RESPONSE_POLICY_RESPONSES,
                                   ZCL_PRICE_CLUSTER_ID,
                                   ZCL_PUBLISH_PRICE_COMMAND_ID,
    #if defined(SL_CATALOG_ZIGBEE_TEST_HARNESS_PRESENT)
                                   args[sendSE11PublishPriceCommand],
    #else // EMBER_AF_SE12.
                                   "wswwuvuuwvwuwuwuuuuuuuuu",
    #endif
                                   price.providerId,
                                   price.rateLabel,
                                   price.issuerEventID,
                                   emberAfGetCurrentTime(),
                                   price.unitOfMeasure,
                                   price.currency,
                                   price.priceTrailingDigitAndTier,
                                   price.numberOfPriceTiersAndTier,
                                   price.startTime,
                                   price.duration,
                                   price.price,
                                   price.priceRatio,
                                   price.generationPrice,
                                   price.generationPriceRatio,
                                   price.alternateCostDelivered,
                                   price.alternateCostUnit,
                                   price.alternateCostTrailingDigit,
                                   price.numberOfBlockThresholds,
                                   price.priceControl,
                                   // TODO: these are optional; if we want to implement, we should!
                                   0, // NumberOfGenerationTiers
                                   0x01, // GenerationTier
                                   0, // ExtendedNumberOfPriceTiers
                                   0, // ExtendedPriceTier
                                   0); // ExtendedRegisterTier
}

void emberAfPluginMnPricePassthroughPollAndForwardEsiEventHandler(sl_zigbee_event_t * event)
{
  EmberStatus status;

  // Ensure that the endpoint for the proxy ESI has been set
  if (forwardingId == EMBER_NULL_NODE_ID
      || forwardingEndpoint == 0xFF
      || proxyEsiEndpoint == 0xFF) {
    emberAfPriceClusterPrintln("Routing parameters not properly established: node %x forwarding %x proxy %x",
                               forwardingId,
                               forwardingEndpoint,
                               proxyEsiEndpoint);
    goto reschedule;
  }

  // Poll the real ESI
  emberAfFillCommandPriceClusterGetCurrentPrice(0x00);
  emberAfSetCommandEndpoints(forwardingEndpoint, proxyEsiEndpoint);
  status = emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, forwardingId);
  if (status != EMBER_SUCCESS) {
    emberAfPriceClusterPrintln("Error in poll and forward event handler %x", status);
  }

  reschedule:
  // Reschedule the event
  sl_zigbee_event_set_delay_minutes(pollAndForwardEsiEventControl,
                                    EMBER_AF_PLUGIN_MN_PRICE_PASSTHROUGH_POLL_RATE);
}

void emberAfPluginMnPricePassthroughInitCallback(uint8_t init_level)
{
  switch (init_level) {
    case SL_ZIGBEE_INIT_LEVEL_EVENT:
    {
      sl_zigbee_event_init(pollAndForwardEsiEventControl,
                           emberAfPluginMnPricePassthroughPollAndForwardEsiEventHandler);
      break;
    }

    case SL_ZIGBEE_INIT_LEVEL_LOCAL_DATA:
    {
      // Initialize the proxy ESI endpoint
      sli_zigbee_af_mn_price_passthrough_routing_setup(EMBER_NULL_NODE_ID, 0xFF, 0xFF);
      break;
    }
  }
}

bool emberAfPriceClusterPublishPriceCallback(EmberAfClusterCommand *cmd)
{
  sl_zcl_price_cluster_publish_price_command_t cmd_data;
  uint8_t endpoint = emberAfCurrentEndpoint();
  uint8_t ep = emberAfFindClusterClientEndpointIndex(endpoint,
                                                     ZCL_PRICE_CLUSTER_ID);
  if ((zcl_decode_price_cluster_publish_price_command(cmd, &cmd_data)
       != EMBER_ZCL_STATUS_SUCCESS)
      || ep == 0xFF) {
    return false;
  }

  emberAfPriceClusterPrint("RX: PublishPrice 0x%4x, \"", cmd_data.providerId);
  emberAfPriceClusterPrintString(cmd_data.rateLabel);
  emberAfPriceClusterPrint("\"");
  emberAfPriceClusterFlush();
  emberAfPriceClusterPrint(", 0x%4x, 0x%4x, 0x%x, 0x%2x, 0x%x, 0x%x, 0x%4x",
                           cmd_data.issuerEventId,
                           cmd_data.currentTime,
                           cmd_data.unitOfMeasure,
                           cmd_data.currency,
                           cmd_data.priceTrailingDigitAndPriceTier,
                           cmd_data.numberOfPriceTiersAndRegisterTier,
                           cmd_data.startTime);
  emberAfPriceClusterFlush();
  emberAfPriceClusterPrint(", 0x%2x, 0x%4x, 0x%x, 0x%4x, 0x%x, 0x%4x, 0x%x",
                           cmd_data.durationInMinutes,
                           cmd_data.price,
                           cmd_data.priceRatio,
                           cmd_data.generationPrice,
                           cmd_data.generationPriceRatio,
                           cmd_data.alternateCostDelivered,
                           cmd_data.alternateCostUnit);
  emberAfPriceClusterFlush();
  emberAfPriceClusterPrintln(", 0x%x, 0x%x, 0x%x",
                             cmd_data.alternateCostTrailingDigit,
                             cmd_data.numberOfBlockThresholds,
                             cmd_data.priceControl);
  emberAfPriceClusterFlush();

  currentPrice.providerId = cmd_data.providerId;
  emberAfCopyString(currentPrice.rateLabel, cmd_data.rateLabel, ZCL_PRICE_CLUSTER_MAXIMUM_RATE_LABEL_LENGTH);
  currentPrice.issuerEventID = cmd_data.issuerEventId;
  currentPrice.startTime = cmd_data.currentTime;
  currentPrice.unitOfMeasure = cmd_data.unitOfMeasure;
  currentPrice.currency = cmd_data.currency;
  currentPrice.priceTrailingDigitAndTier = cmd_data.priceTrailingDigitAndPriceTier;
  currentPrice.numberOfPriceTiersAndTier = cmd_data.numberOfPriceTiersAndRegisterTier;
  currentPrice.startTime = cmd_data.startTime;
  currentPrice.duration = cmd_data.durationInMinutes;
  currentPrice.price = cmd_data.price;
  currentPrice.priceRatio = cmd_data.priceRatio;
  currentPrice.generationPrice = cmd_data.generationPrice;
  currentPrice.generationPriceRatio = cmd_data.generationPriceRatio;
  currentPrice.alternateCostDelivered = cmd_data.alternateCostDelivered;
  currentPrice.alternateCostUnit = cmd_data.alternateCostUnit;
  currentPrice.alternateCostTrailingDigit = cmd_data.alternateCostTrailingDigit;
  currentPrice.numberOfBlockThresholds = cmd_data.numberOfBlockThresholds;
  currentPrice.priceControl = cmd_data.priceControl;
  emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_SUCCESS);
  return true;
}

uint32_t emberAfPriceClusterClientCommandParse(sl_service_opcode_t opcode,
                                               sl_service_function_context_t *context)
{
  (void)opcode;

  EmberAfClusterCommand *cmd = (EmberAfClusterCommand *)context->data;
  bool wasHandled = false;

  if (!cmd->mfgSpecific) {
    switch (cmd->commandId) {
      case ZCL_PUBLISH_PRICE_COMMAND_ID:
      {
        wasHandled = emberAfPriceClusterPublishPriceCallback(cmd);
        break;
      }
    }
  }

  return ((wasHandled)
          ? EMBER_ZCL_STATUS_SUCCESS
          : EMBER_ZCL_STATUS_UNSUP_COMMAND);
}

void sli_zigbee_af_mn_price_passthrough_routing_setup(EmberNodeId fwdId,
                                                      uint8_t fwdEndpoint,
                                                      uint8_t esiEndpoint)
{
  forwardingId = fwdId;
  forwardingEndpoint = fwdEndpoint;
  proxyEsiEndpoint = esiEndpoint;
}

void sli_zigbee_af_mn_price_passthrough_start_poll_and_forward(void)
{
  emberAfPriceClusterPrintln("Starting %p", "poll and forward");
  sl_zigbee_event_set_delay_ms(pollAndForwardEsiEventControl,
                               MILLISECOND_TICKS_PER_SECOND);
}

void sli_zigbee_af_mn_price_passthrough_stop_poll_and_forward(void)
{
  emberAfPriceClusterPrintln("Stopping %p", "poll and forward");
  sl_zigbee_event_set_inactive(pollAndForwardEsiEventControl);
}

bool emberAfPriceClusterGetCurrentPriceCallback(uint8_t commandOptions)
{
  emberAfPriceClusterPrintln("RX: GetCurrentPrice 0x%x", commandOptions);
  if (currentPrice.priceControl & VALID) {
    emberAfPriceClusterPrintln("no valid price to return!");
    emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_NOT_FOUND);
  } else {
    fillPublishPriceCommand(currentPrice);
    emberAfSendResponse();
  }
  return true;
}

void sli_zigbee_af_mn_price_passthrough_print_current_price(void)
{
  emberAfPriceClusterPrintln("Current configured price:");
  emberAfPriceClusterPrintln("  Note: ALL values given in HEX\r\n");

  emberAfPriceClusterPrintln("= CURRENT PRICE =");
  emberAfPriceClusterPrint("  label: ");
  emberAfPriceClusterPrintString(currentPrice.rateLabel);

  emberAfPriceClusterPrint("(%x)\r\n  uom/cur: 0x%x/0x%2x"
                           "\r\n  pid/eid: 0x%4x/0x%4x"
                           "\r\n  ct/st/dur: 0x%4x/0x%4x/",
                           emberAfStringLength(currentPrice.rateLabel),
                           currentPrice.unitOfMeasure,
                           currentPrice.currency,
                           currentPrice.providerId,
                           currentPrice.issuerEventID,
                           emberAfGetCurrentTime(),
                           currentPrice.startTime);
  if (currentPrice.duration == ZCL_PRICE_CLUSTER_DURATION_UNTIL_CHANGED) {
    emberAfPriceClusterPrint("INF");
  } else {
    emberAfPriceClusterPrint("0x%2x", currentPrice.duration);
  }
  emberAfPriceClusterPrintln("\r\n  ptdt/ptrt: 0x%x/0x%x"
                             "\r\n  p/pr: 0x%4x/0x%x"
                             "\r\n  gp/gpr: 0x%4x/0x%x"
                             "\r\n  acd/acu/actd: 0x%4x/0x%x/0x%x",
                             currentPrice.priceTrailingDigitAndTier,
                             currentPrice.numberOfPriceTiersAndTier,
                             currentPrice.price,
                             currentPrice.priceRatio,
                             currentPrice.generationPrice,
                             currentPrice.generationPriceRatio,
                             currentPrice.alternateCostDelivered,
                             currentPrice.alternateCostUnit,
                             currentPrice.alternateCostTrailingDigit);
  emberAfPriceClusterPrintln("  nobt: 0x%x", currentPrice.numberOfBlockThresholds);
  emberAfPriceClusterPrintln("  pc: 0x%x",
                             (currentPrice.priceControl
                              & ZCL_PRICE_CLUSTER_RESERVED_MASK));
  emberAfPriceClusterPrint("  price is valid from time 0x%4x until ",
                           currentPrice.startTime);
  if (currentPrice.duration == ZCL_PRICE_CLUSTER_DURATION_UNTIL_CHANGED) {
    emberAfPriceClusterPrintln("eternity");
  } else {
    emberAfPriceClusterPrintln("0x%4x",
                               (currentPrice.startTime + (currentPrice.duration * 60)));
  }
}
