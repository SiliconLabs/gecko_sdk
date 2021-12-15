#ifndef SL_MEMLCD_CONFIG_H
#define SL_MEMLCD_CONFIG_H

// <<< sl:start pin_tool >>>
// <usart signal=TX,CLK> SL_MEMLCD_SPI
// $[USART_SL_MEMLCD_SPI]
#define SL_MEMLCD_SPI_PERIPHERAL                 USART0
#define SL_MEMLCD_SPI_PERIPHERAL_NO              0

// USART0 TX on PD00
#define SL_MEMLCD_SPI_TX_PORT                    gpioPortD
#define SL_MEMLCD_SPI_TX_PIN                     0

// USART0 CLK on PD02
#define SL_MEMLCD_SPI_CLK_PORT                   gpioPortD
#define SL_MEMLCD_SPI_CLK_PIN                    2

// [USART_SL_MEMLCD_SPI]$

// <gpio> SL_MEMLCD_SPI_CS
// $[GPIO_SL_MEMLCD_SPI_CS]
#define SL_MEMLCD_SPI_CS_PORT                    gpioPortD
#define SL_MEMLCD_SPI_CS_PIN                     4

// [GPIO_SL_MEMLCD_SPI_CS]$

// <gpio optional=true> SL_MEMLCD_EXTCOMIN
// $[GPIO_SL_MEMLCD_EXTCOMIN]
#define SL_MEMLCD_EXTCOMIN_PORT                  gpioPortB
#define SL_MEMLCD_EXTCOMIN_PIN                   0

// [GPIO_SL_MEMLCD_EXTCOMIN]$

// <<< sl:end pin_tool >>>

#endif
