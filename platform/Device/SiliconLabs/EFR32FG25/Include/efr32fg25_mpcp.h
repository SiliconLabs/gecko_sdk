/**************************************************************************//**
 * @file
 * @brief EFR32FG25 MPCP register and bit field definitions
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
#ifndef EFR32FG25_MPCP_H
#define EFR32FG25_MPCP_H
#define MPCP_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_MPCP MPCP
 * @{
 * @brief EFR32FG25 MPCP Register Declaration.
 *****************************************************************************/

/** MPCP FIFOIN Register Group Declaration. */
typedef struct {
  __IOM uint32_t FIFOIN;                             /**< New Register                                       */
} MPCP_FIFOIN_TypeDef;

/** MPCP Register Declaration. */
typedef struct {
  __IM uint32_t       IPVERSION;                /**< IP Version ID                                      */
  __IOM uint32_t      EN;                       /**< Module Enable                                      */
  __IOM uint32_t      SWRST;                    /**< Software Reset                                     */
  __IOM uint32_t      CONNECT;                  /**< New Register                                       */
  __IOM uint32_t      DISCLK;                   /**< Disable Clocks                                     */
  uint32_t            RESERVED0[3U];            /**< Reserved for future use                            */
  MPCP_FIFOIN_TypeDef FIFOIN[4U];               /**<                                                    */
  uint32_t            RESERVED1[4U];            /**< Reserved for future use                            */
  __IM uint32_t       FIFOOUT;                  /**< New Register                                       */
  uint32_t            RESERVED2[23U];           /**< Reserved for future use                            */
  uint32_t            RESERVED3[1U];            /**< Reserved for future use                            */
  uint32_t            RESERVED4[7U];            /**< Reserved for future use                            */
  __IOM uint32_t      FMTOUT;                   /**< New Register                                       */
  uint32_t            RESERVED5[79U];           /**< Reserved for future use                            */
  __IOM uint32_t      CTRL1;                    /**< New Register                                       */
  __IOM uint32_t      CTRL2;                    /**< New Register                                       */
  __IOM uint32_t      CTRL3;                    /**< New Register                                       */
  __IOM uint32_t      CTEA;                     /**< New Register                                       */
  __IOM uint32_t      CTEB;                     /**< New Register                                       */
  __IOM uint32_t      CTEC;                     /**< New Register                                       */
  __IOM uint32_t      BYPASS;                   /**< New Register                                       */
  __IM uint32_t       STAT;                     /**< New Register                                       */
  __IOM uint32_t      CTRL4;                    /**< New Register                                       */
  __IOM uint32_t      IF;                       /**< New Register                                       */
  __IOM uint32_t      IEN;                      /**< New Register                                       */
  __IOM uint32_t      CTRL5;                    /**< New Register                                       */
  __IM uint32_t       MINMAXI;                  /**< New Register                                       */
  __IM uint32_t       MINMAXQ;                  /**< New Register                                       */
  __IM uint32_t       MINMAXIDX;                /**< New Register                                       */
  uint32_t            RESERVED6[881U];          /**< Reserved for future use                            */
  __IM uint32_t       IPVERSION_SET;            /**< IP Version ID                                      */
  __IOM uint32_t      EN_SET;                   /**< Module Enable                                      */
  __IOM uint32_t      SWRST_SET;                /**< Software Reset                                     */
  __IOM uint32_t      CONNECT_SET;              /**< New Register                                       */
  __IOM uint32_t      DISCLK_SET;               /**< Disable Clocks                                     */
  uint32_t            RESERVED7[3U];            /**< Reserved for future use                            */
  MPCP_FIFOIN_TypeDef FIFOIN_SET[4U];           /**<                                                    */
  uint32_t            RESERVED8[4U];            /**< Reserved for future use                            */
  __IM uint32_t       FIFOOUT_SET;              /**< New Register                                       */
  uint32_t            RESERVED9[23U];           /**< Reserved for future use                            */
  uint32_t            RESERVED10[1U];           /**< Reserved for future use                            */
  uint32_t            RESERVED11[7U];           /**< Reserved for future use                            */
  __IOM uint32_t      FMTOUT_SET;               /**< New Register                                       */
  uint32_t            RESERVED12[79U];          /**< Reserved for future use                            */
  __IOM uint32_t      CTRL1_SET;                /**< New Register                                       */
  __IOM uint32_t      CTRL2_SET;                /**< New Register                                       */
  __IOM uint32_t      CTRL3_SET;                /**< New Register                                       */
  __IOM uint32_t      CTEA_SET;                 /**< New Register                                       */
  __IOM uint32_t      CTEB_SET;                 /**< New Register                                       */
  __IOM uint32_t      CTEC_SET;                 /**< New Register                                       */
  __IOM uint32_t      BYPASS_SET;               /**< New Register                                       */
  __IM uint32_t       STAT_SET;                 /**< New Register                                       */
  __IOM uint32_t      CTRL4_SET;                /**< New Register                                       */
  __IOM uint32_t      IF_SET;                   /**< New Register                                       */
  __IOM uint32_t      IEN_SET;                  /**< New Register                                       */
  __IOM uint32_t      CTRL5_SET;                /**< New Register                                       */
  __IM uint32_t       MINMAXI_SET;              /**< New Register                                       */
  __IM uint32_t       MINMAXQ_SET;              /**< New Register                                       */
  __IM uint32_t       MINMAXIDX_SET;            /**< New Register                                       */
  uint32_t            RESERVED13[881U];         /**< Reserved for future use                            */
  __IM uint32_t       IPVERSION_CLR;            /**< IP Version ID                                      */
  __IOM uint32_t      EN_CLR;                   /**< Module Enable                                      */
  __IOM uint32_t      SWRST_CLR;                /**< Software Reset                                     */
  __IOM uint32_t      CONNECT_CLR;              /**< New Register                                       */
  __IOM uint32_t      DISCLK_CLR;               /**< Disable Clocks                                     */
  uint32_t            RESERVED14[3U];           /**< Reserved for future use                            */
  MPCP_FIFOIN_TypeDef FIFOIN_CLR[4U];           /**<                                                    */
  uint32_t            RESERVED15[4U];           /**< Reserved for future use                            */
  __IM uint32_t       FIFOOUT_CLR;              /**< New Register                                       */
  uint32_t            RESERVED16[23U];          /**< Reserved for future use                            */
  uint32_t            RESERVED17[1U];           /**< Reserved for future use                            */
  uint32_t            RESERVED18[7U];           /**< Reserved for future use                            */
  __IOM uint32_t      FMTOUT_CLR;               /**< New Register                                       */
  uint32_t            RESERVED19[79U];          /**< Reserved for future use                            */
  __IOM uint32_t      CTRL1_CLR;                /**< New Register                                       */
  __IOM uint32_t      CTRL2_CLR;                /**< New Register                                       */
  __IOM uint32_t      CTRL3_CLR;                /**< New Register                                       */
  __IOM uint32_t      CTEA_CLR;                 /**< New Register                                       */
  __IOM uint32_t      CTEB_CLR;                 /**< New Register                                       */
  __IOM uint32_t      CTEC_CLR;                 /**< New Register                                       */
  __IOM uint32_t      BYPASS_CLR;               /**< New Register                                       */
  __IM uint32_t       STAT_CLR;                 /**< New Register                                       */
  __IOM uint32_t      CTRL4_CLR;                /**< New Register                                       */
  __IOM uint32_t      IF_CLR;                   /**< New Register                                       */
  __IOM uint32_t      IEN_CLR;                  /**< New Register                                       */
  __IOM uint32_t      CTRL5_CLR;                /**< New Register                                       */
  __IM uint32_t       MINMAXI_CLR;              /**< New Register                                       */
  __IM uint32_t       MINMAXQ_CLR;              /**< New Register                                       */
  __IM uint32_t       MINMAXIDX_CLR;            /**< New Register                                       */
  uint32_t            RESERVED20[881U];         /**< Reserved for future use                            */
  __IM uint32_t       IPVERSION_TGL;            /**< IP Version ID                                      */
  __IOM uint32_t      EN_TGL;                   /**< Module Enable                                      */
  __IOM uint32_t      SWRST_TGL;                /**< Software Reset                                     */
  __IOM uint32_t      CONNECT_TGL;              /**< New Register                                       */
  __IOM uint32_t      DISCLK_TGL;               /**< Disable Clocks                                     */
  uint32_t            RESERVED21[3U];           /**< Reserved for future use                            */
  MPCP_FIFOIN_TypeDef FIFOIN_TGL[4U];           /**<                                                    */
  uint32_t            RESERVED22[4U];           /**< Reserved for future use                            */
  __IM uint32_t       FIFOOUT_TGL;              /**< New Register                                       */
  uint32_t            RESERVED23[23U];          /**< Reserved for future use                            */
  uint32_t            RESERVED24[1U];           /**< Reserved for future use                            */
  uint32_t            RESERVED25[7U];           /**< Reserved for future use                            */
  __IOM uint32_t      FMTOUT_TGL;               /**< New Register                                       */
  uint32_t            RESERVED26[79U];          /**< Reserved for future use                            */
  __IOM uint32_t      CTRL1_TGL;                /**< New Register                                       */
  __IOM uint32_t      CTRL2_TGL;                /**< New Register                                       */
  __IOM uint32_t      CTRL3_TGL;                /**< New Register                                       */
  __IOM uint32_t      CTEA_TGL;                 /**< New Register                                       */
  __IOM uint32_t      CTEB_TGL;                 /**< New Register                                       */
  __IOM uint32_t      CTEC_TGL;                 /**< New Register                                       */
  __IOM uint32_t      BYPASS_TGL;               /**< New Register                                       */
  __IM uint32_t       STAT_TGL;                 /**< New Register                                       */
  __IOM uint32_t      CTRL4_TGL;                /**< New Register                                       */
  __IOM uint32_t      IF_TGL;                   /**< New Register                                       */
  __IOM uint32_t      IEN_TGL;                  /**< New Register                                       */
  __IOM uint32_t      CTRL5_TGL;                /**< New Register                                       */
  __IM uint32_t       MINMAXI_TGL;              /**< New Register                                       */
  __IM uint32_t       MINMAXQ_TGL;              /**< New Register                                       */
  __IM uint32_t       MINMAXIDX_TGL;            /**< New Register                                       */
} MPCP_TypeDef;
/** @} End of group EFR32FG25_MPCP */

/**************************************************************************//**
 * @addtogroup EFR32FG25_MPCP
 * @{
 * @defgroup EFR32FG25_MPCP_BitFields MPCP Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for MPCP IPVERSION */
#define _MPCP_IPVERSION_RESETVALUE            0x00000001UL                              /**< Default value for MPCP_IPVERSION            */
#define _MPCP_IPVERSION_MASK                  0xFFFFFFFFUL                              /**< Mask for MPCP_IPVERSION                     */
#define _MPCP_IPVERSION_IPVERSION_SHIFT       0                                         /**< Shift value for MPCP_IPVERSION              */
#define _MPCP_IPVERSION_IPVERSION_MASK        0xFFFFFFFFUL                              /**< Bit mask for MPCP_IPVERSION                 */
#define _MPCP_IPVERSION_IPVERSION_DEFAULT     0x00000001UL                              /**< Mode DEFAULT for MPCP_IPVERSION             */
#define MPCP_IPVERSION_IPVERSION_DEFAULT      (_MPCP_IPVERSION_IPVERSION_DEFAULT << 0)  /**< Shifted mode DEFAULT for MPCP_IPVERSION     */

