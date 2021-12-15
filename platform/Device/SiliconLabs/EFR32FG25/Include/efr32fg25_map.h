/**************************************************************************//**
 * @file
 * @brief EFR32FG25 MAP register and bit field definitions
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
#ifndef EFR32FG25_MAP_H
#define EFR32FG25_MAP_H
#define MAP_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_MAP MAP
 * @{
 * @brief EFR32FG25 MAP Register Declaration.
 *****************************************************************************/

/** MAP Register Declaration. */
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
  uint32_t       RESERVED5[895U];               /**< Reserved for future use                            */
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
  uint32_t       RESERVED11[895U];              /**< Reserved for future use                            */
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
  uint32_t       RESERVED17[895U];              /**< Reserved for future use                            */
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
} MAP_TypeDef;
/** @} End of group EFR32FG25_MAP */

/**************************************************************************//**
 * @addtogroup EFR32FG25_MAP
 * @{
 * @defgroup EFR32FG25_MAP_BitFields MAP Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for MAP IPVERSION */
#define _MAP_IPVERSION_RESETVALUE           0x00000001UL                                /**< Default value for MAP_IPVERSION             */
#define _MAP_IPVERSION_MASK                 0xFFFFFFFFUL                                /**< Mask for MAP_IPVERSION                      */
#define _MAP_IPVERSION_IPVERSION_SHIFT      0                                           /**< Shift value for MAP_IPVERSION               */
#define _MAP_IPVERSION_IPVERSION_MASK       0xFFFFFFFFUL                                /**< Bit mask for MAP_IPVERSION                  */
#define _MAP_IPVERSION_IPVERSION_DEFAULT    0x00000001UL                                /**< Mode DEFAULT for MAP_IPVERSION              */
#define MAP_IPVERSION_IPVERSION_DEFAULT     (_MAP_IPVERSION_IPVERSION_DEFAULT << 0)     /**< Shifted mode DEFAULT for MAP_IPVERSION      */

/* Bit fields for MAP EN */
#define _MAP_EN_RESETVALUE                  0x00000000UL                                /**< Default value for MAP_EN                    */
#define _MAP_EN_MASK                        0x00000003UL                                /**< Mask for MAP_EN                             */
#define MAP_EN_EN                           (0x1UL << 0)                                /**< Module Enable                               */
#define _MAP_EN_EN_SHIFT                    0                                           /**< Shift value for MAP_EN                      */
#define _MAP_EN_EN_MASK                     0x1UL                                       /**< Bit mask for MAP_EN                         */
#define _MAP_EN_EN_DEFAULT                  0x00000000UL                                /**< Mode DEFAULT for MAP_EN                     */
#define MAP_EN_EN_DEFAULT                   (_MAP_EN_EN_DEFAULT << 0)                   /**< Shifted mode DEFAULT for MAP_EN             */
#define MAP_EN_DISABLING                    (0x1UL << 1)                                /**< Disablement Busy Status                     */
#define _MAP_EN_DISABLING_SHIFT             1                                           /**< Shift value for MAP_DISABLING               */
#define _MAP_EN_DISABLING_MASK              0x2UL                                       /**< Bit mask for MAP_DISABLING                  */
#define _MAP_EN_DISABLING_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for MAP_EN                     */
#define MAP_EN_DISABLING_DEFAULT            (_MAP_EN_DISABLING_DEFAULT << 1)            /**< Shifted mode DEFAULT for MAP_EN             */

