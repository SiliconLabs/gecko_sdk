/***************************************************************************//**
 * @file
 * @brief Dot matrix display interface using EBI
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

#include <stdint.h>
#include "dmd_ssd2119_registers.h"
#include "dmd_ssd2119.h"
#include "dmdif_ssd2119_ebi.h"
#include "bsp.h"

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/* Local function prototypes */
static EMSTATUS setNextReg(uint8_t reg);

static volatile uint16_t *command_register;
static volatile uint16_t *data_register;

/**************************************************************************//**
*  @brief
*  Initializes the data interface to the LCD controller SSD2119
*
*
*  @param cmdRegAddr
*  The address in memory where data to the command register in the display
*  controller are written
*  @param dataRegAddr
*  The address in memory where data to the data register in the display
*  controller are written
*
*  @return
*  DMD_OK on success, otherwise error code
******************************************************************************/
EMSTATUS DMDIF_init(uint32_t cmdRegAddr, uint32_t dataRegAddr)
{
  command_register = (volatile uint16_t*) cmdRegAddr;
  data_register    = (volatile uint16_t*) dataRegAddr;

  BSP_RegisterWrite(BC_BUS_CFG, BC_BUS_CFG_EBI);

  return DMD_OK;
}

/**************************************************************************//**
*  @brief
*  Writes a value to a control register in the LCD controller
*
*  @param reg
*  The register that will be written to
*  @param data
*  The value to write to the register
*
*  @return
*  DMD_OK on success, otherwise error code
******************************************************************************/
EMSTATUS DMDIF_writeReg(uint8_t reg, uint16_t data)
{
  setNextReg(reg);

  /* Write bits [15:8] of the data to bits [8:1] of the output lines */
  *data_register = ((data & 0xff00) >> 8) << 1;

  /* Write bits [7:0] of the data to bits [8:1] of the output lines */
  *data_register = (data & 0x00ff) << 1;

  return DMD_OK;
}

/**************************************************************************//**
*  @brief
*  Reads the device code of the LCD controller
*  DOESN'T WORK
*
*  @return
*  The device code of the LCD controller
******************************************************************************/
uint16_t DMDIF_readDeviceCode(void)
{
  uint16_t readData;
  uint16_t deviceCode;

  /* Reading from the oscillation control register gives the device code */
  setNextReg(DMD_SSD2119_DEVICE_CODE_READ);

  readData    = *data_register;
  deviceCode  = ((readData >> 1) & 0x00ff) << 8;
  readData    = *data_register;
  deviceCode |= ((readData >> 1) & 0x00ff);

  return deviceCode;
}

/**************************************************************************//**
*  @brief
*  Sends the data access command to the LCD controller to prepare for one or more
*  writes or reads using the DMDIF_writeData() and DMDIF_readData()
*
*  @return
*  DMD_OK on success, otherwise error code
******************************************************************************/
EMSTATUS DMDIF_prepareDataAccess(void)
{
  setNextReg(DMD_SSD2119_ACCESS_DATA);

  return DMD_OK;
}

/**************************************************************************//**
*  @brief
*  Writes one pixel to the LCD controller. DMDIF_prepareDataAccess() needs to be
*  called before writing data using this function.
*
*  @param data
*  The color value of the pixel to be written in 18bpp format
*
*  @return
*  DMD_OK on success, otherwise error code
******************************************************************************/
EMSTATUS DMDIF_writeData(uint32_t data)
{
  /* Write bits [17:9] of the pixel data to bits [8:0] on the output lines */
  *data_register = (data & 0x0003FE00) >> 9;
  /* Write bits [8:0] of the pixel data to bits [8:0] on the output lines */
  *data_register = (data & 0x000001FF);

  return DMD_OK;
}

/**************************************************************************//**
*  @brief
*  Reads a byte of data from the memory of the LCD controller.
*  DMDIF_prepareDataAccess() needs to be called before using this function.
*  DOESN'T WORK
*
*  @return
*  18bpp value of pixel
******************************************************************************/
uint32_t DMDIF_readData(void)
{
  uint32_t data;

  /* Read bits [17:9] of the pixel */
  data = *data_register << 9;
  /* Read bits [8:0] of the pixel */
  data |= *data_register;

  return data;
}

/**************************************************************************//**
*  @brief
*  Delays the program a given number of milliseconds
*
*  @param reg
*  Number of milliseconds to delay.
*
*  @return
*  DMD_OK on success, otherwise error code
******************************************************************************/
EMSTATUS DMDIF_delay(uint32_t ms)
{
  extern void Delay(uint32_t dlyTicks);

  Delay(ms);

  return DMD_OK;
}

/**************************************************************************//**
*  \brief
*  Sets the register in the LCD controller to write commands to
*
*  \param reg
*  The next register in the LCD controller to write to
*
*  @return
*  DMD_OK on success, otherwise error code
******************************************************************************/
static EMSTATUS setNextReg(uint8_t reg)
{
  uint16_t data;

  data = ((uint16_t) reg) << 1;

  /* First 9 bits is 0 */
  *command_register = 0;

  /* Write the register address to bits [8:1] in the index register */
  *command_register = data;

  return DMD_OK;
}

/** @endcond */
