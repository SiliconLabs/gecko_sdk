/***************************************************************************//**
 * @brief sl_btmesh_hsl_signal_transition_handler.h
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_BTMESH_HSL_SIGNAL_TRANSITION_H
#define SL_BTMESH_HSL_SIGNAL_TRANSITION_H

/***************************************************************************//**
 * Function for retrieving current hue.
 *
 * @return Current hue level.
 ******************************************************************************/
uint16_t sl_btmesh_get_hue(void);

/***************************************************************************//**
 * Function for retrieving current saturation.
 *
 * @return Current saturation level.
 ******************************************************************************/
uint16_t sl_btmesh_get_saturation(void);

/***************************************************************************//**
 * Set LED hue in given transition time.
 *
 * @param[in] hue            Hue level.
 * @param[in] transition_ms  Transition time in milliseconds.
 ******************************************************************************/
void sl_btmesh_hsl_set_hue_level(uint16_t hue,
                                 uint32_t transition_ms);

/***************************************************************************//**
 * Set LED saturation in given transition time.
 *
 * @param[in] saturation     Saturation level.
 * @param[in] transition_ms  Transition time in milliseconds.
 ******************************************************************************/
void sl_btmesh_hsl_set_saturation_level(uint16_t saturation,
                                        uint32_t transition_ms);

/*******************************************************************************
 * Callback for setting Light Hue
 *
 * @param[in] hue            Desired light hue level.
 ******************************************************************************/
void sl_btmesh_hsl_hue_cb(uint16_t hue);

/*******************************************************************************
 * Callback for setting Light Saturation
 *
 * @param[in] saturation     Desired light saturation level.
 ******************************************************************************/
void sl_btmesh_hsl_saturation_cb(uint16_t saturation);

/***************************************************************************//**
 * Called when the UI shall be updated with the changed HSL Model state during
 * a transition. The rate of this callback can be controlled by changing the
 * HSL_SERVER_HUE_UI_UPDATE_PERIOD macro.
 *
 * This is a callback which can be implemented in the application.
 * @note If no implementation is provided in the application then a default weak
 *       implementation is provided which is a no-operation. (empty function)
 *
 * @param[in] hue            Hue value.
 ******************************************************************************/
void sl_btmesh_hsl_hue_on_ui_update(uint16_t hue);

/***************************************************************************//**
 * Called when the UI shall be updated with the changed HSL Model state during
 * a transition. The rate of this callback can be controlled by changing the
 * HSL_SERVER_SATURATION_UI_UPDATE_PERIOD macro.
 *
 * This is a callback which can be implemented in the application.
 * @note If no implementation is provided in the application then a default weak
 *       implementation is provided which is a no-operation. (empty function)
 *
 * @param[in] saturation     Saturation value.
 ******************************************************************************/
void sl_btmesh_hsl_saturation_on_ui_update(uint16_t saturation);

#endif // SL_BTMESH_HSL_SIGNAL_TRANSITION_H
