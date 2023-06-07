/***************************************************************************//**
 * @file
 * @brief CLI for the Device Management Server plugin.
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

#include "app/framework/include/af.h"
#include "device-management-server.h"
#include "app/framework/plugin/device-management-server/device-management-common.h"
#ifndef EMBER_AF_GENERATE_CLI
  #error The Device Management Server plugin is not compatible with the legacy CLI.
#endif

void sli_zigbee_af_device_management_server_cli_print(sl_cli_command_arg_t *arguments)
{
  emberAfDeviceManagementServerPrint();
}

void sli_zigbee_af_device_management_server_cli_tenancy(sl_cli_command_arg_t *arguments)
{
  EmberAfDeviceManagementTenancy tenancy;
  tenancy.implementationDateTime = sl_cli_get_argument_uint32(arguments, 0);
  tenancy.tenancy = sl_cli_get_argument_uint32(arguments, 1);

  emberAfPluginDeviceManagementSetTenancy(&tenancy,
                                          false);
}

void sli_zigbee_af_device_management_server_cli_provider_id(sl_cli_command_arg_t *arguments)
{
  uint32_t providerId = sl_cli_get_argument_uint32(arguments, 0);
  emberAfPluginDeviceManagementSetProviderId(providerId);
}

void sli_zigbee_af_device_management_server_cli_issuer_event_id(sl_cli_command_arg_t *arguments)
{
  uint32_t issuerEventId = sl_cli_get_argument_uint32(arguments, 0);
  emberAfPluginDeviceManagementSetIssuerEventId(issuerEventId);
}

void sli_zigbee_af_device_management_server_cli_tariff_type(sl_cli_command_arg_t *arguments)
{
  EmberAfTariffType tariffType = (EmberAfTariffType) sl_cli_get_argument_uint8(arguments, 0);
  emberAfPluginDeviceManagementSetTariffType(tariffType);
}

void sli_zigbee_af_device_management_server_cli_supplier(sl_cli_command_arg_t *arguments)
{
  uint8_t length;
  EmberAfDeviceManagementSupplier supplier;

  uint8_t endpoint = sl_cli_get_argument_uint32(arguments, 0);
  supplier.proposedProviderId = sl_cli_get_argument_uint32(arguments, 1);
  supplier.implementationDateTime = sl_cli_get_argument_uint32(arguments, 2);
  supplier.providerChangeControl =  sl_cli_get_argument_uint32(arguments, 3);
  length = sl_zigbee_copy_string_arg(arguments, 4,
                                     supplier.proposedProviderName + 1,
                                     EMBER_AF_DEVICE_MANAGEMENT_MAXIMUM_PROPOSED_PROVIDER_NAME_LENGTH, false);
  supplier.proposedProviderName[0] = length;
  length = sl_zigbee_copy_string_arg(arguments, 5,
                                     supplier.proposedProviderContactDetails + 1,
                                     EMBER_AF_DEVICE_MANAGEMENT_MAXIMUM_PROPOSED_PROVIDER_CONTACT_DETAILS_LENGTH, false);
  supplier.proposedProviderContactDetails[0] = length;
  emberAfPluginDeviceManagementSetSupplier(endpoint, &supplier);
}

void sli_zigbee_af_device_management_server_cli_site_id(sl_cli_command_arg_t *arguments)
{
  uint8_t length;
  EmberAfDeviceManagementSiteId siteId;

  length = sl_zigbee_copy_string_arg(arguments, 0,
                                     siteId.siteId + 1,
                                     EMBER_AF_DEVICE_MANAGEMENT_MAXIMUM_SITE_ID_LENGTH, false);
  siteId.siteId[0] = length;
  siteId.implementationDateTime = sl_cli_get_argument_uint32(arguments, 1);

  emberAfPluginDeviceManagementSetSiteId(&siteId);
}

void sli_zigbee_af_device_management_server_cli_cin(sl_cli_command_arg_t *arguments)
{
  uint8_t length;
  EmberAfDeviceManagementCIN cin;

  length = sl_zigbee_copy_string_arg(arguments, 0,
                                     cin.cin + 1,
                                     EMBER_AF_DEVICE_MANAGEMENT_MAXIMUM_CIN_LENGTH, false);
  cin.cin[0] = length;
  cin.implementationDateTime = sl_cli_get_argument_uint32(arguments, 1);

  emberAfPluginDeviceManagementSetCIN(&cin);
}

void sli_zigbee_af_device_management_server_cli_password(sl_cli_command_arg_t *arguments)
{
  uint8_t length;
  EmberAfDeviceManagementPassword password;

  length = sl_zigbee_copy_string_arg(arguments, 0,
                                     password.password + 1,
                                     EMBER_AF_DEVICE_MANAGEMENT_MAXIMUM_PASSWORD_LENGTH, false);
  password.password[0] = length;
  password.implementationDateTime = sl_cli_get_argument_uint32(arguments, 1);
  password.durationInMinutes = sl_cli_get_argument_uint16(arguments, 2);
  password.passwordType = sl_cli_get_argument_uint8(arguments, 3);

  emberAfPluginDeviceManagementSetPassword(&password);
}

// plugin device-management-server pub-chg-of-tenancy <dst:2> <src endpoint:1>  <dst endpoint:1>
void sli_zigbee_af_device_management_server_cli_publish_change_of_tenancy(sl_cli_command_arg_t *arguments)
{
  EmberNodeId dstAddr = (EmberNodeId) sl_cli_get_argument_uint16(arguments, 0);
  uint8_t srcEndpoint =  sl_cli_get_argument_uint8(arguments, 1);
  uint8_t dstEndpoint =  sl_cli_get_argument_uint8(arguments, 2);
  emberAfDeviceManagementClusterPublishChangeOfTenancy(dstAddr, srcEndpoint, dstEndpoint);
}

// plugin device-management-server pub-chg-of-tenancy <dst:2> <src endpoint:1>  <dst endpoint:1>
void sli_zigbee_af_device_management_server_cli_publish_change_of_supplier(sl_cli_command_arg_t *arguments)
{
  EmberNodeId dstAddr = (EmberNodeId)sl_cli_get_argument_uint16(arguments, 0);
  uint8_t srcEndpoint =  sl_cli_get_argument_uint8(arguments, 1);
  uint8_t dstEndpoint =  sl_cli_get_argument_uint8(arguments, 2);
  emberAfDeviceManagementClusterPublishChangeOfSupplier(dstAddr, srcEndpoint, dstEndpoint);
}

// plugin device-management-server update-site-id <dst:2> <src endpoint:1>  <dst endpoint:1>
void sli_zigbee_af_device_management_server_cli_update_site_id(sl_cli_command_arg_t *arguments)
{
  EmberNodeId dstAddr = (EmberNodeId)sl_cli_get_argument_uint16(arguments, 0);
  uint8_t srcEndpoint =  sl_cli_get_argument_uint8(arguments, 1);
  uint8_t dstEndpoint =  sl_cli_get_argument_uint8(arguments, 2);
  emberAfDeviceManagementClusterUpdateSiteId(dstAddr, srcEndpoint, dstEndpoint);
}

// plugin device-management-server update-cin <dst:2> <src endpoint:1>  <dst endpoint:1>
void sli_zigbee_af_device_management_server_cli_update_cin(sl_cli_command_arg_t *arguments)
{
  EmberNodeId dstAddr = (EmberNodeId)sl_cli_get_argument_uint16(arguments, 0);
  uint8_t srcEndpoint =  sl_cli_get_argument_uint8(arguments, 1);
  uint8_t dstEndpoint =  sl_cli_get_argument_uint8(arguments, 2);
  emberAfDeviceManagementClusterUpdateCIN(dstAddr, srcEndpoint, dstEndpoint);
}

// plugin device-management-server pendingUpdatesMask <pendingUpdatesMask:1>
void sli_zigbee_af_device_management_server_cli_pending_updates(sl_cli_command_arg_t *arguments)
{
  EmberAfDeviceManagementChangePendingFlags pendingUpdatesMask = sl_cli_get_argument_uint8(arguments, 0);
  emberAfDeviceManagementClusterSetPendingUpdates(pendingUpdatesMask);
}

void sli_zigbee_af_device_management_server_cli_send_request_new_password_response(sl_cli_command_arg_t *arguments)
{
  uint8_t passwordType = sl_cli_get_argument_uint8(arguments, 0);
  EmberNodeId dstAddr = (EmberNodeId)sl_cli_get_argument_uint16(arguments, 1);
  uint8_t srcEndpoint =  sl_cli_get_argument_uint8(arguments, 2);
  uint8_t dstEndpoint =  sl_cli_get_argument_uint8(arguments, 3);
  emberAfDeviceManagementClusterSendRequestNewPasswordResponse(passwordType,
                                                               dstAddr,
                                                               srcEndpoint,
                                                               dstEndpoint);
}
