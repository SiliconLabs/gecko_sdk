/**
 * @file
 * @brief Transport layer for Multi Channel endpoint functionality.
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _ZW_TRANSPORTENDPOINT_H_
#define _ZW_TRANSPORTENDPOINT_H_

#include <ZW_classcmd.h>
#include <ZW_security_api.h>
#include <ZW_transport_api.h>
#include <ZAF_types.h>

/**
 * @addtogroup ZAF
 * @{
 * @addtogroup ZAF_Transport
 * @{
 * @addtogroup ZAF_Transport_Endpoint
 * @{
 */

/**
* Defines return values for ZAF_Transmit.
* They match the enum values defined in EQueueNotifyingStatus (i.e.,
* EQUEUENOTIFYING_STATUS_SUCCESS and EQUEUENOTIFYING_STATUS_TIMEOUT, respectively).
*/
typedef enum
{
  ZAF_ENQUEUE_STATUS_SUCCESS = 0, /**< Item successfully put on queue */
  ZAF_ENQUEUE_STATUS_TIMEOUT = 1, /**< Failed to put item on queue as it was full. Queue remained full until timeout */
  ZAF_ENQUEUE_STATUS_BUFFER_OVERRUN = 2  /**< Failed to put item on queue as it was to long to fit in tx buffer */
} EZAF_EnqueueStatus_t;

/**
 * MULTICHAN_NODE_INFO should include feature node informations as CRC, security etc.
 */
typedef struct _MULTICHAN_NODE_INFO_
{
  uint8_t BitMultiChannelEncap; /**< uint8_t 0, bit 0 */
  security_key_t security; /**< of type security_key_t*/
} MULTICHAN_NODE_INFO;

typedef struct _MULTICHAN_NODE_INFO_PACKED_
{
  uint8_t security             : 4; /**< bit 0-3 of type security_key_t: 0-NON_KEY,1-S2_UNAUTHENTICATED,
                                      2-S2_AUTHENTICATED, 3-S2_ACCESS, 4-S0 (security_key_t)*/
  uint8_t unused               : 1; /**< bit 4 */
  uint8_t BitMultiChannelEncap : 1; /**< bit 5 */
  uint8_t unused2              : 1; /**< bit 6 */
  uint8_t unused3              : 1; /**< bit 7 */
} MULTICHAN_NODE_INFO_PACKED;

/**
 * Association node data field in a association group.
 */
typedef struct
{
  MULTICHAN_DEST_NODE_ID node;
  MULTICHAN_NODE_INFO    nodeInfo;
}
destination_info_t;

typedef destination_info_t MULTICHAN_NODE_ID;

typedef struct
{
  MULTICHAN_DEST_NODE_ID_8bit  node;    // We cannot store 16bit NodeIDs in the NVM, because of backwards compatibility!
  MULTICHAN_NODE_INFO_PACKED   nodeInfoPacked;
} MULTICHAN_NODE_ID_PACKED;

/* Transmit options for ZW_SendDataEx */
typedef struct _TRANSMIT_OPTIONS_TYPE_EX_ {
  uint8_t S2_groupID;
  uint8_t txOptions;
  uint8_t sourceEndpoint;
  MULTICHAN_NODE_ID *pList;
  uint8_t list_length;
} TRANSMIT_OPTIONS_TYPE_EX;

/* Transmit options for ZW_SendDataEx */
typedef struct _TRANSMIT_OPTIONS_TYPE_SINGLE_EX_ {
  uint8_t txOptions;
  uint8_t txSecOptions; /**< Options for enabling specific Security scheme functionality */
  uint8_t sourceEndpoint;
  MULTICHAN_NODE_ID* pDestNode;
} TRANSMIT_OPTIONS_TYPE_SINGLE_EX;

typedef enum _ENDPOINT_
{
  ENDPOINT_ROOT = 0,
  ENDPOINT_1,
  ENDPOINT_2,
  ENDPOINT_3,
  ENDPOINT_4,
  ENDPOINT_5,
  ENDPOINT_6,
  ENDPOINT_7,
  ENDPOINT_8,
  ENDPOINT_9
} ENDPOINT;

