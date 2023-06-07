/**
 * @file
 *
 * Definitions of events for Wall Controller Certified App.
 *
 * @copyright 2019 Silicon Laboratories Inc.
 */
#ifndef APPS_WALLCONTROLLER_EVENTS_H_
#define APPS_WALLCONTROLLER_EVENTS_H_

#include <ev_man.h>

/**
 * Defines events for the application.
 *
 * These events are not referred to anywhere else than in the application. Hence, they can be
 * altered to suit the application flow.
 *
 * The events are located in a separate file to make it possible to include them in other
 * application files. An example could be a peripheral driver that enqueues an event when something
 * specific happens, e.g. when battery level reach a certain level.
 */
typedef enum EVENT_APP_WALL_CONTROLLER
{
  EVENT_EMPTY = DEFINE_EVENT_APP_NBR,
  EVENT_APP_KEY01_SHORT_PRESS,
  EVENT_APP_KEY01_HOLD,
  EVENT_APP_KEY01_RELEASE,
  EVENT_APP_KEY02_SHORT_PRESS,
  EVENT_APP_KEY02_HOLD,
  EVENT_APP_KEY02_RELEASE,
  EVENT_APP_KEY03_SHORT_PRESS,
  EVENT_APP_KEY03_HOLD,
  EVENT_APP_KEY03_RELEASE,
}
EVENT_APP;

#endif /* APPS_WALLCONTROLLER_EVENTS_H_ */
