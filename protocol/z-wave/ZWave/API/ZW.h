/**
 * @file
 * @copyright 2019 Silicon Laboratories Inc.
 */
#ifndef ZWAVE_API_ZW_H_
#define ZWAVE_API_ZW_H_

/**
 * @addtogroup ZWaveAPI
 * @{
 */

/**
 * @addtogroup ZW_SET_LEARN_MODE ZW Learn Mode defines
 * Mode parameters to ZW_SetLearnMode
 * @{
 */
#define ZW_SET_LEARN_MODE_DISABLE           0x00 ///< Disable Learn Mode
#define ZW_SET_LEARN_MODE_CLASSIC           0x01 ///< Start Classic Learn Mode
#define ZW_SET_LEARN_MODE_NWI               0x02 ///< Enable Network Wide Inclusion
#define ZW_SET_LEARN_MODE_NWE               0x03 ///< Enable Network Wide Exclusion
///@}

///@}

#endif /* ZWAVE_API_ZW_H_ */
