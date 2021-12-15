/**************************************************************************//**
 * @file
 * @brief EFR32FG25 UTIMER register and bit field definitions
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
#ifndef EFR32FG25_UTIMER_H
#define EFR32FG25_UTIMER_H
#define UTIMER_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_UTIMER UTIMER
 * @{
 * @brief EFR32FG25 UTIMER Register Declaration.
 *****************************************************************************/

/** UTIMER COMP_CH Register Group Declaration. */
typedef struct {
  __IOM uint32_t VAL;                                /**< Compare Value                                      */
  uint32_t       RESERVED0[1U];                      /**< Reserved for future use                            */
} UTIMER_COMP_CH_TypeDef;

/** UTIMER Register Declaration. */
typedef struct {
  __IM uint32_t          IPVERSION;             /**< IP Version                                         */
  __IOM uint32_t         EN;                    /**< Module Enable                                      */
  __IOM uint32_t         SWRST;                 /**< Software Reset                                     */
  __IOM uint32_t         CFG;                   /**< Configuration                                      */
  __IOM uint32_t         CMD;                   /**< Command                                            */
  __IM uint32_t          STATUS;                /**< Status                                             */
  __IOM uint32_t         IF;                    /**< Interrupt Flags                                    */
  __IOM uint32_t         IEN;                   /**< Interrupt Enable                                   */
  __IOM uint32_t         LOCK;                  /**< UTIMER Configuration Lock                          */
  __IOM uint32_t         CNT;                   /**< Counter Value                                      */
  uint32_t               RESERVED0[1U];         /**< Reserved for future use                            */
  UTIMER_COMP_CH_TypeDef COMP_CH[2U];           /**< Comparator Channels                                */
  uint32_t               RESERVED1[1009U];      /**< Reserved for future use                            */
  __IM uint32_t          IPVERSION_SET;         /**< IP Version                                         */
  __IOM uint32_t         EN_SET;                /**< Module Enable                                      */
  __IOM uint32_t         SWRST_SET;             /**< Software Reset                                     */
  __IOM uint32_t         CFG_SET;               /**< Configuration                                      */
  __IOM uint32_t         CMD_SET;               /**< Command                                            */
  __IM uint32_t          STATUS_SET;            /**< Status                                             */
  __IOM uint32_t         IF_SET;                /**< Interrupt Flags                                    */
  __IOM uint32_t         IEN_SET;               /**< Interrupt Enable                                   */
  __IOM uint32_t         LOCK_SET;              /**< UTIMER Configuration Lock                          */
  __IOM uint32_t         CNT_SET;               /**< Counter Value                                      */
  uint32_t               RESERVED2[1U];         /**< Reserved for future use                            */
  UTIMER_COMP_CH_TypeDef COMP_CH_SET[2U];       /**< Comparator Channels                                */
  uint32_t               RESERVED3[1009U];      /**< Reserved for future use                            */
  __IM uint32_t          IPVERSION_CLR;         /**< IP Version                                         */
  __IOM uint32_t         EN_CLR;                /**< Module Enable                                      */
  __IOM uint32_t         SWRST_CLR;             /**< Software Reset                                     */
  __IOM uint32_t         CFG_CLR;               /**< Configuration                                      */
  __IOM uint32_t         CMD_CLR;               /**< Command                                            */
  __IM uint32_t          STATUS_CLR;            /**< Status                                             */
  __IOM uint32_t         IF_CLR;                /**< Interrupt Flags                                    */
  __IOM uint32_t         IEN_CLR;               /**< Interrupt Enable                                   */
  __IOM uint32_t         LOCK_CLR;              /**< UTIMER Configuration Lock                          */
  __IOM uint32_t         CNT_CLR;               /**< Counter Value                                      */
  uint32_t               RESERVED4[1U];         /**< Reserved for future use                            */
  UTIMER_COMP_CH_TypeDef COMP_CH_CLR[2U];       /**< Comparator Channels                                */
  uint32_t               RESERVED5[1009U];      /**< Reserved for future use                            */
  __IM uint32_t          IPVERSION_TGL;         /**< IP Version                                         */
  __IOM uint32_t         EN_TGL;                /**< Module Enable                                      */
  __IOM uint32_t         SWRST_TGL;             /**< Software Reset                                     */
  __IOM uint32_t         CFG_TGL;               /**< Configuration                                      */
  __IOM uint32_t         CMD_TGL;               /**< Command                                            */
  __IM uint32_t          STATUS_TGL;            /**< Status                                             */
  __IOM uint32_t         IF_TGL;                /**< Interrupt Flags                                    */
  __IOM uint32_t         IEN_TGL;               /**< Interrupt Enable                                   */
  __IOM uint32_t         LOCK_TGL;              /**< UTIMER Configuration Lock                          */
  __IOM uint32_t         CNT_TGL;               /**< Counter Value                                      */
  uint32_t               RESERVED6[1U];         /**< Reserved for future use                            */
  UTIMER_COMP_CH_TypeDef COMP_CH_TGL[2U];       /**< Comparator Channels                                */
} UTIMER_TypeDef;
/** @} End of group EFR32FG25_UTIMER */

