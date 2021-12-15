/**************************************************************************//**
 * @file
 * @brief EFR32FG25 TXF register and bit field definitions
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
#ifndef EFR32FG25_TXF_H
#define EFR32FG25_TXF_H
#define TXF_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_TXF TXF
 * @{
 * @brief EFR32FG25 TXF Register Declaration.
 *****************************************************************************/

/** TXF TXFIT Register Group Declaration. */
typedef struct {
  __IOM uint32_t ITCTRL;                             /**< New Register                                       */
  __IOM uint32_t DATEIT;                             /**< New Register                                       */
  __IM uint32_t  ITSIG;                              /**< New Register                                       */
} TXF_TXFIT_TypeDef;

/** TXF Register Declaration. */
typedef struct {
  __IM uint32_t     IPVERSION;                  /**< IP Version ID                                      */
  __IOM uint32_t    EN;                         /**< Module Enable                                      */
  __IOM uint32_t    SWRST;                      /**< Software Reset                                     */
  __IOM uint32_t    CONNECT;                    /**< New Register                                       */
  __IOM uint32_t    DISCLK;                     /**< Diablle clk_per                                    */
  uint32_t          RESERVED0[3U];              /**< Reserved for future use                            */
  __IOM uint32_t    FIFOIN;                     /**< New Register                                       */
  uint32_t          RESERVED1[7U];              /**< Reserved for future use                            */
  uint32_t          RESERVED2[1U];              /**< Reserved for future use                            */
  uint32_t          RESERVED3[23U];             /**< Reserved for future use                            */
  uint32_t          RESERVED4[1U];              /**< Reserved for future use                            */
  uint32_t          RESERVED5[7U];              /**< Reserved for future use                            */
  uint32_t          RESERVED6[1U];              /**< Reserved for future use                            */
  uint32_t          RESERVED7[79U];             /**< Reserved for future use                            */
  __IOM uint32_t    CTRL;                       /**< New Register                                       */
  __IM uint32_t     DATE;                       /**< New Register                                       */
  __IOM uint32_t    IF;                         /**< New Register                                       */
  __IOM uint32_t    IEN;                        /**< New Register                                       */
  __IOM uint32_t    FRAMELENGTH;                /**< New Register                                       */
  TXF_TXFIT_TypeDef TXFIT[6U];                  /**<                                                    */
  uint32_t          RESERVED8[873U];            /**< Reserved for future use                            */
  __IM uint32_t     IPVERSION_SET;              /**< IP Version ID                                      */
  __IOM uint32_t    EN_SET;                     /**< Module Enable                                      */
  __IOM uint32_t    SWRST_SET;                  /**< Software Reset                                     */
  __IOM uint32_t    CONNECT_SET;                /**< New Register                                       */
  __IOM uint32_t    DISCLK_SET;                 /**< Diablle clk_per                                    */
  uint32_t          RESERVED9[3U];              /**< Reserved for future use                            */
  __IOM uint32_t    FIFOIN_SET;                 /**< New Register                                       */
  uint32_t          RESERVED10[7U];             /**< Reserved for future use                            */
  uint32_t          RESERVED11[1U];             /**< Reserved for future use                            */
  uint32_t          RESERVED12[23U];            /**< Reserved for future use                            */
  uint32_t          RESERVED13[1U];             /**< Reserved for future use                            */
  uint32_t          RESERVED14[7U];             /**< Reserved for future use                            */
  uint32_t          RESERVED15[1U];             /**< Reserved for future use                            */
  uint32_t          RESERVED16[79U];            /**< Reserved for future use                            */
  __IOM uint32_t    CTRL_SET;                   /**< New Register                                       */
  __IM uint32_t     DATE_SET;                   /**< New Register                                       */
  __IOM uint32_t    IF_SET;                     /**< New Register                                       */
  __IOM uint32_t    IEN_SET;                    /**< New Register                                       */
  __IOM uint32_t    FRAMELENGTH_SET;            /**< New Register                                       */
  TXF_TXFIT_TypeDef TXFIT_SET[6U];              /**<                                                    */
  uint32_t          RESERVED17[873U];           /**< Reserved for future use                            */
  __IM uint32_t     IPVERSION_CLR;              /**< IP Version ID                                      */
  __IOM uint32_t    EN_CLR;                     /**< Module Enable                                      */
  __IOM uint32_t    SWRST_CLR;                  /**< Software Reset                                     */
  __IOM uint32_t    CONNECT_CLR;                /**< New Register                                       */
  __IOM uint32_t    DISCLK_CLR;                 /**< Diablle clk_per                                    */
  uint32_t          RESERVED18[3U];             /**< Reserved for future use                            */
  __IOM uint32_t    FIFOIN_CLR;                 /**< New Register                                       */
  uint32_t          RESERVED19[7U];             /**< Reserved for future use                            */
  uint32_t          RESERVED20[1U];             /**< Reserved for future use                            */
  uint32_t          RESERVED21[23U];            /**< Reserved for future use                            */
  uint32_t          RESERVED22[1U];             /**< Reserved for future use                            */
  uint32_t          RESERVED23[7U];             /**< Reserved for future use                            */
  uint32_t          RESERVED24[1U];             /**< Reserved for future use                            */
  uint32_t          RESERVED25[79U];            /**< Reserved for future use                            */
  __IOM uint32_t    CTRL_CLR;                   /**< New Register                                       */
  __IM uint32_t     DATE_CLR;                   /**< New Register                                       */
  __IOM uint32_t    IF_CLR;                     /**< New Register                                       */
  __IOM uint32_t    IEN_CLR;                    /**< New Register                                       */
  __IOM uint32_t    FRAMELENGTH_CLR;            /**< New Register                                       */
  TXF_TXFIT_TypeDef TXFIT_CLR[6U];              /**<                                                    */
  uint32_t          RESERVED26[873U];           /**< Reserved for future use                            */
  __IM uint32_t     IPVERSION_TGL;              /**< IP Version ID                                      */
  __IOM uint32_t    EN_TGL;                     /**< Module Enable                                      */
  __IOM uint32_t    SWRST_TGL;                  /**< Software Reset                                     */
  __IOM uint32_t    CONNECT_TGL;                /**< New Register                                       */
  __IOM uint32_t    DISCLK_TGL;                 /**< Diablle clk_per                                    */
  uint32_t          RESERVED27[3U];             /**< Reserved for future use                            */
  __IOM uint32_t    FIFOIN_TGL;                 /**< New Register                                       */
  uint32_t          RESERVED28[7U];             /**< Reserved for future use                            */
  uint32_t          RESERVED29[1U];             /**< Reserved for future use                            */
  uint32_t          RESERVED30[23U];            /**< Reserved for future use                            */
  uint32_t          RESERVED31[1U];             /**< Reserved for future use                            */
  uint32_t          RESERVED32[7U];             /**< Reserved for future use                            */
  uint32_t          RESERVED33[1U];             /**< Reserved for future use                            */
  uint32_t          RESERVED34[79U];            /**< Reserved for future use                            */
  __IOM uint32_t    CTRL_TGL;                   /**< New Register                                       */
  __IM uint32_t     DATE_TGL;                   /**< New Register                                       */
  __IOM uint32_t    IF_TGL;                     /**< New Register                                       */
  __IOM uint32_t    IEN_TGL;                    /**< New Register                                       */
  __IOM uint32_t    FRAMELENGTH_TGL;            /**< New Register                                       */
  TXF_TXFIT_TypeDef TXFIT_TGL[6U];              /**<                                                    */
} TXF_TypeDef;
/** @} End of group EFR32FG25_TXF */