/* Bit fields for MAP SWRST */
#define _MAP_SWRST_RESETVALUE               0x00000000UL                                /**< Default value for MAP_SWRST                 */
#define _MAP_SWRST_MASK                     0x00000003UL                                /**< Mask for MAP_SWRST                          */
#define MAP_SWRST_SWRST                     (0x1UL << 0)                                /**< Software Reset Command                      */
#define _MAP_SWRST_SWRST_SHIFT              0                                           /**< Shift value for MAP_SWRST                   */
#define _MAP_SWRST_SWRST_MASK               0x1UL                                       /**< Bit mask for MAP_SWRST                      */
#define _MAP_SWRST_SWRST_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for MAP_SWRST                  */
#define MAP_SWRST_SWRST_DEFAULT             (_MAP_SWRST_SWRST_DEFAULT << 0)             /**< Shifted mode DEFAULT for MAP_SWRST          */
#define MAP_SWRST_RESETTING                 (0x1UL << 1)                                /**< Software Reset Busy Status                  */
#define _MAP_SWRST_RESETTING_SHIFT          1                                           /**< Shift value for MAP_RESETTING               */
#define _MAP_SWRST_RESETTING_MASK           0x2UL                                       /**< Bit mask for MAP_RESETTING                  */
#define _MAP_SWRST_RESETTING_DEFAULT        0x00000000UL                                /**< Mode DEFAULT for MAP_SWRST                  */
#define MAP_SWRST_RESETTING_DEFAULT         (_MAP_SWRST_RESETTING_DEFAULT << 1)         /**< Shifted mode DEFAULT for MAP_SWRST          */

/* Bit fields for MAP CONNECT */
#define _MAP_CONNECT_RESETVALUE             0x00000000UL                                /**< Default value for MAP_CONNECT               */
#define _MAP_CONNECT_MASK                   0x00000101UL                                /**< Mask for MAP_CONNECT                        */
#define MAP_CONNECT_IN                      (0x1UL << 0)                                /**< Input FIFO connect                          */
#define _MAP_CONNECT_IN_SHIFT               0                                           /**< Shift value for MAP_IN                      */
#define _MAP_CONNECT_IN_MASK                0x1UL                                       /**< Bit mask for MAP_IN                         */
#define _MAP_CONNECT_IN_DEFAULT             0x00000000UL                                /**< Mode DEFAULT for MAP_CONNECT                */
#define MAP_CONNECT_IN_DEFAULT              (_MAP_CONNECT_IN_DEFAULT << 0)              /**< Shifted mode DEFAULT for MAP_CONNECT        */
#define MAP_CONNECT_OUT                     (0x1UL << 8)                                /**< Output FIFO connect                         */
#define _MAP_CONNECT_OUT_SHIFT              8                                           /**< Shift value for MAP_OUT                     */
#define _MAP_CONNECT_OUT_MASK               0x100UL                                     /**< Bit mask for MAP_OUT                        */
#define _MAP_CONNECT_OUT_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for MAP_CONNECT                */
#define MAP_CONNECT_OUT_DEFAULT             (_MAP_CONNECT_OUT_DEFAULT << 8)             /**< Shifted mode DEFAULT for MAP_CONNECT        */

/* Bit fields for MAP DISCLK */
#define _MAP_DISCLK_RESETVALUE              0x00000002UL                                /**< Default value for MAP_DISCLK                */
#define _MAP_DISCLK_MASK                    0x00000003UL                                /**< Mask for MAP_DISCLK                         */
#define _MAP_DISCLK_DISCLK_SHIFT            0                                           /**< Shift value for MAP_DISCLK                  */
#define _MAP_DISCLK_DISCLK_MASK             0x3UL                                       /**< Bit mask for MAP_DISCLK                     */
#define _MAP_DISCLK_DISCLK_DEFAULT          0x00000002UL                                /**< Mode DEFAULT for MAP_DISCLK                 */
#define _MAP_DISCLK_DISCLK_NONE             0x00000000UL                                /**< Mode NONE for MAP_DISCLK                    */
#define _MAP_DISCLK_DISCLK_ALL              0x00000001UL                                /**< Mode ALL for MAP_DISCLK                     */
#define _MAP_DISCLK_DISCLK_AUTO             0x00000002UL                                /**< Mode AUTO for MAP_DISCLK                    */
#define MAP_DISCLK_DISCLK_DEFAULT           (_MAP_DISCLK_DISCLK_DEFAULT << 0)           /**< Shifted mode DEFAULT for MAP_DISCLK         */
#define MAP_DISCLK_DISCLK_NONE              (_MAP_DISCLK_DISCLK_NONE << 0)              /**< Shifted mode NONE for MAP_DISCLK            */
#define MAP_DISCLK_DISCLK_ALL               (_MAP_DISCLK_DISCLK_ALL << 0)               /**< Shifted mode ALL for MAP_DISCLK             */
#define MAP_DISCLK_DISCLK_AUTO              (_MAP_DISCLK_DISCLK_AUTO << 0)              /**< Shifted mode AUTO for MAP_DISCLK            */

