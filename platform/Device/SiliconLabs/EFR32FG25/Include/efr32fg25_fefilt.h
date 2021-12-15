/**************************************************************************//**
 * @file
 * @brief EFR32FG25 FEFILT register and bit field definitions
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
#ifndef EFR32FG25_FEFILT_H
#define EFR32FG25_FEFILT_H
#define FEFILT_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_FEFILT FEFILT
 * @{
 * @brief EFR32FG25 FEFILT Register Declaration.
 *****************************************************************************/

/** FEFILT IRCALCOEFWR Register Group Declaration. */
typedef struct {
  __IOM uint32_t IRCALCOEFWR;                        /**< IRCAL COEF WR per antenna                          */
} FEFILT_IRCALCOEFWR_TypeDef;

/** FEFILT Register Declaration. */
typedef struct {
  __IM uint32_t              IPVERSION;           /**< IP version ID                                      */
  __IOM uint32_t             EN;                  /**< Enable peripheral clock to this module             */
  __IOM uint32_t             SWRST;               /**< Software reset of the module                       */
  __IM uint32_t              STATUS;              /**< Status Register                                    */
  __IOM uint32_t             LOCK;                /**< Configuration Lock Key                             */
  __IOM uint32_t             CFG;                 /**< Configuration register                             */
  __IOM uint32_t             CMD;                 /**< Command register                                   */
  uint32_t                   RESERVED0[57U];      /**< Reserved for future use                            */
  __IOM uint32_t             CF;                  /**< Channel Filter                                     */
  __IOM uint32_t             SRC;                 /**< SRC values                                         */
  __IOM uint32_t             DIGIGAINCTRL;        /**< Digital Gain Control                               */
  __IOM uint32_t             CHFCOE00;            /**< CHF COE. Set0 group0                               */
  __IOM uint32_t             CHFCOE01;            /**< CHF COE. Set0 group1                               */
  __IOM uint32_t             CHFCOE02;            /**< CHF COE. Set0 group2                               */
  __IOM uint32_t             CHFCOE03;            /**< CHF COE. Set0 group3                               */
  __IOM uint32_t             CHFCOE04;            /**< CHF COE. Set0 group4                               */
  __IOM uint32_t             CHFCOE05;            /**< CHF COE. Set0 group5                               */
  __IOM uint32_t             CHFCOE06;            /**< CHF COE. Set0 group6                               */
  __IOM uint32_t             CHFCOE10;            /**< CHF COE. Set1 group0                               */
  __IOM uint32_t             CHFCOE11;            /**< CHF COE. Set1 group1                               */
  __IOM uint32_t             CHFCOE12;            /**< CHF COE. Set1 group2                               */
  __IOM uint32_t             CHFCOE13;            /**< CHF COE. Set1 group3                               */
  __IOM uint32_t             CHFCOE15;            /**< CHF COE. Set1 group5                               */
  __IOM uint32_t             CHFCOE14;            /**< CHF COE. Set1 group4                               */
  __IOM uint32_t             CHFCOE16;            /**< CHF COE. Set1 group6                               */
  __IOM uint32_t             CHFCTRL;             /**< CHF control                                        */
  uint32_t                   RESERVED1[1U];       /**< Reserved for future use                            */
  __IOM uint32_t             CTRL;                /**< FEFILT control register                            */
  __IOM uint32_t             BLANKING;            /**< BLANKING CTRL                                      */
  __IOM uint32_t             RSSIFILT;            /**< OOB Filter for RSSI                                */
  uint32_t                   RESERVED2[10U];      /**< Reserved for future use                            */
  __IOM uint32_t             DIGMIXCTRL;          /**< Digital mixer control register                     */
  uint32_t                   RESERVED3[31U];      /**< Reserved for future use                            */
  __IOM uint32_t             DCCOMP;              /**< DC Offset Compensation Filter Settings             */
  __IOM uint32_t             DCCOMPFILTINIT;      /**< DC Offset compensation Filter                      */
  __IM uint32_t              DCESTI;              /**< DC Offset Estimated value                          */
  uint32_t                   RESERVED4[17U];      /**< Reserved for future use                            */
  __IOM uint32_t             IRCAL;               /**< IRCAL control signals                              */
  __IM uint32_t              IRCALCOEF;           /**< IRCAL COEF values                                  */
  uint32_t                   RESERVED5[42U];      /**< Reserved for future use                            */
  FEFILT_IRCALCOEFWR_TypeDef IRCALCOEFWR[2U];     /**< IRCAL                                              */
  uint32_t                   RESERVED6[830U];     /**< Reserved for future use                            */
  __IM uint32_t              IPVERSION_SET;       /**< IP version ID                                      */
  __IOM uint32_t             EN_SET;              /**< Enable peripheral clock to this module             */
  __IOM uint32_t             SWRST_SET;           /**< Software reset of the module                       */
  __IM uint32_t              STATUS_SET;          /**< Status Register                                    */
  __IOM uint32_t             LOCK_SET;            /**< Configuration Lock Key                             */
  __IOM uint32_t             CFG_SET;             /**< Configuration register                             */
  __IOM uint32_t             CMD_SET;             /**< Command register                                   */
  uint32_t                   RESERVED7[57U];      /**< Reserved for future use                            */
  __IOM uint32_t             CF_SET;              /**< Channel Filter                                     */
  __IOM uint32_t             SRC_SET;             /**< SRC values                                         */
  __IOM uint32_t             DIGIGAINCTRL_SET;    /**< Digital Gain Control                               */
  __IOM uint32_t             CHFCOE00_SET;        /**< CHF COE. Set0 group0                               */
  __IOM uint32_t             CHFCOE01_SET;        /**< CHF COE. Set0 group1                               */
  __IOM uint32_t             CHFCOE02_SET;        /**< CHF COE. Set0 group2                               */
  __IOM uint32_t             CHFCOE03_SET;        /**< CHF COE. Set0 group3                               */
  __IOM uint32_t             CHFCOE04_SET;        /**< CHF COE. Set0 group4                               */
  __IOM uint32_t             CHFCOE05_SET;        /**< CHF COE. Set0 group5                               */
  __IOM uint32_t             CHFCOE06_SET;        /**< CHF COE. Set0 group6                               */
  __IOM uint32_t             CHFCOE10_SET;        /**< CHF COE. Set1 group0                               */
  __IOM uint32_t             CHFCOE11_SET;        /**< CHF COE. Set1 group1                               */
  __IOM uint32_t             CHFCOE12_SET;        /**< CHF COE. Set1 group2                               */
  __IOM uint32_t             CHFCOE13_SET;        /**< CHF COE. Set1 group3                               */
  __IOM uint32_t             CHFCOE15_SET;        /**< CHF COE. Set1 group5                               */
  __IOM uint32_t             CHFCOE14_SET;        /**< CHF COE. Set1 group4                               */
  __IOM uint32_t             CHFCOE16_SET;        /**< CHF COE. Set1 group6                               */
  __IOM uint32_t             CHFCTRL_SET;         /**< CHF control                                        */
  uint32_t                   RESERVED8[1U];       /**< Reserved for future use                            */
  __IOM uint32_t             CTRL_SET;            /**< FEFILT control register                            */
  __IOM uint32_t             BLANKING_SET;        /**< BLANKING CTRL                                      */
  __IOM uint32_t             RSSIFILT_SET;        /**< OOB Filter for RSSI                                */
  uint32_t                   RESERVED9[10U];      /**< Reserved for future use                            */
  __IOM uint32_t             DIGMIXCTRL_SET;      /**< Digital mixer control register                     */
  uint32_t                   RESERVED10[31U];     /**< Reserved for future use                            */
  __IOM uint32_t             DCCOMP_SET;          /**< DC Offset Compensation Filter Settings             */
  __IOM uint32_t             DCCOMPFILTINIT_SET;  /**< DC Offset compensation Filter                      */
  __IM uint32_t              DCESTI_SET;          /**< DC Offset Estimated value                          */
  uint32_t                   RESERVED11[17U];     /**< Reserved for future use                            */
  __IOM uint32_t             IRCAL_SET;           /**< IRCAL control signals                              */
  __IM uint32_t              IRCALCOEF_SET;       /**< IRCAL COEF values                                  */
  uint32_t                   RESERVED12[42U];     /**< Reserved for future use                            */
  FEFILT_IRCALCOEFWR_TypeDef IRCALCOEFWR_SET[2U]; /**< IRCAL                                              */
  uint32_t                   RESERVED13[830U];    /**< Reserved for future use                            */
  __IM uint32_t              IPVERSION_CLR;       /**< IP version ID                                      */
  __IOM uint32_t             EN_CLR;              /**< Enable peripheral clock to this module             */
  __IOM uint32_t             SWRST_CLR;           /**< Software reset of the module                       */
  __IM uint32_t              STATUS_CLR;          /**< Status Register                                    */
  __IOM uint32_t             LOCK_CLR;            /**< Configuration Lock Key                             */
  __IOM uint32_t             CFG_CLR;             /**< Configuration register                             */
  __IOM uint32_t             CMD_CLR;             /**< Command register                                   */
  uint32_t                   RESERVED14[57U];     /**< Reserved for future use                            */
  __IOM uint32_t             CF_CLR;              /**< Channel Filter                                     */
  __IOM uint32_t             SRC_CLR;             /**< SRC values                                         */
  __IOM uint32_t             DIGIGAINCTRL_CLR;    /**< Digital Gain Control                               */
  __IOM uint32_t             CHFCOE00_CLR;        /**< CHF COE. Set0 group0                               */
  __IOM uint32_t             CHFCOE01_CLR;        /**< CHF COE. Set0 group1                               */
  __IOM uint32_t             CHFCOE02_CLR;        /**< CHF COE. Set0 group2                               */
  __IOM uint32_t             CHFCOE03_CLR;        /**< CHF COE. Set0 group3                               */
  __IOM uint32_t             CHFCOE04_CLR;        /**< CHF COE. Set0 group4                               */
  __IOM uint32_t             CHFCOE05_CLR;        /**< CHF COE. Set0 group5                               */
  __IOM uint32_t             CHFCOE06_CLR;        /**< CHF COE. Set0 group6                               */
  __IOM uint32_t             CHFCOE10_CLR;        /**< CHF COE. Set1 group0                               */
  __IOM uint32_t             CHFCOE11_CLR;        /**< CHF COE. Set1 group1                               */
  __IOM uint32_t             CHFCOE12_CLR;        /**< CHF COE. Set1 group2                               */
  __IOM uint32_t             CHFCOE13_CLR;        /**< CHF COE. Set1 group3                               */
  __IOM uint32_t             CHFCOE15_CLR;        /**< CHF COE. Set1 group5                               */
  __IOM uint32_t             CHFCOE14_CLR;        /**< CHF COE. Set1 group4                               */
  __IOM uint32_t             CHFCOE16_CLR;        /**< CHF COE. Set1 group6                               */
  __IOM uint32_t             CHFCTRL_CLR;         /**< CHF control                                        */
  uint32_t                   RESERVED15[1U];      /**< Reserved for future use                            */
  __IOM uint32_t             CTRL_CLR;            /**< FEFILT control register                            */
  __IOM uint32_t             BLANKING_CLR;        /**< BLANKING CTRL                                      */
  __IOM uint32_t             RSSIFILT_CLR;        /**< OOB Filter for RSSI                                */
  uint32_t                   RESERVED16[10U];     /**< Reserved for future use                            */
  __IOM uint32_t             DIGMIXCTRL_CLR;      /**< Digital mixer control register                     */
  uint32_t                   RESERVED17[31U];     /**< Reserved for future use                            */
  __IOM uint32_t             DCCOMP_CLR;          /**< DC Offset Compensation Filter Settings             */
  __IOM uint32_t             DCCOMPFILTINIT_CLR;  /**< DC Offset compensation Filter                      */
  __IM uint32_t              DCESTI_CLR;          /**< DC Offset Estimated value                          */
  uint32_t                   RESERVED18[17U];     /**< Reserved for future use                            */
  __IOM uint32_t             IRCAL_CLR;           /**< IRCAL control signals                              */
  __IM uint32_t              IRCALCOEF_CLR;       /**< IRCAL COEF values                                  */
  uint32_t                   RESERVED19[42U];     /**< Reserved for future use                            */
  FEFILT_IRCALCOEFWR_TypeDef IRCALCOEFWR_CLR[2U]; /**< IRCAL                                              */
  uint32_t                   RESERVED20[830U];    /**< Reserved for future use                            */
  __IM uint32_t              IPVERSION_TGL;       /**< IP version ID                                      */
  __IOM uint32_t             EN_TGL;              /**< Enable peripheral clock to this module             */
  __IOM uint32_t             SWRST_TGL;           /**< Software reset of the module                       */
  __IM uint32_t              STATUS_TGL;          /**< Status Register                                    */
  __IOM uint32_t             LOCK_TGL;            /**< Configuration Lock Key                             */
  __IOM uint32_t             CFG_TGL;             /**< Configuration register                             */
  __IOM uint32_t             CMD_TGL;             /**< Command register                                   */
  uint32_t                   RESERVED21[57U];     /**< Reserved for future use                            */
  __IOM uint32_t             CF_TGL;              /**< Channel Filter                                     */
  __IOM uint32_t             SRC_TGL;             /**< SRC values                                         */
  __IOM uint32_t             DIGIGAINCTRL_TGL;    /**< Digital Gain Control                               */
  __IOM uint32_t             CHFCOE00_TGL;        /**< CHF COE. Set0 group0                               */
  __IOM uint32_t             CHFCOE01_TGL;        /**< CHF COE. Set0 group1                               */
  __IOM uint32_t             CHFCOE02_TGL;        /**< CHF COE. Set0 group2                               */
  __IOM uint32_t             CHFCOE03_TGL;        /**< CHF COE. Set0 group3                               */
  __IOM uint32_t             CHFCOE04_TGL;        /**< CHF COE. Set0 group4                               */
  __IOM uint32_t             CHFCOE05_TGL;        /**< CHF COE. Set0 group5                               */
  __IOM uint32_t             CHFCOE06_TGL;        /**< CHF COE. Set0 group6                               */
  __IOM uint32_t             CHFCOE10_TGL;        /**< CHF COE. Set1 group0                               */
  __IOM uint32_t             CHFCOE11_TGL;        /**< CHF COE. Set1 group1                               */
  __IOM uint32_t             CHFCOE12_TGL;        /**< CHF COE. Set1 group2                               */
  __IOM uint32_t             CHFCOE13_TGL;        /**< CHF COE. Set1 group3                               */
  __IOM uint32_t             CHFCOE15_TGL;        /**< CHF COE. Set1 group5                               */
  __IOM uint32_t             CHFCOE14_TGL;        /**< CHF COE. Set1 group4                               */
  __IOM uint32_t             CHFCOE16_TGL;        /**< CHF COE. Set1 group6                               */
  __IOM uint32_t             CHFCTRL_TGL;         /**< CHF control                                        */
  uint32_t                   RESERVED22[1U];      /**< Reserved for future use                            */
  __IOM uint32_t             CTRL_TGL;            /**< FEFILT control register                            */
  __IOM uint32_t             BLANKING_TGL;        /**< BLANKING CTRL                                      */
  __IOM uint32_t             RSSIFILT_TGL;        /**< OOB Filter for RSSI                                */
  uint32_t                   RESERVED23[10U];     /**< Reserved for future use                            */
  __IOM uint32_t             DIGMIXCTRL_TGL;      /**< Digital mixer control register                     */
  uint32_t                   RESERVED24[31U];     /**< Reserved for future use                            */
  __IOM uint32_t             DCCOMP_TGL;          /**< DC Offset Compensation Filter Settings             */
  __IOM uint32_t             DCCOMPFILTINIT_TGL;  /**< DC Offset compensation Filter                      */
  __IM uint32_t              DCESTI_TGL;          /**< DC Offset Estimated value                          */
  uint32_t                   RESERVED25[17U];     /**< Reserved for future use                            */
  __IOM uint32_t             IRCAL_TGL;           /**< IRCAL control signals                              */
  __IM uint32_t              IRCALCOEF_TGL;       /**< IRCAL COEF values                                  */
  uint32_t                   RESERVED26[42U];     /**< Reserved for future use                            */
  FEFILT_IRCALCOEFWR_TypeDef IRCALCOEFWR_TGL[2U]; /**< IRCAL                                              */
} FEFILT_TypeDef;
/** @} End of group EFR32FG25_FEFILT */

