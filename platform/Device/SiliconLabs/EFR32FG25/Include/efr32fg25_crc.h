/**************************************************************************//**
 * @file
 * @brief EFR32FG25 CRC register and bit field definitions
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
#ifndef EFR32FG25_CRC_H
#define EFR32FG25_CRC_H
#define CRC_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_CRC CRC
 * @{
 * @brief EFR32FG25 CRC Register Declaration.
 *****************************************************************************/

/** CRC Register Declaration. */
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
  __IOM uint32_t CTRL2;                         /**< New Register                                       */
  __IOM uint32_t POLY;                          /**< New Register                                       */
  __IOM uint32_t INIT;                          /**< New Register                                       */
  uint32_t       RESERVED6[5U];                 /**< Reserved for future use                            */
  __IM uint32_t  STATUS;                        /**< New Register                                       */
  __IM uint32_t  REFERENCE;                     /**< New Register                                       */
  __IM uint32_t  RECEIVED;                      /**< New Register                                       */
  __IOM uint32_t IF;                            /**< Interrupt Flag                                     */
  __IOM uint32_t IEN;                           /**< Interrupt Enable                                   */
  __IOM uint32_t CTRL3;                         /**< New Register                                       */
  uint32_t       RESERVED7[881U];               /**< Reserved for future use                            */
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
  __IOM uint32_t CTRL2_SET;                     /**< New Register                                       */
  __IOM uint32_t POLY_SET;                      /**< New Register                                       */
  __IOM uint32_t INIT_SET;                      /**< New Register                                       */
  uint32_t       RESERVED14[5U];                /**< Reserved for future use                            */
  __IM uint32_t  STATUS_SET;                    /**< New Register                                       */
  __IM uint32_t  REFERENCE_SET;                 /**< New Register                                       */
  __IM uint32_t  RECEIVED_SET;                  /**< New Register                                       */
  __IOM uint32_t IF_SET;                        /**< Interrupt Flag                                     */
  __IOM uint32_t IEN_SET;                       /**< Interrupt Enable                                   */
  __IOM uint32_t CTRL3_SET;                     /**< New Register                                       */
  uint32_t       RESERVED15[881U];              /**< Reserved for future use                            */
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
  __IOM uint32_t CTRL2_CLR;                     /**< New Register                                       */
  __IOM uint32_t POLY_CLR;                      /**< New Register                                       */
  __IOM uint32_t INIT_CLR;                      /**< New Register                                       */
  uint32_t       RESERVED22[5U];                /**< Reserved for future use                            */
  __IM uint32_t  STATUS_CLR;                    /**< New Register                                       */
  __IM uint32_t  REFERENCE_CLR;                 /**< New Register                                       */
  __IM uint32_t  RECEIVED_CLR;                  /**< New Register                                       */
  __IOM uint32_t IF_CLR;                        /**< Interrupt Flag                                     */
  __IOM uint32_t IEN_CLR;                       /**< Interrupt Enable                                   */
  __IOM uint32_t CTRL3_CLR;                     /**< New Register                                       */
  uint32_t       RESERVED23[881U];              /**< Reserved for future use                            */
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
  __IOM uint32_t CTRL2_TGL;                     /**< New Register                                       */
  __IOM uint32_t POLY_TGL;                      /**< New Register                                       */
  __IOM uint32_t INIT_TGL;                      /**< New Register                                       */
  uint32_t       RESERVED30[5U];                /**< Reserved for future use                            */
  __IM uint32_t  STATUS_TGL;                    /**< New Register                                       */
  __IM uint32_t  REFERENCE_TGL;                 /**< New Register                                       */
  __IM uint32_t  RECEIVED_TGL;                  /**< New Register                                       */
  __IOM uint32_t IF_TGL;                        /**< Interrupt Flag                                     */
  __IOM uint32_t IEN_TGL;                       /**< Interrupt Enable                                   */
  __IOM uint32_t CTRL3_TGL;                     /**< New Register                                       */
} CRC_TypeDef;
/** @} End of group EFR32FG25_CRC */

/**************************************************************************//**
 * @addtogroup EFR32FG25_CRC
 * @{
 * @defgroup EFR32FG25_CRC_BitFields CRC Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for CRC IPVERSION */
#define _CRC_IPVERSION_RESETVALUE           0x00000001UL                                /**< Default value for CRC_IPVERSION             */
#define _CRC_IPVERSION_MASK                 0xFFFFFFFFUL                                /**< Mask for CRC_IPVERSION                      */
#define _CRC_IPVERSION_IPVERSION_SHIFT      0                                           /**< Shift value for CRC_IPVERSION               */
#define _CRC_IPVERSION_IPVERSION_MASK       0xFFFFFFFFUL                                /**< Bit mask for CRC_IPVERSION                  */
#define _CRC_IPVERSION_IPVERSION_DEFAULT    0x00000001UL                                /**< Mode DEFAULT for CRC_IPVERSION              */
#define CRC_IPVERSION_IPVERSION_DEFAULT     (_CRC_IPVERSION_IPVERSION_DEFAULT << 0)     /**< Shifted mode DEFAULT for CRC_IPVERSION      */

/* Bit fields for CRC EN */
#define _CRC_EN_RESETVALUE                  0x00000000UL                                /**< Default value for CRC_EN                    */
#define _CRC_EN_MASK                        0x00000003UL                                /**< Mask for CRC_EN                             */
#define CRC_EN_EN                           (0x1UL << 0)                                /**< Module Enable                               */
#define _CRC_EN_EN_SHIFT                    0                                           /**< Shift value for CRC_EN                      */
#define _CRC_EN_EN_MASK                     0x1UL                                       /**< Bit mask for CRC_EN                         */
#define _CRC_EN_EN_DEFAULT                  0x00000000UL                                /**< Mode DEFAULT for CRC_EN                     */
#define CRC_EN_EN_DEFAULT                   (_CRC_EN_EN_DEFAULT << 0)                   /**< Shifted mode DEFAULT for CRC_EN             */
#define CRC_EN_DISABLING                    (0x1UL << 1)                                /**< Disablement Busy Status                     */
#define _CRC_EN_DISABLING_SHIFT             1                                           /**< Shift value for CRC_DISABLING               */
#define _CRC_EN_DISABLING_MASK              0x2UL                                       /**< Bit mask for CRC_DISABLING                  */
#define _CRC_EN_DISABLING_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for CRC_EN                     */
#define CRC_EN_DISABLING_DEFAULT            (_CRC_EN_DISABLING_DEFAULT << 1)            /**< Shifted mode DEFAULT for CRC_EN             */

