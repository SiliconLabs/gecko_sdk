/**
 * @file
 * Platform abstraction for Zniffer application
 * 
 * @copyright 2022 Silicon Laboratories Inc.
 */
#ifndef ZNIFFER_HW_H_
#define ZNIFFER_HW_H_

/**
 * Initialize hardware modules specific to Serial API application.
 */
void Zniffer_hw_init(void);

/**
 * Get zpal-uart config extension.
 */
const void* Zniffer_get_uart_config_ext(void);

#endif /* ZNIFFER_HW_H_ */
