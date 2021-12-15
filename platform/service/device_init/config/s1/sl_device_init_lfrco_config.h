#ifndef SL_DEVICE_INIT_LFRCO_CONFIG_H
#define SL_DEVICE_INIT_LFRCO_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <q SL_DEVICE_INIT_LFRCO_ENVREF> Enable Duty Cycling of Vref
// <i> Default: 0
// <i> Setting this configuration to 1 puts the LFRCO in duty cycle mode by
// <i> setting the ENVREF bit in CMU_LFRCOCTRL to 1 before starting the LFRCO.
// <i> This helps reduce current consumption by ~100nA in EM2, but will result
// <i> in slightly worse accuracy especially at high temperatures.
// <i> To improve the average LFRCO frequency accuracy, make sure ENCHOP
// <i> and ENDEM configs are also set.
#define SL_DEVICE_INIT_LFRCO_ENVREF          0

// <q SL_DEVICE_INIT_LFRCO_ENCHOP> Enable Comparator Chopping
// <i> Default: 1
// <i> Setting this configuration to 1 enables LFRCO comparator chopping by
// <i> setting the ENCHOP bit in CMU_LFRCOCTRL to 1 before starting the LFRCO.
// <i> Setting this bit, along with ENDEM, helps improve the average LFRCO
// <i> frequency accuracy.
#define SL_DEVICE_INIT_LFRCO_ENCHOP          1

// <q SL_DEVICE_INIT_LFRCO_ENDEM> Enable Dynamic Element Matching
// <i> Default: 1
// <i> Setting this configuration to 1 enables dynamic element matching by
// <i> setting the ENDEM bit in CMU_LFRCOCTRL to 1 before starting the LFRCO.
// <i> Setting this bit, along with ENCHOP, helps improve the average LFRCO
// <i> frequency accuracy.
#define SL_DEVICE_INIT_LFRCO_ENDEM           1

// <<< end of configuration section >>>

#endif // SL_DEVICE_INIT_LFRCO_CONFIG_H
