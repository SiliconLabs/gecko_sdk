/**
 * @copyright 2021 Silicon Laboratories Inc.
 */
#include "ZAF_CC_Invoker.h"
#include "Assert.h"

#ifdef __APPLE__
extern zaf_cc_config_entry_latest_t __start__zaf_cc_config __asm("section$start$__TEXT$__zaf_cc_config");
extern zaf_cc_config_entry_latest_t __stop__zaf_cc_config __asm("section$end$__TEXT$__zaf_cc_config");
#else
/**
 * This is the first of the registered CC configurations.
 */
extern const zaf_cc_config_entry_latest_t __start__zaf_cc_config;
/**
 * This marks the end of the CC configurations. The element
 * after the last element. This means that this element
 * is not valid.
 */
extern const  zaf_cc_config_entry_latest_t __stop__zaf_cc_config;
#endif

#define cc_config_start __start__zaf_cc_config
#define cc_config_stop __stop__zaf_cc_config

received_frame_status_t ZAF_CC_invoke_specific(CC_handler_map_latest_t const * const p_cc_entry,
                                               cc_handler_input_t *input,
                                               cc_handler_output_t *output)
{
  if (NULL == p_cc_entry->handler) {
    return RECEIVED_FRAME_STATUS_NO_SUPPORT;
  }
  switch (p_cc_entry->handler_api_version) {
    case 1:
    {
      cc_handler_v1_t handler = (cc_handler_v1_t)p_cc_entry->handler;
      return handler(input->rx_options, input->frame, input->length);
    }
    case 2:
    {
      cc_handler_v2_t handler = (cc_handler_v2_t)p_cc_entry->handler;
      return handler(input->rx_options, input->frame, input->length, output->frame, &output->length);
    }
    case 3:
    {
      cc_handler_v3_t handler = (cc_handler_v3_t)p_cc_entry->handler;
      return handler(input, output);
    }
    default:
      // Handler API version is not supported.
      return RECEIVED_FRAME_STATUS_CC_NOT_FOUND;
  }
}

received_frame_status_t invoke_cc_handler(cc_handler_input_t * input,
                                          cc_handler_output_t * output)
{
  CC_handler_map_latest_t const * iter = &cc_handlers_start;
  for ( ; iter < &cc_handlers_stop; ++iter)
  {
    if (iter->CC == input->frame->ZW_Common.cmdClass) {
      return ZAF_CC_invoke_specific(iter, input, output);
    }
  }

  return RECEIVED_FRAME_STATUS_CC_NOT_FOUND;
}

void ZAF_CC_init_specific(uint8_t cmdClass)
{
  CC_handler_map_latest_t const * iter = &cc_handlers_start;
  for ( ; iter < &cc_handlers_stop; ++iter) {
    if ((iter->CC == cmdClass) && (NULL != iter->init)) {
      iter->init();
      break;
    }
  }
}

void ZAF_CC_reset_specific(uint8_t cmdClass)
{
  CC_handler_map_latest_t const * iter = &cc_handlers_start;
  for ( ; iter < &cc_handlers_stop; ++iter) {
    if ((iter->CC == cmdClass) && (NULL != iter->reset)) {
      iter->reset();
      break;
    }
  }
}

void ZAF_CC_foreach(zaf_cc_invoker_callback_t callback, zaf_cc_context_t context)
{
  ASSERT(callback != NULL);
  CC_handler_map_latest_t const * iter = &cc_handlers_start;
  for ( ; iter < &cc_handlers_stop; ++iter)
  {
    if (true == callback(iter, context)) {
      break;
    }
  }
}

size_t ZAF_CC_handler_map_size(void)
{
  return (size_t) ((&cc_handlers_stop) - (&cc_handlers_start));
}

void ZAF_CC_config_foreach(zaf_cc_config_invoker_callback_t callback, void *context)
{
  ASSERT(callback != NULL);
  zaf_cc_config_entry_latest_t const * iter = &cc_config_start;
  for ( ; iter < &cc_config_stop; ++iter)
  {
    if (callback(iter, context)) {
      break;
    }
  }
}

size_t ZAF_CC_config_map_size(void)
{
  return (size_t) ((&cc_config_stop) - (&cc_config_start));
}

/*
 * Make sure at least one entry exists. If zero entries exist, the linking will fail because
 * start and stop variables are not defined.
 */
REGISTER_CC(0xFF, 0xFF, NULL);
ZAF_CC_REGISTER_CONFIG(0xFF, NULL, 0);