/**************************************************************************//**
 * @addtogroup EFR32FG25_FEFILT
 * @{
 * @defgroup EFR32FG25_FEFILT_BitFields FEFILT Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for FEFILT IPVERSION */
#define _FEFILT_IPVERSION_RESETVALUE                     0x00000001UL                               /**< Default value for FEFILT_IPVERSION          */
#define _FEFILT_IPVERSION_MASK                           0xFFFFFFFFUL                               /**< Mask for FEFILT_IPVERSION                   */
#define _FEFILT_IPVERSION_IPVERSION_SHIFT                0                                          /**< Shift value for FEFILT_IPVERSION            */
#define _FEFILT_IPVERSION_IPVERSION_MASK                 0xFFFFFFFFUL                               /**< Bit mask for FEFILT_IPVERSION               */
#define _FEFILT_IPVERSION_IPVERSION_DEFAULT              0x00000001UL                               /**< Mode DEFAULT for FEFILT_IPVERSION           */
#define FEFILT_IPVERSION_IPVERSION_DEFAULT               (_FEFILT_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for FEFILT_IPVERSION   */

/* Bit fields for FEFILT EN */
#define _FEFILT_EN_RESETVALUE                            0x00000000UL                        /**< Default value for FEFILT_EN                 */
#define _FEFILT_EN_MASK                                  0x00000003UL                        /**< Mask for FEFILT_EN                          */
#define FEFILT_EN_EN                                     (0x1UL << 0)                        /**< Module enable                               */
#define _FEFILT_EN_EN_SHIFT                              0                                   /**< Shift value for FEFILT_EN                   */
#define _FEFILT_EN_EN_MASK                               0x1UL                               /**< Bit mask for FEFILT_EN                      */
#define _FEFILT_EN_EN_DEFAULT                            0x00000000UL                        /**< Mode DEFAULT for FEFILT_EN                  */
#define FEFILT_EN_EN_DEFAULT                             (_FEFILT_EN_EN_DEFAULT << 0)        /**< Shifted mode DEFAULT for FEFILT_EN          */
#define FEFILT_EN_DISABLING                              (0x1UL << 1)                        /**< Disablement busy status                     */
#define _FEFILT_EN_DISABLING_SHIFT                       1                                   /**< Shift value for FEFILT_DISABLING            */
#define _FEFILT_EN_DISABLING_MASK                        0x2UL                               /**< Bit mask for FEFILT_DISABLING               */
#define _FEFILT_EN_DISABLING_DEFAULT                     0x00000000UL                        /**< Mode DEFAULT for FEFILT_EN                  */
#define FEFILT_EN_DISABLING_DEFAULT                      (_FEFILT_EN_DISABLING_DEFAULT << 1) /**< Shifted mode DEFAULT for FEFILT_EN          */

/* Bit fields for FEFILT SWRST */
#define _FEFILT_SWRST_RESETVALUE                         0x00000000UL                           /**< Default value for FEFILT_SWRST              */
#define _FEFILT_SWRST_MASK                               0x00000003UL                           /**< Mask for FEFILT_SWRST                       */
#define FEFILT_SWRST_SWRST                               (0x1UL << 0)                           /**< Software reset command                      */
#define _FEFILT_SWRST_SWRST_SHIFT                        0                                      /**< Shift value for FEFILT_SWRST                */
#define _FEFILT_SWRST_SWRST_MASK                         0x1UL                                  /**< Bit mask for FEFILT_SWRST                   */
#define _FEFILT_SWRST_SWRST_DEFAULT                      0x00000000UL                           /**< Mode DEFAULT for FEFILT_SWRST               */
#define FEFILT_SWRST_SWRST_DEFAULT                       (_FEFILT_SWRST_SWRST_DEFAULT << 0)     /**< Shifted mode DEFAULT for FEFILT_SWRST       */
#define FEFILT_SWRST_RESETTING                           (0x1UL << 1)                           /**< Software reset busy status                  */
#define _FEFILT_SWRST_RESETTING_SHIFT                    1                                      /**< Shift value for FEFILT_RESETTING            */
#define _FEFILT_SWRST_RESETTING_MASK                     0x2UL                                  /**< Bit mask for FEFILT_RESETTING               */
#define _FEFILT_SWRST_RESETTING_DEFAULT                  0x00000000UL                           /**< Mode DEFAULT for FEFILT_SWRST               */
#define FEFILT_SWRST_RESETTING_DEFAULT                   (_FEFILT_SWRST_RESETTING_DEFAULT << 1) /**< Shifted mode DEFAULT for FEFILT_SWRST       */

/* Bit fields for FEFILT STATUS */
#define _FEFILT_STATUS_RESETVALUE                        0x00000000UL                                    /**< Default value for FEFILT_STATUS             */
#define _FEFILT_STATUS_MASK                              0x00000001UL                                    /**< Mask for FEFILT_STATUS                      */
#define FEFILT_STATUS_FEFILTLOCKSTATUS                   (0x1UL << 0)                                    /**< Lock Status                                 */
#define _FEFILT_STATUS_FEFILTLOCKSTATUS_SHIFT            0                                               /**< Shift value for FEFILT_FEFILTLOCKSTATUS     */
#define _FEFILT_STATUS_FEFILTLOCKSTATUS_MASK             0x1UL                                           /**< Bit mask for FEFILT_FEFILTLOCKSTATUS        */
#define _FEFILT_STATUS_FEFILTLOCKSTATUS_DEFAULT          0x00000000UL                                    /**< Mode DEFAULT for FEFILT_STATUS              */
#define _FEFILT_STATUS_FEFILTLOCKSTATUS_UNLOCKED         0x00000000UL                                    /**< Mode UNLOCKED for FEFILT_STATUS             */
#define _FEFILT_STATUS_FEFILTLOCKSTATUS_LOCKED           0x00000001UL                                    /**< Mode LOCKED for FEFILT_STATUS               */
#define FEFILT_STATUS_FEFILTLOCKSTATUS_DEFAULT           (_FEFILT_STATUS_FEFILTLOCKSTATUS_DEFAULT << 0)  /**< Shifted mode DEFAULT for FEFILT_STATUS      */
#define FEFILT_STATUS_FEFILTLOCKSTATUS_UNLOCKED          (_FEFILT_STATUS_FEFILTLOCKSTATUS_UNLOCKED << 0) /**< Shifted mode UNLOCKED for FEFILT_STATUS     */
#define FEFILT_STATUS_FEFILTLOCKSTATUS_LOCKED            (_FEFILT_STATUS_FEFILTLOCKSTATUS_LOCKED << 0)   /**< Shifted mode LOCKED for FEFILT_STATUS       */

/* Bit fields for FEFILT LOCK */
#define _FEFILT_LOCK_RESETVALUE                          0x00000000UL                              /**< Default value for FEFILT_LOCK               */
#define _FEFILT_LOCK_MASK                                0x0000FFFFUL                              /**< Mask for FEFILT_LOCK                        */
#define _FEFILT_LOCK_FEFILTLOCKKEY_SHIFT                 0                                         /**< Shift value for FEFILT_FEFILTLOCKKEY        */
#define _FEFILT_LOCK_FEFILTLOCKKEY_MASK                  0xFFFFUL                                  /**< Bit mask for FEFILT_FEFILTLOCKKEY           */
#define _FEFILT_LOCK_FEFILTLOCKKEY_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for FEFILT_LOCK                */
#define _FEFILT_LOCK_FEFILTLOCKKEY_UNLOCK                0x000027A1UL                              /**< Mode UNLOCK for FEFILT_LOCK                 */
#define FEFILT_LOCK_FEFILTLOCKKEY_DEFAULT                (_FEFILT_LOCK_FEFILTLOCKKEY_DEFAULT << 0) /**< Shifted mode DEFAULT for FEFILT_LOCK        */
#define FEFILT_LOCK_FEFILTLOCKKEY_UNLOCK                 (_FEFILT_LOCK_FEFILTLOCKKEY_UNLOCK << 0)  /**< Shifted mode UNLOCK for FEFILT_LOCK         */

/* Bit fields for FEFILT CFG */
#define _FEFILT_CFG_RESETVALUE                           0x00000000UL                                 /**< Default value for FEFILT_CFG                */
#define _FEFILT_CFG_MASK                                 0x00000001UL                                 /**< Mask for FEFILT_CFG                         */
#define FEFILT_CFG_LOSYNCRESETENABLE                     (0x1UL << 0)                                 /**< Enable sync reset of ADC clock domain       */
#define _FEFILT_CFG_LOSYNCRESETENABLE_SHIFT              0                                            /**< Shift value for FEFILT_LOSYNCRESETENABLE    */
#define _FEFILT_CFG_LOSYNCRESETENABLE_MASK               0x1UL                                        /**< Bit mask for FEFILT_LOSYNCRESETENABLE       */
#define _FEFILT_CFG_LOSYNCRESETENABLE_DEFAULT            0x00000000UL                                 /**< Mode DEFAULT for FEFILT_CFG                 */
#define FEFILT_CFG_LOSYNCRESETENABLE_DEFAULT             (_FEFILT_CFG_LOSYNCRESETENABLE_DEFAULT << 0) /**< Shifted mode DEFAULT for FEFILT_CFG         */

/* Bit fields for FEFILT CMD */
#define _FEFILT_CMD_RESETVALUE                           0x00000000UL                            /**< Default value for FEFILT_CMD                */
#define _FEFILT_CMD_MASK                                 0x00000001UL                            /**< Mask for FEFILT_CMD                         */
#define FEFILT_CMD_SWGAINCHANGE                          (0x1UL << 0)                            /**< Gainchange request cmd                      */
#define _FEFILT_CMD_SWGAINCHANGE_SHIFT                   0                                       /**< Shift value for FEFILT_SWGAINCHANGE         */
#define _FEFILT_CMD_SWGAINCHANGE_MASK                    0x1UL                                   /**< Bit mask for FEFILT_SWGAINCHANGE            */
#define _FEFILT_CMD_SWGAINCHANGE_DEFAULT                 0x00000000UL                            /**< Mode DEFAULT for FEFILT_CMD                 */
#define FEFILT_CMD_SWGAINCHANGE_DEFAULT                  (_FEFILT_CMD_SWGAINCHANGE_DEFAULT << 0) /**< Shifted mode DEFAULT for FEFILT_CMD         */

/* Bit fields for FEFILT CF */
#define _FEFILT_CF_RESETVALUE                            0x00000000UL                     /**< Default value for FEFILT_CF                 */
#define _FEFILT_CF_MASK                                  0xC001FFFFUL                     /**< Mask for FEFILT_CF                          */
#define _FEFILT_CF_DEC0_SHIFT                            0                                /**< Shift value for FEFILT_DEC0                 */
#define _FEFILT_CF_DEC0_MASK                             0x7UL                            /**< Bit mask for FEFILT_DEC0                    */
#define _FEFILT_CF_DEC0_DEFAULT                          0x00000000UL                     /**< Mode DEFAULT for FEFILT_CF                  */
#define _FEFILT_CF_DEC0_DF3                              0x00000000UL                     /**< Mode DF3 for FEFILT_CF                      */
#define _FEFILT_CF_DEC0_DF4WIDE                          0x00000001UL                     /**< Mode DF4WIDE for FEFILT_CF                  */
#define _FEFILT_CF_DEC0_DF4NARROW                        0x00000002UL                     /**< Mode DF4NARROW for FEFILT_CF                */
#define _FEFILT_CF_DEC0_DF8WIDE                          0x00000003UL                     /**< Mode DF8WIDE for FEFILT_CF                  */
#define _FEFILT_CF_DEC0_DF8NARROW                        0x00000004UL                     /**< Mode DF8NARROW for FEFILT_CF                */
#define _FEFILT_CF_DEC0_DF5                              0x00000005UL                     /**< Mode DF5 for FEFILT_CF                      */
#define FEFILT_CF_DEC0_DEFAULT                           (_FEFILT_CF_DEC0_DEFAULT << 0)   /**< Shifted mode DEFAULT for FEFILT_CF          */
#define FEFILT_CF_DEC0_DF3                               (_FEFILT_CF_DEC0_DF3 << 0)       /**< Shifted mode DF3 for FEFILT_CF              */
#define FEFILT_CF_DEC0_DF4WIDE                           (_FEFILT_CF_DEC0_DF4WIDE << 0)   /**< Shifted mode DF4WIDE for FEFILT_CF          */
#define FEFILT_CF_DEC0_DF4NARROW                         (_FEFILT_CF_DEC0_DF4NARROW << 0) /**< Shifted mode DF4NARROW for FEFILT_CF        */
#define FEFILT_CF_DEC0_DF8WIDE                           (_FEFILT_CF_DEC0_DF8WIDE << 0)   /**< Shifted mode DF8WIDE for FEFILT_CF          */
#define FEFILT_CF_DEC0_DF8NARROW                         (_FEFILT_CF_DEC0_DF8NARROW << 0) /**< Shifted mode DF8NARROW for FEFILT_CF        */
#define FEFILT_CF_DEC0_DF5                               (_FEFILT_CF_DEC0_DF5 << 0)       /**< Shifted mode DF5 for FEFILT_CF              */
#define _FEFILT_CF_DEC1_SHIFT                            3                                /**< Shift value for FEFILT_DEC1                 */
#define _FEFILT_CF_DEC1_MASK                             0x1FFF8UL                        /**< Bit mask for FEFILT_DEC1                    */
#define _FEFILT_CF_DEC1_DEFAULT                          0x00000000UL                     /**< Mode DEFAULT for FEFILT_CF                  */
#define FEFILT_CF_DEC1_DEFAULT                           (_FEFILT_CF_DEC1_DEFAULT << 3)   /**< Shifted mode DEFAULT for FEFILT_CF          */

