/***************************************************************************//**
 * @file
 * @brief System Peripheral API
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

#include "em_system.h"
#include "sl_assert.h"
#include <stddef.h>
#if defined(SYSCFG_PRESENT)
#include "em_syscfg.h"
#endif
/***************************************************************************//**
 * @addtogroup system
 * @{
 ******************************************************************************/

/*******************************************************************************
 *********************************   DEFINES   *********************************
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/* Bit mask used to extract the part number value without the new naming
 * bitfield. */
#define SYSCFG_CHIPREV_PARTNUMBER1  0xFE0
#define SYSCFG_CHIPREV_PARTNUMBER0  0xF

/* Bit mask to convert NON-SECURE to SECURE */
#define CONVERT_NS_TO_S (~(1 << 28U))

/** @endcond */

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Get a chip major/minor revision.
 *
 * @param[out] rev
 *   A location to place the chip revision information.
 ******************************************************************************/
void SYSTEM_ChipRevisionGet(SYSTEM_ChipRevision_TypeDef *rev)
{
#if defined(_SYSCFG_CHIPREV_FAMILY_MASK) || defined(_SYSCFG_CHIPREV_PARTNUMBER_MASK)
  /* On series-2 (and higher) the revision info is in the SYSCFG->CHIPREV register. */
#if defined(CMU_CLKEN0_SYSCFG)
  CMU->CLKEN0_SET = CMU_CLKEN0_SYSCFG;
#endif
  uint32_t chiprev = SYSCFG_readChipRev();
#if defined(_SYSCFG_CHIPREV_PARTNUMBER_MASK)
  rev->partNumber = ((chiprev & SYSCFG_CHIPREV_PARTNUMBER1) >> 5) | (chiprev & SYSCFG_CHIPREV_PARTNUMBER0);
#else
  rev->family = (chiprev & _SYSCFG_CHIPREV_FAMILY_MASK) >> _SYSCFG_CHIPREV_FAMILY_SHIFT;
#endif
  rev->major  = (chiprev & _SYSCFG_CHIPREV_MAJOR_MASK)  >> _SYSCFG_CHIPREV_MAJOR_SHIFT;
  rev->minor  = (chiprev & _SYSCFG_CHIPREV_MINOR_MASK)  >> _SYSCFG_CHIPREV_MINOR_SHIFT;
#else
  uint8_t tmp;

  EFM_ASSERT(rev);

  /* CHIP FAMILY bit [5:2] */
  tmp  = (uint8_t)(((ROMTABLE->PID1 & _ROMTABLE_PID1_FAMILYMSB_MASK)
                    >> _ROMTABLE_PID1_FAMILYMSB_SHIFT) << 2);
  /* CHIP FAMILY bit [1:0] */
  tmp |=  (uint8_t)((ROMTABLE->PID0 & _ROMTABLE_PID0_FAMILYLSB_MASK)
                    >> _ROMTABLE_PID0_FAMILYLSB_SHIFT);
  rev->family = tmp;

  /* CHIP MAJOR bit [3:0] */
  rev->major = (uint8_t)((ROMTABLE->PID0 & _ROMTABLE_PID0_REVMAJOR_MASK)
                         >> _ROMTABLE_PID0_REVMAJOR_SHIFT);

  /* CHIP MINOR bit [7:4] */
  tmp  = (uint8_t)(((ROMTABLE->PID2 & _ROMTABLE_PID2_REVMINORMSB_MASK)
                    >> _ROMTABLE_PID2_REVMINORMSB_SHIFT) << 4);
  /* CHIP MINOR bit [3:0] */
  tmp |= (uint8_t)((ROMTABLE->PID3 & _ROMTABLE_PID3_REVMINORLSB_MASK)
                   >> _ROMTABLE_PID3_REVMINORLSB_SHIFT);
  rev->minor = tmp;
#endif
}

