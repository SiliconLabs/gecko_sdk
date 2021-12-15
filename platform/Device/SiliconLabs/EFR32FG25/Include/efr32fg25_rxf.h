/**************************************************************************//**
 * @file
 * @brief EFR32FG25 RXF register and bit field definitions
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
#ifndef EFR32FG25_RXF_H
#define EFR32FG25_RXF_H
#define RXF_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_RXF RXF
 * @{
 * @brief EFR32FG25 RXF Register Declaration.
 *****************************************************************************/

/** RXF RXFIT Register Group Declaration. */
typedef struct {
  __IOM uint32_t ITCTRL;                             /**< New Register                                       */
  __IOM uint32_t DATEIT;                             /**< New Register                                       */
  __IM uint32_t  ITSIG;                              /**< New Register                                       */
} RXF_RXFIT_TypeDef;

/** RXF RXFEV Register Group Declaration. */
typedef struct {
  __IOM uint32_t EVCTRL;                             /**< New Register                                       */
  __IM uint32_t  EVDATE;                             /**< New Register                                       */
} RXF_RXFEV_TypeDef;

/** RXF Register Declaration. */
typedef struct {
  __IM uint32_t     IPVERSION;                  /**< IP Version ID                                      */
  __IOM uint32_t    EN;                         /**< Module Enable                                      */
  __IOM uint32_t    SWRST;                      /**< Software Reset                                     */
  __IOM uint32_t    CONNECT;                    /**< New Register                                       */
  __IOM uint32_t    DISCLK;                     /**< Diablle clk_per                                    */
  uint32_t          RESERVED0[3U];              /**< Reserved for future use                            */
  uint32_t          RESERVED1[1U];              /**< Reserved for future use                            */
  uint32_t          RESERVED2[7U];              /**< Reserved for future use                            */
  __IM uint32_t     FIFOOUT;                    /**< New Register                                       */
  uint32_t          RESERVED3[23U];             /**< Reserved for future use                            */
  uint32_t          RESERVED4[1U];              /**< Reserved for future use                            */
  uint32_t          RESERVED5[7U];              /**< Reserved for future use                            */
  uint32_t          RESERVED6[1U];              /**< Reserved for future use                            */
  uint32_t          RESERVED7[79U];             /**< Reserved for future use                            */
  __IOM uint32_t    CTRL;                       /**< New Register                                       */
  __IM uint32_t     DATE;                       /**< New Register                                       */
  __IOM uint32_t    IF;                         /**< New Register                                       */
  __IOM uint32_t    IEN;                        /**< New Register                                       */
  RXF_RXFIT_TypeDef RXFIT[10U];                 /**<                                                    */
  uint32_t          RESERVED8[2U];              /**< Reserved for future use                            */
  RXF_RXFEV_TypeDef RXFEV[4U];                  /**<                                                    */
  uint32_t          RESERVED9[852U];            /**< Reserved for future use                            */
  __IM uint32_t     IPVERSION_SET;              /**< IP Version ID                                      */
  __IOM uint32_t    EN_SET;                     /**< Module Enable                                      */
  __IOM uint32_t    SWRST_SET;                  /**< Software Reset                                     */
  __IOM uint32_t    CONNECT_SET;                /**< New Register                                       */
  __IOM uint32_t    DISCLK_SET;                 /**< Diablle clk_per                                    */
  uint32_t          RESERVED10[3U];             /**< Reserved for future use                            */
  uint32_t          RESERVED11[1U];             /**< Reserved for future use                            */
  uint32_t          RESERVED12[7U];             /**< Reserved for future use                            */
  __IM uint32_t     FIFOOUT_SET;                /**< New Register                                       */
  uint32_t          RESERVED13[23U];            /**< Reserved for future use                            */
  uint32_t          RESERVED14[1U];             /**< Reserved for future use                            */
  uint32_t          RESERVED15[7U];             /**< Reserved for future use                            */
  uint32_t          RESERVED16[1U];             /**< Reserved for future use                            */
  uint32_t          RESERVED17[79U];            /**< Reserved for future use                            */
  __IOM uint32_t    CTRL_SET;                   /**< New Register                                       */
  __IM uint32_t     DATE_SET;                   /**< New Register                                       */
  __IOM uint32_t    IF_SET;                     /**< New Register                                       */
  __IOM uint32_t    IEN_SET;                    /**< New Register                                       */
  RXF_RXFIT_TypeDef RXFIT_SET[10U];             /**<                                                    */
  uint32_t          RESERVED18[2U];             /**< Reserved for future use                            */
  RXF_RXFEV_TypeDef RXFEV_SET[4U];              /**<                                                    */
  uint32_t          RESERVED19[852U];           /**< Reserved for future use                            */
  __IM uint32_t     IPVERSION_CLR;              /**< IP Version ID                                      */
  __IOM uint32_t    EN_CLR;                     /**< Module Enable                                      */
  __IOM uint32_t    SWRST_CLR;                  /**< Software Reset                                     */
  __IOM uint32_t    CONNECT_CLR;                /**< New Register                                       */
  __IOM uint32_t    DISCLK_CLR;                 /**< Diablle clk_per                                    */
  uint32_t          RESERVED20[3U];             /**< Reserved for future use                            */
  uint32_t          RESERVED21[1U];             /**< Reserved for future use                            */
  uint32_t          RESERVED22[7U];             /**< Reserved for future use                            */
  __IM uint32_t     FIFOOUT_CLR;                /**< New Register                                       */
  uint32_t          RESERVED23[23U];            /**< Reserved for future use                            */
  uint32_t          RESERVED24[1U];             /**< Reserved for future use                            */
  uint32_t          RESERVED25[7U];             /**< Reserved for future use                            */
  uint32_t          RESERVED26[1U];             /**< Reserved for future use                            */
  uint32_t          RESERVED27[79U];            /**< Reserved for future use                            */
  __IOM uint32_t    CTRL_CLR;                   /**< New Register                                       */
  __IM uint32_t     DATE_CLR;                   /**< New Register                                       */
  __IOM uint32_t    IF_CLR;                     /**< New Register                                       */
  __IOM uint32_t    IEN_CLR;                    /**< New Register                                       */
  RXF_RXFIT_TypeDef RXFIT_CLR[10U];             /**<                                                    */
  uint32_t          RESERVED28[2U];             /**< Reserved for future use                            */
  RXF_RXFEV_TypeDef RXFEV_CLR[4U];              /**<                                                    */
  uint32_t          RESERVED29[852U];           /**< Reserved for future use                            */
  __IM uint32_t     IPVERSION_TGL;              /**< IP Version ID                                      */
  __IOM uint32_t    EN_TGL;                     /**< Module Enable                                      */
  __IOM uint32_t    SWRST_TGL;                  /**< Software Reset                                     */
  __IOM uint32_t    CONNECT_TGL;                /**< New Register                                       */
  __IOM uint32_t    DISCLK_TGL;                 /**< Diablle clk_per                                    */
  uint32_t          RESERVED30[3U];             /**< Reserved for future use                            */
  uint32_t          RESERVED31[1U];             /**< Reserved for future use                            */
  uint32_t          RESERVED32[7U];             /**< Reserved for future use                            */
  __IM uint32_t     FIFOOUT_TGL;                /**< New Register                                       */
  uint32_t          RESERVED33[23U];            /**< Reserved for future use                            */
  uint32_t          RESERVED34[1U];             /**< Reserved for future use                            */
  uint32_t          RESERVED35[7U];             /**< Reserved for future use                            */
  uint32_t          RESERVED36[1U];             /**< Reserved for future use                            */
  uint32_t          RESERVED37[79U];            /**< Reserved for future use                            */
  __IOM uint32_t    CTRL_TGL;                   /**< New Register                                       */
  __IM uint32_t     DATE_TGL;                   /**< New Register                                       */
  __IOM uint32_t    IF_TGL;                     /**< New Register                                       */
  __IOM uint32_t    IEN_TGL;                    /**< New Register                                       */
  RXF_RXFIT_TypeDef RXFIT_TGL[10U];             /**<                                                    */
  uint32_t          RESERVED38[2U];             /**< Reserved for future use                            */
  RXF_RXFEV_TypeDef RXFEV_TGL[4U];              /**<                                                    */
} RXF_TypeDef;
/** @} End of group EFR32FG25_RXF */