/**
 * Initializes the ZAF Transport Layer.
 */
void ZW_TransportEndpoint_Init(void);

/**
 * @brief Get endpoint non-secure or secure command class list.
 * @param[in] secList true if secure list else false for non-secure list
 * @param[in] endpoint parameter
 * @return Return endpoint command class list. Return NULL if list is not present!
 */
zaf_cc_list_t*
GetEndpointcmdClassList( bool secList, uint8_t endpoint);

/**
 * @brief Send data. This function is used both as response to a command and for sending unsolicited frames
 * Encapsulate data for endpoint support and call protocol ZW_SendDataEx.
 *
 * @param[in] pData IN Data buffer pointer.
 * @param[in] dataLength IN Data buffer length.
 * @param[in] pTxOptionsEx transmit options pointer.
 * @param[out] pCallback is a callback function-pointer returning result of the job. Please note that both
 *             bStatus TRANSMIT_COMPLETE_OK and TRANSMIT_COMPLETE_VERIFIED indicates successful transmission.
 * @return status of enum type EZAF_EnqueueStatus_t
 */
EZAF_EnqueueStatus_t
ZAF_Transmit(
  uint8_t *pData,
  size_t   dataLength,
  TRANSMIT_OPTIONS_TYPE_SINGLE_EX *pTxOptionsEx,
  ZAF_TX_Callback_t pCallback);

/**
 * Invokes a command class handler based on the first byte in the frame.
 *
 * Must be defined in the application.
 *
 * @deprecated If all command classes use one of the REGISTER_CC macros, this function is not
 *             required to be implemented in the application. There exists a weak definition of it.
 *             ZAF_CC_Invoker will take care of invoking the right command class handler.
 *
 * @param[in] rxOpt IN receive options of type RECEIVE_OPTIONS_TYPE_EX.
 * @param[in] pCmd IN  Payload from the received frame.
 * @param[in] cmdLength IN  Number of command bytes including command.
 * @return status of extracting frame
 */
received_frame_status_t
Transport_ApplicationCommandHandlerEx(
  RECEIVE_OPTIONS_TYPE_EX *rxOpt,
  ZW_APPLICATION_TX_BUFFER *pCmd,
  uint8_t   cmdLength);


/**
 * @brief Helper function to switching endpoints for SendData.
 * @param[in] rxopt Receive options to convert.
 * @param[out] txopt Converted transmit options
 */
void
RxToTxOptions( RECEIVE_OPTIONS_TYPE_EX *rxopt,
               TRANSMIT_OPTIONS_TYPE_SINGLE_EX **txopt);


/**
 * @brief Validate destination endpoint use bit-addressing. This function must only
 * be used to check jobs that return response (Get <-> Report).
 * @param[in] rxOpt pointer of type RECEIVE_OPTIONS_TYPE_EX
 * @return Boolean true if use bit-addressing else false
 */
bool
Check_not_legal_response_job(RECEIVE_OPTIONS_TYPE_EX *rxOpt);


/**
 * @brief This function indicates if the frame was received using multicast addressing
 * The Z-Wave Multicast frame, the broadcast NodeID and the Multi Channel multi-End
 * Point destination are all considered multicast addressing methods.
 * 
 * @param[in] rxOpt pointer of type RECEIVE_OPTIONS_TYPE_EX
 * @return Boolean true if use bit-addressing else false
 */
bool is_multicast(RECEIVE_OPTIONS_TYPE_EX *rxOpt);

/**
 * @brief Set supervision-encapsulated-frame flag. The Command class call Check_not_legal_response_job()
 * Use the flag to discard current job if a Get<->Response job (CC:006C.01.00.13.002).
 * @param[in] flag supervision-encapsulated-frame true if active and false if deactive.
 */
void
SetFlagSupervisionEncap(bool flag);

/**
 * @} // ZAF_Transport_Endpoint
 * @} // ZAF_Transport
 * @} // ZAF
 */

#endif /* _ZW_TRANSPORTENDPOINT_H_ */

