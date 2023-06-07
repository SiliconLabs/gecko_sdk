/**
 * @file
 *
 * Generates CC lists used for the Node Information Frame and for validation of incoming frames.
 *
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef ZAF_CC_LIST_GENERATOR_H
#define ZAF_CC_LIST_GENERATOR_H

#include <stdint.h>
#include <stdbool.h>
#include <ZAF_types.h>

/**
 * @addtogroup ZAF
 * @{
 * @addtogroup CC_LIST Command Classes List Generator
 * @{
 */

/**
 * @brief Gets all lists based on an endpoint
 *
 * @param[in] endpoint 0 for root device, 1-N where N is max number of endpoints, other values are invalid.
 * @param[out] unsecure_included_ccs A pointer to the list of unsecure included Command Classes
 * @param[out] secure_included_unsecure_ccs A pointer to the list of secure included unsecure Command Classes
 * @param[out] secure_included_secure_ccs A pointer to the list of secure included secure Command Classes
 */
void zafi_cc_list_generator_get_lists(uint8_t endpoint, zaf_cc_list_t **unsecure_included_ccs, zaf_cc_list_t **secure_included_unsecure_ccs, zaf_cc_list_t **secure_included_secure_ccs);

/**
 * Generates 3 CC lists for the root device and for each supported endpoint.
 *
 * @remarks Must be invoked by \ref ZAF_Init().
 */
void zafi_cc_list_generator_generate(void);

/**
 * @brief Frees the lists generate by \ref zafi_cc_list_generator_generate
 *
 * @remarks MUST NOT be invoked from the application because the CC lists are used during the lifetime of the device.
 */
void zafi_cc_list_generator_destroy(void);

/**
 * @} // CC_LIST
 * @} // ZAF
 */
#endif /* ZAF_CC_LIST_GENERATOR_H */
