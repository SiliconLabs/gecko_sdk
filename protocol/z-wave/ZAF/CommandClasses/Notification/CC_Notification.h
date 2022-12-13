/**
 * @file
 * Handler for Command Class Notification.
 *
 * @addtogroup CC
 * @{
 * @addtogroup Notification
 * @{
 *
 * Command Class Notification enables a device to send notifications like
 * "smoke detected" or "window opened".
 *
 * CC Notification is typically used in sensor applications because it supports
 * many different notification/sensor types.
 *
 * CC Notification requires at least one notification to be configured by
 * implementing the functions declared in cc_notification_config_api.h.
 * Simplicity Studio / SLC generates this configuration automatically based on
 * user configuration in *.cc_config files.
 *
 * This command class offers one single API function to be used by the
 * application:
 * - CC_Notification_TriggerAndTransmit()
 *
 * The specification of CC Notification can be found in
 * https://github.com/Z-Wave-Alliance/AWG/blob/main/source/application_command_classes/command_class_definitions/notification_command_class_version_3-8.rst.
 *
 * @}
 * @}
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _CC_NOTIFICATION_H_
#define _CC_NOTIFICATION_H_

#include <ZW_classcmd.h>
#include <CC_Common.h>
#include <ZW_TransportEndpoint.h>

/**
 * @addtogroup CC
 * @{
 * @addtogroup Notification
 * @{
 */

/**
 *  the maximum length of the notification bitmask array
 */
#define NOTIFICATION_BITMASK_ARRAY_LENGTH   32
/**
 * Notification type (8 bit).
 */
typedef enum
{
  NOTIFICATION_TYPE_NONE,
  NOTIFICATION_TYPE_SMOKE_ALARM = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_SMOKE_ALARM),
  NOTIFICATION_TYPE_CO_ALARM = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_CO_ALARM),
  NOTIFICATION_TYPE_CO2_ALARM = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_CO2_ALARM),
  NOTIFICATION_TYPE_HEAT_ALARM = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_HEAT_ALARM),
  NOTIFICATION_TYPE_WATER_ALARM = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_WATER_ALARM),
  NOTIFICATION_TYPE_ACCESS_CONTROL = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_ACCESS_CONTROL),
  NOTIFICATION_TYPE_HOME_SECURITY = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_HOME_SECURITY),
  NOTIFICATION_TYPE_POWER_MANAGEMENT = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_POWER_MANAGEMENT),
  NOTIFICATION_TYPE_SYSTEM = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_SYSTEM),
  NOTIFICATION_TYPE_EMERGENCY_ALARM = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_EMERGENCY_ALARM),
  NOTIFICATION_TYPE_CLOCK = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_CLOCK),
  NOTIFICATION_TYPE_MULTIDEVICE = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_MULTIDEVICE)
} notification_type_t;


/**
 * General purpose notification event
 */
typedef enum
{
  NOTIFICATION_EVENT_NO_EVENT,
  NOTIFICATION_EVENT_UNKNOWN_EVENT = 0xFE
}NOTIFICATION_EVENT;

/**
 * Notification event (8 bit) for notification type NOTIFICATION_TYPE_HOME_SECURITY.
 */
typedef enum
{
  NOTIFICATION_EVENT_HOME_SECURITY_NO_EVENT,
  NOTIFICATION_EVENT_HOME_SECURITY_INTRUSION,
  NOTIFICATION_EVENT_HOME_SECURITY_INTRUSION_UNKNOWN_EV,
  NOTIFICATION_EVENT_HOME_SECURITY_TAMPERING_COVERING_REMOVED,
  NOTIFICATION_EVENT_HOME_SECURITY_TAMPERING_INVALID_CODE,
  NOTIFICATION_EVENT_HOME_SECURITY_GLASS_BREAKAGE,
  NOTIFICATION_EVENT_HOME_SECURITY_GLASS_BREAKAGE_UNKNOWN_LOCATION,
  NOTIFICATION_EVENT_HOME_SECURITY_MOTION_DETECTION,
  NOTIFICATION_EVENT_HOME_SECURITY_MOTION_DETECTION_UNKNOWN_LOCATION,
  NOTIFICATION_EVENT_HOME_SECURITY_UNKNOWN_EVENT = 0xFE
}NOTIFICATION_EVENT_HOME_SECURITY;

/**
 * Notification event (8 bit) for notification type NOTIFICATION_TYPE_POWER_MANAGEMENT.
 */
