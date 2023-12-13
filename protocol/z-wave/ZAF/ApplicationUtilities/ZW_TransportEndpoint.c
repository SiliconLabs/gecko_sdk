/**
* @file ZW_TransportEndpoint.c
* @copyright 2018 Silicon Laboratories Inc.
* @brief Transport layer for Multi Channel endpoint functionality
*
*/

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include <string.h>
#include <ZW_transport_api.h>
#include <multichannel.h>
#include <ZW_TransportLayer.h>
#include <misc.h>
//#define DEBUGPRINT
#include "DebugPrint.h"
#include <ZW_TransportEndpoint.h>
#include <ZW_application_transport_interface.h>
#include <ZAF_Common_helper.h>
#include <ZAF_Common_interface.h>
#include <QueueNotifying.h>
#include "ZAF_types.h"
#include "ZAF_CC_Invoker.h"
#include <zaf_cc_list_generator.h>
#include "zaf_transport_tx.h"
#include "zaf_config_api.h"

/* Ensuring that we use the same enum definition for EZAF_EnqueueStatus_t and EQueueNotifyingStatus */
STATIC_ASSERT((ZAF_ENQUEUE_STATUS_SUCCESS == (EZAF_EnqueueStatus_t)EQUEUENOTIFYING_STATUS_SUCCESS) &&
              (ZAF_ENQUEUE_STATUS_TIMEOUT == (EZAF_EnqueueStatus_t)EQUEUENOTIFYING_STATUS_TIMEOUT),
              STATIC_ASSERT_FAILED_EZAF_EnqueueStatus_t_define_error);

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

#define QUEUE_NOTIFYING_SEND_MAX_WAIT  4000  /* [ms] Due to limitations in RAM, the allocated amount of frames with
                                              * follow-ups are limited to the queue size determined by application with
                                              * APP_EVENT_QUEUE_SIZE, and this will halt certain operations if
                                              * QUEUE_NOTIFYING_SEND_MAX_WAIT is set to zero.
                                              * See the detailed description above. */


typedef struct {
  uint8_t flag_supervision_encap;
  zaf_cc_list_t emptyList;
} CTransportEndpoint_t;

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/
static CTransportEndpoint_t myTransportEndpoint =
{
  false,
  {
    .cc_list = NULL,
    .list_size = 0
  }
};

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/

void ZW_TransportEndpoint_Init(void)
{
  myTransportEndpoint.flag_supervision_encap = false;
}

uint8_t eKeyToBitKey[] =
{
  0x00, SECURITY_KEY_S2_UNAUTHENTICATED_BIT, SECURITY_KEY_S2_AUTHENTICATED_BIT, SECURITY_KEY_S2_ACCESS_BIT, SECURITY_KEY_S0_BIT
};

uint8_t ConvertEnumKeytoBitKey(enum SECURITY_KEY eKey)
{
  return eKeyToBitKey[eKey];
}

/*============================ GetEndpointcmdClassList ======================
**-------------------------------------------------------------------------*/
zaf_cc_list_t*
GetEndpointcmdClassList( bool secList, uint8_t endpoint)
{
  zaf_cc_list_t *unsecure_included_cc;
  zaf_cc_list_t *secure_included_unsecure_cc;
  zaf_cc_list_t *secure_included_secure_cc;

  if((endpoint > zaf_config_get_number_of_endpoints()) || (0 == endpoint))
  {
    return NULL;
  }

  zafi_cc_list_generator_get_lists(endpoint, &unsecure_included_cc, &secure_included_unsecure_cc, &secure_included_secure_cc);

  if(SECURITY_KEY_NONE == GetHighestSecureLevel(ZAF_GetSecurityKeys()))
  {
    /*Non-secure included*/
    if(false == secList){
      return unsecure_included_cc;
    }
    else {
      return &(myTransportEndpoint.emptyList);
    }
  }
  else{
    /*Secure included*/
    if(false == secList){
      return secure_included_unsecure_cc;
    }
    else {
      return secure_included_secure_cc;
    }
  }
  return NULL;
}

