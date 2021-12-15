#ifndef SL_MEMLCD_CONFIG_H
#define SL_MEMLCD_CONFIG_H

// <<< sl:start pin_tool >>>
// <eusart signal=TX,SCLK> SL_MEMLCD_SPI
// $[EUSART_SL_MEMLCD_SPI]
#warning "Memory LCD SPI peripheral not configured"
// #define SL_MEMLCD_SPI_PERIPHERAL     EUSART1
// #define SL_MEMLCD_SPI_PERIPHERAL_NO  1

// #define SL_MEMLCD_SPI_SCLK_LOC        11
// #define SL_MEMLCD_SPI_SCLK_PORT       gpioPortC
// #define SL_MEMLCD_SPI_SCLK_PIN        8
// #define SL_MEMLCD_SPI_TX_LOC         11
// #define SL_MEMLCD_SPI_TX_PORT        gpioPortC
// #define SL_MEMLCD_SPI_TX_PIN         6
// [EUSART_SL_MEMLCD_SPI]$

// <gpio> SL_MEMLCD_SPI_CS
// $[GPIO_SL_MEMLCD_SPI_CS]
#warning "Memory LCD SPI CS pin not configured"
// #define SL_MEMLCD_SPI_CS_PORT        gpioPortD
// #define SL_MEMLCD_SPI_CS_PIN         14
// [GPIO_SL_MEMLCD_SPI_CS]$

// <gpio optional=true> SL_MEMLCD_EXTCOMIN
// $[GPIO_SL_MEMLCD_EXTCOMIN]
// #define SL_MEMLCD_EXTCOMIN_PORT      gpioPortD
// #define SL_MEMLCD_EXTCOMIN_PIN       13
// [GPIO_SL_MEMLCD_EXTCOMIN]$

// <<< sl:end pin_tool >>>

#endif
