#ifndef SL_BTCTRL_PHY_SUPPORT_CONFIG_H
#define SL_BTCTRL_PHY_SUPPORT_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Bluetooth Controller Configuration

// <o SL_BT_CONTROLLER_2M_PHY_SUPPORT> Bluetooth Controller 2M PHY support
// <i> Default: SL_BT_CONTROLLER_2M_PHY_SUPPORT
// <i> Enable or disable support for the 2M PHY.
// <i> Attempting to use an unsupported PHY will result in a runtime error.
#define SL_BT_CONTROLLER_2M_PHY_SUPPORT      (1)

// <o SL_BT_CONTROLLER_CODED_PHY_SUPPORT> Bluetooth Controller Coded and SimulScan PHY support
// <i> Default: SL_BT_CONTROLLER_CODED_PHY_SUPPORT
// <i> Enable or disable support for coded and simulscan PHYs.
// <i> Attempting to use an unsupported PHY will result in a runtime error.
#define SL_BT_CONTROLLER_CODED_PHY_SUPPORT   (1)

// </h> Bluetooth Controller Configuration

// <<< end of configuration section >>>

#endif // SL_BTCTRL_PHY_SUPPORT_CONFIG_H
