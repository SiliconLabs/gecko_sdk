/***************************************************************************//**
 * @file
 * @brief Tokens for the Tunneling Server plugin (persist opened tunnels).
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "tunneling-server.h"
#include "tunneling-server-config.h"

#if (EMBER_AF_PLUGIN_TUNNELING_SERVER_PERSIST_TUNNELS_TO_TOKEN == 1)

// Custom Application Tokens - persist opened tunnel entries across reboots.
// Unused entry: clientEndpoint == TUNNELING_SERVER_TOKEN_UNUSED_ENDPOINT (0xFF).
#define CREATOR_PLUGIN_TUNNELING_SERVER_TUNNELS   (0x0030)
#define NVM3KEY_PLUGIN_TUNNELING_SERVER_TUNNELS   (NVM3KEY_DOMAIN_USER | 0x0030)

#ifdef DEFINETYPES
// Type EmberAfPluginTunnelingServerStoredTunnelEntry comes from tunneling-server.h
#endif // DEFINETYPES

#ifdef DEFINETOKENS
DEFINE_INDEXED_TOKEN(PLUGIN_TUNNELING_SERVER_TUNNELS,
                     EmberAfPluginTunnelingServerStoredTunnelEntry,
                     EMBER_AF_PLUGIN_TUNNELING_SERVER_TUNNEL_LIMIT,
                     { { 0 }, TUNNELING_SERVER_TOKEN_UNUSED_ENDPOINT, 0, 0, 0, 0 })
#endif // DEFINETOKENS

#endif /* EMBER_AF_PLUGIN_TUNNELING_SERVER_PERSIST_TUNNELS_TO_TOKEN */
