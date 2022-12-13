/**
 * @file
 * Handler for Command Class Central Scene.
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _COMMANDCLASSCENTRALSCENE_H_
#define _COMMANDCLASSCENTRALSCENE_H_

#include <CC_Common.h>
#include <ZW_TransportEndpoint.h>


/**
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup CentralScene
 * @{
 */

/**
 * Contains all configuration parameters.
 */
typedef struct
{
  uint8_t slowRefresh;
}
central_scene_configuration_t;

typedef struct s_CC_centralScene_data_t_
{
  RECEIVE_OPTIONS_TYPE_EX rxOptions; /**< rxOptions */
} s_CC_centralScene_data_t;

/**
 * Initiates the transmission of a "Central Scene Notification" command.
 * @param[in] pProfile pointer to AGI profile
 * @param[in] sourceEndpoint source endpoint
 * @param[in] keyAttribute The key event.
 * @param[in] sceneNumber The scene number.
 * @param[in] pCbFunc Callback function to be called when transmission is done/failed.
 * @return Status of the job.
 */
JOB_STATUS
CommandClassCentralSceneNotificationTransmit(
  AGI_PROFILE* pProfile,
  uint8_t sourceEndpoint,
  uint8_t keyAttribute,
  uint8_t sceneNumber,
  VOID_CALLBACKFUNC(pCbFunc)(TRANSMISSION_RESULT * pTransmissionResult));

/**
 * Send report when change happen via lifeLine.
 *
 * Callback used by TSE module. Refer to @ref ZAF_TSE.h for more details.
 *
 * @param txOptions txOptions
 * @param pData Command payload for the report
 */
void CC_CentralScene_configuration_report_stx(
    TRANSMIT_OPTIONS_TYPE_SINGLE_EX txOptions,
    void *pData);

/**
 * Get the configuration parameter
 * @return Configuration value, with the "Slow Refresh" capability included.
 */
uint8_t 
cc_central_scene_get_configuration();

/**
 * Set the configuration parameter
 * @param slowRefresh Configuration value
 */
void
cc_central_scene_set_configuration(uint8_t slowRefresh);

/**
 * @}
 * @}
 */

#endif /* _COMMANDCLASSCENTRALSCENE_H_ */
