/***************************************************************************//**
 * @brief Bluetooth Link Layer configuration API
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef _SL_BTCTRL_LINKLAYER_H_
#define _SL_BTCTRL_LINKLAYER_H_
#include "sl_status.h"
#include <stdint.h>

void sl_bt_controller_init(void);

void sl_bt_controller_deinit(void);

void sl_btctrl_init(void);

/**
 * Allocate memory buffers for controller
 *
 * @param memsize size of memory to allocate
 * @returns number of memory buffers allocated
 */
uint32_t sl_btctrl_init_mem(uint32_t memsize);

/**
 *  Configures how many maximum sized ACL data packets
 *  can the controller store.
 */
void sl_btctrl_configure_le_buffer_size(uint8_t count);

/**
 * Release all memory allocated by controller
 */
void sli_btctrl_deinit_mem(void);

void sli_btctrl_set_interrupt_priorities();

sl_status_t sl_btctrl_init_ll(void);

void sli_btctrl_set_address(uint8_t *address);

//Initialize memory objects used by LinkLayer
//In future these should be configured individually
sl_status_t sl_btctrl_init_basic(uint8_t connections, uint8_t adv_sets, uint8_t whitelist);

void sli_btctrl_events_init(void);

enum sl_btctrl_channelmap_flags{
  SL_BTCTRL_CHANNELMAP_FLAG_ACTIVE_ADAPTIVITY = 0x01,
  SL_BTCTRL_CHANNELMAP_FLAG_PASSIVE_ADAPTIVITY= 0x02,
};

/**
 * Initialize and enable adaptive frequency hopping
 */
sl_status_t sl_btctrl_init_afh(uint32_t flags);

/**
 * Enable high power use under appropriate conditions
 */
void sl_btctrl_init_highpower(void);

/**
 * @brief Initilize periodic advertiser
 */
void sl_btctrl_init_periodic_adv();

/**
 * @brief Initilize periodic advertiser
 */
void sl_btctrl_init_periodic_scan();

/**
 * Configuration for Periodic Advertising with Responses.
 */
struct sl_btctrl_pawr_advertiser_config {
  /**
   * Number of advertising sets supporting PAwR.
   * If set to zero, previously allocated PAwR sets are only freed. */
  uint8_t max_pawr_sets;
  /**
   * Hint to the controller what will be the maximum advertised data length.
   * The value does not prevent using longer advertising data. Value zero means
   * that maximum data length can expected to be up to the length of Periodic
   * Advertising Delay. */
  uint8_t max_advertised_data_length_hint;
  /**
   * The number of subevent advertising packets requested from the host
   * at once. */
  uint8_t subevent_data_request_count;
  /**
   * How many subevents before airing a subevent its data is requested from
   * the host. */
  uint8_t subevent_data_request_advance;
};

/**
 * Configuration of synchronizer for Periodic Advertising with Responses.
 */
struct sl_btctrl_pawr_synchronizer_config {
  /**
   * Number of advertising sets supporting PArR.
   * If set to zero, previously allocated PArR sets are only freed. */
  uint8_t max_pawr_sets;
};

/**
 * @brief Enable and initialize support for the PAwR advertiser.
 * @param[in] pawr_adv_config PAwR advertiser configuration.
 * @return SL_STATUS_OK, or an appropriate error code. */
sl_status_t sl_btctrl_pawr_advertiser_configure(struct sl_btctrl_pawr_advertiser_config *pawr_adv_config);

/**
 * @brief Enable and initialize support for PAwR sync/receiver.
 * @param[in] pawr_sync_config PAwR synchronizer configuration.
 * @return SL_STATUS_OK, or an appropriate error code. */
sl_status_t sl_btctrl_pawr_synchronizer_configure(struct sl_btctrl_pawr_synchronizer_config *pawr_sync_config);

/**
 * @brief Allocate memory for synchronized scanners
 *
 * @param num_scan Number of Periodic Scanners Allowed
 * @return SL_STATUS_OK if allocation was succesfull, failure reason otherwise
 */
sl_status_t sl_btctrl_alloc_periodic_scan(uint8_t num_scan);

/**
 * @brief Allocate memory for periodic advertisers
 *
 * @param num_adv Number of advertisers to allocate
 */
