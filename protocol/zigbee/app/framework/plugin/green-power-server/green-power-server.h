/***************************************************************************//**
 * @file
 * @brief APIs and defines for the Green Power Server plugin.
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

#ifndef _SILABS_GREEN_POWER_SERVER_H_
#define _SILABS_GREEN_POWER_SERVER_H_

/**
 * @defgroup green-power-server Green Power Server
 * @ingroup component cluster
 * @brief API and Callbacks for the Green Power Cluster Server Component
 *
 * A component implementing the server-side functionality of the Green Power cluster.
 *
 */

/**
 * @addtogroup green-power-server
 * @{
 */

// Key Types for MIC Calculations
#define EMBER_AF_GREEN_POWER_GP_SHARED_KEY 0
#define EMBER_AF_GREEN_POWER_GP_INDIVIDUAL_KEY 1

#define GREEN_POWER_SERVER_GPS_SECURITY_LEVEL_ATTRIBUTE_FIELD_INVOLVE_TC 0x08

#define GP_DEVICE_ANNOUNCE_SIZE 12

#define SIZE_OF_REPORT_STORAGE 82
#define COMM_REPLY_PAYLOAD_SIZE 30
#define GP_SINK_TABLE_RESPONSE_ENTRIES_OFFSET           (3)
#define EMBER_AF_ZCL_CLUSTER_GP_GPS_COMMISSIONING_WINDOWS_DEFAULT_TIME_S (180)
#define GP_ADDR_SRC_ID_WILDCARD (0xFFFFFFFF)
#define GPS_ATTRIBUTE_KEY_TYPE_MASK (0x07)
#define GP_PAIRING_CONFIGURATION_FIXED_FLAG (0x230)

#define GREEN_POWER_SERVER_MIN_REPORT_LENGTH (10)

// payload [0] = length of payload,[1] = cmdID,[2] = report id,[3] = 1st data value
#define FIX_SHIFT_REPORTING_DATA_POSITION_CONVERT_TO_PAYLOAD_INDEX          (3)
// In CAR GPD : payload [0] = reportId, payload[1] = first data point
#define CAR_DATA_POINT_OFFSET 1
#define GP_DEFAULT_LINK_KEY { 0x5A, 0x69, 0x67, 0x42, 0x65, 0x65, 0x41, 0x6C, 0x6C, 0x69, 0x61, 0x6E, 0x63, 0x65, 0x30, 0x39 }

typedef uint8_t GpsNetworkState;
#ifdef DOXYGEN_SHOULD_SKIP_THIS
enum GreenPowerServerGPSNodeState
#else
enum
#endif
{
  GREEN_POWER_SERVER_GPS_NODE_STATE_NOT_IN_NETWORK,
  GREEN_POWER_SERVER_GPS_NODE_STATE_IN_NETWORK
};

typedef uint8_t EmberAfGpServerSinkTableAccessType;
#ifdef DOXYGEN_SHOULD_SKIP_THIS
enum GreenPowerServerSinkTableAccessType
#else
enum
#endif
{
  GREEN_POWER_SERVER_SINK_TABLE_ACCESS_TYPE_REMOVE_GPD, // 0 : Remove GPD from Sink Table
  GREEN_POWER_SERVER_SINK_TABLE_ACCESS_TYPE_ADD_GPD,    // 1 : Add GPD in Sink Table

  GREEN_POWER_SERVER_SINK_TABLE_ACCESS_TYPE_UNKNOWN,
};

typedef uint8_t EmberSinkCommissionState;
#ifdef DOXYGEN_SHOULD_SKIP_THIS
enum GPSinkCommState
#else
enum
#endif
{
  GP_SINK_COMM_STATE_IDLE,
  GP_SINK_COMM_STATE_COLLECT_REPORTS,
  GP_SINK_COMM_STATE_SEND_COMM_REPLY,
  GP_SINK_COMM_STATE_WAIT_FOR_SUCCESS,
  GP_SINK_COMM_STATE_FINALISE_PAIRING,
  GP_SINK_COMM_STATE_PAIRING_DONE,
};

