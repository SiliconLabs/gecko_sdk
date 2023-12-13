/**
 * @file
 * Platform abstraction for Zniffer application
 * 
 * @copyright 2022 Silicon Laboratories Inc.
 */
#include <Zniffer_hw.h>
#include <zw_region_config.h>
#include <board.h>
//#define DEBUGPRINT
#include "DebugPrint.h"
// #include <utils.h>
#include <zpal_uart_config_ext.h>
#include <zniffer_config.h>

static const zpal_uart_config_ext_t zpal_uart_config_ext = {
#if defined(ZNIFFER_TX_PIN)
    .tx_pin = ZNIFFER_TX_PIN,
#endif /* defined(ZNIFFER_TX_PIN) */
#if defined(ZNIFFER_TX_PORT)
    .tx_port = ZNIFFER_TX_PORT,
#endif /* defined(ZNIFFER_TX_PORT) */
#if defined(ZNIFFER_TX_LOC)
    .tx_loc = ZNIFFER_TX_LOC,
#endif /* defined(ZNIFFER_TX_LOC) */
#if defined(ZNIFFER_RX_PIN)
    .rx_pin = ZNIFFER_RX_PIN,
#endif /* defined(ZNIFFER_RX_PIN) */
#if defined(ZNIFFER_RX_PORT)
    .rx_port = ZNIFFER_RX_PORT,
#endif /* defined(ZNIFFER_RX_PORT) */
#if defined(ZNIFFER_RX_LOC)
    .rx_loc = ZNIFFER_RX_LOC,
#endif /* defined(ZNIFFER_RX_LOC) */
};

void Zniffer_hw_init(void)
{

}

const void * Zniffer_get_uart_config_ext(void)
{
  return &zpal_uart_config_ext;
}
