/**************************************************************************//**
 * @file
 * @brief EFR32FG25 FILT register and bit field definitions
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
#ifndef EFR32FG25_FILT_H
#define EFR32FG25_FILT_H
#define FILT_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_FILT FILT
 * @{
 * @brief EFR32FG25 FILT Register Declaration.
 *****************************************************************************/

/** FILT FIR Register Group Declaration. */
typedef struct {
  __IOM uint32_t COEFF;                              /**< FIlter Cooefficient Value                          */
} FILT_FIR_TypeDef;

/** FILT Register Declaration. */
typedef struct {
  __IM uint32_t    IPVERSION;                   /**< IP Version ID                                      */
  __IOM uint32_t   EN;                          /**< Module Enable                                      */
  __IOM uint32_t   SWRST;                       /**< Software Reset                                     */
  __IOM uint32_t   CONNECT;                     /**< New Register                                       */
  __IOM uint32_t   DISCLK;                      /**< Disable Clocks                                     */
  uint32_t         RESERVED0[3U];               /**< Reserved for future use                            */
  __IOM uint32_t   FIFOIN;                      /**< New Register                                       */
  uint32_t         RESERVED1[7U];               /**< Reserved for future use                            */
  __IM uint32_t    FIFOOUT;                     /**< New Register                                       */
  uint32_t         RESERVED2[23U];              /**< Reserved for future use                            */
  uint32_t         RESERVED3[1U];               /**< Reserved for future use                            */
  uint32_t         RESERVED4[7U];               /**< Reserved for future use                            */
  __IOM uint32_t   FMTOUT;                      /**< New Register                                       */
  uint32_t         RESERVED5[79U];              /**< Reserved for future use                            */
  __IOM uint32_t   CFG;                         /**< Filter Config Register                             */
  __IOM uint32_t   CTRL;                        /**< Filter Control Register                            */
  __IOM uint32_t   NUMSKIP;                     /**< Number of Output Samples to Skip                   */
  uint32_t         RESERVED6[13U];              /**< Reserved for future use                            */
  FILT_FIR_TypeDef FIR[16U];                    /**<                                                    */
  uint32_t         RESERVED7[864U];             /**< Reserved for future use                            */
  __IM uint32_t    IPVERSION_SET;               /**< IP Version ID                                      */
  __IOM uint32_t   EN_SET;                      /**< Module Enable                                      */
  __IOM uint32_t   SWRST_SET;                   /**< Software Reset                                     */
  __IOM uint32_t   CONNECT_SET;                 /**< New Register                                       */
  __IOM uint32_t   DISCLK_SET;                  /**< Disable Clocks                                     */
  uint32_t         RESERVED8[3U];               /**< Reserved for future use                            */
  __IOM uint32_t   FIFOIN_SET;                  /**< New Register                                       */
  uint32_t         RESERVED9[7U];               /**< Reserved for future use                            */
  __IM uint32_t    FIFOOUT_SET;                 /**< New Register                                       */
  uint32_t         RESERVED10[23U];             /**< Reserved for future use                            */
  uint32_t         RESERVED11[1U];              /**< Reserved for future use                            */
  uint32_t         RESERVED12[7U];              /**< Reserved for future use                            */
  __IOM uint32_t   FMTOUT_SET;                  /**< New Register                                       */
  uint32_t         RESERVED13[79U];             /**< Reserved for future use                            */
  __IOM uint32_t   CFG_SET;                     /**< Filter Config Register                             */
  __IOM uint32_t   CTRL_SET;                    /**< Filter Control Register                            */
  __IOM uint32_t   NUMSKIP_SET;                 /**< Number of Output Samples to Skip                   */
  uint32_t         RESERVED14[13U];             /**< Reserved for future use                            */
  FILT_FIR_TypeDef FIR_SET[16U];                /**<                                                    */
  uint32_t         RESERVED15[864U];            /**< Reserved for future use                            */
  __IM uint32_t    IPVERSION_CLR;               /**< IP Version ID                                      */
  __IOM uint32_t   EN_CLR;                      /**< Module Enable                                      */
  __IOM uint32_t   SWRST_CLR;                   /**< Software Reset                                     */
  __IOM uint32_t   CONNECT_CLR;                 /**< New Register                                       */
  __IOM uint32_t   DISCLK_CLR;                  /**< Disable Clocks                                     */
  uint32_t         RESERVED16[3U];              /**< Reserved for future use                            */
  __IOM uint32_t   FIFOIN_CLR;                  /**< New Register                                       */
  uint32_t         RESERVED17[7U];              /**< Reserved for future use                            */
  __IM uint32_t    FIFOOUT_CLR;                 /**< New Register                                       */
  uint32_t         RESERVED18[23U];             /**< Reserved for future use                            */
  uint32_t         RESERVED19[1U];              /**< Reserved for future use                            */
  uint32_t         RESERVED20[7U];              /**< Reserved for future use                            */
  __IOM uint32_t   FMTOUT_CLR;                  /**< New Register                                       */
  uint32_t         RESERVED21[79U];             /**< Reserved for future use                            */
  __IOM uint32_t   CFG_CLR;                     /**< Filter Config Register                             */
  __IOM uint32_t   CTRL_CLR;                    /**< Filter Control Register                            */
  __IOM uint32_t   NUMSKIP_CLR;                 /**< Number of Output Samples to Skip                   */
  uint32_t         RESERVED22[13U];             /**< Reserved for future use                            */
  FILT_FIR_TypeDef FIR_CLR[16U];                /**<                                                    */
  uint32_t         RESERVED23[864U];            /**< Reserved for future use                            */
  __IM uint32_t    IPVERSION_TGL;               /**< IP Version ID                                      */
  __IOM uint32_t   EN_TGL;                      /**< Module Enable                                      */
  __IOM uint32_t   SWRST_TGL;                   /**< Software Reset                                     */
  __IOM uint32_t   CONNECT_TGL;                 /**< New Register                                       */
  __IOM uint32_t   DISCLK_TGL;                  /**< Disable Clocks                                     */
  uint32_t         RESERVED24[3U];              /**< Reserved for future use                            */
  __IOM uint32_t   FIFOIN_TGL;                  /**< New Register                                       */
  uint32_t         RESERVED25[7U];              /**< Reserved for future use                            */
  __IM uint32_t    FIFOOUT_TGL;                 /**< New Register                                       */
  uint32_t         RESERVED26[23U];             /**< Reserved for future use                            */
  uint32_t         RESERVED27[1U];              /**< Reserved for future use                            */
  uint32_t         RESERVED28[7U];              /**< Reserved for future use                            */
  __IOM uint32_t   FMTOUT_TGL;                  /**< New Register                                       */
  uint32_t         RESERVED29[79U];             /**< Reserved for future use                            */
  __IOM uint32_t   CFG_TGL;                     /**< Filter Config Register                             */
  __IOM uint32_t   CTRL_TGL;                    /**< Filter Control Register                            */
  __IOM uint32_t   NUMSKIP_TGL;                 /**< Number of Output Samples to Skip                   */
  uint32_t         RESERVED30[13U];             /**< Reserved for future use                            */
  FILT_FIR_TypeDef FIR_TGL[16U];                /**<                                                    */
} FILT_TypeDef;
/** @} End of group EFR32FG25_FILT */

