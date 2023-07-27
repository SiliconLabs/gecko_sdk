/***************************************************************************//**
 * @file
 * @brief E-paper display low level driver API for Pervasive Displays products.
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

#include "spidrv.h"
#include "tempdrv.h"
#include "sl_udelay.h"
#include "sl_sleeptimer.h"
#include "esl_tag_log.h"
#include "esl_tag_image_core.h"
#include "esl_tag_display_core.h"
#include "esl_tag_pd_epd_driver.h"
#include "sl_spidrv_exp_epd_config.h"
#include "esl_tag_pd_epd_interface.h"

enum pd_epd_states {
  PD_EPD_READY,
  PD_EPD_INIT,
  PD_EPD_WRITE_BLACK,
  PD_EPD_WRITE_COLOR,
  PD_EPD_POWER_ON,
  PD_EPD_REFRESH,
  PD_EPD_DCDC,
  PD_EPD_DEINIT,
};

static enum pd_epd_states pd_epd_machine = PD_EPD_READY;

extern SPIDRV_Handle_t sl_spidrv_exp_epd_handle;
extern void esl_pd_epd_display_power_save(void);

// Bytes to read from NVM and write to EPD
#define PD_EPD_WRITE_BUF_SIZE PD_EPD_DISPLAY_HEIGHT
#define SECTION_MAX           ((PD_EPD_DISPLAY_WIDTH * PD_EPD_DISPLAY_HEIGHT) \
                               / (8 * PD_EPD_WRITE_BUF_SIZE))

/* ************************************************************************** */
/* *** PD_EPD functions ***************************************************** */
/* ************************************************************************** */

