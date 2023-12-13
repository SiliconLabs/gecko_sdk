/***************************************************************************//**
 * @file
 * @brief GCC startup file
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

/* The startup files contain a stack and heap symbol in addition
 * to the vector table. The size of these internal stack and heap
 * objects depend on the build system providing two macros on the
 * commandline called __STACK_SIZE and __HEAP_SIZE.
 *
 * We provide alternative stack and heap symbols in the sl_memory.c
 * file which can be configured in a separate config file. Go to
 * sl_memory_config.h to configure the stack and heap size. */
#define __STACK_SIZE    0x0
#define __HEAP_SIZE     0x0
