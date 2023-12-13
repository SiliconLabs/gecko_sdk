/***************************************************************************//**
 * @file
 * @brief ABR file log config
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef ABR_FILE_LOG_CONFIG_H
#define ABR_FILE_LOG_CONFIG_H

#if defined(HOST_TOOLCHAIN) && (ABR_FILE_LOG_ENABLED == 1)

// Defines the maximum number of events that shall be logged
// (Default: 256)
#define ABR_FILE_LOG_CFG_MAX_EVENTS                 256

// Defines the maximum number of steps per event that shall be logged
// by the abr_file_log module (Default: 50)
#define ABR_FILE_LOG_CFG_MAX_STEPS                  50

// Set timestamps as numbers or strings in JSONL (Default: 1)
#define ABR_FILE_LOG_CFG_NUMERIC_TIMESTAMPS          0

// Print string data into the jsonl file in a formatted way
// only for testing purposes. (Default: 0)
#define ABR_FILE_LOG_CFG_FORMATTED_PRINT            0

// cJSON_PrintUnformatted() doesn't add newline symbols to the end of the content
// enabling this flag will add it forcefully.
#define ABR_FILE_LOG_CFG_FORCE_ADD_NEWLINE          1

#if (ABR_FILE_LOG_CFG_FORCE_ADD_NEWLINE == 1)
// Set the newline character that shall be added for the raw content.
#define ABR_FILE_LOG_CFG_NL                         "\n"
#endif

// Should the fprintf wrapper retry on failure or not? (Default: 0)
#define ABR_FILE_LOG_CFG_RETRY_FPRINTF              1

#if (ABR_FILE_LOG_CFG_RETRY_FPRINTF == 1)
// Number of retries (Default: 3)
#define ABR_FILE_LOG_CFG_RETRY_FPRINTF_COUNT        3
#endif

// .jsonl filename (without extension)
// The name of the output .jsonl file without extension
// Default: IQ_report.jsonl
#define ABR_FILE_LOG_CFG_FILENAME                   "abr_report"

// Enable filename measurement type postfixes
// (Default: 1)
#define ABR_FILE_LOG_CFG_MEAS_TYPE_POSTFIX_ENABLE   1

#if (ABR_FILE_LOG_CFG_MEAS_TYPE_POSTFIX_ENABLE == 1)
// RTT or round trip time postfix
#define ABR_FILE_LOG_CFG_RTT_POSTFIX                "_RTT"
// PBR or phase based ranging (formerly RTP) postfix
#define ABR_FILE_LOG_CFG_PBS_POSTFIX                "_PBR"
#endif

// Keep old .jsonl file
// If set the old file will be appended the current time instead of
// overwriting the existing one
#define ABR_FILE_LOG_CFG_KEEP_OLD_FILES             1

#if (ABR_FILE_LOG_CFG_KEEP_OLD_FILES == 1)
// Post fix of the file extension in case old files shall be kept for later use (Default: _bkp)
#define ABR_FILE_LOG_CFG_BACKUP_POSTFIX             "_bkp"
#endif

// Set how many times the logger should display re-occurring critical messages
// e.g. "Logger is not functional!"
#define ABR_FILE_LOG_MAX_CRITICAL_MESSAGE_DISPLAY   5

#endif // defined(HOST_TOOLCHAIN) && (ABR_FILE_LOG_ENABLED == 1)
#endif // ABR_FILE_LOG_CONFIG_H
