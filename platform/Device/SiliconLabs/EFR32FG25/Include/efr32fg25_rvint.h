/**************************************************************************//**
 * @file
 * @brief EFR32FG25 RVINT register and bit field definitions
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
#ifndef EFR32FG25_RVINT_H
#define EFR32FG25_RVINT_H
#define RVINT_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_RVINT RVINT
 * @{
 * @brief EFR32FG25 RVINT Register Declaration.
 *****************************************************************************/

/** RVINT Register Declaration. */
typedef struct {
  __IOM uint32_t CNTL;                          /**< CNTL_REG                                           */
  __IOM uint32_t CLEAR;                         /**< CLEAR_REG                                          */
  __IOM uint32_t ENABLE0;                       /**< ENABLE0_REG                                        */
  __IOM uint32_t ENABLE1;                       /**< ENABLE1_REG                                        */
  __IOM uint32_t ENABLE2;                       /**< ENABLE2_REG                                        */
  __IOM uint32_t POLARITY;                      /**< POLARITY_REG                                       */
  __IOM uint32_t ITYPE;                         /**< ITYPE_REG                                          */
  __IM uint32_t  STATUS0;                       /**< STATUS0_REG                                        */
  __IM uint32_t  STATUS1;                       /**< STATUS1_REG                                        */
  __IM uint32_t  STATUS2;                       /**< STATUS2_REG                                        */
  __IM uint32_t  STATUS;                        /**< STATUS_REG                                         */
  __IM uint32_t  ILEVEL;                        /**< ILEVEL_REG                                         */
  uint32_t       RESERVED0[1012U];              /**< Reserved for future use                            */
  __IOM uint32_t CNTL_SET;                      /**< CNTL_REG                                           */
  __IOM uint32_t CLEAR_SET;                     /**< CLEAR_REG                                          */
  __IOM uint32_t ENABLE0_SET;                   /**< ENABLE0_REG                                        */
  __IOM uint32_t ENABLE1_SET;                   /**< ENABLE1_REG                                        */
  __IOM uint32_t ENABLE2_SET;                   /**< ENABLE2_REG                                        */
  __IOM uint32_t POLARITY_SET;                  /**< POLARITY_REG                                       */
  __IOM uint32_t ITYPE_SET;                     /**< ITYPE_REG                                          */
  __IM uint32_t  STATUS0_SET;                   /**< STATUS0_REG                                        */
  __IM uint32_t  STATUS1_SET;                   /**< STATUS1_REG                                        */
  __IM uint32_t  STATUS2_SET;                   /**< STATUS2_REG                                        */
  __IM uint32_t  STATUS_SET;                    /**< STATUS_REG                                         */
  __IM uint32_t  ILEVEL_SET;                    /**< ILEVEL_REG                                         */
  uint32_t       RESERVED1[1012U];              /**< Reserved for future use                            */
  __IOM uint32_t CNTL_CLR;                      /**< CNTL_REG                                           */
  __IOM uint32_t CLEAR_CLR;                     /**< CLEAR_REG                                          */
  __IOM uint32_t ENABLE0_CLR;                   /**< ENABLE0_REG                                        */
  __IOM uint32_t ENABLE1_CLR;                   /**< ENABLE1_REG                                        */
  __IOM uint32_t ENABLE2_CLR;                   /**< ENABLE2_REG                                        */
  __IOM uint32_t POLARITY_CLR;                  /**< POLARITY_REG                                       */
  __IOM uint32_t ITYPE_CLR;                     /**< ITYPE_REG                                          */
  __IM uint32_t  STATUS0_CLR;                   /**< STATUS0_REG                                        */
  __IM uint32_t  STATUS1_CLR;                   /**< STATUS1_REG                                        */
  __IM uint32_t  STATUS2_CLR;                   /**< STATUS2_REG                                        */
  __IM uint32_t  STATUS_CLR;                    /**< STATUS_REG                                         */
  __IM uint32_t  ILEVEL_CLR;                    /**< ILEVEL_REG                                         */
  uint32_t       RESERVED2[1012U];              /**< Reserved for future use                            */
  __IOM uint32_t CNTL_TGL;                      /**< CNTL_REG                                           */
  __IOM uint32_t CLEAR_TGL;                     /**< CLEAR_REG                                          */
  __IOM uint32_t ENABLE0_TGL;                   /**< ENABLE0_REG                                        */
  __IOM uint32_t ENABLE1_TGL;                   /**< ENABLE1_REG                                        */
  __IOM uint32_t ENABLE2_TGL;                   /**< ENABLE2_REG                                        */
  __IOM uint32_t POLARITY_TGL;                  /**< POLARITY_REG                                       */
  __IOM uint32_t ITYPE_TGL;                     /**< ITYPE_REG                                          */
  __IM uint32_t  STATUS0_TGL;                   /**< STATUS0_REG                                        */
  __IM uint32_t  STATUS1_TGL;                   /**< STATUS1_REG                                        */
  __IM uint32_t  STATUS2_TGL;                   /**< STATUS2_REG                                        */
  __IM uint32_t  STATUS_TGL;                    /**< STATUS_REG                                         */
  __IM uint32_t  ILEVEL_TGL;                    /**< ILEVEL_REG                                         */
} RVINT_TypeDef;
/** @} End of group EFR32FG25_RVINT */