sl_status_t pd_epd_update_image(uint8_t display_index, uint8_t image_index)
{
  sl_status_t report_status = SL_STATUS_IN_PROGRESS;
  static uint16_t section = 0;
  static uint16_t offset  = 0;
  static uint16_t last_image = ESL_IMAGE_OBJECT_BASE;
  size_t len = 1;
  uint8_t buffer[PD_EPD_WRITE_BUF_SIZE];
  uint8_t reg;

  // This driver example is not able to handle more than one display!
  (void)display_index;

  switch (pd_epd_machine) {
    case PD_EPD_READY:
      // Check if image is available at requested slot
      report_status = esl_image_get_data(image_index,
                                         &offset,
                                         0,
                                         buffer);

      if (report_status == SL_STATUS_OK) {
        // Start actual image transfer on next call only if image exists
        pd_epd_machine = PD_EPD_INIT;
        last_image = (uint16_t)image_index;
        report_status = SL_STATUS_IN_PROGRESS;
      }
      break;

    case PD_EPD_INIT:
      report_status = pd_epd_init();

      if (report_status != SL_STATUS_OK) {
        // This is a serious error condition, set service needed flag to indicate
        esl_core_set_basic_state_bit(ESL_BASIC_STATE_SERVICE_NEEDED_BIT, ESL_TRUE);
        pd_epd_machine = PD_EPD_DEINIT;
      } else {
        pd_epd_machine = PD_EPD_WRITE_BLACK;
        section = 0;
        offset  = 0;
        report_status = SL_STATUS_IN_PROGRESS;
      }
      break;

    case PD_EPD_WRITE_BLACK: {
      reg = section == 0 ? PD_REG_BLACK_BUFFER : PD_REG_NOP;
      len = PD_EPD_WRITE_BUF_SIZE;

      if (section < SECTION_MAX) {
        report_status = esl_image_get_data((uint8_t)last_image,
                                           &offset,
                                           sizeof(buffer),
                                           buffer);

        if (report_status == SL_STATUS_OK) {
          pd_epd_write_data(&reg, buffer, len);
          section++;
          report_status = SL_STATUS_IN_PROGRESS;
        } else {
          pd_epd_machine = PD_EPD_DEINIT;
        }
      } else {
        pd_epd_machine = PD_EPD_WRITE_COLOR;
        section = 0;
      }
    } break;

    case PD_EPD_WRITE_COLOR: {
      reg = section == 0 ? PD_REG_RED_BUFFER : PD_REG_NOP;
      len = PD_EPD_WRITE_BUF_SIZE;

      if (section < SECTION_MAX) {
        // get data if color
        //if mono buffer = 0
      #if (PD_EPD_DISPLAY_COLOR_TYPE == PD_EPD_SPECTRA)
        report_status = esl_image_get_data((uint8_t)last_image,
                                           &offset,
                                           sizeof(buffer),
                                           buffer);
      #else
        report_status = SL_STATUS_OK;
        memset(buffer, 0, sizeof(buffer));
      #endif

        if (report_status == SL_STATUS_OK) {
          pd_epd_write_data(&reg, buffer, len);
          section++;
          report_status = SL_STATUS_IN_PROGRESS;
        } else {
          pd_epd_machine = PD_EPD_DEINIT;
        }
      } else {
        reg = PD_REG_POWER_ON;
        len = 1;
        buffer[0] = 0;
        pd_epd_write_data(&reg, buffer, len);
        pd_epd_machine = PD_EPD_POWER_ON;
        esl_pd_epd_display_power_save();
        section = 1; // Use the counter for HW error detection from this point on
      }
    } break;

    case PD_EPD_POWER_ON:
      if (GPIO_PinInGet(PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_PORT, PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_PIN) == PD_EPD_GPIO_LEVEL_HIGH) {
        reg = PD_REG_DISPLAY_REFRESH;
        buffer[0] = 0;
        pd_epd_write_data(&reg, buffer, len);
        pd_epd_machine = PD_EPD_REFRESH;
      } else {
        section++; // Count how many times we're waiting, timeout after 255 cycles
      }
      break;

    case PD_EPD_REFRESH:
      if (GPIO_PinInGet(PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_PORT, PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_PIN) == PD_EPD_GPIO_LEVEL_HIGH) {
        reg = PD_REG_DCDC;
        buffer[0] = 0;
        pd_epd_write_data(&reg, buffer, len);
        pd_epd_machine = PD_EPD_DCDC;
      } else {
        section++;
      }
      break;

    case PD_EPD_DCDC:
      if (GPIO_PinInGet(PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_PORT, PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_PIN) == PD_EPD_GPIO_LEVEL_HIGH) {
        pd_epd_machine = PD_EPD_DEINIT;
        // Reaching here means everything went OK, the image is now displayed
        report_status = SL_STATUS_OK;
      } else {
        section++;
      }
      break;

    default:
      break;
  }

  // Check for hardware error conditions before leave. Timeout will happen after
  // about 1 min. with default polling speed, see ESL_EPD_DISPLAY_TIMER_SLOW
  if (pd_epd_machine >= PD_EPD_POWER_ON && !(uint8_t)section) {
    report_status = SL_STATUS_ABORT;
    // Report HW error condition via Service Needed Flag
    esl_core_set_basic_state_bit(ESL_BASIC_STATE_SERVICE_NEEDED_BIT, ESL_TRUE);
    pd_epd_machine = PD_EPD_DEINIT;
  }

  // Handle PD_EPD_DEINIT state outside of the switch-case allows to do de-init
  // immediately whenever an error occurs.
  if (pd_epd_machine == PD_EPD_DEINIT) {
    GPIO_PinOutClear(PD_EPD_DRIVER_DATA_CONTROL_PORT, PD_EPD_DRIVER_DATA_CONTROL_PIN);
    GPIO_PinOutClear(PD_EPD_DRIVER_CHIP_SELECT_PORT, PD_EPD_DRIVER_CHIP_SELECT_PIN);
    pd_epd_deinit_GPIOs();
    pd_epd_machine = PD_EPD_READY;
    // Set report status to OK in any step will end the process immediately
  }

  return report_status;
}

sl_status_t pd_epd_write_data(const uint8_t *reg, const uint8_t *data, uint32_t len)
{
  Ecode_t SPI_status = 0;

  if (*reg != PD_REG_NOP) {
    // PD_DC low --> command/reg
    GPIO_PinOutClear(PD_EPD_DRIVER_DATA_CONTROL_PORT, PD_EPD_DRIVER_DATA_CONTROL_PIN);

    // PD_CS low
    GPIO_PinOutClear(PD_EPD_DRIVER_CHIP_SELECT_PORT, PD_EPD_DRIVER_CHIP_SELECT_PIN);

    // SPI write reg
    SPI_status |= SPIDRV_MTransmitB(sl_spidrv_exp_epd_handle, reg, 1);

    // PD_CS high
    GPIO_PinOutSet(PD_EPD_DRIVER_CHIP_SELECT_PORT, PD_EPD_DRIVER_CHIP_SELECT_PIN);

    // PD_DC high --> data
    GPIO_PinOutSet(PD_EPD_DRIVER_DATA_CONTROL_PORT, PD_EPD_DRIVER_DATA_CONTROL_PIN);
  }

  for (uint32_t i = 0; i < len; i++) {
    // PD_CS low
    GPIO_PinOutClear(PD_EPD_DRIVER_CHIP_SELECT_PORT, PD_EPD_DRIVER_CHIP_SELECT_PIN);

    // SPI write data[i]
    // if data is NULL pointer then 0 (nullára mutató pointer) instead of &data[i]
    SPI_status |= SPIDRV_MTransmitB(sl_spidrv_exp_epd_handle, &data[i], 1);

    // PD_CS high
    GPIO_PinOutSet(PD_EPD_DRIVER_CHIP_SELECT_PORT, PD_EPD_DRIVER_CHIP_SELECT_PIN);
  }

  // Use specific SL_STATUS_xxx values
  if (ECODE_OK == SPI_status) {
    return SL_STATUS_OK;
  } else {
    return SL_STATUS_FAIL;
  }
}

