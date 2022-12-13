/**
 * @file
 * @brief Network learn module
 * @copyright 2019 Silicon Laboratories Inc.
 */

#ifndef ZAF_APPLICATIONUTILITIES_ZAF_NETWORK_LEARN_H_
#define ZAF_APPLICATIONUTILITIES_ZAF_NETWORK_LEARN_H_

#include "ZW_basis_api.h"

/**
 * @addtogroup ZAF
 * @{
 * @addtogroup Network
 * @{
 * @addtogroup LearnMode Network Learn Mode
 * @{
 */

/**
 * Sets network learn mode to given value.
 *
 * This function is called when node should be added or removed from the network,
 * or to enable Smart Start.
 *
 * @param bMode Network mode to be set. Refer to @ref E_NETWORK_LEARN_MODE_ACTION
 */
void ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_ACTION bMode);

/**
 * @} //
 * @} //
 * @} //
 */

#endif /* ZAF_APPLICATIONUTILITIES_ZAF_NETWORK_LEARN_H_ */