/**************************************************************************//**
 * @addtogroup EFR32FG25_FILT
 * @{
 * @defgroup EFR32FG25_FILT_BitFields FILT Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for FILT IPVERSION */
#define _FILT_IPVERSION_RESETVALUE           0x00000001UL                               /**< Default value for FILT_IPVERSION            */
#define _FILT_IPVERSION_MASK                 0xFFFFFFFFUL                               /**< Mask for FILT_IPVERSION                     */
#define _FILT_IPVERSION_IPVERSION_SHIFT      0                                          /**< Shift value for FILT_IPVERSION              */
#define _FILT_IPVERSION_IPVERSION_MASK       0xFFFFFFFFUL                               /**< Bit mask for FILT_IPVERSION                 */
#define _FILT_IPVERSION_IPVERSION_DEFAULT    0x00000001UL                               /**< Mode DEFAULT for FILT_IPVERSION             */
#define FILT_IPVERSION_IPVERSION_DEFAULT     (_FILT_IPVERSION_IPVERSION_DEFAULT << 0)   /**< Shifted mode DEFAULT for FILT_IPVERSION     */

/* Bit fields for FILT EN */
#define _FILT_EN_RESETVALUE                  0x00000000UL                               /**< Default value for FILT_EN                   */
#define _FILT_EN_MASK                        0x00000003UL                               /**< Mask for FILT_EN                            */
#define FILT_EN_EN                           (0x1UL << 0)                               /**< Module Enable                               */
#define _FILT_EN_EN_SHIFT                    0                                          /**< Shift value for FILT_EN                     */
#define _FILT_EN_EN_MASK                     0x1UL                                      /**< Bit mask for FILT_EN                        */
#define _FILT_EN_EN_DEFAULT                  0x00000000UL                               /**< Mode DEFAULT for FILT_EN                    */
#define FILT_EN_EN_DEFAULT                   (_FILT_EN_EN_DEFAULT << 0)                 /**< Shifted mode DEFAULT for FILT_EN            */
#define FILT_EN_DISABLING                    (0x1UL << 1)                               /**< Disablement Busy Status                     */
#define _FILT_EN_DISABLING_SHIFT             1                                          /**< Shift value for FILT_DISABLING              */
#define _FILT_EN_DISABLING_MASK              0x2UL                                      /**< Bit mask for FILT_DISABLING                 */
#define _FILT_EN_DISABLING_DEFAULT           0x00000000UL                               /**< Mode DEFAULT for FILT_EN                    */
#define FILT_EN_DISABLING_DEFAULT            (_FILT_EN_DISABLING_DEFAULT << 1)          /**< Shifted mode DEFAULT for FILT_EN            */

