/**************************************************************************//**
 * @file
 * @brief EFR32MG21 SMU register and bit field definitions
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
#ifndef EFR32MG21_SMU_H
#define EFR32MG21_SMU_H
#define SMU_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32MG21_SMU SMU
 * @{
 * @brief EFR32MG21 SMU Register Declaration.
 *****************************************************************************/

/** SMU Register Declaration. */
typedef struct {
  __IM uint32_t  IPVERSION;                     /**< IP Version                                         */
  __IM uint32_t  STATUS;                        /**< Status Register                                    */
  __IOM uint32_t LOCK;                          /**< Lock Register                                      */
  __IOM uint32_t IF;                            /**< Interrupt Flag Register                            */
  __IOM uint32_t IEN;                           /**< Interrupt Enable Register                          */
  uint32_t       RESERVED0[3U];                 /**< Reserved for future use                            */
  __IOM uint32_t M33CTRL;                       /**< M33 Control Settings                               */
  uint32_t       RESERVED1[7U];                 /**< Reserved for future use                            */
  __IOM uint32_t PPUPATD0;                      /**< Privileged Access                                  */
  __IOM uint32_t PPUPATD1;                      /**< Privileged Access                                  */
  uint32_t       RESERVED2[6U];                 /**< Reserved for future use                            */
  __IOM uint32_t PPUSATD0;                      /**< Secure Access                                      */
  __IOM uint32_t PPUSATD1;                      /**< Secure Access                                      */
  uint32_t       RESERVED3[54U];                /**< Reserved for future use                            */
  __IM uint32_t  PPUFS;                         /**< Fault Status                                       */
  uint32_t       RESERVED4[3U];                 /**< Reserved for future use                            */
  __IOM uint32_t BMPUPATD0;                     /**< Privileged Attribute                               */
  uint32_t       RESERVED5[7U];                 /**< Reserved for future use                            */
  __IOM uint32_t BMPUSATD0;                     /**< Secure Attribute                                   */
  uint32_t       RESERVED6[55U];                /**< Reserved for future use                            */
  __IM uint32_t  BMPUFS;                        /**< Fault Status                                       */
  __IM uint32_t  BMPUFSADDR;                    /**< Fault Status Address                               */
  uint32_t       RESERVED7[2U];                 /**< Reserved for future use                            */
  __IOM uint32_t ESAURTYPES0;                   /**< Region Types 0                                     */
  __IOM uint32_t ESAURTYPES1;                   /**< Region Types 1                                     */
  uint32_t       RESERVED8[2U];                 /**< Reserved for future use                            */
  __IOM uint32_t ESAUMRB01;                     /**< Movable Region Boundary                            */
  __IOM uint32_t ESAUMRB12;                     /**< Movable Region Boundary                            */
  uint32_t       RESERVED9[2U];                 /**< Reserved for future use                            */
  __IOM uint32_t ESAUMRB45;                     /**< Movable Region Boundary                            */
  __IOM uint32_t ESAUMRB56;                     /**< Movable Region Boundary                            */
  uint32_t       RESERVED10[862U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP Version                                         */
  __IM uint32_t  STATUS_SET;                    /**< Status Register                                    */
  __IOM uint32_t LOCK_SET;                      /**< Lock Register                                      */
  __IOM uint32_t IF_SET;                        /**< Interrupt Flag Register                            */
  __IOM uint32_t IEN_SET;                       /**< Interrupt Enable Register                          */
  uint32_t       RESERVED11[3U];                /**< Reserved for future use                            */
  __IOM uint32_t M33CTRL_SET;                   /**< M33 Control Settings                               */
  uint32_t       RESERVED12[7U];                /**< Reserved for future use                            */
  __IOM uint32_t PPUPATD0_SET;                  /**< Privileged Access                                  */
  __IOM uint32_t PPUPATD1_SET;                  /**< Privileged Access                                  */
  uint32_t       RESERVED13[6U];                /**< Reserved for future use                            */
  __IOM uint32_t PPUSATD0_SET;                  /**< Secure Access                                      */
  __IOM uint32_t PPUSATD1_SET;                  /**< Secure Access                                      */
  uint32_t       RESERVED14[54U];               /**< Reserved for future use                            */
  __IM uint32_t  PPUFS_SET;                     /**< Fault Status                                       */
  uint32_t       RESERVED15[3U];                /**< Reserved for future use                            */
  __IOM uint32_t BMPUPATD0_SET;                 /**< Privileged Attribute                               */
  uint32_t       RESERVED16[7U];                /**< Reserved for future use                            */
  __IOM uint32_t BMPUSATD0_SET;                 /**< Secure Attribute                                   */
  uint32_t       RESERVED17[55U];               /**< Reserved for future use                            */
  __IM uint32_t  BMPUFS_SET;                    /**< Fault Status                                       */
  __IM uint32_t  BMPUFSADDR_SET;                /**< Fault Status Address                               */
  uint32_t       RESERVED18[2U];                /**< Reserved for future use                            */
  __IOM uint32_t ESAURTYPES0_SET;               /**< Region Types 0                                     */
  __IOM uint32_t ESAURTYPES1_SET;               /**< Region Types 1                                     */
  uint32_t       RESERVED19[2U];                /**< Reserved for future use                            */
  __IOM uint32_t ESAUMRB01_SET;                 /**< Movable Region Boundary                            */
  __IOM uint32_t ESAUMRB12_SET;                 /**< Movable Region Boundary                            */
  uint32_t       RESERVED20[2U];                /**< Reserved for future use                            */
  __IOM uint32_t ESAUMRB45_SET;                 /**< Movable Region Boundary                            */
  __IOM uint32_t ESAUMRB56_SET;                 /**< Movable Region Boundary                            */
  uint32_t       RESERVED21[862U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP Version                                         */
  __IM uint32_t  STATUS_CLR;                    /**< Status Register                                    */
  __IOM uint32_t LOCK_CLR;                      /**< Lock Register                                      */
  __IOM uint32_t IF_CLR;                        /**< Interrupt Flag Register                            */
  __IOM uint32_t IEN_CLR;                       /**< Interrupt Enable Register                          */
  uint32_t       RESERVED22[3U];                /**< Reserved for future use                            */
  __IOM uint32_t M33CTRL_CLR;                   /**< M33 Control Settings                               */
  uint32_t       RESERVED23[7U];                /**< Reserved for future use                            */
  __IOM uint32_t PPUPATD0_CLR;                  /**< Privileged Access                                  */
  __IOM uint32_t PPUPATD1_CLR;                  /**< Privileged Access                                  */
  uint32_t       RESERVED24[6U];                /**< Reserved for future use                            */
  __IOM uint32_t PPUSATD0_CLR;                  /**< Secure Access                                      */
  __IOM uint32_t PPUSATD1_CLR;                  /**< Secure Access                                      */
  uint32_t       RESERVED25[54U];               /**< Reserved for future use                            */
  __IM uint32_t  PPUFS_CLR;                     /**< Fault Status                                       */
  uint32_t       RESERVED26[3U];                /**< Reserved for future use                            */
  __IOM uint32_t BMPUPATD0_CLR;                 /**< Privileged Attribute                               */
  uint32_t       RESERVED27[7U];                /**< Reserved for future use                            */
  __IOM uint32_t BMPUSATD0_CLR;                 /**< Secure Attribute                                   */
  uint32_t       RESERVED28[55U];               /**< Reserved for future use                            */
  __IM uint32_t  BMPUFS_CLR;                    /**< Fault Status                                       */
  __IM uint32_t  BMPUFSADDR_CLR;                /**< Fault Status Address                               */
  uint32_t       RESERVED29[2U];                /**< Reserved for future use                            */
  __IOM uint32_t ESAURTYPES0_CLR;               /**< Region Types 0                                     */
  __IOM uint32_t ESAURTYPES1_CLR;               /**< Region Types 1                                     */
  uint32_t       RESERVED30[2U];                /**< Reserved for future use                            */
  __IOM uint32_t ESAUMRB01_CLR;                 /**< Movable Region Boundary                            */
  __IOM uint32_t ESAUMRB12_CLR;                 /**< Movable Region Boundary                            */
  uint32_t       RESERVED31[2U];                /**< Reserved for future use                            */
  __IOM uint32_t ESAUMRB45_CLR;                 /**< Movable Region Boundary                            */
  __IOM uint32_t ESAUMRB56_CLR;                 /**< Movable Region Boundary                            */
  uint32_t       RESERVED32[862U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP Version                                         */
  __IM uint32_t  STATUS_TGL;                    /**< Status Register                                    */
  __IOM uint32_t LOCK_TGL;                      /**< Lock Register                                      */
  __IOM uint32_t IF_TGL;                        /**< Interrupt Flag Register                            */
  __IOM uint32_t IEN_TGL;                       /**< Interrupt Enable Register                          */
  uint32_t       RESERVED33[3U];                /**< Reserved for future use                            */
  __IOM uint32_t M33CTRL_TGL;                   /**< M33 Control Settings                               */
  uint32_t       RESERVED34[7U];                /**< Reserved for future use                            */
  __IOM uint32_t PPUPATD0_TGL;                  /**< Privileged Access                                  */
  __IOM uint32_t PPUPATD1_TGL;                  /**< Privileged Access                                  */
  uint32_t       RESERVED35[6U];                /**< Reserved for future use                            */
  __IOM uint32_t PPUSATD0_TGL;                  /**< Secure Access                                      */
  __IOM uint32_t PPUSATD1_TGL;                  /**< Secure Access                                      */
  uint32_t       RESERVED36[54U];               /**< Reserved for future use                            */
  __IM uint32_t  PPUFS_TGL;                     /**< Fault Status                                       */
  uint32_t       RESERVED37[3U];                /**< Reserved for future use                            */
  __IOM uint32_t BMPUPATD0_TGL;                 /**< Privileged Attribute                               */
  uint32_t       RESERVED38[7U];                /**< Reserved for future use                            */
  __IOM uint32_t BMPUSATD0_TGL;                 /**< Secure Attribute                                   */
  uint32_t       RESERVED39[55U];               /**< Reserved for future use                            */
  __IM uint32_t  BMPUFS_TGL;                    /**< Fault Status                                       */
  __IM uint32_t  BMPUFSADDR_TGL;                /**< Fault Status Address                               */
  uint32_t       RESERVED40[2U];                /**< Reserved for future use                            */
  __IOM uint32_t ESAURTYPES0_TGL;               /**< Region Types 0                                     */
  __IOM uint32_t ESAURTYPES1_TGL;               /**< Region Types 1                                     */
  uint32_t       RESERVED41[2U];                /**< Reserved for future use                            */
  __IOM uint32_t ESAUMRB01_TGL;                 /**< Movable Region Boundary                            */
  __IOM uint32_t ESAUMRB12_TGL;                 /**< Movable Region Boundary                            */
  uint32_t       RESERVED42[2U];                /**< Reserved for future use                            */
  __IOM uint32_t ESAUMRB45_TGL;                 /**< Movable Region Boundary                            */
  __IOM uint32_t ESAUMRB56_TGL;                 /**< Movable Region Boundary                            */
} SMU_TypeDef;
/** @} End of group EFR32MG21_SMU */

/**************************************************************************//**
 * @addtogroup EFR32MG21_SMU
 * @{
 * @defgroup EFR32MG21_SMU_BitFields SMU Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for SMU IPVERSION */
#define _SMU_IPVERSION_RESETVALUE                 0x00000000UL                            /**< Default value for SMU_IPVERSION             */
#define _SMU_IPVERSION_MASK                       0xFFFFFFFFUL                            /**< Mask for SMU_IPVERSION                      */
#define _SMU_IPVERSION_IPVERSION_SHIFT            0                                       /**< Shift value for SMU_IPVERSION               */
#define _SMU_IPVERSION_IPVERSION_MASK             0xFFFFFFFFUL                            /**< Bit mask for SMU_IPVERSION                  */
#define _SMU_IPVERSION_IPVERSION_DEFAULT          0x00000000UL                            /**< Mode DEFAULT for SMU_IPVERSION              */
#define SMU_IPVERSION_IPVERSION_DEFAULT           (_SMU_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for SMU_IPVERSION      */

/* Bit fields for SMU STATUS */
#define _SMU_STATUS_RESETVALUE                    0x00000000UL                          /**< Default value for SMU_STATUS                */
#define _SMU_STATUS_MASK                          0x00000003UL                          /**< Mask for SMU_STATUS                         */
#define SMU_STATUS_SMULOCK                        (0x1UL << 0)                          /**< SMU Lock                                    */
#define _SMU_STATUS_SMULOCK_SHIFT                 0                                     /**< Shift value for SMU_SMULOCK                 */
#define _SMU_STATUS_SMULOCK_MASK                  0x1UL                                 /**< Bit mask for SMU_SMULOCK                    */
#define _SMU_STATUS_SMULOCK_DEFAULT               0x00000000UL                          /**< Mode DEFAULT for SMU_STATUS                 */
#define _SMU_STATUS_SMULOCK_UNLOCKED              0x00000000UL                          /**< Mode UNLOCKED for SMU_STATUS                */
#define _SMU_STATUS_SMULOCK_LOCKED                0x00000001UL                          /**< Mode LOCKED for SMU_STATUS                  */
#define SMU_STATUS_SMULOCK_DEFAULT                (_SMU_STATUS_SMULOCK_DEFAULT << 0)    /**< Shifted mode DEFAULT for SMU_STATUS         */
#define SMU_STATUS_SMULOCK_UNLOCKED               (_SMU_STATUS_SMULOCK_UNLOCKED << 0)   /**< Shifted mode UNLOCKED for SMU_STATUS        */
#define SMU_STATUS_SMULOCK_LOCKED                 (_SMU_STATUS_SMULOCK_LOCKED << 0)     /**< Shifted mode LOCKED for SMU_STATUS          */
#define SMU_STATUS_SMUPRGERR                      (0x1UL << 1)                          /**< SMU Programming Error                       */
#define _SMU_STATUS_SMUPRGERR_SHIFT               1                                     /**< Shift value for SMU_SMUPRGERR               */
#define _SMU_STATUS_SMUPRGERR_MASK                0x2UL                                 /**< Bit mask for SMU_SMUPRGERR                  */
#define _SMU_STATUS_SMUPRGERR_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMU_STATUS                 */
#define SMU_STATUS_SMUPRGERR_DEFAULT              (_SMU_STATUS_SMUPRGERR_DEFAULT << 1)  /**< Shifted mode DEFAULT for SMU_STATUS         */

/* Bit fields for SMU LOCK */
#define _SMU_LOCK_RESETVALUE                      0x00000000UL                          /**< Default value for SMU_LOCK                  */
#define _SMU_LOCK_MASK                            0x00FFFFFFUL                          /**< Mask for SMU_LOCK                           */
#define _SMU_LOCK_SMULOCKKEY_SHIFT                0                                     /**< Shift value for SMU_SMULOCKKEY              */
#define _SMU_LOCK_SMULOCKKEY_MASK                 0xFFFFFFUL                            /**< Bit mask for SMU_SMULOCKKEY                 */
#define _SMU_LOCK_SMULOCKKEY_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMU_LOCK                   */
#define _SMU_LOCK_SMULOCKKEY_UNLOCK               0x00ACCE55UL                          /**< Mode UNLOCK for SMU_LOCK                    */
#define SMU_LOCK_SMULOCKKEY_DEFAULT               (_SMU_LOCK_SMULOCKKEY_DEFAULT << 0)   /**< Shifted mode DEFAULT for SMU_LOCK           */
#define SMU_LOCK_SMULOCKKEY_UNLOCK                (_SMU_LOCK_SMULOCKKEY_UNLOCK << 0)    /**< Shifted mode UNLOCK for SMU_LOCK            */

/* Bit fields for SMU IF */
#define _SMU_IF_RESETVALUE                        0x00000000UL                          /**< Default value for SMU_IF                    */
#define _SMU_IF_MASK                              0x00030005UL                          /**< Mask for SMU_IF                             */
#define SMU_IF_PPUPRIV                            (0x1UL << 0)                          /**< PPU Privilege Interrupt Flag                */
#define _SMU_IF_PPUPRIV_SHIFT                     0                                     /**< Shift value for SMU_PPUPRIV                 */
#define _SMU_IF_PPUPRIV_MASK                      0x1UL                                 /**< Bit mask for SMU_PPUPRIV                    */
#define _SMU_IF_PPUPRIV_DEFAULT                   0x00000000UL                          /**< Mode DEFAULT for SMU_IF                     */
#define SMU_IF_PPUPRIV_DEFAULT                    (_SMU_IF_PPUPRIV_DEFAULT << 0)        /**< Shifted mode DEFAULT for SMU_IF             */
#define SMU_IF_PPUINST                            (0x1UL << 2)                          /**< PPU Instruction Interrupt Flag              */
#define _SMU_IF_PPUINST_SHIFT                     2                                     /**< Shift value for SMU_PPUINST                 */
#define _SMU_IF_PPUINST_MASK                      0x4UL                                 /**< Bit mask for SMU_PPUINST                    */
#define _SMU_IF_PPUINST_DEFAULT                   0x00000000UL                          /**< Mode DEFAULT for SMU_IF                     */
#define SMU_IF_PPUINST_DEFAULT                    (_SMU_IF_PPUINST_DEFAULT << 2)        /**< Shifted mode DEFAULT for SMU_IF             */
#define SMU_IF_PPUSEC                             (0x1UL << 16)                         /**< PPU Security Interrupt Flag                 */
#define _SMU_IF_PPUSEC_SHIFT                      16                                    /**< Shift value for SMU_PPUSEC                  */
#define _SMU_IF_PPUSEC_MASK                       0x10000UL                             /**< Bit mask for SMU_PPUSEC                     */
#define _SMU_IF_PPUSEC_DEFAULT                    0x00000000UL                          /**< Mode DEFAULT for SMU_IF                     */
#define SMU_IF_PPUSEC_DEFAULT                     (_SMU_IF_PPUSEC_DEFAULT << 16)        /**< Shifted mode DEFAULT for SMU_IF             */
#define SMU_IF_BMPUSEC                            (0x1UL << 17)                         /**< BMPU Security Interrupt Flag                */
#define _SMU_IF_BMPUSEC_SHIFT                     17                                    /**< Shift value for SMU_BMPUSEC                 */
#define _SMU_IF_BMPUSEC_MASK                      0x20000UL                             /**< Bit mask for SMU_BMPUSEC                    */
#define _SMU_IF_BMPUSEC_DEFAULT                   0x00000000UL                          /**< Mode DEFAULT for SMU_IF                     */
#define SMU_IF_BMPUSEC_DEFAULT                    (_SMU_IF_BMPUSEC_DEFAULT << 17)       /**< Shifted mode DEFAULT for SMU_IF             */

/* Bit fields for SMU IEN */
#define _SMU_IEN_RESETVALUE                       0x00000000UL                          /**< Default value for SMU_IEN                   */
#define _SMU_IEN_MASK                             0x00030005UL                          /**< Mask for SMU_IEN                            */
#define SMU_IEN_PPUPRIV                           (0x1UL << 0)                          /**< PPU Privilege Interrupt Flag                */
#define _SMU_IEN_PPUPRIV_SHIFT                    0                                     /**< Shift value for SMU_PPUPRIV                 */
#define _SMU_IEN_PPUPRIV_MASK                     0x1UL                                 /**< Bit mask for SMU_PPUPRIV                    */
#define _SMU_IEN_PPUPRIV_DEFAULT                  0x00000000UL                          /**< Mode DEFAULT for SMU_IEN                    */
#define SMU_IEN_PPUPRIV_DEFAULT                   (_SMU_IEN_PPUPRIV_DEFAULT << 0)       /**< Shifted mode DEFAULT for SMU_IEN            */
#define SMU_IEN_PPUINST                           (0x1UL << 2)                          /**< PPU Instruction Interrupt Flag              */
#define _SMU_IEN_PPUINST_SHIFT                    2                                     /**< Shift value for SMU_PPUINST                 */
#define _SMU_IEN_PPUINST_MASK                     0x4UL                                 /**< Bit mask for SMU_PPUINST                    */
#define _SMU_IEN_PPUINST_DEFAULT                  0x00000000UL                          /**< Mode DEFAULT for SMU_IEN                    */
#define SMU_IEN_PPUINST_DEFAULT                   (_SMU_IEN_PPUINST_DEFAULT << 2)       /**< Shifted mode DEFAULT for SMU_IEN            */
#define SMU_IEN_PPUSEC                            (0x1UL << 16)                         /**< PPU Security Interrupt Flag                 */
#define _SMU_IEN_PPUSEC_SHIFT                     16                                    /**< Shift value for SMU_PPUSEC                  */
#define _SMU_IEN_PPUSEC_MASK                      0x10000UL                             /**< Bit mask for SMU_PPUSEC                     */
#define _SMU_IEN_PPUSEC_DEFAULT                   0x00000000UL                          /**< Mode DEFAULT for SMU_IEN                    */
#define SMU_IEN_PPUSEC_DEFAULT                    (_SMU_IEN_PPUSEC_DEFAULT << 16)       /**< Shifted mode DEFAULT for SMU_IEN            */
#define SMU_IEN_BMPUSEC                           (0x1UL << 17)                         /**< BMPU Security Interrupt Flag                */
#define _SMU_IEN_BMPUSEC_SHIFT                    17                                    /**< Shift value for SMU_BMPUSEC                 */
#define _SMU_IEN_BMPUSEC_MASK                     0x20000UL                             /**< Bit mask for SMU_BMPUSEC                    */
#define _SMU_IEN_BMPUSEC_DEFAULT                  0x00000000UL                          /**< Mode DEFAULT for SMU_IEN                    */
#define SMU_IEN_BMPUSEC_DEFAULT                   (_SMU_IEN_BMPUSEC_DEFAULT << 17)      /**< Shifted mode DEFAULT for SMU_IEN            */

/* Bit fields for SMU M33CTRL */
#define _SMU_M33CTRL_RESETVALUE                   0x00000000UL                             /**< Default value for SMU_M33CTRL               */
#define _SMU_M33CTRL_MASK                         0x0000001FUL                             /**< Mask for SMU_M33CTRL                        */
#define SMU_M33CTRL_LOCKSVTAIRCR                  (0x1UL << 0)                             /**< SVTAIRCR LOCK bit                           */
#define _SMU_M33CTRL_LOCKSVTAIRCR_SHIFT           0                                        /**< Shift value for SMU_LOCKSVTAIRCR            */
#define _SMU_M33CTRL_LOCKSVTAIRCR_MASK            0x1UL                                    /**< Bit mask for SMU_LOCKSVTAIRCR               */
#define _SMU_M33CTRL_LOCKSVTAIRCR_DEFAULT         0x00000000UL                             /**< Mode DEFAULT for SMU_M33CTRL                */
#define SMU_M33CTRL_LOCKSVTAIRCR_DEFAULT          (_SMU_M33CTRL_LOCKSVTAIRCR_DEFAULT << 0) /**< Shifted mode DEFAULT for SMU_M33CTRL        */
#define SMU_M33CTRL_LOCKNSVTOR                    (0x1UL << 1)                             /**< NSVTOR LOCK bit                             */
#define _SMU_M33CTRL_LOCKNSVTOR_SHIFT             1                                        /**< Shift value for SMU_LOCKNSVTOR              */
#define _SMU_M33CTRL_LOCKNSVTOR_MASK              0x2UL                                    /**< Bit mask for SMU_LOCKNSVTOR                 */
#define _SMU_M33CTRL_LOCKNSVTOR_DEFAULT           0x00000000UL                             /**< Mode DEFAULT for SMU_M33CTRL                */
#define SMU_M33CTRL_LOCKNSVTOR_DEFAULT            (_SMU_M33CTRL_LOCKNSVTOR_DEFAULT << 1)   /**< Shifted mode DEFAULT for SMU_M33CTRL        */
#define SMU_M33CTRL_LOCKSMPU                      (0x1UL << 2)                             /**< SMPU LOCK bit                               */
#define _SMU_M33CTRL_LOCKSMPU_SHIFT               2                                        /**< Shift value for SMU_LOCKSMPU                */
#define _SMU_M33CTRL_LOCKSMPU_MASK                0x4UL                                    /**< Bit mask for SMU_LOCKSMPU                   */
#define _SMU_M33CTRL_LOCKSMPU_DEFAULT             0x00000000UL                             /**< Mode DEFAULT for SMU_M33CTRL                */
#define SMU_M33CTRL_LOCKSMPU_DEFAULT              (_SMU_M33CTRL_LOCKSMPU_DEFAULT << 2)     /**< Shifted mode DEFAULT for SMU_M33CTRL        */
#define SMU_M33CTRL_LOCKNSMPU                     (0x1UL << 3)                             /**< NSMPU LOCK bit                              */
#define _SMU_M33CTRL_LOCKNSMPU_SHIFT              3                                        /**< Shift value for SMU_LOCKNSMPU               */
#define _SMU_M33CTRL_LOCKNSMPU_MASK               0x8UL                                    /**< Bit mask for SMU_LOCKNSMPU                  */
#define _SMU_M33CTRL_LOCKNSMPU_DEFAULT            0x00000000UL                             /**< Mode DEFAULT for SMU_M33CTRL                */
#define SMU_M33CTRL_LOCKNSMPU_DEFAULT             (_SMU_M33CTRL_LOCKNSMPU_DEFAULT << 3)    /**< Shifted mode DEFAULT for SMU_M33CTRL        */
#define SMU_M33CTRL_LOCKSAU                       (0x1UL << 4)                             /**< SAU LOCK bit                                */
#define _SMU_M33CTRL_LOCKSAU_SHIFT                4                                        /**< Shift value for SMU_LOCKSAU                 */
#define _SMU_M33CTRL_LOCKSAU_MASK                 0x10UL                                   /**< Bit mask for SMU_LOCKSAU                    */
#define _SMU_M33CTRL_LOCKSAU_DEFAULT              0x00000000UL                             /**< Mode DEFAULT for SMU_M33CTRL                */
#define SMU_M33CTRL_LOCKSAU_DEFAULT               (_SMU_M33CTRL_LOCKSAU_DEFAULT << 4)      /**< Shifted mode DEFAULT for SMU_M33CTRL        */

/* Bit fields for SMU PPUPATD0 */
#define _SMU_PPUPATD0_RESETVALUE                  0x00000000UL                               /**< Default value for SMU_PPUPATD0              */
#define _SMU_PPUPATD0_MASK                        0xFFFFFFFEUL                               /**< Mask for SMU_PPUPATD0                       */
#define SMU_PPUPATD0_EMU                          (0x1UL << 1)                               /**< EMU Privileged Access                       */
#define _SMU_PPUPATD0_EMU_SHIFT                   1                                          /**< Shift value for SMU_EMU                     */
#define _SMU_PPUPATD0_EMU_MASK                    0x2UL                                      /**< Bit mask for SMU_EMU                        */
#define _SMU_PPUPATD0_EMU_DEFAULT                 0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_EMU_DEFAULT                  (_SMU_PPUPATD0_EMU_DEFAULT << 1)           /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_CMU                          (0x1UL << 2)                               /**< CMU Privileged Access                       */
#define _SMU_PPUPATD0_CMU_SHIFT                   2                                          /**< Shift value for SMU_CMU                     */
#define _SMU_PPUPATD0_CMU_MASK                    0x4UL                                      /**< Bit mask for SMU_CMU                        */
#define _SMU_PPUPATD0_CMU_DEFAULT                 0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_CMU_DEFAULT                  (_SMU_PPUPATD0_CMU_DEFAULT << 2)           /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_HFXO0                        (0x1UL << 3)                               /**< HFXO0 Privileged Access                     */
#define _SMU_PPUPATD0_HFXO0_SHIFT                 3                                          /**< Shift value for SMU_HFXO0                   */
#define _SMU_PPUPATD0_HFXO0_MASK                  0x8UL                                      /**< Bit mask for SMU_HFXO0                      */
#define _SMU_PPUPATD0_HFXO0_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_HFXO0_DEFAULT                (_SMU_PPUPATD0_HFXO0_DEFAULT << 3)         /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_HFRCO0                       (0x1UL << 4)                               /**< HFRCO0 Privileged Access                    */
#define _SMU_PPUPATD0_HFRCO0_SHIFT                4                                          /**< Shift value for SMU_HFRCO0                  */
#define _SMU_PPUPATD0_HFRCO0_MASK                 0x10UL                                     /**< Bit mask for SMU_HFRCO0                     */
#define _SMU_PPUPATD0_HFRCO0_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_HFRCO0_DEFAULT               (_SMU_PPUPATD0_HFRCO0_DEFAULT << 4)        /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_FSRCO                        (0x1UL << 5)                               /**< FSRCO Privileged Access                     */
#define _SMU_PPUPATD0_FSRCO_SHIFT                 5                                          /**< Shift value for SMU_FSRCO                   */
#define _SMU_PPUPATD0_FSRCO_MASK                  0x20UL                                     /**< Bit mask for SMU_FSRCO                      */
#define _SMU_PPUPATD0_FSRCO_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_FSRCO_DEFAULT                (_SMU_PPUPATD0_FSRCO_DEFAULT << 5)         /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_DPLL0                        (0x1UL << 6)                               /**< DPLL0 Privileged Access                     */
#define _SMU_PPUPATD0_DPLL0_SHIFT                 6                                          /**< Shift value for SMU_DPLL0                   */
#define _SMU_PPUPATD0_DPLL0_MASK                  0x40UL                                     /**< Bit mask for SMU_DPLL0                      */
#define _SMU_PPUPATD0_DPLL0_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_DPLL0_DEFAULT                (_SMU_PPUPATD0_DPLL0_DEFAULT << 6)         /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_LFXO                         (0x1UL << 7)                               /**< LFXO Privileged Access                      */
#define _SMU_PPUPATD0_LFXO_SHIFT                  7                                          /**< Shift value for SMU_LFXO                    */
#define _SMU_PPUPATD0_LFXO_MASK                   0x80UL                                     /**< Bit mask for SMU_LFXO                       */
#define _SMU_PPUPATD0_LFXO_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_LFXO_DEFAULT                 (_SMU_PPUPATD0_LFXO_DEFAULT << 7)          /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_LFRCO                        (0x1UL << 8)                               /**< LFRCO Privileged Access                     */
#define _SMU_PPUPATD0_LFRCO_SHIFT                 8                                          /**< Shift value for SMU_LFRCO                   */
#define _SMU_PPUPATD0_LFRCO_MASK                  0x100UL                                    /**< Bit mask for SMU_LFRCO                      */
#define _SMU_PPUPATD0_LFRCO_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_LFRCO_DEFAULT                (_SMU_PPUPATD0_LFRCO_DEFAULT << 8)         /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_ULFRCO                       (0x1UL << 9)                               /**< ULFRCO Privileged Access                    */
#define _SMU_PPUPATD0_ULFRCO_SHIFT                9                                          /**< Shift value for SMU_ULFRCO                  */
#define _SMU_PPUPATD0_ULFRCO_MASK                 0x200UL                                    /**< Bit mask for SMU_ULFRCO                     */
#define _SMU_PPUPATD0_ULFRCO_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_ULFRCO_DEFAULT               (_SMU_PPUPATD0_ULFRCO_DEFAULT << 9)        /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_MSC                          (0x1UL << 10)                              /**< MSC Privileged Access                       */
#define _SMU_PPUPATD0_MSC_SHIFT                   10                                         /**< Shift value for SMU_MSC                     */
#define _SMU_PPUPATD0_MSC_MASK                    0x400UL                                    /**< Bit mask for SMU_MSC                        */
#define _SMU_PPUPATD0_MSC_DEFAULT                 0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_MSC_DEFAULT                  (_SMU_PPUPATD0_MSC_DEFAULT << 10)          /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_ICACHE0                      (0x1UL << 11)                              /**< ICACHE0 Privileged Access                   */
#define _SMU_PPUPATD0_ICACHE0_SHIFT               11                                         /**< Shift value for SMU_ICACHE0                 */
#define _SMU_PPUPATD0_ICACHE0_MASK                0x800UL                                    /**< Bit mask for SMU_ICACHE0                    */
#define _SMU_PPUPATD0_ICACHE0_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_ICACHE0_DEFAULT              (_SMU_PPUPATD0_ICACHE0_DEFAULT << 11)      /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_PRS                          (0x1UL << 12)                              /**< PRS Privileged Access                       */
#define _SMU_PPUPATD0_PRS_SHIFT                   12                                         /**< Shift value for SMU_PRS                     */
#define _SMU_PPUPATD0_PRS_MASK                    0x1000UL                                   /**< Bit mask for SMU_PRS                        */
#define _SMU_PPUPATD0_PRS_DEFAULT                 0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_PRS_DEFAULT                  (_SMU_PPUPATD0_PRS_DEFAULT << 12)          /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_GPIO                         (0x1UL << 13)                              /**< GPIO Privileged Access                      */
#define _SMU_PPUPATD0_GPIO_SHIFT                  13                                         /**< Shift value for SMU_GPIO                    */
#define _SMU_PPUPATD0_GPIO_MASK                   0x2000UL                                   /**< Bit mask for SMU_GPIO                       */
#define _SMU_PPUPATD0_GPIO_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_GPIO_DEFAULT                 (_SMU_PPUPATD0_GPIO_DEFAULT << 13)         /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_LDMA                         (0x1UL << 14)                              /**< LDMA Privileged Access                      */
#define _SMU_PPUPATD0_LDMA_SHIFT                  14                                         /**< Shift value for SMU_LDMA                    */
#define _SMU_PPUPATD0_LDMA_MASK                   0x4000UL                                   /**< Bit mask for SMU_LDMA                       */
#define _SMU_PPUPATD0_LDMA_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_LDMA_DEFAULT                 (_SMU_PPUPATD0_LDMA_DEFAULT << 14)         /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_LDMAXBAR                     (0x1UL << 15)                              /**< LDMAXBAR Privileged Access                  */
#define _SMU_PPUPATD0_LDMAXBAR_SHIFT              15                                         /**< Shift value for SMU_LDMAXBAR                */
#define _SMU_PPUPATD0_LDMAXBAR_MASK               0x8000UL                                   /**< Bit mask for SMU_LDMAXBAR                   */
#define _SMU_PPUPATD0_LDMAXBAR_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_LDMAXBAR_DEFAULT             (_SMU_PPUPATD0_LDMAXBAR_DEFAULT << 15)     /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_TIMER0                       (0x1UL << 16)                              /**< TIMER0 Privileged Access                    */
#define _SMU_PPUPATD0_TIMER0_SHIFT                16                                         /**< Shift value for SMU_TIMER0                  */
#define _SMU_PPUPATD0_TIMER0_MASK                 0x10000UL                                  /**< Bit mask for SMU_TIMER0                     */
#define _SMU_PPUPATD0_TIMER0_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_TIMER0_DEFAULT               (_SMU_PPUPATD0_TIMER0_DEFAULT << 16)       /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_TIMER1                       (0x1UL << 17)                              /**< TIMER1 Privileged Access                    */
#define _SMU_PPUPATD0_TIMER1_SHIFT                17                                         /**< Shift value for SMU_TIMER1                  */
#define _SMU_PPUPATD0_TIMER1_MASK                 0x20000UL                                  /**< Bit mask for SMU_TIMER1                     */
#define _SMU_PPUPATD0_TIMER1_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_TIMER1_DEFAULT               (_SMU_PPUPATD0_TIMER1_DEFAULT << 17)       /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_TIMER2                       (0x1UL << 18)                              /**< TIMER2 Privileged Access                    */
#define _SMU_PPUPATD0_TIMER2_SHIFT                18                                         /**< Shift value for SMU_TIMER2                  */
#define _SMU_PPUPATD0_TIMER2_MASK                 0x40000UL                                  /**< Bit mask for SMU_TIMER2                     */
#define _SMU_PPUPATD0_TIMER2_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_TIMER2_DEFAULT               (_SMU_PPUPATD0_TIMER2_DEFAULT << 18)       /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_TIMER3                       (0x1UL << 19)                              /**< TIMER3 Privileged Access                    */
#define _SMU_PPUPATD0_TIMER3_SHIFT                19                                         /**< Shift value for SMU_TIMER3                  */
#define _SMU_PPUPATD0_TIMER3_MASK                 0x80000UL                                  /**< Bit mask for SMU_TIMER3                     */
#define _SMU_PPUPATD0_TIMER3_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_TIMER3_DEFAULT               (_SMU_PPUPATD0_TIMER3_DEFAULT << 19)       /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_USART0                       (0x1UL << 20)                              /**< USART0 Privileged Access                    */
#define _SMU_PPUPATD0_USART0_SHIFT                20                                         /**< Shift value for SMU_USART0                  */
#define _SMU_PPUPATD0_USART0_MASK                 0x100000UL                                 /**< Bit mask for SMU_USART0                     */
#define _SMU_PPUPATD0_USART0_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_USART0_DEFAULT               (_SMU_PPUPATD0_USART0_DEFAULT << 20)       /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_USART1                       (0x1UL << 21)                              /**< USART1 Privileged Access                    */
#define _SMU_PPUPATD0_USART1_SHIFT                21                                         /**< Shift value for SMU_USART1                  */
#define _SMU_PPUPATD0_USART1_MASK                 0x200000UL                                 /**< Bit mask for SMU_USART1                     */
#define _SMU_PPUPATD0_USART1_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_USART1_DEFAULT               (_SMU_PPUPATD0_USART1_DEFAULT << 21)       /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_USART2                       (0x1UL << 22)                              /**< USART2 Privileged Access                    */
#define _SMU_PPUPATD0_USART2_SHIFT                22                                         /**< Shift value for SMU_USART2                  */
#define _SMU_PPUPATD0_USART2_MASK                 0x400000UL                                 /**< Bit mask for SMU_USART2                     */
#define _SMU_PPUPATD0_USART2_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_USART2_DEFAULT               (_SMU_PPUPATD0_USART2_DEFAULT << 22)       /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_BURTC                        (0x1UL << 23)                              /**< BURTC Privileged Access                     */
#define _SMU_PPUPATD0_BURTC_SHIFT                 23                                         /**< Shift value for SMU_BURTC                   */
#define _SMU_PPUPATD0_BURTC_MASK                  0x800000UL                                 /**< Bit mask for SMU_BURTC                      */
#define _SMU_PPUPATD0_BURTC_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_BURTC_DEFAULT                (_SMU_PPUPATD0_BURTC_DEFAULT << 23)        /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_I2C1                         (0x1UL << 24)                              /**< I2C1 Privileged Access                      */
#define _SMU_PPUPATD0_I2C1_SHIFT                  24                                         /**< Shift value for SMU_I2C1                    */
#define _SMU_PPUPATD0_I2C1_MASK                   0x1000000UL                                /**< Bit mask for SMU_I2C1                       */
#define _SMU_PPUPATD0_I2C1_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_I2C1_DEFAULT                 (_SMU_PPUPATD0_I2C1_DEFAULT << 24)         /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_CHIPTESTCTRL                 (0x1UL << 25)                              /**< CHIPTESTCTRL Privileged Access              */
#define _SMU_PPUPATD0_CHIPTESTCTRL_SHIFT          25                                         /**< Shift value for SMU_CHIPTESTCTRL            */
#define _SMU_PPUPATD0_CHIPTESTCTRL_MASK           0x2000000UL                                /**< Bit mask for SMU_CHIPTESTCTRL               */
#define _SMU_PPUPATD0_CHIPTESTCTRL_DEFAULT        0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_CHIPTESTCTRL_DEFAULT         (_SMU_PPUPATD0_CHIPTESTCTRL_DEFAULT << 25) /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_LVGD                         (0x1UL << 26)                              /**< LVGD Privileged Access                      */
#define _SMU_PPUPATD0_LVGD_SHIFT                  26                                         /**< Shift value for SMU_LVGD                    */
#define _SMU_PPUPATD0_LVGD_MASK                   0x4000000UL                                /**< Bit mask for SMU_LVGD                       */
#define _SMU_PPUPATD0_LVGD_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_LVGD_DEFAULT                 (_SMU_PPUPATD0_LVGD_DEFAULT << 26)         /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_SYSCFG                       (0x1UL << 27)                              /**< SYSCFG Privileged Access                    */
#define _SMU_PPUPATD0_SYSCFG_SHIFT                27                                         /**< Shift value for SMU_SYSCFG                  */
#define _SMU_PPUPATD0_SYSCFG_MASK                 0x8000000UL                                /**< Bit mask for SMU_SYSCFG                     */
#define _SMU_PPUPATD0_SYSCFG_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_SYSCFG_DEFAULT               (_SMU_PPUPATD0_SYSCFG_DEFAULT << 27)       /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_BURAM                        (0x1UL << 28)                              /**< BURAM Privileged Access                     */
#define _SMU_PPUPATD0_BURAM_SHIFT                 28                                         /**< Shift value for SMU_BURAM                   */
#define _SMU_PPUPATD0_BURAM_MASK                  0x10000000UL                               /**< Bit mask for SMU_BURAM                      */
#define _SMU_PPUPATD0_BURAM_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_BURAM_DEFAULT                (_SMU_PPUPATD0_BURAM_DEFAULT << 28)        /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_IFADCDEBUG                   (0x1UL << 29)                              /**< IFADCDEBUG Privileged Access                */
#define _SMU_PPUPATD0_IFADCDEBUG_SHIFT            29                                         /**< Shift value for SMU_IFADCDEBUG              */
#define _SMU_PPUPATD0_IFADCDEBUG_MASK             0x20000000UL                               /**< Bit mask for SMU_IFADCDEBUG                 */
#define _SMU_PPUPATD0_IFADCDEBUG_DEFAULT          0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_IFADCDEBUG_DEFAULT           (_SMU_PPUPATD0_IFADCDEBUG_DEFAULT << 29)   /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_GPCRC                        (0x1UL << 30)                              /**< GPCRC Privileged Access                     */
#define _SMU_PPUPATD0_GPCRC_SHIFT                 30                                         /**< Shift value for SMU_GPCRC                   */
#define _SMU_PPUPATD0_GPCRC_MASK                  0x40000000UL                               /**< Bit mask for SMU_GPCRC                      */
#define _SMU_PPUPATD0_GPCRC_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_GPCRC_DEFAULT                (_SMU_PPUPATD0_GPCRC_DEFAULT << 30)        /**< Shifted mode DEFAULT for SMU_PPUPATD0       */
#define SMU_PPUPATD0_RTCC                         (0x1UL << 31)                              /**< RTCC Privileged Access                      */
#define _SMU_PPUPATD0_RTCC_SHIFT                  31                                         /**< Shift value for SMU_RTCC                    */
#define _SMU_PPUPATD0_RTCC_MASK                   0x80000000UL                               /**< Bit mask for SMU_RTCC                       */
#define _SMU_PPUPATD0_RTCC_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for SMU_PPUPATD0               */
#define SMU_PPUPATD0_RTCC_DEFAULT                 (_SMU_PPUPATD0_RTCC_DEFAULT << 31)         /**< Shifted mode DEFAULT for SMU_PPUPATD0       */

/* Bit fields for SMU PPUPATD1 */
#define _SMU_PPUPATD1_RESETVALUE                  0x00000000UL                            /**< Default value for SMU_PPUPATD1              */
#define _SMU_PPUPATD1_MASK                        0x00003FFFUL                            /**< Mask for SMU_PPUPATD1                       */
#define SMU_PPUPATD1_LETIMER0                     (0x1UL << 0)                            /**< LETIMER0 Privileged Access                  */
#define _SMU_PPUPATD1_LETIMER0_SHIFT              0                                       /**< Shift value for SMU_LETIMER0                */
#define _SMU_PPUPATD1_LETIMER0_MASK               0x1UL                                   /**< Bit mask for SMU_LETIMER0                   */
#define _SMU_PPUPATD1_LETIMER0_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMU_PPUPATD1               */
#define SMU_PPUPATD1_LETIMER0_DEFAULT             (_SMU_PPUPATD1_LETIMER0_DEFAULT << 0)   /**< Shifted mode DEFAULT for SMU_PPUPATD1       */
#define SMU_PPUPATD1_IADC0                        (0x1UL << 1)                            /**< IADC0 Privileged Access                     */
#define _SMU_PPUPATD1_IADC0_SHIFT                 1                                       /**< Shift value for SMU_IADC0                   */
#define _SMU_PPUPATD1_IADC0_MASK                  0x2UL                                   /**< Bit mask for SMU_IADC0                      */
#define _SMU_PPUPATD1_IADC0_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for SMU_PPUPATD1               */
#define SMU_PPUPATD1_IADC0_DEFAULT                (_SMU_PPUPATD1_IADC0_DEFAULT << 1)      /**< Shifted mode DEFAULT for SMU_PPUPATD1       */
#define SMU_PPUPATD1_ACMP0                        (0x1UL << 2)                            /**< ACMP0 Privileged Access                     */
#define _SMU_PPUPATD1_ACMP0_SHIFT                 2                                       /**< Shift value for SMU_ACMP0                   */
#define _SMU_PPUPATD1_ACMP0_MASK                  0x4UL                                   /**< Bit mask for SMU_ACMP0                      */
#define _SMU_PPUPATD1_ACMP0_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for SMU_PPUPATD1               */
#define SMU_PPUPATD1_ACMP0_DEFAULT                (_SMU_PPUPATD1_ACMP0_DEFAULT << 2)      /**< Shifted mode DEFAULT for SMU_PPUPATD1       */
#define SMU_PPUPATD1_ACMP1                        (0x1UL << 3)                            /**< ACMP1 Privileged Access                     */
#define _SMU_PPUPATD1_ACMP1_SHIFT                 3                                       /**< Shift value for SMU_ACMP1                   */
#define _SMU_PPUPATD1_ACMP1_MASK                  0x8UL                                   /**< Bit mask for SMU_ACMP1                      */
#define _SMU_PPUPATD1_ACMP1_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for SMU_PPUPATD1               */
#define SMU_PPUPATD1_ACMP1_DEFAULT                (_SMU_PPUPATD1_ACMP1_DEFAULT << 3)      /**< Shifted mode DEFAULT for SMU_PPUPATD1       */
#define SMU_PPUPATD1_I2C0                         (0x1UL << 4)                            /**< I2C0 Privileged Access                      */
#define _SMU_PPUPATD1_I2C0_SHIFT                  4                                       /**< Shift value for SMU_I2C0                    */
#define _SMU_PPUPATD1_I2C0_MASK                   0x10UL                                  /**< Bit mask for SMU_I2C0                       */
#define _SMU_PPUPATD1_I2C0_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for SMU_PPUPATD1               */
#define SMU_PPUPATD1_I2C0_DEFAULT                 (_SMU_PPUPATD1_I2C0_DEFAULT << 4)       /**< Shifted mode DEFAULT for SMU_PPUPATD1       */
#define SMU_PPUPATD1_HFRCOEM23                    (0x1UL << 5)                            /**< HFRCOEM23 Privileged Access                 */
#define _SMU_PPUPATD1_HFRCOEM23_SHIFT             5                                       /**< Shift value for SMU_HFRCOEM23               */
#define _SMU_PPUPATD1_HFRCOEM23_MASK              0x20UL                                  /**< Bit mask for SMU_HFRCOEM23                  */
#define _SMU_PPUPATD1_HFRCOEM23_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMU_PPUPATD1               */
#define SMU_PPUPATD1_HFRCOEM23_DEFAULT            (_SMU_PPUPATD1_HFRCOEM23_DEFAULT << 5)  /**< Shifted mode DEFAULT for SMU_PPUPATD1       */
#define SMU_PPUPATD1_WDOG0                        (0x1UL << 6)                            /**< WDOG0 Privileged Access                     */
#define _SMU_PPUPATD1_WDOG0_SHIFT                 6                                       /**< Shift value for SMU_WDOG0                   */
#define _SMU_PPUPATD1_WDOG0_MASK                  0x40UL                                  /**< Bit mask for SMU_WDOG0                      */
#define _SMU_PPUPATD1_WDOG0_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for SMU_PPUPATD1               */
#define SMU_PPUPATD1_WDOG0_DEFAULT                (_SMU_PPUPATD1_WDOG0_DEFAULT << 6)      /**< Shifted mode DEFAULT for SMU_PPUPATD1       */
#define SMU_PPUPATD1_WDOG1                        (0x1UL << 7)                            /**< WDOG1 Privileged Access                     */
#define _SMU_PPUPATD1_WDOG1_SHIFT                 7                                       /**< Shift value for SMU_WDOG1                   */
#define _SMU_PPUPATD1_WDOG1_MASK                  0x80UL                                  /**< Bit mask for SMU_WDOG1                      */
#define _SMU_PPUPATD1_WDOG1_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for SMU_PPUPATD1               */
#define SMU_PPUPATD1_WDOG1_DEFAULT                (_SMU_PPUPATD1_WDOG1_DEFAULT << 7)      /**< Shifted mode DEFAULT for SMU_PPUPATD1       */
#define SMU_PPUPATD1_AMUXCP0                      (0x1UL << 8)                            /**< AMUXCP0 Privileged Access                   */
#define _SMU_PPUPATD1_AMUXCP0_SHIFT               8                                       /**< Shift value for SMU_AMUXCP0                 */
#define _SMU_PPUPATD1_AMUXCP0_MASK                0x100UL                                 /**< Bit mask for SMU_AMUXCP0                    */
#define _SMU_PPUPATD1_AMUXCP0_DEFAULT             0x00000000UL                            /**< Mode DEFAULT for SMU_PPUPATD1               */
#define SMU_PPUPATD1_AMUXCP0_DEFAULT              (_SMU_PPUPATD1_AMUXCP0_DEFAULT << 8)    /**< Shifted mode DEFAULT for SMU_PPUPATD1       */
#define SMU_PPUPATD1_RADIOAES                     (0x1UL << 9)                            /**< RADIOAES Privileged Access                  */
#define _SMU_PPUPATD1_RADIOAES_SHIFT              9                                       /**< Shift value for SMU_RADIOAES                */
#define _SMU_PPUPATD1_RADIOAES_MASK               0x200UL                                 /**< Bit mask for SMU_RADIOAES                   */
#define _SMU_PPUPATD1_RADIOAES_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMU_PPUPATD1               */
#define SMU_PPUPATD1_RADIOAES_DEFAULT             (_SMU_PPUPATD1_RADIOAES_DEFAULT << 9)   /**< Shifted mode DEFAULT for SMU_PPUPATD1       */
#define SMU_PPUPATD1_BUFC                         (0x1UL << 10)                           /**< BUFC Privileged Access                      */
#define _SMU_PPUPATD1_BUFC_SHIFT                  10                                      /**< Shift value for SMU_BUFC                    */
#define _SMU_PPUPATD1_BUFC_MASK                   0x400UL                                 /**< Bit mask for SMU_BUFC                       */
#define _SMU_PPUPATD1_BUFC_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for SMU_PPUPATD1               */
#define SMU_PPUPATD1_BUFC_DEFAULT                 (_SMU_PPUPATD1_BUFC_DEFAULT << 10)      /**< Shifted mode DEFAULT for SMU_PPUPATD1       */
#define SMU_PPUPATD1_SMU                          (0x1UL << 11)                           /**< SMU Privileged Access                       */
#define _SMU_PPUPATD1_SMU_SHIFT                   11                                      /**< Shift value for SMU_SMU                     */
#define _SMU_PPUPATD1_SMU_MASK                    0x800UL                                 /**< Bit mask for SMU_SMU                        */
#define _SMU_PPUPATD1_SMU_DEFAULT                 0x00000000UL                            /**< Mode DEFAULT for SMU_PPUPATD1               */
#define SMU_PPUPATD1_SMU_DEFAULT                  (_SMU_PPUPATD1_SMU_DEFAULT << 11)       /**< Shifted mode DEFAULT for SMU_PPUPATD1       */
#define SMU_PPUPATD1_AHBRADIO                     (0x1UL << 12)                           /**< AHBRADIO Privileged Access                  */
#define _SMU_PPUPATD1_AHBRADIO_SHIFT              12                                      /**< Shift value for SMU_AHBRADIO                */
#define _SMU_PPUPATD1_AHBRADIO_MASK               0x1000UL                                /**< Bit mask for SMU_AHBRADIO                   */
#define _SMU_PPUPATD1_AHBRADIO_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMU_PPUPATD1               */
#define SMU_PPUPATD1_AHBRADIO_DEFAULT             (_SMU_PPUPATD1_AHBRADIO_DEFAULT << 12)  /**< Shifted mode DEFAULT for SMU_PPUPATD1       */
#define SMU_PPUPATD1_SEMAILBOX                    (0x1UL << 13)                           /**< SE MAILBOX Privileged Access                */
#define _SMU_PPUPATD1_SEMAILBOX_SHIFT             13                                      /**< Shift value for SMU_SEMAILBOX               */
#define _SMU_PPUPATD1_SEMAILBOX_MASK              0x2000UL                                /**< Bit mask for SMU_SEMAILBOX                  */
#define _SMU_PPUPATD1_SEMAILBOX_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMU_PPUPATD1               */
#define SMU_PPUPATD1_SEMAILBOX_DEFAULT            (_SMU_PPUPATD1_SEMAILBOX_DEFAULT << 13) /**< Shifted mode DEFAULT for SMU_PPUPATD1       */

/* Bit fields for SMU PPUSATD0 */
#define _SMU_PPUSATD0_RESETVALUE                  0x00000000UL                               /**< Default value for SMU_PPUSATD0              */
#define _SMU_PPUSATD0_MASK                        0xFFFFFFFEUL                               /**< Mask for SMU_PPUSATD0                       */
#define SMU_PPUSATD0_EMU                          (0x1UL << 1)                               /**< EMU Secure Access                           */
#define _SMU_PPUSATD0_EMU_SHIFT                   1                                          /**< Shift value for SMU_EMU                     */
#define _SMU_PPUSATD0_EMU_MASK                    0x2UL                                      /**< Bit mask for SMU_EMU                        */
#define _SMU_PPUSATD0_EMU_DEFAULT                 0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_EMU_DEFAULT                  (_SMU_PPUSATD0_EMU_DEFAULT << 1)           /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_CMU                          (0x1UL << 2)                               /**< CMU Secure Access                           */
#define _SMU_PPUSATD0_CMU_SHIFT                   2                                          /**< Shift value for SMU_CMU                     */
#define _SMU_PPUSATD0_CMU_MASK                    0x4UL                                      /**< Bit mask for SMU_CMU                        */
#define _SMU_PPUSATD0_CMU_DEFAULT                 0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_CMU_DEFAULT                  (_SMU_PPUSATD0_CMU_DEFAULT << 2)           /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_HFXO0                        (0x1UL << 3)                               /**< HFXO0 Secure Access                         */
#define _SMU_PPUSATD0_HFXO0_SHIFT                 3                                          /**< Shift value for SMU_HFXO0                   */
#define _SMU_PPUSATD0_HFXO0_MASK                  0x8UL                                      /**< Bit mask for SMU_HFXO0                      */
#define _SMU_PPUSATD0_HFXO0_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_HFXO0_DEFAULT                (_SMU_PPUSATD0_HFXO0_DEFAULT << 3)         /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_HFRCO0                       (0x1UL << 4)                               /**< HFRCO0 Secure Access                        */
#define _SMU_PPUSATD0_HFRCO0_SHIFT                4                                          /**< Shift value for SMU_HFRCO0                  */
#define _SMU_PPUSATD0_HFRCO0_MASK                 0x10UL                                     /**< Bit mask for SMU_HFRCO0                     */
#define _SMU_PPUSATD0_HFRCO0_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_HFRCO0_DEFAULT               (_SMU_PPUSATD0_HFRCO0_DEFAULT << 4)        /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_FSRCO                        (0x1UL << 5)                               /**< FSRCO Secure Access                         */
#define _SMU_PPUSATD0_FSRCO_SHIFT                 5                                          /**< Shift value for SMU_FSRCO                   */
#define _SMU_PPUSATD0_FSRCO_MASK                  0x20UL                                     /**< Bit mask for SMU_FSRCO                      */
#define _SMU_PPUSATD0_FSRCO_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_FSRCO_DEFAULT                (_SMU_PPUSATD0_FSRCO_DEFAULT << 5)         /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_DPLL0                        (0x1UL << 6)                               /**< DPLL0 Secure Access                         */
#define _SMU_PPUSATD0_DPLL0_SHIFT                 6                                          /**< Shift value for SMU_DPLL0                   */
#define _SMU_PPUSATD0_DPLL0_MASK                  0x40UL                                     /**< Bit mask for SMU_DPLL0                      */
#define _SMU_PPUSATD0_DPLL0_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_DPLL0_DEFAULT                (_SMU_PPUSATD0_DPLL0_DEFAULT << 6)         /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_LFXO                         (0x1UL << 7)                               /**< LFXO Secure Access                          */
#define _SMU_PPUSATD0_LFXO_SHIFT                  7                                          /**< Shift value for SMU_LFXO                    */
#define _SMU_PPUSATD0_LFXO_MASK                   0x80UL                                     /**< Bit mask for SMU_LFXO                       */
#define _SMU_PPUSATD0_LFXO_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_LFXO_DEFAULT                 (_SMU_PPUSATD0_LFXO_DEFAULT << 7)          /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_LFRCO                        (0x1UL << 8)                               /**< LFRCO Secure Access                         */
#define _SMU_PPUSATD0_LFRCO_SHIFT                 8                                          /**< Shift value for SMU_LFRCO                   */
#define _SMU_PPUSATD0_LFRCO_MASK                  0x100UL                                    /**< Bit mask for SMU_LFRCO                      */
#define _SMU_PPUSATD0_LFRCO_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_LFRCO_DEFAULT                (_SMU_PPUSATD0_LFRCO_DEFAULT << 8)         /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_ULFRCO                       (0x1UL << 9)                               /**< ULFRCO Secure Access                        */
#define _SMU_PPUSATD0_ULFRCO_SHIFT                9                                          /**< Shift value for SMU_ULFRCO                  */
#define _SMU_PPUSATD0_ULFRCO_MASK                 0x200UL                                    /**< Bit mask for SMU_ULFRCO                     */
#define _SMU_PPUSATD0_ULFRCO_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_ULFRCO_DEFAULT               (_SMU_PPUSATD0_ULFRCO_DEFAULT << 9)        /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_MSC                          (0x1UL << 10)                              /**< MSC Secure Access                           */
#define _SMU_PPUSATD0_MSC_SHIFT                   10                                         /**< Shift value for SMU_MSC                     */
#define _SMU_PPUSATD0_MSC_MASK                    0x400UL                                    /**< Bit mask for SMU_MSC                        */
#define _SMU_PPUSATD0_MSC_DEFAULT                 0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_MSC_DEFAULT                  (_SMU_PPUSATD0_MSC_DEFAULT << 10)          /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_ICACHE0                      (0x1UL << 11)                              /**< ICACHE0 Secure Access                       */
#define _SMU_PPUSATD0_ICACHE0_SHIFT               11                                         /**< Shift value for SMU_ICACHE0                 */
#define _SMU_PPUSATD0_ICACHE0_MASK                0x800UL                                    /**< Bit mask for SMU_ICACHE0                    */
#define _SMU_PPUSATD0_ICACHE0_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_ICACHE0_DEFAULT              (_SMU_PPUSATD0_ICACHE0_DEFAULT << 11)      /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_PRS                          (0x1UL << 12)                              /**< PRS Secure Access                           */
#define _SMU_PPUSATD0_PRS_SHIFT                   12                                         /**< Shift value for SMU_PRS                     */
#define _SMU_PPUSATD0_PRS_MASK                    0x1000UL                                   /**< Bit mask for SMU_PRS                        */
#define _SMU_PPUSATD0_PRS_DEFAULT                 0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_PRS_DEFAULT                  (_SMU_PPUSATD0_PRS_DEFAULT << 12)          /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_GPIO                         (0x1UL << 13)                              /**< GPIO Secure Access                          */
#define _SMU_PPUSATD0_GPIO_SHIFT                  13                                         /**< Shift value for SMU_GPIO                    */
#define _SMU_PPUSATD0_GPIO_MASK                   0x2000UL                                   /**< Bit mask for SMU_GPIO                       */
#define _SMU_PPUSATD0_GPIO_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_GPIO_DEFAULT                 (_SMU_PPUSATD0_GPIO_DEFAULT << 13)         /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_LDMA                         (0x1UL << 14)                              /**< LDMA Secure Access                          */
#define _SMU_PPUSATD0_LDMA_SHIFT                  14                                         /**< Shift value for SMU_LDMA                    */
#define _SMU_PPUSATD0_LDMA_MASK                   0x4000UL                                   /**< Bit mask for SMU_LDMA                       */
#define _SMU_PPUSATD0_LDMA_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_LDMA_DEFAULT                 (_SMU_PPUSATD0_LDMA_DEFAULT << 14)         /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_LDMAXBAR                     (0x1UL << 15)                              /**< LDMAXBAR Secure Access                      */
#define _SMU_PPUSATD0_LDMAXBAR_SHIFT              15                                         /**< Shift value for SMU_LDMAXBAR                */
#define _SMU_PPUSATD0_LDMAXBAR_MASK               0x8000UL                                   /**< Bit mask for SMU_LDMAXBAR                   */
#define _SMU_PPUSATD0_LDMAXBAR_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_LDMAXBAR_DEFAULT             (_SMU_PPUSATD0_LDMAXBAR_DEFAULT << 15)     /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_TIMER0                       (0x1UL << 16)                              /**< TIMER0 Secure Access                        */
#define _SMU_PPUSATD0_TIMER0_SHIFT                16                                         /**< Shift value for SMU_TIMER0                  */
#define _SMU_PPUSATD0_TIMER0_MASK                 0x10000UL                                  /**< Bit mask for SMU_TIMER0                     */
#define _SMU_PPUSATD0_TIMER0_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_TIMER0_DEFAULT               (_SMU_PPUSATD0_TIMER0_DEFAULT << 16)       /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_TIMER1                       (0x1UL << 17)                              /**< TIMER1 Secure Access                        */
#define _SMU_PPUSATD0_TIMER1_SHIFT                17                                         /**< Shift value for SMU_TIMER1                  */
#define _SMU_PPUSATD0_TIMER1_MASK                 0x20000UL                                  /**< Bit mask for SMU_TIMER1                     */
#define _SMU_PPUSATD0_TIMER1_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_TIMER1_DEFAULT               (_SMU_PPUSATD0_TIMER1_DEFAULT << 17)       /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_TIMER2                       (0x1UL << 18)                              /**< TIMER2 Secure Access                        */
#define _SMU_PPUSATD0_TIMER2_SHIFT                18                                         /**< Shift value for SMU_TIMER2                  */
#define _SMU_PPUSATD0_TIMER2_MASK                 0x40000UL                                  /**< Bit mask for SMU_TIMER2                     */
#define _SMU_PPUSATD0_TIMER2_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_TIMER2_DEFAULT               (_SMU_PPUSATD0_TIMER2_DEFAULT << 18)       /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_TIMER3                       (0x1UL << 19)                              /**< TIMER3 Secure Access                        */
#define _SMU_PPUSATD0_TIMER3_SHIFT                19                                         /**< Shift value for SMU_TIMER3                  */
#define _SMU_PPUSATD0_TIMER3_MASK                 0x80000UL                                  /**< Bit mask for SMU_TIMER3                     */
#define _SMU_PPUSATD0_TIMER3_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_TIMER3_DEFAULT               (_SMU_PPUSATD0_TIMER3_DEFAULT << 19)       /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_USART0                       (0x1UL << 20)                              /**< USART0 Secure Access                        */
#define _SMU_PPUSATD0_USART0_SHIFT                20                                         /**< Shift value for SMU_USART0                  */
#define _SMU_PPUSATD0_USART0_MASK                 0x100000UL                                 /**< Bit mask for SMU_USART0                     */
#define _SMU_PPUSATD0_USART0_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_USART0_DEFAULT               (_SMU_PPUSATD0_USART0_DEFAULT << 20)       /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_USART1                       (0x1UL << 21)                              /**< USART1 Secure Access                        */
#define _SMU_PPUSATD0_USART1_SHIFT                21                                         /**< Shift value for SMU_USART1                  */
#define _SMU_PPUSATD0_USART1_MASK                 0x200000UL                                 /**< Bit mask for SMU_USART1                     */
#define _SMU_PPUSATD0_USART1_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_USART1_DEFAULT               (_SMU_PPUSATD0_USART1_DEFAULT << 21)       /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_USART2                       (0x1UL << 22)                              /**< USART2 Secure Access                        */
#define _SMU_PPUSATD0_USART2_SHIFT                22                                         /**< Shift value for SMU_USART2                  */
#define _SMU_PPUSATD0_USART2_MASK                 0x400000UL                                 /**< Bit mask for SMU_USART2                     */
#define _SMU_PPUSATD0_USART2_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_USART2_DEFAULT               (_SMU_PPUSATD0_USART2_DEFAULT << 22)       /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_BURTC                        (0x1UL << 23)                              /**< BURTC Secure Access                         */
#define _SMU_PPUSATD0_BURTC_SHIFT                 23                                         /**< Shift value for SMU_BURTC                   */
#define _SMU_PPUSATD0_BURTC_MASK                  0x800000UL                                 /**< Bit mask for SMU_BURTC                      */
#define _SMU_PPUSATD0_BURTC_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_BURTC_DEFAULT                (_SMU_PPUSATD0_BURTC_DEFAULT << 23)        /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_I2C1                         (0x1UL << 24)                              /**< I2C1 Secure Access                          */
#define _SMU_PPUSATD0_I2C1_SHIFT                  24                                         /**< Shift value for SMU_I2C1                    */
#define _SMU_PPUSATD0_I2C1_MASK                   0x1000000UL                                /**< Bit mask for SMU_I2C1                       */
#define _SMU_PPUSATD0_I2C1_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_I2C1_DEFAULT                 (_SMU_PPUSATD0_I2C1_DEFAULT << 24)         /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_CHIPTESTCTRL                 (0x1UL << 25)                              /**< CHIPTESTCTRL Secure Access                  */
#define _SMU_PPUSATD0_CHIPTESTCTRL_SHIFT          25                                         /**< Shift value for SMU_CHIPTESTCTRL            */
#define _SMU_PPUSATD0_CHIPTESTCTRL_MASK           0x2000000UL                                /**< Bit mask for SMU_CHIPTESTCTRL               */
#define _SMU_PPUSATD0_CHIPTESTCTRL_DEFAULT        0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_CHIPTESTCTRL_DEFAULT         (_SMU_PPUSATD0_CHIPTESTCTRL_DEFAULT << 25) /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_LVGD                         (0x1UL << 26)                              /**< LVGD Secure Access                          */
#define _SMU_PPUSATD0_LVGD_SHIFT                  26                                         /**< Shift value for SMU_LVGD                    */
#define _SMU_PPUSATD0_LVGD_MASK                   0x4000000UL                                /**< Bit mask for SMU_LVGD                       */
#define _SMU_PPUSATD0_LVGD_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_LVGD_DEFAULT                 (_SMU_PPUSATD0_LVGD_DEFAULT << 26)         /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_SYSCFG                       (0x1UL << 27)                              /**< SYSCFG Secure Access                        */
#define _SMU_PPUSATD0_SYSCFG_SHIFT                27                                         /**< Shift value for SMU_SYSCFG                  */
#define _SMU_PPUSATD0_SYSCFG_MASK                 0x8000000UL                                /**< Bit mask for SMU_SYSCFG                     */
#define _SMU_PPUSATD0_SYSCFG_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_SYSCFG_DEFAULT               (_SMU_PPUSATD0_SYSCFG_DEFAULT << 27)       /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_BURAM                        (0x1UL << 28)                              /**< BURAM Secure Access                         */
#define _SMU_PPUSATD0_BURAM_SHIFT                 28                                         /**< Shift value for SMU_BURAM                   */
#define _SMU_PPUSATD0_BURAM_MASK                  0x10000000UL                               /**< Bit mask for SMU_BURAM                      */
#define _SMU_PPUSATD0_BURAM_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_BURAM_DEFAULT                (_SMU_PPUSATD0_BURAM_DEFAULT << 28)        /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_IFADCDEBUG                   (0x1UL << 29)                              /**< IFADCDEBUG Secure Access                    */
#define _SMU_PPUSATD0_IFADCDEBUG_SHIFT            29                                         /**< Shift value for SMU_IFADCDEBUG              */
#define _SMU_PPUSATD0_IFADCDEBUG_MASK             0x20000000UL                               /**< Bit mask for SMU_IFADCDEBUG                 */
#define _SMU_PPUSATD0_IFADCDEBUG_DEFAULT          0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_IFADCDEBUG_DEFAULT           (_SMU_PPUSATD0_IFADCDEBUG_DEFAULT << 29)   /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_GPCRC                        (0x1UL << 30)                              /**< GPCRC Secure Access                         */
#define _SMU_PPUSATD0_GPCRC_SHIFT                 30                                         /**< Shift value for SMU_GPCRC                   */
#define _SMU_PPUSATD0_GPCRC_MASK                  0x40000000UL                               /**< Bit mask for SMU_GPCRC                      */
#define _SMU_PPUSATD0_GPCRC_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_GPCRC_DEFAULT                (_SMU_PPUSATD0_GPCRC_DEFAULT << 30)        /**< Shifted mode DEFAULT for SMU_PPUSATD0       */
#define SMU_PPUSATD0_RTCC                         (0x1UL << 31)                              /**< RTCC Secure Access                          */
#define _SMU_PPUSATD0_RTCC_SHIFT                  31                                         /**< Shift value for SMU_RTCC                    */
#define _SMU_PPUSATD0_RTCC_MASK                   0x80000000UL                               /**< Bit mask for SMU_RTCC                       */
#define _SMU_PPUSATD0_RTCC_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for SMU_PPUSATD0               */
#define SMU_PPUSATD0_RTCC_DEFAULT                 (_SMU_PPUSATD0_RTCC_DEFAULT << 31)         /**< Shifted mode DEFAULT for SMU_PPUSATD0       */

/* Bit fields for SMU PPUSATD1 */
#define _SMU_PPUSATD1_RESETVALUE                  0x00000000UL                            /**< Default value for SMU_PPUSATD1              */
#define _SMU_PPUSATD1_MASK                        0x00003FFFUL                            /**< Mask for SMU_PPUSATD1                       */
#define SMU_PPUSATD1_LETIMER0                     (0x1UL << 0)                            /**< LETIMER0 Secure Access                      */
#define _SMU_PPUSATD1_LETIMER0_SHIFT              0                                       /**< Shift value for SMU_LETIMER0                */
#define _SMU_PPUSATD1_LETIMER0_MASK               0x1UL                                   /**< Bit mask for SMU_LETIMER0                   */
#define _SMU_PPUSATD1_LETIMER0_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMU_PPUSATD1               */
#define SMU_PPUSATD1_LETIMER0_DEFAULT             (_SMU_PPUSATD1_LETIMER0_DEFAULT << 0)   /**< Shifted mode DEFAULT for SMU_PPUSATD1       */
#define SMU_PPUSATD1_IADC0                        (0x1UL << 1)                            /**< IADC0 Secure Access                         */
#define _SMU_PPUSATD1_IADC0_SHIFT                 1                                       /**< Shift value for SMU_IADC0                   */
#define _SMU_PPUSATD1_IADC0_MASK                  0x2UL                                   /**< Bit mask for SMU_IADC0                      */
#define _SMU_PPUSATD1_IADC0_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for SMU_PPUSATD1               */
#define SMU_PPUSATD1_IADC0_DEFAULT                (_SMU_PPUSATD1_IADC0_DEFAULT << 1)      /**< Shifted mode DEFAULT for SMU_PPUSATD1       */
#define SMU_PPUSATD1_ACMP0                        (0x1UL << 2)                            /**< ACMP0 Secure Access                         */
#define _SMU_PPUSATD1_ACMP0_SHIFT                 2                                       /**< Shift value for SMU_ACMP0                   */
#define _SMU_PPUSATD1_ACMP0_MASK                  0x4UL                                   /**< Bit mask for SMU_ACMP0                      */
#define _SMU_PPUSATD1_ACMP0_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for SMU_PPUSATD1               */
#define SMU_PPUSATD1_ACMP0_DEFAULT                (_SMU_PPUSATD1_ACMP0_DEFAULT << 2)      /**< Shifted mode DEFAULT for SMU_PPUSATD1       */
#define SMU_PPUSATD1_ACMP1                        (0x1UL << 3)                            /**< ACMP1 Secure Access                         */
#define _SMU_PPUSATD1_ACMP1_SHIFT                 3                                       /**< Shift value for SMU_ACMP1                   */
#define _SMU_PPUSATD1_ACMP1_MASK                  0x8UL                                   /**< Bit mask for SMU_ACMP1                      */
#define _SMU_PPUSATD1_ACMP1_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for SMU_PPUSATD1               */
#define SMU_PPUSATD1_ACMP1_DEFAULT                (_SMU_PPUSATD1_ACMP1_DEFAULT << 3)      /**< Shifted mode DEFAULT for SMU_PPUSATD1       */
#define SMU_PPUSATD1_I2C0                         (0x1UL << 4)                            /**< I2C0 Secure Access                          */
#define _SMU_PPUSATD1_I2C0_SHIFT                  4                                       /**< Shift value for SMU_I2C0                    */
#define _SMU_PPUSATD1_I2C0_MASK                   0x10UL                                  /**< Bit mask for SMU_I2C0                       */
#define _SMU_PPUSATD1_I2C0_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for SMU_PPUSATD1               */
#define SMU_PPUSATD1_I2C0_DEFAULT                 (_SMU_PPUSATD1_I2C0_DEFAULT << 4)       /**< Shifted mode DEFAULT for SMU_PPUSATD1       */
#define SMU_PPUSATD1_HFRCOEM23                    (0x1UL << 5)                            /**< HFRCOEM23 Secure Access                     */
#define _SMU_PPUSATD1_HFRCOEM23_SHIFT             5                                       /**< Shift value for SMU_HFRCOEM23               */
#define _SMU_PPUSATD1_HFRCOEM23_MASK              0x20UL                                  /**< Bit mask for SMU_HFRCOEM23                  */
#define _SMU_PPUSATD1_HFRCOEM23_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMU_PPUSATD1               */
#define SMU_PPUSATD1_HFRCOEM23_DEFAULT            (_SMU_PPUSATD1_HFRCOEM23_DEFAULT << 5)  /**< Shifted mode DEFAULT for SMU_PPUSATD1       */
#define SMU_PPUSATD1_WDOG0                        (0x1UL << 6)                            /**< WDOG0 Secure Access                         */
#define _SMU_PPUSATD1_WDOG0_SHIFT                 6                                       /**< Shift value for SMU_WDOG0                   */
#define _SMU_PPUSATD1_WDOG0_MASK                  0x40UL                                  /**< Bit mask for SMU_WDOG0                      */
#define _SMU_PPUSATD1_WDOG0_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for SMU_PPUSATD1               */
#define SMU_PPUSATD1_WDOG0_DEFAULT                (_SMU_PPUSATD1_WDOG0_DEFAULT << 6)      /**< Shifted mode DEFAULT for SMU_PPUSATD1       */
#define SMU_PPUSATD1_WDOG1                        (0x1UL << 7)                            /**< WDOG1 Secure Access                         */
#define _SMU_PPUSATD1_WDOG1_SHIFT                 7                                       /**< Shift value for SMU_WDOG1                   */
#define _SMU_PPUSATD1_WDOG1_MASK                  0x80UL                                  /**< Bit mask for SMU_WDOG1                      */
#define _SMU_PPUSATD1_WDOG1_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for SMU_PPUSATD1               */
#define SMU_PPUSATD1_WDOG1_DEFAULT                (_SMU_PPUSATD1_WDOG1_DEFAULT << 7)      /**< Shifted mode DEFAULT for SMU_PPUSATD1       */
#define SMU_PPUSATD1_AMUXCP0                      (0x1UL << 8)                            /**< AMUXCP0 Secure Access                       */
#define _SMU_PPUSATD1_AMUXCP0_SHIFT               8                                       /**< Shift value for SMU_AMUXCP0                 */
#define _SMU_PPUSATD1_AMUXCP0_MASK                0x100UL                                 /**< Bit mask for SMU_AMUXCP0                    */
#define _SMU_PPUSATD1_AMUXCP0_DEFAULT             0x00000000UL                            /**< Mode DEFAULT for SMU_PPUSATD1               */
#define SMU_PPUSATD1_AMUXCP0_DEFAULT              (_SMU_PPUSATD1_AMUXCP0_DEFAULT << 8)    /**< Shifted mode DEFAULT for SMU_PPUSATD1       */
#define SMU_PPUSATD1_RADIOAES                     (0x1UL << 9)                            /**< RADIOAES Secure Access                      */
#define _SMU_PPUSATD1_RADIOAES_SHIFT              9                                       /**< Shift value for SMU_RADIOAES                */
#define _SMU_PPUSATD1_RADIOAES_MASK               0x200UL                                 /**< Bit mask for SMU_RADIOAES                   */
#define _SMU_PPUSATD1_RADIOAES_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMU_PPUSATD1               */
#define SMU_PPUSATD1_RADIOAES_DEFAULT             (_SMU_PPUSATD1_RADIOAES_DEFAULT << 9)   /**< Shifted mode DEFAULT for SMU_PPUSATD1       */
#define SMU_PPUSATD1_BUFC                         (0x1UL << 10)                           /**< BUFC Secure Access                          */
#define _SMU_PPUSATD1_BUFC_SHIFT                  10                                      /**< Shift value for SMU_BUFC                    */
#define _SMU_PPUSATD1_BUFC_MASK                   0x400UL                                 /**< Bit mask for SMU_BUFC                       */
#define _SMU_PPUSATD1_BUFC_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for SMU_PPUSATD1               */
#define SMU_PPUSATD1_BUFC_DEFAULT                 (_SMU_PPUSATD1_BUFC_DEFAULT << 10)      /**< Shifted mode DEFAULT for SMU_PPUSATD1       */
#define SMU_PPUSATD1_SMU                          (0x1UL << 11)                           /**< SMU Secure Access                           */
#define _SMU_PPUSATD1_SMU_SHIFT                   11                                      /**< Shift value for SMU_SMU                     */
#define _SMU_PPUSATD1_SMU_MASK                    0x800UL                                 /**< Bit mask for SMU_SMU                        */
#define _SMU_PPUSATD1_SMU_DEFAULT                 0x00000000UL                            /**< Mode DEFAULT for SMU_PPUSATD1               */
#define SMU_PPUSATD1_SMU_DEFAULT                  (_SMU_PPUSATD1_SMU_DEFAULT << 11)       /**< Shifted mode DEFAULT for SMU_PPUSATD1       */
#define SMU_PPUSATD1_AHBRADIO                     (0x1UL << 12)                           /**< AHBRADIO Secure Access                      */
#define _SMU_PPUSATD1_AHBRADIO_SHIFT              12                                      /**< Shift value for SMU_AHBRADIO                */
#define _SMU_PPUSATD1_AHBRADIO_MASK               0x1000UL                                /**< Bit mask for SMU_AHBRADIO                   */
#define _SMU_PPUSATD1_AHBRADIO_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMU_PPUSATD1               */
#define SMU_PPUSATD1_AHBRADIO_DEFAULT             (_SMU_PPUSATD1_AHBRADIO_DEFAULT << 12)  /**< Shifted mode DEFAULT for SMU_PPUSATD1       */
#define SMU_PPUSATD1_SEMAILBOX                    (0x1UL << 13)                           /**< SE MAILBOX Secure Access                    */
#define _SMU_PPUSATD1_SEMAILBOX_SHIFT             13                                      /**< Shift value for SMU_SEMAILBOX               */
#define _SMU_PPUSATD1_SEMAILBOX_MASK              0x2000UL                                /**< Bit mask for SMU_SEMAILBOX                  */
#define _SMU_PPUSATD1_SEMAILBOX_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMU_PPUSATD1               */
#define SMU_PPUSATD1_SEMAILBOX_DEFAULT            (_SMU_PPUSATD1_SEMAILBOX_DEFAULT << 13) /**< Shifted mode DEFAULT for SMU_PPUSATD1       */

/* Bit fields for SMU PPUFS */
#define _SMU_PPUFS_RESETVALUE                     0x00000000UL                            /**< Default value for SMU_PPUFS                 */
#define _SMU_PPUFS_MASK                           0x000000FFUL                            /**< Mask for SMU_PPUFS                          */
#define _SMU_PPUFS_PPUFSPERIPHID_SHIFT            0                                       /**< Shift value for SMU_PPUFSPERIPHID           */
#define _SMU_PPUFS_PPUFSPERIPHID_MASK             0xFFUL                                  /**< Bit mask for SMU_PPUFSPERIPHID              */
#define _SMU_PPUFS_PPUFSPERIPHID_DEFAULT          0x00000000UL                            /**< Mode DEFAULT for SMU_PPUFS                  */
#define SMU_PPUFS_PPUFSPERIPHID_DEFAULT           (_SMU_PPUFS_PPUFSPERIPHID_DEFAULT << 0) /**< Shifted mode DEFAULT for SMU_PPUFS          */

/* Bit fields for SMU BMPUPATD0 */
#define _SMU_BMPUPATD0_RESETVALUE                 0x0000003FUL                                  /**< Default value for SMU_BMPUPATD0             */
#define _SMU_BMPUPATD0_MASK                       0x0000003FUL                                  /**< Mask for SMU_BMPUPATD0                      */
#define SMU_BMPUPATD0_RADIOAES                    (0x1UL << 0)                                  /**< RADIO AES DMA privileged mode               */
#define _SMU_BMPUPATD0_RADIOAES_SHIFT             0                                             /**< Shift value for SMU_RADIOAES                */
#define _SMU_BMPUPATD0_RADIOAES_MASK              0x1UL                                         /**< Bit mask for SMU_RADIOAES                   */
#define _SMU_BMPUPATD0_RADIOAES_DEFAULT           0x00000001UL                                  /**< Mode DEFAULT for SMU_BMPUPATD0              */
#define SMU_BMPUPATD0_RADIOAES_DEFAULT            (_SMU_BMPUPATD0_RADIOAES_DEFAULT << 0)        /**< Shifted mode DEFAULT for SMU_BMPUPATD0      */
#define SMU_BMPUPATD0_RADIOSUBSYSTEM              (0x1UL << 1)                                  /**< RADIO subsystem masters privileged mode     */
#define _SMU_BMPUPATD0_RADIOSUBSYSTEM_SHIFT       1                                             /**< Shift value for SMU_RADIOSUBSYSTEM          */
#define _SMU_BMPUPATD0_RADIOSUBSYSTEM_MASK        0x2UL                                         /**< Bit mask for SMU_RADIOSUBSYSTEM             */
#define _SMU_BMPUPATD0_RADIOSUBSYSTEM_DEFAULT     0x00000001UL                                  /**< Mode DEFAULT for SMU_BMPUPATD0              */
#define SMU_BMPUPATD0_RADIOSUBSYSTEM_DEFAULT      (_SMU_BMPUPATD0_RADIOSUBSYSTEM_DEFAULT << 1)  /**< Shifted mode DEFAULT for SMU_BMPUPATD0      */
#define SMU_BMPUPATD0_BUFC                        (0x1UL << 2)                                  /**< RADIO BUFFER controller privileged mode     */
#define _SMU_BMPUPATD0_BUFC_SHIFT                 2                                             /**< Shift value for SMU_BUFC                    */
#define _SMU_BMPUPATD0_BUFC_MASK                  0x4UL                                         /**< Bit mask for SMU_BUFC                       */
#define _SMU_BMPUPATD0_BUFC_DEFAULT               0x00000001UL                                  /**< Mode DEFAULT for SMU_BMPUPATD0              */
#define SMU_BMPUPATD0_BUFC_DEFAULT                (_SMU_BMPUPATD0_BUFC_DEFAULT << 2)            /**< Shifted mode DEFAULT for SMU_BMPUPATD0      */
#define SMU_BMPUPATD0_RADIOIFADCDEBUG             (0x1UL << 3)                                  /**< RADIO IFADC debug privileged mode           */
#define _SMU_BMPUPATD0_RADIOIFADCDEBUG_SHIFT      3                                             /**< Shift value for SMU_RADIOIFADCDEBUG         */
#define _SMU_BMPUPATD0_RADIOIFADCDEBUG_MASK       0x8UL                                         /**< Bit mask for SMU_RADIOIFADCDEBUG            */
#define _SMU_BMPUPATD0_RADIOIFADCDEBUG_DEFAULT    0x00000001UL                                  /**< Mode DEFAULT for SMU_BMPUPATD0              */
#define SMU_BMPUPATD0_RADIOIFADCDEBUG_DEFAULT     (_SMU_BMPUPATD0_RADIOIFADCDEBUG_DEFAULT << 3) /**< Shifted mode DEFAULT for SMU_BMPUPATD0      */
#define SMU_BMPUPATD0_LDMA                        (0x1UL << 4)                                  /**< MCU LDMA privileged mode                    */
#define _SMU_BMPUPATD0_LDMA_SHIFT                 4                                             /**< Shift value for SMU_LDMA                    */
#define _SMU_BMPUPATD0_LDMA_MASK                  0x10UL                                        /**< Bit mask for SMU_LDMA                       */
#define _SMU_BMPUPATD0_LDMA_DEFAULT               0x00000001UL                                  /**< Mode DEFAULT for SMU_BMPUPATD0              */
#define SMU_BMPUPATD0_LDMA_DEFAULT                (_SMU_BMPUPATD0_LDMA_DEFAULT << 4)            /**< Shifted mode DEFAULT for SMU_BMPUPATD0      */
#define SMU_BMPUPATD0_SEDMA                       (0x1UL << 5)                                  /**< SE mailbox DMA privileged mode              */
#define _SMU_BMPUPATD0_SEDMA_SHIFT                5                                             /**< Shift value for SMU_SEDMA                   */
#define _SMU_BMPUPATD0_SEDMA_MASK                 0x20UL                                        /**< Bit mask for SMU_SEDMA                      */
#define _SMU_BMPUPATD0_SEDMA_DEFAULT              0x00000001UL                                  /**< Mode DEFAULT for SMU_BMPUPATD0              */
#define SMU_BMPUPATD0_SEDMA_DEFAULT               (_SMU_BMPUPATD0_SEDMA_DEFAULT << 5)           /**< Shifted mode DEFAULT for SMU_BMPUPATD0      */

/* Bit fields for SMU BMPUSATD0 */
#define _SMU_BMPUSATD0_RESETVALUE                 0x0000003FUL                                  /**< Default value for SMU_BMPUSATD0             */
#define _SMU_BMPUSATD0_MASK                       0x0000003FUL                                  /**< Mask for SMU_BMPUSATD0                      */
#define SMU_BMPUSATD0_RADIOAES                    (0x1UL << 0)                                  /**< RADIO AES DMA secure mode                   */
#define _SMU_BMPUSATD0_RADIOAES_SHIFT             0                                             /**< Shift value for SMU_RADIOAES                */
#define _SMU_BMPUSATD0_RADIOAES_MASK              0x1UL                                         /**< Bit mask for SMU_RADIOAES                   */
#define _SMU_BMPUSATD0_RADIOAES_DEFAULT           0x00000001UL                                  /**< Mode DEFAULT for SMU_BMPUSATD0              */
#define SMU_BMPUSATD0_RADIOAES_DEFAULT            (_SMU_BMPUSATD0_RADIOAES_DEFAULT << 0)        /**< Shifted mode DEFAULT for SMU_BMPUSATD0      */
#define SMU_BMPUSATD0_RADIOSUBSYSTEM              (0x1UL << 1)                                  /**< RADIO subsystem masters secure mode         */
#define _SMU_BMPUSATD0_RADIOSUBSYSTEM_SHIFT       1                                             /**< Shift value for SMU_RADIOSUBSYSTEM          */
#define _SMU_BMPUSATD0_RADIOSUBSYSTEM_MASK        0x2UL                                         /**< Bit mask for SMU_RADIOSUBSYSTEM             */
#define _SMU_BMPUSATD0_RADIOSUBSYSTEM_DEFAULT     0x00000001UL                                  /**< Mode DEFAULT for SMU_BMPUSATD0              */
#define SMU_BMPUSATD0_RADIOSUBSYSTEM_DEFAULT      (_SMU_BMPUSATD0_RADIOSUBSYSTEM_DEFAULT << 1)  /**< Shifted mode DEFAULT for SMU_BMPUSATD0      */
#define SMU_BMPUSATD0_BUFC                        (0x1UL << 2)                                  /**< RADIO BUFFER controller secure mode         */
#define _SMU_BMPUSATD0_BUFC_SHIFT                 2                                             /**< Shift value for SMU_BUFC                    */
#define _SMU_BMPUSATD0_BUFC_MASK                  0x4UL                                         /**< Bit mask for SMU_BUFC                       */
#define _SMU_BMPUSATD0_BUFC_DEFAULT               0x00000001UL                                  /**< Mode DEFAULT for SMU_BMPUSATD0              */
#define SMU_BMPUSATD0_BUFC_DEFAULT                (_SMU_BMPUSATD0_BUFC_DEFAULT << 2)            /**< Shifted mode DEFAULT for SMU_BMPUSATD0      */
#define SMU_BMPUSATD0_RADIOIFADCDEBUG             (0x1UL << 3)                                  /**< RADIO IFADC debug secure mode               */
#define _SMU_BMPUSATD0_RADIOIFADCDEBUG_SHIFT      3                                             /**< Shift value for SMU_RADIOIFADCDEBUG         */
#define _SMU_BMPUSATD0_RADIOIFADCDEBUG_MASK       0x8UL                                         /**< Bit mask for SMU_RADIOIFADCDEBUG            */
#define _SMU_BMPUSATD0_RADIOIFADCDEBUG_DEFAULT    0x00000001UL                                  /**< Mode DEFAULT for SMU_BMPUSATD0              */
#define SMU_BMPUSATD0_RADIOIFADCDEBUG_DEFAULT     (_SMU_BMPUSATD0_RADIOIFADCDEBUG_DEFAULT << 3) /**< Shifted mode DEFAULT for SMU_BMPUSATD0      */
#define SMU_BMPUSATD0_LDMA                        (0x1UL << 4)                                  /**< MCU LDMA secure mode                        */
#define _SMU_BMPUSATD0_LDMA_SHIFT                 4                                             /**< Shift value for SMU_LDMA                    */
#define _SMU_BMPUSATD0_LDMA_MASK                  0x10UL                                        /**< Bit mask for SMU_LDMA                       */
#define _SMU_BMPUSATD0_LDMA_DEFAULT               0x00000001UL                                  /**< Mode DEFAULT for SMU_BMPUSATD0              */
#define SMU_BMPUSATD0_LDMA_DEFAULT                (_SMU_BMPUSATD0_LDMA_DEFAULT << 4)            /**< Shifted mode DEFAULT for SMU_BMPUSATD0      */
#define SMU_BMPUSATD0_SEDMA                       (0x1UL << 5)                                  /**< MCU to SE mailbox DMA secure mode           */
#define _SMU_BMPUSATD0_SEDMA_SHIFT                5                                             /**< Shift value for SMU_SEDMA                   */
#define _SMU_BMPUSATD0_SEDMA_MASK                 0x20UL                                        /**< Bit mask for SMU_SEDMA                      */
#define _SMU_BMPUSATD0_SEDMA_DEFAULT              0x00000001UL                                  /**< Mode DEFAULT for SMU_BMPUSATD0              */
#define SMU_BMPUSATD0_SEDMA_DEFAULT               (_SMU_BMPUSATD0_SEDMA_DEFAULT << 5)           /**< Shifted mode DEFAULT for SMU_BMPUSATD0      */

/* Bit fields for SMU BMPUFS */
#define _SMU_BMPUFS_RESETVALUE                    0x00000000UL                              /**< Default value for SMU_BMPUFS                */
#define _SMU_BMPUFS_MASK                          0x000000FFUL                              /**< Mask for SMU_BMPUFS                         */
#define _SMU_BMPUFS_BMPUFSMASTERID_SHIFT          0                                         /**< Shift value for SMU_BMPUFSMASTERID          */
#define _SMU_BMPUFS_BMPUFSMASTERID_MASK           0xFFUL                                    /**< Bit mask for SMU_BMPUFSMASTERID             */
#define _SMU_BMPUFS_BMPUFSMASTERID_DEFAULT        0x00000000UL                              /**< Mode DEFAULT for SMU_BMPUFS                 */
#define SMU_BMPUFS_BMPUFSMASTERID_DEFAULT         (_SMU_BMPUFS_BMPUFSMASTERID_DEFAULT << 0) /**< Shifted mode DEFAULT for SMU_BMPUFS         */

/* Bit fields for SMU BMPUFSADDR */
#define _SMU_BMPUFSADDR_RESETVALUE                0x00000000UL                              /**< Default value for SMU_BMPUFSADDR            */
#define _SMU_BMPUFSADDR_MASK                      0xFFFFFFFFUL                              /**< Mask for SMU_BMPUFSADDR                     */
#define _SMU_BMPUFSADDR_BMPUFSADDR_SHIFT          0                                         /**< Shift value for SMU_BMPUFSADDR              */
#define _SMU_BMPUFSADDR_BMPUFSADDR_MASK           0xFFFFFFFFUL                              /**< Bit mask for SMU_BMPUFSADDR                 */
#define _SMU_BMPUFSADDR_BMPUFSADDR_DEFAULT        0x00000000UL                              /**< Mode DEFAULT for SMU_BMPUFSADDR             */
#define SMU_BMPUFSADDR_BMPUFSADDR_DEFAULT         (_SMU_BMPUFSADDR_BMPUFSADDR_DEFAULT << 0) /**< Shifted mode DEFAULT for SMU_BMPUFSADDR     */

/* Bit fields for SMU ESAURTYPES0 */
#define _SMU_ESAURTYPES0_RESETVALUE               0x00000000UL                              /**< Default value for SMU_ESAURTYPES0           */
#define _SMU_ESAURTYPES0_MASK                     0x00001000UL                              /**< Mask for SMU_ESAURTYPES0                    */
#define SMU_ESAURTYPES0_ESAUR3NS                  (0x1UL << 12)                             /**< Region 3 Non-Secure                         */
#define _SMU_ESAURTYPES0_ESAUR3NS_SHIFT           12                                        /**< Shift value for SMU_ESAUR3NS                */
#define _SMU_ESAURTYPES0_ESAUR3NS_MASK            0x1000UL                                  /**< Bit mask for SMU_ESAUR3NS                   */
#define _SMU_ESAURTYPES0_ESAUR3NS_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMU_ESAURTYPES0            */
#define SMU_ESAURTYPES0_ESAUR3NS_DEFAULT          (_SMU_ESAURTYPES0_ESAUR3NS_DEFAULT << 12) /**< Shifted mode DEFAULT for SMU_ESAURTYPES0    */

/* Bit fields for SMU ESAURTYPES1 */
#define _SMU_ESAURTYPES1_RESETVALUE               0x00000000UL                               /**< Default value for SMU_ESAURTYPES1           */
#define _SMU_ESAURTYPES1_MASK                     0x00001000UL                               /**< Mask for SMU_ESAURTYPES1                    */
#define SMU_ESAURTYPES1_ESAUR11NS                 (0x1UL << 12)                              /**< Region 11 Non-Secure                        */
#define _SMU_ESAURTYPES1_ESAUR11NS_SHIFT          12                                         /**< Shift value for SMU_ESAUR11NS               */
#define _SMU_ESAURTYPES1_ESAUR11NS_MASK           0x1000UL                                   /**< Bit mask for SMU_ESAUR11NS                  */
#define _SMU_ESAURTYPES1_ESAUR11NS_DEFAULT        0x00000000UL                               /**< Mode DEFAULT for SMU_ESAURTYPES1            */
#define SMU_ESAURTYPES1_ESAUR11NS_DEFAULT         (_SMU_ESAURTYPES1_ESAUR11NS_DEFAULT << 12) /**< Shifted mode DEFAULT for SMU_ESAURTYPES1    */

/* Bit fields for SMU ESAUMRB01 */
#define _SMU_ESAUMRB01_RESETVALUE                 0x02000000UL                             /**< Default value for SMU_ESAUMRB01             */
#define _SMU_ESAUMRB01_MASK                       0x0FFFF000UL                             /**< Mask for SMU_ESAUMRB01                      */
#define _SMU_ESAUMRB01_ESAUMRB01_SHIFT            12                                       /**< Shift value for SMU_ESAUMRB01               */
#define _SMU_ESAUMRB01_ESAUMRB01_MASK             0xFFFF000UL                              /**< Bit mask for SMU_ESAUMRB01                  */
#define _SMU_ESAUMRB01_ESAUMRB01_DEFAULT          0x00002000UL                             /**< Mode DEFAULT for SMU_ESAUMRB01              */
#define SMU_ESAUMRB01_ESAUMRB01_DEFAULT           (_SMU_ESAUMRB01_ESAUMRB01_DEFAULT << 12) /**< Shifted mode DEFAULT for SMU_ESAUMRB01      */

/* Bit fields for SMU ESAUMRB12 */
#define _SMU_ESAUMRB12_RESETVALUE                 0x04000000UL                             /**< Default value for SMU_ESAUMRB12             */
#define _SMU_ESAUMRB12_MASK                       0x0FFFF000UL                             /**< Mask for SMU_ESAUMRB12                      */
#define _SMU_ESAUMRB12_ESAUMRB12_SHIFT            12                                       /**< Shift value for SMU_ESAUMRB12               */
#define _SMU_ESAUMRB12_ESAUMRB12_MASK             0xFFFF000UL                              /**< Bit mask for SMU_ESAUMRB12                  */
#define _SMU_ESAUMRB12_ESAUMRB12_DEFAULT          0x00004000UL                             /**< Mode DEFAULT for SMU_ESAUMRB12              */
#define SMU_ESAUMRB12_ESAUMRB12_DEFAULT           (_SMU_ESAUMRB12_ESAUMRB12_DEFAULT << 12) /**< Shifted mode DEFAULT for SMU_ESAUMRB12      */

/* Bit fields for SMU ESAUMRB45 */
#define _SMU_ESAUMRB45_RESETVALUE                 0x02000000UL                             /**< Default value for SMU_ESAUMRB45             */
#define _SMU_ESAUMRB45_MASK                       0x0FFFF000UL                             /**< Mask for SMU_ESAUMRB45                      */
#define _SMU_ESAUMRB45_ESAUMRB45_SHIFT            12                                       /**< Shift value for SMU_ESAUMRB45               */
#define _SMU_ESAUMRB45_ESAUMRB45_MASK             0xFFFF000UL                              /**< Bit mask for SMU_ESAUMRB45                  */
#define _SMU_ESAUMRB45_ESAUMRB45_DEFAULT          0x00002000UL                             /**< Mode DEFAULT for SMU_ESAUMRB45              */
#define SMU_ESAUMRB45_ESAUMRB45_DEFAULT           (_SMU_ESAUMRB45_ESAUMRB45_DEFAULT << 12) /**< Shifted mode DEFAULT for SMU_ESAUMRB45      */

/* Bit fields for SMU ESAUMRB56 */
#define _SMU_ESAUMRB56_RESETVALUE                 0x04000000UL                             /**< Default value for SMU_ESAUMRB56             */
#define _SMU_ESAUMRB56_MASK                       0x0FFFF000UL                             /**< Mask for SMU_ESAUMRB56                      */
#define _SMU_ESAUMRB56_ESAUMRB56_SHIFT            12                                       /**< Shift value for SMU_ESAUMRB56               */
#define _SMU_ESAUMRB56_ESAUMRB56_MASK             0xFFFF000UL                              /**< Bit mask for SMU_ESAUMRB56                  */
#define _SMU_ESAUMRB56_ESAUMRB56_DEFAULT          0x00004000UL                             /**< Mode DEFAULT for SMU_ESAUMRB56              */
#define SMU_ESAUMRB56_ESAUMRB56_DEFAULT           (_SMU_ESAUMRB56_ESAUMRB56_DEFAULT << 12) /**< Shifted mode DEFAULT for SMU_ESAUMRB56      */

/** @} End of group EFR32MG21_SMU_BitFields */
/** @} End of group EFR32MG21_SMU */
/** @} End of group Parts */

#endif /* EFR32MG21_SMU_H */
