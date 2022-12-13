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
#include "green-power-af-wrapper.h"

// Generated interface function
static EmberAfStatus sli_do_decode(EmberAfClusterCommand *cmd,
                                   const sl_signature_t sig,
                                   uint8_t *outputBuffer)
{
  sl_signature_decode_status_t ret;
  ret = sl_signature_decode(cmd->buffer,
                            cmd->bufLen,
                            cmd->payloadStartIndex,
                            sig,
                            outputBuffer);
  if ( ret == SL_SIGNATURE_DECODE_OK ) {
    return EMBER_ZCL_STATUS_SUCCESS;
  } else {
    return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
  }
}

// Command parser for GpPairingSearch command
EmberAfStatus zcl_decode_green_power_cluster_gp_pairing_search_command(EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_pairing_search_command_t *cmd_struct)
{
  // Use classic mechanism to parse this command.
  uint16_t payloadOffset = cmd->payloadStartIndex;
  // Not a fixed length command

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 2u) {
    cmd_struct->options = 0xFFFF;
  } else {
    cmd_struct->options = sli_decode_parse_two_bytes(cmd, payloadOffset);

    payloadOffset += 2u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0000
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 4u
      || !((cmd_struct->options & 0x0007) == 0x0000)) {
    cmd_struct->gpdSrcId = 0xFFFFFFFF;
  } else {
    cmd_struct->gpdSrcId = sli_decode_parse_four_bytes(cmd, payloadOffset);

    payloadOffset += 4u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0002
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 8u
      || !((cmd_struct->options & 0x0007) == 0x0002)) {
    cmd_struct->gpdIeee = NULL;
  } else {
    cmd_struct->gpdIeee = sli_decode_bytes(cmd, payloadOffset);

    payloadOffset += 8u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0002
  if (!((cmd_struct->options & 0x0007) == 0x0002)) {
    cmd_struct->endpoint = 0xFF;
  } else {
    cmd_struct->endpoint = sli_decode_parse_one_byte(cmd, payloadOffset);
  }
  return EMBER_ZCL_STATUS_SUCCESS;
}

// Command parser for GpNotification command
EmberAfStatus zcl_decode_green_power_cluster_gp_notification_command(EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_notification_command_t *cmd_struct)
{
  // Use classic mechanism to parse this command.
  uint16_t payloadOffset = cmd->payloadStartIndex;
  // Not a fixed length command

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 2u) {
    cmd_struct->options = 0xFFFF;
  } else {
    cmd_struct->options = sli_decode_parse_two_bytes(cmd, payloadOffset);

    payloadOffset += 2u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0000
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 4u
      || !((cmd_struct->options & 0x0007) == 0x0000)) {
    cmd_struct->gpdSrcId = 0xFFFFFFFF;
  } else {
    cmd_struct->gpdSrcId = sli_decode_parse_four_bytes(cmd, payloadOffset);

    payloadOffset += 4u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0002
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 8u
      || !((cmd_struct->options & 0x0007) == 0x0002)) {
    cmd_struct->gpdIeee = NULL;
  } else {
    cmd_struct->gpdIeee = sli_decode_bytes(cmd, payloadOffset);

    payloadOffset += 8u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0002
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 1u
      || !((cmd_struct->options & 0x0007) == 0x0002)) {
    cmd_struct->gpdEndpoint = 0xFF;
  } else {
    cmd_struct->gpdEndpoint = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 4u) {
    cmd_struct->gpdSecurityFrameCounter = 0xFFFFFFFF;
  } else {
    cmd_struct->gpdSecurityFrameCounter = sli_decode_parse_four_bytes(cmd, payloadOffset);

    payloadOffset += 4u;
  }

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 1u) {
    cmd_struct->gpdCommandId = 0xFF;
  } else {
    cmd_struct->gpdCommandId = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset + emberAfStringLength(cmd->buffer + payloadOffset) + 1u) {
    cmd_struct->gpdCommandPayload = NULL;
  } else {
    cmd_struct->gpdCommandPayload = sli_decode_string(cmd, payloadOffset);

    payloadOffset += emberAfStringLength(cmd->buffer + payloadOffset) + 1u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x4000) || (cmd_struct->options & 0x0800)
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 2u
      || !((cmd_struct->options & 0x4000) || (cmd_struct->options & 0x0800))) {
    cmd_struct->gppShortAddress = 0xFFFF;
  } else {
    cmd_struct->gppShortAddress = sli_decode_parse_two_bytes(cmd, payloadOffset);

    payloadOffset += 2u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x4000) || (cmd_struct->options & 0x0800)
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 1u
      || !((cmd_struct->options & 0x4000) || (cmd_struct->options & 0x0800))) {
    cmd_struct->gppDistance = 0xFF;
  } else {
    cmd_struct->gppDistance = sli_decode_parse_one_byte(cmd, payloadOffset);
  }
  return EMBER_ZCL_STATUS_SUCCESS;
}

