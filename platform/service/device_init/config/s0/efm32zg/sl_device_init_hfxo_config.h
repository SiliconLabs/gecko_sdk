#ifndef SL_DEVICE_INIT_HFXO_CONFIG_H
#define SL_DEVICE_INIT_HFXO_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <o SL_DEVICE_INIT_HFXO_MODE> Mode
// <i>
// <cmuOscMode_Crystal=> Crystal oscillator
// <cmuOscMode_AcCoupled=> AC-coupled buffer
// <cmuOscMode_External=> External digital clock
// <i> Default: cmuOscMode_Crystal
#define SL_DEVICE_INIT_HFXO_MODE           cmuOscMode_Crystal

// <o SL_DEVICE_INIT_HFXO_FREQ> Frequency <4000000-24000000>
// <i> Default: 24000000
#define SL_DEVICE_INIT_HFXO_FREQ           24000000

// <o SL_DEVICE_INIT_HFXO_BOOST> Boost
// <0=> 50% boost
// <1=> 70% boost
// <2=> 80% boost
// <3=> 100% boost
// <i> Default: 3
#define SL_DEVICE_INIT_HFXO_BOOST          3
// <<< end of configuration section >>>

#endif // SL_DEVICE_INIT_HFXO_CONFIG_H
