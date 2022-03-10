/**************************************************************************//**
 * @file
 * @brief EFR32FG25 CORREL register and bit field definitions
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
#ifndef EFR32FG25_CORREL_H
#define EFR32FG25_CORREL_H
#define CORREL_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_CORREL CORREL
 * @{
 * @brief EFR32FG25 CORREL Register Declaration.
 *****************************************************************************/

/** CORREL REFSEQ Register Group Declaration. */
typedef struct {
  __IOM uint32_t VAL;                                /**< Reference Sequence                                 */
} CORREL_REFSEQ_TypeDef;

/** CORREL Register Declaration. */
typedef struct {
  __IM uint32_t         IPVERSION;              /**< IP Version ID                                      */
  __IOM uint32_t        EN;                     /**< Module Enable                                      */
  __IOM uint32_t        SWRST;                  /**< Software Reset                                     */
  __IOM uint32_t        CONNECT;                /**< FIFO Connect                                       */
  __IOM uint32_t        DISCLK;                 /**< Disable Clocks                                     */
  uint32_t              RESERVED0[3U];          /**< Reserved for future use                            */
  __IOM uint32_t        FIFOIN;                 /**< New Register                                       */
  uint32_t              RESERVED1[7U];          /**< Reserved for future use                            */
  __IM uint32_t         FIFOOUT;                /**< New Register                                       */
  uint32_t              RESERVED2[23U];         /**< Reserved for future use                            */
  uint32_t              RESERVED3[1U];          /**< Reserved for future use                            */
  uint32_t              RESERVED4[7U];          /**< Reserved for future use                            */
  uint32_t              RESERVED5[1U];          /**< Reserved for future use                            */
  uint32_t              RESERVED6[79U];         /**< Reserved for future use                            */
  __IOM uint32_t        CFG;                    /**< Configuration                                      */
  __IOM uint32_t        CTRL;                   /**< Control                                            */
  __IOM uint32_t        SHIFTRES;               /**< Result Shift Amount                                */
  __IOM uint32_t        IF;                     /**< Interrupt Flags                                    */
  __IOM uint32_t        IEN;                    /**< Interrupt Enable                                   */
  __IM uint32_t         MAXCORR;                /**< Max Correlation Value                              */
  __IM uint32_t         MAXIDX;                 /**< Max Correlation Index                              */
  __IM uint32_t         DETSYMB;                /**< Detected Symbols                                   */
  __IOM uint32_t        TRECS;                  /**< TRECS Mode Configuration                           */
  __IOM uint32_t        THRESHOLD;              /**< Correlation Threshold                              */
  __IM uint32_t         SAMPNUM;                /**< Sample Number of Threshold Cross                   */
  __IM uint32_t         LASTSAMP;               /**< Last Sample Number                                 */
  __IOM uint32_t        NUMSKIP;                /**< Number of Output Samples to Skip                   */
  __IOM uint32_t        DATAFMT;                /**< Data Format                                        */
  uint32_t              RESERVED7[18U];         /**< Reserved for future use                            */
  CORREL_REFSEQ_TypeDef REFSEQ[8U];             /**<                                                    */
  uint32_t              RESERVED8[856U];        /**< Reserved for future use                            */
  __IM uint32_t         IPVERSION_SET;          /**< IP Version ID                                      */
  __IOM uint32_t        EN_SET;                 /**< Module Enable                                      */
  __IOM uint32_t        SWRST_SET;              /**< Software Reset                                     */
  __IOM uint32_t        CONNECT_SET;            /**< FIFO Connect                                       */
  __IOM uint32_t        DISCLK_SET;             /**< Disable Clocks                                     */
  uint32_t              RESERVED9[3U];          /**< Reserved for future use                            */
  __IOM uint32_t        FIFOIN_SET;             /**< New Register                                       */
  uint32_t              RESERVED10[7U];         /**< Reserved for future use                            */
  __IM uint32_t         FIFOOUT_SET;            /**< New Register                                       */
  uint32_t              RESERVED11[23U];        /**< Reserved for future use                            */
  uint32_t              RESERVED12[1U];         /**< Reserved for future use                            */
  uint32_t              RESERVED13[7U];         /**< Reserved for future use                            */
  uint32_t              RESERVED14[1U];         /**< Reserved for future use                            */
  uint32_t              RESERVED15[79U];        /**< Reserved for future use                            */
  __IOM uint32_t        CFG_SET;                /**< Configuration                                      */
  __IOM uint32_t        CTRL_SET;               /**< Control                                            */
  __IOM uint32_t        SHIFTRES_SET;           /**< Result Shift Amount                                */
  __IOM uint32_t        IF_SET;                 /**< Interrupt Flags                                    */
  __IOM uint32_t        IEN_SET;                /**< Interrupt Enable                                   */
  __IM uint32_t         MAXCORR_SET;            /**< Max Correlation Value                              */
  __IM uint32_t         MAXIDX_SET;             /**< Max Correlation Index                              */
  __IM uint32_t         DETSYMB_SET;            /**< Detected Symbols                                   */
  __IOM uint32_t        TRECS_SET;              /**< TRECS Mode Configuration                           */
  __IOM uint32_t        THRESHOLD_SET;          /**< Correlation Threshold                              */
  __IM uint32_t         SAMPNUM_SET;            /**< Sample Number of Threshold Cross                   */
  __IM uint32_t         LASTSAMP_SET;           /**< Last Sample Number                                 */
  __IOM uint32_t        NUMSKIP_SET;            /**< Number of Output Samples to Skip                   */
  __IOM uint32_t        DATAFMT_SET;            /**< Data Format                                        */
  uint32_t              RESERVED16[18U];        /**< Reserved for future use                            */
  CORREL_REFSEQ_TypeDef REFSEQ_SET[8U];         /**<                                                    */
  uint32_t              RESERVED17[856U];       /**< Reserved for future use                            */
  __IM uint32_t         IPVERSION_CLR;          /**< IP Version ID                                      */
  __IOM uint32_t        EN_CLR;                 /**< Module Enable                                      */
  __IOM uint32_t        SWRST_CLR;              /**< Software Reset                                     */
  __IOM uint32_t        CONNECT_CLR;            /**< FIFO Connect                                       */
  __IOM uint32_t        DISCLK_CLR;             /**< Disable Clocks                                     */
  uint32_t              RESERVED18[3U];         /**< Reserved for future use                            */
  __IOM uint32_t        FIFOIN_CLR;             /**< New Register                                       */
  uint32_t              RESERVED19[7U];         /**< Reserved for future use                            */
  __IM uint32_t         FIFOOUT_CLR;            /**< New Register                                       */
  uint32_t              RESERVED20[23U];        /**< Reserved for future use                            */
  uint32_t              RESERVED21[1U];         /**< Reserved for future use                            */
  uint32_t              RESERVED22[7U];         /**< Reserved for future use                            */
  uint32_t              RESERVED23[1U];         /**< Reserved for future use                            */
  uint32_t              RESERVED24[79U];        /**< Reserved for future use                            */
  __IOM uint32_t        CFG_CLR;                /**< Configuration                                      */
  __IOM uint32_t        CTRL_CLR;               /**< Control                                            */
  __IOM uint32_t        SHIFTRES_CLR;           /**< Result Shift Amount                                */
  __IOM uint32_t        IF_CLR;                 /**< Interrupt Flags                                    */
  __IOM uint32_t        IEN_CLR;                /**< Interrupt Enable                                   */
  __IM uint32_t         MAXCORR_CLR;            /**< Max Correlation Value                              */
  __IM uint32_t         MAXIDX_CLR;             /**< Max Correlation Index                              */
  __IM uint32_t         DETSYMB_CLR;            /**< Detected Symbols                                   */
  __IOM uint32_t        TRECS_CLR;              /**< TRECS Mode Configuration                           */
  __IOM uint32_t        THRESHOLD_CLR;          /**< Correlation Threshold                              */
  __IM uint32_t         SAMPNUM_CLR;            /**< Sample Number of Threshold Cross                   */
  __IM uint32_t         LASTSAMP_CLR;           /**< Last Sample Number                                 */
  __IOM uint32_t        NUMSKIP_CLR;            /**< Number of Output Samples to Skip                   */
  __IOM uint32_t        DATAFMT_CLR;            /**< Data Format                                        */
  uint32_t              RESERVED25[18U];        /**< Reserved for future use                            */
  CORREL_REFSEQ_TypeDef REFSEQ_CLR[8U];         /**<                                                    */
  uint32_t              RESERVED26[856U];       /**< Reserved for future use                            */
  __IM uint32_t         IPVERSION_TGL;          /**< IP Version ID                                      */
  __IOM uint32_t        EN_TGL;                 /**< Module Enable                                      */
  __IOM uint32_t        SWRST_TGL;              /**< Software Reset                                     */
  __IOM uint32_t        CONNECT_TGL;            /**< FIFO Connect                                       */
  __IOM uint32_t        DISCLK_TGL;             /**< Disable Clocks                                     */
  uint32_t              RESERVED27[3U];         /**< Reserved for future use                            */
  __IOM uint32_t        FIFOIN_TGL;             /**< New Register                                       */
  uint32_t              RESERVED28[7U];         /**< Reserved for future use                            */
  __IM uint32_t         FIFOOUT_TGL;            /**< New Register                                       */
  uint32_t              RESERVED29[23U];        /**< Reserved for future use                            */
  uint32_t              RESERVED30[1U];         /**< Reserved for future use                            */
  uint32_t              RESERVED31[7U];         /**< Reserved for future use                            */
  uint32_t              RESERVED32[1U];         /**< Reserved for future use                            */
  uint32_t              RESERVED33[79U];        /**< Reserved for future use                            */
  __IOM uint32_t        CFG_TGL;                /**< Configuration                                      */
  __IOM uint32_t        CTRL_TGL;               /**< Control                                            */
  __IOM uint32_t        SHIFTRES_TGL;           /**< Result Shift Amount                                */
  __IOM uint32_t        IF_TGL;                 /**< Interrupt Flags                                    */
  __IOM uint32_t        IEN_TGL;                /**< Interrupt Enable                                   */
  __IM uint32_t         MAXCORR_TGL;            /**< Max Correlation Value                              */
  __IM uint32_t         MAXIDX_TGL;             /**< Max Correlation Index                              */
  __IM uint32_t         DETSYMB_TGL;            /**< Detected Symbols                                   */
  __IOM uint32_t        TRECS_TGL;              /**< TRECS Mode Configuration                           */
  __IOM uint32_t        THRESHOLD_TGL;          /**< Correlation Threshold                              */
  __IM uint32_t         SAMPNUM_TGL;            /**< Sample Number of Threshold Cross                   */
  __IM uint32_t         LASTSAMP_TGL;           /**< Last Sample Number                                 */
  __IOM uint32_t        NUMSKIP_TGL;            /**< Number of Output Samples to Skip                   */
  __IOM uint32_t        DATAFMT_TGL;            /**< Data Format                                        */
  uint32_t              RESERVED34[18U];        /**< Reserved for future use                            */
  CORREL_REFSEQ_TypeDef REFSEQ_TGL[8U];         /**<                                                    */
} CORREL_TypeDef;
/** @} End of group EFR32FG25_CORREL */

