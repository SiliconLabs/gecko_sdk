//   Copyright 2015 Silicon Laboratories, Inc.                              *80*

#include PLATFORM_HEADER
#include "stack/include/ember-types.h"
#include "event_queue/event-queue.h"

EmberEvent emberAfPluginGpioSensorInterruptEvent;
EmberEvent emberAfPluginGpioSensorDebounceEvent;

void emberAfPluginGpioSensorInterruptEventHandler(EmberEvent* event)
{
}

void emberAfPluginGpioSensorDebounceEventHandler(EmberEvent* event)
{
}

typedef enum {
  HAL_GPIO_SENSOR_ACTIVE = 0x01,
  HAL_GPIO_SENSOR_NOT_ACTIVE = 0x00,
} HalGpioSensorState;

void halGpioSensorInitialize(void)
{
}

HalGpioSensorState halGpioSensorGetSensorValue(void)
{
  return HAL_GPIO_SENSOR_ACTIVE;
}

void emberAfPluginGpioSensorInitCallback(void)
{
}
