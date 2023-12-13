/**
 * @file CC_Common.c
 * @brief Common types and definitions for all command classes.
 * @copyright 2018 Silicon Laboratories Inc.
 */

#include <CC_Common.h>
#include <string.h>
#include "zaf_transport_tx.h"

#define MAX_PAYLOAD 150

typedef struct _ZW_ENGINE_FRAME_
{
  CMD_CLASS_GRP grp;
   uint8_t payload[MAX_PAYLOAD];
} ZW_ENGINE_FRAME;



JOB_STATUS cc_engine_multicast_request(
    const AGI_PROFILE* pProfile,
    uint8_t endpoint,
    CMD_CLASS_GRP *pcmdGrp,
    uint8_t* pPayload,
    uint8_t size,
    uint8_t fSupervisionEnable,
    VOID_CALLBACKFUNC(pCbFunc)(TRANSMISSION_RESULT * pTransmissionResult))
{
  uint8_t frame_len = sizeof(CMD_CLASS_GRP);
  ZW_ENGINE_FRAME txBuf = {
    .grp.cmdClass = pcmdGrp->cmdClass,
    .grp.cmd = pcmdGrp->cmd
  };

  if( 0 != size )
  {
    memcpy(&txBuf.payload, pPayload, size);
    frame_len += size;
  }
  zaf_tx_options_t tx_options = {
    .dest_node_id = 0,
    .agi_profile = pProfile,
    .source_endpoint = endpoint,
    .use_supervision = fSupervisionEnable
  };
  if(!zaf_transport_tx((uint8_t *)&txBuf, frame_len, pCbFunc, &tx_options)) {
    return JOB_STATUS_BUSY;
  }
  return JOB_STATUS_SUCCESS;
}
