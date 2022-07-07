/**************************************************************************//**
 * @file
 * @brief EFR32FG25 CORDIC register and bit field definitions
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
#ifndef EFR32FG25_CORDIC_H
#define EFR32FG25_CORDIC_H
#define CORDIC_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_CORDIC CORDIC
 * @{
 * @brief EFR32FG25 CORDIC Register Declaration.
 *****************************************************************************/

/** CORDIC Register Declaration. */
typedef struct {
  __IM uint32_t  IPVERSION;                     /**< IP Version ID                                      */
  __IOM uint32_t EN;                            /**< Module Enable                                      */
  __IOM uint32_t SWRST;                         /**< Software Reset                                     */
  __IOM uint32_t CONNECT;                       /**< New Register                                       */
  __IOM uint32_t DISCLK;                        /**< Disable clk_per                                    */
  uint32_t       RESERVED0[3U];                 /**< Reserved for future use                            */
  __IOM uint32_t FIFOIN;                        /**< New Register                                       */
  uint32_t       RESERVED1[7U];                 /**< Reserved for future use                            */
  __IM uint32_t  FIFOOUT;                       /**< New Register                                       */
  uint32_t       RESERVED2[23U];                /**< Reserved for future use                            */
  uint32_t       RESERVED3[1U];                 /**< Reserved for future use                            */
  uint32_t       RESERVED4[7U];                 /**< Reserved for future use                            */
  uint32_t       RESERVED5[1U];                 /**< Reserved for future use                            */
  uint32_t       RESERVED6[79U];                /**< Reserved for future use                            */
  __IOM uint32_t CTRL;                          /**< New Register                                       */
  __IOM uint32_t UNWRAP;                        /**< New Register                                       */
  uint32_t       RESERVED7[894U];               /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_SET;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_SET;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_SET;                   /**< New Register                                       */
  __IOM uint32_t DISCLK_SET;                    /**< Disable clk_per                                    */
  uint32_t       RESERVED8[3U];                 /**< Reserved for future use                            */
  __IOM uint32_t FIFOIN_SET;                    /**< New Register                                       */
  uint32_t       RESERVED9[7U];                 /**< Reserved for future use                            */
  __IM uint32_t  FIFOOUT_SET;                   /**< New Register                                       */
  uint32_t       RESERVED10[23U];               /**< Reserved for future use                            */
  uint32_t       RESERVED11[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED12[7U];                /**< Reserved for future use                            */
  uint32_t       RESERVED13[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED14[79U];               /**< Reserved for future use                            */
  __IOM uint32_t CTRL_SET;                      /**< New Register                                       */
  __IOM uint32_t UNWRAP_SET;                    /**< New Register                                       */
  uint32_t       RESERVED15[894U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_CLR;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_CLR;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_CLR;                   /**< New Register                                       */
  __IOM uint32_t DISCLK_CLR;                    /**< Disable clk_per                                    */
  uint32_t       RESERVED16[3U];                /**< Reserved for future use                            */
  __IOM uint32_t FIFOIN_CLR;                    /**< New Register                                       */
  uint32_t       RESERVED17[7U];                /**< Reserved for future use                            */
  __IM uint32_t  FIFOOUT_CLR;                   /**< New Register                                       */
  uint32_t       RESERVED18[23U];               /**< Reserved for future use                            */
  uint32_t       RESERVED19[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED20[7U];                /**< Reserved for future use                            */
  uint32_t       RESERVED21[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED22[79U];               /**< Reserved for future use                            */
  __IOM uint32_t CTRL_CLR;                      /**< New Register                                       */
  __IOM uint32_t UNWRAP_CLR;                    /**< New Register                                       */
  uint32_t       RESERVED23[894U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_TGL;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_TGL;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_TGL;                   /**< New Register                                       */
  __IOM uint32_t DISCLK_TGL;                    /**< Disable clk_per                                    */
  uint32_t       RESERVED24[3U];                /**< Reserved for future use                            */
  __IOM uint32_t FIFOIN_TGL;                    /**< New Register                                       */
  uint32_t       RESERVED25[7U];                /**< Reserved for future use                            */
  __IM uint32_t  FIFOOUT_TGL;                   /**< New Register                                       */
  uint32_t       RESERVED26[23U];               /**< Reserved for future use                            */
  uint32_t       RESERVED27[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED28[7U];                /**< Reserved for future use                            */
  uint32_t       RESERVED29[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED30[79U];               /**< Reserved for future use                            */
  __IOM uint32_t CTRL_TGL;                      /**< New Register                                       */
  __IOM uint32_t UNWRAP_TGL;                    /**< New Register                                       */
} CORDIC_TypeDef;
/** @} End of group EFR32FG25_CORDIC */

/**************************************************************************//**
 * @addtogroup EFR32FG25_CORDIC
 * @{
 * @defgroup EFR32FG25_CORDIC_BitFields CORDIC Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for CORDIC IPVERSION */
#define _CORDIC_IPVERSION_RESETVALUE           0x00000001UL                               /**< Default value for CORDIC_IPVERSION          */
#define _CORDIC_IPVERSION_MASK                 0xFFFFFFFFUL                               /**< Mask for CORDIC_IPVERSION                   */
#define _CORDIC_IPVERSION_IPVERSION_SHIFT      0                                          /**< Shift value for CORDIC_IPVERSION            */
#define _CORDIC_IPVERSION_IPVERSION_MASK       0xFFFFFFFFUL                               /**< Bit mask for CORDIC_IPVERSION               */
#define _CORDIC_IPVERSION_IPVERSION_DEFAULT    0x00000001UL                               /**< Mode DEFAULT for CORDIC_IPVERSION           */
#define CORDIC_IPVERSION_IPVERSION_DEFAULT     (_CORDIC_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for CORDIC_IPVERSION   */

/* Bit fields for CORDIC EN */
#define _CORDIC_EN_RESETVALUE                  0x00000000UL                             /**< Default value for CORDIC_EN                 */
#define _CORDIC_EN_MASK                        0x00000003UL                             /**< Mask for CORDIC_EN                          */
#define CORDIC_EN_EN                           (0x1UL << 0)                             /**< Module Enable                               */
#define _CORDIC_EN_EN_SHIFT                    0                                        /**< Shift value for CORDIC_EN                   */
#define _CORDIC_EN_EN_MASK                     0x1UL                                    /**< Bit mask for CORDIC_EN                      */
#define _CORDIC_EN_EN_DEFAULT                  0x00000000UL                             /**< Mode DEFAULT for CORDIC_EN                  */
#define CORDIC_EN_EN_DEFAULT                   (_CORDIC_EN_EN_DEFAULT << 0)             /**< Shifted mode DEFAULT for CORDIC_EN          */
#define CORDIC_EN_DISABLING                    (0x1UL << 1)                             /**< Disablement Busy Status                     */
#define _CORDIC_EN_DISABLING_SHIFT             1                                        /**< Shift value for CORDIC_DISABLING            */
#define _CORDIC_EN_DISABLING_MASK              0x2UL                                    /**< Bit mask for CORDIC_DISABLING               */
#define _CORDIC_EN_DISABLING_DEFAULT           0x00000000UL                             /**< Mode DEFAULT for CORDIC_EN                  */
#define CORDIC_EN_DISABLING_DEFAULT            (_CORDIC_EN_DISABLING_DEFAULT << 1)      /**< Shifted mode DEFAULT for CORDIC_EN          */

/* Bit fields for CORDIC SWRST */
#define _CORDIC_SWRST_RESETVALUE               0x00000000UL                             /**< Default value for CORDIC_SWRST              */
#define _CORDIC_SWRST_MASK                     0x00000003UL                             /**< Mask for CORDIC_SWRST                       */
#define CORDIC_SWRST_SWRST                     (0x1UL << 0)                             /**< Software Reset Command                      */
#define _CORDIC_SWRST_SWRST_SHIFT              0                                        /**< Shift value for CORDIC_SWRST                */
#define _CORDIC_SWRST_SWRST_MASK               0x1UL                                    /**< Bit mask for CORDIC_SWRST                   */
#define _CORDIC_SWRST_SWRST_DEFAULT            0x00000000UL                             /**< Mode DEFAULT for CORDIC_SWRST               */
#define CORDIC_SWRST_SWRST_DEFAULT             (_CORDIC_SWRST_SWRST_DEFAULT << 0)       /**< Shifted mode DEFAULT for CORDIC_SWRST       */
#define CORDIC_SWRST_RESETTING                 (0x1UL << 1)                             /**< Software Reset Busy Status                  */
#define _CORDIC_SWRST_RESETTING_SHIFT          1                                        /**< Shift value for CORDIC_RESETTING            */
#define _CORDIC_SWRST_RESETTING_MASK           0x2UL                                    /**< Bit mask for CORDIC_RESETTING               */
#define _CORDIC_SWRST_RESETTING_DEFAULT        0x00000000UL                             /**< Mode DEFAULT for CORDIC_SWRST               */
#define CORDIC_SWRST_RESETTING_DEFAULT         (_CORDIC_SWRST_RESETTING_DEFAULT << 1)   /**< Shifted mode DEFAULT for CORDIC_SWRST       */

/* Bit fields for CORDIC CONNECT */
#define _CORDIC_CONNECT_RESETVALUE             0x00000000UL                             /**< Default value for CORDIC_CONNECT            */
#define _CORDIC_CONNECT_MASK                   0x00000101UL                             /**< Mask for CORDIC_CONNECT                     */
#define CORDIC_CONNECT_IN                      (0x1UL << 0)                             /**< Input FIFO connect                          */
#define _CORDIC_CONNECT_IN_SHIFT               0                                        /**< Shift value for CORDIC_IN                   */
#define _CORDIC_CONNECT_IN_MASK                0x1UL                                    /**< Bit mask for CORDIC_IN                      */
#define _CORDIC_CONNECT_IN_DEFAULT             0x00000000UL                             /**< Mode DEFAULT for CORDIC_CONNECT             */
#define CORDIC_CONNECT_IN_DEFAULT              (_CORDIC_CONNECT_IN_DEFAULT << 0)        /**< Shifted mode DEFAULT for CORDIC_CONNECT     */
#define CORDIC_CONNECT_OUT                     (0x1UL << 8)                             /**< Output FIFO connect                         */
#define _CORDIC_CONNECT_OUT_SHIFT              8                                        /**< Shift value for CORDIC_OUT                  */
#define _CORDIC_CONNECT_OUT_MASK               0x100UL                                  /**< Bit mask for CORDIC_OUT                     */
#define _CORDIC_CONNECT_OUT_DEFAULT            0x00000000UL                             /**< Mode DEFAULT for CORDIC_CONNECT             */
#define CORDIC_CONNECT_OUT_DEFAULT             (_CORDIC_CONNECT_OUT_DEFAULT << 8)       /**< Shifted mode DEFAULT for CORDIC_CONNECT     */

/* Bit fields for CORDIC DISCLK */
#define _CORDIC_DISCLK_RESETVALUE              0x00000002UL                             /**< Default value for CORDIC_DISCLK             */
#define _CORDIC_DISCLK_MASK                    0x00000003UL                             /**< Mask for CORDIC_DISCLK                      */
#define _CORDIC_DISCLK_DISCLK_SHIFT            0                                        /**< Shift value for CORDIC_DISCLK               */
#define _CORDIC_DISCLK_DISCLK_MASK             0x3UL                                    /**< Bit mask for CORDIC_DISCLK                  */
#define _CORDIC_DISCLK_DISCLK_DEFAULT          0x00000002UL                             /**< Mode DEFAULT for CORDIC_DISCLK              */
#define _CORDIC_DISCLK_DISCLK_NONE             0x00000000UL                             /**< Mode NONE for CORDIC_DISCLK                 */
#define _CORDIC_DISCLK_DISCLK_ALL              0x00000001UL                             /**< Mode ALL for CORDIC_DISCLK                  */
#define _CORDIC_DISCLK_DISCLK_AUTO             0x00000002UL                             /**< Mode AUTO for CORDIC_DISCLK                 */
#define CORDIC_DISCLK_DISCLK_DEFAULT           (_CORDIC_DISCLK_DISCLK_DEFAULT << 0)     /**< Shifted mode DEFAULT for CORDIC_DISCLK      */
#define CORDIC_DISCLK_DISCLK_NONE              (_CORDIC_DISCLK_DISCLK_NONE << 0)        /**< Shifted mode NONE for CORDIC_DISCLK         */
#define CORDIC_DISCLK_DISCLK_ALL               (_CORDIC_DISCLK_DISCLK_ALL << 0)         /**< Shifted mode ALL for CORDIC_DISCLK          */
#define CORDIC_DISCLK_DISCLK_AUTO              (_CORDIC_DISCLK_DISCLK_AUTO << 0)        /**< Shifted mode AUTO for CORDIC_DISCLK         */

/* Bit fields for CORDIC FIFOIN */
#define _CORDIC_FIFOIN_RESETVALUE              0x00000000UL                             /**< Default value for CORDIC_FIFOIN             */
#define _CORDIC_FIFOIN_MASK                    0x1FFF3F0FUL                             /**< Mask for CORDIC_FIFOIN                      */
#define _CORDIC_FIFOIN_FID_SHIFT               0                                        /**< Shift value for CORDIC_FID                  */
#define _CORDIC_FIFOIN_FID_MASK                0xFUL                                    /**< Bit mask for CORDIC_FID                     */
#define _CORDIC_FIFOIN_FID_DEFAULT             0x00000000UL                             /**< Mode DEFAULT for CORDIC_FIFOIN              */
#define CORDIC_FIFOIN_FID_DEFAULT              (_CORDIC_FIFOIN_FID_DEFAULT << 0)        /**< Shifted mode DEFAULT for CORDIC_FIFOIN      */
#define _CORDIC_FIFOIN_CID_SHIFT               8                                        /**< Shift value for CORDIC_CID                  */
#define _CORDIC_FIFOIN_CID_MASK                0x3F00UL                                 /**< Bit mask for CORDIC_CID                     */
#define _CORDIC_FIFOIN_CID_DEFAULT             0x00000000UL                             /**< Mode DEFAULT for CORDIC_FIFOIN              */
#define CORDIC_FIFOIN_CID_DEFAULT              (_CORDIC_FIFOIN_CID_DEFAULT << 8)        /**< Shifted mode DEFAULT for CORDIC_FIFOIN      */
#define _CORDIC_FIFOIN_REM_SHIFT               16                                       /**< Shift value for CORDIC_REM                  */
#define _CORDIC_FIFOIN_REM_MASK                0xFF0000UL                               /**< Bit mask for CORDIC_REM                     */
#define _CORDIC_FIFOIN_REM_DEFAULT             0x00000000UL                             /**< Mode DEFAULT for CORDIC_FIFOIN              */
#define CORDIC_FIFOIN_REM_DEFAULT              (_CORDIC_FIFOIN_REM_DEFAULT << 16)       /**< Shifted mode DEFAULT for CORDIC_FIFOIN      */
#define _CORDIC_FIFOIN_ALARM_SHIFT             24                                       /**< Shift value for CORDIC_ALARM                */
#define _CORDIC_FIFOIN_ALARM_MASK              0x1F000000UL                             /**< Bit mask for CORDIC_ALARM                   */
#define _CORDIC_FIFOIN_ALARM_DEFAULT           0x00000000UL                             /**< Mode DEFAULT for CORDIC_FIFOIN              */
#define CORDIC_FIFOIN_ALARM_DEFAULT            (_CORDIC_FIFOIN_ALARM_DEFAULT << 24)     /**< Shifted mode DEFAULT for CORDIC_FIFOIN      */

/* Bit fields for CORDIC FIFOOUT */
#define _CORDIC_FIFOOUT_RESETVALUE             0x00000000UL                             /**< Default value for CORDIC_FIFOOUT            */
#define _CORDIC_FIFOOUT_MASK                   0x1FFF0000UL                             /**< Mask for CORDIC_FIFOOUT                     */
#define _CORDIC_FIFOOUT_CNT_SHIFT              16                                       /**< Shift value for CORDIC_CNT                  */
#define _CORDIC_FIFOOUT_CNT_MASK               0xFF0000UL                               /**< Bit mask for CORDIC_CNT                     */
#define _CORDIC_FIFOOUT_CNT_DEFAULT            0x00000000UL                             /**< Mode DEFAULT for CORDIC_FIFOOUT             */
#define CORDIC_FIFOOUT_CNT_DEFAULT             (_CORDIC_FIFOOUT_CNT_DEFAULT << 16)      /**< Shifted mode DEFAULT for CORDIC_FIFOOUT     */
#define _CORDIC_FIFOOUT_ALARM_SHIFT            24                                       /**< Shift value for CORDIC_ALARM                */
#define _CORDIC_FIFOOUT_ALARM_MASK             0x1F000000UL                             /**< Bit mask for CORDIC_ALARM                   */
#define _CORDIC_FIFOOUT_ALARM_DEFAULT          0x00000000UL                             /**< Mode DEFAULT for CORDIC_FIFOOUT             */
#define CORDIC_FIFOOUT_ALARM_DEFAULT           (_CORDIC_FIFOOUT_ALARM_DEFAULT << 24)    /**< Shifted mode DEFAULT for CORDIC_FIFOOUT     */

/* Bit fields for CORDIC CTRL */
#define _CORDIC_CTRL_RESETVALUE                0x00000028UL                             /**< Default value for CORDIC_CTRL               */
#define _CORDIC_CTRL_MASK                      0x0000007FUL                             /**< Mask for CORDIC_CTRL                        */
#define _CORDIC_CTRL_MODE_SHIFT                0                                        /**< Shift value for CORDIC_MODE                 */
#define _CORDIC_CTRL_MODE_MASK                 0x3UL                                    /**< Bit mask for CORDIC_MODE                    */
#define _CORDIC_CTRL_MODE_DEFAULT              0x00000000UL                             /**< Mode DEFAULT for CORDIC_CTRL                */
#define _CORDIC_CTRL_MODE_C2P                  0x00000000UL                             /**< Mode C2P for CORDIC_CTRL                    */
#define _CORDIC_CTRL_MODE_P2C                  0x00000001UL                             /**< Mode P2C for CORDIC_CTRL                    */
#define _CORDIC_CTRL_MODE_I2ME                 0x00000002UL                             /**< Mode I2ME for CORDIC_CTRL                   */
#define _CORDIC_CTRL_MODE_NOTUSED              0x00000003UL                             /**< Mode NOTUSED for CORDIC_CTRL                */
#define CORDIC_CTRL_MODE_DEFAULT               (_CORDIC_CTRL_MODE_DEFAULT << 0)         /**< Shifted mode DEFAULT for CORDIC_CTRL        */
#define CORDIC_CTRL_MODE_C2P                   (_CORDIC_CTRL_MODE_C2P << 0)             /**< Shifted mode C2P for CORDIC_CTRL            */
#define CORDIC_CTRL_MODE_P2C                   (_CORDIC_CTRL_MODE_P2C << 0)             /**< Shifted mode P2C for CORDIC_CTRL            */
#define CORDIC_CTRL_MODE_I2ME                  (_CORDIC_CTRL_MODE_I2ME << 0)            /**< Shifted mode I2ME for CORDIC_CTRL           */
#define CORDIC_CTRL_MODE_NOTUSED               (_CORDIC_CTRL_MODE_NOTUSED << 0)         /**< Shifted mode NOTUSED for CORDIC_CTRL        */
#define _CORDIC_CTRL_NITER_SHIFT               2                                        /**< Shift value for CORDIC_NITER                */
#define _CORDIC_CTRL_NITER_MASK                0x3CUL                                   /**< Bit mask for CORDIC_NITER                   */
#define _CORDIC_CTRL_NITER_DEFAULT             0x0000000AUL                             /**< Mode DEFAULT for CORDIC_CTRL                */
#define CORDIC_CTRL_NITER_DEFAULT              (_CORDIC_CTRL_NITER_DEFAULT << 2)        /**< Shifted mode DEFAULT for CORDIC_CTRL        */
#define CORDIC_CTRL_INTYPE                     (0x1UL << 6)                             /**< New BitField                                */
#define _CORDIC_CTRL_INTYPE_SHIFT              6                                        /**< Shift value for CORDIC_INTYPE               */
#define _CORDIC_CTRL_INTYPE_MASK               0x40UL                                   /**< Bit mask for CORDIC_INTYPE                  */
#define _CORDIC_CTRL_INTYPE_DEFAULT            0x00000000UL                             /**< Mode DEFAULT for CORDIC_CTRL                */
#define _CORDIC_CTRL_INTYPE_UNSIGNED           0x00000000UL                             /**< Mode UNSIGNED for CORDIC_CTRL               */
#define _CORDIC_CTRL_INTYPE_SIGNED             0x00000001UL                             /**< Mode SIGNED for CORDIC_CTRL                 */
#define CORDIC_CTRL_INTYPE_DEFAULT             (_CORDIC_CTRL_INTYPE_DEFAULT << 6)       /**< Shifted mode DEFAULT for CORDIC_CTRL        */
#define CORDIC_CTRL_INTYPE_UNSIGNED            (_CORDIC_CTRL_INTYPE_UNSIGNED << 6)      /**< Shifted mode UNSIGNED for CORDIC_CTRL       */
#define CORDIC_CTRL_INTYPE_SIGNED              (_CORDIC_CTRL_INTYPE_SIGNED << 6)        /**< Shifted mode SIGNED for CORDIC_CTRL         */

/* Bit fields for CORDIC UNWRAP */
#define _CORDIC_UNWRAP_RESETVALUE              0x00000000UL                               /**< Default value for CORDIC_UNWRAP             */
#define _CORDIC_UNWRAP_MASK                    0x000FFF8FUL                               /**< Mask for CORDIC_UNWRAP                      */
#define CORDIC_UNWRAP_ENAB                     (0x1UL << 0)                               /**< Phase Unwrap Enable                         */
#define _CORDIC_UNWRAP_ENAB_SHIFT              0                                          /**< Shift value for CORDIC_ENAB                 */
#define _CORDIC_UNWRAP_ENAB_MASK               0x1UL                                      /**< Bit mask for CORDIC_ENAB                    */
#define _CORDIC_UNWRAP_ENAB_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for CORDIC_UNWRAP              */
#define _CORDIC_UNWRAP_ENAB_DISABLE            0x00000000UL                               /**< Mode DISABLE for CORDIC_UNWRAP              */
#define _CORDIC_UNWRAP_ENAB_ENABLE             0x00000001UL                               /**< Mode ENABLE for CORDIC_UNWRAP               */
#define CORDIC_UNWRAP_ENAB_DEFAULT             (_CORDIC_UNWRAP_ENAB_DEFAULT << 0)         /**< Shifted mode DEFAULT for CORDIC_UNWRAP      */
#define CORDIC_UNWRAP_ENAB_DISABLE             (_CORDIC_UNWRAP_ENAB_DISABLE << 0)         /**< Shifted mode DISABLE for CORDIC_UNWRAP      */
#define CORDIC_UNWRAP_ENAB_ENABLE              (_CORDIC_UNWRAP_ENAB_ENABLE << 0)          /**< Shifted mode ENABLE for CORDIC_UNWRAP       */
#define CORDIC_UNWRAP_MODE                     (0x1UL << 1)                               /**< Phase Unwrap Mode                           */
#define _CORDIC_UNWRAP_MODE_SHIFT              1                                          /**< Shift value for CORDIC_MODE                 */
#define _CORDIC_UNWRAP_MODE_MASK               0x2UL                                      /**< Bit mask for CORDIC_MODE                    */
#define _CORDIC_UNWRAP_MODE_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for CORDIC_UNWRAP              */
#define _CORDIC_UNWRAP_MODE_MODE0              0x00000000UL                               /**< Mode MODE0 for CORDIC_UNWRAP                */
#define _CORDIC_UNWRAP_MODE_MODE1              0x00000001UL                               /**< Mode MODE1 for CORDIC_UNWRAP                */
#define CORDIC_UNWRAP_MODE_DEFAULT             (_CORDIC_UNWRAP_MODE_DEFAULT << 1)         /**< Shifted mode DEFAULT for CORDIC_UNWRAP      */
#define CORDIC_UNWRAP_MODE_MODE0               (_CORDIC_UNWRAP_MODE_MODE0 << 1)           /**< Shifted mode MODE0 for CORDIC_UNWRAP        */
#define CORDIC_UNWRAP_MODE_MODE1               (_CORDIC_UNWRAP_MODE_MODE1 << 1)           /**< Shifted mode MODE1 for CORDIC_UNWRAP        */
#define CORDIC_UNWRAP_DIFFDIS                  (0x1UL << 2)                               /**< Phase Unwrap Diff Disable                   */
#define _CORDIC_UNWRAP_DIFFDIS_SHIFT           2                                          /**< Shift value for CORDIC_DIFFDIS              */
#define _CORDIC_UNWRAP_DIFFDIS_MASK            0x4UL                                      /**< Bit mask for CORDIC_DIFFDIS                 */
#define _CORDIC_UNWRAP_DIFFDIS_DEFAULT         0x00000000UL                               /**< Mode DEFAULT for CORDIC_UNWRAP              */
#define _CORDIC_UNWRAP_DIFFDIS_ENABLED         0x00000000UL                               /**< Mode ENABLED for CORDIC_UNWRAP              */
#define _CORDIC_UNWRAP_DIFFDIS_DISABLED        0x00000001UL                               /**< Mode DISABLED for CORDIC_UNWRAP             */
#define CORDIC_UNWRAP_DIFFDIS_DEFAULT          (_CORDIC_UNWRAP_DIFFDIS_DEFAULT << 2)      /**< Shifted mode DEFAULT for CORDIC_UNWRAP      */
#define CORDIC_UNWRAP_DIFFDIS_ENABLED          (_CORDIC_UNWRAP_DIFFDIS_ENABLED << 2)      /**< Shifted mode ENABLED for CORDIC_UNWRAP      */
#define CORDIC_UNWRAP_DIFFDIS_DISABLED         (_CORDIC_UNWRAP_DIFFDIS_DISABLED << 2)     /**< Shifted mode DISABLED for CORDIC_UNWRAP     */
#define CORDIC_UNWRAP_SATDIS                   (0x1UL << 3)                               /**< Phase Unwrap Saturate Disable               */
#define _CORDIC_UNWRAP_SATDIS_SHIFT            3                                          /**< Shift value for CORDIC_SATDIS               */
#define _CORDIC_UNWRAP_SATDIS_MASK             0x8UL                                      /**< Bit mask for CORDIC_SATDIS                  */
#define _CORDIC_UNWRAP_SATDIS_DEFAULT          0x00000000UL                               /**< Mode DEFAULT for CORDIC_UNWRAP              */
#define _CORDIC_UNWRAP_SATDIS_SATURATE         0x00000000UL                               /**< Mode SATURATE for CORDIC_UNWRAP             */
#define _CORDIC_UNWRAP_SATDIS_WRAP             0x00000001UL                               /**< Mode WRAP for CORDIC_UNWRAP                 */
#define CORDIC_UNWRAP_SATDIS_DEFAULT           (_CORDIC_UNWRAP_SATDIS_DEFAULT << 3)       /**< Shifted mode DEFAULT for CORDIC_UNWRAP      */
#define CORDIC_UNWRAP_SATDIS_SATURATE          (_CORDIC_UNWRAP_SATDIS_SATURATE << 3)      /**< Shifted mode SATURATE for CORDIC_UNWRAP     */
#define CORDIC_UNWRAP_SATDIS_WRAP              (_CORDIC_UNWRAP_SATDIS_WRAP << 3)          /**< Shifted mode WRAP for CORDIC_UNWRAP         */
#define CORDIC_UNWRAP_CORDICBYP                (0x1UL << 7)                               /**< Cordic Bypass                               */
#define _CORDIC_UNWRAP_CORDICBYP_SHIFT         7                                          /**< Shift value for CORDIC_CORDICBYP            */
#define _CORDIC_UNWRAP_CORDICBYP_MASK          0x80UL                                     /**< Bit mask for CORDIC_CORDICBYP               */
#define _CORDIC_UNWRAP_CORDICBYP_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CORDIC_UNWRAP              */
#define _CORDIC_UNWRAP_CORDICBYP_NOT_BYPASS    0x00000000UL                               /**< Mode NOT_BYPASS for CORDIC_UNWRAP           */
#define _CORDIC_UNWRAP_CORDICBYP_BYPASS        0x00000001UL                               /**< Mode BYPASS for CORDIC_UNWRAP               */
#define CORDIC_UNWRAP_CORDICBYP_DEFAULT        (_CORDIC_UNWRAP_CORDICBYP_DEFAULT << 7)    /**< Shifted mode DEFAULT for CORDIC_UNWRAP      */
#define CORDIC_UNWRAP_CORDICBYP_NOT_BYPASS     (_CORDIC_UNWRAP_CORDICBYP_NOT_BYPASS << 7) /**< Shifted mode NOT_BYPASS for CORDIC_UNWRAP   */
#define CORDIC_UNWRAP_CORDICBYP_BYPASS         (_CORDIC_UNWRAP_CORDICBYP_BYPASS << 7)     /**< Shifted mode BYPASS for CORDIC_UNWRAP       */
#define _CORDIC_UNWRAP_OSR_SHIFT               8                                          /**< Shift value for CORDIC_OSR                  */
#define _CORDIC_UNWRAP_OSR_MASK                0xFF00UL                                   /**< Bit mask for CORDIC_OSR                     */
#define _CORDIC_UNWRAP_OSR_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for CORDIC_UNWRAP              */
#define CORDIC_UNWRAP_OSR_DEFAULT              (_CORDIC_UNWRAP_OSR_DEFAULT << 8)          /**< Shifted mode DEFAULT for CORDIC_UNWRAP      */
#define _CORDIC_UNWRAP_NBSHIFT_SHIFT           16                                         /**< Shift value for CORDIC_NBSHIFT              */
#define _CORDIC_UNWRAP_NBSHIFT_MASK            0xF0000UL                                  /**< Bit mask for CORDIC_NBSHIFT                 */
#define _CORDIC_UNWRAP_NBSHIFT_DEFAULT         0x00000000UL                               /**< Mode DEFAULT for CORDIC_UNWRAP              */
#define CORDIC_UNWRAP_NBSHIFT_DEFAULT          (_CORDIC_UNWRAP_NBSHIFT_DEFAULT << 16)     /**< Shifted mode DEFAULT for CORDIC_UNWRAP      */

/** @} End of group EFR32FG25_CORDIC_BitFields */
/** @} End of group EFR32FG25_CORDIC */
/** @} End of group Parts */

#endif /* EFR32FG25_CORDIC_H */
