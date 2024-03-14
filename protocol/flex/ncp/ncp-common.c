/***************************************************************************//**
 * @brief Functions for global NCP functionning
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
#include "stack/include/ember.h"
#include "csp-format.h"
#include "csp-command-utils.h"
#include "ncp-cpc-interface.h"

uint8_t *sendBlockingCommand(uint8_t *apiCommandBuffer)
{
  (void *)apiCommandBuffer;
  return NULL;
}

void sendResponse(uint8_t *apiCommandBuffer, uint16_t commandLength)
{
  sli_connect_cpc_send_command(apiCommandBuffer, commandLength);
}

void sendCallbackCommand(uint8_t *callbackCommandBuffer, uint16_t commandLength)
{
  if (sli_connect_is_ncp_connected()) {
    sli_connect_cpc_send_command(callbackCommandBuffer, commandLength);
  }
}

uint8_t *getApiCommandPointer()
{
  return (uint8_t *)malloc(MAX_STACK_API_COMMAND_SIZE);
}

uint8_t *allocateCallbackCommandPointer()
{
  return (uint8_t *)malloc(MAX_STACK_API_COMMAND_SIZE);
}

void acquireCommandMutex(void)
{
}

void releaseCommandMutex(void)
{
}

bool isCurrentTaskStackTask(void)
{
  return true;
}

void unknownCommandIdHandler(uint16_t commandId)
{
  //The host can timeout if the response is not correct, nothing to do here
  (void)commandId;
}
