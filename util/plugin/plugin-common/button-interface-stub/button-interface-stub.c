//   Copyright 2015 Silicon Laboratories, Inc.                              *80*

#include PLATFORM_HEADER
#include "stack/include/ember-types.h"
#include "event_queue/event-queue.h"

EmberEvent emberAfPluginButtonInterfaceButton0PressedEvent;
EmberEvent emberAfPluginButtonInterfaceButton0ReleasedEvent;
EmberEvent emberAfPluginButtonInterfaceButton1PressedEvent;
EmberEvent emberAfPluginButtonInterfaceButton1ReleasedEvent;
EmberEvent emberAfPluginButtonInterfaceButtonTimeoutEvent;

void emberAfPluginButtonInterfaceButtonTimeoutEventHandler(EmberEvent* event)
{
}

void emberAfPluginButtonInterfaceButton0PressedEventHandler(EmberEvent* event)
{
}

void emberAfPluginButtonInterfaceButton0ReleasedEventHandler(EmberEvent* event)
{
}

void emberAfPluginButtonInterfaceButton1PressedEventHandler(EmberEvent* event)
{
}

void emberAfPluginButtonInterfaceButton1ReleasedEventHandler(EmberEvent* event)
{
}

typedef enum {
  EMBER_AF_BUTTON_INTERFACE_POLARITY_ACTIVE_LO = 0x00,
  EMBER_AF_BUTTON_INTERFACE_POLARITY_ACTIVE_HI = 0x01,
} HalButtonInterfacePolarity;

uint8_t halPluginButtonInterfaceButtonPoll(uint8_t button)
{
}

void halPluginButtonInterfaceSetButtonPolarity(
  uint8_t                    button,
  HalButtonInterfacePolarity polarity)
{
}

void emberAfHalButtonIsrCallback(uint8_t button, uint8_t state)
{
}
