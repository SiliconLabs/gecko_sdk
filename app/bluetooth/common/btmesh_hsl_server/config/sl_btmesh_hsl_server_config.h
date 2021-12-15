#ifndef SL_BTMESH_HSL_SERVER_CONFIG_H
#define SL_BTMESH_HSL_SERVER_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> HSL Server configuration

// <o HSL_SERVER_NVM_SAVE_TIME> Timeout [ms] for saving States of the model to NVM.
// <i> Default: 5000
// <i> Timeout [ms] for saving States of the model to NVM.
#define HSL_SERVER_NVM_SAVE_TIME   (5000)

// <o HSL_SERVER_PS_KEY> PS Key for NVM Page where the States of the HSL Models are saved.
// <i> Default: 0x4008
// <i> PS Key for NVM Page where the States of the HSL Models are saved.
#define HSL_SERVER_PS_KEY   (0x4008)

// <o HSL_SERVER_HUE_UPDATE_PERIOD> Periodicity [ms] for updating the hue during a transition.
// <i> Default: 1
// <i> Periodicity [ms] for updating the hue during a transition.
#define HSL_SERVER_HUE_UPDATE_PERIOD   (1)

// <o HSL_SERVER_SATURATION_UPDATE_PERIOD> Periodicity [ms] for updating the saturation during a transition.
// <i> Default: 1
// <i> Periodicity [ms] for updating the saturation during a transition.
#define HSL_SERVER_SATURATION_UPDATE_PERIOD   (1)

// <o HSL_SERVER_HUE_UI_UPDATE_PERIOD> Periodicity [ms] for updating the UI with hue during a transition.
// <i> Default: 100
// <i> Periodicity [ms] for updating the hue values on the UI.
#define HSL_SERVER_HUE_UI_UPDATE_PERIOD   (100)

// <o HSL_SERVER_SATURATION_UI_UPDATE_PERIOD> Periodicity [ms] for updating the UI with saturation during a transition.
// <i> Default: 100
// <i> Periodicity [ms] for updating the saturation values on the UI.
#define HSL_SERVER_SATURATION_UI_UPDATE_PERIOD   (100)

// <o HSL_SERVER_DEFAULT_HUE> Default Hue
// <i> Default: 0
// <i> Default Hue value.
#define HSL_SERVER_DEFAULT_HUE   (0)

// <o HSL_SERVER_DEFAULT_SATURATION> Default Saturation
// <i> Default: 0
// <i> Default Saturation.
#define HSL_SERVER_DEFAULT_SATURATION   (0)

// <o HSL_SERVER_MINIMUM_HUE> Minimum Hue
// <i> Default: 0
// <i> Minimum Hue.
#define HSL_SERVER_MINIMUM_HUE   (0)

// <o HSL_SERVER_MAXIMUM_HUE> Maximum Hue
// <i> Default: 65535
// <i> Maximum Hue.
#define HSL_SERVER_MAXIMUM_HUE   (65535)

// <o HSL_SERVER_MINIMUM_SATURATION> Minimum Saturation
// <i> Default: 0
// <i> Minimum Saturation.
#define HSL_SERVER_MINIMUM_SATURATION   (0)

// <o HSL_SERVER_MAXIMUM_SATURATION> Maximum Saturation
// <i> Default: 65535
// <i> Maximum Saturation.
#define HSL_SERVER_MAXIMUM_SATURATION   (65535)

// <e HSL_SERVER_LOGGING> Enable Logging
// <i> Default: 1
// <i> Enable / disable UART Logging for HSL Server models specific messages for this component.
#define HSL_SERVER_LOGGING   (1)

// </e>

// </h>

// <<< end of configuration section >>>

// The hue update period shall not be greater than the hue UI update period
#if (HSL_SERVER_HUE_UI_UPDATE_PERIOD) < (HSL_SERVER_HUE_UPDATE_PERIOD)
#error "The HSL_SERVER_HUE_UPDATE_PERIOD shall be less than HSL_SERVER_HUE_UI_UPDATE_PERIOD."
#endif

// The saturation update period shall not be greater than the saturation UI update period
#if (HSL_SERVER_SATURATION_UI_UPDATE_PERIOD) < (HSL_SERVER_SATURATION_UPDATE_PERIOD)
#error "The HSL_SERVER_SATURATION_UPDATE_PERIOD shall be less than HSL_SERVER_SATURATION_UI_UPDATE_PERIOD."
#endif

#endif // SL_BTMESH_HSL_SERVER_CONFIG_H