/* Bit fields for CRC SWRST */
#define _CRC_SWRST_RESETVALUE               0x00000000UL                                /**< Default value for CRC_SWRST                 */
#define _CRC_SWRST_MASK                     0x00000003UL                                /**< Mask for CRC_SWRST                          */
#define CRC_SWRST_SWRST                     (0x1UL << 0)                                /**< Software Reset Command                      */
#define _CRC_SWRST_SWRST_SHIFT              0                                           /**< Shift value for CRC_SWRST                   */
#define _CRC_SWRST_SWRST_MASK               0x1UL                                       /**< Bit mask for CRC_SWRST                      */
#define _CRC_SWRST_SWRST_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for CRC_SWRST                  */
#define CRC_SWRST_SWRST_DEFAULT             (_CRC_SWRST_SWRST_DEFAULT << 0)             /**< Shifted mode DEFAULT for CRC_SWRST          */
#define CRC_SWRST_RESETTING                 (0x1UL << 1)                                /**< Software Reset Busy Status                  */
#define _CRC_SWRST_RESETTING_SHIFT          1                                           /**< Shift value for CRC_RESETTING               */
#define _CRC_SWRST_RESETTING_MASK           0x2UL                                       /**< Bit mask for CRC_RESETTING                  */
#define _CRC_SWRST_RESETTING_DEFAULT        0x00000000UL                                /**< Mode DEFAULT for CRC_SWRST                  */
#define CRC_SWRST_RESETTING_DEFAULT         (_CRC_SWRST_RESETTING_DEFAULT << 1)         /**< Shifted mode DEFAULT for CRC_SWRST          */

/* Bit fields for CRC CONNECT */
#define _CRC_CONNECT_RESETVALUE             0x00000000UL                                /**< Default value for CRC_CONNECT               */
#define _CRC_CONNECT_MASK                   0x00000101UL                                /**< Mask for CRC_CONNECT                        */
#define CRC_CONNECT_IN                      (0x1UL << 0)                                /**< Input FIFO connect                          */
#define _CRC_CONNECT_IN_SHIFT               0                                           /**< Shift value for CRC_IN                      */
#define _CRC_CONNECT_IN_MASK                0x1UL                                       /**< Bit mask for CRC_IN                         */
#define _CRC_CONNECT_IN_DEFAULT             0x00000000UL                                /**< Mode DEFAULT for CRC_CONNECT                */
#define CRC_CONNECT_IN_DEFAULT              (_CRC_CONNECT_IN_DEFAULT << 0)              /**< Shifted mode DEFAULT for CRC_CONNECT        */
#define CRC_CONNECT_OUT                     (0x1UL << 8)                                /**< Output FIFO connect                         */
#define _CRC_CONNECT_OUT_SHIFT              8                                           /**< Shift value for CRC_OUT                     */
#define _CRC_CONNECT_OUT_MASK               0x100UL                                     /**< Bit mask for CRC_OUT                        */
#define _CRC_CONNECT_OUT_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for CRC_CONNECT                */
#define CRC_CONNECT_OUT_DEFAULT             (_CRC_CONNECT_OUT_DEFAULT << 8)             /**< Shifted mode DEFAULT for CRC_CONNECT        */

/* Bit fields for CRC DISCLK */
#define _CRC_DISCLK_RESETVALUE              0x00000002UL                                /**< Default value for CRC_DISCLK                */
#define _CRC_DISCLK_MASK                    0x00000003UL                                /**< Mask for CRC_DISCLK                         */
#define _CRC_DISCLK_DISCLK_SHIFT            0                                           /**< Shift value for CRC_DISCLK                  */
#define _CRC_DISCLK_DISCLK_MASK             0x3UL                                       /**< Bit mask for CRC_DISCLK                     */
#define _CRC_DISCLK_DISCLK_DEFAULT          0x00000002UL                                /**< Mode DEFAULT for CRC_DISCLK                 */
#define _CRC_DISCLK_DISCLK_NONE             0x00000000UL                                /**< Mode NONE for CRC_DISCLK                    */
#define _CRC_DISCLK_DISCLK_ALL              0x00000001UL                                /**< Mode ALL for CRC_DISCLK                     */
#define _CRC_DISCLK_DISCLK_AUTO             0x00000002UL                                /**< Mode AUTO for CRC_DISCLK                    */
#define _CRC_DISCLK_DISCLK_NOTUSED          0x00000003UL                                /**< Mode NOTUSED for CRC_DISCLK                 */
#define CRC_DISCLK_DISCLK_DEFAULT           (_CRC_DISCLK_DISCLK_DEFAULT << 0)           /**< Shifted mode DEFAULT for CRC_DISCLK         */
#define CRC_DISCLK_DISCLK_NONE              (_CRC_DISCLK_DISCLK_NONE << 0)              /**< Shifted mode NONE for CRC_DISCLK            */
#define CRC_DISCLK_DISCLK_ALL               (_CRC_DISCLK_DISCLK_ALL << 0)               /**< Shifted mode ALL for CRC_DISCLK             */
#define CRC_DISCLK_DISCLK_AUTO              (_CRC_DISCLK_DISCLK_AUTO << 0)              /**< Shifted mode AUTO for CRC_DISCLK            */
#define CRC_DISCLK_DISCLK_NOTUSED           (_CRC_DISCLK_DISCLK_NOTUSED << 0)           /**< Shifted mode NOTUSED for CRC_DISCLK         */