/**************************************************************************//**
 * @addtogroup EFR32FG25_UTIMER
 * @{
 * @defgroup EFR32FG25_UTIMER_BitFields UTIMER Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for UTIMER IPVERSION */
#define _UTIMER_IPVERSION_RESETVALUE               0x00000001UL                               /**< Default value for UTIMER_IPVERSION          */
#define _UTIMER_IPVERSION_MASK                     0xFFFFFFFFUL                               /**< Mask for UTIMER_IPVERSION                   */
#define _UTIMER_IPVERSION_IPVERSION_SHIFT          0                                          /**< Shift value for UTIMER_IPVERSION            */
#define _UTIMER_IPVERSION_IPVERSION_MASK           0xFFFFFFFFUL                               /**< Bit mask for UTIMER_IPVERSION               */
#define _UTIMER_IPVERSION_IPVERSION_DEFAULT        0x00000001UL                               /**< Mode DEFAULT for UTIMER_IPVERSION           */
#define UTIMER_IPVERSION_IPVERSION_DEFAULT         (_UTIMER_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for UTIMER_IPVERSION   */

/* Bit fields for UTIMER EN */
#define _UTIMER_EN_RESETVALUE                      0x00000000UL                         /**< Default value for UTIMER_EN                 */
#define _UTIMER_EN_MASK                            0x00000003UL                         /**< Mask for UTIMER_EN                          */
#define UTIMER_EN_EN                               (0x1UL << 0)                         /**< Module enable                               */
#define _UTIMER_EN_EN_SHIFT                        0                                    /**< Shift value for UTIMER_EN                   */
#define _UTIMER_EN_EN_MASK                         0x1UL                                /**< Bit mask for UTIMER_EN                      */
#define _UTIMER_EN_EN_DEFAULT                      0x00000000UL                         /**< Mode DEFAULT for UTIMER_EN                  */
#define UTIMER_EN_EN_DEFAULT                       (_UTIMER_EN_EN_DEFAULT << 0)         /**< Shifted mode DEFAULT for UTIMER_EN          */
#define UTIMER_EN_DISABLING                        (0x1UL << 1)                         /**< Disablement Busy Status                     */
#define _UTIMER_EN_DISABLING_SHIFT                 1                                    /**< Shift value for UTIMER_DISABLING            */
#define _UTIMER_EN_DISABLING_MASK                  0x2UL                                /**< Bit mask for UTIMER_DISABLING               */
#define _UTIMER_EN_DISABLING_DEFAULT               0x00000000UL                         /**< Mode DEFAULT for UTIMER_EN                  */
#define UTIMER_EN_DISABLING_DEFAULT                (_UTIMER_EN_DISABLING_DEFAULT << 1)  /**< Shifted mode DEFAULT for UTIMER_EN          */

