/***************************************************************************//**
 * @file
 * @brief SystemCall API
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

/***************************************************************************//**
 * @addtogroup systemcalls
 * @details
 *  This module reimplements the syscalls that don't have the definition in the
 *  bare metal project.
 *  This prevents linker warnings.
 * @{
 ******************************************************************************/
#include "cmsis_compiler.h"

struct stat;
struct timeval;
struct timezone;

__WEAK int _close(int file)
{
  (void)file;
  return -1;
}

__WEAK void _exit(int status)
{
  (void)status;

  /* Convince GCC that this function never returns. */
  for (;; ) {
    ;
  }
}

__WEAK int _fstat(int file, struct stat *st)
{
  (void)file;
  (void)(void *)st;
  return 0;
}

__WEAK int _getpid(void)
{
  return 1;
}

__WEAK int _isatty(int file)
{
  (void)file;
  return 1;
}

__WEAK int _kill(int pid, int sig)
{
  (void)pid;
  (void)sig;
  return -1;
}

__WEAK int _lseek(int file, int ptr, int dir)
{
  (void)file;
  (void)ptr;
  (void)dir;
  return 0;
}

__WEAK int _read(int file, char *ptr, int len)
{
  (void)file;
  (void)(void *)ptr;
  (void)len;
  return 0;
}

__WEAK int _write(int file, const char *ptr, int len)
{
  (void)file;
  (void)(const void *)ptr;
  (void)len;
  return 0;
}

__WEAK int _gettimeofday(struct timeval *tv, struct timezone *tz)
{
  (void)(void *)tv;
  (void)(void *)tz;
  return 0;
}