/* Bit fields for FEFILT SRC */
#define _FEFILT_SRC_RESETVALUE                           0x00000000UL                          /**< Default value for FEFILT_SRC                */
#define _FEFILT_SRC_MASK                                 0x39CFFFFFUL                          /**< Mask for FEFILT_SRC                         */
#define _FEFILT_SRC_SRCRATIO_SHIFT                       0                                     /**< Shift value for FEFILT_SRCRATIO             */
#define _FEFILT_SRC_SRCRATIO_MASK                        0xFFFFFUL                             /**< Bit mask for FEFILT_SRCRATIO                */
#define _FEFILT_SRC_SRCRATIO_DEFAULT                     0x00000000UL                          /**< Mode DEFAULT for FEFILT_SRC                 */
#define FEFILT_SRC_SRCRATIO_DEFAULT                      (_FEFILT_SRC_SRCRATIO_DEFAULT << 0)   /**< Shifted mode DEFAULT for FEFILT_SRC         */
#define _FEFILT_SRC_UPGAPS_SHIFT                         22                                    /**< Shift value for FEFILT_UPGAPS               */
#define _FEFILT_SRC_UPGAPS_MASK                          0x1C00000UL                           /**< Bit mask for FEFILT_UPGAPS                  */
#define _FEFILT_SRC_UPGAPS_DEFAULT                       0x00000000UL                          /**< Mode DEFAULT for FEFILT_SRC                 */
#define FEFILT_SRC_UPGAPS_DEFAULT                        (_FEFILT_SRC_UPGAPS_DEFAULT << 22)    /**< Shifted mode DEFAULT for FEFILT_SRC         */
#define FEFILT_SRC_SRCENABLE                             (0x1UL << 27)                         /**< SRC enable                                  */
#define _FEFILT_SRC_SRCENABLE_SHIFT                      27                                    /**< Shift value for FEFILT_SRCENABLE            */
#define _FEFILT_SRC_SRCENABLE_MASK                       0x8000000UL                           /**< Bit mask for FEFILT_SRCENABLE               */
#define _FEFILT_SRC_SRCENABLE_DEFAULT                    0x00000000UL                          /**< Mode DEFAULT for FEFILT_SRC                 */
#define FEFILT_SRC_SRCENABLE_DEFAULT                     (_FEFILT_SRC_SRCENABLE_DEFAULT << 27) /**< Shifted mode DEFAULT for FEFILT_SRC         */
#define _FEFILT_SRC_SRCSRD_SHIFT                         28                                    /**< Shift value for FEFILT_SRCSRD               */
#define _FEFILT_SRC_SRCSRD_MASK                          0x30000000UL                          /**< Bit mask for FEFILT_SRCSRD                  */
#define _FEFILT_SRC_SRCSRD_DEFAULT                       0x00000000UL                          /**< Mode DEFAULT for FEFILT_SRC                 */
#define _FEFILT_SRC_SRCSRD_NODEC                         0x00000000UL                          /**< Mode NODEC for FEFILT_SRC                   */
#define _FEFILT_SRC_SRCSRD_DEC2                          0x00000001UL                          /**< Mode DEC2 for FEFILT_SRC                    */
#define _FEFILT_SRC_SRCSRD_DEC3                          0x00000002UL                          /**< Mode DEC3 for FEFILT_SRC                    */
#define _FEFILT_SRC_SRCSRD_DEC4                          0x00000003UL                          /**< Mode DEC4 for FEFILT_SRC                    */
#define FEFILT_SRC_SRCSRD_DEFAULT                        (_FEFILT_SRC_SRCSRD_DEFAULT << 28)    /**< Shifted mode DEFAULT for FEFILT_SRC         */
#define FEFILT_SRC_SRCSRD_NODEC                          (_FEFILT_SRC_SRCSRD_NODEC << 28)      /**< Shifted mode NODEC for FEFILT_SRC           */
#define FEFILT_SRC_SRCSRD_DEC2                           (_FEFILT_SRC_SRCSRD_DEC2 << 28)       /**< Shifted mode DEC2 for FEFILT_SRC            */
#define FEFILT_SRC_SRCSRD_DEC3                           (_FEFILT_SRC_SRCSRD_DEC3 << 28)       /**< Shifted mode DEC3 for FEFILT_SRC            */
#define FEFILT_SRC_SRCSRD_DEC4                           (_FEFILT_SRC_SRCSRD_DEC4 << 28)       /**< Shifted mode DEC4 for FEFILT_SRC            */

/* Bit fields for FEFILT DIGIGAINCTRL */
#define _FEFILT_DIGIGAINCTRL_RESETVALUE                  0x00000000UL                                   /**< Default value for FEFILT_DIGIGAINCTRL       */
#define _FEFILT_DIGIGAINCTRL_MASK                        0x0000FFFFUL                                   /**< Mask for FEFILT_DIGIGAINCTRL                */
#define FEFILT_DIGIGAINCTRL_DIGIGAINEN                   (0x1UL << 0)                                   /**< Digital Gain Enable                         */
#define _FEFILT_DIGIGAINCTRL_DIGIGAINEN_SHIFT            0                                              /**< Shift value for FEFILT_DIGIGAINEN           */
#define _FEFILT_DIGIGAINCTRL_DIGIGAINEN_MASK             0x1UL                                          /**< Bit mask for FEFILT_DIGIGAINEN              */
#define _FEFILT_DIGIGAINCTRL_DIGIGAINEN_DEFAULT          0x00000000UL                                   /**< Mode DEFAULT for FEFILT_DIGIGAINCTRL        */
#define FEFILT_DIGIGAINCTRL_DIGIGAINEN_DEFAULT           (_FEFILT_DIGIGAINCTRL_DIGIGAINEN_DEFAULT << 0) /**< Shifted mode DEFAULT for FEFILT_DIGIGAINCTRL*/
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_SHIFT              1                                              /**< Shift value for FEFILT_DIGIGAIN             */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_MASK               0x1FEUL                                        /**< Bit mask for FEFILT_DIGIGAIN                */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_DEFAULT            0x00000000UL                                   /**< Mode DEFAULT for FEFILT_DIGIGAINCTRL        */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM3             0x00000000UL                                   /**< Mode GAINM3 for FEFILT_DIGIGAINCTRL         */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM2P75          0x00000001UL                                   /**< Mode GAINM2P75 for FEFILT_DIGIGAINCTRL      */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM2P5           0x00000002UL                                   /**< Mode GAINM2P5 for FEFILT_DIGIGAINCTRL       */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM2P25          0x00000003UL                                   /**< Mode GAINM2P25 for FEFILT_DIGIGAINCTRL      */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM2             0x00000004UL                                   /**< Mode GAINM2 for FEFILT_DIGIGAINCTRL         */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM1P75          0x00000005UL                                   /**< Mode GAINM1P75 for FEFILT_DIGIGAINCTRL      */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM1P5           0x00000006UL                                   /**< Mode GAINM1P5 for FEFILT_DIGIGAINCTRL       */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM1P25          0x00000007UL                                   /**< Mode GAINM1P25 for FEFILT_DIGIGAINCTRL      */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM1             0x00000008UL                                   /**< Mode GAINM1 for FEFILT_DIGIGAINCTRL         */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM0P75          0x00000009UL                                   /**< Mode GAINM0P75 for FEFILT_DIGIGAINCTRL      */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM0P5           0x0000000AUL                                   /**< Mode GAINM0P5 for FEFILT_DIGIGAINCTRL       */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM0P25          0x0000000BUL                                   /**< Mode GAINM0P25 for FEFILT_DIGIGAINCTRL      */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM0             0x0000000CUL                                   /**< Mode GAINM0 for FEFILT_DIGIGAINCTRL         */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP0P25          0x0000000DUL                                   /**< Mode GAINP0P25 for FEFILT_DIGIGAINCTRL      */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP0P5           0x0000000EUL                                   /**< Mode GAINP0P5 for FEFILT_DIGIGAINCTRL       */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP0P75          0x0000000FUL                                   /**< Mode GAINP0P75 for FEFILT_DIGIGAINCTRL      */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP1             0x00000010UL                                   /**< Mode GAINP1 for FEFILT_DIGIGAINCTRL         */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP1P25          0x00000011UL                                   /**< Mode GAINP1P25 for FEFILT_DIGIGAINCTRL      */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP1P5           0x00000012UL                                   /**< Mode GAINP1P5 for FEFILT_DIGIGAINCTRL       */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP1P75          0x00000013UL                                   /**< Mode GAINP1P75 for FEFILT_DIGIGAINCTRL      */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP2             0x00000014UL                                   /**< Mode GAINP2 for FEFILT_DIGIGAINCTRL         */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP2P25          0x00000015UL                                   /**< Mode GAINP2P25 for FEFILT_DIGIGAINCTRL      */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP2P5           0x00000016UL                                   /**< Mode GAINP2P5 for FEFILT_DIGIGAINCTRL       */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP2P75          0x00000017UL                                   /**< Mode GAINP2P75 for FEFILT_DIGIGAINCTRL      */
#define _FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP3             0x00000018UL                                   /**< Mode GAINP3 for FEFILT_DIGIGAINCTRL         */
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_DEFAULT             (_FEFILT_DIGIGAINCTRL_DIGIGAIN_DEFAULT << 1)   /**< Shifted mode DEFAULT for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM3              (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM3 << 1)    /**< Shifted mode GAINM3 for FEFILT_DIGIGAINCTRL */
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM2P75           (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM2P75 << 1) /**< Shifted mode GAINM2P75 for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM2P5            (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM2P5 << 1)  /**< Shifted mode GAINM2P5 for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM2P25           (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM2P25 << 1) /**< Shifted mode GAINM2P25 for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM2              (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM2 << 1)    /**< Shifted mode GAINM2 for FEFILT_DIGIGAINCTRL */
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM1P75           (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM1P75 << 1) /**< Shifted mode GAINM1P75 for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM1P5            (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM1P5 << 1)  /**< Shifted mode GAINM1P5 for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM1P25           (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM1P25 << 1) /**< Shifted mode GAINM1P25 for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM1              (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM1 << 1)    /**< Shifted mode GAINM1 for FEFILT_DIGIGAINCTRL */
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM0P75           (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM0P75 << 1) /**< Shifted mode GAINM0P75 for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM0P5            (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM0P5 << 1)  /**< Shifted mode GAINM0P5 for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM0P25           (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM0P25 << 1) /**< Shifted mode GAINM0P25 for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM0              (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINM0 << 1)    /**< Shifted mode GAINM0 for FEFILT_DIGIGAINCTRL */
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP0P25           (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP0P25 << 1) /**< Shifted mode GAINP0P25 for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP0P5            (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP0P5 << 1)  /**< Shifted mode GAINP0P5 for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP0P75           (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP0P75 << 1) /**< Shifted mode GAINP0P75 for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP1              (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP1 << 1)    /**< Shifted mode GAINP1 for FEFILT_DIGIGAINCTRL */
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP1P25           (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP1P25 << 1) /**< Shifted mode GAINP1P25 for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP1P5            (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP1P5 << 1)  /**< Shifted mode GAINP1P5 for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP1P75           (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP1P75 << 1) /**< Shifted mode GAINP1P75 for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP2              (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP2 << 1)    /**< Shifted mode GAINP2 for FEFILT_DIGIGAINCTRL */
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP2P25           (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP2P25 << 1) /**< Shifted mode GAINP2P25 for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP2P5            (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP2P5 << 1)  /**< Shifted mode GAINP2P5 for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP2P75           (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP2P75 << 1) /**< Shifted mode GAINP2P75 for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP3              (_FEFILT_DIGIGAINCTRL_DIGIGAIN_GAINP3 << 1)    /**< Shifted mode GAINP3 for FEFILT_DIGIGAINCTRL */
#define FEFILT_DIGIGAINCTRL_DEC0GAIN                     (0x1UL << 9)                                   /**< DEC0 Gain Select                            */
#define _FEFILT_DIGIGAINCTRL_DEC0GAIN_SHIFT              9                                              /**< Shift value for FEFILT_DEC0GAIN             */
#define _FEFILT_DIGIGAINCTRL_DEC0GAIN_MASK               0x200UL                                        /**< Bit mask for FEFILT_DEC0GAIN                */
#define _FEFILT_DIGIGAINCTRL_DEC0GAIN_DEFAULT            0x00000000UL                                   /**< Mode DEFAULT for FEFILT_DIGIGAINCTRL        */
#define FEFILT_DIGIGAINCTRL_DEC0GAIN_DEFAULT             (_FEFILT_DIGIGAINCTRL_DEC0GAIN_DEFAULT << 9)   /**< Shifted mode DEFAULT for FEFILT_DIGIGAINCTRL*/
#define _FEFILT_DIGIGAINCTRL_DEC1GAIN_SHIFT              10                                             /**< Shift value for FEFILT_DEC1GAIN             */
#define _FEFILT_DIGIGAINCTRL_DEC1GAIN_MASK               0xC00UL                                        /**< Bit mask for FEFILT_DEC1GAIN                */
#define _FEFILT_DIGIGAINCTRL_DEC1GAIN_DEFAULT            0x00000000UL                                   /**< Mode DEFAULT for FEFILT_DIGIGAINCTRL        */
#define _FEFILT_DIGIGAINCTRL_DEC1GAIN_ADD0               0x00000000UL                                   /**< Mode ADD0 for FEFILT_DIGIGAINCTRL           */
#define _FEFILT_DIGIGAINCTRL_DEC1GAIN_ADD6               0x00000001UL                                   /**< Mode ADD6 for FEFILT_DIGIGAINCTRL           */
#define _FEFILT_DIGIGAINCTRL_DEC1GAIN_ADD12              0x00000002UL                                   /**< Mode ADD12 for FEFILT_DIGIGAINCTRL          */
#define FEFILT_DIGIGAINCTRL_DEC1GAIN_DEFAULT             (_FEFILT_DIGIGAINCTRL_DEC1GAIN_DEFAULT << 10)  /**< Shifted mode DEFAULT for FEFILT_DIGIGAINCTRL*/
#define FEFILT_DIGIGAINCTRL_DEC1GAIN_ADD0                (_FEFILT_DIGIGAINCTRL_DEC1GAIN_ADD0 << 10)     /**< Shifted mode ADD0 for FEFILT_DIGIGAINCTRL   */
#define FEFILT_DIGIGAINCTRL_DEC1GAIN_ADD6                (_FEFILT_DIGIGAINCTRL_DEC1GAIN_ADD6 << 10)     /**< Shifted mode ADD6 for FEFILT_DIGIGAINCTRL   */
#define FEFILT_DIGIGAINCTRL_DEC1GAIN_ADD12               (_FEFILT_DIGIGAINCTRL_DEC1GAIN_ADD12 << 10)    /**< Shifted mode ADD12 for FEFILT_DIGIGAINCTRL  */
#define _FEFILT_DIGIGAINCTRL_BBSS_SHIFT                  12                                             /**< Shift value for FEFILT_BBSS                 */
#define _FEFILT_DIGIGAINCTRL_BBSS_MASK                   0xF000UL                                       /**< Bit mask for FEFILT_BBSS                    */
#define _FEFILT_DIGIGAINCTRL_BBSS_DEFAULT                0x00000000UL                                   /**< Mode DEFAULT for FEFILT_DIGIGAINCTRL        */
#define FEFILT_DIGIGAINCTRL_BBSS_DEFAULT                 (_FEFILT_DIGIGAINCTRL_BBSS_DEFAULT << 12)      /**< Shifted mode DEFAULT for FEFILT_DIGIGAINCTRL*/