/**************************************************************************//**
 * @addtogroup EFR32FG25_RXF
 * @{
 * @defgroup EFR32FG25_RXF_BitFields RXF Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for RXF IPVERSION */
#define _RXF_IPVERSION_RESETVALUE           0x00000001UL                                /**< Default value for RXF_IPVERSION             */
#define _RXF_IPVERSION_MASK                 0xFFFFFFFFUL                                /**< Mask for RXF_IPVERSION                      */
#define _RXF_IPVERSION_IPVERSION_SHIFT      0                                           /**< Shift value for RXF_IPVERSION               */
#define _RXF_IPVERSION_IPVERSION_MASK       0xFFFFFFFFUL                                /**< Bit mask for RXF_IPVERSION                  */
#define _RXF_IPVERSION_IPVERSION_DEFAULT    0x00000001UL                                /**< Mode DEFAULT for RXF_IPVERSION              */
#define RXF_IPVERSION_IPVERSION_DEFAULT     (_RXF_IPVERSION_IPVERSION_DEFAULT << 0)     /**< Shifted mode DEFAULT for RXF_IPVERSION      */

/* Bit fields for RXF EN */
#define _RXF_EN_RESETVALUE                  0x00000000UL                                /**< Default value for RXF_EN                    */
#define _RXF_EN_MASK                        0x00000003UL                                /**< Mask for RXF_EN                             */
#define RXF_EN_EN                           (0x1UL << 0)                                /**< Module Enable                               */
#define _RXF_EN_EN_SHIFT                    0                                           /**< Shift value for RXF_EN                      */
#define _RXF_EN_EN_MASK                     0x1UL                                       /**< Bit mask for RXF_EN                         */
#define _RXF_EN_EN_DEFAULT                  0x00000000UL                                /**< Mode DEFAULT for RXF_EN                     */
#define RXF_EN_EN_DEFAULT                   (_RXF_EN_EN_DEFAULT << 0)                   /**< Shifted mode DEFAULT for RXF_EN             */
#define RXF_EN_DISABLING                    (0x1UL << 1)                                /**< Disablement Busy Status                     */
#define _RXF_EN_DISABLING_SHIFT             1                                           /**< Shift value for RXF_DISABLING               */
#define _RXF_EN_DISABLING_MASK              0x2UL                                       /**< Bit mask for RXF_DISABLING                  */
#define _RXF_EN_DISABLING_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for RXF_EN                     */
#define RXF_EN_DISABLING_DEFAULT            (_RXF_EN_DISABLING_DEFAULT << 1)            /**< Shifted mode DEFAULT for RXF_EN             */

