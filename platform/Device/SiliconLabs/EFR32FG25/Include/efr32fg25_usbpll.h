/**************************************************************************//**
 * @file
 * @brief EFR32FG25 USBPLL register and bit field definitions
 ******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories, Inc. www.silabs.com</b>
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
#ifndef EFR32FG25_USBPLL_H
#define EFR32FG25_USBPLL_H
#define USBPLL_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_USBPLL USBPLL
 * @{
 * @brief EFR32FG25 USBPLL Register Declaration.
 *****************************************************************************/

/** USBPLL Register Declaration. */
typedef struct {
  __IM uint32_t  IPVERSION;                     /**< IP version ID                                      */
  uint32_t       RESERVED0[2U];                 /**< Reserved for future use                            */
  __IOM uint32_t CTRL;                          /**< Control                                            */
  __IM uint32_t  STATUS;                        /**< Status                                             */
  uint32_t       RESERVED1[2U];                 /**< Reserved for future use                            */
  __IOM uint32_t DCOCTRL;                       /**< DAC oscillator Control                             */
  uint32_t       RESERVED2[4U];                 /**< Reserved for future use                            */
  __IOM uint32_t LOCK;                          /**< Lock PLL                                           */
  __IOM uint32_t IF;                            /**< Interrupt Flag Register                            */
  __IOM uint32_t IEN;                           /**< Interrupt Enable Register                          */
  uint32_t       RESERVED3[1009U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP version ID                                      */
  uint32_t       RESERVED4[2U];                 /**< Reserved for future use                            */
  __IOM uint32_t CTRL_SET;                      /**< Control                                            */
  __IM uint32_t  STATUS_SET;                    /**< Status                                             */
  uint32_t       RESERVED5[2U];                 /**< Reserved for future use                            */
  __IOM uint32_t DCOCTRL_SET;                   /**< DAC oscillator Control                             */
  uint32_t       RESERVED6[4U];                 /**< Reserved for future use                            */
  __IOM uint32_t LOCK_SET;                      /**< Lock PLL                                           */
  __IOM uint32_t IF_SET;                        /**< Interrupt Flag Register                            */
  __IOM uint32_t IEN_SET;                       /**< Interrupt Enable Register                          */
  uint32_t       RESERVED7[1009U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP version ID                                      */
  uint32_t       RESERVED8[2U];                 /**< Reserved for future use                            */
  __IOM uint32_t CTRL_CLR;                      /**< Control                                            */
  __IM uint32_t  STATUS_CLR;                    /**< Status                                             */
  uint32_t       RESERVED9[2U];                 /**< Reserved for future use                            */
  __IOM uint32_t DCOCTRL_CLR;                   /**< DAC oscillator Control                             */
  uint32_t       RESERVED10[4U];                /**< Reserved for future use                            */
  __IOM uint32_t LOCK_CLR;                      /**< Lock PLL                                           */
  __IOM uint32_t IF_CLR;                        /**< Interrupt Flag Register                            */
  __IOM uint32_t IEN_CLR;                       /**< Interrupt Enable Register                          */
  uint32_t       RESERVED11[1009U];             /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP version ID                                      */
  uint32_t       RESERVED12[2U];                /**< Reserved for future use                            */
  __IOM uint32_t CTRL_TGL;                      /**< Control                                            */
  __IM uint32_t  STATUS_TGL;                    /**< Status                                             */
  uint32_t       RESERVED13[2U];                /**< Reserved for future use                            */
  __IOM uint32_t DCOCTRL_TGL;                   /**< DAC oscillator Control                             */
  uint32_t       RESERVED14[4U];                /**< Reserved for future use                            */
  __IOM uint32_t LOCK_TGL;                      /**< Lock PLL                                           */
  __IOM uint32_t IF_TGL;                        /**< Interrupt Flag Register                            */
  __IOM uint32_t IEN_TGL;                       /**< Interrupt Enable Register                          */
} USBPLL_TypeDef;
/** @} End of group EFR32FG25_USBPLL */

/**************************************************************************//**
 * @addtogroup EFR32FG25_USBPLL
 * @{
 * @defgroup EFR32FG25_USBPLL_BitFields USBPLL Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for USBPLL IPVERSION */
#define _USBPLL_IPVERSION_RESETVALUE           0x00000001UL                               /**< Default value for USBPLL_IPVERSION          */
#define _USBPLL_IPVERSION_MASK                 0xFFFFFFFFUL                               /**< Mask for USBPLL_IPVERSION                   */
#define _USBPLL_IPVERSION_IPVERSION_SHIFT      0                                          /**< Shift value for USBPLL_IPVERSION            */
#define _USBPLL_IPVERSION_IPVERSION_MASK       0xFFFFFFFFUL                               /**< Bit mask for USBPLL_IPVERSION               */
#define _USBPLL_IPVERSION_IPVERSION_DEFAULT    0x00000001UL                               /**< Mode DEFAULT for USBPLL_IPVERSION           */
#define USBPLL_IPVERSION_IPVERSION_DEFAULT     (_USBPLL_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for USBPLL_IPVERSION   */

/* Bit fields for USBPLL CTRL */
#define _USBPLL_CTRL_RESETVALUE                0x00360100UL                             /**< Default value for USBPLL_CTRL               */
#define _USBPLL_CTRL_MASK                      0x01FFFF13UL                             /**< Mask for USBPLL_CTRL                        */
#define USBPLL_CTRL_FORCEEN                    (0x1UL << 0)                             /**< Force Enable                                */
#define _USBPLL_CTRL_FORCEEN_SHIFT             0                                        /**< Shift value for USBPLL_FORCEEN              */
#define _USBPLL_CTRL_FORCEEN_MASK              0x1UL                                    /**< Bit mask for USBPLL_FORCEEN                 */
#define _USBPLL_CTRL_FORCEEN_DEFAULT           0x00000000UL                             /**< Mode DEFAULT for USBPLL_CTRL                */
#define USBPLL_CTRL_FORCEEN_DEFAULT            (_USBPLL_CTRL_FORCEEN_DEFAULT << 0)      /**< Shifted mode DEFAULT for USBPLL_CTRL        */
#define USBPLL_CTRL_DISONDEMAND                (0x1UL << 1)                             /**< Disable on Demand                           */
#define _USBPLL_CTRL_DISONDEMAND_SHIFT         1                                        /**< Shift value for USBPLL_DISONDEMAND          */
#define _USBPLL_CTRL_DISONDEMAND_MASK          0x2UL                                    /**< Bit mask for USBPLL_DISONDEMAND             */
#define _USBPLL_CTRL_DISONDEMAND_DEFAULT       0x00000000UL                             /**< Mode DEFAULT for USBPLL_CTRL                */
#define USBPLL_CTRL_DISONDEMAND_DEFAULT        (_USBPLL_CTRL_DISONDEMAND_DEFAULT << 1)  /**< Shifted mode DEFAULT for USBPLL_CTRL        */
#define USBPLL_CTRL_SHUNTREGLPEN               (0x1UL << 4)                             /**< Shunt Regulator LP Enable                   */
#define _USBPLL_CTRL_SHUNTREGLPEN_SHIFT        4                                        /**< Shift value for USBPLL_SHUNTREGLPEN         */
#define _USBPLL_CTRL_SHUNTREGLPEN_MASK         0x10UL                                   /**< Bit mask for USBPLL_SHUNTREGLPEN            */
#define _USBPLL_CTRL_SHUNTREGLPEN_DEFAULT      0x00000000UL                             /**< Mode DEFAULT for USBPLL_CTRL                */
#define USBPLL_CTRL_SHUNTREGLPEN_DEFAULT       (_USBPLL_CTRL_SHUNTREGLPEN_DEFAULT << 4) /**< Shifted mode DEFAULT for USBPLL_CTRL        */
#define _USBPLL_CTRL_DIVR_SHIFT                8                                        /**< Shift value for USBPLL_DIVR                 */
#define _USBPLL_CTRL_DIVR_MASK                 0x1F00UL                                 /**< Bit mask for USBPLL_DIVR                    */
#define _USBPLL_CTRL_DIVR_DEFAULT              0x00000001UL                             /**< Mode DEFAULT for USBPLL_CTRL                */
#define USBPLL_CTRL_DIVR_DEFAULT               (_USBPLL_CTRL_DIVR_DEFAULT << 8)         /**< Shifted mode DEFAULT for USBPLL_CTRL        */
#define _USBPLL_CTRL_DIVX_SHIFT                13                                       /**< Shift value for USBPLL_DIVX                 */
#define _USBPLL_CTRL_DIVX_MASK                 0x3E000UL                                /**< Bit mask for USBPLL_DIVX                    */
#define _USBPLL_CTRL_DIVX_DEFAULT              0x00000010UL                             /**< Mode DEFAULT for USBPLL_CTRL                */
#define USBPLL_CTRL_DIVX_DEFAULT               (_USBPLL_CTRL_DIVX_DEFAULT << 13)        /**< Shifted mode DEFAULT for USBPLL_CTRL        */
#define _USBPLL_CTRL_DIVN_SHIFT                18                                       /**< Shift value for USBPLL_DIVN                 */
#define _USBPLL_CTRL_DIVN_MASK                 0x1FC0000UL                              /**< Bit mask for USBPLL_DIVN                    */
#define _USBPLL_CTRL_DIVN_DEFAULT              0x0000000DUL                             /**< Mode DEFAULT for USBPLL_CTRL                */
#define USBPLL_CTRL_DIVN_DEFAULT               (_USBPLL_CTRL_DIVN_DEFAULT << 18)        /**< Shifted mode DEFAULT for USBPLL_CTRL        */

/* Bit fields for USBPLL STATUS */
#define _USBPLL_STATUS_RESETVALUE              0x00000000UL                             /**< Default value for USBPLL_STATUS             */
#define _USBPLL_STATUS_MASK                    0xC0030000UL                             /**< Mask for USBPLL_STATUS                      */
#define USBPLL_STATUS_PLLRDY                   (0x1UL << 16)                            /**< USBPLL Ready                                */
#define _USBPLL_STATUS_PLLRDY_SHIFT            16                                       /**< Shift value for USBPLL_PLLRDY               */
#define _USBPLL_STATUS_PLLRDY_MASK             0x10000UL                                /**< Bit mask for USBPLL_PLLRDY                  */
#define _USBPLL_STATUS_PLLRDY_DEFAULT          0x00000000UL                             /**< Mode DEFAULT for USBPLL_STATUS              */
#define USBPLL_STATUS_PLLRDY_DEFAULT           (_USBPLL_STATUS_PLLRDY_DEFAULT << 16)    /**< Shifted mode DEFAULT for USBPLL_STATUS      */
#define USBPLL_STATUS_PLLLOCK                  (0x1UL << 17)                            /**< USBPLL is locked                            */
#define _USBPLL_STATUS_PLLLOCK_SHIFT           17                                       /**< Shift value for USBPLL_PLLLOCK              */
#define _USBPLL_STATUS_PLLLOCK_MASK            0x20000UL                                /**< Bit mask for USBPLL_PLLLOCK                 */
#define _USBPLL_STATUS_PLLLOCK_DEFAULT         0x00000000UL                             /**< Mode DEFAULT for USBPLL_STATUS              */
#define USBPLL_STATUS_PLLLOCK_DEFAULT          (_USBPLL_STATUS_PLLLOCK_DEFAULT << 17)   /**< Shifted mode DEFAULT for USBPLL_STATUS      */
#define USBPLL_STATUS_SYNCBUSY                 (0x1UL << 30)                            /**< Sync Busy                                   */
#define _USBPLL_STATUS_SYNCBUSY_SHIFT          30                                       /**< Shift value for USBPLL_SYNCBUSY             */
#define _USBPLL_STATUS_SYNCBUSY_MASK           0x40000000UL                             /**< Bit mask for USBPLL_SYNCBUSY                */
#define _USBPLL_STATUS_SYNCBUSY_DEFAULT        0x00000000UL                             /**< Mode DEFAULT for USBPLL_STATUS              */
#define USBPLL_STATUS_SYNCBUSY_DEFAULT         (_USBPLL_STATUS_SYNCBUSY_DEFAULT << 30)  /**< Shifted mode DEFAULT for USBPLL_STATUS      */
#define USBPLL_STATUS_LOCK                     (0x1UL << 31)                            /**< Locks out registers                         */
#define _USBPLL_STATUS_LOCK_SHIFT              31                                       /**< Shift value for USBPLL_LOCK                 */
#define _USBPLL_STATUS_LOCK_MASK               0x80000000UL                             /**< Bit mask for USBPLL_LOCK                    */
#define _USBPLL_STATUS_LOCK_DEFAULT            0x00000000UL                             /**< Mode DEFAULT for USBPLL_STATUS              */
#define _USBPLL_STATUS_LOCK_UNLOCKED           0x00000000UL                             /**< Mode UNLOCKED for USBPLL_STATUS             */
#define _USBPLL_STATUS_LOCK_LOCKED             0x00000001UL                             /**< Mode LOCKED for USBPLL_STATUS               */
#define USBPLL_STATUS_LOCK_DEFAULT             (_USBPLL_STATUS_LOCK_DEFAULT << 31)      /**< Shifted mode DEFAULT for USBPLL_STATUS      */
#define USBPLL_STATUS_LOCK_UNLOCKED            (_USBPLL_STATUS_LOCK_UNLOCKED << 31)     /**< Shifted mode UNLOCKED for USBPLL_STATUS     */
#define USBPLL_STATUS_LOCK_LOCKED              (_USBPLL_STATUS_LOCK_LOCKED << 31)       /**< Shifted mode LOCKED for USBPLL_STATUS       */

/* Bit fields for USBPLL DCOCTRL */
#define _USBPLL_DCOCTRL_RESETVALUE             0x00060E00UL                               /**< Default value for USBPLL_DCOCTRL            */
#define _USBPLL_DCOCTRL_MASK                   0x003E0E00UL                               /**< Mask for USBPLL_DCOCTRL                     */
#define USBPLL_DCOCTRL_DCOBIASHALF             (0x1UL << 9)                               /**< DCO Half bias                               */
#define _USBPLL_DCOCTRL_DCOBIASHALF_SHIFT      9                                          /**< Shift value for USBPLL_DCOBIASHALF          */
#define _USBPLL_DCOCTRL_DCOBIASHALF_MASK       0x200UL                                    /**< Bit mask for USBPLL_DCOBIASHALF             */
#define _USBPLL_DCOCTRL_DCOBIASHALF_DEFAULT    0x00000001UL                               /**< Mode DEFAULT for USBPLL_DCOCTRL             */
#define _USBPLL_DCOCTRL_DCOBIASHALF_DISABLE    0x00000000UL                               /**< Mode DISABLE for USBPLL_DCOCTRL             */
#define _USBPLL_DCOCTRL_DCOBIASHALF_ENABLE     0x00000001UL                               /**< Mode ENABLE for USBPLL_DCOCTRL              */
#define USBPLL_DCOCTRL_DCOBIASHALF_DEFAULT     (_USBPLL_DCOCTRL_DCOBIASHALF_DEFAULT << 9) /**< Shifted mode DEFAULT for USBPLL_DCOCTRL     */
#define USBPLL_DCOCTRL_DCOBIASHALF_DISABLE     (_USBPLL_DCOCTRL_DCOBIASHALF_DISABLE << 9) /**< Shifted mode DISABLE for USBPLL_DCOCTRL     */
#define USBPLL_DCOCTRL_DCOBIASHALF_ENABLE      (_USBPLL_DCOCTRL_DCOBIASHALF_ENABLE << 9)  /**< Shifted mode ENABLE for USBPLL_DCOCTRL      */

/* Bit fields for USBPLL LOCK */
#define _USBPLL_LOCK_RESETVALUE                0x0000580EUL                             /**< Default value for USBPLL_LOCK               */
#define _USBPLL_LOCK_MASK                      0x0000FFFFUL                             /**< Mask for USBPLL_LOCK                        */
#define _USBPLL_LOCK_LOCKKEY_SHIFT             0                                        /**< Shift value for USBPLL_LOCKKEY              */
#define _USBPLL_LOCK_LOCKKEY_MASK              0xFFFFUL                                 /**< Bit mask for USBPLL_LOCKKEY                 */
#define _USBPLL_LOCK_LOCKKEY_DEFAULT           0x0000580EUL                             /**< Mode DEFAULT for USBPLL_LOCK                */
#define _USBPLL_LOCK_LOCKKEY_UNLOCK            0x0000580EUL                             /**< Mode UNLOCK for USBPLL_LOCK                 */
#define USBPLL_LOCK_LOCKKEY_DEFAULT            (_USBPLL_LOCK_LOCKKEY_DEFAULT << 0)      /**< Shifted mode DEFAULT for USBPLL_LOCK        */
#define USBPLL_LOCK_LOCKKEY_UNLOCK             (_USBPLL_LOCK_LOCKKEY_UNLOCK << 0)       /**< Shifted mode UNLOCK for USBPLL_LOCK         */

/* Bit fields for USBPLL IF */
#define _USBPLL_IF_RESETVALUE                  0x00000000UL                             /**< Default value for USBPLL_IF                 */
#define _USBPLL_IF_MASK                        0x00000007UL                             /**< Mask for USBPLL_IF                          */
#define USBPLL_IF_PLLRDY                       (0x1UL << 0)                             /**< USBPLL Ready Interrupt Flag                 */
#define _USBPLL_IF_PLLRDY_SHIFT                0                                        /**< Shift value for USBPLL_PLLRDY               */
#define _USBPLL_IF_PLLRDY_MASK                 0x1UL                                    /**< Bit mask for USBPLL_PLLRDY                  */
#define _USBPLL_IF_PLLRDY_DEFAULT              0x00000000UL                             /**< Mode DEFAULT for USBPLL_IF                  */
#define USBPLL_IF_PLLRDY_DEFAULT               (_USBPLL_IF_PLLRDY_DEFAULT << 0)         /**< Shifted mode DEFAULT for USBPLL_IF          */
#define USBPLL_IF_PLLLOCKIF                    (0x1UL << 1)                             /**< USBPLL Lock Interrupt Flag                  */
#define _USBPLL_IF_PLLLOCKIF_SHIFT             1                                        /**< Shift value for USBPLL_PLLLOCKIF            */
#define _USBPLL_IF_PLLLOCKIF_MASK              0x2UL                                    /**< Bit mask for USBPLL_PLLLOCKIF               */
#define _USBPLL_IF_PLLLOCKIF_DEFAULT           0x00000000UL                             /**< Mode DEFAULT for USBPLL_IF                  */
#define USBPLL_IF_PLLLOCKIF_DEFAULT            (_USBPLL_IF_PLLLOCKIF_DEFAULT << 1)      /**< Shifted mode DEFAULT for USBPLL_IF          */
#define USBPLL_IF_PLLNOLOCKIF                  (0x1UL << 2)                             /**< USBPLL Loss of Lock Interrupt Flag          */
#define _USBPLL_IF_PLLNOLOCKIF_SHIFT           2                                        /**< Shift value for USBPLL_PLLNOLOCKIF          */
#define _USBPLL_IF_PLLNOLOCKIF_MASK            0x4UL                                    /**< Bit mask for USBPLL_PLLNOLOCKIF             */
#define _USBPLL_IF_PLLNOLOCKIF_DEFAULT         0x00000000UL                             /**< Mode DEFAULT for USBPLL_IF                  */
#define USBPLL_IF_PLLNOLOCKIF_DEFAULT          (_USBPLL_IF_PLLNOLOCKIF_DEFAULT << 2)    /**< Shifted mode DEFAULT for USBPLL_IF          */

/* Bit fields for USBPLL IEN */
#define _USBPLL_IEN_RESETVALUE                 0x00000000UL                             /**< Default value for USBPLL_IEN                */
#define _USBPLL_IEN_MASK                       0x00000007UL                             /**< Mask for USBPLL_IEN                         */
#define USBPLL_IEN_PLLRDY                      (0x1UL << 0)                             /**< USBPLL Ready Interrupt Enable               */
#define _USBPLL_IEN_PLLRDY_SHIFT               0                                        /**< Shift value for USBPLL_PLLRDY               */
#define _USBPLL_IEN_PLLRDY_MASK                0x1UL                                    /**< Bit mask for USBPLL_PLLRDY                  */
#define _USBPLL_IEN_PLLRDY_DEFAULT             0x00000000UL                             /**< Mode DEFAULT for USBPLL_IEN                 */
#define USBPLL_IEN_PLLRDY_DEFAULT              (_USBPLL_IEN_PLLRDY_DEFAULT << 0)        /**< Shifted mode DEFAULT for USBPLL_IEN         */
#define USBPLL_IEN_PLLLOCKIEN                  (0x1UL << 1)                             /**< USBPLL Lock Interrupt Enable                */
#define _USBPLL_IEN_PLLLOCKIEN_SHIFT           1                                        /**< Shift value for USBPLL_PLLLOCKIEN           */
#define _USBPLL_IEN_PLLLOCKIEN_MASK            0x2UL                                    /**< Bit mask for USBPLL_PLLLOCKIEN              */
#define _USBPLL_IEN_PLLLOCKIEN_DEFAULT         0x00000000UL                             /**< Mode DEFAULT for USBPLL_IEN                 */
#define USBPLL_IEN_PLLLOCKIEN_DEFAULT          (_USBPLL_IEN_PLLLOCKIEN_DEFAULT << 1)    /**< Shifted mode DEFAULT for USBPLL_IEN         */
#define USBPLL_IEN_PLLNOLOCKIEN                (0x1UL << 2)                             /**< USBPLL Loss of Lock Interrupt Enable        */
#define _USBPLL_IEN_PLLNOLOCKIEN_SHIFT         2                                        /**< Shift value for USBPLL_PLLNOLOCKIEN         */
#define _USBPLL_IEN_PLLNOLOCKIEN_MASK          0x4UL                                    /**< Bit mask for USBPLL_PLLNOLOCKIEN            */
#define _USBPLL_IEN_PLLNOLOCKIEN_DEFAULT       0x00000000UL                             /**< Mode DEFAULT for USBPLL_IEN                 */
#define USBPLL_IEN_PLLNOLOCKIEN_DEFAULT        (_USBPLL_IEN_PLLNOLOCKIEN_DEFAULT << 2)  /**< Shifted mode DEFAULT for USBPLL_IEN         */

/** @} End of group EFR32FG25_USBPLL_BitFields */
/** @} End of group EFR32FG25_USBPLL */
/** @} End of group Parts */

#endif // EFR32FG25_USBPLL_H
