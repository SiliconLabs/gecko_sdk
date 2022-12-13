# How to implement a new command class

Command classes can have a controlling role and a supporting role. An application typically
uses one of the roles. For instance, an LED bulb supports Color Switch CC, but it doesn't control
Color Switch CC. The controlling role of Color Switch CC would be suited for a Z-Wave gateway as
the gateway would be controlling the color of the LED bulb based on user input in a corresponding
mobile app.

Based on the above, best practice would be to split the controlling implementation and the
supporting implementation in two different source files like it's done for CC Basic.

## Implementation of supporting part

Most command classes require two basic things for the supporting implementation:

1. Define a command handler that parses incoming frames
2. Use a REGISTER_CC() macro to register the command handler and the CC version.

Please see ZAF_types.h for descriptions of the different versions of REGISTER_CC() macros and the
corresponding type definition of the command handler.

### Association Group Information

https://sdomembers.z-wavealliance.org/wg/AWG/document/120 defines a list of command class / command
pairs that MUST be listed for the Lifeline association group. The Z-Wave Controller will ask
for the list using the Association Group Command List Get command.

ZAF will propagate this list automatically, but it requires each command class in the above registry
to register the relevant commands. REGISTER_CC_V4() must be used for this.

The following shows an example of how it's done for CC Door Lock. CC Door Lock must register two
different commands which is why the function returns 2.

```c
static uint8_t lifeline_reporting(ccc_pair_t * p_ccc_pair)
{
  p_ccc_pair->cmdClass = COMMAND_CLASS_DOOR_LOCK;
  p_ccc_pair->cmd      = DOOR_LOCK_OPERATION_REPORT;
  p_ccc_pair++;
  p_ccc_pair->cmdClass = COMMAND_CLASS_DOOR_LOCK;
  p_ccc_pair->cmd      = DOOR_LOCK_CONFIGURATION_REPORT;
  return 2;
}

REGISTER_CC_V4(..., lifeline_reporting, ...);
```

### Basic Mapping
The Device Type V2 specification dictates how a certain device type (DT) must map CC Basic to other
command classes.

For instance, the Lock DT must map CC Basic to CC Door Lock. This mapping is done automatically by
ZAF because CC Door Lock has registered mapping functions.

#### Basic Set Mapping

Basic Set mapping is done by registering a Basic Set mapping function. Please see \ref basic_set_mapper_t
for a description of the function parameters.

Below is an example from CC Door Lock:

```c
static void basic_set_mapper(ZW_APPLICATION_TX_BUFFER* pFrame)
{
  pFrame->ZW_DoorLockOperationSetV4Frame.cmdClass = COMMAND_CLASS_DOOR_LOCK;
  pFrame->ZW_DoorLockOperationSetV4Frame.cmd      = DOOR_LOCK_OPERATION_SET;
}

REGISTER_CC_V4(..., basic_set_mapper, ...);
```

#### Basic Get Mapping

Basic Get mapping is done by registering a Basic Get mapping function. Please see \ref basic_get_mapper_t
for a description of the function parameters.

Below is an example from CC Multilevel Switch:

```c
static void basic_get_mapper(uint8_t endpoint, uint8_t * p_current_value, uint8_t * p_target_value, uint8_t * p_duration)
{
  *p_current_value = cc_multilevel_switch_get_current_value_handler(endpoint);
  *p_target_value  = cc_multilevel_switch_get_target_value_handler(endpoint);
  *p_duration      = cc_multilevel_switch_get_duration_handler(endpoint);
}

REGISTER_CC_V4(..., basic_get_mapper, ...);
```

## Implementation of controlling part

A controlling implementation of a CC is rather simple as the functionality is limited to
transmission of one or more specific frames.

One example is CC_Basic_Set_tx() that can be found in CC_BasicController.c:

```c
JOB_STATUS
CC_Basic_Set_tx(
  const AGI_PROFILE* pProfile,
  uint8_t sourceEndpoint,
  uint8_t bValue,
  void (*pCbFunc)(TRANSMISSION_RESULT * pTransmissionResult))
{
  CMD_CLASS_GRP cmdGrp = {COMMAND_CLASS_BASIC, BASIC_SET};

  return cc_engine_multicast_request(
      pProfile,
      sourceEndpoint,
      &cmdGrp,
      &bValue,
      1,
      true,
      pCbFunc);
}
```

Other slightly more complex examples of such functions can be found in CC_MultilevelSwitch_Control.c.