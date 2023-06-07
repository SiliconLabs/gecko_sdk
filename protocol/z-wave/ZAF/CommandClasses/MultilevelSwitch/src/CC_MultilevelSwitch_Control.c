/**
 * @file
 * Handler for Command Class Multilevel Switch.
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include <CC_MultilevelSwitch_Control.h>
#include <ZW_TransportLayer.h>

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

typedef struct _multi_level_switch_set_t_
{
  uint8_t value;
  uint8_t dimmingDuration;
}multi_level_switch_set_t;


/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/
CMD_CLASS_GRP cmdGrp;

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/

JOB_STATUS
CmdClassMultilevelSwitchStartLevelChange(
  AGI_PROFILE* pProfile,
  uint8_t sourceEndpoint,
  VOID_CALLBACKFUNC(pCbFunc)(TRANSMISSION_RESULT * pTransmissionResult),
  CCMLS_PRIMARY_SWITCH_T primarySwitch,
  CCMLS_IGNORE_START_LEVEL_T fIgnoreStartLevel,
  CCMLS_SECONDARY_SWITCH_T secondarySwitch,
  uint8_t primarySwitchStartLevel,
  uint8_t duration,
  uint8_t secondarySwitchStepSize)
{
  ccc_pair_t ccc_pair = {COMMAND_CLASS_SWITCH_MULTILEVEL_V4, SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V4};
  uint8_t payload[] = {
    (uint8_t)((primarySwitch << 6) | (fIgnoreStartLevel << 5) | (secondarySwitch << 3)),
    primarySwitchStartLevel,
    duration,
    secondarySwitchStepSize
  };
  
  return cc_engine_multicast_request(pProfile,
      sourceEndpoint,
      &ccc_pair,
      payload,
      sizeof(payload),
      true,
      pCbFunc);
}


JOB_STATUS
CmdClassMultilevelSwitchStopLevelChange(
  AGI_PROFILE* pProfile,
  uint8_t sourceEndpoint,
  VOID_CALLBACKFUNC(pCbFunc)(TRANSMISSION_RESULT * pTransmissionResult))
{
  cmdGrp.cmdClass = COMMAND_CLASS_SWITCH_MULTILEVEL_V4;
  cmdGrp.cmd = SWITCH_MULTILEVEL_STOP_LEVEL_CHANGE_V4;

  return cc_engine_multicast_request(
      pProfile,
      sourceEndpoint,
      &cmdGrp,
      NULL,
      0,
      true,
      pCbFunc);
}


JOB_STATUS
CmdClassMultilevelSwitchSetTransmit(
  AGI_PROFILE* pProfile,
  uint8_t sourceEndpoint,
  VOID_CALLBACKFUNC(pCbFunc)(TRANSMISSION_RESULT * pTransmissionResult),
  uint8_t value,
  uint8_t duration)
{
  multi_level_switch_set_t multi_level_switch_set;
  multi_level_switch_set.value = value;
  multi_level_switch_set.dimmingDuration = duration;

  cmdGrp.cmdClass = COMMAND_CLASS_SWITCH_MULTILEVEL_V4;
  cmdGrp.cmd = SWITCH_MULTILEVEL_SET_V4;


  return cc_engine_multicast_request(
      pProfile,
      sourceEndpoint,
      &cmdGrp,
      (uint8_t*)&multi_level_switch_set,
      sizeof(multi_level_switch_set_t),
      true,
      pCbFunc);

}

