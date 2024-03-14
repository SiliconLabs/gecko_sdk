/***************************************************************************//**
 * # License
 * <b> Copyright 2023 Silicon Laboratories Inc. www.silabs.com </b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of the Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * https://www.silabs.com/about-us/legal/master-software-license-agreement
 * By installing, copying or otherwise using this software, you agree to the
 * terms of the MSLA.
 *
 ******************************************************************************/

#ifndef SL_STORAGE_CONFIG_H
#define SL_STORAGE_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>
// <h> Flash Storage configuration

// <e SL_BOOTLOADER_STORAGE_USE_CUSTOM_SIZE> Use custom bootloader storage size.
// <i> Default: 0
// <i> A value of 0 means that half of the flash minus 16kB is allocated to bootloader
// <i> storage. Set this value to 1 in order to customize the bootloader storage
// <i> size.
#define SL_BOOTLOADER_STORAGE_USE_CUSTOM_SIZE  1

// <o SL_BOOTLOADER_STORAGE_SIZE> Size of the bootloader storage.
// <i> Default: 0x20000
// <i> Note that this value is only being used if BOOTLOADER_STORAGE_USE_DEFAULT
// <i> is set to false. This value will control how much of the flash memory
// <i> is reserved for bootloader storage.
#define SL_BOOTLOADER_STORAGE_SIZE  0x0003A000

// </e>
// </h>
// <<< end of configuration section >>>

#endif
