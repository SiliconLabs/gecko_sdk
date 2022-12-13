/**
 * @file
 * Common ZAF Event Distributor interface
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef ZAF_EVENT_DISTRIBUTOR_H
#define ZAF_EVENT_DISTRIBUTOR_H

#include <stdint.h>
#include <stdbool.h>
#include <EventDistributor.h>

/**
 * @addtogroup Events
 * @{
 * @addtogroup EventDistributor
 * @{
 */

/**
 * @brief Initializes the ZAF Event Distributor component.
 *
 * This function invokes EventDistributorConfig().
 */
void zaf_event_distributor_init(void);

/**
 * @brief Gets the events distributor
 *
 * Each variation (NCP,SOC) must implement it's own event distributor table
 *
 * @return const SEventDistributor
 */
const SEventDistributor *zaf_event_distributor_get(void);

/**
 * @brief Distributes events.
 *
 * Wraps EventDistributorDistribute().
 *
 * @return true In case of success
 * @return false In case of error
 */
bool zaf_event_distributor_distribute(void);

/**
 * @} // addtogroup EventDistributor
 * @} // addtogroup Events
 */

#endif /* ZAF_EVENT_DISTRIBUTOR_H */