typedef uint8_t EmberSinkCommissioningTimeoutType;
#ifdef DOXYGEN_SHOULD_SKIP_THIS
enum CommissioningTimeoutType
#else
enum
#endif
{
  COMMISSIONING_TIMEOUT_TYPE_GENERIC_SWITCH = 0,
  COMMISSIONING_TIMEOUT_TYPE_MULTI_SENSOR = 1,
  COMMISSIONING_TIMEOUT_TYPE_COMMISSIONING_WINDOW_TIMEOUT = 2
}; // The commissioning timeout type.

typedef uint8_t EmberSinkPairingStatus;
#ifdef DOXYGEN_SHOULD_SKIP_THIS
enum PairingStatus
#else
enum
#endif
{
  SINK_PAIRING_STATUS_SUCCESS = 0,
  SINK_PAIRING_STATUS_FAILURE = 1,
  SINK_PAIRING_STATUS_IN_PROGRESS = 2,
  SINK_PAIRING_STATUS_FAIL_NO_MATCHING_FUNCTIONALITY = 3,
  SINK_PAIRING_STATUS_FAIL_ADDING_TRANSLATION = 4,
  SINK_PAIRING_STATUS_FAIL_NO_SPACE_IN_SINK_TABLE = 5,
  SINK_PAIRING_STATUS_FAIL_ENTRY_CORRUPTED = 6,
}; // The pairing status.

typedef uint8_t EmberPreSinkPairingCallbackSource;
#ifdef DOXYGEN_SHOULD_SKIP_THIS
enum PreSinkPairingCallbackSource
#else
enum
#endif
{
  GP_PRE_SINK_PAIRING_CALLBACK_SOURCE_UNKNOWN = 0,
  GP_PRE_SINK_PAIRING_CALLBACK_COMMISSONING_FINALIZE = 1,
  GP_PRE_SINK_PAIRING_CALLBACK_PAIRING_CONFIGURATION = 2,
}; // The source of presink callback.

typedef struct {
  bool sendGpPairingInUnicastMode;
  bool unicastCommunication;
  bool inCommissioningMode;
  bool proxiesInvolved;
  uint8_t endpoint;
} EmberAfGreenPowerServerCommissioningState;

typedef struct {
  uint8_t deviceId;
  const uint8_t * cmd;
}GpDeviceIdAndCommandMap;

typedef struct {
  uint8_t deviceId;
  uint8_t numberOfClusters;
  const uint16_t * cluster;
}GpDeviceIdAndClusterMap;

typedef struct {
  uint16_t clusterId;
  bool serverClient;
}ZigbeeCluster;

// Structure to hold the information from commissioning command when received
// and used for subsequent processing
typedef struct {
  EmberGpAddress                addr;
  // saved from the commissioning frame 0xE0
  uint8_t                       gpdfOptions;
  uint8_t                       gpdfExtendedOptions;
  EmberGpSinkType               communicationMode;
  uint8_t                       groupcastRadius;
  uint8_t                       securityLevel;
  EmberKeyData                  key;
  uint32_t                      outgoingFrameCounter;
  bool                          useGivenAssignedAlias;
  uint16_t                      givenAlias;
  EmberGpApplicationInfo        applicationInfo;
  uint8_t                       securityKeyType;

  // The memory space for holding the grouplist from GpPairingConfig command.
  // This is a octet string with format of {<1 byte length, <n bytes grouplist>}
  uint8_t                       groupList[GP_SIZE_OF_SINK_LIST_ENTRIES_OCTET_STRING];

  // data link to generic switch
  EmberGpSwitchInformation      switchInformationStruct;

  // multi-sensor and compact reporting,
  // data link to AppliDescriptionCmd (0xE4), one report descriptor (at a time)
  // total number of report the GPD sensor
  uint8_t                       totalNbOfReport;
  uint8_t                       numberOfReports;
  uint8_t                       lastIndex;
  uint8_t                       reportsStorage[SIZE_OF_REPORT_STORAGE];
  // state machine
  uint16_t                      gppShortAddress;
  EmberSinkCommissionState      commissionState;
  // Send GP Pairing bit for current commissioning
  bool                          doNotSendGpPairing;
  EmberPreSinkPairingCallbackSource preSinkCbSource;
} GpCommDataSaved;

typedef GpCommDataSaved EmberCommissioningGpd;

