/***************************************************************************//**
 * @file sl_zigbee_dynamic_commissioning.h
 * @brief implements hooks for performing device interview during dynamic
 * commissioning
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef SL_ZIGBEE_DYNAMIC_COMMISSIONING_H
#define SL_ZIGBEE_DYNAMIC_COMMISSIONING_H

#include "sl_enum.h"
#include "stack/include/sl_zigbee_address_info.h"
#include "stack/include/ember-types.h"

SL_ENUM_GENERIC(sl_zigbee_dynamic_commissioning_event_t, uint16_t) {
  /// the trust center has received notification of commissioning request
  SL_ZIGBEE_DYNAMIC_COMMISSIONING_EVENT_OPEN_REQUEST,
  /// key negotiation has completed - allow the device on immediately or conduct further interview
  SL_ZIGBEE_DEVICE_INTERVIEW_EVENT_READY,
  /// device interview is continuing, refresh timers
  SL_ZIGBEE_DEVICE_INTERVIEW_EVENT_CONTINUE,
  /// interview was concluded as non-success - commissioning failed
  SL_ZIGBEE_DEVICE_INTERVIEW_EVENT_REJECTED,
  /// interview concluded as success - key is being sent
  SL_ZIGBEE_DEVICE_INTERVIEW_EVENT_TIMEOUT,
  /// a message was received for a downstream child
  SL_ZIGBEE_DEVICE_INTERVIEW_EVENT_DOWNSTREAM_MIDPOINT,
  /// the interview has concluded and the device should be allowed on the network
  SL_ZIGBEE_DYNAMIC_COMMISSIONING_EVENT_ACCEPTED,
  /// an error was encountered during commisioning
  SL_ZIGBEE_DYNAMIC_COMMISSIONING_EVENT_ERROR,
  /// dynamic commissioning complete, device is on the network
  SL_ZIGBEE_DYNAMIC_COMMISSIONING_EVENT_COMPLETE,
};

/**
 * @brief an application defined callback that passes commissioning events to allow
 *        the application to start device interview process and monitor failures during
 *        commissioning.
 * @param[in]  ids  the address info of the device associated with the interview event
 * @param[in]  event  the type of interview event that triggered the alert
 * @return a status code of SL_STATUS_NETWORK_UP allows the TC to transport the network
 *         key to the joiners, SL_STATUS_OK when SL_ZIGBEE_DEVICE_INTERVIEW_EVENT_READY
 *         is sent keeps the status as device interview in progress.
 *         all other return codes deny joining
 * @note
 */
extern void sl_zigbee_dynamic_commissioning_alert_callback(sl_zigbee_address_info *ids,
                                                           sl_zigbee_dynamic_commissioning_event_t event);

/**
 * @brief The API calls the application callback which allow the application to decide if
 *        device interview is to proceed. This setups the internal state to either transport
 *        key or stay in commissioning state to wait for device interview to wait.
 * @param[in]  sl_zigbee_address_info structure to hold the short and long address
 * @param[in]  sl_zigbee_dynamic_commissioning_event_t event to pass to the application to
 *             indicate the state of commissioning.
 */
void sl_zigbee_device_interview_status_update(sl_zigbee_address_info *ids,
                                              sl_zigbee_dynamic_commissioning_event_t event);

/**
 * @brief sets the policy for whether to keep the commissioning window open
 *        to perform device interview procedures.  If false send the network key
 *        after key negotiation completes
 * @param[in]  open_interview boolean indicating whether to keep commissioning open
 */
void sl_zigbee_dynamic_commissioning_set_open_for_interview(bool open_interview);

/**
 * @brief gets the policy for whether the stack will keep the commissioning window open
 *        to perform device interview procedures, or send the network key after key
 *        negotiation completes
 * @return  boolean indicating whether commissioning is kept open
 */
bool sl_zigbee_dynamic_commissioning_is_open_for_interview(void);

/**
 * @brief API to refresh the timers during device interview to keep temporary entries active
 * @param[in]  device_short   short address of the node
 * @param[in]  device_long  EUI64 of the noded
 */
void sli_zigbee_dynamic_commissioning_refresh_timers(EmberNodeId device_short,
                                                     EmberEUI64 device_long);
/**
 * @brief API to update the status of device interview
 * @param[in] sl_zigbee_address_info structure to hold the short and long address
 */
void sli_zigbee_dynamic_commissioning_device_interview_ready(sl_zigbee_address_info *ids);
#endif // SL_ZIGBEE_DYNAMIC_COMMISSIONING_H
