/**************************************************************************//**
 * @file
 * @brief EFR32FG25 DEMAP register and bit field definitions
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
#ifndef EFR32FG25_DEMAP_H
#define EFR32FG25_DEMAP_H
#define DEMAP_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_DEMAP DEMAP
 * @{
 * @brief EFR32FG25 DEMAP Register Declaration.
 *****************************************************************************/

/** DEMAP FIFOIN Register Group Declaration. */
typedef struct {
  __IOM uint32_t FIFOIN;                             /**< New Register                                       */
} DEMAP_FIFOIN_TypeDef;

/** DEMAP FIFOOUT Register Group Declaration. */
typedef struct {
  __IM uint32_t FIFOOUT;                             /**< New Register                                       */
} DEMAP_FIFOOUT_TypeDef;

/** DEMAP DEMAPLLR Register Group Declaration. */
typedef struct {
  __IOM uint32_t CTRL;                               /**< New Register                                       */
} DEMAP_DEMAPLLR_TypeDef;

/** DEMAP DEMAPERR Register Group Declaration. */
typedef struct {
  __IOM uint32_t CTRL;                               /**< New Register                                       */
} DEMAP_DEMAPERR_TypeDef;

/** DEMAP Register Declaration. */
typedef struct {
  __IM uint32_t          IPVERSION;             /**< IP Version ID                                      */
  __IOM uint32_t         EN;                    /**< Module Enable                                      */
  __IOM uint32_t         SWRST;                 /**< Software Reset                                     */
  __IOM uint32_t         CONNECT;               /**< New Register                                       */
  __IOM uint32_t         DISCLK;                /**< Disable Clocks                                     */
  uint32_t               RESERVED0[3U];         /**< Reserved for future use                            */
  DEMAP_FIFOIN_TypeDef   FIFOIN[3U];            /**<                                                    */
  uint32_t               RESERVED1[5U];         /**< Reserved for future use                            */
  DEMAP_FIFOOUT_TypeDef  FIFOOUT[4U];           /**<                                                    */
  uint32_t               RESERVED2[20U];        /**< Reserved for future use                            */
  uint32_t               RESERVED3[2U];         /**< Reserved for future use                            */
  __IOM uint32_t         FMTINCSI;              /**< New Register                                       */
  uint32_t               RESERVED4[5U];         /**< Reserved for future use                            */
  uint32_t               RESERVED5[2U];         /**< Reserved for future use                            */
  __IOM uint32_t         FMTOUTLLR;             /**< New Register                                       */
  uint32_t               RESERVED6[1U];         /**< Reserved for future use                            */
  __IOM uint32_t         FMTOUTERR;             /**< New Register                                       */
  uint32_t               RESERVED7[83U];        /**< Reserved for future use                            */
  __IOM uint32_t         DEMAPCTRL;             /**< New Register                                       */
  __IOM uint32_t         DEMAPLLROUT;           /**< New Register                                       */
  __IOM uint32_t         DEMAPERROUT;           /**< New Register                                       */
  __IM uint32_t          DEMAPSTAT;             /**< New Register                                       */
  __IM uint32_t          DEMAPALARM;            /**< New Register                                       */
  uint32_t               RESERVED8[3U];         /**< Reserved for future use                            */
  DEMAP_DEMAPLLR_TypeDef DEMAPLLR[10U];         /**<                                                    */
  uint32_t               RESERVED9[6U];         /**< Reserved for future use                            */
  DEMAP_DEMAPERR_TypeDef DEMAPERR[2U];          /**<                                                    */
  uint32_t               RESERVED10[862U];      /**< Reserved for future use                            */
  __IM uint32_t          IPVERSION_SET;         /**< IP Version ID                                      */
  __IOM uint32_t         EN_SET;                /**< Module Enable                                      */
  __IOM uint32_t         SWRST_SET;             /**< Software Reset                                     */
  __IOM uint32_t         CONNECT_SET;           /**< New Register                                       */
  __IOM uint32_t         DISCLK_SET;            /**< Disable Clocks                                     */
  uint32_t               RESERVED11[3U];        /**< Reserved for future use                            */
  DEMAP_FIFOIN_TypeDef   FIFOIN_SET[3U];        /**<                                                    */
  uint32_t               RESERVED12[5U];        /**< Reserved for future use                            */
  DEMAP_FIFOOUT_TypeDef  FIFOOUT_SET[4U];       /**<                                                    */
  uint32_t               RESERVED13[20U];       /**< Reserved for future use                            */
  uint32_t               RESERVED14[2U];        /**< Reserved for future use                            */
  __IOM uint32_t         FMTINCSI_SET;          /**< New Register                                       */
  uint32_t               RESERVED15[5U];        /**< Reserved for future use                            */
  uint32_t               RESERVED16[2U];        /**< Reserved for future use                            */
  __IOM uint32_t         FMTOUTLLR_SET;         /**< New Register                                       */
  uint32_t               RESERVED17[1U];        /**< Reserved for future use                            */
  __IOM uint32_t         FMTOUTERR_SET;         /**< New Register                                       */
  uint32_t               RESERVED18[83U];       /**< Reserved for future use                            */
  __IOM uint32_t         DEMAPCTRL_SET;         /**< New Register                                       */
  __IOM uint32_t         DEMAPLLROUT_SET;       /**< New Register                                       */
  __IOM uint32_t         DEMAPERROUT_SET;       /**< New Register                                       */
  __IM uint32_t          DEMAPSTAT_SET;         /**< New Register                                       */
  __IM uint32_t          DEMAPALARM_SET;        /**< New Register                                       */
  uint32_t               RESERVED19[3U];        /**< Reserved for future use                            */
  DEMAP_DEMAPLLR_TypeDef DEMAPLLR_SET[10U];     /**<                                                    */
  uint32_t               RESERVED20[6U];        /**< Reserved for future use                            */
  DEMAP_DEMAPERR_TypeDef DEMAPERR_SET[2U];      /**<                                                    */
  uint32_t               RESERVED21[862U];      /**< Reserved for future use                            */
  __IM uint32_t          IPVERSION_CLR;         /**< IP Version ID                                      */
  __IOM uint32_t         EN_CLR;                /**< Module Enable                                      */
  __IOM uint32_t         SWRST_CLR;             /**< Software Reset                                     */
  __IOM uint32_t         CONNECT_CLR;           /**< New Register                                       */
  __IOM uint32_t         DISCLK_CLR;            /**< Disable Clocks                                     */
  uint32_t               RESERVED22[3U];        /**< Reserved for future use                            */
  DEMAP_FIFOIN_TypeDef   FIFOIN_CLR[3U];        /**<                                                    */
  uint32_t               RESERVED23[5U];        /**< Reserved for future use                            */
  DEMAP_FIFOOUT_TypeDef  FIFOOUT_CLR[4U];       /**<                                                    */
  uint32_t               RESERVED24[20U];       /**< Reserved for future use                            */
  uint32_t               RESERVED25[2U];        /**< Reserved for future use                            */
  __IOM uint32_t         FMTINCSI_CLR;          /**< New Register                                       */
  uint32_t               RESERVED26[5U];        /**< Reserved for future use                            */
  uint32_t               RESERVED27[2U];        /**< Reserved for future use                            */
  __IOM uint32_t         FMTOUTLLR_CLR;         /**< New Register                                       */
  uint32_t               RESERVED28[1U];        /**< Reserved for future use                            */
  __IOM uint32_t         FMTOUTERR_CLR;         /**< New Register                                       */
  uint32_t               RESERVED29[83U];       /**< Reserved for future use                            */
  __IOM uint32_t         DEMAPCTRL_CLR;         /**< New Register                                       */
  __IOM uint32_t         DEMAPLLROUT_CLR;       /**< New Register                                       */
  __IOM uint32_t         DEMAPERROUT_CLR;       /**< New Register                                       */
  __IM uint32_t          DEMAPSTAT_CLR;         /**< New Register                                       */
  __IM uint32_t          DEMAPALARM_CLR;        /**< New Register                                       */
  uint32_t               RESERVED30[3U];        /**< Reserved for future use                            */
  DEMAP_DEMAPLLR_TypeDef DEMAPLLR_CLR[10U];     /**<                                                    */
  uint32_t               RESERVED31[6U];        /**< Reserved for future use                            */
  DEMAP_DEMAPERR_TypeDef DEMAPERR_CLR[2U];      /**<                                                    */
  uint32_t               RESERVED32[862U];      /**< Reserved for future use                            */
  __IM uint32_t          IPVERSION_TGL;         /**< IP Version ID                                      */
  __IOM uint32_t         EN_TGL;                /**< Module Enable                                      */
  __IOM uint32_t         SWRST_TGL;             /**< Software Reset                                     */
  __IOM uint32_t         CONNECT_TGL;           /**< New Register                                       */
  __IOM uint32_t         DISCLK_TGL;            /**< Disable Clocks                                     */
  uint32_t               RESERVED33[3U];        /**< Reserved for future use                            */
  DEMAP_FIFOIN_TypeDef   FIFOIN_TGL[3U];        /**<                                                    */
  uint32_t               RESERVED34[5U];        /**< Reserved for future use                            */
  DEMAP_FIFOOUT_TypeDef  FIFOOUT_TGL[4U];       /**<                                                    */
  uint32_t               RESERVED35[20U];       /**< Reserved for future use                            */
  uint32_t               RESERVED36[2U];        /**< Reserved for future use                            */
  __IOM uint32_t         FMTINCSI_TGL;          /**< New Register                                       */
  uint32_t               RESERVED37[5U];        /**< Reserved for future use                            */
  uint32_t               RESERVED38[2U];        /**< Reserved for future use                            */
  __IOM uint32_t         FMTOUTLLR_TGL;         /**< New Register                                       */
  uint32_t               RESERVED39[1U];        /**< Reserved for future use                            */
  __IOM uint32_t         FMTOUTERR_TGL;         /**< New Register                                       */
  uint32_t               RESERVED40[83U];       /**< Reserved for future use                            */
  __IOM uint32_t         DEMAPCTRL_TGL;         /**< New Register                                       */
  __IOM uint32_t         DEMAPLLROUT_TGL;       /**< New Register                                       */
  __IOM uint32_t         DEMAPERROUT_TGL;       /**< New Register                                       */
  __IM uint32_t          DEMAPSTAT_TGL;         /**< New Register                                       */
  __IM uint32_t          DEMAPALARM_TGL;        /**< New Register                                       */
  uint32_t               RESERVED41[3U];        /**< Reserved for future use                            */
  DEMAP_DEMAPLLR_TypeDef DEMAPLLR_TGL[10U];     /**<                                                    */
  uint32_t               RESERVED42[6U];        /**< Reserved for future use                            */
  DEMAP_DEMAPERR_TypeDef DEMAPERR_TGL[2U];      /**<                                                    */
} DEMAP_TypeDef;
/** @} End of group EFR32FG25_DEMAP */

