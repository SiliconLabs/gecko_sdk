/**************************************************************************//**
 * @file
 * @brief EFR32FG25 CPDMA register and bit field definitions
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
#ifndef EFR32FG25_CPDMA_H
#define EFR32FG25_CPDMA_H
#define CPDMA_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_CPDMA CPDMA
 * @{
 * @brief EFR32FG25 CPDMA Register Declaration.
 *****************************************************************************/

/** CPDMA FIFO Register Group Declaration. */
typedef struct {
  __IOM uint32_t CONN;                               /**< FIFO Connect Register                              */
} CPDMA_FIFO_TypeDef;

/** CPDMA CH Register Group Declaration. */
typedef struct {
  __IOM uint32_t CFG;                                /**< Channel's Configuration Register                   */
  __IOM uint32_t CTRL;                               /**< Channel's Control Register                         */
  __IOM uint32_t STARTADDR;                          /**< Channel's Data Start Addres Register               */
  uint32_t       RESERVED0[1U];                      /**< Reserved for future use                            */
  __IM uint32_t  STAT;                               /**< Channel's Status Register                          */
  __IM uint32_t  CURRADDR;                           /**< Channel's Current Address                          */
  uint32_t       RESERVED1[6U];                      /**< Reserved for future use                            */
} CPDMA_CH_TypeDef;

/** CPDMA Register Declaration. */
typedef struct {
  __IM uint32_t      IPVERSION;                 /**< IP Version Register                                */
  __IOM uint32_t     EN;                        /**< Module Enable Register                             */
  __IOM uint32_t     SWRST;                     /**< Software Reset Register                            */
  __IOM uint32_t     CTRL;                      /**< CPDMA Control Register                             */
  __IM uint32_t      STATUS;                    /**< CPDMA Status Register                              */
  uint32_t           RESERVED0[4U];             /**< Reserved for future use                            */
  __IOM uint32_t     CHEN;                      /**< Channel Enable Register                            */
  __IOM uint32_t     CHDIS;                     /**< Channel Disable Register                           */
  __IM uint32_t      CHSTATUS;                  /**< Channel Status Register                            */
  __IM uint32_t      CHBUSY;                    /**< Channel Busy Register                              */
  __IOM uint32_t     CHDONEIF;                  /**< Channel Done Register                              */
  __IOM uint32_t     DBGHALT;                   /**< Debug Halt Register                                */
  __IOM uint32_t     SWREQ;                     /**< Software Transfer Request Register                 */
  __IOM uint32_t     REQDIS;                    /**< Request Disable Register                           */
  __IM uint32_t      REQPEND;                   /**< Request Pending Register                           */
  __IOM uint32_t     REQCLEAR;                  /**< Request Clear Register                             */
  __IOM uint32_t     FIFORST;                   /**< FIFO Reset Register                                */
  __IOM uint32_t     IF;                        /**< Interrupt Flag Register                            */
  __IOM uint32_t     IEN;                       /**< Interrupt Enable Register                          */
  __IOM uint32_t     ADDRMSKEN1;                /**< Address Mask 1 Enable Register                     */
  __IOM uint32_t     ADDRMSKEN2;                /**< Address Mask 2 Enable Registe                      */
  __IOM uint32_t     ADDRMSKEN3;                /**< Address Mask 3 Enable Register                     */
  __IOM uint32_t     ADDRMSKEN4;                /**< Address Mask 4 Enable Register                     */
  __IOM uint32_t     ADDRMSK;                   /**< Address Update Mask Register                       */
  __IOM uint32_t     SYNCUPMSK1;                /**< Sync Update Mask 1 Register                        */
  __IOM uint32_t     SYNCUPMSK2;                /**< Sync Update Mask 2 Register                        */
  __IOM uint32_t     SYNCENAB1;                 /**< Sync Enable 1 Register                             */
  __IOM uint32_t     SYNCENAB2;                 /**< Sync Enable 2 Register                             */
  __IOM uint32_t     SYNCINPTHRES;              /**< Sync Input Threshold Register                      */
  __IOM uint32_t     SYNCOUTTHRES;              /**< Sync Output Threshold Register                     */
  __IM uint32_t      SYNCCNTSTAT;               /**< Sync Count Status Register                         */
  uint32_t           RESERVED1[30U];            /**< Reserved for future use                            */
  CPDMA_FIFO_TypeDef FIFO[31U];                 /**< CPDMA FIFO Registers                               */
  uint32_t           RESERVED2[33U];            /**< Reserved for future use                            */
  CPDMA_CH_TypeDef   CH[31U];                   /**< CPDMA Channel Registers                            */
  uint32_t           RESERVED3[524U];           /**< Reserved for future use                            */
  __IM uint32_t      IPVERSION_SET;             /**< IP Version Register                                */
  __IOM uint32_t     EN_SET;                    /**< Module Enable Register                             */
  __IOM uint32_t     SWRST_SET;                 /**< Software Reset Register                            */
  __IOM uint32_t     CTRL_SET;                  /**< CPDMA Control Register                             */
  __IM uint32_t      STATUS_SET;                /**< CPDMA Status Register                              */
  uint32_t           RESERVED4[4U];             /**< Reserved for future use                            */
  __IOM uint32_t     CHEN_SET;                  /**< Channel Enable Register                            */
  __IOM uint32_t     CHDIS_SET;                 /**< Channel Disable Register                           */
  __IM uint32_t      CHSTATUS_SET;              /**< Channel Status Register                            */
  __IM uint32_t      CHBUSY_SET;                /**< Channel Busy Register                              */
  __IOM uint32_t     CHDONEIF_SET;              /**< Channel Done Register                              */
  __IOM uint32_t     DBGHALT_SET;               /**< Debug Halt Register                                */
  __IOM uint32_t     SWREQ_SET;                 /**< Software Transfer Request Register                 */
  __IOM uint32_t     REQDIS_SET;                /**< Request Disable Register                           */
  __IM uint32_t      REQPEND_SET;               /**< Request Pending Register                           */
  __IOM uint32_t     REQCLEAR_SET;              /**< Request Clear Register                             */
  __IOM uint32_t     FIFORST_SET;               /**< FIFO Reset Register                                */
  __IOM uint32_t     IF_SET;                    /**< Interrupt Flag Register                            */
  __IOM uint32_t     IEN_SET;                   /**< Interrupt Enable Register                          */
  __IOM uint32_t     ADDRMSKEN1_SET;            /**< Address Mask 1 Enable Register                     */
  __IOM uint32_t     ADDRMSKEN2_SET;            /**< Address Mask 2 Enable Registe                      */
  __IOM uint32_t     ADDRMSKEN3_SET;            /**< Address Mask 3 Enable Register                     */
  __IOM uint32_t     ADDRMSKEN4_SET;            /**< Address Mask 4 Enable Register                     */
  __IOM uint32_t     ADDRMSK_SET;               /**< Address Update Mask Register                       */
  __IOM uint32_t     SYNCUPMSK1_SET;            /**< Sync Update Mask 1 Register                        */
  __IOM uint32_t     SYNCUPMSK2_SET;            /**< Sync Update Mask 2 Register                        */
  __IOM uint32_t     SYNCENAB1_SET;             /**< Sync Enable 1 Register                             */
  __IOM uint32_t     SYNCENAB2_SET;             /**< Sync Enable 2 Register                             */
  __IOM uint32_t     SYNCINPTHRES_SET;          /**< Sync Input Threshold Register                      */
  __IOM uint32_t     SYNCOUTTHRES_SET;          /**< Sync Output Threshold Register                     */
  __IM uint32_t      SYNCCNTSTAT_SET;           /**< Sync Count Status Register                         */
  uint32_t           RESERVED5[30U];            /**< Reserved for future use                            */
  CPDMA_FIFO_TypeDef FIFO_SET[31U];             /**< CPDMA FIFO Registers                               */
  uint32_t           RESERVED6[33U];            /**< Reserved for future use                            */
  CPDMA_CH_TypeDef   CH_SET[31U];               /**< CPDMA Channel Registers                            */
  uint32_t           RESERVED7[524U];           /**< Reserved for future use                            */
  __IM uint32_t      IPVERSION_CLR;             /**< IP Version Register                                */
  __IOM uint32_t     EN_CLR;                    /**< Module Enable Register                             */
  __IOM uint32_t     SWRST_CLR;                 /**< Software Reset Register                            */
  __IOM uint32_t     CTRL_CLR;                  /**< CPDMA Control Register                             */
  __IM uint32_t      STATUS_CLR;                /**< CPDMA Status Register                              */
  uint32_t           RESERVED8[4U];             /**< Reserved for future use                            */
  __IOM uint32_t     CHEN_CLR;                  /**< Channel Enable Register                            */
  __IOM uint32_t     CHDIS_CLR;                 /**< Channel Disable Register                           */
  __IM uint32_t      CHSTATUS_CLR;              /**< Channel Status Register                            */
  __IM uint32_t      CHBUSY_CLR;                /**< Channel Busy Register                              */
  __IOM uint32_t     CHDONEIF_CLR;              /**< Channel Done Register                              */
  __IOM uint32_t     DBGHALT_CLR;               /**< Debug Halt Register                                */
  __IOM uint32_t     SWREQ_CLR;                 /**< Software Transfer Request Register                 */
  __IOM uint32_t     REQDIS_CLR;                /**< Request Disable Register                           */
  __IM uint32_t      REQPEND_CLR;               /**< Request Pending Register                           */
  __IOM uint32_t     REQCLEAR_CLR;              /**< Request Clear Register                             */
  __IOM uint32_t     FIFORST_CLR;               /**< FIFO Reset Register                                */
  __IOM uint32_t     IF_CLR;                    /**< Interrupt Flag Register                            */
  __IOM uint32_t     IEN_CLR;                   /**< Interrupt Enable Register                          */
  __IOM uint32_t     ADDRMSKEN1_CLR;            /**< Address Mask 1 Enable Register                     */
  __IOM uint32_t     ADDRMSKEN2_CLR;            /**< Address Mask 2 Enable Registe                      */
  __IOM uint32_t     ADDRMSKEN3_CLR;            /**< Address Mask 3 Enable Register                     */
  __IOM uint32_t     ADDRMSKEN4_CLR;            /**< Address Mask 4 Enable Register                     */
  __IOM uint32_t     ADDRMSK_CLR;               /**< Address Update Mask Register                       */
  __IOM uint32_t     SYNCUPMSK1_CLR;            /**< Sync Update Mask 1 Register                        */
  __IOM uint32_t     SYNCUPMSK2_CLR;            /**< Sync Update Mask 2 Register                        */
  __IOM uint32_t     SYNCENAB1_CLR;             /**< Sync Enable 1 Register                             */
  __IOM uint32_t     SYNCENAB2_CLR;             /**< Sync Enable 2 Register                             */
  __IOM uint32_t     SYNCINPTHRES_CLR;          /**< Sync Input Threshold Register                      */
  __IOM uint32_t     SYNCOUTTHRES_CLR;          /**< Sync Output Threshold Register                     */
  __IM uint32_t      SYNCCNTSTAT_CLR;           /**< Sync Count Status Register                         */
  uint32_t           RESERVED9[30U];            /**< Reserved for future use                            */
  CPDMA_FIFO_TypeDef FIFO_CLR[31U];             /**< CPDMA FIFO Registers                               */
  uint32_t           RESERVED10[33U];           /**< Reserved for future use                            */
  CPDMA_CH_TypeDef   CH_CLR[31U];               /**< CPDMA Channel Registers                            */
  uint32_t           RESERVED11[524U];          /**< Reserved for future use                            */
  __IM uint32_t      IPVERSION_TGL;             /**< IP Version Register                                */
  __IOM uint32_t     EN_TGL;                    /**< Module Enable Register                             */
  __IOM uint32_t     SWRST_TGL;                 /**< Software Reset Register                            */
  __IOM uint32_t     CTRL_TGL;                  /**< CPDMA Control Register                             */
  __IM uint32_t      STATUS_TGL;                /**< CPDMA Status Register                              */
  uint32_t           RESERVED12[4U];            /**< Reserved for future use                            */
  __IOM uint32_t     CHEN_TGL;                  /**< Channel Enable Register                            */
  __IOM uint32_t     CHDIS_TGL;                 /**< Channel Disable Register                           */
  __IM uint32_t      CHSTATUS_TGL;              /**< Channel Status Register                            */
  __IM uint32_t      CHBUSY_TGL;                /**< Channel Busy Register                              */
  __IOM uint32_t     CHDONEIF_TGL;              /**< Channel Done Register                              */
  __IOM uint32_t     DBGHALT_TGL;               /**< Debug Halt Register                                */
  __IOM uint32_t     SWREQ_TGL;                 /**< Software Transfer Request Register                 */
  __IOM uint32_t     REQDIS_TGL;                /**< Request Disable Register                           */
  __IM uint32_t      REQPEND_TGL;               /**< Request Pending Register                           */
  __IOM uint32_t     REQCLEAR_TGL;              /**< Request Clear Register                             */
  __IOM uint32_t     FIFORST_TGL;               /**< FIFO Reset Register                                */
  __IOM uint32_t     IF_TGL;                    /**< Interrupt Flag Register                            */
  __IOM uint32_t     IEN_TGL;                   /**< Interrupt Enable Register                          */
  __IOM uint32_t     ADDRMSKEN1_TGL;            /**< Address Mask 1 Enable Register                     */
  __IOM uint32_t     ADDRMSKEN2_TGL;            /**< Address Mask 2 Enable Registe                      */
  __IOM uint32_t     ADDRMSKEN3_TGL;            /**< Address Mask 3 Enable Register                     */
  __IOM uint32_t     ADDRMSKEN4_TGL;            /**< Address Mask 4 Enable Register                     */
  __IOM uint32_t     ADDRMSK_TGL;               /**< Address Update Mask Register                       */
  __IOM uint32_t     SYNCUPMSK1_TGL;            /**< Sync Update Mask 1 Register                        */
  __IOM uint32_t     SYNCUPMSK2_TGL;            /**< Sync Update Mask 2 Register                        */
  __IOM uint32_t     SYNCENAB1_TGL;             /**< Sync Enable 1 Register                             */
  __IOM uint32_t     SYNCENAB2_TGL;             /**< Sync Enable 2 Register                             */
  __IOM uint32_t     SYNCINPTHRES_TGL;          /**< Sync Input Threshold Register                      */
  __IOM uint32_t     SYNCOUTTHRES_TGL;          /**< Sync Output Threshold Register                     */
  __IM uint32_t      SYNCCNTSTAT_TGL;           /**< Sync Count Status Register                         */
  uint32_t           RESERVED13[30U];           /**< Reserved for future use                            */
  CPDMA_FIFO_TypeDef FIFO_TGL[31U];             /**< CPDMA FIFO Registers                               */
  uint32_t           RESERVED14[33U];           /**< Reserved for future use                            */
  CPDMA_CH_TypeDef   CH_TGL[31U];               /**< CPDMA Channel Registers                            */
} CPDMA_TypeDef;
/** @} End of group EFR32FG25_CPDMA */

