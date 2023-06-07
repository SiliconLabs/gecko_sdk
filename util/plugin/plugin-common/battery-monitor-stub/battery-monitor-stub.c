//   Copyright 2015 Silicon Laboratories, Inc.                              *80*

#include PLATFORM_HEADER
#include "stack/include/ember-types.h"
#include "event_queue/event-queue.h"

// Events
EmberEvent emberAfPluginBatteryMonitorReadADCEvent;

uint16_t halGetBatteryVoltageMilliV(void)
{
  return 0;
}

void halBatteryMonitorInitialize(void)
{
}

void emberAfPluginBatteryMonitorReadADCEventHandler(EmberEvent *event)
{
}

void emberAfPluginBatteryMonitorInitCallback(void)
{
}