/* Bit fields for MPCP EN */
#define _MPCP_EN_RESETVALUE                   0x00000000UL                              /**< Default value for MPCP_EN                   */
#define _MPCP_EN_MASK                         0x00000003UL                              /**< Mask for MPCP_EN                            */
#define MPCP_EN_EN                            (0x1UL << 0)                              /**< Module Enable                               */
#define _MPCP_EN_EN_SHIFT                     0                                         /**< Shift value for MPCP_EN                     */
#define _MPCP_EN_EN_MASK                      0x1UL                                     /**< Bit mask for MPCP_EN                        */
#define _MPCP_EN_EN_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for MPCP_EN                    */
#define MPCP_EN_EN_DEFAULT                    (_MPCP_EN_EN_DEFAULT << 0)                /**< Shifted mode DEFAULT for MPCP_EN            */
#define MPCP_EN_DISABLING                     (0x1UL << 1)                              /**< Disablement Busy Status                     */
#define _MPCP_EN_DISABLING_SHIFT              1                                         /**< Shift value for MPCP_DISABLING              */
#define _MPCP_EN_DISABLING_MASK               0x2UL                                     /**< Bit mask for MPCP_DISABLING                 */
#define _MPCP_EN_DISABLING_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for MPCP_EN                    */
#define MPCP_EN_DISABLING_DEFAULT             (_MPCP_EN_DISABLING_DEFAULT << 1)         /**< Shifted mode DEFAULT for MPCP_EN            */

/* Bit fields for MPCP SWRST */
#define _MPCP_SWRST_RESETVALUE                0x00000000UL                              /**< Default value for MPCP_SWRST                */
#define _MPCP_SWRST_MASK                      0x00000003UL                              /**< Mask for MPCP_SWRST                         */
#define MPCP_SWRST_SWRST                      (0x1UL << 0)                              /**< Software Reset Command                      */
#define _MPCP_SWRST_SWRST_SHIFT               0                                         /**< Shift value for MPCP_SWRST                  */
#define _MPCP_SWRST_SWRST_MASK                0x1UL                                     /**< Bit mask for MPCP_SWRST                     */
#define _MPCP_SWRST_SWRST_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for MPCP_SWRST                 */
#define MPCP_SWRST_SWRST_DEFAULT              (_MPCP_SWRST_SWRST_DEFAULT << 0)          /**< Shifted mode DEFAULT for MPCP_SWRST         */
#define MPCP_SWRST_RESETTING                  (0x1UL << 1)                              /**< Software Reset Busy Status                  */
#define _MPCP_SWRST_RESETTING_SHIFT           1                                         /**< Shift value for MPCP_RESETTING              */
#define _MPCP_SWRST_RESETTING_MASK            0x2UL                                     /**< Bit mask for MPCP_RESETTING                 */
#define _MPCP_SWRST_RESETTING_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for MPCP_SWRST                 */
#define MPCP_SWRST_RESETTING_DEFAULT          (_MPCP_SWRST_RESETTING_DEFAULT << 1)      /**< Shifted mode DEFAULT for MPCP_SWRST         */

/* Bit fields for MPCP CONNECT */
#define _MPCP_CONNECT_RESETVALUE              0x00000000UL                              /**< Default value for MPCP_CONNECT              */
#define _MPCP_CONNECT_MASK                    0x0000010FUL                              /**< Mask for MPCP_CONNECT                       */
#define _MPCP_CONNECT_IN_SHIFT                0                                         /**< Shift value for MPCP_IN                     */
#define _MPCP_CONNECT_IN_MASK                 0xFUL                                     /**< Bit mask for MPCP_IN                        */
#define _MPCP_CONNECT_IN_DEFAULT              0x00000000UL                              /**< Mode DEFAULT for MPCP_CONNECT               */
#define MPCP_CONNECT_IN_DEFAULT               (_MPCP_CONNECT_IN_DEFAULT << 0)           /**< Shifted mode DEFAULT for MPCP_CONNECT       */
#define MPCP_CONNECT_OUT                      (0x1UL << 8)                              /**< Output FIFO connect                         */
#define _MPCP_CONNECT_OUT_SHIFT               8                                         /**< Shift value for MPCP_OUT                    */
#define _MPCP_CONNECT_OUT_MASK                0x100UL                                   /**< Bit mask for MPCP_OUT                       */
#define _MPCP_CONNECT_OUT_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for MPCP_CONNECT               */
#define MPCP_CONNECT_OUT_DEFAULT              (_MPCP_CONNECT_OUT_DEFAULT << 8)          /**< Shifted mode DEFAULT for MPCP_CONNECT       */

/* Bit fields for MPCP DISCLK */
#define _MPCP_DISCLK_RESETVALUE               0x00000002UL                              /**< Default value for MPCP_DISCLK               */
#define _MPCP_DISCLK_MASK                     0x00000003UL                              /**< Mask for MPCP_DISCLK                        */
#define _MPCP_DISCLK_DISCLK_SHIFT             0                                         /**< Shift value for MPCP_DISCLK                 */
#define _MPCP_DISCLK_DISCLK_MASK              0x3UL                                     /**< Bit mask for MPCP_DISCLK                    */
#define _MPCP_DISCLK_DISCLK_DEFAULT           0x00000002UL                              /**< Mode DEFAULT for MPCP_DISCLK                */
#define _MPCP_DISCLK_DISCLK_NONE              0x00000000UL                              /**< Mode NONE for MPCP_DISCLK                   */
#define _MPCP_DISCLK_DISCLK_ALL               0x00000001UL                              /**< Mode ALL for MPCP_DISCLK                    */
#define _MPCP_DISCLK_DISCLK_AUTO              0x00000002UL                              /**< Mode AUTO for MPCP_DISCLK                   */
#define _MPCP_DISCLK_DISCLK_NOTUSED           0x00000003UL                              /**< Mode NOTUSED for MPCP_DISCLK                */
#define MPCP_DISCLK_DISCLK_DEFAULT            (_MPCP_DISCLK_DISCLK_DEFAULT << 0)        /**< Shifted mode DEFAULT for MPCP_DISCLK        */
#define MPCP_DISCLK_DISCLK_NONE               (_MPCP_DISCLK_DISCLK_NONE << 0)           /**< Shifted mode NONE for MPCP_DISCLK           */
#define MPCP_DISCLK_DISCLK_ALL                (_MPCP_DISCLK_DISCLK_ALL << 0)            /**< Shifted mode ALL for MPCP_DISCLK            */
#define MPCP_DISCLK_DISCLK_AUTO               (_MPCP_DISCLK_DISCLK_AUTO << 0)           /**< Shifted mode AUTO for MPCP_DISCLK           */
#define MPCP_DISCLK_DISCLK_NOTUSED            (_MPCP_DISCLK_DISCLK_NOTUSED << 0)        /**< Shifted mode NOTUSED for MPCP_DISCLK        */

/* Bit fields for MPCP FIFOIN */
#define _MPCP_FIFOIN_RESETVALUE               0x00000000UL                              /**< Default value for MPCP_FIFOIN               */
#define _MPCP_FIFOIN_MASK                     0x1FFF3F0FUL                              /**< Mask for MPCP_FIFOIN                        */
#define _MPCP_FIFOIN_FID_SHIFT                0                                         /**< Shift value for MPCP_FID                    */
#define _MPCP_FIFOIN_FID_MASK                 0xFUL                                     /**< Bit mask for MPCP_FID                       */
#define _MPCP_FIFOIN_FID_DEFAULT              0x00000000UL                              /**< Mode DEFAULT for MPCP_FIFOIN                */
#define MPCP_FIFOIN_FID_DEFAULT               (_MPCP_FIFOIN_FID_DEFAULT << 0)           /**< Shifted mode DEFAULT for MPCP_FIFOIN        */
#define _MPCP_FIFOIN_CID_SHIFT                8                                         /**< Shift value for MPCP_CID                    */
#define _MPCP_FIFOIN_CID_MASK                 0x3F00UL                                  /**< Bit mask for MPCP_CID                       */
#define _MPCP_FIFOIN_CID_DEFAULT              0x00000000UL                              /**< Mode DEFAULT for MPCP_FIFOIN                */
#define MPCP_FIFOIN_CID_DEFAULT               (_MPCP_FIFOIN_CID_DEFAULT << 8)           /**< Shifted mode DEFAULT for MPCP_FIFOIN        */
#define _MPCP_FIFOIN_REM_SHIFT                16                                        /**< Shift value for MPCP_REM                    */
#define _MPCP_FIFOIN_REM_MASK                 0xFF0000UL                                /**< Bit mask for MPCP_REM                       */
#define _MPCP_FIFOIN_REM_DEFAULT              0x00000000UL                              /**< Mode DEFAULT for MPCP_FIFOIN                */
#define MPCP_FIFOIN_REM_DEFAULT               (_MPCP_FIFOIN_REM_DEFAULT << 16)          /**< Shifted mode DEFAULT for MPCP_FIFOIN        */
#define _MPCP_FIFOIN_ALARM_SHIFT              24                                        /**< Shift value for MPCP_ALARM                  */
#define _MPCP_FIFOIN_ALARM_MASK               0x1F000000UL                              /**< Bit mask for MPCP_ALARM                     */
#define _MPCP_FIFOIN_ALARM_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for MPCP_FIFOIN                */
#define MPCP_FIFOIN_ALARM_DEFAULT             (_MPCP_FIFOIN_ALARM_DEFAULT << 24)        /**< Shifted mode DEFAULT for MPCP_FIFOIN        */

/* Bit fields for MPCP FIFOOUT */
#define _MPCP_FIFOOUT_RESETVALUE              0x00000000UL                              /**< Default value for MPCP_FIFOOUT              */
#define _MPCP_FIFOOUT_MASK                    0x1FFF0000UL                              /**< Mask for MPCP_FIFOOUT                       */
#define _MPCP_FIFOOUT_CNT_SHIFT               16                                        /**< Shift value for MPCP_CNT                    */
#define _MPCP_FIFOOUT_CNT_MASK                0xFF0000UL                                /**< Bit mask for MPCP_CNT                       */
#define _MPCP_FIFOOUT_CNT_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for MPCP_FIFOOUT               */
#define MPCP_FIFOOUT_CNT_DEFAULT              (_MPCP_FIFOOUT_CNT_DEFAULT << 16)         /**< Shifted mode DEFAULT for MPCP_FIFOOUT       */
#define _MPCP_FIFOOUT_ALARM_SHIFT             24                                        /**< Shift value for MPCP_ALARM                  */
#define _MPCP_FIFOOUT_ALARM_MASK              0x1F000000UL                              /**< Bit mask for MPCP_ALARM                     */
#define _MPCP_FIFOOUT_ALARM_DEFAULT           0x00000000UL                              /**< Mode DEFAULT for MPCP_FIFOOUT               */
#define MPCP_FIFOOUT_ALARM_DEFAULT            (_MPCP_FIFOOUT_ALARM_DEFAULT << 24)       /**< Shifted mode DEFAULT for MPCP_FIFOOUT       */