extern sl_zigbee_event_t emberAfPluginGreenPowerServerGenericSwitchCommissioningTimeoutEvent;
void emberAfPluginGreenPowerServerGenericSwitchCommissioningTimeoutEventHandler(sl_zigbee_event_t * event);
extern sl_zigbee_event_t emberAfPluginGreenPowerServerMultiSensorCommissioningTimeoutEvent;
void emberAfPluginGreenPowerServerMultiSensorCommissioningTimeoutEventHandler(sl_zigbee_event_t * event);
extern sl_zigbee_event_t emberAfPluginGreenPowerServerCommissioningWindowTimeoutEvent;
void emberAfPluginGreenPowerServerCommissioningWindowTimeoutEventHandler(sl_zigbee_event_t * event);
#define genericSwitchCommissioningTimeout (&emberAfPluginGreenPowerServerGenericSwitchCommissioningTimeoutEvent)
#define multiSensorCommissioningTimeout (&emberAfPluginGreenPowerServerMultiSensorCommissioningTimeoutEvent)
#define commissioningWindowTimeout (&emberAfPluginGreenPowerServerCommissioningWindowTimeoutEvent)

/**
 * @name API
 * @{
 */

/** @brief Get a GPD commissioning instance in a multiple GPD commissioning
 * session.
 *
 * The green power server can be configured to allow multiple GPDs to commission
 * within a commissioning session. Given a GPD instance address,
 * this function will find the currently-commissioning GPD instance.
 * This is a helpful indicator of the commissioning progress
 * of a given GPD when multi GPDS are commissioning in a commissioning window.
 *
 * @param gpdAddr GPD address Ver.: always
 *
 * @returns Information on the commissioning pointed by a structure
 * GpCommDataSaved type about the GPD.
 */
EmberCommissioningGpd * emberAfGreenPowerServerFindCommissioningGpdInstance(EmberGpAddress * gpdAddr);
/** @brief Delete a GPD commissioning instance in a multiple GPD commissioning
 * session.
 *
 * The green power server can be configured to allow multiple GPDs to commission
 * within a commissioning session. Given a GPD instance address,
 * this function will find and delete the currently-commissioning GPD instance.
 * This is a helpful way to remove unwanted GPD
 * instances in a multiple GPD commissioning session.
 *
 * @param gpdAddr GPD address Ver.: always
 *
 */
void emberAfGreenPowerServerDeleteCommissioningGpdInstance(EmberGpAddress * gpdAddr);
/** @brief Extend the commissioning window of a commissioning session.
 *
 * This is a helper function that sends out a proxy commissioning mode from the
 * server side to all proxies in the network. It internally uses the same
 * parameters used previously in the proxy commissioning mode with action =
 * enter.
 *
 * @param commissioningWindow Commissioning window to be extended from this
 * point in time in seconds Ver.: always
 *
 */
void emberAfGreenPowerClusterGpSinkCommissioningWindowExtend(uint16_t commissioningWindow);
/** @brief Get the commissioning state of the green power server.
 *
 * This function gets the commissioning state of the
 * green power server.
 *
 * @returns Server commissioning state and related parameters pointed by structure
 * EmberAfGreenPowerServerCommissioningState Ver.: always
 *
 */
EmberAfGreenPowerServerCommissioningState *emberAfGreenPowerClusterGetServerCommissioningSate(void);

/** @brief Derive the shared key from the sink attributes.
 *
 * This function derives the shared key used in green
 * power server side using the respective security attribute values.
 *
 * @param gpsSecurityKeyTypeAtrribute Security key type attribute as input
 * @param gpSharedKeyAttribute Security key attribute as output
 * @param gpdAddr GPD address
 *
 * @returns Status of the key derivation Ver.: always
 *
 */
EmberAfStatus emberAfGreenPowerServerDeriveSharedKeyFromSinkAttribute(uint8_t * gpsSecurityKeyTypeAtrribute,
                                                                      EmberKeyData * gpSharedKeyAttribute,
                                                                      EmberGpAddress * gpdAddr);
/** @brief Clears the entry for a GPD in sink table.
 *
 * This function clears the entries in the sink table for a given gpd.
 * In a sink table, there is unique entry for each GPD based on its addressing. When the
 * GPD addressing uses application id=0b000 with 32 bit sourceId, there is just one
 * entry for each GPD. But, when the GPD addressing with application Id=0b010 that is EUI64
 * with endpoint id, for each unique endpoint, there can be an entry in sink table. Hence,
 * when this function is called with application Id=0b010,EUI64 with endpoint id=0xff(all endpoints),
 * it clears all the entry for that GPD with supplied EUI64.
 * With clear up the gpd from sink table it also clears the translation table for that GPD.
 *
 * @param gpdAddr GPD address Ver.: always
 *
 *
 */