/**************************************************************************//**
 * @addtogroup EFR32FG25_CORREL
 * @{
 * @defgroup EFR32FG25_CORREL_BitFields CORREL Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for CORREL IPVERSION */
#define _CORREL_IPVERSION_RESETVALUE           0x00000001UL                               /**< Default value for CORREL_IPVERSION          */
#define _CORREL_IPVERSION_MASK                 0xFFFFFFFFUL                               /**< Mask for CORREL_IPVERSION                   */
#define _CORREL_IPVERSION_IPVERSION_SHIFT      0                                          /**< Shift value for CORREL_IPVERSION            */
#define _CORREL_IPVERSION_IPVERSION_MASK       0xFFFFFFFFUL                               /**< Bit mask for CORREL_IPVERSION               */
#define _CORREL_IPVERSION_IPVERSION_DEFAULT    0x00000001UL                               /**< Mode DEFAULT for CORREL_IPVERSION           */
#define CORREL_IPVERSION_IPVERSION_DEFAULT     (_CORREL_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for CORREL_IPVERSION   */

/* Bit fields for CORREL EN */
#define _CORREL_EN_RESETVALUE                  0x00000000UL                             /**< Default value for CORREL_EN                 */
#define _CORREL_EN_MASK                        0x00000003UL                             /**< Mask for CORREL_EN                          */
#define CORREL_EN_EN                           (0x1UL << 0)                             /**< Module Enable                               */
#define _CORREL_EN_EN_SHIFT                    0                                        /**< Shift value for CORREL_EN                   */
#define _CORREL_EN_EN_MASK                     0x1UL                                    /**< Bit mask for CORREL_EN                      */
#define _CORREL_EN_EN_DEFAULT                  0x00000000UL                             /**< Mode DEFAULT for CORREL_EN                  */
#define CORREL_EN_EN_DEFAULT                   (_CORREL_EN_EN_DEFAULT << 0)             /**< Shifted mode DEFAULT for CORREL_EN          */
#define CORREL_EN_DISABLING                    (0x1UL << 1)                             /**< Disablement Busy Status                     */
#define _CORREL_EN_DISABLING_SHIFT             1                                        /**< Shift value for CORREL_DISABLING            */
#define _CORREL_EN_DISABLING_MASK              0x2UL                                    /**< Bit mask for CORREL_DISABLING               */
#define _CORREL_EN_DISABLING_DEFAULT           0x00000000UL                             /**< Mode DEFAULT for CORREL_EN                  */
#define CORREL_EN_DISABLING_DEFAULT            (_CORREL_EN_DISABLING_DEFAULT << 1)      /**< Shifted mode DEFAULT for CORREL_EN          */