/* Bit fields for MPCP FMTOUT */
#define _MPCP_FMTOUT_RESETVALUE               0x0000000FUL                              /**< Default value for MPCP_FMTOUT               */
#define _MPCP_FMTOUT_MASK                     0x0303031FUL                              /**< Mask for MPCP_FMTOUT                        */
#define _MPCP_FMTOUT_ELEMSIZE_SHIFT           0                                         /**< Shift value for MPCP_ELEMSIZE               */
#define _MPCP_FMTOUT_ELEMSIZE_MASK            0x1FUL                                    /**< Bit mask for MPCP_ELEMSIZE                  */
#define _MPCP_FMTOUT_ELEMSIZE_DEFAULT         0x0000000FUL                              /**< Mode DEFAULT for MPCP_FMTOUT                */
#define MPCP_FMTOUT_ELEMSIZE_DEFAULT          (_MPCP_FMTOUT_ELEMSIZE_DEFAULT << 0)      /**< Shifted mode DEFAULT for MPCP_FMTOUT        */
#define _MPCP_FMTOUT_ELEMNB_SHIFT             8                                         /**< Shift value for MPCP_ELEMNB                 */
#define _MPCP_FMTOUT_ELEMNB_MASK              0x300UL                                   /**< Bit mask for MPCP_ELEMNB                    */
#define _MPCP_FMTOUT_ELEMNB_DEFAULT           0x00000000UL                              /**< Mode DEFAULT for MPCP_FMTOUT                */
#define _MPCP_FMTOUT_ELEMNB_ONE               0x00000000UL                              /**< Mode ONE for MPCP_FMTOUT                    */
#define _MPCP_FMTOUT_ELEMNB_TWO               0x00000001UL                              /**< Mode TWO for MPCP_FMTOUT                    */
#define _MPCP_FMTOUT_ELEMNB_FOUR              0x00000002UL                              /**< Mode FOUR for MPCP_FMTOUT                   */
#define MPCP_FMTOUT_ELEMNB_DEFAULT            (_MPCP_FMTOUT_ELEMNB_DEFAULT << 8)        /**< Shifted mode DEFAULT for MPCP_FMTOUT        */
#define MPCP_FMTOUT_ELEMNB_ONE                (_MPCP_FMTOUT_ELEMNB_ONE << 8)            /**< Shifted mode ONE for MPCP_FMTOUT            */
#define MPCP_FMTOUT_ELEMNB_TWO                (_MPCP_FMTOUT_ELEMNB_TWO << 8)            /**< Shifted mode TWO for MPCP_FMTOUT            */
#define MPCP_FMTOUT_ELEMNB_FOUR               (_MPCP_FMTOUT_ELEMNB_FOUR << 8)           /**< Shifted mode FOUR for MPCP_FMTOUT           */
#define _MPCP_FMTOUT_ELEMALIGN_SHIFT          16                                        /**< Shift value for MPCP_ELEMALIGN              */
#define _MPCP_FMTOUT_ELEMALIGN_MASK           0x30000UL                                 /**< Bit mask for MPCP_ELEMALIGN                 */
#define _MPCP_FMTOUT_ELEMALIGN_DEFAULT        0x00000000UL                              /**< Mode DEFAULT for MPCP_FMTOUT                */
#define _MPCP_FMTOUT_ELEMALIGN_WORD           0x00000000UL                              /**< Mode WORD for MPCP_FMTOUT                   */
#define _MPCP_FMTOUT_ELEMALIGN_HALFWORD       0x00000001UL                              /**< Mode HALFWORD for MPCP_FMTOUT               */
#define _MPCP_FMTOUT_ELEMALIGN_BYTE           0x00000002UL                              /**< Mode BYTE for MPCP_FMTOUT                   */
#define MPCP_FMTOUT_ELEMALIGN_DEFAULT         (_MPCP_FMTOUT_ELEMALIGN_DEFAULT << 16)    /**< Shifted mode DEFAULT for MPCP_FMTOUT        */
#define MPCP_FMTOUT_ELEMALIGN_WORD            (_MPCP_FMTOUT_ELEMALIGN_WORD << 16)       /**< Shifted mode WORD for MPCP_FMTOUT           */
#define MPCP_FMTOUT_ELEMALIGN_HALFWORD        (_MPCP_FMTOUT_ELEMALIGN_HALFWORD << 16)   /**< Shifted mode HALFWORD for MPCP_FMTOUT       */
#define MPCP_FMTOUT_ELEMALIGN_BYTE            (_MPCP_FMTOUT_ELEMALIGN_BYTE << 16)       /**< Shifted mode BYTE for MPCP_FMTOUT           */
#define _MPCP_FMTOUT_ELEMTYPE_SHIFT           24                                        /**< Shift value for MPCP_ELEMTYPE               */
#define _MPCP_FMTOUT_ELEMTYPE_MASK            0x3000000UL                               /**< Bit mask for MPCP_ELEMTYPE                  */
#define _MPCP_FMTOUT_ELEMTYPE_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for MPCP_FMTOUT                */
#define _MPCP_FMTOUT_ELEMTYPE_COMPLEX         0x00000000UL                              /**< Mode COMPLEX for MPCP_FMTOUT                */
#define _MPCP_FMTOUT_ELEMTYPE_INTEGER         0x00000001UL                              /**< Mode INTEGER for MPCP_FMTOUT                */
#define _MPCP_FMTOUT_ELEMTYPE_LOGIC           0x00000002UL                              /**< Mode LOGIC for MPCP_FMTOUT                  */
#define MPCP_FMTOUT_ELEMTYPE_DEFAULT          (_MPCP_FMTOUT_ELEMTYPE_DEFAULT << 24)     /**< Shifted mode DEFAULT for MPCP_FMTOUT        */
#define MPCP_FMTOUT_ELEMTYPE_COMPLEX          (_MPCP_FMTOUT_ELEMTYPE_COMPLEX << 24)     /**< Shifted mode COMPLEX for MPCP_FMTOUT        */
#define MPCP_FMTOUT_ELEMTYPE_INTEGER          (_MPCP_FMTOUT_ELEMTYPE_INTEGER << 24)     /**< Shifted mode INTEGER for MPCP_FMTOUT        */
#define MPCP_FMTOUT_ELEMTYPE_LOGIC            (_MPCP_FMTOUT_ELEMTYPE_LOGIC << 24)       /**< Shifted mode LOGIC for MPCP_FMTOUT          */