/**************************************************************************//**
 * @addtogroup EFR32FG25_TXF
 * @{
 * @defgroup EFR32FG25_TXF_BitFields TXF Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for TXF IPVERSION */
#define _TXF_IPVERSION_RESETVALUE               0x00000001UL                            /**< Default value for TXF_IPVERSION             */
#define _TXF_IPVERSION_MASK                     0xFFFFFFFFUL                            /**< Mask for TXF_IPVERSION                      */
#define _TXF_IPVERSION_IPVERSION_SHIFT          0                                       /**< Shift value for TXF_IPVERSION               */
#define _TXF_IPVERSION_IPVERSION_MASK           0xFFFFFFFFUL                            /**< Bit mask for TXF_IPVERSION                  */
#define _TXF_IPVERSION_IPVERSION_DEFAULT        0x00000001UL                            /**< Mode DEFAULT for TXF_IPVERSION              */
#define TXF_IPVERSION_IPVERSION_DEFAULT         (_TXF_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for TXF_IPVERSION      */

/* Bit fields for TXF EN */
#define _TXF_EN_RESETVALUE                      0x00000000UL                            /**< Default value for TXF_EN                    */
#define _TXF_EN_MASK                            0x00000003UL                            /**< Mask for TXF_EN                             */
#define TXF_EN_EN                               (0x1UL << 0)                            /**< Module Enable                               */
#define _TXF_EN_EN_SHIFT                        0                                       /**< Shift value for TXF_EN                      */
#define _TXF_EN_EN_MASK                         0x1UL                                   /**< Bit mask for TXF_EN                         */
#define _TXF_EN_EN_DEFAULT                      0x00000000UL                            /**< Mode DEFAULT for TXF_EN                     */
#define TXF_EN_EN_DEFAULT                       (_TXF_EN_EN_DEFAULT << 0)               /**< Shifted mode DEFAULT for TXF_EN             */
#define TXF_EN_DISABLING                        (0x1UL << 1)                            /**< Disablement Busy Status                     */
#define _TXF_EN_DISABLING_SHIFT                 1                                       /**< Shift value for TXF_DISABLING               */
#define _TXF_EN_DISABLING_MASK                  0x2UL                                   /**< Bit mask for TXF_DISABLING                  */
#define _TXF_EN_DISABLING_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for TXF_EN                     */
#define TXF_EN_DISABLING_DEFAULT                (_TXF_EN_DISABLING_DEFAULT << 1)        /**< Shifted mode DEFAULT for TXF_EN             */