/**************************************************************************//**
 * @addtogroup EFR32FG25_DEMAP
 * @{
 * @defgroup EFR32FG25_DEMAP_BitFields DEMAP Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for DEMAP IPVERSION */
#define _DEMAP_IPVERSION_RESETVALUE                0x00000001UL                              /**< Default value for DEMAP_IPVERSION           */
#define _DEMAP_IPVERSION_MASK                      0xFFFFFFFFUL                              /**< Mask for DEMAP_IPVERSION                    */
#define _DEMAP_IPVERSION_IPVERSION_SHIFT           0                                         /**< Shift value for DEMAP_IPVERSION             */
#define _DEMAP_IPVERSION_IPVERSION_MASK            0xFFFFFFFFUL                              /**< Bit mask for DEMAP_IPVERSION                */
#define _DEMAP_IPVERSION_IPVERSION_DEFAULT         0x00000001UL                              /**< Mode DEFAULT for DEMAP_IPVERSION            */
#define DEMAP_IPVERSION_IPVERSION_DEFAULT          (_DEMAP_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for DEMAP_IPVERSION    */

/* Bit fields for DEMAP EN */
#define _DEMAP_EN_RESETVALUE                       0x00000000UL                         /**< Default value for DEMAP_EN                  */
#define _DEMAP_EN_MASK                             0x00000003UL                         /**< Mask for DEMAP_EN                           */
#define DEMAP_EN_EN                                (0x1UL << 0)                         /**< Module Enable                               */
#define _DEMAP_EN_EN_SHIFT                         0                                    /**< Shift value for DEMAP_EN                    */
#define _DEMAP_EN_EN_MASK                          0x1UL                                /**< Bit mask for DEMAP_EN                       */
#define _DEMAP_EN_EN_DEFAULT                       0x00000000UL                         /**< Mode DEFAULT for DEMAP_EN                   */
#define DEMAP_EN_EN_DEFAULT                        (_DEMAP_EN_EN_DEFAULT << 0)          /**< Shifted mode DEFAULT for DEMAP_EN           */
#define DEMAP_EN_DISABLING                         (0x1UL << 1)                         /**< Disablement Busy Status                     */
#define _DEMAP_EN_DISABLING_SHIFT                  1                                    /**< Shift value for DEMAP_DISABLING             */
#define _DEMAP_EN_DISABLING_MASK                   0x2UL                                /**< Bit mask for DEMAP_DISABLING                */
#define _DEMAP_EN_DISABLING_DEFAULT                0x00000000UL                         /**< Mode DEFAULT for DEMAP_EN                   */
#define DEMAP_EN_DISABLING_DEFAULT                 (_DEMAP_EN_DISABLING_DEFAULT << 1)   /**< Shifted mode DEFAULT for DEMAP_EN           */

/* Bit fields for DEMAP SWRST */
#define _DEMAP_SWRST_RESETVALUE                    0x00000000UL                          /**< Default value for DEMAP_SWRST               */
#define _DEMAP_SWRST_MASK                          0x00000003UL                          /**< Mask for DEMAP_SWRST                        */
#define DEMAP_SWRST_SWRST                          (0x1UL << 0)                          /**< Software Reset Command                      */
#define _DEMAP_SWRST_SWRST_SHIFT                   0                                     /**< Shift value for DEMAP_SWRST                 */
#define _DEMAP_SWRST_SWRST_MASK                    0x1UL                                 /**< Bit mask for DEMAP_SWRST                    */
#define _DEMAP_SWRST_SWRST_DEFAULT                 0x00000000UL                          /**< Mode DEFAULT for DEMAP_SWRST                */
#define DEMAP_SWRST_SWRST_DEFAULT                  (_DEMAP_SWRST_SWRST_DEFAULT << 0)     /**< Shifted mode DEFAULT for DEMAP_SWRST        */
#define DEMAP_SWRST_RESETTING                      (0x1UL << 1)                          /**< Software Reset Busy Status                  */
#define _DEMAP_SWRST_RESETTING_SHIFT               1                                     /**< Shift value for DEMAP_RESETTING             */
#define _DEMAP_SWRST_RESETTING_MASK                0x2UL                                 /**< Bit mask for DEMAP_RESETTING                */
#define _DEMAP_SWRST_RESETTING_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for DEMAP_SWRST                */
#define DEMAP_SWRST_RESETTING_DEFAULT              (_DEMAP_SWRST_RESETTING_DEFAULT << 1) /**< Shifted mode DEFAULT for DEMAP_SWRST        */

/* Bit fields for DEMAP CONNECT */
#define _DEMAP_CONNECT_RESETVALUE                  0x00000000UL                         /**< Default value for DEMAP_CONNECT             */
#define _DEMAP_CONNECT_MASK                        0x00000F07UL                         /**< Mask for DEMAP_CONNECT                      */
#define _DEMAP_CONNECT_IN_SHIFT                    0                                    /**< Shift value for DEMAP_IN                    */
#define _DEMAP_CONNECT_IN_MASK                     0x7UL                                /**< Bit mask for DEMAP_IN                       */
#define _DEMAP_CONNECT_IN_DEFAULT                  0x00000000UL                         /**< Mode DEFAULT for DEMAP_CONNECT              */
#define DEMAP_CONNECT_IN_DEFAULT                   (_DEMAP_CONNECT_IN_DEFAULT << 0)     /**< Shifted mode DEFAULT for DEMAP_CONNECT      */
#define _DEMAP_CONNECT_OUT_SHIFT                   8                                    /**< Shift value for DEMAP_OUT                   */
#define _DEMAP_CONNECT_OUT_MASK                    0xF00UL                              /**< Bit mask for DEMAP_OUT                      */
#define _DEMAP_CONNECT_OUT_DEFAULT                 0x00000000UL                         /**< Mode DEFAULT for DEMAP_CONNECT              */
#define DEMAP_CONNECT_OUT_DEFAULT                  (_DEMAP_CONNECT_OUT_DEFAULT << 8)    /**< Shifted mode DEFAULT for DEMAP_CONNECT      */

/* Bit fields for DEMAP DISCLK */
#define _DEMAP_DISCLK_RESETVALUE                   0x00000002UL                         /**< Default value for DEMAP_DISCLK              */
#define _DEMAP_DISCLK_MASK                         0x00000003UL                         /**< Mask for DEMAP_DISCLK                       */
#define _DEMAP_DISCLK_DISCLK_SHIFT                 0                                    /**< Shift value for DEMAP_DISCLK                */
#define _DEMAP_DISCLK_DISCLK_MASK                  0x3UL                                /**< Bit mask for DEMAP_DISCLK                   */
#define _DEMAP_DISCLK_DISCLK_DEFAULT               0x00000002UL                         /**< Mode DEFAULT for DEMAP_DISCLK               */
#define _DEMAP_DISCLK_DISCLK_NONE                  0x00000000UL                         /**< Mode NONE for DEMAP_DISCLK                  */
#define _DEMAP_DISCLK_DISCLK_ALL                   0x00000001UL                         /**< Mode ALL for DEMAP_DISCLK                   */
#define _DEMAP_DISCLK_DISCLK_AUTO                  0x00000002UL                         /**< Mode AUTO for DEMAP_DISCLK                  */
#define DEMAP_DISCLK_DISCLK_DEFAULT                (_DEMAP_DISCLK_DISCLK_DEFAULT << 0)  /**< Shifted mode DEFAULT for DEMAP_DISCLK       */
#define DEMAP_DISCLK_DISCLK_NONE                   (_DEMAP_DISCLK_DISCLK_NONE << 0)     /**< Shifted mode NONE for DEMAP_DISCLK          */
#define DEMAP_DISCLK_DISCLK_ALL                    (_DEMAP_DISCLK_DISCLK_ALL << 0)      /**< Shifted mode ALL for DEMAP_DISCLK           */
#define DEMAP_DISCLK_DISCLK_AUTO                   (_DEMAP_DISCLK_DISCLK_AUTO << 0)     /**< Shifted mode AUTO for DEMAP_DISCLK          */

