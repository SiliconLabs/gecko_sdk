/**************************************************************************//**
 * @file
 * @brief EFM32PG23 LFRCO register and bit field definitions
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
#ifndef EFM32PG23_LFRCO_H
#define EFM32PG23_LFRCO_H
#define LFRCO_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFM32PG23_LFRCO LFRCO
 * @{
 * @brief EFM32PG23 LFRCO Register Declaration.
 *****************************************************************************/

/** LFRCO Register Declaration. */
typedef struct {
  __IM uint32_t  IPVERSION;                     /**< IP version                                         */
  __IOM uint32_t CTRL;                          /**< Control Register                                   */
  __IM uint32_t  STATUS;                        /**< Status Register                                    */
  __IOM uint32_t CAL;                           /**< Calibration Register                               */
  uint32_t       RESERVED0[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t IF;                            /**< Interrupt Flag Register                            */
  __IOM uint32_t IEN;                           /**< Interrupt Enable Register                          */
  __IM uint32_t  SYNCBUSY;                      /**< Synchronization Busy Register                      */
  __IOM uint32_t LOCK;                          /**< Configuration Lock Register                        */
  uint32_t       RESERVED1[1015U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP version                                         */
  __IOM uint32_t CTRL_SET;                      /**< Control Register                                   */
  __IM uint32_t  STATUS_SET;                    /**< Status Register                                    */
  __IOM uint32_t CAL_SET;                       /**< Calibration Register                               */
  uint32_t       RESERVED2[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t IF_SET;                        /**< Interrupt Flag Register                            */
  __IOM uint32_t IEN_SET;                       /**< Interrupt Enable Register                          */
  __IM uint32_t  SYNCBUSY_SET;                  /**< Synchronization Busy Register                      */
  __IOM uint32_t LOCK_SET;                      /**< Configuration Lock Register                        */
  uint32_t       RESERVED3[1015U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP version                                         */
  __IOM uint32_t CTRL_CLR;                      /**< Control Register                                   */
  __IM uint32_t  STATUS_CLR;                    /**< Status Register                                    */
  __IOM uint32_t CAL_CLR;                       /**< Calibration Register                               */
  uint32_t       RESERVED4[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t IF_CLR;                        /**< Interrupt Flag Register                            */
  __IOM uint32_t IEN_CLR;                       /**< Interrupt Enable Register                          */
  __IM uint32_t  SYNCBUSY_CLR;                  /**< Synchronization Busy Register                      */
  __IOM uint32_t LOCK_CLR;                      /**< Configuration Lock Register                        */
  uint32_t       RESERVED5[1015U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP version                                         */
  __IOM uint32_t CTRL_TGL;                      /**< Control Register                                   */
  __IM uint32_t  STATUS_TGL;                    /**< Status Register                                    */
  __IOM uint32_t CAL_TGL;                       /**< Calibration Register                               */
  uint32_t       RESERVED6[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t IF_TGL;                        /**< Interrupt Flag Register                            */
  __IOM uint32_t IEN_TGL;                       /**< Interrupt Enable Register                          */
  __IM uint32_t  SYNCBUSY_TGL;                  /**< Synchronization Busy Register                      */
  __IOM uint32_t LOCK_TGL;                      /**< Configuration Lock Register                        */
} LFRCO_TypeDef;
/** @} End of group EFM32PG23_LFRCO */

/**************************************************************************//**
 * @addtogroup EFM32PG23_LFRCO
 * @{
 * @defgroup EFM32PG23_LFRCO_BitFields LFRCO Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for LFRCO IPVERSION */
#define _LFRCO_IPVERSION_RESETVALUE           0x00000000UL                              /**< Default value for LFRCO_IPVERSION           */
#define _LFRCO_IPVERSION_MASK                 0xFFFFFFFFUL                              /**< Mask for LFRCO_IPVERSION                    */
#define _LFRCO_IPVERSION_IPVERSION_SHIFT      0                                         /**< Shift value for LFRCO_IPVERSION             */
#define _LFRCO_IPVERSION_IPVERSION_MASK       0xFFFFFFFFUL                              /**< Bit mask for LFRCO_IPVERSION                */
#define _LFRCO_IPVERSION_IPVERSION_DEFAULT    0x00000000UL                              /**< Mode DEFAULT for LFRCO_IPVERSION            */
#define LFRCO_IPVERSION_IPVERSION_DEFAULT     (_LFRCO_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for LFRCO_IPVERSION    */

/* Bit fields for LFRCO CTRL */
#define _LFRCO_CTRL_RESETVALUE                0x00000000UL                              /**< Default value for LFRCO_CTRL                */
#define _LFRCO_CTRL_MASK                      0x00000003UL                              /**< Mask for LFRCO_CTRL                         */
#define LFRCO_CTRL_FORCEEN                    (0x1UL << 0)                              /**< Force Enable                                */
#define _LFRCO_CTRL_FORCEEN_SHIFT             0                                         /**< Shift value for LFRCO_FORCEEN               */
#define _LFRCO_CTRL_FORCEEN_MASK              0x1UL                                     /**< Bit mask for LFRCO_FORCEEN                  */
#define _LFRCO_CTRL_FORCEEN_DEFAULT           0x00000000UL                              /**< Mode DEFAULT for LFRCO_CTRL                 */
#define LFRCO_CTRL_FORCEEN_DEFAULT            (_LFRCO_CTRL_FORCEEN_DEFAULT << 0)        /**< Shifted mode DEFAULT for LFRCO_CTRL         */
#define LFRCO_CTRL_DISONDEMAND                (0x1UL << 1)                              /**< Disable On-Demand                           */
#define _LFRCO_CTRL_DISONDEMAND_SHIFT         1                                         /**< Shift value for LFRCO_DISONDEMAND           */
#define _LFRCO_CTRL_DISONDEMAND_MASK          0x2UL                                     /**< Bit mask for LFRCO_DISONDEMAND              */
#define _LFRCO_CTRL_DISONDEMAND_DEFAULT       0x00000000UL                              /**< Mode DEFAULT for LFRCO_CTRL                 */
#define LFRCO_CTRL_DISONDEMAND_DEFAULT        (_LFRCO_CTRL_DISONDEMAND_DEFAULT << 1)    /**< Shifted mode DEFAULT for LFRCO_CTRL         */

/* Bit fields for LFRCO STATUS */
#define _LFRCO_STATUS_RESETVALUE              0x00000000UL                              /**< Default value for LFRCO_STATUS              */
#define _LFRCO_STATUS_MASK                    0x80010001UL                              /**< Mask for LFRCO_STATUS                       */
#define LFRCO_STATUS_RDY                      (0x1UL << 0)                              /**< Ready Status                                */
#define _LFRCO_STATUS_RDY_SHIFT               0                                         /**< Shift value for LFRCO_RDY                   */
#define _LFRCO_STATUS_RDY_MASK                0x1UL                                     /**< Bit mask for LFRCO_RDY                      */
#define _LFRCO_STATUS_RDY_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for LFRCO_STATUS               */
#define LFRCO_STATUS_RDY_DEFAULT              (_LFRCO_STATUS_RDY_DEFAULT << 0)          /**< Shifted mode DEFAULT for LFRCO_STATUS       */
#define LFRCO_STATUS_ENS                      (0x1UL << 16)                             /**< Enabled Status                              */
#define _LFRCO_STATUS_ENS_SHIFT               16                                        /**< Shift value for LFRCO_ENS                   */
#define _LFRCO_STATUS_ENS_MASK                0x10000UL                                 /**< Bit mask for LFRCO_ENS                      */
#define _LFRCO_STATUS_ENS_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for LFRCO_STATUS               */
#define LFRCO_STATUS_ENS_DEFAULT              (_LFRCO_STATUS_ENS_DEFAULT << 16)         /**< Shifted mode DEFAULT for LFRCO_STATUS       */
#define LFRCO_STATUS_LOCK                     (0x1UL << 31)                             /**< Lock Status                                 */
#define _LFRCO_STATUS_LOCK_SHIFT              31                                        /**< Shift value for LFRCO_LOCK                  */
#define _LFRCO_STATUS_LOCK_MASK               0x80000000UL                              /**< Bit mask for LFRCO_LOCK                     */
#define _LFRCO_STATUS_LOCK_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for LFRCO_STATUS               */
#define _LFRCO_STATUS_LOCK_UNLOCKED           0x00000000UL                              /**< Mode UNLOCKED for LFRCO_STATUS              */
#define _LFRCO_STATUS_LOCK_LOCKED             0x00000001UL                              /**< Mode LOCKED for LFRCO_STATUS                */
#define LFRCO_STATUS_LOCK_DEFAULT             (_LFRCO_STATUS_LOCK_DEFAULT << 31)        /**< Shifted mode DEFAULT for LFRCO_STATUS       */
#define LFRCO_STATUS_LOCK_UNLOCKED            (_LFRCO_STATUS_LOCK_UNLOCKED << 31)       /**< Shifted mode UNLOCKED for LFRCO_STATUS      */
#define LFRCO_STATUS_LOCK_LOCKED              (_LFRCO_STATUS_LOCK_LOCKED << 31)         /**< Shifted mode LOCKED for LFRCO_STATUS        */

/* Bit fields for LFRCO CAL */
#define _LFRCO_CAL_RESETVALUE                 0x000000A5UL                              /**< Default value for LFRCO_CAL                 */
#define _LFRCO_CAL_MASK                       0x000000FFUL                              /**< Mask for LFRCO_CAL                          */
#define _LFRCO_CAL_FREQTRIM_SHIFT             0                                         /**< Shift value for LFRCO_FREQTRIM              */
#define _LFRCO_CAL_FREQTRIM_MASK              0xFFUL                                    /**< Bit mask for LFRCO_FREQTRIM                 */
#define _LFRCO_CAL_FREQTRIM_DEFAULT           0x000000A5UL                              /**< Mode DEFAULT for LFRCO_CAL                  */
#define LFRCO_CAL_FREQTRIM_DEFAULT            (_LFRCO_CAL_FREQTRIM_DEFAULT << 0)        /**< Shifted mode DEFAULT for LFRCO_CAL          */

/* Bit fields for LFRCO IF */
#define _LFRCO_IF_RESETVALUE                  0x00000000UL                              /**< Default value for LFRCO_IF                  */
#define _LFRCO_IF_MASK                        0x00000007UL                              /**< Mask for LFRCO_IF                           */
#define LFRCO_IF_RDY                          (0x1UL << 0)                              /**< Ready Interrupt Flag                        */
#define _LFRCO_IF_RDY_SHIFT                   0                                         /**< Shift value for LFRCO_RDY                   */
#define _LFRCO_IF_RDY_MASK                    0x1UL                                     /**< Bit mask for LFRCO_RDY                      */
#define _LFRCO_IF_RDY_DEFAULT                 0x00000000UL                              /**< Mode DEFAULT for LFRCO_IF                   */
#define LFRCO_IF_RDY_DEFAULT                  (_LFRCO_IF_RDY_DEFAULT << 0)              /**< Shifted mode DEFAULT for LFRCO_IF           */
#define LFRCO_IF_POSEDGE                      (0x1UL << 1)                              /**< Rising Edge Interrupt Flag                  */
#define _LFRCO_IF_POSEDGE_SHIFT               1                                         /**< Shift value for LFRCO_POSEDGE               */
#define _LFRCO_IF_POSEDGE_MASK                0x2UL                                     /**< Bit mask for LFRCO_POSEDGE                  */
#define _LFRCO_IF_POSEDGE_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for LFRCO_IF                   */
#define LFRCO_IF_POSEDGE_DEFAULT              (_LFRCO_IF_POSEDGE_DEFAULT << 1)          /**< Shifted mode DEFAULT for LFRCO_IF           */
#define LFRCO_IF_NEGEDGE                      (0x1UL << 2)                              /**< Falling Edge Interrupt Flag                 */
#define _LFRCO_IF_NEGEDGE_SHIFT               2                                         /**< Shift value for LFRCO_NEGEDGE               */
#define _LFRCO_IF_NEGEDGE_MASK                0x4UL                                     /**< Bit mask for LFRCO_NEGEDGE                  */
#define _LFRCO_IF_NEGEDGE_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for LFRCO_IF                   */
#define LFRCO_IF_NEGEDGE_DEFAULT              (_LFRCO_IF_NEGEDGE_DEFAULT << 2)          /**< Shifted mode DEFAULT for LFRCO_IF           */

/* Bit fields for LFRCO IEN */
#define _LFRCO_IEN_RESETVALUE                 0x00000000UL                              /**< Default value for LFRCO_IEN                 */
#define _LFRCO_IEN_MASK                       0x00000007UL                              /**< Mask for LFRCO_IEN                          */
#define LFRCO_IEN_RDY                         (0x1UL << 0)                              /**< Ready Interrupt Enable                      */
#define _LFRCO_IEN_RDY_SHIFT                  0                                         /**< Shift value for LFRCO_RDY                   */
#define _LFRCO_IEN_RDY_MASK                   0x1UL                                     /**< Bit mask for LFRCO_RDY                      */
#define _LFRCO_IEN_RDY_DEFAULT                0x00000000UL                              /**< Mode DEFAULT for LFRCO_IEN                  */
#define LFRCO_IEN_RDY_DEFAULT                 (_LFRCO_IEN_RDY_DEFAULT << 0)             /**< Shifted mode DEFAULT for LFRCO_IEN          */
#define LFRCO_IEN_POSEDGE                     (0x1UL << 1)                              /**< Rising Edge Interrupt Enable                */
#define _LFRCO_IEN_POSEDGE_SHIFT              1                                         /**< Shift value for LFRCO_POSEDGE               */
#define _LFRCO_IEN_POSEDGE_MASK               0x2UL                                     /**< Bit mask for LFRCO_POSEDGE                  */
#define _LFRCO_IEN_POSEDGE_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for LFRCO_IEN                  */
#define LFRCO_IEN_POSEDGE_DEFAULT             (_LFRCO_IEN_POSEDGE_DEFAULT << 1)         /**< Shifted mode DEFAULT for LFRCO_IEN          */
#define LFRCO_IEN_NEGEDGE                     (0x1UL << 2)                              /**< Falling Edge Interrupt Enable               */
#define _LFRCO_IEN_NEGEDGE_SHIFT              2                                         /**< Shift value for LFRCO_NEGEDGE               */
#define _LFRCO_IEN_NEGEDGE_MASK               0x4UL                                     /**< Bit mask for LFRCO_NEGEDGE                  */
#define _LFRCO_IEN_NEGEDGE_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for LFRCO_IEN                  */
#define LFRCO_IEN_NEGEDGE_DEFAULT             (_LFRCO_IEN_NEGEDGE_DEFAULT << 2)         /**< Shifted mode DEFAULT for LFRCO_IEN          */

/* Bit fields for LFRCO SYNCBUSY */
#define _LFRCO_SYNCBUSY_RESETVALUE            0x00000000UL                              /**< Default value for LFRCO_SYNCBUSY            */
#define _LFRCO_SYNCBUSY_MASK                  0x00000001UL                              /**< Mask for LFRCO_SYNCBUSY                     */
#define LFRCO_SYNCBUSY_CAL                    (0x1UL << 0)                              /**< CAL Busy                                    */
#define _LFRCO_SYNCBUSY_CAL_SHIFT             0                                         /**< Shift value for LFRCO_CAL                   */
#define _LFRCO_SYNCBUSY_CAL_MASK              0x1UL                                     /**< Bit mask for LFRCO_CAL                      */
#define _LFRCO_SYNCBUSY_CAL_DEFAULT           0x00000000UL                              /**< Mode DEFAULT for LFRCO_SYNCBUSY             */
#define LFRCO_SYNCBUSY_CAL_DEFAULT            (_LFRCO_SYNCBUSY_CAL_DEFAULT << 0)        /**< Shifted mode DEFAULT for LFRCO_SYNCBUSY     */

/* Bit fields for LFRCO LOCK */
#define _LFRCO_LOCK_RESETVALUE                0x00002603UL                              /**< Default value for LFRCO_LOCK                */
#define _LFRCO_LOCK_MASK                      0x0000FFFFUL                              /**< Mask for LFRCO_LOCK                         */
#define _LFRCO_LOCK_LOCKKEY_SHIFT             0                                         /**< Shift value for LFRCO_LOCKKEY               */
#define _LFRCO_LOCK_LOCKKEY_MASK              0xFFFFUL                                  /**< Bit mask for LFRCO_LOCKKEY                  */
#define _LFRCO_LOCK_LOCKKEY_DEFAULT           0x00002603UL                              /**< Mode DEFAULT for LFRCO_LOCK                 */
#define _LFRCO_LOCK_LOCKKEY_LOCK              0x00000000UL                              /**< Mode LOCK for LFRCO_LOCK                    */
#define _LFRCO_LOCK_LOCKKEY_UNLOCK            0x00002603UL                              /**< Mode UNLOCK for LFRCO_LOCK                  */
#define LFRCO_LOCK_LOCKKEY_DEFAULT            (_LFRCO_LOCK_LOCKKEY_DEFAULT << 0)        /**< Shifted mode DEFAULT for LFRCO_LOCK         */
#define LFRCO_LOCK_LOCKKEY_LOCK               (_LFRCO_LOCK_LOCKKEY_LOCK << 0)           /**< Shifted mode LOCK for LFRCO_LOCK            */
#define LFRCO_LOCK_LOCKKEY_UNLOCK             (_LFRCO_LOCK_LOCKKEY_UNLOCK << 0)         /**< Shifted mode UNLOCK for LFRCO_LOCK          */

/** @} End of group EFM32PG23_LFRCO_BitFields */
/** @} End of group EFM32PG23_LFRCO */
/** @} End of group Parts */

#endif /* EFM32PG23_LFRCO_H */
