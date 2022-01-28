/***************************************************************************//**
 * @file upper-mac.c
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifdef UNIFIED_MAC_SCRIPTED_TEST
#define EVENT_CONTROL_SYSTEM
#endif
#include "hal/hal.h"
#include "event_control/event.h"
#include "core/ember-stack.h"

#include "buffer_manager/buffer-management.h"
#include "buffer_manager/buffer-queue.h"
#include "buffer_manager/legacy-packet-buffer.h"
#include "mac-types.h"
#include "lower-mac.h"
#include "upper-mac.h"
#include "mac-header.h"
#include "mac-command.h"
#include "mac-child.h"
#include "mac-multi-network.h"
#include "indirect-queue.h"

// On Lynx (MG22), the TX buffer needs to be 32 bit aligned
ALIGNMENT(4)
sl_mac_upper_mac_state_t sl_mac_upper_mac_state[MAX_MAC_INDEX] = { 0 };

#define s sl_mac_upper_mac_state[mac_index]

#define OPTIMIZATION_PREAMBLE() do { \
    mac_index = 0;                   \
} while (0)

static uint8_t mac_outgoing_sequence_number = 0;

// TODO: EMZIGBEE-5606
// These are the zigbee specific stuff in the umac code that
// could be cleaned up in the future.
#ifndef UNIFIED_MAC_SCRIPTED_TEST
uint8_t emGetActiveAlwaysOnNetworkIndex(void);
extern uint8_t emZcAndZrCount;
#endif

// mfglib related external variables
extern uint8_t emMfglibMode;
extern void (*emMfglibRxCallback)(uint8_t *packet, uint8_t linkQuality, int8_t rssi);

// To use either negotiated power by link power delta or fixed power value provided by user
// while forming/joining a network for packet transmissions on subghz interface.
bool useNegotiatedPowerbyLinkPowerDelta = true; // changed through other extern defines in zigbee

void sl_mac_mark_indirect_buffers(void);
void sl_mac_mark_scan_buffer(void);
static void send_frame(uint8_t mac_index);
static void send_poll(uint8_t mac_index);

void sl_mac_mark_upper_mac_buffers(void)
{
  for (uint8_t mac = 0; mac < MAX_MAC_INDEX; mac++ ) {
    emMarkBuffer(&(sl_mac_upper_mac_state[mac].current_outgoing_frame.packet));
    for (uint8_t i = 0; i < sl_mac_upper_mac_state[mac].unsent_message_count; i++) {
      emMarkBuffer(&(sl_mac_upper_mac_state[mac].tx_queue[i].packet));
    }
  }
}

sl_status_t sl_mac_init(uint8_t mac_index)
{
  //OPTIMIZATION_PREAMBLE();
  if (MAC_INDEX >= MAX_MAC_INDEX) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + MAC_INDEX;

  state->pending_tasks_bitmask = 0;
  for (uint8_t i = 0; i < MAC_TX_QUEUE_SIZE; i++) {
    MEMSET(state->tx_queue + i, 0, sizeof(sl_mac_upper_mac_tx_queue_entry_t));
    state->tx_queue[i].packet = NULL_BUFFER;
    state->tx_queue[i].tx_complete_callback = NULL;
  }
  for (uint8_t i = 0; i < SL_MAC_MAX_SUPPORTED_NETWORKS; i++) {
    MEMSET(state->nwk_radio_parameters + i, 0, sizeof(sl_mac_radio_parameters_t));
    state->nwk_radio_parameters[i].local_node_id = EMBER_USE_LONG_ADDRESS;
    state->nwk_radio_parameters[i].parent_node_id = EMBER_USE_LONG_ADDRESS;
    state->nwk_radio_parameters[i].pan_id = EMBER_BROADCAST_PAN_ID;
    state->nwk_radio_parameters[i].rx_state = SL_MAC_RX_OFF;
  }
  MEMSET(state->outgoing_flat_packet, 0, MAX_FLAT_PACKET_SIZE);
  state->unsent_message_count = 0;
  state->mac_shutdown_callback = NULL;
  state->incoming_packet_callback = NULL;
  state->mac_is_shutdown = false;
  state->symbol_timer_callback = NULL;
  state->current_outgoing_frame.packet = NULL_BUFFER,
  state->current_outgoing_frame.nwk_index = 0xFF,
  state->current_outgoing_frame.tag = 0xFF,
  state->current_outgoing_frame.tx_complete_callback = NULL;
#ifdef MAC_DUAL_PRESENT
  //Work around serial initialization issue with dual phy NCP
  //Without this, mac init passes channel set through before
  //the transceiver is initialized
  state->current_nwk = 0xFF;
#else
  state->current_nwk = 0;
#endif

  mac_outgoing_sequence_number = halCommonGetRandom() & 0x00FF;

  // Initialize multi-network polling queue
  MEMSET(sl_mac_network_poll_queue, 0xFF, SL_MAC_MAX_SUPPORTED_NETWORKS);
  // This also initializes the radio.
  sl_mac_lower_mac_init(MAC_INDEX, EMBER_RADIO_POWER_MODE_OFF);

  sl_mac_kickstart(MAC_INDEX);

  return SL_STATUS_OK;
}

sl_status_t sl_mac_get_free_nwk_index(uint8_t mac_index, uint8_t *free_nwk_index)
{
  if (MAC_INDEX >= MAX_MAC_INDEX) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + mac_index;

  for (uint8_t i = 0; i < SL_MAC_MAX_SUPPORTED_NETWORKS; i++) {
    sl_mac_radio_parameters_t *radio_params = state->nwk_radio_parameters + i;

    if (radio_params->rx_callback == NULL
        && radio_params->prepare_tx_callback == NULL) {
      *free_nwk_index = i;
      return SL_STATUS_OK;
    }
  }

  return SL_STATUS_FULL;
}

#ifndef EMBER_MULTI_NETWORK_STRIPPED
// for concurrent dual-pan
static uint8_t concurrent_rx_on_nwks(uint8_t mac_index)
{
  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + mac_index;
  uint8_t rx_on_count = 0;
  for (uint8_t i = 0; i < SL_MAC_MAX_SUPPORTED_NETWORKS; i++) {
    sl_mac_radio_parameters_t *nwk = state->nwk_radio_parameters + i;
    if (nwk->rx_state == SL_MAC_RX_ON_WHEN_IDLE) {
      rx_on_count++;
    }
  }
  return rx_on_count;
}
#endif // EMBER_MULTI_NETWORK_STRIPPED

sl_status_t sl_mac_set_nwk_radio_parameters(uint8_t mac_index, uint8_t nwk_index, sl_mac_radio_parameters_t *radio_parameters)
{
  if (MAC_INDEX >= MAX_MAC_INDEX || NWK_INDEX >= SL_MAC_MAX_SUPPORTED_NETWORKS) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  // check rx_on_when_idle
  for (uint8_t i = 0; i < SL_MAC_MAX_SUPPORTED_NETWORKS; i++) {
    if ((s.nwk_radio_parameters[i].rx_state == SL_MAC_RX_ON_WHEN_IDLE)
        && (radio_parameters->rx_state == SL_MAC_RX_ON_WHEN_IDLE)
        && (i != nwk_index)) {
      // mn-ipd-esi fails without the last condition above,
      //  may be instead we should turn off rx_on_when_idle for old network index when we change the always_on_nwk_index

      #ifndef UNIFIED_MAC_SCRIPTED_TEST
      // Multi-PAN devices are RxOn on both networks.
      // If the channel is the same, we allow it to set the radio parameters.
      if (emZcAndZrCount > 1
          && s.nwk_radio_parameters[i].channel == radio_parameters->channel) {
        break;
      }
      #endif

      // alt-amc test gets here, or/and would eventually fail
      return SL_STATUS_INVALID_STATE;
    }
  }

  // check the channel
  // Without the first condition this fails when the channel and such haven't yet been set up
  // We don't want to fail out of the rest of initialization, especifically when we are not attempting to change the channel ??
  if (!sl_mac_lower_mac_channel_is_valid(mac_index, radio_parameters->channel)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  //ToDo: check the power range, but we don't have  a lower-mac API to do so

  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + MAC_INDEX;
  sl_mac_radio_parameters_t *current_nwk_radio_params = state->nwk_radio_parameters + NWK_INDEX;

  // Copy the radio parameters
  MEMCOPY(current_nwk_radio_params, radio_parameters, sizeof(sl_mac_radio_parameters_t));

  if (sl_mac_lower_mac_is_idle(MAC_INDEX)) {
    if (state->current_nwk == NWK_INDEX) {
      //XXXJAR UNIFIEDMAC this fails when the channel and such haven't yet been set up
      // We don't want to fail out of the rest of initialization
      // Perhaps we should check this only when it's actually live
      (void) sli_set_lower_mac_params_to_current_network(MAC_INDEX);
    }

    SL_MAC_MULTI_PAN_CODE({
      if (concurrent_rx_on_nwks(MAC_INDEX) > 1) {
        //AH DUAL-PAN - the above check for the non-concurrent nwk case gaurds against
        // some cases where pushing the radio parameters down is undesireable.
        // However for concurrent dual-pan it doesn't have as much of an effect so
        // we push down regardless
        (void) sli_set_lower_mac_params_to_concurrent_networks(MAC_INDEX);
      }
    });
  }

  return SL_STATUS_OK;
}

sl_status_t sli_upper_mac_update_lower_mac_params(uint8_t mac_index)
{
  SL_MAC_MULTI_PAN_CODE({
    if (concurrent_rx_on_nwks(mac_index) > 1) {
      // DUAL_PAN
      sli_set_lower_mac_params_to_concurrent_networks(mac_index);
      return SL_STATUS_OK;
    }
  });

  sli_set_lower_mac_params_to_current_network(mac_index);
  return SL_STATUS_OK;
}

static void set_lower_mac_address_parameters(uint8_t mac_index,
                                             uint8_t radio_index,
                                             sl_mac_radio_parameters_t *nwk_params)
{
  sl_mac_lower_mac_set_pan_id(mac_index, radio_index, nwk_params->pan_id);
  sl_mac_lower_mac_set_node_id(mac_index, radio_index, nwk_params->local_node_id);
  sl_mac_lower_mac_set_eui64(mac_index, radio_index, nwk_params->local_eui);
}

static sl_status_t set_lower_mac_rx_duty_cycling(uint8_t mac_index,
                                                 sl_mac_radio_parameters_t *radio_params)
{
  sl_status_t p_status = SL_STATUS_FAIL;

  if ( sl_mac_lower_mac_is_idle(mac_index)
       && (p_status = sl_mac_enable_duty_cycling()) != SL_STATUS_OK) {
    return p_status;
  }

  return SL_STATUS_OK;
}

static sl_status_t set_lower_mac_radio_parameters(uint8_t mac_index,
                                                  sl_mac_radio_parameters_t *radio_params)
{
  sl_status_t p_status = SL_STATUS_FAIL;

  if ( radio_params->channel != sl_mac_lower_mac_get_radio_channel(mac_index)
       && (p_status = sl_mac_lower_mac_set_radio_channel(mac_index, radio_params->channel))
       != SL_STATUS_OK ) {
    return p_status;
  }

  if ( radio_params->tx_power != sl_mac_lower_mac_get_radio_power(mac_index)
       && (p_status = sl_mac_lower_mac_set_radio_power(mac_index, radio_params->tx_power))
       != SL_STATUS_OK ) {
    return p_status;
  }

  // EMZIGBEE-4996
  // We don't initialize these in the network params correctly, so just don't
  // push them down for now, leaving the lower-mac-rail defaults in place
  //sl_mac_set_csma_params(&(current_nwk_radio_params->csmaParams));

  // Don't push current state's rx_on_when_idle value directly because we may be
  // in the middle of a scan, in which case we want the radio to stay on
  RadioPowerMode radio_power_mode = sl_mac_get_radio_idle_mode(mac_index);

  if ( sl_mac_lower_mac_is_idle(mac_index)
       && (p_status = sl_mac_lower_mac_set_radio_idle_mode(mac_index,
                                                           radio_power_mode))
       != SL_STATUS_OK) {
    return p_status;
  }

  return SL_STATUS_OK;
}

#ifndef EMBER_MULTI_NETWORK_STRIPPED
sl_status_t sli_set_lower_mac_params_to_concurrent_networks(uint8_t mac_index)
{
  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + mac_index;
  sl_mac_radio_parameters_t *nwk;
  sl_status_t p_status = SL_STATUS_FAIL;

  if (mac_index >= MAX_MAC_INDEX
      || concurrent_rx_on_nwks(mac_index) > SL_MAC_MAX_SUPPORTED_NETWORKS) {
    return SL_STATUS_FAIL;
  }

  // iterate through all of the always on networks and push the address params down
  for (uint8_t i = 0; i < SL_MAC_MAX_SUPPORTED_NETWORKS; i++) {
    nwk = state->nwk_radio_parameters + i;
    if (nwk->rx_state == SL_MAC_RX_ON_WHEN_IDLE) {
      set_lower_mac_address_parameters(mac_index, i, nwk);
    }
  }
  // since we can only operate concurrent rx-on nwks if they use the same
  // radio parameters (such as channel, idle mode), we set the radio params
  // according to the "current_nwk". sl_mac_set_nwk_radio_parameters() enforces
  // to set same channel for multi PAN network. Radio power can be different
  // per network and send_frame() takes care of it for outgoing packet.
  p_status = set_lower_mac_radio_parameters(mac_index,
                                            state->nwk_radio_parameters + state->current_nwk);
  return p_status;
}
#endif // EMBER_MULTI_NETWORK_STRIPPED

sl_status_t sli_set_lower_mac_params_to_current_network(uint8_t mac_index)
{
  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + mac_index;
#ifdef EMBER_MULTI_NETWORK_STRIPPED
  sl_mac_radio_parameters_t *current_nwk_radio_params = state->nwk_radio_parameters;
#else
  sl_mac_radio_parameters_t *current_nwk_radio_params = state->nwk_radio_parameters + state->current_nwk;
#endif

  if (mac_index >= MAX_MAC_INDEX || state->current_nwk >= SL_MAC_MAX_SUPPORTED_NETWORKS) {
    return SL_STATUS_FAIL;
  }

  sl_status_t p_status = SL_STATUS_FAIL;
  // always use radio_index 0 when not in concurrent rx-on
  set_lower_mac_address_parameters(mac_index, 0, current_nwk_radio_params);

  p_status = set_lower_mac_radio_parameters(mac_index, current_nwk_radio_params);

  return p_status;
}

sl_status_t sli_enable_rx_duty_cycling(uint8_t mac_index)
{
  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + mac_index;
#ifdef EMBER_MULTI_NETWORK_STRIPPED
  sl_mac_radio_parameters_t *current_nwk_radio_params = state->nwk_radio_parameters;
#else
  sl_mac_radio_parameters_t *current_nwk_radio_params = state->nwk_radio_parameters + state->current_nwk;
#endif

  if (mac_index >= MAX_MAC_INDEX || state->current_nwk >= SL_MAC_MAX_SUPPORTED_NETWORKS) {
    return SL_STATUS_FAIL;
  }

  sl_status_t p_status = SL_STATUS_FAIL;

  p_status = set_lower_mac_rx_duty_cycling(mac_index, current_nwk_radio_params);

  return p_status;
}

sl_status_t sli_set_mac_pan_id_node_id_to_current_network(uint8_t mac_index)
{
  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + mac_index;
#ifdef EMBER_MULTI_NETWORK_STRIPPED
  sl_mac_radio_parameters_t *current_nwk_radio_params = state->nwk_radio_parameters;
#else
  sl_mac_radio_parameters_t *current_nwk_radio_params = state->nwk_radio_parameters + state->current_nwk;
#endif

  sl_mac_lower_mac_set_pan_id(mac_index, 0, current_nwk_radio_params->pan_id);
  sl_mac_lower_mac_set_node_id(mac_index, 0, current_nwk_radio_params->local_node_id);
  return SL_STATUS_OK;
}

sl_status_t sl_mac_get_nwk_radio_parameters(uint8_t mac_index, uint8_t nwk_index, sl_mac_radio_parameters_t *return_params)
{
  if (MAC_INDEX >= MAX_MAC_INDEX || NWK_INDEX >= SL_MAC_MAX_SUPPORTED_NETWORKS) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + MAC_INDEX;
  sl_mac_radio_parameters_t *current_nwk_radio_params = state->nwk_radio_parameters + NWK_INDEX;

  MEMCOPY(return_params, current_nwk_radio_params, sizeof(sl_mac_radio_parameters_t));

  return SL_STATUS_OK;
}

bool sl_mac_network_is_active(uint8_t mac_index, uint8_t nwk_index)
{
  if (mac_index >= MAX_MAC_INDEX || nwk_index >= SL_MAC_MAX_SUPPORTED_NETWORKS) {
    return false;
  }

  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + mac_index;
  sl_mac_radio_parameters_t *nwk_radio_params = state->nwk_radio_parameters + nwk_index;

  if (nwk_radio_params->rx_callback != NULL
      && nwk_radio_params->prepare_tx_callback != NULL
      && nwk_radio_params->pan_id != EMBER_BROADCAST_PAN_ID) {
    return true;
  }

  return false;
}

static bool consume_shutdown_callback(uint8_t mac_index)
{
  sl_mac_shutdown_callback_t callback = s.mac_shutdown_callback;
  if (callback != NULL) { // ATOMIC???
    s.mac_shutdown_callback = NULL;
    s.mac_is_shutdown = true; // full shutdown
    callback(MAC_INDEX);
    return true;
  }
  return false;
}
//Request graceful shutdown of mac
//mac continues transmitting until queue is empty, then suspends operation and calls the callback
//any packets received during the suspension are passed to the provided incoming packet callback.

sl_status_t sl_mac_suspend_operation(uint8_t mac_index, sl_mac_shutdown_callback_t shutdown_callback, sl_mac_receive_callback_t incoming_packet_callback)
{
  if ( MAC_INDEX >= MAX_MAC_INDEX
       || s.mac_shutdown_callback != NULL // in the middle of shutdown, based on an earlier call
       || s.mac_is_shutdown
       || shutdown_callback == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  // for a while we might be in a state that both shutdown_callback and  mac_skip_rx_callback are not NULL
  // this would mean we are in the middle of shutdown
  s.mac_shutdown_callback = shutdown_callback;
  s.incoming_packet_callback = incoming_packet_callback;

  sl_mac_kickstart(MAC_INDEX);

  return SL_STATUS_OK;
}

// Resume MAC operation after concluding shutdown
sl_status_t sl_mac_resume_operation(uint8_t mac_index)
{
  if (MAC_INDEX >= MAX_MAC_INDEX) {
    return SL_STATUS_INVALID_PARAMETER;
  }
//  s.mac_shutdown_callback = NULL; //logically this already is NULL
  s.incoming_packet_callback = NULL; //immidiate
  s.mac_is_shutdown = false;
  if (s.symbol_timer_callback) {
    s.symbol_timer_callback = NULL;
    sl_mac_lower_mac_cancel_symbol_timer(MAC_INDEX);
  }
  sli_upper_mac_update_lower_mac_params(MAC_INDEX);
  return SL_STATUS_OK;
}

// This event is used to defer the lower MAC idle notification.
#ifndef EVENT_CONTROL_SYSTEM

#ifdef MAC_DUAL_PRESENT
void upperMacEventHandler0(EmberEvent *event);
void upperMacEventHandler1(EmberEvent *event);
EmberEvent emUpperMacEvents[2] = { {
                                     { &emStackEventQueue,
                                       upperMacEventHandler0,
                                       emIsrEventMarker,
                                       #ifndef EMBER_TEST
                                       ""
                                       #else
                                       "upper MAC0"
                                       #endif
                                     },
                                     NULL
                                   },
                                   {
                                     {
                                       &emStackEventQueue,
                                       upperMacEventHandler1,
                                       emIsrEventMarker,
                                       #ifndef EMBER_TEST
                                       ""
                                       #else
                                       "upper MAC1"
                                       #endif
                                     },
                                     NULL
                                   } };
#else
void upperMacEventHandler(EmberEvent *event);
EmberEvent emUpperMacEvent = {
  {
    &emStackEventQueue,
    upperMacEventHandler,
    emIsrEventMarker,
    #ifndef EMBER_TEST
    ""
    #else
    "upper MAC"
    #endif
  },
  NULL
};
#endif //MAC_DUAL_PRESENT
#else //EVENT_CONTROL_SYSTEM
#ifdef MAC_DUAL_PRESENT
EmberEventControl emUpperMacEvents[2];
#else
EmberEventControl emUpperMacEvent;
void emUpperMacEventHandler(void);
EmberEventData upperMacEvents[] =
{
  { &emUpperMacEvent, emUpperMacEventHandler },
  { NULL, NULL }       // terminator
};
#endif
#endif//EVENT_CONTROL_SYSTEM

static void mac_really_kickstart(uint8_t mac_index)
{
  if (emMfglibMode != 0U) {
    // mfglib has hijacked the radio, so do nothing
    return;
  }

#ifdef MAC_DUAL_PRESENT
  sli_mac_inactivate_event(emUpperMacEvents[MAC_INDEX_ARGUMENT_SOLO]);
#else
  sli_mac_inactivate_event(emUpperMacEvent);
#endif
  if (sl_mac_lower_mac_is_idle(MAC_INDEX)) {
    // First we send out any polls that must transmit ASAP
    if (s.pending_tasks_bitmask & MAC_PENDING_TASK_POLL_BIT) {
      send_poll(MAC_INDEX); // clears MAC_PENDING_TASK_POLL_BIT
      // Then queued messages, if any
    } else if (s.unsent_message_count) {
      MEMCOPY(&(s.current_outgoing_frame), s.tx_queue, sizeof(sl_mac_upper_mac_tx_queue_entry_t));
      send_frame(MAC_INDEX);
      //advance the queue
      MEMMOVE(s.tx_queue, s.tx_queue + 1, s.unsent_message_count * sizeof(sl_mac_upper_mac_tx_queue_entry_t));
      s.unsent_message_count--;
      // Then we shut down the MAC, if needed
    } else if ( consume_shutdown_callback(MAC_INDEX)) {
      // If we're shutting down, clear pending tasks
      sl_mac_cancel_poll(mac_index, 0);
      // Next we elevate a poll to transmit ASAP, if needed
    } else if ((s.pending_tasks_bitmask & MAC_PENDING_TASK_POLL_BIT_AFTER_SEND)
               || sl_mac_multi_network_poll_pending()) { // For the multi network scenario
      s.pending_tasks_bitmask |= MAC_PENDING_TASK_POLL_BIT;
      s.pending_tasks_bitmask &= ~MAC_PENDING_TASK_POLL_BIT_AFTER_SEND;
      sl_mac_kickstart(mac_index);
      // Next, we check if we have a JIT message ready
    } else if ( s.current_nwk < SL_MAC_MAX_SUPPORTED_NETWORKS
                && s.nwk_radio_parameters[s.current_nwk].make_jit_message_callback != NULL
                && s.nwk_radio_parameters[s.current_nwk].make_jit_message_callback()) {
    } else {
#ifndef UNIFIED_MAC_SCRIPTED_TEST
      //TODO this isn't always correct, I still need to debug the cases where it's wrong
      uint8_t always_on_nwk_index = emGetActiveAlwaysOnNetworkIndex();
#else
      uint8_t always_on_nwk_index = 0;
#endif

      if (!s.mac_is_shutdown ) {
        if (always_on_nwk_index != 0xFF /*&&  s.current_nwk != always_on_nwk_index*/) {
          s.current_nwk = always_on_nwk_index;
        }
        sli_upper_mac_update_lower_mac_params(MAC_INDEX);
      }
    }
  }
}