/* Bit fields for DEMAP FIFOIN */
#define _DEMAP_FIFOIN_RESETVALUE                   0x00000000UL                         /**< Default value for DEMAP_FIFOIN              */
#define _DEMAP_FIFOIN_MASK                         0x1FFF3F0FUL                         /**< Mask for DEMAP_FIFOIN                       */
#define _DEMAP_FIFOIN_FID_SHIFT                    0                                    /**< Shift value for DEMAP_FID                   */
#define _DEMAP_FIFOIN_FID_MASK                     0xFUL                                /**< Bit mask for DEMAP_FID                      */
#define _DEMAP_FIFOIN_FID_DEFAULT                  0x00000000UL                         /**< Mode DEFAULT for DEMAP_FIFOIN               */
#define DEMAP_FIFOIN_FID_DEFAULT                   (_DEMAP_FIFOIN_FID_DEFAULT << 0)     /**< Shifted mode DEFAULT for DEMAP_FIFOIN       */
#define _DEMAP_FIFOIN_CID_SHIFT                    8                                    /**< Shift value for DEMAP_CID                   */
#define _DEMAP_FIFOIN_CID_MASK                     0x3F00UL                             /**< Bit mask for DEMAP_CID                      */
#define _DEMAP_FIFOIN_CID_DEFAULT                  0x00000000UL                         /**< Mode DEFAULT for DEMAP_FIFOIN               */
#define DEMAP_FIFOIN_CID_DEFAULT                   (_DEMAP_FIFOIN_CID_DEFAULT << 8)     /**< Shifted mode DEFAULT for DEMAP_FIFOIN       */
#define _DEMAP_FIFOIN_REM_SHIFT                    16                                   /**< Shift value for DEMAP_REM                   */
#define _DEMAP_FIFOIN_REM_MASK                     0xFF0000UL                           /**< Bit mask for DEMAP_REM                      */
#define _DEMAP_FIFOIN_REM_DEFAULT                  0x00000000UL                         /**< Mode DEFAULT for DEMAP_FIFOIN               */
#define DEMAP_FIFOIN_REM_DEFAULT                   (_DEMAP_FIFOIN_REM_DEFAULT << 16)    /**< Shifted mode DEFAULT for DEMAP_FIFOIN       */
#define _DEMAP_FIFOIN_ALARM_SHIFT                  24                                   /**< Shift value for DEMAP_ALARM                 */
#define _DEMAP_FIFOIN_ALARM_MASK                   0x1F000000UL                         /**< Bit mask for DEMAP_ALARM                    */
#define _DEMAP_FIFOIN_ALARM_DEFAULT                0x00000000UL                         /**< Mode DEFAULT for DEMAP_FIFOIN               */
#define DEMAP_FIFOIN_ALARM_DEFAULT                 (_DEMAP_FIFOIN_ALARM_DEFAULT << 24)  /**< Shifted mode DEFAULT for DEMAP_FIFOIN       */

/* Bit fields for DEMAP FIFOOUT */
#define _DEMAP_FIFOOUT_RESETVALUE                  0x00000000UL                         /**< Default value for DEMAP_FIFOOUT             */
#define _DEMAP_FIFOOUT_MASK                        0x1FFF0000UL                         /**< Mask for DEMAP_FIFOOUT                      */
#define _DEMAP_FIFOOUT_CNT_SHIFT                   16                                   /**< Shift value for DEMAP_CNT                   */
#define _DEMAP_FIFOOUT_CNT_MASK                    0xFF0000UL                           /**< Bit mask for DEMAP_CNT                      */
#define _DEMAP_FIFOOUT_CNT_DEFAULT                 0x00000000UL                         /**< Mode DEFAULT for DEMAP_FIFOOUT              */
#define DEMAP_FIFOOUT_CNT_DEFAULT                  (_DEMAP_FIFOOUT_CNT_DEFAULT << 16)   /**< Shifted mode DEFAULT for DEMAP_FIFOOUT      */
#define _DEMAP_FIFOOUT_ALARM_SHIFT                 24                                   /**< Shift value for DEMAP_ALARM                 */
#define _DEMAP_FIFOOUT_ALARM_MASK                  0x1F000000UL                         /**< Bit mask for DEMAP_ALARM                    */
#define _DEMAP_FIFOOUT_ALARM_DEFAULT               0x00000000UL                         /**< Mode DEFAULT for DEMAP_FIFOOUT              */
#define DEMAP_FIFOOUT_ALARM_DEFAULT                (_DEMAP_FIFOOUT_ALARM_DEFAULT << 24) /**< Shifted mode DEFAULT for DEMAP_FIFOOUT      */

/* Bit fields for DEMAP FMTINCSI */
#define _DEMAP_FMTINCSI_RESETVALUE                 0x00000000UL                               /**< Default value for DEMAP_FMTINCSI            */
#define _DEMAP_FMTINCSI_MASK                       0x00030000UL                               /**< Mask for DEMAP_FMTINCSI                     */
#define _DEMAP_FMTINCSI_ELEMALIGN_SHIFT            16                                         /**< Shift value for DEMAP_ELEMALIGN             */
#define _DEMAP_FMTINCSI_ELEMALIGN_MASK             0x30000UL                                  /**< Bit mask for DEMAP_ELEMALIGN                */
#define _DEMAP_FMTINCSI_ELEMALIGN_DEFAULT          0x00000000UL                               /**< Mode DEFAULT for DEMAP_FMTINCSI             */
#define _DEMAP_FMTINCSI_ELEMALIGN_WORD             0x00000000UL                               /**< Mode WORD for DEMAP_FMTINCSI                */
#define _DEMAP_FMTINCSI_ELEMALIGN_HALFWORD         0x00000001UL                               /**< Mode HALFWORD for DEMAP_FMTINCSI            */
#define _DEMAP_FMTINCSI_ELEMALIGN_BYTE             0x00000002UL                               /**< Mode BYTE for DEMAP_FMTINCSI                */
#define DEMAP_FMTINCSI_ELEMALIGN_DEFAULT           (_DEMAP_FMTINCSI_ELEMALIGN_DEFAULT << 16)  /**< Shifted mode DEFAULT for DEMAP_FMTINCSI     */
#define DEMAP_FMTINCSI_ELEMALIGN_WORD              (_DEMAP_FMTINCSI_ELEMALIGN_WORD << 16)     /**< Shifted mode WORD for DEMAP_FMTINCSI        */
#define DEMAP_FMTINCSI_ELEMALIGN_HALFWORD          (_DEMAP_FMTINCSI_ELEMALIGN_HALFWORD << 16) /**< Shifted mode HALFWORD for DEMAP_FMTINCSI    */
#define DEMAP_FMTINCSI_ELEMALIGN_BYTE              (_DEMAP_FMTINCSI_ELEMALIGN_BYTE << 16)     /**< Shifted mode BYTE for DEMAP_FMTINCSI        */