/* Bit fields for TXF SWRST */
#define _TXF_SWRST_RESETVALUE                   0x00000000UL                            /**< Default value for TXF_SWRST                 */
#define _TXF_SWRST_MASK                         0x00000003UL                            /**< Mask for TXF_SWRST                          */
#define TXF_SWRST_SWRST                         (0x1UL << 0)                            /**< Software Reset Command                      */
#define _TXF_SWRST_SWRST_SHIFT                  0                                       /**< Shift value for TXF_SWRST                   */
#define _TXF_SWRST_SWRST_MASK                   0x1UL                                   /**< Bit mask for TXF_SWRST                      */
#define _TXF_SWRST_SWRST_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for TXF_SWRST                  */
#define TXF_SWRST_SWRST_DEFAULT                 (_TXF_SWRST_SWRST_DEFAULT << 0)         /**< Shifted mode DEFAULT for TXF_SWRST          */
#define TXF_SWRST_RESETTING                     (0x1UL << 1)                            /**< Software Reset Busy Status                  */
#define _TXF_SWRST_RESETTING_SHIFT              1                                       /**< Shift value for TXF_RESETTING               */
#define _TXF_SWRST_RESETTING_MASK               0x2UL                                   /**< Bit mask for TXF_RESETTING                  */
#define _TXF_SWRST_RESETTING_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for TXF_SWRST                  */
#define TXF_SWRST_RESETTING_DEFAULT             (_TXF_SWRST_RESETTING_DEFAULT << 1)     /**< Shifted mode DEFAULT for TXF_SWRST          */

/* Bit fields for TXF CONNECT */
#define _TXF_CONNECT_RESETVALUE                 0x00000000UL                            /**< Default value for TXF_CONNECT               */
#define _TXF_CONNECT_MASK                       0x00000001UL                            /**< Mask for TXF_CONNECT                        */
#define TXF_CONNECT_IN                          (0x1UL << 0)                            /**< Input FIFO connect                          */
#define _TXF_CONNECT_IN_SHIFT                   0                                       /**< Shift value for TXF_IN                      */
#define _TXF_CONNECT_IN_MASK                    0x1UL                                   /**< Bit mask for TXF_IN                         */
#define _TXF_CONNECT_IN_DEFAULT                 0x00000000UL                            /**< Mode DEFAULT for TXF_CONNECT                */
#define TXF_CONNECT_IN_DEFAULT                  (_TXF_CONNECT_IN_DEFAULT << 0)          /**< Shifted mode DEFAULT for TXF_CONNECT        */

/* Bit fields for TXF DISCLK */
#define _TXF_DISCLK_RESETVALUE                  0x00000000UL                            /**< Default value for TXF_DISCLK                */
#define _TXF_DISCLK_MASK                        0x00000001UL                            /**< Mask for TXF_DISCLK                         */
#define TXF_DISCLK_DISCLK                       (0x1UL << 0)                            /**< New BitField                                */
#define _TXF_DISCLK_DISCLK_SHIFT                0                                       /**< Shift value for TXF_DISCLK                  */
#define _TXF_DISCLK_DISCLK_MASK                 0x1UL                                   /**< Bit mask for TXF_DISCLK                     */
#define _TXF_DISCLK_DISCLK_DEFAULT              0x00000000UL                            /**< Mode DEFAULT for TXF_DISCLK                 */
#define TXF_DISCLK_DISCLK_DEFAULT               (_TXF_DISCLK_DISCLK_DEFAULT << 0)       /**< Shifted mode DEFAULT for TXF_DISCLK         */