sl_status_t pd_epd_init(void)
{
  const uint32_t max_wait_time = 5; // [ms]
  int8_t temperature = 0;
  uint32_t reference_time;
  sl_status_t status = pd_epd_init_GPIOs();

  temperature = TEMPDRV_GetTemp();

  sl_udelay_wait(5000);
  GPIO_PinOutSet(PD_EPD_DRIVER_SYSTEM_RESET_PORT, PD_EPD_DRIVER_SYSTEM_RESET_PIN);
  sl_udelay_wait(5000);
  GPIO_PinOutClear(PD_EPD_DRIVER_SYSTEM_RESET_PORT, PD_EPD_DRIVER_SYSTEM_RESET_PIN);
  sl_udelay_wait(10000);
  GPIO_PinOutSet(PD_EPD_DRIVER_SYSTEM_RESET_PORT, PD_EPD_DRIVER_SYSTEM_RESET_PIN);
  sl_udelay_wait(5000);

  pd_epd_soft_reset();
  sl_udelay_wait(500);
  // wait until display is busy, but no more than 5 milliseconds
  reference_time = sl_sleeptimer_tick_to_ms(sl_sleeptimer_get_tick_count());

  while (GPIO_PinInGet(PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_PORT, PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_PIN) != PD_EPD_GPIO_LEVEL_HIGH) {
    uint32_t current_time = sl_sleeptimer_tick_to_ms(sl_sleeptimer_get_tick_count());
    if ((uint32_t)(current_time - reference_time) >= max_wait_time) {
      break;
    }
  }
  // check for timeout condition once more
  if (GPIO_PinInGet(PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_PORT, PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_PIN) == PD_EPD_GPIO_LEVEL_LOW) {
    status = SL_STATUS_INITIALIZATION;
  } else {
    status = pd_epd_set_temperature_and_PSR(temperature);
  }

  return status;
}

/*
 *
 */
sl_status_t pd_epd_init_GPIOs(void)
{
#ifdef SL_CATALOG_ESL_TAG_REF_HW_PRESENT
  // Init BUSY pin
  GPIO_PinModeSet(PD_EPD_DRIVER_PWR_PORT,
                  PD_EPD_DRIVER_PWR_PIN,
                  gpioModePushPull,
                  0);
#endif // SL_CATALOG_ESL_TAG_REF_HW_PRESENT

  // Init BUSY pin
  GPIO_PinModeSet(PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_PORT,
                  PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_PIN,
                  PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_MODE,
                  PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_INIT);

  // Init DATA/COMMAND pin
  GPIO_PinModeSet(PD_EPD_DRIVER_DATA_CONTROL_PORT,
                  PD_EPD_DRIVER_DATA_CONTROL_PIN,
                  PD_EPD_DRIVER_DATA_CONTROL_MODE,
                  PD_EPD_DRIVER_DATA_CONTROL_INIT);

  // Init EPD CS pin
  GPIO_PinModeSet(PD_EPD_DRIVER_CHIP_SELECT_PORT,
                  PD_EPD_DRIVER_CHIP_SELECT_PIN,
                  PD_EPD_DRIVER_CHIP_SELECT_MODE,
                  PD_EPD_DRIVER_CHIP_SELECT_INIT);

  // Init RESET pin
  GPIO_PinModeSet(PD_EPD_DRIVER_SYSTEM_RESET_PORT,
                  PD_EPD_DRIVER_SYSTEM_RESET_PIN,
                  PD_EPD_DRIVER_SYSTEM_RESET_MODE,
                  PD_EPD_DRIVER_SYSTEM_RESET_INIT);

  // GPIO_PinModeSet() doesn't return anything, so just return OK (as
  // indication the pin config has been done)
  return SL_STATUS_OK;
}