sl_status_t sl_btctrl_alloc_periodic_adv(uint8_t num_adv);

/**
 * Call to import the conn scheduler state variables in the binary
 */
void sli_btctrl_enable_conn_scheduler_state(void);

/**
 * @brief Set maximum number of advertisement reports allowed to be queued
 *
 * @param num_adv Maximum number of advertisement reports allowed to be queued
 */
void sl_btctrl_configure_max_queued_adv_reports(uint8_t num_reports);

/**
 * Call to enable the even connection scheduling algorithm.
 * This function should be called before link layer initialization.
 */
void sl_btctrl_enable_even_connsch();

/**
 * Call to enable the PAwR aware connection scheduling algorithm.
 * This function should be called before link layer initialization.
 */
void sl_btctrl_enable_pawr_connsch();

/**
 * Call to enable the legacy connection scheduling algorithm.
 * This function should be called before link layer initialization.
 */
void sl_btctrl_enable_legacy_connsch();

/**
 * Call to enable connection statistics collection.
 */
void sl_btctrl_init_conn_statistics(void);

/**
 * Call to initialize multiprotocol
 * in bluetooth controller
 */
void sl_btctrl_init_multiprotocol();

/**
 * Link with symbol to enable radio watchdog
 */
void sl_btctrl_enable_radio_watchdog();

/**
 * Initialize CTE receiver
 */
sl_status_t sl_btctrl_init_cte_receiver();

/**
 * Initialize CTE transmitter
 */
sl_status_t sl_btctrl_init_cte_transmitter();

/**
 * Initialize both CTE receiver and transmitter
 *
 * Note: This is for backward compatibility. It is recommend to
 * use sl_btctrl_init_cte_receiver and sl_btctrl_init_cte_transmitter
 * functions instead.
 */
sl_status_t sl_btctrl_init_cte();

/**
 * Initialize Channel Sounding
 */
struct sl_btctrl_cs_config {
  /** number of channel sounding configurations per connection */
  uint8_t configs_per_connection;
  /** number of simultaneous channel sounding procedures */
  uint8_t procedures;
};

sl_status_t sl_btctrl_init_cs(const struct sl_btctrl_cs_config *config);

/**
 * Check if event bitmap indicates pending events
 * @return bool pending events
 */
bool sli_pending_btctrl_events(void);

/**
 * Disable the support for Coded and Simulscan PHYs.
 */
void sl_btctrl_disable_coded_phy(void);

/**
 * Disable the support for 2M PHY.
 */
void sl_btctrl_disable_2m_phy(void);

/**
 * Initialize adv component
 */
void sl_btctrl_init_adv(void);

void sl_btctrl_init_conn(void);

void sl_btctrl_init_phy(void);

void sl_btctrl_init_adv_ext(void);

void sl_btctrl_init_privacy(void);

sl_status_t sl_btctrl_allocate_resolving_list_memory(uint8_t resolvingListSize);

/**
 * @brief Initialize extended scanner state
 *
 */
void sl_btctrl_init_scan_ext(void);

void sl_btctrl_init_scan(void);

/**
 * @brief return true if controller is initialized
 *
 */
bool sl_btctrl_is_initialized();

/**
 * @brief Sets PAST initiator feature bit,
 * and links in PAST sender and ll_adv_sync symbols to the project.
 */
void sl_btctrl_init_past_local_sync_transfer(void);

/**
 * @brief Sets PAST initiator feature bit,
 * and links in PAST sender, ll_scan_sync and ll_scan_sync_registry symbols to the project.
 */
void sl_btctrl_init_past_remote_sync_transfer(void);

/**
 * @brief Sets PAST receiver feature bit,
 * and links in PAST receiver, ll_scan_sync and ll_scan_sync_registry symbols to the project.
 */
void sl_btctrl_init_past_receiver(void);

/**
 * @brief Configure how often to send the Number Of Completed Packets HCI event.
 * @param[in] packets When the controller has transmitted this number of ACL data packets it will send
 * the Number Of Completed Packets HCI event to the host.
 * @param[in] events When this number of connection events have passed and the controller did not yet report
 * all the transmitted packets, then it will send the Number Of Completed Packets HCI event to the host.
 */
void sl_btctrl_configure_completed_packets_reporting(uint8_t packets, uint8_t events);

#endif
