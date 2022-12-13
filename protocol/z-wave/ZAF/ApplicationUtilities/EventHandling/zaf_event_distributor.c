/**
 * @file
 * @brief ZAF Event distributor source file
 * @copyright 2019 Silicon Laboratories Inc.
 */
#include <EventDistributor.h>
#include <zaf_event_distributor.h>
#include <zaf_event_distributor_core_config.h>

//#define DEBUGPRINT
#include "DebugPrint.h"

bool zaf_event_distributor_distribute(void)
{
  const SEventDistributor *event_distributor;

  event_distributor = zaf_event_distributor_get();

  return (EventDistributorDistribute(event_distributor, ZAF_EVENT_DISTRIBUTOR_CORE_CONFIG_TIMEOUT, 0) != 0xFFFFFFFF);
}
