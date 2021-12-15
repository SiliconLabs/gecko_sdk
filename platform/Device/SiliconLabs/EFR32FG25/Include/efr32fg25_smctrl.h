/**************************************************************************//**
 * @file
 * @brief EFR32FG25 SMCTRL register and bit field definitions
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
#ifndef EFR32FG25_SMCTRL_H
#define EFR32FG25_SMCTRL_H
#define SMCTRL_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_SMCTRL SMCTRL
 * @{
 * @brief EFR32FG25 SMCTRL Register Declaration.
 *****************************************************************************/

/** SMCTRL Register Declaration. */
typedef struct {
  __IM uint32_t  IPVERSION;                     /**< IP Version ID                                      */
  __IOM uint32_t EN;                            /**< Module Enable                                      */
  __IOM uint32_t SWRST;                         /**< Software Reset                                     */
  uint32_t       RESERVED0[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t MAINIF;                        /**< Main CPU Interrupt Flag                            */
  __IOM uint32_t MAINIEN;                       /**< Main CPU Interrupt Enable                          */
  __IOM uint32_t SEQIF;                         /**< Sequencer's Interrupt Flag                         */
  __IOM uint32_t SEQIEN;                        /**< Seuencer's Interrupt Enable                        */
  __IOM uint32_t SWIF;                          /**< Local SW Interrupt Flag                            */
  __IOM uint32_t SWIEN;                         /**< Local SW Interrupt Enable                          */
  __IOM uint32_t GPREG;                         /**< New Register                                       */
  __IOM uint32_t TIMIF;                         /**< Timer's Interrupt Flag                             */
  __IOM uint32_t TIMIEN;                        /**< Timer's Interrupt Enable                           */
  uint32_t       RESERVED1[51U];                /**< Reserved for future use                            */
  __IOM uint32_t FRCRXCTRL;                     /**< New Register                                       */
  __IOM uint32_t CTRL;                          /**< New Register                                       */
  __IM uint32_t  PC;                            /**< New Register                                       */
  uint32_t       RESERVED2[29U];                /**< Reserved for future use                            */
  __IOM uint32_t SCRATCH0;                      /**< SCRATCH0                                           */
  __IOM uint32_t SCRATCH1;                      /**< SCRATCH1                                           */
  __IOM uint32_t SCRATCH2;                      /**< SCRATCH2                                           */
  __IOM uint32_t SCRATCH3;                      /**< SCRATCH3                                           */
  __IOM uint32_t SCRATCH4;                      /**< SCRATCH4                                           */
  __IOM uint32_t SCRATCH5;                      /**< SCRATCH5                                           */
  __IOM uint32_t SCRATCH6;                      /**< SCRATCH6                                           */
  __IOM uint32_t SCRATCH7;                      /**< SCRATCH7                                           */
  uint32_t       RESERVED3[4U];                 /**< Reserved for future use                            */
  __IOM uint32_t PRSMUXLSB;                     /**< New Register                                       */
  __IOM uint32_t PRSMUXMSB;                     /**< New Register                                       */
  __IOM uint32_t PRSOUT;                        /**< New Register                                       */
  uint32_t       RESERVED4[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t RXEVMUX;                       /**< New Register                                       */
  __IOM uint32_t TIMCTRL;                       /**< New Register                                       */
  __IM uint32_t  TIMSTAT;                       /**< New Register                                       */
  uint32_t       RESERVED5[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t SHIFTS;                        /**< New Register                                       */
  __IOM uint32_t TXDONE;                        /**< New Register                                       */
  uint32_t       RESERVED6[906U];               /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_SET;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_SET;                     /**< Software Reset                                     */
  uint32_t       RESERVED7[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t MAINIF_SET;                    /**< Main CPU Interrupt Flag                            */
  __IOM uint32_t MAINIEN_SET;                   /**< Main CPU Interrupt Enable                          */
  __IOM uint32_t SEQIF_SET;                     /**< Sequencer's Interrupt Flag                         */
  __IOM uint32_t SEQIEN_SET;                    /**< Seuencer's Interrupt Enable                        */
  __IOM uint32_t SWIF_SET;                      /**< Local SW Interrupt Flag                            */
  __IOM uint32_t SWIEN_SET;                     /**< Local SW Interrupt Enable                          */
  __IOM uint32_t GPREG_SET;                     /**< New Register                                       */
  __IOM uint32_t TIMIF_SET;                     /**< Timer's Interrupt Flag                             */
  __IOM uint32_t TIMIEN_SET;                    /**< Timer's Interrupt Enable                           */
  uint32_t       RESERVED8[51U];                /**< Reserved for future use                            */
  __IOM uint32_t FRCRXCTRL_SET;                 /**< New Register                                       */
  __IOM uint32_t CTRL_SET;                      /**< New Register                                       */
  __IM uint32_t  PC_SET;                        /**< New Register                                       */
  uint32_t       RESERVED9[29U];                /**< Reserved for future use                            */
  __IOM uint32_t SCRATCH0_SET;                  /**< SCRATCH0                                           */
  __IOM uint32_t SCRATCH1_SET;                  /**< SCRATCH1                                           */
  __IOM uint32_t SCRATCH2_SET;                  /**< SCRATCH2                                           */
  __IOM uint32_t SCRATCH3_SET;                  /**< SCRATCH3                                           */
  __IOM uint32_t SCRATCH4_SET;                  /**< SCRATCH4                                           */
  __IOM uint32_t SCRATCH5_SET;                  /**< SCRATCH5                                           */
  __IOM uint32_t SCRATCH6_SET;                  /**< SCRATCH6                                           */
  __IOM uint32_t SCRATCH7_SET;                  /**< SCRATCH7                                           */
  uint32_t       RESERVED10[4U];                /**< Reserved for future use                            */
  __IOM uint32_t PRSMUXLSB_SET;                 /**< New Register                                       */
  __IOM uint32_t PRSMUXMSB_SET;                 /**< New Register                                       */
  __IOM uint32_t PRSOUT_SET;                    /**< New Register                                       */
  uint32_t       RESERVED11[1U];                /**< Reserved for future use                            */
  __IOM uint32_t RXEVMUX_SET;                   /**< New Register                                       */
  __IOM uint32_t TIMCTRL_SET;                   /**< New Register                                       */
  __IM uint32_t  TIMSTAT_SET;                   /**< New Register                                       */
  uint32_t       RESERVED12[1U];                /**< Reserved for future use                            */
  __IOM uint32_t SHIFTS_SET;                    /**< New Register                                       */
  __IOM uint32_t TXDONE_SET;                    /**< New Register                                       */
  uint32_t       RESERVED13[906U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_CLR;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_CLR;                     /**< Software Reset                                     */
  uint32_t       RESERVED14[1U];                /**< Reserved for future use                            */
  __IOM uint32_t MAINIF_CLR;                    /**< Main CPU Interrupt Flag                            */
  __IOM uint32_t MAINIEN_CLR;                   /**< Main CPU Interrupt Enable                          */
  __IOM uint32_t SEQIF_CLR;                     /**< Sequencer's Interrupt Flag                         */
  __IOM uint32_t SEQIEN_CLR;                    /**< Seuencer's Interrupt Enable                        */
  __IOM uint32_t SWIF_CLR;                      /**< Local SW Interrupt Flag                            */
  __IOM uint32_t SWIEN_CLR;                     /**< Local SW Interrupt Enable                          */
  __IOM uint32_t GPREG_CLR;                     /**< New Register                                       */
  __IOM uint32_t TIMIF_CLR;                     /**< Timer's Interrupt Flag                             */
  __IOM uint32_t TIMIEN_CLR;                    /**< Timer's Interrupt Enable                           */
  uint32_t       RESERVED15[51U];               /**< Reserved for future use                            */
  __IOM uint32_t FRCRXCTRL_CLR;                 /**< New Register                                       */
  __IOM uint32_t CTRL_CLR;                      /**< New Register                                       */
  __IM uint32_t  PC_CLR;                        /**< New Register                                       */
  uint32_t       RESERVED16[29U];               /**< Reserved for future use                            */
  __IOM uint32_t SCRATCH0_CLR;                  /**< SCRATCH0                                           */
  __IOM uint32_t SCRATCH1_CLR;                  /**< SCRATCH1                                           */
  __IOM uint32_t SCRATCH2_CLR;                  /**< SCRATCH2                                           */
  __IOM uint32_t SCRATCH3_CLR;                  /**< SCRATCH3                                           */
  __IOM uint32_t SCRATCH4_CLR;                  /**< SCRATCH4                                           */
  __IOM uint32_t SCRATCH5_CLR;                  /**< SCRATCH5                                           */
  __IOM uint32_t SCRATCH6_CLR;                  /**< SCRATCH6                                           */
  __IOM uint32_t SCRATCH7_CLR;                  /**< SCRATCH7                                           */
  uint32_t       RESERVED17[4U];                /**< Reserved for future use                            */
  __IOM uint32_t PRSMUXLSB_CLR;                 /**< New Register                                       */
  __IOM uint32_t PRSMUXMSB_CLR;                 /**< New Register                                       */
  __IOM uint32_t PRSOUT_CLR;                    /**< New Register                                       */
  uint32_t       RESERVED18[1U];                /**< Reserved for future use                            */
  __IOM uint32_t RXEVMUX_CLR;                   /**< New Register                                       */
  __IOM uint32_t TIMCTRL_CLR;                   /**< New Register                                       */
  __IM uint32_t  TIMSTAT_CLR;                   /**< New Register                                       */
  uint32_t       RESERVED19[1U];                /**< Reserved for future use                            */
  __IOM uint32_t SHIFTS_CLR;                    /**< New Register                                       */
  __IOM uint32_t TXDONE_CLR;                    /**< New Register                                       */
  uint32_t       RESERVED20[906U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP Version ID                                      */
  __IOM uint32_t EN_TGL;                        /**< Module Enable                                      */
  __IOM uint32_t SWRST_TGL;                     /**< Software Reset                                     */
  uint32_t       RESERVED21[1U];                /**< Reserved for future use                            */
  __IOM uint32_t MAINIF_TGL;                    /**< Main CPU Interrupt Flag                            */
  __IOM uint32_t MAINIEN_TGL;                   /**< Main CPU Interrupt Enable                          */
  __IOM uint32_t SEQIF_TGL;                     /**< Sequencer's Interrupt Flag                         */
  __IOM uint32_t SEQIEN_TGL;                    /**< Seuencer's Interrupt Enable                        */
  __IOM uint32_t SWIF_TGL;                      /**< Local SW Interrupt Flag                            */
  __IOM uint32_t SWIEN_TGL;                     /**< Local SW Interrupt Enable                          */
  __IOM uint32_t GPREG_TGL;                     /**< New Register                                       */
  __IOM uint32_t TIMIF_TGL;                     /**< Timer's Interrupt Flag                             */
  __IOM uint32_t TIMIEN_TGL;                    /**< Timer's Interrupt Enable                           */
  uint32_t       RESERVED22[51U];               /**< Reserved for future use                            */
  __IOM uint32_t FRCRXCTRL_TGL;                 /**< New Register                                       */
  __IOM uint32_t CTRL_TGL;                      /**< New Register                                       */
  __IM uint32_t  PC_TGL;                        /**< New Register                                       */
  uint32_t       RESERVED23[29U];               /**< Reserved for future use                            */
  __IOM uint32_t SCRATCH0_TGL;                  /**< SCRATCH0                                           */
  __IOM uint32_t SCRATCH1_TGL;                  /**< SCRATCH1                                           */
  __IOM uint32_t SCRATCH2_TGL;                  /**< SCRATCH2                                           */
  __IOM uint32_t SCRATCH3_TGL;                  /**< SCRATCH3                                           */
  __IOM uint32_t SCRATCH4_TGL;                  /**< SCRATCH4                                           */
  __IOM uint32_t SCRATCH5_TGL;                  /**< SCRATCH5                                           */
  __IOM uint32_t SCRATCH6_TGL;                  /**< SCRATCH6                                           */
  __IOM uint32_t SCRATCH7_TGL;                  /**< SCRATCH7                                           */
  uint32_t       RESERVED24[4U];                /**< Reserved for future use                            */
  __IOM uint32_t PRSMUXLSB_TGL;                 /**< New Register                                       */
  __IOM uint32_t PRSMUXMSB_TGL;                 /**< New Register                                       */
  __IOM uint32_t PRSOUT_TGL;                    /**< New Register                                       */
  uint32_t       RESERVED25[1U];                /**< Reserved for future use                            */
  __IOM uint32_t RXEVMUX_TGL;                   /**< New Register                                       */
  __IOM uint32_t TIMCTRL_TGL;                   /**< New Register                                       */
  __IM uint32_t  TIMSTAT_TGL;                   /**< New Register                                       */
  uint32_t       RESERVED26[1U];                /**< Reserved for future use                            */
  __IOM uint32_t SHIFTS_TGL;                    /**< New Register                                       */
  __IOM uint32_t TXDONE_TGL;                    /**< New Register                                       */
} SMCTRL_TypeDef;
/** @} End of group EFR32FG25_SMCTRL */

/**************************************************************************//**
 * @addtogroup EFR32FG25_SMCTRL
 * @{
 * @defgroup EFR32FG25_SMCTRL_BitFields SMCTRL Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for SMCTRL IPVERSION */
#define _SMCTRL_IPVERSION_RESETVALUE              0x00000001UL                               /**< Default value for SMCTRL_IPVERSION          */
#define _SMCTRL_IPVERSION_MASK                    0xFFFFFFFFUL                               /**< Mask for SMCTRL_IPVERSION                   */
#define _SMCTRL_IPVERSION_IPVERSION_SHIFT         0                                          /**< Shift value for SMCTRL_IPVERSION            */
#define _SMCTRL_IPVERSION_IPVERSION_MASK          0xFFFFFFFFUL                               /**< Bit mask for SMCTRL_IPVERSION               */
#define _SMCTRL_IPVERSION_IPVERSION_DEFAULT       0x00000001UL                               /**< Mode DEFAULT for SMCTRL_IPVERSION           */
#define SMCTRL_IPVERSION_IPVERSION_DEFAULT        (_SMCTRL_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for SMCTRL_IPVERSION   */

/* Bit fields for SMCTRL EN */
#define _SMCTRL_EN_RESETVALUE                     0x00000000UL                          /**< Default value for SMCTRL_EN                 */
#define _SMCTRL_EN_MASK                           0x00000003UL                          /**< Mask for SMCTRL_EN                          */
#define SMCTRL_EN_EN                              (0x1UL << 0)                          /**< Module Enable                               */
#define _SMCTRL_EN_EN_SHIFT                       0                                     /**< Shift value for SMCTRL_EN                   */
#define _SMCTRL_EN_EN_MASK                        0x1UL                                 /**< Bit mask for SMCTRL_EN                      */
#define _SMCTRL_EN_EN_DEFAULT                     0x00000000UL                          /**< Mode DEFAULT for SMCTRL_EN                  */
#define SMCTRL_EN_EN_DEFAULT                      (_SMCTRL_EN_EN_DEFAULT << 0)          /**< Shifted mode DEFAULT for SMCTRL_EN          */
#define SMCTRL_EN_DISABLING                       (0x1UL << 1)                          /**< Disablement Busy Status                     */
#define _SMCTRL_EN_DISABLING_SHIFT                1                                     /**< Shift value for SMCTRL_DISABLING            */
#define _SMCTRL_EN_DISABLING_MASK                 0x2UL                                 /**< Bit mask for SMCTRL_DISABLING               */
#define _SMCTRL_EN_DISABLING_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_EN                  */
#define SMCTRL_EN_DISABLING_DEFAULT               (_SMCTRL_EN_DISABLING_DEFAULT << 1)   /**< Shifted mode DEFAULT for SMCTRL_EN          */

/* Bit fields for SMCTRL SWRST */
#define _SMCTRL_SWRST_RESETVALUE                  0x00000000UL                               /**< Default value for SMCTRL_SWRST              */
#define _SMCTRL_SWRST_MASK                        0x00000007UL                               /**< Mask for SMCTRL_SWRST                       */
#define SMCTRL_SWRST_SWRST                        (0x1UL << 0)                               /**< Software Reset Command                      */
#define _SMCTRL_SWRST_SWRST_SHIFT                 0                                          /**< Shift value for SMCTRL_SWRST                */
#define _SMCTRL_SWRST_SWRST_MASK                  0x1UL                                      /**< Bit mask for SMCTRL_SWRST                   */
#define _SMCTRL_SWRST_SWRST_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for SMCTRL_SWRST               */
#define SMCTRL_SWRST_SWRST_DEFAULT                (_SMCTRL_SWRST_SWRST_DEFAULT << 0)         /**< Shifted mode DEFAULT for SMCTRL_SWRST       */
#define SMCTRL_SWRST_RESETTING                    (0x1UL << 1)                               /**< Software Reset Busy Status                  */
#define _SMCTRL_SWRST_RESETTING_SHIFT             1                                          /**< Shift value for SMCTRL_RESETTING            */
#define _SMCTRL_SWRST_RESETTING_MASK              0x2UL                                      /**< Bit mask for SMCTRL_RESETTING               */
#define _SMCTRL_SWRST_RESETTING_DEFAULT           0x00000000UL                               /**< Mode DEFAULT for SMCTRL_SWRST               */
#define SMCTRL_SWRST_RESETTING_DEFAULT            (_SMCTRL_SWRST_RESETTING_DEFAULT << 1)     /**< Shifted mode DEFAULT for SMCTRL_SWRST       */
#define SMCTRL_SWRST_COMBRESETTING                (0x1UL << 2)                               /**< Software Reset Busy Status (Combined)       */
#define _SMCTRL_SWRST_COMBRESETTING_SHIFT         2                                          /**< Shift value for SMCTRL_COMBRESETTING        */
#define _SMCTRL_SWRST_COMBRESETTING_MASK          0x4UL                                      /**< Bit mask for SMCTRL_COMBRESETTING           */
#define _SMCTRL_SWRST_COMBRESETTING_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for SMCTRL_SWRST               */
#define SMCTRL_SWRST_COMBRESETTING_DEFAULT        (_SMCTRL_SWRST_COMBRESETTING_DEFAULT << 2) /**< Shifted mode DEFAULT for SMCTRL_SWRST       */

/* Bit fields for SMCTRL MAINIF */
#define _SMCTRL_MAINIF_RESETVALUE                 0x00000000UL                            /**< Default value for SMCTRL_MAINIF             */
#define _SMCTRL_MAINIF_MASK                       0xFFFFFFFFUL                            /**< Mask for SMCTRL_MAINIF                      */
#define SMCTRL_MAINIF_MAINIF0                     (0x1UL << 0)                            /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF0_SHIFT              0                                       /**< Shift value for SMCTRL_MAINIF0              */
#define _SMCTRL_MAINIF_MAINIF0_MASK               0x1UL                                   /**< Bit mask for SMCTRL_MAINIF0                 */
#define _SMCTRL_MAINIF_MAINIF0_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF0_DEFAULT             (_SMCTRL_MAINIF_MAINIF0_DEFAULT << 0)   /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF1                     (0x1UL << 1)                            /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF1_SHIFT              1                                       /**< Shift value for SMCTRL_MAINIF1              */
#define _SMCTRL_MAINIF_MAINIF1_MASK               0x2UL                                   /**< Bit mask for SMCTRL_MAINIF1                 */
#define _SMCTRL_MAINIF_MAINIF1_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF1_DEFAULT             (_SMCTRL_MAINIF_MAINIF1_DEFAULT << 1)   /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF2                     (0x1UL << 2)                            /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF2_SHIFT              2                                       /**< Shift value for SMCTRL_MAINIF2              */
#define _SMCTRL_MAINIF_MAINIF2_MASK               0x4UL                                   /**< Bit mask for SMCTRL_MAINIF2                 */
#define _SMCTRL_MAINIF_MAINIF2_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF2_DEFAULT             (_SMCTRL_MAINIF_MAINIF2_DEFAULT << 2)   /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF3                     (0x1UL << 3)                            /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF3_SHIFT              3                                       /**< Shift value for SMCTRL_MAINIF3              */
#define _SMCTRL_MAINIF_MAINIF3_MASK               0x8UL                                   /**< Bit mask for SMCTRL_MAINIF3                 */
#define _SMCTRL_MAINIF_MAINIF3_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF3_DEFAULT             (_SMCTRL_MAINIF_MAINIF3_DEFAULT << 3)   /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF4                     (0x1UL << 4)                            /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF4_SHIFT              4                                       /**< Shift value for SMCTRL_MAINIF4              */
#define _SMCTRL_MAINIF_MAINIF4_MASK               0x10UL                                  /**< Bit mask for SMCTRL_MAINIF4                 */
#define _SMCTRL_MAINIF_MAINIF4_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF4_DEFAULT             (_SMCTRL_MAINIF_MAINIF4_DEFAULT << 4)   /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF5                     (0x1UL << 5)                            /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF5_SHIFT              5                                       /**< Shift value for SMCTRL_MAINIF5              */
#define _SMCTRL_MAINIF_MAINIF5_MASK               0x20UL                                  /**< Bit mask for SMCTRL_MAINIF5                 */
#define _SMCTRL_MAINIF_MAINIF5_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF5_DEFAULT             (_SMCTRL_MAINIF_MAINIF5_DEFAULT << 5)   /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF6                     (0x1UL << 6)                            /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF6_SHIFT              6                                       /**< Shift value for SMCTRL_MAINIF6              */
#define _SMCTRL_MAINIF_MAINIF6_MASK               0x40UL                                  /**< Bit mask for SMCTRL_MAINIF6                 */
#define _SMCTRL_MAINIF_MAINIF6_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF6_DEFAULT             (_SMCTRL_MAINIF_MAINIF6_DEFAULT << 6)   /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF7                     (0x1UL << 7)                            /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF7_SHIFT              7                                       /**< Shift value for SMCTRL_MAINIF7              */
#define _SMCTRL_MAINIF_MAINIF7_MASK               0x80UL                                  /**< Bit mask for SMCTRL_MAINIF7                 */
#define _SMCTRL_MAINIF_MAINIF7_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF7_DEFAULT             (_SMCTRL_MAINIF_MAINIF7_DEFAULT << 7)   /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF8                     (0x1UL << 8)                            /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF8_SHIFT              8                                       /**< Shift value for SMCTRL_MAINIF8              */
#define _SMCTRL_MAINIF_MAINIF8_MASK               0x100UL                                 /**< Bit mask for SMCTRL_MAINIF8                 */
#define _SMCTRL_MAINIF_MAINIF8_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF8_DEFAULT             (_SMCTRL_MAINIF_MAINIF8_DEFAULT << 8)   /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF9                     (0x1UL << 9)                            /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF9_SHIFT              9                                       /**< Shift value for SMCTRL_MAINIF9              */
#define _SMCTRL_MAINIF_MAINIF9_MASK               0x200UL                                 /**< Bit mask for SMCTRL_MAINIF9                 */
#define _SMCTRL_MAINIF_MAINIF9_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF9_DEFAULT             (_SMCTRL_MAINIF_MAINIF9_DEFAULT << 9)   /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF10                    (0x1UL << 10)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF10_SHIFT             10                                      /**< Shift value for SMCTRL_MAINIF10             */
#define _SMCTRL_MAINIF_MAINIF10_MASK              0x400UL                                 /**< Bit mask for SMCTRL_MAINIF10                */
#define _SMCTRL_MAINIF_MAINIF10_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF10_DEFAULT            (_SMCTRL_MAINIF_MAINIF10_DEFAULT << 10) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF11                    (0x1UL << 11)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF11_SHIFT             11                                      /**< Shift value for SMCTRL_MAINIF11             */
#define _SMCTRL_MAINIF_MAINIF11_MASK              0x800UL                                 /**< Bit mask for SMCTRL_MAINIF11                */
#define _SMCTRL_MAINIF_MAINIF11_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF11_DEFAULT            (_SMCTRL_MAINIF_MAINIF11_DEFAULT << 11) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF12                    (0x1UL << 12)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF12_SHIFT             12                                      /**< Shift value for SMCTRL_MAINIF12             */
#define _SMCTRL_MAINIF_MAINIF12_MASK              0x1000UL                                /**< Bit mask for SMCTRL_MAINIF12                */
#define _SMCTRL_MAINIF_MAINIF12_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF12_DEFAULT            (_SMCTRL_MAINIF_MAINIF12_DEFAULT << 12) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF13                    (0x1UL << 13)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF13_SHIFT             13                                      /**< Shift value for SMCTRL_MAINIF13             */
#define _SMCTRL_MAINIF_MAINIF13_MASK              0x2000UL                                /**< Bit mask for SMCTRL_MAINIF13                */
#define _SMCTRL_MAINIF_MAINIF13_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF13_DEFAULT            (_SMCTRL_MAINIF_MAINIF13_DEFAULT << 13) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF14                    (0x1UL << 14)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF14_SHIFT             14                                      /**< Shift value for SMCTRL_MAINIF14             */
#define _SMCTRL_MAINIF_MAINIF14_MASK              0x4000UL                                /**< Bit mask for SMCTRL_MAINIF14                */
#define _SMCTRL_MAINIF_MAINIF14_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF14_DEFAULT            (_SMCTRL_MAINIF_MAINIF14_DEFAULT << 14) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF15                    (0x1UL << 15)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF15_SHIFT             15                                      /**< Shift value for SMCTRL_MAINIF15             */
#define _SMCTRL_MAINIF_MAINIF15_MASK              0x8000UL                                /**< Bit mask for SMCTRL_MAINIF15                */
#define _SMCTRL_MAINIF_MAINIF15_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF15_DEFAULT            (_SMCTRL_MAINIF_MAINIF15_DEFAULT << 15) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF16                    (0x1UL << 16)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF16_SHIFT             16                                      /**< Shift value for SMCTRL_MAINIF16             */
#define _SMCTRL_MAINIF_MAINIF16_MASK              0x10000UL                               /**< Bit mask for SMCTRL_MAINIF16                */
#define _SMCTRL_MAINIF_MAINIF16_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF16_DEFAULT            (_SMCTRL_MAINIF_MAINIF16_DEFAULT << 16) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF17                    (0x1UL << 17)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF17_SHIFT             17                                      /**< Shift value for SMCTRL_MAINIF17             */
#define _SMCTRL_MAINIF_MAINIF17_MASK              0x20000UL                               /**< Bit mask for SMCTRL_MAINIF17                */
#define _SMCTRL_MAINIF_MAINIF17_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF17_DEFAULT            (_SMCTRL_MAINIF_MAINIF17_DEFAULT << 17) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF18                    (0x1UL << 18)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF18_SHIFT             18                                      /**< Shift value for SMCTRL_MAINIF18             */
#define _SMCTRL_MAINIF_MAINIF18_MASK              0x40000UL                               /**< Bit mask for SMCTRL_MAINIF18                */
#define _SMCTRL_MAINIF_MAINIF18_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF18_DEFAULT            (_SMCTRL_MAINIF_MAINIF18_DEFAULT << 18) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF19                    (0x1UL << 19)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF19_SHIFT             19                                      /**< Shift value for SMCTRL_MAINIF19             */
#define _SMCTRL_MAINIF_MAINIF19_MASK              0x80000UL                               /**< Bit mask for SMCTRL_MAINIF19                */
#define _SMCTRL_MAINIF_MAINIF19_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF19_DEFAULT            (_SMCTRL_MAINIF_MAINIF19_DEFAULT << 19) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF20                    (0x1UL << 20)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF20_SHIFT             20                                      /**< Shift value for SMCTRL_MAINIF20             */
#define _SMCTRL_MAINIF_MAINIF20_MASK              0x100000UL                              /**< Bit mask for SMCTRL_MAINIF20                */
#define _SMCTRL_MAINIF_MAINIF20_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF20_DEFAULT            (_SMCTRL_MAINIF_MAINIF20_DEFAULT << 20) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF21                    (0x1UL << 21)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF21_SHIFT             21                                      /**< Shift value for SMCTRL_MAINIF21             */
#define _SMCTRL_MAINIF_MAINIF21_MASK              0x200000UL                              /**< Bit mask for SMCTRL_MAINIF21                */
#define _SMCTRL_MAINIF_MAINIF21_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF21_DEFAULT            (_SMCTRL_MAINIF_MAINIF21_DEFAULT << 21) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF22                    (0x1UL << 22)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF22_SHIFT             22                                      /**< Shift value for SMCTRL_MAINIF22             */
#define _SMCTRL_MAINIF_MAINIF22_MASK              0x400000UL                              /**< Bit mask for SMCTRL_MAINIF22                */
#define _SMCTRL_MAINIF_MAINIF22_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF22_DEFAULT            (_SMCTRL_MAINIF_MAINIF22_DEFAULT << 22) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF23                    (0x1UL << 23)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF23_SHIFT             23                                      /**< Shift value for SMCTRL_MAINIF23             */
#define _SMCTRL_MAINIF_MAINIF23_MASK              0x800000UL                              /**< Bit mask for SMCTRL_MAINIF23                */
#define _SMCTRL_MAINIF_MAINIF23_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF23_DEFAULT            (_SMCTRL_MAINIF_MAINIF23_DEFAULT << 23) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF24                    (0x1UL << 24)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF24_SHIFT             24                                      /**< Shift value for SMCTRL_MAINIF24             */
#define _SMCTRL_MAINIF_MAINIF24_MASK              0x1000000UL                             /**< Bit mask for SMCTRL_MAINIF24                */
#define _SMCTRL_MAINIF_MAINIF24_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF24_DEFAULT            (_SMCTRL_MAINIF_MAINIF24_DEFAULT << 24) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF25                    (0x1UL << 25)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF25_SHIFT             25                                      /**< Shift value for SMCTRL_MAINIF25             */
#define _SMCTRL_MAINIF_MAINIF25_MASK              0x2000000UL                             /**< Bit mask for SMCTRL_MAINIF25                */
#define _SMCTRL_MAINIF_MAINIF25_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF25_DEFAULT            (_SMCTRL_MAINIF_MAINIF25_DEFAULT << 25) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF26                    (0x1UL << 26)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF26_SHIFT             26                                      /**< Shift value for SMCTRL_MAINIF26             */
#define _SMCTRL_MAINIF_MAINIF26_MASK              0x4000000UL                             /**< Bit mask for SMCTRL_MAINIF26                */
#define _SMCTRL_MAINIF_MAINIF26_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF26_DEFAULT            (_SMCTRL_MAINIF_MAINIF26_DEFAULT << 26) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF27                    (0x1UL << 27)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF27_SHIFT             27                                      /**< Shift value for SMCTRL_MAINIF27             */
#define _SMCTRL_MAINIF_MAINIF27_MASK              0x8000000UL                             /**< Bit mask for SMCTRL_MAINIF27                */
#define _SMCTRL_MAINIF_MAINIF27_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF27_DEFAULT            (_SMCTRL_MAINIF_MAINIF27_DEFAULT << 27) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF28                    (0x1UL << 28)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF28_SHIFT             28                                      /**< Shift value for SMCTRL_MAINIF28             */
#define _SMCTRL_MAINIF_MAINIF28_MASK              0x10000000UL                            /**< Bit mask for SMCTRL_MAINIF28                */
#define _SMCTRL_MAINIF_MAINIF28_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF28_DEFAULT            (_SMCTRL_MAINIF_MAINIF28_DEFAULT << 28) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF29                    (0x1UL << 29)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF29_SHIFT             29                                      /**< Shift value for SMCTRL_MAINIF29             */
#define _SMCTRL_MAINIF_MAINIF29_MASK              0x20000000UL                            /**< Bit mask for SMCTRL_MAINIF29                */
#define _SMCTRL_MAINIF_MAINIF29_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF29_DEFAULT            (_SMCTRL_MAINIF_MAINIF29_DEFAULT << 29) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF30                    (0x1UL << 30)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF30_SHIFT             30                                      /**< Shift value for SMCTRL_MAINIF30             */
#define _SMCTRL_MAINIF_MAINIF30_MASK              0x40000000UL                            /**< Bit mask for SMCTRL_MAINIF30                */
#define _SMCTRL_MAINIF_MAINIF30_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF30_DEFAULT            (_SMCTRL_MAINIF_MAINIF30_DEFAULT << 30) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */
#define SMCTRL_MAINIF_MAINIF31                    (0x1UL << 31)                           /**< Main CPU Interupt Flag                      */
#define _SMCTRL_MAINIF_MAINIF31_SHIFT             31                                      /**< Shift value for SMCTRL_MAINIF31             */
#define _SMCTRL_MAINIF_MAINIF31_MASK              0x80000000UL                            /**< Bit mask for SMCTRL_MAINIF31                */
#define _SMCTRL_MAINIF_MAINIF31_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_MAINIF              */
#define SMCTRL_MAINIF_MAINIF31_DEFAULT            (_SMCTRL_MAINIF_MAINIF31_DEFAULT << 31) /**< Shifted mode DEFAULT for SMCTRL_MAINIF      */

/* Bit fields for SMCTRL MAINIEN */
#define _SMCTRL_MAINIEN_RESETVALUE                0x00000000UL                              /**< Default value for SMCTRL_MAINIEN            */
#define _SMCTRL_MAINIEN_MASK                      0xFFFFFFFFUL                              /**< Mask for SMCTRL_MAINIEN                     */
#define SMCTRL_MAINIEN_MAINIEN0                   (0x1UL << 0)                              /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN0_SHIFT            0                                         /**< Shift value for SMCTRL_MAINIEN0             */
#define _SMCTRL_MAINIEN_MAINIEN0_MASK             0x1UL                                     /**< Bit mask for SMCTRL_MAINIEN0                */
#define _SMCTRL_MAINIEN_MAINIEN0_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN0_DEFAULT           (_SMCTRL_MAINIEN_MAINIEN0_DEFAULT << 0)   /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN1                   (0x1UL << 1)                              /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN1_SHIFT            1                                         /**< Shift value for SMCTRL_MAINIEN1             */
#define _SMCTRL_MAINIEN_MAINIEN1_MASK             0x2UL                                     /**< Bit mask for SMCTRL_MAINIEN1                */
#define _SMCTRL_MAINIEN_MAINIEN1_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN1_DEFAULT           (_SMCTRL_MAINIEN_MAINIEN1_DEFAULT << 1)   /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN2                   (0x1UL << 2)                              /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN2_SHIFT            2                                         /**< Shift value for SMCTRL_MAINIEN2             */
#define _SMCTRL_MAINIEN_MAINIEN2_MASK             0x4UL                                     /**< Bit mask for SMCTRL_MAINIEN2                */
#define _SMCTRL_MAINIEN_MAINIEN2_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN2_DEFAULT           (_SMCTRL_MAINIEN_MAINIEN2_DEFAULT << 2)   /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN3                   (0x1UL << 3)                              /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN3_SHIFT            3                                         /**< Shift value for SMCTRL_MAINIEN3             */
#define _SMCTRL_MAINIEN_MAINIEN3_MASK             0x8UL                                     /**< Bit mask for SMCTRL_MAINIEN3                */
#define _SMCTRL_MAINIEN_MAINIEN3_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN3_DEFAULT           (_SMCTRL_MAINIEN_MAINIEN3_DEFAULT << 3)   /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN4                   (0x1UL << 4)                              /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN4_SHIFT            4                                         /**< Shift value for SMCTRL_MAINIEN4             */
#define _SMCTRL_MAINIEN_MAINIEN4_MASK             0x10UL                                    /**< Bit mask for SMCTRL_MAINIEN4                */
#define _SMCTRL_MAINIEN_MAINIEN4_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN4_DEFAULT           (_SMCTRL_MAINIEN_MAINIEN4_DEFAULT << 4)   /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN5                   (0x1UL << 5)                              /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN5_SHIFT            5                                         /**< Shift value for SMCTRL_MAINIEN5             */
#define _SMCTRL_MAINIEN_MAINIEN5_MASK             0x20UL                                    /**< Bit mask for SMCTRL_MAINIEN5                */
#define _SMCTRL_MAINIEN_MAINIEN5_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN5_DEFAULT           (_SMCTRL_MAINIEN_MAINIEN5_DEFAULT << 5)   /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN6                   (0x1UL << 6)                              /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN6_SHIFT            6                                         /**< Shift value for SMCTRL_MAINIEN6             */
#define _SMCTRL_MAINIEN_MAINIEN6_MASK             0x40UL                                    /**< Bit mask for SMCTRL_MAINIEN6                */
#define _SMCTRL_MAINIEN_MAINIEN6_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN6_DEFAULT           (_SMCTRL_MAINIEN_MAINIEN6_DEFAULT << 6)   /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN7                   (0x1UL << 7)                              /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN7_SHIFT            7                                         /**< Shift value for SMCTRL_MAINIEN7             */
#define _SMCTRL_MAINIEN_MAINIEN7_MASK             0x80UL                                    /**< Bit mask for SMCTRL_MAINIEN7                */
#define _SMCTRL_MAINIEN_MAINIEN7_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN7_DEFAULT           (_SMCTRL_MAINIEN_MAINIEN7_DEFAULT << 7)   /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN8                   (0x1UL << 8)                              /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN8_SHIFT            8                                         /**< Shift value for SMCTRL_MAINIEN8             */
#define _SMCTRL_MAINIEN_MAINIEN8_MASK             0x100UL                                   /**< Bit mask for SMCTRL_MAINIEN8                */
#define _SMCTRL_MAINIEN_MAINIEN8_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN8_DEFAULT           (_SMCTRL_MAINIEN_MAINIEN8_DEFAULT << 8)   /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN9                   (0x1UL << 9)                              /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN9_SHIFT            9                                         /**< Shift value for SMCTRL_MAINIEN9             */
#define _SMCTRL_MAINIEN_MAINIEN9_MASK             0x200UL                                   /**< Bit mask for SMCTRL_MAINIEN9                */
#define _SMCTRL_MAINIEN_MAINIEN9_DEFAULT          0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN9_DEFAULT           (_SMCTRL_MAINIEN_MAINIEN9_DEFAULT << 9)   /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN10                  (0x1UL << 10)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN10_SHIFT           10                                        /**< Shift value for SMCTRL_MAINIEN10            */
#define _SMCTRL_MAINIEN_MAINIEN10_MASK            0x400UL                                   /**< Bit mask for SMCTRL_MAINIEN10               */
#define _SMCTRL_MAINIEN_MAINIEN10_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN10_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN10_DEFAULT << 10) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN11                  (0x1UL << 11)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN11_SHIFT           11                                        /**< Shift value for SMCTRL_MAINIEN11            */
#define _SMCTRL_MAINIEN_MAINIEN11_MASK            0x800UL                                   /**< Bit mask for SMCTRL_MAINIEN11               */
#define _SMCTRL_MAINIEN_MAINIEN11_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN11_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN11_DEFAULT << 11) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN12                  (0x1UL << 12)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN12_SHIFT           12                                        /**< Shift value for SMCTRL_MAINIEN12            */
#define _SMCTRL_MAINIEN_MAINIEN12_MASK            0x1000UL                                  /**< Bit mask for SMCTRL_MAINIEN12               */
#define _SMCTRL_MAINIEN_MAINIEN12_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN12_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN12_DEFAULT << 12) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN13                  (0x1UL << 13)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN13_SHIFT           13                                        /**< Shift value for SMCTRL_MAINIEN13            */
#define _SMCTRL_MAINIEN_MAINIEN13_MASK            0x2000UL                                  /**< Bit mask for SMCTRL_MAINIEN13               */
#define _SMCTRL_MAINIEN_MAINIEN13_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN13_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN13_DEFAULT << 13) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN14                  (0x1UL << 14)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN14_SHIFT           14                                        /**< Shift value for SMCTRL_MAINIEN14            */
#define _SMCTRL_MAINIEN_MAINIEN14_MASK            0x4000UL                                  /**< Bit mask for SMCTRL_MAINIEN14               */
#define _SMCTRL_MAINIEN_MAINIEN14_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN14_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN14_DEFAULT << 14) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN15                  (0x1UL << 15)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN15_SHIFT           15                                        /**< Shift value for SMCTRL_MAINIEN15            */
#define _SMCTRL_MAINIEN_MAINIEN15_MASK            0x8000UL                                  /**< Bit mask for SMCTRL_MAINIEN15               */
#define _SMCTRL_MAINIEN_MAINIEN15_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN15_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN15_DEFAULT << 15) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN16                  (0x1UL << 16)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN16_SHIFT           16                                        /**< Shift value for SMCTRL_MAINIEN16            */
#define _SMCTRL_MAINIEN_MAINIEN16_MASK            0x10000UL                                 /**< Bit mask for SMCTRL_MAINIEN16               */
#define _SMCTRL_MAINIEN_MAINIEN16_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN16_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN16_DEFAULT << 16) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN17                  (0x1UL << 17)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN17_SHIFT           17                                        /**< Shift value for SMCTRL_MAINIEN17            */
#define _SMCTRL_MAINIEN_MAINIEN17_MASK            0x20000UL                                 /**< Bit mask for SMCTRL_MAINIEN17               */
#define _SMCTRL_MAINIEN_MAINIEN17_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN17_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN17_DEFAULT << 17) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN18                  (0x1UL << 18)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN18_SHIFT           18                                        /**< Shift value for SMCTRL_MAINIEN18            */
#define _SMCTRL_MAINIEN_MAINIEN18_MASK            0x40000UL                                 /**< Bit mask for SMCTRL_MAINIEN18               */
#define _SMCTRL_MAINIEN_MAINIEN18_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN18_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN18_DEFAULT << 18) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN19                  (0x1UL << 19)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN19_SHIFT           19                                        /**< Shift value for SMCTRL_MAINIEN19            */
#define _SMCTRL_MAINIEN_MAINIEN19_MASK            0x80000UL                                 /**< Bit mask for SMCTRL_MAINIEN19               */
#define _SMCTRL_MAINIEN_MAINIEN19_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN19_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN19_DEFAULT << 19) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN20                  (0x1UL << 20)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN20_SHIFT           20                                        /**< Shift value for SMCTRL_MAINIEN20            */
#define _SMCTRL_MAINIEN_MAINIEN20_MASK            0x100000UL                                /**< Bit mask for SMCTRL_MAINIEN20               */
#define _SMCTRL_MAINIEN_MAINIEN20_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN20_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN20_DEFAULT << 20) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN21                  (0x1UL << 21)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN21_SHIFT           21                                        /**< Shift value for SMCTRL_MAINIEN21            */
#define _SMCTRL_MAINIEN_MAINIEN21_MASK            0x200000UL                                /**< Bit mask for SMCTRL_MAINIEN21               */
#define _SMCTRL_MAINIEN_MAINIEN21_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN21_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN21_DEFAULT << 21) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN22                  (0x1UL << 22)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN22_SHIFT           22                                        /**< Shift value for SMCTRL_MAINIEN22            */
#define _SMCTRL_MAINIEN_MAINIEN22_MASK            0x400000UL                                /**< Bit mask for SMCTRL_MAINIEN22               */
#define _SMCTRL_MAINIEN_MAINIEN22_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN22_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN22_DEFAULT << 22) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN23                  (0x1UL << 23)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN23_SHIFT           23                                        /**< Shift value for SMCTRL_MAINIEN23            */
#define _SMCTRL_MAINIEN_MAINIEN23_MASK            0x800000UL                                /**< Bit mask for SMCTRL_MAINIEN23               */
#define _SMCTRL_MAINIEN_MAINIEN23_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN23_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN23_DEFAULT << 23) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN24                  (0x1UL << 24)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN24_SHIFT           24                                        /**< Shift value for SMCTRL_MAINIEN24            */
#define _SMCTRL_MAINIEN_MAINIEN24_MASK            0x1000000UL                               /**< Bit mask for SMCTRL_MAINIEN24               */
#define _SMCTRL_MAINIEN_MAINIEN24_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN24_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN24_DEFAULT << 24) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN25                  (0x1UL << 25)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN25_SHIFT           25                                        /**< Shift value for SMCTRL_MAINIEN25            */
#define _SMCTRL_MAINIEN_MAINIEN25_MASK            0x2000000UL                               /**< Bit mask for SMCTRL_MAINIEN25               */
#define _SMCTRL_MAINIEN_MAINIEN25_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN25_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN25_DEFAULT << 25) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN26                  (0x1UL << 26)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN26_SHIFT           26                                        /**< Shift value for SMCTRL_MAINIEN26            */
#define _SMCTRL_MAINIEN_MAINIEN26_MASK            0x4000000UL                               /**< Bit mask for SMCTRL_MAINIEN26               */
#define _SMCTRL_MAINIEN_MAINIEN26_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN26_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN26_DEFAULT << 26) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN27                  (0x1UL << 27)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN27_SHIFT           27                                        /**< Shift value for SMCTRL_MAINIEN27            */
#define _SMCTRL_MAINIEN_MAINIEN27_MASK            0x8000000UL                               /**< Bit mask for SMCTRL_MAINIEN27               */
#define _SMCTRL_MAINIEN_MAINIEN27_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN27_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN27_DEFAULT << 27) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN28                  (0x1UL << 28)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN28_SHIFT           28                                        /**< Shift value for SMCTRL_MAINIEN28            */
#define _SMCTRL_MAINIEN_MAINIEN28_MASK            0x10000000UL                              /**< Bit mask for SMCTRL_MAINIEN28               */
#define _SMCTRL_MAINIEN_MAINIEN28_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN28_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN28_DEFAULT << 28) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN29                  (0x1UL << 29)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN29_SHIFT           29                                        /**< Shift value for SMCTRL_MAINIEN29            */
#define _SMCTRL_MAINIEN_MAINIEN29_MASK            0x20000000UL                              /**< Bit mask for SMCTRL_MAINIEN29               */
#define _SMCTRL_MAINIEN_MAINIEN29_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN29_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN29_DEFAULT << 29) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN30                  (0x1UL << 30)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN30_SHIFT           30                                        /**< Shift value for SMCTRL_MAINIEN30            */
#define _SMCTRL_MAINIEN_MAINIEN30_MASK            0x40000000UL                              /**< Bit mask for SMCTRL_MAINIEN30               */
#define _SMCTRL_MAINIEN_MAINIEN30_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN30_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN30_DEFAULT << 30) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */
#define SMCTRL_MAINIEN_MAINIEN31                  (0x1UL << 31)                             /**< Main CPU Interrupt Enable                   */
#define _SMCTRL_MAINIEN_MAINIEN31_SHIFT           31                                        /**< Shift value for SMCTRL_MAINIEN31            */
#define _SMCTRL_MAINIEN_MAINIEN31_MASK            0x80000000UL                              /**< Bit mask for SMCTRL_MAINIEN31               */
#define _SMCTRL_MAINIEN_MAINIEN31_DEFAULT         0x00000000UL                              /**< Mode DEFAULT for SMCTRL_MAINIEN             */
#define SMCTRL_MAINIEN_MAINIEN31_DEFAULT          (_SMCTRL_MAINIEN_MAINIEN31_DEFAULT << 31) /**< Shifted mode DEFAULT for SMCTRL_MAINIEN     */

/* Bit fields for SMCTRL SEQIF */
#define _SMCTRL_SEQIF_RESETVALUE                  0x00000000UL                          /**< Default value for SMCTRL_SEQIF              */
#define _SMCTRL_SEQIF_MASK                        0xFFFFFFFFUL                          /**< Mask for SMCTRL_SEQIF                       */
#define SMCTRL_SEQIF_SEQIF0                       (0x1UL << 0)                          /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF0_SHIFT                0                                     /**< Shift value for SMCTRL_SEQIF0               */
#define _SMCTRL_SEQIF_SEQIF0_MASK                 0x1UL                                 /**< Bit mask for SMCTRL_SEQIF0                  */
#define _SMCTRL_SEQIF_SEQIF0_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF0_DEFAULT               (_SMCTRL_SEQIF_SEQIF0_DEFAULT << 0)   /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF1                       (0x1UL << 1)                          /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF1_SHIFT                1                                     /**< Shift value for SMCTRL_SEQIF1               */
#define _SMCTRL_SEQIF_SEQIF1_MASK                 0x2UL                                 /**< Bit mask for SMCTRL_SEQIF1                  */
#define _SMCTRL_SEQIF_SEQIF1_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF1_DEFAULT               (_SMCTRL_SEQIF_SEQIF1_DEFAULT << 1)   /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF2                       (0x1UL << 2)                          /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF2_SHIFT                2                                     /**< Shift value for SMCTRL_SEQIF2               */
#define _SMCTRL_SEQIF_SEQIF2_MASK                 0x4UL                                 /**< Bit mask for SMCTRL_SEQIF2                  */
#define _SMCTRL_SEQIF_SEQIF2_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF2_DEFAULT               (_SMCTRL_SEQIF_SEQIF2_DEFAULT << 2)   /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF3                       (0x1UL << 3)                          /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF3_SHIFT                3                                     /**< Shift value for SMCTRL_SEQIF3               */
#define _SMCTRL_SEQIF_SEQIF3_MASK                 0x8UL                                 /**< Bit mask for SMCTRL_SEQIF3                  */
#define _SMCTRL_SEQIF_SEQIF3_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF3_DEFAULT               (_SMCTRL_SEQIF_SEQIF3_DEFAULT << 3)   /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF4                       (0x1UL << 4)                          /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF4_SHIFT                4                                     /**< Shift value for SMCTRL_SEQIF4               */
#define _SMCTRL_SEQIF_SEQIF4_MASK                 0x10UL                                /**< Bit mask for SMCTRL_SEQIF4                  */
#define _SMCTRL_SEQIF_SEQIF4_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF4_DEFAULT               (_SMCTRL_SEQIF_SEQIF4_DEFAULT << 4)   /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF5                       (0x1UL << 5)                          /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF5_SHIFT                5                                     /**< Shift value for SMCTRL_SEQIF5               */
#define _SMCTRL_SEQIF_SEQIF5_MASK                 0x20UL                                /**< Bit mask for SMCTRL_SEQIF5                  */
#define _SMCTRL_SEQIF_SEQIF5_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF5_DEFAULT               (_SMCTRL_SEQIF_SEQIF5_DEFAULT << 5)   /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF6                       (0x1UL << 6)                          /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF6_SHIFT                6                                     /**< Shift value for SMCTRL_SEQIF6               */
#define _SMCTRL_SEQIF_SEQIF6_MASK                 0x40UL                                /**< Bit mask for SMCTRL_SEQIF6                  */
#define _SMCTRL_SEQIF_SEQIF6_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF6_DEFAULT               (_SMCTRL_SEQIF_SEQIF6_DEFAULT << 6)   /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF7                       (0x1UL << 7)                          /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF7_SHIFT                7                                     /**< Shift value for SMCTRL_SEQIF7               */
#define _SMCTRL_SEQIF_SEQIF7_MASK                 0x80UL                                /**< Bit mask for SMCTRL_SEQIF7                  */
#define _SMCTRL_SEQIF_SEQIF7_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF7_DEFAULT               (_SMCTRL_SEQIF_SEQIF7_DEFAULT << 7)   /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF8                       (0x1UL << 8)                          /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF8_SHIFT                8                                     /**< Shift value for SMCTRL_SEQIF8               */
#define _SMCTRL_SEQIF_SEQIF8_MASK                 0x100UL                               /**< Bit mask for SMCTRL_SEQIF8                  */
#define _SMCTRL_SEQIF_SEQIF8_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF8_DEFAULT               (_SMCTRL_SEQIF_SEQIF8_DEFAULT << 8)   /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF9                       (0x1UL << 9)                          /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF9_SHIFT                9                                     /**< Shift value for SMCTRL_SEQIF9               */
#define _SMCTRL_SEQIF_SEQIF9_MASK                 0x200UL                               /**< Bit mask for SMCTRL_SEQIF9                  */
#define _SMCTRL_SEQIF_SEQIF9_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF9_DEFAULT               (_SMCTRL_SEQIF_SEQIF9_DEFAULT << 9)   /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF10                      (0x1UL << 10)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF10_SHIFT               10                                    /**< Shift value for SMCTRL_SEQIF10              */
#define _SMCTRL_SEQIF_SEQIF10_MASK                0x400UL                               /**< Bit mask for SMCTRL_SEQIF10                 */
#define _SMCTRL_SEQIF_SEQIF10_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF10_DEFAULT              (_SMCTRL_SEQIF_SEQIF10_DEFAULT << 10) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF11                      (0x1UL << 11)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF11_SHIFT               11                                    /**< Shift value for SMCTRL_SEQIF11              */
#define _SMCTRL_SEQIF_SEQIF11_MASK                0x800UL                               /**< Bit mask for SMCTRL_SEQIF11                 */
#define _SMCTRL_SEQIF_SEQIF11_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF11_DEFAULT              (_SMCTRL_SEQIF_SEQIF11_DEFAULT << 11) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF12                      (0x1UL << 12)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF12_SHIFT               12                                    /**< Shift value for SMCTRL_SEQIF12              */
#define _SMCTRL_SEQIF_SEQIF12_MASK                0x1000UL                              /**< Bit mask for SMCTRL_SEQIF12                 */
#define _SMCTRL_SEQIF_SEQIF12_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF12_DEFAULT              (_SMCTRL_SEQIF_SEQIF12_DEFAULT << 12) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF13                      (0x1UL << 13)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF13_SHIFT               13                                    /**< Shift value for SMCTRL_SEQIF13              */
#define _SMCTRL_SEQIF_SEQIF13_MASK                0x2000UL                              /**< Bit mask for SMCTRL_SEQIF13                 */
#define _SMCTRL_SEQIF_SEQIF13_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF13_DEFAULT              (_SMCTRL_SEQIF_SEQIF13_DEFAULT << 13) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF14                      (0x1UL << 14)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF14_SHIFT               14                                    /**< Shift value for SMCTRL_SEQIF14              */
#define _SMCTRL_SEQIF_SEQIF14_MASK                0x4000UL                              /**< Bit mask for SMCTRL_SEQIF14                 */
#define _SMCTRL_SEQIF_SEQIF14_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF14_DEFAULT              (_SMCTRL_SEQIF_SEQIF14_DEFAULT << 14) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF15                      (0x1UL << 15)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF15_SHIFT               15                                    /**< Shift value for SMCTRL_SEQIF15              */
#define _SMCTRL_SEQIF_SEQIF15_MASK                0x8000UL                              /**< Bit mask for SMCTRL_SEQIF15                 */
#define _SMCTRL_SEQIF_SEQIF15_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF15_DEFAULT              (_SMCTRL_SEQIF_SEQIF15_DEFAULT << 15) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF16                      (0x1UL << 16)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF16_SHIFT               16                                    /**< Shift value for SMCTRL_SEQIF16              */
#define _SMCTRL_SEQIF_SEQIF16_MASK                0x10000UL                             /**< Bit mask for SMCTRL_SEQIF16                 */
#define _SMCTRL_SEQIF_SEQIF16_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF16_DEFAULT              (_SMCTRL_SEQIF_SEQIF16_DEFAULT << 16) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF17                      (0x1UL << 17)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF17_SHIFT               17                                    /**< Shift value for SMCTRL_SEQIF17              */
#define _SMCTRL_SEQIF_SEQIF17_MASK                0x20000UL                             /**< Bit mask for SMCTRL_SEQIF17                 */
#define _SMCTRL_SEQIF_SEQIF17_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF17_DEFAULT              (_SMCTRL_SEQIF_SEQIF17_DEFAULT << 17) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF18                      (0x1UL << 18)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF18_SHIFT               18                                    /**< Shift value for SMCTRL_SEQIF18              */
#define _SMCTRL_SEQIF_SEQIF18_MASK                0x40000UL                             /**< Bit mask for SMCTRL_SEQIF18                 */
#define _SMCTRL_SEQIF_SEQIF18_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF18_DEFAULT              (_SMCTRL_SEQIF_SEQIF18_DEFAULT << 18) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF19                      (0x1UL << 19)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF19_SHIFT               19                                    /**< Shift value for SMCTRL_SEQIF19              */
#define _SMCTRL_SEQIF_SEQIF19_MASK                0x80000UL                             /**< Bit mask for SMCTRL_SEQIF19                 */
#define _SMCTRL_SEQIF_SEQIF19_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF19_DEFAULT              (_SMCTRL_SEQIF_SEQIF19_DEFAULT << 19) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF20                      (0x1UL << 20)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF20_SHIFT               20                                    /**< Shift value for SMCTRL_SEQIF20              */
#define _SMCTRL_SEQIF_SEQIF20_MASK                0x100000UL                            /**< Bit mask for SMCTRL_SEQIF20                 */
#define _SMCTRL_SEQIF_SEQIF20_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF20_DEFAULT              (_SMCTRL_SEQIF_SEQIF20_DEFAULT << 20) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF21                      (0x1UL << 21)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF21_SHIFT               21                                    /**< Shift value for SMCTRL_SEQIF21              */
#define _SMCTRL_SEQIF_SEQIF21_MASK                0x200000UL                            /**< Bit mask for SMCTRL_SEQIF21                 */
#define _SMCTRL_SEQIF_SEQIF21_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF21_DEFAULT              (_SMCTRL_SEQIF_SEQIF21_DEFAULT << 21) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF22                      (0x1UL << 22)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF22_SHIFT               22                                    /**< Shift value for SMCTRL_SEQIF22              */
#define _SMCTRL_SEQIF_SEQIF22_MASK                0x400000UL                            /**< Bit mask for SMCTRL_SEQIF22                 */
#define _SMCTRL_SEQIF_SEQIF22_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF22_DEFAULT              (_SMCTRL_SEQIF_SEQIF22_DEFAULT << 22) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF23                      (0x1UL << 23)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF23_SHIFT               23                                    /**< Shift value for SMCTRL_SEQIF23              */
#define _SMCTRL_SEQIF_SEQIF23_MASK                0x800000UL                            /**< Bit mask for SMCTRL_SEQIF23                 */
#define _SMCTRL_SEQIF_SEQIF23_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF23_DEFAULT              (_SMCTRL_SEQIF_SEQIF23_DEFAULT << 23) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF24                      (0x1UL << 24)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF24_SHIFT               24                                    /**< Shift value for SMCTRL_SEQIF24              */
#define _SMCTRL_SEQIF_SEQIF24_MASK                0x1000000UL                           /**< Bit mask for SMCTRL_SEQIF24                 */
#define _SMCTRL_SEQIF_SEQIF24_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF24_DEFAULT              (_SMCTRL_SEQIF_SEQIF24_DEFAULT << 24) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF25                      (0x1UL << 25)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF25_SHIFT               25                                    /**< Shift value for SMCTRL_SEQIF25              */
#define _SMCTRL_SEQIF_SEQIF25_MASK                0x2000000UL                           /**< Bit mask for SMCTRL_SEQIF25                 */
#define _SMCTRL_SEQIF_SEQIF25_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF25_DEFAULT              (_SMCTRL_SEQIF_SEQIF25_DEFAULT << 25) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF26                      (0x1UL << 26)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF26_SHIFT               26                                    /**< Shift value for SMCTRL_SEQIF26              */
#define _SMCTRL_SEQIF_SEQIF26_MASK                0x4000000UL                           /**< Bit mask for SMCTRL_SEQIF26                 */
#define _SMCTRL_SEQIF_SEQIF26_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF26_DEFAULT              (_SMCTRL_SEQIF_SEQIF26_DEFAULT << 26) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF27                      (0x1UL << 27)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF27_SHIFT               27                                    /**< Shift value for SMCTRL_SEQIF27              */
#define _SMCTRL_SEQIF_SEQIF27_MASK                0x8000000UL                           /**< Bit mask for SMCTRL_SEQIF27                 */
#define _SMCTRL_SEQIF_SEQIF27_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF27_DEFAULT              (_SMCTRL_SEQIF_SEQIF27_DEFAULT << 27) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF28                      (0x1UL << 28)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF28_SHIFT               28                                    /**< Shift value for SMCTRL_SEQIF28              */
#define _SMCTRL_SEQIF_SEQIF28_MASK                0x10000000UL                          /**< Bit mask for SMCTRL_SEQIF28                 */
#define _SMCTRL_SEQIF_SEQIF28_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF28_DEFAULT              (_SMCTRL_SEQIF_SEQIF28_DEFAULT << 28) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF29                      (0x1UL << 29)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF29_SHIFT               29                                    /**< Shift value for SMCTRL_SEQIF29              */
#define _SMCTRL_SEQIF_SEQIF29_MASK                0x20000000UL                          /**< Bit mask for SMCTRL_SEQIF29                 */
#define _SMCTRL_SEQIF_SEQIF29_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF29_DEFAULT              (_SMCTRL_SEQIF_SEQIF29_DEFAULT << 29) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF30                      (0x1UL << 30)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF30_SHIFT               30                                    /**< Shift value for SMCTRL_SEQIF30              */
#define _SMCTRL_SEQIF_SEQIF30_MASK                0x40000000UL                          /**< Bit mask for SMCTRL_SEQIF30                 */
#define _SMCTRL_SEQIF_SEQIF30_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF30_DEFAULT              (_SMCTRL_SEQIF_SEQIF30_DEFAULT << 30) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */
#define SMCTRL_SEQIF_SEQIF31                      (0x1UL << 31)                         /**< Sequencer Interupt Flag                     */
#define _SMCTRL_SEQIF_SEQIF31_SHIFT               31                                    /**< Shift value for SMCTRL_SEQIF31              */
#define _SMCTRL_SEQIF_SEQIF31_MASK                0x80000000UL                          /**< Bit mask for SMCTRL_SEQIF31                 */
#define _SMCTRL_SEQIF_SEQIF31_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SEQIF               */
#define SMCTRL_SEQIF_SEQIF31_DEFAULT              (_SMCTRL_SEQIF_SEQIF31_DEFAULT << 31) /**< Shifted mode DEFAULT for SMCTRL_SEQIF       */

/* Bit fields for SMCTRL SEQIEN */
#define _SMCTRL_SEQIEN_RESETVALUE                 0x00000000UL                            /**< Default value for SMCTRL_SEQIEN             */
#define _SMCTRL_SEQIEN_MASK                       0xFFFFFFFFUL                            /**< Mask for SMCTRL_SEQIEN                      */
#define SMCTRL_SEQIEN_SEQIEN0                     (0x1UL << 0)                            /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN0_SHIFT              0                                       /**< Shift value for SMCTRL_SEQIEN0              */
#define _SMCTRL_SEQIEN_SEQIEN0_MASK               0x1UL                                   /**< Bit mask for SMCTRL_SEQIEN0                 */
#define _SMCTRL_SEQIEN_SEQIEN0_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN0_DEFAULT             (_SMCTRL_SEQIEN_SEQIEN0_DEFAULT << 0)   /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN1                     (0x1UL << 1)                            /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN1_SHIFT              1                                       /**< Shift value for SMCTRL_SEQIEN1              */
#define _SMCTRL_SEQIEN_SEQIEN1_MASK               0x2UL                                   /**< Bit mask for SMCTRL_SEQIEN1                 */
#define _SMCTRL_SEQIEN_SEQIEN1_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN1_DEFAULT             (_SMCTRL_SEQIEN_SEQIEN1_DEFAULT << 1)   /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN2                     (0x1UL << 2)                            /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN2_SHIFT              2                                       /**< Shift value for SMCTRL_SEQIEN2              */
#define _SMCTRL_SEQIEN_SEQIEN2_MASK               0x4UL                                   /**< Bit mask for SMCTRL_SEQIEN2                 */
#define _SMCTRL_SEQIEN_SEQIEN2_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN2_DEFAULT             (_SMCTRL_SEQIEN_SEQIEN2_DEFAULT << 2)   /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN3                     (0x1UL << 3)                            /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN3_SHIFT              3                                       /**< Shift value for SMCTRL_SEQIEN3              */
#define _SMCTRL_SEQIEN_SEQIEN3_MASK               0x8UL                                   /**< Bit mask for SMCTRL_SEQIEN3                 */
#define _SMCTRL_SEQIEN_SEQIEN3_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN3_DEFAULT             (_SMCTRL_SEQIEN_SEQIEN3_DEFAULT << 3)   /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN4                     (0x1UL << 4)                            /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN4_SHIFT              4                                       /**< Shift value for SMCTRL_SEQIEN4              */
#define _SMCTRL_SEQIEN_SEQIEN4_MASK               0x10UL                                  /**< Bit mask for SMCTRL_SEQIEN4                 */
#define _SMCTRL_SEQIEN_SEQIEN4_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN4_DEFAULT             (_SMCTRL_SEQIEN_SEQIEN4_DEFAULT << 4)   /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN5                     (0x1UL << 5)                            /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN5_SHIFT              5                                       /**< Shift value for SMCTRL_SEQIEN5              */
#define _SMCTRL_SEQIEN_SEQIEN5_MASK               0x20UL                                  /**< Bit mask for SMCTRL_SEQIEN5                 */
#define _SMCTRL_SEQIEN_SEQIEN5_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN5_DEFAULT             (_SMCTRL_SEQIEN_SEQIEN5_DEFAULT << 5)   /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN6                     (0x1UL << 6)                            /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN6_SHIFT              6                                       /**< Shift value for SMCTRL_SEQIEN6              */
#define _SMCTRL_SEQIEN_SEQIEN6_MASK               0x40UL                                  /**< Bit mask for SMCTRL_SEQIEN6                 */
#define _SMCTRL_SEQIEN_SEQIEN6_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN6_DEFAULT             (_SMCTRL_SEQIEN_SEQIEN6_DEFAULT << 6)   /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN7                     (0x1UL << 7)                            /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN7_SHIFT              7                                       /**< Shift value for SMCTRL_SEQIEN7              */
#define _SMCTRL_SEQIEN_SEQIEN7_MASK               0x80UL                                  /**< Bit mask for SMCTRL_SEQIEN7                 */
#define _SMCTRL_SEQIEN_SEQIEN7_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN7_DEFAULT             (_SMCTRL_SEQIEN_SEQIEN7_DEFAULT << 7)   /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN8                     (0x1UL << 8)                            /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN8_SHIFT              8                                       /**< Shift value for SMCTRL_SEQIEN8              */
#define _SMCTRL_SEQIEN_SEQIEN8_MASK               0x100UL                                 /**< Bit mask for SMCTRL_SEQIEN8                 */
#define _SMCTRL_SEQIEN_SEQIEN8_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN8_DEFAULT             (_SMCTRL_SEQIEN_SEQIEN8_DEFAULT << 8)   /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN9                     (0x1UL << 9)                            /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN9_SHIFT              9                                       /**< Shift value for SMCTRL_SEQIEN9              */
#define _SMCTRL_SEQIEN_SEQIEN9_MASK               0x200UL                                 /**< Bit mask for SMCTRL_SEQIEN9                 */
#define _SMCTRL_SEQIEN_SEQIEN9_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN9_DEFAULT             (_SMCTRL_SEQIEN_SEQIEN9_DEFAULT << 9)   /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN10                    (0x1UL << 10)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN10_SHIFT             10                                      /**< Shift value for SMCTRL_SEQIEN10             */
#define _SMCTRL_SEQIEN_SEQIEN10_MASK              0x400UL                                 /**< Bit mask for SMCTRL_SEQIEN10                */
#define _SMCTRL_SEQIEN_SEQIEN10_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN10_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN10_DEFAULT << 10) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN11                    (0x1UL << 11)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN11_SHIFT             11                                      /**< Shift value for SMCTRL_SEQIEN11             */
#define _SMCTRL_SEQIEN_SEQIEN11_MASK              0x800UL                                 /**< Bit mask for SMCTRL_SEQIEN11                */
#define _SMCTRL_SEQIEN_SEQIEN11_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN11_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN11_DEFAULT << 11) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN12                    (0x1UL << 12)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN12_SHIFT             12                                      /**< Shift value for SMCTRL_SEQIEN12             */
#define _SMCTRL_SEQIEN_SEQIEN12_MASK              0x1000UL                                /**< Bit mask for SMCTRL_SEQIEN12                */
#define _SMCTRL_SEQIEN_SEQIEN12_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN12_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN12_DEFAULT << 12) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN13                    (0x1UL << 13)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN13_SHIFT             13                                      /**< Shift value for SMCTRL_SEQIEN13             */
#define _SMCTRL_SEQIEN_SEQIEN13_MASK              0x2000UL                                /**< Bit mask for SMCTRL_SEQIEN13                */
#define _SMCTRL_SEQIEN_SEQIEN13_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN13_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN13_DEFAULT << 13) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN14                    (0x1UL << 14)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN14_SHIFT             14                                      /**< Shift value for SMCTRL_SEQIEN14             */
#define _SMCTRL_SEQIEN_SEQIEN14_MASK              0x4000UL                                /**< Bit mask for SMCTRL_SEQIEN14                */
#define _SMCTRL_SEQIEN_SEQIEN14_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN14_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN14_DEFAULT << 14) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN15                    (0x1UL << 15)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN15_SHIFT             15                                      /**< Shift value for SMCTRL_SEQIEN15             */
#define _SMCTRL_SEQIEN_SEQIEN15_MASK              0x8000UL                                /**< Bit mask for SMCTRL_SEQIEN15                */
#define _SMCTRL_SEQIEN_SEQIEN15_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN15_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN15_DEFAULT << 15) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN16                    (0x1UL << 16)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN16_SHIFT             16                                      /**< Shift value for SMCTRL_SEQIEN16             */
#define _SMCTRL_SEQIEN_SEQIEN16_MASK              0x10000UL                               /**< Bit mask for SMCTRL_SEQIEN16                */
#define _SMCTRL_SEQIEN_SEQIEN16_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN16_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN16_DEFAULT << 16) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN17                    (0x1UL << 17)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN17_SHIFT             17                                      /**< Shift value for SMCTRL_SEQIEN17             */
#define _SMCTRL_SEQIEN_SEQIEN17_MASK              0x20000UL                               /**< Bit mask for SMCTRL_SEQIEN17                */
#define _SMCTRL_SEQIEN_SEQIEN17_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN17_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN17_DEFAULT << 17) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN18                    (0x1UL << 18)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN18_SHIFT             18                                      /**< Shift value for SMCTRL_SEQIEN18             */
#define _SMCTRL_SEQIEN_SEQIEN18_MASK              0x40000UL                               /**< Bit mask for SMCTRL_SEQIEN18                */
#define _SMCTRL_SEQIEN_SEQIEN18_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN18_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN18_DEFAULT << 18) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN19                    (0x1UL << 19)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN19_SHIFT             19                                      /**< Shift value for SMCTRL_SEQIEN19             */
#define _SMCTRL_SEQIEN_SEQIEN19_MASK              0x80000UL                               /**< Bit mask for SMCTRL_SEQIEN19                */
#define _SMCTRL_SEQIEN_SEQIEN19_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN19_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN19_DEFAULT << 19) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN20                    (0x1UL << 20)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN20_SHIFT             20                                      /**< Shift value for SMCTRL_SEQIEN20             */
#define _SMCTRL_SEQIEN_SEQIEN20_MASK              0x100000UL                              /**< Bit mask for SMCTRL_SEQIEN20                */
#define _SMCTRL_SEQIEN_SEQIEN20_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN20_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN20_DEFAULT << 20) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN21                    (0x1UL << 21)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN21_SHIFT             21                                      /**< Shift value for SMCTRL_SEQIEN21             */
#define _SMCTRL_SEQIEN_SEQIEN21_MASK              0x200000UL                              /**< Bit mask for SMCTRL_SEQIEN21                */
#define _SMCTRL_SEQIEN_SEQIEN21_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN21_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN21_DEFAULT << 21) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN22                    (0x1UL << 22)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN22_SHIFT             22                                      /**< Shift value for SMCTRL_SEQIEN22             */
#define _SMCTRL_SEQIEN_SEQIEN22_MASK              0x400000UL                              /**< Bit mask for SMCTRL_SEQIEN22                */
#define _SMCTRL_SEQIEN_SEQIEN22_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN22_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN22_DEFAULT << 22) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN23                    (0x1UL << 23)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN23_SHIFT             23                                      /**< Shift value for SMCTRL_SEQIEN23             */
#define _SMCTRL_SEQIEN_SEQIEN23_MASK              0x800000UL                              /**< Bit mask for SMCTRL_SEQIEN23                */
#define _SMCTRL_SEQIEN_SEQIEN23_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN23_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN23_DEFAULT << 23) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN24                    (0x1UL << 24)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN24_SHIFT             24                                      /**< Shift value for SMCTRL_SEQIEN24             */
#define _SMCTRL_SEQIEN_SEQIEN24_MASK              0x1000000UL                             /**< Bit mask for SMCTRL_SEQIEN24                */
#define _SMCTRL_SEQIEN_SEQIEN24_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN24_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN24_DEFAULT << 24) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN25                    (0x1UL << 25)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN25_SHIFT             25                                      /**< Shift value for SMCTRL_SEQIEN25             */
#define _SMCTRL_SEQIEN_SEQIEN25_MASK              0x2000000UL                             /**< Bit mask for SMCTRL_SEQIEN25                */
#define _SMCTRL_SEQIEN_SEQIEN25_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN25_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN25_DEFAULT << 25) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN26                    (0x1UL << 26)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN26_SHIFT             26                                      /**< Shift value for SMCTRL_SEQIEN26             */
#define _SMCTRL_SEQIEN_SEQIEN26_MASK              0x4000000UL                             /**< Bit mask for SMCTRL_SEQIEN26                */
#define _SMCTRL_SEQIEN_SEQIEN26_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN26_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN26_DEFAULT << 26) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN27                    (0x1UL << 27)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN27_SHIFT             27                                      /**< Shift value for SMCTRL_SEQIEN27             */
#define _SMCTRL_SEQIEN_SEQIEN27_MASK              0x8000000UL                             /**< Bit mask for SMCTRL_SEQIEN27                */
#define _SMCTRL_SEQIEN_SEQIEN27_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN27_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN27_DEFAULT << 27) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN28                    (0x1UL << 28)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN28_SHIFT             28                                      /**< Shift value for SMCTRL_SEQIEN28             */
#define _SMCTRL_SEQIEN_SEQIEN28_MASK              0x10000000UL                            /**< Bit mask for SMCTRL_SEQIEN28                */
#define _SMCTRL_SEQIEN_SEQIEN28_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN28_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN28_DEFAULT << 28) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN29                    (0x1UL << 29)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN29_SHIFT             29                                      /**< Shift value for SMCTRL_SEQIEN29             */
#define _SMCTRL_SEQIEN_SEQIEN29_MASK              0x20000000UL                            /**< Bit mask for SMCTRL_SEQIEN29                */
#define _SMCTRL_SEQIEN_SEQIEN29_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN29_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN29_DEFAULT << 29) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN30                    (0x1UL << 30)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN30_SHIFT             30                                      /**< Shift value for SMCTRL_SEQIEN30             */
#define _SMCTRL_SEQIEN_SEQIEN30_MASK              0x40000000UL                            /**< Bit mask for SMCTRL_SEQIEN30                */
#define _SMCTRL_SEQIEN_SEQIEN30_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN30_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN30_DEFAULT << 30) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */
#define SMCTRL_SEQIEN_SEQIEN31                    (0x1UL << 31)                           /**< Sequencer Interrupt Enable                  */
#define _SMCTRL_SEQIEN_SEQIEN31_SHIFT             31                                      /**< Shift value for SMCTRL_SEQIEN31             */
#define _SMCTRL_SEQIEN_SEQIEN31_MASK              0x80000000UL                            /**< Bit mask for SMCTRL_SEQIEN31                */
#define _SMCTRL_SEQIEN_SEQIEN31_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SEQIEN              */
#define SMCTRL_SEQIEN_SEQIEN31_DEFAULT            (_SMCTRL_SEQIEN_SEQIEN31_DEFAULT << 31) /**< Shifted mode DEFAULT for SMCTRL_SEQIEN      */

/* Bit fields for SMCTRL SWIF */
#define _SMCTRL_SWIF_RESETVALUE                   0x00000000UL                          /**< Default value for SMCTRL_SWIF               */
#define _SMCTRL_SWIF_MASK                         0x000000FFUL                          /**< Mask for SMCTRL_SWIF                        */
#define SMCTRL_SWIF_SWIF0                         (0x1UL << 0)                          /**< Local SW Interupt Flag                      */
#define _SMCTRL_SWIF_SWIF0_SHIFT                  0                                     /**< Shift value for SMCTRL_SWIF0                */
#define _SMCTRL_SWIF_SWIF0_MASK                   0x1UL                                 /**< Bit mask for SMCTRL_SWIF0                   */
#define _SMCTRL_SWIF_SWIF0_DEFAULT                0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SWIF                */
#define SMCTRL_SWIF_SWIF0_DEFAULT                 (_SMCTRL_SWIF_SWIF0_DEFAULT << 0)     /**< Shifted mode DEFAULT for SMCTRL_SWIF        */
#define SMCTRL_SWIF_SWIF1                         (0x1UL << 1)                          /**< Local SW Interupt Flag                      */
#define _SMCTRL_SWIF_SWIF1_SHIFT                  1                                     /**< Shift value for SMCTRL_SWIF1                */
#define _SMCTRL_SWIF_SWIF1_MASK                   0x2UL                                 /**< Bit mask for SMCTRL_SWIF1                   */
#define _SMCTRL_SWIF_SWIF1_DEFAULT                0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SWIF                */
#define SMCTRL_SWIF_SWIF1_DEFAULT                 (_SMCTRL_SWIF_SWIF1_DEFAULT << 1)     /**< Shifted mode DEFAULT for SMCTRL_SWIF        */
#define SMCTRL_SWIF_SWIF2                         (0x1UL << 2)                          /**< Local SW Interupt Flag                      */
#define _SMCTRL_SWIF_SWIF2_SHIFT                  2                                     /**< Shift value for SMCTRL_SWIF2                */
#define _SMCTRL_SWIF_SWIF2_MASK                   0x4UL                                 /**< Bit mask for SMCTRL_SWIF2                   */
#define _SMCTRL_SWIF_SWIF2_DEFAULT                0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SWIF                */
#define SMCTRL_SWIF_SWIF2_DEFAULT                 (_SMCTRL_SWIF_SWIF2_DEFAULT << 2)     /**< Shifted mode DEFAULT for SMCTRL_SWIF        */
#define SMCTRL_SWIF_SWIF3                         (0x1UL << 3)                          /**< Local SW Interupt Flag                      */
#define _SMCTRL_SWIF_SWIF3_SHIFT                  3                                     /**< Shift value for SMCTRL_SWIF3                */
#define _SMCTRL_SWIF_SWIF3_MASK                   0x8UL                                 /**< Bit mask for SMCTRL_SWIF3                   */
#define _SMCTRL_SWIF_SWIF3_DEFAULT                0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SWIF                */
#define SMCTRL_SWIF_SWIF3_DEFAULT                 (_SMCTRL_SWIF_SWIF3_DEFAULT << 3)     /**< Shifted mode DEFAULT for SMCTRL_SWIF        */
#define SMCTRL_SWIF_SWIF4                         (0x1UL << 4)                          /**< Local SW Interupt Flag                      */
#define _SMCTRL_SWIF_SWIF4_SHIFT                  4                                     /**< Shift value for SMCTRL_SWIF4                */
#define _SMCTRL_SWIF_SWIF4_MASK                   0x10UL                                /**< Bit mask for SMCTRL_SWIF4                   */
#define _SMCTRL_SWIF_SWIF4_DEFAULT                0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SWIF                */
#define SMCTRL_SWIF_SWIF4_DEFAULT                 (_SMCTRL_SWIF_SWIF4_DEFAULT << 4)     /**< Shifted mode DEFAULT for SMCTRL_SWIF        */
#define SMCTRL_SWIF_SWIF5                         (0x1UL << 5)                          /**< Local SW Interupt Flag                      */
#define _SMCTRL_SWIF_SWIF5_SHIFT                  5                                     /**< Shift value for SMCTRL_SWIF5                */
#define _SMCTRL_SWIF_SWIF5_MASK                   0x20UL                                /**< Bit mask for SMCTRL_SWIF5                   */
#define _SMCTRL_SWIF_SWIF5_DEFAULT                0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SWIF                */
#define SMCTRL_SWIF_SWIF5_DEFAULT                 (_SMCTRL_SWIF_SWIF5_DEFAULT << 5)     /**< Shifted mode DEFAULT for SMCTRL_SWIF        */
#define SMCTRL_SWIF_SWIF6                         (0x1UL << 6)                          /**< Local SW Interupt Flag                      */
#define _SMCTRL_SWIF_SWIF6_SHIFT                  6                                     /**< Shift value for SMCTRL_SWIF6                */
#define _SMCTRL_SWIF_SWIF6_MASK                   0x40UL                                /**< Bit mask for SMCTRL_SWIF6                   */
#define _SMCTRL_SWIF_SWIF6_DEFAULT                0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SWIF                */
#define SMCTRL_SWIF_SWIF6_DEFAULT                 (_SMCTRL_SWIF_SWIF6_DEFAULT << 6)     /**< Shifted mode DEFAULT for SMCTRL_SWIF        */
#define SMCTRL_SWIF_SWIF7                         (0x1UL << 7)                          /**< Local SW Interupt Flag                      */
#define _SMCTRL_SWIF_SWIF7_SHIFT                  7                                     /**< Shift value for SMCTRL_SWIF7                */
#define _SMCTRL_SWIF_SWIF7_MASK                   0x80UL                                /**< Bit mask for SMCTRL_SWIF7                   */
#define _SMCTRL_SWIF_SWIF7_DEFAULT                0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SWIF                */
#define SMCTRL_SWIF_SWIF7_DEFAULT                 (_SMCTRL_SWIF_SWIF7_DEFAULT << 7)     /**< Shifted mode DEFAULT for SMCTRL_SWIF        */

/* Bit fields for SMCTRL SWIEN */
#define _SMCTRL_SWIEN_RESETVALUE                  0x00000000UL                          /**< Default value for SMCTRL_SWIEN              */
#define _SMCTRL_SWIEN_MASK                        0x000000FFUL                          /**< Mask for SMCTRL_SWIEN                       */
#define SMCTRL_SWIEN_SWIEN0                       (0x1UL << 0)                          /**< Local SW Interrupt Enable                   */
#define _SMCTRL_SWIEN_SWIEN0_SHIFT                0                                     /**< Shift value for SMCTRL_SWIEN0               */
#define _SMCTRL_SWIEN_SWIEN0_MASK                 0x1UL                                 /**< Bit mask for SMCTRL_SWIEN0                  */
#define _SMCTRL_SWIEN_SWIEN0_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SWIEN               */
#define SMCTRL_SWIEN_SWIEN0_DEFAULT               (_SMCTRL_SWIEN_SWIEN0_DEFAULT << 0)   /**< Shifted mode DEFAULT for SMCTRL_SWIEN       */
#define SMCTRL_SWIEN_SWIEN1                       (0x1UL << 1)                          /**< Local SW Interrupt Enable                   */
#define _SMCTRL_SWIEN_SWIEN1_SHIFT                1                                     /**< Shift value for SMCTRL_SWIEN1               */
#define _SMCTRL_SWIEN_SWIEN1_MASK                 0x2UL                                 /**< Bit mask for SMCTRL_SWIEN1                  */
#define _SMCTRL_SWIEN_SWIEN1_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SWIEN               */
#define SMCTRL_SWIEN_SWIEN1_DEFAULT               (_SMCTRL_SWIEN_SWIEN1_DEFAULT << 1)   /**< Shifted mode DEFAULT for SMCTRL_SWIEN       */
#define SMCTRL_SWIEN_SWIEN2                       (0x1UL << 2)                          /**< Local SW Interrupt Enable                   */
#define _SMCTRL_SWIEN_SWIEN2_SHIFT                2                                     /**< Shift value for SMCTRL_SWIEN2               */
#define _SMCTRL_SWIEN_SWIEN2_MASK                 0x4UL                                 /**< Bit mask for SMCTRL_SWIEN2                  */
#define _SMCTRL_SWIEN_SWIEN2_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SWIEN               */
#define SMCTRL_SWIEN_SWIEN2_DEFAULT               (_SMCTRL_SWIEN_SWIEN2_DEFAULT << 2)   /**< Shifted mode DEFAULT for SMCTRL_SWIEN       */
#define SMCTRL_SWIEN_SWIEN3                       (0x1UL << 3)                          /**< Local SW Interrupt Enable                   */
#define _SMCTRL_SWIEN_SWIEN3_SHIFT                3                                     /**< Shift value for SMCTRL_SWIEN3               */
#define _SMCTRL_SWIEN_SWIEN3_MASK                 0x8UL                                 /**< Bit mask for SMCTRL_SWIEN3                  */
#define _SMCTRL_SWIEN_SWIEN3_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SWIEN               */
#define SMCTRL_SWIEN_SWIEN3_DEFAULT               (_SMCTRL_SWIEN_SWIEN3_DEFAULT << 3)   /**< Shifted mode DEFAULT for SMCTRL_SWIEN       */
#define SMCTRL_SWIEN_SWIEN4                       (0x1UL << 4)                          /**< Local SW Interrupt Enable                   */
#define _SMCTRL_SWIEN_SWIEN4_SHIFT                4                                     /**< Shift value for SMCTRL_SWIEN4               */
#define _SMCTRL_SWIEN_SWIEN4_MASK                 0x10UL                                /**< Bit mask for SMCTRL_SWIEN4                  */
#define _SMCTRL_SWIEN_SWIEN4_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SWIEN               */
#define SMCTRL_SWIEN_SWIEN4_DEFAULT               (_SMCTRL_SWIEN_SWIEN4_DEFAULT << 4)   /**< Shifted mode DEFAULT for SMCTRL_SWIEN       */
#define SMCTRL_SWIEN_SWIEN5                       (0x1UL << 5)                          /**< Local SW Interrupt Enable                   */
#define _SMCTRL_SWIEN_SWIEN5_SHIFT                5                                     /**< Shift value for SMCTRL_SWIEN5               */
#define _SMCTRL_SWIEN_SWIEN5_MASK                 0x20UL                                /**< Bit mask for SMCTRL_SWIEN5                  */
#define _SMCTRL_SWIEN_SWIEN5_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SWIEN               */
#define SMCTRL_SWIEN_SWIEN5_DEFAULT               (_SMCTRL_SWIEN_SWIEN5_DEFAULT << 5)   /**< Shifted mode DEFAULT for SMCTRL_SWIEN       */
#define SMCTRL_SWIEN_SWIEN6                       (0x1UL << 6)                          /**< Local SW Interrupt Enable                   */
#define _SMCTRL_SWIEN_SWIEN6_SHIFT                6                                     /**< Shift value for SMCTRL_SWIEN6               */
#define _SMCTRL_SWIEN_SWIEN6_MASK                 0x40UL                                /**< Bit mask for SMCTRL_SWIEN6                  */
#define _SMCTRL_SWIEN_SWIEN6_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SWIEN               */
#define SMCTRL_SWIEN_SWIEN6_DEFAULT               (_SMCTRL_SWIEN_SWIEN6_DEFAULT << 6)   /**< Shifted mode DEFAULT for SMCTRL_SWIEN       */
#define SMCTRL_SWIEN_SWIEN7                       (0x1UL << 7)                          /**< Local SW Interrupt Enable                   */
#define _SMCTRL_SWIEN_SWIEN7_SHIFT                7                                     /**< Shift value for SMCTRL_SWIEN7               */
#define _SMCTRL_SWIEN_SWIEN7_MASK                 0x80UL                                /**< Bit mask for SMCTRL_SWIEN7                  */
#define _SMCTRL_SWIEN_SWIEN7_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_SWIEN               */
#define SMCTRL_SWIEN_SWIEN7_DEFAULT               (_SMCTRL_SWIEN_SWIEN7_DEFAULT << 7)   /**< Shifted mode DEFAULT for SMCTRL_SWIEN       */

/* Bit fields for SMCTRL GPREG */
#define _SMCTRL_GPREG_RESETVALUE                  0x00000000UL                          /**< Default value for SMCTRL_GPREG              */
#define _SMCTRL_GPREG_MASK                        0x0000FFFFUL                          /**< Mask for SMCTRL_GPREG                       */
#define SMCTRL_GPREG_GPREG0                       (0x1UL << 0)                          /**< General Purpose                             */
#define _SMCTRL_GPREG_GPREG0_SHIFT                0                                     /**< Shift value for SMCTRL_GPREG0               */
#define _SMCTRL_GPREG_GPREG0_MASK                 0x1UL                                 /**< Bit mask for SMCTRL_GPREG0                  */
#define _SMCTRL_GPREG_GPREG0_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_GPREG               */
#define SMCTRL_GPREG_GPREG0_DEFAULT               (_SMCTRL_GPREG_GPREG0_DEFAULT << 0)   /**< Shifted mode DEFAULT for SMCTRL_GPREG       */
#define SMCTRL_GPREG_GPREG1                       (0x1UL << 1)                          /**< General Purpose                             */
#define _SMCTRL_GPREG_GPREG1_SHIFT                1                                     /**< Shift value for SMCTRL_GPREG1               */
#define _SMCTRL_GPREG_GPREG1_MASK                 0x2UL                                 /**< Bit mask for SMCTRL_GPREG1                  */
#define _SMCTRL_GPREG_GPREG1_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_GPREG               */
#define SMCTRL_GPREG_GPREG1_DEFAULT               (_SMCTRL_GPREG_GPREG1_DEFAULT << 1)   /**< Shifted mode DEFAULT for SMCTRL_GPREG       */
#define SMCTRL_GPREG_GPREG2                       (0x1UL << 2)                          /**< General Purpose                             */
#define _SMCTRL_GPREG_GPREG2_SHIFT                2                                     /**< Shift value for SMCTRL_GPREG2               */
#define _SMCTRL_GPREG_GPREG2_MASK                 0x4UL                                 /**< Bit mask for SMCTRL_GPREG2                  */
#define _SMCTRL_GPREG_GPREG2_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_GPREG               */
#define SMCTRL_GPREG_GPREG2_DEFAULT               (_SMCTRL_GPREG_GPREG2_DEFAULT << 2)   /**< Shifted mode DEFAULT for SMCTRL_GPREG       */
#define SMCTRL_GPREG_GPREG3                       (0x1UL << 3)                          /**< General Purpose                             */
#define _SMCTRL_GPREG_GPREG3_SHIFT                3                                     /**< Shift value for SMCTRL_GPREG3               */
#define _SMCTRL_GPREG_GPREG3_MASK                 0x8UL                                 /**< Bit mask for SMCTRL_GPREG3                  */
#define _SMCTRL_GPREG_GPREG3_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_GPREG               */
#define SMCTRL_GPREG_GPREG3_DEFAULT               (_SMCTRL_GPREG_GPREG3_DEFAULT << 3)   /**< Shifted mode DEFAULT for SMCTRL_GPREG       */
#define SMCTRL_GPREG_GPREG4                       (0x1UL << 4)                          /**< General Purpose                             */
#define _SMCTRL_GPREG_GPREG4_SHIFT                4                                     /**< Shift value for SMCTRL_GPREG4               */
#define _SMCTRL_GPREG_GPREG4_MASK                 0x10UL                                /**< Bit mask for SMCTRL_GPREG4                  */
#define _SMCTRL_GPREG_GPREG4_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_GPREG               */
#define SMCTRL_GPREG_GPREG4_DEFAULT               (_SMCTRL_GPREG_GPREG4_DEFAULT << 4)   /**< Shifted mode DEFAULT for SMCTRL_GPREG       */
#define SMCTRL_GPREG_GPREG5                       (0x1UL << 5)                          /**< General Purpose                             */
#define _SMCTRL_GPREG_GPREG5_SHIFT                5                                     /**< Shift value for SMCTRL_GPREG5               */
#define _SMCTRL_GPREG_GPREG5_MASK                 0x20UL                                /**< Bit mask for SMCTRL_GPREG5                  */
#define _SMCTRL_GPREG_GPREG5_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_GPREG               */
#define SMCTRL_GPREG_GPREG5_DEFAULT               (_SMCTRL_GPREG_GPREG5_DEFAULT << 5)   /**< Shifted mode DEFAULT for SMCTRL_GPREG       */
#define SMCTRL_GPREG_GPREG6                       (0x1UL << 6)                          /**< General Purpose                             */
#define _SMCTRL_GPREG_GPREG6_SHIFT                6                                     /**< Shift value for SMCTRL_GPREG6               */
#define _SMCTRL_GPREG_GPREG6_MASK                 0x40UL                                /**< Bit mask for SMCTRL_GPREG6                  */
#define _SMCTRL_GPREG_GPREG6_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_GPREG               */
#define SMCTRL_GPREG_GPREG6_DEFAULT               (_SMCTRL_GPREG_GPREG6_DEFAULT << 6)   /**< Shifted mode DEFAULT for SMCTRL_GPREG       */
#define SMCTRL_GPREG_GPREG7                       (0x1UL << 7)                          /**< General Purpose                             */
#define _SMCTRL_GPREG_GPREG7_SHIFT                7                                     /**< Shift value for SMCTRL_GPREG7               */
#define _SMCTRL_GPREG_GPREG7_MASK                 0x80UL                                /**< Bit mask for SMCTRL_GPREG7                  */
#define _SMCTRL_GPREG_GPREG7_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_GPREG               */
#define SMCTRL_GPREG_GPREG7_DEFAULT               (_SMCTRL_GPREG_GPREG7_DEFAULT << 7)   /**< Shifted mode DEFAULT for SMCTRL_GPREG       */
#define SMCTRL_GPREG_GPREG8                       (0x1UL << 8)                          /**< General Purpose                             */
#define _SMCTRL_GPREG_GPREG8_SHIFT                8                                     /**< Shift value for SMCTRL_GPREG8               */
#define _SMCTRL_GPREG_GPREG8_MASK                 0x100UL                               /**< Bit mask for SMCTRL_GPREG8                  */
#define _SMCTRL_GPREG_GPREG8_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_GPREG               */
#define SMCTRL_GPREG_GPREG8_DEFAULT               (_SMCTRL_GPREG_GPREG8_DEFAULT << 8)   /**< Shifted mode DEFAULT for SMCTRL_GPREG       */
#define SMCTRL_GPREG_GPREG9                       (0x1UL << 9)                          /**< General Purpose                             */
#define _SMCTRL_GPREG_GPREG9_SHIFT                9                                     /**< Shift value for SMCTRL_GPREG9               */
#define _SMCTRL_GPREG_GPREG9_MASK                 0x200UL                               /**< Bit mask for SMCTRL_GPREG9                  */
#define _SMCTRL_GPREG_GPREG9_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_GPREG               */
#define SMCTRL_GPREG_GPREG9_DEFAULT               (_SMCTRL_GPREG_GPREG9_DEFAULT << 9)   /**< Shifted mode DEFAULT for SMCTRL_GPREG       */
#define SMCTRL_GPREG_GPREG10                      (0x1UL << 10)                         /**< General Purpose                             */
#define _SMCTRL_GPREG_GPREG10_SHIFT               10                                    /**< Shift value for SMCTRL_GPREG10              */
#define _SMCTRL_GPREG_GPREG10_MASK                0x400UL                               /**< Bit mask for SMCTRL_GPREG10                 */
#define _SMCTRL_GPREG_GPREG10_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_GPREG               */
#define SMCTRL_GPREG_GPREG10_DEFAULT              (_SMCTRL_GPREG_GPREG10_DEFAULT << 10) /**< Shifted mode DEFAULT for SMCTRL_GPREG       */
#define SMCTRL_GPREG_GPREG11                      (0x1UL << 11)                         /**< General Purpose                             */
#define _SMCTRL_GPREG_GPREG11_SHIFT               11                                    /**< Shift value for SMCTRL_GPREG11              */
#define _SMCTRL_GPREG_GPREG11_MASK                0x800UL                               /**< Bit mask for SMCTRL_GPREG11                 */
#define _SMCTRL_GPREG_GPREG11_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_GPREG               */
#define SMCTRL_GPREG_GPREG11_DEFAULT              (_SMCTRL_GPREG_GPREG11_DEFAULT << 11) /**< Shifted mode DEFAULT for SMCTRL_GPREG       */
#define SMCTRL_GPREG_GPREG12                      (0x1UL << 12)                         /**< General Purpose                             */
#define _SMCTRL_GPREG_GPREG12_SHIFT               12                                    /**< Shift value for SMCTRL_GPREG12              */
#define _SMCTRL_GPREG_GPREG12_MASK                0x1000UL                              /**< Bit mask for SMCTRL_GPREG12                 */
#define _SMCTRL_GPREG_GPREG12_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_GPREG               */
#define SMCTRL_GPREG_GPREG12_DEFAULT              (_SMCTRL_GPREG_GPREG12_DEFAULT << 12) /**< Shifted mode DEFAULT for SMCTRL_GPREG       */
#define SMCTRL_GPREG_GPREG13                      (0x1UL << 13)                         /**< General Purpose                             */
#define _SMCTRL_GPREG_GPREG13_SHIFT               13                                    /**< Shift value for SMCTRL_GPREG13              */
#define _SMCTRL_GPREG_GPREG13_MASK                0x2000UL                              /**< Bit mask for SMCTRL_GPREG13                 */
#define _SMCTRL_GPREG_GPREG13_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_GPREG               */
#define SMCTRL_GPREG_GPREG13_DEFAULT              (_SMCTRL_GPREG_GPREG13_DEFAULT << 13) /**< Shifted mode DEFAULT for SMCTRL_GPREG       */
#define SMCTRL_GPREG_GPREG14                      (0x1UL << 14)                         /**< General Purpose                             */
#define _SMCTRL_GPREG_GPREG14_SHIFT               14                                    /**< Shift value for SMCTRL_GPREG14              */
#define _SMCTRL_GPREG_GPREG14_MASK                0x4000UL                              /**< Bit mask for SMCTRL_GPREG14                 */
#define _SMCTRL_GPREG_GPREG14_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_GPREG               */
#define SMCTRL_GPREG_GPREG14_DEFAULT              (_SMCTRL_GPREG_GPREG14_DEFAULT << 14) /**< Shifted mode DEFAULT for SMCTRL_GPREG       */
#define SMCTRL_GPREG_GPREG15                      (0x1UL << 15)                         /**< General Purpose                             */
#define _SMCTRL_GPREG_GPREG15_SHIFT               15                                    /**< Shift value for SMCTRL_GPREG15              */
#define _SMCTRL_GPREG_GPREG15_MASK                0x8000UL                              /**< Bit mask for SMCTRL_GPREG15                 */
#define _SMCTRL_GPREG_GPREG15_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_GPREG               */
#define SMCTRL_GPREG_GPREG15_DEFAULT              (_SMCTRL_GPREG_GPREG15_DEFAULT << 15) /**< Shifted mode DEFAULT for SMCTRL_GPREG       */

/* Bit fields for SMCTRL TIMIF */
#define _SMCTRL_TIMIF_RESETVALUE                  0x00000000UL                          /**< Default value for SMCTRL_TIMIF              */
#define _SMCTRL_TIMIF_MASK                        0x00000001UL                          /**< Mask for SMCTRL_TIMIF                       */
#define SMCTRL_TIMIF_TIMIF0                       (0x1UL << 0)                          /**< Timer Interupt Flag                         */
#define _SMCTRL_TIMIF_TIMIF0_SHIFT                0                                     /**< Shift value for SMCTRL_TIMIF0               */
#define _SMCTRL_TIMIF_TIMIF0_MASK                 0x1UL                                 /**< Bit mask for SMCTRL_TIMIF0                  */
#define _SMCTRL_TIMIF_TIMIF0_DEFAULT              0x00000000UL                          /**< Mode DEFAULT for SMCTRL_TIMIF               */
#define SMCTRL_TIMIF_TIMIF0_DEFAULT               (_SMCTRL_TIMIF_TIMIF0_DEFAULT << 0)   /**< Shifted mode DEFAULT for SMCTRL_TIMIF       */

/* Bit fields for SMCTRL TIMIEN */
#define _SMCTRL_TIMIEN_RESETVALUE                 0x00000000UL                          /**< Default value for SMCTRL_TIMIEN             */
#define _SMCTRL_TIMIEN_MASK                       0x00000001UL                          /**< Mask for SMCTRL_TIMIEN                      */
#define SMCTRL_TIMIEN_TIMIEN0                     (0x1UL << 0)                          /**< Timer Interrupt Enable                      */
#define _SMCTRL_TIMIEN_TIMIEN0_SHIFT              0                                     /**< Shift value for SMCTRL_TIMIEN0              */
#define _SMCTRL_TIMIEN_TIMIEN0_MASK               0x1UL                                 /**< Bit mask for SMCTRL_TIMIEN0                 */
#define _SMCTRL_TIMIEN_TIMIEN0_DEFAULT            0x00000000UL                          /**< Mode DEFAULT for SMCTRL_TIMIEN              */
#define SMCTRL_TIMIEN_TIMIEN0_DEFAULT             (_SMCTRL_TIMIEN_TIMIEN0_DEFAULT << 0) /**< Shifted mode DEFAULT for SMCTRL_TIMIEN      */

/* Bit fields for SMCTRL FRCRXCTRL */
#define _SMCTRL_FRCRXCTRL_RESETVALUE              0x00000000UL                                  /**< Default value for SMCTRL_FRCRXCTRL          */
#define _SMCTRL_FRCRXCTRL_MASK                    0x00000003UL                                  /**< Mask for SMCTRL_FRCRXCTRL                   */
#define SMCTRL_FRCRXCTRL_FDETFALLEDGE             (0x1UL << 0)                                  /**< New BitField                                */
#define _SMCTRL_FRCRXCTRL_FDETFALLEDGE_SHIFT      0                                             /**< Shift value for SMCTRL_FDETFALLEDGE         */
#define _SMCTRL_FRCRXCTRL_FDETFALLEDGE_MASK       0x1UL                                         /**< Bit mask for SMCTRL_FDETFALLEDGE            */
#define _SMCTRL_FRCRXCTRL_FDETFALLEDGE_DEFAULT    0x00000000UL                                  /**< Mode DEFAULT for SMCTRL_FRCRXCTRL           */
#define _SMCTRL_FRCRXCTRL_FDETFALLEDGE_DISABLE    0x00000000UL                                  /**< Mode DISABLE for SMCTRL_FRCRXCTRL           */
#define _SMCTRL_FRCRXCTRL_FDETFALLEDGE_ENABLE     0x00000001UL                                  /**< Mode ENABLE for SMCTRL_FRCRXCTRL            */
#define SMCTRL_FRCRXCTRL_FDETFALLEDGE_DEFAULT     (_SMCTRL_FRCRXCTRL_FDETFALLEDGE_DEFAULT << 0) /**< Shifted mode DEFAULT for SMCTRL_FRCRXCTRL   */
#define SMCTRL_FRCRXCTRL_FDETFALLEDGE_DISABLE     (_SMCTRL_FRCRXCTRL_FDETFALLEDGE_DISABLE << 0) /**< Shifted mode DISABLE for SMCTRL_FRCRXCTRL   */
#define SMCTRL_FRCRXCTRL_FDETFALLEDGE_ENABLE      (_SMCTRL_FRCRXCTRL_FDETFALLEDGE_ENABLE << 0)  /**< Shifted mode ENABLE for SMCTRL_FRCRXCTRL    */
#define SMCTRL_FRCRXCTRL_FDETCLR                  (0x1UL << 1)                                  /**< New BitField                                */
#define _SMCTRL_FRCRXCTRL_FDETCLR_SHIFT           1                                             /**< Shift value for SMCTRL_FDETCLR              */
#define _SMCTRL_FRCRXCTRL_FDETCLR_MASK            0x2UL                                         /**< Bit mask for SMCTRL_FDETCLR                 */
#define _SMCTRL_FRCRXCTRL_FDETCLR_DEFAULT         0x00000000UL                                  /**< Mode DEFAULT for SMCTRL_FRCRXCTRL           */
#define SMCTRL_FRCRXCTRL_FDETCLR_DEFAULT          (_SMCTRL_FRCRXCTRL_FDETCLR_DEFAULT << 1)      /**< Shifted mode DEFAULT for SMCTRL_FRCRXCTRL   */

/* Bit fields for SMCTRL CTRL */
#define _SMCTRL_CTRL_RESETVALUE                   0x0003FF00UL                                /**< Default value for SMCTRL_CTRL               */
#define _SMCTRL_CTRL_MASK                         0x0FFFFFFFUL                                /**< Mask for SMCTRL_CTRL                        */
#define SMCTRL_CTRL_FETCHEN                       (0x1UL << 0)                                /**< New BitField                                */
#define _SMCTRL_CTRL_FETCHEN_SHIFT                0                                           /**< Shift value for SMCTRL_FETCHEN              */
#define _SMCTRL_CTRL_FETCHEN_MASK                 0x1UL                                       /**< Bit mask for SMCTRL_FETCHEN                 */
#define _SMCTRL_CTRL_FETCHEN_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for SMCTRL_CTRL                */
#define SMCTRL_CTRL_FETCHEN_DEFAULT               (_SMCTRL_CTRL_FETCHEN_DEFAULT << 0)         /**< Shifted mode DEFAULT for SMCTRL_CTRL        */
#define SMCTRL_CTRL_FEFILT0INPUTSEL               (0x1UL << 1)                                /**< New BitField                                */
#define _SMCTRL_CTRL_FEFILT0INPUTSEL_SHIFT        1                                           /**< Shift value for SMCTRL_FEFILT0INPUTSEL      */
#define _SMCTRL_CTRL_FEFILT0INPUTSEL_MASK         0x2UL                                       /**< Bit mask for SMCTRL_FEFILT0INPUTSEL         */
#define _SMCTRL_CTRL_FEFILT0INPUTSEL_DEFAULT      0x00000000UL                                /**< Mode DEFAULT for SMCTRL_CTRL                */
#define SMCTRL_CTRL_FEFILT0INPUTSEL_DEFAULT       (_SMCTRL_CTRL_FEFILT0INPUTSEL_DEFAULT << 1) /**< Shifted mode DEFAULT for SMCTRL_CTRL        */
#define SMCTRL_CTRL_IRCAL0SEL                     (0x1UL << 2)                                /**< New BitField                                */
#define _SMCTRL_CTRL_IRCAL0SEL_SHIFT              2                                           /**< Shift value for SMCTRL_IRCAL0SEL            */
#define _SMCTRL_CTRL_IRCAL0SEL_MASK               0x4UL                                       /**< Bit mask for SMCTRL_IRCAL0SEL               */
#define _SMCTRL_CTRL_IRCAL0SEL_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for SMCTRL_CTRL                */
#define SMCTRL_CTRL_IRCAL0SEL_DEFAULT             (_SMCTRL_CTRL_IRCAL0SEL_DEFAULT << 2)       /**< Shifted mode DEFAULT for SMCTRL_CTRL        */
#define SMCTRL_CTRL_IRCAL1SEL                     (0x1UL << 3)                                /**< New BitField                                */
#define _SMCTRL_CTRL_IRCAL1SEL_SHIFT              3                                           /**< Shift value for SMCTRL_IRCAL1SEL            */
#define _SMCTRL_CTRL_IRCAL1SEL_MASK               0x8UL                                       /**< Bit mask for SMCTRL_IRCAL1SEL               */
#define _SMCTRL_CTRL_IRCAL1SEL_DEFAULT            0x00000000UL                                /**< Mode DEFAULT for SMCTRL_CTRL                */
#define SMCTRL_CTRL_IRCAL1SEL_DEFAULT             (_SMCTRL_CTRL_IRCAL1SEL_DEFAULT << 3)       /**< Shifted mode DEFAULT for SMCTRL_CTRL        */
#define SMCTRL_CTRL_RISCVSSRESETREQ               (0x1UL << 4)                                /**< New BitField                                */
#define _SMCTRL_CTRL_RISCVSSRESETREQ_SHIFT        4                                           /**< Shift value for SMCTRL_RISCVSSRESETREQ      */
#define _SMCTRL_CTRL_RISCVSSRESETREQ_MASK         0x10UL                                      /**< Bit mask for SMCTRL_RISCVSSRESETREQ         */
#define _SMCTRL_CTRL_RISCVSSRESETREQ_DEFAULT      0x00000000UL                                /**< Mode DEFAULT for SMCTRL_CTRL                */
#define SMCTRL_CTRL_RISCVSSRESETREQ_DEFAULT       (_SMCTRL_CTRL_RISCVSSRESETREQ_DEFAULT << 4) /**< Shifted mode DEFAULT for SMCTRL_CTRL        */
#define SMCTRL_CTRL_RISCVSSRESETACK               (0x1UL << 5)                                /**< New BitField                                */
#define _SMCTRL_CTRL_RISCVSSRESETACK_SHIFT        5                                           /**< Shift value for SMCTRL_RISCVSSRESETACK      */
#define _SMCTRL_CTRL_RISCVSSRESETACK_MASK         0x20UL                                      /**< Bit mask for SMCTRL_RISCVSSRESETACK         */
#define _SMCTRL_CTRL_RISCVSSRESETACK_DEFAULT      0x00000000UL                                /**< Mode DEFAULT for SMCTRL_CTRL                */
#define SMCTRL_CTRL_RISCVSSRESETACK_DEFAULT       (_SMCTRL_CTRL_RISCVSSRESETACK_DEFAULT << 5) /**< Shifted mode DEFAULT for SMCTRL_CTRL        */
#define SMCTRL_CTRL_ECA0INPUTSEL                  (0x1UL << 6)                                /**< New BitField                                */
#define _SMCTRL_CTRL_ECA0INPUTSEL_SHIFT           6                                           /**< Shift value for SMCTRL_ECA0INPUTSEL         */
#define _SMCTRL_CTRL_ECA0INPUTSEL_MASK            0x40UL                                      /**< Bit mask for SMCTRL_ECA0INPUTSEL            */
#define _SMCTRL_CTRL_ECA0INPUTSEL_DEFAULT         0x00000000UL                                /**< Mode DEFAULT for SMCTRL_CTRL                */
#define SMCTRL_CTRL_ECA0INPUTSEL_DEFAULT          (_SMCTRL_CTRL_ECA0INPUTSEL_DEFAULT << 6)    /**< Shifted mode DEFAULT for SMCTRL_CTRL        */
#define SMCTRL_CTRL_ECA1INPUTSEL                  (0x1UL << 7)                                /**< New BitField                                */
#define _SMCTRL_CTRL_ECA1INPUTSEL_SHIFT           7                                           /**< Shift value for SMCTRL_ECA1INPUTSEL         */
#define _SMCTRL_CTRL_ECA1INPUTSEL_MASK            0x80UL                                      /**< Bit mask for SMCTRL_ECA1INPUTSEL            */
#define _SMCTRL_CTRL_ECA1INPUTSEL_DEFAULT         0x00000000UL                                /**< Mode DEFAULT for SMCTRL_CTRL                */
#define SMCTRL_CTRL_ECA1INPUTSEL_DEFAULT          (_SMCTRL_CTRL_ECA1INPUTSEL_DEFAULT << 7)    /**< Shifted mode DEFAULT for SMCTRL_CTRL        */
#define _SMCTRL_CTRL_RXF1TIMEREN_SHIFT            8                                           /**< Shift value for SMCTRL_RXF1TIMEREN          */
#define _SMCTRL_CTRL_RXF1TIMEREN_MASK             0x3FF00UL                                   /**< Bit mask for SMCTRL_RXF1TIMEREN             */
#define _SMCTRL_CTRL_RXF1TIMEREN_DEFAULT          0x000003FFUL                                /**< Mode DEFAULT for SMCTRL_CTRL                */
#define SMCTRL_CTRL_RXF1TIMEREN_DEFAULT           (_SMCTRL_CTRL_RXF1TIMEREN_DEFAULT << 8)     /**< Shifted mode DEFAULT for SMCTRL_CTRL        */
#define _SMCTRL_CTRL_RXF2TIMEREN_SHIFT            18                                          /**< Shift value for SMCTRL_RXF2TIMEREN          */
#define _SMCTRL_CTRL_RXF2TIMEREN_MASK             0xFFC0000UL                                 /**< Bit mask for SMCTRL_RXF2TIMEREN             */
#define _SMCTRL_CTRL_RXF2TIMEREN_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for SMCTRL_CTRL                */
#define SMCTRL_CTRL_RXF2TIMEREN_DEFAULT           (_SMCTRL_CTRL_RXF2TIMEREN_DEFAULT << 18)    /**< Shifted mode DEFAULT for SMCTRL_CTRL        */

/* Bit fields for SMCTRL PC */
#define _SMCTRL_PC_RESETVALUE                     0x00000000UL                          /**< Default value for SMCTRL_PC                 */
#define _SMCTRL_PC_MASK                           0xFFFFFFFFUL                          /**< Mask for SMCTRL_PC                          */
#define _SMCTRL_PC_PC_SHIFT                       0                                     /**< Shift value for SMCTRL_PC                   */
#define _SMCTRL_PC_PC_MASK                        0xFFFFFFFFUL                          /**< Bit mask for SMCTRL_PC                      */
#define _SMCTRL_PC_PC_DEFAULT                     0x00000000UL                          /**< Mode DEFAULT for SMCTRL_PC                  */
#define SMCTRL_PC_PC_DEFAULT                      (_SMCTRL_PC_PC_DEFAULT << 0)          /**< Shifted mode DEFAULT for SMCTRL_PC          */

/* Bit fields for SMCTRL SCRATCH0 */
#define _SMCTRL_SCRATCH0_RESETVALUE               0x00000000UL                             /**< Default value for SMCTRL_SCRATCH0           */
#define _SMCTRL_SCRATCH0_MASK                     0xFFFFFFFFUL                             /**< Mask for SMCTRL_SCRATCH0                    */
#define _SMCTRL_SCRATCH0_SCRATCH0_SHIFT           0                                        /**< Shift value for SMCTRL_SCRATCH0             */
#define _SMCTRL_SCRATCH0_SCRATCH0_MASK            0xFFFFFFFFUL                             /**< Bit mask for SMCTRL_SCRATCH0                */
#define _SMCTRL_SCRATCH0_SCRATCH0_DEFAULT         0x00000000UL                             /**< Mode DEFAULT for SMCTRL_SCRATCH0            */
#define SMCTRL_SCRATCH0_SCRATCH0_DEFAULT          (_SMCTRL_SCRATCH0_SCRATCH0_DEFAULT << 0) /**< Shifted mode DEFAULT for SMCTRL_SCRATCH0    */

/* Bit fields for SMCTRL SCRATCH1 */
#define _SMCTRL_SCRATCH1_RESETVALUE               0x00000000UL                             /**< Default value for SMCTRL_SCRATCH1           */
#define _SMCTRL_SCRATCH1_MASK                     0xFFFFFFFFUL                             /**< Mask for SMCTRL_SCRATCH1                    */
#define _SMCTRL_SCRATCH1_SCRATCH1_SHIFT           0                                        /**< Shift value for SMCTRL_SCRATCH1             */
#define _SMCTRL_SCRATCH1_SCRATCH1_MASK            0xFFFFFFFFUL                             /**< Bit mask for SMCTRL_SCRATCH1                */
#define _SMCTRL_SCRATCH1_SCRATCH1_DEFAULT         0x00000000UL                             /**< Mode DEFAULT for SMCTRL_SCRATCH1            */
#define SMCTRL_SCRATCH1_SCRATCH1_DEFAULT          (_SMCTRL_SCRATCH1_SCRATCH1_DEFAULT << 0) /**< Shifted mode DEFAULT for SMCTRL_SCRATCH1    */

/* Bit fields for SMCTRL SCRATCH2 */
#define _SMCTRL_SCRATCH2_RESETVALUE               0x00000000UL                             /**< Default value for SMCTRL_SCRATCH2           */
#define _SMCTRL_SCRATCH2_MASK                     0xFFFFFFFFUL                             /**< Mask for SMCTRL_SCRATCH2                    */
#define _SMCTRL_SCRATCH2_SCRATCH2_SHIFT           0                                        /**< Shift value for SMCTRL_SCRATCH2             */
#define _SMCTRL_SCRATCH2_SCRATCH2_MASK            0xFFFFFFFFUL                             /**< Bit mask for SMCTRL_SCRATCH2                */
#define _SMCTRL_SCRATCH2_SCRATCH2_DEFAULT         0x00000000UL                             /**< Mode DEFAULT for SMCTRL_SCRATCH2            */
#define SMCTRL_SCRATCH2_SCRATCH2_DEFAULT          (_SMCTRL_SCRATCH2_SCRATCH2_DEFAULT << 0) /**< Shifted mode DEFAULT for SMCTRL_SCRATCH2    */

/* Bit fields for SMCTRL SCRATCH3 */
#define _SMCTRL_SCRATCH3_RESETVALUE               0x00000000UL                             /**< Default value for SMCTRL_SCRATCH3           */
#define _SMCTRL_SCRATCH3_MASK                     0xFFFFFFFFUL                             /**< Mask for SMCTRL_SCRATCH3                    */
#define _SMCTRL_SCRATCH3_SCRATCH3_SHIFT           0                                        /**< Shift value for SMCTRL_SCRATCH3             */
#define _SMCTRL_SCRATCH3_SCRATCH3_MASK            0xFFFFFFFFUL                             /**< Bit mask for SMCTRL_SCRATCH3                */
#define _SMCTRL_SCRATCH3_SCRATCH3_DEFAULT         0x00000000UL                             /**< Mode DEFAULT for SMCTRL_SCRATCH3            */
#define SMCTRL_SCRATCH3_SCRATCH3_DEFAULT          (_SMCTRL_SCRATCH3_SCRATCH3_DEFAULT << 0) /**< Shifted mode DEFAULT for SMCTRL_SCRATCH3    */

/* Bit fields for SMCTRL SCRATCH4 */
#define _SMCTRL_SCRATCH4_RESETVALUE               0x00000000UL                             /**< Default value for SMCTRL_SCRATCH4           */
#define _SMCTRL_SCRATCH4_MASK                     0xFFFFFFFFUL                             /**< Mask for SMCTRL_SCRATCH4                    */
#define _SMCTRL_SCRATCH4_SCRATCH4_SHIFT           0                                        /**< Shift value for SMCTRL_SCRATCH4             */
#define _SMCTRL_SCRATCH4_SCRATCH4_MASK            0xFFFFFFFFUL                             /**< Bit mask for SMCTRL_SCRATCH4                */
#define _SMCTRL_SCRATCH4_SCRATCH4_DEFAULT         0x00000000UL                             /**< Mode DEFAULT for SMCTRL_SCRATCH4            */
#define SMCTRL_SCRATCH4_SCRATCH4_DEFAULT          (_SMCTRL_SCRATCH4_SCRATCH4_DEFAULT << 0) /**< Shifted mode DEFAULT for SMCTRL_SCRATCH4    */

/* Bit fields for SMCTRL SCRATCH5 */
#define _SMCTRL_SCRATCH5_RESETVALUE               0x00000000UL                             /**< Default value for SMCTRL_SCRATCH5           */
#define _SMCTRL_SCRATCH5_MASK                     0xFFFFFFFFUL                             /**< Mask for SMCTRL_SCRATCH5                    */
#define _SMCTRL_SCRATCH5_SCRATCH5_SHIFT           0                                        /**< Shift value for SMCTRL_SCRATCH5             */
#define _SMCTRL_SCRATCH5_SCRATCH5_MASK            0xFFFFFFFFUL                             /**< Bit mask for SMCTRL_SCRATCH5                */
#define _SMCTRL_SCRATCH5_SCRATCH5_DEFAULT         0x00000000UL                             /**< Mode DEFAULT for SMCTRL_SCRATCH5            */
#define SMCTRL_SCRATCH5_SCRATCH5_DEFAULT          (_SMCTRL_SCRATCH5_SCRATCH5_DEFAULT << 0) /**< Shifted mode DEFAULT for SMCTRL_SCRATCH5    */

/* Bit fields for SMCTRL SCRATCH6 */
#define _SMCTRL_SCRATCH6_RESETVALUE               0x00000000UL                             /**< Default value for SMCTRL_SCRATCH6           */
#define _SMCTRL_SCRATCH6_MASK                     0xFFFFFFFFUL                             /**< Mask for SMCTRL_SCRATCH6                    */
#define _SMCTRL_SCRATCH6_SCRATCH6_SHIFT           0                                        /**< Shift value for SMCTRL_SCRATCH6             */
#define _SMCTRL_SCRATCH6_SCRATCH6_MASK            0xFFFFFFFFUL                             /**< Bit mask for SMCTRL_SCRATCH6                */
#define _SMCTRL_SCRATCH6_SCRATCH6_DEFAULT         0x00000000UL                             /**< Mode DEFAULT for SMCTRL_SCRATCH6            */
#define SMCTRL_SCRATCH6_SCRATCH6_DEFAULT          (_SMCTRL_SCRATCH6_SCRATCH6_DEFAULT << 0) /**< Shifted mode DEFAULT for SMCTRL_SCRATCH6    */

/* Bit fields for SMCTRL SCRATCH7 */
#define _SMCTRL_SCRATCH7_RESETVALUE               0x00000000UL                             /**< Default value for SMCTRL_SCRATCH7           */
#define _SMCTRL_SCRATCH7_MASK                     0xFFFFFFFFUL                             /**< Mask for SMCTRL_SCRATCH7                    */
#define _SMCTRL_SCRATCH7_SCRATCH7_SHIFT           0                                        /**< Shift value for SMCTRL_SCRATCH7             */
#define _SMCTRL_SCRATCH7_SCRATCH7_MASK            0xFFFFFFFFUL                             /**< Bit mask for SMCTRL_SCRATCH7                */
#define _SMCTRL_SCRATCH7_SCRATCH7_DEFAULT         0x00000000UL                             /**< Mode DEFAULT for SMCTRL_SCRATCH7            */
#define SMCTRL_SCRATCH7_SCRATCH7_DEFAULT          (_SMCTRL_SCRATCH7_SCRATCH7_DEFAULT << 0) /**< Shifted mode DEFAULT for SMCTRL_SCRATCH7    */

/* Bit fields for SMCTRL PRSMUXLSB */
#define _SMCTRL_PRSMUXLSB_RESETVALUE              0x00000000UL                                 /**< Default value for SMCTRL_PRSMUXLSB          */
#define _SMCTRL_PRSMUXLSB_MASK                    0x00FFFFFFUL                                 /**< Mask for SMCTRL_PRSMUXLSB                   */
#define _SMCTRL_PRSMUXLSB_PRSMUXLSB0_SHIFT        0                                            /**< Shift value for SMCTRL_PRSMUXLSB0           */
#define _SMCTRL_PRSMUXLSB_PRSMUXLSB0_MASK         0xFUL                                        /**< Bit mask for SMCTRL_PRSMUXLSB0              */
#define _SMCTRL_PRSMUXLSB_PRSMUXLSB0_DEFAULT      0x00000000UL                                 /**< Mode DEFAULT for SMCTRL_PRSMUXLSB           */
#define SMCTRL_PRSMUXLSB_PRSMUXLSB0_DEFAULT       (_SMCTRL_PRSMUXLSB_PRSMUXLSB0_DEFAULT << 0)  /**< Shifted mode DEFAULT for SMCTRL_PRSMUXLSB   */
#define _SMCTRL_PRSMUXLSB_PRSMUXLSB1_SHIFT        4                                            /**< Shift value for SMCTRL_PRSMUXLSB1           */
#define _SMCTRL_PRSMUXLSB_PRSMUXLSB1_MASK         0xF0UL                                       /**< Bit mask for SMCTRL_PRSMUXLSB1              */
#define _SMCTRL_PRSMUXLSB_PRSMUXLSB1_DEFAULT      0x00000000UL                                 /**< Mode DEFAULT for SMCTRL_PRSMUXLSB           */
#define SMCTRL_PRSMUXLSB_PRSMUXLSB1_DEFAULT       (_SMCTRL_PRSMUXLSB_PRSMUXLSB1_DEFAULT << 4)  /**< Shifted mode DEFAULT for SMCTRL_PRSMUXLSB   */
#define _SMCTRL_PRSMUXLSB_PRSMUXLSB2_SHIFT        8                                            /**< Shift value for SMCTRL_PRSMUXLSB2           */
#define _SMCTRL_PRSMUXLSB_PRSMUXLSB2_MASK         0xF00UL                                      /**< Bit mask for SMCTRL_PRSMUXLSB2              */
#define _SMCTRL_PRSMUXLSB_PRSMUXLSB2_DEFAULT      0x00000000UL                                 /**< Mode DEFAULT for SMCTRL_PRSMUXLSB           */
#define SMCTRL_PRSMUXLSB_PRSMUXLSB2_DEFAULT       (_SMCTRL_PRSMUXLSB_PRSMUXLSB2_DEFAULT << 8)  /**< Shifted mode DEFAULT for SMCTRL_PRSMUXLSB   */
#define _SMCTRL_PRSMUXLSB_PRSMUXLSB3_SHIFT        12                                           /**< Shift value for SMCTRL_PRSMUXLSB3           */
#define _SMCTRL_PRSMUXLSB_PRSMUXLSB3_MASK         0xF000UL                                     /**< Bit mask for SMCTRL_PRSMUXLSB3              */
#define _SMCTRL_PRSMUXLSB_PRSMUXLSB3_DEFAULT      0x00000000UL                                 /**< Mode DEFAULT for SMCTRL_PRSMUXLSB           */
#define SMCTRL_PRSMUXLSB_PRSMUXLSB3_DEFAULT       (_SMCTRL_PRSMUXLSB_PRSMUXLSB3_DEFAULT << 12) /**< Shifted mode DEFAULT for SMCTRL_PRSMUXLSB   */
#define _SMCTRL_PRSMUXLSB_PRSMUXLSB4_SHIFT        16                                           /**< Shift value for SMCTRL_PRSMUXLSB4           */
#define _SMCTRL_PRSMUXLSB_PRSMUXLSB4_MASK         0xF0000UL                                    /**< Bit mask for SMCTRL_PRSMUXLSB4              */
#define _SMCTRL_PRSMUXLSB_PRSMUXLSB4_DEFAULT      0x00000000UL                                 /**< Mode DEFAULT for SMCTRL_PRSMUXLSB           */
#define SMCTRL_PRSMUXLSB_PRSMUXLSB4_DEFAULT       (_SMCTRL_PRSMUXLSB_PRSMUXLSB4_DEFAULT << 16) /**< Shifted mode DEFAULT for SMCTRL_PRSMUXLSB   */
#define _SMCTRL_PRSMUXLSB_PRSMUXLSB5_SHIFT        20                                           /**< Shift value for SMCTRL_PRSMUXLSB5           */
#define _SMCTRL_PRSMUXLSB_PRSMUXLSB5_MASK         0xF00000UL                                   /**< Bit mask for SMCTRL_PRSMUXLSB5              */
#define _SMCTRL_PRSMUXLSB_PRSMUXLSB5_DEFAULT      0x00000000UL                                 /**< Mode DEFAULT for SMCTRL_PRSMUXLSB           */
#define SMCTRL_PRSMUXLSB_PRSMUXLSB5_DEFAULT       (_SMCTRL_PRSMUXLSB_PRSMUXLSB5_DEFAULT << 20) /**< Shifted mode DEFAULT for SMCTRL_PRSMUXLSB   */

/* Bit fields for SMCTRL PRSMUXMSB */
#define _SMCTRL_PRSMUXMSB_RESETVALUE              0x00000000UL                                 /**< Default value for SMCTRL_PRSMUXMSB          */
#define _SMCTRL_PRSMUXMSB_MASK                    0x00FFFFFFUL                                 /**< Mask for SMCTRL_PRSMUXMSB                   */
#define _SMCTRL_PRSMUXMSB_PRSMUXMSB0_SHIFT        0                                            /**< Shift value for SMCTRL_PRSMUXMSB0           */
#define _SMCTRL_PRSMUXMSB_PRSMUXMSB0_MASK         0xFUL                                        /**< Bit mask for SMCTRL_PRSMUXMSB0              */
#define _SMCTRL_PRSMUXMSB_PRSMUXMSB0_DEFAULT      0x00000000UL                                 /**< Mode DEFAULT for SMCTRL_PRSMUXMSB           */
#define SMCTRL_PRSMUXMSB_PRSMUXMSB0_DEFAULT       (_SMCTRL_PRSMUXMSB_PRSMUXMSB0_DEFAULT << 0)  /**< Shifted mode DEFAULT for SMCTRL_PRSMUXMSB   */
#define _SMCTRL_PRSMUXMSB_PRSMUXMSB1_SHIFT        4                                            /**< Shift value for SMCTRL_PRSMUXMSB1           */
#define _SMCTRL_PRSMUXMSB_PRSMUXMSB1_MASK         0xF0UL                                       /**< Bit mask for SMCTRL_PRSMUXMSB1              */
#define _SMCTRL_PRSMUXMSB_PRSMUXMSB1_DEFAULT      0x00000000UL                                 /**< Mode DEFAULT for SMCTRL_PRSMUXMSB           */
#define SMCTRL_PRSMUXMSB_PRSMUXMSB1_DEFAULT       (_SMCTRL_PRSMUXMSB_PRSMUXMSB1_DEFAULT << 4)  /**< Shifted mode DEFAULT for SMCTRL_PRSMUXMSB   */
#define _SMCTRL_PRSMUXMSB_PRSMUXMSB2_SHIFT        8                                            /**< Shift value for SMCTRL_PRSMUXMSB2           */
#define _SMCTRL_PRSMUXMSB_PRSMUXMSB2_MASK         0xF00UL                                      /**< Bit mask for SMCTRL_PRSMUXMSB2              */
#define _SMCTRL_PRSMUXMSB_PRSMUXMSB2_DEFAULT      0x00000000UL                                 /**< Mode DEFAULT for SMCTRL_PRSMUXMSB           */
#define SMCTRL_PRSMUXMSB_PRSMUXMSB2_DEFAULT       (_SMCTRL_PRSMUXMSB_PRSMUXMSB2_DEFAULT << 8)  /**< Shifted mode DEFAULT for SMCTRL_PRSMUXMSB   */
#define _SMCTRL_PRSMUXMSB_PRSMUXMSB3_SHIFT        12                                           /**< Shift value for SMCTRL_PRSMUXMSB3           */
#define _SMCTRL_PRSMUXMSB_PRSMUXMSB3_MASK         0xF000UL                                     /**< Bit mask for SMCTRL_PRSMUXMSB3              */
#define _SMCTRL_PRSMUXMSB_PRSMUXMSB3_DEFAULT      0x00000000UL                                 /**< Mode DEFAULT for SMCTRL_PRSMUXMSB           */
#define SMCTRL_PRSMUXMSB_PRSMUXMSB3_DEFAULT       (_SMCTRL_PRSMUXMSB_PRSMUXMSB3_DEFAULT << 12) /**< Shifted mode DEFAULT for SMCTRL_PRSMUXMSB   */
#define _SMCTRL_PRSMUXMSB_PRSMUXMSB4_SHIFT        16                                           /**< Shift value for SMCTRL_PRSMUXMSB4           */
#define _SMCTRL_PRSMUXMSB_PRSMUXMSB4_MASK         0xF0000UL                                    /**< Bit mask for SMCTRL_PRSMUXMSB4              */
#define _SMCTRL_PRSMUXMSB_PRSMUXMSB4_DEFAULT      0x00000000UL                                 /**< Mode DEFAULT for SMCTRL_PRSMUXMSB           */
#define SMCTRL_PRSMUXMSB_PRSMUXMSB4_DEFAULT       (_SMCTRL_PRSMUXMSB_PRSMUXMSB4_DEFAULT << 16) /**< Shifted mode DEFAULT for SMCTRL_PRSMUXMSB   */
#define _SMCTRL_PRSMUXMSB_PRSMUXMSB5_SHIFT        20                                           /**< Shift value for SMCTRL_PRSMUXMSB5           */
#define _SMCTRL_PRSMUXMSB_PRSMUXMSB5_MASK         0xF00000UL                                   /**< Bit mask for SMCTRL_PRSMUXMSB5              */
#define _SMCTRL_PRSMUXMSB_PRSMUXMSB5_DEFAULT      0x00000000UL                                 /**< Mode DEFAULT for SMCTRL_PRSMUXMSB           */
#define SMCTRL_PRSMUXMSB_PRSMUXMSB5_DEFAULT       (_SMCTRL_PRSMUXMSB_PRSMUXMSB5_DEFAULT << 20) /**< Shifted mode DEFAULT for SMCTRL_PRSMUXMSB   */

/* Bit fields for SMCTRL PRSOUT */
#define _SMCTRL_PRSOUT_RESETVALUE                 0x00000000UL                            /**< Default value for SMCTRL_PRSOUT             */
#define _SMCTRL_PRSOUT_MASK                       0x00FFFFFFUL                            /**< Mask for SMCTRL_PRSOUT                      */
#define _SMCTRL_PRSOUT_PRSOUT0_SHIFT              0                                       /**< Shift value for SMCTRL_PRSOUT0              */
#define _SMCTRL_PRSOUT_PRSOUT0_MASK               0x3UL                                   /**< Bit mask for SMCTRL_PRSOUT0                 */
#define _SMCTRL_PRSOUT_PRSOUT0_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT0_IDLE               0x00000000UL                            /**< Mode IDLE for SMCTRL_PRSOUT                 */
#define _SMCTRL_PRSOUT_PRSOUT0_SIGSYNC            0x00000001UL                            /**< Mode SIGSYNC for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT0_SIGTOG             0x00000002UL                            /**< Mode SIGTOG for SMCTRL_PRSOUT               */
#define _SMCTRL_PRSOUT_PRSOUT0_GPREG              0x00000003UL                            /**< Mode GPREG for SMCTRL_PRSOUT                */
#define SMCTRL_PRSOUT_PRSOUT0_DEFAULT             (_SMCTRL_PRSOUT_PRSOUT0_DEFAULT << 0)   /**< Shifted mode DEFAULT for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT0_IDLE                (_SMCTRL_PRSOUT_PRSOUT0_IDLE << 0)      /**< Shifted mode IDLE for SMCTRL_PRSOUT         */
#define SMCTRL_PRSOUT_PRSOUT0_SIGSYNC             (_SMCTRL_PRSOUT_PRSOUT0_SIGSYNC << 0)   /**< Shifted mode SIGSYNC for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT0_SIGTOG              (_SMCTRL_PRSOUT_PRSOUT0_SIGTOG << 0)    /**< Shifted mode SIGTOG for SMCTRL_PRSOUT       */
#define SMCTRL_PRSOUT_PRSOUT0_GPREG               (_SMCTRL_PRSOUT_PRSOUT0_GPREG << 0)     /**< Shifted mode GPREG for SMCTRL_PRSOUT        */
#define _SMCTRL_PRSOUT_PRSOUT1_SHIFT              2                                       /**< Shift value for SMCTRL_PRSOUT1              */
#define _SMCTRL_PRSOUT_PRSOUT1_MASK               0xCUL                                   /**< Bit mask for SMCTRL_PRSOUT1                 */
#define _SMCTRL_PRSOUT_PRSOUT1_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT1_IDLE               0x00000000UL                            /**< Mode IDLE for SMCTRL_PRSOUT                 */
#define _SMCTRL_PRSOUT_PRSOUT1_SIGSYNC            0x00000001UL                            /**< Mode SIGSYNC for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT1_SIGTOG             0x00000002UL                            /**< Mode SIGTOG for SMCTRL_PRSOUT               */
#define _SMCTRL_PRSOUT_PRSOUT1_GPREG              0x00000003UL                            /**< Mode GPREG for SMCTRL_PRSOUT                */
#define SMCTRL_PRSOUT_PRSOUT1_DEFAULT             (_SMCTRL_PRSOUT_PRSOUT1_DEFAULT << 2)   /**< Shifted mode DEFAULT for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT1_IDLE                (_SMCTRL_PRSOUT_PRSOUT1_IDLE << 2)      /**< Shifted mode IDLE for SMCTRL_PRSOUT         */
#define SMCTRL_PRSOUT_PRSOUT1_SIGSYNC             (_SMCTRL_PRSOUT_PRSOUT1_SIGSYNC << 2)   /**< Shifted mode SIGSYNC for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT1_SIGTOG              (_SMCTRL_PRSOUT_PRSOUT1_SIGTOG << 2)    /**< Shifted mode SIGTOG for SMCTRL_PRSOUT       */
#define SMCTRL_PRSOUT_PRSOUT1_GPREG               (_SMCTRL_PRSOUT_PRSOUT1_GPREG << 2)     /**< Shifted mode GPREG for SMCTRL_PRSOUT        */
#define _SMCTRL_PRSOUT_PRSOUT2_SHIFT              4                                       /**< Shift value for SMCTRL_PRSOUT2              */
#define _SMCTRL_PRSOUT_PRSOUT2_MASK               0x30UL                                  /**< Bit mask for SMCTRL_PRSOUT2                 */
#define _SMCTRL_PRSOUT_PRSOUT2_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT2_IDLE               0x00000000UL                            /**< Mode IDLE for SMCTRL_PRSOUT                 */
#define _SMCTRL_PRSOUT_PRSOUT2_SIGSYNC            0x00000001UL                            /**< Mode SIGSYNC for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT2_SIGTOG             0x00000002UL                            /**< Mode SIGTOG for SMCTRL_PRSOUT               */
#define _SMCTRL_PRSOUT_PRSOUT2_GPREG              0x00000003UL                            /**< Mode GPREG for SMCTRL_PRSOUT                */
#define SMCTRL_PRSOUT_PRSOUT2_DEFAULT             (_SMCTRL_PRSOUT_PRSOUT2_DEFAULT << 4)   /**< Shifted mode DEFAULT for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT2_IDLE                (_SMCTRL_PRSOUT_PRSOUT2_IDLE << 4)      /**< Shifted mode IDLE for SMCTRL_PRSOUT         */
#define SMCTRL_PRSOUT_PRSOUT2_SIGSYNC             (_SMCTRL_PRSOUT_PRSOUT2_SIGSYNC << 4)   /**< Shifted mode SIGSYNC for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT2_SIGTOG              (_SMCTRL_PRSOUT_PRSOUT2_SIGTOG << 4)    /**< Shifted mode SIGTOG for SMCTRL_PRSOUT       */
#define SMCTRL_PRSOUT_PRSOUT2_GPREG               (_SMCTRL_PRSOUT_PRSOUT2_GPREG << 4)     /**< Shifted mode GPREG for SMCTRL_PRSOUT        */
#define _SMCTRL_PRSOUT_PRSOUT3_SHIFT              6                                       /**< Shift value for SMCTRL_PRSOUT3              */
#define _SMCTRL_PRSOUT_PRSOUT3_MASK               0xC0UL                                  /**< Bit mask for SMCTRL_PRSOUT3                 */
#define _SMCTRL_PRSOUT_PRSOUT3_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT3_IDLE               0x00000000UL                            /**< Mode IDLE for SMCTRL_PRSOUT                 */
#define _SMCTRL_PRSOUT_PRSOUT3_SIGSYNC            0x00000001UL                            /**< Mode SIGSYNC for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT3_SIGTOG             0x00000002UL                            /**< Mode SIGTOG for SMCTRL_PRSOUT               */
#define _SMCTRL_PRSOUT_PRSOUT3_GPREG              0x00000003UL                            /**< Mode GPREG for SMCTRL_PRSOUT                */
#define SMCTRL_PRSOUT_PRSOUT3_DEFAULT             (_SMCTRL_PRSOUT_PRSOUT3_DEFAULT << 6)   /**< Shifted mode DEFAULT for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT3_IDLE                (_SMCTRL_PRSOUT_PRSOUT3_IDLE << 6)      /**< Shifted mode IDLE for SMCTRL_PRSOUT         */
#define SMCTRL_PRSOUT_PRSOUT3_SIGSYNC             (_SMCTRL_PRSOUT_PRSOUT3_SIGSYNC << 6)   /**< Shifted mode SIGSYNC for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT3_SIGTOG              (_SMCTRL_PRSOUT_PRSOUT3_SIGTOG << 6)    /**< Shifted mode SIGTOG for SMCTRL_PRSOUT       */
#define SMCTRL_PRSOUT_PRSOUT3_GPREG               (_SMCTRL_PRSOUT_PRSOUT3_GPREG << 6)     /**< Shifted mode GPREG for SMCTRL_PRSOUT        */
#define _SMCTRL_PRSOUT_PRSOUT4_SHIFT              8                                       /**< Shift value for SMCTRL_PRSOUT4              */
#define _SMCTRL_PRSOUT_PRSOUT4_MASK               0x300UL                                 /**< Bit mask for SMCTRL_PRSOUT4                 */
#define _SMCTRL_PRSOUT_PRSOUT4_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT4_IDLE               0x00000000UL                            /**< Mode IDLE for SMCTRL_PRSOUT                 */
#define _SMCTRL_PRSOUT_PRSOUT4_SIGSYNC            0x00000001UL                            /**< Mode SIGSYNC for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT4_SIGTOG             0x00000002UL                            /**< Mode SIGTOG for SMCTRL_PRSOUT               */
#define _SMCTRL_PRSOUT_PRSOUT4_GPREG              0x00000003UL                            /**< Mode GPREG for SMCTRL_PRSOUT                */
#define SMCTRL_PRSOUT_PRSOUT4_DEFAULT             (_SMCTRL_PRSOUT_PRSOUT4_DEFAULT << 8)   /**< Shifted mode DEFAULT for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT4_IDLE                (_SMCTRL_PRSOUT_PRSOUT4_IDLE << 8)      /**< Shifted mode IDLE for SMCTRL_PRSOUT         */
#define SMCTRL_PRSOUT_PRSOUT4_SIGSYNC             (_SMCTRL_PRSOUT_PRSOUT4_SIGSYNC << 8)   /**< Shifted mode SIGSYNC for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT4_SIGTOG              (_SMCTRL_PRSOUT_PRSOUT4_SIGTOG << 8)    /**< Shifted mode SIGTOG for SMCTRL_PRSOUT       */
#define SMCTRL_PRSOUT_PRSOUT4_GPREG               (_SMCTRL_PRSOUT_PRSOUT4_GPREG << 8)     /**< Shifted mode GPREG for SMCTRL_PRSOUT        */
#define _SMCTRL_PRSOUT_PRSOUT5_SHIFT              10                                      /**< Shift value for SMCTRL_PRSOUT5              */
#define _SMCTRL_PRSOUT_PRSOUT5_MASK               0xC00UL                                 /**< Bit mask for SMCTRL_PRSOUT5                 */
#define _SMCTRL_PRSOUT_PRSOUT5_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT5_IDLE               0x00000000UL                            /**< Mode IDLE for SMCTRL_PRSOUT                 */
#define _SMCTRL_PRSOUT_PRSOUT5_SIGSYNC            0x00000001UL                            /**< Mode SIGSYNC for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT5_SIGTOG             0x00000002UL                            /**< Mode SIGTOG for SMCTRL_PRSOUT               */
#define _SMCTRL_PRSOUT_PRSOUT5_GPREG              0x00000003UL                            /**< Mode GPREG for SMCTRL_PRSOUT                */
#define SMCTRL_PRSOUT_PRSOUT5_DEFAULT             (_SMCTRL_PRSOUT_PRSOUT5_DEFAULT << 10)  /**< Shifted mode DEFAULT for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT5_IDLE                (_SMCTRL_PRSOUT_PRSOUT5_IDLE << 10)     /**< Shifted mode IDLE for SMCTRL_PRSOUT         */
#define SMCTRL_PRSOUT_PRSOUT5_SIGSYNC             (_SMCTRL_PRSOUT_PRSOUT5_SIGSYNC << 10)  /**< Shifted mode SIGSYNC for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT5_SIGTOG              (_SMCTRL_PRSOUT_PRSOUT5_SIGTOG << 10)   /**< Shifted mode SIGTOG for SMCTRL_PRSOUT       */
#define SMCTRL_PRSOUT_PRSOUT5_GPREG               (_SMCTRL_PRSOUT_PRSOUT5_GPREG << 10)    /**< Shifted mode GPREG for SMCTRL_PRSOUT        */
#define _SMCTRL_PRSOUT_PRSOUT6_SHIFT              12                                      /**< Shift value for SMCTRL_PRSOUT6              */
#define _SMCTRL_PRSOUT_PRSOUT6_MASK               0x3000UL                                /**< Bit mask for SMCTRL_PRSOUT6                 */
#define _SMCTRL_PRSOUT_PRSOUT6_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT6_IDLE               0x00000000UL                            /**< Mode IDLE for SMCTRL_PRSOUT                 */
#define _SMCTRL_PRSOUT_PRSOUT6_SIGSYNC            0x00000001UL                            /**< Mode SIGSYNC for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT6_SIGTOG             0x00000002UL                            /**< Mode SIGTOG for SMCTRL_PRSOUT               */
#define _SMCTRL_PRSOUT_PRSOUT6_GPREG              0x00000003UL                            /**< Mode GPREG for SMCTRL_PRSOUT                */
#define SMCTRL_PRSOUT_PRSOUT6_DEFAULT             (_SMCTRL_PRSOUT_PRSOUT6_DEFAULT << 12)  /**< Shifted mode DEFAULT for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT6_IDLE                (_SMCTRL_PRSOUT_PRSOUT6_IDLE << 12)     /**< Shifted mode IDLE for SMCTRL_PRSOUT         */
#define SMCTRL_PRSOUT_PRSOUT6_SIGSYNC             (_SMCTRL_PRSOUT_PRSOUT6_SIGSYNC << 12)  /**< Shifted mode SIGSYNC for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT6_SIGTOG              (_SMCTRL_PRSOUT_PRSOUT6_SIGTOG << 12)   /**< Shifted mode SIGTOG for SMCTRL_PRSOUT       */
#define SMCTRL_PRSOUT_PRSOUT6_GPREG               (_SMCTRL_PRSOUT_PRSOUT6_GPREG << 12)    /**< Shifted mode GPREG for SMCTRL_PRSOUT        */
#define _SMCTRL_PRSOUT_PRSOUT7_SHIFT              14                                      /**< Shift value for SMCTRL_PRSOUT7              */
#define _SMCTRL_PRSOUT_PRSOUT7_MASK               0xC000UL                                /**< Bit mask for SMCTRL_PRSOUT7                 */
#define _SMCTRL_PRSOUT_PRSOUT7_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT7_IDLE               0x00000000UL                            /**< Mode IDLE for SMCTRL_PRSOUT                 */
#define _SMCTRL_PRSOUT_PRSOUT7_SIGSYNC            0x00000001UL                            /**< Mode SIGSYNC for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT7_SIGTOG             0x00000002UL                            /**< Mode SIGTOG for SMCTRL_PRSOUT               */
#define _SMCTRL_PRSOUT_PRSOUT7_GPREG              0x00000003UL                            /**< Mode GPREG for SMCTRL_PRSOUT                */
#define SMCTRL_PRSOUT_PRSOUT7_DEFAULT             (_SMCTRL_PRSOUT_PRSOUT7_DEFAULT << 14)  /**< Shifted mode DEFAULT for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT7_IDLE                (_SMCTRL_PRSOUT_PRSOUT7_IDLE << 14)     /**< Shifted mode IDLE for SMCTRL_PRSOUT         */
#define SMCTRL_PRSOUT_PRSOUT7_SIGSYNC             (_SMCTRL_PRSOUT_PRSOUT7_SIGSYNC << 14)  /**< Shifted mode SIGSYNC for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT7_SIGTOG              (_SMCTRL_PRSOUT_PRSOUT7_SIGTOG << 14)   /**< Shifted mode SIGTOG for SMCTRL_PRSOUT       */
#define SMCTRL_PRSOUT_PRSOUT7_GPREG               (_SMCTRL_PRSOUT_PRSOUT7_GPREG << 14)    /**< Shifted mode GPREG for SMCTRL_PRSOUT        */
#define _SMCTRL_PRSOUT_PRSOUT8_SHIFT              16                                      /**< Shift value for SMCTRL_PRSOUT8              */
#define _SMCTRL_PRSOUT_PRSOUT8_MASK               0x30000UL                               /**< Bit mask for SMCTRL_PRSOUT8                 */
#define _SMCTRL_PRSOUT_PRSOUT8_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT8_IDLE               0x00000000UL                            /**< Mode IDLE for SMCTRL_PRSOUT                 */
#define _SMCTRL_PRSOUT_PRSOUT8_SIGSYNC            0x00000001UL                            /**< Mode SIGSYNC for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT8_SIGTOG             0x00000002UL                            /**< Mode SIGTOG for SMCTRL_PRSOUT               */
#define _SMCTRL_PRSOUT_PRSOUT8_GPREG              0x00000003UL                            /**< Mode GPREG for SMCTRL_PRSOUT                */
#define SMCTRL_PRSOUT_PRSOUT8_DEFAULT             (_SMCTRL_PRSOUT_PRSOUT8_DEFAULT << 16)  /**< Shifted mode DEFAULT for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT8_IDLE                (_SMCTRL_PRSOUT_PRSOUT8_IDLE << 16)     /**< Shifted mode IDLE for SMCTRL_PRSOUT         */
#define SMCTRL_PRSOUT_PRSOUT8_SIGSYNC             (_SMCTRL_PRSOUT_PRSOUT8_SIGSYNC << 16)  /**< Shifted mode SIGSYNC for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT8_SIGTOG              (_SMCTRL_PRSOUT_PRSOUT8_SIGTOG << 16)   /**< Shifted mode SIGTOG for SMCTRL_PRSOUT       */
#define SMCTRL_PRSOUT_PRSOUT8_GPREG               (_SMCTRL_PRSOUT_PRSOUT8_GPREG << 16)    /**< Shifted mode GPREG for SMCTRL_PRSOUT        */
#define _SMCTRL_PRSOUT_PRSOUT9_SHIFT              18                                      /**< Shift value for SMCTRL_PRSOUT9              */
#define _SMCTRL_PRSOUT_PRSOUT9_MASK               0xC0000UL                               /**< Bit mask for SMCTRL_PRSOUT9                 */
#define _SMCTRL_PRSOUT_PRSOUT9_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT9_IDLE               0x00000000UL                            /**< Mode IDLE for SMCTRL_PRSOUT                 */
#define _SMCTRL_PRSOUT_PRSOUT9_SIGSYNC            0x00000001UL                            /**< Mode SIGSYNC for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT9_SIGTOG             0x00000002UL                            /**< Mode SIGTOG for SMCTRL_PRSOUT               */
#define _SMCTRL_PRSOUT_PRSOUT9_GPREG              0x00000003UL                            /**< Mode GPREG for SMCTRL_PRSOUT                */
#define SMCTRL_PRSOUT_PRSOUT9_DEFAULT             (_SMCTRL_PRSOUT_PRSOUT9_DEFAULT << 18)  /**< Shifted mode DEFAULT for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT9_IDLE                (_SMCTRL_PRSOUT_PRSOUT9_IDLE << 18)     /**< Shifted mode IDLE for SMCTRL_PRSOUT         */
#define SMCTRL_PRSOUT_PRSOUT9_SIGSYNC             (_SMCTRL_PRSOUT_PRSOUT9_SIGSYNC << 18)  /**< Shifted mode SIGSYNC for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT9_SIGTOG              (_SMCTRL_PRSOUT_PRSOUT9_SIGTOG << 18)   /**< Shifted mode SIGTOG for SMCTRL_PRSOUT       */
#define SMCTRL_PRSOUT_PRSOUT9_GPREG               (_SMCTRL_PRSOUT_PRSOUT9_GPREG << 18)    /**< Shifted mode GPREG for SMCTRL_PRSOUT        */
#define _SMCTRL_PRSOUT_PRSOUT10_SHIFT             20                                      /**< Shift value for SMCTRL_PRSOUT10             */
#define _SMCTRL_PRSOUT_PRSOUT10_MASK              0x300000UL                              /**< Bit mask for SMCTRL_PRSOUT10                */
#define _SMCTRL_PRSOUT_PRSOUT10_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT10_IDLE              0x00000000UL                            /**< Mode IDLE for SMCTRL_PRSOUT                 */
#define _SMCTRL_PRSOUT_PRSOUT10_SIGSYNC           0x00000001UL                            /**< Mode SIGSYNC for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT10_SIGTOG            0x00000002UL                            /**< Mode SIGTOG for SMCTRL_PRSOUT               */
#define _SMCTRL_PRSOUT_PRSOUT10_GPREG             0x00000003UL                            /**< Mode GPREG for SMCTRL_PRSOUT                */
#define SMCTRL_PRSOUT_PRSOUT10_DEFAULT            (_SMCTRL_PRSOUT_PRSOUT10_DEFAULT << 20) /**< Shifted mode DEFAULT for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT10_IDLE               (_SMCTRL_PRSOUT_PRSOUT10_IDLE << 20)    /**< Shifted mode IDLE for SMCTRL_PRSOUT         */
#define SMCTRL_PRSOUT_PRSOUT10_SIGSYNC            (_SMCTRL_PRSOUT_PRSOUT10_SIGSYNC << 20) /**< Shifted mode SIGSYNC for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT10_SIGTOG             (_SMCTRL_PRSOUT_PRSOUT10_SIGTOG << 20)  /**< Shifted mode SIGTOG for SMCTRL_PRSOUT       */
#define SMCTRL_PRSOUT_PRSOUT10_GPREG              (_SMCTRL_PRSOUT_PRSOUT10_GPREG << 20)   /**< Shifted mode GPREG for SMCTRL_PRSOUT        */
#define _SMCTRL_PRSOUT_PRSOUT11_SHIFT             22                                      /**< Shift value for SMCTRL_PRSOUT11             */
#define _SMCTRL_PRSOUT_PRSOUT11_MASK              0xC00000UL                              /**< Bit mask for SMCTRL_PRSOUT11                */
#define _SMCTRL_PRSOUT_PRSOUT11_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT11_IDLE              0x00000000UL                            /**< Mode IDLE for SMCTRL_PRSOUT                 */
#define _SMCTRL_PRSOUT_PRSOUT11_SIGSYNC           0x00000001UL                            /**< Mode SIGSYNC for SMCTRL_PRSOUT              */
#define _SMCTRL_PRSOUT_PRSOUT11_SIGTOG            0x00000002UL                            /**< Mode SIGTOG for SMCTRL_PRSOUT               */
#define _SMCTRL_PRSOUT_PRSOUT11_GPREG             0x00000003UL                            /**< Mode GPREG for SMCTRL_PRSOUT                */
#define SMCTRL_PRSOUT_PRSOUT11_DEFAULT            (_SMCTRL_PRSOUT_PRSOUT11_DEFAULT << 22) /**< Shifted mode DEFAULT for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT11_IDLE               (_SMCTRL_PRSOUT_PRSOUT11_IDLE << 22)    /**< Shifted mode IDLE for SMCTRL_PRSOUT         */
#define SMCTRL_PRSOUT_PRSOUT11_SIGSYNC            (_SMCTRL_PRSOUT_PRSOUT11_SIGSYNC << 22) /**< Shifted mode SIGSYNC for SMCTRL_PRSOUT      */
#define SMCTRL_PRSOUT_PRSOUT11_SIGTOG             (_SMCTRL_PRSOUT_PRSOUT11_SIGTOG << 22)  /**< Shifted mode SIGTOG for SMCTRL_PRSOUT       */
#define SMCTRL_PRSOUT_PRSOUT11_GPREG              (_SMCTRL_PRSOUT_PRSOUT11_GPREG << 22)   /**< Shifted mode GPREG for SMCTRL_PRSOUT        */

/* Bit fields for SMCTRL RXEVMUX */
#define _SMCTRL_RXEVMUX_RESETVALUE                0x14131211UL                          /**< Default value for SMCTRL_RXEVMUX            */
#define _SMCTRL_RXEVMUX_MASK                      0x1F1F1F1FUL                          /**< Mask for SMCTRL_RXEVMUX                     */
#define _SMCTRL_RXEVMUX_MUX0_SHIFT                0                                     /**< Shift value for SMCTRL_MUX0                 */
#define _SMCTRL_RXEVMUX_MUX0_MASK                 0x1FUL                                /**< Bit mask for SMCTRL_MUX0                    */
#define _SMCTRL_RXEVMUX_MUX0_DEFAULT              0x00000011UL                          /**< Mode DEFAULT for SMCTRL_RXEVMUX             */
#define SMCTRL_RXEVMUX_MUX0_DEFAULT               (_SMCTRL_RXEVMUX_MUX0_DEFAULT << 0)   /**< Shifted mode DEFAULT for SMCTRL_RXEVMUX     */
#define _SMCTRL_RXEVMUX_MUX1_SHIFT                8                                     /**< Shift value for SMCTRL_MUX1                 */
#define _SMCTRL_RXEVMUX_MUX1_MASK                 0x1F00UL                              /**< Bit mask for SMCTRL_MUX1                    */
#define _SMCTRL_RXEVMUX_MUX1_DEFAULT              0x00000012UL                          /**< Mode DEFAULT for SMCTRL_RXEVMUX             */
#define SMCTRL_RXEVMUX_MUX1_DEFAULT               (_SMCTRL_RXEVMUX_MUX1_DEFAULT << 8)   /**< Shifted mode DEFAULT for SMCTRL_RXEVMUX     */
#define _SMCTRL_RXEVMUX_MUX2_SHIFT                16                                    /**< Shift value for SMCTRL_MUX2                 */
#define _SMCTRL_RXEVMUX_MUX2_MASK                 0x1F0000UL                            /**< Bit mask for SMCTRL_MUX2                    */
#define _SMCTRL_RXEVMUX_MUX2_DEFAULT              0x00000013UL                          /**< Mode DEFAULT for SMCTRL_RXEVMUX             */
#define SMCTRL_RXEVMUX_MUX2_DEFAULT               (_SMCTRL_RXEVMUX_MUX2_DEFAULT << 16)  /**< Shifted mode DEFAULT for SMCTRL_RXEVMUX     */
#define _SMCTRL_RXEVMUX_MUX3_SHIFT                24                                    /**< Shift value for SMCTRL_MUX3                 */
#define _SMCTRL_RXEVMUX_MUX3_MASK                 0x1F000000UL                          /**< Bit mask for SMCTRL_MUX3                    */
#define _SMCTRL_RXEVMUX_MUX3_DEFAULT              0x00000014UL                          /**< Mode DEFAULT for SMCTRL_RXEVMUX             */
#define SMCTRL_RXEVMUX_MUX3_DEFAULT               (_SMCTRL_RXEVMUX_MUX3_DEFAULT << 24)  /**< Shifted mode DEFAULT for SMCTRL_RXEVMUX     */

/* Bit fields for SMCTRL TIMCTRL */
#define _SMCTRL_TIMCTRL_RESETVALUE                0x00000000UL                           /**< Default value for SMCTRL_TIMCTRL            */
#define _SMCTRL_TIMCTRL_MASK                      0x00FFFFFFUL                           /**< Mask for SMCTRL_TIMCTRL                     */
#define SMCTRL_TIMCTRL_INIT0                      (0x1UL << 0)                           /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT0_SHIFT               0                                      /**< Shift value for SMCTRL_INIT0                */
#define _SMCTRL_TIMCTRL_INIT0_MASK                0x1UL                                  /**< Bit mask for SMCTRL_INIT0                   */
#define _SMCTRL_TIMCTRL_INIT0_DEFAULT             0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT0_DEFAULT              (_SMCTRL_TIMCTRL_INIT0_DEFAULT << 0)   /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT1                      (0x1UL << 1)                           /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT1_SHIFT               1                                      /**< Shift value for SMCTRL_INIT1                */
#define _SMCTRL_TIMCTRL_INIT1_MASK                0x2UL                                  /**< Bit mask for SMCTRL_INIT1                   */
#define _SMCTRL_TIMCTRL_INIT1_DEFAULT             0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT1_DEFAULT              (_SMCTRL_TIMCTRL_INIT1_DEFAULT << 1)   /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT2                      (0x1UL << 2)                           /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT2_SHIFT               2                                      /**< Shift value for SMCTRL_INIT2                */
#define _SMCTRL_TIMCTRL_INIT2_MASK                0x4UL                                  /**< Bit mask for SMCTRL_INIT2                   */
#define _SMCTRL_TIMCTRL_INIT2_DEFAULT             0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT2_DEFAULT              (_SMCTRL_TIMCTRL_INIT2_DEFAULT << 2)   /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT3                      (0x1UL << 3)                           /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT3_SHIFT               3                                      /**< Shift value for SMCTRL_INIT3                */
#define _SMCTRL_TIMCTRL_INIT3_MASK                0x8UL                                  /**< Bit mask for SMCTRL_INIT3                   */
#define _SMCTRL_TIMCTRL_INIT3_DEFAULT             0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT3_DEFAULT              (_SMCTRL_TIMCTRL_INIT3_DEFAULT << 3)   /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT4                      (0x1UL << 4)                           /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT4_SHIFT               4                                      /**< Shift value for SMCTRL_INIT4                */
#define _SMCTRL_TIMCTRL_INIT4_MASK                0x10UL                                 /**< Bit mask for SMCTRL_INIT4                   */
#define _SMCTRL_TIMCTRL_INIT4_DEFAULT             0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT4_DEFAULT              (_SMCTRL_TIMCTRL_INIT4_DEFAULT << 4)   /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT5                      (0x1UL << 5)                           /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT5_SHIFT               5                                      /**< Shift value for SMCTRL_INIT5                */
#define _SMCTRL_TIMCTRL_INIT5_MASK                0x20UL                                 /**< Bit mask for SMCTRL_INIT5                   */
#define _SMCTRL_TIMCTRL_INIT5_DEFAULT             0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT5_DEFAULT              (_SMCTRL_TIMCTRL_INIT5_DEFAULT << 5)   /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT6                      (0x1UL << 6)                           /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT6_SHIFT               6                                      /**< Shift value for SMCTRL_INIT6                */
#define _SMCTRL_TIMCTRL_INIT6_MASK                0x40UL                                 /**< Bit mask for SMCTRL_INIT6                   */
#define _SMCTRL_TIMCTRL_INIT6_DEFAULT             0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT6_DEFAULT              (_SMCTRL_TIMCTRL_INIT6_DEFAULT << 6)   /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT7                      (0x1UL << 7)                           /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT7_SHIFT               7                                      /**< Shift value for SMCTRL_INIT7                */
#define _SMCTRL_TIMCTRL_INIT7_MASK                0x80UL                                 /**< Bit mask for SMCTRL_INIT7                   */
#define _SMCTRL_TIMCTRL_INIT7_DEFAULT             0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT7_DEFAULT              (_SMCTRL_TIMCTRL_INIT7_DEFAULT << 7)   /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT8                      (0x1UL << 8)                           /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT8_SHIFT               8                                      /**< Shift value for SMCTRL_INIT8                */
#define _SMCTRL_TIMCTRL_INIT8_MASK                0x100UL                                /**< Bit mask for SMCTRL_INIT8                   */
#define _SMCTRL_TIMCTRL_INIT8_DEFAULT             0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT8_DEFAULT              (_SMCTRL_TIMCTRL_INIT8_DEFAULT << 8)   /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT9                      (0x1UL << 9)                           /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT9_SHIFT               9                                      /**< Shift value for SMCTRL_INIT9                */
#define _SMCTRL_TIMCTRL_INIT9_MASK                0x200UL                                /**< Bit mask for SMCTRL_INIT9                   */
#define _SMCTRL_TIMCTRL_INIT9_DEFAULT             0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT9_DEFAULT              (_SMCTRL_TIMCTRL_INIT9_DEFAULT << 9)   /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT10                     (0x1UL << 10)                          /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT10_SHIFT              10                                     /**< Shift value for SMCTRL_INIT10               */
#define _SMCTRL_TIMCTRL_INIT10_MASK               0x400UL                                /**< Bit mask for SMCTRL_INIT10                  */
#define _SMCTRL_TIMCTRL_INIT10_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT10_DEFAULT             (_SMCTRL_TIMCTRL_INIT10_DEFAULT << 10) /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT11                     (0x1UL << 11)                          /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT11_SHIFT              11                                     /**< Shift value for SMCTRL_INIT11               */
#define _SMCTRL_TIMCTRL_INIT11_MASK               0x800UL                                /**< Bit mask for SMCTRL_INIT11                  */
#define _SMCTRL_TIMCTRL_INIT11_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT11_DEFAULT             (_SMCTRL_TIMCTRL_INIT11_DEFAULT << 11) /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT12                     (0x1UL << 12)                          /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT12_SHIFT              12                                     /**< Shift value for SMCTRL_INIT12               */
#define _SMCTRL_TIMCTRL_INIT12_MASK               0x1000UL                               /**< Bit mask for SMCTRL_INIT12                  */
#define _SMCTRL_TIMCTRL_INIT12_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT12_DEFAULT             (_SMCTRL_TIMCTRL_INIT12_DEFAULT << 12) /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT13                     (0x1UL << 13)                          /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT13_SHIFT              13                                     /**< Shift value for SMCTRL_INIT13               */
#define _SMCTRL_TIMCTRL_INIT13_MASK               0x2000UL                               /**< Bit mask for SMCTRL_INIT13                  */
#define _SMCTRL_TIMCTRL_INIT13_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT13_DEFAULT             (_SMCTRL_TIMCTRL_INIT13_DEFAULT << 13) /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT14                     (0x1UL << 14)                          /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT14_SHIFT              14                                     /**< Shift value for SMCTRL_INIT14               */
#define _SMCTRL_TIMCTRL_INIT14_MASK               0x4000UL                               /**< Bit mask for SMCTRL_INIT14                  */
#define _SMCTRL_TIMCTRL_INIT14_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT14_DEFAULT             (_SMCTRL_TIMCTRL_INIT14_DEFAULT << 14) /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT15                     (0x1UL << 15)                          /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT15_SHIFT              15                                     /**< Shift value for SMCTRL_INIT15               */
#define _SMCTRL_TIMCTRL_INIT15_MASK               0x8000UL                               /**< Bit mask for SMCTRL_INIT15                  */
#define _SMCTRL_TIMCTRL_INIT15_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT15_DEFAULT             (_SMCTRL_TIMCTRL_INIT15_DEFAULT << 15) /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT16                     (0x1UL << 16)                          /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT16_SHIFT              16                                     /**< Shift value for SMCTRL_INIT16               */
#define _SMCTRL_TIMCTRL_INIT16_MASK               0x10000UL                              /**< Bit mask for SMCTRL_INIT16                  */
#define _SMCTRL_TIMCTRL_INIT16_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT16_DEFAULT             (_SMCTRL_TIMCTRL_INIT16_DEFAULT << 16) /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT17                     (0x1UL << 17)                          /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT17_SHIFT              17                                     /**< Shift value for SMCTRL_INIT17               */
#define _SMCTRL_TIMCTRL_INIT17_MASK               0x20000UL                              /**< Bit mask for SMCTRL_INIT17                  */
#define _SMCTRL_TIMCTRL_INIT17_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT17_DEFAULT             (_SMCTRL_TIMCTRL_INIT17_DEFAULT << 17) /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT18                     (0x1UL << 18)                          /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT18_SHIFT              18                                     /**< Shift value for SMCTRL_INIT18               */
#define _SMCTRL_TIMCTRL_INIT18_MASK               0x40000UL                              /**< Bit mask for SMCTRL_INIT18                  */
#define _SMCTRL_TIMCTRL_INIT18_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT18_DEFAULT             (_SMCTRL_TIMCTRL_INIT18_DEFAULT << 18) /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT19                     (0x1UL << 19)                          /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT19_SHIFT              19                                     /**< Shift value for SMCTRL_INIT19               */
#define _SMCTRL_TIMCTRL_INIT19_MASK               0x80000UL                              /**< Bit mask for SMCTRL_INIT19                  */
#define _SMCTRL_TIMCTRL_INIT19_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT19_DEFAULT             (_SMCTRL_TIMCTRL_INIT19_DEFAULT << 19) /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT20                     (0x1UL << 20)                          /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT20_SHIFT              20                                     /**< Shift value for SMCTRL_INIT20               */
#define _SMCTRL_TIMCTRL_INIT20_MASK               0x100000UL                             /**< Bit mask for SMCTRL_INIT20                  */
#define _SMCTRL_TIMCTRL_INIT20_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT20_DEFAULT             (_SMCTRL_TIMCTRL_INIT20_DEFAULT << 20) /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT21                     (0x1UL << 21)                          /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT21_SHIFT              21                                     /**< Shift value for SMCTRL_INIT21               */
#define _SMCTRL_TIMCTRL_INIT21_MASK               0x200000UL                             /**< Bit mask for SMCTRL_INIT21                  */
#define _SMCTRL_TIMCTRL_INIT21_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT21_DEFAULT             (_SMCTRL_TIMCTRL_INIT21_DEFAULT << 21) /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT22                     (0x1UL << 22)                          /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT22_SHIFT              22                                     /**< Shift value for SMCTRL_INIT22               */
#define _SMCTRL_TIMCTRL_INIT22_MASK               0x400000UL                             /**< Bit mask for SMCTRL_INIT22                  */
#define _SMCTRL_TIMCTRL_INIT22_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT22_DEFAULT             (_SMCTRL_TIMCTRL_INIT22_DEFAULT << 22) /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */
#define SMCTRL_TIMCTRL_INIT23                     (0x1UL << 23)                          /**< New BitField                                */
#define _SMCTRL_TIMCTRL_INIT23_SHIFT              23                                     /**< Shift value for SMCTRL_INIT23               */
#define _SMCTRL_TIMCTRL_INIT23_MASK               0x800000UL                             /**< Bit mask for SMCTRL_INIT23                  */
#define _SMCTRL_TIMCTRL_INIT23_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for SMCTRL_TIMCTRL             */
#define SMCTRL_TIMCTRL_INIT23_DEFAULT             (_SMCTRL_TIMCTRL_INIT23_DEFAULT << 23) /**< Shifted mode DEFAULT for SMCTRL_TIMCTRL     */

/* Bit fields for SMCTRL TIMSTAT */
#define _SMCTRL_TIMSTAT_RESETVALUE                0x00000000UL                            /**< Default value for SMCTRL_TIMSTAT            */
#define _SMCTRL_TIMSTAT_MASK                      0x00FFFFFFUL                            /**< Mask for SMCTRL_TIMSTAT                     */
#define SMCTRL_TIMSTAT_VALUE0                     (0x1UL << 0)                            /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE0_SHIFT              0                                       /**< Shift value for SMCTRL_VALUE0               */
#define _SMCTRL_TIMSTAT_VALUE0_MASK               0x1UL                                   /**< Bit mask for SMCTRL_VALUE0                  */
#define _SMCTRL_TIMSTAT_VALUE0_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE0_DEFAULT             (_SMCTRL_TIMSTAT_VALUE0_DEFAULT << 0)   /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE1                     (0x1UL << 1)                            /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE1_SHIFT              1                                       /**< Shift value for SMCTRL_VALUE1               */
#define _SMCTRL_TIMSTAT_VALUE1_MASK               0x2UL                                   /**< Bit mask for SMCTRL_VALUE1                  */
#define _SMCTRL_TIMSTAT_VALUE1_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE1_DEFAULT             (_SMCTRL_TIMSTAT_VALUE1_DEFAULT << 1)   /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE2                     (0x1UL << 2)                            /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE2_SHIFT              2                                       /**< Shift value for SMCTRL_VALUE2               */
#define _SMCTRL_TIMSTAT_VALUE2_MASK               0x4UL                                   /**< Bit mask for SMCTRL_VALUE2                  */
#define _SMCTRL_TIMSTAT_VALUE2_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE2_DEFAULT             (_SMCTRL_TIMSTAT_VALUE2_DEFAULT << 2)   /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE3                     (0x1UL << 3)                            /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE3_SHIFT              3                                       /**< Shift value for SMCTRL_VALUE3               */
#define _SMCTRL_TIMSTAT_VALUE3_MASK               0x8UL                                   /**< Bit mask for SMCTRL_VALUE3                  */
#define _SMCTRL_TIMSTAT_VALUE3_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE3_DEFAULT             (_SMCTRL_TIMSTAT_VALUE3_DEFAULT << 3)   /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE4                     (0x1UL << 4)                            /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE4_SHIFT              4                                       /**< Shift value for SMCTRL_VALUE4               */
#define _SMCTRL_TIMSTAT_VALUE4_MASK               0x10UL                                  /**< Bit mask for SMCTRL_VALUE4                  */
#define _SMCTRL_TIMSTAT_VALUE4_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE4_DEFAULT             (_SMCTRL_TIMSTAT_VALUE4_DEFAULT << 4)   /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE5                     (0x1UL << 5)                            /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE5_SHIFT              5                                       /**< Shift value for SMCTRL_VALUE5               */
#define _SMCTRL_TIMSTAT_VALUE5_MASK               0x20UL                                  /**< Bit mask for SMCTRL_VALUE5                  */
#define _SMCTRL_TIMSTAT_VALUE5_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE5_DEFAULT             (_SMCTRL_TIMSTAT_VALUE5_DEFAULT << 5)   /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE6                     (0x1UL << 6)                            /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE6_SHIFT              6                                       /**< Shift value for SMCTRL_VALUE6               */
#define _SMCTRL_TIMSTAT_VALUE6_MASK               0x40UL                                  /**< Bit mask for SMCTRL_VALUE6                  */
#define _SMCTRL_TIMSTAT_VALUE6_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE6_DEFAULT             (_SMCTRL_TIMSTAT_VALUE6_DEFAULT << 6)   /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE7                     (0x1UL << 7)                            /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE7_SHIFT              7                                       /**< Shift value for SMCTRL_VALUE7               */
#define _SMCTRL_TIMSTAT_VALUE7_MASK               0x80UL                                  /**< Bit mask for SMCTRL_VALUE7                  */
#define _SMCTRL_TIMSTAT_VALUE7_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE7_DEFAULT             (_SMCTRL_TIMSTAT_VALUE7_DEFAULT << 7)   /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE8                     (0x1UL << 8)                            /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE8_SHIFT              8                                       /**< Shift value for SMCTRL_VALUE8               */
#define _SMCTRL_TIMSTAT_VALUE8_MASK               0x100UL                                 /**< Bit mask for SMCTRL_VALUE8                  */
#define _SMCTRL_TIMSTAT_VALUE8_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE8_DEFAULT             (_SMCTRL_TIMSTAT_VALUE8_DEFAULT << 8)   /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE9                     (0x1UL << 9)                            /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE9_SHIFT              9                                       /**< Shift value for SMCTRL_VALUE9               */
#define _SMCTRL_TIMSTAT_VALUE9_MASK               0x200UL                                 /**< Bit mask for SMCTRL_VALUE9                  */
#define _SMCTRL_TIMSTAT_VALUE9_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE9_DEFAULT             (_SMCTRL_TIMSTAT_VALUE9_DEFAULT << 9)   /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE10                    (0x1UL << 10)                           /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE10_SHIFT             10                                      /**< Shift value for SMCTRL_VALUE10              */
#define _SMCTRL_TIMSTAT_VALUE10_MASK              0x400UL                                 /**< Bit mask for SMCTRL_VALUE10                 */
#define _SMCTRL_TIMSTAT_VALUE10_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE10_DEFAULT            (_SMCTRL_TIMSTAT_VALUE10_DEFAULT << 10) /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE11                    (0x1UL << 11)                           /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE11_SHIFT             11                                      /**< Shift value for SMCTRL_VALUE11              */
#define _SMCTRL_TIMSTAT_VALUE11_MASK              0x800UL                                 /**< Bit mask for SMCTRL_VALUE11                 */
#define _SMCTRL_TIMSTAT_VALUE11_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE11_DEFAULT            (_SMCTRL_TIMSTAT_VALUE11_DEFAULT << 11) /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE12                    (0x1UL << 12)                           /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE12_SHIFT             12                                      /**< Shift value for SMCTRL_VALUE12              */
#define _SMCTRL_TIMSTAT_VALUE12_MASK              0x1000UL                                /**< Bit mask for SMCTRL_VALUE12                 */
#define _SMCTRL_TIMSTAT_VALUE12_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE12_DEFAULT            (_SMCTRL_TIMSTAT_VALUE12_DEFAULT << 12) /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE13                    (0x1UL << 13)                           /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE13_SHIFT             13                                      /**< Shift value for SMCTRL_VALUE13              */
#define _SMCTRL_TIMSTAT_VALUE13_MASK              0x2000UL                                /**< Bit mask for SMCTRL_VALUE13                 */
#define _SMCTRL_TIMSTAT_VALUE13_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE13_DEFAULT            (_SMCTRL_TIMSTAT_VALUE13_DEFAULT << 13) /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE14                    (0x1UL << 14)                           /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE14_SHIFT             14                                      /**< Shift value for SMCTRL_VALUE14              */
#define _SMCTRL_TIMSTAT_VALUE14_MASK              0x4000UL                                /**< Bit mask for SMCTRL_VALUE14                 */
#define _SMCTRL_TIMSTAT_VALUE14_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE14_DEFAULT            (_SMCTRL_TIMSTAT_VALUE14_DEFAULT << 14) /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE15                    (0x1UL << 15)                           /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE15_SHIFT             15                                      /**< Shift value for SMCTRL_VALUE15              */
#define _SMCTRL_TIMSTAT_VALUE15_MASK              0x8000UL                                /**< Bit mask for SMCTRL_VALUE15                 */
#define _SMCTRL_TIMSTAT_VALUE15_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE15_DEFAULT            (_SMCTRL_TIMSTAT_VALUE15_DEFAULT << 15) /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE16                    (0x1UL << 16)                           /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE16_SHIFT             16                                      /**< Shift value for SMCTRL_VALUE16              */
#define _SMCTRL_TIMSTAT_VALUE16_MASK              0x10000UL                               /**< Bit mask for SMCTRL_VALUE16                 */
#define _SMCTRL_TIMSTAT_VALUE16_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE16_DEFAULT            (_SMCTRL_TIMSTAT_VALUE16_DEFAULT << 16) /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE17                    (0x1UL << 17)                           /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE17_SHIFT             17                                      /**< Shift value for SMCTRL_VALUE17              */
#define _SMCTRL_TIMSTAT_VALUE17_MASK              0x20000UL                               /**< Bit mask for SMCTRL_VALUE17                 */
#define _SMCTRL_TIMSTAT_VALUE17_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE17_DEFAULT            (_SMCTRL_TIMSTAT_VALUE17_DEFAULT << 17) /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE18                    (0x1UL << 18)                           /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE18_SHIFT             18                                      /**< Shift value for SMCTRL_VALUE18              */
#define _SMCTRL_TIMSTAT_VALUE18_MASK              0x40000UL                               /**< Bit mask for SMCTRL_VALUE18                 */
#define _SMCTRL_TIMSTAT_VALUE18_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE18_DEFAULT            (_SMCTRL_TIMSTAT_VALUE18_DEFAULT << 18) /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE19                    (0x1UL << 19)                           /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE19_SHIFT             19                                      /**< Shift value for SMCTRL_VALUE19              */
#define _SMCTRL_TIMSTAT_VALUE19_MASK              0x80000UL                               /**< Bit mask for SMCTRL_VALUE19                 */
#define _SMCTRL_TIMSTAT_VALUE19_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE19_DEFAULT            (_SMCTRL_TIMSTAT_VALUE19_DEFAULT << 19) /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE20                    (0x1UL << 20)                           /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE20_SHIFT             20                                      /**< Shift value for SMCTRL_VALUE20              */
#define _SMCTRL_TIMSTAT_VALUE20_MASK              0x100000UL                              /**< Bit mask for SMCTRL_VALUE20                 */
#define _SMCTRL_TIMSTAT_VALUE20_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE20_DEFAULT            (_SMCTRL_TIMSTAT_VALUE20_DEFAULT << 20) /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE21                    (0x1UL << 21)                           /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE21_SHIFT             21                                      /**< Shift value for SMCTRL_VALUE21              */
#define _SMCTRL_TIMSTAT_VALUE21_MASK              0x200000UL                              /**< Bit mask for SMCTRL_VALUE21                 */
#define _SMCTRL_TIMSTAT_VALUE21_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE21_DEFAULT            (_SMCTRL_TIMSTAT_VALUE21_DEFAULT << 21) /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE22                    (0x1UL << 22)                           /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE22_SHIFT             22                                      /**< Shift value for SMCTRL_VALUE22              */
#define _SMCTRL_TIMSTAT_VALUE22_MASK              0x400000UL                              /**< Bit mask for SMCTRL_VALUE22                 */
#define _SMCTRL_TIMSTAT_VALUE22_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE22_DEFAULT            (_SMCTRL_TIMSTAT_VALUE22_DEFAULT << 22) /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */
#define SMCTRL_TIMSTAT_VALUE23                    (0x1UL << 23)                           /**< New BitField                                */
#define _SMCTRL_TIMSTAT_VALUE23_SHIFT             23                                      /**< Shift value for SMCTRL_VALUE23              */
#define _SMCTRL_TIMSTAT_VALUE23_MASK              0x800000UL                              /**< Bit mask for SMCTRL_VALUE23                 */
#define _SMCTRL_TIMSTAT_VALUE23_DEFAULT           0x00000000UL                            /**< Mode DEFAULT for SMCTRL_TIMSTAT             */
#define SMCTRL_TIMSTAT_VALUE23_DEFAULT            (_SMCTRL_TIMSTAT_VALUE23_DEFAULT << 23) /**< Shifted mode DEFAULT for SMCTRL_TIMSTAT     */

/* Bit fields for SMCTRL SHIFTS */
#define _SMCTRL_SHIFTS_RESETVALUE                 0x00000000UL                            /**< Default value for SMCTRL_SHIFTS             */
#define _SMCTRL_SHIFTS_MASK                       0x0000000FUL                            /**< Mask for SMCTRL_SHIFTS                      */
#define _SMCTRL_SHIFTS_SHIFTRXF1_SHIFT            0                                       /**< Shift value for SMCTRL_SHIFTRXF1            */
#define _SMCTRL_SHIFTS_SHIFTRXF1_MASK             0x3UL                                   /**< Bit mask for SMCTRL_SHIFTRXF1               */
#define _SMCTRL_SHIFTS_SHIFTRXF1_DEFAULT          0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SHIFTS              */
#define SMCTRL_SHIFTS_SHIFTRXF1_DEFAULT           (_SMCTRL_SHIFTS_SHIFTRXF1_DEFAULT << 0) /**< Shifted mode DEFAULT for SMCTRL_SHIFTS      */
#define _SMCTRL_SHIFTS_SHIFTRXF2_SHIFT            2                                       /**< Shift value for SMCTRL_SHIFTRXF2            */
#define _SMCTRL_SHIFTS_SHIFTRXF2_MASK             0xCUL                                   /**< Bit mask for SMCTRL_SHIFTRXF2               */
#define _SMCTRL_SHIFTS_SHIFTRXF2_DEFAULT          0x00000000UL                            /**< Mode DEFAULT for SMCTRL_SHIFTS              */
#define SMCTRL_SHIFTS_SHIFTRXF2_DEFAULT           (_SMCTRL_SHIFTS_SHIFTRXF2_DEFAULT << 2) /**< Shifted mode DEFAULT for SMCTRL_SHIFTS      */

/* Bit fields for SMCTRL TXDONE */
#define _SMCTRL_TXDONE_RESETVALUE                 0x00000000UL                          /**< Default value for SMCTRL_TXDONE             */
#define _SMCTRL_TXDONE_MASK                       0x00000001UL                          /**< Mask for SMCTRL_TXDONE                      */
#define SMCTRL_TXDONE_TXDONE                      (0x1UL << 0)                          /**< New BitField                                */
#define _SMCTRL_TXDONE_TXDONE_SHIFT               0                                     /**< Shift value for SMCTRL_TXDONE               */
#define _SMCTRL_TXDONE_TXDONE_MASK                0x1UL                                 /**< Bit mask for SMCTRL_TXDONE                  */
#define _SMCTRL_TXDONE_TXDONE_DEFAULT             0x00000000UL                          /**< Mode DEFAULT for SMCTRL_TXDONE              */
#define _SMCTRL_TXDONE_TXDONE_SOFTM               0x00000000UL                          /**< Mode SOFTM for SMCTRL_TXDONE                */
#define _SMCTRL_TXDONE_TXDONE_LEG                 0x00000001UL                          /**< Mode LEG for SMCTRL_TXDONE                  */
#define SMCTRL_TXDONE_TXDONE_DEFAULT              (_SMCTRL_TXDONE_TXDONE_DEFAULT << 0)  /**< Shifted mode DEFAULT for SMCTRL_TXDONE      */
#define SMCTRL_TXDONE_TXDONE_SOFTM                (_SMCTRL_TXDONE_TXDONE_SOFTM << 0)    /**< Shifted mode SOFTM for SMCTRL_TXDONE        */
#define SMCTRL_TXDONE_TXDONE_LEG                  (_SMCTRL_TXDONE_TXDONE_LEG << 0)      /**< Shifted mode LEG for SMCTRL_TXDONE          */

/** @} End of group EFR32FG25_SMCTRL_BitFields */
/** @} End of group EFR32FG25_SMCTRL */
/** @} End of group Parts */

#endif /* EFR32FG25_SMCTRL_H */