/* Bit fields for FEFILT CHFCOE00 */
#define _FEFILT_CHFCOE00_RESETVALUE                      0x00000000UL                                /**< Default value for FEFILT_CHFCOE00           */
#define _FEFILT_CHFCOE00_MASK                            0x3FFFFFFFUL                                /**< Mask for FEFILT_CHFCOE00                    */
#define _FEFILT_CHFCOE00_SET0COEFF0_SHIFT                0                                           /**< Shift value for FEFILT_SET0COEFF0           */
#define _FEFILT_CHFCOE00_SET0COEFF0_MASK                 0x3FFUL                                     /**< Bit mask for FEFILT_SET0COEFF0              */
#define _FEFILT_CHFCOE00_SET0COEFF0_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for FEFILT_CHFCOE00            */
#define FEFILT_CHFCOE00_SET0COEFF0_DEFAULT               (_FEFILT_CHFCOE00_SET0COEFF0_DEFAULT << 0)  /**< Shifted mode DEFAULT for FEFILT_CHFCOE00    */
#define _FEFILT_CHFCOE00_SET0COEFF1_SHIFT                10                                          /**< Shift value for FEFILT_SET0COEFF1           */
#define _FEFILT_CHFCOE00_SET0COEFF1_MASK                 0xFFC00UL                                   /**< Bit mask for FEFILT_SET0COEFF1              */
#define _FEFILT_CHFCOE00_SET0COEFF1_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for FEFILT_CHFCOE00            */
#define FEFILT_CHFCOE00_SET0COEFF1_DEFAULT               (_FEFILT_CHFCOE00_SET0COEFF1_DEFAULT << 10) /**< Shifted mode DEFAULT for FEFILT_CHFCOE00    */
#define _FEFILT_CHFCOE00_SET0COEFF2_SHIFT                20                                          /**< Shift value for FEFILT_SET0COEFF2           */
#define _FEFILT_CHFCOE00_SET0COEFF2_MASK                 0x3FF00000UL                                /**< Bit mask for FEFILT_SET0COEFF2              */
#define _FEFILT_CHFCOE00_SET0COEFF2_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for FEFILT_CHFCOE00            */
#define FEFILT_CHFCOE00_SET0COEFF2_DEFAULT               (_FEFILT_CHFCOE00_SET0COEFF2_DEFAULT << 20) /**< Shifted mode DEFAULT for FEFILT_CHFCOE00    */

/* Bit fields for FEFILT CHFCOE01 */
#define _FEFILT_CHFCOE01_RESETVALUE                      0x00000000UL                                /**< Default value for FEFILT_CHFCOE01           */
#define _FEFILT_CHFCOE01_MASK                            0x003FFFFFUL                                /**< Mask for FEFILT_CHFCOE01                    */
#define _FEFILT_CHFCOE01_SET0COEFF3_SHIFT                0                                           /**< Shift value for FEFILT_SET0COEFF3           */
#define _FEFILT_CHFCOE01_SET0COEFF3_MASK                 0x7FFUL                                     /**< Bit mask for FEFILT_SET0COEFF3              */
#define _FEFILT_CHFCOE01_SET0COEFF3_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for FEFILT_CHFCOE01            */
#define FEFILT_CHFCOE01_SET0COEFF3_DEFAULT               (_FEFILT_CHFCOE01_SET0COEFF3_DEFAULT << 0)  /**< Shifted mode DEFAULT for FEFILT_CHFCOE01    */
#define _FEFILT_CHFCOE01_SET0COEFF4_SHIFT                11                                          /**< Shift value for FEFILT_SET0COEFF4           */
#define _FEFILT_CHFCOE01_SET0COEFF4_MASK                 0x3FF800UL                                  /**< Bit mask for FEFILT_SET0COEFF4              */
#define _FEFILT_CHFCOE01_SET0COEFF4_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for FEFILT_CHFCOE01            */
#define FEFILT_CHFCOE01_SET0COEFF4_DEFAULT               (_FEFILT_CHFCOE01_SET0COEFF4_DEFAULT << 11) /**< Shifted mode DEFAULT for FEFILT_CHFCOE01    */

/* Bit fields for FEFILT CHFCOE02 */
#define _FEFILT_CHFCOE02_RESETVALUE                      0x00000000UL                                /**< Default value for FEFILT_CHFCOE02           */
#define _FEFILT_CHFCOE02_MASK                            0x007FFFFFUL                                /**< Mask for FEFILT_CHFCOE02                    */
#define _FEFILT_CHFCOE02_SET0COEFF5_SHIFT                0                                           /**< Shift value for FEFILT_SET0COEFF5           */
#define _FEFILT_CHFCOE02_SET0COEFF5_MASK                 0x7FFUL                                     /**< Bit mask for FEFILT_SET0COEFF5              */
#define _FEFILT_CHFCOE02_SET0COEFF5_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for FEFILT_CHFCOE02            */
#define FEFILT_CHFCOE02_SET0COEFF5_DEFAULT               (_FEFILT_CHFCOE02_SET0COEFF5_DEFAULT << 0)  /**< Shifted mode DEFAULT for FEFILT_CHFCOE02    */
#define _FEFILT_CHFCOE02_SET0COEFF6_SHIFT                11                                          /**< Shift value for FEFILT_SET0COEFF6           */
#define _FEFILT_CHFCOE02_SET0COEFF6_MASK                 0x7FF800UL                                  /**< Bit mask for FEFILT_SET0COEFF6              */
#define _FEFILT_CHFCOE02_SET0COEFF6_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for FEFILT_CHFCOE02            */
#define FEFILT_CHFCOE02_SET0COEFF6_DEFAULT               (_FEFILT_CHFCOE02_SET0COEFF6_DEFAULT << 11) /**< Shifted mode DEFAULT for FEFILT_CHFCOE02    */

/* Bit fields for FEFILT CHFCOE03 */
#define _FEFILT_CHFCOE03_RESETVALUE                      0x00000000UL                                /**< Default value for FEFILT_CHFCOE03           */
#define _FEFILT_CHFCOE03_MASK                            0x00FFFFFFUL                                /**< Mask for FEFILT_CHFCOE03                    */
#define _FEFILT_CHFCOE03_SET0COEFF7_SHIFT                0                                           /**< Shift value for FEFILT_SET0COEFF7           */
#define _FEFILT_CHFCOE03_SET0COEFF7_MASK                 0xFFFUL                                     /**< Bit mask for FEFILT_SET0COEFF7              */
#define _FEFILT_CHFCOE03_SET0COEFF7_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for FEFILT_CHFCOE03            */
#define FEFILT_CHFCOE03_SET0COEFF7_DEFAULT               (_FEFILT_CHFCOE03_SET0COEFF7_DEFAULT << 0)  /**< Shifted mode DEFAULT for FEFILT_CHFCOE03    */
#define _FEFILT_CHFCOE03_SET0COEFF8_SHIFT                12                                          /**< Shift value for FEFILT_SET0COEFF8           */
#define _FEFILT_CHFCOE03_SET0COEFF8_MASK                 0xFFF000UL                                  /**< Bit mask for FEFILT_SET0COEFF8              */
#define _FEFILT_CHFCOE03_SET0COEFF8_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for FEFILT_CHFCOE03            */
#define FEFILT_CHFCOE03_SET0COEFF8_DEFAULT               (_FEFILT_CHFCOE03_SET0COEFF8_DEFAULT << 12) /**< Shifted mode DEFAULT for FEFILT_CHFCOE03    */

/* Bit fields for FEFILT CHFCOE04 */
#define _FEFILT_CHFCOE04_RESETVALUE                      0x00000000UL                                 /**< Default value for FEFILT_CHFCOE04           */
#define _FEFILT_CHFCOE04_MASK                            0x0FFFFFFFUL                                 /**< Mask for FEFILT_CHFCOE04                    */
#define _FEFILT_CHFCOE04_SET0COEFF9_SHIFT                0                                            /**< Shift value for FEFILT_SET0COEFF9           */
#define _FEFILT_CHFCOE04_SET0COEFF9_MASK                 0x3FFFUL                                     /**< Bit mask for FEFILT_SET0COEFF9              */
#define _FEFILT_CHFCOE04_SET0COEFF9_DEFAULT              0x00000000UL                                 /**< Mode DEFAULT for FEFILT_CHFCOE04            */
#define FEFILT_CHFCOE04_SET0COEFF9_DEFAULT               (_FEFILT_CHFCOE04_SET0COEFF9_DEFAULT << 0)   /**< Shifted mode DEFAULT for FEFILT_CHFCOE04    */
#define _FEFILT_CHFCOE04_SET0COEFF10_SHIFT               14                                           /**< Shift value for FEFILT_SET0COEFF10          */
#define _FEFILT_CHFCOE04_SET0COEFF10_MASK                0xFFFC000UL                                  /**< Bit mask for FEFILT_SET0COEFF10             */
#define _FEFILT_CHFCOE04_SET0COEFF10_DEFAULT             0x00000000UL                                 /**< Mode DEFAULT for FEFILT_CHFCOE04            */
#define FEFILT_CHFCOE04_SET0COEFF10_DEFAULT              (_FEFILT_CHFCOE04_SET0COEFF10_DEFAULT << 14) /**< Shifted mode DEFAULT for FEFILT_CHFCOE04    */

/* Bit fields for FEFILT CHFCOE05 */
#define _FEFILT_CHFCOE05_RESETVALUE                      0x00000000UL                                 /**< Default value for FEFILT_CHFCOE05           */
#define _FEFILT_CHFCOE05_MASK                            0x3FFFFFFFUL                                 /**< Mask for FEFILT_CHFCOE05                    */
#define _FEFILT_CHFCOE05_SET0COEFF11_SHIFT               0                                            /**< Shift value for FEFILT_SET0COEFF11          */
#define _FEFILT_CHFCOE05_SET0COEFF11_MASK                0x3FFFUL                                     /**< Bit mask for FEFILT_SET0COEFF11             */
#define _FEFILT_CHFCOE05_SET0COEFF11_DEFAULT             0x00000000UL                                 /**< Mode DEFAULT for FEFILT_CHFCOE05            */
#define FEFILT_CHFCOE05_SET0COEFF11_DEFAULT              (_FEFILT_CHFCOE05_SET0COEFF11_DEFAULT << 0)  /**< Shifted mode DEFAULT for FEFILT_CHFCOE05    */
#define _FEFILT_CHFCOE05_SET0COEFF12_SHIFT               14                                           /**< Shift value for FEFILT_SET0COEFF12          */
#define _FEFILT_CHFCOE05_SET0COEFF12_MASK                0x3FFFC000UL                                 /**< Bit mask for FEFILT_SET0COEFF12             */
#define _FEFILT_CHFCOE05_SET0COEFF12_DEFAULT             0x00000000UL                                 /**< Mode DEFAULT for FEFILT_CHFCOE05            */
#define FEFILT_CHFCOE05_SET0COEFF12_DEFAULT              (_FEFILT_CHFCOE05_SET0COEFF12_DEFAULT << 14) /**< Shifted mode DEFAULT for FEFILT_CHFCOE05    */

/* Bit fields for FEFILT CHFCOE06 */
#define _FEFILT_CHFCOE06_RESETVALUE                      0x00000000UL                                 /**< Default value for FEFILT_CHFCOE06           */
#define _FEFILT_CHFCOE06_MASK                            0xFFFFFFFFUL                                 /**< Mask for FEFILT_CHFCOE06                    */
#define _FEFILT_CHFCOE06_SET0COEFF13_SHIFT               0                                            /**< Shift value for FEFILT_SET0COEFF13          */
#define _FEFILT_CHFCOE06_SET0COEFF13_MASK                0xFFFFUL                                     /**< Bit mask for FEFILT_SET0COEFF13             */
#define _FEFILT_CHFCOE06_SET0COEFF13_DEFAULT             0x00000000UL                                 /**< Mode DEFAULT for FEFILT_CHFCOE06            */
#define FEFILT_CHFCOE06_SET0COEFF13_DEFAULT              (_FEFILT_CHFCOE06_SET0COEFF13_DEFAULT << 0)  /**< Shifted mode DEFAULT for FEFILT_CHFCOE06    */
#define _FEFILT_CHFCOE06_SET0COEFF14_SHIFT               16                                           /**< Shift value for FEFILT_SET0COEFF14          */
#define _FEFILT_CHFCOE06_SET0COEFF14_MASK                0xFFFF0000UL                                 /**< Bit mask for FEFILT_SET0COEFF14             */
#define _FEFILT_CHFCOE06_SET0COEFF14_DEFAULT             0x00000000UL                                 /**< Mode DEFAULT for FEFILT_CHFCOE06            */
#define FEFILT_CHFCOE06_SET0COEFF14_DEFAULT              (_FEFILT_CHFCOE06_SET0COEFF14_DEFAULT << 16) /**< Shifted mode DEFAULT for FEFILT_CHFCOE06    */

/* Bit fields for FEFILT CHFCOE10 */
#define _FEFILT_CHFCOE10_RESETVALUE                      0x00000000UL                                /**< Default value for FEFILT_CHFCOE10           */
#define _FEFILT_CHFCOE10_MASK                            0x3FFFFFFFUL                                /**< Mask for FEFILT_CHFCOE10                    */
#define _FEFILT_CHFCOE10_SET1COEFF0_SHIFT                0                                           /**< Shift value for FEFILT_SET1COEFF0           */
#define _FEFILT_CHFCOE10_SET1COEFF0_MASK                 0x3FFUL                                     /**< Bit mask for FEFILT_SET1COEFF0              */
#define _FEFILT_CHFCOE10_SET1COEFF0_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for FEFILT_CHFCOE10            */
#define FEFILT_CHFCOE10_SET1COEFF0_DEFAULT               (_FEFILT_CHFCOE10_SET1COEFF0_DEFAULT << 0)  /**< Shifted mode DEFAULT for FEFILT_CHFCOE10    */
#define _FEFILT_CHFCOE10_SET1COEFF1_SHIFT                10                                          /**< Shift value for FEFILT_SET1COEFF1           */
#define _FEFILT_CHFCOE10_SET1COEFF1_MASK                 0xFFC00UL                                   /**< Bit mask for FEFILT_SET1COEFF1              */
#define _FEFILT_CHFCOE10_SET1COEFF1_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for FEFILT_CHFCOE10            */
#define FEFILT_CHFCOE10_SET1COEFF1_DEFAULT               (_FEFILT_CHFCOE10_SET1COEFF1_DEFAULT << 10) /**< Shifted mode DEFAULT for FEFILT_CHFCOE10    */
#define _FEFILT_CHFCOE10_SET1COEFF2_SHIFT                20                                          /**< Shift value for FEFILT_SET1COEFF2           */
#define _FEFILT_CHFCOE10_SET1COEFF2_MASK                 0x3FF00000UL                                /**< Bit mask for FEFILT_SET1COEFF2              */
#define _FEFILT_CHFCOE10_SET1COEFF2_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for FEFILT_CHFCOE10            */
#define FEFILT_CHFCOE10_SET1COEFF2_DEFAULT               (_FEFILT_CHFCOE10_SET1COEFF2_DEFAULT << 20) /**< Shifted mode DEFAULT for FEFILT_CHFCOE10    */