/* Bit fields for MPCP CTRL1 */
#define _MPCP_CTRL1_RESETVALUE                0x00000000UL                              /**< Default value for MPCP_CTRL1                */
#define _MPCP_CTRL1_MASK                      0xFFFFFFFFUL                              /**< Mask for MPCP_CTRL1                         */
#define MPCP_CTRL1_RST                        (0x1UL << 0)                              /**< New BitField                                */
#define _MPCP_CTRL1_RST_SHIFT                 0                                         /**< Shift value for MPCP_RST                    */
#define _MPCP_CTRL1_RST_MASK                  0x1UL                                     /**< Bit mask for MPCP_RST                       */
#define _MPCP_CTRL1_RST_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL1                 */
#define MPCP_CTRL1_RST_DEFAULT                (_MPCP_CTRL1_RST_DEFAULT << 0)            /**< Shifted mode DEFAULT for MPCP_CTRL1         */
#define MPCP_CTRL1_START                      (0x1UL << 1)                              /**< New BitField                                */
#define _MPCP_CTRL1_START_SHIFT               1                                         /**< Shift value for MPCP_START                  */
#define _MPCP_CTRL1_START_MASK                0x2UL                                     /**< Bit mask for MPCP_START                     */
#define _MPCP_CTRL1_START_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL1                 */
#define _MPCP_CTRL1_START_Stop                0x00000000UL                              /**< Mode Stop for MPCP_CTRL1                    */
#define _MPCP_CTRL1_START_Start               0x00000001UL                              /**< Mode Start for MPCP_CTRL1                   */
#define MPCP_CTRL1_START_DEFAULT              (_MPCP_CTRL1_START_DEFAULT << 1)          /**< Shifted mode DEFAULT for MPCP_CTRL1         */
#define MPCP_CTRL1_START_Stop                 (_MPCP_CTRL1_START_Stop << 1)             /**< Shifted mode Stop for MPCP_CTRL1            */
#define MPCP_CTRL1_START_Start                (_MPCP_CTRL1_START_Start << 1)            /**< Shifted mode Start for MPCP_CTRL1           */
#define MPCP_CTRL1_DISRST                     (0x1UL << 2)                              /**< New BitField                                */
#define _MPCP_CTRL1_DISRST_SHIFT              2                                         /**< Shift value for MPCP_DISRST                 */
#define _MPCP_CTRL1_DISRST_MASK               0x4UL                                     /**< Bit mask for MPCP_DISRST                    */
#define _MPCP_CTRL1_DISRST_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL1                 */
#define _MPCP_CTRL1_DISRST_NO                 0x00000000UL                              /**< Mode NO for MPCP_CTRL1                      */
#define _MPCP_CTRL1_DISRST_YES                0x00000001UL                              /**< Mode YES for MPCP_CTRL1                     */
#define MPCP_CTRL1_DISRST_DEFAULT             (_MPCP_CTRL1_DISRST_DEFAULT << 2)         /**< Shifted mode DEFAULT for MPCP_CTRL1         */
#define MPCP_CTRL1_DISRST_NO                  (_MPCP_CTRL1_DISRST_NO << 2)              /**< Shifted mode NO for MPCP_CTRL1              */
#define MPCP_CTRL1_DISRST_YES                 (_MPCP_CTRL1_DISRST_YES << 2)             /**< Shifted mode YES for MPCP_CTRL1             */
#define MPCP_CTRL1_ENREQOUT                   (0x1UL << 3)                              /**< New BitField                                */
#define _MPCP_CTRL1_ENREQOUT_SHIFT            3                                         /**< Shift value for MPCP_ENREQOUT               */
#define _MPCP_CTRL1_ENREQOUT_MASK             0x8UL                                     /**< Bit mask for MPCP_ENREQOUT                  */
#define _MPCP_CTRL1_ENREQOUT_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL1                 */
#define _MPCP_CTRL1_ENREQOUT_NO               0x00000000UL                              /**< Mode NO for MPCP_CTRL1                      */
#define _MPCP_CTRL1_ENREQOUT_YES              0x00000001UL                              /**< Mode YES for MPCP_CTRL1                     */
#define MPCP_CTRL1_ENREQOUT_DEFAULT           (_MPCP_CTRL1_ENREQOUT_DEFAULT << 3)       /**< Shifted mode DEFAULT for MPCP_CTRL1         */
#define MPCP_CTRL1_ENREQOUT_NO                (_MPCP_CTRL1_ENREQOUT_NO << 3)            /**< Shifted mode NO for MPCP_CTRL1              */
#define MPCP_CTRL1_ENREQOUT_YES               (_MPCP_CTRL1_ENREQOUT_YES << 3)           /**< Shifted mode YES for MPCP_CTRL1             */
#define MPCP_CTRL1_FORMATIN                   (0x1UL << 4)                              /**< New BitField                                */
#define _MPCP_CTRL1_FORMATIN_SHIFT            4                                         /**< Shift value for MPCP_FORMATIN               */
#define _MPCP_CTRL1_FORMATIN_MASK             0x10UL                                    /**< Bit mask for MPCP_FORMATIN                  */
#define _MPCP_CTRL1_FORMATIN_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL1                 */
#define _MPCP_CTRL1_FORMATIN_Long             0x00000000UL                              /**< Mode Long for MPCP_CTRL1                    */
#define _MPCP_CTRL1_FORMATIN_Short            0x00000001UL                              /**< Mode Short for MPCP_CTRL1                   */
#define MPCP_CTRL1_FORMATIN_DEFAULT           (_MPCP_CTRL1_FORMATIN_DEFAULT << 4)       /**< Shifted mode DEFAULT for MPCP_CTRL1         */
#define MPCP_CTRL1_FORMATIN_Long              (_MPCP_CTRL1_FORMATIN_Long << 4)          /**< Shifted mode Long for MPCP_CTRL1            */
#define MPCP_CTRL1_FORMATIN_Short             (_MPCP_CTRL1_FORMATIN_Short << 4)         /**< Shifted mode Short for MPCP_CTRL1           */
#define MPCP_CTRL1_WHITENING                  (0x1UL << 5)                              /**< New BitField                                */
#define _MPCP_CTRL1_WHITENING_SHIFT           5                                         /**< Shift value for MPCP_WHITENING              */
#define _MPCP_CTRL1_WHITENING_MASK            0x20UL                                    /**< Bit mask for MPCP_WHITENING                 */
#define _MPCP_CTRL1_WHITENING_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL1                 */
#define _MPCP_CTRL1_WHITENING_Disable         0x00000000UL                              /**< Mode Disable for MPCP_CTRL1                 */
#define _MPCP_CTRL1_WHITENING_Enable          0x00000001UL                              /**< Mode Enable for MPCP_CTRL1                  */
#define MPCP_CTRL1_WHITENING_DEFAULT          (_MPCP_CTRL1_WHITENING_DEFAULT << 5)      /**< Shifted mode DEFAULT for MPCP_CTRL1         */
#define MPCP_CTRL1_WHITENING_Disable          (_MPCP_CTRL1_WHITENING_Disable << 5)      /**< Shifted mode Disable for MPCP_CTRL1         */
#define MPCP_CTRL1_WHITENING_Enable           (_MPCP_CTRL1_WHITENING_Enable << 5)       /**< Shifted mode Enable for MPCP_CTRL1          */
#define MPCP_CTRL1_USECOSSIN                  (0x1UL << 6)                              /**< New BitField                                */
#define _MPCP_CTRL1_USECOSSIN_SHIFT           6                                         /**< Shift value for MPCP_USECOSSIN              */
#define _MPCP_CTRL1_USECOSSIN_MASK            0x40UL                                    /**< Bit mask for MPCP_USECOSSIN                 */
#define _MPCP_CTRL1_USECOSSIN_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL1                 */
#define _MPCP_CTRL1_USECOSSIN_NO              0x00000000UL                              /**< Mode NO for MPCP_CTRL1                      */
#define _MPCP_CTRL1_USECOSSIN_YES             0x00000001UL                              /**< Mode YES for MPCP_CTRL1                     */
#define MPCP_CTRL1_USECOSSIN_DEFAULT          (_MPCP_CTRL1_USECOSSIN_DEFAULT << 6)      /**< Shifted mode DEFAULT for MPCP_CTRL1         */
#define MPCP_CTRL1_USECOSSIN_NO               (_MPCP_CTRL1_USECOSSIN_NO << 6)           /**< Shifted mode NO for MPCP_CTRL1              */
#define MPCP_CTRL1_USECOSSIN_YES              (_MPCP_CTRL1_USECOSSIN_YES << 6)          /**< Shifted mode YES for MPCP_CTRL1             */
#define MPCP_CTRL1_DECIMATE                   (0x1UL << 7)                              /**< New BitField                                */
#define _MPCP_CTRL1_DECIMATE_SHIFT            7                                         /**< Shift value for MPCP_DECIMATE               */
#define _MPCP_CTRL1_DECIMATE_MASK             0x80UL                                    /**< Bit mask for MPCP_DECIMATE                  */
#define _MPCP_CTRL1_DECIMATE_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL1                 */
#define _MPCP_CTRL1_DECIMATE_Disable          0x00000000UL                              /**< Mode Disable for MPCP_CTRL1                 */
#define _MPCP_CTRL1_DECIMATE_Enable           0x00000001UL                              /**< Mode Enable for MPCP_CTRL1                  */
#define MPCP_CTRL1_DECIMATE_DEFAULT           (_MPCP_CTRL1_DECIMATE_DEFAULT << 7)       /**< Shifted mode DEFAULT for MPCP_CTRL1         */
#define MPCP_CTRL1_DECIMATE_Disable           (_MPCP_CTRL1_DECIMATE_Disable << 7)       /**< Shifted mode Disable for MPCP_CTRL1         */
#define MPCP_CTRL1_DECIMATE_Enable            (_MPCP_CTRL1_DECIMATE_Enable << 7)        /**< Shifted mode Enable for MPCP_CTRL1          */
#define MPCP_CTRL1_DEROTDSSS                  (0x1UL << 8)                              /**< New BitField                                */
#define _MPCP_CTRL1_DEROTDSSS_SHIFT           8                                         /**< Shift value for MPCP_DEROTDSSS              */
#define _MPCP_CTRL1_DEROTDSSS_MASK            0x100UL                                   /**< Bit mask for MPCP_DEROTDSSS                 */
#define _MPCP_CTRL1_DEROTDSSS_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL1                 */
#define _MPCP_CTRL1_DEROTDSSS_NO              0x00000000UL                              /**< Mode NO for MPCP_CTRL1                      */
#define _MPCP_CTRL1_DEROTDSSS_YES             0x00000001UL                              /**< Mode YES for MPCP_CTRL1                     */
#define MPCP_CTRL1_DEROTDSSS_DEFAULT          (_MPCP_CTRL1_DEROTDSSS_DEFAULT << 8)      /**< Shifted mode DEFAULT for MPCP_CTRL1         */
#define MPCP_CTRL1_DEROTDSSS_NO               (_MPCP_CTRL1_DEROTDSSS_NO << 8)           /**< Shifted mode NO for MPCP_CTRL1              */
#define MPCP_CTRL1_DEROTDSSS_YES              (_MPCP_CTRL1_DEROTDSSS_YES << 8)          /**< Shifted mode YES for MPCP_CTRL1             */
#define MPCP_CTRL1_PRBSMOD                    (0x1UL << 9)                              /**< New BitField                                */
#define _MPCP_CTRL1_PRBSMOD_SHIFT             9                                         /**< Shift value for MPCP_PRBSMOD                */
#define _MPCP_CTRL1_PRBSMOD_MASK              0x200UL                                   /**< Bit mask for MPCP_PRBSMOD                   */
#define _MPCP_CTRL1_PRBSMOD_DEFAULT           0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL1                 */
#define _MPCP_CTRL1_PRBSMOD_NO                0x00000000UL                              /**< Mode NO for MPCP_CTRL1                      */
#define _MPCP_CTRL1_PRBSMOD_YES               0x00000001UL                              /**< Mode YES for MPCP_CTRL1                     */
#define MPCP_CTRL1_PRBSMOD_DEFAULT            (_MPCP_CTRL1_PRBSMOD_DEFAULT << 9)        /**< Shifted mode DEFAULT for MPCP_CTRL1         */
#define MPCP_CTRL1_PRBSMOD_NO                 (_MPCP_CTRL1_PRBSMOD_NO << 9)             /**< Shifted mode NO for MPCP_CTRL1              */
#define MPCP_CTRL1_PRBSMOD_YES                (_MPCP_CTRL1_PRBSMOD_YES << 9)            /**< Shifted mode YES for MPCP_CTRL1             */
#define MPCP_CTRL1_SWAPIQOUT                  (0x1UL << 10)                             /**< New BitField                                */
#define _MPCP_CTRL1_SWAPIQOUT_SHIFT           10                                        /**< Shift value for MPCP_SWAPIQOUT              */
#define _MPCP_CTRL1_SWAPIQOUT_MASK            0x400UL                                   /**< Bit mask for MPCP_SWAPIQOUT                 */
#define _MPCP_CTRL1_SWAPIQOUT_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL1                 */
#define _MPCP_CTRL1_SWAPIQOUT_No              0x00000000UL                              /**< Mode No for MPCP_CTRL1                      */
#define _MPCP_CTRL1_SWAPIQOUT_Yes             0x00000001UL                              /**< Mode Yes for MPCP_CTRL1                     */
#define MPCP_CTRL1_SWAPIQOUT_DEFAULT          (_MPCP_CTRL1_SWAPIQOUT_DEFAULT << 10)     /**< Shifted mode DEFAULT for MPCP_CTRL1         */
#define MPCP_CTRL1_SWAPIQOUT_No               (_MPCP_CTRL1_SWAPIQOUT_No << 10)          /**< Shifted mode No for MPCP_CTRL1              */
#define MPCP_CTRL1_SWAPIQOUT_Yes              (_MPCP_CTRL1_SWAPIQOUT_Yes << 10)         /**< Shifted mode Yes for MPCP_CTRL1             */
#define MPCP_CTRL1_SYNCSTAT                   (0x1UL << 11)                             /**< New BitField                                */
#define _MPCP_CTRL1_SYNCSTAT_SHIFT            11                                        /**< Shift value for MPCP_SYNCSTAT               */
#define _MPCP_CTRL1_SYNCSTAT_MASK             0x800UL                                   /**< Bit mask for MPCP_SYNCSTAT                  */
#define _MPCP_CTRL1_SYNCSTAT_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL1                 */
#define _MPCP_CTRL1_SYNCSTAT_NO               0x00000000UL                              /**< Mode NO for MPCP_CTRL1                      */
#define _MPCP_CTRL1_SYNCSTAT_YES              0x00000001UL                              /**< Mode YES for MPCP_CTRL1                     */
#define MPCP_CTRL1_SYNCSTAT_DEFAULT           (_MPCP_CTRL1_SYNCSTAT_DEFAULT << 11)      /**< Shifted mode DEFAULT for MPCP_CTRL1         */
#define MPCP_CTRL1_SYNCSTAT_NO                (_MPCP_CTRL1_SYNCSTAT_NO << 11)           /**< Shifted mode NO for MPCP_CTRL1              */
#define MPCP_CTRL1_SYNCSTAT_YES               (_MPCP_CTRL1_SYNCSTAT_YES << 11)          /**< Shifted mode YES for MPCP_CTRL1             */
#define _MPCP_CTRL1_OP1_SHIFT                 12                                        /**< Shift value for MPCP_OP1                    */
#define _MPCP_CTRL1_OP1_MASK                  0xF000UL                                  /**< Bit mask for MPCP_OP1                       */
#define _MPCP_CTRL1_OP1_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL1                 */
#define _MPCP_CTRL1_OP1_A                     0x00000000UL                              /**< Mode A for MPCP_CTRL1                       */
#define _MPCP_CTRL1_OP1_B                     0x00000001UL                              /**< Mode B for MPCP_CTRL1                       */
#define _MPCP_CTRL1_OP1_minusA                0x00000002UL                              /**< Mode minusA for MPCP_CTRL1                  */
#define _MPCP_CTRL1_OP1_minusB                0x00000003UL                              /**< Mode minusB for MPCP_CTRL1                  */
#define _MPCP_CTRL1_OP1_AplusB                0x00000004UL                              /**< Mode AplusB for MPCP_CTRL1                  */
#define _MPCP_CTRL1_OP1_AminusB               0x00000005UL                              /**< Mode AminusB for MPCP_CTRL1                 */
#define _MPCP_CTRL1_OP1_AmulB                 0x00000006UL                              /**< Mode AmulB for MPCP_CTRL1                   */
#define _MPCP_CTRL1_OP1_AmulConjB             0x00000007UL                              /**< Mode AmulConjB for MPCP_CTRL1               */
#define _MPCP_CTRL1_OP1_AmulConjA             0x00000009UL                              /**< Mode AmulConjA for MPCP_CTRL1               */
#define _MPCP_CTRL1_OP1_BmulConjB             0x0000000AUL                              /**< Mode BmulConjB for MPCP_CTRL1               */
#define _MPCP_CTRL1_OP1_AxorB                 0x0000000BUL                              /**< Mode AxorB for MPCP_CTRL1                   */
#define _MPCP_CTRL1_OP1_SquareRoot            0x0000000CUL                              /**< Mode SquareRoot for MPCP_CTRL1              */
#define MPCP_CTRL1_OP1_DEFAULT                (_MPCP_CTRL1_OP1_DEFAULT << 12)           /**< Shifted mode DEFAULT for MPCP_CTRL1         */
#define MPCP_CTRL1_OP1_A                      (_MPCP_CTRL1_OP1_A << 12)                 /**< Shifted mode A for MPCP_CTRL1               */
#define MPCP_CTRL1_OP1_B                      (_MPCP_CTRL1_OP1_B << 12)                 /**< Shifted mode B for MPCP_CTRL1               */
#define MPCP_CTRL1_OP1_minusA                 (_MPCP_CTRL1_OP1_minusA << 12)            /**< Shifted mode minusA for MPCP_CTRL1          */
#define MPCP_CTRL1_OP1_minusB                 (_MPCP_CTRL1_OP1_minusB << 12)            /**< Shifted mode minusB for MPCP_CTRL1          */
#define MPCP_CTRL1_OP1_AplusB                 (_MPCP_CTRL1_OP1_AplusB << 12)            /**< Shifted mode AplusB for MPCP_CTRL1          */
#define MPCP_CTRL1_OP1_AminusB                (_MPCP_CTRL1_OP1_AminusB << 12)           /**< Shifted mode AminusB for MPCP_CTRL1         */
#define MPCP_CTRL1_OP1_AmulB                  (_MPCP_CTRL1_OP1_AmulB << 12)             /**< Shifted mode AmulB for MPCP_CTRL1           */
#define MPCP_CTRL1_OP1_AmulConjB              (_MPCP_CTRL1_OP1_AmulConjB << 12)         /**< Shifted mode AmulConjB for MPCP_CTRL1       */
#define MPCP_CTRL1_OP1_AmulConjA              (_MPCP_CTRL1_OP1_AmulConjA << 12)         /**< Shifted mode AmulConjA for MPCP_CTRL1       */
#define MPCP_CTRL1_OP1_BmulConjB              (_MPCP_CTRL1_OP1_BmulConjB << 12)         /**< Shifted mode BmulConjB for MPCP_CTRL1       */
#define MPCP_CTRL1_OP1_AxorB                  (_MPCP_CTRL1_OP1_AxorB << 12)             /**< Shifted mode AxorB for MPCP_CTRL1           */
#define MPCP_CTRL1_OP1_SquareRoot             (_MPCP_CTRL1_OP1_SquareRoot << 12)        /**< Shifted mode SquareRoot for MPCP_CTRL1      */
#define _MPCP_CTRL1_OP2_SHIFT                 16                                        /**< Shift value for MPCP_OP2                    */
#define _MPCP_CTRL1_OP2_MASK                  0xF0000UL                                 /**< Bit mask for MPCP_OP2                       */
#define _MPCP_CTRL1_OP2_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL1                 */
#define _MPCP_CTRL1_OP2_A                     0x00000000UL                              /**< Mode A for MPCP_CTRL1                       */
#define _MPCP_CTRL1_OP2_B                     0x00000001UL                              /**< Mode B for MPCP_CTRL1                       */
#define _MPCP_CTRL1_OP2_minusA                0x00000002UL                              /**< Mode minusA for MPCP_CTRL1                  */
#define _MPCP_CTRL1_OP2_minusB                0x00000003UL                              /**< Mode minusB for MPCP_CTRL1                  */
#define _MPCP_CTRL1_OP2_AplusB                0x00000004UL                              /**< Mode AplusB for MPCP_CTRL1                  */
#define _MPCP_CTRL1_OP2_AminusB               0x00000005UL                              /**< Mode AminusB for MPCP_CTRL1                 */
#define _MPCP_CTRL1_OP2_AmulB                 0x00000006UL                              /**< Mode AmulB for MPCP_CTRL1                   */
#define _MPCP_CTRL1_OP2_AmulConjB             0x00000007UL                              /**< Mode AmulConjB for MPCP_CTRL1               */
#define _MPCP_CTRL1_OP2_AdivB                 0x00000008UL                              /**< Mode AdivB for MPCP_CTRL1                   */
#define _MPCP_CTRL1_OP2_AmulConjA             0x00000009UL                              /**< Mode AmulConjA for MPCP_CTRL1               */
#define _MPCP_CTRL1_OP2_BmulConjB             0x0000000AUL                              /**< Mode BmulConjB for MPCP_CTRL1               */
#define _MPCP_CTRL1_OP2_AxorB                 0x0000000BUL                              /**< Mode AxorB for MPCP_CTRL1                   */
#define MPCP_CTRL1_OP2_DEFAULT                (_MPCP_CTRL1_OP2_DEFAULT << 16)           /**< Shifted mode DEFAULT for MPCP_CTRL1         */
#define MPCP_CTRL1_OP2_A                      (_MPCP_CTRL1_OP2_A << 16)                 /**< Shifted mode A for MPCP_CTRL1               */
#define MPCP_CTRL1_OP2_B                      (_MPCP_CTRL1_OP2_B << 16)                 /**< Shifted mode B for MPCP_CTRL1               */
#define MPCP_CTRL1_OP2_minusA                 (_MPCP_CTRL1_OP2_minusA << 16)            /**< Shifted mode minusA for MPCP_CTRL1          */
#define MPCP_CTRL1_OP2_minusB                 (_MPCP_CTRL1_OP2_minusB << 16)            /**< Shifted mode minusB for MPCP_CTRL1          */
#define MPCP_CTRL1_OP2_AplusB                 (_MPCP_CTRL1_OP2_AplusB << 16)            /**< Shifted mode AplusB for MPCP_CTRL1          */
#define MPCP_CTRL1_OP2_AminusB                (_MPCP_CTRL1_OP2_AminusB << 16)           /**< Shifted mode AminusB for MPCP_CTRL1         */
#define MPCP_CTRL1_OP2_AmulB                  (_MPCP_CTRL1_OP2_AmulB << 16)             /**< Shifted mode AmulB for MPCP_CTRL1           */
#define MPCP_CTRL1_OP2_AmulConjB              (_MPCP_CTRL1_OP2_AmulConjB << 16)         /**< Shifted mode AmulConjB for MPCP_CTRL1       */
#define MPCP_CTRL1_OP2_AdivB                  (_MPCP_CTRL1_OP2_AdivB << 16)             /**< Shifted mode AdivB for MPCP_CTRL1           */
#define MPCP_CTRL1_OP2_AmulConjA              (_MPCP_CTRL1_OP2_AmulConjA << 16)         /**< Shifted mode AmulConjA for MPCP_CTRL1       */
#define MPCP_CTRL1_OP2_BmulConjB              (_MPCP_CTRL1_OP2_BmulConjB << 16)         /**< Shifted mode BmulConjB for MPCP_CTRL1       */
#define MPCP_CTRL1_OP2_AxorB                  (_MPCP_CTRL1_OP2_AxorB << 16)             /**< Shifted mode AxorB for MPCP_CTRL1           */
#define _MPCP_CTRL1_SHIFT0_SHIFT              20                                        /**< Shift value for MPCP_SHIFT0                 */
#define _MPCP_CTRL1_SHIFT0_MASK               0x3F00000UL                               /**< Bit mask for MPCP_SHIFT0                    */
#define _MPCP_CTRL1_SHIFT0_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL1                 */
#define MPCP_CTRL1_SHIFT0_DEFAULT             (_MPCP_CTRL1_SHIFT0_DEFAULT << 20)        /**< Shifted mode DEFAULT for MPCP_CTRL1         */
#define _MPCP_CTRL1_SHIFT1_SHIFT              26                                        /**< Shift value for MPCP_SHIFT1                 */
#define _MPCP_CTRL1_SHIFT1_MASK               0xFC000000UL                              /**< Bit mask for MPCP_SHIFT1                    */
#define _MPCP_CTRL1_SHIFT1_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL1                 */
#define MPCP_CTRL1_SHIFT1_DEFAULT             (_MPCP_CTRL1_SHIFT1_DEFAULT << 26)        /**< Shifted mode DEFAULT for MPCP_CTRL1         */

