/***************************************************************************//**
 * @file
 * @brief Configuration for bootloader
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
#ifndef BTL_CONFIG_H
#define BTL_CONFIG_H

//
// Bootloader Version
//
#define BOOTLOADER_VERSION_MAIN_MAJOR             2
#define BOOTLOADER_VERSION_MAIN_MINOR             0

#include "core/btl_util.h"

MISRAC_DISABLE
#include "em_device.h"
MISRAC_ENABLE

//
// Bootloader configuration
#ifdef BTL_CONFIG_FILE
  #include BTL_CONFIG_FILE
#else
#include "btl_core_cfg.h"
#endif

#ifndef BOOTLOADER_VERSION_MAIN_CUSTOMER
#define BOOTLOADER_VERSION_MAIN_CUSTOMER          1
#endif

#define BOOTLOADER_VERSION_MAIN (BOOTLOADER_VERSION_MAIN_MAJOR   << 24 \
                                 | BOOTLOADER_VERSION_MAIN_MINOR << 16 \
                                 | BOOTLOADER_VERSION_MAIN_CUSTOMER)

#ifdef BTL_SLOT_CONFIGURATION
  #include BTL_SLOT_CONFIGURATION
#endif

#ifndef BOOTLOADER_ENFORCE_SECURE_BOOT
#define BOOTLOADER_ENFORCE_SECURE_BOOT (true)
#endif

// Address of bootloader upgrade location
// Fixed upgrade address for Series 1 devices
#if defined(_SILICON_LABS_32B_SERIES_1) && !defined(BTL_UPGRADE_LOCATION_BASE)
#define BTL_UPGRADE_LOCATION_BASE  0x8000UL
#endif // _SILICON_LABS_32B_SERIES_1

#ifndef BTL_UPGRADE_LOCATION
#define BTL_UPGRADE_LOCATION (FLASH_BASE + BTL_UPGRADE_LOCATION_BASE)
#endif

//
// Option validation
//

#if defined(BTL_UPGRADE_LOCATION_BASE)
// BTL_UPGRADE_LOCATION_BASE is fixed on Series-1 devices.
#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_1)

// The upgrade location needs to fit upgrades of up to 48k
#if ((BTL_UPGRADE_LOCATION_BASE + 0x0000C000UL) > FLASH_SIZE) \
  || (BTL_UPGRADE_LOCATION_BASE % FLASH_PAGE_SIZE)
#error "Invalid bootloader upgrade base address"
#endif

#elif defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)

// The upgrade location needs to fit upgrades of up to 24k
#if ((BTL_UPGRADE_LOCATION_BASE + 0x00006000UL) > FLASH_SIZE) \
  || (BTL_UPGRADE_LOCATION_BASE % FLASH_PAGE_SIZE)
#error "Invalid bootloader upgrade base address"
#endif

#elif defined(_SILICON_LABS_32B_SERIES_2_CONFIG_3)
// The upgrade location needs to fit upgrades of up to 96k
#if ((BTL_UPGRADE_LOCATION_BASE + 0x00018000UL) > FLASH_SIZE) \
  || (BTL_UPGRADE_LOCATION_BASE % FLASH_PAGE_SIZE)
#error "Invalid bootloader upgrade base address"
#endif

#endif

#if defined(_SILICON_LABS_32B_SERIES_2)
#include "api/btl_interface.h"
#if (BTL_UPGRADE_LOCATION_BASE < BTL_MAIN_STAGE_MAX_SIZE)
#error "Invalid bootloader upgrade base address"
#endif
#endif // defined(_SILICON_LABS_32B_SERIES_2)

#endif // defined(BTL_UPGRADE_LOCATION_BASE)
#endif // BTL_CONFIG_H
