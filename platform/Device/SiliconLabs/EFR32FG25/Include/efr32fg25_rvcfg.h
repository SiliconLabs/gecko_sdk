/**************************************************************************//**
 * @file
 * @brief EFR32FG25 RVCFG register and bit field definitions
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
#ifndef EFR32FG25_RVCFG_H
#define EFR32FG25_RVCFG_H
#define RVCFG_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_RVCFG RVCFG
 * @{
 * @brief EFR32FG25 RVCFG Register Declaration.
 *****************************************************************************/

/** RVCFG Register Declaration. */
typedef struct {
  __IM uint32_t  IPVERSION;                     /**< IP version ID                                      */
  __IOM uint32_t SWRST;                         /**< Software reset                                     */
  __IOM uint32_t FETCHENABLE;                   /**< CPU fetch enable                                   */
  __IOM uint32_t BOOTADDRCFG;                   /**< RISC-V boot address                                */
  __IOM uint32_t MTVECADDRCFG;                  /**< RISC-V MTVEC address                               */
  __IOM uint32_t IF;                            /**< Interrupt flags                                    */
  __IOM uint32_t IEN;                           /**< Interrupt enable                                   */
  __IOM uint32_t ISO;                           /**< OBI isolation control register                     */
  __IM uint32_t  ISOSTATUS;                     /**< OBI isolation status register                      */
  __IM uint32_t  STATUS;                        /**< Status register                                    */
  uint32_t       RESERVED0[1014U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP version ID                                      */
  __IOM uint32_t SWRST_SET;                     /**< Software reset                                     */
  __IOM uint32_t FETCHENABLE_SET;               /**< CPU fetch enable                                   */
  __IOM uint32_t BOOTADDRCFG_SET;               /**< RISC-V boot address                                */
  __IOM uint32_t MTVECADDRCFG_SET;              /**< RISC-V MTVEC address                               */
  __IOM uint32_t IF_SET;                        /**< Interrupt flags                                    */
  __IOM uint32_t IEN_SET;                       /**< Interrupt enable                                   */
  __IOM uint32_t ISO_SET;                       /**< OBI isolation control register                     */
  __IM uint32_t  ISOSTATUS_SET;                 /**< OBI isolation status register                      */
  __IM uint32_t  STATUS_SET;                    /**< Status register                                    */
  uint32_t       RESERVED1[1014U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP version ID                                      */
  __IOM uint32_t SWRST_CLR;                     /**< Software reset                                     */
  __IOM uint32_t FETCHENABLE_CLR;               /**< CPU fetch enable                                   */
  __IOM uint32_t BOOTADDRCFG_CLR;               /**< RISC-V boot address                                */
  __IOM uint32_t MTVECADDRCFG_CLR;              /**< RISC-V MTVEC address                               */
  __IOM uint32_t IF_CLR;                        /**< Interrupt flags                                    */
  __IOM uint32_t IEN_CLR;                       /**< Interrupt enable                                   */
  __IOM uint32_t ISO_CLR;                       /**< OBI isolation control register                     */
  __IM uint32_t  ISOSTATUS_CLR;                 /**< OBI isolation status register                      */
  __IM uint32_t  STATUS_CLR;                    /**< Status register                                    */
  uint32_t       RESERVED2[1014U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP version ID                                      */
  __IOM uint32_t SWRST_TGL;                     /**< Software reset                                     */
  __IOM uint32_t FETCHENABLE_TGL;               /**< CPU fetch enable                                   */
  __IOM uint32_t BOOTADDRCFG_TGL;               /**< RISC-V boot address                                */
  __IOM uint32_t MTVECADDRCFG_TGL;              /**< RISC-V MTVEC address                               */
  __IOM uint32_t IF_TGL;                        /**< Interrupt flags                                    */
  __IOM uint32_t IEN_TGL;                       /**< Interrupt enable                                   */
  __IOM uint32_t ISO_TGL;                       /**< OBI isolation control register                     */
  __IM uint32_t  ISOSTATUS_TGL;                 /**< OBI isolation status register                      */
  __IM uint32_t  STATUS_TGL;                    /**< Status register                                    */
} RVCFG_TypeDef;
/** @} End of group EFR32FG25_RVCFG */

/**************************************************************************//**
 * @addtogroup EFR32FG25_RVCFG
 * @{
 * @defgroup EFR32FG25_RVCFG_BitFields RVCFG Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for RVCFG IPVERSION */
#define _RVCFG_IPVERSION_RESETVALUE                 0x00000001UL                              /**< Default value for RVCFG_IPVERSION           */
#define _RVCFG_IPVERSION_MASK                       0x00000001UL                              /**< Mask for RVCFG_IPVERSION                    */
#define RVCFG_IPVERSION_IPVERSION                   (0x1UL << 0)                              /**< IP version ID                               */
#define _RVCFG_IPVERSION_IPVERSION_SHIFT            0                                         /**< Shift value for RVCFG_IPVERSION             */
#define _RVCFG_IPVERSION_IPVERSION_MASK             0x1UL                                     /**< Bit mask for RVCFG_IPVERSION                */
#define _RVCFG_IPVERSION_IPVERSION_DEFAULT          0x00000001UL                              /**< Mode DEFAULT for RVCFG_IPVERSION            */
#define RVCFG_IPVERSION_IPVERSION_DEFAULT           (_RVCFG_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for RVCFG_IPVERSION    */

/* Bit fields for RVCFG SWRST */
#define _RVCFG_SWRST_RESETVALUE                     0x00000000UL                          /**< Default value for RVCFG_SWRST               */
#define _RVCFG_SWRST_MASK                           0x00000003UL                          /**< Mask for RVCFG_SWRST                        */
#define RVCFG_SWRST_SWRST                           (0x1UL << 0)                          /**< Software reset                              */
#define _RVCFG_SWRST_SWRST_SHIFT                    0                                     /**< Shift value for RVCFG_SWRST                 */
#define _RVCFG_SWRST_SWRST_MASK                     0x1UL                                 /**< Bit mask for RVCFG_SWRST                    */
#define _RVCFG_SWRST_SWRST_DEFAULT                  0x00000000UL                          /**< Mode DEFAULT for RVCFG_SWRST                */
#define RVCFG_SWRST_SWRST_DEFAULT                   (_RVCFG_SWRST_SWRST_DEFAULT << 0)     /**< Shifted mode DEFAULT for RVCFG_SWRST        */
#define RVCFG_SWRST_RESETTING                       (0x1UL << 1)                          /**< Software reset busy status                  */
#define _RVCFG_SWRST_RESETTING_SHIFT                1                                     /**< Shift value for RVCFG_RESETTING             */
#define _RVCFG_SWRST_RESETTING_MASK                 0x2UL                                 /**< Bit mask for RVCFG_RESETTING                */
#define _RVCFG_SWRST_RESETTING_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for RVCFG_SWRST                */
#define RVCFG_SWRST_RESETTING_DEFAULT               (_RVCFG_SWRST_RESETTING_DEFAULT << 1) /**< Shifted mode DEFAULT for RVCFG_SWRST        */

/* Bit fields for RVCFG FETCHENABLE */
#define _RVCFG_FETCHENABLE_RESETVALUE               0x00000000UL                                  /**< Default value for RVCFG_FETCHENABLE         */
#define _RVCFG_FETCHENABLE_MASK                     0x00000001UL                                  /**< Mask for RVCFG_FETCHENABLE                  */
#define RVCFG_FETCHENABLE_FETCHENABLE               (0x1UL << 0)                                  /**< CPU instruction fetch enable                */
#define _RVCFG_FETCHENABLE_FETCHENABLE_SHIFT        0                                             /**< Shift value for RVCFG_FETCHENABLE           */
#define _RVCFG_FETCHENABLE_FETCHENABLE_MASK         0x1UL                                         /**< Bit mask for RVCFG_FETCHENABLE              */
#define _RVCFG_FETCHENABLE_FETCHENABLE_DEFAULT      0x00000000UL                                  /**< Mode DEFAULT for RVCFG_FETCHENABLE          */
#define RVCFG_FETCHENABLE_FETCHENABLE_DEFAULT       (_RVCFG_FETCHENABLE_FETCHENABLE_DEFAULT << 0) /**< Shifted mode DEFAULT for RVCFG_FETCHENABLE  */

/* Bit fields for RVCFG BOOTADDRCFG */
#define _RVCFG_BOOTADDRCFG_RESETVALUE               0x00000000UL                                  /**< Default value for RVCFG_BOOTADDRCFG         */
#define _RVCFG_BOOTADDRCFG_MASK                     0xFFFFFFFFUL                                  /**< Mask for RVCFG_BOOTADDRCFG                  */
#define _RVCFG_BOOTADDRCFG_BOOTADDRCFG_SHIFT        0                                             /**< Shift value for RVCFG_BOOTADDRCFG           */
#define _RVCFG_BOOTADDRCFG_BOOTADDRCFG_MASK         0xFFFFFFFFUL                                  /**< Bit mask for RVCFG_BOOTADDRCFG              */
#define _RVCFG_BOOTADDRCFG_BOOTADDRCFG_DEFAULT      0x00000000UL                                  /**< Mode DEFAULT for RVCFG_BOOTADDRCFG          */
#define RVCFG_BOOTADDRCFG_BOOTADDRCFG_DEFAULT       (_RVCFG_BOOTADDRCFG_BOOTADDRCFG_DEFAULT << 0) /**< Shifted mode DEFAULT for RVCFG_BOOTADDRCFG  */

/* Bit fields for RVCFG MTVECADDRCFG */
#define _RVCFG_MTVECADDRCFG_RESETVALUE              0x00000000UL                                    /**< Default value for RVCFG_MTVECADDRCFG        */
#define _RVCFG_MTVECADDRCFG_MASK                    0xFFFFFF00UL                                    /**< Mask for RVCFG_MTVECADDRCFG                 */
#define _RVCFG_MTVECADDRCFG_MTVECADDRCFG_SHIFT      8                                               /**< Shift value for RVCFG_MTVECADDRCFG          */
#define _RVCFG_MTVECADDRCFG_MTVECADDRCFG_MASK       0xFFFFFF00UL                                    /**< Bit mask for RVCFG_MTVECADDRCFG             */
#define _RVCFG_MTVECADDRCFG_MTVECADDRCFG_DEFAULT    0x00000000UL                                    /**< Mode DEFAULT for RVCFG_MTVECADDRCFG         */
#define RVCFG_MTVECADDRCFG_MTVECADDRCFG_DEFAULT     (_RVCFG_MTVECADDRCFG_MTVECADDRCFG_DEFAULT << 8) /**< Shifted mode DEFAULT for RVCFG_MTVECADDRCFG */

/* Bit fields for RVCFG IF */
#define _RVCFG_IF_RESETVALUE                        0x00000000UL                        /**< Default value for RVCFG_IF                  */
#define _RVCFG_IF_MASK                              0x00000007UL                        /**< Mask for RVCFG_IF                           */
#define RVCFG_IF_INSTR0ERR                          (0x1UL << 0)                        /**< CPU instruction bus error                   */
#define _RVCFG_IF_INSTR0ERR_SHIFT                   0                                   /**< Shift value for RVCFG_INSTR0ERR             */
#define _RVCFG_IF_INSTR0ERR_MASK                    0x1UL                               /**< Bit mask for RVCFG_INSTR0ERR                */
#define _RVCFG_IF_INSTR0ERR_DEFAULT                 0x00000000UL                        /**< Mode DEFAULT for RVCFG_IF                   */
#define RVCFG_IF_INSTR0ERR_DEFAULT                  (_RVCFG_IF_INSTR0ERR_DEFAULT << 0)  /**< Shifted mode DEFAULT for RVCFG_IF           */
#define RVCFG_IF_DATA0ERR                           (0x1UL << 1)                        /**< CPU data bus error                          */
#define _RVCFG_IF_DATA0ERR_SHIFT                    1                                   /**< Shift value for RVCFG_DATA0ERR              */
#define _RVCFG_IF_DATA0ERR_MASK                     0x2UL                               /**< Bit mask for RVCFG_DATA0ERR                 */
#define _RVCFG_IF_DATA0ERR_DEFAULT                  0x00000000UL                        /**< Mode DEFAULT for RVCFG_IF                   */
#define RVCFG_IF_DATA0ERR_DEFAULT                   (_RVCFG_IF_DATA0ERR_DEFAULT << 1)   /**< Shifted mode DEFAULT for RVCFG_IF           */
#define RVCFG_IF_DBGERR                             (0x1UL << 2)                        /**< Debug bus error                             */
#define _RVCFG_IF_DBGERR_SHIFT                      2                                   /**< Shift value for RVCFG_DBGERR                */
#define _RVCFG_IF_DBGERR_MASK                       0x4UL                               /**< Bit mask for RVCFG_DBGERR                   */
#define _RVCFG_IF_DBGERR_DEFAULT                    0x00000000UL                        /**< Mode DEFAULT for RVCFG_IF                   */
#define RVCFG_IF_DBGERR_DEFAULT                     (_RVCFG_IF_DBGERR_DEFAULT << 2)     /**< Shifted mode DEFAULT for RVCFG_IF           */

/* Bit fields for RVCFG IEN */
#define _RVCFG_IEN_RESETVALUE                       0x00000000UL                        /**< Default value for RVCFG_IEN                 */
#define _RVCFG_IEN_MASK                             0x00000007UL                        /**< Mask for RVCFG_IEN                          */
#define RVCFG_IEN_INSTR0ERR                         (0x1UL << 0)                        /**< INSTR0ERR interrupt enable                  */
#define _RVCFG_IEN_INSTR0ERR_SHIFT                  0                                   /**< Shift value for RVCFG_INSTR0ERR             */
#define _RVCFG_IEN_INSTR0ERR_MASK                   0x1UL                               /**< Bit mask for RVCFG_INSTR0ERR                */
#define _RVCFG_IEN_INSTR0ERR_DEFAULT                0x00000000UL                        /**< Mode DEFAULT for RVCFG_IEN                  */
#define RVCFG_IEN_INSTR0ERR_DEFAULT                 (_RVCFG_IEN_INSTR0ERR_DEFAULT << 0) /**< Shifted mode DEFAULT for RVCFG_IEN          */
#define RVCFG_IEN_DATA0ERR                          (0x1UL << 1)                        /**< DATA0ERR interrupt enable                   */
#define _RVCFG_IEN_DATA0ERR_SHIFT                   1                                   /**< Shift value for RVCFG_DATA0ERR              */
#define _RVCFG_IEN_DATA0ERR_MASK                    0x2UL                               /**< Bit mask for RVCFG_DATA0ERR                 */
#define _RVCFG_IEN_DATA0ERR_DEFAULT                 0x00000000UL                        /**< Mode DEFAULT for RVCFG_IEN                  */
#define RVCFG_IEN_DATA0ERR_DEFAULT                  (_RVCFG_IEN_DATA0ERR_DEFAULT << 1)  /**< Shifted mode DEFAULT for RVCFG_IEN          */
#define RVCFG_IEN_DBGERR                            (0x1UL << 2)                        /**< DBGERR interrupt enable                     */
#define _RVCFG_IEN_DBGERR_SHIFT                     2                                   /**< Shift value for RVCFG_DBGERR                */
#define _RVCFG_IEN_DBGERR_MASK                      0x4UL                               /**< Bit mask for RVCFG_DBGERR                   */
#define _RVCFG_IEN_DBGERR_DEFAULT                   0x00000000UL                        /**< Mode DEFAULT for RVCFG_IEN                  */
#define RVCFG_IEN_DBGERR_DEFAULT                    (_RVCFG_IEN_DBGERR_DEFAULT << 2)    /**< Shifted mode DEFAULT for RVCFG_IEN          */

/* Bit fields for RVCFG ISO */
#define _RVCFG_ISO_RESETVALUE                       0x00000000UL                        /**< Default value for RVCFG_ISO                 */
#define _RVCFG_ISO_MASK                             0x0000000FUL                        /**< Mask for RVCFG_ISO                          */
#define _RVCFG_ISO_AMODE_SHIFT                      0                                   /**< Shift value for RVCFG_AMODE                 */
#define _RVCFG_ISO_AMODE_MASK                       0x3UL                               /**< Bit mask for RVCFG_AMODE                    */
#define _RVCFG_ISO_AMODE_DEFAULT                    0x00000000UL                        /**< Mode DEFAULT for RVCFG_ISO                  */
#define RVCFG_ISO_AMODE_DEFAULT                     (_RVCFG_ISO_AMODE_DEFAULT << 0)     /**< Shifted mode DEFAULT for RVCFG_ISO          */
#define _RVCFG_ISO_RMODE_SHIFT                      2                                   /**< Shift value for RVCFG_RMODE                 */
#define _RVCFG_ISO_RMODE_MASK                       0xCUL                               /**< Bit mask for RVCFG_RMODE                    */
#define _RVCFG_ISO_RMODE_DEFAULT                    0x00000000UL                        /**< Mode DEFAULT for RVCFG_ISO                  */
#define RVCFG_ISO_RMODE_DEFAULT                     (_RVCFG_ISO_RMODE_DEFAULT << 2)     /**< Shifted mode DEFAULT for RVCFG_ISO          */

/* Bit fields for RVCFG ISOSTATUS */
#define _RVCFG_ISOSTATUS_RESETVALUE                 0x00000000UL                          /**< Default value for RVCFG_ISOSTATUS           */
#define _RVCFG_ISOSTATUS_MASK                       0x0000000FUL                          /**< Mask for RVCFG_ISOSTATUS                    */
#define _RVCFG_ISOSTATUS_AMODE_SHIFT                0                                     /**< Shift value for RVCFG_AMODE                 */
#define _RVCFG_ISOSTATUS_AMODE_MASK                 0x3UL                                 /**< Bit mask for RVCFG_AMODE                    */
#define _RVCFG_ISOSTATUS_AMODE_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for RVCFG_ISOSTATUS            */
#define RVCFG_ISOSTATUS_AMODE_DEFAULT               (_RVCFG_ISOSTATUS_AMODE_DEFAULT << 0) /**< Shifted mode DEFAULT for RVCFG_ISOSTATUS    */
#define _RVCFG_ISOSTATUS_RMODE_SHIFT                2                                     /**< Shift value for RVCFG_RMODE                 */
#define _RVCFG_ISOSTATUS_RMODE_MASK                 0xCUL                                 /**< Bit mask for RVCFG_RMODE                    */
#define _RVCFG_ISOSTATUS_RMODE_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for RVCFG_ISOSTATUS            */
#define RVCFG_ISOSTATUS_RMODE_DEFAULT               (_RVCFG_ISOSTATUS_RMODE_DEFAULT << 2) /**< Shifted mode DEFAULT for RVCFG_ISOSTATUS    */

/* Bit fields for RVCFG STATUS */
#define _RVCFG_STATUS_RESETVALUE                    0x00000000UL                          /**< Default value for RVCFG_STATUS              */
#define _RVCFG_STATUS_MASK                          0x00000001UL                          /**< Mask for RVCFG_STATUS                       */
#define RVCFG_STATUS_DEBUGREQ                       (0x1UL << 0)                          /**< RISC-V debug request status.                */
#define _RVCFG_STATUS_DEBUGREQ_SHIFT                0                                     /**< Shift value for RVCFG_DEBUGREQ              */
#define _RVCFG_STATUS_DEBUGREQ_MASK                 0x1UL                                 /**< Bit mask for RVCFG_DEBUGREQ                 */
#define _RVCFG_STATUS_DEBUGREQ_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for RVCFG_STATUS               */
#define RVCFG_STATUS_DEBUGREQ_DEFAULT               (_RVCFG_STATUS_DEBUGREQ_DEFAULT << 0) /**< Shifted mode DEFAULT for RVCFG_STATUS       */

/** @} End of group EFR32FG25_RVCFG_BitFields */
/** @} End of group EFR32FG25_RVCFG */
/** @} End of group Parts */

#endif /* EFR32FG25_RVCFG_H */