#ifndef EVENT_CONTROL_SYSTEM
#ifdef MAC_DUAL_PRESENT
void upperMacEventHandler0(EmberEvent *event)
{
  mac_really_kickstart(0);
}
void upperMacEventHandler1(EmberEvent *event)
{
  mac_really_kickstart(1);
}
#else
void upperMacEventHandler(EmberEvent *event)
{
  mac_really_kickstart(0);
}
#endif
#else //EVENT_CONTROL_SYSTEM
#ifdef MAC_DUAL_PRESENT
void emUpperMacEventHandler0(void)
{
  mac_really_kickstart(0);
}
void emUpperMacEventHandler1(void)
{
  mac_really_kickstart(1);
}
#endif

void emUpperMacEventHandler(void)
{
  mac_really_kickstart(0);
}
#endif //EVENT_CONTROL_SYSTEM

void sl_mac_kickstart(uint8_t mac_index)
{
#ifdef MAC_DUAL_PRESENT
  if (!sli_mac_event_is_active(emUpperMacEvents[MAC_INDEX_ARGUMENT_SOLO])) {
    sli_mac_activate_event(emUpperMacEvents[MAC_INDEX_ARGUMENT_SOLO]);
  }
#else
  if (!sli_mac_event_is_active(emUpperMacEvent)) {
    sli_mac_activate_event(emUpperMacEvent);
  }
#endif
}

