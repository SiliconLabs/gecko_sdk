/***************************************************************************//**
 * @file
 * @brief System API (Generic)
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef EM_SYSTEM_GENERIC_H
#define EM_SYSTEM_GENERIC_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup system
 * @{
 ******************************************************************************/

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** Family security capability. */
typedef enum {
  securityCapabilityUnknown, /**< Unknown security capability. */
  securityCapabilityNA,      /**< Security capability not applicable. */
  securityCapabilityBasic,   /**< Basic security capability. */
  securityCapabilityRoT,     /**< Root of Trust security capability. */
  securityCapabilitySE,      /**< Secure Element security capability. */
  securityCapabilityVault    /**< Secure Vault security capability. */
} SYSTEM_SecurityCapability_TypeDef;

/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** DEVINFO calibration address/value pair. */
typedef struct {
  uint32_t address;                       /**< Peripheral calibration register address. */
  uint32_t calValue;                      /**< Calibration value for register at address. */
}
SYSTEM_CalAddrVal_TypeDef;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

bool                              SYSTEM_GetCalibrationValue(volatile uint32_t *regAddress);
SYSTEM_SecurityCapability_TypeDef SYSTEM_GetSecurityCapability(void);
uint64_t                          SYSTEM_GetUnique(void);
uint8_t                           SYSTEM_GetProdRev(void);
uint32_t                          SYSTEM_GetSRAMBaseAddress(void);
uint16_t                          SYSTEM_GetSRAMSize(void);
uint16_t                          SYSTEM_GetFlashSize(void);
uint32_t                          SYSTEM_GetFlashPageSize(void);
uint16_t                          SYSTEM_GetPartNumber(void);
uint8_t                           SYSTEM_GetCalibrationTemperature(void);

/** @} (end addtogroup system) */

#ifdef __cplusplus
}
#endif

#endif /* EM_SYSTEM_GENERIC_H */