/* Bit fields for MPCP CTRL2 */
#define _MPCP_CTRL2_RESETVALUE                0x00000000UL                              /**< Default value for MPCP_CTRL2                */
#define _MPCP_CTRL2_MASK                      0xFFFFFFFFUL                              /**< Mask for MPCP_CTRL2                         */
#define MPCP_CTRL2_GENIT                      (0x1UL << 0)                              /**< New BitField                                */
#define _MPCP_CTRL2_GENIT_SHIFT               0                                         /**< Shift value for MPCP_GENIT                  */
#define _MPCP_CTRL2_GENIT_MASK                0x1UL                                     /**< Bit mask for MPCP_GENIT                     */
#define _MPCP_CTRL2_GENIT_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL2                 */
#define _MPCP_CTRL2_GENIT_NO                  0x00000000UL                              /**< Mode NO for MPCP_CTRL2                      */
#define _MPCP_CTRL2_GENIT_YES                 0x00000001UL                              /**< Mode YES for MPCP_CTRL2                     */
#define MPCP_CTRL2_GENIT_DEFAULT              (_MPCP_CTRL2_GENIT_DEFAULT << 0)          /**< Shifted mode DEFAULT for MPCP_CTRL2         */
#define MPCP_CTRL2_GENIT_NO                   (_MPCP_CTRL2_GENIT_NO << 0)               /**< Shifted mode NO for MPCP_CTRL2              */
#define MPCP_CTRL2_GENIT_YES                  (_MPCP_CTRL2_GENIT_YES << 0)              /**< Shifted mode YES for MPCP_CTRL2             */
#define MPCP_CTRL2_LOOPBACK                   (0x1UL << 1)                              /**< New BitField                                */
#define _MPCP_CTRL2_LOOPBACK_SHIFT            1                                         /**< Shift value for MPCP_LOOPBACK               */
#define _MPCP_CTRL2_LOOPBACK_MASK             0x2UL                                     /**< Bit mask for MPCP_LOOPBACK                  */
#define _MPCP_CTRL2_LOOPBACK_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL2                 */
#define _MPCP_CTRL2_LOOPBACK_Disable          0x00000000UL                              /**< Mode Disable for MPCP_CTRL2                 */
#define _MPCP_CTRL2_LOOPBACK_Enable           0x00000001UL                              /**< Mode Enable for MPCP_CTRL2                  */
#define MPCP_CTRL2_LOOPBACK_DEFAULT           (_MPCP_CTRL2_LOOPBACK_DEFAULT << 1)       /**< Shifted mode DEFAULT for MPCP_CTRL2         */
#define MPCP_CTRL2_LOOPBACK_Disable           (_MPCP_CTRL2_LOOPBACK_Disable << 1)       /**< Shifted mode Disable for MPCP_CTRL2         */
#define MPCP_CTRL2_LOOPBACK_Enable            (_MPCP_CTRL2_LOOPBACK_Enable << 1)        /**< Shifted mode Enable for MPCP_CTRL2          */
#define MPCP_CTRL2_USECTEA                    (0x1UL << 2)                              /**< New BitField                                */
#define _MPCP_CTRL2_USECTEA_SHIFT             2                                         /**< Shift value for MPCP_USECTEA                */
#define _MPCP_CTRL2_USECTEA_MASK              0x4UL                                     /**< Bit mask for MPCP_USECTEA                   */
#define _MPCP_CTRL2_USECTEA_DEFAULT           0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL2                 */
#define _MPCP_CTRL2_USECTEA_NO                0x00000000UL                              /**< Mode NO for MPCP_CTRL2                      */
#define _MPCP_CTRL2_USECTEA_YES               0x00000001UL                              /**< Mode YES for MPCP_CTRL2                     */
#define MPCP_CTRL2_USECTEA_DEFAULT            (_MPCP_CTRL2_USECTEA_DEFAULT << 2)        /**< Shifted mode DEFAULT for MPCP_CTRL2         */
#define MPCP_CTRL2_USECTEA_NO                 (_MPCP_CTRL2_USECTEA_NO << 2)             /**< Shifted mode NO for MPCP_CTRL2              */
#define MPCP_CTRL2_USECTEA_YES                (_MPCP_CTRL2_USECTEA_YES << 2)            /**< Shifted mode YES for MPCP_CTRL2             */
#define MPCP_CTRL2_USECTEB                    (0x1UL << 3)                              /**< New BitField                                */
#define _MPCP_CTRL2_USECTEB_SHIFT             3                                         /**< Shift value for MPCP_USECTEB                */
#define _MPCP_CTRL2_USECTEB_MASK              0x8UL                                     /**< Bit mask for MPCP_USECTEB                   */
#define _MPCP_CTRL2_USECTEB_DEFAULT           0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL2                 */
#define _MPCP_CTRL2_USECTEB_NO                0x00000000UL                              /**< Mode NO for MPCP_CTRL2                      */
#define _MPCP_CTRL2_USECTEB_YES               0x00000001UL                              /**< Mode YES for MPCP_CTRL2                     */
#define MPCP_CTRL2_USECTEB_DEFAULT            (_MPCP_CTRL2_USECTEB_DEFAULT << 3)        /**< Shifted mode DEFAULT for MPCP_CTRL2         */
#define MPCP_CTRL2_USECTEB_NO                 (_MPCP_CTRL2_USECTEB_NO << 3)             /**< Shifted mode NO for MPCP_CTRL2              */
#define MPCP_CTRL2_USECTEB_YES                (_MPCP_CTRL2_USECTEB_YES << 3)            /**< Shifted mode YES for MPCP_CTRL2             */
#define MPCP_CTRL2_USECTEC                    (0x1UL << 4)                              /**< New BitField                                */
#define _MPCP_CTRL2_USECTEC_SHIFT             4                                         /**< Shift value for MPCP_USECTEC                */
#define _MPCP_CTRL2_USECTEC_MASK              0x10UL                                    /**< Bit mask for MPCP_USECTEC                   */
#define _MPCP_CTRL2_USECTEC_DEFAULT           0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL2                 */
#define _MPCP_CTRL2_USECTEC_NO                0x00000000UL                              /**< Mode NO for MPCP_CTRL2                      */
#define _MPCP_CTRL2_USECTEC_YES               0x00000001UL                              /**< Mode YES for MPCP_CTRL2                     */
#define MPCP_CTRL2_USECTEC_DEFAULT            (_MPCP_CTRL2_USECTEC_DEFAULT << 4)        /**< Shifted mode DEFAULT for MPCP_CTRL2         */
#define MPCP_CTRL2_USECTEC_NO                 (_MPCP_CTRL2_USECTEC_NO << 4)             /**< Shifted mode NO for MPCP_CTRL2              */
#define MPCP_CTRL2_USECTEC_YES                (_MPCP_CTRL2_USECTEC_YES << 4)            /**< Shifted mode YES for MPCP_CTRL2             */
#define MPCP_CTRL2_SUMRST                     (0x1UL << 5)                              /**< New BitField                                */
#define _MPCP_CTRL2_SUMRST_SHIFT              5                                         /**< Shift value for MPCP_SUMRST                 */
#define _MPCP_CTRL2_SUMRST_MASK               0x20UL                                    /**< Bit mask for MPCP_SUMRST                    */
#define _MPCP_CTRL2_SUMRST_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL2                 */
#define _MPCP_CTRL2_SUMRST_Disable            0x00000000UL                              /**< Mode Disable for MPCP_CTRL2                 */
#define _MPCP_CTRL2_SUMRST_Enable             0x00000001UL                              /**< Mode Enable for MPCP_CTRL2                  */
#define MPCP_CTRL2_SUMRST_DEFAULT             (_MPCP_CTRL2_SUMRST_DEFAULT << 5)         /**< Shifted mode DEFAULT for MPCP_CTRL2         */
#define MPCP_CTRL2_SUMRST_Disable             (_MPCP_CTRL2_SUMRST_Disable << 5)         /**< Shifted mode Disable for MPCP_CTRL2         */
#define MPCP_CTRL2_SUMRST_Enable              (_MPCP_CTRL2_SUMRST_Enable << 5)          /**< Shifted mode Enable for MPCP_CTRL2          */
#define MPCP_CTRL2_SUMSTORE                   (0x1UL << 6)                              /**< New BitField                                */
#define _MPCP_CTRL2_SUMSTORE_SHIFT            6                                         /**< Shift value for MPCP_SUMSTORE               */
#define _MPCP_CTRL2_SUMSTORE_MASK             0x40UL                                    /**< Bit mask for MPCP_SUMSTORE                  */
#define _MPCP_CTRL2_SUMSTORE_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL2                 */
#define _MPCP_CTRL2_SUMSTORE_No               0x00000000UL                              /**< Mode No for MPCP_CTRL2                      */
#define _MPCP_CTRL2_SUMSTORE_Yes              0x00000001UL                              /**< Mode Yes for MPCP_CTRL2                     */
#define MPCP_CTRL2_SUMSTORE_DEFAULT           (_MPCP_CTRL2_SUMSTORE_DEFAULT << 6)       /**< Shifted mode DEFAULT for MPCP_CTRL2         */
#define MPCP_CTRL2_SUMSTORE_No                (_MPCP_CTRL2_SUMSTORE_No << 6)            /**< Shifted mode No for MPCP_CTRL2              */
#define MPCP_CTRL2_SUMSTORE_Yes               (_MPCP_CTRL2_SUMSTORE_Yes << 6)           /**< Shifted mode Yes for MPCP_CTRL2             */
#define MPCP_CTRL2_USEWFORDEROT               (0x1UL << 7)                              /**< New BitField                                */
#define _MPCP_CTRL2_USEWFORDEROT_SHIFT        7                                         /**< Shift value for MPCP_USEWFORDEROT           */
#define _MPCP_CTRL2_USEWFORDEROT_MASK         0x80UL                                    /**< Bit mask for MPCP_USEWFORDEROT              */
#define _MPCP_CTRL2_USEWFORDEROT_DEFAULT      0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL2                 */
#define _MPCP_CTRL2_USEWFORDEROT_No           0x00000000UL                              /**< Mode No for MPCP_CTRL2                      */
#define _MPCP_CTRL2_USEWFORDEROT_Yes          0x00000001UL                              /**< Mode Yes for MPCP_CTRL2                     */
#define MPCP_CTRL2_USEWFORDEROT_DEFAULT       (_MPCP_CTRL2_USEWFORDEROT_DEFAULT << 7)   /**< Shifted mode DEFAULT for MPCP_CTRL2         */
#define MPCP_CTRL2_USEWFORDEROT_No            (_MPCP_CTRL2_USEWFORDEROT_No << 7)        /**< Shifted mode No for MPCP_CTRL2              */
#define MPCP_CTRL2_USEWFORDEROT_Yes           (_MPCP_CTRL2_USEWFORDEROT_Yes << 7)       /**< Shifted mode Yes for MPCP_CTRL2             */
#define _MPCP_CTRL2_NBACCU_SHIFT              8                                         /**< Shift value for MPCP_NBACCU                 */
#define _MPCP_CTRL2_NBACCU_MASK               0x1FFF00UL                                /**< Bit mask for MPCP_NBACCU                    */
#define _MPCP_CTRL2_NBACCU_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL2                 */
#define MPCP_CTRL2_NBACCU_DEFAULT             (_MPCP_CTRL2_NBACCU_DEFAULT << 8)         /**< Shifted mode DEFAULT for MPCP_CTRL2         */
#define _MPCP_CTRL2_NSTEP_SHIFT               21                                        /**< Shift value for MPCP_NSTEP                  */
#define _MPCP_CTRL2_NSTEP_MASK                0x7FE00000UL                              /**< Bit mask for MPCP_NSTEP                     */
#define _MPCP_CTRL2_NSTEP_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL2                 */
#define MPCP_CTRL2_NSTEP_DEFAULT              (_MPCP_CTRL2_NSTEP_DEFAULT << 21)         /**< Shifted mode DEFAULT for MPCP_CTRL2         */
#define MPCP_CTRL2_DEBUG                      (0x1UL << 31)                             /**< New BitField                                */
#define _MPCP_CTRL2_DEBUG_SHIFT               31                                        /**< Shift value for MPCP_DEBUG                  */
#define _MPCP_CTRL2_DEBUG_MASK                0x80000000UL                              /**< Bit mask for MPCP_DEBUG                     */
#define _MPCP_CTRL2_DEBUG_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL2                 */
#define _MPCP_CTRL2_DEBUG_NO                  0x00000000UL                              /**< Mode NO for MPCP_CTRL2                      */
#define _MPCP_CTRL2_DEBUG_YES                 0x00000001UL                              /**< Mode YES for MPCP_CTRL2                     */
#define MPCP_CTRL2_DEBUG_DEFAULT              (_MPCP_CTRL2_DEBUG_DEFAULT << 31)         /**< Shifted mode DEFAULT for MPCP_CTRL2         */
#define MPCP_CTRL2_DEBUG_NO                   (_MPCP_CTRL2_DEBUG_NO << 31)              /**< Shifted mode NO for MPCP_CTRL2              */
#define MPCP_CTRL2_DEBUG_YES                  (_MPCP_CTRL2_DEBUG_YES << 31)             /**< Shifted mode YES for MPCP_CTRL2             */