/* Bit fields for RXF SWRST */
#define _RXF_SWRST_RESETVALUE               0x00000000UL                                /**< Default value for RXF_SWRST                 */
#define _RXF_SWRST_MASK                     0x00000003UL                                /**< Mask for RXF_SWRST                          */
#define RXF_SWRST_SWRST                     (0x1UL << 0)                                /**< Software Reset Command                      */
#define _RXF_SWRST_SWRST_SHIFT              0                                           /**< Shift value for RXF_SWRST                   */
#define _RXF_SWRST_SWRST_MASK               0x1UL                                       /**< Bit mask for RXF_SWRST                      */
#define _RXF_SWRST_SWRST_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for RXF_SWRST                  */
#define RXF_SWRST_SWRST_DEFAULT             (_RXF_SWRST_SWRST_DEFAULT << 0)             /**< Shifted mode DEFAULT for RXF_SWRST          */
#define RXF_SWRST_RESETTING                 (0x1UL << 1)                                /**< Software Reset Busy Status                  */
#define _RXF_SWRST_RESETTING_SHIFT          1                                           /**< Shift value for RXF_RESETTING               */
#define _RXF_SWRST_RESETTING_MASK           0x2UL                                       /**< Bit mask for RXF_RESETTING                  */
#define _RXF_SWRST_RESETTING_DEFAULT        0x00000000UL                                /**< Mode DEFAULT for RXF_SWRST                  */
#define RXF_SWRST_RESETTING_DEFAULT         (_RXF_SWRST_RESETTING_DEFAULT << 1)         /**< Shifted mode DEFAULT for RXF_SWRST          */

/* Bit fields for RXF CONNECT */
#define _RXF_CONNECT_RESETVALUE             0x00000000UL                                /**< Default value for RXF_CONNECT               */
#define _RXF_CONNECT_MASK                   0x00000100UL                                /**< Mask for RXF_CONNECT                        */
#define RXF_CONNECT_OUT                     (0x1UL << 8)                                /**< Output FIFO connect                         */
#define _RXF_CONNECT_OUT_SHIFT              8                                           /**< Shift value for RXF_OUT                     */
#define _RXF_CONNECT_OUT_MASK               0x100UL                                     /**< Bit mask for RXF_OUT                        */
#define _RXF_CONNECT_OUT_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for RXF_CONNECT                */
#define RXF_CONNECT_OUT_DEFAULT             (_RXF_CONNECT_OUT_DEFAULT << 8)             /**< Shifted mode DEFAULT for RXF_CONNECT        */

/* Bit fields for RXF DISCLK */
#define _RXF_DISCLK_RESETVALUE              0x00000000UL                                /**< Default value for RXF_DISCLK                */
#define _RXF_DISCLK_MASK                    0x00000001UL                                /**< Mask for RXF_DISCLK                         */
#define RXF_DISCLK_DISCLK                   (0x1UL << 0)                                /**< New BitField                                */
#define _RXF_DISCLK_DISCLK_SHIFT            0                                           /**< Shift value for RXF_DISCLK                  */
#define _RXF_DISCLK_DISCLK_MASK             0x1UL                                       /**< Bit mask for RXF_DISCLK                     */
#define _RXF_DISCLK_DISCLK_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for RXF_DISCLK                 */
#define RXF_DISCLK_DISCLK_DEFAULT           (_RXF_DISCLK_DISCLK_DEFAULT << 0)           /**< Shifted mode DEFAULT for RXF_DISCLK         */

/* Bit fields for RXF FIFOOUT */
#define _RXF_FIFOOUT_RESETVALUE             0x00000000UL                                /**< Default value for RXF_FIFOOUT               */
#define _RXF_FIFOOUT_MASK                   0x1FFF0000UL                                /**< Mask for RXF_FIFOOUT                        */
#define _RXF_FIFOOUT_CNT_SHIFT              16                                          /**< Shift value for RXF_CNT                     */
#define _RXF_FIFOOUT_CNT_MASK               0xFF0000UL                                  /**< Bit mask for RXF_CNT                        */
#define _RXF_FIFOOUT_CNT_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for RXF_FIFOOUT                */
#define RXF_FIFOOUT_CNT_DEFAULT             (_RXF_FIFOOUT_CNT_DEFAULT << 16)            /**< Shifted mode DEFAULT for RXF_FIFOOUT        */
#define _RXF_FIFOOUT_ALARM_SHIFT            24                                          /**< Shift value for RXF_ALARM                   */
#define _RXF_FIFOOUT_ALARM_MASK             0x1F000000UL                                /**< Bit mask for RXF_ALARM                      */
#define _RXF_FIFOOUT_ALARM_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for RXF_FIFOOUT                */
#define RXF_FIFOOUT_ALARM_DEFAULT           (_RXF_FIFOOUT_ALARM_DEFAULT << 24)          /**< Shifted mode DEFAULT for RXF_FIFOOUT        */