/* Bit fields for FEFILT CHFCOE11 */
#define _FEFILT_CHFCOE11_RESETVALUE                      0x00000000UL                                /**< Default value for FEFILT_CHFCOE11           */
#define _FEFILT_CHFCOE11_MASK                            0x003FFFFFUL                                /**< Mask for FEFILT_CHFCOE11                    */
#define _FEFILT_CHFCOE11_SET1COEFF3_SHIFT                0                                           /**< Shift value for FEFILT_SET1COEFF3           */
#define _FEFILT_CHFCOE11_SET1COEFF3_MASK                 0x7FFUL                                     /**< Bit mask for FEFILT_SET1COEFF3              */
#define _FEFILT_CHFCOE11_SET1COEFF3_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for FEFILT_CHFCOE11            */
#define FEFILT_CHFCOE11_SET1COEFF3_DEFAULT               (_FEFILT_CHFCOE11_SET1COEFF3_DEFAULT << 0)  /**< Shifted mode DEFAULT for FEFILT_CHFCOE11    */
#define _FEFILT_CHFCOE11_SET1COEFF4_SHIFT                11                                          /**< Shift value for FEFILT_SET1COEFF4           */
#define _FEFILT_CHFCOE11_SET1COEFF4_MASK                 0x3FF800UL                                  /**< Bit mask for FEFILT_SET1COEFF4              */
#define _FEFILT_CHFCOE11_SET1COEFF4_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for FEFILT_CHFCOE11            */
#define FEFILT_CHFCOE11_SET1COEFF4_DEFAULT               (_FEFILT_CHFCOE11_SET1COEFF4_DEFAULT << 11) /**< Shifted mode DEFAULT for FEFILT_CHFCOE11    */

/* Bit fields for FEFILT CHFCOE12 */
#define _FEFILT_CHFCOE12_RESETVALUE                      0x00000000UL                                /**< Default value for FEFILT_CHFCOE12           */
#define _FEFILT_CHFCOE12_MASK                            0x007FFFFFUL                                /**< Mask for FEFILT_CHFCOE12                    */
#define _FEFILT_CHFCOE12_SET1COEFF5_SHIFT                0                                           /**< Shift value for FEFILT_SET1COEFF5           */
#define _FEFILT_CHFCOE12_SET1COEFF5_MASK                 0x7FFUL                                     /**< Bit mask for FEFILT_SET1COEFF5              */
#define _FEFILT_CHFCOE12_SET1COEFF5_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for FEFILT_CHFCOE12            */
#define FEFILT_CHFCOE12_SET1COEFF5_DEFAULT               (_FEFILT_CHFCOE12_SET1COEFF5_DEFAULT << 0)  /**< Shifted mode DEFAULT for FEFILT_CHFCOE12    */
#define _FEFILT_CHFCOE12_SET1COEFF6_SHIFT                11                                          /**< Shift value for FEFILT_SET1COEFF6           */
#define _FEFILT_CHFCOE12_SET1COEFF6_MASK                 0x7FF800UL                                  /**< Bit mask for FEFILT_SET1COEFF6              */
#define _FEFILT_CHFCOE12_SET1COEFF6_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for FEFILT_CHFCOE12            */
#define FEFILT_CHFCOE12_SET1COEFF6_DEFAULT               (_FEFILT_CHFCOE12_SET1COEFF6_DEFAULT << 11) /**< Shifted mode DEFAULT for FEFILT_CHFCOE12    */

/* Bit fields for FEFILT CHFCOE13 */
#define _FEFILT_CHFCOE13_RESETVALUE                      0x00000000UL                                /**< Default value for FEFILT_CHFCOE13           */
#define _FEFILT_CHFCOE13_MASK                            0x00FFFFFFUL                                /**< Mask for FEFILT_CHFCOE13                    */
#define _FEFILT_CHFCOE13_SET1COEFF7_SHIFT                0                                           /**< Shift value for FEFILT_SET1COEFF7           */
#define _FEFILT_CHFCOE13_SET1COEFF7_MASK                 0xFFFUL                                     /**< Bit mask for FEFILT_SET1COEFF7              */
#define _FEFILT_CHFCOE13_SET1COEFF7_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for FEFILT_CHFCOE13            */
#define FEFILT_CHFCOE13_SET1COEFF7_DEFAULT               (_FEFILT_CHFCOE13_SET1COEFF7_DEFAULT << 0)  /**< Shifted mode DEFAULT for FEFILT_CHFCOE13    */
#define _FEFILT_CHFCOE13_SET1COEFF8_SHIFT                12                                          /**< Shift value for FEFILT_SET1COEFF8           */
#define _FEFILT_CHFCOE13_SET1COEFF8_MASK                 0xFFF000UL                                  /**< Bit mask for FEFILT_SET1COEFF8              */
#define _FEFILT_CHFCOE13_SET1COEFF8_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for FEFILT_CHFCOE13            */
#define FEFILT_CHFCOE13_SET1COEFF8_DEFAULT               (_FEFILT_CHFCOE13_SET1COEFF8_DEFAULT << 12) /**< Shifted mode DEFAULT for FEFILT_CHFCOE13    */

/* Bit fields for FEFILT CHFCOE15 */
#define _FEFILT_CHFCOE15_RESETVALUE                      0x00000000UL                                 /**< Default value for FEFILT_CHFCOE15           */
#define _FEFILT_CHFCOE15_MASK                            0x3FFFFFFFUL                                 /**< Mask for FEFILT_CHFCOE15                    */
#define _FEFILT_CHFCOE15_SET1COEFF11_SHIFT               0                                            /**< Shift value for FEFILT_SET1COEFF11          */
#define _FEFILT_CHFCOE15_SET1COEFF11_MASK                0x3FFFUL                                     /**< Bit mask for FEFILT_SET1COEFF11             */
#define _FEFILT_CHFCOE15_SET1COEFF11_DEFAULT             0x00000000UL                                 /**< Mode DEFAULT for FEFILT_CHFCOE15            */
#define FEFILT_CHFCOE15_SET1COEFF11_DEFAULT              (_FEFILT_CHFCOE15_SET1COEFF11_DEFAULT << 0)  /**< Shifted mode DEFAULT for FEFILT_CHFCOE15    */
#define _FEFILT_CHFCOE15_SET1COEFF12_SHIFT               14                                           /**< Shift value for FEFILT_SET1COEFF12          */
#define _FEFILT_CHFCOE15_SET1COEFF12_MASK                0x3FFFC000UL                                 /**< Bit mask for FEFILT_SET1COEFF12             */
#define _FEFILT_CHFCOE15_SET1COEFF12_DEFAULT             0x00000000UL                                 /**< Mode DEFAULT for FEFILT_CHFCOE15            */
#define FEFILT_CHFCOE15_SET1COEFF12_DEFAULT              (_FEFILT_CHFCOE15_SET1COEFF12_DEFAULT << 14) /**< Shifted mode DEFAULT for FEFILT_CHFCOE15    */

/* Bit fields for FEFILT CHFCOE14 */
#define _FEFILT_CHFCOE14_RESETVALUE                      0x00000000UL                                 /**< Default value for FEFILT_CHFCOE14           */
#define _FEFILT_CHFCOE14_MASK                            0x0FFFFFFFUL                                 /**< Mask for FEFILT_CHFCOE14                    */
#define _FEFILT_CHFCOE14_SET1COEFF9_SHIFT                0                                            /**< Shift value for FEFILT_SET1COEFF9           */
#define _FEFILT_CHFCOE14_SET1COEFF9_MASK                 0x3FFFUL                                     /**< Bit mask for FEFILT_SET1COEFF9              */
#define _FEFILT_CHFCOE14_SET1COEFF9_DEFAULT              0x00000000UL                                 /**< Mode DEFAULT for FEFILT_CHFCOE14            */
#define FEFILT_CHFCOE14_SET1COEFF9_DEFAULT               (_FEFILT_CHFCOE14_SET1COEFF9_DEFAULT << 0)   /**< Shifted mode DEFAULT for FEFILT_CHFCOE14    */
#define _FEFILT_CHFCOE14_SET1COEFF10_SHIFT               14                                           /**< Shift value for FEFILT_SET1COEFF10          */
#define _FEFILT_CHFCOE14_SET1COEFF10_MASK                0xFFFC000UL                                  /**< Bit mask for FEFILT_SET1COEFF10             */
#define _FEFILT_CHFCOE14_SET1COEFF10_DEFAULT             0x00000000UL                                 /**< Mode DEFAULT for FEFILT_CHFCOE14            */
#define FEFILT_CHFCOE14_SET1COEFF10_DEFAULT              (_FEFILT_CHFCOE14_SET1COEFF10_DEFAULT << 14) /**< Shifted mode DEFAULT for FEFILT_CHFCOE14    */

/* Bit fields for FEFILT CHFCOE16 */
#define _FEFILT_CHFCOE16_RESETVALUE                      0x00000000UL                                 /**< Default value for FEFILT_CHFCOE16           */
#define _FEFILT_CHFCOE16_MASK                            0xFFFFFFFFUL                                 /**< Mask for FEFILT_CHFCOE16                    */
#define _FEFILT_CHFCOE16_SET1COEFF13_SHIFT               0                                            /**< Shift value for FEFILT_SET1COEFF13          */
#define _FEFILT_CHFCOE16_SET1COEFF13_MASK                0xFFFFUL                                     /**< Bit mask for FEFILT_SET1COEFF13             */
#define _FEFILT_CHFCOE16_SET1COEFF13_DEFAULT             0x00000000UL                                 /**< Mode DEFAULT for FEFILT_CHFCOE16            */
#define FEFILT_CHFCOE16_SET1COEFF13_DEFAULT              (_FEFILT_CHFCOE16_SET1COEFF13_DEFAULT << 0)  /**< Shifted mode DEFAULT for FEFILT_CHFCOE16    */
#define _FEFILT_CHFCOE16_SET1COEFF14_SHIFT               16                                           /**< Shift value for FEFILT_SET1COEFF14          */
#define _FEFILT_CHFCOE16_SET1COEFF14_MASK                0xFFFF0000UL                                 /**< Bit mask for FEFILT_SET1COEFF14             */
#define _FEFILT_CHFCOE16_SET1COEFF14_DEFAULT             0x00000000UL                                 /**< Mode DEFAULT for FEFILT_CHFCOE16            */
#define FEFILT_CHFCOE16_SET1COEFF14_DEFAULT              (_FEFILT_CHFCOE16_SET1COEFF14_DEFAULT << 16) /**< Shifted mode DEFAULT for FEFILT_CHFCOE16    */

/* Bit fields for FEFILT CHFCTRL */
#define _FEFILT_CHFCTRL_RESETVALUE                       0x00000000UL                                     /**< Default value for FEFILT_CHFCTRL            */
#define _FEFILT_CHFCTRL_MASK                             0xC000000FUL                                     /**< Mask for FEFILT_CHFCTRL                     */
#define FEFILT_CHFCTRL_FWSWCOEFFEN                       (0x1UL << 0)                                     /**< FW Switch CHF COE. Enable                   */
#define _FEFILT_CHFCTRL_FWSWCOEFFEN_SHIFT                0                                                /**< Shift value for FEFILT_FWSWCOEFFEN          */
#define _FEFILT_CHFCTRL_FWSWCOEFFEN_MASK                 0x1UL                                            /**< Bit mask for FEFILT_FWSWCOEFFEN             */
#define _FEFILT_CHFCTRL_FWSWCOEFFEN_DEFAULT              0x00000000UL                                     /**< Mode DEFAULT for FEFILT_CHFCTRL             */
#define FEFILT_CHFCTRL_FWSWCOEFFEN_DEFAULT               (_FEFILT_CHFCTRL_FWSWCOEFFEN_DEFAULT << 0)       /**< Shifted mode DEFAULT for FEFILT_CHFCTRL     */
#define FEFILT_CHFCTRL_FWSELCOEFF                        (0x1UL << 1)                                     /**< FW Select CHF COE. set                      */
#define _FEFILT_CHFCTRL_FWSELCOEFF_SHIFT                 1                                                /**< Shift value for FEFILT_FWSELCOEFF           */
#define _FEFILT_CHFCTRL_FWSELCOEFF_MASK                  0x2UL                                            /**< Bit mask for FEFILT_FWSELCOEFF              */
#define _FEFILT_CHFCTRL_FWSELCOEFF_DEFAULT               0x00000000UL                                     /**< Mode DEFAULT for FEFILT_CHFCTRL             */
#define FEFILT_CHFCTRL_FWSELCOEFF_DEFAULT                (_FEFILT_CHFCTRL_FWSELCOEFF_DEFAULT << 1)        /**< Shifted mode DEFAULT for FEFILT_CHFCTRL     */
#define _FEFILT_CHFCTRL_CHFLATENCY_SHIFT                 2                                                /**< Shift value for FEFILT_CHFLATENCY           */
#define _FEFILT_CHFCTRL_CHFLATENCY_MASK                  0xCUL                                            /**< Bit mask for FEFILT_CHFLATENCY              */
#define _FEFILT_CHFCTRL_CHFLATENCY_DEFAULT               0x00000000UL                                     /**< Mode DEFAULT for FEFILT_CHFCTRL             */
#define FEFILT_CHFCTRL_CHFLATENCY_DEFAULT                (_FEFILT_CHFCTRL_CHFLATENCY_DEFAULT << 2)        /**< Shifted mode DEFAULT for FEFILT_CHFCTRL     */
#define FEFILT_CHFCTRL_SWCOEFFSELECTION                  (0x1UL << 30)                                    /**< Switch CHF COE. Selection                   */
#define _FEFILT_CHFCTRL_SWCOEFFSELECTION_SHIFT           30                                               /**< Shift value for FEFILT_SWCOEFFSELECTION     */
#define _FEFILT_CHFCTRL_SWCOEFFSELECTION_MASK            0x40000000UL                                     /**< Bit mask for FEFILT_SWCOEFFSELECTION        */
#define _FEFILT_CHFCTRL_SWCOEFFSELECTION_DEFAULT         0x00000000UL                                     /**< Mode DEFAULT for FEFILT_CHFCTRL             */
#define FEFILT_CHFCTRL_SWCOEFFSELECTION_DEFAULT          (_FEFILT_CHFCTRL_SWCOEFFSELECTION_DEFAULT << 30) /**< Shifted mode DEFAULT for FEFILT_CHFCTRL     */
#define FEFILT_CHFCTRL_SWCOEFFEN                         (0x1UL << 31)                                    /**< Switch CHF COE. Enable                      */
#define _FEFILT_CHFCTRL_SWCOEFFEN_SHIFT                  31                                               /**< Shift value for FEFILT_SWCOEFFEN            */
#define _FEFILT_CHFCTRL_SWCOEFFEN_MASK                   0x80000000UL                                     /**< Bit mask for FEFILT_SWCOEFFEN               */
#define _FEFILT_CHFCTRL_SWCOEFFEN_DEFAULT                0x00000000UL                                     /**< Mode DEFAULT for FEFILT_CHFCTRL             */
#define FEFILT_CHFCTRL_SWCOEFFEN_DEFAULT                 (_FEFILT_CHFCTRL_SWCOEFFEN_DEFAULT << 31)        /**< Shifted mode DEFAULT for FEFILT_CHFCTRL     */