/* Bit fields for DEMAP FMTOUTLLR */
#define _DEMAP_FMTOUTLLR_RESETVALUE                0x00000000UL                                /**< Default value for DEMAP_FMTOUTLLR           */
#define _DEMAP_FMTOUTLLR_MASK                      0x00030307UL                                /**< Mask for DEMAP_FMTOUTLLR                    */
#define _DEMAP_FMTOUTLLR_ELEMSIZE_SHIFT            0                                           /**< Shift value for DEMAP_ELEMSIZE              */
#define _DEMAP_FMTOUTLLR_ELEMSIZE_MASK             0x7UL                                       /**< Bit mask for DEMAP_ELEMSIZE                 */
#define _DEMAP_FMTOUTLLR_ELEMSIZE_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for DEMAP_FMTOUTLLR            */
#define DEMAP_FMTOUTLLR_ELEMSIZE_DEFAULT           (_DEMAP_FMTOUTLLR_ELEMSIZE_DEFAULT << 0)    /**< Shifted mode DEFAULT for DEMAP_FMTOUTLLR    */
#define _DEMAP_FMTOUTLLR_ELEMNB_SHIFT              8                                           /**< Shift value for DEMAP_ELEMNB                */
#define _DEMAP_FMTOUTLLR_ELEMNB_MASK               0x300UL                                     /**< Bit mask for DEMAP_ELEMNB                   */
#define _DEMAP_FMTOUTLLR_ELEMNB_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for DEMAP_FMTOUTLLR            */
#define _DEMAP_FMTOUTLLR_ELEMNB_ONE                0x00000000UL                                /**< Mode ONE for DEMAP_FMTOUTLLR                */
#define _DEMAP_FMTOUTLLR_ELEMNB_TWO                0x00000001UL                                /**< Mode TWO for DEMAP_FMTOUTLLR                */
#define _DEMAP_FMTOUTLLR_ELEMNB_FOUR               0x00000002UL                                /**< Mode FOUR for DEMAP_FMTOUTLLR               */
#define DEMAP_FMTOUTLLR_ELEMNB_DEFAULT             (_DEMAP_FMTOUTLLR_ELEMNB_DEFAULT << 8)      /**< Shifted mode DEFAULT for DEMAP_FMTOUTLLR    */
#define DEMAP_FMTOUTLLR_ELEMNB_ONE                 (_DEMAP_FMTOUTLLR_ELEMNB_ONE << 8)          /**< Shifted mode ONE for DEMAP_FMTOUTLLR        */
#define DEMAP_FMTOUTLLR_ELEMNB_TWO                 (_DEMAP_FMTOUTLLR_ELEMNB_TWO << 8)          /**< Shifted mode TWO for DEMAP_FMTOUTLLR        */
#define DEMAP_FMTOUTLLR_ELEMNB_FOUR                (_DEMAP_FMTOUTLLR_ELEMNB_FOUR << 8)         /**< Shifted mode FOUR for DEMAP_FMTOUTLLR       */
#define _DEMAP_FMTOUTLLR_ELEMALIGN_SHIFT           16                                          /**< Shift value for DEMAP_ELEMALIGN             */
#define _DEMAP_FMTOUTLLR_ELEMALIGN_MASK            0x30000UL                                   /**< Bit mask for DEMAP_ELEMALIGN                */
#define _DEMAP_FMTOUTLLR_ELEMALIGN_DEFAULT         0x00000000UL                                /**< Mode DEFAULT for DEMAP_FMTOUTLLR            */
#define _DEMAP_FMTOUTLLR_ELEMALIGN_WORD            0x00000000UL                                /**< Mode WORD for DEMAP_FMTOUTLLR               */
#define _DEMAP_FMTOUTLLR_ELEMALIGN_HALFWORD        0x00000001UL                                /**< Mode HALFWORD for DEMAP_FMTOUTLLR           */
#define _DEMAP_FMTOUTLLR_ELEMALIGN_BYTE            0x00000002UL                                /**< Mode BYTE for DEMAP_FMTOUTLLR               */
#define DEMAP_FMTOUTLLR_ELEMALIGN_DEFAULT          (_DEMAP_FMTOUTLLR_ELEMALIGN_DEFAULT << 16)  /**< Shifted mode DEFAULT for DEMAP_FMTOUTLLR    */
#define DEMAP_FMTOUTLLR_ELEMALIGN_WORD             (_DEMAP_FMTOUTLLR_ELEMALIGN_WORD << 16)     /**< Shifted mode WORD for DEMAP_FMTOUTLLR       */
#define DEMAP_FMTOUTLLR_ELEMALIGN_HALFWORD         (_DEMAP_FMTOUTLLR_ELEMALIGN_HALFWORD << 16) /**< Shifted mode HALFWORD for DEMAP_FMTOUTLLR   */
#define DEMAP_FMTOUTLLR_ELEMALIGN_BYTE             (_DEMAP_FMTOUTLLR_ELEMALIGN_BYTE << 16)     /**< Shifted mode BYTE for DEMAP_FMTOUTLLR       */

/* Bit fields for DEMAP FMTOUTERR */
#define _DEMAP_FMTOUTERR_RESETVALUE                0x00000000UL                                /**< Default value for DEMAP_FMTOUTERR           */
#define _DEMAP_FMTOUTERR_MASK                      0x0003000FUL                                /**< Mask for DEMAP_FMTOUTERR                    */
#define _DEMAP_FMTOUTERR_ELEMSIZE_SHIFT            0                                           /**< Shift value for DEMAP_ELEMSIZE              */
#define _DEMAP_FMTOUTERR_ELEMSIZE_MASK             0xFUL                                       /**< Bit mask for DEMAP_ELEMSIZE                 */
#define _DEMAP_FMTOUTERR_ELEMSIZE_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for DEMAP_FMTOUTERR            */
#define DEMAP_FMTOUTERR_ELEMSIZE_DEFAULT           (_DEMAP_FMTOUTERR_ELEMSIZE_DEFAULT << 0)    /**< Shifted mode DEFAULT for DEMAP_FMTOUTERR    */
#define _DEMAP_FMTOUTERR_ELEMALIGN_SHIFT           16                                          /**< Shift value for DEMAP_ELEMALIGN             */
#define _DEMAP_FMTOUTERR_ELEMALIGN_MASK            0x30000UL                                   /**< Bit mask for DEMAP_ELEMALIGN                */
#define _DEMAP_FMTOUTERR_ELEMALIGN_DEFAULT         0x00000000UL                                /**< Mode DEFAULT for DEMAP_FMTOUTERR            */
#define _DEMAP_FMTOUTERR_ELEMALIGN_WORD            0x00000000UL                                /**< Mode WORD for DEMAP_FMTOUTERR               */
#define _DEMAP_FMTOUTERR_ELEMALIGN_HALFWORD        0x00000001UL                                /**< Mode HALFWORD for DEMAP_FMTOUTERR           */
#define _DEMAP_FMTOUTERR_ELEMALIGN_BYTE            0x00000002UL                                /**< Mode BYTE for DEMAP_FMTOUTERR               */
#define DEMAP_FMTOUTERR_ELEMALIGN_DEFAULT          (_DEMAP_FMTOUTERR_ELEMALIGN_DEFAULT << 16)  /**< Shifted mode DEFAULT for DEMAP_FMTOUTERR    */
#define DEMAP_FMTOUTERR_ELEMALIGN_WORD             (_DEMAP_FMTOUTERR_ELEMALIGN_WORD << 16)     /**< Shifted mode WORD for DEMAP_FMTOUTERR       */
#define DEMAP_FMTOUTERR_ELEMALIGN_HALFWORD         (_DEMAP_FMTOUTERR_ELEMALIGN_HALFWORD << 16) /**< Shifted mode HALFWORD for DEMAP_FMTOUTERR   */
#define DEMAP_FMTOUTERR_ELEMALIGN_BYTE             (_DEMAP_FMTOUTERR_ELEMALIGN_BYTE << 16)     /**< Shifted mode BYTE for DEMAP_FMTOUTERR       */

