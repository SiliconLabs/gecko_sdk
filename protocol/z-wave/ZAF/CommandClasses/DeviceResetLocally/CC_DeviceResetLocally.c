/**
 * @file
 * Handler for Command Class Device Reset Locally.
 * @copyright 2018 Silicon Laboratories Inc.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#include <CC_DeviceResetLocally.h>
#include <ZW_TransportEndpoint.h>
#include <ZAF_Common_interface.h>

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

// Nothing here.

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

// Nothing here.

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

// Nothing here.

/****************************************************************************/
/*                               FUNCTIONS                                  */
/****************************************************************************/

void CC_DeviceResetLocally_notification_tx(
  const agi_profile_t * pProfile,
  void(* pCallback)(transmission_result_t * pTransmissionResult))
{
  transmission_result_t transmissionResult;
  transmissionResult.nodeId = 0;
  transmissionResult.status = false;
  transmissionResult.isFinished = TRANSMISSION_RESULT_FINISHED;

  if(!ZAF_GetNodeID())
  {
    /*
     * The node is not included, and therefore it makes no sense to send
     * anything. Finish by calling the callback function.
     */

    if (NULL != pCallback)
    {
      pCallback(&transmissionResult);
    }
  }
  else
  {
    cc_group_t cmdGrp = {COMMAND_CLASS_DEVICE_RESET_LOCALLY, DEVICE_RESET_LOCALLY_NOTIFICATION};

    if(JOB_STATUS_SUCCESS != cc_engine_multicast_request(
        pProfile,
        ENDPOINT_ROOT,
        &cmdGrp,
        NULL,
        0,
        false,
        pCallback))
    {
      if (NON_NULL(pCallback))
      {
        pCallback(&transmissionResult);
      }
    }
  }
}

static uint8_t lifeline_reporting(ccc_pair_t * p_ccc_pair)
{
  p_ccc_pair->cmdClass = COMMAND_CLASS_DEVICE_RESET_LOCALLY;
  p_ccc_pair->cmd      = DEVICE_RESET_LOCALLY_NOTIFICATION;
  return 1;
}

REGISTER_CC_V3(COMMAND_CLASS_DEVICE_RESET_LOCALLY, DEVICE_RESET_LOCALLY_VERSION, NULL, NULL, NULL, lifeline_reporting, 0);