/* Bit fields for CRC FIFOIN */
#define _CRC_FIFOIN_RESETVALUE              0x00000000UL                                /**< Default value for CRC_FIFOIN                */
#define _CRC_FIFOIN_MASK                    0x1FFF3F0FUL                                /**< Mask for CRC_FIFOIN                         */
#define _CRC_FIFOIN_FID_SHIFT               0                                           /**< Shift value for CRC_FID                     */
#define _CRC_FIFOIN_FID_MASK                0xFUL                                       /**< Bit mask for CRC_FID                        */
#define _CRC_FIFOIN_FID_DEFAULT             0x00000000UL                                /**< Mode DEFAULT for CRC_FIFOIN                 */
#define CRC_FIFOIN_FID_DEFAULT              (_CRC_FIFOIN_FID_DEFAULT << 0)              /**< Shifted mode DEFAULT for CRC_FIFOIN         */
#define _CRC_FIFOIN_CID_SHIFT               8                                           /**< Shift value for CRC_CID                     */
#define _CRC_FIFOIN_CID_MASK                0x3F00UL                                    /**< Bit mask for CRC_CID                        */
#define _CRC_FIFOIN_CID_DEFAULT             0x00000000UL                                /**< Mode DEFAULT for CRC_FIFOIN                 */
#define CRC_FIFOIN_CID_DEFAULT              (_CRC_FIFOIN_CID_DEFAULT << 8)              /**< Shifted mode DEFAULT for CRC_FIFOIN         */
#define _CRC_FIFOIN_REM_SHIFT               16                                          /**< Shift value for CRC_REM                     */
#define _CRC_FIFOIN_REM_MASK                0xFF0000UL                                  /**< Bit mask for CRC_REM                        */
#define _CRC_FIFOIN_REM_DEFAULT             0x00000000UL                                /**< Mode DEFAULT for CRC_FIFOIN                 */
#define CRC_FIFOIN_REM_DEFAULT              (_CRC_FIFOIN_REM_DEFAULT << 16)             /**< Shifted mode DEFAULT for CRC_FIFOIN         */
#define _CRC_FIFOIN_ALARM_SHIFT             24                                          /**< Shift value for CRC_ALARM                   */
#define _CRC_FIFOIN_ALARM_MASK              0x1F000000UL                                /**< Bit mask for CRC_ALARM                      */
#define _CRC_FIFOIN_ALARM_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for CRC_FIFOIN                 */
#define CRC_FIFOIN_ALARM_DEFAULT            (_CRC_FIFOIN_ALARM_DEFAULT << 24)           /**< Shifted mode DEFAULT for CRC_FIFOIN         */

/* Bit fields for CRC FIFOOUT */
#define _CRC_FIFOOUT_RESETVALUE             0x00000000UL                                /**< Default value for CRC_FIFOOUT               */
#define _CRC_FIFOOUT_MASK                   0x1FFF0000UL                                /**< Mask for CRC_FIFOOUT                        */
#define _CRC_FIFOOUT_CNT_SHIFT              16                                          /**< Shift value for CRC_CNT                     */
#define _CRC_FIFOOUT_CNT_MASK               0xFF0000UL                                  /**< Bit mask for CRC_CNT                        */
#define _CRC_FIFOOUT_CNT_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for CRC_FIFOOUT                */
#define CRC_FIFOOUT_CNT_DEFAULT             (_CRC_FIFOOUT_CNT_DEFAULT << 16)            /**< Shifted mode DEFAULT for CRC_FIFOOUT        */
#define _CRC_FIFOOUT_ALARM_SHIFT            24                                          /**< Shift value for CRC_ALARM                   */
#define _CRC_FIFOOUT_ALARM_MASK             0x1F000000UL                                /**< Bit mask for CRC_ALARM                      */
#define _CRC_FIFOOUT_ALARM_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for CRC_FIFOOUT                */
#define CRC_FIFOOUT_ALARM_DEFAULT           (_CRC_FIFOOUT_ALARM_DEFAULT << 24)          /**< Shifted mode DEFAULT for CRC_FIFOOUT        */