/* Bit fields for UTIMER SWRST */
#define _UTIMER_SWRST_RESETVALUE                   0x00000000UL                           /**< Default value for UTIMER_SWRST              */
#define _UTIMER_SWRST_MASK                         0x00000003UL                           /**< Mask for UTIMER_SWRST                       */
#define UTIMER_SWRST_SWRST                         (0x1UL << 0)                           /**< Software Reset Command                      */
#define _UTIMER_SWRST_SWRST_SHIFT                  0                                      /**< Shift value for UTIMER_SWRST                */
#define _UTIMER_SWRST_SWRST_MASK                   0x1UL                                  /**< Bit mask for UTIMER_SWRST                   */
#define _UTIMER_SWRST_SWRST_DEFAULT                0x00000000UL                           /**< Mode DEFAULT for UTIMER_SWRST               */
#define UTIMER_SWRST_SWRST_DEFAULT                 (_UTIMER_SWRST_SWRST_DEFAULT << 0)     /**< Shifted mode DEFAULT for UTIMER_SWRST       */
#define UTIMER_SWRST_RESETTING                     (0x1UL << 1)                           /**< Software Reset Busy Status                  */
#define _UTIMER_SWRST_RESETTING_SHIFT              1                                      /**< Shift value for UTIMER_RESETTING            */
#define _UTIMER_SWRST_RESETTING_MASK               0x2UL                                  /**< Bit mask for UTIMER_RESETTING               */
#define _UTIMER_SWRST_RESETTING_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for UTIMER_SWRST               */
#define UTIMER_SWRST_RESETTING_DEFAULT             (_UTIMER_SWRST_RESETTING_DEFAULT << 1) /**< Shifted mode DEFAULT for UTIMER_SWRST       */

/* Bit fields for UTIMER CFG */
#define _UTIMER_CFG_RESETVALUE                     0x00000000UL                         /**< Default value for UTIMER_CFG                */
#define _UTIMER_CFG_MASK                           0x80000140UL                         /**< Mask for UTIMER_CFG                         */
#define UTIMER_CFG_DEBUGRUN                        (0x1UL << 6)                         /**< Debug Mode Run Enable                       */
#define _UTIMER_CFG_DEBUGRUN_SHIFT                 6                                    /**< Shift value for UTIMER_DEBUGRUN             */
#define _UTIMER_CFG_DEBUGRUN_MASK                  0x40UL                               /**< Bit mask for UTIMER_DEBUGRUN                */
#define _UTIMER_CFG_DEBUGRUN_DEFAULT               0x00000000UL                         /**< Mode DEFAULT for UTIMER_CFG                 */
#define _UTIMER_CFG_DEBUGRUN_DISABLE               0x00000000UL                         /**< Mode DISABLE for UTIMER_CFG                 */
#define _UTIMER_CFG_DEBUGRUN_ENABLE                0x00000001UL                         /**< Mode ENABLE for UTIMER_CFG                  */
#define UTIMER_CFG_DEBUGRUN_DEFAULT                (_UTIMER_CFG_DEBUGRUN_DEFAULT << 6)  /**< Shifted mode DEFAULT for UTIMER_CFG         */
#define UTIMER_CFG_DEBUGRUN_DISABLE                (_UTIMER_CFG_DEBUGRUN_DISABLE << 6)  /**< Shifted mode DISABLE for UTIMER_CFG         */
#define UTIMER_CFG_DEBUGRUN_ENABLE                 (_UTIMER_CFG_DEBUGRUN_ENABLE << 6)   /**< Shifted mode ENABLE for UTIMER_CFG          */
#define UTIMER_CFG_CLKSEL                          (0x1UL << 8)                         /**< Clock Source Select                         */
#define _UTIMER_CFG_CLKSEL_SHIFT                   8                                    /**< Shift value for UTIMER_CLKSEL               */
#define _UTIMER_CFG_CLKSEL_MASK                    0x100UL                              /**< Bit mask for UTIMER_CLKSEL                  */
#define _UTIMER_CFG_CLKSEL_DEFAULT                 0x00000000UL                         /**< Mode DEFAULT for UTIMER_CFG                 */
#define _UTIMER_CFG_CLKSEL_HFPERCLK                0x00000000UL                         /**< Mode HFPERCLK for UTIMER_CFG                */
#define _UTIMER_CFG_CLKSEL_PRS                     0x00000001UL                         /**< Mode PRS for UTIMER_CFG                     */
#define UTIMER_CFG_CLKSEL_DEFAULT                  (_UTIMER_CFG_CLKSEL_DEFAULT << 8)    /**< Shifted mode DEFAULT for UTIMER_CFG         */
#define UTIMER_CFG_CLKSEL_HFPERCLK                 (_UTIMER_CFG_CLKSEL_HFPERCLK << 8)   /**< Shifted mode HFPERCLK for UTIMER_CFG        */
#define UTIMER_CFG_CLKSEL_PRS                      (_UTIMER_CFG_CLKSEL_PRS << 8)        /**< Shifted mode PRS for UTIMER_CFG             */
#define UTIMER_CFG_COMP0TOP                        (0x1UL << 31)                        /**< Top Value Select                            */
#define _UTIMER_CFG_COMP0TOP_SHIFT                 31                                   /**< Shift value for UTIMER_COMP0TOP             */
#define _UTIMER_CFG_COMP0TOP_MASK                  0x80000000UL                         /**< Bit mask for UTIMER_COMP0TOP                */
#define _UTIMER_CFG_COMP0TOP_DEFAULT               0x00000000UL                         /**< Mode DEFAULT for UTIMER_CFG                 */
#define _UTIMER_CFG_COMP0TOP_DISABLE               0x00000000UL                         /**< Mode DISABLE for UTIMER_CFG                 */
#define _UTIMER_CFG_COMP0TOP_ENABLE                0x00000001UL                         /**< Mode ENABLE for UTIMER_CFG                  */
#define UTIMER_CFG_COMP0TOP_DEFAULT                (_UTIMER_CFG_COMP0TOP_DEFAULT << 31) /**< Shifted mode DEFAULT for UTIMER_CFG         */
#define UTIMER_CFG_COMP0TOP_DISABLE                (_UTIMER_CFG_COMP0TOP_DISABLE << 31) /**< Shifted mode DISABLE for UTIMER_CFG         */
#define UTIMER_CFG_COMP0TOP_ENABLE                 (_UTIMER_CFG_COMP0TOP_ENABLE << 31)  /**< Shifted mode ENABLE for UTIMER_CFG          */

