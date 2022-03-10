/**************************************************************************//**
 * @file
 * @brief EFR32FG25 ECAIF register and bit field definitions
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
#ifndef EFR32FG25_ECAIF_H
#define EFR32FG25_ECAIF_H
#define ECAIF_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_ECAIF ECAIF
 * @{
 * @brief EFR32FG25 ECAIF Register Declaration.
 *****************************************************************************/

/** ECAIF FIFOIN Register Group Declaration. */
typedef struct {
  __IOM uint32_t FIFOIN;                             /**< New Register                                       */
} ECAIF_FIFOIN_TypeDef;

/** ECAIF FMTIN Register Group Declaration. */
typedef struct {
  uint32_t RESERVED0[1U];                            /**< Reserved for future use                            */
} ECAIF_FMTIN_TypeDef;

/** ECAIF Register Declaration. */
typedef struct {
  __IM uint32_t        IPVERSION;               /**< IP Version ID                                      */
  __IOM uint32_t       EN;                      /**< Module Enable                                      */
  __IOM uint32_t       SWRST;                   /**< Software Reset                                     */
  __IOM uint32_t       CONNECT;                 /**< New Register                                       */
  __IOM uint32_t       DISCLK;                  /**< New Register                                       */
  uint32_t             RESERVED0[3U];           /**< Reserved for future use                            */
  ECAIF_FIFOIN_TypeDef FIFOIN[2U];              /**<                                                    */
  uint32_t             RESERVED1[6U];           /**< Reserved for future use                            */
  uint32_t             RESERVED2[1U];           /**< Reserved for future use                            */
  uint32_t             RESERVED3[23U];          /**< Reserved for future use                            */
  ECAIF_FMTIN_TypeDef  FMTIN[2U];               /**<                                                    */
  uint32_t             RESERVED4[6U];           /**< Reserved for future use                            */
  uint32_t             RESERVED5[1U];           /**< Reserved for future use                            */
  uint32_t             RESERVED6[79U];          /**< Reserved for future use                            */
  __IOM uint32_t       CTRL;                    /**< New Register                                       */
  uint32_t             RESERVED7[895U];         /**< Reserved for future use                            */
  __IM uint32_t        IPVERSION_SET;           /**< IP Version ID                                      */
  __IOM uint32_t       EN_SET;                  /**< Module Enable                                      */
  __IOM uint32_t       SWRST_SET;               /**< Software Reset                                     */
  __IOM uint32_t       CONNECT_SET;             /**< New Register                                       */
  __IOM uint32_t       DISCLK_SET;              /**< New Register                                       */
  uint32_t             RESERVED8[3U];           /**< Reserved for future use                            */
  ECAIF_FIFOIN_TypeDef FIFOIN_SET[2U];          /**<                                                    */
  uint32_t             RESERVED9[6U];           /**< Reserved for future use                            */
  uint32_t             RESERVED10[1U];          /**< Reserved for future use                            */
  uint32_t             RESERVED11[23U];         /**< Reserved for future use                            */
  ECAIF_FMTIN_TypeDef  FMTIN_SET[2U];           /**<                                                    */
  uint32_t             RESERVED12[6U];          /**< Reserved for future use                            */
  uint32_t             RESERVED13[1U];          /**< Reserved for future use                            */
  uint32_t             RESERVED14[79U];         /**< Reserved for future use                            */
  __IOM uint32_t       CTRL_SET;                /**< New Register                                       */
  uint32_t             RESERVED15[895U];        /**< Reserved for future use                            */
  __IM uint32_t        IPVERSION_CLR;           /**< IP Version ID                                      */
  __IOM uint32_t       EN_CLR;                  /**< Module Enable                                      */
  __IOM uint32_t       SWRST_CLR;               /**< Software Reset                                     */
  __IOM uint32_t       CONNECT_CLR;             /**< New Register                                       */
  __IOM uint32_t       DISCLK_CLR;              /**< New Register                                       */
  uint32_t             RESERVED16[3U];          /**< Reserved for future use                            */
  ECAIF_FIFOIN_TypeDef FIFOIN_CLR[2U];          /**<                                                    */
  uint32_t             RESERVED17[6U];          /**< Reserved for future use                            */
  uint32_t             RESERVED18[1U];          /**< Reserved for future use                            */
  uint32_t             RESERVED19[23U];         /**< Reserved for future use                            */
  ECAIF_FMTIN_TypeDef  FMTIN_CLR[2U];           /**<                                                    */
  uint32_t             RESERVED20[6U];          /**< Reserved for future use                            */
  uint32_t             RESERVED21[1U];          /**< Reserved for future use                            */
  uint32_t             RESERVED22[79U];         /**< Reserved for future use                            */
  __IOM uint32_t       CTRL_CLR;                /**< New Register                                       */
  uint32_t             RESERVED23[895U];        /**< Reserved for future use                            */
  __IM uint32_t        IPVERSION_TGL;           /**< IP Version ID                                      */
  __IOM uint32_t       EN_TGL;                  /**< Module Enable                                      */
  __IOM uint32_t       SWRST_TGL;               /**< Software Reset                                     */
  __IOM uint32_t       CONNECT_TGL;             /**< New Register                                       */
  __IOM uint32_t       DISCLK_TGL;              /**< New Register                                       */
  uint32_t             RESERVED24[3U];          /**< Reserved for future use                            */
  ECAIF_FIFOIN_TypeDef FIFOIN_TGL[2U];          /**<                                                    */
  uint32_t             RESERVED25[6U];          /**< Reserved for future use                            */
  uint32_t             RESERVED26[1U];          /**< Reserved for future use                            */
  uint32_t             RESERVED27[23U];         /**< Reserved for future use                            */
  ECAIF_FMTIN_TypeDef  FMTIN_TGL[2U];           /**<                                                    */
  uint32_t             RESERVED28[6U];          /**< Reserved for future use                            */
  uint32_t             RESERVED29[1U];          /**< Reserved for future use                            */
  uint32_t             RESERVED30[79U];         /**< Reserved for future use                            */
  __IOM uint32_t       CTRL_TGL;                /**< New Register                                       */
} ECAIF_TypeDef;
/** @} End of group EFR32FG25_ECAIF */

