/**************************************************************************//**
 * @file
 * @brief EFR32FG25 CPFIFO register and bit field definitions
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
#ifndef EFR32FG25_CPFIFO_H
#define EFR32FG25_CPFIFO_H

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32FG25_CPFIFO CPFIFO
 * @{
 * @brief EFR32FG25 CPFIFO Register Declaration.
 *****************************************************************************/

/** CPFIFO COPROC Register Group Declaration. */
typedef struct {
  __IOM uint32_t FIFO;                               /**<                                                    */
  uint32_t       RESERVED0[1023U];                   /**< Reserved for future use                            */
} CPFIFO_COPROC_TypeDef;

/** CPFIFO Register Declaration. */
typedef struct {
  CPFIFO_COPROC_TypeDef COPROC[1024U];           /**<                                                    */
} CPFIFO_TypeDef;
/** @} End of group EFR32FG25_CPFIFO */

/**************************************************************************//**
 * @addtogroup EFR32FG25_CPFIFO
 * @{
 * @defgroup EFR32FG25_CPFIFO_BitFields CPFIFO Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for CPFIFO FIFO */
#define _CPFIFO_FIFO_RESETVALUE      0x00000000UL                                       /**< Default value for CPFIFO_FIFO               */
#define _CPFIFO_FIFO_MASK            0xFFFFFFFFUL                                       /**< Mask for CPFIFO_FIFO                        */
#define _CPFIFO_FIFO_DATA_SHIFT      0                                                  /**< Shift value for CPFIFO_DATA                 */
#define _CPFIFO_FIFO_DATA_MASK       0xFFFFFFFFUL                                       /**< Bit mask for CPFIFO_DATA                    */
#define _CPFIFO_FIFO_DATA_DEFAULT    0x00000000UL                                       /**< Mode DEFAULT for CPFIFO_FIFO                */
#define CPFIFO_FIFO_DATA_DEFAULT     (_CPFIFO_FIFO_DATA_DEFAULT << 0)                   /**< Shifted mode DEFAULT for CPFIFO_FIFO        */

/** @} End of group EFR32FG25_CPFIFO_BitFields */
/** @} End of group EFR32FG25_CPFIFO */
/** @} End of group Parts */

#endif /* EFR32FG25_CPFIFO_H */