/* Bit fields for CORREL SWRST */
#define _CORREL_SWRST_RESETVALUE               0x00000000UL                             /**< Default value for CORREL_SWRST              */
#define _CORREL_SWRST_MASK                     0x00000003UL                             /**< Mask for CORREL_SWRST                       */
#define CORREL_SWRST_SWRST                     (0x1UL << 0)                             /**< Software Reset Command                      */
#define _CORREL_SWRST_SWRST_SHIFT              0                                        /**< Shift value for CORREL_SWRST                */
#define _CORREL_SWRST_SWRST_MASK               0x1UL                                    /**< Bit mask for CORREL_SWRST                   */
#define _CORREL_SWRST_SWRST_DEFAULT            0x00000000UL                             /**< Mode DEFAULT for CORREL_SWRST               */
#define CORREL_SWRST_SWRST_DEFAULT             (_CORREL_SWRST_SWRST_DEFAULT << 0)       /**< Shifted mode DEFAULT for CORREL_SWRST       */
#define CORREL_SWRST_RESETTING                 (0x1UL << 1)                             /**< Software Reset Busy Status                  */
#define _CORREL_SWRST_RESETTING_SHIFT          1                                        /**< Shift value for CORREL_RESETTING            */
#define _CORREL_SWRST_RESETTING_MASK           0x2UL                                    /**< Bit mask for CORREL_RESETTING               */
#define _CORREL_SWRST_RESETTING_DEFAULT        0x00000000UL                             /**< Mode DEFAULT for CORREL_SWRST               */
#define CORREL_SWRST_RESETTING_DEFAULT         (_CORREL_SWRST_RESETTING_DEFAULT << 1)   /**< Shifted mode DEFAULT for CORREL_SWRST       */

/* Bit fields for CORREL CONNECT */
#define _CORREL_CONNECT_RESETVALUE             0x00000000UL                             /**< Default value for CORREL_CONNECT            */
#define _CORREL_CONNECT_MASK                   0x00000101UL                             /**< Mask for CORREL_CONNECT                     */
#define CORREL_CONNECT_IN                      (0x1UL << 0)                             /**< Input FIFO connect                          */
#define _CORREL_CONNECT_IN_SHIFT               0                                        /**< Shift value for CORREL_IN                   */
#define _CORREL_CONNECT_IN_MASK                0x1UL                                    /**< Bit mask for CORREL_IN                      */
#define _CORREL_CONNECT_IN_DEFAULT             0x00000000UL                             /**< Mode DEFAULT for CORREL_CONNECT             */
#define CORREL_CONNECT_IN_DEFAULT              (_CORREL_CONNECT_IN_DEFAULT << 0)        /**< Shifted mode DEFAULT for CORREL_CONNECT     */
#define CORREL_CONNECT_OUT                     (0x1UL << 8)                             /**< Output FIFO connect                         */
#define _CORREL_CONNECT_OUT_SHIFT              8                                        /**< Shift value for CORREL_OUT                  */
#define _CORREL_CONNECT_OUT_MASK               0x100UL                                  /**< Bit mask for CORREL_OUT                     */
#define _CORREL_CONNECT_OUT_DEFAULT            0x00000000UL                             /**< Mode DEFAULT for CORREL_CONNECT             */
#define CORREL_CONNECT_OUT_DEFAULT             (_CORREL_CONNECT_OUT_DEFAULT << 8)       /**< Shifted mode DEFAULT for CORREL_CONNECT     */

/* Bit fields for CORREL DISCLK */
#define _CORREL_DISCLK_RESETVALUE              0x00000002UL                             /**< Default value for CORREL_DISCLK             */
#define _CORREL_DISCLK_MASK                    0x00000003UL                             /**< Mask for CORREL_DISCLK                      */
#define _CORREL_DISCLK_DISCLK_SHIFT            0                                        /**< Shift value for CORREL_DISCLK               */
#define _CORREL_DISCLK_DISCLK_MASK             0x3UL                                    /**< Bit mask for CORREL_DISCLK                  */
#define _CORREL_DISCLK_DISCLK_DEFAULT          0x00000002UL                             /**< Mode DEFAULT for CORREL_DISCLK              */
#define _CORREL_DISCLK_DISCLK_NONE             0x00000000UL                             /**< Mode NONE for CORREL_DISCLK                 */
#define _CORREL_DISCLK_DISCLK_ALL              0x00000001UL                             /**< Mode ALL for CORREL_DISCLK                  */
#define _CORREL_DISCLK_DISCLK_AUTO             0x00000002UL                             /**< Mode AUTO for CORREL_DISCLK                 */
#define CORREL_DISCLK_DISCLK_DEFAULT           (_CORREL_DISCLK_DISCLK_DEFAULT << 0)     /**< Shifted mode DEFAULT for CORREL_DISCLK      */
#define CORREL_DISCLK_DISCLK_NONE              (_CORREL_DISCLK_DISCLK_NONE << 0)        /**< Shifted mode NONE for CORREL_DISCLK         */
#define CORREL_DISCLK_DISCLK_ALL               (_CORREL_DISCLK_DISCLK_ALL << 0)         /**< Shifted mode ALL for CORREL_DISCLK          */
#define CORREL_DISCLK_DISCLK_AUTO              (_CORREL_DISCLK_DISCLK_AUTO << 0)        /**< Shifted mode AUTO for CORREL_DISCLK         */

/* Bit fields for CORREL FIFOIN */
#define _CORREL_FIFOIN_RESETVALUE              0x00000000UL                             /**< Default value for CORREL_FIFOIN             */
#define _CORREL_FIFOIN_MASK                    0x1FFF3F0FUL                             /**< Mask for CORREL_FIFOIN                      */
#define _CORREL_FIFOIN_FID_SHIFT               0                                        /**< Shift value for CORREL_FID                  */
#define _CORREL_FIFOIN_FID_MASK                0xFUL                                    /**< Bit mask for CORREL_FID                     */
#define _CORREL_FIFOIN_FID_DEFAULT             0x00000000UL                             /**< Mode DEFAULT for CORREL_FIFOIN              */
#define CORREL_FIFOIN_FID_DEFAULT              (_CORREL_FIFOIN_FID_DEFAULT << 0)        /**< Shifted mode DEFAULT for CORREL_FIFOIN      */
#define _CORREL_FIFOIN_CID_SHIFT               8                                        /**< Shift value for CORREL_CID                  */
#define _CORREL_FIFOIN_CID_MASK                0x3F00UL                                 /**< Bit mask for CORREL_CID                     */
#define _CORREL_FIFOIN_CID_DEFAULT             0x00000000UL                             /**< Mode DEFAULT for CORREL_FIFOIN              */
#define CORREL_FIFOIN_CID_DEFAULT              (_CORREL_FIFOIN_CID_DEFAULT << 8)        /**< Shifted mode DEFAULT for CORREL_FIFOIN      */
#define _CORREL_FIFOIN_REM_SHIFT               16                                       /**< Shift value for CORREL_REM                  */
#define _CORREL_FIFOIN_REM_MASK                0xFF0000UL                               /**< Bit mask for CORREL_REM                     */
#define _CORREL_FIFOIN_REM_DEFAULT             0x00000000UL                             /**< Mode DEFAULT for CORREL_FIFOIN              */
#define CORREL_FIFOIN_REM_DEFAULT              (_CORREL_FIFOIN_REM_DEFAULT << 16)       /**< Shifted mode DEFAULT for CORREL_FIFOIN      */
#define _CORREL_FIFOIN_ALARM_SHIFT             24                                       /**< Shift value for CORREL_ALARM                */
#define _CORREL_FIFOIN_ALARM_MASK              0x1F000000UL                             /**< Bit mask for CORREL_ALARM                   */
#define _CORREL_FIFOIN_ALARM_DEFAULT           0x00000000UL                             /**< Mode DEFAULT for CORREL_FIFOIN              */
#define CORREL_FIFOIN_ALARM_DEFAULT            (_CORREL_FIFOIN_ALARM_DEFAULT << 24)     /**< Shifted mode DEFAULT for CORREL_FIFOIN      */