/***************************************************************************//**
 * @brief
 *    Get a factory calibration value for a given peripheral register.
 *
 * @param[in] regAddress
 *    The peripheral calibration register address to get a calibration value for. If
 *    the calibration value is found, this register is updated with the
 *    calibration value.
 *
 * @return
 *    True if a calibration value exists, false otherwise.
 ******************************************************************************/
bool SYSTEM_GetCalibrationValue(volatile uint32_t *regAddress)
{
  SYSTEM_CalAddrVal_TypeDef * p, * end;

  uint32_t s_regAddress = (uint32_t)regAddress;
  s_regAddress = s_regAddress & CONVERT_NS_TO_S;

#if defined(MSC_FLASH_CHIPCONFIG_MEM_BASE)
  p   = (SYSTEM_CalAddrVal_TypeDef *)MSC_FLASH_CHIPCONFIG_MEM_BASE;
  end = (SYSTEM_CalAddrVal_TypeDef *)MSC_FLASH_CHIPCONFIG_MEM_END;
#else
  p   = (SYSTEM_CalAddrVal_TypeDef *)(DEVINFO_BASE & 0xFFFFF000U);
  end = (SYSTEM_CalAddrVal_TypeDef *)DEVINFO_BASE;
#endif

  for (; p < end; p++) {
    if (p->address == 0) {
      /* p->address == 0 marks the end of the table */
      return false;
    }
    if (p->address == s_regAddress) {
      *regAddress = p->calValue;
      return true;
    }
  }
  /* Nothing found for regAddress. */
  return false;
}

/***************************************************************************//**
 * @brief
 *   Get family security capability.
 *
 * @note
 *   This function retrieves the family security capability based on the
 *   device number. The device number is one letter and 3 digits:
 *   DEVICENUMBER = (alpha-'A')*1000 + numeric. i.e. 0d = "A000"; 1123d = "B123".
 *   The security capabilities are represented by ::SYSTEM_SecurityCapability_TypeDef.
 *
 * @return
 *   Security capability of MCU.
 ******************************************************************************/
SYSTEM_SecurityCapability_TypeDef SYSTEM_GetSecurityCapability(void)
{
  SYSTEM_SecurityCapability_TypeDef sc;

#if (_SILICON_LABS_32B_SERIES == 0)
  sc = securityCapabilityNA;
#elif (_SILICON_LABS_32B_SERIES == 1)
  sc = securityCapabilityBasic;
#else
  sc = securityCapabilityUnknown;
#endif

#if (_SILICON_LABS_32B_SERIES == 2)
  uint16_t mcuFeatureSetMajor;
  uint16_t deviceNumber;
  deviceNumber = SYSTEM_GetPartNumber();
  mcuFeatureSetMajor = 'A' + (deviceNumber / 1000);
#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)
  // override feature set since BRD4182A Rev A00 -> rev B02 are marked "A"
  mcuFeatureSetMajor = 'C';
#endif

  switch (mcuFeatureSetMajor) {
    case 'A':
      sc = securityCapabilitySE;
      break;

    case 'B':
      sc = securityCapabilityVault;
      break;

    case 'C':
      sc = securityCapabilityRoT;
      break;

    default:
      sc = securityCapabilityUnknown;
      break;
  }
#endif

  return sc;
}

/***************************************************************************//**
 * @brief
 *   Get the unique number for this device.
 *
 * @return
 *   Unique number for this device.
 ******************************************************************************/
uint64_t SYSTEM_GetUnique(void)
{
#if defined (_DEVINFO_EUI64H_MASK)
  uint32_t tmp = DEVINFO->EUI64L;
  return (uint64_t)((uint64_t)DEVINFO->EUI64H << 32) | tmp;
#elif defined(_DEVINFO_UNIQUEH_MASK)
  uint32_t tmp = DEVINFO->UNIQUEL;
  return (uint64_t)((uint64_t)DEVINFO->UNIQUEH << 32) | tmp;
#else
#error (em_system.c): Location of device unique number is not defined.
#endif
}

/***************************************************************************//**
 * @brief
 *   Get the production revision for this part.
 *
 * @return
 *   Production revision for this part.
 ******************************************************************************/