// Command parser for GpCommissioningNotification command
EmberAfStatus zcl_decode_green_power_cluster_gp_commissioning_notification_command(EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_commissioning_notification_command_t *cmd_struct)
{
  // Use classic mechanism to parse this command.
  uint16_t payloadOffset = cmd->payloadStartIndex;
  // Not a fixed length command

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 2u) {
    cmd_struct->options = 0xFFFF;
  } else {
    cmd_struct->options = sli_decode_parse_two_bytes(cmd, payloadOffset);

    payloadOffset += 2u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0000
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 4u
      || !((cmd_struct->options & 0x0007) == 0x0000)) {
    cmd_struct->gpdSrcId = 0xFFFFFFFF;
  } else {
    cmd_struct->gpdSrcId = sli_decode_parse_four_bytes(cmd, payloadOffset);

    payloadOffset += 4u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0002
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 8u
      || !((cmd_struct->options & 0x0007) == 0x0002)) {
    cmd_struct->gpdIeee = NULL;
  } else {
    cmd_struct->gpdIeee = sli_decode_bytes(cmd, payloadOffset);

    payloadOffset += 8u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0002
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 1u
      || !((cmd_struct->options & 0x0007) == 0x0002)) {
    cmd_struct->endpoint = 0xFF;
  } else {
    cmd_struct->endpoint = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 4u) {
    cmd_struct->gpdSecurityFrameCounter = 0xFFFFFFFF;
  } else {
    cmd_struct->gpdSecurityFrameCounter = sli_decode_parse_four_bytes(cmd, payloadOffset);

    payloadOffset += 4u;
  }

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 1u) {
    cmd_struct->gpdCommandId = 0xFF;
  } else {
    cmd_struct->gpdCommandId = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset + emberAfStringLength(cmd->buffer + payloadOffset) + 1u) {
    cmd_struct->gpdCommandPayload = NULL;
  } else {
    cmd_struct->gpdCommandPayload = sli_decode_string(cmd, payloadOffset);

    payloadOffset += emberAfStringLength(cmd->buffer + payloadOffset) + 1u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0800) || (cmd_struct->options & 0x0008)
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 2u
      || !((cmd_struct->options & 0x0800) || (cmd_struct->options & 0x0008))) {
    cmd_struct->gppShortAddress = 0xFFFF;
  } else {
    cmd_struct->gppShortAddress = sli_decode_parse_two_bytes(cmd, payloadOffset);

    payloadOffset += 2u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0800) || (cmd_struct->options & 0x0008)
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 1u
      || !((cmd_struct->options & 0x0800) || (cmd_struct->options & 0x0008))) {
    cmd_struct->gppLink = 0xFF;
  } else {
    cmd_struct->gppLink = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is conditionally present based on expression: cmd_struct->options & 0x0200
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 4u
      || !(cmd_struct->options & 0x0200)) {
    cmd_struct->mic = 0xFFFFFFFF;
  } else {
    cmd_struct->mic = sli_decode_parse_four_bytes(cmd, payloadOffset);
  }
  return EMBER_ZCL_STATUS_SUCCESS;
}

