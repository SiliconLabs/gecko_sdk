/**************************************************************************//**
 * @file
 * @brief EFR32FG25 OBIRAM register and bit field definitions
 ******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories, Inc. www.silabs.com</b>
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
#ifndef EFR32FG25_OBIRAM_H
#define EFR32FG25_OBIRAM_H
#define OBIRAM_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_OBIRAM OBIRAM
 * @{
 * @brief EFR32FG25 OBIRAM Register Declaration.
 *****************************************************************************/

/** OBIRAM Register Declaration. */
typedef struct {
  __IM uint32_t  IPVERSION;                     /**< IP version ID                                      */
  __IOM uint32_t CMD;                           /**< Command register                                   */
  __IOM uint32_t CTRL;                          /**< Control register                                   */
  __IM uint32_t  ECCERRADDR0;                   /**< ECC error address                                  */
  __IM uint32_t  ECCMERRIND;                    /**< ECC multiple error indication                      */
  __IOM uint32_t IF;                            /**< Interrupt flags                                    */
  __IOM uint32_t IEN;                           /**< Interrupt enable                                   */
  uint32_t       RESERVED0[1017U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP version ID                                      */
  __IOM uint32_t CMD_SET;                       /**< Command register                                   */
  __IOM uint32_t CTRL_SET;                      /**< Control register                                   */
  __IM uint32_t  ECCERRADDR0_SET;               /**< ECC error address                                  */
  __IM uint32_t  ECCMERRIND_SET;                /**< ECC multiple error indication                      */
  __IOM uint32_t IF_SET;                        /**< Interrupt flags                                    */
  __IOM uint32_t IEN_SET;                       /**< Interrupt enable                                   */
  uint32_t       RESERVED1[1017U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP version ID                                      */
  __IOM uint32_t CMD_CLR;                       /**< Command register                                   */
  __IOM uint32_t CTRL_CLR;                      /**< Control register                                   */
  __IM uint32_t  ECCERRADDR0_CLR;               /**< ECC error address                                  */
  __IM uint32_t  ECCMERRIND_CLR;                /**< ECC multiple error indication                      */
  __IOM uint32_t IF_CLR;                        /**< Interrupt flags                                    */
  __IOM uint32_t IEN_CLR;                       /**< Interrupt enable                                   */
  uint32_t       RESERVED2[1017U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP version ID                                      */
  __IOM uint32_t CMD_TGL;                       /**< Command register                                   */
  __IOM uint32_t CTRL_TGL;                      /**< Control register                                   */
  __IM uint32_t  ECCERRADDR0_TGL;               /**< ECC error address                                  */
  __IM uint32_t  ECCMERRIND_TGL;                /**< ECC multiple error indication                      */
  __IOM uint32_t IF_TGL;                        /**< Interrupt flags                                    */
  __IOM uint32_t IEN_TGL;                       /**< Interrupt enable                                   */
} OBIRAM_TypeDef;
/** @} End of group EFR32FG25_OBIRAM */

/**************************************************************************//**
 * @addtogroup EFR32FG25_OBIRAM
 * @{
 * @defgroup EFR32FG25_OBIRAM_BitFields OBIRAM Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for OBIRAM IPVERSION */
#define _OBIRAM_IPVERSION_RESETVALUE           0x00000001UL                               /**< Default value for OBIRAM_IPVERSION          */
#define _OBIRAM_IPVERSION_MASK                 0x00000001UL                               /**< Mask for OBIRAM_IPVERSION                   */
#define OBIRAM_IPVERSION_IPVERSION             (0x1UL << 0)                               /**< IP version ID                               */
#define _OBIRAM_IPVERSION_IPVERSION_SHIFT      0                                          /**< Shift value for OBIRAM_IPVERSION            */
#define _OBIRAM_IPVERSION_IPVERSION_MASK       0x1UL                                      /**< Bit mask for OBIRAM_IPVERSION               */
#define _OBIRAM_IPVERSION_IPVERSION_DEFAULT    0x00000001UL                               /**< Mode DEFAULT for OBIRAM_IPVERSION           */
#define OBIRAM_IPVERSION_IPVERSION_DEFAULT     (_OBIRAM_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for OBIRAM_IPVERSION   */

/* Bit fields for OBIRAM CMD */
#define _OBIRAM_CMD_RESETVALUE                 0x00000000UL                             /**< Default value for OBIRAM_CMD                */
#define _OBIRAM_CMD_MASK                       0x00000001UL                             /**< Mask for OBIRAM_CMD                         */
#define OBIRAM_CMD_CLEARECCADDR0               (0x1UL << 0)                             /**< Clear ECCERRADD0                            */
#define _OBIRAM_CMD_CLEARECCADDR0_SHIFT        0                                        /**< Shift value for OBIRAM_CLEARECCADDR0        */
#define _OBIRAM_CMD_CLEARECCADDR0_MASK         0x1UL                                    /**< Bit mask for OBIRAM_CLEARECCADDR0           */
#define _OBIRAM_CMD_CLEARECCADDR0_DEFAULT      0x00000000UL                             /**< Mode DEFAULT for OBIRAM_CMD                 */
#define OBIRAM_CMD_CLEARECCADDR0_DEFAULT       (_OBIRAM_CMD_CLEARECCADDR0_DEFAULT << 0) /**< Shifted mode DEFAULT for OBIRAM_CMD         */

/* Bit fields for OBIRAM CTRL */
#define _OBIRAM_CTRL_RESETVALUE                0x00000002UL                              /**< Default value for OBIRAM_CTRL               */
#define _OBIRAM_CTRL_MASK                      0x00000007UL                              /**< Mask for OBIRAM_CTRL                        */
#define OBIRAM_CTRL_ECCEN                      (0x1UL << 0)                              /**< Enable ECC                                  */
#define _OBIRAM_CTRL_ECCEN_SHIFT               0                                         /**< Shift value for OBIRAM_ECCEN                */
#define _OBIRAM_CTRL_ECCEN_MASK                0x1UL                                     /**< Bit mask for OBIRAM_ECCEN                   */
#define _OBIRAM_CTRL_ECCEN_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for OBIRAM_CTRL                */
#define OBIRAM_CTRL_ECCEN_DEFAULT              (_OBIRAM_CTRL_ECCEN_DEFAULT << 0)         /**< Shifted mode DEFAULT for OBIRAM_CTRL        */
#define OBIRAM_CTRL_ECCWEN                     (0x1UL << 1)                              /**< Enable ECC writes                           */
#define _OBIRAM_CTRL_ECCWEN_SHIFT              1                                         /**< Shift value for OBIRAM_ECCWEN               */
#define _OBIRAM_CTRL_ECCWEN_MASK               0x2UL                                     /**< Bit mask for OBIRAM_ECCWEN                  */
#define _OBIRAM_CTRL_ECCWEN_DEFAULT            0x00000001UL                              /**< Mode DEFAULT for OBIRAM_CTRL                */
#define OBIRAM_CTRL_ECCWEN_DEFAULT             (_OBIRAM_CTRL_ECCWEN_DEFAULT << 1)        /**< Shifted mode DEFAULT for OBIRAM_CTRL        */
#define OBIRAM_CTRL_ECCERRFAULTEN              (0x1UL << 2)                              /**< 2bit ECC Error bus fault enable             */
#define _OBIRAM_CTRL_ECCERRFAULTEN_SHIFT       2                                         /**< Shift value for OBIRAM_ECCERRFAULTEN        */
#define _OBIRAM_CTRL_ECCERRFAULTEN_MASK        0x4UL                                     /**< Bit mask for OBIRAM_ECCERRFAULTEN           */
#define _OBIRAM_CTRL_ECCERRFAULTEN_DEFAULT     0x00000000UL                              /**< Mode DEFAULT for OBIRAM_CTRL                */
#define OBIRAM_CTRL_ECCERRFAULTEN_DEFAULT      (_OBIRAM_CTRL_ECCERRFAULTEN_DEFAULT << 2) /**< Shifted mode DEFAULT for OBIRAM_CTRL        */

/* Bit fields for OBIRAM ECCERRADDR0 */
#define _OBIRAM_ECCERRADDR0_RESETVALUE         0x00000000UL                             /**< Default value for OBIRAM_ECCERRADDR0        */
#define _OBIRAM_ECCERRADDR0_MASK               0xFFFFFFFFUL                             /**< Mask for OBIRAM_ECCERRADDR0                 */
#define _OBIRAM_ECCERRADDR0_ADDR_SHIFT         0                                        /**< Shift value for OBIRAM_ADDR                 */
#define _OBIRAM_ECCERRADDR0_ADDR_MASK          0xFFFFFFFFUL                             /**< Bit mask for OBIRAM_ADDR                    */
#define _OBIRAM_ECCERRADDR0_ADDR_DEFAULT       0x00000000UL                             /**< Mode DEFAULT for OBIRAM_ECCERRADDR0         */
#define OBIRAM_ECCERRADDR0_ADDR_DEFAULT        (_OBIRAM_ECCERRADDR0_ADDR_DEFAULT << 0)  /**< Shifted mode DEFAULT for OBIRAM_ECCERRADDR0 */

/* Bit fields for OBIRAM ECCMERRIND */
#define _OBIRAM_ECCMERRIND_RESETVALUE          0x00000000UL                             /**< Default value for OBIRAM_ECCMERRIND         */
#define _OBIRAM_ECCMERRIND_MASK                0x00000001UL                             /**< Mask for OBIRAM_ECCMERRIND                  */
#define OBIRAM_ECCMERRIND_P0                   (0x1UL << 0)                             /**< Multiple ECC errors                         */
#define _OBIRAM_ECCMERRIND_P0_SHIFT            0                                        /**< Shift value for OBIRAM_P0                   */
#define _OBIRAM_ECCMERRIND_P0_MASK             0x1UL                                    /**< Bit mask for OBIRAM_P0                      */
#define _OBIRAM_ECCMERRIND_P0_DEFAULT          0x00000000UL                             /**< Mode DEFAULT for OBIRAM_ECCMERRIND          */
#define OBIRAM_ECCMERRIND_P0_DEFAULT           (_OBIRAM_ECCMERRIND_P0_DEFAULT << 0)     /**< Shifted mode DEFAULT for OBIRAM_ECCMERRIND  */

/* Bit fields for OBIRAM IF */
#define _OBIRAM_IF_RESETVALUE                  0x00000000UL                             /**< Default value for OBIRAM_IF                 */
#define _OBIRAM_IF_MASK                        0x00000003UL                             /**< Mask for OBIRAM_IF                          */
#define OBIRAM_IF_ERR1B                        (0x1UL << 0)                             /**< 1-bit ECC Error Interrupt Flag              */
#define _OBIRAM_IF_ERR1B_SHIFT                 0                                        /**< Shift value for OBIRAM_ERR1B                */
#define _OBIRAM_IF_ERR1B_MASK                  0x1UL                                    /**< Bit mask for OBIRAM_ERR1B                   */
#define _OBIRAM_IF_ERR1B_DEFAULT               0x00000000UL                             /**< Mode DEFAULT for OBIRAM_IF                  */
#define OBIRAM_IF_ERR1B_DEFAULT                (_OBIRAM_IF_ERR1B_DEFAULT << 0)          /**< Shifted mode DEFAULT for OBIRAM_IF          */
#define OBIRAM_IF_ERR2B                        (0x1UL << 1)                             /**< 2-bit ECC Error Interrupt Flag              */
#define _OBIRAM_IF_ERR2B_SHIFT                 1                                        /**< Shift value for OBIRAM_ERR2B                */
#define _OBIRAM_IF_ERR2B_MASK                  0x2UL                                    /**< Bit mask for OBIRAM_ERR2B                   */
#define _OBIRAM_IF_ERR2B_DEFAULT               0x00000000UL                             /**< Mode DEFAULT for OBIRAM_IF                  */
#define OBIRAM_IF_ERR2B_DEFAULT                (_OBIRAM_IF_ERR2B_DEFAULT << 1)          /**< Shifted mode DEFAULT for OBIRAM_IF          */

/* Bit fields for OBIRAM IEN */
#define _OBIRAM_IEN_RESETVALUE                 0x00000000UL                             /**< Default value for OBIRAM_IEN                */
#define _OBIRAM_IEN_MASK                       0x00000003UL                             /**< Mask for OBIRAM_IEN                         */
#define OBIRAM_IEN_ERR1B                       (0x1UL << 0)                             /**< 1-bit ECC Error Interrupt Enable            */
#define _OBIRAM_IEN_ERR1B_SHIFT                0                                        /**< Shift value for OBIRAM_ERR1B                */
#define _OBIRAM_IEN_ERR1B_MASK                 0x1UL                                    /**< Bit mask for OBIRAM_ERR1B                   */
#define _OBIRAM_IEN_ERR1B_DEFAULT              0x00000000UL                             /**< Mode DEFAULT for OBIRAM_IEN                 */
#define OBIRAM_IEN_ERR1B_DEFAULT               (_OBIRAM_IEN_ERR1B_DEFAULT << 0)         /**< Shifted mode DEFAULT for OBIRAM_IEN         */
#define OBIRAM_IEN_ERR2B                       (0x1UL << 1)                             /**< 2-bit ECC Error Interrupt Enable            */
#define _OBIRAM_IEN_ERR2B_SHIFT                1                                        /**< Shift value for OBIRAM_ERR2B                */
#define _OBIRAM_IEN_ERR2B_MASK                 0x2UL                                    /**< Bit mask for OBIRAM_ERR2B                   */
#define _OBIRAM_IEN_ERR2B_DEFAULT              0x00000000UL                             /**< Mode DEFAULT for OBIRAM_IEN                 */
#define OBIRAM_IEN_ERR2B_DEFAULT               (_OBIRAM_IEN_ERR2B_DEFAULT << 1)         /**< Shifted mode DEFAULT for OBIRAM_IEN         */

/** @} End of group EFR32FG25_OBIRAM_BitFields */
/** @} End of group EFR32FG25_OBIRAM */
/** @} End of group Parts */

#endif /* EFR32FG25_OBIRAM_H */