/**************************************************************************//**
 * @addtogroup EFR32FG25_CPDMA
 * @{
 * @defgroup EFR32FG25_CPDMA_BitFields CPDMA Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for CPDMA IPVERSION */
#define _CPDMA_IPVERSION_RESETVALUE              0x00000001UL                              /**< Default value for CPDMA_IPVERSION           */
#define _CPDMA_IPVERSION_MASK                    0xFFFFFFFFUL                              /**< Mask for CPDMA_IPVERSION                    */
#define _CPDMA_IPVERSION_IPVERSION_SHIFT         0                                         /**< Shift value for CPDMA_IPVERSION             */
#define _CPDMA_IPVERSION_IPVERSION_MASK          0xFFFFFFFFUL                              /**< Bit mask for CPDMA_IPVERSION                */
#define _CPDMA_IPVERSION_IPVERSION_DEFAULT       0x00000001UL                              /**< Mode DEFAULT for CPDMA_IPVERSION            */
#define CPDMA_IPVERSION_IPVERSION_DEFAULT        (_CPDMA_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for CPDMA_IPVERSION    */

/* Bit fields for CPDMA EN */
#define _CPDMA_EN_RESETVALUE                     0x00000000UL                           /**< Default value for CPDMA_EN                  */
#define _CPDMA_EN_MASK                           0x00000003UL                           /**< Mask for CPDMA_EN                           */
#define CPDMA_EN_EN                              (0x1UL << 0)                           /**< Module Enable                               */
#define _CPDMA_EN_EN_SHIFT                       0                                      /**< Shift value for CPDMA_EN                    */
#define _CPDMA_EN_EN_MASK                        0x1UL                                  /**< Bit mask for CPDMA_EN                       */
#define _CPDMA_EN_EN_DEFAULT                     0x00000000UL                           /**< Mode DEFAULT for CPDMA_EN                   */
#define CPDMA_EN_EN_DEFAULT                      (_CPDMA_EN_EN_DEFAULT << 0)            /**< Shifted mode DEFAULT for CPDMA_EN           */
#define CPDMA_EN_DISABLING                       (0x1UL << 1)                           /**< Disablement Busy Status                     */
#define _CPDMA_EN_DISABLING_SHIFT                1                                      /**< Shift value for CPDMA_DISABLING             */
#define _CPDMA_EN_DISABLING_MASK                 0x2UL                                  /**< Bit mask for CPDMA_DISABLING                */
#define _CPDMA_EN_DISABLING_DEFAULT              0x00000000UL                           /**< Mode DEFAULT for CPDMA_EN                   */
#define CPDMA_EN_DISABLING_DEFAULT               (_CPDMA_EN_DISABLING_DEFAULT << 1)     /**< Shifted mode DEFAULT for CPDMA_EN           */

/* Bit fields for CPDMA SWRST */
#define _CPDMA_SWRST_RESETVALUE                  0x00000000UL                           /**< Default value for CPDMA_SWRST               */
#define _CPDMA_SWRST_MASK                        0x00000003UL                           /**< Mask for CPDMA_SWRST                        */
#define CPDMA_SWRST_SWRST                        (0x1UL << 0)                           /**< Software Reset Command                      */
#define _CPDMA_SWRST_SWRST_SHIFT                 0                                      /**< Shift value for CPDMA_SWRST                 */
#define _CPDMA_SWRST_SWRST_MASK                  0x1UL                                  /**< Bit mask for CPDMA_SWRST                    */
#define _CPDMA_SWRST_SWRST_DEFAULT               0x00000000UL                           /**< Mode DEFAULT for CPDMA_SWRST                */
#define CPDMA_SWRST_SWRST_DEFAULT                (_CPDMA_SWRST_SWRST_DEFAULT << 0)      /**< Shifted mode DEFAULT for CPDMA_SWRST        */
#define CPDMA_SWRST_RESETTING                    (0x1UL << 1)                           /**< Software Reset Busy Status                  */
#define _CPDMA_SWRST_RESETTING_SHIFT             1                                      /**< Shift value for CPDMA_RESETTING             */
#define _CPDMA_SWRST_RESETTING_MASK              0x2UL                                  /**< Bit mask for CPDMA_RESETTING                */
#define _CPDMA_SWRST_RESETTING_DEFAULT           0x00000000UL                           /**< Mode DEFAULT for CPDMA_SWRST                */
#define CPDMA_SWRST_RESETTING_DEFAULT            (_CPDMA_SWRST_RESETTING_DEFAULT << 1)  /**< Shifted mode DEFAULT for CPDMA_SWRST        */

/* Bit fields for CPDMA CTRL */
#define _CPDMA_CTRL_RESETVALUE                   0x00000000UL                           /**< Default value for CPDMA_CTRL                */
#define _CPDMA_CTRL_MASK                         0x00001F1FUL                           /**< Mask for CPDMA_CTRL                         */
#define _CPDMA_CTRL_NUMFIXEDIN_SHIFT             0                                      /**< Shift value for CPDMA_NUMFIXEDIN            */
#define _CPDMA_CTRL_NUMFIXEDIN_MASK              0x1FUL                                 /**< Bit mask for CPDMA_NUMFIXEDIN               */
#define _CPDMA_CTRL_NUMFIXEDIN_DEFAULT           0x00000000UL                           /**< Mode DEFAULT for CPDMA_CTRL                 */
#define CPDMA_CTRL_NUMFIXEDIN_DEFAULT            (_CPDMA_CTRL_NUMFIXEDIN_DEFAULT << 0)  /**< Shifted mode DEFAULT for CPDMA_CTRL         */
#define _CPDMA_CTRL_NUMFIXEDOUT_SHIFT            8                                      /**< Shift value for CPDMA_NUMFIXEDOUT           */
#define _CPDMA_CTRL_NUMFIXEDOUT_MASK             0x1F00UL                               /**< Bit mask for CPDMA_NUMFIXEDOUT              */
#define _CPDMA_CTRL_NUMFIXEDOUT_DEFAULT          0x00000000UL                           /**< Mode DEFAULT for CPDMA_CTRL                 */
#define CPDMA_CTRL_NUMFIXEDOUT_DEFAULT           (_CPDMA_CTRL_NUMFIXEDOUT_DEFAULT << 8) /**< Shifted mode DEFAULT for CPDMA_CTRL         */

/* Bit fields for CPDMA STATUS */
#define _CPDMA_STATUS_RESETVALUE                 0x1F010000UL                            /**< Default value for CPDMA_STATUS              */
#define _CPDMA_STATUS_MASK                       0x1F071FFBUL                            /**< Mask for CPDMA_STATUS                       */
#define CPDMA_STATUS_ANYBUSY                     (0x1UL << 0)                            /**< Any CPDMA Channel Busy                      */
#define _CPDMA_STATUS_ANYBUSY_SHIFT              0                                       /**< Shift value for CPDMA_ANYBUSY               */
#define _CPDMA_STATUS_ANYBUSY_MASK               0x1UL                                   /**< Bit mask for CPDMA_ANYBUSY                  */
#define _CPDMA_STATUS_ANYBUSY_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for CPDMA_STATUS               */
#define CPDMA_STATUS_ANYBUSY_DEFAULT             (_CPDMA_STATUS_ANYBUSY_DEFAULT << 0)    /**< Shifted mode DEFAULT for CPDMA_STATUS       */
#define CPDMA_STATUS_ANYREQ                      (0x1UL << 1)                            /**< Any CPDMA Channel Request Pending           */
#define _CPDMA_STATUS_ANYREQ_SHIFT               1                                       /**< Shift value for CPDMA_ANYREQ                */
#define _CPDMA_STATUS_ANYREQ_MASK                0x2UL                                   /**< Bit mask for CPDMA_ANYREQ                   */
#define _CPDMA_STATUS_ANYREQ_DEFAULT             0x00000000UL                            /**< Mode DEFAULT for CPDMA_STATUS               */
#define CPDMA_STATUS_ANYREQ_DEFAULT              (_CPDMA_STATUS_ANYREQ_DEFAULT << 1)     /**< Shifted mode DEFAULT for CPDMA_STATUS       */
#define _CPDMA_STATUS_CHGRANT_SHIFT              3                                       /**< Shift value for CPDMA_CHGRANT               */
#define _CPDMA_STATUS_CHGRANT_MASK               0xF8UL                                  /**< Bit mask for CPDMA_CHGRANT                  */
#define _CPDMA_STATUS_CHGRANT_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for CPDMA_STATUS               */
#define CPDMA_STATUS_CHGRANT_DEFAULT             (_CPDMA_STATUS_CHGRANT_DEFAULT << 3)    /**< Shifted mode DEFAULT for CPDMA_STATUS       */
#define _CPDMA_STATUS_CHERROR_SHIFT              8                                       /**< Shift value for CPDMA_CHERROR               */
#define _CPDMA_STATUS_CHERROR_MASK               0x1F00UL                                /**< Bit mask for CPDMA_CHERROR                  */
#define _CPDMA_STATUS_CHERROR_DEFAULT            0x00000000UL                            /**< Mode DEFAULT for CPDMA_STATUS               */
#define CPDMA_STATUS_CHERROR_DEFAULT             (_CPDMA_STATUS_CHERROR_DEFAULT << 8)    /**< Shifted mode DEFAULT for CPDMA_STATUS       */
#define _CPDMA_STATUS_ILEAVENUM_SHIFT            16                                      /**< Shift value for CPDMA_ILEAVENUM             */
#define _CPDMA_STATUS_ILEAVENUM_MASK             0x70000UL                               /**< Bit mask for CPDMA_ILEAVENUM                */
#define _CPDMA_STATUS_ILEAVENUM_DEFAULT          0x00000001UL                            /**< Mode DEFAULT for CPDMA_STATUS               */
#define CPDMA_STATUS_ILEAVENUM_DEFAULT           (_CPDMA_STATUS_ILEAVENUM_DEFAULT << 16) /**< Shifted mode DEFAULT for CPDMA_STATUS       */
#define _CPDMA_STATUS_CHNUM_SHIFT                24                                      /**< Shift value for CPDMA_CHNUM                 */
#define _CPDMA_STATUS_CHNUM_MASK                 0x1F000000UL                            /**< Bit mask for CPDMA_CHNUM                    */
#define _CPDMA_STATUS_CHNUM_DEFAULT              0x0000001FUL                            /**< Mode DEFAULT for CPDMA_STATUS               */
#define CPDMA_STATUS_CHNUM_DEFAULT               (_CPDMA_STATUS_CHNUM_DEFAULT << 24)     /**< Shifted mode DEFAULT for CPDMA_STATUS       */