// Command parser for GpTranslationTableUpdate command
EmberAfStatus zcl_decode_green_power_cluster_gp_translation_table_update_command(EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_translation_table_update_command_t *cmd_struct)
{
  // Use classic mechanism to parse this command.
  uint16_t payloadOffset = cmd->payloadStartIndex;
  // Not a fixed length command

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 2u) {
    cmd_struct->options = 0xFFFF;
  } else {
    cmd_struct->options = sli_decode_parse_two_bytes(cmd, payloadOffset);

    payloadOffset += 2u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0000
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 4u
      || !((cmd_struct->options & 0x0007) == 0x0000)) {
    cmd_struct->gpdSrcId = 0xFFFFFFFF;
  } else {
    cmd_struct->gpdSrcId = sli_decode_parse_four_bytes(cmd, payloadOffset);

    payloadOffset += 4u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0002
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 8u
      || !((cmd_struct->options & 0x0007) == 0x0002)) {
    cmd_struct->gpdIeee = NULL;
  } else {
    cmd_struct->gpdIeee = sli_decode_bytes(cmd, payloadOffset);

    payloadOffset += 8u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0002
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 1u
      || !((cmd_struct->options & 0x0007) == 0x0002)) {
    cmd_struct->endpoint = 0xFF;
  } else {
    cmd_struct->endpoint = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }
  cmd_struct->translations = cmd->buffer + payloadOffset;
  return EMBER_ZCL_STATUS_SUCCESS;
}

// Command parser for GpPairing command
EmberAfStatus zcl_decode_green_power_cluster_gp_pairing_command(EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_pairing_command_t *cmd_struct)
{
  // Use classic mechanism to parse this command.
  uint16_t payloadOffset = cmd->payloadStartIndex;
  // Not a fixed length command

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 3u) {
    cmd_struct->options = 0xFFFFFFFF;
  } else {
    cmd_struct->options = sli_decode_parse_three_bytes(cmd, payloadOffset);

    payloadOffset += 3u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x000007) == 0x000000
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 4u
      || !((cmd_struct->options & 0x000007) == 0x000000)) {
    cmd_struct->gpdSrcId = 0xFFFFFFFF;
  } else {
    cmd_struct->gpdSrcId = sli_decode_parse_four_bytes(cmd, payloadOffset);

    payloadOffset += 4u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x000007) == 0x000002
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 8u
      || !((cmd_struct->options & 0x000007) == 0x000002)) {
    cmd_struct->gpdIeee = NULL;
  } else {
    cmd_struct->gpdIeee = sli_decode_bytes(cmd, payloadOffset);

    payloadOffset += 8u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x000007) == 0x000002
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 1u
      || !((cmd_struct->options & 0x000007) == 0x000002)) {
    cmd_struct->endpoint = 0xFF;
  } else {
    cmd_struct->endpoint = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x000010) == 0x000000 && ((cmd_struct->options & 0x000060) == 0x000000 || (cmd_struct->options & 0x000060) == 0x000060)
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 8u
      || !((cmd_struct->options & 0x000010) == 0x000000 && ((cmd_struct->options & 0x000060) == 0x000000 || (cmd_struct->options & 0x000060) == 0x000060))) {
    cmd_struct->sinkIeeeAddress = NULL;
  } else {
    cmd_struct->sinkIeeeAddress = sli_decode_bytes(cmd, payloadOffset);

    payloadOffset += 8u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x000010) == 0x000000 && ((cmd_struct->options & 0x000060) == 0x000000 || (cmd_struct->options & 0x000060) == 0x000060)
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 2u
      || !((cmd_struct->options & 0x000010) == 0x000000 && ((cmd_struct->options & 0x000060) == 0x000000 || (cmd_struct->options & 0x000060) == 0x000060))) {
    cmd_struct->sinkNwkAddress = 0xFFFF;
  } else {
    cmd_struct->sinkNwkAddress = sli_decode_parse_two_bytes(cmd, payloadOffset);

    payloadOffset += 2u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x000010) == 0x000000 && ((cmd_struct->options & 0x000060) == 0x000020 || (cmd_struct->options & 0x000060) == 0x000040)
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 2u
      || !((cmd_struct->options & 0x000010) == 0x000000 && ((cmd_struct->options & 0x000060) == 0x000020 || (cmd_struct->options & 0x000060) == 0x000040))) {
    cmd_struct->sinkGroupId = 0xFFFF;
  } else {
    cmd_struct->sinkGroupId = sli_decode_parse_two_bytes(cmd, payloadOffset);

    payloadOffset += 2u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x000008) == 0x000008 && (cmd_struct->options & 0x000010) != 0x000010
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 1u
      || !((cmd_struct->options & 0x000008) == 0x000008 && (cmd_struct->options & 0x000010) != 0x000010)) {
    cmd_struct->deviceId = 0xFF;
  } else {
    cmd_struct->deviceId = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x004000) == 0x004000
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 4u
      || !((cmd_struct->options & 0x004000) == 0x004000)) {
    cmd_struct->gpdSecurityFrameCounter = 0xFFFFFFFF;
  } else {
    cmd_struct->gpdSecurityFrameCounter = sli_decode_parse_four_bytes(cmd, payloadOffset);

    payloadOffset += 4u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x008000) == 0x008000
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 16u
      || !((cmd_struct->options & 0x008000) == 0x008000)) {
    cmd_struct->gpdKey = NULL;
  } else {
    cmd_struct->gpdKey = sli_decode_bytes(cmd, payloadOffset);

    payloadOffset += 16u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x010000) == 0x010000
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 2u
      || !((cmd_struct->options & 0x010000) == 0x010000)) {
    cmd_struct->assignedAlias = 0xFFFF;
  } else {
    cmd_struct->assignedAlias = sli_decode_parse_two_bytes(cmd, payloadOffset);

    payloadOffset += 2u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x020000) == 0x020000
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 1u
      || !((cmd_struct->options & 0x020000) == 0x020000)) {
    cmd_struct->groupcastRadius = 0xFF;
  } else {
    cmd_struct->groupcastRadius = sli_decode_parse_one_byte(cmd, payloadOffset);
  }
  return EMBER_ZCL_STATUS_SUCCESS;
}