/* Bit fields for RXF CTRL */
#define _RXF_CTRL_RESETVALUE                0x00000000UL                                /**< Default value for RXF_CTRL                  */
#define _RXF_CTRL_MASK                      0x0003FF07UL                                /**< Mask for RXF_CTRL                           */
#define RXF_CTRL_CONNECTFE                  (0x1UL << 0)                                /**< New BitField                                */
#define _RXF_CTRL_CONNECTFE_SHIFT           0                                           /**< Shift value for RXF_CONNECTFE               */
#define _RXF_CTRL_CONNECTFE_MASK            0x1UL                                       /**< Bit mask for RXF_CONNECTFE                  */
#define _RXF_CTRL_CONNECTFE_DEFAULT         0x00000000UL                                /**< Mode DEFAULT for RXF_CTRL                   */
#define RXF_CTRL_CONNECTFE_DEFAULT          (_RXF_CTRL_CONNECTFE_DEFAULT << 0)          /**< Shifted mode DEFAULT for RXF_CTRL           */
#define RXF_CTRL_DATEREINIT                 (0x1UL << 1)                                /**< New BitField                                */
#define _RXF_CTRL_DATEREINIT_SHIFT          1                                           /**< Shift value for RXF_DATEREINIT              */
#define _RXF_CTRL_DATEREINIT_MASK           0x2UL                                       /**< Bit mask for RXF_DATEREINIT                 */
#define _RXF_CTRL_DATEREINIT_DEFAULT        0x00000000UL                                /**< Mode DEFAULT for RXF_CTRL                   */
#define RXF_CTRL_DATEREINIT_DEFAULT         (_RXF_CTRL_DATEREINIT_DEFAULT << 1)         /**< Shifted mode DEFAULT for RXF_CTRL           */
#define RXF_CTRL_DATEFORCECNT               (0x1UL << 2)                                /**< New BitField                                */
#define _RXF_CTRL_DATEFORCECNT_SHIFT        2                                           /**< Shift value for RXF_DATEFORCECNT            */
#define _RXF_CTRL_DATEFORCECNT_MASK         0x4UL                                       /**< Bit mask for RXF_DATEFORCECNT               */
#define _RXF_CTRL_DATEFORCECNT_DEFAULT      0x00000000UL                                /**< Mode DEFAULT for RXF_CTRL                   */
#define RXF_CTRL_DATEFORCECNT_DEFAULT       (_RXF_CTRL_DATEFORCECNT_DEFAULT << 2)       /**< Shifted mode DEFAULT for RXF_CTRL           */
#define _RXF_CTRL_DATESKIP_SHIFT            8                                           /**< Shift value for RXF_DATESKIP                */
#define _RXF_CTRL_DATESKIP_MASK             0x3FF00UL                                   /**< Bit mask for RXF_DATESKIP                   */
#define _RXF_CTRL_DATESKIP_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for RXF_CTRL                   */
#define RXF_CTRL_DATESKIP_DEFAULT           (_RXF_CTRL_DATESKIP_DEFAULT << 8)           /**< Shifted mode DEFAULT for RXF_CTRL           */

/* Bit fields for RXF DATE */
#define _RXF_DATE_RESETVALUE                0x00000002UL                                /**< Default value for RXF_DATE                  */
#define _RXF_DATE_MASK                      0xFFFFFFFFUL                                /**< Mask for RXF_DATE                           */
#define _RXF_DATE_DATE_SHIFT                0                                           /**< Shift value for RXF_DATE                    */
#define _RXF_DATE_DATE_MASK                 0xFFFFFFFFUL                                /**< Bit mask for RXF_DATE                       */
#define _RXF_DATE_DATE_DEFAULT              0x00000002UL                                /**< Mode DEFAULT for RXF_DATE                   */
#define RXF_DATE_DATE_DEFAULT               (_RXF_DATE_DATE_DEFAULT << 0)               /**< Shifted mode DEFAULT for RXF_DATE           */

