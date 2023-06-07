/***************************************************************************//**
 * @file
 * @brief Routines for the ZLL Scenes Client plugin.
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

#include "../../include/af.h"
#include "../scenes-client/scenes-client.h"

#include "zap-cluster-command-parser.h"

bool emberAfScenesClusterEnhancedAddSceneResponseCallback(EmberAfClusterCommand *cmd)
{
  sl_zcl_scenes_cluster_enhanced_add_scene_response_command_t cmd_data;

  if (zcl_decode_scenes_cluster_enhanced_add_scene_response_command(cmd, &cmd_data)
      != EMBER_ZCL_STATUS_SUCCESS) {
    return false;
  }

  return emberAfPluginScenesClientParseAddSceneResponse(cmd,
                                                        cmd_data.status,
                                                        cmd_data.groupId,
                                                        cmd_data.sceneId);
}

bool emberAfScenesClusterEnhancedViewSceneResponseCallback(EmberAfClusterCommand *cmd)
{
  sl_zcl_scenes_cluster_enhanced_view_scene_response_command_t cmd_data;

  if (zcl_decode_scenes_cluster_enhanced_view_scene_response_command(cmd, &cmd_data)
      != EMBER_ZCL_STATUS_SUCCESS) {
    return false;
  }

  return emberAfPluginScenesClientParseViewSceneResponse(cmd,
                                                         cmd_data.status,
                                                         cmd_data.groupId,
                                                         cmd_data.sceneId,
                                                         cmd_data.transitionTime,
                                                         cmd_data.sceneName,
                                                         cmd_data.extensionFieldSets);
}

bool emberAfScenesClusterCopySceneResponseCallback(EmberAfClusterCommand *cmd)
{
  sl_zcl_scenes_cluster_copy_scene_response_command_t cmd_data;

  if (zcl_decode_scenes_cluster_copy_scene_response_command(cmd, &cmd_data)
      != EMBER_ZCL_STATUS_SUCCESS) {
    return false;
  }

  emberAfScenesClusterPrintln("RX: CopySceneResponse 0x%x, 0x%2x, 0x%x",
                              cmd_data.status,
                              cmd_data.groupIdFrom,
                              cmd_data.sceneIdFrom);
  emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_SUCCESS);
  return true;
}

uint32_t emberAfZllScenesClusterClientCommandParse(sl_service_opcode_t opcode,
                                                   sl_service_function_context_t *context)
{
  (void)opcode;

  EmberAfClusterCommand *cmd = (EmberAfClusterCommand *)context->data;
  bool wasHandled = false;

  if (!cmd->mfgSpecific) {
    switch (cmd->commandId) {
      case ZCL_COPY_SCENE_RESPONSE_COMMAND_ID:
      {
        wasHandled = emberAfScenesClusterCopySceneResponseCallback(cmd);
        break;
      }
      case ZCL_ENHANCED_ADD_SCENE_RESPONSE_COMMAND_ID:
      {
        wasHandled = emberAfScenesClusterEnhancedAddSceneResponseCallback(cmd);
        break;
      }
      case ZCL_ENHANCED_VIEW_SCENE_RESPONSE_COMMAND_ID:
      {
        wasHandled = emberAfScenesClusterEnhancedViewSceneResponseCallback(cmd);
        break;
      }
    }
  }

  return ((wasHandled)
          ? EMBER_ZCL_STATUS_SUCCESS
          : EMBER_ZCL_STATUS_UNSUP_COMMAND);
}