static void send_poll(uint8_t mac_index)
{
  if (s.pending_tasks_bitmask & MAC_PENDING_TASK_POLL_BIT) {
    s.pending_tasks_bitmask &= ~MAC_PENDING_TASK_POLL_BIT;
    uint8_t polling_nwk_index = sl_mac_dequeue_polling_network();
    if (s.pending_tasks_bitmask & MAC_PENDING_TASK_POLL_BIT_AFTER_SEND) {
      // If we have another poll coming behind this one, put the network back in the queue
      sl_mac_add_current_network_to_polling_queue(polling_nwk_index);
    }
    PacketHeader dataRequest = sl_mac_make_data_request(MAC_INDEX, polling_nwk_index);
    s.current_outgoing_frame.packet = dataRequest;
    s.current_outgoing_frame.nwk_index = polling_nwk_index;
    s.current_outgoing_frame.tag = 0;
    s.current_outgoing_frame.tx_complete_callback = s.nwk_radio_parameters[s.current_nwk].poll_tx_complete_callback;
    send_frame(MAC_INDEX);
  }
}

void sl_mac_request_poll(uint8_t mac_index, uint8_t nwk_index)
{
  sl_mac_add_current_network_to_polling_queue(NWK_INDEX);
  s.pending_tasks_bitmask |= MAC_PENDING_TASK_POLL_BIT_AFTER_SEND;
  sl_mac_kickstart(MAC_INDEX);
}