/* Bit fields for TXF FIFOIN */
#define _TXF_FIFOIN_RESETVALUE                  0x00000000UL                            /**< Default value for TXF_FIFOIN                */
#define _TXF_FIFOIN_MASK                        0x1FFF3F0FUL                            /**< Mask for TXF_FIFOIN                         */
#define _TXF_FIFOIN_FID_SHIFT                   0                                       /**< Shift value for TXF_FID                     */
#define _TXF_FIFOIN_FID_MASK                    0xFUL                                   /**< Bit mask for TXF_FID                        */
#define _TXF_FIFOIN_FID_DEFAULT                 0x00000000UL                            /**< Mode DEFAULT for TXF_FIFOIN                 */
#define TXF_FIFOIN_FID_DEFAULT                  (_TXF_FIFOIN_FID_DEFAULT << 0)          /**< Shifted mode DEFAULT for TXF_FIFOIN         */
#define _TXF_FIFOIN_CID_SHIFT                   8                                       /**< Shift value for TXF_CID                     */
#define _TXF_FIFOIN_CID_MASK                    0x3F00UL                                /**< Bit mask for TXF_CID                        */
#define _TXF_FIFOIN_CID_DEFAULT                 0x00000000UL                            /**< Mode DEFAULT for TXF_FIFOIN                 */
#define TXF_FIFOIN_CID_DEFAULT                  (_TXF_FIFOIN_CID_DEFAULT << 8)          /**< Shifted mode DEFAULT for TXF_FIFOIN         */
#define _TXF_FIFOIN_REM_SHIFT                   16                                      /**< Shift value for TXF_REM                     */
#define _TXF_FIFOIN_REM_MASK                    0xFF0000UL                              /**< Bit mask for TXF_REM                        */
#define _TXF_FIFOIN_REM_DEFAULT                 0x00000000UL                            /**< Mode DEFAULT for TXF_FIFOIN                 */
#define TXF_FIFOIN_REM_DEFAULT                  (_TXF_FIFOIN_REM_DEFAULT << 16)         /**< Shifted mode DEFAULT for TXF_FIFOIN         */
#define _TXF_FIFOIN_ALARM_SHIFT                 24                                      /**< Shift value for TXF_ALARM                   */
#define _TXF_FIFOIN_ALARM_MASK                  0x1F000000UL                            /**< Bit mask for TXF_ALARM                      */
#define _TXF_FIFOIN_ALARM_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for TXF_FIFOIN                 */
#define TXF_FIFOIN_ALARM_DEFAULT                (_TXF_FIFOIN_ALARM_DEFAULT << 24)       /**< Shifted mode DEFAULT for TXF_FIFOIN         */

/* Bit fields for TXF CTRL */
#define _TXF_CTRL_RESETVALUE                    0x00000002UL                            /**< Default value for TXF_CTRL                  */
#define _TXF_CTRL_MASK                          0x0000000FUL                            /**< Mask for TXF_CTRL                           */
#define TXF_CTRL_CONNECTFE                      (0x1UL << 0)                            /**< New BitField                                */
#define _TXF_CTRL_CONNECTFE_SHIFT               0                                       /**< Shift value for TXF_CONNECTFE               */
#define _TXF_CTRL_CONNECTFE_MASK                0x1UL                                   /**< Bit mask for TXF_CONNECTFE                  */
#define _TXF_CTRL_CONNECTFE_DEFAULT             0x00000000UL                            /**< Mode DEFAULT for TXF_CTRL                   */
#define TXF_CTRL_CONNECTFE_DEFAULT              (_TXF_CTRL_CONNECTFE_DEFAULT << 0)      /**< Shifted mode DEFAULT for TXF_CTRL           */
#define TXF_CTRL_DIFFENC                        (0x1UL << 1)                            /**< New BitField                                */
#define _TXF_CTRL_DIFFENC_SHIFT                 1                                       /**< Shift value for TXF_DIFFENC                 */
#define _TXF_CTRL_DIFFENC_MASK                  0x2UL                                   /**< Bit mask for TXF_DIFFENC                    */
#define _TXF_CTRL_DIFFENC_DEFAULT               0x00000001UL                            /**< Mode DEFAULT for TXF_CTRL                   */
#define _TXF_CTRL_DIFFENC_disabled              0x00000000UL                            /**< Mode disabled for TXF_CTRL                  */
#define _TXF_CTRL_DIFFENC_enabled               0x00000001UL                            /**< Mode enabled for TXF_CTRL                   */
#define TXF_CTRL_DIFFENC_DEFAULT                (_TXF_CTRL_DIFFENC_DEFAULT << 1)        /**< Shifted mode DEFAULT for TXF_CTRL           */
#define TXF_CTRL_DIFFENC_disabled               (_TXF_CTRL_DIFFENC_disabled << 1)       /**< Shifted mode disabled for TXF_CTRL          */
#define TXF_CTRL_DIFFENC_enabled                (_TXF_CTRL_DIFFENC_enabled << 1)        /**< Shifted mode enabled for TXF_CTRL           */
#define TXF_CTRL_IFSEL                          (0x1UL << 2)                            /**< New BitField                                */
#define _TXF_CTRL_IFSEL_SHIFT                   2                                       /**< Shift value for TXF_IFSEL                   */
#define _TXF_CTRL_IFSEL_MASK                    0x4UL                                   /**< Bit mask for TXF_IFSEL                      */
#define _TXF_CTRL_IFSEL_DEFAULT                 0x00000000UL                            /**< Mode DEFAULT for TXF_CTRL                   */
#define _TXF_CTRL_IFSEL_IQ                      0x00000000UL                            /**< Mode IQ for TXF_CTRL                        */
#define _TXF_CTRL_IFSEL_LEG                     0x00000001UL                            /**< Mode LEG for TXF_CTRL                       */
#define TXF_CTRL_IFSEL_DEFAULT                  (_TXF_CTRL_IFSEL_DEFAULT << 2)          /**< Shifted mode DEFAULT for TXF_CTRL           */
#define TXF_CTRL_IFSEL_IQ                       (_TXF_CTRL_IFSEL_IQ << 2)               /**< Shifted mode IQ for TXF_CTRL                */
#define TXF_CTRL_IFSEL_LEG                      (_TXF_CTRL_IFSEL_LEG << 2)              /**< Shifted mode LEG for TXF_CTRL               */
#define TXF_CTRL_DATEFORCECNT                   (0x1UL << 3)                            /**< New BitField                                */
#define _TXF_CTRL_DATEFORCECNT_SHIFT            3                                       /**< Shift value for TXF_DATEFORCECNT            */
#define _TXF_CTRL_DATEFORCECNT_MASK             0x8UL                                   /**< Bit mask for TXF_DATEFORCECNT               */
#define _TXF_CTRL_DATEFORCECNT_DEFAULT          0x00000000UL                            /**< Mode DEFAULT for TXF_CTRL                   */
#define TXF_CTRL_DATEFORCECNT_DEFAULT           (_TXF_CTRL_DATEFORCECNT_DEFAULT << 3)   /**< Shifted mode DEFAULT for TXF_CTRL           */

