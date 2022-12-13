/**
 * Provides support for BRD8029A (Buttons and LEDs EXP Board)
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef EXTENSION_BOARD_8029A_H
#define EXTENSION_BOARD_8029A_H

#include "em_device.h"

#ifdef ZWAVE_SERIES_800
#if (_SILICON_LABS_32B_SERIES_2_CONFIG == 3)
#include <extension_board_8029a_efr32zg23.h>
#elif (_SILICON_LABS_32B_SERIES_2_CONFIG == 8)
#include "extension_board_8029a_efr32zg28.h"
#else
#error "No valid extension board for selected chip."
#endif
#else
#include <extension_board_8029a_efr32xg13.h>
#endif

#endif /* EXTENSION_BOARD_8029A_H */
