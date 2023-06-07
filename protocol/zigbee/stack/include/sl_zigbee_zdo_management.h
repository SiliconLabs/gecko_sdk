/***************************************************************************//**
 * @file  sl_zigbee_zdo_management.h
 * @brief ZDO Management functionality described in R23 including performing
 * beacon surveys of Zigbee network
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_ZIGBEE_ZDO_MANAGEMENT_H
#define SL_ZIGBEE_ZDO_MANAGEMENT_H

#include "stack/include/ember-types.h"
#include "stack/include/sl_zigbee_stack_specific_tlv.h"

// NOTE we want to set a reasonable limit for the number of results we want to handle
extern uint8_t sli_zigbee_zdo_beacon_survey_unique_nwks;

// a cache to store potential parents
// NOTE this limit is imposed by the ZigBee spec (2.4.4.3.13)
#define BEACON_SURVEY_POTENTIAL_PARENTS_MAX_CANDIDATES 5

typedef struct {
  uint8_t total_beacons;
  uint8_t on_network_beacons;
  uint8_t potential_parent_beacons;
  uint8_t other_network_beacons;
} sl_zigbee_beacon_survey_results_t;

typedef struct {
  EmberNodeId short_id;
  // says lqa, really lqi
  uint8_t lqa;
} sl_zigbee_potential_parent_t;

typedef struct {
  EmberNodeId requester;
  uint8_t sequence;
  sl_zigbee_beacon_survey_results_t results;
  uint16_t observed_pan_ids[SL_ZIGBEE_ZDO_BEACON_SURVEY_MAX_UNIQUE_NETWORKS];
  EmberBeaconData potential_parents[BEACON_SURVEY_POTENTIAL_PARENTS_MAX_CANDIDATES];
} sl_zigbee_beacon_survey_data_t;

// Local Beacon Survey Configuration TLV
#define SLI_ZIGBEE_ZDO_BEACON_SURVEY_CONFIG_TLV_TAG_ID 0
#define SLI_ZIGBEE_ZDO_BEACON_SURVEY_CONFIG_TLV_MIN_LEN 5
#define SLI_ZIGBEE_ZDO_BEACON_SURVEY_CONFIG_TLV_MAX_LEN 6
typedef CONCRETE_TLV_DEFINE (SLI_ZIGBEE_ZDO_BEACON_SURVEY_CONFIG_TLV_MAX_LEN) sl_zigbee_local_tlv_beacon_survey_config_t;

#define SLI_ZIGBEE_ZDO_BEACON_SURVEY_RESULTS_TLV_TAG_ID 1
#define SLI_ZIGBEE_ZDO_BEACON_SURVEY_RESULTS_TLV_MIN_LEN 4
#define SLI_ZIGBEE_ZDO_BEACON_SURVEY_RESULTS_TLV_MAX_LEN 4
#define SLI_ZIGBEE_ZDO_BEACON_SURVEY_RESULTS_TLV_TOTAL_BEACONS_IDX 0
#define SLI_ZIGBEE_ZDO_BEACON_SURVEY_RESULTS_TLV_ON_NETWORK_BEACONS_IDX 1
#define SLI_ZIGBEE_ZDO_BEACON_SURVEY_RESULTS_TLV_POTENTIAL_PARENT_BEACONS_IDX 2
#define SLI_ZIGBEE_ZDO_BEACON_SURVEY_RESULTS_TLV_OTHER_NETWORK_BEACONS_IDX 3
typedef CONCRETE_TLV_DEFINE (SLI_ZIGBEE_ZDO_BEACON_SURVEY_RESULTS_TLV_MAX_LEN) sl_zigbee_local_tlv_beacon_survey_results_t;

#define SLI_ZIGBEE_ZDO_BEACON_SURVEY_POTENTIAL_PARENTS_TLV_TAG_ID 2
#define SLI_ZIGBEE_ZDO_BEACON_SURVEY_POTENTIAL_PARENTS_TLV_MIN_LEN 4
#define SLI_ZIGBEE_ZDO_BEACON_SURVEY_POTENTIAL_PARENTS_TLV_MAX_LEN 19
typedef CONCRETE_TLV_DEFINE (SLI_ZIGBEE_ZDO_BEACON_SURVEY_POTENTIAL_PARENTS_TLV_MAX_LEN) sl_zigbee_local_tlv_beacon_survey_potential_parent_t;

// channel field determines which channels to scan
#define BEACON_SURVEY_CONFIG_CHANNEL_BITMASK
// there is a 1-byte bitmask with a couple of fields
#define BEACON_SURVEY_CONFIG_BITMASK 0x01
#define BEACON_SURVEY_CONFIG_BITMASK_ENHANCED_SCAN BIT(0)

/**
 * @brief issues a survey beacon request to the given destination
 * @param dest the short id of the node intended to fulfill the request
 * @param channel_mask a mask representing the range of channels that should be scanned
 * @param scan_config_mask is a bitmask that helps configure the scan parameters for the survey
 * @note bit 1 indicates an enhanced scan
 * @return a status code indicating whether or not the request was sent successfully
 */
sl_status_t sl_zigbee_request_beacon_survey(EmberNodeId dest,
                                            uint8_t channel_page_count,
                                            uint32_t *channel_masks,
                                            uint8_t scan_config_mask);

/**
 * @brief application defined procedure called on completion of the ZDO beacon survey
 * @param status the status of handling the beacon survey response
 * @param survey_results the tallied results of the beacon survey
 * @param potential_parent_count the number of candidate parent beacons
 * @param potential_parents the potential_parent data received
 * @param pan_id_conflicts the number of recorded pan id conflicts in range
 */
extern void sl_zigbee_beacon_survey_complete_callback(EmberZdoStatus status,
                                                      sl_zigbee_beacon_survey_results_t *survey_results,
                                                      uint8_t potential_parent_count,
                                                      sl_zigbee_potential_parent_t *potential_parents,
                                                      uint16_t pan_id_conflicts);

#endif // SL_ZIGBEE_ZDO_MANAGEMENT_H
