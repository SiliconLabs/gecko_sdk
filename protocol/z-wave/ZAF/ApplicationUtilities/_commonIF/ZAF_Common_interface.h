
/**
 * @file
 * @brief Sets and gets useful values and handles.
 *
 * The functions in this file won't perform any actions like initialization, reset, etc. Such
 * functions can be found in ZAF_Common_helper.h.
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _ZAF_COMMON_IF_H_
#define _ZAF_COMMON_IF_H_

#include <ZAF_CmdPublisher.h>
#include <zpal_power_manager.h>
#include <zpal_radio.h>

#include <ZW_application_transport_interface.h>


/**
 * @addtogroup ZAF
 * @{
 * @addtogroup ZAF_IF ZAF Interface
 * @{
 */

typedef void (* zaf_wake_up_callback_t)(void);

/**
 * Used to indicate node inclusion type that related to it working over Long Range or Z-Wave mode.
 * This information will be used to distinguish between these two mode in order to indicate the needed
 * operations when they differ between Z-Wave and Long Range.
 */
typedef enum
{
  EINCLUSIONMODE_NOT_SET = 0,   ///!< Does not indicate inclusion state, but that it is undefined!
  EINCLUSIONMODE_ZWAVE_CLS,     ///!< This node was included as a Z-Wave Classic device.
  EINCLUSIONMODE_ZWAVE_LR       ///!< This node was included as a Z-Wave Long Range device.
} EInclusionMode_t;

// setters

/**
 * Pass an application handle to the ZAF framework with pointers to application resources. Can be later used by CC-s.
 * @param pAppHandle pointer to Application Handle in application
 */
void ZAF_setAppHandle(SApplicationHandles* pAppHandle);

/**
 * Pass an application power lock handle to the ZAF framework. Can be later used by CC-s.
 * Used for Power management in case of wake up of FLiRS nodes.
 *
 * @param powerLock pointer to power lock object in application
 */
void ZAF_setPowerLock(zpal_pm_handle_t powerLock);

/**
 * Set the CP context. The application should use this an initialization,
 * so the ZAF_Common interface can redistribute the pContext address subsequently
 *
 * @param handle to set
 */
void ZAF_SetCPHandle(CP_Handle_t handle);


// Getters

/**
 * Get m_pAppHandles object
 * @return m_pAppHandles
 */
SApplicationHandles* ZAF_getAppHandle(void);

/**
 * Get Protocol Info object
 * @return pProtocolInfo member of m_pAppHandles
 */
const SProtocolInfo* ZAF_getProtocolInfo(void);

/**
 * Get Notifying queue object. It is stored in m_pAppHandles
 * @return pZwTxQueue member of m_pAppHandles
 */
SQueueNotifying* ZAF_getZwTxQueue(void);

/**
 * Get Notifying queue object used for ZW Command Queue.
 * @return pZwCommandQueue member of m_pAppHandles
 */
SQueueNotifying* ZAF_getZwCommandQueue(void);

/**
 * Get Network Statistics object.
 * @return pNetworkStatistics member of m_pAppHandles
 */
const zpal_radio_network_stats_t* ZAF_getNetworkStatistics(void);

/**
 * Get m_PowerLock object
 * @return m_PowerLock
 */
zpal_pm_handle_t ZAF_getPowerLock(void);

/**
 * Returns the granted security keys.
 *
 * Refer to ZW_security_api.h for the security key masks.
 * @return 8 bit mask where a set bit indicates that a security key is granted.
 */
uint8_t ZAF_GetSecurityKeys(void);


/**
 * Get Command Publisher handle
 * Any other module can request the address of the CP context to use the API
 * @return Pointer to Command Publisher context
 */
CP_Handle_t ZAF_getCPHandle(void);


/**
 * Check if device is FLiRS based on device option mask
 *
 * @param pAppNodeInfo
 * @return True or false, based on pAppNodeInfo
 */
bool isFLiRS(const SAppNodeInfo_t * pAppNodeInfo);

/**
 * Returns the current inclusion state of the node.
 * @return EInclusionState_t
 */
EInclusionState_t ZAF_GetInclusionState(void);

/**
 * Returns the current ID of the node.
 *
 * If the node is not added to a network, the node ID is zero.
 * @return Node ID
 */
node_id_t ZAF_GetNodeID(void);

/**
 * Returns the current home ID
 *
 * @return Home ID
 */
uint32_t ZAF_GetHomeID(void);

/**
 * Returns the current Suc node ID
 *
 * @return Suc Node ID
 */
node_id_t ZAF_GetSucNodeId(void);

/**
 * Returns the current inclusion mode of the node, which indicates
 * whether the node is acting as a Z-Wave or Z-Wave LR node.
 *
 * @return EInclusionMode_t
 */
EInclusionMode_t ZAF_GetInclusionMode(void);

/**
 * Checks if region is valid Z-Wave radio region
 * @param region Region to check
 * @return True if region is valid, false if it isn't.
 */
bool isRfRegionValid(zpal_radio_region_t region);

/**
 * Registers a wake up function to keep the node awake.
 *
 * The function will be invoked on every reception of a frame to keep the node awake.
 * @param callback Function to invoke to keep the node awake.
 */
void zaf_set_stay_awake_callback(zaf_wake_up_callback_t callback);

/**
 * Returns the wake up callback.
 * @return Wake up callback
 */
zaf_wake_up_callback_t zaf_get_stay_awake_callback(void);

/**
 * @} // ZAF_IF
 * @} // ZAF
 */

#endif /*_ZAF_COMMON_IF_H_ */
