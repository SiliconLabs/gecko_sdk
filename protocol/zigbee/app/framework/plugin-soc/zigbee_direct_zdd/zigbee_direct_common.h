/***************************************************************************//**
 * @file zigbee_direct_common.h
 * @brief common defines for Zigbee Direct
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SILABS_ZIGBEE_DIRECT_COMMON_H
#define SILABS_ZIGBEE_DIRECT_COMMON_H

 #include "zigbee_direct_security.h"
 #include "stack/include/sl_zigbee_security_manager_dlk_ecc.h"

/* connection table */
typedef struct {
  bool inUse;
  bool isMaster;
  uint8_t connectionHandle;
  uint8_t bondingHandle;
  uint8_t remoteAddress[6];
} bleConnectionTable_t;

enum {
  HANDLE_ZIGBEE_DIRECT = 0,
  MAX_ADV_HANDLES = 1
};

extern bleConnectionTable_t bleConnectionTable[];
extern uint16_t sl_zvd_node_id;
extern EmberEUI64 sl_zvd_eui;
extern uint8_t sl_my_connection;
extern sl_zigbee_direct_connection_status_t sl_zvd_connection_status;
extern sl_zigbee_direct_connection_status_t sl_zvd_connection_status_next;
extern uint8_t sl_zvd_public_point_x[DLK_ECC_COORDINATE_SIZE];
extern uint8_t sl_zvd_public_point_y[DLK_ECC_COORDINATE_SIZE];
extern uint8_t sl_my_connection;

#define SL_ZIGBEE_DIRECT_ADVERTISEMENT_LENGTH 16
#define SL_ZIGBEE_DIRECT_RESPONSE_MIN_LENGTH (ZDO_MESSAGE_OVERHEAD)
#define SL_ZIGBEE_DIRECT_RESPONSE_MAX_LENGTH 0xFF

extern uint8_t sli_zigbee_direct_ad_data[SL_ZIGBEE_DIRECT_ADVERTISEMENT_LENGTH];

#define SL_ZIGBEE_DIRECT_CONFIGURE_INTERFACE_COMMAND_ID 0
#define SL_ZIGBEE_DIRECT_CONFIGURE_TIMEOUT_COMMAND_ID 1

#define SL_ZIGBEE_DIRECT_DEVICE_LIGHT_ENDPOINT 1

#endif // SILABS_ZIGBEE_DIRECT_COMMON_H
