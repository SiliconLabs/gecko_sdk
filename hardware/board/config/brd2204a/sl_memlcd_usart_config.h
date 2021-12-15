#ifndef SL_MEMLCD_CONFIG_H
#define SL_MEMLCD_CONFIG_H

// <<< sl:start pin_tool >>>
// <usart signal=TX,CLK> SL_MEMLCD_SPI
// $[USART_SL_MEMLCD_SPI]
#define SL_MEMLCD_SPI_PERIPHERAL                 USART1
#define SL_MEMLCD_SPI_PERIPHERAL_NO              1

// USART1 TX on PA14
#define SL_MEMLCD_SPI_TX_PORT                    gpioPortA
#define SL_MEMLCD_SPI_TX_PIN                     14
#define SL_MEMLCD_SPI_TX_LOC                     6

// USART1 CLK on PC15
#define SL_MEMLCD_SPI_CLK_PORT                   gpioPortC
#define SL_MEMLCD_SPI_CLK_PIN                    15
#define SL_MEMLCD_SPI_CLK_LOC                    3

// [USART_SL_MEMLCD_SPI]$

// <gpio> SL_MEMLCD_SPI_CS
// $[GPIO_SL_MEMLCD_SPI_CS]
#define SL_MEMLCD_SPI_CS_PORT                    gpioPortC
#define SL_MEMLCD_SPI_CS_PIN                     14

// [GPIO_SL_MEMLCD_SPI_CS]$

// <gpio optional=true> SL_MEMLCD_EXTCOMIN
// $[GPIO_SL_MEMLCD_EXTCOMIN]
#define SL_MEMLCD_EXTCOMIN_PORT                  gpioPortA
#define SL_MEMLCD_EXTCOMIN_PIN                   11

// [GPIO_SL_MEMLCD_EXTCOMIN]$

// <<< sl:end pin_tool >>>

#endif