typedef enum
{
  NOTIFICATION_EVENT_POWER_MANAGEMENT_NO_EVENT,
  NOTIFICATION_EVENT_POWER_MANAGEMENT_POWER_HAS_BEEN_APPLIED,
  NOTIFICATION_EVENT_POWER_MANAGEMENT_AC_MAINS_DISCONNECED,
  NOTIFICATION_EVENT_POWER_MANAGEMENT_AC_MAINS_RECONNECED,
  NOTIFICATION_EVENT_POWER_MANAGEMENT_SURGE_DETECTED,
  NOTIFICATION_EVENT_POWER_MANAGEMENT_VOLTAGE_DROP_DRIFT,
  NOTIFICATION_EVENT_POWER_MANAGEMENT_OVERCURRENT_DETECTED,
  NOTIFICATION_EVENT_POWER_MANAGEMENT_OVERVOLTAGE_DETECTION,
  NOTIFICATION_EVENT_POWER_MANAGEMENT_OVERLOADED_DETECTED,
  NOTIFICATION_EVENT_POWER_MANAGEMENT_LOAD_ERROR,
  NOTIFICATION_EVENT_POWER_MANAGEMENT_REPLACE_BATTERY_SOON,
  NOTIFICATION_EVENT_POWER_MANAGEMENT_REPLACE_BATTERY_NOW,
  NOTIFICATION_EVENT_POWER_MANAGEMENT_BATTERY_IS_CHARGING,
  NOTIFICATION_EVENT_POWER_MANAGEMENT_BATTERY_IS_FULLY_CHARGED,
  NOTIFICATION_EVENT_POWER_MANAGEMENT_CHARGE_BATTERY_SOON,
  NOTIFICATION_EVENT_POWER_MANAGEMENT_CHARGE_BATTERY_NOW,
  NOTIFICATION_EVENT_POWER_MANAGEMENT_UNKNOWN_EVENT = 0xFE
}NOTIFICATION_EVENT_POWER_MANAGEMENT;


/**
 * Notification event (8 bit) for notification type NOTIFICATION_TYPE_SMOKE_ALARM.
 */
typedef enum
{
  NOTIFICATION_EVENT_EMERGENCY_ALARM_NO_EVENT,
  NOTIFICATION_EVENT_EMERGENCY_ALARM_CONTACT_POLICE,
  NOTIFICATION_EVENT_EMERGENCY_ALARM_CONTACT_FIRE_SERVICE,
  NOTIFICATION_EVENT_EMERGENCY_ALARM_CONTACT_MEDICAL_SERVICE,
  NOTIFICATION_EVENT_EMERGENCY_UNKNOWN_EVENT = 0xFE
}NOTIFICATION_EVENT_EMERGENCY_ALARM;


/**
 * Notification event (8 bit) for notification type NOTIFICATION_TYPE_SYSTEM.
 */
typedef enum
{
  NOTIFICATION_EVENT_SYSTEM_NO_EVENT,
  NOTIFICATION_EVENT_SYSTEM_HARDWARE_FAILURE,
  NOTIFICATION_EVENT_SYSTEM_SOFTWARE_FAILURE,
  NOTIFICATION_EVENT_SYSTEM_HARDWARE_FAILURE_WITH_MANUFACTURER_PROPRIETARY_FAILURE_CODE,
  NOTIFICATION_EVENT_SYSTEM_SOFTWARE_FAILURE_WITH_MANUFACTURER_PROPRIETARY_FAILURE_CODE,
  NOTIFICATION_EVENT_SYSTEM_UNKNOWN_EVENT = 0xFE
}NOTIFICATION_EVENT_SYSTEM;



/**
 * Notification event (8 bit) for notification type NOTIFICATION_TYPE_SMOKE_ALARM.
 */
typedef enum
{
  NOTIFICATION_EVENT_SMOKE_ALARM_NO_EVENT,
  NOTIFICATION_EVENT_SMOKE_ALARM_SMOKE_DETECTED,
  NOTIFICATION_EVENT_SMOKE_ALARM_SMODE_DETECTED_UNKNOWN_LOCATION,
  NOTIFICATION_EVENT_SMOKE_ALARM_TEST,
  NOTIFICATION_EVENT_SMOKE_ALARM_REPLACEMENT_REQUIRED,
  NOTIFICATION_EVENT_SMOKE_ALARM_UNKNOWN_EVENT = 0xFE
}NOTIFICATION_EVENT_SMOKE_ALARM;

/**
 * Notification status
 */
typedef enum
{
  NOTIFICATION_STATUS_UNSOLICIT_DEACTIVATED = 0x00,
  NOTIFICATION_STATUS_UNSOLICIT_ACTIVATED = 0xFF
} NOTIFICATION_STATUS;

