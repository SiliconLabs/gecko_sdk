/***************************************************************************//**
 * @file
 * @brief This file implements the GPIO monitor for RAILtest applications.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#include <string.h>
#include <stdio.h>
#if !defined(__ICCARM__)
// IAR doesn't have strings.h and puts those declarations in string.h
#include <strings.h>
#endif

#include "em_core.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_gpio.h"
#include "em_ldma.h"
#include "em_prs.h"

#include "dmadrv.h"

#include "hal_common.h"
#include "response_print.h"
#include "buffer_pool_allocator.h"

#include "rail.h"
#include "rail_rf_hal.h"
#include "app_common.h"

// EFR32 Built-in Single Pin Monitor

// This command creates a full logic monitor to monitor a single GPIO pin. The
// final output is two arrays of timestamps, one for rising edges, and one for
// falling edges.

// The timestamping source is based on PROTIMER WRAPCNT ticks. This in a clock
// source that we do not expose to the user, but it is the only fast 32-bit
// timestamp I [MW] could find on-chip. If we could find a different fast 32-bit
// timer to use, then we could make this a public plugin in the UC future.

// This logic monitor consumer a number of resources: Two PRS signals, two
// LDMA channels, two LMDAXBAR request signals, and a GPIO interrupt. The LDMA
// channels will be allocated based on the DMADRV if RAIL_DMA_CHANNEL is
// DMA_CHANNEL_DMADRV, and are otherwise set by the macro logic in the monitor
// init code. The two PRS channels will always be set by the macros below. The
// first two LDMAXBAR signals are always used. The GPIO interrupt will be
// chosen as the pin number that is being monitored.

#define MONITOR_PRS_CH_0     (0U)
#define MONITOR_PRS_CH_1     (1U)

#define MONITOR_NUM_SAMPLES  (50U)
static uint32_t rising[MONITOR_NUM_SAMPLES];
static uint32_t falling[MONITOR_NUM_SAMPLES];

static unsigned int dmaCh0;
static unsigned int dmaCh1;

static bool init = false;

// Set up the monitor. The monitor takes a single GPIO pin and connects it to
// 2 PRS channels. One of the channels is inverted. Those two PRS channels then
// each go to an LDMA via the LDMAXBAR (LDMA crossbar), which causes one
// WRAPCNT sample to be written to the appropriate array per GPIO rising or
// falling edge.
bool initMonitor(uint8_t port, uint8_t pin)
{
  // Enable clocks
  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(cmuClock_PRS, true);
  CMU_ClockEnable(cmuClock_LDMA, true);
#ifdef _CMU_CLKEN0_LDMAXBAR_SHIFT
  CMU_ClockEnable(cmuClock_LDMAXBAR, true);
#endif

  // Reset the buffers from any previous operation. 0xFFFFFFFF is not a valid
  // PROTIMER tick value
  memset(rising, 0xFFU, sizeof(rising));
  memset(falling, 0xFFU, sizeof(falling));

  // Allocate DMA channels based on RAIL_DMA_CHANNEL
#if RAIL_DMA_CHANNEL == DMA_CHANNEL_DMADRV
  Ecode_t dmaError = DMADRV_AllocateChannel(&dmaCh0, NULL);
  // Spin loop forever if we fail
  if (dmaError != ECODE_EMDRV_DMADRV_OK) {
    return false;
  }
  dmaError = DMADRV_AllocateChannel(&dmaCh1, NULL);
  if (dmaError != ECODE_EMDRV_DMADRV_OK) {
    return false;
  }
#elif RAIL_DMA_CHANNEL == DMA_CHANNEL_INVALID
  // If RAIL doesn't use a DMA channel, take the first two
  dmaCh0 = 0U;
  dmaCh1 = 1U;
#else
  // If RAIL does have a channel, take the next two (mod DMA_CHAN_COUNT)
  dmaCh0 = ((RAIL_DMA_CHANNEL + 1U) % DMA_CHAN_COUNT);
  dmaCh1 = ((RAIL_DMA_CHANNEL + 2U) % DMA_CHAN_COUNT);
#endif

  uint32_t ldmaPrsConn0;
  uint32_t ldmaPrsConn1;

#if defined(_SILICON_LABS_32B_SERIES_1)
  // Configure the PRS logic we need on Series 1
  uint32_t source = (pin < 8U)
                    ? PRS_CH_CTRL_SOURCESEL_GPIOL
                    : PRS_CH_CTRL_SOURCESEL_GPIOH;
  // On series-1 devices we could use prsEdgeBoth detection, but keep them on
  // two separate channels to maintain compatibility with series-2
  PRS_SourceSignalSet(MONITOR_PRS_CH_0, source, pin, prsEdgePos);
  PRS_SourceSignalSet(MONITOR_PRS_CH_1, source, pin, prsEdgeNeg);

  PRS->DMAREQ0 = MONITOR_PRS_CH_0;
  PRS->DMAREQ1 = MONITOR_PRS_CH_1;

  ldmaPrsConn0 = ldmaPeripheralSignal_PRS_REQ0;
  ldmaPrsConn1 = ldmaPeripheralSignal_PRS_REQ1;
#elif defined(_SILICON_LABS_32B_SERIES_2)

  // Configure the PRS logic we need on Series 2
  PRS_SourceAsyncSignalSet(MONITOR_PRS_CH_0,
                           PRS_ASYNC_CH_CTRL_SOURCESEL_GPIO,
                           pin);
  PRS_ConnectConsumer(MONITOR_PRS_CH_0, prsTypeAsync, prsConsumerLDMA_REQUEST0);
  PRS_ConnectConsumer(MONITOR_PRS_CH_1, prsTypeAsync, prsConsumerLDMA_REQUEST1);
  PRS_Combine(MONITOR_PRS_CH_1, MONITOR_PRS_CH_0, prsLogic_NOT_B);

  ldmaPrsConn0 = ldmaPeripheralSignal_LDMAXBAR_PRSREQ0;
  ldmaPrsConn1 = ldmaPeripheralSignal_LDMAXBAR_PRSREQ1;
#else
#error "Invalid Platform for GPIO Monitor"
#endif
  // The PRS handles GPIO interrupts, so we need to configure one for
  // channel we're using.
  GPIO_ExtIntConfig((GPIO_Port_TypeDef)port, pin, pin, false, false, false);

  // Connect the DMA channels
  LDMA_Init_t ldmaInit = LDMA_INIT_DEFAULT;
  LDMA_Init(&ldmaInit);
  // There's no SINGLE_P2M_WORD define, so modify a SINGLE_P2M_BYTE descriptor
  LDMA_Descriptor_t descriptor = LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(
    RAIL_TimerTick, &rising[0], MONITOR_NUM_SAMPLES);
  descriptor.xfer.size = ldmaCtrlSizeWord;
  LDMA_TransferCfg_t transfer = LDMA_TRANSFER_CFG_PERIPHERAL(ldmaPrsConn0);
  LDMA_StartTransfer(dmaCh0, &transfer, &descriptor);

  descriptor.xfer.dstAddr = (uint32_t) &falling[0];
  transfer.ldmaReqSel = ldmaPrsConn1;
  LDMA_StartTransfer(dmaCh1, &transfer, &descriptor);

  return true;
}

void printMonitorData(sl_cli_command_arg_t *args)
{
  responsePrintStart(sl_cli_get_command_string(args, 0));
  printf("{Rising:0x%.8lx", rising[0]);
  uint32_t samples = 1U;
  while ((samples < MONITOR_NUM_SAMPLES)
         && (rising[samples] != 0xFFFFFFFFUL)) {
    printf(" 0x%.8lx", rising[samples]);
    samples++;
  }

  // The GPIO may toggle while we're outputting falling samples. In order to
  // keep the data consistent, we need to limit the number of falling samples
  // to the number of rising samples, +1 if a falling sample happened first.
  // Loop over all of the equal samples, in case multiple toggles happened on
  // the same tick
  uint32_t i = 0U;
  if (samples < MONITOR_NUM_SAMPLES) {
    do {
      if (falling[i] < rising[i]) {
        samples++;
        break;
      }
      i++;
    } while (falling[i - 1] == rising[i - 1] && (i < samples));
  }

  printf("}{Falling:0x%.8lx", falling[0]);
  i = 1U;
  while ((i < samples) && falling[i] != 0xFFFFFFFFUL) {
    printf(" 0x%.8lx", falling[i]);
    i++;
  }
  printf("}}\n");
}

void printMonitorHelp(sl_cli_command_arg_t *args)
{
  RAILTEST_PRINTF("\nUse the following commands:\n \
  '%s init' [port pin]- To setup monitor on a GPIO\n \
  '%s get'            - To get GPIO rising and falling edges\n \
  '%s stop'           - To disable\n",                \
                  sl_cli_get_command_string(args, 0), \
                  sl_cli_get_command_string(args, 0), \
                  sl_cli_get_command_string(args, 0));
}

void stopMonitor(void)
{
  // Stop all LDMA transfers and deallocate the channels, but everything else
  // can be left as is. Leave clocks running, in case they are needed elsewhere
  LDMA_StopTransfer(dmaCh0);
  LDMA_StopTransfer(dmaCh1);
#if RAIL_DMA_CHANNEL == DMA_CHANNEL_DMADRV
  DMADRV_FreeChannel(dmaCh0);
  DMADRV_FreeChannel(dmaCh1);
#endif
}

void monitorGpio(sl_cli_command_arg_t *args)
{
  if ((sl_cli_get_argument_count(args) < 1)
      || (strcasecmp(sl_cli_get_argument_string(args, 0), "help") == 0)) {
    printMonitorHelp(args);
    return;
  }

  if (strcasecmp(sl_cli_get_argument_string(args, 0), "init") == 0) {
    if (sl_cli_get_argument_count(args) < 3) {
      responsePrintError(sl_cli_get_command_string(args, 0), 0x53,
                         "Invalid parameters for 'init' - Need GPIO port and pin");
      return;
    }

    init = initMonitor(strtoul(sl_cli_get_argument_string(args, 1), NULL, 0),
                       strtoul(sl_cli_get_argument_string(args, 2), NULL, 0));

    if (init) {
      responsePrint(sl_cli_get_command_string(args, 0), "Status:Initialized");
    } else {
      responsePrintError(sl_cli_get_command_string(args, 0), 0x54,
                         "Error during monitor initialization.");
    }
  } else if (strcasecmp(sl_cli_get_argument_string(args, 0), "get") == 0) {
    if (!init) {
      responsePrintError(sl_cli_get_command_string(args, 0), 0x53,
                         "The monitor is not initialized. Call 'init' before '%s'",
                         sl_cli_get_argument_string(args, 0));
      return;
    }
    printMonitorData(args);
  } else if (strcasecmp(sl_cli_get_argument_string(args, 0), "stop") == 0) {
    if (!init) {
      responsePrintError(sl_cli_get_command_string(args, 0), 0x53,
                         "The monitor is not initialized. Call 'init' before '%s'",
                         sl_cli_get_argument_string(args, 0));
      return;
    }
    stopMonitor();

    init = false;
    responsePrint(sl_cli_get_command_string(args, 0), "Status:Stopped");
  } else {
    responsePrintError(sl_cli_get_command_string(args, 0), 0x53,
                       "%s is invalid option.",
                       sl_cli_get_argument_string(args, 0));
    printMonitorHelp(args);
  }
}
