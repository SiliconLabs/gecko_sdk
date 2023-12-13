/***************************************************************************/ /**
 * @file
 * @brief CPC TRACE macros
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

#include <stdio.h>

#if defined(SL_CPC_DEBUG_TRACES)

#define PRINT_INFO(string, ...)  printf("Info : "  string "\n", ##__VA_ARGS__)
#define TRACE_RESET(string, ...) printf("Reset Sequence : "  string "\n", ##__VA_ARGS__)
#define TRACE_CORE(string, ...)  printf("Core : "  string "\n", ##__VA_ARGS__)
#define TRACE_FWU(string, ...)   printf("FWU : " string "\n", ##__VA_ARGS__)
#define TRACE_DRIVER(string, ...) printf("Driver : " string "\n", ##__VA_ARGS__)
#define TRACE_NAKED(string, ...) printf(string, ##__VA_ARGS__)
#define WARN(string, ...)        printf("WARNING : "  string "\n", ##__VA_ARGS__)
#define FATAL(string, ...)                                                                    \
  do {                                                                                        \
    printf("FATAL in file %s at line #%d : " string "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    EFM_ASSERT(false);                                                                        \
  } while (0)
#define BUG(string, ...)                                                                    \
  do {                                                                                      \
    printf("BUG in file %s at line #%d : " string "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    EFM_ASSERT(false);                                                                      \
  } while (0)
#else

#define PRINT_INFO(string, ...)   (void)0
#define TRACE_RESET(string, ...)  (void)0
#define TRACE_CORE(string, ...)   (void)0
#define TRACE_FWU(string, ...)    (void)0
#define WARN(string, ...)         (void)0
#define TRACE_DRIVER(string, ...) (void)0
#define TRACE_NAKED(string, ...)  (void)0
#define FATAL(string, ...)        EFM_ASSERT(false)
#define BUG(string, ...)          EFM_ASSERT(false)

#endif
