/***************************************************************************//**
 * @file btl_apploader_config.h
 * @brief BLE Apploader OTA DFU Configuration - Configuration Template File
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

// <<< Use Configuration Wizard in Context Menu >>>

/*********************************************************************************************************
 *********************************************************************************************************
 *                                               MODULE
 ********************************************************************************************************
 *******************************************************************************************************/

#ifndef  BTL_APPLOADER_CONFIG_H
#define  BTL_APPLOADER_CONFIG_H

// <h> Options:

/********************************************************************************************************
********************************************************************************************************
*                                             APPLOADER CONFIGURATION
*********************************************************************************************************
********************************************************************************************************/
// <q BTL_APPLOADER_USE_RANDOM_ADDRESS> Use static random address
// <i> Default: 0
// <i> The device will use static random address for advertising.
#define BTL_APPLOADER_USE_RANDOM_ADDRESS  0

// <q BTL_APPLOADER_USE_CUSTOM_ADDRESS> Use custom device address
// <i> Default: 0
// <i> The default implementation of custom address will use public BT address stored in MFG_CUSTOM_EUI_64 manufacturing token in user data page.
// <i> The implementation can be overridden by implementing bootloader_apploader_get_custom_device_address() function.
// <i>
// <i> The custom device address is additionally used in advertisement data as device address.
// <i> If both static random address and custom address options are enabled then static random address is used as device address and
// <i> custom device address is used in the advertisement data.
#define BTL_APPLOADER_USE_CUSTOM_ADDRESS  0

// <e BTL_APPLOADER_SET_RF_PATH> Set used RF antenna path.
// <i> Default: 0
// <i> This option should be used only if the device has multiple antenna ports.
#define BTL_APPLOADER_SET_RF_PATH  0

// <o BTL_APPLOADER_RF_PATH> RF antenna path
// <0-255:1>
// <f .h>
// <i> Default: 0xff
// <i> Set the antenna path used during OTA DFU. Default value 0xff uses the default antenna path.
#define BTL_APPLOADER_RF_PATH  255
// </e>

// <o BTL_APPLOADER_TX_POWER> Radiated TX power level in 0.1dBm unit
// <i> Default: 0 (0 dBm)
// <i> TX power levels for Bluetooth connection that are radiated from the antenna.
#define BTL_APPLOADER_TX_POWER 0

// <s.18 BTL_APPLOADER_DEVICE_NAME> Device name
// <i> Default: OTA
// <i> The device name to be used during the OTA DFU.
// <i> Maximum name length is 18 bytes.
#define BTL_APPLOADER_DEVICE_NAME  "OTA"

// </h>

#endif // End of BTL_APPLOADER_CONFIG_H module include.

// <<< end of configuration section >>>
