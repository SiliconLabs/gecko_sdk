/**
* @file
* Implements functions for transporting frames over the native Z-Wave Network
* @copyright 2018 Silicon Laboratories Inc.
*/

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include <ZW_TransportSecProtocol.h>
#include <ZAF_command_class_utils.h>
#include <ZW_transport_api.h>
#include <ZAF_Common_helper.h>
#include <ZAF_Common_interface.h>
#include <zaf_cc_list_generator.h>
#include <ZW_TransportEndpoint.h>

//#define DEBUGPRINT
#include "DebugPrint.h"
/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/
#ifdef ZW_CONTROLLER
uint8_t SECURITY_KEY = 0;
#endif

static zaf_cc_list_t empty_list = {
  .cc_list = NULL,
  .list_size = 0
};

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/

static bool use_non_included_unsecure_list(void)
{
  return (0 == ZAF_GetNodeID() || (SECURITY_KEY_NONE == GetHighestSecureLevel(ZAF_GetSecurityKeys())));
}

uint8_t
Transport_OnApplicationInitSW(void)
{
  DPRINT("SecAppInit\r\n");

  return true;
}

/**
 * @brief Get highest secure level
 */
enum SECURITY_KEY
GetHighestSecureLevel(uint8_t protocolSecBits)
{
  if(SECURITY_KEY_S2_ACCESS_BIT & protocolSecBits)
  {
    return SECURITY_KEY_S2_ACCESS;
  }
  else if(SECURITY_KEY_S2_AUTHENTICATED_BIT & protocolSecBits)
  {
    return SECURITY_KEY_S2_AUTHENTICATED;
  }
  else if(SECURITY_KEY_S2_UNAUTHENTICATED_BIT & protocolSecBits)
  {
    return SECURITY_KEY_S2_UNAUTHENTICATED;
  }
  else if(SECURITY_KEY_S0_BIT & protocolSecBits)
  {
    return SECURITY_KEY_S0;
  }

  return SECURITY_KEY_NONE;
}

zaf_cc_list_t*
GetCommandClassList(
    bool included,
    security_key_t eKey,
    uint8_t endpoint)
{
  zaf_cc_list_t *unsecure_included_cc;
  zaf_cc_list_t *secure_included_unsecure_cc;
  zaf_cc_list_t *secure_included_secure_cc;

  DPRINTF("\r\nCommandsSuppported(%d, %d, %d)\r\n", included, eKey, endpoint);

  // Only read for root device
  // Endpoints are handled by GetEndpointcmdClassList
  if(endpoint == 0) {
    zafi_cc_list_generator_get_lists(endpoint, &unsecure_included_cc, &secure_included_unsecure_cc, &secure_included_secure_cc);  
  }

  if (true == included)
  {

    if (SECURITY_KEY_NONE == eKey)
    {
      uint8_t keys = ZAF_GetSecurityKeys();

      /*Check non secure command class list*/
      if(0 == endpoint)
      {
        if(SECURITY_KEY_NONE_MASK == keys)
        {
          /*Non-secure included, non-secure cmd class list*/
          return unsecure_included_cc;
        } else {
          /*secure included, non-secure cmd class list*/
          return secure_included_unsecure_cc;
        }
      }
#ifndef SERIAL_API_APP
      else
      {
        return GetEndpointcmdClassList(false, endpoint);
      }
#endif
    }
    else
    {
      /*Check secure command class list*/

      /*If eKey not is supported, return NULL pointer!!*/
      if(eKey == GetHighestSecureLevel(ZAF_GetSecurityKeys()) )
      {
        if(0 == endpoint)
        {
          return secure_included_secure_cc;
        }
  #ifndef SERIAL_API_APP
        else
        {
          return GetEndpointcmdClassList(true, endpoint);
        }
  #endif
      }
      else
      {
        /*not included. Deliver empty list*/
        return &empty_list;
      }
    }
  }
  else
  {
    /*Not included!*/
    if(0 == endpoint)
    {
      if (SECURITY_KEY_NONE == eKey)
      {
        return unsecure_included_cc;
      }
      else
      {
        /*not included. Deliver empty list*/
        return &empty_list;
      }
    }
#ifndef SERIAL_API_APP
    else
    {
      return GetEndpointcmdClassList(false, endpoint);
    }
#endif
  }

  return &empty_list;
}

uint8_t
Transport_OnLearnCompleted(__attribute__((unused)) node_id_t nodeID)
{
  zaf_stay_awake();

  return true;
}

void ZAF_Transport_OnLearnCompleted(void)
{
  Transport_OnLearnCompleted(0);
}


void
ApplicationCommandHandler(__attribute__((unused)) void *pSubscriberContext, SZwaveReceivePackage* pRxPackage)
{
  ZW_APPLICATION_TX_BUFFER *pCmd = &pRxPackage->uReceiveParams.Rx.Payload.rxBuffer;
  uint8_t cmdLength = pRxPackage->uReceiveParams.Rx.iLength;
  RECEIVE_OPTIONS_TYPE *rxOpt = &pRxPackage->uReceiveParams.Rx.RxOptions;

  DPRINTF("\r\nAppCmdH  %d %d %d", rxOpt->securityKey, pCmd->ZW_Common.cmdClass, pCmd->ZW_Common.cmd);

#ifndef ACCEPT_ALL_CMD_CLASSES
  /* Check if cmd Class are supported in current mode (unsecure or secure) */
  if (true == TransportCmdClassSupported(pCmd->ZW_Common.cmdClass,
                                pCmd->ZW_Common.cmd,
                                rxOpt->securityKey))
#endif /* ACCEPT_ALL_CMD_CLASSES */
  {
    Transport_ApplicationCommandHandler(pCmd, cmdLength, rxOpt);

    zaf_stay_awake();
  }
#ifndef ACCEPT_ALL_CMD_CLASSES
  else
  {
    DPRINT("\r\nCmdCl not supported :(\r\n");
  }
#endif /* ACCEPT_ALL_CMD_CLASSES */
}

bool
TransportCmdClassSupported(uint8_t commandClass,
                           uint8_t command,
                           enum SECURITY_KEY eKey)
{
  zaf_cc_list_t *unsecure_included_cc;
  zaf_cc_list_t *secure_included_unsecure_cc;
  zaf_cc_list_t *secure_included_secure_cc;

  zafi_cc_list_generator_get_lists(0, &unsecure_included_cc, &secure_included_unsecure_cc, &secure_included_secure_cc);  

  if(use_non_included_unsecure_list()) {
    return CmdClassSupported(eKey,
                            commandClass,
                            command,
                            secure_included_secure_cc->cc_list,
                            secure_included_secure_cc->list_size,
                            unsecure_included_cc->cc_list,
                            unsecure_included_cc->list_size);
  } else {
    return CmdClassSupported(eKey,
                            commandClass,
                            command,
                            secure_included_secure_cc->cc_list,
                            secure_included_secure_cc->list_size,
                            secure_included_unsecure_cc->cc_list,
                            secure_included_unsecure_cc->list_size);
  }
}
