/***************************************************************************//**
 * @brief CMSIS RTOS IPC code.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include PLATFORM_HEADER
#include "cmsis-rtos-ipc-config.h"

#include "stack/include/ember.h"

#include "cmsis-rtos-support.h"
#include "csp-command-utils.h"
#include "csp-format.h"
#include "csp-api-enum-gen.h"

// TODO: This is for IAR, for GCC it should be "unsigned long"
typedef unsigned int PointerType;

osEventFlagsId_t emAfPluginCmsisRtosFlags;

osMutexId_t commandMutex;
osMessageQueueId_t callbackQueue;
static uint8_t apiCommandData[MAX_STACK_API_COMMAND_SIZE];
static EmberBuffer callbackBuffer[EMBER_AF_PLUGIN_CMSIS_RTOS_MAX_CALLBACK_QUEUE_SIZE];

//------------------------------------------------------------------------------
// Forward declarations

static uint32_t pendCommandPendingFlag(void);
static void postCommandPendingFlag(void);
static void pendResponsePendingFlag(void);
static void postResponsePendingFlag(void);
static void postCallbackPendingFlag(void);

//------------------------------------------------------------------------------
// Internal APIs

void emAfPluginCmsisRtosIpcInit(void)
{
  uint8_t i;

  for (i = 0; i < EMBER_AF_PLUGIN_CMSIS_RTOS_MAX_CALLBACK_QUEUE_SIZE; i++) {
    callbackBuffer[i] = EMBER_NULL_BUFFER;
  }

  const osEventFlagsAttr_t rtosFlagsAttr = {
    "RTOS Flags",
    0,
    NULL,
    0
  };

  emAfPluginCmsisRtosFlags = osEventFlagsNew(&rtosFlagsAttr);
  assert(emAfPluginCmsisRtosFlags != NULL);

  commandMutex = osMutexNew(NULL);
  assert(commandMutex != NULL);

  callbackQueue = osMessageQueueNew(EMBER_AF_PLUGIN_CMSIS_RTOS_MAX_CALLBACK_QUEUE_SIZE,
                                    (sizeof(EmberBufferDesc) + 3) & (~3) /* align to 4 bytes */,
                                    NULL);
  assert(callbackQueue != NULL);
}

uint8_t *sendBlockingCommand(uint8_t *apiCommandBuffer)
{
  // This API can not be called from the stack task (the stack task calls
  // stack APIs directly).
  assert(!isCurrentTaskStackTask());

  // Post the "command pending" flag, wake up the stack and pend for the
  // "response" pending flag.
  postCommandPendingFlag();
  emAfPluginCmsisRtosWakeUpConnectStackTask();
  pendResponsePendingFlag();
  return apiCommandData;
}

void sendResponse(uint8_t *apiCommandBuffer, uint16_t commandLength)
{
  // This API must be called from the stack task.
  assert(isCurrentTaskStackTask());
  postResponsePendingFlag();
}

void emAfPluginCmsisRtosProcessIncomingApiCommand(void)
{
  uint32_t status = pendCommandPendingFlag();

  // This API must be called from the stack task.
  assert(isCurrentTaskStackTask());

  /* Need to check that the pend did not result in an error
   * and that the expected flag is present.
   */
  if (((status & CMSIS_RTOS_ERROR_MASK) == 0) && (status & FLAG_IPC_COMMAND_PENDING)) {
    uint16_t commandId =
      emberFetchHighLowInt16u(apiCommandData);

    handleIncomingApiCommand(commandId, apiCommandData);
  }
}

void sendCallbackCommand(uint8_t *callbackCommandBuffer, uint16_t commandLength)
{
  uint8_t i;
  EmberBufferDesc callbackBufferDescriptorPut = { NULL, 0 };

  // This API must be called from the stack task.
  assert(isCurrentTaskStackTask());

  // Enqueing the callback in the app framework task queue.
  emberAfPluginCmsisRtosAcquireBufferSystemMutex();
  for (i = 0; i < EMBER_AF_PLUGIN_CMSIS_RTOS_MAX_CALLBACK_QUEUE_SIZE; i++) {
    if (callbackBuffer[i] == EMBER_NULL_BUFFER) {
      callbackBuffer[i] = emberAllocateBuffer(commandLength);
      break;
    }
  }
  emberAfPluginCmsisRtosReleaseBufferSystemMutex();

  // Queue is full or no memory available: either way just return.
  if (i >= EMBER_AF_PLUGIN_CMSIS_RTOS_MAX_CALLBACK_QUEUE_SIZE
      || callbackBuffer[i] == EMBER_NULL_BUFFER) {
    return;
  }

  // Write the callback command to the callback buffer.
  MEMCOPY(emberGetBufferPointer(callbackBuffer[i]), callbackCommandBuffer, commandLength);
  free(callbackCommandBuffer);
  callbackBufferDescriptorPut.buffer_addr = &callbackBuffer[i];
  callbackBufferDescriptorPut.buffer_length = commandLength;

  osMessageQueuePut(callbackQueue,
                    (void *)&callbackBufferDescriptorPut,
                    0, //TODO: priority ???
                    0);

  // Wake up the AF task.
  postCallbackPendingFlag();

  // TODO: once we implement stack callback dispatching to custom application
  // tasks, we should add the copy of the callback to the queue of every custom
  // application task that chose to listen to this specific callback.
}

