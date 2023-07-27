/***************************************************************************//**
 * @file
 * @brief Routines for the ZLL Identify Server plugin, which contains additions
 *        to the Identify server cluster.
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

// this file contains all the common includes for clusters in the util
#include "app/framework/include/af.h"
#include "app/framework/util/common.h"
#include "zll-identify-server-config.h"
#include "zap-cluster-command-parser.h"

#ifndef EZSP_HOST
#include "hal/hal.h"
#endif

typedef struct {
  bool active;
  bool cancel;
  EmberAfIdentifyEffectIdentifier effectId;
  EmberAfIdentifyEffectVariant commandVariant;
  uint8_t eventsRemaining;
  uint16_t eventDelay;
} sli_zigbee_af_zll_identify_state;

void sli_zigbee_af_zll_identify_server_blink_effect(uint8_t endpoint);

void sli_zigbee_af_zll_identify_server_breathe_effect(uint8_t endpoint);

void sli_zigbee_af_zll_identify_server_okay_effect(uint8_t endpoint);

void sli_zigbee_af_zll_identify_server_channel_change_effect(uint8_t endpoint);

static sl_zigbee_event_t triggerEffectEndpointEvents[FIXED_ENDPOINT_COUNT];

static sli_zigbee_af_zll_identify_state stateTable[EMBER_AF_IDENTIFY_CLUSTER_SERVER_ENDPOINT_COUNT];

static sli_zigbee_af_zll_identify_state *getZllIdentifyState(uint8_t endpoint);

static void deactivateZllIdentify(sli_zigbee_af_zll_identify_state *state, uint8_t endpoint);

static sli_zigbee_af_zll_identify_state *getZllIdentifyState(uint8_t endpoint)
{
  uint8_t index = emberAfFindClusterServerEndpointIndex(endpoint, ZCL_IDENTIFY_CLUSTER_ID);
  return (index == 0xFF ? NULL : &stateTable[index]);
}

static void deactivateZllIdentify(sli_zigbee_af_zll_identify_state *state, uint8_t endpoint)
{
  if (state == NULL) {
    return;
  }

  state->active = false;
  state->cancel = false;

  sl_zigbee_endpoint_event_set_inactive(triggerEffectEndpointEvents, endpoint);
}

static void triggerEffectEndpointEventHandler(uint8_t endpoint)
{
  sli_zigbee_af_zll_identify_state *state = getZllIdentifyState(endpoint);

  if (state == NULL) {
    return;
  }

  switch (state->effectId) {
    case EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_BLINK:
      sli_zigbee_af_zll_identify_server_blink_effect(endpoint);
      break;
    case EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_BREATHE:
      sli_zigbee_af_zll_identify_server_breathe_effect(endpoint);
      break;
    case EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_OKAY:
      sli_zigbee_af_zll_identify_server_okay_effect(endpoint);
      break;
    case EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_CHANNEL_CHANGE:
      sli_zigbee_af_zll_identify_server_channel_change_effect(endpoint);
      break;
    case EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_FINISH_EFFECT: // At this point, these are functionally equivalent
    case EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_STOP_EFFECT:
    default:
      deactivateZllIdentify(state, endpoint);
      return;
  }
  if (state->cancel) {
    deactivateZllIdentify(state, endpoint);
    return;
  }

  if (state->active) {
    sl_zigbee_endpoint_event_set_delay_ms(triggerEffectEndpointEvents,
                                          endpoint,
                                          state->eventDelay);
  }
}

void sli_zigbee_af_zll_identify_server_init_callback(uint8_t init_level)
{
  (void)init_level;

  uint8_t endpoint_array[FIXED_ENDPOINT_COUNT] = FIXED_ENDPOINT_ARRAY;
  uint8_t i;

  for (i = 0; i < FIXED_ENDPOINT_COUNT; i++) {
    sl_zigbee_endpoint_event_init(&triggerEffectEndpointEvents[i],
                                  triggerEffectEndpointEventHandler,
                                  endpoint_array[i]);
  }
}

bool emberAfIdentifyClusterTriggerEffectCallback(EmberAfClusterCommand *cmd)
{
  sl_zcl_identify_cluster_trigger_effect_command_t cmd_data;
  uint8_t endpoint = emberAfCurrentEndpoint();
  sli_zigbee_af_zll_identify_state *state = getZllIdentifyState(endpoint);

  EmberAfStatus status = zcl_decode_identify_cluster_trigger_effect_command(cmd, &cmd_data);

  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    goto default_response;
  }

  if (state == NULL) {
    status = EMBER_ZCL_STATUS_FAILURE;
    goto default_response;
  }

  emberAfIdentifyClusterPrintln("RX identify:trigger effect 0x%x variant 0x%x", cmd_data.effectId, cmd_data.effectVariant);

  if (state->active) {
    switch (state->effectId) {
      case EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_FINISH_EFFECT:
        state->cancel = true;
        status = EMBER_ZCL_STATUS_SUCCESS;
        break;
      case EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_STOP_EFFECT:
        deactivateZllIdentify(state, endpoint);
        status = EMBER_ZCL_STATUS_SUCCESS;
        goto default_response;
      default:
        status = EMBER_ZCL_STATUS_FAILURE;
        break;
    }
  } else {
    switch (cmd_data.effectId) {
      case EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_BLINK:
        state->eventsRemaining = EMBER_AF_PLUGIN_ZLL_IDENTIFY_SERVER_BLINK_EVENTS;
        break;
      case EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_BREATHE:
        state->eventsRemaining = EMBER_AF_PLUGIN_ZLL_IDENTIFY_SERVER_BREATHE_EVENTS;
        break;
      case EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_OKAY:
        state->eventsRemaining = EMBER_AF_PLUGIN_ZLL_IDENTIFY_SERVER_OKAY_EVENTS;
        break;
      case EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_CHANNEL_CHANGE:
        state->eventsRemaining = EMBER_AF_PLUGIN_ZLL_IDENTIFY_SERVER_CHANNEL_CHANGE_EVENTS;
        break;
      case EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_FINISH_EFFECT: // At this point, these are functionally equivalent
      case EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_STOP_EFFECT:
        status = EMBER_ZCL_STATUS_SUCCESS;
        goto default_response;
      default:
        status = EMBER_ZCL_STATUS_FAILURE;
        goto default_response;
    }
    state->active = true;
    state->cancel = false;
    state->effectId = (EmberAfIdentifyEffectIdentifier)cmd_data.effectId;
    state->commandVariant = (EmberAfIdentifyEffectVariant)cmd_data.effectVariant;
    state->eventDelay = EMBER_AF_PLUGIN_ZLL_IDENTIFY_SERVER_EVENT_DELAY;
    sl_zigbee_endpoint_event_set_delay_ms(triggerEffectEndpointEvents,
                                          endpoint,
                                          state->eventDelay);
    status = EMBER_ZCL_STATUS_SUCCESS;
  }

  default_response:
  emberAfSendImmediateDefaultResponse(status);
  return true;
}

void sli_zigbee_af_zll_identify_server_blink_effect(uint8_t endpoint)
{
  sli_zigbee_af_zll_identify_state *state = getZllIdentifyState(endpoint);

  if (state == NULL || state->eventsRemaining == 0) {
    deactivateZllIdentify(state, endpoint);
    return;
  }

#ifndef EZSP_HOST
  halToggleLed(BOARDLED0);
  halToggleLed(BOARDLED1);
  halToggleLed(BOARDLED2);
  halToggleLed(BOARDLED3);
#endif

  state->eventsRemaining = state->eventsRemaining - 1;
}

void sli_zigbee_af_zll_identify_server_breathe_effect(uint8_t endpoint)
{
  sli_zigbee_af_zll_identify_server_blink_effect(endpoint);
}

void sli_zigbee_af_zll_identify_server_okay_effect(uint8_t endpoint)
{
  sli_zigbee_af_zll_identify_server_blink_effect(endpoint);
}

void sli_zigbee_af_zll_identify_server_channel_change_effect(uint8_t endpoint)
{
  sli_zigbee_af_zll_identify_server_blink_effect(endpoint);
}

uint32_t emberAfZllIdentifyClusterServerCommandParse(sl_service_opcode_t opcode,
                                                     sl_service_function_context_t *context)
{
  (void)opcode;
  bool wasHandled = false;
  EmberAfClusterCommand *cmd = (EmberAfClusterCommand *)context->data;
  if (!cmd->mfgSpecific) {
    if (cmd->commandId == ZCL_TRIGGER_EFFECT_COMMAND_ID) {
      wasHandled = emberAfIdentifyClusterTriggerEffectCallback(cmd);
    }
  }

  return ((wasHandled)
          ? EMBER_ZCL_STATUS_SUCCESS
          : EMBER_ZCL_STATUS_UNSUP_COMMAND);
}
