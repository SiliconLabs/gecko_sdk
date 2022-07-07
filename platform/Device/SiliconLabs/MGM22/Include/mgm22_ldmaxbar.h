/**************************************************************************//**
 * @file
 * @brief MGM22 LDMAXBAR register and bit field definitions
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
#ifndef MGM22_LDMAXBAR_H
#define MGM22_LDMAXBAR_H
#define LDMAXBAR_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup MGM22_LDMAXBAR LDMAXBAR
 * @{
 * @brief MGM22 LDMAXBAR Register Declaration.
 *****************************************************************************/

/** LDMAXBAR CH Register Group Declaration. */
typedef struct {
  __IOM uint32_t REQSEL;                             /**< Channel Peripheral Request Select Reg...           */
} LDMAXBAR_CH_TypeDef;

/** LDMAXBAR Register Declaration. */
typedef struct {
  LDMAXBAR_CH_TypeDef CH[8U];                   /**< DMA Channel Registers                              */
  uint32_t            RESERVED0[1016U];         /**< Reserved for future use                            */
  LDMAXBAR_CH_TypeDef CH_SET[8U];               /**< DMA Channel Registers                              */
  uint32_t            RESERVED1[1016U];         /**< Reserved for future use                            */
  LDMAXBAR_CH_TypeDef CH_CLR[8U];               /**< DMA Channel Registers                              */
  uint32_t            RESERVED2[1016U];         /**< Reserved for future use                            */
  LDMAXBAR_CH_TypeDef CH_TGL[8U];               /**< DMA Channel Registers                              */
} LDMAXBAR_TypeDef;
/** @} End of group MGM22_LDMAXBAR */

/**************************************************************************//**
 * @addtogroup MGM22_LDMAXBAR
 * @{
 * @defgroup MGM22_LDMAXBAR_BitFields LDMAXBAR Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for LDMAXBAR CH_REQSEL */
#define _LDMAXBAR_CH_REQSEL_RESETVALUE           0x00000000UL                                  /**< Default value for LDMAXBAR_CH_REQSEL        */
#define _LDMAXBAR_CH_REQSEL_MASK                 0x003F000FUL                                  /**< Mask for LDMAXBAR_CH_REQSEL                 */
#define _LDMAXBAR_CH_REQSEL_SIGSEL_SHIFT         0                                             /**< Shift value for LDMAXBAR_SIGSEL             */
#define _LDMAXBAR_CH_REQSEL_SIGSEL_MASK          0xFUL                                         /**< Bit mask for LDMAXBAR_SIGSEL                */
#define _LDMAXBAR_CH_REQSEL_SIGSEL_DEFAULT       0x00000000UL                                  /**< Mode DEFAULT for LDMAXBAR_CH_REQSEL         */
#define LDMAXBAR_CH_REQSEL_SIGSEL_DEFAULT        (_LDMAXBAR_CH_REQSEL_SIGSEL_DEFAULT << 0)     /**< Shifted mode DEFAULT for LDMAXBAR_CH_REQSEL */
#define _LDMAXBAR_CH_REQSEL_SOURCESEL_SHIFT      16                                            /**< Shift value for LDMAXBAR_SOURCESEL          */
#define _LDMAXBAR_CH_REQSEL_SOURCESEL_MASK       0x3F0000UL                                    /**< Bit mask for LDMAXBAR_SOURCESEL             */
#define _LDMAXBAR_CH_REQSEL_SOURCESEL_DEFAULT    0x00000000UL                                  /**< Mode DEFAULT for LDMAXBAR_CH_REQSEL         */
#define LDMAXBAR_CH_REQSEL_SOURCESEL_DEFAULT     (_LDMAXBAR_CH_REQSEL_SOURCESEL_DEFAULT << 16) /**< Shifted mode DEFAULT for LDMAXBAR_CH_REQSEL */

/** @} End of group MGM22_LDMAXBAR_BitFields */
/** @} End of group MGM22_LDMAXBAR */
/** @} End of group Parts */

#endif /* MGM22_LDMAXBAR_H */
