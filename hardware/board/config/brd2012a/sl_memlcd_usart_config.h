#ifndef SL_MEMLCD_CONFIG_H
#define SL_MEMLCD_CONFIG_H

// <<< sl:start pin_tool >>>
// <usart signal=TX,CLK> SL_MEMLCD_SPI
// $[USART_SL_MEMLCD_SPI]
#define SL_MEMLCD_SPI_PERIPHERAL                 USART0
#define SL_MEMLCD_SPI_PERIPHERAL_NO              0

// USART0 TX on PE10
#define SL_MEMLCD_SPI_TX_PORT                    gpioPortE
#define SL_MEMLCD_SPI_TX_PIN                     10
#define SL_MEMLCD_SPI_ROUTE_LOC                  0

// USART0 CLK on PE12
#define SL_MEMLCD_SPI_CLK_PORT                   gpioPortE
#define SL_MEMLCD_SPI_CLK_PIN                    12

// [USART_SL_MEMLCD_SPI]$

// <gpio> SL_MEMLCD_SPI_CS
// $[GPIO_SL_MEMLCD_SPI_CS]
#define SL_MEMLCD_SPI_CS_PORT                    gpioPortA
#define SL_MEMLCD_SPI_CS_PIN                     10

// [GPIO_SL_MEMLCD_SPI_CS]$

// <gpio optional=true> SL_MEMLCD_EXTCOMIN
// $[GPIO_SL_MEMLCD_EXTCOMIN]
#define SL_MEMLCD_EXTCOMIN_PORT                  gpioPortF
#define SL_MEMLCD_EXTCOMIN_PIN                   3

// [GPIO_SL_MEMLCD_EXTCOMIN]$

// <<< sl:end pin_tool >>>

#endif
