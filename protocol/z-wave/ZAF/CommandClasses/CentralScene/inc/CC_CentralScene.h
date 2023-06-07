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
 * Structure that describes a single scene
 */
typedef struct _cc_central_scene_t
{
  uint8_t scene_number;       /// Number of scene
  uint8_t scene_attributes;   /// Supported attributes of scene
} cc_central_scene_t;

/**
 * Initiates the transmission of a "Central Scene Notification" command.
 * @note Source Endpoint is always set to Root in this function
 *
 * @param[in] pProfile pointer to AGI profile or NULL for lifeline
 * @param[in] keyAttribute The key event.
 * @param[in] sceneNumber The scene number.
 * @param[in] pCbFunc Callback function to be called when transmission is done/failed.
 * @return Status of the job.
 */
JOB_STATUS
cc_central_scene_notification_tx(
  AGI_PROFILE* pProfile,
  uint8_t keyAttribute,
  uint8_t sceneNumber,
  ZAF_TX_Callback_t pCbFunc);


/**
 * Start or stop Central Scene Notification timer
 * Used when event CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_HELD_DOWN
 * happens. App will send notifications periodically as long as the event is
 * active. Frequency depends on whether slow refresh is enabled or not.
 *
 * @param start_timer True if timer should be started,
 *                    false will stop active timer.
 * @param scene_number Number of active scene.
 */
void
cc_central_scene_handle_notification_timer(
    bool start_timer,
    uint8_t scene_number);

/**
 * Size of supported scenes.
 * This field advertises the size of each "Supported Key Attributes" field measured in bytes.
 * @note: This value can have values 1-3, but all attributes available in
 * current version of Central Scene (V3) can fit into a single byte.
 */
#define CC_CENTRAL_SCENE_SIZE_OF_SUPPORTED_SCENES_ATTRIBUTES  sizeof(((cc_central_scene_t *)0)->scene_attributes)


 /**
 * Returns the array of central scenes.
 * @note If scenes are identical, the array will contain only one element
 * @return Address of the first element in the central scene array.
 */
cc_central_scene_t * cc_central_scene_config_get_scenes_attributes(void);

/**
 * Returns number of supported scenes
 * @return Total amount of scenes supported by the app.
 */
uint8_t cc_central_scene_config_get_number_of_scenes();

/**
 * Returns supported attributes for a given scene
 *
 * @note This function is used to prepare CENTRAL_SCENE_SUPPORTED_REPORT
 * It is assumption that argument scene_number is higher than 1 only in case
 * when scenes are not identical.
 *
 * @param scene_number Number of scene to get supported attributes for
 * @return Supported attributes as bitmask
 */
uint8_t cc_central_scene_config_get_attribute_bitmask(uint8_t scene_number);

/**
 * Gets 'identical' attribute that describes supported key attributes
 *
 * @return True if all keys are identical,
 *         False if different key attributes supported
 */
uint8_t cc_central_scene_config_get_identical();

/**
 * @}
 * @}
 */

#endif /* _COMMANDCLASSCENTRALSCENE_H_ */