/* Bit fields for MPCP CTRL3 */
#define _MPCP_CTRL3_RESETVALUE                0x00000000UL                              /**< Default value for MPCP_CTRL3                */
#define _MPCP_CTRL3_MASK                      0xFFFFFFFFUL                              /**< Mask for MPCP_CTRL3                         */
#define _MPCP_CTRL3_F_SHIFT                   0                                         /**< Shift value for MPCP_F                      */
#define _MPCP_CTRL3_F_MASK                    0xFFFFUL                                  /**< Bit mask for MPCP_F                         */
#define _MPCP_CTRL3_F_DEFAULT                 0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL3                 */
#define MPCP_CTRL3_F_DEFAULT                  (_MPCP_CTRL3_F_DEFAULT << 0)              /**< Shifted mode DEFAULT for MPCP_CTRL3         */
#define _MPCP_CTRL3_PHI_SHIFT                 16                                        /**< Shift value for MPCP_PHI                    */
#define _MPCP_CTRL3_PHI_MASK                  0xFFFF0000UL                              /**< Bit mask for MPCP_PHI                       */
#define _MPCP_CTRL3_PHI_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL3                 */
#define MPCP_CTRL3_PHI_DEFAULT                (_MPCP_CTRL3_PHI_DEFAULT << 16)           /**< Shifted mode DEFAULT for MPCP_CTRL3         */

/* Bit fields for MPCP CTEA */
#define _MPCP_CTEA_RESETVALUE                 0x00000000UL                              /**< Default value for MPCP_CTEA                 */
#define _MPCP_CTEA_MASK                       0xFFFFFFFFUL                              /**< Mask for MPCP_CTEA                          */
#define _MPCP_CTEA_I_SHIFT                    0                                         /**< Shift value for MPCP_I                      */
#define _MPCP_CTEA_I_MASK                     0xFFFFUL                                  /**< Bit mask for MPCP_I                         */
#define _MPCP_CTEA_I_DEFAULT                  0x00000000UL                              /**< Mode DEFAULT for MPCP_CTEA                  */
#define MPCP_CTEA_I_DEFAULT                   (_MPCP_CTEA_I_DEFAULT << 0)               /**< Shifted mode DEFAULT for MPCP_CTEA          */
#define _MPCP_CTEA_Q_SHIFT                    16                                        /**< Shift value for MPCP_Q                      */
#define _MPCP_CTEA_Q_MASK                     0xFFFF0000UL                              /**< Bit mask for MPCP_Q                         */
#define _MPCP_CTEA_Q_DEFAULT                  0x00000000UL                              /**< Mode DEFAULT for MPCP_CTEA                  */
#define MPCP_CTEA_Q_DEFAULT                   (_MPCP_CTEA_Q_DEFAULT << 16)              /**< Shifted mode DEFAULT for MPCP_CTEA          */

/* Bit fields for MPCP CTEB */
#define _MPCP_CTEB_RESETVALUE                 0x00000000UL                              /**< Default value for MPCP_CTEB                 */
#define _MPCP_CTEB_MASK                       0xFFFFFFFFUL                              /**< Mask for MPCP_CTEB                          */
#define _MPCP_CTEB_I_SHIFT                    0                                         /**< Shift value for MPCP_I                      */
#define _MPCP_CTEB_I_MASK                     0xFFFFUL                                  /**< Bit mask for MPCP_I                         */
#define _MPCP_CTEB_I_DEFAULT                  0x00000000UL                              /**< Mode DEFAULT for MPCP_CTEB                  */
#define MPCP_CTEB_I_DEFAULT                   (_MPCP_CTEB_I_DEFAULT << 0)               /**< Shifted mode DEFAULT for MPCP_CTEB          */
#define _MPCP_CTEB_Q_SHIFT                    16                                        /**< Shift value for MPCP_Q                      */
#define _MPCP_CTEB_Q_MASK                     0xFFFF0000UL                              /**< Bit mask for MPCP_Q                         */
#define _MPCP_CTEB_Q_DEFAULT                  0x00000000UL                              /**< Mode DEFAULT for MPCP_CTEB                  */
#define MPCP_CTEB_Q_DEFAULT                   (_MPCP_CTEB_Q_DEFAULT << 16)              /**< Shifted mode DEFAULT for MPCP_CTEB          */

