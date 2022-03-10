/**************************************************************************//**
 * @file
 * @brief EFR32FG25 FRCIF register and bit field definitions
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
#ifndef EFR32FG25_FRCIF_H
#define EFR32FG25_FRCIF_H
#define FRCIF_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_FRCIF FRCIF
 * @{
 * @brief EFR32FG25 FRCIF Register Declaration.
 *****************************************************************************/

/** FRCIF Register Declaration. */
typedef struct {
  __IM uint32_t  IPVERSION;                     /**< IP Version ID                                      */
  __IOM uint32_t EN;                            /**< Module Enable                                      */
  __IOM uint32_t SWRST;                         /**< Software Reset                                     */
  __IOM uint32_t CONNECT;                       /**< New Register                                       */
  __IOM uint32_t DISCLK;                        /**< Disable clk_per                                    */
  uint32_t       RESERVED0[3U];                 /**< Reserved for future use                            */
  __IOM uint32_t FIFOIN;                        /**< New Register                                       */
  uint32_t       RESERVED1[7U];                 /**< Reserved for future use                            */
  __IM uint32_t  FIFOOUT;                       /**< New Register                                       */
  uint32_t       RESERVED2[23U];                /**< Reserved for future use                            */
  __IOM uint32_t FMTIN;                         /**< New Register                                       */
  uint32_t       RESERVED3[7U];                 /**< Reserved for future use                            */
  __IOM uint32_t FMTOUT;                        /**< New Register                                       */
  uint32_t       RESERVED4[79U];                /**< Reserved for future use                            */
  __IOM uint32_t TXCTRL;                        /**< New Register                                       */
  __IOM uint32_t RXCTRL;                        /**< New Register                                       */
  __IOM uint32_t IF;                            /**< New Register                                       */
  __IOM uint32_t IEN;                           /**< New Register                                       */
  __IOM uint32_t CTRL;                          /**< New Register                                       */
  uint32_t       RESERVED5[891U];               /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_SET;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_SET;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_SET;                   /**< New Register                                       */
  __IOM uint32_t DISCLK_SET;                    /**< Disable clk_per                                    */
  uint32_t       RESERVED6[3U];                 /**< Reserved for future use                            */
  __IOM uint32_t FIFOIN_SET;                    /**< New Register                                       */
  uint32_t       RESERVED7[7U];                 /**< Reserved for future use                            */
  __IM uint32_t  FIFOOUT_SET;                   /**< New Register                                       */
  uint32_t       RESERVED8[23U];                /**< Reserved for future use                            */
  __IOM uint32_t FMTIN_SET;                     /**< New Register                                       */
  uint32_t       RESERVED9[7U];                 /**< Reserved for future use                            */
  __IOM uint32_t FMTOUT_SET;                    /**< New Register                                       */
  uint32_t       RESERVED10[79U];               /**< Reserved for future use                            */
  __IOM uint32_t TXCTRL_SET;                    /**< New Register                                       */
  __IOM uint32_t RXCTRL_SET;                    /**< New Register                                       */
  __IOM uint32_t IF_SET;                        /**< New Register                                       */
  __IOM uint32_t IEN_SET;                       /**< New Register                                       */
  __IOM uint32_t CTRL_SET;                      /**< New Register                                       */
  uint32_t       RESERVED11[891U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_CLR;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_CLR;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_CLR;                   /**< New Register                                       */
  __IOM uint32_t DISCLK_CLR;                    /**< Disable clk_per                                    */
  uint32_t       RESERVED12[3U];                /**< Reserved for future use                            */
  __IOM uint32_t FIFOIN_CLR;                    /**< New Register                                       */
  uint32_t       RESERVED13[7U];                /**< Reserved for future use                            */
  __IM uint32_t  FIFOOUT_CLR;                   /**< New Register                                       */
  uint32_t       RESERVED14[23U];               /**< Reserved for future use                            */
  __IOM uint32_t FMTIN_CLR;                     /**< New Register                                       */
  uint32_t       RESERVED15[7U];                /**< Reserved for future use                            */
  __IOM uint32_t FMTOUT_CLR;                    /**< New Register                                       */
  uint32_t       RESERVED16[79U];               /**< Reserved for future use                            */
  __IOM uint32_t TXCTRL_CLR;                    /**< New Register                                       */
  __IOM uint32_t RXCTRL_CLR;                    /**< New Register                                       */
  __IOM uint32_t IF_CLR;                        /**< New Register                                       */
  __IOM uint32_t IEN_CLR;                       /**< New Register                                       */
  __IOM uint32_t CTRL_CLR;                      /**< New Register                                       */
  uint32_t       RESERVED17[891U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_TGL;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_TGL;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_TGL;                   /**< New Register                                       */
  __IOM uint32_t DISCLK_TGL;                    /**< Disable clk_per                                    */
  uint32_t       RESERVED18[3U];                /**< Reserved for future use                            */
  __IOM uint32_t FIFOIN_TGL;                    /**< New Register                                       */
  uint32_t       RESERVED19[7U];                /**< Reserved for future use                            */
  __IM uint32_t  FIFOOUT_TGL;                   /**< New Register                                       */
  uint32_t       RESERVED20[23U];               /**< Reserved for future use                            */
  __IOM uint32_t FMTIN_TGL;                     /**< New Register                                       */
  uint32_t       RESERVED21[7U];                /**< Reserved for future use                            */
  __IOM uint32_t FMTOUT_TGL;                    /**< New Register                                       */
  uint32_t       RESERVED22[79U];               /**< Reserved for future use                            */
  __IOM uint32_t TXCTRL_TGL;                    /**< New Register                                       */
  __IOM uint32_t RXCTRL_TGL;                    /**< New Register                                       */
  __IOM uint32_t IF_TGL;                        /**< New Register                                       */
  __IOM uint32_t IEN_TGL;                       /**< New Register                                       */
  __IOM uint32_t CTRL_TGL;                      /**< New Register                                       */
} FRCIF_TypeDef;
/** @} End of group EFR32FG25_FRCIF */

/**************************************************************************//**
 * @addtogroup EFR32FG25_FRCIF
 * @{
 * @defgroup EFR32FG25_FRCIF_BitFields FRCIF Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for FRCIF IPVERSION */
#define _FRCIF_IPVERSION_RESETVALUE           0x00000001UL                              /**< Default value for FRCIF_IPVERSION           */
#define _FRCIF_IPVERSION_MASK                 0xFFFFFFFFUL                              /**< Mask for FRCIF_IPVERSION                    */
#define _FRCIF_IPVERSION_IPVERSION_SHIFT      0                                         /**< Shift value for FRCIF_IPVERSION             */
#define _FRCIF_IPVERSION_IPVERSION_MASK       0xFFFFFFFFUL                              /**< Bit mask for FRCIF_IPVERSION                */
#define _FRCIF_IPVERSION_IPVERSION_DEFAULT    0x00000001UL                              /**< Mode DEFAULT for FRCIF_IPVERSION            */
#define FRCIF_IPVERSION_IPVERSION_DEFAULT     (_FRCIF_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for FRCIF_IPVERSION    */

/* Bit fields for FRCIF EN */
#define _FRCIF_EN_RESETVALUE                  0x00000000UL                              /**< Default value for FRCIF_EN                  */
#define _FRCIF_EN_MASK                        0x00000003UL                              /**< Mask for FRCIF_EN                           */
#define FRCIF_EN_EN                           (0x1UL << 0)                              /**< Module Enable                               */
#define _FRCIF_EN_EN_SHIFT                    0                                         /**< Shift value for FRCIF_EN                    */
#define _FRCIF_EN_EN_MASK                     0x1UL                                     /**< Bit mask for FRCIF_EN                       */
#define _FRCIF_EN_EN_DEFAULT                  0x00000000UL                              /**< Mode DEFAULT for FRCIF_EN                   */
#define FRCIF_EN_EN_DEFAULT                   (_FRCIF_EN_EN_DEFAULT << 0)               /**< Shifted mode DEFAULT for FRCIF_EN           */
#define FRCIF_EN_DISABLING                    (0x1UL << 1)                              /**< Disablement Busy Status                     */
#define _FRCIF_EN_DISABLING_SHIFT             1                                         /**< Shift value for FRCIF_DISABLING             */
#define _FRCIF_EN_DISABLING_MASK              0x2UL                                     /**< Bit mask for FRCIF_DISABLING                */
#define _FRCIF_EN_DISABLING_DEFAULT           0x00000000UL                              /**< Mode DEFAULT for FRCIF_EN                   */
#define FRCIF_EN_DISABLING_DEFAULT            (_FRCIF_EN_DISABLING_DEFAULT << 1)        /**< Shifted mode DEFAULT for FRCIF_EN           */

/* Bit fields for FRCIF SWRST */
#define _FRCIF_SWRST_RESETVALUE               0x00000000UL                              /**< Default value for FRCIF_SWRST               */
#define _FRCIF_SWRST_MASK                     0x00000003UL                              /**< Mask for FRCIF_SWRST                        */
#define FRCIF_SWRST_SWRST                     (0x1UL << 0)                              /**< Software Reset Command                      */
#define _FRCIF_SWRST_SWRST_SHIFT              0                                         /**< Shift value for FRCIF_SWRST                 */
#define _FRCIF_SWRST_SWRST_MASK               0x1UL                                     /**< Bit mask for FRCIF_SWRST                    */
#define _FRCIF_SWRST_SWRST_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for FRCIF_SWRST                */
#define FRCIF_SWRST_SWRST_DEFAULT             (_FRCIF_SWRST_SWRST_DEFAULT << 0)         /**< Shifted mode DEFAULT for FRCIF_SWRST        */
#define FRCIF_SWRST_RESETTING                 (0x1UL << 1)                              /**< Software Reset Busy Status                  */
#define _FRCIF_SWRST_RESETTING_SHIFT          1                                         /**< Shift value for FRCIF_RESETTING             */
#define _FRCIF_SWRST_RESETTING_MASK           0x2UL                                     /**< Bit mask for FRCIF_RESETTING                */
#define _FRCIF_SWRST_RESETTING_DEFAULT        0x00000000UL                              /**< Mode DEFAULT for FRCIF_SWRST                */
#define FRCIF_SWRST_RESETTING_DEFAULT         (_FRCIF_SWRST_RESETTING_DEFAULT << 1)     /**< Shifted mode DEFAULT for FRCIF_SWRST        */

/* Bit fields for FRCIF CONNECT */
#define _FRCIF_CONNECT_RESETVALUE             0x00000000UL                              /**< Default value for FRCIF_CONNECT             */
#define _FRCIF_CONNECT_MASK                   0x00000101UL                              /**< Mask for FRCIF_CONNECT                      */
#define FRCIF_CONNECT_IN                      (0x1UL << 0)                              /**< Input FIFO connect                          */
#define _FRCIF_CONNECT_IN_SHIFT               0                                         /**< Shift value for FRCIF_IN                    */
#define _FRCIF_CONNECT_IN_MASK                0x1UL                                     /**< Bit mask for FRCIF_IN                       */
#define _FRCIF_CONNECT_IN_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for FRCIF_CONNECT              */
#define FRCIF_CONNECT_IN_DEFAULT              (_FRCIF_CONNECT_IN_DEFAULT << 0)          /**< Shifted mode DEFAULT for FRCIF_CONNECT      */
#define FRCIF_CONNECT_OUT                     (0x1UL << 8)                              /**< Output FIFO connect                         */
#define _FRCIF_CONNECT_OUT_SHIFT              8                                         /**< Shift value for FRCIF_OUT                   */
#define _FRCIF_CONNECT_OUT_MASK               0x100UL                                   /**< Bit mask for FRCIF_OUT                      */
#define _FRCIF_CONNECT_OUT_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for FRCIF_CONNECT              */
#define FRCIF_CONNECT_OUT_DEFAULT             (_FRCIF_CONNECT_OUT_DEFAULT << 8)         /**< Shifted mode DEFAULT for FRCIF_CONNECT      */

/* Bit fields for FRCIF DISCLK */
#define _FRCIF_DISCLK_RESETVALUE              0x00000000UL                              /**< Default value for FRCIF_DISCLK              */
#define _FRCIF_DISCLK_MASK                    0x00000003UL                              /**< Mask for FRCIF_DISCLK                       */
#define _FRCIF_DISCLK_DISCLK_SHIFT            0                                         /**< Shift value for FRCIF_DISCLK                */
#define _FRCIF_DISCLK_DISCLK_MASK             0x3UL                                     /**< Bit mask for FRCIF_DISCLK                   */
#define _FRCIF_DISCLK_DISCLK_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for FRCIF_DISCLK               */
#define _FRCIF_DISCLK_DISCLK_NONE             0x00000000UL                              /**< Mode NONE for FRCIF_DISCLK                  */
#define _FRCIF_DISCLK_DISCLK_ALL              0x00000001UL                              /**< Mode ALL for FRCIF_DISCLK                   */
#define _FRCIF_DISCLK_DISCLK_AUTO             0x00000002UL                              /**< Mode AUTO for FRCIF_DISCLK                  */
#define FRCIF_DISCLK_DISCLK_DEFAULT           (_FRCIF_DISCLK_DISCLK_DEFAULT << 0)       /**< Shifted mode DEFAULT for FRCIF_DISCLK       */
#define FRCIF_DISCLK_DISCLK_NONE              (_FRCIF_DISCLK_DISCLK_NONE << 0)          /**< Shifted mode NONE for FRCIF_DISCLK          */
#define FRCIF_DISCLK_DISCLK_ALL               (_FRCIF_DISCLK_DISCLK_ALL << 0)           /**< Shifted mode ALL for FRCIF_DISCLK           */
#define FRCIF_DISCLK_DISCLK_AUTO              (_FRCIF_DISCLK_DISCLK_AUTO << 0)          /**< Shifted mode AUTO for FRCIF_DISCLK          */

/* Bit fields for FRCIF FIFOIN */
#define _FRCIF_FIFOIN_RESETVALUE              0x00000000UL                              /**< Default value for FRCIF_FIFOIN              */
#define _FRCIF_FIFOIN_MASK                    0x1FFF3F0FUL                              /**< Mask for FRCIF_FIFOIN                       */
#define _FRCIF_FIFOIN_FID_SHIFT               0                                         /**< Shift value for FRCIF_FID                   */
#define _FRCIF_FIFOIN_FID_MASK                0xFUL                                     /**< Bit mask for FRCIF_FID                      */
#define _FRCIF_FIFOIN_FID_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for FRCIF_FIFOIN               */
#define FRCIF_FIFOIN_FID_DEFAULT              (_FRCIF_FIFOIN_FID_DEFAULT << 0)          /**< Shifted mode DEFAULT for FRCIF_FIFOIN       */
#define _FRCIF_FIFOIN_CID_SHIFT               8                                         /**< Shift value for FRCIF_CID                   */
#define _FRCIF_FIFOIN_CID_MASK                0x3F00UL                                  /**< Bit mask for FRCIF_CID                      */
#define _FRCIF_FIFOIN_CID_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for FRCIF_FIFOIN               */
#define FRCIF_FIFOIN_CID_DEFAULT              (_FRCIF_FIFOIN_CID_DEFAULT << 8)          /**< Shifted mode DEFAULT for FRCIF_FIFOIN       */
#define _FRCIF_FIFOIN_REM_SHIFT               16                                        /**< Shift value for FRCIF_REM                   */
#define _FRCIF_FIFOIN_REM_MASK                0xFF0000UL                                /**< Bit mask for FRCIF_REM                      */
#define _FRCIF_FIFOIN_REM_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for FRCIF_FIFOIN               */
#define FRCIF_FIFOIN_REM_DEFAULT              (_FRCIF_FIFOIN_REM_DEFAULT << 16)         /**< Shifted mode DEFAULT for FRCIF_FIFOIN       */
#define _FRCIF_FIFOIN_ALARM_SHIFT             24                                        /**< Shift value for FRCIF_ALARM                 */
#define _FRCIF_FIFOIN_ALARM_MASK              0x1F000000UL                              /**< Bit mask for FRCIF_ALARM                    */
#define _FRCIF_FIFOIN_ALARM_DEFAULT           0x00000000UL                              /**< Mode DEFAULT for FRCIF_FIFOIN               */
#define FRCIF_FIFOIN_ALARM_DEFAULT            (_FRCIF_FIFOIN_ALARM_DEFAULT << 24)       /**< Shifted mode DEFAULT for FRCIF_FIFOIN       */

/* Bit fields for FRCIF FIFOOUT */
#define _FRCIF_FIFOOUT_RESETVALUE             0x00000000UL                              /**< Default value for FRCIF_FIFOOUT             */
#define _FRCIF_FIFOOUT_MASK                   0x1FFF0000UL                              /**< Mask for FRCIF_FIFOOUT                      */
#define _FRCIF_FIFOOUT_CNT_SHIFT              16                                        /**< Shift value for FRCIF_CNT                   */
#define _FRCIF_FIFOOUT_CNT_MASK               0xFF0000UL                                /**< Bit mask for FRCIF_CNT                      */
#define _FRCIF_FIFOOUT_CNT_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for FRCIF_FIFOOUT              */
#define FRCIF_FIFOOUT_CNT_DEFAULT             (_FRCIF_FIFOOUT_CNT_DEFAULT << 16)        /**< Shifted mode DEFAULT for FRCIF_FIFOOUT      */
#define _FRCIF_FIFOOUT_ALARM_SHIFT            24                                        /**< Shift value for FRCIF_ALARM                 */
#define _FRCIF_FIFOOUT_ALARM_MASK             0x1F000000UL                              /**< Bit mask for FRCIF_ALARM                    */
#define _FRCIF_FIFOOUT_ALARM_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for FRCIF_FIFOOUT              */
#define FRCIF_FIFOOUT_ALARM_DEFAULT           (_FRCIF_FIFOOUT_ALARM_DEFAULT << 24)      /**< Shifted mode DEFAULT for FRCIF_FIFOOUT      */

/* Bit fields for FRCIF FMTIN */
#define _FRCIF_FMTIN_RESETVALUE               0x0000001FUL                              /**< Default value for FRCIF_FMTIN               */
#define _FRCIF_FMTIN_MASK                     0x0000001FUL                              /**< Mask for FRCIF_FMTIN                        */
#define _FRCIF_FMTIN_ELEMSIZE_SHIFT           0                                         /**< Shift value for FRCIF_ELEMSIZE              */
#define _FRCIF_FMTIN_ELEMSIZE_MASK            0x1FUL                                    /**< Bit mask for FRCIF_ELEMSIZE                 */
#define _FRCIF_FMTIN_ELEMSIZE_DEFAULT         0x0000001FUL                              /**< Mode DEFAULT for FRCIF_FMTIN                */
#define FRCIF_FMTIN_ELEMSIZE_DEFAULT          (_FRCIF_FMTIN_ELEMSIZE_DEFAULT << 0)      /**< Shifted mode DEFAULT for FRCIF_FMTIN        */

/* Bit fields for FRCIF FMTOUT */
#define _FRCIF_FMTOUT_RESETVALUE              0x0000001FUL                              /**< Default value for FRCIF_FMTOUT              */
#define _FRCIF_FMTOUT_MASK                    0x0000001FUL                              /**< Mask for FRCIF_FMTOUT                       */
#define _FRCIF_FMTOUT_ELEMSIZE_SHIFT          0                                         /**< Shift value for FRCIF_ELEMSIZE              */
#define _FRCIF_FMTOUT_ELEMSIZE_MASK           0x1FUL                                    /**< Bit mask for FRCIF_ELEMSIZE                 */
#define _FRCIF_FMTOUT_ELEMSIZE_DEFAULT        0x0000001FUL                              /**< Mode DEFAULT for FRCIF_FMTOUT               */
#define FRCIF_FMTOUT_ELEMSIZE_DEFAULT         (_FRCIF_FMTOUT_ELEMSIZE_DEFAULT << 0)     /**< Shifted mode DEFAULT for FRCIF_FMTOUT       */

/* Bit fields for FRCIF TXCTRL */
#define _FRCIF_TXCTRL_RESETVALUE              0x00000000UL                              /**< Default value for FRCIF_TXCTRL              */
#define _FRCIF_TXCTRL_MASK                    0x0001FFFFUL                              /**< Mask for FRCIF_TXCTRL                       */
#define _FRCIF_TXCTRL_FRCTXREQNB_SHIFT        0                                         /**< Shift value for FRCIF_FRCTXREQNB            */
#define _FRCIF_TXCTRL_FRCTXREQNB_MASK         0xFFFFUL                                  /**< Bit mask for FRCIF_FRCTXREQNB               */
#define _FRCIF_TXCTRL_FRCTXREQNB_DEFAULT      0x00000000UL                              /**< Mode DEFAULT for FRCIF_TXCTRL               */
#define FRCIF_TXCTRL_FRCTXREQNB_DEFAULT       (_FRCIF_TXCTRL_FRCTXREQNB_DEFAULT << 0)   /**< Shifted mode DEFAULT for FRCIF_TXCTRL       */
#define FRCIF_TXCTRL_STARTTX                  (0x1UL << 16)                             /**< New BitField                                */
#define _FRCIF_TXCTRL_STARTTX_SHIFT           16                                        /**< Shift value for FRCIF_STARTTX               */
#define _FRCIF_TXCTRL_STARTTX_MASK            0x10000UL                                 /**< Bit mask for FRCIF_STARTTX                  */
#define _FRCIF_TXCTRL_STARTTX_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for FRCIF_TXCTRL               */
#define FRCIF_TXCTRL_STARTTX_DEFAULT          (_FRCIF_TXCTRL_STARTTX_DEFAULT << 16)     /**< Shifted mode DEFAULT for FRCIF_TXCTRL       */

/* Bit fields for FRCIF RXCTRL */
#define _FRCIF_RXCTRL_RESETVALUE              0x00000000UL                              /**< Default value for FRCIF_RXCTRL              */
#define _FRCIF_RXCTRL_MASK                    0x0001FFFFUL                              /**< Mask for FRCIF_RXCTRL                       */
#define _FRCIF_RXCTRL_FRCRXREQNB_SHIFT        0                                         /**< Shift value for FRCIF_FRCRXREQNB            */
#define _FRCIF_RXCTRL_FRCRXREQNB_MASK         0xFFFFUL                                  /**< Bit mask for FRCIF_FRCRXREQNB               */
#define _FRCIF_RXCTRL_FRCRXREQNB_DEFAULT      0x00000000UL                              /**< Mode DEFAULT for FRCIF_RXCTRL               */
#define FRCIF_RXCTRL_FRCRXREQNB_DEFAULT       (_FRCIF_RXCTRL_FRCRXREQNB_DEFAULT << 0)   /**< Shifted mode DEFAULT for FRCIF_RXCTRL       */
#define FRCIF_RXCTRL_STARTRX                  (0x1UL << 16)                             /**< New BitField                                */
#define _FRCIF_RXCTRL_STARTRX_SHIFT           16                                        /**< Shift value for FRCIF_STARTRX               */
#define _FRCIF_RXCTRL_STARTRX_MASK            0x10000UL                                 /**< Bit mask for FRCIF_STARTRX                  */
#define _FRCIF_RXCTRL_STARTRX_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for FRCIF_RXCTRL               */
#define FRCIF_RXCTRL_STARTRX_DEFAULT          (_FRCIF_RXCTRL_STARTRX_DEFAULT << 16)     /**< Shifted mode DEFAULT for FRCIF_RXCTRL       */

/* Bit fields for FRCIF IF */
#define _FRCIF_IF_RESETVALUE                  0x00000000UL                              /**< Default value for FRCIF_IF                  */
#define _FRCIF_IF_MASK                        0x00000003UL                              /**< Mask for FRCIF_IF                           */
#define FRCIF_IF_FRCIFIF0                     (0x1UL << 0)                              /**< FRCIF Interrupt flag                        */
#define _FRCIF_IF_FRCIFIF0_SHIFT              0                                         /**< Shift value for FRCIF_FRCIFIF0              */
#define _FRCIF_IF_FRCIFIF0_MASK               0x1UL                                     /**< Bit mask for FRCIF_FRCIFIF0                 */
#define _FRCIF_IF_FRCIFIF0_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for FRCIF_IF                   */
#define FRCIF_IF_FRCIFIF0_DEFAULT             (_FRCIF_IF_FRCIFIF0_DEFAULT << 0)         /**< Shifted mode DEFAULT for FRCIF_IF           */
#define FRCIF_IF_FRCIFIF1                     (0x1UL << 1)                              /**< FRCIF Interrupt flag                        */
#define _FRCIF_IF_FRCIFIF1_SHIFT              1                                         /**< Shift value for FRCIF_FRCIFIF1              */
#define _FRCIF_IF_FRCIFIF1_MASK               0x2UL                                     /**< Bit mask for FRCIF_FRCIFIF1                 */
#define _FRCIF_IF_FRCIFIF1_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for FRCIF_IF                   */
#define FRCIF_IF_FRCIFIF1_DEFAULT             (_FRCIF_IF_FRCIFIF1_DEFAULT << 1)         /**< Shifted mode DEFAULT for FRCIF_IF           */

/* Bit fields for FRCIF IEN */
#define _FRCIF_IEN_RESETVALUE                 0x00000000UL                              /**< Default value for FRCIF_IEN                 */
#define _FRCIF_IEN_MASK                       0x00000003UL                              /**< Mask for FRCIF_IEN                          */
#define FRCIF_IEN_FRCIFIEN0                   (0x1UL << 0)                              /**< FRCIF Interrupt Enable                      */
#define _FRCIF_IEN_FRCIFIEN0_SHIFT            0                                         /**< Shift value for FRCIF_FRCIFIEN0             */
#define _FRCIF_IEN_FRCIFIEN0_MASK             0x1UL                                     /**< Bit mask for FRCIF_FRCIFIEN0                */
#define _FRCIF_IEN_FRCIFIEN0_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for FRCIF_IEN                  */
#define FRCIF_IEN_FRCIFIEN0_DEFAULT           (_FRCIF_IEN_FRCIFIEN0_DEFAULT << 0)       /**< Shifted mode DEFAULT for FRCIF_IEN          */
#define FRCIF_IEN_FRCIFIEN1                   (0x1UL << 1)                              /**< FRCIF Interrupt Enable                      */
#define _FRCIF_IEN_FRCIFIEN1_SHIFT            1                                         /**< Shift value for FRCIF_FRCIFIEN1             */
#define _FRCIF_IEN_FRCIFIEN1_MASK             0x2UL                                     /**< Bit mask for FRCIF_FRCIFIEN1                */
#define _FRCIF_IEN_FRCIFIEN1_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for FRCIF_IEN                  */
#define FRCIF_IEN_FRCIFIEN1_DEFAULT           (_FRCIF_IEN_FRCIFIEN1_DEFAULT << 1)       /**< Shifted mode DEFAULT for FRCIF_IEN          */

/* Bit fields for FRCIF CTRL */
#define _FRCIF_CTRL_RESETVALUE                0x00000000UL                              /**< Default value for FRCIF_CTRL                */
#define _FRCIF_CTRL_MASK                      0x00000001UL                              /**< Mask for FRCIF_CTRL                         */
#define FRCIF_CTRL_DISCLKMODE                 (0x1UL << 0)                              /**< New BitField                                */
#define _FRCIF_CTRL_DISCLKMODE_SHIFT          0                                         /**< Shift value for FRCIF_DISCLKMODE            */
#define _FRCIF_CTRL_DISCLKMODE_MASK           0x1UL                                     /**< Bit mask for FRCIF_DISCLKMODE               */
#define _FRCIF_CTRL_DISCLKMODE_DEFAULT        0x00000000UL                              /**< Mode DEFAULT for FRCIF_CTRL                 */
#define FRCIF_CTRL_DISCLKMODE_DEFAULT         (_FRCIF_CTRL_DISCLKMODE_DEFAULT << 0)     /**< Shifted mode DEFAULT for FRCIF_CTRL         */

/** @} End of group EFR32FG25_FRCIF_BitFields */
/** @} End of group EFR32FG25_FRCIF */
/** @} End of group Parts */

#endif /* EFR32FG25_FRCIF_H */
