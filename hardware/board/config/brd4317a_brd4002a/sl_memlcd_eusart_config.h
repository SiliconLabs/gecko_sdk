#ifndef SL_MEMLCD_CONFIG_H
#define SL_MEMLCD_CONFIG_H

// <<< sl:start pin_tool >>>
// <eusart signal=TX,SCLK> SL_MEMLCD_SPI
// $[EUSART_SL_MEMLCD_SPI]
#define SL_MEMLCD_SPI_PERIPHERAL                 EUSART1
#define SL_MEMLCD_SPI_PERIPHERAL_NO              1

// EUSART1 TX on PC00
#define SL_MEMLCD_SPI_TX_PORT                    gpioPortC
#define SL_MEMLCD_SPI_TX_PIN                     0

// EUSART1 SCLK on PC02
#define SL_MEMLCD_SPI_SCLK_PORT                  gpioPortC
#define SL_MEMLCD_SPI_SCLK_PIN                   2

// [EUSART_SL_MEMLCD_SPI]$

// <gpio> SL_MEMLCD_SPI_CS
// $[GPIO_SL_MEMLCD_SPI_CS]
#define SL_MEMLCD_SPI_CS_PORT                    gpioPortC
#define SL_MEMLCD_SPI_CS_PIN                     6

// [GPIO_SL_MEMLCD_SPI_CS]$

// <gpio optional=true> SL_MEMLCD_EXTCOMIN
// $[GPIO_SL_MEMLCD_EXTCOMIN]
#define SL_MEMLCD_EXTCOMIN_PORT                  gpioPortA
#define SL_MEMLCD_EXTCOMIN_PIN                   0

// [GPIO_SL_MEMLCD_EXTCOMIN]$

// <<< sl:end pin_tool >>>

#endif
