/***************************************************************************//**
 * @brief CSP Header for functions to use in RTOS or NCP
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

#ifndef __CSP_COMMAND_UTILS_H__
#define __CSP_COMMAND_UTILS_H__

//------------------------------------------------------------------------------
// Functions to implement in RTOS or NCP files

uint8_t *sendBlockingCommand(uint8_t *apiCommandBuffer);

void sendResponse(uint8_t *apiCommandBuffer, uint16_t commandLength);

uint8_t *getApiCommandPointer();

uint8_t *allocateCallbackCommandPointer();

void acquireCommandMutex(void);

void releaseCommandMutex(void);

bool isCurrentTaskStackTask(void);

void sendCallbackCommand(uint8_t *callbackCommandBuffer, uint16_t commandLength);

//------------------------------------------------------------------------------
// Internal APIs defined in csp-command-vncp.c or csp-command-app.c
void handleIncomingApiCommand(uint16_t commandId, uint8_t *apiCommandData);

void handleIncomingCallbackCommand(uint16_t commandId, uint8_t *callbackParams);

#endif