/* Bit fields for CRC FMTIN */
#define _CRC_FMTIN_RESETVALUE               0x0000001FUL                                /**< Default value for CRC_FMTIN                 */
#define _CRC_FMTIN_MASK                     0x0003031FUL                                /**< Mask for CRC_FMTIN                          */
#define _CRC_FMTIN_ELEMSIZE_SHIFT           0                                           /**< Shift value for CRC_ELEMSIZE                */
#define _CRC_FMTIN_ELEMSIZE_MASK            0x1FUL                                      /**< Bit mask for CRC_ELEMSIZE                   */
#define _CRC_FMTIN_ELEMSIZE_DEFAULT         0x0000001FUL                                /**< Mode DEFAULT for CRC_FMTIN                  */
#define CRC_FMTIN_ELEMSIZE_DEFAULT          (_CRC_FMTIN_ELEMSIZE_DEFAULT << 0)          /**< Shifted mode DEFAULT for CRC_FMTIN          */
#define _CRC_FMTIN_ELEMNB_SHIFT             8                                           /**< Shift value for CRC_ELEMNB                  */
#define _CRC_FMTIN_ELEMNB_MASK              0x300UL                                     /**< Bit mask for CRC_ELEMNB                     */
#define _CRC_FMTIN_ELEMNB_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for CRC_FMTIN                  */
#define _CRC_FMTIN_ELEMNB_ONE               0x00000000UL                                /**< Mode ONE for CRC_FMTIN                      */
#define _CRC_FMTIN_ELEMNB_TWO               0x00000001UL                                /**< Mode TWO for CRC_FMTIN                      */
#define _CRC_FMTIN_ELEMNB_FOUR              0x00000002UL                                /**< Mode FOUR for CRC_FMTIN                     */
#define CRC_FMTIN_ELEMNB_DEFAULT            (_CRC_FMTIN_ELEMNB_DEFAULT << 8)            /**< Shifted mode DEFAULT for CRC_FMTIN          */
#define CRC_FMTIN_ELEMNB_ONE                (_CRC_FMTIN_ELEMNB_ONE << 8)                /**< Shifted mode ONE for CRC_FMTIN              */
#define CRC_FMTIN_ELEMNB_TWO                (_CRC_FMTIN_ELEMNB_TWO << 8)                /**< Shifted mode TWO for CRC_FMTIN              */
#define CRC_FMTIN_ELEMNB_FOUR               (_CRC_FMTIN_ELEMNB_FOUR << 8)               /**< Shifted mode FOUR for CRC_FMTIN             */
#define _CRC_FMTIN_ELEMALIGN_SHIFT          16                                          /**< Shift value for CRC_ELEMALIGN               */
#define _CRC_FMTIN_ELEMALIGN_MASK           0x30000UL                                   /**< Bit mask for CRC_ELEMALIGN                  */
#define _CRC_FMTIN_ELEMALIGN_DEFAULT        0x00000000UL                                /**< Mode DEFAULT for CRC_FMTIN                  */
#define _CRC_FMTIN_ELEMALIGN_WORD           0x00000000UL                                /**< Mode WORD for CRC_FMTIN                     */
#define _CRC_FMTIN_ELEMALIGN_HALFWORD       0x00000001UL                                /**< Mode HALFWORD for CRC_FMTIN                 */
#define _CRC_FMTIN_ELEMALIGN_BYTE           0x00000002UL                                /**< Mode BYTE for CRC_FMTIN                     */
#define CRC_FMTIN_ELEMALIGN_DEFAULT         (_CRC_FMTIN_ELEMALIGN_DEFAULT << 16)        /**< Shifted mode DEFAULT for CRC_FMTIN          */
#define CRC_FMTIN_ELEMALIGN_WORD            (_CRC_FMTIN_ELEMALIGN_WORD << 16)           /**< Shifted mode WORD for CRC_FMTIN             */
#define CRC_FMTIN_ELEMALIGN_HALFWORD        (_CRC_FMTIN_ELEMALIGN_HALFWORD << 16)       /**< Shifted mode HALFWORD for CRC_FMTIN         */
#define CRC_FMTIN_ELEMALIGN_BYTE            (_CRC_FMTIN_ELEMALIGN_BYTE << 16)           /**< Shifted mode BYTE for CRC_FMTIN             */

