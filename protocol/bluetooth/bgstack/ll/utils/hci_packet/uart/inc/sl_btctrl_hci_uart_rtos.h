#ifndef SL_BTCTRL_HCI_UART_RTOS_H
#define SL_BTCTRL_HCI_UART_RTOS_H

#include "sl_status.h"

/**
 * Initialize RTOS task for HCI UART Reader
 */
sl_status_t sl_btctrl_hci_uart_rtos_init(void);

/**
 * Deinitialize HCI tasks
 */
void sl_btctrl_hci_uart_rtos_deinit(void);

/**
 * Get the available stack space of the HCI UART thread as determined
 * by the stack watermark recorded during execution.
 */
uint8_t sl_btctrl_hci_uart_get_stack_space(uint32_t *stack_space);

#endif
