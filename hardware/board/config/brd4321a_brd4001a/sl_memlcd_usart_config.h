#ifndef SL_MEMLCD_CONFIG_H
#define SL_MEMLCD_CONFIG_H

// <<< sl:start pin_tool >>>
// <usart signal=TX,CLK> SL_MEMLCD_SPI
// $[USART_SL_MEMLCD_SPI]
#define SL_MEMLCD_SPI_PERIPHERAL                 USART2
#define SL_MEMLCD_SPI_PERIPHERAL_NO              2

// USART2 TX on PB3
#define SL_MEMLCD_SPI_TX_PORT                    gpioPortB
#define SL_MEMLCD_SPI_TX_PIN                     3
#define SL_MEMLCD_SPI_TX_LOC                     1

// USART2 CLK on PC4
#define SL_MEMLCD_SPI_CLK_PORT                   gpioPortC
#define SL_MEMLCD_SPI_CLK_PIN                    4
#define SL_MEMLCD_SPI_CLK_LOC                    0

// [USART_SL_MEMLCD_SPI]$

// <gpio> SL_MEMLCD_SPI_CS
// $[GPIO_SL_MEMLCD_SPI_CS]
#define SL_MEMLCD_SPI_CS_PORT                    gpioPortA
#define SL_MEMLCD_SPI_CS_PIN                     6

// [GPIO_SL_MEMLCD_SPI_CS]$

// <gpio optional=true> SL_MEMLCD_EXTCOMIN
// $[GPIO_SL_MEMLCD_EXTCOMIN]
#define SL_MEMLCD_EXTCOMIN_PORT                  gpioPortA
#define SL_MEMLCD_EXTCOMIN_PIN                   15

// [GPIO_SL_MEMLCD_EXTCOMIN]$

// <<< sl:end pin_tool >>>

#endif