/* Bit fields for CPDMA CHEN */
#define _CPDMA_CHEN_RESETVALUE                   0x00000000UL                           /**< Default value for CPDMA_CHEN                */
#define _CPDMA_CHEN_MASK                         0x7FFFFFFFUL                           /**< Mask for CPDMA_CHEN                         */
#define _CPDMA_CHEN_CHEN_SHIFT                   0                                      /**< Shift value for CPDMA_CHEN                  */
#define _CPDMA_CHEN_CHEN_MASK                    0x7FFFFFFFUL                           /**< Bit mask for CPDMA_CHEN                     */
#define _CPDMA_CHEN_CHEN_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_CHEN                 */
#define CPDMA_CHEN_CHEN_DEFAULT                  (_CPDMA_CHEN_CHEN_DEFAULT << 0)        /**< Shifted mode DEFAULT for CPDMA_CHEN         */

/* Bit fields for CPDMA CHDIS */
#define _CPDMA_CHDIS_RESETVALUE                  0x00000000UL                           /**< Default value for CPDMA_CHDIS               */
#define _CPDMA_CHDIS_MASK                        0x7FFFFFFFUL                           /**< Mask for CPDMA_CHDIS                        */
#define _CPDMA_CHDIS_CHDIS_SHIFT                 0                                      /**< Shift value for CPDMA_CHDIS                 */
#define _CPDMA_CHDIS_CHDIS_MASK                  0x7FFFFFFFUL                           /**< Bit mask for CPDMA_CHDIS                    */
#define _CPDMA_CHDIS_CHDIS_DEFAULT               0x00000000UL                           /**< Mode DEFAULT for CPDMA_CHDIS                */
#define CPDMA_CHDIS_CHDIS_DEFAULT                (_CPDMA_CHDIS_CHDIS_DEFAULT << 0)      /**< Shifted mode DEFAULT for CPDMA_CHDIS        */

/* Bit fields for CPDMA CHSTATUS */
#define _CPDMA_CHSTATUS_RESETVALUE               0x00000000UL                            /**< Default value for CPDMA_CHSTATUS            */
#define _CPDMA_CHSTATUS_MASK                     0x7FFFFFFFUL                            /**< Mask for CPDMA_CHSTATUS                     */
#define _CPDMA_CHSTATUS_CHSTATUS_SHIFT           0                                       /**< Shift value for CPDMA_CHSTATUS              */
#define _CPDMA_CHSTATUS_CHSTATUS_MASK            0x7FFFFFFFUL                            /**< Bit mask for CPDMA_CHSTATUS                 */
#define _CPDMA_CHSTATUS_CHSTATUS_DEFAULT         0x00000000UL                            /**< Mode DEFAULT for CPDMA_CHSTATUS             */
#define CPDMA_CHSTATUS_CHSTATUS_DEFAULT          (_CPDMA_CHSTATUS_CHSTATUS_DEFAULT << 0) /**< Shifted mode DEFAULT for CPDMA_CHSTATUS     */

/* Bit fields for CPDMA CHBUSY */
#define _CPDMA_CHBUSY_RESETVALUE                 0x00000000UL                           /**< Default value for CPDMA_CHBUSY              */
#define _CPDMA_CHBUSY_MASK                       0x7FFFFFFFUL                           /**< Mask for CPDMA_CHBUSY                       */
#define _CPDMA_CHBUSY_BUSY_SHIFT                 0                                      /**< Shift value for CPDMA_BUSY                  */
#define _CPDMA_CHBUSY_BUSY_MASK                  0x7FFFFFFFUL                           /**< Bit mask for CPDMA_BUSY                     */
#define _CPDMA_CHBUSY_BUSY_DEFAULT               0x00000000UL                           /**< Mode DEFAULT for CPDMA_CHBUSY               */
#define CPDMA_CHBUSY_BUSY_DEFAULT                (_CPDMA_CHBUSY_BUSY_DEFAULT << 0)      /**< Shifted mode DEFAULT for CPDMA_CHBUSY       */

/* Bit fields for CPDMA CHDONEIF */
#define _CPDMA_CHDONEIF_RESETVALUE               0x00000000UL                               /**< Default value for CPDMA_CHDONEIF            */
#define _CPDMA_CHDONEIF_MASK                     0x7FFFFFFFUL                               /**< Mask for CPDMA_CHDONEIF                     */
#define CPDMA_CHDONEIF_CHDONEIF0                 (0x1UL << 0)                               /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF0_SHIFT          0                                          /**< Shift value for CPDMA_CHDONEIF0             */
#define _CPDMA_CHDONEIF_CHDONEIF0_MASK           0x1UL                                      /**< Bit mask for CPDMA_CHDONEIF0                */
#define _CPDMA_CHDONEIF_CHDONEIF0_DEFAULT        0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF0_DEFAULT         (_CPDMA_CHDONEIF_CHDONEIF0_DEFAULT << 0)   /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF1                 (0x1UL << 1)                               /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF1_SHIFT          1                                          /**< Shift value for CPDMA_CHDONEIF1             */
#define _CPDMA_CHDONEIF_CHDONEIF1_MASK           0x2UL                                      /**< Bit mask for CPDMA_CHDONEIF1                */
#define _CPDMA_CHDONEIF_CHDONEIF1_DEFAULT        0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF1_DEFAULT         (_CPDMA_CHDONEIF_CHDONEIF1_DEFAULT << 1)   /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF2                 (0x1UL << 2)                               /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF2_SHIFT          2                                          /**< Shift value for CPDMA_CHDONEIF2             */
#define _CPDMA_CHDONEIF_CHDONEIF2_MASK           0x4UL                                      /**< Bit mask for CPDMA_CHDONEIF2                */
#define _CPDMA_CHDONEIF_CHDONEIF2_DEFAULT        0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF2_DEFAULT         (_CPDMA_CHDONEIF_CHDONEIF2_DEFAULT << 2)   /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF3                 (0x1UL << 3)                               /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF3_SHIFT          3                                          /**< Shift value for CPDMA_CHDONEIF3             */
#define _CPDMA_CHDONEIF_CHDONEIF3_MASK           0x8UL                                      /**< Bit mask for CPDMA_CHDONEIF3                */
#define _CPDMA_CHDONEIF_CHDONEIF3_DEFAULT        0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF3_DEFAULT         (_CPDMA_CHDONEIF_CHDONEIF3_DEFAULT << 3)   /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF4                 (0x1UL << 4)                               /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF4_SHIFT          4                                          /**< Shift value for CPDMA_CHDONEIF4             */
#define _CPDMA_CHDONEIF_CHDONEIF4_MASK           0x10UL                                     /**< Bit mask for CPDMA_CHDONEIF4                */
#define _CPDMA_CHDONEIF_CHDONEIF4_DEFAULT        0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF4_DEFAULT         (_CPDMA_CHDONEIF_CHDONEIF4_DEFAULT << 4)   /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF5                 (0x1UL << 5)                               /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF5_SHIFT          5                                          /**< Shift value for CPDMA_CHDONEIF5             */
#define _CPDMA_CHDONEIF_CHDONEIF5_MASK           0x20UL                                     /**< Bit mask for CPDMA_CHDONEIF5                */
#define _CPDMA_CHDONEIF_CHDONEIF5_DEFAULT        0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF5_DEFAULT         (_CPDMA_CHDONEIF_CHDONEIF5_DEFAULT << 5)   /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF6                 (0x1UL << 6)                               /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF6_SHIFT          6                                          /**< Shift value for CPDMA_CHDONEIF6             */
#define _CPDMA_CHDONEIF_CHDONEIF6_MASK           0x40UL                                     /**< Bit mask for CPDMA_CHDONEIF6                */
#define _CPDMA_CHDONEIF_CHDONEIF6_DEFAULT        0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF6_DEFAULT         (_CPDMA_CHDONEIF_CHDONEIF6_DEFAULT << 6)   /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF7                 (0x1UL << 7)                               /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF7_SHIFT          7                                          /**< Shift value for CPDMA_CHDONEIF7             */
#define _CPDMA_CHDONEIF_CHDONEIF7_MASK           0x80UL                                     /**< Bit mask for CPDMA_CHDONEIF7                */
#define _CPDMA_CHDONEIF_CHDONEIF7_DEFAULT        0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF7_DEFAULT         (_CPDMA_CHDONEIF_CHDONEIF7_DEFAULT << 7)   /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF8                 (0x1UL << 8)                               /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF8_SHIFT          8                                          /**< Shift value for CPDMA_CHDONEIF8             */
#define _CPDMA_CHDONEIF_CHDONEIF8_MASK           0x100UL                                    /**< Bit mask for CPDMA_CHDONEIF8                */
#define _CPDMA_CHDONEIF_CHDONEIF8_DEFAULT        0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF8_DEFAULT         (_CPDMA_CHDONEIF_CHDONEIF8_DEFAULT << 8)   /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF9                 (0x1UL << 9)                               /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF9_SHIFT          9                                          /**< Shift value for CPDMA_CHDONEIF9             */
#define _CPDMA_CHDONEIF_CHDONEIF9_MASK           0x200UL                                    /**< Bit mask for CPDMA_CHDONEIF9                */
#define _CPDMA_CHDONEIF_CHDONEIF9_DEFAULT        0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF9_DEFAULT         (_CPDMA_CHDONEIF_CHDONEIF9_DEFAULT << 9)   /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF10                (0x1UL << 10)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF10_SHIFT         10                                         /**< Shift value for CPDMA_CHDONEIF10            */
#define _CPDMA_CHDONEIF_CHDONEIF10_MASK          0x400UL                                    /**< Bit mask for CPDMA_CHDONEIF10               */
#define _CPDMA_CHDONEIF_CHDONEIF10_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF10_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF10_DEFAULT << 10) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF11                (0x1UL << 11)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF11_SHIFT         11                                         /**< Shift value for CPDMA_CHDONEIF11            */
#define _CPDMA_CHDONEIF_CHDONEIF11_MASK          0x800UL                                    /**< Bit mask for CPDMA_CHDONEIF11               */
#define _CPDMA_CHDONEIF_CHDONEIF11_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF11_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF11_DEFAULT << 11) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF12                (0x1UL << 12)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF12_SHIFT         12                                         /**< Shift value for CPDMA_CHDONEIF12            */
#define _CPDMA_CHDONEIF_CHDONEIF12_MASK          0x1000UL                                   /**< Bit mask for CPDMA_CHDONEIF12               */
#define _CPDMA_CHDONEIF_CHDONEIF12_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF12_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF12_DEFAULT << 12) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF13                (0x1UL << 13)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF13_SHIFT         13                                         /**< Shift value for CPDMA_CHDONEIF13            */
#define _CPDMA_CHDONEIF_CHDONEIF13_MASK          0x2000UL                                   /**< Bit mask for CPDMA_CHDONEIF13               */
#define _CPDMA_CHDONEIF_CHDONEIF13_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF13_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF13_DEFAULT << 13) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF14                (0x1UL << 14)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF14_SHIFT         14                                         /**< Shift value for CPDMA_CHDONEIF14            */
#define _CPDMA_CHDONEIF_CHDONEIF14_MASK          0x4000UL                                   /**< Bit mask for CPDMA_CHDONEIF14               */
#define _CPDMA_CHDONEIF_CHDONEIF14_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF14_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF14_DEFAULT << 14) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF15                (0x1UL << 15)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF15_SHIFT         15                                         /**< Shift value for CPDMA_CHDONEIF15            */
#define _CPDMA_CHDONEIF_CHDONEIF15_MASK          0x8000UL                                   /**< Bit mask for CPDMA_CHDONEIF15               */
#define _CPDMA_CHDONEIF_CHDONEIF15_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF15_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF15_DEFAULT << 15) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF16                (0x1UL << 16)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF16_SHIFT         16                                         /**< Shift value for CPDMA_CHDONEIF16            */
#define _CPDMA_CHDONEIF_CHDONEIF16_MASK          0x10000UL                                  /**< Bit mask for CPDMA_CHDONEIF16               */
#define _CPDMA_CHDONEIF_CHDONEIF16_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF16_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF16_DEFAULT << 16) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF17                (0x1UL << 17)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF17_SHIFT         17                                         /**< Shift value for CPDMA_CHDONEIF17            */
#define _CPDMA_CHDONEIF_CHDONEIF17_MASK          0x20000UL                                  /**< Bit mask for CPDMA_CHDONEIF17               */
#define _CPDMA_CHDONEIF_CHDONEIF17_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF17_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF17_DEFAULT << 17) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF18                (0x1UL << 18)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF18_SHIFT         18                                         /**< Shift value for CPDMA_CHDONEIF18            */
#define _CPDMA_CHDONEIF_CHDONEIF18_MASK          0x40000UL                                  /**< Bit mask for CPDMA_CHDONEIF18               */
#define _CPDMA_CHDONEIF_CHDONEIF18_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF18_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF18_DEFAULT << 18) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF19                (0x1UL << 19)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF19_SHIFT         19                                         /**< Shift value for CPDMA_CHDONEIF19            */
#define _CPDMA_CHDONEIF_CHDONEIF19_MASK          0x80000UL                                  /**< Bit mask for CPDMA_CHDONEIF19               */
#define _CPDMA_CHDONEIF_CHDONEIF19_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF19_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF19_DEFAULT << 19) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF20                (0x1UL << 20)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF20_SHIFT         20                                         /**< Shift value for CPDMA_CHDONEIF20            */
#define _CPDMA_CHDONEIF_CHDONEIF20_MASK          0x100000UL                                 /**< Bit mask for CPDMA_CHDONEIF20               */
#define _CPDMA_CHDONEIF_CHDONEIF20_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF20_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF20_DEFAULT << 20) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF21                (0x1UL << 21)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF21_SHIFT         21                                         /**< Shift value for CPDMA_CHDONEIF21            */
#define _CPDMA_CHDONEIF_CHDONEIF21_MASK          0x200000UL                                 /**< Bit mask for CPDMA_CHDONEIF21               */
#define _CPDMA_CHDONEIF_CHDONEIF21_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF21_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF21_DEFAULT << 21) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF22                (0x1UL << 22)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF22_SHIFT         22                                         /**< Shift value for CPDMA_CHDONEIF22            */
#define _CPDMA_CHDONEIF_CHDONEIF22_MASK          0x400000UL                                 /**< Bit mask for CPDMA_CHDONEIF22               */
#define _CPDMA_CHDONEIF_CHDONEIF22_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF22_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF22_DEFAULT << 22) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF23                (0x1UL << 23)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF23_SHIFT         23                                         /**< Shift value for CPDMA_CHDONEIF23            */
#define _CPDMA_CHDONEIF_CHDONEIF23_MASK          0x800000UL                                 /**< Bit mask for CPDMA_CHDONEIF23               */
#define _CPDMA_CHDONEIF_CHDONEIF23_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF23_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF23_DEFAULT << 23) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF24                (0x1UL << 24)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF24_SHIFT         24                                         /**< Shift value for CPDMA_CHDONEIF24            */
#define _CPDMA_CHDONEIF_CHDONEIF24_MASK          0x1000000UL                                /**< Bit mask for CPDMA_CHDONEIF24               */
#define _CPDMA_CHDONEIF_CHDONEIF24_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF24_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF24_DEFAULT << 24) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF25                (0x1UL << 25)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF25_SHIFT         25                                         /**< Shift value for CPDMA_CHDONEIF25            */
#define _CPDMA_CHDONEIF_CHDONEIF25_MASK          0x2000000UL                                /**< Bit mask for CPDMA_CHDONEIF25               */
#define _CPDMA_CHDONEIF_CHDONEIF25_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF25_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF25_DEFAULT << 25) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF26                (0x1UL << 26)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF26_SHIFT         26                                         /**< Shift value for CPDMA_CHDONEIF26            */
#define _CPDMA_CHDONEIF_CHDONEIF26_MASK          0x4000000UL                                /**< Bit mask for CPDMA_CHDONEIF26               */
#define _CPDMA_CHDONEIF_CHDONEIF26_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF26_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF26_DEFAULT << 26) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF27                (0x1UL << 27)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF27_SHIFT         27                                         /**< Shift value for CPDMA_CHDONEIF27            */
#define _CPDMA_CHDONEIF_CHDONEIF27_MASK          0x8000000UL                                /**< Bit mask for CPDMA_CHDONEIF27               */
#define _CPDMA_CHDONEIF_CHDONEIF27_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF27_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF27_DEFAULT << 27) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF28                (0x1UL << 28)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF28_SHIFT         28                                         /**< Shift value for CPDMA_CHDONEIF28            */
#define _CPDMA_CHDONEIF_CHDONEIF28_MASK          0x10000000UL                               /**< Bit mask for CPDMA_CHDONEIF28               */
#define _CPDMA_CHDONEIF_CHDONEIF28_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF28_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF28_DEFAULT << 28) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF29                (0x1UL << 29)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF29_SHIFT         29                                         /**< Shift value for CPDMA_CHDONEIF29            */
#define _CPDMA_CHDONEIF_CHDONEIF29_MASK          0x20000000UL                               /**< Bit mask for CPDMA_CHDONEIF29               */
#define _CPDMA_CHDONEIF_CHDONEIF29_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF29_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF29_DEFAULT << 29) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */
#define CPDMA_CHDONEIF_CHDONEIF30                (0x1UL << 30)                              /**< Channel Done Flag                           */
#define _CPDMA_CHDONEIF_CHDONEIF30_SHIFT         30                                         /**< Shift value for CPDMA_CHDONEIF30            */
#define _CPDMA_CHDONEIF_CHDONEIF30_MASK          0x40000000UL                               /**< Bit mask for CPDMA_CHDONEIF30               */
#define _CPDMA_CHDONEIF_CHDONEIF30_DEFAULT       0x00000000UL                               /**< Mode DEFAULT for CPDMA_CHDONEIF             */
#define CPDMA_CHDONEIF_CHDONEIF30_DEFAULT        (_CPDMA_CHDONEIF_CHDONEIF30_DEFAULT << 30) /**< Shifted mode DEFAULT for CPDMA_CHDONEIF     */