/* Bit fields for DEMAP DEMAPCTRL */
#define _DEMAP_DEMAPCTRL_RESETVALUE                0x00000005UL                                /**< Default value for DEMAP_DEMAPCTRL           */
#define _DEMAP_DEMAPCTRL_MASK                      0x001FFFFFUL                                /**< Mask for DEMAP_DEMAPCTRL                    */
#define DEMAP_DEMAPCTRL_LLROUTEN                   (0x1UL << 0)                                /**< New BitField                                */
#define _DEMAP_DEMAPCTRL_LLROUTEN_SHIFT            0                                           /**< Shift value for DEMAP_LLROUTEN              */
#define _DEMAP_DEMAPCTRL_LLROUTEN_MASK             0x1UL                                       /**< Bit mask for DEMAP_LLROUTEN                 */
#define _DEMAP_DEMAPCTRL_LLROUTEN_DEFAULT          0x00000001UL                                /**< Mode DEFAULT for DEMAP_DEMAPCTRL            */
#define DEMAP_DEMAPCTRL_LLROUTEN_DEFAULT           (_DEMAP_DEMAPCTRL_LLROUTEN_DEFAULT << 0)    /**< Shifted mode DEFAULT for DEMAP_DEMAPCTRL    */
#define DEMAP_DEMAPCTRL_ERROUTEN                   (0x1UL << 1)                                /**< New BitField                                */
#define _DEMAP_DEMAPCTRL_ERROUTEN_SHIFT            1                                           /**< Shift value for DEMAP_ERROUTEN              */
#define _DEMAP_DEMAPCTRL_ERROUTEN_MASK             0x2UL                                       /**< Bit mask for DEMAP_ERROUTEN                 */
#define _DEMAP_DEMAPCTRL_ERROUTEN_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for DEMAP_DEMAPCTRL            */
#define DEMAP_DEMAPCTRL_ERROUTEN_DEFAULT           (_DEMAP_DEMAPCTRL_ERROUTEN_DEFAULT << 1)    /**< Shifted mode DEFAULT for DEMAP_DEMAPCTRL    */
#define DEMAP_DEMAPCTRL_DECOUTEN                   (0x1UL << 2)                                /**< New BitField                                */
#define _DEMAP_DEMAPCTRL_DECOUTEN_SHIFT            2                                           /**< Shift value for DEMAP_DECOUTEN              */
#define _DEMAP_DEMAPCTRL_DECOUTEN_MASK             0x4UL                                       /**< Bit mask for DEMAP_DECOUTEN                 */
#define _DEMAP_DEMAPCTRL_DECOUTEN_DEFAULT          0x00000001UL                                /**< Mode DEFAULT for DEMAP_DEMAPCTRL            */
#define DEMAP_DEMAPCTRL_DECOUTEN_DEFAULT           (_DEMAP_DEMAPCTRL_DECOUTEN_DEFAULT << 2)    /**< Shifted mode DEFAULT for DEMAP_DEMAPCTRL    */
#define _DEMAP_DEMAPCTRL_DECOUTSHIFT_SHIFT         3                                           /**< Shift value for DEMAP_DECOUTSHIFT           */
#define _DEMAP_DEMAPCTRL_DECOUTSHIFT_MASK          0x18UL                                      /**< Bit mask for DEMAP_DECOUTSHIFT              */
#define _DEMAP_DEMAPCTRL_DECOUTSHIFT_DEFAULT       0x00000000UL                                /**< Mode DEFAULT for DEMAP_DEMAPCTRL            */
#define DEMAP_DEMAPCTRL_DECOUTSHIFT_DEFAULT        (_DEMAP_DEMAPCTRL_DECOUTSHIFT_DEFAULT << 3) /**< Shifted mode DEFAULT for DEMAP_DEMAPCTRL    */
#define DEMAP_DEMAPCTRL_DECOUTCROSS                (0x1UL << 5)                                /**< New BitField                                */
#define _DEMAP_DEMAPCTRL_DECOUTCROSS_SHIFT         5                                           /**< Shift value for DEMAP_DECOUTCROSS           */
#define _DEMAP_DEMAPCTRL_DECOUTCROSS_MASK          0x20UL                                      /**< Bit mask for DEMAP_DECOUTCROSS              */
#define _DEMAP_DEMAPCTRL_DECOUTCROSS_DEFAULT       0x00000000UL                                /**< Mode DEFAULT for DEMAP_DEMAPCTRL            */
#define DEMAP_DEMAPCTRL_DECOUTCROSS_DEFAULT        (_DEMAP_DEMAPCTRL_DECOUTCROSS_DEFAULT << 5) /**< Shifted mode DEFAULT for DEMAP_DEMAPCTRL    */
#define DEMAP_DEMAPCTRL_DECOUTMODE                 (0x1UL << 6)                                /**< New BitField                                */
#define _DEMAP_DEMAPCTRL_DECOUTMODE_SHIFT          6                                           /**< Shift value for DEMAP_DECOUTMODE            */
#define _DEMAP_DEMAPCTRL_DECOUTMODE_MASK           0x40UL                                      /**< Bit mask for DEMAP_DECOUTMODE               */
#define _DEMAP_DEMAPCTRL_DECOUTMODE_DEFAULT        0x00000000UL                                /**< Mode DEFAULT for DEMAP_DEMAPCTRL            */
#define DEMAP_DEMAPCTRL_DECOUTMODE_DEFAULT         (_DEMAP_DEMAPCTRL_DECOUTMODE_DEFAULT << 6)  /**< Shifted mode DEFAULT for DEMAP_DEMAPCTRL    */
#define _DEMAP_DEMAPCTRL_CSIEN_SHIFT               7                                           /**< Shift value for DEMAP_CSIEN                 */
#define _DEMAP_DEMAPCTRL_CSIEN_MASK                0x180UL                                     /**< Bit mask for DEMAP_CSIEN                    */
#define _DEMAP_DEMAPCTRL_CSIEN_DEFAULT             0x00000000UL                                /**< Mode DEFAULT for DEMAP_DEMAPCTRL            */
#define _DEMAP_DEMAPCTRL_CSIEN_no                  0x00000000UL                                /**< Mode no for DEMAP_DEMAPCTRL                 */
#define _DEMAP_DEMAPCTRL_CSIEN_llr_err             0x00000001UL                                /**< Mode llr_err for DEMAP_DEMAPCTRL            */
#define _DEMAP_DEMAPCTRL_CSIEN_llr                 0x00000002UL                                /**< Mode llr for DEMAP_DEMAPCTRL                */
#define _DEMAP_DEMAPCTRL_CSIEN_err                 0x00000003UL                                /**< Mode err for DEMAP_DEMAPCTRL                */
#define DEMAP_DEMAPCTRL_CSIEN_DEFAULT              (_DEMAP_DEMAPCTRL_CSIEN_DEFAULT << 7)       /**< Shifted mode DEFAULT for DEMAP_DEMAPCTRL    */
#define DEMAP_DEMAPCTRL_CSIEN_no                   (_DEMAP_DEMAPCTRL_CSIEN_no << 7)            /**< Shifted mode no for DEMAP_DEMAPCTRL         */
#define DEMAP_DEMAPCTRL_CSIEN_llr_err              (_DEMAP_DEMAPCTRL_CSIEN_llr_err << 7)       /**< Shifted mode llr_err for DEMAP_DEMAPCTRL    */
#define DEMAP_DEMAPCTRL_CSIEN_llr                  (_DEMAP_DEMAPCTRL_CSIEN_llr << 7)           /**< Shifted mode llr for DEMAP_DEMAPCTRL        */
#define DEMAP_DEMAPCTRL_CSIEN_err                  (_DEMAP_DEMAPCTRL_CSIEN_err << 7)           /**< Shifted mode err for DEMAP_DEMAPCTRL        */
#define DEMAP_DEMAPCTRL_CSIERRMODE                 (0x1UL << 9)                                /**< New BitField                                */
#define _DEMAP_DEMAPCTRL_CSIERRMODE_SHIFT          9                                           /**< Shift value for DEMAP_CSIERRMODE            */
#define _DEMAP_DEMAPCTRL_CSIERRMODE_MASK           0x200UL                                     /**< Bit mask for DEMAP_CSIERRMODE               */
#define _DEMAP_DEMAPCTRL_CSIERRMODE_DEFAULT        0x00000000UL                                /**< Mode DEFAULT for DEMAP_DEMAPCTRL            */
#define _DEMAP_DEMAPCTRL_CSIERRMODE_MULT           0x00000000UL                                /**< Mode MULT for DEMAP_DEMAPCTRL               */
#define _DEMAP_DEMAPCTRL_CSIERRMODE_THR            0x00000001UL                                /**< Mode THR for DEMAP_DEMAPCTRL                */
#define DEMAP_DEMAPCTRL_CSIERRMODE_DEFAULT         (_DEMAP_DEMAPCTRL_CSIERRMODE_DEFAULT << 9)  /**< Shifted mode DEFAULT for DEMAP_DEMAPCTRL    */
#define DEMAP_DEMAPCTRL_CSIERRMODE_MULT            (_DEMAP_DEMAPCTRL_CSIERRMODE_MULT << 9)     /**< Shifted mode MULT for DEMAP_DEMAPCTRL       */
#define DEMAP_DEMAPCTRL_CSIERRMODE_THR             (_DEMAP_DEMAPCTRL_CSIERRMODE_THR << 9)      /**< Shifted mode THR for DEMAP_DEMAPCTRL        */
#define _DEMAP_DEMAPCTRL_CSITHR_SHIFT              10                                          /**< Shift value for DEMAP_CSITHR                */
#define _DEMAP_DEMAPCTRL_CSITHR_MASK               0x1FFC00UL                                  /**< Bit mask for DEMAP_CSITHR                   */
#define _DEMAP_DEMAPCTRL_CSITHR_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for DEMAP_DEMAPCTRL            */
#define DEMAP_DEMAPCTRL_CSITHR_DEFAULT             (_DEMAP_DEMAPCTRL_CSITHR_DEFAULT << 10)     /**< Shifted mode DEFAULT for DEMAP_DEMAPCTRL    */

/* Bit fields for DEMAP DEMAPLLROUT */
#define _DEMAP_DEMAPLLROUT_RESETVALUE              0x00000310UL                              /**< Default value for DEMAP_DEMAPLLROUT         */
#define _DEMAP_DEMAPLLROUT_MASK                    0x0003C7FFUL                              /**< Mask for DEMAP_DEMAPLLROUT                  */
#define _DEMAP_DEMAPLLROUT_GAINNUM_SHIFT           0                                         /**< Shift value for DEMAP_GAINNUM               */
#define _DEMAP_DEMAPLLROUT_GAINNUM_MASK            0x3FUL                                    /**< Bit mask for DEMAP_GAINNUM                  */
#define _DEMAP_DEMAPLLROUT_GAINNUM_DEFAULT         0x00000010UL                              /**< Mode DEFAULT for DEMAP_DEMAPLLROUT          */
#define DEMAP_DEMAPLLROUT_GAINNUM_DEFAULT          (_DEMAP_DEMAPLLROUT_GAINNUM_DEFAULT << 0) /**< Shifted mode DEFAULT for DEMAP_DEMAPLLROUT  */
#define _DEMAP_DEMAPLLROUT_GAINDEN_SHIFT           6                                         /**< Shift value for DEMAP_GAINDEN               */
#define _DEMAP_DEMAPLLROUT_GAINDEN_MASK            0x7C0UL                                   /**< Bit mask for DEMAP_GAINDEN                  */
#define _DEMAP_DEMAPLLROUT_GAINDEN_DEFAULT         0x0000000CUL                              /**< Mode DEFAULT for DEMAP_DEMAPLLROUT          */
#define DEMAP_DEMAPLLROUT_GAINDEN_DEFAULT          (_DEMAP_DEMAPLLROUT_GAINDEN_DEFAULT << 6) /**< Shifted mode DEFAULT for DEMAP_DEMAPLLROUT  */
#define _DEMAP_DEMAPLLROUT_NB_SHIFT                14                                        /**< Shift value for DEMAP_NB                    */
#define _DEMAP_DEMAPLLROUT_NB_MASK                 0x3C000UL                                 /**< Bit mask for DEMAP_NB                       */
#define _DEMAP_DEMAPLLROUT_NB_DEFAULT              0x00000000UL                              /**< Mode DEFAULT for DEMAP_DEMAPLLROUT          */
#define DEMAP_DEMAPLLROUT_NB_DEFAULT               (_DEMAP_DEMAPLLROUT_NB_DEFAULT << 14)     /**< Shifted mode DEFAULT for DEMAP_DEMAPLLROUT  */