uint8_t SYSTEM_GetProdRev(void)
{
#if defined (_DEVINFO_PART_PROD_REV_MASK)
  return (uint8_t)((DEVINFO->PART & _DEVINFO_PART_PROD_REV_MASK)
                   >> _DEVINFO_PART_PROD_REV_SHIFT);
#elif defined (_DEVINFO_INFO_PRODREV_MASK)
  return (uint8_t)((DEVINFO->INFO & _DEVINFO_INFO_PRODREV_MASK)
                   >> _DEVINFO_INFO_PRODREV_SHIFT);
#else
#error (em_system.c): Location of production revision is not defined.
#endif
}

/***************************************************************************//**
 * @brief
 *   Get the SRAM Base Address.
 *
 * @note
 *   This function is used to retrieve the base address of the SRAM.
 *
 * @return
 *   Base address SRAM (32-bit unsigned integer).
 ******************************************************************************/
uint32_t SYSTEM_GetSRAMBaseAddress(void)
{
  return (uint32_t)SRAM_BASE;
}

/***************************************************************************//**
 * @brief
 *   Get the SRAM size (in KB).
 *
 * @note
 *   This function retrieves SRAM size by reading the chip device
 *   info structure. If your binary is made for one specific device only,
 *   use SRAM_SIZE instead.
 *
 * @return
 *   Size of internal SRAM (in KB).
 ******************************************************************************/
uint16_t SYSTEM_GetSRAMSize(void)
{
  uint16_t sizekb;

#if defined(_EFM32_GECKO_FAMILY)
  /* Early Gecko devices had a bug where SRAM and Flash size were swapped. */
  if (SYSTEM_GetProdRev() < 5) {
    sizekb = (DEVINFO->MSIZE & _DEVINFO_MSIZE_FLASH_MASK)
             >> _DEVINFO_MSIZE_FLASH_SHIFT;
  }
#endif
  sizekb = (uint16_t)((DEVINFO->MSIZE & _DEVINFO_MSIZE_SRAM_MASK)
                      >> _DEVINFO_MSIZE_SRAM_SHIFT);

#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80) && defined(_EFR_DEVICE)
  /* Do not include EFR32xG1 RAMH. */
  sizekb--;
#endif

  return sizekb;
}

/***************************************************************************//**
 * @brief
 *   Get the flash size (in KB).
 *
 * @note
 *   This function retrieves flash size by reading the chip device
 *   info structure. If your binary is made for one specific device only,
 *   use FLASH_SIZE instead.
 *
 * @return
 *   Size of internal flash (in KB).
 ******************************************************************************/