/**************************************************************************//**
 * @addtogroup EFR32FG25_RVINT
 * @{
 * @defgroup EFR32FG25_RVINT_BitFields RVINT Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for RVINT CNTL */
#define _RVINT_CNTL_RESETVALUE              0x00000001UL                                /**< Default value for RVINT_CNTL                */
#define _RVINT_CNTL_MASK                    0x00000001UL                                /**< Mask for RVINT_CNTL                         */
#define RVINT_CNTL_CNTL                     (0x1UL << 0)                                /**< CNTL                                        */
#define _RVINT_CNTL_CNTL_SHIFT              0                                           /**< Shift value for RVINT_CNTL                  */
#define _RVINT_CNTL_CNTL_MASK               0x1UL                                       /**< Bit mask for RVINT_CNTL                     */
#define _RVINT_CNTL_CNTL_DEFAULT            0x00000001UL                                /**< Mode DEFAULT for RVINT_CNTL                 */
#define RVINT_CNTL_CNTL_DEFAULT             (_RVINT_CNTL_CNTL_DEFAULT << 0)             /**< Shifted mode DEFAULT for RVINT_CNTL         */

/* Bit fields for RVINT CLEAR */
#define _RVINT_CLEAR_RESETVALUE             0x00000000UL                                /**< Default value for RVINT_CLEAR               */
#define _RVINT_CLEAR_MASK                   0xFFFFFFFFUL                                /**< Mask for RVINT_CLEAR                        */
#define _RVINT_CLEAR_CLEAR_SHIFT            0                                           /**< Shift value for RVINT_CLEAR                 */
#define _RVINT_CLEAR_CLEAR_MASK             0xFFFFFFFFUL                                /**< Bit mask for RVINT_CLEAR                    */
#define _RVINT_CLEAR_CLEAR_DEFAULT          0x00000000UL                                /**< Mode DEFAULT for RVINT_CLEAR                */
#define RVINT_CLEAR_CLEAR_DEFAULT           (_RVINT_CLEAR_CLEAR_DEFAULT << 0)           /**< Shifted mode DEFAULT for RVINT_CLEAR        */

/* Bit fields for RVINT ENABLE0 */
#define _RVINT_ENABLE0_RESETVALUE           0x10000000UL                                /**< Default value for RVINT_ENABLE0             */
#define _RVINT_ENABLE0_MASK                 0xFFFFFFFFUL                                /**< Mask for RVINT_ENABLE0                      */
#define _RVINT_ENABLE0_ENABLE0_SHIFT        0                                           /**< Shift value for RVINT_ENABLE0               */
#define _RVINT_ENABLE0_ENABLE0_MASK         0xFFFFFFFFUL                                /**< Bit mask for RVINT_ENABLE0                  */
#define _RVINT_ENABLE0_ENABLE0_DEFAULT      0x10000000UL                                /**< Mode DEFAULT for RVINT_ENABLE0              */
#define RVINT_ENABLE0_ENABLE0_DEFAULT       (_RVINT_ENABLE0_ENABLE0_DEFAULT << 0)       /**< Shifted mode DEFAULT for RVINT_ENABLE0      */