/* Bit fields for CRC CTRL1 */
#define _CRC_CTRL1_RESETVALUE               0x00000000UL                                /**< Default value for CRC_CTRL1                 */
#define _CRC_CTRL1_MASK                     0x8000C1FFUL                                /**< Mask for CRC_CTRL1                          */
#define CRC_CTRL1_RST                       (0x1UL << 0)                                /**< New BitField                                */
#define _CRC_CTRL1_RST_SHIFT                0                                           /**< Shift value for CRC_RST                     */
#define _CRC_CTRL1_RST_MASK                 0x1UL                                       /**< Bit mask for CRC_RST                        */
#define _CRC_CTRL1_RST_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for CRC_CTRL1                  */
#define _CRC_CTRL1_RST_RUN                  0x00000000UL                                /**< Mode RUN for CRC_CTRL1                      */
#define _CRC_CTRL1_RST_RESET                0x00000001UL                                /**< Mode RESET for CRC_CTRL1                    */
#define CRC_CTRL1_RST_DEFAULT               (_CRC_CTRL1_RST_DEFAULT << 0)               /**< Shifted mode DEFAULT for CRC_CTRL1          */
#define CRC_CTRL1_RST_RUN                   (_CRC_CTRL1_RST_RUN << 0)                   /**< Shifted mode RUN for CRC_CTRL1              */
#define CRC_CTRL1_RST_RESET                 (_CRC_CTRL1_RST_RESET << 0)                 /**< Shifted mode RESET for CRC_CTRL1            */
#define CRC_CTRL1_ENREQOUT                  (0x1UL << 1)                                /**< New BitField                                */
#define _CRC_CTRL1_ENREQOUT_SHIFT           1                                           /**< Shift value for CRC_ENREQOUT                */
#define _CRC_CTRL1_ENREQOUT_MASK            0x2UL                                       /**< Bit mask for CRC_ENREQOUT                   */
#define _CRC_CTRL1_ENREQOUT_DEFAULT         0x00000000UL                                /**< Mode DEFAULT for CRC_CTRL1                  */
#define _CRC_CTRL1_ENREQOUT_NO              0x00000000UL                                /**< Mode NO for CRC_CTRL1                       */
#define _CRC_CTRL1_ENREQOUT_YES             0x00000001UL                                /**< Mode YES for CRC_CTRL1                      */
#define CRC_CTRL1_ENREQOUT_DEFAULT          (_CRC_CTRL1_ENREQOUT_DEFAULT << 1)          /**< Shifted mode DEFAULT for CRC_CTRL1          */
#define CRC_CTRL1_ENREQOUT_NO               (_CRC_CTRL1_ENREQOUT_NO << 1)               /**< Shifted mode NO for CRC_CTRL1               */
#define CRC_CTRL1_ENREQOUT_YES              (_CRC_CTRL1_ENREQOUT_YES << 1)              /**< Shifted mode YES for CRC_CTRL1              */
#define CRC_CTRL1_INV                       (0x1UL << 2)                                /**< New BitField                                */
#define _CRC_CTRL1_INV_SHIFT                2                                           /**< Shift value for CRC_INV                     */
#define _CRC_CTRL1_INV_MASK                 0x4UL                                       /**< Bit mask for CRC_INV                        */
#define _CRC_CTRL1_INV_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for CRC_CTRL1                  */
#define _CRC_CTRL1_INV_NO                   0x00000000UL                                /**< Mode NO for CRC_CTRL1                       */
#define _CRC_CTRL1_INV_YES                  0x00000001UL                                /**< Mode YES for CRC_CTRL1                      */
#define CRC_CTRL1_INV_DEFAULT               (_CRC_CTRL1_INV_DEFAULT << 2)               /**< Shifted mode DEFAULT for CRC_CTRL1          */
#define CRC_CTRL1_INV_NO                    (_CRC_CTRL1_INV_NO << 2)                    /**< Shifted mode NO for CRC_CTRL1               */
#define CRC_CTRL1_INV_YES                   (_CRC_CTRL1_INV_YES << 2)                   /**< Shifted mode YES for CRC_CTRL1              */
#define CRC_CTRL1_SWAPIN                    (0x1UL << 3)                                /**< New BitField                                */
#define _CRC_CTRL1_SWAPIN_SHIFT             3                                           /**< Shift value for CRC_SWAPIN                  */
#define _CRC_CTRL1_SWAPIN_MASK              0x8UL                                       /**< Bit mask for CRC_SWAPIN                     */
#define _CRC_CTRL1_SWAPIN_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for CRC_CTRL1                  */
#define _CRC_CTRL1_SWAPIN_NO                0x00000000UL                                /**< Mode NO for CRC_CTRL1                       */
#define _CRC_CTRL1_SWAPIN_YES               0x00000001UL                                /**< Mode YES for CRC_CTRL1                      */
#define CRC_CTRL1_SWAPIN_DEFAULT            (_CRC_CTRL1_SWAPIN_DEFAULT << 3)            /**< Shifted mode DEFAULT for CRC_CTRL1          */
#define CRC_CTRL1_SWAPIN_NO                 (_CRC_CTRL1_SWAPIN_NO << 3)                 /**< Shifted mode NO for CRC_CTRL1               */
#define CRC_CTRL1_SWAPIN_YES                (_CRC_CTRL1_SWAPIN_YES << 3)                /**< Shifted mode YES for CRC_CTRL1              */
#define CRC_CTRL1_SYNCSTAT                  (0x1UL << 4)                                /**< New BitField                                */
#define _CRC_CTRL1_SYNCSTAT_SHIFT           4                                           /**< Shift value for CRC_SYNCSTAT                */
#define _CRC_CTRL1_SYNCSTAT_MASK            0x10UL                                      /**< Bit mask for CRC_SYNCSTAT                   */
#define _CRC_CTRL1_SYNCSTAT_DEFAULT         0x00000000UL                                /**< Mode DEFAULT for CRC_CTRL1                  */
#define _CRC_CTRL1_SYNCSTAT_NO              0x00000000UL                                /**< Mode NO for CRC_CTRL1                       */
#define _CRC_CTRL1_SYNCSTAT_YES             0x00000001UL                                /**< Mode YES for CRC_CTRL1                      */
#define CRC_CTRL1_SYNCSTAT_DEFAULT          (_CRC_CTRL1_SYNCSTAT_DEFAULT << 4)          /**< Shifted mode DEFAULT for CRC_CTRL1          */
#define CRC_CTRL1_SYNCSTAT_NO               (_CRC_CTRL1_SYNCSTAT_NO << 4)               /**< Shifted mode NO for CRC_CTRL1               */
#define CRC_CTRL1_SYNCSTAT_YES              (_CRC_CTRL1_SYNCSTAT_YES << 4)              /**< Shifted mode YES for CRC_CTRL1              */
#define CRC_CTRL1_SWAPOUT                   (0x1UL << 5)                                /**< New BitField                                */
#define _CRC_CTRL1_SWAPOUT_SHIFT            5                                           /**< Shift value for CRC_SWAPOUT                 */
#define _CRC_CTRL1_SWAPOUT_MASK             0x20UL                                      /**< Bit mask for CRC_SWAPOUT                    */
#define _CRC_CTRL1_SWAPOUT_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for CRC_CTRL1                  */
#define _CRC_CTRL1_SWAPOUT_NO               0x00000000UL                                /**< Mode NO for CRC_CTRL1                       */
#define _CRC_CTRL1_SWAPOUT_YES              0x00000001UL                                /**< Mode YES for CRC_CTRL1                      */
#define CRC_CTRL1_SWAPOUT_DEFAULT           (_CRC_CTRL1_SWAPOUT_DEFAULT << 5)           /**< Shifted mode DEFAULT for CRC_CTRL1          */
#define CRC_CTRL1_SWAPOUT_NO                (_CRC_CTRL1_SWAPOUT_NO << 5)                /**< Shifted mode NO for CRC_CTRL1               */
#define CRC_CTRL1_SWAPOUT_YES               (_CRC_CTRL1_SWAPOUT_YES << 5)               /**< Shifted mode YES for CRC_CTRL1              */
#define CRC_CTRL1_BYPASS                    (0x1UL << 6)                                /**< New BitField                                */
#define _CRC_CTRL1_BYPASS_SHIFT             6                                           /**< Shift value for CRC_BYPASS                  */
#define _CRC_CTRL1_BYPASS_MASK              0x40UL                                      /**< Bit mask for CRC_BYPASS                     */
#define _CRC_CTRL1_BYPASS_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for CRC_CTRL1                  */
#define _CRC_CTRL1_BYPASS_NO                0x00000000UL                                /**< Mode NO for CRC_CTRL1                       */
#define _CRC_CTRL1_BYPASS_YES               0x00000001UL                                /**< Mode YES for CRC_CTRL1                      */
#define CRC_CTRL1_BYPASS_DEFAULT            (_CRC_CTRL1_BYPASS_DEFAULT << 6)            /**< Shifted mode DEFAULT for CRC_CTRL1          */
#define CRC_CTRL1_BYPASS_NO                 (_CRC_CTRL1_BYPASS_NO << 6)                 /**< Shifted mode NO for CRC_CTRL1               */
#define CRC_CTRL1_BYPASS_YES                (_CRC_CTRL1_BYPASS_YES << 6)                /**< Shifted mode YES for CRC_CTRL1              */
#define CRC_CTRL1_OUTMODE                   (0x1UL << 7)                                /**< New BitField                                */
#define _CRC_CTRL1_OUTMODE_SHIFT            7                                           /**< Shift value for CRC_OUTMODE                 */
#define _CRC_CTRL1_OUTMODE_MASK             0x80UL                                      /**< Bit mask for CRC_OUTMODE                    */
#define _CRC_CTRL1_OUTMODE_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for CRC_CTRL1                  */
#define _CRC_CTRL1_OUTMODE_ALL              0x00000000UL                                /**< Mode ALL for CRC_CTRL1                      */
#define _CRC_CTRL1_OUTMODE_ONLY_CRC         0x00000001UL                                /**< Mode ONLY_CRC for CRC_CTRL1                 */
#define CRC_CTRL1_OUTMODE_DEFAULT           (_CRC_CTRL1_OUTMODE_DEFAULT << 7)           /**< Shifted mode DEFAULT for CRC_CTRL1          */
#define CRC_CTRL1_OUTMODE_ALL               (_CRC_CTRL1_OUTMODE_ALL << 7)               /**< Shifted mode ALL for CRC_CTRL1              */
#define CRC_CTRL1_OUTMODE_ONLY_CRC          (_CRC_CTRL1_OUTMODE_ONLY_CRC << 7)          /**< Shifted mode ONLY_CRC for CRC_CTRL1         */
#define CRC_CTRL1_INVIN                     (0x1UL << 8)                                /**< New BitField                                */
#define _CRC_CTRL1_INVIN_SHIFT              8                                           /**< Shift value for CRC_INVIN                   */
#define _CRC_CTRL1_INVIN_MASK               0x100UL                                     /**< Bit mask for CRC_INVIN                      */
#define _CRC_CTRL1_INVIN_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for CRC_CTRL1                  */
#define _CRC_CTRL1_INVIN_NO                 0x00000000UL                                /**< Mode NO for CRC_CTRL1                       */
#define _CRC_CTRL1_INVIN_YES                0x00000001UL                                /**< Mode YES for CRC_CTRL1                      */
#define CRC_CTRL1_INVIN_DEFAULT             (_CRC_CTRL1_INVIN_DEFAULT << 8)             /**< Shifted mode DEFAULT for CRC_CTRL1          */
#define CRC_CTRL1_INVIN_NO                  (_CRC_CTRL1_INVIN_NO << 8)                  /**< Shifted mode NO for CRC_CTRL1               */
#define CRC_CTRL1_INVIN_YES                 (_CRC_CTRL1_INVIN_YES << 8)                 /**< Shifted mode YES for CRC_CTRL1              */
#define CRC_CTRL1_ENCODE                    (0x1UL << 14)                               /**< New BitField                                */
#define _CRC_CTRL1_ENCODE_SHIFT             14                                          /**< Shift value for CRC_ENCODE                  */
#define _CRC_CTRL1_ENCODE_MASK              0x4000UL                                    /**< Bit mask for CRC_ENCODE                     */
#define _CRC_CTRL1_ENCODE_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for CRC_CTRL1                  */
#define _CRC_CTRL1_ENCODE_NO                0x00000000UL                                /**< Mode NO for CRC_CTRL1                       */
#define _CRC_CTRL1_ENCODE_YES               0x00000001UL                                /**< Mode YES for CRC_CTRL1                      */
#define CRC_CTRL1_ENCODE_DEFAULT            (_CRC_CTRL1_ENCODE_DEFAULT << 14)           /**< Shifted mode DEFAULT for CRC_CTRL1          */
#define CRC_CTRL1_ENCODE_NO                 (_CRC_CTRL1_ENCODE_NO << 14)                /**< Shifted mode NO for CRC_CTRL1               */
#define CRC_CTRL1_ENCODE_YES                (_CRC_CTRL1_ENCODE_YES << 14)               /**< Shifted mode YES for CRC_CTRL1              */
#define CRC_CTRL1_GENIT                     (0x1UL << 15)                               /**< New BitField                                */
#define _CRC_CTRL1_GENIT_SHIFT              15                                          /**< Shift value for CRC_GENIT                   */
#define _CRC_CTRL1_GENIT_MASK               0x8000UL                                    /**< Bit mask for CRC_GENIT                      */
#define _CRC_CTRL1_GENIT_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for CRC_CTRL1                  */
#define _CRC_CTRL1_GENIT_NO                 0x00000000UL                                /**< Mode NO for CRC_CTRL1                       */
#define _CRC_CTRL1_GENIT_YES                0x00000001UL                                /**< Mode YES for CRC_CTRL1                      */
#define CRC_CTRL1_GENIT_DEFAULT             (_CRC_CTRL1_GENIT_DEFAULT << 15)            /**< Shifted mode DEFAULT for CRC_CTRL1          */
#define CRC_CTRL1_GENIT_NO                  (_CRC_CTRL1_GENIT_NO << 15)                 /**< Shifted mode NO for CRC_CTRL1               */
#define CRC_CTRL1_GENIT_YES                 (_CRC_CTRL1_GENIT_YES << 15)                /**< Shifted mode YES for CRC_CTRL1              */
#define CRC_CTRL1_DEBUG                     (0x1UL << 31)                               /**< New BitField                                */
#define _CRC_CTRL1_DEBUG_SHIFT              31                                          /**< Shift value for CRC_DEBUG                   */
#define _CRC_CTRL1_DEBUG_MASK               0x80000000UL                                /**< Bit mask for CRC_DEBUG                      */
#define _CRC_CTRL1_DEBUG_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for CRC_CTRL1                  */
#define _CRC_CTRL1_DEBUG_NO                 0x00000000UL                                /**< Mode NO for CRC_CTRL1                       */
#define _CRC_CTRL1_DEBUG_YES                0x00000001UL                                /**< Mode YES for CRC_CTRL1                      */
#define CRC_CTRL1_DEBUG_DEFAULT             (_CRC_CTRL1_DEBUG_DEFAULT << 31)            /**< Shifted mode DEFAULT for CRC_CTRL1          */
#define CRC_CTRL1_DEBUG_NO                  (_CRC_CTRL1_DEBUG_NO << 31)                 /**< Shifted mode NO for CRC_CTRL1               */
#define CRC_CTRL1_DEBUG_YES                 (_CRC_CTRL1_DEBUG_YES << 31)                /**< Shifted mode YES for CRC_CTRL1              */