typedef enum
{
  NOTIFICATION_EVENT_HEAT_ALARM_RAPID_TEMPERATURE_RISE_LOCATION_PROVIDED = 0x03,
  NOTIFICATION_EVENT_HEAT_ALARM_RAPID_TEMPERATURE_RISE = 0x04,
  NOTIFICATION_EVENT_HEAT_ALARM_RAPID_TEMPERATURE_FALL_LOCATION_PROVIDED = 0x0C,
  NOTIFICATION_EVENT_HEAT_ALARM_RAPID_TEMPERATURE_FALL= 0x0D,
  NOTIFICATION_EVENT_HEAT_ALARM_UNKNOWN_EVENT = 0xFE
} NOTIFICATION_EVENT_HEAT_ALARM;

/**
 * Struct used to pass operational data to TSE module
 */
typedef struct s_CC_notification_data_t_
{
  RECEIVE_OPTIONS_TYPE_EX rxOptions; /**< rxOptions */
  uint8_t                 index; /// index of notification in notifications array
  uint8_t                *pEventParameters; /// Pointer to event parameters
  uint8_t                 eventParamLength; /// Length of event paramters
} s_CC_notification_data_t;

/**
 * Inits notification module
 * Do not call it directly. Used only by CC_Notification.c
 * @private
 */
extern void notification_init();

/**
 * Resets notification module
 * Do not call it directly. Used only by CC_Notification.c
 * @private
 */
extern void notification_reset();

/**
 * @brief Application specific Notification Set cmd handler.
 * @param[in] notificationType notification type
 * @param[in] notificationStatus notification status of type NOTIFICATION_STATUS
 * @param[in] endpoint is the destination endpoint
 * @return command handler return code
 * @private
 */
extern e_cmd_handler_return_code_t handleAppNotificationSet(
	notification_type_t notificationType,
    NOTIFICATION_STATUS notificationStatus,
    uint8_t endpoint);

/**
 * Fills in Bit Mask with supported Notification Types.
 *
 * Used to prepare data for Notification Supported Report Command
 * as response to Notification Supported Get Command.
 *
 * @param[out] pBitMaskArray The Bit Mask fields describe the supported Notification
 *             Type(s) by the device
 * @param[in] bBitMaskLen The length of the Bit Mask fields
 * @param[in] endpoint is the destination endpoint
 * @return Number of Bit Masks fields (1-31) used, in bytes.
 * @private
 */
extern uint8_t cc_notification_supported_notifications_bitmask(
  uint8_t * pBitMaskArray,
  uint8_t   bBitMaskLen,
  uint8_t endpoint);


/**
 * Fills in Bit Mask with supported events for given notification.
 * Used to prepare data for Event Supported Report Command
 *
 * Finds notification based on {type, endpoint} values
 * an d creates bitmask with supported events. @see cc_notification_config.c
 *
 * @param[in] type Notification type
 * @param[in] endpoint Notification Endpoint
 * @param[out] pBitMaskArray The Bit Mask of supported Events within the requested Notification Type.
 * @return Number of Bit Masks fields (1-31) used in bytes
 * @private
 */
extern uint8_t cc_notification_supported_events_bitmask(
    notification_type_t type,
    uint8_t endpoint,
    uint8_t * pBitMaskArray);

/**
 * Prepares data for Notification Report command as response to
 * Notification Get
 *
 * @param[in,out] type Notification Type
 * @param[in] endpoint Notification endpoint
 * @param[in,out] event If specified, current state of notification
 * @param[out] status Current Notification status - On/Off
 * @return true if notification with {type,endpoint} exists,
 *         false if input data wasn't correct
 * @private
 */
extern bool notification_report_get_data(notification_type_t* type,
                                         uint8_t endpoint,
                                         uint8_t* event,
                                         NOTIFICATION_STATUS* status);

/**
 * Transmits a Notification Report.
 *
 * See SDS11060.doc "Table of defined Notification Types & Events".
 * @param notification_index index of notification to be reported
 *                            in notifications array
 * @param pEvPar List of parameters to be reported
 * @param evParLen Length of event parameters list
 * @param pCallback callback function returning state on job
 * @return JOB_STATUS
 * @private
 */
JOB_STATUS CmdClassNotificationReport(
    uint8_t notification_index,
    uint8_t * pEvPar,
    uint8_t evParLen,
    void(*pCallback)(TRANSMISSION_RESULT * pTransmissionResult));

/**
 * Send report via lifeLine when a change happens.
 *
 * Callback used by TSE module. Refer to @ref ZAF_TSE.h for more details.
 *
 * @param txOptions txOptions
 * @param pData Command payload for the report
 */
void CC_Notification_report_stx(
    TRANSMIT_OPTIONS_TYPE_SINGLE_EX txOptions,
    void* pData);

/**
 * @}
 * @}
 */ 

#endif /*_CC_NOTIFICATION_H_*/