void sl_mac_cancel_poll(uint8_t mac_index, uint8_t nwk_index)
{
  s.pending_tasks_bitmask &= ~MAC_PENDING_TASK_POLL_BIT;
  s.pending_tasks_bitmask &= ~MAC_PENDING_TASK_POLL_BIT_AFTER_SEND;
}

sl_status_t sl_mac_submit(uint8_t mac_index,
                          uint8_t nwk_index,
                          PacketHeader packet,
                          sl_mac_transmit_priority_t priority,
                          sl_mac_transmit_complete_callback_t callback,
                          uint8_t tag)
{
  if (MAC_INDEX >= MAX_MAC_INDEX || NWK_INDEX >= SL_MAC_MAX_SUPPORTED_NETWORKS) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  uint8_t index;
  if ( emMfglibMode != 0U   // mfglib has hijacked the radio
       || s.mac_shutdown_callback != NULL
       || (s.mac_is_shutdown && priority != TRANSMIT_PRIORITY_BYPASS_SHUTDOWN)) {
    return SL_STATUS_FAIL;
  }
  if (s.unsent_message_count < MAC_TX_QUEUE_SIZE) {
    if (priority == SL_MAC_TRANSMIT_PRIORITY_NORMAL) {
      index = s.unsent_message_count;
    } else {
      // insert at head of queue
      MEMMOVE(s.tx_queue + 1, s.tx_queue, s.unsent_message_count * sizeof(sl_mac_upper_mac_tx_queue_entry_t));
      index = 0;
    }
    s.tx_queue[index].packet = packet;
    s.tx_queue[index].nwk_index = NWK_INDEX;
    s.tx_queue[index].tag = tag;
    s.tx_queue[index].tx_complete_callback = callback;
    s.unsent_message_count++;

    sl_mac_kickstart(MAC_INDEX);
    return SL_STATUS_OK;
  } else {
    return SL_STATUS_FULL;
  }
}

