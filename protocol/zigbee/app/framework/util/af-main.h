/***************************************************************************//**
 * @file
 * @brief
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

#ifndef SILABS_AF_MAIN_H
#define SILABS_AF_MAIN_H

#include CONFIGURATION_HEADER
#include PLATFORM_HEADER     // Micro and compiler specific typedefs and macros
#include "stack/include/ember-types.h"

#define MFG_STRING_MAX_LENGTH 16

typedef struct {
  EmberAfMessageSentFunction callback;
  uint16_t tag;
} CallbackTableEntry;

#if defined(EZSP_HOST)
bool emberAfMemoryByteCompare(const uint8_t* pointer, uint8_t count, uint8_t byteValue);
#else
bool sli_zigbee_af_memory_byte_compare(const uint8_t *bytes, uint8_t count, uint8_t target);

#define emberAfMemoryByteCompare(pointer, count, byteValue) \
  sli_zigbee_af_memory_byte_compare((pointer), (count), (byteValue))
#endif

// returnData must be MFG_STRING_MAX_LENGTH in length and
// is NOT expected to be NULL terminated (could be though)
void emberAfGetMfgString(uint8_t* returnData);

// Functions common to both SOC and Host versions of the application.
void sli_zigbee_af_initialize_message_sent_callback_array(void);
uint8_t sli_zigbee_get_permit_joining_remaining_duration_sec(void);

EmberAfCbkeKeyEstablishmentSuite emberAfIsFullSmartEnergySecurityPresent(void);

#if defined(EZSP_HOST)
void sli_zigbee_af_clear_network_cache(uint8_t networkIndex);
#else
  #define sli_zigbee_af_clear_network_cache(index)
uint8_t sli_zigbee_af_copy_message_into_ram_buffer(EmberMessageBuffer message,
                                                   uint8_t *buffer,
                                                   uint16_t bufLen);
#endif

#if defined EZSP_HOST
// utility for setting an EZSP config value and printing the result
EzspStatus emberAfSetEzspConfigValue(EzspConfigId configId,
                                     uint16_t value,
                                     const char * configIdName);

// utility for setting an EZSP policy and printing the result
EzspStatus emberAfSetEzspPolicy(EzspPolicyId policyId,
                                EzspDecisionId decisionId,
                                const char * policyName,
                                const char * decisionName);

// utility for setting an EZSP value and printing the result
EzspStatus emberAfSetEzspValue(EzspValueId valueId,
                               uint8_t valueLength,
                               uint8_t *value,
                               const char * valueName);

bool emberAfNcpNeedsReset(void);

#endif // EZSP_HOST

void sli_zigbee_af_print_status(const char * task,
                                EmberStatus status);

uint8_t emberAfGetSecurityLevel(void);
uint8_t emberAfGetKeyTableSize(void);
uint8_t emberAfGetBindingTableSize(void);
uint8_t emberAfGetAddressTableSize(void);
uint8_t emberAfGetChildTableSize(void);
uint8_t emberAfGetRouteTableSize(void);
uint8_t emberAfGetNeighborTableSize(void);
uint8_t emberAfGetStackProfile(void);
uint8_t emberAfGetSleepyMulticastConfig(void);

uint8_t sli_zigbee_af_get_packet_buffer_free_count(void);
uint8_t sli_zigbee_af_get_packet_buffer_total_count(void);
uint8_t emberAfGetOpenNetworkDurationSec(void);

EmberStatus emberAfGetSourceRouteTableEntry(
  uint8_t index,
  EmberNodeId *destination,
  uint8_t *closerIndex);

uint8_t emberAfGetSourceRouteTableTotalSize(void);
uint8_t emberAfGetSourceRouteTableFilledSize(void);

EmberStatus emberAfGetChildData(uint8_t index,
                                EmberChildData* childData);

void sli_zigbee_af_cli_version_command(void);

EmberStatus sli_zigbee_af_permit_join(uint8_t duration,
                                      bool broadcastMgmtPermitJoin);
void sli_zigbee_af_stop_smart_energy_startup(void);

bool sli_zigbee_af_process_zdo(EmberNodeId sender,
                               EmberApsFrame* apsFrame,
                               uint8_t* message,
                               uint16_t length);

void sli_zigbee_af_incoming_message_handler(EmberIncomingMessageType type,
                                            EmberApsFrame *apsFrame,
                                            uint8_t lastHopLqi,
                                            int8_t lastHopRssi,
                                            uint16_t messageLength,
                                            uint8_t *messageContents);
EmberStatus sli_zigbee_af_send(EmberOutgoingMessageType type,
                               uint16_t indexOrDestination,
                               EmberApsFrame *apsFrame,
                               uint8_t messageLength,
                               uint8_t *message,
                               uint16_t *messageTag,
                               EmberNodeId alias,
                               uint8_t sequence);
void sli_zigbee_af_message_sent_handler(EmberOutgoingMessageType type,
                                        uint16_t indexOrDestination,
                                        EmberApsFrame *apsFrame,
                                        EmberStatus status,
                                        uint16_t messageLength,
                                        uint8_t *messageContents,
                                        uint16_t messageTag);

void sli_zigbee_af_stack_status_handler(EmberStatus status);

void sli_zigbee_af_network_security_init(void);
void sli_zigbee_af_network_init(uint8_t init_level);

void sli_zigbee_af_schedule_find_and_rejoin_event(void);

extern const EmberEUI64 emberAfNullEui64;

void emberAfFormatMfgString(uint8_t* mfgString);

extern bool emberAfPrintReceivedMessages;

void sli_zigbee_af_parse_and_print_version(EmberVersion versionStruct);
void sli_zigbee_af_print_ezsp_endpoint_flags(uint8_t endpoint);

uint16_t sli_zigbee_af_calculate_message_tag_hash(uint8_t *messageContents,
                                                  uint8_t messageLength);
bool sli_zigbee_af_get_endpoint_description(uint8_t endpoint,
                                            EmberEndpointDescription *result);
uint16_t sli_zigbee_af_get_endpoint_cluster(uint8_t endpoint,
                                            EmberClusterListId listId,
                                            uint8_t listIndex);
uint8_t sli_zigbee_af_get_endpoint(uint8_t index);

// Old names
#define emberAfMoveInProgress() emberAfMoveInProgressCallback()
#define emberAfStartMove()      emberAfStartMoveCallback()
#define emberAfStopMove()       emberAfStopMoveCallback()

#endif // SILABS_AF_MAIN_H
