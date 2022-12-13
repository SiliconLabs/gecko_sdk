/**
 * @file
 * @copyright 2022 Silicon Laboratories Inc.
 */
#ifndef CC_CENTRAL_SCENE_IO_H
#define CC_CENTRAL_SCENE_IO_H

#include <CC_CentralScene.h>
#include <ZAF_types.h>

/**
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup CentralScene
 * @{
 */

bool cc_central_scene_read(central_scene_configuration_t* pConfig);

bool cc_central_scene_write(const central_scene_configuration_t* pConfig);

void cc_central_scene_migrate(void);

/**
 * @}
 * @}
 */

#endif /* CC_CENTRAL_SCENE_IO_H */