// Command parser for GpProxyTableRequest command
EmberAfStatus zcl_decode_green_power_cluster_gp_proxy_table_request_command(EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_proxy_table_request_command_t *cmd_struct)
{
  // Use classic mechanism to parse this command.
  uint16_t payloadOffset = cmd->payloadStartIndex;
  // Not a fixed length command

  if (cmd->bufLen < payloadOffset
      + 1u) {
    return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
  }

  cmd_struct->options = sli_decode_parse_one_byte(cmd, payloadOffset);

  payloadOffset += 1u;

  // - Argument is conditionally present based on expression: ((cmd_struct->options & 0x18) == 0x00) && ((cmd_struct->options & 0x07) == 0x00)
  if (!(((cmd_struct->options & 0x18) == 0x00) && ((cmd_struct->options & 0x07) == 0x00))) {
    cmd_struct->gpdSrcId = 0xFFFFFFFF;
  } else {
    cmd_struct->gpdSrcId = sli_decode_parse_four_bytes(cmd, payloadOffset);

    payloadOffset += 4u;
  }

  // - Argument is conditionally present based on expression: ((cmd_struct->options & 0x18) == 0x00) && ((cmd_struct->options & 0x07) == 0x02)
  if (!(((cmd_struct->options & 0x18) == 0x00) && ((cmd_struct->options & 0x07) == 0x02))) {
    cmd_struct->gpdIeee = NULL;
  } else {
    cmd_struct->gpdIeee = sli_decode_bytes(cmd, payloadOffset);

    payloadOffset += 8u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x07) == 0x02
  if (!((cmd_struct->options & 0x07) == 0x02)) {
    cmd_struct->endpoint = 0xFF;
  } else {
    cmd_struct->endpoint = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x18) == 0x08
  if (!((cmd_struct->options & 0x18) == 0x08)) {
    cmd_struct->index = 0xFF;
  } else {
    cmd_struct->index = sli_decode_parse_one_byte(cmd, payloadOffset);
  }
  return EMBER_ZCL_STATUS_SUCCESS;
}