/* Bit fields for TXF DATE */
#define _TXF_DATE_RESETVALUE                    0x00000002UL                            /**< Default value for TXF_DATE                  */
#define _TXF_DATE_MASK                          0xFFFFFFFFUL                            /**< Mask for TXF_DATE                           */
#define _TXF_DATE_DATE_SHIFT                    0                                       /**< Shift value for TXF_DATE                    */
#define _TXF_DATE_DATE_MASK                     0xFFFFFFFFUL                            /**< Bit mask for TXF_DATE                       */
#define _TXF_DATE_DATE_DEFAULT                  0x00000002UL                            /**< Mode DEFAULT for TXF_DATE                   */
#define TXF_DATE_DATE_DEFAULT                   (_TXF_DATE_DATE_DEFAULT << 0)           /**< Shifted mode DEFAULT for TXF_DATE           */

/* Bit fields for TXF IF */
#define _TXF_IF_RESETVALUE                      0x00000000UL                            /**< Default value for TXF_IF                    */
#define _TXF_IF_MASK                            0x0000003FUL                            /**< Mask for TXF_IF                             */
#define TXF_IF_TXFIF0                           (0x1UL << 0)                            /**< TXF Interrupt Flag                          */
#define _TXF_IF_TXFIF0_SHIFT                    0                                       /**< Shift value for TXF_TXFIF0                  */
#define _TXF_IF_TXFIF0_MASK                     0x1UL                                   /**< Bit mask for TXF_TXFIF0                     */
#define _TXF_IF_TXFIF0_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for TXF_IF                     */
#define TXF_IF_TXFIF0_DEFAULT                   (_TXF_IF_TXFIF0_DEFAULT << 0)           /**< Shifted mode DEFAULT for TXF_IF             */
#define TXF_IF_TXFIF1                           (0x1UL << 1)                            /**< TXF Interrupt Flag                          */
#define _TXF_IF_TXFIF1_SHIFT                    1                                       /**< Shift value for TXF_TXFIF1                  */
#define _TXF_IF_TXFIF1_MASK                     0x2UL                                   /**< Bit mask for TXF_TXFIF1                     */
#define _TXF_IF_TXFIF1_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for TXF_IF                     */
#define TXF_IF_TXFIF1_DEFAULT                   (_TXF_IF_TXFIF1_DEFAULT << 1)           /**< Shifted mode DEFAULT for TXF_IF             */
#define TXF_IF_TXFIF2                           (0x1UL << 2)                            /**< TXF Interrupt Flag                          */
#define _TXF_IF_TXFIF2_SHIFT                    2                                       /**< Shift value for TXF_TXFIF2                  */
#define _TXF_IF_TXFIF2_MASK                     0x4UL                                   /**< Bit mask for TXF_TXFIF2                     */
#define _TXF_IF_TXFIF2_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for TXF_IF                     */
#define TXF_IF_TXFIF2_DEFAULT                   (_TXF_IF_TXFIF2_DEFAULT << 2)           /**< Shifted mode DEFAULT for TXF_IF             */
#define TXF_IF_TXFIF3                           (0x1UL << 3)                            /**< TXF Interrupt Flag                          */
#define _TXF_IF_TXFIF3_SHIFT                    3                                       /**< Shift value for TXF_TXFIF3                  */
#define _TXF_IF_TXFIF3_MASK                     0x8UL                                   /**< Bit mask for TXF_TXFIF3                     */
#define _TXF_IF_TXFIF3_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for TXF_IF                     */
#define TXF_IF_TXFIF3_DEFAULT                   (_TXF_IF_TXFIF3_DEFAULT << 3)           /**< Shifted mode DEFAULT for TXF_IF             */
#define TXF_IF_TXFIF4                           (0x1UL << 4)                            /**< TXF Interrupt Flag                          */
#define _TXF_IF_TXFIF4_SHIFT                    4                                       /**< Shift value for TXF_TXFIF4                  */
#define _TXF_IF_TXFIF4_MASK                     0x10UL                                  /**< Bit mask for TXF_TXFIF4                     */
#define _TXF_IF_TXFIF4_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for TXF_IF                     */
#define TXF_IF_TXFIF4_DEFAULT                   (_TXF_IF_TXFIF4_DEFAULT << 4)           /**< Shifted mode DEFAULT for TXF_IF             */
#define TXF_IF_TXFIF5                           (0x1UL << 5)                            /**< TXF Interrupt Flag                          */
#define _TXF_IF_TXFIF5_SHIFT                    5                                       /**< Shift value for TXF_TXFIF5                  */
#define _TXF_IF_TXFIF5_MASK                     0x20UL                                  /**< Bit mask for TXF_TXFIF5                     */
#define _TXF_IF_TXFIF5_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for TXF_IF                     */
#define TXF_IF_TXFIF5_DEFAULT                   (_TXF_IF_TXFIF5_DEFAULT << 5)           /**< Shifted mode DEFAULT for TXF_IF             */

