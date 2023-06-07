/***************************************************************************//**
 * @file
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "em_device.h"
#include "em_chip.h"
#if defined(_EMU_DCDCCTRL_MASK)
#include "em_emu.h"
#include "bspconfig.h"
#endif
#include "cslib.h"
#include "device_init.h"
#include "comm_routines.h"

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
#if defined(_EMU_DCDCCTRL_MASK)
  EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_WSTK_DEFAULT;
#endif

  CHIP_Init();

#if defined(_EMU_DCDCCTRL_MASK)
  /* Init DCDC regulator with kit specific parameters. */
  EMU_DCDCInit(&dcdcInit);
#endif

  systemInit();

  CSLIB_commInit();

  CSLIB_initHardware();
  CSLIB_initLibrary();

  // Infinite loop
  while (1) {
    CSLIB_update();
    CSLIB_commUpdate();
    CSLIB_lowPowerUpdate();
  }
}