/* Bit fields for FEFILT CTRL */
#define _FEFILT_CTRL_RESETVALUE                          0x00000000UL                           /**< Default value for FEFILT_CTRL               */
#define _FEFILT_CTRL_MASK                                0x0007FFFFUL                           /**< Mask for FEFILT_CTRL                        */
#define _FEFILT_CTRL_SWAFCADJRX_SHIFT                    0                                      /**< Shift value for FEFILT_SWAFCADJRX           */
#define _FEFILT_CTRL_SWAFCADJRX_MASK                     0x7FFFFUL                              /**< Bit mask for FEFILT_SWAFCADJRX              */
#define _FEFILT_CTRL_SWAFCADJRX_DEFAULT                  0x00000000UL                           /**< Mode DEFAULT for FEFILT_CTRL                */
#define FEFILT_CTRL_SWAFCADJRX_DEFAULT                   (_FEFILT_CTRL_SWAFCADJRX_DEFAULT << 0) /**< Shifted mode DEFAULT for FEFILT_CTRL        */

/* Bit fields for FEFILT BLANKING */
#define _FEFILT_BLANKING_RESETVALUE                      0x00000000UL                                  /**< Default value for FEFILT_BLANKING           */
#define _FEFILT_BLANKING_MASK                            0x0007FFFFUL                                  /**< Mask for FEFILT_BLANKING                    */
#define _FEFILT_BLANKING_BLANKDELAY_SHIFT                0                                             /**< Shift value for FEFILT_BLANKDELAY           */
#define _FEFILT_BLANKING_BLANKDELAY_MASK                 0xFFUL                                        /**< Bit mask for FEFILT_BLANKDELAY              */
#define _FEFILT_BLANKING_BLANKDELAY_DEFAULT              0x00000000UL                                  /**< Mode DEFAULT for FEFILT_BLANKING            */
#define FEFILT_BLANKING_BLANKDELAY_DEFAULT               (_FEFILT_BLANKING_BLANKDELAY_DEFAULT << 0)    /**< Shifted mode DEFAULT for FEFILT_BLANKING    */
#define _FEFILT_BLANKING_BLANKDURATION_SHIFT             8                                             /**< Shift value for FEFILT_BLANKDURATION        */
#define _FEFILT_BLANKING_BLANKDURATION_MASK              0xFF00UL                                      /**< Bit mask for FEFILT_BLANKDURATION           */
#define _FEFILT_BLANKING_BLANKDURATION_DEFAULT           0x00000000UL                                  /**< Mode DEFAULT for FEFILT_BLANKING            */
#define FEFILT_BLANKING_BLANKDURATION_DEFAULT            (_FEFILT_BLANKING_BLANKDURATION_DEFAULT << 8) /**< Shifted mode DEFAULT for FEFILT_BLANKING    */
#define _FEFILT_BLANKING_BLANKMODE_SHIFT                 16                                            /**< Shift value for FEFILT_BLANKMODE            */
#define _FEFILT_BLANKING_BLANKMODE_MASK                  0x70000UL                                     /**< Bit mask for FEFILT_BLANKMODE               */
#define _FEFILT_BLANKING_BLANKMODE_DEFAULT               0x00000000UL                                  /**< Mode DEFAULT for FEFILT_BLANKING            */
#define _FEFILT_BLANKING_BLANKMODE_OFF                   0x00000000UL                                  /**< Mode OFF for FEFILT_BLANKING                */
#define _FEFILT_BLANKING_BLANKMODE_FORCE_IQ              0x00000001UL                                  /**< Mode FORCE_IQ for FEFILT_BLANKING           */
#define _FEFILT_BLANKING_BLANKMODE_FORCE_I               0x00000002UL                                  /**< Mode FORCE_I for FEFILT_BLANKING            */
#define _FEFILT_BLANKING_BLANKMODE_FORCE_Q               0x00000003UL                                  /**< Mode FORCE_Q for FEFILT_BLANKING            */
#define _FEFILT_BLANKING_BLANKMODE_AUTO                  0x00000004UL                                  /**< Mode AUTO for FEFILT_BLANKING               */
#define FEFILT_BLANKING_BLANKMODE_DEFAULT                (_FEFILT_BLANKING_BLANKMODE_DEFAULT << 16)    /**< Shifted mode DEFAULT for FEFILT_BLANKING    */
#define FEFILT_BLANKING_BLANKMODE_OFF                    (_FEFILT_BLANKING_BLANKMODE_OFF << 16)        /**< Shifted mode OFF for FEFILT_BLANKING        */
#define FEFILT_BLANKING_BLANKMODE_FORCE_IQ               (_FEFILT_BLANKING_BLANKMODE_FORCE_IQ << 16)   /**< Shifted mode FORCE_IQ for FEFILT_BLANKING   */
#define FEFILT_BLANKING_BLANKMODE_FORCE_I                (_FEFILT_BLANKING_BLANKMODE_FORCE_I << 16)    /**< Shifted mode FORCE_I for FEFILT_BLANKING    */
#define FEFILT_BLANKING_BLANKMODE_FORCE_Q                (_FEFILT_BLANKING_BLANKMODE_FORCE_Q << 16)    /**< Shifted mode FORCE_Q for FEFILT_BLANKING    */
#define FEFILT_BLANKING_BLANKMODE_AUTO                   (_FEFILT_BLANKING_BLANKMODE_AUTO << 16)       /**< Shifted mode AUTO for FEFILT_BLANKING       */

/* Bit fields for FEFILT RSSIFILT */
#define _FEFILT_RSSIFILT_RESETVALUE                      0x00000000UL                                   /**< Default value for FEFILT_RSSIFILT           */
#define _FEFILT_RSSIFILT_MASK                            0x001FFFFFUL                                   /**< Mask for FEFILT_RSSIFILT                    */
#define FEFILT_RSSIFILT_RSSIFILTEN                       (0x1UL << 0)                                   /**< New BitField                                */
#define _FEFILT_RSSIFILT_RSSIFILTEN_SHIFT                0                                              /**< Shift value for FEFILT_RSSIFILTEN           */
#define _FEFILT_RSSIFILT_RSSIFILTEN_MASK                 0x1UL                                          /**< Bit mask for FEFILT_RSSIFILTEN              */
#define _FEFILT_RSSIFILT_RSSIFILTEN_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for FEFILT_RSSIFILT            */
#define FEFILT_RSSIFILT_RSSIFILTEN_DEFAULT               (_FEFILT_RSSIFILT_RSSIFILTEN_DEFAULT << 0)     /**< Shifted mode DEFAULT for FEFILT_RSSIFILT    */
#define FEFILT_RSSIFILT_RSSIFILTDEC                      (0x1UL << 1)                                   /**< New BitField                                */
#define _FEFILT_RSSIFILT_RSSIFILTDEC_SHIFT               1                                              /**< Shift value for FEFILT_RSSIFILTDEC          */
#define _FEFILT_RSSIFILT_RSSIFILTDEC_MASK                0x2UL                                          /**< Bit mask for FEFILT_RSSIFILTDEC             */
#define _FEFILT_RSSIFILT_RSSIFILTDEC_DEFAULT             0x00000000UL                                   /**< Mode DEFAULT for FEFILT_RSSIFILT            */
#define FEFILT_RSSIFILT_RSSIFILTDEC_DEFAULT              (_FEFILT_RSSIFILT_RSSIFILTDEC_DEFAULT << 1)    /**< Shifted mode DEFAULT for FEFILT_RSSIFILT    */
#define _FEFILT_RSSIFILT_RSSIFILTGAIN_SHIFT              2                                              /**< Shift value for FEFILT_RSSIFILTGAIN         */
#define _FEFILT_RSSIFILT_RSSIFILTGAIN_MASK               0x1CUL                                         /**< Bit mask for FEFILT_RSSIFILTGAIN            */
#define _FEFILT_RSSIFILT_RSSIFILTGAIN_DEFAULT            0x00000000UL                                   /**< Mode DEFAULT for FEFILT_RSSIFILT            */
#define FEFILT_RSSIFILT_RSSIFILTGAIN_DEFAULT             (_FEFILT_RSSIFILT_RSSIFILTGAIN_DEFAULT << 2)   /**< Shifted mode DEFAULT for FEFILT_RSSIFILT    */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF0_SHIFT             5                                              /**< Shift value for FEFILT_RSSIFILTCOEF0        */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF0_MASK              0x60UL                                         /**< Bit mask for FEFILT_RSSIFILTCOEF0           */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF0_DEFAULT           0x00000000UL                                   /**< Mode DEFAULT for FEFILT_RSSIFILT            */
#define FEFILT_RSSIFILT_RSSIFILTCOEF0_DEFAULT            (_FEFILT_RSSIFILT_RSSIFILTCOEF0_DEFAULT << 5)  /**< Shifted mode DEFAULT for FEFILT_RSSIFILT    */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF1_SHIFT             7                                              /**< Shift value for FEFILT_RSSIFILTCOEF1        */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF1_MASK              0x180UL                                        /**< Bit mask for FEFILT_RSSIFILTCOEF1           */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF1_DEFAULT           0x00000000UL                                   /**< Mode DEFAULT for FEFILT_RSSIFILT            */
#define FEFILT_RSSIFILT_RSSIFILTCOEF1_DEFAULT            (_FEFILT_RSSIFILT_RSSIFILTCOEF1_DEFAULT << 7)  /**< Shifted mode DEFAULT for FEFILT_RSSIFILT    */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF2_SHIFT             9                                              /**< Shift value for FEFILT_RSSIFILTCOEF2        */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF2_MASK              0x600UL                                        /**< Bit mask for FEFILT_RSSIFILTCOEF2           */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF2_DEFAULT           0x00000000UL                                   /**< Mode DEFAULT for FEFILT_RSSIFILT            */
#define FEFILT_RSSIFILT_RSSIFILTCOEF2_DEFAULT            (_FEFILT_RSSIFILT_RSSIFILTCOEF2_DEFAULT << 9)  /**< Shifted mode DEFAULT for FEFILT_RSSIFILT    */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF3_SHIFT             11                                             /**< Shift value for FEFILT_RSSIFILTCOEF3        */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF3_MASK              0x1800UL                                       /**< Bit mask for FEFILT_RSSIFILTCOEF3           */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF3_DEFAULT           0x00000000UL                                   /**< Mode DEFAULT for FEFILT_RSSIFILT            */
#define FEFILT_RSSIFILT_RSSIFILTCOEF3_DEFAULT            (_FEFILT_RSSIFILT_RSSIFILTCOEF3_DEFAULT << 11) /**< Shifted mode DEFAULT for FEFILT_RSSIFILT    */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF4_SHIFT             13                                             /**< Shift value for FEFILT_RSSIFILTCOEF4        */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF4_MASK              0x6000UL                                       /**< Bit mask for FEFILT_RSSIFILTCOEF4           */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF4_DEFAULT           0x00000000UL                                   /**< Mode DEFAULT for FEFILT_RSSIFILT            */
#define FEFILT_RSSIFILT_RSSIFILTCOEF4_DEFAULT            (_FEFILT_RSSIFILT_RSSIFILTCOEF4_DEFAULT << 13) /**< Shifted mode DEFAULT for FEFILT_RSSIFILT    */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF5_SHIFT             15                                             /**< Shift value for FEFILT_RSSIFILTCOEF5        */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF5_MASK              0x18000UL                                      /**< Bit mask for FEFILT_RSSIFILTCOEF5           */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF5_DEFAULT           0x00000000UL                                   /**< Mode DEFAULT for FEFILT_RSSIFILT            */
#define FEFILT_RSSIFILT_RSSIFILTCOEF5_DEFAULT            (_FEFILT_RSSIFILT_RSSIFILTCOEF5_DEFAULT << 15) /**< Shifted mode DEFAULT for FEFILT_RSSIFILT    */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF6_SHIFT             17                                             /**< Shift value for FEFILT_RSSIFILTCOEF6        */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF6_MASK              0x60000UL                                      /**< Bit mask for FEFILT_RSSIFILTCOEF6           */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF6_DEFAULT           0x00000000UL                                   /**< Mode DEFAULT for FEFILT_RSSIFILT            */
#define FEFILT_RSSIFILT_RSSIFILTCOEF6_DEFAULT            (_FEFILT_RSSIFILT_RSSIFILTCOEF6_DEFAULT << 17) /**< Shifted mode DEFAULT for FEFILT_RSSIFILT    */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF7_SHIFT             19                                             /**< Shift value for FEFILT_RSSIFILTCOEF7        */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF7_MASK              0x180000UL                                     /**< Bit mask for FEFILT_RSSIFILTCOEF7           */
#define _FEFILT_RSSIFILT_RSSIFILTCOEF7_DEFAULT           0x00000000UL                                   /**< Mode DEFAULT for FEFILT_RSSIFILT            */
#define FEFILT_RSSIFILT_RSSIFILTCOEF7_DEFAULT            (_FEFILT_RSSIFILT_RSSIFILTCOEF7_DEFAULT << 19) /**< Shifted mode DEFAULT for FEFILT_RSSIFILT    */

/* Bit fields for FEFILT DIGMIXCTRL */
#define _FEFILT_DIGMIXCTRL_RESETVALUE                    0x00000000UL                                      /**< Default value for FEFILT_DIGMIXCTRL         */
#define _FEFILT_DIGMIXCTRL_MASK                          0x007FFFFFUL                                      /**< Mask for FEFILT_DIGMIXCTRL                  */
#define _FEFILT_DIGMIXCTRL_DIGMIXFREQ_SHIFT              0                                                 /**< Shift value for FEFILT_DIGMIXFREQ           */
#define _FEFILT_DIGMIXCTRL_DIGMIXFREQ_MASK               0xFFFFFUL                                         /**< Bit mask for FEFILT_DIGMIXFREQ              */
#define _FEFILT_DIGMIXCTRL_DIGMIXFREQ_DEFAULT            0x00000000UL                                      /**< Mode DEFAULT for FEFILT_DIGMIXCTRL          */
#define FEFILT_DIGMIXCTRL_DIGMIXFREQ_DEFAULT             (_FEFILT_DIGMIXCTRL_DIGMIXFREQ_DEFAULT << 0)      /**< Shifted mode DEFAULT for FEFILT_DIGMIXCTRL  */
#define FEFILT_DIGMIXCTRL_DIGIQSWAPEN                    (0x1UL << 20)                                     /**< Digital I/Q swap enable                     */
#define _FEFILT_DIGMIXCTRL_DIGIQSWAPEN_SHIFT             20                                                /**< Shift value for FEFILT_DIGIQSWAPEN          */
#define _FEFILT_DIGMIXCTRL_DIGIQSWAPEN_MASK              0x100000UL                                        /**< Bit mask for FEFILT_DIGIQSWAPEN             */
#define _FEFILT_DIGMIXCTRL_DIGIQSWAPEN_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for FEFILT_DIGMIXCTRL          */
#define FEFILT_DIGMIXCTRL_DIGIQSWAPEN_DEFAULT            (_FEFILT_DIGMIXCTRL_DIGIQSWAPEN_DEFAULT << 20)    /**< Shifted mode DEFAULT for FEFILT_DIGMIXCTRL  */
#define FEFILT_DIGMIXCTRL_MIXERCONJ                      (0x1UL << 21)                                     /**< Digital mixer input conjugate               */
#define _FEFILT_DIGMIXCTRL_MIXERCONJ_SHIFT               21                                                /**< Shift value for FEFILT_MIXERCONJ            */
#define _FEFILT_DIGMIXCTRL_MIXERCONJ_MASK                0x200000UL                                        /**< Bit mask for FEFILT_MIXERCONJ               */
#define _FEFILT_DIGMIXCTRL_MIXERCONJ_DEFAULT             0x00000000UL                                      /**< Mode DEFAULT for FEFILT_DIGMIXCTRL          */
#define FEFILT_DIGMIXCTRL_MIXERCONJ_DEFAULT              (_FEFILT_DIGMIXCTRL_MIXERCONJ_DEFAULT << 21)      /**< Shifted mode DEFAULT for FEFILT_DIGMIXCTRL  */
#define FEFILT_DIGMIXCTRL_DIGMIXFBENABLE                 (0x1UL << 22)                                     /**< Digital mixer Frequency Correction          */
#define _FEFILT_DIGMIXCTRL_DIGMIXFBENABLE_SHIFT          22                                                /**< Shift value for FEFILT_DIGMIXFBENABLE       */
#define _FEFILT_DIGMIXCTRL_DIGMIXFBENABLE_MASK           0x400000UL                                        /**< Bit mask for FEFILT_DIGMIXFBENABLE          */
#define _FEFILT_DIGMIXCTRL_DIGMIXFBENABLE_DEFAULT        0x00000000UL                                      /**< Mode DEFAULT for FEFILT_DIGMIXCTRL          */
#define FEFILT_DIGMIXCTRL_DIGMIXFBENABLE_DEFAULT         (_FEFILT_DIGMIXCTRL_DIGMIXFBENABLE_DEFAULT << 22) /**< Shifted mode DEFAULT for FEFILT_DIGMIXCTRL  */

