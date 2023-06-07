/**
 * @file
 *
 * Definitions of events for Multilevel Sensor Certified App.
 *
 * @copyright 2019 Silicon Laboratories Inc.
 */
#ifndef _APPS_MULTILEVELSENSOR_EVENTS_H_
#define _APPS_MULTILEVELSENSOR_EVENTS_H_

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
typedef enum EVENT_APP_MULTILEVELSENSOR
{
  EVENT_EMPTY = DEFINE_EVENT_APP_NBR,
  EVENT_APP_SEND_BATTERY_LEVEL_AND_SENSOR_REPORT,
}
EVENT_APP;

#endif /* _APPS_MULTILEVELSENSOR_EVENTS_H_ */
