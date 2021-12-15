/**
 *
 * @file
 * @brief ADC utility functions
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */


#ifndef _ZAF_ADC_H_
#define _ZAF_ADC_H_

#include <stdint.h>

/**
 * Return the supply voltage level (AVDD)
 *
 * @return AVDD in millivolts
 */
uint32_t ZAF_ADC_Measure_VSupply(void);

/**
 * Initialize and enable the ADC
 */
void ZAF_ADC_Enable(void);

/**
 * Disable the ADC
 */
void ZAF_ADC_Disable(void);

#endif /* _ZAF_ADC_H_ */
