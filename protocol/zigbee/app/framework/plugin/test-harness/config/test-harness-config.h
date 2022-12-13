/***************************************************************************//**
 * @brief Zigbee Test Harness component configuration header.
 *\n*******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

// <h>Zigbee Test Harness configuration

// <q EMBER_AF_PLUGIN_TEST_HARNESS_AUTO_REGISTRATION_START> Automatically Start Smart Energy Registration
// <i> Default: TRUE
// <i> This enables or disables whether Smart Energy registration automatically starts after joining or rebooting.  Without this plugin the normal behavior is to start registration.
#define EMBER_AF_PLUGIN_TEST_HARNESS_AUTO_REGISTRATION_START   1

// <q EMBER_AF_TC_SWAP_OUT_TEST> Test configuration for trust center swap out test.
// <i> Default: FALSE
// <i> For testing purposes only, when set to 1, it suppresses, the normal call to emberNetworkInit() at reboot.
// <i> This allows to call manual network initialization later and prevent the node from immediately coming back up on the network after reboot.
// <i> This enables corresponding CLI command to initialize the network at later point in tests.
#define EMBER_AF_TC_SWAP_OUT_TEST   0

// <q EMBER_TEST_OTA_EEPROM_SOC_BOOTLOAD> Test configuration for ota eeprom soc bootload test.
// <i> Default: FALSE
#define EMBER_TEST_OTA_EEPROM_SOC_BOOTLOAD   0

// <q EMBER_TEST_OTA_EEPROM_PAGE_ERASE> Test configuration for ota eeprom page erase test.
// <i> Default: FALSE
#define EMBER_TEST_OTA_EEPROM_PAGE_ERASE   0

// <q EMBER_TEST_OTA_CLIENT_IGNORE_NON_TRUST_CENTERS> Test configuration for ota client to ignore non trust centers test.
// <i> Default: FALSE
// <i> For testing purposes only, when set to 1, in ota discovery process, ota client will ignore ota server which is not trust center.
#define EMBER_TEST_OTA_CLIENT_IGNORE_NON_TRUST_CENTERS   0

// <q EMBER_TEST_BLOCK_PERIOD_IN_SECONDS> Test configuration for delaying ota download on ota client.
// <i> Default: FALSE
// <i> For testing purposes only, when set to 1, the ota client will delay for a period of time (seconds) before starting downloading new image.
#define EMBER_TEST_BLOCK_PERIOD_IN_SECONDS   0

// </h>

// <<< end of configuration section >>>
