/***************************************************************************//**
 * @file
 * @brief Spiflash-backed storage component with JEDEC support for Silicon Labs Bootloader.
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

#ifndef BTL_STORAGE_SPIFLASH_SFDP_H
#define BTL_STORAGE_SPIFLASH_SFDP_H

/***************************************************************************//**
 * @addtogroup Components
 * @{
 * @addtogroup Storage
 * @{
 * @page SPI Flash Using JEDEC SFDP Standard
 *   The SPI Flash storage implementation using JEDEC supports all SPI Flash parts
 *   that support JEDEC SFDP.
 *
 *   The supported devices will be detected and configured at runtime using the
 *   SFDP standard. The driver queries the parameter table present within a
 *   reserved section of the flash memory to get the device properties. The driver
 *   initializes the flash device in accordance with the values present in the
 *   parameter table.
 *   Including support for SFDP standard in the bootloader will lead to slightly
 *   larger bootloader code sizes
 *
 *   The SPI Flash storage implementation does not support any write protection
 *   functionality.
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

// -----------------------------------------------------------------------------
// Typedefs

/// Unique identifiers for supported SPI flash parts
typedef enum {
  UNKNOWN_DEVICE,
  ATMEL_4M_DEVICE,
  ATMEL_8M_DEVICE,
} StorageSpiflashDevice_t;

// -----------------------------------------------------------------------------
// Defines

// -----------------------------------------------------------------------------
// Functions

/** @endcond */

/** @} addtogroup Storage */
/** @} addtogroup Components  */

#endif // BTL_STORAGE_SPIFLASH_SFDP_H
