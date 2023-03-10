/***************************************************************************//**
 * @file
 * @brief Silicon Labs TrustZone secure MSC service (secure side).
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

#include "sli_tz_service_msc.h"
#include "sli_tz_iovec_check.h"

#include "em_msc.h"

//------------------------------------------------------------------------------
// Function definitions

//-------------------------------------
// Simple services (no IOVEC usage)

uint32_t sli_tz_msc_get_locked(void)
{
  return MSC_LockGetLocked();
}

uint32_t sli_tz_msc_set_locked(void)
{
  MSC_LockSetLocked();
  return SLI_TZ_DISPATCH_UNUSED_RETVAL;
}

uint32_t sli_tz_msc_set_unlocked(void)
{
  MSC_LockSetUnlocked();
  return SLI_TZ_DISPATCH_UNUSED_RETVAL;
}

uint32_t sli_tz_msc_get_readctrl(void)
{
  return MSC_ReadCTRLGet();
}

uint32_t sli_tz_msc_set_readctrl(uint32_t value)
{
  MSC_ReadCTRLSet(value);
  return SLI_TZ_DISPATCH_UNUSED_RETVAL;
}

uint32_t sli_tz_msc_set_pagelock(uint32_t page_number)
{
  MSC_PageLockSetLocked(page_number);
  return SLI_TZ_DISPATCH_UNUSED_RETVAL;
}

uint32_t sli_tz_msc_get_pagelock(uint32_t page_number)
{
  return MSC_PageLockGetLocked(page_number);
}

uint32_t sli_tz_msc_get_userdata_size(void)
{
  return MSC_UserDataGetSize();
}

uint32_t sli_tz_msc_get_misclockword(void)
{
  return MSC_MiscLockWordGet();
}

uint32_t sli_tz_msc_set_misclockword(uint32_t value)
{
  MSC_MiscLockWordSet(value);
  return SLI_TZ_DISPATCH_UNUSED_RETVAL;
}
