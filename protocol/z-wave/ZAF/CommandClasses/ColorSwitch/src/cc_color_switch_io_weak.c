/**
 * @file
 * Command Class Color Switch I/O handling weak
 * @copyright 2022 Silicon Laboratories Inc.
 */
#include <cc_color_switch_io.h>

//#define DEBUGPRINT
#include "DebugPrint.h"

ZW_WEAK bool
cc_color_switch_write(__attribute__((unused)) uint8_t color_component_id,
                      __attribute__((unused)) s_colorComponent *color_component)
{
  return false;
}

ZW_WEAK bool
cc_color_switch_read( __attribute__((unused)) uint8_t color_component_id,
                      __attribute__((unused)) s_colorComponent *color_component)
{
  return false;
}
