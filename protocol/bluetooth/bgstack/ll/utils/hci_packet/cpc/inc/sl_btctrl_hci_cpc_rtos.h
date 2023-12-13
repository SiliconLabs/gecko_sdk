#ifndef SL_BTCTRL_HCI_CPC_RTOS_H
#define SL_BTCTRL_HCI_CPC_RTOS_H

/**
 * Initialize RTOS task for HCI CPC Reader
 */
sl_status_t sl_btctrl_hci_cpc_rtos_init(void);

/**
 * Deinitialize HCI tasks
 */
void sl_btctrl_hci_cpc_rtos_deinit(void);

/**
 * Callback handler when new packet is received from cpc
 */
void sl_btctrl_hci_cpc_rx(uint8_t endpoint_id, void * arg);

/**
 * Get the available stack space of the HCI CPC thread as determined
 * by the stack watermark recorded during execution.
 */
uint8_t sl_btctrl_hci_cpc_get_stack_space(uint32_t *stack_space);

#endif