void sli_mac_empty_transmit_queue(uint8_t mac_index)
{
  if (MAC_INDEX >= MAX_MAC_INDEX) {
    return;// SL_STATUS_INVALID_PARAMETER;
  }

  for (uint8_t i = 0; i < MAC_TX_QUEUE_SIZE; i++) {
    MEMSET(s.tx_queue + i, 0, sizeof(sl_mac_upper_mac_tx_queue_entry_t));
    s.tx_queue[i].packet = NULL_BUFFER;
    s.tx_queue[i].tx_complete_callback = NULL;
  }
  s.unsent_message_count = 0;
}

static void send_frame(uint8_t mac_index)
{
  UNUSED uint8_t nwk_index = s.current_outgoing_frame.nwk_index;
  if (s.current_nwk != NWK_INDEX) {
    s.current_nwk = NWK_INDEX;
    sli_upper_mac_update_lower_mac_params(MAC_INDEX);
  }
  int8_t tx_power = s.nwk_radio_parameters[NWK_INDEX].tx_power;
  Buffer packet = s.current_outgoing_frame.packet;
  // Convert the packet and potential payload buffer to a flat buffer and
  // prepend the PHY header
  uint8_t mac_payload_offset = sl_mac_prepare_transmit(NWK_INDEX, packet, s.outgoing_flat_packet);
  sl_mac_tx_options_bitmask_t tx_options = EMBER_MAC_USE_CSMA;
  if (s.nwk_radio_parameters[NWK_INDEX].prepare_tx_callback != NULL) {
    tx_options = s.nwk_radio_parameters[NWK_INDEX].prepare_tx_callback(packet,
                                                                       s.outgoing_flat_packet,
                                                                       mac_payload_offset,
                                                                       MAC_INDEX,
                                                                       NWK_INDEX,
                                                                       &tx_power);
    // Use link power only on SubGhz network.
    #if SINGLE_PHY_MULTIPAGE_SUPPORT
    if (useNegotiatedPowerbyLinkPowerDelta) {// changed from zigbee
      if (emPhyGetChannelPageInUse()) { //for 2.4Ghz, page is zero
        sl_mac_lower_mac_set_radio_power(MAC_INDEX, tx_power);
      }
    }
    #elif defined(MAC_DUAL_PRESENT)
    if (useNegotiatedPowerbyLinkPowerDelta) {// changed from zigbee
      if (MAC_INDEX == 1) {
        sl_mac_lower_mac_set_radio_power(MAC_INDEX, tx_power);
      }
    }
    #endif
  }

  //EMZIGBEE-5351, this allows the prepare_tx_callback to drop a packet by setting the length byte to 0
  if (s.outgoing_flat_packet[0] == 0) {
    //EMZIGBEE-6708, trigger complete callback with success despite droping the packet
    sl_mac_packet_send_complete_callback(MAC_INDEX, SL_STATUS_OK);
    sl_mac_kickstart(MAC_INDEX);
  } else {
    sl_mac_lower_mac_send(MAC_INDEX, s.outgoing_flat_packet, tx_options);
  }
}

