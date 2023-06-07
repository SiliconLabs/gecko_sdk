/***************************************************************************//**
 * @brief schedulable events
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

// Originally I used a heap (complete binary tree stored in an array)
// for the scheduled events.  This took O(log(N)) time for adding an
// event or for removing the next event.  The simple list version here
// takes O(N) time for adding an event O(1) time for removing the next
// one.  It is faster for small numbers of events, because it is much
// simpler, but does poorly as the number of events goes up.
// Measurements showed that the crossover point is somewhere above 100
// scheduled events, which we should never reach.  So the simpler
// version is the way to go.
//
// If more speed is needed, the first step would be to add a pointer
// to the halfway point in the list.  This would cut the lookup time
// almost in half without adding much complexity.

#include "stack/include/ember.h"
#include "hal/hal.h"
#include "event-queue.h"

#ifdef EMBER_TEST
#include <stdio.h>       // for fprintf
#endif

// We use this instead of NULL at the end of a list so that unscheduled
// events can be marked by having a 'next' field of NULL.  This makes them
// easier to initialize.
#define LIST_END ((Event *) 1)

// Marker function for ISR event types.  This should never be called.
void emIsrEventMarker(struct Event_s *event)
{
  (void)event;

  assert(false);
}

void emInitializeEventQueue(EventQueue *queue)
{
  queue->isrEvents = NULL;
  queue->events = LIST_END;
}

static void cancelEvents(Event *events)
{
  while (events != LIST_END) {
    Event *temp = events->next;
    events->next = NULL;
    events = temp;
  }
}

void emberCancelAllEvents(EventQueue *queue)
{
  while (true) {
    Event *events = LIST_END;
    ATOMIC(
      if (queue->isrEvents != NULL) {
      events = queue->isrEvents->next;
      queue->isrEvents->next = LIST_END;
      queue->isrEvents = NULL;
    }
      );
    if (events == LIST_END) {
      break;
    }
    cancelEvents(events);
  }
  cancelEvents(queue->events);
  queue->events = LIST_END;
}

#ifdef EMBER_TEST
static void printEvents(Event *events, bool *firstLoc)
{
  for (; events != LIST_END; events = events->next) {
    fprintf(stderr, "%s%s: %d",
            *firstLoc ? "[" : " | ",
            (events->actions->name == NULL
             ? "?"
             : events->actions->name),
            events->timeToExecute);
    *firstLoc = false;
  }
}

// This is not thread safe.
// Test only function, compiled only with gcc so the attribute is ok
__attribute__((unused)) static void printEventQueue(EventQueue *queue)
{
  bool first = true;
  Event *isrEnd = queue->isrEvents;
  if (isrEnd != NULL) {
    Event *isrStart = isrEnd->next;
    isrEnd->next = LIST_END;
    printEvents(isrStart, &first);
    isrEnd->next = isrStart;
  }
  printEvents(queue->events, &first);
  if (first) {
    fprintf(stderr, "[]\n");
  }
}
#endif // ifdef EMBER_TEST

bool emberEventIsScheduled(Event *event)
{
  return event->next != NULL;
}

uint32_t emberEventGetRemainingMs(Event *event)
{
  if (event->next == NULL) {
    return -1;
  } else if (event->actions->marker == emIsrEventMarker) {
    return 0;
  } else {
    uint32_t remaining =
      event->timeToExecute - halCommonGetInt32uMillisecondTick();
    if (remaining < HALF_MAX_INT32U_VALUE) {
      return remaining;
    } else {
      return 0;         // we're behind in running the event
    }
  }
}

static void adjustListLocation(EventQueue *queue, Event *event, bool keep)
{
  Event *previous = (Event *) queue;
  Event *finger = queue->events;
  Event *newLocation = NULL;
  assert(event->next != event);

  // Find 'event' in the list, noting the new location if we come across it.
  while (finger != event) {
    if (keep
        && newLocation == NULL
        && !timeGTorEqualInt32u(event->timeToExecute, finger->timeToExecute)) {
      newLocation = previous;
    }
    previous = finger;
    finger = finger->next;
  }

  // Remove 'event' from its current location.
  if (previous == (Event *) queue) {
    queue->events = event->next;
  } else {
    previous->next = event->next;
  }

  if (keep) {
    // If we haven't found the new location it must be after the old
    // location, so we have to keep looking for it.
    if (newLocation == NULL) {
      newLocation = previous;
      finger = event->next;
      assert(event->next != event);
      while (finger != LIST_END
             && timeGTorEqualInt32u(event->timeToExecute,
                                    finger->timeToExecute)) {
        newLocation = finger;
        finger = finger->next;
      }
    }

    // Put 'event' in its new location.
    if (newLocation == (Event *) queue) {
      event->next = queue->events;
      queue->events = event;
    } else {
      event->next = newLocation->next;
      newLocation->next = event;
    }
  }
}

uint32_t emberMsToNextQueueEvent(EventQueue *queue)
{
  if (queue->isrEvents != NULL) {
    return 0;
  } else if (queue->events == LIST_END) {
    return -1;
  } else {
    return emberEventGetRemainingMs(queue->events);
  }
}

void emberRunEventQueue(EventQueue *queue)
{
  uint32_t now = halCommonGetInt32uMillisecondTick();
  while (true) {
    Event *event = LIST_END;
    ATOMIC(
      if (queue->isrEvents != NULL) {
      event = queue->isrEvents->next;
      if (event->next == event) {
        queue->isrEvents = NULL;
      } else {
        queue->isrEvents->next = event->next;
      }
      event->next = NULL;
    } else if (queue->events != LIST_END
               && timeGTorEqualInt32u(now, queue->events->timeToExecute)) {
      event = queue->events;
      queue->events = event->next;
      event->next = NULL;
    }
      )
    if (event == LIST_END) {
      break;
    } else {
      event->actions->handler(event);
    }
  }
}

// Mark any of the events that are also buffers, and call any marker actions.

extern void sli_legacy_buffer_manager_mark_buffer_pointer(void **pointerLoc);

void emberMarkEventQueue(EventQueue *queue)
{
  Event **location = &queue->events;
  while (*location != LIST_END) {
    Event *event = *location;
    sli_legacy_buffer_manager_mark_buffer_pointer((void **) location);
    location = &event->next;
    if (event->actions->marker != NULL) {
      event->actions->marker(event);
    }
  }
}

// If the event is ready to run, and the new time doesn't change this,
// then just leave the event where it is.  This is done to avoid shuffling
// events when setActive() is called multiple times on the same event.

void emberEventSetDelayMs(Event *event, uint32_t delay)
{
  EventQueue *queue = event->actions->queue;
  if (event->actions->marker == emIsrEventMarker) {
    assert(delay == 0);
    ATOMIC(
      if (event->next != NULL) {
      // already scheduled, do nothing
    } else if (queue->isrEvents == NULL) {
      event->next = event;
      queue->isrEvents = event;
    } else {
      event->next = queue->isrEvents->next;
      queue->isrEvents->next = event;
      queue->isrEvents = event;
    }
      );
    // Issue a callback to the application so that it knows that an event has
    // happened in ISR context and we should recompute delay times.
    // emApiEventDelayUpdatedFromIsrHandler(event);
  } else {
    uint32_t now = halCommonGetInt32uMillisecondTick();
    uint32_t timeToExecute = now + (delay < EMBER_MAX_EVENT_DELAY_MS
                                    ? delay
                                    : EMBER_MAX_EVENT_DELAY_MS);
    if (emberEventIsScheduled(event)) {
      if (timeToExecute == event->timeToExecute
          || (delay == 0
              && timeGTorEqualInt32u(now, event->timeToExecute))) {
        return;           // avoid unnecessary shuffling of events
      }
    } else {
      event->next = queue->events;
      queue->events = event;
    }
    event->timeToExecute = timeToExecute;
    adjustListLocation(queue, event, true);
  }
}

void emberEventSetInactive(Event *event)
{
  EventQueue *queue = event->actions->queue;
  if (event->actions->marker == emIsrEventMarker) {
    ATOMIC(
      if (event->next == NULL) {
      // do nothing
    } else if (event->next == event) {
      // only event in the queue
      queue->isrEvents = NULL;
      event->next = NULL;
    } else {
      Event *previous = event->next;
      while (previous->next != event) {
        previous = previous->next;
      }
      if (queue->isrEvents == event) {
        queue->isrEvents = previous;
      }
      previous->next = event->next;
      event->next = NULL;
    }
      );
  } else if (emberEventIsScheduled(event)) {
    EventQueue *queue = event->actions->queue;
    adjustListLocation(queue, event, false);
    event->next = NULL;
  }
}

Event *emFindEvents(EventQueue *queue,
                    EventActions *actions,
                    EventPredicate predicate,
                    void *data,
                    bool all)
{
  Event *previous = (Event *) queue;    // any non-NULL, non-Event value works
  Event *finger = queue->events;
  Event *result = NULL;

  while (finger != LIST_END) {
    Event *next = finger->next;
    if (finger->actions == actions
        && (predicate == NULL
            || predicate(finger, data))) {
      if (previous == (Event *) queue) {
        queue->events = next;
      } else {
        previous->next = next;
      }
      finger->next = result;
      if (!all) {
        return finger;
      }
      result = finger;
    } else {
      previous = finger;
    }
    finger = next;
  }
  return result;
}
