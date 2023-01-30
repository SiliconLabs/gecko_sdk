/**
 * @file
 * Configuration file for the CC Central Scene Config
 *
 * @copyright 2022 Silicon Laboratories Inc.
 */

#include <cc_central_scene_config_api.h>
#include <ZAF_types.h>
#include <cc_central_scene_io.h>

uint8_t cc_central_scene_get_supported_key_attributes(ZW_CENTRAL_SCENE_SUPPORTED_REPORT_1BYTE_V3_FRAME * pData)
{
  pData->supportedScenes = CC_CENTRAL_SCENE_SUPPORTED_SCENES; // Number of buttons
  pData->properties1 |= (CC_CENTRAL_SCENE_IDENTICAL << 0);  //Indicates that all keys are identical. Using different key attriubtes are not supported currently in the applications
  uint8_t size_of_supported_key_attributes = CC_CENTRAL_SCENE_SIZE_OF_SUPPORTED_SCENES_ATTRIBUTES; // This value is hardcoded to work with WallController, represents "sizeof(CC_CENTRAL_SCENE_SUPPORTED_SCENES_SCENE_1)"
  pData->properties1 |= (size_of_supported_key_attributes << 1); //This field advertises the size of each “Supported Key Attributes” field measured in bytes
  pData->variantgroup1.supportedKeyAttributesForScene1 = CC_CENTRAL_SCENE_SUPPORTED_SCENES_SCENE_1;  // By default "Key Pressed 1 time", "Key Released", and "Key Held Down" are the supported scenes
  return 1;
}