/* Bit fields for MPCP CTEC */
#define _MPCP_CTEC_RESETVALUE                 0x00000000UL                              /**< Default value for MPCP_CTEC                 */
#define _MPCP_CTEC_MASK                       0xFFFFFFFFUL                              /**< Mask for MPCP_CTEC                          */
#define _MPCP_CTEC_I_SHIFT                    0                                         /**< Shift value for MPCP_I                      */
#define _MPCP_CTEC_I_MASK                     0xFFFFUL                                  /**< Bit mask for MPCP_I                         */
#define _MPCP_CTEC_I_DEFAULT                  0x00000000UL                              /**< Mode DEFAULT for MPCP_CTEC                  */
#define MPCP_CTEC_I_DEFAULT                   (_MPCP_CTEC_I_DEFAULT << 0)               /**< Shifted mode DEFAULT for MPCP_CTEC          */
#define _MPCP_CTEC_Q_SHIFT                    16                                        /**< Shift value for MPCP_Q                      */
#define _MPCP_CTEC_Q_MASK                     0xFFFF0000UL                              /**< Bit mask for MPCP_Q                         */
#define _MPCP_CTEC_Q_DEFAULT                  0x00000000UL                              /**< Mode DEFAULT for MPCP_CTEC                  */
#define MPCP_CTEC_Q_DEFAULT                   (_MPCP_CTEC_Q_DEFAULT << 16)              /**< Shifted mode DEFAULT for MPCP_CTEC          */

/* Bit fields for MPCP BYPASS */
#define _MPCP_BYPASS_RESETVALUE               0x00000000UL                              /**< Default value for MPCP_BYPASS               */
#define _MPCP_BYPASS_MASK                     0x0000001FUL                              /**< Mask for MPCP_BYPASS                        */
#define _MPCP_BYPASS_BYPASS_SHIFT             0                                         /**< Shift value for MPCP_BYPASS                 */
#define _MPCP_BYPASS_BYPASS_MASK              0x1FUL                                    /**< Bit mask for MPCP_BYPASS                    */
#define _MPCP_BYPASS_BYPASS_DEFAULT           0x00000000UL                              /**< Mode DEFAULT for MPCP_BYPASS                */
#define MPCP_BYPASS_BYPASS_DEFAULT            (_MPCP_BYPASS_BYPASS_DEFAULT << 0)        /**< Shifted mode DEFAULT for MPCP_BYPASS        */

/* Bit fields for MPCP STAT */
#define _MPCP_STAT_RESETVALUE                 0x00000000UL                              /**< Default value for MPCP_STAT                 */
#define _MPCP_STAT_MASK                       0xFFFFFFFFUL                              /**< Mask for MPCP_STAT                          */
#define _MPCP_STAT_RESI_SHIFT                 0                                         /**< Shift value for MPCP_RESI                   */
#define _MPCP_STAT_RESI_MASK                  0xFFFFUL                                  /**< Bit mask for MPCP_RESI                      */
#define _MPCP_STAT_RESI_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for MPCP_STAT                  */
#define MPCP_STAT_RESI_DEFAULT                (_MPCP_STAT_RESI_DEFAULT << 0)            /**< Shifted mode DEFAULT for MPCP_STAT          */
#define _MPCP_STAT_RESQ_SHIFT                 16                                        /**< Shift value for MPCP_RESQ                   */
#define _MPCP_STAT_RESQ_MASK                  0xFFFF0000UL                              /**< Bit mask for MPCP_RESQ                      */
#define _MPCP_STAT_RESQ_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for MPCP_STAT                  */
#define MPCP_STAT_RESQ_DEFAULT                (_MPCP_STAT_RESQ_DEFAULT << 16)           /**< Shifted mode DEFAULT for MPCP_STAT          */

/* Bit fields for MPCP CTRL4 */
#define _MPCP_CTRL4_RESETVALUE                0x00000000UL                              /**< Default value for MPCP_CTRL4                */
#define _MPCP_CTRL4_MASK                      0xFFFFFFFFUL                              /**< Mask for MPCP_CTRL4                         */
#define _MPCP_CTRL4_OUTGAIN_SHIFT             0                                         /**< Shift value for MPCP_OUTGAIN                */
#define _MPCP_CTRL4_OUTGAIN_MASK              0x7FUL                                    /**< Bit mask for MPCP_OUTGAIN                   */
#define _MPCP_CTRL4_OUTGAIN_DEFAULT           0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL4                 */
#define MPCP_CTRL4_OUTGAIN_DEFAULT            (_MPCP_CTRL4_OUTGAIN_DEFAULT << 0)        /**< Shifted mode DEFAULT for MPCP_CTRL4         */
#define _MPCP_CTRL4_SHIFTDIVOUT_SHIFT         7                                         /**< Shift value for MPCP_SHIFTDIVOUT            */
#define _MPCP_CTRL4_SHIFTDIVOUT_MASK          0x1F80UL                                  /**< Bit mask for MPCP_SHIFTDIVOUT               */
#define _MPCP_CTRL4_SHIFTDIVOUT_DEFAULT       0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL4                 */
#define MPCP_CTRL4_SHIFTDIVOUT_DEFAULT        (_MPCP_CTRL4_SHIFTDIVOUT_DEFAULT << 7)    /**< Shifted mode DEFAULT for MPCP_CTRL4         */
#define _MPCP_CTRL4_DECIMOUT_SHIFT            13                                        /**< Shift value for MPCP_DECIMOUT               */
#define _MPCP_CTRL4_DECIMOUT_MASK             0x3FFE000UL                               /**< Bit mask for MPCP_DECIMOUT                  */
#define _MPCP_CTRL4_DECIMOUT_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL4                 */
#define MPCP_CTRL4_DECIMOUT_DEFAULT           (_MPCP_CTRL4_DECIMOUT_DEFAULT << 13)      /**< Shifted mode DEFAULT for MPCP_CTRL4         */
#define _MPCP_CTRL4_SHIFT2_SHIFT              26                                        /**< Shift value for MPCP_SHIFT2                 */
#define _MPCP_CTRL4_SHIFT2_MASK               0xFC000000UL                              /**< Bit mask for MPCP_SHIFT2                    */
#define _MPCP_CTRL4_SHIFT2_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL4                 */
#define MPCP_CTRL4_SHIFT2_DEFAULT             (_MPCP_CTRL4_SHIFT2_DEFAULT << 26)        /**< Shifted mode DEFAULT for MPCP_CTRL4         */

/* Bit fields for MPCP IF */
#define _MPCP_IF_RESETVALUE                   0x00000000UL                              /**< Default value for MPCP_IF                   */
#define _MPCP_IF_MASK                         0x00000001UL                              /**< Mask for MPCP_IF                            */
#define MPCP_IF_MPCP                          (0x1UL << 0)                              /**< MPCP Interrupt Flag                         */
#define _MPCP_IF_MPCP_SHIFT                   0                                         /**< Shift value for MPCP_MPCP                   */
#define _MPCP_IF_MPCP_MASK                    0x1UL                                     /**< Bit mask for MPCP_MPCP                      */
#define _MPCP_IF_MPCP_DEFAULT                 0x00000000UL                              /**< Mode DEFAULT for MPCP_IF                    */
#define MPCP_IF_MPCP_DEFAULT                  (_MPCP_IF_MPCP_DEFAULT << 0)              /**< Shifted mode DEFAULT for MPCP_IF            */

/* Bit fields for MPCP IEN */
#define _MPCP_IEN_RESETVALUE                  0x00000000UL                              /**< Default value for MPCP_IEN                  */
#define _MPCP_IEN_MASK                        0x00000001UL                              /**< Mask for MPCP_IEN                           */
#define MPCP_IEN_MPCP                         (0x1UL << 0)                              /**< MPCP Interrupt enable                       */
#define _MPCP_IEN_MPCP_SHIFT                  0                                         /**< Shift value for MPCP_MPCP                   */
#define _MPCP_IEN_MPCP_MASK                   0x1UL                                     /**< Bit mask for MPCP_MPCP                      */
#define _MPCP_IEN_MPCP_DEFAULT                0x00000000UL                              /**< Mode DEFAULT for MPCP_IEN                   */
#define MPCP_IEN_MPCP_DEFAULT                 (_MPCP_IEN_MPCP_DEFAULT << 0)             /**< Shifted mode DEFAULT for MPCP_IEN           */

