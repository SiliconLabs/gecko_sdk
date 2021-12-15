/**************************************************************************//**
 * @file
 * @brief EFR32FG25 VIT register and bit field definitions
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
#ifndef EFR32FG25_VIT_H
#define EFR32FG25_VIT_H
#define VIT_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_VIT VIT
 * @{
 * @brief EFR32FG25 VIT Register Declaration.
 *****************************************************************************/

/** VIT Register Declaration. */
typedef struct {
  __IM uint32_t  IPVERSION;                     /**< IP Version ID                                      */
  __IOM uint32_t EN;                            /**< Module Enable                                      */
  __IOM uint32_t SWRST;                         /**< Software Reset                                     */
  __IOM uint32_t CONNECT;                       /**< New Register                                       */
  __IOM uint32_t DISCLK;                        /**< Disable Clocks                                     */
  uint32_t       RESERVED0[3U];                 /**< Reserved for future use                            */
  __IOM uint32_t FIFOIN;                        /**< New Register                                       */
  uint32_t       RESERVED1[7U];                 /**< Reserved for future use                            */
  __IM uint32_t  FIFOOUT;                       /**< New Register                                       */
  uint32_t       RESERVED2[23U];                /**< Reserved for future use                            */
  __IOM uint32_t FMTIN;                         /**< New Register                                       */
  uint32_t       RESERVED3[7U];                 /**< Reserved for future use                            */
  __IOM uint32_t FMTOUT;                        /**< New Register                                       */
  uint32_t       RESERVED4[79U];                /**< Reserved for future use                            */
  __IOM uint32_t CTRL;                          /**< New Register                                       */
  __IOM uint32_t POLY;                          /**< New Register                                       */
  __IOM uint32_t PUNCT;                         /**< New Register                                       */
  __IOM uint32_t FRAME;                         /**< New Register                                       */
  __IOM uint32_t PM;                            /**< New Register                                       */
  __IOM uint32_t DISCLKCNT;                     /**< New Register                                       */
  __IM uint32_t  STAT;                          /**< New Register                                       */
  __IM uint32_t  FRAMEOUT;                      /**< New Register                                       */
  __IM uint32_t  SYNDROME;                      /**< New Register                                       */
  __IOM uint32_t IF;                            /**< Interrupt Flag                                     */
  __IOM uint32_t IEN;                           /**< Interrupt Enable                                   */
  uint32_t       RESERVED5[885U];               /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_SET;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_SET;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_SET;                   /**< New Register                                       */
  __IOM uint32_t DISCLK_SET;                    /**< Disable Clocks                                     */
  uint32_t       RESERVED6[3U];                 /**< Reserved for future use                            */
  __IOM uint32_t FIFOIN_SET;                    /**< New Register                                       */
  uint32_t       RESERVED7[7U];                 /**< Reserved for future use                            */
  __IM uint32_t  FIFOOUT_SET;                   /**< New Register                                       */
  uint32_t       RESERVED8[23U];                /**< Reserved for future use                            */
  __IOM uint32_t FMTIN_SET;                     /**< New Register                                       */
  uint32_t       RESERVED9[7U];                 /**< Reserved for future use                            */
  __IOM uint32_t FMTOUT_SET;                    /**< New Register                                       */
  uint32_t       RESERVED10[79U];               /**< Reserved for future use                            */
  __IOM uint32_t CTRL_SET;                      /**< New Register                                       */
  __IOM uint32_t POLY_SET;                      /**< New Register                                       */
  __IOM uint32_t PUNCT_SET;                     /**< New Register                                       */
  __IOM uint32_t FRAME_SET;                     /**< New Register                                       */
  __IOM uint32_t PM_SET;                        /**< New Register                                       */
  __IOM uint32_t DISCLKCNT_SET;                 /**< New Register                                       */
  __IM uint32_t  STAT_SET;                      /**< New Register                                       */
  __IM uint32_t  FRAMEOUT_SET;                  /**< New Register                                       */
  __IM uint32_t  SYNDROME_SET;                  /**< New Register                                       */
  __IOM uint32_t IF_SET;                        /**< Interrupt Flag                                     */
  __IOM uint32_t IEN_SET;                       /**< Interrupt Enable                                   */
  uint32_t       RESERVED11[885U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_CLR;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_CLR;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_CLR;                   /**< New Register                                       */
  __IOM uint32_t DISCLK_CLR;                    /**< Disable Clocks                                     */
  uint32_t       RESERVED12[3U];                /**< Reserved for future use                            */
  __IOM uint32_t FIFOIN_CLR;                    /**< New Register                                       */
  uint32_t       RESERVED13[7U];                /**< Reserved for future use                            */
  __IM uint32_t  FIFOOUT_CLR;                   /**< New Register                                       */
  uint32_t       RESERVED14[23U];               /**< Reserved for future use                            */
  __IOM uint32_t FMTIN_CLR;                     /**< New Register                                       */
  uint32_t       RESERVED15[7U];                /**< Reserved for future use                            */
  __IOM uint32_t FMTOUT_CLR;                    /**< New Register                                       */
  uint32_t       RESERVED16[79U];               /**< Reserved for future use                            */
  __IOM uint32_t CTRL_CLR;                      /**< New Register                                       */
  __IOM uint32_t POLY_CLR;                      /**< New Register                                       */
  __IOM uint32_t PUNCT_CLR;                     /**< New Register                                       */
  __IOM uint32_t FRAME_CLR;                     /**< New Register                                       */
  __IOM uint32_t PM_CLR;                        /**< New Register                                       */
  __IOM uint32_t DISCLKCNT_CLR;                 /**< New Register                                       */
  __IM uint32_t  STAT_CLR;                      /**< New Register                                       */
  __IM uint32_t  FRAMEOUT_CLR;                  /**< New Register                                       */
  __IM uint32_t  SYNDROME_CLR;                  /**< New Register                                       */
  __IOM uint32_t IF_CLR;                        /**< Interrupt Flag                                     */
  __IOM uint32_t IEN_CLR;                       /**< Interrupt Enable                                   */
  uint32_t       RESERVED17[885U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_TGL;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_TGL;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_TGL;                   /**< New Register                                       */
  __IOM uint32_t DISCLK_TGL;                    /**< Disable Clocks                                     */
  uint32_t       RESERVED18[3U];                /**< Reserved for future use                            */
  __IOM uint32_t FIFOIN_TGL;                    /**< New Register                                       */
  uint32_t       RESERVED19[7U];                /**< Reserved for future use                            */
  __IM uint32_t  FIFOOUT_TGL;                   /**< New Register                                       */
  uint32_t       RESERVED20[23U];               /**< Reserved for future use                            */
  __IOM uint32_t FMTIN_TGL;                     /**< New Register                                       */
  uint32_t       RESERVED21[7U];                /**< Reserved for future use                            */
  __IOM uint32_t FMTOUT_TGL;                    /**< New Register                                       */
  uint32_t       RESERVED22[79U];               /**< Reserved for future use                            */
  __IOM uint32_t CTRL_TGL;                      /**< New Register                                       */
  __IOM uint32_t POLY_TGL;                      /**< New Register                                       */
  __IOM uint32_t PUNCT_TGL;                     /**< New Register                                       */
  __IOM uint32_t FRAME_TGL;                     /**< New Register                                       */
  __IOM uint32_t PM_TGL;                        /**< New Register                                       */
  __IOM uint32_t DISCLKCNT_TGL;                 /**< New Register                                       */
  __IM uint32_t  STAT_TGL;                      /**< New Register                                       */
  __IM uint32_t  FRAMEOUT_TGL;                  /**< New Register                                       */
  __IM uint32_t  SYNDROME_TGL;                  /**< New Register                                       */
  __IOM uint32_t IF_TGL;                        /**< Interrupt Flag                                     */
  __IOM uint32_t IEN_TGL;                       /**< Interrupt Enable                                   */
} VIT_TypeDef;
/** @} End of group EFR32FG25_VIT */

/**************************************************************************//**
 * @addtogroup EFR32FG25_VIT
 * @{
 * @defgroup EFR32FG25_VIT_BitFields VIT Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for VIT IPVERSION */
#define _VIT_IPVERSION_RESETVALUE            0x00000001UL                               /**< Default value for VIT_IPVERSION             */
#define _VIT_IPVERSION_MASK                  0xFFFFFFFFUL                               /**< Mask for VIT_IPVERSION                      */
#define _VIT_IPVERSION_IPVERSION_SHIFT       0                                          /**< Shift value for VIT_IPVERSION               */
#define _VIT_IPVERSION_IPVERSION_MASK        0xFFFFFFFFUL                               /**< Bit mask for VIT_IPVERSION                  */
#define _VIT_IPVERSION_IPVERSION_DEFAULT     0x00000001UL                               /**< Mode DEFAULT for VIT_IPVERSION              */
#define VIT_IPVERSION_IPVERSION_DEFAULT      (_VIT_IPVERSION_IPVERSION_DEFAULT << 0)    /**< Shifted mode DEFAULT for VIT_IPVERSION      */

/* Bit fields for VIT EN */
#define _VIT_EN_RESETVALUE                   0x00000000UL                               /**< Default value for VIT_EN                    */
#define _VIT_EN_MASK                         0x00000003UL                               /**< Mask for VIT_EN                             */
#define VIT_EN_EN                            (0x1UL << 0)                               /**< Module Enable                               */
#define _VIT_EN_EN_SHIFT                     0                                          /**< Shift value for VIT_EN                      */
#define _VIT_EN_EN_MASK                      0x1UL                                      /**< Bit mask for VIT_EN                         */
#define _VIT_EN_EN_DEFAULT                   0x00000000UL                               /**< Mode DEFAULT for VIT_EN                     */
#define VIT_EN_EN_DEFAULT                    (_VIT_EN_EN_DEFAULT << 0)                  /**< Shifted mode DEFAULT for VIT_EN             */
#define VIT_EN_DISABLING                     (0x1UL << 1)                               /**< Disablement Busy Status                     */
#define _VIT_EN_DISABLING_SHIFT              1                                          /**< Shift value for VIT_DISABLING               */
#define _VIT_EN_DISABLING_MASK               0x2UL                                      /**< Bit mask for VIT_DISABLING                  */
#define _VIT_EN_DISABLING_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for VIT_EN                     */
#define VIT_EN_DISABLING_DEFAULT             (_VIT_EN_DISABLING_DEFAULT << 1)           /**< Shifted mode DEFAULT for VIT_EN             */

/* Bit fields for VIT SWRST */
#define _VIT_SWRST_RESETVALUE                0x00000000UL                               /**< Default value for VIT_SWRST                 */
#define _VIT_SWRST_MASK                      0x00000003UL                               /**< Mask for VIT_SWRST                          */
#define VIT_SWRST_SWRST                      (0x1UL << 0)                               /**< Software Reset Command                      */
#define _VIT_SWRST_SWRST_SHIFT               0                                          /**< Shift value for VIT_SWRST                   */
#define _VIT_SWRST_SWRST_MASK                0x1UL                                      /**< Bit mask for VIT_SWRST                      */
#define _VIT_SWRST_SWRST_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for VIT_SWRST                  */
#define VIT_SWRST_SWRST_DEFAULT              (_VIT_SWRST_SWRST_DEFAULT << 0)            /**< Shifted mode DEFAULT for VIT_SWRST          */
#define VIT_SWRST_RESETTING                  (0x1UL << 1)                               /**< Software Reset Busy Status                  */
#define _VIT_SWRST_RESETTING_SHIFT           1                                          /**< Shift value for VIT_RESETTING               */
#define _VIT_SWRST_RESETTING_MASK            0x2UL                                      /**< Bit mask for VIT_RESETTING                  */
#define _VIT_SWRST_RESETTING_DEFAULT         0x00000000UL                               /**< Mode DEFAULT for VIT_SWRST                  */
#define VIT_SWRST_RESETTING_DEFAULT          (_VIT_SWRST_RESETTING_DEFAULT << 1)        /**< Shifted mode DEFAULT for VIT_SWRST          */

/* Bit fields for VIT CONNECT */
#define _VIT_CONNECT_RESETVALUE              0x00000000UL                               /**< Default value for VIT_CONNECT               */
#define _VIT_CONNECT_MASK                    0x00000101UL                               /**< Mask for VIT_CONNECT                        */
#define VIT_CONNECT_IN                       (0x1UL << 0)                               /**< Input FIFO connect                          */
#define _VIT_CONNECT_IN_SHIFT                0                                          /**< Shift value for VIT_IN                      */
#define _VIT_CONNECT_IN_MASK                 0x1UL                                      /**< Bit mask for VIT_IN                         */
#define _VIT_CONNECT_IN_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for VIT_CONNECT                */
#define VIT_CONNECT_IN_DEFAULT               (_VIT_CONNECT_IN_DEFAULT << 0)             /**< Shifted mode DEFAULT for VIT_CONNECT        */
#define VIT_CONNECT_OUT                      (0x1UL << 8)                               /**< Output FIFO connect                         */
#define _VIT_CONNECT_OUT_SHIFT               8                                          /**< Shift value for VIT_OUT                     */
#define _VIT_CONNECT_OUT_MASK                0x100UL                                    /**< Bit mask for VIT_OUT                        */
#define _VIT_CONNECT_OUT_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for VIT_CONNECT                */
#define VIT_CONNECT_OUT_DEFAULT              (_VIT_CONNECT_OUT_DEFAULT << 8)            /**< Shifted mode DEFAULT for VIT_CONNECT        */

/* Bit fields for VIT DISCLK */
#define _VIT_DISCLK_RESETVALUE               0x00000002UL                               /**< Default value for VIT_DISCLK                */
#define _VIT_DISCLK_MASK                     0x00000003UL                               /**< Mask for VIT_DISCLK                         */
#define _VIT_DISCLK_DISCLK_SHIFT             0                                          /**< Shift value for VIT_DISCLK                  */
#define _VIT_DISCLK_DISCLK_MASK              0x3UL                                      /**< Bit mask for VIT_DISCLK                     */
#define _VIT_DISCLK_DISCLK_DEFAULT           0x00000002UL                               /**< Mode DEFAULT for VIT_DISCLK                 */
#define _VIT_DISCLK_DISCLK_NONE              0x00000000UL                               /**< Mode NONE for VIT_DISCLK                    */
#define _VIT_DISCLK_DISCLK_ALL               0x00000001UL                               /**< Mode ALL for VIT_DISCLK                     */
#define _VIT_DISCLK_DISCLK_AUTO              0x00000002UL                               /**< Mode AUTO for VIT_DISCLK                    */
#define VIT_DISCLK_DISCLK_DEFAULT            (_VIT_DISCLK_DISCLK_DEFAULT << 0)          /**< Shifted mode DEFAULT for VIT_DISCLK         */
#define VIT_DISCLK_DISCLK_NONE               (_VIT_DISCLK_DISCLK_NONE << 0)             /**< Shifted mode NONE for VIT_DISCLK            */
#define VIT_DISCLK_DISCLK_ALL                (_VIT_DISCLK_DISCLK_ALL << 0)              /**< Shifted mode ALL for VIT_DISCLK             */
#define VIT_DISCLK_DISCLK_AUTO               (_VIT_DISCLK_DISCLK_AUTO << 0)             /**< Shifted mode AUTO for VIT_DISCLK            */

/* Bit fields for VIT FIFOIN */
#define _VIT_FIFOIN_RESETVALUE               0x00000000UL                               /**< Default value for VIT_FIFOIN                */
#define _VIT_FIFOIN_MASK                     0x1FFF3F0FUL                               /**< Mask for VIT_FIFOIN                         */
#define _VIT_FIFOIN_FID_SHIFT                0                                          /**< Shift value for VIT_FID                     */
#define _VIT_FIFOIN_FID_MASK                 0xFUL                                      /**< Bit mask for VIT_FID                        */
#define _VIT_FIFOIN_FID_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for VIT_FIFOIN                 */
#define VIT_FIFOIN_FID_DEFAULT               (_VIT_FIFOIN_FID_DEFAULT << 0)             /**< Shifted mode DEFAULT for VIT_FIFOIN         */
#define _VIT_FIFOIN_CID_SHIFT                8                                          /**< Shift value for VIT_CID                     */
#define _VIT_FIFOIN_CID_MASK                 0x3F00UL                                   /**< Bit mask for VIT_CID                        */
#define _VIT_FIFOIN_CID_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for VIT_FIFOIN                 */
#define VIT_FIFOIN_CID_DEFAULT               (_VIT_FIFOIN_CID_DEFAULT << 8)             /**< Shifted mode DEFAULT for VIT_FIFOIN         */
#define _VIT_FIFOIN_REM_SHIFT                16                                         /**< Shift value for VIT_REM                     */
#define _VIT_FIFOIN_REM_MASK                 0xFF0000UL                                 /**< Bit mask for VIT_REM                        */
#define _VIT_FIFOIN_REM_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for VIT_FIFOIN                 */
#define VIT_FIFOIN_REM_DEFAULT               (_VIT_FIFOIN_REM_DEFAULT << 16)            /**< Shifted mode DEFAULT for VIT_FIFOIN         */
#define _VIT_FIFOIN_ALARM_SHIFT              24                                         /**< Shift value for VIT_ALARM                   */
#define _VIT_FIFOIN_ALARM_MASK               0x1F000000UL                               /**< Bit mask for VIT_ALARM                      */
#define _VIT_FIFOIN_ALARM_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for VIT_FIFOIN                 */
#define VIT_FIFOIN_ALARM_DEFAULT             (_VIT_FIFOIN_ALARM_DEFAULT << 24)          /**< Shifted mode DEFAULT for VIT_FIFOIN         */

/* Bit fields for VIT FIFOOUT */
#define _VIT_FIFOOUT_RESETVALUE              0x00000000UL                               /**< Default value for VIT_FIFOOUT               */
#define _VIT_FIFOOUT_MASK                    0x1FFF0000UL                               /**< Mask for VIT_FIFOOUT                        */
#define _VIT_FIFOOUT_CNT_SHIFT               16                                         /**< Shift value for VIT_CNT                     */
#define _VIT_FIFOOUT_CNT_MASK                0xFF0000UL                                 /**< Bit mask for VIT_CNT                        */
#define _VIT_FIFOOUT_CNT_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for VIT_FIFOOUT                */
#define VIT_FIFOOUT_CNT_DEFAULT              (_VIT_FIFOOUT_CNT_DEFAULT << 16)           /**< Shifted mode DEFAULT for VIT_FIFOOUT        */
#define _VIT_FIFOOUT_ALARM_SHIFT             24                                         /**< Shift value for VIT_ALARM                   */
#define _VIT_FIFOOUT_ALARM_MASK              0x1F000000UL                               /**< Bit mask for VIT_ALARM                      */
#define _VIT_FIFOOUT_ALARM_DEFAULT           0x00000000UL                               /**< Mode DEFAULT for VIT_FIFOOUT                */
#define VIT_FIFOOUT_ALARM_DEFAULT            (_VIT_FIFOOUT_ALARM_DEFAULT << 24)         /**< Shifted mode DEFAULT for VIT_FIFOOUT        */

/* Bit fields for VIT FMTIN */
#define _VIT_FMTIN_RESETVALUE                0x00000000UL                               /**< Default value for VIT_FMTIN                 */
#define _VIT_FMTIN_MASK                      0x00030300UL                               /**< Mask for VIT_FMTIN                          */
#define _VIT_FMTIN_ELEMNB_SHIFT              8                                          /**< Shift value for VIT_ELEMNB                  */
#define _VIT_FMTIN_ELEMNB_MASK               0x300UL                                    /**< Bit mask for VIT_ELEMNB                     */
#define _VIT_FMTIN_ELEMNB_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for VIT_FMTIN                  */
#define _VIT_FMTIN_ELEMNB_ONE                0x00000000UL                               /**< Mode ONE for VIT_FMTIN                      */
#define _VIT_FMTIN_ELEMNB_TWO                0x00000001UL                               /**< Mode TWO for VIT_FMTIN                      */
#define _VIT_FMTIN_ELEMNB_FOUR               0x00000002UL                               /**< Mode FOUR for VIT_FMTIN                     */
#define VIT_FMTIN_ELEMNB_DEFAULT             (_VIT_FMTIN_ELEMNB_DEFAULT << 8)           /**< Shifted mode DEFAULT for VIT_FMTIN          */
#define VIT_FMTIN_ELEMNB_ONE                 (_VIT_FMTIN_ELEMNB_ONE << 8)               /**< Shifted mode ONE for VIT_FMTIN              */
#define VIT_FMTIN_ELEMNB_TWO                 (_VIT_FMTIN_ELEMNB_TWO << 8)               /**< Shifted mode TWO for VIT_FMTIN              */
#define VIT_FMTIN_ELEMNB_FOUR                (_VIT_FMTIN_ELEMNB_FOUR << 8)              /**< Shifted mode FOUR for VIT_FMTIN             */
#define _VIT_FMTIN_ELEMALIGN_SHIFT           16                                         /**< Shift value for VIT_ELEMALIGN               */
#define _VIT_FMTIN_ELEMALIGN_MASK            0x30000UL                                  /**< Bit mask for VIT_ELEMALIGN                  */
#define _VIT_FMTIN_ELEMALIGN_DEFAULT         0x00000000UL                               /**< Mode DEFAULT for VIT_FMTIN                  */
#define _VIT_FMTIN_ELEMALIGN_WORD            0x00000000UL                               /**< Mode WORD for VIT_FMTIN                     */
#define _VIT_FMTIN_ELEMALIGN_HALFWORD        0x00000001UL                               /**< Mode HALFWORD for VIT_FMTIN                 */
#define _VIT_FMTIN_ELEMALIGN_BYTE            0x00000002UL                               /**< Mode BYTE for VIT_FMTIN                     */
#define VIT_FMTIN_ELEMALIGN_DEFAULT          (_VIT_FMTIN_ELEMALIGN_DEFAULT << 16)       /**< Shifted mode DEFAULT for VIT_FMTIN          */
#define VIT_FMTIN_ELEMALIGN_WORD             (_VIT_FMTIN_ELEMALIGN_WORD << 16)          /**< Shifted mode WORD for VIT_FMTIN             */
#define VIT_FMTIN_ELEMALIGN_HALFWORD         (_VIT_FMTIN_ELEMALIGN_HALFWORD << 16)      /**< Shifted mode HALFWORD for VIT_FMTIN         */
#define VIT_FMTIN_ELEMALIGN_BYTE             (_VIT_FMTIN_ELEMALIGN_BYTE << 16)          /**< Shifted mode BYTE for VIT_FMTIN             */

/* Bit fields for VIT FMTOUT */
#define _VIT_FMTOUT_RESETVALUE               0x00000000UL                               /**< Default value for VIT_FMTOUT                */
#define _VIT_FMTOUT_MASK                     0x0000001FUL                               /**< Mask for VIT_FMTOUT                         */
#define _VIT_FMTOUT_ELEMSIZE_SHIFT           0                                          /**< Shift value for VIT_ELEMSIZE                */
#define _VIT_FMTOUT_ELEMSIZE_MASK            0x1FUL                                     /**< Bit mask for VIT_ELEMSIZE                   */
#define _VIT_FMTOUT_ELEMSIZE_DEFAULT         0x00000000UL                               /**< Mode DEFAULT for VIT_FMTOUT                 */
#define VIT_FMTOUT_ELEMSIZE_DEFAULT          (_VIT_FMTOUT_ELEMSIZE_DEFAULT << 0)        /**< Shifted mode DEFAULT for VIT_FMTOUT         */

/* Bit fields for VIT CTRL */
#define _VIT_CTRL_RESETVALUE                 0x0000421EUL                               /**< Default value for VIT_CTRL                  */
#define _VIT_CTRL_MASK                       0xEEFFFFFFUL                               /**< Mask for VIT_CTRL                           */
#define VIT_CTRL_STRUCTURE                   (0x1UL << 0)                               /**< New BitField                                */
#define _VIT_CTRL_STRUCTURE_SHIFT            0                                          /**< Shift value for VIT_STRUCTURE               */
#define _VIT_CTRL_STRUCTURE_MASK             0x1UL                                      /**< Bit mask for VIT_STRUCTURE                  */
#define _VIT_CTRL_STRUCTURE_DEFAULT          0x00000000UL                               /**< Mode DEFAULT for VIT_CTRL                   */
#define _VIT_CTRL_STRUCTURE_non_recursive    0x00000000UL                               /**< Mode non_recursive for VIT_CTRL             */
#define _VIT_CTRL_STRUCTURE_recursive        0x00000001UL                               /**< Mode recursive for VIT_CTRL                 */
#define VIT_CTRL_STRUCTURE_DEFAULT           (_VIT_CTRL_STRUCTURE_DEFAULT << 0)         /**< Shifted mode DEFAULT for VIT_CTRL           */
#define VIT_CTRL_STRUCTURE_non_recursive     (_VIT_CTRL_STRUCTURE_non_recursive << 0)   /**< Shifted mode non_recursive for VIT_CTRL     */
#define VIT_CTRL_STRUCTURE_recursive         (_VIT_CTRL_STRUCTURE_recursive << 0)       /**< Shifted mode recursive for VIT_CTRL         */
#define _VIT_CTRL_CONSTLENGTH_SHIFT          1                                          /**< Shift value for VIT_CONSTLENGTH             */
#define _VIT_CTRL_CONSTLENGTH_MASK           0xEUL                                      /**< Bit mask for VIT_CONSTLENGTH                */
#define _VIT_CTRL_CONSTLENGTH_DEFAULT        0x00000007UL                               /**< Mode DEFAULT for VIT_CTRL                   */
#define VIT_CTRL_CONSTLENGTH_DEFAULT         (_VIT_CTRL_CONSTLENGTH_DEFAULT << 1)       /**< Shifted mode DEFAULT for VIT_CTRL           */
#define _VIT_CTRL_PUNCTPERIOD_SHIFT          4                                          /**< Shift value for VIT_PUNCTPERIOD             */
#define _VIT_CTRL_PUNCTPERIOD_MASK           0x70UL                                     /**< Bit mask for VIT_PUNCTPERIOD                */
#define _VIT_CTRL_PUNCTPERIOD_DEFAULT        0x00000001UL                               /**< Mode DEFAULT for VIT_CTRL                   */
#define VIT_CTRL_PUNCTPERIOD_DEFAULT         (_VIT_CTRL_PUNCTPERIOD_DEFAULT << 4)       /**< Shifted mode DEFAULT for VIT_CTRL           */
#define VIT_CTRL_TAILEN                      (0x1UL << 7)                               /**< New BitField                                */
#define _VIT_CTRL_TAILEN_SHIFT               7                                          /**< Shift value for VIT_TAILEN                  */
#define _VIT_CTRL_TAILEN_MASK                0x80UL                                     /**< Bit mask for VIT_TAILEN                     */
#define _VIT_CTRL_TAILEN_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for VIT_CTRL                   */
#define VIT_CTRL_TAILEN_DEFAULT              (_VIT_CTRL_TAILEN_DEFAULT << 7)            /**< Shifted mode DEFAULT for VIT_CTRL           */
#define VIT_CTRL_PMINIT                      (0x1UL << 8)                               /**< New BitField                                */
#define _VIT_CTRL_PMINIT_SHIFT               8                                          /**< Shift value for VIT_PMINIT                  */
#define _VIT_CTRL_PMINIT_MASK                0x100UL                                    /**< Bit mask for VIT_PMINIT                     */
#define _VIT_CTRL_PMINIT_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for VIT_CTRL                   */
#define VIT_CTRL_PMINIT_DEFAULT              (_VIT_CTRL_PMINIT_DEFAULT << 8)            /**< Shifted mode DEFAULT for VIT_CTRL           */
#define VIT_CTRL_PMTAIL                      (0x1UL << 9)                               /**< New BitField                                */
#define _VIT_CTRL_PMTAIL_SHIFT               9                                          /**< Shift value for VIT_PMTAIL                  */
#define _VIT_CTRL_PMTAIL_MASK                0x200UL                                    /**< Bit mask for VIT_PMTAIL                     */
#define _VIT_CTRL_PMTAIL_DEFAULT             0x00000001UL                               /**< Mode DEFAULT for VIT_CTRL                   */
#define VIT_CTRL_PMTAIL_DEFAULT              (_VIT_CTRL_PMTAIL_DEFAULT << 9)            /**< Shifted mode DEFAULT for VIT_CTRL           */
#define VIT_CTRL_SSUMETHOD                   (0x1UL << 10)                              /**< New BitField                                */
#define _VIT_CTRL_SSUMETHOD_SHIFT            10                                         /**< Shift value for VIT_SSUMETHOD               */
#define _VIT_CTRL_SSUMETHOD_MASK             0x400UL                                    /**< Bit mask for VIT_SSUMETHOD                  */
#define _VIT_CTRL_SSUMETHOD_DEFAULT          0x00000000UL                               /**< Mode DEFAULT for VIT_CTRL                   */
#define _VIT_CTRL_SSUMETHOD_RE               0x00000000UL                               /**< Mode RE for VIT_CTRL                        */
#define _VIT_CTRL_SSUMETHOD_TB               0x00000001UL                               /**< Mode TB for VIT_CTRL                        */
#define VIT_CTRL_SSUMETHOD_DEFAULT           (_VIT_CTRL_SSUMETHOD_DEFAULT << 10)        /**< Shifted mode DEFAULT for VIT_CTRL           */
#define VIT_CTRL_SSUMETHOD_RE                (_VIT_CTRL_SSUMETHOD_RE << 10)             /**< Shifted mode RE for VIT_CTRL                */
#define VIT_CTRL_SSUMETHOD_TB                (_VIT_CTRL_SSUMETHOD_TB << 10)             /**< Shifted mode TB for VIT_CTRL                */
#define _VIT_CTRL_TRUNCLENGTH_SHIFT          11                                         /**< Shift value for VIT_TRUNCLENGTH             */
#define _VIT_CTRL_TRUNCLENGTH_MASK           0x7800UL                                   /**< Bit mask for VIT_TRUNCLENGTH                */
#define _VIT_CTRL_TRUNCLENGTH_DEFAULT        0x00000008UL                               /**< Mode DEFAULT for VIT_CTRL                   */
#define _VIT_CTRL_TRUNCLENGTH_TL0            0x00000000UL                               /**< Mode TL0 for VIT_CTRL                       */
#define _VIT_CTRL_TRUNCLENGTH_TL8            0x00000001UL                               /**< Mode TL8 for VIT_CTRL                       */
#define _VIT_CTRL_TRUNCLENGTH_TL16           0x00000002UL                               /**< Mode TL16 for VIT_CTRL                      */
#define _VIT_CTRL_TRUNCLENGTH_TL24           0x00000003UL                               /**< Mode TL24 for VIT_CTRL                      */
#define _VIT_CTRL_TRUNCLENGTH_TL32           0x00000004UL                               /**< Mode TL32 for VIT_CTRL                      */
#define _VIT_CTRL_TRUNCLENGTH_TL40           0x00000005UL                               /**< Mode TL40 for VIT_CTRL                      */
#define _VIT_CTRL_TRUNCLENGTH_TL48           0x00000006UL                               /**< Mode TL48 for VIT_CTRL                      */
#define _VIT_CTRL_TRUNCLENGTH_TL56           0x00000007UL                               /**< Mode TL56 for VIT_CTRL                      */
#define _VIT_CTRL_TRUNCLENGTH_TL64           0x00000008UL                               /**< Mode TL64 for VIT_CTRL                      */
#define _VIT_CTRL_TRUNCLENGTH_TL72           0x00000009UL                               /**< Mode TL72 for VIT_CTRL                      */
#define _VIT_CTRL_TRUNCLENGTH_TL80           0x0000000AUL                               /**< Mode TL80 for VIT_CTRL                      */
#define _VIT_CTRL_TRUNCLENGTH_TL88           0x0000000BUL                               /**< Mode TL88 for VIT_CTRL                      */
#define _VIT_CTRL_TRUNCLENGTH_TL96           0x0000000CUL                               /**< Mode TL96 for VIT_CTRL                      */
#define VIT_CTRL_TRUNCLENGTH_DEFAULT         (_VIT_CTRL_TRUNCLENGTH_DEFAULT << 11)      /**< Shifted mode DEFAULT for VIT_CTRL           */
#define VIT_CTRL_TRUNCLENGTH_TL0             (_VIT_CTRL_TRUNCLENGTH_TL0 << 11)          /**< Shifted mode TL0 for VIT_CTRL               */
#define VIT_CTRL_TRUNCLENGTH_TL8             (_VIT_CTRL_TRUNCLENGTH_TL8 << 11)          /**< Shifted mode TL8 for VIT_CTRL               */
#define VIT_CTRL_TRUNCLENGTH_TL16            (_VIT_CTRL_TRUNCLENGTH_TL16 << 11)         /**< Shifted mode TL16 for VIT_CTRL              */
#define VIT_CTRL_TRUNCLENGTH_TL24            (_VIT_CTRL_TRUNCLENGTH_TL24 << 11)         /**< Shifted mode TL24 for VIT_CTRL              */
#define VIT_CTRL_TRUNCLENGTH_TL32            (_VIT_CTRL_TRUNCLENGTH_TL32 << 11)         /**< Shifted mode TL32 for VIT_CTRL              */
#define VIT_CTRL_TRUNCLENGTH_TL40            (_VIT_CTRL_TRUNCLENGTH_TL40 << 11)         /**< Shifted mode TL40 for VIT_CTRL              */
#define VIT_CTRL_TRUNCLENGTH_TL48            (_VIT_CTRL_TRUNCLENGTH_TL48 << 11)         /**< Shifted mode TL48 for VIT_CTRL              */
#define VIT_CTRL_TRUNCLENGTH_TL56            (_VIT_CTRL_TRUNCLENGTH_TL56 << 11)         /**< Shifted mode TL56 for VIT_CTRL              */
#define VIT_CTRL_TRUNCLENGTH_TL64            (_VIT_CTRL_TRUNCLENGTH_TL64 << 11)         /**< Shifted mode TL64 for VIT_CTRL              */
#define VIT_CTRL_TRUNCLENGTH_TL72            (_VIT_CTRL_TRUNCLENGTH_TL72 << 11)         /**< Shifted mode TL72 for VIT_CTRL              */
#define VIT_CTRL_TRUNCLENGTH_TL80            (_VIT_CTRL_TRUNCLENGTH_TL80 << 11)         /**< Shifted mode TL80 for VIT_CTRL              */
#define VIT_CTRL_TRUNCLENGTH_TL88            (_VIT_CTRL_TRUNCLENGTH_TL88 << 11)         /**< Shifted mode TL88 for VIT_CTRL              */
#define VIT_CTRL_TRUNCLENGTH_TL96            (_VIT_CTRL_TRUNCLENGTH_TL96 << 11)         /**< Shifted mode TL96 for VIT_CTRL              */
#define VIT_CTRL_TRUNCLENGTHUNIT             (0x1UL << 15)                              /**< New BitField                                */
#define _VIT_CTRL_TRUNCLENGTHUNIT_SHIFT      15                                         /**< Shift value for VIT_TRUNCLENGTHUNIT         */
#define _VIT_CTRL_TRUNCLENGTHUNIT_MASK       0x8000UL                                   /**< Bit mask for VIT_TRUNCLENGTHUNIT            */
#define _VIT_CTRL_TRUNCLENGTHUNIT_DEFAULT    0x00000000UL                               /**< Mode DEFAULT for VIT_CTRL                   */
#define _VIT_CTRL_TRUNCLENGTHUNIT_EIGHT      0x00000000UL                               /**< Mode EIGHT for VIT_CTRL                     */
#define _VIT_CTRL_TRUNCLENGTHUNIT_TWELVE     0x00000001UL                               /**< Mode TWELVE for VIT_CTRL                    */
#define VIT_CTRL_TRUNCLENGTHUNIT_DEFAULT     (_VIT_CTRL_TRUNCLENGTHUNIT_DEFAULT << 15)  /**< Shifted mode DEFAULT for VIT_CTRL           */
#define VIT_CTRL_TRUNCLENGTHUNIT_EIGHT       (_VIT_CTRL_TRUNCLENGTHUNIT_EIGHT << 15)    /**< Shifted mode EIGHT for VIT_CTRL             */
#define VIT_CTRL_TRUNCLENGTHUNIT_TWELVE      (_VIT_CTRL_TRUNCLENGTHUNIT_TWELVE << 15)   /**< Shifted mode TWELVE for VIT_CTRL            */
#define _VIT_CTRL_CKRATIO_SHIFT              16                                         /**< Shift value for VIT_CKRATIO                 */
#define _VIT_CTRL_CKRATIO_MASK               0xF0000UL                                  /**< Bit mask for VIT_CKRATIO                    */
#define _VIT_CTRL_CKRATIO_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for VIT_CTRL                   */
#define VIT_CTRL_CKRATIO_DEFAULT             (_VIT_CTRL_CKRATIO_DEFAULT << 16)          /**< Shifted mode DEFAULT for VIT_CTRL           */
#define VIT_CTRL_SYNDMODE                    (0x1UL << 20)                              /**< New BitField                                */
#define _VIT_CTRL_SYNDMODE_SHIFT             20                                         /**< Shift value for VIT_SYNDMODE                */
#define _VIT_CTRL_SYNDMODE_MASK              0x100000UL                                 /**< Bit mask for VIT_SYNDMODE                   */
#define _VIT_CTRL_SYNDMODE_DEFAULT           0x00000000UL                               /**< Mode DEFAULT for VIT_CTRL                   */
#define _VIT_CTRL_SYNDMODE_LEGACY            0x00000000UL                               /**< Mode LEGACY for VIT_CTRL                    */
#define _VIT_CTRL_SYNDMODE_NEW               0x00000001UL                               /**< Mode NEW for VIT_CTRL                       */
#define VIT_CTRL_SYNDMODE_DEFAULT            (_VIT_CTRL_SYNDMODE_DEFAULT << 20)         /**< Shifted mode DEFAULT for VIT_CTRL           */
#define VIT_CTRL_SYNDMODE_LEGACY             (_VIT_CTRL_SYNDMODE_LEGACY << 20)          /**< Shifted mode LEGACY for VIT_CTRL            */
#define VIT_CTRL_SYNDMODE_NEW                (_VIT_CTRL_SYNDMODE_NEW << 20)             /**< Shifted mode NEW for VIT_CTRL               */
#define _VIT_CTRL_INV_SHIFT                  21                                         /**< Shift value for VIT_INV                     */
#define _VIT_CTRL_INV_MASK                   0xE00000UL                                 /**< Bit mask for VIT_INV                        */
#define _VIT_CTRL_INV_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for VIT_CTRL                   */
#define VIT_CTRL_INV_DEFAULT                 (_VIT_CTRL_INV_DEFAULT << 21)              /**< Shifted mode DEFAULT for VIT_CTRL           */
#define _VIT_CTRL_NONSYST_SHIFT              25                                         /**< Shift value for VIT_NONSYST                 */
#define _VIT_CTRL_NONSYST_MASK               0xE000000UL                                /**< Bit mask for VIT_NONSYST                    */
#define _VIT_CTRL_NONSYST_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for VIT_CTRL                   */
#define VIT_CTRL_NONSYST_DEFAULT             (_VIT_CTRL_NONSYST_DEFAULT << 25)          /**< Shifted mode DEFAULT for VIT_CTRL           */
#define _VIT_CTRL_RECURSEL_SHIFT             29                                         /**< Shift value for VIT_RECURSEL                */
#define _VIT_CTRL_RECURSEL_MASK              0x60000000UL                               /**< Bit mask for VIT_RECURSEL                   */
#define _VIT_CTRL_RECURSEL_DEFAULT           0x00000000UL                               /**< Mode DEFAULT for VIT_CTRL                   */
#define VIT_CTRL_RECURSEL_DEFAULT            (_VIT_CTRL_RECURSEL_DEFAULT << 29)         /**< Shifted mode DEFAULT for VIT_CTRL           */
#define VIT_CTRL_MAPINVERT                   (0x1UL << 31)                              /**< New BitField                                */
#define _VIT_CTRL_MAPINVERT_SHIFT            31                                         /**< Shift value for VIT_MAPINVERT               */
#define _VIT_CTRL_MAPINVERT_MASK             0x80000000UL                               /**< Bit mask for VIT_MAPINVERT                  */
#define _VIT_CTRL_MAPINVERT_DEFAULT          0x00000000UL                               /**< Mode DEFAULT for VIT_CTRL                   */
#define VIT_CTRL_MAPINVERT_DEFAULT           (_VIT_CTRL_MAPINVERT_DEFAULT << 31)        /**< Shifted mode DEFAULT for VIT_CTRL           */

/* Bit fields for VIT POLY */
#define _VIT_POLY_RESETVALUE                 0x006D6D6DUL                               /**< Default value for VIT_POLY                  */
#define _VIT_POLY_MASK                       0x007F7F7FUL                               /**< Mask for VIT_POLY                           */
#define _VIT_POLY_POLY0_SHIFT                0                                          /**< Shift value for VIT_POLY0                   */
#define _VIT_POLY_POLY0_MASK                 0x7FUL                                     /**< Bit mask for VIT_POLY0                      */
#define _VIT_POLY_POLY0_DEFAULT              0x0000006DUL                               /**< Mode DEFAULT for VIT_POLY                   */
#define VIT_POLY_POLY0_DEFAULT               (_VIT_POLY_POLY0_DEFAULT << 0)             /**< Shifted mode DEFAULT for VIT_POLY           */
#define _VIT_POLY_POLY1_SHIFT                8                                          /**< Shift value for VIT_POLY1                   */
#define _VIT_POLY_POLY1_MASK                 0x7F00UL                                   /**< Bit mask for VIT_POLY1                      */
#define _VIT_POLY_POLY1_DEFAULT              0x0000006DUL                               /**< Mode DEFAULT for VIT_POLY                   */
#define VIT_POLY_POLY1_DEFAULT               (_VIT_POLY_POLY1_DEFAULT << 8)             /**< Shifted mode DEFAULT for VIT_POLY           */
#define _VIT_POLY_POLY2_SHIFT                16                                         /**< Shift value for VIT_POLY2                   */
#define _VIT_POLY_POLY2_MASK                 0x7F0000UL                                 /**< Bit mask for VIT_POLY2                      */
#define _VIT_POLY_POLY2_DEFAULT              0x0000006DUL                               /**< Mode DEFAULT for VIT_POLY                   */
#define VIT_POLY_POLY2_DEFAULT               (_VIT_POLY_POLY2_DEFAULT << 16)            /**< Shifted mode DEFAULT for VIT_POLY           */

/* Bit fields for VIT PUNCT */
#define _VIT_PUNCT_RESETVALUE                0x00010101UL                               /**< Default value for VIT_PUNCT                 */
#define _VIT_PUNCT_MASK                      0x00FFFFFFUL                               /**< Mask for VIT_PUNCT                          */
#define _VIT_PUNCT_PUNCT0_SHIFT              0                                          /**< Shift value for VIT_PUNCT0                  */
#define _VIT_PUNCT_PUNCT0_MASK               0xFFUL                                     /**< Bit mask for VIT_PUNCT0                     */
#define _VIT_PUNCT_PUNCT0_DEFAULT            0x00000001UL                               /**< Mode DEFAULT for VIT_PUNCT                  */
#define VIT_PUNCT_PUNCT0_DEFAULT             (_VIT_PUNCT_PUNCT0_DEFAULT << 0)           /**< Shifted mode DEFAULT for VIT_PUNCT          */
#define _VIT_PUNCT_PUNCT1_SHIFT              8                                          /**< Shift value for VIT_PUNCT1                  */
#define _VIT_PUNCT_PUNCT1_MASK               0xFF00UL                                   /**< Bit mask for VIT_PUNCT1                     */
#define _VIT_PUNCT_PUNCT1_DEFAULT            0x00000001UL                               /**< Mode DEFAULT for VIT_PUNCT                  */
#define VIT_PUNCT_PUNCT1_DEFAULT             (_VIT_PUNCT_PUNCT1_DEFAULT << 8)           /**< Shifted mode DEFAULT for VIT_PUNCT          */
#define _VIT_PUNCT_PUNCT2_SHIFT              16                                         /**< Shift value for VIT_PUNCT2                  */
#define _VIT_PUNCT_PUNCT2_MASK               0xFF0000UL                                 /**< Bit mask for VIT_PUNCT2                     */
#define _VIT_PUNCT_PUNCT2_DEFAULT            0x00000001UL                               /**< Mode DEFAULT for VIT_PUNCT                  */
#define VIT_PUNCT_PUNCT2_DEFAULT             (_VIT_PUNCT_PUNCT2_DEFAULT << 16)          /**< Shifted mode DEFAULT for VIT_PUNCT          */

/* Bit fields for VIT FRAME */
#define _VIT_FRAME_RESETVALUE                0x00000000UL                               /**< Default value for VIT_FRAME                 */
#define _VIT_FRAME_MASK                      0x0003FFFFUL                               /**< Mask for VIT_FRAME                          */
#define _VIT_FRAME_LENGTH_SHIFT              0                                          /**< Shift value for VIT_LENGTH                  */
#define _VIT_FRAME_LENGTH_MASK               0x3FFFFUL                                  /**< Bit mask for VIT_LENGTH                     */
#define _VIT_FRAME_LENGTH_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for VIT_FRAME                  */
#define VIT_FRAME_LENGTH_DEFAULT             (_VIT_FRAME_LENGTH_DEFAULT << 0)           /**< Shifted mode DEFAULT for VIT_FRAME          */

/* Bit fields for VIT PM */
#define _VIT_PM_RESETVALUE                   0x00000000UL                               /**< Default value for VIT_PM                    */
#define _VIT_PM_MASK                         0x3FFFFF3FUL                               /**< Mask for VIT_PM                             */
#define _VIT_PM_STATEIDX_SHIFT               0                                          /**< Shift value for VIT_STATEIDX                */
#define _VIT_PM_STATEIDX_MASK                0x3FUL                                     /**< Bit mask for VIT_STATEIDX                   */
#define _VIT_PM_STATEIDX_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for VIT_PM                     */
#define VIT_PM_STATEIDX_DEFAULT              (_VIT_PM_STATEIDX_DEFAULT << 0)            /**< Shifted mode DEFAULT for VIT_PM             */
#define _VIT_PM_STATEVAL_SHIFT               8                                          /**< Shift value for VIT_STATEVAL                */
#define _VIT_PM_STATEVAL_MASK                0x7FF00UL                                  /**< Bit mask for VIT_STATEVAL                   */
#define _VIT_PM_STATEVAL_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for VIT_PM                     */
#define VIT_PM_STATEVAL_DEFAULT              (_VIT_PM_STATEVAL_DEFAULT << 8)            /**< Shifted mode DEFAULT for VIT_PM             */
#define _VIT_PM_STATEDEF_SHIFT               19                                         /**< Shift value for VIT_STATEDEF                */
#define _VIT_PM_STATEDEF_MASK                0x3FF80000UL                               /**< Bit mask for VIT_STATEDEF                   */
#define _VIT_PM_STATEDEF_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for VIT_PM                     */
#define VIT_PM_STATEDEF_DEFAULT              (_VIT_PM_STATEDEF_DEFAULT << 19)           /**< Shifted mode DEFAULT for VIT_PM             */

/* Bit fields for VIT DISCLKCNT */
#define _VIT_DISCLKCNT_RESETVALUE            0x00000000UL                               /**< Default value for VIT_DISCLKCNT             */
#define _VIT_DISCLKCNT_MASK                  0x000000FFUL                               /**< Mask for VIT_DISCLKCNT                      */
#define _VIT_DISCLKCNT_DISCLKCNT_SHIFT       0                                          /**< Shift value for VIT_DISCLKCNT               */
#define _VIT_DISCLKCNT_DISCLKCNT_MASK        0xFFUL                                     /**< Bit mask for VIT_DISCLKCNT                  */
#define _VIT_DISCLKCNT_DISCLKCNT_DEFAULT     0x00000000UL                               /**< Mode DEFAULT for VIT_DISCLKCNT              */
#define VIT_DISCLKCNT_DISCLKCNT_DEFAULT      (_VIT_DISCLKCNT_DISCLKCNT_DEFAULT << 0)    /**< Shifted mode DEFAULT for VIT_DISCLKCNT      */

/* Bit fields for VIT STAT */
#define _VIT_STAT_RESETVALUE                 0x00000000UL                               /**< Default value for VIT_STAT                  */
#define _VIT_STAT_MASK                       0x0F013F3FUL                               /**< Mask for VIT_STAT                           */
#define _VIT_STAT_STATEMIN_SHIFT             0                                          /**< Shift value for VIT_STATEMIN                */
#define _VIT_STAT_STATEMIN_MASK              0x3FUL                                     /**< Bit mask for VIT_STATEMIN                   */
#define _VIT_STAT_STATEMIN_DEFAULT           0x00000000UL                               /**< Mode DEFAULT for VIT_STAT                   */
#define VIT_STAT_STATEMIN_DEFAULT            (_VIT_STAT_STATEMIN_DEFAULT << 0)          /**< Shifted mode DEFAULT for VIT_STAT           */
#define _VIT_STAT_SB_SHIFT                   8                                          /**< Shift value for VIT_SB                      */
#define _VIT_STAT_SB_MASK                    0x3F00UL                                   /**< Bit mask for VIT_SB                         */
#define _VIT_STAT_SB_DEFAULT                 0x00000000UL                               /**< Mode DEFAULT for VIT_STAT                   */
#define VIT_STAT_SB_DEFAULT                  (_VIT_STAT_SB_DEFAULT << 8)                /**< Shifted mode DEFAULT for VIT_STAT           */
#define VIT_STAT_FRAMEAVAIL                  (0x1UL << 16)                              /**< New BitField                                */
#define _VIT_STAT_FRAMEAVAIL_SHIFT           16                                         /**< Shift value for VIT_FRAMEAVAIL              */
#define _VIT_STAT_FRAMEAVAIL_MASK            0x10000UL                                  /**< Bit mask for VIT_FRAMEAVAIL                 */
#define _VIT_STAT_FRAMEAVAIL_DEFAULT         0x00000000UL                               /**< Mode DEFAULT for VIT_STAT                   */
#define VIT_STAT_FRAMEAVAIL_DEFAULT          (_VIT_STAT_FRAMEAVAIL_DEFAULT << 16)       /**< Shifted mode DEFAULT for VIT_STAT           */
#define VIT_STAT_SYNDACTIVE                  (0x1UL << 24)                              /**< New BitField                                */
#define _VIT_STAT_SYNDACTIVE_SHIFT           24                                         /**< Shift value for VIT_SYNDACTIVE              */
#define _VIT_STAT_SYNDACTIVE_MASK            0x1000000UL                                /**< Bit mask for VIT_SYNDACTIVE                 */
#define _VIT_STAT_SYNDACTIVE_DEFAULT         0x00000000UL                               /**< Mode DEFAULT for VIT_STAT                   */
#define VIT_STAT_SYNDACTIVE_DEFAULT          (_VIT_STAT_SYNDACTIVE_DEFAULT << 24)       /**< Shifted mode DEFAULT for VIT_STAT           */
#define VIT_STAT_SYNDTOG                     (0x1UL << 25)                              /**< New BitField                                */
#define _VIT_STAT_SYNDTOG_SHIFT              25                                         /**< Shift value for VIT_SYNDTOG                 */
#define _VIT_STAT_SYNDTOG_MASK               0x2000000UL                                /**< Bit mask for VIT_SYNDTOG                    */
#define _VIT_STAT_SYNDTOG_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for VIT_STAT                   */
#define VIT_STAT_SYNDTOG_DEFAULT             (_VIT_STAT_SYNDTOG_DEFAULT << 25)          /**< Shifted mode DEFAULT for VIT_STAT           */
#define VIT_STAT_SYNDAVAIL                   (0x1UL << 26)                              /**< New BitField                                */
#define _VIT_STAT_SYNDAVAIL_SHIFT            26                                         /**< Shift value for VIT_SYNDAVAIL               */
#define _VIT_STAT_SYNDAVAIL_MASK             0x4000000UL                                /**< Bit mask for VIT_SYNDAVAIL                  */
#define _VIT_STAT_SYNDAVAIL_DEFAULT          0x00000000UL                               /**< Mode DEFAULT for VIT_STAT                   */
#define VIT_STAT_SYNDAVAIL_DEFAULT           (_VIT_STAT_SYNDAVAIL_DEFAULT << 26)        /**< Shifted mode DEFAULT for VIT_STAT           */
#define VIT_STAT_DEPUNCTALARM                (0x1UL << 27)                              /**< New BitField                                */
#define _VIT_STAT_DEPUNCTALARM_SHIFT         27                                         /**< Shift value for VIT_DEPUNCTALARM            */
#define _VIT_STAT_DEPUNCTALARM_MASK          0x8000000UL                                /**< Bit mask for VIT_DEPUNCTALARM               */
#define _VIT_STAT_DEPUNCTALARM_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for VIT_STAT                   */
#define VIT_STAT_DEPUNCTALARM_DEFAULT        (_VIT_STAT_DEPUNCTALARM_DEFAULT << 27)     /**< Shifted mode DEFAULT for VIT_STAT           */

/* Bit fields for VIT FRAMEOUT */
#define _VIT_FRAMEOUT_RESETVALUE             0x00000000UL                               /**< Default value for VIT_FRAMEOUT              */
#define _VIT_FRAMEOUT_MASK                   0x0000FFFFUL                               /**< Mask for VIT_FRAMEOUT                       */
#define _VIT_FRAMEOUT_LENGTH_SHIFT           0                                          /**< Shift value for VIT_LENGTH                  */
#define _VIT_FRAMEOUT_LENGTH_MASK            0xFFFFUL                                   /**< Bit mask for VIT_LENGTH                     */
#define _VIT_FRAMEOUT_LENGTH_DEFAULT         0x00000000UL                               /**< Mode DEFAULT for VIT_FRAMEOUT               */
#define VIT_FRAMEOUT_LENGTH_DEFAULT          (_VIT_FRAMEOUT_LENGTH_DEFAULT << 0)        /**< Shifted mode DEFAULT for VIT_FRAMEOUT       */

/* Bit fields for VIT SYNDROME */
#define _VIT_SYNDROME_RESETVALUE             0x00000000UL                               /**< Default value for VIT_SYNDROME              */
#define _VIT_SYNDROME_MASK                   0xFFFFFFFFUL                               /**< Mask for VIT_SYNDROME                       */
#define _VIT_SYNDROME_ERR_SHIFT              0                                          /**< Shift value for VIT_ERR                     */
#define _VIT_SYNDROME_ERR_MASK               0xFFFFUL                                   /**< Bit mask for VIT_ERR                        */
#define _VIT_SYNDROME_ERR_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for VIT_SYNDROME               */
#define VIT_SYNDROME_ERR_DEFAULT             (_VIT_SYNDROME_ERR_DEFAULT << 0)           /**< Shifted mode DEFAULT for VIT_SYNDROME       */
#define _VIT_SYNDROME_CNT_SHIFT              16                                         /**< Shift value for VIT_CNT                     */
#define _VIT_SYNDROME_CNT_MASK               0xFFFF0000UL                               /**< Bit mask for VIT_CNT                        */
#define _VIT_SYNDROME_CNT_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for VIT_SYNDROME               */
#define VIT_SYNDROME_CNT_DEFAULT             (_VIT_SYNDROME_CNT_DEFAULT << 16)          /**< Shifted mode DEFAULT for VIT_SYNDROME       */

/* Bit fields for VIT IF */
#define _VIT_IF_RESETVALUE                   0x00000000UL                               /**< Default value for VIT_IF                    */
#define _VIT_IF_MASK                         0x00000001UL                               /**< Mask for VIT_IF                             */
#define VIT_IF_DONE                          (0x1UL << 0)                               /**< New BitField                                */
#define _VIT_IF_DONE_SHIFT                   0                                          /**< Shift value for VIT_DONE                    */
#define _VIT_IF_DONE_MASK                    0x1UL                                      /**< Bit mask for VIT_DONE                       */
#define _VIT_IF_DONE_DEFAULT                 0x00000000UL                               /**< Mode DEFAULT for VIT_IF                     */
#define VIT_IF_DONE_DEFAULT                  (_VIT_IF_DONE_DEFAULT << 0)                /**< Shifted mode DEFAULT for VIT_IF             */

/* Bit fields for VIT IEN */
#define _VIT_IEN_RESETVALUE                  0x00000000UL                               /**< Default value for VIT_IEN                   */
#define _VIT_IEN_MASK                        0x00000001UL                               /**< Mask for VIT_IEN                            */
#define VIT_IEN_DONE                         (0x1UL << 0)                               /**< New BitField                                */
#define _VIT_IEN_DONE_SHIFT                  0                                          /**< Shift value for VIT_DONE                    */
#define _VIT_IEN_DONE_MASK                   0x1UL                                      /**< Bit mask for VIT_DONE                       */
#define _VIT_IEN_DONE_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for VIT_IEN                    */
#define VIT_IEN_DONE_DEFAULT                 (_VIT_IEN_DONE_DEFAULT << 0)               /**< Shifted mode DEFAULT for VIT_IEN            */

/** @} End of group EFR32FG25_VIT_BitFields */
/** @} End of group EFR32FG25_VIT */
/** @} End of group Parts */

#endif /* EFR32FG25_VIT_H */
