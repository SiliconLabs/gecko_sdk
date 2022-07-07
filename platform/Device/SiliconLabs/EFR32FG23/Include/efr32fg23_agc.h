/**************************************************************************//**
 * @file
 * @brief EFR32FG23 AGC register and bit field definitions
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
#ifndef EFR32FG23_AGC_H
#define EFR32FG23_AGC_H
#define AGC_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG23_AGC AGC
 * @{
 * @brief EFR32FG23 AGC Register Declaration.
 *****************************************************************************/

/** AGC Register Declaration. */
typedef struct {
  __IM uint32_t  IPVERSION;                     /**< IP Version                                         */
  __IOM uint32_t EN;                            /**< Enable peripheral clock to this module             */
  __IM uint32_t  STATUS0;                       /**< Status register 0                                  */
  __IM uint32_t  STATUS1;                       /**< Status register 1                                  */
  __IM uint32_t  STATUS2;                       /**< Status register 2                                  */
  uint32_t       RESERVED0[1U];                 /**< Reserved for future use                            */
  __IM uint32_t  RSSI;                          /**< Received Signal Strength Indicator                 */
  __IM uint32_t  FRAMERSSI;                     /**< FRAME RSSI value                                   */
  __IOM uint32_t CTRL0;                         /**< Control register 0                                 */
  __IOM uint32_t CTRL1;                         /**< Control register 1                                 */
  __IOM uint32_t CTRL2;                         /**< Control register 2                                 */
  __IOM uint32_t CTRL3;                         /**< Control register 3                                 */
  __IOM uint32_t CTRL4;                         /**< Control register 4                                 */
  __IOM uint32_t CTRL5;                         /**< Control register 5                                 */
  __IOM uint32_t CTRL6;                         /**< Control register 6                                 */
  __IOM uint32_t CTRL7;                         /**< Control register 1                                 */
  __IOM uint32_t RSSISTEPTHR;                   /**< RSSI step threshold                                */
  uint32_t       RESERVED1[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t IF;                            /**< Interrupt Flags Register                           */
  __IOM uint32_t IEN;                           /**< Interrupt Enable Register                          */
  uint32_t       RESERVED2[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t GAINRANGE;                     /**< Range of RX Gain to use in AGC                     */
  __IOM uint32_t AGCPERIOD0;                    /**< AGC period                                         */
  __IOM uint32_t AGCPERIOD1;                    /**< AGC Period                                         */
  __IOM uint32_t HICNTREGION0;                  /**< Hi-counter region-0                                */
  __IOM uint32_t HICNTREGION1;                  /**< Hi-counter region-1                                */
  __IOM uint32_t STEPDWN;                       /**< Hi-counter region-2                                */
  __IOM uint32_t GAINSTEPLIM0;                  /**< Limits for Gain Steps                              */
  __IOM uint32_t GAINSTEPLIM1;                  /**< Limits for Gain Steps                              */
  __IOM uint32_t PNRFATT0;                      /**< PN RF attenuation code group 0                     */
  __IOM uint32_t PNRFATT1;                      /**< PN RF attenuation code group 1                     */
  __IOM uint32_t PNRFATT2;                      /**< PN RF attenuation code group 2                     */
  __IOM uint32_t PNRFATT3;                      /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT4;                      /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT5;                      /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT6;                      /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT7;                      /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT8;                      /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT9;                      /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT10;                     /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT11;                     /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATTALT;                    /**< PN RF attenuation code group 3                     */
  __IOM uint32_t LNAMIXCODE0;                   /**< LNA/MIX slice code group 0                         */
  __IOM uint32_t LNAMIXCODE1;                   /**< LNA/MIX slice code group 1                         */
  __IOM uint32_t PGACODE0;                      /**< PGA gain code group 0                              */
  __IOM uint32_t PGACODE1;                      /**< PGA gain code group 1                              */
  __IOM uint32_t LBT;                           /**< Configure AGC for (ETSI) LBT                       */
  __IOM uint32_t MIRRORIF;                      /**< Mirror Interrupt Flags Register                    */
  __IOM uint32_t SEQIF;                         /**< SEQ Interrupt Flags Register                       */
  __IOM uint32_t SEQIEN;                        /**< SEQ Interrupt Enable Register                      */
  __IOM uint32_t RSSIABSTHR;                    /**< RSSI absolute threshold                            */
  __IOM uint32_t LNABOOST;                      /**< LNA boost control register                         */
  __IOM uint32_t ANTDIV;                        /**< Antenna diversity AGC setting                      */
  __IOM uint32_t DUALRFPKDTHD0;                 /**< Thresholds for dual rfpkd                          */
  __IOM uint32_t DUALRFPKDTHD1;                 /**< Thresholds for dual rfpkd                          */
  __IOM uint32_t SPARE;                         /**< Spare register for ECO                             */
  uint32_t       RESERVED3[968U];               /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP Version                                         */
  __IOM uint32_t EN_SET;                        /**< Enable peripheral clock to this module             */
  __IM uint32_t  STATUS0_SET;                   /**< Status register 0                                  */
  __IM uint32_t  STATUS1_SET;                   /**< Status register 1                                  */
  __IM uint32_t  STATUS2_SET;                   /**< Status register 2                                  */
  uint32_t       RESERVED4[1U];                 /**< Reserved for future use                            */
  __IM uint32_t  RSSI_SET;                      /**< Received Signal Strength Indicator                 */
  __IM uint32_t  FRAMERSSI_SET;                 /**< FRAME RSSI value                                   */
  __IOM uint32_t CTRL0_SET;                     /**< Control register 0                                 */
  __IOM uint32_t CTRL1_SET;                     /**< Control register 1                                 */
  __IOM uint32_t CTRL2_SET;                     /**< Control register 2                                 */
  __IOM uint32_t CTRL3_SET;                     /**< Control register 3                                 */
  __IOM uint32_t CTRL4_SET;                     /**< Control register 4                                 */
  __IOM uint32_t CTRL5_SET;                     /**< Control register 5                                 */
  __IOM uint32_t CTRL6_SET;                     /**< Control register 6                                 */
  __IOM uint32_t CTRL7_SET;                     /**< Control register 1                                 */
  __IOM uint32_t RSSISTEPTHR_SET;               /**< RSSI step threshold                                */
  uint32_t       RESERVED5[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t IF_SET;                        /**< Interrupt Flags Register                           */
  __IOM uint32_t IEN_SET;                       /**< Interrupt Enable Register                          */
  uint32_t       RESERVED6[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t GAINRANGE_SET;                 /**< Range of RX Gain to use in AGC                     */
  __IOM uint32_t AGCPERIOD0_SET;                /**< AGC period                                         */
  __IOM uint32_t AGCPERIOD1_SET;                /**< AGC Period                                         */
  __IOM uint32_t HICNTREGION0_SET;              /**< Hi-counter region-0                                */
  __IOM uint32_t HICNTREGION1_SET;              /**< Hi-counter region-1                                */
  __IOM uint32_t STEPDWN_SET;                   /**< Hi-counter region-2                                */
  __IOM uint32_t GAINSTEPLIM0_SET;              /**< Limits for Gain Steps                              */
  __IOM uint32_t GAINSTEPLIM1_SET;              /**< Limits for Gain Steps                              */
  __IOM uint32_t PNRFATT0_SET;                  /**< PN RF attenuation code group 0                     */
  __IOM uint32_t PNRFATT1_SET;                  /**< PN RF attenuation code group 1                     */
  __IOM uint32_t PNRFATT2_SET;                  /**< PN RF attenuation code group 2                     */
  __IOM uint32_t PNRFATT3_SET;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT4_SET;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT5_SET;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT6_SET;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT7_SET;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT8_SET;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT9_SET;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT10_SET;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT11_SET;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATTALT_SET;                /**< PN RF attenuation code group 3                     */
  __IOM uint32_t LNAMIXCODE0_SET;               /**< LNA/MIX slice code group 0                         */
  __IOM uint32_t LNAMIXCODE1_SET;               /**< LNA/MIX slice code group 1                         */
  __IOM uint32_t PGACODE0_SET;                  /**< PGA gain code group 0                              */
  __IOM uint32_t PGACODE1_SET;                  /**< PGA gain code group 1                              */
  __IOM uint32_t LBT_SET;                       /**< Configure AGC for (ETSI) LBT                       */
  __IOM uint32_t MIRRORIF_SET;                  /**< Mirror Interrupt Flags Register                    */
  __IOM uint32_t SEQIF_SET;                     /**< SEQ Interrupt Flags Register                       */
  __IOM uint32_t SEQIEN_SET;                    /**< SEQ Interrupt Enable Register                      */
  __IOM uint32_t RSSIABSTHR_SET;                /**< RSSI absolute threshold                            */
  __IOM uint32_t LNABOOST_SET;                  /**< LNA boost control register                         */
  __IOM uint32_t ANTDIV_SET;                    /**< Antenna diversity AGC setting                      */
  __IOM uint32_t DUALRFPKDTHD0_SET;             /**< Thresholds for dual rfpkd                          */
  __IOM uint32_t DUALRFPKDTHD1_SET;             /**< Thresholds for dual rfpkd                          */
  __IOM uint32_t SPARE_SET;                     /**< Spare register for ECO                             */
  uint32_t       RESERVED7[968U];               /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP Version                                         */
  __IOM uint32_t EN_CLR;                        /**< Enable peripheral clock to this module             */
  __IM uint32_t  STATUS0_CLR;                   /**< Status register 0                                  */
  __IM uint32_t  STATUS1_CLR;                   /**< Status register 1                                  */
  __IM uint32_t  STATUS2_CLR;                   /**< Status register 2                                  */
  uint32_t       RESERVED8[1U];                 /**< Reserved for future use                            */
  __IM uint32_t  RSSI_CLR;                      /**< Received Signal Strength Indicator                 */
  __IM uint32_t  FRAMERSSI_CLR;                 /**< FRAME RSSI value                                   */
  __IOM uint32_t CTRL0_CLR;                     /**< Control register 0                                 */
  __IOM uint32_t CTRL1_CLR;                     /**< Control register 1                                 */
  __IOM uint32_t CTRL2_CLR;                     /**< Control register 2                                 */
  __IOM uint32_t CTRL3_CLR;                     /**< Control register 3                                 */
  __IOM uint32_t CTRL4_CLR;                     /**< Control register 4                                 */
  __IOM uint32_t CTRL5_CLR;                     /**< Control register 5                                 */
  __IOM uint32_t CTRL6_CLR;                     /**< Control register 6                                 */
  __IOM uint32_t CTRL7_CLR;                     /**< Control register 1                                 */
  __IOM uint32_t RSSISTEPTHR_CLR;               /**< RSSI step threshold                                */
  uint32_t       RESERVED9[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t IF_CLR;                        /**< Interrupt Flags Register                           */
  __IOM uint32_t IEN_CLR;                       /**< Interrupt Enable Register                          */
  uint32_t       RESERVED10[1U];                /**< Reserved for future use                            */
  __IOM uint32_t GAINRANGE_CLR;                 /**< Range of RX Gain to use in AGC                     */
  __IOM uint32_t AGCPERIOD0_CLR;                /**< AGC period                                         */
  __IOM uint32_t AGCPERIOD1_CLR;                /**< AGC Period                                         */
  __IOM uint32_t HICNTREGION0_CLR;              /**< Hi-counter region-0                                */
  __IOM uint32_t HICNTREGION1_CLR;              /**< Hi-counter region-1                                */
  __IOM uint32_t STEPDWN_CLR;                   /**< Hi-counter region-2                                */
  __IOM uint32_t GAINSTEPLIM0_CLR;              /**< Limits for Gain Steps                              */
  __IOM uint32_t GAINSTEPLIM1_CLR;              /**< Limits for Gain Steps                              */
  __IOM uint32_t PNRFATT0_CLR;                  /**< PN RF attenuation code group 0                     */
  __IOM uint32_t PNRFATT1_CLR;                  /**< PN RF attenuation code group 1                     */
  __IOM uint32_t PNRFATT2_CLR;                  /**< PN RF attenuation code group 2                     */
  __IOM uint32_t PNRFATT3_CLR;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT4_CLR;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT5_CLR;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT6_CLR;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT7_CLR;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT8_CLR;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT9_CLR;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT10_CLR;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT11_CLR;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATTALT_CLR;                /**< PN RF attenuation code group 3                     */
  __IOM uint32_t LNAMIXCODE0_CLR;               /**< LNA/MIX slice code group 0                         */
  __IOM uint32_t LNAMIXCODE1_CLR;               /**< LNA/MIX slice code group 1                         */
  __IOM uint32_t PGACODE0_CLR;                  /**< PGA gain code group 0                              */
  __IOM uint32_t PGACODE1_CLR;                  /**< PGA gain code group 1                              */
  __IOM uint32_t LBT_CLR;                       /**< Configure AGC for (ETSI) LBT                       */
  __IOM uint32_t MIRRORIF_CLR;                  /**< Mirror Interrupt Flags Register                    */
  __IOM uint32_t SEQIF_CLR;                     /**< SEQ Interrupt Flags Register                       */
  __IOM uint32_t SEQIEN_CLR;                    /**< SEQ Interrupt Enable Register                      */
  __IOM uint32_t RSSIABSTHR_CLR;                /**< RSSI absolute threshold                            */
  __IOM uint32_t LNABOOST_CLR;                  /**< LNA boost control register                         */
  __IOM uint32_t ANTDIV_CLR;                    /**< Antenna diversity AGC setting                      */
  __IOM uint32_t DUALRFPKDTHD0_CLR;             /**< Thresholds for dual rfpkd                          */
  __IOM uint32_t DUALRFPKDTHD1_CLR;             /**< Thresholds for dual rfpkd                          */
  __IOM uint32_t SPARE_CLR;                     /**< Spare register for ECO                             */
  uint32_t       RESERVED11[968U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP Version                                         */
  __IOM uint32_t EN_TGL;                        /**< Enable peripheral clock to this module             */
  __IM uint32_t  STATUS0_TGL;                   /**< Status register 0                                  */
  __IM uint32_t  STATUS1_TGL;                   /**< Status register 1                                  */
  __IM uint32_t  STATUS2_TGL;                   /**< Status register 2                                  */
  uint32_t       RESERVED12[1U];                /**< Reserved for future use                            */
  __IM uint32_t  RSSI_TGL;                      /**< Received Signal Strength Indicator                 */
  __IM uint32_t  FRAMERSSI_TGL;                 /**< FRAME RSSI value                                   */
  __IOM uint32_t CTRL0_TGL;                     /**< Control register 0                                 */
  __IOM uint32_t CTRL1_TGL;                     /**< Control register 1                                 */
  __IOM uint32_t CTRL2_TGL;                     /**< Control register 2                                 */
  __IOM uint32_t CTRL3_TGL;                     /**< Control register 3                                 */
  __IOM uint32_t CTRL4_TGL;                     /**< Control register 4                                 */
  __IOM uint32_t CTRL5_TGL;                     /**< Control register 5                                 */
  __IOM uint32_t CTRL6_TGL;                     /**< Control register 6                                 */
  __IOM uint32_t CTRL7_TGL;                     /**< Control register 1                                 */
  __IOM uint32_t RSSISTEPTHR_TGL;               /**< RSSI step threshold                                */
  uint32_t       RESERVED13[1U];                /**< Reserved for future use                            */
  __IOM uint32_t IF_TGL;                        /**< Interrupt Flags Register                           */
  __IOM uint32_t IEN_TGL;                       /**< Interrupt Enable Register                          */
  uint32_t       RESERVED14[1U];                /**< Reserved for future use                            */
  __IOM uint32_t GAINRANGE_TGL;                 /**< Range of RX Gain to use in AGC                     */
  __IOM uint32_t AGCPERIOD0_TGL;                /**< AGC period                                         */
  __IOM uint32_t AGCPERIOD1_TGL;                /**< AGC Period                                         */
  __IOM uint32_t HICNTREGION0_TGL;              /**< Hi-counter region-0                                */
  __IOM uint32_t HICNTREGION1_TGL;              /**< Hi-counter region-1                                */
  __IOM uint32_t STEPDWN_TGL;                   /**< Hi-counter region-2                                */
  __IOM uint32_t GAINSTEPLIM0_TGL;              /**< Limits for Gain Steps                              */
  __IOM uint32_t GAINSTEPLIM1_TGL;              /**< Limits for Gain Steps                              */
  __IOM uint32_t PNRFATT0_TGL;                  /**< PN RF attenuation code group 0                     */
  __IOM uint32_t PNRFATT1_TGL;                  /**< PN RF attenuation code group 1                     */
  __IOM uint32_t PNRFATT2_TGL;                  /**< PN RF attenuation code group 2                     */
  __IOM uint32_t PNRFATT3_TGL;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT4_TGL;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT5_TGL;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT6_TGL;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT7_TGL;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT8_TGL;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT9_TGL;                  /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT10_TGL;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATT11_TGL;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFATTALT_TGL;                /**< PN RF attenuation code group 3                     */
  __IOM uint32_t LNAMIXCODE0_TGL;               /**< LNA/MIX slice code group 0                         */
  __IOM uint32_t LNAMIXCODE1_TGL;               /**< LNA/MIX slice code group 1                         */
  __IOM uint32_t PGACODE0_TGL;                  /**< PGA gain code group 0                              */
  __IOM uint32_t PGACODE1_TGL;                  /**< PGA gain code group 1                              */
  __IOM uint32_t LBT_TGL;                       /**< Configure AGC for (ETSI) LBT                       */
  __IOM uint32_t MIRRORIF_TGL;                  /**< Mirror Interrupt Flags Register                    */
  __IOM uint32_t SEQIF_TGL;                     /**< SEQ Interrupt Flags Register                       */
  __IOM uint32_t SEQIEN_TGL;                    /**< SEQ Interrupt Enable Register                      */
  __IOM uint32_t RSSIABSTHR_TGL;                /**< RSSI absolute threshold                            */
  __IOM uint32_t LNABOOST_TGL;                  /**< LNA boost control register                         */
  __IOM uint32_t ANTDIV_TGL;                    /**< Antenna diversity AGC setting                      */
  __IOM uint32_t DUALRFPKDTHD0_TGL;             /**< Thresholds for dual rfpkd                          */
  __IOM uint32_t DUALRFPKDTHD1_TGL;             /**< Thresholds for dual rfpkd                          */
  __IOM uint32_t SPARE_TGL;                     /**< Spare register for ECO                             */
} AGC_TypeDef;
/** @} End of group EFR32FG23_AGC */

/**************************************************************************//**
 * @addtogroup EFR32FG23_AGC
 * @{
 * @defgroup EFR32FG23_AGC_BitFields AGC Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for AGC IPVERSION */
#define _AGC_IPVERSION_RESETVALUE                   0x00000002UL                            /**< Default value for AGC_IPVERSION             */
#define _AGC_IPVERSION_MASK                         0xFFFFFFFFUL                            /**< Mask for AGC_IPVERSION                      */
#define _AGC_IPVERSION_IPVERSION_SHIFT              0                                       /**< Shift value for AGC_IPVERSION               */
#define _AGC_IPVERSION_IPVERSION_MASK               0xFFFFFFFFUL                            /**< Bit mask for AGC_IPVERSION                  */
#define _AGC_IPVERSION_IPVERSION_DEFAULT            0x00000002UL                            /**< Mode DEFAULT for AGC_IPVERSION              */
#define AGC_IPVERSION_IPVERSION_DEFAULT             (_AGC_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_IPVERSION      */

/* Bit fields for AGC EN */
#define _AGC_EN_RESETVALUE                          0x00000000UL                        /**< Default value for AGC_EN                    */
#define _AGC_EN_MASK                                0x00000001UL                        /**< Mask for AGC_EN                             */
#define AGC_EN_EN                                   (0x1UL << 0)                        /**< Enable peripheral clock to this module      */
#define _AGC_EN_EN_SHIFT                            0                                   /**< Shift value for AGC_EN                      */
#define _AGC_EN_EN_MASK                             0x1UL                               /**< Bit mask for AGC_EN                         */
#define _AGC_EN_EN_DEFAULT                          0x00000000UL                        /**< Mode DEFAULT for AGC_EN                     */
#define AGC_EN_EN_DEFAULT                           (_AGC_EN_EN_DEFAULT << 0)           /**< Shifted mode DEFAULT for AGC_EN             */

/* Bit fields for AGC STATUS0 */
#define _AGC_STATUS0_RESETVALUE                     0x00000000UL                            /**< Default value for AGC_STATUS0               */
#define _AGC_STATUS0_MASK                           0x07FFFFFFUL                            /**< Mask for AGC_STATUS0                        */
#define _AGC_STATUS0_GAININDEX_SHIFT                0                                       /**< Shift value for AGC_GAININDEX               */
#define _AGC_STATUS0_GAININDEX_MASK                 0x3FUL                                  /**< Bit mask for AGC_GAININDEX                  */
#define _AGC_STATUS0_GAININDEX_DEFAULT              0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_GAININDEX_DEFAULT               (_AGC_STATUS0_GAININDEX_DEFAULT << 0)   /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define AGC_STATUS0_RFPKDLOWLAT                     (0x1UL << 6)                            /**< RFPKD low Latch                             */
#define _AGC_STATUS0_RFPKDLOWLAT_SHIFT              6                                       /**< Shift value for AGC_RFPKDLOWLAT             */
#define _AGC_STATUS0_RFPKDLOWLAT_MASK               0x40UL                                  /**< Bit mask for AGC_RFPKDLOWLAT                */
#define _AGC_STATUS0_RFPKDLOWLAT_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_RFPKDLOWLAT_DEFAULT             (_AGC_STATUS0_RFPKDLOWLAT_DEFAULT << 6) /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define AGC_STATUS0_RFPKDHILAT                      (0x1UL << 7)                            /**< RFPKD hi Latch                              */
#define _AGC_STATUS0_RFPKDHILAT_SHIFT               7                                       /**< Shift value for AGC_RFPKDHILAT              */
#define _AGC_STATUS0_RFPKDHILAT_MASK                0x80UL                                  /**< Bit mask for AGC_RFPKDHILAT                 */
#define _AGC_STATUS0_RFPKDHILAT_DEFAULT             0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_RFPKDHILAT_DEFAULT              (_AGC_STATUS0_RFPKDHILAT_DEFAULT << 7)  /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define AGC_STATUS0_IFPKDLOLAT                      (0x1UL << 8)                            /**< IFPKD Lo threshold pass Latch               */
#define _AGC_STATUS0_IFPKDLOLAT_SHIFT               8                                       /**< Shift value for AGC_IFPKDLOLAT              */
#define _AGC_STATUS0_IFPKDLOLAT_MASK                0x100UL                                 /**< Bit mask for AGC_IFPKDLOLAT                 */
#define _AGC_STATUS0_IFPKDLOLAT_DEFAULT             0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_IFPKDLOLAT_DEFAULT              (_AGC_STATUS0_IFPKDLOLAT_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define AGC_STATUS0_IFPKDHILAT                      (0x1UL << 9)                            /**< IFPKD Hi threshold pass Latch               */
#define _AGC_STATUS0_IFPKDHILAT_SHIFT               9                                       /**< Shift value for AGC_IFPKDHILAT              */
#define _AGC_STATUS0_IFPKDHILAT_MASK                0x200UL                                 /**< Bit mask for AGC_IFPKDHILAT                 */
#define _AGC_STATUS0_IFPKDHILAT_DEFAULT             0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_IFPKDHILAT_DEFAULT              (_AGC_STATUS0_IFPKDHILAT_DEFAULT << 9)  /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define AGC_STATUS0_CCA                             (0x1UL << 10)                           /**< Clear Channel Assessment                    */
#define _AGC_STATUS0_CCA_SHIFT                      10                                      /**< Shift value for AGC_CCA                     */
#define _AGC_STATUS0_CCA_MASK                       0x400UL                                 /**< Bit mask for AGC_CCA                        */
#define _AGC_STATUS0_CCA_DEFAULT                    0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_CCA_DEFAULT                     (_AGC_STATUS0_CCA_DEFAULT << 10)        /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define AGC_STATUS0_GAINOK                          (0x1UL << 11)                           /**< Gain OK                                     */
#define _AGC_STATUS0_GAINOK_SHIFT                   11                                      /**< Shift value for AGC_GAINOK                  */
#define _AGC_STATUS0_GAINOK_MASK                    0x800UL                                 /**< Bit mask for AGC_GAINOK                     */
#define _AGC_STATUS0_GAINOK_DEFAULT                 0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_GAINOK_DEFAULT                  (_AGC_STATUS0_GAINOK_DEFAULT << 11)     /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define _AGC_STATUS0_PGAINDEX_SHIFT                 12                                      /**< Shift value for AGC_PGAINDEX                */
#define _AGC_STATUS0_PGAINDEX_MASK                  0xF000UL                                /**< Bit mask for AGC_PGAINDEX                   */
#define _AGC_STATUS0_PGAINDEX_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_PGAINDEX_DEFAULT                (_AGC_STATUS0_PGAINDEX_DEFAULT << 12)   /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define _AGC_STATUS0_LNAINDEX_SHIFT                 16                                      /**< Shift value for AGC_LNAINDEX                */
#define _AGC_STATUS0_LNAINDEX_MASK                  0xF0000UL                               /**< Bit mask for AGC_LNAINDEX                   */
#define _AGC_STATUS0_LNAINDEX_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_LNAINDEX_DEFAULT                (_AGC_STATUS0_LNAINDEX_DEFAULT << 16)   /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define _AGC_STATUS0_PNINDEX_SHIFT                  20                                      /**< Shift value for AGC_PNINDEX                 */
#define _AGC_STATUS0_PNINDEX_MASK                   0x1F00000UL                             /**< Bit mask for AGC_PNINDEX                    */
#define _AGC_STATUS0_PNINDEX_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_PNINDEX_DEFAULT                 (_AGC_STATUS0_PNINDEX_DEFAULT << 20)    /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define _AGC_STATUS0_ADCINDEX_SHIFT                 25                                      /**< Shift value for AGC_ADCINDEX                */
#define _AGC_STATUS0_ADCINDEX_MASK                  0x6000000UL                             /**< Bit mask for AGC_ADCINDEX                   */
#define _AGC_STATUS0_ADCINDEX_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_ADCINDEX_DEFAULT                (_AGC_STATUS0_ADCINDEX_DEFAULT << 25)   /**< Shifted mode DEFAULT for AGC_STATUS0        */

/* Bit fields for AGC STATUS1 */
#define _AGC_STATUS1_RESETVALUE                     0x00000000UL                                /**< Default value for AGC_STATUS1               */
#define _AGC_STATUS1_MASK                           0x3FFFFEFFUL                                /**< Mask for AGC_STATUS1                        */
#define _AGC_STATUS1_RFPKDLOWLATCNT_SHIFT           18                                          /**< Shift value for AGC_RFPKDLOWLATCNT          */
#define _AGC_STATUS1_RFPKDLOWLATCNT_MASK            0x3FFC0000UL                                /**< Bit mask for AGC_RFPKDLOWLATCNT             */
#define _AGC_STATUS1_RFPKDLOWLATCNT_DEFAULT         0x00000000UL                                /**< Mode DEFAULT for AGC_STATUS1                */
#define AGC_STATUS1_RFPKDLOWLATCNT_DEFAULT          (_AGC_STATUS1_RFPKDLOWLATCNT_DEFAULT << 18) /**< Shifted mode DEFAULT for AGC_STATUS1        */

/* Bit fields for AGC STATUS2 */
#define _AGC_STATUS2_RESETVALUE                     0x00000000UL                              /**< Default value for AGC_STATUS2               */
#define _AGC_STATUS2_MASK                           0xFFFF4FFFUL                              /**< Mask for AGC_STATUS2                        */
#define _AGC_STATUS2_RFPKDHILATCNT_SHIFT            0                                         /**< Shift value for AGC_RFPKDHILATCNT           */
#define _AGC_STATUS2_RFPKDHILATCNT_MASK             0xFFFUL                                   /**< Bit mask for AGC_RFPKDHILATCNT              */
#define _AGC_STATUS2_RFPKDHILATCNT_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for AGC_STATUS2                */
#define AGC_STATUS2_RFPKDHILATCNT_DEFAULT           (_AGC_STATUS2_RFPKDHILATCNT_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_STATUS2        */
#define AGC_STATUS2_PNDWNUP                         (0x1UL << 14)                             /**< Allow PN GAIN UP                            */
#define _AGC_STATUS2_PNDWNUP_SHIFT                  14                                        /**< Shift value for AGC_PNDWNUP                 */
#define _AGC_STATUS2_PNDWNUP_MASK                   0x4000UL                                  /**< Bit mask for AGC_PNDWNUP                    */
#define _AGC_STATUS2_PNDWNUP_DEFAULT                0x00000000UL                              /**< Mode DEFAULT for AGC_STATUS2                */
#define AGC_STATUS2_PNDWNUP_DEFAULT                 (_AGC_STATUS2_PNDWNUP_DEFAULT << 14)      /**< Shifted mode DEFAULT for AGC_STATUS2        */
#define _AGC_STATUS2_RFPKDPRDCNT_SHIFT              16                                        /**< Shift value for AGC_RFPKDPRDCNT             */
#define _AGC_STATUS2_RFPKDPRDCNT_MASK               0xFFFF0000UL                              /**< Bit mask for AGC_RFPKDPRDCNT                */
#define _AGC_STATUS2_RFPKDPRDCNT_DEFAULT            0x00000000UL                              /**< Mode DEFAULT for AGC_STATUS2                */
#define AGC_STATUS2_RFPKDPRDCNT_DEFAULT             (_AGC_STATUS2_RFPKDPRDCNT_DEFAULT << 16)  /**< Shifted mode DEFAULT for AGC_STATUS2        */

/* Bit fields for AGC RSSI */
#define _AGC_RSSI_RESETVALUE                        0x00008000UL                        /**< Default value for AGC_RSSI                  */
#define _AGC_RSSI_MASK                              0x0000FFC0UL                        /**< Mask for AGC_RSSI                           */
#define _AGC_RSSI_RSSIFRAC_SHIFT                    6                                   /**< Shift value for AGC_RSSIFRAC                */
#define _AGC_RSSI_RSSIFRAC_MASK                     0xC0UL                              /**< Bit mask for AGC_RSSIFRAC                   */
#define _AGC_RSSI_RSSIFRAC_DEFAULT                  0x00000000UL                        /**< Mode DEFAULT for AGC_RSSI                   */
#define AGC_RSSI_RSSIFRAC_DEFAULT                   (_AGC_RSSI_RSSIFRAC_DEFAULT << 6)   /**< Shifted mode DEFAULT for AGC_RSSI           */
#define _AGC_RSSI_RSSIINT_SHIFT                     8                                   /**< Shift value for AGC_RSSIINT                 */
#define _AGC_RSSI_RSSIINT_MASK                      0xFF00UL                            /**< Bit mask for AGC_RSSIINT                    */
#define _AGC_RSSI_RSSIINT_DEFAULT                   0x00000080UL                        /**< Mode DEFAULT for AGC_RSSI                   */
#define AGC_RSSI_RSSIINT_DEFAULT                    (_AGC_RSSI_RSSIINT_DEFAULT << 8)    /**< Shifted mode DEFAULT for AGC_RSSI           */

/* Bit fields for AGC FRAMERSSI */
#define _AGC_FRAMERSSI_RESETVALUE                   0x00008000UL                                /**< Default value for AGC_FRAMERSSI             */
#define _AGC_FRAMERSSI_MASK                         0x0000FFC0UL                                /**< Mask for AGC_FRAMERSSI                      */
#define _AGC_FRAMERSSI_FRAMERSSIFRAC_SHIFT          6                                           /**< Shift value for AGC_FRAMERSSIFRAC           */
#define _AGC_FRAMERSSI_FRAMERSSIFRAC_MASK           0xC0UL                                      /**< Bit mask for AGC_FRAMERSSIFRAC              */
#define _AGC_FRAMERSSI_FRAMERSSIFRAC_DEFAULT        0x00000000UL                                /**< Mode DEFAULT for AGC_FRAMERSSI              */
#define AGC_FRAMERSSI_FRAMERSSIFRAC_DEFAULT         (_AGC_FRAMERSSI_FRAMERSSIFRAC_DEFAULT << 6) /**< Shifted mode DEFAULT for AGC_FRAMERSSI      */
#define _AGC_FRAMERSSI_FRAMERSSIINT_SHIFT           8                                           /**< Shift value for AGC_FRAMERSSIINT            */
#define _AGC_FRAMERSSI_FRAMERSSIINT_MASK            0xFF00UL                                    /**< Bit mask for AGC_FRAMERSSIINT               */
#define _AGC_FRAMERSSI_FRAMERSSIINT_DEFAULT         0x00000080UL                                /**< Mode DEFAULT for AGC_FRAMERSSI              */
#define AGC_FRAMERSSI_FRAMERSSIINT_DEFAULT          (_AGC_FRAMERSSI_FRAMERSSIINT_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FRAMERSSI      */

/* Bit fields for AGC CTRL0 */
#define _AGC_CTRL0_RESETVALUE                       0x2032727FUL                               /**< Default value for AGC_CTRL0                 */
#define _AGC_CTRL0_MASK                             0xFEFFFFFFUL                               /**< Mask for AGC_CTRL0                          */
#define _AGC_CTRL0_PWRTARGET_SHIFT                  0                                          /**< Shift value for AGC_PWRTARGET               */
#define _AGC_CTRL0_PWRTARGET_MASK                   0xFFUL                                     /**< Bit mask for AGC_PWRTARGET                  */
#define _AGC_CTRL0_PWRTARGET_DEFAULT                0x0000007FUL                               /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_PWRTARGET_DEFAULT                 (_AGC_CTRL0_PWRTARGET_DEFAULT << 0)        /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define _AGC_CTRL0_MODE_SHIFT                       8                                          /**< Shift value for AGC_MODE                    */
#define _AGC_CTRL0_MODE_MASK                        0x700UL                                    /**< Bit mask for AGC_MODE                       */
#define _AGC_CTRL0_MODE_DEFAULT                     0x00000002UL                               /**< Mode DEFAULT for AGC_CTRL0                  */
#define _AGC_CTRL0_MODE_CONT                        0x00000000UL                               /**< Mode CONT for AGC_CTRL0                     */
#define _AGC_CTRL0_MODE_LOCKPREDET                  0x00000001UL                               /**< Mode LOCKPREDET for AGC_CTRL0               */
#define _AGC_CTRL0_MODE_LOCKFRAMEDET                0x00000002UL                               /**< Mode LOCKFRAMEDET for AGC_CTRL0             */
#define _AGC_CTRL0_MODE_LOCKDSA                     0x00000003UL                               /**< Mode LOCKDSA for AGC_CTRL0                  */
#define AGC_CTRL0_MODE_DEFAULT                      (_AGC_CTRL0_MODE_DEFAULT << 8)             /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_MODE_CONT                         (_AGC_CTRL0_MODE_CONT << 8)                /**< Shifted mode CONT for AGC_CTRL0             */
#define AGC_CTRL0_MODE_LOCKPREDET                   (_AGC_CTRL0_MODE_LOCKPREDET << 8)          /**< Shifted mode LOCKPREDET for AGC_CTRL0       */
#define AGC_CTRL0_MODE_LOCKFRAMEDET                 (_AGC_CTRL0_MODE_LOCKFRAMEDET << 8)        /**< Shifted mode LOCKFRAMEDET for AGC_CTRL0     */
#define AGC_CTRL0_MODE_LOCKDSA                      (_AGC_CTRL0_MODE_LOCKDSA << 8)             /**< Shifted mode LOCKDSA for AGC_CTRL0          */
#define _AGC_CTRL0_RSSISHIFT_SHIFT                  11                                         /**< Shift value for AGC_RSSISHIFT               */
#define _AGC_CTRL0_RSSISHIFT_MASK                   0x7F800UL                                  /**< Bit mask for AGC_RSSISHIFT                  */
#define _AGC_CTRL0_RSSISHIFT_DEFAULT                0x0000004EUL                               /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_RSSISHIFT_DEFAULT                 (_AGC_CTRL0_RSSISHIFT_DEFAULT << 11)       /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_DISCFLOOPADJ                      (0x1UL << 19)                              /**< Disable gain adjustment by CFLOOP           */
#define _AGC_CTRL0_DISCFLOOPADJ_SHIFT               19                                         /**< Shift value for AGC_DISCFLOOPADJ            */
#define _AGC_CTRL0_DISCFLOOPADJ_MASK                0x80000UL                                  /**< Bit mask for AGC_DISCFLOOPADJ               */
#define _AGC_CTRL0_DISCFLOOPADJ_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_DISCFLOOPADJ_DEFAULT              (_AGC_CTRL0_DISCFLOOPADJ_DEFAULT << 19)    /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_CFLOOPNFADJ                       (0x1UL << 20)                              /**< Enable NF correction term in SL             */
#define _AGC_CTRL0_CFLOOPNFADJ_SHIFT                20                                         /**< Shift value for AGC_CFLOOPNFADJ             */
#define _AGC_CTRL0_CFLOOPNFADJ_MASK                 0x100000UL                                 /**< Bit mask for AGC_CFLOOPNFADJ                */
#define _AGC_CTRL0_CFLOOPNFADJ_DEFAULT              0x00000001UL                               /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_CFLOOPNFADJ_DEFAULT               (_AGC_CTRL0_CFLOOPNFADJ_DEFAULT << 20)     /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_CFLOOPNEWCALC                     (0x1UL << 21)                              /**< Enable new wanted gain calculation in SL    */
#define _AGC_CTRL0_CFLOOPNEWCALC_SHIFT              21                                         /**< Shift value for AGC_CFLOOPNEWCALC           */
#define _AGC_CTRL0_CFLOOPNEWCALC_MASK               0x200000UL                                 /**< Bit mask for AGC_CFLOOPNEWCALC              */
#define _AGC_CTRL0_CFLOOPNEWCALC_DEFAULT            0x00000001UL                               /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_CFLOOPNEWCALC_DEFAULT             (_AGC_CTRL0_CFLOOPNEWCALC_DEFAULT << 21)   /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_DISRESETCHPWR                     (0x1UL << 22)                              /**< Disable Reset of CHPWR                      */
#define _AGC_CTRL0_DISRESETCHPWR_SHIFT              22                                         /**< Shift value for AGC_DISRESETCHPWR           */
#define _AGC_CTRL0_DISRESETCHPWR_MASK               0x400000UL                                 /**< Bit mask for AGC_DISRESETCHPWR              */
#define _AGC_CTRL0_DISRESETCHPWR_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_DISRESETCHPWR_DEFAULT             (_AGC_CTRL0_DISRESETCHPWR_DEFAULT << 22)   /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_ADCATTENMODE                      (0x1UL << 23)                              /**< ADC Attenuator mode                         */
#define _AGC_CTRL0_ADCATTENMODE_SHIFT               23                                         /**< Shift value for AGC_ADCATTENMODE            */
#define _AGC_CTRL0_ADCATTENMODE_MASK                0x800000UL                                 /**< Bit mask for AGC_ADCATTENMODE               */
#define _AGC_CTRL0_ADCATTENMODE_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for AGC_CTRL0                  */
#define _AGC_CTRL0_ADCATTENMODE_DISABLE             0x00000000UL                               /**< Mode DISABLE for AGC_CTRL0                  */
#define _AGC_CTRL0_ADCATTENMODE_NOTMAXGAIN          0x00000001UL                               /**< Mode NOTMAXGAIN for AGC_CTRL0               */
#define AGC_CTRL0_ADCATTENMODE_DEFAULT              (_AGC_CTRL0_ADCATTENMODE_DEFAULT << 23)    /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_ADCATTENMODE_DISABLE              (_AGC_CTRL0_ADCATTENMODE_DISABLE << 23)    /**< Shifted mode DISABLE for AGC_CTRL0          */
#define AGC_CTRL0_ADCATTENMODE_NOTMAXGAIN           (_AGC_CTRL0_ADCATTENMODE_NOTMAXGAIN << 23) /**< Shifted mode NOTMAXGAIN for AGC_CTRL0       */
#define _AGC_CTRL0_ADCATTENCODE_SHIFT               25                                         /**< Shift value for AGC_ADCATTENCODE            */
#define _AGC_CTRL0_ADCATTENCODE_MASK                0x6000000UL                                /**< Bit mask for AGC_ADCATTENCODE               */
#define _AGC_CTRL0_ADCATTENCODE_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_ADCATTENCODE_DEFAULT              (_AGC_CTRL0_ADCATTENCODE_DEFAULT << 25)    /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_ENRSSIRESET                       (0x1UL << 27)                              /**< Enables reset of RSSI and CCA               */
#define _AGC_CTRL0_ENRSSIRESET_SHIFT                27                                         /**< Shift value for AGC_ENRSSIRESET             */
#define _AGC_CTRL0_ENRSSIRESET_MASK                 0x8000000UL                                /**< Bit mask for AGC_ENRSSIRESET                */
#define _AGC_CTRL0_ENRSSIRESET_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_ENRSSIRESET_DEFAULT               (_AGC_CTRL0_ENRSSIRESET_DEFAULT << 27)     /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_DSADISCFLOOP                      (0x1UL << 28)                              /**< Disable channel filter loop                 */
#define _AGC_CTRL0_DSADISCFLOOP_SHIFT               28                                         /**< Shift value for AGC_DSADISCFLOOP            */
#define _AGC_CTRL0_DSADISCFLOOP_MASK                0x10000000UL                               /**< Bit mask for AGC_DSADISCFLOOP               */
#define _AGC_CTRL0_DSADISCFLOOP_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_DSADISCFLOOP_DEFAULT              (_AGC_CTRL0_DSADISCFLOOP_DEFAULT << 28)    /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_DISPNGAINUP                       (0x1UL << 29)                              /**< Disable PN gain increase                    */
#define _AGC_CTRL0_DISPNGAINUP_SHIFT                29                                         /**< Shift value for AGC_DISPNGAINUP             */
#define _AGC_CTRL0_DISPNGAINUP_MASK                 0x20000000UL                               /**< Bit mask for AGC_DISPNGAINUP                */
#define _AGC_CTRL0_DISPNGAINUP_DEFAULT              0x00000001UL                               /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_DISPNGAINUP_DEFAULT               (_AGC_CTRL0_DISPNGAINUP_DEFAULT << 29)     /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_DISPNDWNCOMP                      (0x1UL << 30)                              /**< Disable PN gain decrease compensation       */
#define _AGC_CTRL0_DISPNDWNCOMP_SHIFT               30                                         /**< Shift value for AGC_DISPNDWNCOMP            */
#define _AGC_CTRL0_DISPNDWNCOMP_MASK                0x40000000UL                               /**< Bit mask for AGC_DISPNDWNCOMP               */
#define _AGC_CTRL0_DISPNDWNCOMP_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_DISPNDWNCOMP_DEFAULT              (_AGC_CTRL0_DISPNDWNCOMP_DEFAULT << 30)    /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_AGCRST                            (0x1UL << 31)                              /**< AGC reset                                   */
#define _AGC_CTRL0_AGCRST_SHIFT                     31                                         /**< Shift value for AGC_AGCRST                  */
#define _AGC_CTRL0_AGCRST_MASK                      0x80000000UL                               /**< Bit mask for AGC_AGCRST                     */
#define _AGC_CTRL0_AGCRST_DEFAULT                   0x00000000UL                               /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_AGCRST_DEFAULT                    (_AGC_CTRL0_AGCRST_DEFAULT << 31)          /**< Shifted mode DEFAULT for AGC_CTRL0          */

/* Bit fields for AGC CTRL1 */
#define _AGC_CTRL1_RESETVALUE                       0x00001300UL                         /**< Default value for AGC_CTRL1                 */
#define _AGC_CTRL1_MASK                             0x00007FFFUL                         /**< Mask for AGC_CTRL1                          */
#define _AGC_CTRL1_CCATHRSH_SHIFT                   0                                    /**< Shift value for AGC_CCATHRSH                */
#define _AGC_CTRL1_CCATHRSH_MASK                    0xFFUL                               /**< Bit mask for AGC_CCATHRSH                   */
#define _AGC_CTRL1_CCATHRSH_DEFAULT                 0x00000000UL                         /**< Mode DEFAULT for AGC_CTRL1                  */
#define AGC_CTRL1_CCATHRSH_DEFAULT                  (_AGC_CTRL1_CCATHRSH_DEFAULT << 0)   /**< Shifted mode DEFAULT for AGC_CTRL1          */
#define _AGC_CTRL1_RSSIPERIOD_SHIFT                 8                                    /**< Shift value for AGC_RSSIPERIOD              */
#define _AGC_CTRL1_RSSIPERIOD_MASK                  0xF00UL                              /**< Bit mask for AGC_RSSIPERIOD                 */
#define _AGC_CTRL1_RSSIPERIOD_DEFAULT               0x00000003UL                         /**< Mode DEFAULT for AGC_CTRL1                  */
#define AGC_CTRL1_RSSIPERIOD_DEFAULT                (_AGC_CTRL1_RSSIPERIOD_DEFAULT << 8) /**< Shifted mode DEFAULT for AGC_CTRL1          */
#define _AGC_CTRL1_PWRPERIOD_SHIFT                  12                                   /**< Shift value for AGC_PWRPERIOD               */
#define _AGC_CTRL1_PWRPERIOD_MASK                   0x7000UL                             /**< Bit mask for AGC_PWRPERIOD                  */
#define _AGC_CTRL1_PWRPERIOD_DEFAULT                0x00000001UL                         /**< Mode DEFAULT for AGC_CTRL1                  */
#define AGC_CTRL1_PWRPERIOD_DEFAULT                 (_AGC_CTRL1_PWRPERIOD_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_CTRL1          */

/* Bit fields for AGC CTRL2 */
#define _AGC_CTRL2_RESETVALUE                       0x0000610AUL                                 /**< Default value for AGC_CTRL2                 */
#define _AGC_CTRL2_MASK                             0xFFFFFFFFUL                                 /**< Mask for AGC_CTRL2                          */
#define AGC_CTRL2_DMASEL                            (0x1UL << 0)                                 /**< DMA select                                  */
#define _AGC_CTRL2_DMASEL_SHIFT                     0                                            /**< Shift value for AGC_DMASEL                  */
#define _AGC_CTRL2_DMASEL_MASK                      0x1UL                                        /**< Bit mask for AGC_DMASEL                     */
#define _AGC_CTRL2_DMASEL_DEFAULT                   0x00000000UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define _AGC_CTRL2_DMASEL_RSSI                      0x00000000UL                                 /**< Mode RSSI for AGC_CTRL2                     */
#define _AGC_CTRL2_DMASEL_GAIN                      0x00000001UL                                 /**< Mode GAIN for AGC_CTRL2                     */
#define AGC_CTRL2_DMASEL_DEFAULT                    (_AGC_CTRL2_DMASEL_DEFAULT << 0)             /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define AGC_CTRL2_DMASEL_RSSI                       (_AGC_CTRL2_DMASEL_RSSI << 0)                /**< Shifted mode RSSI for AGC_CTRL2             */
#define AGC_CTRL2_DMASEL_GAIN                       (_AGC_CTRL2_DMASEL_GAIN << 0)                /**< Shifted mode GAIN for AGC_CTRL2             */
#define AGC_CTRL2_SAFEMODE                          (0x1UL << 1)                                 /**< AGC safe mode                               */
#define _AGC_CTRL2_SAFEMODE_SHIFT                   1                                            /**< Shift value for AGC_SAFEMODE                */
#define _AGC_CTRL2_SAFEMODE_MASK                    0x2UL                                        /**< Bit mask for AGC_SAFEMODE                   */
#define _AGC_CTRL2_SAFEMODE_DEFAULT                 0x00000001UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define AGC_CTRL2_SAFEMODE_DEFAULT                  (_AGC_CTRL2_SAFEMODE_DEFAULT << 1)           /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define _AGC_CTRL2_SAFEMODETHD_SHIFT                2                                            /**< Shift value for AGC_SAFEMODETHD             */
#define _AGC_CTRL2_SAFEMODETHD_MASK                 0x1CUL                                       /**< Bit mask for AGC_SAFEMODETHD                */
#define _AGC_CTRL2_SAFEMODETHD_DEFAULT              0x00000002UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define AGC_CTRL2_SAFEMODETHD_DEFAULT               (_AGC_CTRL2_SAFEMODETHD_DEFAULT << 2)        /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define _AGC_CTRL2_REHICNTTHD_SHIFT                 5                                            /**< Shift value for AGC_REHICNTTHD              */
#define _AGC_CTRL2_REHICNTTHD_MASK                  0x1FE0UL                                     /**< Bit mask for AGC_REHICNTTHD                 */
#define _AGC_CTRL2_REHICNTTHD_DEFAULT               0x00000008UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define AGC_CTRL2_REHICNTTHD_DEFAULT                (_AGC_CTRL2_REHICNTTHD_DEFAULT << 5)         /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define _AGC_CTRL2_RELOTHD_SHIFT                    13                                           /**< Shift value for AGC_RELOTHD                 */
#define _AGC_CTRL2_RELOTHD_MASK                     0xE000UL                                     /**< Bit mask for AGC_RELOTHD                    */
#define _AGC_CTRL2_RELOTHD_DEFAULT                  0x00000003UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define AGC_CTRL2_RELOTHD_DEFAULT                   (_AGC_CTRL2_RELOTHD_DEFAULT << 13)           /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define _AGC_CTRL2_RELBYCHPWR_SHIFT                 16                                           /**< Shift value for AGC_RELBYCHPWR              */
#define _AGC_CTRL2_RELBYCHPWR_MASK                  0x30000UL                                    /**< Bit mask for AGC_RELBYCHPWR                 */
#define _AGC_CTRL2_RELBYCHPWR_DEFAULT               0x00000000UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define _AGC_CTRL2_RELBYCHPWR_LO_CNT                0x00000000UL                                 /**< Mode LO_CNT for AGC_CTRL2                   */
#define _AGC_CTRL2_RELBYCHPWR_PWR                   0x00000001UL                                 /**< Mode PWR for AGC_CTRL2                      */
#define _AGC_CTRL2_RELBYCHPWR_LO_CNT_PWR            0x00000002UL                                 /**< Mode LO_CNT_PWR for AGC_CTRL2               */
#define _AGC_CTRL2_RELBYCHPWR_LO_CNT_AND_PWR        0x00000003UL                                 /**< Mode LO_CNT_AND_PWR for AGC_CTRL2           */
#define AGC_CTRL2_RELBYCHPWR_DEFAULT                (_AGC_CTRL2_RELBYCHPWR_DEFAULT << 16)        /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define AGC_CTRL2_RELBYCHPWR_LO_CNT                 (_AGC_CTRL2_RELBYCHPWR_LO_CNT << 16)         /**< Shifted mode LO_CNT for AGC_CTRL2           */
#define AGC_CTRL2_RELBYCHPWR_PWR                    (_AGC_CTRL2_RELBYCHPWR_PWR << 16)            /**< Shifted mode PWR for AGC_CTRL2              */
#define AGC_CTRL2_RELBYCHPWR_LO_CNT_PWR             (_AGC_CTRL2_RELBYCHPWR_LO_CNT_PWR << 16)     /**< Shifted mode LO_CNT_PWR for AGC_CTRL2       */
#define AGC_CTRL2_RELBYCHPWR_LO_CNT_AND_PWR         (_AGC_CTRL2_RELBYCHPWR_LO_CNT_AND_PWR << 16) /**< Shifted mode LO_CNT_AND_PWR for AGC_CTRL2   */
#define _AGC_CTRL2_RELTARGETPWR_SHIFT               18                                           /**< Shift value for AGC_RELTARGETPWR            */
#define _AGC_CTRL2_RELTARGETPWR_MASK                0x3FC0000UL                                  /**< Bit mask for AGC_RELTARGETPWR               */
#define _AGC_CTRL2_RELTARGETPWR_DEFAULT             0x00000000UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define AGC_CTRL2_RELTARGETPWR_DEFAULT              (_AGC_CTRL2_RELTARGETPWR_DEFAULT << 18)      /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define _AGC_CTRL2_RSSICCASUB_SHIFT                 26                                           /**< Shift value for AGC_RSSICCASUB              */
#define _AGC_CTRL2_RSSICCASUB_MASK                  0x1C000000UL                                 /**< Bit mask for AGC_RSSICCASUB                 */
#define _AGC_CTRL2_RSSICCASUB_DEFAULT               0x00000000UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define AGC_CTRL2_RSSICCASUB_DEFAULT                (_AGC_CTRL2_RSSICCASUB_DEFAULT << 26)        /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define AGC_CTRL2_DEBCNTRST                         (0x1UL << 29)                                /**< Debonce CNT Reset MODE                      */
#define _AGC_CTRL2_DEBCNTRST_SHIFT                  29                                           /**< Shift value for AGC_DEBCNTRST               */
#define _AGC_CTRL2_DEBCNTRST_MASK                   0x20000000UL                                 /**< Bit mask for AGC_DEBCNTRST                  */
#define _AGC_CTRL2_DEBCNTRST_DEFAULT                0x00000000UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define AGC_CTRL2_DEBCNTRST_DEFAULT                 (_AGC_CTRL2_DEBCNTRST_DEFAULT << 29)         /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define AGC_CTRL2_PRSDEBUGEN                        (0x1UL << 30)                                /**< PRS Debug Enable                            */
#define _AGC_CTRL2_PRSDEBUGEN_SHIFT                 30                                           /**< Shift value for AGC_PRSDEBUGEN              */
#define _AGC_CTRL2_PRSDEBUGEN_MASK                  0x40000000UL                                 /**< Bit mask for AGC_PRSDEBUGEN                 */
#define _AGC_CTRL2_PRSDEBUGEN_DEFAULT               0x00000000UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define AGC_CTRL2_PRSDEBUGEN_DEFAULT                (_AGC_CTRL2_PRSDEBUGEN_DEFAULT << 30)        /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define AGC_CTRL2_DISRFPKD                          (0x1UL << 31)                                /**< Disable RF PEAKDET                          */
#define _AGC_CTRL2_DISRFPKD_SHIFT                   31                                           /**< Shift value for AGC_DISRFPKD                */
#define _AGC_CTRL2_DISRFPKD_MASK                    0x80000000UL                                 /**< Bit mask for AGC_DISRFPKD                   */
#define _AGC_CTRL2_DISRFPKD_DEFAULT                 0x00000000UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define AGC_CTRL2_DISRFPKD_DEFAULT                  (_AGC_CTRL2_DISRFPKD_DEFAULT << 31)          /**< Shifted mode DEFAULT for AGC_CTRL2          */

/* Bit fields for AGC CTRL3 */
#define _AGC_CTRL3_RESETVALUE                       0x5140A800UL                           /**< Default value for AGC_CTRL3                 */
#define _AGC_CTRL3_MASK                             0xFFFFFFFFUL                           /**< Mask for AGC_CTRL3                          */
#define AGC_CTRL3_IFPKDDEB                          (0x1UL << 0)                           /**< IF PEAKDET debounce mode enable             */
#define _AGC_CTRL3_IFPKDDEB_SHIFT                   0                                      /**< Shift value for AGC_IFPKDDEB                */
#define _AGC_CTRL3_IFPKDDEB_MASK                    0x1UL                                  /**< Bit mask for AGC_IFPKDDEB                   */
#define _AGC_CTRL3_IFPKDDEB_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for AGC_CTRL3                  */
#define AGC_CTRL3_IFPKDDEB_DEFAULT                  (_AGC_CTRL3_IFPKDDEB_DEFAULT << 0)     /**< Shifted mode DEFAULT for AGC_CTRL3          */
#define _AGC_CTRL3_IFPKDDEBTHD_SHIFT                1                                      /**< Shift value for AGC_IFPKDDEBTHD             */
#define _AGC_CTRL3_IFPKDDEBTHD_MASK                 0x6UL                                  /**< Bit mask for AGC_IFPKDDEBTHD                */
#define _AGC_CTRL3_IFPKDDEBTHD_DEFAULT              0x00000000UL                           /**< Mode DEFAULT for AGC_CTRL3                  */
#define AGC_CTRL3_IFPKDDEBTHD_DEFAULT               (_AGC_CTRL3_IFPKDDEBTHD_DEFAULT << 1)  /**< Shifted mode DEFAULT for AGC_CTRL3          */
#define _AGC_CTRL3_IFPKDDEBPRD_SHIFT                3                                      /**< Shift value for AGC_IFPKDDEBPRD             */
#define _AGC_CTRL3_IFPKDDEBPRD_MASK                 0x1F8UL                                /**< Bit mask for AGC_IFPKDDEBPRD                */
#define _AGC_CTRL3_IFPKDDEBPRD_DEFAULT              0x00000000UL                           /**< Mode DEFAULT for AGC_CTRL3                  */
#define AGC_CTRL3_IFPKDDEBPRD_DEFAULT               (_AGC_CTRL3_IFPKDDEBPRD_DEFAULT << 3)  /**< Shifted mode DEFAULT for AGC_CTRL3          */
#define _AGC_CTRL3_IFPKDDEBRST_SHIFT                9                                      /**< Shift value for AGC_IFPKDDEBRST             */
#define _AGC_CTRL3_IFPKDDEBRST_MASK                 0x1E00UL                               /**< Bit mask for AGC_IFPKDDEBRST                */
#define _AGC_CTRL3_IFPKDDEBRST_DEFAULT              0x00000004UL                           /**< Mode DEFAULT for AGC_CTRL3                  */
#define AGC_CTRL3_IFPKDDEBRST_DEFAULT               (_AGC_CTRL3_IFPKDDEBRST_DEFAULT << 9)  /**< Shifted mode DEFAULT for AGC_CTRL3          */
#define AGC_CTRL3_RFPKDDEB                          (0x1UL << 13)                          /**< RF PEAKDET debounce mode enable             */
#define _AGC_CTRL3_RFPKDDEB_SHIFT                   13                                     /**< Shift value for AGC_RFPKDDEB                */
#define _AGC_CTRL3_RFPKDDEB_MASK                    0x2000UL                               /**< Bit mask for AGC_RFPKDDEB                   */
#define _AGC_CTRL3_RFPKDDEB_DEFAULT                 0x00000001UL                           /**< Mode DEFAULT for AGC_CTRL3                  */
#define AGC_CTRL3_RFPKDDEB_DEFAULT                  (_AGC_CTRL3_RFPKDDEB_DEFAULT << 13)    /**< Shifted mode DEFAULT for AGC_CTRL3          */
#define _AGC_CTRL3_RFPKDDEBTHD_SHIFT                14                                     /**< Shift value for AGC_RFPKDDEBTHD             */
#define _AGC_CTRL3_RFPKDDEBTHD_MASK                 0x7C000UL                              /**< Bit mask for AGC_RFPKDDEBTHD                */
#define _AGC_CTRL3_RFPKDDEBTHD_DEFAULT              0x00000002UL                           /**< Mode DEFAULT for AGC_CTRL3                  */
#define AGC_CTRL3_RFPKDDEBTHD_DEFAULT               (_AGC_CTRL3_RFPKDDEBTHD_DEFAULT << 14) /**< Shifted mode DEFAULT for AGC_CTRL3          */
#define _AGC_CTRL3_RFPKDDEBPRD_SHIFT                19                                     /**< Shift value for AGC_RFPKDDEBPRD             */
#define _AGC_CTRL3_RFPKDDEBPRD_MASK                 0x7F80000UL                            /**< Bit mask for AGC_RFPKDDEBPRD                */
#define _AGC_CTRL3_RFPKDDEBPRD_DEFAULT              0x00000028UL                           /**< Mode DEFAULT for AGC_CTRL3                  */
#define AGC_CTRL3_RFPKDDEBPRD_DEFAULT               (_AGC_CTRL3_RFPKDDEBPRD_DEFAULT << 19) /**< Shifted mode DEFAULT for AGC_CTRL3          */
#define _AGC_CTRL3_RFPKDDEBRST_SHIFT                27                                     /**< Shift value for AGC_RFPKDDEBRST             */
#define _AGC_CTRL3_RFPKDDEBRST_MASK                 0xF8000000UL                           /**< Bit mask for AGC_RFPKDDEBRST                */
#define _AGC_CTRL3_RFPKDDEBRST_DEFAULT              0x0000000AUL                           /**< Mode DEFAULT for AGC_CTRL3                  */
#define AGC_CTRL3_RFPKDDEBRST_DEFAULT               (_AGC_CTRL3_RFPKDDEBRST_DEFAULT << 27) /**< Shifted mode DEFAULT for AGC_CTRL3          */

/* Bit fields for AGC CTRL4 */
#define _AGC_CTRL4_RESETVALUE                       0x0000000EUL                            /**< Default value for AGC_CTRL4                 */
#define _AGC_CTRL4_MASK                             0xFE00FFFFUL                            /**< Mask for AGC_CTRL4                          */
#define _AGC_CTRL4_PERIODRFPKD_SHIFT                0                                       /**< Shift value for AGC_PERIODRFPKD             */
#define _AGC_CTRL4_PERIODRFPKD_MASK                 0xFFFFUL                                /**< Bit mask for AGC_PERIODRFPKD                */
#define _AGC_CTRL4_PERIODRFPKD_DEFAULT              0x0000000EUL                            /**< Mode DEFAULT for AGC_CTRL4                  */
#define AGC_CTRL4_PERIODRFPKD_DEFAULT               (_AGC_CTRL4_PERIODRFPKD_DEFAULT << 0)   /**< Shifted mode DEFAULT for AGC_CTRL4          */
#define _AGC_CTRL4_RFPKDPRDGEAR_SHIFT               25                                      /**< Shift value for AGC_RFPKDPRDGEAR            */
#define _AGC_CTRL4_RFPKDPRDGEAR_MASK                0xE000000UL                             /**< Bit mask for AGC_RFPKDPRDGEAR               */
#define _AGC_CTRL4_RFPKDPRDGEAR_DEFAULT             0x00000000UL                            /**< Mode DEFAULT for AGC_CTRL4                  */
#define AGC_CTRL4_RFPKDPRDGEAR_DEFAULT              (_AGC_CTRL4_RFPKDPRDGEAR_DEFAULT << 25) /**< Shifted mode DEFAULT for AGC_CTRL4          */
#define AGC_CTRL4_RFPKDSYNCSEL                      (0x1UL << 28)                           /**< SYNC RF PKD OUTPUT SELECT                   */
#define _AGC_CTRL4_RFPKDSYNCSEL_SHIFT               28                                      /**< Shift value for AGC_RFPKDSYNCSEL            */
#define _AGC_CTRL4_RFPKDSYNCSEL_MASK                0x10000000UL                            /**< Bit mask for AGC_RFPKDSYNCSEL               */
#define _AGC_CTRL4_RFPKDSYNCSEL_DEFAULT             0x00000000UL                            /**< Mode DEFAULT for AGC_CTRL4                  */
#define AGC_CTRL4_RFPKDSYNCSEL_DEFAULT              (_AGC_CTRL4_RFPKDSYNCSEL_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_CTRL4          */
#define AGC_CTRL4_RFPKDSEL                          (0x1UL << 29)                           /**< RF PKD OUTPUT SELECT                        */
#define _AGC_CTRL4_RFPKDSEL_SHIFT                   29                                      /**< Shift value for AGC_RFPKDSEL                */
#define _AGC_CTRL4_RFPKDSEL_MASK                    0x20000000UL                            /**< Bit mask for AGC_RFPKDSEL                   */
#define _AGC_CTRL4_RFPKDSEL_DEFAULT                 0x00000000UL                            /**< Mode DEFAULT for AGC_CTRL4                  */
#define AGC_CTRL4_RFPKDSEL_DEFAULT                  (_AGC_CTRL4_RFPKDSEL_DEFAULT << 29)     /**< Shifted mode DEFAULT for AGC_CTRL4          */
#define AGC_CTRL4_FRZPKDEN                          (0x1UL << 30)                           /**< PKD Freeze Enable                           */
#define _AGC_CTRL4_FRZPKDEN_SHIFT                   30                                      /**< Shift value for AGC_FRZPKDEN                */
#define _AGC_CTRL4_FRZPKDEN_MASK                    0x40000000UL                            /**< Bit mask for AGC_FRZPKDEN                   */
#define _AGC_CTRL4_FRZPKDEN_DEFAULT                 0x00000000UL                            /**< Mode DEFAULT for AGC_CTRL4                  */
#define AGC_CTRL4_FRZPKDEN_DEFAULT                  (_AGC_CTRL4_FRZPKDEN_DEFAULT << 30)     /**< Shifted mode DEFAULT for AGC_CTRL4          */
#define AGC_CTRL4_RFPKDCNTEN                        (0x1UL << 31)                           /**< Counter-based RFPKD Enable                  */
#define _AGC_CTRL4_RFPKDCNTEN_SHIFT                 31                                      /**< Shift value for AGC_RFPKDCNTEN              */
#define _AGC_CTRL4_RFPKDCNTEN_MASK                  0x80000000UL                            /**< Bit mask for AGC_RFPKDCNTEN                 */
#define _AGC_CTRL4_RFPKDCNTEN_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for AGC_CTRL4                  */
#define AGC_CTRL4_RFPKDCNTEN_DEFAULT                (_AGC_CTRL4_RFPKDCNTEN_DEFAULT << 31)   /**< Shifted mode DEFAULT for AGC_CTRL4          */

/* Bit fields for AGC CTRL5 */
#define _AGC_CTRL5_RESETVALUE                       0x00000000UL                            /**< Default value for AGC_CTRL5                 */
#define _AGC_CTRL5_MASK                             0xC0FFFFFFUL                            /**< Mask for AGC_CTRL5                          */
#define _AGC_CTRL5_PNUPDISTHD_SHIFT                 0                                       /**< Shift value for AGC_PNUPDISTHD              */
#define _AGC_CTRL5_PNUPDISTHD_MASK                  0xFFFUL                                 /**< Bit mask for AGC_PNUPDISTHD                 */
#define _AGC_CTRL5_PNUPDISTHD_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for AGC_CTRL5                  */
#define AGC_CTRL5_PNUPDISTHD_DEFAULT                (_AGC_CTRL5_PNUPDISTHD_DEFAULT << 0)    /**< Shifted mode DEFAULT for AGC_CTRL5          */
#define _AGC_CTRL5_PNUPRELTHD_SHIFT                 12                                      /**< Shift value for AGC_PNUPRELTHD              */
#define _AGC_CTRL5_PNUPRELTHD_MASK                  0xFFF000UL                              /**< Bit mask for AGC_PNUPRELTHD                 */
#define _AGC_CTRL5_PNUPRELTHD_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for AGC_CTRL5                  */
#define AGC_CTRL5_PNUPRELTHD_DEFAULT                (_AGC_CTRL5_PNUPRELTHD_DEFAULT << 12)   /**< Shifted mode DEFAULT for AGC_CTRL5          */
#define AGC_CTRL5_SEQPNUPALLOW                      (0x1UL << 30)                           /**< SEQ Set PN GAIN UP ALLOW                    */
#define _AGC_CTRL5_SEQPNUPALLOW_SHIFT               30                                      /**< Shift value for AGC_SEQPNUPALLOW            */
#define _AGC_CTRL5_SEQPNUPALLOW_MASK                0x40000000UL                            /**< Bit mask for AGC_SEQPNUPALLOW               */
#define _AGC_CTRL5_SEQPNUPALLOW_DEFAULT             0x00000000UL                            /**< Mode DEFAULT for AGC_CTRL5                  */
#define AGC_CTRL5_SEQPNUPALLOW_DEFAULT              (_AGC_CTRL5_SEQPNUPALLOW_DEFAULT << 30) /**< Shifted mode DEFAULT for AGC_CTRL5          */
#define AGC_CTRL5_SEQRFPKDEN                        (0x1UL << 31)                           /**< SEQ-based RFPKD Enable                      */
#define _AGC_CTRL5_SEQRFPKDEN_SHIFT                 31                                      /**< Shift value for AGC_SEQRFPKDEN              */
#define _AGC_CTRL5_SEQRFPKDEN_MASK                  0x80000000UL                            /**< Bit mask for AGC_SEQRFPKDEN                 */
#define _AGC_CTRL5_SEQRFPKDEN_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for AGC_CTRL5                  */
#define AGC_CTRL5_SEQRFPKDEN_DEFAULT                (_AGC_CTRL5_SEQRFPKDEN_DEFAULT << 31)   /**< Shifted mode DEFAULT for AGC_CTRL5          */

/* Bit fields for AGC CTRL6 */
#define _AGC_CTRL6_RESETVALUE                       0x0003AAA8UL                           /**< Default value for AGC_CTRL6                 */
#define _AGC_CTRL6_MASK                             0x7FFFFFFFUL                           /**< Mask for AGC_CTRL6                          */
#define _AGC_CTRL6_DUALRFPKDDEC_SHIFT               0                                      /**< Shift value for AGC_DUALRFPKDDEC            */
#define _AGC_CTRL6_DUALRFPKDDEC_MASK                0x3FFFFUL                              /**< Bit mask for AGC_DUALRFPKDDEC               */
#define _AGC_CTRL6_DUALRFPKDDEC_DEFAULT             0x0003AAA8UL                           /**< Mode DEFAULT for AGC_CTRL6                  */
#define AGC_CTRL6_DUALRFPKDDEC_DEFAULT              (_AGC_CTRL6_DUALRFPKDDEC_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_CTRL6          */
#define AGC_CTRL6_ENDUALRFPKD                       (0x1UL << 18)                          /**< Enable dual RFPKD                           */
#define _AGC_CTRL6_ENDUALRFPKD_SHIFT                18                                     /**< Shift value for AGC_ENDUALRFPKD             */
#define _AGC_CTRL6_ENDUALRFPKD_MASK                 0x40000UL                              /**< Bit mask for AGC_ENDUALRFPKD                */
#define _AGC_CTRL6_ENDUALRFPKD_DEFAULT              0x00000000UL                           /**< Mode DEFAULT for AGC_CTRL6                  */
#define AGC_CTRL6_ENDUALRFPKD_DEFAULT               (_AGC_CTRL6_ENDUALRFPKD_DEFAULT << 18) /**< Shifted mode DEFAULT for AGC_CTRL6          */
#define _AGC_CTRL6_GAINDETTHD_SHIFT                 19                                     /**< Shift value for AGC_GAINDETTHD              */
#define _AGC_CTRL6_GAINDETTHD_MASK                  0x7FF80000UL                           /**< Bit mask for AGC_GAINDETTHD                 */
#define _AGC_CTRL6_GAINDETTHD_DEFAULT               0x00000000UL                           /**< Mode DEFAULT for AGC_CTRL6                  */
#define AGC_CTRL6_GAINDETTHD_DEFAULT                (_AGC_CTRL6_GAINDETTHD_DEFAULT << 19)  /**< Shifted mode DEFAULT for AGC_CTRL6          */

/* Bit fields for AGC CTRL7 */
#define _AGC_CTRL7_RESETVALUE                       0x00000000UL                         /**< Default value for AGC_CTRL7                 */
#define _AGC_CTRL7_MASK                             0x01FFFFFFUL                         /**< Mask for AGC_CTRL7                          */
#define _AGC_CTRL7_SUBDEN_SHIFT                     0                                    /**< Shift value for AGC_SUBDEN                  */
#define _AGC_CTRL7_SUBDEN_MASK                      0xFFUL                               /**< Bit mask for AGC_SUBDEN                     */
#define _AGC_CTRL7_SUBDEN_DEFAULT                   0x00000000UL                         /**< Mode DEFAULT for AGC_CTRL7                  */
#define AGC_CTRL7_SUBDEN_DEFAULT                    (_AGC_CTRL7_SUBDEN_DEFAULT << 0)     /**< Shifted mode DEFAULT for AGC_CTRL7          */
#define _AGC_CTRL7_SUBINT_SHIFT                     8                                    /**< Shift value for AGC_SUBINT                  */
#define _AGC_CTRL7_SUBINT_MASK                      0xFF00UL                             /**< Bit mask for AGC_SUBINT                     */
#define _AGC_CTRL7_SUBINT_DEFAULT                   0x00000000UL                         /**< Mode DEFAULT for AGC_CTRL7                  */
#define AGC_CTRL7_SUBINT_DEFAULT                    (_AGC_CTRL7_SUBINT_DEFAULT << 8)     /**< Shifted mode DEFAULT for AGC_CTRL7          */
#define _AGC_CTRL7_SUBNUM_SHIFT                     16                                   /**< Shift value for AGC_SUBNUM                  */
#define _AGC_CTRL7_SUBNUM_MASK                      0xFF0000UL                           /**< Bit mask for AGC_SUBNUM                     */
#define _AGC_CTRL7_SUBNUM_DEFAULT                   0x00000000UL                         /**< Mode DEFAULT for AGC_CTRL7                  */
#define AGC_CTRL7_SUBNUM_DEFAULT                    (_AGC_CTRL7_SUBNUM_DEFAULT << 16)    /**< Shifted mode DEFAULT for AGC_CTRL7          */
#define AGC_CTRL7_SUBPERIOD                         (0x1UL << 24)                        /**< Subperiod                                   */
#define _AGC_CTRL7_SUBPERIOD_SHIFT                  24                                   /**< Shift value for AGC_SUBPERIOD               */
#define _AGC_CTRL7_SUBPERIOD_MASK                   0x1000000UL                          /**< Bit mask for AGC_SUBPERIOD                  */
#define _AGC_CTRL7_SUBPERIOD_DEFAULT                0x00000000UL                         /**< Mode DEFAULT for AGC_CTRL7                  */
#define AGC_CTRL7_SUBPERIOD_DEFAULT                 (_AGC_CTRL7_SUBPERIOD_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_CTRL7          */

/* Bit fields for AGC RSSISTEPTHR */
#define _AGC_RSSISTEPTHR_RESETVALUE                 0x00000000UL                                     /**< Default value for AGC_RSSISTEPTHR           */
#define _AGC_RSSISTEPTHR_MASK                       0x3FFFFFFFUL                                     /**< Mask for AGC_RSSISTEPTHR                    */
#define _AGC_RSSISTEPTHR_POSSTEPTHR_SHIFT           0                                                /**< Shift value for AGC_POSSTEPTHR              */
#define _AGC_RSSISTEPTHR_POSSTEPTHR_MASK            0xFFUL                                           /**< Bit mask for AGC_POSSTEPTHR                 */
#define _AGC_RSSISTEPTHR_POSSTEPTHR_DEFAULT         0x00000000UL                                     /**< Mode DEFAULT for AGC_RSSISTEPTHR            */
#define AGC_RSSISTEPTHR_POSSTEPTHR_DEFAULT          (_AGC_RSSISTEPTHR_POSSTEPTHR_DEFAULT << 0)       /**< Shifted mode DEFAULT for AGC_RSSISTEPTHR    */
#define _AGC_RSSISTEPTHR_NEGSTEPTHR_SHIFT           8                                                /**< Shift value for AGC_NEGSTEPTHR              */
#define _AGC_RSSISTEPTHR_NEGSTEPTHR_MASK            0xFF00UL                                         /**< Bit mask for AGC_NEGSTEPTHR                 */
#define _AGC_RSSISTEPTHR_NEGSTEPTHR_DEFAULT         0x00000000UL                                     /**< Mode DEFAULT for AGC_RSSISTEPTHR            */
#define AGC_RSSISTEPTHR_NEGSTEPTHR_DEFAULT          (_AGC_RSSISTEPTHR_NEGSTEPTHR_DEFAULT << 8)       /**< Shifted mode DEFAULT for AGC_RSSISTEPTHR    */
#define AGC_RSSISTEPTHR_STEPPER                     (0x1UL << 16)                                    /**< Step Period                                 */
#define _AGC_RSSISTEPTHR_STEPPER_SHIFT              16                                               /**< Shift value for AGC_STEPPER                 */
#define _AGC_RSSISTEPTHR_STEPPER_MASK               0x10000UL                                        /**< Bit mask for AGC_STEPPER                    */
#define _AGC_RSSISTEPTHR_STEPPER_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for AGC_RSSISTEPTHR            */
#define AGC_RSSISTEPTHR_STEPPER_DEFAULT             (_AGC_RSSISTEPTHR_STEPPER_DEFAULT << 16)         /**< Shifted mode DEFAULT for AGC_RSSISTEPTHR    */
#define _AGC_RSSISTEPTHR_DEMODRESTARTPER_SHIFT      17                                               /**< Shift value for AGC_DEMODRESTARTPER         */
#define _AGC_RSSISTEPTHR_DEMODRESTARTPER_MASK       0x1E0000UL                                       /**< Bit mask for AGC_DEMODRESTARTPER            */
#define _AGC_RSSISTEPTHR_DEMODRESTARTPER_DEFAULT    0x00000000UL                                     /**< Mode DEFAULT for AGC_RSSISTEPTHR            */
#define AGC_RSSISTEPTHR_DEMODRESTARTPER_DEFAULT     (_AGC_RSSISTEPTHR_DEMODRESTARTPER_DEFAULT << 17) /**< Shifted mode DEFAULT for AGC_RSSISTEPTHR    */
#define _AGC_RSSISTEPTHR_DEMODRESTARTTHR_SHIFT      21                                               /**< Shift value for AGC_DEMODRESTARTTHR         */
#define _AGC_RSSISTEPTHR_DEMODRESTARTTHR_MASK       0x1FE00000UL                                     /**< Bit mask for AGC_DEMODRESTARTTHR            */
#define _AGC_RSSISTEPTHR_DEMODRESTARTTHR_DEFAULT    0x00000000UL                                     /**< Mode DEFAULT for AGC_RSSISTEPTHR            */
#define AGC_RSSISTEPTHR_DEMODRESTARTTHR_DEFAULT     (_AGC_RSSISTEPTHR_DEMODRESTARTTHR_DEFAULT << 21) /**< Shifted mode DEFAULT for AGC_RSSISTEPTHR    */
#define AGC_RSSISTEPTHR_RSSIFAST                    (0x1UL << 29)                                    /**< RSSI fast startup                           */
#define _AGC_RSSISTEPTHR_RSSIFAST_SHIFT             29                                               /**< Shift value for AGC_RSSIFAST                */
#define _AGC_RSSISTEPTHR_RSSIFAST_MASK              0x20000000UL                                     /**< Bit mask for AGC_RSSIFAST                   */
#define _AGC_RSSISTEPTHR_RSSIFAST_DEFAULT           0x00000000UL                                     /**< Mode DEFAULT for AGC_RSSISTEPTHR            */
#define AGC_RSSISTEPTHR_RSSIFAST_DEFAULT            (_AGC_RSSISTEPTHR_RSSIFAST_DEFAULT << 29)        /**< Shifted mode DEFAULT for AGC_RSSISTEPTHR    */

/* Bit fields for AGC IF */
#define _AGC_IF_RESETVALUE                          0x00000000UL                             /**< Default value for AGC_IF                    */
#define _AGC_IF_MASK                                0x00007F7DUL                             /**< Mask for AGC_IF                             */
#define AGC_IF_RSSIVALID                            (0x1UL << 0)                             /**< RSSI Value is Valid                         */
#define _AGC_IF_RSSIVALID_SHIFT                     0                                        /**< Shift value for AGC_RSSIVALID               */
#define _AGC_IF_RSSIVALID_MASK                      0x1UL                                    /**< Bit mask for AGC_RSSIVALID                  */
#define _AGC_IF_RSSIVALID_DEFAULT                   0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_RSSIVALID_DEFAULT                    (_AGC_IF_RSSIVALID_DEFAULT << 0)         /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_CCA                                  (0x1UL << 2)                             /**< Clear Channel Assessment                    */
#define _AGC_IF_CCA_SHIFT                           2                                        /**< Shift value for AGC_CCA                     */
#define _AGC_IF_CCA_MASK                            0x4UL                                    /**< Bit mask for AGC_CCA                        */
#define _AGC_IF_CCA_DEFAULT                         0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_CCA_DEFAULT                          (_AGC_IF_CCA_DEFAULT << 2)               /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_RSSIPOSSTEP                          (0x1UL << 3)                             /**< Positive RSSI Step Detected                 */
#define _AGC_IF_RSSIPOSSTEP_SHIFT                   3                                        /**< Shift value for AGC_RSSIPOSSTEP             */
#define _AGC_IF_RSSIPOSSTEP_MASK                    0x8UL                                    /**< Bit mask for AGC_RSSIPOSSTEP                */
#define _AGC_IF_RSSIPOSSTEP_DEFAULT                 0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_RSSIPOSSTEP_DEFAULT                  (_AGC_IF_RSSIPOSSTEP_DEFAULT << 3)       /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_RSSINEGSTEP                          (0x1UL << 4)                             /**< Negative RSSI Step Detected                 */
#define _AGC_IF_RSSINEGSTEP_SHIFT                   4                                        /**< Shift value for AGC_RSSINEGSTEP             */
#define _AGC_IF_RSSINEGSTEP_MASK                    0x10UL                                   /**< Bit mask for AGC_RSSINEGSTEP                */
#define _AGC_IF_RSSINEGSTEP_DEFAULT                 0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_RSSINEGSTEP_DEFAULT                  (_AGC_IF_RSSINEGSTEP_DEFAULT << 4)       /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_SHORTRSSIPOSSTEP                     (0x1UL << 6)                             /**< Short-term Positive RSSI Step Detected      */
#define _AGC_IF_SHORTRSSIPOSSTEP_SHIFT              6                                        /**< Shift value for AGC_SHORTRSSIPOSSTEP        */
#define _AGC_IF_SHORTRSSIPOSSTEP_MASK               0x40UL                                   /**< Bit mask for AGC_SHORTRSSIPOSSTEP           */
#define _AGC_IF_SHORTRSSIPOSSTEP_DEFAULT            0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_SHORTRSSIPOSSTEP_DEFAULT             (_AGC_IF_SHORTRSSIPOSSTEP_DEFAULT << 6)  /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_RFPKDPRDDONE                         (0x1UL << 8)                             /**< RF PKD PERIOD CNT TOMEOUT                   */
#define _AGC_IF_RFPKDPRDDONE_SHIFT                  8                                        /**< Shift value for AGC_RFPKDPRDDONE            */
#define _AGC_IF_RFPKDPRDDONE_MASK                   0x100UL                                  /**< Bit mask for AGC_RFPKDPRDDONE               */
#define _AGC_IF_RFPKDPRDDONE_DEFAULT                0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_RFPKDPRDDONE_DEFAULT                 (_AGC_IF_RFPKDPRDDONE_DEFAULT << 8)      /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_RFPKDCNTDONE                         (0x1UL << 9)                             /**< RF PKD pulse CNT TOMEOUT                    */
#define _AGC_IF_RFPKDCNTDONE_SHIFT                  9                                        /**< Shift value for AGC_RFPKDCNTDONE            */
#define _AGC_IF_RFPKDCNTDONE_MASK                   0x200UL                                  /**< Bit mask for AGC_RFPKDCNTDONE               */
#define _AGC_IF_RFPKDCNTDONE_DEFAULT                0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_RFPKDCNTDONE_DEFAULT                 (_AGC_IF_RFPKDCNTDONE_DEFAULT << 9)      /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_RSSIHIGH                             (0x1UL << 10)                            /**< RSSI high detected                          */
#define _AGC_IF_RSSIHIGH_SHIFT                      10                                       /**< Shift value for AGC_RSSIHIGH                */
#define _AGC_IF_RSSIHIGH_MASK                       0x400UL                                  /**< Bit mask for AGC_RSSIHIGH                   */
#define _AGC_IF_RSSIHIGH_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_RSSIHIGH_DEFAULT                     (_AGC_IF_RSSIHIGH_DEFAULT << 10)         /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_RSSILOW                              (0x1UL << 11)                            /**< RSSI low detected                           */
#define _AGC_IF_RSSILOW_SHIFT                       11                                       /**< Shift value for AGC_RSSILOW                 */
#define _AGC_IF_RSSILOW_MASK                        0x800UL                                  /**< Bit mask for AGC_RSSILOW                    */
#define _AGC_IF_RSSILOW_DEFAULT                     0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_RSSILOW_DEFAULT                      (_AGC_IF_RSSILOW_DEFAULT << 11)          /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_CCANODET                             (0x1UL << 12)                            /**< CCA Not Detected                            */
#define _AGC_IF_CCANODET_SHIFT                      12                                       /**< Shift value for AGC_CCANODET                */
#define _AGC_IF_CCANODET_MASK                       0x1000UL                                 /**< Bit mask for AGC_CCANODET                   */
#define _AGC_IF_CCANODET_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_CCANODET_DEFAULT                     (_AGC_IF_CCANODET_DEFAULT << 12)         /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_GAINBELOWGAINTHD                     (0x1UL << 13)                            /**< agc gain above threshold int                */
#define _AGC_IF_GAINBELOWGAINTHD_SHIFT              13                                       /**< Shift value for AGC_GAINBELOWGAINTHD        */
#define _AGC_IF_GAINBELOWGAINTHD_MASK               0x2000UL                                 /**< Bit mask for AGC_GAINBELOWGAINTHD           */
#define _AGC_IF_GAINBELOWGAINTHD_DEFAULT            0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_GAINBELOWGAINTHD_DEFAULT             (_AGC_IF_GAINBELOWGAINTHD_DEFAULT << 13) /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_GAINUPDATEFRZ                        (0x1UL << 14)                            /**< AGC gain update frozen int                  */
#define _AGC_IF_GAINUPDATEFRZ_SHIFT                 14                                       /**< Shift value for AGC_GAINUPDATEFRZ           */
#define _AGC_IF_GAINUPDATEFRZ_MASK                  0x4000UL                                 /**< Bit mask for AGC_GAINUPDATEFRZ              */
#define _AGC_IF_GAINUPDATEFRZ_DEFAULT               0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_GAINUPDATEFRZ_DEFAULT                (_AGC_IF_GAINUPDATEFRZ_DEFAULT << 14)    /**< Shifted mode DEFAULT for AGC_IF             */

/* Bit fields for AGC IEN */
#define _AGC_IEN_RESETVALUE                         0x00000000UL                              /**< Default value for AGC_IEN                   */
#define _AGC_IEN_MASK                               0x00007F7DUL                              /**< Mask for AGC_IEN                            */
#define AGC_IEN_RSSIVALID                           (0x1UL << 0)                              /**< RSSIVALID Interrupt Enable                  */
#define _AGC_IEN_RSSIVALID_SHIFT                    0                                         /**< Shift value for AGC_RSSIVALID               */
#define _AGC_IEN_RSSIVALID_MASK                     0x1UL                                     /**< Bit mask for AGC_RSSIVALID                  */
#define _AGC_IEN_RSSIVALID_DEFAULT                  0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_RSSIVALID_DEFAULT                   (_AGC_IEN_RSSIVALID_DEFAULT << 0)         /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_CCA                                 (0x1UL << 2)                              /**< CCA Interrupt Enable                        */
#define _AGC_IEN_CCA_SHIFT                          2                                         /**< Shift value for AGC_CCA                     */
#define _AGC_IEN_CCA_MASK                           0x4UL                                     /**< Bit mask for AGC_CCA                        */
#define _AGC_IEN_CCA_DEFAULT                        0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_CCA_DEFAULT                         (_AGC_IEN_CCA_DEFAULT << 2)               /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_RSSIPOSSTEP                         (0x1UL << 3)                              /**< RSSIPOSSTEP Interrupt Enable                */
#define _AGC_IEN_RSSIPOSSTEP_SHIFT                  3                                         /**< Shift value for AGC_RSSIPOSSTEP             */
#define _AGC_IEN_RSSIPOSSTEP_MASK                   0x8UL                                     /**< Bit mask for AGC_RSSIPOSSTEP                */
#define _AGC_IEN_RSSIPOSSTEP_DEFAULT                0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_RSSIPOSSTEP_DEFAULT                 (_AGC_IEN_RSSIPOSSTEP_DEFAULT << 3)       /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_RSSINEGSTEP                         (0x1UL << 4)                              /**< RSSINEGSTEP Interrupt Enable                */
#define _AGC_IEN_RSSINEGSTEP_SHIFT                  4                                         /**< Shift value for AGC_RSSINEGSTEP             */
#define _AGC_IEN_RSSINEGSTEP_MASK                   0x10UL                                    /**< Bit mask for AGC_RSSINEGSTEP                */
#define _AGC_IEN_RSSINEGSTEP_DEFAULT                0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_RSSINEGSTEP_DEFAULT                 (_AGC_IEN_RSSINEGSTEP_DEFAULT << 4)       /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_SHORTRSSIPOSSTEP                    (0x1UL << 6)                              /**< SHORTRSSIPOSSTEP Interrupt Enable           */
#define _AGC_IEN_SHORTRSSIPOSSTEP_SHIFT             6                                         /**< Shift value for AGC_SHORTRSSIPOSSTEP        */
#define _AGC_IEN_SHORTRSSIPOSSTEP_MASK              0x40UL                                    /**< Bit mask for AGC_SHORTRSSIPOSSTEP           */
#define _AGC_IEN_SHORTRSSIPOSSTEP_DEFAULT           0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_SHORTRSSIPOSSTEP_DEFAULT            (_AGC_IEN_SHORTRSSIPOSSTEP_DEFAULT << 6)  /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_RFPKDPRDDONE                        (0x1UL << 8)                              /**< RF PKD PERIOD CNT Interrupt Enable          */
#define _AGC_IEN_RFPKDPRDDONE_SHIFT                 8                                         /**< Shift value for AGC_RFPKDPRDDONE            */
#define _AGC_IEN_RFPKDPRDDONE_MASK                  0x100UL                                   /**< Bit mask for AGC_RFPKDPRDDONE               */
#define _AGC_IEN_RFPKDPRDDONE_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_RFPKDPRDDONE_DEFAULT                (_AGC_IEN_RFPKDPRDDONE_DEFAULT << 8)      /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_RFPKDCNTDONE                        (0x1UL << 9)                              /**< RF PKD pulse CNT Interrupt Enable           */
#define _AGC_IEN_RFPKDCNTDONE_SHIFT                 9                                         /**< Shift value for AGC_RFPKDCNTDONE            */
#define _AGC_IEN_RFPKDCNTDONE_MASK                  0x200UL                                   /**< Bit mask for AGC_RFPKDCNTDONE               */
#define _AGC_IEN_RFPKDCNTDONE_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_RFPKDCNTDONE_DEFAULT                (_AGC_IEN_RFPKDCNTDONE_DEFAULT << 9)      /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_RSSIHIGH                            (0x1UL << 10)                             /**< RSSIHIGH Interrupt Enable                   */
#define _AGC_IEN_RSSIHIGH_SHIFT                     10                                        /**< Shift value for AGC_RSSIHIGH                */
#define _AGC_IEN_RSSIHIGH_MASK                      0x400UL                                   /**< Bit mask for AGC_RSSIHIGH                   */
#define _AGC_IEN_RSSIHIGH_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_RSSIHIGH_DEFAULT                    (_AGC_IEN_RSSIHIGH_DEFAULT << 10)         /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_RSSILOW                             (0x1UL << 11)                             /**< RSSILOW Interrupt Enable                    */
#define _AGC_IEN_RSSILOW_SHIFT                      11                                        /**< Shift value for AGC_RSSILOW                 */
#define _AGC_IEN_RSSILOW_MASK                       0x800UL                                   /**< Bit mask for AGC_RSSILOW                    */
#define _AGC_IEN_RSSILOW_DEFAULT                    0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_RSSILOW_DEFAULT                     (_AGC_IEN_RSSILOW_DEFAULT << 11)          /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_CCANODET                            (0x1UL << 12)                             /**< CCANODET Interrupt Enable                   */
#define _AGC_IEN_CCANODET_SHIFT                     12                                        /**< Shift value for AGC_CCANODET                */
#define _AGC_IEN_CCANODET_MASK                      0x1000UL                                  /**< Bit mask for AGC_CCANODET                   */
#define _AGC_IEN_CCANODET_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_CCANODET_DEFAULT                    (_AGC_IEN_CCANODET_DEFAULT << 12)         /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_GAINBELOWGAINTHD                    (0x1UL << 13)                             /**< GAINBELOWGAINTHD Interrupt Enable           */
#define _AGC_IEN_GAINBELOWGAINTHD_SHIFT             13                                        /**< Shift value for AGC_GAINBELOWGAINTHD        */
#define _AGC_IEN_GAINBELOWGAINTHD_MASK              0x2000UL                                  /**< Bit mask for AGC_GAINBELOWGAINTHD           */
#define _AGC_IEN_GAINBELOWGAINTHD_DEFAULT           0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_GAINBELOWGAINTHD_DEFAULT            (_AGC_IEN_GAINBELOWGAINTHD_DEFAULT << 13) /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_GAINUPDATEFRZ                       (0x1UL << 14)                             /**< AGC gain update frozen int Enable           */
#define _AGC_IEN_GAINUPDATEFRZ_SHIFT                14                                        /**< Shift value for AGC_GAINUPDATEFRZ           */
#define _AGC_IEN_GAINUPDATEFRZ_MASK                 0x4000UL                                  /**< Bit mask for AGC_GAINUPDATEFRZ              */
#define _AGC_IEN_GAINUPDATEFRZ_DEFAULT              0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_GAINUPDATEFRZ_DEFAULT               (_AGC_IEN_GAINUPDATEFRZ_DEFAULT << 14)    /**< Shifted mode DEFAULT for AGC_IEN            */

/* Bit fields for AGC GAINRANGE */
#define _AGC_GAINRANGE_RESETVALUE                   0x00813187UL                                 /**< Default value for AGC_GAINRANGE             */
#define _AGC_GAINRANGE_MASK                         0x03FFFFFFUL                                 /**< Mask for AGC_GAINRANGE                      */
#define _AGC_GAINRANGE_LNAINDEXBORDER_SHIFT         0                                            /**< Shift value for AGC_LNAINDEXBORDER          */
#define _AGC_GAINRANGE_LNAINDEXBORDER_MASK          0xFUL                                        /**< Bit mask for AGC_LNAINDEXBORDER             */
#define _AGC_GAINRANGE_LNAINDEXBORDER_DEFAULT       0x00000007UL                                 /**< Mode DEFAULT for AGC_GAINRANGE              */
#define AGC_GAINRANGE_LNAINDEXBORDER_DEFAULT        (_AGC_GAINRANGE_LNAINDEXBORDER_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_GAINRANGE      */
#define _AGC_GAINRANGE_PGAINDEXBORDER_SHIFT         4                                            /**< Shift value for AGC_PGAINDEXBORDER          */
#define _AGC_GAINRANGE_PGAINDEXBORDER_MASK          0xF0UL                                       /**< Bit mask for AGC_PGAINDEXBORDER             */
#define _AGC_GAINRANGE_PGAINDEXBORDER_DEFAULT       0x00000008UL                                 /**< Mode DEFAULT for AGC_GAINRANGE              */
#define AGC_GAINRANGE_PGAINDEXBORDER_DEFAULT        (_AGC_GAINRANGE_PGAINDEXBORDER_DEFAULT << 4) /**< Shifted mode DEFAULT for AGC_GAINRANGE      */
#define _AGC_GAINRANGE_GAININCSTEP_SHIFT            8                                            /**< Shift value for AGC_GAININCSTEP             */
#define _AGC_GAINRANGE_GAININCSTEP_MASK             0xF00UL                                      /**< Bit mask for AGC_GAININCSTEP                */
#define _AGC_GAINRANGE_GAININCSTEP_DEFAULT          0x00000001UL                                 /**< Mode DEFAULT for AGC_GAINRANGE              */
#define AGC_GAINRANGE_GAININCSTEP_DEFAULT           (_AGC_GAINRANGE_GAININCSTEP_DEFAULT << 8)    /**< Shifted mode DEFAULT for AGC_GAINRANGE      */
#define _AGC_GAINRANGE_PNGAINSTEP_SHIFT             12                                           /**< Shift value for AGC_PNGAINSTEP              */
#define _AGC_GAINRANGE_PNGAINSTEP_MASK              0xF000UL                                     /**< Bit mask for AGC_PNGAINSTEP                 */
#define _AGC_GAINRANGE_PNGAINSTEP_DEFAULT           0x00000003UL                                 /**< Mode DEFAULT for AGC_GAINRANGE              */
#define AGC_GAINRANGE_PNGAINSTEP_DEFAULT            (_AGC_GAINRANGE_PNGAINSTEP_DEFAULT << 12)    /**< Shifted mode DEFAULT for AGC_GAINRANGE      */
#define _AGC_GAINRANGE_LATCHEDHISTEP_SHIFT          16                                           /**< Shift value for AGC_LATCHEDHISTEP           */
#define _AGC_GAINRANGE_LATCHEDHISTEP_MASK           0xF0000UL                                    /**< Bit mask for AGC_LATCHEDHISTEP              */
#define _AGC_GAINRANGE_LATCHEDHISTEP_DEFAULT        0x00000001UL                                 /**< Mode DEFAULT for AGC_GAINRANGE              */
#define AGC_GAINRANGE_LATCHEDHISTEP_DEFAULT         (_AGC_GAINRANGE_LATCHEDHISTEP_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_GAINRANGE      */
#define _AGC_GAINRANGE_HIPWRTHD_SHIFT               20                                           /**< Shift value for AGC_HIPWRTHD                */
#define _AGC_GAINRANGE_HIPWRTHD_MASK                0x3F00000UL                                  /**< Bit mask for AGC_HIPWRTHD                   */
#define _AGC_GAINRANGE_HIPWRTHD_DEFAULT             0x00000008UL                                 /**< Mode DEFAULT for AGC_GAINRANGE              */
#define AGC_GAINRANGE_HIPWRTHD_DEFAULT              (_AGC_GAINRANGE_HIPWRTHD_DEFAULT << 20)      /**< Shifted mode DEFAULT for AGC_GAINRANGE      */

/* Bit fields for AGC AGCPERIOD0 */
#define _AGC_AGCPERIOD0_RESETVALUE                  0xD607000EUL                                 /**< Default value for AGC_AGCPERIOD0            */
#define _AGC_AGCPERIOD0_MASK                        0xFFFF01FFUL                                 /**< Mask for AGC_AGCPERIOD0                     */
#define _AGC_AGCPERIOD0_PERIODHI_SHIFT              0                                            /**< Shift value for AGC_PERIODHI                */
#define _AGC_AGCPERIOD0_PERIODHI_MASK               0x1FFUL                                      /**< Bit mask for AGC_PERIODHI                   */
#define _AGC_AGCPERIOD0_PERIODHI_DEFAULT            0x0000000EUL                                 /**< Mode DEFAULT for AGC_AGCPERIOD0             */
#define AGC_AGCPERIOD0_PERIODHI_DEFAULT             (_AGC_AGCPERIOD0_PERIODHI_DEFAULT << 0)      /**< Shifted mode DEFAULT for AGC_AGCPERIOD0     */
#define _AGC_AGCPERIOD0_MAXHICNTTHD_SHIFT           16                                           /**< Shift value for AGC_MAXHICNTTHD             */
#define _AGC_AGCPERIOD0_MAXHICNTTHD_MASK            0xFF0000UL                                   /**< Bit mask for AGC_MAXHICNTTHD                */
#define _AGC_AGCPERIOD0_MAXHICNTTHD_DEFAULT         0x00000007UL                                 /**< Mode DEFAULT for AGC_AGCPERIOD0             */
#define AGC_AGCPERIOD0_MAXHICNTTHD_DEFAULT          (_AGC_AGCPERIOD0_MAXHICNTTHD_DEFAULT << 16)  /**< Shifted mode DEFAULT for AGC_AGCPERIOD0     */
#define _AGC_AGCPERIOD0_SETTLETIMEIF_SHIFT          24                                           /**< Shift value for AGC_SETTLETIMEIF            */
#define _AGC_AGCPERIOD0_SETTLETIMEIF_MASK           0xF000000UL                                  /**< Bit mask for AGC_SETTLETIMEIF               */
#define _AGC_AGCPERIOD0_SETTLETIMEIF_DEFAULT        0x00000006UL                                 /**< Mode DEFAULT for AGC_AGCPERIOD0             */
#define AGC_AGCPERIOD0_SETTLETIMEIF_DEFAULT         (_AGC_AGCPERIOD0_SETTLETIMEIF_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_AGCPERIOD0     */
#define _AGC_AGCPERIOD0_SETTLETIMERF_SHIFT          28                                           /**< Shift value for AGC_SETTLETIMERF            */
#define _AGC_AGCPERIOD0_SETTLETIMERF_MASK           0xF0000000UL                                 /**< Bit mask for AGC_SETTLETIMERF               */
#define _AGC_AGCPERIOD0_SETTLETIMERF_DEFAULT        0x0000000DUL                                 /**< Mode DEFAULT for AGC_AGCPERIOD0             */
#define AGC_AGCPERIOD0_SETTLETIMERF_DEFAULT         (_AGC_AGCPERIOD0_SETTLETIMERF_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_AGCPERIOD0     */

/* Bit fields for AGC AGCPERIOD1 */
#define _AGC_AGCPERIOD1_RESETVALUE                  0x00000037UL                             /**< Default value for AGC_AGCPERIOD1            */
#define _AGC_AGCPERIOD1_MASK                        0xFFFFFFFFUL                             /**< Mask for AGC_AGCPERIOD1                     */
#define _AGC_AGCPERIOD1_PERIODLOW_SHIFT             0                                        /**< Shift value for AGC_PERIODLOW               */
#define _AGC_AGCPERIOD1_PERIODLOW_MASK              0xFFFFFFFFUL                             /**< Bit mask for AGC_PERIODLOW                  */
#define _AGC_AGCPERIOD1_PERIODLOW_DEFAULT           0x00000037UL                             /**< Mode DEFAULT for AGC_AGCPERIOD1             */
#define AGC_AGCPERIOD1_PERIODLOW_DEFAULT            (_AGC_AGCPERIOD1_PERIODLOW_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_AGCPERIOD1     */

/* Bit fields for AGC HICNTREGION0 */
#define _AGC_HICNTREGION0_RESETVALUE                0x06050403UL                                   /**< Default value for AGC_HICNTREGION0          */
#define _AGC_HICNTREGION0_MASK                      0xFFFFFFFFUL                                   /**< Mask for AGC_HICNTREGION0                   */
#define _AGC_HICNTREGION0_HICNTREGION0_SHIFT        0                                              /**< Shift value for AGC_HICNTREGION0            */
#define _AGC_HICNTREGION0_HICNTREGION0_MASK         0xFFUL                                         /**< Bit mask for AGC_HICNTREGION0               */
#define _AGC_HICNTREGION0_HICNTREGION0_DEFAULT      0x00000003UL                                   /**< Mode DEFAULT for AGC_HICNTREGION0           */
#define AGC_HICNTREGION0_HICNTREGION0_DEFAULT       (_AGC_HICNTREGION0_HICNTREGION0_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_HICNTREGION0   */
#define _AGC_HICNTREGION0_HICNTREGION1_SHIFT        8                                              /**< Shift value for AGC_HICNTREGION1            */
#define _AGC_HICNTREGION0_HICNTREGION1_MASK         0xFF00UL                                       /**< Bit mask for AGC_HICNTREGION1               */
#define _AGC_HICNTREGION0_HICNTREGION1_DEFAULT      0x00000004UL                                   /**< Mode DEFAULT for AGC_HICNTREGION0           */
#define AGC_HICNTREGION0_HICNTREGION1_DEFAULT       (_AGC_HICNTREGION0_HICNTREGION1_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_HICNTREGION0   */
#define _AGC_HICNTREGION0_HICNTREGION2_SHIFT        16                                             /**< Shift value for AGC_HICNTREGION2            */
#define _AGC_HICNTREGION0_HICNTREGION2_MASK         0xFF0000UL                                     /**< Bit mask for AGC_HICNTREGION2               */
#define _AGC_HICNTREGION0_HICNTREGION2_DEFAULT      0x00000005UL                                   /**< Mode DEFAULT for AGC_HICNTREGION0           */
#define AGC_HICNTREGION0_HICNTREGION2_DEFAULT       (_AGC_HICNTREGION0_HICNTREGION2_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_HICNTREGION0   */
#define _AGC_HICNTREGION0_HICNTREGION3_SHIFT        24                                             /**< Shift value for AGC_HICNTREGION3            */
#define _AGC_HICNTREGION0_HICNTREGION3_MASK         0xFF000000UL                                   /**< Bit mask for AGC_HICNTREGION3               */
#define _AGC_HICNTREGION0_HICNTREGION3_DEFAULT      0x00000006UL                                   /**< Mode DEFAULT for AGC_HICNTREGION0           */
#define AGC_HICNTREGION0_HICNTREGION3_DEFAULT       (_AGC_HICNTREGION0_HICNTREGION3_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_HICNTREGION0   */

/* Bit fields for AGC HICNTREGION1 */
#define _AGC_HICNTREGION1_RESETVALUE                0x00000008UL                                  /**< Default value for AGC_HICNTREGION1          */
#define _AGC_HICNTREGION1_MASK                      0x000000FFUL                                  /**< Mask for AGC_HICNTREGION1                   */
#define _AGC_HICNTREGION1_HICNTREGION4_SHIFT        0                                             /**< Shift value for AGC_HICNTREGION4            */
#define _AGC_HICNTREGION1_HICNTREGION4_MASK         0xFFUL                                        /**< Bit mask for AGC_HICNTREGION4               */
#define _AGC_HICNTREGION1_HICNTREGION4_DEFAULT      0x00000008UL                                  /**< Mode DEFAULT for AGC_HICNTREGION1           */
#define AGC_HICNTREGION1_HICNTREGION4_DEFAULT       (_AGC_HICNTREGION1_HICNTREGION4_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_HICNTREGION1   */

/* Bit fields for AGC STEPDWN */
#define _AGC_STEPDWN_RESETVALUE                     0x00036D11UL                          /**< Default value for AGC_STEPDWN               */
#define _AGC_STEPDWN_MASK                           0x0003FFFFUL                          /**< Mask for AGC_STEPDWN                        */
#define _AGC_STEPDWN_STEPDWN0_SHIFT                 0                                     /**< Shift value for AGC_STEPDWN0                */
#define _AGC_STEPDWN_STEPDWN0_MASK                  0x7UL                                 /**< Bit mask for AGC_STEPDWN0                   */
#define _AGC_STEPDWN_STEPDWN0_DEFAULT               0x00000001UL                          /**< Mode DEFAULT for AGC_STEPDWN                */
#define AGC_STEPDWN_STEPDWN0_DEFAULT                (_AGC_STEPDWN_STEPDWN0_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_STEPDWN        */
#define _AGC_STEPDWN_STEPDWN1_SHIFT                 3                                     /**< Shift value for AGC_STEPDWN1                */
#define _AGC_STEPDWN_STEPDWN1_MASK                  0x38UL                                /**< Bit mask for AGC_STEPDWN1                   */
#define _AGC_STEPDWN_STEPDWN1_DEFAULT               0x00000002UL                          /**< Mode DEFAULT for AGC_STEPDWN                */
#define AGC_STEPDWN_STEPDWN1_DEFAULT                (_AGC_STEPDWN_STEPDWN1_DEFAULT << 3)  /**< Shifted mode DEFAULT for AGC_STEPDWN        */
#define _AGC_STEPDWN_STEPDWN2_SHIFT                 6                                     /**< Shift value for AGC_STEPDWN2                */
#define _AGC_STEPDWN_STEPDWN2_MASK                  0x1C0UL                               /**< Bit mask for AGC_STEPDWN2                   */
#define _AGC_STEPDWN_STEPDWN2_DEFAULT               0x00000004UL                          /**< Mode DEFAULT for AGC_STEPDWN                */
#define AGC_STEPDWN_STEPDWN2_DEFAULT                (_AGC_STEPDWN_STEPDWN2_DEFAULT << 6)  /**< Shifted mode DEFAULT for AGC_STEPDWN        */
#define _AGC_STEPDWN_STEPDWN3_SHIFT                 9                                     /**< Shift value for AGC_STEPDWN3                */
#define _AGC_STEPDWN_STEPDWN3_MASK                  0xE00UL                               /**< Bit mask for AGC_STEPDWN3                   */
#define _AGC_STEPDWN_STEPDWN3_DEFAULT               0x00000006UL                          /**< Mode DEFAULT for AGC_STEPDWN                */
#define AGC_STEPDWN_STEPDWN3_DEFAULT                (_AGC_STEPDWN_STEPDWN3_DEFAULT << 9)  /**< Shifted mode DEFAULT for AGC_STEPDWN        */
#define _AGC_STEPDWN_STEPDWN4_SHIFT                 12                                    /**< Shift value for AGC_STEPDWN4                */
#define _AGC_STEPDWN_STEPDWN4_MASK                  0x7000UL                              /**< Bit mask for AGC_STEPDWN4                   */
#define _AGC_STEPDWN_STEPDWN4_DEFAULT               0x00000006UL                          /**< Mode DEFAULT for AGC_STEPDWN                */
#define AGC_STEPDWN_STEPDWN4_DEFAULT                (_AGC_STEPDWN_STEPDWN4_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_STEPDWN        */
#define _AGC_STEPDWN_STEPDWN5_SHIFT                 15                                    /**< Shift value for AGC_STEPDWN5                */
#define _AGC_STEPDWN_STEPDWN5_MASK                  0x38000UL                             /**< Bit mask for AGC_STEPDWN5                   */
#define _AGC_STEPDWN_STEPDWN5_DEFAULT               0x00000006UL                          /**< Mode DEFAULT for AGC_STEPDWN                */
#define AGC_STEPDWN_STEPDWN5_DEFAULT                (_AGC_STEPDWN_STEPDWN5_DEFAULT << 15) /**< Shifted mode DEFAULT for AGC_STEPDWN        */

/* Bit fields for AGC GAINSTEPLIM0 */
#define _AGC_GAINSTEPLIM0_RESETVALUE                0x00003144UL                                   /**< Default value for AGC_GAINSTEPLIM0          */
#define _AGC_GAINSTEPLIM0_MASK                      0x01FFFFFFUL                                   /**< Mask for AGC_GAINSTEPLIM0                   */
#define _AGC_GAINSTEPLIM0_CFLOOPSTEPMAX_SHIFT       0                                              /**< Shift value for AGC_CFLOOPSTEPMAX           */
#define _AGC_GAINSTEPLIM0_CFLOOPSTEPMAX_MASK        0x1FUL                                         /**< Bit mask for AGC_CFLOOPSTEPMAX              */
#define _AGC_GAINSTEPLIM0_CFLOOPSTEPMAX_DEFAULT     0x00000004UL                                   /**< Mode DEFAULT for AGC_GAINSTEPLIM0           */
#define AGC_GAINSTEPLIM0_CFLOOPSTEPMAX_DEFAULT      (_AGC_GAINSTEPLIM0_CFLOOPSTEPMAX_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_GAINSTEPLIM0   */
#define _AGC_GAINSTEPLIM0_CFLOOPDEL_SHIFT           5                                              /**< Shift value for AGC_CFLOOPDEL               */
#define _AGC_GAINSTEPLIM0_CFLOOPDEL_MASK            0xFE0UL                                        /**< Bit mask for AGC_CFLOOPDEL                  */
#define _AGC_GAINSTEPLIM0_CFLOOPDEL_DEFAULT         0x0000000AUL                                   /**< Mode DEFAULT for AGC_GAINSTEPLIM0           */
#define AGC_GAINSTEPLIM0_CFLOOPDEL_DEFAULT          (_AGC_GAINSTEPLIM0_CFLOOPDEL_DEFAULT << 5)     /**< Shifted mode DEFAULT for AGC_GAINSTEPLIM0   */
#define _AGC_GAINSTEPLIM0_HYST_SHIFT                12                                             /**< Shift value for AGC_HYST                    */
#define _AGC_GAINSTEPLIM0_HYST_MASK                 0xF000UL                                       /**< Bit mask for AGC_HYST                       */
#define _AGC_GAINSTEPLIM0_HYST_DEFAULT              0x00000003UL                                   /**< Mode DEFAULT for AGC_GAINSTEPLIM0           */
#define AGC_GAINSTEPLIM0_HYST_DEFAULT               (_AGC_GAINSTEPLIM0_HYST_DEFAULT << 12)         /**< Shifted mode DEFAULT for AGC_GAINSTEPLIM0   */
#define _AGC_GAINSTEPLIM0_MAXPWRVAR_SHIFT           16                                             /**< Shift value for AGC_MAXPWRVAR               */
#define _AGC_GAINSTEPLIM0_MAXPWRVAR_MASK            0xFF0000UL                                     /**< Bit mask for AGC_MAXPWRVAR                  */
#define _AGC_GAINSTEPLIM0_MAXPWRVAR_DEFAULT         0x00000000UL                                   /**< Mode DEFAULT for AGC_GAINSTEPLIM0           */
#define AGC_GAINSTEPLIM0_MAXPWRVAR_DEFAULT          (_AGC_GAINSTEPLIM0_MAXPWRVAR_DEFAULT << 16)    /**< Shifted mode DEFAULT for AGC_GAINSTEPLIM0   */
#define AGC_GAINSTEPLIM0_TRANRSTAGC                 (0x1UL << 24)                                  /**< power transient detector Reset AGC          */
#define _AGC_GAINSTEPLIM0_TRANRSTAGC_SHIFT          24                                             /**< Shift value for AGC_TRANRSTAGC              */
#define _AGC_GAINSTEPLIM0_TRANRSTAGC_MASK           0x1000000UL                                    /**< Bit mask for AGC_TRANRSTAGC                 */
#define _AGC_GAINSTEPLIM0_TRANRSTAGC_DEFAULT        0x00000000UL                                   /**< Mode DEFAULT for AGC_GAINSTEPLIM0           */
#define AGC_GAINSTEPLIM0_TRANRSTAGC_DEFAULT         (_AGC_GAINSTEPLIM0_TRANRSTAGC_DEFAULT << 24)   /**< Shifted mode DEFAULT for AGC_GAINSTEPLIM0   */

/* Bit fields for AGC GAINSTEPLIM1 */
#define _AGC_GAINSTEPLIM1_RESETVALUE                0x000011BAUL                                 /**< Default value for AGC_GAINSTEPLIM1          */
#define _AGC_GAINSTEPLIM1_MASK                      0x00001FFFUL                                 /**< Mask for AGC_GAINSTEPLIM1                   */
#define _AGC_GAINSTEPLIM1_LNAINDEXMAX_SHIFT         0                                            /**< Shift value for AGC_LNAINDEXMAX             */
#define _AGC_GAINSTEPLIM1_LNAINDEXMAX_MASK          0xFUL                                        /**< Bit mask for AGC_LNAINDEXMAX                */
#define _AGC_GAINSTEPLIM1_LNAINDEXMAX_DEFAULT       0x0000000AUL                                 /**< Mode DEFAULT for AGC_GAINSTEPLIM1           */
#define AGC_GAINSTEPLIM1_LNAINDEXMAX_DEFAULT        (_AGC_GAINSTEPLIM1_LNAINDEXMAX_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_GAINSTEPLIM1   */
#define _AGC_GAINSTEPLIM1_PGAINDEXMAX_SHIFT         4                                            /**< Shift value for AGC_PGAINDEXMAX             */
#define _AGC_GAINSTEPLIM1_PGAINDEXMAX_MASK          0xF0UL                                       /**< Bit mask for AGC_PGAINDEXMAX                */
#define _AGC_GAINSTEPLIM1_PGAINDEXMAX_DEFAULT       0x0000000BUL                                 /**< Mode DEFAULT for AGC_GAINSTEPLIM1           */
#define AGC_GAINSTEPLIM1_PGAINDEXMAX_DEFAULT        (_AGC_GAINSTEPLIM1_PGAINDEXMAX_DEFAULT << 4) /**< Shifted mode DEFAULT for AGC_GAINSTEPLIM1   */
#define _AGC_GAINSTEPLIM1_PNINDEXMAX_SHIFT          8                                            /**< Shift value for AGC_PNINDEXMAX              */
#define _AGC_GAINSTEPLIM1_PNINDEXMAX_MASK           0x1F00UL                                     /**< Bit mask for AGC_PNINDEXMAX                 */
#define _AGC_GAINSTEPLIM1_PNINDEXMAX_DEFAULT        0x00000011UL                                 /**< Mode DEFAULT for AGC_GAINSTEPLIM1           */
#define AGC_GAINSTEPLIM1_PNINDEXMAX_DEFAULT         (_AGC_GAINSTEPLIM1_PNINDEXMAX_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_GAINSTEPLIM1   */

/* Bit fields for AGC PNRFATT0 */
#define _AGC_PNRFATT0_RESETVALUE                    0x00140000UL                               /**< Default value for AGC_PNRFATT0              */
#define _AGC_PNRFATT0_MASK                          0x3FFF3FFFUL                               /**< Mask for AGC_PNRFATT0                       */
#define _AGC_PNRFATT0_LNAMIXRFATT1_SHIFT            0                                          /**< Shift value for AGC_LNAMIXRFATT1            */
#define _AGC_PNRFATT0_LNAMIXRFATT1_MASK             0x3FFFUL                                   /**< Bit mask for AGC_LNAMIXRFATT1               */
#define _AGC_PNRFATT0_LNAMIXRFATT1_DEFAULT          0x00000000UL                               /**< Mode DEFAULT for AGC_PNRFATT0               */
#define AGC_PNRFATT0_LNAMIXRFATT1_DEFAULT           (_AGC_PNRFATT0_LNAMIXRFATT1_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFATT0       */
#define _AGC_PNRFATT0_LNAMIXRFATT2_SHIFT            16                                         /**< Shift value for AGC_LNAMIXRFATT2            */
#define _AGC_PNRFATT0_LNAMIXRFATT2_MASK             0x3FFF0000UL                               /**< Bit mask for AGC_LNAMIXRFATT2               */
#define _AGC_PNRFATT0_LNAMIXRFATT2_DEFAULT          0x00000014UL                               /**< Mode DEFAULT for AGC_PNRFATT0               */
#define AGC_PNRFATT0_LNAMIXRFATT2_DEFAULT           (_AGC_PNRFATT0_LNAMIXRFATT2_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_PNRFATT0       */

/* Bit fields for AGC PNRFATT1 */
#define _AGC_PNRFATT1_RESETVALUE                    0x004C0030UL                               /**< Default value for AGC_PNRFATT1              */
#define _AGC_PNRFATT1_MASK                          0x3FFF3FFFUL                               /**< Mask for AGC_PNRFATT1                       */
#define _AGC_PNRFATT1_LNAMIXRFATT3_SHIFT            0                                          /**< Shift value for AGC_LNAMIXRFATT3            */
#define _AGC_PNRFATT1_LNAMIXRFATT3_MASK             0x3FFFUL                                   /**< Bit mask for AGC_LNAMIXRFATT3               */
#define _AGC_PNRFATT1_LNAMIXRFATT3_DEFAULT          0x00000030UL                               /**< Mode DEFAULT for AGC_PNRFATT1               */
#define AGC_PNRFATT1_LNAMIXRFATT3_DEFAULT           (_AGC_PNRFATT1_LNAMIXRFATT3_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFATT1       */
#define _AGC_PNRFATT1_LNAMIXRFATT4_SHIFT            16                                         /**< Shift value for AGC_LNAMIXRFATT4            */
#define _AGC_PNRFATT1_LNAMIXRFATT4_MASK             0x3FFF0000UL                               /**< Bit mask for AGC_LNAMIXRFATT4               */
#define _AGC_PNRFATT1_LNAMIXRFATT4_DEFAULT          0x0000004CUL                               /**< Mode DEFAULT for AGC_PNRFATT1               */
#define AGC_PNRFATT1_LNAMIXRFATT4_DEFAULT           (_AGC_PNRFATT1_LNAMIXRFATT4_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_PNRFATT1       */

/* Bit fields for AGC PNRFATT2 */
#define _AGC_PNRFATT2_RESETVALUE                    0x00A40074UL                               /**< Default value for AGC_PNRFATT2              */
#define _AGC_PNRFATT2_MASK                          0x3FFF3FFFUL                               /**< Mask for AGC_PNRFATT2                       */
#define _AGC_PNRFATT2_LNAMIXRFATT5_SHIFT            0                                          /**< Shift value for AGC_LNAMIXRFATT5            */
#define _AGC_PNRFATT2_LNAMIXRFATT5_MASK             0x3FFFUL                                   /**< Bit mask for AGC_LNAMIXRFATT5               */
#define _AGC_PNRFATT2_LNAMIXRFATT5_DEFAULT          0x00000074UL                               /**< Mode DEFAULT for AGC_PNRFATT2               */
#define AGC_PNRFATT2_LNAMIXRFATT5_DEFAULT           (_AGC_PNRFATT2_LNAMIXRFATT5_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFATT2       */
#define _AGC_PNRFATT2_LNAMIXRFATT6_SHIFT            16                                         /**< Shift value for AGC_LNAMIXRFATT6            */
#define _AGC_PNRFATT2_LNAMIXRFATT6_MASK             0x3FFF0000UL                               /**< Bit mask for AGC_LNAMIXRFATT6               */
#define _AGC_PNRFATT2_LNAMIXRFATT6_DEFAULT          0x000000A4UL                               /**< Mode DEFAULT for AGC_PNRFATT2               */
#define AGC_PNRFATT2_LNAMIXRFATT6_DEFAULT           (_AGC_PNRFATT2_LNAMIXRFATT6_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_PNRFATT2       */

/* Bit fields for AGC PNRFATT3 */
#define _AGC_PNRFATT3_RESETVALUE                    0x01B400E4UL                               /**< Default value for AGC_PNRFATT3              */
#define _AGC_PNRFATT3_MASK                          0x3FFF3FFFUL                               /**< Mask for AGC_PNRFATT3                       */
#define _AGC_PNRFATT3_LNAMIXRFATT7_SHIFT            0                                          /**< Shift value for AGC_LNAMIXRFATT7            */
#define _AGC_PNRFATT3_LNAMIXRFATT7_MASK             0x3FFFUL                                   /**< Bit mask for AGC_LNAMIXRFATT7               */
#define _AGC_PNRFATT3_LNAMIXRFATT7_DEFAULT          0x000000E4UL                               /**< Mode DEFAULT for AGC_PNRFATT3               */
#define AGC_PNRFATT3_LNAMIXRFATT7_DEFAULT           (_AGC_PNRFATT3_LNAMIXRFATT7_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFATT3       */
#define _AGC_PNRFATT3_LNAMIXRFATT8_SHIFT            16                                         /**< Shift value for AGC_LNAMIXRFATT8            */
#define _AGC_PNRFATT3_LNAMIXRFATT8_MASK             0x3FFF0000UL                               /**< Bit mask for AGC_LNAMIXRFATT8               */
#define _AGC_PNRFATT3_LNAMIXRFATT8_DEFAULT          0x000001B4UL                               /**< Mode DEFAULT for AGC_PNRFATT3               */
#define AGC_PNRFATT3_LNAMIXRFATT8_DEFAULT           (_AGC_PNRFATT3_LNAMIXRFATT8_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_PNRFATT3       */

/* Bit fields for AGC PNRFATT4 */
#define _AGC_PNRFATT4_RESETVALUE                    0x039C029CUL                                /**< Default value for AGC_PNRFATT4              */
#define _AGC_PNRFATT4_MASK                          0x3FFF3FFFUL                                /**< Mask for AGC_PNRFATT4                       */
#define _AGC_PNRFATT4_LNAMIXRFATT9_SHIFT            0                                           /**< Shift value for AGC_LNAMIXRFATT9            */
#define _AGC_PNRFATT4_LNAMIXRFATT9_MASK             0x3FFFUL                                    /**< Bit mask for AGC_LNAMIXRFATT9               */
#define _AGC_PNRFATT4_LNAMIXRFATT9_DEFAULT          0x0000029CUL                                /**< Mode DEFAULT for AGC_PNRFATT4               */
#define AGC_PNRFATT4_LNAMIXRFATT9_DEFAULT           (_AGC_PNRFATT4_LNAMIXRFATT9_DEFAULT << 0)   /**< Shifted mode DEFAULT for AGC_PNRFATT4       */
#define _AGC_PNRFATT4_LNAMIXRFATT10_SHIFT           16                                          /**< Shift value for AGC_LNAMIXRFATT10           */
#define _AGC_PNRFATT4_LNAMIXRFATT10_MASK            0x3FFF0000UL                                /**< Bit mask for AGC_LNAMIXRFATT10              */
#define _AGC_PNRFATT4_LNAMIXRFATT10_DEFAULT         0x0000039CUL                                /**< Mode DEFAULT for AGC_PNRFATT4               */
#define AGC_PNRFATT4_LNAMIXRFATT10_DEFAULT          (_AGC_PNRFATT4_LNAMIXRFATT10_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_PNRFATT4       */

/* Bit fields for AGC PNRFATT5 */
#define _AGC_PNRFATT5_RESETVALUE                    0x05FA04BAUL                                /**< Default value for AGC_PNRFATT5              */
#define _AGC_PNRFATT5_MASK                          0x3FFF3FFFUL                                /**< Mask for AGC_PNRFATT5                       */
#define _AGC_PNRFATT5_LNAMIXRFATT11_SHIFT           0                                           /**< Shift value for AGC_LNAMIXRFATT11           */
#define _AGC_PNRFATT5_LNAMIXRFATT11_MASK            0x3FFFUL                                    /**< Bit mask for AGC_LNAMIXRFATT11              */
#define _AGC_PNRFATT5_LNAMIXRFATT11_DEFAULT         0x000004BAUL                                /**< Mode DEFAULT for AGC_PNRFATT5               */
#define AGC_PNRFATT5_LNAMIXRFATT11_DEFAULT          (_AGC_PNRFATT5_LNAMIXRFATT11_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFATT5       */
#define _AGC_PNRFATT5_LNAMIXRFATT12_SHIFT           16                                          /**< Shift value for AGC_LNAMIXRFATT12           */
#define _AGC_PNRFATT5_LNAMIXRFATT12_MASK            0x3FFF0000UL                                /**< Bit mask for AGC_LNAMIXRFATT12              */
#define _AGC_PNRFATT5_LNAMIXRFATT12_DEFAULT         0x000005FAUL                                /**< Mode DEFAULT for AGC_PNRFATT5               */
#define AGC_PNRFATT5_LNAMIXRFATT12_DEFAULT          (_AGC_PNRFATT5_LNAMIXRFATT12_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_PNRFATT5       */

/* Bit fields for AGC PNRFATT6 */
#define _AGC_PNRFATT6_RESETVALUE                    0x0AA007EEUL                                /**< Default value for AGC_PNRFATT6              */
#define _AGC_PNRFATT6_MASK                          0x3FFF3FFFUL                                /**< Mask for AGC_PNRFATT6                       */
#define _AGC_PNRFATT6_LNAMIXRFATT13_SHIFT           0                                           /**< Shift value for AGC_LNAMIXRFATT13           */
#define _AGC_PNRFATT6_LNAMIXRFATT13_MASK            0x3FFFUL                                    /**< Bit mask for AGC_LNAMIXRFATT13              */
#define _AGC_PNRFATT6_LNAMIXRFATT13_DEFAULT         0x000007EEUL                                /**< Mode DEFAULT for AGC_PNRFATT6               */
#define AGC_PNRFATT6_LNAMIXRFATT13_DEFAULT          (_AGC_PNRFATT6_LNAMIXRFATT13_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFATT6       */
#define _AGC_PNRFATT6_LNAMIXRFATT14_SHIFT           16                                          /**< Shift value for AGC_LNAMIXRFATT14           */
#define _AGC_PNRFATT6_LNAMIXRFATT14_MASK            0x3FFF0000UL                                /**< Bit mask for AGC_LNAMIXRFATT14              */
#define _AGC_PNRFATT6_LNAMIXRFATT14_DEFAULT         0x00000AA0UL                                /**< Mode DEFAULT for AGC_PNRFATT6               */
#define AGC_PNRFATT6_LNAMIXRFATT14_DEFAULT          (_AGC_PNRFATT6_LNAMIXRFATT14_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_PNRFATT6       */

/* Bit fields for AGC PNRFATT7 */
#define _AGC_PNRFATT7_RESETVALUE                    0x10FE0D98UL                                /**< Default value for AGC_PNRFATT7              */
#define _AGC_PNRFATT7_MASK                          0x3FFF3FFFUL                                /**< Mask for AGC_PNRFATT7                       */
#define _AGC_PNRFATT7_LNAMIXRFATT15_SHIFT           0                                           /**< Shift value for AGC_LNAMIXRFATT15           */
#define _AGC_PNRFATT7_LNAMIXRFATT15_MASK            0x3FFFUL                                    /**< Bit mask for AGC_LNAMIXRFATT15              */
#define _AGC_PNRFATT7_LNAMIXRFATT15_DEFAULT         0x00000D98UL                                /**< Mode DEFAULT for AGC_PNRFATT7               */
#define AGC_PNRFATT7_LNAMIXRFATT15_DEFAULT          (_AGC_PNRFATT7_LNAMIXRFATT15_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFATT7       */
#define _AGC_PNRFATT7_LNAMIXRFATT16_SHIFT           16                                          /**< Shift value for AGC_LNAMIXRFATT16           */
#define _AGC_PNRFATT7_LNAMIXRFATT16_MASK            0x3FFF0000UL                                /**< Bit mask for AGC_LNAMIXRFATT16              */
#define _AGC_PNRFATT7_LNAMIXRFATT16_DEFAULT         0x000010FEUL                                /**< Mode DEFAULT for AGC_PNRFATT7               */
#define AGC_PNRFATT7_LNAMIXRFATT16_DEFAULT          (_AGC_PNRFATT7_LNAMIXRFATT16_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_PNRFATT7       */

/* Bit fields for AGC PNRFATT8 */
#define _AGC_PNRFATT8_RESETVALUE                    0x1BF815FEUL                                /**< Default value for AGC_PNRFATT8              */
#define _AGC_PNRFATT8_MASK                          0x3FFF3FFFUL                                /**< Mask for AGC_PNRFATT8                       */
#define _AGC_PNRFATT8_LNAMIXRFATT17_SHIFT           0                                           /**< Shift value for AGC_LNAMIXRFATT17           */
#define _AGC_PNRFATT8_LNAMIXRFATT17_MASK            0x3FFFUL                                    /**< Bit mask for AGC_LNAMIXRFATT17              */
#define _AGC_PNRFATT8_LNAMIXRFATT17_DEFAULT         0x000015FEUL                                /**< Mode DEFAULT for AGC_PNRFATT8               */
#define AGC_PNRFATT8_LNAMIXRFATT17_DEFAULT          (_AGC_PNRFATT8_LNAMIXRFATT17_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFATT8       */
#define _AGC_PNRFATT8_LNAMIXRFATT18_SHIFT           16                                          /**< Shift value for AGC_LNAMIXRFATT18           */
#define _AGC_PNRFATT8_LNAMIXRFATT18_MASK            0x3FFF0000UL                                /**< Bit mask for AGC_LNAMIXRFATT18              */
#define _AGC_PNRFATT8_LNAMIXRFATT18_DEFAULT         0x00001BF8UL                                /**< Mode DEFAULT for AGC_PNRFATT8               */
#define AGC_PNRFATT8_LNAMIXRFATT18_DEFAULT          (_AGC_PNRFATT8_LNAMIXRFATT18_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_PNRFATT8       */

/* Bit fields for AGC PNRFATT9 */
#define _AGC_PNRFATT9_RESETVALUE                    0x2DB423DCUL                                /**< Default value for AGC_PNRFATT9              */
#define _AGC_PNRFATT9_MASK                          0x3FFF3FFFUL                                /**< Mask for AGC_PNRFATT9                       */
#define _AGC_PNRFATT9_LNAMIXRFATT19_SHIFT           0                                           /**< Shift value for AGC_LNAMIXRFATT19           */
#define _AGC_PNRFATT9_LNAMIXRFATT19_MASK            0x3FFFUL                                    /**< Bit mask for AGC_LNAMIXRFATT19              */
#define _AGC_PNRFATT9_LNAMIXRFATT19_DEFAULT         0x000023DCUL                                /**< Mode DEFAULT for AGC_PNRFATT9               */
#define AGC_PNRFATT9_LNAMIXRFATT19_DEFAULT          (_AGC_PNRFATT9_LNAMIXRFATT19_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFATT9       */
#define _AGC_PNRFATT9_LNAMIXRFATT20_SHIFT           16                                          /**< Shift value for AGC_LNAMIXRFATT20           */
#define _AGC_PNRFATT9_LNAMIXRFATT20_MASK            0x3FFF0000UL                                /**< Bit mask for AGC_LNAMIXRFATT20              */
#define _AGC_PNRFATT9_LNAMIXRFATT20_DEFAULT         0x00002DB4UL                                /**< Mode DEFAULT for AGC_PNRFATT9               */
#define AGC_PNRFATT9_LNAMIXRFATT20_DEFAULT          (_AGC_PNRFATT9_LNAMIXRFATT20_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_PNRFATT9       */

/* Bit fields for AGC PNRFATT10 */
#define _AGC_PNRFATT10_RESETVALUE                   0x3FFF39D0UL                                 /**< Default value for AGC_PNRFATT10             */
#define _AGC_PNRFATT10_MASK                         0x3FFF3FFFUL                                 /**< Mask for AGC_PNRFATT10                      */
#define _AGC_PNRFATT10_LNAMIXRFATT21_SHIFT          0                                            /**< Shift value for AGC_LNAMIXRFATT21           */
#define _AGC_PNRFATT10_LNAMIXRFATT21_MASK           0x3FFFUL                                     /**< Bit mask for AGC_LNAMIXRFATT21              */
#define _AGC_PNRFATT10_LNAMIXRFATT21_DEFAULT        0x000039D0UL                                 /**< Mode DEFAULT for AGC_PNRFATT10              */
#define AGC_PNRFATT10_LNAMIXRFATT21_DEFAULT         (_AGC_PNRFATT10_LNAMIXRFATT21_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFATT10      */
#define _AGC_PNRFATT10_LNAMIXRFATT22_SHIFT          16                                           /**< Shift value for AGC_LNAMIXRFATT22           */
#define _AGC_PNRFATT10_LNAMIXRFATT22_MASK           0x3FFF0000UL                                 /**< Bit mask for AGC_LNAMIXRFATT22              */
#define _AGC_PNRFATT10_LNAMIXRFATT22_DEFAULT        0x00003FFFUL                                 /**< Mode DEFAULT for AGC_PNRFATT10              */
#define AGC_PNRFATT10_LNAMIXRFATT22_DEFAULT         (_AGC_PNRFATT10_LNAMIXRFATT22_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_PNRFATT10      */

/* Bit fields for AGC PNRFATT11 */
#define _AGC_PNRFATT11_RESETVALUE                   0x00003FFFUL                                /**< Default value for AGC_PNRFATT11             */
#define _AGC_PNRFATT11_MASK                         0x00003FFFUL                                /**< Mask for AGC_PNRFATT11                      */
#define _AGC_PNRFATT11_LNAMIXRFATT23_SHIFT          0                                           /**< Shift value for AGC_LNAMIXRFATT23           */
#define _AGC_PNRFATT11_LNAMIXRFATT23_MASK           0x3FFFUL                                    /**< Bit mask for AGC_LNAMIXRFATT23              */
#define _AGC_PNRFATT11_LNAMIXRFATT23_DEFAULT        0x00003FFFUL                                /**< Mode DEFAULT for AGC_PNRFATT11              */
#define AGC_PNRFATT11_LNAMIXRFATT23_DEFAULT         (_AGC_PNRFATT11_LNAMIXRFATT23_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_PNRFATT11      */

/* Bit fields for AGC PNRFATTALT */
#define _AGC_PNRFATTALT_RESETVALUE                  0x00003FFFUL                                  /**< Default value for AGC_PNRFATTALT            */
#define _AGC_PNRFATTALT_MASK                        0x00003FFFUL                                  /**< Mask for AGC_PNRFATTALT                     */
#define _AGC_PNRFATTALT_LNAMIXRFATTALT_SHIFT        0                                             /**< Shift value for AGC_LNAMIXRFATTALT          */
#define _AGC_PNRFATTALT_LNAMIXRFATTALT_MASK         0x3FFFUL                                      /**< Bit mask for AGC_LNAMIXRFATTALT             */
#define _AGC_PNRFATTALT_LNAMIXRFATTALT_DEFAULT      0x00003FFFUL                                  /**< Mode DEFAULT for AGC_PNRFATTALT             */
#define AGC_PNRFATTALT_LNAMIXRFATTALT_DEFAULT       (_AGC_PNRFATTALT_LNAMIXRFATTALT_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_PNRFATTALT     */

/* Bit fields for AGC LNAMIXCODE0 */
#define _AGC_LNAMIXCODE0_RESETVALUE                 0x15724BBDUL                                  /**< Default value for AGC_LNAMIXCODE0           */
#define _AGC_LNAMIXCODE0_MASK                       0x3FFFFFFFUL                                  /**< Mask for AGC_LNAMIXCODE0                    */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE1_SHIFT         0                                             /**< Shift value for AGC_LNAMIXSLICE1            */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE1_MASK          0x3FUL                                        /**< Bit mask for AGC_LNAMIXSLICE1               */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE1_DEFAULT       0x0000003DUL                                  /**< Mode DEFAULT for AGC_LNAMIXCODE0            */
#define AGC_LNAMIXCODE0_LNAMIXSLICE1_DEFAULT        (_AGC_LNAMIXCODE0_LNAMIXSLICE1_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_LNAMIXCODE0    */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE2_SHIFT         6                                             /**< Shift value for AGC_LNAMIXSLICE2            */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE2_MASK          0xFC0UL                                       /**< Bit mask for AGC_LNAMIXSLICE2               */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE2_DEFAULT       0x0000002EUL                                  /**< Mode DEFAULT for AGC_LNAMIXCODE0            */
#define AGC_LNAMIXCODE0_LNAMIXSLICE2_DEFAULT        (_AGC_LNAMIXCODE0_LNAMIXSLICE2_DEFAULT << 6)  /**< Shifted mode DEFAULT for AGC_LNAMIXCODE0    */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE3_SHIFT         12                                            /**< Shift value for AGC_LNAMIXSLICE3            */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE3_MASK          0x3F000UL                                     /**< Bit mask for AGC_LNAMIXSLICE3               */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE3_DEFAULT       0x00000024UL                                  /**< Mode DEFAULT for AGC_LNAMIXCODE0            */
#define AGC_LNAMIXCODE0_LNAMIXSLICE3_DEFAULT        (_AGC_LNAMIXCODE0_LNAMIXSLICE3_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_LNAMIXCODE0    */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE4_SHIFT         18                                            /**< Shift value for AGC_LNAMIXSLICE4            */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE4_MASK          0xFC0000UL                                    /**< Bit mask for AGC_LNAMIXSLICE4               */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE4_DEFAULT       0x0000001CUL                                  /**< Mode DEFAULT for AGC_LNAMIXCODE0            */
#define AGC_LNAMIXCODE0_LNAMIXSLICE4_DEFAULT        (_AGC_LNAMIXCODE0_LNAMIXSLICE4_DEFAULT << 18) /**< Shifted mode DEFAULT for AGC_LNAMIXCODE0    */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE5_SHIFT         24                                            /**< Shift value for AGC_LNAMIXSLICE5            */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE5_MASK          0x3F000000UL                                  /**< Bit mask for AGC_LNAMIXSLICE5               */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE5_DEFAULT       0x00000015UL                                  /**< Mode DEFAULT for AGC_LNAMIXCODE0            */
#define AGC_LNAMIXCODE0_LNAMIXSLICE5_DEFAULT        (_AGC_LNAMIXCODE0_LNAMIXSLICE5_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_LNAMIXCODE0    */

/* Bit fields for AGC LNAMIXCODE1 */
#define _AGC_LNAMIXCODE1_RESETVALUE                 0x0518A311UL                                   /**< Default value for AGC_LNAMIXCODE1           */
#define _AGC_LNAMIXCODE1_MASK                       0x3FFFFFFFUL                                   /**< Mask for AGC_LNAMIXCODE1                    */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE6_SHIFT         0                                              /**< Shift value for AGC_LNAMIXSLICE6            */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE6_MASK          0x3FUL                                         /**< Bit mask for AGC_LNAMIXSLICE6               */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE6_DEFAULT       0x00000011UL                                   /**< Mode DEFAULT for AGC_LNAMIXCODE1            */
#define AGC_LNAMIXCODE1_LNAMIXSLICE6_DEFAULT        (_AGC_LNAMIXCODE1_LNAMIXSLICE6_DEFAULT << 0)   /**< Shifted mode DEFAULT for AGC_LNAMIXCODE1    */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE7_SHIFT         6                                              /**< Shift value for AGC_LNAMIXSLICE7            */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE7_MASK          0xFC0UL                                        /**< Bit mask for AGC_LNAMIXSLICE7               */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE7_DEFAULT       0x0000000CUL                                   /**< Mode DEFAULT for AGC_LNAMIXCODE1            */
#define AGC_LNAMIXCODE1_LNAMIXSLICE7_DEFAULT        (_AGC_LNAMIXCODE1_LNAMIXSLICE7_DEFAULT << 6)   /**< Shifted mode DEFAULT for AGC_LNAMIXCODE1    */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE8_SHIFT         12                                             /**< Shift value for AGC_LNAMIXSLICE8            */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE8_MASK          0x3F000UL                                      /**< Bit mask for AGC_LNAMIXSLICE8               */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE8_DEFAULT       0x0000000AUL                                   /**< Mode DEFAULT for AGC_LNAMIXCODE1            */
#define AGC_LNAMIXCODE1_LNAMIXSLICE8_DEFAULT        (_AGC_LNAMIXCODE1_LNAMIXSLICE8_DEFAULT << 12)  /**< Shifted mode DEFAULT for AGC_LNAMIXCODE1    */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE9_SHIFT         18                                             /**< Shift value for AGC_LNAMIXSLICE9            */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE9_MASK          0xFC0000UL                                     /**< Bit mask for AGC_LNAMIXSLICE9               */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE9_DEFAULT       0x00000006UL                                   /**< Mode DEFAULT for AGC_LNAMIXCODE1            */
#define AGC_LNAMIXCODE1_LNAMIXSLICE9_DEFAULT        (_AGC_LNAMIXCODE1_LNAMIXSLICE9_DEFAULT << 18)  /**< Shifted mode DEFAULT for AGC_LNAMIXCODE1    */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE10_SHIFT        24                                             /**< Shift value for AGC_LNAMIXSLICE10           */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE10_MASK         0x3F000000UL                                   /**< Bit mask for AGC_LNAMIXSLICE10              */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE10_DEFAULT      0x00000005UL                                   /**< Mode DEFAULT for AGC_LNAMIXCODE1            */
#define AGC_LNAMIXCODE1_LNAMIXSLICE10_DEFAULT       (_AGC_LNAMIXCODE1_LNAMIXSLICE10_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_LNAMIXCODE1    */

/* Bit fields for AGC PGACODE0 */
#define _AGC_PGACODE0_RESETVALUE                    0x76543210UL                           /**< Default value for AGC_PGACODE0              */
#define _AGC_PGACODE0_MASK                          0xFFFFFFFFUL                           /**< Mask for AGC_PGACODE0                       */
#define _AGC_PGACODE0_PGAGAIN1_SHIFT                0                                      /**< Shift value for AGC_PGAGAIN1                */
#define _AGC_PGACODE0_PGAGAIN1_MASK                 0xFUL                                  /**< Bit mask for AGC_PGAGAIN1                   */
#define _AGC_PGACODE0_PGAGAIN1_DEFAULT              0x00000000UL                           /**< Mode DEFAULT for AGC_PGACODE0               */
#define AGC_PGACODE0_PGAGAIN1_DEFAULT               (_AGC_PGACODE0_PGAGAIN1_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PGACODE0       */
#define _AGC_PGACODE0_PGAGAIN2_SHIFT                4                                      /**< Shift value for AGC_PGAGAIN2                */
#define _AGC_PGACODE0_PGAGAIN2_MASK                 0xF0UL                                 /**< Bit mask for AGC_PGAGAIN2                   */
#define _AGC_PGACODE0_PGAGAIN2_DEFAULT              0x00000001UL                           /**< Mode DEFAULT for AGC_PGACODE0               */
#define AGC_PGACODE0_PGAGAIN2_DEFAULT               (_AGC_PGACODE0_PGAGAIN2_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_PGACODE0       */
#define _AGC_PGACODE0_PGAGAIN3_SHIFT                8                                      /**< Shift value for AGC_PGAGAIN3                */
#define _AGC_PGACODE0_PGAGAIN3_MASK                 0xF00UL                                /**< Bit mask for AGC_PGAGAIN3                   */
#define _AGC_PGACODE0_PGAGAIN3_DEFAULT              0x00000002UL                           /**< Mode DEFAULT for AGC_PGACODE0               */
#define AGC_PGACODE0_PGAGAIN3_DEFAULT               (_AGC_PGACODE0_PGAGAIN3_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_PGACODE0       */
#define _AGC_PGACODE0_PGAGAIN4_SHIFT                12                                     /**< Shift value for AGC_PGAGAIN4                */
#define _AGC_PGACODE0_PGAGAIN4_MASK                 0xF000UL                               /**< Bit mask for AGC_PGAGAIN4                   */
#define _AGC_PGACODE0_PGAGAIN4_DEFAULT              0x00000003UL                           /**< Mode DEFAULT for AGC_PGACODE0               */
#define AGC_PGACODE0_PGAGAIN4_DEFAULT               (_AGC_PGACODE0_PGAGAIN4_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_PGACODE0       */
#define _AGC_PGACODE0_PGAGAIN5_SHIFT                16                                     /**< Shift value for AGC_PGAGAIN5                */
#define _AGC_PGACODE0_PGAGAIN5_MASK                 0xF0000UL                              /**< Bit mask for AGC_PGAGAIN5                   */
#define _AGC_PGACODE0_PGAGAIN5_DEFAULT              0x00000004UL                           /**< Mode DEFAULT for AGC_PGACODE0               */
#define AGC_PGACODE0_PGAGAIN5_DEFAULT               (_AGC_PGACODE0_PGAGAIN5_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_PGACODE0       */
#define _AGC_PGACODE0_PGAGAIN6_SHIFT                20                                     /**< Shift value for AGC_PGAGAIN6                */
#define _AGC_PGACODE0_PGAGAIN6_MASK                 0xF00000UL                             /**< Bit mask for AGC_PGAGAIN6                   */
#define _AGC_PGACODE0_PGAGAIN6_DEFAULT              0x00000005UL                           /**< Mode DEFAULT for AGC_PGACODE0               */
#define AGC_PGACODE0_PGAGAIN6_DEFAULT               (_AGC_PGACODE0_PGAGAIN6_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_PGACODE0       */
#define _AGC_PGACODE0_PGAGAIN7_SHIFT                24                                     /**< Shift value for AGC_PGAGAIN7                */
#define _AGC_PGACODE0_PGAGAIN7_MASK                 0xF000000UL                            /**< Bit mask for AGC_PGAGAIN7                   */
#define _AGC_PGACODE0_PGAGAIN7_DEFAULT              0x00000006UL                           /**< Mode DEFAULT for AGC_PGACODE0               */
#define AGC_PGACODE0_PGAGAIN7_DEFAULT               (_AGC_PGACODE0_PGAGAIN7_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_PGACODE0       */
#define _AGC_PGACODE0_PGAGAIN8_SHIFT                28                                     /**< Shift value for AGC_PGAGAIN8                */
#define _AGC_PGACODE0_PGAGAIN8_MASK                 0xF0000000UL                           /**< Bit mask for AGC_PGAGAIN8                   */
#define _AGC_PGACODE0_PGAGAIN8_DEFAULT              0x00000007UL                           /**< Mode DEFAULT for AGC_PGACODE0               */
#define AGC_PGACODE0_PGAGAIN8_DEFAULT               (_AGC_PGACODE0_PGAGAIN8_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_PGACODE0       */

/* Bit fields for AGC PGACODE1 */
#define _AGC_PGACODE1_RESETVALUE                    0x00000A98UL                           /**< Default value for AGC_PGACODE1              */
#define _AGC_PGACODE1_MASK                          0x00000FFFUL                           /**< Mask for AGC_PGACODE1                       */
#define _AGC_PGACODE1_PGAGAIN9_SHIFT                0                                      /**< Shift value for AGC_PGAGAIN9                */
#define _AGC_PGACODE1_PGAGAIN9_MASK                 0xFUL                                  /**< Bit mask for AGC_PGAGAIN9                   */
#define _AGC_PGACODE1_PGAGAIN9_DEFAULT              0x00000008UL                           /**< Mode DEFAULT for AGC_PGACODE1               */
#define AGC_PGACODE1_PGAGAIN9_DEFAULT               (_AGC_PGACODE1_PGAGAIN9_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PGACODE1       */
#define _AGC_PGACODE1_PGAGAIN10_SHIFT               4                                      /**< Shift value for AGC_PGAGAIN10               */
#define _AGC_PGACODE1_PGAGAIN10_MASK                0xF0UL                                 /**< Bit mask for AGC_PGAGAIN10                  */
#define _AGC_PGACODE1_PGAGAIN10_DEFAULT             0x00000009UL                           /**< Mode DEFAULT for AGC_PGACODE1               */
#define AGC_PGACODE1_PGAGAIN10_DEFAULT              (_AGC_PGACODE1_PGAGAIN10_DEFAULT << 4) /**< Shifted mode DEFAULT for AGC_PGACODE1       */
#define _AGC_PGACODE1_PGAGAIN11_SHIFT               8                                      /**< Shift value for AGC_PGAGAIN11               */
#define _AGC_PGACODE1_PGAGAIN11_MASK                0xF00UL                                /**< Bit mask for AGC_PGAGAIN11                  */
#define _AGC_PGACODE1_PGAGAIN11_DEFAULT             0x0000000AUL                           /**< Mode DEFAULT for AGC_PGACODE1               */
#define AGC_PGACODE1_PGAGAIN11_DEFAULT              (_AGC_PGACODE1_PGAGAIN11_DEFAULT << 8) /**< Shifted mode DEFAULT for AGC_PGACODE1       */

/* Bit fields for AGC LBT */
#define _AGC_LBT_RESETVALUE                         0x00000000UL                             /**< Default value for AGC_LBT                   */
#define _AGC_LBT_MASK                               0x0000007FUL                             /**< Mask for AGC_LBT                            */
#define _AGC_LBT_CCARSSIPERIOD_SHIFT                0                                        /**< Shift value for AGC_CCARSSIPERIOD           */
#define _AGC_LBT_CCARSSIPERIOD_MASK                 0xFUL                                    /**< Bit mask for AGC_CCARSSIPERIOD              */
#define _AGC_LBT_CCARSSIPERIOD_DEFAULT              0x00000000UL                             /**< Mode DEFAULT for AGC_LBT                    */
#define AGC_LBT_CCARSSIPERIOD_DEFAULT               (_AGC_LBT_CCARSSIPERIOD_DEFAULT << 0)    /**< Shifted mode DEFAULT for AGC_LBT            */
#define AGC_LBT_ENCCARSSIPERIOD                     (0x1UL << 4)                             /**< RSSI PERIOD during CCA measurements         */
#define _AGC_LBT_ENCCARSSIPERIOD_SHIFT              4                                        /**< Shift value for AGC_ENCCARSSIPERIOD         */
#define _AGC_LBT_ENCCARSSIPERIOD_MASK               0x10UL                                   /**< Bit mask for AGC_ENCCARSSIPERIOD            */
#define _AGC_LBT_ENCCARSSIPERIOD_DEFAULT            0x00000000UL                             /**< Mode DEFAULT for AGC_LBT                    */
#define AGC_LBT_ENCCARSSIPERIOD_DEFAULT             (_AGC_LBT_ENCCARSSIPERIOD_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_LBT            */
#define AGC_LBT_ENCCAGAINREDUCED                    (0x1UL << 5)                             /**< CCA gain reduced                            */
#define _AGC_LBT_ENCCAGAINREDUCED_SHIFT             5                                        /**< Shift value for AGC_ENCCAGAINREDUCED        */
#define _AGC_LBT_ENCCAGAINREDUCED_MASK              0x20UL                                   /**< Bit mask for AGC_ENCCAGAINREDUCED           */
#define _AGC_LBT_ENCCAGAINREDUCED_DEFAULT           0x00000000UL                             /**< Mode DEFAULT for AGC_LBT                    */
#define AGC_LBT_ENCCAGAINREDUCED_DEFAULT            (_AGC_LBT_ENCCAGAINREDUCED_DEFAULT << 5) /**< Shifted mode DEFAULT for AGC_LBT            */
#define AGC_LBT_ENCCARSSIMAX                        (0x1UL << 6)                             /**< Use RSSIMAX to indicate CCA                 */
#define _AGC_LBT_ENCCARSSIMAX_SHIFT                 6                                        /**< Shift value for AGC_ENCCARSSIMAX            */
#define _AGC_LBT_ENCCARSSIMAX_MASK                  0x40UL                                   /**< Bit mask for AGC_ENCCARSSIMAX               */
#define _AGC_LBT_ENCCARSSIMAX_DEFAULT               0x00000000UL                             /**< Mode DEFAULT for AGC_LBT                    */
#define AGC_LBT_ENCCARSSIMAX_DEFAULT                (_AGC_LBT_ENCCARSSIMAX_DEFAULT << 6)     /**< Shifted mode DEFAULT for AGC_LBT            */

/* Bit fields for AGC MIRRORIF */
#define _AGC_MIRRORIF_RESETVALUE                    0x00000000UL                                   /**< Default value for AGC_MIRRORIF              */
#define _AGC_MIRRORIF_MASK                          0x0000000FUL                                   /**< Mask for AGC_MIRRORIF                       */
#define AGC_MIRRORIF_RSSIPOSSTEPM                   (0x1UL << 0)                                   /**< Positive RSSI Step Detected                 */
#define _AGC_MIRRORIF_RSSIPOSSTEPM_SHIFT            0                                              /**< Shift value for AGC_RSSIPOSSTEPM            */
#define _AGC_MIRRORIF_RSSIPOSSTEPM_MASK             0x1UL                                          /**< Bit mask for AGC_RSSIPOSSTEPM               */
#define _AGC_MIRRORIF_RSSIPOSSTEPM_DEFAULT          0x00000000UL                                   /**< Mode DEFAULT for AGC_MIRRORIF               */
#define AGC_MIRRORIF_RSSIPOSSTEPM_DEFAULT           (_AGC_MIRRORIF_RSSIPOSSTEPM_DEFAULT << 0)      /**< Shifted mode DEFAULT for AGC_MIRRORIF       */
#define AGC_MIRRORIF_RSSINEGSTEPM                   (0x1UL << 1)                                   /**< Negative RSSI Step Detected                 */
#define _AGC_MIRRORIF_RSSINEGSTEPM_SHIFT            1                                              /**< Shift value for AGC_RSSINEGSTEPM            */
#define _AGC_MIRRORIF_RSSINEGSTEPM_MASK             0x2UL                                          /**< Bit mask for AGC_RSSINEGSTEPM               */
#define _AGC_MIRRORIF_RSSINEGSTEPM_DEFAULT          0x00000000UL                                   /**< Mode DEFAULT for AGC_MIRRORIF               */
#define AGC_MIRRORIF_RSSINEGSTEPM_DEFAULT           (_AGC_MIRRORIF_RSSINEGSTEPM_DEFAULT << 1)      /**< Shifted mode DEFAULT for AGC_MIRRORIF       */
#define AGC_MIRRORIF_SHORTRSSIPOSSTEPM              (0x1UL << 2)                                   /**< Short-term Positive RSSI Step Detected      */
#define _AGC_MIRRORIF_SHORTRSSIPOSSTEPM_SHIFT       2                                              /**< Shift value for AGC_SHORTRSSIPOSSTEPM       */
#define _AGC_MIRRORIF_SHORTRSSIPOSSTEPM_MASK        0x4UL                                          /**< Bit mask for AGC_SHORTRSSIPOSSTEPM          */
#define _AGC_MIRRORIF_SHORTRSSIPOSSTEPM_DEFAULT     0x00000000UL                                   /**< Mode DEFAULT for AGC_MIRRORIF               */
#define AGC_MIRRORIF_SHORTRSSIPOSSTEPM_DEFAULT      (_AGC_MIRRORIF_SHORTRSSIPOSSTEPM_DEFAULT << 2) /**< Shifted mode DEFAULT for AGC_MIRRORIF       */
#define AGC_MIRRORIF_IFMIRRORCLEAR                  (0x1UL << 3)                                   /**< Clear bit for the AGC IF MIRROR Register    */
#define _AGC_MIRRORIF_IFMIRRORCLEAR_SHIFT           3                                              /**< Shift value for AGC_IFMIRRORCLEAR           */
#define _AGC_MIRRORIF_IFMIRRORCLEAR_MASK            0x8UL                                          /**< Bit mask for AGC_IFMIRRORCLEAR              */
#define _AGC_MIRRORIF_IFMIRRORCLEAR_DEFAULT         0x00000000UL                                   /**< Mode DEFAULT for AGC_MIRRORIF               */
#define AGC_MIRRORIF_IFMIRRORCLEAR_DEFAULT          (_AGC_MIRRORIF_IFMIRRORCLEAR_DEFAULT << 3)     /**< Shifted mode DEFAULT for AGC_MIRRORIF       */

/* Bit fields for AGC SEQIF */
#define _AGC_SEQIF_RESETVALUE                       0x00000000UL                                /**< Default value for AGC_SEQIF                 */
#define _AGC_SEQIF_MASK                             0x00007F7DUL                                /**< Mask for AGC_SEQIF                          */
#define AGC_SEQIF_RSSIVALID                         (0x1UL << 0)                                /**< RSSI Value is Valid                         */
#define _AGC_SEQIF_RSSIVALID_SHIFT                  0                                           /**< Shift value for AGC_RSSIVALID               */
#define _AGC_SEQIF_RSSIVALID_MASK                   0x1UL                                       /**< Bit mask for AGC_RSSIVALID                  */
#define _AGC_SEQIF_RSSIVALID_DEFAULT                0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_RSSIVALID_DEFAULT                 (_AGC_SEQIF_RSSIVALID_DEFAULT << 0)         /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_CCA                               (0x1UL << 2)                                /**< Clear Channel Assessment                    */
#define _AGC_SEQIF_CCA_SHIFT                        2                                           /**< Shift value for AGC_CCA                     */
#define _AGC_SEQIF_CCA_MASK                         0x4UL                                       /**< Bit mask for AGC_CCA                        */
#define _AGC_SEQIF_CCA_DEFAULT                      0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_CCA_DEFAULT                       (_AGC_SEQIF_CCA_DEFAULT << 2)               /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_RSSIPOSSTEP                       (0x1UL << 3)                                /**< Positive RSSI Step Detected                 */
#define _AGC_SEQIF_RSSIPOSSTEP_SHIFT                3                                           /**< Shift value for AGC_RSSIPOSSTEP             */
#define _AGC_SEQIF_RSSIPOSSTEP_MASK                 0x8UL                                       /**< Bit mask for AGC_RSSIPOSSTEP                */
#define _AGC_SEQIF_RSSIPOSSTEP_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_RSSIPOSSTEP_DEFAULT               (_AGC_SEQIF_RSSIPOSSTEP_DEFAULT << 3)       /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_RSSINEGSTEP                       (0x1UL << 4)                                /**< Negative RSSI Step Detected                 */
#define _AGC_SEQIF_RSSINEGSTEP_SHIFT                4                                           /**< Shift value for AGC_RSSINEGSTEP             */
#define _AGC_SEQIF_RSSINEGSTEP_MASK                 0x10UL                                      /**< Bit mask for AGC_RSSINEGSTEP                */
#define _AGC_SEQIF_RSSINEGSTEP_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_RSSINEGSTEP_DEFAULT               (_AGC_SEQIF_RSSINEGSTEP_DEFAULT << 4)       /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_SHORTRSSIPOSSTEP                  (0x1UL << 6)                                /**< Short-term Positive RSSI Step Detected      */
#define _AGC_SEQIF_SHORTRSSIPOSSTEP_SHIFT           6                                           /**< Shift value for AGC_SHORTRSSIPOSSTEP        */
#define _AGC_SEQIF_SHORTRSSIPOSSTEP_MASK            0x40UL                                      /**< Bit mask for AGC_SHORTRSSIPOSSTEP           */
#define _AGC_SEQIF_SHORTRSSIPOSSTEP_DEFAULT         0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_SHORTRSSIPOSSTEP_DEFAULT          (_AGC_SEQIF_SHORTRSSIPOSSTEP_DEFAULT << 6)  /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_RFPKDPRDDONE                      (0x1UL << 8)                                /**< RF PKD PERIOD CNT TOMEOUT                   */
#define _AGC_SEQIF_RFPKDPRDDONE_SHIFT               8                                           /**< Shift value for AGC_RFPKDPRDDONE            */
#define _AGC_SEQIF_RFPKDPRDDONE_MASK                0x100UL                                     /**< Bit mask for AGC_RFPKDPRDDONE               */
#define _AGC_SEQIF_RFPKDPRDDONE_DEFAULT             0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_RFPKDPRDDONE_DEFAULT              (_AGC_SEQIF_RFPKDPRDDONE_DEFAULT << 8)      /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_RFPKDCNTDONE                      (0x1UL << 9)                                /**< RF PKD pulse CNT TOMEOUT                    */
#define _AGC_SEQIF_RFPKDCNTDONE_SHIFT               9                                           /**< Shift value for AGC_RFPKDCNTDONE            */
#define _AGC_SEQIF_RFPKDCNTDONE_MASK                0x200UL                                     /**< Bit mask for AGC_RFPKDCNTDONE               */
#define _AGC_SEQIF_RFPKDCNTDONE_DEFAULT             0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_RFPKDCNTDONE_DEFAULT              (_AGC_SEQIF_RFPKDCNTDONE_DEFAULT << 9)      /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_RSSIHIGH                          (0x1UL << 10)                               /**< RSSI high detected                          */
#define _AGC_SEQIF_RSSIHIGH_SHIFT                   10                                          /**< Shift value for AGC_RSSIHIGH                */
#define _AGC_SEQIF_RSSIHIGH_MASK                    0x400UL                                     /**< Bit mask for AGC_RSSIHIGH                   */
#define _AGC_SEQIF_RSSIHIGH_DEFAULT                 0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_RSSIHIGH_DEFAULT                  (_AGC_SEQIF_RSSIHIGH_DEFAULT << 10)         /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_RSSILOW                           (0x1UL << 11)                               /**< RSSI low detected                           */
#define _AGC_SEQIF_RSSILOW_SHIFT                    11                                          /**< Shift value for AGC_RSSILOW                 */
#define _AGC_SEQIF_RSSILOW_MASK                     0x800UL                                     /**< Bit mask for AGC_RSSILOW                    */
#define _AGC_SEQIF_RSSILOW_DEFAULT                  0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_RSSILOW_DEFAULT                   (_AGC_SEQIF_RSSILOW_DEFAULT << 11)          /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_CCANODET                          (0x1UL << 12)                               /**< CCA Not Detected                            */
#define _AGC_SEQIF_CCANODET_SHIFT                   12                                          /**< Shift value for AGC_CCANODET                */
#define _AGC_SEQIF_CCANODET_MASK                    0x1000UL                                    /**< Bit mask for AGC_CCANODET                   */
#define _AGC_SEQIF_CCANODET_DEFAULT                 0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_CCANODET_DEFAULT                  (_AGC_SEQIF_CCANODET_DEFAULT << 12)         /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_GAINBELOWGAINTHD                  (0x1UL << 13)                               /**< agc gain above threshold int                */
#define _AGC_SEQIF_GAINBELOWGAINTHD_SHIFT           13                                          /**< Shift value for AGC_GAINBELOWGAINTHD        */
#define _AGC_SEQIF_GAINBELOWGAINTHD_MASK            0x2000UL                                    /**< Bit mask for AGC_GAINBELOWGAINTHD           */
#define _AGC_SEQIF_GAINBELOWGAINTHD_DEFAULT         0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_GAINBELOWGAINTHD_DEFAULT          (_AGC_SEQIF_GAINBELOWGAINTHD_DEFAULT << 13) /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_GAINUPDATEFRZ                     (0x1UL << 14)                               /**< AGC gain update frozen int                  */
#define _AGC_SEQIF_GAINUPDATEFRZ_SHIFT              14                                          /**< Shift value for AGC_GAINUPDATEFRZ           */
#define _AGC_SEQIF_GAINUPDATEFRZ_MASK               0x4000UL                                    /**< Bit mask for AGC_GAINUPDATEFRZ              */
#define _AGC_SEQIF_GAINUPDATEFRZ_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_GAINUPDATEFRZ_DEFAULT             (_AGC_SEQIF_GAINUPDATEFRZ_DEFAULT << 14)    /**< Shifted mode DEFAULT for AGC_SEQIF          */

/* Bit fields for AGC SEQIEN */
#define _AGC_SEQIEN_RESETVALUE                      0x00000000UL                                 /**< Default value for AGC_SEQIEN                */
#define _AGC_SEQIEN_MASK                            0x00007F7DUL                                 /**< Mask for AGC_SEQIEN                         */
#define AGC_SEQIEN_RSSIVALID                        (0x1UL << 0)                                 /**< RSSIVALID Interrupt Enable                  */
#define _AGC_SEQIEN_RSSIVALID_SHIFT                 0                                            /**< Shift value for AGC_RSSIVALID               */
#define _AGC_SEQIEN_RSSIVALID_MASK                  0x1UL                                        /**< Bit mask for AGC_RSSIVALID                  */
#define _AGC_SEQIEN_RSSIVALID_DEFAULT               0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_RSSIVALID_DEFAULT                (_AGC_SEQIEN_RSSIVALID_DEFAULT << 0)         /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_CCA                              (0x1UL << 2)                                 /**< CCA Interrupt Enable                        */
#define _AGC_SEQIEN_CCA_SHIFT                       2                                            /**< Shift value for AGC_CCA                     */
#define _AGC_SEQIEN_CCA_MASK                        0x4UL                                        /**< Bit mask for AGC_CCA                        */
#define _AGC_SEQIEN_CCA_DEFAULT                     0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_CCA_DEFAULT                      (_AGC_SEQIEN_CCA_DEFAULT << 2)               /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_RSSIPOSSTEP                      (0x1UL << 3)                                 /**< RSSIPOSSTEP Interrupt Enable                */
#define _AGC_SEQIEN_RSSIPOSSTEP_SHIFT               3                                            /**< Shift value for AGC_RSSIPOSSTEP             */
#define _AGC_SEQIEN_RSSIPOSSTEP_MASK                0x8UL                                        /**< Bit mask for AGC_RSSIPOSSTEP                */
#define _AGC_SEQIEN_RSSIPOSSTEP_DEFAULT             0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_RSSIPOSSTEP_DEFAULT              (_AGC_SEQIEN_RSSIPOSSTEP_DEFAULT << 3)       /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_RSSINEGSTEP                      (0x1UL << 4)                                 /**< RSSINEGSTEP Interrupt Enable                */
#define _AGC_SEQIEN_RSSINEGSTEP_SHIFT               4                                            /**< Shift value for AGC_RSSINEGSTEP             */
#define _AGC_SEQIEN_RSSINEGSTEP_MASK                0x10UL                                       /**< Bit mask for AGC_RSSINEGSTEP                */
#define _AGC_SEQIEN_RSSINEGSTEP_DEFAULT             0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_RSSINEGSTEP_DEFAULT              (_AGC_SEQIEN_RSSINEGSTEP_DEFAULT << 4)       /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_SHORTRSSIPOSSTEP                 (0x1UL << 6)                                 /**< SHORTRSSIPOSSTEP Interrupt Enable           */
#define _AGC_SEQIEN_SHORTRSSIPOSSTEP_SHIFT          6                                            /**< Shift value for AGC_SHORTRSSIPOSSTEP        */
#define _AGC_SEQIEN_SHORTRSSIPOSSTEP_MASK           0x40UL                                       /**< Bit mask for AGC_SHORTRSSIPOSSTEP           */
#define _AGC_SEQIEN_SHORTRSSIPOSSTEP_DEFAULT        0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_SHORTRSSIPOSSTEP_DEFAULT         (_AGC_SEQIEN_SHORTRSSIPOSSTEP_DEFAULT << 6)  /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_RFPKDPRDDONE                     (0x1UL << 8)                                 /**< RF PKD PERIOD CNT Interrupt Enable          */
#define _AGC_SEQIEN_RFPKDPRDDONE_SHIFT              8                                            /**< Shift value for AGC_RFPKDPRDDONE            */
#define _AGC_SEQIEN_RFPKDPRDDONE_MASK               0x100UL                                      /**< Bit mask for AGC_RFPKDPRDDONE               */
#define _AGC_SEQIEN_RFPKDPRDDONE_DEFAULT            0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_RFPKDPRDDONE_DEFAULT             (_AGC_SEQIEN_RFPKDPRDDONE_DEFAULT << 8)      /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_RFPKDCNTDONE                     (0x1UL << 9)                                 /**< RF PKD pulse CNT Interrupt Enable           */
#define _AGC_SEQIEN_RFPKDCNTDONE_SHIFT              9                                            /**< Shift value for AGC_RFPKDCNTDONE            */
#define _AGC_SEQIEN_RFPKDCNTDONE_MASK               0x200UL                                      /**< Bit mask for AGC_RFPKDCNTDONE               */
#define _AGC_SEQIEN_RFPKDCNTDONE_DEFAULT            0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_RFPKDCNTDONE_DEFAULT             (_AGC_SEQIEN_RFPKDCNTDONE_DEFAULT << 9)      /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_RSSIHIGH                         (0x1UL << 10)                                /**< RSSIHIGH Interrupt Enable                   */
#define _AGC_SEQIEN_RSSIHIGH_SHIFT                  10                                           /**< Shift value for AGC_RSSIHIGH                */
#define _AGC_SEQIEN_RSSIHIGH_MASK                   0x400UL                                      /**< Bit mask for AGC_RSSIHIGH                   */
#define _AGC_SEQIEN_RSSIHIGH_DEFAULT                0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_RSSIHIGH_DEFAULT                 (_AGC_SEQIEN_RSSIHIGH_DEFAULT << 10)         /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_RSSILOW                          (0x1UL << 11)                                /**< RSSILOW Interrupt Enable                    */
#define _AGC_SEQIEN_RSSILOW_SHIFT                   11                                           /**< Shift value for AGC_RSSILOW                 */
#define _AGC_SEQIEN_RSSILOW_MASK                    0x800UL                                      /**< Bit mask for AGC_RSSILOW                    */
#define _AGC_SEQIEN_RSSILOW_DEFAULT                 0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_RSSILOW_DEFAULT                  (_AGC_SEQIEN_RSSILOW_DEFAULT << 11)          /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_CCANODET                         (0x1UL << 12)                                /**< CCANODET Interrupt Enable                   */
#define _AGC_SEQIEN_CCANODET_SHIFT                  12                                           /**< Shift value for AGC_CCANODET                */
#define _AGC_SEQIEN_CCANODET_MASK                   0x1000UL                                     /**< Bit mask for AGC_CCANODET                   */
#define _AGC_SEQIEN_CCANODET_DEFAULT                0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_CCANODET_DEFAULT                 (_AGC_SEQIEN_CCANODET_DEFAULT << 12)         /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_GAINBELOWGAINTHD                 (0x1UL << 13)                                /**< GAINBELOWGAINTHD Interrupt Enable           */
#define _AGC_SEQIEN_GAINBELOWGAINTHD_SHIFT          13                                           /**< Shift value for AGC_GAINBELOWGAINTHD        */
#define _AGC_SEQIEN_GAINBELOWGAINTHD_MASK           0x2000UL                                     /**< Bit mask for AGC_GAINBELOWGAINTHD           */
#define _AGC_SEQIEN_GAINBELOWGAINTHD_DEFAULT        0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_GAINBELOWGAINTHD_DEFAULT         (_AGC_SEQIEN_GAINBELOWGAINTHD_DEFAULT << 13) /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_GAINUPDATEFRZ                    (0x1UL << 14)                                /**< AGC gain update frozen int Enable           */
#define _AGC_SEQIEN_GAINUPDATEFRZ_SHIFT             14                                           /**< Shift value for AGC_GAINUPDATEFRZ           */
#define _AGC_SEQIEN_GAINUPDATEFRZ_MASK              0x4000UL                                     /**< Bit mask for AGC_GAINUPDATEFRZ              */
#define _AGC_SEQIEN_GAINUPDATEFRZ_DEFAULT           0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_GAINUPDATEFRZ_DEFAULT            (_AGC_SEQIEN_GAINUPDATEFRZ_DEFAULT << 14)    /**< Shifted mode DEFAULT for AGC_SEQIEN         */

/* Bit fields for AGC RSSIABSTHR */
#define _AGC_RSSIABSTHR_RESETVALUE                  0x00000000UL                                 /**< Default value for AGC_RSSIABSTHR            */
#define _AGC_RSSIABSTHR_MASK                        0x0000FFFFUL                                 /**< Mask for AGC_RSSIABSTHR                     */
#define _AGC_RSSIABSTHR_RSSIHIGHTHRSH_SHIFT         0                                            /**< Shift value for AGC_RSSIHIGHTHRSH           */
#define _AGC_RSSIABSTHR_RSSIHIGHTHRSH_MASK          0xFFUL                                       /**< Bit mask for AGC_RSSIHIGHTHRSH              */
#define _AGC_RSSIABSTHR_RSSIHIGHTHRSH_DEFAULT       0x00000000UL                                 /**< Mode DEFAULT for AGC_RSSIABSTHR             */
#define AGC_RSSIABSTHR_RSSIHIGHTHRSH_DEFAULT        (_AGC_RSSIABSTHR_RSSIHIGHTHRSH_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_RSSIABSTHR     */
#define _AGC_RSSIABSTHR_RSSILOWTHRSH_SHIFT          8                                            /**< Shift value for AGC_RSSILOWTHRSH            */
#define _AGC_RSSIABSTHR_RSSILOWTHRSH_MASK           0xFF00UL                                     /**< Bit mask for AGC_RSSILOWTHRSH               */
#define _AGC_RSSIABSTHR_RSSILOWTHRSH_DEFAULT        0x00000000UL                                 /**< Mode DEFAULT for AGC_RSSIABSTHR             */
#define AGC_RSSIABSTHR_RSSILOWTHRSH_DEFAULT         (_AGC_RSSIABSTHR_RSSILOWTHRSH_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_RSSIABSTHR     */

/* Bit fields for AGC LNABOOST */
#define _AGC_LNABOOST_RESETVALUE                    0x000001FEUL                               /**< Default value for AGC_LNABOOST              */
#define _AGC_LNABOOST_MASK                          0x000001FFUL                               /**< Mask for AGC_LNABOOST                       */
#define AGC_LNABOOST_BOOSTLNA                       (0x1UL << 0)                               /**< LNA GAIN BOOST mode                         */
#define _AGC_LNABOOST_BOOSTLNA_SHIFT                0                                          /**< Shift value for AGC_BOOSTLNA                */
#define _AGC_LNABOOST_BOOSTLNA_MASK                 0x1UL                                      /**< Bit mask for AGC_BOOSTLNA                   */
#define _AGC_LNABOOST_BOOSTLNA_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for AGC_LNABOOST               */
#define AGC_LNABOOST_BOOSTLNA_DEFAULT               (_AGC_LNABOOST_BOOSTLNA_DEFAULT << 0)      /**< Shifted mode DEFAULT for AGC_LNABOOST       */
#define _AGC_LNABOOST_LNABWADJ_SHIFT                1                                          /**< Shift value for AGC_LNABWADJ                */
#define _AGC_LNABOOST_LNABWADJ_MASK                 0x1EUL                                     /**< Bit mask for AGC_LNABWADJ                   */
#define _AGC_LNABOOST_LNABWADJ_DEFAULT              0x0000000FUL                               /**< Mode DEFAULT for AGC_LNABOOST               */
#define AGC_LNABOOST_LNABWADJ_DEFAULT               (_AGC_LNABOOST_LNABWADJ_DEFAULT << 1)      /**< Shifted mode DEFAULT for AGC_LNABOOST       */
#define _AGC_LNABOOST_LNABWADJBOOST_SHIFT           5                                          /**< Shift value for AGC_LNABWADJBOOST           */
#define _AGC_LNABOOST_LNABWADJBOOST_MASK            0x1E0UL                                    /**< Bit mask for AGC_LNABWADJBOOST              */
#define _AGC_LNABOOST_LNABWADJBOOST_DEFAULT         0x0000000FUL                               /**< Mode DEFAULT for AGC_LNABOOST               */
#define AGC_LNABOOST_LNABWADJBOOST_DEFAULT          (_AGC_LNABOOST_LNABWADJBOOST_DEFAULT << 5) /**< Shifted mode DEFAULT for AGC_LNABOOST       */

/* Bit fields for AGC ANTDIV */
#define _AGC_ANTDIV_RESETVALUE                      0x00000000UL                                /**< Default value for AGC_ANTDIV                */
#define _AGC_ANTDIV_MASK                            0x000003FFUL                                /**< Mask for AGC_ANTDIV                         */
#define _AGC_ANTDIV_GAINMODE_SHIFT                  0                                           /**< Shift value for AGC_GAINMODE                */
#define _AGC_ANTDIV_GAINMODE_MASK                   0x3UL                                       /**< Bit mask for AGC_GAINMODE                   */
#define _AGC_ANTDIV_GAINMODE_DEFAULT                0x00000000UL                                /**< Mode DEFAULT for AGC_ANTDIV                 */
#define _AGC_ANTDIV_GAINMODE_DISABLE                0x00000000UL                                /**< Mode DISABLE for AGC_ANTDIV                 */
#define _AGC_ANTDIV_GAINMODE_SINGLE_PACKET          0x00000001UL                                /**< Mode SINGLE_PACKET for AGC_ANTDIV           */
#define _AGC_ANTDIV_GAINMODE_ALWAYS                 0x00000002UL                                /**< Mode ALWAYS for AGC_ANTDIV                  */
#define AGC_ANTDIV_GAINMODE_DEFAULT                 (_AGC_ANTDIV_GAINMODE_DEFAULT << 0)         /**< Shifted mode DEFAULT for AGC_ANTDIV         */
#define AGC_ANTDIV_GAINMODE_DISABLE                 (_AGC_ANTDIV_GAINMODE_DISABLE << 0)         /**< Shifted mode DISABLE for AGC_ANTDIV         */
#define AGC_ANTDIV_GAINMODE_SINGLE_PACKET           (_AGC_ANTDIV_GAINMODE_SINGLE_PACKET << 0)   /**< Shifted mode SINGLE_PACKET for AGC_ANTDIV   */
#define AGC_ANTDIV_GAINMODE_ALWAYS                  (_AGC_ANTDIV_GAINMODE_ALWAYS << 0)          /**< Shifted mode ALWAYS for AGC_ANTDIV          */
#define _AGC_ANTDIV_DEBOUNCECNTTHD_SHIFT            2                                           /**< Shift value for AGC_DEBOUNCECNTTHD          */
#define _AGC_ANTDIV_DEBOUNCECNTTHD_MASK             0x1FCUL                                     /**< Bit mask for AGC_DEBOUNCECNTTHD             */
#define _AGC_ANTDIV_DEBOUNCECNTTHD_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for AGC_ANTDIV                 */
#define AGC_ANTDIV_DEBOUNCECNTTHD_DEFAULT           (_AGC_ANTDIV_DEBOUNCECNTTHD_DEFAULT << 2)   /**< Shifted mode DEFAULT for AGC_ANTDIV         */
#define AGC_ANTDIV_DISRSSIANTDIVFIX                 (0x1UL << 9)                                /**< Disables RSSI fix for antenna diversity     */
#define _AGC_ANTDIV_DISRSSIANTDIVFIX_SHIFT          9                                           /**< Shift value for AGC_DISRSSIANTDIVFIX        */
#define _AGC_ANTDIV_DISRSSIANTDIVFIX_MASK           0x200UL                                     /**< Bit mask for AGC_DISRSSIANTDIVFIX           */
#define _AGC_ANTDIV_DISRSSIANTDIVFIX_DEFAULT        0x00000000UL                                /**< Mode DEFAULT for AGC_ANTDIV                 */
#define AGC_ANTDIV_DISRSSIANTDIVFIX_DEFAULT         (_AGC_ANTDIV_DISRSSIANTDIVFIX_DEFAULT << 9) /**< Shifted mode DEFAULT for AGC_ANTDIV         */

/* Bit fields for AGC DUALRFPKDTHD0 */
#define _AGC_DUALRFPKDTHD0_RESETVALUE               0x000A0001UL                                    /**< Default value for AGC_DUALRFPKDTHD0         */
#define _AGC_DUALRFPKDTHD0_MASK                     0x0FFF0FFFUL                                    /**< Mask for AGC_DUALRFPKDTHD0                  */
#define _AGC_DUALRFPKDTHD0_RFPKDLOWTHD0_SHIFT       0                                               /**< Shift value for AGC_RFPKDLOWTHD0            */
#define _AGC_DUALRFPKDTHD0_RFPKDLOWTHD0_MASK        0xFFFUL                                         /**< Bit mask for AGC_RFPKDLOWTHD0               */
#define _AGC_DUALRFPKDTHD0_RFPKDLOWTHD0_DEFAULT     0x00000001UL                                    /**< Mode DEFAULT for AGC_DUALRFPKDTHD0          */
#define AGC_DUALRFPKDTHD0_RFPKDLOWTHD0_DEFAULT      (_AGC_DUALRFPKDTHD0_RFPKDLOWTHD0_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_DUALRFPKDTHD0  */
#define _AGC_DUALRFPKDTHD0_RFPKDLOWTHD1_SHIFT       16                                              /**< Shift value for AGC_RFPKDLOWTHD1            */
#define _AGC_DUALRFPKDTHD0_RFPKDLOWTHD1_MASK        0xFFF0000UL                                     /**< Bit mask for AGC_RFPKDLOWTHD1               */
#define _AGC_DUALRFPKDTHD0_RFPKDLOWTHD1_DEFAULT     0x0000000AUL                                    /**< Mode DEFAULT for AGC_DUALRFPKDTHD0          */
#define AGC_DUALRFPKDTHD0_RFPKDLOWTHD1_DEFAULT      (_AGC_DUALRFPKDTHD0_RFPKDLOWTHD1_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_DUALRFPKDTHD0  */

/* Bit fields for AGC DUALRFPKDTHD1 */
#define _AGC_DUALRFPKDTHD1_RESETVALUE               0x00280001UL                                   /**< Default value for AGC_DUALRFPKDTHD1         */
#define _AGC_DUALRFPKDTHD1_MASK                     0x0FFF0FFFUL                                   /**< Mask for AGC_DUALRFPKDTHD1                  */
#define _AGC_DUALRFPKDTHD1_RFPKDHITHD0_SHIFT        0                                              /**< Shift value for AGC_RFPKDHITHD0             */
#define _AGC_DUALRFPKDTHD1_RFPKDHITHD0_MASK         0xFFFUL                                        /**< Bit mask for AGC_RFPKDHITHD0                */
#define _AGC_DUALRFPKDTHD1_RFPKDHITHD0_DEFAULT      0x00000001UL                                   /**< Mode DEFAULT for AGC_DUALRFPKDTHD1          */
#define AGC_DUALRFPKDTHD1_RFPKDHITHD0_DEFAULT       (_AGC_DUALRFPKDTHD1_RFPKDHITHD0_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_DUALRFPKDTHD1  */
#define _AGC_DUALRFPKDTHD1_RFPKDHITHD1_SHIFT        16                                             /**< Shift value for AGC_RFPKDHITHD1             */
#define _AGC_DUALRFPKDTHD1_RFPKDHITHD1_MASK         0xFFF0000UL                                    /**< Bit mask for AGC_RFPKDHITHD1                */
#define _AGC_DUALRFPKDTHD1_RFPKDHITHD1_DEFAULT      0x00000028UL                                   /**< Mode DEFAULT for AGC_DUALRFPKDTHD1          */
#define AGC_DUALRFPKDTHD1_RFPKDHITHD1_DEFAULT       (_AGC_DUALRFPKDTHD1_RFPKDHITHD1_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_DUALRFPKDTHD1  */

/* Bit fields for AGC SPARE */
#define _AGC_SPARE_RESETVALUE                       0x00000000UL                        /**< Default value for AGC_SPARE                 */
#define _AGC_SPARE_MASK                             0x000000FFUL                        /**< Mask for AGC_SPARE                          */
#define _AGC_SPARE_SPAREREG_SHIFT                   0                                   /**< Shift value for AGC_SPAREREG                */
#define _AGC_SPARE_SPAREREG_MASK                    0xFFUL                              /**< Bit mask for AGC_SPAREREG                   */
#define _AGC_SPARE_SPAREREG_DEFAULT                 0x00000000UL                        /**< Mode DEFAULT for AGC_SPARE                  */
#define AGC_SPARE_SPAREREG_DEFAULT                  (_AGC_SPARE_SPAREREG_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_SPARE          */

/** @} End of group EFR32FG23_AGC_BitFields */
/** @} End of group EFR32FG23_AGC */
/** @} End of group Parts */

#endif /* EFR32FG23_AGC_H */
