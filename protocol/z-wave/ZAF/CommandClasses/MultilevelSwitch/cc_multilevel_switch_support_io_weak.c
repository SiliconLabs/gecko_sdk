/**
 * @file
 * Command Class Multilevel Switch I/O handling weak
 * @copyright 2022 Silicon Laboratories Inc.
 */
#include <cc_multilevel_switch_support_io.h>

ZW_WEAK bool
cc_multilevel_switch_write(uint8_t multilevel_component_id, cc_multilevel_switch_t *multilevel_switch)
{
  UNUSED(multilevel_component_id);
  UNUSED(multilevel_switch);

  return false;
}

ZW_WEAK bool
cc_multilevel_switch_read(uint8_t multilevel_component_id, cc_multilevel_switch_t *multilevel_switch)
{
  UNUSED(multilevel_component_id);
  UNUSED(multilevel_switch);

  return false;
}