void emberAfGreenPowerServerRemoveSinkEntry(EmberGpAddress *gpdAddr);
/** @} */ // end of name API

/**
 * @name Callbacks
 * @{
 */

/**
 * @defgroup gp_server_cb Green Power Server
 * @ingroup af_callback
 * @brief Callbacks for Green Power Server Component
 *
 */

/**
 * @addtogroup gp_server_cb
 * @{
 */

/** @brief Green power server commissioning timeout callback.
 *
 * This function is called by the Green Power Server upon expiration of any of the
 * commissioning timers, which can be server commissioning window, generic
 * switch commissioning, or multi-sensor commissioning timer expiration.
 *
 * @param commissioningTimeoutType one of the types
 *                     COMMISSIONING_TIMEOUT_TYPE_COMMISSIONING_WINDOW_TIMEOUT,
 *                     COMMISSIONING_TIMEOUT_TYPE_GENERIC_SWITCH
 *                     or COMMISSIONING_TIMEOUT_TYPE_MULTI_SENSOR Ver.: always
 * @param numberOfEndpoints Number of sink endpoints participated in the commissioning Ver.: always
 * @param endpoints list of sink endpoints Ver.: always
 */
void emberAfGreenPowerServerCommissioningTimeoutCallback(uint8_t commissioningTimeoutType,
                                                         uint8_t numberOfEndpoints,
                                                         uint8_t * endpoint);

/** @brief Green power server pairing complete callback.
 *
 * This function is called by the Green Power Server upon the completion of the pairing
 * to indicate the closure of the pairing session.
 *
 * @param numberOfEndpoints number of sink endpoints participated in the pairing Ver.: always
 * @param endpoints list of sink endpoints Ver.: always
 */
void emberAfGreenPowerServerPairingCompleteCallback(uint8_t numberOfEndpoints,
                                                    uint8_t * endpoint);

/** @brief Sink table access notification callback.
 *
 * This function is called by the green power server plugin to notify the
 * application about Green Power Device addition or removal by the green power
 * server to the Sink Table. If returned false, the sink table remains un-accessed.
 *
 * @param data void pointer to the data Ver.: always
 * @param accessType accessType         Ver.: always
 *
 * @returns true if the access is granted.
 */
bool  emberAfPluginGreenPowerServerSinkTableAccessNotificationCallback(void* data,
                                                                       EmberAfGpServerSinkTableAccessType accessType);
/** @brief Green power server commissioning callback.
 *
 * This function is called by the green power server plugin to notify the
 * application of a Green Power Device that has requested commissioning with
 * this sink. Returns false if callback is not handled, true if callback is handled.
 * When the callback is handled, it must set the matchFound argument appropriately
 * to indicate if the matching functionality is found on the sink or not.
 *
 * @param appInfo   Application information of the commissioning GPD. Ver.: always
 * @param matchFound Output flag to notify matching functionality. Ver.: always
 *
 * @returns true if application handled it Ver.: always
 */
bool emberAfPluginGreenPowerServerGpdCommissioningCallback(EmberGpApplicationInfo * appInfo,
                                                           bool* matchFound);

/** @brief Green power server security failure callback.
 *
 * This function is called by the green power server plugin to notify the
 * application of a Green Power Security Processing failed for an incoming notification.
 *
 * @param gpdAddr   Ver.: always
 */
void emberAfPluginGreenPowerServerGpdSecurityFailureCallback(EmberGpAddress *gpdAddr);

/** @brief Green power server update involved TC callback.
 *
 * This function is called by the Green Power Server to proceed with updating the InvolveTC bit
 * of the security level attribute.
 *
 * @param status   Ver.: always
 *
 * @returns true if application handled it and plugin will not process it  Ver.: always
 */
bool emberAfGreenPowerServerUpdateInvolveTCCallback(EmberStatus status);