/* Bit fields for TXF IEN */
#define _TXF_IEN_RESETVALUE                     0x00000000UL                            /**< Default value for TXF_IEN                   */
#define _TXF_IEN_MASK                           0x0000003FUL                            /**< Mask for TXF_IEN                            */
#define TXF_IEN_TXFIEN0                         (0x1UL << 0)                            /**< TXF Interrupt Enable                        */
#define _TXF_IEN_TXFIEN0_SHIFT                  0                                       /**< Shift value for TXF_TXFIEN0                 */
#define _TXF_IEN_TXFIEN0_MASK                   0x1UL                                   /**< Bit mask for TXF_TXFIEN0                    */
#define _TXF_IEN_TXFIEN0_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for TXF_IEN                    */
#define TXF_IEN_TXFIEN0_DEFAULT                 (_TXF_IEN_TXFIEN0_DEFAULT << 0)         /**< Shifted mode DEFAULT for TXF_IEN            */
#define TXF_IEN_TXFIEN1                         (0x1UL << 1)                            /**< TXF Interrupt Enable                        */
#define _TXF_IEN_TXFIEN1_SHIFT                  1                                       /**< Shift value for TXF_TXFIEN1                 */
#define _TXF_IEN_TXFIEN1_MASK                   0x2UL                                   /**< Bit mask for TXF_TXFIEN1                    */
#define _TXF_IEN_TXFIEN1_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for TXF_IEN                    */
#define TXF_IEN_TXFIEN1_DEFAULT                 (_TXF_IEN_TXFIEN1_DEFAULT << 1)         /**< Shifted mode DEFAULT for TXF_IEN            */
#define TXF_IEN_TXFIEN2                         (0x1UL << 2)                            /**< TXF Interrupt Enable                        */
#define _TXF_IEN_TXFIEN2_SHIFT                  2                                       /**< Shift value for TXF_TXFIEN2                 */
#define _TXF_IEN_TXFIEN2_MASK                   0x4UL                                   /**< Bit mask for TXF_TXFIEN2                    */
#define _TXF_IEN_TXFIEN2_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for TXF_IEN                    */
#define TXF_IEN_TXFIEN2_DEFAULT                 (_TXF_IEN_TXFIEN2_DEFAULT << 2)         /**< Shifted mode DEFAULT for TXF_IEN            */
#define TXF_IEN_TXFIEN3                         (0x1UL << 3)                            /**< TXF Interrupt Enable                        */
#define _TXF_IEN_TXFIEN3_SHIFT                  3                                       /**< Shift value for TXF_TXFIEN3                 */
#define _TXF_IEN_TXFIEN3_MASK                   0x8UL                                   /**< Bit mask for TXF_TXFIEN3                    */
#define _TXF_IEN_TXFIEN3_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for TXF_IEN                    */
#define TXF_IEN_TXFIEN3_DEFAULT                 (_TXF_IEN_TXFIEN3_DEFAULT << 3)         /**< Shifted mode DEFAULT for TXF_IEN            */
#define TXF_IEN_TXFIEN4                         (0x1UL << 4)                            /**< TXF Interrupt Enable                        */
#define _TXF_IEN_TXFIEN4_SHIFT                  4                                       /**< Shift value for TXF_TXFIEN4                 */
#define _TXF_IEN_TXFIEN4_MASK                   0x10UL                                  /**< Bit mask for TXF_TXFIEN4                    */
#define _TXF_IEN_TXFIEN4_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for TXF_IEN                    */
#define TXF_IEN_TXFIEN4_DEFAULT                 (_TXF_IEN_TXFIEN4_DEFAULT << 4)         /**< Shifted mode DEFAULT for TXF_IEN            */
#define TXF_IEN_TXFIEN5                         (0x1UL << 5)                            /**< TXF Interrupt Enable                        */
#define _TXF_IEN_TXFIEN5_SHIFT                  5                                       /**< Shift value for TXF_TXFIEN5                 */
#define _TXF_IEN_TXFIEN5_MASK                   0x20UL                                  /**< Bit mask for TXF_TXFIEN5                    */
#define _TXF_IEN_TXFIEN5_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for TXF_IEN                    */
#define TXF_IEN_TXFIEN5_DEFAULT                 (_TXF_IEN_TXFIEN5_DEFAULT << 5)         /**< Shifted mode DEFAULT for TXF_IEN            */