/* Bit fields for RXF IF */
#define _RXF_IF_RESETVALUE                  0x00000000UL                                /**< Default value for RXF_IF                    */
#define _RXF_IF_MASK                        0x000003FFUL                                /**< Mask for RXF_IF                             */
#define RXF_IF_RXFIF0                       (0x1UL << 0)                                /**< RXF Interrupt Flag                          */
#define _RXF_IF_RXFIF0_SHIFT                0                                           /**< Shift value for RXF_RXFIF0                  */
#define _RXF_IF_RXFIF0_MASK                 0x1UL                                       /**< Bit mask for RXF_RXFIF0                     */
#define _RXF_IF_RXFIF0_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for RXF_IF                     */
#define RXF_IF_RXFIF0_DEFAULT               (_RXF_IF_RXFIF0_DEFAULT << 0)               /**< Shifted mode DEFAULT for RXF_IF             */
#define RXF_IF_RXFIF1                       (0x1UL << 1)                                /**< RXF Interrupt Flag                          */
#define _RXF_IF_RXFIF1_SHIFT                1                                           /**< Shift value for RXF_RXFIF1                  */
#define _RXF_IF_RXFIF1_MASK                 0x2UL                                       /**< Bit mask for RXF_RXFIF1                     */
#define _RXF_IF_RXFIF1_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for RXF_IF                     */
#define RXF_IF_RXFIF1_DEFAULT               (_RXF_IF_RXFIF1_DEFAULT << 1)               /**< Shifted mode DEFAULT for RXF_IF             */
#define RXF_IF_RXFIF2                       (0x1UL << 2)                                /**< RXF Interrupt Flag                          */
#define _RXF_IF_RXFIF2_SHIFT                2                                           /**< Shift value for RXF_RXFIF2                  */
#define _RXF_IF_RXFIF2_MASK                 0x4UL                                       /**< Bit mask for RXF_RXFIF2                     */
#define _RXF_IF_RXFIF2_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for RXF_IF                     */
#define RXF_IF_RXFIF2_DEFAULT               (_RXF_IF_RXFIF2_DEFAULT << 2)               /**< Shifted mode DEFAULT for RXF_IF             */
#define RXF_IF_RXFIF3                       (0x1UL << 3)                                /**< RXF Interrupt Flag                          */
#define _RXF_IF_RXFIF3_SHIFT                3                                           /**< Shift value for RXF_RXFIF3                  */
#define _RXF_IF_RXFIF3_MASK                 0x8UL                                       /**< Bit mask for RXF_RXFIF3                     */
#define _RXF_IF_RXFIF3_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for RXF_IF                     */
#define RXF_IF_RXFIF3_DEFAULT               (_RXF_IF_RXFIF3_DEFAULT << 3)               /**< Shifted mode DEFAULT for RXF_IF             */
#define RXF_IF_RXFIF4                       (0x1UL << 4)                                /**< RXF Interrupt Flag                          */
#define _RXF_IF_RXFIF4_SHIFT                4                                           /**< Shift value for RXF_RXFIF4                  */
#define _RXF_IF_RXFIF4_MASK                 0x10UL                                      /**< Bit mask for RXF_RXFIF4                     */
#define _RXF_IF_RXFIF4_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for RXF_IF                     */
#define RXF_IF_RXFIF4_DEFAULT               (_RXF_IF_RXFIF4_DEFAULT << 4)               /**< Shifted mode DEFAULT for RXF_IF             */
#define RXF_IF_RXFIF5                       (0x1UL << 5)                                /**< RXF Interrupt Flag                          */
#define _RXF_IF_RXFIF5_SHIFT                5                                           /**< Shift value for RXF_RXFIF5                  */
#define _RXF_IF_RXFIF5_MASK                 0x20UL                                      /**< Bit mask for RXF_RXFIF5                     */
#define _RXF_IF_RXFIF5_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for RXF_IF                     */
#define RXF_IF_RXFIF5_DEFAULT               (_RXF_IF_RXFIF5_DEFAULT << 5)               /**< Shifted mode DEFAULT for RXF_IF             */
#define RXF_IF_RXFIF6                       (0x1UL << 6)                                /**< RXF Interrupt Flag                          */
#define _RXF_IF_RXFIF6_SHIFT                6                                           /**< Shift value for RXF_RXFIF6                  */
#define _RXF_IF_RXFIF6_MASK                 0x40UL                                      /**< Bit mask for RXF_RXFIF6                     */
#define _RXF_IF_RXFIF6_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for RXF_IF                     */
#define RXF_IF_RXFIF6_DEFAULT               (_RXF_IF_RXFIF6_DEFAULT << 6)               /**< Shifted mode DEFAULT for RXF_IF             */
#define RXF_IF_RXFIF7                       (0x1UL << 7)                                /**< RXF Interrupt Flag                          */
#define _RXF_IF_RXFIF7_SHIFT                7                                           /**< Shift value for RXF_RXFIF7                  */
#define _RXF_IF_RXFIF7_MASK                 0x80UL                                      /**< Bit mask for RXF_RXFIF7                     */
#define _RXF_IF_RXFIF7_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for RXF_IF                     */
#define RXF_IF_RXFIF7_DEFAULT               (_RXF_IF_RXFIF7_DEFAULT << 7)               /**< Shifted mode DEFAULT for RXF_IF             */
#define RXF_IF_RXFIF8                       (0x1UL << 8)                                /**< RXF Interrupt Flag                          */
#define _RXF_IF_RXFIF8_SHIFT                8                                           /**< Shift value for RXF_RXFIF8                  */
#define _RXF_IF_RXFIF8_MASK                 0x100UL                                     /**< Bit mask for RXF_RXFIF8                     */
#define _RXF_IF_RXFIF8_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for RXF_IF                     */
#define RXF_IF_RXFIF8_DEFAULT               (_RXF_IF_RXFIF8_DEFAULT << 8)               /**< Shifted mode DEFAULT for RXF_IF             */
#define RXF_IF_RXFIF9                       (0x1UL << 9)                                /**< RXF Interrupt Flag                          */
#define _RXF_IF_RXFIF9_SHIFT                9                                           /**< Shift value for RXF_RXFIF9                  */
#define _RXF_IF_RXFIF9_MASK                 0x200UL                                     /**< Bit mask for RXF_RXFIF9                     */
#define _RXF_IF_RXFIF9_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for RXF_IF                     */
#define RXF_IF_RXFIF9_DEFAULT               (_RXF_IF_RXFIF9_DEFAULT << 9)               /**< Shifted mode DEFAULT for RXF_IF             */

