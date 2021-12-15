/**************************************************************************//**
 * @file
 * @brief EFR32FG23 ECAIFADC register and bit field definitions
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
#ifndef EFR32FG23_ECAIFADC_H
#define EFR32FG23_ECAIFADC_H
#define ECAIFADC_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG23_ECAIFADC ECAIFADC
 * @{
 * @brief EFR32FG23 ECAIFADC Register Declaration.
 *****************************************************************************/

/** ECAIFADC Register Declaration. */
typedef struct {
  __IM uint32_t  IPVERSION;                     /**< New Register                                       */
  __IOM uint32_t EN;                            /**< Enable Register                                    */
  __IOM uint32_t CTRL;                          /**< Control Register                                   */
  uint32_t       RESERVED0[1U];                 /**< Reserved for future use                            */
  __IM uint32_t  STATUS;                        /**< Status Register                                    */
  uint32_t       RESERVED1[1019U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< New Register                                       */
  __IOM uint32_t EN_SET;                        /**< Enable Register                                    */
  __IOM uint32_t CTRL_SET;                      /**< Control Register                                   */
  uint32_t       RESERVED2[1U];                 /**< Reserved for future use                            */
  __IM uint32_t  STATUS_SET;                    /**< Status Register                                    */
  uint32_t       RESERVED3[1019U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< New Register                                       */
  __IOM uint32_t EN_CLR;                        /**< Enable Register                                    */
  __IOM uint32_t CTRL_CLR;                      /**< Control Register                                   */
  uint32_t       RESERVED4[1U];                 /**< Reserved for future use                            */
  __IM uint32_t  STATUS_CLR;                    /**< Status Register                                    */
  uint32_t       RESERVED5[1019U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< New Register                                       */
  __IOM uint32_t EN_TGL;                        /**< Enable Register                                    */
  __IOM uint32_t CTRL_TGL;                      /**< Control Register                                   */
  uint32_t       RESERVED6[1U];                 /**< Reserved for future use                            */
  __IM uint32_t  STATUS_TGL;                    /**< Status Register                                    */
} ECAIFADC_TypeDef;
/** @} End of group EFR32FG23_ECAIFADC */

/**************************************************************************//**
 * @addtogroup EFR32FG23_ECAIFADC
 * @{
 * @defgroup EFR32FG23_ECAIFADC_BitFields ECAIFADC Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for ECAIFADC IPVERSION */
#define _ECAIFADC_IPVERSION_RESETVALUE           0x00000001UL                                 /**< Default value for ECAIFADC_IPVERSION        */
#define _ECAIFADC_IPVERSION_MASK                 0xFFFFFFFFUL                                 /**< Mask for ECAIFADC_IPVERSION                 */
#define _ECAIFADC_IPVERSION_IPVERSION_SHIFT      0                                            /**< Shift value for ECAIFADC_IPVERSION          */
#define _ECAIFADC_IPVERSION_IPVERSION_MASK       0xFFFFFFFFUL                                 /**< Bit mask for ECAIFADC_IPVERSION             */
#define _ECAIFADC_IPVERSION_IPVERSION_DEFAULT    0x00000001UL                                 /**< Mode DEFAULT for ECAIFADC_IPVERSION         */
#define ECAIFADC_IPVERSION_IPVERSION_DEFAULT     (_ECAIFADC_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for ECAIFADC_IPVERSION */

/* Bit fields for ECAIFADC EN */
#define _ECAIFADC_EN_RESETVALUE                  0x00000000UL                           /**< Default value for ECAIFADC_EN               */
#define _ECAIFADC_EN_MASK                        0x00000001UL                           /**< Mask for ECAIFADC_EN                        */
#define ECAIFADC_EN_EN                           (0x1UL << 0)                           /**< IFADC Debug Enable                          */
#define _ECAIFADC_EN_EN_SHIFT                    0                                      /**< Shift value for ECAIFADC_EN                 */
#define _ECAIFADC_EN_EN_MASK                     0x1UL                                  /**< Bit mask for ECAIFADC_EN                    */
#define _ECAIFADC_EN_EN_DEFAULT                  0x00000000UL                           /**< Mode DEFAULT for ECAIFADC_EN                */
#define ECAIFADC_EN_EN_DEFAULT                   (_ECAIFADC_EN_EN_DEFAULT << 0)         /**< Shifted mode DEFAULT for ECAIFADC_EN        */

/* Bit fields for ECAIFADC CTRL */
#define _ECAIFADC_CTRL_RESETVALUE                0x00000000UL                           /**< Default value for ECAIFADC_CTRL             */
#define _ECAIFADC_CTRL_MASK                      0x00000007UL                           /**< Mask for ECAIFADC_CTRL                      */
#define ECAIFADC_CTRL_MODE                       (0x1UL << 0)                           /**< Mode                                        */
#define _ECAIFADC_CTRL_MODE_SHIFT                0                                      /**< Shift value for ECAIFADC_MODE               */
#define _ECAIFADC_CTRL_MODE_MASK                 0x1UL                                  /**< Bit mask for ECAIFADC_MODE                  */
#define _ECAIFADC_CTRL_MODE_DEFAULT              0x00000000UL                           /**< Mode DEFAULT for ECAIFADC_CTRL              */
#define _ECAIFADC_CTRL_MODE_MP                   0x00000000UL                           /**< Mode MP for ECAIFADC_CTRL                   */
#define _ECAIFADC_CTRL_MODE_IQ                   0x00000001UL                           /**< Mode IQ for ECAIFADC_CTRL                   */
#define ECAIFADC_CTRL_MODE_DEFAULT               (_ECAIFADC_CTRL_MODE_DEFAULT << 0)     /**< Shifted mode DEFAULT for ECAIFADC_CTRL      */
#define ECAIFADC_CTRL_MODE_MP                    (_ECAIFADC_CTRL_MODE_MP << 0)          /**< Shifted mode MP for ECAIFADC_CTRL           */
#define ECAIFADC_CTRL_MODE_IQ                    (_ECAIFADC_CTRL_MODE_IQ << 0)          /**< Shifted mode IQ for ECAIFADC_CTRL           */
#define _ECAIFADC_CTRL_IQSEL_SHIFT               1                                      /**< Shift value for ECAIFADC_IQSEL              */
#define _ECAIFADC_CTRL_IQSEL_MASK                0x6UL                                  /**< Bit mask for ECAIFADC_IQSEL                 */
#define _ECAIFADC_CTRL_IQSEL_DEFAULT             0x00000000UL                           /**< Mode DEFAULT for ECAIFADC_CTRL              */
#define _ECAIFADC_CTRL_IQSEL_NA                  0x00000000UL                           /**< Mode NA for ECAIFADC_CTRL                   */
#define _ECAIFADC_CTRL_IQSEL_IONLY               0x00000001UL                           /**< Mode IONLY for ECAIFADC_CTRL                */
#define _ECAIFADC_CTRL_IQSEL_QONLY               0x00000002UL                           /**< Mode QONLY for ECAIFADC_CTRL                */
#define _ECAIFADC_CTRL_IQSEL_IANDQ               0x00000003UL                           /**< Mode IANDQ for ECAIFADC_CTRL                */
#define ECAIFADC_CTRL_IQSEL_DEFAULT              (_ECAIFADC_CTRL_IQSEL_DEFAULT << 1)    /**< Shifted mode DEFAULT for ECAIFADC_CTRL      */
#define ECAIFADC_CTRL_IQSEL_NA                   (_ECAIFADC_CTRL_IQSEL_NA << 1)         /**< Shifted mode NA for ECAIFADC_CTRL           */
#define ECAIFADC_CTRL_IQSEL_IONLY                (_ECAIFADC_CTRL_IQSEL_IONLY << 1)      /**< Shifted mode IONLY for ECAIFADC_CTRL        */
#define ECAIFADC_CTRL_IQSEL_QONLY                (_ECAIFADC_CTRL_IQSEL_QONLY << 1)      /**< Shifted mode QONLY for ECAIFADC_CTRL        */
#define ECAIFADC_CTRL_IQSEL_IANDQ                (_ECAIFADC_CTRL_IQSEL_IANDQ << 1)      /**< Shifted mode IANDQ for ECAIFADC_CTRL        */

/* Bit fields for ECAIFADC STATUS */
#define _ECAIFADC_STATUS_RESETVALUE              0x00000000UL                             /**< Default value for ECAIFADC_STATUS           */
#define _ECAIFADC_STATUS_MASK                    0x00000001UL                             /**< Mask for ECAIFADC_STATUS                    */
#define ECAIFADC_STATUS_OVERFLOW                 (0x1UL << 0)                             /**< Capture Overflow                            */
#define _ECAIFADC_STATUS_OVERFLOW_SHIFT          0                                        /**< Shift value for ECAIFADC_OVERFLOW           */
#define _ECAIFADC_STATUS_OVERFLOW_MASK           0x1UL                                    /**< Bit mask for ECAIFADC_OVERFLOW              */
#define _ECAIFADC_STATUS_OVERFLOW_DEFAULT        0x00000000UL                             /**< Mode DEFAULT for ECAIFADC_STATUS            */
#define ECAIFADC_STATUS_OVERFLOW_DEFAULT         (_ECAIFADC_STATUS_OVERFLOW_DEFAULT << 0) /**< Shifted mode DEFAULT for ECAIFADC_STATUS    */

/** @} End of group EFR32FG23_ECAIFADC_BitFields */
/** @} End of group EFR32FG23_ECAIFADC */
/** @} End of group Parts */

#endif /* EFR32FG23_ECAIFADC_H */