/* Bit fields for FILT SWRST */
#define _FILT_SWRST_RESETVALUE               0x00000000UL                               /**< Default value for FILT_SWRST                */
#define _FILT_SWRST_MASK                     0x00000003UL                               /**< Mask for FILT_SWRST                         */
#define FILT_SWRST_SWRST                     (0x1UL << 0)                               /**< Software Reset Command                      */
#define _FILT_SWRST_SWRST_SHIFT              0                                          /**< Shift value for FILT_SWRST                  */
#define _FILT_SWRST_SWRST_MASK               0x1UL                                      /**< Bit mask for FILT_SWRST                     */
#define _FILT_SWRST_SWRST_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for FILT_SWRST                 */
#define FILT_SWRST_SWRST_DEFAULT             (_FILT_SWRST_SWRST_DEFAULT << 0)           /**< Shifted mode DEFAULT for FILT_SWRST         */
#define FILT_SWRST_RESETTING                 (0x1UL << 1)                               /**< Software Reset Busy Status                  */
#define _FILT_SWRST_RESETTING_SHIFT          1                                          /**< Shift value for FILT_RESETTING              */
#define _FILT_SWRST_RESETTING_MASK           0x2UL                                      /**< Bit mask for FILT_RESETTING                 */
#define _FILT_SWRST_RESETTING_DEFAULT        0x00000000UL                               /**< Mode DEFAULT for FILT_SWRST                 */
#define FILT_SWRST_RESETTING_DEFAULT         (_FILT_SWRST_RESETTING_DEFAULT << 1)       /**< Shifted mode DEFAULT for FILT_SWRST         */

/* Bit fields for FILT CONNECT */
#define _FILT_CONNECT_RESETVALUE             0x00000000UL                               /**< Default value for FILT_CONNECT              */
#define _FILT_CONNECT_MASK                   0x00000101UL                               /**< Mask for FILT_CONNECT                       */
#define FILT_CONNECT_IN                      (0x1UL << 0)                               /**< Input FIFO connect                          */
#define _FILT_CONNECT_IN_SHIFT               0                                          /**< Shift value for FILT_IN                     */
#define _FILT_CONNECT_IN_MASK                0x1UL                                      /**< Bit mask for FILT_IN                        */
#define _FILT_CONNECT_IN_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for FILT_CONNECT               */
#define FILT_CONNECT_IN_DEFAULT              (_FILT_CONNECT_IN_DEFAULT << 0)            /**< Shifted mode DEFAULT for FILT_CONNECT       */
#define FILT_CONNECT_OUT                     (0x1UL << 8)                               /**< Output FIFO connect                         */
#define _FILT_CONNECT_OUT_SHIFT              8                                          /**< Shift value for FILT_OUT                    */
#define _FILT_CONNECT_OUT_MASK               0x100UL                                    /**< Bit mask for FILT_OUT                       */
#define _FILT_CONNECT_OUT_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for FILT_CONNECT               */
#define FILT_CONNECT_OUT_DEFAULT             (_FILT_CONNECT_OUT_DEFAULT << 8)           /**< Shifted mode DEFAULT for FILT_CONNECT       */