/* Bit fields for DEMAP DEMAPERROUT */
#define _DEMAP_DEMAPERROUT_RESETVALUE              0x00000000UL                           /**< Default value for DEMAP_DEMAPERROUT         */
#define _DEMAP_DEMAPERROUT_MASK                    0x0000007FUL                           /**< Mask for DEMAP_DEMAPERROUT                  */
#define _DEMAP_DEMAPERROUT_GAIN_SHIFT              0                                      /**< Shift value for DEMAP_GAIN                  */
#define _DEMAP_DEMAPERROUT_GAIN_MASK               0x1FUL                                 /**< Bit mask for DEMAP_GAIN                     */
#define _DEMAP_DEMAPERROUT_GAIN_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for DEMAP_DEMAPERROUT          */
#define DEMAP_DEMAPERROUT_GAIN_DEFAULT             (_DEMAP_DEMAPERROUT_GAIN_DEFAULT << 0) /**< Shifted mode DEFAULT for DEMAP_DEMAPERROUT  */
#define _DEMAP_DEMAPERROUT_NB_SHIFT                5                                      /**< Shift value for DEMAP_NB                    */
#define _DEMAP_DEMAPERROUT_NB_MASK                 0x60UL                                 /**< Bit mask for DEMAP_NB                       */
#define _DEMAP_DEMAPERROUT_NB_DEFAULT              0x00000000UL                           /**< Mode DEFAULT for DEMAP_DEMAPERROUT          */
#define DEMAP_DEMAPERROUT_NB_DEFAULT               (_DEMAP_DEMAPERROUT_NB_DEFAULT << 5)   /**< Shifted mode DEFAULT for DEMAP_DEMAPERROUT  */

/* Bit fields for DEMAP DEMAPSTAT */
#define _DEMAP_DEMAPSTAT_RESETVALUE                0x00000000UL                              /**< Default value for DEMAP_DEMAPSTAT           */
#define _DEMAP_DEMAPSTAT_MASK                      0x000001FFUL                              /**< Mask for DEMAP_DEMAPSTAT                    */
#define _DEMAP_DEMAPSTAT_CSILOWVAL_SHIFT           0                                         /**< Shift value for DEMAP_CSILOWVAL             */
#define _DEMAP_DEMAPSTAT_CSILOWVAL_MASK            0x1FFUL                                   /**< Bit mask for DEMAP_CSILOWVAL                */
#define _DEMAP_DEMAPSTAT_CSILOWVAL_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for DEMAP_DEMAPSTAT            */
#define DEMAP_DEMAPSTAT_CSILOWVAL_DEFAULT          (_DEMAP_DEMAPSTAT_CSILOWVAL_DEFAULT << 0) /**< Shifted mode DEFAULT for DEMAP_DEMAPSTAT    */

/* Bit fields for DEMAP DEMAPALARM */
#define _DEMAP_DEMAPALARM_RESETVALUE               0x00000000UL                               /**< Default value for DEMAP_DEMAPALARM          */
#define _DEMAP_DEMAPALARM_MASK                     0x0000001FUL                               /**< Mask for DEMAP_DEMAPALARM                   */
#define _DEMAP_DEMAPALARM_FIFOINOUT_SHIFT          0                                          /**< Shift value for DEMAP_FIFOINOUT             */
#define _DEMAP_DEMAPALARM_FIFOINOUT_MASK           0x1FUL                                     /**< Bit mask for DEMAP_FIFOINOUT                */
#define _DEMAP_DEMAPALARM_FIFOINOUT_DEFAULT        0x00000000UL                               /**< Mode DEFAULT for DEMAP_DEMAPALARM           */
#define DEMAP_DEMAPALARM_FIFOINOUT_DEFAULT         (_DEMAP_DEMAPALARM_FIFOINOUT_DEFAULT << 0) /**< Shifted mode DEFAULT for DEMAP_DEMAPALARM   */