bool emAfPluginCmsisRtosProcessIncomingCallbackCommand(void)
{
  uint16_t messageLength;
  EmberBuffer *callbackBufferPtr = NULL;
  EmberBufferDesc callbackBufferDescriptorGet = { NULL, 0 };
  uint8_t msgPrio;

  // This API can not be called from the stack task (the stack task calls
  // stack APIs directly).
  assert(!isCurrentTaskStackTask());

  osMessageQueueGet(callbackQueue,
                    (void *)&callbackBufferDescriptorGet,
                    &msgPrio,
                    0);

  callbackBufferPtr = callbackBufferDescriptorGet.buffer_addr;
  messageLength = callbackBufferDescriptorGet.buffer_length;

  if (callbackBufferPtr) {
    uint8_t callbackData[MAX_STACK_CALLBACK_COMMAND_SIZE];
    uint16_t commandId;

    // Lock the buffer system to prevent defragmentation while we access the
    // buffer.
    emberAfPluginCmsisRtosAcquireBufferSystemMutex();
    MEMCOPY(callbackData,
            emberGetBufferPointer(*callbackBufferPtr),
            messageLength);
    // This assignment is safe because the vNCP acquires the buffer system mutex
    // before manipulating any entry in callbackBuffer[].
    *callbackBufferPtr = EMBER_NULL_BUFFER;
    emberAfPluginCmsisRtosReleaseBufferSystemMutex();

    commandId = emberFetchHighLowInt16u(callbackData);

    handleIncomingCallbackCommand(commandId,
                                  callbackData + 2);

    return true;
  }

  return false;
}

bool isCurrentTaskStackTask(void)
{
  return (osThreadGetId() == emAfPluginCmsisRtosGetStackTcb());
}

void acquireCommandMutex(void)
{
  assert(!isCurrentTaskStackTask());

  assert(osMutexAcquire(commandMutex, osWaitForever) == osOK);
}

void releaseCommandMutex(void)
{
  assert(!isCurrentTaskStackTask());

  assert(osMutexRelease(commandMutex) == osOK);
}

uint8_t *getApiCommandPointer()
{
  return apiCommandData;
}

uint8_t *allocateCallbackCommandPointer()
{
  return (uint8_t *)malloc(MAX_STACK_API_COMMAND_SIZE);
}

void unknownCommandIdHandler(uint16_t commandId)
{
  uint16_t command_type = commandId & 0xFF00;
  if (command_type == VNCP_CMD_ID) {
    //The OS needs a response to unlock the blocking command
    sendResponse(apiCommandData, 0);
  }
}

//------------------------------------------------------------------------------
// Internal callbacks

void emAfPluginCmsisRtosMarkBuffersCallback(void)
{
  uint8_t i;

  for (i = 0; i < EMBER_AF_PLUGIN_CMSIS_RTOS_MAX_CALLBACK_QUEUE_SIZE; i++) {
    emberMarkBuffer(&callbackBuffer[i]);
  }
}

//------------------------------------------------------------------------------
// Static functions

static uint32_t pendCommandPendingFlag(void)
{
  return osEventFlagsWait(emAfPluginCmsisRtosFlags,
                          FLAG_IPC_COMMAND_PENDING,
                          osFlagsWaitAny,
                          0);
}

static void postCommandPendingFlag(void)
{
  assert((osEventFlagsSet(emAfPluginCmsisRtosFlags,
                          FLAG_IPC_COMMAND_PENDING) & CMSIS_RTOS_ERROR_MASK) == 0);
}

static void pendResponsePendingFlag(void)
{
  assert((osEventFlagsWait(emAfPluginCmsisRtosFlags,
                           FLAG_IPC_RESPONSE_PENDING,
                           osFlagsWaitAny,
                           osWaitForever) & CMSIS_RTOS_ERROR_MASK) == 0);
}

static void postResponsePendingFlag(void)
{
  assert((osEventFlagsSet(emAfPluginCmsisRtosFlags,
                          FLAG_IPC_RESPONSE_PENDING) & CMSIS_RTOS_ERROR_MASK) == 0);
}

static void postCallbackPendingFlag(void)
{
  assert((osEventFlagsSet(emAfPluginCmsisRtosFlags,
                          FLAG_STACK_CALLBACK_PENDING) & CMSIS_RTOS_ERROR_MASK) == 0);
}
