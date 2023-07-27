/**
 * @file wallcontroller_buttons.h
 * This file contains the declarations of the functions and macros used for handling button events on the wall controller.
 *
 * @copyright 2023 Silicon Laboratories Inc.
 */
#ifndef WALLCONTROLLER_BUTTONS_H
#define WALLCONTROLLER_BUTTONS_H

#if defined(THUNDERBOARD)
#include "wallcontroller_buttons_thunderboard.h"
#else
#include "wallcontroller_buttons_wstk.h"
#endif

#endif /* WALLCONTROLLER_BUTTONS_H */
