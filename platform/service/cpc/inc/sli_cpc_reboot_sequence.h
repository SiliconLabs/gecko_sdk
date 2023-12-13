/***************************************************************************/ /**
 * @file
 * @brief CPC Reboot sequence
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

#include <stdbool.h>

/***************************************************************************/ /**
 * Returns the state of the reset bootloader sequence
 *
 * @return Whether the secondary has rebooted in bootloader mode or not
 ******************************************************************************/
bool sli_cpc_reboot_is_bootloader_sequence_done(void);

/***************************************************************************/ /**
 * The bare metal process action function.
 *
 * @param[in] firmware_reset_mode  if the reset sequence should trap into bootloader
 ******************************************************************************/
void sli_cpc_reboot_sequence_process(void);

/***************************************************************************/ /**
 * The bare metal process action function for the reboot into bootloader mode.
 ******************************************************************************/
void sli_cpc_reboot_bootloader_sequence_process(void);

/***************************************************************************/ /**
 * Returns whether or not a gecko bootloader suitable for firmware upgrade is present
 *
 * @return gecko bootloader is present
 ******************************************************************************/
bool sli_cpc_is_gecko_bootloader_present(void);

/***************************************************************************/ /**
 * Reset state machine of the reboot sequence to re-run it
 ******************************************************************************/
void sli_cpc_reboot_sequence_start(void);