/* Bit fields for RVINT ENABLE1 */
#define _RVINT_ENABLE1_RESETVALUE           0x00000000UL                                /**< Default value for RVINT_ENABLE1             */
#define _RVINT_ENABLE1_MASK                 0xFFFFFFFFUL                                /**< Mask for RVINT_ENABLE1                      */
#define _RVINT_ENABLE1_ENABLE1_SHIFT        0                                           /**< Shift value for RVINT_ENABLE1               */
#define _RVINT_ENABLE1_ENABLE1_MASK         0xFFFFFFFFUL                                /**< Bit mask for RVINT_ENABLE1                  */
#define _RVINT_ENABLE1_ENABLE1_DEFAULT      0x00000000UL                                /**< Mode DEFAULT for RVINT_ENABLE1              */
#define RVINT_ENABLE1_ENABLE1_DEFAULT       (_RVINT_ENABLE1_ENABLE1_DEFAULT << 0)       /**< Shifted mode DEFAULT for RVINT_ENABLE1      */

/* Bit fields for RVINT ENABLE2 */
#define _RVINT_ENABLE2_RESETVALUE           0x00000000UL                                /**< Default value for RVINT_ENABLE2             */
#define _RVINT_ENABLE2_MASK                 0xFFFFFFFFUL                                /**< Mask for RVINT_ENABLE2                      */
#define _RVINT_ENABLE2_ENABLE2_SHIFT        0                                           /**< Shift value for RVINT_ENABLE2               */
#define _RVINT_ENABLE2_ENABLE2_MASK         0xFFFFFFFFUL                                /**< Bit mask for RVINT_ENABLE2                  */
#define _RVINT_ENABLE2_ENABLE2_DEFAULT      0x00000000UL                                /**< Mode DEFAULT for RVINT_ENABLE2              */
#define RVINT_ENABLE2_ENABLE2_DEFAULT       (_RVINT_ENABLE2_ENABLE2_DEFAULT << 0)       /**< Shifted mode DEFAULT for RVINT_ENABLE2      */

/* Bit fields for RVINT POLARITY */
#define _RVINT_POLARITY_RESETVALUE          0xFFFFFFFFUL                                /**< Default value for RVINT_POLARITY            */
#define _RVINT_POLARITY_MASK                0xFFFFFFFFUL                                /**< Mask for RVINT_POLARITY                     */
#define _RVINT_POLARITY_POLARITY_SHIFT      0                                           /**< Shift value for RVINT_POLARITY              */
#define _RVINT_POLARITY_POLARITY_MASK       0xFFFFFFFFUL                                /**< Bit mask for RVINT_POLARITY                 */
#define _RVINT_POLARITY_POLARITY_DEFAULT    0xFFFFFFFFUL                                /**< Mode DEFAULT for RVINT_POLARITY             */
#define RVINT_POLARITY_POLARITY_DEFAULT     (_RVINT_POLARITY_POLARITY_DEFAULT << 0)     /**< Shifted mode DEFAULT for RVINT_POLARITY     */

/* Bit fields for RVINT ITYPE */
#define _RVINT_ITYPE_RESETVALUE             0x1600A037UL                                /**< Default value for RVINT_ITYPE               */
#define _RVINT_ITYPE_MASK                   0xFFFFFFFFUL                                /**< Mask for RVINT_ITYPE                        */
#define _RVINT_ITYPE_ITYPE_SHIFT            0                                           /**< Shift value for RVINT_ITYPE                 */
#define _RVINT_ITYPE_ITYPE_MASK             0xFFFFFFFFUL                                /**< Bit mask for RVINT_ITYPE                    */
#define _RVINT_ITYPE_ITYPE_DEFAULT          0x1600A037UL                                /**< Mode DEFAULT for RVINT_ITYPE                */
#define RVINT_ITYPE_ITYPE_DEFAULT           (_RVINT_ITYPE_ITYPE_DEFAULT << 0)           /**< Shifted mode DEFAULT for RVINT_ITYPE        */

/* Bit fields for RVINT STATUS0 */
#define _RVINT_STATUS0_RESETVALUE           0x00000000UL                                /**< Default value for RVINT_STATUS0             */
#define _RVINT_STATUS0_MASK                 0xFFFFFFFFUL                                /**< Mask for RVINT_STATUS0                      */
#define _RVINT_STATUS0_STATUS0_SHIFT        0                                           /**< Shift value for RVINT_STATUS0               */
#define _RVINT_STATUS0_STATUS0_MASK         0xFFFFFFFFUL                                /**< Bit mask for RVINT_STATUS0                  */
#define _RVINT_STATUS0_STATUS0_DEFAULT      0x00000000UL                                /**< Mode DEFAULT for RVINT_STATUS0              */
#define RVINT_STATUS0_STATUS0_DEFAULT       (_RVINT_STATUS0_STATUS0_DEFAULT << 0)       /**< Shifted mode DEFAULT for RVINT_STATUS0      */