// Command parser for GpPairingConfiguration command
EmberAfStatus zcl_decode_green_power_cluster_gp_pairing_configuration_command(EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_pairing_configuration_command_t *cmd_struct)
{
  // Use classic mechanism to parse this command.
  uint16_t payloadOffset = cmd->payloadStartIndex;
  // Not a fixed length command

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 1u) {
    cmd_struct->actions = 0xFF;
  } else {
    cmd_struct->actions = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 2u) {
    cmd_struct->options = 0xFFFF;
  } else {
    cmd_struct->options = sli_decode_parse_two_bytes(cmd, payloadOffset);

    payloadOffset += 2u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0000
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 4u
      || !((cmd_struct->options & 0x0007) == 0x0000)) {
    cmd_struct->gpdSrcId = 0xFFFFFFFF;
  } else {
    cmd_struct->gpdSrcId = sli_decode_parse_four_bytes(cmd, payloadOffset);

    payloadOffset += 4u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0002
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 8u
      || !((cmd_struct->options & 0x0007) == 0x0002)) {
    cmd_struct->gpdIeee = NULL;
  } else {
    cmd_struct->gpdIeee = sli_decode_bytes(cmd, payloadOffset);

    payloadOffset += 8u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0002
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 1u
      || !((cmd_struct->options & 0x0007) == 0x0002)) {
    cmd_struct->endpoint = 0xFF;
  } else {
    cmd_struct->endpoint = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 1u) {
    cmd_struct->deviceId = 0xFF;
  } else {
    cmd_struct->deviceId = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0018) == 0x0010
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 1u
      || !((cmd_struct->options & 0x0018) == 0x0010)) {
    cmd_struct->groupListCount = 0xFF;
  } else {
    cmd_struct->groupListCount = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }
  if ( (cmd_struct->options & 0x0018) == 0x0010 ) {
    // Array is conditionally present based on expression: (cmd_struct->options & 0x0018) == 0x0010
    cmd_struct->groupList = cmd->buffer + payloadOffset;
    payloadOffset += cmd_struct->groupListCount * sizeof(GpPairingConfigurationGroupList);
  } else {
    cmd_struct->groupList = NULL;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0100)
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 2u
      || !((cmd_struct->options & 0x0100))) {
    cmd_struct->gpdAssignedAlias = 0xFFFF;
  } else {
    cmd_struct->gpdAssignedAlias = sli_decode_parse_two_bytes(cmd, payloadOffset);

    payloadOffset += 2u;
  }

  if (cmd->bufLen < payloadOffset
      + 1u) {
    return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
  }

  cmd_struct->groupcastRadius = sli_decode_parse_one_byte(cmd, payloadOffset);

  payloadOffset += 1u;

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0200)
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 1u
      || !((cmd_struct->options & 0x0200))) {
    cmd_struct->securityOptions = 0xFF;
  } else {
    cmd_struct->securityOptions = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0200) || (cmd_struct->options & 0x0020)
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 4u
      || !((cmd_struct->options & 0x0200) || (cmd_struct->options & 0x0020))) {
    cmd_struct->gpdSecurityFrameCounter = 0xFFFFFFFF;
  } else {
    cmd_struct->gpdSecurityFrameCounter = sli_decode_parse_four_bytes(cmd, payloadOffset);

    payloadOffset += 4u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0200)
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 16u
      || !((cmd_struct->options & 0x0200))) {
    cmd_struct->gpdSecurityKey = NULL;
  } else {
    cmd_struct->gpdSecurityKey = sli_decode_bytes(cmd, payloadOffset);

    payloadOffset += 16u;
  }

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 1u) {
    cmd_struct->numberOfPairedEndpoints = 0xFF;
  } else {
    cmd_struct->numberOfPairedEndpoints = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }
  if ( 0 < cmd_struct->numberOfPairedEndpoints && cmd_struct->numberOfPairedEndpoints < 0xFD ) {
    // Array is conditionally present based on expression: 0 < cmd_struct->numberOfPairedEndpoints && cmd_struct->numberOfPairedEndpoints < 0xFD
    cmd_struct->pairedEndpoints = cmd->buffer + payloadOffset;
    payloadOffset += cmd_struct->numberOfPairedEndpoints * sizeof(uint8_t);
  } else {
    cmd_struct->pairedEndpoints = NULL;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0400)
  if (!((cmd_struct->options & 0x0400))) {
    cmd_struct->applicationInformation = 0xFF;
  } else {
    cmd_struct->applicationInformation = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x01)
  if (!((cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x01))) {
    cmd_struct->manufacturerId = 0xFFFF;
  } else {
    cmd_struct->manufacturerId = sli_decode_parse_two_bytes(cmd, payloadOffset);

    payloadOffset += 2u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x02)
  if (!((cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x02))) {
    cmd_struct->modeId = 0xFFFF;
  } else {
    cmd_struct->modeId = sli_decode_parse_two_bytes(cmd, payloadOffset);

    payloadOffset += 2u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x04)
  if (!((cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x04))) {
    cmd_struct->numberOfGpdCommands = 0xFF;
  } else {
    cmd_struct->numberOfGpdCommands = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }
  if ( (cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x04) ) {
    // Array is conditionally present based on expression: (cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x04)
    cmd_struct->gpdCommandIdList = cmd->buffer + payloadOffset;
    payloadOffset += cmd_struct->numberOfGpdCommands * sizeof(uint8_t);
  } else {
    cmd_struct->gpdCommandIdList = NULL;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x08)
  if (!((cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x08))) {
    cmd_struct->clusterIdListCount = 0xFF;
  } else {
    cmd_struct->clusterIdListCount = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }
  if ( (cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x08) && ((cmd_struct->clusterIdListCount & 0x0F) > 0) ) {
    // Array is conditionally present based on expression: (cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x08) && ((cmd_struct->clusterIdListCount & 0x0F) > 0)
    cmd_struct->clusterListServer = cmd->buffer + payloadOffset;
    payloadOffset += (cmd_struct->clusterIdListCount & 0x0F) * sizeof(uint16_t);
  } else {
    cmd_struct->clusterListServer = NULL;
  }
  if ( (cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x08) && ((cmd_struct->clusterIdListCount >> 4) > 0) ) {
    // Array is conditionally present based on expression: (cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x08) && ((cmd_struct->clusterIdListCount >> 4) > 0)
    cmd_struct->clusterListClient = cmd->buffer + payloadOffset;
    payloadOffset += (cmd_struct->clusterIdListCount >> 4) * sizeof(uint16_t);
  } else {
    cmd_struct->clusterListClient = NULL;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x10)
  if (!((cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x10))) {
    cmd_struct->switchInformationLength = 0xFF;
  } else {
    cmd_struct->switchInformationLength = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x10)
  if (!((cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x10))) {
    cmd_struct->switchConfiguration = 0xFF;
  } else {
    cmd_struct->switchConfiguration = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x10)
  if (!((cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x10))) {
    cmd_struct->currentContactStatus = 0xFF;
  } else {
    cmd_struct->currentContactStatus = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x20)
  if (!((cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x20))) {
    cmd_struct->totalNumberOfReports = 0xFF;
  } else {
    cmd_struct->totalNumberOfReports = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x20)
  if (!((cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x20))) {
    cmd_struct->numberOfReports = 0xFF;
  } else {
    cmd_struct->numberOfReports = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }
  if ( (cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x20) ) {
    // Array is conditionally present based on expression: (cmd_struct->options & 0x0400) && (cmd_struct->applicationInformation & 0x20)
    cmd_struct->reportDescriptor = cmd->buffer + payloadOffset;
  } else {
    cmd_struct->reportDescriptor = NULL;
  }
  return EMBER_ZCL_STATUS_SUCCESS;
}

