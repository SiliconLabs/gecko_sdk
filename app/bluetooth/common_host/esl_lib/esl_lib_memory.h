/***************************************************************************//**
 * @file
 * @brief ESL AP Library - Memory management header
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

#ifndef ESL_LIB_MEMORY_H
#define ESL_LIB_MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include "esl_lib.h"

#ifdef ESL_LIB_MEMORY_LEAK_CHECK
#define esl_lib_memory_allocate(size) _esl_lib_malloc(size, __FILE__, __LINE__)
#define esl_lib_memory_free(ptr) _esl_lib_free(ptr, __FILE__, __LINE__)
// Internal allocator function
void *_esl_lib_malloc(size_t size, const char *file, uint32_t line);
// Internal free function
void _esl_lib_free(void *ptr, const char *file, uint32_t line);

/**************************************************************************//**
 * Log memory items for leak check.
 *****************************************************************************/
void esl_lib_memory_log(void);

/**************************************************************************//**
 * Get total number of allocated memory slots.
 *
 * @return number of allocated memory slots.
 *****************************************************************************/
uint32_t esl_lib_memory_get_count(void);

/**************************************************************************//**
 * Get total size of allocated memory slots.
 *
 * @return Total size of allocated memory slots.
 *****************************************************************************/
size_t esl_lib_memory_get_size(void);

#else // ESL_LIB_MEMORY_LEAK_CHECK

#define esl_lib_memory_allocate(size) malloc(size)
#define esl_lib_memory_free(ptr) free(ptr)
#define esl_lib_memory_log()
#define esl_lib_memory_get_count() 0
#define esl_lib_memory_get_size() 0

#endif // ESL_LIB_MEMORY_LEAK_CHECK

#ifdef __cplusplus
};
#endif

#endif // ESL_LIB_MEMORY_H