/**************************************************************************//**
 * @addtogroup EFR32FG25_ECAIF
 * @{
 * @defgroup EFR32FG25_ECAIF_BitFields ECAIF Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for ECAIF IPVERSION */
#define _ECAIF_IPVERSION_RESETVALUE           0x00000001UL                              /**< Default value for ECAIF_IPVERSION           */
#define _ECAIF_IPVERSION_MASK                 0xFFFFFFFFUL                              /**< Mask for ECAIF_IPVERSION                    */
#define _ECAIF_IPVERSION_IPVERSION_SHIFT      0                                         /**< Shift value for ECAIF_IPVERSION             */
#define _ECAIF_IPVERSION_IPVERSION_MASK       0xFFFFFFFFUL                              /**< Bit mask for ECAIF_IPVERSION                */
#define _ECAIF_IPVERSION_IPVERSION_DEFAULT    0x00000001UL                              /**< Mode DEFAULT for ECAIF_IPVERSION            */
#define ECAIF_IPVERSION_IPVERSION_DEFAULT     (_ECAIF_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for ECAIF_IPVERSION    */

/* Bit fields for ECAIF EN */
#define _ECAIF_EN_RESETVALUE                  0x00000000UL                              /**< Default value for ECAIF_EN                  */
#define _ECAIF_EN_MASK                        0x00000003UL                              /**< Mask for ECAIF_EN                           */
#define ECAIF_EN_EN                           (0x1UL << 0)                              /**< Module Enable                               */
#define _ECAIF_EN_EN_SHIFT                    0                                         /**< Shift value for ECAIF_EN                    */
#define _ECAIF_EN_EN_MASK                     0x1UL                                     /**< Bit mask for ECAIF_EN                       */
#define _ECAIF_EN_EN_DEFAULT                  0x00000000UL                              /**< Mode DEFAULT for ECAIF_EN                   */
#define ECAIF_EN_EN_DEFAULT                   (_ECAIF_EN_EN_DEFAULT << 0)               /**< Shifted mode DEFAULT for ECAIF_EN           */
#define ECAIF_EN_DISABLING                    (0x1UL << 1)                              /**< Disablement Busy Status                     */
#define _ECAIF_EN_DISABLING_SHIFT             1                                         /**< Shift value for ECAIF_DISABLING             */
#define _ECAIF_EN_DISABLING_MASK              0x2UL                                     /**< Bit mask for ECAIF_DISABLING                */
#define _ECAIF_EN_DISABLING_DEFAULT           0x00000000UL                              /**< Mode DEFAULT for ECAIF_EN                   */
#define ECAIF_EN_DISABLING_DEFAULT            (_ECAIF_EN_DISABLING_DEFAULT << 1)        /**< Shifted mode DEFAULT for ECAIF_EN           */

