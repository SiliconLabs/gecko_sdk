/**
 * @file
 *
 * Definitions of events for Sensor PIR Certified App.
 *
 * @copyright 2019 Silicon Laboratories Inc.
 */
#ifndef APPS_SENSORPIR_EVENTS_H_
#define APPS_SENSORPIR_EVENTS_H_

#include <ev_man.h>

/**
 * Defines events for the application.
 *
 * These events are not referred to anywhere else than in the application. Hence, they can be
 * altered to suit the application flow.
 *
 * The events are located in a separate file to make it possible to include them in other
 * application files. An example could be a peripheral driver that enqueues an event when something
 * specific happens, e.g. on motion detection.
 */
typedef enum EVENT_APP_SENSOR_PIR
{
  EVENT_EMPTY = DEFINE_EVENT_APP_NBR,
  EVENT_APP_BATTERY_REPORT,
  EVENT_APP_TRANSITION_TO_ACTIVE,
  EVENT_APP_TRANSITION_TO_DEACTIVE,
  /*
   * User-Task related events towards the Main App!
   */
  EVENT_APP_USERTASK_DATA_ACQUISITION_READY,
  EVENT_APP_USERTASK_DATA_ACQUISITION_FINISHED,
}
EVENT_APP;

#endif /* APPS_SENSORPIR_EVENTS_H_ */