/* Bit fields for CRC CTRL2 */
#define _CRC_CTRL2_RESETVALUE               0x00000000UL                                /**< Default value for CRC_CTRL2                 */
#define _CRC_CTRL2_MASK                     0x007FFFFFUL                                /**< Mask for CRC_CTRL2                          */
#define _CRC_CTRL2_LENGTH_SHIFT             0                                           /**< Shift value for CRC_LENGTH                  */
#define _CRC_CTRL2_LENGTH_MASK              0x7FUL                                      /**< Bit mask for CRC_LENGTH                     */
#define _CRC_CTRL2_LENGTH_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for CRC_CTRL2                  */
#define _CRC_CTRL2_LENGTH_CRC8              0x00000008UL                                /**< Mode CRC8 for CRC_CTRL2                     */
#define _CRC_CTRL2_LENGTH_CRC16             0x00000010UL                                /**< Mode CRC16 for CRC_CTRL2                    */
#define _CRC_CTRL2_LENGTH_CRC32             0x00000020UL                                /**< Mode CRC32 for CRC_CTRL2                    */
#define CRC_CTRL2_LENGTH_DEFAULT            (_CRC_CTRL2_LENGTH_DEFAULT << 0)            /**< Shifted mode DEFAULT for CRC_CTRL2          */
#define CRC_CTRL2_LENGTH_CRC8               (_CRC_CTRL2_LENGTH_CRC8 << 0)               /**< Shifted mode CRC8 for CRC_CTRL2             */
#define CRC_CTRL2_LENGTH_CRC16              (_CRC_CTRL2_LENGTH_CRC16 << 0)              /**< Shifted mode CRC16 for CRC_CTRL2            */
#define CRC_CTRL2_LENGTH_CRC32              (_CRC_CTRL2_LENGTH_CRC32 << 0)              /**< Shifted mode CRC32 for CRC_CTRL2            */
#define _CRC_CTRL2_NBBITS_SHIFT             7                                           /**< Shift value for CRC_NBBITS                  */
#define _CRC_CTRL2_NBBITS_MASK              0x7FFF80UL                                  /**< Bit mask for CRC_NBBITS                     */
#define _CRC_CTRL2_NBBITS_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for CRC_CTRL2                  */
#define CRC_CTRL2_NBBITS_DEFAULT            (_CRC_CTRL2_NBBITS_DEFAULT << 7)            /**< Shifted mode DEFAULT for CRC_CTRL2          */

