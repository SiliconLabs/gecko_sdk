/**
 * @file
 *
 * Invokes a CC handler based on the first byte (CC) in a given frame.
 *
 * @copyright 2021 Silicon Laboratories Inc.
 */

#ifndef ZAF_CC_INVOKER_H_
#define ZAF_CC_INVOKER_H_

#include "ZAF_types.h"
#include "ZW_classcmd.h"

/**
 *
 * @addtogroup ZAF
 * @{
 * @addtogroup CC_Invoker
 * @{
 */

/**
 * Invokes the handler with the correct arguments for a given command class entry.
 *
 * Command class handlers can be implemented in different versions having different parameters.
 * This function will invoke the handler with the correct set of arguments based on the handler
 * version.
 *
 * @param[in] p_cc_entry  Pointer to command class entry.
 * @param[in] input       Input data. See @ref cc_handler_input_t for details
 * @param[out] output     Output data. See @ref cc_handler_output_t for details
 *
 * @return Returns RECEIVED_FRAME_STATUS_CC_NOT_FOUND if the handler version is not supported.
 *         Otherwise, the return value from the handler is passed through.
 */
received_frame_status_t ZAF_CC_invoke_specific(
    CC_handler_map_latest_t const * const p_cc_entry,
    cc_handler_input_t *input,
    cc_handler_output_t *output);

/**
 * Invokes a handler based on the command class in the given frame.
 *
 * This function is effectively a wrapper of ZAF_CC_invoke_specific() since it finds the
 * corresponding CC entry and invokes ZAF_CC_invoke_specific().
 *
 * @param[in] input       Input data. See @ref cc_handler_input_t for details
 * @param[out] output     Output data. See @ref cc_handler_output_t for details
 *
 * @return Returns RECEIVED_FRAME_STATUS_CC_NOT_FOUND if the CC entry is not found or of the
 *         handler version is not supported.
 *         Otherwise, the return value from the handler is passed through.
 */
received_frame_status_t invoke_cc_handler(cc_handler_input_t * input,
                                          cc_handler_output_t * output);

/**
 * Initializes a specific command class.
 * 
 * @param cmdClass The CC to initialize
 */
void ZAF_CC_init_specific(uint8_t cmdClass);

/**
 * Resets specific command class.
 *
 * @param cmdClass The CC to reset
 */
void ZAF_CC_reset_specific(uint8_t cmdClass);

typedef void * zaf_cc_context_t;

/**
 * Callback type for ZAF_CC_foreach().
 *
 * The CC handler map must always be the latest available version.
 */
typedef bool (*zaf_cc_invoker_callback_t)(CC_handler_map_latest_t const * const p_cc_entry, zaf_cc_context_t context);

/**
 * Callback type for ZAF_CC_config_foreach().
 *
 * The CC handler map must always be the latest available version.
 */
typedef bool (*zaf_cc_config_invoker_callback_t)(zaf_cc_config_entry_latest_t const * const p_cc_config_entry, void *context);

/**
 * Invokes callback for each registered CC.
 *
 * Will stop if the callback returns true.
 *
 * @param callback Callback function to invoke.
 * @param context Context to pass on to the callback function.
 */
void ZAF_CC_foreach(zaf_cc_invoker_callback_t callback, zaf_cc_context_t context);

/**
 * Returns the size of the handler map
 * 
 * @return size_t Handler map size
 */
size_t ZAF_CC_handler_map_size(void);

/**
 * Invokes callback for each registered CC configuration.
 *
 * Will stop if the callback returns true.
 * 
 * @param callback Callback function to invoke.
 * @param context Context to pass on to the callback function.
 */
void ZAF_CC_config_foreach(zaf_cc_config_invoker_callback_t callback, void *context);

/**
 * Returns the size of the config entry
 * 
 * @return size_t Config entry size
 */
size_t ZAF_CC_config_entry_size(void);

/**
 * @} // CC_Invoker
 * @} // ZAF
 */


#endif /* ZAF_CC_INVOKER_H_ */
