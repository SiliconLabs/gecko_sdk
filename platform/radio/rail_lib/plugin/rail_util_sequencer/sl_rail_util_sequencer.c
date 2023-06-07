/***************************************************************************//**
 * @file
 * @brief
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
#include "sl_rail_util_sequencer_config.h"
#include "rail.h"

#if !SL_RAIL_UTIL_SEQUENCER_RUNTIME_IMAGE_SELECTION \
  && defined(SL_RAIL_UTIL_SEQUENCER_IMAGE)
RAIL_Status_t RAILCb_RadioSequencerImageLoad(void)
{
#if SL_RAIL_UTIL_SEQUENCER_IMAGE == RAIL_SEQ_IMAGE_1
  return RAIL_LoadSequencerImage1(RAIL_EFR32_HANDLE);
#elif SL_RAIL_UTIL_SEQUENCER_IMAGE == RAIL_SEQ_IMAGE_2
  return RAIL_LoadSequencerImage2(RAIL_EFR32_HANDLE);
#else
  #error "Must choose a valid sequencer image!"
#endif
}
#endif