/* Bit fields for UTIMER CMD */
#define _UTIMER_CMD_RESETVALUE                     0x00000000UL                         /**< Default value for UTIMER_CMD                */
#define _UTIMER_CMD_MASK                           0x00000003UL                         /**< Mask for UTIMER_CMD                         */
#define UTIMER_CMD_START                           (0x1UL << 0)                         /**< Start Timer                                 */
#define _UTIMER_CMD_START_SHIFT                    0                                    /**< Shift value for UTIMER_START                */
#define _UTIMER_CMD_START_MASK                     0x1UL                                /**< Bit mask for UTIMER_START                   */
#define _UTIMER_CMD_START_DEFAULT                  0x00000000UL                         /**< Mode DEFAULT for UTIMER_CMD                 */
#define UTIMER_CMD_START_DEFAULT                   (_UTIMER_CMD_START_DEFAULT << 0)     /**< Shifted mode DEFAULT for UTIMER_CMD         */
#define UTIMER_CMD_STOP                            (0x1UL << 1)                         /**< Stop Timer                                  */
#define _UTIMER_CMD_STOP_SHIFT                     1                                    /**< Shift value for UTIMER_STOP                 */
#define _UTIMER_CMD_STOP_MASK                      0x2UL                                /**< Bit mask for UTIMER_STOP                    */
#define _UTIMER_CMD_STOP_DEFAULT                   0x00000000UL                         /**< Mode DEFAULT for UTIMER_CMD                 */
#define UTIMER_CMD_STOP_DEFAULT                    (_UTIMER_CMD_STOP_DEFAULT << 1)      /**< Shifted mode DEFAULT for UTIMER_CMD         */

