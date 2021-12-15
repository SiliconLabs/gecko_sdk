/**
 * @file
 *
 * Definitions of events for Wall Controller Certified App.
 *
 * @copyright 2019 Silicon Laboratories Inc.
 */
#ifndef APPS_WALLCONTROLLER_EVENTS_H_
#define APPS_WALLCONTROLLER_EVENTS_H_

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
  EVENT_APP_INIT,
  EVENT_APP_LEARN_MODE_FINISH,
  EVENT_APP_REFRESH_MMI,
  EVENT_APP_FLUSHMEM_READY,
  EVENT_APP_NEXT_EVENT_JOB,
  EVENT_APP_FINISH_EVENT_JOB,
  EVENT_APP_TOGGLE_LEARN_MODE,
  EVENT_APP_CC_BASIC_JOB,
  EVENT_APP_CC_SWITCH_MULTILEVEL_JOB,
  EVENT_APP_CENTRAL_SCENE_JOB,
  EVENT_APP_SMARTSTART_IN_PROGRESS,
  EVENT_APP_LEARN_IN_PROGRESS
}
EVENT_APP;

#endif /* APPS_WALLCONTROLLER_EVENTS_H_ */
