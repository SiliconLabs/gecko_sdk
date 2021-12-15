/**************************************************************************//**
 * @file
 * @brief EFR32FG25 FFT register and bit field definitions
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
#ifndef EFR32FG25_FFT_H
#define EFR32FG25_FFT_H
#define FFT_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_FFT FFT
 * @{
 * @brief EFR32FG25 FFT Register Declaration.
 *****************************************************************************/

/** FFT Register Declaration. */
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
  __IOM uint32_t FMTOUT;                        /**< New Register                                       */
  uint32_t       RESERVED4[79U];                /**< Reserved for future use                            */
  __IOM uint32_t CTRL;                          /**< New Register                                       */
  __IOM uint32_t CTRL2;                         /**< New Register                                       */
  __IOM uint32_t IF;                            /**< Interrupt Flags                                    */
  __IOM uint32_t IEN;                           /**< Interrupt Enable                                   */
  uint32_t       RESERVED5[892U];               /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_SET;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_SET;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_SET;                   /**< New Register                                       */
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
  __IOM uint32_t CTRL2_SET;                     /**< New Register                                       */
  __IOM uint32_t IF_SET;                        /**< Interrupt Flags                                    */
  __IOM uint32_t IEN_SET;                       /**< Interrupt Enable                                   */
  uint32_t       RESERVED11[892U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_CLR;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_CLR;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_CLR;                   /**< New Register                                       */
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
  __IOM uint32_t CTRL2_CLR;                     /**< New Register                                       */
  __IOM uint32_t IF_CLR;                        /**< Interrupt Flags                                    */
  __IOM uint32_t IEN_CLR;                       /**< Interrupt Enable                                   */
  uint32_t       RESERVED17[892U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_TGL;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_TGL;                     /**< Software Reset                                     */
  __IOM uint32_t CONNECT_TGL;                   /**< New Register                                       */
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
  __IOM uint32_t CTRL2_TGL;                     /**< New Register                                       */
  __IOM uint32_t IF_TGL;                        /**< Interrupt Flags                                    */
  __IOM uint32_t IEN_TGL;                       /**< Interrupt Enable                                   */
} FFT_TypeDef;
/** @} End of group EFR32FG25_FFT */

/**************************************************************************//**
 * @addtogroup EFR32FG25_FFT
 * @{
 * @defgroup EFR32FG25_FFT_BitFields FFT Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for FFT IPVERSION */
#define _FFT_IPVERSION_RESETVALUE                  0x00000001UL                            /**< Default value for FFT_IPVERSION             */
#define _FFT_IPVERSION_MASK                        0xFFFFFFFFUL                            /**< Mask for FFT_IPVERSION                      */
#define _FFT_IPVERSION_IPVERSION_SHIFT             0                                       /**< Shift value for FFT_IPVERSION               */
#define _FFT_IPVERSION_IPVERSION_MASK              0xFFFFFFFFUL                            /**< Bit mask for FFT_IPVERSION                  */
#define _FFT_IPVERSION_IPVERSION_DEFAULT           0x00000001UL                            /**< Mode DEFAULT for FFT_IPVERSION              */
#define FFT_IPVERSION_IPVERSION_DEFAULT            (_FFT_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for FFT_IPVERSION      */

/* Bit fields for FFT EN */
#define _FFT_EN_RESETVALUE                         0x00000000UL                         /**< Default value for FFT_EN                    */
#define _FFT_EN_MASK                               0x00000003UL                         /**< Mask for FFT_EN                             */
#define FFT_EN_EN                                  (0x1UL << 0)                         /**< Module Enable                               */
#define _FFT_EN_EN_SHIFT                           0                                    /**< Shift value for FFT_EN                      */
#define _FFT_EN_EN_MASK                            0x1UL                                /**< Bit mask for FFT_EN                         */
#define _FFT_EN_EN_DEFAULT                         0x00000000UL                         /**< Mode DEFAULT for FFT_EN                     */
#define FFT_EN_EN_DEFAULT                          (_FFT_EN_EN_DEFAULT << 0)            /**< Shifted mode DEFAULT for FFT_EN             */
#define FFT_EN_DISABLING                           (0x1UL << 1)                         /**< Disablement Busy Status                     */
#define _FFT_EN_DISABLING_SHIFT                    1                                    /**< Shift value for FFT_DISABLING               */
#define _FFT_EN_DISABLING_MASK                     0x2UL                                /**< Bit mask for FFT_DISABLING                  */
#define _FFT_EN_DISABLING_DEFAULT                  0x00000000UL                         /**< Mode DEFAULT for FFT_EN                     */
#define FFT_EN_DISABLING_DEFAULT                   (_FFT_EN_DISABLING_DEFAULT << 1)     /**< Shifted mode DEFAULT for FFT_EN             */

/* Bit fields for FFT SWRST */
#define _FFT_SWRST_RESETVALUE                      0x00000000UL                         /**< Default value for FFT_SWRST                 */
#define _FFT_SWRST_MASK                            0x00000003UL                         /**< Mask for FFT_SWRST                          */
#define FFT_SWRST_SWRST                            (0x1UL << 0)                         /**< Software Reset Command                      */
#define _FFT_SWRST_SWRST_SHIFT                     0                                    /**< Shift value for FFT_SWRST                   */
#define _FFT_SWRST_SWRST_MASK                      0x1UL                                /**< Bit mask for FFT_SWRST                      */
#define _FFT_SWRST_SWRST_DEFAULT                   0x00000000UL                         /**< Mode DEFAULT for FFT_SWRST                  */
#define FFT_SWRST_SWRST_DEFAULT                    (_FFT_SWRST_SWRST_DEFAULT << 0)      /**< Shifted mode DEFAULT for FFT_SWRST          */
#define FFT_SWRST_RESETTING                        (0x1UL << 1)                         /**< Software Reset Busy Status                  */
#define _FFT_SWRST_RESETTING_SHIFT                 1                                    /**< Shift value for FFT_RESETTING               */
#define _FFT_SWRST_RESETTING_MASK                  0x2UL                                /**< Bit mask for FFT_RESETTING                  */
#define _FFT_SWRST_RESETTING_DEFAULT               0x00000000UL                         /**< Mode DEFAULT for FFT_SWRST                  */
#define FFT_SWRST_RESETTING_DEFAULT                (_FFT_SWRST_RESETTING_DEFAULT << 1)  /**< Shifted mode DEFAULT for FFT_SWRST          */

/* Bit fields for FFT CONNECT */
#define _FFT_CONNECT_RESETVALUE                    0x00000000UL                         /**< Default value for FFT_CONNECT               */
#define _FFT_CONNECT_MASK                          0x00000101UL                         /**< Mask for FFT_CONNECT                        */
#define FFT_CONNECT_IN                             (0x1UL << 0)                         /**< Input FIFO connect                          */
#define _FFT_CONNECT_IN_SHIFT                      0                                    /**< Shift value for FFT_IN                      */
#define _FFT_CONNECT_IN_MASK                       0x1UL                                /**< Bit mask for FFT_IN                         */
#define _FFT_CONNECT_IN_DEFAULT                    0x00000000UL                         /**< Mode DEFAULT for FFT_CONNECT                */
#define FFT_CONNECT_IN_DEFAULT                     (_FFT_CONNECT_IN_DEFAULT << 0)       /**< Shifted mode DEFAULT for FFT_CONNECT        */
#define FFT_CONNECT_OUT                            (0x1UL << 8)                         /**< Output FIFO connect                         */
#define _FFT_CONNECT_OUT_SHIFT                     8                                    /**< Shift value for FFT_OUT                     */
#define _FFT_CONNECT_OUT_MASK                      0x100UL                              /**< Bit mask for FFT_OUT                        */
#define _FFT_CONNECT_OUT_DEFAULT                   0x00000000UL                         /**< Mode DEFAULT for FFT_CONNECT                */
#define FFT_CONNECT_OUT_DEFAULT                    (_FFT_CONNECT_OUT_DEFAULT << 8)      /**< Shifted mode DEFAULT for FFT_CONNECT        */

/* Bit fields for FFT DISCLK */
#define _FFT_DISCLK_RESETVALUE                     0x00000002UL                         /**< Default value for FFT_DISCLK                */
#define _FFT_DISCLK_MASK                           0x00000003UL                         /**< Mask for FFT_DISCLK                         */
#define _FFT_DISCLK_DISCLK_SHIFT                   0                                    /**< Shift value for FFT_DISCLK                  */
#define _FFT_DISCLK_DISCLK_MASK                    0x3UL                                /**< Bit mask for FFT_DISCLK                     */
#define _FFT_DISCLK_DISCLK_DEFAULT                 0x00000002UL                         /**< Mode DEFAULT for FFT_DISCLK                 */
#define _FFT_DISCLK_DISCLK_NONE                    0x00000000UL                         /**< Mode NONE for FFT_DISCLK                    */
#define _FFT_DISCLK_DISCLK_ALL                     0x00000001UL                         /**< Mode ALL for FFT_DISCLK                     */
#define _FFT_DISCLK_DISCLK_AUTO                    0x00000002UL                         /**< Mode AUTO for FFT_DISCLK                    */
#define _FFT_DISCLK_DISCLK_NOTUSED                 0x00000003UL                         /**< Mode NOTUSED for FFT_DISCLK                 */
#define FFT_DISCLK_DISCLK_DEFAULT                  (_FFT_DISCLK_DISCLK_DEFAULT << 0)    /**< Shifted mode DEFAULT for FFT_DISCLK         */
#define FFT_DISCLK_DISCLK_NONE                     (_FFT_DISCLK_DISCLK_NONE << 0)       /**< Shifted mode NONE for FFT_DISCLK            */
#define FFT_DISCLK_DISCLK_ALL                      (_FFT_DISCLK_DISCLK_ALL << 0)        /**< Shifted mode ALL for FFT_DISCLK             */
#define FFT_DISCLK_DISCLK_AUTO                     (_FFT_DISCLK_DISCLK_AUTO << 0)       /**< Shifted mode AUTO for FFT_DISCLK            */
#define FFT_DISCLK_DISCLK_NOTUSED                  (_FFT_DISCLK_DISCLK_NOTUSED << 0)    /**< Shifted mode NOTUSED for FFT_DISCLK         */

/* Bit fields for FFT FIFOIN */
#define _FFT_FIFOIN_RESETVALUE                     0x00000000UL                         /**< Default value for FFT_FIFOIN                */
#define _FFT_FIFOIN_MASK                           0x1FFF3F0FUL                         /**< Mask for FFT_FIFOIN                         */
#define _FFT_FIFOIN_FID_SHIFT                      0                                    /**< Shift value for FFT_FID                     */
#define _FFT_FIFOIN_FID_MASK                       0xFUL                                /**< Bit mask for FFT_FID                        */
#define _FFT_FIFOIN_FID_DEFAULT                    0x00000000UL                         /**< Mode DEFAULT for FFT_FIFOIN                 */
#define FFT_FIFOIN_FID_DEFAULT                     (_FFT_FIFOIN_FID_DEFAULT << 0)       /**< Shifted mode DEFAULT for FFT_FIFOIN         */
#define _FFT_FIFOIN_CID_SHIFT                      8                                    /**< Shift value for FFT_CID                     */
#define _FFT_FIFOIN_CID_MASK                       0x3F00UL                             /**< Bit mask for FFT_CID                        */
#define _FFT_FIFOIN_CID_DEFAULT                    0x00000000UL                         /**< Mode DEFAULT for FFT_FIFOIN                 */
#define FFT_FIFOIN_CID_DEFAULT                     (_FFT_FIFOIN_CID_DEFAULT << 8)       /**< Shifted mode DEFAULT for FFT_FIFOIN         */
#define _FFT_FIFOIN_REM_SHIFT                      16                                   /**< Shift value for FFT_REM                     */
#define _FFT_FIFOIN_REM_MASK                       0xFF0000UL                           /**< Bit mask for FFT_REM                        */
#define _FFT_FIFOIN_REM_DEFAULT                    0x00000000UL                         /**< Mode DEFAULT for FFT_FIFOIN                 */
#define FFT_FIFOIN_REM_DEFAULT                     (_FFT_FIFOIN_REM_DEFAULT << 16)      /**< Shifted mode DEFAULT for FFT_FIFOIN         */
#define _FFT_FIFOIN_ALARM_SHIFT                    24                                   /**< Shift value for FFT_ALARM                   */
#define _FFT_FIFOIN_ALARM_MASK                     0x1F000000UL                         /**< Bit mask for FFT_ALARM                      */
#define _FFT_FIFOIN_ALARM_DEFAULT                  0x00000000UL                         /**< Mode DEFAULT for FFT_FIFOIN                 */
#define FFT_FIFOIN_ALARM_DEFAULT                   (_FFT_FIFOIN_ALARM_DEFAULT << 24)    /**< Shifted mode DEFAULT for FFT_FIFOIN         */

/* Bit fields for FFT FIFOOUT */
#define _FFT_FIFOOUT_RESETVALUE                    0x00000000UL                         /**< Default value for FFT_FIFOOUT               */
#define _FFT_FIFOOUT_MASK                          0x1FFF0000UL                         /**< Mask for FFT_FIFOOUT                        */
#define _FFT_FIFOOUT_CNT_SHIFT                     16                                   /**< Shift value for FFT_CNT                     */
#define _FFT_FIFOOUT_CNT_MASK                      0xFF0000UL                           /**< Bit mask for FFT_CNT                        */
#define _FFT_FIFOOUT_CNT_DEFAULT                   0x00000000UL                         /**< Mode DEFAULT for FFT_FIFOOUT                */
#define FFT_FIFOOUT_CNT_DEFAULT                    (_FFT_FIFOOUT_CNT_DEFAULT << 16)     /**< Shifted mode DEFAULT for FFT_FIFOOUT        */
#define _FFT_FIFOOUT_ALARM_SHIFT                   24                                   /**< Shift value for FFT_ALARM                   */
#define _FFT_FIFOOUT_ALARM_MASK                    0x1F000000UL                         /**< Bit mask for FFT_ALARM                      */
#define _FFT_FIFOOUT_ALARM_DEFAULT                 0x00000000UL                         /**< Mode DEFAULT for FFT_FIFOOUT                */
#define FFT_FIFOOUT_ALARM_DEFAULT                  (_FFT_FIFOOUT_ALARM_DEFAULT << 24)   /**< Shifted mode DEFAULT for FFT_FIFOOUT        */

/* Bit fields for FFT FMTIN */
#define _FFT_FMTIN_RESETVALUE                      0x00000000UL                          /**< Default value for FFT_FMTIN                 */
#define _FFT_FMTIN_MASK                            0x00030300UL                          /**< Mask for FFT_FMTIN                          */
#define _FFT_FMTIN_ELEMNB_SHIFT                    8                                     /**< Shift value for FFT_ELEMNB                  */
#define _FFT_FMTIN_ELEMNB_MASK                     0x300UL                               /**< Bit mask for FFT_ELEMNB                     */
#define _FFT_FMTIN_ELEMNB_DEFAULT                  0x00000000UL                          /**< Mode DEFAULT for FFT_FMTIN                  */
#define _FFT_FMTIN_ELEMNB_ONE                      0x00000000UL                          /**< Mode ONE for FFT_FMTIN                      */
#define _FFT_FMTIN_ELEMNB_TWO                      0x00000001UL                          /**< Mode TWO for FFT_FMTIN                      */
#define _FFT_FMTIN_ELEMNB_FOUR                     0x00000002UL                          /**< Mode FOUR for FFT_FMTIN                     */
#define FFT_FMTIN_ELEMNB_DEFAULT                   (_FFT_FMTIN_ELEMNB_DEFAULT << 8)      /**< Shifted mode DEFAULT for FFT_FMTIN          */
#define FFT_FMTIN_ELEMNB_ONE                       (_FFT_FMTIN_ELEMNB_ONE << 8)          /**< Shifted mode ONE for FFT_FMTIN              */
#define FFT_FMTIN_ELEMNB_TWO                       (_FFT_FMTIN_ELEMNB_TWO << 8)          /**< Shifted mode TWO for FFT_FMTIN              */
#define FFT_FMTIN_ELEMNB_FOUR                      (_FFT_FMTIN_ELEMNB_FOUR << 8)         /**< Shifted mode FOUR for FFT_FMTIN             */
#define _FFT_FMTIN_ELEMALIGN_SHIFT                 16                                    /**< Shift value for FFT_ELEMALIGN               */
#define _FFT_FMTIN_ELEMALIGN_MASK                  0x30000UL                             /**< Bit mask for FFT_ELEMALIGN                  */
#define _FFT_FMTIN_ELEMALIGN_DEFAULT               0x00000000UL                          /**< Mode DEFAULT for FFT_FMTIN                  */
#define _FFT_FMTIN_ELEMALIGN_WORD                  0x00000000UL                          /**< Mode WORD for FFT_FMTIN                     */
#define _FFT_FMTIN_ELEMALIGN_HALFWORD              0x00000001UL                          /**< Mode HALFWORD for FFT_FMTIN                 */
#define _FFT_FMTIN_ELEMALIGN_BYTE                  0x00000002UL                          /**< Mode BYTE for FFT_FMTIN                     */
#define FFT_FMTIN_ELEMALIGN_DEFAULT                (_FFT_FMTIN_ELEMALIGN_DEFAULT << 16)  /**< Shifted mode DEFAULT for FFT_FMTIN          */
#define FFT_FMTIN_ELEMALIGN_WORD                   (_FFT_FMTIN_ELEMALIGN_WORD << 16)     /**< Shifted mode WORD for FFT_FMTIN             */
#define FFT_FMTIN_ELEMALIGN_HALFWORD               (_FFT_FMTIN_ELEMALIGN_HALFWORD << 16) /**< Shifted mode HALFWORD for FFT_FMTIN         */
#define FFT_FMTIN_ELEMALIGN_BYTE                   (_FFT_FMTIN_ELEMALIGN_BYTE << 16)     /**< Shifted mode BYTE for FFT_FMTIN             */

/* Bit fields for FFT FMTOUT */
#define _FFT_FMTOUT_RESETVALUE                     0x0000000DUL                           /**< Default value for FFT_FMTOUT                */
#define _FFT_FMTOUT_MASK                           0x0003001FUL                           /**< Mask for FFT_FMTOUT                         */
#define _FFT_FMTOUT_ELEMSIZE_SHIFT                 0                                      /**< Shift value for FFT_ELEMSIZE                */
#define _FFT_FMTOUT_ELEMSIZE_MASK                  0x1FUL                                 /**< Bit mask for FFT_ELEMSIZE                   */
#define _FFT_FMTOUT_ELEMSIZE_DEFAULT               0x0000000DUL                           /**< Mode DEFAULT for FFT_FMTOUT                 */
#define FFT_FMTOUT_ELEMSIZE_DEFAULT                (_FFT_FMTOUT_ELEMSIZE_DEFAULT << 0)    /**< Shifted mode DEFAULT for FFT_FMTOUT         */
#define _FFT_FMTOUT_ELEMALIGN_SHIFT                16                                     /**< Shift value for FFT_ELEMALIGN               */
#define _FFT_FMTOUT_ELEMALIGN_MASK                 0x30000UL                              /**< Bit mask for FFT_ELEMALIGN                  */
#define _FFT_FMTOUT_ELEMALIGN_DEFAULT              0x00000000UL                           /**< Mode DEFAULT for FFT_FMTOUT                 */
#define _FFT_FMTOUT_ELEMALIGN_WORD                 0x00000000UL                           /**< Mode WORD for FFT_FMTOUT                    */
#define _FFT_FMTOUT_ELEMALIGN_HALFWORD             0x00000001UL                           /**< Mode HALFWORD for FFT_FMTOUT                */
#define _FFT_FMTOUT_ELEMALIGN_BYTE                 0x00000002UL                           /**< Mode BYTE for FFT_FMTOUT                    */
#define FFT_FMTOUT_ELEMALIGN_DEFAULT               (_FFT_FMTOUT_ELEMALIGN_DEFAULT << 16)  /**< Shifted mode DEFAULT for FFT_FMTOUT         */
#define FFT_FMTOUT_ELEMALIGN_WORD                  (_FFT_FMTOUT_ELEMALIGN_WORD << 16)     /**< Shifted mode WORD for FFT_FMTOUT            */
#define FFT_FMTOUT_ELEMALIGN_HALFWORD              (_FFT_FMTOUT_ELEMALIGN_HALFWORD << 16) /**< Shifted mode HALFWORD for FFT_FMTOUT        */
#define FFT_FMTOUT_ELEMALIGN_BYTE                  (_FFT_FMTOUT_ELEMALIGN_BYTE << 16)     /**< Shifted mode BYTE for FFT_FMTOUT            */

/* Bit fields for FFT CTRL */
#define _FFT_CTRL_RESETVALUE                       0x0038080EUL                                    /**< Default value for FFT_CTRL                  */
#define _FFT_CTRL_MASK                             0xFFFFFFFFUL                                    /**< Mask for FFT_CTRL                           */
#define FFT_CTRL_MODE                              (0x1UL << 0)                                    /**< New BitField                                */
#define _FFT_CTRL_MODE_SHIFT                       0                                               /**< Shift value for FFT_MODE                    */
#define _FFT_CTRL_MODE_MASK                        0x1UL                                           /**< Bit mask for FFT_MODE                       */
#define _FFT_CTRL_MODE_DEFAULT                     0x00000000UL                                    /**< Mode DEFAULT for FFT_CTRL                   */
#define _FFT_CTRL_MODE_FORWARD                     0x00000000UL                                    /**< Mode FORWARD for FFT_CTRL                   */
#define _FFT_CTRL_MODE_BACKWARD                    0x00000001UL                                    /**< Mode BACKWARD for FFT_CTRL                  */
#define FFT_CTRL_MODE_DEFAULT                      (_FFT_CTRL_MODE_DEFAULT << 0)                   /**< Shifted mode DEFAULT for FFT_CTRL           */
#define FFT_CTRL_MODE_FORWARD                      (_FFT_CTRL_MODE_FORWARD << 0)                   /**< Shifted mode FORWARD for FFT_CTRL           */
#define FFT_CTRL_MODE_BACKWARD                     (_FFT_CTRL_MODE_BACKWARD << 0)                  /**< Shifted mode BACKWARD for FFT_CTRL          */
#define _FFT_CTRL_SIZE_SHIFT                       1                                               /**< Shift value for FFT_SIZE                    */
#define _FFT_CTRL_SIZE_MASK                        0x1EUL                                          /**< Bit mask for FFT_SIZE                       */
#define _FFT_CTRL_SIZE_DEFAULT                     0x00000007UL                                    /**< Mode DEFAULT for FFT_CTRL                   */
#define _FFT_CTRL_SIZE_FFT16                       0x00000004UL                                    /**< Mode FFT16 for FFT_CTRL                     */
#define _FFT_CTRL_SIZE_FFT32                       0x00000005UL                                    /**< Mode FFT32 for FFT_CTRL                     */
#define _FFT_CTRL_SIZE_FFT64                       0x00000006UL                                    /**< Mode FFT64 for FFT_CTRL                     */
#define _FFT_CTRL_SIZE_FFT128                      0x00000007UL                                    /**< Mode FFT128 for FFT_CTRL                    */
#define _FFT_CTRL_SIZE_FFT256                      0x00000008UL                                    /**< Mode FFT256 for FFT_CTRL                    */
#define _FFT_CTRL_SIZE_FFT512                      0x00000009UL                                    /**< Mode FFT512 for FFT_CTRL                    */
#define FFT_CTRL_SIZE_DEFAULT                      (_FFT_CTRL_SIZE_DEFAULT << 1)                   /**< Shifted mode DEFAULT for FFT_CTRL           */
#define FFT_CTRL_SIZE_FFT16                        (_FFT_CTRL_SIZE_FFT16 << 1)                     /**< Shifted mode FFT16 for FFT_CTRL             */
#define FFT_CTRL_SIZE_FFT32                        (_FFT_CTRL_SIZE_FFT32 << 1)                     /**< Shifted mode FFT32 for FFT_CTRL             */
#define FFT_CTRL_SIZE_FFT64                        (_FFT_CTRL_SIZE_FFT64 << 1)                     /**< Shifted mode FFT64 for FFT_CTRL             */
#define FFT_CTRL_SIZE_FFT128                       (_FFT_CTRL_SIZE_FFT128 << 1)                    /**< Shifted mode FFT128 for FFT_CTRL            */
#define FFT_CTRL_SIZE_FFT256                       (_FFT_CTRL_SIZE_FFT256 << 1)                    /**< Shifted mode FFT256 for FFT_CTRL            */
#define FFT_CTRL_SIZE_FFT512                       (_FFT_CTRL_SIZE_FFT512 << 1)                    /**< Shifted mode FFT512 for FFT_CTRL            */
#define FFT_CTRL_RSTFSM                            (0x1UL << 5)                                    /**< New BitField                                */
#define _FFT_CTRL_RSTFSM_SHIFT                     5                                               /**< Shift value for FFT_RSTFSM                  */
#define _FFT_CTRL_RSTFSM_MASK                      0x20UL                                          /**< Bit mask for FFT_RSTFSM                     */
#define _FFT_CTRL_RSTFSM_DEFAULT                   0x00000000UL                                    /**< Mode DEFAULT for FFT_CTRL                   */
#define FFT_CTRL_RSTFSM_DEFAULT                    (_FFT_CTRL_RSTFSM_DEFAULT << 5)                 /**< Shifted mode DEFAULT for FFT_CTRL           */
#define FFT_CTRL_RSTSTAT                           (0x1UL << 6)                                    /**< New BitField                                */
#define _FFT_CTRL_RSTSTAT_SHIFT                    6                                               /**< Shift value for FFT_RSTSTAT                 */
#define _FFT_CTRL_RSTSTAT_MASK                     0x40UL                                          /**< Bit mask for FFT_RSTSTAT                    */
#define _FFT_CTRL_RSTSTAT_DEFAULT                  0x00000000UL                                    /**< Mode DEFAULT for FFT_CTRL                   */
#define FFT_CTRL_RSTSTAT_DEFAULT                   (_FFT_CTRL_RSTSTAT_DEFAULT << 6)                /**< Shifted mode DEFAULT for FFT_CTRL           */
#define _FFT_CTRL_GAIN_SHIFT                       7                                               /**< Shift value for FFT_GAIN                    */
#define _FFT_CTRL_GAIN_MASK                        0x1FF80UL                                       /**< Bit mask for FFT_GAIN                       */
#define _FFT_CTRL_GAIN_DEFAULT                     0x00000010UL                                    /**< Mode DEFAULT for FFT_CTRL                   */
#define FFT_CTRL_GAIN_DEFAULT                      (_FFT_CTRL_GAIN_DEFAULT << 7)                   /**< Shifted mode DEFAULT for FFT_CTRL           */
#define FFT_CTRL_SWAPIQIN                          (0x1UL << 17)                                   /**< New BitField                                */
#define _FFT_CTRL_SWAPIQIN_SHIFT                   17                                              /**< Shift value for FFT_SWAPIQIN                */
#define _FFT_CTRL_SWAPIQIN_MASK                    0x20000UL                                       /**< Bit mask for FFT_SWAPIQIN                   */
#define _FFT_CTRL_SWAPIQIN_DEFAULT                 0x00000000UL                                    /**< Mode DEFAULT for FFT_CTRL                   */
#define _FFT_CTRL_SWAPIQIN_NO                      0x00000000UL                                    /**< Mode NO for FFT_CTRL                        */
#define _FFT_CTRL_SWAPIQIN_YES                     0x00000001UL                                    /**< Mode YES for FFT_CTRL                       */
#define FFT_CTRL_SWAPIQIN_DEFAULT                  (_FFT_CTRL_SWAPIQIN_DEFAULT << 17)              /**< Shifted mode DEFAULT for FFT_CTRL           */
#define FFT_CTRL_SWAPIQIN_NO                       (_FFT_CTRL_SWAPIQIN_NO << 17)                   /**< Shifted mode NO for FFT_CTRL                */
#define FFT_CTRL_SWAPIQIN_YES                      (_FFT_CTRL_SWAPIQIN_YES << 17)                  /**< Shifted mode YES for FFT_CTRL               */
#define FFT_CTRL_SWAPIQOUT                         (0x1UL << 18)                                   /**< New BitField                                */
#define _FFT_CTRL_SWAPIQOUT_SHIFT                  18                                              /**< Shift value for FFT_SWAPIQOUT               */
#define _FFT_CTRL_SWAPIQOUT_MASK                   0x40000UL                                       /**< Bit mask for FFT_SWAPIQOUT                  */
#define _FFT_CTRL_SWAPIQOUT_DEFAULT                0x00000000UL                                    /**< Mode DEFAULT for FFT_CTRL                   */
#define _FFT_CTRL_SWAPIQOUT_NO                     0x00000000UL                                    /**< Mode NO for FFT_CTRL                        */
#define _FFT_CTRL_SWAPIQOUT_YES                    0x00000001UL                                    /**< Mode YES for FFT_CTRL                       */
#define FFT_CTRL_SWAPIQOUT_DEFAULT                 (_FFT_CTRL_SWAPIQOUT_DEFAULT << 18)             /**< Shifted mode DEFAULT for FFT_CTRL           */
#define FFT_CTRL_SWAPIQOUT_NO                      (_FFT_CTRL_SWAPIQOUT_NO << 18)                  /**< Shifted mode NO for FFT_CTRL                */
#define FFT_CTRL_SWAPIQOUT_YES                     (_FFT_CTRL_SWAPIQOUT_YES << 18)                 /**< Shifted mode YES for FFT_CTRL               */
#define FFT_CTRL_SPECTRUMSHIFT                     (0x1UL << 19)                                   /**< New BitField                                */
#define _FFT_CTRL_SPECTRUMSHIFT_SHIFT              19                                              /**< Shift value for FFT_SPECTRUMSHIFT           */
#define _FFT_CTRL_SPECTRUMSHIFT_MASK               0x80000UL                                       /**< Bit mask for FFT_SPECTRUMSHIFT              */
#define _FFT_CTRL_SPECTRUMSHIFT_DEFAULT            0x00000001UL                                    /**< Mode DEFAULT for FFT_CTRL                   */
#define _FFT_CTRL_SPECTRUMSHIFT_NoSpectrumShift    0x00000000UL                                    /**< Mode NoSpectrumShift for FFT_CTRL           */
#define _FFT_CTRL_SPECTRUMSHIFT_SpectrumShift      0x00000001UL                                    /**< Mode SpectrumShift for FFT_CTRL             */
#define FFT_CTRL_SPECTRUMSHIFT_DEFAULT             (_FFT_CTRL_SPECTRUMSHIFT_DEFAULT << 19)         /**< Shifted mode DEFAULT for FFT_CTRL           */
#define FFT_CTRL_SPECTRUMSHIFT_NoSpectrumShift     (_FFT_CTRL_SPECTRUMSHIFT_NoSpectrumShift << 19) /**< Shifted mode NoSpectrumShift for FFT_CTRL   */
#define FFT_CTRL_SPECTRUMSHIFT_SpectrumShift       (_FFT_CTRL_SPECTRUMSHIFT_SpectrumShift << 19)   /**< Shifted mode SpectrumShift for FFT_CTRL     */
#define FFT_CTRL_INVQINPUT                         (0x1UL << 20)                                   /**< New BitField                                */
#define _FFT_CTRL_INVQINPUT_SHIFT                  20                                              /**< Shift value for FFT_INVQINPUT               */
#define _FFT_CTRL_INVQINPUT_MASK                   0x100000UL                                      /**< Bit mask for FFT_INVQINPUT                  */
#define _FFT_CTRL_INVQINPUT_DEFAULT                0x00000001UL                                    /**< Mode DEFAULT for FFT_CTRL                   */
#define _FFT_CTRL_INVQINPUT_NoInversion            0x00000000UL                                    /**< Mode NoInversion for FFT_CTRL               */
#define _FFT_CTRL_INVQINPUT_Inversion              0x00000001UL                                    /**< Mode Inversion for FFT_CTRL                 */
#define FFT_CTRL_INVQINPUT_DEFAULT                 (_FFT_CTRL_INVQINPUT_DEFAULT << 20)             /**< Shifted mode DEFAULT for FFT_CTRL           */
#define FFT_CTRL_INVQINPUT_NoInversion             (_FFT_CTRL_INVQINPUT_NoInversion << 20)         /**< Shifted mode NoInversion for FFT_CTRL       */
#define FFT_CTRL_INVQINPUT_Inversion               (_FFT_CTRL_INVQINPUT_Inversion << 20)           /**< Shifted mode Inversion for FFT_CTRL         */
#define FFT_CTRL_INVQOUTPUT                        (0x1UL << 21)                                   /**< New BitField                                */
#define _FFT_CTRL_INVQOUTPUT_SHIFT                 21                                              /**< Shift value for FFT_INVQOUTPUT              */
#define _FFT_CTRL_INVQOUTPUT_MASK                  0x200000UL                                      /**< Bit mask for FFT_INVQOUTPUT                 */
#define _FFT_CTRL_INVQOUTPUT_DEFAULT               0x00000001UL                                    /**< Mode DEFAULT for FFT_CTRL                   */
#define _FFT_CTRL_INVQOUTPUT_NoInversion           0x00000000UL                                    /**< Mode NoInversion for FFT_CTRL               */
#define _FFT_CTRL_INVQOUTPUT_Inversion             0x00000001UL                                    /**< Mode Inversion for FFT_CTRL                 */
#define FFT_CTRL_INVQOUTPUT_DEFAULT                (_FFT_CTRL_INVQOUTPUT_DEFAULT << 21)            /**< Shifted mode DEFAULT for FFT_CTRL           */
#define FFT_CTRL_INVQOUTPUT_NoInversion            (_FFT_CTRL_INVQOUTPUT_NoInversion << 21)        /**< Shifted mode NoInversion for FFT_CTRL       */
#define FFT_CTRL_INVQOUTPUT_Inversion              (_FFT_CTRL_INVQOUTPUT_Inversion << 21)          /**< Shifted mode Inversion for FFT_CTRL         */
#define FFT_CTRL_OUTFORMAT                         (0x1UL << 22)                                   /**< New BitField                                */
#define _FFT_CTRL_OUTFORMAT_SHIFT                  22                                              /**< Shift value for FFT_OUTFORMAT               */
#define _FFT_CTRL_OUTFORMAT_MASK                   0x400000UL                                      /**< Bit mask for FFT_OUTFORMAT                  */
#define _FFT_CTRL_OUTFORMAT_DEFAULT                0x00000000UL                                    /**< Mode DEFAULT for FFT_CTRL                   */
#define _FFT_CTRL_OUTFORMAT_IQ                     0x00000000UL                                    /**< Mode IQ for FFT_CTRL                        */
#define _FFT_CTRL_OUTFORMAT_SQMODULEIQ             0x00000001UL                                    /**< Mode SQMODULEIQ for FFT_CTRL                */
#define FFT_CTRL_OUTFORMAT_DEFAULT                 (_FFT_CTRL_OUTFORMAT_DEFAULT << 22)             /**< Shifted mode DEFAULT for FFT_CTRL           */
#define FFT_CTRL_OUTFORMAT_IQ                      (_FFT_CTRL_OUTFORMAT_IQ << 22)                  /**< Shifted mode IQ for FFT_CTRL                */
#define FFT_CTRL_OUTFORMAT_SQMODULEIQ              (_FFT_CTRL_OUTFORMAT_SQMODULEIQ << 22)          /**< Shifted mode SQMODULEIQ for FFT_CTRL        */
#define _FFT_CTRL_SHIFTOUT_SHIFT                   23                                              /**< Shift value for FFT_SHIFTOUT                */
#define _FFT_CTRL_SHIFTOUT_MASK                    0x7F800000UL                                    /**< Bit mask for FFT_SHIFTOUT                   */
#define _FFT_CTRL_SHIFTOUT_DEFAULT                 0x00000000UL                                    /**< Mode DEFAULT for FFT_CTRL                   */
#define FFT_CTRL_SHIFTOUT_DEFAULT                  (_FFT_CTRL_SHIFTOUT_DEFAULT << 23)              /**< Shifted mode DEFAULT for FFT_CTRL           */
#define FFT_CTRL_DEBUG                             (0x1UL << 31)                                   /**< New BitField                                */
#define _FFT_CTRL_DEBUG_SHIFT                      31                                              /**< Shift value for FFT_DEBUG                   */
#define _FFT_CTRL_DEBUG_MASK                       0x80000000UL                                    /**< Bit mask for FFT_DEBUG                      */
#define _FFT_CTRL_DEBUG_DEFAULT                    0x00000000UL                                    /**< Mode DEFAULT for FFT_CTRL                   */
#define _FFT_CTRL_DEBUG_NO                         0x00000000UL                                    /**< Mode NO for FFT_CTRL                        */
#define _FFT_CTRL_DEBUG_YES                        0x00000001UL                                    /**< Mode YES for FFT_CTRL                       */
#define FFT_CTRL_DEBUG_DEFAULT                     (_FFT_CTRL_DEBUG_DEFAULT << 31)                 /**< Shifted mode DEFAULT for FFT_CTRL           */
#define FFT_CTRL_DEBUG_NO                          (_FFT_CTRL_DEBUG_NO << 31)                      /**< Shifted mode NO for FFT_CTRL                */
#define FFT_CTRL_DEBUG_YES                         (_FFT_CTRL_DEBUG_YES << 31)                     /**< Shifted mode YES for FFT_CTRL               */

/* Bit fields for FFT CTRL2 */
#define _FFT_CTRL2_RESETVALUE                      0x00000000UL                            /**< Default value for FFT_CTRL2                 */
#define _FFT_CTRL2_MASK                            0x00003003UL                            /**< Mask for FFT_CTRL2                          */
#define _FFT_CTRL2_STATUS_SHIFT                    0                                       /**< Shift value for FFT_STATUS                  */
#define _FFT_CTRL2_STATUS_MASK                     0x3UL                                   /**< Bit mask for FFT_STATUS                     */
#define _FFT_CTRL2_STATUS_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for FFT_CTRL2                  */
#define _FFT_CTRL2_STATUS_SLEEP                    0x00000000UL                            /**< Mode SLEEP for FFT_CTRL2                    */
#define _FFT_CTRL2_STATUS_COMPUTING                0x00000001UL                            /**< Mode COMPUTING for FFT_CTRL2                */
#define _FFT_CTRL2_STATUS_UNUSED                   0x00000002UL                            /**< Mode UNUSED for FFT_CTRL2                   */
#define _FFT_CTRL2_STATUS_READING                  0x00000003UL                            /**< Mode READING for FFT_CTRL2                  */
#define FFT_CTRL2_STATUS_DEFAULT                   (_FFT_CTRL2_STATUS_DEFAULT << 0)        /**< Shifted mode DEFAULT for FFT_CTRL2          */
#define FFT_CTRL2_STATUS_SLEEP                     (_FFT_CTRL2_STATUS_SLEEP << 0)          /**< Shifted mode SLEEP for FFT_CTRL2            */
#define FFT_CTRL2_STATUS_COMPUTING                 (_FFT_CTRL2_STATUS_COMPUTING << 0)      /**< Shifted mode COMPUTING for FFT_CTRL2        */
#define FFT_CTRL2_STATUS_UNUSED                    (_FFT_CTRL2_STATUS_UNUSED << 0)         /**< Shifted mode UNUSED for FFT_CTRL2           */
#define FFT_CTRL2_STATUS_READING                   (_FFT_CTRL2_STATUS_READING << 0)        /**< Shifted mode READING for FFT_CTRL2          */
#define _FFT_CTRL2_UPSAMP_SHIFT                    12                                      /**< Shift value for FFT_UPSAMP                  */
#define _FFT_CTRL2_UPSAMP_MASK                     0x3000UL                                /**< Bit mask for FFT_UPSAMP                     */
#define _FFT_CTRL2_UPSAMP_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for FFT_CTRL2                  */
#define _FFT_CTRL2_UPSAMP_NoUpsampling             0x00000000UL                            /**< Mode NoUpsampling for FFT_CTRL2             */
#define _FFT_CTRL2_UPSAMP_Upsamplingby2            0x00000001UL                            /**< Mode Upsamplingby2 for FFT_CTRL2            */
#define _FFT_CTRL2_UPSAMP_Upsamplingby4            0x00000002UL                            /**< Mode Upsamplingby4 for FFT_CTRL2            */
#define _FFT_CTRL2_UPSAMP_Upsamplingby8            0x00000003UL                            /**< Mode Upsamplingby8 for FFT_CTRL2            */
#define FFT_CTRL2_UPSAMP_DEFAULT                   (_FFT_CTRL2_UPSAMP_DEFAULT << 12)       /**< Shifted mode DEFAULT for FFT_CTRL2          */
#define FFT_CTRL2_UPSAMP_NoUpsampling              (_FFT_CTRL2_UPSAMP_NoUpsampling << 12)  /**< Shifted mode NoUpsampling for FFT_CTRL2     */
#define FFT_CTRL2_UPSAMP_Upsamplingby2             (_FFT_CTRL2_UPSAMP_Upsamplingby2 << 12) /**< Shifted mode Upsamplingby2 for FFT_CTRL2    */
#define FFT_CTRL2_UPSAMP_Upsamplingby4             (_FFT_CTRL2_UPSAMP_Upsamplingby4 << 12) /**< Shifted mode Upsamplingby4 for FFT_CTRL2    */
#define FFT_CTRL2_UPSAMP_Upsamplingby8             (_FFT_CTRL2_UPSAMP_Upsamplingby8 << 12) /**< Shifted mode Upsamplingby8 for FFT_CTRL2    */

/* Bit fields for FFT IF */
#define _FFT_IF_RESETVALUE                         0x00000000UL                         /**< Default value for FFT_IF                    */
#define _FFT_IF_MASK                               0x00000001UL                         /**< Mask for FFT_IF                             */
#define FFT_IF_DONE                                (0x1UL << 0)                         /**< New BitField                                */
#define _FFT_IF_DONE_SHIFT                         0                                    /**< Shift value for FFT_DONE                    */
#define _FFT_IF_DONE_MASK                          0x1UL                                /**< Bit mask for FFT_DONE                       */
#define _FFT_IF_DONE_DEFAULT                       0x00000000UL                         /**< Mode DEFAULT for FFT_IF                     */
#define FFT_IF_DONE_DEFAULT                        (_FFT_IF_DONE_DEFAULT << 0)          /**< Shifted mode DEFAULT for FFT_IF             */

/* Bit fields for FFT IEN */
#define _FFT_IEN_RESETVALUE                        0x00000000UL                         /**< Default value for FFT_IEN                   */
#define _FFT_IEN_MASK                              0x00000001UL                         /**< Mask for FFT_IEN                            */
#define FFT_IEN_DONE                               (0x1UL << 0)                         /**< New BitField                                */
#define _FFT_IEN_DONE_SHIFT                        0                                    /**< Shift value for FFT_DONE                    */
#define _FFT_IEN_DONE_MASK                         0x1UL                                /**< Bit mask for FFT_DONE                       */
#define _FFT_IEN_DONE_DEFAULT                      0x00000000UL                         /**< Mode DEFAULT for FFT_IEN                    */
#define FFT_IEN_DONE_DEFAULT                       (_FFT_IEN_DONE_DEFAULT << 0)         /**< Shifted mode DEFAULT for FFT_IEN            */

/** @} End of group EFR32FG25_FFT_BitFields */
/** @} End of group EFR32FG25_FFT */
/** @} End of group Parts */

#endif /* EFR32FG25_FFT_H */
