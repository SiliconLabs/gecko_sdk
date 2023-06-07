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

#include "comm_routines.h"

#include <stdio.h>
#include <stdlib.h>

#include "em_device.h"
#include "retargetserial.h"
#include "em_gpio.h"

/***************************************************************************//**
 * @brief
 *   Hardware init of serial port
 *
 *   This routine fully initializes the serial port for the device.
 *   It also retargets printf output to this interface, which is then
 *   used by the virtual COMM port on STKs in code examples.
 ******************************************************************************/
void CSLIB_commInit(void)
{
  // Initialize USART and map LF to CRLF
  RETARGET_SerialInit();
  RETARGET_SerialCrLf(1);
  /* Enable VCOM */
  GPIO_PinModeSet(BSP_BCC_ENABLE_PORT, BSP_BCC_ENABLE_PIN, gpioModePushPull, 1);
  GPIO_PinOutSet(BSP_BCC_ENABLE_PORT, BSP_BCC_ENABLE_PIN);
}

/***************************************************************************//**
 * @brief
 *   Causes serial interface to block until transfer completes
 *
 *   This routine forces the serial interface output to be a blocking
 *   operation.  This is necessary because otherwise the system may go
 *   into a low power state before all bytes have transmitted.
 *
 ******************************************************************************/
void BlockWhileTX(void)
{
  //Delay a short time while waiting for bytes to transmit.
  uint32_t delay;
  volatile uint32_t touch;
  for ( delay = 0; delay < 4000; delay++) {
    touch = delay * 2;
    touch = touch - delay;
  }
}

/***************************************************************************//**
 * @brief
 *   Prints header line in interface for one data type
 *
 *   The capacitive sensing profiler output begins with a line that describes
 *   the data types being transmitted and the number of elements of each data
 *   type.  This function outputs information about one data type per execution.
 *
 ******************************************************************************/
void outputHeaderCount(HeaderStruct_t headerEntry)
{
  uint8_t index;
  // If more than one element is defined for this data type,
  // then output '_XX' after the name, where 'XX' increments
  // sequentially from 0 for the datatype
  if (headerEntry.instances > 1) {
    for (index = 0; index < headerEntry.instances; index++) {
      printf("%s_%d ", headerEntry.header, index);
    }
  }
  // If only one element exists for this data type, only output the
  // data type name and leave off the '_'
  else {
    printf("%s ", headerEntry.header);
  }
}

/***************************************************************************//**
 * @brief
 *   Prints header line in interface for one data type
 *
 *   The capacitive sensing profiler output begins with a line that describes
 *   the data types being transmitted and the number of elements of each data
 *   type.  This function outputs information about one data type per execution.
 *
 ******************************************************************************/
void outputBreak(void)
{
  printf(" | ");
}

/***************************************************************************//**
 * @brief
 *   Outputs | between columns when needed between data types in header
 *
 *   The serial interfaces header line needs '|' separators between
 *   each defined data type.  This function outputs those separators.
 *
 ******************************************************************************/
void outputBeginHeader(void)
{
  printf("*HEADER ");
}
/***************************************************************************//**
 * @brief
 *   Outputs a carriage return
 *
 *   This function is called in a number of places in serial interface output.
 *   Included here to condense all calls to a single printf() call in Flash.
 *
 ******************************************************************************/
void outputNewLine(void)
{
  printf("\n");
}