void sl_mac_packet_send_complete_callback(uint8_t mac_index, sl_status_t status)
{
  if (emMfglibMode != 0U) {
    // mfglib has hijacked the radio, so do nothing
    return;
  }

  assert(MAC_INDEX < MAX_MAC_INDEX);
  assert(s.current_outgoing_frame.packet != NULL_BUFFER);

  sl_mac_transmit_complete_callback_t callback = s.current_outgoing_frame.tx_complete_callback;
  if (callback != NULL) {
    callback(MAC_INDEX, status, s.current_outgoing_frame.packet, s.current_outgoing_frame.tag);
  }
  s.current_outgoing_frame.packet = NULL_BUFFER;
  s.current_outgoing_frame.tx_complete_callback = NULL;

  // If the last packet sent was not a poll and we have a poll waiting, elevate
  // it now. This allows us to interleave transmissions of non-polls and polls.
  bool wasLastTxAPoll = (callback == s.nwk_radio_parameters[s.current_nwk].poll_tx_complete_callback);
  if (!wasLastTxAPoll
      && ((s.pending_tasks_bitmask & MAC_PENDING_TASK_POLL_BIT_AFTER_SEND)
          || (sl_mac_multi_network_poll_pending()))) {
    s.pending_tasks_bitmask |= MAC_PENDING_TASK_POLL_BIT;
    s.pending_tasks_bitmask &= ~MAC_PENDING_TASK_POLL_BIT_AFTER_SEND;
    sl_mac_kickstart(mac_index);
  }
}

void sl_mac_notify_mac_is_idle(uint8_t mac_index)
{
  assert(MAC_INDEX < MAX_MAC_INDEX);

  sl_mac_kickstart(MAC_INDEX);
}

sl_status_t sl_mac_receive_callback(uint8_t mac_index, PacketHeader rawHeader)
{
  if (MAC_INDEX >= MAX_MAC_INDEX) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  // Current upper MAC state
  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + MAC_INDEX;

  uint8_t *rawHeaderContents = emGetBufferPointer(rawHeader);
  if (rawHeaderContents == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  uint8_t rawHeaderLength = emGetBufferLength(rawHeader);
  uint8_t phyPacketLength = rawHeaderContents[0];
  uint16_t internalMacFcf = HIGH_LOW_TO_INT(rawHeaderContents[2], rawHeaderContents[1]);

  // Get the appended info
  uint8_t appendedInfo[NUM_APPENDED_INFO_BYTES] = { 0 };
  MEMCOPY(appendedInfo,
          rawHeaderContents + rawHeaderLength - NUM_APPENDED_INFO_BYTES,
          NUM_APPENDED_INFO_BYTES);

  // For the multi-network case, set the current network.
  UNUSED uint8_t nwk_index  = (appendedInfo[APPENDED_INFO_NETWORK_OVERWRITE_BYTE_INDEX]
                               & APPENDED_INFO_NETWORK_OVERWRITE_NET_ID_MASK);

  PacketHeader internalHeader = NULL_BUFFER;
  uint8_t *rawMacHeader = rawHeaderContents + 1;
  if (emMfglibMode != 0U) {
    if (emMfglibRxCallback != NULL) {
      (*emMfglibRxCallback)(rawHeaderContents,
                            appendedInfo[APPENDED_INFO_LQI_BYTE_INDEX],
                            (int8_t) appendedInfo[APPENDED_INFO_RSSI_BYTE_INDEX]);
    }
    return SL_STATUS_OK;
  }

  if ((internalMacFcf & EMBER_MAC_HEADER_FC_FRAME_TYPE_MASK) == EMBER_MAC_HEADER_FC_FRAME_TYPE_ACK) {
    // drop 15.4 ACKs in MAC mode.
    return SL_STATUS_FAIL;
  }

  uint8_t rawMacHeaderLength = sl_mac_flat_mac_header_length(rawMacHeader, false);

  // Expect a valid packet
  int8_t macPayloadLength = (phyPacketLength - rawMacHeaderLength - PHY_APPENDED_CRC_SIZE);
  if (macPayloadLength < 0) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  // TODO: Increment incoming MAC counters?

  if (state->nwk_radio_parameters[NWK_INDEX].packet_handoff_incoming_callback != NULL) {
    sl_mac_packet_handoff_incoming_callback_t callback
      = state->nwk_radio_parameters[NWK_INDEX].packet_handoff_incoming_callback;
    if (!callback(rawHeader, 1, NULL)) {
      return SL_STATUS_INVALID_PARAMETER;
    }
  }

  // Process the MAC header.
  uint8_t retval = sl_mac_radio_receive_mac_header_callback(MAC_INDEX,
                                                            NWK_INDEX,
                                                            rawMacHeader,
                                                            macPayloadLength,
                                                            &internalHeader);
  if (retval == SL_STATUS_OK) {
    if (sl_mac_is_data_packet(internalHeader)) {
      if (state->nwk_radio_parameters[NWK_INDEX].process_network_header_callback != NULL) {
        sl_mac_process_network_header_callback_t callback
          = state->nwk_radio_parameters[NWK_INDEX].process_network_header_callback;
        if (!callback(internalHeader, (rawMacHeader + rawMacHeaderLength))) {
          return SL_STATUS_INVALID_STATE;
        }
      }
    }

    uint8_t *internalHeaderPayload = sl_mac_payload_pointer(internalHeader);

    if (sl_mac_is_data_packet(internalHeader)) {
      // Copy MAC payload to just after internal header.
      MEMCOPY(internalHeaderPayload,
              rawMacHeader + rawMacHeaderLength,
              macPayloadLength);
    } else {
//    sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)internalHeaderContents;

      //We need to extend it
      if (emberAppendToLinkedBuffers(internalHeader, rawMacHeader, rawMacHeaderLength + macPayloadLength) != SL_STATUS_OK) {
        return SL_STATUS_ALLOCATION_FAILED;
      }
    }

    sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *) emGetBufferPointer(internalHeader);
#if !defined(EMBER_MULTI_NETWORK_STRIPPED)
    in_memory_packet->info.nwk_index = (appendedInfo[APPENDED_INFO_NETWORK_OVERWRITE_BYTE_INDEX]
                                        & APPENDED_INFO_NETWORK_OVERWRITE_NET_ID_MASK);
#endif

    in_memory_packet->appended_info.queue_info.lqi = appendedInfo[APPENDED_INFO_LQI_BYTE_INDEX];
    in_memory_packet->appended_info.queue_info.rssi = appendedInfo[APPENDED_INFO_RSSI_BYTE_INDEX];
    in_memory_packet->appended_info.queue_info.channel = appendedInfo[APPENDED_INFO_CHANNEL_OVERWRITE_BYTE_INDEX];

    in_memory_packet->appended_info.queue_info.timestamp
      = (uint32_t)appendedInfo[APPENDED_INFO_MAC_TIMER_BYTE_2_INDEX] << 16
        | (uint32_t)appendedInfo[APPENDED_INFO_MAC_TIMER_BYTE_1_INDEX] << 8
        | (uint32_t)appendedInfo[APPENDED_INFO_MAC_TIMER_BYTE_0_INDEX];

    // Pass this internal version to the appropriate rx callback
    rawHeader = internalHeader;
    sl_mac_receive_callback_t callback = NULL;
    if (s.mac_is_shutdown) {
      callback = s.incoming_packet_callback;
    } else {
      callback = state->nwk_radio_parameters[NWK_INDEX].rx_callback;
    }

    if (callback != NULL) {
      callback(rawHeader);
    }
  }

  // TODO: Zigbee restores current network here.
  return retval;
}

