/***************************************************************************//**
 * @brief CPC handlers and initialization for the Connect stack
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
#ifndef __NCP_CPC_INTERFACE_H__
#define __NCP_CPC_INTERFACE_H__

void sli_connect_cpc_send_command(uint8_t *command, uint16_t length);
void sli_connect_ncp_process_incoming_api_command(uint8_t *apiCommandData);
bool sli_connect_is_ncp_connected(void);
void connect_stack_cpc_init(void);

#endif
