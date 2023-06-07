/***************************************************************************//**
 * @brief Functions for seralization and de-serialization
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

// TODO: the two functions below can be consolidated

void fetchParams(uint8_t *readPointer, PGM_P format, va_list args)
{
  char *c = (char *)format;
  void* ptr;

  while (*c) {
    ptr = va_arg(args, void*);

    switch (*c) {
      case 's': {
        uint8_t *realPointer = (uint8_t *)ptr;
        if (ptr) {
          *realPointer = (uint8_t)*readPointer;
        }
        readPointer++;
      }
      break;
      case 'u': {
        uint8_t *realPointer = (uint8_t *)ptr;
        if (ptr) {
          *realPointer = (uint8_t)*readPointer;
        }
        readPointer++;
      }
      break;
      case 'v': {
        uint16_t *realPointer = (uint16_t *)ptr;
        *realPointer = emberFetchHighLowInt16u(readPointer);
        readPointer += 2;
      }
      break;
      case 'w': {
        uint32_t *realPointer = (uint32_t *)ptr;
        if (ptr) {
          *realPointer = emberFetchHighLowInt32u(readPointer);
        }
        readPointer += 4;
      }
      break;
      case 'b': {
        uint8_t *realArray = (uint8_t *)ptr;
        uint8_t *lengthPointer = (uint8_t *)va_arg(args, void*);
        *lengthPointer = *readPointer;
        readPointer++;
        uint8_t bufferSize = (uint8_t)va_arg(args, unsigned int);

        if (ptr) {
          if (*lengthPointer <= bufferSize) {
            MEMMOVE(realArray, readPointer, *lengthPointer);
          } else {
            MEMMOVE(realArray, readPointer, bufferSize);
          }
        }
        readPointer += *lengthPointer;
        // Propagate correct length value in calling function
        if (*lengthPointer > bufferSize) {
          *lengthPointer = bufferSize;
        }
      }
      break;
      case 'p': {
        uint8_t **realPointer = (uint8_t **)ptr;
        uint8_t *lengthPointer = (uint8_t *)va_arg(args, void*);
        *lengthPointer = *readPointer;
        readPointer++;

        if (ptr) {
          *realPointer = readPointer;
        }
        readPointer += *lengthPointer;
      }
      break;
      default:
        ; // meh
    }
    c++;
  }
}

uint8_t computeCommandLength(uint8_t initialLength, const char* format, va_list argumentList)
{
  uint8_t commandLength = initialLength;
  const char *formatFinger;
  for (formatFinger = (char *) format; *formatFinger != 0; formatFinger++) {
    switch (*formatFinger) {
      case 'u':
        va_arg(argumentList, unsigned int);
        commandLength++;
        break;
      case 's':
        va_arg(argumentList, int);
        commandLength++;
        break;
      case 'v':
        va_arg(argumentList, unsigned int);
        commandLength += sizeof(uint16_t);
        break;
      case 'w':
        va_arg(argumentList, uint32_t);
        commandLength += sizeof(uint32_t);
        break;
      case 'b': {
        va_arg(argumentList, const uint8_t*);
        commandLength += va_arg(argumentList, int) + 1;
        break;
      }
      default:
        assert(false);
        break;
    }
  }
  return commandLength;
}

void fetchApiParams(uint8_t *apiCommandData, PGM_P format, ...)
{
  va_list argumentList;
  va_start(argumentList, format);
  // Start fetching right after the command ID
  fetchParams(apiCommandData + 2, format, argumentList);
  va_end(argumentList);
}

void fetchCallbackParams(uint8_t *callbackParams, PGM_P format, ...)
{
  va_list argumentList;
  va_start(argumentList, format);
  fetchParams(callbackParams, format, argumentList);
  va_end(argumentList);
}

uint16_t formatResponseCommandFromArgList(uint8_t *buffer,
                                          uint16_t bufferSize,
                                          uint16_t identifier,
                                          const char *format,
                                          va_list argumentList)
{
  uint8_t *finger = buffer;
  const char *formatFinger;

  MEMSET(buffer, 0, bufferSize);

  // store the identifier
  emberStoreHighLowInt16u(finger, identifier);
  finger += sizeof(uint16_t);

  // We use primitive types to retrieve va_args because gcc on some
  // platforms (eg., unix hosts) complains about automatic variable
  // promotion in variadic functions.
  // [eg: warning: 'uint8_t' is promoted to 'int' when passed through '...']
  //
  // An exception is made for the uint32_t case:  Here we need to check the size
  // of unsigned int, which can be smaller on platforms such as the c8051.

  for (formatFinger = (char *) format; *formatFinger != 0; formatFinger++) {
    switch (*formatFinger) {
      case 'u':
        *finger++ = va_arg(argumentList, unsigned int);
        break;
      case 's':
        *finger++ = va_arg(argumentList, int);
        break;
      case 'v':
        emberStoreHighLowInt16u(finger, va_arg(argumentList, unsigned int));
        finger += sizeof(uint16_t);
        break;
      case 'w':
        if (sizeof(unsigned int) < sizeof(uint32_t)) {
          emberStoreHighLowInt32u(finger, va_arg(argumentList, uint32_t));
        } else {
          emberStoreHighLowInt32u(finger, va_arg(argumentList, unsigned int));
        }
        finger += sizeof(uint32_t);
        break;
      case 'b': {
        const uint8_t *data = va_arg(argumentList, const uint8_t*);
        // store the size, must fit into a byte
        uint8_t dataSize = va_arg(argumentList, int);
        *finger++ = dataSize;

        if (dataSize > 0) {
          // Checking for NULL here save's every caller from checking.  We assume
          // the if dataSize is not zero then we should send all zeroes.
          if (data != NULL) {
            MEMCOPY(finger, data, dataSize);
          } else {
            MEMSET(finger, 0, dataSize);
          }
        }

        finger += dataSize;
        break;
      }
      default:
        // confused!
        assert(false);
        break;
    }
  }

  uint16_t length = finger - buffer;
  // sanity check
  assert(length <= bufferSize);

  return length;
}

uint16_t formatResponseCommand(uint8_t *buffer,
                               uint16_t bufferSize,
                               uint16_t identifier,
                               PGM_P format,
                               ...)
{
  va_list argumentList;
  va_start(argumentList, format);
  uint16_t length = formatResponseCommandFromArgList(buffer,
                                                     bufferSize,
                                                     identifier,
                                                     format,
                                                     argumentList);
  va_end(argumentList);
  return length;
}