/* Bit fields for MAP FIFOIN */
#define _MAP_FIFOIN_RESETVALUE              0x00000000UL                                /**< Default value for MAP_FIFOIN                */
#define _MAP_FIFOIN_MASK                    0x1FFF3F0FUL                                /**< Mask for MAP_FIFOIN                         */
#define _MAP_FIFOIN_FID_SHIFT               0                                           /**< Shift value for MAP_FID                     */
#define _MAP_FIFOIN_FID_MASK                0xFUL                                       /**< Bit mask for MAP_FID                        */
#define _MAP_FIFOIN_FID_DEFAULT             0x00000000UL                                /**< Mode DEFAULT for MAP_FIFOIN                 */
#define MAP_FIFOIN_FID_DEFAULT              (_MAP_FIFOIN_FID_DEFAULT << 0)              /**< Shifted mode DEFAULT for MAP_FIFOIN         */
#define _MAP_FIFOIN_CID_SHIFT               8                                           /**< Shift value for MAP_CID                     */
#define _MAP_FIFOIN_CID_MASK                0x3F00UL                                    /**< Bit mask for MAP_CID                        */
#define _MAP_FIFOIN_CID_DEFAULT             0x00000000UL                                /**< Mode DEFAULT for MAP_FIFOIN                 */
#define MAP_FIFOIN_CID_DEFAULT              (_MAP_FIFOIN_CID_DEFAULT << 8)              /**< Shifted mode DEFAULT for MAP_FIFOIN         */
#define _MAP_FIFOIN_REM_SHIFT               16                                          /**< Shift value for MAP_REM                     */
#define _MAP_FIFOIN_REM_MASK                0xFF0000UL                                  /**< Bit mask for MAP_REM                        */
#define _MAP_FIFOIN_REM_DEFAULT             0x00000000UL                                /**< Mode DEFAULT for MAP_FIFOIN                 */
#define MAP_FIFOIN_REM_DEFAULT              (_MAP_FIFOIN_REM_DEFAULT << 16)             /**< Shifted mode DEFAULT for MAP_FIFOIN         */
#define _MAP_FIFOIN_ALARM_SHIFT             24                                          /**< Shift value for MAP_ALARM                   */
#define _MAP_FIFOIN_ALARM_MASK              0x1F000000UL                                /**< Bit mask for MAP_ALARM                      */
#define _MAP_FIFOIN_ALARM_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for MAP_FIFOIN                 */
#define MAP_FIFOIN_ALARM_DEFAULT            (_MAP_FIFOIN_ALARM_DEFAULT << 24)           /**< Shifted mode DEFAULT for MAP_FIFOIN         */

/* Bit fields for MAP FIFOOUT */
#define _MAP_FIFOOUT_RESETVALUE             0x00000000UL                                /**< Default value for MAP_FIFOOUT               */
#define _MAP_FIFOOUT_MASK                   0x1FFF0000UL                                /**< Mask for MAP_FIFOOUT                        */
#define _MAP_FIFOOUT_CNT_SHIFT              16                                          /**< Shift value for MAP_CNT                     */
#define _MAP_FIFOOUT_CNT_MASK               0xFF0000UL                                  /**< Bit mask for MAP_CNT                        */
#define _MAP_FIFOOUT_CNT_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for MAP_FIFOOUT                */
#define MAP_FIFOOUT_CNT_DEFAULT             (_MAP_FIFOOUT_CNT_DEFAULT << 16)            /**< Shifted mode DEFAULT for MAP_FIFOOUT        */
#define _MAP_FIFOOUT_ALARM_SHIFT            24                                          /**< Shift value for MAP_ALARM                   */
#define _MAP_FIFOOUT_ALARM_MASK             0x1F000000UL                                /**< Bit mask for MAP_ALARM                      */
#define _MAP_FIFOOUT_ALARM_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for MAP_FIFOOUT                */
#define MAP_FIFOOUT_ALARM_DEFAULT           (_MAP_FIFOOUT_ALARM_DEFAULT << 24)          /**< Shifted mode DEFAULT for MAP_FIFOOUT        */