/* Bit fields for CPDMA DBGHALT */
#define _CPDMA_DBGHALT_RESETVALUE                0x00000000UL                           /**< Default value for CPDMA_DBGHALT             */
#define _CPDMA_DBGHALT_MASK                      0x7FFFFFFFUL                           /**< Mask for CPDMA_DBGHALT                      */
#define _CPDMA_DBGHALT_DBGHALT_SHIFT             0                                      /**< Shift value for CPDMA_DBGHALT               */
#define _CPDMA_DBGHALT_DBGHALT_MASK              0x7FFFFFFFUL                           /**< Bit mask for CPDMA_DBGHALT                  */
#define _CPDMA_DBGHALT_DBGHALT_DEFAULT           0x00000000UL                           /**< Mode DEFAULT for CPDMA_DBGHALT              */
#define CPDMA_DBGHALT_DBGHALT_DEFAULT            (_CPDMA_DBGHALT_DBGHALT_DEFAULT << 0)  /**< Shifted mode DEFAULT for CPDMA_DBGHALT      */

/* Bit fields for CPDMA SWREQ */
#define _CPDMA_SWREQ_RESETVALUE                  0x00000000UL                           /**< Default value for CPDMA_SWREQ               */
#define _CPDMA_SWREQ_MASK                        0x7FFFFFFFUL                           /**< Mask for CPDMA_SWREQ                        */
#define _CPDMA_SWREQ_SWREQ_SHIFT                 0                                      /**< Shift value for CPDMA_SWREQ                 */
#define _CPDMA_SWREQ_SWREQ_MASK                  0x7FFFFFFFUL                           /**< Bit mask for CPDMA_SWREQ                    */
#define _CPDMA_SWREQ_SWREQ_DEFAULT               0x00000000UL                           /**< Mode DEFAULT for CPDMA_SWREQ                */
#define CPDMA_SWREQ_SWREQ_DEFAULT                (_CPDMA_SWREQ_SWREQ_DEFAULT << 0)      /**< Shifted mode DEFAULT for CPDMA_SWREQ        */

/* Bit fields for CPDMA REQDIS */
#define _CPDMA_REQDIS_RESETVALUE                 0x00000000UL                           /**< Default value for CPDMA_REQDIS              */
#define _CPDMA_REQDIS_MASK                       0x7FFFFFFFUL                           /**< Mask for CPDMA_REQDIS                       */
#define _CPDMA_REQDIS_REQDIS_SHIFT               0                                      /**< Shift value for CPDMA_REQDIS                */
#define _CPDMA_REQDIS_REQDIS_MASK                0x7FFFFFFFUL                           /**< Bit mask for CPDMA_REQDIS                   */
#define _CPDMA_REQDIS_REQDIS_DEFAULT             0x00000000UL                           /**< Mode DEFAULT for CPDMA_REQDIS               */
#define CPDMA_REQDIS_REQDIS_DEFAULT              (_CPDMA_REQDIS_REQDIS_DEFAULT << 0)    /**< Shifted mode DEFAULT for CPDMA_REQDIS       */

/* Bit fields for CPDMA REQPEND */
#define _CPDMA_REQPEND_RESETVALUE                0x00000000UL                           /**< Default value for CPDMA_REQPEND             */
#define _CPDMA_REQPEND_MASK                      0x7FFFFFFFUL                           /**< Mask for CPDMA_REQPEND                      */
#define _CPDMA_REQPEND_REQPEND_SHIFT             0                                      /**< Shift value for CPDMA_REQPEND               */
#define _CPDMA_REQPEND_REQPEND_MASK              0x7FFFFFFFUL                           /**< Bit mask for CPDMA_REQPEND                  */
#define _CPDMA_REQPEND_REQPEND_DEFAULT           0x00000000UL                           /**< Mode DEFAULT for CPDMA_REQPEND              */
#define CPDMA_REQPEND_REQPEND_DEFAULT            (_CPDMA_REQPEND_REQPEND_DEFAULT << 0)  /**< Shifted mode DEFAULT for CPDMA_REQPEND      */

/* Bit fields for CPDMA REQCLEAR */
#define _CPDMA_REQCLEAR_RESETVALUE               0x00000000UL                            /**< Default value for CPDMA_REQCLEAR            */
#define _CPDMA_REQCLEAR_MASK                     0x7FFFFFFFUL                            /**< Mask for CPDMA_REQCLEAR                     */
#define _CPDMA_REQCLEAR_REQCLEAR_SHIFT           0                                       /**< Shift value for CPDMA_REQCLEAR              */
#define _CPDMA_REQCLEAR_REQCLEAR_MASK            0x7FFFFFFFUL                            /**< Bit mask for CPDMA_REQCLEAR                 */
#define _CPDMA_REQCLEAR_REQCLEAR_DEFAULT         0x00000000UL                            /**< Mode DEFAULT for CPDMA_REQCLEAR             */
#define CPDMA_REQCLEAR_REQCLEAR_DEFAULT          (_CPDMA_REQCLEAR_REQCLEAR_DEFAULT << 0) /**< Shifted mode DEFAULT for CPDMA_REQCLEAR     */

/* Bit fields for CPDMA FIFORST */
#define _CPDMA_FIFORST_RESETVALUE                0x00000000UL                           /**< Default value for CPDMA_FIFORST             */
#define _CPDMA_FIFORST_MASK                      0x7FFFFFFFUL                           /**< Mask for CPDMA_FIFORST                      */
#define _CPDMA_FIFORST_FIFORST_SHIFT             0                                      /**< Shift value for CPDMA_FIFORST               */
#define _CPDMA_FIFORST_FIFORST_MASK              0x7FFFFFFFUL                           /**< Bit mask for CPDMA_FIFORST                  */
#define _CPDMA_FIFORST_FIFORST_DEFAULT           0x00000000UL                           /**< Mode DEFAULT for CPDMA_FIFORST              */
#define CPDMA_FIFORST_FIFORST_DEFAULT            (_CPDMA_FIFORST_FIFORST_DEFAULT << 0)  /**< Shifted mode DEFAULT for CPDMA_FIFORST      */

