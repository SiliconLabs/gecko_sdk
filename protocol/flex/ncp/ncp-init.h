#ifndef __NCP_INIT_H__
#define __NCP_INIT_H__

/**
 * Event Handler for loading a security key from the NVM at startup
 */
void sli_connect_ncp_key_loader_handler(void);

/**
 * @brief Init event to load the security key if it exists
 */
void sli_connect_init_ncp_security(void);

#endif