EZAF_EnqueueStatus_t
ZAF_Transmit(
  uint8_t *pData,
  size_t   dataLength,
  TRANSMIT_OPTIONS_TYPE_SINGLE_EX *pTxOptionsEx,
  __attribute__((unused)) ZAF_TX_Callback_t pCallback)
{
  if (EINCLUSIONSTATE_EXCLUDED == ZAF_GetInclusionState())
  {
    // We are not network included. Nothing to do.
    DPRINTF("\r\n%s: Not network included - nothing to do.\r\n", __func__);
    return ZAF_ENQUEUE_STATUS_SUCCESS;
  }

  EZAF_EnqueueStatus_t result;

  // Check for multi channel
  if(false == pTxOptionsEx->pDestNode->nodeInfo.BitMultiChannelEncap)
  {
    pTxOptionsEx->sourceEndpoint = 0;
  }

  if (IS_NULL(pTxOptionsEx))
  {
    return ZAF_ENQUEUE_STATUS_TIMEOUT;
  }

  //Safeguard against buffer overflow
  if (TX_BUFFER_SIZE < dataLength)
  {
    return ZAF_ENQUEUE_STATUS_BUFFER_OVERRUN;
  }

  CmdClassMultiChannelEncapsulate(&pData,
                                  &dataLength,
                                  pTxOptionsEx);

  SZwaveTransmitPackage FramePackage =  {
    .uTransmitParams.SendDataEx.DestNodeId = pTxOptionsEx->pDestNode->node.nodeId,
    .uTransmitParams.SendDataEx.FrameConfig.TransmitOptions = pTxOptionsEx->txOptions,
    .uTransmitParams.SendDataEx.FrameConfig.iFrameLength = (uint8_t)dataLength,
    .uTransmitParams.SendDataEx.SourceNodeId = 0x0000,
    .uTransmitParams.SendDataEx.TransmitOptions2 = 0x00,
    .uTransmitParams.SendDataEx.TransmitSecurityOptions = pTxOptionsEx->txSecOptions,
    .uTransmitParams.SendDataEx.eKeyType = pTxOptionsEx->pDestNode->nodeInfo.security,
    .eTransmitType = EZWAVETRANSMITTYPE_EX
  };
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
  FramePackage.uTransmitParams.SendDataEx.FrameConfig.Handle = (ZW_TX_Callback_t)pCallback;
#pragma GCC diagnostic pop
  memcpy(FramePackage.uTransmitParams.SendDataEx.FrameConfig.aFrame, pData, dataLength);



  // Put the package on queue (and don't wait for it)
  result = (EZAF_EnqueueStatus_t)QueueNotifyingSendToBack(ZAF_getZwTxQueue(), (uint8_t*)&FramePackage, QUEUE_NOTIFYING_SEND_MAX_WAIT);
  return result;
}

void Transport_ApplicationCommandHandler(
    ZW_APPLICATION_TX_BUFFER * pCmd,
    uint8_t cmdLength,
    RECEIVE_OPTIONS_TYPE * rxOpt)
{
  RECEIVE_OPTIONS_TYPE_EX rxOptEx = {
    .rxStatus = rxOpt->rxStatus,
    .securityKey = rxOpt->securityKey,
    .sourceNode.nodeId = rxOpt->sourceNode,
    .sourceNode.endpoint = 0,
    .destNode.nodeId = rxOpt->destNode,
    .destNode.endpoint = 0,
    .destNode.BitAddress = 0,
  // If applicable, supervision CC will fill in Supervision data in rxOptEx.
    .bSupervisionActive = 0
  };
  cc_handler_input_t input = {
    .rx_options = &rxOptEx,
    .frame = pCmd,
    .length = cmdLength
  };

  ZW_APPLICATION_TX_BUFFER bufferOut = { 0 };
  cc_handler_output_t output = {
    .frame = &bufferOut,
    .length = 0
  };
  // Ignore output.duration - it is not expected that zaf_transport_tx() will use it

  received_frame_status_t status = invoke_cc_handler(&input, &output);

  if (RECEIVED_FRAME_STATUS_CC_NOT_FOUND != status) {
    if (0 < output.length && RECEIVED_FRAME_STATUS_FAIL != status) {
      // The CC handler put something into the output buffer => Transmit it.
      zaf_tx_options_t tx_options = { 0 };
      zaf_transport_rx_to_tx_options(&rxOptEx, &tx_options);
      (void) zaf_transport_tx((uint8_t *)output.frame, output.length, NULL, &tx_options);
    }

    /*
     * The response was handled above. Hence, return here so that the frame is not parsed twice.
     */
    return;
  }

  Transport_ApplicationCommandHandlerEx(&rxOptEx, pCmd, cmdLength);
}