// Command parser for GpResponse command
EmberAfStatus zcl_decode_green_power_cluster_gp_response_command(EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_response_command_t *cmd_struct)
{
  // Use classic mechanism to parse this command.
  uint16_t payloadOffset = cmd->payloadStartIndex;
  // Not a fixed length command

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 1u) {
    cmd_struct->options = 0xFF;
  } else {
    cmd_struct->options = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 2u) {
    cmd_struct->tempMasterShortAddress = 0xFFFF;
  } else {
    cmd_struct->tempMasterShortAddress = sli_decode_parse_two_bytes(cmd, payloadOffset);

    payloadOffset += 2u;
  }

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 1u) {
    cmd_struct->tempMasterTxChannel = 0xFF;
  } else {
    cmd_struct->tempMasterTxChannel = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x07) == 0x00
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 4u
      || !((cmd_struct->options & 0x07) == 0x00)) {
    cmd_struct->gpdSrcId = 0xFFFFFFFF;
  } else {
    cmd_struct->gpdSrcId = sli_decode_parse_four_bytes(cmd, payloadOffset);

    payloadOffset += 4u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x07) == 0x02
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 8u
      || !((cmd_struct->options & 0x07) == 0x02)) {
    cmd_struct->gpdIeee = NULL;
  } else {
    cmd_struct->gpdIeee = sli_decode_bytes(cmd, payloadOffset);

    payloadOffset += 8u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x07) == 0x02
  if (!((cmd_struct->options & 0x07) == 0x02)) {
    cmd_struct->endpoint = 0xFF;
  } else {
    cmd_struct->endpoint = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 1u) {
    cmd_struct->gpdCommandId = 0xFF;
  } else {
    cmd_struct->gpdCommandId = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  if (cmd->bufLen < payloadOffset + emberAfStringLength(cmd->buffer + payloadOffset) + 1u) {
    return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
  }

  cmd_struct->gpdCommandPayload = sli_decode_string(cmd, payloadOffset);

  return EMBER_ZCL_STATUS_SUCCESS;
}

