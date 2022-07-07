/**************************************************************************//**
 * @file
 * @brief EFR32FG25 PRBS register and bit field definitions
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
#ifndef EFR32FG25_PRBS_H
#define EFR32FG25_PRBS_H
#define PRBS_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_PRBS PRBS
 * @{
 * @brief EFR32FG25 PRBS Register Declaration.
 *****************************************************************************/

/** PRBS Register Declaration. */
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
  uint32_t       RESERVED4[1U];                 /**< Reserved for future use                            */
  uint32_t       RESERVED5[79U];                /**< Reserved for future use                            */
  __IOM uint32_t CTRL1;                         /**< New Register                                       */
  __IOM uint32_t INIT;                          /**< New Register                                       */
  __IOM uint32_t CTRL2;                         /**< New Register                                       */
  uint32_t       RESERVED6[5U];                 /**< Reserved for future use                            */
  __IM uint32_t  STAT;                          /**< New Register                                       */
  __IM uint32_t  SEQ;                           /**< New Register                                       */
  __IOM uint32_t POLY;                          /**< New Register                                       */
  __IOM uint32_t FEED;                          /**< New Register                                       */
  uint32_t       RESERVED7[884U];               /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_SET;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_SET;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_SET;                   /**< New Register                                       */
  __IOM uint32_t DISCLK_SET;                    /**< Disable Clocks                                     */
  uint32_t       RESERVED8[3U];                 /**< Reserved for future use                            */
  __IOM uint32_t FIFOIN_SET;                    /**< New Register                                       */
  uint32_t       RESERVED9[7U];                 /**< Reserved for future use                            */
  __IM uint32_t  FIFOOUT_SET;                   /**< New Register                                       */
  uint32_t       RESERVED10[23U];               /**< Reserved for future use                            */
  __IOM uint32_t FMTIN_SET;                     /**< New Register                                       */
  uint32_t       RESERVED11[7U];                /**< Reserved for future use                            */
  uint32_t       RESERVED12[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED13[79U];               /**< Reserved for future use                            */
  __IOM uint32_t CTRL1_SET;                     /**< New Register                                       */
  __IOM uint32_t INIT_SET;                      /**< New Register                                       */
  __IOM uint32_t CTRL2_SET;                     /**< New Register                                       */
  uint32_t       RESERVED14[5U];                /**< Reserved for future use                            */
  __IM uint32_t  STAT_SET;                      /**< New Register                                       */
  __IM uint32_t  SEQ_SET;                       /**< New Register                                       */
  __IOM uint32_t POLY_SET;                      /**< New Register                                       */
  __IOM uint32_t FEED_SET;                      /**< New Register                                       */
  uint32_t       RESERVED15[884U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_CLR;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_CLR;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_CLR;                   /**< New Register                                       */
  __IOM uint32_t DISCLK_CLR;                    /**< Disable Clocks                                     */
  uint32_t       RESERVED16[3U];                /**< Reserved for future use                            */
  __IOM uint32_t FIFOIN_CLR;                    /**< New Register                                       */
  uint32_t       RESERVED17[7U];                /**< Reserved for future use                            */
  __IM uint32_t  FIFOOUT_CLR;                   /**< New Register                                       */
  uint32_t       RESERVED18[23U];               /**< Reserved for future use                            */
  __IOM uint32_t FMTIN_CLR;                     /**< New Register                                       */
  uint32_t       RESERVED19[7U];                /**< Reserved for future use                            */
  uint32_t       RESERVED20[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED21[79U];               /**< Reserved for future use                            */
  __IOM uint32_t CTRL1_CLR;                     /**< New Register                                       */
  __IOM uint32_t INIT_CLR;                      /**< New Register                                       */
  __IOM uint32_t CTRL2_CLR;                     /**< New Register                                       */
  uint32_t       RESERVED22[5U];                /**< Reserved for future use                            */
  __IM uint32_t  STAT_CLR;                      /**< New Register                                       */
  __IM uint32_t  SEQ_CLR;                       /**< New Register                                       */
  __IOM uint32_t POLY_CLR;                      /**< New Register                                       */
  __IOM uint32_t FEED_CLR;                      /**< New Register                                       */
  uint32_t       RESERVED23[884U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_TGL;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_TGL;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_TGL;                   /**< New Register                                       */
  __IOM uint32_t DISCLK_TGL;                    /**< Disable Clocks                                     */
  uint32_t       RESERVED24[3U];                /**< Reserved for future use                            */
  __IOM uint32_t FIFOIN_TGL;                    /**< New Register                                       */
  uint32_t       RESERVED25[7U];                /**< Reserved for future use                            */
  __IM uint32_t  FIFOOUT_TGL;                   /**< New Register                                       */
  uint32_t       RESERVED26[23U];               /**< Reserved for future use                            */
  __IOM uint32_t FMTIN_TGL;                     /**< New Register                                       */
  uint32_t       RESERVED27[7U];                /**< Reserved for future use                            */
  uint32_t       RESERVED28[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED29[79U];               /**< Reserved for future use                            */
  __IOM uint32_t CTRL1_TGL;                     /**< New Register                                       */
  __IOM uint32_t INIT_TGL;                      /**< New Register                                       */
  __IOM uint32_t CTRL2_TGL;                     /**< New Register                                       */
  uint32_t       RESERVED30[5U];                /**< Reserved for future use                            */
  __IM uint32_t  STAT_TGL;                      /**< New Register                                       */
  __IM uint32_t  SEQ_TGL;                       /**< New Register                                       */
  __IOM uint32_t POLY_TGL;                      /**< New Register                                       */
  __IOM uint32_t FEED_TGL;                      /**< New Register                                       */
} PRBS_TypeDef;
/** @} End of group EFR32FG25_PRBS */

/**************************************************************************//**
 * @addtogroup EFR32FG25_PRBS
 * @{
 * @defgroup EFR32FG25_PRBS_BitFields PRBS Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for PRBS IPVERSION */
#define _PRBS_IPVERSION_RESETVALUE           0x00000001UL                               /**< Default value for PRBS_IPVERSION            */
#define _PRBS_IPVERSION_MASK                 0xFFFFFFFFUL                               /**< Mask for PRBS_IPVERSION                     */
#define _PRBS_IPVERSION_IPVERSION_SHIFT      0                                          /**< Shift value for PRBS_IPVERSION              */
#define _PRBS_IPVERSION_IPVERSION_MASK       0xFFFFFFFFUL                               /**< Bit mask for PRBS_IPVERSION                 */
#define _PRBS_IPVERSION_IPVERSION_DEFAULT    0x00000001UL                               /**< Mode DEFAULT for PRBS_IPVERSION             */
#define PRBS_IPVERSION_IPVERSION_DEFAULT     (_PRBS_IPVERSION_IPVERSION_DEFAULT << 0)   /**< Shifted mode DEFAULT for PRBS_IPVERSION     */

/* Bit fields for PRBS EN */
#define _PRBS_EN_RESETVALUE                  0x00000000UL                               /**< Default value for PRBS_EN                   */
#define _PRBS_EN_MASK                        0x00000003UL                               /**< Mask for PRBS_EN                            */
#define PRBS_EN_EN                           (0x1UL << 0)                               /**< Module Enable                               */
#define _PRBS_EN_EN_SHIFT                    0                                          /**< Shift value for PRBS_EN                     */
#define _PRBS_EN_EN_MASK                     0x1UL                                      /**< Bit mask for PRBS_EN                        */
#define _PRBS_EN_EN_DEFAULT                  0x00000000UL                               /**< Mode DEFAULT for PRBS_EN                    */
#define PRBS_EN_EN_DEFAULT                   (_PRBS_EN_EN_DEFAULT << 0)                 /**< Shifted mode DEFAULT for PRBS_EN            */
#define PRBS_EN_DISABLING                    (0x1UL << 1)                               /**< Disablement Busy Status                     */
#define _PRBS_EN_DISABLING_SHIFT             1                                          /**< Shift value for PRBS_DISABLING              */
#define _PRBS_EN_DISABLING_MASK              0x2UL                                      /**< Bit mask for PRBS_DISABLING                 */
#define _PRBS_EN_DISABLING_DEFAULT           0x00000000UL                               /**< Mode DEFAULT for PRBS_EN                    */
#define PRBS_EN_DISABLING_DEFAULT            (_PRBS_EN_DISABLING_DEFAULT << 1)          /**< Shifted mode DEFAULT for PRBS_EN            */

/* Bit fields for PRBS SWRST */
#define _PRBS_SWRST_RESETVALUE               0x00000000UL                               /**< Default value for PRBS_SWRST                */
#define _PRBS_SWRST_MASK                     0x00000003UL                               /**< Mask for PRBS_SWRST                         */
#define PRBS_SWRST_SWRST                     (0x1UL << 0)                               /**< Software Reset Command                      */
#define _PRBS_SWRST_SWRST_SHIFT              0                                          /**< Shift value for PRBS_SWRST                  */
#define _PRBS_SWRST_SWRST_MASK               0x1UL                                      /**< Bit mask for PRBS_SWRST                     */
#define _PRBS_SWRST_SWRST_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for PRBS_SWRST                 */
#define PRBS_SWRST_SWRST_DEFAULT             (_PRBS_SWRST_SWRST_DEFAULT << 0)           /**< Shifted mode DEFAULT for PRBS_SWRST         */
#define PRBS_SWRST_RESETTING                 (0x1UL << 1)                               /**< Software Reset Busy Status                  */
#define _PRBS_SWRST_RESETTING_SHIFT          1                                          /**< Shift value for PRBS_RESETTING              */
#define _PRBS_SWRST_RESETTING_MASK           0x2UL                                      /**< Bit mask for PRBS_RESETTING                 */
#define _PRBS_SWRST_RESETTING_DEFAULT        0x00000000UL                               /**< Mode DEFAULT for PRBS_SWRST                 */
#define PRBS_SWRST_RESETTING_DEFAULT         (_PRBS_SWRST_RESETTING_DEFAULT << 1)       /**< Shifted mode DEFAULT for PRBS_SWRST         */

/* Bit fields for PRBS CONNECT */
#define _PRBS_CONNECT_RESETVALUE             0x00000000UL                               /**< Default value for PRBS_CONNECT              */
#define _PRBS_CONNECT_MASK                   0x00000101UL                               /**< Mask for PRBS_CONNECT                       */
#define PRBS_CONNECT_IN                      (0x1UL << 0)                               /**< Input FIFO connect                          */
#define _PRBS_CONNECT_IN_SHIFT               0                                          /**< Shift value for PRBS_IN                     */
#define _PRBS_CONNECT_IN_MASK                0x1UL                                      /**< Bit mask for PRBS_IN                        */
#define _PRBS_CONNECT_IN_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for PRBS_CONNECT               */
#define PRBS_CONNECT_IN_DEFAULT              (_PRBS_CONNECT_IN_DEFAULT << 0)            /**< Shifted mode DEFAULT for PRBS_CONNECT       */
#define PRBS_CONNECT_OUT                     (0x1UL << 8)                               /**< Output FIFO connect                         */
#define _PRBS_CONNECT_OUT_SHIFT              8                                          /**< Shift value for PRBS_OUT                    */
#define _PRBS_CONNECT_OUT_MASK               0x100UL                                    /**< Bit mask for PRBS_OUT                       */
#define _PRBS_CONNECT_OUT_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for PRBS_CONNECT               */
#define PRBS_CONNECT_OUT_DEFAULT             (_PRBS_CONNECT_OUT_DEFAULT << 8)           /**< Shifted mode DEFAULT for PRBS_CONNECT       */

/* Bit fields for PRBS DISCLK */
#define _PRBS_DISCLK_RESETVALUE              0x00000002UL                               /**< Default value for PRBS_DISCLK               */
#define _PRBS_DISCLK_MASK                    0x00000003UL                               /**< Mask for PRBS_DISCLK                        */
#define _PRBS_DISCLK_DISCLK_SHIFT            0                                          /**< Shift value for PRBS_DISCLK                 */
#define _PRBS_DISCLK_DISCLK_MASK             0x3UL                                      /**< Bit mask for PRBS_DISCLK                    */
#define _PRBS_DISCLK_DISCLK_DEFAULT          0x00000002UL                               /**< Mode DEFAULT for PRBS_DISCLK                */
#define _PRBS_DISCLK_DISCLK_NONE             0x00000000UL                               /**< Mode NONE for PRBS_DISCLK                   */
#define _PRBS_DISCLK_DISCLK_ALL              0x00000001UL                               /**< Mode ALL for PRBS_DISCLK                    */
#define _PRBS_DISCLK_DISCLK_AUTO             0x00000002UL                               /**< Mode AUTO for PRBS_DISCLK                   */
#define _PRBS_DISCLK_DISCLK_NOTUSED          0x00000003UL                               /**< Mode NOTUSED for PRBS_DISCLK                */
#define PRBS_DISCLK_DISCLK_DEFAULT           (_PRBS_DISCLK_DISCLK_DEFAULT << 0)         /**< Shifted mode DEFAULT for PRBS_DISCLK        */
#define PRBS_DISCLK_DISCLK_NONE              (_PRBS_DISCLK_DISCLK_NONE << 0)            /**< Shifted mode NONE for PRBS_DISCLK           */
#define PRBS_DISCLK_DISCLK_ALL               (_PRBS_DISCLK_DISCLK_ALL << 0)             /**< Shifted mode ALL for PRBS_DISCLK            */
#define PRBS_DISCLK_DISCLK_AUTO              (_PRBS_DISCLK_DISCLK_AUTO << 0)            /**< Shifted mode AUTO for PRBS_DISCLK           */
#define PRBS_DISCLK_DISCLK_NOTUSED           (_PRBS_DISCLK_DISCLK_NOTUSED << 0)         /**< Shifted mode NOTUSED for PRBS_DISCLK        */

/* Bit fields for PRBS FIFOIN */
#define _PRBS_FIFOIN_RESETVALUE              0x00000000UL                               /**< Default value for PRBS_FIFOIN               */
#define _PRBS_FIFOIN_MASK                    0x1FFF3F0FUL                               /**< Mask for PRBS_FIFOIN                        */
#define _PRBS_FIFOIN_FID_SHIFT               0                                          /**< Shift value for PRBS_FID                    */
#define _PRBS_FIFOIN_FID_MASK                0xFUL                                      /**< Bit mask for PRBS_FID                       */
#define _PRBS_FIFOIN_FID_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for PRBS_FIFOIN                */
#define PRBS_FIFOIN_FID_DEFAULT              (_PRBS_FIFOIN_FID_DEFAULT << 0)            /**< Shifted mode DEFAULT for PRBS_FIFOIN        */
#define _PRBS_FIFOIN_CID_SHIFT               8                                          /**< Shift value for PRBS_CID                    */
#define _PRBS_FIFOIN_CID_MASK                0x3F00UL                                   /**< Bit mask for PRBS_CID                       */
#define _PRBS_FIFOIN_CID_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for PRBS_FIFOIN                */
#define PRBS_FIFOIN_CID_DEFAULT              (_PRBS_FIFOIN_CID_DEFAULT << 8)            /**< Shifted mode DEFAULT for PRBS_FIFOIN        */
#define _PRBS_FIFOIN_REM_SHIFT               16                                         /**< Shift value for PRBS_REM                    */
#define _PRBS_FIFOIN_REM_MASK                0xFF0000UL                                 /**< Bit mask for PRBS_REM                       */
#define _PRBS_FIFOIN_REM_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for PRBS_FIFOIN                */
#define PRBS_FIFOIN_REM_DEFAULT              (_PRBS_FIFOIN_REM_DEFAULT << 16)           /**< Shifted mode DEFAULT for PRBS_FIFOIN        */
#define _PRBS_FIFOIN_ALARM_SHIFT             24                                         /**< Shift value for PRBS_ALARM                  */
#define _PRBS_FIFOIN_ALARM_MASK              0x1F000000UL                               /**< Bit mask for PRBS_ALARM                     */
#define _PRBS_FIFOIN_ALARM_DEFAULT           0x00000000UL                               /**< Mode DEFAULT for PRBS_FIFOIN                */
#define PRBS_FIFOIN_ALARM_DEFAULT            (_PRBS_FIFOIN_ALARM_DEFAULT << 24)         /**< Shifted mode DEFAULT for PRBS_FIFOIN        */

/* Bit fields for PRBS FIFOOUT */
#define _PRBS_FIFOOUT_RESETVALUE             0x00000000UL                               /**< Default value for PRBS_FIFOOUT              */
#define _PRBS_FIFOOUT_MASK                   0x1FFF0000UL                               /**< Mask for PRBS_FIFOOUT                       */
#define _PRBS_FIFOOUT_CNT_SHIFT              16                                         /**< Shift value for PRBS_CNT                    */
#define _PRBS_FIFOOUT_CNT_MASK               0xFF0000UL                                 /**< Bit mask for PRBS_CNT                       */
#define _PRBS_FIFOOUT_CNT_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for PRBS_FIFOOUT               */
#define PRBS_FIFOOUT_CNT_DEFAULT             (_PRBS_FIFOOUT_CNT_DEFAULT << 16)          /**< Shifted mode DEFAULT for PRBS_FIFOOUT       */
#define _PRBS_FIFOOUT_ALARM_SHIFT            24                                         /**< Shift value for PRBS_ALARM                  */
#define _PRBS_FIFOOUT_ALARM_MASK             0x1F000000UL                               /**< Bit mask for PRBS_ALARM                     */
#define _PRBS_FIFOOUT_ALARM_DEFAULT          0x00000000UL                               /**< Mode DEFAULT for PRBS_FIFOOUT               */
#define PRBS_FIFOOUT_ALARM_DEFAULT           (_PRBS_FIFOOUT_ALARM_DEFAULT << 24)        /**< Shifted mode DEFAULT for PRBS_FIFOOUT       */

/* Bit fields for PRBS FMTIN */
#define _PRBS_FMTIN_RESETVALUE               0x0200001FUL                               /**< Default value for PRBS_FMTIN                */
#define _PRBS_FMTIN_MASK                     0x0303031FUL                               /**< Mask for PRBS_FMTIN                         */
#define _PRBS_FMTIN_ELEMSIZE_SHIFT           0                                          /**< Shift value for PRBS_ELEMSIZE               */
#define _PRBS_FMTIN_ELEMSIZE_MASK            0x1FUL                                     /**< Bit mask for PRBS_ELEMSIZE                  */
#define _PRBS_FMTIN_ELEMSIZE_DEFAULT         0x0000001FUL                               /**< Mode DEFAULT for PRBS_FMTIN                 */
#define PRBS_FMTIN_ELEMSIZE_DEFAULT          (_PRBS_FMTIN_ELEMSIZE_DEFAULT << 0)        /**< Shifted mode DEFAULT for PRBS_FMTIN         */
#define _PRBS_FMTIN_ELEMNB_SHIFT             8                                          /**< Shift value for PRBS_ELEMNB                 */
#define _PRBS_FMTIN_ELEMNB_MASK              0x300UL                                    /**< Bit mask for PRBS_ELEMNB                    */
#define _PRBS_FMTIN_ELEMNB_DEFAULT           0x00000000UL                               /**< Mode DEFAULT for PRBS_FMTIN                 */
#define _PRBS_FMTIN_ELEMNB_ONE               0x00000000UL                               /**< Mode ONE for PRBS_FMTIN                     */
#define _PRBS_FMTIN_ELEMNB_TWO               0x00000001UL                               /**< Mode TWO for PRBS_FMTIN                     */
#define _PRBS_FMTIN_ELEMNB_FOUR              0x00000002UL                               /**< Mode FOUR for PRBS_FMTIN                    */
#define PRBS_FMTIN_ELEMNB_DEFAULT            (_PRBS_FMTIN_ELEMNB_DEFAULT << 8)          /**< Shifted mode DEFAULT for PRBS_FMTIN         */
#define PRBS_FMTIN_ELEMNB_ONE                (_PRBS_FMTIN_ELEMNB_ONE << 8)              /**< Shifted mode ONE for PRBS_FMTIN             */
#define PRBS_FMTIN_ELEMNB_TWO                (_PRBS_FMTIN_ELEMNB_TWO << 8)              /**< Shifted mode TWO for PRBS_FMTIN             */
#define PRBS_FMTIN_ELEMNB_FOUR               (_PRBS_FMTIN_ELEMNB_FOUR << 8)             /**< Shifted mode FOUR for PRBS_FMTIN            */
#define _PRBS_FMTIN_ELEMALIGN_SHIFT          16                                         /**< Shift value for PRBS_ELEMALIGN              */
#define _PRBS_FMTIN_ELEMALIGN_MASK           0x30000UL                                  /**< Bit mask for PRBS_ELEMALIGN                 */
#define _PRBS_FMTIN_ELEMALIGN_DEFAULT        0x00000000UL                               /**< Mode DEFAULT for PRBS_FMTIN                 */
#define _PRBS_FMTIN_ELEMALIGN_WORD           0x00000000UL                               /**< Mode WORD for PRBS_FMTIN                    */
#define _PRBS_FMTIN_ELEMALIGN_HALFWORD       0x00000001UL                               /**< Mode HALFWORD for PRBS_FMTIN                */
#define _PRBS_FMTIN_ELEMALIGN_BYTE           0x00000002UL                               /**< Mode BYTE for PRBS_FMTIN                    */
#define PRBS_FMTIN_ELEMALIGN_DEFAULT         (_PRBS_FMTIN_ELEMALIGN_DEFAULT << 16)      /**< Shifted mode DEFAULT for PRBS_FMTIN         */
#define PRBS_FMTIN_ELEMALIGN_WORD            (_PRBS_FMTIN_ELEMALIGN_WORD << 16)         /**< Shifted mode WORD for PRBS_FMTIN            */
#define PRBS_FMTIN_ELEMALIGN_HALFWORD        (_PRBS_FMTIN_ELEMALIGN_HALFWORD << 16)     /**< Shifted mode HALFWORD for PRBS_FMTIN        */
#define PRBS_FMTIN_ELEMALIGN_BYTE            (_PRBS_FMTIN_ELEMALIGN_BYTE << 16)         /**< Shifted mode BYTE for PRBS_FMTIN            */
#define _PRBS_FMTIN_ELEMTYPE_SHIFT           24                                         /**< Shift value for PRBS_ELEMTYPE               */
#define _PRBS_FMTIN_ELEMTYPE_MASK            0x3000000UL                                /**< Bit mask for PRBS_ELEMTYPE                  */
#define _PRBS_FMTIN_ELEMTYPE_DEFAULT         0x00000002UL                               /**< Mode DEFAULT for PRBS_FMTIN                 */
#define _PRBS_FMTIN_ELEMTYPE_COMPLEX         0x00000000UL                               /**< Mode COMPLEX for PRBS_FMTIN                 */
#define _PRBS_FMTIN_ELEMTYPE_INTEGER         0x00000001UL                               /**< Mode INTEGER for PRBS_FMTIN                 */
#define _PRBS_FMTIN_ELEMTYPE_LOGIC           0x00000002UL                               /**< Mode LOGIC for PRBS_FMTIN                   */
#define PRBS_FMTIN_ELEMTYPE_DEFAULT          (_PRBS_FMTIN_ELEMTYPE_DEFAULT << 24)       /**< Shifted mode DEFAULT for PRBS_FMTIN         */
#define PRBS_FMTIN_ELEMTYPE_COMPLEX          (_PRBS_FMTIN_ELEMTYPE_COMPLEX << 24)       /**< Shifted mode COMPLEX for PRBS_FMTIN         */
#define PRBS_FMTIN_ELEMTYPE_INTEGER          (_PRBS_FMTIN_ELEMTYPE_INTEGER << 24)       /**< Shifted mode INTEGER for PRBS_FMTIN         */
#define PRBS_FMTIN_ELEMTYPE_LOGIC            (_PRBS_FMTIN_ELEMTYPE_LOGIC << 24)         /**< Shifted mode LOGIC for PRBS_FMTIN           */

/* Bit fields for PRBS CTRL1 */
#define _PRBS_CTRL1_RESETVALUE               0x00004000UL                               /**< Default value for PRBS_CTRL1                */
#define _PRBS_CTRL1_MASK                     0xFFFFC00FUL                               /**< Mask for PRBS_CTRL1                         */
#define PRBS_CTRL1_RST                       (0x1UL << 0)                               /**< New BitField                                */
#define _PRBS_CTRL1_RST_SHIFT                0                                          /**< Shift value for PRBS_RST                    */
#define _PRBS_CTRL1_RST_MASK                 0x1UL                                      /**< Bit mask for PRBS_RST                       */
#define _PRBS_CTRL1_RST_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for PRBS_CTRL1                 */
#define PRBS_CTRL1_RST_DEFAULT               (_PRBS_CTRL1_RST_DEFAULT << 0)             /**< Shifted mode DEFAULT for PRBS_CTRL1         */
#define PRBS_CTRL1_START                     (0x1UL << 1)                               /**< New BitField                                */
#define _PRBS_CTRL1_START_SHIFT              1                                          /**< Shift value for PRBS_START                  */
#define _PRBS_CTRL1_START_MASK               0x2UL                                      /**< Bit mask for PRBS_START                     */
#define _PRBS_CTRL1_START_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for PRBS_CTRL1                 */
#define _PRBS_CTRL1_START_IDLE               0x00000000UL                               /**< Mode IDLE for PRBS_CTRL1                    */
#define _PRBS_CTRL1_START_RUN                0x00000001UL                               /**< Mode RUN for PRBS_CTRL1                     */
#define PRBS_CTRL1_START_DEFAULT             (_PRBS_CTRL1_START_DEFAULT << 1)           /**< Shifted mode DEFAULT for PRBS_CTRL1         */
#define PRBS_CTRL1_START_IDLE                (_PRBS_CTRL1_START_IDLE << 1)              /**< Shifted mode IDLE for PRBS_CTRL1            */
#define PRBS_CTRL1_START_RUN                 (_PRBS_CTRL1_START_RUN << 1)               /**< Shifted mode RUN for PRBS_CTRL1             */
#define PRBS_CTRL1_CONT                      (0x1UL << 2)                               /**< New BitField                                */
#define _PRBS_CTRL1_CONT_SHIFT               2                                          /**< Shift value for PRBS_CONT                   */
#define _PRBS_CTRL1_CONT_MASK                0x4UL                                      /**< Bit mask for PRBS_CONT                      */
#define _PRBS_CTRL1_CONT_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for PRBS_CTRL1                 */
#define _PRBS_CTRL1_CONT_IDLE                0x00000000UL                               /**< Mode IDLE for PRBS_CTRL1                    */
#define _PRBS_CTRL1_CONT_RUN                 0x00000001UL                               /**< Mode RUN for PRBS_CTRL1                     */
#define PRBS_CTRL1_CONT_DEFAULT              (_PRBS_CTRL1_CONT_DEFAULT << 2)            /**< Shifted mode DEFAULT for PRBS_CTRL1         */
#define PRBS_CTRL1_CONT_IDLE                 (_PRBS_CTRL1_CONT_IDLE << 2)               /**< Shifted mode IDLE for PRBS_CTRL1            */
#define PRBS_CTRL1_CONT_RUN                  (_PRBS_CTRL1_CONT_RUN << 2)                /**< Shifted mode RUN for PRBS_CTRL1             */
#define PRBS_CTRL1_ENREQOUT                  (0x1UL << 3)                               /**< New BitField                                */
#define _PRBS_CTRL1_ENREQOUT_SHIFT           3                                          /**< Shift value for PRBS_ENREQOUT               */
#define _PRBS_CTRL1_ENREQOUT_MASK            0x8UL                                      /**< Bit mask for PRBS_ENREQOUT                  */
#define _PRBS_CTRL1_ENREQOUT_DEFAULT         0x00000000UL                               /**< Mode DEFAULT for PRBS_CTRL1                 */
#define _PRBS_CTRL1_ENREQOUT_NO              0x00000000UL                               /**< Mode NO for PRBS_CTRL1                      */
#define _PRBS_CTRL1_ENREQOUT_YES             0x00000001UL                               /**< Mode YES for PRBS_CTRL1                     */
#define PRBS_CTRL1_ENREQOUT_DEFAULT          (_PRBS_CTRL1_ENREQOUT_DEFAULT << 3)        /**< Shifted mode DEFAULT for PRBS_CTRL1         */
#define PRBS_CTRL1_ENREQOUT_NO               (_PRBS_CTRL1_ENREQOUT_NO << 3)             /**< Shifted mode NO for PRBS_CTRL1              */
#define PRBS_CTRL1_ENREQOUT_YES              (_PRBS_CTRL1_ENREQOUT_YES << 3)            /**< Shifted mode YES for PRBS_CTRL1             */
#define _PRBS_CTRL1_OUTSEL_SHIFT             14                                         /**< Shift value for PRBS_OUTSEL                 */
#define _PRBS_CTRL1_OUTSEL_MASK              0xC000UL                                   /**< Bit mask for PRBS_OUTSEL                    */
#define _PRBS_CTRL1_OUTSEL_DEFAULT           0x00000001UL                               /**< Mode DEFAULT for PRBS_CTRL1                 */
#define _PRBS_CTRL1_OUTSEL_FEEDBACK          0x00000000UL                               /**< Mode FEEDBACK for PRBS_CTRL1                */
#define _PRBS_CTRL1_OUTSEL_IDX               0x00000001UL                               /**< Mode IDX for PRBS_CTRL1                     */
#define _PRBS_CTRL1_OUTSEL_FEEDSEL           0x00000002UL                               /**< Mode FEEDSEL for PRBS_CTRL1                 */
#define PRBS_CTRL1_OUTSEL_DEFAULT            (_PRBS_CTRL1_OUTSEL_DEFAULT << 14)         /**< Shifted mode DEFAULT for PRBS_CTRL1         */
#define PRBS_CTRL1_OUTSEL_FEEDBACK           (_PRBS_CTRL1_OUTSEL_FEEDBACK << 14)        /**< Shifted mode FEEDBACK for PRBS_CTRL1        */
#define PRBS_CTRL1_OUTSEL_IDX                (_PRBS_CTRL1_OUTSEL_IDX << 14)             /**< Shifted mode IDX for PRBS_CTRL1             */
#define PRBS_CTRL1_OUTSEL_FEEDSEL            (_PRBS_CTRL1_OUTSEL_FEEDSEL << 14)         /**< Shifted mode FEEDSEL for PRBS_CTRL1         */
#define PRBS_CTRL1_INV                       (0x1UL << 16)                              /**< New BitField                                */
#define _PRBS_CTRL1_INV_SHIFT                16                                         /**< Shift value for PRBS_INV                    */
#define _PRBS_CTRL1_INV_MASK                 0x10000UL                                  /**< Bit mask for PRBS_INV                       */
#define _PRBS_CTRL1_INV_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for PRBS_CTRL1                 */
#define _PRBS_CTRL1_INV_NO                   0x00000000UL                               /**< Mode NO for PRBS_CTRL1                      */
#define _PRBS_CTRL1_INV_YES                  0x00000001UL                               /**< Mode YES for PRBS_CTRL1                     */
#define PRBS_CTRL1_INV_DEFAULT               (_PRBS_CTRL1_INV_DEFAULT << 16)            /**< Shifted mode DEFAULT for PRBS_CTRL1         */
#define PRBS_CTRL1_INV_NO                    (_PRBS_CTRL1_INV_NO << 16)                 /**< Shifted mode NO for PRBS_CTRL1              */
#define PRBS_CTRL1_INV_YES                   (_PRBS_CTRL1_INV_YES << 16)                /**< Shifted mode YES for PRBS_CTRL1             */
#define _PRBS_CTRL1_INSEL_SHIFT              17                                         /**< Shift value for PRBS_INSEL                  */
#define _PRBS_CTRL1_INSEL_MASK               0x60000UL                                  /**< Bit mask for PRBS_INSEL                     */
#define _PRBS_CTRL1_INSEL_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for PRBS_CTRL1                 */
#define _PRBS_CTRL1_INSEL_PRBSOUT            0x00000000UL                               /**< Mode PRBSOUT for PRBS_CTRL1                 */
#define _PRBS_CTRL1_INSEL_INPUT              0x00000001UL                               /**< Mode INPUT for PRBS_CTRL1                   */
#define _PRBS_CTRL1_INSEL_PRBSXORINPUT       0x00000002UL                               /**< Mode PRBSXORINPUT for PRBS_CTRL1            */
#define _PRBS_CTRL1_INSEL_NOTUSED            0x00000003UL                               /**< Mode NOTUSED for PRBS_CTRL1                 */
#define PRBS_CTRL1_INSEL_DEFAULT             (_PRBS_CTRL1_INSEL_DEFAULT << 17)          /**< Shifted mode DEFAULT for PRBS_CTRL1         */
#define PRBS_CTRL1_INSEL_PRBSOUT             (_PRBS_CTRL1_INSEL_PRBSOUT << 17)          /**< Shifted mode PRBSOUT for PRBS_CTRL1         */
#define PRBS_CTRL1_INSEL_INPUT               (_PRBS_CTRL1_INSEL_INPUT << 17)            /**< Shifted mode INPUT for PRBS_CTRL1           */
#define PRBS_CTRL1_INSEL_PRBSXORINPUT        (_PRBS_CTRL1_INSEL_PRBSXORINPUT << 17)     /**< Shifted mode PRBSXORINPUT for PRBS_CTRL1    */
#define PRBS_CTRL1_INSEL_NOTUSED             (_PRBS_CTRL1_INSEL_NOTUSED << 17)          /**< Shifted mode NOTUSED for PRBS_CTRL1         */
#define PRBS_CTRL1_USEINPUT                  (0x1UL << 19)                              /**< New BitField                                */
#define _PRBS_CTRL1_USEINPUT_SHIFT           19                                         /**< Shift value for PRBS_USEINPUT               */
#define _PRBS_CTRL1_USEINPUT_MASK            0x80000UL                                  /**< Bit mask for PRBS_USEINPUT                  */
#define _PRBS_CTRL1_USEINPUT_DEFAULT         0x00000000UL                               /**< Mode DEFAULT for PRBS_CTRL1                 */
#define _PRBS_CTRL1_USEINPUT_NO              0x00000000UL                               /**< Mode NO for PRBS_CTRL1                      */
#define _PRBS_CTRL1_USEINPUT_YES             0x00000001UL                               /**< Mode YES for PRBS_CTRL1                     */
#define PRBS_CTRL1_USEINPUT_DEFAULT          (_PRBS_CTRL1_USEINPUT_DEFAULT << 19)       /**< Shifted mode DEFAULT for PRBS_CTRL1         */
#define PRBS_CTRL1_USEINPUT_NO               (_PRBS_CTRL1_USEINPUT_NO << 19)            /**< Shifted mode NO for PRBS_CTRL1              */
#define PRBS_CTRL1_USEINPUT_YES              (_PRBS_CTRL1_USEINPUT_YES << 19)           /**< Shifted mode YES for PRBS_CTRL1             */
#define PRBS_CTRL1_OUTINV                    (0x1UL << 20)                              /**< New BitField                                */
#define _PRBS_CTRL1_OUTINV_SHIFT             20                                         /**< Shift value for PRBS_OUTINV                 */
#define _PRBS_CTRL1_OUTINV_MASK              0x100000UL                                 /**< Bit mask for PRBS_OUTINV                    */
#define _PRBS_CTRL1_OUTINV_DEFAULT           0x00000000UL                               /**< Mode DEFAULT for PRBS_CTRL1                 */
#define _PRBS_CTRL1_OUTINV_NO                0x00000000UL                               /**< Mode NO for PRBS_CTRL1                      */
#define _PRBS_CTRL1_OUTINV_YES               0x00000001UL                               /**< Mode YES for PRBS_CTRL1                     */
#define PRBS_CTRL1_OUTINV_DEFAULT            (_PRBS_CTRL1_OUTINV_DEFAULT << 20)         /**< Shifted mode DEFAULT for PRBS_CTRL1         */
#define PRBS_CTRL1_OUTINV_NO                 (_PRBS_CTRL1_OUTINV_NO << 20)              /**< Shifted mode NO for PRBS_CTRL1              */
#define PRBS_CTRL1_OUTINV_YES                (_PRBS_CTRL1_OUTINV_YES << 20)             /**< Shifted mode YES for PRBS_CTRL1             */
#define PRBS_CTRL1_SWAP                      (0x1UL << 21)                              /**< New BitField                                */
#define _PRBS_CTRL1_SWAP_SHIFT               21                                         /**< Shift value for PRBS_SWAP                   */
#define _PRBS_CTRL1_SWAP_MASK                0x200000UL                                 /**< Bit mask for PRBS_SWAP                      */
#define _PRBS_CTRL1_SWAP_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for PRBS_CTRL1                 */
#define _PRBS_CTRL1_SWAP_NO                  0x00000000UL                               /**< Mode NO for PRBS_CTRL1                      */
#define _PRBS_CTRL1_SWAP_YES                 0x00000001UL                               /**< Mode YES for PRBS_CTRL1                     */
#define PRBS_CTRL1_SWAP_DEFAULT              (_PRBS_CTRL1_SWAP_DEFAULT << 21)           /**< Shifted mode DEFAULT for PRBS_CTRL1         */
#define PRBS_CTRL1_SWAP_NO                   (_PRBS_CTRL1_SWAP_NO << 21)                /**< Shifted mode NO for PRBS_CTRL1              */
#define PRBS_CTRL1_SWAP_YES                  (_PRBS_CTRL1_SWAP_YES << 21)               /**< Shifted mode YES for PRBS_CTRL1             */
#define _PRBS_CTRL1_OUTIDX_SHIFT             22                                         /**< Shift value for PRBS_OUTIDX                 */
#define _PRBS_CTRL1_OUTIDX_MASK              0xFC00000UL                                /**< Bit mask for PRBS_OUTIDX                    */
#define _PRBS_CTRL1_OUTIDX_DEFAULT           0x00000000UL                               /**< Mode DEFAULT for PRBS_CTRL1                 */
#define PRBS_CTRL1_OUTIDX_DEFAULT            (_PRBS_CTRL1_OUTIDX_DEFAULT << 22)         /**< Shifted mode DEFAULT for PRBS_CTRL1         */
#define PRBS_CTRL1_SOFTBIT                   (0x1UL << 28)                              /**< New BitField                                */
#define _PRBS_CTRL1_SOFTBIT_SHIFT            28                                         /**< Shift value for PRBS_SOFTBIT                */
#define _PRBS_CTRL1_SOFTBIT_MASK             0x10000000UL                               /**< Bit mask for PRBS_SOFTBIT                   */
#define _PRBS_CTRL1_SOFTBIT_DEFAULT          0x00000000UL                               /**< Mode DEFAULT for PRBS_CTRL1                 */
#define _PRBS_CTRL1_SOFTBIT_NO               0x00000000UL                               /**< Mode NO for PRBS_CTRL1                      */
#define _PRBS_CTRL1_SOFTBIT_YES              0x00000001UL                               /**< Mode YES for PRBS_CTRL1                     */
#define PRBS_CTRL1_SOFTBIT_DEFAULT           (_PRBS_CTRL1_SOFTBIT_DEFAULT << 28)        /**< Shifted mode DEFAULT for PRBS_CTRL1         */
#define PRBS_CTRL1_SOFTBIT_NO                (_PRBS_CTRL1_SOFTBIT_NO << 28)             /**< Shifted mode NO for PRBS_CTRL1              */
#define PRBS_CTRL1_SOFTBIT_YES               (_PRBS_CTRL1_SOFTBIT_YES << 28)            /**< Shifted mode YES for PRBS_CTRL1             */
#define PRBS_CTRL1_SYNCSTAT                  (0x1UL << 29)                              /**< New BitField                                */
#define _PRBS_CTRL1_SYNCSTAT_SHIFT           29                                         /**< Shift value for PRBS_SYNCSTAT               */
#define _PRBS_CTRL1_SYNCSTAT_MASK            0x20000000UL                               /**< Bit mask for PRBS_SYNCSTAT                  */
#define _PRBS_CTRL1_SYNCSTAT_DEFAULT         0x00000000UL                               /**< Mode DEFAULT for PRBS_CTRL1                 */
#define _PRBS_CTRL1_SYNCSTAT_NO              0x00000000UL                               /**< Mode NO for PRBS_CTRL1                      */
#define _PRBS_CTRL1_SYNCSTAT_YES             0x00000001UL                               /**< Mode YES for PRBS_CTRL1                     */
#define PRBS_CTRL1_SYNCSTAT_DEFAULT          (_PRBS_CTRL1_SYNCSTAT_DEFAULT << 29)       /**< Shifted mode DEFAULT for PRBS_CTRL1         */
#define PRBS_CTRL1_SYNCSTAT_NO               (_PRBS_CTRL1_SYNCSTAT_NO << 29)            /**< Shifted mode NO for PRBS_CTRL1              */
#define PRBS_CTRL1_SYNCSTAT_YES              (_PRBS_CTRL1_SYNCSTAT_YES << 29)           /**< Shifted mode YES for PRBS_CTRL1             */
#define PRBS_CTRL1_BYPASS                    (0x1UL << 30)                              /**< New BitField                                */
#define _PRBS_CTRL1_BYPASS_SHIFT             30                                         /**< Shift value for PRBS_BYPASS                 */
#define _PRBS_CTRL1_BYPASS_MASK              0x40000000UL                               /**< Bit mask for PRBS_BYPASS                    */
#define _PRBS_CTRL1_BYPASS_DEFAULT           0x00000000UL                               /**< Mode DEFAULT for PRBS_CTRL1                 */
#define _PRBS_CTRL1_BYPASS_NO                0x00000000UL                               /**< Mode NO for PRBS_CTRL1                      */
#define _PRBS_CTRL1_BYPASS_YES               0x00000001UL                               /**< Mode YES for PRBS_CTRL1                     */
#define PRBS_CTRL1_BYPASS_DEFAULT            (_PRBS_CTRL1_BYPASS_DEFAULT << 30)         /**< Shifted mode DEFAULT for PRBS_CTRL1         */
#define PRBS_CTRL1_BYPASS_NO                 (_PRBS_CTRL1_BYPASS_NO << 30)              /**< Shifted mode NO for PRBS_CTRL1              */
#define PRBS_CTRL1_BYPASS_YES                (_PRBS_CTRL1_BYPASS_YES << 30)             /**< Shifted mode YES for PRBS_CTRL1             */
#define PRBS_CTRL1_DEBUG                     (0x1UL << 31)                              /**< New BitField                                */
#define _PRBS_CTRL1_DEBUG_SHIFT              31                                         /**< Shift value for PRBS_DEBUG                  */
#define _PRBS_CTRL1_DEBUG_MASK               0x80000000UL                               /**< Bit mask for PRBS_DEBUG                     */
#define _PRBS_CTRL1_DEBUG_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for PRBS_CTRL1                 */
#define _PRBS_CTRL1_DEBUG_NO                 0x00000000UL                               /**< Mode NO for PRBS_CTRL1                      */
#define _PRBS_CTRL1_DEBUG_YES                0x00000001UL                               /**< Mode YES for PRBS_CTRL1                     */
#define PRBS_CTRL1_DEBUG_DEFAULT             (_PRBS_CTRL1_DEBUG_DEFAULT << 31)          /**< Shifted mode DEFAULT for PRBS_CTRL1         */
#define PRBS_CTRL1_DEBUG_NO                  (_PRBS_CTRL1_DEBUG_NO << 31)               /**< Shifted mode NO for PRBS_CTRL1              */
#define PRBS_CTRL1_DEBUG_YES                 (_PRBS_CTRL1_DEBUG_YES << 31)              /**< Shifted mode YES for PRBS_CTRL1             */

/* Bit fields for PRBS INIT */
#define _PRBS_INIT_RESETVALUE                0x00000000UL                               /**< Default value for PRBS_INIT                 */
#define _PRBS_INIT_MASK                      0xFFFFFFFFUL                               /**< Mask for PRBS_INIT                          */
#define _PRBS_INIT_INIT_SHIFT                0                                          /**< Shift value for PRBS_INIT                   */
#define _PRBS_INIT_INIT_MASK                 0xFFFFFFFFUL                               /**< Bit mask for PRBS_INIT                      */
#define _PRBS_INIT_INIT_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for PRBS_INIT                  */
#define PRBS_INIT_INIT_DEFAULT               (_PRBS_INIT_INIT_DEFAULT << 0)             /**< Shifted mode DEFAULT for PRBS_INIT          */

/* Bit fields for PRBS CTRL2 */
#define _PRBS_CTRL2_RESETVALUE               0x00830020UL                               /**< Default value for PRBS_CTRL2                */
#define _PRBS_CTRL2_MASK                     0xFFFFFFFFUL                               /**< Mask for PRBS_CTRL2                         */
#define _PRBS_CTRL2_NBITER_SHIFT             0                                          /**< Shift value for PRBS_NBITER                 */
#define _PRBS_CTRL2_NBITER_MASK              0xFFFFUL                                   /**< Bit mask for PRBS_NBITER                    */
#define _PRBS_CTRL2_NBITER_DEFAULT           0x00000020UL                               /**< Mode DEFAULT for PRBS_CTRL2                 */
#define PRBS_CTRL2_NBITER_DEFAULT            (_PRBS_CTRL2_NBITER_DEFAULT << 0)          /**< Shifted mode DEFAULT for PRBS_CTRL2         */
#define PRBS_CTRL2_SELCOMPLEMENT             (0x1UL << 16)                              /**< New BitField                                */
#define _PRBS_CTRL2_SELCOMPLEMENT_SHIFT      16                                         /**< Shift value for PRBS_SELCOMPLEMENT          */
#define _PRBS_CTRL2_SELCOMPLEMENT_MASK       0x10000UL                                  /**< Bit mask for PRBS_SELCOMPLEMENT             */
#define _PRBS_CTRL2_SELCOMPLEMENT_DEFAULT    0x00000001UL                               /**< Mode DEFAULT for PRBS_CTRL2                 */
#define _PRBS_CTRL2_SELCOMPLEMENT_CA1        0x00000000UL                               /**< Mode CA1 for PRBS_CTRL2                     */
#define _PRBS_CTRL2_SELCOMPLEMENT_CA2        0x00000001UL                               /**< Mode CA2 for PRBS_CTRL2                     */
#define PRBS_CTRL2_SELCOMPLEMENT_DEFAULT     (_PRBS_CTRL2_SELCOMPLEMENT_DEFAULT << 16)  /**< Shifted mode DEFAULT for PRBS_CTRL2         */
#define PRBS_CTRL2_SELCOMPLEMENT_CA1         (_PRBS_CTRL2_SELCOMPLEMENT_CA1 << 16)      /**< Shifted mode CA1 for PRBS_CTRL2             */
#define PRBS_CTRL2_SELCOMPLEMENT_CA2         (_PRBS_CTRL2_SELCOMPLEMENT_CA2 << 16)      /**< Shifted mode CA2 for PRBS_CTRL2             */
#define PRBS_CTRL2_SCRAMBLE                  (0x1UL << 17)                              /**< New BitField                                */
#define _PRBS_CTRL2_SCRAMBLE_SHIFT           17                                         /**< Shift value for PRBS_SCRAMBLE               */
#define _PRBS_CTRL2_SCRAMBLE_MASK            0x20000UL                                  /**< Bit mask for PRBS_SCRAMBLE                  */
#define _PRBS_CTRL2_SCRAMBLE_DEFAULT         0x00000001UL                               /**< Mode DEFAULT for PRBS_CTRL2                 */
#define _PRBS_CTRL2_SCRAMBLE_NO              0x00000000UL                               /**< Mode NO for PRBS_CTRL2                      */
#define _PRBS_CTRL2_SCRAMBLE_YES             0x00000001UL                               /**< Mode YES for PRBS_CTRL2                     */
#define PRBS_CTRL2_SCRAMBLE_DEFAULT          (_PRBS_CTRL2_SCRAMBLE_DEFAULT << 17)       /**< Shifted mode DEFAULT for PRBS_CTRL2         */
#define PRBS_CTRL2_SCRAMBLE_NO               (_PRBS_CTRL2_SCRAMBLE_NO << 17)            /**< Shifted mode NO for PRBS_CTRL2              */
#define PRBS_CTRL2_SCRAMBLE_YES              (_PRBS_CTRL2_SCRAMBLE_YES << 17)           /**< Shifted mode YES for PRBS_CTRL2             */
#define _PRBS_CTRL2_BDEPERIOD_SHIFT          18                                         /**< Shift value for PRBS_BDEPERIOD              */
#define _PRBS_CTRL2_BDEPERIOD_MASK           0xFFFC0000UL                               /**< Bit mask for PRBS_BDEPERIOD                 */
#define _PRBS_CTRL2_BDEPERIOD_DEFAULT        0x00000020UL                               /**< Mode DEFAULT for PRBS_CTRL2                 */
#define PRBS_CTRL2_BDEPERIOD_DEFAULT         (_PRBS_CTRL2_BDEPERIOD_DEFAULT << 18)      /**< Shifted mode DEFAULT for PRBS_CTRL2         */

/* Bit fields for PRBS STAT */
#define _PRBS_STAT_RESETVALUE                0x00000000UL                               /**< Default value for PRBS_STAT                 */
#define _PRBS_STAT_MASK                      0xFFFFFFFFUL                               /**< Mask for PRBS_STAT                          */
#define _PRBS_STAT_RES_SHIFT                 0                                          /**< Shift value for PRBS_RES                    */
#define _PRBS_STAT_RES_MASK                  0xFFFFFFFFUL                               /**< Bit mask for PRBS_RES                       */
#define _PRBS_STAT_RES_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for PRBS_STAT                  */
#define PRBS_STAT_RES_DEFAULT                (_PRBS_STAT_RES_DEFAULT << 0)              /**< Shifted mode DEFAULT for PRBS_STAT          */

/* Bit fields for PRBS SEQ */
#define _PRBS_SEQ_RESETVALUE                 0x00000000UL                               /**< Default value for PRBS_SEQ                  */
#define _PRBS_SEQ_MASK                       0xFFFFFFFFUL                               /**< Mask for PRBS_SEQ                           */
#define _PRBS_SEQ_SEQ_SHIFT                  0                                          /**< Shift value for PRBS_SEQ                    */
#define _PRBS_SEQ_SEQ_MASK                   0xFFFFFFFFUL                               /**< Bit mask for PRBS_SEQ                       */
#define _PRBS_SEQ_SEQ_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for PRBS_SEQ                   */
#define PRBS_SEQ_SEQ_DEFAULT                 (_PRBS_SEQ_SEQ_DEFAULT << 0)               /**< Shifted mode DEFAULT for PRBS_SEQ           */

/* Bit fields for PRBS POLY */
#define _PRBS_POLY_RESETVALUE                0x00000000UL                               /**< Default value for PRBS_POLY                 */
#define _PRBS_POLY_MASK                      0xFFFFFFFFUL                               /**< Mask for PRBS_POLY                          */
#define _PRBS_POLY_POLY_SHIFT                0                                          /**< Shift value for PRBS_POLY                   */
#define _PRBS_POLY_POLY_MASK                 0xFFFFFFFFUL                               /**< Bit mask for PRBS_POLY                      */
#define _PRBS_POLY_POLY_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for PRBS_POLY                  */
#define PRBS_POLY_POLY_DEFAULT               (_PRBS_POLY_POLY_DEFAULT << 0)             /**< Shifted mode DEFAULT for PRBS_POLY          */

/* Bit fields for PRBS FEED */
#define _PRBS_FEED_RESETVALUE                0x00000000UL                               /**< Default value for PRBS_FEED                 */
#define _PRBS_FEED_MASK                      0xFFFFFFFFUL                               /**< Mask for PRBS_FEED                          */
#define _PRBS_FEED_FEED_SHIFT                0                                          /**< Shift value for PRBS_FEED                   */
#define _PRBS_FEED_FEED_MASK                 0xFFFFFFFFUL                               /**< Bit mask for PRBS_FEED                      */
#define _PRBS_FEED_FEED_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for PRBS_FEED                  */
#define PRBS_FEED_FEED_DEFAULT               (_PRBS_FEED_FEED_DEFAULT << 0)             /**< Shifted mode DEFAULT for PRBS_FEED          */

/** @} End of group EFR32FG25_PRBS_BitFields */
/** @} End of group EFR32FG25_PRBS */
/** @} End of group Parts */

#endif /* EFR32FG25_PRBS_H */
