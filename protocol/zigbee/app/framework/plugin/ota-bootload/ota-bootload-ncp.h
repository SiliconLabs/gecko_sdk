/***************************************************************************//**
 * @file
 * @brief SPI/UART Interface to bootloading the NCP from a connected host.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

bool sli_zigbee_af_start_ncp_bootloader_communications(void);
void sli_zigbee_af_post_ncp_bootload(bool success);
bool sli_zigbee_af_reboot_ncp_after_bootload(void);

// These primitives are called by the Xmodem code to pass data via
// the specific mechanism (UART or SPI).
bool sli_zigbee_af_bootload_send_data(const uint8_t *data, uint16_t length);
bool sli_zigbee_af_bootload_send_byte(uint8_t byte);
bool sli_zigbee_af_bootload_wait_char(uint8_t *data, bool expect, uint8_t expected);
