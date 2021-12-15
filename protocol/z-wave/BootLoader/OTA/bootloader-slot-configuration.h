/**
 * @file
 * Contains memory addresses for the bootloader.
 * @attention This file MUST NOT be changed.
 * @copyright 2019 Silicon Laboratories Inc.
 */
#ifndef __SI_BOOTLOADER_CONFIG__
#define __SI_BOOTLOADER_CONFIG__

#define BTL_PLUGIN_STORAGE_NUM_SLOTS (1)

#ifdef _SILICON_LABS_32B_SERIES_2
#define BTL_STORAGE_SLOT_START_ADDRESS 0x08042000
#define BTL_STORAGE_SLOT_SIZE 172032U
#endif
#ifdef _SILICON_LABS_32B_SERIES_1
#define BTL_STORAGE_SLOT_START_ADDRESS 237568U
#define BTL_STORAGE_SLOT_SIZE 237568U
#endif
#define BTL_PLUGIN_STORAGE_SLOTS  \
  {\
    {BTL_STORAGE_SLOT_START_ADDRESS, BTL_STORAGE_SLOT_SIZE}, /* Slot 0 */ \
  }\

// Number of slots in bootload list
#define BTL_STORAGE_BOOTLOAD_LIST_LENGTH BTL_PLUGIN_STORAGE_NUM_SLOTS

#endif // __SI_BOOTLOADER_CONFIG__