/* Bit fields for TXF FRAMELENGTH */
#define _TXF_FRAMELENGTH_RESETVALUE             0x00000000UL                                /**< Default value for TXF_FRAMELENGTH           */
#define _TXF_FRAMELENGTH_MASK                   0x0003FFFFUL                                /**< Mask for TXF_FRAMELENGTH                    */
#define _TXF_FRAMELENGTH_FRAMELENGTH_SHIFT      0                                           /**< Shift value for TXF_FRAMELENGTH             */
#define _TXF_FRAMELENGTH_FRAMELENGTH_MASK       0x3FFFFUL                                   /**< Bit mask for TXF_FRAMELENGTH                */
#define _TXF_FRAMELENGTH_FRAMELENGTH_DEFAULT    0x00000000UL                                /**< Mode DEFAULT for TXF_FRAMELENGTH            */
#define TXF_FRAMELENGTH_FRAMELENGTH_DEFAULT     (_TXF_FRAMELENGTH_FRAMELENGTH_DEFAULT << 0) /**< Shifted mode DEFAULT for TXF_FRAMELENGTH    */

/* Bit fields for TXF ITCTRL */
#define _TXF_ITCTRL_RESETVALUE                  0x00000000UL                            /**< Default value for TXF_ITCTRL                */
#define _TXF_ITCTRL_MASK                        0x0000000FUL                            /**< Mask for TXF_ITCTRL                         */
#define TXF_ITCTRL_ITMODE                       (0x1UL << 0)                            /**< New BitField                                */
#define _TXF_ITCTRL_ITMODE_SHIFT                0                                       /**< Shift value for TXF_ITMODE                  */
#define _TXF_ITCTRL_ITMODE_MASK                 0x1UL                                   /**< Bit mask for TXF_ITMODE                     */
#define _TXF_ITCTRL_ITMODE_DEFAULT              0x00000000UL                            /**< Mode DEFAULT for TXF_ITCTRL                 */
#define _TXF_ITCTRL_ITMODE_reg                  0x00000000UL                            /**< Mode reg for TXF_ITCTRL                     */
#define _TXF_ITCTRL_ITMODE_timer                0x00000001UL                            /**< Mode timer for TXF_ITCTRL                   */
#define TXF_ITCTRL_ITMODE_DEFAULT               (_TXF_ITCTRL_ITMODE_DEFAULT << 0)       /**< Shifted mode DEFAULT for TXF_ITCTRL         */
#define TXF_ITCTRL_ITMODE_reg                   (_TXF_ITCTRL_ITMODE_reg << 0)           /**< Shifted mode reg for TXF_ITCTRL             */
#define TXF_ITCTRL_ITMODE_timer                 (_TXF_ITCTRL_ITMODE_timer << 0)         /**< Shifted mode timer for TXF_ITCTRL           */
#define TXF_ITCTRL_ITTIMERMODE                  (0x1UL << 1)                            /**< New BitField                                */
#define _TXF_ITCTRL_ITTIMERMODE_SHIFT           1                                       /**< Shift value for TXF_ITTIMERMODE             */
#define _TXF_ITCTRL_ITTIMERMODE_MASK            0x2UL                                   /**< Bit mask for TXF_ITTIMERMODE                */
#define _TXF_ITCTRL_ITTIMERMODE_DEFAULT         0x00000000UL                            /**< Mode DEFAULT for TXF_ITCTRL                 */
#define _TXF_ITCTRL_ITTIMERMODE_expired         0x00000000UL                            /**< Mode expired for TXF_ITCTRL                 */
#define _TXF_ITCTRL_ITTIMERMODE_equal           0x00000001UL                            /**< Mode equal for TXF_ITCTRL                   */
#define TXF_ITCTRL_ITTIMERMODE_DEFAULT          (_TXF_ITCTRL_ITTIMERMODE_DEFAULT << 1)  /**< Shifted mode DEFAULT for TXF_ITCTRL         */
#define TXF_ITCTRL_ITTIMERMODE_expired          (_TXF_ITCTRL_ITTIMERMODE_expired << 1)  /**< Shifted mode expired for TXF_ITCTRL         */
#define TXF_ITCTRL_ITTIMERMODE_equal            (_TXF_ITCTRL_ITTIMERMODE_equal << 1)    /**< Shifted mode equal for TXF_ITCTRL           */
#define TXF_ITCTRL_ITREG                        (0x1UL << 2)                            /**< New BitField                                */
#define _TXF_ITCTRL_ITREG_SHIFT                 2                                       /**< Shift value for TXF_ITREG                   */
#define _TXF_ITCTRL_ITREG_MASK                  0x4UL                                   /**< Bit mask for TXF_ITREG                      */
#define _TXF_ITCTRL_ITREG_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for TXF_ITCTRL                 */
#define TXF_ITCTRL_ITREG_DEFAULT                (_TXF_ITCTRL_ITREG_DEFAULT << 2)        /**< Shifted mode DEFAULT for TXF_ITCTRL         */
#define TXF_ITCTRL_ITTRIG                       (0x1UL << 3)                            /**< New BitField                                */
#define _TXF_ITCTRL_ITTRIG_SHIFT                3                                       /**< Shift value for TXF_ITTRIG                  */
#define _TXF_ITCTRL_ITTRIG_MASK                 0x8UL                                   /**< Bit mask for TXF_ITTRIG                     */
#define _TXF_ITCTRL_ITTRIG_DEFAULT              0x00000000UL                            /**< Mode DEFAULT for TXF_ITCTRL                 */
#define _TXF_ITCTRL_ITTRIG_pulse                0x00000000UL                            /**< Mode pulse for TXF_ITCTRL                   */
#define _TXF_ITCTRL_ITTRIG_level                0x00000001UL                            /**< Mode level for TXF_ITCTRL                   */
#define TXF_ITCTRL_ITTRIG_DEFAULT               (_TXF_ITCTRL_ITTRIG_DEFAULT << 3)       /**< Shifted mode DEFAULT for TXF_ITCTRL         */
#define TXF_ITCTRL_ITTRIG_pulse                 (_TXF_ITCTRL_ITTRIG_pulse << 3)         /**< Shifted mode pulse for TXF_ITCTRL           */
#define TXF_ITCTRL_ITTRIG_level                 (_TXF_ITCTRL_ITTRIG_level << 3)         /**< Shifted mode level for TXF_ITCTRL           */

