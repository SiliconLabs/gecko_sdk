/**************************************************************************//**
 * @file
 * @brief EFR32FG25 TXFRONT register and bit field definitions
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
#ifndef EFR32FG25_TXFRONT_H
#define EFR32FG25_TXFRONT_H
#define TXFRONT_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_TXFRONT TXFRONT
 * @{
 * @brief EFR32FG25 TXFRONT Register Declaration.
 *****************************************************************************/

/** TXFRONT Register Declaration. */
typedef struct {
  __IM uint32_t  IPVERSION;                     /**< IP Version ID                                      */
  __IOM uint32_t EN;                            /**< Module Enable                                      */
  __IOM uint32_t SWRST;                         /**< Software Reset                                     */
  uint32_t       RESERVED0[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t DISCLK;                        /**< Disable clk_per                                    */
  uint32_t       RESERVED1[59U];                /**< Reserved for future use                            */
  __IOM uint32_t INT1CFG;                       /**< New Register                                       */
  __IOM uint32_t INT1COEF01;                    /**< New Register                                       */
  __IOM uint32_t INT1COEF23;                    /**< New Register                                       */
  __IOM uint32_t INT1COEF45;                    /**< New Register                                       */
  __IOM uint32_t INT1COEF67;                    /**< New Register                                       */
  __IOM uint32_t INT1COEF89;                    /**< New Register                                       */
  __IOM uint32_t INT1COEF1011;                  /**< New Register                                       */
  __IOM uint32_t INT1COEF1213;                  /**< New Register                                       */
  __IOM uint32_t INT1COEF1415;                  /**< New Register                                       */
  __IOM uint32_t INT2CFG;                       /**< New Register                                       */
  __IOM uint32_t SRCCFG;                        /**< New Register                                       */
  __IOM uint32_t TXIQIMB;                       /**< New Register                                       */
  __IOM uint32_t TXDCOFFSET;                    /**< New Register                                       */
  __IOM uint32_t TXRAMPUP;                      /**< New Register                                       */
  __IOM uint32_t TXDCRAMPUP;                    /**< New Register                                       */
  __IOM uint32_t TXGAIN;                        /**< New Register                                       */
  __IOM uint32_t TXCLIP;                        /**< New Register                                       */
  __IOM uint32_t TXPREDIST;                     /**< New Register                                       */
  uint32_t       RESERVED2[2U];                 /**< Reserved for future use                            */
  __IOM uint32_t DAC;                           /**< New Register                                       */
  uint32_t       RESERVED3[939U];               /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_SET;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_SET;                     /**< Software Reset                                     */
  uint32_t       RESERVED4[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t DISCLK_SET;                    /**< Disable clk_per                                    */
  uint32_t       RESERVED5[59U];                /**< Reserved for future use                            */
  __IOM uint32_t INT1CFG_SET;                   /**< New Register                                       */
  __IOM uint32_t INT1COEF01_SET;                /**< New Register                                       */
  __IOM uint32_t INT1COEF23_SET;                /**< New Register                                       */
  __IOM uint32_t INT1COEF45_SET;                /**< New Register                                       */
  __IOM uint32_t INT1COEF67_SET;                /**< New Register                                       */
  __IOM uint32_t INT1COEF89_SET;                /**< New Register                                       */
  __IOM uint32_t INT1COEF1011_SET;              /**< New Register                                       */
  __IOM uint32_t INT1COEF1213_SET;              /**< New Register                                       */
  __IOM uint32_t INT1COEF1415_SET;              /**< New Register                                       */
  __IOM uint32_t INT2CFG_SET;                   /**< New Register                                       */
  __IOM uint32_t SRCCFG_SET;                    /**< New Register                                       */
  __IOM uint32_t TXIQIMB_SET;                   /**< New Register                                       */
  __IOM uint32_t TXDCOFFSET_SET;                /**< New Register                                       */
  __IOM uint32_t TXRAMPUP_SET;                  /**< New Register                                       */
  __IOM uint32_t TXDCRAMPUP_SET;                /**< New Register                                       */
  __IOM uint32_t TXGAIN_SET;                    /**< New Register                                       */
  __IOM uint32_t TXCLIP_SET;                    /**< New Register                                       */
  __IOM uint32_t TXPREDIST_SET;                 /**< New Register                                       */
  uint32_t       RESERVED6[2U];                 /**< Reserved for future use                            */
  __IOM uint32_t DAC_SET;                       /**< New Register                                       */
  uint32_t       RESERVED7[939U];               /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_CLR;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_CLR;                     /**< Software Reset                                     */
  uint32_t       RESERVED8[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t DISCLK_CLR;                    /**< Disable clk_per                                    */
  uint32_t       RESERVED9[59U];                /**< Reserved for future use                            */
  __IOM uint32_t INT1CFG_CLR;                   /**< New Register                                       */
  __IOM uint32_t INT1COEF01_CLR;                /**< New Register                                       */
  __IOM uint32_t INT1COEF23_CLR;                /**< New Register                                       */
  __IOM uint32_t INT1COEF45_CLR;                /**< New Register                                       */
  __IOM uint32_t INT1COEF67_CLR;                /**< New Register                                       */
  __IOM uint32_t INT1COEF89_CLR;                /**< New Register                                       */
  __IOM uint32_t INT1COEF1011_CLR;              /**< New Register                                       */
  __IOM uint32_t INT1COEF1213_CLR;              /**< New Register                                       */
  __IOM uint32_t INT1COEF1415_CLR;              /**< New Register                                       */
  __IOM uint32_t INT2CFG_CLR;                   /**< New Register                                       */
  __IOM uint32_t SRCCFG_CLR;                    /**< New Register                                       */
  __IOM uint32_t TXIQIMB_CLR;                   /**< New Register                                       */
  __IOM uint32_t TXDCOFFSET_CLR;                /**< New Register                                       */
  __IOM uint32_t TXRAMPUP_CLR;                  /**< New Register                                       */
  __IOM uint32_t TXDCRAMPUP_CLR;                /**< New Register                                       */
  __IOM uint32_t TXGAIN_CLR;                    /**< New Register                                       */
  __IOM uint32_t TXCLIP_CLR;                    /**< New Register                                       */
  __IOM uint32_t TXPREDIST_CLR;                 /**< New Register                                       */
  uint32_t       RESERVED10[2U];                /**< Reserved for future use                            */
  __IOM uint32_t DAC_CLR;                       /**< New Register                                       */
  uint32_t       RESERVED11[939U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_TGL;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_TGL;                     /**< Software Reset                                     */
  uint32_t       RESERVED12[1U];                /**< Reserved for future use                            */
  __IOM uint32_t DISCLK_TGL;                    /**< Disable clk_per                                    */
  uint32_t       RESERVED13[59U];               /**< Reserved for future use                            */
  __IOM uint32_t INT1CFG_TGL;                   /**< New Register                                       */
  __IOM uint32_t INT1COEF01_TGL;                /**< New Register                                       */
  __IOM uint32_t INT1COEF23_TGL;                /**< New Register                                       */
  __IOM uint32_t INT1COEF45_TGL;                /**< New Register                                       */
  __IOM uint32_t INT1COEF67_TGL;                /**< New Register                                       */
  __IOM uint32_t INT1COEF89_TGL;                /**< New Register                                       */
  __IOM uint32_t INT1COEF1011_TGL;              /**< New Register                                       */
  __IOM uint32_t INT1COEF1213_TGL;              /**< New Register                                       */
  __IOM uint32_t INT1COEF1415_TGL;              /**< New Register                                       */
  __IOM uint32_t INT2CFG_TGL;                   /**< New Register                                       */
  __IOM uint32_t SRCCFG_TGL;                    /**< New Register                                       */
  __IOM uint32_t TXIQIMB_TGL;                   /**< New Register                                       */
  __IOM uint32_t TXDCOFFSET_TGL;                /**< New Register                                       */
  __IOM uint32_t TXRAMPUP_TGL;                  /**< New Register                                       */
  __IOM uint32_t TXDCRAMPUP_TGL;                /**< New Register                                       */
  __IOM uint32_t TXGAIN_TGL;                    /**< New Register                                       */
  __IOM uint32_t TXCLIP_TGL;                    /**< New Register                                       */
  __IOM uint32_t TXPREDIST_TGL;                 /**< New Register                                       */
  uint32_t       RESERVED14[2U];                /**< Reserved for future use                            */
  __IOM uint32_t DAC_TGL;                       /**< New Register                                       */
} TXFRONT_TypeDef;
/** @} End of group EFR32FG25_TXFRONT */

/**************************************************************************//**
 * @addtogroup EFR32FG25_TXFRONT
 * @{
 * @defgroup EFR32FG25_TXFRONT_BitFields TXFRONT Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for TXFRONT IPVERSION */
#define _TXFRONT_IPVERSION_RESETVALUE            0x00000001UL                                /**< Default value for TXFRONT_IPVERSION         */
#define _TXFRONT_IPVERSION_MASK                  0xFFFFFFFFUL                                /**< Mask for TXFRONT_IPVERSION                  */
#define _TXFRONT_IPVERSION_IPVERSION_SHIFT       0                                           /**< Shift value for TXFRONT_IPVERSION           */
#define _TXFRONT_IPVERSION_IPVERSION_MASK        0xFFFFFFFFUL                                /**< Bit mask for TXFRONT_IPVERSION              */
#define _TXFRONT_IPVERSION_IPVERSION_DEFAULT     0x00000001UL                                /**< Mode DEFAULT for TXFRONT_IPVERSION          */
#define TXFRONT_IPVERSION_IPVERSION_DEFAULT      (_TXFRONT_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for TXFRONT_IPVERSION  */

/* Bit fields for TXFRONT EN */
#define _TXFRONT_EN_RESETVALUE                   0x00000000UL                           /**< Default value for TXFRONT_EN                */
#define _TXFRONT_EN_MASK                         0x00000003UL                           /**< Mask for TXFRONT_EN                         */
#define TXFRONT_EN_EN                            (0x1UL << 0)                           /**< Module Enable                               */
#define _TXFRONT_EN_EN_SHIFT                     0                                      /**< Shift value for TXFRONT_EN                  */
#define _TXFRONT_EN_EN_MASK                      0x1UL                                  /**< Bit mask for TXFRONT_EN                     */
#define _TXFRONT_EN_EN_DEFAULT                   0x00000000UL                           /**< Mode DEFAULT for TXFRONT_EN                 */
#define TXFRONT_EN_EN_DEFAULT                    (_TXFRONT_EN_EN_DEFAULT << 0)          /**< Shifted mode DEFAULT for TXFRONT_EN         */
#define TXFRONT_EN_DISABLING                     (0x1UL << 1)                           /**< Disablement Busy Status                     */
#define _TXFRONT_EN_DISABLING_SHIFT              1                                      /**< Shift value for TXFRONT_DISABLING           */
#define _TXFRONT_EN_DISABLING_MASK               0x2UL                                  /**< Bit mask for TXFRONT_DISABLING              */
#define _TXFRONT_EN_DISABLING_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for TXFRONT_EN                 */
#define TXFRONT_EN_DISABLING_DEFAULT             (_TXFRONT_EN_DISABLING_DEFAULT << 1)   /**< Shifted mode DEFAULT for TXFRONT_EN         */

/* Bit fields for TXFRONT SWRST */
#define _TXFRONT_SWRST_RESETVALUE                0x00000000UL                            /**< Default value for TXFRONT_SWRST             */
#define _TXFRONT_SWRST_MASK                      0x00000003UL                            /**< Mask for TXFRONT_SWRST                      */
#define TXFRONT_SWRST_SWRST                      (0x1UL << 0)                            /**< Software Reset Command                      */
#define _TXFRONT_SWRST_SWRST_SHIFT               0                                       /**< Shift value for TXFRONT_SWRST               */
#define _TXFRONT_SWRST_SWRST_MASK                0x1UL                                   /**< Bit mask for TXFRONT_SWRST                  */
#define _TXFRONT_SWRST_SWRST_DEFAULT             0x00000000UL                            /**< Mode DEFAULT for TXFRONT_SWRST              */
#define TXFRONT_SWRST_SWRST_DEFAULT              (_TXFRONT_SWRST_SWRST_DEFAULT << 0)     /**< Shifted mode DEFAULT for TXFRONT_SWRST      */
#define TXFRONT_SWRST_RESETTING                  (0x1UL << 1)                            /**< Software Reset Busy Status                  */
#define _TXFRONT_SWRST_RESETTING_SHIFT           1                                       /**< Shift value for TXFRONT_RESETTING           */
#define _TXFRONT_SWRST_RESETTING_MASK            0x2UL                                   /**< Bit mask for TXFRONT_RESETTING              */
#define _TXFRONT_SWRST_RESETTING_DEFAULT         0x00000000UL                            /**< Mode DEFAULT for TXFRONT_SWRST              */
#define TXFRONT_SWRST_RESETTING_DEFAULT          (_TXFRONT_SWRST_RESETTING_DEFAULT << 1) /**< Shifted mode DEFAULT for TXFRONT_SWRST      */

/* Bit fields for TXFRONT DISCLK */
#define _TXFRONT_DISCLK_RESETVALUE               0x00000000UL                           /**< Default value for TXFRONT_DISCLK            */
#define _TXFRONT_DISCLK_MASK                     0x00000001UL                           /**< Mask for TXFRONT_DISCLK                     */
#define TXFRONT_DISCLK_DISCLK                    (0x1UL << 0)                           /**< New BitField                                */
#define _TXFRONT_DISCLK_DISCLK_SHIFT             0                                      /**< Shift value for TXFRONT_DISCLK              */
#define _TXFRONT_DISCLK_DISCLK_MASK              0x1UL                                  /**< Bit mask for TXFRONT_DISCLK                 */
#define _TXFRONT_DISCLK_DISCLK_DEFAULT           0x00000000UL                           /**< Mode DEFAULT for TXFRONT_DISCLK             */
#define TXFRONT_DISCLK_DISCLK_DEFAULT            (_TXFRONT_DISCLK_DISCLK_DEFAULT << 0)  /**< Shifted mode DEFAULT for TXFRONT_DISCLK     */

/* Bit fields for TXFRONT INT1CFG */
#define _TXFRONT_INT1CFG_RESETVALUE              0x000000C7UL                              /**< Default value for TXFRONT_INT1CFG           */
#define _TXFRONT_INT1CFG_MASK                    0x000001FFUL                              /**< Mask for TXFRONT_INT1CFG                    */
#define _TXFRONT_INT1CFG_RATIO_SHIFT             0                                         /**< Shift value for TXFRONT_RATIO               */
#define _TXFRONT_INT1CFG_RATIO_MASK              0xFUL                                     /**< Bit mask for TXFRONT_RATIO                  */
#define _TXFRONT_INT1CFG_RATIO_DEFAULT           0x00000007UL                              /**< Mode DEFAULT for TXFRONT_INT1CFG            */
#define TXFRONT_INT1CFG_RATIO_DEFAULT            (_TXFRONT_INT1CFG_RATIO_DEFAULT << 0)     /**< Shifted mode DEFAULT for TXFRONT_INT1CFG    */
#define _TXFRONT_INT1CFG_GAINSHIFT_SHIFT         4                                         /**< Shift value for TXFRONT_GAINSHIFT           */
#define _TXFRONT_INT1CFG_GAINSHIFT_MASK          0x1F0UL                                   /**< Bit mask for TXFRONT_GAINSHIFT              */
#define _TXFRONT_INT1CFG_GAINSHIFT_DEFAULT       0x0000000CUL                              /**< Mode DEFAULT for TXFRONT_INT1CFG            */
#define TXFRONT_INT1CFG_GAINSHIFT_DEFAULT        (_TXFRONT_INT1CFG_GAINSHIFT_DEFAULT << 4) /**< Shifted mode DEFAULT for TXFRONT_INT1CFG    */

/* Bit fields for TXFRONT INT1COEF01 */
#define _TXFRONT_INT1COEF01_RESETVALUE           0x00000000UL                               /**< Default value for TXFRONT_INT1COEF01        */
#define _TXFRONT_INT1COEF01_MASK                 0x7FFF7FFFUL                               /**< Mask for TXFRONT_INT1COEF01                 */
#define _TXFRONT_INT1COEF01_COEFF0_SHIFT         0                                          /**< Shift value for TXFRONT_COEFF0              */
#define _TXFRONT_INT1COEF01_COEFF0_MASK          0x7FFFUL                                   /**< Bit mask for TXFRONT_COEFF0                 */
#define _TXFRONT_INT1COEF01_COEFF0_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for TXFRONT_INT1COEF01         */
#define TXFRONT_INT1COEF01_COEFF0_DEFAULT        (_TXFRONT_INT1COEF01_COEFF0_DEFAULT << 0)  /**< Shifted mode DEFAULT for TXFRONT_INT1COEF01 */
#define _TXFRONT_INT1COEF01_COEFF1_SHIFT         16                                         /**< Shift value for TXFRONT_COEFF1              */
#define _TXFRONT_INT1COEF01_COEFF1_MASK          0x7FFF0000UL                               /**< Bit mask for TXFRONT_COEFF1                 */
#define _TXFRONT_INT1COEF01_COEFF1_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for TXFRONT_INT1COEF01         */
#define TXFRONT_INT1COEF01_COEFF1_DEFAULT        (_TXFRONT_INT1COEF01_COEFF1_DEFAULT << 16) /**< Shifted mode DEFAULT for TXFRONT_INT1COEF01 */

/* Bit fields for TXFRONT INT1COEF23 */
#define _TXFRONT_INT1COEF23_RESETVALUE           0x00000000UL                               /**< Default value for TXFRONT_INT1COEF23        */
#define _TXFRONT_INT1COEF23_MASK                 0x7FFF7FFFUL                               /**< Mask for TXFRONT_INT1COEF23                 */
#define _TXFRONT_INT1COEF23_COEFF2_SHIFT         0                                          /**< Shift value for TXFRONT_COEFF2              */
#define _TXFRONT_INT1COEF23_COEFF2_MASK          0x7FFFUL                                   /**< Bit mask for TXFRONT_COEFF2                 */
#define _TXFRONT_INT1COEF23_COEFF2_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for TXFRONT_INT1COEF23         */
#define TXFRONT_INT1COEF23_COEFF2_DEFAULT        (_TXFRONT_INT1COEF23_COEFF2_DEFAULT << 0)  /**< Shifted mode DEFAULT for TXFRONT_INT1COEF23 */
#define _TXFRONT_INT1COEF23_COEFF3_SHIFT         16                                         /**< Shift value for TXFRONT_COEFF3              */
#define _TXFRONT_INT1COEF23_COEFF3_MASK          0x7FFF0000UL                               /**< Bit mask for TXFRONT_COEFF3                 */
#define _TXFRONT_INT1COEF23_COEFF3_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for TXFRONT_INT1COEF23         */
#define TXFRONT_INT1COEF23_COEFF3_DEFAULT        (_TXFRONT_INT1COEF23_COEFF3_DEFAULT << 16) /**< Shifted mode DEFAULT for TXFRONT_INT1COEF23 */

/* Bit fields for TXFRONT INT1COEF45 */
#define _TXFRONT_INT1COEF45_RESETVALUE           0x00000000UL                               /**< Default value for TXFRONT_INT1COEF45        */
#define _TXFRONT_INT1COEF45_MASK                 0x7FFF7FFFUL                               /**< Mask for TXFRONT_INT1COEF45                 */
#define _TXFRONT_INT1COEF45_COEFF4_SHIFT         0                                          /**< Shift value for TXFRONT_COEFF4              */
#define _TXFRONT_INT1COEF45_COEFF4_MASK          0x7FFFUL                                   /**< Bit mask for TXFRONT_COEFF4                 */
#define _TXFRONT_INT1COEF45_COEFF4_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for TXFRONT_INT1COEF45         */
#define TXFRONT_INT1COEF45_COEFF4_DEFAULT        (_TXFRONT_INT1COEF45_COEFF4_DEFAULT << 0)  /**< Shifted mode DEFAULT for TXFRONT_INT1COEF45 */
#define _TXFRONT_INT1COEF45_COEFF5_SHIFT         16                                         /**< Shift value for TXFRONT_COEFF5              */
#define _TXFRONT_INT1COEF45_COEFF5_MASK          0x7FFF0000UL                               /**< Bit mask for TXFRONT_COEFF5                 */
#define _TXFRONT_INT1COEF45_COEFF5_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for TXFRONT_INT1COEF45         */
#define TXFRONT_INT1COEF45_COEFF5_DEFAULT        (_TXFRONT_INT1COEF45_COEFF5_DEFAULT << 16) /**< Shifted mode DEFAULT for TXFRONT_INT1COEF45 */

/* Bit fields for TXFRONT INT1COEF67 */
#define _TXFRONT_INT1COEF67_RESETVALUE           0x00000000UL                               /**< Default value for TXFRONT_INT1COEF67        */
#define _TXFRONT_INT1COEF67_MASK                 0x7FFF7FFFUL                               /**< Mask for TXFRONT_INT1COEF67                 */
#define _TXFRONT_INT1COEF67_COEFF6_SHIFT         0                                          /**< Shift value for TXFRONT_COEFF6              */
#define _TXFRONT_INT1COEF67_COEFF6_MASK          0x7FFFUL                                   /**< Bit mask for TXFRONT_COEFF6                 */
#define _TXFRONT_INT1COEF67_COEFF6_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for TXFRONT_INT1COEF67         */
#define TXFRONT_INT1COEF67_COEFF6_DEFAULT        (_TXFRONT_INT1COEF67_COEFF6_DEFAULT << 0)  /**< Shifted mode DEFAULT for TXFRONT_INT1COEF67 */
#define _TXFRONT_INT1COEF67_COEFF7_SHIFT         16                                         /**< Shift value for TXFRONT_COEFF7              */
#define _TXFRONT_INT1COEF67_COEFF7_MASK          0x7FFF0000UL                               /**< Bit mask for TXFRONT_COEFF7                 */
#define _TXFRONT_INT1COEF67_COEFF7_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for TXFRONT_INT1COEF67         */
#define TXFRONT_INT1COEF67_COEFF7_DEFAULT        (_TXFRONT_INT1COEF67_COEFF7_DEFAULT << 16) /**< Shifted mode DEFAULT for TXFRONT_INT1COEF67 */

/* Bit fields for TXFRONT INT1COEF89 */
#define _TXFRONT_INT1COEF89_RESETVALUE           0x00000000UL                               /**< Default value for TXFRONT_INT1COEF89        */
#define _TXFRONT_INT1COEF89_MASK                 0x7FFF7FFFUL                               /**< Mask for TXFRONT_INT1COEF89                 */
#define _TXFRONT_INT1COEF89_COEFF8_SHIFT         0                                          /**< Shift value for TXFRONT_COEFF8              */
#define _TXFRONT_INT1COEF89_COEFF8_MASK          0x7FFFUL                                   /**< Bit mask for TXFRONT_COEFF8                 */
#define _TXFRONT_INT1COEF89_COEFF8_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for TXFRONT_INT1COEF89         */
#define TXFRONT_INT1COEF89_COEFF8_DEFAULT        (_TXFRONT_INT1COEF89_COEFF8_DEFAULT << 0)  /**< Shifted mode DEFAULT for TXFRONT_INT1COEF89 */
#define _TXFRONT_INT1COEF89_COEFF9_SHIFT         16                                         /**< Shift value for TXFRONT_COEFF9              */
#define _TXFRONT_INT1COEF89_COEFF9_MASK          0x7FFF0000UL                               /**< Bit mask for TXFRONT_COEFF9                 */
#define _TXFRONT_INT1COEF89_COEFF9_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for TXFRONT_INT1COEF89         */
#define TXFRONT_INT1COEF89_COEFF9_DEFAULT        (_TXFRONT_INT1COEF89_COEFF9_DEFAULT << 16) /**< Shifted mode DEFAULT for TXFRONT_INT1COEF89 */

/* Bit fields for TXFRONT INT1COEF1011 */
#define _TXFRONT_INT1COEF1011_RESETVALUE         0x00000000UL                                  /**< Default value for TXFRONT_INT1COEF1011      */
#define _TXFRONT_INT1COEF1011_MASK               0x7FFF7FFFUL                                  /**< Mask for TXFRONT_INT1COEF1011               */
#define _TXFRONT_INT1COEF1011_COEFF10_SHIFT      0                                             /**< Shift value for TXFRONT_COEFF10             */
#define _TXFRONT_INT1COEF1011_COEFF10_MASK       0x7FFFUL                                      /**< Bit mask for TXFRONT_COEFF10                */
#define _TXFRONT_INT1COEF1011_COEFF10_DEFAULT    0x00000000UL                                  /**< Mode DEFAULT for TXFRONT_INT1COEF1011       */
#define TXFRONT_INT1COEF1011_COEFF10_DEFAULT     (_TXFRONT_INT1COEF1011_COEFF10_DEFAULT << 0)  /**< Shifted mode DEFAULT for TXFRONT_INT1COEF1011*/
#define _TXFRONT_INT1COEF1011_COEFF11_SHIFT      16                                            /**< Shift value for TXFRONT_COEFF11             */
#define _TXFRONT_INT1COEF1011_COEFF11_MASK       0x7FFF0000UL                                  /**< Bit mask for TXFRONT_COEFF11                */
#define _TXFRONT_INT1COEF1011_COEFF11_DEFAULT    0x00000000UL                                  /**< Mode DEFAULT for TXFRONT_INT1COEF1011       */
#define TXFRONT_INT1COEF1011_COEFF11_DEFAULT     (_TXFRONT_INT1COEF1011_COEFF11_DEFAULT << 16) /**< Shifted mode DEFAULT for TXFRONT_INT1COEF1011*/

/* Bit fields for TXFRONT INT1COEF1213 */
#define _TXFRONT_INT1COEF1213_RESETVALUE         0x00000000UL                                  /**< Default value for TXFRONT_INT1COEF1213      */
#define _TXFRONT_INT1COEF1213_MASK               0x7FFF7FFFUL                                  /**< Mask for TXFRONT_INT1COEF1213               */
#define _TXFRONT_INT1COEF1213_COEFF12_SHIFT      0                                             /**< Shift value for TXFRONT_COEFF12             */
#define _TXFRONT_INT1COEF1213_COEFF12_MASK       0x7FFFUL                                      /**< Bit mask for TXFRONT_COEFF12                */
#define _TXFRONT_INT1COEF1213_COEFF12_DEFAULT    0x00000000UL                                  /**< Mode DEFAULT for TXFRONT_INT1COEF1213       */
#define TXFRONT_INT1COEF1213_COEFF12_DEFAULT     (_TXFRONT_INT1COEF1213_COEFF12_DEFAULT << 0)  /**< Shifted mode DEFAULT for TXFRONT_INT1COEF1213*/
#define _TXFRONT_INT1COEF1213_COEFF13_SHIFT      16                                            /**< Shift value for TXFRONT_COEFF13             */
#define _TXFRONT_INT1COEF1213_COEFF13_MASK       0x7FFF0000UL                                  /**< Bit mask for TXFRONT_COEFF13                */
#define _TXFRONT_INT1COEF1213_COEFF13_DEFAULT    0x00000000UL                                  /**< Mode DEFAULT for TXFRONT_INT1COEF1213       */
#define TXFRONT_INT1COEF1213_COEFF13_DEFAULT     (_TXFRONT_INT1COEF1213_COEFF13_DEFAULT << 16) /**< Shifted mode DEFAULT for TXFRONT_INT1COEF1213*/

/* Bit fields for TXFRONT INT1COEF1415 */
#define _TXFRONT_INT1COEF1415_RESETVALUE         0x00000000UL                                  /**< Default value for TXFRONT_INT1COEF1415      */
#define _TXFRONT_INT1COEF1415_MASK               0x7FFF7FFFUL                                  /**< Mask for TXFRONT_INT1COEF1415               */
#define _TXFRONT_INT1COEF1415_COEFF14_SHIFT      0                                             /**< Shift value for TXFRONT_COEFF14             */
#define _TXFRONT_INT1COEF1415_COEFF14_MASK       0x7FFFUL                                      /**< Bit mask for TXFRONT_COEFF14                */
#define _TXFRONT_INT1COEF1415_COEFF14_DEFAULT    0x00000000UL                                  /**< Mode DEFAULT for TXFRONT_INT1COEF1415       */
#define TXFRONT_INT1COEF1415_COEFF14_DEFAULT     (_TXFRONT_INT1COEF1415_COEFF14_DEFAULT << 0)  /**< Shifted mode DEFAULT for TXFRONT_INT1COEF1415*/
#define _TXFRONT_INT1COEF1415_COEFF15_SHIFT      16                                            /**< Shift value for TXFRONT_COEFF15             */
#define _TXFRONT_INT1COEF1415_COEFF15_MASK       0x7FFF0000UL                                  /**< Bit mask for TXFRONT_COEFF15                */
#define _TXFRONT_INT1COEF1415_COEFF15_DEFAULT    0x00000000UL                                  /**< Mode DEFAULT for TXFRONT_INT1COEF1415       */
#define TXFRONT_INT1COEF1415_COEFF15_DEFAULT     (_TXFRONT_INT1COEF1415_COEFF15_DEFAULT << 16) /**< Shifted mode DEFAULT for TXFRONT_INT1COEF1415*/

/* Bit fields for TXFRONT INT2CFG */
#define _TXFRONT_INT2CFG_RESETVALUE              0x00000802UL                               /**< Default value for TXFRONT_INT2CFG           */
#define _TXFRONT_INT2CFG_MASK                    0x00007FFFUL                               /**< Mask for TXFRONT_INT2CFG                    */
#define _TXFRONT_INT2CFG_RATIO_SHIFT             0                                          /**< Shift value for TXFRONT_RATIO               */
#define _TXFRONT_INT2CFG_RATIO_MASK              0x3FFUL                                    /**< Bit mask for TXFRONT_RATIO                  */
#define _TXFRONT_INT2CFG_RATIO_DEFAULT           0x00000002UL                               /**< Mode DEFAULT for TXFRONT_INT2CFG            */
#define TXFRONT_INT2CFG_RATIO_DEFAULT            (_TXFRONT_INT2CFG_RATIO_DEFAULT << 0)      /**< Shifted mode DEFAULT for TXFRONT_INT2CFG    */
#define _TXFRONT_INT2CFG_GAINSHIFT_SHIFT         10                                         /**< Shift value for TXFRONT_GAINSHIFT           */
#define _TXFRONT_INT2CFG_GAINSHIFT_MASK          0x7C00UL                                   /**< Bit mask for TXFRONT_GAINSHIFT              */
#define _TXFRONT_INT2CFG_GAINSHIFT_DEFAULT       0x00000002UL                               /**< Mode DEFAULT for TXFRONT_INT2CFG            */
#define TXFRONT_INT2CFG_GAINSHIFT_DEFAULT        (_TXFRONT_INT2CFG_GAINSHIFT_DEFAULT << 10) /**< Shifted mode DEFAULT for TXFRONT_INT2CFG    */

/* Bit fields for TXFRONT SRCCFG */
#define _TXFRONT_SRCCFG_RESETVALUE               0x00000002UL                           /**< Default value for TXFRONT_SRCCFG            */
#define _TXFRONT_SRCCFG_MASK                     0x0007FFFFUL                           /**< Mask for TXFRONT_SRCCFG                     */
#define _TXFRONT_SRCCFG_RATIO_SHIFT              0                                      /**< Shift value for TXFRONT_RATIO               */
#define _TXFRONT_SRCCFG_RATIO_MASK               0x7FFFFUL                              /**< Bit mask for TXFRONT_RATIO                  */
#define _TXFRONT_SRCCFG_RATIO_DEFAULT            0x00000002UL                           /**< Mode DEFAULT for TXFRONT_SRCCFG             */
#define TXFRONT_SRCCFG_RATIO_DEFAULT             (_TXFRONT_SRCCFG_RATIO_DEFAULT << 0)   /**< Shifted mode DEFAULT for TXFRONT_SRCCFG     */

/* Bit fields for TXFRONT TXIQIMB */
#define _TXFRONT_TXIQIMB_RESETVALUE              0x00000000UL                            /**< Default value for TXFRONT_TXIQIMB           */
#define _TXFRONT_TXIQIMB_MASK                    0x0FFF0FFFUL                            /**< Mask for TXFRONT_TXIQIMB                    */
#define _TXFRONT_TXIQIMB_EPSILON_SHIFT           0                                       /**< Shift value for TXFRONT_EPSILON             */
#define _TXFRONT_TXIQIMB_EPSILON_MASK            0xFFFUL                                 /**< Bit mask for TXFRONT_EPSILON                */
#define _TXFRONT_TXIQIMB_EPSILON_DEFAULT         0x00000000UL                            /**< Mode DEFAULT for TXFRONT_TXIQIMB            */
#define TXFRONT_TXIQIMB_EPSILON_DEFAULT          (_TXFRONT_TXIQIMB_EPSILON_DEFAULT << 0) /**< Shifted mode DEFAULT for TXFRONT_TXIQIMB    */
#define _TXFRONT_TXIQIMB_PHI_SHIFT               16                                      /**< Shift value for TXFRONT_PHI                 */
#define _TXFRONT_TXIQIMB_PHI_MASK                0xFFF0000UL                             /**< Bit mask for TXFRONT_PHI                    */
#define _TXFRONT_TXIQIMB_PHI_DEFAULT             0x00000000UL                            /**< Mode DEFAULT for TXFRONT_TXIQIMB            */
#define TXFRONT_TXIQIMB_PHI_DEFAULT              (_TXFRONT_TXIQIMB_PHI_DEFAULT << 16)    /**< Shifted mode DEFAULT for TXFRONT_TXIQIMB    */

/* Bit fields for TXFRONT TXDCOFFSET */
#define _TXFRONT_TXDCOFFSET_RESETVALUE           0x00000000UL                                  /**< Default value for TXFRONT_TXDCOFFSET        */
#define _TXFRONT_TXDCOFFSET_MASK                 0x03FF03FFUL                                  /**< Mask for TXFRONT_TXDCOFFSET                 */
#define _TXFRONT_TXDCOFFSET_DCOFFSETI_SHIFT      0                                             /**< Shift value for TXFRONT_DCOFFSETI           */
#define _TXFRONT_TXDCOFFSET_DCOFFSETI_MASK       0x3FFUL                                       /**< Bit mask for TXFRONT_DCOFFSETI              */
#define _TXFRONT_TXDCOFFSET_DCOFFSETI_DEFAULT    0x00000000UL                                  /**< Mode DEFAULT for TXFRONT_TXDCOFFSET         */
#define TXFRONT_TXDCOFFSET_DCOFFSETI_DEFAULT     (_TXFRONT_TXDCOFFSET_DCOFFSETI_DEFAULT << 0)  /**< Shifted mode DEFAULT for TXFRONT_TXDCOFFSET */
#define _TXFRONT_TXDCOFFSET_DCOFFSETQ_SHIFT      16                                            /**< Shift value for TXFRONT_DCOFFSETQ           */
#define _TXFRONT_TXDCOFFSET_DCOFFSETQ_MASK       0x3FF0000UL                                   /**< Bit mask for TXFRONT_DCOFFSETQ              */
#define _TXFRONT_TXDCOFFSET_DCOFFSETQ_DEFAULT    0x00000000UL                                  /**< Mode DEFAULT for TXFRONT_TXDCOFFSET         */
#define TXFRONT_TXDCOFFSET_DCOFFSETQ_DEFAULT     (_TXFRONT_TXDCOFFSET_DCOFFSETQ_DEFAULT << 16) /**< Shifted mode DEFAULT for TXFRONT_TXDCOFFSET */

/* Bit fields for TXFRONT TXRAMPUP */
#define _TXFRONT_TXRAMPUP_RESETVALUE             0x00002088UL                           /**< Default value for TXFRONT_TXRAMPUP          */
#define _TXFRONT_TXRAMPUP_MASK                   0x0001FFFFUL                           /**< Mask for TXFRONT_TXRAMPUP                   */
#define TXFRONT_TXRAMPUP_MODE                    (0x1UL << 0)                           /**< New BitField                                */
#define _TXFRONT_TXRAMPUP_MODE_SHIFT             0                                      /**< Shift value for TXFRONT_MODE                */
#define _TXFRONT_TXRAMPUP_MODE_MASK              0x1UL                                  /**< Bit mask for TXFRONT_MODE                   */
#define _TXFRONT_TXRAMPUP_MODE_DEFAULT           0x00000000UL                           /**< Mode DEFAULT for TXFRONT_TXRAMPUP           */
#define _TXFRONT_TXRAMPUP_MODE_ENABLED           0x00000000UL                           /**< Mode ENABLED for TXFRONT_TXRAMPUP           */
#define _TXFRONT_TXRAMPUP_MODE_DISABLED          0x00000001UL                           /**< Mode DISABLED for TXFRONT_TXRAMPUP          */
#define TXFRONT_TXRAMPUP_MODE_DEFAULT            (_TXFRONT_TXRAMPUP_MODE_DEFAULT << 0)  /**< Shifted mode DEFAULT for TXFRONT_TXRAMPUP   */
#define TXFRONT_TXRAMPUP_MODE_ENABLED            (_TXFRONT_TXRAMPUP_MODE_ENABLED << 0)  /**< Shifted mode ENABLED for TXFRONT_TXRAMPUP   */
#define TXFRONT_TXRAMPUP_MODE_DISABLED           (_TXFRONT_TXRAMPUP_MODE_DISABLED << 0) /**< Shifted mode DISABLED for TXFRONT_TXRAMPUP  */
#define _TXFRONT_TXRAMPUP_DELAY_SHIFT            1                                      /**< Shift value for TXFRONT_DELAY               */
#define _TXFRONT_TXRAMPUP_DELAY_MASK             0x7FEUL                                /**< Bit mask for TXFRONT_DELAY                  */
#define _TXFRONT_TXRAMPUP_DELAY_DEFAULT          0x00000044UL                           /**< Mode DEFAULT for TXFRONT_TXRAMPUP           */
#define TXFRONT_TXRAMPUP_DELAY_DEFAULT           (_TXFRONT_TXRAMPUP_DELAY_DEFAULT << 1) /**< Shifted mode DEFAULT for TXFRONT_TXRAMPUP   */
#define _TXFRONT_TXRAMPUP_STEP_SHIFT             11                                     /**< Shift value for TXFRONT_STEP                */
#define _TXFRONT_TXRAMPUP_STEP_MASK              0x1F800UL                              /**< Bit mask for TXFRONT_STEP                   */
#define _TXFRONT_TXRAMPUP_STEP_DEFAULT           0x00000004UL                           /**< Mode DEFAULT for TXFRONT_TXRAMPUP           */
#define TXFRONT_TXRAMPUP_STEP_DEFAULT            (_TXFRONT_TXRAMPUP_STEP_DEFAULT << 11) /**< Shifted mode DEFAULT for TXFRONT_TXRAMPUP   */

/* Bit fields for TXFRONT TXDCRAMPUP */
#define _TXFRONT_TXDCRAMPUP_RESETVALUE           0x00000000UL                             /**< Default value for TXFRONT_TXDCRAMPUP        */
#define _TXFRONT_TXDCRAMPUP_MASK                 0xFFFFFFFFUL                             /**< Mask for TXFRONT_TXDCRAMPUP                 */
#define _TXFRONT_TXDCRAMPUP_DELAY_SHIFT          0                                        /**< Shift value for TXFRONT_DELAY               */
#define _TXFRONT_TXDCRAMPUP_DELAY_MASK           0x3FFUL                                  /**< Bit mask for TXFRONT_DELAY                  */
#define _TXFRONT_TXDCRAMPUP_DELAY_DEFAULT        0x00000000UL                             /**< Mode DEFAULT for TXFRONT_TXDCRAMPUP         */
#define TXFRONT_TXDCRAMPUP_DELAY_DEFAULT         (_TXFRONT_TXDCRAMPUP_DELAY_DEFAULT << 0) /**< Shifted mode DEFAULT for TXFRONT_TXDCRAMPUP */
#define _TXFRONT_TXDCRAMPUP_DCRI_SHIFT           10                                       /**< Shift value for TXFRONT_DCRI                */
#define _TXFRONT_TXDCRAMPUP_DCRI_MASK            0x1FFC00UL                               /**< Bit mask for TXFRONT_DCRI                   */
#define _TXFRONT_TXDCRAMPUP_DCRI_DEFAULT         0x00000000UL                             /**< Mode DEFAULT for TXFRONT_TXDCRAMPUP         */
#define TXFRONT_TXDCRAMPUP_DCRI_DEFAULT          (_TXFRONT_TXDCRAMPUP_DCRI_DEFAULT << 10) /**< Shifted mode DEFAULT for TXFRONT_TXDCRAMPUP */
#define _TXFRONT_TXDCRAMPUP_DCRQ_SHIFT           21                                       /**< Shift value for TXFRONT_DCRQ                */
#define _TXFRONT_TXDCRAMPUP_DCRQ_MASK            0xFFE00000UL                             /**< Bit mask for TXFRONT_DCRQ                   */
#define _TXFRONT_TXDCRAMPUP_DCRQ_DEFAULT         0x00000000UL                             /**< Mode DEFAULT for TXFRONT_TXDCRAMPUP         */
#define TXFRONT_TXDCRAMPUP_DCRQ_DEFAULT          (_TXFRONT_TXDCRAMPUP_DCRQ_DEFAULT << 21) /**< Shifted mode DEFAULT for TXFRONT_TXDCRAMPUP */

/* Bit fields for TXFRONT TXGAIN */
#define _TXFRONT_TXGAIN_RESETVALUE               0x000001FFUL                           /**< Default value for TXFRONT_TXGAIN            */
#define _TXFRONT_TXGAIN_MASK                     0x000003FFUL                           /**< Mask for TXFRONT_TXGAIN                     */
#define _TXFRONT_TXGAIN_GAINDIG_SHIFT            0                                      /**< Shift value for TXFRONT_GAINDIG             */
#define _TXFRONT_TXGAIN_GAINDIG_MASK             0x3FFUL                                /**< Bit mask for TXFRONT_GAINDIG                */
#define _TXFRONT_TXGAIN_GAINDIG_DEFAULT          0x000001FFUL                           /**< Mode DEFAULT for TXFRONT_TXGAIN             */
#define TXFRONT_TXGAIN_GAINDIG_DEFAULT           (_TXFRONT_TXGAIN_GAINDIG_DEFAULT << 0) /**< Shifted mode DEFAULT for TXFRONT_TXGAIN     */

/* Bit fields for TXFRONT TXCLIP */
#define _TXFRONT_TXCLIP_RESETVALUE               0x080007FFUL                            /**< Default value for TXFRONT_TXCLIP            */
#define _TXFRONT_TXCLIP_MASK                     0x0FFF0FFFUL                            /**< Mask for TXFRONT_TXCLIP                     */
#define _TXFRONT_TXCLIP_CLIPPOS_SHIFT            0                                       /**< Shift value for TXFRONT_CLIPPOS             */
#define _TXFRONT_TXCLIP_CLIPPOS_MASK             0xFFFUL                                 /**< Bit mask for TXFRONT_CLIPPOS                */
#define _TXFRONT_TXCLIP_CLIPPOS_DEFAULT          0x000007FFUL                            /**< Mode DEFAULT for TXFRONT_TXCLIP             */
#define TXFRONT_TXCLIP_CLIPPOS_DEFAULT           (_TXFRONT_TXCLIP_CLIPPOS_DEFAULT << 0)  /**< Shifted mode DEFAULT for TXFRONT_TXCLIP     */
#define _TXFRONT_TXCLIP_CLIPNEG_SHIFT            16                                      /**< Shift value for TXFRONT_CLIPNEG             */
#define _TXFRONT_TXCLIP_CLIPNEG_MASK             0xFFF0000UL                             /**< Bit mask for TXFRONT_CLIPNEG                */
#define _TXFRONT_TXCLIP_CLIPNEG_DEFAULT          0x00000800UL                            /**< Mode DEFAULT for TXFRONT_TXCLIP             */
#define TXFRONT_TXCLIP_CLIPNEG_DEFAULT           (_TXFRONT_TXCLIP_CLIPNEG_DEFAULT << 16) /**< Shifted mode DEFAULT for TXFRONT_TXCLIP     */

/* Bit fields for TXFRONT TXPREDIST */
#define _TXFRONT_TXPREDIST_RESETVALUE            0x00000000UL                               /**< Default value for TXFRONT_TXPREDIST         */
#define _TXFRONT_TXPREDIST_MASK                  0x3FFF3FFFUL                               /**< Mask for TXFRONT_TXPREDIST                  */
#define _TXFRONT_TXPREDIST_BETAAMP_SHIFT         0                                          /**< Shift value for TXFRONT_BETAAMP             */
#define _TXFRONT_TXPREDIST_BETAAMP_MASK          0x3FFFUL                                   /**< Bit mask for TXFRONT_BETAAMP                */
#define _TXFRONT_TXPREDIST_BETAAMP_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for TXFRONT_TXPREDIST          */
#define TXFRONT_TXPREDIST_BETAAMP_DEFAULT        (_TXFRONT_TXPREDIST_BETAAMP_DEFAULT << 0)  /**< Shifted mode DEFAULT for TXFRONT_TXPREDIST  */
#define _TXFRONT_TXPREDIST_BETAPHA_SHIFT         16                                         /**< Shift value for TXFRONT_BETAPHA             */
#define _TXFRONT_TXPREDIST_BETAPHA_MASK          0x3FFF0000UL                               /**< Bit mask for TXFRONT_BETAPHA                */
#define _TXFRONT_TXPREDIST_BETAPHA_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for TXFRONT_TXPREDIST          */
#define TXFRONT_TXPREDIST_BETAPHA_DEFAULT        (_TXFRONT_TXPREDIST_BETAPHA_DEFAULT << 16) /**< Shifted mode DEFAULT for TXFRONT_TXPREDIST  */

/* Bit fields for TXFRONT DAC */
#define _TXFRONT_DAC_RESETVALUE                  0x00000002UL                            /**< Default value for TXFRONT_DAC               */
#define _TXFRONT_DAC_MASK                        0x00000003UL                            /**< Mask for TXFRONT_DAC                        */
#define TXFRONT_DAC_CONNECTTEST                  (0x1UL << 0)                            /**< New BitField                                */
#define _TXFRONT_DAC_CONNECTTEST_SHIFT           0                                       /**< Shift value for TXFRONT_CONNECTTEST         */
#define _TXFRONT_DAC_CONNECTTEST_MASK            0x1UL                                   /**< Bit mask for TXFRONT_CONNECTTEST            */
#define _TXFRONT_DAC_CONNECTTEST_DEFAULT         0x00000000UL                            /**< Mode DEFAULT for TXFRONT_DAC                */
#define _TXFRONT_DAC_CONNECTTEST_NO              0x00000000UL                            /**< Mode NO for TXFRONT_DAC                     */
#define _TXFRONT_DAC_CONNECTTEST_YES             0x00000001UL                            /**< Mode YES for TXFRONT_DAC                    */
#define TXFRONT_DAC_CONNECTTEST_DEFAULT          (_TXFRONT_DAC_CONNECTTEST_DEFAULT << 0) /**< Shifted mode DEFAULT for TXFRONT_DAC        */
#define TXFRONT_DAC_CONNECTTEST_NO               (_TXFRONT_DAC_CONNECTTEST_NO << 0)      /**< Shifted mode NO for TXFRONT_DAC             */
#define TXFRONT_DAC_CONNECTTEST_YES              (_TXFRONT_DAC_CONNECTTEST_YES << 0)     /**< Shifted mode YES for TXFRONT_DAC            */
#define TXFRONT_DAC_DACFORMAT                    (0x1UL << 1)                            /**< New BitField                                */
#define _TXFRONT_DAC_DACFORMAT_SHIFT             1                                       /**< Shift value for TXFRONT_DACFORMAT           */
#define _TXFRONT_DAC_DACFORMAT_MASK              0x2UL                                   /**< Bit mask for TXFRONT_DACFORMAT              */
#define _TXFRONT_DAC_DACFORMAT_DEFAULT           0x00000001UL                            /**< Mode DEFAULT for TXFRONT_DAC                */
#define _TXFRONT_DAC_DACFORMAT_SIGNED            0x00000000UL                            /**< Mode SIGNED for TXFRONT_DAC                 */
#define _TXFRONT_DAC_DACFORMAT_UNSIGNED          0x00000001UL                            /**< Mode UNSIGNED for TXFRONT_DAC               */
#define TXFRONT_DAC_DACFORMAT_DEFAULT            (_TXFRONT_DAC_DACFORMAT_DEFAULT << 1)   /**< Shifted mode DEFAULT for TXFRONT_DAC        */
#define TXFRONT_DAC_DACFORMAT_SIGNED             (_TXFRONT_DAC_DACFORMAT_SIGNED << 1)    /**< Shifted mode SIGNED for TXFRONT_DAC         */
#define TXFRONT_DAC_DACFORMAT_UNSIGNED           (_TXFRONT_DAC_DACFORMAT_UNSIGNED << 1)  /**< Shifted mode UNSIGNED for TXFRONT_DAC       */

/** @} End of group EFR32FG25_TXFRONT_BitFields */
/** @} End of group EFR32FG25_TXFRONT */
/** @} End of group Parts */

#endif /* EFR32FG25_TXFRONT_H */
