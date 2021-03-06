/***************************************************************************//**
 * @file
 * @brief CRC16 veneer functions.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

// -----------------------------------------------------------------------------
// Includes

#include "core/btl_tz_utils.h"
#include "security/btl_crc16.h"

// -----------------------------------------------------------------------------
// NSC functions

__attribute__((cmse_nonsecure_entry))
uint16_t btl_nsc_crc16(const uint8_t newByte, uint16_t prevResult)
{
  return btl_crc16(newByte, prevResult);
}

__attribute__((cmse_nonsecure_entry))
uint16_t btl_nsc_crc16Stream(const uint8_t *buffer,
                             size_t        length,
                             uint16_t      prevResult)
{
  if (!bl_verify_ns_memory_access(buffer, length)) {
    bl_fatal_assert_action();
  }

  return btl_crc16Stream(buffer, length, prevResult);
}