/* Bit fields for RXF IEN */
#define _RXF_IEN_RESETVALUE                 0x00000000UL                                /**< Default value for RXF_IEN                   */
#define _RXF_IEN_MASK                       0x000003FFUL                                /**< Mask for RXF_IEN                            */
#define RXF_IEN_RXFIEN0                     (0x1UL << 0)                                /**< RXF Interrupt Enable                        */
#define _RXF_IEN_RXFIEN0_SHIFT              0                                           /**< Shift value for RXF_RXFIEN0                 */
#define _RXF_IEN_RXFIEN0_MASK               0x1UL                                       /**< Bit mask for RXF_RXFIEN0                    */
#define _RXF_IEN_RXFIEN0_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for RXF_IEN                    */
#define RXF_IEN_RXFIEN0_DEFAULT             (_RXF_IEN_RXFIEN0_DEFAULT << 0)             /**< Shifted mode DEFAULT for RXF_IEN            */
#define RXF_IEN_RXFIEN1                     (0x1UL << 1)                                /**< RXF Interrupt Enable                        */
#define _RXF_IEN_RXFIEN1_SHIFT              1                                           /**< Shift value for RXF_RXFIEN1                 */
#define _RXF_IEN_RXFIEN1_MASK               0x2UL                                       /**< Bit mask for RXF_RXFIEN1                    */
#define _RXF_IEN_RXFIEN1_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for RXF_IEN                    */
#define RXF_IEN_RXFIEN1_DEFAULT             (_RXF_IEN_RXFIEN1_DEFAULT << 1)             /**< Shifted mode DEFAULT for RXF_IEN            */
#define RXF_IEN_RXFIEN2                     (0x1UL << 2)                                /**< RXF Interrupt Enable                        */
#define _RXF_IEN_RXFIEN2_SHIFT              2                                           /**< Shift value for RXF_RXFIEN2                 */
#define _RXF_IEN_RXFIEN2_MASK               0x4UL                                       /**< Bit mask for RXF_RXFIEN2                    */
#define _RXF_IEN_RXFIEN2_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for RXF_IEN                    */
#define RXF_IEN_RXFIEN2_DEFAULT             (_RXF_IEN_RXFIEN2_DEFAULT << 2)             /**< Shifted mode DEFAULT for RXF_IEN            */
#define RXF_IEN_RXFIEN3                     (0x1UL << 3)                                /**< RXF Interrupt Enable                        */
#define _RXF_IEN_RXFIEN3_SHIFT              3                                           /**< Shift value for RXF_RXFIEN3                 */
#define _RXF_IEN_RXFIEN3_MASK               0x8UL                                       /**< Bit mask for RXF_RXFIEN3                    */
#define _RXF_IEN_RXFIEN3_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for RXF_IEN                    */
#define RXF_IEN_RXFIEN3_DEFAULT             (_RXF_IEN_RXFIEN3_DEFAULT << 3)             /**< Shifted mode DEFAULT for RXF_IEN            */
#define RXF_IEN_RXFIEN4                     (0x1UL << 4)                                /**< RXF Interrupt Enable                        */
#define _RXF_IEN_RXFIEN4_SHIFT              4                                           /**< Shift value for RXF_RXFIEN4                 */
#define _RXF_IEN_RXFIEN4_MASK               0x10UL                                      /**< Bit mask for RXF_RXFIEN4                    */
#define _RXF_IEN_RXFIEN4_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for RXF_IEN                    */
#define RXF_IEN_RXFIEN4_DEFAULT             (_RXF_IEN_RXFIEN4_DEFAULT << 4)             /**< Shifted mode DEFAULT for RXF_IEN            */
#define RXF_IEN_RXFIEN5                     (0x1UL << 5)                                /**< RXF Interrupt Enable                        */
#define _RXF_IEN_RXFIEN5_SHIFT              5                                           /**< Shift value for RXF_RXFIEN5                 */
#define _RXF_IEN_RXFIEN5_MASK               0x20UL                                      /**< Bit mask for RXF_RXFIEN5                    */
#define _RXF_IEN_RXFIEN5_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for RXF_IEN                    */
#define RXF_IEN_RXFIEN5_DEFAULT             (_RXF_IEN_RXFIEN5_DEFAULT << 5)             /**< Shifted mode DEFAULT for RXF_IEN            */
#define RXF_IEN_RXFIEN6                     (0x1UL << 6)                                /**< RXF Interrupt Enable                        */
#define _RXF_IEN_RXFIEN6_SHIFT              6                                           /**< Shift value for RXF_RXFIEN6                 */
#define _RXF_IEN_RXFIEN6_MASK               0x40UL                                      /**< Bit mask for RXF_RXFIEN6                    */
#define _RXF_IEN_RXFIEN6_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for RXF_IEN                    */
#define RXF_IEN_RXFIEN6_DEFAULT             (_RXF_IEN_RXFIEN6_DEFAULT << 6)             /**< Shifted mode DEFAULT for RXF_IEN            */
#define RXF_IEN_RXFIEN7                     (0x1UL << 7)                                /**< RXF Interrupt Enable                        */
#define _RXF_IEN_RXFIEN7_SHIFT              7                                           /**< Shift value for RXF_RXFIEN7                 */
#define _RXF_IEN_RXFIEN7_MASK               0x80UL                                      /**< Bit mask for RXF_RXFIEN7                    */
#define _RXF_IEN_RXFIEN7_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for RXF_IEN                    */
#define RXF_IEN_RXFIEN7_DEFAULT             (_RXF_IEN_RXFIEN7_DEFAULT << 7)             /**< Shifted mode DEFAULT for RXF_IEN            */
#define RXF_IEN_RXFIEN8                     (0x1UL << 8)                                /**< RXF Interrupt Enable                        */
#define _RXF_IEN_RXFIEN8_SHIFT              8                                           /**< Shift value for RXF_RXFIEN8                 */
#define _RXF_IEN_RXFIEN8_MASK               0x100UL                                     /**< Bit mask for RXF_RXFIEN8                    */
#define _RXF_IEN_RXFIEN8_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for RXF_IEN                    */
#define RXF_IEN_RXFIEN8_DEFAULT             (_RXF_IEN_RXFIEN8_DEFAULT << 8)             /**< Shifted mode DEFAULT for RXF_IEN            */
#define RXF_IEN_RXFIEN9                     (0x1UL << 9)                                /**< RXF Interrupt Enable                        */
#define _RXF_IEN_RXFIEN9_SHIFT              9                                           /**< Shift value for RXF_RXFIEN9                 */
#define _RXF_IEN_RXFIEN9_MASK               0x200UL                                     /**< Bit mask for RXF_RXFIEN9                    */
#define _RXF_IEN_RXFIEN9_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for RXF_IEN                    */
#define RXF_IEN_RXFIEN9_DEFAULT             (_RXF_IEN_RXFIEN9_DEFAULT << 9)             /**< Shifted mode DEFAULT for RXF_IEN            */