// Command parser for GpProxyCommissioningMode command
EmberAfStatus zcl_decode_green_power_cluster_gp_proxy_commissioning_mode_command(EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_proxy_commissioning_mode_command_t *cmd_struct)
{
  // Use classic mechanism to parse this command.
  uint16_t payloadOffset = cmd->payloadStartIndex;
  // Not a fixed length command

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 1u) {
    cmd_struct->options = 0xFF;
  } else {
    cmd_struct->options = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x02) == 0x02
  if (!((cmd_struct->options & 0x02) == 0x02)) {
    cmd_struct->commissioningWindow = 0xFFFF;
  } else {
    cmd_struct->commissioningWindow = sli_decode_parse_two_bytes(cmd, payloadOffset);

    payloadOffset += 2u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x10) == 0x10
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 1u
      || !((cmd_struct->options & 0x10) == 0x10)) {
    cmd_struct->channel = 0xFF;
  } else {
    cmd_struct->channel = sli_decode_parse_one_byte(cmd, payloadOffset);
  }
  return EMBER_ZCL_STATUS_SUCCESS;
}

// Command parser for GpNotificationResponse command
EmberAfStatus zcl_decode_green_power_cluster_gp_notification_response_command(EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_notification_response_command_t *cmd_struct)
{
  // Use classic mechanism to parse this command.
  uint16_t payloadOffset = cmd->payloadStartIndex;
  // Not a fixed length command

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 1u) {
    cmd_struct->options = 0xFF;
  } else {
    cmd_struct->options = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0000
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 4u
      || !((cmd_struct->options & 0x0007) == 0x0000)) {
    cmd_struct->gpdSrcId = 0xFFFFFFFF;
  } else {
    cmd_struct->gpdSrcId = sli_decode_parse_four_bytes(cmd, payloadOffset);

    payloadOffset += 4u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0002
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 8u
      || !((cmd_struct->options & 0x0007) == 0x0002)) {
    cmd_struct->gpdIeee = NULL;
  } else {
    cmd_struct->gpdIeee = sli_decode_bytes(cmd, payloadOffset);

    payloadOffset += 8u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0002
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 1u
      || !((cmd_struct->options & 0x0007) == 0x0002)) {
    cmd_struct->endpoint = 0xFF;
  } else {
    cmd_struct->endpoint = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 4u) {
    cmd_struct->gpdSecurityFrameCounter = 0xFFFFFFFF;
  } else {
    cmd_struct->gpdSecurityFrameCounter = sli_decode_parse_four_bytes(cmd, payloadOffset);
  }
  return EMBER_ZCL_STATUS_SUCCESS;
}

// Command parser for GpTunnelingStop command
EmberAfStatus zcl_decode_green_power_cluster_gp_tunneling_stop_command(EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_tunneling_stop_command_t *cmd_struct)
{
  // Use classic mechanism to parse this command.
  uint16_t payloadOffset = cmd->payloadStartIndex;
  // Not a fixed length command

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 1u) {
    cmd_struct->options = 0xFF;
  } else {
    cmd_struct->options = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0000
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 4u
      || !((cmd_struct->options & 0x0007) == 0x0000)) {
    cmd_struct->gpdSrcId = 0xFFFFFFFF;
  } else {
    cmd_struct->gpdSrcId = sli_decode_parse_four_bytes(cmd, payloadOffset);

    payloadOffset += 4u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0002
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 8u
      || !((cmd_struct->options & 0x0007) == 0x0002)) {
    cmd_struct->gpdIeee = NULL;
  } else {
    cmd_struct->gpdIeee = sli_decode_bytes(cmd, payloadOffset);

    payloadOffset += 8u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x0007) == 0x0002
  // - Argument is not present in all versions
  if (cmd->bufLen < payloadOffset
      + 1u
      || !((cmd_struct->options & 0x0007) == 0x0002)) {
    cmd_struct->endpoint = 0xFF;
  } else {
    cmd_struct->endpoint = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 4u) {
    cmd_struct->gpdSecurityFrameCounter = 0xFFFFFFFF;
  } else {
    cmd_struct->gpdSecurityFrameCounter = sli_decode_parse_four_bytes(cmd, payloadOffset);

    payloadOffset += 4u;
  }

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 2u) {
    cmd_struct->gppShortAddress = 0xFFFF;
  } else {
    cmd_struct->gppShortAddress = sli_decode_parse_two_bytes(cmd, payloadOffset);

    payloadOffset += 2u;
  }

  // - Argument is not present in all versions.
  if (cmd->bufLen < payloadOffset
      + 1u) {
    cmd_struct->gppDistance = 0xFF;
  } else {
    cmd_struct->gppDistance = sli_decode_parse_one_byte(cmd, payloadOffset);
  }
  return EMBER_ZCL_STATUS_SUCCESS;
}