/* Bit fields for CORREL FIFOOUT */
#define _CORREL_FIFOOUT_RESETVALUE             0x00000000UL                             /**< Default value for CORREL_FIFOOUT            */
#define _CORREL_FIFOOUT_MASK                   0x1FFF0000UL                             /**< Mask for CORREL_FIFOOUT                     */
#define _CORREL_FIFOOUT_CNT_SHIFT              16                                       /**< Shift value for CORREL_CNT                  */
#define _CORREL_FIFOOUT_CNT_MASK               0xFF0000UL                               /**< Bit mask for CORREL_CNT                     */
#define _CORREL_FIFOOUT_CNT_DEFAULT            0x00000000UL                             /**< Mode DEFAULT for CORREL_FIFOOUT             */
#define CORREL_FIFOOUT_CNT_DEFAULT             (_CORREL_FIFOOUT_CNT_DEFAULT << 16)      /**< Shifted mode DEFAULT for CORREL_FIFOOUT     */
#define _CORREL_FIFOOUT_ALARM_SHIFT            24                                       /**< Shift value for CORREL_ALARM                */
#define _CORREL_FIFOOUT_ALARM_MASK             0x1F000000UL                             /**< Bit mask for CORREL_ALARM                   */
#define _CORREL_FIFOOUT_ALARM_DEFAULT          0x00000000UL                             /**< Mode DEFAULT for CORREL_FIFOOUT             */
#define CORREL_FIFOOUT_ALARM_DEFAULT           (_CORREL_FIFOOUT_ALARM_DEFAULT << 24)    /**< Shifted mode DEFAULT for CORREL_FIFOOUT     */

/* Bit fields for CORREL CFG */
#define _CORREL_CFG_RESETVALUE                 0x00000000UL                             /**< Default value for CORREL_CFG                */
#define _CORREL_CFG_MASK                       0x777FFFFFUL                             /**< Mask for CORREL_CFG                         */
#define _CORREL_CFG_NS_SHIFT                   0                                        /**< Shift value for CORREL_NS                   */
#define _CORREL_CFG_NS_MASK                    0xFFUL                                   /**< Bit mask for CORREL_NS                      */
#define _CORREL_CFG_NS_DEFAULT                 0x00000000UL                             /**< Mode DEFAULT for CORREL_CFG                 */
#define CORREL_CFG_NS_DEFAULT                  (_CORREL_CFG_NS_DEFAULT << 0)            /**< Shifted mode DEFAULT for CORREL_CFG         */
#define _CORREL_CFG_L_SHIFT                    8                                        /**< Shift value for CORREL_L                    */
#define _CORREL_CFG_L_MASK                     0xFF00UL                                 /**< Bit mask for CORREL_L                       */
#define _CORREL_CFG_L_DEFAULT                  0x00000000UL                             /**< Mode DEFAULT for CORREL_CFG                 */
#define CORREL_CFG_L_DEFAULT                   (_CORREL_CFG_L_DEFAULT << 8)             /**< Shifted mode DEFAULT for CORREL_CFG         */
#define _CORREL_CFG_K_SHIFT                    16                                       /**< Shift value for CORREL_K                    */
#define _CORREL_CFG_K_MASK                     0x7F0000UL                               /**< Bit mask for CORREL_K                       */
#define _CORREL_CFG_K_DEFAULT                  0x00000000UL                             /**< Mode DEFAULT for CORREL_CFG                 */
#define CORREL_CFG_K_DEFAULT                   (_CORREL_CFG_K_DEFAULT << 16)            /**< Shifted mode DEFAULT for CORREL_CFG         */
#define CORREL_CFG_SEQBAR                      (0x1UL << 24)                            /**< Complementary Sequences                     */
#define _CORREL_CFG_SEQBAR_SHIFT               24                                       /**< Shift value for CORREL_SEQBAR               */
#define _CORREL_CFG_SEQBAR_MASK                0x1000000UL                              /**< Bit mask for CORREL_SEQBAR                  */
#define _CORREL_CFG_SEQBAR_DEFAULT             0x00000000UL                             /**< Mode DEFAULT for CORREL_CFG                 */
#define _CORREL_CFG_SEQBAR_NON_COMP            0x00000000UL                             /**< Mode NON_COMP for CORREL_CFG                */
#define _CORREL_CFG_SEQBAR_COMP                0x00000001UL                             /**< Mode COMP for CORREL_CFG                    */
#define CORREL_CFG_SEQBAR_DEFAULT              (_CORREL_CFG_SEQBAR_DEFAULT << 24)       /**< Shifted mode DEFAULT for CORREL_CFG         */
#define CORREL_CFG_SEQBAR_NON_COMP             (_CORREL_CFG_SEQBAR_NON_COMP << 24)      /**< Shifted mode NON_COMP for CORREL_CFG        */
#define CORREL_CFG_SEQBAR_COMP                 (_CORREL_CFG_SEQBAR_COMP << 24)          /**< Shifted mode COMP for CORREL_CFG            */
#define CORREL_CFG_ODDEVEN                     (0x1UL << 25)                            /**< Odd or Even Sequence Select                 */
#define _CORREL_CFG_ODDEVEN_SHIFT              25                                       /**< Shift value for CORREL_ODDEVEN              */
#define _CORREL_CFG_ODDEVEN_MASK               0x2000000UL                              /**< Bit mask for CORREL_ODDEVEN                 */
#define _CORREL_CFG_ODDEVEN_DEFAULT            0x00000000UL                             /**< Mode DEFAULT for CORREL_CFG                 */
#define CORREL_CFG_ODDEVEN_DEFAULT             (_CORREL_CFG_ODDEVEN_DEFAULT << 25)      /**< Shifted mode DEFAULT for CORREL_CFG         */
#define CORREL_CFG_CORRINV                     (0x1UL << 26)                            /**< Correlation Invert                          */
#define _CORREL_CFG_CORRINV_SHIFT              26                                       /**< Shift value for CORREL_CORRINV              */
#define _CORREL_CFG_CORRINV_MASK               0x4000000UL                              /**< Bit mask for CORREL_CORRINV                 */
#define _CORREL_CFG_CORRINV_DEFAULT            0x00000000UL                             /**< Mode DEFAULT for CORREL_CFG                 */
#define CORREL_CFG_CORRINV_DEFAULT             (_CORREL_CFG_CORRINV_DEFAULT << 26)      /**< Shifted mode DEFAULT for CORREL_CFG         */
#define _CORREL_CFG_MODE_SHIFT                 28                                       /**< Shift value for CORREL_MODE                 */
#define _CORREL_CFG_MODE_MASK                  0x70000000UL                             /**< Bit mask for CORREL_MODE                    */
#define _CORREL_CFG_MODE_DEFAULT               0x00000000UL                             /**< Mode DEFAULT for CORREL_CFG                 */
#define _CORREL_CFG_MODE_DSSS_TIMING_DET       0x00000000UL                             /**< Mode DSSS_TIMING_DET for CORREL_CFG         */
#define _CORREL_CFG_MODE_DSSS_SYMB_DET         0x00000001UL                             /**< Mode DSSS_SYMB_DET for CORREL_CFG           */
#define _CORREL_CFG_MODE_TRECS                 0x00000002UL                             /**< Mode TRECS for CORREL_CFG                   */
#define CORREL_CFG_MODE_DEFAULT                (_CORREL_CFG_MODE_DEFAULT << 28)         /**< Shifted mode DEFAULT for CORREL_CFG         */
#define CORREL_CFG_MODE_DSSS_TIMING_DET        (_CORREL_CFG_MODE_DSSS_TIMING_DET << 28) /**< Shifted mode DSSS_TIMING_DET for CORREL_CFG */
#define CORREL_CFG_MODE_DSSS_SYMB_DET          (_CORREL_CFG_MODE_DSSS_SYMB_DET << 28)   /**< Shifted mode DSSS_SYMB_DET for CORREL_CFG   */
#define CORREL_CFG_MODE_TRECS                  (_CORREL_CFG_MODE_TRECS << 28)           /**< Shifted mode TRECS for CORREL_CFG           */

