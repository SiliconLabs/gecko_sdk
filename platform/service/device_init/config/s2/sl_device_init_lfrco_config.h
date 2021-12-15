#ifndef SL_DEVICE_INIT_LFRCO_CONFIG_H
#define SL_DEVICE_INIT_LFRCO_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <o SL_DEVICE_INIT_LFRCO_PRECISION> Precision Mode
// <i> Precision mode uses hardware to automatically re-calibrate the LFRCO
// <i> against a crystal driven by the HFXO. Hardware detects temperature
// <i> changes and initiates a re-calibration of the LFRCO as needed when
// <i> operating in EM0, EM1, or EM2. If a re-calibration is necessary and the
// <i> HFXO is not active, the precision mode hardware will automatically
// <i> enable HFXO for a short time to perform the calibration. EM4 operation is
// <i> not allowed while precision mode is enabled.
// <i> If high precision is selected on devices that do not support it, default
// <i> precision will be used.
// <cmuPrecisionDefault=> Default precision
// <cmuPrecisionHigh=> High precision
// <i> Default: cmuPrecisionHigh
#define SL_DEVICE_INIT_LFRCO_PRECISION          cmuPrecisionHigh

// <<< end of configuration section >>>

#endif // SL_DEVICE_INIT_LFRCO_CONFIG_H
