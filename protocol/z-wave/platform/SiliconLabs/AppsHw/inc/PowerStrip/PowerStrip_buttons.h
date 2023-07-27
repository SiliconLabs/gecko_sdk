/**
 * @file Powerstrip_buttons.h
 * This file contains the declarations of the functions and macros used for handling button events on the power strip.
 *
 * @copyright 2023 Silicon Laboratories Inc.
 */
#ifndef POWERSTRIP_BUTTONS_H
#define POWERSTRIP_BUTTONS_H

#if defined(THUNDERBOARD)
#include "PowerStrip_buttons_thunderboard.h"
#else
#include "PowerStrip_buttons_wstk.h"
#endif

#endif /* POWERSTRIP_BUTTONS_H */
