/**
 * @file
 */
#ifndef _ZW_CONFIG_RF_H_
#define _ZW_CONFIG_RF_H_

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Max Tx Power LR Configuration
// <o APP_MAX_TX_POWER_LR> The maximum allowed Tx power in deci dBm for Z-Wave Long Range network
#ifndef APP_MAX_TX_POWER_LR 
#if defined (EFR32ZG13P531F512GM48) || defined(EFR32ZG23B020F512IM48)
#define APP_MAX_TX_POWER_LR 200
#else 
#define APP_MAX_TX_POWER_LR 140
#endif
#endif

// <o ENABLE_PTI> Enables PTI
#ifndef ENABLE_PTI
#define ENABLE_PTI 0
#endif

// <o APP_MAX_TX_POWER> The maximum allowed Tx power in deci dBm for Z-Wave network
#ifndef APP_MAX_TX_POWER 
#define APP_MAX_TX_POWER      0
#endif

// <o APP_MEASURED_0DBM_TX_POWER> The deci dBm output measured at a PA setting of 0dBm
#ifndef APP_MEASURED_0DBM_TX_POWER 
#define APP_MEASURED_0DBM_TX_POWER  0
#endif
// </h>

// <<< end of configuration section >>>

#endif /* _ZW_CONFIG_RF_H_ */
