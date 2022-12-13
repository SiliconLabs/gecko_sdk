/**
 * @file
 * ZAF Event Distributor for SOC applications
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef ZAF_EVENT_DISTRIBUTOR_SOC_H
#define ZAF_EVENT_DISTRIBUTOR_SOC_H

#include <zaf_event_distributor.h>
#include <ZW_application_transport_interface.h>

/**
 * @addtogroup Events
 * @{
 * @addtogroup EventDistributor
 * @{
 */

/**
 * @brief Used by the application to handle protocol received events
 *
 * @param RxPackage ZW Receive Package
 */
void zaf_event_distributor_app_zw_rx(SZwaveReceivePackage *RxPackage);

/**
 * @brief Used by the application to handle protocol command status
 *
 * @param Status ZW Command Status Package
 */
void zaf_event_distributor_app_zw_command_status(SZwaveCommandStatusPackage *Status);

/**
 * @brief Used by the application to handle application/system received events
 *
 * @param event application/system received event
 */
extern void zaf_event_distributor_app_event_manager(const uint8_t event);

/**
 * @brief Used by application to verify if it is a primary controller
 *
 * @return uint8_t 1 if it is primary controller else 0
 */
uint8_t zaf_event_distributor_is_primary_controller(void);

/**
 * @} // addtogroup EventDistributor
 * @} // addtogroup Events
 */

#endif /* ZAF_EVENT_DISTRIBUTOR_SOC_H */