/* Bit fields for FILT DISCLK */
#define _FILT_DISCLK_RESETVALUE              0x00000002UL                               /**< Default value for FILT_DISCLK               */
#define _FILT_DISCLK_MASK                    0x00000003UL                               /**< Mask for FILT_DISCLK                        */
#define _FILT_DISCLK_DISCLK_SHIFT            0                                          /**< Shift value for FILT_DISCLK                 */
#define _FILT_DISCLK_DISCLK_MASK             0x3UL                                      /**< Bit mask for FILT_DISCLK                    */
#define _FILT_DISCLK_DISCLK_DEFAULT          0x00000002UL                               /**< Mode DEFAULT for FILT_DISCLK                */
#define _FILT_DISCLK_DISCLK_NONE             0x00000000UL                               /**< Mode NONE for FILT_DISCLK                   */
#define _FILT_DISCLK_DISCLK_ALL              0x00000001UL                               /**< Mode ALL for FILT_DISCLK                    */
#define _FILT_DISCLK_DISCLK_AUTO             0x00000002UL                               /**< Mode AUTO for FILT_DISCLK                   */
#define FILT_DISCLK_DISCLK_DEFAULT           (_FILT_DISCLK_DISCLK_DEFAULT << 0)         /**< Shifted mode DEFAULT for FILT_DISCLK        */
#define FILT_DISCLK_DISCLK_NONE              (_FILT_DISCLK_DISCLK_NONE << 0)            /**< Shifted mode NONE for FILT_DISCLK           */
#define FILT_DISCLK_DISCLK_ALL               (_FILT_DISCLK_DISCLK_ALL << 0)             /**< Shifted mode ALL for FILT_DISCLK            */
#define FILT_DISCLK_DISCLK_AUTO              (_FILT_DISCLK_DISCLK_AUTO << 0)            /**< Shifted mode AUTO for FILT_DISCLK           */

/* Bit fields for FILT FIFOIN */
#define _FILT_FIFOIN_RESETVALUE              0x00000000UL                               /**< Default value for FILT_FIFOIN               */
#define _FILT_FIFOIN_MASK                    0x1FFF3F0FUL                               /**< Mask for FILT_FIFOIN                        */
#define _FILT_FIFOIN_FID_SHIFT               0                                          /**< Shift value for FILT_FID                    */
#define _FILT_FIFOIN_FID_MASK                0xFUL                                      /**< Bit mask for FILT_FID                       */
#define _FILT_FIFOIN_FID_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for FILT_FIFOIN                */
#define FILT_FIFOIN_FID_DEFAULT              (_FILT_FIFOIN_FID_DEFAULT << 0)            /**< Shifted mode DEFAULT for FILT_FIFOIN        */
#define _FILT_FIFOIN_CID_SHIFT               8                                          /**< Shift value for FILT_CID                    */
#define _FILT_FIFOIN_CID_MASK                0x3F00UL                                   /**< Bit mask for FILT_CID                       */
#define _FILT_FIFOIN_CID_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for FILT_FIFOIN                */
#define FILT_FIFOIN_CID_DEFAULT              (_FILT_FIFOIN_CID_DEFAULT << 8)            /**< Shifted mode DEFAULT for FILT_FIFOIN        */
#define _FILT_FIFOIN_REM_SHIFT               16                                         /**< Shift value for FILT_REM                    */
#define _FILT_FIFOIN_REM_MASK                0xFF0000UL                                 /**< Bit mask for FILT_REM                       */
#define _FILT_FIFOIN_REM_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for FILT_FIFOIN                */
#define FILT_FIFOIN_REM_DEFAULT              (_FILT_FIFOIN_REM_DEFAULT << 16)           /**< Shifted mode DEFAULT for FILT_FIFOIN        */
#define _FILT_FIFOIN_ALARM_SHIFT             24                                         /**< Shift value for FILT_ALARM                  */
#define _FILT_FIFOIN_ALARM_MASK              0x1F000000UL                               /**< Bit mask for FILT_ALARM                     */
#define _FILT_FIFOIN_ALARM_DEFAULT           0x00000000UL                               /**< Mode DEFAULT for FILT_FIFOIN                */
#define FILT_FIFOIN_ALARM_DEFAULT            (_FILT_FIFOIN_ALARM_DEFAULT << 24)         /**< Shifted mode DEFAULT for FILT_FIFOIN        */

