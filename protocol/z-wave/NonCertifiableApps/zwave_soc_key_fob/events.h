/**
 * @file
 *
 * Definitions of events for the Key Fob App.
 *
 * @copyright 2021 Silicon Laboratories Inc.
 */
#ifndef APPS_KEY_FOB_EVENTS_H_
#define APPS_KEY_FOB_EVENTS_H_

#include <ev_man.h>

/**
 * Defines events for the application.
 *
 * These events are not referred to anywhere else than in the application. Hence, they can be
 * altered to suit the required application flow.
 *
 * The events are located in a separate file to make it possible to include them in other
 * application files. An example could be a peripheral driver that enqueues an event when something
 * specific happens.
 */
typedef enum EVENT_APP_KEY_FOB
{
  EVENT_EMPTY = DEFINE_EVENT_APP_NBR,
  EVENT_APP_FINISH_EVENT,
  EVENT_APP_BASIC_ON,
  EVENT_APP_BASIC_OFF,
  EVENT_APP_ASSOCIATION_GROUP_ADD,
  EVENT_APP_ASSOCIATION_GROUP_ADD_START,
  EVENT_APP_ASSOCIATION_GROUP_REMOVE,
  EVENT_APP_ASSOCIATION_GROUP_REMOVE_START,
  EVENT_APP_INCLUDE_DEVICE,
  EVENT_APP_EXCLUDE_DEVICE,
  EVENT_APP_RESET,
  EVENT_APP_NETWORK_LEARNMODE_NWI,
  EVENT_APP_NETWORK_LEARNMODE_NWE,
} EVENT_APP;

#endif /* APPS_KEY_FOB_EVENTS_H_ */
