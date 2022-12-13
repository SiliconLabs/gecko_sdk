/**
 * @file
 * Platform abstraction for Power Strip application
 * 
 * @copyright 2021 Silicon Laboratories Inc.
 */
#ifndef POWERSTRIP_HW_H_
#define POWERSTRIP_HW_H_

#include <stdbool.h>
#include <CC_MultilevelSwitch_Support.h>

/**
 * Initialize hardware modules specific to Power Strip application.
 */
void PowerStrip_hw_init(void);

#endif /* POWERSTRIP_HW_H_ */