/* Bit fields for FEFILT DCCOMP */
#define _FEFILT_DCCOMP_RESETVALUE                        0x00000030UL                                     /**< Default value for FEFILT_DCCOMP             */
#define _FEFILT_DCCOMP_MASK                              0x01FFFFFFUL                                     /**< Mask for FEFILT_DCCOMP                      */
#define FEFILT_DCCOMP_DCESTIEN                           (0x1UL << 0)                                     /**< DC Offset Estimation Enable                 */
#define _FEFILT_DCCOMP_DCESTIEN_SHIFT                    0                                                /**< Shift value for FEFILT_DCESTIEN             */
#define _FEFILT_DCCOMP_DCESTIEN_MASK                     0x1UL                                            /**< Bit mask for FEFILT_DCESTIEN                */
#define _FEFILT_DCCOMP_DCESTIEN_DEFAULT                  0x00000000UL                                     /**< Mode DEFAULT for FEFILT_DCCOMP              */
#define FEFILT_DCCOMP_DCESTIEN_DEFAULT                   (_FEFILT_DCCOMP_DCESTIEN_DEFAULT << 0)           /**< Shifted mode DEFAULT for FEFILT_DCCOMP      */
#define FEFILT_DCCOMP_DCCOMPEN                           (0x1UL << 1)                                     /**< DC Offset Compensation Enable               */
#define _FEFILT_DCCOMP_DCCOMPEN_SHIFT                    1                                                /**< Shift value for FEFILT_DCCOMPEN             */
#define _FEFILT_DCCOMP_DCCOMPEN_MASK                     0x2UL                                            /**< Bit mask for FEFILT_DCCOMPEN                */
#define _FEFILT_DCCOMP_DCCOMPEN_DEFAULT                  0x00000000UL                                     /**< Mode DEFAULT for FEFILT_DCCOMP              */
#define FEFILT_DCCOMP_DCCOMPEN_DEFAULT                   (_FEFILT_DCCOMP_DCCOMPEN_DEFAULT << 1)           /**< Shifted mode DEFAULT for FEFILT_DCCOMP      */
#define FEFILT_DCCOMP_DCRSTEN                            (0x1UL << 2)                                     /**< DC Compensation Filter Reset Enable         */
#define _FEFILT_DCCOMP_DCRSTEN_SHIFT                     2                                                /**< Shift value for FEFILT_DCRSTEN              */
#define _FEFILT_DCCOMP_DCRSTEN_MASK                      0x4UL                                            /**< Bit mask for FEFILT_DCRSTEN                 */
#define _FEFILT_DCCOMP_DCRSTEN_DEFAULT                   0x00000000UL                                     /**< Mode DEFAULT for FEFILT_DCCOMP              */
#define FEFILT_DCCOMP_DCRSTEN_DEFAULT                    (_FEFILT_DCCOMP_DCRSTEN_DEFAULT << 2)            /**< Shifted mode DEFAULT for FEFILT_DCCOMP      */
#define FEFILT_DCCOMP_DCCOMPFREEZE                       (0x1UL << 3)                                     /**< DC Offset Compensation Filter Freeze        */
#define _FEFILT_DCCOMP_DCCOMPFREEZE_SHIFT                3                                                /**< Shift value for FEFILT_DCCOMPFREEZE         */
#define _FEFILT_DCCOMP_DCCOMPFREEZE_MASK                 0x8UL                                            /**< Bit mask for FEFILT_DCCOMPFREEZE            */
#define _FEFILT_DCCOMP_DCCOMPFREEZE_DEFAULT              0x00000000UL                                     /**< Mode DEFAULT for FEFILT_DCCOMP              */
#define FEFILT_DCCOMP_DCCOMPFREEZE_DEFAULT               (_FEFILT_DCCOMP_DCCOMPFREEZE_DEFAULT << 3)       /**< Shifted mode DEFAULT for FEFILT_DCCOMP      */
#define _FEFILT_DCCOMP_DCCOMPGEAR_SHIFT                  4                                                /**< Shift value for FEFILT_DCCOMPGEAR           */
#define _FEFILT_DCCOMP_DCCOMPGEAR_MASK                   0xF0UL                                           /**< Bit mask for FEFILT_DCCOMPGEAR              */
#define _FEFILT_DCCOMP_DCCOMPGEAR_DEFAULT                0x00000003UL                                     /**< Mode DEFAULT for FEFILT_DCCOMP              */
#define FEFILT_DCCOMP_DCCOMPGEAR_DEFAULT                 (_FEFILT_DCCOMP_DCCOMPGEAR_DEFAULT << 4)         /**< Shifted mode DEFAULT for FEFILT_DCCOMP      */
#define _FEFILT_DCCOMP_DCLIMIT_SHIFT                     8                                                /**< Shift value for FEFILT_DCLIMIT              */
#define _FEFILT_DCCOMP_DCLIMIT_MASK                      0x300UL                                          /**< Bit mask for FEFILT_DCLIMIT                 */
#define _FEFILT_DCCOMP_DCLIMIT_DEFAULT                   0x00000000UL                                     /**< Mode DEFAULT for FEFILT_DCCOMP              */
#define _FEFILT_DCCOMP_DCLIMIT_FULLSCALE                 0x00000000UL                                     /**< Mode FULLSCALE for FEFILT_DCCOMP            */
#define _FEFILT_DCCOMP_DCLIMIT_FULLSCALEBY4              0x00000001UL                                     /**< Mode FULLSCALEBY4 for FEFILT_DCCOMP         */
#define _FEFILT_DCCOMP_DCLIMIT_FULLSCALEBY8              0x00000002UL                                     /**< Mode FULLSCALEBY8 for FEFILT_DCCOMP         */
#define _FEFILT_DCCOMP_DCLIMIT_FULLSCALEBY16             0x00000003UL                                     /**< Mode FULLSCALEBY16 for FEFILT_DCCOMP        */
#define FEFILT_DCCOMP_DCLIMIT_DEFAULT                    (_FEFILT_DCCOMP_DCLIMIT_DEFAULT << 8)            /**< Shifted mode DEFAULT for FEFILT_DCCOMP      */
#define FEFILT_DCCOMP_DCLIMIT_FULLSCALE                  (_FEFILT_DCCOMP_DCLIMIT_FULLSCALE << 8)          /**< Shifted mode FULLSCALE for FEFILT_DCCOMP    */
#define FEFILT_DCCOMP_DCLIMIT_FULLSCALEBY4               (_FEFILT_DCCOMP_DCLIMIT_FULLSCALEBY4 << 8)       /**< Shifted mode FULLSCALEBY4 for FEFILT_DCCOMP */
#define FEFILT_DCCOMP_DCLIMIT_FULLSCALEBY8               (_FEFILT_DCCOMP_DCLIMIT_FULLSCALEBY8 << 8)       /**< Shifted mode FULLSCALEBY8 for FEFILT_DCCOMP */
#define FEFILT_DCCOMP_DCLIMIT_FULLSCALEBY16              (_FEFILT_DCCOMP_DCLIMIT_FULLSCALEBY16 << 8)      /**< Shifted mode FULLSCALEBY16 for FEFILT_DCCOMP*/
#define FEFILT_DCCOMP_DCGAINGEAREN                       (0x1UL << 10)                                    /**< DC Offset Gain Change Filter Gear Enable    */
#define _FEFILT_DCCOMP_DCGAINGEAREN_SHIFT                10                                               /**< Shift value for FEFILT_DCGAINGEAREN         */
#define _FEFILT_DCCOMP_DCGAINGEAREN_MASK                 0x400UL                                          /**< Bit mask for FEFILT_DCGAINGEAREN            */
#define _FEFILT_DCCOMP_DCGAINGEAREN_DEFAULT              0x00000000UL                                     /**< Mode DEFAULT for FEFILT_DCCOMP              */
#define FEFILT_DCCOMP_DCGAINGEAREN_DEFAULT               (_FEFILT_DCCOMP_DCGAINGEAREN_DEFAULT << 10)      /**< Shifted mode DEFAULT for FEFILT_DCCOMP      */
#define _FEFILT_DCCOMP_DCGAINGEAR_SHIFT                  11                                               /**< Shift value for FEFILT_DCGAINGEAR           */
#define _FEFILT_DCCOMP_DCGAINGEAR_MASK                   0x7800UL                                         /**< Bit mask for FEFILT_DCGAINGEAR              */
#define _FEFILT_DCCOMP_DCGAINGEAR_DEFAULT                0x00000000UL                                     /**< Mode DEFAULT for FEFILT_DCCOMP              */
#define FEFILT_DCCOMP_DCGAINGEAR_DEFAULT                 (_FEFILT_DCCOMP_DCGAINGEAR_DEFAULT << 11)        /**< Shifted mode DEFAULT for FEFILT_DCCOMP      */
#define _FEFILT_DCCOMP_DCGAINGEARSMPS_SHIFT              15                                               /**< Shift value for FEFILT_DCGAINGEARSMPS       */
#define _FEFILT_DCCOMP_DCGAINGEARSMPS_MASK               0x7F8000UL                                       /**< Bit mask for FEFILT_DCGAINGEARSMPS          */
#define _FEFILT_DCCOMP_DCGAINGEARSMPS_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for FEFILT_DCCOMP              */
#define FEFILT_DCCOMP_DCGAINGEARSMPS_DEFAULT             (_FEFILT_DCCOMP_DCGAINGEARSMPS_DEFAULT << 15)    /**< Shifted mode DEFAULT for FEFILT_DCCOMP      */
#define FEFILT_DCCOMP_GEARGAINCHANGESEL                  (0x1UL << 23)                                    /**< DC Offset Gain Change Request Selection     */
#define _FEFILT_DCCOMP_GEARGAINCHANGESEL_SHIFT           23                                               /**< Shift value for FEFILT_GEARGAINCHANGESEL    */
#define _FEFILT_DCCOMP_GEARGAINCHANGESEL_MASK            0x800000UL                                       /**< Bit mask for FEFILT_GEARGAINCHANGESEL       */
#define _FEFILT_DCCOMP_GEARGAINCHANGESEL_DEFAULT         0x00000000UL                                     /**< Mode DEFAULT for FEFILT_DCCOMP              */
#define _FEFILT_DCCOMP_GEARGAINCHANGESEL_AGC             0x00000000UL                                     /**< Mode AGC for FEFILT_DCCOMP                  */
#define _FEFILT_DCCOMP_GEARGAINCHANGESEL_SW              0x00000001UL                                     /**< Mode SW for FEFILT_DCCOMP                   */
#define FEFILT_DCCOMP_GEARGAINCHANGESEL_DEFAULT          (_FEFILT_DCCOMP_GEARGAINCHANGESEL_DEFAULT << 23) /**< Shifted mode DEFAULT for FEFILT_DCCOMP      */
#define FEFILT_DCCOMP_GEARGAINCHANGESEL_AGC              (_FEFILT_DCCOMP_GEARGAINCHANGESEL_AGC << 23)     /**< Shifted mode AGC for FEFILT_DCCOMP          */
#define FEFILT_DCCOMP_GEARGAINCHANGESEL_SW               (_FEFILT_DCCOMP_GEARGAINCHANGESEL_SW << 23)      /**< Shifted mode SW for FEFILT_DCCOMP           */
#define FEFILT_DCCOMP_GEARFREEZEENABLE                   (0x1UL << 24)                                    /**< DC Offset freeze enable for DC Gear         */
#define _FEFILT_DCCOMP_GEARFREEZEENABLE_SHIFT            24                                               /**< Shift value for FEFILT_GEARFREEZEENABLE     */
#define _FEFILT_DCCOMP_GEARFREEZEENABLE_MASK             0x1000000UL                                      /**< Bit mask for FEFILT_GEARFREEZEENABLE        */
#define _FEFILT_DCCOMP_GEARFREEZEENABLE_DEFAULT          0x00000000UL                                     /**< Mode DEFAULT for FEFILT_DCCOMP              */
#define _FEFILT_DCCOMP_GEARFREEZEENABLE_DISABLE          0x00000000UL                                     /**< Mode DISABLE for FEFILT_DCCOMP              */
#define _FEFILT_DCCOMP_GEARFREEZEENABLE_ENABLE           0x00000001UL                                     /**< Mode ENABLE for FEFILT_DCCOMP               */
#define FEFILT_DCCOMP_GEARFREEZEENABLE_DEFAULT           (_FEFILT_DCCOMP_GEARFREEZEENABLE_DEFAULT << 24)  /**< Shifted mode DEFAULT for FEFILT_DCCOMP      */
#define FEFILT_DCCOMP_GEARFREEZEENABLE_DISABLE           (_FEFILT_DCCOMP_GEARFREEZEENABLE_DISABLE << 24)  /**< Shifted mode DISABLE for FEFILT_DCCOMP      */
#define FEFILT_DCCOMP_GEARFREEZEENABLE_ENABLE            (_FEFILT_DCCOMP_GEARFREEZEENABLE_ENABLE << 24)   /**< Shifted mode ENABLE for FEFILT_DCCOMP       */