/*
 *
 */
sl_status_t pd_epd_deinit_GPIOs(void)
{
#ifdef SL_CATALOG_ESL_TAG_REF_HW_PRESENT
  // Init BUSY pin
  GPIO_PinModeSet(PD_EPD_DRIVER_PWR_PORT,
                  PD_EPD_DRIVER_PWR_PIN,
                  gpioModeDisabled,
                  0);
#endif // SL_CATALOG_ESL_TAG_REF_HW_PRESENT

  // Deinit BUSY pin
  GPIO_PinModeSet(PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_PORT,
                  PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_PIN,
                  gpioModeDisabled,
                  PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_INIT);

  // Deinit DATA/COMMAND pin
  GPIO_PinModeSet(PD_EPD_DRIVER_DATA_CONTROL_PORT,
                  PD_EPD_DRIVER_DATA_CONTROL_PIN,
                  gpioModeDisabled,
                  PD_EPD_DRIVER_DATA_CONTROL_INIT);

  // Deinit EPD CS pin
  GPIO_PinModeSet(PD_EPD_DRIVER_CHIP_SELECT_PORT,
                  PD_EPD_DRIVER_CHIP_SELECT_PIN,
                  gpioModeDisabled,
                  PD_EPD_DRIVER_CHIP_SELECT_INIT);

  // Deinit RESET pin
  GPIO_PinModeSet(PD_EPD_DRIVER_SYSTEM_RESET_PORT,
                  PD_EPD_DRIVER_SYSTEM_RESET_PIN,
                  gpioModeDisabled,
                  PD_EPD_DRIVER_SYSTEM_RESET_INIT);

  // GPIO_PinModeSet() doesn't return anything, so just return OK (as
  // indication the pin config has been done)
  return SL_STATUS_OK;
}

/*
 *
 */
sl_status_t pd_epd_soft_reset(void)
{
  uint8_t reg = PD_REG_SOFT_RESET;
  uint8_t data = PD_SOFT_RESET;

  pd_epd_write_data(&reg, &data, 1);

  return SL_STATUS_OK;
}

/*
 *
 */
sl_status_t pd_epd_set_temperature_and_PSR(int8_t temperature)
{
  uint8_t reg = 0x00;
  uint8_t data[2] = { 0x00, 0x00 };

  reg = PD_REG_INPUT_TEMPERATURE;

  // 25 degC = 0x19
  //  5 degC = 0x05
  // -5 degC = 0xFB (2's complement of temperature value)
  data[0] = temperature;

  pd_epd_write_data(&reg, data, 1);

  reg = PD_REG_ACTIVE_TEMPERATURE;
  data[0] = PD_ACTIVE_TEMPERATURE_DATA;

  pd_epd_write_data(&reg, data, 1);

  reg = PD_REG_PSR;
  data[0] = PD_PSR_BYTE_0;
  data[1] = PD_PSR_BYTE_1;

  pd_epd_write_data(&reg, data, 2);

  return SL_STATUS_OK;
}

void esl_pd_epd_bt_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;
  (void)sc; // suppress the compiler warning if sl_bt_esl_assert disabled

  // This event shall precede the esl_core_bt_on_event handler, and hence the
  // esl_core_boot handler invocation. Only then we can assure that the WST LCD
  // will be registered as the very first one in the list of available displays.
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_bt_evt_system_boot_id:
      // here we're checking that we precede the esl_core_bt_on_event invocation
      if (esl_core_get_status() == esl_state_boot) {
        esl_display_info_p info;

        // create the display info characteristic data
        #if PD_EPD_DISPLAY_COLOR_TYPE == PD_EPD_SPECTRA
        const uint8_t type = ESL_DISPLAY_TYPE_RED_BLACK_WHITE;
        #else
        const uint8_t type = ESL_DISPLAY_TYPE_BLACK_WHITE;
        #endif
        sc = esl_display_create(PD_EPD_DISPLAY_WIDTH, PD_EPD_DISPLAY_HEIGHT, type, &info);
        sl_bt_esl_assert(sc == SL_STATUS_OK);
        // register display we just created temporary - this makes it permanent
        sc = esl_display_add(info, esl_pd_epd_display_init, esl_pd_epd_display_write);
        sl_bt_esl_assert(sc == SL_STATUS_OK);
      }
      break;

    default:
      break;
  }
}