/* Bit fields for CORREL CTRL */
#define _CORREL_CTRL_RESETVALUE                0x00000000UL                             /**< Default value for CORREL_CTRL               */
#define _CORREL_CTRL_MASK                      0x00000703UL                             /**< Mask for CORREL_CTRL                        */
#define CORREL_CTRL_START                      (0x1UL << 0)                             /**< Start Correlator                            */
#define _CORREL_CTRL_START_SHIFT               0                                        /**< Shift value for CORREL_START                */
#define _CORREL_CTRL_START_MASK                0x1UL                                    /**< Bit mask for CORREL_START                   */
#define _CORREL_CTRL_START_DEFAULT             0x00000000UL                             /**< Mode DEFAULT for CORREL_CTRL                */
#define CORREL_CTRL_START_DEFAULT              (_CORREL_CTRL_START_DEFAULT << 0)        /**< Shifted mode DEFAULT for CORREL_CTRL        */
#define CORREL_CTRL_STOP                       (0x1UL << 1)                             /**< Stop Correlator                             */
#define _CORREL_CTRL_STOP_SHIFT                1                                        /**< Shift value for CORREL_STOP                 */
#define _CORREL_CTRL_STOP_MASK                 0x2UL                                    /**< Bit mask for CORREL_STOP                    */
#define _CORREL_CTRL_STOP_DEFAULT              0x00000000UL                             /**< Mode DEFAULT for CORREL_CTRL                */
#define CORREL_CTRL_STOP_DEFAULT               (_CORREL_CTRL_STOP_DEFAULT << 1)         /**< Shifted mode DEFAULT for CORREL_CTRL        */
#define CORREL_CTRL_THRESRST                   (0x1UL << 8)                             /**< Reset Threshold Detection                   */
#define _CORREL_CTRL_THRESRST_SHIFT            8                                        /**< Shift value for CORREL_THRESRST             */
#define _CORREL_CTRL_THRESRST_MASK             0x100UL                                  /**< Bit mask for CORREL_THRESRST                */
#define _CORREL_CTRL_THRESRST_DEFAULT          0x00000000UL                             /**< Mode DEFAULT for CORREL_CTRL                */
#define CORREL_CTRL_THRESRST_DEFAULT           (_CORREL_CTRL_THRESRST_DEFAULT << 8)     /**< Shifted mode DEFAULT for CORREL_CTRL        */
#define CORREL_CTRL_SAMPNRST                   (0x1UL << 9)                             /**< Reset Sample Number                         */
#define _CORREL_CTRL_SAMPNRST_SHIFT            9                                        /**< Shift value for CORREL_SAMPNRST             */
#define _CORREL_CTRL_SAMPNRST_MASK             0x200UL                                  /**< Bit mask for CORREL_SAMPNRST                */
#define _CORREL_CTRL_SAMPNRST_DEFAULT          0x00000000UL                             /**< Mode DEFAULT for CORREL_CTRL                */
#define CORREL_CTRL_SAMPNRST_DEFAULT           (_CORREL_CTRL_SAMPNRST_DEFAULT << 9)     /**< Shifted mode DEFAULT for CORREL_CTRL        */
#define CORREL_CTRL_SKIPRST                    (0x1UL << 10)                            /**< Reset the Output Sample Skip Counter        */
#define _CORREL_CTRL_SKIPRST_SHIFT             10                                       /**< Shift value for CORREL_SKIPRST              */
#define _CORREL_CTRL_SKIPRST_MASK              0x400UL                                  /**< Bit mask for CORREL_SKIPRST                 */
#define _CORREL_CTRL_SKIPRST_DEFAULT           0x00000000UL                             /**< Mode DEFAULT for CORREL_CTRL                */
#define CORREL_CTRL_SKIPRST_DEFAULT            (_CORREL_CTRL_SKIPRST_DEFAULT << 10)     /**< Shifted mode DEFAULT for CORREL_CTRL        */

/* Bit fields for CORREL SHIFTRES */
#define _CORREL_SHIFTRES_RESETVALUE            0x00000000UL                             /**< Default value for CORREL_SHIFTRES           */
#define _CORREL_SHIFTRES_MASK                  0x0000001FUL                             /**< Mask for CORREL_SHIFTRES                    */
#define _CORREL_SHIFTRES_SHIFTRES_SHIFT        0                                        /**< Shift value for CORREL_SHIFTRES             */
#define _CORREL_SHIFTRES_SHIFTRES_MASK         0x1FUL                                   /**< Bit mask for CORREL_SHIFTRES                */
#define _CORREL_SHIFTRES_SHIFTRES_DEFAULT      0x00000000UL                             /**< Mode DEFAULT for CORREL_SHIFTRES            */
#define CORREL_SHIFTRES_SHIFTRES_DEFAULT       (_CORREL_SHIFTRES_SHIFTRES_DEFAULT << 0) /**< Shifted mode DEFAULT for CORREL_SHIFTRES    */