/* Bit fields for FEFILT DCCOMPFILTINIT */
#define _FEFILT_DCCOMPFILTINIT_RESETVALUE                0x00000000UL                                          /**< Default value for FEFILT_DCCOMPFILTINIT     */
#define _FEFILT_DCCOMPFILTINIT_MASK                      0x7FFFFFFFUL                                          /**< Mask for FEFILT_DCCOMPFILTINIT              */
#define _FEFILT_DCCOMPFILTINIT_DCCOMPINITVALI_SHIFT      0                                                     /**< Shift value for FEFILT_DCCOMPINITVALI       */
#define _FEFILT_DCCOMPFILTINIT_DCCOMPINITVALI_MASK       0x7FFFUL                                              /**< Bit mask for FEFILT_DCCOMPINITVALI          */
#define _FEFILT_DCCOMPFILTINIT_DCCOMPINITVALI_DEFAULT    0x00000000UL                                          /**< Mode DEFAULT for FEFILT_DCCOMPFILTINIT      */
#define FEFILT_DCCOMPFILTINIT_DCCOMPINITVALI_DEFAULT     (_FEFILT_DCCOMPFILTINIT_DCCOMPINITVALI_DEFAULT << 0)  /**< Shifted mode DEFAULT for FEFILT_DCCOMPFILTINIT*/
#define _FEFILT_DCCOMPFILTINIT_DCCOMPINITVALQ_SHIFT      15                                                    /**< Shift value for FEFILT_DCCOMPINITVALQ       */
#define _FEFILT_DCCOMPFILTINIT_DCCOMPINITVALQ_MASK       0x3FFF8000UL                                          /**< Bit mask for FEFILT_DCCOMPINITVALQ          */
#define _FEFILT_DCCOMPFILTINIT_DCCOMPINITVALQ_DEFAULT    0x00000000UL                                          /**< Mode DEFAULT for FEFILT_DCCOMPFILTINIT      */
#define FEFILT_DCCOMPFILTINIT_DCCOMPINITVALQ_DEFAULT     (_FEFILT_DCCOMPFILTINIT_DCCOMPINITVALQ_DEFAULT << 15) /**< Shifted mode DEFAULT for FEFILT_DCCOMPFILTINIT*/
#define FEFILT_DCCOMPFILTINIT_DCCOMPINIT                 (0x1UL << 30)                                         /**< Initialize filter state                     */
#define _FEFILT_DCCOMPFILTINIT_DCCOMPINIT_SHIFT          30                                                    /**< Shift value for FEFILT_DCCOMPINIT           */
#define _FEFILT_DCCOMPFILTINIT_DCCOMPINIT_MASK           0x40000000UL                                          /**< Bit mask for FEFILT_DCCOMPINIT              */
#define _FEFILT_DCCOMPFILTINIT_DCCOMPINIT_DEFAULT        0x00000000UL                                          /**< Mode DEFAULT for FEFILT_DCCOMPFILTINIT      */
#define FEFILT_DCCOMPFILTINIT_DCCOMPINIT_DEFAULT         (_FEFILT_DCCOMPFILTINIT_DCCOMPINIT_DEFAULT << 30)     /**< Shifted mode DEFAULT for FEFILT_DCCOMPFILTINIT*/

/* Bit fields for FEFILT DCESTI */
#define _FEFILT_DCESTI_RESETVALUE                        0x00000000UL                                  /**< Default value for FEFILT_DCESTI             */
#define _FEFILT_DCESTI_MASK                              0x3FFFFFFFUL                                  /**< Mask for FEFILT_DCESTI                      */
#define _FEFILT_DCESTI_DCCOMPESTIVALI_SHIFT              0                                             /**< Shift value for FEFILT_DCCOMPESTIVALI       */
#define _FEFILT_DCESTI_DCCOMPESTIVALI_MASK               0x7FFFUL                                      /**< Bit mask for FEFILT_DCCOMPESTIVALI          */
#define _FEFILT_DCESTI_DCCOMPESTIVALI_DEFAULT            0x00000000UL                                  /**< Mode DEFAULT for FEFILT_DCESTI              */
#define FEFILT_DCESTI_DCCOMPESTIVALI_DEFAULT             (_FEFILT_DCESTI_DCCOMPESTIVALI_DEFAULT << 0)  /**< Shifted mode DEFAULT for FEFILT_DCESTI      */
#define _FEFILT_DCESTI_DCCOMPESTIVALQ_SHIFT              15                                            /**< Shift value for FEFILT_DCCOMPESTIVALQ       */
#define _FEFILT_DCESTI_DCCOMPESTIVALQ_MASK               0x3FFF8000UL                                  /**< Bit mask for FEFILT_DCCOMPESTIVALQ          */
#define _FEFILT_DCESTI_DCCOMPESTIVALQ_DEFAULT            0x00000000UL                                  /**< Mode DEFAULT for FEFILT_DCESTI              */
#define FEFILT_DCESTI_DCCOMPESTIVALQ_DEFAULT             (_FEFILT_DCESTI_DCCOMPESTIVALQ_DEFAULT << 15) /**< Shifted mode DEFAULT for FEFILT_DCESTI      */

/* Bit fields for FEFILT IRCAL */
#define _FEFILT_IRCAL_RESETVALUE                         0x00000000UL                                  /**< Default value for FEFILT_IRCAL              */
#define _FEFILT_IRCAL_MASK                               0x0000FFBFUL                                  /**< Mask for FEFILT_IRCAL                       */
#define FEFILT_IRCAL_IRCALEN                             (0x1UL << 0)                                  /**< IRCAL enable bit                            */
#define _FEFILT_IRCAL_IRCALEN_SHIFT                      0                                             /**< Shift value for FEFILT_IRCALEN              */
#define _FEFILT_IRCAL_IRCALEN_MASK                       0x1UL                                         /**< Bit mask for FEFILT_IRCALEN                 */
#define _FEFILT_IRCAL_IRCALEN_DEFAULT                    0x00000000UL                                  /**< Mode DEFAULT for FEFILT_IRCAL               */
#define FEFILT_IRCAL_IRCALEN_DEFAULT                     (_FEFILT_IRCAL_IRCALEN_DEFAULT << 0)          /**< Shifted mode DEFAULT for FEFILT_IRCAL       */
#define _FEFILT_IRCAL_MURSHF_SHIFT                       1                                             /**< Shift value for FEFILT_MURSHF               */
#define _FEFILT_IRCAL_MURSHF_MASK                        0x3EUL                                        /**< Bit mask for FEFILT_MURSHF                  */
#define _FEFILT_IRCAL_MURSHF_DEFAULT                     0x00000000UL                                  /**< Mode DEFAULT for FEFILT_IRCAL               */
#define FEFILT_IRCAL_MURSHF_DEFAULT                      (_FEFILT_IRCAL_MURSHF_DEFAULT << 1)           /**< Shifted mode DEFAULT for FEFILT_IRCAL       */
#define _FEFILT_IRCAL_MUISHF_SHIFT                       7                                             /**< Shift value for FEFILT_MUISHF               */
#define _FEFILT_IRCAL_MUISHF_MASK                        0x1F80UL                                      /**< Bit mask for FEFILT_MUISHF                  */
#define _FEFILT_IRCAL_MUISHF_DEFAULT                     0x00000000UL                                  /**< Mode DEFAULT for FEFILT_IRCAL               */
#define FEFILT_IRCAL_MUISHF_DEFAULT                      (_FEFILT_IRCAL_MUISHF_DEFAULT << 7)           /**< Shifted mode DEFAULT for FEFILT_IRCAL       */
#define FEFILT_IRCAL_IRCORREN                            (0x1UL << 13)                                 /**< IR Correction enable bit                    */
#define _FEFILT_IRCAL_IRCORREN_SHIFT                     13                                            /**< Shift value for FEFILT_IRCORREN             */
#define _FEFILT_IRCAL_IRCORREN_MASK                      0x2000UL                                      /**< Bit mask for FEFILT_IRCORREN                */
#define _FEFILT_IRCAL_IRCORREN_DEFAULT                   0x00000000UL                                  /**< Mode DEFAULT for FEFILT_IRCAL               */
#define FEFILT_IRCAL_IRCORREN_DEFAULT                    (_FEFILT_IRCAL_IRCORREN_DEFAULT << 13)        /**< Shifted mode DEFAULT for FEFILT_IRCAL       */
#define FEFILT_IRCAL_IRCALCOEFRSTCMD                     (0x1UL << 14)                                 /**< IRCAL coef reset cmd                        */
#define _FEFILT_IRCAL_IRCALCOEFRSTCMD_SHIFT              14                                            /**< Shift value for FEFILT_IRCALCOEFRSTCMD      */
#define _FEFILT_IRCAL_IRCALCOEFRSTCMD_MASK               0x4000UL                                      /**< Bit mask for FEFILT_IRCALCOEFRSTCMD         */
#define _FEFILT_IRCAL_IRCALCOEFRSTCMD_DEFAULT            0x00000000UL                                  /**< Mode DEFAULT for FEFILT_IRCAL               */
#define FEFILT_IRCAL_IRCALCOEFRSTCMD_DEFAULT             (_FEFILT_IRCAL_IRCALCOEFRSTCMD_DEFAULT << 14) /**< Shifted mode DEFAULT for FEFILT_IRCAL       */
#define FEFILT_IRCAL_IRCALIFADCDBG                       (0x1UL << 15)                                 /**< IRCAL IFADC DBG                             */
#define _FEFILT_IRCAL_IRCALIFADCDBG_SHIFT                15                                            /**< Shift value for FEFILT_IRCALIFADCDBG        */
#define _FEFILT_IRCAL_IRCALIFADCDBG_MASK                 0x8000UL                                      /**< Bit mask for FEFILT_IRCALIFADCDBG           */
#define _FEFILT_IRCAL_IRCALIFADCDBG_DEFAULT              0x00000000UL                                  /**< Mode DEFAULT for FEFILT_IRCAL               */
#define FEFILT_IRCAL_IRCALIFADCDBG_DEFAULT               (_FEFILT_IRCAL_IRCALIFADCDBG_DEFAULT << 15)   /**< Shifted mode DEFAULT for FEFILT_IRCAL       */

/* Bit fields for FEFILT IRCALCOEF */
#define _FEFILT_IRCALCOEF_RESETVALUE                     0x00000000UL                          /**< Default value for FEFILT_IRCALCOEF          */
#define _FEFILT_IRCALCOEF_MASK                           0x7FFF7FFFUL                          /**< Mask for FEFILT_IRCALCOEF                   */
#define _FEFILT_IRCALCOEF_CRV_SHIFT                      0                                     /**< Shift value for FEFILT_CRV                  */
#define _FEFILT_IRCALCOEF_CRV_MASK                       0x7FFFUL                              /**< Bit mask for FEFILT_CRV                     */
#define _FEFILT_IRCALCOEF_CRV_DEFAULT                    0x00000000UL                          /**< Mode DEFAULT for FEFILT_IRCALCOEF           */
#define FEFILT_IRCALCOEF_CRV_DEFAULT                     (_FEFILT_IRCALCOEF_CRV_DEFAULT << 0)  /**< Shifted mode DEFAULT for FEFILT_IRCALCOEF   */
#define _FEFILT_IRCALCOEF_CIV_SHIFT                      16                                    /**< Shift value for FEFILT_CIV                  */
#define _FEFILT_IRCALCOEF_CIV_MASK                       0x7FFF0000UL                          /**< Bit mask for FEFILT_CIV                     */
#define _FEFILT_IRCALCOEF_CIV_DEFAULT                    0x00000000UL                          /**< Mode DEFAULT for FEFILT_IRCALCOEF           */
#define FEFILT_IRCALCOEF_CIV_DEFAULT                     (_FEFILT_IRCALCOEF_CIV_DEFAULT << 16) /**< Shifted mode DEFAULT for FEFILT_IRCALCOEF   */

/* Bit fields for FEFILT IRCALCOEFWR */
#define _FEFILT_IRCALCOEFWR_RESETVALUE                   0x00000000UL                               /**< Default value for FEFILT_IRCALCOEFWR        */
#define _FEFILT_IRCALCOEFWR_MASK                         0xFFFFFFFFUL                               /**< Mask for FEFILT_IRCALCOEFWR                 */
#define _FEFILT_IRCALCOEFWR_CRVWD_SHIFT                  0                                          /**< Shift value for FEFILT_CRVWD                */
#define _FEFILT_IRCALCOEFWR_CRVWD_MASK                   0x7FFFUL                                   /**< Bit mask for FEFILT_CRVWD                   */
#define _FEFILT_IRCALCOEFWR_CRVWD_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for FEFILT_IRCALCOEFWR         */
#define FEFILT_IRCALCOEFWR_CRVWD_DEFAULT                 (_FEFILT_IRCALCOEFWR_CRVWD_DEFAULT << 0)   /**< Shifted mode DEFAULT for FEFILT_IRCALCOEFWR */
#define FEFILT_IRCALCOEFWR_CRVWEN                        (0x1UL << 15)                              /**< CIV Coefficient Write Enable                */
#define _FEFILT_IRCALCOEFWR_CRVWEN_SHIFT                 15                                         /**< Shift value for FEFILT_CRVWEN               */
#define _FEFILT_IRCALCOEFWR_CRVWEN_MASK                  0x8000UL                                   /**< Bit mask for FEFILT_CRVWEN                  */
#define _FEFILT_IRCALCOEFWR_CRVWEN_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for FEFILT_IRCALCOEFWR         */
#define FEFILT_IRCALCOEFWR_CRVWEN_DEFAULT                (_FEFILT_IRCALCOEFWR_CRVWEN_DEFAULT << 15) /**< Shifted mode DEFAULT for FEFILT_IRCALCOEFWR */
#define _FEFILT_IRCALCOEFWR_CIVWD_SHIFT                  16                                         /**< Shift value for FEFILT_CIVWD                */
#define _FEFILT_IRCALCOEFWR_CIVWD_MASK                   0x7FFF0000UL                               /**< Bit mask for FEFILT_CIVWD                   */
#define _FEFILT_IRCALCOEFWR_CIVWD_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for FEFILT_IRCALCOEFWR         */
#define FEFILT_IRCALCOEFWR_CIVWD_DEFAULT                 (_FEFILT_IRCALCOEFWR_CIVWD_DEFAULT << 16)  /**< Shifted mode DEFAULT for FEFILT_IRCALCOEFWR */
#define FEFILT_IRCALCOEFWR_CIVWEN                        (0x1UL << 31)                              /**< CIV Coefficient Write Enable                */
#define _FEFILT_IRCALCOEFWR_CIVWEN_SHIFT                 31                                         /**< Shift value for FEFILT_CIVWEN               */
#define _FEFILT_IRCALCOEFWR_CIVWEN_MASK                  0x80000000UL                               /**< Bit mask for FEFILT_CIVWEN                  */
#define _FEFILT_IRCALCOEFWR_CIVWEN_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for FEFILT_IRCALCOEFWR         */
#define FEFILT_IRCALCOEFWR_CIVWEN_DEFAULT                (_FEFILT_IRCALCOEFWR_CIVWEN_DEFAULT << 31) /**< Shifted mode DEFAULT for FEFILT_IRCALCOEFWR */

/** @} End of group EFR32FG25_FEFILT_BitFields */
/** @} End of group EFR32FG25_FEFILT */
/** @} End of group Parts */

#endif /* EFR32FG25_FEFILT_H */