/* Bit fields for ECAIF SWRST */
#define _ECAIF_SWRST_RESETVALUE               0x00000000UL                              /**< Default value for ECAIF_SWRST               */
#define _ECAIF_SWRST_MASK                     0x00000003UL                              /**< Mask for ECAIF_SWRST                        */
#define ECAIF_SWRST_SWRST                     (0x1UL << 0)                              /**< Software Reset Command                      */
#define _ECAIF_SWRST_SWRST_SHIFT              0                                         /**< Shift value for ECAIF_SWRST                 */
#define _ECAIF_SWRST_SWRST_MASK               0x1UL                                     /**< Bit mask for ECAIF_SWRST                    */
#define _ECAIF_SWRST_SWRST_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for ECAIF_SWRST                */
#define ECAIF_SWRST_SWRST_DEFAULT             (_ECAIF_SWRST_SWRST_DEFAULT << 0)         /**< Shifted mode DEFAULT for ECAIF_SWRST        */
#define ECAIF_SWRST_RESETTING                 (0x1UL << 1)                              /**< Software Reset Busy Status                  */
#define _ECAIF_SWRST_RESETTING_SHIFT          1                                         /**< Shift value for ECAIF_RESETTING             */
#define _ECAIF_SWRST_RESETTING_MASK           0x2UL                                     /**< Bit mask for ECAIF_RESETTING                */
#define _ECAIF_SWRST_RESETTING_DEFAULT        0x00000000UL                              /**< Mode DEFAULT for ECAIF_SWRST                */
#define ECAIF_SWRST_RESETTING_DEFAULT         (_ECAIF_SWRST_RESETTING_DEFAULT << 1)     /**< Shifted mode DEFAULT for ECAIF_SWRST        */

/* Bit fields for ECAIF CONNECT */
#define _ECAIF_CONNECT_RESETVALUE             0x00000000UL                              /**< Default value for ECAIF_CONNECT             */
#define _ECAIF_CONNECT_MASK                   0x00000003UL                              /**< Mask for ECAIF_CONNECT                      */
#define _ECAIF_CONNECT_IN_SHIFT               0                                         /**< Shift value for ECAIF_IN                    */
#define _ECAIF_CONNECT_IN_MASK                0x3UL                                     /**< Bit mask for ECAIF_IN                       */
#define _ECAIF_CONNECT_IN_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for ECAIF_CONNECT              */
#define ECAIF_CONNECT_IN_DEFAULT              (_ECAIF_CONNECT_IN_DEFAULT << 0)          /**< Shifted mode DEFAULT for ECAIF_CONNECT      */