/* Bit fields for CORREL IF */
#define _CORREL_IF_RESETVALUE                  0x00000000UL                             /**< Default value for CORREL_IF                 */
#define _CORREL_IF_MASK                        0x00000003UL                             /**< Mask for CORREL_IF                          */
#define CORREL_IF_DONE                         (0x1UL << 0)                             /**< New BitField                                */
#define _CORREL_IF_DONE_SHIFT                  0                                        /**< Shift value for CORREL_DONE                 */
#define _CORREL_IF_DONE_MASK                   0x1UL                                    /**< Bit mask for CORREL_DONE                    */
#define _CORREL_IF_DONE_DEFAULT                0x00000000UL                             /**< Mode DEFAULT for CORREL_IF                  */
#define CORREL_IF_DONE_DEFAULT                 (_CORREL_IF_DONE_DEFAULT << 0)           /**< Shifted mode DEFAULT for CORREL_IF          */
#define CORREL_IF_THRES                        (0x1UL << 1)                             /**< New BitField                                */
#define _CORREL_IF_THRES_SHIFT                 1                                        /**< Shift value for CORREL_THRES                */
#define _CORREL_IF_THRES_MASK                  0x2UL                                    /**< Bit mask for CORREL_THRES                   */
#define _CORREL_IF_THRES_DEFAULT               0x00000000UL                             /**< Mode DEFAULT for CORREL_IF                  */
#define CORREL_IF_THRES_DEFAULT                (_CORREL_IF_THRES_DEFAULT << 1)          /**< Shifted mode DEFAULT for CORREL_IF          */

/* Bit fields for CORREL IEN */
#define _CORREL_IEN_RESETVALUE                 0x00000000UL                             /**< Default value for CORREL_IEN                */
#define _CORREL_IEN_MASK                       0x00000003UL                             /**< Mask for CORREL_IEN                         */
#define CORREL_IEN_DONE                        (0x1UL << 0)                             /**< New BitField                                */
#define _CORREL_IEN_DONE_SHIFT                 0                                        /**< Shift value for CORREL_DONE                 */
#define _CORREL_IEN_DONE_MASK                  0x1UL                                    /**< Bit mask for CORREL_DONE                    */
#define _CORREL_IEN_DONE_DEFAULT               0x00000000UL                             /**< Mode DEFAULT for CORREL_IEN                 */
#define CORREL_IEN_DONE_DEFAULT                (_CORREL_IEN_DONE_DEFAULT << 0)          /**< Shifted mode DEFAULT for CORREL_IEN         */
#define CORREL_IEN_THRES                       (0x1UL << 1)                             /**< New BitField                                */
#define _CORREL_IEN_THRES_SHIFT                1                                        /**< Shift value for CORREL_THRES                */
#define _CORREL_IEN_THRES_MASK                 0x2UL                                    /**< Bit mask for CORREL_THRES                   */
#define _CORREL_IEN_THRES_DEFAULT              0x00000000UL                             /**< Mode DEFAULT for CORREL_IEN                 */
#define CORREL_IEN_THRES_DEFAULT               (_CORREL_IEN_THRES_DEFAULT << 1)         /**< Shifted mode DEFAULT for CORREL_IEN         */

/* Bit fields for CORREL MAXCORR */
#define _CORREL_MAXCORR_RESETVALUE             0x00000000UL                             /**< Default value for CORREL_MAXCORR            */
#define _CORREL_MAXCORR_MASK                   0xFFFFFFFFUL                             /**< Mask for CORREL_MAXCORR                     */
#define _CORREL_MAXCORR_MAXCORR_SHIFT          0                                        /**< Shift value for CORREL_MAXCORR              */
#define _CORREL_MAXCORR_MAXCORR_MASK           0xFFFFFFFFUL                             /**< Bit mask for CORREL_MAXCORR                 */
#define _CORREL_MAXCORR_MAXCORR_DEFAULT        0x00000000UL                             /**< Mode DEFAULT for CORREL_MAXCORR             */
#define CORREL_MAXCORR_MAXCORR_DEFAULT         (_CORREL_MAXCORR_MAXCORR_DEFAULT << 0)   /**< Shifted mode DEFAULT for CORREL_MAXCORR     */

/* Bit fields for CORREL MAXIDX */
#define _CORREL_MAXIDX_RESETVALUE              0x00000000UL                             /**< Default value for CORREL_MAXIDX             */
#define _CORREL_MAXIDX_MASK                    0x00000FFFUL                             /**< Mask for CORREL_MAXIDX                      */
#define _CORREL_MAXIDX_MAXIDX_SHIFT            0                                        /**< Shift value for CORREL_MAXIDX               */
#define _CORREL_MAXIDX_MAXIDX_MASK             0xFFFUL                                  /**< Bit mask for CORREL_MAXIDX                  */
#define _CORREL_MAXIDX_MAXIDX_DEFAULT          0x00000000UL                             /**< Mode DEFAULT for CORREL_MAXIDX              */
#define CORREL_MAXIDX_MAXIDX_DEFAULT           (_CORREL_MAXIDX_MAXIDX_DEFAULT << 0)     /**< Shifted mode DEFAULT for CORREL_MAXIDX      */

/* Bit fields for CORREL DETSYMB */
#define _CORREL_DETSYMB_RESETVALUE             0x00000000UL                             /**< Default value for CORREL_DETSYMB            */
#define _CORREL_DETSYMB_MASK                   0xFFFFFFFFUL                             /**< Mask for CORREL_DETSYMB                     */
#define _CORREL_DETSYMB_DETSYMB_SHIFT          0                                        /**< Shift value for CORREL_DETSYMB              */
#define _CORREL_DETSYMB_DETSYMB_MASK           0xFFFFFFFFUL                             /**< Bit mask for CORREL_DETSYMB                 */
#define _CORREL_DETSYMB_DETSYMB_DEFAULT        0x00000000UL                             /**< Mode DEFAULT for CORREL_DETSYMB             */
#define CORREL_DETSYMB_DETSYMB_DEFAULT         (_CORREL_DETSYMB_DETSYMB_DEFAULT << 0)   /**< Shifted mode DEFAULT for CORREL_DETSYMB     */