/* Bit fields for MAP FMTIN */
#define _MAP_FMTIN_RESETVALUE               0x00000000UL                                /**< Default value for MAP_FMTIN                 */
#define _MAP_FMTIN_MASK                     0x0003001FUL                                /**< Mask for MAP_FMTIN                          */
#define _MAP_FMTIN_ELEMSIZE_SHIFT           0                                           /**< Shift value for MAP_ELEMSIZE                */
#define _MAP_FMTIN_ELEMSIZE_MASK            0x1FUL                                      /**< Bit mask for MAP_ELEMSIZE                   */
#define _MAP_FMTIN_ELEMSIZE_DEFAULT         0x00000000UL                                /**< Mode DEFAULT for MAP_FMTIN                  */
#define MAP_FMTIN_ELEMSIZE_DEFAULT          (_MAP_FMTIN_ELEMSIZE_DEFAULT << 0)          /**< Shifted mode DEFAULT for MAP_FMTIN          */
#define _MAP_FMTIN_ELEMALIGN_SHIFT          16                                          /**< Shift value for MAP_ELEMALIGN               */
#define _MAP_FMTIN_ELEMALIGN_MASK           0x30000UL                                   /**< Bit mask for MAP_ELEMALIGN                  */
#define _MAP_FMTIN_ELEMALIGN_DEFAULT        0x00000000UL                                /**< Mode DEFAULT for MAP_FMTIN                  */
#define _MAP_FMTIN_ELEMALIGN_WORD           0x00000000UL                                /**< Mode WORD for MAP_FMTIN                     */
#define _MAP_FMTIN_ELEMALIGN_HALFWORD       0x00000001UL                                /**< Mode HALFWORD for MAP_FMTIN                 */
#define _MAP_FMTIN_ELEMALIGN_BYTE           0x00000002UL                                /**< Mode BYTE for MAP_FMTIN                     */
#define MAP_FMTIN_ELEMALIGN_DEFAULT         (_MAP_FMTIN_ELEMALIGN_DEFAULT << 16)        /**< Shifted mode DEFAULT for MAP_FMTIN          */
#define MAP_FMTIN_ELEMALIGN_WORD            (_MAP_FMTIN_ELEMALIGN_WORD << 16)           /**< Shifted mode WORD for MAP_FMTIN             */
#define MAP_FMTIN_ELEMALIGN_HALFWORD        (_MAP_FMTIN_ELEMALIGN_HALFWORD << 16)       /**< Shifted mode HALFWORD for MAP_FMTIN         */
#define MAP_FMTIN_ELEMALIGN_BYTE            (_MAP_FMTIN_ELEMALIGN_BYTE << 16)           /**< Shifted mode BYTE for MAP_FMTIN             */