/* Bit fields for RVINT STATUS1 */
#define _RVINT_STATUS1_RESETVALUE           0x00000000UL                                /**< Default value for RVINT_STATUS1             */
#define _RVINT_STATUS1_MASK                 0xFFFFFFFFUL                                /**< Mask for RVINT_STATUS1                      */
#define _RVINT_STATUS1_STATUS1_SHIFT        0                                           /**< Shift value for RVINT_STATUS1               */
#define _RVINT_STATUS1_STATUS1_MASK         0xFFFFFFFFUL                                /**< Bit mask for RVINT_STATUS1                  */
#define _RVINT_STATUS1_STATUS1_DEFAULT      0x00000000UL                                /**< Mode DEFAULT for RVINT_STATUS1              */
#define RVINT_STATUS1_STATUS1_DEFAULT       (_RVINT_STATUS1_STATUS1_DEFAULT << 0)       /**< Shifted mode DEFAULT for RVINT_STATUS1      */

/* Bit fields for RVINT STATUS2 */
#define _RVINT_STATUS2_RESETVALUE           0x00000000UL                                /**< Default value for RVINT_STATUS2             */
#define _RVINT_STATUS2_MASK                 0xFFFFFFFFUL                                /**< Mask for RVINT_STATUS2                      */
#define _RVINT_STATUS2_STATUS2_SHIFT        0                                           /**< Shift value for RVINT_STATUS2               */
#define _RVINT_STATUS2_STATUS2_MASK         0xFFFFFFFFUL                                /**< Bit mask for RVINT_STATUS2                  */
#define _RVINT_STATUS2_STATUS2_DEFAULT      0x00000000UL                                /**< Mode DEFAULT for RVINT_STATUS2              */
#define RVINT_STATUS2_STATUS2_DEFAULT       (_RVINT_STATUS2_STATUS2_DEFAULT << 0)       /**< Shifted mode DEFAULT for RVINT_STATUS2      */

/* Bit fields for RVINT STATUS */
#define _RVINT_STATUS_RESETVALUE            0x00000000UL                                /**< Default value for RVINT_STATUS              */
#define _RVINT_STATUS_MASK                  0xFFFFFFFFUL                                /**< Mask for RVINT_STATUS                       */
#define _RVINT_STATUS_STATUS_SHIFT          0                                           /**< Shift value for RVINT_STATUS                */
#define _RVINT_STATUS_STATUS_MASK           0xFFFFFFFFUL                                /**< Bit mask for RVINT_STATUS                   */
#define _RVINT_STATUS_STATUS_DEFAULT        0x00000000UL                                /**< Mode DEFAULT for RVINT_STATUS               */
#define RVINT_STATUS_STATUS_DEFAULT         (_RVINT_STATUS_STATUS_DEFAULT << 0)         /**< Shifted mode DEFAULT for RVINT_STATUS       */

/* Bit fields for RVINT ILEVEL */
#define _RVINT_ILEVEL_RESETVALUE            0x00000000UL                                /**< Default value for RVINT_ILEVEL              */
#define _RVINT_ILEVEL_MASK                  0xFFFFFFFFUL                                /**< Mask for RVINT_ILEVEL                       */
#define _RVINT_ILEVEL_ILEVEL_SHIFT          0                                           /**< Shift value for RVINT_ILEVEL                */
#define _RVINT_ILEVEL_ILEVEL_MASK           0xFFFFFFFFUL                                /**< Bit mask for RVINT_ILEVEL                   */
#define _RVINT_ILEVEL_ILEVEL_DEFAULT        0x00000000UL                                /**< Mode DEFAULT for RVINT_ILEVEL               */
#define RVINT_ILEVEL_ILEVEL_DEFAULT         (_RVINT_ILEVEL_ILEVEL_DEFAULT << 0)         /**< Shifted mode DEFAULT for RVINT_ILEVEL       */

/** @} End of group EFR32FG25_RVINT_BitFields */
/** @} End of group EFR32FG25_RVINT */
/** @} End of group Parts */

#endif /* EFR32FG25_RVINT_H */
