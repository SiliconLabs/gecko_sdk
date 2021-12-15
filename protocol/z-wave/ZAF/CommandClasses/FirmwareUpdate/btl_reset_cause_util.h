/**
 * @file
 * Helps access the Silicon Labs bootloader reset cause.
 * @copyright 2019 Silicon Laboratories Inc.
 */

#ifndef PROTOCOL_Z_WAVE_ZAF_COMMANDCLASSES_FIRMWAREUPDATE_BTL_RESET_CAUSE_UTIL_H_
#define PROTOCOL_Z_WAVE_ZAF_COMMANDCLASSES_FIRMWAREUPDATE_BTL_RESET_CAUSE_UTIL_H_

#include <stdbool.h>
#include <stdint.h>

/**
 * Returns whether it's the first boot after firmware update.
 *
 * When invoked, it resets the cause to 0xFFFF so that this function will not return true on every
 * boot.
 *
 * If invoked several times on the first boot, the function will return true every time.
 * @param pBootReason Memory to which the bootloader reset cause will be written.
 * @return Returns true if it's the first boot after a firmware update, and false otherwise.
 */
bool CC_FirmwareUpdate_IsFirstBoot(uint16_t * pBootReason);

/**
 * Invalidates the current stored image so that the image storage slot is ready for a new image.
 */
void CC_FirmwareUpdate_InvalidateImage(void);

#endif /* PROTOCOL_Z_WAVE_ZAF_COMMANDCLASSES_FIRMWAREUPDATE_BTL_RESET_CAUSE_UTIL_H_ */