/* Bit fields for CORREL TRECS */
#define _CORREL_TRECS_RESETVALUE               0x00000000UL                              /**< Default value for CORREL_TRECS              */
#define _CORREL_TRECS_MASK                     0x07FF0307UL                              /**< Mask for CORREL_TRECS                       */
#define _CORREL_TRECS_OSR_SHIFT                0                                         /**< Shift value for CORREL_OSR                  */
#define _CORREL_TRECS_OSR_MASK                 0x7UL                                     /**< Bit mask for CORREL_OSR                     */
#define _CORREL_TRECS_OSR_DEFAULT              0x00000000UL                              /**< Mode DEFAULT for CORREL_TRECS               */
#define CORREL_TRECS_OSR_DEFAULT               (_CORREL_TRECS_OSR_DEFAULT << 0)          /**< Shifted mode DEFAULT for CORREL_TRECS       */
#define CORREL_TRECS_MODEOUT                   (0x1UL << 8)                              /**< Output Mode                                 */
#define _CORREL_TRECS_MODEOUT_SHIFT            8                                         /**< Shift value for CORREL_MODEOUT              */
#define _CORREL_TRECS_MODEOUT_MASK             0x100UL                                   /**< Bit mask for CORREL_MODEOUT                 */
#define _CORREL_TRECS_MODEOUT_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for CORREL_TRECS               */
#define _CORREL_TRECS_MODEOUT_ALWAYS_ON        0x00000000UL                              /**< Mode ALWAYS_ON for CORREL_TRECS             */
#define _CORREL_TRECS_MODEOUT_POST_THRES       0x00000001UL                              /**< Mode POST_THRES for CORREL_TRECS            */
#define CORREL_TRECS_MODEOUT_DEFAULT           (_CORREL_TRECS_MODEOUT_DEFAULT << 8)      /**< Shifted mode DEFAULT for CORREL_TRECS       */
#define CORREL_TRECS_MODEOUT_ALWAYS_ON         (_CORREL_TRECS_MODEOUT_ALWAYS_ON << 8)    /**< Shifted mode ALWAYS_ON for CORREL_TRECS     */
#define CORREL_TRECS_MODEOUT_POST_THRES        (_CORREL_TRECS_MODEOUT_POST_THRES << 8)   /**< Shifted mode POST_THRES for CORREL_TRECS    */
#define CORREL_TRECS_SKIPFIRST                 (0x1UL << 9)                              /**< Skip First Output Samples                   */
#define _CORREL_TRECS_SKIPFIRST_SHIFT          9                                         /**< Shift value for CORREL_SKIPFIRST            */
#define _CORREL_TRECS_SKIPFIRST_MASK           0x200UL                                   /**< Bit mask for CORREL_SKIPFIRST               */
#define _CORREL_TRECS_SKIPFIRST_DEFAULT        0x00000000UL                              /**< Mode DEFAULT for CORREL_TRECS               */
#define _CORREL_TRECS_SKIPFIRST_NO_SKIP        0x00000000UL                              /**< Mode NO_SKIP for CORREL_TRECS               */
#define _CORREL_TRECS_SKIPFIRST_SKIP_FIRST     0x00000001UL                              /**< Mode SKIP_FIRST for CORREL_TRECS            */
#define CORREL_TRECS_SKIPFIRST_DEFAULT         (_CORREL_TRECS_SKIPFIRST_DEFAULT << 9)    /**< Shifted mode DEFAULT for CORREL_TRECS       */
#define CORREL_TRECS_SKIPFIRST_NO_SKIP         (_CORREL_TRECS_SKIPFIRST_NO_SKIP << 9)    /**< Shifted mode NO_SKIP for CORREL_TRECS       */
#define CORREL_TRECS_SKIPFIRST_SKIP_FIRST      (_CORREL_TRECS_SKIPFIRST_SKIP_FIRST << 9) /**< Shifted mode SKIP_FIRST for CORREL_TRECS    */
#define _CORREL_TRECS_FWINSIZE_SHIFT           16                                        /**< Shift value for CORREL_FWINSIZE             */
#define _CORREL_TRECS_FWINSIZE_MASK            0x3FF0000UL                               /**< Bit mask for CORREL_FWINSIZE                */
#define _CORREL_TRECS_FWINSIZE_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for CORREL_TRECS               */
#define CORREL_TRECS_FWINSIZE_DEFAULT          (_CORREL_TRECS_FWINSIZE_DEFAULT << 16)    /**< Shifted mode DEFAULT for CORREL_TRECS       */
#define CORREL_TRECS_AUTODIS                   (0x1UL << 26)                             /**< Autodisable TRECS                           */
#define _CORREL_TRECS_AUTODIS_SHIFT            26                                        /**< Shift value for CORREL_AUTODIS              */
#define _CORREL_TRECS_AUTODIS_MASK             0x4000000UL                               /**< Bit mask for CORREL_AUTODIS                 */
#define _CORREL_TRECS_AUTODIS_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for CORREL_TRECS               */
#define _CORREL_TRECS_AUTODIS_DISABLED         0x00000000UL                              /**< Mode DISABLED for CORREL_TRECS              */
#define _CORREL_TRECS_AUTODIS_ENABLED          0x00000001UL                              /**< Mode ENABLED for CORREL_TRECS               */
#define CORREL_TRECS_AUTODIS_DEFAULT           (_CORREL_TRECS_AUTODIS_DEFAULT << 26)     /**< Shifted mode DEFAULT for CORREL_TRECS       */
#define CORREL_TRECS_AUTODIS_DISABLED          (_CORREL_TRECS_AUTODIS_DISABLED << 26)    /**< Shifted mode DISABLED for CORREL_TRECS      */
#define CORREL_TRECS_AUTODIS_ENABLED           (_CORREL_TRECS_AUTODIS_ENABLED << 26)     /**< Shifted mode ENABLED for CORREL_TRECS       */

/* Bit fields for CORREL THRESHOLD */
#define _CORREL_THRESHOLD_RESETVALUE           0x00000000UL                               /**< Default value for CORREL_THRESHOLD          */
#define _CORREL_THRESHOLD_MASK                 0xFFFFFFFFUL                               /**< Mask for CORREL_THRESHOLD                   */
#define _CORREL_THRESHOLD_THRESHOLD_SHIFT      0                                          /**< Shift value for CORREL_THRESHOLD            */
#define _CORREL_THRESHOLD_THRESHOLD_MASK       0xFFFFFFFFUL                               /**< Bit mask for CORREL_THRESHOLD               */
#define _CORREL_THRESHOLD_THRESHOLD_DEFAULT    0x00000000UL                               /**< Mode DEFAULT for CORREL_THRESHOLD           */
#define CORREL_THRESHOLD_THRESHOLD_DEFAULT     (_CORREL_THRESHOLD_THRESHOLD_DEFAULT << 0) /**< Shifted mode DEFAULT for CORREL_THRESHOLD   */

