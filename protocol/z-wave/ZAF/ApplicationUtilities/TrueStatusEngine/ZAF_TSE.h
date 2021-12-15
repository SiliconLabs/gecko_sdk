/**
 * @file
 * @brief True Status Engine used by application framework.
 * This module is used to notify the Lifeline (or any other association groups)
 * of state changes for any Command Class.
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef ZAF_TRUE_STATUS_ENGINE_H_
#define ZAF_TRUE_STATUS_ENGINE_H_

#include <stdbool.h>
#include "ZAF_types.h"
#include <ZW_transport_api.h>
#include <CC_Common.h>
#include "ZW_TransportEndpoint.h"

/**
 * The ZAF_TSE_GROUP_ID setting represents the Association Group Identifier
 * This represent the Root Device Group identifier. It is not possible to configure a
 * Multi Channel endpoint Association Group on this module,
 * for which the True Status Engine will report its status.
 */
#define ZAF_TSE_GROUP_ID                        1

/**
 * The ZAF_TSE_MAXIMUM_SIMULTANEOUS_TRIGGERS setting represents the maximum number
 * of queued status report waiting to be reported via the Association Group.
 * Note: This number should not be higher than the maximum number of frames that can be
 * queued for transmission, which is set to 5
 */
#define ZAF_TSE_MAXIMUM_SIMULTANEOUS_TRIGGERS   3

/**
 * The ZAF_TSE_DELAY_TRIGGER setting represents the delay (expressed in ms) between the status change and
 * queuing the report command to the transmit queue.
 * This setting should be as small as possible but not too small so that it would trigger network collisions.
 */
#define ZAF_TSE_DELAY_TRIGGER                   250


/* This struct is made as a template to parse incoming structs to the TSE_Trigger function */
typedef struct _s_zaf_tse_data_input_template_t_
{
  RECEIVE_OPTIONS_TYPE_EX rxOptions;
  /* There may be more members, but what follows does not matter to the ZAF_TSE */
}s_zaf_tse_data_input_template_t;

/**
 * Callback function for True Status engine.
 * Must be implemented by the caller of TSE
 * @param[out] txOptions Tx options of the current transmission
 * @param[in] pData Data relevant to the caller of TSE
 */
typedef void (*zaf_tse_callback_t)(TRANSMIT_OPTIONS_TYPE_SINGLE_EX txOptions,
                                   void* pData);

/**
* An API for the True Status engine activation.
* The True Status engine will queue up the status reporting request into a queue
* The status report are triggered after ZAF_TSE_DELAY_TRIGGER milliseconds
*
* If the pCallback was already in the queue and overwrite_previous_trigger is set to true, pData will be updated
* and the timer waiting ZAF_TSE_DELAY_TRIGGER will be restarted.
*
* @param[in]     pCallback                      Pointer to the function to callback. The callback function must
*                                               be a function taking the following arguments:
*                                                 1. TRANSMIT_OPTIONS_TYPE_SINGLE_EX rxOptionsEx
*                                                 2. void* pData
*
* @param[in]     pData                          Pointer to a data struct that will be passed in argument to
*                                               the pCallback function. The pData pointed struct MUST first
*                                               contain a RECEIVE_OPTIONS_TYPE_EX variable indicating properties
*                                               about the received frame that triggered the change. Local changes
*                                               must also include a RECEIVE_OPTIONS_TYPE_EX in the pData.
*
* @param[in]     overwrite_previous_trigger     Boolean parameter indicating if a previous trigger with the same
*                                               pCallback and the same source Endpoint in the pData should be
*                                               discarded or not. Set it to true for overwriting previous triggers
*                                               and false to stack up all the trigger messages.
*
* @return                                       True if the pCallback / pData were queued in the engine
*                                               False if the queue is full and the pCallback was not queued.
*/
bool ZAF_TSE_Trigger(zaf_tse_callback_t pCallback,
                     void* pData,
                     bool overwrite_previous_trigger);


/**
* Initialization function for the TSE.
* The function initialize the necessary timers based on the ZAF_TSE_MAXIMUM_SIMULTANEOUS_TRIGGERS setting
* The status report are triggered after ZAF_TSE_DELAY_TRIGGER milliseconds
*
* @return                           True if initialization completed successfully
*                                   False if initialization could not be done without errors
*/
bool ZAF_TSE_Init();

/**
 * Must be passed as a callback to Transport_SendRequestEP() in functions used as TSE callbacks.
 *
 * One example is CC_BinarySwitch_report_stx().
 * @param pTransmissionResult Pointer to transmission data. The argument is not used, but exists
 *                            because Transport_SendRequestEP() takes an argument being a pointer
 *                            to a function with this type.
 */
void ZAF_TSE_TXCallback(transmission_result_t * pTransmissionResult);

#endif // ZAF_TRUE_STATUS_ENGINE_H_