/* Bit fields for DEMAP DEMAPLLR_CTRL */
#define _DEMAP_DEMAPLLR_CTRL_RESETVALUE            0x00000023UL                                    /**< Default value for DEMAP_DEMAPLLR_CTRL       */
#define _DEMAP_DEMAPLLR_CTRL_MASK                  0x01FFFFFFUL                                    /**< Mask for DEMAP_DEMAPLLR_CTRL                */
#define _DEMAP_DEMAPLLR_CTRL_IQNBIT_SHIFT          0                                               /**< Shift value for DEMAP_IQNBIT                */
#define _DEMAP_DEMAPLLR_CTRL_IQNBIT_MASK           0x7UL                                           /**< Bit mask for DEMAP_IQNBIT                   */
#define _DEMAP_DEMAPLLR_CTRL_IQNBIT_DEFAULT        0x00000003UL                                    /**< Mode DEFAULT for DEMAP_DEMAPLLR_CTRL        */
#define _DEMAP_DEMAPLLR_CTRL_IQNBIT_FIVE           0x00000000UL                                    /**< Mode FIVE for DEMAP_DEMAPLLR_CTRL           */
#define _DEMAP_DEMAPLLR_CTRL_IQNBIT_SIX            0x00000001UL                                    /**< Mode SIX for DEMAP_DEMAPLLR_CTRL            */
#define _DEMAP_DEMAPLLR_CTRL_IQNBIT_SEVEN          0x00000002UL                                    /**< Mode SEVEN for DEMAP_DEMAPLLR_CTRL          */
#define _DEMAP_DEMAPLLR_CTRL_IQNBIT_EIGHT          0x00000003UL                                    /**< Mode EIGHT for DEMAP_DEMAPLLR_CTRL          */
#define _DEMAP_DEMAPLLR_CTRL_IQNBIT_NINE           0x00000004UL                                    /**< Mode NINE for DEMAP_DEMAPLLR_CTRL           */
#define _DEMAP_DEMAPLLR_CTRL_IQNBIT_TEN            0x00000005UL                                    /**< Mode TEN for DEMAP_DEMAPLLR_CTRL            */
#define _DEMAP_DEMAPLLR_CTRL_IQNBIT_ELEVEN         0x00000006UL                                    /**< Mode ELEVEN for DEMAP_DEMAPLLR_CTRL         */
#define _DEMAP_DEMAPLLR_CTRL_IQNBIT_TWELVE         0x00000007UL                                    /**< Mode TWELVE for DEMAP_DEMAPLLR_CTRL         */
#define DEMAP_DEMAPLLR_CTRL_IQNBIT_DEFAULT         (_DEMAP_DEMAPLLR_CTRL_IQNBIT_DEFAULT << 0)      /**< Shifted mode DEFAULT for DEMAP_DEMAPLLR_CTRL*/
#define DEMAP_DEMAPLLR_CTRL_IQNBIT_FIVE            (_DEMAP_DEMAPLLR_CTRL_IQNBIT_FIVE << 0)         /**< Shifted mode FIVE for DEMAP_DEMAPLLR_CTRL   */
#define DEMAP_DEMAPLLR_CTRL_IQNBIT_SIX             (_DEMAP_DEMAPLLR_CTRL_IQNBIT_SIX << 0)          /**< Shifted mode SIX for DEMAP_DEMAPLLR_CTRL    */
#define DEMAP_DEMAPLLR_CTRL_IQNBIT_SEVEN           (_DEMAP_DEMAPLLR_CTRL_IQNBIT_SEVEN << 0)        /**< Shifted mode SEVEN for DEMAP_DEMAPLLR_CTRL  */
#define DEMAP_DEMAPLLR_CTRL_IQNBIT_EIGHT           (_DEMAP_DEMAPLLR_CTRL_IQNBIT_EIGHT << 0)        /**< Shifted mode EIGHT for DEMAP_DEMAPLLR_CTRL  */
#define DEMAP_DEMAPLLR_CTRL_IQNBIT_NINE            (_DEMAP_DEMAPLLR_CTRL_IQNBIT_NINE << 0)         /**< Shifted mode NINE for DEMAP_DEMAPLLR_CTRL   */
#define DEMAP_DEMAPLLR_CTRL_IQNBIT_TEN             (_DEMAP_DEMAPLLR_CTRL_IQNBIT_TEN << 0)          /**< Shifted mode TEN for DEMAP_DEMAPLLR_CTRL    */
#define DEMAP_DEMAPLLR_CTRL_IQNBIT_ELEVEN          (_DEMAP_DEMAPLLR_CTRL_IQNBIT_ELEVEN << 0)       /**< Shifted mode ELEVEN for DEMAP_DEMAPLLR_CTRL */
#define DEMAP_DEMAPLLR_CTRL_IQNBIT_TWELVE          (_DEMAP_DEMAPLLR_CTRL_IQNBIT_TWELVE << 0)       /**< Shifted mode TWELVE for DEMAP_DEMAPLLR_CTRL */
#define _DEMAP_DEMAPLLR_CTRL_IQDEP_SHIFT           3                                               /**< Shift value for DEMAP_IQDEP                 */
#define _DEMAP_DEMAPLLR_CTRL_IQDEP_MASK            0x18UL                                          /**< Bit mask for DEMAP_IQDEP                    */
#define _DEMAP_DEMAPLLR_CTRL_IQDEP_DEFAULT         0x00000000UL                                    /**< Mode DEFAULT for DEMAP_DEMAPLLR_CTRL        */
#define _DEMAP_DEMAPLLR_CTRL_IQDEP_I               0x00000000UL                                    /**< Mode I for DEMAP_DEMAPLLR_CTRL              */
#define _DEMAP_DEMAPLLR_CTRL_IQDEP_Q               0x00000001UL                                    /**< Mode Q for DEMAP_DEMAPLLR_CTRL              */
#define _DEMAP_DEMAPLLR_CTRL_IQDEP_IQ              0x00000002UL                                    /**< Mode IQ for DEMAP_DEMAPLLR_CTRL             */
#define _DEMAP_DEMAPLLR_CTRL_IQDEP_IQ_switch       0x00000003UL                                    /**< Mode IQ_switch for DEMAP_DEMAPLLR_CTRL      */
#define DEMAP_DEMAPLLR_CTRL_IQDEP_DEFAULT          (_DEMAP_DEMAPLLR_CTRL_IQDEP_DEFAULT << 3)       /**< Shifted mode DEFAULT for DEMAP_DEMAPLLR_CTRL*/
#define DEMAP_DEMAPLLR_CTRL_IQDEP_I                (_DEMAP_DEMAPLLR_CTRL_IQDEP_I << 3)             /**< Shifted mode I for DEMAP_DEMAPLLR_CTRL      */
#define DEMAP_DEMAPLLR_CTRL_IQDEP_Q                (_DEMAP_DEMAPLLR_CTRL_IQDEP_Q << 3)             /**< Shifted mode Q for DEMAP_DEMAPLLR_CTRL      */
#define DEMAP_DEMAPLLR_CTRL_IQDEP_IQ               (_DEMAP_DEMAPLLR_CTRL_IQDEP_IQ << 3)            /**< Shifted mode IQ for DEMAP_DEMAPLLR_CTRL     */
#define DEMAP_DEMAPLLR_CTRL_IQDEP_IQ_switch        (_DEMAP_DEMAPLLR_CTRL_IQDEP_IQ_switch << 3)     /**< Shifted mode IQ_switch for DEMAP_DEMAPLLR_CTRL*/
#define _DEMAP_DEMAPLLR_CTRL_NBIT_SHIFT            5                                               /**< Shift value for DEMAP_NBIT                  */
#define _DEMAP_DEMAPLLR_CTRL_NBIT_MASK             0x60UL                                          /**< Bit mask for DEMAP_NBIT                     */
#define _DEMAP_DEMAPLLR_CTRL_NBIT_DEFAULT          0x00000001UL                                    /**< Mode DEFAULT for DEMAP_DEMAPLLR_CTRL        */
#define _DEMAP_DEMAPLLR_CTRL_NBIT_TWO              0x00000000UL                                    /**< Mode TWO for DEMAP_DEMAPLLR_CTRL            */
#define _DEMAP_DEMAPLLR_CTRL_NBIT_FOUR             0x00000001UL                                    /**< Mode FOUR for DEMAP_DEMAPLLR_CTRL           */
#define _DEMAP_DEMAPLLR_CTRL_NBIT_EIGHT            0x00000002UL                                    /**< Mode EIGHT for DEMAP_DEMAPLLR_CTRL          */
#define _DEMAP_DEMAPLLR_CTRL_NBIT_SIXTEEN          0x00000003UL                                    /**< Mode SIXTEEN for DEMAP_DEMAPLLR_CTRL        */
#define DEMAP_DEMAPLLR_CTRL_NBIT_DEFAULT           (_DEMAP_DEMAPLLR_CTRL_NBIT_DEFAULT << 5)        /**< Shifted mode DEFAULT for DEMAP_DEMAPLLR_CTRL*/
#define DEMAP_DEMAPLLR_CTRL_NBIT_TWO               (_DEMAP_DEMAPLLR_CTRL_NBIT_TWO << 5)            /**< Shifted mode TWO for DEMAP_DEMAPLLR_CTRL    */
#define DEMAP_DEMAPLLR_CTRL_NBIT_FOUR              (_DEMAP_DEMAPLLR_CTRL_NBIT_FOUR << 5)           /**< Shifted mode FOUR for DEMAP_DEMAPLLR_CTRL   */
#define DEMAP_DEMAPLLR_CTRL_NBIT_EIGHT             (_DEMAP_DEMAPLLR_CTRL_NBIT_EIGHT << 5)          /**< Shifted mode EIGHT for DEMAP_DEMAPLLR_CTRL  */
#define DEMAP_DEMAPLLR_CTRL_NBIT_SIXTEEN           (_DEMAP_DEMAPLLR_CTRL_NBIT_SIXTEEN << 5)        /**< Shifted mode SIXTEEN for DEMAP_DEMAPLLR_CTRL*/
#define _DEMAP_DEMAPLLR_CTRL_INVLLR_SHIFT          7                                               /**< Shift value for DEMAP_INVLLR                */
#define _DEMAP_DEMAPLLR_CTRL_INVLLR_MASK           0x380UL                                         /**< Bit mask for DEMAP_INVLLR                   */
#define _DEMAP_DEMAPLLR_CTRL_INVLLR_DEFAULT        0x00000000UL                                    /**< Mode DEFAULT for DEMAP_DEMAPLLR_CTRL        */
#define DEMAP_DEMAPLLR_CTRL_INVLLR_DEFAULT         (_DEMAP_DEMAPLLR_CTRL_INVLLR_DEFAULT << 7)      /**< Shifted mode DEFAULT for DEMAP_DEMAPLLR_CTRL*/
#define DEMAP_DEMAPLLR_CTRL_INVDEC                 (0x1UL << 10)                                   /**< New BitField                                */
#define _DEMAP_DEMAPLLR_CTRL_INVDEC_SHIFT          10                                              /**< Shift value for DEMAP_INVDEC                */
#define _DEMAP_DEMAPLLR_CTRL_INVDEC_MASK           0x400UL                                         /**< Bit mask for DEMAP_INVDEC                   */
#define _DEMAP_DEMAPLLR_CTRL_INVDEC_DEFAULT        0x00000000UL                                    /**< Mode DEFAULT for DEMAP_DEMAPLLR_CTRL        */
#define _DEMAP_DEMAPLLR_CTRL_INVDEC_DONT_INVERT    0x00000000UL                                    /**< Mode DONT_INVERT for DEMAP_DEMAPLLR_CTRL    */
#define _DEMAP_DEMAPLLR_CTRL_INVDEC_INVERT         0x00000001UL                                    /**< Mode INVERT for DEMAP_DEMAPLLR_CTRL         */
#define DEMAP_DEMAPLLR_CTRL_INVDEC_DEFAULT         (_DEMAP_DEMAPLLR_CTRL_INVDEC_DEFAULT << 10)     /**< Shifted mode DEFAULT for DEMAP_DEMAPLLR_CTRL*/
#define DEMAP_DEMAPLLR_CTRL_INVDEC_DONT_INVERT     (_DEMAP_DEMAPLLR_CTRL_INVDEC_DONT_INVERT << 10) /**< Shifted mode DONT_INVERT for DEMAP_DEMAPLLR_CTRL*/
#define DEMAP_DEMAPLLR_CTRL_INVDEC_INVERT          (_DEMAP_DEMAPLLR_CTRL_INVDEC_INVERT << 10)      /**< Shifted mode INVERT for DEMAP_DEMAPLLR_CTRL */
#define _DEMAP_DEMAPLLR_CTRL_LUTADDR_SHIFT         11                                              /**< Shift value for DEMAP_LUTADDR               */
#define _DEMAP_DEMAPLLR_CTRL_LUTADDR_MASK          0x1FFF800UL                                     /**< Bit mask for DEMAP_LUTADDR                  */
#define _DEMAP_DEMAPLLR_CTRL_LUTADDR_DEFAULT       0x00000000UL                                    /**< Mode DEFAULT for DEMAP_DEMAPLLR_CTRL        */
#define DEMAP_DEMAPLLR_CTRL_LUTADDR_DEFAULT        (_DEMAP_DEMAPLLR_CTRL_LUTADDR_DEFAULT << 11)    /**< Shifted mode DEFAULT for DEMAP_DEMAPLLR_CTRL*/