/** @brief Green power server notification forward callback.
 *
 * This function is called by the green power server plugin to notify the
 * application of a Green Power Gp Notification of an incoming gpd command.
 * Return true to handle in application.
 *
 * @param options from the incoming Gp Notification Command Ver.: always
 * @param addr GPD address        Ver.: always
 * @param gpdSecurityFrameCounter Ver.: always
 * @param gpdCommandId            Ver.: always
 * @param gpdCommandPayload first byte is length of the payload Ver.: always
 * @param gppShortAddress         Ver.: always
 * @param gppDistance             Ver.: always
 *
 * @returns true if application handled it and plugin will not process it anymore.
 * else return false to process the notification by the plugin  Ver.: always
 */
bool emberAfGreenPowerClusterGpNotificationForwardCallback(uint16_t options,
                                                           EmberGpAddress * addr,
                                                           uint32_t gpdSecurityFrameCounter,
                                                           uint8_t gpdCommandId,
                                                           uint8_t * gpdCommandPayload,
                                                           uint16_t gppShortAddress,
                                                           uint8_t  gppDistance);

/** @brief Green power commissioning notification callback.
 *
 * This function is called by the green power server plugin to notify the
 * application about gp commissioning notification received by the sink.
 * If the this function returns false indicating application does not handle
 * the notification, the plugin will handle. If this returns true, the plugin
 * will skip processing of the commissioning notification.
 *
 * @param commandId                    Ver.: always
 * @param commNotificationOptions      Ver.: always
 * @param gpdAddr                      Ver.: always
 * @param gpdSecurityFrameCounte       Ver.: always
 * @param gpdCommandId                 Ver.: always
 * @param gpdCommandPayload            Ver.: always
 * @param gppShortAddress              Ver.: always
 * @param rssi                         Ver.: always
 * @param linkQuality                  Ver.: always
 * @param gppDistance                  Ver.: always
 * @param commissioningNotificationMic Ver.: always
 *
 * @returns true if application handles it and plugin will not process it anymore.
 * else return false to process the notification by the plugin  Ver.: always
 */
bool emberAfPluginGreenPowerServerGpdCommissioningNotificationCallback(uint8_t commandId,
                                                                       uint16_t commNotificationOptions,
                                                                       EmberGpAddress *gpdAddr,
                                                                       uint32_t gpdSecurityFrameCounter,
                                                                       uint8_t gpdCommandId,
                                                                       uint8_t* gpdCommandPayload,
                                                                       uint16_t gppShortAddress,
                                                                       int8_t rssi,
                                                                       uint8_t linkQuality,
                                                                       uint8_t gppDistance,
                                                                       uint32_t commissioningNotificationMic);

/** @brief Sink commissioning enter call status notification callback.
 *
 * This function is called by the green power server plugin from the sink
 * commissioning enter command to notify the application of the status of the
 * proxy commissioning enter message submission to network layer.
 *
 * @param commissioningState Sink commissioning state Ver.: always
 * @param apsFrame aps frame header        Ver.: always
 * @param messageType unicast or broadcast Ver.: always
 * @param destination destination node     Ver.: always
 * @param status status of the network submission Ver.: always
 *
 */
void emberAfGreenPowerClusterCommissioningMessageStatusNotificationCallback(EmberAfGreenPowerServerCommissioningState *commissioningState,
                                                                            EmberApsFrame *apsFrame,
                                                                            EmberOutgoingMessageType messageType,
                                                                            uint16_t destination,
                                                                            EmberStatus status);

/** @brief Update alias information callback.
 *
 * This function is called by the green power server plugin during
 * commissioning to update alias information from user.
 *
 * @param gpdAddr GPD address Ver.: always
 * @param alias        Ver.: always
 *
 * @returns true if the alias is updated by the caller.
 */
bool emberAfPluginGreenPowerServerUpdateAliasCallback(EmberGpAddress *gpdAddr,
                                                      uint16_t *alias);
/** @brief Green power server pairing complete callback
 *
 * This function is called by the Green Power Server plugin during the pairing
 * process to indicate the status. This may be called multiple times for a single
 * pairing session. This provides the status as well as the current GPD context.
 * This callback can be monitored to get information in case a GPD commissioning
 * that has started ended up in success or failure. This callback does not give
 * any information about a commissioning GPDF that gets filtered out ealier in the
 * commissioning processing.
 *
 * @param status status of the pairing Ver.: always
 * @param commissioningGpd context of the GPD that is currently commissioning Ver.: always
 */