/* Bit fields for ECAIF DISCLK */
#define _ECAIF_DISCLK_RESETVALUE              0x00000000UL                              /**< Default value for ECAIF_DISCLK              */
#define _ECAIF_DISCLK_MASK                    0x00000003UL                              /**< Mask for ECAIF_DISCLK                       */
#define _ECAIF_DISCLK_DISCLK_SHIFT            0                                         /**< Shift value for ECAIF_DISCLK                */
#define _ECAIF_DISCLK_DISCLK_MASK             0x3UL                                     /**< Bit mask for ECAIF_DISCLK                   */
#define _ECAIF_DISCLK_DISCLK_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for ECAIF_DISCLK               */
#define _ECAIF_DISCLK_DISCLK_NONE             0x00000000UL                              /**< Mode NONE for ECAIF_DISCLK                  */
#define _ECAIF_DISCLK_DISCLK_ALL              0x00000001UL                              /**< Mode ALL for ECAIF_DISCLK                   */
#define _ECAIF_DISCLK_DISCLK_NOTUSED          0x00000003UL                              /**< Mode NOTUSED for ECAIF_DISCLK               */
#define ECAIF_DISCLK_DISCLK_DEFAULT           (_ECAIF_DISCLK_DISCLK_DEFAULT << 0)       /**< Shifted mode DEFAULT for ECAIF_DISCLK       */
#define ECAIF_DISCLK_DISCLK_NONE              (_ECAIF_DISCLK_DISCLK_NONE << 0)          /**< Shifted mode NONE for ECAIF_DISCLK          */
#define ECAIF_DISCLK_DISCLK_ALL               (_ECAIF_DISCLK_DISCLK_ALL << 0)           /**< Shifted mode ALL for ECAIF_DISCLK           */
#define ECAIF_DISCLK_DISCLK_NOTUSED           (_ECAIF_DISCLK_DISCLK_NOTUSED << 0)       /**< Shifted mode NOTUSED for ECAIF_DISCLK       */

/* Bit fields for ECAIF FIFOIN */
#define _ECAIF_FIFOIN_RESETVALUE              0x00000000UL                              /**< Default value for ECAIF_FIFOIN              */
#define _ECAIF_FIFOIN_MASK                    0x1FFF3F0FUL                              /**< Mask for ECAIF_FIFOIN                       */
#define _ECAIF_FIFOIN_FID_SHIFT               0                                         /**< Shift value for ECAIF_FID                   */
#define _ECAIF_FIFOIN_FID_MASK                0xFUL                                     /**< Bit mask for ECAIF_FID                      */
#define _ECAIF_FIFOIN_FID_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for ECAIF_FIFOIN               */
#define ECAIF_FIFOIN_FID_DEFAULT              (_ECAIF_FIFOIN_FID_DEFAULT << 0)          /**< Shifted mode DEFAULT for ECAIF_FIFOIN       */
#define _ECAIF_FIFOIN_CID_SHIFT               8                                         /**< Shift value for ECAIF_CID                   */
#define _ECAIF_FIFOIN_CID_MASK                0x3F00UL                                  /**< Bit mask for ECAIF_CID                      */
#define _ECAIF_FIFOIN_CID_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for ECAIF_FIFOIN               */
#define ECAIF_FIFOIN_CID_DEFAULT              (_ECAIF_FIFOIN_CID_DEFAULT << 8)          /**< Shifted mode DEFAULT for ECAIF_FIFOIN       */
#define _ECAIF_FIFOIN_REM_SHIFT               16                                        /**< Shift value for ECAIF_REM                   */
#define _ECAIF_FIFOIN_REM_MASK                0xFF0000UL                                /**< Bit mask for ECAIF_REM                      */
#define _ECAIF_FIFOIN_REM_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for ECAIF_FIFOIN               */
#define ECAIF_FIFOIN_REM_DEFAULT              (_ECAIF_FIFOIN_REM_DEFAULT << 16)         /**< Shifted mode DEFAULT for ECAIF_FIFOIN       */
#define _ECAIF_FIFOIN_ALARM_SHIFT             24                                        /**< Shift value for ECAIF_ALARM                 */
#define _ECAIF_FIFOIN_ALARM_MASK              0x1F000000UL                              /**< Bit mask for ECAIF_ALARM                    */
#define _ECAIF_FIFOIN_ALARM_DEFAULT           0x00000000UL                              /**< Mode DEFAULT for ECAIF_FIFOIN               */
#define ECAIF_FIFOIN_ALARM_DEFAULT            (_ECAIF_FIFOIN_ALARM_DEFAULT << 24)       /**< Shifted mode DEFAULT for ECAIF_FIFOIN       */

