#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "FreeRTOSConfigTasks.h"  // Parameters from this task configuration file is used to configure the FreeRTOS!

void enterPowerDown(uint32_t millis);
void exitPowerDown(uint32_t millis);

#define configPRE_SLEEP_PROCESSING enterPowerDown
#define configPOST_SLEEP_PROCESSING exitPowerDown

// Include target specific configuration
#ifdef ZWAVE_SERIES_800
#include "800/FreeRTOSConfigTarget.h"
#else
#include "700/FreeRTOSConfigTarget.h"
#endif

/*
 * Converts a time in milliseconds to a time in ticks.
 * This macro overrides a macro of the same name defined in projdefs.h that gets
 * uint32_t overflow in case xTimeInMs > 4.2950e6  ~1.2 hours.
 */
#define pdMS_TO_TICKS( xTimeInMs ) \
      ( ( TickType_t ) ( ( ( uint64_t ) ( xTimeInMs ) * ( TickType_t ) configTICK_RATE_HZ ) / ( TickType_t ) 1000 ) )

#endif /* FREERTOS_CONFIG_H */
