/**
 * @file
 * Configuration file for the CC Central Scene Config
 *
 * @copyright 2022 Silicon Laboratories Inc.
 */
#ifndef _CC_CENTRAL_SCENE_CONFIG_API_H_
#define _CC_CENTRAL_SCENE_CONFIG_API_H_

#include <stdint.h>
#include <cc_central_scene_config.h>
#include <CC_CentralScene.h>

/**
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup CentralScene
 * @{
 */

uint8_t cc_central_scene_get_supported_key_attributes(ZW_CENTRAL_SCENE_SUPPORTED_REPORT_1BYTE_V3_FRAME * pData);

/**
 * @}
 * @}
 */

#endif /* _CC_CENTRAL_SCENE_CONFIG_API_H_ */