/* Bit fields for DEMAP DEMAPERR_CTRL */
#define _DEMAP_DEMAPERR_CTRL_RESETVALUE            0x00000003UL                                /**< Default value for DEMAP_DEMAPERR_CTRL       */
#define _DEMAP_DEMAPERR_CTRL_MASK                  0x000FFFFFUL                                /**< Mask for DEMAP_DEMAPERR_CTRL                */
#define _DEMAP_DEMAPERR_CTRL_IQNBIT_SHIFT          0                                           /**< Shift value for DEMAP_IQNBIT                */
#define _DEMAP_DEMAPERR_CTRL_IQNBIT_MASK           0x7UL                                       /**< Bit mask for DEMAP_IQNBIT                   */
#define _DEMAP_DEMAPERR_CTRL_IQNBIT_DEFAULT        0x00000003UL                                /**< Mode DEFAULT for DEMAP_DEMAPERR_CTRL        */
#define _DEMAP_DEMAPERR_CTRL_IQNBIT_FIVE           0x00000000UL                                /**< Mode FIVE for DEMAP_DEMAPERR_CTRL           */
#define _DEMAP_DEMAPERR_CTRL_IQNBIT_SIX            0x00000001UL                                /**< Mode SIX for DEMAP_DEMAPERR_CTRL            */
#define _DEMAP_DEMAPERR_CTRL_IQNBIT_SEVEN          0x00000002UL                                /**< Mode SEVEN for DEMAP_DEMAPERR_CTRL          */
#define _DEMAP_DEMAPERR_CTRL_IQNBIT_EIGHT          0x00000003UL                                /**< Mode EIGHT for DEMAP_DEMAPERR_CTRL          */
#define _DEMAP_DEMAPERR_CTRL_IQNBIT_NINE           0x00000004UL                                /**< Mode NINE for DEMAP_DEMAPERR_CTRL           */
#define _DEMAP_DEMAPERR_CTRL_IQNBIT_TEN            0x00000005UL                                /**< Mode TEN for DEMAP_DEMAPERR_CTRL            */
#define _DEMAP_DEMAPERR_CTRL_IQNBIT_ELEVEN         0x00000006UL                                /**< Mode ELEVEN for DEMAP_DEMAPERR_CTRL         */
#define _DEMAP_DEMAPERR_CTRL_IQNBIT_TWELVE         0x00000007UL                                /**< Mode TWELVE for DEMAP_DEMAPERR_CTRL         */
#define DEMAP_DEMAPERR_CTRL_IQNBIT_DEFAULT         (_DEMAP_DEMAPERR_CTRL_IQNBIT_DEFAULT << 0)  /**< Shifted mode DEFAULT for DEMAP_DEMAPERR_CTRL*/
#define DEMAP_DEMAPERR_CTRL_IQNBIT_FIVE            (_DEMAP_DEMAPERR_CTRL_IQNBIT_FIVE << 0)     /**< Shifted mode FIVE for DEMAP_DEMAPERR_CTRL   */
#define DEMAP_DEMAPERR_CTRL_IQNBIT_SIX             (_DEMAP_DEMAPERR_CTRL_IQNBIT_SIX << 0)      /**< Shifted mode SIX for DEMAP_DEMAPERR_CTRL    */
#define DEMAP_DEMAPERR_CTRL_IQNBIT_SEVEN           (_DEMAP_DEMAPERR_CTRL_IQNBIT_SEVEN << 0)    /**< Shifted mode SEVEN for DEMAP_DEMAPERR_CTRL  */
#define DEMAP_DEMAPERR_CTRL_IQNBIT_EIGHT           (_DEMAP_DEMAPERR_CTRL_IQNBIT_EIGHT << 0)    /**< Shifted mode EIGHT for DEMAP_DEMAPERR_CTRL  */
#define DEMAP_DEMAPERR_CTRL_IQNBIT_NINE            (_DEMAP_DEMAPERR_CTRL_IQNBIT_NINE << 0)     /**< Shifted mode NINE for DEMAP_DEMAPERR_CTRL   */
#define DEMAP_DEMAPERR_CTRL_IQNBIT_TEN             (_DEMAP_DEMAPERR_CTRL_IQNBIT_TEN << 0)      /**< Shifted mode TEN for DEMAP_DEMAPERR_CTRL    */
#define DEMAP_DEMAPERR_CTRL_IQNBIT_ELEVEN          (_DEMAP_DEMAPERR_CTRL_IQNBIT_ELEVEN << 0)   /**< Shifted mode ELEVEN for DEMAP_DEMAPERR_CTRL */
#define DEMAP_DEMAPERR_CTRL_IQNBIT_TWELVE          (_DEMAP_DEMAPERR_CTRL_IQNBIT_TWELVE << 0)   /**< Shifted mode TWELVE for DEMAP_DEMAPERR_CTRL */
#define _DEMAP_DEMAPERR_CTRL_IQDEP_SHIFT           3                                           /**< Shift value for DEMAP_IQDEP                 */
#define _DEMAP_DEMAPERR_CTRL_IQDEP_MASK            0x18UL                                      /**< Bit mask for DEMAP_IQDEP                    */
#define _DEMAP_DEMAPERR_CTRL_IQDEP_DEFAULT         0x00000000UL                                /**< Mode DEFAULT for DEMAP_DEMAPERR_CTRL        */
#define _DEMAP_DEMAPERR_CTRL_IQDEP_I               0x00000000UL                                /**< Mode I for DEMAP_DEMAPERR_CTRL              */
#define _DEMAP_DEMAPERR_CTRL_IQDEP_Q               0x00000001UL                                /**< Mode Q for DEMAP_DEMAPERR_CTRL              */
#define _DEMAP_DEMAPERR_CTRL_IQDEP_IQ              0x00000002UL                                /**< Mode IQ for DEMAP_DEMAPERR_CTRL             */
#define DEMAP_DEMAPERR_CTRL_IQDEP_DEFAULT          (_DEMAP_DEMAPERR_CTRL_IQDEP_DEFAULT << 3)   /**< Shifted mode DEFAULT for DEMAP_DEMAPERR_CTRL*/
#define DEMAP_DEMAPERR_CTRL_IQDEP_I                (_DEMAP_DEMAPERR_CTRL_IQDEP_I << 3)         /**< Shifted mode I for DEMAP_DEMAPERR_CTRL      */
#define DEMAP_DEMAPERR_CTRL_IQDEP_Q                (_DEMAP_DEMAPERR_CTRL_IQDEP_Q << 3)         /**< Shifted mode Q for DEMAP_DEMAPERR_CTRL      */
#define DEMAP_DEMAPERR_CTRL_IQDEP_IQ               (_DEMAP_DEMAPERR_CTRL_IQDEP_IQ << 3)        /**< Shifted mode IQ for DEMAP_DEMAPERR_CTRL     */
#define DEMAP_DEMAPERR_CTRL_NBIT                   (0x1UL << 5)                                /**< New BitField                                */
#define _DEMAP_DEMAPERR_CTRL_NBIT_SHIFT            5                                           /**< Shift value for DEMAP_NBIT                  */
#define _DEMAP_DEMAPERR_CTRL_NBIT_MASK             0x20UL                                      /**< Bit mask for DEMAP_NBIT                     */
#define _DEMAP_DEMAPERR_CTRL_NBIT_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for DEMAP_DEMAPERR_CTRL        */
#define _DEMAP_DEMAPERR_CTRL_NBIT_EIGHT            0x00000000UL                                /**< Mode EIGHT for DEMAP_DEMAPERR_CTRL          */
#define _DEMAP_DEMAPERR_CTRL_NBIT_SIXTEEN          0x00000001UL                                /**< Mode SIXTEEN for DEMAP_DEMAPERR_CTRL        */
#define DEMAP_DEMAPERR_CTRL_NBIT_DEFAULT           (_DEMAP_DEMAPERR_CTRL_NBIT_DEFAULT << 5)    /**< Shifted mode DEFAULT for DEMAP_DEMAPERR_CTRL*/
#define DEMAP_DEMAPERR_CTRL_NBIT_EIGHT             (_DEMAP_DEMAPERR_CTRL_NBIT_EIGHT << 5)      /**< Shifted mode EIGHT for DEMAP_DEMAPERR_CTRL  */
#define DEMAP_DEMAPERR_CTRL_NBIT_SIXTEEN           (_DEMAP_DEMAPERR_CTRL_NBIT_SIXTEEN << 5)    /**< Shifted mode SIXTEEN for DEMAP_DEMAPERR_CTRL*/
#define _DEMAP_DEMAPERR_CTRL_LUTADDR_SHIFT         6                                           /**< Shift value for DEMAP_LUTADDR               */
#define _DEMAP_DEMAPERR_CTRL_LUTADDR_MASK          0xFFFC0UL                                   /**< Bit mask for DEMAP_LUTADDR                  */
#define _DEMAP_DEMAPERR_CTRL_LUTADDR_DEFAULT       0x00000000UL                                /**< Mode DEFAULT for DEMAP_DEMAPERR_CTRL        */
#define DEMAP_DEMAPERR_CTRL_LUTADDR_DEFAULT        (_DEMAP_DEMAPERR_CTRL_LUTADDR_DEFAULT << 6) /**< Shifted mode DEFAULT for DEMAP_DEMAPERR_CTRL*/

/** @} End of group EFR32FG25_DEMAP_BitFields */
/** @} End of group EFR32FG25_DEMAP */
/** @} End of group Parts */

#endif /* EFR32FG25_DEMAP_H */