/* Bit fields for MAP FMTOUT */
#define _MAP_FMTOUT_RESETVALUE              0x00000000UL                                /**< Default value for MAP_FMTOUT                */
#define _MAP_FMTOUT_MASK                    0x0003001FUL                                /**< Mask for MAP_FMTOUT                         */
#define _MAP_FMTOUT_ELEMSIZE_SHIFT          0                                           /**< Shift value for MAP_ELEMSIZE                */
#define _MAP_FMTOUT_ELEMSIZE_MASK           0x1FUL                                      /**< Bit mask for MAP_ELEMSIZE                   */
#define _MAP_FMTOUT_ELEMSIZE_DEFAULT        0x00000000UL                                /**< Mode DEFAULT for MAP_FMTOUT                 */
#define MAP_FMTOUT_ELEMSIZE_DEFAULT         (_MAP_FMTOUT_ELEMSIZE_DEFAULT << 0)         /**< Shifted mode DEFAULT for MAP_FMTOUT         */
#define _MAP_FMTOUT_ELEMALIGN_SHIFT         16                                          /**< Shift value for MAP_ELEMALIGN               */
#define _MAP_FMTOUT_ELEMALIGN_MASK          0x30000UL                                   /**< Bit mask for MAP_ELEMALIGN                  */
#define _MAP_FMTOUT_ELEMALIGN_DEFAULT       0x00000000UL                                /**< Mode DEFAULT for MAP_FMTOUT                 */
#define _MAP_FMTOUT_ELEMALIGN_WORD          0x00000000UL                                /**< Mode WORD for MAP_FMTOUT                    */
#define _MAP_FMTOUT_ELEMALIGN_HALFWORD      0x00000001UL                                /**< Mode HALFWORD for MAP_FMTOUT                */
#define _MAP_FMTOUT_ELEMALIGN_BYTE          0x00000002UL                                /**< Mode BYTE for MAP_FMTOUT                    */
#define MAP_FMTOUT_ELEMALIGN_DEFAULT        (_MAP_FMTOUT_ELEMALIGN_DEFAULT << 16)       /**< Shifted mode DEFAULT for MAP_FMTOUT         */
#define MAP_FMTOUT_ELEMALIGN_WORD           (_MAP_FMTOUT_ELEMALIGN_WORD << 16)          /**< Shifted mode WORD for MAP_FMTOUT            */
#define MAP_FMTOUT_ELEMALIGN_HALFWORD       (_MAP_FMTOUT_ELEMALIGN_HALFWORD << 16)      /**< Shifted mode HALFWORD for MAP_FMTOUT        */
#define MAP_FMTOUT_ELEMALIGN_BYTE           (_MAP_FMTOUT_ELEMALIGN_BYTE << 16)          /**< Shifted mode BYTE for MAP_FMTOUT            */