/* Bit fields for CPDMA IF */
#define _CPDMA_IF_RESETVALUE                     0x00000000UL                           /**< Default value for CPDMA_IF                  */
#define _CPDMA_IF_MASK                           0xFFFFFFFFUL                           /**< Mask for CPDMA_IF                           */
#define CPDMA_IF_DONE0                           (0x1UL << 0)                           /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE0_SHIFT                    0                                      /**< Shift value for CPDMA_DONE0                 */
#define _CPDMA_IF_DONE0_MASK                     0x1UL                                  /**< Bit mask for CPDMA_DONE0                    */
#define _CPDMA_IF_DONE0_DEFAULT                  0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE0_DEFAULT                   (_CPDMA_IF_DONE0_DEFAULT << 0)         /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE1                           (0x1UL << 1)                           /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE1_SHIFT                    1                                      /**< Shift value for CPDMA_DONE1                 */
#define _CPDMA_IF_DONE1_MASK                     0x2UL                                  /**< Bit mask for CPDMA_DONE1                    */
#define _CPDMA_IF_DONE1_DEFAULT                  0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE1_DEFAULT                   (_CPDMA_IF_DONE1_DEFAULT << 1)         /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE2                           (0x1UL << 2)                           /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE2_SHIFT                    2                                      /**< Shift value for CPDMA_DONE2                 */
#define _CPDMA_IF_DONE2_MASK                     0x4UL                                  /**< Bit mask for CPDMA_DONE2                    */
#define _CPDMA_IF_DONE2_DEFAULT                  0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE2_DEFAULT                   (_CPDMA_IF_DONE2_DEFAULT << 2)         /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE3                           (0x1UL << 3)                           /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE3_SHIFT                    3                                      /**< Shift value for CPDMA_DONE3                 */
#define _CPDMA_IF_DONE3_MASK                     0x8UL                                  /**< Bit mask for CPDMA_DONE3                    */
#define _CPDMA_IF_DONE3_DEFAULT                  0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE3_DEFAULT                   (_CPDMA_IF_DONE3_DEFAULT << 3)         /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE4                           (0x1UL << 4)                           /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE4_SHIFT                    4                                      /**< Shift value for CPDMA_DONE4                 */
#define _CPDMA_IF_DONE4_MASK                     0x10UL                                 /**< Bit mask for CPDMA_DONE4                    */
#define _CPDMA_IF_DONE4_DEFAULT                  0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE4_DEFAULT                   (_CPDMA_IF_DONE4_DEFAULT << 4)         /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE5                           (0x1UL << 5)                           /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE5_SHIFT                    5                                      /**< Shift value for CPDMA_DONE5                 */
#define _CPDMA_IF_DONE5_MASK                     0x20UL                                 /**< Bit mask for CPDMA_DONE5                    */
#define _CPDMA_IF_DONE5_DEFAULT                  0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE5_DEFAULT                   (_CPDMA_IF_DONE5_DEFAULT << 5)         /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE6                           (0x1UL << 6)                           /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE6_SHIFT                    6                                      /**< Shift value for CPDMA_DONE6                 */
#define _CPDMA_IF_DONE6_MASK                     0x40UL                                 /**< Bit mask for CPDMA_DONE6                    */
#define _CPDMA_IF_DONE6_DEFAULT                  0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE6_DEFAULT                   (_CPDMA_IF_DONE6_DEFAULT << 6)         /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE7                           (0x1UL << 7)                           /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE7_SHIFT                    7                                      /**< Shift value for CPDMA_DONE7                 */
#define _CPDMA_IF_DONE7_MASK                     0x80UL                                 /**< Bit mask for CPDMA_DONE7                    */
#define _CPDMA_IF_DONE7_DEFAULT                  0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE7_DEFAULT                   (_CPDMA_IF_DONE7_DEFAULT << 7)         /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE8                           (0x1UL << 8)                           /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE8_SHIFT                    8                                      /**< Shift value for CPDMA_DONE8                 */
#define _CPDMA_IF_DONE8_MASK                     0x100UL                                /**< Bit mask for CPDMA_DONE8                    */
#define _CPDMA_IF_DONE8_DEFAULT                  0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE8_DEFAULT                   (_CPDMA_IF_DONE8_DEFAULT << 8)         /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE9                           (0x1UL << 9)                           /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE9_SHIFT                    9                                      /**< Shift value for CPDMA_DONE9                 */
#define _CPDMA_IF_DONE9_MASK                     0x200UL                                /**< Bit mask for CPDMA_DONE9                    */
#define _CPDMA_IF_DONE9_DEFAULT                  0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE9_DEFAULT                   (_CPDMA_IF_DONE9_DEFAULT << 9)         /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE10                          (0x1UL << 10)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE10_SHIFT                   10                                     /**< Shift value for CPDMA_DONE10                */
#define _CPDMA_IF_DONE10_MASK                    0x400UL                                /**< Bit mask for CPDMA_DONE10                   */
#define _CPDMA_IF_DONE10_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE10_DEFAULT                  (_CPDMA_IF_DONE10_DEFAULT << 10)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE11                          (0x1UL << 11)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE11_SHIFT                   11                                     /**< Shift value for CPDMA_DONE11                */
#define _CPDMA_IF_DONE11_MASK                    0x800UL                                /**< Bit mask for CPDMA_DONE11                   */
#define _CPDMA_IF_DONE11_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE11_DEFAULT                  (_CPDMA_IF_DONE11_DEFAULT << 11)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE12                          (0x1UL << 12)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE12_SHIFT                   12                                     /**< Shift value for CPDMA_DONE12                */
#define _CPDMA_IF_DONE12_MASK                    0x1000UL                               /**< Bit mask for CPDMA_DONE12                   */
#define _CPDMA_IF_DONE12_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE12_DEFAULT                  (_CPDMA_IF_DONE12_DEFAULT << 12)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE13                          (0x1UL << 13)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE13_SHIFT                   13                                     /**< Shift value for CPDMA_DONE13                */
#define _CPDMA_IF_DONE13_MASK                    0x2000UL                               /**< Bit mask for CPDMA_DONE13                   */
#define _CPDMA_IF_DONE13_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE13_DEFAULT                  (_CPDMA_IF_DONE13_DEFAULT << 13)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE14                          (0x1UL << 14)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE14_SHIFT                   14                                     /**< Shift value for CPDMA_DONE14                */
#define _CPDMA_IF_DONE14_MASK                    0x4000UL                               /**< Bit mask for CPDMA_DONE14                   */
#define _CPDMA_IF_DONE14_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE14_DEFAULT                  (_CPDMA_IF_DONE14_DEFAULT << 14)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE15                          (0x1UL << 15)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE15_SHIFT                   15                                     /**< Shift value for CPDMA_DONE15                */
#define _CPDMA_IF_DONE15_MASK                    0x8000UL                               /**< Bit mask for CPDMA_DONE15                   */
#define _CPDMA_IF_DONE15_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE15_DEFAULT                  (_CPDMA_IF_DONE15_DEFAULT << 15)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE16                          (0x1UL << 16)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE16_SHIFT                   16                                     /**< Shift value for CPDMA_DONE16                */
#define _CPDMA_IF_DONE16_MASK                    0x10000UL                              /**< Bit mask for CPDMA_DONE16                   */
#define _CPDMA_IF_DONE16_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE16_DEFAULT                  (_CPDMA_IF_DONE16_DEFAULT << 16)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE17                          (0x1UL << 17)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE17_SHIFT                   17                                     /**< Shift value for CPDMA_DONE17                */
#define _CPDMA_IF_DONE17_MASK                    0x20000UL                              /**< Bit mask for CPDMA_DONE17                   */
#define _CPDMA_IF_DONE17_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE17_DEFAULT                  (_CPDMA_IF_DONE17_DEFAULT << 17)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE18                          (0x1UL << 18)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE18_SHIFT                   18                                     /**< Shift value for CPDMA_DONE18                */
#define _CPDMA_IF_DONE18_MASK                    0x40000UL                              /**< Bit mask for CPDMA_DONE18                   */
#define _CPDMA_IF_DONE18_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE18_DEFAULT                  (_CPDMA_IF_DONE18_DEFAULT << 18)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE19                          (0x1UL << 19)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE19_SHIFT                   19                                     /**< Shift value for CPDMA_DONE19                */
#define _CPDMA_IF_DONE19_MASK                    0x80000UL                              /**< Bit mask for CPDMA_DONE19                   */
#define _CPDMA_IF_DONE19_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE19_DEFAULT                  (_CPDMA_IF_DONE19_DEFAULT << 19)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE20                          (0x1UL << 20)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE20_SHIFT                   20                                     /**< Shift value for CPDMA_DONE20                */
#define _CPDMA_IF_DONE20_MASK                    0x100000UL                             /**< Bit mask for CPDMA_DONE20                   */
#define _CPDMA_IF_DONE20_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE20_DEFAULT                  (_CPDMA_IF_DONE20_DEFAULT << 20)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE21                          (0x1UL << 21)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE21_SHIFT                   21                                     /**< Shift value for CPDMA_DONE21                */
#define _CPDMA_IF_DONE21_MASK                    0x200000UL                             /**< Bit mask for CPDMA_DONE21                   */
#define _CPDMA_IF_DONE21_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE21_DEFAULT                  (_CPDMA_IF_DONE21_DEFAULT << 21)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE22                          (0x1UL << 22)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE22_SHIFT                   22                                     /**< Shift value for CPDMA_DONE22                */
#define _CPDMA_IF_DONE22_MASK                    0x400000UL                             /**< Bit mask for CPDMA_DONE22                   */
#define _CPDMA_IF_DONE22_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE22_DEFAULT                  (_CPDMA_IF_DONE22_DEFAULT << 22)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE23                          (0x1UL << 23)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE23_SHIFT                   23                                     /**< Shift value for CPDMA_DONE23                */
#define _CPDMA_IF_DONE23_MASK                    0x800000UL                             /**< Bit mask for CPDMA_DONE23                   */
#define _CPDMA_IF_DONE23_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE23_DEFAULT                  (_CPDMA_IF_DONE23_DEFAULT << 23)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE24                          (0x1UL << 24)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE24_SHIFT                   24                                     /**< Shift value for CPDMA_DONE24                */
#define _CPDMA_IF_DONE24_MASK                    0x1000000UL                            /**< Bit mask for CPDMA_DONE24                   */
#define _CPDMA_IF_DONE24_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE24_DEFAULT                  (_CPDMA_IF_DONE24_DEFAULT << 24)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE25                          (0x1UL << 25)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE25_SHIFT                   25                                     /**< Shift value for CPDMA_DONE25                */
#define _CPDMA_IF_DONE25_MASK                    0x2000000UL                            /**< Bit mask for CPDMA_DONE25                   */
#define _CPDMA_IF_DONE25_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE25_DEFAULT                  (_CPDMA_IF_DONE25_DEFAULT << 25)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE26                          (0x1UL << 26)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE26_SHIFT                   26                                     /**< Shift value for CPDMA_DONE26                */
#define _CPDMA_IF_DONE26_MASK                    0x4000000UL                            /**< Bit mask for CPDMA_DONE26                   */
#define _CPDMA_IF_DONE26_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE26_DEFAULT                  (_CPDMA_IF_DONE26_DEFAULT << 26)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE27                          (0x1UL << 27)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE27_SHIFT                   27                                     /**< Shift value for CPDMA_DONE27                */
#define _CPDMA_IF_DONE27_MASK                    0x8000000UL                            /**< Bit mask for CPDMA_DONE27                   */
#define _CPDMA_IF_DONE27_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE27_DEFAULT                  (_CPDMA_IF_DONE27_DEFAULT << 27)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE28                          (0x1UL << 28)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE28_SHIFT                   28                                     /**< Shift value for CPDMA_DONE28                */
#define _CPDMA_IF_DONE28_MASK                    0x10000000UL                           /**< Bit mask for CPDMA_DONE28                   */
#define _CPDMA_IF_DONE28_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE28_DEFAULT                  (_CPDMA_IF_DONE28_DEFAULT << 28)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE29                          (0x1UL << 29)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE29_SHIFT                   29                                     /**< Shift value for CPDMA_DONE29                */
#define _CPDMA_IF_DONE29_MASK                    0x20000000UL                           /**< Bit mask for CPDMA_DONE29                   */
#define _CPDMA_IF_DONE29_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE29_DEFAULT                  (_CPDMA_IF_DONE29_DEFAULT << 29)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_DONE30                          (0x1UL << 30)                          /**< Channel Done Interrupt Flag                 */
#define _CPDMA_IF_DONE30_SHIFT                   30                                     /**< Shift value for CPDMA_DONE30                */
#define _CPDMA_IF_DONE30_MASK                    0x40000000UL                           /**< Bit mask for CPDMA_DONE30                   */
#define _CPDMA_IF_DONE30_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_DONE30_DEFAULT                  (_CPDMA_IF_DONE30_DEFAULT << 30)       /**< Shifted mode DEFAULT for CPDMA_IF           */
#define CPDMA_IF_ERROR                           (0x1UL << 31)                          /**< Bus Error Interrupt Flag                    */
#define _CPDMA_IF_ERROR_SHIFT                    31                                     /**< Shift value for CPDMA_ERROR                 */
#define _CPDMA_IF_ERROR_MASK                     0x80000000UL                           /**< Bit mask for CPDMA_ERROR                    */
#define _CPDMA_IF_ERROR_DEFAULT                  0x00000000UL                           /**< Mode DEFAULT for CPDMA_IF                   */
#define CPDMA_IF_ERROR_DEFAULT                   (_CPDMA_IF_ERROR_DEFAULT << 31)        /**< Shifted mode DEFAULT for CPDMA_IF           */

/* Bit fields for CPDMA IEN */
#define _CPDMA_IEN_RESETVALUE                    0x00000000UL                           /**< Default value for CPDMA_IEN                 */
#define _CPDMA_IEN_MASK                          0xFFFFFFFFUL                           /**< Mask for CPDMA_IEN                          */
#define _CPDMA_IEN_CHDONE_SHIFT                  0                                      /**< Shift value for CPDMA_CHDONE                */
#define _CPDMA_IEN_CHDONE_MASK                   0x7FFFFFFFUL                           /**< Bit mask for CPDMA_CHDONE                   */
#define _CPDMA_IEN_CHDONE_DEFAULT                0x00000000UL                           /**< Mode DEFAULT for CPDMA_IEN                  */
#define CPDMA_IEN_CHDONE_DEFAULT                 (_CPDMA_IEN_CHDONE_DEFAULT << 0)       /**< Shifted mode DEFAULT for CPDMA_IEN          */
#define CPDMA_IEN_ERROR                          (0x1UL << 31)                          /**< Bus Error Int Enable                        */
#define _CPDMA_IEN_ERROR_SHIFT                   31                                     /**< Shift value for CPDMA_ERROR                 */
#define _CPDMA_IEN_ERROR_MASK                    0x80000000UL                           /**< Bit mask for CPDMA_ERROR                    */
#define _CPDMA_IEN_ERROR_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for CPDMA_IEN                  */
#define CPDMA_IEN_ERROR_DEFAULT                  (_CPDMA_IEN_ERROR_DEFAULT << 31)       /**< Shifted mode DEFAULT for CPDMA_IEN          */

