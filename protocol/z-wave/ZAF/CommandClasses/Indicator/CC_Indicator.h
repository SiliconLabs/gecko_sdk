/**
 * Indicator command class version 3
 *
 * @copyright 2019 Silicon Laboratories Inc.
 */

#ifndef CC_INDICATOR_H_
#define CC_INDICATOR_H_

#include <ZAF_types.h>
#include <ZW_classcmd.h>
#include <CC_Common.h>
#include <ZW_TransportEndpoint.h>

/*
 * Local defines to get rid of context sensitive define names from ZW_classcmd.h
 */

/* Indicator IDs */
#define INDICATOR_IND_NA            INDICATOR_SET_NA_V3
#define INDICATOR_IND_NODE_IDENTIFY INDICATOR_SET_NODE_IDENTIFY_V3

/* Property IDs */
#define INDICATOR_PROP_ON_OFF_PERIOD INDICATOR_SET_ON_OFF_PERIOD_V3
#define INDICATOR_PROP_ON_OFF_CYCLES INDICATOR_SET_ON_OFF_CYCLES_V3
#define INDICATOR_PROP_ON_TIME       INDICATOR_SET_ONE_TIME_ON_OFF_PERIOD_V3

/* Masks etc. */
#define INDICATOR_OBJECT_COUNT_MASK INDICATOR_SET_PROPERTIES1_INDICATOR_OBJECT_COUNT_MASK_V3
#define INDICATOR_RESERVED_MASK     INDICATOR_SET_PROPERTIES1_RESERVED_MASK_V3
#define INDICATOR_RESERVED_SHIFT    INDICATOR_SET_PROPERTIES1_RESERVED_SHIFT_V3

/**
 * Struct used to pass operational data to TSE module
 */
typedef struct s_CC_indicator_data_t_
{
  RECEIVE_OPTIONS_TYPE_EX rxOptions; /**< rxOptions */
  uint8_t indicatorId; /**< Indicator Id */
} s_CC_indicator_data_t;

/**
 * Send report when change happen via lifeLine by INDICATOR_SET
 *
 * Callback used by TSE module. Refer to @ref ZAF_TSE.h for more details.
 *
 * @param txOptions txOptions
 * @param pData Command payload for the report
 */
void CC_Indicator_report_stx(TRANSMIT_OPTIONS_TYPE_SINGLE_EX txOptions, void* pData);

/**
 * Resets the indicator CC properties to their "off" values if the
 * indicator is no longer active.
 *
 * If the application manually de-activates the Indicator (e.g. learn mode), it should call
 * this function to have the CC Indicator values refreshed before it reports
 * its state to the Lifeline destinations.
*/
void CC_Indicator_RefreshIndicatorProperties(void);


#endif /* CC_INDICATOR_H_ */