/* Bit fields for UTIMER STATUS */
#define _UTIMER_STATUS_RESETVALUE                  0x00000000UL                                   /**< Default value for UTIMER_STATUS             */
#define _UTIMER_STATUS_MASK                        0x00000051UL                                   /**< Mask for UTIMER_STATUS                      */
#define UTIMER_STATUS_RUNNING                      (0x1UL << 0)                                   /**< Running                                     */
#define _UTIMER_STATUS_RUNNING_SHIFT               0                                              /**< Shift value for UTIMER_RUNNING              */
#define _UTIMER_STATUS_RUNNING_MASK                0x1UL                                          /**< Bit mask for UTIMER_RUNNING                 */
#define _UTIMER_STATUS_RUNNING_DEFAULT             0x00000000UL                                   /**< Mode DEFAULT for UTIMER_STATUS              */
#define UTIMER_STATUS_RUNNING_DEFAULT              (_UTIMER_STATUS_RUNNING_DEFAULT << 0)          /**< Shifted mode DEFAULT for UTIMER_STATUS      */
#define UTIMER_STATUS_TIMERLOCKSTATUS              (0x1UL << 4)                                   /**< Timer lock status                           */
#define _UTIMER_STATUS_TIMERLOCKSTATUS_SHIFT       4                                              /**< Shift value for UTIMER_TIMERLOCKSTATUS      */
#define _UTIMER_STATUS_TIMERLOCKSTATUS_MASK        0x10UL                                         /**< Bit mask for UTIMER_TIMERLOCKSTATUS         */
#define _UTIMER_STATUS_TIMERLOCKSTATUS_DEFAULT     0x00000000UL                                   /**< Mode DEFAULT for UTIMER_STATUS              */
#define _UTIMER_STATUS_TIMERLOCKSTATUS_UNLOCKED    0x00000000UL                                   /**< Mode UNLOCKED for UTIMER_STATUS             */
#define _UTIMER_STATUS_TIMERLOCKSTATUS_LOCKED      0x00000001UL                                   /**< Mode LOCKED for UTIMER_STATUS               */
#define UTIMER_STATUS_TIMERLOCKSTATUS_DEFAULT      (_UTIMER_STATUS_TIMERLOCKSTATUS_DEFAULT << 4)  /**< Shifted mode DEFAULT for UTIMER_STATUS      */
#define UTIMER_STATUS_TIMERLOCKSTATUS_UNLOCKED     (_UTIMER_STATUS_TIMERLOCKSTATUS_UNLOCKED << 4) /**< Shifted mode UNLOCKED for UTIMER_STATUS     */
#define UTIMER_STATUS_TIMERLOCKSTATUS_LOCKED       (_UTIMER_STATUS_TIMERLOCKSTATUS_LOCKED << 4)   /**< Shifted mode LOCKED for UTIMER_STATUS       */
#define UTIMER_STATUS_SYNCBUSY                     (0x1UL << 6)                                   /**< Sync Busy                                   */
#define _UTIMER_STATUS_SYNCBUSY_SHIFT              6                                              /**< Shift value for UTIMER_SYNCBUSY             */
#define _UTIMER_STATUS_SYNCBUSY_MASK               0x40UL                                         /**< Bit mask for UTIMER_SYNCBUSY                */
#define _UTIMER_STATUS_SYNCBUSY_DEFAULT            0x00000000UL                                   /**< Mode DEFAULT for UTIMER_STATUS              */
#define UTIMER_STATUS_SYNCBUSY_DEFAULT             (_UTIMER_STATUS_SYNCBUSY_DEFAULT << 6)         /**< Shifted mode DEFAULT for UTIMER_STATUS      */