/* Bit fields for MAP CTRL */
#define _MAP_CTRL_RESETVALUE                0x00000000UL                                /**< Default value for MAP_CTRL                  */
#define _MAP_CTRL_MASK                      0x000003FFUL                                /**< Mask for MAP_CTRL                           */
#define _MAP_CTRL_MULTSYMB_SHIFT            0                                           /**< Shift value for MAP_MULTSYMB                */
#define _MAP_CTRL_MULTSYMB_MASK             0x3UL                                       /**< Bit mask for MAP_MULTSYMB                   */
#define _MAP_CTRL_MULTSYMB_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for MAP_CTRL                   */
#define _MAP_CTRL_MULTSYMB_ONE              0x00000000UL                                /**< Mode ONE for MAP_CTRL                       */
#define _MAP_CTRL_MULTSYMB_TWO              0x00000001UL                                /**< Mode TWO for MAP_CTRL                       */
#define _MAP_CTRL_MULTSYMB_FOUR             0x00000002UL                                /**< Mode FOUR for MAP_CTRL                      */
#define MAP_CTRL_MULTSYMB_DEFAULT           (_MAP_CTRL_MULTSYMB_DEFAULT << 0)           /**< Shifted mode DEFAULT for MAP_CTRL           */
#define MAP_CTRL_MULTSYMB_ONE               (_MAP_CTRL_MULTSYMB_ONE << 0)               /**< Shifted mode ONE for MAP_CTRL               */
#define MAP_CTRL_MULTSYMB_TWO               (_MAP_CTRL_MULTSYMB_TWO << 0)               /**< Shifted mode TWO for MAP_CTRL               */
#define MAP_CTRL_MULTSYMB_FOUR              (_MAP_CTRL_MULTSYMB_FOUR << 0)              /**< Shifted mode FOUR for MAP_CTRL              */
#define _MAP_CTRL_SPREAD_SHIFT              2                                           /**< Shift value for MAP_SPREAD                  */
#define _MAP_CTRL_SPREAD_MASK               0xCUL                                       /**< Bit mask for MAP_SPREAD                     */
#define _MAP_CTRL_SPREAD_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for MAP_CTRL                   */
#define _MAP_CTRL_SPREAD_OFF                0x00000000UL                                /**< Mode OFF for MAP_CTRL                       */
#define _MAP_CTRL_SPREAD_FACTOR2            0x00000001UL                                /**< Mode FACTOR2 for MAP_CTRL                   */
#define _MAP_CTRL_SPREAD_FACTOR4            0x00000002UL                                /**< Mode FACTOR4 for MAP_CTRL                   */
#define _MAP_CTRL_SPREAD_FACTOR8            0x00000003UL                                /**< Mode FACTOR8 for MAP_CTRL                   */
#define MAP_CTRL_SPREAD_DEFAULT             (_MAP_CTRL_SPREAD_DEFAULT << 2)             /**< Shifted mode DEFAULT for MAP_CTRL           */
#define MAP_CTRL_SPREAD_OFF                 (_MAP_CTRL_SPREAD_OFF << 2)                 /**< Shifted mode OFF for MAP_CTRL               */
#define MAP_CTRL_SPREAD_FACTOR2             (_MAP_CTRL_SPREAD_FACTOR2 << 2)             /**< Shifted mode FACTOR2 for MAP_CTRL           */
#define MAP_CTRL_SPREAD_FACTOR4             (_MAP_CTRL_SPREAD_FACTOR4 << 2)             /**< Shifted mode FACTOR4 for MAP_CTRL           */
#define MAP_CTRL_SPREAD_FACTOR8             (_MAP_CTRL_SPREAD_FACTOR8 << 2)             /**< Shifted mode FACTOR8 for MAP_CTRL           */
#define _MAP_CTRL_BYTESWAP0_SHIFT           4                                           /**< Shift value for MAP_BYTESWAP0               */
#define _MAP_CTRL_BYTESWAP0_MASK            0x30UL                                      /**< Bit mask for MAP_BYTESWAP0                  */
#define _MAP_CTRL_BYTESWAP0_DEFAULT         0x00000000UL                                /**< Mode DEFAULT for MAP_CTRL                   */
#define _MAP_CTRL_BYTESWAP0_DISABLED        0x00000000UL                                /**< Mode DISABLED for MAP_CTRL                  */
#define _MAP_CTRL_BYTESWAP0_HALFWORD        0x00000001UL                                /**< Mode HALFWORD for MAP_CTRL                  */
#define _MAP_CTRL_BYTESWAP0_WORD            0x00000002UL                                /**< Mode WORD for MAP_CTRL                      */
#define MAP_CTRL_BYTESWAP0_DEFAULT          (_MAP_CTRL_BYTESWAP0_DEFAULT << 4)          /**< Shifted mode DEFAULT for MAP_CTRL           */
#define MAP_CTRL_BYTESWAP0_DISABLED         (_MAP_CTRL_BYTESWAP0_DISABLED << 4)         /**< Shifted mode DISABLED for MAP_CTRL          */
#define MAP_CTRL_BYTESWAP0_HALFWORD         (_MAP_CTRL_BYTESWAP0_HALFWORD << 4)         /**< Shifted mode HALFWORD for MAP_CTRL          */
#define MAP_CTRL_BYTESWAP0_WORD             (_MAP_CTRL_BYTESWAP0_WORD << 4)             /**< Shifted mode WORD for MAP_CTRL              */
#define MAP_CTRL_BITSWAP0                   (0x1UL << 6)                                /**< New BitField                                */
#define _MAP_CTRL_BITSWAP0_SHIFT            6                                           /**< Shift value for MAP_BITSWAP0                */
#define _MAP_CTRL_BITSWAP0_MASK             0x40UL                                      /**< Bit mask for MAP_BITSWAP0                   */
#define _MAP_CTRL_BITSWAP0_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for MAP_CTRL                   */
#define _MAP_CTRL_BITSWAP0_DISABLED         0x00000000UL                                /**< Mode DISABLED for MAP_CTRL                  */
#define _MAP_CTRL_BITSWAP0_ENABLED          0x00000001UL                                /**< Mode ENABLED for MAP_CTRL                   */
#define MAP_CTRL_BITSWAP0_DEFAULT           (_MAP_CTRL_BITSWAP0_DEFAULT << 6)           /**< Shifted mode DEFAULT for MAP_CTRL           */
#define MAP_CTRL_BITSWAP0_DISABLED          (_MAP_CTRL_BITSWAP0_DISABLED << 6)          /**< Shifted mode DISABLED for MAP_CTRL          */
#define MAP_CTRL_BITSWAP0_ENABLED           (_MAP_CTRL_BITSWAP0_ENABLED << 6)           /**< Shifted mode ENABLED for MAP_CTRL           */
#define _MAP_CTRL_BYTESWAP1_SHIFT           7                                           /**< Shift value for MAP_BYTESWAP1               */
#define _MAP_CTRL_BYTESWAP1_MASK            0x180UL                                     /**< Bit mask for MAP_BYTESWAP1                  */
#define _MAP_CTRL_BYTESWAP1_DEFAULT         0x00000000UL                                /**< Mode DEFAULT for MAP_CTRL                   */
#define _MAP_CTRL_BYTESWAP1_DISABLED        0x00000000UL                                /**< Mode DISABLED for MAP_CTRL                  */
#define _MAP_CTRL_BYTESWAP1_HALFWORD        0x00000001UL                                /**< Mode HALFWORD for MAP_CTRL                  */
#define _MAP_CTRL_BYTESWAP1_WORD            0x00000002UL                                /**< Mode WORD for MAP_CTRL                      */
#define MAP_CTRL_BYTESWAP1_DEFAULT          (_MAP_CTRL_BYTESWAP1_DEFAULT << 7)          /**< Shifted mode DEFAULT for MAP_CTRL           */
#define MAP_CTRL_BYTESWAP1_DISABLED         (_MAP_CTRL_BYTESWAP1_DISABLED << 7)         /**< Shifted mode DISABLED for MAP_CTRL          */
#define MAP_CTRL_BYTESWAP1_HALFWORD         (_MAP_CTRL_BYTESWAP1_HALFWORD << 7)         /**< Shifted mode HALFWORD for MAP_CTRL          */
#define MAP_CTRL_BYTESWAP1_WORD             (_MAP_CTRL_BYTESWAP1_WORD << 7)             /**< Shifted mode WORD for MAP_CTRL              */
#define MAP_CTRL_BITSWAP1                   (0x1UL << 9)                                /**< New BitField                                */
#define _MAP_CTRL_BITSWAP1_SHIFT            9                                           /**< Shift value for MAP_BITSWAP1                */
#define _MAP_CTRL_BITSWAP1_MASK             0x200UL                                     /**< Bit mask for MAP_BITSWAP1                   */
#define _MAP_CTRL_BITSWAP1_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for MAP_CTRL                   */
#define _MAP_CTRL_BITSWAP1_DISABLED         0x00000000UL                                /**< Mode DISABLED for MAP_CTRL                  */
#define _MAP_CTRL_BITSWAP1_ENABLED          0x00000001UL                                /**< Mode ENABLED for MAP_CTRL                   */
#define MAP_CTRL_BITSWAP1_DEFAULT           (_MAP_CTRL_BITSWAP1_DEFAULT << 9)           /**< Shifted mode DEFAULT for MAP_CTRL           */
#define MAP_CTRL_BITSWAP1_DISABLED          (_MAP_CTRL_BITSWAP1_DISABLED << 9)          /**< Shifted mode DISABLED for MAP_CTRL          */
#define MAP_CTRL_BITSWAP1_ENABLED           (_MAP_CTRL_BITSWAP1_ENABLED << 9)           /**< Shifted mode ENABLED for MAP_CTRL           */

/** @} End of group EFR32FG25_MAP_BitFields */
/** @} End of group EFR32FG25_MAP */
/** @} End of group Parts */

#endif /* EFR32FG25_MAP_H */
