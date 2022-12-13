/**
 * @file
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef _CC_CENTRAL_SCENE_CONFIG_H_
#define _CC_CENTRAL_SCENE_CONFIG_H_

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Command Class Central Scene Configuration

// <o> Number of supported scenes <1..255:1> <f.d>
// <i> Default: 3
#define CC_CENTRAL_SCENE_SUPPORTED_SCENES  3

// <o> Supported key attributes for Scene 1 <1..255:1> <f.h>
// <i> This Bit Mask field advertises the attributes supported by the corresponding scene
// <i> Default: 7
#define CC_CENTRAL_SCENE_SUPPORTED_SCENES_SCENE_1  7

// <q> Supported key attributes
// <i> True indicates that all keys are identical, False if different key attributes supported
// <i> Default: 1
#define CC_CENTRAL_SCENE_PROPERTIES  1

// </h>

// <<< end of configuration section >>>

#endif /* _CC_CENTRAL_SCENE_CONFIG_H_ */
