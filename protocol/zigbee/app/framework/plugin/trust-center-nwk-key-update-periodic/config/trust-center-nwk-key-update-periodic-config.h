/***************************************************************************//**
 * @brief Zigbee Trust Center Network Key Update Periodic component configuration header.
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

// <h>Zigbee Trust Center Network Key Update Periodic configuration

// <o KEY_UPDATE_PERIOD_MINUTES> Key Update Period in minutes <1-525601>
// <i> Default: 30
// <i> This configuration is for the Trust Center to periodically initiate a NWK key update based on the parameters defined below.  It uses either a Broadcast based method, or a Unicast based method depending on whether the 'Trust Center NWK Key Update Broadcast' or 'Trust Center NWK Key Update Unicast' component has been included.
// <i> NOTE: Trust centers should update the network key at least once per year. It is not recommended to update the network key more than once every 30 days except when required by the application or profile.
// <i> NOTE: The default value of 30 minutes for Key Update Period/Units is to ensure that the network key update operation is observed and verified during development and test.  This value should be changed for production deployment; Zigbee R22 recommends a period of no less than 30 days.
#define KEY_UPDATE_PERIOD_MINUTES   30

// </h>

// <<< end of configuration section >>>