/* Bit fields for TXF DATEIT */
#define _TXF_DATEIT_RESETVALUE                  0x00000000UL                            /**< Default value for TXF_DATEIT                */
#define _TXF_DATEIT_MASK                        0xFFFFFFFFUL                            /**< Mask for TXF_DATEIT                         */
#define _TXF_DATEIT_DATEIT_SHIFT                0                                       /**< Shift value for TXF_DATEIT                  */
#define _TXF_DATEIT_DATEIT_MASK                 0xFFFFFFFFUL                            /**< Bit mask for TXF_DATEIT                     */
#define _TXF_DATEIT_DATEIT_DEFAULT              0x00000000UL                            /**< Mode DEFAULT for TXF_DATEIT                 */
#define TXF_DATEIT_DATEIT_DEFAULT               (_TXF_DATEIT_DATEIT_DEFAULT << 0)       /**< Shifted mode DEFAULT for TXF_DATEIT         */

/* Bit fields for TXF ITSIG */
#define _TXF_ITSIG_RESETVALUE                   0x00000000UL                            /**< Default value for TXF_ITSIG                 */
#define _TXF_ITSIG_MASK                         0x00000001UL                            /**< Mask for TXF_ITSIG                          */
#define TXF_ITSIG_ITSIG                         (0x1UL << 0)                            /**< New BitField                                */
#define _TXF_ITSIG_ITSIG_SHIFT                  0                                       /**< Shift value for TXF_ITSIG                   */
#define _TXF_ITSIG_ITSIG_MASK                   0x1UL                                   /**< Bit mask for TXF_ITSIG                      */
#define _TXF_ITSIG_ITSIG_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for TXF_ITSIG                  */
#define TXF_ITSIG_ITSIG_DEFAULT                 (_TXF_ITSIG_ITSIG_DEFAULT << 0)         /**< Shifted mode DEFAULT for TXF_ITSIG          */

/** @} End of group EFR32FG25_TXF_BitFields */
/** @} End of group EFR32FG25_TXF */
/** @} End of group Parts */

#endif /* EFR32FG25_TXF_H */
