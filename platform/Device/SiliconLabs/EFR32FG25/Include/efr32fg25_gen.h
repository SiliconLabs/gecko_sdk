/**************************************************************************//**
 * @file
 * @brief EFR32FG25 GEN register and bit field definitions
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
#ifndef EFR32FG25_GEN_H
#define EFR32FG25_GEN_H
#define GEN_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_GEN GEN
 * @{
 * @brief EFR32FG25 GEN Register Declaration.
 *****************************************************************************/

/** GEN RW Register Group Declaration. */
typedef struct {
  __IOM uint32_t CTRL;                               /**< New Register                                       */
} GEN_RW_TypeDef;

/** GEN RO Register Group Declaration. */
typedef struct {
  __IM uint32_t STAT;                                /**< New Register                                       */
} GEN_RO_TypeDef;

/** GEN Register Declaration. */
typedef struct {
  GEN_RW_TypeDef RW[256U];                      /**<                                                    */
  GEN_RO_TypeDef RO[256U];                      /**<                                                    */
  uint32_t       RESERVED0[512U];               /**< Reserved for future use                            */
  GEN_RW_TypeDef RW_SET[256U];                  /**<                                                    */
  GEN_RO_TypeDef RO_SET[256U];                  /**<                                                    */
  uint32_t       RESERVED1[512U];               /**< Reserved for future use                            */
  GEN_RW_TypeDef RW_CLR[256U];                  /**<                                                    */
  GEN_RO_TypeDef RO_CLR[256U];                  /**<                                                    */
  uint32_t       RESERVED2[512U];               /**< Reserved for future use                            */
  GEN_RW_TypeDef RW_TGL[256U];                  /**<                                                    */
  GEN_RO_TypeDef RO_TGL[256U];                  /**<                                                    */
} GEN_TypeDef;
/** @} End of group EFR32FG25_GEN */

/**************************************************************************//**
 * @addtogroup EFR32FG25_GEN
 * @{
 * @defgroup EFR32FG25_GEN_BitFields GEN Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for GEN RW_CTRL */
#define _GEN_RW_CTRL_RESETVALUE         0x00000000UL                                    /**< Default value for GEN_RW_CTRL               */
#define _GEN_RW_CTRL_MASK               0xFFFFFFFFUL                                    /**< Mask for GEN_RW_CTRL                        */
#define _GEN_RW_CTRL_GENERIC_SHIFT      0                                               /**< Shift value for GEN_GENERIC                 */
#define _GEN_RW_CTRL_GENERIC_MASK       0xFFFFFFFFUL                                    /**< Bit mask for GEN_GENERIC                    */
#define _GEN_RW_CTRL_GENERIC_DEFAULT    0x00000000UL                                    /**< Mode DEFAULT for GEN_RW_CTRL                */
#define GEN_RW_CTRL_GENERIC_DEFAULT     (_GEN_RW_CTRL_GENERIC_DEFAULT << 0)             /**< Shifted mode DEFAULT for GEN_RW_CTRL        */

/* Bit fields for GEN RO_STAT */
#define _GEN_RO_STAT_RESETVALUE         0x00000000UL                                    /**< Default value for GEN_RO_STAT               */
#define _GEN_RO_STAT_MASK               0xFFFFFFFFUL                                    /**< Mask for GEN_RO_STAT                        */
#define _GEN_RO_STAT_GENERIC_SHIFT      0                                               /**< Shift value for GEN_GENERIC                 */
#define _GEN_RO_STAT_GENERIC_MASK       0xFFFFFFFFUL                                    /**< Bit mask for GEN_GENERIC                    */
#define _GEN_RO_STAT_GENERIC_DEFAULT    0x00000000UL                                    /**< Mode DEFAULT for GEN_RO_STAT                */
#define GEN_RO_STAT_GENERIC_DEFAULT     (_GEN_RO_STAT_GENERIC_DEFAULT << 0)             /**< Shifted mode DEFAULT for GEN_RO_STAT        */

/** @} End of group EFR32FG25_GEN_BitFields */
/** @} End of group EFR32FG25_GEN */
/** @} End of group Parts */

#endif /* EFR32FG25_GEN_H */