/* Bit fields for FILT FIFOOUT */
#define _FILT_FIFOOUT_RESETVALUE             0x00000000UL                               /**< Default value for FILT_FIFOOUT              */
#define _FILT_FIFOOUT_MASK                   0x1FFF0000UL                               /**< Mask for FILT_FIFOOUT                       */
#define _FILT_FIFOOUT_CNT_SHIFT              16                                         /**< Shift value for FILT_CNT                    */
#define _FILT_FIFOOUT_CNT_MASK               0xFF0000UL                                 /**< Bit mask for FILT_CNT                       */
#define _FILT_FIFOOUT_CNT_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for FILT_FIFOOUT               */
#define FILT_FIFOOUT_CNT_DEFAULT             (_FILT_FIFOOUT_CNT_DEFAULT << 16)          /**< Shifted mode DEFAULT for FILT_FIFOOUT       */
#define _FILT_FIFOOUT_ALARM_SHIFT            24                                         /**< Shift value for FILT_ALARM                  */
#define _FILT_FIFOOUT_ALARM_MASK             0x1F000000UL                               /**< Bit mask for FILT_ALARM                     */
#define _FILT_FIFOOUT_ALARM_DEFAULT          0x00000000UL                               /**< Mode DEFAULT for FILT_FIFOOUT               */
#define FILT_FIFOOUT_ALARM_DEFAULT           (_FILT_FIFOOUT_ALARM_DEFAULT << 24)        /**< Shifted mode DEFAULT for FILT_FIFOOUT       */

/* Bit fields for FILT FMTOUT */
#define _FILT_FMTOUT_RESETVALUE              0x0000000BUL                               /**< Default value for FILT_FMTOUT               */
#define _FILT_FMTOUT_MASK                    0x0000001FUL                               /**< Mask for FILT_FMTOUT                        */
#define _FILT_FMTOUT_ELEMSIZE_SHIFT          0                                          /**< Shift value for FILT_ELEMSIZE               */
#define _FILT_FMTOUT_ELEMSIZE_MASK           0x1FUL                                     /**< Bit mask for FILT_ELEMSIZE                  */
#define _FILT_FMTOUT_ELEMSIZE_DEFAULT        0x0000000BUL                               /**< Mode DEFAULT for FILT_FMTOUT                */
#define FILT_FMTOUT_ELEMSIZE_DEFAULT         (_FILT_FMTOUT_ELEMSIZE_DEFAULT << 0)       /**< Shifted mode DEFAULT for FILT_FMTOUT        */

