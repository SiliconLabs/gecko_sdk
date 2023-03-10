#ifndef SL_HCI_UART_H
#define SL_HCI_UART_H

#include "em_common.h"

typedef uint32_t Ecode_t;

void sl_hci_uart_init(void);
int sl_hci_uart_read(uint8_t *data, uint16_t len);
Ecode_t sl_hci_uart_write(uint8_t *data, uint16_t len, void (*callback)(uint32_t));
int sl_hci_uart_rx_buffered_length();
void sl_hci_disable_sleep(bool set_sleep_disabled);

#endif // SL_HCI_UART_H