/* Bit fields for RXF ITCTRL */
#define _RXF_ITCTRL_RESETVALUE              0x00000000UL                                /**< Default value for RXF_ITCTRL                */
#define _RXF_ITCTRL_MASK                    0x0000000FUL                                /**< Mask for RXF_ITCTRL                         */
#define RXF_ITCTRL_ITMODE                   (0x1UL << 0)                                /**< New BitField                                */
#define _RXF_ITCTRL_ITMODE_SHIFT            0                                           /**< Shift value for RXF_ITMODE                  */
#define _RXF_ITCTRL_ITMODE_MASK             0x1UL                                       /**< Bit mask for RXF_ITMODE                     */
#define _RXF_ITCTRL_ITMODE_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for RXF_ITCTRL                 */
#define _RXF_ITCTRL_ITMODE_reg              0x00000000UL                                /**< Mode reg for RXF_ITCTRL                     */
#define _RXF_ITCTRL_ITMODE_timer            0x00000001UL                                /**< Mode timer for RXF_ITCTRL                   */
#define RXF_ITCTRL_ITMODE_DEFAULT           (_RXF_ITCTRL_ITMODE_DEFAULT << 0)           /**< Shifted mode DEFAULT for RXF_ITCTRL         */
#define RXF_ITCTRL_ITMODE_reg               (_RXF_ITCTRL_ITMODE_reg << 0)               /**< Shifted mode reg for RXF_ITCTRL             */
#define RXF_ITCTRL_ITMODE_timer             (_RXF_ITCTRL_ITMODE_timer << 0)             /**< Shifted mode timer for RXF_ITCTRL           */
#define RXF_ITCTRL_ITTIMERMODE              (0x1UL << 1)                                /**< New BitField                                */
#define _RXF_ITCTRL_ITTIMERMODE_SHIFT       1                                           /**< Shift value for RXF_ITTIMERMODE             */
#define _RXF_ITCTRL_ITTIMERMODE_MASK        0x2UL                                       /**< Bit mask for RXF_ITTIMERMODE                */
#define _RXF_ITCTRL_ITTIMERMODE_DEFAULT     0x00000000UL                                /**< Mode DEFAULT for RXF_ITCTRL                 */
#define _RXF_ITCTRL_ITTIMERMODE_expired     0x00000000UL                                /**< Mode expired for RXF_ITCTRL                 */
#define _RXF_ITCTRL_ITTIMERMODE_equal       0x00000001UL                                /**< Mode equal for RXF_ITCTRL                   */
#define RXF_ITCTRL_ITTIMERMODE_DEFAULT      (_RXF_ITCTRL_ITTIMERMODE_DEFAULT << 1)      /**< Shifted mode DEFAULT for RXF_ITCTRL         */
#define RXF_ITCTRL_ITTIMERMODE_expired      (_RXF_ITCTRL_ITTIMERMODE_expired << 1)      /**< Shifted mode expired for RXF_ITCTRL         */
#define RXF_ITCTRL_ITTIMERMODE_equal        (_RXF_ITCTRL_ITTIMERMODE_equal << 1)        /**< Shifted mode equal for RXF_ITCTRL           */
#define RXF_ITCTRL_ITREG                    (0x1UL << 2)                                /**< New BitField                                */
#define _RXF_ITCTRL_ITREG_SHIFT             2                                           /**< Shift value for RXF_ITREG                   */
#define _RXF_ITCTRL_ITREG_MASK              0x4UL                                       /**< Bit mask for RXF_ITREG                      */
#define _RXF_ITCTRL_ITREG_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for RXF_ITCTRL                 */
#define RXF_ITCTRL_ITREG_DEFAULT            (_RXF_ITCTRL_ITREG_DEFAULT << 2)            /**< Shifted mode DEFAULT for RXF_ITCTRL         */
#define RXF_ITCTRL_ITTRIG                   (0x1UL << 3)                                /**< New BitField                                */
#define _RXF_ITCTRL_ITTRIG_SHIFT            3                                           /**< Shift value for RXF_ITTRIG                  */
#define _RXF_ITCTRL_ITTRIG_MASK             0x8UL                                       /**< Bit mask for RXF_ITTRIG                     */
#define _RXF_ITCTRL_ITTRIG_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for RXF_ITCTRL                 */
#define _RXF_ITCTRL_ITTRIG_pulse            0x00000000UL                                /**< Mode pulse for RXF_ITCTRL                   */
#define _RXF_ITCTRL_ITTRIG_level            0x00000001UL                                /**< Mode level for RXF_ITCTRL                   */
#define RXF_ITCTRL_ITTRIG_DEFAULT           (_RXF_ITCTRL_ITTRIG_DEFAULT << 3)           /**< Shifted mode DEFAULT for RXF_ITCTRL         */
#define RXF_ITCTRL_ITTRIG_pulse             (_RXF_ITCTRL_ITTRIG_pulse << 3)             /**< Shifted mode pulse for RXF_ITCTRL           */
#define RXF_ITCTRL_ITTRIG_level             (_RXF_ITCTRL_ITTRIG_level << 3)             /**< Shifted mode level for RXF_ITCTRL           */