/* Bit fields for FILT CFG */
#define _FILT_CFG_RESETVALUE                 0x00000080UL                               /**< Default value for FILT_CFG                  */
#define _FILT_CFG_MASK                       0x013F77BFUL                               /**< Mask for FILT_CFG                           */
#define _FILT_CFG_NTAPS_SHIFT                0                                          /**< Shift value for FILT_NTAPS                  */
#define _FILT_CFG_NTAPS_MASK                 0x3FUL                                     /**< Bit mask for FILT_NTAPS                     */
#define _FILT_CFG_NTAPS_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for FILT_CFG                   */
#define FILT_CFG_NTAPS_DEFAULT               (_FILT_CFG_NTAPS_DEFAULT << 0)             /**< Shifted mode DEFAULT for FILT_CFG           */
#define FILT_CFG_SYMMETRIC                   (0x1UL << 7)                               /**< Symmetric filter                            */
#define _FILT_CFG_SYMMETRIC_SHIFT            7                                          /**< Shift value for FILT_SYMMETRIC              */
#define _FILT_CFG_SYMMETRIC_MASK             0x80UL                                     /**< Bit mask for FILT_SYMMETRIC                 */
#define _FILT_CFG_SYMMETRIC_DEFAULT          0x00000001UL                               /**< Mode DEFAULT for FILT_CFG                   */
#define FILT_CFG_SYMMETRIC_DEFAULT           (_FILT_CFG_SYMMETRIC_DEFAULT << 7)         /**< Shifted mode DEFAULT for FILT_CFG           */
#define _FILT_CFG_INTERP_SHIFT               8                                          /**< Shift value for FILT_INTERP                 */
#define _FILT_CFG_INTERP_MASK                0x700UL                                    /**< Bit mask for FILT_INTERP                    */
#define _FILT_CFG_INTERP_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for FILT_CFG                   */
#define FILT_CFG_INTERP_DEFAULT              (_FILT_CFG_INTERP_DEFAULT << 8)            /**< Shifted mode DEFAULT for FILT_CFG           */
#define _FILT_CFG_DECIM_SHIFT                12                                         /**< Shift value for FILT_DECIM                  */
#define _FILT_CFG_DECIM_MASK                 0x7000UL                                   /**< Bit mask for FILT_DECIM                     */
#define _FILT_CFG_DECIM_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for FILT_CFG                   */
#define FILT_CFG_DECIM_DEFAULT               (_FILT_CFG_DECIM_DEFAULT << 12)            /**< Shifted mode DEFAULT for FILT_CFG           */
#define _FILT_CFG_NSHIFT_SHIFT               16                                         /**< Shift value for FILT_NSHIFT                 */
#define _FILT_CFG_NSHIFT_MASK                0x3F0000UL                                 /**< Bit mask for FILT_NSHIFT                    */
#define _FILT_CFG_NSHIFT_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for FILT_CFG                   */
#define FILT_CFG_NSHIFT_DEFAULT              (_FILT_CFG_NSHIFT_DEFAULT << 16)           /**< Shifted mode DEFAULT for FILT_CFG           */
#define FILT_CFG_SKIPFIRST                   (0x1UL << 24)                              /**< Skip First Output Samples                   */
#define _FILT_CFG_SKIPFIRST_SHIFT            24                                         /**< Shift value for FILT_SKIPFIRST              */
#define _FILT_CFG_SKIPFIRST_MASK             0x1000000UL                                /**< Bit mask for FILT_SKIPFIRST                 */
#define _FILT_CFG_SKIPFIRST_DEFAULT          0x00000000UL                               /**< Mode DEFAULT for FILT_CFG                   */
#define _FILT_CFG_SKIPFIRST_NO_SKIP          0x00000000UL                               /**< Mode NO_SKIP for FILT_CFG                   */
#define _FILT_CFG_SKIPFIRST_SKIP_FIRST       0x00000001UL                               /**< Mode SKIP_FIRST for FILT_CFG                */
#define FILT_CFG_SKIPFIRST_DEFAULT           (_FILT_CFG_SKIPFIRST_DEFAULT << 24)        /**< Shifted mode DEFAULT for FILT_CFG           */
#define FILT_CFG_SKIPFIRST_NO_SKIP           (_FILT_CFG_SKIPFIRST_NO_SKIP << 24)        /**< Shifted mode NO_SKIP for FILT_CFG           */
#define FILT_CFG_SKIPFIRST_SKIP_FIRST        (_FILT_CFG_SKIPFIRST_SKIP_FIRST << 24)     /**< Shifted mode SKIP_FIRST for FILT_CFG        */

