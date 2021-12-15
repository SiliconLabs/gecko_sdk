/**************************************************************************//**
 * @file
 * @brief EFR32FG25 TESTCTRL register and bit field definitions
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
#ifndef EFR32FG25_TESTCTRL_H
#define EFR32FG25_TESTCTRL_H
#define TESTCTRL_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_TESTCTRL TESTCTRL
 * @{
 * @brief EFR32FG25 TESTCTRL Register Declaration.
 *****************************************************************************/

/** TESTCTRL Register Declaration. */
typedef struct {
  __IM uint32_t IPVERSION;                      /**<                                                    */
  uint32_t      RESERVED0[3U];                  /**< Reserved for future use                            */
  uint32_t      RESERVED1[1U];                  /**< Reserved for future use                            */
  uint32_t      RESERVED2[59U];                 /**< Reserved for future use                            */
  uint32_t      RESERVED3[1U];                  /**< Reserved for future use                            */
  uint32_t      RESERVED4[63U];                 /**< Reserved for future use                            */
  uint32_t      RESERVED5[1U];                  /**< Reserved for future use                            */
  uint32_t      RESERVED6[63U];                 /**< Reserved for future use                            */
  uint32_t      RESERVED7[1U];                  /**< Reserved for future use                            */
  uint32_t      RESERVED8[831U];                /**< Reserved for future use                            */
  __IM uint32_t IPVERSION_SET;                  /**<                                                    */
  uint32_t      RESERVED9[3U];                  /**< Reserved for future use                            */
  uint32_t      RESERVED10[1U];                 /**< Reserved for future use                            */
  uint32_t      RESERVED11[59U];                /**< Reserved for future use                            */
  uint32_t      RESERVED12[1U];                 /**< Reserved for future use                            */
  uint32_t      RESERVED13[63U];                /**< Reserved for future use                            */
  uint32_t      RESERVED14[1U];                 /**< Reserved for future use                            */
  uint32_t      RESERVED15[63U];                /**< Reserved for future use                            */
  uint32_t      RESERVED16[1U];                 /**< Reserved for future use                            */
  uint32_t      RESERVED17[831U];               /**< Reserved for future use                            */
  __IM uint32_t IPVERSION_CLR;                  /**<                                                    */
  uint32_t      RESERVED18[3U];                 /**< Reserved for future use                            */
  uint32_t      RESERVED19[1U];                 /**< Reserved for future use                            */
  uint32_t      RESERVED20[59U];                /**< Reserved for future use                            */
  uint32_t      RESERVED21[1U];                 /**< Reserved for future use                            */
  uint32_t      RESERVED22[63U];                /**< Reserved for future use                            */
  uint32_t      RESERVED23[1U];                 /**< Reserved for future use                            */
  uint32_t      RESERVED24[63U];                /**< Reserved for future use                            */
  uint32_t      RESERVED25[1U];                 /**< Reserved for future use                            */
  uint32_t      RESERVED26[831U];               /**< Reserved for future use                            */
  __IM uint32_t IPVERSION_TGL;                  /**<                                                    */
  uint32_t      RESERVED27[3U];                 /**< Reserved for future use                            */
  uint32_t      RESERVED28[1U];                 /**< Reserved for future use                            */
  uint32_t      RESERVED29[59U];                /**< Reserved for future use                            */
  uint32_t      RESERVED30[1U];                 /**< Reserved for future use                            */
  uint32_t      RESERVED31[63U];                /**< Reserved for future use                            */
  uint32_t      RESERVED32[1U];                 /**< Reserved for future use                            */
  uint32_t      RESERVED33[63U];                /**< Reserved for future use                            */
  uint32_t      RESERVED34[1U];                 /**< Reserved for future use                            */
} TESTCTRL_TypeDef;
/** @} End of group EFR32FG25_TESTCTRL */

/**************************************************************************//**
 * @addtogroup EFR32FG25_TESTCTRL
 * @{
 * @defgroup EFR32FG25_TESTCTRL_BitFields TESTCTRL Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for TESTCTRL IPVERSION */
#define _TESTCTRL_IPVERSION_RESETVALUE           0x00000004UL                                 /**< Default value for TESTCTRL_IPVERSION        */
#define _TESTCTRL_IPVERSION_MASK                 0xFFFFFFFFUL                                 /**< Mask for TESTCTRL_IPVERSION                 */
#define _TESTCTRL_IPVERSION_IPVERSION_SHIFT      0                                            /**< Shift value for TESTCTRL_IPVERSION          */
#define _TESTCTRL_IPVERSION_IPVERSION_MASK       0xFFFFFFFFUL                                 /**< Bit mask for TESTCTRL_IPVERSION             */
#define _TESTCTRL_IPVERSION_IPVERSION_DEFAULT    0x00000004UL                                 /**< Mode DEFAULT for TESTCTRL_IPVERSION         */
#define TESTCTRL_IPVERSION_IPVERSION_DEFAULT     (_TESTCTRL_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for TESTCTRL_IPVERSION */

/** @} End of group EFR32FG25_TESTCTRL_BitFields */
/** @} End of group EFR32FG25_TESTCTRL */
/** @} End of group Parts */

#endif /* EFR32FG25_TESTCTRL_H */