void sl_mac_symbol_timer_expired_handler_isr(uint8_t mac_index)
{
  assert(MAC_INDEX < MAX_MAC_INDEX);
  sl_mac_symbol_timer_callback_t callback = s.symbol_timer_callback;

  assert(s.symbol_timer_callback != NULL);

  s.symbol_timer_callback = NULL;
  callback();
}

uint8_t sl_mac_prepare_transmit(uint8_t nwk_index, Buffer header, uint8_t *phy_packet)
{
  uint8_t *finger = phy_packet + EMBER_MAC_HEADER_OFFSET;   // first byte is the length
  uint8_t header_len = sl_mac_payload_length(header);
  uint16_t frameControl;

  if (sl_mac_header_mac_info_frame_type(header) == EMBER_MAC_INFO_TYPE_DATA) {   // Frame type is data
    frameControl = 0x8840 | EMBER_MAC_HEADER_FC_FRAME_TYPE_DATA;
    if (sl_mac_destination(header) != 0xFFFF) {
      frameControl |= EMBER_MAC_HEADER_FC_ACK_REQUEST_BIT;
    }

    emberStoreLowHighInt16u(finger + 3, sl_mac_upper_mac_state[0].nwk_radio_parameters[NWK_INDEX].pan_id);
    emberStoreLowHighInt16u(finger + 5, sl_mac_destination(header));
    emberStoreLowHighInt16u(finger + 7, sl_mac_upper_mac_state[0].nwk_radio_parameters[NWK_INDEX].local_node_id);
    finger += 9;
  } else {
    frameControl = sl_mac_flat_mac_frame_control(phy_packet, true);
  }

  if (sl_mac_check_additional_pending_data(header)) {
    frameControl |= MAC_FRAME_FLAG_FRAME_PENDING;
  }

  sl_mac_flat_set_mac_frame_control(phy_packet, true, frameControl);

  MEMCOPY(finger, sl_mac_payload_pointer(header), header_len);
  finger += header_len;

  // Append payload buffer if present
  Buffer payload_buffer = emGetPayloadLink(header);  //emPacketHeaderPayload(header);
  if (payload_buffer != EMBER_NULL_MESSAGE_BUFFER) {
    uint8_t payload_len = emGetBufferLength(payload_buffer);
    MEMCOPY(finger,
            emGetBufferPointer(payload_buffer),
            payload_len);
    finger += payload_len;
  }

  phy_packet[EMBER_MAC_HEADER_OFFSET + 2] = mac_outgoing_sequence_number++;  //update the mac seq number
  // Update the PHY length byte of the packet
  *phy_packet = finger
                - phy_packet
                - EMBER_PHY_HEADER_LENGTH   // length itself not included
                + PHY_APPENDED_CRC_SIZE;

  return sl_mac_flat_payload_offset(phy_packet, true);
}

// -----------------------
// Symbol timer interface.

sl_status_t sl_mac_schedule_symbol_timer(uint8_t mac_index,
                                         sl_mac_symbol_timer_callback_t callback,
                                         uint16_t duration)
{
  sl_status_t status;

  // Symbol timer already in use.
  if (s.symbol_timer_callback != NULL) {
    return SL_STATUS_INVALID_STATE;
  } else {
    s.symbol_timer_callback = callback;
  }

  status = sl_mac_lower_mac_schedule_symbol_timer(0, duration);

  return status;
}

