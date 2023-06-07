/**
 * @file
 * Handler for Command Class Color Switch.
 * @copyright 2020 Silicon Laboratories Inc.
 */

#ifndef CC_COLOR_SWITCH_H
#define CC_COLOR_SWITCH_H

#include <ZAF_types.h>
#include <ZAF_Actuator.h>

/**
 * @addtogroup CC
 * @{
 * @addtogroup ColorSwitch
 * @{
 */

/**
 * Defined Color Components ID
 */
typedef enum EColorComponents_ {
  ECOLORCOMPONENT_WARM_WHITE,   ///< ECOLORCOMPONENT_WARM_WHITE
  ECOLORCOMPONENT_COLD_WHITE,   ///< ECOLORCOMPONENT_COLD_WHITE
  ECOLORCOMPONENT_RED,          ///< ECOLORCOMPONENT_RED
  ECOLORCOMPONENT_GREEN,        ///< ECOLORCOMPONENT_GREEN
  ECOLORCOMPONENT_BLUE,         ///< ECOLORCOMPONENT_BLUE
  ECOLORCOMPONENT_AMBER,        ///< ECOLORCOMPONENT_AMBER
  ECOLORCOMPONENT_CYAN,         ///< ECOLORCOMPONENT_CYAN (For 6ch color mixing)
  ECOLORCOMPONENT_PURPLE,       ///< ECOLORCOMPONENT_PURPLE (For 6ch color mixing)
  //ECOLORCOMPONENT_INDEXED_COLOR, //(OBSOLETED)
  ECOLORCOMPONENT_COLOR_UNDEFINED
} EColorComponents;


/**
 * Structure that holds Color Switch CC related data.
 */
typedef struct colorComponent_
{
  RECEIVE_OPTIONS_TYPE_EX rxOpt;             ///< saves Rx values, including data about supervision.
                                             ///< (Must be first member - required by TSE)
  EColorComponents colorId;                  ///< Color Component ID
  uint8_t ep;                                ///< Endpoint that supports colorId
  s_Actuator obj;                            ///< Actuator data
  void (*cb)(struct colorComponent_ *color); ///< pointer to app callback function that triggers driver changes
} s_colorComponent;

/**
 * @brief Can be used as single cb function for all colors. Defined in the app.
 * Called when change takes place in driver and app needs to update LED status
 * 
 */
void cc_color_switch_refresh_cb(void);

/**
 * @}
 * @}
 */
#endif // CC_COLOR_SWITCH_H
