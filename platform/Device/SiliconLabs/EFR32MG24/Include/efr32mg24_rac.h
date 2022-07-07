/**************************************************************************//**
 * @file
 * @brief EFR32MG24 RAC register and bit field definitions
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
#ifndef EFR32MG24_RAC_H
#define EFR32MG24_RAC_H
#define RAC_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32MG24_RAC RAC
 * @{
 * @brief EFR32MG24 RAC Register Declaration.
 *****************************************************************************/

/** RAC Register Declaration. */
typedef struct {
  __IM uint32_t  IPVERSION;                     /**< IP Version                                         */
  __IOM uint32_t EN;                            /**< Enable peripheral clock to this module             */
  __IOM uint32_t RXENSRCEN;                     /**< RXEN Source Enable                                 */
  __IM uint32_t  STATUS;                        /**< Radio State Machine Status                         */
  __IOM uint32_t CMD;                           /**< Radio Commands                                     */
  __IOM uint32_t CTRL;                          /**< Radio Control Register                             */
  __IOM uint32_t FORCESTATE;                    /**< Force state transition                             */
  __IOM uint32_t IF;                            /**< Radio Controller Interrupt Flags                   */
  __IOM uint32_t IEN;                           /**< Interrupt Enable Register                          */
  __IOM uint32_t TESTCTRL;                      /**< Test Control Register                              */
  __IOM uint32_t SEQIF;                         /**< SEQ Interrupt Flags                                */
  __IOM uint32_t SEQIEN;                        /**< SEQ Interrupt Enable Register                      */
  __IM uint32_t  STATUS1;                       /**< Radio State Machine Status                         */
  __IM uint32_t  STIMER;                        /**< Sequencer Timer Value                              */
  __IOM uint32_t STIMERCOMP;                    /**< Sequencer Timer Compare Value                      */
  __IOM uint32_t SEQCTRL;                       /**< Sequencer Control Register                         */
  __IOM uint32_t PRESC;                         /**< Sequencer prescaler Register                       */
  __IOM uint32_t SR0;                           /**< Storage Register 0                                 */
  __IOM uint32_t SR1;                           /**< Storage Register 1                                 */
  __IOM uint32_t SR2;                           /**< Storage Register 2                                 */
  __IOM uint32_t SR3;                           /**< Storage Register 3                                 */
  __IOM uint32_t STCTRL;                        /**< Sys tick timer Control Register                    */
  __IOM uint32_t FRCTXWORD;                     /**< FRC wordbuffer write                               */
  __IM uint32_t  FRCRXWORD;                     /**< FRC wordbuffer read                                */
  __IOM uint32_t EM1PCSR;                       /**< Radio EM1P Control and Status Register             */
  uint32_t       RESERVED0[13U];                /**< Reserved for future use                            */
  __IOM uint32_t SYNTHENCTRL;                   /**< Synthesizer Enable Control Register                */
  __IOM uint32_t SYNTHREGCTRL;                  /**< Synthesizer Regulator Enable Control               */
  __IOM uint32_t VCOCTRL;                       /**< VCO Control Register                               */
  uint32_t       RESERVED1[2U];                 /**< Reserved for future use                            */
  uint32_t       RESERVED2[1U];                 /**< Reserved for future use                            */
  __IM uint32_t  STATUS2;                       /**< Radio State Machine Status 2                       */
  __IOM uint32_t IFPGACTRL;                     /**< IF PGA Control Register                            */
  __IOM uint32_t PAENCTRL;                      /**< PA Enable Control Register                         */
  __IOM uint32_t APC;                           /**< Automatic Power Control Register                   */
  __IOM uint32_t ANTDIV;                        /**< ANTDIV                                             */
  __IOM uint32_t AUXADCTRIM;                    /**< AUXADCTRIM                                         */
  __IOM uint32_t AUXADCEN;                      /**< AUXADCEN                                           */
  __IOM uint32_t AUXADCCTRL0;                   /**< Auxiliary ADC register control                     */
  __IOM uint32_t AUXADCCTRL1;                   /**< AUXADCCTRL1                                        */
  __IM uint32_t  AUXADCOUT;                     /**< Auxiliary ADC digital output                       */
  __IOM uint32_t CLKMULTEN0;                    /**< CLKMULTEN0                                         */
  __IOM uint32_t CLKMULTEN1;                    /**< CLKMULTEN1                                         */
  __IOM uint32_t CLKMULTCTRL;                   /**< CLKMULTCTRL                                        */
  __IM uint32_t  CLKMULTSTATUS;                 /**< CLKMULTSTATUS                                      */
  uint32_t       RESERVED3[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t IFADCTRIM0;                    /**< IFADCTRIM0                                         */
  __IOM uint32_t IFADCTRIM1;                    /**< IFADCTRIM1                                         */
  __IOM uint32_t IFADCCAL;                      /**< IFADCCAL                                           */
  __IM uint32_t  IFADCSTATUS;                   /**< IFADCSTATUS                                        */
  uint32_t       RESERVED4[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t LNAMIXTRIM0;                   /**< LNAMIXTRIM0                                        */
  __IOM uint32_t LNAMIXTRIM1;                   /**< LNAMIXTRIM1                                        */
  __IOM uint32_t LNAMIXTRIM2;                   /**< LNAMIXTRIM2                                        */
  __IOM uint32_t LNAMIXTRIM3;                   /**< LNAMIXTRIM3                                        */
  __IOM uint32_t LNAMIXTRIM4;                   /**< LNAMIXTRIM4                                        */
  __IOM uint32_t LNAMIXCAL;                     /**< LNAMIXCAL                                          */
  __IOM uint32_t LNAMIXEN;                      /**< LNAMIXEN                                           */
  __IOM uint32_t PRECTRL;                       /**< PRECTRL                                            */
  __IOM uint32_t PATRIM0;                       /**< PATRIM0                                            */
  __IOM uint32_t PATRIM1;                       /**< PATRIM1                                            */
  __IOM uint32_t PATRIM2;                       /**< PATRIM2                                            */
  __IOM uint32_t PATRIM3;                       /**< PATRIM3                                            */
  __IOM uint32_t PATRIM4;                       /**< PATRIM4                                            */
  __IOM uint32_t PATRIM5;                       /**< PATRIM5                                            */
  uint32_t       RESERVED5[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t TXPOWER;                       /**< TXPOWER                                            */
  __IOM uint32_t TXRAMP;                        /**< TXRAMP                                             */
  uint32_t       RESERVED6[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t PGATRIM;                       /**< PGATRIM                                            */
  __IOM uint32_t PGACAL;                        /**< PGACAL                                             */
  __IOM uint32_t PGACTRL;                       /**< PGACTRL                                            */
  __IOM uint32_t RFBIASCAL;                     /**< RFBIASCAL                                          */
  __IOM uint32_t RFBIASCTRL;                    /**< RFBIASCTRL                                         */
  __IOM uint32_t RADIOEN;                       /**< RADIOEN                                            */
  __IOM uint32_t RFPATHEN0;                     /**< RFPATHEN0                                          */
  __IOM uint32_t RFPATHEN1;                     /**< RFPATHEN1                                          */
  __IOM uint32_t RX;                            /**< RX                                                 */
  __IOM uint32_t TX;                            /**< TX                                                 */
  uint32_t       RESERVED7[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t SYTRIM0;                       /**< SYTRIM0                                            */
  __IOM uint32_t SYTRIM1;                       /**< SYTRIM1                                            */
  __IOM uint32_t SYCAL;                         /**< SYCAL                                              */
  __IOM uint32_t SYEN;                          /**< SYEN                                               */
  __IOM uint32_t SYLOEN;                        /**< SYLOEN                                             */
  __IOM uint32_t SYMMDCTRL;                     /**< SYMMDCTRL                                          */
  uint32_t       RESERVED8[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t DIGCLKRETIMECTRL;              /**< DIGCLKRETIMECTRL                                   */
  __IM uint32_t  DIGCLKRETIMESTATUS;            /**< DIGCLKRETIMESTATUS                                 */
  __IOM uint32_t XORETIMECTRL;                  /**< XORETIMECTRL                                       */
  __IM uint32_t  XORETIMESTATUS;                /**< XORETIMESTATUS                                     */
  __IOM uint32_t AGCOVERWRITE0;                 /**< OVERWRITE AGC                                      */
  __IOM uint32_t AGCOVERWRITE1;                 /**< OVERWRITE AGC                                      */
  __IOM uint32_t AGCOVERWRITE2;                 /**< OVERWRITE AGC                                      */
  uint32_t       RESERVED9[7U];                 /**< Reserved for future use                            */
  __IOM uint32_t PACTRL;                        /**< PACTRL                                             */
  __IOM uint32_t FENOTCH0;                      /**< FENOTCH0                                           */
  __IOM uint32_t FENOTCH1;                      /**< FENOTCH1                                           */
  uint32_t       RESERVED10[131U];              /**< Reserved for future use                            */
  __IOM uint32_t SCRATCH0;                      /**< SCRATCH0                                           */
  __IOM uint32_t SCRATCH1;                      /**< SCRATCH1                                           */
  __IOM uint32_t SCRATCH2;                      /**< SCRATCH2                                           */
  __IOM uint32_t SCRATCH3;                      /**< SCRATCH3                                           */
  __IOM uint32_t SCRATCH4;                      /**< SCRATCH4                                           */
  __IOM uint32_t SCRATCH5;                      /**< SCRATCH5                                           */
  __IOM uint32_t SCRATCH6;                      /**< SCRATCH6                                           */
  __IOM uint32_t SCRATCH7;                      /**< SCRATCH7                                           */
  uint32_t       RESERVED11[250U];              /**< Reserved for future use                            */
  __IOM uint32_t THMSW;                         /**< Thermister control                                 */
  uint32_t       RESERVED12[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED13[2U];                /**< Reserved for future use                            */
  uint32_t       RESERVED14[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED15[513U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP Version                                         */
  __IOM uint32_t EN_SET;                        /**< Enable peripheral clock to this module             */
  __IOM uint32_t RXENSRCEN_SET;                 /**< RXEN Source Enable                                 */
  __IM uint32_t  STATUS_SET;                    /**< Radio State Machine Status                         */
  __IOM uint32_t CMD_SET;                       /**< Radio Commands                                     */
  __IOM uint32_t CTRL_SET;                      /**< Radio Control Register                             */
  __IOM uint32_t FORCESTATE_SET;                /**< Force state transition                             */
  __IOM uint32_t IF_SET;                        /**< Radio Controller Interrupt Flags                   */
  __IOM uint32_t IEN_SET;                       /**< Interrupt Enable Register                          */
  __IOM uint32_t TESTCTRL_SET;                  /**< Test Control Register                              */
  __IOM uint32_t SEQIF_SET;                     /**< SEQ Interrupt Flags                                */
  __IOM uint32_t SEQIEN_SET;                    /**< SEQ Interrupt Enable Register                      */
  __IM uint32_t  STATUS1_SET;                   /**< Radio State Machine Status                         */
  __IM uint32_t  STIMER_SET;                    /**< Sequencer Timer Value                              */
  __IOM uint32_t STIMERCOMP_SET;                /**< Sequencer Timer Compare Value                      */
  __IOM uint32_t SEQCTRL_SET;                   /**< Sequencer Control Register                         */
  __IOM uint32_t PRESC_SET;                     /**< Sequencer prescaler Register                       */
  __IOM uint32_t SR0_SET;                       /**< Storage Register 0                                 */
  __IOM uint32_t SR1_SET;                       /**< Storage Register 1                                 */
  __IOM uint32_t SR2_SET;                       /**< Storage Register 2                                 */
  __IOM uint32_t SR3_SET;                       /**< Storage Register 3                                 */
  __IOM uint32_t STCTRL_SET;                    /**< Sys tick timer Control Register                    */
  __IOM uint32_t FRCTXWORD_SET;                 /**< FRC wordbuffer write                               */
  __IM uint32_t  FRCRXWORD_SET;                 /**< FRC wordbuffer read                                */
  __IOM uint32_t EM1PCSR_SET;                   /**< Radio EM1P Control and Status Register             */
  uint32_t       RESERVED16[13U];               /**< Reserved for future use                            */
  __IOM uint32_t SYNTHENCTRL_SET;               /**< Synthesizer Enable Control Register                */
  __IOM uint32_t SYNTHREGCTRL_SET;              /**< Synthesizer Regulator Enable Control               */
  __IOM uint32_t VCOCTRL_SET;                   /**< VCO Control Register                               */
  uint32_t       RESERVED17[2U];                /**< Reserved for future use                            */
  uint32_t       RESERVED18[1U];                /**< Reserved for future use                            */
  __IM uint32_t  STATUS2_SET;                   /**< Radio State Machine Status 2                       */
  __IOM uint32_t IFPGACTRL_SET;                 /**< IF PGA Control Register                            */
  __IOM uint32_t PAENCTRL_SET;                  /**< PA Enable Control Register                         */
  __IOM uint32_t APC_SET;                       /**< Automatic Power Control Register                   */
  __IOM uint32_t ANTDIV_SET;                    /**< ANTDIV                                             */
  __IOM uint32_t AUXADCTRIM_SET;                /**< AUXADCTRIM                                         */
  __IOM uint32_t AUXADCEN_SET;                  /**< AUXADCEN                                           */
  __IOM uint32_t AUXADCCTRL0_SET;               /**< Auxiliary ADC register control                     */
  __IOM uint32_t AUXADCCTRL1_SET;               /**< AUXADCCTRL1                                        */
  __IM uint32_t  AUXADCOUT_SET;                 /**< Auxiliary ADC digital output                       */
  __IOM uint32_t CLKMULTEN0_SET;                /**< CLKMULTEN0                                         */
  __IOM uint32_t CLKMULTEN1_SET;                /**< CLKMULTEN1                                         */
  __IOM uint32_t CLKMULTCTRL_SET;               /**< CLKMULTCTRL                                        */
  __IM uint32_t  CLKMULTSTATUS_SET;             /**< CLKMULTSTATUS                                      */
  uint32_t       RESERVED19[1U];                /**< Reserved for future use                            */
  __IOM uint32_t IFADCTRIM0_SET;                /**< IFADCTRIM0                                         */
  __IOM uint32_t IFADCTRIM1_SET;                /**< IFADCTRIM1                                         */
  __IOM uint32_t IFADCCAL_SET;                  /**< IFADCCAL                                           */
  __IM uint32_t  IFADCSTATUS_SET;               /**< IFADCSTATUS                                        */
  uint32_t       RESERVED20[1U];                /**< Reserved for future use                            */
  __IOM uint32_t LNAMIXTRIM0_SET;               /**< LNAMIXTRIM0                                        */
  __IOM uint32_t LNAMIXTRIM1_SET;               /**< LNAMIXTRIM1                                        */
  __IOM uint32_t LNAMIXTRIM2_SET;               /**< LNAMIXTRIM2                                        */
  __IOM uint32_t LNAMIXTRIM3_SET;               /**< LNAMIXTRIM3                                        */
  __IOM uint32_t LNAMIXTRIM4_SET;               /**< LNAMIXTRIM4                                        */
  __IOM uint32_t LNAMIXCAL_SET;                 /**< LNAMIXCAL                                          */
  __IOM uint32_t LNAMIXEN_SET;                  /**< LNAMIXEN                                           */
  __IOM uint32_t PRECTRL_SET;                   /**< PRECTRL                                            */
  __IOM uint32_t PATRIM0_SET;                   /**< PATRIM0                                            */
  __IOM uint32_t PATRIM1_SET;                   /**< PATRIM1                                            */
  __IOM uint32_t PATRIM2_SET;                   /**< PATRIM2                                            */
  __IOM uint32_t PATRIM3_SET;                   /**< PATRIM3                                            */
  __IOM uint32_t PATRIM4_SET;                   /**< PATRIM4                                            */
  __IOM uint32_t PATRIM5_SET;                   /**< PATRIM5                                            */
  uint32_t       RESERVED21[1U];                /**< Reserved for future use                            */
  __IOM uint32_t TXPOWER_SET;                   /**< TXPOWER                                            */
  __IOM uint32_t TXRAMP_SET;                    /**< TXRAMP                                             */
  uint32_t       RESERVED22[1U];                /**< Reserved for future use                            */
  __IOM uint32_t PGATRIM_SET;                   /**< PGATRIM                                            */
  __IOM uint32_t PGACAL_SET;                    /**< PGACAL                                             */
  __IOM uint32_t PGACTRL_SET;                   /**< PGACTRL                                            */
  __IOM uint32_t RFBIASCAL_SET;                 /**< RFBIASCAL                                          */
  __IOM uint32_t RFBIASCTRL_SET;                /**< RFBIASCTRL                                         */
  __IOM uint32_t RADIOEN_SET;                   /**< RADIOEN                                            */
  __IOM uint32_t RFPATHEN0_SET;                 /**< RFPATHEN0                                          */
  __IOM uint32_t RFPATHEN1_SET;                 /**< RFPATHEN1                                          */
  __IOM uint32_t RX_SET;                        /**< RX                                                 */
  __IOM uint32_t TX_SET;                        /**< TX                                                 */
  uint32_t       RESERVED23[1U];                /**< Reserved for future use                            */
  __IOM uint32_t SYTRIM0_SET;                   /**< SYTRIM0                                            */
  __IOM uint32_t SYTRIM1_SET;                   /**< SYTRIM1                                            */
  __IOM uint32_t SYCAL_SET;                     /**< SYCAL                                              */
  __IOM uint32_t SYEN_SET;                      /**< SYEN                                               */
  __IOM uint32_t SYLOEN_SET;                    /**< SYLOEN                                             */
  __IOM uint32_t SYMMDCTRL_SET;                 /**< SYMMDCTRL                                          */
  uint32_t       RESERVED24[1U];                /**< Reserved for future use                            */
  __IOM uint32_t DIGCLKRETIMECTRL_SET;          /**< DIGCLKRETIMECTRL                                   */
  __IM uint32_t  DIGCLKRETIMESTATUS_SET;        /**< DIGCLKRETIMESTATUS                                 */
  __IOM uint32_t XORETIMECTRL_SET;              /**< XORETIMECTRL                                       */
  __IM uint32_t  XORETIMESTATUS_SET;            /**< XORETIMESTATUS                                     */
  __IOM uint32_t AGCOVERWRITE0_SET;             /**< OVERWRITE AGC                                      */
  __IOM uint32_t AGCOVERWRITE1_SET;             /**< OVERWRITE AGC                                      */
  __IOM uint32_t AGCOVERWRITE2_SET;             /**< OVERWRITE AGC                                      */
  uint32_t       RESERVED25[7U];                /**< Reserved for future use                            */
  __IOM uint32_t PACTRL_SET;                    /**< PACTRL                                             */
  __IOM uint32_t FENOTCH0_SET;                  /**< FENOTCH0                                           */
  __IOM uint32_t FENOTCH1_SET;                  /**< FENOTCH1                                           */
  uint32_t       RESERVED26[131U];              /**< Reserved for future use                            */
  __IOM uint32_t SCRATCH0_SET;                  /**< SCRATCH0                                           */
  __IOM uint32_t SCRATCH1_SET;                  /**< SCRATCH1                                           */
  __IOM uint32_t SCRATCH2_SET;                  /**< SCRATCH2                                           */
  __IOM uint32_t SCRATCH3_SET;                  /**< SCRATCH3                                           */
  __IOM uint32_t SCRATCH4_SET;                  /**< SCRATCH4                                           */
  __IOM uint32_t SCRATCH5_SET;                  /**< SCRATCH5                                           */
  __IOM uint32_t SCRATCH6_SET;                  /**< SCRATCH6                                           */
  __IOM uint32_t SCRATCH7_SET;                  /**< SCRATCH7                                           */
  uint32_t       RESERVED27[250U];              /**< Reserved for future use                            */
  __IOM uint32_t THMSW_SET;                     /**< Thermister control                                 */
  uint32_t       RESERVED28[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED29[2U];                /**< Reserved for future use                            */
  uint32_t       RESERVED30[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED31[513U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP Version                                         */
  __IOM uint32_t EN_CLR;                        /**< Enable peripheral clock to this module             */
  __IOM uint32_t RXENSRCEN_CLR;                 /**< RXEN Source Enable                                 */
  __IM uint32_t  STATUS_CLR;                    /**< Radio State Machine Status                         */
  __IOM uint32_t CMD_CLR;                       /**< Radio Commands                                     */
  __IOM uint32_t CTRL_CLR;                      /**< Radio Control Register                             */
  __IOM uint32_t FORCESTATE_CLR;                /**< Force state transition                             */
  __IOM uint32_t IF_CLR;                        /**< Radio Controller Interrupt Flags                   */
  __IOM uint32_t IEN_CLR;                       /**< Interrupt Enable Register                          */
  __IOM uint32_t TESTCTRL_CLR;                  /**< Test Control Register                              */
  __IOM uint32_t SEQIF_CLR;                     /**< SEQ Interrupt Flags                                */
  __IOM uint32_t SEQIEN_CLR;                    /**< SEQ Interrupt Enable Register                      */
  __IM uint32_t  STATUS1_CLR;                   /**< Radio State Machine Status                         */
  __IM uint32_t  STIMER_CLR;                    /**< Sequencer Timer Value                              */
  __IOM uint32_t STIMERCOMP_CLR;                /**< Sequencer Timer Compare Value                      */
  __IOM uint32_t SEQCTRL_CLR;                   /**< Sequencer Control Register                         */
  __IOM uint32_t PRESC_CLR;                     /**< Sequencer prescaler Register                       */
  __IOM uint32_t SR0_CLR;                       /**< Storage Register 0                                 */
  __IOM uint32_t SR1_CLR;                       /**< Storage Register 1                                 */
  __IOM uint32_t SR2_CLR;                       /**< Storage Register 2                                 */
  __IOM uint32_t SR3_CLR;                       /**< Storage Register 3                                 */
  __IOM uint32_t STCTRL_CLR;                    /**< Sys tick timer Control Register                    */
  __IOM uint32_t FRCTXWORD_CLR;                 /**< FRC wordbuffer write                               */
  __IM uint32_t  FRCRXWORD_CLR;                 /**< FRC wordbuffer read                                */
  __IOM uint32_t EM1PCSR_CLR;                   /**< Radio EM1P Control and Status Register             */
  uint32_t       RESERVED32[13U];               /**< Reserved for future use                            */
  __IOM uint32_t SYNTHENCTRL_CLR;               /**< Synthesizer Enable Control Register                */
  __IOM uint32_t SYNTHREGCTRL_CLR;              /**< Synthesizer Regulator Enable Control               */
  __IOM uint32_t VCOCTRL_CLR;                   /**< VCO Control Register                               */
  uint32_t       RESERVED33[2U];                /**< Reserved for future use                            */
  uint32_t       RESERVED34[1U];                /**< Reserved for future use                            */
  __IM uint32_t  STATUS2_CLR;                   /**< Radio State Machine Status 2                       */
  __IOM uint32_t IFPGACTRL_CLR;                 /**< IF PGA Control Register                            */
  __IOM uint32_t PAENCTRL_CLR;                  /**< PA Enable Control Register                         */
  __IOM uint32_t APC_CLR;                       /**< Automatic Power Control Register                   */
  __IOM uint32_t ANTDIV_CLR;                    /**< ANTDIV                                             */
  __IOM uint32_t AUXADCTRIM_CLR;                /**< AUXADCTRIM                                         */
  __IOM uint32_t AUXADCEN_CLR;                  /**< AUXADCEN                                           */
  __IOM uint32_t AUXADCCTRL0_CLR;               /**< Auxiliary ADC register control                     */
  __IOM uint32_t AUXADCCTRL1_CLR;               /**< AUXADCCTRL1                                        */
  __IM uint32_t  AUXADCOUT_CLR;                 /**< Auxiliary ADC digital output                       */
  __IOM uint32_t CLKMULTEN0_CLR;                /**< CLKMULTEN0                                         */
  __IOM uint32_t CLKMULTEN1_CLR;                /**< CLKMULTEN1                                         */
  __IOM uint32_t CLKMULTCTRL_CLR;               /**< CLKMULTCTRL                                        */
  __IM uint32_t  CLKMULTSTATUS_CLR;             /**< CLKMULTSTATUS                                      */
  uint32_t       RESERVED35[1U];                /**< Reserved for future use                            */
  __IOM uint32_t IFADCTRIM0_CLR;                /**< IFADCTRIM0                                         */
  __IOM uint32_t IFADCTRIM1_CLR;                /**< IFADCTRIM1                                         */
  __IOM uint32_t IFADCCAL_CLR;                  /**< IFADCCAL                                           */
  __IM uint32_t  IFADCSTATUS_CLR;               /**< IFADCSTATUS                                        */
  uint32_t       RESERVED36[1U];                /**< Reserved for future use                            */
  __IOM uint32_t LNAMIXTRIM0_CLR;               /**< LNAMIXTRIM0                                        */
  __IOM uint32_t LNAMIXTRIM1_CLR;               /**< LNAMIXTRIM1                                        */
  __IOM uint32_t LNAMIXTRIM2_CLR;               /**< LNAMIXTRIM2                                        */
  __IOM uint32_t LNAMIXTRIM3_CLR;               /**< LNAMIXTRIM3                                        */
  __IOM uint32_t LNAMIXTRIM4_CLR;               /**< LNAMIXTRIM4                                        */
  __IOM uint32_t LNAMIXCAL_CLR;                 /**< LNAMIXCAL                                          */
  __IOM uint32_t LNAMIXEN_CLR;                  /**< LNAMIXEN                                           */
  __IOM uint32_t PRECTRL_CLR;                   /**< PRECTRL                                            */
  __IOM uint32_t PATRIM0_CLR;                   /**< PATRIM0                                            */
  __IOM uint32_t PATRIM1_CLR;                   /**< PATRIM1                                            */
  __IOM uint32_t PATRIM2_CLR;                   /**< PATRIM2                                            */
  __IOM uint32_t PATRIM3_CLR;                   /**< PATRIM3                                            */
  __IOM uint32_t PATRIM4_CLR;                   /**< PATRIM4                                            */
  __IOM uint32_t PATRIM5_CLR;                   /**< PATRIM5                                            */
  uint32_t       RESERVED37[1U];                /**< Reserved for future use                            */
  __IOM uint32_t TXPOWER_CLR;                   /**< TXPOWER                                            */
  __IOM uint32_t TXRAMP_CLR;                    /**< TXRAMP                                             */
  uint32_t       RESERVED38[1U];                /**< Reserved for future use                            */
  __IOM uint32_t PGATRIM_CLR;                   /**< PGATRIM                                            */
  __IOM uint32_t PGACAL_CLR;                    /**< PGACAL                                             */
  __IOM uint32_t PGACTRL_CLR;                   /**< PGACTRL                                            */
  __IOM uint32_t RFBIASCAL_CLR;                 /**< RFBIASCAL                                          */
  __IOM uint32_t RFBIASCTRL_CLR;                /**< RFBIASCTRL                                         */
  __IOM uint32_t RADIOEN_CLR;                   /**< RADIOEN                                            */
  __IOM uint32_t RFPATHEN0_CLR;                 /**< RFPATHEN0                                          */
  __IOM uint32_t RFPATHEN1_CLR;                 /**< RFPATHEN1                                          */
  __IOM uint32_t RX_CLR;                        /**< RX                                                 */
  __IOM uint32_t TX_CLR;                        /**< TX                                                 */
  uint32_t       RESERVED39[1U];                /**< Reserved for future use                            */
  __IOM uint32_t SYTRIM0_CLR;                   /**< SYTRIM0                                            */
  __IOM uint32_t SYTRIM1_CLR;                   /**< SYTRIM1                                            */
  __IOM uint32_t SYCAL_CLR;                     /**< SYCAL                                              */
  __IOM uint32_t SYEN_CLR;                      /**< SYEN                                               */
  __IOM uint32_t SYLOEN_CLR;                    /**< SYLOEN                                             */
  __IOM uint32_t SYMMDCTRL_CLR;                 /**< SYMMDCTRL                                          */
  uint32_t       RESERVED40[1U];                /**< Reserved for future use                            */
  __IOM uint32_t DIGCLKRETIMECTRL_CLR;          /**< DIGCLKRETIMECTRL                                   */
  __IM uint32_t  DIGCLKRETIMESTATUS_CLR;        /**< DIGCLKRETIMESTATUS                                 */
  __IOM uint32_t XORETIMECTRL_CLR;              /**< XORETIMECTRL                                       */
  __IM uint32_t  XORETIMESTATUS_CLR;            /**< XORETIMESTATUS                                     */
  __IOM uint32_t AGCOVERWRITE0_CLR;             /**< OVERWRITE AGC                                      */
  __IOM uint32_t AGCOVERWRITE1_CLR;             /**< OVERWRITE AGC                                      */
  __IOM uint32_t AGCOVERWRITE2_CLR;             /**< OVERWRITE AGC                                      */
  uint32_t       RESERVED41[7U];                /**< Reserved for future use                            */
  __IOM uint32_t PACTRL_CLR;                    /**< PACTRL                                             */
  __IOM uint32_t FENOTCH0_CLR;                  /**< FENOTCH0                                           */
  __IOM uint32_t FENOTCH1_CLR;                  /**< FENOTCH1                                           */
  uint32_t       RESERVED42[131U];              /**< Reserved for future use                            */
  __IOM uint32_t SCRATCH0_CLR;                  /**< SCRATCH0                                           */
  __IOM uint32_t SCRATCH1_CLR;                  /**< SCRATCH1                                           */
  __IOM uint32_t SCRATCH2_CLR;                  /**< SCRATCH2                                           */
  __IOM uint32_t SCRATCH3_CLR;                  /**< SCRATCH3                                           */
  __IOM uint32_t SCRATCH4_CLR;                  /**< SCRATCH4                                           */
  __IOM uint32_t SCRATCH5_CLR;                  /**< SCRATCH5                                           */
  __IOM uint32_t SCRATCH6_CLR;                  /**< SCRATCH6                                           */
  __IOM uint32_t SCRATCH7_CLR;                  /**< SCRATCH7                                           */
  uint32_t       RESERVED43[250U];              /**< Reserved for future use                            */
  __IOM uint32_t THMSW_CLR;                     /**< Thermister control                                 */
  uint32_t       RESERVED44[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED45[2U];                /**< Reserved for future use                            */
  uint32_t       RESERVED46[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED47[513U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP Version                                         */
  __IOM uint32_t EN_TGL;                        /**< Enable peripheral clock to this module             */
  __IOM uint32_t RXENSRCEN_TGL;                 /**< RXEN Source Enable                                 */
  __IM uint32_t  STATUS_TGL;                    /**< Radio State Machine Status                         */
  __IOM uint32_t CMD_TGL;                       /**< Radio Commands                                     */
  __IOM uint32_t CTRL_TGL;                      /**< Radio Control Register                             */
  __IOM uint32_t FORCESTATE_TGL;                /**< Force state transition                             */
  __IOM uint32_t IF_TGL;                        /**< Radio Controller Interrupt Flags                   */
  __IOM uint32_t IEN_TGL;                       /**< Interrupt Enable Register                          */
  __IOM uint32_t TESTCTRL_TGL;                  /**< Test Control Register                              */
  __IOM uint32_t SEQIF_TGL;                     /**< SEQ Interrupt Flags                                */
  __IOM uint32_t SEQIEN_TGL;                    /**< SEQ Interrupt Enable Register                      */
  __IM uint32_t  STATUS1_TGL;                   /**< Radio State Machine Status                         */
  __IM uint32_t  STIMER_TGL;                    /**< Sequencer Timer Value                              */
  __IOM uint32_t STIMERCOMP_TGL;                /**< Sequencer Timer Compare Value                      */
  __IOM uint32_t SEQCTRL_TGL;                   /**< Sequencer Control Register                         */
  __IOM uint32_t PRESC_TGL;                     /**< Sequencer prescaler Register                       */
  __IOM uint32_t SR0_TGL;                       /**< Storage Register 0                                 */
  __IOM uint32_t SR1_TGL;                       /**< Storage Register 1                                 */
  __IOM uint32_t SR2_TGL;                       /**< Storage Register 2                                 */
  __IOM uint32_t SR3_TGL;                       /**< Storage Register 3                                 */
  __IOM uint32_t STCTRL_TGL;                    /**< Sys tick timer Control Register                    */
  __IOM uint32_t FRCTXWORD_TGL;                 /**< FRC wordbuffer write                               */
  __IM uint32_t  FRCRXWORD_TGL;                 /**< FRC wordbuffer read                                */
  __IOM uint32_t EM1PCSR_TGL;                   /**< Radio EM1P Control and Status Register             */
  uint32_t       RESERVED48[13U];               /**< Reserved for future use                            */
  __IOM uint32_t SYNTHENCTRL_TGL;               /**< Synthesizer Enable Control Register                */
  __IOM uint32_t SYNTHREGCTRL_TGL;              /**< Synthesizer Regulator Enable Control               */
  __IOM uint32_t VCOCTRL_TGL;                   /**< VCO Control Register                               */
  uint32_t       RESERVED49[2U];                /**< Reserved for future use                            */
  uint32_t       RESERVED50[1U];                /**< Reserved for future use                            */
  __IM uint32_t  STATUS2_TGL;                   /**< Radio State Machine Status 2                       */
  __IOM uint32_t IFPGACTRL_TGL;                 /**< IF PGA Control Register                            */
  __IOM uint32_t PAENCTRL_TGL;                  /**< PA Enable Control Register                         */
  __IOM uint32_t APC_TGL;                       /**< Automatic Power Control Register                   */
  __IOM uint32_t ANTDIV_TGL;                    /**< ANTDIV                                             */
  __IOM uint32_t AUXADCTRIM_TGL;                /**< AUXADCTRIM                                         */
  __IOM uint32_t AUXADCEN_TGL;                  /**< AUXADCEN                                           */
  __IOM uint32_t AUXADCCTRL0_TGL;               /**< Auxiliary ADC register control                     */
  __IOM uint32_t AUXADCCTRL1_TGL;               /**< AUXADCCTRL1                                        */
  __IM uint32_t  AUXADCOUT_TGL;                 /**< Auxiliary ADC digital output                       */
  __IOM uint32_t CLKMULTEN0_TGL;                /**< CLKMULTEN0                                         */
  __IOM uint32_t CLKMULTEN1_TGL;                /**< CLKMULTEN1                                         */
  __IOM uint32_t CLKMULTCTRL_TGL;               /**< CLKMULTCTRL                                        */
  __IM uint32_t  CLKMULTSTATUS_TGL;             /**< CLKMULTSTATUS                                      */
  uint32_t       RESERVED51[1U];                /**< Reserved for future use                            */
  __IOM uint32_t IFADCTRIM0_TGL;                /**< IFADCTRIM0                                         */
  __IOM uint32_t IFADCTRIM1_TGL;                /**< IFADCTRIM1                                         */
  __IOM uint32_t IFADCCAL_TGL;                  /**< IFADCCAL                                           */
  __IM uint32_t  IFADCSTATUS_TGL;               /**< IFADCSTATUS                                        */
  uint32_t       RESERVED52[1U];                /**< Reserved for future use                            */
  __IOM uint32_t LNAMIXTRIM0_TGL;               /**< LNAMIXTRIM0                                        */
  __IOM uint32_t LNAMIXTRIM1_TGL;               /**< LNAMIXTRIM1                                        */
  __IOM uint32_t LNAMIXTRIM2_TGL;               /**< LNAMIXTRIM2                                        */
  __IOM uint32_t LNAMIXTRIM3_TGL;               /**< LNAMIXTRIM3                                        */
  __IOM uint32_t LNAMIXTRIM4_TGL;               /**< LNAMIXTRIM4                                        */
  __IOM uint32_t LNAMIXCAL_TGL;                 /**< LNAMIXCAL                                          */
  __IOM uint32_t LNAMIXEN_TGL;                  /**< LNAMIXEN                                           */
  __IOM uint32_t PRECTRL_TGL;                   /**< PRECTRL                                            */
  __IOM uint32_t PATRIM0_TGL;                   /**< PATRIM0                                            */
  __IOM uint32_t PATRIM1_TGL;                   /**< PATRIM1                                            */
  __IOM uint32_t PATRIM2_TGL;                   /**< PATRIM2                                            */
  __IOM uint32_t PATRIM3_TGL;                   /**< PATRIM3                                            */
  __IOM uint32_t PATRIM4_TGL;                   /**< PATRIM4                                            */
  __IOM uint32_t PATRIM5_TGL;                   /**< PATRIM5                                            */
  uint32_t       RESERVED53[1U];                /**< Reserved for future use                            */
  __IOM uint32_t TXPOWER_TGL;                   /**< TXPOWER                                            */
  __IOM uint32_t TXRAMP_TGL;                    /**< TXRAMP                                             */
  uint32_t       RESERVED54[1U];                /**< Reserved for future use                            */
  __IOM uint32_t PGATRIM_TGL;                   /**< PGATRIM                                            */
  __IOM uint32_t PGACAL_TGL;                    /**< PGACAL                                             */
  __IOM uint32_t PGACTRL_TGL;                   /**< PGACTRL                                            */
  __IOM uint32_t RFBIASCAL_TGL;                 /**< RFBIASCAL                                          */
  __IOM uint32_t RFBIASCTRL_TGL;                /**< RFBIASCTRL                                         */
  __IOM uint32_t RADIOEN_TGL;                   /**< RADIOEN                                            */
  __IOM uint32_t RFPATHEN0_TGL;                 /**< RFPATHEN0                                          */
  __IOM uint32_t RFPATHEN1_TGL;                 /**< RFPATHEN1                                          */
  __IOM uint32_t RX_TGL;                        /**< RX                                                 */
  __IOM uint32_t TX_TGL;                        /**< TX                                                 */
  uint32_t       RESERVED55[1U];                /**< Reserved for future use                            */
  __IOM uint32_t SYTRIM0_TGL;                   /**< SYTRIM0                                            */
  __IOM uint32_t SYTRIM1_TGL;                   /**< SYTRIM1                                            */
  __IOM uint32_t SYCAL_TGL;                     /**< SYCAL                                              */
  __IOM uint32_t SYEN_TGL;                      /**< SYEN                                               */
  __IOM uint32_t SYLOEN_TGL;                    /**< SYLOEN                                             */
  __IOM uint32_t SYMMDCTRL_TGL;                 /**< SYMMDCTRL                                          */
  uint32_t       RESERVED56[1U];                /**< Reserved for future use                            */
  __IOM uint32_t DIGCLKRETIMECTRL_TGL;          /**< DIGCLKRETIMECTRL                                   */
  __IM uint32_t  DIGCLKRETIMESTATUS_TGL;        /**< DIGCLKRETIMESTATUS                                 */
  __IOM uint32_t XORETIMECTRL_TGL;              /**< XORETIMECTRL                                       */
  __IM uint32_t  XORETIMESTATUS_TGL;            /**< XORETIMESTATUS                                     */
  __IOM uint32_t AGCOVERWRITE0_TGL;             /**< OVERWRITE AGC                                      */
  __IOM uint32_t AGCOVERWRITE1_TGL;             /**< OVERWRITE AGC                                      */
  __IOM uint32_t AGCOVERWRITE2_TGL;             /**< OVERWRITE AGC                                      */
  uint32_t       RESERVED57[7U];                /**< Reserved for future use                            */
  __IOM uint32_t PACTRL_TGL;                    /**< PACTRL                                             */
  __IOM uint32_t FENOTCH0_TGL;                  /**< FENOTCH0                                           */
  __IOM uint32_t FENOTCH1_TGL;                  /**< FENOTCH1                                           */
  uint32_t       RESERVED58[131U];              /**< Reserved for future use                            */
  __IOM uint32_t SCRATCH0_TGL;                  /**< SCRATCH0                                           */
  __IOM uint32_t SCRATCH1_TGL;                  /**< SCRATCH1                                           */
  __IOM uint32_t SCRATCH2_TGL;                  /**< SCRATCH2                                           */
  __IOM uint32_t SCRATCH3_TGL;                  /**< SCRATCH3                                           */
  __IOM uint32_t SCRATCH4_TGL;                  /**< SCRATCH4                                           */
  __IOM uint32_t SCRATCH5_TGL;                  /**< SCRATCH5                                           */
  __IOM uint32_t SCRATCH6_TGL;                  /**< SCRATCH6                                           */
  __IOM uint32_t SCRATCH7_TGL;                  /**< SCRATCH7                                           */
  uint32_t       RESERVED59[250U];              /**< Reserved for future use                            */
  __IOM uint32_t THMSW_TGL;                     /**< Thermister control                                 */
  uint32_t       RESERVED60[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED61[2U];                /**< Reserved for future use                            */
  uint32_t       RESERVED62[1U];                /**< Reserved for future use                            */
} RAC_TypeDef;
/** @} End of group EFR32MG24_RAC */

/**************************************************************************//**
 * @addtogroup EFR32MG24_RAC
 * @{
 * @defgroup EFR32MG24_RAC_BitFields RAC Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for RAC IPVERSION */
#define _RAC_IPVERSION_RESETVALUE                                     0x00000003UL                            /**< Default value for RAC_IPVERSION             */
#define _RAC_IPVERSION_MASK                                           0xFFFFFFFFUL                            /**< Mask for RAC_IPVERSION                      */
#define _RAC_IPVERSION_IPVERSION_SHIFT                                0                                       /**< Shift value for RAC_IPVERSION               */
#define _RAC_IPVERSION_IPVERSION_MASK                                 0xFFFFFFFFUL                            /**< Bit mask for RAC_IPVERSION                  */
#define _RAC_IPVERSION_IPVERSION_DEFAULT                              0x00000003UL                            /**< Mode DEFAULT for RAC_IPVERSION              */
#define RAC_IPVERSION_IPVERSION_DEFAULT                               (_RAC_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_IPVERSION      */

/* Bit fields for RAC EN */
#define _RAC_EN_RESETVALUE                                            0x00000000UL              /**< Default value for RAC_EN                    */
#define _RAC_EN_MASK                                                  0x00000001UL              /**< Mask for RAC_EN                             */
#define RAC_EN_EN                                                     (0x1UL << 0)              /**< Enable peripheral clock to this module      */
#define _RAC_EN_EN_SHIFT                                              0                         /**< Shift value for RAC_EN                      */
#define _RAC_EN_EN_MASK                                               0x1UL                     /**< Bit mask for RAC_EN                         */
#define _RAC_EN_EN_DEFAULT                                            0x00000000UL              /**< Mode DEFAULT for RAC_EN                     */
#define RAC_EN_EN_DEFAULT                                             (_RAC_EN_EN_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_EN             */

/* Bit fields for RAC RXENSRCEN */
#define _RAC_RXENSRCEN_RESETVALUE                                     0x00000000UL                                /**< Default value for RAC_RXENSRCEN             */
#define _RAC_RXENSRCEN_MASK                                           0x00003FFFUL                                /**< Mask for RAC_RXENSRCEN                      */
#define _RAC_RXENSRCEN_SWRXEN_SHIFT                                   0                                           /**< Shift value for RAC_SWRXEN                  */
#define _RAC_RXENSRCEN_SWRXEN_MASK                                    0xFFUL                                      /**< Bit mask for RAC_SWRXEN                     */
#define _RAC_RXENSRCEN_SWRXEN_DEFAULT                                 0x00000000UL                                /**< Mode DEFAULT for RAC_RXENSRCEN              */
#define RAC_RXENSRCEN_SWRXEN_DEFAULT                                  (_RAC_RXENSRCEN_SWRXEN_DEFAULT << 0)        /**< Shifted mode DEFAULT for RAC_RXENSRCEN      */
#define RAC_RXENSRCEN_CHANNELBUSYEN                                   (0x1UL << 8)                                /**< Channel Busy Enable                         */
#define _RAC_RXENSRCEN_CHANNELBUSYEN_SHIFT                            8                                           /**< Shift value for RAC_CHANNELBUSYEN           */
#define _RAC_RXENSRCEN_CHANNELBUSYEN_MASK                             0x100UL                                     /**< Bit mask for RAC_CHANNELBUSYEN              */
#define _RAC_RXENSRCEN_CHANNELBUSYEN_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for RAC_RXENSRCEN              */
#define RAC_RXENSRCEN_CHANNELBUSYEN_DEFAULT                           (_RAC_RXENSRCEN_CHANNELBUSYEN_DEFAULT << 8) /**< Shifted mode DEFAULT for RAC_RXENSRCEN      */
#define RAC_RXENSRCEN_TIMDETEN                                        (0x1UL << 9)                                /**< Timing Detected Enable                      */
#define _RAC_RXENSRCEN_TIMDETEN_SHIFT                                 9                                           /**< Shift value for RAC_TIMDETEN                */
#define _RAC_RXENSRCEN_TIMDETEN_MASK                                  0x200UL                                     /**< Bit mask for RAC_TIMDETEN                   */
#define _RAC_RXENSRCEN_TIMDETEN_DEFAULT                               0x00000000UL                                /**< Mode DEFAULT for RAC_RXENSRCEN              */
#define RAC_RXENSRCEN_TIMDETEN_DEFAULT                                (_RAC_RXENSRCEN_TIMDETEN_DEFAULT << 9)      /**< Shifted mode DEFAULT for RAC_RXENSRCEN      */
#define RAC_RXENSRCEN_PREDETEN                                        (0x1UL << 10)                               /**< Preamble Detected Enable                    */
#define _RAC_RXENSRCEN_PREDETEN_SHIFT                                 10                                          /**< Shift value for RAC_PREDETEN                */
#define _RAC_RXENSRCEN_PREDETEN_MASK                                  0x400UL                                     /**< Bit mask for RAC_PREDETEN                   */
#define _RAC_RXENSRCEN_PREDETEN_DEFAULT                               0x00000000UL                                /**< Mode DEFAULT for RAC_RXENSRCEN              */
#define RAC_RXENSRCEN_PREDETEN_DEFAULT                                (_RAC_RXENSRCEN_PREDETEN_DEFAULT << 10)     /**< Shifted mode DEFAULT for RAC_RXENSRCEN      */
#define RAC_RXENSRCEN_FRAMEDETEN                                      (0x1UL << 11)                               /**< Frame Detected Enable                       */
#define _RAC_RXENSRCEN_FRAMEDETEN_SHIFT                               11                                          /**< Shift value for RAC_FRAMEDETEN              */
#define _RAC_RXENSRCEN_FRAMEDETEN_MASK                                0x800UL                                     /**< Bit mask for RAC_FRAMEDETEN                 */
#define _RAC_RXENSRCEN_FRAMEDETEN_DEFAULT                             0x00000000UL                                /**< Mode DEFAULT for RAC_RXENSRCEN              */
#define RAC_RXENSRCEN_FRAMEDETEN_DEFAULT                              (_RAC_RXENSRCEN_FRAMEDETEN_DEFAULT << 11)   /**< Shifted mode DEFAULT for RAC_RXENSRCEN      */
#define RAC_RXENSRCEN_DEMODRXREQEN                                    (0x1UL << 12)                               /**< DEMOD RX Request Enable                     */
#define _RAC_RXENSRCEN_DEMODRXREQEN_SHIFT                             12                                          /**< Shift value for RAC_DEMODRXREQEN            */
#define _RAC_RXENSRCEN_DEMODRXREQEN_MASK                              0x1000UL                                    /**< Bit mask for RAC_DEMODRXREQEN               */
#define _RAC_RXENSRCEN_DEMODRXREQEN_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for RAC_RXENSRCEN              */
#define RAC_RXENSRCEN_DEMODRXREQEN_DEFAULT                            (_RAC_RXENSRCEN_DEMODRXREQEN_DEFAULT << 12) /**< Shifted mode DEFAULT for RAC_RXENSRCEN      */
#define RAC_RXENSRCEN_PRSRXEN                                         (0x1UL << 13)                               /**< PRS RX Enable                               */
#define _RAC_RXENSRCEN_PRSRXEN_SHIFT                                  13                                          /**< Shift value for RAC_PRSRXEN                 */
#define _RAC_RXENSRCEN_PRSRXEN_MASK                                   0x2000UL                                    /**< Bit mask for RAC_PRSRXEN                    */
#define _RAC_RXENSRCEN_PRSRXEN_DEFAULT                                0x00000000UL                                /**< Mode DEFAULT for RAC_RXENSRCEN              */
#define RAC_RXENSRCEN_PRSRXEN_DEFAULT                                 (_RAC_RXENSRCEN_PRSRXEN_DEFAULT << 13)      /**< Shifted mode DEFAULT for RAC_RXENSRCEN      */

/* Bit fields for RAC STATUS */
#define _RAC_STATUS_RESETVALUE                                        0x00000000UL                                   /**< Default value for RAC_STATUS                */
#define _RAC_STATUS_MASK                                              0xFFF8FFFFUL                                   /**< Mask for RAC_STATUS                         */
#define _RAC_STATUS_RXMASK_SHIFT                                      0                                              /**< Shift value for RAC_RXMASK                  */
#define _RAC_STATUS_RXMASK_MASK                                       0xFFFFUL                                       /**< Bit mask for RAC_RXMASK                     */
#define _RAC_STATUS_RXMASK_DEFAULT                                    0x00000000UL                                   /**< Mode DEFAULT for RAC_STATUS                 */
#define RAC_STATUS_RXMASK_DEFAULT                                     (_RAC_STATUS_RXMASK_DEFAULT << 0)              /**< Shifted mode DEFAULT for RAC_STATUS         */
#define RAC_STATUS_FORCESTATEACTIVE                                   (0x1UL << 19)                                  /**< FSM state force active                      */
#define _RAC_STATUS_FORCESTATEACTIVE_SHIFT                            19                                             /**< Shift value for RAC_FORCESTATEACTIVE        */
#define _RAC_STATUS_FORCESTATEACTIVE_MASK                             0x80000UL                                      /**< Bit mask for RAC_FORCESTATEACTIVE           */
#define _RAC_STATUS_FORCESTATEACTIVE_DEFAULT                          0x00000000UL                                   /**< Mode DEFAULT for RAC_STATUS                 */
#define _RAC_STATUS_FORCESTATEACTIVE_X0                               0x00000000UL                                   /**< Mode X0 for RAC_STATUS                      */
#define _RAC_STATUS_FORCESTATEACTIVE_X1                               0x00000001UL                                   /**< Mode X1 for RAC_STATUS                      */
#define RAC_STATUS_FORCESTATEACTIVE_DEFAULT                           (_RAC_STATUS_FORCESTATEACTIVE_DEFAULT << 19)   /**< Shifted mode DEFAULT for RAC_STATUS         */
#define RAC_STATUS_FORCESTATEACTIVE_X0                                (_RAC_STATUS_FORCESTATEACTIVE_X0 << 19)        /**< Shifted mode X0 for RAC_STATUS              */
#define RAC_STATUS_FORCESTATEACTIVE_X1                                (_RAC_STATUS_FORCESTATEACTIVE_X1 << 19)        /**< Shifted mode X1 for RAC_STATUS              */
#define RAC_STATUS_TXAFTERFRAMEPEND                                   (0x1UL << 20)                                  /**< TX After Frame Pending                      */
#define _RAC_STATUS_TXAFTERFRAMEPEND_SHIFT                            20                                             /**< Shift value for RAC_TXAFTERFRAMEPEND        */
#define _RAC_STATUS_TXAFTERFRAMEPEND_MASK                             0x100000UL                                     /**< Bit mask for RAC_TXAFTERFRAMEPEND           */
#define _RAC_STATUS_TXAFTERFRAMEPEND_DEFAULT                          0x00000000UL                                   /**< Mode DEFAULT for RAC_STATUS                 */
#define _RAC_STATUS_TXAFTERFRAMEPEND_X0                               0x00000000UL                                   /**< Mode X0 for RAC_STATUS                      */
#define _RAC_STATUS_TXAFTERFRAMEPEND_X1                               0x00000001UL                                   /**< Mode X1 for RAC_STATUS                      */
#define RAC_STATUS_TXAFTERFRAMEPEND_DEFAULT                           (_RAC_STATUS_TXAFTERFRAMEPEND_DEFAULT << 20)   /**< Shifted mode DEFAULT for RAC_STATUS         */
#define RAC_STATUS_TXAFTERFRAMEPEND_X0                                (_RAC_STATUS_TXAFTERFRAMEPEND_X0 << 20)        /**< Shifted mode X0 for RAC_STATUS              */
#define RAC_STATUS_TXAFTERFRAMEPEND_X1                                (_RAC_STATUS_TXAFTERFRAMEPEND_X1 << 20)        /**< Shifted mode X1 for RAC_STATUS              */
#define RAC_STATUS_TXAFTERFRAMEACTIVE                                 (0x1UL << 21)                                  /**< TX After Frame Active                       */
#define _RAC_STATUS_TXAFTERFRAMEACTIVE_SHIFT                          21                                             /**< Shift value for RAC_TXAFTERFRAMEACTIVE      */
#define _RAC_STATUS_TXAFTERFRAMEACTIVE_MASK                           0x200000UL                                     /**< Bit mask for RAC_TXAFTERFRAMEACTIVE         */
#define _RAC_STATUS_TXAFTERFRAMEACTIVE_DEFAULT                        0x00000000UL                                   /**< Mode DEFAULT for RAC_STATUS                 */
#define _RAC_STATUS_TXAFTERFRAMEACTIVE_X0                             0x00000000UL                                   /**< Mode X0 for RAC_STATUS                      */
#define _RAC_STATUS_TXAFTERFRAMEACTIVE_X1                             0x00000001UL                                   /**< Mode X1 for RAC_STATUS                      */
#define RAC_STATUS_TXAFTERFRAMEACTIVE_DEFAULT                         (_RAC_STATUS_TXAFTERFRAMEACTIVE_DEFAULT << 21) /**< Shifted mode DEFAULT for RAC_STATUS         */
#define RAC_STATUS_TXAFTERFRAMEACTIVE_X0                              (_RAC_STATUS_TXAFTERFRAMEACTIVE_X0 << 21)      /**< Shifted mode X0 for RAC_STATUS              */
#define RAC_STATUS_TXAFTERFRAMEACTIVE_X1                              (_RAC_STATUS_TXAFTERFRAMEACTIVE_X1 << 21)      /**< Shifted mode X1 for RAC_STATUS              */
#define RAC_STATUS_SEQSLEEPING                                        (0x1UL << 22)                                  /**< SEQ in sleeping                             */
#define _RAC_STATUS_SEQSLEEPING_SHIFT                                 22                                             /**< Shift value for RAC_SEQSLEEPING             */
#define _RAC_STATUS_SEQSLEEPING_MASK                                  0x400000UL                                     /**< Bit mask for RAC_SEQSLEEPING                */
#define _RAC_STATUS_SEQSLEEPING_DEFAULT                               0x00000000UL                                   /**< Mode DEFAULT for RAC_STATUS                 */
#define RAC_STATUS_SEQSLEEPING_DEFAULT                                (_RAC_STATUS_SEQSLEEPING_DEFAULT << 22)        /**< Shifted mode DEFAULT for RAC_STATUS         */
#define RAC_STATUS_SEQSLEEPDEEP                                       (0x1UL << 23)                                  /**< SEQ in deep sleep                           */
#define _RAC_STATUS_SEQSLEEPDEEP_SHIFT                                23                                             /**< Shift value for RAC_SEQSLEEPDEEP            */
#define _RAC_STATUS_SEQSLEEPDEEP_MASK                                 0x800000UL                                     /**< Bit mask for RAC_SEQSLEEPDEEP               */
#define _RAC_STATUS_SEQSLEEPDEEP_DEFAULT                              0x00000000UL                                   /**< Mode DEFAULT for RAC_STATUS                 */
#define RAC_STATUS_SEQSLEEPDEEP_DEFAULT                               (_RAC_STATUS_SEQSLEEPDEEP_DEFAULT << 23)       /**< Shifted mode DEFAULT for RAC_STATUS         */
#define _RAC_STATUS_STATE_SHIFT                                       24                                             /**< Shift value for RAC_STATE                   */
#define _RAC_STATUS_STATE_MASK                                        0xF000000UL                                    /**< Bit mask for RAC_STATE                      */
#define _RAC_STATUS_STATE_DEFAULT                                     0x00000000UL                                   /**< Mode DEFAULT for RAC_STATUS                 */
#define _RAC_STATUS_STATE_OFF                                         0x00000000UL                                   /**< Mode OFF for RAC_STATUS                     */
#define _RAC_STATUS_STATE_RXWARM                                      0x00000001UL                                   /**< Mode RXWARM for RAC_STATUS                  */
#define _RAC_STATUS_STATE_RXSEARCH                                    0x00000002UL                                   /**< Mode RXSEARCH for RAC_STATUS                */
#define _RAC_STATUS_STATE_RXFRAME                                     0x00000003UL                                   /**< Mode RXFRAME for RAC_STATUS                 */
#define _RAC_STATUS_STATE_RXPD                                        0x00000004UL                                   /**< Mode RXPD for RAC_STATUS                    */
#define _RAC_STATUS_STATE_RX2RX                                       0x00000005UL                                   /**< Mode RX2RX for RAC_STATUS                   */
#define _RAC_STATUS_STATE_RXOVERFLOW                                  0x00000006UL                                   /**< Mode RXOVERFLOW for RAC_STATUS              */
#define _RAC_STATUS_STATE_RX2TX                                       0x00000007UL                                   /**< Mode RX2TX for RAC_STATUS                   */
#define _RAC_STATUS_STATE_TXWARM                                      0x00000008UL                                   /**< Mode TXWARM for RAC_STATUS                  */
#define _RAC_STATUS_STATE_TX                                          0x00000009UL                                   /**< Mode TX for RAC_STATUS                      */
#define _RAC_STATUS_STATE_TXPD                                        0x0000000AUL                                   /**< Mode TXPD for RAC_STATUS                    */
#define _RAC_STATUS_STATE_TX2RX                                       0x0000000BUL                                   /**< Mode TX2RX for RAC_STATUS                   */
#define _RAC_STATUS_STATE_TX2TX                                       0x0000000CUL                                   /**< Mode TX2TX for RAC_STATUS                   */
#define _RAC_STATUS_STATE_SHUTDOWN                                    0x0000000DUL                                   /**< Mode SHUTDOWN for RAC_STATUS                */
#define _RAC_STATUS_STATE_POR                                         0x0000000EUL                                   /**< Mode POR for RAC_STATUS                     */
#define RAC_STATUS_STATE_DEFAULT                                      (_RAC_STATUS_STATE_DEFAULT << 24)              /**< Shifted mode DEFAULT for RAC_STATUS         */
#define RAC_STATUS_STATE_OFF                                          (_RAC_STATUS_STATE_OFF << 24)                  /**< Shifted mode OFF for RAC_STATUS             */
#define RAC_STATUS_STATE_RXWARM                                       (_RAC_STATUS_STATE_RXWARM << 24)               /**< Shifted mode RXWARM for RAC_STATUS          */
#define RAC_STATUS_STATE_RXSEARCH                                     (_RAC_STATUS_STATE_RXSEARCH << 24)             /**< Shifted mode RXSEARCH for RAC_STATUS        */
#define RAC_STATUS_STATE_RXFRAME                                      (_RAC_STATUS_STATE_RXFRAME << 24)              /**< Shifted mode RXFRAME for RAC_STATUS         */
#define RAC_STATUS_STATE_RXPD                                         (_RAC_STATUS_STATE_RXPD << 24)                 /**< Shifted mode RXPD for RAC_STATUS            */
#define RAC_STATUS_STATE_RX2RX                                        (_RAC_STATUS_STATE_RX2RX << 24)                /**< Shifted mode RX2RX for RAC_STATUS           */
#define RAC_STATUS_STATE_RXOVERFLOW                                   (_RAC_STATUS_STATE_RXOVERFLOW << 24)           /**< Shifted mode RXOVERFLOW for RAC_STATUS      */
#define RAC_STATUS_STATE_RX2TX                                        (_RAC_STATUS_STATE_RX2TX << 24)                /**< Shifted mode RX2TX for RAC_STATUS           */
#define RAC_STATUS_STATE_TXWARM                                       (_RAC_STATUS_STATE_TXWARM << 24)               /**< Shifted mode TXWARM for RAC_STATUS          */
#define RAC_STATUS_STATE_TX                                           (_RAC_STATUS_STATE_TX << 24)                   /**< Shifted mode TX for RAC_STATUS              */
#define RAC_STATUS_STATE_TXPD                                         (_RAC_STATUS_STATE_TXPD << 24)                 /**< Shifted mode TXPD for RAC_STATUS            */
#define RAC_STATUS_STATE_TX2RX                                        (_RAC_STATUS_STATE_TX2RX << 24)                /**< Shifted mode TX2RX for RAC_STATUS           */
#define RAC_STATUS_STATE_TX2TX                                        (_RAC_STATUS_STATE_TX2TX << 24)                /**< Shifted mode TX2TX for RAC_STATUS           */
#define RAC_STATUS_STATE_SHUTDOWN                                     (_RAC_STATUS_STATE_SHUTDOWN << 24)             /**< Shifted mode SHUTDOWN for RAC_STATUS        */
#define RAC_STATUS_STATE_POR                                          (_RAC_STATUS_STATE_POR << 24)                  /**< Shifted mode POR for RAC_STATUS             */
#define RAC_STATUS_SEQACTIVE                                          (0x1UL << 28)                                  /**< SEQ active                                  */
#define _RAC_STATUS_SEQACTIVE_SHIFT                                   28                                             /**< Shift value for RAC_SEQACTIVE               */
#define _RAC_STATUS_SEQACTIVE_MASK                                    0x10000000UL                                   /**< Bit mask for RAC_SEQACTIVE                  */
#define _RAC_STATUS_SEQACTIVE_DEFAULT                                 0x00000000UL                                   /**< Mode DEFAULT for RAC_STATUS                 */
#define RAC_STATUS_SEQACTIVE_DEFAULT                                  (_RAC_STATUS_SEQACTIVE_DEFAULT << 28)          /**< Shifted mode DEFAULT for RAC_STATUS         */
#define RAC_STATUS_TXENS                                              (0x1UL << 30)                                  /**< TXEN Status                                 */
#define _RAC_STATUS_TXENS_SHIFT                                       30                                             /**< Shift value for RAC_TXENS                   */
#define _RAC_STATUS_TXENS_MASK                                        0x40000000UL                                   /**< Bit mask for RAC_TXENS                      */
#define _RAC_STATUS_TXENS_DEFAULT                                     0x00000000UL                                   /**< Mode DEFAULT for RAC_STATUS                 */
#define _RAC_STATUS_TXENS_X0                                          0x00000000UL                                   /**< Mode X0 for RAC_STATUS                      */
#define _RAC_STATUS_TXENS_X1                                          0x00000001UL                                   /**< Mode X1 for RAC_STATUS                      */
#define RAC_STATUS_TXENS_DEFAULT                                      (_RAC_STATUS_TXENS_DEFAULT << 30)              /**< Shifted mode DEFAULT for RAC_STATUS         */
#define RAC_STATUS_TXENS_X0                                           (_RAC_STATUS_TXENS_X0 << 30)                   /**< Shifted mode X0 for RAC_STATUS              */
#define RAC_STATUS_TXENS_X1                                           (_RAC_STATUS_TXENS_X1 << 30)                   /**< Shifted mode X1 for RAC_STATUS              */
#define RAC_STATUS_RXENS                                              (0x1UL << 31)                                  /**< RXEN Status                                 */
#define _RAC_STATUS_RXENS_SHIFT                                       31                                             /**< Shift value for RAC_RXENS                   */
#define _RAC_STATUS_RXENS_MASK                                        0x80000000UL                                   /**< Bit mask for RAC_RXENS                      */
#define _RAC_STATUS_RXENS_DEFAULT                                     0x00000000UL                                   /**< Mode DEFAULT for RAC_STATUS                 */
#define _RAC_STATUS_RXENS_X0                                          0x00000000UL                                   /**< Mode X0 for RAC_STATUS                      */
#define _RAC_STATUS_RXENS_X1                                          0x00000001UL                                   /**< Mode X1 for RAC_STATUS                      */
#define RAC_STATUS_RXENS_DEFAULT                                      (_RAC_STATUS_RXENS_DEFAULT << 31)              /**< Shifted mode DEFAULT for RAC_STATUS         */
#define RAC_STATUS_RXENS_X0                                           (_RAC_STATUS_RXENS_X0 << 31)                   /**< Shifted mode X0 for RAC_STATUS              */
#define RAC_STATUS_RXENS_X1                                           (_RAC_STATUS_RXENS_X1 << 31)                   /**< Shifted mode X1 for RAC_STATUS              */

/* Bit fields for RAC CMD */
#define _RAC_CMD_RESETVALUE                                           0x00000000UL                            /**< Default value for RAC_CMD                   */
#define _RAC_CMD_MASK                                                 0xC000FDFFUL                            /**< Mask for RAC_CMD                            */
#define RAC_CMD_TXEN                                                  (0x1UL << 0)                            /**< Transmitter Enable                          */
#define _RAC_CMD_TXEN_SHIFT                                           0                                       /**< Shift value for RAC_TXEN                    */
#define _RAC_CMD_TXEN_MASK                                            0x1UL                                   /**< Bit mask for RAC_TXEN                       */
#define _RAC_CMD_TXEN_DEFAULT                                         0x00000000UL                            /**< Mode DEFAULT for RAC_CMD                    */
#define RAC_CMD_TXEN_DEFAULT                                          (_RAC_CMD_TXEN_DEFAULT << 0)            /**< Shifted mode DEFAULT for RAC_CMD            */
#define RAC_CMD_FORCETX                                               (0x1UL << 1)                            /**< Force TX Command                            */
#define _RAC_CMD_FORCETX_SHIFT                                        1                                       /**< Shift value for RAC_FORCETX                 */
#define _RAC_CMD_FORCETX_MASK                                         0x2UL                                   /**< Bit mask for RAC_FORCETX                    */
#define _RAC_CMD_FORCETX_DEFAULT                                      0x00000000UL                            /**< Mode DEFAULT for RAC_CMD                    */
#define RAC_CMD_FORCETX_DEFAULT                                       (_RAC_CMD_FORCETX_DEFAULT << 1)         /**< Shifted mode DEFAULT for RAC_CMD            */
#define RAC_CMD_TXONCCA                                               (0x1UL << 2)                            /**< Transmit On CCA                             */
#define _RAC_CMD_TXONCCA_SHIFT                                        2                                       /**< Shift value for RAC_TXONCCA                 */
#define _RAC_CMD_TXONCCA_MASK                                         0x4UL                                   /**< Bit mask for RAC_TXONCCA                    */
#define _RAC_CMD_TXONCCA_DEFAULT                                      0x00000000UL                            /**< Mode DEFAULT for RAC_CMD                    */
#define RAC_CMD_TXONCCA_DEFAULT                                       (_RAC_CMD_TXONCCA_DEFAULT << 2)         /**< Shifted mode DEFAULT for RAC_CMD            */
#define RAC_CMD_CLEARTXEN                                             (0x1UL << 3)                            /**< Clear TX Enable                             */
#define _RAC_CMD_CLEARTXEN_SHIFT                                      3                                       /**< Shift value for RAC_CLEARTXEN               */
#define _RAC_CMD_CLEARTXEN_MASK                                       0x8UL                                   /**< Bit mask for RAC_CLEARTXEN                  */
#define _RAC_CMD_CLEARTXEN_DEFAULT                                    0x00000000UL                            /**< Mode DEFAULT for RAC_CMD                    */
#define RAC_CMD_CLEARTXEN_DEFAULT                                     (_RAC_CMD_CLEARTXEN_DEFAULT << 3)       /**< Shifted mode DEFAULT for RAC_CMD            */
#define RAC_CMD_TXAFTERFRAME                                          (0x1UL << 4)                            /**< TX After Frame                              */
#define _RAC_CMD_TXAFTERFRAME_SHIFT                                   4                                       /**< Shift value for RAC_TXAFTERFRAME            */
#define _RAC_CMD_TXAFTERFRAME_MASK                                    0x10UL                                  /**< Bit mask for RAC_TXAFTERFRAME               */
#define _RAC_CMD_TXAFTERFRAME_DEFAULT                                 0x00000000UL                            /**< Mode DEFAULT for RAC_CMD                    */
#define RAC_CMD_TXAFTERFRAME_DEFAULT                                  (_RAC_CMD_TXAFTERFRAME_DEFAULT << 4)    /**< Shifted mode DEFAULT for RAC_CMD            */
#define RAC_CMD_TXDIS                                                 (0x1UL << 5)                            /**< TX Disable                                  */
#define _RAC_CMD_TXDIS_SHIFT                                          5                                       /**< Shift value for RAC_TXDIS                   */
#define _RAC_CMD_TXDIS_MASK                                           0x20UL                                  /**< Bit mask for RAC_TXDIS                      */
#define _RAC_CMD_TXDIS_DEFAULT                                        0x00000000UL                            /**< Mode DEFAULT for RAC_CMD                    */
#define RAC_CMD_TXDIS_DEFAULT                                         (_RAC_CMD_TXDIS_DEFAULT << 5)           /**< Shifted mode DEFAULT for RAC_CMD            */
#define RAC_CMD_CLEARRXOVERFLOW                                       (0x1UL << 6)                            /**< Clear RX Overflow                           */
#define _RAC_CMD_CLEARRXOVERFLOW_SHIFT                                6                                       /**< Shift value for RAC_CLEARRXOVERFLOW         */
#define _RAC_CMD_CLEARRXOVERFLOW_MASK                                 0x40UL                                  /**< Bit mask for RAC_CLEARRXOVERFLOW            */
#define _RAC_CMD_CLEARRXOVERFLOW_DEFAULT                              0x00000000UL                            /**< Mode DEFAULT for RAC_CMD                    */
#define RAC_CMD_CLEARRXOVERFLOW_DEFAULT                               (_RAC_CMD_CLEARRXOVERFLOW_DEFAULT << 6) /**< Shifted mode DEFAULT for RAC_CMD            */
#define RAC_CMD_RXCAL                                                 (0x1UL << 7)                            /**< Start an RX Calibration                     */
#define _RAC_CMD_RXCAL_SHIFT                                          7                                       /**< Shift value for RAC_RXCAL                   */
#define _RAC_CMD_RXCAL_MASK                                           0x80UL                                  /**< Bit mask for RAC_RXCAL                      */
#define _RAC_CMD_RXCAL_DEFAULT                                        0x00000000UL                            /**< Mode DEFAULT for RAC_CMD                    */
#define RAC_CMD_RXCAL_DEFAULT                                         (_RAC_CMD_RXCAL_DEFAULT << 7)           /**< Shifted mode DEFAULT for RAC_CMD            */
#define RAC_CMD_RXDIS                                                 (0x1UL << 8)                            /**< RX Disable                                  */
#define _RAC_CMD_RXDIS_SHIFT                                          8                                       /**< Shift value for RAC_RXDIS                   */
#define _RAC_CMD_RXDIS_MASK                                           0x100UL                                 /**< Bit mask for RAC_RXDIS                      */
#define _RAC_CMD_RXDIS_DEFAULT                                        0x00000000UL                            /**< Mode DEFAULT for RAC_CMD                    */
#define RAC_CMD_RXDIS_DEFAULT                                         (_RAC_CMD_RXDIS_DEFAULT << 8)           /**< Shifted mode DEFAULT for RAC_CMD            */
#define RAC_CMD_FRCWR                                                 (0x1UL << 10)                           /**< FRC write cmd                               */
#define _RAC_CMD_FRCWR_SHIFT                                          10                                      /**< Shift value for RAC_FRCWR                   */
#define _RAC_CMD_FRCWR_MASK                                           0x400UL                                 /**< Bit mask for RAC_FRCWR                      */
#define _RAC_CMD_FRCWR_DEFAULT                                        0x00000000UL                            /**< Mode DEFAULT for RAC_CMD                    */
#define RAC_CMD_FRCWR_DEFAULT                                         (_RAC_CMD_FRCWR_DEFAULT << 10)          /**< Shifted mode DEFAULT for RAC_CMD            */
#define RAC_CMD_FRCRD                                                 (0x1UL << 11)                           /**< FRC read cmd                                */
#define _RAC_CMD_FRCRD_SHIFT                                          11                                      /**< Shift value for RAC_FRCRD                   */
#define _RAC_CMD_FRCRD_MASK                                           0x800UL                                 /**< Bit mask for RAC_FRCRD                      */
#define _RAC_CMD_FRCRD_DEFAULT                                        0x00000000UL                            /**< Mode DEFAULT for RAC_CMD                    */
#define RAC_CMD_FRCRD_DEFAULT                                         (_RAC_CMD_FRCRD_DEFAULT << 11)          /**< Shifted mode DEFAULT for RAC_CMD            */
#define RAC_CMD_PAENSET                                               (0x1UL << 12)                           /**< PAEN Set                                    */
#define _RAC_CMD_PAENSET_SHIFT                                        12                                      /**< Shift value for RAC_PAENSET                 */
#define _RAC_CMD_PAENSET_MASK                                         0x1000UL                                /**< Bit mask for RAC_PAENSET                    */
#define _RAC_CMD_PAENSET_DEFAULT                                      0x00000000UL                            /**< Mode DEFAULT for RAC_CMD                    */
#define RAC_CMD_PAENSET_DEFAULT                                       (_RAC_CMD_PAENSET_DEFAULT << 12)        /**< Shifted mode DEFAULT for RAC_CMD            */
#define RAC_CMD_PAENCLEAR                                             (0x1UL << 13)                           /**< PAEN Clear                                  */
#define _RAC_CMD_PAENCLEAR_SHIFT                                      13                                      /**< Shift value for RAC_PAENCLEAR               */
#define _RAC_CMD_PAENCLEAR_MASK                                       0x2000UL                                /**< Bit mask for RAC_PAENCLEAR                  */
#define _RAC_CMD_PAENCLEAR_DEFAULT                                    0x00000000UL                            /**< Mode DEFAULT for RAC_CMD                    */
#define RAC_CMD_PAENCLEAR_DEFAULT                                     (_RAC_CMD_PAENCLEAR_DEFAULT << 13)      /**< Shifted mode DEFAULT for RAC_CMD            */
#define RAC_CMD_LNAENSET                                              (0x1UL << 14)                           /**< LNAEN Set                                   */
#define _RAC_CMD_LNAENSET_SHIFT                                       14                                      /**< Shift value for RAC_LNAENSET                */
#define _RAC_CMD_LNAENSET_MASK                                        0x4000UL                                /**< Bit mask for RAC_LNAENSET                   */
#define _RAC_CMD_LNAENSET_DEFAULT                                     0x00000000UL                            /**< Mode DEFAULT for RAC_CMD                    */
#define RAC_CMD_LNAENSET_DEFAULT                                      (_RAC_CMD_LNAENSET_DEFAULT << 14)       /**< Shifted mode DEFAULT for RAC_CMD            */
#define RAC_CMD_LNAENCLEAR                                            (0x1UL << 15)                           /**< LNAEN Clear                                 */
#define _RAC_CMD_LNAENCLEAR_SHIFT                                     15                                      /**< Shift value for RAC_LNAENCLEAR              */
#define _RAC_CMD_LNAENCLEAR_MASK                                      0x8000UL                                /**< Bit mask for RAC_LNAENCLEAR                 */
#define _RAC_CMD_LNAENCLEAR_DEFAULT                                   0x00000000UL                            /**< Mode DEFAULT for RAC_CMD                    */
#define RAC_CMD_LNAENCLEAR_DEFAULT                                    (_RAC_CMD_LNAENCLEAR_DEFAULT << 15)     /**< Shifted mode DEFAULT for RAC_CMD            */

/* Bit fields for RAC CTRL */
#define _RAC_CTRL_RESETVALUE                                          0x00000000UL                              /**< Default value for RAC_CTRL                  */
#define _RAC_CTRL_MASK                                                0x1F0107EFUL                              /**< Mask for RAC_CTRL                           */
#define RAC_CTRL_FORCEDISABLE                                         (0x1UL << 0)                              /**< Force Radio Disable                         */
#define _RAC_CTRL_FORCEDISABLE_SHIFT                                  0                                         /**< Shift value for RAC_FORCEDISABLE            */
#define _RAC_CTRL_FORCEDISABLE_MASK                                   0x1UL                                     /**< Bit mask for RAC_FORCEDISABLE               */
#define _RAC_CTRL_FORCEDISABLE_DEFAULT                                0x00000000UL                              /**< Mode DEFAULT for RAC_CTRL                   */
#define RAC_CTRL_FORCEDISABLE_DEFAULT                                 (_RAC_CTRL_FORCEDISABLE_DEFAULT << 0)     /**< Shifted mode DEFAULT for RAC_CTRL           */
#define RAC_CTRL_PRSTXEN                                              (0x1UL << 1)                              /**< PRS TX Enable                               */
#define _RAC_CTRL_PRSTXEN_SHIFT                                       1                                         /**< Shift value for RAC_PRSTXEN                 */
#define _RAC_CTRL_PRSTXEN_MASK                                        0x2UL                                     /**< Bit mask for RAC_PRSTXEN                    */
#define _RAC_CTRL_PRSTXEN_DEFAULT                                     0x00000000UL                              /**< Mode DEFAULT for RAC_CTRL                   */
#define RAC_CTRL_PRSTXEN_DEFAULT                                      (_RAC_CTRL_PRSTXEN_DEFAULT << 1)          /**< Shifted mode DEFAULT for RAC_CTRL           */
#define RAC_CTRL_TXAFTERRX                                            (0x1UL << 2)                              /**< TX After RX                                 */
#define _RAC_CTRL_TXAFTERRX_SHIFT                                     2                                         /**< Shift value for RAC_TXAFTERRX               */
#define _RAC_CTRL_TXAFTERRX_MASK                                      0x4UL                                     /**< Bit mask for RAC_TXAFTERRX                  */
#define _RAC_CTRL_TXAFTERRX_DEFAULT                                   0x00000000UL                              /**< Mode DEFAULT for RAC_CTRL                   */
#define _RAC_CTRL_TXAFTERRX_X0                                        0x00000000UL                              /**< Mode X0 for RAC_CTRL                        */
#define _RAC_CTRL_TXAFTERRX_X1                                        0x00000001UL                              /**< Mode X1 for RAC_CTRL                        */
#define RAC_CTRL_TXAFTERRX_DEFAULT                                    (_RAC_CTRL_TXAFTERRX_DEFAULT << 2)        /**< Shifted mode DEFAULT for RAC_CTRL           */
#define RAC_CTRL_TXAFTERRX_X0                                         (_RAC_CTRL_TXAFTERRX_X0 << 2)             /**< Shifted mode X0 for RAC_CTRL                */
#define RAC_CTRL_TXAFTERRX_X1                                         (_RAC_CTRL_TXAFTERRX_X1 << 2)             /**< Shifted mode X1 for RAC_CTRL                */
#define RAC_CTRL_PRSMODE                                              (0x1UL << 3)                              /**< PRS RXEN Mode                               */
#define _RAC_CTRL_PRSMODE_SHIFT                                       3                                         /**< Shift value for RAC_PRSMODE                 */
#define _RAC_CTRL_PRSMODE_MASK                                        0x8UL                                     /**< Bit mask for RAC_PRSMODE                    */
#define _RAC_CTRL_PRSMODE_DEFAULT                                     0x00000000UL                              /**< Mode DEFAULT for RAC_CTRL                   */
#define _RAC_CTRL_PRSMODE_DIRECT                                      0x00000000UL                              /**< Mode DIRECT for RAC_CTRL                    */
#define _RAC_CTRL_PRSMODE_PULSE                                       0x00000001UL                              /**< Mode PULSE for RAC_CTRL                     */
#define RAC_CTRL_PRSMODE_DEFAULT                                      (_RAC_CTRL_PRSMODE_DEFAULT << 3)          /**< Shifted mode DEFAULT for RAC_CTRL           */
#define RAC_CTRL_PRSMODE_DIRECT                                       (_RAC_CTRL_PRSMODE_DIRECT << 3)           /**< Shifted mode DIRECT for RAC_CTRL            */
#define RAC_CTRL_PRSMODE_PULSE                                        (_RAC_CTRL_PRSMODE_PULSE << 3)            /**< Shifted mode PULSE for RAC_CTRL             */
#define RAC_CTRL_PRSCLR                                               (0x1UL << 5)                              /**< PRS RXEN Clear                              */
#define _RAC_CTRL_PRSCLR_SHIFT                                        5                                         /**< Shift value for RAC_PRSCLR                  */
#define _RAC_CTRL_PRSCLR_MASK                                         0x20UL                                    /**< Bit mask for RAC_PRSCLR                     */
#define _RAC_CTRL_PRSCLR_DEFAULT                                      0x00000000UL                              /**< Mode DEFAULT for RAC_CTRL                   */
#define _RAC_CTRL_PRSCLR_RXSEARCH                                     0x00000000UL                              /**< Mode RXSEARCH for RAC_CTRL                  */
#define _RAC_CTRL_PRSCLR_PRSCH                                        0x00000001UL                              /**< Mode PRSCH for RAC_CTRL                     */
#define RAC_CTRL_PRSCLR_DEFAULT                                       (_RAC_CTRL_PRSCLR_DEFAULT << 5)           /**< Shifted mode DEFAULT for RAC_CTRL           */
#define RAC_CTRL_PRSCLR_RXSEARCH                                      (_RAC_CTRL_PRSCLR_RXSEARCH << 5)          /**< Shifted mode RXSEARCH for RAC_CTRL          */
#define RAC_CTRL_PRSCLR_PRSCH                                         (_RAC_CTRL_PRSCLR_PRSCH << 5)             /**< Shifted mode PRSCH for RAC_CTRL             */
#define RAC_CTRL_TXPOSTPONE                                           (0x1UL << 6)                              /**< TX Postpone                                 */
#define _RAC_CTRL_TXPOSTPONE_SHIFT                                    6                                         /**< Shift value for RAC_TXPOSTPONE              */
#define _RAC_CTRL_TXPOSTPONE_MASK                                     0x40UL                                    /**< Bit mask for RAC_TXPOSTPONE                 */
#define _RAC_CTRL_TXPOSTPONE_DEFAULT                                  0x00000000UL                              /**< Mode DEFAULT for RAC_CTRL                   */
#define _RAC_CTRL_TXPOSTPONE_X0                                       0x00000000UL                              /**< Mode X0 for RAC_CTRL                        */
#define _RAC_CTRL_TXPOSTPONE_X1                                       0x00000001UL                              /**< Mode X1 for RAC_CTRL                        */
#define RAC_CTRL_TXPOSTPONE_DEFAULT                                   (_RAC_CTRL_TXPOSTPONE_DEFAULT << 6)       /**< Shifted mode DEFAULT for RAC_CTRL           */
#define RAC_CTRL_TXPOSTPONE_X0                                        (_RAC_CTRL_TXPOSTPONE_X0 << 6)            /**< Shifted mode X0 for RAC_CTRL                */
#define RAC_CTRL_TXPOSTPONE_X1                                        (_RAC_CTRL_TXPOSTPONE_X1 << 6)            /**< Shifted mode X1 for RAC_CTRL                */
#define RAC_CTRL_ACTIVEPOL                                            (0x1UL << 7)                              /**< ACTIVE signal polarity                      */
#define _RAC_CTRL_ACTIVEPOL_SHIFT                                     7                                         /**< Shift value for RAC_ACTIVEPOL               */
#define _RAC_CTRL_ACTIVEPOL_MASK                                      0x80UL                                    /**< Bit mask for RAC_ACTIVEPOL                  */
#define _RAC_CTRL_ACTIVEPOL_DEFAULT                                   0x00000000UL                              /**< Mode DEFAULT for RAC_CTRL                   */
#define _RAC_CTRL_ACTIVEPOL_X0                                        0x00000000UL                              /**< Mode X0 for RAC_CTRL                        */
#define _RAC_CTRL_ACTIVEPOL_X1                                        0x00000001UL                              /**< Mode X1 for RAC_CTRL                        */
#define RAC_CTRL_ACTIVEPOL_DEFAULT                                    (_RAC_CTRL_ACTIVEPOL_DEFAULT << 7)        /**< Shifted mode DEFAULT for RAC_CTRL           */
#define RAC_CTRL_ACTIVEPOL_X0                                         (_RAC_CTRL_ACTIVEPOL_X0 << 7)             /**< Shifted mode X0 for RAC_CTRL                */
#define RAC_CTRL_ACTIVEPOL_X1                                         (_RAC_CTRL_ACTIVEPOL_X1 << 7)             /**< Shifted mode X1 for RAC_CTRL                */
#define RAC_CTRL_PAENPOL                                              (0x1UL << 8)                              /**< PAEN signal polarity                        */
#define _RAC_CTRL_PAENPOL_SHIFT                                       8                                         /**< Shift value for RAC_PAENPOL                 */
#define _RAC_CTRL_PAENPOL_MASK                                        0x100UL                                   /**< Bit mask for RAC_PAENPOL                    */
#define _RAC_CTRL_PAENPOL_DEFAULT                                     0x00000000UL                              /**< Mode DEFAULT for RAC_CTRL                   */
#define _RAC_CTRL_PAENPOL_X0                                          0x00000000UL                              /**< Mode X0 for RAC_CTRL                        */
#define _RAC_CTRL_PAENPOL_X1                                          0x00000001UL                              /**< Mode X1 for RAC_CTRL                        */
#define RAC_CTRL_PAENPOL_DEFAULT                                      (_RAC_CTRL_PAENPOL_DEFAULT << 8)          /**< Shifted mode DEFAULT for RAC_CTRL           */
#define RAC_CTRL_PAENPOL_X0                                           (_RAC_CTRL_PAENPOL_X0 << 8)               /**< Shifted mode X0 for RAC_CTRL                */
#define RAC_CTRL_PAENPOL_X1                                           (_RAC_CTRL_PAENPOL_X1 << 8)               /**< Shifted mode X1 for RAC_CTRL                */
#define RAC_CTRL_LNAENPOL                                             (0x1UL << 9)                              /**< LNAEN signal polarity                       */
#define _RAC_CTRL_LNAENPOL_SHIFT                                      9                                         /**< Shift value for RAC_LNAENPOL                */
#define _RAC_CTRL_LNAENPOL_MASK                                       0x200UL                                   /**< Bit mask for RAC_LNAENPOL                   */
#define _RAC_CTRL_LNAENPOL_DEFAULT                                    0x00000000UL                              /**< Mode DEFAULT for RAC_CTRL                   */
#define _RAC_CTRL_LNAENPOL_X0                                         0x00000000UL                              /**< Mode X0 for RAC_CTRL                        */
#define _RAC_CTRL_LNAENPOL_X1                                         0x00000001UL                              /**< Mode X1 for RAC_CTRL                        */
#define RAC_CTRL_LNAENPOL_DEFAULT                                     (_RAC_CTRL_LNAENPOL_DEFAULT << 9)         /**< Shifted mode DEFAULT for RAC_CTRL           */
#define RAC_CTRL_LNAENPOL_X0                                          (_RAC_CTRL_LNAENPOL_X0 << 9)              /**< Shifted mode X0 for RAC_CTRL                */
#define RAC_CTRL_LNAENPOL_X1                                          (_RAC_CTRL_LNAENPOL_X1 << 9)              /**< Shifted mode X1 for RAC_CTRL                */
#define RAC_CTRL_PRSRXDIS                                             (0x1UL << 10)                             /**< PRS RX Disable                              */
#define _RAC_CTRL_PRSRXDIS_SHIFT                                      10                                        /**< Shift value for RAC_PRSRXDIS                */
#define _RAC_CTRL_PRSRXDIS_MASK                                       0x400UL                                   /**< Bit mask for RAC_PRSRXDIS                   */
#define _RAC_CTRL_PRSRXDIS_DEFAULT                                    0x00000000UL                              /**< Mode DEFAULT for RAC_CTRL                   */
#define _RAC_CTRL_PRSRXDIS_X0                                         0x00000000UL                              /**< Mode X0 for RAC_CTRL                        */
#define _RAC_CTRL_PRSRXDIS_X1                                         0x00000001UL                              /**< Mode X1 for RAC_CTRL                        */
#define RAC_CTRL_PRSRXDIS_DEFAULT                                     (_RAC_CTRL_PRSRXDIS_DEFAULT << 10)        /**< Shifted mode DEFAULT for RAC_CTRL           */
#define RAC_CTRL_PRSRXDIS_X0                                          (_RAC_CTRL_PRSRXDIS_X0 << 10)             /**< Shifted mode X0 for RAC_CTRL                */
#define RAC_CTRL_PRSRXDIS_X1                                          (_RAC_CTRL_PRSRXDIS_X1 << 10)             /**< Shifted mode X1 for RAC_CTRL                */
#define RAC_CTRL_PRSFORCETX                                           (0x1UL << 16)                             /**< PRS Force RX                                */
#define _RAC_CTRL_PRSFORCETX_SHIFT                                    16                                        /**< Shift value for RAC_PRSFORCETX              */
#define _RAC_CTRL_PRSFORCETX_MASK                                     0x10000UL                                 /**< Bit mask for RAC_PRSFORCETX                 */
#define _RAC_CTRL_PRSFORCETX_DEFAULT                                  0x00000000UL                              /**< Mode DEFAULT for RAC_CTRL                   */
#define _RAC_CTRL_PRSFORCETX_X0                                       0x00000000UL                              /**< Mode X0 for RAC_CTRL                        */
#define _RAC_CTRL_PRSFORCETX_X1                                       0x00000001UL                              /**< Mode X1 for RAC_CTRL                        */
#define RAC_CTRL_PRSFORCETX_DEFAULT                                   (_RAC_CTRL_PRSFORCETX_DEFAULT << 16)      /**< Shifted mode DEFAULT for RAC_CTRL           */
#define RAC_CTRL_PRSFORCETX_X0                                        (_RAC_CTRL_PRSFORCETX_X0 << 16)           /**< Shifted mode X0 for RAC_CTRL                */
#define RAC_CTRL_PRSFORCETX_X1                                        (_RAC_CTRL_PRSFORCETX_X1 << 16)           /**< Shifted mode X1 for RAC_CTRL                */
#define RAC_CTRL_SEQRESET                                             (0x1UL << 24)                             /**< SEQ reset                                   */
#define _RAC_CTRL_SEQRESET_SHIFT                                      24                                        /**< Shift value for RAC_SEQRESET                */
#define _RAC_CTRL_SEQRESET_MASK                                       0x1000000UL                               /**< Bit mask for RAC_SEQRESET                   */
#define _RAC_CTRL_SEQRESET_DEFAULT                                    0x00000000UL                              /**< Mode DEFAULT for RAC_CTRL                   */
#define RAC_CTRL_SEQRESET_DEFAULT                                     (_RAC_CTRL_SEQRESET_DEFAULT << 24)        /**< Shifted mode DEFAULT for RAC_CTRL           */
#define RAC_CTRL_EXITSHUTDOWNDIS                                      (0x1UL << 25)                             /**< Exit SHUTDOWN state Disable                 */
#define _RAC_CTRL_EXITSHUTDOWNDIS_SHIFT                               25                                        /**< Shift value for RAC_EXITSHUTDOWNDIS         */
#define _RAC_CTRL_EXITSHUTDOWNDIS_MASK                                0x2000000UL                               /**< Bit mask for RAC_EXITSHUTDOWNDIS            */
#define _RAC_CTRL_EXITSHUTDOWNDIS_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for RAC_CTRL                   */
#define RAC_CTRL_EXITSHUTDOWNDIS_DEFAULT                              (_RAC_CTRL_EXITSHUTDOWNDIS_DEFAULT << 25) /**< Shifted mode DEFAULT for RAC_CTRL           */
#define RAC_CTRL_CPUWAITDIS                                           (0x1UL << 26)                             /**< SEQ CPU Wait Disable                        */
#define _RAC_CTRL_CPUWAITDIS_SHIFT                                    26                                        /**< Shift value for RAC_CPUWAITDIS              */
#define _RAC_CTRL_CPUWAITDIS_MASK                                     0x4000000UL                               /**< Bit mask for RAC_CPUWAITDIS                 */
#define _RAC_CTRL_CPUWAITDIS_DEFAULT                                  0x00000000UL                              /**< Mode DEFAULT for RAC_CTRL                   */
#define RAC_CTRL_CPUWAITDIS_DEFAULT                                   (_RAC_CTRL_CPUWAITDIS_DEFAULT << 26)      /**< Shifted mode DEFAULT for RAC_CTRL           */
#define RAC_CTRL_SEQCLKDIS                                            (0x1UL << 27)                             /**< SEQ Clk Disable                             */
#define _RAC_CTRL_SEQCLKDIS_SHIFT                                     27                                        /**< Shift value for RAC_SEQCLKDIS               */
#define _RAC_CTRL_SEQCLKDIS_MASK                                      0x8000000UL                               /**< Bit mask for RAC_SEQCLKDIS                  */
#define _RAC_CTRL_SEQCLKDIS_DEFAULT                                   0x00000000UL                              /**< Mode DEFAULT for RAC_CTRL                   */
#define RAC_CTRL_SEQCLKDIS_DEFAULT                                    (_RAC_CTRL_SEQCLKDIS_DEFAULT << 27)       /**< Shifted mode DEFAULT for RAC_CTRL           */
#define RAC_CTRL_RXOFDIS                                              (0x1UL << 28)                             /**< Switch to RXOVERFLOW Disable                */
#define _RAC_CTRL_RXOFDIS_SHIFT                                       28                                        /**< Shift value for RAC_RXOFDIS                 */
#define _RAC_CTRL_RXOFDIS_MASK                                        0x10000000UL                              /**< Bit mask for RAC_RXOFDIS                    */
#define _RAC_CTRL_RXOFDIS_DEFAULT                                     0x00000000UL                              /**< Mode DEFAULT for RAC_CTRL                   */
#define RAC_CTRL_RXOFDIS_DEFAULT                                      (_RAC_CTRL_RXOFDIS_DEFAULT << 28)         /**< Shifted mode DEFAULT for RAC_CTRL           */

/* Bit fields for RAC FORCESTATE */
#define _RAC_FORCESTATE_RESETVALUE                                    0x00000000UL                              /**< Default value for RAC_FORCESTATE            */
#define _RAC_FORCESTATE_MASK                                          0x0000000FUL                              /**< Mask for RAC_FORCESTATE                     */
#define _RAC_FORCESTATE_FORCESTATE_SHIFT                              0                                         /**< Shift value for RAC_FORCESTATE              */
#define _RAC_FORCESTATE_FORCESTATE_MASK                               0xFUL                                     /**< Bit mask for RAC_FORCESTATE                 */
#define _RAC_FORCESTATE_FORCESTATE_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for RAC_FORCESTATE             */
#define RAC_FORCESTATE_FORCESTATE_DEFAULT                             (_RAC_FORCESTATE_FORCESTATE_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_FORCESTATE     */

/* Bit fields for RAC IF */
#define _RAC_IF_RESETVALUE                                            0x00000000UL                       /**< Default value for RAC_IF                    */
#define _RAC_IF_MASK                                                  0x00FF000FUL                       /**< Mask for RAC_IF                             */
#define RAC_IF_STATECHANGE                                            (0x1UL << 0)                       /**< Radio State Change                          */
#define _RAC_IF_STATECHANGE_SHIFT                                     0                                  /**< Shift value for RAC_STATECHANGE             */
#define _RAC_IF_STATECHANGE_MASK                                      0x1UL                              /**< Bit mask for RAC_STATECHANGE                */
#define _RAC_IF_STATECHANGE_DEFAULT                                   0x00000000UL                       /**< Mode DEFAULT for RAC_IF                     */
#define RAC_IF_STATECHANGE_DEFAULT                                    (_RAC_IF_STATECHANGE_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_IF             */
#define RAC_IF_STIMCMPEV                                              (0x1UL << 1)                       /**< STIMER Compare Event                        */
#define _RAC_IF_STIMCMPEV_SHIFT                                       1                                  /**< Shift value for RAC_STIMCMPEV               */
#define _RAC_IF_STIMCMPEV_MASK                                        0x2UL                              /**< Bit mask for RAC_STIMCMPEV                  */
#define _RAC_IF_STIMCMPEV_DEFAULT                                     0x00000000UL                       /**< Mode DEFAULT for RAC_IF                     */
#define RAC_IF_STIMCMPEV_DEFAULT                                      (_RAC_IF_STIMCMPEV_DEFAULT << 1)   /**< Shifted mode DEFAULT for RAC_IF             */
#define RAC_IF_SEQLOCKUP                                              (0x1UL << 2)                       /**< SEQ locked up                               */
#define _RAC_IF_SEQLOCKUP_SHIFT                                       2                                  /**< Shift value for RAC_SEQLOCKUP               */
#define _RAC_IF_SEQLOCKUP_MASK                                        0x4UL                              /**< Bit mask for RAC_SEQLOCKUP                  */
#define _RAC_IF_SEQLOCKUP_DEFAULT                                     0x00000000UL                       /**< Mode DEFAULT for RAC_IF                     */
#define RAC_IF_SEQLOCKUP_DEFAULT                                      (_RAC_IF_SEQLOCKUP_DEFAULT << 2)   /**< Shifted mode DEFAULT for RAC_IF             */
#define RAC_IF_SEQRESETREQ                                            (0x1UL << 3)                       /**< SEQ reset request                           */
#define _RAC_IF_SEQRESETREQ_SHIFT                                     3                                  /**< Shift value for RAC_SEQRESETREQ             */
#define _RAC_IF_SEQRESETREQ_MASK                                      0x8UL                              /**< Bit mask for RAC_SEQRESETREQ                */
#define _RAC_IF_SEQRESETREQ_DEFAULT                                   0x00000000UL                       /**< Mode DEFAULT for RAC_IF                     */
#define RAC_IF_SEQRESETREQ_DEFAULT                                    (_RAC_IF_SEQRESETREQ_DEFAULT << 3) /**< Shifted mode DEFAULT for RAC_IF             */
#define _RAC_IF_SEQ_SHIFT                                             16                                 /**< Shift value for RAC_SEQ                     */
#define _RAC_IF_SEQ_MASK                                              0xFF0000UL                         /**< Bit mask for RAC_SEQ                        */
#define _RAC_IF_SEQ_DEFAULT                                           0x00000000UL                       /**< Mode DEFAULT for RAC_IF                     */
#define RAC_IF_SEQ_DEFAULT                                            (_RAC_IF_SEQ_DEFAULT << 16)        /**< Shifted mode DEFAULT for RAC_IF             */

/* Bit fields for RAC IEN */
#define _RAC_IEN_RESETVALUE                                           0x00000000UL                        /**< Default value for RAC_IEN                   */
#define _RAC_IEN_MASK                                                 0x00FF000FUL                        /**< Mask for RAC_IEN                            */
#define RAC_IEN_STATECHANGE                                           (0x1UL << 0)                        /**< Radio State Change Interrupt Enable         */
#define _RAC_IEN_STATECHANGE_SHIFT                                    0                                   /**< Shift value for RAC_STATECHANGE             */
#define _RAC_IEN_STATECHANGE_MASK                                     0x1UL                               /**< Bit mask for RAC_STATECHANGE                */
#define _RAC_IEN_STATECHANGE_DEFAULT                                  0x00000000UL                        /**< Mode DEFAULT for RAC_IEN                    */
#define RAC_IEN_STATECHANGE_DEFAULT                                   (_RAC_IEN_STATECHANGE_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_IEN            */
#define RAC_IEN_STIMCMPEV                                             (0x1UL << 1)                        /**< STIMER Compare Event Interrupt Enable       */
#define _RAC_IEN_STIMCMPEV_SHIFT                                      1                                   /**< Shift value for RAC_STIMCMPEV               */
#define _RAC_IEN_STIMCMPEV_MASK                                       0x2UL                               /**< Bit mask for RAC_STIMCMPEV                  */
#define _RAC_IEN_STIMCMPEV_DEFAULT                                    0x00000000UL                        /**< Mode DEFAULT for RAC_IEN                    */
#define RAC_IEN_STIMCMPEV_DEFAULT                                     (_RAC_IEN_STIMCMPEV_DEFAULT << 1)   /**< Shifted mode DEFAULT for RAC_IEN            */
#define RAC_IEN_SEQLOCKUP                                             (0x1UL << 2)                        /**< SEQ locked up Interrupt Enable              */
#define _RAC_IEN_SEQLOCKUP_SHIFT                                      2                                   /**< Shift value for RAC_SEQLOCKUP               */
#define _RAC_IEN_SEQLOCKUP_MASK                                       0x4UL                               /**< Bit mask for RAC_SEQLOCKUP                  */
#define _RAC_IEN_SEQLOCKUP_DEFAULT                                    0x00000000UL                        /**< Mode DEFAULT for RAC_IEN                    */
#define RAC_IEN_SEQLOCKUP_DEFAULT                                     (_RAC_IEN_SEQLOCKUP_DEFAULT << 2)   /**< Shifted mode DEFAULT for RAC_IEN            */
#define RAC_IEN_SEQRESETREQ                                           (0x1UL << 3)                        /**< SEQ reset request Interrupt Enable          */
#define _RAC_IEN_SEQRESETREQ_SHIFT                                    3                                   /**< Shift value for RAC_SEQRESETREQ             */
#define _RAC_IEN_SEQRESETREQ_MASK                                     0x8UL                               /**< Bit mask for RAC_SEQRESETREQ                */
#define _RAC_IEN_SEQRESETREQ_DEFAULT                                  0x00000000UL                        /**< Mode DEFAULT for RAC_IEN                    */
#define RAC_IEN_SEQRESETREQ_DEFAULT                                   (_RAC_IEN_SEQRESETREQ_DEFAULT << 3) /**< Shifted mode DEFAULT for RAC_IEN            */
#define _RAC_IEN_SEQ_SHIFT                                            16                                  /**< Shift value for RAC_SEQ                     */
#define _RAC_IEN_SEQ_MASK                                             0xFF0000UL                          /**< Bit mask for RAC_SEQ                        */
#define _RAC_IEN_SEQ_DEFAULT                                          0x00000000UL                        /**< Mode DEFAULT for RAC_IEN                    */
#define RAC_IEN_SEQ_DEFAULT                                           (_RAC_IEN_SEQ_DEFAULT << 16)        /**< Shifted mode DEFAULT for RAC_IEN            */

/* Bit fields for RAC TESTCTRL */
#define _RAC_TESTCTRL_RESETVALUE                                      0x00000000UL                         /**< Default value for RAC_TESTCTRL              */
#define _RAC_TESTCTRL_MASK                                            0x00000003UL                         /**< Mask for RAC_TESTCTRL                       */
#define RAC_TESTCTRL_MODEN                                            (0x1UL << 0)                         /**< Modulator enable                            */
#define _RAC_TESTCTRL_MODEN_SHIFT                                     0                                    /**< Shift value for RAC_MODEN                   */
#define _RAC_TESTCTRL_MODEN_MASK                                      0x1UL                                /**< Bit mask for RAC_MODEN                      */
#define _RAC_TESTCTRL_MODEN_DEFAULT                                   0x00000000UL                         /**< Mode DEFAULT for RAC_TESTCTRL               */
#define RAC_TESTCTRL_MODEN_DEFAULT                                    (_RAC_TESTCTRL_MODEN_DEFAULT << 0)   /**< Shifted mode DEFAULT for RAC_TESTCTRL       */
#define RAC_TESTCTRL_DEMODEN                                          (0x1UL << 1)                         /**< Demodulator enable                          */
#define _RAC_TESTCTRL_DEMODEN_SHIFT                                   1                                    /**< Shift value for RAC_DEMODEN                 */
#define _RAC_TESTCTRL_DEMODEN_MASK                                    0x2UL                                /**< Bit mask for RAC_DEMODEN                    */
#define _RAC_TESTCTRL_DEMODEN_DEFAULT                                 0x00000000UL                         /**< Mode DEFAULT for RAC_TESTCTRL               */
#define RAC_TESTCTRL_DEMODEN_DEFAULT                                  (_RAC_TESTCTRL_DEMODEN_DEFAULT << 1) /**< Shifted mode DEFAULT for RAC_TESTCTRL       */

/* Bit fields for RAC SEQIF */
#define _RAC_SEQIF_RESETVALUE                                         0x00000000UL                               /**< Default value for RAC_SEQIF                 */
#define _RAC_SEQIF_MASK                                               0x3FFF000FUL                               /**< Mask for RAC_SEQIF                          */
#define RAC_SEQIF_STATECHANGESEQ                                      (0x1UL << 0)                               /**< Radio State Change                          */
#define _RAC_SEQIF_STATECHANGESEQ_SHIFT                               0                                          /**< Shift value for RAC_STATECHANGESEQ          */
#define _RAC_SEQIF_STATECHANGESEQ_MASK                                0x1UL                                      /**< Bit mask for RAC_STATECHANGESEQ             */
#define _RAC_SEQIF_STATECHANGESEQ_DEFAULT                             0x00000000UL                               /**< Mode DEFAULT for RAC_SEQIF                  */
#define RAC_SEQIF_STATECHANGESEQ_DEFAULT                              (_RAC_SEQIF_STATECHANGESEQ_DEFAULT << 0)   /**< Shifted mode DEFAULT for RAC_SEQIF          */
#define RAC_SEQIF_STIMCMPEVSEQ                                        (0x1UL << 1)                               /**< STIMER Compare Event                        */
#define _RAC_SEQIF_STIMCMPEVSEQ_SHIFT                                 1                                          /**< Shift value for RAC_STIMCMPEVSEQ            */
#define _RAC_SEQIF_STIMCMPEVSEQ_MASK                                  0x2UL                                      /**< Bit mask for RAC_STIMCMPEVSEQ               */
#define _RAC_SEQIF_STIMCMPEVSEQ_DEFAULT                               0x00000000UL                               /**< Mode DEFAULT for RAC_SEQIF                  */
#define RAC_SEQIF_STIMCMPEVSEQ_DEFAULT                                (_RAC_SEQIF_STIMCMPEVSEQ_DEFAULT << 1)     /**< Shifted mode DEFAULT for RAC_SEQIF          */
#define RAC_SEQIF_DEMODRXREQCLRSEQ                                    (0x1UL << 2)                               /**< Demod RX request clear                      */
#define _RAC_SEQIF_DEMODRXREQCLRSEQ_SHIFT                             2                                          /**< Shift value for RAC_DEMODRXREQCLRSEQ        */
#define _RAC_SEQIF_DEMODRXREQCLRSEQ_MASK                              0x4UL                                      /**< Bit mask for RAC_DEMODRXREQCLRSEQ           */
#define _RAC_SEQIF_DEMODRXREQCLRSEQ_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for RAC_SEQIF                  */
#define RAC_SEQIF_DEMODRXREQCLRSEQ_DEFAULT                            (_RAC_SEQIF_DEMODRXREQCLRSEQ_DEFAULT << 2) /**< Shifted mode DEFAULT for RAC_SEQIF          */
#define RAC_SEQIF_PRSEVENTSEQ                                         (0x1UL << 3)                               /**< SEQ PRS Event                               */
#define _RAC_SEQIF_PRSEVENTSEQ_SHIFT                                  3                                          /**< Shift value for RAC_PRSEVENTSEQ             */
#define _RAC_SEQIF_PRSEVENTSEQ_MASK                                   0x8UL                                      /**< Bit mask for RAC_PRSEVENTSEQ                */
#define _RAC_SEQIF_PRSEVENTSEQ_DEFAULT                                0x00000000UL                               /**< Mode DEFAULT for RAC_SEQIF                  */
#define RAC_SEQIF_PRSEVENTSEQ_DEFAULT                                 (_RAC_SEQIF_PRSEVENTSEQ_DEFAULT << 3)      /**< Shifted mode DEFAULT for RAC_SEQIF          */
#define RAC_SEQIF_STATEOFF                                            (0x1UL << 16)                              /**< entering STATE_OFF                          */
#define _RAC_SEQIF_STATEOFF_SHIFT                                     16                                         /**< Shift value for RAC_STATEOFF                */
#define _RAC_SEQIF_STATEOFF_MASK                                      0x10000UL                                  /**< Bit mask for RAC_STATEOFF                   */
#define _RAC_SEQIF_STATEOFF_DEFAULT                                   0x00000000UL                               /**< Mode DEFAULT for RAC_SEQIF                  */
#define RAC_SEQIF_STATEOFF_DEFAULT                                    (_RAC_SEQIF_STATEOFF_DEFAULT << 16)        /**< Shifted mode DEFAULT for RAC_SEQIF          */
#define RAC_SEQIF_STATERXWARM                                         (0x1UL << 17)                              /**< entering STATE_RXWARM                       */
#define _RAC_SEQIF_STATERXWARM_SHIFT                                  17                                         /**< Shift value for RAC_STATERXWARM             */
#define _RAC_SEQIF_STATERXWARM_MASK                                   0x20000UL                                  /**< Bit mask for RAC_STATERXWARM                */
#define _RAC_SEQIF_STATERXWARM_DEFAULT                                0x00000000UL                               /**< Mode DEFAULT for RAC_SEQIF                  */
#define RAC_SEQIF_STATERXWARM_DEFAULT                                 (_RAC_SEQIF_STATERXWARM_DEFAULT << 17)     /**< Shifted mode DEFAULT for RAC_SEQIF          */
#define RAC_SEQIF_STATERXSEARCH                                       (0x1UL << 18)                              /**< entering STATE_RXSEARCH                     */
#define _RAC_SEQIF_STATERXSEARCH_SHIFT                                18                                         /**< Shift value for RAC_STATERXSEARCH           */
#define _RAC_SEQIF_STATERXSEARCH_MASK                                 0x40000UL                                  /**< Bit mask for RAC_STATERXSEARCH              */
#define _RAC_SEQIF_STATERXSEARCH_DEFAULT                              0x00000000UL                               /**< Mode DEFAULT for RAC_SEQIF                  */
#define RAC_SEQIF_STATERXSEARCH_DEFAULT                               (_RAC_SEQIF_STATERXSEARCH_DEFAULT << 18)   /**< Shifted mode DEFAULT for RAC_SEQIF          */
#define RAC_SEQIF_STATERXFRAME                                        (0x1UL << 19)                              /**< entering STATE_RXFRAME                      */
#define _RAC_SEQIF_STATERXFRAME_SHIFT                                 19                                         /**< Shift value for RAC_STATERXFRAME            */
#define _RAC_SEQIF_STATERXFRAME_MASK                                  0x80000UL                                  /**< Bit mask for RAC_STATERXFRAME               */
#define _RAC_SEQIF_STATERXFRAME_DEFAULT                               0x00000000UL                               /**< Mode DEFAULT for RAC_SEQIF                  */
#define RAC_SEQIF_STATERXFRAME_DEFAULT                                (_RAC_SEQIF_STATERXFRAME_DEFAULT << 19)    /**< Shifted mode DEFAULT for RAC_SEQIF          */
#define RAC_SEQIF_STATERXPD                                           (0x1UL << 20)                              /**< entering STATE_RXPD                         */
#define _RAC_SEQIF_STATERXPD_SHIFT                                    20                                         /**< Shift value for RAC_STATERXPD               */
#define _RAC_SEQIF_STATERXPD_MASK                                     0x100000UL                                 /**< Bit mask for RAC_STATERXPD                  */
#define _RAC_SEQIF_STATERXPD_DEFAULT                                  0x00000000UL                               /**< Mode DEFAULT for RAC_SEQIF                  */
#define RAC_SEQIF_STATERXPD_DEFAULT                                   (_RAC_SEQIF_STATERXPD_DEFAULT << 20)       /**< Shifted mode DEFAULT for RAC_SEQIF          */
#define RAC_SEQIF_STATERX2RX                                          (0x1UL << 21)                              /**< entering STATE_RX2RX                        */
#define _RAC_SEQIF_STATERX2RX_SHIFT                                   21                                         /**< Shift value for RAC_STATERX2RX              */
#define _RAC_SEQIF_STATERX2RX_MASK                                    0x200000UL                                 /**< Bit mask for RAC_STATERX2RX                 */
#define _RAC_SEQIF_STATERX2RX_DEFAULT                                 0x00000000UL                               /**< Mode DEFAULT for RAC_SEQIF                  */
#define RAC_SEQIF_STATERX2RX_DEFAULT                                  (_RAC_SEQIF_STATERX2RX_DEFAULT << 21)      /**< Shifted mode DEFAULT for RAC_SEQIF          */
#define RAC_SEQIF_STATERXOVERFLOW                                     (0x1UL << 22)                              /**< entering STATE_RXOVERFLOW                   */
#define _RAC_SEQIF_STATERXOVERFLOW_SHIFT                              22                                         /**< Shift value for RAC_STATERXOVERFLOW         */
#define _RAC_SEQIF_STATERXOVERFLOW_MASK                               0x400000UL                                 /**< Bit mask for RAC_STATERXOVERFLOW            */
#define _RAC_SEQIF_STATERXOVERFLOW_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for RAC_SEQIF                  */
#define RAC_SEQIF_STATERXOVERFLOW_DEFAULT                             (_RAC_SEQIF_STATERXOVERFLOW_DEFAULT << 22) /**< Shifted mode DEFAULT for RAC_SEQIF          */
#define RAC_SEQIF_STATERX2TX                                          (0x1UL << 23)                              /**< entering STATE_RX2TX                        */
#define _RAC_SEQIF_STATERX2TX_SHIFT                                   23                                         /**< Shift value for RAC_STATERX2TX              */
#define _RAC_SEQIF_STATERX2TX_MASK                                    0x800000UL                                 /**< Bit mask for RAC_STATERX2TX                 */
#define _RAC_SEQIF_STATERX2TX_DEFAULT                                 0x00000000UL                               /**< Mode DEFAULT for RAC_SEQIF                  */
#define RAC_SEQIF_STATERX2TX_DEFAULT                                  (_RAC_SEQIF_STATERX2TX_DEFAULT << 23)      /**< Shifted mode DEFAULT for RAC_SEQIF          */
#define RAC_SEQIF_STATETXWARM                                         (0x1UL << 24)                              /**< entering STATE_TXWARM                       */
#define _RAC_SEQIF_STATETXWARM_SHIFT                                  24                                         /**< Shift value for RAC_STATETXWARM             */
#define _RAC_SEQIF_STATETXWARM_MASK                                   0x1000000UL                                /**< Bit mask for RAC_STATETXWARM                */
#define _RAC_SEQIF_STATETXWARM_DEFAULT                                0x00000000UL                               /**< Mode DEFAULT for RAC_SEQIF                  */
#define RAC_SEQIF_STATETXWARM_DEFAULT                                 (_RAC_SEQIF_STATETXWARM_DEFAULT << 24)     /**< Shifted mode DEFAULT for RAC_SEQIF          */
#define RAC_SEQIF_STATETX                                             (0x1UL << 25)                              /**< entering STATE_TX                           */
#define _RAC_SEQIF_STATETX_SHIFT                                      25                                         /**< Shift value for RAC_STATETX                 */
#define _RAC_SEQIF_STATETX_MASK                                       0x2000000UL                                /**< Bit mask for RAC_STATETX                    */
#define _RAC_SEQIF_STATETX_DEFAULT                                    0x00000000UL                               /**< Mode DEFAULT for RAC_SEQIF                  */
#define RAC_SEQIF_STATETX_DEFAULT                                     (_RAC_SEQIF_STATETX_DEFAULT << 25)         /**< Shifted mode DEFAULT for RAC_SEQIF          */
#define RAC_SEQIF_STATETXPD                                           (0x1UL << 26)                              /**< entering STATE_TXPD                         */
#define _RAC_SEQIF_STATETXPD_SHIFT                                    26                                         /**< Shift value for RAC_STATETXPD               */
#define _RAC_SEQIF_STATETXPD_MASK                                     0x4000000UL                                /**< Bit mask for RAC_STATETXPD                  */
#define _RAC_SEQIF_STATETXPD_DEFAULT                                  0x00000000UL                               /**< Mode DEFAULT for RAC_SEQIF                  */
#define RAC_SEQIF_STATETXPD_DEFAULT                                   (_RAC_SEQIF_STATETXPD_DEFAULT << 26)       /**< Shifted mode DEFAULT for RAC_SEQIF          */
#define RAC_SEQIF_STATETX2RX                                          (0x1UL << 27)                              /**< entering STATE_TX2RX                        */
#define _RAC_SEQIF_STATETX2RX_SHIFT                                   27                                         /**< Shift value for RAC_STATETX2RX              */
#define _RAC_SEQIF_STATETX2RX_MASK                                    0x8000000UL                                /**< Bit mask for RAC_STATETX2RX                 */
#define _RAC_SEQIF_STATETX2RX_DEFAULT                                 0x00000000UL                               /**< Mode DEFAULT for RAC_SEQIF                  */
#define RAC_SEQIF_STATETX2RX_DEFAULT                                  (_RAC_SEQIF_STATETX2RX_DEFAULT << 27)      /**< Shifted mode DEFAULT for RAC_SEQIF          */
#define RAC_SEQIF_STATETX2TX                                          (0x1UL << 28)                              /**< entering STATE_TX2TX                        */
#define _RAC_SEQIF_STATETX2TX_SHIFT                                   28                                         /**< Shift value for RAC_STATETX2TX              */
#define _RAC_SEQIF_STATETX2TX_MASK                                    0x10000000UL                               /**< Bit mask for RAC_STATETX2TX                 */
#define _RAC_SEQIF_STATETX2TX_DEFAULT                                 0x00000000UL                               /**< Mode DEFAULT for RAC_SEQIF                  */
#define RAC_SEQIF_STATETX2TX_DEFAULT                                  (_RAC_SEQIF_STATETX2TX_DEFAULT << 28)      /**< Shifted mode DEFAULT for RAC_SEQIF          */
#define RAC_SEQIF_STATESHUTDOWN                                       (0x1UL << 29)                              /**< entering STATE_SHUTDOWN                     */
#define _RAC_SEQIF_STATESHUTDOWN_SHIFT                                29                                         /**< Shift value for RAC_STATESHUTDOWN           */
#define _RAC_SEQIF_STATESHUTDOWN_MASK                                 0x20000000UL                               /**< Bit mask for RAC_STATESHUTDOWN              */
#define _RAC_SEQIF_STATESHUTDOWN_DEFAULT                              0x00000000UL                               /**< Mode DEFAULT for RAC_SEQIF                  */
#define RAC_SEQIF_STATESHUTDOWN_DEFAULT                               (_RAC_SEQIF_STATESHUTDOWN_DEFAULT << 29)   /**< Shifted mode DEFAULT for RAC_SEQIF          */

/* Bit fields for RAC SEQIEN */
#define _RAC_SEQIEN_RESETVALUE                                        0x00000000UL                                /**< Default value for RAC_SEQIEN                */
#define _RAC_SEQIEN_MASK                                              0x3FFF000FUL                                /**< Mask for RAC_SEQIEN                         */
#define RAC_SEQIEN_STATECHANGESEQ                                     (0x1UL << 0)                                /**< Radio State Change Interrupt Enable         */
#define _RAC_SEQIEN_STATECHANGESEQ_SHIFT                              0                                           /**< Shift value for RAC_STATECHANGESEQ          */
#define _RAC_SEQIEN_STATECHANGESEQ_MASK                               0x1UL                                       /**< Bit mask for RAC_STATECHANGESEQ             */
#define _RAC_SEQIEN_STATECHANGESEQ_DEFAULT                            0x00000000UL                                /**< Mode DEFAULT for RAC_SEQIEN                 */
#define RAC_SEQIEN_STATECHANGESEQ_DEFAULT                             (_RAC_SEQIEN_STATECHANGESEQ_DEFAULT << 0)   /**< Shifted mode DEFAULT for RAC_SEQIEN         */
#define RAC_SEQIEN_STIMCMPEVSEQ                                       (0x1UL << 1)                                /**< STIMER Compare Event Interrupt Enable       */
#define _RAC_SEQIEN_STIMCMPEVSEQ_SHIFT                                1                                           /**< Shift value for RAC_STIMCMPEVSEQ            */
#define _RAC_SEQIEN_STIMCMPEVSEQ_MASK                                 0x2UL                                       /**< Bit mask for RAC_STIMCMPEVSEQ               */
#define _RAC_SEQIEN_STIMCMPEVSEQ_DEFAULT                              0x00000000UL                                /**< Mode DEFAULT for RAC_SEQIEN                 */
#define RAC_SEQIEN_STIMCMPEVSEQ_DEFAULT                               (_RAC_SEQIEN_STIMCMPEVSEQ_DEFAULT << 1)     /**< Shifted mode DEFAULT for RAC_SEQIEN         */
#define RAC_SEQIEN_DEMODRXREQCLRSEQ                                   (0x1UL << 2)                                /**< Demod RX req clr Interrupt Enable           */
#define _RAC_SEQIEN_DEMODRXREQCLRSEQ_SHIFT                            2                                           /**< Shift value for RAC_DEMODRXREQCLRSEQ        */
#define _RAC_SEQIEN_DEMODRXREQCLRSEQ_MASK                             0x4UL                                       /**< Bit mask for RAC_DEMODRXREQCLRSEQ           */
#define _RAC_SEQIEN_DEMODRXREQCLRSEQ_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for RAC_SEQIEN                 */
#define RAC_SEQIEN_DEMODRXREQCLRSEQ_DEFAULT                           (_RAC_SEQIEN_DEMODRXREQCLRSEQ_DEFAULT << 2) /**< Shifted mode DEFAULT for RAC_SEQIEN         */
#define RAC_SEQIEN_PRSEVENTSEQ                                        (0x1UL << 3)                                /**< PRS SEQ EVENT Interrupt Enable              */
#define _RAC_SEQIEN_PRSEVENTSEQ_SHIFT                                 3                                           /**< Shift value for RAC_PRSEVENTSEQ             */
#define _RAC_SEQIEN_PRSEVENTSEQ_MASK                                  0x8UL                                       /**< Bit mask for RAC_PRSEVENTSEQ                */
#define _RAC_SEQIEN_PRSEVENTSEQ_DEFAULT                               0x00000000UL                                /**< Mode DEFAULT for RAC_SEQIEN                 */
#define RAC_SEQIEN_PRSEVENTSEQ_DEFAULT                                (_RAC_SEQIEN_PRSEVENTSEQ_DEFAULT << 3)      /**< Shifted mode DEFAULT for RAC_SEQIEN         */
#define RAC_SEQIEN_STATEOFF                                           (0x1UL << 16)                               /**< STATE_OFF Interrupt Enable                  */
#define _RAC_SEQIEN_STATEOFF_SHIFT                                    16                                          /**< Shift value for RAC_STATEOFF                */
#define _RAC_SEQIEN_STATEOFF_MASK                                     0x10000UL                                   /**< Bit mask for RAC_STATEOFF                   */
#define _RAC_SEQIEN_STATEOFF_DEFAULT                                  0x00000000UL                                /**< Mode DEFAULT for RAC_SEQIEN                 */
#define RAC_SEQIEN_STATEOFF_DEFAULT                                   (_RAC_SEQIEN_STATEOFF_DEFAULT << 16)        /**< Shifted mode DEFAULT for RAC_SEQIEN         */
#define RAC_SEQIEN_STATERXWARM                                        (0x1UL << 17)                               /**< STATE_RXWARM Interrupt Enable               */
#define _RAC_SEQIEN_STATERXWARM_SHIFT                                 17                                          /**< Shift value for RAC_STATERXWARM             */
#define _RAC_SEQIEN_STATERXWARM_MASK                                  0x20000UL                                   /**< Bit mask for RAC_STATERXWARM                */
#define _RAC_SEQIEN_STATERXWARM_DEFAULT                               0x00000000UL                                /**< Mode DEFAULT for RAC_SEQIEN                 */
#define RAC_SEQIEN_STATERXWARM_DEFAULT                                (_RAC_SEQIEN_STATERXWARM_DEFAULT << 17)     /**< Shifted mode DEFAULT for RAC_SEQIEN         */
#define RAC_SEQIEN_STATERXSEARCH                                      (0x1UL << 18)                               /**< STATE_RXSEARC Interrupt Enable              */
#define _RAC_SEQIEN_STATERXSEARCH_SHIFT                               18                                          /**< Shift value for RAC_STATERXSEARCH           */
#define _RAC_SEQIEN_STATERXSEARCH_MASK                                0x40000UL                                   /**< Bit mask for RAC_STATERXSEARCH              */
#define _RAC_SEQIEN_STATERXSEARCH_DEFAULT                             0x00000000UL                                /**< Mode DEFAULT for RAC_SEQIEN                 */
#define RAC_SEQIEN_STATERXSEARCH_DEFAULT                              (_RAC_SEQIEN_STATERXSEARCH_DEFAULT << 18)   /**< Shifted mode DEFAULT for RAC_SEQIEN         */
#define RAC_SEQIEN_STATERXFRAME                                       (0x1UL << 19)                               /**< STATE_RXFRAME Interrupt Enable              */
#define _RAC_SEQIEN_STATERXFRAME_SHIFT                                19                                          /**< Shift value for RAC_STATERXFRAME            */
#define _RAC_SEQIEN_STATERXFRAME_MASK                                 0x80000UL                                   /**< Bit mask for RAC_STATERXFRAME               */
#define _RAC_SEQIEN_STATERXFRAME_DEFAULT                              0x00000000UL                                /**< Mode DEFAULT for RAC_SEQIEN                 */
#define RAC_SEQIEN_STATERXFRAME_DEFAULT                               (_RAC_SEQIEN_STATERXFRAME_DEFAULT << 19)    /**< Shifted mode DEFAULT for RAC_SEQIEN         */
#define RAC_SEQIEN_STATERXPD                                          (0x1UL << 20)                               /**< STATE_RXPD Interrupt Enable                 */
#define _RAC_SEQIEN_STATERXPD_SHIFT                                   20                                          /**< Shift value for RAC_STATERXPD               */
#define _RAC_SEQIEN_STATERXPD_MASK                                    0x100000UL                                  /**< Bit mask for RAC_STATERXPD                  */
#define _RAC_SEQIEN_STATERXPD_DEFAULT                                 0x00000000UL                                /**< Mode DEFAULT for RAC_SEQIEN                 */
#define RAC_SEQIEN_STATERXPD_DEFAULT                                  (_RAC_SEQIEN_STATERXPD_DEFAULT << 20)       /**< Shifted mode DEFAULT for RAC_SEQIEN         */
#define RAC_SEQIEN_STATERX2RX                                         (0x1UL << 21)                               /**< STATE_RX2RX Interrupt Enable                */
#define _RAC_SEQIEN_STATERX2RX_SHIFT                                  21                                          /**< Shift value for RAC_STATERX2RX              */
#define _RAC_SEQIEN_STATERX2RX_MASK                                   0x200000UL                                  /**< Bit mask for RAC_STATERX2RX                 */
#define _RAC_SEQIEN_STATERX2RX_DEFAULT                                0x00000000UL                                /**< Mode DEFAULT for RAC_SEQIEN                 */
#define RAC_SEQIEN_STATERX2RX_DEFAULT                                 (_RAC_SEQIEN_STATERX2RX_DEFAULT << 21)      /**< Shifted mode DEFAULT for RAC_SEQIEN         */
#define RAC_SEQIEN_STATERXOVERFLOW                                    (0x1UL << 22)                               /**< STATE_RXOVERFLOW Interrupt Enable           */
#define _RAC_SEQIEN_STATERXOVERFLOW_SHIFT                             22                                          /**< Shift value for RAC_STATERXOVERFLOW         */
#define _RAC_SEQIEN_STATERXOVERFLOW_MASK                              0x400000UL                                  /**< Bit mask for RAC_STATERXOVERFLOW            */
#define _RAC_SEQIEN_STATERXOVERFLOW_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for RAC_SEQIEN                 */
#define RAC_SEQIEN_STATERXOVERFLOW_DEFAULT                            (_RAC_SEQIEN_STATERXOVERFLOW_DEFAULT << 22) /**< Shifted mode DEFAULT for RAC_SEQIEN         */
#define RAC_SEQIEN_STATERX2TX                                         (0x1UL << 23)                               /**< STATE_RX2TX Interrupt Enable                */
#define _RAC_SEQIEN_STATERX2TX_SHIFT                                  23                                          /**< Shift value for RAC_STATERX2TX              */
#define _RAC_SEQIEN_STATERX2TX_MASK                                   0x800000UL                                  /**< Bit mask for RAC_STATERX2TX                 */
#define _RAC_SEQIEN_STATERX2TX_DEFAULT                                0x00000000UL                                /**< Mode DEFAULT for RAC_SEQIEN                 */
#define RAC_SEQIEN_STATERX2TX_DEFAULT                                 (_RAC_SEQIEN_STATERX2TX_DEFAULT << 23)      /**< Shifted mode DEFAULT for RAC_SEQIEN         */
#define RAC_SEQIEN_STATETXWARM                                        (0x1UL << 24)                               /**< STATE_TXWARM Interrupt Enable               */
#define _RAC_SEQIEN_STATETXWARM_SHIFT                                 24                                          /**< Shift value for RAC_STATETXWARM             */
#define _RAC_SEQIEN_STATETXWARM_MASK                                  0x1000000UL                                 /**< Bit mask for RAC_STATETXWARM                */
#define _RAC_SEQIEN_STATETXWARM_DEFAULT                               0x00000000UL                                /**< Mode DEFAULT for RAC_SEQIEN                 */
#define RAC_SEQIEN_STATETXWARM_DEFAULT                                (_RAC_SEQIEN_STATETXWARM_DEFAULT << 24)     /**< Shifted mode DEFAULT for RAC_SEQIEN         */
#define RAC_SEQIEN_STATETX                                            (0x1UL << 25)                               /**< STATE_TX Interrupt Enable                   */
#define _RAC_SEQIEN_STATETX_SHIFT                                     25                                          /**< Shift value for RAC_STATETX                 */
#define _RAC_SEQIEN_STATETX_MASK                                      0x2000000UL                                 /**< Bit mask for RAC_STATETX                    */
#define _RAC_SEQIEN_STATETX_DEFAULT                                   0x00000000UL                                /**< Mode DEFAULT for RAC_SEQIEN                 */
#define RAC_SEQIEN_STATETX_DEFAULT                                    (_RAC_SEQIEN_STATETX_DEFAULT << 25)         /**< Shifted mode DEFAULT for RAC_SEQIEN         */
#define RAC_SEQIEN_STATETXPD                                          (0x1UL << 26)                               /**< STATE_TXPD Interrupt Enable                 */
#define _RAC_SEQIEN_STATETXPD_SHIFT                                   26                                          /**< Shift value for RAC_STATETXPD               */
#define _RAC_SEQIEN_STATETXPD_MASK                                    0x4000000UL                                 /**< Bit mask for RAC_STATETXPD                  */
#define _RAC_SEQIEN_STATETXPD_DEFAULT                                 0x00000000UL                                /**< Mode DEFAULT for RAC_SEQIEN                 */
#define RAC_SEQIEN_STATETXPD_DEFAULT                                  (_RAC_SEQIEN_STATETXPD_DEFAULT << 26)       /**< Shifted mode DEFAULT for RAC_SEQIEN         */
#define RAC_SEQIEN_STATETX2RX                                         (0x1UL << 27)                               /**< STATE_TX2RX Interrupt Enable                */
#define _RAC_SEQIEN_STATETX2RX_SHIFT                                  27                                          /**< Shift value for RAC_STATETX2RX              */
#define _RAC_SEQIEN_STATETX2RX_MASK                                   0x8000000UL                                 /**< Bit mask for RAC_STATETX2RX                 */
#define _RAC_SEQIEN_STATETX2RX_DEFAULT                                0x00000000UL                                /**< Mode DEFAULT for RAC_SEQIEN                 */
#define RAC_SEQIEN_STATETX2RX_DEFAULT                                 (_RAC_SEQIEN_STATETX2RX_DEFAULT << 27)      /**< Shifted mode DEFAULT for RAC_SEQIEN         */
#define RAC_SEQIEN_STATETX2TX                                         (0x1UL << 28)                               /**< STATE_TX2TX Interrupt Enable                */
#define _RAC_SEQIEN_STATETX2TX_SHIFT                                  28                                          /**< Shift value for RAC_STATETX2TX              */
#define _RAC_SEQIEN_STATETX2TX_MASK                                   0x10000000UL                                /**< Bit mask for RAC_STATETX2TX                 */
#define _RAC_SEQIEN_STATETX2TX_DEFAULT                                0x00000000UL                                /**< Mode DEFAULT for RAC_SEQIEN                 */
#define RAC_SEQIEN_STATETX2TX_DEFAULT                                 (_RAC_SEQIEN_STATETX2TX_DEFAULT << 28)      /**< Shifted mode DEFAULT for RAC_SEQIEN         */
#define RAC_SEQIEN_STATESHUTDOWN                                      (0x1UL << 29)                               /**< STATE_SHUTDOWN Interrupt Enable             */
#define _RAC_SEQIEN_STATESHUTDOWN_SHIFT                               29                                          /**< Shift value for RAC_STATESHUTDOWN           */
#define _RAC_SEQIEN_STATESHUTDOWN_MASK                                0x20000000UL                                /**< Bit mask for RAC_STATESHUTDOWN              */
#define _RAC_SEQIEN_STATESHUTDOWN_DEFAULT                             0x00000000UL                                /**< Mode DEFAULT for RAC_SEQIEN                 */
#define RAC_SEQIEN_STATESHUTDOWN_DEFAULT                              (_RAC_SEQIEN_STATESHUTDOWN_DEFAULT << 29)   /**< Shifted mode DEFAULT for RAC_SEQIEN         */

/* Bit fields for RAC STATUS1 */
#define _RAC_STATUS1_RESETVALUE                                       0x00000000UL                       /**< Default value for RAC_STATUS1               */
#define _RAC_STATUS1_MASK                                             0x000000FFUL                       /**< Mask for RAC_STATUS1                        */
#define _RAC_STATUS1_TXMASK_SHIFT                                     0                                  /**< Shift value for RAC_TXMASK                  */
#define _RAC_STATUS1_TXMASK_MASK                                      0xFFUL                             /**< Bit mask for RAC_TXMASK                     */
#define _RAC_STATUS1_TXMASK_DEFAULT                                   0x00000000UL                       /**< Mode DEFAULT for RAC_STATUS1                */
#define RAC_STATUS1_TXMASK_DEFAULT                                    (_RAC_STATUS1_TXMASK_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_STATUS1        */

/* Bit fields for RAC STIMER */
#define _RAC_STIMER_RESETVALUE                                        0x00000000UL                      /**< Default value for RAC_STIMER                */
#define _RAC_STIMER_MASK                                              0x0000FFFFUL                      /**< Mask for RAC_STIMER                         */
#define _RAC_STIMER_STIMER_SHIFT                                      0                                 /**< Shift value for RAC_STIMER                  */
#define _RAC_STIMER_STIMER_MASK                                       0xFFFFUL                          /**< Bit mask for RAC_STIMER                     */
#define _RAC_STIMER_STIMER_DEFAULT                                    0x00000000UL                      /**< Mode DEFAULT for RAC_STIMER                 */
#define RAC_STIMER_STIMER_DEFAULT                                     (_RAC_STIMER_STIMER_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_STIMER         */

/* Bit fields for RAC STIMERCOMP */
#define _RAC_STIMERCOMP_RESETVALUE                                    0x00000000UL                              /**< Default value for RAC_STIMERCOMP            */
#define _RAC_STIMERCOMP_MASK                                          0x0000FFFFUL                              /**< Mask for RAC_STIMERCOMP                     */
#define _RAC_STIMERCOMP_STIMERCOMP_SHIFT                              0                                         /**< Shift value for RAC_STIMERCOMP              */
#define _RAC_STIMERCOMP_STIMERCOMP_MASK                               0xFFFFUL                                  /**< Bit mask for RAC_STIMERCOMP                 */
#define _RAC_STIMERCOMP_STIMERCOMP_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for RAC_STIMERCOMP             */
#define RAC_STIMERCOMP_STIMERCOMP_DEFAULT                             (_RAC_STIMERCOMP_STIMERCOMP_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_STIMERCOMP     */

/* Bit fields for RAC SEQCTRL */
#define _RAC_SEQCTRL_RESETVALUE                                       0x00000000UL                                  /**< Default value for RAC_SEQCTRL               */
#define _RAC_SEQCTRL_MASK                                             0x0300007FUL                                  /**< Mask for RAC_SEQCTRL                        */
#define RAC_SEQCTRL_COMPACT                                           (0x1UL << 0)                                  /**< STIMER Compare Action                       */
#define _RAC_SEQCTRL_COMPACT_SHIFT                                    0                                             /**< Shift value for RAC_COMPACT                 */
#define _RAC_SEQCTRL_COMPACT_MASK                                     0x1UL                                         /**< Bit mask for RAC_COMPACT                    */
#define _RAC_SEQCTRL_COMPACT_DEFAULT                                  0x00000000UL                                  /**< Mode DEFAULT for RAC_SEQCTRL                */
#define _RAC_SEQCTRL_COMPACT_WRAP                                     0x00000000UL                                  /**< Mode WRAP for RAC_SEQCTRL                   */
#define _RAC_SEQCTRL_COMPACT_CONTINUE                                 0x00000001UL                                  /**< Mode CONTINUE for RAC_SEQCTRL               */
#define RAC_SEQCTRL_COMPACT_DEFAULT                                   (_RAC_SEQCTRL_COMPACT_DEFAULT << 0)           /**< Shifted mode DEFAULT for RAC_SEQCTRL        */
#define RAC_SEQCTRL_COMPACT_WRAP                                      (_RAC_SEQCTRL_COMPACT_WRAP << 0)              /**< Shifted mode WRAP for RAC_SEQCTRL           */
#define RAC_SEQCTRL_COMPACT_CONTINUE                                  (_RAC_SEQCTRL_COMPACT_CONTINUE << 0)          /**< Shifted mode CONTINUE for RAC_SEQCTRL       */
#define _RAC_SEQCTRL_COMPINVALMODE_SHIFT                              1                                             /**< Shift value for RAC_COMPINVALMODE           */
#define _RAC_SEQCTRL_COMPINVALMODE_MASK                               0x6UL                                         /**< Bit mask for RAC_COMPINVALMODE              */
#define _RAC_SEQCTRL_COMPINVALMODE_DEFAULT                            0x00000000UL                                  /**< Mode DEFAULT for RAC_SEQCTRL                */
#define _RAC_SEQCTRL_COMPINVALMODE_NEVER                              0x00000000UL                                  /**< Mode NEVER for RAC_SEQCTRL                  */
#define _RAC_SEQCTRL_COMPINVALMODE_STATECHANGE                        0x00000001UL                                  /**< Mode STATECHANGE for RAC_SEQCTRL            */
#define _RAC_SEQCTRL_COMPINVALMODE_COMPEVENT                          0x00000002UL                                  /**< Mode COMPEVENT for RAC_SEQCTRL              */
#define _RAC_SEQCTRL_COMPINVALMODE_STATECOMP                          0x00000003UL                                  /**< Mode STATECOMP for RAC_SEQCTRL              */
#define RAC_SEQCTRL_COMPINVALMODE_DEFAULT                             (_RAC_SEQCTRL_COMPINVALMODE_DEFAULT << 1)     /**< Shifted mode DEFAULT for RAC_SEQCTRL        */
#define RAC_SEQCTRL_COMPINVALMODE_NEVER                               (_RAC_SEQCTRL_COMPINVALMODE_NEVER << 1)       /**< Shifted mode NEVER for RAC_SEQCTRL          */
#define RAC_SEQCTRL_COMPINVALMODE_STATECHANGE                         (_RAC_SEQCTRL_COMPINVALMODE_STATECHANGE << 1) /**< Shifted mode STATECHANGE for RAC_SEQCTRL    */
#define RAC_SEQCTRL_COMPINVALMODE_COMPEVENT                           (_RAC_SEQCTRL_COMPINVALMODE_COMPEVENT << 1)   /**< Shifted mode COMPEVENT for RAC_SEQCTRL      */
#define RAC_SEQCTRL_COMPINVALMODE_STATECOMP                           (_RAC_SEQCTRL_COMPINVALMODE_STATECOMP << 1)   /**< Shifted mode STATECOMP for RAC_SEQCTRL      */
#define RAC_SEQCTRL_RELATIVE                                          (0x1UL << 3)                                  /**< STIMER Compare value relative               */
#define _RAC_SEQCTRL_RELATIVE_SHIFT                                   3                                             /**< Shift value for RAC_RELATIVE                */
#define _RAC_SEQCTRL_RELATIVE_MASK                                    0x8UL                                         /**< Bit mask for RAC_RELATIVE                   */
#define _RAC_SEQCTRL_RELATIVE_DEFAULT                                 0x00000000UL                                  /**< Mode DEFAULT for RAC_SEQCTRL                */
#define _RAC_SEQCTRL_RELATIVE_Absolute                                0x00000000UL                                  /**< Mode Absolute for RAC_SEQCTRL               */
#define _RAC_SEQCTRL_RELATIVE_Relative                                0x00000001UL                                  /**< Mode Relative for RAC_SEQCTRL               */
#define RAC_SEQCTRL_RELATIVE_DEFAULT                                  (_RAC_SEQCTRL_RELATIVE_DEFAULT << 3)          /**< Shifted mode DEFAULT for RAC_SEQCTRL        */
#define RAC_SEQCTRL_RELATIVE_Absolute                                 (_RAC_SEQCTRL_RELATIVE_Absolute << 3)         /**< Shifted mode Absolute for RAC_SEQCTRL       */
#define RAC_SEQCTRL_RELATIVE_Relative                                 (_RAC_SEQCTRL_RELATIVE_Relative << 3)         /**< Shifted mode Relative for RAC_SEQCTRL       */
#define RAC_SEQCTRL_STIMERALWAYSRUN                                   (0x1UL << 4)                                  /**< STIMER always Run                           */
#define _RAC_SEQCTRL_STIMERALWAYSRUN_SHIFT                            4                                             /**< Shift value for RAC_STIMERALWAYSRUN         */
#define _RAC_SEQCTRL_STIMERALWAYSRUN_MASK                             0x10UL                                        /**< Bit mask for RAC_STIMERALWAYSRUN            */
#define _RAC_SEQCTRL_STIMERALWAYSRUN_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for RAC_SEQCTRL                */
#define RAC_SEQCTRL_STIMERALWAYSRUN_DEFAULT                           (_RAC_SEQCTRL_STIMERALWAYSRUN_DEFAULT << 4)   /**< Shifted mode DEFAULT for RAC_SEQCTRL        */
#define RAC_SEQCTRL_STIMERDEBUGRUN                                    (0x1UL << 5)                                  /**< STIMER Debug Run                            */
#define _RAC_SEQCTRL_STIMERDEBUGRUN_SHIFT                             5                                             /**< Shift value for RAC_STIMERDEBUGRUN          */
#define _RAC_SEQCTRL_STIMERDEBUGRUN_MASK                              0x20UL                                        /**< Bit mask for RAC_STIMERDEBUGRUN             */
#define _RAC_SEQCTRL_STIMERDEBUGRUN_DEFAULT                           0x00000000UL                                  /**< Mode DEFAULT for RAC_SEQCTRL                */
#define _RAC_SEQCTRL_STIMERDEBUGRUN_X0                                0x00000000UL                                  /**< Mode X0 for RAC_SEQCTRL                     */
#define _RAC_SEQCTRL_STIMERDEBUGRUN_X1                                0x00000001UL                                  /**< Mode X1 for RAC_SEQCTRL                     */
#define RAC_SEQCTRL_STIMERDEBUGRUN_DEFAULT                            (_RAC_SEQCTRL_STIMERDEBUGRUN_DEFAULT << 5)    /**< Shifted mode DEFAULT for RAC_SEQCTRL        */
#define RAC_SEQCTRL_STIMERDEBUGRUN_X0                                 (_RAC_SEQCTRL_STIMERDEBUGRUN_X0 << 5)         /**< Shifted mode X0 for RAC_SEQCTRL             */
#define RAC_SEQCTRL_STIMERDEBUGRUN_X1                                 (_RAC_SEQCTRL_STIMERDEBUGRUN_X1 << 5)         /**< Shifted mode X1 for RAC_SEQCTRL             */
#define RAC_SEQCTRL_STATEDEBUGRUN                                     (0x1UL << 6)                                  /**< FSM state Debug Run                         */
#define _RAC_SEQCTRL_STATEDEBUGRUN_SHIFT                              6                                             /**< Shift value for RAC_STATEDEBUGRUN           */
#define _RAC_SEQCTRL_STATEDEBUGRUN_MASK                               0x40UL                                        /**< Bit mask for RAC_STATEDEBUGRUN              */
#define _RAC_SEQCTRL_STATEDEBUGRUN_DEFAULT                            0x00000000UL                                  /**< Mode DEFAULT for RAC_SEQCTRL                */
#define _RAC_SEQCTRL_STATEDEBUGRUN_X0                                 0x00000000UL                                  /**< Mode X0 for RAC_SEQCTRL                     */
#define _RAC_SEQCTRL_STATEDEBUGRUN_X1                                 0x00000001UL                                  /**< Mode X1 for RAC_SEQCTRL                     */
#define RAC_SEQCTRL_STATEDEBUGRUN_DEFAULT                             (_RAC_SEQCTRL_STATEDEBUGRUN_DEFAULT << 6)     /**< Shifted mode DEFAULT for RAC_SEQCTRL        */
#define RAC_SEQCTRL_STATEDEBUGRUN_X0                                  (_RAC_SEQCTRL_STATEDEBUGRUN_X0 << 6)          /**< Shifted mode X0 for RAC_SEQCTRL             */
#define RAC_SEQCTRL_STATEDEBUGRUN_X1                                  (_RAC_SEQCTRL_STATEDEBUGRUN_X1 << 6)          /**< Shifted mode X1 for RAC_SEQCTRL             */
#define _RAC_SEQCTRL_SWIRQ_SHIFT                                      24                                            /**< Shift value for RAC_SWIRQ                   */
#define _RAC_SEQCTRL_SWIRQ_MASK                                       0x3000000UL                                   /**< Bit mask for RAC_SWIRQ                      */
#define _RAC_SEQCTRL_SWIRQ_DEFAULT                                    0x00000000UL                                  /**< Mode DEFAULT for RAC_SEQCTRL                */
#define RAC_SEQCTRL_SWIRQ_DEFAULT                                     (_RAC_SEQCTRL_SWIRQ_DEFAULT << 24)            /**< Shifted mode DEFAULT for RAC_SEQCTRL        */

/* Bit fields for RAC PRESC */
#define _RAC_PRESC_RESETVALUE                                         0x00000007UL                     /**< Default value for RAC_PRESC                 */
#define _RAC_PRESC_MASK                                               0x0000007FUL                     /**< Mask for RAC_PRESC                          */
#define _RAC_PRESC_STIMER_SHIFT                                       0                                /**< Shift value for RAC_STIMER                  */
#define _RAC_PRESC_STIMER_MASK                                        0x7FUL                           /**< Bit mask for RAC_STIMER                     */
#define _RAC_PRESC_STIMER_DEFAULT                                     0x00000007UL                     /**< Mode DEFAULT for RAC_PRESC                  */
#define RAC_PRESC_STIMER_DEFAULT                                      (_RAC_PRESC_STIMER_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_PRESC          */

/* Bit fields for RAC SR0 */
#define _RAC_SR0_RESETVALUE                                           0x00000000UL                /**< Default value for RAC_SR0                   */
#define _RAC_SR0_MASK                                                 0xFFFFFFFFUL                /**< Mask for RAC_SR0                            */
#define _RAC_SR0_SR0_SHIFT                                            0                           /**< Shift value for RAC_SR0                     */
#define _RAC_SR0_SR0_MASK                                             0xFFFFFFFFUL                /**< Bit mask for RAC_SR0                        */
#define _RAC_SR0_SR0_DEFAULT                                          0x00000000UL                /**< Mode DEFAULT for RAC_SR0                    */
#define RAC_SR0_SR0_DEFAULT                                           (_RAC_SR0_SR0_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_SR0            */

/* Bit fields for RAC SR1 */
#define _RAC_SR1_RESETVALUE                                           0x00000000UL                /**< Default value for RAC_SR1                   */
#define _RAC_SR1_MASK                                                 0xFFFFFFFFUL                /**< Mask for RAC_SR1                            */
#define _RAC_SR1_SR1_SHIFT                                            0                           /**< Shift value for RAC_SR1                     */
#define _RAC_SR1_SR1_MASK                                             0xFFFFFFFFUL                /**< Bit mask for RAC_SR1                        */
#define _RAC_SR1_SR1_DEFAULT                                          0x00000000UL                /**< Mode DEFAULT for RAC_SR1                    */
#define RAC_SR1_SR1_DEFAULT                                           (_RAC_SR1_SR1_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_SR1            */

/* Bit fields for RAC SR2 */
#define _RAC_SR2_RESETVALUE                                           0x00000000UL                /**< Default value for RAC_SR2                   */
#define _RAC_SR2_MASK                                                 0xFFFFFFFFUL                /**< Mask for RAC_SR2                            */
#define _RAC_SR2_SR2_SHIFT                                            0                           /**< Shift value for RAC_SR2                     */
#define _RAC_SR2_SR2_MASK                                             0xFFFFFFFFUL                /**< Bit mask for RAC_SR2                        */
#define _RAC_SR2_SR2_DEFAULT                                          0x00000000UL                /**< Mode DEFAULT for RAC_SR2                    */
#define RAC_SR2_SR2_DEFAULT                                           (_RAC_SR2_SR2_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_SR2            */

/* Bit fields for RAC SR3 */
#define _RAC_SR3_RESETVALUE                                           0x00000000UL                /**< Default value for RAC_SR3                   */
#define _RAC_SR3_MASK                                                 0xFFFFFFFFUL                /**< Mask for RAC_SR3                            */
#define _RAC_SR3_SR3_SHIFT                                            0                           /**< Shift value for RAC_SR3                     */
#define _RAC_SR3_SR3_MASK                                             0xFFFFFFFFUL                /**< Bit mask for RAC_SR3                        */
#define _RAC_SR3_SR3_DEFAULT                                          0x00000000UL                /**< Mode DEFAULT for RAC_SR3                    */
#define RAC_SR3_SR3_DEFAULT                                           (_RAC_SR3_SR3_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_SR3            */

/* Bit fields for RAC STCTRL */
#define _RAC_STCTRL_RESETVALUE                                        0x00000000UL                       /**< Default value for RAC_STCTRL                */
#define _RAC_STCTRL_MASK                                              0x01FFFFFFUL                       /**< Mask for RAC_STCTRL                         */
#define _RAC_STCTRL_STCAL_SHIFT                                       0                                  /**< Shift value for RAC_STCAL                   */
#define _RAC_STCTRL_STCAL_MASK                                        0xFFFFFFUL                         /**< Bit mask for RAC_STCAL                      */
#define _RAC_STCTRL_STCAL_DEFAULT                                     0x00000000UL                       /**< Mode DEFAULT for RAC_STCTRL                 */
#define RAC_STCTRL_STCAL_DEFAULT                                      (_RAC_STCTRL_STCAL_DEFAULT << 0)   /**< Shifted mode DEFAULT for RAC_STCTRL         */
#define RAC_STCTRL_STSKEW                                             (0x1UL << 24)                      /**< Systick timer skew                          */
#define _RAC_STCTRL_STSKEW_SHIFT                                      24                                 /**< Shift value for RAC_STSKEW                  */
#define _RAC_STCTRL_STSKEW_MASK                                       0x1000000UL                        /**< Bit mask for RAC_STSKEW                     */
#define _RAC_STCTRL_STSKEW_DEFAULT                                    0x00000000UL                       /**< Mode DEFAULT for RAC_STCTRL                 */
#define RAC_STCTRL_STSKEW_DEFAULT                                     (_RAC_STCTRL_STSKEW_DEFAULT << 24) /**< Shifted mode DEFAULT for RAC_STCTRL         */

/* Bit fields for RAC FRCTXWORD */
#define _RAC_FRCTXWORD_RESETVALUE                                     0x00000000UL                        /**< Default value for RAC_FRCTXWORD             */
#define _RAC_FRCTXWORD_MASK                                           0x000000FFUL                        /**< Mask for RAC_FRCTXWORD                      */
#define _RAC_FRCTXWORD_WDATA_SHIFT                                    0                                   /**< Shift value for RAC_WDATA                   */
#define _RAC_FRCTXWORD_WDATA_MASK                                     0xFFUL                              /**< Bit mask for RAC_WDATA                      */
#define _RAC_FRCTXWORD_WDATA_DEFAULT                                  0x00000000UL                        /**< Mode DEFAULT for RAC_FRCTXWORD              */
#define RAC_FRCTXWORD_WDATA_DEFAULT                                   (_RAC_FRCTXWORD_WDATA_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_FRCTXWORD      */

/* Bit fields for RAC FRCRXWORD */
#define _RAC_FRCRXWORD_RESETVALUE                                     0x00000000UL                        /**< Default value for RAC_FRCRXWORD             */
#define _RAC_FRCRXWORD_MASK                                           0x000000FFUL                        /**< Mask for RAC_FRCRXWORD                      */
#define _RAC_FRCRXWORD_RDATA_SHIFT                                    0                                   /**< Shift value for RAC_RDATA                   */
#define _RAC_FRCRXWORD_RDATA_MASK                                     0xFFUL                              /**< Bit mask for RAC_RDATA                      */
#define _RAC_FRCRXWORD_RDATA_DEFAULT                                  0x00000000UL                        /**< Mode DEFAULT for RAC_FRCRXWORD              */
#define RAC_FRCRXWORD_RDATA_DEFAULT                                   (_RAC_FRCRXWORD_RDATA_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_FRCRXWORD      */

/* Bit fields for RAC EM1PCSR */
#define _RAC_EM1PCSR_RESETVALUE                                       0x00000000UL                                  /**< Default value for RAC_EM1PCSR               */
#define _RAC_EM1PCSR_MASK                                             0x00070033UL                                  /**< Mask for RAC_EM1PCSR                        */
#define RAC_EM1PCSR_RADIOEM1PMODE                                     (0x1UL << 0)                                  /**<                                             */
#define _RAC_EM1PCSR_RADIOEM1PMODE_SHIFT                              0                                             /**< Shift value for RAC_RADIOEM1PMODE           */
#define _RAC_EM1PCSR_RADIOEM1PMODE_MASK                               0x1UL                                         /**< Bit mask for RAC_RADIOEM1PMODE              */
#define _RAC_EM1PCSR_RADIOEM1PMODE_DEFAULT                            0x00000000UL                                  /**< Mode DEFAULT for RAC_EM1PCSR                */
#define _RAC_EM1PCSR_RADIOEM1PMODE_HWCTRL                             0x00000000UL                                  /**< Mode HWCTRL for RAC_EM1PCSR                 */
#define _RAC_EM1PCSR_RADIOEM1PMODE_SWCTRL                             0x00000001UL                                  /**< Mode SWCTRL for RAC_EM1PCSR                 */
#define RAC_EM1PCSR_RADIOEM1PMODE_DEFAULT                             (_RAC_EM1PCSR_RADIOEM1PMODE_DEFAULT << 0)     /**< Shifted mode DEFAULT for RAC_EM1PCSR        */
#define RAC_EM1PCSR_RADIOEM1PMODE_HWCTRL                              (_RAC_EM1PCSR_RADIOEM1PMODE_HWCTRL << 0)      /**< Shifted mode HWCTRL for RAC_EM1PCSR         */
#define RAC_EM1PCSR_RADIOEM1PMODE_SWCTRL                              (_RAC_EM1PCSR_RADIOEM1PMODE_SWCTRL << 0)      /**< Shifted mode SWCTRL for RAC_EM1PCSR         */
#define RAC_EM1PCSR_RADIOEM1PDISSWREQ                                 (0x1UL << 1)                                  /**<                                             */
#define _RAC_EM1PCSR_RADIOEM1PDISSWREQ_SHIFT                          1                                             /**< Shift value for RAC_RADIOEM1PDISSWREQ       */
#define _RAC_EM1PCSR_RADIOEM1PDISSWREQ_MASK                           0x2UL                                         /**< Bit mask for RAC_RADIOEM1PDISSWREQ          */
#define _RAC_EM1PCSR_RADIOEM1PDISSWREQ_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for RAC_EM1PCSR                */
#define RAC_EM1PCSR_RADIOEM1PDISSWREQ_DEFAULT                         (_RAC_EM1PCSR_RADIOEM1PDISSWREQ_DEFAULT << 1) /**< Shifted mode DEFAULT for RAC_EM1PCSR        */
#define RAC_EM1PCSR_MCUEM1PMODE                                       (0x1UL << 4)                                  /**<                                             */
#define _RAC_EM1PCSR_MCUEM1PMODE_SHIFT                                4                                             /**< Shift value for RAC_MCUEM1PMODE             */
#define _RAC_EM1PCSR_MCUEM1PMODE_MASK                                 0x10UL                                        /**< Bit mask for RAC_MCUEM1PMODE                */
#define _RAC_EM1PCSR_MCUEM1PMODE_DEFAULT                              0x00000000UL                                  /**< Mode DEFAULT for RAC_EM1PCSR                */
#define _RAC_EM1PCSR_MCUEM1PMODE_HWCTRL                               0x00000000UL                                  /**< Mode HWCTRL for RAC_EM1PCSR                 */
#define _RAC_EM1PCSR_MCUEM1PMODE_SWCTRL                               0x00000001UL                                  /**< Mode SWCTRL for RAC_EM1PCSR                 */
#define RAC_EM1PCSR_MCUEM1PMODE_DEFAULT                               (_RAC_EM1PCSR_MCUEM1PMODE_DEFAULT << 4)       /**< Shifted mode DEFAULT for RAC_EM1PCSR        */
#define RAC_EM1PCSR_MCUEM1PMODE_HWCTRL                                (_RAC_EM1PCSR_MCUEM1PMODE_HWCTRL << 4)        /**< Shifted mode HWCTRL for RAC_EM1PCSR         */
#define RAC_EM1PCSR_MCUEM1PMODE_SWCTRL                                (_RAC_EM1PCSR_MCUEM1PMODE_SWCTRL << 4)        /**< Shifted mode SWCTRL for RAC_EM1PCSR         */
#define RAC_EM1PCSR_MCUEM1PDISSWREQ                                   (0x1UL << 5)                                  /**<                                             */
#define _RAC_EM1PCSR_MCUEM1PDISSWREQ_SHIFT                            5                                             /**< Shift value for RAC_MCUEM1PDISSWREQ         */
#define _RAC_EM1PCSR_MCUEM1PDISSWREQ_MASK                             0x20UL                                        /**< Bit mask for RAC_MCUEM1PDISSWREQ            */
#define _RAC_EM1PCSR_MCUEM1PDISSWREQ_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for RAC_EM1PCSR                */
#define RAC_EM1PCSR_MCUEM1PDISSWREQ_DEFAULT                           (_RAC_EM1PCSR_MCUEM1PDISSWREQ_DEFAULT << 5)   /**< Shifted mode DEFAULT for RAC_EM1PCSR        */
#define RAC_EM1PCSR_RADIOEM1PREQ                                      (0x1UL << 16)                                 /**<                                             */
#define _RAC_EM1PCSR_RADIOEM1PREQ_SHIFT                               16                                            /**< Shift value for RAC_RADIOEM1PREQ            */
#define _RAC_EM1PCSR_RADIOEM1PREQ_MASK                                0x10000UL                                     /**< Bit mask for RAC_RADIOEM1PREQ               */
#define _RAC_EM1PCSR_RADIOEM1PREQ_DEFAULT                             0x00000000UL                                  /**< Mode DEFAULT for RAC_EM1PCSR                */
#define RAC_EM1PCSR_RADIOEM1PREQ_DEFAULT                              (_RAC_EM1PCSR_RADIOEM1PREQ_DEFAULT << 16)     /**< Shifted mode DEFAULT for RAC_EM1PCSR        */
#define RAC_EM1PCSR_RADIOEM1PACK                                      (0x1UL << 17)                                 /**<                                             */
#define _RAC_EM1PCSR_RADIOEM1PACK_SHIFT                               17                                            /**< Shift value for RAC_RADIOEM1PACK            */
#define _RAC_EM1PCSR_RADIOEM1PACK_MASK                                0x20000UL                                     /**< Bit mask for RAC_RADIOEM1PACK               */
#define _RAC_EM1PCSR_RADIOEM1PACK_DEFAULT                             0x00000000UL                                  /**< Mode DEFAULT for RAC_EM1PCSR                */
#define RAC_EM1PCSR_RADIOEM1PACK_DEFAULT                              (_RAC_EM1PCSR_RADIOEM1PACK_DEFAULT << 17)     /**< Shifted mode DEFAULT for RAC_EM1PCSR        */
#define RAC_EM1PCSR_RADIOEM1PHWREQ                                    (0x1UL << 18)                                 /**<                                             */
#define _RAC_EM1PCSR_RADIOEM1PHWREQ_SHIFT                             18                                            /**< Shift value for RAC_RADIOEM1PHWREQ          */
#define _RAC_EM1PCSR_RADIOEM1PHWREQ_MASK                              0x40000UL                                     /**< Bit mask for RAC_RADIOEM1PHWREQ             */
#define _RAC_EM1PCSR_RADIOEM1PHWREQ_DEFAULT                           0x00000000UL                                  /**< Mode DEFAULT for RAC_EM1PCSR                */
#define RAC_EM1PCSR_RADIOEM1PHWREQ_DEFAULT                            (_RAC_EM1PCSR_RADIOEM1PHWREQ_DEFAULT << 18)   /**< Shifted mode DEFAULT for RAC_EM1PCSR        */

/* Bit fields for RAC SYNTHENCTRL */
#define _RAC_SYNTHENCTRL_RESETVALUE                                   0x00000000UL                                                      /**< Default value for RAC_SYNTHENCTRL           */
#define _RAC_SYNTHENCTRL_MASK                                         0x00100682UL                                                      /**< Mask for RAC_SYNTHENCTRL                    */
#define RAC_SYNTHENCTRL_VCOSTARTUP                                    (0x1UL << 1)                                                      /**< SYVCOFASTSTARTUP                            */
#define _RAC_SYNTHENCTRL_VCOSTARTUP_SHIFT                             1                                                                 /**< Shift value for RAC_VCOSTARTUP              */
#define _RAC_SYNTHENCTRL_VCOSTARTUP_MASK                              0x2UL                                                             /**< Bit mask for RAC_VCOSTARTUP                 */
#define _RAC_SYNTHENCTRL_VCOSTARTUP_DEFAULT                           0x00000000UL                                                      /**< Mode DEFAULT for RAC_SYNTHENCTRL            */
#define _RAC_SYNTHENCTRL_VCOSTARTUP_fast_start_up_0                   0x00000000UL                                                      /**< Mode fast_start_up_0 for RAC_SYNTHENCTRL    */
#define _RAC_SYNTHENCTRL_VCOSTARTUP_fast_start_up_1                   0x00000001UL                                                      /**< Mode fast_start_up_1 for RAC_SYNTHENCTRL    */
#define RAC_SYNTHENCTRL_VCOSTARTUP_DEFAULT                            (_RAC_SYNTHENCTRL_VCOSTARTUP_DEFAULT << 1)                        /**< Shifted mode DEFAULT for RAC_SYNTHENCTRL    */
#define RAC_SYNTHENCTRL_VCOSTARTUP_fast_start_up_0                    (_RAC_SYNTHENCTRL_VCOSTARTUP_fast_start_up_0 << 1)                /**< Shifted mode fast_start_up_0 for RAC_SYNTHENCTRL*/
#define RAC_SYNTHENCTRL_VCOSTARTUP_fast_start_up_1                    (_RAC_SYNTHENCTRL_VCOSTARTUP_fast_start_up_1 << 1)                /**< Shifted mode fast_start_up_1 for RAC_SYNTHENCTRL*/
#define RAC_SYNTHENCTRL_VCBUFEN                                       (0x1UL << 7)                                                      /**< SYLPFVCBUFEN                                */
#define _RAC_SYNTHENCTRL_VCBUFEN_SHIFT                                7                                                                 /**< Shift value for RAC_VCBUFEN                 */
#define _RAC_SYNTHENCTRL_VCBUFEN_MASK                                 0x80UL                                                            /**< Bit mask for RAC_VCBUFEN                    */
#define _RAC_SYNTHENCTRL_VCBUFEN_DEFAULT                              0x00000000UL                                                      /**< Mode DEFAULT for RAC_SYNTHENCTRL            */
#define _RAC_SYNTHENCTRL_VCBUFEN_Disabled                             0x00000000UL                                                      /**< Mode Disabled for RAC_SYNTHENCTRL           */
#define _RAC_SYNTHENCTRL_VCBUFEN_Enabled                              0x00000001UL                                                      /**< Mode Enabled for RAC_SYNTHENCTRL            */
#define RAC_SYNTHENCTRL_VCBUFEN_DEFAULT                               (_RAC_SYNTHENCTRL_VCBUFEN_DEFAULT << 7)                           /**< Shifted mode DEFAULT for RAC_SYNTHENCTRL    */
#define RAC_SYNTHENCTRL_VCBUFEN_Disabled                              (_RAC_SYNTHENCTRL_VCBUFEN_Disabled << 7)                          /**< Shifted mode Disabled for RAC_SYNTHENCTRL   */
#define RAC_SYNTHENCTRL_VCBUFEN_Enabled                               (_RAC_SYNTHENCTRL_VCBUFEN_Enabled << 7)                           /**< Shifted mode Enabled for RAC_SYNTHENCTRL    */
#define RAC_SYNTHENCTRL_MMDPOWERBALANCEDISABLE                        (0x1UL << 10)                                                     /**< SYMMDPOWERBALANCEENB                        */
#define _RAC_SYNTHENCTRL_MMDPOWERBALANCEDISABLE_SHIFT                 10                                                                /**< Shift value for RAC_MMDPOWERBALANCEDISABLE  */
#define _RAC_SYNTHENCTRL_MMDPOWERBALANCEDISABLE_MASK                  0x400UL                                                           /**< Bit mask for RAC_MMDPOWERBALANCEDISABLE     */
#define _RAC_SYNTHENCTRL_MMDPOWERBALANCEDISABLE_DEFAULT               0x00000000UL                                                      /**< Mode DEFAULT for RAC_SYNTHENCTRL            */
#define _RAC_SYNTHENCTRL_MMDPOWERBALANCEDISABLE_EnablePowerbleed      0x00000000UL                                                      /**< Mode EnablePowerbleed for RAC_SYNTHENCTRL   */
#define _RAC_SYNTHENCTRL_MMDPOWERBALANCEDISABLE_DisablePowerBleed     0x00000001UL                                                      /**< Mode DisablePowerBleed for RAC_SYNTHENCTRL  */
#define RAC_SYNTHENCTRL_MMDPOWERBALANCEDISABLE_DEFAULT                (_RAC_SYNTHENCTRL_MMDPOWERBALANCEDISABLE_DEFAULT << 10)           /**< Shifted mode DEFAULT for RAC_SYNTHENCTRL    */
#define RAC_SYNTHENCTRL_MMDPOWERBALANCEDISABLE_EnablePowerbleed       (_RAC_SYNTHENCTRL_MMDPOWERBALANCEDISABLE_EnablePowerbleed << 10)  /**< Shifted mode EnablePowerbleed for RAC_SYNTHENCTRL*/
#define RAC_SYNTHENCTRL_MMDPOWERBALANCEDISABLE_DisablePowerBleed      (_RAC_SYNTHENCTRL_MMDPOWERBALANCEDISABLE_DisablePowerBleed << 10) /**< Shifted mode DisablePowerBleed for RAC_SYNTHENCTRL*/
#define RAC_SYNTHENCTRL_LPFBWSEL                                      (0x1UL << 20)                                                     /**< LPF bandwidth register selection            */
#define _RAC_SYNTHENCTRL_LPFBWSEL_SHIFT                               20                                                                /**< Shift value for RAC_LPFBWSEL                */
#define _RAC_SYNTHENCTRL_LPFBWSEL_MASK                                0x100000UL                                                        /**< Bit mask for RAC_LPFBWSEL                   */
#define _RAC_SYNTHENCTRL_LPFBWSEL_DEFAULT                             0x00000000UL                                                      /**< Mode DEFAULT for RAC_SYNTHENCTRL            */
#define _RAC_SYNTHENCTRL_LPFBWSEL_LPFBWRX                             0x00000000UL                                                      /**< Mode LPFBWRX for RAC_SYNTHENCTRL            */
#define _RAC_SYNTHENCTRL_LPFBWSEL_LPFBWTX                             0x00000001UL                                                      /**< Mode LPFBWTX for RAC_SYNTHENCTRL            */
#define RAC_SYNTHENCTRL_LPFBWSEL_DEFAULT                              (_RAC_SYNTHENCTRL_LPFBWSEL_DEFAULT << 20)                         /**< Shifted mode DEFAULT for RAC_SYNTHENCTRL    */
#define RAC_SYNTHENCTRL_LPFBWSEL_LPFBWRX                              (_RAC_SYNTHENCTRL_LPFBWSEL_LPFBWRX << 20)                         /**< Shifted mode LPFBWRX for RAC_SYNTHENCTRL    */
#define RAC_SYNTHENCTRL_LPFBWSEL_LPFBWTX                              (_RAC_SYNTHENCTRL_LPFBWSEL_LPFBWTX << 20)                         /**< Shifted mode LPFBWTX for RAC_SYNTHENCTRL    */

/* Bit fields for RAC SYNTHREGCTRL */
#define _RAC_SYNTHREGCTRL_RESETVALUE                                  0x04000000UL                                        /**< Default value for RAC_SYNTHREGCTRL          */
#define _RAC_SYNTHREGCTRL_MASK                                        0x07001C00UL                                        /**< Mask for RAC_SYNTHREGCTRL                   */
#define _RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_SHIFT                        10                                                  /**< Shift value for RAC_MMDLDOVREFTRIM          */
#define _RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_MASK                         0x1C00UL                                            /**< Bit mask for RAC_MMDLDOVREFTRIM             */
#define _RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_DEFAULT                      0x00000000UL                                        /**< Mode DEFAULT for RAC_SYNTHREGCTRL           */
#define _RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6000                   0x00000000UL                                        /**< Mode vref0p6000 for RAC_SYNTHREGCTRL        */
#define _RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6125                   0x00000001UL                                        /**< Mode vref0p6125 for RAC_SYNTHREGCTRL        */
#define _RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6250                   0x00000002UL                                        /**< Mode vref0p6250 for RAC_SYNTHREGCTRL        */
#define _RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6375                   0x00000003UL                                        /**< Mode vref0p6375 for RAC_SYNTHREGCTRL        */
#define _RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6500                   0x00000004UL                                        /**< Mode vref0p6500 for RAC_SYNTHREGCTRL        */
#define _RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6625                   0x00000005UL                                        /**< Mode vref0p6625 for RAC_SYNTHREGCTRL        */
#define _RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6750                   0x00000006UL                                        /**< Mode vref0p6750 for RAC_SYNTHREGCTRL        */
#define _RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6875                   0x00000007UL                                        /**< Mode vref0p6875 for RAC_SYNTHREGCTRL        */
#define RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_DEFAULT                       (_RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_DEFAULT << 10)    /**< Shifted mode DEFAULT for RAC_SYNTHREGCTRL   */
#define RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6000                    (_RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6000 << 10) /**< Shifted mode vref0p6000 for RAC_SYNTHREGCTRL*/
#define RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6125                    (_RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6125 << 10) /**< Shifted mode vref0p6125 for RAC_SYNTHREGCTRL*/
#define RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6250                    (_RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6250 << 10) /**< Shifted mode vref0p6250 for RAC_SYNTHREGCTRL*/
#define RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6375                    (_RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6375 << 10) /**< Shifted mode vref0p6375 for RAC_SYNTHREGCTRL*/
#define RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6500                    (_RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6500 << 10) /**< Shifted mode vref0p6500 for RAC_SYNTHREGCTRL*/
#define RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6625                    (_RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6625 << 10) /**< Shifted mode vref0p6625 for RAC_SYNTHREGCTRL*/
#define RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6750                    (_RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6750 << 10) /**< Shifted mode vref0p6750 for RAC_SYNTHREGCTRL*/
#define RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6875                    (_RAC_SYNTHREGCTRL_MMDLDOVREFTRIM_vref0p6875 << 10) /**< Shifted mode vref0p6875 for RAC_SYNTHREGCTRL*/
#define _RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_SHIFT                        24                                                  /**< Shift value for RAC_CHPLDOVREFTRIM          */
#define _RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_MASK                         0x7000000UL                                         /**< Bit mask for RAC_CHPLDOVREFTRIM             */
#define _RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_DEFAULT                      0x00000004UL                                        /**< Mode DEFAULT for RAC_SYNTHREGCTRL           */
#define _RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6000                   0x00000000UL                                        /**< Mode vref0p6000 for RAC_SYNTHREGCTRL        */
#define _RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6125                   0x00000001UL                                        /**< Mode vref0p6125 for RAC_SYNTHREGCTRL        */
#define _RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6250                   0x00000002UL                                        /**< Mode vref0p6250 for RAC_SYNTHREGCTRL        */
#define _RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6375                   0x00000003UL                                        /**< Mode vref0p6375 for RAC_SYNTHREGCTRL        */
#define _RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6500                   0x00000004UL                                        /**< Mode vref0p6500 for RAC_SYNTHREGCTRL        */
#define _RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6625                   0x00000005UL                                        /**< Mode vref0p6625 for RAC_SYNTHREGCTRL        */
#define _RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6750                   0x00000006UL                                        /**< Mode vref0p6750 for RAC_SYNTHREGCTRL        */
#define _RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6875                   0x00000007UL                                        /**< Mode vref0p6875 for RAC_SYNTHREGCTRL        */
#define RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_DEFAULT                       (_RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_DEFAULT << 24)    /**< Shifted mode DEFAULT for RAC_SYNTHREGCTRL   */
#define RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6000                    (_RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6000 << 24) /**< Shifted mode vref0p6000 for RAC_SYNTHREGCTRL*/
#define RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6125                    (_RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6125 << 24) /**< Shifted mode vref0p6125 for RAC_SYNTHREGCTRL*/
#define RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6250                    (_RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6250 << 24) /**< Shifted mode vref0p6250 for RAC_SYNTHREGCTRL*/
#define RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6375                    (_RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6375 << 24) /**< Shifted mode vref0p6375 for RAC_SYNTHREGCTRL*/
#define RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6500                    (_RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6500 << 24) /**< Shifted mode vref0p6500 for RAC_SYNTHREGCTRL*/
#define RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6625                    (_RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6625 << 24) /**< Shifted mode vref0p6625 for RAC_SYNTHREGCTRL*/
#define RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6750                    (_RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6750 << 24) /**< Shifted mode vref0p6750 for RAC_SYNTHREGCTRL*/
#define RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6875                    (_RAC_SYNTHREGCTRL_CHPLDOVREFTRIM_vref0p6875 << 24) /**< Shifted mode vref0p6875 for RAC_SYNTHREGCTRL*/

/* Bit fields for RAC VCOCTRL */
#define _RAC_VCOCTRL_RESETVALUE                                       0x0000044CUL                                  /**< Default value for RAC_VCOCTRL               */
#define _RAC_VCOCTRL_MASK                                             0x00000FFFUL                                  /**< Mask for RAC_VCOCTRL                        */
#define _RAC_VCOCTRL_VCOAMPLITUDE_SHIFT                               0                                             /**< Shift value for RAC_VCOAMPLITUDE            */
#define _RAC_VCOCTRL_VCOAMPLITUDE_MASK                                0xFUL                                         /**< Bit mask for RAC_VCOAMPLITUDE               */
#define _RAC_VCOCTRL_VCOAMPLITUDE_DEFAULT                             0x0000000CUL                                  /**< Mode DEFAULT for RAC_VCOCTRL                */
#define RAC_VCOCTRL_VCOAMPLITUDE_DEFAULT                              (_RAC_VCOCTRL_VCOAMPLITUDE_DEFAULT << 0)      /**< Shifted mode DEFAULT for RAC_VCOCTRL        */
#define _RAC_VCOCTRL_VCODETAMPLITUDERX_SHIFT                          4                                             /**< Shift value for RAC_VCODETAMPLITUDERX       */
#define _RAC_VCOCTRL_VCODETAMPLITUDERX_MASK                           0xF0UL                                        /**< Bit mask for RAC_VCODETAMPLITUDERX          */
#define _RAC_VCOCTRL_VCODETAMPLITUDERX_DEFAULT                        0x00000004UL                                  /**< Mode DEFAULT for RAC_VCOCTRL                */
#define RAC_VCOCTRL_VCODETAMPLITUDERX_DEFAULT                         (_RAC_VCOCTRL_VCODETAMPLITUDERX_DEFAULT << 4) /**< Shifted mode DEFAULT for RAC_VCOCTRL        */
#define _RAC_VCOCTRL_VCODETAMPLITUDETX_SHIFT                          8                                             /**< Shift value for RAC_VCODETAMPLITUDETX       */
#define _RAC_VCOCTRL_VCODETAMPLITUDETX_MASK                           0xF00UL                                       /**< Bit mask for RAC_VCODETAMPLITUDETX          */
#define _RAC_VCOCTRL_VCODETAMPLITUDETX_DEFAULT                        0x00000004UL                                  /**< Mode DEFAULT for RAC_VCOCTRL                */
#define RAC_VCOCTRL_VCODETAMPLITUDETX_DEFAULT                         (_RAC_VCOCTRL_VCODETAMPLITUDETX_DEFAULT << 8) /**< Shifted mode DEFAULT for RAC_VCOCTRL        */

/* Bit fields for RAC STATUS2 */
#define _RAC_STATUS2_RESETVALUE                                       0x00000000UL                              /**< Default value for RAC_STATUS2               */
#define _RAC_STATUS2_MASK                                             0x0000FFFFUL                              /**< Mask for RAC_STATUS2                        */
#define _RAC_STATUS2_PREVSTATE1_SHIFT                                 0                                         /**< Shift value for RAC_PREVSTATE1              */
#define _RAC_STATUS2_PREVSTATE1_MASK                                  0xFUL                                     /**< Bit mask for RAC_PREVSTATE1                 */
#define _RAC_STATUS2_PREVSTATE1_DEFAULT                               0x00000000UL                              /**< Mode DEFAULT for RAC_STATUS2                */
#define _RAC_STATUS2_PREVSTATE1_OFF                                   0x00000000UL                              /**< Mode OFF for RAC_STATUS2                    */
#define _RAC_STATUS2_PREVSTATE1_RXWARM                                0x00000001UL                              /**< Mode RXWARM for RAC_STATUS2                 */
#define _RAC_STATUS2_PREVSTATE1_RXSEARCH                              0x00000002UL                              /**< Mode RXSEARCH for RAC_STATUS2               */
#define _RAC_STATUS2_PREVSTATE1_RXFRAME                               0x00000003UL                              /**< Mode RXFRAME for RAC_STATUS2                */
#define _RAC_STATUS2_PREVSTATE1_RXPD                                  0x00000004UL                              /**< Mode RXPD for RAC_STATUS2                   */
#define _RAC_STATUS2_PREVSTATE1_RX2RX                                 0x00000005UL                              /**< Mode RX2RX for RAC_STATUS2                  */
#define _RAC_STATUS2_PREVSTATE1_RXOVERFLOW                            0x00000006UL                              /**< Mode RXOVERFLOW for RAC_STATUS2             */
#define _RAC_STATUS2_PREVSTATE1_RX2TX                                 0x00000007UL                              /**< Mode RX2TX for RAC_STATUS2                  */
#define _RAC_STATUS2_PREVSTATE1_TXWARM                                0x00000008UL                              /**< Mode TXWARM for RAC_STATUS2                 */
#define _RAC_STATUS2_PREVSTATE1_TX                                    0x00000009UL                              /**< Mode TX for RAC_STATUS2                     */
#define _RAC_STATUS2_PREVSTATE1_TXPD                                  0x0000000AUL                              /**< Mode TXPD for RAC_STATUS2                   */
#define _RAC_STATUS2_PREVSTATE1_TX2RX                                 0x0000000BUL                              /**< Mode TX2RX for RAC_STATUS2                  */
#define _RAC_STATUS2_PREVSTATE1_TX2TX                                 0x0000000CUL                              /**< Mode TX2TX for RAC_STATUS2                  */
#define _RAC_STATUS2_PREVSTATE1_SHUTDOWN                              0x0000000DUL                              /**< Mode SHUTDOWN for RAC_STATUS2               */
#define _RAC_STATUS2_PREVSTATE1_POR                                   0x0000000EUL                              /**< Mode POR for RAC_STATUS2                    */
#define RAC_STATUS2_PREVSTATE1_DEFAULT                                (_RAC_STATUS2_PREVSTATE1_DEFAULT << 0)    /**< Shifted mode DEFAULT for RAC_STATUS2        */
#define RAC_STATUS2_PREVSTATE1_OFF                                    (_RAC_STATUS2_PREVSTATE1_OFF << 0)        /**< Shifted mode OFF for RAC_STATUS2            */
#define RAC_STATUS2_PREVSTATE1_RXWARM                                 (_RAC_STATUS2_PREVSTATE1_RXWARM << 0)     /**< Shifted mode RXWARM for RAC_STATUS2         */
#define RAC_STATUS2_PREVSTATE1_RXSEARCH                               (_RAC_STATUS2_PREVSTATE1_RXSEARCH << 0)   /**< Shifted mode RXSEARCH for RAC_STATUS2       */
#define RAC_STATUS2_PREVSTATE1_RXFRAME                                (_RAC_STATUS2_PREVSTATE1_RXFRAME << 0)    /**< Shifted mode RXFRAME for RAC_STATUS2        */
#define RAC_STATUS2_PREVSTATE1_RXPD                                   (_RAC_STATUS2_PREVSTATE1_RXPD << 0)       /**< Shifted mode RXPD for RAC_STATUS2           */
#define RAC_STATUS2_PREVSTATE1_RX2RX                                  (_RAC_STATUS2_PREVSTATE1_RX2RX << 0)      /**< Shifted mode RX2RX for RAC_STATUS2          */
#define RAC_STATUS2_PREVSTATE1_RXOVERFLOW                             (_RAC_STATUS2_PREVSTATE1_RXOVERFLOW << 0) /**< Shifted mode RXOVERFLOW for RAC_STATUS2     */
#define RAC_STATUS2_PREVSTATE1_RX2TX                                  (_RAC_STATUS2_PREVSTATE1_RX2TX << 0)      /**< Shifted mode RX2TX for RAC_STATUS2          */
#define RAC_STATUS2_PREVSTATE1_TXWARM                                 (_RAC_STATUS2_PREVSTATE1_TXWARM << 0)     /**< Shifted mode TXWARM for RAC_STATUS2         */
#define RAC_STATUS2_PREVSTATE1_TX                                     (_RAC_STATUS2_PREVSTATE1_TX << 0)         /**< Shifted mode TX for RAC_STATUS2             */
#define RAC_STATUS2_PREVSTATE1_TXPD                                   (_RAC_STATUS2_PREVSTATE1_TXPD << 0)       /**< Shifted mode TXPD for RAC_STATUS2           */
#define RAC_STATUS2_PREVSTATE1_TX2RX                                  (_RAC_STATUS2_PREVSTATE1_TX2RX << 0)      /**< Shifted mode TX2RX for RAC_STATUS2          */
#define RAC_STATUS2_PREVSTATE1_TX2TX                                  (_RAC_STATUS2_PREVSTATE1_TX2TX << 0)      /**< Shifted mode TX2TX for RAC_STATUS2          */
#define RAC_STATUS2_PREVSTATE1_SHUTDOWN                               (_RAC_STATUS2_PREVSTATE1_SHUTDOWN << 0)   /**< Shifted mode SHUTDOWN for RAC_STATUS2       */
#define RAC_STATUS2_PREVSTATE1_POR                                    (_RAC_STATUS2_PREVSTATE1_POR << 0)        /**< Shifted mode POR for RAC_STATUS2            */
#define _RAC_STATUS2_PREVSTATE2_SHIFT                                 4                                         /**< Shift value for RAC_PREVSTATE2              */
#define _RAC_STATUS2_PREVSTATE2_MASK                                  0xF0UL                                    /**< Bit mask for RAC_PREVSTATE2                 */
#define _RAC_STATUS2_PREVSTATE2_DEFAULT                               0x00000000UL                              /**< Mode DEFAULT for RAC_STATUS2                */
#define _RAC_STATUS2_PREVSTATE2_OFF                                   0x00000000UL                              /**< Mode OFF for RAC_STATUS2                    */
#define _RAC_STATUS2_PREVSTATE2_RXWARM                                0x00000001UL                              /**< Mode RXWARM for RAC_STATUS2                 */
#define _RAC_STATUS2_PREVSTATE2_RXSEARCH                              0x00000002UL                              /**< Mode RXSEARCH for RAC_STATUS2               */
#define _RAC_STATUS2_PREVSTATE2_RXFRAME                               0x00000003UL                              /**< Mode RXFRAME for RAC_STATUS2                */
#define _RAC_STATUS2_PREVSTATE2_RXPD                                  0x00000004UL                              /**< Mode RXPD for RAC_STATUS2                   */
#define _RAC_STATUS2_PREVSTATE2_RX2RX                                 0x00000005UL                              /**< Mode RX2RX for RAC_STATUS2                  */
#define _RAC_STATUS2_PREVSTATE2_RXOVERFLOW                            0x00000006UL                              /**< Mode RXOVERFLOW for RAC_STATUS2             */
#define _RAC_STATUS2_PREVSTATE2_RX2TX                                 0x00000007UL                              /**< Mode RX2TX for RAC_STATUS2                  */
#define _RAC_STATUS2_PREVSTATE2_TXWARM                                0x00000008UL                              /**< Mode TXWARM for RAC_STATUS2                 */
#define _RAC_STATUS2_PREVSTATE2_TX                                    0x00000009UL                              /**< Mode TX for RAC_STATUS2                     */
#define _RAC_STATUS2_PREVSTATE2_TXPD                                  0x0000000AUL                              /**< Mode TXPD for RAC_STATUS2                   */
#define _RAC_STATUS2_PREVSTATE2_TX2RX                                 0x0000000BUL                              /**< Mode TX2RX for RAC_STATUS2                  */
#define _RAC_STATUS2_PREVSTATE2_TX2TX                                 0x0000000CUL                              /**< Mode TX2TX for RAC_STATUS2                  */
#define _RAC_STATUS2_PREVSTATE2_SHUTDOWN                              0x0000000DUL                              /**< Mode SHUTDOWN for RAC_STATUS2               */
#define _RAC_STATUS2_PREVSTATE2_POR                                   0x0000000EUL                              /**< Mode POR for RAC_STATUS2                    */
#define RAC_STATUS2_PREVSTATE2_DEFAULT                                (_RAC_STATUS2_PREVSTATE2_DEFAULT << 4)    /**< Shifted mode DEFAULT for RAC_STATUS2        */
#define RAC_STATUS2_PREVSTATE2_OFF                                    (_RAC_STATUS2_PREVSTATE2_OFF << 4)        /**< Shifted mode OFF for RAC_STATUS2            */
#define RAC_STATUS2_PREVSTATE2_RXWARM                                 (_RAC_STATUS2_PREVSTATE2_RXWARM << 4)     /**< Shifted mode RXWARM for RAC_STATUS2         */
#define RAC_STATUS2_PREVSTATE2_RXSEARCH                               (_RAC_STATUS2_PREVSTATE2_RXSEARCH << 4)   /**< Shifted mode RXSEARCH for RAC_STATUS2       */
#define RAC_STATUS2_PREVSTATE2_RXFRAME                                (_RAC_STATUS2_PREVSTATE2_RXFRAME << 4)    /**< Shifted mode RXFRAME for RAC_STATUS2        */
#define RAC_STATUS2_PREVSTATE2_RXPD                                   (_RAC_STATUS2_PREVSTATE2_RXPD << 4)       /**< Shifted mode RXPD for RAC_STATUS2           */
#define RAC_STATUS2_PREVSTATE2_RX2RX                                  (_RAC_STATUS2_PREVSTATE2_RX2RX << 4)      /**< Shifted mode RX2RX for RAC_STATUS2          */
#define RAC_STATUS2_PREVSTATE2_RXOVERFLOW                             (_RAC_STATUS2_PREVSTATE2_RXOVERFLOW << 4) /**< Shifted mode RXOVERFLOW for RAC_STATUS2     */
#define RAC_STATUS2_PREVSTATE2_RX2TX                                  (_RAC_STATUS2_PREVSTATE2_RX2TX << 4)      /**< Shifted mode RX2TX for RAC_STATUS2          */
#define RAC_STATUS2_PREVSTATE2_TXWARM                                 (_RAC_STATUS2_PREVSTATE2_TXWARM << 4)     /**< Shifted mode TXWARM for RAC_STATUS2         */
#define RAC_STATUS2_PREVSTATE2_TX                                     (_RAC_STATUS2_PREVSTATE2_TX << 4)         /**< Shifted mode TX for RAC_STATUS2             */
#define RAC_STATUS2_PREVSTATE2_TXPD                                   (_RAC_STATUS2_PREVSTATE2_TXPD << 4)       /**< Shifted mode TXPD for RAC_STATUS2           */
#define RAC_STATUS2_PREVSTATE2_TX2RX                                  (_RAC_STATUS2_PREVSTATE2_TX2RX << 4)      /**< Shifted mode TX2RX for RAC_STATUS2          */
#define RAC_STATUS2_PREVSTATE2_TX2TX                                  (_RAC_STATUS2_PREVSTATE2_TX2TX << 4)      /**< Shifted mode TX2TX for RAC_STATUS2          */
#define RAC_STATUS2_PREVSTATE2_SHUTDOWN                               (_RAC_STATUS2_PREVSTATE2_SHUTDOWN << 4)   /**< Shifted mode SHUTDOWN for RAC_STATUS2       */
#define RAC_STATUS2_PREVSTATE2_POR                                    (_RAC_STATUS2_PREVSTATE2_POR << 4)        /**< Shifted mode POR for RAC_STATUS2            */
#define _RAC_STATUS2_PREVSTATE3_SHIFT                                 8                                         /**< Shift value for RAC_PREVSTATE3              */
#define _RAC_STATUS2_PREVSTATE3_MASK                                  0xF00UL                                   /**< Bit mask for RAC_PREVSTATE3                 */
#define _RAC_STATUS2_PREVSTATE3_DEFAULT                               0x00000000UL                              /**< Mode DEFAULT for RAC_STATUS2                */
#define _RAC_STATUS2_PREVSTATE3_OFF                                   0x00000000UL                              /**< Mode OFF for RAC_STATUS2                    */
#define _RAC_STATUS2_PREVSTATE3_RXWARM                                0x00000001UL                              /**< Mode RXWARM for RAC_STATUS2                 */
#define _RAC_STATUS2_PREVSTATE3_RXSEARCH                              0x00000002UL                              /**< Mode RXSEARCH for RAC_STATUS2               */
#define _RAC_STATUS2_PREVSTATE3_RXFRAME                               0x00000003UL                              /**< Mode RXFRAME for RAC_STATUS2                */
#define _RAC_STATUS2_PREVSTATE3_RXPD                                  0x00000004UL                              /**< Mode RXPD for RAC_STATUS2                   */
#define _RAC_STATUS2_PREVSTATE3_RX2RX                                 0x00000005UL                              /**< Mode RX2RX for RAC_STATUS2                  */
#define _RAC_STATUS2_PREVSTATE3_RXOVERFLOW                            0x00000006UL                              /**< Mode RXOVERFLOW for RAC_STATUS2             */
#define _RAC_STATUS2_PREVSTATE3_RX2TX                                 0x00000007UL                              /**< Mode RX2TX for RAC_STATUS2                  */
#define _RAC_STATUS2_PREVSTATE3_TXWARM                                0x00000008UL                              /**< Mode TXWARM for RAC_STATUS2                 */
#define _RAC_STATUS2_PREVSTATE3_TX                                    0x00000009UL                              /**< Mode TX for RAC_STATUS2                     */
#define _RAC_STATUS2_PREVSTATE3_TXPD                                  0x0000000AUL                              /**< Mode TXPD for RAC_STATUS2                   */
#define _RAC_STATUS2_PREVSTATE3_TX2RX                                 0x0000000BUL                              /**< Mode TX2RX for RAC_STATUS2                  */
#define _RAC_STATUS2_PREVSTATE3_TX2TX                                 0x0000000CUL                              /**< Mode TX2TX for RAC_STATUS2                  */
#define _RAC_STATUS2_PREVSTATE3_SHUTDOWN                              0x0000000DUL                              /**< Mode SHUTDOWN for RAC_STATUS2               */
#define _RAC_STATUS2_PREVSTATE3_POR                                   0x0000000EUL                              /**< Mode POR for RAC_STATUS2                    */
#define RAC_STATUS2_PREVSTATE3_DEFAULT                                (_RAC_STATUS2_PREVSTATE3_DEFAULT << 8)    /**< Shifted mode DEFAULT for RAC_STATUS2        */
#define RAC_STATUS2_PREVSTATE3_OFF                                    (_RAC_STATUS2_PREVSTATE3_OFF << 8)        /**< Shifted mode OFF for RAC_STATUS2            */
#define RAC_STATUS2_PREVSTATE3_RXWARM                                 (_RAC_STATUS2_PREVSTATE3_RXWARM << 8)     /**< Shifted mode RXWARM for RAC_STATUS2         */
#define RAC_STATUS2_PREVSTATE3_RXSEARCH                               (_RAC_STATUS2_PREVSTATE3_RXSEARCH << 8)   /**< Shifted mode RXSEARCH for RAC_STATUS2       */
#define RAC_STATUS2_PREVSTATE3_RXFRAME                                (_RAC_STATUS2_PREVSTATE3_RXFRAME << 8)    /**< Shifted mode RXFRAME for RAC_STATUS2        */
#define RAC_STATUS2_PREVSTATE3_RXPD                                   (_RAC_STATUS2_PREVSTATE3_RXPD << 8)       /**< Shifted mode RXPD for RAC_STATUS2           */
#define RAC_STATUS2_PREVSTATE3_RX2RX                                  (_RAC_STATUS2_PREVSTATE3_RX2RX << 8)      /**< Shifted mode RX2RX for RAC_STATUS2          */
#define RAC_STATUS2_PREVSTATE3_RXOVERFLOW                             (_RAC_STATUS2_PREVSTATE3_RXOVERFLOW << 8) /**< Shifted mode RXOVERFLOW for RAC_STATUS2     */
#define RAC_STATUS2_PREVSTATE3_RX2TX                                  (_RAC_STATUS2_PREVSTATE3_RX2TX << 8)      /**< Shifted mode RX2TX for RAC_STATUS2          */
#define RAC_STATUS2_PREVSTATE3_TXWARM                                 (_RAC_STATUS2_PREVSTATE3_TXWARM << 8)     /**< Shifted mode TXWARM for RAC_STATUS2         */
#define RAC_STATUS2_PREVSTATE3_TX                                     (_RAC_STATUS2_PREVSTATE3_TX << 8)         /**< Shifted mode TX for RAC_STATUS2             */
#define RAC_STATUS2_PREVSTATE3_TXPD                                   (_RAC_STATUS2_PREVSTATE3_TXPD << 8)       /**< Shifted mode TXPD for RAC_STATUS2           */
#define RAC_STATUS2_PREVSTATE3_TX2RX                                  (_RAC_STATUS2_PREVSTATE3_TX2RX << 8)      /**< Shifted mode TX2RX for RAC_STATUS2          */
#define RAC_STATUS2_PREVSTATE3_TX2TX                                  (_RAC_STATUS2_PREVSTATE3_TX2TX << 8)      /**< Shifted mode TX2TX for RAC_STATUS2          */
#define RAC_STATUS2_PREVSTATE3_SHUTDOWN                               (_RAC_STATUS2_PREVSTATE3_SHUTDOWN << 8)   /**< Shifted mode SHUTDOWN for RAC_STATUS2       */
#define RAC_STATUS2_PREVSTATE3_POR                                    (_RAC_STATUS2_PREVSTATE3_POR << 8)        /**< Shifted mode POR for RAC_STATUS2            */
#define _RAC_STATUS2_CURRSTATE_SHIFT                                  12                                        /**< Shift value for RAC_CURRSTATE               */
#define _RAC_STATUS2_CURRSTATE_MASK                                   0xF000UL                                  /**< Bit mask for RAC_CURRSTATE                  */
#define _RAC_STATUS2_CURRSTATE_DEFAULT                                0x00000000UL                              /**< Mode DEFAULT for RAC_STATUS2                */
#define _RAC_STATUS2_CURRSTATE_OFF                                    0x00000000UL                              /**< Mode OFF for RAC_STATUS2                    */
#define _RAC_STATUS2_CURRSTATE_RXWARM                                 0x00000001UL                              /**< Mode RXWARM for RAC_STATUS2                 */
#define _RAC_STATUS2_CURRSTATE_RXSEARCH                               0x00000002UL                              /**< Mode RXSEARCH for RAC_STATUS2               */
#define _RAC_STATUS2_CURRSTATE_RXFRAME                                0x00000003UL                              /**< Mode RXFRAME for RAC_STATUS2                */
#define _RAC_STATUS2_CURRSTATE_RXPD                                   0x00000004UL                              /**< Mode RXPD for RAC_STATUS2                   */
#define _RAC_STATUS2_CURRSTATE_RX2RX                                  0x00000005UL                              /**< Mode RX2RX for RAC_STATUS2                  */
#define _RAC_STATUS2_CURRSTATE_RXOVERFLOW                             0x00000006UL                              /**< Mode RXOVERFLOW for RAC_STATUS2             */
#define _RAC_STATUS2_CURRSTATE_RX2TX                                  0x00000007UL                              /**< Mode RX2TX for RAC_STATUS2                  */
#define _RAC_STATUS2_CURRSTATE_TXWARM                                 0x00000008UL                              /**< Mode TXWARM for RAC_STATUS2                 */
#define _RAC_STATUS2_CURRSTATE_TX                                     0x00000009UL                              /**< Mode TX for RAC_STATUS2                     */
#define _RAC_STATUS2_CURRSTATE_TXPD                                   0x0000000AUL                              /**< Mode TXPD for RAC_STATUS2                   */
#define _RAC_STATUS2_CURRSTATE_TX2RX                                  0x0000000BUL                              /**< Mode TX2RX for RAC_STATUS2                  */
#define _RAC_STATUS2_CURRSTATE_TX2TX                                  0x0000000CUL                              /**< Mode TX2TX for RAC_STATUS2                  */
#define _RAC_STATUS2_CURRSTATE_SHUTDOWN                               0x0000000DUL                              /**< Mode SHUTDOWN for RAC_STATUS2               */
#define _RAC_STATUS2_CURRSTATE_POR                                    0x0000000EUL                              /**< Mode POR for RAC_STATUS2                    */
#define RAC_STATUS2_CURRSTATE_DEFAULT                                 (_RAC_STATUS2_CURRSTATE_DEFAULT << 12)    /**< Shifted mode DEFAULT for RAC_STATUS2        */
#define RAC_STATUS2_CURRSTATE_OFF                                     (_RAC_STATUS2_CURRSTATE_OFF << 12)        /**< Shifted mode OFF for RAC_STATUS2            */
#define RAC_STATUS2_CURRSTATE_RXWARM                                  (_RAC_STATUS2_CURRSTATE_RXWARM << 12)     /**< Shifted mode RXWARM for RAC_STATUS2         */
#define RAC_STATUS2_CURRSTATE_RXSEARCH                                (_RAC_STATUS2_CURRSTATE_RXSEARCH << 12)   /**< Shifted mode RXSEARCH for RAC_STATUS2       */
#define RAC_STATUS2_CURRSTATE_RXFRAME                                 (_RAC_STATUS2_CURRSTATE_RXFRAME << 12)    /**< Shifted mode RXFRAME for RAC_STATUS2        */
#define RAC_STATUS2_CURRSTATE_RXPD                                    (_RAC_STATUS2_CURRSTATE_RXPD << 12)       /**< Shifted mode RXPD for RAC_STATUS2           */
#define RAC_STATUS2_CURRSTATE_RX2RX                                   (_RAC_STATUS2_CURRSTATE_RX2RX << 12)      /**< Shifted mode RX2RX for RAC_STATUS2          */
#define RAC_STATUS2_CURRSTATE_RXOVERFLOW                              (_RAC_STATUS2_CURRSTATE_RXOVERFLOW << 12) /**< Shifted mode RXOVERFLOW for RAC_STATUS2     */
#define RAC_STATUS2_CURRSTATE_RX2TX                                   (_RAC_STATUS2_CURRSTATE_RX2TX << 12)      /**< Shifted mode RX2TX for RAC_STATUS2          */
#define RAC_STATUS2_CURRSTATE_TXWARM                                  (_RAC_STATUS2_CURRSTATE_TXWARM << 12)     /**< Shifted mode TXWARM for RAC_STATUS2         */
#define RAC_STATUS2_CURRSTATE_TX                                      (_RAC_STATUS2_CURRSTATE_TX << 12)         /**< Shifted mode TX for RAC_STATUS2             */
#define RAC_STATUS2_CURRSTATE_TXPD                                    (_RAC_STATUS2_CURRSTATE_TXPD << 12)       /**< Shifted mode TXPD for RAC_STATUS2           */
#define RAC_STATUS2_CURRSTATE_TX2RX                                   (_RAC_STATUS2_CURRSTATE_TX2RX << 12)      /**< Shifted mode TX2RX for RAC_STATUS2          */
#define RAC_STATUS2_CURRSTATE_TX2TX                                   (_RAC_STATUS2_CURRSTATE_TX2TX << 12)      /**< Shifted mode TX2TX for RAC_STATUS2          */
#define RAC_STATUS2_CURRSTATE_SHUTDOWN                                (_RAC_STATUS2_CURRSTATE_SHUTDOWN << 12)   /**< Shifted mode SHUTDOWN for RAC_STATUS2       */
#define RAC_STATUS2_CURRSTATE_POR                                     (_RAC_STATUS2_CURRSTATE_POR << 12)        /**< Shifted mode POR for RAC_STATUS2            */

/* Bit fields for RAC IFPGACTRL */
#define _RAC_IFPGACTRL_RESETVALUE                                     0x00000000UL                               /**< Default value for RAC_IFPGACTRL             */
#define _RAC_IFPGACTRL_MASK                                           0x0FF80000UL                               /**< Mask for RAC_IFPGACTRL                      */
#define RAC_IFPGACTRL_DCCALON                                         (0x1UL << 19)                              /**< Enable/Disable DCCAL in DEMOD               */
#define _RAC_IFPGACTRL_DCCALON_SHIFT                                  19                                         /**< Shift value for RAC_DCCALON                 */
#define _RAC_IFPGACTRL_DCCALON_MASK                                   0x80000UL                                  /**< Bit mask for RAC_DCCALON                    */
#define _RAC_IFPGACTRL_DCCALON_DEFAULT                                0x00000000UL                               /**< Mode DEFAULT for RAC_IFPGACTRL              */
#define _RAC_IFPGACTRL_DCCALON_DISABLE                                0x00000000UL                               /**< Mode DISABLE for RAC_IFPGACTRL              */
#define _RAC_IFPGACTRL_DCCALON_ENABLE                                 0x00000001UL                               /**< Mode ENABLE for RAC_IFPGACTRL               */
#define RAC_IFPGACTRL_DCCALON_DEFAULT                                 (_RAC_IFPGACTRL_DCCALON_DEFAULT << 19)     /**< Shifted mode DEFAULT for RAC_IFPGACTRL      */
#define RAC_IFPGACTRL_DCCALON_DISABLE                                 (_RAC_IFPGACTRL_DCCALON_DISABLE << 19)     /**< Shifted mode DISABLE for RAC_IFPGACTRL      */
#define RAC_IFPGACTRL_DCCALON_ENABLE                                  (_RAC_IFPGACTRL_DCCALON_ENABLE << 19)      /**< Shifted mode ENABLE for RAC_IFPGACTRL       */
#define RAC_IFPGACTRL_DCRSTEN                                         (0x1UL << 20)                              /**< DC Compensation Filter Reset Enable         */
#define _RAC_IFPGACTRL_DCRSTEN_SHIFT                                  20                                         /**< Shift value for RAC_DCRSTEN                 */
#define _RAC_IFPGACTRL_DCRSTEN_MASK                                   0x100000UL                                 /**< Bit mask for RAC_DCRSTEN                    */
#define _RAC_IFPGACTRL_DCRSTEN_DEFAULT                                0x00000000UL                               /**< Mode DEFAULT for RAC_IFPGACTRL              */
#define _RAC_IFPGACTRL_DCRSTEN_DISABLE                                0x00000000UL                               /**< Mode DISABLE for RAC_IFPGACTRL              */
#define _RAC_IFPGACTRL_DCRSTEN_ENABLE                                 0x00000001UL                               /**< Mode ENABLE for RAC_IFPGACTRL               */
#define RAC_IFPGACTRL_DCRSTEN_DEFAULT                                 (_RAC_IFPGACTRL_DCRSTEN_DEFAULT << 20)     /**< Shifted mode DEFAULT for RAC_IFPGACTRL      */
#define RAC_IFPGACTRL_DCRSTEN_DISABLE                                 (_RAC_IFPGACTRL_DCRSTEN_DISABLE << 20)     /**< Shifted mode DISABLE for RAC_IFPGACTRL      */
#define RAC_IFPGACTRL_DCRSTEN_ENABLE                                  (_RAC_IFPGACTRL_DCRSTEN_ENABLE << 20)      /**< Shifted mode ENABLE for RAC_IFPGACTRL       */
#define RAC_IFPGACTRL_DCESTIEN                                        (0x1UL << 21)                              /**< DCESTIEN Override for RAC                   */
#define _RAC_IFPGACTRL_DCESTIEN_SHIFT                                 21                                         /**< Shift value for RAC_DCESTIEN                */
#define _RAC_IFPGACTRL_DCESTIEN_MASK                                  0x200000UL                                 /**< Bit mask for RAC_DCESTIEN                   */
#define _RAC_IFPGACTRL_DCESTIEN_DEFAULT                               0x00000000UL                               /**< Mode DEFAULT for RAC_IFPGACTRL              */
#define _RAC_IFPGACTRL_DCESTIEN_DISABLE                               0x00000000UL                               /**< Mode DISABLE for RAC_IFPGACTRL              */
#define _RAC_IFPGACTRL_DCESTIEN_ENABLE                                0x00000001UL                               /**< Mode ENABLE for RAC_IFPGACTRL               */
#define RAC_IFPGACTRL_DCESTIEN_DEFAULT                                (_RAC_IFPGACTRL_DCESTIEN_DEFAULT << 21)    /**< Shifted mode DEFAULT for RAC_IFPGACTRL      */
#define RAC_IFPGACTRL_DCESTIEN_DISABLE                                (_RAC_IFPGACTRL_DCESTIEN_DISABLE << 21)    /**< Shifted mode DISABLE for RAC_IFPGACTRL      */
#define RAC_IFPGACTRL_DCESTIEN_ENABLE                                 (_RAC_IFPGACTRL_DCESTIEN_ENABLE << 21)     /**< Shifted mode ENABLE for RAC_IFPGACTRL       */
#define _RAC_IFPGACTRL_DCCALDEC0_SHIFT                                22                                         /**< Shift value for RAC_DCCALDEC0               */
#define _RAC_IFPGACTRL_DCCALDEC0_MASK                                 0x1C00000UL                                /**< Bit mask for RAC_DCCALDEC0                  */
#define _RAC_IFPGACTRL_DCCALDEC0_DEFAULT                              0x00000000UL                               /**< Mode DEFAULT for RAC_IFPGACTRL              */
#define _RAC_IFPGACTRL_DCCALDEC0_DF3                                  0x00000000UL                               /**< Mode DF3 for RAC_IFPGACTRL                  */
#define _RAC_IFPGACTRL_DCCALDEC0_DF4WIDE                              0x00000001UL                               /**< Mode DF4WIDE for RAC_IFPGACTRL              */
#define _RAC_IFPGACTRL_DCCALDEC0_DF4NARROW                            0x00000002UL                               /**< Mode DF4NARROW for RAC_IFPGACTRL            */
#define _RAC_IFPGACTRL_DCCALDEC0_DF8WIDE                              0x00000003UL                               /**< Mode DF8WIDE for RAC_IFPGACTRL              */
#define _RAC_IFPGACTRL_DCCALDEC0_DF8NARROW                            0x00000004UL                               /**< Mode DF8NARROW for RAC_IFPGACTRL            */
#define RAC_IFPGACTRL_DCCALDEC0_DEFAULT                               (_RAC_IFPGACTRL_DCCALDEC0_DEFAULT << 22)   /**< Shifted mode DEFAULT for RAC_IFPGACTRL      */
#define RAC_IFPGACTRL_DCCALDEC0_DF3                                   (_RAC_IFPGACTRL_DCCALDEC0_DF3 << 22)       /**< Shifted mode DF3 for RAC_IFPGACTRL          */
#define RAC_IFPGACTRL_DCCALDEC0_DF4WIDE                               (_RAC_IFPGACTRL_DCCALDEC0_DF4WIDE << 22)   /**< Shifted mode DF4WIDE for RAC_IFPGACTRL      */
#define RAC_IFPGACTRL_DCCALDEC0_DF4NARROW                             (_RAC_IFPGACTRL_DCCALDEC0_DF4NARROW << 22) /**< Shifted mode DF4NARROW for RAC_IFPGACTRL    */
#define RAC_IFPGACTRL_DCCALDEC0_DF8WIDE                               (_RAC_IFPGACTRL_DCCALDEC0_DF8WIDE << 22)   /**< Shifted mode DF8WIDE for RAC_IFPGACTRL      */
#define RAC_IFPGACTRL_DCCALDEC0_DF8NARROW                             (_RAC_IFPGACTRL_DCCALDEC0_DF8NARROW << 22) /**< Shifted mode DF8NARROW for RAC_IFPGACTRL    */
#define _RAC_IFPGACTRL_DCCALDCGEAR_SHIFT                              25                                         /**< Shift value for RAC_DCCALDCGEAR             */
#define _RAC_IFPGACTRL_DCCALDCGEAR_MASK                               0xE000000UL                                /**< Bit mask for RAC_DCCALDCGEAR                */
#define _RAC_IFPGACTRL_DCCALDCGEAR_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for RAC_IFPGACTRL              */
#define RAC_IFPGACTRL_DCCALDCGEAR_DEFAULT                             (_RAC_IFPGACTRL_DCCALDCGEAR_DEFAULT << 25) /**< Shifted mode DEFAULT for RAC_IFPGACTRL      */

/* Bit fields for RAC PAENCTRL */
#define _RAC_PAENCTRL_RESETVALUE                                      0x00000000UL                                 /**< Default value for RAC_PAENCTRL              */
#define _RAC_PAENCTRL_MASK                                            0x00070100UL                                 /**< Mask for RAC_PAENCTRL                       */
#define RAC_PAENCTRL_PARAMP                                           (0x1UL << 8)                                 /**< PA output level ramping                     */
#define _RAC_PAENCTRL_PARAMP_SHIFT                                    8                                            /**< Shift value for RAC_PARAMP                  */
#define _RAC_PAENCTRL_PARAMP_MASK                                     0x100UL                                      /**< Bit mask for RAC_PARAMP                     */
#define _RAC_PAENCTRL_PARAMP_DEFAULT                                  0x00000000UL                                 /**< Mode DEFAULT for RAC_PAENCTRL               */
#define RAC_PAENCTRL_PARAMP_DEFAULT                                   (_RAC_PAENCTRL_PARAMP_DEFAULT << 8)          /**< Shifted mode DEFAULT for RAC_PAENCTRL       */
#define RAC_PAENCTRL_INVRAMPCLK                                       (0x1UL << 16)                                /**< Invert PA ramping clock                     */
#define _RAC_PAENCTRL_INVRAMPCLK_SHIFT                                16                                           /**< Shift value for RAC_INVRAMPCLK              */
#define _RAC_PAENCTRL_INVRAMPCLK_MASK                                 0x10000UL                                    /**< Bit mask for RAC_INVRAMPCLK                 */
#define _RAC_PAENCTRL_INVRAMPCLK_DEFAULT                              0x00000000UL                                 /**< Mode DEFAULT for RAC_PAENCTRL               */
#define RAC_PAENCTRL_INVRAMPCLK_DEFAULT                               (_RAC_PAENCTRL_INVRAMPCLK_DEFAULT << 16)     /**< Shifted mode DEFAULT for RAC_PAENCTRL       */
#define RAC_PAENCTRL_DIV2RAMPCLK                                      (0x1UL << 17)                                /**< Div PA ramping clock by 2                   */
#define _RAC_PAENCTRL_DIV2RAMPCLK_SHIFT                               17                                           /**< Shift value for RAC_DIV2RAMPCLK             */
#define _RAC_PAENCTRL_DIV2RAMPCLK_MASK                                0x20000UL                                    /**< Bit mask for RAC_DIV2RAMPCLK                */
#define _RAC_PAENCTRL_DIV2RAMPCLK_DEFAULT                             0x00000000UL                                 /**< Mode DEFAULT for RAC_PAENCTRL               */
#define RAC_PAENCTRL_DIV2RAMPCLK_DEFAULT                              (_RAC_PAENCTRL_DIV2RAMPCLK_DEFAULT << 17)    /**< Shifted mode DEFAULT for RAC_PAENCTRL       */
#define RAC_PAENCTRL_RSTDIV2RAMPCLK                                   (0x1UL << 18)                                /**< Reset Div2 PA ramping clock                 */
#define _RAC_PAENCTRL_RSTDIV2RAMPCLK_SHIFT                            18                                           /**< Shift value for RAC_RSTDIV2RAMPCLK          */
#define _RAC_PAENCTRL_RSTDIV2RAMPCLK_MASK                             0x40000UL                                    /**< Bit mask for RAC_RSTDIV2RAMPCLK             */
#define _RAC_PAENCTRL_RSTDIV2RAMPCLK_DEFAULT                          0x00000000UL                                 /**< Mode DEFAULT for RAC_PAENCTRL               */
#define RAC_PAENCTRL_RSTDIV2RAMPCLK_DEFAULT                           (_RAC_PAENCTRL_RSTDIV2RAMPCLK_DEFAULT << 18) /**< Shifted mode DEFAULT for RAC_PAENCTRL       */

/* Bit fields for RAC APC */
#define _RAC_APC_RESETVALUE                                           0xFF000000UL                               /**< Default value for RAC_APC                   */
#define _RAC_APC_MASK                                                 0xFF000004UL                               /**< Mask for RAC_APC                            */
#define RAC_APC_ENAPCSW                                               (0x1UL << 2)                               /**< software control bit for apc                */
#define _RAC_APC_ENAPCSW_SHIFT                                        2                                          /**< Shift value for RAC_ENAPCSW                 */
#define _RAC_APC_ENAPCSW_MASK                                         0x4UL                                      /**< Bit mask for RAC_ENAPCSW                    */
#define _RAC_APC_ENAPCSW_DEFAULT                                      0x00000000UL                               /**< Mode DEFAULT for RAC_APC                    */
#define _RAC_APC_ENAPCSW_DISABLE                                      0x00000000UL                               /**< Mode DISABLE for RAC_APC                    */
#define _RAC_APC_ENAPCSW_ENABLE                                       0x00000001UL                               /**< Mode ENABLE for RAC_APC                     */
#define RAC_APC_ENAPCSW_DEFAULT                                       (_RAC_APC_ENAPCSW_DEFAULT << 2)            /**< Shifted mode DEFAULT for RAC_APC            */
#define RAC_APC_ENAPCSW_DISABLE                                       (_RAC_APC_ENAPCSW_DISABLE << 2)            /**< Shifted mode DISABLE for RAC_APC            */
#define RAC_APC_ENAPCSW_ENABLE                                        (_RAC_APC_ENAPCSW_ENABLE << 2)             /**< Shifted mode ENABLE for RAC_APC             */
#define _RAC_APC_AMPCONTROLLIMITSW_SHIFT                              24                                         /**< Shift value for RAC_AMPCONTROLLIMITSW       */
#define _RAC_APC_AMPCONTROLLIMITSW_MASK                               0xFF000000UL                               /**< Bit mask for RAC_AMPCONTROLLIMITSW          */
#define _RAC_APC_AMPCONTROLLIMITSW_DEFAULT                            0x000000FFUL                               /**< Mode DEFAULT for RAC_APC                    */
#define RAC_APC_AMPCONTROLLIMITSW_DEFAULT                             (_RAC_APC_AMPCONTROLLIMITSW_DEFAULT << 24) /**< Shifted mode DEFAULT for RAC_APC            */

/* Bit fields for RAC ANTDIV */
#define _RAC_ANTDIV_RESETVALUE                                        0x00000000UL                                      /**< Default value for RAC_ANTDIV                */
#define _RAC_ANTDIV_MASK                                              0x00000FBDUL                                      /**< Mask for RAC_ANTDIV                         */
#define RAC_ANTDIV_INTDIVLNAMIXEN0                                    (0x1UL << 0)                                      /**< INTDIVLNAMIXEN0                             */
#define _RAC_ANTDIV_INTDIVLNAMIXEN0_SHIFT                             0                                                 /**< Shift value for RAC_INTDIVLNAMIXEN0         */
#define _RAC_ANTDIV_INTDIVLNAMIXEN0_MASK                              0x1UL                                             /**< Bit mask for RAC_INTDIVLNAMIXEN0            */
#define _RAC_ANTDIV_INTDIVLNAMIXEN0_DEFAULT                           0x00000000UL                                      /**< Mode DEFAULT for RAC_ANTDIV                 */
#define RAC_ANTDIV_INTDIVLNAMIXEN0_DEFAULT                            (_RAC_ANTDIV_INTDIVLNAMIXEN0_DEFAULT << 0)        /**< Shifted mode DEFAULT for RAC_ANTDIV         */
#define RAC_ANTDIV_INTDIVLNAMIXRFATTDCEN0                             (0x1UL << 2)                                      /**< INTDIVLNAMIXRFATTDCEN0                      */
#define _RAC_ANTDIV_INTDIVLNAMIXRFATTDCEN0_SHIFT                      2                                                 /**< Shift value for RAC_INTDIVLNAMIXRFATTDCEN0  */
#define _RAC_ANTDIV_INTDIVLNAMIXRFATTDCEN0_MASK                       0x4UL                                             /**< Bit mask for RAC_INTDIVLNAMIXRFATTDCEN0     */
#define _RAC_ANTDIV_INTDIVLNAMIXRFATTDCEN0_DEFAULT                    0x00000000UL                                      /**< Mode DEFAULT for RAC_ANTDIV                 */
#define RAC_ANTDIV_INTDIVLNAMIXRFATTDCEN0_DEFAULT                     (_RAC_ANTDIV_INTDIVLNAMIXRFATTDCEN0_DEFAULT << 2) /**< Shifted mode DEFAULT for RAC_ANTDIV         */
#define RAC_ANTDIV_INTDIVLNAMIXRFPKDENRF0                             (0x1UL << 3)                                      /**< INTDIVLNAMIXRFPKDENRF0                      */
#define _RAC_ANTDIV_INTDIVLNAMIXRFPKDENRF0_SHIFT                      3                                                 /**< Shift value for RAC_INTDIVLNAMIXRFPKDENRF0  */
#define _RAC_ANTDIV_INTDIVLNAMIXRFPKDENRF0_MASK                       0x8UL                                             /**< Bit mask for RAC_INTDIVLNAMIXRFPKDENRF0     */
#define _RAC_ANTDIV_INTDIVLNAMIXRFPKDENRF0_DEFAULT                    0x00000000UL                                      /**< Mode DEFAULT for RAC_ANTDIV                 */
#define RAC_ANTDIV_INTDIVLNAMIXRFPKDENRF0_DEFAULT                     (_RAC_ANTDIV_INTDIVLNAMIXRFPKDENRF0_DEFAULT << 3) /**< Shifted mode DEFAULT for RAC_ANTDIV         */
#define RAC_ANTDIV_INTDIVSYLODIVRLO02G4EN                             (0x1UL << 4)                                      /**< INTDIVSYLODIVRLO02G4EN                      */
#define _RAC_ANTDIV_INTDIVSYLODIVRLO02G4EN_SHIFT                      4                                                 /**< Shift value for RAC_INTDIVSYLODIVRLO02G4EN  */
#define _RAC_ANTDIV_INTDIVSYLODIVRLO02G4EN_MASK                       0x10UL                                            /**< Bit mask for RAC_INTDIVSYLODIVRLO02G4EN     */
#define _RAC_ANTDIV_INTDIVSYLODIVRLO02G4EN_DEFAULT                    0x00000000UL                                      /**< Mode DEFAULT for RAC_ANTDIV                 */
#define RAC_ANTDIV_INTDIVSYLODIVRLO02G4EN_DEFAULT                     (_RAC_ANTDIV_INTDIVSYLODIVRLO02G4EN_DEFAULT << 4) /**< Shifted mode DEFAULT for RAC_ANTDIV         */
#define RAC_ANTDIV_INTDIVLNAMIXEN1                                    (0x1UL << 5)                                      /**< INTDIVLNAMIXEN1                             */
#define _RAC_ANTDIV_INTDIVLNAMIXEN1_SHIFT                             5                                                 /**< Shift value for RAC_INTDIVLNAMIXEN1         */
#define _RAC_ANTDIV_INTDIVLNAMIXEN1_MASK                              0x20UL                                            /**< Bit mask for RAC_INTDIVLNAMIXEN1            */
#define _RAC_ANTDIV_INTDIVLNAMIXEN1_DEFAULT                           0x00000000UL                                      /**< Mode DEFAULT for RAC_ANTDIV                 */
#define RAC_ANTDIV_INTDIVLNAMIXEN1_DEFAULT                            (_RAC_ANTDIV_INTDIVLNAMIXEN1_DEFAULT << 5)        /**< Shifted mode DEFAULT for RAC_ANTDIV         */
#define RAC_ANTDIV_INTDIVLNAMIXRFATTDCEN1                             (0x1UL << 7)                                      /**< INTDIVLNAMIXRFATTDCEN1                      */
#define _RAC_ANTDIV_INTDIVLNAMIXRFATTDCEN1_SHIFT                      7                                                 /**< Shift value for RAC_INTDIVLNAMIXRFATTDCEN1  */
#define _RAC_ANTDIV_INTDIVLNAMIXRFATTDCEN1_MASK                       0x80UL                                            /**< Bit mask for RAC_INTDIVLNAMIXRFATTDCEN1     */
#define _RAC_ANTDIV_INTDIVLNAMIXRFATTDCEN1_DEFAULT                    0x00000000UL                                      /**< Mode DEFAULT for RAC_ANTDIV                 */
#define RAC_ANTDIV_INTDIVLNAMIXRFATTDCEN1_DEFAULT                     (_RAC_ANTDIV_INTDIVLNAMIXRFATTDCEN1_DEFAULT << 7) /**< Shifted mode DEFAULT for RAC_ANTDIV         */
#define RAC_ANTDIV_INTDIVLNAMIXRFPKDENRF1                             (0x1UL << 8)                                      /**< INTDIVLNAMIXRFPKDENRF1                      */
#define _RAC_ANTDIV_INTDIVLNAMIXRFPKDENRF1_SHIFT                      8                                                 /**< Shift value for RAC_INTDIVLNAMIXRFPKDENRF1  */
#define _RAC_ANTDIV_INTDIVLNAMIXRFPKDENRF1_MASK                       0x100UL                                           /**< Bit mask for RAC_INTDIVLNAMIXRFPKDENRF1     */
#define _RAC_ANTDIV_INTDIVLNAMIXRFPKDENRF1_DEFAULT                    0x00000000UL                                      /**< Mode DEFAULT for RAC_ANTDIV                 */
#define RAC_ANTDIV_INTDIVLNAMIXRFPKDENRF1_DEFAULT                     (_RAC_ANTDIV_INTDIVLNAMIXRFPKDENRF1_DEFAULT << 8) /**< Shifted mode DEFAULT for RAC_ANTDIV         */
#define RAC_ANTDIV_INTDIVSYLODIVRLO12G4EN                             (0x1UL << 9)                                      /**< INTDIVSYLODIVRLO12G4EN                      */
#define _RAC_ANTDIV_INTDIVSYLODIVRLO12G4EN_SHIFT                      9                                                 /**< Shift value for RAC_INTDIVSYLODIVRLO12G4EN  */
#define _RAC_ANTDIV_INTDIVSYLODIVRLO12G4EN_MASK                       0x200UL                                           /**< Bit mask for RAC_INTDIVSYLODIVRLO12G4EN     */
#define _RAC_ANTDIV_INTDIVSYLODIVRLO12G4EN_DEFAULT                    0x00000000UL                                      /**< Mode DEFAULT for RAC_ANTDIV                 */
#define RAC_ANTDIV_INTDIVSYLODIVRLO12G4EN_DEFAULT                     (_RAC_ANTDIV_INTDIVSYLODIVRLO12G4EN_DEFAULT << 9) /**< Shifted mode DEFAULT for RAC_ANTDIV         */
#define _RAC_ANTDIV_ANTDIVSTATUS_SHIFT                                10                                                /**< Shift value for RAC_ANTDIVSTATUS            */
#define _RAC_ANTDIV_ANTDIVSTATUS_MASK                                 0xC00UL                                           /**< Bit mask for RAC_ANTDIVSTATUS               */
#define _RAC_ANTDIV_ANTDIVSTATUS_DEFAULT                              0x00000000UL                                      /**< Mode DEFAULT for RAC_ANTDIV                 */
#define _RAC_ANTDIV_ANTDIVSTATUS_OFF                                  0x00000000UL                                      /**< Mode OFF for RAC_ANTDIV                     */
#define _RAC_ANTDIV_ANTDIVSTATUS_ANT1                                 0x00000001UL                                      /**< Mode ANT1 for RAC_ANTDIV                    */
#define _RAC_ANTDIV_ANTDIVSTATUS_ANT2                                 0x00000002UL                                      /**< Mode ANT2 for RAC_ANTDIV                    */
#define _RAC_ANTDIV_ANTDIVSTATUS_BOTH                                 0x00000003UL                                      /**< Mode BOTH for RAC_ANTDIV                    */
#define RAC_ANTDIV_ANTDIVSTATUS_DEFAULT                               (_RAC_ANTDIV_ANTDIVSTATUS_DEFAULT << 10)          /**< Shifted mode DEFAULT for RAC_ANTDIV         */
#define RAC_ANTDIV_ANTDIVSTATUS_OFF                                   (_RAC_ANTDIV_ANTDIVSTATUS_OFF << 10)              /**< Shifted mode OFF for RAC_ANTDIV             */
#define RAC_ANTDIV_ANTDIVSTATUS_ANT1                                  (_RAC_ANTDIV_ANTDIVSTATUS_ANT1 << 10)             /**< Shifted mode ANT1 for RAC_ANTDIV            */
#define RAC_ANTDIV_ANTDIVSTATUS_ANT2                                  (_RAC_ANTDIV_ANTDIVSTATUS_ANT2 << 10)             /**< Shifted mode ANT2 for RAC_ANTDIV            */
#define RAC_ANTDIV_ANTDIVSTATUS_BOTH                                  (_RAC_ANTDIV_ANTDIVSTATUS_BOTH << 10)             /**< Shifted mode BOTH for RAC_ANTDIV            */

/* Bit fields for RAC AUXADCTRIM */
#define _RAC_AUXADCTRIM_RESETVALUE                                    0x06D55502UL                                                     /**< Default value for RAC_AUXADCTRIM            */
#define _RAC_AUXADCTRIM_MASK                                          0x1FFFFFFFUL                                                     /**< Mask for RAC_AUXADCTRIM                     */
#define RAC_AUXADCTRIM_AUXADCCLKINVERT                                (0x1UL << 0)                                                     /**< AUXADCCLKINVERT                             */
#define _RAC_AUXADCTRIM_AUXADCCLKINVERT_SHIFT                         0                                                                /**< Shift value for RAC_AUXADCCLKINVERT         */
#define _RAC_AUXADCTRIM_AUXADCCLKINVERT_MASK                          0x1UL                                                            /**< Bit mask for RAC_AUXADCCLKINVERT            */
#define _RAC_AUXADCTRIM_AUXADCCLKINVERT_DEFAULT                       0x00000000UL                                                     /**< Mode DEFAULT for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCCLKINVERT_Disable_Invert                0x00000000UL                                                     /**< Mode Disable_Invert for RAC_AUXADCTRIM      */
#define _RAC_AUXADCTRIM_AUXADCCLKINVERT_Enable_Invert                 0x00000001UL                                                     /**< Mode Enable_Invert for RAC_AUXADCTRIM       */
#define RAC_AUXADCTRIM_AUXADCCLKINVERT_DEFAULT                        (_RAC_AUXADCTRIM_AUXADCCLKINVERT_DEFAULT << 0)                   /**< Shifted mode DEFAULT for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCCLKINVERT_Disable_Invert                 (_RAC_AUXADCTRIM_AUXADCCLKINVERT_Disable_Invert << 0)            /**< Shifted mode Disable_Invert for RAC_AUXADCTRIM*/
#define RAC_AUXADCTRIM_AUXADCCLKINVERT_Enable_Invert                  (_RAC_AUXADCTRIM_AUXADCCLKINVERT_Enable_Invert << 0)             /**< Shifted mode Enable_Invert for RAC_AUXADCTRIM*/
#define _RAC_AUXADCTRIM_AUXADCLDOVREFTRIM_SHIFT                       1                                                                /**< Shift value for RAC_AUXADCLDOVREFTRIM       */
#define _RAC_AUXADCTRIM_AUXADCLDOVREFTRIM_MASK                        0x6UL                                                            /**< Bit mask for RAC_AUXADCLDOVREFTRIM          */
#define _RAC_AUXADCTRIM_AUXADCLDOVREFTRIM_DEFAULT                     0x00000001UL                                                     /**< Mode DEFAULT for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCLDOVREFTRIM_TRIM1p27                    0x00000000UL                                                     /**< Mode TRIM1p27 for RAC_AUXADCTRIM            */
#define _RAC_AUXADCTRIM_AUXADCLDOVREFTRIM_TRIM1p3                     0x00000001UL                                                     /**< Mode TRIM1p3 for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCLDOVREFTRIM_TRIM1p35                    0x00000002UL                                                     /**< Mode TRIM1p35 for RAC_AUXADCTRIM            */
#define _RAC_AUXADCTRIM_AUXADCLDOVREFTRIM_TRIM1p4                     0x00000003UL                                                     /**< Mode TRIM1p4 for RAC_AUXADCTRIM             */
#define RAC_AUXADCTRIM_AUXADCLDOVREFTRIM_DEFAULT                      (_RAC_AUXADCTRIM_AUXADCLDOVREFTRIM_DEFAULT << 1)                 /**< Shifted mode DEFAULT for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCLDOVREFTRIM_TRIM1p27                     (_RAC_AUXADCTRIM_AUXADCLDOVREFTRIM_TRIM1p27 << 1)                /**< Shifted mode TRIM1p27 for RAC_AUXADCTRIM    */
#define RAC_AUXADCTRIM_AUXADCLDOVREFTRIM_TRIM1p3                      (_RAC_AUXADCTRIM_AUXADCLDOVREFTRIM_TRIM1p3 << 1)                 /**< Shifted mode TRIM1p3 for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCLDOVREFTRIM_TRIM1p35                     (_RAC_AUXADCTRIM_AUXADCLDOVREFTRIM_TRIM1p35 << 1)                /**< Shifted mode TRIM1p35 for RAC_AUXADCTRIM    */
#define RAC_AUXADCTRIM_AUXADCLDOVREFTRIM_TRIM1p4                      (_RAC_AUXADCTRIM_AUXADCLDOVREFTRIM_TRIM1p4 << 1)                 /**< Shifted mode TRIM1p4 for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCOUTPUTINVERT                             (0x1UL << 3)                                                     /**< AUXADCOUTPUTINVERT                          */
#define _RAC_AUXADCTRIM_AUXADCOUTPUTINVERT_SHIFT                      3                                                                /**< Shift value for RAC_AUXADCOUTPUTINVERT      */
#define _RAC_AUXADCTRIM_AUXADCOUTPUTINVERT_MASK                       0x8UL                                                            /**< Bit mask for RAC_AUXADCOUTPUTINVERT         */
#define _RAC_AUXADCTRIM_AUXADCOUTPUTINVERT_DEFAULT                    0x00000000UL                                                     /**< Mode DEFAULT for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCOUTPUTINVERT_Disabled                   0x00000000UL                                                     /**< Mode Disabled for RAC_AUXADCTRIM            */
#define _RAC_AUXADCTRIM_AUXADCOUTPUTINVERT_Enabled                    0x00000001UL                                                     /**< Mode Enabled for RAC_AUXADCTRIM             */
#define RAC_AUXADCTRIM_AUXADCOUTPUTINVERT_DEFAULT                     (_RAC_AUXADCTRIM_AUXADCOUTPUTINVERT_DEFAULT << 3)                /**< Shifted mode DEFAULT for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCOUTPUTINVERT_Disabled                    (_RAC_AUXADCTRIM_AUXADCOUTPUTINVERT_Disabled << 3)               /**< Shifted mode Disabled for RAC_AUXADCTRIM    */
#define RAC_AUXADCTRIM_AUXADCOUTPUTINVERT_Enabled                     (_RAC_AUXADCTRIM_AUXADCOUTPUTINVERT_Enabled << 3)                /**< Shifted mode Enabled for RAC_AUXADCTRIM     */
#define _RAC_AUXADCTRIM_AUXADCRCTUNE_SHIFT                            4                                                                /**< Shift value for RAC_AUXADCRCTUNE            */
#define _RAC_AUXADCTRIM_AUXADCRCTUNE_MASK                             0x1F0UL                                                          /**< Bit mask for RAC_AUXADCRCTUNE               */
#define _RAC_AUXADCTRIM_AUXADCRCTUNE_DEFAULT                          0x00000010UL                                                     /**< Mode DEFAULT for RAC_AUXADCTRIM             */
#define RAC_AUXADCTRIM_AUXADCRCTUNE_DEFAULT                           (_RAC_AUXADCTRIM_AUXADCRCTUNE_DEFAULT << 4)                      /**< Shifted mode DEFAULT for RAC_AUXADCTRIM     */
#define _RAC_AUXADCTRIM_AUXADCTRIMADCINPUTRES_SHIFT                   9                                                                /**< Shift value for RAC_AUXADCTRIMADCINPUTRES   */
#define _RAC_AUXADCTRIM_AUXADCTRIMADCINPUTRES_MASK                    0x600UL                                                          /**< Bit mask for RAC_AUXADCTRIMADCINPUTRES      */
#define _RAC_AUXADCTRIM_AUXADCTRIMADCINPUTRES_DEFAULT                 0x00000002UL                                                     /**< Mode DEFAULT for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCTRIMADCINPUTRES_RES200k                 0x00000000UL                                                     /**< Mode RES200k for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCTRIMADCINPUTRES_RES250k                 0x00000001UL                                                     /**< Mode RES250k for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCTRIMADCINPUTRES_RES300k                 0x00000002UL                                                     /**< Mode RES300k for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCTRIMADCINPUTRES_RES350k                 0x00000003UL                                                     /**< Mode RES350k for RAC_AUXADCTRIM             */
#define RAC_AUXADCTRIM_AUXADCTRIMADCINPUTRES_DEFAULT                  (_RAC_AUXADCTRIM_AUXADCTRIMADCINPUTRES_DEFAULT << 9)             /**< Shifted mode DEFAULT for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTRIMADCINPUTRES_RES200k                  (_RAC_AUXADCTRIM_AUXADCTRIMADCINPUTRES_RES200k << 9)             /**< Shifted mode RES200k for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTRIMADCINPUTRES_RES250k                  (_RAC_AUXADCTRIM_AUXADCTRIMADCINPUTRES_RES250k << 9)             /**< Shifted mode RES250k for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTRIMADCINPUTRES_RES300k                  (_RAC_AUXADCTRIM_AUXADCTRIMADCINPUTRES_RES300k << 9)             /**< Shifted mode RES300k for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTRIMADCINPUTRES_RES350k                  (_RAC_AUXADCTRIM_AUXADCTRIMADCINPUTRES_RES350k << 9)             /**< Shifted mode RES350k for RAC_AUXADCTRIM     */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF_SHIFT                  11                                                               /**< Shift value for RAC_AUXADCTRIMCURRINPUTBUF  */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF_MASK                   0x1800UL                                                         /**< Bit mask for RAC_AUXADCTRIMCURRINPUTBUF     */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF_DEFAULT                0x00000002UL                                                     /**< Mode DEFAULT for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF_Typ_minus_40pct        0x00000000UL                                                     /**< Mode Typ_minus_40pct for RAC_AUXADCTRIM     */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF_Typ_minus_20pct        0x00000001UL                                                     /**< Mode Typ_minus_20pct for RAC_AUXADCTRIM     */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF_Typ                    0x00000002UL                                                     /**< Mode Typ for RAC_AUXADCTRIM                 */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF_Typ_plus_20pct         0x00000003UL                                                     /**< Mode Typ_plus_20pct for RAC_AUXADCTRIM      */
#define RAC_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF_DEFAULT                 (_RAC_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF_DEFAULT << 11)           /**< Shifted mode DEFAULT for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF_Typ_minus_40pct         (_RAC_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF_Typ_minus_40pct << 11)   /**< Shifted mode Typ_minus_40pct for RAC_AUXADCTRIM*/
#define RAC_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF_Typ_minus_20pct         (_RAC_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF_Typ_minus_20pct << 11)   /**< Shifted mode Typ_minus_20pct for RAC_AUXADCTRIM*/
#define RAC_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF_Typ                     (_RAC_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF_Typ << 11)               /**< Shifted mode Typ for RAC_AUXADCTRIM         */
#define RAC_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF_Typ_plus_20pct          (_RAC_AUXADCTRIM_AUXADCTRIMCURRINPUTBUF_Typ_plus_20pct << 11)    /**< Shifted mode Typ_plus_20pct for RAC_AUXADCTRIM*/
#define _RAC_AUXADCTRIM_AUXADCTRIMCURROPA1_SHIFT                      13                                                               /**< Shift value for RAC_AUXADCTRIMCURROPA1      */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURROPA1_MASK                       0x6000UL                                                         /**< Bit mask for RAC_AUXADCTRIMCURROPA1         */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURROPA1_DEFAULT                    0x00000002UL                                                     /**< Mode DEFAULT for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURROPA1_Typ_minus_40pct            0x00000000UL                                                     /**< Mode Typ_minus_40pct for RAC_AUXADCTRIM     */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURROPA1_Typ_minus_20pct            0x00000001UL                                                     /**< Mode Typ_minus_20pct for RAC_AUXADCTRIM     */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURROPA1_Typ                        0x00000002UL                                                     /**< Mode Typ for RAC_AUXADCTRIM                 */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURROPA1_Typ_plus_20pct             0x00000003UL                                                     /**< Mode Typ_plus_20pct for RAC_AUXADCTRIM      */
#define RAC_AUXADCTRIM_AUXADCTRIMCURROPA1_DEFAULT                     (_RAC_AUXADCTRIM_AUXADCTRIMCURROPA1_DEFAULT << 13)               /**< Shifted mode DEFAULT for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTRIMCURROPA1_Typ_minus_40pct             (_RAC_AUXADCTRIM_AUXADCTRIMCURROPA1_Typ_minus_40pct << 13)       /**< Shifted mode Typ_minus_40pct for RAC_AUXADCTRIM*/
#define RAC_AUXADCTRIM_AUXADCTRIMCURROPA1_Typ_minus_20pct             (_RAC_AUXADCTRIM_AUXADCTRIMCURROPA1_Typ_minus_20pct << 13)       /**< Shifted mode Typ_minus_20pct for RAC_AUXADCTRIM*/
#define RAC_AUXADCTRIM_AUXADCTRIMCURROPA1_Typ                         (_RAC_AUXADCTRIM_AUXADCTRIMCURROPA1_Typ << 13)                   /**< Shifted mode Typ for RAC_AUXADCTRIM         */
#define RAC_AUXADCTRIM_AUXADCTRIMCURROPA1_Typ_plus_20pct              (_RAC_AUXADCTRIM_AUXADCTRIMCURROPA1_Typ_plus_20pct << 13)        /**< Shifted mode Typ_plus_20pct for RAC_AUXADCTRIM*/
#define _RAC_AUXADCTRIM_AUXADCTRIMCURROPA2_SHIFT                      15                                                               /**< Shift value for RAC_AUXADCTRIMCURROPA2      */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURROPA2_MASK                       0x18000UL                                                        /**< Bit mask for RAC_AUXADCTRIMCURROPA2         */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURROPA2_DEFAULT                    0x00000002UL                                                     /**< Mode DEFAULT for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURROPA2_Typ_minus_40pct            0x00000000UL                                                     /**< Mode Typ_minus_40pct for RAC_AUXADCTRIM     */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURROPA2_Typ_minus_20pct            0x00000001UL                                                     /**< Mode Typ_minus_20pct for RAC_AUXADCTRIM     */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURROPA2_Typ                        0x00000002UL                                                     /**< Mode Typ for RAC_AUXADCTRIM                 */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURROPA2_Typ_plus_20pct             0x00000003UL                                                     /**< Mode Typ_plus_20pct for RAC_AUXADCTRIM      */
#define RAC_AUXADCTRIM_AUXADCTRIMCURROPA2_DEFAULT                     (_RAC_AUXADCTRIM_AUXADCTRIMCURROPA2_DEFAULT << 15)               /**< Shifted mode DEFAULT for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTRIMCURROPA2_Typ_minus_40pct             (_RAC_AUXADCTRIM_AUXADCTRIMCURROPA2_Typ_minus_40pct << 15)       /**< Shifted mode Typ_minus_40pct for RAC_AUXADCTRIM*/
#define RAC_AUXADCTRIM_AUXADCTRIMCURROPA2_Typ_minus_20pct             (_RAC_AUXADCTRIM_AUXADCTRIMCURROPA2_Typ_minus_20pct << 15)       /**< Shifted mode Typ_minus_20pct for RAC_AUXADCTRIM*/
#define RAC_AUXADCTRIM_AUXADCTRIMCURROPA2_Typ                         (_RAC_AUXADCTRIM_AUXADCTRIMCURROPA2_Typ << 15)                   /**< Shifted mode Typ for RAC_AUXADCTRIM         */
#define RAC_AUXADCTRIM_AUXADCTRIMCURROPA2_Typ_plus_20pct              (_RAC_AUXADCTRIM_AUXADCTRIMCURROPA2_Typ_plus_20pct << 15)        /**< Shifted mode Typ_plus_20pct for RAC_AUXADCTRIM*/
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRREFBUF_SHIFT                    17                                                               /**< Shift value for RAC_AUXADCTRIMCURRREFBUF    */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRREFBUF_MASK                     0x60000UL                                                        /**< Bit mask for RAC_AUXADCTRIMCURRREFBUF       */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRREFBUF_DEFAULT                  0x00000002UL                                                     /**< Mode DEFAULT for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRREFBUF_Typ_minus_40pct          0x00000000UL                                                     /**< Mode Typ_minus_40pct for RAC_AUXADCTRIM     */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRREFBUF_Typ_minus_20pct          0x00000001UL                                                     /**< Mode Typ_minus_20pct for RAC_AUXADCTRIM     */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRREFBUF_Typ                      0x00000002UL                                                     /**< Mode Typ for RAC_AUXADCTRIM                 */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRREFBUF_Typ_plus_20pct           0x00000003UL                                                     /**< Mode Typ_plus_20pct for RAC_AUXADCTRIM      */
#define RAC_AUXADCTRIM_AUXADCTRIMCURRREFBUF_DEFAULT                   (_RAC_AUXADCTRIM_AUXADCTRIMCURRREFBUF_DEFAULT << 17)             /**< Shifted mode DEFAULT for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTRIMCURRREFBUF_Typ_minus_40pct           (_RAC_AUXADCTRIM_AUXADCTRIMCURRREFBUF_Typ_minus_40pct << 17)     /**< Shifted mode Typ_minus_40pct for RAC_AUXADCTRIM*/
#define RAC_AUXADCTRIM_AUXADCTRIMCURRREFBUF_Typ_minus_20pct           (_RAC_AUXADCTRIM_AUXADCTRIMCURRREFBUF_Typ_minus_20pct << 17)     /**< Shifted mode Typ_minus_20pct for RAC_AUXADCTRIM*/
#define RAC_AUXADCTRIM_AUXADCTRIMCURRREFBUF_Typ                       (_RAC_AUXADCTRIM_AUXADCTRIMCURRREFBUF_Typ << 17)                 /**< Shifted mode Typ for RAC_AUXADCTRIM         */
#define RAC_AUXADCTRIM_AUXADCTRIMCURRREFBUF_Typ_plus_20pct            (_RAC_AUXADCTRIM_AUXADCTRIMCURRREFBUF_Typ_plus_20pct << 17)      /**< Shifted mode Typ_plus_20pct for RAC_AUXADCTRIM*/
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRTSENSE_SHIFT                    19                                                               /**< Shift value for RAC_AUXADCTRIMCURRTSENSE    */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRTSENSE_MASK                     0x180000UL                                                       /**< Bit mask for RAC_AUXADCTRIMCURRTSENSE       */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRTSENSE_DEFAULT                  0x00000002UL                                                     /**< Mode DEFAULT for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRTSENSE_Typ_minus_40pct          0x00000000UL                                                     /**< Mode Typ_minus_40pct for RAC_AUXADCTRIM     */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRTSENSE_Typ_minus_20pct          0x00000001UL                                                     /**< Mode Typ_minus_20pct for RAC_AUXADCTRIM     */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRTSENSE_Typ                      0x00000002UL                                                     /**< Mode Typ for RAC_AUXADCTRIM                 */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRTSENSE_Typ_plus_20pct           0x00000003UL                                                     /**< Mode Typ_plus_20pct for RAC_AUXADCTRIM      */
#define RAC_AUXADCTRIM_AUXADCTRIMCURRTSENSE_DEFAULT                   (_RAC_AUXADCTRIM_AUXADCTRIMCURRTSENSE_DEFAULT << 19)             /**< Shifted mode DEFAULT for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTRIMCURRTSENSE_Typ_minus_40pct           (_RAC_AUXADCTRIM_AUXADCTRIMCURRTSENSE_Typ_minus_40pct << 19)     /**< Shifted mode Typ_minus_40pct for RAC_AUXADCTRIM*/
#define RAC_AUXADCTRIM_AUXADCTRIMCURRTSENSE_Typ_minus_20pct           (_RAC_AUXADCTRIM_AUXADCTRIMCURRTSENSE_Typ_minus_20pct << 19)     /**< Shifted mode Typ_minus_20pct for RAC_AUXADCTRIM*/
#define RAC_AUXADCTRIM_AUXADCTRIMCURRTSENSE_Typ                       (_RAC_AUXADCTRIM_AUXADCTRIMCURRTSENSE_Typ << 19)                 /**< Shifted mode Typ for RAC_AUXADCTRIM         */
#define RAC_AUXADCTRIM_AUXADCTRIMCURRTSENSE_Typ_plus_20pct            (_RAC_AUXADCTRIM_AUXADCTRIMCURRTSENSE_Typ_plus_20pct << 19)      /**< Shifted mode Typ_plus_20pct for RAC_AUXADCTRIM*/
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRVCMBUF_SHIFT                    21                                                               /**< Shift value for RAC_AUXADCTRIMCURRVCMBUF    */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRVCMBUF_MASK                     0x600000UL                                                       /**< Bit mask for RAC_AUXADCTRIMCURRVCMBUF       */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRVCMBUF_DEFAULT                  0x00000002UL                                                     /**< Mode DEFAULT for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRVCMBUF_Typ_minus_40pct          0x00000000UL                                                     /**< Mode Typ_minus_40pct for RAC_AUXADCTRIM     */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRVCMBUF_Typ_minus_20pct          0x00000001UL                                                     /**< Mode Typ_minus_20pct for RAC_AUXADCTRIM     */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRVCMBUF_Typ                      0x00000002UL                                                     /**< Mode Typ for RAC_AUXADCTRIM                 */
#define _RAC_AUXADCTRIM_AUXADCTRIMCURRVCMBUF_Typ_plus_20pct           0x00000003UL                                                     /**< Mode Typ_plus_20pct for RAC_AUXADCTRIM      */
#define RAC_AUXADCTRIM_AUXADCTRIMCURRVCMBUF_DEFAULT                   (_RAC_AUXADCTRIM_AUXADCTRIMCURRVCMBUF_DEFAULT << 21)             /**< Shifted mode DEFAULT for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTRIMCURRVCMBUF_Typ_minus_40pct           (_RAC_AUXADCTRIM_AUXADCTRIMCURRVCMBUF_Typ_minus_40pct << 21)     /**< Shifted mode Typ_minus_40pct for RAC_AUXADCTRIM*/
#define RAC_AUXADCTRIM_AUXADCTRIMCURRVCMBUF_Typ_minus_20pct           (_RAC_AUXADCTRIM_AUXADCTRIMCURRVCMBUF_Typ_minus_20pct << 21)     /**< Shifted mode Typ_minus_20pct for RAC_AUXADCTRIM*/
#define RAC_AUXADCTRIM_AUXADCTRIMCURRVCMBUF_Typ                       (_RAC_AUXADCTRIM_AUXADCTRIMCURRVCMBUF_Typ << 21)                 /**< Shifted mode Typ for RAC_AUXADCTRIM         */
#define RAC_AUXADCTRIM_AUXADCTRIMCURRVCMBUF_Typ_plus_20pct            (_RAC_AUXADCTRIM_AUXADCTRIMCURRVCMBUF_Typ_plus_20pct << 21)      /**< Shifted mode Typ_plus_20pct for RAC_AUXADCTRIM*/
#define RAC_AUXADCTRIM_AUXADCTRIMLDOHIGHCURRENT                       (0x1UL << 23)                                                    /**< AUXADCTRIMLDOHIGHCURRENT                    */
#define _RAC_AUXADCTRIM_AUXADCTRIMLDOHIGHCURRENT_SHIFT                23                                                               /**< Shift value for RAC_AUXADCTRIMLDOHIGHCURRENT*/
#define _RAC_AUXADCTRIM_AUXADCTRIMLDOHIGHCURRENT_MASK                 0x800000UL                                                       /**< Bit mask for RAC_AUXADCTRIMLDOHIGHCURRENT   */
#define _RAC_AUXADCTRIM_AUXADCTRIMLDOHIGHCURRENT_DEFAULT              0x00000001UL                                                     /**< Mode DEFAULT for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCTRIMLDOHIGHCURRENT_LowCurrentMode       0x00000000UL                                                     /**< Mode LowCurrentMode for RAC_AUXADCTRIM      */
#define _RAC_AUXADCTRIM_AUXADCTRIMLDOHIGHCURRENT_HighCurrentMode      0x00000001UL                                                     /**< Mode HighCurrentMode for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTRIMLDOHIGHCURRENT_DEFAULT               (_RAC_AUXADCTRIM_AUXADCTRIMLDOHIGHCURRENT_DEFAULT << 23)         /**< Shifted mode DEFAULT for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTRIMLDOHIGHCURRENT_LowCurrentMode        (_RAC_AUXADCTRIM_AUXADCTRIMLDOHIGHCURRENT_LowCurrentMode << 23)  /**< Shifted mode LowCurrentMode for RAC_AUXADCTRIM*/
#define RAC_AUXADCTRIM_AUXADCTRIMLDOHIGHCURRENT_HighCurrentMode       (_RAC_AUXADCTRIM_AUXADCTRIMLDOHIGHCURRENT_HighCurrentMode << 23) /**< Shifted mode HighCurrentMode for RAC_AUXADCTRIM*/
#define _RAC_AUXADCTRIM_AUXADCTRIMREFP_SHIFT                          24                                                               /**< Shift value for RAC_AUXADCTRIMREFP          */
#define _RAC_AUXADCTRIM_AUXADCTRIMREFP_MASK                           0x3000000UL                                                      /**< Bit mask for RAC_AUXADCTRIMREFP             */
#define _RAC_AUXADCTRIM_AUXADCTRIMREFP_DEFAULT                        0x00000002UL                                                     /**< Mode DEFAULT for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCTRIMREFP_REF1p05                        0x00000000UL                                                     /**< Mode REF1p05 for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCTRIMREFP_REF1p16                        0x00000001UL                                                     /**< Mode REF1p16 for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCTRIMREFP_REF1p2                         0x00000002UL                                                     /**< Mode REF1p2 for RAC_AUXADCTRIM              */
#define _RAC_AUXADCTRIM_AUXADCTRIMREFP_REF1p25                        0x00000003UL                                                     /**< Mode REF1p25 for RAC_AUXADCTRIM             */
#define RAC_AUXADCTRIM_AUXADCTRIMREFP_DEFAULT                         (_RAC_AUXADCTRIM_AUXADCTRIMREFP_DEFAULT << 24)                   /**< Shifted mode DEFAULT for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTRIMREFP_REF1p05                         (_RAC_AUXADCTRIM_AUXADCTRIMREFP_REF1p05 << 24)                   /**< Shifted mode REF1p05 for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTRIMREFP_REF1p16                         (_RAC_AUXADCTRIM_AUXADCTRIMREFP_REF1p16 << 24)                   /**< Shifted mode REF1p16 for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTRIMREFP_REF1p2                          (_RAC_AUXADCTRIM_AUXADCTRIMREFP_REF1p2 << 24)                    /**< Shifted mode REF1p2 for RAC_AUXADCTRIM      */
#define RAC_AUXADCTRIM_AUXADCTRIMREFP_REF1p25                         (_RAC_AUXADCTRIM_AUXADCTRIMREFP_REF1p25 << 24)                   /**< Shifted mode REF1p25 for RAC_AUXADCTRIM     */
#define _RAC_AUXADCTRIM_AUXADCTRIMVREFVCM_SHIFT                       26                                                               /**< Shift value for RAC_AUXADCTRIMVREFVCM       */
#define _RAC_AUXADCTRIM_AUXADCTRIMVREFVCM_MASK                        0xC000000UL                                                      /**< Bit mask for RAC_AUXADCTRIMVREFVCM          */
#define _RAC_AUXADCTRIM_AUXADCTRIMVREFVCM_DEFAULT                     0x00000001UL                                                     /**< Mode DEFAULT for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCTRIMVREFVCM_Trim0p6                     0x00000000UL                                                     /**< Mode Trim0p6 for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCTRIMVREFVCM_Trim0p65                    0x00000001UL                                                     /**< Mode Trim0p65 for RAC_AUXADCTRIM            */
#define _RAC_AUXADCTRIM_AUXADCTRIMVREFVCM_Trim0p7                     0x00000002UL                                                     /**< Mode Trim0p7 for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCTRIMVREFVCM_Trim0p75                    0x00000003UL                                                     /**< Mode Trim0p75 for RAC_AUXADCTRIM            */
#define RAC_AUXADCTRIM_AUXADCTRIMVREFVCM_DEFAULT                      (_RAC_AUXADCTRIM_AUXADCTRIMVREFVCM_DEFAULT << 26)                /**< Shifted mode DEFAULT for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTRIMVREFVCM_Trim0p6                      (_RAC_AUXADCTRIM_AUXADCTRIMVREFVCM_Trim0p6 << 26)                /**< Shifted mode Trim0p6 for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTRIMVREFVCM_Trim0p65                     (_RAC_AUXADCTRIM_AUXADCTRIMVREFVCM_Trim0p65 << 26)               /**< Shifted mode Trim0p65 for RAC_AUXADCTRIM    */
#define RAC_AUXADCTRIM_AUXADCTRIMVREFVCM_Trim0p7                      (_RAC_AUXADCTRIM_AUXADCTRIMVREFVCM_Trim0p7 << 26)                /**< Shifted mode Trim0p7 for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTRIMVREFVCM_Trim0p75                     (_RAC_AUXADCTRIM_AUXADCTRIMVREFVCM_Trim0p75 << 26)               /**< Shifted mode Trim0p75 for RAC_AUXADCTRIM    */
#define RAC_AUXADCTRIM_AUXADCTSENSETRIMVBE2                           (0x1UL << 28)                                                    /**< AUXADCTSENSETRIMVBE2                        */
#define _RAC_AUXADCTRIM_AUXADCTSENSETRIMVBE2_SHIFT                    28                                                               /**< Shift value for RAC_AUXADCTSENSETRIMVBE2    */
#define _RAC_AUXADCTRIM_AUXADCTSENSETRIMVBE2_MASK                     0x10000000UL                                                     /**< Bit mask for RAC_AUXADCTSENSETRIMVBE2       */
#define _RAC_AUXADCTRIM_AUXADCTSENSETRIMVBE2_DEFAULT                  0x00000000UL                                                     /**< Mode DEFAULT for RAC_AUXADCTRIM             */
#define _RAC_AUXADCTRIM_AUXADCTSENSETRIMVBE2_VBE_16uA                 0x00000000UL                                                     /**< Mode VBE_16uA for RAC_AUXADCTRIM            */
#define _RAC_AUXADCTRIM_AUXADCTSENSETRIMVBE2_VBE_32uA                 0x00000001UL                                                     /**< Mode VBE_32uA for RAC_AUXADCTRIM            */
#define RAC_AUXADCTRIM_AUXADCTSENSETRIMVBE2_DEFAULT                   (_RAC_AUXADCTRIM_AUXADCTSENSETRIMVBE2_DEFAULT << 28)             /**< Shifted mode DEFAULT for RAC_AUXADCTRIM     */
#define RAC_AUXADCTRIM_AUXADCTSENSETRIMVBE2_VBE_16uA                  (_RAC_AUXADCTRIM_AUXADCTSENSETRIMVBE2_VBE_16uA << 28)            /**< Shifted mode VBE_16uA for RAC_AUXADCTRIM    */
#define RAC_AUXADCTRIM_AUXADCTSENSETRIMVBE2_VBE_32uA                  (_RAC_AUXADCTRIM_AUXADCTSENSETRIMVBE2_VBE_32uA << 28)            /**< Shifted mode VBE_32uA for RAC_AUXADCTRIM    */

/* Bit fields for RAC AUXADCEN */
#define _RAC_AUXADCEN_RESETVALUE                                      0x00000000UL                                              /**< Default value for RAC_AUXADCEN              */
#define _RAC_AUXADCEN_MASK                                            0x000003FFUL                                              /**< Mask for RAC_AUXADCEN                       */
#define RAC_AUXADCEN_AUXADCENAUXADC                                   (0x1UL << 0)                                              /**< AUXADCENAUXADC                              */
#define _RAC_AUXADCEN_AUXADCENAUXADC_SHIFT                            0                                                         /**< Shift value for RAC_AUXADCENAUXADC          */
#define _RAC_AUXADCEN_AUXADCENAUXADC_MASK                             0x1UL                                                     /**< Bit mask for RAC_AUXADCENAUXADC             */
#define _RAC_AUXADCEN_AUXADCENAUXADC_DEFAULT                          0x00000000UL                                              /**< Mode DEFAULT for RAC_AUXADCEN               */
#define _RAC_AUXADCEN_AUXADCENAUXADC_Disabled                         0x00000000UL                                              /**< Mode Disabled for RAC_AUXADCEN              */
#define _RAC_AUXADCEN_AUXADCENAUXADC_Enabled                          0x00000001UL                                              /**< Mode Enabled for RAC_AUXADCEN               */
#define RAC_AUXADCEN_AUXADCENAUXADC_DEFAULT                           (_RAC_AUXADCEN_AUXADCENAUXADC_DEFAULT << 0)               /**< Shifted mode DEFAULT for RAC_AUXADCEN       */
#define RAC_AUXADCEN_AUXADCENAUXADC_Disabled                          (_RAC_AUXADCEN_AUXADCENAUXADC_Disabled << 0)              /**< Shifted mode Disabled for RAC_AUXADCEN      */
#define RAC_AUXADCEN_AUXADCENAUXADC_Enabled                           (_RAC_AUXADCEN_AUXADCENAUXADC_Enabled << 0)               /**< Shifted mode Enabled for RAC_AUXADCEN       */
#define RAC_AUXADCEN_AUXADCENINPUTBUFFER                              (0x1UL << 1)                                              /**< AUXADCENINPUTBUFFER                         */
#define _RAC_AUXADCEN_AUXADCENINPUTBUFFER_SHIFT                       1                                                         /**< Shift value for RAC_AUXADCENINPUTBUFFER     */
#define _RAC_AUXADCEN_AUXADCENINPUTBUFFER_MASK                        0x2UL                                                     /**< Bit mask for RAC_AUXADCENINPUTBUFFER        */
#define _RAC_AUXADCEN_AUXADCENINPUTBUFFER_DEFAULT                     0x00000000UL                                              /**< Mode DEFAULT for RAC_AUXADCEN               */
#define _RAC_AUXADCEN_AUXADCENINPUTBUFFER_Disabled                    0x00000000UL                                              /**< Mode Disabled for RAC_AUXADCEN              */
#define _RAC_AUXADCEN_AUXADCENINPUTBUFFER_Enabled                     0x00000001UL                                              /**< Mode Enabled for RAC_AUXADCEN               */
#define RAC_AUXADCEN_AUXADCENINPUTBUFFER_DEFAULT                      (_RAC_AUXADCEN_AUXADCENINPUTBUFFER_DEFAULT << 1)          /**< Shifted mode DEFAULT for RAC_AUXADCEN       */
#define RAC_AUXADCEN_AUXADCENINPUTBUFFER_Disabled                     (_RAC_AUXADCEN_AUXADCENINPUTBUFFER_Disabled << 1)         /**< Shifted mode Disabled for RAC_AUXADCEN      */
#define RAC_AUXADCEN_AUXADCENINPUTBUFFER_Enabled                      (_RAC_AUXADCEN_AUXADCENINPUTBUFFER_Enabled << 1)          /**< Shifted mode Enabled for RAC_AUXADCEN       */
#define RAC_AUXADCEN_AUXADCENLDO                                      (0x1UL << 2)                                              /**< AUXADCENLDO                                 */
#define _RAC_AUXADCEN_AUXADCENLDO_SHIFT                               2                                                         /**< Shift value for RAC_AUXADCENLDO             */
#define _RAC_AUXADCEN_AUXADCENLDO_MASK                                0x4UL                                                     /**< Bit mask for RAC_AUXADCENLDO                */
#define _RAC_AUXADCEN_AUXADCENLDO_DEFAULT                             0x00000000UL                                              /**< Mode DEFAULT for RAC_AUXADCEN               */
#define _RAC_AUXADCEN_AUXADCENLDO_Disabled                            0x00000000UL                                              /**< Mode Disabled for RAC_AUXADCEN              */
#define _RAC_AUXADCEN_AUXADCENLDO_Enabled                             0x00000001UL                                              /**< Mode Enabled for RAC_AUXADCEN               */
#define RAC_AUXADCEN_AUXADCENLDO_DEFAULT                              (_RAC_AUXADCEN_AUXADCENLDO_DEFAULT << 2)                  /**< Shifted mode DEFAULT for RAC_AUXADCEN       */
#define RAC_AUXADCEN_AUXADCENLDO_Disabled                             (_RAC_AUXADCEN_AUXADCENLDO_Disabled << 2)                 /**< Shifted mode Disabled for RAC_AUXADCEN      */
#define RAC_AUXADCEN_AUXADCENLDO_Enabled                              (_RAC_AUXADCEN_AUXADCENLDO_Enabled << 2)                  /**< Shifted mode Enabled for RAC_AUXADCEN       */
#define RAC_AUXADCEN_AUXADCENOUTPUTDRV                                (0x1UL << 3)                                              /**< AUXADCENOUTPUTDRV                           */
#define _RAC_AUXADCEN_AUXADCENOUTPUTDRV_SHIFT                         3                                                         /**< Shift value for RAC_AUXADCENOUTPUTDRV       */
#define _RAC_AUXADCEN_AUXADCENOUTPUTDRV_MASK                          0x8UL                                                     /**< Bit mask for RAC_AUXADCENOUTPUTDRV          */
#define _RAC_AUXADCEN_AUXADCENOUTPUTDRV_DEFAULT                       0x00000000UL                                              /**< Mode DEFAULT for RAC_AUXADCEN               */
#define _RAC_AUXADCEN_AUXADCENOUTPUTDRV_Disabled                      0x00000000UL                                              /**< Mode Disabled for RAC_AUXADCEN              */
#define _RAC_AUXADCEN_AUXADCENOUTPUTDRV_Enabled                       0x00000001UL                                              /**< Mode Enabled for RAC_AUXADCEN               */
#define RAC_AUXADCEN_AUXADCENOUTPUTDRV_DEFAULT                        (_RAC_AUXADCEN_AUXADCENOUTPUTDRV_DEFAULT << 3)            /**< Shifted mode DEFAULT for RAC_AUXADCEN       */
#define RAC_AUXADCEN_AUXADCENOUTPUTDRV_Disabled                       (_RAC_AUXADCEN_AUXADCENOUTPUTDRV_Disabled << 3)           /**< Shifted mode Disabled for RAC_AUXADCEN      */
#define RAC_AUXADCEN_AUXADCENOUTPUTDRV_Enabled                        (_RAC_AUXADCEN_AUXADCENOUTPUTDRV_Enabled << 3)            /**< Shifted mode Enabled for RAC_AUXADCEN       */
#define RAC_AUXADCEN_AUXADCENPMON                                     (0x1UL << 4)                                              /**< AUXADCENPMON                                */
#define _RAC_AUXADCEN_AUXADCENPMON_SHIFT                              4                                                         /**< Shift value for RAC_AUXADCENPMON            */
#define _RAC_AUXADCEN_AUXADCENPMON_MASK                               0x10UL                                                    /**< Bit mask for RAC_AUXADCENPMON               */
#define _RAC_AUXADCEN_AUXADCENPMON_DEFAULT                            0x00000000UL                                              /**< Mode DEFAULT for RAC_AUXADCEN               */
#define _RAC_AUXADCEN_AUXADCENPMON_Disabled                           0x00000000UL                                              /**< Mode Disabled for RAC_AUXADCEN              */
#define _RAC_AUXADCEN_AUXADCENPMON_Enabled                            0x00000001UL                                              /**< Mode Enabled for RAC_AUXADCEN               */
#define RAC_AUXADCEN_AUXADCENPMON_DEFAULT                             (_RAC_AUXADCEN_AUXADCENPMON_DEFAULT << 4)                 /**< Shifted mode DEFAULT for RAC_AUXADCEN       */
#define RAC_AUXADCEN_AUXADCENPMON_Disabled                            (_RAC_AUXADCEN_AUXADCENPMON_Disabled << 4)                /**< Shifted mode Disabled for RAC_AUXADCEN      */
#define RAC_AUXADCEN_AUXADCENPMON_Enabled                             (_RAC_AUXADCEN_AUXADCENPMON_Enabled << 4)                 /**< Shifted mode Enabled for RAC_AUXADCEN       */
#define RAC_AUXADCEN_AUXADCENRESONDIAGA                               (0x1UL << 5)                                              /**< AUXADCENRESONDIAGA                          */
#define _RAC_AUXADCEN_AUXADCENRESONDIAGA_SHIFT                        5                                                         /**< Shift value for RAC_AUXADCENRESONDIAGA      */
#define _RAC_AUXADCEN_AUXADCENRESONDIAGA_MASK                         0x20UL                                                    /**< Bit mask for RAC_AUXADCENRESONDIAGA         */
#define _RAC_AUXADCEN_AUXADCENRESONDIAGA_DEFAULT                      0x00000000UL                                              /**< Mode DEFAULT for RAC_AUXADCEN               */
#define _RAC_AUXADCEN_AUXADCENRESONDIAGA_Disabled                     0x00000000UL                                              /**< Mode Disabled for RAC_AUXADCEN              */
#define _RAC_AUXADCEN_AUXADCENRESONDIAGA_Enabled                      0x00000001UL                                              /**< Mode Enabled for RAC_AUXADCEN               */
#define RAC_AUXADCEN_AUXADCENRESONDIAGA_DEFAULT                       (_RAC_AUXADCEN_AUXADCENRESONDIAGA_DEFAULT << 5)           /**< Shifted mode DEFAULT for RAC_AUXADCEN       */
#define RAC_AUXADCEN_AUXADCENRESONDIAGA_Disabled                      (_RAC_AUXADCEN_AUXADCENRESONDIAGA_Disabled << 5)          /**< Shifted mode Disabled for RAC_AUXADCEN      */
#define RAC_AUXADCEN_AUXADCENRESONDIAGA_Enabled                       (_RAC_AUXADCEN_AUXADCENRESONDIAGA_Enabled << 5)           /**< Shifted mode Enabled for RAC_AUXADCEN       */
#define RAC_AUXADCEN_AUXADCENTSENSE                                   (0x1UL << 6)                                              /**< AUXADCENTSENSE                              */
#define _RAC_AUXADCEN_AUXADCENTSENSE_SHIFT                            6                                                         /**< Shift value for RAC_AUXADCENTSENSE          */
#define _RAC_AUXADCEN_AUXADCENTSENSE_MASK                             0x40UL                                                    /**< Bit mask for RAC_AUXADCENTSENSE             */
#define _RAC_AUXADCEN_AUXADCENTSENSE_DEFAULT                          0x00000000UL                                              /**< Mode DEFAULT for RAC_AUXADCEN               */
#define _RAC_AUXADCEN_AUXADCENTSENSE_Disabled                         0x00000000UL                                              /**< Mode Disabled for RAC_AUXADCEN              */
#define _RAC_AUXADCEN_AUXADCENTSENSE_Enabled                          0x00000001UL                                              /**< Mode Enabled for RAC_AUXADCEN               */
#define RAC_AUXADCEN_AUXADCENTSENSE_DEFAULT                           (_RAC_AUXADCEN_AUXADCENTSENSE_DEFAULT << 6)               /**< Shifted mode DEFAULT for RAC_AUXADCEN       */
#define RAC_AUXADCEN_AUXADCENTSENSE_Disabled                          (_RAC_AUXADCEN_AUXADCENTSENSE_Disabled << 6)              /**< Shifted mode Disabled for RAC_AUXADCEN      */
#define RAC_AUXADCEN_AUXADCENTSENSE_Enabled                           (_RAC_AUXADCEN_AUXADCENTSENSE_Enabled << 6)               /**< Shifted mode Enabled for RAC_AUXADCEN       */
#define RAC_AUXADCEN_AUXADCENTSENSECAL                                (0x1UL << 7)                                              /**< AUXADCENTSENSECAL                           */
#define _RAC_AUXADCEN_AUXADCENTSENSECAL_SHIFT                         7                                                         /**< Shift value for RAC_AUXADCENTSENSECAL       */
#define _RAC_AUXADCEN_AUXADCENTSENSECAL_MASK                          0x80UL                                                    /**< Bit mask for RAC_AUXADCENTSENSECAL          */
#define _RAC_AUXADCEN_AUXADCENTSENSECAL_DEFAULT                       0x00000000UL                                              /**< Mode DEFAULT for RAC_AUXADCEN               */
#define _RAC_AUXADCEN_AUXADCENTSENSECAL_Disabled                      0x00000000UL                                              /**< Mode Disabled for RAC_AUXADCEN              */
#define _RAC_AUXADCEN_AUXADCENTSENSECAL_Enabled                       0x00000001UL                                              /**< Mode Enabled for RAC_AUXADCEN               */
#define RAC_AUXADCEN_AUXADCENTSENSECAL_DEFAULT                        (_RAC_AUXADCEN_AUXADCENTSENSECAL_DEFAULT << 7)            /**< Shifted mode DEFAULT for RAC_AUXADCEN       */
#define RAC_AUXADCEN_AUXADCENTSENSECAL_Disabled                       (_RAC_AUXADCEN_AUXADCENTSENSECAL_Disabled << 7)           /**< Shifted mode Disabled for RAC_AUXADCEN      */
#define RAC_AUXADCEN_AUXADCENTSENSECAL_Enabled                        (_RAC_AUXADCEN_AUXADCENTSENSECAL_Enabled << 7)            /**< Shifted mode Enabled for RAC_AUXADCEN       */
#define RAC_AUXADCEN_AUXADCINPUTBUFFERBYPASS                          (0x1UL << 8)                                              /**< AUXADCINPUTBUFFERBYPASS                     */
#define _RAC_AUXADCEN_AUXADCINPUTBUFFERBYPASS_SHIFT                   8                                                         /**< Shift value for RAC_AUXADCINPUTBUFFERBYPASS */
#define _RAC_AUXADCEN_AUXADCINPUTBUFFERBYPASS_MASK                    0x100UL                                                   /**< Bit mask for RAC_AUXADCINPUTBUFFERBYPASS    */
#define _RAC_AUXADCEN_AUXADCINPUTBUFFERBYPASS_DEFAULT                 0x00000000UL                                              /**< Mode DEFAULT for RAC_AUXADCEN               */
#define _RAC_AUXADCEN_AUXADCINPUTBUFFERBYPASS_Not_Bypassed            0x00000000UL                                              /**< Mode Not_Bypassed for RAC_AUXADCEN          */
#define _RAC_AUXADCEN_AUXADCINPUTBUFFERBYPASS_Bypassed                0x00000001UL                                              /**< Mode Bypassed for RAC_AUXADCEN              */
#define RAC_AUXADCEN_AUXADCINPUTBUFFERBYPASS_DEFAULT                  (_RAC_AUXADCEN_AUXADCINPUTBUFFERBYPASS_DEFAULT << 8)      /**< Shifted mode DEFAULT for RAC_AUXADCEN       */
#define RAC_AUXADCEN_AUXADCINPUTBUFFERBYPASS_Not_Bypassed             (_RAC_AUXADCEN_AUXADCINPUTBUFFERBYPASS_Not_Bypassed << 8) /**< Shifted mode Not_Bypassed for RAC_AUXADCEN  */
#define RAC_AUXADCEN_AUXADCINPUTBUFFERBYPASS_Bypassed                 (_RAC_AUXADCEN_AUXADCINPUTBUFFERBYPASS_Bypassed << 8)     /**< Shifted mode Bypassed for RAC_AUXADCEN      */
#define RAC_AUXADCEN_AUXADCENMEASTHERMISTOR                           (0x1UL << 9)                                              /**< AUXADCENMEASTHERMISTOR                      */
#define _RAC_AUXADCEN_AUXADCENMEASTHERMISTOR_SHIFT                    9                                                         /**< Shift value for RAC_AUXADCENMEASTHERMISTOR  */
#define _RAC_AUXADCEN_AUXADCENMEASTHERMISTOR_MASK                     0x200UL                                                   /**< Bit mask for RAC_AUXADCENMEASTHERMISTOR     */
#define _RAC_AUXADCEN_AUXADCENMEASTHERMISTOR_DEFAULT                  0x00000000UL                                              /**< Mode DEFAULT for RAC_AUXADCEN               */
#define _RAC_AUXADCEN_AUXADCENMEASTHERMISTOR_Disabled                 0x00000000UL                                              /**< Mode Disabled for RAC_AUXADCEN              */
#define _RAC_AUXADCEN_AUXADCENMEASTHERMISTOR_Enabled                  0x00000001UL                                              /**< Mode Enabled for RAC_AUXADCEN               */
#define RAC_AUXADCEN_AUXADCENMEASTHERMISTOR_DEFAULT                   (_RAC_AUXADCEN_AUXADCENMEASTHERMISTOR_DEFAULT << 9)       /**< Shifted mode DEFAULT for RAC_AUXADCEN       */
#define RAC_AUXADCEN_AUXADCENMEASTHERMISTOR_Disabled                  (_RAC_AUXADCEN_AUXADCENMEASTHERMISTOR_Disabled << 9)      /**< Shifted mode Disabled for RAC_AUXADCEN      */
#define RAC_AUXADCEN_AUXADCENMEASTHERMISTOR_Enabled                   (_RAC_AUXADCEN_AUXADCENMEASTHERMISTOR_Enabled << 9)       /**< Shifted mode Enabled for RAC_AUXADCEN       */

/* Bit fields for RAC AUXADCCTRL0 */
#define _RAC_AUXADCCTRL0_RESETVALUE                                   0x00000100UL                                /**< Default value for RAC_AUXADCCTRL0           */
#define _RAC_AUXADCCTRL0_MASK                                         0x00003FFFUL                                /**< Mask for RAC_AUXADCCTRL0                    */
#define _RAC_AUXADCCTRL0_CYCLES_SHIFT                                 0                                           /**< Shift value for RAC_CYCLES                  */
#define _RAC_AUXADCCTRL0_CYCLES_MASK                                  0x3FFUL                                     /**< Bit mask for RAC_CYCLES                     */
#define _RAC_AUXADCCTRL0_CYCLES_DEFAULT                               0x00000100UL                                /**< Mode DEFAULT for RAC_AUXADCCTRL0            */
#define RAC_AUXADCCTRL0_CYCLES_DEFAULT                                (_RAC_AUXADCCTRL0_CYCLES_DEFAULT << 0)      /**< Shifted mode DEFAULT for RAC_AUXADCCTRL0    */
#define _RAC_AUXADCCTRL0_MUXSEL_SHIFT                                 10                                          /**< Shift value for RAC_MUXSEL                  */
#define _RAC_AUXADCCTRL0_MUXSEL_MASK                                  0xC00UL                                     /**< Bit mask for RAC_MUXSEL                     */
#define _RAC_AUXADCCTRL0_MUXSEL_DEFAULT                               0x00000000UL                                /**< Mode DEFAULT for RAC_AUXADCCTRL0            */
#define RAC_AUXADCCTRL0_MUXSEL_DEFAULT                                (_RAC_AUXADCCTRL0_MUXSEL_DEFAULT << 10)     /**< Shifted mode DEFAULT for RAC_AUXADCCTRL0    */
#define RAC_AUXADCCTRL0_CLRCOUNTER                                    (0x1UL << 12)                               /**< Clear counter                               */
#define _RAC_AUXADCCTRL0_CLRCOUNTER_SHIFT                             12                                          /**< Shift value for RAC_CLRCOUNTER              */
#define _RAC_AUXADCCTRL0_CLRCOUNTER_MASK                              0x1000UL                                    /**< Bit mask for RAC_CLRCOUNTER                 */
#define _RAC_AUXADCCTRL0_CLRCOUNTER_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for RAC_AUXADCCTRL0            */
#define RAC_AUXADCCTRL0_CLRCOUNTER_DEFAULT                            (_RAC_AUXADCCTRL0_CLRCOUNTER_DEFAULT << 12) /**< Shifted mode DEFAULT for RAC_AUXADCCTRL0    */
#define RAC_AUXADCCTRL0_CLRFILTER                                     (0x1UL << 13)                               /**< Clear accumulators                          */
#define _RAC_AUXADCCTRL0_CLRFILTER_SHIFT                              13                                          /**< Shift value for RAC_CLRFILTER               */
#define _RAC_AUXADCCTRL0_CLRFILTER_MASK                               0x2000UL                                    /**< Bit mask for RAC_CLRFILTER                  */
#define _RAC_AUXADCCTRL0_CLRFILTER_DEFAULT                            0x00000000UL                                /**< Mode DEFAULT for RAC_AUXADCCTRL0            */
#define RAC_AUXADCCTRL0_CLRFILTER_DEFAULT                             (_RAC_AUXADCCTRL0_CLRFILTER_DEFAULT << 13)  /**< Shifted mode DEFAULT for RAC_AUXADCCTRL0    */

/* Bit fields for RAC AUXADCCTRL1 */
#define _RAC_AUXADCCTRL1_RESETVALUE                                   0x00000000UL                                             /**< Default value for RAC_AUXADCCTRL1           */
#define _RAC_AUXADCCTRL1_MASK                                         0xF31F0FFFUL                                             /**< Mask for RAC_AUXADCCTRL1                    */
#define _RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_SHIFT                      0                                                        /**< Shift value for RAC_AUXADCINPUTRESSEL       */
#define _RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_MASK                       0xFUL                                                    /**< Bit mask for RAC_AUXADCINPUTRESSEL          */
#define _RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_DEFAULT                    0x00000000UL                                             /**< Mode DEFAULT for RAC_AUXADCCTRL1            */
#define _RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES640kOhm                 0x00000000UL                                             /**< Mode RES640kOhm for RAC_AUXADCCTRL1         */
#define _RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES320kOhm                 0x00000001UL                                             /**< Mode RES320kOhm for RAC_AUXADCCTRL1         */
#define _RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES160kOhm                 0x00000002UL                                             /**< Mode RES160kOhm for RAC_AUXADCCTRL1         */
#define _RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES80kOhm                  0x00000003UL                                             /**< Mode RES80kOhm for RAC_AUXADCCTRL1          */
#define _RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES40kOhm                  0x00000004UL                                             /**< Mode RES40kOhm for RAC_AUXADCCTRL1          */
#define _RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES20kOhm                  0x00000005UL                                             /**< Mode RES20kOhm for RAC_AUXADCCTRL1          */
#define _RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES10kOhm                  0x00000006UL                                             /**< Mode RES10kOhm for RAC_AUXADCCTRL1          */
#define _RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES5kOhm                   0x00000007UL                                             /**< Mode RES5kOhm for RAC_AUXADCCTRL1           */
#define _RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES2p5kOhm                 0x00000008UL                                             /**< Mode RES2p5kOhm for RAC_AUXADCCTRL1         */
#define _RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES1p25kOhm                0x00000009UL                                             /**< Mode RES1p25kOhm for RAC_AUXADCCTRL1        */
#define _RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES0p6kOhm                 0x0000000AUL                                             /**< Mode RES0p6kOhm for RAC_AUXADCCTRL1         */
#define _RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES_switch                 0x0000000BUL                                             /**< Mode RES_switch for RAC_AUXADCCTRL1         */
#define RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_DEFAULT                     (_RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_DEFAULT << 0)        /**< Shifted mode DEFAULT for RAC_AUXADCCTRL1    */
#define RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES640kOhm                  (_RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES640kOhm << 0)     /**< Shifted mode RES640kOhm for RAC_AUXADCCTRL1 */
#define RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES320kOhm                  (_RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES320kOhm << 0)     /**< Shifted mode RES320kOhm for RAC_AUXADCCTRL1 */
#define RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES160kOhm                  (_RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES160kOhm << 0)     /**< Shifted mode RES160kOhm for RAC_AUXADCCTRL1 */
#define RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES80kOhm                   (_RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES80kOhm << 0)      /**< Shifted mode RES80kOhm for RAC_AUXADCCTRL1  */
#define RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES40kOhm                   (_RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES40kOhm << 0)      /**< Shifted mode RES40kOhm for RAC_AUXADCCTRL1  */
#define RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES20kOhm                   (_RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES20kOhm << 0)      /**< Shifted mode RES20kOhm for RAC_AUXADCCTRL1  */
#define RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES10kOhm                   (_RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES10kOhm << 0)      /**< Shifted mode RES10kOhm for RAC_AUXADCCTRL1  */
#define RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES5kOhm                    (_RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES5kOhm << 0)       /**< Shifted mode RES5kOhm for RAC_AUXADCCTRL1   */
#define RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES2p5kOhm                  (_RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES2p5kOhm << 0)     /**< Shifted mode RES2p5kOhm for RAC_AUXADCCTRL1 */
#define RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES1p25kOhm                 (_RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES1p25kOhm << 0)    /**< Shifted mode RES1p25kOhm for RAC_AUXADCCTRL1*/
#define RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES0p6kOhm                  (_RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES0p6kOhm << 0)     /**< Shifted mode RES0p6kOhm for RAC_AUXADCCTRL1 */
#define RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES_switch                  (_RAC_AUXADCCTRL1_AUXADCINPUTRESSEL_RES_switch << 0)     /**< Shifted mode RES_switch for RAC_AUXADCCTRL1 */
#define _RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SHIFT                      4                                                        /**< Shift value for RAC_AUXADCINPUTSELECT       */
#define _RAC_AUXADCCTRL1_AUXADCINPUTSELECT_MASK                       0xF0UL                                                   /**< Bit mask for RAC_AUXADCINPUTSELECT          */
#define _RAC_AUXADCCTRL1_AUXADCINPUTSELECT_DEFAULT                    0x00000000UL                                             /**< Mode DEFAULT for RAC_AUXADCCTRL1            */
#define _RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL0                       0x00000000UL                                             /**< Mode SEL0 for RAC_AUXADCCTRL1               */
#define _RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL1                       0x00000001UL                                             /**< Mode SEL1 for RAC_AUXADCCTRL1               */
#define _RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL2                       0x00000002UL                                             /**< Mode SEL2 for RAC_AUXADCCTRL1               */
#define _RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL3                       0x00000003UL                                             /**< Mode SEL3 for RAC_AUXADCCTRL1               */
#define _RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL4                       0x00000004UL                                             /**< Mode SEL4 for RAC_AUXADCCTRL1               */
#define _RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL5                       0x00000005UL                                             /**< Mode SEL5 for RAC_AUXADCCTRL1               */
#define _RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL6                       0x00000006UL                                             /**< Mode SEL6 for RAC_AUXADCCTRL1               */
#define _RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL7                       0x00000007UL                                             /**< Mode SEL7 for RAC_AUXADCCTRL1               */
#define _RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL8                       0x00000008UL                                             /**< Mode SEL8 for RAC_AUXADCCTRL1               */
#define _RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL9                       0x00000009UL                                             /**< Mode SEL9 for RAC_AUXADCCTRL1               */
#define RAC_AUXADCCTRL1_AUXADCINPUTSELECT_DEFAULT                     (_RAC_AUXADCCTRL1_AUXADCINPUTSELECT_DEFAULT << 4)        /**< Shifted mode DEFAULT for RAC_AUXADCCTRL1    */
#define RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL0                        (_RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL0 << 4)           /**< Shifted mode SEL0 for RAC_AUXADCCTRL1       */
#define RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL1                        (_RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL1 << 4)           /**< Shifted mode SEL1 for RAC_AUXADCCTRL1       */
#define RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL2                        (_RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL2 << 4)           /**< Shifted mode SEL2 for RAC_AUXADCCTRL1       */
#define RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL3                        (_RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL3 << 4)           /**< Shifted mode SEL3 for RAC_AUXADCCTRL1       */
#define RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL4                        (_RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL4 << 4)           /**< Shifted mode SEL4 for RAC_AUXADCCTRL1       */
#define RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL5                        (_RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL5 << 4)           /**< Shifted mode SEL5 for RAC_AUXADCCTRL1       */
#define RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL6                        (_RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL6 << 4)           /**< Shifted mode SEL6 for RAC_AUXADCCTRL1       */
#define RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL7                        (_RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL7 << 4)           /**< Shifted mode SEL7 for RAC_AUXADCCTRL1       */
#define RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL8                        (_RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL8 << 4)           /**< Shifted mode SEL8 for RAC_AUXADCCTRL1       */
#define RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL9                        (_RAC_AUXADCCTRL1_AUXADCINPUTSELECT_SEL9 << 4)           /**< Shifted mode SEL9 for RAC_AUXADCCTRL1       */
#define _RAC_AUXADCCTRL1_AUXADCPMONSELECT_SHIFT                       8                                                        /**< Shift value for RAC_AUXADCPMONSELECT        */
#define _RAC_AUXADCCTRL1_AUXADCPMONSELECT_MASK                        0xF00UL                                                  /**< Bit mask for RAC_AUXADCPMONSELECT           */
#define _RAC_AUXADCCTRL1_AUXADCPMONSELECT_DEFAULT                     0x00000000UL                                             /**< Mode DEFAULT for RAC_AUXADCCTRL1            */
#define RAC_AUXADCCTRL1_AUXADCPMONSELECT_DEFAULT                      (_RAC_AUXADCCTRL1_AUXADCPMONSELECT_DEFAULT << 8)         /**< Shifted mode DEFAULT for RAC_AUXADCCTRL1    */
#define _RAC_AUXADCCTRL1_AUXADCTSENSESELCURR_SHIFT                    16                                                       /**< Shift value for RAC_AUXADCTSENSESELCURR     */
#define _RAC_AUXADCCTRL1_AUXADCTSENSESELCURR_MASK                     0x1F0000UL                                               /**< Bit mask for RAC_AUXADCTSENSESELCURR        */
#define _RAC_AUXADCCTRL1_AUXADCTSENSESELCURR_DEFAULT                  0x00000000UL                                             /**< Mode DEFAULT for RAC_AUXADCCTRL1            */
#define RAC_AUXADCCTRL1_AUXADCTSENSESELCURR_DEFAULT                   (_RAC_AUXADCCTRL1_AUXADCTSENSESELCURR_DEFAULT << 16)     /**< Shifted mode DEFAULT for RAC_AUXADCCTRL1    */
#define RAC_AUXADCCTRL1_AUXADCRESET                                   (0x1UL << 24)                                            /**< AUXADCRESET                                 */
#define _RAC_AUXADCCTRL1_AUXADCRESET_SHIFT                            24                                                       /**< Shift value for RAC_AUXADCRESET             */
#define _RAC_AUXADCCTRL1_AUXADCRESET_MASK                             0x1000000UL                                              /**< Bit mask for RAC_AUXADCRESET                */
#define _RAC_AUXADCCTRL1_AUXADCRESET_DEFAULT                          0x00000000UL                                             /**< Mode DEFAULT for RAC_AUXADCCTRL1            */
#define _RAC_AUXADCCTRL1_AUXADCRESET_Reset_Disabled                   0x00000000UL                                             /**< Mode Reset_Disabled for RAC_AUXADCCTRL1     */
#define _RAC_AUXADCCTRL1_AUXADCRESET_Reset_Enabled                    0x00000001UL                                             /**< Mode Reset_Enabled for RAC_AUXADCCTRL1      */
#define RAC_AUXADCCTRL1_AUXADCRESET_DEFAULT                           (_RAC_AUXADCCTRL1_AUXADCRESET_DEFAULT << 24)             /**< Shifted mode DEFAULT for RAC_AUXADCCTRL1    */
#define RAC_AUXADCCTRL1_AUXADCRESET_Reset_Disabled                    (_RAC_AUXADCCTRL1_AUXADCRESET_Reset_Disabled << 24)      /**< Shifted mode Reset_Disabled for RAC_AUXADCCTRL1*/
#define RAC_AUXADCCTRL1_AUXADCRESET_Reset_Enabled                     (_RAC_AUXADCCTRL1_AUXADCRESET_Reset_Enabled << 24)       /**< Shifted mode Reset_Enabled for RAC_AUXADCCTRL1*/
#define RAC_AUXADCCTRL1_AUXADCTSENSESELVBE                            (0x1UL << 25)                                            /**< AUXADCTSENSESELVBE                          */
#define _RAC_AUXADCCTRL1_AUXADCTSENSESELVBE_SHIFT                     25                                                       /**< Shift value for RAC_AUXADCTSENSESELVBE      */
#define _RAC_AUXADCCTRL1_AUXADCTSENSESELVBE_MASK                      0x2000000UL                                              /**< Bit mask for RAC_AUXADCTSENSESELVBE         */
#define _RAC_AUXADCCTRL1_AUXADCTSENSESELVBE_DEFAULT                   0x00000000UL                                             /**< Mode DEFAULT for RAC_AUXADCCTRL1            */
#define _RAC_AUXADCCTRL1_AUXADCTSENSESELVBE_VBE1                      0x00000000UL                                             /**< Mode VBE1 for RAC_AUXADCCTRL1               */
#define _RAC_AUXADCCTRL1_AUXADCTSENSESELVBE_VBE2                      0x00000001UL                                             /**< Mode VBE2 for RAC_AUXADCCTRL1               */
#define RAC_AUXADCCTRL1_AUXADCTSENSESELVBE_DEFAULT                    (_RAC_AUXADCCTRL1_AUXADCTSENSESELVBE_DEFAULT << 25)      /**< Shifted mode DEFAULT for RAC_AUXADCCTRL1    */
#define RAC_AUXADCCTRL1_AUXADCTSENSESELVBE_VBE1                       (_RAC_AUXADCCTRL1_AUXADCTSENSESELVBE_VBE1 << 25)         /**< Shifted mode VBE1 for RAC_AUXADCCTRL1       */
#define RAC_AUXADCCTRL1_AUXADCTSENSESELVBE_VBE2                       (_RAC_AUXADCCTRL1_AUXADCTSENSESELVBE_VBE2 << 25)         /**< Shifted mode VBE2 for RAC_AUXADCCTRL1       */
#define _RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_SHIFT                28                                                       /**< Shift value for RAC_AUXADCTHERMISTORFREQSEL */
#define _RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_MASK                 0xF0000000UL                                             /**< Bit mask for RAC_AUXADCTHERMISTORFREQSEL    */
#define _RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DEFAULT              0x00000000UL                                             /**< Mode DEFAULT for RAC_AUXADCCTRL1            */
#define _RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV1                 0x00000000UL                                             /**< Mode DIV1 for RAC_AUXADCCTRL1               */
#define _RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV2                 0x00000001UL                                             /**< Mode DIV2 for RAC_AUXADCCTRL1               */
#define _RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV4                 0x00000002UL                                             /**< Mode DIV4 for RAC_AUXADCCTRL1               */
#define _RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV8                 0x00000003UL                                             /**< Mode DIV8 for RAC_AUXADCCTRL1               */
#define _RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV16                0x00000004UL                                             /**< Mode DIV16 for RAC_AUXADCCTRL1              */
#define _RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV32                0x00000005UL                                             /**< Mode DIV32 for RAC_AUXADCCTRL1              */
#define _RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV64                0x00000006UL                                             /**< Mode DIV64 for RAC_AUXADCCTRL1              */
#define _RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV128               0x00000007UL                                             /**< Mode DIV128 for RAC_AUXADCCTRL1             */
#define _RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV256               0x00000008UL                                             /**< Mode DIV256 for RAC_AUXADCCTRL1             */
#define _RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV512               0x00000009UL                                             /**< Mode DIV512 for RAC_AUXADCCTRL1             */
#define _RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV1024              0x0000000AUL                                             /**< Mode DIV1024 for RAC_AUXADCCTRL1            */
#define RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DEFAULT               (_RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DEFAULT << 28) /**< Shifted mode DEFAULT for RAC_AUXADCCTRL1    */
#define RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV1                  (_RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV1 << 28)    /**< Shifted mode DIV1 for RAC_AUXADCCTRL1       */
#define RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV2                  (_RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV2 << 28)    /**< Shifted mode DIV2 for RAC_AUXADCCTRL1       */
#define RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV4                  (_RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV4 << 28)    /**< Shifted mode DIV4 for RAC_AUXADCCTRL1       */
#define RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV8                  (_RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV8 << 28)    /**< Shifted mode DIV8 for RAC_AUXADCCTRL1       */
#define RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV16                 (_RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV16 << 28)   /**< Shifted mode DIV16 for RAC_AUXADCCTRL1      */
#define RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV32                 (_RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV32 << 28)   /**< Shifted mode DIV32 for RAC_AUXADCCTRL1      */
#define RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV64                 (_RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV64 << 28)   /**< Shifted mode DIV64 for RAC_AUXADCCTRL1      */
#define RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV128                (_RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV128 << 28)  /**< Shifted mode DIV128 for RAC_AUXADCCTRL1     */
#define RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV256                (_RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV256 << 28)  /**< Shifted mode DIV256 for RAC_AUXADCCTRL1     */
#define RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV512                (_RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV512 << 28)  /**< Shifted mode DIV512 for RAC_AUXADCCTRL1     */
#define RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV1024               (_RAC_AUXADCCTRL1_AUXADCTHERMISTORFREQSEL_DIV1024 << 28) /**< Shifted mode DIV1024 for RAC_AUXADCCTRL1    */

/* Bit fields for RAC AUXADCOUT */
#define _RAC_AUXADCOUT_RESETVALUE                                     0x00000000UL                            /**< Default value for RAC_AUXADCOUT             */
#define _RAC_AUXADCOUT_MASK                                           0x0FFFFFFFUL                            /**< Mask for RAC_AUXADCOUT                      */
#define _RAC_AUXADCOUT_AUXADCOUT_SHIFT                                0                                       /**< Shift value for RAC_AUXADCOUT               */
#define _RAC_AUXADCOUT_AUXADCOUT_MASK                                 0xFFFFFFFUL                             /**< Bit mask for RAC_AUXADCOUT                  */
#define _RAC_AUXADCOUT_AUXADCOUT_DEFAULT                              0x00000000UL                            /**< Mode DEFAULT for RAC_AUXADCOUT              */
#define RAC_AUXADCOUT_AUXADCOUT_DEFAULT                               (_RAC_AUXADCOUT_AUXADCOUT_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_AUXADCOUT      */

/* Bit fields for RAC CLKMULTEN0 */
#define _RAC_CLKMULTEN0_RESETVALUE                                    0xAA400005UL                                         /**< Default value for RAC_CLKMULTEN0            */
#define _RAC_CLKMULTEN0_MASK                                          0xFFDFFFFFUL                                         /**< Mask for RAC_CLKMULTEN0                     */
#define _RAC_CLKMULTEN0_CLKMULTBWCAL_SHIFT                            0                                                    /**< Shift value for RAC_CLKMULTBWCAL            */
#define _RAC_CLKMULTEN0_CLKMULTBWCAL_MASK                             0x3UL                                                /**< Bit mask for RAC_CLKMULTBWCAL               */
#define _RAC_CLKMULTEN0_CLKMULTBWCAL_DEFAULT                          0x00000001UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTBWCAL_bw_1lsb                          0x00000000UL                                         /**< Mode bw_1lsb for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTBWCAL_bw_2lsb                          0x00000001UL                                         /**< Mode bw_2lsb for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTBWCAL_bw_3lsb                          0x00000002UL                                         /**< Mode bw_3lsb for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTBWCAL_bw_4lsb                          0x00000003UL                                         /**< Mode bw_4lsb for RAC_CLKMULTEN0             */
#define RAC_CLKMULTEN0_CLKMULTBWCAL_DEFAULT                           (_RAC_CLKMULTEN0_CLKMULTBWCAL_DEFAULT << 0)          /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTBWCAL_bw_1lsb                           (_RAC_CLKMULTEN0_CLKMULTBWCAL_bw_1lsb << 0)          /**< Shifted mode bw_1lsb for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTBWCAL_bw_2lsb                           (_RAC_CLKMULTEN0_CLKMULTBWCAL_bw_2lsb << 0)          /**< Shifted mode bw_2lsb for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTBWCAL_bw_3lsb                           (_RAC_CLKMULTEN0_CLKMULTBWCAL_bw_3lsb << 0)          /**< Shifted mode bw_3lsb for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTBWCAL_bw_4lsb                           (_RAC_CLKMULTEN0_CLKMULTBWCAL_bw_4lsb << 0)          /**< Shifted mode bw_4lsb for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTDISICO                                  (0x1UL << 2)                                         /**< CLKMULTDISICO                               */
#define _RAC_CLKMULTEN0_CLKMULTDISICO_SHIFT                           2                                                    /**< Shift value for RAC_CLKMULTDISICO           */
#define _RAC_CLKMULTEN0_CLKMULTDISICO_MASK                            0x4UL                                                /**< Bit mask for RAC_CLKMULTDISICO              */
#define _RAC_CLKMULTEN0_CLKMULTDISICO_DEFAULT                         0x00000001UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTDISICO_enable                          0x00000000UL                                         /**< Mode enable for RAC_CLKMULTEN0              */
#define _RAC_CLKMULTEN0_CLKMULTDISICO_disable                         0x00000001UL                                         /**< Mode disable for RAC_CLKMULTEN0             */
#define RAC_CLKMULTEN0_CLKMULTDISICO_DEFAULT                          (_RAC_CLKMULTEN0_CLKMULTDISICO_DEFAULT << 2)         /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTDISICO_enable                           (_RAC_CLKMULTEN0_CLKMULTDISICO_enable << 2)          /**< Shifted mode enable for RAC_CLKMULTEN0      */
#define RAC_CLKMULTEN0_CLKMULTDISICO_disable                          (_RAC_CLKMULTEN0_CLKMULTDISICO_disable << 2)         /**< Shifted mode disable for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENBBDET                                 (0x1UL << 3)                                         /**< CLKMULTENBBDET                              */
#define _RAC_CLKMULTEN0_CLKMULTENBBDET_SHIFT                          3                                                    /**< Shift value for RAC_CLKMULTENBBDET          */
#define _RAC_CLKMULTEN0_CLKMULTENBBDET_MASK                           0x8UL                                                /**< Bit mask for RAC_CLKMULTENBBDET             */
#define _RAC_CLKMULTEN0_CLKMULTENBBDET_DEFAULT                        0x00000000UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENBBDET_disable                        0x00000000UL                                         /**< Mode disable for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENBBDET_enable                         0x00000001UL                                         /**< Mode enable for RAC_CLKMULTEN0              */
#define RAC_CLKMULTEN0_CLKMULTENBBDET_DEFAULT                         (_RAC_CLKMULTEN0_CLKMULTENBBDET_DEFAULT << 3)        /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENBBDET_disable                         (_RAC_CLKMULTEN0_CLKMULTENBBDET_disable << 3)        /**< Shifted mode disable for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENBBDET_enable                          (_RAC_CLKMULTEN0_CLKMULTENBBDET_enable << 3)         /**< Shifted mode enable for RAC_CLKMULTEN0      */
#define RAC_CLKMULTEN0_CLKMULTENBBXLDET                               (0x1UL << 4)                                         /**< CLKMULTENBBXLDET                            */
#define _RAC_CLKMULTEN0_CLKMULTENBBXLDET_SHIFT                        4                                                    /**< Shift value for RAC_CLKMULTENBBXLDET        */
#define _RAC_CLKMULTEN0_CLKMULTENBBXLDET_MASK                         0x10UL                                               /**< Bit mask for RAC_CLKMULTENBBXLDET           */
#define _RAC_CLKMULTEN0_CLKMULTENBBXLDET_DEFAULT                      0x00000000UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENBBXLDET_disable                      0x00000000UL                                         /**< Mode disable for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENBBXLDET_enable                       0x00000001UL                                         /**< Mode enable for RAC_CLKMULTEN0              */
#define RAC_CLKMULTEN0_CLKMULTENBBXLDET_DEFAULT                       (_RAC_CLKMULTEN0_CLKMULTENBBXLDET_DEFAULT << 4)      /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENBBXLDET_disable                       (_RAC_CLKMULTEN0_CLKMULTENBBXLDET_disable << 4)      /**< Shifted mode disable for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENBBXLDET_enable                        (_RAC_CLKMULTEN0_CLKMULTENBBXLDET_enable << 4)       /**< Shifted mode enable for RAC_CLKMULTEN0      */
#define RAC_CLKMULTEN0_CLKMULTENBBXMDET                               (0x1UL << 5)                                         /**< CLKMULTENBBXMDET                            */
#define _RAC_CLKMULTEN0_CLKMULTENBBXMDET_SHIFT                        5                                                    /**< Shift value for RAC_CLKMULTENBBXMDET        */
#define _RAC_CLKMULTEN0_CLKMULTENBBXMDET_MASK                         0x20UL                                               /**< Bit mask for RAC_CLKMULTENBBXMDET           */
#define _RAC_CLKMULTEN0_CLKMULTENBBXMDET_DEFAULT                      0x00000000UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENBBXMDET_disable                      0x00000000UL                                         /**< Mode disable for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENBBXMDET_enable                       0x00000001UL                                         /**< Mode enable for RAC_CLKMULTEN0              */
#define RAC_CLKMULTEN0_CLKMULTENBBXMDET_DEFAULT                       (_RAC_CLKMULTEN0_CLKMULTENBBXMDET_DEFAULT << 5)      /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENBBXMDET_disable                       (_RAC_CLKMULTEN0_CLKMULTENBBXMDET_disable << 5)      /**< Shifted mode disable for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENBBXMDET_enable                        (_RAC_CLKMULTEN0_CLKMULTENBBXMDET_enable << 5)       /**< Shifted mode enable for RAC_CLKMULTEN0      */
#define RAC_CLKMULTEN0_CLKMULTENCFDET                                 (0x1UL << 6)                                         /**< CLKMULTENCFDET                              */
#define _RAC_CLKMULTEN0_CLKMULTENCFDET_SHIFT                          6                                                    /**< Shift value for RAC_CLKMULTENCFDET          */
#define _RAC_CLKMULTEN0_CLKMULTENCFDET_MASK                           0x40UL                                               /**< Bit mask for RAC_CLKMULTENCFDET             */
#define _RAC_CLKMULTEN0_CLKMULTENCFDET_DEFAULT                        0x00000000UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENCFDET_disable                        0x00000000UL                                         /**< Mode disable for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENCFDET_enable                         0x00000001UL                                         /**< Mode enable for RAC_CLKMULTEN0              */
#define RAC_CLKMULTEN0_CLKMULTENCFDET_DEFAULT                         (_RAC_CLKMULTEN0_CLKMULTENCFDET_DEFAULT << 6)        /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENCFDET_disable                         (_RAC_CLKMULTEN0_CLKMULTENCFDET_disable << 6)        /**< Shifted mode disable for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENCFDET_enable                          (_RAC_CLKMULTEN0_CLKMULTENCFDET_enable << 6)         /**< Shifted mode enable for RAC_CLKMULTEN0      */
#define RAC_CLKMULTEN0_CLKMULTENDITHER                                (0x1UL << 7)                                         /**< CLKMULTENDITHER                             */
#define _RAC_CLKMULTEN0_CLKMULTENDITHER_SHIFT                         7                                                    /**< Shift value for RAC_CLKMULTENDITHER         */
#define _RAC_CLKMULTEN0_CLKMULTENDITHER_MASK                          0x80UL                                               /**< Bit mask for RAC_CLKMULTENDITHER            */
#define _RAC_CLKMULTEN0_CLKMULTENDITHER_DEFAULT                       0x00000000UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENDITHER_disable                       0x00000000UL                                         /**< Mode disable for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENDITHER_enable                        0x00000001UL                                         /**< Mode enable for RAC_CLKMULTEN0              */
#define RAC_CLKMULTEN0_CLKMULTENDITHER_DEFAULT                        (_RAC_CLKMULTEN0_CLKMULTENDITHER_DEFAULT << 7)       /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENDITHER_disable                        (_RAC_CLKMULTEN0_CLKMULTENDITHER_disable << 7)       /**< Shifted mode disable for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENDITHER_enable                         (_RAC_CLKMULTEN0_CLKMULTENDITHER_enable << 7)        /**< Shifted mode enable for RAC_CLKMULTEN0      */
#define RAC_CLKMULTEN0_CLKMULTENDRVADC                                (0x1UL << 8)                                         /**< CLKMULTENDRVADC                             */
#define _RAC_CLKMULTEN0_CLKMULTENDRVADC_SHIFT                         8                                                    /**< Shift value for RAC_CLKMULTENDRVADC         */
#define _RAC_CLKMULTEN0_CLKMULTENDRVADC_MASK                          0x100UL                                              /**< Bit mask for RAC_CLKMULTENDRVADC            */
#define _RAC_CLKMULTEN0_CLKMULTENDRVADC_DEFAULT                       0x00000000UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENDRVADC_disable                       0x00000000UL                                         /**< Mode disable for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENDRVADC_enable                        0x00000001UL                                         /**< Mode enable for RAC_CLKMULTEN0              */
#define RAC_CLKMULTEN0_CLKMULTENDRVADC_DEFAULT                        (_RAC_CLKMULTEN0_CLKMULTENDRVADC_DEFAULT << 8)       /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENDRVADC_disable                        (_RAC_CLKMULTEN0_CLKMULTENDRVADC_disable << 8)       /**< Shifted mode disable for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENDRVADC_enable                         (_RAC_CLKMULTEN0_CLKMULTENDRVADC_enable << 8)        /**< Shifted mode enable for RAC_CLKMULTEN0      */
#define RAC_CLKMULTEN0_CLKMULTENDRVN                                  (0x1UL << 9)                                         /**< CLKMULTENDRVN                               */
#define _RAC_CLKMULTEN0_CLKMULTENDRVN_SHIFT                           9                                                    /**< Shift value for RAC_CLKMULTENDRVN           */
#define _RAC_CLKMULTEN0_CLKMULTENDRVN_MASK                            0x200UL                                              /**< Bit mask for RAC_CLKMULTENDRVN              */
#define _RAC_CLKMULTEN0_CLKMULTENDRVN_DEFAULT                         0x00000000UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENDRVN_disable                         0x00000000UL                                         /**< Mode disable for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENDRVN_enable                          0x00000001UL                                         /**< Mode enable for RAC_CLKMULTEN0              */
#define RAC_CLKMULTEN0_CLKMULTENDRVN_DEFAULT                          (_RAC_CLKMULTEN0_CLKMULTENDRVN_DEFAULT << 9)         /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENDRVN_disable                          (_RAC_CLKMULTEN0_CLKMULTENDRVN_disable << 9)         /**< Shifted mode disable for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENDRVN_enable                           (_RAC_CLKMULTEN0_CLKMULTENDRVN_enable << 9)          /**< Shifted mode enable for RAC_CLKMULTEN0      */
#define RAC_CLKMULTEN0_CLKMULTENDRVP                                  (0x1UL << 10)                                        /**< CLKMULTENDRVP                               */
#define _RAC_CLKMULTEN0_CLKMULTENDRVP_SHIFT                           10                                                   /**< Shift value for RAC_CLKMULTENDRVP           */
#define _RAC_CLKMULTEN0_CLKMULTENDRVP_MASK                            0x400UL                                              /**< Bit mask for RAC_CLKMULTENDRVP              */
#define _RAC_CLKMULTEN0_CLKMULTENDRVP_DEFAULT                         0x00000000UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENDRVP_disable                         0x00000000UL                                         /**< Mode disable for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENDRVP_enable                          0x00000001UL                                         /**< Mode enable for RAC_CLKMULTEN0              */
#define RAC_CLKMULTEN0_CLKMULTENDRVP_DEFAULT                          (_RAC_CLKMULTEN0_CLKMULTENDRVP_DEFAULT << 10)        /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENDRVP_disable                          (_RAC_CLKMULTEN0_CLKMULTENDRVP_disable << 10)        /**< Shifted mode disable for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENDRVP_enable                           (_RAC_CLKMULTEN0_CLKMULTENDRVP_enable << 10)         /**< Shifted mode enable for RAC_CLKMULTEN0      */
#define RAC_CLKMULTEN0_CLKMULTENDRVRX2P4G                             (0x1UL << 11)                                        /**< CLKMULTENDRVRX2P4G                          */
#define _RAC_CLKMULTEN0_CLKMULTENDRVRX2P4G_SHIFT                      11                                                   /**< Shift value for RAC_CLKMULTENDRVRX2P4G      */
#define _RAC_CLKMULTEN0_CLKMULTENDRVRX2P4G_MASK                       0x800UL                                              /**< Bit mask for RAC_CLKMULTENDRVRX2P4G         */
#define _RAC_CLKMULTEN0_CLKMULTENDRVRX2P4G_DEFAULT                    0x00000000UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENDRVRX2P4G_disable                    0x00000000UL                                         /**< Mode disable for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENDRVRX2P4G_enable                     0x00000001UL                                         /**< Mode enable for RAC_CLKMULTEN0              */
#define RAC_CLKMULTEN0_CLKMULTENDRVRX2P4G_DEFAULT                     (_RAC_CLKMULTEN0_CLKMULTENDRVRX2P4G_DEFAULT << 11)   /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENDRVRX2P4G_disable                     (_RAC_CLKMULTEN0_CLKMULTENDRVRX2P4G_disable << 11)   /**< Shifted mode disable for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENDRVRX2P4G_enable                      (_RAC_CLKMULTEN0_CLKMULTENDRVRX2P4G_enable << 11)    /**< Shifted mode enable for RAC_CLKMULTEN0      */
#define RAC_CLKMULTEN0_CLKMULTENFBDIV                                 (0x1UL << 14)                                        /**< CLKMULTENFBDIV                              */
#define _RAC_CLKMULTEN0_CLKMULTENFBDIV_SHIFT                          14                                                   /**< Shift value for RAC_CLKMULTENFBDIV          */
#define _RAC_CLKMULTEN0_CLKMULTENFBDIV_MASK                           0x4000UL                                             /**< Bit mask for RAC_CLKMULTENFBDIV             */
#define _RAC_CLKMULTEN0_CLKMULTENFBDIV_DEFAULT                        0x00000000UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENFBDIV_disable                        0x00000000UL                                         /**< Mode disable for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENFBDIV_enable                         0x00000001UL                                         /**< Mode enable for RAC_CLKMULTEN0              */
#define RAC_CLKMULTEN0_CLKMULTENFBDIV_DEFAULT                         (_RAC_CLKMULTEN0_CLKMULTENFBDIV_DEFAULT << 14)       /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENFBDIV_disable                         (_RAC_CLKMULTEN0_CLKMULTENFBDIV_disable << 14)       /**< Shifted mode disable for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENFBDIV_enable                          (_RAC_CLKMULTEN0_CLKMULTENFBDIV_enable << 14)        /**< Shifted mode enable for RAC_CLKMULTEN0      */
#define RAC_CLKMULTEN0_CLKMULTENREFDIV                                (0x1UL << 15)                                        /**< CLKMULTENREFDIV                             */
#define _RAC_CLKMULTEN0_CLKMULTENREFDIV_SHIFT                         15                                                   /**< Shift value for RAC_CLKMULTENREFDIV         */
#define _RAC_CLKMULTEN0_CLKMULTENREFDIV_MASK                          0x8000UL                                             /**< Bit mask for RAC_CLKMULTENREFDIV            */
#define _RAC_CLKMULTEN0_CLKMULTENREFDIV_DEFAULT                       0x00000000UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENREFDIV_disable                       0x00000000UL                                         /**< Mode disable for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENREFDIV_enable                        0x00000001UL                                         /**< Mode enable for RAC_CLKMULTEN0              */
#define RAC_CLKMULTEN0_CLKMULTENREFDIV_DEFAULT                        (_RAC_CLKMULTEN0_CLKMULTENREFDIV_DEFAULT << 15)      /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENREFDIV_disable                        (_RAC_CLKMULTEN0_CLKMULTENREFDIV_disable << 15)      /**< Shifted mode disable for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENREFDIV_enable                         (_RAC_CLKMULTEN0_CLKMULTENREFDIV_enable << 15)       /**< Shifted mode enable for RAC_CLKMULTEN0      */
#define RAC_CLKMULTEN0_CLKMULTENREG1                                  (0x1UL << 16)                                        /**< CLKMULTENREG1                               */
#define _RAC_CLKMULTEN0_CLKMULTENREG1_SHIFT                           16                                                   /**< Shift value for RAC_CLKMULTENREG1           */
#define _RAC_CLKMULTEN0_CLKMULTENREG1_MASK                            0x10000UL                                            /**< Bit mask for RAC_CLKMULTENREG1              */
#define _RAC_CLKMULTEN0_CLKMULTENREG1_DEFAULT                         0x00000000UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENREG1_disable                         0x00000000UL                                         /**< Mode disable for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENREG1_enable                          0x00000001UL                                         /**< Mode enable for RAC_CLKMULTEN0              */
#define RAC_CLKMULTEN0_CLKMULTENREG1_DEFAULT                          (_RAC_CLKMULTEN0_CLKMULTENREG1_DEFAULT << 16)        /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENREG1_disable                          (_RAC_CLKMULTEN0_CLKMULTENREG1_disable << 16)        /**< Shifted mode disable for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENREG1_enable                           (_RAC_CLKMULTEN0_CLKMULTENREG1_enable << 16)         /**< Shifted mode enable for RAC_CLKMULTEN0      */
#define RAC_CLKMULTEN0_CLKMULTENREG2                                  (0x1UL << 17)                                        /**< CLKMULTENREG2                               */
#define _RAC_CLKMULTEN0_CLKMULTENREG2_SHIFT                           17                                                   /**< Shift value for RAC_CLKMULTENREG2           */
#define _RAC_CLKMULTEN0_CLKMULTENREG2_MASK                            0x20000UL                                            /**< Bit mask for RAC_CLKMULTENREG2              */
#define _RAC_CLKMULTEN0_CLKMULTENREG2_DEFAULT                         0x00000000UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENREG2_disable                         0x00000000UL                                         /**< Mode disable for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENREG2_enable                          0x00000001UL                                         /**< Mode enable for RAC_CLKMULTEN0              */
#define RAC_CLKMULTEN0_CLKMULTENREG2_DEFAULT                          (_RAC_CLKMULTEN0_CLKMULTENREG2_DEFAULT << 17)        /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENREG2_disable                          (_RAC_CLKMULTEN0_CLKMULTENREG2_disable << 17)        /**< Shifted mode disable for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENREG2_enable                           (_RAC_CLKMULTEN0_CLKMULTENREG2_enable << 17)         /**< Shifted mode enable for RAC_CLKMULTEN0      */
#define RAC_CLKMULTEN0_CLKMULTENREG3                                  (0x1UL << 18)                                        /**< CLKMULTENREG3                               */
#define _RAC_CLKMULTEN0_CLKMULTENREG3_SHIFT                           18                                                   /**< Shift value for RAC_CLKMULTENREG3           */
#define _RAC_CLKMULTEN0_CLKMULTENREG3_MASK                            0x40000UL                                            /**< Bit mask for RAC_CLKMULTENREG3              */
#define _RAC_CLKMULTEN0_CLKMULTENREG3_DEFAULT                         0x00000000UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENREG3_disable                         0x00000000UL                                         /**< Mode disable for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENREG3_enable                          0x00000001UL                                         /**< Mode enable for RAC_CLKMULTEN0              */
#define RAC_CLKMULTEN0_CLKMULTENREG3_DEFAULT                          (_RAC_CLKMULTEN0_CLKMULTENREG3_DEFAULT << 18)        /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENREG3_disable                          (_RAC_CLKMULTEN0_CLKMULTENREG3_disable << 18)        /**< Shifted mode disable for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENREG3_enable                           (_RAC_CLKMULTEN0_CLKMULTENREG3_enable << 18)         /**< Shifted mode enable for RAC_CLKMULTEN0      */
#define RAC_CLKMULTEN0_CLKMULTENROTDET                                (0x1UL << 19)                                        /**< CLKMULTENROTDET                             */
#define _RAC_CLKMULTEN0_CLKMULTENROTDET_SHIFT                         19                                                   /**< Shift value for RAC_CLKMULTENROTDET         */
#define _RAC_CLKMULTEN0_CLKMULTENROTDET_MASK                          0x80000UL                                            /**< Bit mask for RAC_CLKMULTENROTDET            */
#define _RAC_CLKMULTEN0_CLKMULTENROTDET_DEFAULT                       0x00000000UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENROTDET_disable                       0x00000000UL                                         /**< Mode disable for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENROTDET_enable                        0x00000001UL                                         /**< Mode enable for RAC_CLKMULTEN0              */
#define RAC_CLKMULTEN0_CLKMULTENROTDET_DEFAULT                        (_RAC_CLKMULTEN0_CLKMULTENROTDET_DEFAULT << 19)      /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENROTDET_disable                        (_RAC_CLKMULTEN0_CLKMULTENROTDET_disable << 19)      /**< Shifted mode disable for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENROTDET_enable                         (_RAC_CLKMULTEN0_CLKMULTENROTDET_enable << 19)       /**< Shifted mode enable for RAC_CLKMULTEN0      */
#define RAC_CLKMULTEN0_CLKMULTENBYPASS40MHZ                           (0x1UL << 20)                                        /**< CLKMULTENBYPASS40MHZ                        */
#define _RAC_CLKMULTEN0_CLKMULTENBYPASS40MHZ_SHIFT                    20                                                   /**< Shift value for RAC_CLKMULTENBYPASS40MHZ    */
#define _RAC_CLKMULTEN0_CLKMULTENBYPASS40MHZ_MASK                     0x100000UL                                           /**< Bit mask for RAC_CLKMULTENBYPASS40MHZ       */
#define _RAC_CLKMULTEN0_CLKMULTENBYPASS40MHZ_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENBYPASS40MHZ_disable                  0x00000000UL                                         /**< Mode disable for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTENBYPASS40MHZ_enable                   0x00000001UL                                         /**< Mode enable for RAC_CLKMULTEN0              */
#define RAC_CLKMULTEN0_CLKMULTENBYPASS40MHZ_DEFAULT                   (_RAC_CLKMULTEN0_CLKMULTENBYPASS40MHZ_DEFAULT << 20) /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENBYPASS40MHZ_disable                   (_RAC_CLKMULTEN0_CLKMULTENBYPASS40MHZ_disable << 20) /**< Shifted mode disable for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTENBYPASS40MHZ_enable                    (_RAC_CLKMULTEN0_CLKMULTENBYPASS40MHZ_enable << 20)  /**< Shifted mode enable for RAC_CLKMULTEN0      */
#define _RAC_CLKMULTEN0_CLKMULTFREQCAL_SHIFT                          22                                                   /**< Shift value for RAC_CLKMULTFREQCAL          */
#define _RAC_CLKMULTEN0_CLKMULTFREQCAL_MASK                           0xC00000UL                                           /**< Bit mask for RAC_CLKMULTFREQCAL             */
#define _RAC_CLKMULTEN0_CLKMULTFREQCAL_DEFAULT                        0x00000001UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTFREQCAL_pedes_14uA                     0x00000000UL                                         /**< Mode pedes_14uA for RAC_CLKMULTEN0          */
#define _RAC_CLKMULTEN0_CLKMULTFREQCAL_pedes_22uA                     0x00000001UL                                         /**< Mode pedes_22uA for RAC_CLKMULTEN0          */
#define _RAC_CLKMULTEN0_CLKMULTFREQCAL_pedes_30uA                     0x00000002UL                                         /**< Mode pedes_30uA for RAC_CLKMULTEN0          */
#define _RAC_CLKMULTEN0_CLKMULTFREQCAL_pedes_38uA                     0x00000003UL                                         /**< Mode pedes_38uA for RAC_CLKMULTEN0          */
#define RAC_CLKMULTEN0_CLKMULTFREQCAL_DEFAULT                         (_RAC_CLKMULTEN0_CLKMULTFREQCAL_DEFAULT << 22)       /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTFREQCAL_pedes_14uA                      (_RAC_CLKMULTEN0_CLKMULTFREQCAL_pedes_14uA << 22)    /**< Shifted mode pedes_14uA for RAC_CLKMULTEN0  */
#define RAC_CLKMULTEN0_CLKMULTFREQCAL_pedes_22uA                      (_RAC_CLKMULTEN0_CLKMULTFREQCAL_pedes_22uA << 22)    /**< Shifted mode pedes_22uA for RAC_CLKMULTEN0  */
#define RAC_CLKMULTEN0_CLKMULTFREQCAL_pedes_30uA                      (_RAC_CLKMULTEN0_CLKMULTFREQCAL_pedes_30uA << 22)    /**< Shifted mode pedes_30uA for RAC_CLKMULTEN0  */
#define RAC_CLKMULTEN0_CLKMULTFREQCAL_pedes_38uA                      (_RAC_CLKMULTEN0_CLKMULTFREQCAL_pedes_38uA << 22)    /**< Shifted mode pedes_38uA for RAC_CLKMULTEN0  */
#define _RAC_CLKMULTEN0_CLKMULTREG2ADJI_SHIFT                         24                                                   /**< Shift value for RAC_CLKMULTREG2ADJI         */
#define _RAC_CLKMULTEN0_CLKMULTREG2ADJI_MASK                          0x3000000UL                                          /**< Bit mask for RAC_CLKMULTREG2ADJI            */
#define _RAC_CLKMULTEN0_CLKMULTREG2ADJI_DEFAULT                       0x00000002UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTREG2ADJI_I_80uA                        0x00000000UL                                         /**< Mode I_80uA for RAC_CLKMULTEN0              */
#define _RAC_CLKMULTEN0_CLKMULTREG2ADJI_I_100uA                       0x00000001UL                                         /**< Mode I_100uA for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTREG2ADJI_I_120uA                       0x00000002UL                                         /**< Mode I_120uA for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTREG2ADJI_I_140uA                       0x00000003UL                                         /**< Mode I_140uA for RAC_CLKMULTEN0             */
#define RAC_CLKMULTEN0_CLKMULTREG2ADJI_DEFAULT                        (_RAC_CLKMULTEN0_CLKMULTREG2ADJI_DEFAULT << 24)      /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTREG2ADJI_I_80uA                         (_RAC_CLKMULTEN0_CLKMULTREG2ADJI_I_80uA << 24)       /**< Shifted mode I_80uA for RAC_CLKMULTEN0      */
#define RAC_CLKMULTEN0_CLKMULTREG2ADJI_I_100uA                        (_RAC_CLKMULTEN0_CLKMULTREG2ADJI_I_100uA << 24)      /**< Shifted mode I_100uA for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTREG2ADJI_I_120uA                        (_RAC_CLKMULTEN0_CLKMULTREG2ADJI_I_120uA << 24)      /**< Shifted mode I_120uA for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTREG2ADJI_I_140uA                        (_RAC_CLKMULTEN0_CLKMULTREG2ADJI_I_140uA << 24)      /**< Shifted mode I_140uA for RAC_CLKMULTEN0     */
#define _RAC_CLKMULTEN0_CLKMULTREG1ADJV_SHIFT                         26                                                   /**< Shift value for RAC_CLKMULTREG1ADJV         */
#define _RAC_CLKMULTEN0_CLKMULTREG1ADJV_MASK                          0xC000000UL                                          /**< Bit mask for RAC_CLKMULTREG1ADJV            */
#define _RAC_CLKMULTEN0_CLKMULTREG1ADJV_DEFAULT                       0x00000002UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTREG1ADJV_v1p28                         0x00000000UL                                         /**< Mode v1p28 for RAC_CLKMULTEN0               */
#define _RAC_CLKMULTEN0_CLKMULTREG1ADJV_v1p32                         0x00000001UL                                         /**< Mode v1p32 for RAC_CLKMULTEN0               */
#define _RAC_CLKMULTEN0_CLKMULTREG1ADJV_v1p33                         0x00000002UL                                         /**< Mode v1p33 for RAC_CLKMULTEN0               */
#define _RAC_CLKMULTEN0_CLKMULTREG1ADJV_v1p38                         0x00000003UL                                         /**< Mode v1p38 for RAC_CLKMULTEN0               */
#define RAC_CLKMULTEN0_CLKMULTREG1ADJV_DEFAULT                        (_RAC_CLKMULTEN0_CLKMULTREG1ADJV_DEFAULT << 26)      /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTREG1ADJV_v1p28                          (_RAC_CLKMULTEN0_CLKMULTREG1ADJV_v1p28 << 26)        /**< Shifted mode v1p28 for RAC_CLKMULTEN0       */
#define RAC_CLKMULTEN0_CLKMULTREG1ADJV_v1p32                          (_RAC_CLKMULTEN0_CLKMULTREG1ADJV_v1p32 << 26)        /**< Shifted mode v1p32 for RAC_CLKMULTEN0       */
#define RAC_CLKMULTEN0_CLKMULTREG1ADJV_v1p33                          (_RAC_CLKMULTEN0_CLKMULTREG1ADJV_v1p33 << 26)        /**< Shifted mode v1p33 for RAC_CLKMULTEN0       */
#define RAC_CLKMULTEN0_CLKMULTREG1ADJV_v1p38                          (_RAC_CLKMULTEN0_CLKMULTREG1ADJV_v1p38 << 26)        /**< Shifted mode v1p38 for RAC_CLKMULTEN0       */
#define _RAC_CLKMULTEN0_CLKMULTREG2ADJV_SHIFT                         28                                                   /**< Shift value for RAC_CLKMULTREG2ADJV         */
#define _RAC_CLKMULTEN0_CLKMULTREG2ADJV_MASK                          0x30000000UL                                         /**< Bit mask for RAC_CLKMULTREG2ADJV            */
#define _RAC_CLKMULTEN0_CLKMULTREG2ADJV_DEFAULT                       0x00000002UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTREG2ADJV_v1p03                         0x00000000UL                                         /**< Mode v1p03 for RAC_CLKMULTEN0               */
#define _RAC_CLKMULTEN0_CLKMULTREG2ADJV_v1p09                         0x00000001UL                                         /**< Mode v1p09 for RAC_CLKMULTEN0               */
#define _RAC_CLKMULTEN0_CLKMULTREG2ADJV_v1p10                         0x00000002UL                                         /**< Mode v1p10 for RAC_CLKMULTEN0               */
#define _RAC_CLKMULTEN0_CLKMULTREG2ADJV_v1p16                         0x00000003UL                                         /**< Mode v1p16 for RAC_CLKMULTEN0               */
#define RAC_CLKMULTEN0_CLKMULTREG2ADJV_DEFAULT                        (_RAC_CLKMULTEN0_CLKMULTREG2ADJV_DEFAULT << 28)      /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTREG2ADJV_v1p03                          (_RAC_CLKMULTEN0_CLKMULTREG2ADJV_v1p03 << 28)        /**< Shifted mode v1p03 for RAC_CLKMULTEN0       */
#define RAC_CLKMULTEN0_CLKMULTREG2ADJV_v1p09                          (_RAC_CLKMULTEN0_CLKMULTREG2ADJV_v1p09 << 28)        /**< Shifted mode v1p09 for RAC_CLKMULTEN0       */
#define RAC_CLKMULTEN0_CLKMULTREG2ADJV_v1p10                          (_RAC_CLKMULTEN0_CLKMULTREG2ADJV_v1p10 << 28)        /**< Shifted mode v1p10 for RAC_CLKMULTEN0       */
#define RAC_CLKMULTEN0_CLKMULTREG2ADJV_v1p16                          (_RAC_CLKMULTEN0_CLKMULTREG2ADJV_v1p16 << 28)        /**< Shifted mode v1p16 for RAC_CLKMULTEN0       */
#define _RAC_CLKMULTEN0_CLKMULTREG3ADJV_SHIFT                         30                                                   /**< Shift value for RAC_CLKMULTREG3ADJV         */
#define _RAC_CLKMULTEN0_CLKMULTREG3ADJV_MASK                          0xC0000000UL                                         /**< Bit mask for RAC_CLKMULTREG3ADJV            */
#define _RAC_CLKMULTEN0_CLKMULTREG3ADJV_DEFAULT                       0x00000002UL                                         /**< Mode DEFAULT for RAC_CLKMULTEN0             */
#define _RAC_CLKMULTEN0_CLKMULTREG3ADJV_v1p03                         0x00000000UL                                         /**< Mode v1p03 for RAC_CLKMULTEN0               */
#define _RAC_CLKMULTEN0_CLKMULTREG3ADJV_v1p06                         0x00000001UL                                         /**< Mode v1p06 for RAC_CLKMULTEN0               */
#define _RAC_CLKMULTEN0_CLKMULTREG3ADJV_v1p07                         0x00000002UL                                         /**< Mode v1p07 for RAC_CLKMULTEN0               */
#define _RAC_CLKMULTEN0_CLKMULTREG3ADJV_v1p09                         0x00000003UL                                         /**< Mode v1p09 for RAC_CLKMULTEN0               */
#define RAC_CLKMULTEN0_CLKMULTREG3ADJV_DEFAULT                        (_RAC_CLKMULTEN0_CLKMULTREG3ADJV_DEFAULT << 30)      /**< Shifted mode DEFAULT for RAC_CLKMULTEN0     */
#define RAC_CLKMULTEN0_CLKMULTREG3ADJV_v1p03                          (_RAC_CLKMULTEN0_CLKMULTREG3ADJV_v1p03 << 30)        /**< Shifted mode v1p03 for RAC_CLKMULTEN0       */
#define RAC_CLKMULTEN0_CLKMULTREG3ADJV_v1p06                          (_RAC_CLKMULTEN0_CLKMULTREG3ADJV_v1p06 << 30)        /**< Shifted mode v1p06 for RAC_CLKMULTEN0       */
#define RAC_CLKMULTEN0_CLKMULTREG3ADJV_v1p07                          (_RAC_CLKMULTEN0_CLKMULTREG3ADJV_v1p07 << 30)        /**< Shifted mode v1p07 for RAC_CLKMULTEN0       */
#define RAC_CLKMULTEN0_CLKMULTREG3ADJV_v1p09                          (_RAC_CLKMULTEN0_CLKMULTREG3ADJV_v1p09 << 30)        /**< Shifted mode v1p09 for RAC_CLKMULTEN0       */

/* Bit fields for RAC CLKMULTEN1 */
#define _RAC_CLKMULTEN1_RESETVALUE                                    0x00000188UL                                           /**< Default value for RAC_CLKMULTEN1            */
#define _RAC_CLKMULTEN1_MASK                                          0x0001FDEFUL                                           /**< Mask for RAC_CLKMULTEN1                     */
#define _RAC_CLKMULTEN1_CLKMULTINNIBBLE_SHIFT                         0                                                      /**< Shift value for RAC_CLKMULTINNIBBLE         */
#define _RAC_CLKMULTEN1_CLKMULTINNIBBLE_MASK                          0xFUL                                                  /**< Bit mask for RAC_CLKMULTINNIBBLE            */
#define _RAC_CLKMULTEN1_CLKMULTINNIBBLE_DEFAULT                       0x00000008UL                                           /**< Mode DEFAULT for RAC_CLKMULTEN1             */
#define RAC_CLKMULTEN1_CLKMULTINNIBBLE_DEFAULT                        (_RAC_CLKMULTEN1_CLKMULTINNIBBLE_DEFAULT << 0)         /**< Shifted mode DEFAULT for RAC_CLKMULTEN1     */
#define RAC_CLKMULTEN1_CLKMULTLDFNIB                                  (0x1UL << 5)                                           /**< CLKMULTLDFNIB                               */
#define _RAC_CLKMULTEN1_CLKMULTLDFNIB_SHIFT                           5                                                      /**< Shift value for RAC_CLKMULTLDFNIB           */
#define _RAC_CLKMULTEN1_CLKMULTLDFNIB_MASK                            0x20UL                                                 /**< Bit mask for RAC_CLKMULTLDFNIB              */
#define _RAC_CLKMULTEN1_CLKMULTLDFNIB_DEFAULT                         0x00000000UL                                           /**< Mode DEFAULT for RAC_CLKMULTEN1             */
#define _RAC_CLKMULTEN1_CLKMULTLDFNIB_disable                         0x00000000UL                                           /**< Mode disable for RAC_CLKMULTEN1             */
#define _RAC_CLKMULTEN1_CLKMULTLDFNIB_enable                          0x00000001UL                                           /**< Mode enable for RAC_CLKMULTEN1              */
#define RAC_CLKMULTEN1_CLKMULTLDFNIB_DEFAULT                          (_RAC_CLKMULTEN1_CLKMULTLDFNIB_DEFAULT << 5)           /**< Shifted mode DEFAULT for RAC_CLKMULTEN1     */
#define RAC_CLKMULTEN1_CLKMULTLDFNIB_disable                          (_RAC_CLKMULTEN1_CLKMULTLDFNIB_disable << 5)           /**< Shifted mode disable for RAC_CLKMULTEN1     */
#define RAC_CLKMULTEN1_CLKMULTLDFNIB_enable                           (_RAC_CLKMULTEN1_CLKMULTLDFNIB_enable << 5)            /**< Shifted mode enable for RAC_CLKMULTEN1      */
#define RAC_CLKMULTEN1_CLKMULTLDMNIB                                  (0x1UL << 6)                                           /**< CLKMULTLDMNIB                               */
#define _RAC_CLKMULTEN1_CLKMULTLDMNIB_SHIFT                           6                                                      /**< Shift value for RAC_CLKMULTLDMNIB           */
#define _RAC_CLKMULTEN1_CLKMULTLDMNIB_MASK                            0x40UL                                                 /**< Bit mask for RAC_CLKMULTLDMNIB              */
#define _RAC_CLKMULTEN1_CLKMULTLDMNIB_DEFAULT                         0x00000000UL                                           /**< Mode DEFAULT for RAC_CLKMULTEN1             */
#define _RAC_CLKMULTEN1_CLKMULTLDMNIB_disable                         0x00000000UL                                           /**< Mode disable for RAC_CLKMULTEN1             */
#define _RAC_CLKMULTEN1_CLKMULTLDMNIB_enable                          0x00000001UL                                           /**< Mode enable for RAC_CLKMULTEN1              */
#define RAC_CLKMULTEN1_CLKMULTLDMNIB_DEFAULT                          (_RAC_CLKMULTEN1_CLKMULTLDMNIB_DEFAULT << 6)           /**< Shifted mode DEFAULT for RAC_CLKMULTEN1     */
#define RAC_CLKMULTEN1_CLKMULTLDMNIB_disable                          (_RAC_CLKMULTEN1_CLKMULTLDMNIB_disable << 6)           /**< Shifted mode disable for RAC_CLKMULTEN1     */
#define RAC_CLKMULTEN1_CLKMULTLDMNIB_enable                           (_RAC_CLKMULTEN1_CLKMULTLDMNIB_enable << 6)            /**< Shifted mode enable for RAC_CLKMULTEN1      */
#define _RAC_CLKMULTEN1_CLKMULTRDNIBBLE_SHIFT                         7                                                      /**< Shift value for RAC_CLKMULTRDNIBBLE         */
#define _RAC_CLKMULTEN1_CLKMULTRDNIBBLE_MASK                          0x180UL                                                /**< Bit mask for RAC_CLKMULTRDNIBBLE            */
#define _RAC_CLKMULTEN1_CLKMULTRDNIBBLE_DEFAULT                       0x00000003UL                                           /**< Mode DEFAULT for RAC_CLKMULTEN1             */
#define _RAC_CLKMULTEN1_CLKMULTRDNIBBLE_quarter_nibble                0x00000000UL                                           /**< Mode quarter_nibble for RAC_CLKMULTEN1      */
#define _RAC_CLKMULTEN1_CLKMULTRDNIBBLE_fine_nibble                   0x00000001UL                                           /**< Mode fine_nibble for RAC_CLKMULTEN1         */
#define _RAC_CLKMULTEN1_CLKMULTRDNIBBLE_moderate_nibble               0x00000002UL                                           /**< Mode moderate_nibble for RAC_CLKMULTEN1     */
#define _RAC_CLKMULTEN1_CLKMULTRDNIBBLE_coarse_nibble                 0x00000003UL                                           /**< Mode coarse_nibble for RAC_CLKMULTEN1       */
#define RAC_CLKMULTEN1_CLKMULTRDNIBBLE_DEFAULT                        (_RAC_CLKMULTEN1_CLKMULTRDNIBBLE_DEFAULT << 7)         /**< Shifted mode DEFAULT for RAC_CLKMULTEN1     */
#define RAC_CLKMULTEN1_CLKMULTRDNIBBLE_quarter_nibble                 (_RAC_CLKMULTEN1_CLKMULTRDNIBBLE_quarter_nibble << 7)  /**< Shifted mode quarter_nibble for RAC_CLKMULTEN1*/
#define RAC_CLKMULTEN1_CLKMULTRDNIBBLE_fine_nibble                    (_RAC_CLKMULTEN1_CLKMULTRDNIBBLE_fine_nibble << 7)     /**< Shifted mode fine_nibble for RAC_CLKMULTEN1 */
#define RAC_CLKMULTEN1_CLKMULTRDNIBBLE_moderate_nibble                (_RAC_CLKMULTEN1_CLKMULTRDNIBBLE_moderate_nibble << 7) /**< Shifted mode moderate_nibble for RAC_CLKMULTEN1*/
#define RAC_CLKMULTEN1_CLKMULTRDNIBBLE_coarse_nibble                  (_RAC_CLKMULTEN1_CLKMULTRDNIBBLE_coarse_nibble << 7)   /**< Shifted mode coarse_nibble for RAC_CLKMULTEN1*/
#define RAC_CLKMULTEN1_CLKMULTLDCNIB                                  (0x1UL << 10)                                          /**< CLKMULTLDCNIB                               */
#define _RAC_CLKMULTEN1_CLKMULTLDCNIB_SHIFT                           10                                                     /**< Shift value for RAC_CLKMULTLDCNIB           */
#define _RAC_CLKMULTEN1_CLKMULTLDCNIB_MASK                            0x400UL                                                /**< Bit mask for RAC_CLKMULTLDCNIB              */
#define _RAC_CLKMULTEN1_CLKMULTLDCNIB_DEFAULT                         0x00000000UL                                           /**< Mode DEFAULT for RAC_CLKMULTEN1             */
#define _RAC_CLKMULTEN1_CLKMULTLDCNIB_disable                         0x00000000UL                                           /**< Mode disable for RAC_CLKMULTEN1             */
#define _RAC_CLKMULTEN1_CLKMULTLDCNIB_enable                          0x00000001UL                                           /**< Mode enable for RAC_CLKMULTEN1              */
#define RAC_CLKMULTEN1_CLKMULTLDCNIB_DEFAULT                          (_RAC_CLKMULTEN1_CLKMULTLDCNIB_DEFAULT << 10)          /**< Shifted mode DEFAULT for RAC_CLKMULTEN1     */
#define RAC_CLKMULTEN1_CLKMULTLDCNIB_disable                          (_RAC_CLKMULTEN1_CLKMULTLDCNIB_disable << 10)          /**< Shifted mode disable for RAC_CLKMULTEN1     */
#define RAC_CLKMULTEN1_CLKMULTLDCNIB_enable                           (_RAC_CLKMULTEN1_CLKMULTLDCNIB_enable << 10)           /**< Shifted mode enable for RAC_CLKMULTEN1      */
#define _RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_SHIFT                        11                                                     /**< Shift value for RAC_CLKMULTDRVAMPSEL        */
#define _RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_MASK                         0x1F800UL                                              /**< Bit mask for RAC_CLKMULTDRVAMPSEL           */
#define _RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_DEFAULT                      0x00000000UL                                           /**< Mode DEFAULT for RAC_CLKMULTEN1             */
#define _RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_off                          0x00000000UL                                           /**< Mode off for RAC_CLKMULTEN1                 */
#define _RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_slide_x1                     0x00000001UL                                           /**< Mode slide_x1 for RAC_CLKMULTEN1            */
#define _RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_slide_x2                     0x00000003UL                                           /**< Mode slide_x2 for RAC_CLKMULTEN1            */
#define _RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_slide_x3                     0x00000007UL                                           /**< Mode slide_x3 for RAC_CLKMULTEN1            */
#define _RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_slide_x4                     0x0000000FUL                                           /**< Mode slide_x4 for RAC_CLKMULTEN1            */
#define _RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_slide_x5                     0x0000001FUL                                           /**< Mode slide_x5 for RAC_CLKMULTEN1            */
#define _RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_slide_x6                     0x0000003FUL                                           /**< Mode slide_x6 for RAC_CLKMULTEN1            */
#define RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_DEFAULT                       (_RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_DEFAULT << 11)       /**< Shifted mode DEFAULT for RAC_CLKMULTEN1     */
#define RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_off                           (_RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_off << 11)           /**< Shifted mode off for RAC_CLKMULTEN1         */
#define RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_slide_x1                      (_RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_slide_x1 << 11)      /**< Shifted mode slide_x1 for RAC_CLKMULTEN1    */
#define RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_slide_x2                      (_RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_slide_x2 << 11)      /**< Shifted mode slide_x2 for RAC_CLKMULTEN1    */
#define RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_slide_x3                      (_RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_slide_x3 << 11)      /**< Shifted mode slide_x3 for RAC_CLKMULTEN1    */
#define RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_slide_x4                      (_RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_slide_x4 << 11)      /**< Shifted mode slide_x4 for RAC_CLKMULTEN1    */
#define RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_slide_x5                      (_RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_slide_x5 << 11)      /**< Shifted mode slide_x5 for RAC_CLKMULTEN1    */
#define RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_slide_x6                      (_RAC_CLKMULTEN1_CLKMULTDRVAMPSEL_slide_x6 << 11)      /**< Shifted mode slide_x6 for RAC_CLKMULTEN1    */

/* Bit fields for RAC CLKMULTCTRL */
#define _RAC_CLKMULTCTRL_RESETVALUE                                   0x000000C0UL                                          /**< Default value for RAC_CLKMULTCTRL           */
#define _RAC_CLKMULTCTRL_MASK                                         0x00007FFFUL                                          /**< Mask for RAC_CLKMULTCTRL                    */
#define _RAC_CLKMULTCTRL_CLKMULTDIVN_SHIFT                            0                                                     /**< Shift value for RAC_CLKMULTDIVN             */
#define _RAC_CLKMULTCTRL_CLKMULTDIVN_MASK                             0x7FUL                                                /**< Bit mask for RAC_CLKMULTDIVN                */
#define _RAC_CLKMULTCTRL_CLKMULTDIVN_DEFAULT                          0x00000040UL                                          /**< Mode DEFAULT for RAC_CLKMULTCTRL            */
#define RAC_CLKMULTCTRL_CLKMULTDIVN_DEFAULT                           (_RAC_CLKMULTCTRL_CLKMULTDIVN_DEFAULT << 0)           /**< Shifted mode DEFAULT for RAC_CLKMULTCTRL    */
#define _RAC_CLKMULTCTRL_CLKMULTDIVR_SHIFT                            7                                                     /**< Shift value for RAC_CLKMULTDIVR             */
#define _RAC_CLKMULTCTRL_CLKMULTDIVR_MASK                             0x380UL                                               /**< Bit mask for RAC_CLKMULTDIVR                */
#define _RAC_CLKMULTCTRL_CLKMULTDIVR_DEFAULT                          0x00000001UL                                          /**< Mode DEFAULT for RAC_CLKMULTCTRL            */
#define RAC_CLKMULTCTRL_CLKMULTDIVR_DEFAULT                           (_RAC_CLKMULTCTRL_CLKMULTDIVR_DEFAULT << 7)           /**< Shifted mode DEFAULT for RAC_CLKMULTCTRL    */
#define _RAC_CLKMULTCTRL_CLKMULTDIVX_SHIFT                            10                                                    /**< Shift value for RAC_CLKMULTDIVX             */
#define _RAC_CLKMULTCTRL_CLKMULTDIVX_MASK                             0x1C00UL                                              /**< Bit mask for RAC_CLKMULTDIVX                */
#define _RAC_CLKMULTCTRL_CLKMULTDIVX_DEFAULT                          0x00000000UL                                          /**< Mode DEFAULT for RAC_CLKMULTCTRL            */
#define _RAC_CLKMULTCTRL_CLKMULTDIVX_div_1                            0x00000000UL                                          /**< Mode div_1 for RAC_CLKMULTCTRL              */
#define _RAC_CLKMULTCTRL_CLKMULTDIVX_div_2                            0x00000001UL                                          /**< Mode div_2 for RAC_CLKMULTCTRL              */
#define _RAC_CLKMULTCTRL_CLKMULTDIVX_div_4                            0x00000002UL                                          /**< Mode div_4 for RAC_CLKMULTCTRL              */
#define _RAC_CLKMULTCTRL_CLKMULTDIVX_div_6                            0x00000003UL                                          /**< Mode div_6 for RAC_CLKMULTCTRL              */
#define _RAC_CLKMULTCTRL_CLKMULTDIVX_div_8                            0x00000004UL                                          /**< Mode div_8 for RAC_CLKMULTCTRL              */
#define _RAC_CLKMULTCTRL_CLKMULTDIVX_div10                            0x00000005UL                                          /**< Mode div10 for RAC_CLKMULTCTRL              */
#define _RAC_CLKMULTCTRL_CLKMULTDIVX_div12                            0x00000006UL                                          /**< Mode div12 for RAC_CLKMULTCTRL              */
#define _RAC_CLKMULTCTRL_CLKMULTDIVX_div14                            0x00000007UL                                          /**< Mode div14 for RAC_CLKMULTCTRL              */
#define RAC_CLKMULTCTRL_CLKMULTDIVX_DEFAULT                           (_RAC_CLKMULTCTRL_CLKMULTDIVX_DEFAULT << 10)          /**< Shifted mode DEFAULT for RAC_CLKMULTCTRL    */
#define RAC_CLKMULTCTRL_CLKMULTDIVX_div_1                             (_RAC_CLKMULTCTRL_CLKMULTDIVX_div_1 << 10)            /**< Shifted mode div_1 for RAC_CLKMULTCTRL      */
#define RAC_CLKMULTCTRL_CLKMULTDIVX_div_2                             (_RAC_CLKMULTCTRL_CLKMULTDIVX_div_2 << 10)            /**< Shifted mode div_2 for RAC_CLKMULTCTRL      */
#define RAC_CLKMULTCTRL_CLKMULTDIVX_div_4                             (_RAC_CLKMULTCTRL_CLKMULTDIVX_div_4 << 10)            /**< Shifted mode div_4 for RAC_CLKMULTCTRL      */
#define RAC_CLKMULTCTRL_CLKMULTDIVX_div_6                             (_RAC_CLKMULTCTRL_CLKMULTDIVX_div_6 << 10)            /**< Shifted mode div_6 for RAC_CLKMULTCTRL      */
#define RAC_CLKMULTCTRL_CLKMULTDIVX_div_8                             (_RAC_CLKMULTCTRL_CLKMULTDIVX_div_8 << 10)            /**< Shifted mode div_8 for RAC_CLKMULTCTRL      */
#define RAC_CLKMULTCTRL_CLKMULTDIVX_div10                             (_RAC_CLKMULTCTRL_CLKMULTDIVX_div10 << 10)            /**< Shifted mode div10 for RAC_CLKMULTCTRL      */
#define RAC_CLKMULTCTRL_CLKMULTDIVX_div12                             (_RAC_CLKMULTCTRL_CLKMULTDIVX_div12 << 10)            /**< Shifted mode div12 for RAC_CLKMULTCTRL      */
#define RAC_CLKMULTCTRL_CLKMULTDIVX_div14                             (_RAC_CLKMULTCTRL_CLKMULTDIVX_div14 << 10)            /**< Shifted mode div14 for RAC_CLKMULTCTRL      */
#define RAC_CLKMULTCTRL_CLKMULTENRESYNC                               (0x1UL << 13)                                         /**< CLKMULTENRESYNC                             */
#define _RAC_CLKMULTCTRL_CLKMULTENRESYNC_SHIFT                        13                                                    /**< Shift value for RAC_CLKMULTENRESYNC         */
#define _RAC_CLKMULTCTRL_CLKMULTENRESYNC_MASK                         0x2000UL                                              /**< Bit mask for RAC_CLKMULTENRESYNC            */
#define _RAC_CLKMULTCTRL_CLKMULTENRESYNC_DEFAULT                      0x00000000UL                                          /**< Mode DEFAULT for RAC_CLKMULTCTRL            */
#define _RAC_CLKMULTCTRL_CLKMULTENRESYNC_disable_sync                 0x00000000UL                                          /**< Mode disable_sync for RAC_CLKMULTCTRL       */
#define _RAC_CLKMULTCTRL_CLKMULTENRESYNC_enable_sync                  0x00000001UL                                          /**< Mode enable_sync for RAC_CLKMULTCTRL        */
#define RAC_CLKMULTCTRL_CLKMULTENRESYNC_DEFAULT                       (_RAC_CLKMULTCTRL_CLKMULTENRESYNC_DEFAULT << 13)      /**< Shifted mode DEFAULT for RAC_CLKMULTCTRL    */
#define RAC_CLKMULTCTRL_CLKMULTENRESYNC_disable_sync                  (_RAC_CLKMULTCTRL_CLKMULTENRESYNC_disable_sync << 13) /**< Shifted mode disable_sync for RAC_CLKMULTCTRL*/
#define RAC_CLKMULTCTRL_CLKMULTENRESYNC_enable_sync                   (_RAC_CLKMULTCTRL_CLKMULTENRESYNC_enable_sync << 13)  /**< Shifted mode enable_sync for RAC_CLKMULTCTRL*/
#define RAC_CLKMULTCTRL_CLKMULTVALID                                  (0x1UL << 14)                                         /**< CLKMULTVALID                                */
#define _RAC_CLKMULTCTRL_CLKMULTVALID_SHIFT                           14                                                    /**< Shift value for RAC_CLKMULTVALID            */
#define _RAC_CLKMULTCTRL_CLKMULTVALID_MASK                            0x4000UL                                              /**< Bit mask for RAC_CLKMULTVALID               */
#define _RAC_CLKMULTCTRL_CLKMULTVALID_DEFAULT                         0x00000000UL                                          /**< Mode DEFAULT for RAC_CLKMULTCTRL            */
#define _RAC_CLKMULTCTRL_CLKMULTVALID_invalid                         0x00000000UL                                          /**< Mode invalid for RAC_CLKMULTCTRL            */
#define _RAC_CLKMULTCTRL_CLKMULTVALID_valid                           0x00000001UL                                          /**< Mode valid for RAC_CLKMULTCTRL              */
#define RAC_CLKMULTCTRL_CLKMULTVALID_DEFAULT                          (_RAC_CLKMULTCTRL_CLKMULTVALID_DEFAULT << 14)         /**< Shifted mode DEFAULT for RAC_CLKMULTCTRL    */
#define RAC_CLKMULTCTRL_CLKMULTVALID_invalid                          (_RAC_CLKMULTCTRL_CLKMULTVALID_invalid << 14)         /**< Shifted mode invalid for RAC_CLKMULTCTRL    */
#define RAC_CLKMULTCTRL_CLKMULTVALID_valid                            (_RAC_CLKMULTCTRL_CLKMULTVALID_valid << 14)           /**< Shifted mode valid for RAC_CLKMULTCTRL      */

/* Bit fields for RAC CLKMULTSTATUS */
#define _RAC_CLKMULTSTATUS_RESETVALUE                                 0x00000000UL                                       /**< Default value for RAC_CLKMULTSTATUS         */
#define _RAC_CLKMULTSTATUS_MASK                                       0x0000001FUL                                       /**< Mask for RAC_CLKMULTSTATUS                  */
#define _RAC_CLKMULTSTATUS_CLKMULTOUTNIBBLE_SHIFT                     0                                                  /**< Shift value for RAC_CLKMULTOUTNIBBLE        */
#define _RAC_CLKMULTSTATUS_CLKMULTOUTNIBBLE_MASK                      0xFUL                                              /**< Bit mask for RAC_CLKMULTOUTNIBBLE           */
#define _RAC_CLKMULTSTATUS_CLKMULTOUTNIBBLE_DEFAULT                   0x00000000UL                                       /**< Mode DEFAULT for RAC_CLKMULTSTATUS          */
#define RAC_CLKMULTSTATUS_CLKMULTOUTNIBBLE_DEFAULT                    (_RAC_CLKMULTSTATUS_CLKMULTOUTNIBBLE_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_CLKMULTSTATUS  */
#define RAC_CLKMULTSTATUS_CLKMULTACKVALID                             (0x1UL << 4)                                       /**< CLKMULTACKVALID                             */
#define _RAC_CLKMULTSTATUS_CLKMULTACKVALID_SHIFT                      4                                                  /**< Shift value for RAC_CLKMULTACKVALID         */
#define _RAC_CLKMULTSTATUS_CLKMULTACKVALID_MASK                       0x10UL                                             /**< Bit mask for RAC_CLKMULTACKVALID            */
#define _RAC_CLKMULTSTATUS_CLKMULTACKVALID_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for RAC_CLKMULTSTATUS          */
#define _RAC_CLKMULTSTATUS_CLKMULTACKVALID_invalid                    0x00000000UL                                       /**< Mode invalid for RAC_CLKMULTSTATUS          */
#define _RAC_CLKMULTSTATUS_CLKMULTACKVALID_valid                      0x00000001UL                                       /**< Mode valid for RAC_CLKMULTSTATUS            */
#define RAC_CLKMULTSTATUS_CLKMULTACKVALID_DEFAULT                     (_RAC_CLKMULTSTATUS_CLKMULTACKVALID_DEFAULT << 4)  /**< Shifted mode DEFAULT for RAC_CLKMULTSTATUS  */
#define RAC_CLKMULTSTATUS_CLKMULTACKVALID_invalid                     (_RAC_CLKMULTSTATUS_CLKMULTACKVALID_invalid << 4)  /**< Shifted mode invalid for RAC_CLKMULTSTATUS  */
#define RAC_CLKMULTSTATUS_CLKMULTACKVALID_valid                       (_RAC_CLKMULTSTATUS_CLKMULTACKVALID_valid << 4)    /**< Shifted mode valid for RAC_CLKMULTSTATUS    */

/* Bit fields for RAC IFADCTRIM0 */
#define _RAC_IFADCTRIM0_RESETVALUE                                    0x11512C6CUL                                            /**< Default value for RAC_IFADCTRIM0            */
#define _RAC_IFADCTRIM0_MASK                                          0x7FFFFFFDUL                                            /**< Mask for RAC_IFADCTRIM0                     */
#define RAC_IFADCTRIM0_IFADCCLKSEL                                    (0x1UL << 0)                                            /**< IFADCCLKSEL                                 */
#define _RAC_IFADCTRIM0_IFADCCLKSEL_SHIFT                             0                                                       /**< Shift value for RAC_IFADCCLKSEL             */
#define _RAC_IFADCTRIM0_IFADCCLKSEL_MASK                              0x1UL                                                   /**< Bit mask for RAC_IFADCCLKSEL                */
#define _RAC_IFADCTRIM0_IFADCCLKSEL_DEFAULT                           0x00000000UL                                            /**< Mode DEFAULT for RAC_IFADCTRIM0             */
#define _RAC_IFADCTRIM0_IFADCCLKSEL_clk_2p4g                          0x00000000UL                                            /**< Mode clk_2p4g for RAC_IFADCTRIM0            */
#define _RAC_IFADCTRIM0_IFADCCLKSEL_clk_subg                          0x00000001UL                                            /**< Mode clk_subg for RAC_IFADCTRIM0            */
#define RAC_IFADCTRIM0_IFADCCLKSEL_DEFAULT                            (_RAC_IFADCTRIM0_IFADCCLKSEL_DEFAULT << 0)              /**< Shifted mode DEFAULT for RAC_IFADCTRIM0     */
#define RAC_IFADCTRIM0_IFADCCLKSEL_clk_2p4g                           (_RAC_IFADCTRIM0_IFADCCLKSEL_clk_2p4g << 0)             /**< Shifted mode clk_2p4g for RAC_IFADCTRIM0    */
#define RAC_IFADCTRIM0_IFADCCLKSEL_clk_subg                           (_RAC_IFADCTRIM0_IFADCCLKSEL_clk_subg << 0)             /**< Shifted mode clk_subg for RAC_IFADCTRIM0    */
#define _RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_SHIFT                    2                                                       /**< Shift value for RAC_IFADCLDOSERIESAMPLVL    */
#define _RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_MASK                     0x1CUL                                                  /**< Bit mask for RAC_IFADCLDOSERIESAMPLVL       */
#define _RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_DEFAULT                  0x00000003UL                                            /**< Mode DEFAULT for RAC_IFADCTRIM0             */
#define _RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p225                   0x00000000UL                                            /**< Mode v1p225 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p250                   0x00000001UL                                            /**< Mode v1p250 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p275                   0x00000002UL                                            /**< Mode v1p275 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p300                   0x00000003UL                                            /**< Mode v1p300 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p325                   0x00000004UL                                            /**< Mode v1p325 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p350                   0x00000005UL                                            /**< Mode v1p350 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p375                   0x00000006UL                                            /**< Mode v1p375 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p400                   0x00000007UL                                            /**< Mode v1p400 for RAC_IFADCTRIM0              */
#define RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_DEFAULT                   (_RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_DEFAULT << 2)     /**< Shifted mode DEFAULT for RAC_IFADCTRIM0     */
#define RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p225                    (_RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p225 << 2)      /**< Shifted mode v1p225 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p250                    (_RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p250 << 2)      /**< Shifted mode v1p250 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p275                    (_RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p275 << 2)      /**< Shifted mode v1p275 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p300                    (_RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p300 << 2)      /**< Shifted mode v1p300 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p325                    (_RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p325 << 2)      /**< Shifted mode v1p325 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p350                    (_RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p350 << 2)      /**< Shifted mode v1p350 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p375                    (_RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p375 << 2)      /**< Shifted mode v1p375 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p400                    (_RAC_IFADCTRIM0_IFADCLDOSERIESAMPLVL_v1p400 << 2)      /**< Shifted mode v1p400 for RAC_IFADCTRIM0      */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_SHIFT                    5                                                       /**< Shift value for RAC_IFADCLDOSHUNTAMPLVL1    */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_MASK                     0xE0UL                                                  /**< Bit mask for RAC_IFADCLDOSHUNTAMPLVL1       */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_DEFAULT                  0x00000003UL                                            /**< Mode DEFAULT for RAC_IFADCTRIM0             */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p125                   0x00000000UL                                            /**< Mode v1p125 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p150                   0x00000001UL                                            /**< Mode v1p150 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p175                   0x00000002UL                                            /**< Mode v1p175 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p200                   0x00000003UL                                            /**< Mode v1p200 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p225                   0x00000004UL                                            /**< Mode v1p225 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p250                   0x00000005UL                                            /**< Mode v1p250 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p275                   0x00000006UL                                            /**< Mode v1p275 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p300                   0x00000007UL                                            /**< Mode v1p300 for RAC_IFADCTRIM0              */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_DEFAULT                   (_RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_DEFAULT << 5)     /**< Shifted mode DEFAULT for RAC_IFADCTRIM0     */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p125                    (_RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p125 << 5)      /**< Shifted mode v1p125 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p150                    (_RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p150 << 5)      /**< Shifted mode v1p150 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p175                    (_RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p175 << 5)      /**< Shifted mode v1p175 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p200                    (_RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p200 << 5)      /**< Shifted mode v1p200 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p225                    (_RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p225 << 5)      /**< Shifted mode v1p225 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p250                    (_RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p250 << 5)      /**< Shifted mode v1p250 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p275                    (_RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p275 << 5)      /**< Shifted mode v1p275 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p300                    (_RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL1_v1p300 << 5)      /**< Shifted mode v1p300 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL2                           (0x1UL << 8)                                            /**< IFADCLDOSHUNTAMPLVL2                        */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL2_SHIFT                    8                                                       /**< Shift value for RAC_IFADCLDOSHUNTAMPLVL2    */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL2_MASK                     0x100UL                                                 /**< Bit mask for RAC_IFADCLDOSHUNTAMPLVL2       */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL2_DEFAULT                  0x00000000UL                                            /**< Mode DEFAULT for RAC_IFADCTRIM0             */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL2_disable                  0x00000000UL                                            /**< Mode disable for RAC_IFADCTRIM0             */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL2_enable                   0x00000001UL                                            /**< Mode enable for RAC_IFADCTRIM0              */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL2_DEFAULT                   (_RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL2_DEFAULT << 8)     /**< Shifted mode DEFAULT for RAC_IFADCTRIM0     */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL2_disable                   (_RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL2_disable << 8)     /**< Shifted mode disable for RAC_IFADCTRIM0     */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL2_enable                    (_RAC_IFADCTRIM0_IFADCLDOSHUNTAMPLVL2_enable << 8)      /**< Shifted mode enable for RAC_IFADCTRIM0      */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_SHIFT                    9                                                       /**< Shift value for RAC_IFADCLDOSHUNTCURLVL1    */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_MASK                     0xE00UL                                                 /**< Bit mask for RAC_IFADCLDOSHUNTCURLVL1       */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_DEFAULT                  0x00000006UL                                            /**< Mode DEFAULT for RAC_IFADCTRIM0             */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i55u                     0x00000000UL                                            /**< Mode i55u for RAC_IFADCTRIM0                */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i65u                     0x00000001UL                                            /**< Mode i65u for RAC_IFADCTRIM0                */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i70u                     0x00000002UL                                            /**< Mode i70u for RAC_IFADCTRIM0                */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i85u                     0x00000003UL                                            /**< Mode i85u for RAC_IFADCTRIM0                */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i85u2                    0x00000004UL                                            /**< Mode i85u2 for RAC_IFADCTRIM0               */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i95u                     0x00000005UL                                            /**< Mode i95u for RAC_IFADCTRIM0                */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i100u                    0x00000006UL                                            /**< Mode i100u for RAC_IFADCTRIM0               */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i110u                    0x00000007UL                                            /**< Mode i110u for RAC_IFADCTRIM0               */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_DEFAULT                   (_RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_DEFAULT << 9)     /**< Shifted mode DEFAULT for RAC_IFADCTRIM0     */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i55u                      (_RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i55u << 9)        /**< Shifted mode i55u for RAC_IFADCTRIM0        */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i65u                      (_RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i65u << 9)        /**< Shifted mode i65u for RAC_IFADCTRIM0        */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i70u                      (_RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i70u << 9)        /**< Shifted mode i70u for RAC_IFADCTRIM0        */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i85u                      (_RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i85u << 9)        /**< Shifted mode i85u for RAC_IFADCTRIM0        */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i85u2                     (_RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i85u2 << 9)       /**< Shifted mode i85u2 for RAC_IFADCTRIM0       */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i95u                      (_RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i95u << 9)        /**< Shifted mode i95u for RAC_IFADCTRIM0        */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i100u                     (_RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i100u << 9)       /**< Shifted mode i100u for RAC_IFADCTRIM0       */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i110u                     (_RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL1_i110u << 9)       /**< Shifted mode i110u for RAC_IFADCTRIM0       */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_SHIFT                    12                                                      /**< Shift value for RAC_IFADCLDOSHUNTCURLVL2    */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_MASK                     0x7000UL                                                /**< Bit mask for RAC_IFADCLDOSHUNTCURLVL2       */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_DEFAULT                  0x00000002UL                                            /**< Mode DEFAULT for RAC_IFADCTRIM0             */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i4u                      0x00000000UL                                            /**< Mode i4u for RAC_IFADCTRIM0                 */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i4p5u                    0x00000001UL                                            /**< Mode i4p5u for RAC_IFADCTRIM0               */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i5u                      0x00000002UL                                            /**< Mode i5u for RAC_IFADCTRIM0                 */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i5p5u                    0x00000003UL                                            /**< Mode i5p5u for RAC_IFADCTRIM0               */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i5u2                     0x00000004UL                                            /**< Mode i5u2 for RAC_IFADCTRIM0                */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i5p5u2                   0x00000005UL                                            /**< Mode i5p5u2 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i6u                      0x00000006UL                                            /**< Mode i6u for RAC_IFADCTRIM0                 */
#define _RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i6p5u                    0x00000007UL                                            /**< Mode i6p5u for RAC_IFADCTRIM0               */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_DEFAULT                   (_RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_DEFAULT << 12)    /**< Shifted mode DEFAULT for RAC_IFADCTRIM0     */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i4u                       (_RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i4u << 12)        /**< Shifted mode i4u for RAC_IFADCTRIM0         */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i4p5u                     (_RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i4p5u << 12)      /**< Shifted mode i4p5u for RAC_IFADCTRIM0       */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i5u                       (_RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i5u << 12)        /**< Shifted mode i5u for RAC_IFADCTRIM0         */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i5p5u                     (_RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i5p5u << 12)      /**< Shifted mode i5p5u for RAC_IFADCTRIM0       */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i5u2                      (_RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i5u2 << 12)       /**< Shifted mode i5u2 for RAC_IFADCTRIM0        */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i5p5u2                    (_RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i5p5u2 << 12)     /**< Shifted mode i5p5u2 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i6u                       (_RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i6u << 12)        /**< Shifted mode i6u for RAC_IFADCTRIM0         */
#define RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i6p5u                     (_RAC_IFADCTRIM0_IFADCLDOSHUNTCURLVL2_i6p5u << 12)      /**< Shifted mode i6p5u for RAC_IFADCTRIM0       */
#define _RAC_IFADCTRIM0_IFADCOTACURRENT_SHIFT                         15                                                      /**< Shift value for RAC_IFADCOTACURRENT         */
#define _RAC_IFADCTRIM0_IFADCOTACURRENT_MASK                          0x38000UL                                               /**< Bit mask for RAC_IFADCOTACURRENT            */
#define _RAC_IFADCTRIM0_IFADCOTACURRENT_DEFAULT                       0x00000002UL                                            /**< Mode DEFAULT for RAC_IFADCTRIM0             */
#define _RAC_IFADCTRIM0_IFADCOTACURRENT_i3u                           0x00000000UL                                            /**< Mode i3u for RAC_IFADCTRIM0                 */
#define _RAC_IFADCTRIM0_IFADCOTACURRENT_i3p5u                         0x00000001UL                                            /**< Mode i3p5u for RAC_IFADCTRIM0               */
#define _RAC_IFADCTRIM0_IFADCOTACURRENT_i4u                           0x00000002UL                                            /**< Mode i4u for RAC_IFADCTRIM0                 */
#define _RAC_IFADCTRIM0_IFADCOTACURRENT_i4p5u                         0x00000003UL                                            /**< Mode i4p5u for RAC_IFADCTRIM0               */
#define _RAC_IFADCTRIM0_IFADCOTACURRENT_i4u2                          0x00000004UL                                            /**< Mode i4u2 for RAC_IFADCTRIM0                */
#define _RAC_IFADCTRIM0_IFADCOTACURRENT_i4p5u2                        0x00000005UL                                            /**< Mode i4p5u2 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCOTACURRENT_i5u                           0x00000006UL                                            /**< Mode i5u for RAC_IFADCTRIM0                 */
#define _RAC_IFADCTRIM0_IFADCOTACURRENT_i5p5u                         0x00000007UL                                            /**< Mode i5p5u for RAC_IFADCTRIM0               */
#define RAC_IFADCTRIM0_IFADCOTACURRENT_DEFAULT                        (_RAC_IFADCTRIM0_IFADCOTACURRENT_DEFAULT << 15)         /**< Shifted mode DEFAULT for RAC_IFADCTRIM0     */
#define RAC_IFADCTRIM0_IFADCOTACURRENT_i3u                            (_RAC_IFADCTRIM0_IFADCOTACURRENT_i3u << 15)             /**< Shifted mode i3u for RAC_IFADCTRIM0         */
#define RAC_IFADCTRIM0_IFADCOTACURRENT_i3p5u                          (_RAC_IFADCTRIM0_IFADCOTACURRENT_i3p5u << 15)           /**< Shifted mode i3p5u for RAC_IFADCTRIM0       */
#define RAC_IFADCTRIM0_IFADCOTACURRENT_i4u                            (_RAC_IFADCTRIM0_IFADCOTACURRENT_i4u << 15)             /**< Shifted mode i4u for RAC_IFADCTRIM0         */
#define RAC_IFADCTRIM0_IFADCOTACURRENT_i4p5u                          (_RAC_IFADCTRIM0_IFADCOTACURRENT_i4p5u << 15)           /**< Shifted mode i4p5u for RAC_IFADCTRIM0       */
#define RAC_IFADCTRIM0_IFADCOTACURRENT_i4u2                           (_RAC_IFADCTRIM0_IFADCOTACURRENT_i4u2 << 15)            /**< Shifted mode i4u2 for RAC_IFADCTRIM0        */
#define RAC_IFADCTRIM0_IFADCOTACURRENT_i4p5u2                         (_RAC_IFADCTRIM0_IFADCOTACURRENT_i4p5u2 << 15)          /**< Shifted mode i4p5u2 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCOTACURRENT_i5u                            (_RAC_IFADCTRIM0_IFADCOTACURRENT_i5u << 15)             /**< Shifted mode i5u for RAC_IFADCTRIM0         */
#define RAC_IFADCTRIM0_IFADCOTACURRENT_i5p5u                          (_RAC_IFADCTRIM0_IFADCOTACURRENT_i5p5u << 15)           /**< Shifted mode i5p5u for RAC_IFADCTRIM0       */
#define _RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_SHIFT                       18                                                      /**< Shift value for RAC_IFADCREFBUFAMPLVL       */
#define _RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_MASK                        0x1C0000UL                                              /**< Bit mask for RAC_IFADCREFBUFAMPLVL          */
#define _RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_DEFAULT                     0x00000004UL                                            /**< Mode DEFAULT for RAC_IFADCTRIM0             */
#define _RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v0p88                       0x00000000UL                                            /**< Mode v0p88 for RAC_IFADCTRIM0               */
#define _RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v0p91                       0x00000001UL                                            /**< Mode v0p91 for RAC_IFADCTRIM0               */
#define _RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v0p94                       0x00000002UL                                            /**< Mode v0p94 for RAC_IFADCTRIM0               */
#define _RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v0p97                       0x00000003UL                                            /**< Mode v0p97 for RAC_IFADCTRIM0               */
#define _RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v1p00                       0x00000004UL                                            /**< Mode v1p00 for RAC_IFADCTRIM0               */
#define _RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v1p03                       0x00000005UL                                            /**< Mode v1p03 for RAC_IFADCTRIM0               */
#define _RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v1p06                       0x00000006UL                                            /**< Mode v1p06 for RAC_IFADCTRIM0               */
#define _RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v1p09                       0x00000007UL                                            /**< Mode v1p09 for RAC_IFADCTRIM0               */
#define RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_DEFAULT                      (_RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_DEFAULT << 18)       /**< Shifted mode DEFAULT for RAC_IFADCTRIM0     */
#define RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v0p88                        (_RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v0p88 << 18)         /**< Shifted mode v0p88 for RAC_IFADCTRIM0       */
#define RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v0p91                        (_RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v0p91 << 18)         /**< Shifted mode v0p91 for RAC_IFADCTRIM0       */
#define RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v0p94                        (_RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v0p94 << 18)         /**< Shifted mode v0p94 for RAC_IFADCTRIM0       */
#define RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v0p97                        (_RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v0p97 << 18)         /**< Shifted mode v0p97 for RAC_IFADCTRIM0       */
#define RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v1p00                        (_RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v1p00 << 18)         /**< Shifted mode v1p00 for RAC_IFADCTRIM0       */
#define RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v1p03                        (_RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v1p03 << 18)         /**< Shifted mode v1p03 for RAC_IFADCTRIM0       */
#define RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v1p06                        (_RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v1p06 << 18)         /**< Shifted mode v1p06 for RAC_IFADCTRIM0       */
#define RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v1p09                        (_RAC_IFADCTRIM0_IFADCREFBUFAMPLVL_v1p09 << 18)         /**< Shifted mode v1p09 for RAC_IFADCTRIM0       */
#define _RAC_IFADCTRIM0_IFADCREFBUFCURLVL_SHIFT                       21                                                      /**< Shift value for RAC_IFADCREFBUFCURLVL       */
#define _RAC_IFADCTRIM0_IFADCREFBUFCURLVL_MASK                        0xE00000UL                                              /**< Bit mask for RAC_IFADCREFBUFCURLVL          */
#define _RAC_IFADCTRIM0_IFADCREFBUFCURLVL_DEFAULT                     0x00000002UL                                            /**< Mode DEFAULT for RAC_IFADCTRIM0             */
#define _RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i4u                         0x00000000UL                                            /**< Mode i4u for RAC_IFADCTRIM0                 */
#define _RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i4p5u                       0x00000001UL                                            /**< Mode i4p5u for RAC_IFADCTRIM0               */
#define _RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i5u                         0x00000002UL                                            /**< Mode i5u for RAC_IFADCTRIM0                 */
#define _RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i5p5u                       0x00000003UL                                            /**< Mode i5p5u for RAC_IFADCTRIM0               */
#define _RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i5u2                        0x00000004UL                                            /**< Mode i5u2 for RAC_IFADCTRIM0                */
#define _RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i5p5u2                      0x00000005UL                                            /**< Mode i5p5u2 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i6u                         0x00000006UL                                            /**< Mode i6u for RAC_IFADCTRIM0                 */
#define _RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i6p5u                       0x00000007UL                                            /**< Mode i6p5u for RAC_IFADCTRIM0               */
#define RAC_IFADCTRIM0_IFADCREFBUFCURLVL_DEFAULT                      (_RAC_IFADCTRIM0_IFADCREFBUFCURLVL_DEFAULT << 21)       /**< Shifted mode DEFAULT for RAC_IFADCTRIM0     */
#define RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i4u                          (_RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i4u << 21)           /**< Shifted mode i4u for RAC_IFADCTRIM0         */
#define RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i4p5u                        (_RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i4p5u << 21)         /**< Shifted mode i4p5u for RAC_IFADCTRIM0       */
#define RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i5u                          (_RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i5u << 21)           /**< Shifted mode i5u for RAC_IFADCTRIM0         */
#define RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i5p5u                        (_RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i5p5u << 21)         /**< Shifted mode i5p5u for RAC_IFADCTRIM0       */
#define RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i5u2                         (_RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i5u2 << 21)          /**< Shifted mode i5u2 for RAC_IFADCTRIM0        */
#define RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i5p5u2                       (_RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i5p5u2 << 21)        /**< Shifted mode i5p5u2 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i6u                          (_RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i6u << 21)           /**< Shifted mode i6u for RAC_IFADCTRIM0         */
#define RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i6p5u                        (_RAC_IFADCTRIM0_IFADCREFBUFCURLVL_i6p5u << 21)         /**< Shifted mode i6p5u for RAC_IFADCTRIM0       */
#define _RAC_IFADCTRIM0_IFADCSIDETONEAMP_SHIFT                        24                                                      /**< Shift value for RAC_IFADCSIDETONEAMP        */
#define _RAC_IFADCTRIM0_IFADCSIDETONEAMP_MASK                         0x7000000UL                                             /**< Bit mask for RAC_IFADCSIDETONEAMP           */
#define _RAC_IFADCTRIM0_IFADCSIDETONEAMP_DEFAULT                      0x00000001UL                                            /**< Mode DEFAULT for RAC_IFADCTRIM0             */
#define _RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_5p68mV                  0x00000000UL                                            /**< Mode diff_5p68mV for RAC_IFADCTRIM0         */
#define _RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_29p1mV                  0x00000001UL                                            /**< Mode diff_29p1mV for RAC_IFADCTRIM0         */
#define _RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_9p73mV                  0x00000002UL                                            /**< Mode diff_9p73mV for RAC_IFADCTRIM0         */
#define _RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_76p9mV                  0x00000003UL                                            /**< Mode diff_76p9mV for RAC_IFADCTRIM0         */
#define _RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_9p68_mV                 0x00000004UL                                            /**< Mode diff_9p68_mV for RAC_IFADCTRIM0        */
#define _RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_51_mV                   0x00000005UL                                            /**< Mode diff_51_mV for RAC_IFADCTRIM0          */
#define _RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_17p2_mV                 0x00000006UL                                            /**< Mode diff_17p2_mV for RAC_IFADCTRIM0        */
#define _RAC_IFADCTRIM0_IFADCSIDETONEAMP_disable                      0x00000007UL                                            /**< Mode disable for RAC_IFADCTRIM0             */
#define RAC_IFADCTRIM0_IFADCSIDETONEAMP_DEFAULT                       (_RAC_IFADCTRIM0_IFADCSIDETONEAMP_DEFAULT << 24)        /**< Shifted mode DEFAULT for RAC_IFADCTRIM0     */
#define RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_5p68mV                   (_RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_5p68mV << 24)    /**< Shifted mode diff_5p68mV for RAC_IFADCTRIM0 */
#define RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_29p1mV                   (_RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_29p1mV << 24)    /**< Shifted mode diff_29p1mV for RAC_IFADCTRIM0 */
#define RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_9p73mV                   (_RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_9p73mV << 24)    /**< Shifted mode diff_9p73mV for RAC_IFADCTRIM0 */
#define RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_76p9mV                   (_RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_76p9mV << 24)    /**< Shifted mode diff_76p9mV for RAC_IFADCTRIM0 */
#define RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_9p68_mV                  (_RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_9p68_mV << 24)   /**< Shifted mode diff_9p68_mV for RAC_IFADCTRIM0*/
#define RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_51_mV                    (_RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_51_mV << 24)     /**< Shifted mode diff_51_mV for RAC_IFADCTRIM0  */
#define RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_17p2_mV                  (_RAC_IFADCTRIM0_IFADCSIDETONEAMP_diff_17p2_mV << 24)   /**< Shifted mode diff_17p2_mV for RAC_IFADCTRIM0*/
#define RAC_IFADCTRIM0_IFADCSIDETONEAMP_disable                       (_RAC_IFADCTRIM0_IFADCSIDETONEAMP_disable << 24)        /**< Shifted mode disable for RAC_IFADCTRIM0     */
#define _RAC_IFADCTRIM0_IFADCSIDETONEFREQ_SHIFT                       27                                                      /**< Shift value for RAC_IFADCSIDETONEFREQ       */
#define _RAC_IFADCTRIM0_IFADCSIDETONEFREQ_MASK                        0x38000000UL                                            /**< Bit mask for RAC_IFADCSIDETONEFREQ          */
#define _RAC_IFADCTRIM0_IFADCSIDETONEFREQ_DEFAULT                     0x00000002UL                                            /**< Mode DEFAULT for RAC_IFADCTRIM0             */
#define _RAC_IFADCTRIM0_IFADCSIDETONEFREQ_na0                         0x00000000UL                                            /**< Mode na0 for RAC_IFADCTRIM0                 */
#define _RAC_IFADCTRIM0_IFADCSIDETONEFREQ_div_128                     0x00000001UL                                            /**< Mode div_128 for RAC_IFADCTRIM0             */
#define _RAC_IFADCTRIM0_IFADCSIDETONEFREQ_div_64                      0x00000002UL                                            /**< Mode div_64 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCSIDETONEFREQ_div_32                      0x00000003UL                                            /**< Mode div_32 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCSIDETONEFREQ_div_16                      0x00000004UL                                            /**< Mode div_16 for RAC_IFADCTRIM0              */
#define _RAC_IFADCTRIM0_IFADCSIDETONEFREQ_div_8                       0x00000005UL                                            /**< Mode div_8 for RAC_IFADCTRIM0               */
#define _RAC_IFADCTRIM0_IFADCSIDETONEFREQ_div_4                       0x00000006UL                                            /**< Mode div_4 for RAC_IFADCTRIM0               */
#define _RAC_IFADCTRIM0_IFADCSIDETONEFREQ_na7                         0x00000007UL                                            /**< Mode na7 for RAC_IFADCTRIM0                 */
#define RAC_IFADCTRIM0_IFADCSIDETONEFREQ_DEFAULT                      (_RAC_IFADCTRIM0_IFADCSIDETONEFREQ_DEFAULT << 27)       /**< Shifted mode DEFAULT for RAC_IFADCTRIM0     */
#define RAC_IFADCTRIM0_IFADCSIDETONEFREQ_na0                          (_RAC_IFADCTRIM0_IFADCSIDETONEFREQ_na0 << 27)           /**< Shifted mode na0 for RAC_IFADCTRIM0         */
#define RAC_IFADCTRIM0_IFADCSIDETONEFREQ_div_128                      (_RAC_IFADCTRIM0_IFADCSIDETONEFREQ_div_128 << 27)       /**< Shifted mode div_128 for RAC_IFADCTRIM0     */
#define RAC_IFADCTRIM0_IFADCSIDETONEFREQ_div_64                       (_RAC_IFADCTRIM0_IFADCSIDETONEFREQ_div_64 << 27)        /**< Shifted mode div_64 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCSIDETONEFREQ_div_32                       (_RAC_IFADCTRIM0_IFADCSIDETONEFREQ_div_32 << 27)        /**< Shifted mode div_32 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCSIDETONEFREQ_div_16                       (_RAC_IFADCTRIM0_IFADCSIDETONEFREQ_div_16 << 27)        /**< Shifted mode div_16 for RAC_IFADCTRIM0      */
#define RAC_IFADCTRIM0_IFADCSIDETONEFREQ_div_8                        (_RAC_IFADCTRIM0_IFADCSIDETONEFREQ_div_8 << 27)         /**< Shifted mode div_8 for RAC_IFADCTRIM0       */
#define RAC_IFADCTRIM0_IFADCSIDETONEFREQ_div_4                        (_RAC_IFADCTRIM0_IFADCSIDETONEFREQ_div_4 << 27)         /**< Shifted mode div_4 for RAC_IFADCTRIM0       */
#define RAC_IFADCTRIM0_IFADCSIDETONEFREQ_na7                          (_RAC_IFADCTRIM0_IFADCSIDETONEFREQ_na7 << 27)           /**< Shifted mode na7 for RAC_IFADCTRIM0         */
#define RAC_IFADCTRIM0_IFADCENHALFMODE                                (0x1UL << 30)                                           /**< IFADCENHALFMODE                             */
#define _RAC_IFADCTRIM0_IFADCENHALFMODE_SHIFT                         30                                                      /**< Shift value for RAC_IFADCENHALFMODE         */
#define _RAC_IFADCTRIM0_IFADCENHALFMODE_MASK                          0x40000000UL                                            /**< Bit mask for RAC_IFADCENHALFMODE            */
#define _RAC_IFADCTRIM0_IFADCENHALFMODE_DEFAULT                       0x00000000UL                                            /**< Mode DEFAULT for RAC_IFADCTRIM0             */
#define _RAC_IFADCTRIM0_IFADCENHALFMODE_full_speed_mode               0x00000000UL                                            /**< Mode full_speed_mode for RAC_IFADCTRIM0     */
#define _RAC_IFADCTRIM0_IFADCENHALFMODE_half_speed_mode               0x00000001UL                                            /**< Mode half_speed_mode for RAC_IFADCTRIM0     */
#define RAC_IFADCTRIM0_IFADCENHALFMODE_DEFAULT                        (_RAC_IFADCTRIM0_IFADCENHALFMODE_DEFAULT << 30)         /**< Shifted mode DEFAULT for RAC_IFADCTRIM0     */
#define RAC_IFADCTRIM0_IFADCENHALFMODE_full_speed_mode                (_RAC_IFADCTRIM0_IFADCENHALFMODE_full_speed_mode << 30) /**< Shifted mode full_speed_mode for RAC_IFADCTRIM0*/
#define RAC_IFADCTRIM0_IFADCENHALFMODE_half_speed_mode                (_RAC_IFADCTRIM0_IFADCENHALFMODE_half_speed_mode << 30) /**< Shifted mode half_speed_mode for RAC_IFADCTRIM0*/

/* Bit fields for RAC IFADCTRIM1 */
#define _RAC_IFADCTRIM1_RESETVALUE                                    0x00000123UL                                       /**< Default value for RAC_IFADCTRIM1            */
#define _RAC_IFADCTRIM1_MASK                                          0x000001FFUL                                       /**< Mask for RAC_IFADCTRIM1                     */
#define _RAC_IFADCTRIM1_IFADCVCMLVL_SHIFT                             0                                                  /**< Shift value for RAC_IFADCVCMLVL             */
#define _RAC_IFADCTRIM1_IFADCVCMLVL_MASK                              0x7UL                                              /**< Bit mask for RAC_IFADCVCMLVL                */
#define _RAC_IFADCTRIM1_IFADCVCMLVL_DEFAULT                           0x00000003UL                                       /**< Mode DEFAULT for RAC_IFADCTRIM1             */
#define _RAC_IFADCTRIM1_IFADCVCMLVL_vcm_475mV                         0x00000000UL                                       /**< Mode vcm_475mV for RAC_IFADCTRIM1           */
#define _RAC_IFADCTRIM1_IFADCVCMLVL_vcm_500mV                         0x00000001UL                                       /**< Mode vcm_500mV for RAC_IFADCTRIM1           */
#define _RAC_IFADCTRIM1_IFADCVCMLVL_vcm_525mV                         0x00000002UL                                       /**< Mode vcm_525mV for RAC_IFADCTRIM1           */
#define _RAC_IFADCTRIM1_IFADCVCMLVL_vcm_550mV                         0x00000003UL                                       /**< Mode vcm_550mV for RAC_IFADCTRIM1           */
#define _RAC_IFADCTRIM1_IFADCVCMLVL_vcm_575mV                         0x00000004UL                                       /**< Mode vcm_575mV for RAC_IFADCTRIM1           */
#define _RAC_IFADCTRIM1_IFADCVCMLVL_vcm_600mV                         0x00000005UL                                       /**< Mode vcm_600mV for RAC_IFADCTRIM1           */
#define _RAC_IFADCTRIM1_IFADCVCMLVL_vcm_625mV                         0x00000006UL                                       /**< Mode vcm_625mV for RAC_IFADCTRIM1           */
#define _RAC_IFADCTRIM1_IFADCVCMLVL_cm_650mV                          0x00000007UL                                       /**< Mode cm_650mV for RAC_IFADCTRIM1            */
#define RAC_IFADCTRIM1_IFADCVCMLVL_DEFAULT                            (_RAC_IFADCTRIM1_IFADCVCMLVL_DEFAULT << 0)         /**< Shifted mode DEFAULT for RAC_IFADCTRIM1     */
#define RAC_IFADCTRIM1_IFADCVCMLVL_vcm_475mV                          (_RAC_IFADCTRIM1_IFADCVCMLVL_vcm_475mV << 0)       /**< Shifted mode vcm_475mV for RAC_IFADCTRIM1   */
#define RAC_IFADCTRIM1_IFADCVCMLVL_vcm_500mV                          (_RAC_IFADCTRIM1_IFADCVCMLVL_vcm_500mV << 0)       /**< Shifted mode vcm_500mV for RAC_IFADCTRIM1   */
#define RAC_IFADCTRIM1_IFADCVCMLVL_vcm_525mV                          (_RAC_IFADCTRIM1_IFADCVCMLVL_vcm_525mV << 0)       /**< Shifted mode vcm_525mV for RAC_IFADCTRIM1   */
#define RAC_IFADCTRIM1_IFADCVCMLVL_vcm_550mV                          (_RAC_IFADCTRIM1_IFADCVCMLVL_vcm_550mV << 0)       /**< Shifted mode vcm_550mV for RAC_IFADCTRIM1   */
#define RAC_IFADCTRIM1_IFADCVCMLVL_vcm_575mV                          (_RAC_IFADCTRIM1_IFADCVCMLVL_vcm_575mV << 0)       /**< Shifted mode vcm_575mV for RAC_IFADCTRIM1   */
#define RAC_IFADCTRIM1_IFADCVCMLVL_vcm_600mV                          (_RAC_IFADCTRIM1_IFADCVCMLVL_vcm_600mV << 0)       /**< Shifted mode vcm_600mV for RAC_IFADCTRIM1   */
#define RAC_IFADCTRIM1_IFADCVCMLVL_vcm_625mV                          (_RAC_IFADCTRIM1_IFADCVCMLVL_vcm_625mV << 0)       /**< Shifted mode vcm_625mV for RAC_IFADCTRIM1   */
#define RAC_IFADCTRIM1_IFADCVCMLVL_cm_650mV                           (_RAC_IFADCTRIM1_IFADCVCMLVL_cm_650mV << 0)        /**< Shifted mode cm_650mV for RAC_IFADCTRIM1    */
#define RAC_IFADCTRIM1_IFADCENNEGRES                                  (0x1UL << 3)                                       /**< IFADCENNEGRES                               */
#define _RAC_IFADCTRIM1_IFADCENNEGRES_SHIFT                           3                                                  /**< Shift value for RAC_IFADCENNEGRES           */
#define _RAC_IFADCTRIM1_IFADCENNEGRES_MASK                            0x8UL                                              /**< Bit mask for RAC_IFADCENNEGRES              */
#define _RAC_IFADCTRIM1_IFADCENNEGRES_DEFAULT                         0x00000000UL                                       /**< Mode DEFAULT for RAC_IFADCTRIM1             */
#define _RAC_IFADCTRIM1_IFADCENNEGRES_disable                         0x00000000UL                                       /**< Mode disable for RAC_IFADCTRIM1             */
#define _RAC_IFADCTRIM1_IFADCENNEGRES_enable                          0x00000001UL                                       /**< Mode enable for RAC_IFADCTRIM1              */
#define RAC_IFADCTRIM1_IFADCENNEGRES_DEFAULT                          (_RAC_IFADCTRIM1_IFADCENNEGRES_DEFAULT << 3)       /**< Shifted mode DEFAULT for RAC_IFADCTRIM1     */
#define RAC_IFADCTRIM1_IFADCENNEGRES_disable                          (_RAC_IFADCTRIM1_IFADCENNEGRES_disable << 3)       /**< Shifted mode disable for RAC_IFADCTRIM1     */
#define RAC_IFADCTRIM1_IFADCENNEGRES_enable                           (_RAC_IFADCTRIM1_IFADCENNEGRES_enable << 3)        /**< Shifted mode enable for RAC_IFADCTRIM1      */
#define _RAC_IFADCTRIM1_IFADCNEGRESCURRENT_SHIFT                      4                                                  /**< Shift value for RAC_IFADCNEGRESCURRENT      */
#define _RAC_IFADCTRIM1_IFADCNEGRESCURRENT_MASK                       0x70UL                                             /**< Bit mask for RAC_IFADCNEGRESCURRENT         */
#define _RAC_IFADCTRIM1_IFADCNEGRESCURRENT_DEFAULT                    0x00000002UL                                       /**< Mode DEFAULT for RAC_IFADCTRIM1             */
#define _RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i1p0u                      0x00000000UL                                       /**< Mode i1p0u for RAC_IFADCTRIM1               */
#define _RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i1p5u                      0x00000001UL                                       /**< Mode i1p5u for RAC_IFADCTRIM1               */
#define _RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i2p0u                      0x00000002UL                                       /**< Mode i2p0u for RAC_IFADCTRIM1               */
#define _RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i2p5u                      0x00000003UL                                       /**< Mode i2p5u for RAC_IFADCTRIM1               */
#define _RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i2p0u2                     0x00000004UL                                       /**< Mode i2p0u2 for RAC_IFADCTRIM1              */
#define _RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i2p5u2                     0x00000005UL                                       /**< Mode i2p5u2 for RAC_IFADCTRIM1              */
#define _RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i3p0u                      0x00000006UL                                       /**< Mode i3p0u for RAC_IFADCTRIM1               */
#define _RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i3p5u                      0x00000007UL                                       /**< Mode i3p5u for RAC_IFADCTRIM1               */
#define RAC_IFADCTRIM1_IFADCNEGRESCURRENT_DEFAULT                     (_RAC_IFADCTRIM1_IFADCNEGRESCURRENT_DEFAULT << 4)  /**< Shifted mode DEFAULT for RAC_IFADCTRIM1     */
#define RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i1p0u                       (_RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i1p0u << 4)    /**< Shifted mode i1p0u for RAC_IFADCTRIM1       */
#define RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i1p5u                       (_RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i1p5u << 4)    /**< Shifted mode i1p5u for RAC_IFADCTRIM1       */
#define RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i2p0u                       (_RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i2p0u << 4)    /**< Shifted mode i2p0u for RAC_IFADCTRIM1       */
#define RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i2p5u                       (_RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i2p5u << 4)    /**< Shifted mode i2p5u for RAC_IFADCTRIM1       */
#define RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i2p0u2                      (_RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i2p0u2 << 4)   /**< Shifted mode i2p0u2 for RAC_IFADCTRIM1      */
#define RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i2p5u2                      (_RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i2p5u2 << 4)   /**< Shifted mode i2p5u2 for RAC_IFADCTRIM1      */
#define RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i3p0u                       (_RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i3p0u << 4)    /**< Shifted mode i3p0u for RAC_IFADCTRIM1       */
#define RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i3p5u                       (_RAC_IFADCTRIM1_IFADCNEGRESCURRENT_i3p5u << 4)    /**< Shifted mode i3p5u for RAC_IFADCTRIM1       */
#define _RAC_IFADCTRIM1_IFADCNEGRESVCM_SHIFT                          7                                                  /**< Shift value for RAC_IFADCNEGRESVCM          */
#define _RAC_IFADCTRIM1_IFADCNEGRESVCM_MASK                           0x180UL                                            /**< Bit mask for RAC_IFADCNEGRESVCM             */
#define _RAC_IFADCTRIM1_IFADCNEGRESVCM_DEFAULT                        0x00000002UL                                       /**< Mode DEFAULT for RAC_IFADCTRIM1             */
#define _RAC_IFADCTRIM1_IFADCNEGRESVCM_r210k_x_1uA                    0x00000000UL                                       /**< Mode r210k_x_1uA for RAC_IFADCTRIM1         */
#define _RAC_IFADCTRIM1_IFADCNEGRESVCM_r210k_x_1uA2                   0x00000001UL                                       /**< Mode r210k_x_1uA2 for RAC_IFADCTRIM1        */
#define _RAC_IFADCTRIM1_IFADCNEGRESVCM_r100k_x_2uA                    0x00000002UL                                       /**< Mode r100k_x_2uA for RAC_IFADCTRIM1         */
#define _RAC_IFADCTRIM1_IFADCNEGRESVCM_r50k_x_3uA                     0x00000003UL                                       /**< Mode r50k_x_3uA for RAC_IFADCTRIM1          */
#define RAC_IFADCTRIM1_IFADCNEGRESVCM_DEFAULT                         (_RAC_IFADCTRIM1_IFADCNEGRESVCM_DEFAULT << 7)      /**< Shifted mode DEFAULT for RAC_IFADCTRIM1     */
#define RAC_IFADCTRIM1_IFADCNEGRESVCM_r210k_x_1uA                     (_RAC_IFADCTRIM1_IFADCNEGRESVCM_r210k_x_1uA << 7)  /**< Shifted mode r210k_x_1uA for RAC_IFADCTRIM1 */
#define RAC_IFADCTRIM1_IFADCNEGRESVCM_r210k_x_1uA2                    (_RAC_IFADCTRIM1_IFADCNEGRESVCM_r210k_x_1uA2 << 7) /**< Shifted mode r210k_x_1uA2 for RAC_IFADCTRIM1*/
#define RAC_IFADCTRIM1_IFADCNEGRESVCM_r100k_x_2uA                     (_RAC_IFADCTRIM1_IFADCNEGRESVCM_r100k_x_2uA << 7)  /**< Shifted mode r100k_x_2uA for RAC_IFADCTRIM1 */
#define RAC_IFADCTRIM1_IFADCNEGRESVCM_r50k_x_3uA                      (_RAC_IFADCTRIM1_IFADCNEGRESVCM_r50k_x_3uA << 7)   /**< Shifted mode r50k_x_3uA for RAC_IFADCTRIM1  */

/* Bit fields for RAC IFADCCAL */
#define _RAC_IFADCCAL_RESETVALUE                                      0x00000C00UL                                            /**< Default value for RAC_IFADCCAL              */
#define _RAC_IFADCCAL_MASK                                            0x00FF1F03UL                                            /**< Mask for RAC_IFADCCAL                       */
#define RAC_IFADCCAL_IFADCENRCCAL                                     (0x1UL << 0)                                            /**< IFADCENRCCAL                                */
#define _RAC_IFADCCAL_IFADCENRCCAL_SHIFT                              0                                                       /**< Shift value for RAC_IFADCENRCCAL            */
#define _RAC_IFADCCAL_IFADCENRCCAL_MASK                               0x1UL                                                   /**< Bit mask for RAC_IFADCENRCCAL               */
#define _RAC_IFADCCAL_IFADCENRCCAL_DEFAULT                            0x00000000UL                                            /**< Mode DEFAULT for RAC_IFADCCAL               */
#define _RAC_IFADCCAL_IFADCENRCCAL_rccal_disable                      0x00000000UL                                            /**< Mode rccal_disable for RAC_IFADCCAL         */
#define _RAC_IFADCCAL_IFADCENRCCAL_rccal_enable                       0x00000001UL                                            /**< Mode rccal_enable for RAC_IFADCCAL          */
#define RAC_IFADCCAL_IFADCENRCCAL_DEFAULT                             (_RAC_IFADCCAL_IFADCENRCCAL_DEFAULT << 0)               /**< Shifted mode DEFAULT for RAC_IFADCCAL       */
#define RAC_IFADCCAL_IFADCENRCCAL_rccal_disable                       (_RAC_IFADCCAL_IFADCENRCCAL_rccal_disable << 0)         /**< Shifted mode rccal_disable for RAC_IFADCCAL */
#define RAC_IFADCCAL_IFADCENRCCAL_rccal_enable                        (_RAC_IFADCCAL_IFADCENRCCAL_rccal_enable << 0)          /**< Shifted mode rccal_enable for RAC_IFADCCAL  */
#define RAC_IFADCCAL_IFADCTUNERCCALMODE                               (0x1UL << 1)                                            /**< IFADCTUNERCCALMODE                          */
#define _RAC_IFADCCAL_IFADCTUNERCCALMODE_SHIFT                        1                                                       /**< Shift value for RAC_IFADCTUNERCCALMODE      */
#define _RAC_IFADCCAL_IFADCTUNERCCALMODE_MASK                         0x2UL                                                   /**< Bit mask for RAC_IFADCTUNERCCALMODE         */
#define _RAC_IFADCCAL_IFADCTUNERCCALMODE_DEFAULT                      0x00000000UL                                            /**< Mode DEFAULT for RAC_IFADCCAL               */
#define _RAC_IFADCCAL_IFADCTUNERCCALMODE_SYmode                       0x00000000UL                                            /**< Mode SYmode for RAC_IFADCCAL                */
#define _RAC_IFADCCAL_IFADCTUNERCCALMODE_ADCmode                      0x00000001UL                                            /**< Mode ADCmode for RAC_IFADCCAL               */
#define RAC_IFADCCAL_IFADCTUNERCCALMODE_DEFAULT                       (_RAC_IFADCCAL_IFADCTUNERCCALMODE_DEFAULT << 1)         /**< Shifted mode DEFAULT for RAC_IFADCCAL       */
#define RAC_IFADCCAL_IFADCTUNERCCALMODE_SYmode                        (_RAC_IFADCCAL_IFADCTUNERCCALMODE_SYmode << 1)          /**< Shifted mode SYmode for RAC_IFADCCAL        */
#define RAC_IFADCCAL_IFADCTUNERCCALMODE_ADCmode                       (_RAC_IFADCCAL_IFADCTUNERCCALMODE_ADCmode << 1)         /**< Shifted mode ADCmode for RAC_IFADCCAL       */
#define _RAC_IFADCCAL_IFADCTUNERC_SHIFT                               8                                                       /**< Shift value for RAC_IFADCTUNERC             */
#define _RAC_IFADCCAL_IFADCTUNERC_MASK                                0x1F00UL                                                /**< Bit mask for RAC_IFADCTUNERC                */
#define _RAC_IFADCCAL_IFADCTUNERC_DEFAULT                             0x0000000CUL                                            /**< Mode DEFAULT for RAC_IFADCCAL               */
#define RAC_IFADCCAL_IFADCTUNERC_DEFAULT                              (_RAC_IFADCCAL_IFADCTUNERC_DEFAULT << 8)                /**< Shifted mode DEFAULT for RAC_IFADCCAL       */
#define _RAC_IFADCCAL_IFADCRCCALCOUNTERSTARTVAL_SHIFT                 16                                                      /**< Shift value for RAC_IFADCRCCALCOUNTERSTARTVAL*/
#define _RAC_IFADCCAL_IFADCRCCALCOUNTERSTARTVAL_MASK                  0xFF0000UL                                              /**< Bit mask for RAC_IFADCRCCALCOUNTERSTARTVAL  */
#define _RAC_IFADCCAL_IFADCRCCALCOUNTERSTARTVAL_DEFAULT               0x00000000UL                                            /**< Mode DEFAULT for RAC_IFADCCAL               */
#define RAC_IFADCCAL_IFADCRCCALCOUNTERSTARTVAL_DEFAULT                (_RAC_IFADCCAL_IFADCRCCALCOUNTERSTARTVAL_DEFAULT << 16) /**< Shifted mode DEFAULT for RAC_IFADCCAL       */

/* Bit fields for RAC IFADCSTATUS */
#define _RAC_IFADCSTATUS_RESETVALUE                                   0x00000000UL                                  /**< Default value for RAC_IFADCSTATUS           */
#define _RAC_IFADCSTATUS_MASK                                         0x00000001UL                                  /**< Mask for RAC_IFADCSTATUS                    */
#define RAC_IFADCSTATUS_IFADCRCCALOUT                                 (0x1UL << 0)                                  /**< IFADCRCCALOUT                               */
#define _RAC_IFADCSTATUS_IFADCRCCALOUT_SHIFT                          0                                             /**< Shift value for RAC_IFADCRCCALOUT           */
#define _RAC_IFADCSTATUS_IFADCRCCALOUT_MASK                           0x1UL                                         /**< Bit mask for RAC_IFADCRCCALOUT              */
#define _RAC_IFADCSTATUS_IFADCRCCALOUT_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for RAC_IFADCSTATUS            */
#define _RAC_IFADCSTATUS_IFADCRCCALOUT_lo                             0x00000000UL                                  /**< Mode lo for RAC_IFADCSTATUS                 */
#define _RAC_IFADCSTATUS_IFADCRCCALOUT_hi                             0x00000001UL                                  /**< Mode hi for RAC_IFADCSTATUS                 */
#define RAC_IFADCSTATUS_IFADCRCCALOUT_DEFAULT                         (_RAC_IFADCSTATUS_IFADCRCCALOUT_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_IFADCSTATUS    */
#define RAC_IFADCSTATUS_IFADCRCCALOUT_lo                              (_RAC_IFADCSTATUS_IFADCRCCALOUT_lo << 0)      /**< Shifted mode lo for RAC_IFADCSTATUS         */
#define RAC_IFADCSTATUS_IFADCRCCALOUT_hi                              (_RAC_IFADCSTATUS_IFADCRCCALOUT_hi << 0)      /**< Shifted mode hi for RAC_IFADCSTATUS         */

/* Bit fields for RAC LNAMIXTRIM0 */
#define _RAC_LNAMIXTRIM0_RESETVALUE                                   0x00000110UL                                     /**< Default value for RAC_LNAMIXTRIM0           */
#define _RAC_LNAMIXTRIM0_MASK                                         0x000001FFUL                                     /**< Mask for RAC_LNAMIXTRIM0                    */
#define _RAC_LNAMIXTRIM0_LNAMIXCAPSEL0_SHIFT                          0                                                /**< Shift value for RAC_LNAMIXCAPSEL0           */
#define _RAC_LNAMIXTRIM0_LNAMIXCAPSEL0_MASK                           0x7UL                                            /**< Bit mask for RAC_LNAMIXCAPSEL0              */
#define _RAC_LNAMIXTRIM0_LNAMIXCAPSEL0_DEFAULT                        0x00000000UL                                     /**< Mode DEFAULT for RAC_LNAMIXTRIM0            */
#define RAC_LNAMIXTRIM0_LNAMIXCAPSEL0_DEFAULT                         (_RAC_LNAMIXTRIM0_LNAMIXCAPSEL0_DEFAULT << 0)    /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM0    */
#define _RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0_SHIFT                         3                                                /**< Shift value for RAC_LNAMIXMXRBIAS0          */
#define _RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0_MASK                          0x18UL                                           /**< Bit mask for RAC_LNAMIXMXRBIAS0             */
#define _RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0_DEFAULT                       0x00000002UL                                     /**< Mode DEFAULT for RAC_LNAMIXTRIM0            */
#define _RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0_bias_1V                       0x00000000UL                                     /**< Mode bias_1V for RAC_LNAMIXTRIM0            */
#define _RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0_unused                        0x00000001UL                                     /**< Mode unused for RAC_LNAMIXTRIM0             */
#define _RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0_bias_900m                     0x00000002UL                                     /**< Mode bias_900m for RAC_LNAMIXTRIM0          */
#define _RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0_bias_800m                     0x00000003UL                                     /**< Mode bias_800m for RAC_LNAMIXTRIM0          */
#define RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0_DEFAULT                        (_RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0_DEFAULT << 3)   /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM0    */
#define RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0_bias_1V                        (_RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0_bias_1V << 3)   /**< Shifted mode bias_1V for RAC_LNAMIXTRIM0    */
#define RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0_unused                         (_RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0_unused << 3)    /**< Shifted mode unused for RAC_LNAMIXTRIM0     */
#define RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0_bias_900m                      (_RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0_bias_900m << 3) /**< Shifted mode bias_900m for RAC_LNAMIXTRIM0  */
#define RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0_bias_800m                      (_RAC_LNAMIXTRIM0_LNAMIXMXRBIAS0_bias_800m << 3) /**< Shifted mode bias_800m for RAC_LNAMIXTRIM0  */
#define _RAC_LNAMIXTRIM0_LNAMIXVOUTADJ0_SHIFT                         5                                                /**< Shift value for RAC_LNAMIXVOUTADJ0          */
#define _RAC_LNAMIXTRIM0_LNAMIXVOUTADJ0_MASK                          0x1E0UL                                          /**< Bit mask for RAC_LNAMIXVOUTADJ0             */
#define _RAC_LNAMIXTRIM0_LNAMIXVOUTADJ0_DEFAULT                       0x00000008UL                                     /**< Mode DEFAULT for RAC_LNAMIXTRIM0            */
#define RAC_LNAMIXTRIM0_LNAMIXVOUTADJ0_DEFAULT                        (_RAC_LNAMIXTRIM0_LNAMIXVOUTADJ0_DEFAULT << 5)   /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM0    */

/* Bit fields for RAC LNAMIXTRIM1 */
#define _RAC_LNAMIXTRIM1_RESETVALUE                                   0x00000110UL                                     /**< Default value for RAC_LNAMIXTRIM1           */
#define _RAC_LNAMIXTRIM1_MASK                                         0x000001FFUL                                     /**< Mask for RAC_LNAMIXTRIM1                    */
#define _RAC_LNAMIXTRIM1_LNAMIXCAPSEL1_SHIFT                          0                                                /**< Shift value for RAC_LNAMIXCAPSEL1           */
#define _RAC_LNAMIXTRIM1_LNAMIXCAPSEL1_MASK                           0x7UL                                            /**< Bit mask for RAC_LNAMIXCAPSEL1              */
#define _RAC_LNAMIXTRIM1_LNAMIXCAPSEL1_DEFAULT                        0x00000000UL                                     /**< Mode DEFAULT for RAC_LNAMIXTRIM1            */
#define RAC_LNAMIXTRIM1_LNAMIXCAPSEL1_DEFAULT                         (_RAC_LNAMIXTRIM1_LNAMIXCAPSEL1_DEFAULT << 0)    /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM1    */
#define _RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1_SHIFT                         3                                                /**< Shift value for RAC_LNAMIXMXRBIAS1          */
#define _RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1_MASK                          0x18UL                                           /**< Bit mask for RAC_LNAMIXMXRBIAS1             */
#define _RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1_DEFAULT                       0x00000002UL                                     /**< Mode DEFAULT for RAC_LNAMIXTRIM1            */
#define _RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1_bias_1V                       0x00000000UL                                     /**< Mode bias_1V for RAC_LNAMIXTRIM1            */
#define _RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1_unused                        0x00000001UL                                     /**< Mode unused for RAC_LNAMIXTRIM1             */
#define _RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1_bias_900m                     0x00000002UL                                     /**< Mode bias_900m for RAC_LNAMIXTRIM1          */
#define _RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1_bias_800m                     0x00000003UL                                     /**< Mode bias_800m for RAC_LNAMIXTRIM1          */
#define RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1_DEFAULT                        (_RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1_DEFAULT << 3)   /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM1    */
#define RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1_bias_1V                        (_RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1_bias_1V << 3)   /**< Shifted mode bias_1V for RAC_LNAMIXTRIM1    */
#define RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1_unused                         (_RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1_unused << 3)    /**< Shifted mode unused for RAC_LNAMIXTRIM1     */
#define RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1_bias_900m                      (_RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1_bias_900m << 3) /**< Shifted mode bias_900m for RAC_LNAMIXTRIM1  */
#define RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1_bias_800m                      (_RAC_LNAMIXTRIM1_LNAMIXMXRBIAS1_bias_800m << 3) /**< Shifted mode bias_800m for RAC_LNAMIXTRIM1  */
#define _RAC_LNAMIXTRIM1_LNAMIXVOUTADJ1_SHIFT                         5                                                /**< Shift value for RAC_LNAMIXVOUTADJ1          */
#define _RAC_LNAMIXTRIM1_LNAMIXVOUTADJ1_MASK                          0x1E0UL                                          /**< Bit mask for RAC_LNAMIXVOUTADJ1             */
#define _RAC_LNAMIXTRIM1_LNAMIXVOUTADJ1_DEFAULT                       0x00000008UL                                     /**< Mode DEFAULT for RAC_LNAMIXTRIM1            */
#define RAC_LNAMIXTRIM1_LNAMIXVOUTADJ1_DEFAULT                        (_RAC_LNAMIXTRIM1_LNAMIXVOUTADJ1_DEFAULT << 5)   /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM1    */

/* Bit fields for RAC LNAMIXTRIM2 */
#define _RAC_LNAMIXTRIM2_RESETVALUE                                   0x545033D0UL                                         /**< Default value for RAC_LNAMIXTRIM2           */
#define _RAC_LNAMIXTRIM2_MASK                                         0x7FF8FFF0UL                                         /**< Mask for RAC_LNAMIXTRIM2                    */
#define _RAC_LNAMIXTRIM2_LNAMIXCURCTRL_SHIFT                          4                                                    /**< Shift value for RAC_LNAMIXCURCTRL           */
#define _RAC_LNAMIXTRIM2_LNAMIXCURCTRL_MASK                           0x3F0UL                                              /**< Bit mask for RAC_LNAMIXCURCTRL              */
#define _RAC_LNAMIXTRIM2_LNAMIXCURCTRL_DEFAULT                        0x0000003DUL                                         /**< Mode DEFAULT for RAC_LNAMIXTRIM2            */
#define RAC_LNAMIXTRIM2_LNAMIXCURCTRL_DEFAULT                         (_RAC_LNAMIXTRIM2_LNAMIXCURCTRL_DEFAULT << 4)        /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM2    */
#define _RAC_LNAMIXTRIM2_LNAMIXHIGHCUR_SHIFT                          10                                                   /**< Shift value for RAC_LNAMIXHIGHCUR           */
#define _RAC_LNAMIXTRIM2_LNAMIXHIGHCUR_MASK                           0xC00UL                                              /**< Bit mask for RAC_LNAMIXHIGHCUR              */
#define _RAC_LNAMIXTRIM2_LNAMIXHIGHCUR_DEFAULT                        0x00000000UL                                         /**< Mode DEFAULT for RAC_LNAMIXTRIM2            */
#define _RAC_LNAMIXTRIM2_LNAMIXHIGHCUR_current_470uA                  0x00000000UL                                         /**< Mode current_470uA for RAC_LNAMIXTRIM2      */
#define _RAC_LNAMIXTRIM2_LNAMIXHIGHCUR_current_530uA                  0x00000001UL                                         /**< Mode current_530uA for RAC_LNAMIXTRIM2      */
#define _RAC_LNAMIXTRIM2_LNAMIXHIGHCUR_unused                         0x00000002UL                                         /**< Mode unused for RAC_LNAMIXTRIM2             */
#define _RAC_LNAMIXTRIM2_LNAMIXHIGHCUR_current_590uA                  0x00000003UL                                         /**< Mode current_590uA for RAC_LNAMIXTRIM2      */
#define RAC_LNAMIXTRIM2_LNAMIXHIGHCUR_DEFAULT                         (_RAC_LNAMIXTRIM2_LNAMIXHIGHCUR_DEFAULT << 10)       /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM2    */
#define RAC_LNAMIXTRIM2_LNAMIXHIGHCUR_current_470uA                   (_RAC_LNAMIXTRIM2_LNAMIXHIGHCUR_current_470uA << 10) /**< Shifted mode current_470uA for RAC_LNAMIXTRIM2*/
#define RAC_LNAMIXTRIM2_LNAMIXHIGHCUR_current_530uA                   (_RAC_LNAMIXTRIM2_LNAMIXHIGHCUR_current_530uA << 10) /**< Shifted mode current_530uA for RAC_LNAMIXTRIM2*/
#define RAC_LNAMIXTRIM2_LNAMIXHIGHCUR_unused                          (_RAC_LNAMIXTRIM2_LNAMIXHIGHCUR_unused << 10)        /**< Shifted mode unused for RAC_LNAMIXTRIM2     */
#define RAC_LNAMIXTRIM2_LNAMIXHIGHCUR_current_590uA                   (_RAC_LNAMIXTRIM2_LNAMIXHIGHCUR_current_590uA << 10) /**< Shifted mode current_590uA for RAC_LNAMIXTRIM2*/
#define _RAC_LNAMIXTRIM2_LNAMIXLOWCUR_SHIFT                           12                                                   /**< Shift value for RAC_LNAMIXLOWCUR            */
#define _RAC_LNAMIXTRIM2_LNAMIXLOWCUR_MASK                            0xF000UL                                             /**< Bit mask for RAC_LNAMIXLOWCUR               */
#define _RAC_LNAMIXTRIM2_LNAMIXLOWCUR_DEFAULT                         0x00000003UL                                         /**< Mode DEFAULT for RAC_LNAMIXTRIM2            */
#define RAC_LNAMIXTRIM2_LNAMIXLOWCUR_DEFAULT                          (_RAC_LNAMIXTRIM2_LNAMIXLOWCUR_DEFAULT << 12)        /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM2    */
#define _RAC_LNAMIXTRIM2_LNAMIXNCASADJ0_SHIFT                         19                                                   /**< Shift value for RAC_LNAMIXNCASADJ0          */
#define _RAC_LNAMIXTRIM2_LNAMIXNCASADJ0_MASK                          0x180000UL                                           /**< Bit mask for RAC_LNAMIXNCASADJ0             */
#define _RAC_LNAMIXTRIM2_LNAMIXNCASADJ0_DEFAULT                       0x00000002UL                                         /**< Mode DEFAULT for RAC_LNAMIXTRIM2            */
#define _RAC_LNAMIXTRIM2_LNAMIXNCASADJ0_ncas_1V                       0x00000000UL                                         /**< Mode ncas_1V for RAC_LNAMIXTRIM2            */
#define _RAC_LNAMIXTRIM2_LNAMIXNCASADJ0_unused                        0x00000001UL                                         /**< Mode unused for RAC_LNAMIXTRIM2             */
#define _RAC_LNAMIXTRIM2_LNAMIXNCASADJ0_ncas_950m                     0x00000002UL                                         /**< Mode ncas_950m for RAC_LNAMIXTRIM2          */
#define _RAC_LNAMIXTRIM2_LNAMIXNCASADJ0_ncas_900m                     0x00000003UL                                         /**< Mode ncas_900m for RAC_LNAMIXTRIM2          */
#define RAC_LNAMIXTRIM2_LNAMIXNCASADJ0_DEFAULT                        (_RAC_LNAMIXTRIM2_LNAMIXNCASADJ0_DEFAULT << 19)      /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM2    */
#define RAC_LNAMIXTRIM2_LNAMIXNCASADJ0_ncas_1V                        (_RAC_LNAMIXTRIM2_LNAMIXNCASADJ0_ncas_1V << 19)      /**< Shifted mode ncas_1V for RAC_LNAMIXTRIM2    */
#define RAC_LNAMIXTRIM2_LNAMIXNCASADJ0_unused                         (_RAC_LNAMIXTRIM2_LNAMIXNCASADJ0_unused << 19)       /**< Shifted mode unused for RAC_LNAMIXTRIM2     */
#define RAC_LNAMIXTRIM2_LNAMIXNCASADJ0_ncas_950m                      (_RAC_LNAMIXTRIM2_LNAMIXNCASADJ0_ncas_950m << 19)    /**< Shifted mode ncas_950m for RAC_LNAMIXTRIM2  */
#define RAC_LNAMIXTRIM2_LNAMIXNCASADJ0_ncas_900m                      (_RAC_LNAMIXTRIM2_LNAMIXNCASADJ0_ncas_900m << 19)    /**< Shifted mode ncas_900m for RAC_LNAMIXTRIM2  */
#define _RAC_LNAMIXTRIM2_LNAMIXPCASADJ0_SHIFT                         21                                                   /**< Shift value for RAC_LNAMIXPCASADJ0          */
#define _RAC_LNAMIXTRIM2_LNAMIXPCASADJ0_MASK                          0x600000UL                                           /**< Bit mask for RAC_LNAMIXPCASADJ0             */
#define _RAC_LNAMIXTRIM2_LNAMIXPCASADJ0_DEFAULT                       0x00000002UL                                         /**< Mode DEFAULT for RAC_LNAMIXTRIM2            */
#define _RAC_LNAMIXTRIM2_LNAMIXPCASADJ0_pcas_250m                     0x00000000UL                                         /**< Mode pcas_250m for RAC_LNAMIXTRIM2          */
#define _RAC_LNAMIXTRIM2_LNAMIXPCASADJ0_unused                        0x00000001UL                                         /**< Mode unused for RAC_LNAMIXTRIM2             */
#define _RAC_LNAMIXTRIM2_LNAMIXPCASADJ0_pcas_300m                     0x00000002UL                                         /**< Mode pcas_300m for RAC_LNAMIXTRIM2          */
#define _RAC_LNAMIXTRIM2_LNAMIXPCASADJ0_pcas_350m                     0x00000003UL                                         /**< Mode pcas_350m for RAC_LNAMIXTRIM2          */
#define RAC_LNAMIXTRIM2_LNAMIXPCASADJ0_DEFAULT                        (_RAC_LNAMIXTRIM2_LNAMIXPCASADJ0_DEFAULT << 21)      /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM2    */
#define RAC_LNAMIXTRIM2_LNAMIXPCASADJ0_pcas_250m                      (_RAC_LNAMIXTRIM2_LNAMIXPCASADJ0_pcas_250m << 21)    /**< Shifted mode pcas_250m for RAC_LNAMIXTRIM2  */
#define RAC_LNAMIXTRIM2_LNAMIXPCASADJ0_unused                         (_RAC_LNAMIXTRIM2_LNAMIXPCASADJ0_unused << 21)       /**< Shifted mode unused for RAC_LNAMIXTRIM2     */
#define RAC_LNAMIXTRIM2_LNAMIXPCASADJ0_pcas_300m                      (_RAC_LNAMIXTRIM2_LNAMIXPCASADJ0_pcas_300m << 21)    /**< Shifted mode pcas_300m for RAC_LNAMIXTRIM2  */
#define RAC_LNAMIXTRIM2_LNAMIXPCASADJ0_pcas_350m                      (_RAC_LNAMIXTRIM2_LNAMIXPCASADJ0_pcas_350m << 21)    /**< Shifted mode pcas_350m for RAC_LNAMIXTRIM2  */
#define _RAC_LNAMIXTRIM2_LNAMIXTRIMVREG_SHIFT                         23                                                   /**< Shift value for RAC_LNAMIXTRIMVREG          */
#define _RAC_LNAMIXTRIM2_LNAMIXTRIMVREG_MASK                          0x7800000UL                                          /**< Bit mask for RAC_LNAMIXTRIMVREG             */
#define _RAC_LNAMIXTRIM2_LNAMIXTRIMVREG_DEFAULT                       0x00000008UL                                         /**< Mode DEFAULT for RAC_LNAMIXTRIM2            */
#define RAC_LNAMIXTRIM2_LNAMIXTRIMVREG_DEFAULT                        (_RAC_LNAMIXTRIM2_LNAMIXTRIMVREG_DEFAULT << 23)      /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM2    */
#define _RAC_LNAMIXTRIM2_LNAMIXNCASADJ1_SHIFT                         27                                                   /**< Shift value for RAC_LNAMIXNCASADJ1          */
#define _RAC_LNAMIXTRIM2_LNAMIXNCASADJ1_MASK                          0x18000000UL                                         /**< Bit mask for RAC_LNAMIXNCASADJ1             */
#define _RAC_LNAMIXTRIM2_LNAMIXNCASADJ1_DEFAULT                       0x00000002UL                                         /**< Mode DEFAULT for RAC_LNAMIXTRIM2            */
#define _RAC_LNAMIXTRIM2_LNAMIXNCASADJ1_ncas_1V                       0x00000000UL                                         /**< Mode ncas_1V for RAC_LNAMIXTRIM2            */
#define _RAC_LNAMIXTRIM2_LNAMIXNCASADJ1_unused                        0x00000001UL                                         /**< Mode unused for RAC_LNAMIXTRIM2             */
#define _RAC_LNAMIXTRIM2_LNAMIXNCASADJ1_ncas_950m                     0x00000002UL                                         /**< Mode ncas_950m for RAC_LNAMIXTRIM2          */
#define _RAC_LNAMIXTRIM2_LNAMIXNCASADJ1_ncas_900m                     0x00000003UL                                         /**< Mode ncas_900m for RAC_LNAMIXTRIM2          */
#define RAC_LNAMIXTRIM2_LNAMIXNCASADJ1_DEFAULT                        (_RAC_LNAMIXTRIM2_LNAMIXNCASADJ1_DEFAULT << 27)      /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM2    */
#define RAC_LNAMIXTRIM2_LNAMIXNCASADJ1_ncas_1V                        (_RAC_LNAMIXTRIM2_LNAMIXNCASADJ1_ncas_1V << 27)      /**< Shifted mode ncas_1V for RAC_LNAMIXTRIM2    */
#define RAC_LNAMIXTRIM2_LNAMIXNCASADJ1_unused                         (_RAC_LNAMIXTRIM2_LNAMIXNCASADJ1_unused << 27)       /**< Shifted mode unused for RAC_LNAMIXTRIM2     */
#define RAC_LNAMIXTRIM2_LNAMIXNCASADJ1_ncas_950m                      (_RAC_LNAMIXTRIM2_LNAMIXNCASADJ1_ncas_950m << 27)    /**< Shifted mode ncas_950m for RAC_LNAMIXTRIM2  */
#define RAC_LNAMIXTRIM2_LNAMIXNCASADJ1_ncas_900m                      (_RAC_LNAMIXTRIM2_LNAMIXNCASADJ1_ncas_900m << 27)    /**< Shifted mode ncas_900m for RAC_LNAMIXTRIM2  */
#define _RAC_LNAMIXTRIM2_LNAMIXPCASADJ1_SHIFT                         29                                                   /**< Shift value for RAC_LNAMIXPCASADJ1          */
#define _RAC_LNAMIXTRIM2_LNAMIXPCASADJ1_MASK                          0x60000000UL                                         /**< Bit mask for RAC_LNAMIXPCASADJ1             */
#define _RAC_LNAMIXTRIM2_LNAMIXPCASADJ1_DEFAULT                       0x00000002UL                                         /**< Mode DEFAULT for RAC_LNAMIXTRIM2            */
#define _RAC_LNAMIXTRIM2_LNAMIXPCASADJ1_pcas_250m                     0x00000000UL                                         /**< Mode pcas_250m for RAC_LNAMIXTRIM2          */
#define _RAC_LNAMIXTRIM2_LNAMIXPCASADJ1_unused                        0x00000001UL                                         /**< Mode unused for RAC_LNAMIXTRIM2             */
#define _RAC_LNAMIXTRIM2_LNAMIXPCASADJ1_pcas_300m                     0x00000002UL                                         /**< Mode pcas_300m for RAC_LNAMIXTRIM2          */
#define _RAC_LNAMIXTRIM2_LNAMIXPCASADJ1_pcas_350m                     0x00000003UL                                         /**< Mode pcas_350m for RAC_LNAMIXTRIM2          */
#define RAC_LNAMIXTRIM2_LNAMIXPCASADJ1_DEFAULT                        (_RAC_LNAMIXTRIM2_LNAMIXPCASADJ1_DEFAULT << 29)      /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM2    */
#define RAC_LNAMIXTRIM2_LNAMIXPCASADJ1_pcas_250m                      (_RAC_LNAMIXTRIM2_LNAMIXPCASADJ1_pcas_250m << 29)    /**< Shifted mode pcas_250m for RAC_LNAMIXTRIM2  */
#define RAC_LNAMIXTRIM2_LNAMIXPCASADJ1_unused                         (_RAC_LNAMIXTRIM2_LNAMIXPCASADJ1_unused << 29)       /**< Shifted mode unused for RAC_LNAMIXTRIM2     */
#define RAC_LNAMIXTRIM2_LNAMIXPCASADJ1_pcas_300m                      (_RAC_LNAMIXTRIM2_LNAMIXPCASADJ1_pcas_300m << 29)    /**< Shifted mode pcas_300m for RAC_LNAMIXTRIM2  */
#define RAC_LNAMIXTRIM2_LNAMIXPCASADJ1_pcas_350m                      (_RAC_LNAMIXTRIM2_LNAMIXPCASADJ1_pcas_350m << 29)    /**< Shifted mode pcas_350m for RAC_LNAMIXTRIM2  */

/* Bit fields for RAC LNAMIXTRIM3 */
#define _RAC_LNAMIXTRIM3_RESETVALUE                                   0x00000208UL                                    /**< Default value for RAC_LNAMIXTRIM3           */
#define _RAC_LNAMIXTRIM3_MASK                                         0x00000FFFUL                                    /**< Mask for RAC_LNAMIXTRIM3                    */
#define _RAC_LNAMIXTRIM3_LNAMIXIBIASADJ0_SHIFT                        0                                               /**< Shift value for RAC_LNAMIXIBIASADJ0         */
#define _RAC_LNAMIXTRIM3_LNAMIXIBIASADJ0_MASK                         0x3FUL                                          /**< Bit mask for RAC_LNAMIXIBIASADJ0            */
#define _RAC_LNAMIXTRIM3_LNAMIXIBIASADJ0_DEFAULT                      0x00000008UL                                    /**< Mode DEFAULT for RAC_LNAMIXTRIM3            */
#define RAC_LNAMIXTRIM3_LNAMIXIBIASADJ0_DEFAULT                       (_RAC_LNAMIXTRIM3_LNAMIXIBIASADJ0_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM3    */
#define _RAC_LNAMIXTRIM3_LNAMIXIBIASADJ1_SHIFT                        6                                               /**< Shift value for RAC_LNAMIXIBIASADJ1         */
#define _RAC_LNAMIXTRIM3_LNAMIXIBIASADJ1_MASK                         0xFC0UL                                         /**< Bit mask for RAC_LNAMIXIBIASADJ1            */
#define _RAC_LNAMIXTRIM3_LNAMIXIBIASADJ1_DEFAULT                      0x00000008UL                                    /**< Mode DEFAULT for RAC_LNAMIXTRIM3            */
#define RAC_LNAMIXTRIM3_LNAMIXIBIASADJ1_DEFAULT                       (_RAC_LNAMIXTRIM3_LNAMIXIBIASADJ1_DEFAULT << 6) /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM3    */

/* Bit fields for RAC LNAMIXTRIM4 */
#define _RAC_LNAMIXTRIM4_RESETVALUE                                   0x88082002UL                                            /**< Default value for RAC_LNAMIXTRIM4           */
#define _RAC_LNAMIXTRIM4_MASK                                         0xFF0FFF03UL                                            /**< Mask for RAC_LNAMIXTRIM4                    */
#define _RAC_LNAMIXTRIM4_LNAMIXRFPKDBWSEL_SHIFT                       0                                                       /**< Shift value for RAC_LNAMIXRFPKDBWSEL        */
#define _RAC_LNAMIXTRIM4_LNAMIXRFPKDBWSEL_MASK                        0x3UL                                                   /**< Bit mask for RAC_LNAMIXRFPKDBWSEL           */
#define _RAC_LNAMIXTRIM4_LNAMIXRFPKDBWSEL_DEFAULT                     0x00000002UL                                            /**< Mode DEFAULT for RAC_LNAMIXTRIM4            */
#define RAC_LNAMIXTRIM4_LNAMIXRFPKDBWSEL_DEFAULT                      (_RAC_LNAMIXTRIM4_LNAMIXRFPKDBWSEL_DEFAULT << 0)        /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM4    */
#define _RAC_LNAMIXTRIM4_LNAMIXRFPKDCALCMLO_SHIFT                     8                                                       /**< Shift value for RAC_LNAMIXRFPKDCALCMLO      */
#define _RAC_LNAMIXTRIM4_LNAMIXRFPKDCALCMLO_MASK                      0x3F00UL                                                /**< Bit mask for RAC_LNAMIXRFPKDCALCMLO         */
#define _RAC_LNAMIXTRIM4_LNAMIXRFPKDCALCMLO_DEFAULT                   0x00000020UL                                            /**< Mode DEFAULT for RAC_LNAMIXTRIM4            */
#define RAC_LNAMIXTRIM4_LNAMIXRFPKDCALCMLO_DEFAULT                    (_RAC_LNAMIXTRIM4_LNAMIXRFPKDCALCMLO_DEFAULT << 8)      /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM4    */
#define _RAC_LNAMIXTRIM4_LNAMIXRFPKDCALCMHI_SHIFT                     14                                                      /**< Shift value for RAC_LNAMIXRFPKDCALCMHI      */
#define _RAC_LNAMIXTRIM4_LNAMIXRFPKDCALCMHI_MASK                      0xFC000UL                                               /**< Bit mask for RAC_LNAMIXRFPKDCALCMHI         */
#define _RAC_LNAMIXTRIM4_LNAMIXRFPKDCALCMHI_DEFAULT                   0x00000020UL                                            /**< Mode DEFAULT for RAC_LNAMIXTRIM4            */
#define RAC_LNAMIXTRIM4_LNAMIXRFPKDCALCMHI_DEFAULT                    (_RAC_LNAMIXTRIM4_LNAMIXRFPKDCALCMHI_DEFAULT << 14)     /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM4    */
#define _RAC_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELLO_SHIFT                 24                                                      /**< Shift value for RAC_LNAMIXRFPKDTHRESHSELLO  */
#define _RAC_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELLO_MASK                  0xF000000UL                                             /**< Bit mask for RAC_LNAMIXRFPKDTHRESHSELLO     */
#define _RAC_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELLO_DEFAULT               0x00000008UL                                            /**< Mode DEFAULT for RAC_LNAMIXTRIM4            */
#define RAC_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELLO_DEFAULT                (_RAC_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELLO_DEFAULT << 24) /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM4    */
#define _RAC_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELHI_SHIFT                 28                                                      /**< Shift value for RAC_LNAMIXRFPKDTHRESHSELHI  */
#define _RAC_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELHI_MASK                  0xF0000000UL                                            /**< Bit mask for RAC_LNAMIXRFPKDTHRESHSELHI     */
#define _RAC_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELHI_DEFAULT               0x00000008UL                                            /**< Mode DEFAULT for RAC_LNAMIXTRIM4            */
#define RAC_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELHI_DEFAULT                (_RAC_LNAMIXTRIM4_LNAMIXRFPKDTHRESHSELHI_DEFAULT << 28) /**< Shifted mode DEFAULT for RAC_LNAMIXTRIM4    */

/* Bit fields for RAC LNAMIXCAL */
#define _RAC_LNAMIXCAL_RESETVALUE                                     0x000007E0UL                                      /**< Default value for RAC_LNAMIXCAL             */
#define _RAC_LNAMIXCAL_MASK                                           0x000007FDUL                                      /**< Mask for RAC_LNAMIXCAL                      */
#define RAC_LNAMIXCAL_LNAMIXCALEN                                     (0x1UL << 0)                                      /**< LNAMIXCALPMOSEN                             */
#define _RAC_LNAMIXCAL_LNAMIXCALEN_SHIFT                              0                                                 /**< Shift value for RAC_LNAMIXCALEN             */
#define _RAC_LNAMIXCAL_LNAMIXCALEN_MASK                               0x1UL                                             /**< Bit mask for RAC_LNAMIXCALEN                */
#define _RAC_LNAMIXCAL_LNAMIXCALEN_DEFAULT                            0x00000000UL                                      /**< Mode DEFAULT for RAC_LNAMIXCAL              */
#define _RAC_LNAMIXCAL_LNAMIXCALEN_cal_disable                        0x00000000UL                                      /**< Mode cal_disable for RAC_LNAMIXCAL          */
#define _RAC_LNAMIXCAL_LNAMIXCALEN_cal_enable                         0x00000001UL                                      /**< Mode cal_enable for RAC_LNAMIXCAL           */
#define RAC_LNAMIXCAL_LNAMIXCALEN_DEFAULT                             (_RAC_LNAMIXCAL_LNAMIXCALEN_DEFAULT << 0)         /**< Shifted mode DEFAULT for RAC_LNAMIXCAL      */
#define RAC_LNAMIXCAL_LNAMIXCALEN_cal_disable                         (_RAC_LNAMIXCAL_LNAMIXCALEN_cal_disable << 0)     /**< Shifted mode cal_disable for RAC_LNAMIXCAL  */
#define RAC_LNAMIXCAL_LNAMIXCALEN_cal_enable                          (_RAC_LNAMIXCAL_LNAMIXCALEN_cal_enable << 0)      /**< Shifted mode cal_enable for RAC_LNAMIXCAL   */
#define RAC_LNAMIXCAL_LNAMIXCALVMODE                                  (0x1UL << 2)                                      /**< LNAMIXCALVMODE                              */
#define _RAC_LNAMIXCAL_LNAMIXCALVMODE_SHIFT                           2                                                 /**< Shift value for RAC_LNAMIXCALVMODE          */
#define _RAC_LNAMIXCAL_LNAMIXCALVMODE_MASK                            0x4UL                                             /**< Bit mask for RAC_LNAMIXCALVMODE             */
#define _RAC_LNAMIXCAL_LNAMIXCALVMODE_DEFAULT                         0x00000000UL                                      /**< Mode DEFAULT for RAC_LNAMIXCAL              */
#define _RAC_LNAMIXCAL_LNAMIXCALVMODE_current_mode                    0x00000000UL                                      /**< Mode current_mode for RAC_LNAMIXCAL         */
#define _RAC_LNAMIXCAL_LNAMIXCALVMODE_voltage_mode                    0x00000001UL                                      /**< Mode voltage_mode for RAC_LNAMIXCAL         */
#define RAC_LNAMIXCAL_LNAMIXCALVMODE_DEFAULT                          (_RAC_LNAMIXCAL_LNAMIXCALVMODE_DEFAULT << 2)      /**< Shifted mode DEFAULT for RAC_LNAMIXCAL      */
#define RAC_LNAMIXCAL_LNAMIXCALVMODE_current_mode                     (_RAC_LNAMIXCAL_LNAMIXCALVMODE_current_mode << 2) /**< Shifted mode current_mode for RAC_LNAMIXCAL */
#define RAC_LNAMIXCAL_LNAMIXCALVMODE_voltage_mode                     (_RAC_LNAMIXCAL_LNAMIXCALVMODE_voltage_mode << 2) /**< Shifted mode voltage_mode for RAC_LNAMIXCAL */
#define RAC_LNAMIXCAL_LNAMIXENIRCAL0                                  (0x1UL << 3)                                      /**< LNAMIXENIRCAL0                              */
#define _RAC_LNAMIXCAL_LNAMIXENIRCAL0_SHIFT                           3                                                 /**< Shift value for RAC_LNAMIXENIRCAL0          */
#define _RAC_LNAMIXCAL_LNAMIXENIRCAL0_MASK                            0x8UL                                             /**< Bit mask for RAC_LNAMIXENIRCAL0             */
#define _RAC_LNAMIXCAL_LNAMIXENIRCAL0_DEFAULT                         0x00000000UL                                      /**< Mode DEFAULT for RAC_LNAMIXCAL              */
#define _RAC_LNAMIXCAL_LNAMIXENIRCAL0_disable                         0x00000000UL                                      /**< Mode disable for RAC_LNAMIXCAL              */
#define _RAC_LNAMIXCAL_LNAMIXENIRCAL0_enable                          0x00000001UL                                      /**< Mode enable for RAC_LNAMIXCAL               */
#define RAC_LNAMIXCAL_LNAMIXENIRCAL0_DEFAULT                          (_RAC_LNAMIXCAL_LNAMIXENIRCAL0_DEFAULT << 3)      /**< Shifted mode DEFAULT for RAC_LNAMIXCAL      */
#define RAC_LNAMIXCAL_LNAMIXENIRCAL0_disable                          (_RAC_LNAMIXCAL_LNAMIXENIRCAL0_disable << 3)      /**< Shifted mode disable for RAC_LNAMIXCAL      */
#define RAC_LNAMIXCAL_LNAMIXENIRCAL0_enable                           (_RAC_LNAMIXCAL_LNAMIXENIRCAL0_enable << 3)       /**< Shifted mode enable for RAC_LNAMIXCAL       */
#define RAC_LNAMIXCAL_LNAMIXENIRCAL1                                  (0x1UL << 4)                                      /**< LNAMIXENIRCAL1                              */
#define _RAC_LNAMIXCAL_LNAMIXENIRCAL1_SHIFT                           4                                                 /**< Shift value for RAC_LNAMIXENIRCAL1          */
#define _RAC_LNAMIXCAL_LNAMIXENIRCAL1_MASK                            0x10UL                                            /**< Bit mask for RAC_LNAMIXENIRCAL1             */
#define _RAC_LNAMIXCAL_LNAMIXENIRCAL1_DEFAULT                         0x00000000UL                                      /**< Mode DEFAULT for RAC_LNAMIXCAL              */
#define _RAC_LNAMIXCAL_LNAMIXENIRCAL1_disable                         0x00000000UL                                      /**< Mode disable for RAC_LNAMIXCAL              */
#define _RAC_LNAMIXCAL_LNAMIXENIRCAL1_enable                          0x00000001UL                                      /**< Mode enable for RAC_LNAMIXCAL               */
#define RAC_LNAMIXCAL_LNAMIXENIRCAL1_DEFAULT                          (_RAC_LNAMIXCAL_LNAMIXENIRCAL1_DEFAULT << 4)      /**< Shifted mode DEFAULT for RAC_LNAMIXCAL      */
#define RAC_LNAMIXCAL_LNAMIXENIRCAL1_disable                          (_RAC_LNAMIXCAL_LNAMIXENIRCAL1_disable << 4)      /**< Shifted mode disable for RAC_LNAMIXCAL      */
#define RAC_LNAMIXCAL_LNAMIXENIRCAL1_enable                           (_RAC_LNAMIXCAL_LNAMIXENIRCAL1_enable << 4)       /**< Shifted mode enable for RAC_LNAMIXCAL       */
#define _RAC_LNAMIXCAL_LNAMIXIRCALAMP0_SHIFT                          5                                                 /**< Shift value for RAC_LNAMIXIRCALAMP0         */
#define _RAC_LNAMIXCAL_LNAMIXIRCALAMP0_MASK                           0xE0UL                                            /**< Bit mask for RAC_LNAMIXIRCALAMP0            */
#define _RAC_LNAMIXCAL_LNAMIXIRCALAMP0_DEFAULT                        0x00000007UL                                      /**< Mode DEFAULT for RAC_LNAMIXCAL              */
#define RAC_LNAMIXCAL_LNAMIXIRCALAMP0_DEFAULT                         (_RAC_LNAMIXCAL_LNAMIXIRCALAMP0_DEFAULT << 5)     /**< Shifted mode DEFAULT for RAC_LNAMIXCAL      */
#define _RAC_LNAMIXCAL_LNAMIXIRCALAMP1_SHIFT                          8                                                 /**< Shift value for RAC_LNAMIXIRCALAMP1         */
#define _RAC_LNAMIXCAL_LNAMIXIRCALAMP1_MASK                           0x700UL                                           /**< Bit mask for RAC_LNAMIXIRCALAMP1            */
#define _RAC_LNAMIXCAL_LNAMIXIRCALAMP1_DEFAULT                        0x00000007UL                                      /**< Mode DEFAULT for RAC_LNAMIXCAL              */
#define RAC_LNAMIXCAL_LNAMIXIRCALAMP1_DEFAULT                         (_RAC_LNAMIXCAL_LNAMIXIRCALAMP1_DEFAULT << 8)     /**< Shifted mode DEFAULT for RAC_LNAMIXCAL      */

/* Bit fields for RAC LNAMIXEN */
#define _RAC_LNAMIXEN_RESETVALUE                                      0x00000000UL                             /**< Default value for RAC_LNAMIXEN              */
#define _RAC_LNAMIXEN_MASK                                            0x00000008UL                             /**< Mask for RAC_LNAMIXEN                       */
#define RAC_LNAMIXEN_LNAMIXENLDO                                      (0x1UL << 3)                             /**< LNAMIXENLDO                                 */
#define _RAC_LNAMIXEN_LNAMIXENLDO_SHIFT                               3                                        /**< Shift value for RAC_LNAMIXENLDO             */
#define _RAC_LNAMIXEN_LNAMIXENLDO_MASK                                0x8UL                                    /**< Bit mask for RAC_LNAMIXENLDO                */
#define _RAC_LNAMIXEN_LNAMIXENLDO_DEFAULT                             0x00000000UL                             /**< Mode DEFAULT for RAC_LNAMIXEN               */
#define _RAC_LNAMIXEN_LNAMIXENLDO_disable                             0x00000000UL                             /**< Mode disable for RAC_LNAMIXEN               */
#define _RAC_LNAMIXEN_LNAMIXENLDO_enable                              0x00000001UL                             /**< Mode enable for RAC_LNAMIXEN                */
#define RAC_LNAMIXEN_LNAMIXENLDO_DEFAULT                              (_RAC_LNAMIXEN_LNAMIXENLDO_DEFAULT << 3) /**< Shifted mode DEFAULT for RAC_LNAMIXEN       */
#define RAC_LNAMIXEN_LNAMIXENLDO_disable                              (_RAC_LNAMIXEN_LNAMIXENLDO_disable << 3) /**< Shifted mode disable for RAC_LNAMIXEN       */
#define RAC_LNAMIXEN_LNAMIXENLDO_enable                               (_RAC_LNAMIXEN_LNAMIXENLDO_enable << 3)  /**< Shifted mode enable for RAC_LNAMIXEN        */

/* Bit fields for RAC PRECTRL */
#define _RAC_PRECTRL_RESETVALUE                                       0x00000026UL                               /**< Default value for RAC_PRECTRL               */
#define _RAC_PRECTRL_MASK                                             0x0000003FUL                               /**< Mask for RAC_PRECTRL                        */
#define RAC_PRECTRL_PREBYPFORCE                                       (0x1UL << 0)                               /**< PREBYPFORCE                                 */
#define _RAC_PRECTRL_PREBYPFORCE_SHIFT                                0                                          /**< Shift value for RAC_PREBYPFORCE             */
#define _RAC_PRECTRL_PREBYPFORCE_MASK                                 0x1UL                                      /**< Bit mask for RAC_PREBYPFORCE                */
#define _RAC_PRECTRL_PREBYPFORCE_DEFAULT                              0x00000000UL                               /**< Mode DEFAULT for RAC_PRECTRL                */
#define _RAC_PRECTRL_PREBYPFORCE_not_forced                           0x00000000UL                               /**< Mode not_forced for RAC_PRECTRL             */
#define _RAC_PRECTRL_PREBYPFORCE_forced                               0x00000001UL                               /**< Mode forced for RAC_PRECTRL                 */
#define RAC_PRECTRL_PREBYPFORCE_DEFAULT                               (_RAC_PRECTRL_PREBYPFORCE_DEFAULT << 0)    /**< Shifted mode DEFAULT for RAC_PRECTRL        */
#define RAC_PRECTRL_PREBYPFORCE_not_forced                            (_RAC_PRECTRL_PREBYPFORCE_not_forced << 0) /**< Shifted mode not_forced for RAC_PRECTRL     */
#define RAC_PRECTRL_PREBYPFORCE_forced                                (_RAC_PRECTRL_PREBYPFORCE_forced << 0)     /**< Shifted mode forced for RAC_PRECTRL         */
#define _RAC_PRECTRL_PREREGTRIM_SHIFT                                 1                                          /**< Shift value for RAC_PREREGTRIM              */
#define _RAC_PRECTRL_PREREGTRIM_MASK                                  0xEUL                                      /**< Bit mask for RAC_PREREGTRIM                 */
#define _RAC_PRECTRL_PREREGTRIM_DEFAULT                               0x00000003UL                               /**< Mode DEFAULT for RAC_PRECTRL                */
#define _RAC_PRECTRL_PREREGTRIM_v1p61                                 0x00000000UL                               /**< Mode v1p61 for RAC_PRECTRL                  */
#define _RAC_PRECTRL_PREREGTRIM_v1p68                                 0x00000001UL                               /**< Mode v1p68 for RAC_PRECTRL                  */
#define _RAC_PRECTRL_PREREGTRIM_v1p74                                 0x00000002UL                               /**< Mode v1p74 for RAC_PRECTRL                  */
#define _RAC_PRECTRL_PREREGTRIM_v1p80                                 0x00000003UL                               /**< Mode v1p80 for RAC_PRECTRL                  */
#define _RAC_PRECTRL_PREREGTRIM_v1p86                                 0x00000004UL                               /**< Mode v1p86 for RAC_PRECTRL                  */
#define _RAC_PRECTRL_PREREGTRIM_v1p91                                 0x00000005UL                               /**< Mode v1p91 for RAC_PRECTRL                  */
#define _RAC_PRECTRL_PREREGTRIM_v1p96                                 0x00000006UL                               /**< Mode v1p96 for RAC_PRECTRL                  */
#define _RAC_PRECTRL_PREREGTRIM_v2p00                                 0x00000007UL                               /**< Mode v2p00 for RAC_PRECTRL                  */
#define RAC_PRECTRL_PREREGTRIM_DEFAULT                                (_RAC_PRECTRL_PREREGTRIM_DEFAULT << 1)     /**< Shifted mode DEFAULT for RAC_PRECTRL        */
#define RAC_PRECTRL_PREREGTRIM_v1p61                                  (_RAC_PRECTRL_PREREGTRIM_v1p61 << 1)       /**< Shifted mode v1p61 for RAC_PRECTRL          */
#define RAC_PRECTRL_PREREGTRIM_v1p68                                  (_RAC_PRECTRL_PREREGTRIM_v1p68 << 1)       /**< Shifted mode v1p68 for RAC_PRECTRL          */
#define RAC_PRECTRL_PREREGTRIM_v1p74                                  (_RAC_PRECTRL_PREREGTRIM_v1p74 << 1)       /**< Shifted mode v1p74 for RAC_PRECTRL          */
#define RAC_PRECTRL_PREREGTRIM_v1p80                                  (_RAC_PRECTRL_PREREGTRIM_v1p80 << 1)       /**< Shifted mode v1p80 for RAC_PRECTRL          */
#define RAC_PRECTRL_PREREGTRIM_v1p86                                  (_RAC_PRECTRL_PREREGTRIM_v1p86 << 1)       /**< Shifted mode v1p86 for RAC_PRECTRL          */
#define RAC_PRECTRL_PREREGTRIM_v1p91                                  (_RAC_PRECTRL_PREREGTRIM_v1p91 << 1)       /**< Shifted mode v1p91 for RAC_PRECTRL          */
#define RAC_PRECTRL_PREREGTRIM_v1p96                                  (_RAC_PRECTRL_PREREGTRIM_v1p96 << 1)       /**< Shifted mode v1p96 for RAC_PRECTRL          */
#define RAC_PRECTRL_PREREGTRIM_v2p00                                  (_RAC_PRECTRL_PREREGTRIM_v2p00 << 1)       /**< Shifted mode v2p00 for RAC_PRECTRL          */
#define _RAC_PRECTRL_PREVREFTRIM_SHIFT                                4                                          /**< Shift value for RAC_PREVREFTRIM             */
#define _RAC_PRECTRL_PREVREFTRIM_MASK                                 0x30UL                                     /**< Bit mask for RAC_PREVREFTRIM                */
#define _RAC_PRECTRL_PREVREFTRIM_DEFAULT                              0x00000002UL                               /**< Mode DEFAULT for RAC_PRECTRL                */
#define _RAC_PRECTRL_PREVREFTRIM_v0p675                               0x00000000UL                               /**< Mode v0p675 for RAC_PRECTRL                 */
#define _RAC_PRECTRL_PREVREFTRIM_v0p688                               0x00000001UL                               /**< Mode v0p688 for RAC_PRECTRL                 */
#define _RAC_PRECTRL_PREVREFTRIM_v0p700                               0x00000002UL                               /**< Mode v0p700 for RAC_PRECTRL                 */
#define _RAC_PRECTRL_PREVREFTRIM_v0p713                               0x00000003UL                               /**< Mode v0p713 for RAC_PRECTRL                 */
#define RAC_PRECTRL_PREVREFTRIM_DEFAULT                               (_RAC_PRECTRL_PREVREFTRIM_DEFAULT << 4)    /**< Shifted mode DEFAULT for RAC_PRECTRL        */
#define RAC_PRECTRL_PREVREFTRIM_v0p675                                (_RAC_PRECTRL_PREVREFTRIM_v0p675 << 4)     /**< Shifted mode v0p675 for RAC_PRECTRL         */
#define RAC_PRECTRL_PREVREFTRIM_v0p688                                (_RAC_PRECTRL_PREVREFTRIM_v0p688 << 4)     /**< Shifted mode v0p688 for RAC_PRECTRL         */
#define RAC_PRECTRL_PREVREFTRIM_v0p700                                (_RAC_PRECTRL_PREVREFTRIM_v0p700 << 4)     /**< Shifted mode v0p700 for RAC_PRECTRL         */
#define RAC_PRECTRL_PREVREFTRIM_v0p713                                (_RAC_PRECTRL_PREVREFTRIM_v0p713 << 4)     /**< Shifted mode v0p713 for RAC_PRECTRL         */

/* Bit fields for RAC PATRIM0 */
#define _RAC_PATRIM0_RESETVALUE                                       0x00000077UL                                        /**< Default value for RAC_PATRIM0               */
#define _RAC_PATRIM0_MASK                                             0x0101FFFFUL                                        /**< Mask for RAC_PATRIM0                        */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_SHIFT                            0                                                   /**< Shift value for RAC_TX0DBMTRIMBIASN         */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_MASK                             0xFUL                                               /**< Bit mask for RAC_TX0DBMTRIMBIASN            */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_DEFAULT                          0x00000007UL                                        /**< Mode DEFAULT for RAC_PATRIM0                */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_v_367m                           0x00000000UL                                        /**< Mode v_367m for RAC_PATRIM0                 */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_v_380m                           0x00000001UL                                        /**< Mode v_380m for RAC_PATRIM0                 */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_v_393m                           0x00000002UL                                        /**< Mode v_393m for RAC_PATRIM0                 */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_v_406m                           0x00000003UL                                        /**< Mode v_406m for RAC_PATRIM0                 */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_v_419m                           0x00000004UL                                        /**< Mode v_419m for RAC_PATRIM0                 */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_v_432m                           0x00000005UL                                        /**< Mode v_432m for RAC_PATRIM0                 */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_v_445m                           0x00000006UL                                        /**< Mode v_445m for RAC_PATRIM0                 */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_v_default_458m                   0x00000007UL                                        /**< Mode v_default_458m for RAC_PATRIM0         */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_v_483m                           0x00000008UL                                        /**< Mode v_483m for RAC_PATRIM0                 */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_v_496m                           0x00000009UL                                        /**< Mode v_496m for RAC_PATRIM0                 */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_v_509m                           0x0000000AUL                                        /**< Mode v_509m for RAC_PATRIM0                 */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_v_522m                           0x0000000BUL                                        /**< Mode v_522m for RAC_PATRIM0                 */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_v_535m                           0x0000000CUL                                        /**< Mode v_535m for RAC_PATRIM0                 */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_v_548m                           0x0000000DUL                                        /**< Mode v_548m for RAC_PATRIM0                 */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_v_561m                           0x0000000EUL                                        /**< Mode v_561m for RAC_PATRIM0                 */
#define _RAC_PATRIM0_TX0DBMTRIMBIASN_v_574m                           0x0000000FUL                                        /**< Mode v_574m for RAC_PATRIM0                 */
#define RAC_PATRIM0_TX0DBMTRIMBIASN_DEFAULT                           (_RAC_PATRIM0_TX0DBMTRIMBIASN_DEFAULT << 0)         /**< Shifted mode DEFAULT for RAC_PATRIM0        */
#define RAC_PATRIM0_TX0DBMTRIMBIASN_v_367m                            (_RAC_PATRIM0_TX0DBMTRIMBIASN_v_367m << 0)          /**< Shifted mode v_367m for RAC_PATRIM0         */
#define RAC_PATRIM0_TX0DBMTRIMBIASN_v_380m                            (_RAC_PATRIM0_TX0DBMTRIMBIASN_v_380m << 0)          /**< Shifted mode v_380m for RAC_PATRIM0         */
#define RAC_PATRIM0_TX0DBMTRIMBIASN_v_393m                            (_RAC_PATRIM0_TX0DBMTRIMBIASN_v_393m << 0)          /**< Shifted mode v_393m for RAC_PATRIM0         */
#define RAC_PATRIM0_TX0DBMTRIMBIASN_v_406m                            (_RAC_PATRIM0_TX0DBMTRIMBIASN_v_406m << 0)          /**< Shifted mode v_406m for RAC_PATRIM0         */
#define RAC_PATRIM0_TX0DBMTRIMBIASN_v_419m                            (_RAC_PATRIM0_TX0DBMTRIMBIASN_v_419m << 0)          /**< Shifted mode v_419m for RAC_PATRIM0         */
#define RAC_PATRIM0_TX0DBMTRIMBIASN_v_432m                            (_RAC_PATRIM0_TX0DBMTRIMBIASN_v_432m << 0)          /**< Shifted mode v_432m for RAC_PATRIM0         */
#define RAC_PATRIM0_TX0DBMTRIMBIASN_v_445m                            (_RAC_PATRIM0_TX0DBMTRIMBIASN_v_445m << 0)          /**< Shifted mode v_445m for RAC_PATRIM0         */
#define RAC_PATRIM0_TX0DBMTRIMBIASN_v_default_458m                    (_RAC_PATRIM0_TX0DBMTRIMBIASN_v_default_458m << 0)  /**< Shifted mode v_default_458m for RAC_PATRIM0 */
#define RAC_PATRIM0_TX0DBMTRIMBIASN_v_483m                            (_RAC_PATRIM0_TX0DBMTRIMBIASN_v_483m << 0)          /**< Shifted mode v_483m for RAC_PATRIM0         */
#define RAC_PATRIM0_TX0DBMTRIMBIASN_v_496m                            (_RAC_PATRIM0_TX0DBMTRIMBIASN_v_496m << 0)          /**< Shifted mode v_496m for RAC_PATRIM0         */
#define RAC_PATRIM0_TX0DBMTRIMBIASN_v_509m                            (_RAC_PATRIM0_TX0DBMTRIMBIASN_v_509m << 0)          /**< Shifted mode v_509m for RAC_PATRIM0         */
#define RAC_PATRIM0_TX0DBMTRIMBIASN_v_522m                            (_RAC_PATRIM0_TX0DBMTRIMBIASN_v_522m << 0)          /**< Shifted mode v_522m for RAC_PATRIM0         */
#define RAC_PATRIM0_TX0DBMTRIMBIASN_v_535m                            (_RAC_PATRIM0_TX0DBMTRIMBIASN_v_535m << 0)          /**< Shifted mode v_535m for RAC_PATRIM0         */
#define RAC_PATRIM0_TX0DBMTRIMBIASN_v_548m                            (_RAC_PATRIM0_TX0DBMTRIMBIASN_v_548m << 0)          /**< Shifted mode v_548m for RAC_PATRIM0         */
#define RAC_PATRIM0_TX0DBMTRIMBIASN_v_561m                            (_RAC_PATRIM0_TX0DBMTRIMBIASN_v_561m << 0)          /**< Shifted mode v_561m for RAC_PATRIM0         */
#define RAC_PATRIM0_TX0DBMTRIMBIASN_v_574m                            (_RAC_PATRIM0_TX0DBMTRIMBIASN_v_574m << 0)          /**< Shifted mode v_574m for RAC_PATRIM0         */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_SHIFT                            4                                                   /**< Shift value for RAC_TX0DBMTRIMBIASP         */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_MASK                             0xF0UL                                              /**< Bit mask for RAC_TX0DBMTRIMBIASP            */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_DEFAULT                          0x00000007UL                                        /**< Mode DEFAULT for RAC_PATRIM0                */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p186                          0x00000000UL                                        /**< Mode v_1p186 for RAC_PATRIM0                */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p173                          0x00000001UL                                        /**< Mode v_1p173 for RAC_PATRIM0                */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p16                           0x00000002UL                                        /**< Mode v_1p16 for RAC_PATRIM0                 */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p147                          0x00000003UL                                        /**< Mode v_1p147 for RAC_PATRIM0                */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p134                          0x00000004UL                                        /**< Mode v_1p134 for RAC_PATRIM0                */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p121                          0x00000005UL                                        /**< Mode v_1p121 for RAC_PATRIM0                */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p108                          0x00000006UL                                        /**< Mode v_1p108 for RAC_PATRIM0                */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_v_default_1p095                  0x00000007UL                                        /**< Mode v_default_1p095 for RAC_PATRIM0        */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p083                          0x00000008UL                                        /**< Mode v_1p083 for RAC_PATRIM0                */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p07                           0x00000009UL                                        /**< Mode v_1p07 for RAC_PATRIM0                 */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p057                          0x0000000AUL                                        /**< Mode v_1p057 for RAC_PATRIM0                */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p044                          0x0000000BUL                                        /**< Mode v_1p044 for RAC_PATRIM0                */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p031                          0x0000000CUL                                        /**< Mode v_1p031 for RAC_PATRIM0                */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p019                          0x0000000DUL                                        /**< Mode v_1p019 for RAC_PATRIM0                */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p006                          0x0000000EUL                                        /**< Mode v_1p006 for RAC_PATRIM0                */
#define _RAC_PATRIM0_TX0DBMTRIMBIASP_v_0p993                          0x0000000FUL                                        /**< Mode v_0p993 for RAC_PATRIM0                */
#define RAC_PATRIM0_TX0DBMTRIMBIASP_DEFAULT                           (_RAC_PATRIM0_TX0DBMTRIMBIASP_DEFAULT << 4)         /**< Shifted mode DEFAULT for RAC_PATRIM0        */
#define RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p186                           (_RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p186 << 4)         /**< Shifted mode v_1p186 for RAC_PATRIM0        */
#define RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p173                           (_RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p173 << 4)         /**< Shifted mode v_1p173 for RAC_PATRIM0        */
#define RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p16                            (_RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p16 << 4)          /**< Shifted mode v_1p16 for RAC_PATRIM0         */
#define RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p147                           (_RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p147 << 4)         /**< Shifted mode v_1p147 for RAC_PATRIM0        */
#define RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p134                           (_RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p134 << 4)         /**< Shifted mode v_1p134 for RAC_PATRIM0        */
#define RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p121                           (_RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p121 << 4)         /**< Shifted mode v_1p121 for RAC_PATRIM0        */
#define RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p108                           (_RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p108 << 4)         /**< Shifted mode v_1p108 for RAC_PATRIM0        */
#define RAC_PATRIM0_TX0DBMTRIMBIASP_v_default_1p095                   (_RAC_PATRIM0_TX0DBMTRIMBIASP_v_default_1p095 << 4) /**< Shifted mode v_default_1p095 for RAC_PATRIM0*/
#define RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p083                           (_RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p083 << 4)         /**< Shifted mode v_1p083 for RAC_PATRIM0        */
#define RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p07                            (_RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p07 << 4)          /**< Shifted mode v_1p07 for RAC_PATRIM0         */
#define RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p057                           (_RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p057 << 4)         /**< Shifted mode v_1p057 for RAC_PATRIM0        */
#define RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p044                           (_RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p044 << 4)         /**< Shifted mode v_1p044 for RAC_PATRIM0        */
#define RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p031                           (_RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p031 << 4)         /**< Shifted mode v_1p031 for RAC_PATRIM0        */
#define RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p019                           (_RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p019 << 4)         /**< Shifted mode v_1p019 for RAC_PATRIM0        */
#define RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p006                           (_RAC_PATRIM0_TX0DBMTRIMBIASP_v_1p006 << 4)         /**< Shifted mode v_1p006 for RAC_PATRIM0        */
#define RAC_PATRIM0_TX0DBMTRIMBIASP_v_0p993                           (_RAC_PATRIM0_TX0DBMTRIMBIASP_v_0p993 << 4)         /**< Shifted mode v_0p993 for RAC_PATRIM0        */
#define _RAC_PATRIM0_TXPAAMPCTRL_SHIFT                                8                                                   /**< Shift value for RAC_TXPAAMPCTRL             */
#define _RAC_PATRIM0_TXPAAMPCTRL_MASK                                 0xFF00UL                                            /**< Bit mask for RAC_TXPAAMPCTRL                */
#define _RAC_PATRIM0_TXPAAMPCTRL_DEFAULT                              0x00000000UL                                        /**< Mode DEFAULT for RAC_PATRIM0                */
#define RAC_PATRIM0_TXPAAMPCTRL_DEFAULT                               (_RAC_PATRIM0_TXPAAMPCTRL_DEFAULT << 8)             /**< Shifted mode DEFAULT for RAC_PATRIM0        */
#define RAC_PATRIM0_TXPABYPASSREG                                     (0x1UL << 16)                                       /**< TXPABYPASSREG                               */
#define _RAC_PATRIM0_TXPABYPASSREG_SHIFT                              16                                                  /**< Shift value for RAC_TXPABYPASSREG           */
#define _RAC_PATRIM0_TXPABYPASSREG_MASK                               0x10000UL                                           /**< Bit mask for RAC_TXPABYPASSREG              */
#define _RAC_PATRIM0_TXPABYPASSREG_DEFAULT                            0x00000000UL                                        /**< Mode DEFAULT for RAC_PATRIM0                */
#define _RAC_PATRIM0_TXPABYPASSREG_not_bypass                         0x00000000UL                                        /**< Mode not_bypass for RAC_PATRIM0             */
#define _RAC_PATRIM0_TXPABYPASSREG_bypass                             0x00000001UL                                        /**< Mode bypass for RAC_PATRIM0                 */
#define RAC_PATRIM0_TXPABYPASSREG_DEFAULT                             (_RAC_PATRIM0_TXPABYPASSREG_DEFAULT << 16)          /**< Shifted mode DEFAULT for RAC_PATRIM0        */
#define RAC_PATRIM0_TXPABYPASSREG_not_bypass                          (_RAC_PATRIM0_TXPABYPASSREG_not_bypass << 16)       /**< Shifted mode not_bypass for RAC_PATRIM0     */
#define RAC_PATRIM0_TXPABYPASSREG_bypass                              (_RAC_PATRIM0_TXPABYPASSREG_bypass << 16)           /**< Shifted mode bypass for RAC_PATRIM0         */
#define RAC_PATRIM0_ENAMPCTRLREG                                      (0x1UL << 24)                                       /**< ENAMPCTRLREG                                */
#define _RAC_PATRIM0_ENAMPCTRLREG_SHIFT                               24                                                  /**< Shift value for RAC_ENAMPCTRLREG            */
#define _RAC_PATRIM0_ENAMPCTRLREG_MASK                                0x1000000UL                                         /**< Bit mask for RAC_ENAMPCTRLREG               */
#define _RAC_PATRIM0_ENAMPCTRLREG_DEFAULT                             0x00000000UL                                        /**< Mode DEFAULT for RAC_PATRIM0                */
#define RAC_PATRIM0_ENAMPCTRLREG_DEFAULT                              (_RAC_PATRIM0_ENAMPCTRLREG_DEFAULT << 24)           /**< Shifted mode DEFAULT for RAC_PATRIM0        */

/* Bit fields for RAC PATRIM1 */
#define _RAC_PATRIM1_RESETVALUE                                       0x03034373UL                                                     /**< Default value for RAC_PATRIM1               */
#define _RAC_PATRIM1_MASK                                             0x0777F3F7UL                                                     /**< Mask for RAC_PATRIM1                        */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBCORE_SHIFT                  0                                                                /**< Shift value for RAC_TX0DBMTRIMPREDRVREGIBCORE*/
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBCORE_MASK                   0x3UL                                                            /**< Bit mask for RAC_TX0DBMTRIMPREDRVREGIBCORE  */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBCORE_DEFAULT                0x00000003UL                                                     /**< Mode DEFAULT for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBCORE_i_4u                   0x00000000UL                                                     /**< Mode i_4u for RAC_PATRIM1                   */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBCORE_i_5u                   0x00000001UL                                                     /**< Mode i_5u for RAC_PATRIM1                   */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBCORE_i_6u                   0x00000002UL                                                     /**< Mode i_6u for RAC_PATRIM1                   */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBCORE_i_default_7u           0x00000003UL                                                     /**< Mode i_default_7u for RAC_PATRIM1           */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBCORE_DEFAULT                 (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBCORE_DEFAULT << 0)            /**< Shifted mode DEFAULT for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBCORE_i_4u                    (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBCORE_i_4u << 0)               /**< Shifted mode i_4u for RAC_PATRIM1           */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBCORE_i_5u                    (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBCORE_i_5u << 0)               /**< Shifted mode i_5u for RAC_PATRIM1           */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBCORE_i_6u                    (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBCORE_i_6u << 0)               /**< Shifted mode i_6u for RAC_PATRIM1           */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBCORE_i_default_7u            (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBCORE_i_default_7u << 0)       /**< Shifted mode i_default_7u for RAC_PATRIM1   */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGPSR                            (0x1UL << 2)                                                     /**< TX0DBMTRIMPREDRVREGPSR                      */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGPSR_SHIFT                     2                                                                /**< Shift value for RAC_TX0DBMTRIMPREDRVREGPSR  */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGPSR_MASK                      0x4UL                                                            /**< Bit mask for RAC_TX0DBMTRIMPREDRVREGPSR     */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGPSR_DEFAULT                   0x00000000UL                                                     /**< Mode DEFAULT for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGPSR_disable                   0x00000000UL                                                     /**< Mode disable for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGPSR_enable                    0x00000001UL                                                     /**< Mode enable for RAC_PATRIM1                 */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGPSR_DEFAULT                    (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGPSR_DEFAULT << 2)               /**< Shifted mode DEFAULT for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGPSR_disable                    (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGPSR_disable << 2)               /**< Shifted mode disable for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGPSR_enable                     (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGPSR_enable << 2)                /**< Shifted mode enable for RAC_PATRIM1         */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_SHIFT                  4                                                                /**< Shift value for RAC_TX0DBMTRIMPREDRVREGIBNDIO*/
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_MASK                   0xF0UL                                                           /**< Bit mask for RAC_TX0DBMTRIMPREDRVREGIBNDIO  */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_DEFAULT                0x00000007UL                                                     /**< Mode DEFAULT for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p127             0x00000000UL                                                     /**< Mode vreg_1p127 for RAC_PATRIM1             */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p171             0x00000001UL                                                     /**< Mode vreg_1p171 for RAC_PATRIM1             */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p209             0x00000002UL                                                     /**< Mode vreg_1p209 for RAC_PATRIM1             */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p244             0x00000003UL                                                     /**< Mode vreg_1p244 for RAC_PATRIM1             */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p275             0x00000004UL                                                     /**< Mode vreg_1p275 for RAC_PATRIM1             */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p305             0x00000005UL                                                     /**< Mode vreg_1p305 for RAC_PATRIM1             */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p335             0x00000006UL                                                     /**< Mode vreg_1p335 for RAC_PATRIM1             */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_default_1p362     0x00000007UL                                                     /**< Mode vreg_default_1p362 for RAC_PATRIM1     */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p388             0x00000008UL                                                     /**< Mode vreg_1p388 for RAC_PATRIM1             */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p414             0x00000009UL                                                     /**< Mode vreg_1p414 for RAC_PATRIM1             */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p439             0x0000000AUL                                                     /**< Mode vreg_1p439 for RAC_PATRIM1             */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p463             0x0000000BUL                                                     /**< Mode vreg_1p463 for RAC_PATRIM1             */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p486             0x0000000CUL                                                     /**< Mode vreg_1p486 for RAC_PATRIM1             */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p509             0x0000000DUL                                                     /**< Mode vreg_1p509 for RAC_PATRIM1             */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p532             0x0000000EUL                                                     /**< Mode vreg_1p532 for RAC_PATRIM1             */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p555             0x0000000FUL                                                     /**< Mode vreg_1p555 for RAC_PATRIM1             */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_DEFAULT                 (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_DEFAULT << 4)            /**< Shifted mode DEFAULT for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p127              (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p127 << 4)         /**< Shifted mode vreg_1p127 for RAC_PATRIM1     */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p171              (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p171 << 4)         /**< Shifted mode vreg_1p171 for RAC_PATRIM1     */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p209              (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p209 << 4)         /**< Shifted mode vreg_1p209 for RAC_PATRIM1     */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p244              (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p244 << 4)         /**< Shifted mode vreg_1p244 for RAC_PATRIM1     */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p275              (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p275 << 4)         /**< Shifted mode vreg_1p275 for RAC_PATRIM1     */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p305              (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p305 << 4)         /**< Shifted mode vreg_1p305 for RAC_PATRIM1     */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p335              (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p335 << 4)         /**< Shifted mode vreg_1p335 for RAC_PATRIM1     */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_default_1p362      (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_default_1p362 << 4) /**< Shifted mode vreg_default_1p362 for RAC_PATRIM1*/
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p388              (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p388 << 4)         /**< Shifted mode vreg_1p388 for RAC_PATRIM1     */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p414              (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p414 << 4)         /**< Shifted mode vreg_1p414 for RAC_PATRIM1     */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p439              (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p439 << 4)         /**< Shifted mode vreg_1p439 for RAC_PATRIM1     */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p463              (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p463 << 4)         /**< Shifted mode vreg_1p463 for RAC_PATRIM1     */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p486              (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p486 << 4)         /**< Shifted mode vreg_1p486 for RAC_PATRIM1     */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p509              (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p509 << 4)         /**< Shifted mode vreg_1p509 for RAC_PATRIM1     */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p532              (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p532 << 4)         /**< Shifted mode vreg_1p532 for RAC_PATRIM1     */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p555              (_RAC_PATRIM1_TX0DBMTRIMPREDRVREGIBNDIO_vreg_1p555 << 4)         /**< Shifted mode vreg_1p555 for RAC_PATRIM1     */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVSLOPE_SHIFT                      8                                                                /**< Shift value for RAC_TX0DBMTRIMPREDRVSLOPE   */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVSLOPE_MASK                       0x300UL                                                          /**< Bit mask for RAC_TX0DBMTRIMPREDRVSLOPE      */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVSLOPE_DEFAULT                    0x00000003UL                                                     /**< Mode DEFAULT for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVSLOPE_slope_0                    0x00000000UL                                                     /**< Mode slope_0 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVSLOPE_slope_1                    0x00000001UL                                                     /**< Mode slope_1 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVSLOPE_slope_2                    0x00000002UL                                                     /**< Mode slope_2 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMPREDRVSLOPE_slope_default_max          0x00000003UL                                                     /**< Mode slope_default_max for RAC_PATRIM1      */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVSLOPE_DEFAULT                     (_RAC_PATRIM1_TX0DBMTRIMPREDRVSLOPE_DEFAULT << 8)                /**< Shifted mode DEFAULT for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVSLOPE_slope_0                     (_RAC_PATRIM1_TX0DBMTRIMPREDRVSLOPE_slope_0 << 8)                /**< Shifted mode slope_0 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVSLOPE_slope_1                     (_RAC_PATRIM1_TX0DBMTRIMPREDRVSLOPE_slope_1 << 8)                /**< Shifted mode slope_1 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVSLOPE_slope_2                     (_RAC_PATRIM1_TX0DBMTRIMPREDRVSLOPE_slope_2 << 8)                /**< Shifted mode slope_2 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMPREDRVSLOPE_slope_default_max           (_RAC_PATRIM1_TX0DBMTRIMPREDRVSLOPE_slope_default_max << 8)      /**< Shifted mode slope_default_max for RAC_PATRIM1*/
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_SHIFT                            12                                                               /**< Shift value for RAC_TX0DBMTRIMREGFB         */
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_MASK                             0xF000UL                                                         /**< Bit mask for RAC_TX0DBMTRIMREGFB            */
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_DEFAULT                          0x00000004UL                                                     /**< Mode DEFAULT for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p976                          0x00000000UL                                                     /**< Mode v_1p976 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p878                          0x00000001UL                                                     /**< Mode v_1p878 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p788                          0x00000002UL                                                     /**< Mode v_1p788 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p707                          0x00000003UL                                                     /**< Mode v_1p707 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_v_default_1p633                  0x00000004UL                                                     /**< Mode v_default_1p633 for RAC_PATRIM1        */
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p565                          0x00000005UL                                                     /**< Mode v_1p565 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p503                          0x00000006UL                                                     /**< Mode v_1p503 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p445                          0x00000007UL                                                     /**< Mode v_1p445 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p392                          0x00000008UL                                                     /**< Mode v_1p392 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p342                          0x00000009UL                                                     /**< Mode v_1p342 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p296                          0x0000000AUL                                                     /**< Mode v_1p296 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p253                          0x0000000BUL                                                     /**< Mode v_1p253 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p213                          0x0000000CUL                                                     /**< Mode v_1p213 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p175                          0x0000000DUL                                                     /**< Mode v_1p175 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p14                           0x0000000EUL                                                     /**< Mode v_1p14 for RAC_PATRIM1                 */
#define _RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p106                          0x0000000FUL                                                     /**< Mode v_1p106 for RAC_PATRIM1                */
#define RAC_PATRIM1_TX0DBMTRIMREGFB_DEFAULT                           (_RAC_PATRIM1_TX0DBMTRIMREGFB_DEFAULT << 12)                     /**< Shifted mode DEFAULT for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p976                           (_RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p976 << 12)                     /**< Shifted mode v_1p976 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p878                           (_RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p878 << 12)                     /**< Shifted mode v_1p878 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p788                           (_RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p788 << 12)                     /**< Shifted mode v_1p788 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p707                           (_RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p707 << 12)                     /**< Shifted mode v_1p707 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGFB_v_default_1p633                   (_RAC_PATRIM1_TX0DBMTRIMREGFB_v_default_1p633 << 12)             /**< Shifted mode v_default_1p633 for RAC_PATRIM1*/
#define RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p565                           (_RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p565 << 12)                     /**< Shifted mode v_1p565 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p503                           (_RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p503 << 12)                     /**< Shifted mode v_1p503 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p445                           (_RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p445 << 12)                     /**< Shifted mode v_1p445 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p392                           (_RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p392 << 12)                     /**< Shifted mode v_1p392 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p342                           (_RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p342 << 12)                     /**< Shifted mode v_1p342 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p296                           (_RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p296 << 12)                     /**< Shifted mode v_1p296 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p253                           (_RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p253 << 12)                     /**< Shifted mode v_1p253 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p213                           (_RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p213 << 12)                     /**< Shifted mode v_1p213 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p175                           (_RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p175 << 12)                     /**< Shifted mode v_1p175 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p14                            (_RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p14 << 12)                      /**< Shifted mode v_1p14 for RAC_PATRIM1         */
#define RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p106                           (_RAC_PATRIM1_TX0DBMTRIMREGFB_v_1p106 << 12)                     /**< Shifted mode v_1p106 for RAC_PATRIM1        */
#define _RAC_PATRIM1_TX0DBMTRIMREGVREF_SHIFT                          16                                                               /**< Shift value for RAC_TX0DBMTRIMREGVREF       */
#define _RAC_PATRIM1_TX0DBMTRIMREGVREF_MASK                           0x70000UL                                                        /**< Bit mask for RAC_TX0DBMTRIMREGVREF          */
#define _RAC_PATRIM1_TX0DBMTRIMREGVREF_DEFAULT                        0x00000003UL                                                     /**< Mode DEFAULT for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p572                        0x00000000UL                                                     /**< Mode v_1p572 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p593                        0x00000001UL                                                     /**< Mode v_1p593 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p613                        0x00000002UL                                                     /**< Mode v_1p613 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGVREF_v_default_1p634                0x00000003UL                                                     /**< Mode v_default_1p634 for RAC_PATRIM1        */
#define _RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p654                        0x00000004UL                                                     /**< Mode v_1p654 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p674                        0x00000005UL                                                     /**< Mode v_1p674 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p694                        0x00000006UL                                                     /**< Mode v_1p694 for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p714                        0x00000007UL                                                     /**< Mode v_1p714 for RAC_PATRIM1                */
#define RAC_PATRIM1_TX0DBMTRIMREGVREF_DEFAULT                         (_RAC_PATRIM1_TX0DBMTRIMREGVREF_DEFAULT << 16)                   /**< Shifted mode DEFAULT for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p572                         (_RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p572 << 16)                   /**< Shifted mode v_1p572 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p593                         (_RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p593 << 16)                   /**< Shifted mode v_1p593 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p613                         (_RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p613 << 16)                   /**< Shifted mode v_1p613 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGVREF_v_default_1p634                 (_RAC_PATRIM1_TX0DBMTRIMREGVREF_v_default_1p634 << 16)           /**< Shifted mode v_default_1p634 for RAC_PATRIM1*/
#define RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p654                         (_RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p654 << 16)                   /**< Shifted mode v_1p654 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p674                         (_RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p674 << 16)                   /**< Shifted mode v_1p674 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p694                         (_RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p694 << 16)                   /**< Shifted mode v_1p694 for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p714                         (_RAC_PATRIM1_TX0DBMTRIMREGVREF_v_1p714 << 16)                   /**< Shifted mode v_1p714 for RAC_PATRIM1        */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_SHIFT                       20                                                               /**< Shift value for RAC_TX0DBMTRIMTAPCAP100F    */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_MASK                        0x700000UL                                                       /**< Bit mask for RAC_TX0DBMTRIMTAPCAP100F       */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_DEFAULT                     0x00000000UL                                                     /**< Mode DEFAULT for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_0f                0x00000000UL                                                     /**< Mode Ctap_plus_0f for RAC_PATRIM1           */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_100f              0x00000001UL                                                     /**< Mode Ctap_plus_100f for RAC_PATRIM1         */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_200f              0x00000002UL                                                     /**< Mode Ctap_plus_200f for RAC_PATRIM1         */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_300f              0x00000003UL                                                     /**< Mode Ctap_plus_300f for RAC_PATRIM1         */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_400f              0x00000004UL                                                     /**< Mode Ctap_plus_400f for RAC_PATRIM1         */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_500f              0x00000005UL                                                     /**< Mode Ctap_plus_500f for RAC_PATRIM1         */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_600f              0x00000006UL                                                     /**< Mode Ctap_plus_600f for RAC_PATRIM1         */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_700f              0x00000007UL                                                     /**< Mode Ctap_plus_700f for RAC_PATRIM1         */
#define RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_DEFAULT                      (_RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_DEFAULT << 20)                /**< Shifted mode DEFAULT for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_0f                 (_RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_0f << 20)           /**< Shifted mode Ctap_plus_0f for RAC_PATRIM1   */
#define RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_100f               (_RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_100f << 20)         /**< Shifted mode Ctap_plus_100f for RAC_PATRIM1 */
#define RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_200f               (_RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_200f << 20)         /**< Shifted mode Ctap_plus_200f for RAC_PATRIM1 */
#define RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_300f               (_RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_300f << 20)         /**< Shifted mode Ctap_plus_300f for RAC_PATRIM1 */
#define RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_400f               (_RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_400f << 20)         /**< Shifted mode Ctap_plus_400f for RAC_PATRIM1 */
#define RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_500f               (_RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_500f << 20)         /**< Shifted mode Ctap_plus_500f for RAC_PATRIM1 */
#define RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_600f               (_RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_600f << 20)         /**< Shifted mode Ctap_plus_600f for RAC_PATRIM1 */
#define RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_700f               (_RAC_PATRIM1_TX0DBMTRIMTAPCAP100F_Ctap_plus_700f << 20)         /**< Shifted mode Ctap_plus_700f for RAC_PATRIM1 */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_SHIFT                       24                                                               /**< Shift value for RAC_TX0DBMTRIMTAPCAP200F    */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_MASK                        0x7000000UL                                                      /**< Bit mask for RAC_TX0DBMTRIMTAPCAP200F       */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_DEFAULT                     0x00000003UL                                                     /**< Mode DEFAULT for RAC_PATRIM1                */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_0f                0x00000000UL                                                     /**< Mode Ctap_plus_0f for RAC_PATRIM1           */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_200f              0x00000001UL                                                     /**< Mode Ctap_plus_200f for RAC_PATRIM1         */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_400f              0x00000002UL                                                     /**< Mode Ctap_plus_400f for RAC_PATRIM1         */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_600f              0x00000003UL                                                     /**< Mode Ctap_plus_600f for RAC_PATRIM1         */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_800f              0x00000004UL                                                     /**< Mode Ctap_plus_800f for RAC_PATRIM1         */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_1p                0x00000005UL                                                     /**< Mode Ctap_plus_1p for RAC_PATRIM1           */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_1p2p              0x00000006UL                                                     /**< Mode Ctap_plus_1p2p for RAC_PATRIM1         */
#define _RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_1p4p              0x00000007UL                                                     /**< Mode Ctap_plus_1p4p for RAC_PATRIM1         */
#define RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_DEFAULT                      (_RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_DEFAULT << 24)                /**< Shifted mode DEFAULT for RAC_PATRIM1        */
#define RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_0f                 (_RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_0f << 24)           /**< Shifted mode Ctap_plus_0f for RAC_PATRIM1   */
#define RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_200f               (_RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_200f << 24)         /**< Shifted mode Ctap_plus_200f for RAC_PATRIM1 */
#define RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_400f               (_RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_400f << 24)         /**< Shifted mode Ctap_plus_400f for RAC_PATRIM1 */
#define RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_600f               (_RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_600f << 24)         /**< Shifted mode Ctap_plus_600f for RAC_PATRIM1 */
#define RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_800f               (_RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_800f << 24)         /**< Shifted mode Ctap_plus_800f for RAC_PATRIM1 */
#define RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_1p                 (_RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_1p << 24)           /**< Shifted mode Ctap_plus_1p for RAC_PATRIM1   */
#define RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_1p2p               (_RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_1p2p << 24)         /**< Shifted mode Ctap_plus_1p2p for RAC_PATRIM1 */
#define RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_1p4p               (_RAC_PATRIM1_TX0DBMTRIMTAPCAP200F_Ctap_plus_1p4p << 24)         /**< Shifted mode Ctap_plus_1p4p for RAC_PATRIM1 */

/* Bit fields for RAC PATRIM2 */
#define _RAC_PATRIM2_RESETVALUE                                       0x00000000UL                                      /**< Default value for RAC_PATRIM2               */
#define _RAC_PATRIM2_MASK                                             0x00007777UL                                      /**< Mask for RAC_PATRIM2                        */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYN_SHIFT                          0                                                 /**< Shift value for RAC_TX0DBMTRIMDUTYCYN       */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYN_MASK                           0x7UL                                             /**< Bit mask for RAC_TX0DBMTRIMDUTYCYN          */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYN_DEFAULT                        0x00000000UL                                      /**< Mode DEFAULT for RAC_PATRIM2                */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_0pct                        0x00000000UL                                      /**< Mode up_0pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_1pct                        0x00000001UL                                      /**< Mode up_1pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_2pct                        0x00000002UL                                      /**< Mode up_2pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_3pct                        0x00000003UL                                      /**< Mode up_3pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_4pct                        0x00000004UL                                      /**< Mode up_4pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_5pct                        0x00000005UL                                      /**< Mode up_5pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_6pct                        0x00000006UL                                      /**< Mode up_6pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYN_na                             0x00000007UL                                      /**< Mode na for RAC_PATRIM2                     */
#define RAC_PATRIM2_TX0DBMTRIMDUTYCYN_DEFAULT                         (_RAC_PATRIM2_TX0DBMTRIMDUTYCYN_DEFAULT << 0)     /**< Shifted mode DEFAULT for RAC_PATRIM2        */
#define RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_0pct                         (_RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_0pct << 0)     /**< Shifted mode up_0pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_1pct                         (_RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_1pct << 0)     /**< Shifted mode up_1pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_2pct                         (_RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_2pct << 0)     /**< Shifted mode up_2pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_3pct                         (_RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_3pct << 0)     /**< Shifted mode up_3pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_4pct                         (_RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_4pct << 0)     /**< Shifted mode up_4pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_5pct                         (_RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_5pct << 0)     /**< Shifted mode up_5pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_6pct                         (_RAC_PATRIM2_TX0DBMTRIMDUTYCYN_up_6pct << 0)     /**< Shifted mode up_6pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TX0DBMTRIMDUTYCYN_na                              (_RAC_PATRIM2_TX0DBMTRIMDUTYCYN_na << 0)          /**< Shifted mode na for RAC_PATRIM2             */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYP_SHIFT                          4                                                 /**< Shift value for RAC_TX0DBMTRIMDUTYCYP       */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYP_MASK                           0x70UL                                            /**< Bit mask for RAC_TX0DBMTRIMDUTYCYP          */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYP_DEFAULT                        0x00000000UL                                      /**< Mode DEFAULT for RAC_PATRIM2                */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_0pct                        0x00000000UL                                      /**< Mode dn_0pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_1pct                        0x00000001UL                                      /**< Mode dn_1pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_2pct                        0x00000002UL                                      /**< Mode dn_2pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_3pct                        0x00000003UL                                      /**< Mode dn_3pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_4pct                        0x00000004UL                                      /**< Mode dn_4pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_5pct                        0x00000005UL                                      /**< Mode dn_5pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_6pct                        0x00000006UL                                      /**< Mode dn_6pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TX0DBMTRIMDUTYCYP_na                             0x00000007UL                                      /**< Mode na for RAC_PATRIM2                     */
#define RAC_PATRIM2_TX0DBMTRIMDUTYCYP_DEFAULT                         (_RAC_PATRIM2_TX0DBMTRIMDUTYCYP_DEFAULT << 4)     /**< Shifted mode DEFAULT for RAC_PATRIM2        */
#define RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_0pct                         (_RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_0pct << 4)     /**< Shifted mode dn_0pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_1pct                         (_RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_1pct << 4)     /**< Shifted mode dn_1pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_2pct                         (_RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_2pct << 4)     /**< Shifted mode dn_2pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_3pct                         (_RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_3pct << 4)     /**< Shifted mode dn_3pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_4pct                         (_RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_4pct << 4)     /**< Shifted mode dn_4pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_5pct                         (_RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_5pct << 4)     /**< Shifted mode dn_5pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_6pct                         (_RAC_PATRIM2_TX0DBMTRIMDUTYCYP_dn_6pct << 4)     /**< Shifted mode dn_6pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TX0DBMTRIMDUTYCYP_na                              (_RAC_PATRIM2_TX0DBMTRIMDUTYCYP_na << 4)          /**< Shifted mode na for RAC_PATRIM2             */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_SHIFT                       8                                                 /**< Shift value for RAC_TXPATRIM10DBMDUTYCYN    */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_MASK                        0x700UL                                           /**< Bit mask for RAC_TXPATRIM10DBMDUTYCYN       */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_DEFAULT                     0x00000000UL                                      /**< Mode DEFAULT for RAC_PATRIM2                */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_0pct                     0x00000000UL                                      /**< Mode up_0pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_1pct                     0x00000001UL                                      /**< Mode up_1pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_2pct                     0x00000002UL                                      /**< Mode up_2pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_3pct                     0x00000003UL                                      /**< Mode up_3pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_4pct                     0x00000004UL                                      /**< Mode up_4pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_5pct                     0x00000005UL                                      /**< Mode up_5pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_6pct                     0x00000006UL                                      /**< Mode up_6pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_na                          0x00000007UL                                      /**< Mode na for RAC_PATRIM2                     */
#define RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_DEFAULT                      (_RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_DEFAULT << 8)  /**< Shifted mode DEFAULT for RAC_PATRIM2        */
#define RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_0pct                      (_RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_0pct << 8)  /**< Shifted mode up_0pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_1pct                      (_RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_1pct << 8)  /**< Shifted mode up_1pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_2pct                      (_RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_2pct << 8)  /**< Shifted mode up_2pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_3pct                      (_RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_3pct << 8)  /**< Shifted mode up_3pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_4pct                      (_RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_4pct << 8)  /**< Shifted mode up_4pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_5pct                      (_RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_5pct << 8)  /**< Shifted mode up_5pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_6pct                      (_RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_up_6pct << 8)  /**< Shifted mode up_6pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_na                           (_RAC_PATRIM2_TXPATRIM10DBMDUTYCYN_na << 8)       /**< Shifted mode na for RAC_PATRIM2             */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_SHIFT                       12                                                /**< Shift value for RAC_TXPATRIM10DBMDUTYCYP    */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_MASK                        0x7000UL                                          /**< Bit mask for RAC_TXPATRIM10DBMDUTYCYP       */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_DEFAULT                     0x00000000UL                                      /**< Mode DEFAULT for RAC_PATRIM2                */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_0pct                     0x00000000UL                                      /**< Mode dn_0pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_1pct                     0x00000001UL                                      /**< Mode dn_1pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_2pct                     0x00000002UL                                      /**< Mode dn_2pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_3pct                     0x00000003UL                                      /**< Mode dn_3pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_4pct                     0x00000004UL                                      /**< Mode dn_4pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_5pct                     0x00000005UL                                      /**< Mode dn_5pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_6pct                     0x00000006UL                                      /**< Mode dn_6pct for RAC_PATRIM2                */
#define _RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_na                          0x00000007UL                                      /**< Mode na for RAC_PATRIM2                     */
#define RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_DEFAULT                      (_RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_DEFAULT << 12) /**< Shifted mode DEFAULT for RAC_PATRIM2        */
#define RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_0pct                      (_RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_0pct << 12) /**< Shifted mode dn_0pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_1pct                      (_RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_1pct << 12) /**< Shifted mode dn_1pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_2pct                      (_RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_2pct << 12) /**< Shifted mode dn_2pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_3pct                      (_RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_3pct << 12) /**< Shifted mode dn_3pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_4pct                      (_RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_4pct << 12) /**< Shifted mode dn_4pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_5pct                      (_RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_5pct << 12) /**< Shifted mode dn_5pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_6pct                      (_RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_dn_6pct << 12) /**< Shifted mode dn_6pct for RAC_PATRIM2        */
#define RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_na                           (_RAC_PATRIM2_TXPATRIM10DBMDUTYCYP_na << 12)      /**< Shifted mode na for RAC_PATRIM2             */

/* Bit fields for RAC PATRIM3 */
#define _RAC_PATRIM3_RESETVALUE                                       0x008D33AAUL                                             /**< Default value for RAC_PATRIM3               */
#define _RAC_PATRIM3_MASK                                             0x00FF73FEUL                                             /**< Mask for RAC_PATRIM3                        */
#define RAC_PATRIM3_TXPATRIMBLEEDAUTOREG                              (0x1UL << 1)                                             /**< TXPATRIMBLEEDAUTOREG                        */
#define _RAC_PATRIM3_TXPATRIMBLEEDAUTOREG_SHIFT                       1                                                        /**< Shift value for RAC_TXPATRIMBLEEDAUTOREG    */
#define _RAC_PATRIM3_TXPATRIMBLEEDAUTOREG_MASK                        0x2UL                                                    /**< Bit mask for RAC_TXPATRIMBLEEDAUTOREG       */
#define _RAC_PATRIM3_TXPATRIMBLEEDAUTOREG_DEFAULT                     0x00000001UL                                             /**< Mode DEFAULT for RAC_PATRIM3                */
#define _RAC_PATRIM3_TXPATRIMBLEEDAUTOREG_not_automatic               0x00000000UL                                             /**< Mode not_automatic for RAC_PATRIM3          */
#define _RAC_PATRIM3_TXPATRIMBLEEDAUTOREG_automatic                   0x00000001UL                                             /**< Mode automatic for RAC_PATRIM3              */
#define RAC_PATRIM3_TXPATRIMBLEEDAUTOREG_DEFAULT                      (_RAC_PATRIM3_TXPATRIMBLEEDAUTOREG_DEFAULT << 1)         /**< Shifted mode DEFAULT for RAC_PATRIM3        */
#define RAC_PATRIM3_TXPATRIMBLEEDAUTOREG_not_automatic                (_RAC_PATRIM3_TXPATRIMBLEEDAUTOREG_not_automatic << 1)   /**< Shifted mode not_automatic for RAC_PATRIM3  */
#define RAC_PATRIM3_TXPATRIMBLEEDAUTOREG_automatic                    (_RAC_PATRIM3_TXPATRIMBLEEDAUTOREG_automatic << 1)       /**< Shifted mode automatic for RAC_PATRIM3      */
#define _RAC_PATRIM3_TXPATRIMIBIASMASTER_SHIFT                        2                                                        /**< Shift value for RAC_TXPATRIMIBIASMASTER     */
#define _RAC_PATRIM3_TXPATRIMIBIASMASTER_MASK                         0xCUL                                                    /**< Bit mask for RAC_TXPATRIMIBIASMASTER        */
#define _RAC_PATRIM3_TXPATRIMIBIASMASTER_DEFAULT                      0x00000002UL                                             /**< Mode DEFAULT for RAC_PATRIM3                */
#define _RAC_PATRIM3_TXPATRIMIBIASMASTER_Ibias_is_45u                 0x00000000UL                                             /**< Mode Ibias_is_45u for RAC_PATRIM3           */
#define _RAC_PATRIM3_TXPATRIMIBIASMASTER_Ibias_is_47p5u               0x00000001UL                                             /**< Mode Ibias_is_47p5u for RAC_PATRIM3         */
#define _RAC_PATRIM3_TXPATRIMIBIASMASTER_Ibias_is_50u                 0x00000002UL                                             /**< Mode Ibias_is_50u for RAC_PATRIM3           */
#define _RAC_PATRIM3_TXPATRIMIBIASMASTER_Ibias_is_52p5u               0x00000003UL                                             /**< Mode Ibias_is_52p5u for RAC_PATRIM3         */
#define RAC_PATRIM3_TXPATRIMIBIASMASTER_DEFAULT                       (_RAC_PATRIM3_TXPATRIMIBIASMASTER_DEFAULT << 2)          /**< Shifted mode DEFAULT for RAC_PATRIM3        */
#define RAC_PATRIM3_TXPATRIMIBIASMASTER_Ibias_is_45u                  (_RAC_PATRIM3_TXPATRIMIBIASMASTER_Ibias_is_45u << 2)     /**< Shifted mode Ibias_is_45u for RAC_PATRIM3   */
#define RAC_PATRIM3_TXPATRIMIBIASMASTER_Ibias_is_47p5u                (_RAC_PATRIM3_TXPATRIMIBIASMASTER_Ibias_is_47p5u << 2)   /**< Shifted mode Ibias_is_47p5u for RAC_PATRIM3 */
#define RAC_PATRIM3_TXPATRIMIBIASMASTER_Ibias_is_50u                  (_RAC_PATRIM3_TXPATRIMIBIASMASTER_Ibias_is_50u << 2)     /**< Shifted mode Ibias_is_50u for RAC_PATRIM3   */
#define RAC_PATRIM3_TXPATRIMIBIASMASTER_Ibias_is_52p5u                (_RAC_PATRIM3_TXPATRIMIBIASMASTER_Ibias_is_52p5u << 2)   /**< Shifted mode Ibias_is_52p5u for RAC_PATRIM3 */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGFB_SHIFT                        4                                                        /**< Shift value for RAC_TXPATRIMPREDRVREGFB     */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGFB_MASK                         0x30UL                                                   /**< Bit mask for RAC_TXPATRIMPREDRVREGFB        */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGFB_DEFAULT                      0x00000002UL                                             /**< Mode DEFAULT for RAC_PATRIM3                */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGFB_vreg_1p22                    0x00000000UL                                             /**< Mode vreg_1p22 for RAC_PATRIM3              */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGFB_vreg_1p28                    0x00000001UL                                             /**< Mode vreg_1p28 for RAC_PATRIM3              */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGFB_vreg_1p35                    0x00000002UL                                             /**< Mode vreg_1p35 for RAC_PATRIM3              */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGFB_vreg_1p44                    0x00000003UL                                             /**< Mode vreg_1p44 for RAC_PATRIM3              */
#define RAC_PATRIM3_TXPATRIMPREDRVREGFB_DEFAULT                       (_RAC_PATRIM3_TXPATRIMPREDRVREGFB_DEFAULT << 4)          /**< Shifted mode DEFAULT for RAC_PATRIM3        */
#define RAC_PATRIM3_TXPATRIMPREDRVREGFB_vreg_1p22                     (_RAC_PATRIM3_TXPATRIMPREDRVREGFB_vreg_1p22 << 4)        /**< Shifted mode vreg_1p22 for RAC_PATRIM3      */
#define RAC_PATRIM3_TXPATRIMPREDRVREGFB_vreg_1p28                     (_RAC_PATRIM3_TXPATRIMPREDRVREGFB_vreg_1p28 << 4)        /**< Shifted mode vreg_1p28 for RAC_PATRIM3      */
#define RAC_PATRIM3_TXPATRIMPREDRVREGFB_vreg_1p35                     (_RAC_PATRIM3_TXPATRIMPREDRVREGFB_vreg_1p35 << 4)        /**< Shifted mode vreg_1p35 for RAC_PATRIM3      */
#define RAC_PATRIM3_TXPATRIMPREDRVREGFB_vreg_1p44                     (_RAC_PATRIM3_TXPATRIMPREDRVREGFB_vreg_1p44 << 4)        /**< Shifted mode vreg_1p44 for RAC_PATRIM3      */
#define RAC_PATRIM3_TXPATRIMPREDRVREGFBKATT                           (0x1UL << 6)                                             /**< TXPATRIMPREDRVREGFBKATT                     */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGFBKATT_SHIFT                    6                                                        /**< Shift value for RAC_TXPATRIMPREDRVREGFBKATT */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGFBKATT_MASK                     0x40UL                                                   /**< Bit mask for RAC_TXPATRIMPREDRVREGFBKATT    */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGFBKATT_DEFAULT                  0x00000000UL                                             /**< Mode DEFAULT for RAC_PATRIM3                */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGFBKATT_less_bw                  0x00000000UL                                             /**< Mode less_bw for RAC_PATRIM3                */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGFBKATT_more_bw                  0x00000001UL                                             /**< Mode more_bw for RAC_PATRIM3                */
#define RAC_PATRIM3_TXPATRIMPREDRVREGFBKATT_DEFAULT                   (_RAC_PATRIM3_TXPATRIMPREDRVREGFBKATT_DEFAULT << 6)      /**< Shifted mode DEFAULT for RAC_PATRIM3        */
#define RAC_PATRIM3_TXPATRIMPREDRVREGFBKATT_less_bw                   (_RAC_PATRIM3_TXPATRIMPREDRVREGFBKATT_less_bw << 6)      /**< Shifted mode less_bw for RAC_PATRIM3        */
#define RAC_PATRIM3_TXPATRIMPREDRVREGFBKATT_more_bw                   (_RAC_PATRIM3_TXPATRIMPREDRVREGFBKATT_more_bw << 6)      /**< Shifted mode more_bw for RAC_PATRIM3        */
#define RAC_PATRIM3_TXPATRIMPREDRVREGPSR                              (0x1UL << 7)                                             /**< TXPATRIMPREDRVREGPSR                        */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGPSR_SHIFT                       7                                                        /**< Shift value for RAC_TXPATRIMPREDRVREGPSR    */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGPSR_MASK                        0x80UL                                                   /**< Bit mask for RAC_TXPATRIMPREDRVREGPSR       */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGPSR_DEFAULT                     0x00000001UL                                             /**< Mode DEFAULT for RAC_PATRIM3                */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGPSR_low_psr                     0x00000000UL                                             /**< Mode low_psr for RAC_PATRIM3                */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGPSR_high_psr                    0x00000001UL                                             /**< Mode high_psr for RAC_PATRIM3               */
#define RAC_PATRIM3_TXPATRIMPREDRVREGPSR_DEFAULT                      (_RAC_PATRIM3_TXPATRIMPREDRVREGPSR_DEFAULT << 7)         /**< Shifted mode DEFAULT for RAC_PATRIM3        */
#define RAC_PATRIM3_TXPATRIMPREDRVREGPSR_low_psr                      (_RAC_PATRIM3_TXPATRIMPREDRVREGPSR_low_psr << 7)         /**< Shifted mode low_psr for RAC_PATRIM3        */
#define RAC_PATRIM3_TXPATRIMPREDRVREGPSR_high_psr                     (_RAC_PATRIM3_TXPATRIMPREDRVREGPSR_high_psr << 7)        /**< Shifted mode high_psr for RAC_PATRIM3       */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGSLICES_SHIFT                    8                                                        /**< Shift value for RAC_TXPATRIMPREDRVREGSLICES */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGSLICES_MASK                     0x300UL                                                  /**< Bit mask for RAC_TXPATRIMPREDRVREGSLICES    */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGSLICES_DEFAULT                  0x00000003UL                                             /**< Mode DEFAULT for RAC_PATRIM3                */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGSLICES_iload_7p5mA              0x00000000UL                                             /**< Mode iload_7p5mA for RAC_PATRIM3            */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGSLICES_iload_15mA               0x00000001UL                                             /**< Mode iload_15mA for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGSLICES_iload_22p5mA             0x00000002UL                                             /**< Mode iload_22p5mA for RAC_PATRIM3           */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGSLICES_iload_30mA               0x00000003UL                                             /**< Mode iload_30mA for RAC_PATRIM3             */
#define RAC_PATRIM3_TXPATRIMPREDRVREGSLICES_DEFAULT                   (_RAC_PATRIM3_TXPATRIMPREDRVREGSLICES_DEFAULT << 8)      /**< Shifted mode DEFAULT for RAC_PATRIM3        */
#define RAC_PATRIM3_TXPATRIMPREDRVREGSLICES_iload_7p5mA               (_RAC_PATRIM3_TXPATRIMPREDRVREGSLICES_iload_7p5mA << 8)  /**< Shifted mode iload_7p5mA for RAC_PATRIM3    */
#define RAC_PATRIM3_TXPATRIMPREDRVREGSLICES_iload_15mA                (_RAC_PATRIM3_TXPATRIMPREDRVREGSLICES_iload_15mA << 8)   /**< Shifted mode iload_15mA for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMPREDRVREGSLICES_iload_22p5mA              (_RAC_PATRIM3_TXPATRIMPREDRVREGSLICES_iload_22p5mA << 8) /**< Shifted mode iload_22p5mA for RAC_PATRIM3   */
#define RAC_PATRIM3_TXPATRIMPREDRVREGSLICES_iload_30mA                (_RAC_PATRIM3_TXPATRIMPREDRVREGSLICES_iload_30mA << 8)   /**< Shifted mode iload_30mA for RAC_PATRIM3     */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGVREF_SHIFT                      12                                                       /**< Shift value for RAC_TXPATRIMPREDRVREGVREF   */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGVREF_MASK                       0x7000UL                                                 /**< Bit mask for RAC_TXPATRIMPREDRVREGVREF      */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGVREF_DEFAULT                    0x00000003UL                                             /**< Mode DEFAULT for RAC_PATRIM3                */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p675                 0x00000000UL                                             /**< Mode vref_0p675 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p700                 0x00000001UL                                             /**< Mode vref_0p700 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p725                 0x00000002UL                                             /**< Mode vref_0p725 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p750                 0x00000003UL                                             /**< Mode vref_0p750 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p775                 0x00000004UL                                             /**< Mode vref_0p775 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p800                 0x00000005UL                                             /**< Mode vref_0p800 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p825                 0x00000006UL                                             /**< Mode vref_0p825 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p850                 0x00000007UL                                             /**< Mode vref_0p850 for RAC_PATRIM3             */
#define RAC_PATRIM3_TXPATRIMPREDRVREGVREF_DEFAULT                     (_RAC_PATRIM3_TXPATRIMPREDRVREGVREF_DEFAULT << 12)       /**< Shifted mode DEFAULT for RAC_PATRIM3        */
#define RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p675                  (_RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p675 << 12)    /**< Shifted mode vref_0p675 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p700                  (_RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p700 << 12)    /**< Shifted mode vref_0p700 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p725                  (_RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p725 << 12)    /**< Shifted mode vref_0p725 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p750                  (_RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p750 << 12)    /**< Shifted mode vref_0p750 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p775                  (_RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p775 << 12)    /**< Shifted mode vref_0p775 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p800                  (_RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p800 << 12)    /**< Shifted mode vref_0p800 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p825                  (_RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p825 << 12)    /**< Shifted mode vref_0p825 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p850                  (_RAC_PATRIM3_TXPATRIMPREDRVREGVREF_vref_0p850 << 12)    /**< Shifted mode vref_0p850 for RAC_PATRIM3     */
#define _RAC_PATRIM3_TXPATRIMREGFB_SHIFT                              16                                                       /**< Shift value for RAC_TXPATRIMREGFB           */
#define _RAC_PATRIM3_TXPATRIMREGFB_MASK                               0x70000UL                                                /**< Bit mask for RAC_TXPATRIMREGFB              */
#define _RAC_PATRIM3_TXPATRIMREGFB_DEFAULT                            0x00000005UL                                             /**< Mode DEFAULT for RAC_PATRIM3                */
#define _RAC_PATRIM3_TXPATRIMREGFB_vreg_1p678                         0x00000000UL                                             /**< Mode vreg_1p678 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGFB_vreg_1p735                         0x00000001UL                                             /**< Mode vreg_1p735 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGFB_vreg_1p801                         0x00000002UL                                             /**< Mode vreg_1p801 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGFB_vreg_1p875                         0x00000003UL                                             /**< Mode vreg_1p875 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGFB_vreg_3p00                          0x00000004UL                                             /**< Mode vreg_3p00 for RAC_PATRIM3              */
#define _RAC_PATRIM3_TXPATRIMREGFB_vreg_3p14                          0x00000005UL                                             /**< Mode vreg_3p14 for RAC_PATRIM3              */
#define _RAC_PATRIM3_TXPATRIMREGFB_vreg_3p3                           0x00000006UL                                             /**< Mode vreg_3p3 for RAC_PATRIM3               */
#define _RAC_PATRIM3_TXPATRIMREGFB_vreg_3p477                         0x00000007UL                                             /**< Mode vreg_3p477 for RAC_PATRIM3             */
#define RAC_PATRIM3_TXPATRIMREGFB_DEFAULT                             (_RAC_PATRIM3_TXPATRIMREGFB_DEFAULT << 16)               /**< Shifted mode DEFAULT for RAC_PATRIM3        */
#define RAC_PATRIM3_TXPATRIMREGFB_vreg_1p678                          (_RAC_PATRIM3_TXPATRIMREGFB_vreg_1p678 << 16)            /**< Shifted mode vreg_1p678 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGFB_vreg_1p735                          (_RAC_PATRIM3_TXPATRIMREGFB_vreg_1p735 << 16)            /**< Shifted mode vreg_1p735 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGFB_vreg_1p801                          (_RAC_PATRIM3_TXPATRIMREGFB_vreg_1p801 << 16)            /**< Shifted mode vreg_1p801 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGFB_vreg_1p875                          (_RAC_PATRIM3_TXPATRIMREGFB_vreg_1p875 << 16)            /**< Shifted mode vreg_1p875 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGFB_vreg_3p00                           (_RAC_PATRIM3_TXPATRIMREGFB_vreg_3p00 << 16)             /**< Shifted mode vreg_3p00 for RAC_PATRIM3      */
#define RAC_PATRIM3_TXPATRIMREGFB_vreg_3p14                           (_RAC_PATRIM3_TXPATRIMREGFB_vreg_3p14 << 16)             /**< Shifted mode vreg_3p14 for RAC_PATRIM3      */
#define RAC_PATRIM3_TXPATRIMREGFB_vreg_3p3                            (_RAC_PATRIM3_TXPATRIMREGFB_vreg_3p3 << 16)              /**< Shifted mode vreg_3p3 for RAC_PATRIM3       */
#define RAC_PATRIM3_TXPATRIMREGFB_vreg_3p477                          (_RAC_PATRIM3_TXPATRIMREGFB_vreg_3p477 << 16)            /**< Shifted mode vreg_3p477 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGPSR                                    (0x1UL << 19)                                            /**< TXPATRIMREGPSR                              */
#define _RAC_PATRIM3_TXPATRIMREGPSR_SHIFT                             19                                                       /**< Shift value for RAC_TXPATRIMREGPSR          */
#define _RAC_PATRIM3_TXPATRIMREGPSR_MASK                              0x80000UL                                                /**< Bit mask for RAC_TXPATRIMREGPSR             */
#define _RAC_PATRIM3_TXPATRIMREGPSR_DEFAULT                           0x00000001UL                                             /**< Mode DEFAULT for RAC_PATRIM3                */
#define _RAC_PATRIM3_TXPATRIMREGPSR_low_psr                           0x00000000UL                                             /**< Mode low_psr for RAC_PATRIM3                */
#define _RAC_PATRIM3_TXPATRIMREGPSR_high_psr                          0x00000001UL                                             /**< Mode high_psr for RAC_PATRIM3               */
#define RAC_PATRIM3_TXPATRIMREGPSR_DEFAULT                            (_RAC_PATRIM3_TXPATRIMREGPSR_DEFAULT << 19)              /**< Shifted mode DEFAULT for RAC_PATRIM3        */
#define RAC_PATRIM3_TXPATRIMREGPSR_low_psr                            (_RAC_PATRIM3_TXPATRIMREGPSR_low_psr << 19)              /**< Shifted mode low_psr for RAC_PATRIM3        */
#define RAC_PATRIM3_TXPATRIMREGPSR_high_psr                           (_RAC_PATRIM3_TXPATRIMREGPSR_high_psr << 19)             /**< Shifted mode high_psr for RAC_PATRIM3       */
#define _RAC_PATRIM3_TXPATRIMREGVREF_SHIFT                            20                                                       /**< Shift value for RAC_TXPATRIMREGVREF         */
#define _RAC_PATRIM3_TXPATRIMREGVREF_MASK                             0xF00000UL                                               /**< Bit mask for RAC_TXPATRIMREGVREF            */
#define _RAC_PATRIM3_TXPATRIMREGVREF_DEFAULT                          0x00000008UL                                             /**< Mode DEFAULT for RAC_PATRIM3                */
#define _RAC_PATRIM3_TXPATRIMREGVREF_vref_0p651                       0x00000000UL                                             /**< Mode vref_0p651 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGVREF_vref_0p663                       0x00000001UL                                             /**< Mode vref_0p663 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGVREF_vref_0p676                       0x00000002UL                                             /**< Mode vref_0p676 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGVREF_vref_0p688                       0x00000003UL                                             /**< Mode vref_0p688 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGVREF_vref_0p701                       0x00000004UL                                             /**< Mode vref_0p701 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGVREF_vref_0p713                       0x00000005UL                                             /**< Mode vref_0p713 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGVREF_vref_0p726                       0x00000006UL                                             /**< Mode vref_0p726 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGVREF_vref_0p738                       0x00000007UL                                             /**< Mode vref_0p738 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGVREF_vref_0p751                       0x00000008UL                                             /**< Mode vref_0p751 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGVREF_vref_0p763                       0x00000009UL                                             /**< Mode vref_0p763 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGVREF_vref_0p776                       0x0000000AUL                                             /**< Mode vref_0p776 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGVREF_vref_0p788                       0x0000000BUL                                             /**< Mode vref_0p788 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGVREF_vref_0p801                       0x0000000CUL                                             /**< Mode vref_0p801 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGVREF_vref_0p813                       0x0000000DUL                                             /**< Mode vref_0p813 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGVREF_vref_0p826                       0x0000000EUL                                             /**< Mode vref_0p826 for RAC_PATRIM3             */
#define _RAC_PATRIM3_TXPATRIMREGVREF_vref_0p838                       0x0000000FUL                                             /**< Mode vref_0p838 for RAC_PATRIM3             */
#define RAC_PATRIM3_TXPATRIMREGVREF_DEFAULT                           (_RAC_PATRIM3_TXPATRIMREGVREF_DEFAULT << 20)             /**< Shifted mode DEFAULT for RAC_PATRIM3        */
#define RAC_PATRIM3_TXPATRIMREGVREF_vref_0p651                        (_RAC_PATRIM3_TXPATRIMREGVREF_vref_0p651 << 20)          /**< Shifted mode vref_0p651 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGVREF_vref_0p663                        (_RAC_PATRIM3_TXPATRIMREGVREF_vref_0p663 << 20)          /**< Shifted mode vref_0p663 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGVREF_vref_0p676                        (_RAC_PATRIM3_TXPATRIMREGVREF_vref_0p676 << 20)          /**< Shifted mode vref_0p676 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGVREF_vref_0p688                        (_RAC_PATRIM3_TXPATRIMREGVREF_vref_0p688 << 20)          /**< Shifted mode vref_0p688 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGVREF_vref_0p701                        (_RAC_PATRIM3_TXPATRIMREGVREF_vref_0p701 << 20)          /**< Shifted mode vref_0p701 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGVREF_vref_0p713                        (_RAC_PATRIM3_TXPATRIMREGVREF_vref_0p713 << 20)          /**< Shifted mode vref_0p713 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGVREF_vref_0p726                        (_RAC_PATRIM3_TXPATRIMREGVREF_vref_0p726 << 20)          /**< Shifted mode vref_0p726 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGVREF_vref_0p738                        (_RAC_PATRIM3_TXPATRIMREGVREF_vref_0p738 << 20)          /**< Shifted mode vref_0p738 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGVREF_vref_0p751                        (_RAC_PATRIM3_TXPATRIMREGVREF_vref_0p751 << 20)          /**< Shifted mode vref_0p751 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGVREF_vref_0p763                        (_RAC_PATRIM3_TXPATRIMREGVREF_vref_0p763 << 20)          /**< Shifted mode vref_0p763 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGVREF_vref_0p776                        (_RAC_PATRIM3_TXPATRIMREGVREF_vref_0p776 << 20)          /**< Shifted mode vref_0p776 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGVREF_vref_0p788                        (_RAC_PATRIM3_TXPATRIMREGVREF_vref_0p788 << 20)          /**< Shifted mode vref_0p788 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGVREF_vref_0p801                        (_RAC_PATRIM3_TXPATRIMREGVREF_vref_0p801 << 20)          /**< Shifted mode vref_0p801 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGVREF_vref_0p813                        (_RAC_PATRIM3_TXPATRIMREGVREF_vref_0p813 << 20)          /**< Shifted mode vref_0p813 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGVREF_vref_0p826                        (_RAC_PATRIM3_TXPATRIMREGVREF_vref_0p826 << 20)          /**< Shifted mode vref_0p826 for RAC_PATRIM3     */
#define RAC_PATRIM3_TXPATRIMREGVREF_vref_0p838                        (_RAC_PATRIM3_TXPATRIMREGVREF_vref_0p838 << 20)          /**< Shifted mode vref_0p838 for RAC_PATRIM3     */

/* Bit fields for RAC PATRIM4 */
#define _RAC_PATRIM4_RESETVALUE                                       0x00006000UL                                         /**< Default value for RAC_PATRIM4               */
#define _RAC_PATRIM4_MASK                                             0x03FFFFFFUL                                         /**< Mask for RAC_PATRIM4                        */
#define _RAC_PATRIM4_TXPATRIM10DBMCTAP_SHIFT                          0                                                    /**< Shift value for RAC_TXPATRIM10DBMCTAP       */
#define _RAC_PATRIM4_TXPATRIM10DBMCTAP_MASK                           0xFUL                                                /**< Bit mask for RAC_TXPATRIM10DBMCTAP          */
#define _RAC_PATRIM4_TXPATRIM10DBMCTAP_DEFAULT                        0x00000000UL                                         /**< Mode DEFAULT for RAC_PATRIM4                */
#define _RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_0                    0x00000000UL                                         /**< Mode ctap_trim_0 for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_1                    0x00000001UL                                         /**< Mode ctap_trim_1 for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_2                    0x00000002UL                                         /**< Mode ctap_trim_2 for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_3                    0x00000003UL                                         /**< Mode ctap_trim_3 for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_4                    0x00000004UL                                         /**< Mode ctap_trim_4 for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_5                    0x00000005UL                                         /**< Mode ctap_trim_5 for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_6                    0x00000006UL                                         /**< Mode ctap_trim_6 for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_7                    0x00000007UL                                         /**< Mode ctap_trim_7 for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_8                    0x00000008UL                                         /**< Mode ctap_trim_8 for RAC_PATRIM4            */
#define RAC_PATRIM4_TXPATRIM10DBMCTAP_DEFAULT                         (_RAC_PATRIM4_TXPATRIM10DBMCTAP_DEFAULT << 0)        /**< Shifted mode DEFAULT for RAC_PATRIM4        */
#define RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_0                     (_RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_0 << 0)    /**< Shifted mode ctap_trim_0 for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_1                     (_RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_1 << 0)    /**< Shifted mode ctap_trim_1 for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_2                     (_RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_2 << 0)    /**< Shifted mode ctap_trim_2 for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_3                     (_RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_3 << 0)    /**< Shifted mode ctap_trim_3 for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_4                     (_RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_4 << 0)    /**< Shifted mode ctap_trim_4 for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_5                     (_RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_5 << 0)    /**< Shifted mode ctap_trim_5 for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_6                     (_RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_6 << 0)    /**< Shifted mode ctap_trim_6 for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_7                     (_RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_7 << 0)    /**< Shifted mode ctap_trim_7 for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_8                     (_RAC_PATRIM4_TXPATRIM10DBMCTAP_ctap_trim_8 << 0)    /**< Shifted mode ctap_trim_8 for RAC_PATRIM4    */
#define _RAC_PATRIM4_TXPATRIM10DBMPREDRVCAP_SHIFT                     4                                                    /**< Shift value for RAC_TXPATRIM10DBMPREDRVCAP  */
#define _RAC_PATRIM4_TXPATRIM10DBMPREDRVCAP_MASK                      0x30UL                                               /**< Bit mask for RAC_TXPATRIM10DBMPREDRVCAP     */
#define _RAC_PATRIM4_TXPATRIM10DBMPREDRVCAP_DEFAULT                   0x00000000UL                                         /**< Mode DEFAULT for RAC_PATRIM4                */
#define _RAC_PATRIM4_TXPATRIM10DBMPREDRVCAP_cap_0                     0x00000000UL                                         /**< Mode cap_0 for RAC_PATRIM4                  */
#define _RAC_PATRIM4_TXPATRIM10DBMPREDRVCAP_cap_1                     0x00000001UL                                         /**< Mode cap_1 for RAC_PATRIM4                  */
#define _RAC_PATRIM4_TXPATRIM10DBMPREDRVCAP_cap_2                     0x00000002UL                                         /**< Mode cap_2 for RAC_PATRIM4                  */
#define _RAC_PATRIM4_TXPATRIM10DBMPREDRVCAP_cap_3                     0x00000003UL                                         /**< Mode cap_3 for RAC_PATRIM4                  */
#define RAC_PATRIM4_TXPATRIM10DBMPREDRVCAP_DEFAULT                    (_RAC_PATRIM4_TXPATRIM10DBMPREDRVCAP_DEFAULT << 4)   /**< Shifted mode DEFAULT for RAC_PATRIM4        */
#define RAC_PATRIM4_TXPATRIM10DBMPREDRVCAP_cap_0                      (_RAC_PATRIM4_TXPATRIM10DBMPREDRVCAP_cap_0 << 4)     /**< Shifted mode cap_0 for RAC_PATRIM4          */
#define RAC_PATRIM4_TXPATRIM10DBMPREDRVCAP_cap_1                      (_RAC_PATRIM4_TXPATRIM10DBMPREDRVCAP_cap_1 << 4)     /**< Shifted mode cap_1 for RAC_PATRIM4          */
#define RAC_PATRIM4_TXPATRIM10DBMPREDRVCAP_cap_2                      (_RAC_PATRIM4_TXPATRIM10DBMPREDRVCAP_cap_2 << 4)     /**< Shifted mode cap_2 for RAC_PATRIM4          */
#define RAC_PATRIM4_TXPATRIM10DBMPREDRVCAP_cap_3                      (_RAC_PATRIM4_TXPATRIM10DBMPREDRVCAP_cap_3 << 4)     /**< Shifted mode cap_3 for RAC_PATRIM4          */
#define _RAC_PATRIM4_TXPATRIM10DBMPREDRVSLC_SHIFT                     6                                                    /**< Shift value for RAC_TXPATRIM10DBMPREDRVSLC  */
#define _RAC_PATRIM4_TXPATRIM10DBMPREDRVSLC_MASK                      0xC0UL                                               /**< Bit mask for RAC_TXPATRIM10DBMPREDRVSLC     */
#define _RAC_PATRIM4_TXPATRIM10DBMPREDRVSLC_DEFAULT                   0x00000000UL                                         /**< Mode DEFAULT for RAC_PATRIM4                */
#define _RAC_PATRIM4_TXPATRIM10DBMPREDRVSLC_slc_0                     0x00000000UL                                         /**< Mode slc_0 for RAC_PATRIM4                  */
#define _RAC_PATRIM4_TXPATRIM10DBMPREDRVSLC_slc_1                     0x00000001UL                                         /**< Mode slc_1 for RAC_PATRIM4                  */
#define _RAC_PATRIM4_TXPATRIM10DBMPREDRVSLC_slc_2                     0x00000002UL                                         /**< Mode slc_2 for RAC_PATRIM4                  */
#define _RAC_PATRIM4_TXPATRIM10DBMPREDRVSLC_slc_3                     0x00000003UL                                         /**< Mode slc_3 for RAC_PATRIM4                  */
#define RAC_PATRIM4_TXPATRIM10DBMPREDRVSLC_DEFAULT                    (_RAC_PATRIM4_TXPATRIM10DBMPREDRVSLC_DEFAULT << 6)   /**< Shifted mode DEFAULT for RAC_PATRIM4        */
#define RAC_PATRIM4_TXPATRIM10DBMPREDRVSLC_slc_0                      (_RAC_PATRIM4_TXPATRIM10DBMPREDRVSLC_slc_0 << 6)     /**< Shifted mode slc_0 for RAC_PATRIM4          */
#define RAC_PATRIM4_TXPATRIM10DBMPREDRVSLC_slc_1                      (_RAC_PATRIM4_TXPATRIM10DBMPREDRVSLC_slc_1 << 6)     /**< Shifted mode slc_1 for RAC_PATRIM4          */
#define RAC_PATRIM4_TXPATRIM10DBMPREDRVSLC_slc_2                      (_RAC_PATRIM4_TXPATRIM10DBMPREDRVSLC_slc_2 << 6)     /**< Shifted mode slc_2 for RAC_PATRIM4          */
#define RAC_PATRIM4_TXPATRIM10DBMPREDRVSLC_slc_3                      (_RAC_PATRIM4_TXPATRIM10DBMPREDRVSLC_slc_3 << 6)     /**< Shifted mode slc_3 for RAC_PATRIM4          */
#define _RAC_PATRIM4_TXPATRIM20DBMCTAP_SHIFT                          8                                                    /**< Shift value for RAC_TXPATRIM20DBMCTAP       */
#define _RAC_PATRIM4_TXPATRIM20DBMCTAP_MASK                           0xF00UL                                              /**< Bit mask for RAC_TXPATRIM20DBMCTAP          */
#define _RAC_PATRIM4_TXPATRIM20DBMCTAP_DEFAULT                        0x00000000UL                                         /**< Mode DEFAULT for RAC_PATRIM4                */
#define _RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_0                    0x00000000UL                                         /**< Mode ctap_trim_0 for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_1                    0x00000001UL                                         /**< Mode ctap_trim_1 for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_2                    0x00000002UL                                         /**< Mode ctap_trim_2 for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_3                    0x00000003UL                                         /**< Mode ctap_trim_3 for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_4                    0x00000004UL                                         /**< Mode ctap_trim_4 for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_5                    0x00000005UL                                         /**< Mode ctap_trim_5 for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_6                    0x00000006UL                                         /**< Mode ctap_trim_6 for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_7                    0x00000007UL                                         /**< Mode ctap_trim_7 for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_8                    0x00000008UL                                         /**< Mode ctap_trim_8 for RAC_PATRIM4            */
#define RAC_PATRIM4_TXPATRIM20DBMCTAP_DEFAULT                         (_RAC_PATRIM4_TXPATRIM20DBMCTAP_DEFAULT << 8)        /**< Shifted mode DEFAULT for RAC_PATRIM4        */
#define RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_0                     (_RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_0 << 8)    /**< Shifted mode ctap_trim_0 for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_1                     (_RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_1 << 8)    /**< Shifted mode ctap_trim_1 for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_2                     (_RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_2 << 8)    /**< Shifted mode ctap_trim_2 for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_3                     (_RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_3 << 8)    /**< Shifted mode ctap_trim_3 for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_4                     (_RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_4 << 8)    /**< Shifted mode ctap_trim_4 for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_5                     (_RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_5 << 8)    /**< Shifted mode ctap_trim_5 for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_6                     (_RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_6 << 8)    /**< Shifted mode ctap_trim_6 for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_7                     (_RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_7 << 8)    /**< Shifted mode ctap_trim_7 for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_8                     (_RAC_PATRIM4_TXPATRIM20DBMCTAP_ctap_trim_8 << 8)    /**< Shifted mode ctap_trim_8 for RAC_PATRIM4    */
#define _RAC_PATRIM4_TXPATRIM20DBMPREDRV_SHIFT                        12                                                   /**< Shift value for RAC_TXPATRIM20DBMPREDRV     */
#define _RAC_PATRIM4_TXPATRIM20DBMPREDRV_MASK                         0xF000UL                                             /**< Bit mask for RAC_TXPATRIM20DBMPREDRV        */
#define _RAC_PATRIM4_TXPATRIM20DBMPREDRV_DEFAULT                      0x00000006UL                                         /**< Mode DEFAULT for RAC_PATRIM4                */
#define _RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_137ps                  0x00000000UL                                         /**< Mode trise_137ps for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_127ps                  0x00000001UL                                         /**< Mode trise_127ps for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_117ps                  0x00000002UL                                         /**< Mode trise_117ps for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_110ps                  0x00000003UL                                         /**< Mode trise_110ps for RAC_PATRIM4            */
#define _RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_75ps                   0x00000004UL                                         /**< Mode trise_75ps for RAC_PATRIM4             */
#define _RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_73ps                   0x00000005UL                                         /**< Mode trise_73ps for RAC_PATRIM4             */
#define _RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_71ps                   0x00000006UL                                         /**< Mode trise_71ps for RAC_PATRIM4             */
#define _RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_70ps                   0x00000007UL                                         /**< Mode trise_70ps for RAC_PATRIM4             */
#define RAC_PATRIM4_TXPATRIM20DBMPREDRV_DEFAULT                       (_RAC_PATRIM4_TXPATRIM20DBMPREDRV_DEFAULT << 12)     /**< Shifted mode DEFAULT for RAC_PATRIM4        */
#define RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_137ps                   (_RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_137ps << 12) /**< Shifted mode trise_137ps for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_127ps                   (_RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_127ps << 12) /**< Shifted mode trise_127ps for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_117ps                   (_RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_117ps << 12) /**< Shifted mode trise_117ps for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_110ps                   (_RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_110ps << 12) /**< Shifted mode trise_110ps for RAC_PATRIM4    */
#define RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_75ps                    (_RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_75ps << 12)  /**< Shifted mode trise_75ps for RAC_PATRIM4     */
#define RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_73ps                    (_RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_73ps << 12)  /**< Shifted mode trise_73ps for RAC_PATRIM4     */
#define RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_71ps                    (_RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_71ps << 12)  /**< Shifted mode trise_71ps for RAC_PATRIM4     */
#define RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_70ps                    (_RAC_PATRIM4_TXPATRIM20DBMPREDRV_trise_70ps << 12)  /**< Shifted mode trise_70ps for RAC_PATRIM4     */
#define _RAC_PATRIM4_TXPATRIMCAPPAOUTM_SHIFT                          16                                                   /**< Shift value for RAC_TXPATRIMCAPPAOUTM       */
#define _RAC_PATRIM4_TXPATRIMCAPPAOUTM_MASK                           0xF0000UL                                            /**< Bit mask for RAC_TXPATRIMCAPPAOUTM          */
#define _RAC_PATRIM4_TXPATRIMCAPPAOUTM_DEFAULT                        0x00000000UL                                         /**< Mode DEFAULT for RAC_PATRIM4                */
#define RAC_PATRIM4_TXPATRIMCAPPAOUTM_DEFAULT                         (_RAC_PATRIM4_TXPATRIMCAPPAOUTM_DEFAULT << 16)       /**< Shifted mode DEFAULT for RAC_PATRIM4        */
#define _RAC_PATRIM4_TXPATRIMCAPPAOUTP_SHIFT                          20                                                   /**< Shift value for RAC_TXPATRIMCAPPAOUTP       */
#define _RAC_PATRIM4_TXPATRIMCAPPAOUTP_MASK                           0xF00000UL                                           /**< Bit mask for RAC_TXPATRIMCAPPAOUTP          */
#define _RAC_PATRIM4_TXPATRIMCAPPAOUTP_DEFAULT                        0x00000000UL                                         /**< Mode DEFAULT for RAC_PATRIM4                */
#define RAC_PATRIM4_TXPATRIMCAPPAOUTP_DEFAULT                         (_RAC_PATRIM4_TXPATRIMCAPPAOUTP_DEFAULT << 20)       /**< Shifted mode DEFAULT for RAC_PATRIM4        */
#define _RAC_PATRIM4_TXPATRIMCMGAIN_SHIFT                             24                                                   /**< Shift value for RAC_TXPATRIMCMGAIN          */
#define _RAC_PATRIM4_TXPATRIMCMGAIN_MASK                              0x3000000UL                                          /**< Bit mask for RAC_TXPATRIMCMGAIN             */
#define _RAC_PATRIM4_TXPATRIMCMGAIN_DEFAULT                           0x00000000UL                                         /**< Mode DEFAULT for RAC_PATRIM4                */
#define RAC_PATRIM4_TXPATRIMCMGAIN_DEFAULT                            (_RAC_PATRIM4_TXPATRIMCMGAIN_DEFAULT << 24)          /**< Shifted mode DEFAULT for RAC_PATRIM4        */

/* Bit fields for RAC PATRIM5 */
#define _RAC_PATRIM5_RESETVALUE                                       0x00181800UL                                         /**< Default value for RAC_PATRIM5               */
#define _RAC_PATRIM5_MASK                                             0x033F3F7FUL                                         /**< Mask for RAC_PATRIM5                        */
#define RAC_PATRIM5_TXPATRIMDACGLITCH                                 (0x1UL << 0)                                         /**< TXPATRIMDACGLITCH                           */
#define _RAC_PATRIM5_TXPATRIMDACGLITCH_SHIFT                          0                                                    /**< Shift value for RAC_TXPATRIMDACGLITCH       */
#define _RAC_PATRIM5_TXPATRIMDACGLITCH_MASK                           0x1UL                                                /**< Bit mask for RAC_TXPATRIMDACGLITCH          */
#define _RAC_PATRIM5_TXPATRIMDACGLITCH_DEFAULT                        0x00000000UL                                         /**< Mode DEFAULT for RAC_PATRIM5                */
#define _RAC_PATRIM5_TXPATRIMDACGLITCH_larger_glitch                  0x00000000UL                                         /**< Mode larger_glitch for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMDACGLITCH_smaller_glitch                 0x00000001UL                                         /**< Mode smaller_glitch for RAC_PATRIM5         */
#define RAC_PATRIM5_TXPATRIMDACGLITCH_DEFAULT                         (_RAC_PATRIM5_TXPATRIMDACGLITCH_DEFAULT << 0)        /**< Shifted mode DEFAULT for RAC_PATRIM5        */
#define RAC_PATRIM5_TXPATRIMDACGLITCH_larger_glitch                   (_RAC_PATRIM5_TXPATRIMDACGLITCH_larger_glitch << 0)  /**< Shifted mode larger_glitch for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMDACGLITCH_smaller_glitch                  (_RAC_PATRIM5_TXPATRIMDACGLITCH_smaller_glitch << 0) /**< Shifted mode smaller_glitch for RAC_PATRIM5 */
#define _RAC_PATRIM5_TXPATRIMDLY0_SHIFT                               1                                                    /**< Shift value for RAC_TXPATRIMDLY0            */
#define _RAC_PATRIM5_TXPATRIMDLY0_MASK                                0xEUL                                                /**< Bit mask for RAC_TXPATRIMDLY0               */
#define _RAC_PATRIM5_TXPATRIMDLY0_DEFAULT                             0x00000000UL                                         /**< Mode DEFAULT for RAC_PATRIM5                */
#define _RAC_PATRIM5_TXPATRIMDLY0_tdly_0ps                            0x00000000UL                                         /**< Mode tdly_0ps for RAC_PATRIM5               */
#define _RAC_PATRIM5_TXPATRIMDLY0_tdly_64ps                           0x00000001UL                                         /**< Mode tdly_64ps for RAC_PATRIM5              */
#define _RAC_PATRIM5_TXPATRIMDLY0_tdly_65ps                           0x00000002UL                                         /**< Mode tdly_65ps for RAC_PATRIM5              */
#define _RAC_PATRIM5_TXPATRIMDLY0_tdly_66ps                           0x00000003UL                                         /**< Mode tdly_66ps for RAC_PATRIM5              */
#define _RAC_PATRIM5_TXPATRIMDLY0_tdly_68ps                           0x00000004UL                                         /**< Mode tdly_68ps for RAC_PATRIM5              */
#define _RAC_PATRIM5_TXPATRIMDLY0_tdly_70ps                           0x00000005UL                                         /**< Mode tdly_70ps for RAC_PATRIM5              */
#define _RAC_PATRIM5_TXPATRIMDLY0_tdly_75ps                           0x00000006UL                                         /**< Mode tdly_75ps for RAC_PATRIM5              */
#define _RAC_PATRIM5_TXPATRIMDLY0_tdly_83ps                           0x00000007UL                                         /**< Mode tdly_83ps for RAC_PATRIM5              */
#define RAC_PATRIM5_TXPATRIMDLY0_DEFAULT                              (_RAC_PATRIM5_TXPATRIMDLY0_DEFAULT << 1)             /**< Shifted mode DEFAULT for RAC_PATRIM5        */
#define RAC_PATRIM5_TXPATRIMDLY0_tdly_0ps                             (_RAC_PATRIM5_TXPATRIMDLY0_tdly_0ps << 1)            /**< Shifted mode tdly_0ps for RAC_PATRIM5       */
#define RAC_PATRIM5_TXPATRIMDLY0_tdly_64ps                            (_RAC_PATRIM5_TXPATRIMDLY0_tdly_64ps << 1)           /**< Shifted mode tdly_64ps for RAC_PATRIM5      */
#define RAC_PATRIM5_TXPATRIMDLY0_tdly_65ps                            (_RAC_PATRIM5_TXPATRIMDLY0_tdly_65ps << 1)           /**< Shifted mode tdly_65ps for RAC_PATRIM5      */
#define RAC_PATRIM5_TXPATRIMDLY0_tdly_66ps                            (_RAC_PATRIM5_TXPATRIMDLY0_tdly_66ps << 1)           /**< Shifted mode tdly_66ps for RAC_PATRIM5      */
#define RAC_PATRIM5_TXPATRIMDLY0_tdly_68ps                            (_RAC_PATRIM5_TXPATRIMDLY0_tdly_68ps << 1)           /**< Shifted mode tdly_68ps for RAC_PATRIM5      */
#define RAC_PATRIM5_TXPATRIMDLY0_tdly_70ps                            (_RAC_PATRIM5_TXPATRIMDLY0_tdly_70ps << 1)           /**< Shifted mode tdly_70ps for RAC_PATRIM5      */
#define RAC_PATRIM5_TXPATRIMDLY0_tdly_75ps                            (_RAC_PATRIM5_TXPATRIMDLY0_tdly_75ps << 1)           /**< Shifted mode tdly_75ps for RAC_PATRIM5      */
#define RAC_PATRIM5_TXPATRIMDLY0_tdly_83ps                            (_RAC_PATRIM5_TXPATRIMDLY0_tdly_83ps << 1)           /**< Shifted mode tdly_83ps for RAC_PATRIM5      */
#define _RAC_PATRIM5_TXPATRIMDLY1_SHIFT                               4                                                    /**< Shift value for RAC_TXPATRIMDLY1            */
#define _RAC_PATRIM5_TXPATRIMDLY1_MASK                                0x70UL                                               /**< Bit mask for RAC_TXPATRIMDLY1               */
#define _RAC_PATRIM5_TXPATRIMDLY1_DEFAULT                             0x00000000UL                                         /**< Mode DEFAULT for RAC_PATRIM5                */
#define _RAC_PATRIM5_TXPATRIMDLY1_tdly_0ps                            0x00000000UL                                         /**< Mode tdly_0ps for RAC_PATRIM5               */
#define _RAC_PATRIM5_TXPATRIMDLY1_tdly_64ps                           0x00000001UL                                         /**< Mode tdly_64ps for RAC_PATRIM5              */
#define _RAC_PATRIM5_TXPATRIMDLY1_tdly_65ps                           0x00000002UL                                         /**< Mode tdly_65ps for RAC_PATRIM5              */
#define _RAC_PATRIM5_TXPATRIMDLY1_tdly_66ps                           0x00000003UL                                         /**< Mode tdly_66ps for RAC_PATRIM5              */
#define _RAC_PATRIM5_TXPATRIMDLY1_tdly_68ps                           0x00000004UL                                         /**< Mode tdly_68ps for RAC_PATRIM5              */
#define _RAC_PATRIM5_TXPATRIMDLY1_tdly_70ps                           0x00000005UL                                         /**< Mode tdly_70ps for RAC_PATRIM5              */
#define _RAC_PATRIM5_TXPATRIMDLY1_tdly_75ps                           0x00000006UL                                         /**< Mode tdly_75ps for RAC_PATRIM5              */
#define _RAC_PATRIM5_TXPATRIMDLY1_tdly_83ps                           0x00000007UL                                         /**< Mode tdly_83ps for RAC_PATRIM5              */
#define RAC_PATRIM5_TXPATRIMDLY1_DEFAULT                              (_RAC_PATRIM5_TXPATRIMDLY1_DEFAULT << 4)             /**< Shifted mode DEFAULT for RAC_PATRIM5        */
#define RAC_PATRIM5_TXPATRIMDLY1_tdly_0ps                             (_RAC_PATRIM5_TXPATRIMDLY1_tdly_0ps << 4)            /**< Shifted mode tdly_0ps for RAC_PATRIM5       */
#define RAC_PATRIM5_TXPATRIMDLY1_tdly_64ps                            (_RAC_PATRIM5_TXPATRIMDLY1_tdly_64ps << 4)           /**< Shifted mode tdly_64ps for RAC_PATRIM5      */
#define RAC_PATRIM5_TXPATRIMDLY1_tdly_65ps                            (_RAC_PATRIM5_TXPATRIMDLY1_tdly_65ps << 4)           /**< Shifted mode tdly_65ps for RAC_PATRIM5      */
#define RAC_PATRIM5_TXPATRIMDLY1_tdly_66ps                            (_RAC_PATRIM5_TXPATRIMDLY1_tdly_66ps << 4)           /**< Shifted mode tdly_66ps for RAC_PATRIM5      */
#define RAC_PATRIM5_TXPATRIMDLY1_tdly_68ps                            (_RAC_PATRIM5_TXPATRIMDLY1_tdly_68ps << 4)           /**< Shifted mode tdly_68ps for RAC_PATRIM5      */
#define RAC_PATRIM5_TXPATRIMDLY1_tdly_70ps                            (_RAC_PATRIM5_TXPATRIMDLY1_tdly_70ps << 4)           /**< Shifted mode tdly_70ps for RAC_PATRIM5      */
#define RAC_PATRIM5_TXPATRIMDLY1_tdly_75ps                            (_RAC_PATRIM5_TXPATRIMDLY1_tdly_75ps << 4)           /**< Shifted mode tdly_75ps for RAC_PATRIM5      */
#define RAC_PATRIM5_TXPATRIMDLY1_tdly_83ps                            (_RAC_PATRIM5_TXPATRIMDLY1_tdly_83ps << 4)           /**< Shifted mode tdly_83ps for RAC_PATRIM5      */
#define _RAC_PATRIM5_TXPATRIMNBIAS_SHIFT                              8                                                    /**< Shift value for RAC_TXPATRIMNBIAS           */
#define _RAC_PATRIM5_TXPATRIMNBIAS_MASK                               0xF00UL                                              /**< Bit mask for RAC_TXPATRIMNBIAS              */
#define _RAC_PATRIM5_TXPATRIMNBIAS_DEFAULT                            0x00000008UL                                         /**< Mode DEFAULT for RAC_PATRIM5                */
#define _RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn104mv                     0x00000000UL                                         /**< Mode vnbias_dn104mv for RAC_PATRIM5         */
#define _RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn91mv                      0x00000001UL                                         /**< Mode vnbias_dn91mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn78mv                      0x00000002UL                                         /**< Mode vnbias_dn78mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn65mv                      0x00000003UL                                         /**< Mode vnbias_dn65mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn52mv                      0x00000004UL                                         /**< Mode vnbias_dn52mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn39mv                      0x00000005UL                                         /**< Mode vnbias_dn39mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn26mv                      0x00000006UL                                         /**< Mode vnbias_dn26mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn13mv                      0x00000007UL                                         /**< Mode vnbias_dn13mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMNBIAS_vnbias_default                     0x00000008UL                                         /**< Mode vnbias_default for RAC_PATRIM5         */
#define _RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up13mv                      0x00000009UL                                         /**< Mode vnbias_up13mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up26mv                      0x0000000AUL                                         /**< Mode vnbias_up26mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up39mv                      0x0000000BUL                                         /**< Mode vnbias_up39mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up52mv                      0x0000000CUL                                         /**< Mode vnbias_up52mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up65mv                      0x0000000DUL                                         /**< Mode vnbias_up65mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up78mv                      0x0000000EUL                                         /**< Mode vnbias_up78mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up91mv                      0x0000000FUL                                         /**< Mode vnbias_up91mv for RAC_PATRIM5          */
#define RAC_PATRIM5_TXPATRIMNBIAS_DEFAULT                             (_RAC_PATRIM5_TXPATRIMNBIAS_DEFAULT << 8)            /**< Shifted mode DEFAULT for RAC_PATRIM5        */
#define RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn104mv                      (_RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn104mv << 8)     /**< Shifted mode vnbias_dn104mv for RAC_PATRIM5 */
#define RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn91mv                       (_RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn91mv << 8)      /**< Shifted mode vnbias_dn91mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn78mv                       (_RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn78mv << 8)      /**< Shifted mode vnbias_dn78mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn65mv                       (_RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn65mv << 8)      /**< Shifted mode vnbias_dn65mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn52mv                       (_RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn52mv << 8)      /**< Shifted mode vnbias_dn52mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn39mv                       (_RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn39mv << 8)      /**< Shifted mode vnbias_dn39mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn26mv                       (_RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn26mv << 8)      /**< Shifted mode vnbias_dn26mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn13mv                       (_RAC_PATRIM5_TXPATRIMNBIAS_vnbias_dn13mv << 8)      /**< Shifted mode vnbias_dn13mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMNBIAS_vnbias_default                      (_RAC_PATRIM5_TXPATRIMNBIAS_vnbias_default << 8)     /**< Shifted mode vnbias_default for RAC_PATRIM5 */
#define RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up13mv                       (_RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up13mv << 8)      /**< Shifted mode vnbias_up13mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up26mv                       (_RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up26mv << 8)      /**< Shifted mode vnbias_up26mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up39mv                       (_RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up39mv << 8)      /**< Shifted mode vnbias_up39mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up52mv                       (_RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up52mv << 8)      /**< Shifted mode vnbias_up52mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up65mv                       (_RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up65mv << 8)      /**< Shifted mode vnbias_up65mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up78mv                       (_RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up78mv << 8)      /**< Shifted mode vnbias_up78mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up91mv                       (_RAC_PATRIM5_TXPATRIMNBIAS_vnbias_up91mv << 8)      /**< Shifted mode vnbias_up91mv for RAC_PATRIM5  */
#define _RAC_PATRIM5_TXPATRIMNCASC_SHIFT                              12                                                   /**< Shift value for RAC_TXPATRIMNCASC           */
#define _RAC_PATRIM5_TXPATRIMNCASC_MASK                               0x3000UL                                             /**< Bit mask for RAC_TXPATRIMNCASC              */
#define _RAC_PATRIM5_TXPATRIMNCASC_DEFAULT                            0x00000001UL                                         /**< Mode DEFAULT for RAC_PATRIM5                */
#define _RAC_PATRIM5_TXPATRIMNCASC_ncbias_m50mv                       0x00000000UL                                         /**< Mode ncbias_m50mv for RAC_PATRIM5           */
#define _RAC_PATRIM5_TXPATRIMNCASC_ncbiasdefault                      0x00000001UL                                         /**< Mode ncbiasdefault for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMNCASC_ncbias_p50mv                       0x00000002UL                                         /**< Mode ncbias_p50mv for RAC_PATRIM5           */
#define _RAC_PATRIM5_TXPATRIMNCASC_ncbias_p100mv                      0x00000003UL                                         /**< Mode ncbias_p100mv for RAC_PATRIM5          */
#define RAC_PATRIM5_TXPATRIMNCASC_DEFAULT                             (_RAC_PATRIM5_TXPATRIMNCASC_DEFAULT << 12)           /**< Shifted mode DEFAULT for RAC_PATRIM5        */
#define RAC_PATRIM5_TXPATRIMNCASC_ncbias_m50mv                        (_RAC_PATRIM5_TXPATRIMNCASC_ncbias_m50mv << 12)      /**< Shifted mode ncbias_m50mv for RAC_PATRIM5   */
#define RAC_PATRIM5_TXPATRIMNCASC_ncbiasdefault                       (_RAC_PATRIM5_TXPATRIMNCASC_ncbiasdefault << 12)     /**< Shifted mode ncbiasdefault for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMNCASC_ncbias_p50mv                        (_RAC_PATRIM5_TXPATRIMNCASC_ncbias_p50mv << 12)      /**< Shifted mode ncbias_p50mv for RAC_PATRIM5   */
#define RAC_PATRIM5_TXPATRIMNCASC_ncbias_p100mv                       (_RAC_PATRIM5_TXPATRIMNCASC_ncbias_p100mv << 12)     /**< Shifted mode ncbias_p100mv for RAC_PATRIM5  */
#define _RAC_PATRIM5_TXPATRIMPBIAS_SHIFT                              16                                                   /**< Shift value for RAC_TXPATRIMPBIAS           */
#define _RAC_PATRIM5_TXPATRIMPBIAS_MASK                               0xF0000UL                                            /**< Bit mask for RAC_TXPATRIMPBIAS              */
#define _RAC_PATRIM5_TXPATRIMPBIAS_DEFAULT                            0x00000008UL                                         /**< Mode DEFAULT for RAC_PATRIM5                */
#define _RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up104mv                     0x00000000UL                                         /**< Mode vpbias_up104mv for RAC_PATRIM5         */
#define _RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up91mv                      0x00000001UL                                         /**< Mode vpbias_up91mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up78mv                      0x00000002UL                                         /**< Mode vpbias_up78mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up65mv                      0x00000003UL                                         /**< Mode vpbias_up65mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up52mv                      0x00000004UL                                         /**< Mode vpbias_up52mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up39mv                      0x00000005UL                                         /**< Mode vpbias_up39mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up26mv                      0x00000006UL                                         /**< Mode vpbias_up26mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up13mv                      0x00000007UL                                         /**< Mode vpbias_up13mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMPBIAS_vpbias_default                     0x00000008UL                                         /**< Mode vpbias_default for RAC_PATRIM5         */
#define _RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn13mv                      0x00000009UL                                         /**< Mode vpbias_dn13mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn26mv                      0x0000000AUL                                         /**< Mode vpbias_dn26mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn38mv                      0x0000000BUL                                         /**< Mode vpbias_dn38mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn52mv                      0x0000000CUL                                         /**< Mode vpbias_dn52mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn65mv                      0x0000000DUL                                         /**< Mode vpbias_dn65mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn78mv                      0x0000000EUL                                         /**< Mode vpbias_dn78mv for RAC_PATRIM5          */
#define _RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn91mv                      0x0000000FUL                                         /**< Mode vpbias_dn91mv for RAC_PATRIM5          */
#define RAC_PATRIM5_TXPATRIMPBIAS_DEFAULT                             (_RAC_PATRIM5_TXPATRIMPBIAS_DEFAULT << 16)           /**< Shifted mode DEFAULT for RAC_PATRIM5        */
#define RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up104mv                      (_RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up104mv << 16)    /**< Shifted mode vpbias_up104mv for RAC_PATRIM5 */
#define RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up91mv                       (_RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up91mv << 16)     /**< Shifted mode vpbias_up91mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up78mv                       (_RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up78mv << 16)     /**< Shifted mode vpbias_up78mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up65mv                       (_RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up65mv << 16)     /**< Shifted mode vpbias_up65mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up52mv                       (_RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up52mv << 16)     /**< Shifted mode vpbias_up52mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up39mv                       (_RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up39mv << 16)     /**< Shifted mode vpbias_up39mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up26mv                       (_RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up26mv << 16)     /**< Shifted mode vpbias_up26mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up13mv                       (_RAC_PATRIM5_TXPATRIMPBIAS_vpbias_up13mv << 16)     /**< Shifted mode vpbias_up13mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMPBIAS_vpbias_default                      (_RAC_PATRIM5_TXPATRIMPBIAS_vpbias_default << 16)    /**< Shifted mode vpbias_default for RAC_PATRIM5 */
#define RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn13mv                       (_RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn13mv << 16)     /**< Shifted mode vpbias_dn13mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn26mv                       (_RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn26mv << 16)     /**< Shifted mode vpbias_dn26mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn38mv                       (_RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn38mv << 16)     /**< Shifted mode vpbias_dn38mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn52mv                       (_RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn52mv << 16)     /**< Shifted mode vpbias_dn52mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn65mv                       (_RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn65mv << 16)     /**< Shifted mode vpbias_dn65mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn78mv                       (_RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn78mv << 16)     /**< Shifted mode vpbias_dn78mv for RAC_PATRIM5  */
#define RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn91mv                       (_RAC_PATRIM5_TXPATRIMPBIAS_vpbias_dn91mv << 16)     /**< Shifted mode vpbias_dn91mv for RAC_PATRIM5  */
#define _RAC_PATRIM5_TXPATRIMPCASC_SHIFT                              20                                                   /**< Shift value for RAC_TXPATRIMPCASC           */
#define _RAC_PATRIM5_TXPATRIMPCASC_MASK                               0x300000UL                                           /**< Bit mask for RAC_TXPATRIMPCASC              */
#define _RAC_PATRIM5_TXPATRIMPCASC_DEFAULT                            0x00000001UL                                         /**< Mode DEFAULT for RAC_PATRIM5                */
#define _RAC_PATRIM5_TXPATRIMPCASC_pcbias_n50mv                       0x00000000UL                                         /**< Mode pcbias_n50mv for RAC_PATRIM5           */
#define _RAC_PATRIM5_TXPATRIMPCASC_pcbias_default                     0x00000001UL                                         /**< Mode pcbias_default for RAC_PATRIM5         */
#define _RAC_PATRIM5_TXPATRIMPCASC_pcbias_m50mv                       0x00000002UL                                         /**< Mode pcbias_m50mv for RAC_PATRIM5           */
#define _RAC_PATRIM5_TXPATRIMPCASC_pcbias_m100mv                      0x00000003UL                                         /**< Mode pcbias_m100mv for RAC_PATRIM5          */
#define RAC_PATRIM5_TXPATRIMPCASC_DEFAULT                             (_RAC_PATRIM5_TXPATRIMPCASC_DEFAULT << 20)           /**< Shifted mode DEFAULT for RAC_PATRIM5        */
#define RAC_PATRIM5_TXPATRIMPCASC_pcbias_n50mv                        (_RAC_PATRIM5_TXPATRIMPCASC_pcbias_n50mv << 20)      /**< Shifted mode pcbias_n50mv for RAC_PATRIM5   */
#define RAC_PATRIM5_TXPATRIMPCASC_pcbias_default                      (_RAC_PATRIM5_TXPATRIMPCASC_pcbias_default << 20)    /**< Shifted mode pcbias_default for RAC_PATRIM5 */
#define RAC_PATRIM5_TXPATRIMPCASC_pcbias_m50mv                        (_RAC_PATRIM5_TXPATRIMPCASC_pcbias_m50mv << 20)      /**< Shifted mode pcbias_m50mv for RAC_PATRIM5   */
#define RAC_PATRIM5_TXPATRIMPCASC_pcbias_m100mv                       (_RAC_PATRIM5_TXPATRIMPCASC_pcbias_m100mv << 20)     /**< Shifted mode pcbias_m100mv for RAC_PATRIM5  */
#define _RAC_PATRIM5_TXPATRIMREGSLICES_SHIFT                          24                                                   /**< Shift value for RAC_TXPATRIMREGSLICES       */
#define _RAC_PATRIM5_TXPATRIMREGSLICES_MASK                           0x3000000UL                                          /**< Bit mask for RAC_TXPATRIMREGSLICES          */
#define _RAC_PATRIM5_TXPATRIMREGSLICES_DEFAULT                        0x00000000UL                                         /**< Mode DEFAULT for RAC_PATRIM5                */
#define _RAC_PATRIM5_TXPATRIMREGSLICES_spare1                         0x00000000UL                                         /**< Mode spare1 for RAC_PATRIM5                 */
#define _RAC_PATRIM5_TXPATRIMREGSLICES_spare2                         0x00000001UL                                         /**< Mode spare2 for RAC_PATRIM5                 */
#define _RAC_PATRIM5_TXPATRIMREGSLICES_spare3                         0x00000002UL                                         /**< Mode spare3 for RAC_PATRIM5                 */
#define _RAC_PATRIM5_TXPATRIMREGSLICES_spare4                         0x00000003UL                                         /**< Mode spare4 for RAC_PATRIM5                 */
#define RAC_PATRIM5_TXPATRIMREGSLICES_DEFAULT                         (_RAC_PATRIM5_TXPATRIMREGSLICES_DEFAULT << 24)       /**< Shifted mode DEFAULT for RAC_PATRIM5        */
#define RAC_PATRIM5_TXPATRIMREGSLICES_spare1                          (_RAC_PATRIM5_TXPATRIMREGSLICES_spare1 << 24)        /**< Shifted mode spare1 for RAC_PATRIM5         */
#define RAC_PATRIM5_TXPATRIMREGSLICES_spare2                          (_RAC_PATRIM5_TXPATRIMREGSLICES_spare2 << 24)        /**< Shifted mode spare2 for RAC_PATRIM5         */
#define RAC_PATRIM5_TXPATRIMREGSLICES_spare3                          (_RAC_PATRIM5_TXPATRIMREGSLICES_spare3 << 24)        /**< Shifted mode spare3 for RAC_PATRIM5         */
#define RAC_PATRIM5_TXPATRIMREGSLICES_spare4                          (_RAC_PATRIM5_TXPATRIMREGSLICES_spare4 << 24)        /**< Shifted mode spare4 for RAC_PATRIM5         */

/* Bit fields for RAC TXPOWER */
#define _RAC_TXPOWER_RESETVALUE                                       0x00000010UL                                   /**< Default value for RAC_TXPOWER               */
#define _RAC_TXPOWER_MASK                                             0x0000003FUL                                   /**< Mask for RAC_TXPOWER                        */
#define _RAC_TXPOWER_TX0DBMPOWER_SHIFT                                0                                              /**< Shift value for RAC_TX0DBMPOWER             */
#define _RAC_TXPOWER_TX0DBMPOWER_MASK                                 0xFUL                                          /**< Bit mask for RAC_TX0DBMPOWER                */
#define _RAC_TXPOWER_TX0DBMPOWER_DEFAULT                              0x00000000UL                                   /**< Mode DEFAULT for RAC_TXPOWER                */
#define _RAC_TXPOWER_TX0DBMPOWER_on_stripe_0                          0x00000000UL                                   /**< Mode on_stripe_0 for RAC_TXPOWER            */
#define _RAC_TXPOWER_TX0DBMPOWER_on_stripe_15                         0x0000000FUL                                   /**< Mode on_stripe_15 for RAC_TXPOWER           */
#define RAC_TXPOWER_TX0DBMPOWER_DEFAULT                               (_RAC_TXPOWER_TX0DBMPOWER_DEFAULT << 0)        /**< Shifted mode DEFAULT for RAC_TXPOWER        */
#define RAC_TXPOWER_TX0DBMPOWER_on_stripe_0                           (_RAC_TXPOWER_TX0DBMPOWER_on_stripe_0 << 0)    /**< Shifted mode on_stripe_0 for RAC_TXPOWER    */
#define RAC_TXPOWER_TX0DBMPOWER_on_stripe_15                          (_RAC_TXPOWER_TX0DBMPOWER_on_stripe_15 << 0)   /**< Shifted mode on_stripe_15 for RAC_TXPOWER   */
#define _RAC_TXPOWER_TX0DBMSELSLICE_SHIFT                             4                                              /**< Shift value for RAC_TX0DBMSELSLICE          */
#define _RAC_TXPOWER_TX0DBMSELSLICE_MASK                              0x30UL                                         /**< Bit mask for RAC_TX0DBMSELSLICE             */
#define _RAC_TXPOWER_TX0DBMSELSLICE_DEFAULT                           0x00000001UL                                   /**< Mode DEFAULT for RAC_TXPOWER                */
#define _RAC_TXPOWER_TX0DBMSELSLICE_on_0_slice                        0x00000000UL                                   /**< Mode on_0_slice for RAC_TXPOWER             */
#define _RAC_TXPOWER_TX0DBMSELSLICE_on_1_slice                        0x00000001UL                                   /**< Mode on_1_slice for RAC_TXPOWER             */
#define _RAC_TXPOWER_TX0DBMSELSLICE_NA                                0x00000002UL                                   /**< Mode NA for RAC_TXPOWER                     */
#define _RAC_TXPOWER_TX0DBMSELSLICE_on_1_slices                       0x00000003UL                                   /**< Mode on_1_slices for RAC_TXPOWER            */
#define RAC_TXPOWER_TX0DBMSELSLICE_DEFAULT                            (_RAC_TXPOWER_TX0DBMSELSLICE_DEFAULT << 4)     /**< Shifted mode DEFAULT for RAC_TXPOWER        */
#define RAC_TXPOWER_TX0DBMSELSLICE_on_0_slice                         (_RAC_TXPOWER_TX0DBMSELSLICE_on_0_slice << 4)  /**< Shifted mode on_0_slice for RAC_TXPOWER     */
#define RAC_TXPOWER_TX0DBMSELSLICE_on_1_slice                         (_RAC_TXPOWER_TX0DBMSELSLICE_on_1_slice << 4)  /**< Shifted mode on_1_slice for RAC_TXPOWER     */
#define RAC_TXPOWER_TX0DBMSELSLICE_NA                                 (_RAC_TXPOWER_TX0DBMSELSLICE_NA << 4)          /**< Shifted mode NA for RAC_TXPOWER             */
#define RAC_TXPOWER_TX0DBMSELSLICE_on_1_slices                        (_RAC_TXPOWER_TX0DBMSELSLICE_on_1_slices << 4) /**< Shifted mode on_1_slices for RAC_TXPOWER    */

/* Bit fields for RAC TXRAMP */
#define _RAC_TXRAMP_RESETVALUE                                        0x00000000UL                          /**< Default value for RAC_TXRAMP                */
#define _RAC_TXRAMP_MASK                                              0x00000001UL                          /**< Mask for RAC_TXRAMP                         */
#define RAC_TXRAMP_PARAMPMODE                                         (0x1UL << 0)                          /**< PARAMPMODE                                  */
#define _RAC_TXRAMP_PARAMPMODE_SHIFT                                  0                                     /**< Shift value for RAC_PARAMPMODE              */
#define _RAC_TXRAMP_PARAMPMODE_MASK                                   0x1UL                                 /**< Bit mask for RAC_PARAMPMODE                 */
#define _RAC_TXRAMP_PARAMPMODE_DEFAULT                                0x00000000UL                          /**< Mode DEFAULT for RAC_TXRAMP                 */
#define RAC_TXRAMP_PARAMPMODE_DEFAULT                                 (_RAC_TXRAMP_PARAMPMODE_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_TXRAMP         */

/* Bit fields for RAC PGATRIM */
#define _RAC_PGATRIM_RESETVALUE                                       0x00000B15UL                                  /**< Default value for RAC_PGATRIM               */
#define _RAC_PGATRIM_MASK                                             0x00000FDFUL                                  /**< Mask for RAC_PGATRIM                        */
#define _RAC_PGATRIM_PGACTUNE_SHIFT                                   0                                             /**< Shift value for RAC_PGACTUNE                */
#define _RAC_PGATRIM_PGACTUNE_MASK                                    0x1FUL                                        /**< Bit mask for RAC_PGACTUNE                   */
#define _RAC_PGATRIM_PGACTUNE_DEFAULT                                 0x00000015UL                                  /**< Mode DEFAULT for RAC_PGATRIM                */
#define RAC_PGATRIM_PGACTUNE_DEFAULT                                  (_RAC_PGATRIM_PGACTUNE_DEFAULT << 0)          /**< Shifted mode DEFAULT for RAC_PGATRIM        */
#define _RAC_PGATRIM_PGAVCMOUTTRIM_SHIFT                              6                                             /**< Shift value for RAC_PGAVCMOUTTRIM           */
#define _RAC_PGATRIM_PGAVCMOUTTRIM_MASK                               0x1C0UL                                       /**< Bit mask for RAC_PGAVCMOUTTRIM              */
#define _RAC_PGATRIM_PGAVCMOUTTRIM_DEFAULT                            0x00000004UL                                  /**< Mode DEFAULT for RAC_PGATRIM                */
#define _RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_475                        0x00000000UL                                  /**< Mode vcm_out_475 for RAC_PGATRIM            */
#define _RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_500                        0x00000001UL                                  /**< Mode vcm_out_500 for RAC_PGATRIM            */
#define _RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_525                        0x00000002UL                                  /**< Mode vcm_out_525 for RAC_PGATRIM            */
#define _RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_550                        0x00000003UL                                  /**< Mode vcm_out_550 for RAC_PGATRIM            */
#define _RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_575                        0x00000004UL                                  /**< Mode vcm_out_575 for RAC_PGATRIM            */
#define _RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_600                        0x00000005UL                                  /**< Mode vcm_out_600 for RAC_PGATRIM            */
#define _RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_625                        0x00000006UL                                  /**< Mode vcm_out_625 for RAC_PGATRIM            */
#define _RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_650                        0x00000007UL                                  /**< Mode vcm_out_650 for RAC_PGATRIM            */
#define RAC_PGATRIM_PGAVCMOUTTRIM_DEFAULT                             (_RAC_PGATRIM_PGAVCMOUTTRIM_DEFAULT << 6)     /**< Shifted mode DEFAULT for RAC_PGATRIM        */
#define RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_475                         (_RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_475 << 6) /**< Shifted mode vcm_out_475 for RAC_PGATRIM    */
#define RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_500                         (_RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_500 << 6) /**< Shifted mode vcm_out_500 for RAC_PGATRIM    */
#define RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_525                         (_RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_525 << 6) /**< Shifted mode vcm_out_525 for RAC_PGATRIM    */
#define RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_550                         (_RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_550 << 6) /**< Shifted mode vcm_out_550 for RAC_PGATRIM    */
#define RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_575                         (_RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_575 << 6) /**< Shifted mode vcm_out_575 for RAC_PGATRIM    */
#define RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_600                         (_RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_600 << 6) /**< Shifted mode vcm_out_600 for RAC_PGATRIM    */
#define RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_625                         (_RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_625 << 6) /**< Shifted mode vcm_out_625 for RAC_PGATRIM    */
#define RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_650                         (_RAC_PGATRIM_PGAVCMOUTTRIM_vcm_out_650 << 6) /**< Shifted mode vcm_out_650 for RAC_PGATRIM    */
#define _RAC_PGATRIM_PGAVLDOTRIM_SHIFT                                9                                             /**< Shift value for RAC_PGAVLDOTRIM             */
#define _RAC_PGATRIM_PGAVLDOTRIM_MASK                                 0xE00UL                                       /**< Bit mask for RAC_PGAVLDOTRIM                */
#define _RAC_PGATRIM_PGAVLDOTRIM_DEFAULT                              0x00000005UL                                  /**< Mode DEFAULT for RAC_PGATRIM                */
#define _RAC_PGATRIM_PGAVLDOTRIM_vdda_1225                            0x00000000UL                                  /**< Mode vdda_1225 for RAC_PGATRIM              */
#define _RAC_PGATRIM_PGAVLDOTRIM_vdda_1250                            0x00000001UL                                  /**< Mode vdda_1250 for RAC_PGATRIM              */
#define _RAC_PGATRIM_PGAVLDOTRIM_vdda_1275                            0x00000002UL                                  /**< Mode vdda_1275 for RAC_PGATRIM              */
#define _RAC_PGATRIM_PGAVLDOTRIM_vdda_1300                            0x00000003UL                                  /**< Mode vdda_1300 for RAC_PGATRIM              */
#define _RAC_PGATRIM_PGAVLDOTRIM_vdda_1325                            0x00000004UL                                  /**< Mode vdda_1325 for RAC_PGATRIM              */
#define _RAC_PGATRIM_PGAVLDOTRIM_vdda_1350                            0x00000005UL                                  /**< Mode vdda_1350 for RAC_PGATRIM              */
#define _RAC_PGATRIM_PGAVLDOTRIM_vdda_1375                            0x00000006UL                                  /**< Mode vdda_1375 for RAC_PGATRIM              */
#define _RAC_PGATRIM_PGAVLDOTRIM_vdda_1400                            0x00000007UL                                  /**< Mode vdda_1400 for RAC_PGATRIM              */
#define RAC_PGATRIM_PGAVLDOTRIM_DEFAULT                               (_RAC_PGATRIM_PGAVLDOTRIM_DEFAULT << 9)       /**< Shifted mode DEFAULT for RAC_PGATRIM        */
#define RAC_PGATRIM_PGAVLDOTRIM_vdda_1225                             (_RAC_PGATRIM_PGAVLDOTRIM_vdda_1225 << 9)     /**< Shifted mode vdda_1225 for RAC_PGATRIM      */
#define RAC_PGATRIM_PGAVLDOTRIM_vdda_1250                             (_RAC_PGATRIM_PGAVLDOTRIM_vdda_1250 << 9)     /**< Shifted mode vdda_1250 for RAC_PGATRIM      */
#define RAC_PGATRIM_PGAVLDOTRIM_vdda_1275                             (_RAC_PGATRIM_PGAVLDOTRIM_vdda_1275 << 9)     /**< Shifted mode vdda_1275 for RAC_PGATRIM      */
#define RAC_PGATRIM_PGAVLDOTRIM_vdda_1300                             (_RAC_PGATRIM_PGAVLDOTRIM_vdda_1300 << 9)     /**< Shifted mode vdda_1300 for RAC_PGATRIM      */
#define RAC_PGATRIM_PGAVLDOTRIM_vdda_1325                             (_RAC_PGATRIM_PGAVLDOTRIM_vdda_1325 << 9)     /**< Shifted mode vdda_1325 for RAC_PGATRIM      */
#define RAC_PGATRIM_PGAVLDOTRIM_vdda_1350                             (_RAC_PGATRIM_PGAVLDOTRIM_vdda_1350 << 9)     /**< Shifted mode vdda_1350 for RAC_PGATRIM      */
#define RAC_PGATRIM_PGAVLDOTRIM_vdda_1375                             (_RAC_PGATRIM_PGAVLDOTRIM_vdda_1375 << 9)     /**< Shifted mode vdda_1375 for RAC_PGATRIM      */
#define RAC_PGATRIM_PGAVLDOTRIM_vdda_1400                             (_RAC_PGATRIM_PGAVLDOTRIM_vdda_1400 << 9)     /**< Shifted mode vdda_1400 for RAC_PGATRIM      */

/* Bit fields for RAC PGACAL */
#define _RAC_PGACAL_RESETVALUE                                        0x00002020UL                          /**< Default value for RAC_PGACAL                */
#define _RAC_PGACAL_MASK                                              0x00003F3FUL                          /**< Mask for RAC_PGACAL                         */
#define _RAC_PGACAL_PGAOFFCALI_SHIFT                                  0                                     /**< Shift value for RAC_PGAOFFCALI              */
#define _RAC_PGACAL_PGAOFFCALI_MASK                                   0x3FUL                                /**< Bit mask for RAC_PGAOFFCALI                 */
#define _RAC_PGACAL_PGAOFFCALI_DEFAULT                                0x00000020UL                          /**< Mode DEFAULT for RAC_PGACAL                 */
#define RAC_PGACAL_PGAOFFCALI_DEFAULT                                 (_RAC_PGACAL_PGAOFFCALI_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_PGACAL         */
#define _RAC_PGACAL_PGAOFFCALQ_SHIFT                                  8                                     /**< Shift value for RAC_PGAOFFCALQ              */
#define _RAC_PGACAL_PGAOFFCALQ_MASK                                   0x3F00UL                              /**< Bit mask for RAC_PGAOFFCALQ                 */
#define _RAC_PGACAL_PGAOFFCALQ_DEFAULT                                0x00000020UL                          /**< Mode DEFAULT for RAC_PGACAL                 */
#define RAC_PGACAL_PGAOFFCALQ_DEFAULT                                 (_RAC_PGACAL_PGAOFFCALQ_DEFAULT << 8) /**< Shifted mode DEFAULT for RAC_PGACAL         */

/* Bit fields for RAC PGACTRL */
#define _RAC_PGACTRL_RESETVALUE                                       0x00008001UL                                        /**< Default value for RAC_PGACTRL               */
#define _RAC_PGACTRL_MASK                                             0x01FFEFFFUL                                        /**< Mask for RAC_PGACTRL                        */
#define _RAC_PGACTRL_PGABWMODE_SHIFT                                  0                                                   /**< Shift value for RAC_PGABWMODE               */
#define _RAC_PGACTRL_PGABWMODE_MASK                                   0xFUL                                               /**< Bit mask for RAC_PGABWMODE                  */
#define _RAC_PGACTRL_PGABWMODE_DEFAULT                                0x00000001UL                                        /**< Mode DEFAULT for RAC_PGACTRL                */
#define RAC_PGACTRL_PGABWMODE_DEFAULT                                 (_RAC_PGACTRL_PGABWMODE_DEFAULT << 0)               /**< Shifted mode DEFAULT for RAC_PGACTRL        */
#define RAC_PGACTRL_PGAENGHZ                                          (0x1UL << 4)                                        /**< PGAENGHZ                                    */
#define _RAC_PGACTRL_PGAENGHZ_SHIFT                                   4                                                   /**< Shift value for RAC_PGAENGHZ                */
#define _RAC_PGACTRL_PGAENGHZ_MASK                                    0x10UL                                              /**< Bit mask for RAC_PGAENGHZ                   */
#define _RAC_PGACTRL_PGAENGHZ_DEFAULT                                 0x00000000UL                                        /**< Mode DEFAULT for RAC_PGACTRL                */
#define _RAC_PGACTRL_PGAENGHZ_ghz_disable                             0x00000000UL                                        /**< Mode ghz_disable for RAC_PGACTRL            */
#define _RAC_PGACTRL_PGAENGHZ_ghz_enable                              0x00000001UL                                        /**< Mode ghz_enable for RAC_PGACTRL             */
#define RAC_PGACTRL_PGAENGHZ_DEFAULT                                  (_RAC_PGACTRL_PGAENGHZ_DEFAULT << 4)                /**< Shifted mode DEFAULT for RAC_PGACTRL        */
#define RAC_PGACTRL_PGAENGHZ_ghz_disable                              (_RAC_PGACTRL_PGAENGHZ_ghz_disable << 4)            /**< Shifted mode ghz_disable for RAC_PGACTRL    */
#define RAC_PGACTRL_PGAENGHZ_ghz_enable                               (_RAC_PGACTRL_PGAENGHZ_ghz_enable << 4)             /**< Shifted mode ghz_enable for RAC_PGACTRL     */
#define RAC_PGACTRL_PGAENBIAS                                         (0x1UL << 5)                                        /**< PGAENBIAS                                   */
#define _RAC_PGACTRL_PGAENBIAS_SHIFT                                  5                                                   /**< Shift value for RAC_PGAENBIAS               */
#define _RAC_PGACTRL_PGAENBIAS_MASK                                   0x20UL                                              /**< Bit mask for RAC_PGAENBIAS                  */
#define _RAC_PGACTRL_PGAENBIAS_DEFAULT                                0x00000000UL                                        /**< Mode DEFAULT for RAC_PGACTRL                */
#define _RAC_PGACTRL_PGAENBIAS_bias_disable                           0x00000000UL                                        /**< Mode bias_disable for RAC_PGACTRL           */
#define _RAC_PGACTRL_PGAENBIAS_bias_enable                            0x00000001UL                                        /**< Mode bias_enable for RAC_PGACTRL            */
#define RAC_PGACTRL_PGAENBIAS_DEFAULT                                 (_RAC_PGACTRL_PGAENBIAS_DEFAULT << 5)               /**< Shifted mode DEFAULT for RAC_PGACTRL        */
#define RAC_PGACTRL_PGAENBIAS_bias_disable                            (_RAC_PGACTRL_PGAENBIAS_bias_disable << 5)          /**< Shifted mode bias_disable for RAC_PGACTRL   */
#define RAC_PGACTRL_PGAENBIAS_bias_enable                             (_RAC_PGACTRL_PGAENBIAS_bias_enable << 5)           /**< Shifted mode bias_enable for RAC_PGACTRL    */
#define RAC_PGACTRL_PGAENLATCHI                                       (0x1UL << 6)                                        /**< PGAENLATCHI                                 */
#define _RAC_PGACTRL_PGAENLATCHI_SHIFT                                6                                                   /**< Shift value for RAC_PGAENLATCHI             */
#define _RAC_PGACTRL_PGAENLATCHI_MASK                                 0x40UL                                              /**< Bit mask for RAC_PGAENLATCHI                */
#define _RAC_PGACTRL_PGAENLATCHI_DEFAULT                              0x00000000UL                                        /**< Mode DEFAULT for RAC_PGACTRL                */
#define _RAC_PGACTRL_PGAENLATCHI_pkd_latch_i_disable                  0x00000000UL                                        /**< Mode pkd_latch_i_disable for RAC_PGACTRL    */
#define _RAC_PGACTRL_PGAENLATCHI_pkd_latch_i_enable                   0x00000001UL                                        /**< Mode pkd_latch_i_enable for RAC_PGACTRL     */
#define RAC_PGACTRL_PGAENLATCHI_DEFAULT                               (_RAC_PGACTRL_PGAENLATCHI_DEFAULT << 6)             /**< Shifted mode DEFAULT for RAC_PGACTRL        */
#define RAC_PGACTRL_PGAENLATCHI_pkd_latch_i_disable                   (_RAC_PGACTRL_PGAENLATCHI_pkd_latch_i_disable << 6) /**< Shifted mode pkd_latch_i_disable for RAC_PGACTRL*/
#define RAC_PGACTRL_PGAENLATCHI_pkd_latch_i_enable                    (_RAC_PGACTRL_PGAENLATCHI_pkd_latch_i_enable << 6)  /**< Shifted mode pkd_latch_i_enable for RAC_PGACTRL*/
#define RAC_PGACTRL_PGAENLATCHQ                                       (0x1UL << 7)                                        /**< PGAENLATCHQ                                 */
#define _RAC_PGACTRL_PGAENLATCHQ_SHIFT                                7                                                   /**< Shift value for RAC_PGAENLATCHQ             */
#define _RAC_PGACTRL_PGAENLATCHQ_MASK                                 0x80UL                                              /**< Bit mask for RAC_PGAENLATCHQ                */
#define _RAC_PGACTRL_PGAENLATCHQ_DEFAULT                              0x00000000UL                                        /**< Mode DEFAULT for RAC_PGACTRL                */
#define _RAC_PGACTRL_PGAENLATCHQ_pkd_latch_q_disable                  0x00000000UL                                        /**< Mode pkd_latch_q_disable for RAC_PGACTRL    */
#define _RAC_PGACTRL_PGAENLATCHQ_pkd_latch_q_enable                   0x00000001UL                                        /**< Mode pkd_latch_q_enable for RAC_PGACTRL     */
#define RAC_PGACTRL_PGAENLATCHQ_DEFAULT                               (_RAC_PGACTRL_PGAENLATCHQ_DEFAULT << 7)             /**< Shifted mode DEFAULT for RAC_PGACTRL        */
#define RAC_PGACTRL_PGAENLATCHQ_pkd_latch_q_disable                   (_RAC_PGACTRL_PGAENLATCHQ_pkd_latch_q_disable << 7) /**< Shifted mode pkd_latch_q_disable for RAC_PGACTRL*/
#define RAC_PGACTRL_PGAENLATCHQ_pkd_latch_q_enable                    (_RAC_PGACTRL_PGAENLATCHQ_pkd_latch_q_enable << 7)  /**< Shifted mode pkd_latch_q_enable for RAC_PGACTRL*/
#define RAC_PGACTRL_PGAENLDOLOAD                                      (0x1UL << 8)                                        /**< PGAENLDOLOAD                                */
#define _RAC_PGACTRL_PGAENLDOLOAD_SHIFT                               8                                                   /**< Shift value for RAC_PGAENLDOLOAD            */
#define _RAC_PGACTRL_PGAENLDOLOAD_MASK                                0x100UL                                             /**< Bit mask for RAC_PGAENLDOLOAD               */
#define _RAC_PGACTRL_PGAENLDOLOAD_DEFAULT                             0x00000000UL                                        /**< Mode DEFAULT for RAC_PGACTRL                */
#define _RAC_PGACTRL_PGAENLDOLOAD_disable_ldo_load                    0x00000000UL                                        /**< Mode disable_ldo_load for RAC_PGACTRL       */
#define _RAC_PGACTRL_PGAENLDOLOAD_enable_ldo_load                     0x00000001UL                                        /**< Mode enable_ldo_load for RAC_PGACTRL        */
#define RAC_PGACTRL_PGAENLDOLOAD_DEFAULT                              (_RAC_PGACTRL_PGAENLDOLOAD_DEFAULT << 8)            /**< Shifted mode DEFAULT for RAC_PGACTRL        */
#define RAC_PGACTRL_PGAENLDOLOAD_disable_ldo_load                     (_RAC_PGACTRL_PGAENLDOLOAD_disable_ldo_load << 8)   /**< Shifted mode disable_ldo_load for RAC_PGACTRL*/
#define RAC_PGACTRL_PGAENLDOLOAD_enable_ldo_load                      (_RAC_PGACTRL_PGAENLDOLOAD_enable_ldo_load << 8)    /**< Shifted mode enable_ldo_load for RAC_PGACTRL*/
#define RAC_PGACTRL_PGAENPGAI                                         (0x1UL << 9)                                        /**< PGAENPGAI                                   */
#define _RAC_PGACTRL_PGAENPGAI_SHIFT                                  9                                                   /**< Shift value for RAC_PGAENPGAI               */
#define _RAC_PGACTRL_PGAENPGAI_MASK                                   0x200UL                                             /**< Bit mask for RAC_PGAENPGAI                  */
#define _RAC_PGACTRL_PGAENPGAI_DEFAULT                                0x00000000UL                                        /**< Mode DEFAULT for RAC_PGACTRL                */
#define _RAC_PGACTRL_PGAENPGAI_pgai_disable                           0x00000000UL                                        /**< Mode pgai_disable for RAC_PGACTRL           */
#define _RAC_PGACTRL_PGAENPGAI_pgai_enable                            0x00000001UL                                        /**< Mode pgai_enable for RAC_PGACTRL            */
#define RAC_PGACTRL_PGAENPGAI_DEFAULT                                 (_RAC_PGACTRL_PGAENPGAI_DEFAULT << 9)               /**< Shifted mode DEFAULT for RAC_PGACTRL        */
#define RAC_PGACTRL_PGAENPGAI_pgai_disable                            (_RAC_PGACTRL_PGAENPGAI_pgai_disable << 9)          /**< Shifted mode pgai_disable for RAC_PGACTRL   */
#define RAC_PGACTRL_PGAENPGAI_pgai_enable                             (_RAC_PGACTRL_PGAENPGAI_pgai_enable << 9)           /**< Shifted mode pgai_enable for RAC_PGACTRL    */
#define RAC_PGACTRL_PGAENPGAQ                                         (0x1UL << 10)                                       /**< PGAENPGAQ                                   */
#define _RAC_PGACTRL_PGAENPGAQ_SHIFT                                  10                                                  /**< Shift value for RAC_PGAENPGAQ               */
#define _RAC_PGACTRL_PGAENPGAQ_MASK                                   0x400UL                                             /**< Bit mask for RAC_PGAENPGAQ                  */
#define _RAC_PGACTRL_PGAENPGAQ_DEFAULT                                0x00000000UL                                        /**< Mode DEFAULT for RAC_PGACTRL                */
#define _RAC_PGACTRL_PGAENPGAQ_pgaq_disable                           0x00000000UL                                        /**< Mode pgaq_disable for RAC_PGACTRL           */
#define _RAC_PGACTRL_PGAENPGAQ_pgaq_enable                            0x00000001UL                                        /**< Mode pgaq_enable for RAC_PGACTRL            */
#define RAC_PGACTRL_PGAENPGAQ_DEFAULT                                 (_RAC_PGACTRL_PGAENPGAQ_DEFAULT << 10)              /**< Shifted mode DEFAULT for RAC_PGACTRL        */
#define RAC_PGACTRL_PGAENPGAQ_pgaq_disable                            (_RAC_PGACTRL_PGAENPGAQ_pgaq_disable << 10)         /**< Shifted mode pgaq_disable for RAC_PGACTRL   */
#define RAC_PGACTRL_PGAENPGAQ_pgaq_enable                             (_RAC_PGACTRL_PGAENPGAQ_pgaq_enable << 10)          /**< Shifted mode pgaq_enable for RAC_PGACTRL    */
#define RAC_PGACTRL_PGAENPKD                                          (0x1UL << 11)                                       /**< PGAENPKD                                    */
#define _RAC_PGACTRL_PGAENPKD_SHIFT                                   11                                                  /**< Shift value for RAC_PGAENPKD                */
#define _RAC_PGACTRL_PGAENPKD_MASK                                    0x800UL                                             /**< Bit mask for RAC_PGAENPKD                   */
#define _RAC_PGACTRL_PGAENPKD_DEFAULT                                 0x00000000UL                                        /**< Mode DEFAULT for RAC_PGACTRL                */
#define _RAC_PGACTRL_PGAENPKD_pkd_disable                             0x00000000UL                                        /**< Mode pkd_disable for RAC_PGACTRL            */
#define _RAC_PGACTRL_PGAENPKD_pkd_enable                              0x00000001UL                                        /**< Mode pkd_enable for RAC_PGACTRL             */
#define RAC_PGACTRL_PGAENPKD_DEFAULT                                  (_RAC_PGACTRL_PGAENPKD_DEFAULT << 11)               /**< Shifted mode DEFAULT for RAC_PGACTRL        */
#define RAC_PGACTRL_PGAENPKD_pkd_disable                              (_RAC_PGACTRL_PGAENPKD_pkd_disable << 11)           /**< Shifted mode pkd_disable for RAC_PGACTRL    */
#define RAC_PGACTRL_PGAENPKD_pkd_enable                               (_RAC_PGACTRL_PGAENPKD_pkd_enable << 11)            /**< Shifted mode pkd_enable for RAC_PGACTRL     */
#define _RAC_PGACTRL_PGAPOWERMODE_SHIFT                               14                                                  /**< Shift value for RAC_PGAPOWERMODE            */
#define _RAC_PGACTRL_PGAPOWERMODE_MASK                                0x1C000UL                                           /**< Bit mask for RAC_PGAPOWERMODE               */
#define _RAC_PGACTRL_PGAPOWERMODE_DEFAULT                             0x00000002UL                                        /**< Mode DEFAULT for RAC_PGACTRL                */
#define _RAC_PGACTRL_PGAPOWERMODE_pm0_3u0                             0x00000000UL                                        /**< Mode pm0_3u0 for RAC_PGACTRL                */
#define _RAC_PGACTRL_PGAPOWERMODE_pm1_3u5                             0x00000001UL                                        /**< Mode pm1_3u5 for RAC_PGACTRL                */
#define _RAC_PGACTRL_PGAPOWERMODE_pm2_4u0                             0x00000002UL                                        /**< Mode pm2_4u0 for RAC_PGACTRL                */
#define _RAC_PGACTRL_PGAPOWERMODE_pm3_4u5                             0x00000003UL                                        /**< Mode pm3_4u5 for RAC_PGACTRL                */
#define _RAC_PGACTRL_PGAPOWERMODE_pm4_4u0                             0x00000004UL                                        /**< Mode pm4_4u0 for RAC_PGACTRL                */
#define _RAC_PGACTRL_PGAPOWERMODE_pm5_4u5                             0x00000005UL                                        /**< Mode pm5_4u5 for RAC_PGACTRL                */
#define _RAC_PGACTRL_PGAPOWERMODE_pm6_5u0                             0x00000006UL                                        /**< Mode pm6_5u0 for RAC_PGACTRL                */
#define _RAC_PGACTRL_PGAPOWERMODE_pm7_5u5                             0x00000007UL                                        /**< Mode pm7_5u5 for RAC_PGACTRL                */
#define RAC_PGACTRL_PGAPOWERMODE_DEFAULT                              (_RAC_PGACTRL_PGAPOWERMODE_DEFAULT << 14)           /**< Shifted mode DEFAULT for RAC_PGACTRL        */
#define RAC_PGACTRL_PGAPOWERMODE_pm0_3u0                              (_RAC_PGACTRL_PGAPOWERMODE_pm0_3u0 << 14)           /**< Shifted mode pm0_3u0 for RAC_PGACTRL        */
#define RAC_PGACTRL_PGAPOWERMODE_pm1_3u5                              (_RAC_PGACTRL_PGAPOWERMODE_pm1_3u5 << 14)           /**< Shifted mode pm1_3u5 for RAC_PGACTRL        */
#define RAC_PGACTRL_PGAPOWERMODE_pm2_4u0                              (_RAC_PGACTRL_PGAPOWERMODE_pm2_4u0 << 14)           /**< Shifted mode pm2_4u0 for RAC_PGACTRL        */
#define RAC_PGACTRL_PGAPOWERMODE_pm3_4u5                              (_RAC_PGACTRL_PGAPOWERMODE_pm3_4u5 << 14)           /**< Shifted mode pm3_4u5 for RAC_PGACTRL        */
#define RAC_PGACTRL_PGAPOWERMODE_pm4_4u0                              (_RAC_PGACTRL_PGAPOWERMODE_pm4_4u0 << 14)           /**< Shifted mode pm4_4u0 for RAC_PGACTRL        */
#define RAC_PGACTRL_PGAPOWERMODE_pm5_4u5                              (_RAC_PGACTRL_PGAPOWERMODE_pm5_4u5 << 14)           /**< Shifted mode pm5_4u5 for RAC_PGACTRL        */
#define RAC_PGACTRL_PGAPOWERMODE_pm6_5u0                              (_RAC_PGACTRL_PGAPOWERMODE_pm6_5u0 << 14)           /**< Shifted mode pm6_5u0 for RAC_PGACTRL        */
#define RAC_PGACTRL_PGAPOWERMODE_pm7_5u5                              (_RAC_PGACTRL_PGAPOWERMODE_pm7_5u5 << 14)           /**< Shifted mode pm7_5u5 for RAC_PGACTRL        */
#define _RAC_PGACTRL_PGATHRPKDLOSEL_SHIFT                             17                                                  /**< Shift value for RAC_PGATHRPKDLOSEL          */
#define _RAC_PGACTRL_PGATHRPKDLOSEL_MASK                              0x1E0000UL                                          /**< Bit mask for RAC_PGATHRPKDLOSEL             */
#define _RAC_PGACTRL_PGATHRPKDLOSEL_DEFAULT                           0x00000000UL                                        /**< Mode DEFAULT for RAC_PGACTRL                */
#define _RAC_PGACTRL_PGATHRPKDLOSEL_vref50mv                          0x00000000UL                                        /**< Mode vref50mv for RAC_PGACTRL               */
#define _RAC_PGACTRL_PGATHRPKDLOSEL_vref75mv                          0x00000001UL                                        /**< Mode vref75mv for RAC_PGACTRL               */
#define _RAC_PGACTRL_PGATHRPKDLOSEL_vref100mv                         0x00000002UL                                        /**< Mode vref100mv for RAC_PGACTRL              */
#define _RAC_PGACTRL_PGATHRPKDLOSEL_vref125mv                         0x00000003UL                                        /**< Mode vref125mv for RAC_PGACTRL              */
#define _RAC_PGACTRL_PGATHRPKDLOSEL_vref150mv                         0x00000004UL                                        /**< Mode vref150mv for RAC_PGACTRL              */
#define _RAC_PGACTRL_PGATHRPKDLOSEL_vref175mv                         0x00000005UL                                        /**< Mode vref175mv for RAC_PGACTRL              */
#define _RAC_PGACTRL_PGATHRPKDLOSEL_vref200mv                         0x00000006UL                                        /**< Mode vref200mv for RAC_PGACTRL              */
#define _RAC_PGACTRL_PGATHRPKDLOSEL_vref225mv                         0x00000007UL                                        /**< Mode vref225mv for RAC_PGACTRL              */
#define _RAC_PGACTRL_PGATHRPKDLOSEL_vref250mv                         0x00000008UL                                        /**< Mode vref250mv for RAC_PGACTRL              */
#define _RAC_PGACTRL_PGATHRPKDLOSEL_vref275mv                         0x00000009UL                                        /**< Mode vref275mv for RAC_PGACTRL              */
#define _RAC_PGACTRL_PGATHRPKDLOSEL_vref300mv                         0x0000000AUL                                        /**< Mode vref300mv for RAC_PGACTRL              */
#define RAC_PGACTRL_PGATHRPKDLOSEL_DEFAULT                            (_RAC_PGACTRL_PGATHRPKDLOSEL_DEFAULT << 17)         /**< Shifted mode DEFAULT for RAC_PGACTRL        */
#define RAC_PGACTRL_PGATHRPKDLOSEL_vref50mv                           (_RAC_PGACTRL_PGATHRPKDLOSEL_vref50mv << 17)        /**< Shifted mode vref50mv for RAC_PGACTRL       */
#define RAC_PGACTRL_PGATHRPKDLOSEL_vref75mv                           (_RAC_PGACTRL_PGATHRPKDLOSEL_vref75mv << 17)        /**< Shifted mode vref75mv for RAC_PGACTRL       */
#define RAC_PGACTRL_PGATHRPKDLOSEL_vref100mv                          (_RAC_PGACTRL_PGATHRPKDLOSEL_vref100mv << 17)       /**< Shifted mode vref100mv for RAC_PGACTRL      */
#define RAC_PGACTRL_PGATHRPKDLOSEL_vref125mv                          (_RAC_PGACTRL_PGATHRPKDLOSEL_vref125mv << 17)       /**< Shifted mode vref125mv for RAC_PGACTRL      */
#define RAC_PGACTRL_PGATHRPKDLOSEL_vref150mv                          (_RAC_PGACTRL_PGATHRPKDLOSEL_vref150mv << 17)       /**< Shifted mode vref150mv for RAC_PGACTRL      */
#define RAC_PGACTRL_PGATHRPKDLOSEL_vref175mv                          (_RAC_PGACTRL_PGATHRPKDLOSEL_vref175mv << 17)       /**< Shifted mode vref175mv for RAC_PGACTRL      */
#define RAC_PGACTRL_PGATHRPKDLOSEL_vref200mv                          (_RAC_PGACTRL_PGATHRPKDLOSEL_vref200mv << 17)       /**< Shifted mode vref200mv for RAC_PGACTRL      */
#define RAC_PGACTRL_PGATHRPKDLOSEL_vref225mv                          (_RAC_PGACTRL_PGATHRPKDLOSEL_vref225mv << 17)       /**< Shifted mode vref225mv for RAC_PGACTRL      */
#define RAC_PGACTRL_PGATHRPKDLOSEL_vref250mv                          (_RAC_PGACTRL_PGATHRPKDLOSEL_vref250mv << 17)       /**< Shifted mode vref250mv for RAC_PGACTRL      */
#define RAC_PGACTRL_PGATHRPKDLOSEL_vref275mv                          (_RAC_PGACTRL_PGATHRPKDLOSEL_vref275mv << 17)       /**< Shifted mode vref275mv for RAC_PGACTRL      */
#define RAC_PGACTRL_PGATHRPKDLOSEL_vref300mv                          (_RAC_PGACTRL_PGATHRPKDLOSEL_vref300mv << 17)       /**< Shifted mode vref300mv for RAC_PGACTRL      */
#define _RAC_PGACTRL_PGATHRPKDHISEL_SHIFT                             21                                                  /**< Shift value for RAC_PGATHRPKDHISEL          */
#define _RAC_PGACTRL_PGATHRPKDHISEL_MASK                              0x1E00000UL                                         /**< Bit mask for RAC_PGATHRPKDHISEL             */
#define _RAC_PGACTRL_PGATHRPKDHISEL_DEFAULT                           0x00000000UL                                        /**< Mode DEFAULT for RAC_PGACTRL                */
#define _RAC_PGACTRL_PGATHRPKDHISEL_vref50mv                          0x00000000UL                                        /**< Mode vref50mv for RAC_PGACTRL               */
#define _RAC_PGACTRL_PGATHRPKDHISEL_vref75mv                          0x00000001UL                                        /**< Mode vref75mv for RAC_PGACTRL               */
#define _RAC_PGACTRL_PGATHRPKDHISEL_vref100mv                         0x00000002UL                                        /**< Mode vref100mv for RAC_PGACTRL              */
#define _RAC_PGACTRL_PGATHRPKDHISEL_vref125mv                         0x00000003UL                                        /**< Mode vref125mv for RAC_PGACTRL              */
#define _RAC_PGACTRL_PGATHRPKDHISEL_verf150mv                         0x00000004UL                                        /**< Mode verf150mv for RAC_PGACTRL              */
#define _RAC_PGACTRL_PGATHRPKDHISEL_vref175mv                         0x00000005UL                                        /**< Mode vref175mv for RAC_PGACTRL              */
#define _RAC_PGACTRL_PGATHRPKDHISEL_vref200mv                         0x00000006UL                                        /**< Mode vref200mv for RAC_PGACTRL              */
#define _RAC_PGACTRL_PGATHRPKDHISEL_vref225mv                         0x00000007UL                                        /**< Mode vref225mv for RAC_PGACTRL              */
#define _RAC_PGACTRL_PGATHRPKDHISEL_vref250mv                         0x00000008UL                                        /**< Mode vref250mv for RAC_PGACTRL              */
#define _RAC_PGACTRL_PGATHRPKDHISEL_vref275mv                         0x00000009UL                                        /**< Mode vref275mv for RAC_PGACTRL              */
#define _RAC_PGACTRL_PGATHRPKDHISEL_vref300mv                         0x0000000AUL                                        /**< Mode vref300mv for RAC_PGACTRL              */
#define RAC_PGACTRL_PGATHRPKDHISEL_DEFAULT                            (_RAC_PGACTRL_PGATHRPKDHISEL_DEFAULT << 21)         /**< Shifted mode DEFAULT for RAC_PGACTRL        */
#define RAC_PGACTRL_PGATHRPKDHISEL_vref50mv                           (_RAC_PGACTRL_PGATHRPKDHISEL_vref50mv << 21)        /**< Shifted mode vref50mv for RAC_PGACTRL       */
#define RAC_PGACTRL_PGATHRPKDHISEL_vref75mv                           (_RAC_PGACTRL_PGATHRPKDHISEL_vref75mv << 21)        /**< Shifted mode vref75mv for RAC_PGACTRL       */
#define RAC_PGACTRL_PGATHRPKDHISEL_vref100mv                          (_RAC_PGACTRL_PGATHRPKDHISEL_vref100mv << 21)       /**< Shifted mode vref100mv for RAC_PGACTRL      */
#define RAC_PGACTRL_PGATHRPKDHISEL_vref125mv                          (_RAC_PGACTRL_PGATHRPKDHISEL_vref125mv << 21)       /**< Shifted mode vref125mv for RAC_PGACTRL      */
#define RAC_PGACTRL_PGATHRPKDHISEL_verf150mv                          (_RAC_PGACTRL_PGATHRPKDHISEL_verf150mv << 21)       /**< Shifted mode verf150mv for RAC_PGACTRL      */
#define RAC_PGACTRL_PGATHRPKDHISEL_vref175mv                          (_RAC_PGACTRL_PGATHRPKDHISEL_vref175mv << 21)       /**< Shifted mode vref175mv for RAC_PGACTRL      */
#define RAC_PGACTRL_PGATHRPKDHISEL_vref200mv                          (_RAC_PGACTRL_PGATHRPKDHISEL_vref200mv << 21)       /**< Shifted mode vref200mv for RAC_PGACTRL      */
#define RAC_PGACTRL_PGATHRPKDHISEL_vref225mv                          (_RAC_PGACTRL_PGATHRPKDHISEL_vref225mv << 21)       /**< Shifted mode vref225mv for RAC_PGACTRL      */
#define RAC_PGACTRL_PGATHRPKDHISEL_vref250mv                          (_RAC_PGACTRL_PGATHRPKDHISEL_vref250mv << 21)       /**< Shifted mode vref250mv for RAC_PGACTRL      */
#define RAC_PGACTRL_PGATHRPKDHISEL_vref275mv                          (_RAC_PGACTRL_PGATHRPKDHISEL_vref275mv << 21)       /**< Shifted mode vref275mv for RAC_PGACTRL      */
#define RAC_PGACTRL_PGATHRPKDHISEL_vref300mv                          (_RAC_PGACTRL_PGATHRPKDHISEL_vref300mv << 21)       /**< Shifted mode vref300mv for RAC_PGACTRL      */

/* Bit fields for RAC RFBIASCAL */
#define _RAC_RFBIASCAL_RESETVALUE                                     0x30201A20UL                                        /**< Default value for RAC_RFBIASCAL             */
#define _RAC_RFBIASCAL_MASK                                           0x3F3F3F3FUL                                        /**< Mask for RAC_RFBIASCAL                      */
#define _RAC_RFBIASCAL_RFBIASCALBIAS_SHIFT                            0                                                   /**< Shift value for RAC_RFBIASCALBIAS           */
#define _RAC_RFBIASCAL_RFBIASCALBIAS_MASK                             0x3FUL                                              /**< Bit mask for RAC_RFBIASCALBIAS              */
#define _RAC_RFBIASCAL_RFBIASCALBIAS_DEFAULT                          0x00000020UL                                        /**< Mode DEFAULT for RAC_RFBIASCAL              */
#define RAC_RFBIASCAL_RFBIASCALBIAS_DEFAULT                           (_RAC_RFBIASCAL_RFBIASCALBIAS_DEFAULT << 0)         /**< Shifted mode DEFAULT for RAC_RFBIASCAL      */
#define _RAC_RFBIASCAL_RFBIASCALTC_SHIFT                              8                                                   /**< Shift value for RAC_RFBIASCALTC             */
#define _RAC_RFBIASCAL_RFBIASCALTC_MASK                               0x3F00UL                                            /**< Bit mask for RAC_RFBIASCALTC                */
#define _RAC_RFBIASCAL_RFBIASCALTC_DEFAULT                            0x0000001AUL                                        /**< Mode DEFAULT for RAC_RFBIASCAL              */
#define RAC_RFBIASCAL_RFBIASCALTC_DEFAULT                             (_RAC_RFBIASCAL_RFBIASCALTC_DEFAULT << 8)           /**< Shifted mode DEFAULT for RAC_RFBIASCAL      */
#define _RAC_RFBIASCAL_RFBIASCALVREF_SHIFT                            16                                                  /**< Shift value for RAC_RFBIASCALVREF           */
#define _RAC_RFBIASCAL_RFBIASCALVREF_MASK                             0x3F0000UL                                          /**< Bit mask for RAC_RFBIASCALVREF              */
#define _RAC_RFBIASCAL_RFBIASCALVREF_DEFAULT                          0x00000020UL                                        /**< Mode DEFAULT for RAC_RFBIASCAL              */
#define RAC_RFBIASCAL_RFBIASCALVREF_DEFAULT                           (_RAC_RFBIASCAL_RFBIASCALVREF_DEFAULT << 16)        /**< Shifted mode DEFAULT for RAC_RFBIASCAL      */
#define _RAC_RFBIASCAL_RFBIASCALVREFSTARTUP_SHIFT                     24                                                  /**< Shift value for RAC_RFBIASCALVREFSTARTUP    */
#define _RAC_RFBIASCAL_RFBIASCALVREFSTARTUP_MASK                      0x3F000000UL                                        /**< Bit mask for RAC_RFBIASCALVREFSTARTUP       */
#define _RAC_RFBIASCAL_RFBIASCALVREFSTARTUP_DEFAULT                   0x00000030UL                                        /**< Mode DEFAULT for RAC_RFBIASCAL              */
#define RAC_RFBIASCAL_RFBIASCALVREFSTARTUP_DEFAULT                    (_RAC_RFBIASCAL_RFBIASCALVREFSTARTUP_DEFAULT << 24) /**< Shifted mode DEFAULT for RAC_RFBIASCAL      */

/* Bit fields for RAC RFBIASCTRL */
#define _RAC_RFBIASCTRL_RESETVALUE                                    0x00040000UL                                                  /**< Default value for RAC_RFBIASCTRL            */
#define _RAC_RFBIASCTRL_MASK                                          0x000F001FUL                                                  /**< Mask for RAC_RFBIASCTRL                     */
#define RAC_RFBIASCTRL_RFBIASDISABLEBOOTSTRAP                         (0x1UL << 0)                                                  /**< RFBIASDISABLEBOOTSTRAP                      */
#define _RAC_RFBIASCTRL_RFBIASDISABLEBOOTSTRAP_SHIFT                  0                                                             /**< Shift value for RAC_RFBIASDISABLEBOOTSTRAP  */
#define _RAC_RFBIASCTRL_RFBIASDISABLEBOOTSTRAP_MASK                   0x1UL                                                         /**< Bit mask for RAC_RFBIASDISABLEBOOTSTRAP     */
#define _RAC_RFBIASCTRL_RFBIASDISABLEBOOTSTRAP_DEFAULT                0x00000000UL                                                  /**< Mode DEFAULT for RAC_RFBIASCTRL             */
#define _RAC_RFBIASCTRL_RFBIASDISABLEBOOTSTRAP_enable_startup         0x00000000UL                                                  /**< Mode enable_startup for RAC_RFBIASCTRL      */
#define _RAC_RFBIASCTRL_RFBIASDISABLEBOOTSTRAP_disable_startup        0x00000001UL                                                  /**< Mode disable_startup for RAC_RFBIASCTRL     */
#define RAC_RFBIASCTRL_RFBIASDISABLEBOOTSTRAP_DEFAULT                 (_RAC_RFBIASCTRL_RFBIASDISABLEBOOTSTRAP_DEFAULT << 0)         /**< Shifted mode DEFAULT for RAC_RFBIASCTRL     */
#define RAC_RFBIASCTRL_RFBIASDISABLEBOOTSTRAP_enable_startup          (_RAC_RFBIASCTRL_RFBIASDISABLEBOOTSTRAP_enable_startup << 0)  /**< Shifted mode enable_startup for RAC_RFBIASCTRL*/
#define RAC_RFBIASCTRL_RFBIASDISABLEBOOTSTRAP_disable_startup         (_RAC_RFBIASCTRL_RFBIASDISABLEBOOTSTRAP_disable_startup << 0) /**< Shifted mode disable_startup for RAC_RFBIASCTRL*/
#define RAC_RFBIASCTRL_RFBIASLDOHIGHCURRENT                           (0x1UL << 1)                                                  /**< RFBIASLDOHIGHCURRENT                        */
#define _RAC_RFBIASCTRL_RFBIASLDOHIGHCURRENT_SHIFT                    1                                                             /**< Shift value for RAC_RFBIASLDOHIGHCURRENT    */
#define _RAC_RFBIASCTRL_RFBIASLDOHIGHCURRENT_MASK                     0x2UL                                                         /**< Bit mask for RAC_RFBIASLDOHIGHCURRENT       */
#define _RAC_RFBIASCTRL_RFBIASLDOHIGHCURRENT_DEFAULT                  0x00000000UL                                                  /**< Mode DEFAULT for RAC_RFBIASCTRL             */
#define _RAC_RFBIASCTRL_RFBIASLDOHIGHCURRENT_low_current              0x00000000UL                                                  /**< Mode low_current for RAC_RFBIASCTRL         */
#define _RAC_RFBIASCTRL_RFBIASLDOHIGHCURRENT_high_current             0x00000001UL                                                  /**< Mode high_current for RAC_RFBIASCTRL        */
#define RAC_RFBIASCTRL_RFBIASLDOHIGHCURRENT_DEFAULT                   (_RAC_RFBIASCTRL_RFBIASLDOHIGHCURRENT_DEFAULT << 1)           /**< Shifted mode DEFAULT for RAC_RFBIASCTRL     */
#define RAC_RFBIASCTRL_RFBIASLDOHIGHCURRENT_low_current               (_RAC_RFBIASCTRL_RFBIASLDOHIGHCURRENT_low_current << 1)       /**< Shifted mode low_current for RAC_RFBIASCTRL */
#define RAC_RFBIASCTRL_RFBIASLDOHIGHCURRENT_high_current              (_RAC_RFBIASCTRL_RFBIASLDOHIGHCURRENT_high_current << 1)      /**< Shifted mode high_current for RAC_RFBIASCTRL*/
#define RAC_RFBIASCTRL_RFBIASNONFLASHMODE                             (0x1UL << 2)                                                  /**< RFBIASNONFLASHMODE                          */
#define _RAC_RFBIASCTRL_RFBIASNONFLASHMODE_SHIFT                      2                                                             /**< Shift value for RAC_RFBIASNONFLASHMODE      */
#define _RAC_RFBIASCTRL_RFBIASNONFLASHMODE_MASK                       0x4UL                                                         /**< Bit mask for RAC_RFBIASNONFLASHMODE         */
#define _RAC_RFBIASCTRL_RFBIASNONFLASHMODE_DEFAULT                    0x00000000UL                                                  /**< Mode DEFAULT for RAC_RFBIASCTRL             */
#define _RAC_RFBIASCTRL_RFBIASNONFLASHMODE_flash_process              0x00000000UL                                                  /**< Mode flash_process for RAC_RFBIASCTRL       */
#define _RAC_RFBIASCTRL_RFBIASNONFLASHMODE_non_flash_process          0x00000001UL                                                  /**< Mode non_flash_process for RAC_RFBIASCTRL   */
#define RAC_RFBIASCTRL_RFBIASNONFLASHMODE_DEFAULT                     (_RAC_RFBIASCTRL_RFBIASNONFLASHMODE_DEFAULT << 2)             /**< Shifted mode DEFAULT for RAC_RFBIASCTRL     */
#define RAC_RFBIASCTRL_RFBIASNONFLASHMODE_flash_process               (_RAC_RFBIASCTRL_RFBIASNONFLASHMODE_flash_process << 2)       /**< Shifted mode flash_process for RAC_RFBIASCTRL*/
#define RAC_RFBIASCTRL_RFBIASNONFLASHMODE_non_flash_process           (_RAC_RFBIASCTRL_RFBIASNONFLASHMODE_non_flash_process << 2)   /**< Shifted mode non_flash_process for RAC_RFBIASCTRL*/
#define RAC_RFBIASCTRL_RFBIASSTARTUPCORE                              (0x1UL << 3)                                                  /**< RFBIASSTARTUPCORE                           */
#define _RAC_RFBIASCTRL_RFBIASSTARTUPCORE_SHIFT                       3                                                             /**< Shift value for RAC_RFBIASSTARTUPCORE       */
#define _RAC_RFBIASCTRL_RFBIASSTARTUPCORE_MASK                        0x8UL                                                         /**< Bit mask for RAC_RFBIASSTARTUPCORE          */
#define _RAC_RFBIASCTRL_RFBIASSTARTUPCORE_DEFAULT                     0x00000000UL                                                  /**< Mode DEFAULT for RAC_RFBIASCTRL             */
#define _RAC_RFBIASCTRL_RFBIASSTARTUPCORE_default                     0x00000000UL                                                  /**< Mode default for RAC_RFBIASCTRL             */
#define _RAC_RFBIASCTRL_RFBIASSTARTUPCORE_force_start                 0x00000001UL                                                  /**< Mode force_start for RAC_RFBIASCTRL         */
#define RAC_RFBIASCTRL_RFBIASSTARTUPCORE_DEFAULT                      (_RAC_RFBIASCTRL_RFBIASSTARTUPCORE_DEFAULT << 3)              /**< Shifted mode DEFAULT for RAC_RFBIASCTRL     */
#define RAC_RFBIASCTRL_RFBIASSTARTUPCORE_default                      (_RAC_RFBIASCTRL_RFBIASSTARTUPCORE_default << 3)              /**< Shifted mode default for RAC_RFBIASCTRL     */
#define RAC_RFBIASCTRL_RFBIASSTARTUPCORE_force_start                  (_RAC_RFBIASCTRL_RFBIASSTARTUPCORE_force_start << 3)          /**< Shifted mode force_start for RAC_RFBIASCTRL */
#define RAC_RFBIASCTRL_RFBIASSTARTUPSUPPLY                            (0x1UL << 4)                                                  /**< RFBIASSTARTUPSUPPLY                         */
#define _RAC_RFBIASCTRL_RFBIASSTARTUPSUPPLY_SHIFT                     4                                                             /**< Shift value for RAC_RFBIASSTARTUPSUPPLY     */
#define _RAC_RFBIASCTRL_RFBIASSTARTUPSUPPLY_MASK                      0x10UL                                                        /**< Bit mask for RAC_RFBIASSTARTUPSUPPLY        */
#define _RAC_RFBIASCTRL_RFBIASSTARTUPSUPPLY_DEFAULT                   0x00000000UL                                                  /**< Mode DEFAULT for RAC_RFBIASCTRL             */
#define _RAC_RFBIASCTRL_RFBIASSTARTUPSUPPLY_default                   0x00000000UL                                                  /**< Mode default for RAC_RFBIASCTRL             */
#define _RAC_RFBIASCTRL_RFBIASSTARTUPSUPPLY_forc_start                0x00000001UL                                                  /**< Mode forc_start for RAC_RFBIASCTRL          */
#define RAC_RFBIASCTRL_RFBIASSTARTUPSUPPLY_DEFAULT                    (_RAC_RFBIASCTRL_RFBIASSTARTUPSUPPLY_DEFAULT << 4)            /**< Shifted mode DEFAULT for RAC_RFBIASCTRL     */
#define RAC_RFBIASCTRL_RFBIASSTARTUPSUPPLY_default                    (_RAC_RFBIASCTRL_RFBIASSTARTUPSUPPLY_default << 4)            /**< Shifted mode default for RAC_RFBIASCTRL     */
#define RAC_RFBIASCTRL_RFBIASSTARTUPSUPPLY_forc_start                 (_RAC_RFBIASCTRL_RFBIASSTARTUPSUPPLY_forc_start << 4)         /**< Shifted mode forc_start for RAC_RFBIASCTRL  */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_SHIFT                       16                                                            /**< Shift value for RAC_RFBIASLDOVREFTRIM       */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_MASK                        0xF0000UL                                                     /**< Bit mask for RAC_RFBIASLDOVREFTRIM          */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_DEFAULT                     0x00000004UL                                                  /**< Mode DEFAULT for RAC_RFBIASCTRL             */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p800                 0x00000000UL                                                  /**< Mode vref_v0p800 for RAC_RFBIASCTRL         */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p813                 0x00000001UL                                                  /**< Mode vref_v0p813 for RAC_RFBIASCTRL         */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p825                 0x00000002UL                                                  /**< Mode vref_v0p825 for RAC_RFBIASCTRL         */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p837                 0x00000003UL                                                  /**< Mode vref_v0p837 for RAC_RFBIASCTRL         */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p850                 0x00000004UL                                                  /**< Mode vref_v0p850 for RAC_RFBIASCTRL         */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p863                 0x00000005UL                                                  /**< Mode vref_v0p863 for RAC_RFBIASCTRL         */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p875                 0x00000006UL                                                  /**< Mode vref_v0p875 for RAC_RFBIASCTRL         */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p887                 0x00000007UL                                                  /**< Mode vref_v0p887 for RAC_RFBIASCTRL         */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p900                 0x00000008UL                                                  /**< Mode vref_v0p900 for RAC_RFBIASCTRL         */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p913                 0x00000009UL                                                  /**< Mode vref_v0p913 for RAC_RFBIASCTRL         */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p925                 0x0000000AUL                                                  /**< Mode vref_v0p925 for RAC_RFBIASCTRL         */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p938                 0x0000000BUL                                                  /**< Mode vref_v0p938 for RAC_RFBIASCTRL         */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p950                 0x0000000CUL                                                  /**< Mode vref_v0p950 for RAC_RFBIASCTRL         */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p963                 0x0000000DUL                                                  /**< Mode vref_v0p963 for RAC_RFBIASCTRL         */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p975                 0x0000000EUL                                                  /**< Mode vref_v0p975 for RAC_RFBIASCTRL         */
#define _RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p988                 0x0000000FUL                                                  /**< Mode vref_v0p988 for RAC_RFBIASCTRL         */
#define RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_DEFAULT                      (_RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_DEFAULT << 16)             /**< Shifted mode DEFAULT for RAC_RFBIASCTRL     */
#define RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p800                  (_RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p800 << 16)         /**< Shifted mode vref_v0p800 for RAC_RFBIASCTRL */
#define RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p813                  (_RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p813 << 16)         /**< Shifted mode vref_v0p813 for RAC_RFBIASCTRL */
#define RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p825                  (_RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p825 << 16)         /**< Shifted mode vref_v0p825 for RAC_RFBIASCTRL */
#define RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p837                  (_RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p837 << 16)         /**< Shifted mode vref_v0p837 for RAC_RFBIASCTRL */
#define RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p850                  (_RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p850 << 16)         /**< Shifted mode vref_v0p850 for RAC_RFBIASCTRL */
#define RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p863                  (_RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p863 << 16)         /**< Shifted mode vref_v0p863 for RAC_RFBIASCTRL */
#define RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p875                  (_RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p875 << 16)         /**< Shifted mode vref_v0p875 for RAC_RFBIASCTRL */
#define RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p887                  (_RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p887 << 16)         /**< Shifted mode vref_v0p887 for RAC_RFBIASCTRL */
#define RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p900                  (_RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p900 << 16)         /**< Shifted mode vref_v0p900 for RAC_RFBIASCTRL */
#define RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p913                  (_RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p913 << 16)         /**< Shifted mode vref_v0p913 for RAC_RFBIASCTRL */
#define RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p925                  (_RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p925 << 16)         /**< Shifted mode vref_v0p925 for RAC_RFBIASCTRL */
#define RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p938                  (_RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p938 << 16)         /**< Shifted mode vref_v0p938 for RAC_RFBIASCTRL */
#define RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p950                  (_RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p950 << 16)         /**< Shifted mode vref_v0p950 for RAC_RFBIASCTRL */
#define RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p963                  (_RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p963 << 16)         /**< Shifted mode vref_v0p963 for RAC_RFBIASCTRL */
#define RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p975                  (_RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p975 << 16)         /**< Shifted mode vref_v0p975 for RAC_RFBIASCTRL */
#define RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p988                  (_RAC_RFBIASCTRL_RFBIASLDOVREFTRIM_vref_v0p988 << 16)         /**< Shifted mode vref_v0p988 for RAC_RFBIASCTRL */

/* Bit fields for RAC RADIOEN */
#define _RAC_RADIOEN_RESETVALUE                                       0x00000000UL                                      /**< Default value for RAC_RADIOEN               */
#define _RAC_RADIOEN_MASK                                             0x00000007UL                                      /**< Mask for RAC_RADIOEN                        */
#define RAC_RADIOEN_PREEN                                             (0x1UL << 0)                                      /**< PREEN                                       */
#define _RAC_RADIOEN_PREEN_SHIFT                                      0                                                 /**< Shift value for RAC_PREEN                   */
#define _RAC_RADIOEN_PREEN_MASK                                       0x1UL                                             /**< Bit mask for RAC_PREEN                      */
#define _RAC_RADIOEN_PREEN_DEFAULT                                    0x00000000UL                                      /**< Mode DEFAULT for RAC_RADIOEN                */
#define _RAC_RADIOEN_PREEN_powered_off                                0x00000000UL                                      /**< Mode powered_off for RAC_RADIOEN            */
#define _RAC_RADIOEN_PREEN_powered_on                                 0x00000001UL                                      /**< Mode powered_on for RAC_RADIOEN             */
#define RAC_RADIOEN_PREEN_DEFAULT                                     (_RAC_RADIOEN_PREEN_DEFAULT << 0)                 /**< Shifted mode DEFAULT for RAC_RADIOEN        */
#define RAC_RADIOEN_PREEN_powered_off                                 (_RAC_RADIOEN_PREEN_powered_off << 0)             /**< Shifted mode powered_off for RAC_RADIOEN    */
#define RAC_RADIOEN_PREEN_powered_on                                  (_RAC_RADIOEN_PREEN_powered_on << 0)              /**< Shifted mode powered_on for RAC_RADIOEN     */
#define RAC_RADIOEN_PRESTB100UDIS                                     (0x1UL << 1)                                      /**< PRESTB100UDIS                               */
#define _RAC_RADIOEN_PRESTB100UDIS_SHIFT                              1                                                 /**< Shift value for RAC_PRESTB100UDIS           */
#define _RAC_RADIOEN_PRESTB100UDIS_MASK                               0x2UL                                             /**< Bit mask for RAC_PRESTB100UDIS              */
#define _RAC_RADIOEN_PRESTB100UDIS_DEFAULT                            0x00000000UL                                      /**< Mode DEFAULT for RAC_RADIOEN                */
#define _RAC_RADIOEN_PRESTB100UDIS_i100ua_enabled                     0x00000000UL                                      /**< Mode i100ua_enabled for RAC_RADIOEN         */
#define _RAC_RADIOEN_PRESTB100UDIS_i100ua_disabled                    0x00000001UL                                      /**< Mode i100ua_disabled for RAC_RADIOEN        */
#define RAC_RADIOEN_PRESTB100UDIS_DEFAULT                             (_RAC_RADIOEN_PRESTB100UDIS_DEFAULT << 1)         /**< Shifted mode DEFAULT for RAC_RADIOEN        */
#define RAC_RADIOEN_PRESTB100UDIS_i100ua_enabled                      (_RAC_RADIOEN_PRESTB100UDIS_i100ua_enabled << 1)  /**< Shifted mode i100ua_enabled for RAC_RADIOEN */
#define RAC_RADIOEN_PRESTB100UDIS_i100ua_disabled                     (_RAC_RADIOEN_PRESTB100UDIS_i100ua_disabled << 1) /**< Shifted mode i100ua_disabled for RAC_RADIOEN*/
#define RAC_RADIOEN_RFBIASEN                                          (0x1UL << 2)                                      /**< RFBIASEN                                    */
#define _RAC_RADIOEN_RFBIASEN_SHIFT                                   2                                                 /**< Shift value for RAC_RFBIASEN                */
#define _RAC_RADIOEN_RFBIASEN_MASK                                    0x4UL                                             /**< Bit mask for RAC_RFBIASEN                   */
#define _RAC_RADIOEN_RFBIASEN_DEFAULT                                 0x00000000UL                                      /**< Mode DEFAULT for RAC_RADIOEN                */
#define _RAC_RADIOEN_RFBIASEN_disable_rfis_vtr                        0x00000000UL                                      /**< Mode disable_rfis_vtr for RAC_RADIOEN       */
#define _RAC_RADIOEN_RFBIASEN_enable_rfis_vtr                         0x00000001UL                                      /**< Mode enable_rfis_vtr for RAC_RADIOEN        */
#define RAC_RADIOEN_RFBIASEN_DEFAULT                                  (_RAC_RADIOEN_RFBIASEN_DEFAULT << 2)              /**< Shifted mode DEFAULT for RAC_RADIOEN        */
#define RAC_RADIOEN_RFBIASEN_disable_rfis_vtr                         (_RAC_RADIOEN_RFBIASEN_disable_rfis_vtr << 2)     /**< Shifted mode disable_rfis_vtr for RAC_RADIOEN*/
#define RAC_RADIOEN_RFBIASEN_enable_rfis_vtr                          (_RAC_RADIOEN_RFBIASEN_enable_rfis_vtr << 2)      /**< Shifted mode enable_rfis_vtr for RAC_RADIOEN*/

/* Bit fields for RAC RFPATHEN0 */
#define _RAC_RFPATHEN0_RESETVALUE                                     0x00000002UL                                       /**< Default value for RAC_RFPATHEN0             */
#define _RAC_RFPATHEN0_MASK                                           0x0000004FUL                                       /**< Mask for RAC_RFPATHEN0                      */
#define RAC_RFPATHEN0_LNAMIXEN0                                       (0x1UL << 0)                                       /**< LNAMIXEN0                                   */
#define _RAC_RFPATHEN0_LNAMIXEN0_SHIFT                                0                                                  /**< Shift value for RAC_LNAMIXEN0               */
#define _RAC_RFPATHEN0_LNAMIXEN0_MASK                                 0x1UL                                              /**< Bit mask for RAC_LNAMIXEN0                  */
#define _RAC_RFPATHEN0_LNAMIXEN0_DEFAULT                              0x00000000UL                                       /**< Mode DEFAULT for RAC_RFPATHEN0              */
#define _RAC_RFPATHEN0_LNAMIXEN0_disable                              0x00000000UL                                       /**< Mode disable for RAC_RFPATHEN0              */
#define _RAC_RFPATHEN0_LNAMIXEN0_enable                               0x00000001UL                                       /**< Mode enable for RAC_RFPATHEN0               */
#define RAC_RFPATHEN0_LNAMIXEN0_DEFAULT                               (_RAC_RFPATHEN0_LNAMIXEN0_DEFAULT << 0)            /**< Shifted mode DEFAULT for RAC_RFPATHEN0      */
#define RAC_RFPATHEN0_LNAMIXEN0_disable                               (_RAC_RFPATHEN0_LNAMIXEN0_disable << 0)            /**< Shifted mode disable for RAC_RFPATHEN0      */
#define RAC_RFPATHEN0_LNAMIXEN0_enable                                (_RAC_RFPATHEN0_LNAMIXEN0_enable << 0)             /**< Shifted mode enable for RAC_RFPATHEN0       */
#define RAC_RFPATHEN0_LNAMIXRFATTDCEN0                                (0x1UL << 1)                                       /**< LNAMIXRFATTDCEN0                            */
#define _RAC_RFPATHEN0_LNAMIXRFATTDCEN0_SHIFT                         1                                                  /**< Shift value for RAC_LNAMIXRFATTDCEN0        */
#define _RAC_RFPATHEN0_LNAMIXRFATTDCEN0_MASK                          0x2UL                                              /**< Bit mask for RAC_LNAMIXRFATTDCEN0           */
#define _RAC_RFPATHEN0_LNAMIXRFATTDCEN0_DEFAULT                       0x00000001UL                                       /**< Mode DEFAULT for RAC_RFPATHEN0              */
#define _RAC_RFPATHEN0_LNAMIXRFATTDCEN0_disable_dc                    0x00000000UL                                       /**< Mode disable_dc for RAC_RFPATHEN0           */
#define _RAC_RFPATHEN0_LNAMIXRFATTDCEN0_enable_dc                     0x00000001UL                                       /**< Mode enable_dc for RAC_RFPATHEN0            */
#define RAC_RFPATHEN0_LNAMIXRFATTDCEN0_DEFAULT                        (_RAC_RFPATHEN0_LNAMIXRFATTDCEN0_DEFAULT << 1)     /**< Shifted mode DEFAULT for RAC_RFPATHEN0      */
#define RAC_RFPATHEN0_LNAMIXRFATTDCEN0_disable_dc                     (_RAC_RFPATHEN0_LNAMIXRFATTDCEN0_disable_dc << 1)  /**< Shifted mode disable_dc for RAC_RFPATHEN0   */
#define RAC_RFPATHEN0_LNAMIXRFATTDCEN0_enable_dc                      (_RAC_RFPATHEN0_LNAMIXRFATTDCEN0_enable_dc << 1)   /**< Shifted mode enable_dc for RAC_RFPATHEN0    */
#define RAC_RFPATHEN0_LNAMIXRFPKDENRF0                                (0x1UL << 2)                                       /**< LNAMIXRFPKDENRF0                            */
#define _RAC_RFPATHEN0_LNAMIXRFPKDENRF0_SHIFT                         2                                                  /**< Shift value for RAC_LNAMIXRFPKDENRF0        */
#define _RAC_RFPATHEN0_LNAMIXRFPKDENRF0_MASK                          0x4UL                                              /**< Bit mask for RAC_LNAMIXRFPKDENRF0           */
#define _RAC_RFPATHEN0_LNAMIXRFPKDENRF0_DEFAULT                       0x00000000UL                                       /**< Mode DEFAULT for RAC_RFPATHEN0              */
#define _RAC_RFPATHEN0_LNAMIXRFPKDENRF0_disable                       0x00000000UL                                       /**< Mode disable for RAC_RFPATHEN0              */
#define _RAC_RFPATHEN0_LNAMIXRFPKDENRF0_enable_path                   0x00000001UL                                       /**< Mode enable_path for RAC_RFPATHEN0          */
#define RAC_RFPATHEN0_LNAMIXRFPKDENRF0_DEFAULT                        (_RAC_RFPATHEN0_LNAMIXRFPKDENRF0_DEFAULT << 2)     /**< Shifted mode DEFAULT for RAC_RFPATHEN0      */
#define RAC_RFPATHEN0_LNAMIXRFPKDENRF0_disable                        (_RAC_RFPATHEN0_LNAMIXRFPKDENRF0_disable << 2)     /**< Shifted mode disable for RAC_RFPATHEN0      */
#define RAC_RFPATHEN0_LNAMIXRFPKDENRF0_enable_path                    (_RAC_RFPATHEN0_LNAMIXRFPKDENRF0_enable_path << 2) /**< Shifted mode enable_path for RAC_RFPATHEN0  */
#define RAC_RFPATHEN0_SYLODIVRLO02G4EN                                (0x1UL << 3)                                       /**< SYLODIVRLO02G4EN                            */
#define _RAC_RFPATHEN0_SYLODIVRLO02G4EN_SHIFT                         3                                                  /**< Shift value for RAC_SYLODIVRLO02G4EN        */
#define _RAC_RFPATHEN0_SYLODIVRLO02G4EN_MASK                          0x8UL                                              /**< Bit mask for RAC_SYLODIVRLO02G4EN           */
#define _RAC_RFPATHEN0_SYLODIVRLO02G4EN_DEFAULT                       0x00000000UL                                       /**< Mode DEFAULT for RAC_RFPATHEN0              */
#define _RAC_RFPATHEN0_SYLODIVRLO02G4EN_disable                       0x00000000UL                                       /**< Mode disable for RAC_RFPATHEN0              */
#define _RAC_RFPATHEN0_SYLODIVRLO02G4EN_enable                        0x00000001UL                                       /**< Mode enable for RAC_RFPATHEN0               */
#define RAC_RFPATHEN0_SYLODIVRLO02G4EN_DEFAULT                        (_RAC_RFPATHEN0_SYLODIVRLO02G4EN_DEFAULT << 3)     /**< Shifted mode DEFAULT for RAC_RFPATHEN0      */
#define RAC_RFPATHEN0_SYLODIVRLO02G4EN_disable                        (_RAC_RFPATHEN0_SYLODIVRLO02G4EN_disable << 3)     /**< Shifted mode disable for RAC_RFPATHEN0      */
#define RAC_RFPATHEN0_SYLODIVRLO02G4EN_enable                         (_RAC_RFPATHEN0_SYLODIVRLO02G4EN_enable << 3)      /**< Shifted mode enable for RAC_RFPATHEN0       */
#define RAC_RFPATHEN0_LNAMIXTRSW0                                     (0x1UL << 6)                                       /**< LNAMIXTRSW0                                 */
#define _RAC_RFPATHEN0_LNAMIXTRSW0_SHIFT                              6                                                  /**< Shift value for RAC_LNAMIXTRSW0             */
#define _RAC_RFPATHEN0_LNAMIXTRSW0_MASK                               0x40UL                                             /**< Bit mask for RAC_LNAMIXTRSW0                */
#define _RAC_RFPATHEN0_LNAMIXTRSW0_DEFAULT                            0x00000000UL                                       /**< Mode DEFAULT for RAC_RFPATHEN0              */
#define _RAC_RFPATHEN0_LNAMIXTRSW0_disabled                           0x00000000UL                                       /**< Mode disabled for RAC_RFPATHEN0             */
#define _RAC_RFPATHEN0_LNAMIXTRSW0_enabled                            0x00000001UL                                       /**< Mode enabled for RAC_RFPATHEN0              */
#define RAC_RFPATHEN0_LNAMIXTRSW0_DEFAULT                             (_RAC_RFPATHEN0_LNAMIXTRSW0_DEFAULT << 6)          /**< Shifted mode DEFAULT for RAC_RFPATHEN0      */
#define RAC_RFPATHEN0_LNAMIXTRSW0_disabled                            (_RAC_RFPATHEN0_LNAMIXTRSW0_disabled << 6)         /**< Shifted mode disabled for RAC_RFPATHEN0     */
#define RAC_RFPATHEN0_LNAMIXTRSW0_enabled                             (_RAC_RFPATHEN0_LNAMIXTRSW0_enabled << 6)          /**< Shifted mode enabled for RAC_RFPATHEN0      */

/* Bit fields for RAC RFPATHEN1 */
#define _RAC_RFPATHEN1_RESETVALUE                                     0x00000002UL                                       /**< Default value for RAC_RFPATHEN1             */
#define _RAC_RFPATHEN1_MASK                                           0x0000004FUL                                       /**< Mask for RAC_RFPATHEN1                      */
#define RAC_RFPATHEN1_LNAMIXEN1                                       (0x1UL << 0)                                       /**< LNAMIXEN1                                   */
#define _RAC_RFPATHEN1_LNAMIXEN1_SHIFT                                0                                                  /**< Shift value for RAC_LNAMIXEN1               */
#define _RAC_RFPATHEN1_LNAMIXEN1_MASK                                 0x1UL                                              /**< Bit mask for RAC_LNAMIXEN1                  */
#define _RAC_RFPATHEN1_LNAMIXEN1_DEFAULT                              0x00000000UL                                       /**< Mode DEFAULT for RAC_RFPATHEN1              */
#define _RAC_RFPATHEN1_LNAMIXEN1_disable                              0x00000000UL                                       /**< Mode disable for RAC_RFPATHEN1              */
#define _RAC_RFPATHEN1_LNAMIXEN1_enable                               0x00000001UL                                       /**< Mode enable for RAC_RFPATHEN1               */
#define RAC_RFPATHEN1_LNAMIXEN1_DEFAULT                               (_RAC_RFPATHEN1_LNAMIXEN1_DEFAULT << 0)            /**< Shifted mode DEFAULT for RAC_RFPATHEN1      */
#define RAC_RFPATHEN1_LNAMIXEN1_disable                               (_RAC_RFPATHEN1_LNAMIXEN1_disable << 0)            /**< Shifted mode disable for RAC_RFPATHEN1      */
#define RAC_RFPATHEN1_LNAMIXEN1_enable                                (_RAC_RFPATHEN1_LNAMIXEN1_enable << 0)             /**< Shifted mode enable for RAC_RFPATHEN1       */
#define RAC_RFPATHEN1_LNAMIXRFATTDCEN1                                (0x1UL << 1)                                       /**< LNAMIXRFATTDCEN1                            */
#define _RAC_RFPATHEN1_LNAMIXRFATTDCEN1_SHIFT                         1                                                  /**< Shift value for RAC_LNAMIXRFATTDCEN1        */
#define _RAC_RFPATHEN1_LNAMIXRFATTDCEN1_MASK                          0x2UL                                              /**< Bit mask for RAC_LNAMIXRFATTDCEN1           */
#define _RAC_RFPATHEN1_LNAMIXRFATTDCEN1_DEFAULT                       0x00000001UL                                       /**< Mode DEFAULT for RAC_RFPATHEN1              */
#define _RAC_RFPATHEN1_LNAMIXRFATTDCEN1_disable_dc                    0x00000000UL                                       /**< Mode disable_dc for RAC_RFPATHEN1           */
#define _RAC_RFPATHEN1_LNAMIXRFATTDCEN1_enable_dc                     0x00000001UL                                       /**< Mode enable_dc for RAC_RFPATHEN1            */
#define RAC_RFPATHEN1_LNAMIXRFATTDCEN1_DEFAULT                        (_RAC_RFPATHEN1_LNAMIXRFATTDCEN1_DEFAULT << 1)     /**< Shifted mode DEFAULT for RAC_RFPATHEN1      */
#define RAC_RFPATHEN1_LNAMIXRFATTDCEN1_disable_dc                     (_RAC_RFPATHEN1_LNAMIXRFATTDCEN1_disable_dc << 1)  /**< Shifted mode disable_dc for RAC_RFPATHEN1   */
#define RAC_RFPATHEN1_LNAMIXRFATTDCEN1_enable_dc                      (_RAC_RFPATHEN1_LNAMIXRFATTDCEN1_enable_dc << 1)   /**< Shifted mode enable_dc for RAC_RFPATHEN1    */
#define RAC_RFPATHEN1_LNAMIXRFPKDENRF1                                (0x1UL << 2)                                       /**< LNAMIXRFPKDENRF1                            */
#define _RAC_RFPATHEN1_LNAMIXRFPKDENRF1_SHIFT                         2                                                  /**< Shift value for RAC_LNAMIXRFPKDENRF1        */
#define _RAC_RFPATHEN1_LNAMIXRFPKDENRF1_MASK                          0x4UL                                              /**< Bit mask for RAC_LNAMIXRFPKDENRF1           */
#define _RAC_RFPATHEN1_LNAMIXRFPKDENRF1_DEFAULT                       0x00000000UL                                       /**< Mode DEFAULT for RAC_RFPATHEN1              */
#define _RAC_RFPATHEN1_LNAMIXRFPKDENRF1_disable                       0x00000000UL                                       /**< Mode disable for RAC_RFPATHEN1              */
#define _RAC_RFPATHEN1_LNAMIXRFPKDENRF1_enable_path                   0x00000001UL                                       /**< Mode enable_path for RAC_RFPATHEN1          */
#define RAC_RFPATHEN1_LNAMIXRFPKDENRF1_DEFAULT                        (_RAC_RFPATHEN1_LNAMIXRFPKDENRF1_DEFAULT << 2)     /**< Shifted mode DEFAULT for RAC_RFPATHEN1      */
#define RAC_RFPATHEN1_LNAMIXRFPKDENRF1_disable                        (_RAC_RFPATHEN1_LNAMIXRFPKDENRF1_disable << 2)     /**< Shifted mode disable for RAC_RFPATHEN1      */
#define RAC_RFPATHEN1_LNAMIXRFPKDENRF1_enable_path                    (_RAC_RFPATHEN1_LNAMIXRFPKDENRF1_enable_path << 2) /**< Shifted mode enable_path for RAC_RFPATHEN1  */
#define RAC_RFPATHEN1_SYLODIVRLO12G4EN                                (0x1UL << 3)                                       /**< SYLODIVRLO12G4EN                            */
#define _RAC_RFPATHEN1_SYLODIVRLO12G4EN_SHIFT                         3                                                  /**< Shift value for RAC_SYLODIVRLO12G4EN        */
#define _RAC_RFPATHEN1_SYLODIVRLO12G4EN_MASK                          0x8UL                                              /**< Bit mask for RAC_SYLODIVRLO12G4EN           */
#define _RAC_RFPATHEN1_SYLODIVRLO12G4EN_DEFAULT                       0x00000000UL                                       /**< Mode DEFAULT for RAC_RFPATHEN1              */
#define _RAC_RFPATHEN1_SYLODIVRLO12G4EN_disable                       0x00000000UL                                       /**< Mode disable for RAC_RFPATHEN1              */
#define _RAC_RFPATHEN1_SYLODIVRLO12G4EN_enable                        0x00000001UL                                       /**< Mode enable for RAC_RFPATHEN1               */
#define RAC_RFPATHEN1_SYLODIVRLO12G4EN_DEFAULT                        (_RAC_RFPATHEN1_SYLODIVRLO12G4EN_DEFAULT << 3)     /**< Shifted mode DEFAULT for RAC_RFPATHEN1      */
#define RAC_RFPATHEN1_SYLODIVRLO12G4EN_disable                        (_RAC_RFPATHEN1_SYLODIVRLO12G4EN_disable << 3)     /**< Shifted mode disable for RAC_RFPATHEN1      */
#define RAC_RFPATHEN1_SYLODIVRLO12G4EN_enable                         (_RAC_RFPATHEN1_SYLODIVRLO12G4EN_enable << 3)      /**< Shifted mode enable for RAC_RFPATHEN1       */
#define RAC_RFPATHEN1_LNAMIXTRSW1                                     (0x1UL << 6)                                       /**< LNAMIXTRSW1                                 */
#define _RAC_RFPATHEN1_LNAMIXTRSW1_SHIFT                              6                                                  /**< Shift value for RAC_LNAMIXTRSW1             */
#define _RAC_RFPATHEN1_LNAMIXTRSW1_MASK                               0x40UL                                             /**< Bit mask for RAC_LNAMIXTRSW1                */
#define _RAC_RFPATHEN1_LNAMIXTRSW1_DEFAULT                            0x00000000UL                                       /**< Mode DEFAULT for RAC_RFPATHEN1              */
#define _RAC_RFPATHEN1_LNAMIXTRSW1_disabled                           0x00000000UL                                       /**< Mode disabled for RAC_RFPATHEN1             */
#define _RAC_RFPATHEN1_LNAMIXTRSW1_enabled                            0x00000001UL                                       /**< Mode enabled for RAC_RFPATHEN1              */
#define RAC_RFPATHEN1_LNAMIXTRSW1_DEFAULT                             (_RAC_RFPATHEN1_LNAMIXTRSW1_DEFAULT << 6)          /**< Shifted mode DEFAULT for RAC_RFPATHEN1      */
#define RAC_RFPATHEN1_LNAMIXTRSW1_disabled                            (_RAC_RFPATHEN1_LNAMIXTRSW1_disabled << 6)         /**< Shifted mode disabled for RAC_RFPATHEN1     */
#define RAC_RFPATHEN1_LNAMIXTRSW1_enabled                             (_RAC_RFPATHEN1_LNAMIXTRSW1_enabled << 6)          /**< Shifted mode enabled for RAC_RFPATHEN1      */

/* Bit fields for RAC RX */
#define _RAC_RX_RESETVALUE                                            0x00000020UL                                       /**< Default value for RAC_RX                    */
#define _RAC_RX_MASK                                                  0x000703BFUL                                       /**< Mask for RAC_RX                             */
#define RAC_RX_IFADCCAPRESET                                          (0x1UL << 0)                                       /**< IFADCCAPRESET                               */
#define _RAC_RX_IFADCCAPRESET_SHIFT                                   0                                                  /**< Shift value for RAC_IFADCCAPRESET           */
#define _RAC_RX_IFADCCAPRESET_MASK                                    0x1UL                                              /**< Bit mask for RAC_IFADCCAPRESET              */
#define _RAC_RX_IFADCCAPRESET_DEFAULT                                 0x00000000UL                                       /**< Mode DEFAULT for RAC_RX                     */
#define _RAC_RX_IFADCCAPRESET_cap_reset_disable                       0x00000000UL                                       /**< Mode cap_reset_disable for RAC_RX           */
#define _RAC_RX_IFADCCAPRESET_cap_reset_enable                        0x00000001UL                                       /**< Mode cap_reset_enable for RAC_RX            */
#define RAC_RX_IFADCCAPRESET_DEFAULT                                  (_RAC_RX_IFADCCAPRESET_DEFAULT << 0)               /**< Shifted mode DEFAULT for RAC_RX             */
#define RAC_RX_IFADCCAPRESET_cap_reset_disable                        (_RAC_RX_IFADCCAPRESET_cap_reset_disable << 0)     /**< Shifted mode cap_reset_disable for RAC_RX   */
#define RAC_RX_IFADCCAPRESET_cap_reset_enable                         (_RAC_RX_IFADCCAPRESET_cap_reset_enable << 0)      /**< Shifted mode cap_reset_enable for RAC_RX    */
#define RAC_RX_IFADCENLDOSERIES                                       (0x1UL << 1)                                       /**< IFADCENLDOSERIES                            */
#define _RAC_RX_IFADCENLDOSERIES_SHIFT                                1                                                  /**< Shift value for RAC_IFADCENLDOSERIES        */
#define _RAC_RX_IFADCENLDOSERIES_MASK                                 0x2UL                                              /**< Bit mask for RAC_IFADCENLDOSERIES           */
#define _RAC_RX_IFADCENLDOSERIES_DEFAULT                              0x00000000UL                                       /**< Mode DEFAULT for RAC_RX                     */
#define _RAC_RX_IFADCENLDOSERIES_series_ldo_disable                   0x00000000UL                                       /**< Mode series_ldo_disable for RAC_RX          */
#define _RAC_RX_IFADCENLDOSERIES_series_ldo_enable                    0x00000001UL                                       /**< Mode series_ldo_enable for RAC_RX           */
#define RAC_RX_IFADCENLDOSERIES_DEFAULT                               (_RAC_RX_IFADCENLDOSERIES_DEFAULT << 1)            /**< Shifted mode DEFAULT for RAC_RX             */
#define RAC_RX_IFADCENLDOSERIES_series_ldo_disable                    (_RAC_RX_IFADCENLDOSERIES_series_ldo_disable << 1) /**< Shifted mode series_ldo_disable for RAC_RX  */
#define RAC_RX_IFADCENLDOSERIES_series_ldo_enable                     (_RAC_RX_IFADCENLDOSERIES_series_ldo_enable << 1)  /**< Shifted mode series_ldo_enable for RAC_RX   */
#define RAC_RX_IFADCENLDOSHUNT                                        (0x1UL << 2)                                       /**< IFADCENLDOSHUNT                             */
#define _RAC_RX_IFADCENLDOSHUNT_SHIFT                                 2                                                  /**< Shift value for RAC_IFADCENLDOSHUNT         */
#define _RAC_RX_IFADCENLDOSHUNT_MASK                                  0x4UL                                              /**< Bit mask for RAC_IFADCENLDOSHUNT            */
#define _RAC_RX_IFADCENLDOSHUNT_DEFAULT                               0x00000000UL                                       /**< Mode DEFAULT for RAC_RX                     */
#define _RAC_RX_IFADCENLDOSHUNT_shunt_ldo_disable                     0x00000000UL                                       /**< Mode shunt_ldo_disable for RAC_RX           */
#define _RAC_RX_IFADCENLDOSHUNT_shunt_ldo_enable                      0x00000001UL                                       /**< Mode shunt_ldo_enable for RAC_RX            */
#define RAC_RX_IFADCENLDOSHUNT_DEFAULT                                (_RAC_RX_IFADCENLDOSHUNT_DEFAULT << 2)             /**< Shifted mode DEFAULT for RAC_RX             */
#define RAC_RX_IFADCENLDOSHUNT_shunt_ldo_disable                      (_RAC_RX_IFADCENLDOSHUNT_shunt_ldo_disable << 2)   /**< Shifted mode shunt_ldo_disable for RAC_RX   */
#define RAC_RX_IFADCENLDOSHUNT_shunt_ldo_enable                       (_RAC_RX_IFADCENLDOSHUNT_shunt_ldo_enable << 2)    /**< Shifted mode shunt_ldo_enable for RAC_RX    */
#define RAC_RX_LNAMIXENRFPKD                                          (0x1UL << 3)                                       /**< LNAMIXENRFPKD                               */
#define _RAC_RX_LNAMIXENRFPKD_SHIFT                                   3                                                  /**< Shift value for RAC_LNAMIXENRFPKD           */
#define _RAC_RX_LNAMIXENRFPKD_MASK                                    0x8UL                                              /**< Bit mask for RAC_LNAMIXENRFPKD              */
#define _RAC_RX_LNAMIXENRFPKD_DEFAULT                                 0x00000000UL                                       /**< Mode DEFAULT for RAC_RX                     */
#define _RAC_RX_LNAMIXENRFPKD_disable                                 0x00000000UL                                       /**< Mode disable for RAC_RX                     */
#define _RAC_RX_LNAMIXENRFPKD_enable                                  0x00000001UL                                       /**< Mode enable for RAC_RX                      */
#define RAC_RX_LNAMIXENRFPKD_DEFAULT                                  (_RAC_RX_LNAMIXENRFPKD_DEFAULT << 3)               /**< Shifted mode DEFAULT for RAC_RX             */
#define RAC_RX_LNAMIXENRFPKD_disable                                  (_RAC_RX_LNAMIXENRFPKD_disable << 3)               /**< Shifted mode disable for RAC_RX             */
#define RAC_RX_LNAMIXENRFPKD_enable                                   (_RAC_RX_LNAMIXENRFPKD_enable << 3)                /**< Shifted mode enable for RAC_RX              */
#define RAC_RX_LNAMIXENRFPKDLOTHRESH                                  (0x1UL << 4)                                       /**< LNAMIXENRFPKDLOTHRESH                       */
#define _RAC_RX_LNAMIXENRFPKDLOTHRESH_SHIFT                           4                                                  /**< Shift value for RAC_LNAMIXENRFPKDLOTHRESH   */
#define _RAC_RX_LNAMIXENRFPKDLOTHRESH_MASK                            0x10UL                                             /**< Bit mask for RAC_LNAMIXENRFPKDLOTHRESH      */
#define _RAC_RX_LNAMIXENRFPKDLOTHRESH_DEFAULT                         0x00000000UL                                       /**< Mode DEFAULT for RAC_RX                     */
#define _RAC_RX_LNAMIXENRFPKDLOTHRESH_disable                         0x00000000UL                                       /**< Mode disable for RAC_RX                     */
#define _RAC_RX_LNAMIXENRFPKDLOTHRESH_enable                          0x00000001UL                                       /**< Mode enable for RAC_RX                      */
#define RAC_RX_LNAMIXENRFPKDLOTHRESH_DEFAULT                          (_RAC_RX_LNAMIXENRFPKDLOTHRESH_DEFAULT << 4)       /**< Shifted mode DEFAULT for RAC_RX             */
#define RAC_RX_LNAMIXENRFPKDLOTHRESH_disable                          (_RAC_RX_LNAMIXENRFPKDLOTHRESH_disable << 4)       /**< Shifted mode disable for RAC_RX             */
#define RAC_RX_LNAMIXENRFPKDLOTHRESH_enable                           (_RAC_RX_LNAMIXENRFPKDLOTHRESH_enable << 4)        /**< Shifted mode enable for RAC_RX              */
#define RAC_RX_LNAMIXLDOLOWCUR                                        (0x1UL << 5)                                       /**< LNAMIXLDOLOWCUR                             */
#define _RAC_RX_LNAMIXLDOLOWCUR_SHIFT                                 5                                                  /**< Shift value for RAC_LNAMIXLDOLOWCUR         */
#define _RAC_RX_LNAMIXLDOLOWCUR_MASK                                  0x20UL                                             /**< Bit mask for RAC_LNAMIXLDOLOWCUR            */
#define _RAC_RX_LNAMIXLDOLOWCUR_DEFAULT                               0x00000001UL                                       /**< Mode DEFAULT for RAC_RX                     */
#define _RAC_RX_LNAMIXLDOLOWCUR_regular_mode                          0x00000000UL                                       /**< Mode regular_mode for RAC_RX                */
#define _RAC_RX_LNAMIXLDOLOWCUR_low_current_mode                      0x00000001UL                                       /**< Mode low_current_mode for RAC_RX            */
#define RAC_RX_LNAMIXLDOLOWCUR_DEFAULT                                (_RAC_RX_LNAMIXLDOLOWCUR_DEFAULT << 5)             /**< Shifted mode DEFAULT for RAC_RX             */
#define RAC_RX_LNAMIXLDOLOWCUR_regular_mode                           (_RAC_RX_LNAMIXLDOLOWCUR_regular_mode << 5)        /**< Shifted mode regular_mode for RAC_RX        */
#define RAC_RX_LNAMIXLDOLOWCUR_low_current_mode                       (_RAC_RX_LNAMIXLDOLOWCUR_low_current_mode << 5)    /**< Shifted mode low_current_mode for RAC_RX    */
#define RAC_RX_LNAMIXREGLOADEN                                        (0x1UL << 7)                                       /**< LNAMIXREGLOADEN                             */
#define _RAC_RX_LNAMIXREGLOADEN_SHIFT                                 7                                                  /**< Shift value for RAC_LNAMIXREGLOADEN         */
#define _RAC_RX_LNAMIXREGLOADEN_MASK                                  0x80UL                                             /**< Bit mask for RAC_LNAMIXREGLOADEN            */
#define _RAC_RX_LNAMIXREGLOADEN_DEFAULT                               0x00000000UL                                       /**< Mode DEFAULT for RAC_RX                     */
#define _RAC_RX_LNAMIXREGLOADEN_disable_resistor                      0x00000000UL                                       /**< Mode disable_resistor for RAC_RX            */
#define _RAC_RX_LNAMIXREGLOADEN_enable_resistor                       0x00000001UL                                       /**< Mode enable_resistor for RAC_RX             */
#define RAC_RX_LNAMIXREGLOADEN_DEFAULT                                (_RAC_RX_LNAMIXREGLOADEN_DEFAULT << 7)             /**< Shifted mode DEFAULT for RAC_RX             */
#define RAC_RX_LNAMIXREGLOADEN_disable_resistor                       (_RAC_RX_LNAMIXREGLOADEN_disable_resistor << 7)    /**< Shifted mode disable_resistor for RAC_RX    */
#define RAC_RX_LNAMIXREGLOADEN_enable_resistor                        (_RAC_RX_LNAMIXREGLOADEN_enable_resistor << 7)     /**< Shifted mode enable_resistor for RAC_RX     */
#define RAC_RX_PGAENLDO                                               (0x1UL << 8)                                       /**< PGAENLDO                                    */
#define _RAC_RX_PGAENLDO_SHIFT                                        8                                                  /**< Shift value for RAC_PGAENLDO                */
#define _RAC_RX_PGAENLDO_MASK                                         0x100UL                                            /**< Bit mask for RAC_PGAENLDO                   */
#define _RAC_RX_PGAENLDO_DEFAULT                                      0x00000000UL                                       /**< Mode DEFAULT for RAC_RX                     */
#define _RAC_RX_PGAENLDO_disable_ldo                                  0x00000000UL                                       /**< Mode disable_ldo for RAC_RX                 */
#define _RAC_RX_PGAENLDO_enable_ldo                                   0x00000001UL                                       /**< Mode enable_ldo for RAC_RX                  */
#define RAC_RX_PGAENLDO_DEFAULT                                       (_RAC_RX_PGAENLDO_DEFAULT << 8)                    /**< Shifted mode DEFAULT for RAC_RX             */
#define RAC_RX_PGAENLDO_disable_ldo                                   (_RAC_RX_PGAENLDO_disable_ldo << 8)                /**< Shifted mode disable_ldo for RAC_RX         */
#define RAC_RX_PGAENLDO_enable_ldo                                    (_RAC_RX_PGAENLDO_enable_ldo << 8)                 /**< Shifted mode enable_ldo for RAC_RX          */
#define RAC_RX_SYCHPQNC3EN                                            (0x1UL << 9)                                       /**< SYCHPQNC3EN                                 */
#define _RAC_RX_SYCHPQNC3EN_SHIFT                                     9                                                  /**< Shift value for RAC_SYCHPQNC3EN             */
#define _RAC_RX_SYCHPQNC3EN_MASK                                      0x200UL                                            /**< Bit mask for RAC_SYCHPQNC3EN                */
#define _RAC_RX_SYCHPQNC3EN_DEFAULT                                   0x00000000UL                                       /**< Mode DEFAULT for RAC_RX                     */
#define _RAC_RX_SYCHPQNC3EN_qnc_2                                     0x00000000UL                                       /**< Mode qnc_2 for RAC_RX                       */
#define _RAC_RX_SYCHPQNC3EN_qnc_3                                     0x00000001UL                                       /**< Mode qnc_3 for RAC_RX                       */
#define RAC_RX_SYCHPQNC3EN_DEFAULT                                    (_RAC_RX_SYCHPQNC3EN_DEFAULT << 9)                 /**< Shifted mode DEFAULT for RAC_RX             */
#define RAC_RX_SYCHPQNC3EN_qnc_2                                      (_RAC_RX_SYCHPQNC3EN_qnc_2 << 9)                   /**< Shifted mode qnc_2 for RAC_RX               */
#define RAC_RX_SYCHPQNC3EN_qnc_3                                      (_RAC_RX_SYCHPQNC3EN_qnc_3 << 9)                   /**< Shifted mode qnc_3 for RAC_RX               */
#define RAC_RX_SYCHPBIASTRIMBUFRX                                     (0x1UL << 16)                                      /**< SYCHPBIASTRIMBUFRX                          */
#define _RAC_RX_SYCHPBIASTRIMBUFRX_SHIFT                              16                                                 /**< Shift value for RAC_SYCHPBIASTRIMBUFRX      */
#define _RAC_RX_SYCHPBIASTRIMBUFRX_MASK                               0x10000UL                                          /**< Bit mask for RAC_SYCHPBIASTRIMBUFRX         */
#define _RAC_RX_SYCHPBIASTRIMBUFRX_DEFAULT                            0x00000000UL                                       /**< Mode DEFAULT for RAC_RX                     */
#define _RAC_RX_SYCHPBIASTRIMBUFRX_i_tail_10u                         0x00000000UL                                       /**< Mode i_tail_10u for RAC_RX                  */
#define _RAC_RX_SYCHPBIASTRIMBUFRX_i_tail_20u                         0x00000001UL                                       /**< Mode i_tail_20u for RAC_RX                  */
#define RAC_RX_SYCHPBIASTRIMBUFRX_DEFAULT                             (_RAC_RX_SYCHPBIASTRIMBUFRX_DEFAULT << 16)         /**< Shifted mode DEFAULT for RAC_RX             */
#define RAC_RX_SYCHPBIASTRIMBUFRX_i_tail_10u                          (_RAC_RX_SYCHPBIASTRIMBUFRX_i_tail_10u << 16)      /**< Shifted mode i_tail_10u for RAC_RX          */
#define RAC_RX_SYCHPBIASTRIMBUFRX_i_tail_20u                          (_RAC_RX_SYCHPBIASTRIMBUFRX_i_tail_20u << 16)      /**< Shifted mode i_tail_20u for RAC_RX          */
#define RAC_RX_SYPFDCHPLPENRX                                         (0x1UL << 17)                                      /**< SYPFDCHPLPENRX                              */
#define _RAC_RX_SYPFDCHPLPENRX_SHIFT                                  17                                                 /**< Shift value for RAC_SYPFDCHPLPENRX          */
#define _RAC_RX_SYPFDCHPLPENRX_MASK                                   0x20000UL                                          /**< Bit mask for RAC_SYPFDCHPLPENRX             */
#define _RAC_RX_SYPFDCHPLPENRX_DEFAULT                                0x00000000UL                                       /**< Mode DEFAULT for RAC_RX                     */
#define _RAC_RX_SYPFDCHPLPENRX_disable                                0x00000000UL                                       /**< Mode disable for RAC_RX                     */
#define _RAC_RX_SYPFDCHPLPENRX_enable                                 0x00000001UL                                       /**< Mode enable for RAC_RX                      */
#define RAC_RX_SYPFDCHPLPENRX_DEFAULT                                 (_RAC_RX_SYPFDCHPLPENRX_DEFAULT << 17)             /**< Shifted mode DEFAULT for RAC_RX             */
#define RAC_RX_SYPFDCHPLPENRX_disable                                 (_RAC_RX_SYPFDCHPLPENRX_disable << 17)             /**< Shifted mode disable for RAC_RX             */
#define RAC_RX_SYPFDCHPLPENRX_enable                                  (_RAC_RX_SYPFDCHPLPENRX_enable << 17)              /**< Shifted mode enable for RAC_RX              */
#define RAC_RX_SYPFDFPWENRX                                           (0x1UL << 18)                                      /**< SYPFDFPWENRX                                */
#define _RAC_RX_SYPFDFPWENRX_SHIFT                                    18                                                 /**< Shift value for RAC_SYPFDFPWENRX            */
#define _RAC_RX_SYPFDFPWENRX_MASK                                     0x40000UL                                          /**< Bit mask for RAC_SYPFDFPWENRX               */
#define _RAC_RX_SYPFDFPWENRX_DEFAULT                                  0x00000000UL                                       /**< Mode DEFAULT for RAC_RX                     */
#define _RAC_RX_SYPFDFPWENRX_disable                                  0x00000000UL                                       /**< Mode disable for RAC_RX                     */
#define _RAC_RX_SYPFDFPWENRX_enable                                   0x00000001UL                                       /**< Mode enable for RAC_RX                      */
#define RAC_RX_SYPFDFPWENRX_DEFAULT                                   (_RAC_RX_SYPFDFPWENRX_DEFAULT << 18)               /**< Shifted mode DEFAULT for RAC_RX             */
#define RAC_RX_SYPFDFPWENRX_disable                                   (_RAC_RX_SYPFDFPWENRX_disable << 18)               /**< Shifted mode disable for RAC_RX             */
#define RAC_RX_SYPFDFPWENRX_enable                                    (_RAC_RX_SYPFDFPWENRX_enable << 18)                /**< Shifted mode enable for RAC_RX              */

/* Bit fields for RAC TX */
#define _RAC_TX_RESETVALUE                                            0x00000000UL                                      /**< Default value for RAC_TX                    */
#define _RAC_TX_MASK                                                  0xFFFFF7EFUL                                      /**< Mask for RAC_TX                             */
#define RAC_TX_TXPAENREG                                              (0x1UL << 0)                                      /**< TXPAENREG                                   */
#define _RAC_TX_TXPAENREG_SHIFT                                       0                                                 /**< Shift value for RAC_TXPAENREG               */
#define _RAC_TX_TXPAENREG_MASK                                        0x1UL                                             /**< Bit mask for RAC_TXPAENREG                  */
#define _RAC_TX_TXPAENREG_DEFAULT                                     0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TXPAENREG_disable                                     0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TXPAENREG_enable                                      0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TXPAENREG_DEFAULT                                      (_RAC_TX_TXPAENREG_DEFAULT << 0)                  /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TXPAENREG_disable                                      (_RAC_TX_TXPAENREG_disable << 0)                  /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TXPAENREG_enable                                       (_RAC_TX_TXPAENREG_enable << 0)                   /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TXPAENRAMPCLK                                          (0x1UL << 1)                                      /**< TXPAENRAMPCLK                               */
#define _RAC_TX_TXPAENRAMPCLK_SHIFT                                   1                                                 /**< Shift value for RAC_TXPAENRAMPCLK           */
#define _RAC_TX_TXPAENRAMPCLK_MASK                                    0x2UL                                             /**< Bit mask for RAC_TXPAENRAMPCLK              */
#define _RAC_TX_TXPAENRAMPCLK_DEFAULT                                 0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TXPAENRAMPCLK_silence_clk                             0x00000000UL                                      /**< Mode silence_clk for RAC_TX                 */
#define _RAC_TX_TXPAENRAMPCLK_en_clk                                  0x00000001UL                                      /**< Mode en_clk for RAC_TX                      */
#define RAC_TX_TXPAENRAMPCLK_DEFAULT                                  (_RAC_TX_TXPAENRAMPCLK_DEFAULT << 1)              /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TXPAENRAMPCLK_silence_clk                              (_RAC_TX_TXPAENRAMPCLK_silence_clk << 1)          /**< Shifted mode silence_clk for RAC_TX         */
#define RAC_TX_TXPAENRAMPCLK_en_clk                                   (_RAC_TX_TXPAENRAMPCLK_en_clk << 1)               /**< Shifted mode en_clk for RAC_TX              */
#define RAC_TX_TX0DBMENBLEEDREG                                       (0x1UL << 2)                                      /**< TX0DBMENBLEEDREG                            */
#define _RAC_TX_TX0DBMENBLEEDREG_SHIFT                                2                                                 /**< Shift value for RAC_TX0DBMENBLEEDREG        */
#define _RAC_TX_TX0DBMENBLEEDREG_MASK                                 0x4UL                                             /**< Bit mask for RAC_TX0DBMENBLEEDREG           */
#define _RAC_TX_TX0DBMENBLEEDREG_DEFAULT                              0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TX0DBMENBLEEDREG_disable                              0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TX0DBMENBLEEDREG_enable                               0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TX0DBMENBLEEDREG_DEFAULT                               (_RAC_TX_TX0DBMENBLEEDREG_DEFAULT << 2)           /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TX0DBMENBLEEDREG_disable                               (_RAC_TX_TX0DBMENBLEEDREG_disable << 2)           /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TX0DBMENBLEEDREG_enable                                (_RAC_TX_TX0DBMENBLEEDREG_enable << 2)            /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TX0DBMENREG                                            (0x1UL << 3)                                      /**< TX0DBMENREG                                 */
#define _RAC_TX_TX0DBMENREG_SHIFT                                     3                                                 /**< Shift value for RAC_TX0DBMENREG             */
#define _RAC_TX_TX0DBMENREG_MASK                                      0x8UL                                             /**< Bit mask for RAC_TX0DBMENREG                */
#define _RAC_TX_TX0DBMENREG_DEFAULT                                   0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TX0DBMENREG_disable                                   0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TX0DBMENREG_enable                                    0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TX0DBMENREG_DEFAULT                                    (_RAC_TX_TX0DBMENREG_DEFAULT << 3)                /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TX0DBMENREG_disable                                    (_RAC_TX_TX0DBMENREG_disable << 3)                /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TX0DBMENREG_enable                                     (_RAC_TX_TX0DBMENREG_enable << 3)                 /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TX0DBMENBIAS                                           (0x1UL << 5)                                      /**< TX0DBMENBIAS                                */
#define _RAC_TX_TX0DBMENBIAS_SHIFT                                    5                                                 /**< Shift value for RAC_TX0DBMENBIAS            */
#define _RAC_TX_TX0DBMENBIAS_MASK                                     0x20UL                                            /**< Bit mask for RAC_TX0DBMENBIAS               */
#define _RAC_TX_TX0DBMENBIAS_DEFAULT                                  0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TX0DBMENBIAS_disable                                  0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TX0DBMENBIAS_enable                                   0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TX0DBMENBIAS_DEFAULT                                   (_RAC_TX_TX0DBMENBIAS_DEFAULT << 5)               /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TX0DBMENBIAS_disable                                   (_RAC_TX_TX0DBMENBIAS_disable << 5)               /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TX0DBMENBIAS_enable                                    (_RAC_TX_TX0DBMENBIAS_enable << 5)                /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TX0DBMENPREDRV                                         (0x1UL << 6)                                      /**< TX0DBMENPREDRV                              */
#define _RAC_TX_TX0DBMENPREDRV_SHIFT                                  6                                                 /**< Shift value for RAC_TX0DBMENPREDRV          */
#define _RAC_TX_TX0DBMENPREDRV_MASK                                   0x40UL                                            /**< Bit mask for RAC_TX0DBMENPREDRV             */
#define _RAC_TX_TX0DBMENPREDRV_DEFAULT                                0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TX0DBMENPREDRV_disable                                0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TX0DBMENPREDRV_enable                                 0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TX0DBMENPREDRV_DEFAULT                                 (_RAC_TX_TX0DBMENPREDRV_DEFAULT << 6)             /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TX0DBMENPREDRV_disable                                 (_RAC_TX_TX0DBMENPREDRV_disable << 6)             /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TX0DBMENPREDRV_enable                                  (_RAC_TX_TX0DBMENPREDRV_enable << 6)              /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TX0DBMENPREDRVREG                                      (0x1UL << 7)                                      /**< TX0DBMENPREDRVREG                           */
#define _RAC_TX_TX0DBMENPREDRVREG_SHIFT                               7                                                 /**< Shift value for RAC_TX0DBMENPREDRVREG       */
#define _RAC_TX_TX0DBMENPREDRVREG_MASK                                0x80UL                                            /**< Bit mask for RAC_TX0DBMENPREDRVREG          */
#define _RAC_TX_TX0DBMENPREDRVREG_DEFAULT                             0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TX0DBMENPREDRVREG_disable                             0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TX0DBMENPREDRVREG_enable                              0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TX0DBMENPREDRVREG_DEFAULT                              (_RAC_TX_TX0DBMENPREDRVREG_DEFAULT << 7)          /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TX0DBMENPREDRVREG_disable                              (_RAC_TX_TX0DBMENPREDRVREG_disable << 7)          /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TX0DBMENPREDRVREG_enable                               (_RAC_TX_TX0DBMENPREDRVREG_enable << 7)           /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TX0DBMENPREDRVREGBIAS                                  (0x1UL << 8)                                      /**< TX0DBMENPREDRVREGBIAS                       */
#define _RAC_TX_TX0DBMENPREDRVREGBIAS_SHIFT                           8                                                 /**< Shift value for RAC_TX0DBMENPREDRVREGBIAS   */
#define _RAC_TX_TX0DBMENPREDRVREGBIAS_MASK                            0x100UL                                           /**< Bit mask for RAC_TX0DBMENPREDRVREGBIAS      */
#define _RAC_TX_TX0DBMENPREDRVREGBIAS_DEFAULT                         0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TX0DBMENPREDRVREGBIAS_disable                         0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TX0DBMENPREDRVREGBIAS_enable                          0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TX0DBMENPREDRVREGBIAS_DEFAULT                          (_RAC_TX_TX0DBMENPREDRVREGBIAS_DEFAULT << 8)      /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TX0DBMENPREDRVREGBIAS_disable                          (_RAC_TX_TX0DBMENPREDRVREGBIAS_disable << 8)      /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TX0DBMENPREDRVREGBIAS_enable                           (_RAC_TX_TX0DBMENPREDRVREGBIAS_enable << 8)       /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TX0DBMENRAMPCLK                                        (0x1UL << 9)                                      /**< TX0DBMENRAMPCLK                             */
#define _RAC_TX_TX0DBMENRAMPCLK_SHIFT                                 9                                                 /**< Shift value for RAC_TX0DBMENRAMPCLK         */
#define _RAC_TX_TX0DBMENRAMPCLK_MASK                                  0x200UL                                           /**< Bit mask for RAC_TX0DBMENRAMPCLK            */
#define _RAC_TX_TX0DBMENRAMPCLK_DEFAULT                               0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TX0DBMENRAMPCLK_disable                               0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TX0DBMENRAMPCLK_enable                                0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TX0DBMENRAMPCLK_DEFAULT                                (_RAC_TX_TX0DBMENRAMPCLK_DEFAULT << 9)            /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TX0DBMENRAMPCLK_disable                                (_RAC_TX_TX0DBMENRAMPCLK_disable << 9)            /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TX0DBMENRAMPCLK_enable                                 (_RAC_TX_TX0DBMENRAMPCLK_enable << 9)             /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TX0DBMENBLEEDPREDRVREG                                 (0x1UL << 10)                                     /**< TX0DBMENBLEEDPREDRVREG                      */
#define _RAC_TX_TX0DBMENBLEEDPREDRVREG_SHIFT                          10                                                /**< Shift value for RAC_TX0DBMENBLEEDPREDRVREG  */
#define _RAC_TX_TX0DBMENBLEEDPREDRVREG_MASK                           0x400UL                                           /**< Bit mask for RAC_TX0DBMENBLEEDPREDRVREG     */
#define _RAC_TX_TX0DBMENBLEEDPREDRVREG_DEFAULT                        0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TX0DBMENBLEEDPREDRVREG_disable                        0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TX0DBMENBLEEDPREDRVREG_enable                         0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TX0DBMENBLEEDPREDRVREG_DEFAULT                         (_RAC_TX_TX0DBMENBLEEDPREDRVREG_DEFAULT << 10)    /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TX0DBMENBLEEDPREDRVREG_disable                         (_RAC_TX_TX0DBMENBLEEDPREDRVREG_disable << 10)    /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TX0DBMENBLEEDPREDRVREG_enable                          (_RAC_TX_TX0DBMENBLEEDPREDRVREG_enable << 10)     /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TXPAENBLEEDPREDRVREG                                   (0x1UL << 12)                                     /**< TXPAENBLEEDPREDRVREG                        */
#define _RAC_TX_TXPAENBLEEDPREDRVREG_SHIFT                            12                                                /**< Shift value for RAC_TXPAENBLEEDPREDRVREG    */
#define _RAC_TX_TXPAENBLEEDPREDRVREG_MASK                             0x1000UL                                          /**< Bit mask for RAC_TXPAENBLEEDPREDRVREG       */
#define _RAC_TX_TXPAENBLEEDPREDRVREG_DEFAULT                          0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TXPAENBLEEDPREDRVREG_disable                          0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TXPAENBLEEDPREDRVREG_enable                           0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TXPAENBLEEDPREDRVREG_DEFAULT                           (_RAC_TX_TXPAENBLEEDPREDRVREG_DEFAULT << 12)      /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TXPAENBLEEDPREDRVREG_disable                           (_RAC_TX_TXPAENBLEEDPREDRVREG_disable << 12)      /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TXPAENBLEEDPREDRVREG_enable                            (_RAC_TX_TXPAENBLEEDPREDRVREG_enable << 12)       /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TXPAENBLEEDREG                                         (0x1UL << 13)                                     /**< TXPAENBLEEDREG                              */
#define _RAC_TX_TXPAENBLEEDREG_SHIFT                                  13                                                /**< Shift value for RAC_TXPAENBLEEDREG          */
#define _RAC_TX_TXPAENBLEEDREG_MASK                                   0x2000UL                                          /**< Bit mask for RAC_TXPAENBLEEDREG             */
#define _RAC_TX_TXPAENBLEEDREG_DEFAULT                                0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TXPAENBLEEDREG_disable                                0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TXPAENBLEEDREG_enable                                 0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TXPAENBLEEDREG_DEFAULT                                 (_RAC_TX_TXPAENBLEEDREG_DEFAULT << 13)            /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TXPAENBLEEDREG_disable                                 (_RAC_TX_TXPAENBLEEDREG_disable << 13)            /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TXPAENBLEEDREG_enable                                  (_RAC_TX_TXPAENBLEEDREG_enable << 13)             /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TXPAENPAOUT                                            (0x1UL << 14)                                     /**< TXPAENPAOUT                                 */
#define _RAC_TX_TXPAENPAOUT_SHIFT                                     14                                                /**< Shift value for RAC_TXPAENPAOUT             */
#define _RAC_TX_TXPAENPAOUT_MASK                                      0x4000UL                                          /**< Bit mask for RAC_TXPAENPAOUT                */
#define _RAC_TX_TXPAENPAOUT_DEFAULT                                   0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TXPAENPAOUT_disable                                   0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TXPAENPAOUT_enable                                    0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TXPAENPAOUT_DEFAULT                                    (_RAC_TX_TXPAENPAOUT_DEFAULT << 14)               /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TXPAENPAOUT_disable                                    (_RAC_TX_TXPAENPAOUT_disable << 14)               /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TXPAENPAOUT_enable                                     (_RAC_TX_TXPAENPAOUT_enable << 14)                /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TXPAENPREDRVREG                                        (0x1UL << 15)                                     /**< TXPAENPREDRVREG                             */
#define _RAC_TX_TXPAENPREDRVREG_SHIFT                                 15                                                /**< Shift value for RAC_TXPAENPREDRVREG         */
#define _RAC_TX_TXPAENPREDRVREG_MASK                                  0x8000UL                                          /**< Bit mask for RAC_TXPAENPREDRVREG            */
#define _RAC_TX_TXPAENPREDRVREG_DEFAULT                               0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TXPAENPREDRVREG_disable                               0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TXPAENPREDRVREG_enable                                0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TXPAENPREDRVREG_DEFAULT                                (_RAC_TX_TXPAENPREDRVREG_DEFAULT << 15)           /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TXPAENPREDRVREG_disable                                (_RAC_TX_TXPAENPREDRVREG_disable << 15)           /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TXPAENPREDRVREG_enable                                 (_RAC_TX_TXPAENPREDRVREG_enable << 15)            /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_SYCHPBIASTRIMBUFTX                                     (0x1UL << 16)                                     /**< SYCHPBIASTRIMBUFTX                          */
#define _RAC_TX_SYCHPBIASTRIMBUFTX_SHIFT                              16                                                /**< Shift value for RAC_SYCHPBIASTRIMBUFTX      */
#define _RAC_TX_SYCHPBIASTRIMBUFTX_MASK                               0x10000UL                                         /**< Bit mask for RAC_SYCHPBIASTRIMBUFTX         */
#define _RAC_TX_SYCHPBIASTRIMBUFTX_DEFAULT                            0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_SYCHPBIASTRIMBUFTX_i_tail_10u                         0x00000000UL                                      /**< Mode i_tail_10u for RAC_TX                  */
#define _RAC_TX_SYCHPBIASTRIMBUFTX_i_tail_20u                         0x00000001UL                                      /**< Mode i_tail_20u for RAC_TX                  */
#define RAC_TX_SYCHPBIASTRIMBUFTX_DEFAULT                             (_RAC_TX_SYCHPBIASTRIMBUFTX_DEFAULT << 16)        /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_SYCHPBIASTRIMBUFTX_i_tail_10u                          (_RAC_TX_SYCHPBIASTRIMBUFTX_i_tail_10u << 16)     /**< Shifted mode i_tail_10u for RAC_TX          */
#define RAC_TX_SYCHPBIASTRIMBUFTX_i_tail_20u                          (_RAC_TX_SYCHPBIASTRIMBUFTX_i_tail_20u << 16)     /**< Shifted mode i_tail_20u for RAC_TX          */
#define RAC_TX_SYPFDCHPLPENTX                                         (0x1UL << 17)                                     /**< SYPFDCHPLPENTX                              */
#define _RAC_TX_SYPFDCHPLPENTX_SHIFT                                  17                                                /**< Shift value for RAC_SYPFDCHPLPENTX          */
#define _RAC_TX_SYPFDCHPLPENTX_MASK                                   0x20000UL                                         /**< Bit mask for RAC_SYPFDCHPLPENTX             */
#define _RAC_TX_SYPFDCHPLPENTX_DEFAULT                                0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_SYPFDCHPLPENTX_disable                                0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_SYPFDCHPLPENTX_enable                                 0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_SYPFDCHPLPENTX_DEFAULT                                 (_RAC_TX_SYPFDCHPLPENTX_DEFAULT << 17)            /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_SYPFDCHPLPENTX_disable                                 (_RAC_TX_SYPFDCHPLPENTX_disable << 17)            /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_SYPFDCHPLPENTX_enable                                  (_RAC_TX_SYPFDCHPLPENTX_enable << 17)             /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_SYPFDFPWENTX                                           (0x1UL << 18)                                     /**< SYPFDFPWENTX                                */
#define _RAC_TX_SYPFDFPWENTX_SHIFT                                    18                                                /**< Shift value for RAC_SYPFDFPWENTX            */
#define _RAC_TX_SYPFDFPWENTX_MASK                                     0x40000UL                                         /**< Bit mask for RAC_SYPFDFPWENTX               */
#define _RAC_TX_SYPFDFPWENTX_DEFAULT                                  0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_SYPFDFPWENTX_disable                                  0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_SYPFDFPWENTX_enable                                   0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_SYPFDFPWENTX_DEFAULT                                   (_RAC_TX_SYPFDFPWENTX_DEFAULT << 18)              /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_SYPFDFPWENTX_disable                                   (_RAC_TX_SYPFDFPWENTX_disable << 18)              /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_SYPFDFPWENTX_enable                                    (_RAC_TX_SYPFDFPWENTX_enable << 18)               /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TXPAEN10DBM                                            (0x1UL << 19)                                     /**< TXPAEN10DBM                                 */
#define _RAC_TX_TXPAEN10DBM_SHIFT                                     19                                                /**< Shift value for RAC_TXPAEN10DBM             */
#define _RAC_TX_TXPAEN10DBM_MASK                                      0x80000UL                                         /**< Bit mask for RAC_TXPAEN10DBM                */
#define _RAC_TX_TXPAEN10DBM_DEFAULT                                   0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TXPAEN10DBM_disable                                   0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TXPAEN10DBM_enable                                    0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TXPAEN10DBM_DEFAULT                                    (_RAC_TX_TXPAEN10DBM_DEFAULT << 19)               /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TXPAEN10DBM_disable                                    (_RAC_TX_TXPAEN10DBM_disable << 19)               /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TXPAEN10DBM_enable                                     (_RAC_TX_TXPAEN10DBM_enable << 19)                /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TXPAEN10DBMMAINCTAP                                    (0x1UL << 20)                                     /**< TXPAEN10DBMMAINCTAP                         */
#define _RAC_TX_TXPAEN10DBMMAINCTAP_SHIFT                             20                                                /**< Shift value for RAC_TXPAEN10DBMMAINCTAP     */
#define _RAC_TX_TXPAEN10DBMMAINCTAP_MASK                              0x100000UL                                        /**< Bit mask for RAC_TXPAEN10DBMMAINCTAP        */
#define _RAC_TX_TXPAEN10DBMMAINCTAP_DEFAULT                           0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TXPAEN10DBMMAINCTAP_ctap_main_dis                     0x00000000UL                                      /**< Mode ctap_main_dis for RAC_TX               */
#define _RAC_TX_TXPAEN10DBMMAINCTAP_ctap_main_en                      0x00000001UL                                      /**< Mode ctap_main_en for RAC_TX                */
#define RAC_TX_TXPAEN10DBMMAINCTAP_DEFAULT                            (_RAC_TX_TXPAEN10DBMMAINCTAP_DEFAULT << 20)       /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TXPAEN10DBMMAINCTAP_ctap_main_dis                      (_RAC_TX_TXPAEN10DBMMAINCTAP_ctap_main_dis << 20) /**< Shifted mode ctap_main_dis for RAC_TX       */
#define RAC_TX_TXPAEN10DBMMAINCTAP_ctap_main_en                       (_RAC_TX_TXPAEN10DBMMAINCTAP_ctap_main_en << 20)  /**< Shifted mode ctap_main_en for RAC_TX        */
#define RAC_TX_TXPAEN10DBMPREDRV                                      (0x1UL << 21)                                     /**< TXPAEN10DBMPREDRV                           */
#define _RAC_TX_TXPAEN10DBMPREDRV_SHIFT                               21                                                /**< Shift value for RAC_TXPAEN10DBMPREDRV       */
#define _RAC_TX_TXPAEN10DBMPREDRV_MASK                                0x200000UL                                        /**< Bit mask for RAC_TXPAEN10DBMPREDRV          */
#define _RAC_TX_TXPAEN10DBMPREDRV_DEFAULT                             0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TXPAEN10DBMPREDRV_disable                             0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TXPAEN10DBMPREDRV_enable                              0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TXPAEN10DBMPREDRV_DEFAULT                              (_RAC_TX_TXPAEN10DBMPREDRV_DEFAULT << 21)         /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TXPAEN10DBMPREDRV_disable                              (_RAC_TX_TXPAEN10DBMPREDRV_disable << 21)         /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TXPAEN10DBMPREDRV_enable                               (_RAC_TX_TXPAEN10DBMPREDRV_enable << 21)          /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TXPAEN10DBMVMID                                        (0x1UL << 22)                                     /**< TXPAEN10DBMVMID                             */
#define _RAC_TX_TXPAEN10DBMVMID_SHIFT                                 22                                                /**< Shift value for RAC_TXPAEN10DBMVMID         */
#define _RAC_TX_TXPAEN10DBMVMID_MASK                                  0x400000UL                                        /**< Bit mask for RAC_TXPAEN10DBMVMID            */
#define _RAC_TX_TXPAEN10DBMVMID_DEFAULT                               0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TXPAEN10DBMVMID_disable                               0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TXPAEN10DBMVMID_enable                                0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TXPAEN10DBMVMID_DEFAULT                                (_RAC_TX_TXPAEN10DBMVMID_DEFAULT << 22)           /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TXPAEN10DBMVMID_disable                                (_RAC_TX_TXPAEN10DBMVMID_disable << 22)           /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TXPAEN10DBMVMID_enable                                 (_RAC_TX_TXPAEN10DBMVMID_enable << 22)            /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TXPAEN20DBM                                            (0x1UL << 23)                                     /**< TXPAEN20DBM                                 */
#define _RAC_TX_TXPAEN20DBM_SHIFT                                     23                                                /**< Shift value for RAC_TXPAEN20DBM             */
#define _RAC_TX_TXPAEN20DBM_MASK                                      0x800000UL                                        /**< Bit mask for RAC_TXPAEN20DBM                */
#define _RAC_TX_TXPAEN20DBM_DEFAULT                                   0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TXPAEN20DBM_disable                                   0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TXPAEN20DBM_enable                                    0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TXPAEN20DBM_DEFAULT                                    (_RAC_TX_TXPAEN20DBM_DEFAULT << 23)               /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TXPAEN20DBM_disable                                    (_RAC_TX_TXPAEN20DBM_disable << 23)               /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TXPAEN20DBM_enable                                     (_RAC_TX_TXPAEN20DBM_enable << 23)                /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TXPAEN20DBMMAINCTAP                                    (0x1UL << 24)                                     /**< TXPAEN20DBMMAINCTAP                         */
#define _RAC_TX_TXPAEN20DBMMAINCTAP_SHIFT                             24                                                /**< Shift value for RAC_TXPAEN20DBMMAINCTAP     */
#define _RAC_TX_TXPAEN20DBMMAINCTAP_MASK                              0x1000000UL                                       /**< Bit mask for RAC_TXPAEN20DBMMAINCTAP        */
#define _RAC_TX_TXPAEN20DBMMAINCTAP_DEFAULT                           0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TXPAEN20DBMMAINCTAP_ctap_main_dis                     0x00000000UL                                      /**< Mode ctap_main_dis for RAC_TX               */
#define _RAC_TX_TXPAEN20DBMMAINCTAP_ctap_main_en                      0x00000001UL                                      /**< Mode ctap_main_en for RAC_TX                */
#define RAC_TX_TXPAEN20DBMMAINCTAP_DEFAULT                            (_RAC_TX_TXPAEN20DBMMAINCTAP_DEFAULT << 24)       /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TXPAEN20DBMMAINCTAP_ctap_main_dis                      (_RAC_TX_TXPAEN20DBMMAINCTAP_ctap_main_dis << 24) /**< Shifted mode ctap_main_dis for RAC_TX       */
#define RAC_TX_TXPAEN20DBMMAINCTAP_ctap_main_en                       (_RAC_TX_TXPAEN20DBMMAINCTAP_ctap_main_en << 24)  /**< Shifted mode ctap_main_en for RAC_TX        */
#define RAC_TX_TXPAEN20DBMPREDRV                                      (0x1UL << 25)                                     /**< TXPAEN20DBMPREDRV                           */
#define _RAC_TX_TXPAEN20DBMPREDRV_SHIFT                               25                                                /**< Shift value for RAC_TXPAEN20DBMPREDRV       */
#define _RAC_TX_TXPAEN20DBMPREDRV_MASK                                0x2000000UL                                       /**< Bit mask for RAC_TXPAEN20DBMPREDRV          */
#define _RAC_TX_TXPAEN20DBMPREDRV_DEFAULT                             0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TXPAEN20DBMPREDRV_disable                             0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TXPAEN20DBMPREDRV_enable                              0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TXPAEN20DBMPREDRV_DEFAULT                              (_RAC_TX_TXPAEN20DBMPREDRV_DEFAULT << 25)         /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TXPAEN20DBMPREDRV_disable                              (_RAC_TX_TXPAEN20DBMPREDRV_disable << 25)         /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TXPAEN20DBMPREDRV_enable                               (_RAC_TX_TXPAEN20DBMPREDRV_enable << 25)          /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TXPAEN20DBMVMID                                        (0x1UL << 26)                                     /**< TXPAEN20DBMVMID                             */
#define _RAC_TX_TXPAEN20DBMVMID_SHIFT                                 26                                                /**< Shift value for RAC_TXPAEN20DBMVMID         */
#define _RAC_TX_TXPAEN20DBMVMID_MASK                                  0x4000000UL                                       /**< Bit mask for RAC_TXPAEN20DBMVMID            */
#define _RAC_TX_TXPAEN20DBMVMID_DEFAULT                               0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TXPAEN20DBMVMID_disable                               0x00000000UL                                      /**< Mode disable for RAC_TX                     */
#define _RAC_TX_TXPAEN20DBMVMID_enable                                0x00000001UL                                      /**< Mode enable for RAC_TX                      */
#define RAC_TX_TXPAEN20DBMVMID_DEFAULT                                (_RAC_TX_TXPAEN20DBMVMID_DEFAULT << 26)           /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TXPAEN20DBMVMID_disable                                (_RAC_TX_TXPAEN20DBMVMID_disable << 26)           /**< Shifted mode disable for RAC_TX             */
#define RAC_TX_TXPAEN20DBMVMID_enable                                 (_RAC_TX_TXPAEN20DBMVMID_enable << 26)            /**< Shifted mode enable for RAC_TX              */
#define RAC_TX_TXPAEN20DBMVBIASHF                                     (0x1UL << 27)                                     /**< TXPAEN20DBMVBIASHF                          */
#define _RAC_TX_TXPAEN20DBMVBIASHF_SHIFT                              27                                                /**< Shift value for RAC_TXPAEN20DBMVBIASHF      */
#define _RAC_TX_TXPAEN20DBMVBIASHF_MASK                               0x8000000UL                                       /**< Bit mask for RAC_TXPAEN20DBMVBIASHF         */
#define _RAC_TX_TXPAEN20DBMVBIASHF_DEFAULT                            0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TXPAEN20DBMVBIASHF_disable_bias                       0x00000000UL                                      /**< Mode disable_bias for RAC_TX                */
#define _RAC_TX_TXPAEN20DBMVBIASHF_enable_bias                        0x00000001UL                                      /**< Mode enable_bias for RAC_TX                 */
#define RAC_TX_TXPAEN20DBMVBIASHF_DEFAULT                             (_RAC_TX_TXPAEN20DBMVBIASHF_DEFAULT << 27)        /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TXPAEN20DBMVBIASHF_disable_bias                        (_RAC_TX_TXPAEN20DBMVBIASHF_disable_bias << 27)   /**< Shifted mode disable_bias for RAC_TX        */
#define RAC_TX_TXPAEN20DBMVBIASHF_enable_bias                         (_RAC_TX_TXPAEN20DBMVBIASHF_enable_bias << 27)    /**< Shifted mode enable_bias for RAC_TX         */
#define _RAC_TX_TXPATRIM20DBMVBIASHF_SHIFT                            28                                                /**< Shift value for RAC_TXPATRIM20DBMVBIASHF    */
#define _RAC_TX_TXPATRIM20DBMVBIASHF_MASK                             0x30000000UL                                      /**< Bit mask for RAC_TXPATRIM20DBMVBIASHF       */
#define _RAC_TX_TXPATRIM20DBMVBIASHF_DEFAULT                          0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define _RAC_TX_TXPATRIM20DBMVBIASHF_bias_avss                        0x00000000UL                                      /**< Mode bias_avss for RAC_TX                   */
#define _RAC_TX_TXPATRIM20DBMVBIASHF_bias_low                         0x00000001UL                                      /**< Mode bias_low for RAC_TX                    */
#define _RAC_TX_TXPATRIM20DBMVBIASHF_bias_mid                         0x00000002UL                                      /**< Mode bias_mid for RAC_TX                    */
#define _RAC_TX_TXPATRIM20DBMVBIASHF_bias_high                        0x00000003UL                                      /**< Mode bias_high for RAC_TX                   */
#define RAC_TX_TXPATRIM20DBMVBIASHF_DEFAULT                           (_RAC_TX_TXPATRIM20DBMVBIASHF_DEFAULT << 28)      /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_TXPATRIM20DBMVBIASHF_bias_avss                         (_RAC_TX_TXPATRIM20DBMVBIASHF_bias_avss << 28)    /**< Shifted mode bias_avss for RAC_TX           */
#define RAC_TX_TXPATRIM20DBMVBIASHF_bias_low                          (_RAC_TX_TXPATRIM20DBMVBIASHF_bias_low << 28)     /**< Shifted mode bias_low for RAC_TX            */
#define RAC_TX_TXPATRIM20DBMVBIASHF_bias_mid                          (_RAC_TX_TXPATRIM20DBMVBIASHF_bias_mid << 28)     /**< Shifted mode bias_mid for RAC_TX            */
#define RAC_TX_TXPATRIM20DBMVBIASHF_bias_high                         (_RAC_TX_TXPATRIM20DBMVBIASHF_bias_high << 28)    /**< Shifted mode bias_high for RAC_TX           */
#define RAC_TX_ENPAPOWER                                              (0x1UL << 30)                                     /**< Override                                    */
#define _RAC_TX_ENPAPOWER_SHIFT                                       30                                                /**< Shift value for RAC_ENPAPOWER               */
#define _RAC_TX_ENPAPOWER_MASK                                        0x40000000UL                                      /**< Bit mask for RAC_ENPAPOWER                  */
#define _RAC_TX_ENPAPOWER_DEFAULT                                     0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define RAC_TX_ENPAPOWER_DEFAULT                                      (_RAC_TX_ENPAPOWER_DEFAULT << 30)                 /**< Shifted mode DEFAULT for RAC_TX             */
#define RAC_TX_ENPASELSLICE                                           (0x1UL << 31)                                     /**< Override                                    */
#define _RAC_TX_ENPASELSLICE_SHIFT                                    31                                                /**< Shift value for RAC_ENPASELSLICE            */
#define _RAC_TX_ENPASELSLICE_MASK                                     0x80000000UL                                      /**< Bit mask for RAC_ENPASELSLICE               */
#define _RAC_TX_ENPASELSLICE_DEFAULT                                  0x00000000UL                                      /**< Mode DEFAULT for RAC_TX                     */
#define RAC_TX_ENPASELSLICE_DEFAULT                                   (_RAC_TX_ENPASELSLICE_DEFAULT << 31)              /**< Shifted mode DEFAULT for RAC_TX             */

/* Bit fields for RAC SYTRIM0 */
#define _RAC_SYTRIM0_RESETVALUE                                       0x018FF169UL                                       /**< Default value for RAC_SYTRIM0               */
#define _RAC_SYTRIM0_MASK                                             0x0FFFFFFFUL                                       /**< Mask for RAC_SYTRIM0                        */
#define _RAC_SYTRIM0_SYCHPBIAS_SHIFT                                  0                                                  /**< Shift value for RAC_SYCHPBIAS               */
#define _RAC_SYTRIM0_SYCHPBIAS_MASK                                   0x7UL                                              /**< Bit mask for RAC_SYCHPBIAS                  */
#define _RAC_SYTRIM0_SYCHPBIAS_DEFAULT                                0x00000001UL                                       /**< Mode DEFAULT for RAC_SYTRIM0                */
#define _RAC_SYTRIM0_SYCHPBIAS_bias_0                                 0x00000000UL                                       /**< Mode bias_0 for RAC_SYTRIM0                 */
#define _RAC_SYTRIM0_SYCHPBIAS_bias_1                                 0x00000001UL                                       /**< Mode bias_1 for RAC_SYTRIM0                 */
#define _RAC_SYTRIM0_SYCHPBIAS_bias_2                                 0x00000003UL                                       /**< Mode bias_2 for RAC_SYTRIM0                 */
#define _RAC_SYTRIM0_SYCHPBIAS_bias_3                                 0x00000007UL                                       /**< Mode bias_3 for RAC_SYTRIM0                 */
#define RAC_SYTRIM0_SYCHPBIAS_DEFAULT                                 (_RAC_SYTRIM0_SYCHPBIAS_DEFAULT << 0)              /**< Shifted mode DEFAULT for RAC_SYTRIM0        */
#define RAC_SYTRIM0_SYCHPBIAS_bias_0                                  (_RAC_SYTRIM0_SYCHPBIAS_bias_0 << 0)               /**< Shifted mode bias_0 for RAC_SYTRIM0         */
#define RAC_SYTRIM0_SYCHPBIAS_bias_1                                  (_RAC_SYTRIM0_SYCHPBIAS_bias_1 << 0)               /**< Shifted mode bias_1 for RAC_SYTRIM0         */
#define RAC_SYTRIM0_SYCHPBIAS_bias_2                                  (_RAC_SYTRIM0_SYCHPBIAS_bias_2 << 0)               /**< Shifted mode bias_2 for RAC_SYTRIM0         */
#define RAC_SYTRIM0_SYCHPBIAS_bias_3                                  (_RAC_SYTRIM0_SYCHPBIAS_bias_3 << 0)               /**< Shifted mode bias_3 for RAC_SYTRIM0         */
#define _RAC_SYTRIM0_SYCHPCURRRX_SHIFT                                3                                                  /**< Shift value for RAC_SYCHPCURRRX             */
#define _RAC_SYTRIM0_SYCHPCURRRX_MASK                                 0x38UL                                             /**< Bit mask for RAC_SYCHPCURRRX                */
#define _RAC_SYTRIM0_SYCHPCURRRX_DEFAULT                              0x00000005UL                                       /**< Mode DEFAULT for RAC_SYTRIM0                */
#define _RAC_SYTRIM0_SYCHPCURRRX_curr_1p5uA                           0x00000000UL                                       /**< Mode curr_1p5uA for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPCURRRX_curr_2p0uA                           0x00000001UL                                       /**< Mode curr_2p0uA for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPCURRRX_curr_2p5uA                           0x00000002UL                                       /**< Mode curr_2p5uA for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPCURRRX_curr_3p0uA                           0x00000003UL                                       /**< Mode curr_3p0uA for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPCURRRX_curr_3p5uA                           0x00000004UL                                       /**< Mode curr_3p5uA for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPCURRRX_curr_4p0uA                           0x00000005UL                                       /**< Mode curr_4p0uA for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPCURRRX_curr_4p5uA                           0x00000006UL                                       /**< Mode curr_4p5uA for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPCURRRX_curr_5p0uA                           0x00000007UL                                       /**< Mode curr_5p0uA for RAC_SYTRIM0             */
#define RAC_SYTRIM0_SYCHPCURRRX_DEFAULT                               (_RAC_SYTRIM0_SYCHPCURRRX_DEFAULT << 3)            /**< Shifted mode DEFAULT for RAC_SYTRIM0        */
#define RAC_SYTRIM0_SYCHPCURRRX_curr_1p5uA                            (_RAC_SYTRIM0_SYCHPCURRRX_curr_1p5uA << 3)         /**< Shifted mode curr_1p5uA for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPCURRRX_curr_2p0uA                            (_RAC_SYTRIM0_SYCHPCURRRX_curr_2p0uA << 3)         /**< Shifted mode curr_2p0uA for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPCURRRX_curr_2p5uA                            (_RAC_SYTRIM0_SYCHPCURRRX_curr_2p5uA << 3)         /**< Shifted mode curr_2p5uA for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPCURRRX_curr_3p0uA                            (_RAC_SYTRIM0_SYCHPCURRRX_curr_3p0uA << 3)         /**< Shifted mode curr_3p0uA for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPCURRRX_curr_3p5uA                            (_RAC_SYTRIM0_SYCHPCURRRX_curr_3p5uA << 3)         /**< Shifted mode curr_3p5uA for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPCURRRX_curr_4p0uA                            (_RAC_SYTRIM0_SYCHPCURRRX_curr_4p0uA << 3)         /**< Shifted mode curr_4p0uA for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPCURRRX_curr_4p5uA                            (_RAC_SYTRIM0_SYCHPCURRRX_curr_4p5uA << 3)         /**< Shifted mode curr_4p5uA for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPCURRRX_curr_5p0uA                            (_RAC_SYTRIM0_SYCHPCURRRX_curr_5p0uA << 3)         /**< Shifted mode curr_5p0uA for RAC_SYTRIM0     */
#define _RAC_SYTRIM0_SYCHPCURRTX_SHIFT                                6                                                  /**< Shift value for RAC_SYCHPCURRTX             */
#define _RAC_SYTRIM0_SYCHPCURRTX_MASK                                 0x1C0UL                                            /**< Bit mask for RAC_SYCHPCURRTX                */
#define _RAC_SYTRIM0_SYCHPCURRTX_DEFAULT                              0x00000005UL                                       /**< Mode DEFAULT for RAC_SYTRIM0                */
#define _RAC_SYTRIM0_SYCHPCURRTX_curr_1p5uA                           0x00000000UL                                       /**< Mode curr_1p5uA for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPCURRTX_curr_2p0uA                           0x00000001UL                                       /**< Mode curr_2p0uA for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPCURRTX_curr_2p5uA                           0x00000002UL                                       /**< Mode curr_2p5uA for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPCURRTX_curr_3p0uA                           0x00000003UL                                       /**< Mode curr_3p0uA for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPCURRTX_curr_3p5uA                           0x00000004UL                                       /**< Mode curr_3p5uA for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPCURRTX_curr_4p0uA                           0x00000005UL                                       /**< Mode curr_4p0uA for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPCURRTX_curr_4p5uA                           0x00000006UL                                       /**< Mode curr_4p5uA for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPCURRTX_curr_5p0uA                           0x00000007UL                                       /**< Mode curr_5p0uA for RAC_SYTRIM0             */
#define RAC_SYTRIM0_SYCHPCURRTX_DEFAULT                               (_RAC_SYTRIM0_SYCHPCURRTX_DEFAULT << 6)            /**< Shifted mode DEFAULT for RAC_SYTRIM0        */
#define RAC_SYTRIM0_SYCHPCURRTX_curr_1p5uA                            (_RAC_SYTRIM0_SYCHPCURRTX_curr_1p5uA << 6)         /**< Shifted mode curr_1p5uA for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPCURRTX_curr_2p0uA                            (_RAC_SYTRIM0_SYCHPCURRTX_curr_2p0uA << 6)         /**< Shifted mode curr_2p0uA for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPCURRTX_curr_2p5uA                            (_RAC_SYTRIM0_SYCHPCURRTX_curr_2p5uA << 6)         /**< Shifted mode curr_2p5uA for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPCURRTX_curr_3p0uA                            (_RAC_SYTRIM0_SYCHPCURRTX_curr_3p0uA << 6)         /**< Shifted mode curr_3p0uA for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPCURRTX_curr_3p5uA                            (_RAC_SYTRIM0_SYCHPCURRTX_curr_3p5uA << 6)         /**< Shifted mode curr_3p5uA for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPCURRTX_curr_4p0uA                            (_RAC_SYTRIM0_SYCHPCURRTX_curr_4p0uA << 6)         /**< Shifted mode curr_4p0uA for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPCURRTX_curr_4p5uA                            (_RAC_SYTRIM0_SYCHPCURRTX_curr_4p5uA << 6)         /**< Shifted mode curr_4p5uA for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPCURRTX_curr_5p0uA                            (_RAC_SYTRIM0_SYCHPCURRTX_curr_5p0uA << 6)         /**< Shifted mode curr_5p0uA for RAC_SYTRIM0     */
#define _RAC_SYTRIM0_SYCHPLEVNSRC_SHIFT                               9                                                  /**< Shift value for RAC_SYCHPLEVNSRC            */
#define _RAC_SYTRIM0_SYCHPLEVNSRC_MASK                                0xE00UL                                            /**< Bit mask for RAC_SYCHPLEVNSRC               */
#define _RAC_SYTRIM0_SYCHPLEVNSRC_DEFAULT                             0x00000000UL                                       /**< Mode DEFAULT for RAC_SYTRIM0                */
#define RAC_SYTRIM0_SYCHPLEVNSRC_DEFAULT                              (_RAC_SYTRIM0_SYCHPLEVNSRC_DEFAULT << 9)           /**< Shifted mode DEFAULT for RAC_SYTRIM0        */
#define _RAC_SYTRIM0_SYCHPLEVPSRCRX_SHIFT                             12                                                 /**< Shift value for RAC_SYCHPLEVPSRCRX          */
#define _RAC_SYTRIM0_SYCHPLEVPSRCRX_MASK                              0x7000UL                                           /**< Bit mask for RAC_SYCHPLEVPSRCRX             */
#define _RAC_SYTRIM0_SYCHPLEVPSRCRX_DEFAULT                           0x00000007UL                                       /**< Mode DEFAULT for RAC_SYTRIM0                */
#define _RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n105m                       0x00000000UL                                       /**< Mode vsrcp_n105m for RAC_SYTRIM0            */
#define _RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n90m                        0x00000001UL                                       /**< Mode vsrcp_n90m for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n75m                        0x00000002UL                                       /**< Mode vsrcp_n75m for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n60m                        0x00000003UL                                       /**< Mode vsrcp_n60m for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n45m                        0x00000004UL                                       /**< Mode vsrcp_n45m for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n30m                        0x00000005UL                                       /**< Mode vsrcp_n30m for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n15m                        0x00000006UL                                       /**< Mode vsrcp_n15m for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n0m                         0x00000007UL                                       /**< Mode vsrcp_n0m for RAC_SYTRIM0              */
#define RAC_SYTRIM0_SYCHPLEVPSRCRX_DEFAULT                            (_RAC_SYTRIM0_SYCHPLEVPSRCRX_DEFAULT << 12)        /**< Shifted mode DEFAULT for RAC_SYTRIM0        */
#define RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n105m                        (_RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n105m << 12)    /**< Shifted mode vsrcp_n105m for RAC_SYTRIM0    */
#define RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n90m                         (_RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n90m << 12)     /**< Shifted mode vsrcp_n90m for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n75m                         (_RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n75m << 12)     /**< Shifted mode vsrcp_n75m for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n60m                         (_RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n60m << 12)     /**< Shifted mode vsrcp_n60m for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n45m                         (_RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n45m << 12)     /**< Shifted mode vsrcp_n45m for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n30m                         (_RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n30m << 12)     /**< Shifted mode vsrcp_n30m for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n15m                         (_RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n15m << 12)     /**< Shifted mode vsrcp_n15m for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n0m                          (_RAC_SYTRIM0_SYCHPLEVPSRCRX_vsrcp_n0m << 12)      /**< Shifted mode vsrcp_n0m for RAC_SYTRIM0      */
#define _RAC_SYTRIM0_SYCHPLEVPSRCTX_SHIFT                             15                                                 /**< Shift value for RAC_SYCHPLEVPSRCTX          */
#define _RAC_SYTRIM0_SYCHPLEVPSRCTX_MASK                              0x38000UL                                          /**< Bit mask for RAC_SYCHPLEVPSRCTX             */
#define _RAC_SYTRIM0_SYCHPLEVPSRCTX_DEFAULT                           0x00000007UL                                       /**< Mode DEFAULT for RAC_SYTRIM0                */
#define _RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n105m                       0x00000000UL                                       /**< Mode vsrcp_n105m for RAC_SYTRIM0            */
#define _RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n90m                        0x00000001UL                                       /**< Mode vsrcp_n90m for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n75m                        0x00000002UL                                       /**< Mode vsrcp_n75m for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n60m                        0x00000003UL                                       /**< Mode vsrcp_n60m for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n45m                        0x00000004UL                                       /**< Mode vsrcp_n45m for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n30m                        0x00000005UL                                       /**< Mode vsrcp_n30m for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n15m                        0x00000006UL                                       /**< Mode vsrcp_n15m for RAC_SYTRIM0             */
#define _RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n0m                         0x00000007UL                                       /**< Mode vsrcp_n0m for RAC_SYTRIM0              */
#define RAC_SYTRIM0_SYCHPLEVPSRCTX_DEFAULT                            (_RAC_SYTRIM0_SYCHPLEVPSRCTX_DEFAULT << 15)        /**< Shifted mode DEFAULT for RAC_SYTRIM0        */
#define RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n105m                        (_RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n105m << 15)    /**< Shifted mode vsrcp_n105m for RAC_SYTRIM0    */
#define RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n90m                         (_RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n90m << 15)     /**< Shifted mode vsrcp_n90m for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n75m                         (_RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n75m << 15)     /**< Shifted mode vsrcp_n75m for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n60m                         (_RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n60m << 15)     /**< Shifted mode vsrcp_n60m for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n45m                         (_RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n45m << 15)     /**< Shifted mode vsrcp_n45m for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n30m                         (_RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n30m << 15)     /**< Shifted mode vsrcp_n30m for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n15m                         (_RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n15m << 15)     /**< Shifted mode vsrcp_n15m for RAC_SYTRIM0     */
#define RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n0m                          (_RAC_SYTRIM0_SYCHPLEVPSRCTX_vsrcp_n0m << 15)      /**< Shifted mode vsrcp_n0m for RAC_SYTRIM0      */
#define RAC_SYTRIM0_SYCHPSRCENRX                                      (0x1UL << 18)                                      /**< SYCHPSRCENRX                                */
#define _RAC_SYTRIM0_SYCHPSRCENRX_SHIFT                               18                                                 /**< Shift value for RAC_SYCHPSRCENRX            */
#define _RAC_SYTRIM0_SYCHPSRCENRX_MASK                                0x40000UL                                          /**< Bit mask for RAC_SYCHPSRCENRX               */
#define _RAC_SYTRIM0_SYCHPSRCENRX_DEFAULT                             0x00000001UL                                       /**< Mode DEFAULT for RAC_SYTRIM0                */
#define _RAC_SYTRIM0_SYCHPSRCENRX_disable                             0x00000000UL                                       /**< Mode disable for RAC_SYTRIM0                */
#define _RAC_SYTRIM0_SYCHPSRCENRX_enable                              0x00000001UL                                       /**< Mode enable for RAC_SYTRIM0                 */
#define RAC_SYTRIM0_SYCHPSRCENRX_DEFAULT                              (_RAC_SYTRIM0_SYCHPSRCENRX_DEFAULT << 18)          /**< Shifted mode DEFAULT for RAC_SYTRIM0        */
#define RAC_SYTRIM0_SYCHPSRCENRX_disable                              (_RAC_SYTRIM0_SYCHPSRCENRX_disable << 18)          /**< Shifted mode disable for RAC_SYTRIM0        */
#define RAC_SYTRIM0_SYCHPSRCENRX_enable                               (_RAC_SYTRIM0_SYCHPSRCENRX_enable << 18)           /**< Shifted mode enable for RAC_SYTRIM0         */
#define RAC_SYTRIM0_SYCHPSRCENTX                                      (0x1UL << 19)                                      /**< SYCHPSRCENTX                                */
#define _RAC_SYTRIM0_SYCHPSRCENTX_SHIFT                               19                                                 /**< Shift value for RAC_SYCHPSRCENTX            */
#define _RAC_SYTRIM0_SYCHPSRCENTX_MASK                                0x80000UL                                          /**< Bit mask for RAC_SYCHPSRCENTX               */
#define _RAC_SYTRIM0_SYCHPSRCENTX_DEFAULT                             0x00000001UL                                       /**< Mode DEFAULT for RAC_SYTRIM0                */
#define _RAC_SYTRIM0_SYCHPSRCENTX_disable                             0x00000000UL                                       /**< Mode disable for RAC_SYTRIM0                */
#define _RAC_SYTRIM0_SYCHPSRCENTX_enable                              0x00000001UL                                       /**< Mode enable for RAC_SYTRIM0                 */
#define RAC_SYTRIM0_SYCHPSRCENTX_DEFAULT                              (_RAC_SYTRIM0_SYCHPSRCENTX_DEFAULT << 19)          /**< Shifted mode DEFAULT for RAC_SYTRIM0        */
#define RAC_SYTRIM0_SYCHPSRCENTX_disable                              (_RAC_SYTRIM0_SYCHPSRCENTX_disable << 19)          /**< Shifted mode disable for RAC_SYTRIM0        */
#define RAC_SYTRIM0_SYCHPSRCENTX_enable                               (_RAC_SYTRIM0_SYCHPSRCENTX_enable << 19)           /**< Shifted mode enable for RAC_SYTRIM0         */
#define _RAC_SYTRIM0_SYCHPREPLICACURRADJ_SHIFT                        20                                                 /**< Shift value for RAC_SYCHPREPLICACURRADJ     */
#define _RAC_SYTRIM0_SYCHPREPLICACURRADJ_MASK                         0x700000UL                                         /**< Bit mask for RAC_SYCHPREPLICACURRADJ        */
#define _RAC_SYTRIM0_SYCHPREPLICACURRADJ_DEFAULT                      0x00000000UL                                       /**< Mode DEFAULT for RAC_SYTRIM0                */
#define _RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_8ua                     0x00000000UL                                       /**< Mode load_8ua for RAC_SYTRIM0               */
#define _RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_16ua                    0x00000001UL                                       /**< Mode load_16ua for RAC_SYTRIM0              */
#define _RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_20ua                    0x00000002UL                                       /**< Mode load_20ua for RAC_SYTRIM0              */
#define _RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_28ua                    0x00000003UL                                       /**< Mode load_28ua for RAC_SYTRIM0              */
#define _RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_24ua                    0x00000004UL                                       /**< Mode load_24ua for RAC_SYTRIM0              */
#define _RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_32ua                    0x00000005UL                                       /**< Mode load_32ua for RAC_SYTRIM0              */
#define _RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_36ua                    0x00000006UL                                       /**< Mode load_36ua for RAC_SYTRIM0              */
#define _RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_44ua                    0x00000007UL                                       /**< Mode load_44ua for RAC_SYTRIM0              */
#define RAC_SYTRIM0_SYCHPREPLICACURRADJ_DEFAULT                       (_RAC_SYTRIM0_SYCHPREPLICACURRADJ_DEFAULT << 20)   /**< Shifted mode DEFAULT for RAC_SYTRIM0        */
#define RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_8ua                      (_RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_8ua << 20)  /**< Shifted mode load_8ua for RAC_SYTRIM0       */
#define RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_16ua                     (_RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_16ua << 20) /**< Shifted mode load_16ua for RAC_SYTRIM0      */
#define RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_20ua                     (_RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_20ua << 20) /**< Shifted mode load_20ua for RAC_SYTRIM0      */
#define RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_28ua                     (_RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_28ua << 20) /**< Shifted mode load_28ua for RAC_SYTRIM0      */
#define RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_24ua                     (_RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_24ua << 20) /**< Shifted mode load_24ua for RAC_SYTRIM0      */
#define RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_32ua                     (_RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_32ua << 20) /**< Shifted mode load_32ua for RAC_SYTRIM0      */
#define RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_36ua                     (_RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_36ua << 20) /**< Shifted mode load_36ua for RAC_SYTRIM0      */
#define RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_44ua                     (_RAC_SYTRIM0_SYCHPREPLICACURRADJ_load_44ua << 20) /**< Shifted mode load_44ua for RAC_SYTRIM0      */
#define _RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_SHIFT                        23                                                 /**< Shift value for RAC_SYTRIMCHPREGAMPBIAS     */
#define _RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_MASK                         0x3800000UL                                        /**< Bit mask for RAC_SYTRIMCHPREGAMPBIAS        */
#define _RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_DEFAULT                      0x00000003UL                                       /**< Mode DEFAULT for RAC_SYTRIM0                */
#define _RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_14uA                    0x00000000UL                                       /**< Mode bias_14uA for RAC_SYTRIM0              */
#define _RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_20uA                    0x00000001UL                                       /**< Mode bias_20uA for RAC_SYTRIM0              */
#define _RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_26uA                    0x00000002UL                                       /**< Mode bias_26uA for RAC_SYTRIM0              */
#define _RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_32uA                    0x00000003UL                                       /**< Mode bias_32uA for RAC_SYTRIM0              */
#define _RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_38uA                    0x00000004UL                                       /**< Mode bias_38uA for RAC_SYTRIM0              */
#define _RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_44uA                    0x00000005UL                                       /**< Mode bias_44uA for RAC_SYTRIM0              */
#define _RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_50uA                    0x00000006UL                                       /**< Mode bias_50uA for RAC_SYTRIM0              */
#define _RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_56uA                    0x00000007UL                                       /**< Mode bias_56uA for RAC_SYTRIM0              */
#define RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_DEFAULT                       (_RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_DEFAULT << 23)   /**< Shifted mode DEFAULT for RAC_SYTRIM0        */
#define RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_14uA                     (_RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_14uA << 23) /**< Shifted mode bias_14uA for RAC_SYTRIM0      */
#define RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_20uA                     (_RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_20uA << 23) /**< Shifted mode bias_20uA for RAC_SYTRIM0      */
#define RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_26uA                     (_RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_26uA << 23) /**< Shifted mode bias_26uA for RAC_SYTRIM0      */
#define RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_32uA                     (_RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_32uA << 23) /**< Shifted mode bias_32uA for RAC_SYTRIM0      */
#define RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_38uA                     (_RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_38uA << 23) /**< Shifted mode bias_38uA for RAC_SYTRIM0      */
#define RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_44uA                     (_RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_44uA << 23) /**< Shifted mode bias_44uA for RAC_SYTRIM0      */
#define RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_50uA                     (_RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_50uA << 23) /**< Shifted mode bias_50uA for RAC_SYTRIM0      */
#define RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_56uA                     (_RAC_SYTRIM0_SYTRIMCHPREGAMPBIAS_bias_56uA << 23) /**< Shifted mode bias_56uA for RAC_SYTRIM0      */
#define _RAC_SYTRIM0_SYTRIMCHPREGAMPBW_SHIFT                          26                                                 /**< Shift value for RAC_SYTRIMCHPREGAMPBW       */
#define _RAC_SYTRIM0_SYTRIMCHPREGAMPBW_MASK                           0xC000000UL                                        /**< Bit mask for RAC_SYTRIMCHPREGAMPBW          */
#define _RAC_SYTRIM0_SYTRIMCHPREGAMPBW_DEFAULT                        0x00000000UL                                       /**< Mode DEFAULT for RAC_SYTRIM0                */
#define _RAC_SYTRIM0_SYTRIMCHPREGAMPBW_C_000f                         0x00000000UL                                       /**< Mode C_000f for RAC_SYTRIM0                 */
#define _RAC_SYTRIM0_SYTRIMCHPREGAMPBW_C_300f                         0x00000001UL                                       /**< Mode C_300f for RAC_SYTRIM0                 */
#define _RAC_SYTRIM0_SYTRIMCHPREGAMPBW_C_600f                         0x00000002UL                                       /**< Mode C_600f for RAC_SYTRIM0                 */
#define _RAC_SYTRIM0_SYTRIMCHPREGAMPBW_C_900f                         0x00000003UL                                       /**< Mode C_900f for RAC_SYTRIM0                 */
#define RAC_SYTRIM0_SYTRIMCHPREGAMPBW_DEFAULT                         (_RAC_SYTRIM0_SYTRIMCHPREGAMPBW_DEFAULT << 26)     /**< Shifted mode DEFAULT for RAC_SYTRIM0        */
#define RAC_SYTRIM0_SYTRIMCHPREGAMPBW_C_000f                          (_RAC_SYTRIM0_SYTRIMCHPREGAMPBW_C_000f << 26)      /**< Shifted mode C_000f for RAC_SYTRIM0         */
#define RAC_SYTRIM0_SYTRIMCHPREGAMPBW_C_300f                          (_RAC_SYTRIM0_SYTRIMCHPREGAMPBW_C_300f << 26)      /**< Shifted mode C_300f for RAC_SYTRIM0         */
#define RAC_SYTRIM0_SYTRIMCHPREGAMPBW_C_600f                          (_RAC_SYTRIM0_SYTRIMCHPREGAMPBW_C_600f << 26)      /**< Shifted mode C_600f for RAC_SYTRIM0         */
#define RAC_SYTRIM0_SYTRIMCHPREGAMPBW_C_900f                          (_RAC_SYTRIM0_SYTRIMCHPREGAMPBW_C_900f << 26)      /**< Shifted mode C_900f for RAC_SYTRIM0         */

/* Bit fields for RAC SYTRIM1 */
#define _RAC_SYTRIM1_RESETVALUE                                       0x1FE00410UL                                         /**< Default value for RAC_SYTRIM1               */
#define _RAC_SYTRIM1_MASK                                             0xFFFC0FFFUL                                         /**< Mask for RAC_SYTRIM1                        */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMCORERX_SHIFT                       0                                                    /**< Shift value for RAC_SYLODIVLDOTRIMCORERX    */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMCORERX_MASK                        0x3UL                                                /**< Bit mask for RAC_SYLODIVLDOTRIMCORERX       */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMCORERX_DEFAULT                     0x00000000UL                                         /**< Mode DEFAULT for RAC_SYTRIM1                */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMCORERX_RXLO                        0x00000000UL                                         /**< Mode RXLO for RAC_SYTRIM1                   */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMCORERX_TXLO                        0x00000003UL                                         /**< Mode TXLO for RAC_SYTRIM1                   */
#define RAC_SYTRIM1_SYLODIVLDOTRIMCORERX_DEFAULT                      (_RAC_SYTRIM1_SYLODIVLDOTRIMCORERX_DEFAULT << 0)     /**< Shifted mode DEFAULT for RAC_SYTRIM1        */
#define RAC_SYTRIM1_SYLODIVLDOTRIMCORERX_RXLO                         (_RAC_SYTRIM1_SYLODIVLDOTRIMCORERX_RXLO << 0)        /**< Shifted mode RXLO for RAC_SYTRIM1           */
#define RAC_SYTRIM1_SYLODIVLDOTRIMCORERX_TXLO                         (_RAC_SYTRIM1_SYLODIVLDOTRIMCORERX_TXLO << 0)        /**< Shifted mode TXLO for RAC_SYTRIM1           */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMCORETX_SHIFT                       2                                                    /**< Shift value for RAC_SYLODIVLDOTRIMCORETX    */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMCORETX_MASK                        0xCUL                                                /**< Bit mask for RAC_SYLODIVLDOTRIMCORETX       */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMCORETX_DEFAULT                     0x00000000UL                                         /**< Mode DEFAULT for RAC_SYTRIM1                */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMCORETX_RXLO                        0x00000000UL                                         /**< Mode RXLO for RAC_SYTRIM1                   */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMCORETX_TXLO                        0x00000003UL                                         /**< Mode TXLO for RAC_SYTRIM1                   */
#define RAC_SYTRIM1_SYLODIVLDOTRIMCORETX_DEFAULT                      (_RAC_SYTRIM1_SYLODIVLDOTRIMCORETX_DEFAULT << 2)     /**< Shifted mode DEFAULT for RAC_SYTRIM1        */
#define RAC_SYTRIM1_SYLODIVLDOTRIMCORETX_RXLO                         (_RAC_SYTRIM1_SYLODIVLDOTRIMCORETX_RXLO << 2)        /**< Shifted mode RXLO for RAC_SYTRIM1           */
#define RAC_SYTRIM1_SYLODIVLDOTRIMCORETX_TXLO                         (_RAC_SYTRIM1_SYLODIVLDOTRIMCORETX_TXLO << 2)        /**< Shifted mode TXLO for RAC_SYTRIM1           */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_SHIFT                       4                                                    /**< Shift value for RAC_SYLODIVLDOTRIMNDIORX    */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_MASK                        0xF0UL                                               /**< Bit mask for RAC_SYLODIVLDOTRIMNDIORX       */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_DEFAULT                     0x00000001UL                                         /**< Mode DEFAULT for RAC_SYTRIM1                */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p08                   0x00000000UL                                         /**< Mode vreg_1p08 for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p11                   0x00000001UL                                         /**< Mode vreg_1p11 for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p15                   0x00000002UL                                         /**< Mode vreg_1p15 for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p18                   0x00000003UL                                         /**< Mode vreg_1p18 for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p21                   0x00000004UL                                         /**< Mode vreg_1p21 for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p24                   0x00000005UL                                         /**< Mode vreg_1p24 for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p27                   0x00000006UL                                         /**< Mode vreg_1p27 for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p29                   0x00000007UL                                         /**< Mode vreg_1p29 for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p32                   0x00000008UL                                         /**< Mode vreg_1p32 for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p34                   0x00000009UL                                         /**< Mode vreg_1p34 for RAC_SYTRIM1              */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_DEFAULT                      (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_DEFAULT << 4)     /**< Shifted mode DEFAULT for RAC_SYTRIM1        */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p08                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p08 << 4)   /**< Shifted mode vreg_1p08 for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p11                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p11 << 4)   /**< Shifted mode vreg_1p11 for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p15                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p15 << 4)   /**< Shifted mode vreg_1p15 for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p18                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p18 << 4)   /**< Shifted mode vreg_1p18 for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p21                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p21 << 4)   /**< Shifted mode vreg_1p21 for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p24                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p24 << 4)   /**< Shifted mode vreg_1p24 for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p27                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p27 << 4)   /**< Shifted mode vreg_1p27 for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p29                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p29 << 4)   /**< Shifted mode vreg_1p29 for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p32                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p32 << 4)   /**< Shifted mode vreg_1p32 for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p34                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIORX_vreg_1p34 << 4)   /**< Shifted mode vreg_1p34 for RAC_SYTRIM1      */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_SHIFT                       8                                                    /**< Shift value for RAC_SYLODIVLDOTRIMNDIOTX    */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_MASK                        0xF00UL                                              /**< Bit mask for RAC_SYLODIVLDOTRIMNDIOTX       */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_DEFAULT                     0x00000004UL                                         /**< Mode DEFAULT for RAC_SYTRIM1                */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p08                   0x00000000UL                                         /**< Mode vreg_1p08 for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p11                   0x00000001UL                                         /**< Mode vreg_1p11 for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p15                   0x00000002UL                                         /**< Mode vreg_1p15 for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p18                   0x00000003UL                                         /**< Mode vreg_1p18 for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p21                   0x00000004UL                                         /**< Mode vreg_1p21 for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p24                   0x00000005UL                                         /**< Mode vreg_1p24 for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p27                   0x00000006UL                                         /**< Mode vreg_1p27 for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p29                   0x00000007UL                                         /**< Mode vreg_1p29 for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p32                   0x00000008UL                                         /**< Mode vreg_1p32 for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p34                   0x00000009UL                                         /**< Mode vreg_1p34 for RAC_SYTRIM1              */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_DEFAULT                      (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_DEFAULT << 8)     /**< Shifted mode DEFAULT for RAC_SYTRIM1        */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p08                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p08 << 8)   /**< Shifted mode vreg_1p08 for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p11                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p11 << 8)   /**< Shifted mode vreg_1p11 for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p15                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p15 << 8)   /**< Shifted mode vreg_1p15 for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p18                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p18 << 8)   /**< Shifted mode vreg_1p18 for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p21                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p21 << 8)   /**< Shifted mode vreg_1p21 for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p24                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p24 << 8)   /**< Shifted mode vreg_1p24 for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p27                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p27 << 8)   /**< Shifted mode vreg_1p27 for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p29                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p29 << 8)   /**< Shifted mode vreg_1p29 for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p32                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p32 << 8)   /**< Shifted mode vreg_1p32 for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p34                    (_RAC_SYTRIM1_SYLODIVLDOTRIMNDIOTX_vreg_1p34 << 8)   /**< Shifted mode vreg_1p34 for RAC_SYTRIM1      */
#define _RAC_SYTRIM1_SYLODIVTLO20DBM2G4DELAY_SHIFT                    18                                                   /**< Shift value for RAC_SYLODIVTLO20DBM2G4DELAY */
#define _RAC_SYTRIM1_SYLODIVTLO20DBM2G4DELAY_MASK                     0x1C0000UL                                           /**< Bit mask for RAC_SYLODIVTLO20DBM2G4DELAY    */
#define _RAC_SYTRIM1_SYLODIVTLO20DBM2G4DELAY_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for RAC_SYTRIM1                */
#define RAC_SYTRIM1_SYLODIVTLO20DBM2G4DELAY_DEFAULT                   (_RAC_SYTRIM1_SYLODIVTLO20DBM2G4DELAY_DEFAULT << 18) /**< Shifted mode DEFAULT for RAC_SYTRIM1        */
#define _RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_SHIFT                       21                                                   /**< Shift value for RAC_SYMMDREPLICA1CURRADJ    */
#define _RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_MASK                        0xE00000UL                                           /**< Bit mask for RAC_SYMMDREPLICA1CURRADJ       */
#define _RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_DEFAULT                     0x00000007UL                                         /**< Mode DEFAULT for RAC_SYTRIM1                */
#define _RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_8ua                    0x00000000UL                                         /**< Mode load_8ua for RAC_SYTRIM1               */
#define _RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_16u                    0x00000001UL                                         /**< Mode load_16u for RAC_SYTRIM1               */
#define _RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_20ua                   0x00000002UL                                         /**< Mode load_20ua for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_28ua                   0x00000003UL                                         /**< Mode load_28ua for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_24ua                   0x00000004UL                                         /**< Mode load_24ua for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_32ua                   0x00000005UL                                         /**< Mode load_32ua for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_36ua                   0x00000006UL                                         /**< Mode load_36ua for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_44ua                   0x00000007UL                                         /**< Mode load_44ua for RAC_SYTRIM1              */
#define RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_DEFAULT                      (_RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_DEFAULT << 21)    /**< Shifted mode DEFAULT for RAC_SYTRIM1        */
#define RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_8ua                     (_RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_8ua << 21)   /**< Shifted mode load_8ua for RAC_SYTRIM1       */
#define RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_16u                     (_RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_16u << 21)   /**< Shifted mode load_16u for RAC_SYTRIM1       */
#define RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_20ua                    (_RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_20ua << 21)  /**< Shifted mode load_20ua for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_28ua                    (_RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_28ua << 21)  /**< Shifted mode load_28ua for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_24ua                    (_RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_24ua << 21)  /**< Shifted mode load_24ua for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_32ua                    (_RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_32ua << 21)  /**< Shifted mode load_32ua for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_36ua                    (_RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_36ua << 21)  /**< Shifted mode load_36ua for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_44ua                    (_RAC_SYTRIM1_SYMMDREPLICA1CURRADJ_load_44ua << 21)  /**< Shifted mode load_44ua for RAC_SYTRIM1      */
#define _RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_SHIFT                       24                                                   /**< Shift value for RAC_SYMMDREPLICA2CURRADJ    */
#define _RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_MASK                        0x7000000UL                                          /**< Bit mask for RAC_SYMMDREPLICA2CURRADJ       */
#define _RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_DEFAULT                     0x00000007UL                                         /**< Mode DEFAULT for RAC_SYTRIM1                */
#define _RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_32u                    0x00000000UL                                         /**< Mode load_32u for RAC_SYTRIM1               */
#define _RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_64u                    0x00000001UL                                         /**< Mode load_64u for RAC_SYTRIM1               */
#define _RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_96u                    0x00000002UL                                         /**< Mode load_96u for RAC_SYTRIM1               */
#define _RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_128u                   0x00000003UL                                         /**< Mode load_128u for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_160u                   0x00000004UL                                         /**< Mode load_160u for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_192u                   0x00000005UL                                         /**< Mode load_192u for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_224u                   0x00000006UL                                         /**< Mode load_224u for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_256u                   0x00000007UL                                         /**< Mode load_256u for RAC_SYTRIM1              */
#define RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_DEFAULT                      (_RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_DEFAULT << 24)    /**< Shifted mode DEFAULT for RAC_SYTRIM1        */
#define RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_32u                     (_RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_32u << 24)   /**< Shifted mode load_32u for RAC_SYTRIM1       */
#define RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_64u                     (_RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_64u << 24)   /**< Shifted mode load_64u for RAC_SYTRIM1       */
#define RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_96u                     (_RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_96u << 24)   /**< Shifted mode load_96u for RAC_SYTRIM1       */
#define RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_128u                    (_RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_128u << 24)  /**< Shifted mode load_128u for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_160u                    (_RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_160u << 24)  /**< Shifted mode load_160u for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_192u                    (_RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_192u << 24)  /**< Shifted mode load_192u for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_224u                    (_RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_224u << 24)  /**< Shifted mode load_224u for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_256u                    (_RAC_SYTRIM1_SYMMDREPLICA2CURRADJ_load_256u << 24)  /**< Shifted mode load_256u for RAC_SYTRIM1      */
#define _RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_SHIFT                        27                                                   /**< Shift value for RAC_SYTRIMMMDREGAMPBIAS     */
#define _RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_MASK                         0x38000000UL                                         /**< Bit mask for RAC_SYTRIMMMDREGAMPBIAS        */
#define _RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_DEFAULT                      0x00000003UL                                         /**< Mode DEFAULT for RAC_SYTRIM1                */
#define _RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_14uA                    0x00000000UL                                         /**< Mode bias_14uA for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_20uA                    0x00000001UL                                         /**< Mode bias_20uA for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_26uA                    0x00000002UL                                         /**< Mode bias_26uA for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_32uA                    0x00000003UL                                         /**< Mode bias_32uA for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_38uA                    0x00000004UL                                         /**< Mode bias_38uA for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_44uA                    0x00000005UL                                         /**< Mode bias_44uA for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_50uA                    0x00000006UL                                         /**< Mode bias_50uA for RAC_SYTRIM1              */
#define _RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_56uA                    0x00000007UL                                         /**< Mode bias_56uA for RAC_SYTRIM1              */
#define RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_DEFAULT                       (_RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_DEFAULT << 27)     /**< Shifted mode DEFAULT for RAC_SYTRIM1        */
#define RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_14uA                     (_RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_14uA << 27)   /**< Shifted mode bias_14uA for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_20uA                     (_RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_20uA << 27)   /**< Shifted mode bias_20uA for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_26uA                     (_RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_26uA << 27)   /**< Shifted mode bias_26uA for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_32uA                     (_RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_32uA << 27)   /**< Shifted mode bias_32uA for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_38uA                     (_RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_38uA << 27)   /**< Shifted mode bias_38uA for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_44uA                     (_RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_44uA << 27)   /**< Shifted mode bias_44uA for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_50uA                     (_RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_50uA << 27)   /**< Shifted mode bias_50uA for RAC_SYTRIM1      */
#define RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_56uA                     (_RAC_SYTRIM1_SYTRIMMMDREGAMPBIAS_bias_56uA << 27)   /**< Shifted mode bias_56uA for RAC_SYTRIM1      */
#define _RAC_SYTRIM1_SYTRIMMMDREGAMPBW_SHIFT                          30                                                   /**< Shift value for RAC_SYTRIMMMDREGAMPBW       */
#define _RAC_SYTRIM1_SYTRIMMMDREGAMPBW_MASK                           0xC0000000UL                                         /**< Bit mask for RAC_SYTRIMMMDREGAMPBW          */
#define _RAC_SYTRIM1_SYTRIMMMDREGAMPBW_DEFAULT                        0x00000000UL                                         /**< Mode DEFAULT for RAC_SYTRIM1                */
#define _RAC_SYTRIM1_SYTRIMMMDREGAMPBW_C_000f                         0x00000000UL                                         /**< Mode C_000f for RAC_SYTRIM1                 */
#define _RAC_SYTRIM1_SYTRIMMMDREGAMPBW_C_300f                         0x00000001UL                                         /**< Mode C_300f for RAC_SYTRIM1                 */
#define _RAC_SYTRIM1_SYTRIMMMDREGAMPBW_C_600f                         0x00000002UL                                         /**< Mode C_600f for RAC_SYTRIM1                 */
#define _RAC_SYTRIM1_SYTRIMMMDREGAMPBW_C_900f                         0x00000003UL                                         /**< Mode C_900f for RAC_SYTRIM1                 */
#define RAC_SYTRIM1_SYTRIMMMDREGAMPBW_DEFAULT                         (_RAC_SYTRIM1_SYTRIMMMDREGAMPBW_DEFAULT << 30)       /**< Shifted mode DEFAULT for RAC_SYTRIM1        */
#define RAC_SYTRIM1_SYTRIMMMDREGAMPBW_C_000f                          (_RAC_SYTRIM1_SYTRIMMMDREGAMPBW_C_000f << 30)        /**< Shifted mode C_000f for RAC_SYTRIM1         */
#define RAC_SYTRIM1_SYTRIMMMDREGAMPBW_C_300f                          (_RAC_SYTRIM1_SYTRIMMMDREGAMPBW_C_300f << 30)        /**< Shifted mode C_300f for RAC_SYTRIM1         */
#define RAC_SYTRIM1_SYTRIMMMDREGAMPBW_C_600f                          (_RAC_SYTRIM1_SYTRIMMMDREGAMPBW_C_600f << 30)        /**< Shifted mode C_600f for RAC_SYTRIM1         */
#define RAC_SYTRIM1_SYTRIMMMDREGAMPBW_C_900f                          (_RAC_SYTRIM1_SYTRIMMMDREGAMPBW_C_900f << 30)        /**< Shifted mode C_900f for RAC_SYTRIM1         */

/* Bit fields for RAC SYCAL */
#define _RAC_SYCAL_RESETVALUE                                         0x01008100UL                                                /**< Default value for RAC_SYCAL                 */
#define _RAC_SYCAL_MASK                                               0x03018700UL                                                /**< Mask for RAC_SYCAL                          */
#define RAC_SYCAL_SYVCOMODEPKD                                        (0x1UL << 8)                                                /**< SYVCOMODEPKD                                */
#define _RAC_SYCAL_SYVCOMODEPKD_SHIFT                                 8                                                           /**< Shift value for RAC_SYVCOMODEPKD            */
#define _RAC_SYCAL_SYVCOMODEPKD_MASK                                  0x100UL                                                     /**< Bit mask for RAC_SYVCOMODEPKD               */
#define _RAC_SYCAL_SYVCOMODEPKD_DEFAULT                               0x00000001UL                                                /**< Mode DEFAULT for RAC_SYCAL                  */
#define _RAC_SYCAL_SYVCOMODEPKD_t_openloop_0                          0x00000000UL                                                /**< Mode t_openloop_0 for RAC_SYCAL             */
#define _RAC_SYCAL_SYVCOMODEPKD_t_pkdetect_1                          0x00000001UL                                                /**< Mode t_pkdetect_1 for RAC_SYCAL             */
#define RAC_SYCAL_SYVCOMODEPKD_DEFAULT                                (_RAC_SYCAL_SYVCOMODEPKD_DEFAULT << 8)                      /**< Shifted mode DEFAULT for RAC_SYCAL          */
#define RAC_SYCAL_SYVCOMODEPKD_t_openloop_0                           (_RAC_SYCAL_SYVCOMODEPKD_t_openloop_0 << 8)                 /**< Shifted mode t_openloop_0 for RAC_SYCAL     */
#define RAC_SYCAL_SYVCOMODEPKD_t_pkdetect_1                           (_RAC_SYCAL_SYVCOMODEPKD_t_pkdetect_1 << 8)                 /**< Shifted mode t_pkdetect_1 for RAC_SYCAL     */
#define RAC_SYCAL_SYVCOMORECURRENT                                    (0x1UL << 9)                                                /**< SYVCOMORECURRENT                            */
#define _RAC_SYCAL_SYVCOMORECURRENT_SHIFT                             9                                                           /**< Shift value for RAC_SYVCOMORECURRENT        */
#define _RAC_SYCAL_SYVCOMORECURRENT_MASK                              0x200UL                                                     /**< Bit mask for RAC_SYVCOMORECURRENT           */
#define _RAC_SYCAL_SYVCOMORECURRENT_DEFAULT                           0x00000000UL                                                /**< Mode DEFAULT for RAC_SYCAL                  */
#define _RAC_SYCAL_SYVCOMORECURRENT_more_current_0                    0x00000000UL                                                /**< Mode more_current_0 for RAC_SYCAL           */
#define _RAC_SYCAL_SYVCOMORECURRENT_more_current_1                    0x00000001UL                                                /**< Mode more_current_1 for RAC_SYCAL           */
#define RAC_SYCAL_SYVCOMORECURRENT_DEFAULT                            (_RAC_SYCAL_SYVCOMORECURRENT_DEFAULT << 9)                  /**< Shifted mode DEFAULT for RAC_SYCAL          */
#define RAC_SYCAL_SYVCOMORECURRENT_more_current_0                     (_RAC_SYCAL_SYVCOMORECURRENT_more_current_0 << 9)           /**< Shifted mode more_current_0 for RAC_SYCAL   */
#define RAC_SYCAL_SYVCOMORECURRENT_more_current_1                     (_RAC_SYCAL_SYVCOMORECURRENT_more_current_1 << 9)           /**< Shifted mode more_current_1 for RAC_SYCAL   */
#define RAC_SYCAL_SYVCOSLOWNOISEFILTER                                (0x1UL << 10)                                               /**< SYVCOSLOWNOISEFILTER                        */
#define _RAC_SYCAL_SYVCOSLOWNOISEFILTER_SHIFT                         10                                                          /**< Shift value for RAC_SYVCOSLOWNOISEFILTER    */
#define _RAC_SYCAL_SYVCOSLOWNOISEFILTER_MASK                          0x400UL                                                     /**< Bit mask for RAC_SYVCOSLOWNOISEFILTER       */
#define _RAC_SYCAL_SYVCOSLOWNOISEFILTER_DEFAULT                       0x00000000UL                                                /**< Mode DEFAULT for RAC_SYCAL                  */
#define _RAC_SYCAL_SYVCOSLOWNOISEFILTER_slow_noise_filter_0           0x00000000UL                                                /**< Mode slow_noise_filter_0 for RAC_SYCAL      */
#define _RAC_SYCAL_SYVCOSLOWNOISEFILTER_slow_noise_filter_1           0x00000001UL                                                /**< Mode slow_noise_filter_1 for RAC_SYCAL      */
#define RAC_SYCAL_SYVCOSLOWNOISEFILTER_DEFAULT                        (_RAC_SYCAL_SYVCOSLOWNOISEFILTER_DEFAULT << 10)             /**< Shifted mode DEFAULT for RAC_SYCAL          */
#define RAC_SYCAL_SYVCOSLOWNOISEFILTER_slow_noise_filter_0            (_RAC_SYCAL_SYVCOSLOWNOISEFILTER_slow_noise_filter_0 << 10) /**< Shifted mode slow_noise_filter_0 for RAC_SYCAL*/
#define RAC_SYCAL_SYVCOSLOWNOISEFILTER_slow_noise_filter_1            (_RAC_SYCAL_SYVCOSLOWNOISEFILTER_slow_noise_filter_1 << 10) /**< Shifted mode slow_noise_filter_1 for RAC_SYCAL*/
#define _RAC_SYCAL_SYVCOVCAPVCM_SHIFT                                 15                                                          /**< Shift value for RAC_SYVCOVCAPVCM            */
#define _RAC_SYCAL_SYVCOVCAPVCM_MASK                                  0x18000UL                                                   /**< Bit mask for RAC_SYVCOVCAPVCM               */
#define _RAC_SYCAL_SYVCOVCAPVCM_DEFAULT                               0x00000001UL                                                /**< Mode DEFAULT for RAC_SYCAL                  */
#define RAC_SYCAL_SYVCOVCAPVCM_DEFAULT                                (_RAC_SYCAL_SYVCOVCAPVCM_DEFAULT << 15)                     /**< Shifted mode DEFAULT for RAC_SYCAL          */
#define _RAC_SYCAL_SYHILOADCHPREG_SHIFT                               24                                                          /**< Shift value for RAC_SYHILOADCHPREG          */
#define _RAC_SYCAL_SYHILOADCHPREG_MASK                                0x3000000UL                                                 /**< Bit mask for RAC_SYHILOADCHPREG             */
#define _RAC_SYCAL_SYHILOADCHPREG_DEFAULT                             0x00000001UL                                                /**< Mode DEFAULT for RAC_SYCAL                  */
#define _RAC_SYCAL_SYHILOADCHPREG_i_350uA                             0x00000000UL                                                /**< Mode i_350uA for RAC_SYCAL                  */
#define _RAC_SYCAL_SYHILOADCHPREG_i_500uA                             0x00000001UL                                                /**< Mode i_500uA for RAC_SYCAL                  */
#define _RAC_SYCAL_SYHILOADCHPREG_i_550uA                             0x00000002UL                                                /**< Mode i_550uA for RAC_SYCAL                  */
#define _RAC_SYCAL_SYHILOADCHPREG_i_700uA                             0x00000003UL                                                /**< Mode i_700uA for RAC_SYCAL                  */
#define RAC_SYCAL_SYHILOADCHPREG_DEFAULT                              (_RAC_SYCAL_SYHILOADCHPREG_DEFAULT << 24)                   /**< Shifted mode DEFAULT for RAC_SYCAL          */
#define RAC_SYCAL_SYHILOADCHPREG_i_350uA                              (_RAC_SYCAL_SYHILOADCHPREG_i_350uA << 24)                   /**< Shifted mode i_350uA for RAC_SYCAL          */
#define RAC_SYCAL_SYHILOADCHPREG_i_500uA                              (_RAC_SYCAL_SYHILOADCHPREG_i_500uA << 24)                   /**< Shifted mode i_500uA for RAC_SYCAL          */
#define RAC_SYCAL_SYHILOADCHPREG_i_550uA                              (_RAC_SYCAL_SYHILOADCHPREG_i_550uA << 24)                   /**< Shifted mode i_550uA for RAC_SYCAL          */
#define RAC_SYCAL_SYHILOADCHPREG_i_700uA                              (_RAC_SYCAL_SYHILOADCHPREG_i_700uA << 24)                   /**< Shifted mode i_700uA for RAC_SYCAL          */

/* Bit fields for RAC SYEN */
#define _RAC_SYEN_RESETVALUE                                          0x00000000UL                                    /**< Default value for RAC_SYEN                  */
#define _RAC_SYEN_MASK                                                0x000067FFUL                                    /**< Mask for RAC_SYEN                           */
#define RAC_SYEN_SYCHPEN                                              (0x1UL << 0)                                    /**< SYCHPEN                                     */
#define _RAC_SYEN_SYCHPEN_SHIFT                                       0                                               /**< Shift value for RAC_SYCHPEN                 */
#define _RAC_SYEN_SYCHPEN_MASK                                        0x1UL                                           /**< Bit mask for RAC_SYCHPEN                    */
#define _RAC_SYEN_SYCHPEN_DEFAULT                                     0x00000000UL                                    /**< Mode DEFAULT for RAC_SYEN                   */
#define _RAC_SYEN_SYCHPEN_disable                                     0x00000000UL                                    /**< Mode disable for RAC_SYEN                   */
#define _RAC_SYEN_SYCHPEN_enable                                      0x00000001UL                                    /**< Mode enable for RAC_SYEN                    */
#define RAC_SYEN_SYCHPEN_DEFAULT                                      (_RAC_SYEN_SYCHPEN_DEFAULT << 0)                /**< Shifted mode DEFAULT for RAC_SYEN           */
#define RAC_SYEN_SYCHPEN_disable                                      (_RAC_SYEN_SYCHPEN_disable << 0)                /**< Shifted mode disable for RAC_SYEN           */
#define RAC_SYEN_SYCHPEN_enable                                       (_RAC_SYEN_SYCHPEN_enable << 0)                 /**< Shifted mode enable for RAC_SYEN            */
#define RAC_SYEN_SYCHPLPENRX                                          (0x1UL << 1)                                    /**< SYCHPLPENRX                                 */
#define _RAC_SYEN_SYCHPLPENRX_SHIFT                                   1                                               /**< Shift value for RAC_SYCHPLPENRX             */
#define _RAC_SYEN_SYCHPLPENRX_MASK                                    0x2UL                                           /**< Bit mask for RAC_SYCHPLPENRX                */
#define _RAC_SYEN_SYCHPLPENRX_DEFAULT                                 0x00000000UL                                    /**< Mode DEFAULT for RAC_SYEN                   */
#define _RAC_SYEN_SYCHPLPENRX_disable                                 0x00000000UL                                    /**< Mode disable for RAC_SYEN                   */
#define _RAC_SYEN_SYCHPLPENRX_enable                                  0x00000001UL                                    /**< Mode enable for RAC_SYEN                    */
#define RAC_SYEN_SYCHPLPENRX_DEFAULT                                  (_RAC_SYEN_SYCHPLPENRX_DEFAULT << 1)            /**< Shifted mode DEFAULT for RAC_SYEN           */
#define RAC_SYEN_SYCHPLPENRX_disable                                  (_RAC_SYEN_SYCHPLPENRX_disable << 1)            /**< Shifted mode disable for RAC_SYEN           */
#define RAC_SYEN_SYCHPLPENRX_enable                                   (_RAC_SYEN_SYCHPLPENRX_enable << 1)             /**< Shifted mode enable for RAC_SYEN            */
#define RAC_SYEN_SYCHPLPENTX                                          (0x1UL << 2)                                    /**< SYCHPLPENTX                                 */
#define _RAC_SYEN_SYCHPLPENTX_SHIFT                                   2                                               /**< Shift value for RAC_SYCHPLPENTX             */
#define _RAC_SYEN_SYCHPLPENTX_MASK                                    0x4UL                                           /**< Bit mask for RAC_SYCHPLPENTX                */
#define _RAC_SYEN_SYCHPLPENTX_DEFAULT                                 0x00000000UL                                    /**< Mode DEFAULT for RAC_SYEN                   */
#define _RAC_SYEN_SYCHPLPENTX_disable                                 0x00000000UL                                    /**< Mode disable for RAC_SYEN                   */
#define _RAC_SYEN_SYCHPLPENTX_enable                                  0x00000001UL                                    /**< Mode enable for RAC_SYEN                    */
#define RAC_SYEN_SYCHPLPENTX_DEFAULT                                  (_RAC_SYEN_SYCHPLPENTX_DEFAULT << 2)            /**< Shifted mode DEFAULT for RAC_SYEN           */
#define RAC_SYEN_SYCHPLPENTX_disable                                  (_RAC_SYEN_SYCHPLPENTX_disable << 2)            /**< Shifted mode disable for RAC_SYEN           */
#define RAC_SYEN_SYCHPLPENTX_enable                                   (_RAC_SYEN_SYCHPLPENTX_enable << 2)             /**< Shifted mode enable for RAC_SYEN            */
#define RAC_SYEN_SYENCHPREG                                           (0x1UL << 3)                                    /**< SYENCHPREG                                  */
#define _RAC_SYEN_SYENCHPREG_SHIFT                                    3                                               /**< Shift value for RAC_SYENCHPREG              */
#define _RAC_SYEN_SYENCHPREG_MASK                                     0x8UL                                           /**< Bit mask for RAC_SYENCHPREG                 */
#define _RAC_SYEN_SYENCHPREG_DEFAULT                                  0x00000000UL                                    /**< Mode DEFAULT for RAC_SYEN                   */
#define _RAC_SYEN_SYENCHPREG_Disable                                  0x00000000UL                                    /**< Mode Disable for RAC_SYEN                   */
#define _RAC_SYEN_SYENCHPREG_Enable                                   0x00000001UL                                    /**< Mode Enable for RAC_SYEN                    */
#define RAC_SYEN_SYENCHPREG_DEFAULT                                   (_RAC_SYEN_SYENCHPREG_DEFAULT << 3)             /**< Shifted mode DEFAULT for RAC_SYEN           */
#define RAC_SYEN_SYENCHPREG_Disable                                   (_RAC_SYEN_SYENCHPREG_Disable << 3)             /**< Shifted mode Disable for RAC_SYEN           */
#define RAC_SYEN_SYENCHPREG_Enable                                    (_RAC_SYEN_SYENCHPREG_Enable << 3)              /**< Shifted mode Enable for RAC_SYEN            */
#define RAC_SYEN_SYENCHPREPLICA                                       (0x1UL << 4)                                    /**< SYENCHPREPLICA                              */
#define _RAC_SYEN_SYENCHPREPLICA_SHIFT                                4                                               /**< Shift value for RAC_SYENCHPREPLICA          */
#define _RAC_SYEN_SYENCHPREPLICA_MASK                                 0x10UL                                          /**< Bit mask for RAC_SYENCHPREPLICA             */
#define _RAC_SYEN_SYENCHPREPLICA_DEFAULT                              0x00000000UL                                    /**< Mode DEFAULT for RAC_SYEN                   */
#define _RAC_SYEN_SYENCHPREPLICA_disable                              0x00000000UL                                    /**< Mode disable for RAC_SYEN                   */
#define _RAC_SYEN_SYENCHPREPLICA_enable                               0x00000001UL                                    /**< Mode enable for RAC_SYEN                    */
#define RAC_SYEN_SYENCHPREPLICA_DEFAULT                               (_RAC_SYEN_SYENCHPREPLICA_DEFAULT << 4)         /**< Shifted mode DEFAULT for RAC_SYEN           */
#define RAC_SYEN_SYENCHPREPLICA_disable                               (_RAC_SYEN_SYENCHPREPLICA_disable << 4)         /**< Shifted mode disable for RAC_SYEN           */
#define RAC_SYEN_SYENCHPREPLICA_enable                                (_RAC_SYEN_SYENCHPREPLICA_enable << 4)          /**< Shifted mode enable for RAC_SYEN            */
#define RAC_SYEN_SYENMMDREG                                           (0x1UL << 5)                                    /**< SYENMMDREG                                  */
#define _RAC_SYEN_SYENMMDREG_SHIFT                                    5                                               /**< Shift value for RAC_SYENMMDREG              */
#define _RAC_SYEN_SYENMMDREG_MASK                                     0x20UL                                          /**< Bit mask for RAC_SYENMMDREG                 */
#define _RAC_SYEN_SYENMMDREG_DEFAULT                                  0x00000000UL                                    /**< Mode DEFAULT for RAC_SYEN                   */
#define _RAC_SYEN_SYENMMDREG_Disable                                  0x00000000UL                                    /**< Mode Disable for RAC_SYEN                   */
#define _RAC_SYEN_SYENMMDREG_Enable                                   0x00000001UL                                    /**< Mode Enable for RAC_SYEN                    */
#define RAC_SYEN_SYENMMDREG_DEFAULT                                   (_RAC_SYEN_SYENMMDREG_DEFAULT << 5)             /**< Shifted mode DEFAULT for RAC_SYEN           */
#define RAC_SYEN_SYENMMDREG_Disable                                   (_RAC_SYEN_SYENMMDREG_Disable << 5)             /**< Shifted mode Disable for RAC_SYEN           */
#define RAC_SYEN_SYENMMDREG_Enable                                    (_RAC_SYEN_SYENMMDREG_Enable << 5)              /**< Shifted mode Enable for RAC_SYEN            */
#define RAC_SYEN_SYENMMDREPLICA1                                      (0x1UL << 6)                                    /**< SYENMMDREPLICA1                             */
#define _RAC_SYEN_SYENMMDREPLICA1_SHIFT                               6                                               /**< Shift value for RAC_SYENMMDREPLICA1         */
#define _RAC_SYEN_SYENMMDREPLICA1_MASK                                0x40UL                                          /**< Bit mask for RAC_SYENMMDREPLICA1            */
#define _RAC_SYEN_SYENMMDREPLICA1_DEFAULT                             0x00000000UL                                    /**< Mode DEFAULT for RAC_SYEN                   */
#define _RAC_SYEN_SYENMMDREPLICA1_disable                             0x00000000UL                                    /**< Mode disable for RAC_SYEN                   */
#define _RAC_SYEN_SYENMMDREPLICA1_enable                              0x00000001UL                                    /**< Mode enable for RAC_SYEN                    */
#define RAC_SYEN_SYENMMDREPLICA1_DEFAULT                              (_RAC_SYEN_SYENMMDREPLICA1_DEFAULT << 6)        /**< Shifted mode DEFAULT for RAC_SYEN           */
#define RAC_SYEN_SYENMMDREPLICA1_disable                              (_RAC_SYEN_SYENMMDREPLICA1_disable << 6)        /**< Shifted mode disable for RAC_SYEN           */
#define RAC_SYEN_SYENMMDREPLICA1_enable                               (_RAC_SYEN_SYENMMDREPLICA1_enable << 6)         /**< Shifted mode enable for RAC_SYEN            */
#define RAC_SYEN_SYENMMDREPLICA2                                      (0x1UL << 7)                                    /**< SYENMMDREPLICA2                             */
#define _RAC_SYEN_SYENMMDREPLICA2_SHIFT                               7                                               /**< Shift value for RAC_SYENMMDREPLICA2         */
#define _RAC_SYEN_SYENMMDREPLICA2_MASK                                0x80UL                                          /**< Bit mask for RAC_SYENMMDREPLICA2            */
#define _RAC_SYEN_SYENMMDREPLICA2_DEFAULT                             0x00000000UL                                    /**< Mode DEFAULT for RAC_SYEN                   */
#define _RAC_SYEN_SYENMMDREPLICA2_Disable                             0x00000000UL                                    /**< Mode Disable for RAC_SYEN                   */
#define _RAC_SYEN_SYENMMDREPLICA2_Enable                              0x00000001UL                                    /**< Mode Enable for RAC_SYEN                    */
#define RAC_SYEN_SYENMMDREPLICA2_DEFAULT                              (_RAC_SYEN_SYENMMDREPLICA2_DEFAULT << 7)        /**< Shifted mode DEFAULT for RAC_SYEN           */
#define RAC_SYEN_SYENMMDREPLICA2_Disable                              (_RAC_SYEN_SYENMMDREPLICA2_Disable << 7)        /**< Shifted mode Disable for RAC_SYEN           */
#define RAC_SYEN_SYENMMDREPLICA2_Enable                               (_RAC_SYEN_SYENMMDREPLICA2_Enable << 7)         /**< Shifted mode Enable for RAC_SYEN            */
#define RAC_SYEN_SYENVCOBIAS                                          (0x1UL << 8)                                    /**< SYENVCOBIAS                                 */
#define _RAC_SYEN_SYENVCOBIAS_SHIFT                                   8                                               /**< Shift value for RAC_SYENVCOBIAS             */
#define _RAC_SYEN_SYENVCOBIAS_MASK                                    0x100UL                                         /**< Bit mask for RAC_SYENVCOBIAS                */
#define _RAC_SYEN_SYENVCOBIAS_DEFAULT                                 0x00000000UL                                    /**< Mode DEFAULT for RAC_SYEN                   */
#define _RAC_SYEN_SYENVCOBIAS_en_vco_bias_0                           0x00000000UL                                    /**< Mode en_vco_bias_0 for RAC_SYEN             */
#define _RAC_SYEN_SYENVCOBIAS_en_vco_bias_1                           0x00000001UL                                    /**< Mode en_vco_bias_1 for RAC_SYEN             */
#define RAC_SYEN_SYENVCOBIAS_DEFAULT                                  (_RAC_SYEN_SYENVCOBIAS_DEFAULT << 8)            /**< Shifted mode DEFAULT for RAC_SYEN           */
#define RAC_SYEN_SYENVCOBIAS_en_vco_bias_0                            (_RAC_SYEN_SYENVCOBIAS_en_vco_bias_0 << 8)      /**< Shifted mode en_vco_bias_0 for RAC_SYEN     */
#define RAC_SYEN_SYENVCOBIAS_en_vco_bias_1                            (_RAC_SYEN_SYENVCOBIAS_en_vco_bias_1 << 8)      /**< Shifted mode en_vco_bias_1 for RAC_SYEN     */
#define RAC_SYEN_SYENVCOPFET                                          (0x1UL << 9)                                    /**< SYENVCOPFET                                 */
#define _RAC_SYEN_SYENVCOPFET_SHIFT                                   9                                               /**< Shift value for RAC_SYENVCOPFET             */
#define _RAC_SYEN_SYENVCOPFET_MASK                                    0x200UL                                         /**< Bit mask for RAC_SYENVCOPFET                */
#define _RAC_SYEN_SYENVCOPFET_DEFAULT                                 0x00000000UL                                    /**< Mode DEFAULT for RAC_SYEN                   */
#define _RAC_SYEN_SYENVCOPFET_en_vco_pfet_0                           0x00000000UL                                    /**< Mode en_vco_pfet_0 for RAC_SYEN             */
#define _RAC_SYEN_SYENVCOPFET_en_vco_pfet_1                           0x00000001UL                                    /**< Mode en_vco_pfet_1 for RAC_SYEN             */
#define RAC_SYEN_SYENVCOPFET_DEFAULT                                  (_RAC_SYEN_SYENVCOPFET_DEFAULT << 9)            /**< Shifted mode DEFAULT for RAC_SYEN           */
#define RAC_SYEN_SYENVCOPFET_en_vco_pfet_0                            (_RAC_SYEN_SYENVCOPFET_en_vco_pfet_0 << 9)      /**< Shifted mode en_vco_pfet_0 for RAC_SYEN     */
#define RAC_SYEN_SYENVCOPFET_en_vco_pfet_1                            (_RAC_SYEN_SYENVCOPFET_en_vco_pfet_1 << 9)      /**< Shifted mode en_vco_pfet_1 for RAC_SYEN     */
#define RAC_SYEN_SYENVCOREG                                           (0x1UL << 10)                                   /**< SYENVCOREG                                  */
#define _RAC_SYEN_SYENVCOREG_SHIFT                                    10                                              /**< Shift value for RAC_SYENVCOREG              */
#define _RAC_SYEN_SYENVCOREG_MASK                                     0x400UL                                         /**< Bit mask for RAC_SYENVCOREG                 */
#define _RAC_SYEN_SYENVCOREG_DEFAULT                                  0x00000000UL                                    /**< Mode DEFAULT for RAC_SYEN                   */
#define _RAC_SYEN_SYENVCOREG_en_vco_reg_0                             0x00000000UL                                    /**< Mode en_vco_reg_0 for RAC_SYEN              */
#define _RAC_SYEN_SYENVCOREG_en_vco_reg_1                             0x00000001UL                                    /**< Mode en_vco_reg_1 for RAC_SYEN              */
#define RAC_SYEN_SYENVCOREG_DEFAULT                                   (_RAC_SYEN_SYENVCOREG_DEFAULT << 10)            /**< Shifted mode DEFAULT for RAC_SYEN           */
#define RAC_SYEN_SYENVCOREG_en_vco_reg_0                              (_RAC_SYEN_SYENVCOREG_en_vco_reg_0 << 10)       /**< Shifted mode en_vco_reg_0 for RAC_SYEN      */
#define RAC_SYEN_SYENVCOREG_en_vco_reg_1                              (_RAC_SYEN_SYENVCOREG_en_vco_reg_1 << 10)       /**< Shifted mode en_vco_reg_1 for RAC_SYEN      */
#define RAC_SYEN_SYSTARTCHPREG                                        (0x1UL << 13)                                   /**< SYSTARTCHPREG                               */
#define _RAC_SYEN_SYSTARTCHPREG_SHIFT                                 13                                              /**< Shift value for RAC_SYSTARTCHPREG           */
#define _RAC_SYEN_SYSTARTCHPREG_MASK                                  0x2000UL                                        /**< Bit mask for RAC_SYSTARTCHPREG              */
#define _RAC_SYEN_SYSTARTCHPREG_DEFAULT                               0x00000000UL                                    /**< Mode DEFAULT for RAC_SYEN                   */
#define _RAC_SYEN_SYSTARTCHPREG_no_fast_startup                       0x00000000UL                                    /**< Mode no_fast_startup for RAC_SYEN           */
#define _RAC_SYEN_SYSTARTCHPREG_fast_startup                          0x00000001UL                                    /**< Mode fast_startup for RAC_SYEN              */
#define RAC_SYEN_SYSTARTCHPREG_DEFAULT                                (_RAC_SYEN_SYSTARTCHPREG_DEFAULT << 13)         /**< Shifted mode DEFAULT for RAC_SYEN           */
#define RAC_SYEN_SYSTARTCHPREG_no_fast_startup                        (_RAC_SYEN_SYSTARTCHPREG_no_fast_startup << 13) /**< Shifted mode no_fast_startup for RAC_SYEN   */
#define RAC_SYEN_SYSTARTCHPREG_fast_startup                           (_RAC_SYEN_SYSTARTCHPREG_fast_startup << 13)    /**< Shifted mode fast_startup for RAC_SYEN      */
#define RAC_SYEN_SYSTARTMMDREG                                        (0x1UL << 14)                                   /**< SYSTARTMMDREG                               */
#define _RAC_SYEN_SYSTARTMMDREG_SHIFT                                 14                                              /**< Shift value for RAC_SYSTARTMMDREG           */
#define _RAC_SYEN_SYSTARTMMDREG_MASK                                  0x4000UL                                        /**< Bit mask for RAC_SYSTARTMMDREG              */
#define _RAC_SYEN_SYSTARTMMDREG_DEFAULT                               0x00000000UL                                    /**< Mode DEFAULT for RAC_SYEN                   */
#define _RAC_SYEN_SYSTARTMMDREG_no_fast_startup                       0x00000000UL                                    /**< Mode no_fast_startup for RAC_SYEN           */
#define _RAC_SYEN_SYSTARTMMDREG_fast_startup                          0x00000001UL                                    /**< Mode fast_startup for RAC_SYEN              */
#define RAC_SYEN_SYSTARTMMDREG_DEFAULT                                (_RAC_SYEN_SYSTARTMMDREG_DEFAULT << 14)         /**< Shifted mode DEFAULT for RAC_SYEN           */
#define RAC_SYEN_SYSTARTMMDREG_no_fast_startup                        (_RAC_SYEN_SYSTARTMMDREG_no_fast_startup << 14) /**< Shifted mode no_fast_startup for RAC_SYEN   */
#define RAC_SYEN_SYSTARTMMDREG_fast_startup                           (_RAC_SYEN_SYSTARTMMDREG_fast_startup << 14)    /**< Shifted mode fast_startup for RAC_SYEN      */

/* Bit fields for RAC SYLOEN */
#define _RAC_SYLOEN_RESETVALUE                                        0x00000000UL                                          /**< Default value for RAC_SYLOEN                */
#define _RAC_SYLOEN_MASK                                              0x00001F1EUL                                          /**< Mask for RAC_SYLOEN                         */
#define RAC_SYLOEN_SYLODIVEN                                          (0x1UL << 1)                                          /**< SYLODIVEN                                   */
#define _RAC_SYLOEN_SYLODIVEN_SHIFT                                   1                                                     /**< Shift value for RAC_SYLODIVEN               */
#define _RAC_SYLOEN_SYLODIVEN_MASK                                    0x2UL                                                 /**< Bit mask for RAC_SYLODIVEN                  */
#define _RAC_SYLOEN_SYLODIVEN_DEFAULT                                 0x00000000UL                                          /**< Mode DEFAULT for RAC_SYLOEN                 */
#define _RAC_SYLOEN_SYLODIVEN_disable                                 0x00000000UL                                          /**< Mode disable for RAC_SYLOEN                 */
#define _RAC_SYLOEN_SYLODIVEN_enable                                  0x00000001UL                                          /**< Mode enable for RAC_SYLOEN                  */
#define RAC_SYLOEN_SYLODIVEN_DEFAULT                                  (_RAC_SYLOEN_SYLODIVEN_DEFAULT << 1)                  /**< Shifted mode DEFAULT for RAC_SYLOEN         */
#define RAC_SYLOEN_SYLODIVEN_disable                                  (_RAC_SYLOEN_SYLODIVEN_disable << 1)                  /**< Shifted mode disable for RAC_SYLOEN         */
#define RAC_SYLOEN_SYLODIVEN_enable                                   (_RAC_SYLOEN_SYLODIVEN_enable << 1)                   /**< Shifted mode enable for RAC_SYLOEN          */
#define RAC_SYLOEN_SYLODIVLDOBIASEN                                   (0x1UL << 2)                                          /**< SYLODIVLDOBIASEN                            */
#define _RAC_SYLOEN_SYLODIVLDOBIASEN_SHIFT                            2                                                     /**< Shift value for RAC_SYLODIVLDOBIASEN        */
#define _RAC_SYLOEN_SYLODIVLDOBIASEN_MASK                             0x4UL                                                 /**< Bit mask for RAC_SYLODIVLDOBIASEN           */
#define _RAC_SYLOEN_SYLODIVLDOBIASEN_DEFAULT                          0x00000000UL                                          /**< Mode DEFAULT for RAC_SYLOEN                 */
#define _RAC_SYLOEN_SYLODIVLDOBIASEN_disable                          0x00000000UL                                          /**< Mode disable for RAC_SYLOEN                 */
#define _RAC_SYLOEN_SYLODIVLDOBIASEN_enable                           0x00000001UL                                          /**< Mode enable for RAC_SYLOEN                  */
#define RAC_SYLOEN_SYLODIVLDOBIASEN_DEFAULT                           (_RAC_SYLOEN_SYLODIVLDOBIASEN_DEFAULT << 2)           /**< Shifted mode DEFAULT for RAC_SYLOEN         */
#define RAC_SYLOEN_SYLODIVLDOBIASEN_disable                           (_RAC_SYLOEN_SYLODIVLDOBIASEN_disable << 2)           /**< Shifted mode disable for RAC_SYLOEN         */
#define RAC_SYLOEN_SYLODIVLDOBIASEN_enable                            (_RAC_SYLOEN_SYLODIVLDOBIASEN_enable << 2)            /**< Shifted mode enable for RAC_SYLOEN          */
#define RAC_SYLOEN_SYLODIVLDOEN                                       (0x1UL << 3)                                          /**< SYLODIVLDOEN                                */
#define _RAC_SYLOEN_SYLODIVLDOEN_SHIFT                                3                                                     /**< Shift value for RAC_SYLODIVLDOEN            */
#define _RAC_SYLOEN_SYLODIVLDOEN_MASK                                 0x8UL                                                 /**< Bit mask for RAC_SYLODIVLDOEN               */
#define _RAC_SYLOEN_SYLODIVLDOEN_DEFAULT                              0x00000000UL                                          /**< Mode DEFAULT for RAC_SYLOEN                 */
#define _RAC_SYLOEN_SYLODIVLDOEN_disable                              0x00000000UL                                          /**< Mode disable for RAC_SYLOEN                 */
#define _RAC_SYLOEN_SYLODIVLDOEN_enable                               0x00000001UL                                          /**< Mode enable for RAC_SYLOEN                  */
#define RAC_SYLOEN_SYLODIVLDOEN_DEFAULT                               (_RAC_SYLOEN_SYLODIVLDOEN_DEFAULT << 3)               /**< Shifted mode DEFAULT for RAC_SYLOEN         */
#define RAC_SYLOEN_SYLODIVLDOEN_disable                               (_RAC_SYLOEN_SYLODIVLDOEN_disable << 3)               /**< Shifted mode disable for RAC_SYLOEN         */
#define RAC_SYLOEN_SYLODIVLDOEN_enable                                (_RAC_SYLOEN_SYLODIVLDOEN_enable << 3)                /**< Shifted mode enable for RAC_SYLOEN          */
#define RAC_SYLOEN_SYLODIVRLOADCCLK2G4EN                              (0x1UL << 4)                                          /**< SYLODIVRLOADCCLK2G4EN                       */
#define _RAC_SYLOEN_SYLODIVRLOADCCLK2G4EN_SHIFT                       4                                                     /**< Shift value for RAC_SYLODIVRLOADCCLK2G4EN   */
#define _RAC_SYLOEN_SYLODIVRLOADCCLK2G4EN_MASK                        0x10UL                                                /**< Bit mask for RAC_SYLODIVRLOADCCLK2G4EN      */
#define _RAC_SYLOEN_SYLODIVRLOADCCLK2G4EN_DEFAULT                     0x00000000UL                                          /**< Mode DEFAULT for RAC_SYLOEN                 */
#define _RAC_SYLOEN_SYLODIVRLOADCCLK2G4EN_disable                     0x00000000UL                                          /**< Mode disable for RAC_SYLOEN                 */
#define _RAC_SYLOEN_SYLODIVRLOADCCLK2G4EN_enable                      0x00000001UL                                          /**< Mode enable for RAC_SYLOEN                  */
#define RAC_SYLOEN_SYLODIVRLOADCCLK2G4EN_DEFAULT                      (_RAC_SYLOEN_SYLODIVRLOADCCLK2G4EN_DEFAULT << 4)      /**< Shifted mode DEFAULT for RAC_SYLOEN         */
#define RAC_SYLOEN_SYLODIVRLOADCCLK2G4EN_disable                      (_RAC_SYLOEN_SYLODIVRLOADCCLK2G4EN_disable << 4)      /**< Shifted mode disable for RAC_SYLOEN         */
#define RAC_SYLOEN_SYLODIVRLOADCCLK2G4EN_enable                       (_RAC_SYLOEN_SYLODIVRLOADCCLK2G4EN_enable << 4)       /**< Shifted mode enable for RAC_SYLOEN          */
#define RAC_SYLOEN_SYLODIVTLO0DBM2G4AUXEN                             (0x1UL << 8)                                          /**< SYLODIVTLO0DBM2G4AUXEN                      */
#define _RAC_SYLOEN_SYLODIVTLO0DBM2G4AUXEN_SHIFT                      8                                                     /**< Shift value for RAC_SYLODIVTLO0DBM2G4AUXEN  */
#define _RAC_SYLOEN_SYLODIVTLO0DBM2G4AUXEN_MASK                       0x100UL                                               /**< Bit mask for RAC_SYLODIVTLO0DBM2G4AUXEN     */
#define _RAC_SYLOEN_SYLODIVTLO0DBM2G4AUXEN_DEFAULT                    0x00000000UL                                          /**< Mode DEFAULT for RAC_SYLOEN                 */
#define _RAC_SYLOEN_SYLODIVTLO0DBM2G4AUXEN_disable                    0x00000000UL                                          /**< Mode disable for RAC_SYLOEN                 */
#define _RAC_SYLOEN_SYLODIVTLO0DBM2G4AUXEN_enable                     0x00000001UL                                          /**< Mode enable for RAC_SYLOEN                  */
#define RAC_SYLOEN_SYLODIVTLO0DBM2G4AUXEN_DEFAULT                     (_RAC_SYLOEN_SYLODIVTLO0DBM2G4AUXEN_DEFAULT << 8)     /**< Shifted mode DEFAULT for RAC_SYLOEN         */
#define RAC_SYLOEN_SYLODIVTLO0DBM2G4AUXEN_disable                     (_RAC_SYLOEN_SYLODIVTLO0DBM2G4AUXEN_disable << 8)     /**< Shifted mode disable for RAC_SYLOEN         */
#define RAC_SYLOEN_SYLODIVTLO0DBM2G4AUXEN_enable                      (_RAC_SYLOEN_SYLODIVTLO0DBM2G4AUXEN_enable << 8)      /**< Shifted mode enable for RAC_SYLOEN          */
#define RAC_SYLOEN_SYLODIVTLO0DBM2G4EN                                (0x1UL << 9)                                          /**< SYLODIVTLO0DBM2G4EN                         */
#define _RAC_SYLOEN_SYLODIVTLO0DBM2G4EN_SHIFT                         9                                                     /**< Shift value for RAC_SYLODIVTLO0DBM2G4EN     */
#define _RAC_SYLOEN_SYLODIVTLO0DBM2G4EN_MASK                          0x200UL                                               /**< Bit mask for RAC_SYLODIVTLO0DBM2G4EN        */
#define _RAC_SYLOEN_SYLODIVTLO0DBM2G4EN_DEFAULT                       0x00000000UL                                          /**< Mode DEFAULT for RAC_SYLOEN                 */
#define _RAC_SYLOEN_SYLODIVTLO0DBM2G4EN_disable                       0x00000000UL                                          /**< Mode disable for RAC_SYLOEN                 */
#define _RAC_SYLOEN_SYLODIVTLO0DBM2G4EN_enable                        0x00000001UL                                          /**< Mode enable for RAC_SYLOEN                  */
#define RAC_SYLOEN_SYLODIVTLO0DBM2G4EN_DEFAULT                        (_RAC_SYLOEN_SYLODIVTLO0DBM2G4EN_DEFAULT << 9)        /**< Shifted mode DEFAULT for RAC_SYLOEN         */
#define RAC_SYLOEN_SYLODIVTLO0DBM2G4EN_disable                        (_RAC_SYLOEN_SYLODIVTLO0DBM2G4EN_disable << 9)        /**< Shifted mode disable for RAC_SYLOEN         */
#define RAC_SYLOEN_SYLODIVTLO0DBM2G4EN_enable                         (_RAC_SYLOEN_SYLODIVTLO0DBM2G4EN_enable << 9)         /**< Shifted mode enable for RAC_SYLOEN          */
#define RAC_SYLOEN_SYLODIVTLO20DBM2G4AUXEN                            (0x1UL << 10)                                         /**< SYLODIVTLO20DBM2G4AUXEN                     */
#define _RAC_SYLOEN_SYLODIVTLO20DBM2G4AUXEN_SHIFT                     10                                                    /**< Shift value for RAC_SYLODIVTLO20DBM2G4AUXEN */
#define _RAC_SYLOEN_SYLODIVTLO20DBM2G4AUXEN_MASK                      0x400UL                                               /**< Bit mask for RAC_SYLODIVTLO20DBM2G4AUXEN    */
#define _RAC_SYLOEN_SYLODIVTLO20DBM2G4AUXEN_DEFAULT                   0x00000000UL                                          /**< Mode DEFAULT for RAC_SYLOEN                 */
#define _RAC_SYLOEN_SYLODIVTLO20DBM2G4AUXEN_disable                   0x00000000UL                                          /**< Mode disable for RAC_SYLOEN                 */
#define _RAC_SYLOEN_SYLODIVTLO20DBM2G4AUXEN_enable                    0x00000001UL                                          /**< Mode enable for RAC_SYLOEN                  */
#define RAC_SYLOEN_SYLODIVTLO20DBM2G4AUXEN_DEFAULT                    (_RAC_SYLOEN_SYLODIVTLO20DBM2G4AUXEN_DEFAULT << 10)   /**< Shifted mode DEFAULT for RAC_SYLOEN         */
#define RAC_SYLOEN_SYLODIVTLO20DBM2G4AUXEN_disable                    (_RAC_SYLOEN_SYLODIVTLO20DBM2G4AUXEN_disable << 10)   /**< Shifted mode disable for RAC_SYLOEN         */
#define RAC_SYLOEN_SYLODIVTLO20DBM2G4AUXEN_enable                     (_RAC_SYLOEN_SYLODIVTLO20DBM2G4AUXEN_enable << 10)    /**< Shifted mode enable for RAC_SYLOEN          */
#define RAC_SYLOEN_SYLODIVTLO20DBM2G4EN                               (0x1UL << 11)                                         /**< SYLODIVTLO20DBM2G4EN                        */
#define _RAC_SYLOEN_SYLODIVTLO20DBM2G4EN_SHIFT                        11                                                    /**< Shift value for RAC_SYLODIVTLO20DBM2G4EN    */
#define _RAC_SYLOEN_SYLODIVTLO20DBM2G4EN_MASK                         0x800UL                                               /**< Bit mask for RAC_SYLODIVTLO20DBM2G4EN       */
#define _RAC_SYLOEN_SYLODIVTLO20DBM2G4EN_DEFAULT                      0x00000000UL                                          /**< Mode DEFAULT for RAC_SYLOEN                 */
#define _RAC_SYLOEN_SYLODIVTLO20DBM2G4EN_disable                      0x00000000UL                                          /**< Mode disable for RAC_SYLOEN                 */
#define _RAC_SYLOEN_SYLODIVTLO20DBM2G4EN_enable                       0x00000001UL                                          /**< Mode enable for RAC_SYLOEN                  */
#define RAC_SYLOEN_SYLODIVTLO20DBM2G4EN_DEFAULT                       (_RAC_SYLOEN_SYLODIVTLO20DBM2G4EN_DEFAULT << 11)      /**< Shifted mode DEFAULT for RAC_SYLOEN         */
#define RAC_SYLOEN_SYLODIVTLO20DBM2G4EN_disable                       (_RAC_SYLOEN_SYLODIVTLO20DBM2G4EN_disable << 11)      /**< Shifted mode disable for RAC_SYLOEN         */
#define RAC_SYLOEN_SYLODIVTLO20DBM2G4EN_enable                        (_RAC_SYLOEN_SYLODIVTLO20DBM2G4EN_enable << 11)       /**< Shifted mode enable for RAC_SYLOEN          */
#define RAC_SYLOEN_SYLODIVRLOADCCLKSEL                                (0x1UL << 12)                                         /**< SYLODIVRLOADCCLKSEL                         */
#define _RAC_SYLOEN_SYLODIVRLOADCCLKSEL_SHIFT                         12                                                    /**< Shift value for RAC_SYLODIVRLOADCCLKSEL     */
#define _RAC_SYLOEN_SYLODIVRLOADCCLKSEL_MASK                          0x1000UL                                              /**< Bit mask for RAC_SYLODIVRLOADCCLKSEL        */
#define _RAC_SYLOEN_SYLODIVRLOADCCLKSEL_DEFAULT                       0x00000000UL                                          /**< Mode DEFAULT for RAC_SYLOEN                 */
#define _RAC_SYLOEN_SYLODIVRLOADCCLKSEL_adc_clk_div8                  0x00000000UL                                          /**< Mode adc_clk_div8 for RAC_SYLOEN            */
#define _RAC_SYLOEN_SYLODIVRLOADCCLKSEL_adc_clk_div16                 0x00000001UL                                          /**< Mode adc_clk_div16 for RAC_SYLOEN           */
#define RAC_SYLOEN_SYLODIVRLOADCCLKSEL_DEFAULT                        (_RAC_SYLOEN_SYLODIVRLOADCCLKSEL_DEFAULT << 12)       /**< Shifted mode DEFAULT for RAC_SYLOEN         */
#define RAC_SYLOEN_SYLODIVRLOADCCLKSEL_adc_clk_div8                   (_RAC_SYLOEN_SYLODIVRLOADCCLKSEL_adc_clk_div8 << 12)  /**< Shifted mode adc_clk_div8 for RAC_SYLOEN    */
#define RAC_SYLOEN_SYLODIVRLOADCCLKSEL_adc_clk_div16                  (_RAC_SYLOEN_SYLODIVRLOADCCLKSEL_adc_clk_div16 << 12) /**< Shifted mode adc_clk_div16 for RAC_SYLOEN   */

/* Bit fields for RAC SYMMDCTRL */
#define _RAC_SYMMDCTRL_RESETVALUE                                     0x00000048UL                                     /**< Default value for RAC_SYMMDCTRL             */
#define _RAC_SYMMDCTRL_MASK                                           0x000001FFUL                                     /**< Mask for RAC_SYMMDCTRL                      */
#define _RAC_SYMMDCTRL_SYMMDDIVRSDIG_SHIFT                            0                                                /**< Shift value for RAC_SYMMDDIVRSDIG           */
#define _RAC_SYMMDCTRL_SYMMDDIVRSDIG_MASK                             0x3UL                                            /**< Bit mask for RAC_SYMMDDIVRSDIG              */
#define _RAC_SYMMDCTRL_SYMMDDIVRSDIG_DEFAULT                          0x00000000UL                                     /**< Mode DEFAULT for RAC_SYMMDCTRL              */
#define _RAC_SYMMDCTRL_SYMMDDIVRSDIG_Divideby1                        0x00000000UL                                     /**< Mode Divideby1 for RAC_SYMMDCTRL            */
#define _RAC_SYMMDCTRL_SYMMDDIVRSDIG_Divideby2                        0x00000001UL                                     /**< Mode Divideby2 for RAC_SYMMDCTRL            */
#define _RAC_SYMMDCTRL_SYMMDDIVRSDIG_Divideby4                        0x00000002UL                                     /**< Mode Divideby4 for RAC_SYMMDCTRL            */
#define _RAC_SYMMDCTRL_SYMMDDIVRSDIG_Divideby8                        0x00000003UL                                     /**< Mode Divideby8 for RAC_SYMMDCTRL            */
#define RAC_SYMMDCTRL_SYMMDDIVRSDIG_DEFAULT                           (_RAC_SYMMDCTRL_SYMMDDIVRSDIG_DEFAULT << 0)      /**< Shifted mode DEFAULT for RAC_SYMMDCTRL      */
#define RAC_SYMMDCTRL_SYMMDDIVRSDIG_Divideby1                         (_RAC_SYMMDCTRL_SYMMDDIVRSDIG_Divideby1 << 0)    /**< Shifted mode Divideby1 for RAC_SYMMDCTRL    */
#define RAC_SYMMDCTRL_SYMMDDIVRSDIG_Divideby2                         (_RAC_SYMMDCTRL_SYMMDDIVRSDIG_Divideby2 << 0)    /**< Shifted mode Divideby2 for RAC_SYMMDCTRL    */
#define RAC_SYMMDCTRL_SYMMDDIVRSDIG_Divideby4                         (_RAC_SYMMDCTRL_SYMMDDIVRSDIG_Divideby4 << 0)    /**< Shifted mode Divideby4 for RAC_SYMMDCTRL    */
#define RAC_SYMMDCTRL_SYMMDDIVRSDIG_Divideby8                         (_RAC_SYMMDCTRL_SYMMDDIVRSDIG_Divideby8 << 0)    /**< Shifted mode Divideby8 for RAC_SYMMDCTRL    */
#define _RAC_SYMMDCTRL_SYMMDMODERX_SHIFT                              2                                                /**< Shift value for RAC_SYMMDMODERX             */
#define _RAC_SYMMDCTRL_SYMMDMODERX_MASK                               0x1CUL                                           /**< Bit mask for RAC_SYMMDMODERX                */
#define _RAC_SYMMDCTRL_SYMMDMODERX_DEFAULT                            0x00000002UL                                     /**< Mode DEFAULT for RAC_SYMMDCTRL              */
#define _RAC_SYMMDCTRL_SYMMDMODERX_rx_w_swctrl                        0x00000000UL                                     /**< Mode rx_w_swctrl for RAC_SYMMDCTRL          */
#define _RAC_SYMMDCTRL_SYMMDMODERX_rx_wo_swctrl                       0x00000001UL                                     /**< Mode rx_wo_swctrl for RAC_SYMMDCTRL         */
#define _RAC_SYMMDCTRL_SYMMDMODERX_qnc_dsm2                           0x00000002UL                                     /**< Mode qnc_dsm2 for RAC_SYMMDCTRL             */
#define _RAC_SYMMDCTRL_SYMMDMODERX_qnc_dsm3                           0x00000003UL                                     /**< Mode qnc_dsm3 for RAC_SYMMDCTRL             */
#define _RAC_SYMMDCTRL_SYMMDMODERX_rxlp_wo_swctrl                     0x00000004UL                                     /**< Mode rxlp_wo_swctrl for RAC_SYMMDCTRL       */
#define _RAC_SYMMDCTRL_SYMMDMODERX_notuse_5                           0x00000005UL                                     /**< Mode notuse_5 for RAC_SYMMDCTRL             */
#define _RAC_SYMMDCTRL_SYMMDMODERX_notuse_6                           0x00000006UL                                     /**< Mode notuse_6 for RAC_SYMMDCTRL             */
#define _RAC_SYMMDCTRL_SYMMDMODERX_notuse_7                           0x00000007UL                                     /**< Mode notuse_7 for RAC_SYMMDCTRL             */
#define RAC_SYMMDCTRL_SYMMDMODERX_DEFAULT                             (_RAC_SYMMDCTRL_SYMMDMODERX_DEFAULT << 2)        /**< Shifted mode DEFAULT for RAC_SYMMDCTRL      */
#define RAC_SYMMDCTRL_SYMMDMODERX_rx_w_swctrl                         (_RAC_SYMMDCTRL_SYMMDMODERX_rx_w_swctrl << 2)    /**< Shifted mode rx_w_swctrl for RAC_SYMMDCTRL  */
#define RAC_SYMMDCTRL_SYMMDMODERX_rx_wo_swctrl                        (_RAC_SYMMDCTRL_SYMMDMODERX_rx_wo_swctrl << 2)   /**< Shifted mode rx_wo_swctrl for RAC_SYMMDCTRL */
#define RAC_SYMMDCTRL_SYMMDMODERX_qnc_dsm2                            (_RAC_SYMMDCTRL_SYMMDMODERX_qnc_dsm2 << 2)       /**< Shifted mode qnc_dsm2 for RAC_SYMMDCTRL     */
#define RAC_SYMMDCTRL_SYMMDMODERX_qnc_dsm3                            (_RAC_SYMMDCTRL_SYMMDMODERX_qnc_dsm3 << 2)       /**< Shifted mode qnc_dsm3 for RAC_SYMMDCTRL     */
#define RAC_SYMMDCTRL_SYMMDMODERX_rxlp_wo_swctrl                      (_RAC_SYMMDCTRL_SYMMDMODERX_rxlp_wo_swctrl << 2) /**< Shifted mode rxlp_wo_swctrl for RAC_SYMMDCTRL*/
#define RAC_SYMMDCTRL_SYMMDMODERX_notuse_5                            (_RAC_SYMMDCTRL_SYMMDMODERX_notuse_5 << 2)       /**< Shifted mode notuse_5 for RAC_SYMMDCTRL     */
#define RAC_SYMMDCTRL_SYMMDMODERX_notuse_6                            (_RAC_SYMMDCTRL_SYMMDMODERX_notuse_6 << 2)       /**< Shifted mode notuse_6 for RAC_SYMMDCTRL     */
#define RAC_SYMMDCTRL_SYMMDMODERX_notuse_7                            (_RAC_SYMMDCTRL_SYMMDMODERX_notuse_7 << 2)       /**< Shifted mode notuse_7 for RAC_SYMMDCTRL     */
#define _RAC_SYMMDCTRL_SYMMDMODETX_SHIFT                              5                                                /**< Shift value for RAC_SYMMDMODETX             */
#define _RAC_SYMMDCTRL_SYMMDMODETX_MASK                               0xE0UL                                           /**< Bit mask for RAC_SYMMDMODETX                */
#define _RAC_SYMMDCTRL_SYMMDMODETX_DEFAULT                            0x00000002UL                                     /**< Mode DEFAULT for RAC_SYMMDCTRL              */
#define _RAC_SYMMDCTRL_SYMMDMODETX_rx_w_swctrl                        0x00000000UL                                     /**< Mode rx_w_swctrl for RAC_SYMMDCTRL          */
#define _RAC_SYMMDCTRL_SYMMDMODETX_rx_wo_swctrl                       0x00000001UL                                     /**< Mode rx_wo_swctrl for RAC_SYMMDCTRL         */
#define _RAC_SYMMDCTRL_SYMMDMODETX_qnc_dsm2                           0x00000002UL                                     /**< Mode qnc_dsm2 for RAC_SYMMDCTRL             */
#define _RAC_SYMMDCTRL_SYMMDMODETX_qnc_dsm3                           0x00000003UL                                     /**< Mode qnc_dsm3 for RAC_SYMMDCTRL             */
#define _RAC_SYMMDCTRL_SYMMDMODETX_rxlp_wo_swctrl                     0x00000004UL                                     /**< Mode rxlp_wo_swctrl for RAC_SYMMDCTRL       */
#define _RAC_SYMMDCTRL_SYMMDMODETX_notuse_5                           0x00000005UL                                     /**< Mode notuse_5 for RAC_SYMMDCTRL             */
#define _RAC_SYMMDCTRL_SYMMDMODETX_notuse_6                           0x00000006UL                                     /**< Mode notuse_6 for RAC_SYMMDCTRL             */
#define _RAC_SYMMDCTRL_SYMMDMODETX_notuse_7                           0x00000007UL                                     /**< Mode notuse_7 for RAC_SYMMDCTRL             */
#define RAC_SYMMDCTRL_SYMMDMODETX_DEFAULT                             (_RAC_SYMMDCTRL_SYMMDMODETX_DEFAULT << 5)        /**< Shifted mode DEFAULT for RAC_SYMMDCTRL      */
#define RAC_SYMMDCTRL_SYMMDMODETX_rx_w_swctrl                         (_RAC_SYMMDCTRL_SYMMDMODETX_rx_w_swctrl << 5)    /**< Shifted mode rx_w_swctrl for RAC_SYMMDCTRL  */
#define RAC_SYMMDCTRL_SYMMDMODETX_rx_wo_swctrl                        (_RAC_SYMMDCTRL_SYMMDMODETX_rx_wo_swctrl << 5)   /**< Shifted mode rx_wo_swctrl for RAC_SYMMDCTRL */
#define RAC_SYMMDCTRL_SYMMDMODETX_qnc_dsm2                            (_RAC_SYMMDCTRL_SYMMDMODETX_qnc_dsm2 << 5)       /**< Shifted mode qnc_dsm2 for RAC_SYMMDCTRL     */
#define RAC_SYMMDCTRL_SYMMDMODETX_qnc_dsm3                            (_RAC_SYMMDCTRL_SYMMDMODETX_qnc_dsm3 << 5)       /**< Shifted mode qnc_dsm3 for RAC_SYMMDCTRL     */
#define RAC_SYMMDCTRL_SYMMDMODETX_rxlp_wo_swctrl                      (_RAC_SYMMDCTRL_SYMMDMODETX_rxlp_wo_swctrl << 5) /**< Shifted mode rxlp_wo_swctrl for RAC_SYMMDCTRL*/
#define RAC_SYMMDCTRL_SYMMDMODETX_notuse_5                            (_RAC_SYMMDCTRL_SYMMDMODETX_notuse_5 << 5)       /**< Shifted mode notuse_5 for RAC_SYMMDCTRL     */
#define RAC_SYMMDCTRL_SYMMDMODETX_notuse_6                            (_RAC_SYMMDCTRL_SYMMDMODETX_notuse_6 << 5)       /**< Shifted mode notuse_6 for RAC_SYMMDCTRL     */
#define RAC_SYMMDCTRL_SYMMDMODETX_notuse_7                            (_RAC_SYMMDCTRL_SYMMDMODETX_notuse_7 << 5)       /**< Shifted mode notuse_7 for RAC_SYMMDCTRL     */
#define RAC_SYMMDCTRL_SYMMDENRSDIG                                    (0x1UL << 8)                                     /**< SYMMDENRSDIG                                */
#define _RAC_SYMMDCTRL_SYMMDENRSDIG_SHIFT                             8                                                /**< Shift value for RAC_SYMMDENRSDIG            */
#define _RAC_SYMMDCTRL_SYMMDENRSDIG_MASK                              0x100UL                                          /**< Bit mask for RAC_SYMMDENRSDIG               */
#define _RAC_SYMMDCTRL_SYMMDENRSDIG_DEFAULT                           0x00000000UL                                     /**< Mode DEFAULT for RAC_SYMMDCTRL              */
#define _RAC_SYMMDCTRL_SYMMDENRSDIG_disable                           0x00000000UL                                     /**< Mode disable for RAC_SYMMDCTRL              */
#define _RAC_SYMMDCTRL_SYMMDENRSDIG_enable                            0x00000001UL                                     /**< Mode enable for RAC_SYMMDCTRL               */
#define RAC_SYMMDCTRL_SYMMDENRSDIG_DEFAULT                            (_RAC_SYMMDCTRL_SYMMDENRSDIG_DEFAULT << 8)       /**< Shifted mode DEFAULT for RAC_SYMMDCTRL      */
#define RAC_SYMMDCTRL_SYMMDENRSDIG_disable                            (_RAC_SYMMDCTRL_SYMMDENRSDIG_disable << 8)       /**< Shifted mode disable for RAC_SYMMDCTRL      */
#define RAC_SYMMDCTRL_SYMMDENRSDIG_enable                             (_RAC_SYMMDCTRL_SYMMDENRSDIG_enable << 8)        /**< Shifted mode enable for RAC_SYMMDCTRL       */

/* Bit fields for RAC DIGCLKRETIMECTRL */
#define _RAC_DIGCLKRETIMECTRL_RESETVALUE                              0x00000000UL                                                      /**< Default value for RAC_DIGCLKRETIMECTRL      */
#define _RAC_DIGCLKRETIMECTRL_MASK                                    0x00000777UL                                                      /**< Mask for RAC_DIGCLKRETIMECTRL               */
#define RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEENRETIME                     (0x1UL << 0)                                                      /**< DIGCLKRETIMEENRETIME                        */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEENRETIME_SHIFT              0                                                                 /**< Shift value for RAC_DIGCLKRETIMEENRETIME    */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEENRETIME_MASK               0x1UL                                                             /**< Bit mask for RAC_DIGCLKRETIMEENRETIME       */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEENRETIME_DEFAULT            0x00000000UL                                                      /**< Mode DEFAULT for RAC_DIGCLKRETIMECTRL       */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEENRETIME_disable            0x00000000UL                                                      /**< Mode disable for RAC_DIGCLKRETIMECTRL       */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEENRETIME_enable             0x00000001UL                                                      /**< Mode enable for RAC_DIGCLKRETIMECTRL        */
#define RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEENRETIME_DEFAULT             (_RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEENRETIME_DEFAULT << 0)         /**< Shifted mode DEFAULT for RAC_DIGCLKRETIMECTRL*/
#define RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEENRETIME_disable             (_RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEENRETIME_disable << 0)         /**< Shifted mode disable for RAC_DIGCLKRETIMECTRL*/
#define RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEENRETIME_enable              (_RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEENRETIME_enable << 0)          /**< Shifted mode enable for RAC_DIGCLKRETIMECTRL*/
#define RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEDISRETIME                    (0x1UL << 1)                                                      /**< DIGCLKRETIMEDISRETIME                       */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEDISRETIME_SHIFT             1                                                                 /**< Shift value for RAC_DIGCLKRETIMEDISRETIME   */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEDISRETIME_MASK              0x2UL                                                             /**< Bit mask for RAC_DIGCLKRETIMEDISRETIME      */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEDISRETIME_DEFAULT           0x00000000UL                                                      /**< Mode DEFAULT for RAC_DIGCLKRETIMECTRL       */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEDISRETIME_enable_retime     0x00000000UL                                                      /**< Mode enable_retime for RAC_DIGCLKRETIMECTRL */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEDISRETIME_disable_retime    0x00000001UL                                                      /**< Mode disable_retime for RAC_DIGCLKRETIMECTRL*/
#define RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEDISRETIME_DEFAULT            (_RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEDISRETIME_DEFAULT << 1)        /**< Shifted mode DEFAULT for RAC_DIGCLKRETIMECTRL*/
#define RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEDISRETIME_enable_retime      (_RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEDISRETIME_enable_retime << 1)  /**< Shifted mode enable_retime for RAC_DIGCLKRETIMECTRL*/
#define RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEDISRETIME_disable_retime     (_RAC_DIGCLKRETIMECTRL_DIGCLKRETIMEDISRETIME_disable_retime << 1) /**< Shifted mode disable_retime for RAC_DIGCLKRETIMECTRL*/
#define RAC_DIGCLKRETIMECTRL_DIGCLKRETIMERESETN                       (0x1UL << 2)                                                      /**< DIGCLKRETIMERESETN                          */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMERESETN_SHIFT                2                                                                 /**< Shift value for RAC_DIGCLKRETIMERESETN      */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMERESETN_MASK                 0x4UL                                                             /**< Bit mask for RAC_DIGCLKRETIMERESETN         */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMERESETN_DEFAULT              0x00000000UL                                                      /**< Mode DEFAULT for RAC_DIGCLKRETIMECTRL       */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMERESETN_reset                0x00000000UL                                                      /**< Mode reset for RAC_DIGCLKRETIMECTRL         */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMERESETN_operate              0x00000001UL                                                      /**< Mode operate for RAC_DIGCLKRETIMECTRL       */
#define RAC_DIGCLKRETIMECTRL_DIGCLKRETIMERESETN_DEFAULT               (_RAC_DIGCLKRETIMECTRL_DIGCLKRETIMERESETN_DEFAULT << 2)           /**< Shifted mode DEFAULT for RAC_DIGCLKRETIMECTRL*/
#define RAC_DIGCLKRETIMECTRL_DIGCLKRETIMERESETN_reset                 (_RAC_DIGCLKRETIMECTRL_DIGCLKRETIMERESETN_reset << 2)             /**< Shifted mode reset for RAC_DIGCLKRETIMECTRL */
#define RAC_DIGCLKRETIMECTRL_DIGCLKRETIMERESETN_operate               (_RAC_DIGCLKRETIMECTRL_DIGCLKRETIMERESETN_operate << 2)           /**< Shifted mode operate for RAC_DIGCLKRETIMECTRL*/
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITH_SHIFT                4                                                                 /**< Shift value for RAC_DIGCLKRETIMELIMITH      */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITH_MASK                 0x70UL                                                            /**< Bit mask for RAC_DIGCLKRETIMELIMITH         */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITH_DEFAULT              0x00000000UL                                                      /**< Mode DEFAULT for RAC_DIGCLKRETIMECTRL       */
#define RAC_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITH_DEFAULT               (_RAC_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITH_DEFAULT << 4)           /**< Shifted mode DEFAULT for RAC_DIGCLKRETIMECTRL*/
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITL_SHIFT                8                                                                 /**< Shift value for RAC_DIGCLKRETIMELIMITL      */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITL_MASK                 0x700UL                                                           /**< Bit mask for RAC_DIGCLKRETIMELIMITL         */
#define _RAC_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITL_DEFAULT              0x00000000UL                                                      /**< Mode DEFAULT for RAC_DIGCLKRETIMECTRL       */
#define RAC_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITL_DEFAULT               (_RAC_DIGCLKRETIMECTRL_DIGCLKRETIMELIMITL_DEFAULT << 8)           /**< Shifted mode DEFAULT for RAC_DIGCLKRETIMECTRL*/

/* Bit fields for RAC DIGCLKRETIMESTATUS */
#define _RAC_DIGCLKRETIMESTATUS_RESETVALUE                            0x00000000UL                                                      /**< Default value for RAC_DIGCLKRETIMESTATUS    */
#define _RAC_DIGCLKRETIMESTATUS_MASK                                  0x00000003UL                                                      /**< Mask for RAC_DIGCLKRETIMESTATUS             */
#define RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMECLKSEL                     (0x1UL << 0)                                                      /**< DIGCLKRETIMECLKSEL                          */
#define _RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMECLKSEL_SHIFT              0                                                                 /**< Shift value for RAC_DIGCLKRETIMECLKSEL      */
#define _RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMECLKSEL_MASK               0x1UL                                                             /**< Bit mask for RAC_DIGCLKRETIMECLKSEL         */
#define _RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMECLKSEL_DEFAULT            0x00000000UL                                                      /**< Mode DEFAULT for RAC_DIGCLKRETIMESTATUS     */
#define _RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMECLKSEL_use_raw_clk        0x00000000UL                                                      /**< Mode use_raw_clk for RAC_DIGCLKRETIMESTATUS */
#define _RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMECLKSEL_use_retimed_clk    0x00000001UL                                                      /**< Mode use_retimed_clk for RAC_DIGCLKRETIMESTATUS*/
#define RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMECLKSEL_DEFAULT             (_RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMECLKSEL_DEFAULT << 0)         /**< Shifted mode DEFAULT for RAC_DIGCLKRETIMESTATUS*/
#define RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMECLKSEL_use_raw_clk         (_RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMECLKSEL_use_raw_clk << 0)     /**< Shifted mode use_raw_clk for RAC_DIGCLKRETIMESTATUS*/
#define RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMECLKSEL_use_retimed_clk     (_RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMECLKSEL_use_retimed_clk << 0) /**< Shifted mode use_retimed_clk for RAC_DIGCLKRETIMESTATUS*/
#define RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMERESETNLO                   (0x1UL << 1)                                                      /**< DIGCLKRETIMERESETNLO                        */
#define _RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMERESETNLO_SHIFT            1                                                                 /**< Shift value for RAC_DIGCLKRETIMERESETNLO    */
#define _RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMERESETNLO_MASK             0x2UL                                                             /**< Bit mask for RAC_DIGCLKRETIMERESETNLO       */
#define _RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMERESETNLO_DEFAULT          0x00000000UL                                                      /**< Mode DEFAULT for RAC_DIGCLKRETIMESTATUS     */
#define _RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMERESETNLO_lo               0x00000000UL                                                      /**< Mode lo for RAC_DIGCLKRETIMESTATUS          */
#define _RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMERESETNLO_hi               0x00000001UL                                                      /**< Mode hi for RAC_DIGCLKRETIMESTATUS          */
#define RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMERESETNLO_DEFAULT           (_RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMERESETNLO_DEFAULT << 1)       /**< Shifted mode DEFAULT for RAC_DIGCLKRETIMESTATUS*/
#define RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMERESETNLO_lo                (_RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMERESETNLO_lo << 1)            /**< Shifted mode lo for RAC_DIGCLKRETIMESTATUS  */
#define RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMERESETNLO_hi                (_RAC_DIGCLKRETIMESTATUS_DIGCLKRETIMERESETNLO_hi << 1)            /**< Shifted mode hi for RAC_DIGCLKRETIMESTATUS  */

/* Bit fields for RAC XORETIMECTRL */
#define _RAC_XORETIMECTRL_RESETVALUE                                  0x00000000UL                                              /**< Default value for RAC_XORETIMECTRL          */
#define _RAC_XORETIMECTRL_MASK                                        0x00000777UL                                              /**< Mask for RAC_XORETIMECTRL                   */
#define RAC_XORETIMECTRL_XORETIMEENRETIME                             (0x1UL << 0)                                              /**< XORETIMEENRETIME                            */
#define _RAC_XORETIMECTRL_XORETIMEENRETIME_SHIFT                      0                                                         /**< Shift value for RAC_XORETIMEENRETIME        */
#define _RAC_XORETIMECTRL_XORETIMEENRETIME_MASK                       0x1UL                                                     /**< Bit mask for RAC_XORETIMEENRETIME           */
#define _RAC_XORETIMECTRL_XORETIMEENRETIME_DEFAULT                    0x00000000UL                                              /**< Mode DEFAULT for RAC_XORETIMECTRL           */
#define _RAC_XORETIMECTRL_XORETIMEENRETIME_disable                    0x00000000UL                                              /**< Mode disable for RAC_XORETIMECTRL           */
#define _RAC_XORETIMECTRL_XORETIMEENRETIME_enable                     0x00000001UL                                              /**< Mode enable for RAC_XORETIMECTRL            */
#define RAC_XORETIMECTRL_XORETIMEENRETIME_DEFAULT                     (_RAC_XORETIMECTRL_XORETIMEENRETIME_DEFAULT << 0)         /**< Shifted mode DEFAULT for RAC_XORETIMECTRL   */
#define RAC_XORETIMECTRL_XORETIMEENRETIME_disable                     (_RAC_XORETIMECTRL_XORETIMEENRETIME_disable << 0)         /**< Shifted mode disable for RAC_XORETIMECTRL   */
#define RAC_XORETIMECTRL_XORETIMEENRETIME_enable                      (_RAC_XORETIMECTRL_XORETIMEENRETIME_enable << 0)          /**< Shifted mode enable for RAC_XORETIMECTRL    */
#define RAC_XORETIMECTRL_XORETIMEDISRETIME                            (0x1UL << 1)                                              /**< XORETIMEDISRETIME                           */
#define _RAC_XORETIMECTRL_XORETIMEDISRETIME_SHIFT                     1                                                         /**< Shift value for RAC_XORETIMEDISRETIME       */
#define _RAC_XORETIMECTRL_XORETIMEDISRETIME_MASK                      0x2UL                                                     /**< Bit mask for RAC_XORETIMEDISRETIME          */
#define _RAC_XORETIMECTRL_XORETIMEDISRETIME_DEFAULT                   0x00000000UL                                              /**< Mode DEFAULT for RAC_XORETIMECTRL           */
#define _RAC_XORETIMECTRL_XORETIMEDISRETIME_enable_retime             0x00000000UL                                              /**< Mode enable_retime for RAC_XORETIMECTRL     */
#define _RAC_XORETIMECTRL_XORETIMEDISRETIME_disable_retime            0x00000001UL                                              /**< Mode disable_retime for RAC_XORETIMECTRL    */
#define RAC_XORETIMECTRL_XORETIMEDISRETIME_DEFAULT                    (_RAC_XORETIMECTRL_XORETIMEDISRETIME_DEFAULT << 1)        /**< Shifted mode DEFAULT for RAC_XORETIMECTRL   */
#define RAC_XORETIMECTRL_XORETIMEDISRETIME_enable_retime              (_RAC_XORETIMECTRL_XORETIMEDISRETIME_enable_retime << 1)  /**< Shifted mode enable_retime for RAC_XORETIMECTRL*/
#define RAC_XORETIMECTRL_XORETIMEDISRETIME_disable_retime             (_RAC_XORETIMECTRL_XORETIMEDISRETIME_disable_retime << 1) /**< Shifted mode disable_retime for RAC_XORETIMECTRL*/
#define RAC_XORETIMECTRL_XORETIMERESETN                               (0x1UL << 2)                                              /**< XORETIMERESETN                              */
#define _RAC_XORETIMECTRL_XORETIMERESETN_SHIFT                        2                                                         /**< Shift value for RAC_XORETIMERESETN          */
#define _RAC_XORETIMECTRL_XORETIMERESETN_MASK                         0x4UL                                                     /**< Bit mask for RAC_XORETIMERESETN             */
#define _RAC_XORETIMECTRL_XORETIMERESETN_DEFAULT                      0x00000000UL                                              /**< Mode DEFAULT for RAC_XORETIMECTRL           */
#define _RAC_XORETIMECTRL_XORETIMERESETN_reset                        0x00000000UL                                              /**< Mode reset for RAC_XORETIMECTRL             */
#define _RAC_XORETIMECTRL_XORETIMERESETN_operate                      0x00000001UL                                              /**< Mode operate for RAC_XORETIMECTRL           */
#define RAC_XORETIMECTRL_XORETIMERESETN_DEFAULT                       (_RAC_XORETIMECTRL_XORETIMERESETN_DEFAULT << 2)           /**< Shifted mode DEFAULT for RAC_XORETIMECTRL   */
#define RAC_XORETIMECTRL_XORETIMERESETN_reset                         (_RAC_XORETIMECTRL_XORETIMERESETN_reset << 2)             /**< Shifted mode reset for RAC_XORETIMECTRL     */
#define RAC_XORETIMECTRL_XORETIMERESETN_operate                       (_RAC_XORETIMECTRL_XORETIMERESETN_operate << 2)           /**< Shifted mode operate for RAC_XORETIMECTRL   */
#define _RAC_XORETIMECTRL_XORETIMELIMITH_SHIFT                        4                                                         /**< Shift value for RAC_XORETIMELIMITH          */
#define _RAC_XORETIMECTRL_XORETIMELIMITH_MASK                         0x70UL                                                    /**< Bit mask for RAC_XORETIMELIMITH             */
#define _RAC_XORETIMECTRL_XORETIMELIMITH_DEFAULT                      0x00000000UL                                              /**< Mode DEFAULT for RAC_XORETIMECTRL           */
#define RAC_XORETIMECTRL_XORETIMELIMITH_DEFAULT                       (_RAC_XORETIMECTRL_XORETIMELIMITH_DEFAULT << 4)           /**< Shifted mode DEFAULT for RAC_XORETIMECTRL   */
#define _RAC_XORETIMECTRL_XORETIMELIMITL_SHIFT                        8                                                         /**< Shift value for RAC_XORETIMELIMITL          */
#define _RAC_XORETIMECTRL_XORETIMELIMITL_MASK                         0x700UL                                                   /**< Bit mask for RAC_XORETIMELIMITL             */
#define _RAC_XORETIMECTRL_XORETIMELIMITL_DEFAULT                      0x00000000UL                                              /**< Mode DEFAULT for RAC_XORETIMECTRL           */
#define RAC_XORETIMECTRL_XORETIMELIMITL_DEFAULT                       (_RAC_XORETIMECTRL_XORETIMELIMITL_DEFAULT << 8)           /**< Shifted mode DEFAULT for RAC_XORETIMECTRL   */

/* Bit fields for RAC XORETIMESTATUS */
#define _RAC_XORETIMESTATUS_RESETVALUE                                0x00000000UL                                              /**< Default value for RAC_XORETIMESTATUS        */
#define _RAC_XORETIMESTATUS_MASK                                      0x00000003UL                                              /**< Mask for RAC_XORETIMESTATUS                 */
#define RAC_XORETIMESTATUS_XORETIMECLKSEL                             (0x1UL << 0)                                              /**< XORETIMECLKSEL                              */
#define _RAC_XORETIMESTATUS_XORETIMECLKSEL_SHIFT                      0                                                         /**< Shift value for RAC_XORETIMECLKSEL          */
#define _RAC_XORETIMESTATUS_XORETIMECLKSEL_MASK                       0x1UL                                                     /**< Bit mask for RAC_XORETIMECLKSEL             */
#define _RAC_XORETIMESTATUS_XORETIMECLKSEL_DEFAULT                    0x00000000UL                                              /**< Mode DEFAULT for RAC_XORETIMESTATUS         */
#define _RAC_XORETIMESTATUS_XORETIMECLKSEL_use_raw_clk                0x00000000UL                                              /**< Mode use_raw_clk for RAC_XORETIMESTATUS     */
#define _RAC_XORETIMESTATUS_XORETIMECLKSEL_use_retimed_clk            0x00000001UL                                              /**< Mode use_retimed_clk for RAC_XORETIMESTATUS */
#define RAC_XORETIMESTATUS_XORETIMECLKSEL_DEFAULT                     (_RAC_XORETIMESTATUS_XORETIMECLKSEL_DEFAULT << 0)         /**< Shifted mode DEFAULT for RAC_XORETIMESTATUS */
#define RAC_XORETIMESTATUS_XORETIMECLKSEL_use_raw_clk                 (_RAC_XORETIMESTATUS_XORETIMECLKSEL_use_raw_clk << 0)     /**< Shifted mode use_raw_clk for RAC_XORETIMESTATUS*/
#define RAC_XORETIMESTATUS_XORETIMECLKSEL_use_retimed_clk             (_RAC_XORETIMESTATUS_XORETIMECLKSEL_use_retimed_clk << 0) /**< Shifted mode use_retimed_clk for RAC_XORETIMESTATUS*/
#define RAC_XORETIMESTATUS_XORETIMERESETNLO                           (0x1UL << 1)                                              /**< XORETIMERESETNLO                            */
#define _RAC_XORETIMESTATUS_XORETIMERESETNLO_SHIFT                    1                                                         /**< Shift value for RAC_XORETIMERESETNLO        */
#define _RAC_XORETIMESTATUS_XORETIMERESETNLO_MASK                     0x2UL                                                     /**< Bit mask for RAC_XORETIMERESETNLO           */
#define _RAC_XORETIMESTATUS_XORETIMERESETNLO_DEFAULT                  0x00000000UL                                              /**< Mode DEFAULT for RAC_XORETIMESTATUS         */
#define _RAC_XORETIMESTATUS_XORETIMERESETNLO_lo                       0x00000000UL                                              /**< Mode lo for RAC_XORETIMESTATUS              */
#define _RAC_XORETIMESTATUS_XORETIMERESETNLO_hi                       0x00000001UL                                              /**< Mode hi for RAC_XORETIMESTATUS              */
#define RAC_XORETIMESTATUS_XORETIMERESETNLO_DEFAULT                   (_RAC_XORETIMESTATUS_XORETIMERESETNLO_DEFAULT << 1)       /**< Shifted mode DEFAULT for RAC_XORETIMESTATUS */
#define RAC_XORETIMESTATUS_XORETIMERESETNLO_lo                        (_RAC_XORETIMESTATUS_XORETIMERESETNLO_lo << 1)            /**< Shifted mode lo for RAC_XORETIMESTATUS      */
#define RAC_XORETIMESTATUS_XORETIMERESETNLO_hi                        (_RAC_XORETIMESTATUS_XORETIMERESETNLO_hi << 1)            /**< Shifted mode hi for RAC_XORETIMESTATUS      */

/* Bit fields for RAC AGCOVERWRITE0 */
#define _RAC_AGCOVERWRITE0_RESETVALUE                                 0x00000000UL                                       /**< Default value for RAC_AGCOVERWRITE0         */
#define _RAC_AGCOVERWRITE0_MASK                                       0x03F0FFFFUL                                       /**< Mask for RAC_AGCOVERWRITE0                  */
#define RAC_AGCOVERWRITE0_ENMANLNAMIXRFATT                            (0x1UL << 0)                                       /**< Enable RAC Overwite PN                      */
#define _RAC_AGCOVERWRITE0_ENMANLNAMIXRFATT_SHIFT                     0                                                  /**< Shift value for RAC_ENMANLNAMIXRFATT        */
#define _RAC_AGCOVERWRITE0_ENMANLNAMIXRFATT_MASK                      0x1UL                                              /**< Bit mask for RAC_ENMANLNAMIXRFATT           */
#define _RAC_AGCOVERWRITE0_ENMANLNAMIXRFATT_DEFAULT                   0x00000000UL                                       /**< Mode DEFAULT for RAC_AGCOVERWRITE0          */
#define RAC_AGCOVERWRITE0_ENMANLNAMIXRFATT_DEFAULT                    (_RAC_AGCOVERWRITE0_ENMANLNAMIXRFATT_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_AGCOVERWRITE0  */
#define RAC_AGCOVERWRITE0_ENMANLNAMIXSLICE                            (0x1UL << 1)                                       /**< Enable RAC Overwite LNA                     */
#define _RAC_AGCOVERWRITE0_ENMANLNAMIXSLICE_SHIFT                     1                                                  /**< Shift value for RAC_ENMANLNAMIXSLICE        */
#define _RAC_AGCOVERWRITE0_ENMANLNAMIXSLICE_MASK                      0x2UL                                              /**< Bit mask for RAC_ENMANLNAMIXSLICE           */
#define _RAC_AGCOVERWRITE0_ENMANLNAMIXSLICE_DEFAULT                   0x00000000UL                                       /**< Mode DEFAULT for RAC_AGCOVERWRITE0          */
#define RAC_AGCOVERWRITE0_ENMANLNAMIXSLICE_DEFAULT                    (_RAC_AGCOVERWRITE0_ENMANLNAMIXSLICE_DEFAULT << 1) /**< Shifted mode DEFAULT for RAC_AGCOVERWRITE0  */
#define RAC_AGCOVERWRITE0_ENMANPGAGAIN                                (0x1UL << 2)                                       /**< Enable RAC Overwite PGA                     */
#define _RAC_AGCOVERWRITE0_ENMANPGAGAIN_SHIFT                         2                                                  /**< Shift value for RAC_ENMANPGAGAIN            */
#define _RAC_AGCOVERWRITE0_ENMANPGAGAIN_MASK                          0x4UL                                              /**< Bit mask for RAC_ENMANPGAGAIN               */
#define _RAC_AGCOVERWRITE0_ENMANPGAGAIN_DEFAULT                       0x00000000UL                                       /**< Mode DEFAULT for RAC_AGCOVERWRITE0          */
#define RAC_AGCOVERWRITE0_ENMANPGAGAIN_DEFAULT                        (_RAC_AGCOVERWRITE0_ENMANPGAGAIN_DEFAULT << 2)     /**< Shifted mode DEFAULT for RAC_AGCOVERWRITE0  */
#define RAC_AGCOVERWRITE0_ENMANIFADCSCALE                             (0x1UL << 3)                                       /**< Enable RAC Overwite PN                      */
#define _RAC_AGCOVERWRITE0_ENMANIFADCSCALE_SHIFT                      3                                                  /**< Shift value for RAC_ENMANIFADCSCALE         */
#define _RAC_AGCOVERWRITE0_ENMANIFADCSCALE_MASK                       0x8UL                                              /**< Bit mask for RAC_ENMANIFADCSCALE            */
#define _RAC_AGCOVERWRITE0_ENMANIFADCSCALE_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for RAC_AGCOVERWRITE0          */
#define RAC_AGCOVERWRITE0_ENMANIFADCSCALE_DEFAULT                     (_RAC_AGCOVERWRITE0_ENMANIFADCSCALE_DEFAULT << 3)  /**< Shifted mode DEFAULT for RAC_AGCOVERWRITE0  */
#define _RAC_AGCOVERWRITE0_MANLNAMIXSLICE0_SHIFT                      4                                                  /**< Shift value for RAC_MANLNAMIXSLICE0         */
#define _RAC_AGCOVERWRITE0_MANLNAMIXSLICE0_MASK                       0x3F0UL                                            /**< Bit mask for RAC_MANLNAMIXSLICE0            */
#define _RAC_AGCOVERWRITE0_MANLNAMIXSLICE0_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for RAC_AGCOVERWRITE0          */
#define RAC_AGCOVERWRITE0_MANLNAMIXSLICE0_DEFAULT                     (_RAC_AGCOVERWRITE0_MANLNAMIXSLICE0_DEFAULT << 4)  /**< Shifted mode DEFAULT for RAC_AGCOVERWRITE0  */
#define _RAC_AGCOVERWRITE0_MANLNAMIXSLICE1_SHIFT                      10                                                 /**< Shift value for RAC_MANLNAMIXSLICE1         */
#define _RAC_AGCOVERWRITE0_MANLNAMIXSLICE1_MASK                       0xFC00UL                                           /**< Bit mask for RAC_MANLNAMIXSLICE1            */
#define _RAC_AGCOVERWRITE0_MANLNAMIXSLICE1_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for RAC_AGCOVERWRITE0          */
#define RAC_AGCOVERWRITE0_MANLNAMIXSLICE1_DEFAULT                     (_RAC_AGCOVERWRITE0_MANLNAMIXSLICE1_DEFAULT << 10) /**< Shifted mode DEFAULT for RAC_AGCOVERWRITE0  */
#define _RAC_AGCOVERWRITE0_MANPGAGAIN_SHIFT                           20                                                 /**< Shift value for RAC_MANPGAGAIN              */
#define _RAC_AGCOVERWRITE0_MANPGAGAIN_MASK                            0xF00000UL                                         /**< Bit mask for RAC_MANPGAGAIN                 */
#define _RAC_AGCOVERWRITE0_MANPGAGAIN_DEFAULT                         0x00000000UL                                       /**< Mode DEFAULT for RAC_AGCOVERWRITE0          */
#define RAC_AGCOVERWRITE0_MANPGAGAIN_DEFAULT                          (_RAC_AGCOVERWRITE0_MANPGAGAIN_DEFAULT << 20)      /**< Shifted mode DEFAULT for RAC_AGCOVERWRITE0  */
#define _RAC_AGCOVERWRITE0_MANIFADCSCALE_SHIFT                        24                                                 /**< Shift value for RAC_MANIFADCSCALE           */
#define _RAC_AGCOVERWRITE0_MANIFADCSCALE_MASK                         0x3000000UL                                        /**< Bit mask for RAC_MANIFADCSCALE              */
#define _RAC_AGCOVERWRITE0_MANIFADCSCALE_DEFAULT                      0x00000000UL                                       /**< Mode DEFAULT for RAC_AGCOVERWRITE0          */
#define RAC_AGCOVERWRITE0_MANIFADCSCALE_DEFAULT                       (_RAC_AGCOVERWRITE0_MANIFADCSCALE_DEFAULT << 24)   /**< Shifted mode DEFAULT for RAC_AGCOVERWRITE0  */

/* Bit fields for RAC AGCOVERWRITE1 */
#define _RAC_AGCOVERWRITE1_RESETVALUE                                 0x00000000UL                                       /**< Default value for RAC_AGCOVERWRITE1         */
#define _RAC_AGCOVERWRITE1_MASK                                       0x3FFF3FFFUL                                       /**< Mask for RAC_AGCOVERWRITE1                  */
#define _RAC_AGCOVERWRITE1_MANLNAMIXRFATT0_SHIFT                      0                                                  /**< Shift value for RAC_MANLNAMIXRFATT0         */
#define _RAC_AGCOVERWRITE1_MANLNAMIXRFATT0_MASK                       0x3FFFUL                                           /**< Bit mask for RAC_MANLNAMIXRFATT0            */
#define _RAC_AGCOVERWRITE1_MANLNAMIXRFATT0_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for RAC_AGCOVERWRITE1          */
#define RAC_AGCOVERWRITE1_MANLNAMIXRFATT0_DEFAULT                     (_RAC_AGCOVERWRITE1_MANLNAMIXRFATT0_DEFAULT << 0)  /**< Shifted mode DEFAULT for RAC_AGCOVERWRITE1  */
#define _RAC_AGCOVERWRITE1_MANLNAMIXRFATT1_SHIFT                      16                                                 /**< Shift value for RAC_MANLNAMIXRFATT1         */
#define _RAC_AGCOVERWRITE1_MANLNAMIXRFATT1_MASK                       0x3FFF0000UL                                       /**< Bit mask for RAC_MANLNAMIXRFATT1            */
#define _RAC_AGCOVERWRITE1_MANLNAMIXRFATT1_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for RAC_AGCOVERWRITE1          */
#define RAC_AGCOVERWRITE1_MANLNAMIXRFATT1_DEFAULT                     (_RAC_AGCOVERWRITE1_MANLNAMIXRFATT1_DEFAULT << 16) /**< Shifted mode DEFAULT for RAC_AGCOVERWRITE1  */

/* Bit fields for RAC AGCOVERWRITE2 */
#define _RAC_AGCOVERWRITE2_RESETVALUE                                 0x00000000UL                                           /**< Default value for RAC_AGCOVERWRITE2         */
#define _RAC_AGCOVERWRITE2_MASK                                       0x0000FFFFUL                                           /**< Mask for RAC_AGCOVERWRITE2                  */
#define RAC_AGCOVERWRITE2_ENMANFENOTCH                                (0x1UL << 0)                                           /**< Enable RAC Overwrite FENOTCH                */
#define _RAC_AGCOVERWRITE2_ENMANFENOTCH_SHIFT                         0                                                      /**< Shift value for RAC_ENMANFENOTCH            */
#define _RAC_AGCOVERWRITE2_ENMANFENOTCH_MASK                          0x1UL                                                  /**< Bit mask for RAC_ENMANFENOTCH               */
#define _RAC_AGCOVERWRITE2_ENMANFENOTCH_DEFAULT                       0x00000000UL                                           /**< Mode DEFAULT for RAC_AGCOVERWRITE2          */
#define RAC_AGCOVERWRITE2_ENMANFENOTCH_DEFAULT                        (_RAC_AGCOVERWRITE2_ENMANFENOTCH_DEFAULT << 0)         /**< Shifted mode DEFAULT for RAC_AGCOVERWRITE2  */
#define RAC_AGCOVERWRITE2_MANFENOTCHEN                                (0x1UL << 1)                                           /**< RAC Overwrite fenotchen                     */
#define _RAC_AGCOVERWRITE2_MANFENOTCHEN_SHIFT                         1                                                      /**< Shift value for RAC_MANFENOTCHEN            */
#define _RAC_AGCOVERWRITE2_MANFENOTCHEN_MASK                          0x2UL                                                  /**< Bit mask for RAC_MANFENOTCHEN               */
#define _RAC_AGCOVERWRITE2_MANFENOTCHEN_DEFAULT                       0x00000000UL                                           /**< Mode DEFAULT for RAC_AGCOVERWRITE2          */
#define RAC_AGCOVERWRITE2_MANFENOTCHEN_DEFAULT                        (_RAC_AGCOVERWRITE2_MANFENOTCHEN_DEFAULT << 1)         /**< Shifted mode DEFAULT for RAC_AGCOVERWRITE2  */
#define _RAC_AGCOVERWRITE2_MANFENOTCHATTNSEL_SHIFT                    2                                                      /**< Shift value for RAC_MANFENOTCHATTNSEL       */
#define _RAC_AGCOVERWRITE2_MANFENOTCHATTNSEL_MASK                     0x3CUL                                                 /**< Bit mask for RAC_MANFENOTCHATTNSEL          */
#define _RAC_AGCOVERWRITE2_MANFENOTCHATTNSEL_DEFAULT                  0x00000000UL                                           /**< Mode DEFAULT for RAC_AGCOVERWRITE2          */
#define RAC_AGCOVERWRITE2_MANFENOTCHATTNSEL_DEFAULT                   (_RAC_AGCOVERWRITE2_MANFENOTCHATTNSEL_DEFAULT << 2)    /**< Shifted mode DEFAULT for RAC_AGCOVERWRITE2  */
#define RAC_AGCOVERWRITE2_MANFENOTCHRATTNENRF0                        (0x1UL << 6)                                           /**< RAC Overwrite fenotchrattnenrf0             */
#define _RAC_AGCOVERWRITE2_MANFENOTCHRATTNENRF0_SHIFT                 6                                                      /**< Shift value for RAC_MANFENOTCHRATTNENRF0    */
#define _RAC_AGCOVERWRITE2_MANFENOTCHRATTNENRF0_MASK                  0x40UL                                                 /**< Bit mask for RAC_MANFENOTCHRATTNENRF0       */
#define _RAC_AGCOVERWRITE2_MANFENOTCHRATTNENRF0_DEFAULT               0x00000000UL                                           /**< Mode DEFAULT for RAC_AGCOVERWRITE2          */
#define RAC_AGCOVERWRITE2_MANFENOTCHRATTNENRF0_DEFAULT                (_RAC_AGCOVERWRITE2_MANFENOTCHRATTNENRF0_DEFAULT << 6) /**< Shifted mode DEFAULT for RAC_AGCOVERWRITE2  */
#define RAC_AGCOVERWRITE2_MANFENOTCHRATTNENRF1                        (0x1UL << 7)                                           /**< RAC Overwrite fenotchrattnenrf1             */
#define _RAC_AGCOVERWRITE2_MANFENOTCHRATTNENRF1_SHIFT                 7                                                      /**< Shift value for RAC_MANFENOTCHRATTNENRF1    */
#define _RAC_AGCOVERWRITE2_MANFENOTCHRATTNENRF1_MASK                  0x80UL                                                 /**< Bit mask for RAC_MANFENOTCHRATTNENRF1       */
#define _RAC_AGCOVERWRITE2_MANFENOTCHRATTNENRF1_DEFAULT               0x00000000UL                                           /**< Mode DEFAULT for RAC_AGCOVERWRITE2          */
#define RAC_AGCOVERWRITE2_MANFENOTCHRATTNENRF1_DEFAULT                (_RAC_AGCOVERWRITE2_MANFENOTCHRATTNENRF1_DEFAULT << 7) /**< Shifted mode DEFAULT for RAC_AGCOVERWRITE2  */
#define _RAC_AGCOVERWRITE2_MANFENOTCHCAPCRSE_SHIFT                    8                                                      /**< Shift value for RAC_MANFENOTCHCAPCRSE       */
#define _RAC_AGCOVERWRITE2_MANFENOTCHCAPCRSE_MASK                     0xF00UL                                                /**< Bit mask for RAC_MANFENOTCHCAPCRSE          */
#define _RAC_AGCOVERWRITE2_MANFENOTCHCAPCRSE_DEFAULT                  0x00000000UL                                           /**< Mode DEFAULT for RAC_AGCOVERWRITE2          */
#define RAC_AGCOVERWRITE2_MANFENOTCHCAPCRSE_DEFAULT                   (_RAC_AGCOVERWRITE2_MANFENOTCHCAPCRSE_DEFAULT << 8)    /**< Shifted mode DEFAULT for RAC_AGCOVERWRITE2  */
#define _RAC_AGCOVERWRITE2_MANFENOTCHCAPFINE_SHIFT                    12                                                     /**< Shift value for RAC_MANFENOTCHCAPFINE       */
#define _RAC_AGCOVERWRITE2_MANFENOTCHCAPFINE_MASK                     0xF000UL                                               /**< Bit mask for RAC_MANFENOTCHCAPFINE          */
#define _RAC_AGCOVERWRITE2_MANFENOTCHCAPFINE_DEFAULT                  0x00000000UL                                           /**< Mode DEFAULT for RAC_AGCOVERWRITE2          */
#define RAC_AGCOVERWRITE2_MANFENOTCHCAPFINE_DEFAULT                   (_RAC_AGCOVERWRITE2_MANFENOTCHCAPFINE_DEFAULT << 12)   /**< Shifted mode DEFAULT for RAC_AGCOVERWRITE2  */

/* Bit fields for RAC PACTRL */
#define _RAC_PACTRL_RESETVALUE                                        0x00000000UL                                           /**< Default value for RAC_PACTRL                */
#define _RAC_PACTRL_MASK                                              0x0001FFFFUL                                           /**< Mask for RAC_PACTRL                         */
#define RAC_PACTRL_TX0DBMLATCHBYPASS                                  (0x1UL << 0)                                           /**< TX0DBMLATCHBYPASS                           */
#define _RAC_PACTRL_TX0DBMLATCHBYPASS_SHIFT                           0                                                      /**< Shift value for RAC_TX0DBMLATCHBYPASS       */
#define _RAC_PACTRL_TX0DBMLATCHBYPASS_MASK                            0x1UL                                                  /**< Bit mask for RAC_TX0DBMLATCHBYPASS          */
#define _RAC_PACTRL_TX0DBMLATCHBYPASS_DEFAULT                         0x00000000UL                                           /**< Mode DEFAULT for RAC_PACTRL                 */
#define _RAC_PACTRL_TX0DBMLATCHBYPASS_disable                         0x00000000UL                                           /**< Mode disable for RAC_PACTRL                 */
#define _RAC_PACTRL_TX0DBMLATCHBYPASS_enable                          0x00000001UL                                           /**< Mode enable for RAC_PACTRL                  */
#define RAC_PACTRL_TX0DBMLATCHBYPASS_DEFAULT                          (_RAC_PACTRL_TX0DBMLATCHBYPASS_DEFAULT << 0)           /**< Shifted mode DEFAULT for RAC_PACTRL         */
#define RAC_PACTRL_TX0DBMLATCHBYPASS_disable                          (_RAC_PACTRL_TX0DBMLATCHBYPASS_disable << 0)           /**< Shifted mode disable for RAC_PACTRL         */
#define RAC_PACTRL_TX0DBMLATCHBYPASS_enable                           (_RAC_PACTRL_TX0DBMLATCHBYPASS_enable << 0)            /**< Shifted mode enable for RAC_PACTRL          */
#define RAC_PACTRL_TX0DBMSLICERESET                                   (0x1UL << 1)                                           /**< TX0DBMSLICERESET                            */
#define _RAC_PACTRL_TX0DBMSLICERESET_SHIFT                            1                                                      /**< Shift value for RAC_TX0DBMSLICERESET        */
#define _RAC_PACTRL_TX0DBMSLICERESET_MASK                             0x2UL                                                  /**< Bit mask for RAC_TX0DBMSLICERESET           */
#define _RAC_PACTRL_TX0DBMSLICERESET_DEFAULT                          0x00000000UL                                           /**< Mode DEFAULT for RAC_PACTRL                 */
#define _RAC_PACTRL_TX0DBMSLICERESET_active                           0x00000000UL                                           /**< Mode active for RAC_PACTRL                  */
#define _RAC_PACTRL_TX0DBMSLICERESET_reset                            0x00000001UL                                           /**< Mode reset for RAC_PACTRL                   */
#define RAC_PACTRL_TX0DBMSLICERESET_DEFAULT                           (_RAC_PACTRL_TX0DBMSLICERESET_DEFAULT << 1)            /**< Shifted mode DEFAULT for RAC_PACTRL         */
#define RAC_PACTRL_TX0DBMSLICERESET_active                            (_RAC_PACTRL_TX0DBMSLICERESET_active << 1)             /**< Shifted mode active for RAC_PACTRL          */
#define RAC_PACTRL_TX0DBMSLICERESET_reset                             (_RAC_PACTRL_TX0DBMSLICERESET_reset << 1)              /**< Shifted mode reset for RAC_PACTRL           */
#define RAC_PACTRL_TXPABYPASSPREDRVREG                                (0x1UL << 2)                                           /**< TXPABYPASSPREDRVREG                         */
#define _RAC_PACTRL_TXPABYPASSPREDRVREG_SHIFT                         2                                                      /**< Shift value for RAC_TXPABYPASSPREDRVREG     */
#define _RAC_PACTRL_TXPABYPASSPREDRVREG_MASK                          0x4UL                                                  /**< Bit mask for RAC_TXPABYPASSPREDRVREG        */
#define _RAC_PACTRL_TXPABYPASSPREDRVREG_DEFAULT                       0x00000000UL                                           /**< Mode DEFAULT for RAC_PACTRL                 */
#define _RAC_PACTRL_TXPABYPASSPREDRVREG_not_bypass                    0x00000000UL                                           /**< Mode not_bypass for RAC_PACTRL              */
#define _RAC_PACTRL_TXPABYPASSPREDRVREG_bypass                        0x00000001UL                                           /**< Mode bypass for RAC_PACTRL                  */
#define RAC_PACTRL_TXPABYPASSPREDRVREG_DEFAULT                        (_RAC_PACTRL_TXPABYPASSPREDRVREG_DEFAULT << 2)         /**< Shifted mode DEFAULT for RAC_PACTRL         */
#define RAC_PACTRL_TXPABYPASSPREDRVREG_not_bypass                     (_RAC_PACTRL_TXPABYPASSPREDRVREG_not_bypass << 2)      /**< Shifted mode not_bypass for RAC_PACTRL      */
#define RAC_PACTRL_TXPABYPASSPREDRVREG_bypass                         (_RAC_PACTRL_TXPABYPASSPREDRVREG_bypass << 2)          /**< Shifted mode bypass for RAC_PACTRL          */
#define RAC_PACTRL_TXPAPULLDOWNVDDPA                                  (0x1UL << 3)                                           /**< TXPAPULLDOWNVDDPA                           */
#define _RAC_PACTRL_TXPAPULLDOWNVDDPA_SHIFT                           3                                                      /**< Shift value for RAC_TXPAPULLDOWNVDDPA       */
#define _RAC_PACTRL_TXPAPULLDOWNVDDPA_MASK                            0x8UL                                                  /**< Bit mask for RAC_TXPAPULLDOWNVDDPA          */
#define _RAC_PACTRL_TXPAPULLDOWNVDDPA_DEFAULT                         0x00000000UL                                           /**< Mode DEFAULT for RAC_PACTRL                 */
#define _RAC_PACTRL_TXPAPULLDOWNVDDPA_not_pull_down                   0x00000000UL                                           /**< Mode not_pull_down for RAC_PACTRL           */
#define _RAC_PACTRL_TXPAPULLDOWNVDDPA_pull_down_vddpa                 0x00000001UL                                           /**< Mode pull_down_vddpa for RAC_PACTRL         */
#define RAC_PACTRL_TXPAPULLDOWNVDDPA_DEFAULT                          (_RAC_PACTRL_TXPAPULLDOWNVDDPA_DEFAULT << 3)           /**< Shifted mode DEFAULT for RAC_PACTRL         */
#define RAC_PACTRL_TXPAPULLDOWNVDDPA_not_pull_down                    (_RAC_PACTRL_TXPAPULLDOWNVDDPA_not_pull_down << 3)     /**< Shifted mode not_pull_down for RAC_PACTRL   */
#define RAC_PACTRL_TXPAPULLDOWNVDDPA_pull_down_vddpa                  (_RAC_PACTRL_TXPAPULLDOWNVDDPA_pull_down_vddpa << 3)   /**< Shifted mode pull_down_vddpa for RAC_PACTRL */
#define _RAC_PACTRL_TXPAPOWER_SHIFT                                   4                                                      /**< Shift value for RAC_TXPAPOWER               */
#define _RAC_PACTRL_TXPAPOWER_MASK                                    0xF0UL                                                 /**< Bit mask for RAC_TXPAPOWER                  */
#define _RAC_PACTRL_TXPAPOWER_DEFAULT                                 0x00000000UL                                           /**< Mode DEFAULT for RAC_PACTRL                 */
#define _RAC_PACTRL_TXPAPOWER_t0stripeon                              0x00000000UL                                           /**< Mode t0stripeon for RAC_PACTRL              */
#define _RAC_PACTRL_TXPAPOWER_t1stripeon                              0x00000001UL                                           /**< Mode t1stripeon for RAC_PACTRL              */
#define _RAC_PACTRL_TXPAPOWER_t2stripeon                              0x00000002UL                                           /**< Mode t2stripeon for RAC_PACTRL              */
#define _RAC_PACTRL_TXPAPOWER_t3stripeon                              0x00000003UL                                           /**< Mode t3stripeon for RAC_PACTRL              */
#define _RAC_PACTRL_TXPAPOWER_t4stripeon                              0x00000004UL                                           /**< Mode t4stripeon for RAC_PACTRL              */
#define _RAC_PACTRL_TXPAPOWER_t5stripeon                              0x00000005UL                                           /**< Mode t5stripeon for RAC_PACTRL              */
#define _RAC_PACTRL_TXPAPOWER_t6stripeon                              0x00000006UL                                           /**< Mode t6stripeon for RAC_PACTRL              */
#define _RAC_PACTRL_TXPAPOWER_t7stripeon                              0x00000007UL                                           /**< Mode t7stripeon for RAC_PACTRL              */
#define _RAC_PACTRL_TXPAPOWER_t8stripeon                              0x00000008UL                                           /**< Mode t8stripeon for RAC_PACTRL              */
#define _RAC_PACTRL_TXPAPOWER_t9stripeon                              0x00000009UL                                           /**< Mode t9stripeon for RAC_PACTRL              */
#define _RAC_PACTRL_TXPAPOWER_t10stripeon                             0x0000000AUL                                           /**< Mode t10stripeon for RAC_PACTRL             */
#define _RAC_PACTRL_TXPAPOWER_t11stripeon                             0x0000000BUL                                           /**< Mode t11stripeon for RAC_PACTRL             */
#define _RAC_PACTRL_TXPAPOWER_t12stripeon                             0x0000000CUL                                           /**< Mode t12stripeon for RAC_PACTRL             */
#define _RAC_PACTRL_TXPAPOWER_t13stripeon                             0x0000000DUL                                           /**< Mode t13stripeon for RAC_PACTRL             */
#define _RAC_PACTRL_TXPAPOWER_t14stripeon                             0x0000000EUL                                           /**< Mode t14stripeon for RAC_PACTRL             */
#define _RAC_PACTRL_TXPAPOWER_t15stripeon                             0x0000000FUL                                           /**< Mode t15stripeon for RAC_PACTRL             */
#define RAC_PACTRL_TXPAPOWER_DEFAULT                                  (_RAC_PACTRL_TXPAPOWER_DEFAULT << 4)                   /**< Shifted mode DEFAULT for RAC_PACTRL         */
#define RAC_PACTRL_TXPAPOWER_t0stripeon                               (_RAC_PACTRL_TXPAPOWER_t0stripeon << 4)                /**< Shifted mode t0stripeon for RAC_PACTRL      */
#define RAC_PACTRL_TXPAPOWER_t1stripeon                               (_RAC_PACTRL_TXPAPOWER_t1stripeon << 4)                /**< Shifted mode t1stripeon for RAC_PACTRL      */
#define RAC_PACTRL_TXPAPOWER_t2stripeon                               (_RAC_PACTRL_TXPAPOWER_t2stripeon << 4)                /**< Shifted mode t2stripeon for RAC_PACTRL      */
#define RAC_PACTRL_TXPAPOWER_t3stripeon                               (_RAC_PACTRL_TXPAPOWER_t3stripeon << 4)                /**< Shifted mode t3stripeon for RAC_PACTRL      */
#define RAC_PACTRL_TXPAPOWER_t4stripeon                               (_RAC_PACTRL_TXPAPOWER_t4stripeon << 4)                /**< Shifted mode t4stripeon for RAC_PACTRL      */
#define RAC_PACTRL_TXPAPOWER_t5stripeon                               (_RAC_PACTRL_TXPAPOWER_t5stripeon << 4)                /**< Shifted mode t5stripeon for RAC_PACTRL      */
#define RAC_PACTRL_TXPAPOWER_t6stripeon                               (_RAC_PACTRL_TXPAPOWER_t6stripeon << 4)                /**< Shifted mode t6stripeon for RAC_PACTRL      */
#define RAC_PACTRL_TXPAPOWER_t7stripeon                               (_RAC_PACTRL_TXPAPOWER_t7stripeon << 4)                /**< Shifted mode t7stripeon for RAC_PACTRL      */
#define RAC_PACTRL_TXPAPOWER_t8stripeon                               (_RAC_PACTRL_TXPAPOWER_t8stripeon << 4)                /**< Shifted mode t8stripeon for RAC_PACTRL      */
#define RAC_PACTRL_TXPAPOWER_t9stripeon                               (_RAC_PACTRL_TXPAPOWER_t9stripeon << 4)                /**< Shifted mode t9stripeon for RAC_PACTRL      */
#define RAC_PACTRL_TXPAPOWER_t10stripeon                              (_RAC_PACTRL_TXPAPOWER_t10stripeon << 4)               /**< Shifted mode t10stripeon for RAC_PACTRL     */
#define RAC_PACTRL_TXPAPOWER_t11stripeon                              (_RAC_PACTRL_TXPAPOWER_t11stripeon << 4)               /**< Shifted mode t11stripeon for RAC_PACTRL     */
#define RAC_PACTRL_TXPAPOWER_t12stripeon                              (_RAC_PACTRL_TXPAPOWER_t12stripeon << 4)               /**< Shifted mode t12stripeon for RAC_PACTRL     */
#define RAC_PACTRL_TXPAPOWER_t13stripeon                              (_RAC_PACTRL_TXPAPOWER_t13stripeon << 4)               /**< Shifted mode t13stripeon for RAC_PACTRL     */
#define RAC_PACTRL_TXPAPOWER_t14stripeon                              (_RAC_PACTRL_TXPAPOWER_t14stripeon << 4)               /**< Shifted mode t14stripeon for RAC_PACTRL     */
#define RAC_PACTRL_TXPAPOWER_t15stripeon                              (_RAC_PACTRL_TXPAPOWER_t15stripeon << 4)               /**< Shifted mode t15stripeon for RAC_PACTRL     */
#define RAC_PACTRL_TXPALATCHBYPASS10DBM                               (0x1UL << 8)                                           /**< TXPALATCHBYPASS10DBM                        */
#define _RAC_PACTRL_TXPALATCHBYPASS10DBM_SHIFT                        8                                                      /**< Shift value for RAC_TXPALATCHBYPASS10DBM    */
#define _RAC_PACTRL_TXPALATCHBYPASS10DBM_MASK                         0x100UL                                                /**< Bit mask for RAC_TXPALATCHBYPASS10DBM       */
#define _RAC_PACTRL_TXPALATCHBYPASS10DBM_DEFAULT                      0x00000000UL                                           /**< Mode DEFAULT for RAC_PACTRL                 */
#define _RAC_PACTRL_TXPALATCHBYPASS10DBM_disable                      0x00000000UL                                           /**< Mode disable for RAC_PACTRL                 */
#define _RAC_PACTRL_TXPALATCHBYPASS10DBM_enable                       0x00000001UL                                           /**< Mode enable for RAC_PACTRL                  */
#define RAC_PACTRL_TXPALATCHBYPASS10DBM_DEFAULT                       (_RAC_PACTRL_TXPALATCHBYPASS10DBM_DEFAULT << 8)        /**< Shifted mode DEFAULT for RAC_PACTRL         */
#define RAC_PACTRL_TXPALATCHBYPASS10DBM_disable                       (_RAC_PACTRL_TXPALATCHBYPASS10DBM_disable << 8)        /**< Shifted mode disable for RAC_PACTRL         */
#define RAC_PACTRL_TXPALATCHBYPASS10DBM_enable                        (_RAC_PACTRL_TXPALATCHBYPASS10DBM_enable << 8)         /**< Shifted mode enable for RAC_PACTRL          */
#define RAC_PACTRL_TXPALATCHBYPASS20DBM                               (0x1UL << 9)                                           /**< TXPALATCHBYPASS20DBM                        */
#define _RAC_PACTRL_TXPALATCHBYPASS20DBM_SHIFT                        9                                                      /**< Shift value for RAC_TXPALATCHBYPASS20DBM    */
#define _RAC_PACTRL_TXPALATCHBYPASS20DBM_MASK                         0x200UL                                                /**< Bit mask for RAC_TXPALATCHBYPASS20DBM       */
#define _RAC_PACTRL_TXPALATCHBYPASS20DBM_DEFAULT                      0x00000000UL                                           /**< Mode DEFAULT for RAC_PACTRL                 */
#define _RAC_PACTRL_TXPALATCHBYPASS20DBM_disable                      0x00000000UL                                           /**< Mode disable for RAC_PACTRL                 */
#define _RAC_PACTRL_TXPALATCHBYPASS20DBM_enable                       0x00000001UL                                           /**< Mode enable for RAC_PACTRL                  */
#define RAC_PACTRL_TXPALATCHBYPASS20DBM_DEFAULT                       (_RAC_PACTRL_TXPALATCHBYPASS20DBM_DEFAULT << 9)        /**< Shifted mode DEFAULT for RAC_PACTRL         */
#define RAC_PACTRL_TXPALATCHBYPASS20DBM_disable                       (_RAC_PACTRL_TXPALATCHBYPASS20DBM_disable << 9)        /**< Shifted mode disable for RAC_PACTRL         */
#define RAC_PACTRL_TXPALATCHBYPASS20DBM_enable                        (_RAC_PACTRL_TXPALATCHBYPASS20DBM_enable << 9)         /**< Shifted mode enable for RAC_PACTRL          */
#define RAC_PACTRL_TXPASELPREDRVREGVDDPA                              (0x1UL << 10)                                          /**< TXPASELPREDRVREGVDDPA                       */
#define _RAC_PACTRL_TXPASELPREDRVREGVDDPA_SHIFT                       10                                                     /**< Shift value for RAC_TXPASELPREDRVREGVDDPA   */
#define _RAC_PACTRL_TXPASELPREDRVREGVDDPA_MASK                        0x400UL                                                /**< Bit mask for RAC_TXPASELPREDRVREGVDDPA      */
#define _RAC_PACTRL_TXPASELPREDRVREGVDDPA_DEFAULT                     0x00000000UL                                           /**< Mode DEFAULT for RAC_PACTRL                 */
#define _RAC_PACTRL_TXPASELPREDRVREGVDDPA_not_selected                0x00000000UL                                           /**< Mode not_selected for RAC_PACTRL            */
#define _RAC_PACTRL_TXPASELPREDRVREGVDDPA_selected                    0x00000001UL                                           /**< Mode selected for RAC_PACTRL                */
#define RAC_PACTRL_TXPASELPREDRVREGVDDPA_DEFAULT                      (_RAC_PACTRL_TXPASELPREDRVREGVDDPA_DEFAULT << 10)      /**< Shifted mode DEFAULT for RAC_PACTRL         */
#define RAC_PACTRL_TXPASELPREDRVREGVDDPA_not_selected                 (_RAC_PACTRL_TXPASELPREDRVREGVDDPA_not_selected << 10) /**< Shifted mode not_selected for RAC_PACTRL    */
#define RAC_PACTRL_TXPASELPREDRVREGVDDPA_selected                     (_RAC_PACTRL_TXPASELPREDRVREGVDDPA_selected << 10)     /**< Shifted mode selected for RAC_PACTRL        */
#define RAC_PACTRL_TXPASELPREDRVREGVDDRF                              (0x1UL << 11)                                          /**< TXPASELPREDRVREGVDDRF                       */
#define _RAC_PACTRL_TXPASELPREDRVREGVDDRF_SHIFT                       11                                                     /**< Shift value for RAC_TXPASELPREDRVREGVDDRF   */
#define _RAC_PACTRL_TXPASELPREDRVREGVDDRF_MASK                        0x800UL                                                /**< Bit mask for RAC_TXPASELPREDRVREGVDDRF      */
#define _RAC_PACTRL_TXPASELPREDRVREGVDDRF_DEFAULT                     0x00000000UL                                           /**< Mode DEFAULT for RAC_PACTRL                 */
#define _RAC_PACTRL_TXPASELPREDRVREGVDDRF_not_selected                0x00000000UL                                           /**< Mode not_selected for RAC_PACTRL            */
#define _RAC_PACTRL_TXPASELPREDRVREGVDDRF_selected                    0x00000001UL                                           /**< Mode selected for RAC_PACTRL                */
#define RAC_PACTRL_TXPASELPREDRVREGVDDRF_DEFAULT                      (_RAC_PACTRL_TXPASELPREDRVREGVDDRF_DEFAULT << 11)      /**< Shifted mode DEFAULT for RAC_PACTRL         */
#define RAC_PACTRL_TXPASELPREDRVREGVDDRF_not_selected                 (_RAC_PACTRL_TXPASELPREDRVREGVDDRF_not_selected << 11) /**< Shifted mode not_selected for RAC_PACTRL    */
#define RAC_PACTRL_TXPASELPREDRVREGVDDRF_selected                     (_RAC_PACTRL_TXPASELPREDRVREGVDDRF_selected << 11)     /**< Shifted mode selected for RAC_PACTRL        */
#define _RAC_PACTRL_TXPASELSLICE_SHIFT                                12                                                     /**< Shift value for RAC_TXPASELSLICE            */
#define _RAC_PACTRL_TXPASELSLICE_MASK                                 0xF000UL                                               /**< Bit mask for RAC_TXPASELSLICE               */
#define _RAC_PACTRL_TXPASELSLICE_DEFAULT                              0x00000000UL                                           /**< Mode DEFAULT for RAC_PACTRL                 */
#define RAC_PACTRL_TXPASELSLICE_DEFAULT                               (_RAC_PACTRL_TXPASELSLICE_DEFAULT << 12)               /**< Shifted mode DEFAULT for RAC_PACTRL         */
#define RAC_PACTRL_TXPASLICERST                                       (0x1UL << 16)                                          /**< TXPASLICERST                                */
#define _RAC_PACTRL_TXPASLICERST_SHIFT                                16                                                     /**< Shift value for RAC_TXPASLICERST            */
#define _RAC_PACTRL_TXPASLICERST_MASK                                 0x10000UL                                              /**< Bit mask for RAC_TXPASLICERST               */
#define _RAC_PACTRL_TXPASLICERST_DEFAULT                              0x00000000UL                                           /**< Mode DEFAULT for RAC_PACTRL                 */
#define _RAC_PACTRL_TXPASLICERST_disable                              0x00000000UL                                           /**< Mode disable for RAC_PACTRL                 */
#define _RAC_PACTRL_TXPASLICERST_enable                               0x00000001UL                                           /**< Mode enable for RAC_PACTRL                  */
#define RAC_PACTRL_TXPASLICERST_DEFAULT                               (_RAC_PACTRL_TXPASLICERST_DEFAULT << 16)               /**< Shifted mode DEFAULT for RAC_PACTRL         */
#define RAC_PACTRL_TXPASLICERST_disable                               (_RAC_PACTRL_TXPASLICERST_disable << 16)               /**< Shifted mode disable for RAC_PACTRL         */
#define RAC_PACTRL_TXPASLICERST_enable                                (_RAC_PACTRL_TXPASLICERST_enable << 16)                /**< Shifted mode enable for RAC_PACTRL          */

/* Bit fields for RAC FENOTCH0 */
#define _RAC_FENOTCH0_RESETVALUE                                      0x00004000UL                               /**< Default value for RAC_FENOTCH0              */
#define _RAC_FENOTCH0_MASK                                            0x00007000UL                               /**< Mask for RAC_FENOTCH0                       */
#define _RAC_FENOTCH0_FENOTCHVBIAS_SHIFT                              12                                         /**< Shift value for RAC_FENOTCHVBIAS            */
#define _RAC_FENOTCH0_FENOTCHVBIAS_MASK                               0x7000UL                                   /**< Bit mask for RAC_FENOTCHVBIAS               */
#define _RAC_FENOTCH0_FENOTCHVBIAS_DEFAULT                            0x00000004UL                               /**< Mode DEFAULT for RAC_FENOTCH0               */
#define RAC_FENOTCH0_FENOTCHVBIAS_DEFAULT                             (_RAC_FENOTCH0_FENOTCHVBIAS_DEFAULT << 12) /**< Shifted mode DEFAULT for RAC_FENOTCH0       */

/* Bit fields for RAC FENOTCH1 */
#define _RAC_FENOTCH1_RESETVALUE                                      0x00000000UL                                     /**< Default value for RAC_FENOTCH1              */
#define _RAC_FENOTCH1_MASK                                            0x001FFF05UL                                     /**< Mask for RAC_FENOTCH1                       */
#define RAC_FENOTCH1_FENOTCHENVDDSW                                   (0x1UL << 0)                                     /**< FENOTCHENVDDSW                              */
#define _RAC_FENOTCH1_FENOTCHENVDDSW_SHIFT                            0                                                /**< Shift value for RAC_FENOTCHENVDDSW          */
#define _RAC_FENOTCH1_FENOTCHENVDDSW_MASK                             0x1UL                                            /**< Bit mask for RAC_FENOTCHENVDDSW             */
#define _RAC_FENOTCH1_FENOTCHENVDDSW_DEFAULT                          0x00000000UL                                     /**< Mode DEFAULT for RAC_FENOTCH1               */
#define _RAC_FENOTCH1_FENOTCHENVDDSW_disable                          0x00000000UL                                     /**< Mode disable for RAC_FENOTCH1               */
#define _RAC_FENOTCH1_FENOTCHENVDDSW_enable                           0x00000001UL                                     /**< Mode enable for RAC_FENOTCH1                */
#define RAC_FENOTCH1_FENOTCHENVDDSW_DEFAULT                           (_RAC_FENOTCH1_FENOTCHENVDDSW_DEFAULT << 0)      /**< Shifted mode DEFAULT for RAC_FENOTCH1       */
#define RAC_FENOTCH1_FENOTCHENVDDSW_disable                           (_RAC_FENOTCH1_FENOTCHENVDDSW_disable << 0)      /**< Shifted mode disable for RAC_FENOTCH1       */
#define RAC_FENOTCH1_FENOTCHENVDDSW_enable                            (_RAC_FENOTCH1_FENOTCHENVDDSW_enable << 0)       /**< Shifted mode enable for RAC_FENOTCH1        */
#define RAC_FENOTCH1_FENOTCHRCCALEN                                   (0x1UL << 2)                                     /**< FENOTCHRCCALEN                              */
#define _RAC_FENOTCH1_FENOTCHRCCALEN_SHIFT                            2                                                /**< Shift value for RAC_FENOTCHRCCALEN          */
#define _RAC_FENOTCH1_FENOTCHRCCALEN_MASK                             0x4UL                                            /**< Bit mask for RAC_FENOTCHRCCALEN             */
#define _RAC_FENOTCH1_FENOTCHRCCALEN_DEFAULT                          0x00000000UL                                     /**< Mode DEFAULT for RAC_FENOTCH1               */
#define _RAC_FENOTCH1_FENOTCHRCCALEN_disable                          0x00000000UL                                     /**< Mode disable for RAC_FENOTCH1               */
#define _RAC_FENOTCH1_FENOTCHRCCALEN_enable                           0x00000001UL                                     /**< Mode enable for RAC_FENOTCH1                */
#define RAC_FENOTCH1_FENOTCHRCCALEN_DEFAULT                           (_RAC_FENOTCH1_FENOTCHRCCALEN_DEFAULT << 2)      /**< Shifted mode DEFAULT for RAC_FENOTCH1       */
#define RAC_FENOTCH1_FENOTCHRCCALEN_disable                           (_RAC_FENOTCH1_FENOTCHRCCALEN_disable << 2)      /**< Shifted mode disable for RAC_FENOTCH1       */
#define RAC_FENOTCH1_FENOTCHRCCALEN_enable                            (_RAC_FENOTCH1_FENOTCHRCCALEN_enable << 2)       /**< Shifted mode enable for RAC_FENOTCH1        */
#define _RAC_FENOTCH1_FENOTCHRCCALCOUNTER_SHIFT                       8                                                /**< Shift value for RAC_FENOTCHRCCALCOUNTER     */
#define _RAC_FENOTCH1_FENOTCHRCCALCOUNTER_MASK                        0xFF00UL                                         /**< Bit mask for RAC_FENOTCHRCCALCOUNTER        */
#define _RAC_FENOTCH1_FENOTCHRCCALCOUNTER_DEFAULT                     0x00000000UL                                     /**< Mode DEFAULT for RAC_FENOTCH1               */
#define RAC_FENOTCH1_FENOTCHRCCALCOUNTER_DEFAULT                      (_RAC_FENOTCH1_FENOTCHRCCALCOUNTER_DEFAULT << 8) /**< Shifted mode DEFAULT for RAC_FENOTCH1       */
#define _RAC_FENOTCH1_FENOTCHRCCALOSC_SHIFT                           16                                               /**< Shift value for RAC_FENOTCHRCCALOSC         */
#define _RAC_FENOTCH1_FENOTCHRCCALOSC_MASK                            0xF0000UL                                        /**< Bit mask for RAC_FENOTCHRCCALOSC            */
#define _RAC_FENOTCH1_FENOTCHRCCALOSC_DEFAULT                         0x00000000UL                                     /**< Mode DEFAULT for RAC_FENOTCH1               */
#define RAC_FENOTCH1_FENOTCHRCCALOSC_DEFAULT                          (_RAC_FENOTCH1_FENOTCHRCCALOSC_DEFAULT << 16)    /**< Shifted mode DEFAULT for RAC_FENOTCH1       */
#define RAC_FENOTCH1_FENOTCHRCCALOUT                                  (0x1UL << 20)                                    /**< FENOTCHRCCALOUT                             */
#define _RAC_FENOTCH1_FENOTCHRCCALOUT_SHIFT                           20                                               /**< Shift value for RAC_FENOTCHRCCALOUT         */
#define _RAC_FENOTCH1_FENOTCHRCCALOUT_MASK                            0x100000UL                                       /**< Bit mask for RAC_FENOTCHRCCALOUT            */
#define _RAC_FENOTCH1_FENOTCHRCCALOUT_DEFAULT                         0x00000000UL                                     /**< Mode DEFAULT for RAC_FENOTCH1               */
#define RAC_FENOTCH1_FENOTCHRCCALOUT_DEFAULT                          (_RAC_FENOTCH1_FENOTCHRCCALOUT_DEFAULT << 20)    /**< Shifted mode DEFAULT for RAC_FENOTCH1       */

/* Bit fields for RAC SCRATCH0 */
#define _RAC_SCRATCH0_RESETVALUE                                      0x00000000UL                          /**< Default value for RAC_SCRATCH0              */
#define _RAC_SCRATCH0_MASK                                            0xFFFFFFFFUL                          /**< Mask for RAC_SCRATCH0                       */
#define _RAC_SCRATCH0_SCRATCH0_SHIFT                                  0                                     /**< Shift value for RAC_SCRATCH0                */
#define _RAC_SCRATCH0_SCRATCH0_MASK                                   0xFFFFFFFFUL                          /**< Bit mask for RAC_SCRATCH0                   */
#define _RAC_SCRATCH0_SCRATCH0_DEFAULT                                0x00000000UL                          /**< Mode DEFAULT for RAC_SCRATCH0               */
#define RAC_SCRATCH0_SCRATCH0_DEFAULT                                 (_RAC_SCRATCH0_SCRATCH0_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_SCRATCH0       */

/* Bit fields for RAC SCRATCH1 */
#define _RAC_SCRATCH1_RESETVALUE                                      0x00000000UL                          /**< Default value for RAC_SCRATCH1              */
#define _RAC_SCRATCH1_MASK                                            0xFFFFFFFFUL                          /**< Mask for RAC_SCRATCH1                       */
#define _RAC_SCRATCH1_SCRATCH1_SHIFT                                  0                                     /**< Shift value for RAC_SCRATCH1                */
#define _RAC_SCRATCH1_SCRATCH1_MASK                                   0xFFFFFFFFUL                          /**< Bit mask for RAC_SCRATCH1                   */
#define _RAC_SCRATCH1_SCRATCH1_DEFAULT                                0x00000000UL                          /**< Mode DEFAULT for RAC_SCRATCH1               */
#define RAC_SCRATCH1_SCRATCH1_DEFAULT                                 (_RAC_SCRATCH1_SCRATCH1_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_SCRATCH1       */

/* Bit fields for RAC SCRATCH2 */
#define _RAC_SCRATCH2_RESETVALUE                                      0x00000000UL                          /**< Default value for RAC_SCRATCH2              */
#define _RAC_SCRATCH2_MASK                                            0xFFFFFFFFUL                          /**< Mask for RAC_SCRATCH2                       */
#define _RAC_SCRATCH2_SCRATCH2_SHIFT                                  0                                     /**< Shift value for RAC_SCRATCH2                */
#define _RAC_SCRATCH2_SCRATCH2_MASK                                   0xFFFFFFFFUL                          /**< Bit mask for RAC_SCRATCH2                   */
#define _RAC_SCRATCH2_SCRATCH2_DEFAULT                                0x00000000UL                          /**< Mode DEFAULT for RAC_SCRATCH2               */
#define RAC_SCRATCH2_SCRATCH2_DEFAULT                                 (_RAC_SCRATCH2_SCRATCH2_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_SCRATCH2       */

/* Bit fields for RAC SCRATCH3 */
#define _RAC_SCRATCH3_RESETVALUE                                      0x00000000UL                          /**< Default value for RAC_SCRATCH3              */
#define _RAC_SCRATCH3_MASK                                            0xFFFFFFFFUL                          /**< Mask for RAC_SCRATCH3                       */
#define _RAC_SCRATCH3_SCRATCH3_SHIFT                                  0                                     /**< Shift value for RAC_SCRATCH3                */
#define _RAC_SCRATCH3_SCRATCH3_MASK                                   0xFFFFFFFFUL                          /**< Bit mask for RAC_SCRATCH3                   */
#define _RAC_SCRATCH3_SCRATCH3_DEFAULT                                0x00000000UL                          /**< Mode DEFAULT for RAC_SCRATCH3               */
#define RAC_SCRATCH3_SCRATCH3_DEFAULT                                 (_RAC_SCRATCH3_SCRATCH3_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_SCRATCH3       */

/* Bit fields for RAC SCRATCH4 */
#define _RAC_SCRATCH4_RESETVALUE                                      0x00000000UL                          /**< Default value for RAC_SCRATCH4              */
#define _RAC_SCRATCH4_MASK                                            0xFFFFFFFFUL                          /**< Mask for RAC_SCRATCH4                       */
#define _RAC_SCRATCH4_SCRATCH4_SHIFT                                  0                                     /**< Shift value for RAC_SCRATCH4                */
#define _RAC_SCRATCH4_SCRATCH4_MASK                                   0xFFFFFFFFUL                          /**< Bit mask for RAC_SCRATCH4                   */
#define _RAC_SCRATCH4_SCRATCH4_DEFAULT                                0x00000000UL                          /**< Mode DEFAULT for RAC_SCRATCH4               */
#define RAC_SCRATCH4_SCRATCH4_DEFAULT                                 (_RAC_SCRATCH4_SCRATCH4_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_SCRATCH4       */

/* Bit fields for RAC SCRATCH5 */
#define _RAC_SCRATCH5_RESETVALUE                                      0x00000000UL                          /**< Default value for RAC_SCRATCH5              */
#define _RAC_SCRATCH5_MASK                                            0xFFFFFFFFUL                          /**< Mask for RAC_SCRATCH5                       */
#define _RAC_SCRATCH5_SCRATCH5_SHIFT                                  0                                     /**< Shift value for RAC_SCRATCH5                */
#define _RAC_SCRATCH5_SCRATCH5_MASK                                   0xFFFFFFFFUL                          /**< Bit mask for RAC_SCRATCH5                   */
#define _RAC_SCRATCH5_SCRATCH5_DEFAULT                                0x00000000UL                          /**< Mode DEFAULT for RAC_SCRATCH5               */
#define RAC_SCRATCH5_SCRATCH5_DEFAULT                                 (_RAC_SCRATCH5_SCRATCH5_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_SCRATCH5       */

/* Bit fields for RAC SCRATCH6 */
#define _RAC_SCRATCH6_RESETVALUE                                      0x00000000UL                          /**< Default value for RAC_SCRATCH6              */
#define _RAC_SCRATCH6_MASK                                            0xFFFFFFFFUL                          /**< Mask for RAC_SCRATCH6                       */
#define _RAC_SCRATCH6_SCRATCH6_SHIFT                                  0                                     /**< Shift value for RAC_SCRATCH6                */
#define _RAC_SCRATCH6_SCRATCH6_MASK                                   0xFFFFFFFFUL                          /**< Bit mask for RAC_SCRATCH6                   */
#define _RAC_SCRATCH6_SCRATCH6_DEFAULT                                0x00000000UL                          /**< Mode DEFAULT for RAC_SCRATCH6               */
#define RAC_SCRATCH6_SCRATCH6_DEFAULT                                 (_RAC_SCRATCH6_SCRATCH6_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_SCRATCH6       */

/* Bit fields for RAC SCRATCH7 */
#define _RAC_SCRATCH7_RESETVALUE                                      0x00000000UL                          /**< Default value for RAC_SCRATCH7              */
#define _RAC_SCRATCH7_MASK                                            0xFFFFFFFFUL                          /**< Mask for RAC_SCRATCH7                       */
#define _RAC_SCRATCH7_SCRATCH7_SHIFT                                  0                                     /**< Shift value for RAC_SCRATCH7                */
#define _RAC_SCRATCH7_SCRATCH7_MASK                                   0xFFFFFFFFUL                          /**< Bit mask for RAC_SCRATCH7                   */
#define _RAC_SCRATCH7_SCRATCH7_DEFAULT                                0x00000000UL                          /**< Mode DEFAULT for RAC_SCRATCH7               */
#define RAC_SCRATCH7_SCRATCH7_DEFAULT                                 (_RAC_SCRATCH7_SCRATCH7_DEFAULT << 0) /**< Shifted mode DEFAULT for RAC_SCRATCH7       */

/* Bit fields for RAC THMSW */
#define _RAC_THMSW_RESETVALUE                                         0x00000000UL                          /**< Default value for RAC_THMSW                 */
#define _RAC_THMSW_MASK                                               0x00000003UL                          /**< Mask for RAC_THMSW                          */
#define RAC_THMSW_EN                                                  (0x1UL << 0)                          /**< Enable Switch                               */
#define _RAC_THMSW_EN_SHIFT                                           0                                     /**< Shift value for RAC_EN                      */
#define _RAC_THMSW_EN_MASK                                            0x1UL                                 /**< Bit mask for RAC_EN                         */
#define _RAC_THMSW_EN_DEFAULT                                         0x00000000UL                          /**< Mode DEFAULT for RAC_THMSW                  */
#define _RAC_THMSW_EN_Disabled                                        0x00000000UL                          /**< Mode Disabled for RAC_THMSW                 */
#define _RAC_THMSW_EN_Enabled                                         0x00000001UL                          /**< Mode Enabled for RAC_THMSW                  */
#define RAC_THMSW_EN_DEFAULT                                          (_RAC_THMSW_EN_DEFAULT << 0)          /**< Shifted mode DEFAULT for RAC_THMSW          */
#define RAC_THMSW_EN_Disabled                                         (_RAC_THMSW_EN_Disabled << 0)         /**< Shifted mode Disabled for RAC_THMSW         */
#define RAC_THMSW_EN_Enabled                                          (_RAC_THMSW_EN_Enabled << 0)          /**< Shifted mode Enabled for RAC_THMSW          */
#define RAC_THMSW_HALFSWITCH                                          (0x1UL << 1)                          /**< Halfswitch Mode enable                      */
#define _RAC_THMSW_HALFSWITCH_SHIFT                                   1                                     /**< Shift value for RAC_HALFSWITCH              */
#define _RAC_THMSW_HALFSWITCH_MASK                                    0x2UL                                 /**< Bit mask for RAC_HALFSWITCH                 */
#define _RAC_THMSW_HALFSWITCH_DEFAULT                                 0x00000000UL                          /**< Mode DEFAULT for RAC_THMSW                  */
#define _RAC_THMSW_HALFSWITCH_Disabled                                0x00000000UL                          /**< Mode Disabled for RAC_THMSW                 */
#define _RAC_THMSW_HALFSWITCH_Enabled                                 0x00000001UL                          /**< Mode Enabled for RAC_THMSW                  */
#define RAC_THMSW_HALFSWITCH_DEFAULT                                  (_RAC_THMSW_HALFSWITCH_DEFAULT << 1)  /**< Shifted mode DEFAULT for RAC_THMSW          */
#define RAC_THMSW_HALFSWITCH_Disabled                                 (_RAC_THMSW_HALFSWITCH_Disabled << 1) /**< Shifted mode Disabled for RAC_THMSW         */
#define RAC_THMSW_HALFSWITCH_Enabled                                  (_RAC_THMSW_HALFSWITCH_Enabled << 1)  /**< Shifted mode Enabled for RAC_THMSW          */

/** @} End of group EFR32MG24_RAC_BitFields */
/** @} End of group EFR32MG24_RAC */
/** @} End of group Parts */

#endif /* EFR32MG24_RAC_H */
