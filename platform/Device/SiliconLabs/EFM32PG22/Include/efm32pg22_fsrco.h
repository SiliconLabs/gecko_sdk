/**************************************************************************//**
 * @file
 * @brief EFM32PG22 FSRCO register and bit field definitions
 ******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories, Inc. www.silabs.com</b>
 ******************************************************************************
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
 *****************************************************************************/
#ifndef EFM32PG22_FSRCO_H
#define EFM32PG22_FSRCO_H
#define FSRCO_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFM32PG22_FSRCO FSRCO
 * @{
 * @brief EFM32PG22 FSRCO Register Declaration.
 *****************************************************************************/

/** FSRCO Register Declaration. */
typedef struct {
  __IM uint32_t IPVERSION;                      /**< IP Version                                         */
  uint32_t      RESERVED0[1023U];               /**< Reserved for future use                            */
  __IM uint32_t IPVERSION_SET;                  /**< IP Version                                         */
  uint32_t      RESERVED1[1023U];               /**< Reserved for future use                            */
  __IM uint32_t IPVERSION_CLR;                  /**< IP Version                                         */
  uint32_t      RESERVED2[1023U];               /**< Reserved for future use                            */
  __IM uint32_t IPVERSION_TGL;                  /**< IP Version                                         */
} FSRCO_TypeDef;
/** @} End of group EFM32PG22_FSRCO */

/**************************************************************************//**
 * @addtogroup EFM32PG22_FSRCO
 * @{
 * @defgroup EFM32PG22_FSRCO_BitFields FSRCO Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for FSRCO IPVERSION */
#define _FSRCO_IPVERSION_RESETVALUE           0x00000000UL                              /**< Default value for FSRCO_IPVERSION           */
#define _FSRCO_IPVERSION_MASK                 0xFFFFFFFFUL                              /**< Mask for FSRCO_IPVERSION                    */
#define _FSRCO_IPVERSION_IPVERSION_SHIFT      0                                         /**< Shift value for FSRCO_IPVERSION             */
#define _FSRCO_IPVERSION_IPVERSION_MASK       0xFFFFFFFFUL                              /**< Bit mask for FSRCO_IPVERSION                */
#define _FSRCO_IPVERSION_IPVERSION_DEFAULT    0x00000000UL                              /**< Mode DEFAULT for FSRCO_IPVERSION            */
#define FSRCO_IPVERSION_IPVERSION_DEFAULT     (_FSRCO_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for FSRCO_IPVERSION    */

/** @} End of group EFM32PG22_FSRCO_BitFields */
/** @} End of group EFM32PG22_FSRCO */
/** @} End of group Parts */

#endif /* EFM32PG22_FSRCO_H */