/* Bit fields for CRC POLY */
#define _CRC_POLY_RESETVALUE                0x000000E0UL                                /**< Default value for CRC_POLY                  */
#define _CRC_POLY_MASK                      0xFFFFFFFFUL                                /**< Mask for CRC_POLY                           */
#define _CRC_POLY_POLY_SHIFT                0                                           /**< Shift value for CRC_POLY                    */
#define _CRC_POLY_POLY_MASK                 0xFFFFFFFFUL                                /**< Bit mask for CRC_POLY                       */
#define _CRC_POLY_POLY_DEFAULT              0x000000E0UL                                /**< Mode DEFAULT for CRC_POLY                   */
#define CRC_POLY_POLY_DEFAULT               (_CRC_POLY_POLY_DEFAULT << 0)               /**< Shifted mode DEFAULT for CRC_POLY           */

/* Bit fields for CRC INIT */
#define _CRC_INIT_RESETVALUE                0x00000000UL                                /**< Default value for CRC_INIT                  */
#define _CRC_INIT_MASK                      0xFFFFFFFFUL                                /**< Mask for CRC_INIT                           */
#define _CRC_INIT_INIT_SHIFT                0                                           /**< Shift value for CRC_INIT                    */
#define _CRC_INIT_INIT_MASK                 0xFFFFFFFFUL                                /**< Bit mask for CRC_INIT                       */
#define _CRC_INIT_INIT_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for CRC_INIT                   */
#define CRC_INIT_INIT_DEFAULT               (_CRC_INIT_INIT_DEFAULT << 0)               /**< Shifted mode DEFAULT for CRC_INIT           */

/* Bit fields for CRC STATUS */
#define _CRC_STATUS_RESETVALUE              0x00000000UL                                /**< Default value for CRC_STATUS                */
#define _CRC_STATUS_MASK                    0x00000003UL                                /**< Mask for CRC_STATUS                         */
#define CRC_STATUS_STATE                    (0x1UL << 0)                                /**< New BitField                                */
#define _CRC_STATUS_STATE_SHIFT             0                                           /**< Shift value for CRC_STATE                   */
#define _CRC_STATUS_STATE_MASK              0x1UL                                       /**< Bit mask for CRC_STATE                      */
#define _CRC_STATUS_STATE_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for CRC_STATUS                 */
#define _CRC_STATUS_STATE_Computing         0x00000000UL                                /**< Mode Computing for CRC_STATUS               */
#define _CRC_STATUS_STATE_Completed         0x00000001UL                                /**< Mode Completed for CRC_STATUS               */
#define CRC_STATUS_STATE_DEFAULT            (_CRC_STATUS_STATE_DEFAULT << 0)            /**< Shifted mode DEFAULT for CRC_STATUS         */
#define CRC_STATUS_STATE_Computing          (_CRC_STATUS_STATE_Computing << 0)          /**< Shifted mode Computing for CRC_STATUS       */
#define CRC_STATUS_STATE_Completed          (_CRC_STATUS_STATE_Completed << 0)          /**< Shifted mode Completed for CRC_STATUS       */
#define CRC_STATUS_STATUS                   (0x1UL << 1)                                /**< New BitField                                */
#define _CRC_STATUS_STATUS_SHIFT            1                                           /**< Shift value for CRC_STATUS                  */
#define _CRC_STATUS_STATUS_MASK             0x2UL                                       /**< Bit mask for CRC_STATUS                     */
#define _CRC_STATUS_STATUS_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for CRC_STATUS                 */
#define _CRC_STATUS_STATUS_Good             0x00000000UL                                /**< Mode Good for CRC_STATUS                    */
#define _CRC_STATUS_STATUS_Failed           0x00000001UL                                /**< Mode Failed for CRC_STATUS                  */
#define CRC_STATUS_STATUS_DEFAULT           (_CRC_STATUS_STATUS_DEFAULT << 1)           /**< Shifted mode DEFAULT for CRC_STATUS         */
#define CRC_STATUS_STATUS_Good              (_CRC_STATUS_STATUS_Good << 1)              /**< Shifted mode Good for CRC_STATUS            */
#define CRC_STATUS_STATUS_Failed            (_CRC_STATUS_STATUS_Failed << 1)            /**< Shifted mode Failed for CRC_STATUS          */

