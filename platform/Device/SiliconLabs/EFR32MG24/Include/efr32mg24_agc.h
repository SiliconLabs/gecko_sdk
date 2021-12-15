/**************************************************************************//**
 * @file
 * @brief EFR32MG24 AGC register and bit field definitions
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
#ifndef EFR32MG24_AGC_H
#define EFR32MG24_AGC_H
#define AGC_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32MG24_AGC AGC
 * @{
 * @brief EFR32MG24 AGC Register Declaration.
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
  uint32_t       RESERVED3[4U];                 /**< Reserved for future use                            */
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
  __IOM uint32_t PNRFFILT0;                     /**< PN RF attenuation code group 0                     */
  __IOM uint32_t PNRFFILT1;                     /**< PN RF attenuation code group 1                     */
  __IOM uint32_t PNRFFILT2;                     /**< PN RF attenuation code group 2                     */
  __IOM uint32_t PNRFFILT3;                     /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFFILT4;                     /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFFILT5;                     /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFFILT6;                     /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFFILT7;                     /**< PN RF attenuation code group 3                     */
  __IOM uint32_t FENOTCHATT0;                   /**< FE Notch attenuation code group 0                  */
  __IOM uint32_t FENOTCHATT1;                   /**< FE Notch attenuation code group 1                  */
  __IOM uint32_t FENOTCHATT2;                   /**< FE Notch attenuation code group 2                  */
  __IOM uint32_t FENOTCHATT3;                   /**< FE Notch attenuation code group 3                  */
  __IOM uint32_t FENOTCHATT4;                   /**< FE Notch attenuation code group 4                  */
  __IOM uint32_t FENOTCHATT5;                   /**< FE Notch attenuation code group 5                  */
  __IOM uint32_t FENOTCHATT6;                   /**< FE Notch attenuation code group 6                  */
  __IOM uint32_t FENOTCHATT7;                   /**< FE Notch attenuation code group 7                  */
  __IOM uint32_t FENOTCHATT8;                   /**< FE Notch attenuation code group 8                  */
  __IOM uint32_t FENOTCHATT9;                   /**< FE Notch attenuation code group 9                  */
  __IOM uint32_t FENOTCHATT10;                  /**< FE Notch attenuation code group 10                 */
  __IOM uint32_t FENOTCHATT11;                  /**< FE Notch attenuation code group 11                 */
  __IOM uint32_t FENOTCHFILT0;                  /**< FE Notch filter code group 0                       */
  __IOM uint32_t FENOTCHFILT1;                  /**< FE Notch filter code group 1                       */
  __IOM uint32_t FENOTCHFILT2;                  /**< FE Notch filter code group 2                       */
  __IOM uint32_t FENOTCHFILT3;                  /**< FE Notch filter code group 3                       */
  __IOM uint32_t FENOTCHFILT4;                  /**< FE Notch filter code group 4                       */
  __IOM uint32_t FENOTCHFILT5;                  /**< FE Notch filter code group 5                       */
  __IOM uint32_t FENOTCHFILT6;                  /**< FE Notch filter code group 6                       */
  __IOM uint32_t FENOTCHFILT7;                  /**< FE Notch filter code group 7                       */
  __IOM uint32_t FENOTCHFILT8;                  /**< FE Notch filter code group 8                       */
  __IOM uint32_t FENOTCHFILT9;                  /**< FE Notch filter code group 9                       */
  __IOM uint32_t FENOTCHFILT10;                 /**< FE Notch filter code group 10                      */
  __IOM uint32_t FENOTCHFILT11;                 /**< FE Notch filter code group 11                      */
  __IM uint32_t  CCADEBUG;                      /**< CCA debug register                                 */
  uint32_t       RESERVED4[935U];               /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP Version                                         */
  __IOM uint32_t EN_SET;                        /**< Enable peripheral clock to this module             */
  __IM uint32_t  STATUS0_SET;                   /**< Status register 0                                  */
  __IM uint32_t  STATUS1_SET;                   /**< Status register 1                                  */
  __IM uint32_t  STATUS2_SET;                   /**< Status register 2                                  */
  uint32_t       RESERVED5[1U];                 /**< Reserved for future use                            */
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
  uint32_t       RESERVED6[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t IF_SET;                        /**< Interrupt Flags Register                           */
  __IOM uint32_t IEN_SET;                       /**< Interrupt Enable Register                          */
  uint32_t       RESERVED7[1U];                 /**< Reserved for future use                            */
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
  uint32_t       RESERVED8[4U];                 /**< Reserved for future use                            */
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
  __IOM uint32_t PNRFFILT0_SET;                 /**< PN RF attenuation code group 0                     */
  __IOM uint32_t PNRFFILT1_SET;                 /**< PN RF attenuation code group 1                     */
  __IOM uint32_t PNRFFILT2_SET;                 /**< PN RF attenuation code group 2                     */
  __IOM uint32_t PNRFFILT3_SET;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFFILT4_SET;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFFILT5_SET;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFFILT6_SET;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFFILT7_SET;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t FENOTCHATT0_SET;               /**< FE Notch attenuation code group 0                  */
  __IOM uint32_t FENOTCHATT1_SET;               /**< FE Notch attenuation code group 1                  */
  __IOM uint32_t FENOTCHATT2_SET;               /**< FE Notch attenuation code group 2                  */
  __IOM uint32_t FENOTCHATT3_SET;               /**< FE Notch attenuation code group 3                  */
  __IOM uint32_t FENOTCHATT4_SET;               /**< FE Notch attenuation code group 4                  */
  __IOM uint32_t FENOTCHATT5_SET;               /**< FE Notch attenuation code group 5                  */
  __IOM uint32_t FENOTCHATT6_SET;               /**< FE Notch attenuation code group 6                  */
  __IOM uint32_t FENOTCHATT7_SET;               /**< FE Notch attenuation code group 7                  */
  __IOM uint32_t FENOTCHATT8_SET;               /**< FE Notch attenuation code group 8                  */
  __IOM uint32_t FENOTCHATT9_SET;               /**< FE Notch attenuation code group 9                  */
  __IOM uint32_t FENOTCHATT10_SET;              /**< FE Notch attenuation code group 10                 */
  __IOM uint32_t FENOTCHATT11_SET;              /**< FE Notch attenuation code group 11                 */
  __IOM uint32_t FENOTCHFILT0_SET;              /**< FE Notch filter code group 0                       */
  __IOM uint32_t FENOTCHFILT1_SET;              /**< FE Notch filter code group 1                       */
  __IOM uint32_t FENOTCHFILT2_SET;              /**< FE Notch filter code group 2                       */
  __IOM uint32_t FENOTCHFILT3_SET;              /**< FE Notch filter code group 3                       */
  __IOM uint32_t FENOTCHFILT4_SET;              /**< FE Notch filter code group 4                       */
  __IOM uint32_t FENOTCHFILT5_SET;              /**< FE Notch filter code group 5                       */
  __IOM uint32_t FENOTCHFILT6_SET;              /**< FE Notch filter code group 6                       */
  __IOM uint32_t FENOTCHFILT7_SET;              /**< FE Notch filter code group 7                       */
  __IOM uint32_t FENOTCHFILT8_SET;              /**< FE Notch filter code group 8                       */
  __IOM uint32_t FENOTCHFILT9_SET;              /**< FE Notch filter code group 9                       */
  __IOM uint32_t FENOTCHFILT10_SET;             /**< FE Notch filter code group 10                      */
  __IOM uint32_t FENOTCHFILT11_SET;             /**< FE Notch filter code group 11                      */
  __IM uint32_t  CCADEBUG_SET;                  /**< CCA debug register                                 */
  uint32_t       RESERVED9[935U];               /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP Version                                         */
  __IOM uint32_t EN_CLR;                        /**< Enable peripheral clock to this module             */
  __IM uint32_t  STATUS0_CLR;                   /**< Status register 0                                  */
  __IM uint32_t  STATUS1_CLR;                   /**< Status register 1                                  */
  __IM uint32_t  STATUS2_CLR;                   /**< Status register 2                                  */
  uint32_t       RESERVED10[1U];                /**< Reserved for future use                            */
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
  uint32_t       RESERVED11[1U];                /**< Reserved for future use                            */
  __IOM uint32_t IF_CLR;                        /**< Interrupt Flags Register                           */
  __IOM uint32_t IEN_CLR;                       /**< Interrupt Enable Register                          */
  uint32_t       RESERVED12[1U];                /**< Reserved for future use                            */
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
  uint32_t       RESERVED13[4U];                /**< Reserved for future use                            */
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
  __IOM uint32_t PNRFFILT0_CLR;                 /**< PN RF attenuation code group 0                     */
  __IOM uint32_t PNRFFILT1_CLR;                 /**< PN RF attenuation code group 1                     */
  __IOM uint32_t PNRFFILT2_CLR;                 /**< PN RF attenuation code group 2                     */
  __IOM uint32_t PNRFFILT3_CLR;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFFILT4_CLR;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFFILT5_CLR;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFFILT6_CLR;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFFILT7_CLR;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t FENOTCHATT0_CLR;               /**< FE Notch attenuation code group 0                  */
  __IOM uint32_t FENOTCHATT1_CLR;               /**< FE Notch attenuation code group 1                  */
  __IOM uint32_t FENOTCHATT2_CLR;               /**< FE Notch attenuation code group 2                  */
  __IOM uint32_t FENOTCHATT3_CLR;               /**< FE Notch attenuation code group 3                  */
  __IOM uint32_t FENOTCHATT4_CLR;               /**< FE Notch attenuation code group 4                  */
  __IOM uint32_t FENOTCHATT5_CLR;               /**< FE Notch attenuation code group 5                  */
  __IOM uint32_t FENOTCHATT6_CLR;               /**< FE Notch attenuation code group 6                  */
  __IOM uint32_t FENOTCHATT7_CLR;               /**< FE Notch attenuation code group 7                  */
  __IOM uint32_t FENOTCHATT8_CLR;               /**< FE Notch attenuation code group 8                  */
  __IOM uint32_t FENOTCHATT9_CLR;               /**< FE Notch attenuation code group 9                  */
  __IOM uint32_t FENOTCHATT10_CLR;              /**< FE Notch attenuation code group 10                 */
  __IOM uint32_t FENOTCHATT11_CLR;              /**< FE Notch attenuation code group 11                 */
  __IOM uint32_t FENOTCHFILT0_CLR;              /**< FE Notch filter code group 0                       */
  __IOM uint32_t FENOTCHFILT1_CLR;              /**< FE Notch filter code group 1                       */
  __IOM uint32_t FENOTCHFILT2_CLR;              /**< FE Notch filter code group 2                       */
  __IOM uint32_t FENOTCHFILT3_CLR;              /**< FE Notch filter code group 3                       */
  __IOM uint32_t FENOTCHFILT4_CLR;              /**< FE Notch filter code group 4                       */
  __IOM uint32_t FENOTCHFILT5_CLR;              /**< FE Notch filter code group 5                       */
  __IOM uint32_t FENOTCHFILT6_CLR;              /**< FE Notch filter code group 6                       */
  __IOM uint32_t FENOTCHFILT7_CLR;              /**< FE Notch filter code group 7                       */
  __IOM uint32_t FENOTCHFILT8_CLR;              /**< FE Notch filter code group 8                       */
  __IOM uint32_t FENOTCHFILT9_CLR;              /**< FE Notch filter code group 9                       */
  __IOM uint32_t FENOTCHFILT10_CLR;             /**< FE Notch filter code group 10                      */
  __IOM uint32_t FENOTCHFILT11_CLR;             /**< FE Notch filter code group 11                      */
  __IM uint32_t  CCADEBUG_CLR;                  /**< CCA debug register                                 */
  uint32_t       RESERVED14[935U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP Version                                         */
  __IOM uint32_t EN_TGL;                        /**< Enable peripheral clock to this module             */
  __IM uint32_t  STATUS0_TGL;                   /**< Status register 0                                  */
  __IM uint32_t  STATUS1_TGL;                   /**< Status register 1                                  */
  __IM uint32_t  STATUS2_TGL;                   /**< Status register 2                                  */
  uint32_t       RESERVED15[1U];                /**< Reserved for future use                            */
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
  uint32_t       RESERVED16[1U];                /**< Reserved for future use                            */
  __IOM uint32_t IF_TGL;                        /**< Interrupt Flags Register                           */
  __IOM uint32_t IEN_TGL;                       /**< Interrupt Enable Register                          */
  uint32_t       RESERVED17[1U];                /**< Reserved for future use                            */
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
  uint32_t       RESERVED18[4U];                /**< Reserved for future use                            */
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
  __IOM uint32_t PNRFFILT0_TGL;                 /**< PN RF attenuation code group 0                     */
  __IOM uint32_t PNRFFILT1_TGL;                 /**< PN RF attenuation code group 1                     */
  __IOM uint32_t PNRFFILT2_TGL;                 /**< PN RF attenuation code group 2                     */
  __IOM uint32_t PNRFFILT3_TGL;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFFILT4_TGL;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFFILT5_TGL;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFFILT6_TGL;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t PNRFFILT7_TGL;                 /**< PN RF attenuation code group 3                     */
  __IOM uint32_t FENOTCHATT0_TGL;               /**< FE Notch attenuation code group 0                  */
  __IOM uint32_t FENOTCHATT1_TGL;               /**< FE Notch attenuation code group 1                  */
  __IOM uint32_t FENOTCHATT2_TGL;               /**< FE Notch attenuation code group 2                  */
  __IOM uint32_t FENOTCHATT3_TGL;               /**< FE Notch attenuation code group 3                  */
  __IOM uint32_t FENOTCHATT4_TGL;               /**< FE Notch attenuation code group 4                  */
  __IOM uint32_t FENOTCHATT5_TGL;               /**< FE Notch attenuation code group 5                  */
  __IOM uint32_t FENOTCHATT6_TGL;               /**< FE Notch attenuation code group 6                  */
  __IOM uint32_t FENOTCHATT7_TGL;               /**< FE Notch attenuation code group 7                  */
  __IOM uint32_t FENOTCHATT8_TGL;               /**< FE Notch attenuation code group 8                  */
  __IOM uint32_t FENOTCHATT9_TGL;               /**< FE Notch attenuation code group 9                  */
  __IOM uint32_t FENOTCHATT10_TGL;              /**< FE Notch attenuation code group 10                 */
  __IOM uint32_t FENOTCHATT11_TGL;              /**< FE Notch attenuation code group 11                 */
  __IOM uint32_t FENOTCHFILT0_TGL;              /**< FE Notch filter code group 0                       */
  __IOM uint32_t FENOTCHFILT1_TGL;              /**< FE Notch filter code group 1                       */
  __IOM uint32_t FENOTCHFILT2_TGL;              /**< FE Notch filter code group 2                       */
  __IOM uint32_t FENOTCHFILT3_TGL;              /**< FE Notch filter code group 3                       */
  __IOM uint32_t FENOTCHFILT4_TGL;              /**< FE Notch filter code group 4                       */
  __IOM uint32_t FENOTCHFILT5_TGL;              /**< FE Notch filter code group 5                       */
  __IOM uint32_t FENOTCHFILT6_TGL;              /**< FE Notch filter code group 6                       */
  __IOM uint32_t FENOTCHFILT7_TGL;              /**< FE Notch filter code group 7                       */
  __IOM uint32_t FENOTCHFILT8_TGL;              /**< FE Notch filter code group 8                       */
  __IOM uint32_t FENOTCHFILT9_TGL;              /**< FE Notch filter code group 9                       */
  __IOM uint32_t FENOTCHFILT10_TGL;             /**< FE Notch filter code group 10                      */
  __IOM uint32_t FENOTCHFILT11_TGL;             /**< FE Notch filter code group 11                      */
  __IM uint32_t  CCADEBUG_TGL;                  /**< CCA debug register                                 */
} AGC_TypeDef;
/** @} End of group EFR32MG24_AGC */

/**************************************************************************//**
 * @addtogroup EFR32MG24_AGC
 * @{
 * @defgroup EFR32MG24_AGC_BitFields AGC Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for AGC IPVERSION */
#define _AGC_IPVERSION_RESETVALUE                      0x00000003UL                            /**< Default value for AGC_IPVERSION             */
#define _AGC_IPVERSION_MASK                            0xFFFFFFFFUL                            /**< Mask for AGC_IPVERSION                      */
#define _AGC_IPVERSION_IPVERSION_SHIFT                 0                                       /**< Shift value for AGC_IPVERSION               */
#define _AGC_IPVERSION_IPVERSION_MASK                  0xFFFFFFFFUL                            /**< Bit mask for AGC_IPVERSION                  */
#define _AGC_IPVERSION_IPVERSION_DEFAULT               0x00000003UL                            /**< Mode DEFAULT for AGC_IPVERSION              */
#define AGC_IPVERSION_IPVERSION_DEFAULT                (_AGC_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_IPVERSION      */

/* Bit fields for AGC EN */
#define _AGC_EN_RESETVALUE                             0x00000000UL                     /**< Default value for AGC_EN                    */
#define _AGC_EN_MASK                                   0x00000001UL                     /**< Mask for AGC_EN                             */
#define AGC_EN_EN                                      (0x1UL << 0)                     /**< Enable peripheral clock to this module      */
#define _AGC_EN_EN_SHIFT                               0                                /**< Shift value for AGC_EN                      */
#define _AGC_EN_EN_MASK                                0x1UL                            /**< Bit mask for AGC_EN                         */
#define _AGC_EN_EN_DEFAULT                             0x00000000UL                     /**< Mode DEFAULT for AGC_EN                     */
#define AGC_EN_EN_DEFAULT                              (_AGC_EN_EN_DEFAULT << 0)        /**< Shifted mode DEFAULT for AGC_EN             */

/* Bit fields for AGC STATUS0 */
#define _AGC_STATUS0_RESETVALUE                        0x00000000UL                            /**< Default value for AGC_STATUS0               */
#define _AGC_STATUS0_MASK                              0x07FFFFFFUL                            /**< Mask for AGC_STATUS0                        */
#define _AGC_STATUS0_GAININDEX_SHIFT                   0                                       /**< Shift value for AGC_GAININDEX               */
#define _AGC_STATUS0_GAININDEX_MASK                    0x3FUL                                  /**< Bit mask for AGC_GAININDEX                  */
#define _AGC_STATUS0_GAININDEX_DEFAULT                 0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_GAININDEX_DEFAULT                  (_AGC_STATUS0_GAININDEX_DEFAULT << 0)   /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define AGC_STATUS0_RFPKDLOWLAT                        (0x1UL << 6)                            /**< RFPKD low Latch                             */
#define _AGC_STATUS0_RFPKDLOWLAT_SHIFT                 6                                       /**< Shift value for AGC_RFPKDLOWLAT             */
#define _AGC_STATUS0_RFPKDLOWLAT_MASK                  0x40UL                                  /**< Bit mask for AGC_RFPKDLOWLAT                */
#define _AGC_STATUS0_RFPKDLOWLAT_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_RFPKDLOWLAT_DEFAULT                (_AGC_STATUS0_RFPKDLOWLAT_DEFAULT << 6) /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define AGC_STATUS0_RFPKDHILAT                         (0x1UL << 7)                            /**< RFPKD hi Latch                              */
#define _AGC_STATUS0_RFPKDHILAT_SHIFT                  7                                       /**< Shift value for AGC_RFPKDHILAT              */
#define _AGC_STATUS0_RFPKDHILAT_MASK                   0x80UL                                  /**< Bit mask for AGC_RFPKDHILAT                 */
#define _AGC_STATUS0_RFPKDHILAT_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_RFPKDHILAT_DEFAULT                 (_AGC_STATUS0_RFPKDHILAT_DEFAULT << 7)  /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define AGC_STATUS0_IFPKDLOLAT                         (0x1UL << 8)                            /**< IFPKD Lo threshold pass Latch               */
#define _AGC_STATUS0_IFPKDLOLAT_SHIFT                  8                                       /**< Shift value for AGC_IFPKDLOLAT              */
#define _AGC_STATUS0_IFPKDLOLAT_MASK                   0x100UL                                 /**< Bit mask for AGC_IFPKDLOLAT                 */
#define _AGC_STATUS0_IFPKDLOLAT_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_IFPKDLOLAT_DEFAULT                 (_AGC_STATUS0_IFPKDLOLAT_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define AGC_STATUS0_IFPKDHILAT                         (0x1UL << 9)                            /**< IFPKD Hi threshold pass Latch               */
#define _AGC_STATUS0_IFPKDHILAT_SHIFT                  9                                       /**< Shift value for AGC_IFPKDHILAT              */
#define _AGC_STATUS0_IFPKDHILAT_MASK                   0x200UL                                 /**< Bit mask for AGC_IFPKDHILAT                 */
#define _AGC_STATUS0_IFPKDHILAT_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_IFPKDHILAT_DEFAULT                 (_AGC_STATUS0_IFPKDHILAT_DEFAULT << 9)  /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define AGC_STATUS0_CCA                                (0x1UL << 10)                           /**< Clear Channel Assessment                    */
#define _AGC_STATUS0_CCA_SHIFT                         10                                      /**< Shift value for AGC_CCA                     */
#define _AGC_STATUS0_CCA_MASK                          0x400UL                                 /**< Bit mask for AGC_CCA                        */
#define _AGC_STATUS0_CCA_DEFAULT                       0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_CCA_DEFAULT                        (_AGC_STATUS0_CCA_DEFAULT << 10)        /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define AGC_STATUS0_GAINOK                             (0x1UL << 11)                           /**< Gain OK                                     */
#define _AGC_STATUS0_GAINOK_SHIFT                      11                                      /**< Shift value for AGC_GAINOK                  */
#define _AGC_STATUS0_GAINOK_MASK                       0x800UL                                 /**< Bit mask for AGC_GAINOK                     */
#define _AGC_STATUS0_GAINOK_DEFAULT                    0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_GAINOK_DEFAULT                     (_AGC_STATUS0_GAINOK_DEFAULT << 11)     /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define _AGC_STATUS0_PGAINDEX_SHIFT                    12                                      /**< Shift value for AGC_PGAINDEX                */
#define _AGC_STATUS0_PGAINDEX_MASK                     0xF000UL                                /**< Bit mask for AGC_PGAINDEX                   */
#define _AGC_STATUS0_PGAINDEX_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_PGAINDEX_DEFAULT                   (_AGC_STATUS0_PGAINDEX_DEFAULT << 12)   /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define _AGC_STATUS0_LNAINDEX_SHIFT                    16                                      /**< Shift value for AGC_LNAINDEX                */
#define _AGC_STATUS0_LNAINDEX_MASK                     0xF0000UL                               /**< Bit mask for AGC_LNAINDEX                   */
#define _AGC_STATUS0_LNAINDEX_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_LNAINDEX_DEFAULT                   (_AGC_STATUS0_LNAINDEX_DEFAULT << 16)   /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define _AGC_STATUS0_PNINDEX_SHIFT                     20                                      /**< Shift value for AGC_PNINDEX                 */
#define _AGC_STATUS0_PNINDEX_MASK                      0x1F00000UL                             /**< Bit mask for AGC_PNINDEX                    */
#define _AGC_STATUS0_PNINDEX_DEFAULT                   0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_PNINDEX_DEFAULT                    (_AGC_STATUS0_PNINDEX_DEFAULT << 20)    /**< Shifted mode DEFAULT for AGC_STATUS0        */
#define _AGC_STATUS0_ADCINDEX_SHIFT                    25                                      /**< Shift value for AGC_ADCINDEX                */
#define _AGC_STATUS0_ADCINDEX_MASK                     0x6000000UL                             /**< Bit mask for AGC_ADCINDEX                   */
#define _AGC_STATUS0_ADCINDEX_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for AGC_STATUS0                */
#define AGC_STATUS0_ADCINDEX_DEFAULT                   (_AGC_STATUS0_ADCINDEX_DEFAULT << 25)   /**< Shifted mode DEFAULT for AGC_STATUS0        */

/* Bit fields for AGC STATUS1 */
#define _AGC_STATUS1_RESETVALUE                        0x00000000UL                                /**< Default value for AGC_STATUS1               */
#define _AGC_STATUS1_MASK                              0x3FFFFEFFUL                                /**< Mask for AGC_STATUS1                        */
#define _AGC_STATUS1_RFPKDLOWLATCNT_SHIFT              18                                          /**< Shift value for AGC_RFPKDLOWLATCNT          */
#define _AGC_STATUS1_RFPKDLOWLATCNT_MASK               0x3FFC0000UL                                /**< Bit mask for AGC_RFPKDLOWLATCNT             */
#define _AGC_STATUS1_RFPKDLOWLATCNT_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for AGC_STATUS1                */
#define AGC_STATUS1_RFPKDLOWLATCNT_DEFAULT             (_AGC_STATUS1_RFPKDLOWLATCNT_DEFAULT << 18) /**< Shifted mode DEFAULT for AGC_STATUS1        */

/* Bit fields for AGC STATUS2 */
#define _AGC_STATUS2_RESETVALUE                        0x00000000UL                              /**< Default value for AGC_STATUS2               */
#define _AGC_STATUS2_MASK                              0xFFFF4FFFUL                              /**< Mask for AGC_STATUS2                        */
#define _AGC_STATUS2_RFPKDHILATCNT_SHIFT               0                                         /**< Shift value for AGC_RFPKDHILATCNT           */
#define _AGC_STATUS2_RFPKDHILATCNT_MASK                0xFFFUL                                   /**< Bit mask for AGC_RFPKDHILATCNT              */
#define _AGC_STATUS2_RFPKDHILATCNT_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for AGC_STATUS2                */
#define AGC_STATUS2_RFPKDHILATCNT_DEFAULT              (_AGC_STATUS2_RFPKDHILATCNT_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_STATUS2        */
#define AGC_STATUS2_PNDWNUP                            (0x1UL << 14)                             /**< Allow PN GAIN UP                            */
#define _AGC_STATUS2_PNDWNUP_SHIFT                     14                                        /**< Shift value for AGC_PNDWNUP                 */
#define _AGC_STATUS2_PNDWNUP_MASK                      0x4000UL                                  /**< Bit mask for AGC_PNDWNUP                    */
#define _AGC_STATUS2_PNDWNUP_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for AGC_STATUS2                */
#define AGC_STATUS2_PNDWNUP_DEFAULT                    (_AGC_STATUS2_PNDWNUP_DEFAULT << 14)      /**< Shifted mode DEFAULT for AGC_STATUS2        */
#define _AGC_STATUS2_RFPKDPRDCNT_SHIFT                 16                                        /**< Shift value for AGC_RFPKDPRDCNT             */
#define _AGC_STATUS2_RFPKDPRDCNT_MASK                  0xFFFF0000UL                              /**< Bit mask for AGC_RFPKDPRDCNT                */
#define _AGC_STATUS2_RFPKDPRDCNT_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for AGC_STATUS2                */
#define AGC_STATUS2_RFPKDPRDCNT_DEFAULT                (_AGC_STATUS2_RFPKDPRDCNT_DEFAULT << 16)  /**< Shifted mode DEFAULT for AGC_STATUS2        */

/* Bit fields for AGC RSSI */
#define _AGC_RSSI_RESETVALUE                           0x00008000UL                      /**< Default value for AGC_RSSI                  */
#define _AGC_RSSI_MASK                                 0x0000FFC0UL                      /**< Mask for AGC_RSSI                           */
#define _AGC_RSSI_RSSIFRAC_SHIFT                       6                                 /**< Shift value for AGC_RSSIFRAC                */
#define _AGC_RSSI_RSSIFRAC_MASK                        0xC0UL                            /**< Bit mask for AGC_RSSIFRAC                   */
#define _AGC_RSSI_RSSIFRAC_DEFAULT                     0x00000000UL                      /**< Mode DEFAULT for AGC_RSSI                   */
#define AGC_RSSI_RSSIFRAC_DEFAULT                      (_AGC_RSSI_RSSIFRAC_DEFAULT << 6) /**< Shifted mode DEFAULT for AGC_RSSI           */
#define _AGC_RSSI_RSSIINT_SHIFT                        8                                 /**< Shift value for AGC_RSSIINT                 */
#define _AGC_RSSI_RSSIINT_MASK                         0xFF00UL                          /**< Bit mask for AGC_RSSIINT                    */
#define _AGC_RSSI_RSSIINT_DEFAULT                      0x00000080UL                      /**< Mode DEFAULT for AGC_RSSI                   */
#define AGC_RSSI_RSSIINT_DEFAULT                       (_AGC_RSSI_RSSIINT_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_RSSI           */

/* Bit fields for AGC FRAMERSSI */
#define _AGC_FRAMERSSI_RESETVALUE                      0x00008000UL                                /**< Default value for AGC_FRAMERSSI             */
#define _AGC_FRAMERSSI_MASK                            0x0000FFC0UL                                /**< Mask for AGC_FRAMERSSI                      */
#define _AGC_FRAMERSSI_FRAMERSSIFRAC_SHIFT             6                                           /**< Shift value for AGC_FRAMERSSIFRAC           */
#define _AGC_FRAMERSSI_FRAMERSSIFRAC_MASK              0xC0UL                                      /**< Bit mask for AGC_FRAMERSSIFRAC              */
#define _AGC_FRAMERSSI_FRAMERSSIFRAC_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for AGC_FRAMERSSI              */
#define AGC_FRAMERSSI_FRAMERSSIFRAC_DEFAULT            (_AGC_FRAMERSSI_FRAMERSSIFRAC_DEFAULT << 6) /**< Shifted mode DEFAULT for AGC_FRAMERSSI      */
#define _AGC_FRAMERSSI_FRAMERSSIINT_SHIFT              8                                           /**< Shift value for AGC_FRAMERSSIINT            */
#define _AGC_FRAMERSSI_FRAMERSSIINT_MASK               0xFF00UL                                    /**< Bit mask for AGC_FRAMERSSIINT               */
#define _AGC_FRAMERSSI_FRAMERSSIINT_DEFAULT            0x00000080UL                                /**< Mode DEFAULT for AGC_FRAMERSSI              */
#define AGC_FRAMERSSI_FRAMERSSIINT_DEFAULT             (_AGC_FRAMERSSI_FRAMERSSIINT_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FRAMERSSI      */

/* Bit fields for AGC CTRL0 */
#define _AGC_CTRL0_RESETVALUE                          0x2132727FUL                                  /**< Default value for AGC_CTRL0                 */
#define _AGC_CTRL0_MASK                                0xFFFFFFFFUL                                  /**< Mask for AGC_CTRL0                          */
#define _AGC_CTRL0_PWRTARGET_SHIFT                     0                                             /**< Shift value for AGC_PWRTARGET               */
#define _AGC_CTRL0_PWRTARGET_MASK                      0xFFUL                                        /**< Bit mask for AGC_PWRTARGET                  */
#define _AGC_CTRL0_PWRTARGET_DEFAULT                   0x0000007FUL                                  /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_PWRTARGET_DEFAULT                    (_AGC_CTRL0_PWRTARGET_DEFAULT << 0)           /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define _AGC_CTRL0_MODE_SHIFT                          8                                             /**< Shift value for AGC_MODE                    */
#define _AGC_CTRL0_MODE_MASK                           0x700UL                                       /**< Bit mask for AGC_MODE                       */
#define _AGC_CTRL0_MODE_DEFAULT                        0x00000002UL                                  /**< Mode DEFAULT for AGC_CTRL0                  */
#define _AGC_CTRL0_MODE_CONT                           0x00000000UL                                  /**< Mode CONT for AGC_CTRL0                     */
#define _AGC_CTRL0_MODE_LOCKPREDET                     0x00000001UL                                  /**< Mode LOCKPREDET for AGC_CTRL0               */
#define _AGC_CTRL0_MODE_LOCKFRAMEDET                   0x00000002UL                                  /**< Mode LOCKFRAMEDET for AGC_CTRL0             */
#define _AGC_CTRL0_MODE_LOCKDSA                        0x00000003UL                                  /**< Mode LOCKDSA for AGC_CTRL0                  */
#define AGC_CTRL0_MODE_DEFAULT                         (_AGC_CTRL0_MODE_DEFAULT << 8)                /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_MODE_CONT                            (_AGC_CTRL0_MODE_CONT << 8)                   /**< Shifted mode CONT for AGC_CTRL0             */
#define AGC_CTRL0_MODE_LOCKPREDET                      (_AGC_CTRL0_MODE_LOCKPREDET << 8)             /**< Shifted mode LOCKPREDET for AGC_CTRL0       */
#define AGC_CTRL0_MODE_LOCKFRAMEDET                    (_AGC_CTRL0_MODE_LOCKFRAMEDET << 8)           /**< Shifted mode LOCKFRAMEDET for AGC_CTRL0     */
#define AGC_CTRL0_MODE_LOCKDSA                         (_AGC_CTRL0_MODE_LOCKDSA << 8)                /**< Shifted mode LOCKDSA for AGC_CTRL0          */
#define _AGC_CTRL0_RSSISHIFT_SHIFT                     11                                            /**< Shift value for AGC_RSSISHIFT               */
#define _AGC_CTRL0_RSSISHIFT_MASK                      0x7F800UL                                     /**< Bit mask for AGC_RSSISHIFT                  */
#define _AGC_CTRL0_RSSISHIFT_DEFAULT                   0x0000004EUL                                  /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_RSSISHIFT_DEFAULT                    (_AGC_CTRL0_RSSISHIFT_DEFAULT << 11)          /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_DISCFLOOPADJ                         (0x1UL << 19)                                 /**< Disable gain adjustment by CFLOOP           */
#define _AGC_CTRL0_DISCFLOOPADJ_SHIFT                  19                                            /**< Shift value for AGC_DISCFLOOPADJ            */
#define _AGC_CTRL0_DISCFLOOPADJ_MASK                   0x80000UL                                     /**< Bit mask for AGC_DISCFLOOPADJ               */
#define _AGC_CTRL0_DISCFLOOPADJ_DEFAULT                0x00000000UL                                  /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_DISCFLOOPADJ_DEFAULT                 (_AGC_CTRL0_DISCFLOOPADJ_DEFAULT << 19)       /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_CFLOOPNFADJ                          (0x1UL << 20)                                 /**< Enable NF correction term in SL             */
#define _AGC_CTRL0_CFLOOPNFADJ_SHIFT                   20                                            /**< Shift value for AGC_CFLOOPNFADJ             */
#define _AGC_CTRL0_CFLOOPNFADJ_MASK                    0x100000UL                                    /**< Bit mask for AGC_CFLOOPNFADJ                */
#define _AGC_CTRL0_CFLOOPNFADJ_DEFAULT                 0x00000001UL                                  /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_CFLOOPNFADJ_DEFAULT                  (_AGC_CTRL0_CFLOOPNFADJ_DEFAULT << 20)        /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_CFLOOPNEWCALC                        (0x1UL << 21)                                 /**< Enable new wanted gain calculation in SL    */
#define _AGC_CTRL0_CFLOOPNEWCALC_SHIFT                 21                                            /**< Shift value for AGC_CFLOOPNEWCALC           */
#define _AGC_CTRL0_CFLOOPNEWCALC_MASK                  0x200000UL                                    /**< Bit mask for AGC_CFLOOPNEWCALC              */
#define _AGC_CTRL0_CFLOOPNEWCALC_DEFAULT               0x00000001UL                                  /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_CFLOOPNEWCALC_DEFAULT                (_AGC_CTRL0_CFLOOPNEWCALC_DEFAULT << 21)      /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_DISRESETCHPWR                        (0x1UL << 22)                                 /**< Disable Reset of CHPWR                      */
#define _AGC_CTRL0_DISRESETCHPWR_SHIFT                 22                                            /**< Shift value for AGC_DISRESETCHPWR           */
#define _AGC_CTRL0_DISRESETCHPWR_MASK                  0x400000UL                                    /**< Bit mask for AGC_DISRESETCHPWR              */
#define _AGC_CTRL0_DISRESETCHPWR_DEFAULT               0x00000000UL                                  /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_DISRESETCHPWR_DEFAULT                (_AGC_CTRL0_DISRESETCHPWR_DEFAULT << 22)      /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_ADCATTENMODE                         (0x1UL << 23)                                 /**< ADC Attenuator mode                         */
#define _AGC_CTRL0_ADCATTENMODE_SHIFT                  23                                            /**< Shift value for AGC_ADCATTENMODE            */
#define _AGC_CTRL0_ADCATTENMODE_MASK                   0x800000UL                                    /**< Bit mask for AGC_ADCATTENMODE               */
#define _AGC_CTRL0_ADCATTENMODE_DEFAULT                0x00000000UL                                  /**< Mode DEFAULT for AGC_CTRL0                  */
#define _AGC_CTRL0_ADCATTENMODE_DISABLE                0x00000000UL                                  /**< Mode DISABLE for AGC_CTRL0                  */
#define _AGC_CTRL0_ADCATTENMODE_NOTMAXGAIN             0x00000001UL                                  /**< Mode NOTMAXGAIN for AGC_CTRL0               */
#define AGC_CTRL0_ADCATTENMODE_DEFAULT                 (_AGC_CTRL0_ADCATTENMODE_DEFAULT << 23)       /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_ADCATTENMODE_DISABLE                 (_AGC_CTRL0_ADCATTENMODE_DISABLE << 23)       /**< Shifted mode DISABLE for AGC_CTRL0          */
#define AGC_CTRL0_ADCATTENMODE_NOTMAXGAIN              (_AGC_CTRL0_ADCATTENMODE_NOTMAXGAIN << 23)    /**< Shifted mode NOTMAXGAIN for AGC_CTRL0       */
#define AGC_CTRL0_FENOTCHMODESEL                       (0x1UL << 24)                                 /**< FE notch mode select                        */
#define _AGC_CTRL0_FENOTCHMODESEL_SHIFT                24                                            /**< Shift value for AGC_FENOTCHMODESEL          */
#define _AGC_CTRL0_FENOTCHMODESEL_MASK                 0x1000000UL                                   /**< Bit mask for AGC_FENOTCHMODESEL             */
#define _AGC_CTRL0_FENOTCHMODESEL_DEFAULT              0x00000001UL                                  /**< Mode DEFAULT for AGC_CTRL0                  */
#define _AGC_CTRL0_FENOTCHMODESEL_FENOTCHFILT          0x00000000UL                                  /**< Mode FENOTCHFILT for AGC_CTRL0              */
#define _AGC_CTRL0_FENOTCHMODESEL_FENOTCHATTN          0x00000001UL                                  /**< Mode FENOTCHATTN for AGC_CTRL0              */
#define AGC_CTRL0_FENOTCHMODESEL_DEFAULT               (_AGC_CTRL0_FENOTCHMODESEL_DEFAULT << 24)     /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_FENOTCHMODESEL_FENOTCHFILT           (_AGC_CTRL0_FENOTCHMODESEL_FENOTCHFILT << 24) /**< Shifted mode FENOTCHFILT for AGC_CTRL0      */
#define AGC_CTRL0_FENOTCHMODESEL_FENOTCHATTN           (_AGC_CTRL0_FENOTCHMODESEL_FENOTCHATTN << 24) /**< Shifted mode FENOTCHATTN for AGC_CTRL0      */
#define _AGC_CTRL0_ADCATTENCODE_SHIFT                  25                                            /**< Shift value for AGC_ADCATTENCODE            */
#define _AGC_CTRL0_ADCATTENCODE_MASK                   0x6000000UL                                   /**< Bit mask for AGC_ADCATTENCODE               */
#define _AGC_CTRL0_ADCATTENCODE_DEFAULT                0x00000000UL                                  /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_ADCATTENCODE_DEFAULT                 (_AGC_CTRL0_ADCATTENCODE_DEFAULT << 25)       /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_ENRSSIRESET                          (0x1UL << 27)                                 /**< Enables reset of RSSI and CCA               */
#define _AGC_CTRL0_ENRSSIRESET_SHIFT                   27                                            /**< Shift value for AGC_ENRSSIRESET             */
#define _AGC_CTRL0_ENRSSIRESET_MASK                    0x8000000UL                                   /**< Bit mask for AGC_ENRSSIRESET                */
#define _AGC_CTRL0_ENRSSIRESET_DEFAULT                 0x00000000UL                                  /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_ENRSSIRESET_DEFAULT                  (_AGC_CTRL0_ENRSSIRESET_DEFAULT << 27)        /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_DSADISCFLOOP                         (0x1UL << 28)                                 /**< Disable channel filter loop                 */
#define _AGC_CTRL0_DSADISCFLOOP_SHIFT                  28                                            /**< Shift value for AGC_DSADISCFLOOP            */
#define _AGC_CTRL0_DSADISCFLOOP_MASK                   0x10000000UL                                  /**< Bit mask for AGC_DSADISCFLOOP               */
#define _AGC_CTRL0_DSADISCFLOOP_DEFAULT                0x00000000UL                                  /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_DSADISCFLOOP_DEFAULT                 (_AGC_CTRL0_DSADISCFLOOP_DEFAULT << 28)       /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_DISPNGAINUP                          (0x1UL << 29)                                 /**< Disable PN gain increase                    */
#define _AGC_CTRL0_DISPNGAINUP_SHIFT                   29                                            /**< Shift value for AGC_DISPNGAINUP             */
#define _AGC_CTRL0_DISPNGAINUP_MASK                    0x20000000UL                                  /**< Bit mask for AGC_DISPNGAINUP                */
#define _AGC_CTRL0_DISPNGAINUP_DEFAULT                 0x00000001UL                                  /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_DISPNGAINUP_DEFAULT                  (_AGC_CTRL0_DISPNGAINUP_DEFAULT << 29)        /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_DISPNDWNCOMP                         (0x1UL << 30)                                 /**< Disable PN gain decrease compensation       */
#define _AGC_CTRL0_DISPNDWNCOMP_SHIFT                  30                                            /**< Shift value for AGC_DISPNDWNCOMP            */
#define _AGC_CTRL0_DISPNDWNCOMP_MASK                   0x40000000UL                                  /**< Bit mask for AGC_DISPNDWNCOMP               */
#define _AGC_CTRL0_DISPNDWNCOMP_DEFAULT                0x00000000UL                                  /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_DISPNDWNCOMP_DEFAULT                 (_AGC_CTRL0_DISPNDWNCOMP_DEFAULT << 30)       /**< Shifted mode DEFAULT for AGC_CTRL0          */
#define AGC_CTRL0_AGCRST                               (0x1UL << 31)                                 /**< AGC reset                                   */
#define _AGC_CTRL0_AGCRST_SHIFT                        31                                            /**< Shift value for AGC_AGCRST                  */
#define _AGC_CTRL0_AGCRST_MASK                         0x80000000UL                                  /**< Bit mask for AGC_AGCRST                     */
#define _AGC_CTRL0_AGCRST_DEFAULT                      0x00000000UL                                  /**< Mode DEFAULT for AGC_CTRL0                  */
#define AGC_CTRL0_AGCRST_DEFAULT                       (_AGC_CTRL0_AGCRST_DEFAULT << 31)             /**< Shifted mode DEFAULT for AGC_CTRL0          */

/* Bit fields for AGC CTRL1 */
#define _AGC_CTRL1_RESETVALUE                          0x00001300UL                             /**< Default value for AGC_CTRL1                 */
#define _AGC_CTRL1_MASK                                0x0007FFFFUL                             /**< Mask for AGC_CTRL1                          */
#define _AGC_CTRL1_CCATHRSH_SHIFT                      0                                        /**< Shift value for AGC_CCATHRSH                */
#define _AGC_CTRL1_CCATHRSH_MASK                       0xFFUL                                   /**< Bit mask for AGC_CCATHRSH                   */
#define _AGC_CTRL1_CCATHRSH_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for AGC_CTRL1                  */
#define AGC_CTRL1_CCATHRSH_DEFAULT                     (_AGC_CTRL1_CCATHRSH_DEFAULT << 0)       /**< Shifted mode DEFAULT for AGC_CTRL1          */
#define _AGC_CTRL1_RSSIPERIOD_SHIFT                    8                                        /**< Shift value for AGC_RSSIPERIOD              */
#define _AGC_CTRL1_RSSIPERIOD_MASK                     0xF00UL                                  /**< Bit mask for AGC_RSSIPERIOD                 */
#define _AGC_CTRL1_RSSIPERIOD_DEFAULT                  0x00000003UL                             /**< Mode DEFAULT for AGC_CTRL1                  */
#define AGC_CTRL1_RSSIPERIOD_DEFAULT                   (_AGC_CTRL1_RSSIPERIOD_DEFAULT << 8)     /**< Shifted mode DEFAULT for AGC_CTRL1          */
#define _AGC_CTRL1_PWRPERIOD_SHIFT                     12                                       /**< Shift value for AGC_PWRPERIOD               */
#define _AGC_CTRL1_PWRPERIOD_MASK                      0x7000UL                                 /**< Bit mask for AGC_PWRPERIOD                  */
#define _AGC_CTRL1_PWRPERIOD_DEFAULT                   0x00000001UL                             /**< Mode DEFAULT for AGC_CTRL1                  */
#define AGC_CTRL1_PWRPERIOD_DEFAULT                    (_AGC_CTRL1_PWRPERIOD_DEFAULT << 12)     /**< Shifted mode DEFAULT for AGC_CTRL1          */
#define _AGC_CTRL1_CCAMODE_SHIFT                       15                                       /**< Shift value for AGC_CCAMODE                 */
#define _AGC_CTRL1_CCAMODE_MASK                        0x18000UL                                /**< Bit mask for AGC_CCAMODE                    */
#define _AGC_CTRL1_CCAMODE_DEFAULT                     0x00000000UL                             /**< Mode DEFAULT for AGC_CTRL1                  */
#define _AGC_CTRL1_CCAMODE_MODE1                       0x00000000UL                             /**< Mode MODE1 for AGC_CTRL1                    */
#define _AGC_CTRL1_CCAMODE_MODE2                       0x00000001UL                             /**< Mode MODE2 for AGC_CTRL1                    */
#define _AGC_CTRL1_CCAMODE_MODE3                       0x00000002UL                             /**< Mode MODE3 for AGC_CTRL1                    */
#define _AGC_CTRL1_CCAMODE_MODE4                       0x00000003UL                             /**< Mode MODE4 for AGC_CTRL1                    */
#define AGC_CTRL1_CCAMODE_DEFAULT                      (_AGC_CTRL1_CCAMODE_DEFAULT << 15)       /**< Shifted mode DEFAULT for AGC_CTRL1          */
#define AGC_CTRL1_CCAMODE_MODE1                        (_AGC_CTRL1_CCAMODE_MODE1 << 15)         /**< Shifted mode MODE1 for AGC_CTRL1            */
#define AGC_CTRL1_CCAMODE_MODE2                        (_AGC_CTRL1_CCAMODE_MODE2 << 15)         /**< Shifted mode MODE2 for AGC_CTRL1            */
#define AGC_CTRL1_CCAMODE_MODE3                        (_AGC_CTRL1_CCAMODE_MODE3 << 15)         /**< Shifted mode MODE3 for AGC_CTRL1            */
#define AGC_CTRL1_CCAMODE_MODE4                        (_AGC_CTRL1_CCAMODE_MODE4 << 15)         /**< Shifted mode MODE4 for AGC_CTRL1            */
#define AGC_CTRL1_CCAMODE3LOGIC                        (0x1UL << 17)                            /**< Select mode3 logic                          */
#define _AGC_CTRL1_CCAMODE3LOGIC_SHIFT                 17                                       /**< Shift value for AGC_CCAMODE3LOGIC           */
#define _AGC_CTRL1_CCAMODE3LOGIC_MASK                  0x20000UL                                /**< Bit mask for AGC_CCAMODE3LOGIC              */
#define _AGC_CTRL1_CCAMODE3LOGIC_DEFAULT               0x00000000UL                             /**< Mode DEFAULT for AGC_CTRL1                  */
#define _AGC_CTRL1_CCAMODE3LOGIC_AND                   0x00000000UL                             /**< Mode AND for AGC_CTRL1                      */
#define _AGC_CTRL1_CCAMODE3LOGIC_OR                    0x00000001UL                             /**< Mode OR for AGC_CTRL1                       */
#define AGC_CTRL1_CCAMODE3LOGIC_DEFAULT                (_AGC_CTRL1_CCAMODE3LOGIC_DEFAULT << 17) /**< Shifted mode DEFAULT for AGC_CTRL1          */
#define AGC_CTRL1_CCAMODE3LOGIC_AND                    (_AGC_CTRL1_CCAMODE3LOGIC_AND << 17)     /**< Shifted mode AND for AGC_CTRL1              */
#define AGC_CTRL1_CCAMODE3LOGIC_OR                     (_AGC_CTRL1_CCAMODE3LOGIC_OR << 17)      /**< Shifted mode OR for AGC_CTRL1               */
#define AGC_CTRL1_CCASWCTRL                            (0x1UL << 18)                            /**< SW control over CCA                         */
#define _AGC_CTRL1_CCASWCTRL_SHIFT                     18                                       /**< Shift value for AGC_CCASWCTRL               */
#define _AGC_CTRL1_CCASWCTRL_MASK                      0x40000UL                                /**< Bit mask for AGC_CCASWCTRL                  */
#define _AGC_CTRL1_CCASWCTRL_DEFAULT                   0x00000000UL                             /**< Mode DEFAULT for AGC_CTRL1                  */
#define AGC_CTRL1_CCASWCTRL_DEFAULT                    (_AGC_CTRL1_CCASWCTRL_DEFAULT << 18)     /**< Shifted mode DEFAULT for AGC_CTRL1          */

/* Bit fields for AGC CTRL2 */
#define _AGC_CTRL2_RESETVALUE                          0x0000610AUL                                 /**< Default value for AGC_CTRL2                 */
#define _AGC_CTRL2_MASK                                0xFFFFFFFFUL                                 /**< Mask for AGC_CTRL2                          */
#define AGC_CTRL2_DMASEL                               (0x1UL << 0)                                 /**< DMA select                                  */
#define _AGC_CTRL2_DMASEL_SHIFT                        0                                            /**< Shift value for AGC_DMASEL                  */
#define _AGC_CTRL2_DMASEL_MASK                         0x1UL                                        /**< Bit mask for AGC_DMASEL                     */
#define _AGC_CTRL2_DMASEL_DEFAULT                      0x00000000UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define _AGC_CTRL2_DMASEL_RSSI                         0x00000000UL                                 /**< Mode RSSI for AGC_CTRL2                     */
#define _AGC_CTRL2_DMASEL_GAIN                         0x00000001UL                                 /**< Mode GAIN for AGC_CTRL2                     */
#define AGC_CTRL2_DMASEL_DEFAULT                       (_AGC_CTRL2_DMASEL_DEFAULT << 0)             /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define AGC_CTRL2_DMASEL_RSSI                          (_AGC_CTRL2_DMASEL_RSSI << 0)                /**< Shifted mode RSSI for AGC_CTRL2             */
#define AGC_CTRL2_DMASEL_GAIN                          (_AGC_CTRL2_DMASEL_GAIN << 0)                /**< Shifted mode GAIN for AGC_CTRL2             */
#define AGC_CTRL2_SAFEMODE                             (0x1UL << 1)                                 /**< AGC safe mode                               */
#define _AGC_CTRL2_SAFEMODE_SHIFT                      1                                            /**< Shift value for AGC_SAFEMODE                */
#define _AGC_CTRL2_SAFEMODE_MASK                       0x2UL                                        /**< Bit mask for AGC_SAFEMODE                   */
#define _AGC_CTRL2_SAFEMODE_DEFAULT                    0x00000001UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define AGC_CTRL2_SAFEMODE_DEFAULT                     (_AGC_CTRL2_SAFEMODE_DEFAULT << 1)           /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define _AGC_CTRL2_SAFEMODETHD_SHIFT                   2                                            /**< Shift value for AGC_SAFEMODETHD             */
#define _AGC_CTRL2_SAFEMODETHD_MASK                    0x1CUL                                       /**< Bit mask for AGC_SAFEMODETHD                */
#define _AGC_CTRL2_SAFEMODETHD_DEFAULT                 0x00000002UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define AGC_CTRL2_SAFEMODETHD_DEFAULT                  (_AGC_CTRL2_SAFEMODETHD_DEFAULT << 2)        /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define _AGC_CTRL2_REHICNTTHD_SHIFT                    5                                            /**< Shift value for AGC_REHICNTTHD              */
#define _AGC_CTRL2_REHICNTTHD_MASK                     0x1FE0UL                                     /**< Bit mask for AGC_REHICNTTHD                 */
#define _AGC_CTRL2_REHICNTTHD_DEFAULT                  0x00000008UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define AGC_CTRL2_REHICNTTHD_DEFAULT                   (_AGC_CTRL2_REHICNTTHD_DEFAULT << 5)         /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define _AGC_CTRL2_RELOTHD_SHIFT                       13                                           /**< Shift value for AGC_RELOTHD                 */
#define _AGC_CTRL2_RELOTHD_MASK                        0xE000UL                                     /**< Bit mask for AGC_RELOTHD                    */
#define _AGC_CTRL2_RELOTHD_DEFAULT                     0x00000003UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define AGC_CTRL2_RELOTHD_DEFAULT                      (_AGC_CTRL2_RELOTHD_DEFAULT << 13)           /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define _AGC_CTRL2_RELBYCHPWR_SHIFT                    16                                           /**< Shift value for AGC_RELBYCHPWR              */
#define _AGC_CTRL2_RELBYCHPWR_MASK                     0x30000UL                                    /**< Bit mask for AGC_RELBYCHPWR                 */
#define _AGC_CTRL2_RELBYCHPWR_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define _AGC_CTRL2_RELBYCHPWR_LO_CNT                   0x00000000UL                                 /**< Mode LO_CNT for AGC_CTRL2                   */
#define _AGC_CTRL2_RELBYCHPWR_PWR                      0x00000001UL                                 /**< Mode PWR for AGC_CTRL2                      */
#define _AGC_CTRL2_RELBYCHPWR_LO_CNT_PWR               0x00000002UL                                 /**< Mode LO_CNT_PWR for AGC_CTRL2               */
#define _AGC_CTRL2_RELBYCHPWR_LO_CNT_AND_PWR           0x00000003UL                                 /**< Mode LO_CNT_AND_PWR for AGC_CTRL2           */
#define AGC_CTRL2_RELBYCHPWR_DEFAULT                   (_AGC_CTRL2_RELBYCHPWR_DEFAULT << 16)        /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define AGC_CTRL2_RELBYCHPWR_LO_CNT                    (_AGC_CTRL2_RELBYCHPWR_LO_CNT << 16)         /**< Shifted mode LO_CNT for AGC_CTRL2           */
#define AGC_CTRL2_RELBYCHPWR_PWR                       (_AGC_CTRL2_RELBYCHPWR_PWR << 16)            /**< Shifted mode PWR for AGC_CTRL2              */
#define AGC_CTRL2_RELBYCHPWR_LO_CNT_PWR                (_AGC_CTRL2_RELBYCHPWR_LO_CNT_PWR << 16)     /**< Shifted mode LO_CNT_PWR for AGC_CTRL2       */
#define AGC_CTRL2_RELBYCHPWR_LO_CNT_AND_PWR            (_AGC_CTRL2_RELBYCHPWR_LO_CNT_AND_PWR << 16) /**< Shifted mode LO_CNT_AND_PWR for AGC_CTRL2   */
#define _AGC_CTRL2_RELTARGETPWR_SHIFT                  18                                           /**< Shift value for AGC_RELTARGETPWR            */
#define _AGC_CTRL2_RELTARGETPWR_MASK                   0x3FC0000UL                                  /**< Bit mask for AGC_RELTARGETPWR               */
#define _AGC_CTRL2_RELTARGETPWR_DEFAULT                0x00000000UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define AGC_CTRL2_RELTARGETPWR_DEFAULT                 (_AGC_CTRL2_RELTARGETPWR_DEFAULT << 18)      /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define _AGC_CTRL2_RSSICCASUB_SHIFT                    26                                           /**< Shift value for AGC_RSSICCASUB              */
#define _AGC_CTRL2_RSSICCASUB_MASK                     0x1C000000UL                                 /**< Bit mask for AGC_RSSICCASUB                 */
#define _AGC_CTRL2_RSSICCASUB_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define AGC_CTRL2_RSSICCASUB_DEFAULT                   (_AGC_CTRL2_RSSICCASUB_DEFAULT << 26)        /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define AGC_CTRL2_DEBCNTRST                            (0x1UL << 29)                                /**< Debonce CNT Reset MODE                      */
#define _AGC_CTRL2_DEBCNTRST_SHIFT                     29                                           /**< Shift value for AGC_DEBCNTRST               */
#define _AGC_CTRL2_DEBCNTRST_MASK                      0x20000000UL                                 /**< Bit mask for AGC_DEBCNTRST                  */
#define _AGC_CTRL2_DEBCNTRST_DEFAULT                   0x00000000UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define AGC_CTRL2_DEBCNTRST_DEFAULT                    (_AGC_CTRL2_DEBCNTRST_DEFAULT << 29)         /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define AGC_CTRL2_PRSDEBUGEN                           (0x1UL << 30)                                /**< PRS Debug Enable                            */
#define _AGC_CTRL2_PRSDEBUGEN_SHIFT                    30                                           /**< Shift value for AGC_PRSDEBUGEN              */
#define _AGC_CTRL2_PRSDEBUGEN_MASK                     0x40000000UL                                 /**< Bit mask for AGC_PRSDEBUGEN                 */
#define _AGC_CTRL2_PRSDEBUGEN_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define AGC_CTRL2_PRSDEBUGEN_DEFAULT                   (_AGC_CTRL2_PRSDEBUGEN_DEFAULT << 30)        /**< Shifted mode DEFAULT for AGC_CTRL2          */
#define AGC_CTRL2_DISRFPKD                             (0x1UL << 31)                                /**< Disable RF PEAKDET                          */
#define _AGC_CTRL2_DISRFPKD_SHIFT                      31                                           /**< Shift value for AGC_DISRFPKD                */
#define _AGC_CTRL2_DISRFPKD_MASK                       0x80000000UL                                 /**< Bit mask for AGC_DISRFPKD                   */
#define _AGC_CTRL2_DISRFPKD_DEFAULT                    0x00000000UL                                 /**< Mode DEFAULT for AGC_CTRL2                  */
#define AGC_CTRL2_DISRFPKD_DEFAULT                     (_AGC_CTRL2_DISRFPKD_DEFAULT << 31)          /**< Shifted mode DEFAULT for AGC_CTRL2          */

/* Bit fields for AGC CTRL3 */
#define _AGC_CTRL3_RESETVALUE                          0x5140A800UL                           /**< Default value for AGC_CTRL3                 */
#define _AGC_CTRL3_MASK                                0xFFFFFFFFUL                           /**< Mask for AGC_CTRL3                          */
#define AGC_CTRL3_IFPKDDEB                             (0x1UL << 0)                           /**< IF PEAKDET debounce mode enable             */
#define _AGC_CTRL3_IFPKDDEB_SHIFT                      0                                      /**< Shift value for AGC_IFPKDDEB                */
#define _AGC_CTRL3_IFPKDDEB_MASK                       0x1UL                                  /**< Bit mask for AGC_IFPKDDEB                   */
#define _AGC_CTRL3_IFPKDDEB_DEFAULT                    0x00000000UL                           /**< Mode DEFAULT for AGC_CTRL3                  */
#define AGC_CTRL3_IFPKDDEB_DEFAULT                     (_AGC_CTRL3_IFPKDDEB_DEFAULT << 0)     /**< Shifted mode DEFAULT for AGC_CTRL3          */
#define _AGC_CTRL3_IFPKDDEBTHD_SHIFT                   1                                      /**< Shift value for AGC_IFPKDDEBTHD             */
#define _AGC_CTRL3_IFPKDDEBTHD_MASK                    0x6UL                                  /**< Bit mask for AGC_IFPKDDEBTHD                */
#define _AGC_CTRL3_IFPKDDEBTHD_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for AGC_CTRL3                  */
#define AGC_CTRL3_IFPKDDEBTHD_DEFAULT                  (_AGC_CTRL3_IFPKDDEBTHD_DEFAULT << 1)  /**< Shifted mode DEFAULT for AGC_CTRL3          */
#define _AGC_CTRL3_IFPKDDEBPRD_SHIFT                   3                                      /**< Shift value for AGC_IFPKDDEBPRD             */
#define _AGC_CTRL3_IFPKDDEBPRD_MASK                    0x1F8UL                                /**< Bit mask for AGC_IFPKDDEBPRD                */
#define _AGC_CTRL3_IFPKDDEBPRD_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for AGC_CTRL3                  */
#define AGC_CTRL3_IFPKDDEBPRD_DEFAULT                  (_AGC_CTRL3_IFPKDDEBPRD_DEFAULT << 3)  /**< Shifted mode DEFAULT for AGC_CTRL3          */
#define _AGC_CTRL3_IFPKDDEBRST_SHIFT                   9                                      /**< Shift value for AGC_IFPKDDEBRST             */
#define _AGC_CTRL3_IFPKDDEBRST_MASK                    0x1E00UL                               /**< Bit mask for AGC_IFPKDDEBRST                */
#define _AGC_CTRL3_IFPKDDEBRST_DEFAULT                 0x00000004UL                           /**< Mode DEFAULT for AGC_CTRL3                  */
#define AGC_CTRL3_IFPKDDEBRST_DEFAULT                  (_AGC_CTRL3_IFPKDDEBRST_DEFAULT << 9)  /**< Shifted mode DEFAULT for AGC_CTRL3          */
#define AGC_CTRL3_RFPKDDEB                             (0x1UL << 13)                          /**< RF PEAKDET debounce mode enable             */
#define _AGC_CTRL3_RFPKDDEB_SHIFT                      13                                     /**< Shift value for AGC_RFPKDDEB                */
#define _AGC_CTRL3_RFPKDDEB_MASK                       0x2000UL                               /**< Bit mask for AGC_RFPKDDEB                   */
#define _AGC_CTRL3_RFPKDDEB_DEFAULT                    0x00000001UL                           /**< Mode DEFAULT for AGC_CTRL3                  */
#define AGC_CTRL3_RFPKDDEB_DEFAULT                     (_AGC_CTRL3_RFPKDDEB_DEFAULT << 13)    /**< Shifted mode DEFAULT for AGC_CTRL3          */
#define _AGC_CTRL3_RFPKDDEBTHD_SHIFT                   14                                     /**< Shift value for AGC_RFPKDDEBTHD             */
#define _AGC_CTRL3_RFPKDDEBTHD_MASK                    0x7C000UL                              /**< Bit mask for AGC_RFPKDDEBTHD                */
#define _AGC_CTRL3_RFPKDDEBTHD_DEFAULT                 0x00000002UL                           /**< Mode DEFAULT for AGC_CTRL3                  */
#define AGC_CTRL3_RFPKDDEBTHD_DEFAULT                  (_AGC_CTRL3_RFPKDDEBTHD_DEFAULT << 14) /**< Shifted mode DEFAULT for AGC_CTRL3          */
#define _AGC_CTRL3_RFPKDDEBPRD_SHIFT                   19                                     /**< Shift value for AGC_RFPKDDEBPRD             */
#define _AGC_CTRL3_RFPKDDEBPRD_MASK                    0x7F80000UL                            /**< Bit mask for AGC_RFPKDDEBPRD                */
#define _AGC_CTRL3_RFPKDDEBPRD_DEFAULT                 0x00000028UL                           /**< Mode DEFAULT for AGC_CTRL3                  */
#define AGC_CTRL3_RFPKDDEBPRD_DEFAULT                  (_AGC_CTRL3_RFPKDDEBPRD_DEFAULT << 19) /**< Shifted mode DEFAULT for AGC_CTRL3          */
#define _AGC_CTRL3_RFPKDDEBRST_SHIFT                   27                                     /**< Shift value for AGC_RFPKDDEBRST             */
#define _AGC_CTRL3_RFPKDDEBRST_MASK                    0xF8000000UL                           /**< Bit mask for AGC_RFPKDDEBRST                */
#define _AGC_CTRL3_RFPKDDEBRST_DEFAULT                 0x0000000AUL                           /**< Mode DEFAULT for AGC_CTRL3                  */
#define AGC_CTRL3_RFPKDDEBRST_DEFAULT                  (_AGC_CTRL3_RFPKDDEBRST_DEFAULT << 27) /**< Shifted mode DEFAULT for AGC_CTRL3          */

/* Bit fields for AGC CTRL4 */
#define _AGC_CTRL4_RESETVALUE                          0x0000000EUL                              /**< Default value for AGC_CTRL4                 */
#define _AGC_CTRL4_MASK                                0xFF80FFFFUL                              /**< Mask for AGC_CTRL4                          */
#define _AGC_CTRL4_PERIODRFPKD_SHIFT                   0                                         /**< Shift value for AGC_PERIODRFPKD             */
#define _AGC_CTRL4_PERIODRFPKD_MASK                    0xFFFFUL                                  /**< Bit mask for AGC_PERIODRFPKD                */
#define _AGC_CTRL4_PERIODRFPKD_DEFAULT                 0x0000000EUL                              /**< Mode DEFAULT for AGC_CTRL4                  */
#define AGC_CTRL4_PERIODRFPKD_DEFAULT                  (_AGC_CTRL4_PERIODRFPKD_DEFAULT << 0)     /**< Shifted mode DEFAULT for AGC_CTRL4          */
#define AGC_CTRL4_DISRFPKDCNTRST                       (0x1UL << 23)                             /**< Disable PGOCELOT-5333 fix                   */
#define _AGC_CTRL4_DISRFPKDCNTRST_SHIFT                23                                        /**< Shift value for AGC_DISRFPKDCNTRST          */
#define _AGC_CTRL4_DISRFPKDCNTRST_MASK                 0x800000UL                                /**< Bit mask for AGC_DISRFPKDCNTRST             */
#define _AGC_CTRL4_DISRFPKDCNTRST_DEFAULT              0x00000000UL                              /**< Mode DEFAULT for AGC_CTRL4                  */
#define AGC_CTRL4_DISRFPKDCNTRST_DEFAULT               (_AGC_CTRL4_DISRFPKDCNTRST_DEFAULT << 23) /**< Shifted mode DEFAULT for AGC_CTRL4          */
#define AGC_CTRL4_DISRSTCONDI                          (0x1UL << 24)                             /**< Disable PGOCELOT-5333 fix                   */
#define _AGC_CTRL4_DISRSTCONDI_SHIFT                   24                                        /**< Shift value for AGC_DISRSTCONDI             */
#define _AGC_CTRL4_DISRSTCONDI_MASK                    0x1000000UL                               /**< Bit mask for AGC_DISRSTCONDI                */
#define _AGC_CTRL4_DISRSTCONDI_DEFAULT                 0x00000000UL                              /**< Mode DEFAULT for AGC_CTRL4                  */
#define AGC_CTRL4_DISRSTCONDI_DEFAULT                  (_AGC_CTRL4_DISRSTCONDI_DEFAULT << 24)    /**< Shifted mode DEFAULT for AGC_CTRL4          */
#define _AGC_CTRL4_RFPKDPRDGEAR_SHIFT                  25                                        /**< Shift value for AGC_RFPKDPRDGEAR            */
#define _AGC_CTRL4_RFPKDPRDGEAR_MASK                   0xE000000UL                               /**< Bit mask for AGC_RFPKDPRDGEAR               */
#define _AGC_CTRL4_RFPKDPRDGEAR_DEFAULT                0x00000000UL                              /**< Mode DEFAULT for AGC_CTRL4                  */
#define AGC_CTRL4_RFPKDPRDGEAR_DEFAULT                 (_AGC_CTRL4_RFPKDPRDGEAR_DEFAULT << 25)   /**< Shifted mode DEFAULT for AGC_CTRL4          */
#define AGC_CTRL4_RFPKDSYNCSEL                         (0x1UL << 28)                             /**< SYNC RF PKD OUTPUT SELECT                   */
#define _AGC_CTRL4_RFPKDSYNCSEL_SHIFT                  28                                        /**< Shift value for AGC_RFPKDSYNCSEL            */
#define _AGC_CTRL4_RFPKDSYNCSEL_MASK                   0x10000000UL                              /**< Bit mask for AGC_RFPKDSYNCSEL               */
#define _AGC_CTRL4_RFPKDSYNCSEL_DEFAULT                0x00000000UL                              /**< Mode DEFAULT for AGC_CTRL4                  */
#define AGC_CTRL4_RFPKDSYNCSEL_DEFAULT                 (_AGC_CTRL4_RFPKDSYNCSEL_DEFAULT << 28)   /**< Shifted mode DEFAULT for AGC_CTRL4          */
#define AGC_CTRL4_RFPKDSEL                             (0x1UL << 29)                             /**< RF PKD OUTPUT SELECT                        */
#define _AGC_CTRL4_RFPKDSEL_SHIFT                      29                                        /**< Shift value for AGC_RFPKDSEL                */
#define _AGC_CTRL4_RFPKDSEL_MASK                       0x20000000UL                              /**< Bit mask for AGC_RFPKDSEL                   */
#define _AGC_CTRL4_RFPKDSEL_DEFAULT                    0x00000000UL                              /**< Mode DEFAULT for AGC_CTRL4                  */
#define AGC_CTRL4_RFPKDSEL_DEFAULT                     (_AGC_CTRL4_RFPKDSEL_DEFAULT << 29)       /**< Shifted mode DEFAULT for AGC_CTRL4          */
#define AGC_CTRL4_FRZPKDEN                             (0x1UL << 30)                             /**< PKD Freeze Enable                           */
#define _AGC_CTRL4_FRZPKDEN_SHIFT                      30                                        /**< Shift value for AGC_FRZPKDEN                */
#define _AGC_CTRL4_FRZPKDEN_MASK                       0x40000000UL                              /**< Bit mask for AGC_FRZPKDEN                   */
#define _AGC_CTRL4_FRZPKDEN_DEFAULT                    0x00000000UL                              /**< Mode DEFAULT for AGC_CTRL4                  */
#define AGC_CTRL4_FRZPKDEN_DEFAULT                     (_AGC_CTRL4_FRZPKDEN_DEFAULT << 30)       /**< Shifted mode DEFAULT for AGC_CTRL4          */
#define AGC_CTRL4_RFPKDCNTEN                           (0x1UL << 31)                             /**< Counter-based RFPKD Enable                  */
#define _AGC_CTRL4_RFPKDCNTEN_SHIFT                    31                                        /**< Shift value for AGC_RFPKDCNTEN              */
#define _AGC_CTRL4_RFPKDCNTEN_MASK                     0x80000000UL                              /**< Bit mask for AGC_RFPKDCNTEN                 */
#define _AGC_CTRL4_RFPKDCNTEN_DEFAULT                  0x00000000UL                              /**< Mode DEFAULT for AGC_CTRL4                  */
#define AGC_CTRL4_RFPKDCNTEN_DEFAULT                   (_AGC_CTRL4_RFPKDCNTEN_DEFAULT << 31)     /**< Shifted mode DEFAULT for AGC_CTRL4          */

/* Bit fields for AGC CTRL5 */
#define _AGC_CTRL5_RESETVALUE                          0x00000000UL                            /**< Default value for AGC_CTRL5                 */
#define _AGC_CTRL5_MASK                                0xC0FFFFFFUL                            /**< Mask for AGC_CTRL5                          */
#define _AGC_CTRL5_PNUPDISTHD_SHIFT                    0                                       /**< Shift value for AGC_PNUPDISTHD              */
#define _AGC_CTRL5_PNUPDISTHD_MASK                     0xFFFUL                                 /**< Bit mask for AGC_PNUPDISTHD                 */
#define _AGC_CTRL5_PNUPDISTHD_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for AGC_CTRL5                  */
#define AGC_CTRL5_PNUPDISTHD_DEFAULT                   (_AGC_CTRL5_PNUPDISTHD_DEFAULT << 0)    /**< Shifted mode DEFAULT for AGC_CTRL5          */
#define _AGC_CTRL5_PNUPRELTHD_SHIFT                    12                                      /**< Shift value for AGC_PNUPRELTHD              */
#define _AGC_CTRL5_PNUPRELTHD_MASK                     0xFFF000UL                              /**< Bit mask for AGC_PNUPRELTHD                 */
#define _AGC_CTRL5_PNUPRELTHD_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for AGC_CTRL5                  */
#define AGC_CTRL5_PNUPRELTHD_DEFAULT                   (_AGC_CTRL5_PNUPRELTHD_DEFAULT << 12)   /**< Shifted mode DEFAULT for AGC_CTRL5          */
#define AGC_CTRL5_SEQPNUPALLOW                         (0x1UL << 30)                           /**< SEQ Set PN GAIN UP ALLOW                    */
#define _AGC_CTRL5_SEQPNUPALLOW_SHIFT                  30                                      /**< Shift value for AGC_SEQPNUPALLOW            */
#define _AGC_CTRL5_SEQPNUPALLOW_MASK                   0x40000000UL                            /**< Bit mask for AGC_SEQPNUPALLOW               */
#define _AGC_CTRL5_SEQPNUPALLOW_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for AGC_CTRL5                  */
#define AGC_CTRL5_SEQPNUPALLOW_DEFAULT                 (_AGC_CTRL5_SEQPNUPALLOW_DEFAULT << 30) /**< Shifted mode DEFAULT for AGC_CTRL5          */
#define AGC_CTRL5_SEQRFPKDEN                           (0x1UL << 31)                           /**< SEQ-based RFPKD Enable                      */
#define _AGC_CTRL5_SEQRFPKDEN_SHIFT                    31                                      /**< Shift value for AGC_SEQRFPKDEN              */
#define _AGC_CTRL5_SEQRFPKDEN_MASK                     0x80000000UL                            /**< Bit mask for AGC_SEQRFPKDEN                 */
#define _AGC_CTRL5_SEQRFPKDEN_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for AGC_CTRL5                  */
#define AGC_CTRL5_SEQRFPKDEN_DEFAULT                   (_AGC_CTRL5_SEQRFPKDEN_DEFAULT << 31)   /**< Shifted mode DEFAULT for AGC_CTRL5          */

/* Bit fields for AGC CTRL6 */
#define _AGC_CTRL6_RESETVALUE                          0x0003AAA8UL                           /**< Default value for AGC_CTRL6                 */
#define _AGC_CTRL6_MASK                                0x7FFFFFFFUL                           /**< Mask for AGC_CTRL6                          */
#define _AGC_CTRL6_DUALRFPKDDEC_SHIFT                  0                                      /**< Shift value for AGC_DUALRFPKDDEC            */
#define _AGC_CTRL6_DUALRFPKDDEC_MASK                   0x3FFFFUL                              /**< Bit mask for AGC_DUALRFPKDDEC               */
#define _AGC_CTRL6_DUALRFPKDDEC_DEFAULT                0x0003AAA8UL                           /**< Mode DEFAULT for AGC_CTRL6                  */
#define AGC_CTRL6_DUALRFPKDDEC_DEFAULT                 (_AGC_CTRL6_DUALRFPKDDEC_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_CTRL6          */
#define AGC_CTRL6_ENDUALRFPKD                          (0x1UL << 18)                          /**< Enable dual RFPKD                           */
#define _AGC_CTRL6_ENDUALRFPKD_SHIFT                   18                                     /**< Shift value for AGC_ENDUALRFPKD             */
#define _AGC_CTRL6_ENDUALRFPKD_MASK                    0x40000UL                              /**< Bit mask for AGC_ENDUALRFPKD                */
#define _AGC_CTRL6_ENDUALRFPKD_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for AGC_CTRL6                  */
#define AGC_CTRL6_ENDUALRFPKD_DEFAULT                  (_AGC_CTRL6_ENDUALRFPKD_DEFAULT << 18) /**< Shifted mode DEFAULT for AGC_CTRL6          */
#define _AGC_CTRL6_GAINDETTHD_SHIFT                    19                                     /**< Shift value for AGC_GAINDETTHD              */
#define _AGC_CTRL6_GAINDETTHD_MASK                     0x7FF80000UL                           /**< Bit mask for AGC_GAINDETTHD                 */
#define _AGC_CTRL6_GAINDETTHD_DEFAULT                  0x00000000UL                           /**< Mode DEFAULT for AGC_CTRL6                  */
#define AGC_CTRL6_GAINDETTHD_DEFAULT                   (_AGC_CTRL6_GAINDETTHD_DEFAULT << 19)  /**< Shifted mode DEFAULT for AGC_CTRL6          */

/* Bit fields for AGC CTRL7 */
#define _AGC_CTRL7_RESETVALUE                          0x00000000UL                         /**< Default value for AGC_CTRL7                 */
#define _AGC_CTRL7_MASK                                0x01FFFFFFUL                         /**< Mask for AGC_CTRL7                          */
#define _AGC_CTRL7_SUBDEN_SHIFT                        0                                    /**< Shift value for AGC_SUBDEN                  */
#define _AGC_CTRL7_SUBDEN_MASK                         0xFFUL                               /**< Bit mask for AGC_SUBDEN                     */
#define _AGC_CTRL7_SUBDEN_DEFAULT                      0x00000000UL                         /**< Mode DEFAULT for AGC_CTRL7                  */
#define AGC_CTRL7_SUBDEN_DEFAULT                       (_AGC_CTRL7_SUBDEN_DEFAULT << 0)     /**< Shifted mode DEFAULT for AGC_CTRL7          */
#define _AGC_CTRL7_SUBINT_SHIFT                        8                                    /**< Shift value for AGC_SUBINT                  */
#define _AGC_CTRL7_SUBINT_MASK                         0xFF00UL                             /**< Bit mask for AGC_SUBINT                     */
#define _AGC_CTRL7_SUBINT_DEFAULT                      0x00000000UL                         /**< Mode DEFAULT for AGC_CTRL7                  */
#define AGC_CTRL7_SUBINT_DEFAULT                       (_AGC_CTRL7_SUBINT_DEFAULT << 8)     /**< Shifted mode DEFAULT for AGC_CTRL7          */
#define _AGC_CTRL7_SUBNUM_SHIFT                        16                                   /**< Shift value for AGC_SUBNUM                  */
#define _AGC_CTRL7_SUBNUM_MASK                         0xFF0000UL                           /**< Bit mask for AGC_SUBNUM                     */
#define _AGC_CTRL7_SUBNUM_DEFAULT                      0x00000000UL                         /**< Mode DEFAULT for AGC_CTRL7                  */
#define AGC_CTRL7_SUBNUM_DEFAULT                       (_AGC_CTRL7_SUBNUM_DEFAULT << 16)    /**< Shifted mode DEFAULT for AGC_CTRL7          */
#define AGC_CTRL7_SUBPERIOD                            (0x1UL << 24)                        /**< Subperiod                                   */
#define _AGC_CTRL7_SUBPERIOD_SHIFT                     24                                   /**< Shift value for AGC_SUBPERIOD               */
#define _AGC_CTRL7_SUBPERIOD_MASK                      0x1000000UL                          /**< Bit mask for AGC_SUBPERIOD                  */
#define _AGC_CTRL7_SUBPERIOD_DEFAULT                   0x00000000UL                         /**< Mode DEFAULT for AGC_CTRL7                  */
#define AGC_CTRL7_SUBPERIOD_DEFAULT                    (_AGC_CTRL7_SUBPERIOD_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_CTRL7          */

/* Bit fields for AGC RSSISTEPTHR */
#define _AGC_RSSISTEPTHR_RESETVALUE                    0x00000000UL                                     /**< Default value for AGC_RSSISTEPTHR           */
#define _AGC_RSSISTEPTHR_MASK                          0x3FFFFFFFUL                                     /**< Mask for AGC_RSSISTEPTHR                    */
#define _AGC_RSSISTEPTHR_POSSTEPTHR_SHIFT              0                                                /**< Shift value for AGC_POSSTEPTHR              */
#define _AGC_RSSISTEPTHR_POSSTEPTHR_MASK               0xFFUL                                           /**< Bit mask for AGC_POSSTEPTHR                 */
#define _AGC_RSSISTEPTHR_POSSTEPTHR_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for AGC_RSSISTEPTHR            */
#define AGC_RSSISTEPTHR_POSSTEPTHR_DEFAULT             (_AGC_RSSISTEPTHR_POSSTEPTHR_DEFAULT << 0)       /**< Shifted mode DEFAULT for AGC_RSSISTEPTHR    */
#define _AGC_RSSISTEPTHR_NEGSTEPTHR_SHIFT              8                                                /**< Shift value for AGC_NEGSTEPTHR              */
#define _AGC_RSSISTEPTHR_NEGSTEPTHR_MASK               0xFF00UL                                         /**< Bit mask for AGC_NEGSTEPTHR                 */
#define _AGC_RSSISTEPTHR_NEGSTEPTHR_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for AGC_RSSISTEPTHR            */
#define AGC_RSSISTEPTHR_NEGSTEPTHR_DEFAULT             (_AGC_RSSISTEPTHR_NEGSTEPTHR_DEFAULT << 8)       /**< Shifted mode DEFAULT for AGC_RSSISTEPTHR    */
#define AGC_RSSISTEPTHR_STEPPER                        (0x1UL << 16)                                    /**< Step Period                                 */
#define _AGC_RSSISTEPTHR_STEPPER_SHIFT                 16                                               /**< Shift value for AGC_STEPPER                 */
#define _AGC_RSSISTEPTHR_STEPPER_MASK                  0x10000UL                                        /**< Bit mask for AGC_STEPPER                    */
#define _AGC_RSSISTEPTHR_STEPPER_DEFAULT               0x00000000UL                                     /**< Mode DEFAULT for AGC_RSSISTEPTHR            */
#define AGC_RSSISTEPTHR_STEPPER_DEFAULT                (_AGC_RSSISTEPTHR_STEPPER_DEFAULT << 16)         /**< Shifted mode DEFAULT for AGC_RSSISTEPTHR    */
#define _AGC_RSSISTEPTHR_DEMODRESTARTPER_SHIFT         17                                               /**< Shift value for AGC_DEMODRESTARTPER         */
#define _AGC_RSSISTEPTHR_DEMODRESTARTPER_MASK          0x1E0000UL                                       /**< Bit mask for AGC_DEMODRESTARTPER            */
#define _AGC_RSSISTEPTHR_DEMODRESTARTPER_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_RSSISTEPTHR            */
#define AGC_RSSISTEPTHR_DEMODRESTARTPER_DEFAULT        (_AGC_RSSISTEPTHR_DEMODRESTARTPER_DEFAULT << 17) /**< Shifted mode DEFAULT for AGC_RSSISTEPTHR    */
#define _AGC_RSSISTEPTHR_DEMODRESTARTTHR_SHIFT         21                                               /**< Shift value for AGC_DEMODRESTARTTHR         */
#define _AGC_RSSISTEPTHR_DEMODRESTARTTHR_MASK          0x1FE00000UL                                     /**< Bit mask for AGC_DEMODRESTARTTHR            */
#define _AGC_RSSISTEPTHR_DEMODRESTARTTHR_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_RSSISTEPTHR            */
#define AGC_RSSISTEPTHR_DEMODRESTARTTHR_DEFAULT        (_AGC_RSSISTEPTHR_DEMODRESTARTTHR_DEFAULT << 21) /**< Shifted mode DEFAULT for AGC_RSSISTEPTHR    */
#define AGC_RSSISTEPTHR_RSSIFAST                       (0x1UL << 29)                                    /**< RSSI fast startup                           */
#define _AGC_RSSISTEPTHR_RSSIFAST_SHIFT                29                                               /**< Shift value for AGC_RSSIFAST                */
#define _AGC_RSSISTEPTHR_RSSIFAST_MASK                 0x20000000UL                                     /**< Bit mask for AGC_RSSIFAST                   */
#define _AGC_RSSISTEPTHR_RSSIFAST_DEFAULT              0x00000000UL                                     /**< Mode DEFAULT for AGC_RSSISTEPTHR            */
#define AGC_RSSISTEPTHR_RSSIFAST_DEFAULT               (_AGC_RSSISTEPTHR_RSSIFAST_DEFAULT << 29)        /**< Shifted mode DEFAULT for AGC_RSSISTEPTHR    */

/* Bit fields for AGC IF */
#define _AGC_IF_RESETVALUE                             0x00000000UL                             /**< Default value for AGC_IF                    */
#define _AGC_IF_MASK                                   0x00007F7DUL                             /**< Mask for AGC_IF                             */
#define AGC_IF_RSSIVALID                               (0x1UL << 0)                             /**< RSSI Value is Valid                         */
#define _AGC_IF_RSSIVALID_SHIFT                        0                                        /**< Shift value for AGC_RSSIVALID               */
#define _AGC_IF_RSSIVALID_MASK                         0x1UL                                    /**< Bit mask for AGC_RSSIVALID                  */
#define _AGC_IF_RSSIVALID_DEFAULT                      0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_RSSIVALID_DEFAULT                       (_AGC_IF_RSSIVALID_DEFAULT << 0)         /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_CCA                                     (0x1UL << 2)                             /**< Clear Channel Assessment                    */
#define _AGC_IF_CCA_SHIFT                              2                                        /**< Shift value for AGC_CCA                     */
#define _AGC_IF_CCA_MASK                               0x4UL                                    /**< Bit mask for AGC_CCA                        */
#define _AGC_IF_CCA_DEFAULT                            0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_CCA_DEFAULT                             (_AGC_IF_CCA_DEFAULT << 2)               /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_RSSIPOSSTEP                             (0x1UL << 3)                             /**< Positive RSSI Step Detected                 */
#define _AGC_IF_RSSIPOSSTEP_SHIFT                      3                                        /**< Shift value for AGC_RSSIPOSSTEP             */
#define _AGC_IF_RSSIPOSSTEP_MASK                       0x8UL                                    /**< Bit mask for AGC_RSSIPOSSTEP                */
#define _AGC_IF_RSSIPOSSTEP_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_RSSIPOSSTEP_DEFAULT                     (_AGC_IF_RSSIPOSSTEP_DEFAULT << 3)       /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_RSSINEGSTEP                             (0x1UL << 4)                             /**< Negative RSSI Step Detected                 */
#define _AGC_IF_RSSINEGSTEP_SHIFT                      4                                        /**< Shift value for AGC_RSSINEGSTEP             */
#define _AGC_IF_RSSINEGSTEP_MASK                       0x10UL                                   /**< Bit mask for AGC_RSSINEGSTEP                */
#define _AGC_IF_RSSINEGSTEP_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_RSSINEGSTEP_DEFAULT                     (_AGC_IF_RSSINEGSTEP_DEFAULT << 4)       /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_SHORTRSSIPOSSTEP                        (0x1UL << 6)                             /**< Short-term Positive RSSI Step Detected      */
#define _AGC_IF_SHORTRSSIPOSSTEP_SHIFT                 6                                        /**< Shift value for AGC_SHORTRSSIPOSSTEP        */
#define _AGC_IF_SHORTRSSIPOSSTEP_MASK                  0x40UL                                   /**< Bit mask for AGC_SHORTRSSIPOSSTEP           */
#define _AGC_IF_SHORTRSSIPOSSTEP_DEFAULT               0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_SHORTRSSIPOSSTEP_DEFAULT                (_AGC_IF_SHORTRSSIPOSSTEP_DEFAULT << 6)  /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_RFPKDPRDDONE                            (0x1UL << 8)                             /**< RF PKD PERIOD CNT TOMEOUT                   */
#define _AGC_IF_RFPKDPRDDONE_SHIFT                     8                                        /**< Shift value for AGC_RFPKDPRDDONE            */
#define _AGC_IF_RFPKDPRDDONE_MASK                      0x100UL                                  /**< Bit mask for AGC_RFPKDPRDDONE               */
#define _AGC_IF_RFPKDPRDDONE_DEFAULT                   0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_RFPKDPRDDONE_DEFAULT                    (_AGC_IF_RFPKDPRDDONE_DEFAULT << 8)      /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_RFPKDCNTDONE                            (0x1UL << 9)                             /**< RF PKD pulse CNT TOMEOUT                    */
#define _AGC_IF_RFPKDCNTDONE_SHIFT                     9                                        /**< Shift value for AGC_RFPKDCNTDONE            */
#define _AGC_IF_RFPKDCNTDONE_MASK                      0x200UL                                  /**< Bit mask for AGC_RFPKDCNTDONE               */
#define _AGC_IF_RFPKDCNTDONE_DEFAULT                   0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_RFPKDCNTDONE_DEFAULT                    (_AGC_IF_RFPKDCNTDONE_DEFAULT << 9)      /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_RSSIHIGH                                (0x1UL << 10)                            /**< RSSI high detected                          */
#define _AGC_IF_RSSIHIGH_SHIFT                         10                                       /**< Shift value for AGC_RSSIHIGH                */
#define _AGC_IF_RSSIHIGH_MASK                          0x400UL                                  /**< Bit mask for AGC_RSSIHIGH                   */
#define _AGC_IF_RSSIHIGH_DEFAULT                       0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_RSSIHIGH_DEFAULT                        (_AGC_IF_RSSIHIGH_DEFAULT << 10)         /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_RSSILOW                                 (0x1UL << 11)                            /**< RSSI low detected                           */
#define _AGC_IF_RSSILOW_SHIFT                          11                                       /**< Shift value for AGC_RSSILOW                 */
#define _AGC_IF_RSSILOW_MASK                           0x800UL                                  /**< Bit mask for AGC_RSSILOW                    */
#define _AGC_IF_RSSILOW_DEFAULT                        0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_RSSILOW_DEFAULT                         (_AGC_IF_RSSILOW_DEFAULT << 11)          /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_CCANODET                                (0x1UL << 12)                            /**< CCA Not Detected                            */
#define _AGC_IF_CCANODET_SHIFT                         12                                       /**< Shift value for AGC_CCANODET                */
#define _AGC_IF_CCANODET_MASK                          0x1000UL                                 /**< Bit mask for AGC_CCANODET                   */
#define _AGC_IF_CCANODET_DEFAULT                       0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_CCANODET_DEFAULT                        (_AGC_IF_CCANODET_DEFAULT << 12)         /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_GAINBELOWGAINTHD                        (0x1UL << 13)                            /**< agc gain above threshold int                */
#define _AGC_IF_GAINBELOWGAINTHD_SHIFT                 13                                       /**< Shift value for AGC_GAINBELOWGAINTHD        */
#define _AGC_IF_GAINBELOWGAINTHD_MASK                  0x2000UL                                 /**< Bit mask for AGC_GAINBELOWGAINTHD           */
#define _AGC_IF_GAINBELOWGAINTHD_DEFAULT               0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_GAINBELOWGAINTHD_DEFAULT                (_AGC_IF_GAINBELOWGAINTHD_DEFAULT << 13) /**< Shifted mode DEFAULT for AGC_IF             */
#define AGC_IF_GAINUPDATEFRZ                           (0x1UL << 14)                            /**< AGC gain update frozen int                  */
#define _AGC_IF_GAINUPDATEFRZ_SHIFT                    14                                       /**< Shift value for AGC_GAINUPDATEFRZ           */
#define _AGC_IF_GAINUPDATEFRZ_MASK                     0x4000UL                                 /**< Bit mask for AGC_GAINUPDATEFRZ              */
#define _AGC_IF_GAINUPDATEFRZ_DEFAULT                  0x00000000UL                             /**< Mode DEFAULT for AGC_IF                     */
#define AGC_IF_GAINUPDATEFRZ_DEFAULT                   (_AGC_IF_GAINUPDATEFRZ_DEFAULT << 14)    /**< Shifted mode DEFAULT for AGC_IF             */

/* Bit fields for AGC IEN */
#define _AGC_IEN_RESETVALUE                            0x00000000UL                              /**< Default value for AGC_IEN                   */
#define _AGC_IEN_MASK                                  0x00007F7DUL                              /**< Mask for AGC_IEN                            */
#define AGC_IEN_RSSIVALID                              (0x1UL << 0)                              /**< RSSIVALID Interrupt Enable                  */
#define _AGC_IEN_RSSIVALID_SHIFT                       0                                         /**< Shift value for AGC_RSSIVALID               */
#define _AGC_IEN_RSSIVALID_MASK                        0x1UL                                     /**< Bit mask for AGC_RSSIVALID                  */
#define _AGC_IEN_RSSIVALID_DEFAULT                     0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_RSSIVALID_DEFAULT                      (_AGC_IEN_RSSIVALID_DEFAULT << 0)         /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_CCA                                    (0x1UL << 2)                              /**< CCA Interrupt Enable                        */
#define _AGC_IEN_CCA_SHIFT                             2                                         /**< Shift value for AGC_CCA                     */
#define _AGC_IEN_CCA_MASK                              0x4UL                                     /**< Bit mask for AGC_CCA                        */
#define _AGC_IEN_CCA_DEFAULT                           0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_CCA_DEFAULT                            (_AGC_IEN_CCA_DEFAULT << 2)               /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_RSSIPOSSTEP                            (0x1UL << 3)                              /**< RSSIPOSSTEP Interrupt Enable                */
#define _AGC_IEN_RSSIPOSSTEP_SHIFT                     3                                         /**< Shift value for AGC_RSSIPOSSTEP             */
#define _AGC_IEN_RSSIPOSSTEP_MASK                      0x8UL                                     /**< Bit mask for AGC_RSSIPOSSTEP                */
#define _AGC_IEN_RSSIPOSSTEP_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_RSSIPOSSTEP_DEFAULT                    (_AGC_IEN_RSSIPOSSTEP_DEFAULT << 3)       /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_RSSINEGSTEP                            (0x1UL << 4)                              /**< RSSINEGSTEP Interrupt Enable                */
#define _AGC_IEN_RSSINEGSTEP_SHIFT                     4                                         /**< Shift value for AGC_RSSINEGSTEP             */
#define _AGC_IEN_RSSINEGSTEP_MASK                      0x10UL                                    /**< Bit mask for AGC_RSSINEGSTEP                */
#define _AGC_IEN_RSSINEGSTEP_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_RSSINEGSTEP_DEFAULT                    (_AGC_IEN_RSSINEGSTEP_DEFAULT << 4)       /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_SHORTRSSIPOSSTEP                       (0x1UL << 6)                              /**< SHORTRSSIPOSSTEP Interrupt Enable           */
#define _AGC_IEN_SHORTRSSIPOSSTEP_SHIFT                6                                         /**< Shift value for AGC_SHORTRSSIPOSSTEP        */
#define _AGC_IEN_SHORTRSSIPOSSTEP_MASK                 0x40UL                                    /**< Bit mask for AGC_SHORTRSSIPOSSTEP           */
#define _AGC_IEN_SHORTRSSIPOSSTEP_DEFAULT              0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_SHORTRSSIPOSSTEP_DEFAULT               (_AGC_IEN_SHORTRSSIPOSSTEP_DEFAULT << 6)  /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_RFPKDPRDDONE                           (0x1UL << 8)                              /**< RF PKD PERIOD CNT Interrupt Enable          */
#define _AGC_IEN_RFPKDPRDDONE_SHIFT                    8                                         /**< Shift value for AGC_RFPKDPRDDONE            */
#define _AGC_IEN_RFPKDPRDDONE_MASK                     0x100UL                                   /**< Bit mask for AGC_RFPKDPRDDONE               */
#define _AGC_IEN_RFPKDPRDDONE_DEFAULT                  0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_RFPKDPRDDONE_DEFAULT                   (_AGC_IEN_RFPKDPRDDONE_DEFAULT << 8)      /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_RFPKDCNTDONE                           (0x1UL << 9)                              /**< RF PKD pulse CNT Interrupt Enable           */
#define _AGC_IEN_RFPKDCNTDONE_SHIFT                    9                                         /**< Shift value for AGC_RFPKDCNTDONE            */
#define _AGC_IEN_RFPKDCNTDONE_MASK                     0x200UL                                   /**< Bit mask for AGC_RFPKDCNTDONE               */
#define _AGC_IEN_RFPKDCNTDONE_DEFAULT                  0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_RFPKDCNTDONE_DEFAULT                   (_AGC_IEN_RFPKDCNTDONE_DEFAULT << 9)      /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_RSSIHIGH                               (0x1UL << 10)                             /**< RSSIHIGH Interrupt Enable                   */
#define _AGC_IEN_RSSIHIGH_SHIFT                        10                                        /**< Shift value for AGC_RSSIHIGH                */
#define _AGC_IEN_RSSIHIGH_MASK                         0x400UL                                   /**< Bit mask for AGC_RSSIHIGH                   */
#define _AGC_IEN_RSSIHIGH_DEFAULT                      0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_RSSIHIGH_DEFAULT                       (_AGC_IEN_RSSIHIGH_DEFAULT << 10)         /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_RSSILOW                                (0x1UL << 11)                             /**< RSSILOW Interrupt Enable                    */
#define _AGC_IEN_RSSILOW_SHIFT                         11                                        /**< Shift value for AGC_RSSILOW                 */
#define _AGC_IEN_RSSILOW_MASK                          0x800UL                                   /**< Bit mask for AGC_RSSILOW                    */
#define _AGC_IEN_RSSILOW_DEFAULT                       0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_RSSILOW_DEFAULT                        (_AGC_IEN_RSSILOW_DEFAULT << 11)          /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_CCANODET                               (0x1UL << 12)                             /**< CCANODET Interrupt Enable                   */
#define _AGC_IEN_CCANODET_SHIFT                        12                                        /**< Shift value for AGC_CCANODET                */
#define _AGC_IEN_CCANODET_MASK                         0x1000UL                                  /**< Bit mask for AGC_CCANODET                   */
#define _AGC_IEN_CCANODET_DEFAULT                      0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_CCANODET_DEFAULT                       (_AGC_IEN_CCANODET_DEFAULT << 12)         /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_GAINBELOWGAINTHD                       (0x1UL << 13)                             /**< GAINBELOWGAINTHD Interrupt Enable           */
#define _AGC_IEN_GAINBELOWGAINTHD_SHIFT                13                                        /**< Shift value for AGC_GAINBELOWGAINTHD        */
#define _AGC_IEN_GAINBELOWGAINTHD_MASK                 0x2000UL                                  /**< Bit mask for AGC_GAINBELOWGAINTHD           */
#define _AGC_IEN_GAINBELOWGAINTHD_DEFAULT              0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_GAINBELOWGAINTHD_DEFAULT               (_AGC_IEN_GAINBELOWGAINTHD_DEFAULT << 13) /**< Shifted mode DEFAULT for AGC_IEN            */
#define AGC_IEN_GAINUPDATEFRZ                          (0x1UL << 14)                             /**< AGC gain update frozen int Enable           */
#define _AGC_IEN_GAINUPDATEFRZ_SHIFT                   14                                        /**< Shift value for AGC_GAINUPDATEFRZ           */
#define _AGC_IEN_GAINUPDATEFRZ_MASK                    0x4000UL                                  /**< Bit mask for AGC_GAINUPDATEFRZ              */
#define _AGC_IEN_GAINUPDATEFRZ_DEFAULT                 0x00000000UL                              /**< Mode DEFAULT for AGC_IEN                    */
#define AGC_IEN_GAINUPDATEFRZ_DEFAULT                  (_AGC_IEN_GAINUPDATEFRZ_DEFAULT << 14)    /**< Shifted mode DEFAULT for AGC_IEN            */

/* Bit fields for AGC GAINRANGE */
#define _AGC_GAINRANGE_RESETVALUE                      0x00813187UL                                 /**< Default value for AGC_GAINRANGE             */
#define _AGC_GAINRANGE_MASK                            0x03FFFFFFUL                                 /**< Mask for AGC_GAINRANGE                      */
#define _AGC_GAINRANGE_LNAINDEXBORDER_SHIFT            0                                            /**< Shift value for AGC_LNAINDEXBORDER          */
#define _AGC_GAINRANGE_LNAINDEXBORDER_MASK             0xFUL                                        /**< Bit mask for AGC_LNAINDEXBORDER             */
#define _AGC_GAINRANGE_LNAINDEXBORDER_DEFAULT          0x00000007UL                                 /**< Mode DEFAULT for AGC_GAINRANGE              */
#define AGC_GAINRANGE_LNAINDEXBORDER_DEFAULT           (_AGC_GAINRANGE_LNAINDEXBORDER_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_GAINRANGE      */
#define _AGC_GAINRANGE_PGAINDEXBORDER_SHIFT            4                                            /**< Shift value for AGC_PGAINDEXBORDER          */
#define _AGC_GAINRANGE_PGAINDEXBORDER_MASK             0xF0UL                                       /**< Bit mask for AGC_PGAINDEXBORDER             */
#define _AGC_GAINRANGE_PGAINDEXBORDER_DEFAULT          0x00000008UL                                 /**< Mode DEFAULT for AGC_GAINRANGE              */
#define AGC_GAINRANGE_PGAINDEXBORDER_DEFAULT           (_AGC_GAINRANGE_PGAINDEXBORDER_DEFAULT << 4) /**< Shifted mode DEFAULT for AGC_GAINRANGE      */
#define _AGC_GAINRANGE_GAININCSTEP_SHIFT               8                                            /**< Shift value for AGC_GAININCSTEP             */
#define _AGC_GAINRANGE_GAININCSTEP_MASK                0xF00UL                                      /**< Bit mask for AGC_GAININCSTEP                */
#define _AGC_GAINRANGE_GAININCSTEP_DEFAULT             0x00000001UL                                 /**< Mode DEFAULT for AGC_GAINRANGE              */
#define AGC_GAINRANGE_GAININCSTEP_DEFAULT              (_AGC_GAINRANGE_GAININCSTEP_DEFAULT << 8)    /**< Shifted mode DEFAULT for AGC_GAINRANGE      */
#define _AGC_GAINRANGE_PNGAINSTEP_SHIFT                12                                           /**< Shift value for AGC_PNGAINSTEP              */
#define _AGC_GAINRANGE_PNGAINSTEP_MASK                 0xF000UL                                     /**< Bit mask for AGC_PNGAINSTEP                 */
#define _AGC_GAINRANGE_PNGAINSTEP_DEFAULT              0x00000003UL                                 /**< Mode DEFAULT for AGC_GAINRANGE              */
#define AGC_GAINRANGE_PNGAINSTEP_DEFAULT               (_AGC_GAINRANGE_PNGAINSTEP_DEFAULT << 12)    /**< Shifted mode DEFAULT for AGC_GAINRANGE      */
#define _AGC_GAINRANGE_LATCHEDHISTEP_SHIFT             16                                           /**< Shift value for AGC_LATCHEDHISTEP           */
#define _AGC_GAINRANGE_LATCHEDHISTEP_MASK              0xF0000UL                                    /**< Bit mask for AGC_LATCHEDHISTEP              */
#define _AGC_GAINRANGE_LATCHEDHISTEP_DEFAULT           0x00000001UL                                 /**< Mode DEFAULT for AGC_GAINRANGE              */
#define AGC_GAINRANGE_LATCHEDHISTEP_DEFAULT            (_AGC_GAINRANGE_LATCHEDHISTEP_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_GAINRANGE      */
#define _AGC_GAINRANGE_HIPWRTHD_SHIFT                  20                                           /**< Shift value for AGC_HIPWRTHD                */
#define _AGC_GAINRANGE_HIPWRTHD_MASK                   0x3F00000UL                                  /**< Bit mask for AGC_HIPWRTHD                   */
#define _AGC_GAINRANGE_HIPWRTHD_DEFAULT                0x00000008UL                                 /**< Mode DEFAULT for AGC_GAINRANGE              */
#define AGC_GAINRANGE_HIPWRTHD_DEFAULT                 (_AGC_GAINRANGE_HIPWRTHD_DEFAULT << 20)      /**< Shifted mode DEFAULT for AGC_GAINRANGE      */

/* Bit fields for AGC AGCPERIOD0 */
#define _AGC_AGCPERIOD0_RESETVALUE                     0xD607000EUL                                 /**< Default value for AGC_AGCPERIOD0            */
#define _AGC_AGCPERIOD0_MASK                           0xFFFF01FFUL                                 /**< Mask for AGC_AGCPERIOD0                     */
#define _AGC_AGCPERIOD0_PERIODHI_SHIFT                 0                                            /**< Shift value for AGC_PERIODHI                */
#define _AGC_AGCPERIOD0_PERIODHI_MASK                  0x1FFUL                                      /**< Bit mask for AGC_PERIODHI                   */
#define _AGC_AGCPERIOD0_PERIODHI_DEFAULT               0x0000000EUL                                 /**< Mode DEFAULT for AGC_AGCPERIOD0             */
#define AGC_AGCPERIOD0_PERIODHI_DEFAULT                (_AGC_AGCPERIOD0_PERIODHI_DEFAULT << 0)      /**< Shifted mode DEFAULT for AGC_AGCPERIOD0     */
#define _AGC_AGCPERIOD0_MAXHICNTTHD_SHIFT              16                                           /**< Shift value for AGC_MAXHICNTTHD             */
#define _AGC_AGCPERIOD0_MAXHICNTTHD_MASK               0xFF0000UL                                   /**< Bit mask for AGC_MAXHICNTTHD                */
#define _AGC_AGCPERIOD0_MAXHICNTTHD_DEFAULT            0x00000007UL                                 /**< Mode DEFAULT for AGC_AGCPERIOD0             */
#define AGC_AGCPERIOD0_MAXHICNTTHD_DEFAULT             (_AGC_AGCPERIOD0_MAXHICNTTHD_DEFAULT << 16)  /**< Shifted mode DEFAULT for AGC_AGCPERIOD0     */
#define _AGC_AGCPERIOD0_SETTLETIMEIF_SHIFT             24                                           /**< Shift value for AGC_SETTLETIMEIF            */
#define _AGC_AGCPERIOD0_SETTLETIMEIF_MASK              0xF000000UL                                  /**< Bit mask for AGC_SETTLETIMEIF               */
#define _AGC_AGCPERIOD0_SETTLETIMEIF_DEFAULT           0x00000006UL                                 /**< Mode DEFAULT for AGC_AGCPERIOD0             */
#define AGC_AGCPERIOD0_SETTLETIMEIF_DEFAULT            (_AGC_AGCPERIOD0_SETTLETIMEIF_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_AGCPERIOD0     */
#define _AGC_AGCPERIOD0_SETTLETIMERF_SHIFT             28                                           /**< Shift value for AGC_SETTLETIMERF            */
#define _AGC_AGCPERIOD0_SETTLETIMERF_MASK              0xF0000000UL                                 /**< Bit mask for AGC_SETTLETIMERF               */
#define _AGC_AGCPERIOD0_SETTLETIMERF_DEFAULT           0x0000000DUL                                 /**< Mode DEFAULT for AGC_AGCPERIOD0             */
#define AGC_AGCPERIOD0_SETTLETIMERF_DEFAULT            (_AGC_AGCPERIOD0_SETTLETIMERF_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_AGCPERIOD0     */

/* Bit fields for AGC AGCPERIOD1 */
#define _AGC_AGCPERIOD1_RESETVALUE                     0x00000037UL                             /**< Default value for AGC_AGCPERIOD1            */
#define _AGC_AGCPERIOD1_MASK                           0xFFFFFFFFUL                             /**< Mask for AGC_AGCPERIOD1                     */
#define _AGC_AGCPERIOD1_PERIODLOW_SHIFT                0                                        /**< Shift value for AGC_PERIODLOW               */
#define _AGC_AGCPERIOD1_PERIODLOW_MASK                 0xFFFFFFFFUL                             /**< Bit mask for AGC_PERIODLOW                  */
#define _AGC_AGCPERIOD1_PERIODLOW_DEFAULT              0x00000037UL                             /**< Mode DEFAULT for AGC_AGCPERIOD1             */
#define AGC_AGCPERIOD1_PERIODLOW_DEFAULT               (_AGC_AGCPERIOD1_PERIODLOW_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_AGCPERIOD1     */

/* Bit fields for AGC HICNTREGION0 */
#define _AGC_HICNTREGION0_RESETVALUE                   0x06050403UL                                   /**< Default value for AGC_HICNTREGION0          */
#define _AGC_HICNTREGION0_MASK                         0xFFFFFFFFUL                                   /**< Mask for AGC_HICNTREGION0                   */
#define _AGC_HICNTREGION0_HICNTREGION0_SHIFT           0                                              /**< Shift value for AGC_HICNTREGION0            */
#define _AGC_HICNTREGION0_HICNTREGION0_MASK            0xFFUL                                         /**< Bit mask for AGC_HICNTREGION0               */
#define _AGC_HICNTREGION0_HICNTREGION0_DEFAULT         0x00000003UL                                   /**< Mode DEFAULT for AGC_HICNTREGION0           */
#define AGC_HICNTREGION0_HICNTREGION0_DEFAULT          (_AGC_HICNTREGION0_HICNTREGION0_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_HICNTREGION0   */
#define _AGC_HICNTREGION0_HICNTREGION1_SHIFT           8                                              /**< Shift value for AGC_HICNTREGION1            */
#define _AGC_HICNTREGION0_HICNTREGION1_MASK            0xFF00UL                                       /**< Bit mask for AGC_HICNTREGION1               */
#define _AGC_HICNTREGION0_HICNTREGION1_DEFAULT         0x00000004UL                                   /**< Mode DEFAULT for AGC_HICNTREGION0           */
#define AGC_HICNTREGION0_HICNTREGION1_DEFAULT          (_AGC_HICNTREGION0_HICNTREGION1_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_HICNTREGION0   */
#define _AGC_HICNTREGION0_HICNTREGION2_SHIFT           16                                             /**< Shift value for AGC_HICNTREGION2            */
#define _AGC_HICNTREGION0_HICNTREGION2_MASK            0xFF0000UL                                     /**< Bit mask for AGC_HICNTREGION2               */
#define _AGC_HICNTREGION0_HICNTREGION2_DEFAULT         0x00000005UL                                   /**< Mode DEFAULT for AGC_HICNTREGION0           */
#define AGC_HICNTREGION0_HICNTREGION2_DEFAULT          (_AGC_HICNTREGION0_HICNTREGION2_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_HICNTREGION0   */
#define _AGC_HICNTREGION0_HICNTREGION3_SHIFT           24                                             /**< Shift value for AGC_HICNTREGION3            */
#define _AGC_HICNTREGION0_HICNTREGION3_MASK            0xFF000000UL                                   /**< Bit mask for AGC_HICNTREGION3               */
#define _AGC_HICNTREGION0_HICNTREGION3_DEFAULT         0x00000006UL                                   /**< Mode DEFAULT for AGC_HICNTREGION0           */
#define AGC_HICNTREGION0_HICNTREGION3_DEFAULT          (_AGC_HICNTREGION0_HICNTREGION3_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_HICNTREGION0   */

/* Bit fields for AGC HICNTREGION1 */
#define _AGC_HICNTREGION1_RESETVALUE                   0x00000008UL                                  /**< Default value for AGC_HICNTREGION1          */
#define _AGC_HICNTREGION1_MASK                         0x000000FFUL                                  /**< Mask for AGC_HICNTREGION1                   */
#define _AGC_HICNTREGION1_HICNTREGION4_SHIFT           0                                             /**< Shift value for AGC_HICNTREGION4            */
#define _AGC_HICNTREGION1_HICNTREGION4_MASK            0xFFUL                                        /**< Bit mask for AGC_HICNTREGION4               */
#define _AGC_HICNTREGION1_HICNTREGION4_DEFAULT         0x00000008UL                                  /**< Mode DEFAULT for AGC_HICNTREGION1           */
#define AGC_HICNTREGION1_HICNTREGION4_DEFAULT          (_AGC_HICNTREGION1_HICNTREGION4_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_HICNTREGION1   */

/* Bit fields for AGC STEPDWN */
#define _AGC_STEPDWN_RESETVALUE                        0x00036D11UL                          /**< Default value for AGC_STEPDWN               */
#define _AGC_STEPDWN_MASK                              0x0003FFFFUL                          /**< Mask for AGC_STEPDWN                        */
#define _AGC_STEPDWN_STEPDWN0_SHIFT                    0                                     /**< Shift value for AGC_STEPDWN0                */
#define _AGC_STEPDWN_STEPDWN0_MASK                     0x7UL                                 /**< Bit mask for AGC_STEPDWN0                   */
#define _AGC_STEPDWN_STEPDWN0_DEFAULT                  0x00000001UL                          /**< Mode DEFAULT for AGC_STEPDWN                */
#define AGC_STEPDWN_STEPDWN0_DEFAULT                   (_AGC_STEPDWN_STEPDWN0_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_STEPDWN        */
#define _AGC_STEPDWN_STEPDWN1_SHIFT                    3                                     /**< Shift value for AGC_STEPDWN1                */
#define _AGC_STEPDWN_STEPDWN1_MASK                     0x38UL                                /**< Bit mask for AGC_STEPDWN1                   */
#define _AGC_STEPDWN_STEPDWN1_DEFAULT                  0x00000002UL                          /**< Mode DEFAULT for AGC_STEPDWN                */
#define AGC_STEPDWN_STEPDWN1_DEFAULT                   (_AGC_STEPDWN_STEPDWN1_DEFAULT << 3)  /**< Shifted mode DEFAULT for AGC_STEPDWN        */
#define _AGC_STEPDWN_STEPDWN2_SHIFT                    6                                     /**< Shift value for AGC_STEPDWN2                */
#define _AGC_STEPDWN_STEPDWN2_MASK                     0x1C0UL                               /**< Bit mask for AGC_STEPDWN2                   */
#define _AGC_STEPDWN_STEPDWN2_DEFAULT                  0x00000004UL                          /**< Mode DEFAULT for AGC_STEPDWN                */
#define AGC_STEPDWN_STEPDWN2_DEFAULT                   (_AGC_STEPDWN_STEPDWN2_DEFAULT << 6)  /**< Shifted mode DEFAULT for AGC_STEPDWN        */
#define _AGC_STEPDWN_STEPDWN3_SHIFT                    9                                     /**< Shift value for AGC_STEPDWN3                */
#define _AGC_STEPDWN_STEPDWN3_MASK                     0xE00UL                               /**< Bit mask for AGC_STEPDWN3                   */
#define _AGC_STEPDWN_STEPDWN3_DEFAULT                  0x00000006UL                          /**< Mode DEFAULT for AGC_STEPDWN                */
#define AGC_STEPDWN_STEPDWN3_DEFAULT                   (_AGC_STEPDWN_STEPDWN3_DEFAULT << 9)  /**< Shifted mode DEFAULT for AGC_STEPDWN        */
#define _AGC_STEPDWN_STEPDWN4_SHIFT                    12                                    /**< Shift value for AGC_STEPDWN4                */
#define _AGC_STEPDWN_STEPDWN4_MASK                     0x7000UL                              /**< Bit mask for AGC_STEPDWN4                   */
#define _AGC_STEPDWN_STEPDWN4_DEFAULT                  0x00000006UL                          /**< Mode DEFAULT for AGC_STEPDWN                */
#define AGC_STEPDWN_STEPDWN4_DEFAULT                   (_AGC_STEPDWN_STEPDWN4_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_STEPDWN        */
#define _AGC_STEPDWN_STEPDWN5_SHIFT                    15                                    /**< Shift value for AGC_STEPDWN5                */
#define _AGC_STEPDWN_STEPDWN5_MASK                     0x38000UL                             /**< Bit mask for AGC_STEPDWN5                   */
#define _AGC_STEPDWN_STEPDWN5_DEFAULT                  0x00000006UL                          /**< Mode DEFAULT for AGC_STEPDWN                */
#define AGC_STEPDWN_STEPDWN5_DEFAULT                   (_AGC_STEPDWN_STEPDWN5_DEFAULT << 15) /**< Shifted mode DEFAULT for AGC_STEPDWN        */

/* Bit fields for AGC GAINSTEPLIM0 */
#define _AGC_GAINSTEPLIM0_RESETVALUE                   0x00003144UL                                   /**< Default value for AGC_GAINSTEPLIM0          */
#define _AGC_GAINSTEPLIM0_MASK                         0x01FFFFFFUL                                   /**< Mask for AGC_GAINSTEPLIM0                   */
#define _AGC_GAINSTEPLIM0_CFLOOPSTEPMAX_SHIFT          0                                              /**< Shift value for AGC_CFLOOPSTEPMAX           */
#define _AGC_GAINSTEPLIM0_CFLOOPSTEPMAX_MASK           0x1FUL                                         /**< Bit mask for AGC_CFLOOPSTEPMAX              */
#define _AGC_GAINSTEPLIM0_CFLOOPSTEPMAX_DEFAULT        0x00000004UL                                   /**< Mode DEFAULT for AGC_GAINSTEPLIM0           */
#define AGC_GAINSTEPLIM0_CFLOOPSTEPMAX_DEFAULT         (_AGC_GAINSTEPLIM0_CFLOOPSTEPMAX_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_GAINSTEPLIM0   */
#define _AGC_GAINSTEPLIM0_CFLOOPDEL_SHIFT              5                                              /**< Shift value for AGC_CFLOOPDEL               */
#define _AGC_GAINSTEPLIM0_CFLOOPDEL_MASK               0xFE0UL                                        /**< Bit mask for AGC_CFLOOPDEL                  */
#define _AGC_GAINSTEPLIM0_CFLOOPDEL_DEFAULT            0x0000000AUL                                   /**< Mode DEFAULT for AGC_GAINSTEPLIM0           */
#define AGC_GAINSTEPLIM0_CFLOOPDEL_DEFAULT             (_AGC_GAINSTEPLIM0_CFLOOPDEL_DEFAULT << 5)     /**< Shifted mode DEFAULT for AGC_GAINSTEPLIM0   */
#define _AGC_GAINSTEPLIM0_HYST_SHIFT                   12                                             /**< Shift value for AGC_HYST                    */
#define _AGC_GAINSTEPLIM0_HYST_MASK                    0xF000UL                                       /**< Bit mask for AGC_HYST                       */
#define _AGC_GAINSTEPLIM0_HYST_DEFAULT                 0x00000003UL                                   /**< Mode DEFAULT for AGC_GAINSTEPLIM0           */
#define AGC_GAINSTEPLIM0_HYST_DEFAULT                  (_AGC_GAINSTEPLIM0_HYST_DEFAULT << 12)         /**< Shifted mode DEFAULT for AGC_GAINSTEPLIM0   */
#define _AGC_GAINSTEPLIM0_MAXPWRVAR_SHIFT              16                                             /**< Shift value for AGC_MAXPWRVAR               */
#define _AGC_GAINSTEPLIM0_MAXPWRVAR_MASK               0xFF0000UL                                     /**< Bit mask for AGC_MAXPWRVAR                  */
#define _AGC_GAINSTEPLIM0_MAXPWRVAR_DEFAULT            0x00000000UL                                   /**< Mode DEFAULT for AGC_GAINSTEPLIM0           */
#define AGC_GAINSTEPLIM0_MAXPWRVAR_DEFAULT             (_AGC_GAINSTEPLIM0_MAXPWRVAR_DEFAULT << 16)    /**< Shifted mode DEFAULT for AGC_GAINSTEPLIM0   */
#define AGC_GAINSTEPLIM0_TRANRSTAGC                    (0x1UL << 24)                                  /**< power transient detector Reset AGC          */
#define _AGC_GAINSTEPLIM0_TRANRSTAGC_SHIFT             24                                             /**< Shift value for AGC_TRANRSTAGC              */
#define _AGC_GAINSTEPLIM0_TRANRSTAGC_MASK              0x1000000UL                                    /**< Bit mask for AGC_TRANRSTAGC                 */
#define _AGC_GAINSTEPLIM0_TRANRSTAGC_DEFAULT           0x00000000UL                                   /**< Mode DEFAULT for AGC_GAINSTEPLIM0           */
#define AGC_GAINSTEPLIM0_TRANRSTAGC_DEFAULT            (_AGC_GAINSTEPLIM0_TRANRSTAGC_DEFAULT << 24)   /**< Shifted mode DEFAULT for AGC_GAINSTEPLIM0   */

/* Bit fields for AGC GAINSTEPLIM1 */
#define _AGC_GAINSTEPLIM1_RESETVALUE                   0x000011BAUL                                 /**< Default value for AGC_GAINSTEPLIM1          */
#define _AGC_GAINSTEPLIM1_MASK                         0x00001FFFUL                                 /**< Mask for AGC_GAINSTEPLIM1                   */
#define _AGC_GAINSTEPLIM1_LNAINDEXMAX_SHIFT            0                                            /**< Shift value for AGC_LNAINDEXMAX             */
#define _AGC_GAINSTEPLIM1_LNAINDEXMAX_MASK             0xFUL                                        /**< Bit mask for AGC_LNAINDEXMAX                */
#define _AGC_GAINSTEPLIM1_LNAINDEXMAX_DEFAULT          0x0000000AUL                                 /**< Mode DEFAULT for AGC_GAINSTEPLIM1           */
#define AGC_GAINSTEPLIM1_LNAINDEXMAX_DEFAULT           (_AGC_GAINSTEPLIM1_LNAINDEXMAX_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_GAINSTEPLIM1   */
#define _AGC_GAINSTEPLIM1_PGAINDEXMAX_SHIFT            4                                            /**< Shift value for AGC_PGAINDEXMAX             */
#define _AGC_GAINSTEPLIM1_PGAINDEXMAX_MASK             0xF0UL                                       /**< Bit mask for AGC_PGAINDEXMAX                */
#define _AGC_GAINSTEPLIM1_PGAINDEXMAX_DEFAULT          0x0000000BUL                                 /**< Mode DEFAULT for AGC_GAINSTEPLIM1           */
#define AGC_GAINSTEPLIM1_PGAINDEXMAX_DEFAULT           (_AGC_GAINSTEPLIM1_PGAINDEXMAX_DEFAULT << 4) /**< Shifted mode DEFAULT for AGC_GAINSTEPLIM1   */
#define _AGC_GAINSTEPLIM1_PNINDEXMAX_SHIFT             8                                            /**< Shift value for AGC_PNINDEXMAX              */
#define _AGC_GAINSTEPLIM1_PNINDEXMAX_MASK              0x1F00UL                                     /**< Bit mask for AGC_PNINDEXMAX                 */
#define _AGC_GAINSTEPLIM1_PNINDEXMAX_DEFAULT           0x00000011UL                                 /**< Mode DEFAULT for AGC_GAINSTEPLIM1           */
#define AGC_GAINSTEPLIM1_PNINDEXMAX_DEFAULT            (_AGC_GAINSTEPLIM1_PNINDEXMAX_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_GAINSTEPLIM1   */

/* Bit fields for AGC PNRFATT0 */
#define _AGC_PNRFATT0_RESETVALUE                       0x00200400UL                               /**< Default value for AGC_PNRFATT0              */
#define _AGC_PNRFATT0_MASK                             0x3FFFFFFFUL                               /**< Mask for AGC_PNRFATT0                       */
#define _AGC_PNRFATT0_LNAMIXRFATT1_SHIFT               0                                          /**< Shift value for AGC_LNAMIXRFATT1            */
#define _AGC_PNRFATT0_LNAMIXRFATT1_MASK                0x3FFUL                                    /**< Bit mask for AGC_LNAMIXRFATT1               */
#define _AGC_PNRFATT0_LNAMIXRFATT1_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for AGC_PNRFATT0               */
#define AGC_PNRFATT0_LNAMIXRFATT1_DEFAULT              (_AGC_PNRFATT0_LNAMIXRFATT1_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFATT0       */
#define _AGC_PNRFATT0_LNAMIXRFATT2_SHIFT               10                                         /**< Shift value for AGC_LNAMIXRFATT2            */
#define _AGC_PNRFATT0_LNAMIXRFATT2_MASK                0xFFC00UL                                  /**< Bit mask for AGC_LNAMIXRFATT2               */
#define _AGC_PNRFATT0_LNAMIXRFATT2_DEFAULT             0x00000001UL                               /**< Mode DEFAULT for AGC_PNRFATT0               */
#define AGC_PNRFATT0_LNAMIXRFATT2_DEFAULT              (_AGC_PNRFATT0_LNAMIXRFATT2_DEFAULT << 10) /**< Shifted mode DEFAULT for AGC_PNRFATT0       */
#define _AGC_PNRFATT0_LNAMIXRFATT3_SHIFT               20                                         /**< Shift value for AGC_LNAMIXRFATT3            */
#define _AGC_PNRFATT0_LNAMIXRFATT3_MASK                0x3FF00000UL                               /**< Bit mask for AGC_LNAMIXRFATT3               */
#define _AGC_PNRFATT0_LNAMIXRFATT3_DEFAULT             0x00000002UL                               /**< Mode DEFAULT for AGC_PNRFATT0               */
#define AGC_PNRFATT0_LNAMIXRFATT3_DEFAULT              (_AGC_PNRFATT0_LNAMIXRFATT3_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_PNRFATT0       */

/* Bit fields for AGC PNRFATT1 */
#define _AGC_PNRFATT1_RESETVALUE                       0x00801804UL                               /**< Default value for AGC_PNRFATT1              */
#define _AGC_PNRFATT1_MASK                             0x3FFFFFFFUL                               /**< Mask for AGC_PNRFATT1                       */
#define _AGC_PNRFATT1_LNAMIXRFATT4_SHIFT               0                                          /**< Shift value for AGC_LNAMIXRFATT4            */
#define _AGC_PNRFATT1_LNAMIXRFATT4_MASK                0x3FFUL                                    /**< Bit mask for AGC_LNAMIXRFATT4               */
#define _AGC_PNRFATT1_LNAMIXRFATT4_DEFAULT             0x00000004UL                               /**< Mode DEFAULT for AGC_PNRFATT1               */
#define AGC_PNRFATT1_LNAMIXRFATT4_DEFAULT              (_AGC_PNRFATT1_LNAMIXRFATT4_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFATT1       */
#define _AGC_PNRFATT1_LNAMIXRFATT5_SHIFT               10                                         /**< Shift value for AGC_LNAMIXRFATT5            */
#define _AGC_PNRFATT1_LNAMIXRFATT5_MASK                0xFFC00UL                                  /**< Bit mask for AGC_LNAMIXRFATT5               */
#define _AGC_PNRFATT1_LNAMIXRFATT5_DEFAULT             0x00000006UL                               /**< Mode DEFAULT for AGC_PNRFATT1               */
#define AGC_PNRFATT1_LNAMIXRFATT5_DEFAULT              (_AGC_PNRFATT1_LNAMIXRFATT5_DEFAULT << 10) /**< Shifted mode DEFAULT for AGC_PNRFATT1       */
#define _AGC_PNRFATT1_LNAMIXRFATT6_SHIFT               20                                         /**< Shift value for AGC_LNAMIXRFATT6            */
#define _AGC_PNRFATT1_LNAMIXRFATT6_MASK                0x3FF00000UL                               /**< Bit mask for AGC_LNAMIXRFATT6               */
#define _AGC_PNRFATT1_LNAMIXRFATT6_DEFAULT             0x00000008UL                               /**< Mode DEFAULT for AGC_PNRFATT1               */
#define AGC_PNRFATT1_LNAMIXRFATT6_DEFAULT              (_AGC_PNRFATT1_LNAMIXRFATT6_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_PNRFATT1       */

/* Bit fields for AGC PNRFATT2 */
#define _AGC_PNRFATT2_RESETVALUE                       0x01203C0BUL                               /**< Default value for AGC_PNRFATT2              */
#define _AGC_PNRFATT2_MASK                             0x3FFFFFFFUL                               /**< Mask for AGC_PNRFATT2                       */
#define _AGC_PNRFATT2_LNAMIXRFATT7_SHIFT               0                                          /**< Shift value for AGC_LNAMIXRFATT7            */
#define _AGC_PNRFATT2_LNAMIXRFATT7_MASK                0x3FFUL                                    /**< Bit mask for AGC_LNAMIXRFATT7               */
#define _AGC_PNRFATT2_LNAMIXRFATT7_DEFAULT             0x0000000BUL                               /**< Mode DEFAULT for AGC_PNRFATT2               */
#define AGC_PNRFATT2_LNAMIXRFATT7_DEFAULT              (_AGC_PNRFATT2_LNAMIXRFATT7_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFATT2       */
#define _AGC_PNRFATT2_LNAMIXRFATT8_SHIFT               10                                         /**< Shift value for AGC_LNAMIXRFATT8            */
#define _AGC_PNRFATT2_LNAMIXRFATT8_MASK                0xFFC00UL                                  /**< Bit mask for AGC_LNAMIXRFATT8               */
#define _AGC_PNRFATT2_LNAMIXRFATT8_DEFAULT             0x0000000FUL                               /**< Mode DEFAULT for AGC_PNRFATT2               */
#define AGC_PNRFATT2_LNAMIXRFATT8_DEFAULT              (_AGC_PNRFATT2_LNAMIXRFATT8_DEFAULT << 10) /**< Shifted mode DEFAULT for AGC_PNRFATT2       */
#define _AGC_PNRFATT2_LNAMIXRFATT9_SHIFT               20                                         /**< Shift value for AGC_LNAMIXRFATT9            */
#define _AGC_PNRFATT2_LNAMIXRFATT9_MASK                0x3FF00000UL                               /**< Bit mask for AGC_LNAMIXRFATT9               */
#define _AGC_PNRFATT2_LNAMIXRFATT9_DEFAULT             0x00000012UL                               /**< Mode DEFAULT for AGC_PNRFATT2               */
#define AGC_PNRFATT2_LNAMIXRFATT9_DEFAULT              (_AGC_PNRFATT2_LNAMIXRFATT9_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_PNRFATT2       */

/* Bit fields for AGC PNRFATT3 */
#define _AGC_PNRFATT3_RESETVALUE                       0x02107C18UL                                /**< Default value for AGC_PNRFATT3              */
#define _AGC_PNRFATT3_MASK                             0x3FFFFFFFUL                                /**< Mask for AGC_PNRFATT3                       */
#define _AGC_PNRFATT3_LNAMIXRFATT10_SHIFT              0                                           /**< Shift value for AGC_LNAMIXRFATT10           */
#define _AGC_PNRFATT3_LNAMIXRFATT10_MASK               0x3FFUL                                     /**< Bit mask for AGC_LNAMIXRFATT10              */
#define _AGC_PNRFATT3_LNAMIXRFATT10_DEFAULT            0x00000018UL                                /**< Mode DEFAULT for AGC_PNRFATT3               */
#define AGC_PNRFATT3_LNAMIXRFATT10_DEFAULT             (_AGC_PNRFATT3_LNAMIXRFATT10_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFATT3       */
#define _AGC_PNRFATT3_LNAMIXRFATT11_SHIFT              10                                          /**< Shift value for AGC_LNAMIXRFATT11           */
#define _AGC_PNRFATT3_LNAMIXRFATT11_MASK               0xFFC00UL                                   /**< Bit mask for AGC_LNAMIXRFATT11              */
#define _AGC_PNRFATT3_LNAMIXRFATT11_DEFAULT            0x0000001FUL                                /**< Mode DEFAULT for AGC_PNRFATT3               */
#define AGC_PNRFATT3_LNAMIXRFATT11_DEFAULT             (_AGC_PNRFATT3_LNAMIXRFATT11_DEFAULT << 10) /**< Shifted mode DEFAULT for AGC_PNRFATT3       */
#define _AGC_PNRFATT3_LNAMIXRFATT12_SHIFT              20                                          /**< Shift value for AGC_LNAMIXRFATT12           */
#define _AGC_PNRFATT3_LNAMIXRFATT12_MASK               0x3FF00000UL                                /**< Bit mask for AGC_LNAMIXRFATT12              */
#define _AGC_PNRFATT3_LNAMIXRFATT12_DEFAULT            0x00000021UL                                /**< Mode DEFAULT for AGC_PNRFATT3               */
#define AGC_PNRFATT3_LNAMIXRFATT12_DEFAULT             (_AGC_PNRFATT3_LNAMIXRFATT12_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_PNRFATT3       */

/* Bit fields for AGC PNRFATT4 */
#define _AGC_PNRFATT4_RESETVALUE                       0x06E0FC2FUL                                /**< Default value for AGC_PNRFATT4              */
#define _AGC_PNRFATT4_MASK                             0x3FFFFFFFUL                                /**< Mask for AGC_PNRFATT4                       */
#define _AGC_PNRFATT4_LNAMIXRFATT13_SHIFT              0                                           /**< Shift value for AGC_LNAMIXRFATT13           */
#define _AGC_PNRFATT4_LNAMIXRFATT13_MASK               0x3FFUL                                     /**< Bit mask for AGC_LNAMIXRFATT13              */
#define _AGC_PNRFATT4_LNAMIXRFATT13_DEFAULT            0x0000002FUL                                /**< Mode DEFAULT for AGC_PNRFATT4               */
#define AGC_PNRFATT4_LNAMIXRFATT13_DEFAULT             (_AGC_PNRFATT4_LNAMIXRFATT13_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFATT4       */
#define _AGC_PNRFATT4_LNAMIXRFATT14_SHIFT              10                                          /**< Shift value for AGC_LNAMIXRFATT14           */
#define _AGC_PNRFATT4_LNAMIXRFATT14_MASK               0xFFC00UL                                   /**< Bit mask for AGC_LNAMIXRFATT14              */
#define _AGC_PNRFATT4_LNAMIXRFATT14_DEFAULT            0x0000003FUL                                /**< Mode DEFAULT for AGC_PNRFATT4               */
#define AGC_PNRFATT4_LNAMIXRFATT14_DEFAULT             (_AGC_PNRFATT4_LNAMIXRFATT14_DEFAULT << 10) /**< Shifted mode DEFAULT for AGC_PNRFATT4       */
#define _AGC_PNRFATT4_LNAMIXRFATT15_SHIFT              20                                          /**< Shift value for AGC_LNAMIXRFATT15           */
#define _AGC_PNRFATT4_LNAMIXRFATT15_MASK               0x3FF00000UL                                /**< Bit mask for AGC_LNAMIXRFATT15              */
#define _AGC_PNRFATT4_LNAMIXRFATT15_DEFAULT            0x0000006EUL                                /**< Mode DEFAULT for AGC_PNRFATT4               */
#define AGC_PNRFATT4_LNAMIXRFATT15_DEFAULT             (_AGC_PNRFATT4_LNAMIXRFATT15_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_PNRFATT4       */

/* Bit fields for AGC PNRFATT5 */
#define _AGC_PNRFATT5_RESETVALUE                       0x0180480FUL                                /**< Default value for AGC_PNRFATT5              */
#define _AGC_PNRFATT5_MASK                             0x3FFFFFFFUL                                /**< Mask for AGC_PNRFATT5                       */
#define _AGC_PNRFATT5_LNAMIXRFATT16_SHIFT              0                                           /**< Shift value for AGC_LNAMIXRFATT16           */
#define _AGC_PNRFATT5_LNAMIXRFATT16_MASK               0x3FFUL                                     /**< Bit mask for AGC_LNAMIXRFATT16              */
#define _AGC_PNRFATT5_LNAMIXRFATT16_DEFAULT            0x0000000FUL                                /**< Mode DEFAULT for AGC_PNRFATT5               */
#define AGC_PNRFATT5_LNAMIXRFATT16_DEFAULT             (_AGC_PNRFATT5_LNAMIXRFATT16_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFATT5       */
#define _AGC_PNRFATT5_LNAMIXRFATT17_SHIFT              10                                          /**< Shift value for AGC_LNAMIXRFATT17           */
#define _AGC_PNRFATT5_LNAMIXRFATT17_MASK               0xFFC00UL                                   /**< Bit mask for AGC_LNAMIXRFATT17              */
#define _AGC_PNRFATT5_LNAMIXRFATT17_DEFAULT            0x00000012UL                                /**< Mode DEFAULT for AGC_PNRFATT5               */
#define AGC_PNRFATT5_LNAMIXRFATT17_DEFAULT             (_AGC_PNRFATT5_LNAMIXRFATT17_DEFAULT << 10) /**< Shifted mode DEFAULT for AGC_PNRFATT5       */
#define _AGC_PNRFATT5_LNAMIXRFATT18_SHIFT              20                                          /**< Shift value for AGC_LNAMIXRFATT18           */
#define _AGC_PNRFATT5_LNAMIXRFATT18_MASK               0x3FF00000UL                                /**< Bit mask for AGC_LNAMIXRFATT18              */
#define _AGC_PNRFATT5_LNAMIXRFATT18_DEFAULT            0x00000018UL                                /**< Mode DEFAULT for AGC_PNRFATT5               */
#define AGC_PNRFATT5_LNAMIXRFATT18_DEFAULT             (_AGC_PNRFATT5_LNAMIXRFATT18_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_PNRFATT5       */

/* Bit fields for AGC PNRFATT6 */
#define _AGC_PNRFATT6_RESETVALUE                       0x02F0841FUL                                /**< Default value for AGC_PNRFATT6              */
#define _AGC_PNRFATT6_MASK                             0x3FFFFFFFUL                                /**< Mask for AGC_PNRFATT6                       */
#define _AGC_PNRFATT6_LNAMIXRFATT19_SHIFT              0                                           /**< Shift value for AGC_LNAMIXRFATT19           */
#define _AGC_PNRFATT6_LNAMIXRFATT19_MASK               0x3FFUL                                     /**< Bit mask for AGC_LNAMIXRFATT19              */
#define _AGC_PNRFATT6_LNAMIXRFATT19_DEFAULT            0x0000001FUL                                /**< Mode DEFAULT for AGC_PNRFATT6               */
#define AGC_PNRFATT6_LNAMIXRFATT19_DEFAULT             (_AGC_PNRFATT6_LNAMIXRFATT19_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFATT6       */
#define _AGC_PNRFATT6_LNAMIXRFATT20_SHIFT              10                                          /**< Shift value for AGC_LNAMIXRFATT20           */
#define _AGC_PNRFATT6_LNAMIXRFATT20_MASK               0xFFC00UL                                   /**< Bit mask for AGC_LNAMIXRFATT20              */
#define _AGC_PNRFATT6_LNAMIXRFATT20_DEFAULT            0x00000021UL                                /**< Mode DEFAULT for AGC_PNRFATT6               */
#define AGC_PNRFATT6_LNAMIXRFATT20_DEFAULT             (_AGC_PNRFATT6_LNAMIXRFATT20_DEFAULT << 10) /**< Shifted mode DEFAULT for AGC_PNRFATT6       */
#define _AGC_PNRFATT6_LNAMIXRFATT21_SHIFT              20                                          /**< Shift value for AGC_LNAMIXRFATT21           */
#define _AGC_PNRFATT6_LNAMIXRFATT21_MASK               0x3FF00000UL                                /**< Bit mask for AGC_LNAMIXRFATT21              */
#define _AGC_PNRFATT6_LNAMIXRFATT21_DEFAULT            0x0000002FUL                                /**< Mode DEFAULT for AGC_PNRFATT6               */
#define AGC_PNRFATT6_LNAMIXRFATT21_DEFAULT             (_AGC_PNRFATT6_LNAMIXRFATT21_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_PNRFATT6       */

/* Bit fields for AGC PNRFATT7 */
#define _AGC_PNRFATT7_RESETVALUE                       0x07F1B83FUL                                /**< Default value for AGC_PNRFATT7              */
#define _AGC_PNRFATT7_MASK                             0x3FFFFFFFUL                                /**< Mask for AGC_PNRFATT7                       */
#define _AGC_PNRFATT7_LNAMIXRFATT22_SHIFT              0                                           /**< Shift value for AGC_LNAMIXRFATT22           */
#define _AGC_PNRFATT7_LNAMIXRFATT22_MASK               0x3FFUL                                     /**< Bit mask for AGC_LNAMIXRFATT22              */
#define _AGC_PNRFATT7_LNAMIXRFATT22_DEFAULT            0x0000003FUL                                /**< Mode DEFAULT for AGC_PNRFATT7               */
#define AGC_PNRFATT7_LNAMIXRFATT22_DEFAULT             (_AGC_PNRFATT7_LNAMIXRFATT22_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFATT7       */
#define _AGC_PNRFATT7_LNAMIXRFATT23_SHIFT              10                                          /**< Shift value for AGC_LNAMIXRFATT23           */
#define _AGC_PNRFATT7_LNAMIXRFATT23_MASK               0xFFC00UL                                   /**< Bit mask for AGC_LNAMIXRFATT23              */
#define _AGC_PNRFATT7_LNAMIXRFATT23_DEFAULT            0x0000006EUL                                /**< Mode DEFAULT for AGC_PNRFATT7               */
#define AGC_PNRFATT7_LNAMIXRFATT23_DEFAULT             (_AGC_PNRFATT7_LNAMIXRFATT23_DEFAULT << 10) /**< Shifted mode DEFAULT for AGC_PNRFATT7       */
#define _AGC_PNRFATT7_LNAMIXRFATT24_SHIFT              20                                          /**< Shift value for AGC_LNAMIXRFATT24           */
#define _AGC_PNRFATT7_LNAMIXRFATT24_MASK               0x3FF00000UL                                /**< Bit mask for AGC_LNAMIXRFATT24              */
#define _AGC_PNRFATT7_LNAMIXRFATT24_DEFAULT            0x0000007FUL                                /**< Mode DEFAULT for AGC_PNRFATT7               */
#define AGC_PNRFATT7_LNAMIXRFATT24_DEFAULT             (_AGC_PNRFATT7_LNAMIXRFATT24_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_PNRFATT7       */

/* Bit fields for AGC PNRFATTALT */
#define _AGC_PNRFATTALT_RESETVALUE                     0x0000007FUL                                  /**< Default value for AGC_PNRFATTALT            */
#define _AGC_PNRFATTALT_MASK                           0x000003FFUL                                  /**< Mask for AGC_PNRFATTALT                     */
#define _AGC_PNRFATTALT_LNAMIXRFATTALT_SHIFT           0                                             /**< Shift value for AGC_LNAMIXRFATTALT          */
#define _AGC_PNRFATTALT_LNAMIXRFATTALT_MASK            0x3FFUL                                       /**< Bit mask for AGC_LNAMIXRFATTALT             */
#define _AGC_PNRFATTALT_LNAMIXRFATTALT_DEFAULT         0x0000007FUL                                  /**< Mode DEFAULT for AGC_PNRFATTALT             */
#define AGC_PNRFATTALT_LNAMIXRFATTALT_DEFAULT          (_AGC_PNRFATTALT_LNAMIXRFATTALT_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_PNRFATTALT     */

/* Bit fields for AGC LNAMIXCODE0 */
#define _AGC_LNAMIXCODE0_RESETVALUE                    0x15724BBDUL                                  /**< Default value for AGC_LNAMIXCODE0           */
#define _AGC_LNAMIXCODE0_MASK                          0x3FFFFFFFUL                                  /**< Mask for AGC_LNAMIXCODE0                    */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE1_SHIFT            0                                             /**< Shift value for AGC_LNAMIXSLICE1            */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE1_MASK             0x3FUL                                        /**< Bit mask for AGC_LNAMIXSLICE1               */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE1_DEFAULT          0x0000003DUL                                  /**< Mode DEFAULT for AGC_LNAMIXCODE0            */
#define AGC_LNAMIXCODE0_LNAMIXSLICE1_DEFAULT           (_AGC_LNAMIXCODE0_LNAMIXSLICE1_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_LNAMIXCODE0    */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE2_SHIFT            6                                             /**< Shift value for AGC_LNAMIXSLICE2            */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE2_MASK             0xFC0UL                                       /**< Bit mask for AGC_LNAMIXSLICE2               */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE2_DEFAULT          0x0000002EUL                                  /**< Mode DEFAULT for AGC_LNAMIXCODE0            */
#define AGC_LNAMIXCODE0_LNAMIXSLICE2_DEFAULT           (_AGC_LNAMIXCODE0_LNAMIXSLICE2_DEFAULT << 6)  /**< Shifted mode DEFAULT for AGC_LNAMIXCODE0    */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE3_SHIFT            12                                            /**< Shift value for AGC_LNAMIXSLICE3            */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE3_MASK             0x3F000UL                                     /**< Bit mask for AGC_LNAMIXSLICE3               */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE3_DEFAULT          0x00000024UL                                  /**< Mode DEFAULT for AGC_LNAMIXCODE0            */
#define AGC_LNAMIXCODE0_LNAMIXSLICE3_DEFAULT           (_AGC_LNAMIXCODE0_LNAMIXSLICE3_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_LNAMIXCODE0    */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE4_SHIFT            18                                            /**< Shift value for AGC_LNAMIXSLICE4            */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE4_MASK             0xFC0000UL                                    /**< Bit mask for AGC_LNAMIXSLICE4               */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE4_DEFAULT          0x0000001CUL                                  /**< Mode DEFAULT for AGC_LNAMIXCODE0            */
#define AGC_LNAMIXCODE0_LNAMIXSLICE4_DEFAULT           (_AGC_LNAMIXCODE0_LNAMIXSLICE4_DEFAULT << 18) /**< Shifted mode DEFAULT for AGC_LNAMIXCODE0    */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE5_SHIFT            24                                            /**< Shift value for AGC_LNAMIXSLICE5            */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE5_MASK             0x3F000000UL                                  /**< Bit mask for AGC_LNAMIXSLICE5               */
#define _AGC_LNAMIXCODE0_LNAMIXSLICE5_DEFAULT          0x00000015UL                                  /**< Mode DEFAULT for AGC_LNAMIXCODE0            */
#define AGC_LNAMIXCODE0_LNAMIXSLICE5_DEFAULT           (_AGC_LNAMIXCODE0_LNAMIXSLICE5_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_LNAMIXCODE0    */

/* Bit fields for AGC LNAMIXCODE1 */
#define _AGC_LNAMIXCODE1_RESETVALUE                    0x0518A311UL                                   /**< Default value for AGC_LNAMIXCODE1           */
#define _AGC_LNAMIXCODE1_MASK                          0x3FFFFFFFUL                                   /**< Mask for AGC_LNAMIXCODE1                    */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE6_SHIFT            0                                              /**< Shift value for AGC_LNAMIXSLICE6            */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE6_MASK             0x3FUL                                         /**< Bit mask for AGC_LNAMIXSLICE6               */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE6_DEFAULT          0x00000011UL                                   /**< Mode DEFAULT for AGC_LNAMIXCODE1            */
#define AGC_LNAMIXCODE1_LNAMIXSLICE6_DEFAULT           (_AGC_LNAMIXCODE1_LNAMIXSLICE6_DEFAULT << 0)   /**< Shifted mode DEFAULT for AGC_LNAMIXCODE1    */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE7_SHIFT            6                                              /**< Shift value for AGC_LNAMIXSLICE7            */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE7_MASK             0xFC0UL                                        /**< Bit mask for AGC_LNAMIXSLICE7               */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE7_DEFAULT          0x0000000CUL                                   /**< Mode DEFAULT for AGC_LNAMIXCODE1            */
#define AGC_LNAMIXCODE1_LNAMIXSLICE7_DEFAULT           (_AGC_LNAMIXCODE1_LNAMIXSLICE7_DEFAULT << 6)   /**< Shifted mode DEFAULT for AGC_LNAMIXCODE1    */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE8_SHIFT            12                                             /**< Shift value for AGC_LNAMIXSLICE8            */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE8_MASK             0x3F000UL                                      /**< Bit mask for AGC_LNAMIXSLICE8               */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE8_DEFAULT          0x0000000AUL                                   /**< Mode DEFAULT for AGC_LNAMIXCODE1            */
#define AGC_LNAMIXCODE1_LNAMIXSLICE8_DEFAULT           (_AGC_LNAMIXCODE1_LNAMIXSLICE8_DEFAULT << 12)  /**< Shifted mode DEFAULT for AGC_LNAMIXCODE1    */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE9_SHIFT            18                                             /**< Shift value for AGC_LNAMIXSLICE9            */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE9_MASK             0xFC0000UL                                     /**< Bit mask for AGC_LNAMIXSLICE9               */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE9_DEFAULT          0x00000006UL                                   /**< Mode DEFAULT for AGC_LNAMIXCODE1            */
#define AGC_LNAMIXCODE1_LNAMIXSLICE9_DEFAULT           (_AGC_LNAMIXCODE1_LNAMIXSLICE9_DEFAULT << 18)  /**< Shifted mode DEFAULT for AGC_LNAMIXCODE1    */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE10_SHIFT           24                                             /**< Shift value for AGC_LNAMIXSLICE10           */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE10_MASK            0x3F000000UL                                   /**< Bit mask for AGC_LNAMIXSLICE10              */
#define _AGC_LNAMIXCODE1_LNAMIXSLICE10_DEFAULT         0x00000005UL                                   /**< Mode DEFAULT for AGC_LNAMIXCODE1            */
#define AGC_LNAMIXCODE1_LNAMIXSLICE10_DEFAULT          (_AGC_LNAMIXCODE1_LNAMIXSLICE10_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_LNAMIXCODE1    */

/* Bit fields for AGC PGACODE0 */
#define _AGC_PGACODE0_RESETVALUE                       0x76543210UL                           /**< Default value for AGC_PGACODE0              */
#define _AGC_PGACODE0_MASK                             0xFFFFFFFFUL                           /**< Mask for AGC_PGACODE0                       */
#define _AGC_PGACODE0_PGAGAIN1_SHIFT                   0                                      /**< Shift value for AGC_PGAGAIN1                */
#define _AGC_PGACODE0_PGAGAIN1_MASK                    0xFUL                                  /**< Bit mask for AGC_PGAGAIN1                   */
#define _AGC_PGACODE0_PGAGAIN1_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for AGC_PGACODE0               */
#define AGC_PGACODE0_PGAGAIN1_DEFAULT                  (_AGC_PGACODE0_PGAGAIN1_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PGACODE0       */
#define _AGC_PGACODE0_PGAGAIN2_SHIFT                   4                                      /**< Shift value for AGC_PGAGAIN2                */
#define _AGC_PGACODE0_PGAGAIN2_MASK                    0xF0UL                                 /**< Bit mask for AGC_PGAGAIN2                   */
#define _AGC_PGACODE0_PGAGAIN2_DEFAULT                 0x00000001UL                           /**< Mode DEFAULT for AGC_PGACODE0               */
#define AGC_PGACODE0_PGAGAIN2_DEFAULT                  (_AGC_PGACODE0_PGAGAIN2_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_PGACODE0       */
#define _AGC_PGACODE0_PGAGAIN3_SHIFT                   8                                      /**< Shift value for AGC_PGAGAIN3                */
#define _AGC_PGACODE0_PGAGAIN3_MASK                    0xF00UL                                /**< Bit mask for AGC_PGAGAIN3                   */
#define _AGC_PGACODE0_PGAGAIN3_DEFAULT                 0x00000002UL                           /**< Mode DEFAULT for AGC_PGACODE0               */
#define AGC_PGACODE0_PGAGAIN3_DEFAULT                  (_AGC_PGACODE0_PGAGAIN3_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_PGACODE0       */
#define _AGC_PGACODE0_PGAGAIN4_SHIFT                   12                                     /**< Shift value for AGC_PGAGAIN4                */
#define _AGC_PGACODE0_PGAGAIN4_MASK                    0xF000UL                               /**< Bit mask for AGC_PGAGAIN4                   */
#define _AGC_PGACODE0_PGAGAIN4_DEFAULT                 0x00000003UL                           /**< Mode DEFAULT for AGC_PGACODE0               */
#define AGC_PGACODE0_PGAGAIN4_DEFAULT                  (_AGC_PGACODE0_PGAGAIN4_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_PGACODE0       */
#define _AGC_PGACODE0_PGAGAIN5_SHIFT                   16                                     /**< Shift value for AGC_PGAGAIN5                */
#define _AGC_PGACODE0_PGAGAIN5_MASK                    0xF0000UL                              /**< Bit mask for AGC_PGAGAIN5                   */
#define _AGC_PGACODE0_PGAGAIN5_DEFAULT                 0x00000004UL                           /**< Mode DEFAULT for AGC_PGACODE0               */
#define AGC_PGACODE0_PGAGAIN5_DEFAULT                  (_AGC_PGACODE0_PGAGAIN5_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_PGACODE0       */
#define _AGC_PGACODE0_PGAGAIN6_SHIFT                   20                                     /**< Shift value for AGC_PGAGAIN6                */
#define _AGC_PGACODE0_PGAGAIN6_MASK                    0xF00000UL                             /**< Bit mask for AGC_PGAGAIN6                   */
#define _AGC_PGACODE0_PGAGAIN6_DEFAULT                 0x00000005UL                           /**< Mode DEFAULT for AGC_PGACODE0               */
#define AGC_PGACODE0_PGAGAIN6_DEFAULT                  (_AGC_PGACODE0_PGAGAIN6_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_PGACODE0       */
#define _AGC_PGACODE0_PGAGAIN7_SHIFT                   24                                     /**< Shift value for AGC_PGAGAIN7                */
#define _AGC_PGACODE0_PGAGAIN7_MASK                    0xF000000UL                            /**< Bit mask for AGC_PGAGAIN7                   */
#define _AGC_PGACODE0_PGAGAIN7_DEFAULT                 0x00000006UL                           /**< Mode DEFAULT for AGC_PGACODE0               */
#define AGC_PGACODE0_PGAGAIN7_DEFAULT                  (_AGC_PGACODE0_PGAGAIN7_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_PGACODE0       */
#define _AGC_PGACODE0_PGAGAIN8_SHIFT                   28                                     /**< Shift value for AGC_PGAGAIN8                */
#define _AGC_PGACODE0_PGAGAIN8_MASK                    0xF0000000UL                           /**< Bit mask for AGC_PGAGAIN8                   */
#define _AGC_PGACODE0_PGAGAIN8_DEFAULT                 0x00000007UL                           /**< Mode DEFAULT for AGC_PGACODE0               */
#define AGC_PGACODE0_PGAGAIN8_DEFAULT                  (_AGC_PGACODE0_PGAGAIN8_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_PGACODE0       */

/* Bit fields for AGC PGACODE1 */
#define _AGC_PGACODE1_RESETVALUE                       0x00000A98UL                           /**< Default value for AGC_PGACODE1              */
#define _AGC_PGACODE1_MASK                             0x00000FFFUL                           /**< Mask for AGC_PGACODE1                       */
#define _AGC_PGACODE1_PGAGAIN9_SHIFT                   0                                      /**< Shift value for AGC_PGAGAIN9                */
#define _AGC_PGACODE1_PGAGAIN9_MASK                    0xFUL                                  /**< Bit mask for AGC_PGAGAIN9                   */
#define _AGC_PGACODE1_PGAGAIN9_DEFAULT                 0x00000008UL                           /**< Mode DEFAULT for AGC_PGACODE1               */
#define AGC_PGACODE1_PGAGAIN9_DEFAULT                  (_AGC_PGACODE1_PGAGAIN9_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PGACODE1       */
#define _AGC_PGACODE1_PGAGAIN10_SHIFT                  4                                      /**< Shift value for AGC_PGAGAIN10               */
#define _AGC_PGACODE1_PGAGAIN10_MASK                   0xF0UL                                 /**< Bit mask for AGC_PGAGAIN10                  */
#define _AGC_PGACODE1_PGAGAIN10_DEFAULT                0x00000009UL                           /**< Mode DEFAULT for AGC_PGACODE1               */
#define AGC_PGACODE1_PGAGAIN10_DEFAULT                 (_AGC_PGACODE1_PGAGAIN10_DEFAULT << 4) /**< Shifted mode DEFAULT for AGC_PGACODE1       */
#define _AGC_PGACODE1_PGAGAIN11_SHIFT                  8                                      /**< Shift value for AGC_PGAGAIN11               */
#define _AGC_PGACODE1_PGAGAIN11_MASK                   0xF00UL                                /**< Bit mask for AGC_PGAGAIN11                  */
#define _AGC_PGACODE1_PGAGAIN11_DEFAULT                0x0000000AUL                           /**< Mode DEFAULT for AGC_PGACODE1               */
#define AGC_PGACODE1_PGAGAIN11_DEFAULT                 (_AGC_PGACODE1_PGAGAIN11_DEFAULT << 8) /**< Shifted mode DEFAULT for AGC_PGACODE1       */

/* Bit fields for AGC LBT */
#define _AGC_LBT_RESETVALUE                            0x00000000UL                             /**< Default value for AGC_LBT                   */
#define _AGC_LBT_MASK                                  0x0000007FUL                             /**< Mask for AGC_LBT                            */
#define _AGC_LBT_CCARSSIPERIOD_SHIFT                   0                                        /**< Shift value for AGC_CCARSSIPERIOD           */
#define _AGC_LBT_CCARSSIPERIOD_MASK                    0xFUL                                    /**< Bit mask for AGC_CCARSSIPERIOD              */
#define _AGC_LBT_CCARSSIPERIOD_DEFAULT                 0x00000000UL                             /**< Mode DEFAULT for AGC_LBT                    */
#define AGC_LBT_CCARSSIPERIOD_DEFAULT                  (_AGC_LBT_CCARSSIPERIOD_DEFAULT << 0)    /**< Shifted mode DEFAULT for AGC_LBT            */
#define AGC_LBT_ENCCARSSIPERIOD                        (0x1UL << 4)                             /**< RSSI PERIOD during CCA measurements         */
#define _AGC_LBT_ENCCARSSIPERIOD_SHIFT                 4                                        /**< Shift value for AGC_ENCCARSSIPERIOD         */
#define _AGC_LBT_ENCCARSSIPERIOD_MASK                  0x10UL                                   /**< Bit mask for AGC_ENCCARSSIPERIOD            */
#define _AGC_LBT_ENCCARSSIPERIOD_DEFAULT               0x00000000UL                             /**< Mode DEFAULT for AGC_LBT                    */
#define AGC_LBT_ENCCARSSIPERIOD_DEFAULT                (_AGC_LBT_ENCCARSSIPERIOD_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_LBT            */
#define AGC_LBT_ENCCAGAINREDUCED                       (0x1UL << 5)                             /**< CCA gain reduced                            */
#define _AGC_LBT_ENCCAGAINREDUCED_SHIFT                5                                        /**< Shift value for AGC_ENCCAGAINREDUCED        */
#define _AGC_LBT_ENCCAGAINREDUCED_MASK                 0x20UL                                   /**< Bit mask for AGC_ENCCAGAINREDUCED           */
#define _AGC_LBT_ENCCAGAINREDUCED_DEFAULT              0x00000000UL                             /**< Mode DEFAULT for AGC_LBT                    */
#define AGC_LBT_ENCCAGAINREDUCED_DEFAULT               (_AGC_LBT_ENCCAGAINREDUCED_DEFAULT << 5) /**< Shifted mode DEFAULT for AGC_LBT            */
#define AGC_LBT_ENCCARSSIMAX                           (0x1UL << 6)                             /**< Use RSSIMAX to indicate CCA                 */
#define _AGC_LBT_ENCCARSSIMAX_SHIFT                    6                                        /**< Shift value for AGC_ENCCARSSIMAX            */
#define _AGC_LBT_ENCCARSSIMAX_MASK                     0x40UL                                   /**< Bit mask for AGC_ENCCARSSIMAX               */
#define _AGC_LBT_ENCCARSSIMAX_DEFAULT                  0x00000000UL                             /**< Mode DEFAULT for AGC_LBT                    */
#define AGC_LBT_ENCCARSSIMAX_DEFAULT                   (_AGC_LBT_ENCCARSSIMAX_DEFAULT << 6)     /**< Shifted mode DEFAULT for AGC_LBT            */

/* Bit fields for AGC MIRRORIF */
#define _AGC_MIRRORIF_RESETVALUE                       0x00000000UL                                   /**< Default value for AGC_MIRRORIF              */
#define _AGC_MIRRORIF_MASK                             0x0000000FUL                                   /**< Mask for AGC_MIRRORIF                       */
#define AGC_MIRRORIF_RSSIPOSSTEPM                      (0x1UL << 0)                                   /**< Positive RSSI Step Detected                 */
#define _AGC_MIRRORIF_RSSIPOSSTEPM_SHIFT               0                                              /**< Shift value for AGC_RSSIPOSSTEPM            */
#define _AGC_MIRRORIF_RSSIPOSSTEPM_MASK                0x1UL                                          /**< Bit mask for AGC_RSSIPOSSTEPM               */
#define _AGC_MIRRORIF_RSSIPOSSTEPM_DEFAULT             0x00000000UL                                   /**< Mode DEFAULT for AGC_MIRRORIF               */
#define AGC_MIRRORIF_RSSIPOSSTEPM_DEFAULT              (_AGC_MIRRORIF_RSSIPOSSTEPM_DEFAULT << 0)      /**< Shifted mode DEFAULT for AGC_MIRRORIF       */
#define AGC_MIRRORIF_RSSINEGSTEPM                      (0x1UL << 1)                                   /**< Negative RSSI Step Detected                 */
#define _AGC_MIRRORIF_RSSINEGSTEPM_SHIFT               1                                              /**< Shift value for AGC_RSSINEGSTEPM            */
#define _AGC_MIRRORIF_RSSINEGSTEPM_MASK                0x2UL                                          /**< Bit mask for AGC_RSSINEGSTEPM               */
#define _AGC_MIRRORIF_RSSINEGSTEPM_DEFAULT             0x00000000UL                                   /**< Mode DEFAULT for AGC_MIRRORIF               */
#define AGC_MIRRORIF_RSSINEGSTEPM_DEFAULT              (_AGC_MIRRORIF_RSSINEGSTEPM_DEFAULT << 1)      /**< Shifted mode DEFAULT for AGC_MIRRORIF       */
#define AGC_MIRRORIF_SHORTRSSIPOSSTEPM                 (0x1UL << 2)                                   /**< Short-term Positive RSSI Step Detected      */
#define _AGC_MIRRORIF_SHORTRSSIPOSSTEPM_SHIFT          2                                              /**< Shift value for AGC_SHORTRSSIPOSSTEPM       */
#define _AGC_MIRRORIF_SHORTRSSIPOSSTEPM_MASK           0x4UL                                          /**< Bit mask for AGC_SHORTRSSIPOSSTEPM          */
#define _AGC_MIRRORIF_SHORTRSSIPOSSTEPM_DEFAULT        0x00000000UL                                   /**< Mode DEFAULT for AGC_MIRRORIF               */
#define AGC_MIRRORIF_SHORTRSSIPOSSTEPM_DEFAULT         (_AGC_MIRRORIF_SHORTRSSIPOSSTEPM_DEFAULT << 2) /**< Shifted mode DEFAULT for AGC_MIRRORIF       */
#define AGC_MIRRORIF_IFMIRRORCLEAR                     (0x1UL << 3)                                   /**< Clear bit for the AGC IF MIRROR Register    */
#define _AGC_MIRRORIF_IFMIRRORCLEAR_SHIFT              3                                              /**< Shift value for AGC_IFMIRRORCLEAR           */
#define _AGC_MIRRORIF_IFMIRRORCLEAR_MASK               0x8UL                                          /**< Bit mask for AGC_IFMIRRORCLEAR              */
#define _AGC_MIRRORIF_IFMIRRORCLEAR_DEFAULT            0x00000000UL                                   /**< Mode DEFAULT for AGC_MIRRORIF               */
#define AGC_MIRRORIF_IFMIRRORCLEAR_DEFAULT             (_AGC_MIRRORIF_IFMIRRORCLEAR_DEFAULT << 3)     /**< Shifted mode DEFAULT for AGC_MIRRORIF       */

/* Bit fields for AGC SEQIF */
#define _AGC_SEQIF_RESETVALUE                          0x00000000UL                                /**< Default value for AGC_SEQIF                 */
#define _AGC_SEQIF_MASK                                0x00007F7DUL                                /**< Mask for AGC_SEQIF                          */
#define AGC_SEQIF_RSSIVALID                            (0x1UL << 0)                                /**< RSSI Value is Valid                         */
#define _AGC_SEQIF_RSSIVALID_SHIFT                     0                                           /**< Shift value for AGC_RSSIVALID               */
#define _AGC_SEQIF_RSSIVALID_MASK                      0x1UL                                       /**< Bit mask for AGC_RSSIVALID                  */
#define _AGC_SEQIF_RSSIVALID_DEFAULT                   0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_RSSIVALID_DEFAULT                    (_AGC_SEQIF_RSSIVALID_DEFAULT << 0)         /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_CCA                                  (0x1UL << 2)                                /**< Clear Channel Assessment                    */
#define _AGC_SEQIF_CCA_SHIFT                           2                                           /**< Shift value for AGC_CCA                     */
#define _AGC_SEQIF_CCA_MASK                            0x4UL                                       /**< Bit mask for AGC_CCA                        */
#define _AGC_SEQIF_CCA_DEFAULT                         0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_CCA_DEFAULT                          (_AGC_SEQIF_CCA_DEFAULT << 2)               /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_RSSIPOSSTEP                          (0x1UL << 3)                                /**< Positive RSSI Step Detected                 */
#define _AGC_SEQIF_RSSIPOSSTEP_SHIFT                   3                                           /**< Shift value for AGC_RSSIPOSSTEP             */
#define _AGC_SEQIF_RSSIPOSSTEP_MASK                    0x8UL                                       /**< Bit mask for AGC_RSSIPOSSTEP                */
#define _AGC_SEQIF_RSSIPOSSTEP_DEFAULT                 0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_RSSIPOSSTEP_DEFAULT                  (_AGC_SEQIF_RSSIPOSSTEP_DEFAULT << 3)       /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_RSSINEGSTEP                          (0x1UL << 4)                                /**< Negative RSSI Step Detected                 */
#define _AGC_SEQIF_RSSINEGSTEP_SHIFT                   4                                           /**< Shift value for AGC_RSSINEGSTEP             */
#define _AGC_SEQIF_RSSINEGSTEP_MASK                    0x10UL                                      /**< Bit mask for AGC_RSSINEGSTEP                */
#define _AGC_SEQIF_RSSINEGSTEP_DEFAULT                 0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_RSSINEGSTEP_DEFAULT                  (_AGC_SEQIF_RSSINEGSTEP_DEFAULT << 4)       /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_SHORTRSSIPOSSTEP                     (0x1UL << 6)                                /**< Short-term Positive RSSI Step Detected      */
#define _AGC_SEQIF_SHORTRSSIPOSSTEP_SHIFT              6                                           /**< Shift value for AGC_SHORTRSSIPOSSTEP        */
#define _AGC_SEQIF_SHORTRSSIPOSSTEP_MASK               0x40UL                                      /**< Bit mask for AGC_SHORTRSSIPOSSTEP           */
#define _AGC_SEQIF_SHORTRSSIPOSSTEP_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_SHORTRSSIPOSSTEP_DEFAULT             (_AGC_SEQIF_SHORTRSSIPOSSTEP_DEFAULT << 6)  /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_RFPKDPRDDONE                         (0x1UL << 8)                                /**< RF PKD PERIOD CNT TOMEOUT                   */
#define _AGC_SEQIF_RFPKDPRDDONE_SHIFT                  8                                           /**< Shift value for AGC_RFPKDPRDDONE            */
#define _AGC_SEQIF_RFPKDPRDDONE_MASK                   0x100UL                                     /**< Bit mask for AGC_RFPKDPRDDONE               */
#define _AGC_SEQIF_RFPKDPRDDONE_DEFAULT                0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_RFPKDPRDDONE_DEFAULT                 (_AGC_SEQIF_RFPKDPRDDONE_DEFAULT << 8)      /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_RFPKDCNTDONE                         (0x1UL << 9)                                /**< RF PKD pulse CNT TOMEOUT                    */
#define _AGC_SEQIF_RFPKDCNTDONE_SHIFT                  9                                           /**< Shift value for AGC_RFPKDCNTDONE            */
#define _AGC_SEQIF_RFPKDCNTDONE_MASK                   0x200UL                                     /**< Bit mask for AGC_RFPKDCNTDONE               */
#define _AGC_SEQIF_RFPKDCNTDONE_DEFAULT                0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_RFPKDCNTDONE_DEFAULT                 (_AGC_SEQIF_RFPKDCNTDONE_DEFAULT << 9)      /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_RSSIHIGH                             (0x1UL << 10)                               /**< RSSI high detected                          */
#define _AGC_SEQIF_RSSIHIGH_SHIFT                      10                                          /**< Shift value for AGC_RSSIHIGH                */
#define _AGC_SEQIF_RSSIHIGH_MASK                       0x400UL                                     /**< Bit mask for AGC_RSSIHIGH                   */
#define _AGC_SEQIF_RSSIHIGH_DEFAULT                    0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_RSSIHIGH_DEFAULT                     (_AGC_SEQIF_RSSIHIGH_DEFAULT << 10)         /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_RSSILOW                              (0x1UL << 11)                               /**< RSSI low detected                           */
#define _AGC_SEQIF_RSSILOW_SHIFT                       11                                          /**< Shift value for AGC_RSSILOW                 */
#define _AGC_SEQIF_RSSILOW_MASK                        0x800UL                                     /**< Bit mask for AGC_RSSILOW                    */
#define _AGC_SEQIF_RSSILOW_DEFAULT                     0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_RSSILOW_DEFAULT                      (_AGC_SEQIF_RSSILOW_DEFAULT << 11)          /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_CCANODET                             (0x1UL << 12)                               /**< CCA Not Detected                            */
#define _AGC_SEQIF_CCANODET_SHIFT                      12                                          /**< Shift value for AGC_CCANODET                */
#define _AGC_SEQIF_CCANODET_MASK                       0x1000UL                                    /**< Bit mask for AGC_CCANODET                   */
#define _AGC_SEQIF_CCANODET_DEFAULT                    0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_CCANODET_DEFAULT                     (_AGC_SEQIF_CCANODET_DEFAULT << 12)         /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_GAINBELOWGAINTHD                     (0x1UL << 13)                               /**< agc gain above threshold int                */
#define _AGC_SEQIF_GAINBELOWGAINTHD_SHIFT              13                                          /**< Shift value for AGC_GAINBELOWGAINTHD        */
#define _AGC_SEQIF_GAINBELOWGAINTHD_MASK               0x2000UL                                    /**< Bit mask for AGC_GAINBELOWGAINTHD           */
#define _AGC_SEQIF_GAINBELOWGAINTHD_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_GAINBELOWGAINTHD_DEFAULT             (_AGC_SEQIF_GAINBELOWGAINTHD_DEFAULT << 13) /**< Shifted mode DEFAULT for AGC_SEQIF          */
#define AGC_SEQIF_GAINUPDATEFRZ                        (0x1UL << 14)                               /**< AGC gain update frozen int                  */
#define _AGC_SEQIF_GAINUPDATEFRZ_SHIFT                 14                                          /**< Shift value for AGC_GAINUPDATEFRZ           */
#define _AGC_SEQIF_GAINUPDATEFRZ_MASK                  0x4000UL                                    /**< Bit mask for AGC_GAINUPDATEFRZ              */
#define _AGC_SEQIF_GAINUPDATEFRZ_DEFAULT               0x00000000UL                                /**< Mode DEFAULT for AGC_SEQIF                  */
#define AGC_SEQIF_GAINUPDATEFRZ_DEFAULT                (_AGC_SEQIF_GAINUPDATEFRZ_DEFAULT << 14)    /**< Shifted mode DEFAULT for AGC_SEQIF          */

/* Bit fields for AGC SEQIEN */
#define _AGC_SEQIEN_RESETVALUE                         0x00000000UL                                 /**< Default value for AGC_SEQIEN                */
#define _AGC_SEQIEN_MASK                               0x00007F7DUL                                 /**< Mask for AGC_SEQIEN                         */
#define AGC_SEQIEN_RSSIVALID                           (0x1UL << 0)                                 /**< RSSIVALID Interrupt Enable                  */
#define _AGC_SEQIEN_RSSIVALID_SHIFT                    0                                            /**< Shift value for AGC_RSSIVALID               */
#define _AGC_SEQIEN_RSSIVALID_MASK                     0x1UL                                        /**< Bit mask for AGC_RSSIVALID                  */
#define _AGC_SEQIEN_RSSIVALID_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_RSSIVALID_DEFAULT                   (_AGC_SEQIEN_RSSIVALID_DEFAULT << 0)         /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_CCA                                 (0x1UL << 2)                                 /**< CCA Interrupt Enable                        */
#define _AGC_SEQIEN_CCA_SHIFT                          2                                            /**< Shift value for AGC_CCA                     */
#define _AGC_SEQIEN_CCA_MASK                           0x4UL                                        /**< Bit mask for AGC_CCA                        */
#define _AGC_SEQIEN_CCA_DEFAULT                        0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_CCA_DEFAULT                         (_AGC_SEQIEN_CCA_DEFAULT << 2)               /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_RSSIPOSSTEP                         (0x1UL << 3)                                 /**< RSSIPOSSTEP Interrupt Enable                */
#define _AGC_SEQIEN_RSSIPOSSTEP_SHIFT                  3                                            /**< Shift value for AGC_RSSIPOSSTEP             */
#define _AGC_SEQIEN_RSSIPOSSTEP_MASK                   0x8UL                                        /**< Bit mask for AGC_RSSIPOSSTEP                */
#define _AGC_SEQIEN_RSSIPOSSTEP_DEFAULT                0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_RSSIPOSSTEP_DEFAULT                 (_AGC_SEQIEN_RSSIPOSSTEP_DEFAULT << 3)       /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_RSSINEGSTEP                         (0x1UL << 4)                                 /**< RSSINEGSTEP Interrupt Enable                */
#define _AGC_SEQIEN_RSSINEGSTEP_SHIFT                  4                                            /**< Shift value for AGC_RSSINEGSTEP             */
#define _AGC_SEQIEN_RSSINEGSTEP_MASK                   0x10UL                                       /**< Bit mask for AGC_RSSINEGSTEP                */
#define _AGC_SEQIEN_RSSINEGSTEP_DEFAULT                0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_RSSINEGSTEP_DEFAULT                 (_AGC_SEQIEN_RSSINEGSTEP_DEFAULT << 4)       /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_SHORTRSSIPOSSTEP                    (0x1UL << 6)                                 /**< SHORTRSSIPOSSTEP Interrupt Enable           */
#define _AGC_SEQIEN_SHORTRSSIPOSSTEP_SHIFT             6                                            /**< Shift value for AGC_SHORTRSSIPOSSTEP        */
#define _AGC_SEQIEN_SHORTRSSIPOSSTEP_MASK              0x40UL                                       /**< Bit mask for AGC_SHORTRSSIPOSSTEP           */
#define _AGC_SEQIEN_SHORTRSSIPOSSTEP_DEFAULT           0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_SHORTRSSIPOSSTEP_DEFAULT            (_AGC_SEQIEN_SHORTRSSIPOSSTEP_DEFAULT << 6)  /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_RFPKDPRDDONE                        (0x1UL << 8)                                 /**< RF PKD PERIOD CNT Interrupt Enable          */
#define _AGC_SEQIEN_RFPKDPRDDONE_SHIFT                 8                                            /**< Shift value for AGC_RFPKDPRDDONE            */
#define _AGC_SEQIEN_RFPKDPRDDONE_MASK                  0x100UL                                      /**< Bit mask for AGC_RFPKDPRDDONE               */
#define _AGC_SEQIEN_RFPKDPRDDONE_DEFAULT               0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_RFPKDPRDDONE_DEFAULT                (_AGC_SEQIEN_RFPKDPRDDONE_DEFAULT << 8)      /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_RFPKDCNTDONE                        (0x1UL << 9)                                 /**< RF PKD pulse CNT Interrupt Enable           */
#define _AGC_SEQIEN_RFPKDCNTDONE_SHIFT                 9                                            /**< Shift value for AGC_RFPKDCNTDONE            */
#define _AGC_SEQIEN_RFPKDCNTDONE_MASK                  0x200UL                                      /**< Bit mask for AGC_RFPKDCNTDONE               */
#define _AGC_SEQIEN_RFPKDCNTDONE_DEFAULT               0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_RFPKDCNTDONE_DEFAULT                (_AGC_SEQIEN_RFPKDCNTDONE_DEFAULT << 9)      /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_RSSIHIGH                            (0x1UL << 10)                                /**< RSSIHIGH Interrupt Enable                   */
#define _AGC_SEQIEN_RSSIHIGH_SHIFT                     10                                           /**< Shift value for AGC_RSSIHIGH                */
#define _AGC_SEQIEN_RSSIHIGH_MASK                      0x400UL                                      /**< Bit mask for AGC_RSSIHIGH                   */
#define _AGC_SEQIEN_RSSIHIGH_DEFAULT                   0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_RSSIHIGH_DEFAULT                    (_AGC_SEQIEN_RSSIHIGH_DEFAULT << 10)         /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_RSSILOW                             (0x1UL << 11)                                /**< RSSILOW Interrupt Enable                    */
#define _AGC_SEQIEN_RSSILOW_SHIFT                      11                                           /**< Shift value for AGC_RSSILOW                 */
#define _AGC_SEQIEN_RSSILOW_MASK                       0x800UL                                      /**< Bit mask for AGC_RSSILOW                    */
#define _AGC_SEQIEN_RSSILOW_DEFAULT                    0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_RSSILOW_DEFAULT                     (_AGC_SEQIEN_RSSILOW_DEFAULT << 11)          /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_CCANODET                            (0x1UL << 12)                                /**< CCANODET Interrupt Enable                   */
#define _AGC_SEQIEN_CCANODET_SHIFT                     12                                           /**< Shift value for AGC_CCANODET                */
#define _AGC_SEQIEN_CCANODET_MASK                      0x1000UL                                     /**< Bit mask for AGC_CCANODET                   */
#define _AGC_SEQIEN_CCANODET_DEFAULT                   0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_CCANODET_DEFAULT                    (_AGC_SEQIEN_CCANODET_DEFAULT << 12)         /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_GAINBELOWGAINTHD                    (0x1UL << 13)                                /**< GAINBELOWGAINTHD Interrupt Enable           */
#define _AGC_SEQIEN_GAINBELOWGAINTHD_SHIFT             13                                           /**< Shift value for AGC_GAINBELOWGAINTHD        */
#define _AGC_SEQIEN_GAINBELOWGAINTHD_MASK              0x2000UL                                     /**< Bit mask for AGC_GAINBELOWGAINTHD           */
#define _AGC_SEQIEN_GAINBELOWGAINTHD_DEFAULT           0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_GAINBELOWGAINTHD_DEFAULT            (_AGC_SEQIEN_GAINBELOWGAINTHD_DEFAULT << 13) /**< Shifted mode DEFAULT for AGC_SEQIEN         */
#define AGC_SEQIEN_GAINUPDATEFRZ                       (0x1UL << 14)                                /**< AGC gain update frozen int Enable           */
#define _AGC_SEQIEN_GAINUPDATEFRZ_SHIFT                14                                           /**< Shift value for AGC_GAINUPDATEFRZ           */
#define _AGC_SEQIEN_GAINUPDATEFRZ_MASK                 0x4000UL                                     /**< Bit mask for AGC_GAINUPDATEFRZ              */
#define _AGC_SEQIEN_GAINUPDATEFRZ_DEFAULT              0x00000000UL                                 /**< Mode DEFAULT for AGC_SEQIEN                 */
#define AGC_SEQIEN_GAINUPDATEFRZ_DEFAULT               (_AGC_SEQIEN_GAINUPDATEFRZ_DEFAULT << 14)    /**< Shifted mode DEFAULT for AGC_SEQIEN         */

/* Bit fields for AGC RSSIABSTHR */
#define _AGC_RSSIABSTHR_RESETVALUE                     0x00000000UL                                     /**< Default value for AGC_RSSIABSTHR            */
#define _AGC_RSSIABSTHR_MASK                           0xFFFFFFFFUL                                     /**< Mask for AGC_RSSIABSTHR                     */
#define _AGC_RSSIABSTHR_RSSIHIGHTHRSH_SHIFT            0                                                /**< Shift value for AGC_RSSIHIGHTHRSH           */
#define _AGC_RSSIABSTHR_RSSIHIGHTHRSH_MASK             0xFFUL                                           /**< Bit mask for AGC_RSSIHIGHTHRSH              */
#define _AGC_RSSIABSTHR_RSSIHIGHTHRSH_DEFAULT          0x00000000UL                                     /**< Mode DEFAULT for AGC_RSSIABSTHR             */
#define AGC_RSSIABSTHR_RSSIHIGHTHRSH_DEFAULT           (_AGC_RSSIABSTHR_RSSIHIGHTHRSH_DEFAULT << 0)     /**< Shifted mode DEFAULT for AGC_RSSIABSTHR     */
#define _AGC_RSSIABSTHR_RSSILOWTHRSH_SHIFT             8                                                /**< Shift value for AGC_RSSILOWTHRSH            */
#define _AGC_RSSIABSTHR_RSSILOWTHRSH_MASK              0xFF00UL                                         /**< Bit mask for AGC_RSSILOWTHRSH               */
#define _AGC_RSSIABSTHR_RSSILOWTHRSH_DEFAULT           0x00000000UL                                     /**< Mode DEFAULT for AGC_RSSIABSTHR             */
#define AGC_RSSIABSTHR_RSSILOWTHRSH_DEFAULT            (_AGC_RSSIABSTHR_RSSILOWTHRSH_DEFAULT << 8)      /**< Shifted mode DEFAULT for AGC_RSSIABSTHR     */
#define _AGC_RSSIABSTHR_SIRSSIHIGHTHR_SHIFT            16                                               /**< Shift value for AGC_SIRSSIHIGHTHR           */
#define _AGC_RSSIABSTHR_SIRSSIHIGHTHR_MASK             0xFF0000UL                                       /**< Bit mask for AGC_SIRSSIHIGHTHR              */
#define _AGC_RSSIABSTHR_SIRSSIHIGHTHR_DEFAULT          0x00000000UL                                     /**< Mode DEFAULT for AGC_RSSIABSTHR             */
#define AGC_RSSIABSTHR_SIRSSIHIGHTHR_DEFAULT           (_AGC_RSSIABSTHR_SIRSSIHIGHTHR_DEFAULT << 16)    /**< Shifted mode DEFAULT for AGC_RSSIABSTHR     */
#define _AGC_RSSIABSTHR_SIRSSINEGSTEPTHR_SHIFT         24                                               /**< Shift value for AGC_SIRSSINEGSTEPTHR        */
#define _AGC_RSSIABSTHR_SIRSSINEGSTEPTHR_MASK          0xFF000000UL                                     /**< Bit mask for AGC_SIRSSINEGSTEPTHR           */
#define _AGC_RSSIABSTHR_SIRSSINEGSTEPTHR_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_RSSIABSTHR             */
#define AGC_RSSIABSTHR_SIRSSINEGSTEPTHR_DEFAULT        (_AGC_RSSIABSTHR_SIRSSINEGSTEPTHR_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_RSSIABSTHR     */

/* Bit fields for AGC LNABOOST */
#define _AGC_LNABOOST_RESETVALUE                       0x000001FEUL                               /**< Default value for AGC_LNABOOST              */
#define _AGC_LNABOOST_MASK                             0x000001FFUL                               /**< Mask for AGC_LNABOOST                       */
#define AGC_LNABOOST_BOOSTLNA                          (0x1UL << 0)                               /**< LNA GAIN BOOST mode                         */
#define _AGC_LNABOOST_BOOSTLNA_SHIFT                   0                                          /**< Shift value for AGC_BOOSTLNA                */
#define _AGC_LNABOOST_BOOSTLNA_MASK                    0x1UL                                      /**< Bit mask for AGC_BOOSTLNA                   */
#define _AGC_LNABOOST_BOOSTLNA_DEFAULT                 0x00000000UL                               /**< Mode DEFAULT for AGC_LNABOOST               */
#define AGC_LNABOOST_BOOSTLNA_DEFAULT                  (_AGC_LNABOOST_BOOSTLNA_DEFAULT << 0)      /**< Shifted mode DEFAULT for AGC_LNABOOST       */
#define _AGC_LNABOOST_LNABWADJ_SHIFT                   1                                          /**< Shift value for AGC_LNABWADJ                */
#define _AGC_LNABOOST_LNABWADJ_MASK                    0x1EUL                                     /**< Bit mask for AGC_LNABWADJ                   */
#define _AGC_LNABOOST_LNABWADJ_DEFAULT                 0x0000000FUL                               /**< Mode DEFAULT for AGC_LNABOOST               */
#define AGC_LNABOOST_LNABWADJ_DEFAULT                  (_AGC_LNABOOST_LNABWADJ_DEFAULT << 1)      /**< Shifted mode DEFAULT for AGC_LNABOOST       */
#define _AGC_LNABOOST_LNABWADJBOOST_SHIFT              5                                          /**< Shift value for AGC_LNABWADJBOOST           */
#define _AGC_LNABOOST_LNABWADJBOOST_MASK               0x1E0UL                                    /**< Bit mask for AGC_LNABWADJBOOST              */
#define _AGC_LNABOOST_LNABWADJBOOST_DEFAULT            0x0000000FUL                               /**< Mode DEFAULT for AGC_LNABOOST               */
#define AGC_LNABOOST_LNABWADJBOOST_DEFAULT             (_AGC_LNABOOST_LNABWADJBOOST_DEFAULT << 5) /**< Shifted mode DEFAULT for AGC_LNABOOST       */

/* Bit fields for AGC ANTDIV */
#define _AGC_ANTDIV_RESETVALUE                         0x00000000UL                                /**< Default value for AGC_ANTDIV                */
#define _AGC_ANTDIV_MASK                               0x000007FFUL                                /**< Mask for AGC_ANTDIV                         */
#define _AGC_ANTDIV_GAINMODE_SHIFT                     0                                           /**< Shift value for AGC_GAINMODE                */
#define _AGC_ANTDIV_GAINMODE_MASK                      0x3UL                                       /**< Bit mask for AGC_GAINMODE                   */
#define _AGC_ANTDIV_GAINMODE_DEFAULT                   0x00000000UL                                /**< Mode DEFAULT for AGC_ANTDIV                 */
#define _AGC_ANTDIV_GAINMODE_DISABLE                   0x00000000UL                                /**< Mode DISABLE for AGC_ANTDIV                 */
#define _AGC_ANTDIV_GAINMODE_SINGLE_PACKET             0x00000001UL                                /**< Mode SINGLE_PACKET for AGC_ANTDIV           */
#define _AGC_ANTDIV_GAINMODE_ALWAYS                    0x00000002UL                                /**< Mode ALWAYS for AGC_ANTDIV                  */
#define AGC_ANTDIV_GAINMODE_DEFAULT                    (_AGC_ANTDIV_GAINMODE_DEFAULT << 0)         /**< Shifted mode DEFAULT for AGC_ANTDIV         */
#define AGC_ANTDIV_GAINMODE_DISABLE                    (_AGC_ANTDIV_GAINMODE_DISABLE << 0)         /**< Shifted mode DISABLE for AGC_ANTDIV         */
#define AGC_ANTDIV_GAINMODE_SINGLE_PACKET              (_AGC_ANTDIV_GAINMODE_SINGLE_PACKET << 0)   /**< Shifted mode SINGLE_PACKET for AGC_ANTDIV   */
#define AGC_ANTDIV_GAINMODE_ALWAYS                     (_AGC_ANTDIV_GAINMODE_ALWAYS << 0)          /**< Shifted mode ALWAYS for AGC_ANTDIV          */
#define _AGC_ANTDIV_DEBOUNCECNTTHD_SHIFT               2                                           /**< Shift value for AGC_DEBOUNCECNTTHD          */
#define _AGC_ANTDIV_DEBOUNCECNTTHD_MASK                0x1FCUL                                     /**< Bit mask for AGC_DEBOUNCECNTTHD             */
#define _AGC_ANTDIV_DEBOUNCECNTTHD_DEFAULT             0x00000000UL                                /**< Mode DEFAULT for AGC_ANTDIV                 */
#define AGC_ANTDIV_DEBOUNCECNTTHD_DEFAULT              (_AGC_ANTDIV_DEBOUNCECNTTHD_DEFAULT << 2)   /**< Shifted mode DEFAULT for AGC_ANTDIV         */
#define _AGC_ANTDIV_DISRSSIANTDIVFIX_SHIFT             9                                           /**< Shift value for AGC_DISRSSIANTDIVFIX        */
#define _AGC_ANTDIV_DISRSSIANTDIVFIX_MASK              0x600UL                                     /**< Bit mask for AGC_DISRSSIANTDIVFIX           */
#define _AGC_ANTDIV_DISRSSIANTDIVFIX_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for AGC_ANTDIV                 */
#define AGC_ANTDIV_DISRSSIANTDIVFIX_DEFAULT            (_AGC_ANTDIV_DISRSSIANTDIVFIX_DEFAULT << 9) /**< Shifted mode DEFAULT for AGC_ANTDIV         */

/* Bit fields for AGC DUALRFPKDTHD0 */
#define _AGC_DUALRFPKDTHD0_RESETVALUE                  0x000A0001UL                                    /**< Default value for AGC_DUALRFPKDTHD0         */
#define _AGC_DUALRFPKDTHD0_MASK                        0x0FFF0FFFUL                                    /**< Mask for AGC_DUALRFPKDTHD0                  */
#define _AGC_DUALRFPKDTHD0_RFPKDLOWTHD0_SHIFT          0                                               /**< Shift value for AGC_RFPKDLOWTHD0            */
#define _AGC_DUALRFPKDTHD0_RFPKDLOWTHD0_MASK           0xFFFUL                                         /**< Bit mask for AGC_RFPKDLOWTHD0               */
#define _AGC_DUALRFPKDTHD0_RFPKDLOWTHD0_DEFAULT        0x00000001UL                                    /**< Mode DEFAULT for AGC_DUALRFPKDTHD0          */
#define AGC_DUALRFPKDTHD0_RFPKDLOWTHD0_DEFAULT         (_AGC_DUALRFPKDTHD0_RFPKDLOWTHD0_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_DUALRFPKDTHD0  */
#define _AGC_DUALRFPKDTHD0_RFPKDLOWTHD1_SHIFT          16                                              /**< Shift value for AGC_RFPKDLOWTHD1            */
#define _AGC_DUALRFPKDTHD0_RFPKDLOWTHD1_MASK           0xFFF0000UL                                     /**< Bit mask for AGC_RFPKDLOWTHD1               */
#define _AGC_DUALRFPKDTHD0_RFPKDLOWTHD1_DEFAULT        0x0000000AUL                                    /**< Mode DEFAULT for AGC_DUALRFPKDTHD0          */
#define AGC_DUALRFPKDTHD0_RFPKDLOWTHD1_DEFAULT         (_AGC_DUALRFPKDTHD0_RFPKDLOWTHD1_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_DUALRFPKDTHD0  */

/* Bit fields for AGC DUALRFPKDTHD1 */
#define _AGC_DUALRFPKDTHD1_RESETVALUE                  0x00280001UL                                   /**< Default value for AGC_DUALRFPKDTHD1         */
#define _AGC_DUALRFPKDTHD1_MASK                        0x0FFF0FFFUL                                   /**< Mask for AGC_DUALRFPKDTHD1                  */
#define _AGC_DUALRFPKDTHD1_RFPKDHITHD0_SHIFT           0                                              /**< Shift value for AGC_RFPKDHITHD0             */
#define _AGC_DUALRFPKDTHD1_RFPKDHITHD0_MASK            0xFFFUL                                        /**< Bit mask for AGC_RFPKDHITHD0                */
#define _AGC_DUALRFPKDTHD1_RFPKDHITHD0_DEFAULT         0x00000001UL                                   /**< Mode DEFAULT for AGC_DUALRFPKDTHD1          */
#define AGC_DUALRFPKDTHD1_RFPKDHITHD0_DEFAULT          (_AGC_DUALRFPKDTHD1_RFPKDHITHD0_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_DUALRFPKDTHD1  */
#define _AGC_DUALRFPKDTHD1_RFPKDHITHD1_SHIFT           16                                             /**< Shift value for AGC_RFPKDHITHD1             */
#define _AGC_DUALRFPKDTHD1_RFPKDHITHD1_MASK            0xFFF0000UL                                    /**< Bit mask for AGC_RFPKDHITHD1                */
#define _AGC_DUALRFPKDTHD1_RFPKDHITHD1_DEFAULT         0x00000028UL                                   /**< Mode DEFAULT for AGC_DUALRFPKDTHD1          */
#define AGC_DUALRFPKDTHD1_RFPKDHITHD1_DEFAULT          (_AGC_DUALRFPKDTHD1_RFPKDHITHD1_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_DUALRFPKDTHD1  */

/* Bit fields for AGC SPARE */
#define _AGC_SPARE_RESETVALUE                          0x00000000UL                       /**< Default value for AGC_SPARE                 */
#define _AGC_SPARE_MASK                                0x000000FFUL                       /**< Mask for AGC_SPARE                          */
#define _AGC_SPARE_SPAREREG_SHIFT                      0                                  /**< Shift value for AGC_SPAREREG                */
#define _AGC_SPARE_SPAREREG_MASK                       0xFFUL                             /**< Bit mask for AGC_SPAREREG                   */
#define _AGC_SPARE_SPAREREG_DEFAULT                    0x00000000UL                       /**< Mode DEFAULT for AGC_SPARE                  */
#define AGC_SPARE_SPAREREG_DEFAULT                     (_AGC_SPARE_SPAREREG_DEFAULT << 0) /**< Shifted mode DEFAULT for AGC_SPARE          */

/* Bit fields for AGC PNRFFILT0 */
#define _AGC_PNRFFILT0_RESETVALUE                      0x00200400UL                                /**< Default value for AGC_PNRFFILT0             */
#define _AGC_PNRFFILT0_MASK                            0x3FFFFFFFUL                                /**< Mask for AGC_PNRFFILT0                      */
#define _AGC_PNRFFILT0_LNAMIXRFATT1_SHIFT              0                                           /**< Shift value for AGC_LNAMIXRFATT1            */
#define _AGC_PNRFFILT0_LNAMIXRFATT1_MASK               0x3FFUL                                     /**< Bit mask for AGC_LNAMIXRFATT1               */
#define _AGC_PNRFFILT0_LNAMIXRFATT1_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for AGC_PNRFFILT0              */
#define AGC_PNRFFILT0_LNAMIXRFATT1_DEFAULT             (_AGC_PNRFFILT0_LNAMIXRFATT1_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFFILT0      */
#define _AGC_PNRFFILT0_LNAMIXRFATT2_SHIFT              10                                          /**< Shift value for AGC_LNAMIXRFATT2            */
#define _AGC_PNRFFILT0_LNAMIXRFATT2_MASK               0xFFC00UL                                   /**< Bit mask for AGC_LNAMIXRFATT2               */
#define _AGC_PNRFFILT0_LNAMIXRFATT2_DEFAULT            0x00000001UL                                /**< Mode DEFAULT for AGC_PNRFFILT0              */
#define AGC_PNRFFILT0_LNAMIXRFATT2_DEFAULT             (_AGC_PNRFFILT0_LNAMIXRFATT2_DEFAULT << 10) /**< Shifted mode DEFAULT for AGC_PNRFFILT0      */
#define _AGC_PNRFFILT0_LNAMIXRFATT3_SHIFT              20                                          /**< Shift value for AGC_LNAMIXRFATT3            */
#define _AGC_PNRFFILT0_LNAMIXRFATT3_MASK               0x3FF00000UL                                /**< Bit mask for AGC_LNAMIXRFATT3               */
#define _AGC_PNRFFILT0_LNAMIXRFATT3_DEFAULT            0x00000002UL                                /**< Mode DEFAULT for AGC_PNRFFILT0              */
#define AGC_PNRFFILT0_LNAMIXRFATT3_DEFAULT             (_AGC_PNRFFILT0_LNAMIXRFATT3_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_PNRFFILT0      */

/* Bit fields for AGC PNRFFILT1 */
#define _AGC_PNRFFILT1_RESETVALUE                      0x00801804UL                                /**< Default value for AGC_PNRFFILT1             */
#define _AGC_PNRFFILT1_MASK                            0x3FFFFFFFUL                                /**< Mask for AGC_PNRFFILT1                      */
#define _AGC_PNRFFILT1_LNAMIXRFATT4_SHIFT              0                                           /**< Shift value for AGC_LNAMIXRFATT4            */
#define _AGC_PNRFFILT1_LNAMIXRFATT4_MASK               0x3FFUL                                     /**< Bit mask for AGC_LNAMIXRFATT4               */
#define _AGC_PNRFFILT1_LNAMIXRFATT4_DEFAULT            0x00000004UL                                /**< Mode DEFAULT for AGC_PNRFFILT1              */
#define AGC_PNRFFILT1_LNAMIXRFATT4_DEFAULT             (_AGC_PNRFFILT1_LNAMIXRFATT4_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFFILT1      */
#define _AGC_PNRFFILT1_LNAMIXRFATT5_SHIFT              10                                          /**< Shift value for AGC_LNAMIXRFATT5            */
#define _AGC_PNRFFILT1_LNAMIXRFATT5_MASK               0xFFC00UL                                   /**< Bit mask for AGC_LNAMIXRFATT5               */
#define _AGC_PNRFFILT1_LNAMIXRFATT5_DEFAULT            0x00000006UL                                /**< Mode DEFAULT for AGC_PNRFFILT1              */
#define AGC_PNRFFILT1_LNAMIXRFATT5_DEFAULT             (_AGC_PNRFFILT1_LNAMIXRFATT5_DEFAULT << 10) /**< Shifted mode DEFAULT for AGC_PNRFFILT1      */
#define _AGC_PNRFFILT1_LNAMIXRFATT6_SHIFT              20                                          /**< Shift value for AGC_LNAMIXRFATT6            */
#define _AGC_PNRFFILT1_LNAMIXRFATT6_MASK               0x3FF00000UL                                /**< Bit mask for AGC_LNAMIXRFATT6               */
#define _AGC_PNRFFILT1_LNAMIXRFATT6_DEFAULT            0x00000008UL                                /**< Mode DEFAULT for AGC_PNRFFILT1              */
#define AGC_PNRFFILT1_LNAMIXRFATT6_DEFAULT             (_AGC_PNRFFILT1_LNAMIXRFATT6_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_PNRFFILT1      */

/* Bit fields for AGC PNRFFILT2 */
#define _AGC_PNRFFILT2_RESETVALUE                      0x01203C0BUL                                /**< Default value for AGC_PNRFFILT2             */
#define _AGC_PNRFFILT2_MASK                            0x3FFFFFFFUL                                /**< Mask for AGC_PNRFFILT2                      */
#define _AGC_PNRFFILT2_LNAMIXRFATT7_SHIFT              0                                           /**< Shift value for AGC_LNAMIXRFATT7            */
#define _AGC_PNRFFILT2_LNAMIXRFATT7_MASK               0x3FFUL                                     /**< Bit mask for AGC_LNAMIXRFATT7               */
#define _AGC_PNRFFILT2_LNAMIXRFATT7_DEFAULT            0x0000000BUL                                /**< Mode DEFAULT for AGC_PNRFFILT2              */
#define AGC_PNRFFILT2_LNAMIXRFATT7_DEFAULT             (_AGC_PNRFFILT2_LNAMIXRFATT7_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFFILT2      */
#define _AGC_PNRFFILT2_LNAMIXRFATT8_SHIFT              10                                          /**< Shift value for AGC_LNAMIXRFATT8            */
#define _AGC_PNRFFILT2_LNAMIXRFATT8_MASK               0xFFC00UL                                   /**< Bit mask for AGC_LNAMIXRFATT8               */
#define _AGC_PNRFFILT2_LNAMIXRFATT8_DEFAULT            0x0000000FUL                                /**< Mode DEFAULT for AGC_PNRFFILT2              */
#define AGC_PNRFFILT2_LNAMIXRFATT8_DEFAULT             (_AGC_PNRFFILT2_LNAMIXRFATT8_DEFAULT << 10) /**< Shifted mode DEFAULT for AGC_PNRFFILT2      */
#define _AGC_PNRFFILT2_LNAMIXRFATT9_SHIFT              20                                          /**< Shift value for AGC_LNAMIXRFATT9            */
#define _AGC_PNRFFILT2_LNAMIXRFATT9_MASK               0x3FF00000UL                                /**< Bit mask for AGC_LNAMIXRFATT9               */
#define _AGC_PNRFFILT2_LNAMIXRFATT9_DEFAULT            0x00000012UL                                /**< Mode DEFAULT for AGC_PNRFFILT2              */
#define AGC_PNRFFILT2_LNAMIXRFATT9_DEFAULT             (_AGC_PNRFFILT2_LNAMIXRFATT9_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_PNRFFILT2      */

/* Bit fields for AGC PNRFFILT3 */
#define _AGC_PNRFFILT3_RESETVALUE                      0x02107C18UL                                 /**< Default value for AGC_PNRFFILT3             */
#define _AGC_PNRFFILT3_MASK                            0x3FFFFFFFUL                                 /**< Mask for AGC_PNRFFILT3                      */
#define _AGC_PNRFFILT3_LNAMIXRFATT10_SHIFT             0                                            /**< Shift value for AGC_LNAMIXRFATT10           */
#define _AGC_PNRFFILT3_LNAMIXRFATT10_MASK              0x3FFUL                                      /**< Bit mask for AGC_LNAMIXRFATT10              */
#define _AGC_PNRFFILT3_LNAMIXRFATT10_DEFAULT           0x00000018UL                                 /**< Mode DEFAULT for AGC_PNRFFILT3              */
#define AGC_PNRFFILT3_LNAMIXRFATT10_DEFAULT            (_AGC_PNRFFILT3_LNAMIXRFATT10_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFFILT3      */
#define _AGC_PNRFFILT3_LNAMIXRFATT11_SHIFT             10                                           /**< Shift value for AGC_LNAMIXRFATT11           */
#define _AGC_PNRFFILT3_LNAMIXRFATT11_MASK              0xFFC00UL                                    /**< Bit mask for AGC_LNAMIXRFATT11              */
#define _AGC_PNRFFILT3_LNAMIXRFATT11_DEFAULT           0x0000001FUL                                 /**< Mode DEFAULT for AGC_PNRFFILT3              */
#define AGC_PNRFFILT3_LNAMIXRFATT11_DEFAULT            (_AGC_PNRFFILT3_LNAMIXRFATT11_DEFAULT << 10) /**< Shifted mode DEFAULT for AGC_PNRFFILT3      */
#define _AGC_PNRFFILT3_LNAMIXRFATT12_SHIFT             20                                           /**< Shift value for AGC_LNAMIXRFATT12           */
#define _AGC_PNRFFILT3_LNAMIXRFATT12_MASK              0x3FF00000UL                                 /**< Bit mask for AGC_LNAMIXRFATT12              */
#define _AGC_PNRFFILT3_LNAMIXRFATT12_DEFAULT           0x00000021UL                                 /**< Mode DEFAULT for AGC_PNRFFILT3              */
#define AGC_PNRFFILT3_LNAMIXRFATT12_DEFAULT            (_AGC_PNRFFILT3_LNAMIXRFATT12_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_PNRFFILT3      */

/* Bit fields for AGC PNRFFILT4 */
#define _AGC_PNRFFILT4_RESETVALUE                      0x06E0FC2FUL                                 /**< Default value for AGC_PNRFFILT4             */
#define _AGC_PNRFFILT4_MASK                            0x3FFFFFFFUL                                 /**< Mask for AGC_PNRFFILT4                      */
#define _AGC_PNRFFILT4_LNAMIXRFATT13_SHIFT             0                                            /**< Shift value for AGC_LNAMIXRFATT13           */
#define _AGC_PNRFFILT4_LNAMIXRFATT13_MASK              0x3FFUL                                      /**< Bit mask for AGC_LNAMIXRFATT13              */
#define _AGC_PNRFFILT4_LNAMIXRFATT13_DEFAULT           0x0000002FUL                                 /**< Mode DEFAULT for AGC_PNRFFILT4              */
#define AGC_PNRFFILT4_LNAMIXRFATT13_DEFAULT            (_AGC_PNRFFILT4_LNAMIXRFATT13_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFFILT4      */
#define _AGC_PNRFFILT4_LNAMIXRFATT14_SHIFT             10                                           /**< Shift value for AGC_LNAMIXRFATT14           */
#define _AGC_PNRFFILT4_LNAMIXRFATT14_MASK              0xFFC00UL                                    /**< Bit mask for AGC_LNAMIXRFATT14              */
#define _AGC_PNRFFILT4_LNAMIXRFATT14_DEFAULT           0x0000003FUL                                 /**< Mode DEFAULT for AGC_PNRFFILT4              */
#define AGC_PNRFFILT4_LNAMIXRFATT14_DEFAULT            (_AGC_PNRFFILT4_LNAMIXRFATT14_DEFAULT << 10) /**< Shifted mode DEFAULT for AGC_PNRFFILT4      */
#define _AGC_PNRFFILT4_LNAMIXRFATT15_SHIFT             20                                           /**< Shift value for AGC_LNAMIXRFATT15           */
#define _AGC_PNRFFILT4_LNAMIXRFATT15_MASK              0x3FF00000UL                                 /**< Bit mask for AGC_LNAMIXRFATT15              */
#define _AGC_PNRFFILT4_LNAMIXRFATT15_DEFAULT           0x0000006EUL                                 /**< Mode DEFAULT for AGC_PNRFFILT4              */
#define AGC_PNRFFILT4_LNAMIXRFATT15_DEFAULT            (_AGC_PNRFFILT4_LNAMIXRFATT15_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_PNRFFILT4      */

/* Bit fields for AGC PNRFFILT5 */
#define _AGC_PNRFFILT5_RESETVALUE                      0x0180480FUL                                 /**< Default value for AGC_PNRFFILT5             */
#define _AGC_PNRFFILT5_MASK                            0x3FFFFFFFUL                                 /**< Mask for AGC_PNRFFILT5                      */
#define _AGC_PNRFFILT5_LNAMIXRFATT16_SHIFT             0                                            /**< Shift value for AGC_LNAMIXRFATT16           */
#define _AGC_PNRFFILT5_LNAMIXRFATT16_MASK              0x3FFUL                                      /**< Bit mask for AGC_LNAMIXRFATT16              */
#define _AGC_PNRFFILT5_LNAMIXRFATT16_DEFAULT           0x0000000FUL                                 /**< Mode DEFAULT for AGC_PNRFFILT5              */
#define AGC_PNRFFILT5_LNAMIXRFATT16_DEFAULT            (_AGC_PNRFFILT5_LNAMIXRFATT16_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFFILT5      */
#define _AGC_PNRFFILT5_LNAMIXRFATT17_SHIFT             10                                           /**< Shift value for AGC_LNAMIXRFATT17           */
#define _AGC_PNRFFILT5_LNAMIXRFATT17_MASK              0xFFC00UL                                    /**< Bit mask for AGC_LNAMIXRFATT17              */
#define _AGC_PNRFFILT5_LNAMIXRFATT17_DEFAULT           0x00000012UL                                 /**< Mode DEFAULT for AGC_PNRFFILT5              */
#define AGC_PNRFFILT5_LNAMIXRFATT17_DEFAULT            (_AGC_PNRFFILT5_LNAMIXRFATT17_DEFAULT << 10) /**< Shifted mode DEFAULT for AGC_PNRFFILT5      */
#define _AGC_PNRFFILT5_LNAMIXRFATT18_SHIFT             20                                           /**< Shift value for AGC_LNAMIXRFATT18           */
#define _AGC_PNRFFILT5_LNAMIXRFATT18_MASK              0x3FF00000UL                                 /**< Bit mask for AGC_LNAMIXRFATT18              */
#define _AGC_PNRFFILT5_LNAMIXRFATT18_DEFAULT           0x00000018UL                                 /**< Mode DEFAULT for AGC_PNRFFILT5              */
#define AGC_PNRFFILT5_LNAMIXRFATT18_DEFAULT            (_AGC_PNRFFILT5_LNAMIXRFATT18_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_PNRFFILT5      */

/* Bit fields for AGC PNRFFILT6 */
#define _AGC_PNRFFILT6_RESETVALUE                      0x02F0841FUL                                 /**< Default value for AGC_PNRFFILT6             */
#define _AGC_PNRFFILT6_MASK                            0x3FFFFFFFUL                                 /**< Mask for AGC_PNRFFILT6                      */
#define _AGC_PNRFFILT6_LNAMIXRFATT19_SHIFT             0                                            /**< Shift value for AGC_LNAMIXRFATT19           */
#define _AGC_PNRFFILT6_LNAMIXRFATT19_MASK              0x3FFUL                                      /**< Bit mask for AGC_LNAMIXRFATT19              */
#define _AGC_PNRFFILT6_LNAMIXRFATT19_DEFAULT           0x0000001FUL                                 /**< Mode DEFAULT for AGC_PNRFFILT6              */
#define AGC_PNRFFILT6_LNAMIXRFATT19_DEFAULT            (_AGC_PNRFFILT6_LNAMIXRFATT19_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFFILT6      */
#define _AGC_PNRFFILT6_LNAMIXRFATT20_SHIFT             10                                           /**< Shift value for AGC_LNAMIXRFATT20           */
#define _AGC_PNRFFILT6_LNAMIXRFATT20_MASK              0xFFC00UL                                    /**< Bit mask for AGC_LNAMIXRFATT20              */
#define _AGC_PNRFFILT6_LNAMIXRFATT20_DEFAULT           0x00000021UL                                 /**< Mode DEFAULT for AGC_PNRFFILT6              */
#define AGC_PNRFFILT6_LNAMIXRFATT20_DEFAULT            (_AGC_PNRFFILT6_LNAMIXRFATT20_DEFAULT << 10) /**< Shifted mode DEFAULT for AGC_PNRFFILT6      */
#define _AGC_PNRFFILT6_LNAMIXRFATT21_SHIFT             20                                           /**< Shift value for AGC_LNAMIXRFATT21           */
#define _AGC_PNRFFILT6_LNAMIXRFATT21_MASK              0x3FF00000UL                                 /**< Bit mask for AGC_LNAMIXRFATT21              */
#define _AGC_PNRFFILT6_LNAMIXRFATT21_DEFAULT           0x0000002FUL                                 /**< Mode DEFAULT for AGC_PNRFFILT6              */
#define AGC_PNRFFILT6_LNAMIXRFATT21_DEFAULT            (_AGC_PNRFFILT6_LNAMIXRFATT21_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_PNRFFILT6      */

/* Bit fields for AGC PNRFFILT7 */
#define _AGC_PNRFFILT7_RESETVALUE                      0x07F1B83FUL                                 /**< Default value for AGC_PNRFFILT7             */
#define _AGC_PNRFFILT7_MASK                            0x3FFFFFFFUL                                 /**< Mask for AGC_PNRFFILT7                      */
#define _AGC_PNRFFILT7_LNAMIXRFATT22_SHIFT             0                                            /**< Shift value for AGC_LNAMIXRFATT22           */
#define _AGC_PNRFFILT7_LNAMIXRFATT22_MASK              0x3FFUL                                      /**< Bit mask for AGC_LNAMIXRFATT22              */
#define _AGC_PNRFFILT7_LNAMIXRFATT22_DEFAULT           0x0000003FUL                                 /**< Mode DEFAULT for AGC_PNRFFILT7              */
#define AGC_PNRFFILT7_LNAMIXRFATT22_DEFAULT            (_AGC_PNRFFILT7_LNAMIXRFATT22_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_PNRFFILT7      */
#define _AGC_PNRFFILT7_LNAMIXRFATT23_SHIFT             10                                           /**< Shift value for AGC_LNAMIXRFATT23           */
#define _AGC_PNRFFILT7_LNAMIXRFATT23_MASK              0xFFC00UL                                    /**< Bit mask for AGC_LNAMIXRFATT23              */
#define _AGC_PNRFFILT7_LNAMIXRFATT23_DEFAULT           0x0000006EUL                                 /**< Mode DEFAULT for AGC_PNRFFILT7              */
#define AGC_PNRFFILT7_LNAMIXRFATT23_DEFAULT            (_AGC_PNRFFILT7_LNAMIXRFATT23_DEFAULT << 10) /**< Shifted mode DEFAULT for AGC_PNRFFILT7      */
#define _AGC_PNRFFILT7_LNAMIXRFATT24_SHIFT             20                                           /**< Shift value for AGC_LNAMIXRFATT24           */
#define _AGC_PNRFFILT7_LNAMIXRFATT24_MASK              0x3FF00000UL                                 /**< Bit mask for AGC_LNAMIXRFATT24              */
#define _AGC_PNRFFILT7_LNAMIXRFATT24_DEFAULT           0x0000007FUL                                 /**< Mode DEFAULT for AGC_PNRFFILT7              */
#define AGC_PNRFFILT7_LNAMIXRFATT24_DEFAULT            (_AGC_PNRFFILT7_LNAMIXRFATT24_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_PNRFFILT7      */

/* Bit fields for AGC FENOTCHATT0 */
#define _AGC_FENOTCHATT0_RESETVALUE                    0x00000000UL                                     /**< Default value for AGC_FENOTCHATT0           */
#define _AGC_FENOTCHATT0_MASK                          0x3FFF3FFFUL                                     /**< Mask for AGC_FENOTCHATT0                    */
#define _AGC_FENOTCHATT0_FENOTCHATTNSEL1_SHIFT         0                                                /**< Shift value for AGC_FENOTCHATTNSEL1         */
#define _AGC_FENOTCHATT0_FENOTCHATTNSEL1_MASK          0xFUL                                            /**< Bit mask for AGC_FENOTCHATTNSEL1            */
#define _AGC_FENOTCHATT0_FENOTCHATTNSEL1_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT0            */
#define AGC_FENOTCHATT0_FENOTCHATTNSEL1_DEFAULT        (_AGC_FENOTCHATT0_FENOTCHATTNSEL1_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT0    */
#define _AGC_FENOTCHATT0_FENOTCHCAPCRSE1_SHIFT         4                                                /**< Shift value for AGC_FENOTCHCAPCRSE1         */
#define _AGC_FENOTCHATT0_FENOTCHCAPCRSE1_MASK          0xF0UL                                           /**< Bit mask for AGC_FENOTCHCAPCRSE1            */
#define _AGC_FENOTCHATT0_FENOTCHCAPCRSE1_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT0            */
#define AGC_FENOTCHATT0_FENOTCHCAPCRSE1_DEFAULT        (_AGC_FENOTCHATT0_FENOTCHCAPCRSE1_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT0    */
#define _AGC_FENOTCHATT0_FENOTCHCAPFINE1_SHIFT         8                                                /**< Shift value for AGC_FENOTCHCAPFINE1         */
#define _AGC_FENOTCHATT0_FENOTCHCAPFINE1_MASK          0xF00UL                                          /**< Bit mask for AGC_FENOTCHCAPFINE1            */
#define _AGC_FENOTCHATT0_FENOTCHCAPFINE1_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT0            */
#define AGC_FENOTCHATT0_FENOTCHCAPFINE1_DEFAULT        (_AGC_FENOTCHATT0_FENOTCHCAPFINE1_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT0    */
#define AGC_FENOTCHATT0_FENOTCHRATTNEN1                (0x1UL << 12)                                    /**< FE notch rattn enable for index 1           */
#define _AGC_FENOTCHATT0_FENOTCHRATTNEN1_SHIFT         12                                               /**< Shift value for AGC_FENOTCHRATTNEN1         */
#define _AGC_FENOTCHATT0_FENOTCHRATTNEN1_MASK          0x1000UL                                         /**< Bit mask for AGC_FENOTCHRATTNEN1            */
#define _AGC_FENOTCHATT0_FENOTCHRATTNEN1_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT0            */
#define AGC_FENOTCHATT0_FENOTCHRATTNEN1_DEFAULT        (_AGC_FENOTCHATT0_FENOTCHRATTNEN1_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHATT0    */
#define AGC_FENOTCHATT0_FENOTCHEN1                     (0x1UL << 13)                                    /**< FE notch enable for index 1                 */
#define _AGC_FENOTCHATT0_FENOTCHEN1_SHIFT              13                                               /**< Shift value for AGC_FENOTCHEN1              */
#define _AGC_FENOTCHATT0_FENOTCHEN1_MASK               0x2000UL                                         /**< Bit mask for AGC_FENOTCHEN1                 */
#define _AGC_FENOTCHATT0_FENOTCHEN1_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT0            */
#define AGC_FENOTCHATT0_FENOTCHEN1_DEFAULT             (_AGC_FENOTCHATT0_FENOTCHEN1_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT0    */
#define _AGC_FENOTCHATT0_FENOTCHATTNSEL2_SHIFT         16                                               /**< Shift value for AGC_FENOTCHATTNSEL2         */
#define _AGC_FENOTCHATT0_FENOTCHATTNSEL2_MASK          0xF0000UL                                        /**< Bit mask for AGC_FENOTCHATTNSEL2            */
#define _AGC_FENOTCHATT0_FENOTCHATTNSEL2_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT0            */
#define AGC_FENOTCHATT0_FENOTCHATTNSEL2_DEFAULT        (_AGC_FENOTCHATT0_FENOTCHATTNSEL2_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHATT0    */
#define _AGC_FENOTCHATT0_FENOTCHCAPCRSE2_SHIFT         20                                               /**< Shift value for AGC_FENOTCHCAPCRSE2         */
#define _AGC_FENOTCHATT0_FENOTCHCAPCRSE2_MASK          0xF00000UL                                       /**< Bit mask for AGC_FENOTCHCAPCRSE2            */
#define _AGC_FENOTCHATT0_FENOTCHCAPCRSE2_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT0            */
#define AGC_FENOTCHATT0_FENOTCHCAPCRSE2_DEFAULT        (_AGC_FENOTCHATT0_FENOTCHCAPCRSE2_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHATT0    */
#define _AGC_FENOTCHATT0_FENOTCHCAPFINE2_SHIFT         24                                               /**< Shift value for AGC_FENOTCHCAPFINE2         */
#define _AGC_FENOTCHATT0_FENOTCHCAPFINE2_MASK          0xF000000UL                                      /**< Bit mask for AGC_FENOTCHCAPFINE2            */
#define _AGC_FENOTCHATT0_FENOTCHCAPFINE2_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT0            */
#define AGC_FENOTCHATT0_FENOTCHCAPFINE2_DEFAULT        (_AGC_FENOTCHATT0_FENOTCHCAPFINE2_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHATT0    */
#define AGC_FENOTCHATT0_FENOTCHRATTNEN2                (0x1UL << 28)                                    /**< FE notch rattn enable for index 2           */
#define _AGC_FENOTCHATT0_FENOTCHRATTNEN2_SHIFT         28                                               /**< Shift value for AGC_FENOTCHRATTNEN2         */
#define _AGC_FENOTCHATT0_FENOTCHRATTNEN2_MASK          0x10000000UL                                     /**< Bit mask for AGC_FENOTCHRATTNEN2            */
#define _AGC_FENOTCHATT0_FENOTCHRATTNEN2_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT0            */
#define AGC_FENOTCHATT0_FENOTCHRATTNEN2_DEFAULT        (_AGC_FENOTCHATT0_FENOTCHRATTNEN2_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHATT0    */
#define AGC_FENOTCHATT0_FENOTCHEN2                     (0x1UL << 29)                                    /**< FE notch enable for index 2                 */
#define _AGC_FENOTCHATT0_FENOTCHEN2_SHIFT              29                                               /**< Shift value for AGC_FENOTCHEN2              */
#define _AGC_FENOTCHATT0_FENOTCHEN2_MASK               0x20000000UL                                     /**< Bit mask for AGC_FENOTCHEN2                 */
#define _AGC_FENOTCHATT0_FENOTCHEN2_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT0            */
#define AGC_FENOTCHATT0_FENOTCHEN2_DEFAULT             (_AGC_FENOTCHATT0_FENOTCHEN2_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT0    */

/* Bit fields for AGC FENOTCHATT1 */
#define _AGC_FENOTCHATT1_RESETVALUE                    0x00000000UL                                     /**< Default value for AGC_FENOTCHATT1           */
#define _AGC_FENOTCHATT1_MASK                          0x3FFF3FFFUL                                     /**< Mask for AGC_FENOTCHATT1                    */
#define _AGC_FENOTCHATT1_FENOTCHATTNSEL3_SHIFT         0                                                /**< Shift value for AGC_FENOTCHATTNSEL3         */
#define _AGC_FENOTCHATT1_FENOTCHATTNSEL3_MASK          0xFUL                                            /**< Bit mask for AGC_FENOTCHATTNSEL3            */
#define _AGC_FENOTCHATT1_FENOTCHATTNSEL3_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT1            */
#define AGC_FENOTCHATT1_FENOTCHATTNSEL3_DEFAULT        (_AGC_FENOTCHATT1_FENOTCHATTNSEL3_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT1    */
#define _AGC_FENOTCHATT1_FENOTCHCAPCRSE3_SHIFT         4                                                /**< Shift value for AGC_FENOTCHCAPCRSE3         */
#define _AGC_FENOTCHATT1_FENOTCHCAPCRSE3_MASK          0xF0UL                                           /**< Bit mask for AGC_FENOTCHCAPCRSE3            */
#define _AGC_FENOTCHATT1_FENOTCHCAPCRSE3_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT1            */
#define AGC_FENOTCHATT1_FENOTCHCAPCRSE3_DEFAULT        (_AGC_FENOTCHATT1_FENOTCHCAPCRSE3_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT1    */
#define _AGC_FENOTCHATT1_FENOTCHCAPFINE3_SHIFT         8                                                /**< Shift value for AGC_FENOTCHCAPFINE3         */
#define _AGC_FENOTCHATT1_FENOTCHCAPFINE3_MASK          0xF00UL                                          /**< Bit mask for AGC_FENOTCHCAPFINE3            */
#define _AGC_FENOTCHATT1_FENOTCHCAPFINE3_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT1            */
#define AGC_FENOTCHATT1_FENOTCHCAPFINE3_DEFAULT        (_AGC_FENOTCHATT1_FENOTCHCAPFINE3_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT1    */
#define AGC_FENOTCHATT1_FENOTCHRATTNEN3                (0x1UL << 12)                                    /**< FE notch rattn enable for index 3           */
#define _AGC_FENOTCHATT1_FENOTCHRATTNEN3_SHIFT         12                                               /**< Shift value for AGC_FENOTCHRATTNEN3         */
#define _AGC_FENOTCHATT1_FENOTCHRATTNEN3_MASK          0x1000UL                                         /**< Bit mask for AGC_FENOTCHRATTNEN3            */
#define _AGC_FENOTCHATT1_FENOTCHRATTNEN3_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT1            */
#define AGC_FENOTCHATT1_FENOTCHRATTNEN3_DEFAULT        (_AGC_FENOTCHATT1_FENOTCHRATTNEN3_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHATT1    */
#define AGC_FENOTCHATT1_FENOTCHEN3                     (0x1UL << 13)                                    /**< FE notch enable for index 3                 */
#define _AGC_FENOTCHATT1_FENOTCHEN3_SHIFT              13                                               /**< Shift value for AGC_FENOTCHEN3              */
#define _AGC_FENOTCHATT1_FENOTCHEN3_MASK               0x2000UL                                         /**< Bit mask for AGC_FENOTCHEN3                 */
#define _AGC_FENOTCHATT1_FENOTCHEN3_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT1            */
#define AGC_FENOTCHATT1_FENOTCHEN3_DEFAULT             (_AGC_FENOTCHATT1_FENOTCHEN3_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT1    */
#define _AGC_FENOTCHATT1_FENOTCHATTNSEL4_SHIFT         16                                               /**< Shift value for AGC_FENOTCHATTNSEL4         */
#define _AGC_FENOTCHATT1_FENOTCHATTNSEL4_MASK          0xF0000UL                                        /**< Bit mask for AGC_FENOTCHATTNSEL4            */
#define _AGC_FENOTCHATT1_FENOTCHATTNSEL4_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT1            */
#define AGC_FENOTCHATT1_FENOTCHATTNSEL4_DEFAULT        (_AGC_FENOTCHATT1_FENOTCHATTNSEL4_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHATT1    */
#define _AGC_FENOTCHATT1_FENOTCHCAPCRSE4_SHIFT         20                                               /**< Shift value for AGC_FENOTCHCAPCRSE4         */
#define _AGC_FENOTCHATT1_FENOTCHCAPCRSE4_MASK          0xF00000UL                                       /**< Bit mask for AGC_FENOTCHCAPCRSE4            */
#define _AGC_FENOTCHATT1_FENOTCHCAPCRSE4_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT1            */
#define AGC_FENOTCHATT1_FENOTCHCAPCRSE4_DEFAULT        (_AGC_FENOTCHATT1_FENOTCHCAPCRSE4_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHATT1    */
#define _AGC_FENOTCHATT1_FENOTCHCAPFINE4_SHIFT         24                                               /**< Shift value for AGC_FENOTCHCAPFINE4         */
#define _AGC_FENOTCHATT1_FENOTCHCAPFINE4_MASK          0xF000000UL                                      /**< Bit mask for AGC_FENOTCHCAPFINE4            */
#define _AGC_FENOTCHATT1_FENOTCHCAPFINE4_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT1            */
#define AGC_FENOTCHATT1_FENOTCHCAPFINE4_DEFAULT        (_AGC_FENOTCHATT1_FENOTCHCAPFINE4_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHATT1    */
#define AGC_FENOTCHATT1_FENOTCHRATTNEN4                (0x1UL << 28)                                    /**< FE notch rattn enable for index 4           */
#define _AGC_FENOTCHATT1_FENOTCHRATTNEN4_SHIFT         28                                               /**< Shift value for AGC_FENOTCHRATTNEN4         */
#define _AGC_FENOTCHATT1_FENOTCHRATTNEN4_MASK          0x10000000UL                                     /**< Bit mask for AGC_FENOTCHRATTNEN4            */
#define _AGC_FENOTCHATT1_FENOTCHRATTNEN4_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT1            */
#define AGC_FENOTCHATT1_FENOTCHRATTNEN4_DEFAULT        (_AGC_FENOTCHATT1_FENOTCHRATTNEN4_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHATT1    */
#define AGC_FENOTCHATT1_FENOTCHEN4                     (0x1UL << 29)                                    /**< FE notch enable for index 4                 */
#define _AGC_FENOTCHATT1_FENOTCHEN4_SHIFT              29                                               /**< Shift value for AGC_FENOTCHEN4              */
#define _AGC_FENOTCHATT1_FENOTCHEN4_MASK               0x20000000UL                                     /**< Bit mask for AGC_FENOTCHEN4                 */
#define _AGC_FENOTCHATT1_FENOTCHEN4_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT1            */
#define AGC_FENOTCHATT1_FENOTCHEN4_DEFAULT             (_AGC_FENOTCHATT1_FENOTCHEN4_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT1    */

/* Bit fields for AGC FENOTCHATT2 */
#define _AGC_FENOTCHATT2_RESETVALUE                    0x00000000UL                                     /**< Default value for AGC_FENOTCHATT2           */
#define _AGC_FENOTCHATT2_MASK                          0x3FFF3FFFUL                                     /**< Mask for AGC_FENOTCHATT2                    */
#define _AGC_FENOTCHATT2_FENOTCHATTNSEL5_SHIFT         0                                                /**< Shift value for AGC_FENOTCHATTNSEL5         */
#define _AGC_FENOTCHATT2_FENOTCHATTNSEL5_MASK          0xFUL                                            /**< Bit mask for AGC_FENOTCHATTNSEL5            */
#define _AGC_FENOTCHATT2_FENOTCHATTNSEL5_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT2            */
#define AGC_FENOTCHATT2_FENOTCHATTNSEL5_DEFAULT        (_AGC_FENOTCHATT2_FENOTCHATTNSEL5_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT2    */
#define _AGC_FENOTCHATT2_FENOTCHCAPCRSE5_SHIFT         4                                                /**< Shift value for AGC_FENOTCHCAPCRSE5         */
#define _AGC_FENOTCHATT2_FENOTCHCAPCRSE5_MASK          0xF0UL                                           /**< Bit mask for AGC_FENOTCHCAPCRSE5            */
#define _AGC_FENOTCHATT2_FENOTCHCAPCRSE5_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT2            */
#define AGC_FENOTCHATT2_FENOTCHCAPCRSE5_DEFAULT        (_AGC_FENOTCHATT2_FENOTCHCAPCRSE5_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT2    */
#define _AGC_FENOTCHATT2_FENOTCHCAPFINE5_SHIFT         8                                                /**< Shift value for AGC_FENOTCHCAPFINE5         */
#define _AGC_FENOTCHATT2_FENOTCHCAPFINE5_MASK          0xF00UL                                          /**< Bit mask for AGC_FENOTCHCAPFINE5            */
#define _AGC_FENOTCHATT2_FENOTCHCAPFINE5_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT2            */
#define AGC_FENOTCHATT2_FENOTCHCAPFINE5_DEFAULT        (_AGC_FENOTCHATT2_FENOTCHCAPFINE5_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT2    */
#define AGC_FENOTCHATT2_FENOTCHRATTNEN5                (0x1UL << 12)                                    /**< FE notch rattn enable for index 5           */
#define _AGC_FENOTCHATT2_FENOTCHRATTNEN5_SHIFT         12                                               /**< Shift value for AGC_FENOTCHRATTNEN5         */
#define _AGC_FENOTCHATT2_FENOTCHRATTNEN5_MASK          0x1000UL                                         /**< Bit mask for AGC_FENOTCHRATTNEN5            */
#define _AGC_FENOTCHATT2_FENOTCHRATTNEN5_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT2            */
#define AGC_FENOTCHATT2_FENOTCHRATTNEN5_DEFAULT        (_AGC_FENOTCHATT2_FENOTCHRATTNEN5_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHATT2    */
#define AGC_FENOTCHATT2_FENOTCHEN5                     (0x1UL << 13)                                    /**< FE notch enable for index 5                 */
#define _AGC_FENOTCHATT2_FENOTCHEN5_SHIFT              13                                               /**< Shift value for AGC_FENOTCHEN5              */
#define _AGC_FENOTCHATT2_FENOTCHEN5_MASK               0x2000UL                                         /**< Bit mask for AGC_FENOTCHEN5                 */
#define _AGC_FENOTCHATT2_FENOTCHEN5_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT2            */
#define AGC_FENOTCHATT2_FENOTCHEN5_DEFAULT             (_AGC_FENOTCHATT2_FENOTCHEN5_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT2    */
#define _AGC_FENOTCHATT2_FENOTCHATTNSEL6_SHIFT         16                                               /**< Shift value for AGC_FENOTCHATTNSEL6         */
#define _AGC_FENOTCHATT2_FENOTCHATTNSEL6_MASK          0xF0000UL                                        /**< Bit mask for AGC_FENOTCHATTNSEL6            */
#define _AGC_FENOTCHATT2_FENOTCHATTNSEL6_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT2            */
#define AGC_FENOTCHATT2_FENOTCHATTNSEL6_DEFAULT        (_AGC_FENOTCHATT2_FENOTCHATTNSEL6_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHATT2    */
#define _AGC_FENOTCHATT2_FENOTCHCAPCRSE6_SHIFT         20                                               /**< Shift value for AGC_FENOTCHCAPCRSE6         */
#define _AGC_FENOTCHATT2_FENOTCHCAPCRSE6_MASK          0xF00000UL                                       /**< Bit mask for AGC_FENOTCHCAPCRSE6            */
#define _AGC_FENOTCHATT2_FENOTCHCAPCRSE6_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT2            */
#define AGC_FENOTCHATT2_FENOTCHCAPCRSE6_DEFAULT        (_AGC_FENOTCHATT2_FENOTCHCAPCRSE6_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHATT2    */
#define _AGC_FENOTCHATT2_FENOTCHCAPFINE6_SHIFT         24                                               /**< Shift value for AGC_FENOTCHCAPFINE6         */
#define _AGC_FENOTCHATT2_FENOTCHCAPFINE6_MASK          0xF000000UL                                      /**< Bit mask for AGC_FENOTCHCAPFINE6            */
#define _AGC_FENOTCHATT2_FENOTCHCAPFINE6_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT2            */
#define AGC_FENOTCHATT2_FENOTCHCAPFINE6_DEFAULT        (_AGC_FENOTCHATT2_FENOTCHCAPFINE6_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHATT2    */
#define AGC_FENOTCHATT2_FENOTCHRATTNEN6                (0x1UL << 28)                                    /**< FE notch rattn enable for index 6           */
#define _AGC_FENOTCHATT2_FENOTCHRATTNEN6_SHIFT         28                                               /**< Shift value for AGC_FENOTCHRATTNEN6         */
#define _AGC_FENOTCHATT2_FENOTCHRATTNEN6_MASK          0x10000000UL                                     /**< Bit mask for AGC_FENOTCHRATTNEN6            */
#define _AGC_FENOTCHATT2_FENOTCHRATTNEN6_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT2            */
#define AGC_FENOTCHATT2_FENOTCHRATTNEN6_DEFAULT        (_AGC_FENOTCHATT2_FENOTCHRATTNEN6_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHATT2    */
#define AGC_FENOTCHATT2_FENOTCHEN6                     (0x1UL << 29)                                    /**< FE notch enable for index 6                 */
#define _AGC_FENOTCHATT2_FENOTCHEN6_SHIFT              29                                               /**< Shift value for AGC_FENOTCHEN6              */
#define _AGC_FENOTCHATT2_FENOTCHEN6_MASK               0x20000000UL                                     /**< Bit mask for AGC_FENOTCHEN6                 */
#define _AGC_FENOTCHATT2_FENOTCHEN6_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT2            */
#define AGC_FENOTCHATT2_FENOTCHEN6_DEFAULT             (_AGC_FENOTCHATT2_FENOTCHEN6_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT2    */

/* Bit fields for AGC FENOTCHATT3 */
#define _AGC_FENOTCHATT3_RESETVALUE                    0x00000000UL                                     /**< Default value for AGC_FENOTCHATT3           */
#define _AGC_FENOTCHATT3_MASK                          0x3FFF3FFFUL                                     /**< Mask for AGC_FENOTCHATT3                    */
#define _AGC_FENOTCHATT3_FENOTCHATTNSEL7_SHIFT         0                                                /**< Shift value for AGC_FENOTCHATTNSEL7         */
#define _AGC_FENOTCHATT3_FENOTCHATTNSEL7_MASK          0xFUL                                            /**< Bit mask for AGC_FENOTCHATTNSEL7            */
#define _AGC_FENOTCHATT3_FENOTCHATTNSEL7_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT3            */
#define AGC_FENOTCHATT3_FENOTCHATTNSEL7_DEFAULT        (_AGC_FENOTCHATT3_FENOTCHATTNSEL7_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT3    */
#define _AGC_FENOTCHATT3_FENOTCHCAPCRSE7_SHIFT         4                                                /**< Shift value for AGC_FENOTCHCAPCRSE7         */
#define _AGC_FENOTCHATT3_FENOTCHCAPCRSE7_MASK          0xF0UL                                           /**< Bit mask for AGC_FENOTCHCAPCRSE7            */
#define _AGC_FENOTCHATT3_FENOTCHCAPCRSE7_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT3            */
#define AGC_FENOTCHATT3_FENOTCHCAPCRSE7_DEFAULT        (_AGC_FENOTCHATT3_FENOTCHCAPCRSE7_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT3    */
#define _AGC_FENOTCHATT3_FENOTCHCAPFINE7_SHIFT         8                                                /**< Shift value for AGC_FENOTCHCAPFINE7         */
#define _AGC_FENOTCHATT3_FENOTCHCAPFINE7_MASK          0xF00UL                                          /**< Bit mask for AGC_FENOTCHCAPFINE7            */
#define _AGC_FENOTCHATT3_FENOTCHCAPFINE7_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT3            */
#define AGC_FENOTCHATT3_FENOTCHCAPFINE7_DEFAULT        (_AGC_FENOTCHATT3_FENOTCHCAPFINE7_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT3    */
#define AGC_FENOTCHATT3_FENOTCHRATTNEN7                (0x1UL << 12)                                    /**< FE notch rattn enable for index 7           */
#define _AGC_FENOTCHATT3_FENOTCHRATTNEN7_SHIFT         12                                               /**< Shift value for AGC_FENOTCHRATTNEN7         */
#define _AGC_FENOTCHATT3_FENOTCHRATTNEN7_MASK          0x1000UL                                         /**< Bit mask for AGC_FENOTCHRATTNEN7            */
#define _AGC_FENOTCHATT3_FENOTCHRATTNEN7_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT3            */
#define AGC_FENOTCHATT3_FENOTCHRATTNEN7_DEFAULT        (_AGC_FENOTCHATT3_FENOTCHRATTNEN7_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHATT3    */
#define AGC_FENOTCHATT3_FENOTCHEN7                     (0x1UL << 13)                                    /**< FE notch enable for index 7                 */
#define _AGC_FENOTCHATT3_FENOTCHEN7_SHIFT              13                                               /**< Shift value for AGC_FENOTCHEN7              */
#define _AGC_FENOTCHATT3_FENOTCHEN7_MASK               0x2000UL                                         /**< Bit mask for AGC_FENOTCHEN7                 */
#define _AGC_FENOTCHATT3_FENOTCHEN7_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT3            */
#define AGC_FENOTCHATT3_FENOTCHEN7_DEFAULT             (_AGC_FENOTCHATT3_FENOTCHEN7_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT3    */
#define _AGC_FENOTCHATT3_FENOTCHATTNSEL8_SHIFT         16                                               /**< Shift value for AGC_FENOTCHATTNSEL8         */
#define _AGC_FENOTCHATT3_FENOTCHATTNSEL8_MASK          0xF0000UL                                        /**< Bit mask for AGC_FENOTCHATTNSEL8            */
#define _AGC_FENOTCHATT3_FENOTCHATTNSEL8_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT3            */
#define AGC_FENOTCHATT3_FENOTCHATTNSEL8_DEFAULT        (_AGC_FENOTCHATT3_FENOTCHATTNSEL8_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHATT3    */
#define _AGC_FENOTCHATT3_FENOTCHCAPCRSE8_SHIFT         20                                               /**< Shift value for AGC_FENOTCHCAPCRSE8         */
#define _AGC_FENOTCHATT3_FENOTCHCAPCRSE8_MASK          0xF00000UL                                       /**< Bit mask for AGC_FENOTCHCAPCRSE8            */
#define _AGC_FENOTCHATT3_FENOTCHCAPCRSE8_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT3            */
#define AGC_FENOTCHATT3_FENOTCHCAPCRSE8_DEFAULT        (_AGC_FENOTCHATT3_FENOTCHCAPCRSE8_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHATT3    */
#define _AGC_FENOTCHATT3_FENOTCHCAPFINE8_SHIFT         24                                               /**< Shift value for AGC_FENOTCHCAPFINE8         */
#define _AGC_FENOTCHATT3_FENOTCHCAPFINE8_MASK          0xF000000UL                                      /**< Bit mask for AGC_FENOTCHCAPFINE8            */
#define _AGC_FENOTCHATT3_FENOTCHCAPFINE8_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT3            */
#define AGC_FENOTCHATT3_FENOTCHCAPFINE8_DEFAULT        (_AGC_FENOTCHATT3_FENOTCHCAPFINE8_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHATT3    */
#define AGC_FENOTCHATT3_FENOTCHRATTNEN8                (0x1UL << 28)                                    /**< FE notch rattn enable for index 8           */
#define _AGC_FENOTCHATT3_FENOTCHRATTNEN8_SHIFT         28                                               /**< Shift value for AGC_FENOTCHRATTNEN8         */
#define _AGC_FENOTCHATT3_FENOTCHRATTNEN8_MASK          0x10000000UL                                     /**< Bit mask for AGC_FENOTCHRATTNEN8            */
#define _AGC_FENOTCHATT3_FENOTCHRATTNEN8_DEFAULT       0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT3            */
#define AGC_FENOTCHATT3_FENOTCHRATTNEN8_DEFAULT        (_AGC_FENOTCHATT3_FENOTCHRATTNEN8_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHATT3    */
#define AGC_FENOTCHATT3_FENOTCHEN8                     (0x1UL << 29)                                    /**< FE notch enable for index 8                 */
#define _AGC_FENOTCHATT3_FENOTCHEN8_SHIFT              29                                               /**< Shift value for AGC_FENOTCHEN8              */
#define _AGC_FENOTCHATT3_FENOTCHEN8_MASK               0x20000000UL                                     /**< Bit mask for AGC_FENOTCHEN8                 */
#define _AGC_FENOTCHATT3_FENOTCHEN8_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for AGC_FENOTCHATT3            */
#define AGC_FENOTCHATT3_FENOTCHEN8_DEFAULT             (_AGC_FENOTCHATT3_FENOTCHEN8_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT3    */

/* Bit fields for AGC FENOTCHATT4 */
#define _AGC_FENOTCHATT4_RESETVALUE                    0x00000000UL                                      /**< Default value for AGC_FENOTCHATT4           */
#define _AGC_FENOTCHATT4_MASK                          0x3FFF3FFFUL                                      /**< Mask for AGC_FENOTCHATT4                    */
#define _AGC_FENOTCHATT4_FENOTCHATTNSEL9_SHIFT         0                                                 /**< Shift value for AGC_FENOTCHATTNSEL9         */
#define _AGC_FENOTCHATT4_FENOTCHATTNSEL9_MASK          0xFUL                                             /**< Bit mask for AGC_FENOTCHATTNSEL9            */
#define _AGC_FENOTCHATT4_FENOTCHATTNSEL9_DEFAULT       0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT4            */
#define AGC_FENOTCHATT4_FENOTCHATTNSEL9_DEFAULT        (_AGC_FENOTCHATT4_FENOTCHATTNSEL9_DEFAULT << 0)   /**< Shifted mode DEFAULT for AGC_FENOTCHATT4    */
#define _AGC_FENOTCHATT4_FENOTCHCAPCRSE9_SHIFT         4                                                 /**< Shift value for AGC_FENOTCHCAPCRSE9         */
#define _AGC_FENOTCHATT4_FENOTCHCAPCRSE9_MASK          0xF0UL                                            /**< Bit mask for AGC_FENOTCHCAPCRSE9            */
#define _AGC_FENOTCHATT4_FENOTCHCAPCRSE9_DEFAULT       0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT4            */
#define AGC_FENOTCHATT4_FENOTCHCAPCRSE9_DEFAULT        (_AGC_FENOTCHATT4_FENOTCHCAPCRSE9_DEFAULT << 4)   /**< Shifted mode DEFAULT for AGC_FENOTCHATT4    */
#define _AGC_FENOTCHATT4_FENOTCHCAPFINE9_SHIFT         8                                                 /**< Shift value for AGC_FENOTCHCAPFINE9         */
#define _AGC_FENOTCHATT4_FENOTCHCAPFINE9_MASK          0xF00UL                                           /**< Bit mask for AGC_FENOTCHCAPFINE9            */
#define _AGC_FENOTCHATT4_FENOTCHCAPFINE9_DEFAULT       0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT4            */
#define AGC_FENOTCHATT4_FENOTCHCAPFINE9_DEFAULT        (_AGC_FENOTCHATT4_FENOTCHCAPFINE9_DEFAULT << 8)   /**< Shifted mode DEFAULT for AGC_FENOTCHATT4    */
#define AGC_FENOTCHATT4_FENOTCHRATTNEN9                (0x1UL << 12)                                     /**< FE notch rattn enable for index 9           */
#define _AGC_FENOTCHATT4_FENOTCHRATTNEN9_SHIFT         12                                                /**< Shift value for AGC_FENOTCHRATTNEN9         */
#define _AGC_FENOTCHATT4_FENOTCHRATTNEN9_MASK          0x1000UL                                          /**< Bit mask for AGC_FENOTCHRATTNEN9            */
#define _AGC_FENOTCHATT4_FENOTCHRATTNEN9_DEFAULT       0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT4            */
#define AGC_FENOTCHATT4_FENOTCHRATTNEN9_DEFAULT        (_AGC_FENOTCHATT4_FENOTCHRATTNEN9_DEFAULT << 12)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT4    */
#define AGC_FENOTCHATT4_FENOTCHEN9                     (0x1UL << 13)                                     /**< FE notch enable for index 9                 */
#define _AGC_FENOTCHATT4_FENOTCHEN9_SHIFT              13                                                /**< Shift value for AGC_FENOTCHEN9              */
#define _AGC_FENOTCHATT4_FENOTCHEN9_MASK               0x2000UL                                          /**< Bit mask for AGC_FENOTCHEN9                 */
#define _AGC_FENOTCHATT4_FENOTCHEN9_DEFAULT            0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT4            */
#define AGC_FENOTCHATT4_FENOTCHEN9_DEFAULT             (_AGC_FENOTCHATT4_FENOTCHEN9_DEFAULT << 13)       /**< Shifted mode DEFAULT for AGC_FENOTCHATT4    */
#define _AGC_FENOTCHATT4_FENOTCHATTNSEL10_SHIFT        16                                                /**< Shift value for AGC_FENOTCHATTNSEL10        */
#define _AGC_FENOTCHATT4_FENOTCHATTNSEL10_MASK         0xF0000UL                                         /**< Bit mask for AGC_FENOTCHATTNSEL10           */
#define _AGC_FENOTCHATT4_FENOTCHATTNSEL10_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT4            */
#define AGC_FENOTCHATT4_FENOTCHATTNSEL10_DEFAULT       (_AGC_FENOTCHATT4_FENOTCHATTNSEL10_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHATT4    */
#define _AGC_FENOTCHATT4_FENOTCHCAPCRSE10_SHIFT        20                                                /**< Shift value for AGC_FENOTCHCAPCRSE10        */
#define _AGC_FENOTCHATT4_FENOTCHCAPCRSE10_MASK         0xF00000UL                                        /**< Bit mask for AGC_FENOTCHCAPCRSE10           */
#define _AGC_FENOTCHATT4_FENOTCHCAPCRSE10_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT4            */
#define AGC_FENOTCHATT4_FENOTCHCAPCRSE10_DEFAULT       (_AGC_FENOTCHATT4_FENOTCHCAPCRSE10_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHATT4    */
#define _AGC_FENOTCHATT4_FENOTCHCAPFINE10_SHIFT        24                                                /**< Shift value for AGC_FENOTCHCAPFINE10        */
#define _AGC_FENOTCHATT4_FENOTCHCAPFINE10_MASK         0xF000000UL                                       /**< Bit mask for AGC_FENOTCHCAPFINE10           */
#define _AGC_FENOTCHATT4_FENOTCHCAPFINE10_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT4            */
#define AGC_FENOTCHATT4_FENOTCHCAPFINE10_DEFAULT       (_AGC_FENOTCHATT4_FENOTCHCAPFINE10_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHATT4    */
#define AGC_FENOTCHATT4_FENOTCHRATTNEN10               (0x1UL << 28)                                     /**< FE notch rattn enable for index 10          */
#define _AGC_FENOTCHATT4_FENOTCHRATTNEN10_SHIFT        28                                                /**< Shift value for AGC_FENOTCHRATTNEN10        */
#define _AGC_FENOTCHATT4_FENOTCHRATTNEN10_MASK         0x10000000UL                                      /**< Bit mask for AGC_FENOTCHRATTNEN10           */
#define _AGC_FENOTCHATT4_FENOTCHRATTNEN10_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT4            */
#define AGC_FENOTCHATT4_FENOTCHRATTNEN10_DEFAULT       (_AGC_FENOTCHATT4_FENOTCHRATTNEN10_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHATT4    */
#define AGC_FENOTCHATT4_FENOTCHEN10                    (0x1UL << 29)                                     /**< FE notch enable for index 10                */
#define _AGC_FENOTCHATT4_FENOTCHEN10_SHIFT             29                                                /**< Shift value for AGC_FENOTCHEN10             */
#define _AGC_FENOTCHATT4_FENOTCHEN10_MASK              0x20000000UL                                      /**< Bit mask for AGC_FENOTCHEN10                */
#define _AGC_FENOTCHATT4_FENOTCHEN10_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT4            */
#define AGC_FENOTCHATT4_FENOTCHEN10_DEFAULT            (_AGC_FENOTCHATT4_FENOTCHEN10_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT4    */

/* Bit fields for AGC FENOTCHATT5 */
#define _AGC_FENOTCHATT5_RESETVALUE                    0x00000000UL                                      /**< Default value for AGC_FENOTCHATT5           */
#define _AGC_FENOTCHATT5_MASK                          0x3FFF3FFFUL                                      /**< Mask for AGC_FENOTCHATT5                    */
#define _AGC_FENOTCHATT5_FENOTCHATTNSEL11_SHIFT        0                                                 /**< Shift value for AGC_FENOTCHATTNSEL11        */
#define _AGC_FENOTCHATT5_FENOTCHATTNSEL11_MASK         0xFUL                                             /**< Bit mask for AGC_FENOTCHATTNSEL11           */
#define _AGC_FENOTCHATT5_FENOTCHATTNSEL11_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT5            */
#define AGC_FENOTCHATT5_FENOTCHATTNSEL11_DEFAULT       (_AGC_FENOTCHATT5_FENOTCHATTNSEL11_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT5    */
#define _AGC_FENOTCHATT5_FENOTCHCAPCRSE11_SHIFT        4                                                 /**< Shift value for AGC_FENOTCHCAPCRSE11        */
#define _AGC_FENOTCHATT5_FENOTCHCAPCRSE11_MASK         0xF0UL                                            /**< Bit mask for AGC_FENOTCHCAPCRSE11           */
#define _AGC_FENOTCHATT5_FENOTCHCAPCRSE11_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT5            */
#define AGC_FENOTCHATT5_FENOTCHCAPCRSE11_DEFAULT       (_AGC_FENOTCHATT5_FENOTCHCAPCRSE11_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT5    */
#define _AGC_FENOTCHATT5_FENOTCHCAPFINE11_SHIFT        8                                                 /**< Shift value for AGC_FENOTCHCAPFINE11        */
#define _AGC_FENOTCHATT5_FENOTCHCAPFINE11_MASK         0xF00UL                                           /**< Bit mask for AGC_FENOTCHCAPFINE11           */
#define _AGC_FENOTCHATT5_FENOTCHCAPFINE11_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT5            */
#define AGC_FENOTCHATT5_FENOTCHCAPFINE11_DEFAULT       (_AGC_FENOTCHATT5_FENOTCHCAPFINE11_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT5    */
#define AGC_FENOTCHATT5_FENOTCHRATTNEN11               (0x1UL << 12)                                     /**< FE notch rattn enable for index 11          */
#define _AGC_FENOTCHATT5_FENOTCHRATTNEN11_SHIFT        12                                                /**< Shift value for AGC_FENOTCHRATTNEN11        */
#define _AGC_FENOTCHATT5_FENOTCHRATTNEN11_MASK         0x1000UL                                          /**< Bit mask for AGC_FENOTCHRATTNEN11           */
#define _AGC_FENOTCHATT5_FENOTCHRATTNEN11_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT5            */
#define AGC_FENOTCHATT5_FENOTCHRATTNEN11_DEFAULT       (_AGC_FENOTCHATT5_FENOTCHRATTNEN11_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHATT5    */
#define AGC_FENOTCHATT5_FENOTCHEN11                    (0x1UL << 13)                                     /**< FE notch enable for index 11                */
#define _AGC_FENOTCHATT5_FENOTCHEN11_SHIFT             13                                                /**< Shift value for AGC_FENOTCHEN11             */
#define _AGC_FENOTCHATT5_FENOTCHEN11_MASK              0x2000UL                                          /**< Bit mask for AGC_FENOTCHEN11                */
#define _AGC_FENOTCHATT5_FENOTCHEN11_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT5            */
#define AGC_FENOTCHATT5_FENOTCHEN11_DEFAULT            (_AGC_FENOTCHATT5_FENOTCHEN11_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT5    */
#define _AGC_FENOTCHATT5_FENOTCHATTNSEL12_SHIFT        16                                                /**< Shift value for AGC_FENOTCHATTNSEL12        */
#define _AGC_FENOTCHATT5_FENOTCHATTNSEL12_MASK         0xF0000UL                                         /**< Bit mask for AGC_FENOTCHATTNSEL12           */
#define _AGC_FENOTCHATT5_FENOTCHATTNSEL12_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT5            */
#define AGC_FENOTCHATT5_FENOTCHATTNSEL12_DEFAULT       (_AGC_FENOTCHATT5_FENOTCHATTNSEL12_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHATT5    */
#define _AGC_FENOTCHATT5_FENOTCHCAPCRSE12_SHIFT        20                                                /**< Shift value for AGC_FENOTCHCAPCRSE12        */
#define _AGC_FENOTCHATT5_FENOTCHCAPCRSE12_MASK         0xF00000UL                                        /**< Bit mask for AGC_FENOTCHCAPCRSE12           */
#define _AGC_FENOTCHATT5_FENOTCHCAPCRSE12_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT5            */
#define AGC_FENOTCHATT5_FENOTCHCAPCRSE12_DEFAULT       (_AGC_FENOTCHATT5_FENOTCHCAPCRSE12_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHATT5    */
#define _AGC_FENOTCHATT5_FENOTCHCAPFINE12_SHIFT        24                                                /**< Shift value for AGC_FENOTCHCAPFINE12        */
#define _AGC_FENOTCHATT5_FENOTCHCAPFINE12_MASK         0xF000000UL                                       /**< Bit mask for AGC_FENOTCHCAPFINE12           */
#define _AGC_FENOTCHATT5_FENOTCHCAPFINE12_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT5            */
#define AGC_FENOTCHATT5_FENOTCHCAPFINE12_DEFAULT       (_AGC_FENOTCHATT5_FENOTCHCAPFINE12_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHATT5    */
#define AGC_FENOTCHATT5_FENOTCHRATTNEN12               (0x1UL << 28)                                     /**< FE notch rattn enable for index 12          */
#define _AGC_FENOTCHATT5_FENOTCHRATTNEN12_SHIFT        28                                                /**< Shift value for AGC_FENOTCHRATTNEN12        */
#define _AGC_FENOTCHATT5_FENOTCHRATTNEN12_MASK         0x10000000UL                                      /**< Bit mask for AGC_FENOTCHRATTNEN12           */
#define _AGC_FENOTCHATT5_FENOTCHRATTNEN12_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT5            */
#define AGC_FENOTCHATT5_FENOTCHRATTNEN12_DEFAULT       (_AGC_FENOTCHATT5_FENOTCHRATTNEN12_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHATT5    */
#define AGC_FENOTCHATT5_FENOTCHEN12                    (0x1UL << 29)                                     /**< FE notch enable for index 12                */
#define _AGC_FENOTCHATT5_FENOTCHEN12_SHIFT             29                                                /**< Shift value for AGC_FENOTCHEN12             */
#define _AGC_FENOTCHATT5_FENOTCHEN12_MASK              0x20000000UL                                      /**< Bit mask for AGC_FENOTCHEN12                */
#define _AGC_FENOTCHATT5_FENOTCHEN12_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT5            */
#define AGC_FENOTCHATT5_FENOTCHEN12_DEFAULT            (_AGC_FENOTCHATT5_FENOTCHEN12_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT5    */

/* Bit fields for AGC FENOTCHATT6 */
#define _AGC_FENOTCHATT6_RESETVALUE                    0x00000000UL                                      /**< Default value for AGC_FENOTCHATT6           */
#define _AGC_FENOTCHATT6_MASK                          0x3FFF3FFFUL                                      /**< Mask for AGC_FENOTCHATT6                    */
#define _AGC_FENOTCHATT6_FENOTCHATTNSEL13_SHIFT        0                                                 /**< Shift value for AGC_FENOTCHATTNSEL13        */
#define _AGC_FENOTCHATT6_FENOTCHATTNSEL13_MASK         0xFUL                                             /**< Bit mask for AGC_FENOTCHATTNSEL13           */
#define _AGC_FENOTCHATT6_FENOTCHATTNSEL13_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT6            */
#define AGC_FENOTCHATT6_FENOTCHATTNSEL13_DEFAULT       (_AGC_FENOTCHATT6_FENOTCHATTNSEL13_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT6    */
#define _AGC_FENOTCHATT6_FENOTCHCAPCRSE13_SHIFT        4                                                 /**< Shift value for AGC_FENOTCHCAPCRSE13        */
#define _AGC_FENOTCHATT6_FENOTCHCAPCRSE13_MASK         0xF0UL                                            /**< Bit mask for AGC_FENOTCHCAPCRSE13           */
#define _AGC_FENOTCHATT6_FENOTCHCAPCRSE13_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT6            */
#define AGC_FENOTCHATT6_FENOTCHCAPCRSE13_DEFAULT       (_AGC_FENOTCHATT6_FENOTCHCAPCRSE13_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT6    */
#define _AGC_FENOTCHATT6_FENOTCHCAPFINE13_SHIFT        8                                                 /**< Shift value for AGC_FENOTCHCAPFINE13        */
#define _AGC_FENOTCHATT6_FENOTCHCAPFINE13_MASK         0xF00UL                                           /**< Bit mask for AGC_FENOTCHCAPFINE13           */
#define _AGC_FENOTCHATT6_FENOTCHCAPFINE13_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT6            */
#define AGC_FENOTCHATT6_FENOTCHCAPFINE13_DEFAULT       (_AGC_FENOTCHATT6_FENOTCHCAPFINE13_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT6    */
#define AGC_FENOTCHATT6_FENOTCHRATTNEN13               (0x1UL << 12)                                     /**< FE notch rattn enable for index 13          */
#define _AGC_FENOTCHATT6_FENOTCHRATTNEN13_SHIFT        12                                                /**< Shift value for AGC_FENOTCHRATTNEN13        */
#define _AGC_FENOTCHATT6_FENOTCHRATTNEN13_MASK         0x1000UL                                          /**< Bit mask for AGC_FENOTCHRATTNEN13           */
#define _AGC_FENOTCHATT6_FENOTCHRATTNEN13_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT6            */
#define AGC_FENOTCHATT6_FENOTCHRATTNEN13_DEFAULT       (_AGC_FENOTCHATT6_FENOTCHRATTNEN13_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHATT6    */
#define AGC_FENOTCHATT6_FENOTCHEN13                    (0x1UL << 13)                                     /**< FE notch enable for index 13                */
#define _AGC_FENOTCHATT6_FENOTCHEN13_SHIFT             13                                                /**< Shift value for AGC_FENOTCHEN13             */
#define _AGC_FENOTCHATT6_FENOTCHEN13_MASK              0x2000UL                                          /**< Bit mask for AGC_FENOTCHEN13                */
#define _AGC_FENOTCHATT6_FENOTCHEN13_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT6            */
#define AGC_FENOTCHATT6_FENOTCHEN13_DEFAULT            (_AGC_FENOTCHATT6_FENOTCHEN13_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT6    */
#define _AGC_FENOTCHATT6_FENOTCHATTNSEL14_SHIFT        16                                                /**< Shift value for AGC_FENOTCHATTNSEL14        */
#define _AGC_FENOTCHATT6_FENOTCHATTNSEL14_MASK         0xF0000UL                                         /**< Bit mask for AGC_FENOTCHATTNSEL14           */
#define _AGC_FENOTCHATT6_FENOTCHATTNSEL14_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT6            */
#define AGC_FENOTCHATT6_FENOTCHATTNSEL14_DEFAULT       (_AGC_FENOTCHATT6_FENOTCHATTNSEL14_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHATT6    */
#define _AGC_FENOTCHATT6_FENOTCHCAPCRSE14_SHIFT        20                                                /**< Shift value for AGC_FENOTCHCAPCRSE14        */
#define _AGC_FENOTCHATT6_FENOTCHCAPCRSE14_MASK         0xF00000UL                                        /**< Bit mask for AGC_FENOTCHCAPCRSE14           */
#define _AGC_FENOTCHATT6_FENOTCHCAPCRSE14_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT6            */
#define AGC_FENOTCHATT6_FENOTCHCAPCRSE14_DEFAULT       (_AGC_FENOTCHATT6_FENOTCHCAPCRSE14_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHATT6    */
#define _AGC_FENOTCHATT6_FENOTCHCAPFINE14_SHIFT        24                                                /**< Shift value for AGC_FENOTCHCAPFINE14        */
#define _AGC_FENOTCHATT6_FENOTCHCAPFINE14_MASK         0xF000000UL                                       /**< Bit mask for AGC_FENOTCHCAPFINE14           */
#define _AGC_FENOTCHATT6_FENOTCHCAPFINE14_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT6            */
#define AGC_FENOTCHATT6_FENOTCHCAPFINE14_DEFAULT       (_AGC_FENOTCHATT6_FENOTCHCAPFINE14_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHATT6    */
#define AGC_FENOTCHATT6_FENOTCHRATTNEN14               (0x1UL << 28)                                     /**< FE notch rattn enable for index 14          */
#define _AGC_FENOTCHATT6_FENOTCHRATTNEN14_SHIFT        28                                                /**< Shift value for AGC_FENOTCHRATTNEN14        */
#define _AGC_FENOTCHATT6_FENOTCHRATTNEN14_MASK         0x10000000UL                                      /**< Bit mask for AGC_FENOTCHRATTNEN14           */
#define _AGC_FENOTCHATT6_FENOTCHRATTNEN14_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT6            */
#define AGC_FENOTCHATT6_FENOTCHRATTNEN14_DEFAULT       (_AGC_FENOTCHATT6_FENOTCHRATTNEN14_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHATT6    */
#define AGC_FENOTCHATT6_FENOTCHEN14                    (0x1UL << 29)                                     /**< FE notch enable for index 14                */
#define _AGC_FENOTCHATT6_FENOTCHEN14_SHIFT             29                                                /**< Shift value for AGC_FENOTCHEN14             */
#define _AGC_FENOTCHATT6_FENOTCHEN14_MASK              0x20000000UL                                      /**< Bit mask for AGC_FENOTCHEN14                */
#define _AGC_FENOTCHATT6_FENOTCHEN14_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT6            */
#define AGC_FENOTCHATT6_FENOTCHEN14_DEFAULT            (_AGC_FENOTCHATT6_FENOTCHEN14_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT6    */

/* Bit fields for AGC FENOTCHATT7 */
#define _AGC_FENOTCHATT7_RESETVALUE                    0x20080000UL                                      /**< Default value for AGC_FENOTCHATT7           */
#define _AGC_FENOTCHATT7_MASK                          0x3FFF3FFFUL                                      /**< Mask for AGC_FENOTCHATT7                    */
#define _AGC_FENOTCHATT7_FENOTCHATTNSEL15_SHIFT        0                                                 /**< Shift value for AGC_FENOTCHATTNSEL15        */
#define _AGC_FENOTCHATT7_FENOTCHATTNSEL15_MASK         0xFUL                                             /**< Bit mask for AGC_FENOTCHATTNSEL15           */
#define _AGC_FENOTCHATT7_FENOTCHATTNSEL15_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT7            */
#define AGC_FENOTCHATT7_FENOTCHATTNSEL15_DEFAULT       (_AGC_FENOTCHATT7_FENOTCHATTNSEL15_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT7    */
#define _AGC_FENOTCHATT7_FENOTCHCAPCRSE15_SHIFT        4                                                 /**< Shift value for AGC_FENOTCHCAPCRSE15        */
#define _AGC_FENOTCHATT7_FENOTCHCAPCRSE15_MASK         0xF0UL                                            /**< Bit mask for AGC_FENOTCHCAPCRSE15           */
#define _AGC_FENOTCHATT7_FENOTCHCAPCRSE15_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT7            */
#define AGC_FENOTCHATT7_FENOTCHCAPCRSE15_DEFAULT       (_AGC_FENOTCHATT7_FENOTCHCAPCRSE15_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT7    */
#define _AGC_FENOTCHATT7_FENOTCHCAPFINE15_SHIFT        8                                                 /**< Shift value for AGC_FENOTCHCAPFINE15        */
#define _AGC_FENOTCHATT7_FENOTCHCAPFINE15_MASK         0xF00UL                                           /**< Bit mask for AGC_FENOTCHCAPFINE15           */
#define _AGC_FENOTCHATT7_FENOTCHCAPFINE15_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT7            */
#define AGC_FENOTCHATT7_FENOTCHCAPFINE15_DEFAULT       (_AGC_FENOTCHATT7_FENOTCHCAPFINE15_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT7    */
#define AGC_FENOTCHATT7_FENOTCHRATTNEN15               (0x1UL << 12)                                     /**< FE notch rattn enable for index 15          */
#define _AGC_FENOTCHATT7_FENOTCHRATTNEN15_SHIFT        12                                                /**< Shift value for AGC_FENOTCHRATTNEN15        */
#define _AGC_FENOTCHATT7_FENOTCHRATTNEN15_MASK         0x1000UL                                          /**< Bit mask for AGC_FENOTCHRATTNEN15           */
#define _AGC_FENOTCHATT7_FENOTCHRATTNEN15_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT7            */
#define AGC_FENOTCHATT7_FENOTCHRATTNEN15_DEFAULT       (_AGC_FENOTCHATT7_FENOTCHRATTNEN15_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHATT7    */
#define AGC_FENOTCHATT7_FENOTCHEN15                    (0x1UL << 13)                                     /**< FE notch enable for index 15                */
#define _AGC_FENOTCHATT7_FENOTCHEN15_SHIFT             13                                                /**< Shift value for AGC_FENOTCHEN15             */
#define _AGC_FENOTCHATT7_FENOTCHEN15_MASK              0x2000UL                                          /**< Bit mask for AGC_FENOTCHEN15                */
#define _AGC_FENOTCHATT7_FENOTCHEN15_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT7            */
#define AGC_FENOTCHATT7_FENOTCHEN15_DEFAULT            (_AGC_FENOTCHATT7_FENOTCHEN15_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT7    */
#define _AGC_FENOTCHATT7_FENOTCHATTNSEL16_SHIFT        16                                                /**< Shift value for AGC_FENOTCHATTNSEL16        */
#define _AGC_FENOTCHATT7_FENOTCHATTNSEL16_MASK         0xF0000UL                                         /**< Bit mask for AGC_FENOTCHATTNSEL16           */
#define _AGC_FENOTCHATT7_FENOTCHATTNSEL16_DEFAULT      0x00000008UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT7            */
#define AGC_FENOTCHATT7_FENOTCHATTNSEL16_DEFAULT       (_AGC_FENOTCHATT7_FENOTCHATTNSEL16_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHATT7    */
#define _AGC_FENOTCHATT7_FENOTCHCAPCRSE16_SHIFT        20                                                /**< Shift value for AGC_FENOTCHCAPCRSE16        */
#define _AGC_FENOTCHATT7_FENOTCHCAPCRSE16_MASK         0xF00000UL                                        /**< Bit mask for AGC_FENOTCHCAPCRSE16           */
#define _AGC_FENOTCHATT7_FENOTCHCAPCRSE16_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT7            */
#define AGC_FENOTCHATT7_FENOTCHCAPCRSE16_DEFAULT       (_AGC_FENOTCHATT7_FENOTCHCAPCRSE16_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHATT7    */
#define _AGC_FENOTCHATT7_FENOTCHCAPFINE16_SHIFT        24                                                /**< Shift value for AGC_FENOTCHCAPFINE16        */
#define _AGC_FENOTCHATT7_FENOTCHCAPFINE16_MASK         0xF000000UL                                       /**< Bit mask for AGC_FENOTCHCAPFINE16           */
#define _AGC_FENOTCHATT7_FENOTCHCAPFINE16_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT7            */
#define AGC_FENOTCHATT7_FENOTCHCAPFINE16_DEFAULT       (_AGC_FENOTCHATT7_FENOTCHCAPFINE16_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHATT7    */
#define AGC_FENOTCHATT7_FENOTCHRATTNEN16               (0x1UL << 28)                                     /**< FE notch rattn enable for index 16          */
#define _AGC_FENOTCHATT7_FENOTCHRATTNEN16_SHIFT        28                                                /**< Shift value for AGC_FENOTCHRATTNEN16        */
#define _AGC_FENOTCHATT7_FENOTCHRATTNEN16_MASK         0x10000000UL                                      /**< Bit mask for AGC_FENOTCHRATTNEN16           */
#define _AGC_FENOTCHATT7_FENOTCHRATTNEN16_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT7            */
#define AGC_FENOTCHATT7_FENOTCHRATTNEN16_DEFAULT       (_AGC_FENOTCHATT7_FENOTCHRATTNEN16_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHATT7    */
#define AGC_FENOTCHATT7_FENOTCHEN16                    (0x1UL << 29)                                     /**< FE notch enable for index 16                */
#define _AGC_FENOTCHATT7_FENOTCHEN16_SHIFT             29                                                /**< Shift value for AGC_FENOTCHEN16             */
#define _AGC_FENOTCHATT7_FENOTCHEN16_MASK              0x20000000UL                                      /**< Bit mask for AGC_FENOTCHEN16                */
#define _AGC_FENOTCHATT7_FENOTCHEN16_DEFAULT           0x00000001UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT7            */
#define AGC_FENOTCHATT7_FENOTCHEN16_DEFAULT            (_AGC_FENOTCHATT7_FENOTCHEN16_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT7    */

/* Bit fields for AGC FENOTCHATT8 */
#define _AGC_FENOTCHATT8_RESETVALUE                    0x200B200AUL                                      /**< Default value for AGC_FENOTCHATT8           */
#define _AGC_FENOTCHATT8_MASK                          0x3FFF3FFFUL                                      /**< Mask for AGC_FENOTCHATT8                    */
#define _AGC_FENOTCHATT8_FENOTCHATTNSEL17_SHIFT        0                                                 /**< Shift value for AGC_FENOTCHATTNSEL17        */
#define _AGC_FENOTCHATT8_FENOTCHATTNSEL17_MASK         0xFUL                                             /**< Bit mask for AGC_FENOTCHATTNSEL17           */
#define _AGC_FENOTCHATT8_FENOTCHATTNSEL17_DEFAULT      0x0000000AUL                                      /**< Mode DEFAULT for AGC_FENOTCHATT8            */
#define AGC_FENOTCHATT8_FENOTCHATTNSEL17_DEFAULT       (_AGC_FENOTCHATT8_FENOTCHATTNSEL17_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT8    */
#define _AGC_FENOTCHATT8_FENOTCHCAPCRSE17_SHIFT        4                                                 /**< Shift value for AGC_FENOTCHCAPCRSE17        */
#define _AGC_FENOTCHATT8_FENOTCHCAPCRSE17_MASK         0xF0UL                                            /**< Bit mask for AGC_FENOTCHCAPCRSE17           */
#define _AGC_FENOTCHATT8_FENOTCHCAPCRSE17_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT8            */
#define AGC_FENOTCHATT8_FENOTCHCAPCRSE17_DEFAULT       (_AGC_FENOTCHATT8_FENOTCHCAPCRSE17_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT8    */
#define _AGC_FENOTCHATT8_FENOTCHCAPFINE17_SHIFT        8                                                 /**< Shift value for AGC_FENOTCHCAPFINE17        */
#define _AGC_FENOTCHATT8_FENOTCHCAPFINE17_MASK         0xF00UL                                           /**< Bit mask for AGC_FENOTCHCAPFINE17           */
#define _AGC_FENOTCHATT8_FENOTCHCAPFINE17_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT8            */
#define AGC_FENOTCHATT8_FENOTCHCAPFINE17_DEFAULT       (_AGC_FENOTCHATT8_FENOTCHCAPFINE17_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT8    */
#define AGC_FENOTCHATT8_FENOTCHRATTNEN17               (0x1UL << 12)                                     /**< FE notch rattn enable for index 17          */
#define _AGC_FENOTCHATT8_FENOTCHRATTNEN17_SHIFT        12                                                /**< Shift value for AGC_FENOTCHRATTNEN17        */
#define _AGC_FENOTCHATT8_FENOTCHRATTNEN17_MASK         0x1000UL                                          /**< Bit mask for AGC_FENOTCHRATTNEN17           */
#define _AGC_FENOTCHATT8_FENOTCHRATTNEN17_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT8            */
#define AGC_FENOTCHATT8_FENOTCHRATTNEN17_DEFAULT       (_AGC_FENOTCHATT8_FENOTCHRATTNEN17_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHATT8    */
#define AGC_FENOTCHATT8_FENOTCHEN17                    (0x1UL << 13)                                     /**< FE notch enable for index 17                */
#define _AGC_FENOTCHATT8_FENOTCHEN17_SHIFT             13                                                /**< Shift value for AGC_FENOTCHEN17             */
#define _AGC_FENOTCHATT8_FENOTCHEN17_MASK              0x2000UL                                          /**< Bit mask for AGC_FENOTCHEN17                */
#define _AGC_FENOTCHATT8_FENOTCHEN17_DEFAULT           0x00000001UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT8            */
#define AGC_FENOTCHATT8_FENOTCHEN17_DEFAULT            (_AGC_FENOTCHATT8_FENOTCHEN17_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT8    */
#define _AGC_FENOTCHATT8_FENOTCHATTNSEL18_SHIFT        16                                                /**< Shift value for AGC_FENOTCHATTNSEL18        */
#define _AGC_FENOTCHATT8_FENOTCHATTNSEL18_MASK         0xF0000UL                                         /**< Bit mask for AGC_FENOTCHATTNSEL18           */
#define _AGC_FENOTCHATT8_FENOTCHATTNSEL18_DEFAULT      0x0000000BUL                                      /**< Mode DEFAULT for AGC_FENOTCHATT8            */
#define AGC_FENOTCHATT8_FENOTCHATTNSEL18_DEFAULT       (_AGC_FENOTCHATT8_FENOTCHATTNSEL18_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHATT8    */
#define _AGC_FENOTCHATT8_FENOTCHCAPCRSE18_SHIFT        20                                                /**< Shift value for AGC_FENOTCHCAPCRSE18        */
#define _AGC_FENOTCHATT8_FENOTCHCAPCRSE18_MASK         0xF00000UL                                        /**< Bit mask for AGC_FENOTCHCAPCRSE18           */
#define _AGC_FENOTCHATT8_FENOTCHCAPCRSE18_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT8            */
#define AGC_FENOTCHATT8_FENOTCHCAPCRSE18_DEFAULT       (_AGC_FENOTCHATT8_FENOTCHCAPCRSE18_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHATT8    */
#define _AGC_FENOTCHATT8_FENOTCHCAPFINE18_SHIFT        24                                                /**< Shift value for AGC_FENOTCHCAPFINE18        */
#define _AGC_FENOTCHATT8_FENOTCHCAPFINE18_MASK         0xF000000UL                                       /**< Bit mask for AGC_FENOTCHCAPFINE18           */
#define _AGC_FENOTCHATT8_FENOTCHCAPFINE18_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT8            */
#define AGC_FENOTCHATT8_FENOTCHCAPFINE18_DEFAULT       (_AGC_FENOTCHATT8_FENOTCHCAPFINE18_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHATT8    */
#define AGC_FENOTCHATT8_FENOTCHRATTNEN18               (0x1UL << 28)                                     /**< FE notch rattn enable for index 18          */
#define _AGC_FENOTCHATT8_FENOTCHRATTNEN18_SHIFT        28                                                /**< Shift value for AGC_FENOTCHRATTNEN18        */
#define _AGC_FENOTCHATT8_FENOTCHRATTNEN18_MASK         0x10000000UL                                      /**< Bit mask for AGC_FENOTCHRATTNEN18           */
#define _AGC_FENOTCHATT8_FENOTCHRATTNEN18_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT8            */
#define AGC_FENOTCHATT8_FENOTCHRATTNEN18_DEFAULT       (_AGC_FENOTCHATT8_FENOTCHRATTNEN18_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHATT8    */
#define AGC_FENOTCHATT8_FENOTCHEN18                    (0x1UL << 29)                                     /**< FE notch enable for index 18                */
#define _AGC_FENOTCHATT8_FENOTCHEN18_SHIFT             29                                                /**< Shift value for AGC_FENOTCHEN18             */
#define _AGC_FENOTCHATT8_FENOTCHEN18_MASK              0x20000000UL                                      /**< Bit mask for AGC_FENOTCHEN18                */
#define _AGC_FENOTCHATT8_FENOTCHEN18_DEFAULT           0x00000001UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT8            */
#define AGC_FENOTCHATT8_FENOTCHEN18_DEFAULT            (_AGC_FENOTCHATT8_FENOTCHEN18_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT8    */

/* Bit fields for AGC FENOTCHATT9 */
#define _AGC_FENOTCHATT9_RESETVALUE                    0x200B200BUL                                      /**< Default value for AGC_FENOTCHATT9           */
#define _AGC_FENOTCHATT9_MASK                          0x3FFF3FFFUL                                      /**< Mask for AGC_FENOTCHATT9                    */
#define _AGC_FENOTCHATT9_FENOTCHATTNSEL19_SHIFT        0                                                 /**< Shift value for AGC_FENOTCHATTNSEL19        */
#define _AGC_FENOTCHATT9_FENOTCHATTNSEL19_MASK         0xFUL                                             /**< Bit mask for AGC_FENOTCHATTNSEL19           */
#define _AGC_FENOTCHATT9_FENOTCHATTNSEL19_DEFAULT      0x0000000BUL                                      /**< Mode DEFAULT for AGC_FENOTCHATT9            */
#define AGC_FENOTCHATT9_FENOTCHATTNSEL19_DEFAULT       (_AGC_FENOTCHATT9_FENOTCHATTNSEL19_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT9    */
#define _AGC_FENOTCHATT9_FENOTCHCAPCRSE19_SHIFT        4                                                 /**< Shift value for AGC_FENOTCHCAPCRSE19        */
#define _AGC_FENOTCHATT9_FENOTCHCAPCRSE19_MASK         0xF0UL                                            /**< Bit mask for AGC_FENOTCHCAPCRSE19           */
#define _AGC_FENOTCHATT9_FENOTCHCAPCRSE19_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT9            */
#define AGC_FENOTCHATT9_FENOTCHCAPCRSE19_DEFAULT       (_AGC_FENOTCHATT9_FENOTCHCAPCRSE19_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT9    */
#define _AGC_FENOTCHATT9_FENOTCHCAPFINE19_SHIFT        8                                                 /**< Shift value for AGC_FENOTCHCAPFINE19        */
#define _AGC_FENOTCHATT9_FENOTCHCAPFINE19_MASK         0xF00UL                                           /**< Bit mask for AGC_FENOTCHCAPFINE19           */
#define _AGC_FENOTCHATT9_FENOTCHCAPFINE19_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT9            */
#define AGC_FENOTCHATT9_FENOTCHCAPFINE19_DEFAULT       (_AGC_FENOTCHATT9_FENOTCHCAPFINE19_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT9    */
#define AGC_FENOTCHATT9_FENOTCHRATTNEN19               (0x1UL << 12)                                     /**< FE notch rattn enable for index 19          */
#define _AGC_FENOTCHATT9_FENOTCHRATTNEN19_SHIFT        12                                                /**< Shift value for AGC_FENOTCHRATTNEN19        */
#define _AGC_FENOTCHATT9_FENOTCHRATTNEN19_MASK         0x1000UL                                          /**< Bit mask for AGC_FENOTCHRATTNEN19           */
#define _AGC_FENOTCHATT9_FENOTCHRATTNEN19_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT9            */
#define AGC_FENOTCHATT9_FENOTCHRATTNEN19_DEFAULT       (_AGC_FENOTCHATT9_FENOTCHRATTNEN19_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHATT9    */
#define AGC_FENOTCHATT9_FENOTCHEN19                    (0x1UL << 13)                                     /**< FE notch enable for index 19                */
#define _AGC_FENOTCHATT9_FENOTCHEN19_SHIFT             13                                                /**< Shift value for AGC_FENOTCHEN19             */
#define _AGC_FENOTCHATT9_FENOTCHEN19_MASK              0x2000UL                                          /**< Bit mask for AGC_FENOTCHEN19                */
#define _AGC_FENOTCHATT9_FENOTCHEN19_DEFAULT           0x00000001UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT9            */
#define AGC_FENOTCHATT9_FENOTCHEN19_DEFAULT            (_AGC_FENOTCHATT9_FENOTCHEN19_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT9    */
#define _AGC_FENOTCHATT9_FENOTCHATTNSEL20_SHIFT        16                                                /**< Shift value for AGC_FENOTCHATTNSEL20        */
#define _AGC_FENOTCHATT9_FENOTCHATTNSEL20_MASK         0xF0000UL                                         /**< Bit mask for AGC_FENOTCHATTNSEL20           */
#define _AGC_FENOTCHATT9_FENOTCHATTNSEL20_DEFAULT      0x0000000BUL                                      /**< Mode DEFAULT for AGC_FENOTCHATT9            */
#define AGC_FENOTCHATT9_FENOTCHATTNSEL20_DEFAULT       (_AGC_FENOTCHATT9_FENOTCHATTNSEL20_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHATT9    */
#define _AGC_FENOTCHATT9_FENOTCHCAPCRSE20_SHIFT        20                                                /**< Shift value for AGC_FENOTCHCAPCRSE20        */
#define _AGC_FENOTCHATT9_FENOTCHCAPCRSE20_MASK         0xF00000UL                                        /**< Bit mask for AGC_FENOTCHCAPCRSE20           */
#define _AGC_FENOTCHATT9_FENOTCHCAPCRSE20_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT9            */
#define AGC_FENOTCHATT9_FENOTCHCAPCRSE20_DEFAULT       (_AGC_FENOTCHATT9_FENOTCHCAPCRSE20_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHATT9    */
#define _AGC_FENOTCHATT9_FENOTCHCAPFINE20_SHIFT        24                                                /**< Shift value for AGC_FENOTCHCAPFINE20        */
#define _AGC_FENOTCHATT9_FENOTCHCAPFINE20_MASK         0xF000000UL                                       /**< Bit mask for AGC_FENOTCHCAPFINE20           */
#define _AGC_FENOTCHATT9_FENOTCHCAPFINE20_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT9            */
#define AGC_FENOTCHATT9_FENOTCHCAPFINE20_DEFAULT       (_AGC_FENOTCHATT9_FENOTCHCAPFINE20_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHATT9    */
#define AGC_FENOTCHATT9_FENOTCHRATTNEN20               (0x1UL << 28)                                     /**< FE notch rattn enable for index 20          */
#define _AGC_FENOTCHATT9_FENOTCHRATTNEN20_SHIFT        28                                                /**< Shift value for AGC_FENOTCHRATTNEN20        */
#define _AGC_FENOTCHATT9_FENOTCHRATTNEN20_MASK         0x10000000UL                                      /**< Bit mask for AGC_FENOTCHRATTNEN20           */
#define _AGC_FENOTCHATT9_FENOTCHRATTNEN20_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT9            */
#define AGC_FENOTCHATT9_FENOTCHRATTNEN20_DEFAULT       (_AGC_FENOTCHATT9_FENOTCHRATTNEN20_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHATT9    */
#define AGC_FENOTCHATT9_FENOTCHEN20                    (0x1UL << 29)                                     /**< FE notch enable for index 20                */
#define _AGC_FENOTCHATT9_FENOTCHEN20_SHIFT             29                                                /**< Shift value for AGC_FENOTCHEN20             */
#define _AGC_FENOTCHATT9_FENOTCHEN20_MASK              0x20000000UL                                      /**< Bit mask for AGC_FENOTCHEN20                */
#define _AGC_FENOTCHATT9_FENOTCHEN20_DEFAULT           0x00000001UL                                      /**< Mode DEFAULT for AGC_FENOTCHATT9            */
#define AGC_FENOTCHATT9_FENOTCHEN20_DEFAULT            (_AGC_FENOTCHATT9_FENOTCHEN20_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT9    */

/* Bit fields for AGC FENOTCHATT10 */
#define _AGC_FENOTCHATT10_RESETVALUE                   0x200B200BUL                                       /**< Default value for AGC_FENOTCHATT10          */
#define _AGC_FENOTCHATT10_MASK                         0x3FFF3FFFUL                                       /**< Mask for AGC_FENOTCHATT10                   */
#define _AGC_FENOTCHATT10_FENOTCHATTNSEL21_SHIFT       0                                                  /**< Shift value for AGC_FENOTCHATTNSEL21        */
#define _AGC_FENOTCHATT10_FENOTCHATTNSEL21_MASK        0xFUL                                              /**< Bit mask for AGC_FENOTCHATTNSEL21           */
#define _AGC_FENOTCHATT10_FENOTCHATTNSEL21_DEFAULT     0x0000000BUL                                       /**< Mode DEFAULT for AGC_FENOTCHATT10           */
#define AGC_FENOTCHATT10_FENOTCHATTNSEL21_DEFAULT      (_AGC_FENOTCHATT10_FENOTCHATTNSEL21_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT10   */
#define _AGC_FENOTCHATT10_FENOTCHCAPCRSE21_SHIFT       4                                                  /**< Shift value for AGC_FENOTCHCAPCRSE21        */
#define _AGC_FENOTCHATT10_FENOTCHCAPCRSE21_MASK        0xF0UL                                             /**< Bit mask for AGC_FENOTCHCAPCRSE21           */
#define _AGC_FENOTCHATT10_FENOTCHCAPCRSE21_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHATT10           */
#define AGC_FENOTCHATT10_FENOTCHCAPCRSE21_DEFAULT      (_AGC_FENOTCHATT10_FENOTCHCAPCRSE21_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT10   */
#define _AGC_FENOTCHATT10_FENOTCHCAPFINE21_SHIFT       8                                                  /**< Shift value for AGC_FENOTCHCAPFINE21        */
#define _AGC_FENOTCHATT10_FENOTCHCAPFINE21_MASK        0xF00UL                                            /**< Bit mask for AGC_FENOTCHCAPFINE21           */
#define _AGC_FENOTCHATT10_FENOTCHCAPFINE21_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHATT10           */
#define AGC_FENOTCHATT10_FENOTCHCAPFINE21_DEFAULT      (_AGC_FENOTCHATT10_FENOTCHCAPFINE21_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT10   */
#define AGC_FENOTCHATT10_FENOTCHRATTNEN21              (0x1UL << 12)                                      /**< FE notch rattn enable for index 21          */
#define _AGC_FENOTCHATT10_FENOTCHRATTNEN21_SHIFT       12                                                 /**< Shift value for AGC_FENOTCHRATTNEN21        */
#define _AGC_FENOTCHATT10_FENOTCHRATTNEN21_MASK        0x1000UL                                           /**< Bit mask for AGC_FENOTCHRATTNEN21           */
#define _AGC_FENOTCHATT10_FENOTCHRATTNEN21_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHATT10           */
#define AGC_FENOTCHATT10_FENOTCHRATTNEN21_DEFAULT      (_AGC_FENOTCHATT10_FENOTCHRATTNEN21_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHATT10   */
#define AGC_FENOTCHATT10_FENOTCHEN21                   (0x1UL << 13)                                      /**< FE notch enable for index 21                */
#define _AGC_FENOTCHATT10_FENOTCHEN21_SHIFT            13                                                 /**< Shift value for AGC_FENOTCHEN21             */
#define _AGC_FENOTCHATT10_FENOTCHEN21_MASK             0x2000UL                                           /**< Bit mask for AGC_FENOTCHEN21                */
#define _AGC_FENOTCHATT10_FENOTCHEN21_DEFAULT          0x00000001UL                                       /**< Mode DEFAULT for AGC_FENOTCHATT10           */
#define AGC_FENOTCHATT10_FENOTCHEN21_DEFAULT           (_AGC_FENOTCHATT10_FENOTCHEN21_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT10   */
#define _AGC_FENOTCHATT10_FENOTCHATTNSEL22_SHIFT       16                                                 /**< Shift value for AGC_FENOTCHATTNSEL22        */
#define _AGC_FENOTCHATT10_FENOTCHATTNSEL22_MASK        0xF0000UL                                          /**< Bit mask for AGC_FENOTCHATTNSEL22           */
#define _AGC_FENOTCHATT10_FENOTCHATTNSEL22_DEFAULT     0x0000000BUL                                       /**< Mode DEFAULT for AGC_FENOTCHATT10           */
#define AGC_FENOTCHATT10_FENOTCHATTNSEL22_DEFAULT      (_AGC_FENOTCHATT10_FENOTCHATTNSEL22_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHATT10   */
#define _AGC_FENOTCHATT10_FENOTCHCAPCRSE22_SHIFT       20                                                 /**< Shift value for AGC_FENOTCHCAPCRSE22        */
#define _AGC_FENOTCHATT10_FENOTCHCAPCRSE22_MASK        0xF00000UL                                         /**< Bit mask for AGC_FENOTCHCAPCRSE22           */
#define _AGC_FENOTCHATT10_FENOTCHCAPCRSE22_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHATT10           */
#define AGC_FENOTCHATT10_FENOTCHCAPCRSE22_DEFAULT      (_AGC_FENOTCHATT10_FENOTCHCAPCRSE22_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHATT10   */
#define _AGC_FENOTCHATT10_FENOTCHCAPFINE22_SHIFT       24                                                 /**< Shift value for AGC_FENOTCHCAPFINE22        */
#define _AGC_FENOTCHATT10_FENOTCHCAPFINE22_MASK        0xF000000UL                                        /**< Bit mask for AGC_FENOTCHCAPFINE22           */
#define _AGC_FENOTCHATT10_FENOTCHCAPFINE22_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHATT10           */
#define AGC_FENOTCHATT10_FENOTCHCAPFINE22_DEFAULT      (_AGC_FENOTCHATT10_FENOTCHCAPFINE22_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHATT10   */
#define AGC_FENOTCHATT10_FENOTCHRATTNEN22              (0x1UL << 28)                                      /**< FE notch rattn enable for index 22          */
#define _AGC_FENOTCHATT10_FENOTCHRATTNEN22_SHIFT       28                                                 /**< Shift value for AGC_FENOTCHRATTNEN22        */
#define _AGC_FENOTCHATT10_FENOTCHRATTNEN22_MASK        0x10000000UL                                       /**< Bit mask for AGC_FENOTCHRATTNEN22           */
#define _AGC_FENOTCHATT10_FENOTCHRATTNEN22_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHATT10           */
#define AGC_FENOTCHATT10_FENOTCHRATTNEN22_DEFAULT      (_AGC_FENOTCHATT10_FENOTCHRATTNEN22_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHATT10   */
#define AGC_FENOTCHATT10_FENOTCHEN22                   (0x1UL << 29)                                      /**< FE notch enable for index 22                */
#define _AGC_FENOTCHATT10_FENOTCHEN22_SHIFT            29                                                 /**< Shift value for AGC_FENOTCHEN22             */
#define _AGC_FENOTCHATT10_FENOTCHEN22_MASK             0x20000000UL                                       /**< Bit mask for AGC_FENOTCHEN22                */
#define _AGC_FENOTCHATT10_FENOTCHEN22_DEFAULT          0x00000001UL                                       /**< Mode DEFAULT for AGC_FENOTCHATT10           */
#define AGC_FENOTCHATT10_FENOTCHEN22_DEFAULT           (_AGC_FENOTCHATT10_FENOTCHEN22_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT10   */

/* Bit fields for AGC FENOTCHATT11 */
#define _AGC_FENOTCHATT11_RESETVALUE                   0x200B200BUL                                       /**< Default value for AGC_FENOTCHATT11          */
#define _AGC_FENOTCHATT11_MASK                         0x3FFF3FFFUL                                       /**< Mask for AGC_FENOTCHATT11                   */
#define _AGC_FENOTCHATT11_FENOTCHATTNSEL23_SHIFT       0                                                  /**< Shift value for AGC_FENOTCHATTNSEL23        */
#define _AGC_FENOTCHATT11_FENOTCHATTNSEL23_MASK        0xFUL                                              /**< Bit mask for AGC_FENOTCHATTNSEL23           */
#define _AGC_FENOTCHATT11_FENOTCHATTNSEL23_DEFAULT     0x0000000BUL                                       /**< Mode DEFAULT for AGC_FENOTCHATT11           */
#define AGC_FENOTCHATT11_FENOTCHATTNSEL23_DEFAULT      (_AGC_FENOTCHATT11_FENOTCHATTNSEL23_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT11   */
#define _AGC_FENOTCHATT11_FENOTCHCAPCRSE23_SHIFT       4                                                  /**< Shift value for AGC_FENOTCHCAPCRSE23        */
#define _AGC_FENOTCHATT11_FENOTCHCAPCRSE23_MASK        0xF0UL                                             /**< Bit mask for AGC_FENOTCHCAPCRSE23           */
#define _AGC_FENOTCHATT11_FENOTCHCAPCRSE23_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHATT11           */
#define AGC_FENOTCHATT11_FENOTCHCAPCRSE23_DEFAULT      (_AGC_FENOTCHATT11_FENOTCHCAPCRSE23_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT11   */
#define _AGC_FENOTCHATT11_FENOTCHCAPFINE23_SHIFT       8                                                  /**< Shift value for AGC_FENOTCHCAPFINE23        */
#define _AGC_FENOTCHATT11_FENOTCHCAPFINE23_MASK        0xF00UL                                            /**< Bit mask for AGC_FENOTCHCAPFINE23           */
#define _AGC_FENOTCHATT11_FENOTCHCAPFINE23_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHATT11           */
#define AGC_FENOTCHATT11_FENOTCHCAPFINE23_DEFAULT      (_AGC_FENOTCHATT11_FENOTCHCAPFINE23_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHATT11   */
#define AGC_FENOTCHATT11_FENOTCHRATTNEN23              (0x1UL << 12)                                      /**< FE notch rattn enable for index 23          */
#define _AGC_FENOTCHATT11_FENOTCHRATTNEN23_SHIFT       12                                                 /**< Shift value for AGC_FENOTCHRATTNEN23        */
#define _AGC_FENOTCHATT11_FENOTCHRATTNEN23_MASK        0x1000UL                                           /**< Bit mask for AGC_FENOTCHRATTNEN23           */
#define _AGC_FENOTCHATT11_FENOTCHRATTNEN23_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHATT11           */
#define AGC_FENOTCHATT11_FENOTCHRATTNEN23_DEFAULT      (_AGC_FENOTCHATT11_FENOTCHRATTNEN23_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHATT11   */
#define AGC_FENOTCHATT11_FENOTCHEN23                   (0x1UL << 13)                                      /**< FE notch enable for index 23                */
#define _AGC_FENOTCHATT11_FENOTCHEN23_SHIFT            13                                                 /**< Shift value for AGC_FENOTCHEN23             */
#define _AGC_FENOTCHATT11_FENOTCHEN23_MASK             0x2000UL                                           /**< Bit mask for AGC_FENOTCHEN23                */
#define _AGC_FENOTCHATT11_FENOTCHEN23_DEFAULT          0x00000001UL                                       /**< Mode DEFAULT for AGC_FENOTCHATT11           */
#define AGC_FENOTCHATT11_FENOTCHEN23_DEFAULT           (_AGC_FENOTCHATT11_FENOTCHEN23_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT11   */
#define _AGC_FENOTCHATT11_FENOTCHATTNSEL24_SHIFT       16                                                 /**< Shift value for AGC_FENOTCHATTNSEL24        */
#define _AGC_FENOTCHATT11_FENOTCHATTNSEL24_MASK        0xF0000UL                                          /**< Bit mask for AGC_FENOTCHATTNSEL24           */
#define _AGC_FENOTCHATT11_FENOTCHATTNSEL24_DEFAULT     0x0000000BUL                                       /**< Mode DEFAULT for AGC_FENOTCHATT11           */
#define AGC_FENOTCHATT11_FENOTCHATTNSEL24_DEFAULT      (_AGC_FENOTCHATT11_FENOTCHATTNSEL24_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHATT11   */
#define _AGC_FENOTCHATT11_FENOTCHCAPCRSE24_SHIFT       20                                                 /**< Shift value for AGC_FENOTCHCAPCRSE24        */
#define _AGC_FENOTCHATT11_FENOTCHCAPCRSE24_MASK        0xF00000UL                                         /**< Bit mask for AGC_FENOTCHCAPCRSE24           */
#define _AGC_FENOTCHATT11_FENOTCHCAPCRSE24_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHATT11           */
#define AGC_FENOTCHATT11_FENOTCHCAPCRSE24_DEFAULT      (_AGC_FENOTCHATT11_FENOTCHCAPCRSE24_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHATT11   */
#define _AGC_FENOTCHATT11_FENOTCHCAPFINE24_SHIFT       24                                                 /**< Shift value for AGC_FENOTCHCAPFINE24        */
#define _AGC_FENOTCHATT11_FENOTCHCAPFINE24_MASK        0xF000000UL                                        /**< Bit mask for AGC_FENOTCHCAPFINE24           */
#define _AGC_FENOTCHATT11_FENOTCHCAPFINE24_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHATT11           */
#define AGC_FENOTCHATT11_FENOTCHCAPFINE24_DEFAULT      (_AGC_FENOTCHATT11_FENOTCHCAPFINE24_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHATT11   */
#define AGC_FENOTCHATT11_FENOTCHRATTNEN24              (0x1UL << 28)                                      /**< FE notch rattn enable for index 24          */
#define _AGC_FENOTCHATT11_FENOTCHRATTNEN24_SHIFT       28                                                 /**< Shift value for AGC_FENOTCHRATTNEN24        */
#define _AGC_FENOTCHATT11_FENOTCHRATTNEN24_MASK        0x10000000UL                                       /**< Bit mask for AGC_FENOTCHRATTNEN24           */
#define _AGC_FENOTCHATT11_FENOTCHRATTNEN24_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHATT11           */
#define AGC_FENOTCHATT11_FENOTCHRATTNEN24_DEFAULT      (_AGC_FENOTCHATT11_FENOTCHRATTNEN24_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHATT11   */
#define AGC_FENOTCHATT11_FENOTCHEN24                   (0x1UL << 29)                                      /**< FE notch enable for index 24                */
#define _AGC_FENOTCHATT11_FENOTCHEN24_SHIFT            29                                                 /**< Shift value for AGC_FENOTCHEN24             */
#define _AGC_FENOTCHATT11_FENOTCHEN24_MASK             0x20000000UL                                       /**< Bit mask for AGC_FENOTCHEN24                */
#define _AGC_FENOTCHATT11_FENOTCHEN24_DEFAULT          0x00000001UL                                       /**< Mode DEFAULT for AGC_FENOTCHATT11           */
#define AGC_FENOTCHATT11_FENOTCHEN24_DEFAULT           (_AGC_FENOTCHATT11_FENOTCHEN24_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHATT11   */

/* Bit fields for AGC FENOTCHFILT0 */
#define _AGC_FENOTCHFILT0_RESETVALUE                   0x00000000UL                                      /**< Default value for AGC_FENOTCHFILT0          */
#define _AGC_FENOTCHFILT0_MASK                         0x3FFF3FFFUL                                      /**< Mask for AGC_FENOTCHFILT0                   */
#define _AGC_FENOTCHFILT0_FENOTCHATTNSEL1_SHIFT        0                                                 /**< Shift value for AGC_FENOTCHATTNSEL1         */
#define _AGC_FENOTCHFILT0_FENOTCHATTNSEL1_MASK         0xFUL                                             /**< Bit mask for AGC_FENOTCHATTNSEL1            */
#define _AGC_FENOTCHFILT0_FENOTCHATTNSEL1_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT0           */
#define AGC_FENOTCHFILT0_FENOTCHATTNSEL1_DEFAULT       (_AGC_FENOTCHFILT0_FENOTCHATTNSEL1_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT0   */
#define _AGC_FENOTCHFILT0_FENOTCHCAPCRSE1_SHIFT        4                                                 /**< Shift value for AGC_FENOTCHCAPCRSE1         */
#define _AGC_FENOTCHFILT0_FENOTCHCAPCRSE1_MASK         0xF0UL                                            /**< Bit mask for AGC_FENOTCHCAPCRSE1            */
#define _AGC_FENOTCHFILT0_FENOTCHCAPCRSE1_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT0           */
#define AGC_FENOTCHFILT0_FENOTCHCAPCRSE1_DEFAULT       (_AGC_FENOTCHFILT0_FENOTCHCAPCRSE1_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT0   */
#define _AGC_FENOTCHFILT0_FENOTCHCAPFINE1_SHIFT        8                                                 /**< Shift value for AGC_FENOTCHCAPFINE1         */
#define _AGC_FENOTCHFILT0_FENOTCHCAPFINE1_MASK         0xF00UL                                           /**< Bit mask for AGC_FENOTCHCAPFINE1            */
#define _AGC_FENOTCHFILT0_FENOTCHCAPFINE1_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT0           */
#define AGC_FENOTCHFILT0_FENOTCHCAPFINE1_DEFAULT       (_AGC_FENOTCHFILT0_FENOTCHCAPFINE1_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT0   */
#define AGC_FENOTCHFILT0_FENOTCHRATTNEN1               (0x1UL << 12)                                     /**< FE notch rattn enable for index 1           */
#define _AGC_FENOTCHFILT0_FENOTCHRATTNEN1_SHIFT        12                                                /**< Shift value for AGC_FENOTCHRATTNEN1         */
#define _AGC_FENOTCHFILT0_FENOTCHRATTNEN1_MASK         0x1000UL                                          /**< Bit mask for AGC_FENOTCHRATTNEN1            */
#define _AGC_FENOTCHFILT0_FENOTCHRATTNEN1_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT0           */
#define AGC_FENOTCHFILT0_FENOTCHRATTNEN1_DEFAULT       (_AGC_FENOTCHFILT0_FENOTCHRATTNEN1_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT0   */
#define AGC_FENOTCHFILT0_FENOTCHEN1                    (0x1UL << 13)                                     /**< FE notch enable for index 1                 */
#define _AGC_FENOTCHFILT0_FENOTCHEN1_SHIFT             13                                                /**< Shift value for AGC_FENOTCHEN1              */
#define _AGC_FENOTCHFILT0_FENOTCHEN1_MASK              0x2000UL                                          /**< Bit mask for AGC_FENOTCHEN1                 */
#define _AGC_FENOTCHFILT0_FENOTCHEN1_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT0           */
#define AGC_FENOTCHFILT0_FENOTCHEN1_DEFAULT            (_AGC_FENOTCHFILT0_FENOTCHEN1_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT0   */
#define _AGC_FENOTCHFILT0_FENOTCHATTNSEL2_SHIFT        16                                                /**< Shift value for AGC_FENOTCHATTNSEL2         */
#define _AGC_FENOTCHFILT0_FENOTCHATTNSEL2_MASK         0xF0000UL                                         /**< Bit mask for AGC_FENOTCHATTNSEL2            */
#define _AGC_FENOTCHFILT0_FENOTCHATTNSEL2_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT0           */
#define AGC_FENOTCHFILT0_FENOTCHATTNSEL2_DEFAULT       (_AGC_FENOTCHFILT0_FENOTCHATTNSEL2_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT0   */
#define _AGC_FENOTCHFILT0_FENOTCHCAPCRSE2_SHIFT        20                                                /**< Shift value for AGC_FENOTCHCAPCRSE2         */
#define _AGC_FENOTCHFILT0_FENOTCHCAPCRSE2_MASK         0xF00000UL                                        /**< Bit mask for AGC_FENOTCHCAPCRSE2            */
#define _AGC_FENOTCHFILT0_FENOTCHCAPCRSE2_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT0           */
#define AGC_FENOTCHFILT0_FENOTCHCAPCRSE2_DEFAULT       (_AGC_FENOTCHFILT0_FENOTCHCAPCRSE2_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT0   */
#define _AGC_FENOTCHFILT0_FENOTCHCAPFINE2_SHIFT        24                                                /**< Shift value for AGC_FENOTCHCAPFINE2         */
#define _AGC_FENOTCHFILT0_FENOTCHCAPFINE2_MASK         0xF000000UL                                       /**< Bit mask for AGC_FENOTCHCAPFINE2            */
#define _AGC_FENOTCHFILT0_FENOTCHCAPFINE2_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT0           */
#define AGC_FENOTCHFILT0_FENOTCHCAPFINE2_DEFAULT       (_AGC_FENOTCHFILT0_FENOTCHCAPFINE2_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT0   */
#define AGC_FENOTCHFILT0_FENOTCHRATTNEN2               (0x1UL << 28)                                     /**< FE notch rattn enable for index 2           */
#define _AGC_FENOTCHFILT0_FENOTCHRATTNEN2_SHIFT        28                                                /**< Shift value for AGC_FENOTCHRATTNEN2         */
#define _AGC_FENOTCHFILT0_FENOTCHRATTNEN2_MASK         0x10000000UL                                      /**< Bit mask for AGC_FENOTCHRATTNEN2            */
#define _AGC_FENOTCHFILT0_FENOTCHRATTNEN2_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT0           */
#define AGC_FENOTCHFILT0_FENOTCHRATTNEN2_DEFAULT       (_AGC_FENOTCHFILT0_FENOTCHRATTNEN2_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT0   */
#define AGC_FENOTCHFILT0_FENOTCHEN2                    (0x1UL << 29)                                     /**< FE notch enable for index 2                 */
#define _AGC_FENOTCHFILT0_FENOTCHEN2_SHIFT             29                                                /**< Shift value for AGC_FENOTCHEN2              */
#define _AGC_FENOTCHFILT0_FENOTCHEN2_MASK              0x20000000UL                                      /**< Bit mask for AGC_FENOTCHEN2                 */
#define _AGC_FENOTCHFILT0_FENOTCHEN2_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT0           */
#define AGC_FENOTCHFILT0_FENOTCHEN2_DEFAULT            (_AGC_FENOTCHFILT0_FENOTCHEN2_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT0   */

/* Bit fields for AGC FENOTCHFILT1 */
#define _AGC_FENOTCHFILT1_RESETVALUE                   0x00000000UL                                      /**< Default value for AGC_FENOTCHFILT1          */
#define _AGC_FENOTCHFILT1_MASK                         0x3FFF3FFFUL                                      /**< Mask for AGC_FENOTCHFILT1                   */
#define _AGC_FENOTCHFILT1_FENOTCHATTNSEL3_SHIFT        0                                                 /**< Shift value for AGC_FENOTCHATTNSEL3         */
#define _AGC_FENOTCHFILT1_FENOTCHATTNSEL3_MASK         0xFUL                                             /**< Bit mask for AGC_FENOTCHATTNSEL3            */
#define _AGC_FENOTCHFILT1_FENOTCHATTNSEL3_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT1           */
#define AGC_FENOTCHFILT1_FENOTCHATTNSEL3_DEFAULT       (_AGC_FENOTCHFILT1_FENOTCHATTNSEL3_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT1   */
#define _AGC_FENOTCHFILT1_FENOTCHCAPCRSE3_SHIFT        4                                                 /**< Shift value for AGC_FENOTCHCAPCRSE3         */
#define _AGC_FENOTCHFILT1_FENOTCHCAPCRSE3_MASK         0xF0UL                                            /**< Bit mask for AGC_FENOTCHCAPCRSE3            */
#define _AGC_FENOTCHFILT1_FENOTCHCAPCRSE3_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT1           */
#define AGC_FENOTCHFILT1_FENOTCHCAPCRSE3_DEFAULT       (_AGC_FENOTCHFILT1_FENOTCHCAPCRSE3_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT1   */
#define _AGC_FENOTCHFILT1_FENOTCHCAPFINE3_SHIFT        8                                                 /**< Shift value for AGC_FENOTCHCAPFINE3         */
#define _AGC_FENOTCHFILT1_FENOTCHCAPFINE3_MASK         0xF00UL                                           /**< Bit mask for AGC_FENOTCHCAPFINE3            */
#define _AGC_FENOTCHFILT1_FENOTCHCAPFINE3_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT1           */
#define AGC_FENOTCHFILT1_FENOTCHCAPFINE3_DEFAULT       (_AGC_FENOTCHFILT1_FENOTCHCAPFINE3_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT1   */
#define AGC_FENOTCHFILT1_FENOTCHRATTNEN3               (0x1UL << 12)                                     /**< FE notch rattn enable for index 3           */
#define _AGC_FENOTCHFILT1_FENOTCHRATTNEN3_SHIFT        12                                                /**< Shift value for AGC_FENOTCHRATTNEN3         */
#define _AGC_FENOTCHFILT1_FENOTCHRATTNEN3_MASK         0x1000UL                                          /**< Bit mask for AGC_FENOTCHRATTNEN3            */
#define _AGC_FENOTCHFILT1_FENOTCHRATTNEN3_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT1           */
#define AGC_FENOTCHFILT1_FENOTCHRATTNEN3_DEFAULT       (_AGC_FENOTCHFILT1_FENOTCHRATTNEN3_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT1   */
#define AGC_FENOTCHFILT1_FENOTCHEN3                    (0x1UL << 13)                                     /**< FE notch enable for index 3                 */
#define _AGC_FENOTCHFILT1_FENOTCHEN3_SHIFT             13                                                /**< Shift value for AGC_FENOTCHEN3              */
#define _AGC_FENOTCHFILT1_FENOTCHEN3_MASK              0x2000UL                                          /**< Bit mask for AGC_FENOTCHEN3                 */
#define _AGC_FENOTCHFILT1_FENOTCHEN3_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT1           */
#define AGC_FENOTCHFILT1_FENOTCHEN3_DEFAULT            (_AGC_FENOTCHFILT1_FENOTCHEN3_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT1   */
#define _AGC_FENOTCHFILT1_FENOTCHATTNSEL4_SHIFT        16                                                /**< Shift value for AGC_FENOTCHATTNSEL4         */
#define _AGC_FENOTCHFILT1_FENOTCHATTNSEL4_MASK         0xF0000UL                                         /**< Bit mask for AGC_FENOTCHATTNSEL4            */
#define _AGC_FENOTCHFILT1_FENOTCHATTNSEL4_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT1           */
#define AGC_FENOTCHFILT1_FENOTCHATTNSEL4_DEFAULT       (_AGC_FENOTCHFILT1_FENOTCHATTNSEL4_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT1   */
#define _AGC_FENOTCHFILT1_FENOTCHCAPCRSE4_SHIFT        20                                                /**< Shift value for AGC_FENOTCHCAPCRSE4         */
#define _AGC_FENOTCHFILT1_FENOTCHCAPCRSE4_MASK         0xF00000UL                                        /**< Bit mask for AGC_FENOTCHCAPCRSE4            */
#define _AGC_FENOTCHFILT1_FENOTCHCAPCRSE4_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT1           */
#define AGC_FENOTCHFILT1_FENOTCHCAPCRSE4_DEFAULT       (_AGC_FENOTCHFILT1_FENOTCHCAPCRSE4_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT1   */
#define _AGC_FENOTCHFILT1_FENOTCHCAPFINE4_SHIFT        24                                                /**< Shift value for AGC_FENOTCHCAPFINE4         */
#define _AGC_FENOTCHFILT1_FENOTCHCAPFINE4_MASK         0xF000000UL                                       /**< Bit mask for AGC_FENOTCHCAPFINE4            */
#define _AGC_FENOTCHFILT1_FENOTCHCAPFINE4_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT1           */
#define AGC_FENOTCHFILT1_FENOTCHCAPFINE4_DEFAULT       (_AGC_FENOTCHFILT1_FENOTCHCAPFINE4_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT1   */
#define AGC_FENOTCHFILT1_FENOTCHRATTNEN4               (0x1UL << 28)                                     /**< FE notch rattn enable for index 4           */
#define _AGC_FENOTCHFILT1_FENOTCHRATTNEN4_SHIFT        28                                                /**< Shift value for AGC_FENOTCHRATTNEN4         */
#define _AGC_FENOTCHFILT1_FENOTCHRATTNEN4_MASK         0x10000000UL                                      /**< Bit mask for AGC_FENOTCHRATTNEN4            */
#define _AGC_FENOTCHFILT1_FENOTCHRATTNEN4_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT1           */
#define AGC_FENOTCHFILT1_FENOTCHRATTNEN4_DEFAULT       (_AGC_FENOTCHFILT1_FENOTCHRATTNEN4_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT1   */
#define AGC_FENOTCHFILT1_FENOTCHEN4                    (0x1UL << 29)                                     /**< FE notch enable for index 4                 */
#define _AGC_FENOTCHFILT1_FENOTCHEN4_SHIFT             29                                                /**< Shift value for AGC_FENOTCHEN4              */
#define _AGC_FENOTCHFILT1_FENOTCHEN4_MASK              0x20000000UL                                      /**< Bit mask for AGC_FENOTCHEN4                 */
#define _AGC_FENOTCHFILT1_FENOTCHEN4_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT1           */
#define AGC_FENOTCHFILT1_FENOTCHEN4_DEFAULT            (_AGC_FENOTCHFILT1_FENOTCHEN4_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT1   */

/* Bit fields for AGC FENOTCHFILT2 */
#define _AGC_FENOTCHFILT2_RESETVALUE                   0x00000000UL                                      /**< Default value for AGC_FENOTCHFILT2          */
#define _AGC_FENOTCHFILT2_MASK                         0x3FFF3FFFUL                                      /**< Mask for AGC_FENOTCHFILT2                   */
#define _AGC_FENOTCHFILT2_FENOTCHATTNSEL5_SHIFT        0                                                 /**< Shift value for AGC_FENOTCHATTNSEL5         */
#define _AGC_FENOTCHFILT2_FENOTCHATTNSEL5_MASK         0xFUL                                             /**< Bit mask for AGC_FENOTCHATTNSEL5            */
#define _AGC_FENOTCHFILT2_FENOTCHATTNSEL5_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT2           */
#define AGC_FENOTCHFILT2_FENOTCHATTNSEL5_DEFAULT       (_AGC_FENOTCHFILT2_FENOTCHATTNSEL5_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT2   */
#define _AGC_FENOTCHFILT2_FENOTCHCAPCRSE5_SHIFT        4                                                 /**< Shift value for AGC_FENOTCHCAPCRSE5         */
#define _AGC_FENOTCHFILT2_FENOTCHCAPCRSE5_MASK         0xF0UL                                            /**< Bit mask for AGC_FENOTCHCAPCRSE5            */
#define _AGC_FENOTCHFILT2_FENOTCHCAPCRSE5_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT2           */
#define AGC_FENOTCHFILT2_FENOTCHCAPCRSE5_DEFAULT       (_AGC_FENOTCHFILT2_FENOTCHCAPCRSE5_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT2   */
#define _AGC_FENOTCHFILT2_FENOTCHCAPFINE5_SHIFT        8                                                 /**< Shift value for AGC_FENOTCHCAPFINE5         */
#define _AGC_FENOTCHFILT2_FENOTCHCAPFINE5_MASK         0xF00UL                                           /**< Bit mask for AGC_FENOTCHCAPFINE5            */
#define _AGC_FENOTCHFILT2_FENOTCHCAPFINE5_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT2           */
#define AGC_FENOTCHFILT2_FENOTCHCAPFINE5_DEFAULT       (_AGC_FENOTCHFILT2_FENOTCHCAPFINE5_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT2   */
#define AGC_FENOTCHFILT2_FENOTCHRATTNEN5               (0x1UL << 12)                                     /**< FE notch rattn enable for index 5           */
#define _AGC_FENOTCHFILT2_FENOTCHRATTNEN5_SHIFT        12                                                /**< Shift value for AGC_FENOTCHRATTNEN5         */
#define _AGC_FENOTCHFILT2_FENOTCHRATTNEN5_MASK         0x1000UL                                          /**< Bit mask for AGC_FENOTCHRATTNEN5            */
#define _AGC_FENOTCHFILT2_FENOTCHRATTNEN5_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT2           */
#define AGC_FENOTCHFILT2_FENOTCHRATTNEN5_DEFAULT       (_AGC_FENOTCHFILT2_FENOTCHRATTNEN5_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT2   */
#define AGC_FENOTCHFILT2_FENOTCHEN5                    (0x1UL << 13)                                     /**< FE notch enable for index 5                 */
#define _AGC_FENOTCHFILT2_FENOTCHEN5_SHIFT             13                                                /**< Shift value for AGC_FENOTCHEN5              */
#define _AGC_FENOTCHFILT2_FENOTCHEN5_MASK              0x2000UL                                          /**< Bit mask for AGC_FENOTCHEN5                 */
#define _AGC_FENOTCHFILT2_FENOTCHEN5_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT2           */
#define AGC_FENOTCHFILT2_FENOTCHEN5_DEFAULT            (_AGC_FENOTCHFILT2_FENOTCHEN5_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT2   */
#define _AGC_FENOTCHFILT2_FENOTCHATTNSEL6_SHIFT        16                                                /**< Shift value for AGC_FENOTCHATTNSEL6         */
#define _AGC_FENOTCHFILT2_FENOTCHATTNSEL6_MASK         0xF0000UL                                         /**< Bit mask for AGC_FENOTCHATTNSEL6            */
#define _AGC_FENOTCHFILT2_FENOTCHATTNSEL6_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT2           */
#define AGC_FENOTCHFILT2_FENOTCHATTNSEL6_DEFAULT       (_AGC_FENOTCHFILT2_FENOTCHATTNSEL6_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT2   */
#define _AGC_FENOTCHFILT2_FENOTCHCAPCRSE6_SHIFT        20                                                /**< Shift value for AGC_FENOTCHCAPCRSE6         */
#define _AGC_FENOTCHFILT2_FENOTCHCAPCRSE6_MASK         0xF00000UL                                        /**< Bit mask for AGC_FENOTCHCAPCRSE6            */
#define _AGC_FENOTCHFILT2_FENOTCHCAPCRSE6_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT2           */
#define AGC_FENOTCHFILT2_FENOTCHCAPCRSE6_DEFAULT       (_AGC_FENOTCHFILT2_FENOTCHCAPCRSE6_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT2   */
#define _AGC_FENOTCHFILT2_FENOTCHCAPFINE6_SHIFT        24                                                /**< Shift value for AGC_FENOTCHCAPFINE6         */
#define _AGC_FENOTCHFILT2_FENOTCHCAPFINE6_MASK         0xF000000UL                                       /**< Bit mask for AGC_FENOTCHCAPFINE6            */
#define _AGC_FENOTCHFILT2_FENOTCHCAPFINE6_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT2           */
#define AGC_FENOTCHFILT2_FENOTCHCAPFINE6_DEFAULT       (_AGC_FENOTCHFILT2_FENOTCHCAPFINE6_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT2   */
#define AGC_FENOTCHFILT2_FENOTCHRATTNEN6               (0x1UL << 28)                                     /**< FE notch rattn enable for index 6           */
#define _AGC_FENOTCHFILT2_FENOTCHRATTNEN6_SHIFT        28                                                /**< Shift value for AGC_FENOTCHRATTNEN6         */
#define _AGC_FENOTCHFILT2_FENOTCHRATTNEN6_MASK         0x10000000UL                                      /**< Bit mask for AGC_FENOTCHRATTNEN6            */
#define _AGC_FENOTCHFILT2_FENOTCHRATTNEN6_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT2           */
#define AGC_FENOTCHFILT2_FENOTCHRATTNEN6_DEFAULT       (_AGC_FENOTCHFILT2_FENOTCHRATTNEN6_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT2   */
#define AGC_FENOTCHFILT2_FENOTCHEN6                    (0x1UL << 29)                                     /**< FE notch enable for index 6                 */
#define _AGC_FENOTCHFILT2_FENOTCHEN6_SHIFT             29                                                /**< Shift value for AGC_FENOTCHEN6              */
#define _AGC_FENOTCHFILT2_FENOTCHEN6_MASK              0x20000000UL                                      /**< Bit mask for AGC_FENOTCHEN6                 */
#define _AGC_FENOTCHFILT2_FENOTCHEN6_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT2           */
#define AGC_FENOTCHFILT2_FENOTCHEN6_DEFAULT            (_AGC_FENOTCHFILT2_FENOTCHEN6_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT2   */

/* Bit fields for AGC FENOTCHFILT3 */
#define _AGC_FENOTCHFILT3_RESETVALUE                   0x00000000UL                                      /**< Default value for AGC_FENOTCHFILT3          */
#define _AGC_FENOTCHFILT3_MASK                         0x3FFF3FFFUL                                      /**< Mask for AGC_FENOTCHFILT3                   */
#define _AGC_FENOTCHFILT3_FENOTCHATTNSEL7_SHIFT        0                                                 /**< Shift value for AGC_FENOTCHATTNSEL7         */
#define _AGC_FENOTCHFILT3_FENOTCHATTNSEL7_MASK         0xFUL                                             /**< Bit mask for AGC_FENOTCHATTNSEL7            */
#define _AGC_FENOTCHFILT3_FENOTCHATTNSEL7_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT3           */
#define AGC_FENOTCHFILT3_FENOTCHATTNSEL7_DEFAULT       (_AGC_FENOTCHFILT3_FENOTCHATTNSEL7_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT3   */
#define _AGC_FENOTCHFILT3_FENOTCHCAPCRSE7_SHIFT        4                                                 /**< Shift value for AGC_FENOTCHCAPCRSE7         */
#define _AGC_FENOTCHFILT3_FENOTCHCAPCRSE7_MASK         0xF0UL                                            /**< Bit mask for AGC_FENOTCHCAPCRSE7            */
#define _AGC_FENOTCHFILT3_FENOTCHCAPCRSE7_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT3           */
#define AGC_FENOTCHFILT3_FENOTCHCAPCRSE7_DEFAULT       (_AGC_FENOTCHFILT3_FENOTCHCAPCRSE7_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT3   */
#define _AGC_FENOTCHFILT3_FENOTCHCAPFINE7_SHIFT        8                                                 /**< Shift value for AGC_FENOTCHCAPFINE7         */
#define _AGC_FENOTCHFILT3_FENOTCHCAPFINE7_MASK         0xF00UL                                           /**< Bit mask for AGC_FENOTCHCAPFINE7            */
#define _AGC_FENOTCHFILT3_FENOTCHCAPFINE7_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT3           */
#define AGC_FENOTCHFILT3_FENOTCHCAPFINE7_DEFAULT       (_AGC_FENOTCHFILT3_FENOTCHCAPFINE7_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT3   */
#define AGC_FENOTCHFILT3_FENOTCHRATTNEN7               (0x1UL << 12)                                     /**< FE notch rattn enable for index 7           */
#define _AGC_FENOTCHFILT3_FENOTCHRATTNEN7_SHIFT        12                                                /**< Shift value for AGC_FENOTCHRATTNEN7         */
#define _AGC_FENOTCHFILT3_FENOTCHRATTNEN7_MASK         0x1000UL                                          /**< Bit mask for AGC_FENOTCHRATTNEN7            */
#define _AGC_FENOTCHFILT3_FENOTCHRATTNEN7_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT3           */
#define AGC_FENOTCHFILT3_FENOTCHRATTNEN7_DEFAULT       (_AGC_FENOTCHFILT3_FENOTCHRATTNEN7_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT3   */
#define AGC_FENOTCHFILT3_FENOTCHEN7                    (0x1UL << 13)                                     /**< FE notch enable for index 7                 */
#define _AGC_FENOTCHFILT3_FENOTCHEN7_SHIFT             13                                                /**< Shift value for AGC_FENOTCHEN7              */
#define _AGC_FENOTCHFILT3_FENOTCHEN7_MASK              0x2000UL                                          /**< Bit mask for AGC_FENOTCHEN7                 */
#define _AGC_FENOTCHFILT3_FENOTCHEN7_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT3           */
#define AGC_FENOTCHFILT3_FENOTCHEN7_DEFAULT            (_AGC_FENOTCHFILT3_FENOTCHEN7_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT3   */
#define _AGC_FENOTCHFILT3_FENOTCHATTNSEL8_SHIFT        16                                                /**< Shift value for AGC_FENOTCHATTNSEL8         */
#define _AGC_FENOTCHFILT3_FENOTCHATTNSEL8_MASK         0xF0000UL                                         /**< Bit mask for AGC_FENOTCHATTNSEL8            */
#define _AGC_FENOTCHFILT3_FENOTCHATTNSEL8_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT3           */
#define AGC_FENOTCHFILT3_FENOTCHATTNSEL8_DEFAULT       (_AGC_FENOTCHFILT3_FENOTCHATTNSEL8_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT3   */
#define _AGC_FENOTCHFILT3_FENOTCHCAPCRSE8_SHIFT        20                                                /**< Shift value for AGC_FENOTCHCAPCRSE8         */
#define _AGC_FENOTCHFILT3_FENOTCHCAPCRSE8_MASK         0xF00000UL                                        /**< Bit mask for AGC_FENOTCHCAPCRSE8            */
#define _AGC_FENOTCHFILT3_FENOTCHCAPCRSE8_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT3           */
#define AGC_FENOTCHFILT3_FENOTCHCAPCRSE8_DEFAULT       (_AGC_FENOTCHFILT3_FENOTCHCAPCRSE8_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT3   */
#define _AGC_FENOTCHFILT3_FENOTCHCAPFINE8_SHIFT        24                                                /**< Shift value for AGC_FENOTCHCAPFINE8         */
#define _AGC_FENOTCHFILT3_FENOTCHCAPFINE8_MASK         0xF000000UL                                       /**< Bit mask for AGC_FENOTCHCAPFINE8            */
#define _AGC_FENOTCHFILT3_FENOTCHCAPFINE8_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT3           */
#define AGC_FENOTCHFILT3_FENOTCHCAPFINE8_DEFAULT       (_AGC_FENOTCHFILT3_FENOTCHCAPFINE8_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT3   */
#define AGC_FENOTCHFILT3_FENOTCHRATTNEN8               (0x1UL << 28)                                     /**< FE notch rattn enable for index 8           */
#define _AGC_FENOTCHFILT3_FENOTCHRATTNEN8_SHIFT        28                                                /**< Shift value for AGC_FENOTCHRATTNEN8         */
#define _AGC_FENOTCHFILT3_FENOTCHRATTNEN8_MASK         0x10000000UL                                      /**< Bit mask for AGC_FENOTCHRATTNEN8            */
#define _AGC_FENOTCHFILT3_FENOTCHRATTNEN8_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT3           */
#define AGC_FENOTCHFILT3_FENOTCHRATTNEN8_DEFAULT       (_AGC_FENOTCHFILT3_FENOTCHRATTNEN8_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT3   */
#define AGC_FENOTCHFILT3_FENOTCHEN8                    (0x1UL << 29)                                     /**< FE notch enable for index 8                 */
#define _AGC_FENOTCHFILT3_FENOTCHEN8_SHIFT             29                                                /**< Shift value for AGC_FENOTCHEN8              */
#define _AGC_FENOTCHFILT3_FENOTCHEN8_MASK              0x20000000UL                                      /**< Bit mask for AGC_FENOTCHEN8                 */
#define _AGC_FENOTCHFILT3_FENOTCHEN8_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for AGC_FENOTCHFILT3           */
#define AGC_FENOTCHFILT3_FENOTCHEN8_DEFAULT            (_AGC_FENOTCHFILT3_FENOTCHEN8_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT3   */

/* Bit fields for AGC FENOTCHFILT4 */
#define _AGC_FENOTCHFILT4_RESETVALUE                   0x00000000UL                                       /**< Default value for AGC_FENOTCHFILT4          */
#define _AGC_FENOTCHFILT4_MASK                         0x3FFF3FFFUL                                       /**< Mask for AGC_FENOTCHFILT4                   */
#define _AGC_FENOTCHFILT4_FENOTCHATTNSEL9_SHIFT        0                                                  /**< Shift value for AGC_FENOTCHATTNSEL9         */
#define _AGC_FENOTCHFILT4_FENOTCHATTNSEL9_MASK         0xFUL                                              /**< Bit mask for AGC_FENOTCHATTNSEL9            */
#define _AGC_FENOTCHFILT4_FENOTCHATTNSEL9_DEFAULT      0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT4           */
#define AGC_FENOTCHFILT4_FENOTCHATTNSEL9_DEFAULT       (_AGC_FENOTCHFILT4_FENOTCHATTNSEL9_DEFAULT << 0)   /**< Shifted mode DEFAULT for AGC_FENOTCHFILT4   */
#define _AGC_FENOTCHFILT4_FENOTCHCAPCRSE9_SHIFT        4                                                  /**< Shift value for AGC_FENOTCHCAPCRSE9         */
#define _AGC_FENOTCHFILT4_FENOTCHCAPCRSE9_MASK         0xF0UL                                             /**< Bit mask for AGC_FENOTCHCAPCRSE9            */
#define _AGC_FENOTCHFILT4_FENOTCHCAPCRSE9_DEFAULT      0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT4           */
#define AGC_FENOTCHFILT4_FENOTCHCAPCRSE9_DEFAULT       (_AGC_FENOTCHFILT4_FENOTCHCAPCRSE9_DEFAULT << 4)   /**< Shifted mode DEFAULT for AGC_FENOTCHFILT4   */
#define _AGC_FENOTCHFILT4_FENOTCHCAPFINE9_SHIFT        8                                                  /**< Shift value for AGC_FENOTCHCAPFINE9         */
#define _AGC_FENOTCHFILT4_FENOTCHCAPFINE9_MASK         0xF00UL                                            /**< Bit mask for AGC_FENOTCHCAPFINE9            */
#define _AGC_FENOTCHFILT4_FENOTCHCAPFINE9_DEFAULT      0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT4           */
#define AGC_FENOTCHFILT4_FENOTCHCAPFINE9_DEFAULT       (_AGC_FENOTCHFILT4_FENOTCHCAPFINE9_DEFAULT << 8)   /**< Shifted mode DEFAULT for AGC_FENOTCHFILT4   */
#define AGC_FENOTCHFILT4_FENOTCHRATTNEN9               (0x1UL << 12)                                      /**< FE notch rattn enable for index 9           */
#define _AGC_FENOTCHFILT4_FENOTCHRATTNEN9_SHIFT        12                                                 /**< Shift value for AGC_FENOTCHRATTNEN9         */
#define _AGC_FENOTCHFILT4_FENOTCHRATTNEN9_MASK         0x1000UL                                           /**< Bit mask for AGC_FENOTCHRATTNEN9            */
#define _AGC_FENOTCHFILT4_FENOTCHRATTNEN9_DEFAULT      0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT4           */
#define AGC_FENOTCHFILT4_FENOTCHRATTNEN9_DEFAULT       (_AGC_FENOTCHFILT4_FENOTCHRATTNEN9_DEFAULT << 12)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT4   */
#define AGC_FENOTCHFILT4_FENOTCHEN9                    (0x1UL << 13)                                      /**< FE notch enable for index 9                 */
#define _AGC_FENOTCHFILT4_FENOTCHEN9_SHIFT             13                                                 /**< Shift value for AGC_FENOTCHEN9              */
#define _AGC_FENOTCHFILT4_FENOTCHEN9_MASK              0x2000UL                                           /**< Bit mask for AGC_FENOTCHEN9                 */
#define _AGC_FENOTCHFILT4_FENOTCHEN9_DEFAULT           0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT4           */
#define AGC_FENOTCHFILT4_FENOTCHEN9_DEFAULT            (_AGC_FENOTCHFILT4_FENOTCHEN9_DEFAULT << 13)       /**< Shifted mode DEFAULT for AGC_FENOTCHFILT4   */
#define _AGC_FENOTCHFILT4_FENOTCHATTNSEL10_SHIFT       16                                                 /**< Shift value for AGC_FENOTCHATTNSEL10        */
#define _AGC_FENOTCHFILT4_FENOTCHATTNSEL10_MASK        0xF0000UL                                          /**< Bit mask for AGC_FENOTCHATTNSEL10           */
#define _AGC_FENOTCHFILT4_FENOTCHATTNSEL10_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT4           */
#define AGC_FENOTCHFILT4_FENOTCHATTNSEL10_DEFAULT      (_AGC_FENOTCHFILT4_FENOTCHATTNSEL10_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT4   */
#define _AGC_FENOTCHFILT4_FENOTCHCAPCRSE10_SHIFT       20                                                 /**< Shift value for AGC_FENOTCHCAPCRSE10        */
#define _AGC_FENOTCHFILT4_FENOTCHCAPCRSE10_MASK        0xF00000UL                                         /**< Bit mask for AGC_FENOTCHCAPCRSE10           */
#define _AGC_FENOTCHFILT4_FENOTCHCAPCRSE10_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT4           */
#define AGC_FENOTCHFILT4_FENOTCHCAPCRSE10_DEFAULT      (_AGC_FENOTCHFILT4_FENOTCHCAPCRSE10_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT4   */
#define _AGC_FENOTCHFILT4_FENOTCHCAPFINE10_SHIFT       24                                                 /**< Shift value for AGC_FENOTCHCAPFINE10        */
#define _AGC_FENOTCHFILT4_FENOTCHCAPFINE10_MASK        0xF000000UL                                        /**< Bit mask for AGC_FENOTCHCAPFINE10           */
#define _AGC_FENOTCHFILT4_FENOTCHCAPFINE10_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT4           */
#define AGC_FENOTCHFILT4_FENOTCHCAPFINE10_DEFAULT      (_AGC_FENOTCHFILT4_FENOTCHCAPFINE10_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT4   */
#define AGC_FENOTCHFILT4_FENOTCHRATTNEN10              (0x1UL << 28)                                      /**< FE notch rattn enable for index 10          */
#define _AGC_FENOTCHFILT4_FENOTCHRATTNEN10_SHIFT       28                                                 /**< Shift value for AGC_FENOTCHRATTNEN10        */
#define _AGC_FENOTCHFILT4_FENOTCHRATTNEN10_MASK        0x10000000UL                                       /**< Bit mask for AGC_FENOTCHRATTNEN10           */
#define _AGC_FENOTCHFILT4_FENOTCHRATTNEN10_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT4           */
#define AGC_FENOTCHFILT4_FENOTCHRATTNEN10_DEFAULT      (_AGC_FENOTCHFILT4_FENOTCHRATTNEN10_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT4   */
#define AGC_FENOTCHFILT4_FENOTCHEN10                   (0x1UL << 29)                                      /**< FE notch enable for index 10                */
#define _AGC_FENOTCHFILT4_FENOTCHEN10_SHIFT            29                                                 /**< Shift value for AGC_FENOTCHEN10             */
#define _AGC_FENOTCHFILT4_FENOTCHEN10_MASK             0x20000000UL                                       /**< Bit mask for AGC_FENOTCHEN10                */
#define _AGC_FENOTCHFILT4_FENOTCHEN10_DEFAULT          0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT4           */
#define AGC_FENOTCHFILT4_FENOTCHEN10_DEFAULT           (_AGC_FENOTCHFILT4_FENOTCHEN10_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT4   */

/* Bit fields for AGC FENOTCHFILT5 */
#define _AGC_FENOTCHFILT5_RESETVALUE                   0x00000000UL                                       /**< Default value for AGC_FENOTCHFILT5          */
#define _AGC_FENOTCHFILT5_MASK                         0x3FFF3FFFUL                                       /**< Mask for AGC_FENOTCHFILT5                   */
#define _AGC_FENOTCHFILT5_FENOTCHATTNSEL11_SHIFT       0                                                  /**< Shift value for AGC_FENOTCHATTNSEL11        */
#define _AGC_FENOTCHFILT5_FENOTCHATTNSEL11_MASK        0xFUL                                              /**< Bit mask for AGC_FENOTCHATTNSEL11           */
#define _AGC_FENOTCHFILT5_FENOTCHATTNSEL11_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT5           */
#define AGC_FENOTCHFILT5_FENOTCHATTNSEL11_DEFAULT      (_AGC_FENOTCHFILT5_FENOTCHATTNSEL11_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT5   */
#define _AGC_FENOTCHFILT5_FENOTCHCAPCRSE11_SHIFT       4                                                  /**< Shift value for AGC_FENOTCHCAPCRSE11        */
#define _AGC_FENOTCHFILT5_FENOTCHCAPCRSE11_MASK        0xF0UL                                             /**< Bit mask for AGC_FENOTCHCAPCRSE11           */
#define _AGC_FENOTCHFILT5_FENOTCHCAPCRSE11_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT5           */
#define AGC_FENOTCHFILT5_FENOTCHCAPCRSE11_DEFAULT      (_AGC_FENOTCHFILT5_FENOTCHCAPCRSE11_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT5   */
#define _AGC_FENOTCHFILT5_FENOTCHCAPFINE11_SHIFT       8                                                  /**< Shift value for AGC_FENOTCHCAPFINE11        */
#define _AGC_FENOTCHFILT5_FENOTCHCAPFINE11_MASK        0xF00UL                                            /**< Bit mask for AGC_FENOTCHCAPFINE11           */
#define _AGC_FENOTCHFILT5_FENOTCHCAPFINE11_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT5           */
#define AGC_FENOTCHFILT5_FENOTCHCAPFINE11_DEFAULT      (_AGC_FENOTCHFILT5_FENOTCHCAPFINE11_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT5   */
#define AGC_FENOTCHFILT5_FENOTCHRATTNEN11              (0x1UL << 12)                                      /**< FE notch rattn enable for index 11          */
#define _AGC_FENOTCHFILT5_FENOTCHRATTNEN11_SHIFT       12                                                 /**< Shift value for AGC_FENOTCHRATTNEN11        */
#define _AGC_FENOTCHFILT5_FENOTCHRATTNEN11_MASK        0x1000UL                                           /**< Bit mask for AGC_FENOTCHRATTNEN11           */
#define _AGC_FENOTCHFILT5_FENOTCHRATTNEN11_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT5           */
#define AGC_FENOTCHFILT5_FENOTCHRATTNEN11_DEFAULT      (_AGC_FENOTCHFILT5_FENOTCHRATTNEN11_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT5   */
#define AGC_FENOTCHFILT5_FENOTCHEN11                   (0x1UL << 13)                                      /**< FE notch enable for index 11                */
#define _AGC_FENOTCHFILT5_FENOTCHEN11_SHIFT            13                                                 /**< Shift value for AGC_FENOTCHEN11             */
#define _AGC_FENOTCHFILT5_FENOTCHEN11_MASK             0x2000UL                                           /**< Bit mask for AGC_FENOTCHEN11                */
#define _AGC_FENOTCHFILT5_FENOTCHEN11_DEFAULT          0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT5           */
#define AGC_FENOTCHFILT5_FENOTCHEN11_DEFAULT           (_AGC_FENOTCHFILT5_FENOTCHEN11_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT5   */
#define _AGC_FENOTCHFILT5_FENOTCHATTNSEL12_SHIFT       16                                                 /**< Shift value for AGC_FENOTCHATTNSEL12        */
#define _AGC_FENOTCHFILT5_FENOTCHATTNSEL12_MASK        0xF0000UL                                          /**< Bit mask for AGC_FENOTCHATTNSEL12           */
#define _AGC_FENOTCHFILT5_FENOTCHATTNSEL12_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT5           */
#define AGC_FENOTCHFILT5_FENOTCHATTNSEL12_DEFAULT      (_AGC_FENOTCHFILT5_FENOTCHATTNSEL12_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT5   */
#define _AGC_FENOTCHFILT5_FENOTCHCAPCRSE12_SHIFT       20                                                 /**< Shift value for AGC_FENOTCHCAPCRSE12        */
#define _AGC_FENOTCHFILT5_FENOTCHCAPCRSE12_MASK        0xF00000UL                                         /**< Bit mask for AGC_FENOTCHCAPCRSE12           */
#define _AGC_FENOTCHFILT5_FENOTCHCAPCRSE12_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT5           */
#define AGC_FENOTCHFILT5_FENOTCHCAPCRSE12_DEFAULT      (_AGC_FENOTCHFILT5_FENOTCHCAPCRSE12_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT5   */
#define _AGC_FENOTCHFILT5_FENOTCHCAPFINE12_SHIFT       24                                                 /**< Shift value for AGC_FENOTCHCAPFINE12        */
#define _AGC_FENOTCHFILT5_FENOTCHCAPFINE12_MASK        0xF000000UL                                        /**< Bit mask for AGC_FENOTCHCAPFINE12           */
#define _AGC_FENOTCHFILT5_FENOTCHCAPFINE12_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT5           */
#define AGC_FENOTCHFILT5_FENOTCHCAPFINE12_DEFAULT      (_AGC_FENOTCHFILT5_FENOTCHCAPFINE12_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT5   */
#define AGC_FENOTCHFILT5_FENOTCHRATTNEN12              (0x1UL << 28)                                      /**< FE notch rattn enable for index 12          */
#define _AGC_FENOTCHFILT5_FENOTCHRATTNEN12_SHIFT       28                                                 /**< Shift value for AGC_FENOTCHRATTNEN12        */
#define _AGC_FENOTCHFILT5_FENOTCHRATTNEN12_MASK        0x10000000UL                                       /**< Bit mask for AGC_FENOTCHRATTNEN12           */
#define _AGC_FENOTCHFILT5_FENOTCHRATTNEN12_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT5           */
#define AGC_FENOTCHFILT5_FENOTCHRATTNEN12_DEFAULT      (_AGC_FENOTCHFILT5_FENOTCHRATTNEN12_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT5   */
#define AGC_FENOTCHFILT5_FENOTCHEN12                   (0x1UL << 29)                                      /**< FE notch enable for index 12                */
#define _AGC_FENOTCHFILT5_FENOTCHEN12_SHIFT            29                                                 /**< Shift value for AGC_FENOTCHEN12             */
#define _AGC_FENOTCHFILT5_FENOTCHEN12_MASK             0x20000000UL                                       /**< Bit mask for AGC_FENOTCHEN12                */
#define _AGC_FENOTCHFILT5_FENOTCHEN12_DEFAULT          0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT5           */
#define AGC_FENOTCHFILT5_FENOTCHEN12_DEFAULT           (_AGC_FENOTCHFILT5_FENOTCHEN12_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT5   */

/* Bit fields for AGC FENOTCHFILT6 */
#define _AGC_FENOTCHFILT6_RESETVALUE                   0x00000000UL                                       /**< Default value for AGC_FENOTCHFILT6          */
#define _AGC_FENOTCHFILT6_MASK                         0x3FFF3FFFUL                                       /**< Mask for AGC_FENOTCHFILT6                   */
#define _AGC_FENOTCHFILT6_FENOTCHATTNSEL13_SHIFT       0                                                  /**< Shift value for AGC_FENOTCHATTNSEL13        */
#define _AGC_FENOTCHFILT6_FENOTCHATTNSEL13_MASK        0xFUL                                              /**< Bit mask for AGC_FENOTCHATTNSEL13           */
#define _AGC_FENOTCHFILT6_FENOTCHATTNSEL13_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT6           */
#define AGC_FENOTCHFILT6_FENOTCHATTNSEL13_DEFAULT      (_AGC_FENOTCHFILT6_FENOTCHATTNSEL13_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT6   */
#define _AGC_FENOTCHFILT6_FENOTCHCAPCRSE13_SHIFT       4                                                  /**< Shift value for AGC_FENOTCHCAPCRSE13        */
#define _AGC_FENOTCHFILT6_FENOTCHCAPCRSE13_MASK        0xF0UL                                             /**< Bit mask for AGC_FENOTCHCAPCRSE13           */
#define _AGC_FENOTCHFILT6_FENOTCHCAPCRSE13_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT6           */
#define AGC_FENOTCHFILT6_FENOTCHCAPCRSE13_DEFAULT      (_AGC_FENOTCHFILT6_FENOTCHCAPCRSE13_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT6   */
#define _AGC_FENOTCHFILT6_FENOTCHCAPFINE13_SHIFT       8                                                  /**< Shift value for AGC_FENOTCHCAPFINE13        */
#define _AGC_FENOTCHFILT6_FENOTCHCAPFINE13_MASK        0xF00UL                                            /**< Bit mask for AGC_FENOTCHCAPFINE13           */
#define _AGC_FENOTCHFILT6_FENOTCHCAPFINE13_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT6           */
#define AGC_FENOTCHFILT6_FENOTCHCAPFINE13_DEFAULT      (_AGC_FENOTCHFILT6_FENOTCHCAPFINE13_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT6   */
#define AGC_FENOTCHFILT6_FENOTCHRATTNEN13              (0x1UL << 12)                                      /**< FE notch rattn enable for index 13          */
#define _AGC_FENOTCHFILT6_FENOTCHRATTNEN13_SHIFT       12                                                 /**< Shift value for AGC_FENOTCHRATTNEN13        */
#define _AGC_FENOTCHFILT6_FENOTCHRATTNEN13_MASK        0x1000UL                                           /**< Bit mask for AGC_FENOTCHRATTNEN13           */
#define _AGC_FENOTCHFILT6_FENOTCHRATTNEN13_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT6           */
#define AGC_FENOTCHFILT6_FENOTCHRATTNEN13_DEFAULT      (_AGC_FENOTCHFILT6_FENOTCHRATTNEN13_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT6   */
#define AGC_FENOTCHFILT6_FENOTCHEN13                   (0x1UL << 13)                                      /**< FE notch enable for index 13                */
#define _AGC_FENOTCHFILT6_FENOTCHEN13_SHIFT            13                                                 /**< Shift value for AGC_FENOTCHEN13             */
#define _AGC_FENOTCHFILT6_FENOTCHEN13_MASK             0x2000UL                                           /**< Bit mask for AGC_FENOTCHEN13                */
#define _AGC_FENOTCHFILT6_FENOTCHEN13_DEFAULT          0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT6           */
#define AGC_FENOTCHFILT6_FENOTCHEN13_DEFAULT           (_AGC_FENOTCHFILT6_FENOTCHEN13_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT6   */
#define _AGC_FENOTCHFILT6_FENOTCHATTNSEL14_SHIFT       16                                                 /**< Shift value for AGC_FENOTCHATTNSEL14        */
#define _AGC_FENOTCHFILT6_FENOTCHATTNSEL14_MASK        0xF0000UL                                          /**< Bit mask for AGC_FENOTCHATTNSEL14           */
#define _AGC_FENOTCHFILT6_FENOTCHATTNSEL14_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT6           */
#define AGC_FENOTCHFILT6_FENOTCHATTNSEL14_DEFAULT      (_AGC_FENOTCHFILT6_FENOTCHATTNSEL14_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT6   */
#define _AGC_FENOTCHFILT6_FENOTCHCAPCRSE14_SHIFT       20                                                 /**< Shift value for AGC_FENOTCHCAPCRSE14        */
#define _AGC_FENOTCHFILT6_FENOTCHCAPCRSE14_MASK        0xF00000UL                                         /**< Bit mask for AGC_FENOTCHCAPCRSE14           */
#define _AGC_FENOTCHFILT6_FENOTCHCAPCRSE14_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT6           */
#define AGC_FENOTCHFILT6_FENOTCHCAPCRSE14_DEFAULT      (_AGC_FENOTCHFILT6_FENOTCHCAPCRSE14_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT6   */
#define _AGC_FENOTCHFILT6_FENOTCHCAPFINE14_SHIFT       24                                                 /**< Shift value for AGC_FENOTCHCAPFINE14        */
#define _AGC_FENOTCHFILT6_FENOTCHCAPFINE14_MASK        0xF000000UL                                        /**< Bit mask for AGC_FENOTCHCAPFINE14           */
#define _AGC_FENOTCHFILT6_FENOTCHCAPFINE14_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT6           */
#define AGC_FENOTCHFILT6_FENOTCHCAPFINE14_DEFAULT      (_AGC_FENOTCHFILT6_FENOTCHCAPFINE14_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT6   */
#define AGC_FENOTCHFILT6_FENOTCHRATTNEN14              (0x1UL << 28)                                      /**< FE notch rattn enable for index 14          */
#define _AGC_FENOTCHFILT6_FENOTCHRATTNEN14_SHIFT       28                                                 /**< Shift value for AGC_FENOTCHRATTNEN14        */
#define _AGC_FENOTCHFILT6_FENOTCHRATTNEN14_MASK        0x10000000UL                                       /**< Bit mask for AGC_FENOTCHRATTNEN14           */
#define _AGC_FENOTCHFILT6_FENOTCHRATTNEN14_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT6           */
#define AGC_FENOTCHFILT6_FENOTCHRATTNEN14_DEFAULT      (_AGC_FENOTCHFILT6_FENOTCHRATTNEN14_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT6   */
#define AGC_FENOTCHFILT6_FENOTCHEN14                   (0x1UL << 29)                                      /**< FE notch enable for index 14                */
#define _AGC_FENOTCHFILT6_FENOTCHEN14_SHIFT            29                                                 /**< Shift value for AGC_FENOTCHEN14             */
#define _AGC_FENOTCHFILT6_FENOTCHEN14_MASK             0x20000000UL                                       /**< Bit mask for AGC_FENOTCHEN14                */
#define _AGC_FENOTCHFILT6_FENOTCHEN14_DEFAULT          0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT6           */
#define AGC_FENOTCHFILT6_FENOTCHEN14_DEFAULT           (_AGC_FENOTCHFILT6_FENOTCHEN14_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT6   */

/* Bit fields for AGC FENOTCHFILT7 */
#define _AGC_FENOTCHFILT7_RESETVALUE                   0x20080000UL                                       /**< Default value for AGC_FENOTCHFILT7          */
#define _AGC_FENOTCHFILT7_MASK                         0x3FFF3FFFUL                                       /**< Mask for AGC_FENOTCHFILT7                   */
#define _AGC_FENOTCHFILT7_FENOTCHATTNSEL15_SHIFT       0                                                  /**< Shift value for AGC_FENOTCHATTNSEL15        */
#define _AGC_FENOTCHFILT7_FENOTCHATTNSEL15_MASK        0xFUL                                              /**< Bit mask for AGC_FENOTCHATTNSEL15           */
#define _AGC_FENOTCHFILT7_FENOTCHATTNSEL15_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT7           */
#define AGC_FENOTCHFILT7_FENOTCHATTNSEL15_DEFAULT      (_AGC_FENOTCHFILT7_FENOTCHATTNSEL15_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT7   */
#define _AGC_FENOTCHFILT7_FENOTCHCAPCRSE15_SHIFT       4                                                  /**< Shift value for AGC_FENOTCHCAPCRSE15        */
#define _AGC_FENOTCHFILT7_FENOTCHCAPCRSE15_MASK        0xF0UL                                             /**< Bit mask for AGC_FENOTCHCAPCRSE15           */
#define _AGC_FENOTCHFILT7_FENOTCHCAPCRSE15_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT7           */
#define AGC_FENOTCHFILT7_FENOTCHCAPCRSE15_DEFAULT      (_AGC_FENOTCHFILT7_FENOTCHCAPCRSE15_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT7   */
#define _AGC_FENOTCHFILT7_FENOTCHCAPFINE15_SHIFT       8                                                  /**< Shift value for AGC_FENOTCHCAPFINE15        */
#define _AGC_FENOTCHFILT7_FENOTCHCAPFINE15_MASK        0xF00UL                                            /**< Bit mask for AGC_FENOTCHCAPFINE15           */
#define _AGC_FENOTCHFILT7_FENOTCHCAPFINE15_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT7           */
#define AGC_FENOTCHFILT7_FENOTCHCAPFINE15_DEFAULT      (_AGC_FENOTCHFILT7_FENOTCHCAPFINE15_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT7   */
#define AGC_FENOTCHFILT7_FENOTCHRATTNEN15              (0x1UL << 12)                                      /**< FE notch rattn enable for index 15          */
#define _AGC_FENOTCHFILT7_FENOTCHRATTNEN15_SHIFT       12                                                 /**< Shift value for AGC_FENOTCHRATTNEN15        */
#define _AGC_FENOTCHFILT7_FENOTCHRATTNEN15_MASK        0x1000UL                                           /**< Bit mask for AGC_FENOTCHRATTNEN15           */
#define _AGC_FENOTCHFILT7_FENOTCHRATTNEN15_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT7           */
#define AGC_FENOTCHFILT7_FENOTCHRATTNEN15_DEFAULT      (_AGC_FENOTCHFILT7_FENOTCHRATTNEN15_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT7   */
#define AGC_FENOTCHFILT7_FENOTCHEN15                   (0x1UL << 13)                                      /**< FE notch enable for index 15                */
#define _AGC_FENOTCHFILT7_FENOTCHEN15_SHIFT            13                                                 /**< Shift value for AGC_FENOTCHEN15             */
#define _AGC_FENOTCHFILT7_FENOTCHEN15_MASK             0x2000UL                                           /**< Bit mask for AGC_FENOTCHEN15                */
#define _AGC_FENOTCHFILT7_FENOTCHEN15_DEFAULT          0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT7           */
#define AGC_FENOTCHFILT7_FENOTCHEN15_DEFAULT           (_AGC_FENOTCHFILT7_FENOTCHEN15_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT7   */
#define _AGC_FENOTCHFILT7_FENOTCHATTNSEL16_SHIFT       16                                                 /**< Shift value for AGC_FENOTCHATTNSEL16        */
#define _AGC_FENOTCHFILT7_FENOTCHATTNSEL16_MASK        0xF0000UL                                          /**< Bit mask for AGC_FENOTCHATTNSEL16           */
#define _AGC_FENOTCHFILT7_FENOTCHATTNSEL16_DEFAULT     0x00000008UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT7           */
#define AGC_FENOTCHFILT7_FENOTCHATTNSEL16_DEFAULT      (_AGC_FENOTCHFILT7_FENOTCHATTNSEL16_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT7   */
#define _AGC_FENOTCHFILT7_FENOTCHCAPCRSE16_SHIFT       20                                                 /**< Shift value for AGC_FENOTCHCAPCRSE16        */
#define _AGC_FENOTCHFILT7_FENOTCHCAPCRSE16_MASK        0xF00000UL                                         /**< Bit mask for AGC_FENOTCHCAPCRSE16           */
#define _AGC_FENOTCHFILT7_FENOTCHCAPCRSE16_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT7           */
#define AGC_FENOTCHFILT7_FENOTCHCAPCRSE16_DEFAULT      (_AGC_FENOTCHFILT7_FENOTCHCAPCRSE16_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT7   */
#define _AGC_FENOTCHFILT7_FENOTCHCAPFINE16_SHIFT       24                                                 /**< Shift value for AGC_FENOTCHCAPFINE16        */
#define _AGC_FENOTCHFILT7_FENOTCHCAPFINE16_MASK        0xF000000UL                                        /**< Bit mask for AGC_FENOTCHCAPFINE16           */
#define _AGC_FENOTCHFILT7_FENOTCHCAPFINE16_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT7           */
#define AGC_FENOTCHFILT7_FENOTCHCAPFINE16_DEFAULT      (_AGC_FENOTCHFILT7_FENOTCHCAPFINE16_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT7   */
#define AGC_FENOTCHFILT7_FENOTCHRATTNEN16              (0x1UL << 28)                                      /**< FE notch rattn enable for index 16          */
#define _AGC_FENOTCHFILT7_FENOTCHRATTNEN16_SHIFT       28                                                 /**< Shift value for AGC_FENOTCHRATTNEN16        */
#define _AGC_FENOTCHFILT7_FENOTCHRATTNEN16_MASK        0x10000000UL                                       /**< Bit mask for AGC_FENOTCHRATTNEN16           */
#define _AGC_FENOTCHFILT7_FENOTCHRATTNEN16_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT7           */
#define AGC_FENOTCHFILT7_FENOTCHRATTNEN16_DEFAULT      (_AGC_FENOTCHFILT7_FENOTCHRATTNEN16_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT7   */
#define AGC_FENOTCHFILT7_FENOTCHEN16                   (0x1UL << 29)                                      /**< FE notch enable for index 16                */
#define _AGC_FENOTCHFILT7_FENOTCHEN16_SHIFT            29                                                 /**< Shift value for AGC_FENOTCHEN16             */
#define _AGC_FENOTCHFILT7_FENOTCHEN16_MASK             0x20000000UL                                       /**< Bit mask for AGC_FENOTCHEN16                */
#define _AGC_FENOTCHFILT7_FENOTCHEN16_DEFAULT          0x00000001UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT7           */
#define AGC_FENOTCHFILT7_FENOTCHEN16_DEFAULT           (_AGC_FENOTCHFILT7_FENOTCHEN16_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT7   */

/* Bit fields for AGC FENOTCHFILT8 */
#define _AGC_FENOTCHFILT8_RESETVALUE                   0x200B200AUL                                       /**< Default value for AGC_FENOTCHFILT8          */
#define _AGC_FENOTCHFILT8_MASK                         0x3FFF3FFFUL                                       /**< Mask for AGC_FENOTCHFILT8                   */
#define _AGC_FENOTCHFILT8_FENOTCHATTNSEL17_SHIFT       0                                                  /**< Shift value for AGC_FENOTCHATTNSEL17        */
#define _AGC_FENOTCHFILT8_FENOTCHATTNSEL17_MASK        0xFUL                                              /**< Bit mask for AGC_FENOTCHATTNSEL17           */
#define _AGC_FENOTCHFILT8_FENOTCHATTNSEL17_DEFAULT     0x0000000AUL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT8           */
#define AGC_FENOTCHFILT8_FENOTCHATTNSEL17_DEFAULT      (_AGC_FENOTCHFILT8_FENOTCHATTNSEL17_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT8   */
#define _AGC_FENOTCHFILT8_FENOTCHCAPCRSE17_SHIFT       4                                                  /**< Shift value for AGC_FENOTCHCAPCRSE17        */
#define _AGC_FENOTCHFILT8_FENOTCHCAPCRSE17_MASK        0xF0UL                                             /**< Bit mask for AGC_FENOTCHCAPCRSE17           */
#define _AGC_FENOTCHFILT8_FENOTCHCAPCRSE17_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT8           */
#define AGC_FENOTCHFILT8_FENOTCHCAPCRSE17_DEFAULT      (_AGC_FENOTCHFILT8_FENOTCHCAPCRSE17_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT8   */
#define _AGC_FENOTCHFILT8_FENOTCHCAPFINE17_SHIFT       8                                                  /**< Shift value for AGC_FENOTCHCAPFINE17        */
#define _AGC_FENOTCHFILT8_FENOTCHCAPFINE17_MASK        0xF00UL                                            /**< Bit mask for AGC_FENOTCHCAPFINE17           */
#define _AGC_FENOTCHFILT8_FENOTCHCAPFINE17_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT8           */
#define AGC_FENOTCHFILT8_FENOTCHCAPFINE17_DEFAULT      (_AGC_FENOTCHFILT8_FENOTCHCAPFINE17_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT8   */
#define AGC_FENOTCHFILT8_FENOTCHRATTNEN17              (0x1UL << 12)                                      /**< FE notch rattn enable for index 17          */
#define _AGC_FENOTCHFILT8_FENOTCHRATTNEN17_SHIFT       12                                                 /**< Shift value for AGC_FENOTCHRATTNEN17        */
#define _AGC_FENOTCHFILT8_FENOTCHRATTNEN17_MASK        0x1000UL                                           /**< Bit mask for AGC_FENOTCHRATTNEN17           */
#define _AGC_FENOTCHFILT8_FENOTCHRATTNEN17_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT8           */
#define AGC_FENOTCHFILT8_FENOTCHRATTNEN17_DEFAULT      (_AGC_FENOTCHFILT8_FENOTCHRATTNEN17_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT8   */
#define AGC_FENOTCHFILT8_FENOTCHEN17                   (0x1UL << 13)                                      /**< FE notch enable for index 17                */
#define _AGC_FENOTCHFILT8_FENOTCHEN17_SHIFT            13                                                 /**< Shift value for AGC_FENOTCHEN17             */
#define _AGC_FENOTCHFILT8_FENOTCHEN17_MASK             0x2000UL                                           /**< Bit mask for AGC_FENOTCHEN17                */
#define _AGC_FENOTCHFILT8_FENOTCHEN17_DEFAULT          0x00000001UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT8           */
#define AGC_FENOTCHFILT8_FENOTCHEN17_DEFAULT           (_AGC_FENOTCHFILT8_FENOTCHEN17_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT8   */
#define _AGC_FENOTCHFILT8_FENOTCHATTNSEL18_SHIFT       16                                                 /**< Shift value for AGC_FENOTCHATTNSEL18        */
#define _AGC_FENOTCHFILT8_FENOTCHATTNSEL18_MASK        0xF0000UL                                          /**< Bit mask for AGC_FENOTCHATTNSEL18           */
#define _AGC_FENOTCHFILT8_FENOTCHATTNSEL18_DEFAULT     0x0000000BUL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT8           */
#define AGC_FENOTCHFILT8_FENOTCHATTNSEL18_DEFAULT      (_AGC_FENOTCHFILT8_FENOTCHATTNSEL18_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT8   */
#define _AGC_FENOTCHFILT8_FENOTCHCAPCRSE18_SHIFT       20                                                 /**< Shift value for AGC_FENOTCHCAPCRSE18        */
#define _AGC_FENOTCHFILT8_FENOTCHCAPCRSE18_MASK        0xF00000UL                                         /**< Bit mask for AGC_FENOTCHCAPCRSE18           */
#define _AGC_FENOTCHFILT8_FENOTCHCAPCRSE18_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT8           */
#define AGC_FENOTCHFILT8_FENOTCHCAPCRSE18_DEFAULT      (_AGC_FENOTCHFILT8_FENOTCHCAPCRSE18_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT8   */
#define _AGC_FENOTCHFILT8_FENOTCHCAPFINE18_SHIFT       24                                                 /**< Shift value for AGC_FENOTCHCAPFINE18        */
#define _AGC_FENOTCHFILT8_FENOTCHCAPFINE18_MASK        0xF000000UL                                        /**< Bit mask for AGC_FENOTCHCAPFINE18           */
#define _AGC_FENOTCHFILT8_FENOTCHCAPFINE18_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT8           */
#define AGC_FENOTCHFILT8_FENOTCHCAPFINE18_DEFAULT      (_AGC_FENOTCHFILT8_FENOTCHCAPFINE18_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT8   */
#define AGC_FENOTCHFILT8_FENOTCHRATTNEN18              (0x1UL << 28)                                      /**< FE notch rattn enable for index 18          */
#define _AGC_FENOTCHFILT8_FENOTCHRATTNEN18_SHIFT       28                                                 /**< Shift value for AGC_FENOTCHRATTNEN18        */
#define _AGC_FENOTCHFILT8_FENOTCHRATTNEN18_MASK        0x10000000UL                                       /**< Bit mask for AGC_FENOTCHRATTNEN18           */
#define _AGC_FENOTCHFILT8_FENOTCHRATTNEN18_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT8           */
#define AGC_FENOTCHFILT8_FENOTCHRATTNEN18_DEFAULT      (_AGC_FENOTCHFILT8_FENOTCHRATTNEN18_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT8   */
#define AGC_FENOTCHFILT8_FENOTCHEN18                   (0x1UL << 29)                                      /**< FE notch enable for index 18                */
#define _AGC_FENOTCHFILT8_FENOTCHEN18_SHIFT            29                                                 /**< Shift value for AGC_FENOTCHEN18             */
#define _AGC_FENOTCHFILT8_FENOTCHEN18_MASK             0x20000000UL                                       /**< Bit mask for AGC_FENOTCHEN18                */
#define _AGC_FENOTCHFILT8_FENOTCHEN18_DEFAULT          0x00000001UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT8           */
#define AGC_FENOTCHFILT8_FENOTCHEN18_DEFAULT           (_AGC_FENOTCHFILT8_FENOTCHEN18_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT8   */

/* Bit fields for AGC FENOTCHFILT9 */
#define _AGC_FENOTCHFILT9_RESETVALUE                   0x200B200BUL                                       /**< Default value for AGC_FENOTCHFILT9          */
#define _AGC_FENOTCHFILT9_MASK                         0x3FFF3FFFUL                                       /**< Mask for AGC_FENOTCHFILT9                   */
#define _AGC_FENOTCHFILT9_FENOTCHATTNSEL19_SHIFT       0                                                  /**< Shift value for AGC_FENOTCHATTNSEL19        */
#define _AGC_FENOTCHFILT9_FENOTCHATTNSEL19_MASK        0xFUL                                              /**< Bit mask for AGC_FENOTCHATTNSEL19           */
#define _AGC_FENOTCHFILT9_FENOTCHATTNSEL19_DEFAULT     0x0000000BUL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT9           */
#define AGC_FENOTCHFILT9_FENOTCHATTNSEL19_DEFAULT      (_AGC_FENOTCHFILT9_FENOTCHATTNSEL19_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT9   */
#define _AGC_FENOTCHFILT9_FENOTCHCAPCRSE19_SHIFT       4                                                  /**< Shift value for AGC_FENOTCHCAPCRSE19        */
#define _AGC_FENOTCHFILT9_FENOTCHCAPCRSE19_MASK        0xF0UL                                             /**< Bit mask for AGC_FENOTCHCAPCRSE19           */
#define _AGC_FENOTCHFILT9_FENOTCHCAPCRSE19_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT9           */
#define AGC_FENOTCHFILT9_FENOTCHCAPCRSE19_DEFAULT      (_AGC_FENOTCHFILT9_FENOTCHCAPCRSE19_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT9   */
#define _AGC_FENOTCHFILT9_FENOTCHCAPFINE19_SHIFT       8                                                  /**< Shift value for AGC_FENOTCHCAPFINE19        */
#define _AGC_FENOTCHFILT9_FENOTCHCAPFINE19_MASK        0xF00UL                                            /**< Bit mask for AGC_FENOTCHCAPFINE19           */
#define _AGC_FENOTCHFILT9_FENOTCHCAPFINE19_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT9           */
#define AGC_FENOTCHFILT9_FENOTCHCAPFINE19_DEFAULT      (_AGC_FENOTCHFILT9_FENOTCHCAPFINE19_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT9   */
#define AGC_FENOTCHFILT9_FENOTCHRATTNEN19              (0x1UL << 12)                                      /**< FE notch rattn enable for index 19          */
#define _AGC_FENOTCHFILT9_FENOTCHRATTNEN19_SHIFT       12                                                 /**< Shift value for AGC_FENOTCHRATTNEN19        */
#define _AGC_FENOTCHFILT9_FENOTCHRATTNEN19_MASK        0x1000UL                                           /**< Bit mask for AGC_FENOTCHRATTNEN19           */
#define _AGC_FENOTCHFILT9_FENOTCHRATTNEN19_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT9           */
#define AGC_FENOTCHFILT9_FENOTCHRATTNEN19_DEFAULT      (_AGC_FENOTCHFILT9_FENOTCHRATTNEN19_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT9   */
#define AGC_FENOTCHFILT9_FENOTCHEN19                   (0x1UL << 13)                                      /**< FE notch enable for index 19                */
#define _AGC_FENOTCHFILT9_FENOTCHEN19_SHIFT            13                                                 /**< Shift value for AGC_FENOTCHEN19             */
#define _AGC_FENOTCHFILT9_FENOTCHEN19_MASK             0x2000UL                                           /**< Bit mask for AGC_FENOTCHEN19                */
#define _AGC_FENOTCHFILT9_FENOTCHEN19_DEFAULT          0x00000001UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT9           */
#define AGC_FENOTCHFILT9_FENOTCHEN19_DEFAULT           (_AGC_FENOTCHFILT9_FENOTCHEN19_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT9   */
#define _AGC_FENOTCHFILT9_FENOTCHATTNSEL20_SHIFT       16                                                 /**< Shift value for AGC_FENOTCHATTNSEL20        */
#define _AGC_FENOTCHFILT9_FENOTCHATTNSEL20_MASK        0xF0000UL                                          /**< Bit mask for AGC_FENOTCHATTNSEL20           */
#define _AGC_FENOTCHFILT9_FENOTCHATTNSEL20_DEFAULT     0x0000000BUL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT9           */
#define AGC_FENOTCHFILT9_FENOTCHATTNSEL20_DEFAULT      (_AGC_FENOTCHFILT9_FENOTCHATTNSEL20_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT9   */
#define _AGC_FENOTCHFILT9_FENOTCHCAPCRSE20_SHIFT       20                                                 /**< Shift value for AGC_FENOTCHCAPCRSE20        */
#define _AGC_FENOTCHFILT9_FENOTCHCAPCRSE20_MASK        0xF00000UL                                         /**< Bit mask for AGC_FENOTCHCAPCRSE20           */
#define _AGC_FENOTCHFILT9_FENOTCHCAPCRSE20_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT9           */
#define AGC_FENOTCHFILT9_FENOTCHCAPCRSE20_DEFAULT      (_AGC_FENOTCHFILT9_FENOTCHCAPCRSE20_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT9   */
#define _AGC_FENOTCHFILT9_FENOTCHCAPFINE20_SHIFT       24                                                 /**< Shift value for AGC_FENOTCHCAPFINE20        */
#define _AGC_FENOTCHFILT9_FENOTCHCAPFINE20_MASK        0xF000000UL                                        /**< Bit mask for AGC_FENOTCHCAPFINE20           */
#define _AGC_FENOTCHFILT9_FENOTCHCAPFINE20_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT9           */
#define AGC_FENOTCHFILT9_FENOTCHCAPFINE20_DEFAULT      (_AGC_FENOTCHFILT9_FENOTCHCAPFINE20_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT9   */
#define AGC_FENOTCHFILT9_FENOTCHRATTNEN20              (0x1UL << 28)                                      /**< FE notch rattn enable for index 20          */
#define _AGC_FENOTCHFILT9_FENOTCHRATTNEN20_SHIFT       28                                                 /**< Shift value for AGC_FENOTCHRATTNEN20        */
#define _AGC_FENOTCHFILT9_FENOTCHRATTNEN20_MASK        0x10000000UL                                       /**< Bit mask for AGC_FENOTCHRATTNEN20           */
#define _AGC_FENOTCHFILT9_FENOTCHRATTNEN20_DEFAULT     0x00000000UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT9           */
#define AGC_FENOTCHFILT9_FENOTCHRATTNEN20_DEFAULT      (_AGC_FENOTCHFILT9_FENOTCHRATTNEN20_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT9   */
#define AGC_FENOTCHFILT9_FENOTCHEN20                   (0x1UL << 29)                                      /**< FE notch enable for index 20                */
#define _AGC_FENOTCHFILT9_FENOTCHEN20_SHIFT            29                                                 /**< Shift value for AGC_FENOTCHEN20             */
#define _AGC_FENOTCHFILT9_FENOTCHEN20_MASK             0x20000000UL                                       /**< Bit mask for AGC_FENOTCHEN20                */
#define _AGC_FENOTCHFILT9_FENOTCHEN20_DEFAULT          0x00000001UL                                       /**< Mode DEFAULT for AGC_FENOTCHFILT9           */
#define AGC_FENOTCHFILT9_FENOTCHEN20_DEFAULT           (_AGC_FENOTCHFILT9_FENOTCHEN20_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT9   */

/* Bit fields for AGC FENOTCHFILT10 */
#define _AGC_FENOTCHFILT10_RESETVALUE                  0x200B200BUL                                        /**< Default value for AGC_FENOTCHFILT10         */
#define _AGC_FENOTCHFILT10_MASK                        0x3FFF3FFFUL                                        /**< Mask for AGC_FENOTCHFILT10                  */
#define _AGC_FENOTCHFILT10_FENOTCHATTNSEL21_SHIFT      0                                                   /**< Shift value for AGC_FENOTCHATTNSEL21        */
#define _AGC_FENOTCHFILT10_FENOTCHATTNSEL21_MASK       0xFUL                                               /**< Bit mask for AGC_FENOTCHATTNSEL21           */
#define _AGC_FENOTCHFILT10_FENOTCHATTNSEL21_DEFAULT    0x0000000BUL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT10          */
#define AGC_FENOTCHFILT10_FENOTCHATTNSEL21_DEFAULT     (_AGC_FENOTCHFILT10_FENOTCHATTNSEL21_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT10  */
#define _AGC_FENOTCHFILT10_FENOTCHCAPCRSE21_SHIFT      4                                                   /**< Shift value for AGC_FENOTCHCAPCRSE21        */
#define _AGC_FENOTCHFILT10_FENOTCHCAPCRSE21_MASK       0xF0UL                                              /**< Bit mask for AGC_FENOTCHCAPCRSE21           */
#define _AGC_FENOTCHFILT10_FENOTCHCAPCRSE21_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT10          */
#define AGC_FENOTCHFILT10_FENOTCHCAPCRSE21_DEFAULT     (_AGC_FENOTCHFILT10_FENOTCHCAPCRSE21_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT10  */
#define _AGC_FENOTCHFILT10_FENOTCHCAPFINE21_SHIFT      8                                                   /**< Shift value for AGC_FENOTCHCAPFINE21        */
#define _AGC_FENOTCHFILT10_FENOTCHCAPFINE21_MASK       0xF00UL                                             /**< Bit mask for AGC_FENOTCHCAPFINE21           */
#define _AGC_FENOTCHFILT10_FENOTCHCAPFINE21_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT10          */
#define AGC_FENOTCHFILT10_FENOTCHCAPFINE21_DEFAULT     (_AGC_FENOTCHFILT10_FENOTCHCAPFINE21_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT10  */
#define AGC_FENOTCHFILT10_FENOTCHRATTNEN21             (0x1UL << 12)                                       /**< FE notch rattn enable for index 21          */
#define _AGC_FENOTCHFILT10_FENOTCHRATTNEN21_SHIFT      12                                                  /**< Shift value for AGC_FENOTCHRATTNEN21        */
#define _AGC_FENOTCHFILT10_FENOTCHRATTNEN21_MASK       0x1000UL                                            /**< Bit mask for AGC_FENOTCHRATTNEN21           */
#define _AGC_FENOTCHFILT10_FENOTCHRATTNEN21_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT10          */
#define AGC_FENOTCHFILT10_FENOTCHRATTNEN21_DEFAULT     (_AGC_FENOTCHFILT10_FENOTCHRATTNEN21_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT10  */
#define AGC_FENOTCHFILT10_FENOTCHEN21                  (0x1UL << 13)                                       /**< FE notch enable for index 21                */
#define _AGC_FENOTCHFILT10_FENOTCHEN21_SHIFT           13                                                  /**< Shift value for AGC_FENOTCHEN21             */
#define _AGC_FENOTCHFILT10_FENOTCHEN21_MASK            0x2000UL                                            /**< Bit mask for AGC_FENOTCHEN21                */
#define _AGC_FENOTCHFILT10_FENOTCHEN21_DEFAULT         0x00000001UL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT10          */
#define AGC_FENOTCHFILT10_FENOTCHEN21_DEFAULT          (_AGC_FENOTCHFILT10_FENOTCHEN21_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT10  */
#define _AGC_FENOTCHFILT10_FENOTCHATTNSEL22_SHIFT      16                                                  /**< Shift value for AGC_FENOTCHATTNSEL22        */
#define _AGC_FENOTCHFILT10_FENOTCHATTNSEL22_MASK       0xF0000UL                                           /**< Bit mask for AGC_FENOTCHATTNSEL22           */
#define _AGC_FENOTCHFILT10_FENOTCHATTNSEL22_DEFAULT    0x0000000BUL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT10          */
#define AGC_FENOTCHFILT10_FENOTCHATTNSEL22_DEFAULT     (_AGC_FENOTCHFILT10_FENOTCHATTNSEL22_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT10  */
#define _AGC_FENOTCHFILT10_FENOTCHCAPCRSE22_SHIFT      20                                                  /**< Shift value for AGC_FENOTCHCAPCRSE22        */
#define _AGC_FENOTCHFILT10_FENOTCHCAPCRSE22_MASK       0xF00000UL                                          /**< Bit mask for AGC_FENOTCHCAPCRSE22           */
#define _AGC_FENOTCHFILT10_FENOTCHCAPCRSE22_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT10          */
#define AGC_FENOTCHFILT10_FENOTCHCAPCRSE22_DEFAULT     (_AGC_FENOTCHFILT10_FENOTCHCAPCRSE22_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT10  */
#define _AGC_FENOTCHFILT10_FENOTCHCAPFINE22_SHIFT      24                                                  /**< Shift value for AGC_FENOTCHCAPFINE22        */
#define _AGC_FENOTCHFILT10_FENOTCHCAPFINE22_MASK       0xF000000UL                                         /**< Bit mask for AGC_FENOTCHCAPFINE22           */
#define _AGC_FENOTCHFILT10_FENOTCHCAPFINE22_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT10          */
#define AGC_FENOTCHFILT10_FENOTCHCAPFINE22_DEFAULT     (_AGC_FENOTCHFILT10_FENOTCHCAPFINE22_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT10  */
#define AGC_FENOTCHFILT10_FENOTCHRATTNEN22             (0x1UL << 28)                                       /**< FE notch rattn enable for index 22          */
#define _AGC_FENOTCHFILT10_FENOTCHRATTNEN22_SHIFT      28                                                  /**< Shift value for AGC_FENOTCHRATTNEN22        */
#define _AGC_FENOTCHFILT10_FENOTCHRATTNEN22_MASK       0x10000000UL                                        /**< Bit mask for AGC_FENOTCHRATTNEN22           */
#define _AGC_FENOTCHFILT10_FENOTCHRATTNEN22_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT10          */
#define AGC_FENOTCHFILT10_FENOTCHRATTNEN22_DEFAULT     (_AGC_FENOTCHFILT10_FENOTCHRATTNEN22_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT10  */
#define AGC_FENOTCHFILT10_FENOTCHEN22                  (0x1UL << 29)                                       /**< FE notch enable for index 22                */
#define _AGC_FENOTCHFILT10_FENOTCHEN22_SHIFT           29                                                  /**< Shift value for AGC_FENOTCHEN22             */
#define _AGC_FENOTCHFILT10_FENOTCHEN22_MASK            0x20000000UL                                        /**< Bit mask for AGC_FENOTCHEN22                */
#define _AGC_FENOTCHFILT10_FENOTCHEN22_DEFAULT         0x00000001UL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT10          */
#define AGC_FENOTCHFILT10_FENOTCHEN22_DEFAULT          (_AGC_FENOTCHFILT10_FENOTCHEN22_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT10  */

/* Bit fields for AGC FENOTCHFILT11 */
#define _AGC_FENOTCHFILT11_RESETVALUE                  0x200B200BUL                                        /**< Default value for AGC_FENOTCHFILT11         */
#define _AGC_FENOTCHFILT11_MASK                        0x3FFF3FFFUL                                        /**< Mask for AGC_FENOTCHFILT11                  */
#define _AGC_FENOTCHFILT11_FENOTCHATTNSEL23_SHIFT      0                                                   /**< Shift value for AGC_FENOTCHATTNSEL23        */
#define _AGC_FENOTCHFILT11_FENOTCHATTNSEL23_MASK       0xFUL                                               /**< Bit mask for AGC_FENOTCHATTNSEL23           */
#define _AGC_FENOTCHFILT11_FENOTCHATTNSEL23_DEFAULT    0x0000000BUL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT11          */
#define AGC_FENOTCHFILT11_FENOTCHATTNSEL23_DEFAULT     (_AGC_FENOTCHFILT11_FENOTCHATTNSEL23_DEFAULT << 0)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT11  */
#define _AGC_FENOTCHFILT11_FENOTCHCAPCRSE23_SHIFT      4                                                   /**< Shift value for AGC_FENOTCHCAPCRSE23        */
#define _AGC_FENOTCHFILT11_FENOTCHCAPCRSE23_MASK       0xF0UL                                              /**< Bit mask for AGC_FENOTCHCAPCRSE23           */
#define _AGC_FENOTCHFILT11_FENOTCHCAPCRSE23_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT11          */
#define AGC_FENOTCHFILT11_FENOTCHCAPCRSE23_DEFAULT     (_AGC_FENOTCHFILT11_FENOTCHCAPCRSE23_DEFAULT << 4)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT11  */
#define _AGC_FENOTCHFILT11_FENOTCHCAPFINE23_SHIFT      8                                                   /**< Shift value for AGC_FENOTCHCAPFINE23        */
#define _AGC_FENOTCHFILT11_FENOTCHCAPFINE23_MASK       0xF00UL                                             /**< Bit mask for AGC_FENOTCHCAPFINE23           */
#define _AGC_FENOTCHFILT11_FENOTCHCAPFINE23_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT11          */
#define AGC_FENOTCHFILT11_FENOTCHCAPFINE23_DEFAULT     (_AGC_FENOTCHFILT11_FENOTCHCAPFINE23_DEFAULT << 8)  /**< Shifted mode DEFAULT for AGC_FENOTCHFILT11  */
#define AGC_FENOTCHFILT11_FENOTCHRATTNEN23             (0x1UL << 12)                                       /**< FE notch rattn enable for index 23          */
#define _AGC_FENOTCHFILT11_FENOTCHRATTNEN23_SHIFT      12                                                  /**< Shift value for AGC_FENOTCHRATTNEN23        */
#define _AGC_FENOTCHFILT11_FENOTCHRATTNEN23_MASK       0x1000UL                                            /**< Bit mask for AGC_FENOTCHRATTNEN23           */
#define _AGC_FENOTCHFILT11_FENOTCHRATTNEN23_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT11          */
#define AGC_FENOTCHFILT11_FENOTCHRATTNEN23_DEFAULT     (_AGC_FENOTCHFILT11_FENOTCHRATTNEN23_DEFAULT << 12) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT11  */
#define AGC_FENOTCHFILT11_FENOTCHEN23                  (0x1UL << 13)                                       /**< FE notch enable for index 23                */
#define _AGC_FENOTCHFILT11_FENOTCHEN23_SHIFT           13                                                  /**< Shift value for AGC_FENOTCHEN23             */
#define _AGC_FENOTCHFILT11_FENOTCHEN23_MASK            0x2000UL                                            /**< Bit mask for AGC_FENOTCHEN23                */
#define _AGC_FENOTCHFILT11_FENOTCHEN23_DEFAULT         0x00000001UL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT11          */
#define AGC_FENOTCHFILT11_FENOTCHEN23_DEFAULT          (_AGC_FENOTCHFILT11_FENOTCHEN23_DEFAULT << 13)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT11  */
#define _AGC_FENOTCHFILT11_FENOTCHATTNSEL24_SHIFT      16                                                  /**< Shift value for AGC_FENOTCHATTNSEL24        */
#define _AGC_FENOTCHFILT11_FENOTCHATTNSEL24_MASK       0xF0000UL                                           /**< Bit mask for AGC_FENOTCHATTNSEL24           */
#define _AGC_FENOTCHFILT11_FENOTCHATTNSEL24_DEFAULT    0x0000000BUL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT11          */
#define AGC_FENOTCHFILT11_FENOTCHATTNSEL24_DEFAULT     (_AGC_FENOTCHFILT11_FENOTCHATTNSEL24_DEFAULT << 16) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT11  */
#define _AGC_FENOTCHFILT11_FENOTCHCAPCRSE24_SHIFT      20                                                  /**< Shift value for AGC_FENOTCHCAPCRSE24        */
#define _AGC_FENOTCHFILT11_FENOTCHCAPCRSE24_MASK       0xF00000UL                                          /**< Bit mask for AGC_FENOTCHCAPCRSE24           */
#define _AGC_FENOTCHFILT11_FENOTCHCAPCRSE24_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT11          */
#define AGC_FENOTCHFILT11_FENOTCHCAPCRSE24_DEFAULT     (_AGC_FENOTCHFILT11_FENOTCHCAPCRSE24_DEFAULT << 20) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT11  */
#define _AGC_FENOTCHFILT11_FENOTCHCAPFINE24_SHIFT      24                                                  /**< Shift value for AGC_FENOTCHCAPFINE24        */
#define _AGC_FENOTCHFILT11_FENOTCHCAPFINE24_MASK       0xF000000UL                                         /**< Bit mask for AGC_FENOTCHCAPFINE24           */
#define _AGC_FENOTCHFILT11_FENOTCHCAPFINE24_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT11          */
#define AGC_FENOTCHFILT11_FENOTCHCAPFINE24_DEFAULT     (_AGC_FENOTCHFILT11_FENOTCHCAPFINE24_DEFAULT << 24) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT11  */
#define AGC_FENOTCHFILT11_FENOTCHRATTNEN24             (0x1UL << 28)                                       /**< FE notch rattn enable for index 24          */
#define _AGC_FENOTCHFILT11_FENOTCHRATTNEN24_SHIFT      28                                                  /**< Shift value for AGC_FENOTCHRATTNEN24        */
#define _AGC_FENOTCHFILT11_FENOTCHRATTNEN24_MASK       0x10000000UL                                        /**< Bit mask for AGC_FENOTCHRATTNEN24           */
#define _AGC_FENOTCHFILT11_FENOTCHRATTNEN24_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT11          */
#define AGC_FENOTCHFILT11_FENOTCHRATTNEN24_DEFAULT     (_AGC_FENOTCHFILT11_FENOTCHRATTNEN24_DEFAULT << 28) /**< Shifted mode DEFAULT for AGC_FENOTCHFILT11  */
#define AGC_FENOTCHFILT11_FENOTCHEN24                  (0x1UL << 29)                                       /**< FE notch enable for index 24                */
#define _AGC_FENOTCHFILT11_FENOTCHEN24_SHIFT           29                                                  /**< Shift value for AGC_FENOTCHEN24             */
#define _AGC_FENOTCHFILT11_FENOTCHEN24_MASK            0x20000000UL                                        /**< Bit mask for AGC_FENOTCHEN24                */
#define _AGC_FENOTCHFILT11_FENOTCHEN24_DEFAULT         0x00000001UL                                        /**< Mode DEFAULT for AGC_FENOTCHFILT11          */
#define AGC_FENOTCHFILT11_FENOTCHEN24_DEFAULT          (_AGC_FENOTCHFILT11_FENOTCHEN24_DEFAULT << 29)      /**< Shifted mode DEFAULT for AGC_FENOTCHFILT11  */

/* Bit fields for AGC CCADEBUG */
#define _AGC_CCADEBUG_RESETVALUE                       0x00000000UL                                /**< Default value for AGC_CCADEBUG              */
#define _AGC_CCADEBUG_MASK                             0x000003FFUL                                /**< Mask for AGC_CCADEBUG                       */
#define _AGC_CCADEBUG_DEBUGCCARSSI_SHIFT               0                                           /**< Shift value for AGC_DEBUGCCARSSI            */
#define _AGC_CCADEBUG_DEBUGCCARSSI_MASK                0xFFUL                                      /**< Bit mask for AGC_DEBUGCCARSSI               */
#define _AGC_CCADEBUG_DEBUGCCARSSI_DEFAULT             0x00000000UL                                /**< Mode DEFAULT for AGC_CCADEBUG               */
#define AGC_CCADEBUG_DEBUGCCARSSI_DEFAULT              (_AGC_CCADEBUG_DEBUGCCARSSI_DEFAULT << 0)   /**< Shifted mode DEFAULT for AGC_CCADEBUG       */
#define AGC_CCADEBUG_DEBUGCCAM1                        (0x1UL << 8)                                /**< Mode 1 Clear Channel Assessment             */
#define _AGC_CCADEBUG_DEBUGCCAM1_SHIFT                 8                                           /**< Shift value for AGC_DEBUGCCAM1              */
#define _AGC_CCADEBUG_DEBUGCCAM1_MASK                  0x100UL                                     /**< Bit mask for AGC_DEBUGCCAM1                 */
#define _AGC_CCADEBUG_DEBUGCCAM1_DEFAULT               0x00000000UL                                /**< Mode DEFAULT for AGC_CCADEBUG               */
#define AGC_CCADEBUG_DEBUGCCAM1_DEFAULT                (_AGC_CCADEBUG_DEBUGCCAM1_DEFAULT << 8)     /**< Shifted mode DEFAULT for AGC_CCADEBUG       */
#define AGC_CCADEBUG_DEBUGCCASIGDET                    (0x1UL << 9)                                /**< Signal detector Clear Channel Assessment    */
#define _AGC_CCADEBUG_DEBUGCCASIGDET_SHIFT             9                                           /**< Shift value for AGC_DEBUGCCASIGDET          */
#define _AGC_CCADEBUG_DEBUGCCASIGDET_MASK              0x200UL                                     /**< Bit mask for AGC_DEBUGCCASIGDET             */
#define _AGC_CCADEBUG_DEBUGCCASIGDET_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for AGC_CCADEBUG               */
#define AGC_CCADEBUG_DEBUGCCASIGDET_DEFAULT            (_AGC_CCADEBUG_DEBUGCCASIGDET_DEFAULT << 9) /**< Shifted mode DEFAULT for AGC_CCADEBUG       */

/** @} End of group EFR32MG24_AGC_BitFields */
/** @} End of group EFR32MG24_AGC */
/** @} End of group Parts */

#endif /* EFR32MG24_AGC_H */
