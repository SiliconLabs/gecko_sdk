/***************************************************************************//**
 * @file
 * @brief Configuration Over SWO Component.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_COS_H
#define SL_COS_H

#include "sl_enum.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup cos Configuration Over SWO
 * @brief Configuration Over SWO
 * @details
 * ## Overview
 *
 *   When working with VCOM and/or PTI with a Silicon Labs kit (WSTK or WPK),
 *   it's important that the configuration of the kit's board controller
 *   matches that of the target application.
 *   The Configuration Over SWO component provides a way to automatically
 *   configure the board controller to use the same settings for VCOM and
 *   PTI configuration is sent to the board controller over SWO at startup,
 *   ensuring that the configuration is synchronized.
 * @{
 ******************************************************************************/

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN
/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/
#if defined (SL_CATALOG_UARTDRV_USART_PRESENT) || defined (SL_CATALOG_UARTDRV_EUSART_PRESENT)
#define SLI_COS_UARTDRV_VCOM_PRESENT
#endif // SL_CATALOG_UARTDRV_USART_PRESENT || SL_CATALOG_UARTDRV_EUSART_PRESENT

#define COS_CONFIG_FLOWCONTROL_NONE      0
#define COS_CONFIG_FLOWCONTROL_CTS       1
#define COS_CONFIG_FLOWCONTROL_RTS       2
#define COS_CONFIG_FLOWCONTROL_CTS_RTS   3
/// @endcond

// -----------------------------------------------------------------------------
// Data Types

/// @brief Enumeration representing the PTI Modes
SL_ENUM(COS_PtiMode_t) {
  /** ONEWIRE mode. */
  COS_CONFIG_PTI_MODE_ONEWIRE,
  /** TWOWIRE mode. */
  COS_CONFIG_PTI_MODE_TWOWIRE,
  /** UART mode. */
  COS_CONFIG_PTI_MODE_EFRUART,
  /** SPI mode. */
  COS_CONFIG_PTI_MODE_EFRSPI,
  /** Mode count. */
  COS_CONFIG_PTI_MODE_COUNT
};

/// @brief Enumeration representing the PTI Interfaces
SL_ENUM(COS_PtiInterface_t) {
  /** PTI INTERFACE 0. */
  COS_CONFIG_PTI_INTERFACE_0,
  /** PTI INTERFACE 1. */
  COS_CONFIG_PTI_INTERFACE_1,
  /** Interface count. */
  COS_CONFIG_PTI_INTERFACE_COUNT
};

// -----------------------------------------------------------------------------
// Prototypes

/***************************************************************************//**
 * Initialize the SWO ITM 8 and initiates VCOM/PTI SWO writes.
 ******************************************************************************/
void sl_cos_send_config(void);

 /***************************************************************************//**
 * Custom API, to be used by other software component to write the
 * structured VCOM data on SWO ITM channel 8
 * The following Custom API take Baud rate, Flow Control as an input that should be
 * configured at the bit(0 to 23) and bit(30(CTS), 31(RTS)) of the structured VCOM
 * data respectively so that WSTK identifies the baud rate and flow_control values
 * and configure accordingly
 *
 * @param[in] BaudRate       Baud rate that has to be set over bit_0 to bit_23.
 *
 * @param[in] flow_control   Flow Control value that has to be set over bit_30 and bit_31.
 ******************************************************************************/
void sl_cos_config_vcom(uint32_t baudrate,
                        uint8_t flow_control);

/***************************************************************************//**
 * Custom API, to be used by other software component to write the
 * structured PTI data on SWO ITM channel 8
 *
 * @param[in] BaudRate       Baud rate that has to be set over bit_0 to bit_23.
 * @param[in] mode           COS_PtiMode_t to be used.
 *                           ONEWIRE mode.
 *                           TWOWIRE mode.
 *                           UART mode.
 *                           SPI mode.
 *                           PTI Modes that has to be set over bit_27 to bit_29.
 * @param[in] interface      COS_PtiInterface_t to be used.
 *                           PTI INTERFACE 0.
 *                           PTI INTERFACE 1.
 *                           Interface value that has to be set over bit_30 and bit_31.
 * @return  config
 ******************************************************************************/
void sl_cos_config_pti(uint32_t baudrate,
                       COS_PtiMode_t mode,
                       COS_PtiInterface_t interface);

/** @} (end addtogroup cos) */

#ifdef __cplusplus
}
#endif

#endif /* SL_COS_H */
