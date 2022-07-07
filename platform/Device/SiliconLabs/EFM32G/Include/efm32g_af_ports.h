/***************************************************************************//**
 * @file
 * @brief EFM32G_AF_PORTS register and bit field definitions
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
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
 ******************************************************************************/

#if defined(__ICCARM__)
#pragma system_include       /* Treat file as system include file. */
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang system_header  /* Treat file as system include file. */
#endif

/***************************************************************************//**
 * @addtogroup Parts
 * @{
 ******************************************************************************/
/***************************************************************************//**
 * @defgroup EFM32G_AF_Ports
 * @{
 ******************************************************************************/

#define AF_CMU_CLK0_PORT(i)         ((i) == 0 ? 0 : (i) == 1 ? 2 :  -1)                               /**< Port number for AF_CMU_CLK0 location number i */
#define AF_CMU_CLK1_PORT(i)         ((i) == 0 ? 0 : (i) == 1 ? 3 :  -1)                               /**< Port number for AF_CMU_CLK1 location number i */
#define AF_EBI_AD00_PORT(i)         ((i) == 0 ? 4 :  -1)                                              /**< Port number for AF_EBI_AD00 location number i */
#define AF_EBI_AD01_PORT(i)         ((i) == 0 ? 4 :  -1)                                              /**< Port number for AF_EBI_AD01 location number i */
#define AF_EBI_AD02_PORT(i)         ((i) == 0 ? 4 :  -1)                                              /**< Port number for AF_EBI_AD02 location number i */
#define AF_EBI_AD03_PORT(i)         ((i) == 0 ? 4 :  -1)                                              /**< Port number for AF_EBI_AD03 location number i */
#define AF_EBI_AD04_PORT(i)         ((i) == 0 ? 4 :  -1)                                              /**< Port number for AF_EBI_AD04 location number i */
#define AF_EBI_AD05_PORT(i)         ((i) == 0 ? 4 :  -1)                                              /**< Port number for AF_EBI_AD05 location number i */
#define AF_EBI_AD06_PORT(i)         ((i) == 0 ? 4 :  -1)                                              /**< Port number for AF_EBI_AD06 location number i */
#define AF_EBI_AD07_PORT(i)         ((i) == 0 ? 4 :  -1)                                              /**< Port number for AF_EBI_AD07 location number i */
#define AF_EBI_AD08_PORT(i)         ((i) == 0 ? 0 :  -1)                                              /**< Port number for AF_EBI_AD08 location number i */
#define AF_EBI_AD09_PORT(i)         ((i) == 0 ? 0 :  -1)                                              /**< Port number for AF_EBI_AD09 location number i */
#define AF_EBI_AD10_PORT(i)         ((i) == 0 ? 0 :  -1)                                              /**< Port number for AF_EBI_AD10 location number i */
#define AF_EBI_AD11_PORT(i)         ((i) == 0 ? 0 :  -1)                                              /**< Port number for AF_EBI_AD11 location number i */
#define AF_EBI_AD12_PORT(i)         ((i) == 0 ? 0 :  -1)                                              /**< Port number for AF_EBI_AD12 location number i */
#define AF_EBI_AD13_PORT(i)         ((i) == 0 ? 0 :  -1)                                              /**< Port number for AF_EBI_AD13 location number i */
#define AF_EBI_AD14_PORT(i)         ((i) == 0 ? 0 :  -1)                                              /**< Port number for AF_EBI_AD14 location number i */
#define AF_EBI_AD15_PORT(i)         ((i) == 0 ? 0 :  -1)                                              /**< Port number for AF_EBI_AD15 location number i */
#define AF_EBI_CS0_PORT(i)          ((i) == 0 ? 3 :  -1)                                              /**< Port number for AF_EBI_CS0 location number i */
#define AF_EBI_CS1_PORT(i)          ((i) == 0 ? 3 :  -1)                                              /**< Port number for AF_EBI_CS1 location number i */
#define AF_EBI_CS2_PORT(i)          ((i) == 0 ? 3 :  -1)                                              /**< Port number for AF_EBI_CS2 location number i */
#define AF_EBI_CS3_PORT(i)          ((i) == 0 ? 3 :  -1)                                              /**< Port number for AF_EBI_CS3 location number i */
#define AF_EBI_WEn_PORT(i)          ((i) == 0 ? 5 :  -1)                                              /**< Port number for AF_EBI_WEn location number i */
#define AF_EBI_REn_PORT(i)          ((i) == 0 ? 5 :  -1)                                              /**< Port number for AF_EBI_REn location number i */
#define AF_EBI_ARDY_PORT(i)         ((i) == 0 ? 5 :  -1)                                              /**< Port number for AF_EBI_ARDY location number i */
#define AF_EBI_ALE_PORT(i)          ((i) == 0 ? 5 :  -1)                                              /**< Port number for AF_EBI_ALE location number i */
#define AF_TIMER0_CC0_PORT(i)       ((i) == 0 ? 0 : (i) == 1 ? 0 : (i) == 2 ? 5 : (i) == 3 ? 3 :  -1) /**< Port number for AF_TIMER0_CC0 location number i */
#define AF_TIMER0_CC1_PORT(i)       ((i) == 0 ? 0 : (i) == 1 ? 0 : (i) == 2 ? 5 : (i) == 3 ? 3 :  -1) /**< Port number for AF_TIMER0_CC1 location number i */
#define AF_TIMER0_CC2_PORT(i)       ((i) == 0 ? 0 : (i) == 1 ? 0 : (i) == 2 ? 5 : (i) == 3 ? 3 :  -1) /**< Port number for AF_TIMER0_CC2 location number i */
#define AF_TIMER0_CDTI0_PORT(i)     ((i) == 0 ? 0 : (i) == 1 ? 2 : (i) == 2 ? 5 : (i) == 3 ? 2 :  -1) /**< Port number for AF_TIMER0_CDTI0 location number i */
#define AF_TIMER0_CDTI1_PORT(i)     ((i) == 0 ? 0 : (i) == 1 ? 2 : (i) == 2 ? 5 : (i) == 3 ? 2 :  -1) /**< Port number for AF_TIMER0_CDTI1 location number i */
#define AF_TIMER0_CDTI2_PORT(i)     ((i) == 0 ? 0 : (i) == 1 ? 2 : (i) == 2 ? 5 : (i) == 3 ? 2 :  -1) /**< Port number for AF_TIMER0_CDTI2 location number i */
#define AF_TIMER1_CC0_PORT(i)       ((i) == 0 ? 2 : (i) == 1 ? 4 : (i) == 2 ? 1 :  -1)                /**< Port number for AF_TIMER1_CC0 location number i */
#define AF_TIMER1_CC1_PORT(i)       ((i) == 0 ? 2 : (i) == 1 ? 4 : (i) == 2 ? 1 :  -1)                /**< Port number for AF_TIMER1_CC1 location number i */
#define AF_TIMER1_CC2_PORT(i)       ((i) == 0 ? 2 : (i) == 1 ? 4 : (i) == 2 ? 1 :  -1)                /**< Port number for AF_TIMER1_CC2 location number i */
#define AF_TIMER1_CDTI0_PORT(i)     (-1)                                                              /**< Port number for AF_TIMER1_CDTI0 location number i */
#define AF_TIMER1_CDTI1_PORT(i)     (-1)                                                              /**< Port number for AF_TIMER1_CDTI1 location number i */
#define AF_TIMER1_CDTI2_PORT(i)     (-1)                                                              /**< Port number for AF_TIMER1_CDTI2 location number i */
#define AF_TIMER2_CC0_PORT(i)       ((i) == 0 ? 0 : (i) == 1 ? 0 : (i) == 2 ? 2 :  -1)                /**< Port number for AF_TIMER2_CC0 location number i */
#define AF_TIMER2_CC1_PORT(i)       ((i) == 0 ? 0 : (i) == 1 ? 0 : (i) == 2 ? 2 :  -1)                /**< Port number for AF_TIMER2_CC1 location number i */
#define AF_TIMER2_CC2_PORT(i)       ((i) == 0 ? 0 : (i) == 1 ? 0 : (i) == 2 ? 2 :  -1)                /**< Port number for AF_TIMER2_CC2 location number i */
#define AF_TIMER2_CDTI0_PORT(i)     (-1)                                                              /**< Port number for AF_TIMER2_CDTI0 location number i */
#define AF_TIMER2_CDTI1_PORT(i)     (-1)                                                              /**< Port number for AF_TIMER2_CDTI1 location number i */
#define AF_TIMER2_CDTI2_PORT(i)     (-1)                                                              /**< Port number for AF_TIMER2_CDTI2 location number i */
#define AF_USART0_TX_PORT(i)        ((i) == 0 ? 4 : (i) == 1 ? 4 : (i) == 2 ? 2 :  -1)                /**< Port number for AF_USART0_TX location number i */
#define AF_USART0_RX_PORT(i)        ((i) == 0 ? 4 : (i) == 1 ? 4 : (i) == 2 ? 2 :  -1)                /**< Port number for AF_USART0_RX location number i */
#define AF_USART0_CLK_PORT(i)       ((i) == 0 ? 4 : (i) == 1 ? 4 : (i) == 2 ? 2 :  -1)                /**< Port number for AF_USART0_CLK location number i */
#define AF_USART0_CS_PORT(i)        ((i) == 0 ? 4 : (i) == 1 ? 4 : (i) == 2 ? 2 :  -1)                /**< Port number for AF_USART0_CS location number i */
#define AF_USART1_TX_PORT(i)        ((i) == 0 ? 2 : (i) == 1 ? 3 :  -1)                               /**< Port number for AF_USART1_TX location number i */
#define AF_USART1_RX_PORT(i)        ((i) == 0 ? 2 : (i) == 1 ? 3 :  -1)                               /**< Port number for AF_USART1_RX location number i */
#define AF_USART1_CLK_PORT(i)       ((i) == 0 ? 1 : (i) == 1 ? 3 :  -1)                               /**< Port number for AF_USART1_CLK location number i */
#define AF_USART1_CS_PORT(i)        ((i) == 0 ? 1 : (i) == 1 ? 3 :  -1)                               /**< Port number for AF_USART1_CS location number i */
#define AF_USART2_TX_PORT(i)        ((i) == 0 ? 2 : (i) == 1 ? 1 :  -1)                               /**< Port number for AF_USART2_TX location number i */
#define AF_USART2_RX_PORT(i)        ((i) == 0 ? 2 : (i) == 1 ? 1 :  -1)                               /**< Port number for AF_USART2_RX location number i */
#define AF_USART2_CLK_PORT(i)       ((i) == 0 ? 2 : (i) == 1 ? 1 :  -1)                               /**< Port number for AF_USART2_CLK location number i */
#define AF_USART2_CS_PORT(i)        ((i) == 0 ? 2 : (i) == 1 ? 1 :  -1)                               /**< Port number for AF_USART2_CS location number i */
#define AF_UART0_TX_PORT(i)         ((i) == 0 ? 5 : (i) == 1 ? 4 : (i) == 2 ? 0 : (i) == 3 ? 2 :  -1) /**< Port number for AF_UART0_TX location number i */
#define AF_UART0_RX_PORT(i)         ((i) == 0 ? 5 : (i) == 1 ? 4 : (i) == 2 ? 0 : (i) == 3 ? 2 :  -1) /**< Port number for AF_UART0_RX location number i */
#define AF_UART0_CLK_PORT(i)        (-1)                                                              /**< Port number for AF_UART0_CLK location number i */
#define AF_UART0_CS_PORT(i)         (-1)                                                              /**< Port number for AF_UART0_CS location number i */
#define AF_LEUART0_TX_PORT(i)       ((i) == 0 ? 3 : (i) == 1 ? 1 : (i) == 2 ? 4 :  -1)                /**< Port number for AF_LEUART0_TX location number i */
#define AF_LEUART0_RX_PORT(i)       ((i) == 0 ? 3 : (i) == 1 ? 1 : (i) == 2 ? 4 :  -1)                /**< Port number for AF_LEUART0_RX location number i */
#define AF_LEUART1_TX_PORT(i)       ((i) == 0 ? 2 : (i) == 1 ? 0 :  -1)                               /**< Port number for AF_LEUART1_TX location number i */
#define AF_LEUART1_RX_PORT(i)       ((i) == 0 ? 2 : (i) == 1 ? 0 :  -1)                               /**< Port number for AF_LEUART1_RX location number i */
#define AF_LETIMER0_OUT0_PORT(i)    ((i) == 0 ? 3 : (i) == 1 ? 1 : (i) == 2 ? 5 : (i) == 3 ? 2 :  -1) /**< Port number for AF_LETIMER0_OUT0 location number i */
#define AF_LETIMER0_OUT1_PORT(i)    ((i) == 0 ? 3 : (i) == 1 ? 1 : (i) == 2 ? 5 : (i) == 3 ? 2 :  -1) /**< Port number for AF_LETIMER0_OUT1 location number i */
#define AF_PCNT0_S0IN_PORT(i)       ((i) == 0 ? 2 : (i) == 1 ? 4 : (i) == 2 ? 2 :  -1)                /**< Port number for AF_PCNT0_S0IN location number i */
#define AF_PCNT0_S1IN_PORT(i)       ((i) == 0 ? 2 : (i) == 1 ? 4 : (i) == 2 ? 2 :  -1)                /**< Port number for AF_PCNT0_S1IN location number i */
#define AF_PCNT1_S0IN_PORT(i)       ((i) == 0 ? 2 : (i) == 1 ? 1 :  -1)                               /**< Port number for AF_PCNT1_S0IN location number i */
#define AF_PCNT1_S1IN_PORT(i)       ((i) == 0 ? 2 : (i) == 1 ? 1 :  -1)                               /**< Port number for AF_PCNT1_S1IN location number i */
#define AF_PCNT2_S0IN_PORT(i)       ((i) == 0 ? 3 : (i) == 1 ? 4 :  -1)                               /**< Port number for AF_PCNT2_S0IN location number i */
#define AF_PCNT2_S1IN_PORT(i)       ((i) == 0 ? 3 : (i) == 1 ? 4 :  -1)                               /**< Port number for AF_PCNT2_S1IN location number i */
#define AF_ACMP0_OUT_PORT(i)        ((i) == 0 ? 4 : (i) == 1 ? 4 :  -1)                               /**< Port number for AF_ACMP0_OUT location number i */
#define AF_ACMP1_OUT_PORT(i)        ((i) == 0 ? 5 : (i) == 1 ? 4 :  -1)                               /**< Port number for AF_ACMP1_OUT location number i */
#define AF_I2C0_SDA_PORT(i)         ((i) == 0 ? 0 : (i) == 1 ? 3 : (i) == 2 ? 2 : (i) == 3 ? 3 :  -1) /**< Port number for AF_I2C0_SDA location number i */
#define AF_I2C0_SCL_PORT(i)         ((i) == 0 ? 0 : (i) == 1 ? 3 : (i) == 2 ? 2 : (i) == 3 ? 3 :  -1) /**< Port number for AF_I2C0_SCL location number i */
#define AF_DBG_SWO_PORT(i)          ((i) == 0 ? 5 : (i) == 1 ? 2 :  -1)                               /**< Port number for AF_DBG_SWO location number i */
#define AF_DBG_SWDIO_PORT(i)        ((i) == 0 ? 5 : (i) == 1 ? 5 :  -1)                               /**< Port number for AF_DBG_SWDIO location number i */
#define AF_DBG_SWCLK_PORT(i)        ((i) == 0 ? 5 : (i) == 1 ? 5 :  -1)                               /**< Port number for AF_DBG_SWCLK location number i */

/** @} End of group EFM32G_AF_Ports */
/** @} End of group Parts */