void emberAfGreenPowerServerPairingStatusCallback(EmberSinkPairingStatus status,
                                                  EmberCommissioningGpd *commissioningGpd);

/** @brief Green power server update sink list callback
 *
 * This callback is called by the green power server at a final stagee during pairing process.
 * At this point the commissioning sink is ready to be saved or updated into the sink table
 * and GpPairing announcement. This callback is helpful to supply or update the associated
 * parameters to the sink entry.
 * For example, a sink application can update a group list groupcast comminication.
 *
 *
 * @param commissioningGpd context of the GPD that is currently commissioning Ver.: always
 */
void emberAfPluginGreenPowerServerPreSinkPairingCallback(EmberCommissioningGpd *commissioningGpd);

/** @} */ // end of gp_server_cb
/** @} */ // end of name Callbacks

/** @} */ // end of green-power-server

extern EmberStatus ezspProxyBroadcast(EmberNodeId source,
                                      EmberNodeId destination,
                                      uint8_t nwkSequence,
                                      EmberApsFrame *apsFrame,
                                      uint8_t radius,
                                      uint8_t messageTag,
                                      uint8_t messageLength,
                                      uint8_t *messageContents,
                                      uint8_t *apsSequence);

/*
 * Disable default response bit should be set per GP Spec 14-0563-08
 */
extern bool emberAfGreenPowerClusterGpProxyCommissioningModeCallback(EmberAfClusterCommand *cmd);

// security function prototypes
bool sli_zigbee_af_gp_key_tc_lk_derivation(EmberGpAddress * gpdAddr,
                                           uint32_t gpdSecurityFrameCounter,
                                           uint8_t mic[4],
                                           EmberKeyData * key,
                                           bool directionIncomming);
bool sli_zigbee_af_gp_calculate_incoming_command_mic(EmberGpAddress * gpdAddr,
                                                     bool rxAfterTx,
                                                     uint8_t keyType,
                                                     uint8_t securityLevel,
                                                     uint32_t gpdSecurityFrameCounter,
                                                     uint8_t gpdCommandId,
                                                     uint8_t * gpdCommandPayload,
                                                     bool encryptedPayload,
                                                     uint8_t mic[4]);
bool sli_zigbee_af_gp_calculate_incoming_command_decrypt(EmberGpAddress * gpdAddr,
                                                         uint32_t gpdSecurityFrameCounter,
                                                         uint8_t payloadLength,
                                                         uint8_t * payload);
uint8_t sli_zigbee_af_gp_outgoing_command_encrypt(EmberGpAddress * gpdAddr,
                                                  uint32_t gpdSecurityFrameCounter,
                                                  uint8_t keyType,
                                                  uint8_t securityLevel,
                                                  uint8_t gpdCommandId,
                                                  uint8_t * gpdCommandPayload,
                                                  uint8_t * securedOutgoingGpdf,
                                                  uint8_t securedOutgoingGpdfMaxLength);
// gp security test function
EmberStatus sli_zigbee_af_gp_test_security(void);

EmberAfStatus sli_zigbee_af_gp_add_to_aps_group(uint8_t endpoint, uint16_t groupId);
// GP helper functions
bool sli_zigbee_af_gp_endpoint_and_cluster_id_validation(uint8_t endpoint,
                                                         bool server,
                                                         EmberAfClusterId clusterId);
const uint8_t * sli_zigbee_af_gp_find_report_id(uint8_t reportId,
                                                uint8_t numberOfReports,
                                                const uint8_t * reports);
uint8_t sli_zigbee_af_get_command_list_from_device_id_lookup(uint8_t gpdDeviceId,
                                                             uint8_t * gpdCommandList);
uint8_t sli_zigbee_af_get_cluster_list_from_device_id_lookup(uint8_t gpdDeviceId,
                                                             ZigbeeCluster * gpdClusterList);
bool sli_zigbee_af_get_cluster_list_from_cmd_id_lookup(uint8_t gpdCommandId,
                                                       ZigbeeCluster * gpdCluster);
void sli_zigbee_af_gp_forward_gpd_command_default(EmberGpAddress *addr,
                                                  uint8_t gpdCommandId,
                                                  uint8_t *gpdCommandPayload);
void emberAfGreenPowerServerSinkTableInit(void);

bool isCommissioningAppEndpoint(uint8_t endpoint);

#endif //_GREEN_POWER_SERVER_H_
