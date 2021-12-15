/**************************************************************************//**
 * @file
 * @brief EFR32FG25 CONV register and bit field definitions
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
#ifndef EFR32FG25_CONV_H
#define EFR32FG25_CONV_H
#define CONV_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_CONV CONV
 * @{
 * @brief EFR32FG25 CONV Register Declaration.
 *****************************************************************************/

/** CONV Register Declaration. */
typedef struct {
  __IM uint32_t  IPVERSION;                     /**< IP Version ID                                      */
  __IOM uint32_t EN;                            /**< Module Enable                                      */
  __IOM uint32_t SWRST;                         /**< Software Reset                                     */
  __IOM uint32_t CONNECT;                       /**< FIFO connect control                               */
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
  __IOM uint32_t FRAMELENGTH;                   /**< New Register                                       */
  __IOM uint32_t PADLENGTH;                     /**< New Register                                       */
  __IOM uint32_t PADDATA;                       /**< New Register                                       */
  __IOM uint32_t INITDATA;                      /**< New Register                                       */
  __IOM uint32_t TAILDATA;                      /**< New Register                                       */
  __IOM uint32_t DBG;                           /**< New Register                                       */
  __IM uint32_t  STAT;                          /**< New Register                                       */
  __IM uint32_t  STATLGTH;                      /**< New Register                                       */
  __IOM uint32_t IF;                            /**< Interrupt Flag                                     */
  __IOM uint32_t IEN;                           /**< Interrupt Enable                                   */
  uint32_t       RESERVED5[883U];               /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_SET;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_SET;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_SET;                   /**< FIFO connect control                               */
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
  __IOM uint32_t FRAMELENGTH_SET;               /**< New Register                                       */
  __IOM uint32_t PADLENGTH_SET;                 /**< New Register                                       */
  __IOM uint32_t PADDATA_SET;                   /**< New Register                                       */
  __IOM uint32_t INITDATA_SET;                  /**< New Register                                       */
  __IOM uint32_t TAILDATA_SET;                  /**< New Register                                       */
  __IOM uint32_t DBG_SET;                       /**< New Register                                       */
  __IM uint32_t  STAT_SET;                      /**< New Register                                       */
  __IM uint32_t  STATLGTH_SET;                  /**< New Register                                       */
  __IOM uint32_t IF_SET;                        /**< Interrupt Flag                                     */
  __IOM uint32_t IEN_SET;                       /**< Interrupt Enable                                   */
  uint32_t       RESERVED11[883U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_CLR;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_CLR;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_CLR;                   /**< FIFO connect control                               */
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
  __IOM uint32_t FRAMELENGTH_CLR;               /**< New Register                                       */
  __IOM uint32_t PADLENGTH_CLR;                 /**< New Register                                       */
  __IOM uint32_t PADDATA_CLR;                   /**< New Register                                       */
  __IOM uint32_t INITDATA_CLR;                  /**< New Register                                       */
  __IOM uint32_t TAILDATA_CLR;                  /**< New Register                                       */
  __IOM uint32_t DBG_CLR;                       /**< New Register                                       */
  __IM uint32_t  STAT_CLR;                      /**< New Register                                       */
  __IM uint32_t  STATLGTH_CLR;                  /**< New Register                                       */
  __IOM uint32_t IF_CLR;                        /**< Interrupt Flag                                     */
  __IOM uint32_t IEN_CLR;                       /**< Interrupt Enable                                   */
  uint32_t       RESERVED17[883U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_TGL;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_TGL;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_TGL;                   /**< FIFO connect control                               */
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
  __IOM uint32_t FRAMELENGTH_TGL;               /**< New Register                                       */
  __IOM uint32_t PADLENGTH_TGL;                 /**< New Register                                       */
  __IOM uint32_t PADDATA_TGL;                   /**< New Register                                       */
  __IOM uint32_t INITDATA_TGL;                  /**< New Register                                       */
  __IOM uint32_t TAILDATA_TGL;                  /**< New Register                                       */
  __IOM uint32_t DBG_TGL;                       /**< New Register                                       */
  __IM uint32_t  STAT_TGL;                      /**< New Register                                       */
  __IM uint32_t  STATLGTH_TGL;                  /**< New Register                                       */
  __IOM uint32_t IF_TGL;                        /**< Interrupt Flag                                     */
  __IOM uint32_t IEN_TGL;                       /**< Interrupt Enable                                   */
} CONV_TypeDef;
/** @} End of group EFR32FG25_CONV */

/**************************************************************************//**
 * @addtogroup EFR32FG25_CONV
 * @{
 * @defgroup EFR32FG25_CONV_BitFields CONV Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for CONV IPVERSION */
#define _CONV_IPVERSION_RESETVALUE               0x00000001UL                             /**< Default value for CONV_IPVERSION            */
#define _CONV_IPVERSION_MASK                     0xFFFFFFFFUL                             /**< Mask for CONV_IPVERSION                     */
#define _CONV_IPVERSION_IPVERSION_SHIFT          0                                        /**< Shift value for CONV_IPVERSION              */
#define _CONV_IPVERSION_IPVERSION_MASK           0xFFFFFFFFUL                             /**< Bit mask for CONV_IPVERSION                 */
#define _CONV_IPVERSION_IPVERSION_DEFAULT        0x00000001UL                             /**< Mode DEFAULT for CONV_IPVERSION             */
#define CONV_IPVERSION_IPVERSION_DEFAULT         (_CONV_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for CONV_IPVERSION     */

/* Bit fields for CONV EN */
#define _CONV_EN_RESETVALUE                      0x00000000UL                           /**< Default value for CONV_EN                   */
#define _CONV_EN_MASK                            0x00000003UL                           /**< Mask for CONV_EN                            */
#define CONV_EN_EN                               (0x1UL << 0)                           /**< Module Enable                               */
#define _CONV_EN_EN_SHIFT                        0                                      /**< Shift value for CONV_EN                     */
#define _CONV_EN_EN_MASK                         0x1UL                                  /**< Bit mask for CONV_EN                        */
#define _CONV_EN_EN_DEFAULT                      0x00000000UL                           /**< Mode DEFAULT for CONV_EN                    */
#define CONV_EN_EN_DEFAULT                       (_CONV_EN_EN_DEFAULT << 0)             /**< Shifted mode DEFAULT for CONV_EN            */
#define CONV_EN_DISABLING                        (0x1UL << 1)                           /**< Disablement Busy Status                     */
#define _CONV_EN_DISABLING_SHIFT                 1                                      /**< Shift value for CONV_DISABLING              */
#define _CONV_EN_DISABLING_MASK                  0x2UL                                  /**< Bit mask for CONV_DISABLING                 */
#define _CONV_EN_DISABLING_DEFAULT               0x00000000UL                           /**< Mode DEFAULT for CONV_EN                    */
#define CONV_EN_DISABLING_DEFAULT                (_CONV_EN_DISABLING_DEFAULT << 1)      /**< Shifted mode DEFAULT for CONV_EN            */

/* Bit fields for CONV SWRST */
#define _CONV_SWRST_RESETVALUE                   0x00000000UL                           /**< Default value for CONV_SWRST                */
#define _CONV_SWRST_MASK                         0x00000003UL                           /**< Mask for CONV_SWRST                         */
#define CONV_SWRST_SWRST                         (0x1UL << 0)                           /**< Software Reset Command                      */
#define _CONV_SWRST_SWRST_SHIFT                  0                                      /**< Shift value for CONV_SWRST                  */
#define _CONV_SWRST_SWRST_MASK                   0x1UL                                  /**< Bit mask for CONV_SWRST                     */
#define _CONV_SWRST_SWRST_DEFAULT                0x00000000UL                           /**< Mode DEFAULT for CONV_SWRST                 */
#define CONV_SWRST_SWRST_DEFAULT                 (_CONV_SWRST_SWRST_DEFAULT << 0)       /**< Shifted mode DEFAULT for CONV_SWRST         */
#define CONV_SWRST_RESETTING                     (0x1UL << 1)                           /**< Software Reset Busy Status                  */
#define _CONV_SWRST_RESETTING_SHIFT              1                                      /**< Shift value for CONV_RESETTING              */
#define _CONV_SWRST_RESETTING_MASK               0x2UL                                  /**< Bit mask for CONV_RESETTING                 */
#define _CONV_SWRST_RESETTING_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for CONV_SWRST                 */
#define CONV_SWRST_RESETTING_DEFAULT             (_CONV_SWRST_RESETTING_DEFAULT << 1)   /**< Shifted mode DEFAULT for CONV_SWRST         */

/* Bit fields for CONV CONNECT */
#define _CONV_CONNECT_RESETVALUE                 0x00000000UL                           /**< Default value for CONV_CONNECT              */
#define _CONV_CONNECT_MASK                       0x00000101UL                           /**< Mask for CONV_CONNECT                       */
#define CONV_CONNECT_IN                          (0x1UL << 0)                           /**< Input FIFO connect                          */
#define _CONV_CONNECT_IN_SHIFT                   0                                      /**< Shift value for CONV_IN                     */
#define _CONV_CONNECT_IN_MASK                    0x1UL                                  /**< Bit mask for CONV_IN                        */
#define _CONV_CONNECT_IN_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CONV_CONNECT               */
#define CONV_CONNECT_IN_DEFAULT                  (_CONV_CONNECT_IN_DEFAULT << 0)        /**< Shifted mode DEFAULT for CONV_CONNECT       */
#define CONV_CONNECT_OUT                         (0x1UL << 8)                           /**< Output FIFO connect                         */
#define _CONV_CONNECT_OUT_SHIFT                  8                                      /**< Shift value for CONV_OUT                    */
#define _CONV_CONNECT_OUT_MASK                   0x100UL                                /**< Bit mask for CONV_OUT                       */
#define _CONV_CONNECT_OUT_DEFAULT                0x00000000UL                           /**< Mode DEFAULT for CONV_CONNECT               */
#define CONV_CONNECT_OUT_DEFAULT                 (_CONV_CONNECT_OUT_DEFAULT << 8)       /**< Shifted mode DEFAULT for CONV_CONNECT       */

/* Bit fields for CONV DISCLK */
#define _CONV_DISCLK_RESETVALUE                  0x00000002UL                           /**< Default value for CONV_DISCLK               */
#define _CONV_DISCLK_MASK                        0x00000003UL                           /**< Mask for CONV_DISCLK                        */
#define _CONV_DISCLK_DISCLK_SHIFT                0                                      /**< Shift value for CONV_DISCLK                 */
#define _CONV_DISCLK_DISCLK_MASK                 0x3UL                                  /**< Bit mask for CONV_DISCLK                    */
#define _CONV_DISCLK_DISCLK_DEFAULT              0x00000002UL                           /**< Mode DEFAULT for CONV_DISCLK                */
#define _CONV_DISCLK_DISCLK_NONE                 0x00000000UL                           /**< Mode NONE for CONV_DISCLK                   */
#define _CONV_DISCLK_DISCLK_ALL                  0x00000001UL                           /**< Mode ALL for CONV_DISCLK                    */
#define _CONV_DISCLK_DISCLK_AUTO                 0x00000002UL                           /**< Mode AUTO for CONV_DISCLK                   */
#define CONV_DISCLK_DISCLK_DEFAULT               (_CONV_DISCLK_DISCLK_DEFAULT << 0)     /**< Shifted mode DEFAULT for CONV_DISCLK        */
#define CONV_DISCLK_DISCLK_NONE                  (_CONV_DISCLK_DISCLK_NONE << 0)        /**< Shifted mode NONE for CONV_DISCLK           */
#define CONV_DISCLK_DISCLK_ALL                   (_CONV_DISCLK_DISCLK_ALL << 0)         /**< Shifted mode ALL for CONV_DISCLK            */
#define CONV_DISCLK_DISCLK_AUTO                  (_CONV_DISCLK_DISCLK_AUTO << 0)        /**< Shifted mode AUTO for CONV_DISCLK           */

/* Bit fields for CONV FIFOIN */
#define _CONV_FIFOIN_RESETVALUE                  0x00000000UL                           /**< Default value for CONV_FIFOIN               */
#define _CONV_FIFOIN_MASK                        0x1FFF3F0FUL                           /**< Mask for CONV_FIFOIN                        */
#define _CONV_FIFOIN_FID_SHIFT                   0                                      /**< Shift value for CONV_FID                    */
#define _CONV_FIFOIN_FID_MASK                    0xFUL                                  /**< Bit mask for CONV_FID                       */
#define _CONV_FIFOIN_FID_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CONV_FIFOIN                */
#define CONV_FIFOIN_FID_DEFAULT                  (_CONV_FIFOIN_FID_DEFAULT << 0)        /**< Shifted mode DEFAULT for CONV_FIFOIN        */
#define _CONV_FIFOIN_CID_SHIFT                   8                                      /**< Shift value for CONV_CID                    */
#define _CONV_FIFOIN_CID_MASK                    0x3F00UL                               /**< Bit mask for CONV_CID                       */
#define _CONV_FIFOIN_CID_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CONV_FIFOIN                */
#define CONV_FIFOIN_CID_DEFAULT                  (_CONV_FIFOIN_CID_DEFAULT << 8)        /**< Shifted mode DEFAULT for CONV_FIFOIN        */
#define _CONV_FIFOIN_REM_SHIFT                   16                                     /**< Shift value for CONV_REM                    */
#define _CONV_FIFOIN_REM_MASK                    0xFF0000UL                             /**< Bit mask for CONV_REM                       */
#define _CONV_FIFOIN_REM_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CONV_FIFOIN                */
#define CONV_FIFOIN_REM_DEFAULT                  (_CONV_FIFOIN_REM_DEFAULT << 16)       /**< Shifted mode DEFAULT for CONV_FIFOIN        */
#define _CONV_FIFOIN_ALARM_SHIFT                 24                                     /**< Shift value for CONV_ALARM                  */
#define _CONV_FIFOIN_ALARM_MASK                  0x1F000000UL                           /**< Bit mask for CONV_ALARM                     */
#define _CONV_FIFOIN_ALARM_DEFAULT               0x00000000UL                           /**< Mode DEFAULT for CONV_FIFOIN                */
#define CONV_FIFOIN_ALARM_DEFAULT                (_CONV_FIFOIN_ALARM_DEFAULT << 24)     /**< Shifted mode DEFAULT for CONV_FIFOIN        */

/* Bit fields for CONV FIFOOUT */
#define _CONV_FIFOOUT_RESETVALUE                 0x00000000UL                           /**< Default value for CONV_FIFOOUT              */
#define _CONV_FIFOOUT_MASK                       0x1FFF0000UL                           /**< Mask for CONV_FIFOOUT                       */
#define _CONV_FIFOOUT_CNT_SHIFT                  16                                     /**< Shift value for CONV_CNT                    */
#define _CONV_FIFOOUT_CNT_MASK                   0xFF0000UL                             /**< Bit mask for CONV_CNT                       */
#define _CONV_FIFOOUT_CNT_DEFAULT                0x00000000UL                           /**< Mode DEFAULT for CONV_FIFOOUT               */
#define CONV_FIFOOUT_CNT_DEFAULT                 (_CONV_FIFOOUT_CNT_DEFAULT << 16)      /**< Shifted mode DEFAULT for CONV_FIFOOUT       */
#define _CONV_FIFOOUT_ALARM_SHIFT                24                                     /**< Shift value for CONV_ALARM                  */
#define _CONV_FIFOOUT_ALARM_MASK                 0x1F000000UL                           /**< Bit mask for CONV_ALARM                     */
#define _CONV_FIFOOUT_ALARM_DEFAULT              0x00000000UL                           /**< Mode DEFAULT for CONV_FIFOOUT               */
#define CONV_FIFOOUT_ALARM_DEFAULT               (_CONV_FIFOOUT_ALARM_DEFAULT << 24)    /**< Shifted mode DEFAULT for CONV_FIFOOUT       */

/* Bit fields for CONV FMTIN */
#define _CONV_FMTIN_RESETVALUE                   0x00000000UL                           /**< Default value for CONV_FMTIN                */
#define _CONV_FMTIN_MASK                         0x0000031FUL                           /**< Mask for CONV_FMTIN                         */
#define _CONV_FMTIN_ELEMSIZE_SHIFT               0                                      /**< Shift value for CONV_ELEMSIZE               */
#define _CONV_FMTIN_ELEMSIZE_MASK                0x1FUL                                 /**< Bit mask for CONV_ELEMSIZE                  */
#define _CONV_FMTIN_ELEMSIZE_DEFAULT             0x00000000UL                           /**< Mode DEFAULT for CONV_FMTIN                 */
#define CONV_FMTIN_ELEMSIZE_DEFAULT              (_CONV_FMTIN_ELEMSIZE_DEFAULT << 0)    /**< Shifted mode DEFAULT for CONV_FMTIN         */
#define _CONV_FMTIN_ELEMNB_SHIFT                 8                                      /**< Shift value for CONV_ELEMNB                 */
#define _CONV_FMTIN_ELEMNB_MASK                  0x300UL                                /**< Bit mask for CONV_ELEMNB                    */
#define _CONV_FMTIN_ELEMNB_DEFAULT               0x00000000UL                           /**< Mode DEFAULT for CONV_FMTIN                 */
#define _CONV_FMTIN_ELEMNB_ONE                   0x00000000UL                           /**< Mode ONE for CONV_FMTIN                     */
#define _CONV_FMTIN_ELEMNB_TWO                   0x00000001UL                           /**< Mode TWO for CONV_FMTIN                     */
#define _CONV_FMTIN_ELEMNB_FOUR                  0x00000002UL                           /**< Mode FOUR for CONV_FMTIN                    */
#define CONV_FMTIN_ELEMNB_DEFAULT                (_CONV_FMTIN_ELEMNB_DEFAULT << 8)      /**< Shifted mode DEFAULT for CONV_FMTIN         */
#define CONV_FMTIN_ELEMNB_ONE                    (_CONV_FMTIN_ELEMNB_ONE << 8)          /**< Shifted mode ONE for CONV_FMTIN             */
#define CONV_FMTIN_ELEMNB_TWO                    (_CONV_FMTIN_ELEMNB_TWO << 8)          /**< Shifted mode TWO for CONV_FMTIN             */
#define CONV_FMTIN_ELEMNB_FOUR                   (_CONV_FMTIN_ELEMNB_FOUR << 8)         /**< Shifted mode FOUR for CONV_FMTIN            */

/* Bit fields for CONV FMTOUT */
#define _CONV_FMTOUT_RESETVALUE                  0x00000000UL                           /**< Default value for CONV_FMTOUT               */
#define _CONV_FMTOUT_MASK                        0x0000031FUL                           /**< Mask for CONV_FMTOUT                        */
#define _CONV_FMTOUT_ELEMSIZE_SHIFT              0                                      /**< Shift value for CONV_ELEMSIZE               */
#define _CONV_FMTOUT_ELEMSIZE_MASK               0x1FUL                                 /**< Bit mask for CONV_ELEMSIZE                  */
#define _CONV_FMTOUT_ELEMSIZE_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for CONV_FMTOUT                */
#define CONV_FMTOUT_ELEMSIZE_DEFAULT             (_CONV_FMTOUT_ELEMSIZE_DEFAULT << 0)   /**< Shifted mode DEFAULT for CONV_FMTOUT        */
#define _CONV_FMTOUT_ELEMNB_SHIFT                8                                      /**< Shift value for CONV_ELEMNB                 */
#define _CONV_FMTOUT_ELEMNB_MASK                 0x300UL                                /**< Bit mask for CONV_ELEMNB                    */
#define _CONV_FMTOUT_ELEMNB_DEFAULT              0x00000000UL                           /**< Mode DEFAULT for CONV_FMTOUT                */
#define _CONV_FMTOUT_ELEMNB_ONE                  0x00000000UL                           /**< Mode ONE for CONV_FMTOUT                    */
#define _CONV_FMTOUT_ELEMNB_TWO                  0x00000001UL                           /**< Mode TWO for CONV_FMTOUT                    */
#define _CONV_FMTOUT_ELEMNB_FOUR                 0x00000002UL                           /**< Mode FOUR for CONV_FMTOUT                   */
#define CONV_FMTOUT_ELEMNB_DEFAULT               (_CONV_FMTOUT_ELEMNB_DEFAULT << 8)     /**< Shifted mode DEFAULT for CONV_FMTOUT        */
#define CONV_FMTOUT_ELEMNB_ONE                   (_CONV_FMTOUT_ELEMNB_ONE << 8)         /**< Shifted mode ONE for CONV_FMTOUT            */
#define CONV_FMTOUT_ELEMNB_TWO                   (_CONV_FMTOUT_ELEMNB_TWO << 8)         /**< Shifted mode TWO for CONV_FMTOUT            */
#define CONV_FMTOUT_ELEMNB_FOUR                  (_CONV_FMTOUT_ELEMNB_FOUR << 8)        /**< Shifted mode FOUR for CONV_FMTOUT           */

/* Bit fields for CONV CTRL */
#define _CONV_CTRL_RESETVALUE                    0x0000021CUL                              /**< Default value for CONV_CTRL                 */
#define _CONV_CTRL_MASK                          0xE03DDEFFUL                              /**< Mask for CONV_CTRL                          */
#define CONV_CTRL_INPUTMODE                      (0x1UL << 0)                              /**< New BitField                                */
#define _CONV_CTRL_INPUTMODE_SHIFT               0                                         /**< Shift value for CONV_INPUTMODE              */
#define _CONV_CTRL_INPUTMODE_MASK                0x1UL                                     /**< Bit mask for CONV_INPUTMODE                 */
#define _CONV_CTRL_INPUTMODE_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for CONV_CTRL                  */
#define _CONV_CTRL_INPUTMODE_PARTIAL             0x00000000UL                              /**< Mode PARTIAL for CONV_CTRL                  */
#define _CONV_CTRL_INPUTMODE_FULL                0x00000001UL                              /**< Mode FULL for CONV_CTRL                     */
#define CONV_CTRL_INPUTMODE_DEFAULT              (_CONV_CTRL_INPUTMODE_DEFAULT << 0)       /**< Shifted mode DEFAULT for CONV_CTRL          */
#define CONV_CTRL_INPUTMODE_PARTIAL              (_CONV_CTRL_INPUTMODE_PARTIAL << 0)       /**< Shifted mode PARTIAL for CONV_CTRL          */
#define CONV_CTRL_INPUTMODE_FULL                 (_CONV_CTRL_INPUTMODE_FULL << 0)          /**< Shifted mode FULL for CONV_CTRL             */
#define CONV_CTRL_STRUCTURE                      (0x1UL << 1)                              /**< New BitField                                */
#define _CONV_CTRL_STRUCTURE_SHIFT               1                                         /**< Shift value for CONV_STRUCTURE              */
#define _CONV_CTRL_STRUCTURE_MASK                0x2UL                                     /**< Bit mask for CONV_STRUCTURE                 */
#define _CONV_CTRL_STRUCTURE_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for CONV_CTRL                  */
#define _CONV_CTRL_STRUCTURE_non_recursive       0x00000000UL                              /**< Mode non_recursive for CONV_CTRL            */
#define _CONV_CTRL_STRUCTURE_recursive           0x00000001UL                              /**< Mode recursive for CONV_CTRL                */
#define CONV_CTRL_STRUCTURE_DEFAULT              (_CONV_CTRL_STRUCTURE_DEFAULT << 1)       /**< Shifted mode DEFAULT for CONV_CTRL          */
#define CONV_CTRL_STRUCTURE_non_recursive        (_CONV_CTRL_STRUCTURE_non_recursive << 1) /**< Shifted mode non_recursive for CONV_CTRL    */
#define CONV_CTRL_STRUCTURE_recursive            (_CONV_CTRL_STRUCTURE_recursive << 1)     /**< Shifted mode recursive for CONV_CTRL        */
#define _CONV_CTRL_CONSTLENGTH_SHIFT             2                                         /**< Shift value for CONV_CONSTLENGTH            */
#define _CONV_CTRL_CONSTLENGTH_MASK              0x1CUL                                    /**< Bit mask for CONV_CONSTLENGTH               */
#define _CONV_CTRL_CONSTLENGTH_DEFAULT           0x00000007UL                              /**< Mode DEFAULT for CONV_CTRL                  */
#define CONV_CTRL_CONSTLENGTH_DEFAULT            (_CONV_CTRL_CONSTLENGTH_DEFAULT << 2)     /**< Shifted mode DEFAULT for CONV_CTRL          */
#define _CONV_CTRL_PUNCTPERIOD_SHIFT             5                                         /**< Shift value for CONV_PUNCTPERIOD            */
#define _CONV_CTRL_PUNCTPERIOD_MASK              0xE0UL                                    /**< Bit mask for CONV_PUNCTPERIOD               */
#define _CONV_CTRL_PUNCTPERIOD_DEFAULT           0x00000000UL                              /**< Mode DEFAULT for CONV_CTRL                  */
#define _CONV_CTRL_PUNCTPERIOD_ONE               0x00000000UL                              /**< Mode ONE for CONV_CTRL                      */
#define _CONV_CTRL_PUNCTPERIOD_TWO               0x00000001UL                              /**< Mode TWO for CONV_CTRL                      */
#define _CONV_CTRL_PUNCTPERIOD_THREE             0x00000002UL                              /**< Mode THREE for CONV_CTRL                    */
#define _CONV_CTRL_PUNCTPERIOD_FOUR              0x00000003UL                              /**< Mode FOUR for CONV_CTRL                     */
#define _CONV_CTRL_PUNCTPERIOD_FIVE              0x00000004UL                              /**< Mode FIVE for CONV_CTRL                     */
#define _CONV_CTRL_PUNCTPERIOD_SIX               0x00000005UL                              /**< Mode SIX for CONV_CTRL                      */
#define _CONV_CTRL_PUNCTPERIOD_SEVEN             0x00000006UL                              /**< Mode SEVEN for CONV_CTRL                    */
#define _CONV_CTRL_PUNCTPERIOD_EIGHT             0x00000007UL                              /**< Mode EIGHT for CONV_CTRL                    */
#define CONV_CTRL_PUNCTPERIOD_DEFAULT            (_CONV_CTRL_PUNCTPERIOD_DEFAULT << 5)     /**< Shifted mode DEFAULT for CONV_CTRL          */
#define CONV_CTRL_PUNCTPERIOD_ONE                (_CONV_CTRL_PUNCTPERIOD_ONE << 5)         /**< Shifted mode ONE for CONV_CTRL              */
#define CONV_CTRL_PUNCTPERIOD_TWO                (_CONV_CTRL_PUNCTPERIOD_TWO << 5)         /**< Shifted mode TWO for CONV_CTRL              */
#define CONV_CTRL_PUNCTPERIOD_THREE              (_CONV_CTRL_PUNCTPERIOD_THREE << 5)       /**< Shifted mode THREE for CONV_CTRL            */
#define CONV_CTRL_PUNCTPERIOD_FOUR               (_CONV_CTRL_PUNCTPERIOD_FOUR << 5)        /**< Shifted mode FOUR for CONV_CTRL             */
#define CONV_CTRL_PUNCTPERIOD_FIVE               (_CONV_CTRL_PUNCTPERIOD_FIVE << 5)        /**< Shifted mode FIVE for CONV_CTRL             */
#define CONV_CTRL_PUNCTPERIOD_SIX                (_CONV_CTRL_PUNCTPERIOD_SIX << 5)         /**< Shifted mode SIX for CONV_CTRL              */
#define CONV_CTRL_PUNCTPERIOD_SEVEN              (_CONV_CTRL_PUNCTPERIOD_SEVEN << 5)       /**< Shifted mode SEVEN for CONV_CTRL            */
#define CONV_CTRL_PUNCTPERIOD_EIGHT              (_CONV_CTRL_PUNCTPERIOD_EIGHT << 5)       /**< Shifted mode EIGHT for CONV_CTRL            */
#define CONV_CTRL_TAILEN                         (0x1UL << 9)                              /**< New BitField                                */
#define _CONV_CTRL_TAILEN_SHIFT                  9                                         /**< Shift value for CONV_TAILEN                 */
#define _CONV_CTRL_TAILEN_MASK                   0x200UL                                   /**< Bit mask for CONV_TAILEN                    */
#define _CONV_CTRL_TAILEN_DEFAULT                0x00000001UL                              /**< Mode DEFAULT for CONV_CTRL                  */
#define CONV_CTRL_TAILEN_DEFAULT                 (_CONV_CTRL_TAILEN_DEFAULT << 9)          /**< Shifted mode DEFAULT for CONV_CTRL          */
#define _CONV_CTRL_INV_SHIFT                     10                                        /**< Shift value for CONV_INV                    */
#define _CONV_CTRL_INV_MASK                      0x1C00UL                                  /**< Bit mask for CONV_INV                       */
#define _CONV_CTRL_INV_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for CONV_CTRL                  */
#define CONV_CTRL_INV_DEFAULT                    (_CONV_CTRL_INV_DEFAULT << 10)            /**< Shifted mode DEFAULT for CONV_CTRL          */
#define _CONV_CTRL_NONSYST_SHIFT                 14                                        /**< Shift value for CONV_NONSYST                */
#define _CONV_CTRL_NONSYST_MASK                  0x1C000UL                                 /**< Bit mask for CONV_NONSYST                   */
#define _CONV_CTRL_NONSYST_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for CONV_CTRL                  */
#define CONV_CTRL_NONSYST_DEFAULT                (_CONV_CTRL_NONSYST_DEFAULT << 14)        /**< Shifted mode DEFAULT for CONV_CTRL          */
#define _CONV_CTRL_RECURSEL_SHIFT                18                                        /**< Shift value for CONV_RECURSEL               */
#define _CONV_CTRL_RECURSEL_MASK                 0xC0000UL                                 /**< Bit mask for CONV_RECURSEL                  */
#define _CONV_CTRL_RECURSEL_DEFAULT              0x00000000UL                              /**< Mode DEFAULT for CONV_CTRL                  */
#define CONV_CTRL_RECURSEL_DEFAULT               (_CONV_CTRL_RECURSEL_DEFAULT << 18)       /**< Shifted mode DEFAULT for CONV_CTRL          */
#define CONV_CTRL_ONGOING                        (0x1UL << 20)                             /**< New BitField                                */
#define _CONV_CTRL_ONGOING_SHIFT                 20                                        /**< Shift value for CONV_ONGOING                */
#define _CONV_CTRL_ONGOING_MASK                  0x100000UL                                /**< Bit mask for CONV_ONGOING                   */
#define _CONV_CTRL_ONGOING_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for CONV_CTRL                  */
#define CONV_CTRL_ONGOING_DEFAULT                (_CONV_CTRL_ONGOING_DEFAULT << 20)        /**< Shifted mode DEFAULT for CONV_CTRL          */
#define CONV_CTRL_RST                            (0x1UL << 21)                             /**< New BitField                                */
#define _CONV_CTRL_RST_SHIFT                     21                                        /**< Shift value for CONV_RST                    */
#define _CONV_CTRL_RST_MASK                      0x200000UL                                /**< Bit mask for CONV_RST                       */
#define _CONV_CTRL_RST_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for CONV_CTRL                  */
#define CONV_CTRL_RST_DEFAULT                    (_CONV_CTRL_RST_DEFAULT << 21)            /**< Shifted mode DEFAULT for CONV_CTRL          */
#define _CONV_CTRL_BYTESWAP_SHIFT                29                                        /**< Shift value for CONV_BYTESWAP               */
#define _CONV_CTRL_BYTESWAP_MASK                 0x60000000UL                              /**< Bit mask for CONV_BYTESWAP                  */
#define _CONV_CTRL_BYTESWAP_DEFAULT              0x00000000UL                              /**< Mode DEFAULT for CONV_CTRL                  */
#define _CONV_CTRL_BYTESWAP_DISABLED             0x00000000UL                              /**< Mode DISABLED for CONV_CTRL                 */
#define _CONV_CTRL_BYTESWAP_HALFWORD             0x00000001UL                              /**< Mode HALFWORD for CONV_CTRL                 */
#define _CONV_CTRL_BYTESWAP_WORD                 0x00000002UL                              /**< Mode WORD for CONV_CTRL                     */
#define CONV_CTRL_BYTESWAP_DEFAULT               (_CONV_CTRL_BYTESWAP_DEFAULT << 29)       /**< Shifted mode DEFAULT for CONV_CTRL          */
#define CONV_CTRL_BYTESWAP_DISABLED              (_CONV_CTRL_BYTESWAP_DISABLED << 29)      /**< Shifted mode DISABLED for CONV_CTRL         */
#define CONV_CTRL_BYTESWAP_HALFWORD              (_CONV_CTRL_BYTESWAP_HALFWORD << 29)      /**< Shifted mode HALFWORD for CONV_CTRL         */
#define CONV_CTRL_BYTESWAP_WORD                  (_CONV_CTRL_BYTESWAP_WORD << 29)          /**< Shifted mode WORD for CONV_CTRL             */
#define CONV_CTRL_BITSWAP                        (0x1UL << 31)                             /**< New BitField                                */
#define _CONV_CTRL_BITSWAP_SHIFT                 31                                        /**< Shift value for CONV_BITSWAP                */
#define _CONV_CTRL_BITSWAP_MASK                  0x80000000UL                              /**< Bit mask for CONV_BITSWAP                   */
#define _CONV_CTRL_BITSWAP_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for CONV_CTRL                  */
#define CONV_CTRL_BITSWAP_DEFAULT                (_CONV_CTRL_BITSWAP_DEFAULT << 31)        /**< Shifted mode DEFAULT for CONV_CTRL          */

/* Bit fields for CONV POLY */
#define _CONV_POLY_RESETVALUE                    0x006D6D6DUL                           /**< Default value for CONV_POLY                 */
#define _CONV_POLY_MASK                          0x007F7F7FUL                           /**< Mask for CONV_POLY                          */
#define _CONV_POLY_POLY0_SHIFT                   0                                      /**< Shift value for CONV_POLY0                  */
#define _CONV_POLY_POLY0_MASK                    0x7FUL                                 /**< Bit mask for CONV_POLY0                     */
#define _CONV_POLY_POLY0_DEFAULT                 0x0000006DUL                           /**< Mode DEFAULT for CONV_POLY                  */
#define CONV_POLY_POLY0_DEFAULT                  (_CONV_POLY_POLY0_DEFAULT << 0)        /**< Shifted mode DEFAULT for CONV_POLY          */
#define _CONV_POLY_POLY1_SHIFT                   8                                      /**< Shift value for CONV_POLY1                  */
#define _CONV_POLY_POLY1_MASK                    0x7F00UL                               /**< Bit mask for CONV_POLY1                     */
#define _CONV_POLY_POLY1_DEFAULT                 0x0000006DUL                           /**< Mode DEFAULT for CONV_POLY                  */
#define CONV_POLY_POLY1_DEFAULT                  (_CONV_POLY_POLY1_DEFAULT << 8)        /**< Shifted mode DEFAULT for CONV_POLY          */
#define _CONV_POLY_POLY2_SHIFT                   16                                     /**< Shift value for CONV_POLY2                  */
#define _CONV_POLY_POLY2_MASK                    0x7F0000UL                             /**< Bit mask for CONV_POLY2                     */
#define _CONV_POLY_POLY2_DEFAULT                 0x0000006DUL                           /**< Mode DEFAULT for CONV_POLY                  */
#define CONV_POLY_POLY2_DEFAULT                  (_CONV_POLY_POLY2_DEFAULT << 16)       /**< Shifted mode DEFAULT for CONV_POLY          */

/* Bit fields for CONV PUNCT */
#define _CONV_PUNCT_RESETVALUE                   0x00010101UL                           /**< Default value for CONV_PUNCT                */
#define _CONV_PUNCT_MASK                         0x00FFFFFFUL                           /**< Mask for CONV_PUNCT                         */
#define _CONV_PUNCT_PUNCT0_SHIFT                 0                                      /**< Shift value for CONV_PUNCT0                 */
#define _CONV_PUNCT_PUNCT0_MASK                  0xFFUL                                 /**< Bit mask for CONV_PUNCT0                    */
#define _CONV_PUNCT_PUNCT0_DEFAULT               0x00000001UL                           /**< Mode DEFAULT for CONV_PUNCT                 */
#define CONV_PUNCT_PUNCT0_DEFAULT                (_CONV_PUNCT_PUNCT0_DEFAULT << 0)      /**< Shifted mode DEFAULT for CONV_PUNCT         */
#define _CONV_PUNCT_PUNCT1_SHIFT                 8                                      /**< Shift value for CONV_PUNCT1                 */
#define _CONV_PUNCT_PUNCT1_MASK                  0xFF00UL                               /**< Bit mask for CONV_PUNCT1                    */
#define _CONV_PUNCT_PUNCT1_DEFAULT               0x00000001UL                           /**< Mode DEFAULT for CONV_PUNCT                 */
#define CONV_PUNCT_PUNCT1_DEFAULT                (_CONV_PUNCT_PUNCT1_DEFAULT << 8)      /**< Shifted mode DEFAULT for CONV_PUNCT         */
#define _CONV_PUNCT_PUNCT2_SHIFT                 16                                     /**< Shift value for CONV_PUNCT2                 */
#define _CONV_PUNCT_PUNCT2_MASK                  0xFF0000UL                             /**< Bit mask for CONV_PUNCT2                    */
#define _CONV_PUNCT_PUNCT2_DEFAULT               0x00000001UL                           /**< Mode DEFAULT for CONV_PUNCT                 */
#define CONV_PUNCT_PUNCT2_DEFAULT                (_CONV_PUNCT_PUNCT2_DEFAULT << 16)     /**< Shifted mode DEFAULT for CONV_PUNCT         */

/* Bit fields for CONV FRAMELENGTH */
#define _CONV_FRAMELENGTH_RESETVALUE             0x00000000UL                                 /**< Default value for CONV_FRAMELENGTH          */
#define _CONV_FRAMELENGTH_MASK                   0x0000FFFFUL                                 /**< Mask for CONV_FRAMELENGTH                   */
#define _CONV_FRAMELENGTH_FRAMELENGTH_SHIFT      0                                            /**< Shift value for CONV_FRAMELENGTH            */
#define _CONV_FRAMELENGTH_FRAMELENGTH_MASK       0xFFFFUL                                     /**< Bit mask for CONV_FRAMELENGTH               */
#define _CONV_FRAMELENGTH_FRAMELENGTH_DEFAULT    0x00000000UL                                 /**< Mode DEFAULT for CONV_FRAMELENGTH           */
#define CONV_FRAMELENGTH_FRAMELENGTH_DEFAULT     (_CONV_FRAMELENGTH_FRAMELENGTH_DEFAULT << 0) /**< Shifted mode DEFAULT for CONV_FRAMELENGTH   */

/* Bit fields for CONV PADLENGTH */
#define _CONV_PADLENGTH_RESETVALUE               0x00000000UL                             /**< Default value for CONV_PADLENGTH            */
#define _CONV_PADLENGTH_MASK                     0x00000FFFUL                             /**< Mask for CONV_PADLENGTH                     */
#define _CONV_PADLENGTH_PADLENGTH_SHIFT          0                                        /**< Shift value for CONV_PADLENGTH              */
#define _CONV_PADLENGTH_PADLENGTH_MASK           0xFFFUL                                  /**< Bit mask for CONV_PADLENGTH                 */
#define _CONV_PADLENGTH_PADLENGTH_DEFAULT        0x00000000UL                             /**< Mode DEFAULT for CONV_PADLENGTH             */
#define CONV_PADLENGTH_PADLENGTH_DEFAULT         (_CONV_PADLENGTH_PADLENGTH_DEFAULT << 0) /**< Shifted mode DEFAULT for CONV_PADLENGTH     */

/* Bit fields for CONV PADDATA */
#define _CONV_PADDATA_RESETVALUE                 0x00000000UL                           /**< Default value for CONV_PADDATA              */
#define _CONV_PADDATA_MASK                       0xFFFFFFFFUL                           /**< Mask for CONV_PADDATA                       */
#define _CONV_PADDATA_PADDATA_SHIFT              0                                      /**< Shift value for CONV_PADDATA                */
#define _CONV_PADDATA_PADDATA_MASK               0xFFFFFFFFUL                           /**< Bit mask for CONV_PADDATA                   */
#define _CONV_PADDATA_PADDATA_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for CONV_PADDATA               */
#define CONV_PADDATA_PADDATA_DEFAULT             (_CONV_PADDATA_PADDATA_DEFAULT << 0)   /**< Shifted mode DEFAULT for CONV_PADDATA       */

/* Bit fields for CONV INITDATA */
#define _CONV_INITDATA_RESETVALUE                0x00000000UL                           /**< Default value for CONV_INITDATA             */
#define _CONV_INITDATA_MASK                      0x0000003FUL                           /**< Mask for CONV_INITDATA                      */
#define _CONV_INITDATA_INITDATA_SHIFT            0                                      /**< Shift value for CONV_INITDATA               */
#define _CONV_INITDATA_INITDATA_MASK             0x3FUL                                 /**< Bit mask for CONV_INITDATA                  */
#define _CONV_INITDATA_INITDATA_DEFAULT          0x00000000UL                           /**< Mode DEFAULT for CONV_INITDATA              */
#define CONV_INITDATA_INITDATA_DEFAULT           (_CONV_INITDATA_INITDATA_DEFAULT << 0) /**< Shifted mode DEFAULT for CONV_INITDATA      */

/* Bit fields for CONV TAILDATA */
#define _CONV_TAILDATA_RESETVALUE                0x00000000UL                           /**< Default value for CONV_TAILDATA             */
#define _CONV_TAILDATA_MASK                      0x0000003FUL                           /**< Mask for CONV_TAILDATA                      */
#define _CONV_TAILDATA_TAILDATA_SHIFT            0                                      /**< Shift value for CONV_TAILDATA               */
#define _CONV_TAILDATA_TAILDATA_MASK             0x3FUL                                 /**< Bit mask for CONV_TAILDATA                  */
#define _CONV_TAILDATA_TAILDATA_DEFAULT          0x00000000UL                           /**< Mode DEFAULT for CONV_TAILDATA              */
#define CONV_TAILDATA_TAILDATA_DEFAULT           (_CONV_TAILDATA_TAILDATA_DEFAULT << 0) /**< Shifted mode DEFAULT for CONV_TAILDATA      */

/* Bit fields for CONV DBG */
#define _CONV_DBG_RESETVALUE                     0x00000402UL                           /**< Default value for CONV_DBG                  */
#define _CONV_DBG_MASK                           0x000007FFUL                           /**< Mask for CONV_DBG                           */
#define _CONV_DBG_LGTH_SHIFT                     0                                      /**< Shift value for CONV_LGTH                   */
#define _CONV_DBG_LGTH_MASK                      0x3UL                                  /**< Bit mask for CONV_LGTH                      */
#define _CONV_DBG_LGTH_DEFAULT                   0x00000002UL                           /**< Mode DEFAULT for CONV_DBG                   */
#define _CONV_DBG_LGTH_PAYLOAD                   0x00000000UL                           /**< Mode PAYLOAD for CONV_DBG                   */
#define _CONV_DBG_LGTH_PAYLOAD_TAIL              0x00000001UL                           /**< Mode PAYLOAD_TAIL for CONV_DBG              */
#define _CONV_DBG_LGTH_PAYLOAD_TAIL_PAD          0x00000002UL                           /**< Mode PAYLOAD_TAIL_PAD for CONV_DBG          */
#define CONV_DBG_LGTH_DEFAULT                    (_CONV_DBG_LGTH_DEFAULT << 0)          /**< Shifted mode DEFAULT for CONV_DBG           */
#define CONV_DBG_LGTH_PAYLOAD                    (_CONV_DBG_LGTH_PAYLOAD << 0)          /**< Shifted mode PAYLOAD for CONV_DBG           */
#define CONV_DBG_LGTH_PAYLOAD_TAIL               (_CONV_DBG_LGTH_PAYLOAD_TAIL << 0)     /**< Shifted mode PAYLOAD_TAIL for CONV_DBG      */
#define CONV_DBG_LGTH_PAYLOAD_TAIL_PAD           (_CONV_DBG_LGTH_PAYLOAD_TAIL_PAD << 0) /**< Shifted mode PAYLOAD_TAIL_PAD for CONV_DBG  */
#define _CONV_DBG_SOFTMODE_SHIFT                 2                                      /**< Shift value for CONV_SOFTMODE               */
#define _CONV_DBG_SOFTMODE_MASK                  0xCUL                                  /**< Bit mask for CONV_SOFTMODE                  */
#define _CONV_DBG_SOFTMODE_DEFAULT               0x00000000UL                           /**< Mode DEFAULT for CONV_DBG                   */
#define _CONV_DBG_SOFTMODE_OFF                   0x00000000UL                           /**< Mode OFF for CONV_DBG                       */
#define _CONV_DBG_SOFTMODE_NO_INV                0x00000001UL                           /**< Mode NO_INV for CONV_DBG                    */
#define _CONV_DBG_SOFTMODE_INV                   0x00000002UL                           /**< Mode INV for CONV_DBG                       */
#define CONV_DBG_SOFTMODE_DEFAULT                (_CONV_DBG_SOFTMODE_DEFAULT << 2)      /**< Shifted mode DEFAULT for CONV_DBG           */
#define CONV_DBG_SOFTMODE_OFF                    (_CONV_DBG_SOFTMODE_OFF << 2)          /**< Shifted mode OFF for CONV_DBG               */
#define CONV_DBG_SOFTMODE_NO_INV                 (_CONV_DBG_SOFTMODE_NO_INV << 2)       /**< Shifted mode NO_INV for CONV_DBG            */
#define CONV_DBG_SOFTMODE_INV                    (_CONV_DBG_SOFTMODE_INV << 2)          /**< Shifted mode INV for CONV_DBG               */
#define _CONV_DBG_SOFTVAL_SHIFT                  4                                      /**< Shift value for CONV_SOFTVAL                */
#define _CONV_DBG_SOFTVAL_MASK                   0x7F0UL                                /**< Bit mask for CONV_SOFTVAL                   */
#define _CONV_DBG_SOFTVAL_DEFAULT                0x00000040UL                           /**< Mode DEFAULT for CONV_DBG                   */
#define CONV_DBG_SOFTVAL_DEFAULT                 (_CONV_DBG_SOFTVAL_DEFAULT << 4)       /**< Shifted mode DEFAULT for CONV_DBG           */

/* Bit fields for CONV STAT */
#define _CONV_STAT_RESETVALUE                    0x00000000UL                           /**< Default value for CONV_STAT                 */
#define _CONV_STAT_MASK                          0x00FF077FUL                           /**< Mask for CONV_STAT                          */
#define _CONV_STAT_STATE_SHIFT                   0                                      /**< Shift value for CONV_STATE                  */
#define _CONV_STAT_STATE_MASK                    0x7FUL                                 /**< Bit mask for CONV_STATE                     */
#define _CONV_STAT_STATE_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CONV_STAT                  */
#define CONV_STAT_STATE_DEFAULT                  (_CONV_STAT_STATE_DEFAULT << 0)        /**< Shifted mode DEFAULT for CONV_STAT          */
#define _CONV_STAT_DOUT_SHIFT                    8                                      /**< Shift value for CONV_DOUT                   */
#define _CONV_STAT_DOUT_MASK                     0x700UL                                /**< Bit mask for CONV_DOUT                      */
#define _CONV_STAT_DOUT_DEFAULT                  0x00000000UL                           /**< Mode DEFAULT for CONV_STAT                  */
#define CONV_STAT_DOUT_DEFAULT                   (_CONV_STAT_DOUT_DEFAULT << 8)         /**< Shifted mode DEFAULT for CONV_STAT          */
#define _CONV_STAT_PUNCT_SHIFT                   16                                     /**< Shift value for CONV_PUNCT                  */
#define _CONV_STAT_PUNCT_MASK                    0xFF0000UL                             /**< Bit mask for CONV_PUNCT                     */
#define _CONV_STAT_PUNCT_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CONV_STAT                  */
#define CONV_STAT_PUNCT_DEFAULT                  (_CONV_STAT_PUNCT_DEFAULT << 16)       /**< Shifted mode DEFAULT for CONV_STAT          */

/* Bit fields for CONV STATLGTH */
#define _CONV_STATLGTH_RESETVALUE                0x00000000UL                           /**< Default value for CONV_STATLGTH             */
#define _CONV_STATLGTH_MASK                      0x0003FFFFUL                           /**< Mask for CONV_STATLGTH                      */
#define _CONV_STATLGTH_STATLGTH_SHIFT            0                                      /**< Shift value for CONV_STATLGTH               */
#define _CONV_STATLGTH_STATLGTH_MASK             0x3FFFFUL                              /**< Bit mask for CONV_STATLGTH                  */
#define _CONV_STATLGTH_STATLGTH_DEFAULT          0x00000000UL                           /**< Mode DEFAULT for CONV_STATLGTH              */
#define CONV_STATLGTH_STATLGTH_DEFAULT           (_CONV_STATLGTH_STATLGTH_DEFAULT << 0) /**< Shifted mode DEFAULT for CONV_STATLGTH      */

/* Bit fields for CONV IF */
#define _CONV_IF_RESETVALUE                      0x00000000UL                           /**< Default value for CONV_IF                   */
#define _CONV_IF_MASK                            0x00000001UL                           /**< Mask for CONV_IF                            */
#define CONV_IF_DONE                             (0x1UL << 0)                           /**< New BitField                                */
#define _CONV_IF_DONE_SHIFT                      0                                      /**< Shift value for CONV_DONE                   */
#define _CONV_IF_DONE_MASK                       0x1UL                                  /**< Bit mask for CONV_DONE                      */
#define _CONV_IF_DONE_DEFAULT                    0x00000000UL                           /**< Mode DEFAULT for CONV_IF                    */
#define CONV_IF_DONE_DEFAULT                     (_CONV_IF_DONE_DEFAULT << 0)           /**< Shifted mode DEFAULT for CONV_IF            */

/* Bit fields for CONV IEN */
#define _CONV_IEN_RESETVALUE                     0x00000000UL                           /**< Default value for CONV_IEN                  */
#define _CONV_IEN_MASK                           0x00000001UL                           /**< Mask for CONV_IEN                           */
#define CONV_IEN_DONE                            (0x1UL << 0)                           /**< New BitField                                */
#define _CONV_IEN_DONE_SHIFT                     0                                      /**< Shift value for CONV_DONE                   */
#define _CONV_IEN_DONE_MASK                      0x1UL                                  /**< Bit mask for CONV_DONE                      */
#define _CONV_IEN_DONE_DEFAULT                   0x00000000UL                           /**< Mode DEFAULT for CONV_IEN                   */
#define CONV_IEN_DONE_DEFAULT                    (_CONV_IEN_DONE_DEFAULT << 0)          /**< Shifted mode DEFAULT for CONV_IEN           */

/** @} End of group EFR32FG25_CONV_BitFields */
/** @} End of group EFR32FG25_CONV */
/** @} End of group Parts */

#endif /* EFR32FG25_CONV_H */
