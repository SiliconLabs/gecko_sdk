#ifndef SL_DEVICE_INIT_LFXO_CONFIG_H
#define SL_DEVICE_INIT_LFXO_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <o SL_DEVICE_INIT_LFXO_MODE> Mode
// <i>
// <cmuOscMode_Crystal=> Crystal oscillator
// <cmuOscMode_AcCoupled=> AC-coupled buffer
// <cmuOscMode_External=> External digital clock
// <i> Default: cmuOscMode_Crystal
#define SL_DEVICE_INIT_LFXO_MODE           cmuOscMode_Crystal

// <o SL_DEVICE_INIT_LFXO_BOOST> Boost
// <i>
// <cmuLfxoBoost70=> 70% boost
// <cmuLfxoBoost100=> 100% boost
// <cmuLfxoBoost70Reduced=> Reduced 70% boost
// <cmuLfxoBoost100Reduced=> Reduced 100% boost
// <i> Default: cmuLfxoBoost70
#define SL_DEVICE_INIT_LFXO_BOOST          cmuLfxoBoost70

// <o SL_DEVICE_INIT_LFXO_PRECISION> LFXO precision in PPM <0-65535>
// <i> Default: 500
#define SL_DEVICE_INIT_LFXO_PRECISION      100

// <o SL_DEVICE_INIT_LFXO_TIMEOUT> Startup Timeout Delay
// <i>
// <_CMU_CTRL_LFXOTIMEOUT_8CYCLES=> 8 cycles
// <_CMU_CTRL_LFXOTIMEOUT_1KCYCLES=> 1K cycles
// <_CMU_CTRL_LFXOTIMEOUT_16KCYCLES=> 16K cycles
// <_CMU_CTRL_LFXOTIMEOUT_32KCYCLES=> 32K cycles
// <_CMU_CTRL_LFXOTIMEOUT_DEFAULT=> Default
// <i> Default: _CMU_CTRL_LFXOTIMEOUT_DEFAULT
#define SL_DEVICE_INIT_LFXO_TIMEOUT           _CMU_CTRL_LFXOTIMEOUT_DEFAULT
// <<< end of configuration section >>>

#endif // SL_DEVICE_INIT_LFXO_CONFIG_H
