/***************************************************************************//**
 * @file
 * @brief OS dependent sleep functionality.
 *******************************************************************************
 * # License
 * <b>Copyright 2024 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "app_sleep.h"

#if defined(POSIX)
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/errno.h>
#elif defined(_WIN32)
#include <windows.h>
#endif

#if defined(POSIX)
// POSIX compliant
void app_sleep_us(uint64_t usec)
{
  struct timeval tv;
  int ret = -1;

  tv.tv_sec = usec / 1000000;
  tv.tv_usec = usec % 1000000;

  do {
    // using select() instead of usleep(usec) results in better precision and slightly lower overall CPU usage as well
    ret = select(1, NULL, NULL, NULL, &tv);
  } while ((ret == -1) && (errno == EINTR)); // select can be interruped by SIGALRM
}
#elif defined(_WIN32)
static NTSTATUS(__stdcall * NtDelayExecution)(BOOL Alertable, PLARGE_INTEGER DelayInterval) = NULL;
static NTSTATUS(__stdcall * ZwSetTimerResolution)(IN ULONG RequestedResolution, IN BOOLEAN Set, OUT PULONG ActualResolution) = NULL;

void app_sleep_us(uint64_t usec)
{
  static BOOL lazy_init = TRUE; // need to get some function pointers and set timer resolution before the first use
  LARGE_INTEGER interval;

  if (lazy_init) {
    ULONG actualResolution;
    // import two ntdll functions which are needed
    ZwSetTimerResolution = (NTSTATUS(__stdcall*)(ULONG, BOOLEAN, PULONG))GetProcAddress(GetModuleHandle("ntdll.dll"), "ZwSetTimerResolution");
    NtDelayExecution = (NTSTATUS(__stdcall*)(BOOL, PLARGE_INTEGER))GetProcAddress(GetModuleHandle("ntdll.dll"), "NtDelayExecution");
    // set high resolution
    ZwSetTimerResolution(1, TRUE, &actualResolution);
    lazy_init = FALSE;
  }

  interval.QuadPart = -1 * (int)(usec * 10);
  NtDelayExecution(FALSE, &interval);
}
#endif
