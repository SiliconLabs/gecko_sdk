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

typedef void(*zaf_event_distributor_cc_event_handler_handler_v1_t)(const uint8_t, const void*);

typedef struct {
  const void* data;               ///< This must point to a global data
  uint16_t command_class;
  uint8_t event;
} event_cc_t;

/**
 * ZAF Event Distributor Handler Map
 */
typedef struct {
  zaf_event_distributor_cc_event_handler_handler_v1_t handler;  ///< Custom handler
  uint16_t command_class;                                       ///< Table entry
  uint8_t version;                                              ///< Map version
} zaf_event_distributor_cc_event_handler_map_v1_t;

/**
 * Redefine latest version to a common define called latest
 */
typedef zaf_event_distributor_cc_event_handler_map_v1_t zaf_event_distributor_cc_event_handler_map_latest_t;

/**
 * Section name
 */
#define ZAF_EVENT_DISTRIBUTOR_CC_EVENT_HANDLER_SECTION "_zaf_event_distributor_cc_event_handler"

/**
 * Registers a custom event handler for a specific command class
 *
 * @param[in] command_class Command Class
 * @param[in] handler       Address of the handler function.
 */
#define ZAF_EVENT_DISTRIBUTOR_REGISTER_CC_EVENT_HANDLER(command_class, handler)                                                           \
  static const zaf_event_distributor_cc_event_handler_map_latest_t zaf_event_distributor_cc_event_handler_##command_class##event##handler \
  __attribute__((aligned(4), __used__, __section__(ZAF_EVENT_DISTRIBUTOR_CC_EVENT_HANDLER_SECTION))) = { handler, command_class, 1 };     \
  void * zaf_event_distributor_register_cc_event_handler_##table_entry##handler

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
 * @brief Enqueues an event in the application queue
 * @param event The event to enqueue.
 * @return Returns true if the event was enqueued and false otherwise.
 */
bool zaf_event_distributor_enqueue_app_event(const uint8_t event);

/**
 * @brief Enqueues an event in the application queue
 * @param event The event to enqueue.
 * @return Returns true if the event was enqueued and false otherwise.
 */
bool zaf_event_distributor_enqueue_app_event_from_isr(const uint8_t event);

/**
 * @brief Enqueues an event in the command class event queue
 *
 * @param command_class The command class to receive the event
 * @param event The event to enqueue.
 * @param data A data pointer. It must point to a global variable
 * @return Returns true if the event was enqueued and false otherwise.
 */
bool zaf_event_distributor_enqueue_cc_event(const uint16_t command_class,
                                            const uint8_t event,
                                            const void* data);

/**
 * @brief Enqueues an event in the command class event queue
 *
 * @param command_class The command class to receive the event
 * @param event The event to enqueue.
 * @param data A data pointer. It must point to a global variable
 * @return Returns true if the event was enqueued and false otherwise.
 */
bool zaf_event_distributor_enqueue_cc_event_from_isr(const uint16_t command_class,
                                                     const uint8_t event,
                                                     const void* data);

/**
 * @} // addtogroup EventDistributor
 * @} // addtogroup Events
 */

#endif /* ZAF_EVENT_DISTRIBUTOR_SOC_H */