/* Bit fields for UTIMER IF */
#define _UTIMER_IF_RESETVALUE                      0x00000000UL                         /**< Default value for UTIMER_IF                 */
#define _UTIMER_IF_MASK                            0x00000031UL                         /**< Mask for UTIMER_IF                          */
#define UTIMER_IF_OF                               (0x1UL << 0)                         /**< Overflow Interrupt Flag                     */
#define _UTIMER_IF_OF_SHIFT                        0                                    /**< Shift value for UTIMER_OF                   */
#define _UTIMER_IF_OF_MASK                         0x1UL                                /**< Bit mask for UTIMER_OF                      */
#define _UTIMER_IF_OF_DEFAULT                      0x00000000UL                         /**< Mode DEFAULT for UTIMER_IF                  */
#define UTIMER_IF_OF_DEFAULT                       (_UTIMER_IF_OF_DEFAULT << 0)         /**< Shifted mode DEFAULT for UTIMER_IF          */
#define UTIMER_IF_COMP0IF                          (0x1UL << 4)                         /**< Compare Match 0 Interrupt Flag              */
#define _UTIMER_IF_COMP0IF_SHIFT                   4                                    /**< Shift value for UTIMER_COMP0IF              */
#define _UTIMER_IF_COMP0IF_MASK                    0x10UL                               /**< Bit mask for UTIMER_COMP0IF                 */
#define _UTIMER_IF_COMP0IF_DEFAULT                 0x00000000UL                         /**< Mode DEFAULT for UTIMER_IF                  */
#define UTIMER_IF_COMP0IF_DEFAULT                  (_UTIMER_IF_COMP0IF_DEFAULT << 4)    /**< Shifted mode DEFAULT for UTIMER_IF          */
#define UTIMER_IF_COMP1IF                          (0x1UL << 5)                         /**< Compare Match 1 Interrupt Flag              */
#define _UTIMER_IF_COMP1IF_SHIFT                   5                                    /**< Shift value for UTIMER_COMP1IF              */
#define _UTIMER_IF_COMP1IF_MASK                    0x20UL                               /**< Bit mask for UTIMER_COMP1IF                 */
#define _UTIMER_IF_COMP1IF_DEFAULT                 0x00000000UL                         /**< Mode DEFAULT for UTIMER_IF                  */
#define UTIMER_IF_COMP1IF_DEFAULT                  (_UTIMER_IF_COMP1IF_DEFAULT << 5)    /**< Shifted mode DEFAULT for UTIMER_IF          */

/* Bit fields for UTIMER IEN */
#define _UTIMER_IEN_RESETVALUE                     0x00000000UL                         /**< Default value for UTIMER_IEN                */
#define _UTIMER_IEN_MASK                           0x00000031UL                         /**< Mask for UTIMER_IEN                         */
#define UTIMER_IEN_OF                              (0x1UL << 0)                         /**< Overflow Interrupt Enable                   */
#define _UTIMER_IEN_OF_SHIFT                       0                                    /**< Shift value for UTIMER_OF                   */
#define _UTIMER_IEN_OF_MASK                        0x1UL                                /**< Bit mask for UTIMER_OF                      */
#define _UTIMER_IEN_OF_DEFAULT                     0x00000000UL                         /**< Mode DEFAULT for UTIMER_IEN                 */
#define UTIMER_IEN_OF_DEFAULT                      (_UTIMER_IEN_OF_DEFAULT << 0)        /**< Shifted mode DEFAULT for UTIMER_IEN         */
#define UTIMER_IEN_COMP0IEN                        (0x1UL << 4)                         /**< Compare Match 0 Interrupt Enable            */
#define _UTIMER_IEN_COMP0IEN_SHIFT                 4                                    /**< Shift value for UTIMER_COMP0IEN             */
#define _UTIMER_IEN_COMP0IEN_MASK                  0x10UL                               /**< Bit mask for UTIMER_COMP0IEN                */
#define _UTIMER_IEN_COMP0IEN_DEFAULT               0x00000000UL                         /**< Mode DEFAULT for UTIMER_IEN                 */
#define UTIMER_IEN_COMP0IEN_DEFAULT                (_UTIMER_IEN_COMP0IEN_DEFAULT << 4)  /**< Shifted mode DEFAULT for UTIMER_IEN         */
#define UTIMER_IEN_COMP1IEN                        (0x1UL << 5)                         /**< Compare Match 1 Interrupt Enable            */
#define _UTIMER_IEN_COMP1IEN_SHIFT                 5                                    /**< Shift value for UTIMER_COMP1IEN             */
#define _UTIMER_IEN_COMP1IEN_MASK                  0x20UL                               /**< Bit mask for UTIMER_COMP1IEN                */
#define _UTIMER_IEN_COMP1IEN_DEFAULT               0x00000000UL                         /**< Mode DEFAULT for UTIMER_IEN                 */
#define UTIMER_IEN_COMP1IEN_DEFAULT                (_UTIMER_IEN_COMP1IEN_DEFAULT << 5)  /**< Shifted mode DEFAULT for UTIMER_IEN         */