/* Bit fields for FILT CTRL */
#define _FILT_CTRL_RESETVALUE                0x00000000UL                               /**< Default value for FILT_CTRL                 */
#define _FILT_CTRL_MASK                      0xC0000001UL                               /**< Mask for FILT_CTRL                          */
#define FILT_CTRL_ENAB                       (0x1UL << 0)                               /**< Enable Filter                               */
#define _FILT_CTRL_ENAB_SHIFT                0                                          /**< Shift value for FILT_ENAB                   */
#define _FILT_CTRL_ENAB_MASK                 0x1UL                                      /**< Bit mask for FILT_ENAB                      */
#define _FILT_CTRL_ENAB_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for FILT_CTRL                  */
#define FILT_CTRL_ENAB_DEFAULT               (_FILT_CTRL_ENAB_DEFAULT << 0)             /**< Shifted mode DEFAULT for FILT_CTRL          */
#define FILT_CTRL_SKIPRST                    (0x1UL << 30)                              /**< Reset the Output Sample Skip Counter        */
#define _FILT_CTRL_SKIPRST_SHIFT             30                                         /**< Shift value for FILT_SKIPRST                */
#define _FILT_CTRL_SKIPRST_MASK              0x40000000UL                               /**< Bit mask for FILT_SKIPRST                   */
#define _FILT_CTRL_SKIPRST_DEFAULT           0x00000000UL                               /**< Mode DEFAULT for FILT_CTRL                  */
#define FILT_CTRL_SKIPRST_DEFAULT            (_FILT_CTRL_SKIPRST_DEFAULT << 30)         /**< Shifted mode DEFAULT for FILT_CTRL          */
#define FILT_CTRL_RSTFSM                     (0x1UL << 31)                              /**< Reset FSM                                   */
#define _FILT_CTRL_RSTFSM_SHIFT              31                                         /**< Shift value for FILT_RSTFSM                 */
#define _FILT_CTRL_RSTFSM_MASK               0x80000000UL                               /**< Bit mask for FILT_RSTFSM                    */
#define _FILT_CTRL_RSTFSM_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for FILT_CTRL                  */
#define FILT_CTRL_RSTFSM_DEFAULT             (_FILT_CTRL_RSTFSM_DEFAULT << 31)          /**< Shifted mode DEFAULT for FILT_CTRL          */

/* Bit fields for FILT NUMSKIP */
#define _FILT_NUMSKIP_RESETVALUE             0x00000000UL                               /**< Default value for FILT_NUMSKIP              */
#define _FILT_NUMSKIP_MASK                   0x000000FFUL                               /**< Mask for FILT_NUMSKIP                       */
#define _FILT_NUMSKIP_NUMSKIP_SHIFT          0                                          /**< Shift value for FILT_NUMSKIP                */
#define _FILT_NUMSKIP_NUMSKIP_MASK           0xFFUL                                     /**< Bit mask for FILT_NUMSKIP                   */
#define _FILT_NUMSKIP_NUMSKIP_DEFAULT        0x00000000UL                               /**< Mode DEFAULT for FILT_NUMSKIP               */
#define FILT_NUMSKIP_NUMSKIP_DEFAULT         (_FILT_NUMSKIP_NUMSKIP_DEFAULT << 0)       /**< Shifted mode DEFAULT for FILT_NUMSKIP       */

/* Bit fields for FILT COEFF */
#define _FILT_COEFF_RESETVALUE               0x00000000UL                               /**< Default value for FILT_COEFF                */
#define _FILT_COEFF_MASK                     0x00007FFFUL                               /**< Mask for FILT_COEFF                         */
#define _FILT_COEFF_COEFF_SHIFT              0                                          /**< Shift value for FILT_COEFF                  */
#define _FILT_COEFF_COEFF_MASK               0x7FFFUL                                   /**< Bit mask for FILT_COEFF                     */
#define _FILT_COEFF_COEFF_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for FILT_COEFF                 */
#define FILT_COEFF_COEFF_DEFAULT             (_FILT_COEFF_COEFF_DEFAULT << 0)           /**< Shifted mode DEFAULT for FILT_COEFF         */

/** @} End of group EFR32FG25_FILT_BitFields */
/** @} End of group EFR32FG25_FILT */
/** @} End of group Parts */

#endif /* EFR32FG25_FILT_H */
