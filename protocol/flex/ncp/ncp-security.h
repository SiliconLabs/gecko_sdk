#ifndef __NCP_SECURITY_H__
#define __NCP_SECURITY_H__

/**
 * @brief Register a PSA Crypto key. The key is given as an clear array and the API
 * is intended to be used when the SoC is used as an NCP.
 * @warning: As this API passes a plain text key, it is not recommended to use it
 * without CPC secure link enabled
 *
 * @param keyContents An array containing the security key to be set.
 * @param keyLength This API checks that the key is the correct length with this
 *                  parameter
 * @return An EmberStatus value of ::EMBER_SUCCESS if the key was successfully
 *  imported. If the function failed, it returns:
 *  - EMBER_BAD_ARGUMENT if the key length is incorrect
 *  - EMBER_SECURITY_DATA_INVALID if the key does not match the Connect stack
 *  key format.
 *
 */

EmberStatus emApiSetNcpSecurityKey(uint8_t *keyContents, uint8_t keyLength);

#endif
