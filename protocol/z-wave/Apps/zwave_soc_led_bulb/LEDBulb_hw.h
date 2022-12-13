/**
 * @file
 * Platform abstraction for LED Bulb application
 * 
 * @copyright 2021 Silicon Laboratories Inc.
 */
#ifndef LEDBULB_HW_H_
#define LEDBULB_HW_H_

#include <CC_ColorSwitch.h>
#include <CC_MultilevelSwitch_Support.h>

/**
 * Initialize hardware modules specific to LED Bulb application.
 */
void LEDBulb_hw_init(void);

#endif /* LEDBULB_HW_H_ */
