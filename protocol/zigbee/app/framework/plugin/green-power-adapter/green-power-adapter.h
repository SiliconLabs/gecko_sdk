/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef _SILABS_GREEN_POWER_ADAPTER_H_
#define _SILABS_GREEN_POWER_ADAPTER_H_

#include "zap-command.h"
#include "zap-id.h"
#include "zap-type.h"
#include "zap-enabled-incoming-commands.h"
#define SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "zap-command-structs.h"
#undef SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT

#include "sl_service_function.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"

#ifdef SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "zcl-framework-core-config.h"
#endif // SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT

#include "green-power-adapter-config.h"

#endif // SL_COMPONENT_CATALOG_PRESENT

#include "green-power-stack-wrapper.h"
#include "green-power-print-wrapper.h"
#include "green-power-token-wrapper.h"
#include "green-power-event-wrapper.h"
#include "green-power-af-wrapper.h"

/** @brief Parser function for "GpNotification" ZCL command from "Green Power" cluster
 */
EmberAfStatus zcl_decode_green_power_cluster_gp_notification_command (EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_notification_command_t *cmd_struct);
/** @brief Parser function for "GpPairingSearch" ZCL command from "Green Power" cluster
 */
EmberAfStatus zcl_decode_green_power_cluster_gp_pairing_search_command (EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_pairing_search_command_t *cmd_struct);
/** @brief Parser function for "GpTunnelingStop" ZCL command from "Green Power" cluster
 */
EmberAfStatus zcl_decode_green_power_cluster_gp_tunneling_stop_command (EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_tunneling_stop_command_t *cmd_struct);
/** @brief Parser function for "GpCommissioningNotification" ZCL command from "Green Power" cluster
 */
EmberAfStatus zcl_decode_green_power_cluster_gp_commissioning_notification_command (EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_commissioning_notification_command_t *cmd_struct);
/** @brief Parser function for "GpSinkCommissioningMode" ZCL command from "Green Power" cluster
 */
EmberAfStatus zcl_decode_green_power_cluster_gp_sink_commissioning_mode_command (EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_sink_commissioning_mode_command_t *cmd_struct);
/** @brief Parser function for "GpTranslationTableUpdate" ZCL command from "Green Power" cluster
 */
EmberAfStatus zcl_decode_green_power_cluster_gp_translation_table_update_command (EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_translation_table_update_command_t *cmd_struct);
/** @brief Parser function for "GpTranslationTableRequest" ZCL command from "Green Power" cluster
 */
EmberAfStatus zcl_decode_green_power_cluster_gp_translation_table_request_command (EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_translation_table_request_command_t *cmd_struct);
/** @brief Parser function for "GpPairingConfiguration" ZCL command from "Green Power" cluster
 */
EmberAfStatus zcl_decode_green_power_cluster_gp_pairing_configuration_command (EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_pairing_configuration_command_t *cmd_struct);
/** @brief Parser function for "GpSinkTableRequest" ZCL command from "Green Power" cluster
 */
EmberAfStatus zcl_decode_green_power_cluster_gp_sink_table_request_command (EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_sink_table_request_command_t *cmd_struct);
/** @brief Parser function for "GpProxyTableResponse" ZCL command from "Green Power" cluster
 */
EmberAfStatus zcl_decode_green_power_cluster_gp_proxy_table_response_command (EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_proxy_table_response_command_t *cmd_struct);
/** @brief Parser function for "GpNotificationResponse" ZCL command from "Green Power" cluster
 */
EmberAfStatus zcl_decode_green_power_cluster_gp_notification_response_command (EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_notification_response_command_t *cmd_struct);
/** @brief Parser function for "GpPairing" ZCL command from "Green Power" cluster
 */
EmberAfStatus zcl_decode_green_power_cluster_gp_pairing_command (EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_pairing_command_t *cmd_struct);
/** @brief Parser function for "GpProxyCommissioningMode" ZCL command from "Green Power" cluster
 */
EmberAfStatus zcl_decode_green_power_cluster_gp_proxy_commissioning_mode_command (EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_proxy_commissioning_mode_command_t *cmd_struct);
/** @brief Parser function for "GpResponse" ZCL command from "Green Power" cluster
 */
EmberAfStatus zcl_decode_green_power_cluster_gp_response_command (EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_response_command_t *cmd_struct);
/** @brief Parser function for "GpTranslationTableResponse" ZCL command from "Green Power" cluster
 */
EmberAfStatus zcl_decode_green_power_cluster_gp_translation_table_response_command (EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_translation_table_response_command_t *cmd_struct);
/** @brief Parser function for "GpSinkTableResponse" ZCL command from "Green Power" cluster
 */
EmberAfStatus zcl_decode_green_power_cluster_gp_sink_table_response_command (EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_sink_table_response_command_t *cmd_struct);
/** @brief Parser function for "GpProxyTableRequest" ZCL command from "Green Power" cluster
 */
EmberAfStatus zcl_decode_green_power_cluster_gp_proxy_table_request_command (EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_proxy_table_request_command_t *cmd_struct);

/// ///////////

#endif //_SILABS_GREEN_POWER_ADAPTER_H_