// Pass-through packet headers do not get MAC or other headers prepended prior to transmission.
sl_status_t sl_mac_send_raw_message(uint8_t mac_index,
                                    Buffer message,
                                    sl_mac_transmit_priority_t priority,
                                    bool useCca,
                                    sl_mac_transmit_complete_callback_t callback)
{
  uint8_t macInfoFlags = (EMBER_MAC_INFO_TYPE_PASSTHROUGH | (!useCca ? MAC_INHIBIT_CCA : 0));

  PacketHeader header  = sl_mac_make_raw_message(message,
                                                 macInfoFlags,
                                                 // TODO this is incorrect
                                                 // Should be the current stack network context instead
                                                 s.current_nwk);

  if (header == NULL_BUFFER) {
    return SL_STATUS_FAIL;
  }

  return sl_mac_submit(MAC_INDEX,
                       s.current_nwk,
                       header,
                       priority,
                       callback,    /* tx complete callback */
                       0 /*tag*/);
}

RadioPowerMode sl_mac_get_radio_idle_mode(uint8_t mac_index)
{
  // TODO: We currently don't have control of the idle mode on shutdown operations
  // This might not enumerate every possible case where we need the radio on, but
  // this works for Zigbee, so leaving it as it is for now.
  return (((s.nwk_radio_parameters[s.current_nwk].rx_state == SL_MAC_RX_ON_WHEN_IDLE) || s.mac_is_shutdown)
          ? EMBER_RADIO_POWER_MODE_RX_ON
#ifndef UPPER_MAC_USING_BASE_PHY
          // TODO: right now make test uses base's phy/phy.h, which doesn't define
          // EMBER_RADIO_POWER_MODE_DC_RX; only mac-phy.h defines it.
          // Eventually zigbee will stop using base's phy.h and this should be
          // reverted
          : ((s.nwk_radio_parameters[s.current_nwk].rx_state == SL_MAC_RX_DUTY_CYCLING)
             ? EMBER_RADIO_POWER_MODE_DC_RX : EMBER_RADIO_POWER_MODE_OFF));
#else // EMBER_TEST
          : EMBER_RADIO_POWER_MODE_OFF);
#endif // EMBER_TEST
}

uint8_t sl_mac_get_current_radio_network_index(uint8_t mac_index)
{
  return s.current_nwk;
}

bool sl_mac_upper_mac_is_empty(uint8_t mac_index)
{
  #ifdef MAC_DUAL_PRESENT
  return (!s.mac_is_shutdown   //primarily to keep us awake while scanning
          && sl_mac_lower_mac_is_idle(PHY_INDEX_NATIVE) && sl_mac_lower_mac_is_idle(PHY_INDEX_PRO2PLUS)
          && !sli_mac_event_is_active(emUpperMacEvents[PHY_INDEX_NATIVE])
          && !sli_mac_event_is_active(emUpperMacEvents[PHY_INDEX_PRO2PLUS])
          && !sl_mac_upper_mac_state[PHY_INDEX_NATIVE].pending_tasks_bitmask
          && sl_mac_upper_mac_state[PHY_INDEX_NATIVE].unsent_message_count == 0
          && !sl_mac_upper_mac_state[PHY_INDEX_PRO2PLUS].pending_tasks_bitmask
          && sl_mac_upper_mac_state[PHY_INDEX_PRO2PLUS].unsent_message_count == 0);
  #else
  return (!s.mac_is_shutdown   //primarily to keep us awake while scanning
          && sl_mac_lower_mac_is_idle(0)
          && !sli_mac_event_is_active(emUpperMacEvent)
          && !s.pending_tasks_bitmask
          && s.unsent_message_count == 0);
  #endif
}

#ifndef EMBER_MULTI_NETWORK_STRIPPED
// When given pan id and radio channel it will return a bitmask indicating
// which network indices "match".  It will set the bit for the index of
// the first active nwk on that channel with that pan, or if the given
// pan id is a broadcast (0xFFFF) it will set a bit for all active nwks on the
// given channel.
sl_status_t sl_mac_get_matching_nwk_index_bitmask(uint8_t mac_index,
                                                  uint16_t pan_id,
                                                  uint8_t radio_channel,
                                                  uint8_t *nwk_bit_mask)
{
  uint8_t nwk_bits = 0;

  if (mac_index >= MAX_MAC_INDEX) {
    return SL_STATUS_FAIL;
  }

  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + mac_index;
  // Iterate through the networks and return any matching indices
  for (uint8_t i = 0; i < SL_MAC_MAX_SUPPORTED_NETWORKS; i++) {
    if (sl_mac_network_is_active(mac_index, i)) {
      // Get the network parameters
      sl_mac_radio_parameters_t *nwk_radio_params = state->nwk_radio_parameters + i;

      // Make sure that radio channel and pan id matches, else move to the next network
      if ((nwk_radio_params->channel == radio_channel)
          && ((pan_id == EMBER_BROADCAST_PAN_ID) || (nwk_radio_params->pan_id == pan_id))) {
        // If we get here, then the network index matches so set the bit
        nwk_bits |= (1 << i);

        // Quit if we found the non-broadcast pan id
        if (pan_id != EMBER_BROADCAST_PAN_ID) {
          break;
        }
      }
    }
  }

  *nwk_bit_mask = nwk_bits;
  return SL_STATUS_OK;
}

uint8_t sl_mac_get_nwk_index_matching_pan(uint8_t mac_index,
                                          uint8_t radio_channel,
                                          uint16_t pan_id)
{
  if (mac_index >= MAX_MAC_INDEX) {
    return 0xFF;
  }

  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + mac_index;
  for (uint8_t i = 0; i < SL_MAC_MAX_SUPPORTED_NETWORKS; i++) {
    sl_mac_radio_parameters_t *nwk_radio_params = state->nwk_radio_parameters + i;
    if ((nwk_radio_params->channel == radio_channel)
        && (pan_id == nwk_radio_params->pan_id)) {
      return i;
    }
  }
  return 0xFF;
}
#endif // EMBER_MULTI_NETWORK_STRIPPED

// Returns current sequence and bumps it for the next get
uint8_t sli_mac_get_next_sequence(void)
{
  return mac_outgoing_sequence_number++;
}
