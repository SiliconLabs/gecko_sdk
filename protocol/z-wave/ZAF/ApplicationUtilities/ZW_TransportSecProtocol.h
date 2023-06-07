/**
 * @file
 * Implements parts of the Z-Wave Application Framework Transport Layer.
 * @copyright 2018 Silicon Laboratories Inc.
 */
#ifndef _TRANSPORT_SEC_PROTOCOL_H_
#define _TRANSPORT_SEC_PROTOCOL_H_


#include <ZW_basis_api.h>
#include <ZW_transport_api.h>
#include <ZW_TransportEndpoint.h>
#include <ZW_application_transport_interface.h>

/**
 * @addtogroup ZAF
 * @{
 * @addtogroup ZAF_Transport
 * @{
 * @addtogroup ZAF_Transport_Security
 * @{
 */

/**
 * Max number of command classes a command class list can contain.
 */
#define APPL_NODEPARM_MAX 35


/**
 * Called when the frame is received
 * @param pCmd  Payload from the received frame, the command is the very first byte
 * @param cmdLength Number of command bytes including the command
 * @param rxOpt Struct to use (may be partially filled out if parsing encapsulated command)
 */
extern void
Transport_ApplicationCommandHandler(
    ZW_APPLICATION_TX_BUFFER *pCmd,
    uint8_t cmdLength,
    RECEIVE_OPTIONS_TYPE *rxOpt);


/**
 * Callback function triggered by Cmd Publisher when the frame is received from protocol
 * See ZAF_CmdPublisher.h for more details
 *
 * @param pSubscriberContext A handle to the Transport layer
 * @param pRxPackage Received package containing: payload from received frame, number of command bytes
 *                   (including the command) and rxOpt struct
 */
void
ApplicationCommandHandler(void *pSubscriberContext, SZwaveReceivePackage* pRxPackage);

/**
 * Initializes the ZAF transport layer.
 *
 * @return true if transport layer is initialized, false otherwise.
 */
uint8_t Transport_OnApplicationInitSW(void);
/**
 * @brief Register the new node id in the transport layer after learn mode completes.
 *
 * This function must be called in LearnCompleted application function
 *
 * @deprecated Use ZAF_Transport_OnLearnCompleted().
 *
 * @param nodeID The newly assigned node id.
 * @return true on success.
*/
uint8_t
Transport_OnLearnCompleted(node_id_t nodeID);

/**
 * Updates the active NIF depending on learn mode result.
 *
 * Must be invoked when learn mode has completed (on inclusion/exclusion).
 */
void ZAF_Transport_OnLearnCompleted(void);

/**
 * Returns whether a given command is supported.
 *
 * @param commandClass Command class to check for.
 * @param command Command to check for.
 * @param eKey Security key that the frame was received with.
 * @return Returns true if the command is supported and false otherwise.
 */
bool
TransportCmdClassSupported(uint8_t commandClass,
                           uint8_t command,
                           enum SECURITY_KEY eKey);

/**
 * @brief  Get highest secure level
 * @param protocolSecBits secure bits
 * @return secure level
 */
enum SECURITY_KEY
GetHighestSecureLevel(
    uint8_t protocolSecBits);

/**
 * @brief Get command class list from device
 * @param[in] included boolean value for node is included
 * @param[in] eKey security key of type security_key_t
 * @param[in] endpoint 0 - root 1 - X endpoint number
 */
zaf_cc_list_t*
GetCommandClassList(
    bool included,
    security_key_t eKey,
    uint8_t endpoint);

/**
 * @} // ZAF_Transport_Security
 * @} // ZAF_Transport
 * @} // ZAF
 */

#endif /*_TRANSPORT_SEC_PROTOCOL_H_*/