/* Bit fields for CRC REFERENCE */
#define _CRC_REFERENCE_RESETVALUE           0x00000000UL                                /**< Default value for CRC_REFERENCE             */
#define _CRC_REFERENCE_MASK                 0xFFFFFFFFUL                                /**< Mask for CRC_REFERENCE                      */
#define _CRC_REFERENCE_REFERENCE_SHIFT      0                                           /**< Shift value for CRC_REFERENCE               */
#define _CRC_REFERENCE_REFERENCE_MASK       0xFFFFFFFFUL                                /**< Bit mask for CRC_REFERENCE                  */
#define _CRC_REFERENCE_REFERENCE_DEFAULT    0x00000000UL                                /**< Mode DEFAULT for CRC_REFERENCE              */
#define CRC_REFERENCE_REFERENCE_DEFAULT     (_CRC_REFERENCE_REFERENCE_DEFAULT << 0)     /**< Shifted mode DEFAULT for CRC_REFERENCE      */

/* Bit fields for CRC RECEIVED */
#define _CRC_RECEIVED_RESETVALUE            0x00000000UL                                /**< Default value for CRC_RECEIVED              */
#define _CRC_RECEIVED_MASK                  0xFFFFFFFFUL                                /**< Mask for CRC_RECEIVED                       */
#define _CRC_RECEIVED_RECEIVED_SHIFT        0                                           /**< Shift value for CRC_RECEIVED                */
#define _CRC_RECEIVED_RECEIVED_MASK         0xFFFFFFFFUL                                /**< Bit mask for CRC_RECEIVED                   */
#define _CRC_RECEIVED_RECEIVED_DEFAULT      0x00000000UL                                /**< Mode DEFAULT for CRC_RECEIVED               */
#define CRC_RECEIVED_RECEIVED_DEFAULT       (_CRC_RECEIVED_RECEIVED_DEFAULT << 0)       /**< Shifted mode DEFAULT for CRC_RECEIVED       */

/* Bit fields for CRC IF */
#define _CRC_IF_RESETVALUE                  0x00000000UL                                /**< Default value for CRC_IF                    */
#define _CRC_IF_MASK                        0x00000001UL                                /**< Mask for CRC_IF                             */
#define CRC_IF_DONE                         (0x1UL << 0)                                /**< New BitField                                */
#define _CRC_IF_DONE_SHIFT                  0                                           /**< Shift value for CRC_DONE                    */
#define _CRC_IF_DONE_MASK                   0x1UL                                       /**< Bit mask for CRC_DONE                       */
#define _CRC_IF_DONE_DEFAULT                0x00000000UL                                /**< Mode DEFAULT for CRC_IF                     */
#define CRC_IF_DONE_DEFAULT                 (_CRC_IF_DONE_DEFAULT << 0)                 /**< Shifted mode DEFAULT for CRC_IF             */

/* Bit fields for CRC IEN */
#define _CRC_IEN_RESETVALUE                 0x00000000UL                                /**< Default value for CRC_IEN                   */
#define _CRC_IEN_MASK                       0x00000001UL                                /**< Mask for CRC_IEN                            */
#define CRC_IEN_DONE                        (0x1UL << 0)                                /**< New BitField                                */
#define _CRC_IEN_DONE_SHIFT                 0                                           /**< Shift value for CRC_DONE                    */
#define _CRC_IEN_DONE_MASK                  0x1UL                                       /**< Bit mask for CRC_DONE                       */
#define _CRC_IEN_DONE_DEFAULT               0x00000000UL                                /**< Mode DEFAULT for CRC_IEN                    */
#define CRC_IEN_DONE_DEFAULT                (_CRC_IEN_DONE_DEFAULT << 0)                /**< Shifted mode DEFAULT for CRC_IEN            */

/* Bit fields for CRC CTRL3 */
#define _CRC_CTRL3_RESETVALUE               0x00000001UL                                /**< Default value for CRC_CTRL3                 */
#define _CRC_CTRL3_MASK                     0x00000001UL                                /**< Mask for CRC_CTRL3                          */
#define CRC_CTRL3_PADDING                   (0x1UL << 0)                                /**< New BitField                                */
#define _CRC_CTRL3_PADDING_SHIFT            0                                           /**< Shift value for CRC_PADDING                 */
#define _CRC_CTRL3_PADDING_MASK             0x1UL                                       /**< Bit mask for CRC_PADDING                    */
#define _CRC_CTRL3_PADDING_DEFAULT          0x00000001UL                                /**< Mode DEFAULT for CRC_CTRL3                  */
#define _CRC_CTRL3_PADDING_NO               0x00000000UL                                /**< Mode NO for CRC_CTRL3                       */
#define _CRC_CTRL3_PADDING_YES              0x00000001UL                                /**< Mode YES for CRC_CTRL3                      */
#define CRC_CTRL3_PADDING_DEFAULT           (_CRC_CTRL3_PADDING_DEFAULT << 0)           /**< Shifted mode DEFAULT for CRC_CTRL3          */
#define CRC_CTRL3_PADDING_NO                (_CRC_CTRL3_PADDING_NO << 0)                /**< Shifted mode NO for CRC_CTRL3               */
#define CRC_CTRL3_PADDING_YES               (_CRC_CTRL3_PADDING_YES << 0)               /**< Shifted mode YES for CRC_CTRL3              */

/** @} End of group EFR32FG25_CRC_BitFields */
/** @} End of group EFR32FG25_CRC */
/** @} End of group Parts */

#endif /* EFR32FG25_CRC_H */
