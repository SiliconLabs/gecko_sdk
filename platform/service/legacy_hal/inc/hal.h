/***************************************************************************//**
 * @file hal.h
 * @brief Header file for the Legacy HAL
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories, Inc, www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef HAL_H
#define HAL_H

#ifdef TOKEN_MANAGER_TEST
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#else // TOKEN_MANAGER_TEST
#ifndef EZSP_HOST
#include "ember.h"
#endif
#endif // TOKEN_MANAGER_TEST
#include "error-def.h"
#include "micro.h"
#include "serial.h"
#include "led.h"
#include "button.h"
#include "crc.h"

#if defined(SL_CATALOG_LEGACY_BOOTLOADER_INTERFACE_PRESENT)
#include "bootloader-common.h"
#include "bootloader-interface.h"
#include "bootloader-interface-app.h"
#include "bootloader-interface-standalone.h"
#endif

#include "random.h"
#if !defined(EZSP_HOST) && !defined(EMBER_TEST)
#include "sl_token_api.h"
#else
#include "token.h"
#endif
#ifdef CORTEXM3
#include "cortexm3/diagnostic.h"
#endif

#define SECURITY_BLOCK_SIZE   16 // in bytes

/***************************************************************************//**
 * @addtogroup legacyhal Legacy HAL
 * @brief The Legacy HAL is an implementation of the Hardware Abstraction Layer (HAL)
 *        that was used by the Zigbee EmberZNet and Flex Connect stacks before their
 *		  transition to the new component-based architecture (Zigbee version 7.0 and
 *		  Connect version 3.0).
 *        This component is not a complete duplicate of the old HAL. It only contains
 *        the most commonly used pieces to enable our networking stacks and sample
 *		  applications and to support porting customer applications to the new
 *		  component-based implementation.
 *        Currently, Zigbee and Connect sample applications are dependent on this component.
 *        Eventually, they will be ported to use new HAL components directly so that this
 *		  component can become optional or be deprecated.
 * @note This component is only designed to be used with Zigbee and Connect stack applications.
 *       Do not use with any other stacks as it will likely introduce problems.
 *
 * @{
 ******************************************************************************/

#ifndef EMBER_TEST
#define simulatedTimePasses()
#else
void simulatedTimePasses(void);
#endif // EMBER_TEST
/**
 * @brief This function will get 16u ms tick data
 *
 * @return
 */
uint16_t halCommonGetInt16uMillisecondTick(void);

/**
 * @brief This function will get 32u ms tick data
 *
 * @return
 */
uint32_t halCommonGetInt32uMillisecondTick(void);

/**
 * @brief This function will get 64u ms tick data
 *
 * @return
 */
uint64_t halCommonGetInt64uMillisecondTick(void);

/**
 * @brief This function will get 16u quater second tick data
 *
 * @return
 */
uint16_t halCommonGetInt16uQuarterSecondTick(void);

/**
 * @brief This function will start system timer
 *
 * @return
 */
uint16_t halInternalStartSystemTimer(void);

/**
 * @brief This function will delay an amount of time in us
 *
 * @param us second in us
 */
void halCommonDelayMicroseconds(uint16_t us);

/**
 * @brief This function will delay an amount of time in ms
 *
 * @param ms second in ms
 */
void halCommonDelayMilliseconds(uint16_t ms);

/**
 * @brief This function will set state to idle for an amount of time in ms
 *
 * @param duration second in us
 *
 * @return EmberStatus
 */
EmberStatus halCommonIdleForMilliseconds(uint32_t *duration);

/**
 * @brief This function is halStackSymbolDelayAIsr
 */
void halStackSymbolDelayAIsr(void);

/**
 * @brief This function is halStackRadioPowerUpBoard
 */
void halStackRadioPowerUpBoard(void);

/**
 * @brief This function is halStackRadioPowerUpBoard
 */
void halStackRadioPowerDownBoard(void);

/**
 * @brief This function is halStackProcessBootCount
 */
void halStackProcessBootCount(void);

/**
 * @brief This function is sli_util_debug_init
 *
 * @return EmberStatus
 */
EmberStatus sli_util_debug_init(void);

/**
 * @brief This function is sli_802154phy_radio_seed_random
 */
void sli_802154phy_radio_seed_random(void);

/** @} (end addtogroup legacyhal) */

#endif // HAL_H