/* Bit fields for UTIMER LOCK */
#define _UTIMER_LOCK_RESETVALUE                    0x00000000UL                             /**< Default value for UTIMER_LOCK               */
#define _UTIMER_LOCK_MASK                          0x0000FFFFUL                             /**< Mask for UTIMER_LOCK                        */
#define _UTIMER_LOCK_TIMERLOCKKEY_SHIFT            0                                        /**< Shift value for UTIMER_TIMERLOCKKEY         */
#define _UTIMER_LOCK_TIMERLOCKKEY_MASK             0xFFFFUL                                 /**< Bit mask for UTIMER_TIMERLOCKKEY            */
#define _UTIMER_LOCK_TIMERLOCKKEY_DEFAULT          0x00000000UL                             /**< Mode DEFAULT for UTIMER_LOCK                */
#define _UTIMER_LOCK_TIMERLOCKKEY_UNLOCK           0x0000BF91UL                             /**< Mode UNLOCK for UTIMER_LOCK                 */
#define UTIMER_LOCK_TIMERLOCKKEY_DEFAULT           (_UTIMER_LOCK_TIMERLOCKKEY_DEFAULT << 0) /**< Shifted mode DEFAULT for UTIMER_LOCK        */
#define UTIMER_LOCK_TIMERLOCKKEY_UNLOCK            (_UTIMER_LOCK_TIMERLOCKKEY_UNLOCK << 0)  /**< Shifted mode UNLOCK for UTIMER_LOCK         */

/* Bit fields for UTIMER CNT */
#define _UTIMER_CNT_RESETVALUE                     0x00000000UL                         /**< Default value for UTIMER_CNT                */
#define _UTIMER_CNT_MASK                           0xFFFFFFFFUL                         /**< Mask for UTIMER_CNT                         */
#define _UTIMER_CNT_CNT_SHIFT                      0                                    /**< Shift value for UTIMER_CNT                  */
#define _UTIMER_CNT_CNT_MASK                       0xFFFFFFFFUL                         /**< Bit mask for UTIMER_CNT                     */
#define _UTIMER_CNT_CNT_DEFAULT                    0x00000000UL                         /**< Mode DEFAULT for UTIMER_CNT                 */
#define UTIMER_CNT_CNT_DEFAULT                     (_UTIMER_CNT_CNT_DEFAULT << 0)       /**< Shifted mode DEFAULT for UTIMER_CNT         */

/* Bit fields for UTIMER COMPVAL */
#define _UTIMER_COMPVAL_RESETVALUE                 0x00000000UL                         /**< Default value for UTIMER_COMPVAL            */
#define _UTIMER_COMPVAL_MASK                       0xFFFFFFFFUL                         /**< Mask for UTIMER_COMPVAL                     */
#define _UTIMER_COMPVAL_COMP_SHIFT                 0                                    /**< Shift value for UTIMER_COMP                 */
#define _UTIMER_COMPVAL_COMP_MASK                  0xFFFFFFFFUL                         /**< Bit mask for UTIMER_COMP                    */
#define _UTIMER_COMPVAL_COMP_DEFAULT               0x00000000UL                         /**< Mode DEFAULT for UTIMER_COMPVAL             */
#define UTIMER_COMPVAL_COMP_DEFAULT                (_UTIMER_COMPVAL_COMP_DEFAULT << 0)  /**< Shifted mode DEFAULT for UTIMER_COMPVAL     */

/** @} End of group EFR32FG25_UTIMER_BitFields */
/** @} End of group EFR32FG25_UTIMER */
/** @} End of group Parts */

#endif /* EFR32FG25_UTIMER_H */