/* Bit fields for CPDMA ADDRMSKEN1 */
#define _CPDMA_ADDRMSKEN1_RESETVALUE             0x00000000UL                           /**< Default value for CPDMA_ADDRMSKEN1          */
#define _CPDMA_ADDRMSKEN1_MASK                   0x7FFFFFFFUL                           /**< Mask for CPDMA_ADDRMSKEN1                   */
#define _CPDMA_ADDRMSKEN1_MSKEN_SHIFT            0                                      /**< Shift value for CPDMA_MSKEN                 */
#define _CPDMA_ADDRMSKEN1_MSKEN_MASK             0x7FFFFFFFUL                           /**< Bit mask for CPDMA_MSKEN                    */
#define _CPDMA_ADDRMSKEN1_MSKEN_DEFAULT          0x00000000UL                           /**< Mode DEFAULT for CPDMA_ADDRMSKEN1           */
#define CPDMA_ADDRMSKEN1_MSKEN_DEFAULT           (_CPDMA_ADDRMSKEN1_MSKEN_DEFAULT << 0) /**< Shifted mode DEFAULT for CPDMA_ADDRMSKEN1   */

/* Bit fields for CPDMA ADDRMSKEN2 */
#define _CPDMA_ADDRMSKEN2_RESETVALUE             0x00000000UL                           /**< Default value for CPDMA_ADDRMSKEN2          */
#define _CPDMA_ADDRMSKEN2_MASK                   0x7FFFFFFFUL                           /**< Mask for CPDMA_ADDRMSKEN2                   */
#define _CPDMA_ADDRMSKEN2_MSKEN_SHIFT            0                                      /**< Shift value for CPDMA_MSKEN                 */
#define _CPDMA_ADDRMSKEN2_MSKEN_MASK             0x7FFFFFFFUL                           /**< Bit mask for CPDMA_MSKEN                    */
#define _CPDMA_ADDRMSKEN2_MSKEN_DEFAULT          0x00000000UL                           /**< Mode DEFAULT for CPDMA_ADDRMSKEN2           */
#define CPDMA_ADDRMSKEN2_MSKEN_DEFAULT           (_CPDMA_ADDRMSKEN2_MSKEN_DEFAULT << 0) /**< Shifted mode DEFAULT for CPDMA_ADDRMSKEN2   */

/* Bit fields for CPDMA ADDRMSKEN3 */
#define _CPDMA_ADDRMSKEN3_RESETVALUE             0x00000000UL                           /**< Default value for CPDMA_ADDRMSKEN3          */
#define _CPDMA_ADDRMSKEN3_MASK                   0x7FFFFFFFUL                           /**< Mask for CPDMA_ADDRMSKEN3                   */
#define _CPDMA_ADDRMSKEN3_MSKEN_SHIFT            0                                      /**< Shift value for CPDMA_MSKEN                 */
#define _CPDMA_ADDRMSKEN3_MSKEN_MASK             0x7FFFFFFFUL                           /**< Bit mask for CPDMA_MSKEN                    */
#define _CPDMA_ADDRMSKEN3_MSKEN_DEFAULT          0x00000000UL                           /**< Mode DEFAULT for CPDMA_ADDRMSKEN3           */
#define CPDMA_ADDRMSKEN3_MSKEN_DEFAULT           (_CPDMA_ADDRMSKEN3_MSKEN_DEFAULT << 0) /**< Shifted mode DEFAULT for CPDMA_ADDRMSKEN3   */

/* Bit fields for CPDMA ADDRMSKEN4 */
#define _CPDMA_ADDRMSKEN4_RESETVALUE             0x00000000UL                           /**< Default value for CPDMA_ADDRMSKEN4          */
#define _CPDMA_ADDRMSKEN4_MASK                   0x7FFFFFFFUL                           /**< Mask for CPDMA_ADDRMSKEN4                   */
#define _CPDMA_ADDRMSKEN4_MSKEN_SHIFT            0                                      /**< Shift value for CPDMA_MSKEN                 */
#define _CPDMA_ADDRMSKEN4_MSKEN_MASK             0x7FFFFFFFUL                           /**< Bit mask for CPDMA_MSKEN                    */
#define _CPDMA_ADDRMSKEN4_MSKEN_DEFAULT          0x00000000UL                           /**< Mode DEFAULT for CPDMA_ADDRMSKEN4           */
#define CPDMA_ADDRMSKEN4_MSKEN_DEFAULT           (_CPDMA_ADDRMSKEN4_MSKEN_DEFAULT << 0) /**< Shifted mode DEFAULT for CPDMA_ADDRMSKEN4   */

/* Bit fields for CPDMA ADDRMSK */
#define _CPDMA_ADDRMSK_RESETVALUE                0x00000000UL                           /**< Default value for CPDMA_ADDRMSK             */
#define _CPDMA_ADDRMSK_MASK                      0x1F1F1F1FUL                           /**< Mask for CPDMA_ADDRMSK                      */
#define _CPDMA_ADDRMSK_ADDMSK1_SHIFT             0                                      /**< Shift value for CPDMA_ADDMSK1               */
#define _CPDMA_ADDRMSK_ADDMSK1_MASK              0x1FUL                                 /**< Bit mask for CPDMA_ADDMSK1                  */
#define _CPDMA_ADDRMSK_ADDMSK1_DEFAULT           0x00000000UL                           /**< Mode DEFAULT for CPDMA_ADDRMSK              */
#define CPDMA_ADDRMSK_ADDMSK1_DEFAULT            (_CPDMA_ADDRMSK_ADDMSK1_DEFAULT << 0)  /**< Shifted mode DEFAULT for CPDMA_ADDRMSK      */
#define _CPDMA_ADDRMSK_ADDMSK2_SHIFT             8                                      /**< Shift value for CPDMA_ADDMSK2               */
#define _CPDMA_ADDRMSK_ADDMSK2_MASK              0x1F00UL                               /**< Bit mask for CPDMA_ADDMSK2                  */
#define _CPDMA_ADDRMSK_ADDMSK2_DEFAULT           0x00000000UL                           /**< Mode DEFAULT for CPDMA_ADDRMSK              */
#define CPDMA_ADDRMSK_ADDMSK2_DEFAULT            (_CPDMA_ADDRMSK_ADDMSK2_DEFAULT << 8)  /**< Shifted mode DEFAULT for CPDMA_ADDRMSK      */
#define _CPDMA_ADDRMSK_ADDMSK3_SHIFT             16                                     /**< Shift value for CPDMA_ADDMSK3               */
#define _CPDMA_ADDRMSK_ADDMSK3_MASK              0x1F0000UL                             /**< Bit mask for CPDMA_ADDMSK3                  */
#define _CPDMA_ADDRMSK_ADDMSK3_DEFAULT           0x00000000UL                           /**< Mode DEFAULT for CPDMA_ADDRMSK              */
#define CPDMA_ADDRMSK_ADDMSK3_DEFAULT            (_CPDMA_ADDRMSK_ADDMSK3_DEFAULT << 16) /**< Shifted mode DEFAULT for CPDMA_ADDRMSK      */
#define _CPDMA_ADDRMSK_ADDMSK4_SHIFT             24                                     /**< Shift value for CPDMA_ADDMSK4               */
#define _CPDMA_ADDRMSK_ADDMSK4_MASK              0x1F000000UL                           /**< Bit mask for CPDMA_ADDMSK4                  */
#define _CPDMA_ADDRMSK_ADDMSK4_DEFAULT           0x00000000UL                           /**< Mode DEFAULT for CPDMA_ADDRMSK              */
#define CPDMA_ADDRMSK_ADDMSK4_DEFAULT            (_CPDMA_ADDRMSK_ADDMSK4_DEFAULT << 24) /**< Shifted mode DEFAULT for CPDMA_ADDRMSK      */

/* Bit fields for CPDMA SYNCUPMSK1 */
#define _CPDMA_SYNCUPMSK1_RESETVALUE             0x00000000UL                                /**< Default value for CPDMA_SYNCUPMSK1          */
#define _CPDMA_SYNCUPMSK1_MASK                   0x7FFFFFFFUL                                /**< Mask for CPDMA_SYNCUPMSK1                   */
#define _CPDMA_SYNCUPMSK1_SYNCUPMSK1_SHIFT       0                                           /**< Shift value for CPDMA_SYNCUPMSK1            */
#define _CPDMA_SYNCUPMSK1_SYNCUPMSK1_MASK        0x7FFFFFFFUL                                /**< Bit mask for CPDMA_SYNCUPMSK1               */
#define _CPDMA_SYNCUPMSK1_SYNCUPMSK1_DEFAULT     0x00000000UL                                /**< Mode DEFAULT for CPDMA_SYNCUPMSK1           */
#define CPDMA_SYNCUPMSK1_SYNCUPMSK1_DEFAULT      (_CPDMA_SYNCUPMSK1_SYNCUPMSK1_DEFAULT << 0) /**< Shifted mode DEFAULT for CPDMA_SYNCUPMSK1   */

/* Bit fields for CPDMA SYNCUPMSK2 */
#define _CPDMA_SYNCUPMSK2_RESETVALUE             0x00000000UL                                /**< Default value for CPDMA_SYNCUPMSK2          */
#define _CPDMA_SYNCUPMSK2_MASK                   0x7FFFFFFFUL                                /**< Mask for CPDMA_SYNCUPMSK2                   */
#define _CPDMA_SYNCUPMSK2_SYNCUPMSK2_SHIFT       0                                           /**< Shift value for CPDMA_SYNCUPMSK2            */
#define _CPDMA_SYNCUPMSK2_SYNCUPMSK2_MASK        0x7FFFFFFFUL                                /**< Bit mask for CPDMA_SYNCUPMSK2               */
#define _CPDMA_SYNCUPMSK2_SYNCUPMSK2_DEFAULT     0x00000000UL                                /**< Mode DEFAULT for CPDMA_SYNCUPMSK2           */
#define CPDMA_SYNCUPMSK2_SYNCUPMSK2_DEFAULT      (_CPDMA_SYNCUPMSK2_SYNCUPMSK2_DEFAULT << 0) /**< Shifted mode DEFAULT for CPDMA_SYNCUPMSK2   */

/* Bit fields for CPDMA SYNCENAB1 */
#define _CPDMA_SYNCENAB1_RESETVALUE              0x00000000UL                              /**< Default value for CPDMA_SYNCENAB1           */
#define _CPDMA_SYNCENAB1_MASK                    0x7FFFFFFFUL                              /**< Mask for CPDMA_SYNCENAB1                    */
#define _CPDMA_SYNCENAB1_SYNCENAB1_SHIFT         0                                         /**< Shift value for CPDMA_SYNCENAB1             */
#define _CPDMA_SYNCENAB1_SYNCENAB1_MASK          0x7FFFFFFFUL                              /**< Bit mask for CPDMA_SYNCENAB1                */
#define _CPDMA_SYNCENAB1_SYNCENAB1_DEFAULT       0x00000000UL                              /**< Mode DEFAULT for CPDMA_SYNCENAB1            */
#define CPDMA_SYNCENAB1_SYNCENAB1_DEFAULT        (_CPDMA_SYNCENAB1_SYNCENAB1_DEFAULT << 0) /**< Shifted mode DEFAULT for CPDMA_SYNCENAB1    */

/* Bit fields for CPDMA SYNCENAB2 */
#define _CPDMA_SYNCENAB2_RESETVALUE              0x00000000UL                              /**< Default value for CPDMA_SYNCENAB2           */
#define _CPDMA_SYNCENAB2_MASK                    0x7FFFFFFFUL                              /**< Mask for CPDMA_SYNCENAB2                    */
#define _CPDMA_SYNCENAB2_SYNCENAB2_SHIFT         0                                         /**< Shift value for CPDMA_SYNCENAB2             */
#define _CPDMA_SYNCENAB2_SYNCENAB2_MASK          0x7FFFFFFFUL                              /**< Bit mask for CPDMA_SYNCENAB2                */
#define _CPDMA_SYNCENAB2_SYNCENAB2_DEFAULT       0x00000000UL                              /**< Mode DEFAULT for CPDMA_SYNCENAB2            */
#define CPDMA_SYNCENAB2_SYNCENAB2_DEFAULT        (_CPDMA_SYNCENAB2_SYNCENAB2_DEFAULT << 0) /**< Shifted mode DEFAULT for CPDMA_SYNCENAB2    */