// Signature for GpSinkCommissioningMode command
static const sl_signature_t sig_green_power_cluster_gp_sink_commissioning_mode_command = sl_zcl_green_power_cluster_gp_sink_commissioning_mode_command_signature;
// Command parser for GpSinkCommissioningMode command
EmberAfStatus zcl_decode_green_power_cluster_gp_sink_commissioning_mode_command(EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_sink_commissioning_mode_command_t *cmd_struct)
{
  // Use signature-decoding mechanism to parse this command.
  return sli_do_decode(cmd, sig_green_power_cluster_gp_sink_commissioning_mode_command, (uint8_t*)cmd_struct);
}

// Command parser for GpSinkTableRequest command
EmberAfStatus zcl_decode_green_power_cluster_gp_sink_table_request_command(EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_sink_table_request_command_t *cmd_struct)
{
  // Use classic mechanism to parse this command.
  uint16_t payloadOffset = cmd->payloadStartIndex;
  // Not a fixed length command

  if (cmd->bufLen < payloadOffset + 1u) {
    return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
  }

  cmd_struct->options = sli_decode_parse_one_byte(cmd, payloadOffset);

  payloadOffset += 1u;

  // - Argument is conditionally present based on expression: ((cmd_struct->options & 0x07) == 0x00) && ((cmd_struct->options & 0x18) == 0x00)
  if (!(((cmd_struct->options & 0x07) == 0x00) && ((cmd_struct->options & 0x18) == 0x00))) {
    cmd_struct->gpdSrcId = 0xFFFFFFFF;
  } else {
    cmd_struct->gpdSrcId = sli_decode_parse_four_bytes(cmd, payloadOffset);

    payloadOffset += 4u;
  }

  // - Argument is conditionally present based on expression: ((cmd_struct->options & 0x07) == 0x02) && ((cmd_struct->options & 0x18) == 0x00)
  if (!(((cmd_struct->options & 0x07) == 0x02) && ((cmd_struct->options & 0x18) == 0x00))) {
    cmd_struct->gpdIeee = NULL;
  } else {
    cmd_struct->gpdIeee = sli_decode_bytes(cmd, payloadOffset);

    payloadOffset += 8u;
  }

  // - Argument is conditionally present based on expression: ((cmd_struct->options & 0x07) == 0x02) && ((cmd_struct->options & 0x18) == 0x00)
  if (!(((cmd_struct->options & 0x07) == 0x02) && ((cmd_struct->options & 0x18) == 0x00))) {
    cmd_struct->endpoint = 0xFF;
  } else {
    cmd_struct->endpoint = sli_decode_parse_one_byte(cmd, payloadOffset);

    payloadOffset += 1u;
  }

  // - Argument is conditionally present based on expression: (cmd_struct->options & 0x18) == 0x08
  if (!((cmd_struct->options & 0x18) == 0x08)) {
    cmd_struct->index = 0xFF;
  } else {
    cmd_struct->index = sli_decode_parse_one_byte(cmd, payloadOffset);
  }
  return EMBER_ZCL_STATUS_SUCCESS;
}

// Signature for GpTranslationTableRequest command
static const sl_signature_t sig_green_power_cluster_gp_translation_table_request_command = sl_zcl_green_power_cluster_gp_translation_table_request_command_signature;
// Command parser for GpTranslationTableRequest command
EmberAfStatus zcl_decode_green_power_cluster_gp_translation_table_request_command(EmberAfClusterCommand * cmd, sl_zcl_green_power_cluster_gp_translation_table_request_command_t *cmd_struct)
{
  // Use signature-decoding mechanism to parse this command.
  return sli_do_decode(cmd, sig_green_power_cluster_gp_translation_table_request_command, (uint8_t*)cmd_struct);
}
