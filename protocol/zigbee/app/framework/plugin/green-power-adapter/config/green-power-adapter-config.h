/***************************************************************************//**
 * @file  green-power-adapter-config.h
 * @brief Zigbee Green Power Adapter component configuration header.
 ********************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

// <<< Use Configuration Wizard in Context Menu >>>

// <h>Zigbee Green Power Adapter configuration

// <e EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_EVENT_SYSTEM>Use custom event system for green-power plugins
// <i> Default: TRUE
// <i> This enables abbility to use custom event system on green-power plugins.
#define EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_EVENT_SYSTEM  1

// <s EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_CUSTOM_EVENT_SYSTEM_HEADER> File containing custom data type used for green power plugins
// <i> Default: "green-power-adapter-custom-type.h"
// <i> Custom event system header used by green-power plugins. By default adapter plugin uses a stubbed header file supplied by Silabs SDK. Customer has to duplicate that file with different name and define their own data type
#define EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_CUSTOM_EVENT_SYSTEM_HEADER "green-power-adapter-custom-type.h"
// </e>

// <e EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_ATTRIBUTE_SYSTEM>Use custom attribute system for green-power plugins
// <i> Default: TRUE
// <i> This enables abbility to use custom attribute system on green-power plugins.
#define EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_ATTRIBUTE_SYSTEM  1

// <s EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_CUSTOM_ATTRIBUTE_SYSTEM_HEADER> File containing custom data type used for green power plugins
// <i> Default: "green-power-adapter-type.h"
// <i> Custom event system header used by green-power plugins. By default adapter plugin uses a stubbed header file supplied by Silabs SDK. Customer has to duplicate that file with different name and define their own data type
#define EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_CUSTOM_ATTRIBUTE_SYSTEM_HEADER "green-power-adapter-custom-type.h"
// </e>

// </h>
// <<< end of configuration section >>>