uint16_t SYSTEM_GetFlashSize(void)
{
#if defined(_EFM32_GECKO_FAMILY)
  /* Early Gecko devices had a bug where SRAM and Flash size were swapped. */
  if (SYSTEM_GetProdRev() < 5) {
    return (DEVINFO->MSIZE & _DEVINFO_MSIZE_SRAM_MASK)
           >> _DEVINFO_MSIZE_SRAM_SHIFT;
  }
#endif
  return (uint16_t)((DEVINFO->MSIZE & _DEVINFO_MSIZE_FLASH_MASK)
                    >> _DEVINFO_MSIZE_FLASH_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Get the flash page size in bytes.
 *
 * @note
 *   This function retrieves flash page size by reading the chip device
 *   info structure. If your binary is made for one specific device only,
 *   use FLASH_PAGE_SIZE instead.
 *
 * @return
 *   Page size of internal flash in bytes.
 ******************************************************************************/
uint32_t SYSTEM_GetFlashPageSize(void)
{
  uint32_t tmp;

#if defined(_SILICON_LABS_32B_SERIES_0)

#if defined(_EFM32_GIANT_FAMILY)
  if (SYSTEM_GetProdRev() < 18) {
    /* Early Giant/Leopard devices did not have MEMINFO in DEVINFO. */
    return FLASH_PAGE_SIZE;
  }
#elif defined(_EFM32_ZERO_FAMILY)
  if (SYSTEM_GetProdRev() < 24) {
    /* Early Zero devices have an incorrect DEVINFO flash page size */
    return FLASH_PAGE_SIZE;
  }
#endif
#endif

#if defined(_DEVINFO_MEMINFO_FLASHPAGESIZE_MASK)
  tmp = (DEVINFO->MEMINFO & _DEVINFO_MEMINFO_FLASHPAGESIZE_MASK)
        >> _DEVINFO_MEMINFO_FLASHPAGESIZE_SHIFT;
#elif defined(_DEVINFO_MEMINFO_FLASH_PAGE_SIZE_MASK)
  tmp = (DEVINFO->MEMINFO & _DEVINFO_MEMINFO_FLASH_PAGE_SIZE_MASK)
        >> _DEVINFO_MEMINFO_FLASH_PAGE_SIZE_SHIFT;
#else
#error (em_system.c): Location of flash page size is not defined.
#endif

  return 1UL << ((tmp + 10UL) & 0x1FUL);
}

/***************************************************************************//**
 * @brief
 *   Get the MCU part number.
 *
 * @return
 *   The part number of MCU.
 ******************************************************************************/
uint16_t SYSTEM_GetPartNumber(void)
{
#if defined(_DEVINFO_PART_DEVICENUM_MASK)
  return (uint16_t)((DEVINFO->PART & _DEVINFO_PART_DEVICENUM_MASK)
                    >> _DEVINFO_PART_DEVICENUM_SHIFT);
#elif defined(_DEVINFO_PART_DEVICE_NUMBER_MASK)
  return (uint16_t)((DEVINFO->PART & _DEVINFO_PART_DEVICE_NUMBER_MASK)
                    >> _DEVINFO_PART_DEVICE_NUMBER_SHIFT);
#else
#error (em_system.c): Location of device part number is not defined.
#endif
}

/***************************************************************************//**
 * @brief
 *   Get the calibration temperature (in degrees Celsius).
 *
 * @return
 *   Calibration temperature in Celsius.
 ******************************************************************************/
uint8_t SYSTEM_GetCalibrationTemperature(void)
{
#if defined(_DEVINFO_CAL_TEMP_MASK)
  return (uint8_t)((DEVINFO->CAL & _DEVINFO_CAL_TEMP_MASK)
                   >> _DEVINFO_CAL_TEMP_SHIFT);
#elif defined(_DEVINFO_CALTEMP_TEMP_MASK)
  return (uint8_t)((DEVINFO->CALTEMP & _DEVINFO_CALTEMP_TEMP_MASK)
                   >> _DEVINFO_CALTEMP_TEMP_SHIFT);
#else
#error (em_system.c): Location of calibration temperature is not defined.
#endif
}

/***************************************************************************//**
 * @brief
 *   Get the MCU family identifier.
 *
 * @note
 *   This function retrieves family ID by reading the chip's device info
 *   structure in flash memory. Users can retrieve family ID directly
 *   by reading DEVINFO->PART item and decode with mask and shift
 *   \#defines defined in \<part_family\>_devinfo.h (refer to code
 *   below for details).
 *
 * @return
 *   Family identifier of MCU.
 ******************************************************************************/
SYSTEM_PartFamily_TypeDef SYSTEM_GetFamily(void)
{
#if defined(_DEVINFO_PART_FAMILY_MASK)
  return (SYSTEM_PartFamily_TypeDef)
         ((uint32_t)((DEVINFO->PART & (_DEVINFO_PART_FAMILY_MASK
                                       | _DEVINFO_PART_FAMILYNUM_MASK))));
#elif defined(_DEVINFO_PART_DEVICE_FAMILY_MASK)
  return (SYSTEM_PartFamily_TypeDef)
         ((uint32_t)((DEVINFO->PART & _DEVINFO_PART_DEVICE_FAMILY_MASK)
                     >> _DEVINFO_PART_DEVICE_FAMILY_SHIFT));
#else
  #error (em_system.h): Location of device family name is not defined.
#endif
}

/** @} (end addtogroup system) */
