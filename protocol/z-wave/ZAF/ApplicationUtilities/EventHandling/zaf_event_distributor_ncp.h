/**
 * @file
 * ZAF Event Distributor for NCP applications
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef ZAF_EVENT_DISTRIBUTOR_NCP_H
#define ZAF_EVENT_DISTRIBUTOR_NCP_H

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
 * @brief Used by the application to handle state changes in the NCP state
 * machine
 *
 */
extern void zaf_event_distributor_app_state_change(void);

/**
 * @brief Used by the application to handle serial data received
 *
 */
extern void zaf_event_distributor_app_serial_data_rx(void);

/**
 * @brief Used by the application to handle serial timeout
 *
 */
extern void zaf_event_distributor_app_serial_timeout(void);

/**
 * @} // addtogroup EventDistributor
 * @} // addtogroup Events
 */

#endif /* ZAF_EVENT_DISTRIBUTOR_NCP_H */
