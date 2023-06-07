/***************************************************************************//**
 * @file
 * @brief Bookkeeping for Commissioning related info.
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

#include "green-power-client-config.h"

// TODO: properly doxygenate this file

/**
 * @defgroup green-power-client Green Power Client
 * @ingroup component cluster
 * @brief API and Callbacks for the Green Power Cluster Client Component
 *
 * A component implementing the client-side functionality of the Green Power cluster.
 *
 */

/**
 * @addtogroup green-power-client
 * @{
 */

#define GP_CLIENT_ON_TRANSMIT_CHANNEL_MASK BIT(0)
#define GP_CLIENT_TRANSMIT_SAME_AS_OPERATIONAL_CHANNEL_MASK BIT(1)
#define GP_CLIENT_ADDITIONAL_CHANNEL_REQUEST_PENDING BIT(2)

typedef enum  {
  EMBER_GP_GPD_MAC_SEQ_NUM_CAP_SEQUENTIAL  = 0x00,
  EMBER_GP_GPD_MAC_SEQ_NUM_CAP_RANDOM      = 0x01,
} EmberGpGpdMacSeqNumCap;

typedef enum {
  EMBER_AF_GPC_COMMISSIONING_EXIT_ON_COMMISSIONING_WINDOW_EXP = 0x1,
  EMBER_AF_GPC_COMMISSIONING_EXIT_ON_FIRST_PAIRING_SUCCESS = 0x2,
  EMBER_AF_GPC_COMMISSIONING_EXIT_ON_GP_PROXY_COMMISSIONING_MODE_EXIT = 0x4,
  EMBER_AF_GPC_COMMISSIONING_EXIT_MODE_MAX = 0xFF,
} EmberAfGreenPowerClientCommissioningExitMode;

typedef struct {
  bool inCommissioningMode;
  EmberAfGreenPowerClientCommissioningExitMode exitMode;
  uint16_t gppCommissioningWindow;
  uint8_t channel;
  bool unicastCommunication;
  EmberNodeId commissioningSink;
  uint8_t channelStatus;  //bit 0 shows if we are on transmit channel(1) or on operational channel(0). bit 1 shows if operational channel is same as transmit channel (1).
} EmberAfGreenPowerClientCommissioningState;

typedef struct {
  EmberGpAddress addrs[EMBER_AF_PLUGIN_GREEN_POWER_CLIENT_MAX_ADDR_ENTRIES];
  uint8_t randomSeqNums[EMBER_AF_PLUGIN_GREEN_POWER_CLIENT_MAX_ADDR_ENTRIES][EMBER_AF_PLUGIN_GREEN_POWER_CLIENT_MAX_SEQ_NUM_ENTRIES_PER_ADDR];
  uint32_t expirationTimes[EMBER_AF_PLUGIN_GREEN_POWER_CLIENT_MAX_ADDR_ENTRIES][EMBER_AF_PLUGIN_GREEN_POWER_CLIENT_MAX_SEQ_NUM_ENTRIES_PER_ADDR];
} EmberAfGreenPowerDuplicateFilter;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
bool sli_zigbee_af_gp_message_checking(EmberGpAddress *gpAddr, uint8_t sequenceNumber);
#endif //DOXYGEN_SHOULD_SKIP_THIS

/**
 * @name API
 * @{
 */

/** @brief Clear the proxy table.
 *
 * This function clears the proxy table.
 *
 */
void emberAfPluginGreenPowerClientClearProxyTable(void);

/** @} */ // end of name API

/**
 * @name Callbacks
 * @{
 */

/**
 * @defgroup gp_client_cb Green Power Client
 * @ingroup af_callback
 * @brief Callbacks for Green Power Client Component
 *
 */

/**
 * @addtogroup gp_client_cb
 * @{
 */

/** @brief Green power client Sink table based forward callback.
 *
 * This function is called by the Green Power client before forwarding the gp notification.
 * This callback provides the pointer to the group list for the paired gpd.
 * In case of a combo application, where the green power server is also present, this callback
 * is consumed by the green power server to update the sinklist from the sink table.
 *
 * @param addr gpd address Ver.: always
 * @param sinkList sink list pointer , that can be used to update the sink list  Ver.: always
 * @param maxNumberEntries maximum number of sink list entires Ver.: always
 */
void emberAfGreenPowerClientGpdfSinkTableBasedForwardCallback(EmberGpAddress *addr,
                                                              EmberGpSinkListEntry *sinkList,
                                                              uint8_t maxNumberEntries);

/** @} */ // end of gp_client_cb
/** @} */ // end of name Callbacks

/** @} */ // end of green-power-client
