/***************************************************************************//**
 * @file
 * @brief ESL Tag CLI interface.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#ifndef ESL_TAG_CLI_TEST_HARNESS_H
#define ESL_TAG_CLI_TEST_HARNESS_H

/***********************************************************************************************//**
 * @addtogroup esl_tag_cli_test_harness
 * @{
 **************************************************************************************************/
#include "sl_cli.h"
#include "esl_tag_log.h"
#include "sl_cli_types.h"

/*******************************************************************************
 ****************************** DEFINITIONS  ***********************************
 ******************************************************************************/
// CLI
#define VA(...) __VA_ARGS__
#define CLI_RESPONSE(...)           sli_bt_esl_logger(ESL_LOG_COMPONENT_CLI, \
                                                      ESL_LOG_LEVEL_INFO,    \
                                                      __VA_ARGS__)
#define CLI_RESPONSE_APPEND(...)    sli_bt_esl_logger((ESL_LOG_COMPONENT_CLI   \
                                                       | ESL_LOG_FLAG_APPEND), \
                                                      ESL_LOG_LEVEL_INFO,      \
                                                      __VA_ARGS__)
#define CLI_RESPONSE_HEADLESS(...)  sli_bt_esl_logger((ESL_LOG_COMPONENT_CLI     \
                                                       | ESL_LOG_FLAG_NOHEADER), \
                                                      ESL_LOG_LEVEL_INFO,        \
                                                      __VA_ARGS__)
#define CLI_OK                      "OK"
#define CLI_ERROR                   "ERROR"

/***************************************************************************//**
 * Init ESL Tag CLI test harness
 ******************************************************************************/
void esl_tag_cli_test_harness_init(void);

/***************************************************************************//**
 * CLI command for reading the ESL Address value
 * @param[in] arguments command line argument list
 ******************************************************************************/
void cli_esl_tag_address_get(sl_cli_command_arg_t *arguments);

/***************************************************************************//**
 * CLI command for reading the ESL Access Point Key value
 * @param[in] arguments command line argument list
 ******************************************************************************/
void cli_esl_tag_ap_key_get(sl_cli_command_arg_t *arguments);

/***************************************************************************//**
 * CLI command for reading the ESL Response Key value
 * @param[in] arguments command line argument list
 ******************************************************************************/
void cli_esl_tag_response_key_get(sl_cli_command_arg_t *arguments);

/***************************************************************************//**
 * CLI command for reading the ESL Absolute Time value
 * @param[in] arguments command line argument list
 ******************************************************************************/
void cli_esl_tag_absolute_time_get(sl_cli_command_arg_t *arguments);

/***************************************************************************//**
 * CLI command for reading the ESL LED Information
 * @param[in] arguments command line argument list
 ******************************************************************************/
void cli_esl_tag_led_info_get(sl_cli_command_arg_t *arguments);

/***************************************************************************//**
 * CLI command for reading the ESL Display Information
 * @param[in] arguments command line argument list
 ******************************************************************************/
void cli_esl_tag_display_info_get(sl_cli_command_arg_t *arguments);

/***************************************************************************//**
 * CLI command for reading the ESL Image Information
 * @param[in] arguments command line argument list
 ******************************************************************************/
void cli_esl_tag_image_info_get(sl_cli_command_arg_t *arguments);

/***************************************************************************//**
 * CLI command for reading the ESL Sensor Information
 * @param[in] arguments command line argument list
 ******************************************************************************/
void cli_esl_tag_sensor_info_get(sl_cli_command_arg_t *arguments);

/***************************************************************************//**
 * CLI command for reading the ESL State Machine status
 * @param[in] arguments command line argument list
 ******************************************************************************/
void cli_esl_tag_status_get(sl_cli_command_arg_t *arguments);

/***************************************************************************//**
 * CLI command for reading the ESL Basic State
 * @param[in] arguments command line argument list
 ******************************************************************************/
void cli_esl_tag_basic_state_get(sl_cli_command_arg_t *arguments);

/***************************************************************************//**
 * CLI command for writing the ESL Basic State Service Needed flag
 * @param[in] arguments command line argument list
 ******************************************************************************/
void cli_esl_tag_service_needed_set(sl_cli_command_arg_t *arguments);

/***************************************************************************//**
 * CLI command for enabling ESL advertising
 * @param[in] arguments command line argument list
 ******************************************************************************/
void cli_esl_tag_advertising_set(sl_cli_command_arg_t *arguments);

/***************************************************************************//**
 * CLI command for setting static image data
 * @param[in] arguments command line argument list
 ******************************************************************************/
void cli_esl_tag_image_set(sl_cli_command_arg_t *arguments);

/***************************************************************************//**
 * CLI command for restart the ESL Tag
 * @param[in] arguments command line argument list
 ******************************************************************************/
void cli_esl_tag_restart(sl_cli_command_arg_t *arguments);

/** @} (end addtogroup esl_tag_cli_test_harness) */
#endif // ESL_TAG_CLI_TEST_HARNESS_H