/* Bit fields for CPDMA SYNCINPTHRES */
#define _CPDMA_SYNCINPTHRES_RESETVALUE           0x00000101UL                                 /**< Default value for CPDMA_SYNCINPTHRES        */
#define _CPDMA_SYNCINPTHRES_MASK                 0x0000FFFFUL                                 /**< Mask for CPDMA_SYNCINPTHRES                 */
#define _CPDMA_SYNCINPTHRES_INPTHRES1_SHIFT      0                                            /**< Shift value for CPDMA_INPTHRES1             */
#define _CPDMA_SYNCINPTHRES_INPTHRES1_MASK       0xFFUL                                       /**< Bit mask for CPDMA_INPTHRES1                */
#define _CPDMA_SYNCINPTHRES_INPTHRES1_DEFAULT    0x00000001UL                                 /**< Mode DEFAULT for CPDMA_SYNCINPTHRES         */
#define CPDMA_SYNCINPTHRES_INPTHRES1_DEFAULT     (_CPDMA_SYNCINPTHRES_INPTHRES1_DEFAULT << 0) /**< Shifted mode DEFAULT for CPDMA_SYNCINPTHRES */
#define _CPDMA_SYNCINPTHRES_INPTHRES2_SHIFT      8                                            /**< Shift value for CPDMA_INPTHRES2             */
#define _CPDMA_SYNCINPTHRES_INPTHRES2_MASK       0xFF00UL                                     /**< Bit mask for CPDMA_INPTHRES2                */
#define _CPDMA_SYNCINPTHRES_INPTHRES2_DEFAULT    0x00000001UL                                 /**< Mode DEFAULT for CPDMA_SYNCINPTHRES         */
#define CPDMA_SYNCINPTHRES_INPTHRES2_DEFAULT     (_CPDMA_SYNCINPTHRES_INPTHRES2_DEFAULT << 8) /**< Shifted mode DEFAULT for CPDMA_SYNCINPTHRES */

/* Bit fields for CPDMA SYNCOUTTHRES */
#define _CPDMA_SYNCOUTTHRES_RESETVALUE           0x00000101UL                                 /**< Default value for CPDMA_SYNCOUTTHRES        */
#define _CPDMA_SYNCOUTTHRES_MASK                 0x0000FFFFUL                                 /**< Mask for CPDMA_SYNCOUTTHRES                 */
#define _CPDMA_SYNCOUTTHRES_OUTTHRES1_SHIFT      0                                            /**< Shift value for CPDMA_OUTTHRES1             */
#define _CPDMA_SYNCOUTTHRES_OUTTHRES1_MASK       0xFFUL                                       /**< Bit mask for CPDMA_OUTTHRES1                */
#define _CPDMA_SYNCOUTTHRES_OUTTHRES1_DEFAULT    0x00000001UL                                 /**< Mode DEFAULT for CPDMA_SYNCOUTTHRES         */
#define CPDMA_SYNCOUTTHRES_OUTTHRES1_DEFAULT     (_CPDMA_SYNCOUTTHRES_OUTTHRES1_DEFAULT << 0) /**< Shifted mode DEFAULT for CPDMA_SYNCOUTTHRES */
#define _CPDMA_SYNCOUTTHRES_OUTTHRES2_SHIFT      8                                            /**< Shift value for CPDMA_OUTTHRES2             */
#define _CPDMA_SYNCOUTTHRES_OUTTHRES2_MASK       0xFF00UL                                     /**< Bit mask for CPDMA_OUTTHRES2                */
#define _CPDMA_SYNCOUTTHRES_OUTTHRES2_DEFAULT    0x00000001UL                                 /**< Mode DEFAULT for CPDMA_SYNCOUTTHRES         */
#define CPDMA_SYNCOUTTHRES_OUTTHRES2_DEFAULT     (_CPDMA_SYNCOUTTHRES_OUTTHRES2_DEFAULT << 8) /**< Shifted mode DEFAULT for CPDMA_SYNCOUTTHRES */

/* Bit fields for CPDMA SYNCCNTSTAT */
#define _CPDMA_SYNCCNTSTAT_RESETVALUE            0x00000000UL                               /**< Default value for CPDMA_SYNCCNTSTAT         */
#define _CPDMA_SYNCCNTSTAT_MASK                  0x0000FFFFUL                               /**< Mask for CPDMA_SYNCCNTSTAT                  */
#define _CPDMA_SYNCCNTSTAT_CNTSTAT1_SHIFT        0                                          /**< Shift value for CPDMA_CNTSTAT1              */
#define _CPDMA_SYNCCNTSTAT_CNTSTAT1_MASK         0xFFUL                                     /**< Bit mask for CPDMA_CNTSTAT1                 */
#define _CPDMA_SYNCCNTSTAT_CNTSTAT1_DEFAULT      0x00000000UL                               /**< Mode DEFAULT for CPDMA_SYNCCNTSTAT          */
#define CPDMA_SYNCCNTSTAT_CNTSTAT1_DEFAULT       (_CPDMA_SYNCCNTSTAT_CNTSTAT1_DEFAULT << 0) /**< Shifted mode DEFAULT for CPDMA_SYNCCNTSTAT  */
#define _CPDMA_SYNCCNTSTAT_CNTSTAT2_SHIFT        8                                          /**< Shift value for CPDMA_CNTSTAT2              */
#define _CPDMA_SYNCCNTSTAT_CNTSTAT2_MASK         0xFF00UL                                   /**< Bit mask for CPDMA_CNTSTAT2                 */
#define _CPDMA_SYNCCNTSTAT_CNTSTAT2_DEFAULT      0x00000000UL                               /**< Mode DEFAULT for CPDMA_SYNCCNTSTAT          */
#define CPDMA_SYNCCNTSTAT_CNTSTAT2_DEFAULT       (_CPDMA_SYNCCNTSTAT_CNTSTAT2_DEFAULT << 8) /**< Shifted mode DEFAULT for CPDMA_SYNCCNTSTAT  */

/* Bit fields for CPDMA FIFO_CONN */
#define _CPDMA_FIFO_CONN_RESETVALUE              0x00000000UL                           /**< Default value for CPDMA_FIFO_CONN           */
#define _CPDMA_FIFO_CONN_MASK                    0x00003F0FUL                           /**< Mask for CPDMA_FIFO_CONN                    */
#define _CPDMA_FIFO_CONN_FIFOID_SHIFT            0                                      /**< Shift value for CPDMA_FIFOID                */
#define _CPDMA_FIFO_CONN_FIFOID_MASK             0xFUL                                  /**< Bit mask for CPDMA_FIFOID                   */
#define _CPDMA_FIFO_CONN_FIFOID_DEFAULT          0x00000000UL                           /**< Mode DEFAULT for CPDMA_FIFO_CONN            */
#define CPDMA_FIFO_CONN_FIFOID_DEFAULT           (_CPDMA_FIFO_CONN_FIFOID_DEFAULT << 0) /**< Shifted mode DEFAULT for CPDMA_FIFO_CONN    */
#define _CPDMA_FIFO_CONN_CPID_SHIFT              8                                      /**< Shift value for CPDMA_CPID                  */
#define _CPDMA_FIFO_CONN_CPID_MASK               0x3F00UL                               /**< Bit mask for CPDMA_CPID                     */
#define _CPDMA_FIFO_CONN_CPID_DEFAULT            0x00000000UL                           /**< Mode DEFAULT for CPDMA_FIFO_CONN            */
#define CPDMA_FIFO_CONN_CPID_DEFAULT             (_CPDMA_FIFO_CONN_CPID_DEFAULT << 8)   /**< Shifted mode DEFAULT for CPDMA_FIFO_CONN    */

/* Bit fields for CPDMA CH_CFG */
#define _CPDMA_CH_CFG_RESETVALUE                 0x01000000UL                             /**< Default value for CPDMA_CH_CFG              */
#define _CPDMA_CH_CFG_MASK                       0x1FECF300UL                             /**< Mask for CPDMA_CH_CFG                       */
#define _CPDMA_CH_CFG_ILEAVESEL_SHIFT            8                                        /**< Shift value for CPDMA_ILEAVESEL             */
#define _CPDMA_CH_CFG_ILEAVESEL_MASK             0x300UL                                  /**< Bit mask for CPDMA_ILEAVESEL                */
#define _CPDMA_CH_CFG_ILEAVESEL_DEFAULT          0x00000000UL                             /**< Mode DEFAULT for CPDMA_CH_CFG               */
#define CPDMA_CH_CFG_ILEAVESEL_DEFAULT           (_CPDMA_CH_CFG_ILEAVESEL_DEFAULT << 8)   /**< Shifted mode DEFAULT for CPDMA_CH_CFG       */
#define _CPDMA_CH_CFG_ILEAVEMODE_SHIFT           12                                       /**< Shift value for CPDMA_ILEAVEMODE            */
#define _CPDMA_CH_CFG_ILEAVEMODE_MASK            0x3000UL                                 /**< Bit mask for CPDMA_ILEAVEMODE               */
#define _CPDMA_CH_CFG_ILEAVEMODE_DEFAULT         0x00000000UL                             /**< Mode DEFAULT for CPDMA_CH_CFG               */
#define _CPDMA_CH_CFG_ILEAVEMODE_NONE            0x00000000UL                             /**< Mode NONE for CPDMA_CH_CFG                  */
#define _CPDMA_CH_CFG_ILEAVEMODE_SOURCE          0x00000001UL                             /**< Mode SOURCE for CPDMA_CH_CFG                */
#define _CPDMA_CH_CFG_ILEAVEMODE_SINK            0x00000002UL                             /**< Mode SINK for CPDMA_CH_CFG                  */
#define CPDMA_CH_CFG_ILEAVEMODE_DEFAULT          (_CPDMA_CH_CFG_ILEAVEMODE_DEFAULT << 12) /**< Shifted mode DEFAULT for CPDMA_CH_CFG       */
#define CPDMA_CH_CFG_ILEAVEMODE_NONE             (_CPDMA_CH_CFG_ILEAVEMODE_NONE << 12)    /**< Shifted mode NONE for CPDMA_CH_CFG          */
#define CPDMA_CH_CFG_ILEAVEMODE_SOURCE           (_CPDMA_CH_CFG_ILEAVEMODE_SOURCE << 12)  /**< Shifted mode SOURCE for CPDMA_CH_CFG        */
#define CPDMA_CH_CFG_ILEAVEMODE_SINK             (_CPDMA_CH_CFG_ILEAVEMODE_SINK << 12)    /**< Shifted mode SINK for CPDMA_CH_CFG          */
#define CPDMA_CH_CFG_ILEAVEABS                   (0x1UL << 14)                            /**< Interleave Absolute Address                 */
#define _CPDMA_CH_CFG_ILEAVEABS_SHIFT            14                                       /**< Shift value for CPDMA_ILEAVEABS             */
#define _CPDMA_CH_CFG_ILEAVEABS_MASK             0x4000UL                                 /**< Bit mask for CPDMA_ILEAVEABS                */
#define _CPDMA_CH_CFG_ILEAVEABS_DEFAULT          0x00000000UL                             /**< Mode DEFAULT for CPDMA_CH_CFG               */
#define CPDMA_CH_CFG_ILEAVEABS_DEFAULT           (_CPDMA_CH_CFG_ILEAVEABS_DEFAULT << 14)  /**< Shifted mode DEFAULT for CPDMA_CH_CFG       */
#define CPDMA_CH_CFG_FORCEREQ                    (0x1UL << 15)                            /**< Forced Request Mode                         */
#define _CPDMA_CH_CFG_FORCEREQ_SHIFT             15                                       /**< Shift value for CPDMA_FORCEREQ              */
#define _CPDMA_CH_CFG_FORCEREQ_MASK              0x8000UL                                 /**< Bit mask for CPDMA_FORCEREQ                 */
#define _CPDMA_CH_CFG_FORCEREQ_DEFAULT           0x00000000UL                             /**< Mode DEFAULT for CPDMA_CH_CFG               */
#define _CPDMA_CH_CFG_FORCEREQ_DISABLED          0x00000000UL                             /**< Mode DISABLED for CPDMA_CH_CFG              */
#define _CPDMA_CH_CFG_FORCEREQ_ENABLED           0x00000001UL                             /**< Mode ENABLED for CPDMA_CH_CFG               */
#define CPDMA_CH_CFG_FORCEREQ_DEFAULT            (_CPDMA_CH_CFG_FORCEREQ_DEFAULT << 15)   /**< Shifted mode DEFAULT for CPDMA_CH_CFG       */
#define CPDMA_CH_CFG_FORCEREQ_DISABLED           (_CPDMA_CH_CFG_FORCEREQ_DISABLED << 15)  /**< Shifted mode DISABLED for CPDMA_CH_CFG      */
#define CPDMA_CH_CFG_FORCEREQ_ENABLED            (_CPDMA_CH_CFG_FORCEREQ_ENABLED << 15)   /**< Shifted mode ENABLED for CPDMA_CH_CFG       */
#define _CPDMA_CH_CFG_ARBDEL_SHIFT               18                                       /**< Shift value for CPDMA_ARBDEL                */
#define _CPDMA_CH_CFG_ARBDEL_MASK                0xC0000UL                                /**< Bit mask for CPDMA_ARBDEL                   */
#define _CPDMA_CH_CFG_ARBDEL_DEFAULT             0x00000000UL                             /**< Mode DEFAULT for CPDMA_CH_CFG               */
#define CPDMA_CH_CFG_ARBDEL_DEFAULT              (_CPDMA_CH_CFG_ARBDEL_DEFAULT << 18)     /**< Shifted mode DEFAULT for CPDMA_CH_CFG       */
#define CPDMA_CH_CFG_ADDRELDIS                   (0x1UL << 21)                            /**< Address Reload Disable                      */
#define _CPDMA_CH_CFG_ADDRELDIS_SHIFT            21                                       /**< Shift value for CPDMA_ADDRELDIS             */
#define _CPDMA_CH_CFG_ADDRELDIS_MASK             0x200000UL                               /**< Bit mask for CPDMA_ADDRELDIS                */
#define _CPDMA_CH_CFG_ADDRELDIS_DEFAULT          0x00000000UL                             /**< Mode DEFAULT for CPDMA_CH_CFG               */
#define CPDMA_CH_CFG_ADDRELDIS_DEFAULT           (_CPDMA_CH_CFG_ADDRELDIS_DEFAULT << 21)  /**< Shifted mode DEFAULT for CPDMA_CH_CFG       */
#define _CPDMA_CH_CFG_AUTODIS_SHIFT              22                                       /**< Shift value for CPDMA_AUTODIS               */
#define _CPDMA_CH_CFG_AUTODIS_MASK               0xC00000UL                               /**< Bit mask for CPDMA_AUTODIS                  */
#define _CPDMA_CH_CFG_AUTODIS_DEFAULT            0x00000000UL                             /**< Mode DEFAULT for CPDMA_CH_CFG               */
#define _CPDMA_CH_CFG_AUTODIS_NONE               0x00000000UL                             /**< Mode NONE for CPDMA_CH_CFG                  */
#define _CPDMA_CH_CFG_AUTODIS_SINGLE             0x00000001UL                             /**< Mode SINGLE for CPDMA_CH_CFG                */
#define _CPDMA_CH_CFG_AUTODIS_CYCLE              0x00000002UL                             /**< Mode CYCLE for CPDMA_CH_CFG                 */
#define _CPDMA_CH_CFG_AUTODIS_BOTH               0x00000003UL                             /**< Mode BOTH for CPDMA_CH_CFG                  */
#define CPDMA_CH_CFG_AUTODIS_DEFAULT             (_CPDMA_CH_CFG_AUTODIS_DEFAULT << 22)    /**< Shifted mode DEFAULT for CPDMA_CH_CFG       */
#define CPDMA_CH_CFG_AUTODIS_NONE                (_CPDMA_CH_CFG_AUTODIS_NONE << 22)       /**< Shifted mode NONE for CPDMA_CH_CFG          */
#define CPDMA_CH_CFG_AUTODIS_SINGLE              (_CPDMA_CH_CFG_AUTODIS_SINGLE << 22)     /**< Shifted mode SINGLE for CPDMA_CH_CFG        */
#define CPDMA_CH_CFG_AUTODIS_CYCLE               (_CPDMA_CH_CFG_AUTODIS_CYCLE << 22)      /**< Shifted mode CYCLE for CPDMA_CH_CFG         */
#define CPDMA_CH_CFG_AUTODIS_BOTH                (_CPDMA_CH_CFG_AUTODIS_BOTH << 22)       /**< Shifted mode BOTH for CPDMA_CH_CFG          */
#define _CPDMA_CH_CFG_ADDRINC_SHIFT              24                                       /**< Shift value for CPDMA_ADDRINC               */
#define _CPDMA_CH_CFG_ADDRINC_MASK               0x1F000000UL                             /**< Bit mask for CPDMA_ADDRINC                  */
#define _CPDMA_CH_CFG_ADDRINC_DEFAULT            0x00000001UL                             /**< Mode DEFAULT for CPDMA_CH_CFG               */
#define CPDMA_CH_CFG_ADDRINC_DEFAULT             (_CPDMA_CH_CFG_ADDRINC_DEFAULT << 24)    /**< Shifted mode DEFAULT for CPDMA_CH_CFG       */