/* Bit fields for RXF DATEIT */
#define _RXF_DATEIT_RESETVALUE              0x00000000UL                                /**< Default value for RXF_DATEIT                */
#define _RXF_DATEIT_MASK                    0xFFFFFFFFUL                                /**< Mask for RXF_DATEIT                         */
#define _RXF_DATEIT_DATEIT_SHIFT            0                                           /**< Shift value for RXF_DATEIT                  */
#define _RXF_DATEIT_DATEIT_MASK             0xFFFFFFFFUL                                /**< Bit mask for RXF_DATEIT                     */
#define _RXF_DATEIT_DATEIT_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for RXF_DATEIT                 */
#define RXF_DATEIT_DATEIT_DEFAULT           (_RXF_DATEIT_DATEIT_DEFAULT << 0)           /**< Shifted mode DEFAULT for RXF_DATEIT         */

/* Bit fields for RXF ITSIG */
#define _RXF_ITSIG_RESETVALUE               0x00000000UL                                /**< Default value for RXF_ITSIG                 */
#define _RXF_ITSIG_MASK                     0x00000001UL                                /**< Mask for RXF_ITSIG                          */
#define RXF_ITSIG_ITSIG                     (0x1UL << 0)                                /**< New BitField                                */
#define _RXF_ITSIG_ITSIG_SHIFT              0                                           /**< Shift value for RXF_ITSIG                   */
#define _RXF_ITSIG_ITSIG_MASK               0x1UL                                       /**< Bit mask for RXF_ITSIG                      */
#define _RXF_ITSIG_ITSIG_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for RXF_ITSIG                  */
#define RXF_ITSIG_ITSIG_DEFAULT             (_RXF_ITSIG_ITSIG_DEFAULT << 0)             /**< Shifted mode DEFAULT for RXF_ITSIG          */

/* Bit fields for RXF EVCTRL */
#define _RXF_EVCTRL_RESETVALUE              0x00000000UL                                /**< Default value for RXF_EVCTRL                */
#define _RXF_EVCTRL_MASK                    0x00000003UL                                /**< Mask for RXF_EVCTRL                         */
#define _RXF_EVCTRL_TRIG_SHIFT              0                                           /**< Shift value for RXF_TRIG                    */
#define _RXF_EVCTRL_TRIG_MASK               0x3UL                                       /**< Bit mask for RXF_TRIG                       */
#define _RXF_EVCTRL_TRIG_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for RXF_EVCTRL                 */
#define _RXF_EVCTRL_TRIG_IDLE               0x00000000UL                                /**< Mode IDLE for RXF_EVCTRL                    */
#define _RXF_EVCTRL_TRIG_RISING             0x00000001UL                                /**< Mode RISING for RXF_EVCTRL                  */
#define _RXF_EVCTRL_TRIG_FALLING            0x00000002UL                                /**< Mode FALLING for RXF_EVCTRL                 */
#define _RXF_EVCTRL_TRIG_BOTH               0x00000003UL                                /**< Mode BOTH for RXF_EVCTRL                    */
#define RXF_EVCTRL_TRIG_DEFAULT             (_RXF_EVCTRL_TRIG_DEFAULT << 0)             /**< Shifted mode DEFAULT for RXF_EVCTRL         */
#define RXF_EVCTRL_TRIG_IDLE                (_RXF_EVCTRL_TRIG_IDLE << 0)                /**< Shifted mode IDLE for RXF_EVCTRL            */
#define RXF_EVCTRL_TRIG_RISING              (_RXF_EVCTRL_TRIG_RISING << 0)              /**< Shifted mode RISING for RXF_EVCTRL          */
#define RXF_EVCTRL_TRIG_FALLING             (_RXF_EVCTRL_TRIG_FALLING << 0)             /**< Shifted mode FALLING for RXF_EVCTRL         */
#define RXF_EVCTRL_TRIG_BOTH                (_RXF_EVCTRL_TRIG_BOTH << 0)                /**< Shifted mode BOTH for RXF_EVCTRL            */

/* Bit fields for RXF EVDATE */
#define _RXF_EVDATE_RESETVALUE              0x00000000UL                                /**< Default value for RXF_EVDATE                */
#define _RXF_EVDATE_MASK                    0xFFFFFFFFUL                                /**< Mask for RXF_EVDATE                         */
#define _RXF_EVDATE_DATE_SHIFT              0                                           /**< Shift value for RXF_DATE                    */
#define _RXF_EVDATE_DATE_MASK               0xFFFFFFFFUL                                /**< Bit mask for RXF_DATE                       */
#define _RXF_EVDATE_DATE_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for RXF_EVDATE                 */
#define RXF_EVDATE_DATE_DEFAULT             (_RXF_EVDATE_DATE_DEFAULT << 0)             /**< Shifted mode DEFAULT for RXF_EVDATE         */

/** @} End of group EFR32FG25_RXF_BitFields */
/** @} End of group EFR32FG25_RXF */
/** @} End of group Parts */

#endif /* EFR32FG25_RXF_H */
