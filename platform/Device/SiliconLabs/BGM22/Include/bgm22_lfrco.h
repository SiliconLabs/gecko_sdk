/**************************************************************************//**
 * @file
 * @brief BGM22 LFRCO register and bit field definitions
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
#ifndef BGM22_LFRCO_H
#define BGM22_LFRCO_H
#define LFRCO_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup BGM22_LFRCO LFRCO
 * @{
 * @brief BGM22 LFRCO Register Declaration.
 *****************************************************************************/

/** LFRCO Register Declaration. */
typedef struct {
  __IM uint32_t  IPVERSION;                     /**< IP version                                         */
  __IOM uint32_t CTRL;                          /**< Control Register                                   */
  __IM uint32_t  STATUS;                        /**< Status Register                                    */
  uint32_t       RESERVED0[2U];                 /**< Reserved for future use                            */
  __IOM uint32_t IF;                            /**< Interrupt Flag Register                            */
  __IOM uint32_t IEN;                           /**< Interrupt Enable Register                          */
  uint32_t       RESERVED1[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t LOCK;                          /**< Configuration Lock Register                        */
  __IOM uint32_t CFG;                           /**< Configuration Register                             */
  uint32_t       RESERVED2[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t NOMCAL;                        /**< Nominal Calibration Register                       */
  __IOM uint32_t NOMCALINV;                     /**< Nominal Calibration Inverted Register              */
  __IOM uint32_t CMD;                           /**< Command Register                                   */
  uint32_t       RESERVED3[1010U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP version                                         */
  __IOM uint32_t CTRL_SET;                      /**< Control Register                                   */
  __IM uint32_t  STATUS_SET;                    /**< Status Register                                    */
  uint32_t       RESERVED4[2U];                 /**< Reserved for future use                            */
  __IOM uint32_t IF_SET;                        /**< Interrupt Flag Register                            */
  __IOM uint32_t IEN_SET;                       /**< Interrupt Enable Register                          */
  uint32_t       RESERVED5[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t LOCK_SET;                      /**< Configuration Lock Register                        */
  __IOM uint32_t CFG_SET;                       /**< Configuration Register                             */
  uint32_t       RESERVED6[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t NOMCAL_SET;                    /**< Nominal Calibration Register                       */
  __IOM uint32_t NOMCALINV_SET;                 /**< Nominal Calibration Inverted Register              */
  __IOM uint32_t CMD_SET;                       /**< Command Register                                   */
  uint32_t       RESERVED7[1010U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP version                                         */
  __IOM uint32_t CTRL_CLR;                      /**< Control Register                                   */
  __IM uint32_t  STATUS_CLR;                    /**< Status Register                                    */
  uint32_t       RESERVED8[2U];                 /**< Reserved for future use                            */
  __IOM uint32_t IF_CLR;                        /**< Interrupt Flag Register                            */
  __IOM uint32_t IEN_CLR;                       /**< Interrupt Enable Register                          */
  uint32_t       RESERVED9[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t LOCK_CLR;                      /**< Configuration Lock Register                        */
  __IOM uint32_t CFG_CLR;                       /**< Configuration Register                             */
  uint32_t       RESERVED10[1U];                /**< Reserved for future use                            */
  __IOM uint32_t NOMCAL_CLR;                    /**< Nominal Calibration Register                       */
  __IOM uint32_t NOMCALINV_CLR;                 /**< Nominal Calibration Inverted Register              */
  __IOM uint32_t CMD_CLR;                       /**< Command Register                                   */
  uint32_t       RESERVED11[1010U];             /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP version                                         */
  __IOM uint32_t CTRL_TGL;                      /**< Control Register                                   */
  __IM uint32_t  STATUS_TGL;                    /**< Status Register                                    */
  uint32_t       RESERVED12[2U];                /**< Reserved for future use                            */
  __IOM uint32_t IF_TGL;                        /**< Interrupt Flag Register                            */
  __IOM uint32_t IEN_TGL;                       /**< Interrupt Enable Register                          */
  uint32_t       RESERVED13[1U];                /**< Reserved for future use                            */
  __IOM uint32_t LOCK_TGL;                      /**< Configuration Lock Register                        */
  __IOM uint32_t CFG_TGL;                       /**< Configuration Register                             */
  uint32_t       RESERVED14[1U];                /**< Reserved for future use                            */
  __IOM uint32_t NOMCAL_TGL;                    /**< Nominal Calibration Register                       */
  __IOM uint32_t NOMCALINV_TGL;                 /**< Nominal Calibration Inverted Register              */
  __IOM uint32_t CMD_TGL;                       /**< Command Register                                   */
} LFRCO_TypeDef;
/** @} End of group BGM22_LFRCO */

/**************************************************************************//**
 * @addtogroup BGM22_LFRCO
 * @{
 * @defgroup BGM22_LFRCO_BitFields LFRCO Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for LFRCO IPVERSION */
#define _LFRCO_IPVERSION_RESETVALUE              0x00000001UL                              /**< Default value for LFRCO_IPVERSION           */
#define _LFRCO_IPVERSION_MASK                    0xFFFFFFFFUL                              /**< Mask for LFRCO_IPVERSION                    */
#define _LFRCO_IPVERSION_IPVERSION_SHIFT         0                                         /**< Shift value for LFRCO_IPVERSION             */
#define _LFRCO_IPVERSION_IPVERSION_MASK          0xFFFFFFFFUL                              /**< Bit mask for LFRCO_IPVERSION                */
#define _LFRCO_IPVERSION_IPVERSION_DEFAULT       0x00000001UL                              /**< Mode DEFAULT for LFRCO_IPVERSION            */
#define LFRCO_IPVERSION_IPVERSION_DEFAULT        (_LFRCO_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for LFRCO_IPVERSION    */

/* Bit fields for LFRCO CTRL */
#define _LFRCO_CTRL_RESETVALUE                   0x00000000UL                           /**< Default value for LFRCO_CTRL                */
#define _LFRCO_CTRL_MASK                         0x00000003UL                           /**< Mask for LFRCO_CTRL                         */
#define LFRCO_CTRL_FORCEEN                       (0x1UL << 0)                           /**< Force Enable                                */
#define _LFRCO_CTRL_FORCEEN_SHIFT                0                                      /**< Shift value for LFRCO_FORCEEN               */
#define _LFRCO_CTRL_FORCEEN_MASK                 0x1UL                                  /**< Bit mask for LFRCO_FORCEEN                  */
#define _LFRCO_CTRL_FORCEEN_DEFAULT              0x00000000UL                           /**< Mode DEFAULT for LFRCO_CTRL                 */
#define LFRCO_CTRL_FORCEEN_DEFAULT               (_LFRCO_CTRL_FORCEEN_DEFAULT << 0)     /**< Shifted mode DEFAULT for LFRCO_CTRL         */
#define LFRCO_CTRL_DISONDEMAND                   (0x1UL << 1)                           /**< Disable On-Demand                           */
#define _LFRCO_CTRL_DISONDEMAND_SHIFT            1                                      /**< Shift value for LFRCO_DISONDEMAND           */
#define _LFRCO_CTRL_DISONDEMAND_MASK             0x2UL                                  /**< Bit mask for LFRCO_DISONDEMAND              */
#define _LFRCO_CTRL_DISONDEMAND_DEFAULT          0x00000000UL                           /**< Mode DEFAULT for LFRCO_CTRL                 */
#define LFRCO_CTRL_DISONDEMAND_DEFAULT           (_LFRCO_CTRL_DISONDEMAND_DEFAULT << 1) /**< Shifted mode DEFAULT for LFRCO_CTRL         */

/* Bit fields for LFRCO STATUS */
#define _LFRCO_STATUS_RESETVALUE                 0x00000000UL                           /**< Default value for LFRCO_STATUS              */
#define _LFRCO_STATUS_MASK                       0x80010001UL                           /**< Mask for LFRCO_STATUS                       */
#define LFRCO_STATUS_RDY                         (0x1UL << 0)                           /**< Ready Status                                */
#define _LFRCO_STATUS_RDY_SHIFT                  0                                      /**< Shift value for LFRCO_RDY                   */
#define _LFRCO_STATUS_RDY_MASK                   0x1UL                                  /**< Bit mask for LFRCO_RDY                      */
#define _LFRCO_STATUS_RDY_DEFAULT                0x00000000UL                           /**< Mode DEFAULT for LFRCO_STATUS               */
#define LFRCO_STATUS_RDY_DEFAULT                 (_LFRCO_STATUS_RDY_DEFAULT << 0)       /**< Shifted mode DEFAULT for LFRCO_STATUS       */
#define LFRCO_STATUS_ENS                         (0x1UL << 16)                          /**< Enabled Status                              */
#define _LFRCO_STATUS_ENS_SHIFT                  16                                     /**< Shift value for LFRCO_ENS                   */
#define _LFRCO_STATUS_ENS_MASK                   0x10000UL                              /**< Bit mask for LFRCO_ENS                      */
#define _LFRCO_STATUS_ENS_DEFAULT                0x00000000UL                           /**< Mode DEFAULT for LFRCO_STATUS               */
#define LFRCO_STATUS_ENS_DEFAULT                 (_LFRCO_STATUS_ENS_DEFAULT << 16)      /**< Shifted mode DEFAULT for LFRCO_STATUS       */
#define LFRCO_STATUS_LOCK                        (0x1UL << 31)                          /**< Lock Status                                 */
#define _LFRCO_STATUS_LOCK_SHIFT                 31                                     /**< Shift value for LFRCO_LOCK                  */
#define _LFRCO_STATUS_LOCK_MASK                  0x80000000UL                           /**< Bit mask for LFRCO_LOCK                     */
#define _LFRCO_STATUS_LOCK_DEFAULT               0x00000000UL                           /**< Mode DEFAULT for LFRCO_STATUS               */
#define _LFRCO_STATUS_LOCK_UNLOCKED              0x00000000UL                           /**< Mode UNLOCKED for LFRCO_STATUS              */
#define _LFRCO_STATUS_LOCK_LOCKED                0x00000001UL                           /**< Mode LOCKED for LFRCO_STATUS                */
#define LFRCO_STATUS_LOCK_DEFAULT                (_LFRCO_STATUS_LOCK_DEFAULT << 31)     /**< Shifted mode DEFAULT for LFRCO_STATUS       */
#define LFRCO_STATUS_LOCK_UNLOCKED               (_LFRCO_STATUS_LOCK_UNLOCKED << 31)    /**< Shifted mode UNLOCKED for LFRCO_STATUS      */
#define LFRCO_STATUS_LOCK_LOCKED                 (_LFRCO_STATUS_LOCK_LOCKED << 31)      /**< Shifted mode LOCKED for LFRCO_STATUS        */

/* Bit fields for LFRCO IF */
#define _LFRCO_IF_RESETVALUE                     0x00000000UL                           /**< Default value for LFRCO_IF                  */
#define _LFRCO_IF_MASK                           0x00070707UL                           /**< Mask for LFRCO_IF                           */
#define LFRCO_IF_RDY                             (0x1UL << 0)                           /**< Ready Flag                                  */
#define _LFRCO_IF_RDY_SHIFT                      0                                      /**< Shift value for LFRCO_RDY                   */
#define _LFRCO_IF_RDY_MASK                       0x1UL                                  /**< Bit mask for LFRCO_RDY                      */
#define _LFRCO_IF_RDY_DEFAULT                    0x00000000UL                           /**< Mode DEFAULT for LFRCO_IF                   */
#define LFRCO_IF_RDY_DEFAULT                     (_LFRCO_IF_RDY_DEFAULT << 0)           /**< Shifted mode DEFAULT for LFRCO_IF           */
#define LFRCO_IF_POSEDGE                         (0x1UL << 1)                           /**< Rising Edge Flag                            */
#define _LFRCO_IF_POSEDGE_SHIFT                  1                                      /**< Shift value for LFRCO_POSEDGE               */
#define _LFRCO_IF_POSEDGE_MASK                   0x2UL                                  /**< Bit mask for LFRCO_POSEDGE                  */
#define _LFRCO_IF_POSEDGE_DEFAULT                0x00000000UL                           /**< Mode DEFAULT for LFRCO_IF                   */
#define LFRCO_IF_POSEDGE_DEFAULT                 (_LFRCO_IF_POSEDGE_DEFAULT << 1)       /**< Shifted mode DEFAULT for LFRCO_IF           */
#define LFRCO_IF_NEGEDGE                         (0x1UL << 2)                           /**< Falling Edge Flag                           */
#define _LFRCO_IF_NEGEDGE_SHIFT                  2                                      /**< Shift value for LFRCO_NEGEDGE               */
#define _LFRCO_IF_NEGEDGE_MASK                   0x4UL                                  /**< Bit mask for LFRCO_NEGEDGE                  */
#define _LFRCO_IF_NEGEDGE_DEFAULT                0x00000000UL                           /**< Mode DEFAULT for LFRCO_IF                   */
#define LFRCO_IF_NEGEDGE_DEFAULT                 (_LFRCO_IF_NEGEDGE_DEFAULT << 2)       /**< Shifted mode DEFAULT for LFRCO_IF           */
#define LFRCO_IF_TCDONE                          (0x1UL << 8)                           /**< Temperature Check Done Flag                 */
#define _LFRCO_IF_TCDONE_SHIFT                   8                                      /**< Shift value for LFRCO_TCDONE                */
#define _LFRCO_IF_TCDONE_MASK                    0x100UL                                /**< Bit mask for LFRCO_TCDONE                   */
#define _LFRCO_IF_TCDONE_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for LFRCO_IF                   */
#define LFRCO_IF_TCDONE_DEFAULT                  (_LFRCO_IF_TCDONE_DEFAULT << 8)        /**< Shifted mode DEFAULT for LFRCO_IF           */
#define LFRCO_IF_CALDONE                         (0x1UL << 9)                           /**< Calibration Done Flag                       */
#define _LFRCO_IF_CALDONE_SHIFT                  9                                      /**< Shift value for LFRCO_CALDONE               */
#define _LFRCO_IF_CALDONE_MASK                   0x200UL                                /**< Bit mask for LFRCO_CALDONE                  */
#define _LFRCO_IF_CALDONE_DEFAULT                0x00000000UL                           /**< Mode DEFAULT for LFRCO_IF                   */
#define LFRCO_IF_CALDONE_DEFAULT                 (_LFRCO_IF_CALDONE_DEFAULT << 9)       /**< Shifted mode DEFAULT for LFRCO_IF           */
#define LFRCO_IF_TEMPCHANGE                      (0x1UL << 10)                          /**< Temperature Change Flag                     */
#define _LFRCO_IF_TEMPCHANGE_SHIFT               10                                     /**< Shift value for LFRCO_TEMPCHANGE            */
#define _LFRCO_IF_TEMPCHANGE_MASK                0x400UL                                /**< Bit mask for LFRCO_TEMPCHANGE               */
#define _LFRCO_IF_TEMPCHANGE_DEFAULT             0x00000000UL                           /**< Mode DEFAULT for LFRCO_IF                   */
#define LFRCO_IF_TEMPCHANGE_DEFAULT              (_LFRCO_IF_TEMPCHANGE_DEFAULT << 10)   /**< Shifted mode DEFAULT for LFRCO_IF           */
#define LFRCO_IF_SCHEDERR                        (0x1UL << 16)                          /**< Scheduling Error Flag                       */
#define _LFRCO_IF_SCHEDERR_SHIFT                 16                                     /**< Shift value for LFRCO_SCHEDERR              */
#define _LFRCO_IF_SCHEDERR_MASK                  0x10000UL                              /**< Bit mask for LFRCO_SCHEDERR                 */
#define _LFRCO_IF_SCHEDERR_DEFAULT               0x00000000UL                           /**< Mode DEFAULT for LFRCO_IF                   */
#define LFRCO_IF_SCHEDERR_DEFAULT                (_LFRCO_IF_SCHEDERR_DEFAULT << 16)     /**< Shifted mode DEFAULT for LFRCO_IF           */
#define LFRCO_IF_TCOOR                           (0x1UL << 17)                          /**< Temperature Check Out Of Range Flag         */
#define _LFRCO_IF_TCOOR_SHIFT                    17                                     /**< Shift value for LFRCO_TCOOR                 */
#define _LFRCO_IF_TCOOR_MASK                     0x20000UL                              /**< Bit mask for LFRCO_TCOOR                    */
#define _LFRCO_IF_TCOOR_DEFAULT                  0x00000000UL                           /**< Mode DEFAULT for LFRCO_IF                   */
#define LFRCO_IF_TCOOR_DEFAULT                   (_LFRCO_IF_TCOOR_DEFAULT << 17)        /**< Shifted mode DEFAULT for LFRCO_IF           */
#define LFRCO_IF_CALOOR                          (0x1UL << 18)                          /**< Calibration Out Of Range Flag               */
#define _LFRCO_IF_CALOOR_SHIFT                   18                                     /**< Shift value for LFRCO_CALOOR                */
#define _LFRCO_IF_CALOOR_MASK                    0x40000UL                              /**< Bit mask for LFRCO_CALOOR                   */
#define _LFRCO_IF_CALOOR_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for LFRCO_IF                   */
#define LFRCO_IF_CALOOR_DEFAULT                  (_LFRCO_IF_CALOOR_DEFAULT << 18)       /**< Shifted mode DEFAULT for LFRCO_IF           */

/* Bit fields for LFRCO IEN */
#define _LFRCO_IEN_RESETVALUE                    0x00000000UL                           /**< Default value for LFRCO_IEN                 */
#define _LFRCO_IEN_MASK                          0x00070707UL                           /**< Mask for LFRCO_IEN                          */
#define LFRCO_IEN_RDY                            (0x1UL << 0)                           /**< Ready Enable                                */
#define _LFRCO_IEN_RDY_SHIFT                     0                                      /**< Shift value for LFRCO_RDY                   */
#define _LFRCO_IEN_RDY_MASK                      0x1UL                                  /**< Bit mask for LFRCO_RDY                      */
#define _LFRCO_IEN_RDY_DEFAULT                   0x00000000UL                           /**< Mode DEFAULT for LFRCO_IEN                  */
#define LFRCO_IEN_RDY_DEFAULT                    (_LFRCO_IEN_RDY_DEFAULT << 0)          /**< Shifted mode DEFAULT for LFRCO_IEN          */
#define LFRCO_IEN_POSEDGE                        (0x1UL << 1)                           /**< Rising Edge Enable                          */
#define _LFRCO_IEN_POSEDGE_SHIFT                 1                                      /**< Shift value for LFRCO_POSEDGE               */
#define _LFRCO_IEN_POSEDGE_MASK                  0x2UL                                  /**< Bit mask for LFRCO_POSEDGE                  */
#define _LFRCO_IEN_POSEDGE_DEFAULT               0x00000000UL                           /**< Mode DEFAULT for LFRCO_IEN                  */
#define LFRCO_IEN_POSEDGE_DEFAULT                (_LFRCO_IEN_POSEDGE_DEFAULT << 1)      /**< Shifted mode DEFAULT for LFRCO_IEN          */
#define LFRCO_IEN_NEGEDGE                        (0x1UL << 2)                           /**< Falling Edge Enable                         */
#define _LFRCO_IEN_NEGEDGE_SHIFT                 2                                      /**< Shift value for LFRCO_NEGEDGE               */
#define _LFRCO_IEN_NEGEDGE_MASK                  0x4UL                                  /**< Bit mask for LFRCO_NEGEDGE                  */
#define _LFRCO_IEN_NEGEDGE_DEFAULT               0x00000000UL                           /**< Mode DEFAULT for LFRCO_IEN                  */
#define LFRCO_IEN_NEGEDGE_DEFAULT                (_LFRCO_IEN_NEGEDGE_DEFAULT << 2)      /**< Shifted mode DEFAULT for LFRCO_IEN          */
#define LFRCO_IEN_TCDONE                         (0x1UL << 8)                           /**< Temperature Check Done Enable               */
#define _LFRCO_IEN_TCDONE_SHIFT                  8                                      /**< Shift value for LFRCO_TCDONE                */
#define _LFRCO_IEN_TCDONE_MASK                   0x100UL                                /**< Bit mask for LFRCO_TCDONE                   */
#define _LFRCO_IEN_TCDONE_DEFAULT                0x00000000UL                           /**< Mode DEFAULT for LFRCO_IEN                  */
#define LFRCO_IEN_TCDONE_DEFAULT                 (_LFRCO_IEN_TCDONE_DEFAULT << 8)       /**< Shifted mode DEFAULT for LFRCO_IEN          */
#define LFRCO_IEN_CALDONE                        (0x1UL << 9)                           /**< Calibration Done Enable                     */
#define _LFRCO_IEN_CALDONE_SHIFT                 9                                      /**< Shift value for LFRCO_CALDONE               */
#define _LFRCO_IEN_CALDONE_MASK                  0x200UL                                /**< Bit mask for LFRCO_CALDONE                  */
#define _LFRCO_IEN_CALDONE_DEFAULT               0x00000000UL                           /**< Mode DEFAULT for LFRCO_IEN                  */
#define LFRCO_IEN_CALDONE_DEFAULT                (_LFRCO_IEN_CALDONE_DEFAULT << 9)      /**< Shifted mode DEFAULT for LFRCO_IEN          */
#define LFRCO_IEN_TEMPCHANGE                     (0x1UL << 10)                          /**< Temperature Change Enable                   */
#define _LFRCO_IEN_TEMPCHANGE_SHIFT              10                                     /**< Shift value for LFRCO_TEMPCHANGE            */
#define _LFRCO_IEN_TEMPCHANGE_MASK               0x400UL                                /**< Bit mask for LFRCO_TEMPCHANGE               */
#define _LFRCO_IEN_TEMPCHANGE_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for LFRCO_IEN                  */
#define LFRCO_IEN_TEMPCHANGE_DEFAULT             (_LFRCO_IEN_TEMPCHANGE_DEFAULT << 10)  /**< Shifted mode DEFAULT for LFRCO_IEN          */
#define LFRCO_IEN_SCHEDERR                       (0x1UL << 16)                          /**< Scheduling Error Enable                     */
#define _LFRCO_IEN_SCHEDERR_SHIFT                16                                     /**< Shift value for LFRCO_SCHEDERR              */
#define _LFRCO_IEN_SCHEDERR_MASK                 0x10000UL                              /**< Bit mask for LFRCO_SCHEDERR                 */
#define _LFRCO_IEN_SCHEDERR_DEFAULT              0x00000000UL                           /**< Mode DEFAULT for LFRCO_IEN                  */
#define LFRCO_IEN_SCHEDERR_DEFAULT               (_LFRCO_IEN_SCHEDERR_DEFAULT << 16)    /**< Shifted mode DEFAULT for LFRCO_IEN          */
#define LFRCO_IEN_TCOOR                          (0x1UL << 17)                          /**< Temperature Check Out Of Range Enable       */
#define _LFRCO_IEN_TCOOR_SHIFT                   17                                     /**< Shift value for LFRCO_TCOOR                 */
#define _LFRCO_IEN_TCOOR_MASK                    0x20000UL                              /**< Bit mask for LFRCO_TCOOR                    */
#define _LFRCO_IEN_TCOOR_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for LFRCO_IEN                  */
#define LFRCO_IEN_TCOOR_DEFAULT                  (_LFRCO_IEN_TCOOR_DEFAULT << 17)       /**< Shifted mode DEFAULT for LFRCO_IEN          */
#define LFRCO_IEN_CALOOR                         (0x1UL << 18)                          /**< Calibration Out Of Range Enable             */
#define _LFRCO_IEN_CALOOR_SHIFT                  18                                     /**< Shift value for LFRCO_CALOOR                */
#define _LFRCO_IEN_CALOOR_MASK                   0x40000UL                              /**< Bit mask for LFRCO_CALOOR                   */
#define _LFRCO_IEN_CALOOR_DEFAULT                0x00000000UL                           /**< Mode DEFAULT for LFRCO_IEN                  */
#define LFRCO_IEN_CALOOR_DEFAULT                 (_LFRCO_IEN_CALOOR_DEFAULT << 18)      /**< Shifted mode DEFAULT for LFRCO_IEN          */

/* Bit fields for LFRCO LOCK */
#define _LFRCO_LOCK_RESETVALUE                   0x00000000UL                           /**< Default value for LFRCO_LOCK                */
#define _LFRCO_LOCK_MASK                         0x0000FFFFUL                           /**< Mask for LFRCO_LOCK                         */
#define _LFRCO_LOCK_LOCKKEY_SHIFT                0                                      /**< Shift value for LFRCO_LOCKKEY               */
#define _LFRCO_LOCK_LOCKKEY_MASK                 0xFFFFUL                               /**< Bit mask for LFRCO_LOCKKEY                  */
#define _LFRCO_LOCK_LOCKKEY_DEFAULT              0x00000000UL                           /**< Mode DEFAULT for LFRCO_LOCK                 */
#define _LFRCO_LOCK_LOCKKEY_LOCK                 0x00000000UL                           /**< Mode LOCK for LFRCO_LOCK                    */
#define _LFRCO_LOCK_LOCKKEY_UNLOCK               0x00000F93UL                           /**< Mode UNLOCK for LFRCO_LOCK                  */
#define LFRCO_LOCK_LOCKKEY_DEFAULT               (_LFRCO_LOCK_LOCKKEY_DEFAULT << 0)     /**< Shifted mode DEFAULT for LFRCO_LOCK         */
#define LFRCO_LOCK_LOCKKEY_LOCK                  (_LFRCO_LOCK_LOCKKEY_LOCK << 0)        /**< Shifted mode LOCK for LFRCO_LOCK            */
#define LFRCO_LOCK_LOCKKEY_UNLOCK                (_LFRCO_LOCK_LOCKKEY_UNLOCK << 0)      /**< Shifted mode UNLOCK for LFRCO_LOCK          */

/* Bit fields for LFRCO CFG */
#define _LFRCO_CFG_RESETVALUE                    0x00000000UL                           /**< Default value for LFRCO_CFG                 */
#define _LFRCO_CFG_MASK                          0x00000001UL                           /**< Mask for LFRCO_CFG                          */
#define LFRCO_CFG_HIGHPRECEN                     (0x1UL << 0)                           /**< High Precision Enable                       */
#define _LFRCO_CFG_HIGHPRECEN_SHIFT              0                                      /**< Shift value for LFRCO_HIGHPRECEN            */
#define _LFRCO_CFG_HIGHPRECEN_MASK               0x1UL                                  /**< Bit mask for LFRCO_HIGHPRECEN               */
#define _LFRCO_CFG_HIGHPRECEN_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for LFRCO_CFG                  */
#define LFRCO_CFG_HIGHPRECEN_DEFAULT             (_LFRCO_CFG_HIGHPRECEN_DEFAULT << 0)   /**< Shifted mode DEFAULT for LFRCO_CFG          */

/* Bit fields for LFRCO NOMCAL */
#define _LFRCO_NOMCAL_RESETVALUE                 0x0005B8D8UL                           /**< Default value for LFRCO_NOMCAL              */
#define _LFRCO_NOMCAL_MASK                       0x001FFFFFUL                           /**< Mask for LFRCO_NOMCAL                       */
#define _LFRCO_NOMCAL_NOMCALCNT_SHIFT            0                                      /**< Shift value for LFRCO_NOMCALCNT             */
#define _LFRCO_NOMCAL_NOMCALCNT_MASK             0x1FFFFFUL                             /**< Bit mask for LFRCO_NOMCALCNT                */
#define _LFRCO_NOMCAL_NOMCALCNT_DEFAULT          0x0005B8D8UL                           /**< Mode DEFAULT for LFRCO_NOMCAL               */
#define LFRCO_NOMCAL_NOMCALCNT_DEFAULT           (_LFRCO_NOMCAL_NOMCALCNT_DEFAULT << 0) /**< Shifted mode DEFAULT for LFRCO_NOMCAL       */

/* Bit fields for LFRCO NOMCALINV */
#define _LFRCO_NOMCALINV_RESETVALUE              0x0000597AUL                                 /**< Default value for LFRCO_NOMCALINV           */
#define _LFRCO_NOMCALINV_MASK                    0x0001FFFFUL                                 /**< Mask for LFRCO_NOMCALINV                    */
#define _LFRCO_NOMCALINV_NOMCALCNTINV_SHIFT      0                                            /**< Shift value for LFRCO_NOMCALCNTINV          */
#define _LFRCO_NOMCALINV_NOMCALCNTINV_MASK       0x1FFFFUL                                    /**< Bit mask for LFRCO_NOMCALCNTINV             */
#define _LFRCO_NOMCALINV_NOMCALCNTINV_DEFAULT    0x0000597AUL                                 /**< Mode DEFAULT for LFRCO_NOMCALINV            */
#define LFRCO_NOMCALINV_NOMCALCNTINV_DEFAULT     (_LFRCO_NOMCALINV_NOMCALCNTINV_DEFAULT << 0) /**< Shifted mode DEFAULT for LFRCO_NOMCALINV    */

/* Bit fields for LFRCO CMD */
#define _LFRCO_CMD_RESETVALUE                    0x00000000UL                           /**< Default value for LFRCO_CMD                 */
#define _LFRCO_CMD_MASK                          0x00000001UL                           /**< Mask for LFRCO_CMD                          */
#define LFRCO_CMD_REDUCETCINT                    (0x1UL << 0)                           /**< Reduce Temperature Check Interval           */
#define _LFRCO_CMD_REDUCETCINT_SHIFT             0                                      /**< Shift value for LFRCO_REDUCETCINT           */
#define _LFRCO_CMD_REDUCETCINT_MASK              0x1UL                                  /**< Bit mask for LFRCO_REDUCETCINT              */
#define _LFRCO_CMD_REDUCETCINT_DEFAULT           0x00000000UL                           /**< Mode DEFAULT for LFRCO_CMD                  */
#define LFRCO_CMD_REDUCETCINT_DEFAULT            (_LFRCO_CMD_REDUCETCINT_DEFAULT << 0)  /**< Shifted mode DEFAULT for LFRCO_CMD          */

/** @} End of group BGM22_LFRCO_BitFields */
/** @} End of group BGM22_LFRCO */
/** @} End of group Parts */

#endif /* BGM22_LFRCO_H */