/* Bit fields for CPDMA CH_CTRL */
#define _CPDMA_CH_CTRL_RESETVALUE                0x22000000UL                           /**< Default value for CPDMA_CH_CTRL             */
#define _CPDMA_CH_CTRL_MASK                      0x3300FFFFUL                           /**< Mask for CPDMA_CH_CTRL                      */
#define _CPDMA_CH_CTRL_XFERCNT_SHIFT             0                                      /**< Shift value for CPDMA_XFERCNT               */
#define _CPDMA_CH_CTRL_XFERCNT_MASK              0xFFFFUL                               /**< Bit mask for CPDMA_XFERCNT                  */
#define _CPDMA_CH_CTRL_XFERCNT_DEFAULT           0x00000000UL                           /**< Mode DEFAULT for CPDMA_CH_CTRL              */
#define CPDMA_CH_CTRL_XFERCNT_DEFAULT            (_CPDMA_CH_CTRL_XFERCNT_DEFAULT << 0)  /**< Shifted mode DEFAULT for CPDMA_CH_CTRL      */
#define _CPDMA_CH_CTRL_SIZE_SHIFT                24                                     /**< Shift value for CPDMA_SIZE                  */
#define _CPDMA_CH_CTRL_SIZE_MASK                 0x3000000UL                            /**< Bit mask for CPDMA_SIZE                     */
#define _CPDMA_CH_CTRL_SIZE_DEFAULT              0x00000002UL                           /**< Mode DEFAULT for CPDMA_CH_CTRL              */
#define _CPDMA_CH_CTRL_SIZE_BYTE                 0x00000000UL                           /**< Mode BYTE for CPDMA_CH_CTRL                 */
#define _CPDMA_CH_CTRL_SIZE_HALFWORD             0x00000001UL                           /**< Mode HALFWORD for CPDMA_CH_CTRL             */
#define _CPDMA_CH_CTRL_SIZE_WORD                 0x00000002UL                           /**< Mode WORD for CPDMA_CH_CTRL                 */
#define CPDMA_CH_CTRL_SIZE_DEFAULT               (_CPDMA_CH_CTRL_SIZE_DEFAULT << 24)    /**< Shifted mode DEFAULT for CPDMA_CH_CTRL      */
#define CPDMA_CH_CTRL_SIZE_BYTE                  (_CPDMA_CH_CTRL_SIZE_BYTE << 24)       /**< Shifted mode BYTE for CPDMA_CH_CTRL         */
#define CPDMA_CH_CTRL_SIZE_HALFWORD              (_CPDMA_CH_CTRL_SIZE_HALFWORD << 24)   /**< Shifted mode HALFWORD for CPDMA_CH_CTRL     */
#define CPDMA_CH_CTRL_SIZE_WORD                  (_CPDMA_CH_CTRL_SIZE_WORD << 24)       /**< Shifted mode WORD for CPDMA_CH_CTRL         */
#define CPDMA_CH_CTRL_DONEIEN                    (0x1UL << 28)                          /**< CPDMA Operation Done Interrupt Enab         */
#define _CPDMA_CH_CTRL_DONEIEN_SHIFT             28                                     /**< Shift value for CPDMA_DONEIEN               */
#define _CPDMA_CH_CTRL_DONEIEN_MASK              0x10000000UL                           /**< Bit mask for CPDMA_DONEIEN                  */
#define _CPDMA_CH_CTRL_DONEIEN_DEFAULT           0x00000000UL                           /**< Mode DEFAULT for CPDMA_CH_CTRL              */
#define CPDMA_CH_CTRL_DONEIEN_DEFAULT            (_CPDMA_CH_CTRL_DONEIEN_DEFAULT << 28) /**< Shifted mode DEFAULT for CPDMA_CH_CTRL      */
#define CPDMA_CH_CTRL_REQMODE                    (0x1UL << 29)                          /**< CPDMA Request Transfer Mode Select          */
#define _CPDMA_CH_CTRL_REQMODE_SHIFT             29                                     /**< Shift value for CPDMA_REQMODE               */
#define _CPDMA_CH_CTRL_REQMODE_MASK              0x20000000UL                           /**< Bit mask for CPDMA_REQMODE                  */
#define _CPDMA_CH_CTRL_REQMODE_DEFAULT           0x00000001UL                           /**< Mode DEFAULT for CPDMA_CH_CTRL              */
#define _CPDMA_CH_CTRL_REQMODE_SINGLE            0x00000000UL                           /**< Mode SINGLE for CPDMA_CH_CTRL               */
#define _CPDMA_CH_CTRL_REQMODE_CYCLE             0x00000001UL                           /**< Mode CYCLE for CPDMA_CH_CTRL                */
#define CPDMA_CH_CTRL_REQMODE_DEFAULT            (_CPDMA_CH_CTRL_REQMODE_DEFAULT << 29) /**< Shifted mode DEFAULT for CPDMA_CH_CTRL      */
#define CPDMA_CH_CTRL_REQMODE_SINGLE             (_CPDMA_CH_CTRL_REQMODE_SINGLE << 29)  /**< Shifted mode SINGLE for CPDMA_CH_CTRL       */
#define CPDMA_CH_CTRL_REQMODE_CYCLE              (_CPDMA_CH_CTRL_REQMODE_CYCLE << 29)   /**< Shifted mode CYCLE for CPDMA_CH_CTRL        */

/* Bit fields for CPDMA CH_STARTADDR */
#define _CPDMA_CH_STARTADDR_RESETVALUE           0x00000000UL                                 /**< Default value for CPDMA_CH_STARTADDR        */
#define _CPDMA_CH_STARTADDR_MASK                 0xFFFFFFFFUL                                 /**< Mask for CPDMA_CH_STARTADDR                 */
#define _CPDMA_CH_STARTADDR_STARTADDR_SHIFT      0                                            /**< Shift value for CPDMA_STARTADDR             */
#define _CPDMA_CH_STARTADDR_STARTADDR_MASK       0xFFFFFFFFUL                                 /**< Bit mask for CPDMA_STARTADDR                */
#define _CPDMA_CH_STARTADDR_STARTADDR_DEFAULT    0x00000000UL                                 /**< Mode DEFAULT for CPDMA_CH_STARTADDR         */
#define CPDMA_CH_STARTADDR_STARTADDR_DEFAULT     (_CPDMA_CH_STARTADDR_STARTADDR_DEFAULT << 0) /**< Shifted mode DEFAULT for CPDMA_CH_STARTADDR */

/* Bit fields for CPDMA CH_STAT */
#define _CPDMA_CH_STAT_RESETVALUE                0x00000000UL                           /**< Default value for CPDMA_CH_STAT             */
#define _CPDMA_CH_STAT_MASK                      0x0000FFFFUL                           /**< Mask for CPDMA_CH_STAT                      */
#define _CPDMA_CH_STAT_XFERREM_SHIFT             0                                      /**< Shift value for CPDMA_XFERREM               */
#define _CPDMA_CH_STAT_XFERREM_MASK              0xFFFFUL                               /**< Bit mask for CPDMA_XFERREM                  */
#define _CPDMA_CH_STAT_XFERREM_DEFAULT           0x00000000UL                           /**< Mode DEFAULT for CPDMA_CH_STAT              */
#define CPDMA_CH_STAT_XFERREM_DEFAULT            (_CPDMA_CH_STAT_XFERREM_DEFAULT << 0)  /**< Shifted mode DEFAULT for CPDMA_CH_STAT      */

/* Bit fields for CPDMA CH_CURRADDR */
#define _CPDMA_CH_CURRADDR_RESETVALUE            0x00000000UL                               /**< Default value for CPDMA_CH_CURRADDR         */
#define _CPDMA_CH_CURRADDR_MASK                  0xFFFFFFFFUL                               /**< Mask for CPDMA_CH_CURRADDR                  */
#define _CPDMA_CH_CURRADDR_CURRADDR_SHIFT        0                                          /**< Shift value for CPDMA_CURRADDR              */
#define _CPDMA_CH_CURRADDR_CURRADDR_MASK         0xFFFFFFFFUL                               /**< Bit mask for CPDMA_CURRADDR                 */
#define _CPDMA_CH_CURRADDR_CURRADDR_DEFAULT      0x00000000UL                               /**< Mode DEFAULT for CPDMA_CH_CURRADDR          */
#define CPDMA_CH_CURRADDR_CURRADDR_DEFAULT       (_CPDMA_CH_CURRADDR_CURRADDR_DEFAULT << 0) /**< Shifted mode DEFAULT for CPDMA_CH_CURRADDR  */

/** @} End of group EFR32FG25_CPDMA_BitFields */
/** @} End of group EFR32FG25_CPDMA */
/** @} End of group Parts */

#endif /* EFR32FG25_CPDMA_H */