/* Bit fields for ECAIF CTRL */
#define _ECAIF_CTRL_RESETVALUE                0x00040002UL                              /**< Default value for ECAIF_CTRL                */
#define _ECAIF_CTRL_MASK                      0x003FFFFFUL                              /**< Mask for ECAIF_CTRL                         */
#define ECAIF_CTRL_RST                        (0x1UL << 0)                              /**< New BitField                                */
#define _ECAIF_CTRL_RST_SHIFT                 0                                         /**< Shift value for ECAIF_RST                   */
#define _ECAIF_CTRL_RST_MASK                  0x1UL                                     /**< Bit mask for ECAIF_RST                      */
#define _ECAIF_CTRL_RST_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for ECAIF_CTRL                 */
#define ECAIF_CTRL_RST_DEFAULT                (_ECAIF_CTRL_RST_DEFAULT << 0)            /**< Shifted mode DEFAULT for ECAIF_CTRL         */
#define _ECAIF_CTRL_OUTDIV_SHIFT              1                                         /**< Shift value for ECAIF_OUTDIV                */
#define _ECAIF_CTRL_OUTDIV_MASK               0x1EUL                                    /**< Bit mask for ECAIF_OUTDIV                   */
#define _ECAIF_CTRL_OUTDIV_DEFAULT            0x00000001UL                              /**< Mode DEFAULT for ECAIF_CTRL                 */
#define ECAIF_CTRL_OUTDIV_DEFAULT             (_ECAIF_CTRL_OUTDIV_DEFAULT << 1)         /**< Shifted mode DEFAULT for ECAIF_CTRL         */
#define _ECAIF_CTRL_SELIRQ_SHIFT              5                                         /**< Shift value for ECAIF_SELIRQ                */
#define _ECAIF_CTRL_SELIRQ_MASK               0xE0UL                                    /**< Bit mask for ECAIF_SELIRQ                   */
#define _ECAIF_CTRL_SELIRQ_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for ECAIF_CTRL                 */
#define _ECAIF_CTRL_SELIRQ_S_1_0              0x00000000UL                              /**< Mode S_1_0 for ECAIF_CTRL                   */
#define _ECAIF_CTRL_SELIRQ_S_2_0              0x00000001UL                              /**< Mode S_2_0 for ECAIF_CTRL                   */
#define _ECAIF_CTRL_SELIRQ_S_3_0              0x00000002UL                              /**< Mode S_3_0 for ECAIF_CTRL                   */
#define _ECAIF_CTRL_SELIRQ_S_2_1              0x00000003UL                              /**< Mode S_2_1 for ECAIF_CTRL                   */
#define _ECAIF_CTRL_SELIRQ_S_3_1              0x00000004UL                              /**< Mode S_3_1 for ECAIF_CTRL                   */
#define _ECAIF_CTRL_SELIRQ_S_3_2              0x00000005UL                              /**< Mode S_3_2 for ECAIF_CTRL                   */
#define _ECAIF_CTRL_SELIRQ_EXTRA1             0x00000006UL                              /**< Mode EXTRA1 for ECAIF_CTRL                  */
#define _ECAIF_CTRL_SELIRQ_EXTRA2             0x00000007UL                              /**< Mode EXTRA2 for ECAIF_CTRL                  */
#define ECAIF_CTRL_SELIRQ_DEFAULT             (_ECAIF_CTRL_SELIRQ_DEFAULT << 5)         /**< Shifted mode DEFAULT for ECAIF_CTRL         */
#define ECAIF_CTRL_SELIRQ_S_1_0               (_ECAIF_CTRL_SELIRQ_S_1_0 << 5)           /**< Shifted mode S_1_0 for ECAIF_CTRL           */
#define ECAIF_CTRL_SELIRQ_S_2_0               (_ECAIF_CTRL_SELIRQ_S_2_0 << 5)           /**< Shifted mode S_2_0 for ECAIF_CTRL           */
#define ECAIF_CTRL_SELIRQ_S_3_0               (_ECAIF_CTRL_SELIRQ_S_3_0 << 5)           /**< Shifted mode S_3_0 for ECAIF_CTRL           */
#define ECAIF_CTRL_SELIRQ_S_2_1               (_ECAIF_CTRL_SELIRQ_S_2_1 << 5)           /**< Shifted mode S_2_1 for ECAIF_CTRL           */
#define ECAIF_CTRL_SELIRQ_S_3_1               (_ECAIF_CTRL_SELIRQ_S_3_1 << 5)           /**< Shifted mode S_3_1 for ECAIF_CTRL           */
#define ECAIF_CTRL_SELIRQ_S_3_2               (_ECAIF_CTRL_SELIRQ_S_3_2 << 5)           /**< Shifted mode S_3_2 for ECAIF_CTRL           */
#define ECAIF_CTRL_SELIRQ_EXTRA1              (_ECAIF_CTRL_SELIRQ_EXTRA1 << 5)          /**< Shifted mode EXTRA1 for ECAIF_CTRL          */
#define ECAIF_CTRL_SELIRQ_EXTRA2              (_ECAIF_CTRL_SELIRQ_EXTRA2 << 5)          /**< Shifted mode EXTRA2 for ECAIF_CTRL          */
#define _ECAIF_CTRL_SHIFT0_SHIFT              8                                         /**< Shift value for ECAIF_SHIFT0                */
#define _ECAIF_CTRL_SHIFT0_MASK               0x1F00UL                                  /**< Bit mask for ECAIF_SHIFT0                   */
#define _ECAIF_CTRL_SHIFT0_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for ECAIF_CTRL                 */
#define ECAIF_CTRL_SHIFT0_DEFAULT             (_ECAIF_CTRL_SHIFT0_DEFAULT << 8)         /**< Shifted mode DEFAULT for ECAIF_CTRL         */
#define _ECAIF_CTRL_SHIFT1_SHIFT              13                                        /**< Shift value for ECAIF_SHIFT1                */
#define _ECAIF_CTRL_SHIFT1_MASK               0x3E000UL                                 /**< Bit mask for ECAIF_SHIFT1                   */
#define _ECAIF_CTRL_SHIFT1_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for ECAIF_CTRL                 */
#define ECAIF_CTRL_SHIFT1_DEFAULT             (_ECAIF_CTRL_SHIFT1_DEFAULT << 13)        /**< Shifted mode DEFAULT for ECAIF_CTRL         */
#define _ECAIF_CTRL_SELDACI_SHIFT             18                                        /**< Shift value for ECAIF_SELDACI               */
#define _ECAIF_CTRL_SELDACI_MASK              0xC0000UL                                 /**< Bit mask for ECAIF_SELDACI                  */
#define _ECAIF_CTRL_SELDACI_DEFAULT           0x00000001UL                              /**< Mode DEFAULT for ECAIF_CTRL                 */
#define _ECAIF_CTRL_SELDACI_Q_FIFO_0          0x00000000UL                              /**< Mode Q_FIFO_0 for ECAIF_CTRL                */
#define _ECAIF_CTRL_SELDACI_I_FIFO_0          0x00000001UL                              /**< Mode I_FIFO_0 for ECAIF_CTRL                */
#define _ECAIF_CTRL_SELDACI_Q_FIFO_1          0x00000002UL                              /**< Mode Q_FIFO_1 for ECAIF_CTRL                */
#define _ECAIF_CTRL_SELDACI_I_FIFO_1          0x00000003UL                              /**< Mode I_FIFO_1 for ECAIF_CTRL                */
#define ECAIF_CTRL_SELDACI_DEFAULT            (_ECAIF_CTRL_SELDACI_DEFAULT << 18)       /**< Shifted mode DEFAULT for ECAIF_CTRL         */
#define ECAIF_CTRL_SELDACI_Q_FIFO_0           (_ECAIF_CTRL_SELDACI_Q_FIFO_0 << 18)      /**< Shifted mode Q_FIFO_0 for ECAIF_CTRL        */
#define ECAIF_CTRL_SELDACI_I_FIFO_0           (_ECAIF_CTRL_SELDACI_I_FIFO_0 << 18)      /**< Shifted mode I_FIFO_0 for ECAIF_CTRL        */
#define ECAIF_CTRL_SELDACI_Q_FIFO_1           (_ECAIF_CTRL_SELDACI_Q_FIFO_1 << 18)      /**< Shifted mode Q_FIFO_1 for ECAIF_CTRL        */
#define ECAIF_CTRL_SELDACI_I_FIFO_1           (_ECAIF_CTRL_SELDACI_I_FIFO_1 << 18)      /**< Shifted mode I_FIFO_1 for ECAIF_CTRL        */
#define _ECAIF_CTRL_SELDACQ_SHIFT             20                                        /**< Shift value for ECAIF_SELDACQ               */
#define _ECAIF_CTRL_SELDACQ_MASK              0x300000UL                                /**< Bit mask for ECAIF_SELDACQ                  */
#define _ECAIF_CTRL_SELDACQ_DEFAULT           0x00000000UL                              /**< Mode DEFAULT for ECAIF_CTRL                 */
#define _ECAIF_CTRL_SELDACQ_Q_FIFO_0          0x00000000UL                              /**< Mode Q_FIFO_0 for ECAIF_CTRL                */
#define _ECAIF_CTRL_SELDACQ_I_FIFO_0          0x00000001UL                              /**< Mode I_FIFO_0 for ECAIF_CTRL                */
#define _ECAIF_CTRL_SELDACQ_Q_FIFO_1          0x00000002UL                              /**< Mode Q_FIFO_1 for ECAIF_CTRL                */
#define _ECAIF_CTRL_SELDACQ_I_FIFO_1          0x00000003UL                              /**< Mode I_FIFO_1 for ECAIF_CTRL                */
#define ECAIF_CTRL_SELDACQ_DEFAULT            (_ECAIF_CTRL_SELDACQ_DEFAULT << 20)       /**< Shifted mode DEFAULT for ECAIF_CTRL         */
#define ECAIF_CTRL_SELDACQ_Q_FIFO_0           (_ECAIF_CTRL_SELDACQ_Q_FIFO_0 << 20)      /**< Shifted mode Q_FIFO_0 for ECAIF_CTRL        */
#define ECAIF_CTRL_SELDACQ_I_FIFO_0           (_ECAIF_CTRL_SELDACQ_I_FIFO_0 << 20)      /**< Shifted mode I_FIFO_0 for ECAIF_CTRL        */
#define ECAIF_CTRL_SELDACQ_Q_FIFO_1           (_ECAIF_CTRL_SELDACQ_Q_FIFO_1 << 20)      /**< Shifted mode Q_FIFO_1 for ECAIF_CTRL        */
#define ECAIF_CTRL_SELDACQ_I_FIFO_1           (_ECAIF_CTRL_SELDACQ_I_FIFO_1 << 20)      /**< Shifted mode I_FIFO_1 for ECAIF_CTRL        */

/** @} End of group EFR32FG25_ECAIF_BitFields */
/** @} End of group EFR32FG25_ECAIF */
/** @} End of group Parts */

#endif /* EFR32FG25_ECAIF_H */
