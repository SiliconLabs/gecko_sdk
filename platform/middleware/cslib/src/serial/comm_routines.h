/***************************************************************************//**
 * @file
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

#ifndef COMM_ROUTINES_H
#define COMM_ROUTINES_H
#include <stdint.h>
/** Saves string describing data types and number of data elements */
typedef struct {
  char* header;
  uint8_t instances;
}HeaderStruct_t;

/** Helper function for outputting a string */
uint8_t OutputString(uint8_t* buffer);

/** Hardware init of serial port */
void CSLIB_commInit(void);

/** Outputs | between columns when needed in ASCII serial protocol */
void outputBreak(void);

/** Outputs Profiler header with column information */
void outputBeginHeader(void);

/** Carriage return function */
void outputNewLine(void);

/** Causes serial interface to block until transfer completes */
void BlockWhileTX(void);

/** Top level function for serial interface tick, called in main() */
void CSLIB_commUpdate(void);

/** Prints header line in interface for one data type */
void outputHeaderCount(HeaderStruct_t headerEntry);

#endif // COMM_ROUTINES_H