/* Bit fields for CORREL SAMPNUM */
#define _CORREL_SAMPNUM_RESETVALUE             0x00000000UL                             /**< Default value for CORREL_SAMPNUM            */
#define _CORREL_SAMPNUM_MASK                   0xFFFFFFFFUL                             /**< Mask for CORREL_SAMPNUM                     */
#define _CORREL_SAMPNUM_SAMPNUM_SHIFT          0                                        /**< Shift value for CORREL_SAMPNUM              */
#define _CORREL_SAMPNUM_SAMPNUM_MASK           0xFFFFFFFFUL                             /**< Bit mask for CORREL_SAMPNUM                 */
#define _CORREL_SAMPNUM_SAMPNUM_DEFAULT        0x00000000UL                             /**< Mode DEFAULT for CORREL_SAMPNUM             */
#define CORREL_SAMPNUM_SAMPNUM_DEFAULT         (_CORREL_SAMPNUM_SAMPNUM_DEFAULT << 0)   /**< Shifted mode DEFAULT for CORREL_SAMPNUM     */

/* Bit fields for CORREL LASTSAMP */
#define _CORREL_LASTSAMP_RESETVALUE            0x00000000UL                             /**< Default value for CORREL_LASTSAMP           */
#define _CORREL_LASTSAMP_MASK                  0xFFFFFFFFUL                             /**< Mask for CORREL_LASTSAMP                    */
#define _CORREL_LASTSAMP_LASTSAMP_SHIFT        0                                        /**< Shift value for CORREL_LASTSAMP             */
#define _CORREL_LASTSAMP_LASTSAMP_MASK         0xFFFFFFFFUL                             /**< Bit mask for CORREL_LASTSAMP                */
#define _CORREL_LASTSAMP_LASTSAMP_DEFAULT      0x00000000UL                             /**< Mode DEFAULT for CORREL_LASTSAMP            */
#define CORREL_LASTSAMP_LASTSAMP_DEFAULT       (_CORREL_LASTSAMP_LASTSAMP_DEFAULT << 0) /**< Shifted mode DEFAULT for CORREL_LASTSAMP    */

/* Bit fields for CORREL NUMSKIP */
#define _CORREL_NUMSKIP_RESETVALUE             0x00000000UL                             /**< Default value for CORREL_NUMSKIP            */
#define _CORREL_NUMSKIP_MASK                   0x000000FFUL                             /**< Mask for CORREL_NUMSKIP                     */
#define _CORREL_NUMSKIP_NUMSKIP_SHIFT          0                                        /**< Shift value for CORREL_NUMSKIP              */
#define _CORREL_NUMSKIP_NUMSKIP_MASK           0xFFUL                                   /**< Bit mask for CORREL_NUMSKIP                 */
#define _CORREL_NUMSKIP_NUMSKIP_DEFAULT        0x00000000UL                             /**< Mode DEFAULT for CORREL_NUMSKIP             */
#define CORREL_NUMSKIP_NUMSKIP_DEFAULT         (_CORREL_NUMSKIP_NUMSKIP_DEFAULT << 0)   /**< Shifted mode DEFAULT for CORREL_NUMSKIP     */

/* Bit fields for CORREL DATAFMT */
#define _CORREL_DATAFMT_RESETVALUE             0x00000000UL                             /**< Default value for CORREL_DATAFMT            */
#define _CORREL_DATAFMT_MASK                   0x00000007UL                             /**< Mask for CORREL_DATAFMT                     */
#define _CORREL_DATAFMT_IQSEL_SHIFT            0                                        /**< Shift value for CORREL_IQSEL                */
#define _CORREL_DATAFMT_IQSEL_MASK             0x7UL                                    /**< Bit mask for CORREL_IQSEL                   */
#define _CORREL_DATAFMT_IQSEL_DEFAULT          0x00000000UL                             /**< Mode DEFAULT for CORREL_DATAFMT             */
#define _CORREL_DATAFMT_IQSEL_AUTO             0x00000000UL                             /**< Mode AUTO for CORREL_DATAFMT                */
#define _CORREL_DATAFMT_IQSEL_RES1             0x00000001UL                             /**< Mode RES1 for CORREL_DATAFMT                */
#define _CORREL_DATAFMT_IQSEL_SEL_I            0x00000002UL                             /**< Mode SEL_I for CORREL_DATAFMT               */
#define _CORREL_DATAFMT_IQSEL_SEL_Q            0x00000003UL                             /**< Mode SEL_Q for CORREL_DATAFMT               */
#define _CORREL_DATAFMT_IQSEL_ALT_EVEN         0x00000004UL                             /**< Mode ALT_EVEN for CORREL_DATAFMT            */
#define _CORREL_DATAFMT_IQSEL_ALT_ODD          0x00000005UL                             /**< Mode ALT_ODD for CORREL_DATAFMT             */
#define CORREL_DATAFMT_IQSEL_DEFAULT           (_CORREL_DATAFMT_IQSEL_DEFAULT << 0)     /**< Shifted mode DEFAULT for CORREL_DATAFMT     */
#define CORREL_DATAFMT_IQSEL_AUTO              (_CORREL_DATAFMT_IQSEL_AUTO << 0)        /**< Shifted mode AUTO for CORREL_DATAFMT        */
#define CORREL_DATAFMT_IQSEL_RES1              (_CORREL_DATAFMT_IQSEL_RES1 << 0)        /**< Shifted mode RES1 for CORREL_DATAFMT        */
#define CORREL_DATAFMT_IQSEL_SEL_I             (_CORREL_DATAFMT_IQSEL_SEL_I << 0)       /**< Shifted mode SEL_I for CORREL_DATAFMT       */
#define CORREL_DATAFMT_IQSEL_SEL_Q             (_CORREL_DATAFMT_IQSEL_SEL_Q << 0)       /**< Shifted mode SEL_Q for CORREL_DATAFMT       */
#define CORREL_DATAFMT_IQSEL_ALT_EVEN          (_CORREL_DATAFMT_IQSEL_ALT_EVEN << 0)    /**< Shifted mode ALT_EVEN for CORREL_DATAFMT    */
#define CORREL_DATAFMT_IQSEL_ALT_ODD           (_CORREL_DATAFMT_IQSEL_ALT_ODD << 0)     /**< Shifted mode ALT_ODD for CORREL_DATAFMT     */

/* Bit fields for CORREL VAL */
#define _CORREL_VAL_RESETVALUE                 0x00000000UL                             /**< Default value for CORREL_VAL                */
#define _CORREL_VAL_MASK                       0xFFFFFFFFUL                             /**< Mask for CORREL_VAL                         */
#define _CORREL_VAL_REFSEQ_SHIFT               0                                        /**< Shift value for CORREL_REFSEQ               */
#define _CORREL_VAL_REFSEQ_MASK                0xFFFFFFFFUL                             /**< Bit mask for CORREL_REFSEQ                  */
#define _CORREL_VAL_REFSEQ_DEFAULT             0x00000000UL                             /**< Mode DEFAULT for CORREL_VAL                 */
#define CORREL_VAL_REFSEQ_DEFAULT              (_CORREL_VAL_REFSEQ_DEFAULT << 0)        /**< Shifted mode DEFAULT for CORREL_VAL         */

/** @} End of group EFR32FG25_CORREL_BitFields */
/** @} End of group EFR32FG25_CORREL */
/** @} End of group Parts */

#endif /* EFR32FG25_CORREL_H */