/* Bit fields for MPCP CTRL5 */
#define _MPCP_CTRL5_RESETVALUE                0x00000000UL                              /**< Default value for MPCP_CTRL5                */
#define _MPCP_CTRL5_MASK                      0xFC000FFFUL                              /**< Mask for MPCP_CTRL5                         */
#define _MPCP_CTRL5_SEARCHMINMAX_SHIFT        0                                         /**< Shift value for MPCP_SEARCHMINMAX           */
#define _MPCP_CTRL5_SEARCHMINMAX_MASK         0x3UL                                     /**< Bit mask for MPCP_SEARCHMINMAX              */
#define _MPCP_CTRL5_SEARCHMINMAX_DEFAULT      0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL5                 */
#define _MPCP_CTRL5_SEARCHMINMAX_NO           0x00000000UL                              /**< Mode NO for MPCP_CTRL5                      */
#define _MPCP_CTRL5_SEARCHMINMAX_MIN          0x00000001UL                              /**< Mode MIN for MPCP_CTRL5                     */
#define _MPCP_CTRL5_SEARCHMINMAX_MAX          0x00000002UL                              /**< Mode MAX for MPCP_CTRL5                     */
#define MPCP_CTRL5_SEARCHMINMAX_DEFAULT       (_MPCP_CTRL5_SEARCHMINMAX_DEFAULT << 0)   /**< Shifted mode DEFAULT for MPCP_CTRL5         */
#define MPCP_CTRL5_SEARCHMINMAX_NO            (_MPCP_CTRL5_SEARCHMINMAX_NO << 0)        /**< Shifted mode NO for MPCP_CTRL5              */
#define MPCP_CTRL5_SEARCHMINMAX_MIN           (_MPCP_CTRL5_SEARCHMINMAX_MIN << 0)       /**< Shifted mode MIN for MPCP_CTRL5             */
#define MPCP_CTRL5_SEARCHMINMAX_MAX           (_MPCP_CTRL5_SEARCHMINMAX_MAX << 0)       /**< Shifted mode MAX for MPCP_CTRL5             */
#define MPCP_CTRL5_SEARCHPATH                 (0x1UL << 2)                              /**< New BitField                                */
#define _MPCP_CTRL5_SEARCHPATH_SHIFT          2                                         /**< Shift value for MPCP_SEARCHPATH             */
#define _MPCP_CTRL5_SEARCHPATH_MASK           0x4UL                                     /**< Bit mask for MPCP_SEARCHPATH                */
#define _MPCP_CTRL5_SEARCHPATH_DEFAULT        0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL5                 */
#define _MPCP_CTRL5_SEARCHPATH_IQ             0x00000000UL                              /**< Mode IQ for MPCP_CTRL5                      */
#define _MPCP_CTRL5_SEARCHPATH_ACCU           0x00000001UL                              /**< Mode ACCU for MPCP_CTRL5                    */
#define MPCP_CTRL5_SEARCHPATH_DEFAULT         (_MPCP_CTRL5_SEARCHPATH_DEFAULT << 2)     /**< Shifted mode DEFAULT for MPCP_CTRL5         */
#define MPCP_CTRL5_SEARCHPATH_IQ              (_MPCP_CTRL5_SEARCHPATH_IQ << 2)          /**< Shifted mode IQ for MPCP_CTRL5              */
#define MPCP_CTRL5_SEARCHPATH_ACCU            (_MPCP_CTRL5_SEARCHPATH_ACCU << 2)        /**< Shifted mode ACCU for MPCP_CTRL5            */
#define MPCP_CTRL5_SEARCHAFTERABS             (0x1UL << 3)                              /**< New BitField                                */
#define _MPCP_CTRL5_SEARCHAFTERABS_SHIFT      3                                         /**< Shift value for MPCP_SEARCHAFTERABS         */
#define _MPCP_CTRL5_SEARCHAFTERABS_MASK       0x8UL                                     /**< Bit mask for MPCP_SEARCHAFTERABS            */
#define _MPCP_CTRL5_SEARCHAFTERABS_DEFAULT    0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL5                 */
#define _MPCP_CTRL5_SEARCHAFTERABS_NO         0x00000000UL                              /**< Mode NO for MPCP_CTRL5                      */
#define _MPCP_CTRL5_SEARCHAFTERABS_YES        0x00000001UL                              /**< Mode YES for MPCP_CTRL5                     */
#define MPCP_CTRL5_SEARCHAFTERABS_DEFAULT     (_MPCP_CTRL5_SEARCHAFTERABS_DEFAULT << 3) /**< Shifted mode DEFAULT for MPCP_CTRL5         */
#define MPCP_CTRL5_SEARCHAFTERABS_NO          (_MPCP_CTRL5_SEARCHAFTERABS_NO << 3)      /**< Shifted mode NO for MPCP_CTRL5              */
#define MPCP_CTRL5_SEARCHAFTERABS_YES         (_MPCP_CTRL5_SEARCHAFTERABS_YES << 3)     /**< Shifted mode YES for MPCP_CTRL5             */
#define MPCP_CTRL5_SERIALOUTEN                (0x1UL << 4)                              /**< New BitField                                */
#define _MPCP_CTRL5_SERIALOUTEN_SHIFT         4                                         /**< Shift value for MPCP_SERIALOUTEN            */
#define _MPCP_CTRL5_SERIALOUTEN_MASK          0x10UL                                    /**< Bit mask for MPCP_SERIALOUTEN               */
#define _MPCP_CTRL5_SERIALOUTEN_DEFAULT       0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL5                 */
#define _MPCP_CTRL5_SERIALOUTEN_DISABLED      0x00000000UL                              /**< Mode DISABLED for MPCP_CTRL5                */
#define _MPCP_CTRL5_SERIALOUTEN_ENABLED       0x00000001UL                              /**< Mode ENABLED for MPCP_CTRL5                 */
#define MPCP_CTRL5_SERIALOUTEN_DEFAULT        (_MPCP_CTRL5_SERIALOUTEN_DEFAULT << 4)    /**< Shifted mode DEFAULT for MPCP_CTRL5         */
#define MPCP_CTRL5_SERIALOUTEN_DISABLED       (_MPCP_CTRL5_SERIALOUTEN_DISABLED << 4)   /**< Shifted mode DISABLED for MPCP_CTRL5        */
#define MPCP_CTRL5_SERIALOUTEN_ENABLED        (_MPCP_CTRL5_SERIALOUTEN_ENABLED << 4)    /**< Shifted mode ENABLED for MPCP_CTRL5         */
#define MPCP_CTRL5_USEBFORCOSIN               (0x1UL << 5)                              /**< New BitField                                */
#define _MPCP_CTRL5_USEBFORCOSIN_SHIFT        5                                         /**< Shift value for MPCP_USEBFORCOSIN           */
#define _MPCP_CTRL5_USEBFORCOSIN_MASK         0x20UL                                    /**< Bit mask for MPCP_USEBFORCOSIN              */
#define _MPCP_CTRL5_USEBFORCOSIN_DEFAULT      0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL5                 */
#define _MPCP_CTRL5_USEBFORCOSIN_NO           0x00000000UL                              /**< Mode NO for MPCP_CTRL5                      */
#define _MPCP_CTRL5_USEBFORCOSIN_YES          0x00000001UL                              /**< Mode YES for MPCP_CTRL5                     */
#define MPCP_CTRL5_USEBFORCOSIN_DEFAULT       (_MPCP_CTRL5_USEBFORCOSIN_DEFAULT << 5)   /**< Shifted mode DEFAULT for MPCP_CTRL5         */
#define MPCP_CTRL5_USEBFORCOSIN_NO            (_MPCP_CTRL5_USEBFORCOSIN_NO << 5)        /**< Shifted mode NO for MPCP_CTRL5              */
#define MPCP_CTRL5_USEBFORCOSIN_YES           (_MPCP_CTRL5_USEBFORCOSIN_YES << 5)       /**< Shifted mode YES for MPCP_CTRL5             */
#define MPCP_CTRL5_INAASINTEGER               (0x1UL << 6)                              /**< New BitField                                */
#define _MPCP_CTRL5_INAASINTEGER_SHIFT        6                                         /**< Shift value for MPCP_INAASINTEGER           */
#define _MPCP_CTRL5_INAASINTEGER_MASK         0x40UL                                    /**< Bit mask for MPCP_INAASINTEGER              */
#define _MPCP_CTRL5_INAASINTEGER_DEFAULT      0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL5                 */
#define _MPCP_CTRL5_INAASINTEGER_NO           0x00000000UL                              /**< Mode NO for MPCP_CTRL5                      */
#define _MPCP_CTRL5_INAASINTEGER_YES          0x00000001UL                              /**< Mode YES for MPCP_CTRL5                     */
#define MPCP_CTRL5_INAASINTEGER_DEFAULT       (_MPCP_CTRL5_INAASINTEGER_DEFAULT << 6)   /**< Shifted mode DEFAULT for MPCP_CTRL5         */
#define MPCP_CTRL5_INAASINTEGER_NO            (_MPCP_CTRL5_INAASINTEGER_NO << 6)        /**< Shifted mode NO for MPCP_CTRL5              */
#define MPCP_CTRL5_INAASINTEGER_YES           (_MPCP_CTRL5_INAASINTEGER_YES << 6)       /**< Shifted mode YES for MPCP_CTRL5             */
#define _MPCP_CTRL5_SHIFTINA_SHIFT            7                                         /**< Shift value for MPCP_SHIFTINA               */
#define _MPCP_CTRL5_SHIFTINA_MASK             0xF80UL                                   /**< Bit mask for MPCP_SHIFTINA                  */
#define _MPCP_CTRL5_SHIFTINA_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL5                 */
#define _MPCP_CTRL5_SHIFTINA_NO               0x00000000UL                              /**< Mode NO for MPCP_CTRL5                      */
#define _MPCP_CTRL5_SHIFTINA_YES              0x00000001UL                              /**< Mode YES for MPCP_CTRL5                     */
#define MPCP_CTRL5_SHIFTINA_DEFAULT           (_MPCP_CTRL5_SHIFTINA_DEFAULT << 7)       /**< Shifted mode DEFAULT for MPCP_CTRL5         */
#define MPCP_CTRL5_SHIFTINA_NO                (_MPCP_CTRL5_SHIFTINA_NO << 7)            /**< Shifted mode NO for MPCP_CTRL5              */
#define MPCP_CTRL5_SHIFTINA_YES               (_MPCP_CTRL5_SHIFTINA_YES << 7)           /**< Shifted mode YES for MPCP_CTRL5             */
#define _MPCP_CTRL5_SHIFT3_SHIFT              26                                        /**< Shift value for MPCP_SHIFT3                 */
#define _MPCP_CTRL5_SHIFT3_MASK               0xFC000000UL                              /**< Bit mask for MPCP_SHIFT3                    */
#define _MPCP_CTRL5_SHIFT3_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for MPCP_CTRL5                 */
#define MPCP_CTRL5_SHIFT3_DEFAULT             (_MPCP_CTRL5_SHIFT3_DEFAULT << 26)        /**< Shifted mode DEFAULT for MPCP_CTRL5         */

/* Bit fields for MPCP MINMAXI */
#define _MPCP_MINMAXI_RESETVALUE              0x00000000UL                              /**< Default value for MPCP_MINMAXI              */
#define _MPCP_MINMAXI_MASK                    0xFFFFFFFFUL                              /**< Mask for MPCP_MINMAXI                       */
#define _MPCP_MINMAXI_MINMAXI_SHIFT           0                                         /**< Shift value for MPCP_MINMAXI                */
#define _MPCP_MINMAXI_MINMAXI_MASK            0xFFFFFFFFUL                              /**< Bit mask for MPCP_MINMAXI                   */
#define _MPCP_MINMAXI_MINMAXI_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for MPCP_MINMAXI               */
#define MPCP_MINMAXI_MINMAXI_DEFAULT          (_MPCP_MINMAXI_MINMAXI_DEFAULT << 0)      /**< Shifted mode DEFAULT for MPCP_MINMAXI       */

/* Bit fields for MPCP MINMAXQ */
#define _MPCP_MINMAXQ_RESETVALUE              0x00000000UL                              /**< Default value for MPCP_MINMAXQ              */
#define _MPCP_MINMAXQ_MASK                    0xFFFFFF00UL                              /**< Mask for MPCP_MINMAXQ                       */
#define _MPCP_MINMAXQ_MINMAXQ_SHIFT           8                                         /**< Shift value for MPCP_MINMAXQ                */
#define _MPCP_MINMAXQ_MINMAXQ_MASK            0xFFFFFF00UL                              /**< Bit mask for MPCP_MINMAXQ                   */
#define _MPCP_MINMAXQ_MINMAXQ_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for MPCP_MINMAXQ               */
#define MPCP_MINMAXQ_MINMAXQ_DEFAULT          (_MPCP_MINMAXQ_MINMAXQ_DEFAULT << 8)      /**< Shifted mode DEFAULT for MPCP_MINMAXQ       */

/* Bit fields for MPCP MINMAXIDX */
#define _MPCP_MINMAXIDX_RESETVALUE            0x00000000UL                               /**< Default value for MPCP_MINMAXIDX            */
#define _MPCP_MINMAXIDX_MASK                  0xFFFFFFFFUL                               /**< Mask for MPCP_MINMAXIDX                     */
#define _MPCP_MINMAXIDX_MINMAXIDXI_SHIFT      0                                          /**< Shift value for MPCP_MINMAXIDXI             */
#define _MPCP_MINMAXIDX_MINMAXIDXI_MASK       0xFFFFUL                                   /**< Bit mask for MPCP_MINMAXIDXI                */
#define _MPCP_MINMAXIDX_MINMAXIDXI_DEFAULT    0x00000000UL                               /**< Mode DEFAULT for MPCP_MINMAXIDX             */
#define MPCP_MINMAXIDX_MINMAXIDXI_DEFAULT     (_MPCP_MINMAXIDX_MINMAXIDXI_DEFAULT << 0)  /**< Shifted mode DEFAULT for MPCP_MINMAXIDX     */
#define _MPCP_MINMAXIDX_MINMAXIDXQ_SHIFT      16                                         /**< Shift value for MPCP_MINMAXIDXQ             */
#define _MPCP_MINMAXIDX_MINMAXIDXQ_MASK       0xFFFF0000UL                               /**< Bit mask for MPCP_MINMAXIDXQ                */
#define _MPCP_MINMAXIDX_MINMAXIDXQ_DEFAULT    0x00000000UL                               /**< Mode DEFAULT for MPCP_MINMAXIDX             */
#define MPCP_MINMAXIDX_MINMAXIDXQ_DEFAULT     (_MPCP_MINMAXIDX_MINMAXIDXQ_DEFAULT << 16) /**< Shifted mode DEFAULT for MPCP_MINMAXIDX     */

/** @} End of group EFR32FG25_MPCP_BitFields */
/** @} End of group EFR32FG25_MPCP */
/** @} End of group Parts */

#endif /* EFR32FG25_MPCP_H */
