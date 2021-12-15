/**************************************************************************//**
 * @file
 * @brief EFR32FG25 VEQ register and bit field definitions
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
#ifndef EFR32FG25_VEQ_H
#define EFR32FG25_VEQ_H
#define VEQ_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_VEQ VEQ
 * @{
 * @brief EFR32FG25 VEQ Register Declaration.
 *****************************************************************************/

/** VEQ Register Declaration. */
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
  uint32_t       RESERVED3[1U];                 /**< Reserved for future use                            */
  uint32_t       RESERVED4[7U];                 /**< Reserved for future use                            */
  __IOM uint32_t FMTOUT;                        /**< New Register                                       */
  uint32_t       RESERVED5[79U];                /**< Reserved for future use                            */
  __IOM uint32_t CFG;                           /**< VEQ Configuration                                  */
  uint32_t       RESERVED6[3U];                 /**< Reserved for future use                            */
  __IM uint32_t  STAT;                          /**< VEQ Status                                         */
  uint32_t       RESERVED7[3U];                 /**< Reserved for future use                            */
  __IOM uint32_t CTRL;                          /**< VEQ Control                                        */
  uint32_t       RESERVED8[887U];               /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_SET;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_SET;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_SET;                   /**< New Register                                       */
  __IOM uint32_t DISCLK_SET;                    /**< Disable Clocks                                     */
  uint32_t       RESERVED9[3U];                 /**< Reserved for future use                            */
  __IOM uint32_t FIFOIN_SET;                    /**< New Register                                       */
  uint32_t       RESERVED10[7U];                /**< Reserved for future use                            */
  __IM uint32_t  FIFOOUT_SET;                   /**< New Register                                       */
  uint32_t       RESERVED11[23U];               /**< Reserved for future use                            */
  uint32_t       RESERVED12[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED13[7U];                /**< Reserved for future use                            */
  __IOM uint32_t FMTOUT_SET;                    /**< New Register                                       */
  uint32_t       RESERVED14[79U];               /**< Reserved for future use                            */
  __IOM uint32_t CFG_SET;                       /**< VEQ Configuration                                  */
  uint32_t       RESERVED15[3U];                /**< Reserved for future use                            */
  __IM uint32_t  STAT_SET;                      /**< VEQ Status                                         */
  uint32_t       RESERVED16[3U];                /**< Reserved for future use                            */
  __IOM uint32_t CTRL_SET;                      /**< VEQ Control                                        */
  uint32_t       RESERVED17[887U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_CLR;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_CLR;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_CLR;                   /**< New Register                                       */
  __IOM uint32_t DISCLK_CLR;                    /**< Disable Clocks                                     */
  uint32_t       RESERVED18[3U];                /**< Reserved for future use                            */
  __IOM uint32_t FIFOIN_CLR;                    /**< New Register                                       */
  uint32_t       RESERVED19[7U];                /**< Reserved for future use                            */
  __IM uint32_t  FIFOOUT_CLR;                   /**< New Register                                       */
  uint32_t       RESERVED20[23U];               /**< Reserved for future use                            */
  uint32_t       RESERVED21[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED22[7U];                /**< Reserved for future use                            */
  __IOM uint32_t FMTOUT_CLR;                    /**< New Register                                       */
  uint32_t       RESERVED23[79U];               /**< Reserved for future use                            */
  __IOM uint32_t CFG_CLR;                       /**< VEQ Configuration                                  */
  uint32_t       RESERVED24[3U];                /**< Reserved for future use                            */
  __IM uint32_t  STAT_CLR;                      /**< VEQ Status                                         */
  uint32_t       RESERVED25[3U];                /**< Reserved for future use                            */
  __IOM uint32_t CTRL_CLR;                      /**< VEQ Control                                        */
  uint32_t       RESERVED26[887U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_TGL;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_TGL;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_TGL;                   /**< New Register                                       */
  __IOM uint32_t DISCLK_TGL;                    /**< Disable Clocks                                     */
  uint32_t       RESERVED27[3U];                /**< Reserved for future use                            */
  __IOM uint32_t FIFOIN_TGL;                    /**< New Register                                       */
  uint32_t       RESERVED28[7U];                /**< Reserved for future use                            */
  __IM uint32_t  FIFOOUT_TGL;                   /**< New Register                                       */
  uint32_t       RESERVED29[23U];               /**< Reserved for future use                            */
  uint32_t       RESERVED30[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED31[7U];                /**< Reserved for future use                            */
  __IOM uint32_t FMTOUT_TGL;                    /**< New Register                                       */
  uint32_t       RESERVED32[79U];               /**< Reserved for future use                            */
  __IOM uint32_t CFG_TGL;                       /**< VEQ Configuration                                  */
  uint32_t       RESERVED33[3U];                /**< Reserved for future use                            */
  __IM uint32_t  STAT_TGL;                      /**< VEQ Status                                         */
  uint32_t       RESERVED34[3U];                /**< Reserved for future use                            */
  __IOM uint32_t CTRL_TGL;                      /**< VEQ Control                                        */
} VEQ_TypeDef;
/** @} End of group EFR32FG25_VEQ */

/**************************************************************************//**
 * @addtogroup EFR32FG25_VEQ
 * @{
 * @defgroup EFR32FG25_VEQ_BitFields VEQ Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for VEQ IPVERSION */
#define _VEQ_IPVERSION_RESETVALUE           0x00000001UL                                /**< Default value for VEQ_IPVERSION             */
#define _VEQ_IPVERSION_MASK                 0xFFFFFFFFUL                                /**< Mask for VEQ_IPVERSION                      */
#define _VEQ_IPVERSION_IPVERSION_SHIFT      0                                           /**< Shift value for VEQ_IPVERSION               */
#define _VEQ_IPVERSION_IPVERSION_MASK       0xFFFFFFFFUL                                /**< Bit mask for VEQ_IPVERSION                  */
#define _VEQ_IPVERSION_IPVERSION_DEFAULT    0x00000001UL                                /**< Mode DEFAULT for VEQ_IPVERSION              */
#define VEQ_IPVERSION_IPVERSION_DEFAULT     (_VEQ_IPVERSION_IPVERSION_DEFAULT << 0)     /**< Shifted mode DEFAULT for VEQ_IPVERSION      */

/* Bit fields for VEQ EN */
#define _VEQ_EN_RESETVALUE                  0x00000000UL                                /**< Default value for VEQ_EN                    */
#define _VEQ_EN_MASK                        0x00000003UL                                /**< Mask for VEQ_EN                             */
#define VEQ_EN_EN                           (0x1UL << 0)                                /**< Module Enable                               */
#define _VEQ_EN_EN_SHIFT                    0                                           /**< Shift value for VEQ_EN                      */
#define _VEQ_EN_EN_MASK                     0x1UL                                       /**< Bit mask for VEQ_EN                         */
#define _VEQ_EN_EN_DEFAULT                  0x00000000UL                                /**< Mode DEFAULT for VEQ_EN                     */
#define VEQ_EN_EN_DEFAULT                   (_VEQ_EN_EN_DEFAULT << 0)                   /**< Shifted mode DEFAULT for VEQ_EN             */
#define VEQ_EN_DISABLING                    (0x1UL << 1)                                /**< Disablement Busy Status                     */
#define _VEQ_EN_DISABLING_SHIFT             1                                           /**< Shift value for VEQ_DISABLING               */
#define _VEQ_EN_DISABLING_MASK              0x2UL                                       /**< Bit mask for VEQ_DISABLING                  */
#define _VEQ_EN_DISABLING_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for VEQ_EN                     */
#define VEQ_EN_DISABLING_DEFAULT            (_VEQ_EN_DISABLING_DEFAULT << 1)            /**< Shifted mode DEFAULT for VEQ_EN             */

/* Bit fields for VEQ SWRST */
#define _VEQ_SWRST_RESETVALUE               0x00000000UL                                /**< Default value for VEQ_SWRST                 */
#define _VEQ_SWRST_MASK                     0x00000003UL                                /**< Mask for VEQ_SWRST                          */
#define VEQ_SWRST_SWRST                     (0x1UL << 0)                                /**< Software Reset Command                      */
#define _VEQ_SWRST_SWRST_SHIFT              0                                           /**< Shift value for VEQ_SWRST                   */
#define _VEQ_SWRST_SWRST_MASK               0x1UL                                       /**< Bit mask for VEQ_SWRST                      */
#define _VEQ_SWRST_SWRST_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for VEQ_SWRST                  */
#define VEQ_SWRST_SWRST_DEFAULT             (_VEQ_SWRST_SWRST_DEFAULT << 0)             /**< Shifted mode DEFAULT for VEQ_SWRST          */
#define VEQ_SWRST_RESETTING                 (0x1UL << 1)                                /**< Software Reset Busy Status                  */
#define _VEQ_SWRST_RESETTING_SHIFT          1                                           /**< Shift value for VEQ_RESETTING               */
#define _VEQ_SWRST_RESETTING_MASK           0x2UL                                       /**< Bit mask for VEQ_RESETTING                  */
#define _VEQ_SWRST_RESETTING_DEFAULT        0x00000000UL                                /**< Mode DEFAULT for VEQ_SWRST                  */
#define VEQ_SWRST_RESETTING_DEFAULT         (_VEQ_SWRST_RESETTING_DEFAULT << 1)         /**< Shifted mode DEFAULT for VEQ_SWRST          */

/* Bit fields for VEQ CONNECT */
#define _VEQ_CONNECT_RESETVALUE             0x00000000UL                                /**< Default value for VEQ_CONNECT               */
#define _VEQ_CONNECT_MASK                   0x00000101UL                                /**< Mask for VEQ_CONNECT                        */
#define VEQ_CONNECT_IN                      (0x1UL << 0)                                /**< Input FIFO connect                          */
#define _VEQ_CONNECT_IN_SHIFT               0                                           /**< Shift value for VEQ_IN                      */
#define _VEQ_CONNECT_IN_MASK                0x1UL                                       /**< Bit mask for VEQ_IN                         */
#define _VEQ_CONNECT_IN_DEFAULT             0x00000000UL                                /**< Mode DEFAULT for VEQ_CONNECT                */
#define VEQ_CONNECT_IN_DEFAULT              (_VEQ_CONNECT_IN_DEFAULT << 0)              /**< Shifted mode DEFAULT for VEQ_CONNECT        */
#define VEQ_CONNECT_OUT                     (0x1UL << 8)                                /**< Output FIFO connect                         */
#define _VEQ_CONNECT_OUT_SHIFT              8                                           /**< Shift value for VEQ_OUT                     */
#define _VEQ_CONNECT_OUT_MASK               0x100UL                                     /**< Bit mask for VEQ_OUT                        */
#define _VEQ_CONNECT_OUT_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for VEQ_CONNECT                */
#define VEQ_CONNECT_OUT_DEFAULT             (_VEQ_CONNECT_OUT_DEFAULT << 8)             /**< Shifted mode DEFAULT for VEQ_CONNECT        */

/* Bit fields for VEQ DISCLK */
#define _VEQ_DISCLK_RESETVALUE              0x00000002UL                                /**< Default value for VEQ_DISCLK                */
#define _VEQ_DISCLK_MASK                    0x00000003UL                                /**< Mask for VEQ_DISCLK                         */
#define _VEQ_DISCLK_DISCLK_SHIFT            0                                           /**< Shift value for VEQ_DISCLK                  */
#define _VEQ_DISCLK_DISCLK_MASK             0x3UL                                       /**< Bit mask for VEQ_DISCLK                     */
#define _VEQ_DISCLK_DISCLK_DEFAULT          0x00000002UL                                /**< Mode DEFAULT for VEQ_DISCLK                 */
#define _VEQ_DISCLK_DISCLK_NONE             0x00000000UL                                /**< Mode NONE for VEQ_DISCLK                    */
#define _VEQ_DISCLK_DISCLK_ALL              0x00000001UL                                /**< Mode ALL for VEQ_DISCLK                     */
#define _VEQ_DISCLK_DISCLK_AUTO             0x00000002UL                                /**< Mode AUTO for VEQ_DISCLK                    */
#define VEQ_DISCLK_DISCLK_DEFAULT           (_VEQ_DISCLK_DISCLK_DEFAULT << 0)           /**< Shifted mode DEFAULT for VEQ_DISCLK         */
#define VEQ_DISCLK_DISCLK_NONE              (_VEQ_DISCLK_DISCLK_NONE << 0)              /**< Shifted mode NONE for VEQ_DISCLK            */
#define VEQ_DISCLK_DISCLK_ALL               (_VEQ_DISCLK_DISCLK_ALL << 0)               /**< Shifted mode ALL for VEQ_DISCLK             */
#define VEQ_DISCLK_DISCLK_AUTO              (_VEQ_DISCLK_DISCLK_AUTO << 0)              /**< Shifted mode AUTO for VEQ_DISCLK            */

/* Bit fields for VEQ FIFOIN */
#define _VEQ_FIFOIN_RESETVALUE              0x00000000UL                                /**< Default value for VEQ_FIFOIN                */
#define _VEQ_FIFOIN_MASK                    0x1F033F0FUL                                /**< Mask for VEQ_FIFOIN                         */
#define _VEQ_FIFOIN_FID_SHIFT               0                                           /**< Shift value for VEQ_FID                     */
#define _VEQ_FIFOIN_FID_MASK                0xFUL                                       /**< Bit mask for VEQ_FID                        */
#define _VEQ_FIFOIN_FID_DEFAULT             0x00000000UL                                /**< Mode DEFAULT for VEQ_FIFOIN                 */
#define VEQ_FIFOIN_FID_DEFAULT              (_VEQ_FIFOIN_FID_DEFAULT << 0)              /**< Shifted mode DEFAULT for VEQ_FIFOIN         */
#define _VEQ_FIFOIN_CID_SHIFT               8                                           /**< Shift value for VEQ_CID                     */
#define _VEQ_FIFOIN_CID_MASK                0x3F00UL                                    /**< Bit mask for VEQ_CID                        */
#define _VEQ_FIFOIN_CID_DEFAULT             0x00000000UL                                /**< Mode DEFAULT for VEQ_FIFOIN                 */
#define VEQ_FIFOIN_CID_DEFAULT              (_VEQ_FIFOIN_CID_DEFAULT << 8)              /**< Shifted mode DEFAULT for VEQ_FIFOIN         */
#define _VEQ_FIFOIN_REM_SHIFT               16                                          /**< Shift value for VEQ_REM                     */
#define _VEQ_FIFOIN_REM_MASK                0x30000UL                                   /**< Bit mask for VEQ_REM                        */
#define _VEQ_FIFOIN_REM_DEFAULT             0x00000000UL                                /**< Mode DEFAULT for VEQ_FIFOIN                 */
#define VEQ_FIFOIN_REM_DEFAULT              (_VEQ_FIFOIN_REM_DEFAULT << 16)             /**< Shifted mode DEFAULT for VEQ_FIFOIN         */
#define _VEQ_FIFOIN_ALARM_SHIFT             24                                          /**< Shift value for VEQ_ALARM                   */
#define _VEQ_FIFOIN_ALARM_MASK              0x1F000000UL                                /**< Bit mask for VEQ_ALARM                      */
#define _VEQ_FIFOIN_ALARM_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for VEQ_FIFOIN                 */
#define VEQ_FIFOIN_ALARM_DEFAULT            (_VEQ_FIFOIN_ALARM_DEFAULT << 24)           /**< Shifted mode DEFAULT for VEQ_FIFOIN         */

/* Bit fields for VEQ FIFOOUT */
#define _VEQ_FIFOOUT_RESETVALUE             0x00000000UL                                /**< Default value for VEQ_FIFOOUT               */
#define _VEQ_FIFOOUT_MASK                   0x1F030000UL                                /**< Mask for VEQ_FIFOOUT                        */
#define _VEQ_FIFOOUT_CNT_SHIFT              16                                          /**< Shift value for VEQ_CNT                     */
#define _VEQ_FIFOOUT_CNT_MASK               0x30000UL                                   /**< Bit mask for VEQ_CNT                        */
#define _VEQ_FIFOOUT_CNT_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for VEQ_FIFOOUT                */
#define VEQ_FIFOOUT_CNT_DEFAULT             (_VEQ_FIFOOUT_CNT_DEFAULT << 16)            /**< Shifted mode DEFAULT for VEQ_FIFOOUT        */
#define _VEQ_FIFOOUT_ALARM_SHIFT            24                                          /**< Shift value for VEQ_ALARM                   */
#define _VEQ_FIFOOUT_ALARM_MASK             0x1F000000UL                                /**< Bit mask for VEQ_ALARM                      */
#define _VEQ_FIFOOUT_ALARM_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for VEQ_FIFOOUT                */
#define VEQ_FIFOOUT_ALARM_DEFAULT           (_VEQ_FIFOOUT_ALARM_DEFAULT << 24)          /**< Shifted mode DEFAULT for VEQ_FIFOOUT        */

/* Bit fields for VEQ FMTOUT */
#define _VEQ_FMTOUT_RESETVALUE              0x00000000UL                                /**< Default value for VEQ_FMTOUT                */
#define _VEQ_FMTOUT_MASK                    0x0000001FUL                                /**< Mask for VEQ_FMTOUT                         */
#define _VEQ_FMTOUT_ELEMSIZE_SHIFT          0                                           /**< Shift value for VEQ_ELEMSIZE                */
#define _VEQ_FMTOUT_ELEMSIZE_MASK           0x1FUL                                      /**< Bit mask for VEQ_ELEMSIZE                   */
#define _VEQ_FMTOUT_ELEMSIZE_DEFAULT        0x00000000UL                                /**< Mode DEFAULT for VEQ_FMTOUT                 */
#define VEQ_FMTOUT_ELEMSIZE_DEFAULT         (_VEQ_FMTOUT_ELEMSIZE_DEFAULT << 0)         /**< Shifted mode DEFAULT for VEQ_FMTOUT         */

/* Bit fields for VEQ CFG */
#define _VEQ_CFG_RESETVALUE                 0x00203040UL                                /**< Default value for VEQ_CFG                   */
#define _VEQ_CFG_MASK                       0x877F7F7FUL                                /**< Mask for VEQ_CFG                            */
#define _VEQ_CFG_VITERBIKSI1_SHIFT          0                                           /**< Shift value for VEQ_VITERBIKSI1             */
#define _VEQ_CFG_VITERBIKSI1_MASK           0x7FUL                                      /**< Bit mask for VEQ_VITERBIKSI1                */
#define _VEQ_CFG_VITERBIKSI1_DEFAULT        0x00000040UL                                /**< Mode DEFAULT for VEQ_CFG                    */
#define VEQ_CFG_VITERBIKSI1_DEFAULT         (_VEQ_CFG_VITERBIKSI1_DEFAULT << 0)         /**< Shifted mode DEFAULT for VEQ_CFG            */
#define _VEQ_CFG_VITERBIKSI2_SHIFT          8                                           /**< Shift value for VEQ_VITERBIKSI2             */
#define _VEQ_CFG_VITERBIKSI2_MASK           0x7F00UL                                    /**< Bit mask for VEQ_VITERBIKSI2                */
#define _VEQ_CFG_VITERBIKSI2_DEFAULT        0x00000030UL                                /**< Mode DEFAULT for VEQ_CFG                    */
#define VEQ_CFG_VITERBIKSI2_DEFAULT         (_VEQ_CFG_VITERBIKSI2_DEFAULT << 8)         /**< Shifted mode DEFAULT for VEQ_CFG            */
#define _VEQ_CFG_VITERBIKSI3_SHIFT          16                                          /**< Shift value for VEQ_VITERBIKSI3             */
#define _VEQ_CFG_VITERBIKSI3_MASK           0x7F0000UL                                  /**< Bit mask for VEQ_VITERBIKSI3                */
#define _VEQ_CFG_VITERBIKSI3_DEFAULT        0x00000020UL                                /**< Mode DEFAULT for VEQ_CFG                    */
#define VEQ_CFG_VITERBIKSI3_DEFAULT         (_VEQ_CFG_VITERBIKSI3_DEFAULT << 16)        /**< Shifted mode DEFAULT for VEQ_CFG            */
#define _VEQ_CFG_SDSCALE_SHIFT              24                                          /**< Shift value for VEQ_SDSCALE                 */
#define _VEQ_CFG_SDSCALE_MASK               0x7000000UL                                 /**< Bit mask for VEQ_SDSCALE                    */
#define _VEQ_CFG_SDSCALE_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for VEQ_CFG                    */
#define VEQ_CFG_SDSCALE_DEFAULT             (_VEQ_CFG_SDSCALE_DEFAULT << 24)            /**< Shifted mode DEFAULT for VEQ_CFG            */
#define VEQ_CFG_SOFTD                       (0x1UL << 31)                               /**< SOFT DECISION                               */
#define _VEQ_CFG_SOFTD_SHIFT                31                                          /**< Shift value for VEQ_SOFTD                   */
#define _VEQ_CFG_SOFTD_MASK                 0x80000000UL                                /**< Bit mask for VEQ_SOFTD                      */
#define _VEQ_CFG_SOFTD_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for VEQ_CFG                    */
#define VEQ_CFG_SOFTD_DEFAULT               (_VEQ_CFG_SOFTD_DEFAULT << 31)              /**< Shifted mode DEFAULT for VEQ_CFG            */

/* Bit fields for VEQ STAT */
#define _VEQ_STAT_RESETVALUE                0x00000000UL                                /**< Default value for VEQ_STAT                  */
#define _VEQ_STAT_MASK                      0x00000001UL                                /**< Mask for VEQ_STAT                           */
#define VEQ_STAT_INITDONE                   (0x1UL << 0)                                /**< Initialization Done                         */
#define _VEQ_STAT_INITDONE_SHIFT            0                                           /**< Shift value for VEQ_INITDONE                */
#define _VEQ_STAT_INITDONE_MASK             0x1UL                                       /**< Bit mask for VEQ_INITDONE                   */
#define _VEQ_STAT_INITDONE_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for VEQ_STAT                   */
#define VEQ_STAT_INITDONE_DEFAULT           (_VEQ_STAT_INITDONE_DEFAULT << 0)           /**< Shifted mode DEFAULT for VEQ_STAT           */

/* Bit fields for VEQ CTRL */
#define _VEQ_CTRL_RESETVALUE                0x00000000UL                                /**< Default value for VEQ_CTRL                  */
#define _VEQ_CTRL_MASK                      0x0000FFFFUL                                /**< Mask for VEQ_CTRL                           */
#define _VEQ_CTRL_FRAMECNT_SHIFT            0                                           /**< Shift value for VEQ_FRAMECNT                */
#define _VEQ_CTRL_FRAMECNT_MASK             0xFFFFUL                                    /**< Bit mask for VEQ_FRAMECNT                   */
#define _VEQ_CTRL_FRAMECNT_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for VEQ_CTRL                   */
#define VEQ_CTRL_FRAMECNT_DEFAULT           (_VEQ_CTRL_FRAMECNT_DEFAULT << 0)           /**< Shifted mode DEFAULT for VEQ_CTRL           */

/** @} End of group EFR32FG25_VEQ_BitFields */
/** @} End of group EFR32FG25_VEQ */
/** @} End of group Parts */

#endif /* EFR32FG25_VEQ_H */