void
RxToTxOptions( RECEIVE_OPTIONS_TYPE_EX *rxopt,     /* IN  receive options to convert */
               TRANSMIT_OPTIONS_TYPE_SINGLE_EX** txopt)   /* OUT converted transmit options */
{
  static TRANSMIT_OPTIONS_TYPE_SINGLE_EX txOptionsEx;
  static MULTICHAN_NODE_ID destNode;

  // Here we reset struct using memset because struct are static & reused
  memset(&txOptionsEx,0,sizeof(txOptionsEx));
  memset(&destNode,0,sizeof(destNode));

  txOptionsEx.pDestNode = &destNode;
  *txopt = &txOptionsEx;

  destNode.node.nodeId = rxopt->sourceNode.nodeId;
  destNode.node.endpoint = rxopt->sourceNode.endpoint;
  destNode.nodeInfo.BitMultiChannelEncap = (rxopt->sourceNode.endpoint == 0) ? 0 : 1;
  destNode.nodeInfo.security = rxopt->securityKey;

  txOptionsEx.txOptions = TRANSMIT_OPTION_ACK | TRANSMIT_OPTION_EXPLORE | ZWAVE_PLUS_TX_OPTIONS;
  if (rxopt->rxStatus & RECEIVE_STATUS_LOW_POWER)
  {
      txOptionsEx.txOptions |= TRANSMIT_OPTION_LOW_POWER;
  }
  txOptionsEx.sourceEndpoint = rxopt->destNode.endpoint;
  txOptionsEx.txSecOptions = 0;
  txOptionsEx.pDestNode->nodeInfo.security = rxopt->securityKey;
}

bool
Check_not_legal_response_job(RECEIVE_OPTIONS_TYPE_EX *rxOpt) /*rxOpt pointer of type RECEIVE_OPTIONS_TYPE_EX */
{
  bool status = false;
  /*
   * Check
   * 1: is the command received via multicast ?
   * 2: is the bit address set to 1 in the Multi Channel destination End Point ?
   * 3: Get command must not support Supervision encapsulation (CC:006C.01.00.21.003)
   */
  if (is_multicast(rxOpt) ||
     (0 != rxOpt->destNode.BitAddress) ||
     (true == myTransportEndpoint.flag_supervision_encap))
  {

    status = true;
  }
  myTransportEndpoint.flag_supervision_encap = false;
  return status;
}

bool
is_multicast(RECEIVE_OPTIONS_TYPE_EX *rxOpt) /*rxOpt pointer of type RECEIVE_OPTIONS_TYPE_EX */
{
  /*
   * Check if the frame is addressed to Broadcast NodeID or a Multicast frame
   */
  if (0 != (rxOpt->rxStatus & (RECEIVE_STATUS_TYPE_BROAD | RECEIVE_STATUS_TYPE_MULTI)))
  {
    return true;
  }
  return false;
}

void
SetFlagSupervisionEncap(bool flag)
{
  myTransportEndpoint.flag_supervision_encap = flag;
}

ZW_WEAK received_frame_status_t
Transport_ApplicationCommandHandlerEx(
  __attribute__((unused)) RECEIVE_OPTIONS_TYPE_EX *rxOpt,
  __attribute__((unused)) ZW_APPLICATION_TX_BUFFER *pCmd,
  __attribute__((unused)) uint8_t cmdLength)
{
  return RECEIVED_FRAME_STATUS_NO_SUPPORT;
}
