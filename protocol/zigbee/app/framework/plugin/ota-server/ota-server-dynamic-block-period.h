/***************************************************************************//**
 * @file
 * @brief APIs and defines for the dynamic block request feature of the OTA
 *        Server plugin.
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

#ifndef OTA_SERVER_DYNAMIC_BLOCK_PERIOD_H
#define OTA_SERVER_DYNAMIC_BLOCK_PERIOD_H

#include "ota-server.h"

#ifdef DYNAMIC_MIN_BLOCK_PERIOD_SUPPORT
void    sli_zigbee_af_ota_server_dynamic_block_period_init();
void    sli_zigbee_af_ota_server_dynamic_block_period_tick();
uint8_t sli_zigbee_af_ota_server_check_dynamic_block_period_download(EmberAfImageBlockRequestCallbackStruct *data);
void    sli_zigbee_af_ota_server_complete_dynamic_block_period_download(EmberNodeId clientId);
bool    sli_zigbee_af_ota_server_dynamic_block_period_client_uses_seconds(EmberNodeId clientId);
#else // DYNAMIC_MIN_BLOCK_PERIOD_SUPPORT
// Stubs
  #define sli_zigbee_af_ota_server_dynamic_block_period_init()
  #define sli_zigbee_af_ota_server_dynamic_block_period_tick()
  #define sli_zigbee_af_ota_server_check_dynamic_block_period_download(arg) \
  EMBER_ZCL_STATUS_SUCCESS
  #define sli_zigbee_af_ota_server_complete_dynamic_block_period_download(arg)
  #define sli_zigbee_af_ota_server_dynamic_block_period_client_uses_seconds(arg) false
#endif // DYNAMIC_MIN_BLOCK_PERIOD_SUPPORT

#endif // OTA_SERVER_DYNAMIC_BLOCK_PERIOD_H
