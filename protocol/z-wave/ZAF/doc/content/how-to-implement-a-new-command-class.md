# How to implement a new command class

## General informations

An essential feature of the ZAF is the communication through Command Classes. For this purpose, each 
of the Command Classes has a C module where incoming commands are handled, and outgoing 
commands are transmitted.

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
2. Use REGISTER_CC_V5() to register the command handler and the CC version.

Please see ZAF_types.h for descriptions REGISTER_CC_V5() and the corresponding type definition of
the command handler.

### Association Group Information

https://sdomembers.z-wavealliance.org/wg/AWG/document/120 defines a list of command class / command
pairs that MUST be listed for the Lifeline association group. The Z-Wave Controller will ask
for the list using the Association Group Command List Get command.

ZAF will propagate this list automatically, but it requires each command class in the above registry
to register the relevant commands. Use REGISTER_CC_V5() for this.

The following shows an example of how it's done for CC Door Lock. CC Door Lock must register two
different commands which is why the function returns 2. Other command classes register only one
command and must then return 1.

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

REGISTER_CC_V5(..., lifeline_reporting, ...);
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

REGISTER_CC_V5(..., basic_set_mapper, ...);
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

REGISTER_CC_V5(..., basic_get_mapper, ...);
```

### Parsing incoming frames

Each CC implementation defines a handler, e.g. `CC_MultilevelSwitch_handler()`. This function 
extracts the received frame for a given Command Class. The function must be registered using a 
REGISTER_CC_V5 macro. Normally, the frame is carrying a “Set” or “Get” Command 
that results in a function call for reading or writing data. All commands are handled by the command class itself.

Example:
```c
static received_frame_status_t CC_MultilevelSwitch_handler(
    cc_handler_input_t * input,
    cc_handler_output_t * output)
{
  switch (input->frame->ZW_Common.cmd)
  {
    case SWITCH_MULTILEVEL_GET:
      // Parse SWITCH_MULTILEVEL_GET
      break;
    default:
      // Unknown command
      return RECEIVED_FRAME_STATUS_NO_SUPPORT;
  }
  return RECEIVED_FRAME_STATUS_SUCCESS;
}

REGISTER_CC_V5(COMMAND_CLASS_SWITCH_MULTILEVEL, SWITCH_MULTILEVEL_VERSION_V4, CC_MultilevelSwitch_handler, ...);
```


## Implementation of controlling part

A controlling implementation of a CC is rather simple as the functionality is limited to
transmission of one or more specific frames.

One example is CC_Basic_Set_tx() that can be found in CC_BasicController.c:

```c
zaf_job_status_t CC_Basic_Set_tx(
  agi_profile_t const * const p_profile,
  const uint8_t source_endpoint,
  const uint8_t value,
  const bool use_supervision,
  ZAF_TX_Callback_t callback)
{
  ccc_pair_t ccc_pair = {COMMAND_CLASS_BASIC, BASIC_SET};

  return cc_engine_multicast_request(
      p_profile,
      source_endpoint,
      &ccc_pair,
      (uint8_t *)&value,
      sizeof(value),
      use_supervision,
      callback);
}
```

A controlling device, e.g., a wall switch, may want to send a Basic Set command. The implementation
of Basic Set transmission is shown above. The `value` parameter is specific for the Basic Set
command. The remaining four parameters are recommended as generic parameters: `p_profile`,
`source_endpoint`, `use_supervision` and `callback`. These parameters are detailed
below.

Another slightly more complex example of such a function can be found in `CC_MultilevelSwitch_Control.c`.

Some command classes might not offer the profile and the source endpoint, but instead rely on an
index or a pointer to the configuration that contains the AGI profile and the source endpoint. One
example of such an API is `CC_Notification_TriggerAndTransmit()`.

**p_profile (AGI profile)**

The `p_profile` is required together with `source_endpoint` for ZAF to be able to look up
the right association group. The profile must match one of those defined in the CC AGI
configuration. Alternatively, if NULL is passed as the profile, the ZAF will default to the Lifeline
profile.

**source_endpoint**

If the application is configured with endpoints, `source_endpoint` must be set to the endpoint
that triggers the command.
An example could be a device with two temperature sensors represented by endpoint 1 and 2. This
device could transmit a Basic Set if the temperature drops under a certain threshold. In that case,
`CC_Basic_Set_tx()` would need to be invoked with the endpoint that represents the relevant
temperature sensor.
If an application does not configure endpoints, `source_endpoint` must be set to zero.

**use_supervision**

This parameter offers the application developer the option to use Supervision for a certain
command. Supervision might be important in the case of a window sensor in an alarm system to make
sure that a Notification Report, signaling that a window was opened, is received and decrypted by
the destination node. An example where Supervision might be of less relevance could be a wall switch
sending a Basic Set or a Binary Switch set. In this scenario, an end user would probably just press
the button again if a frame was lost and the light didn't turn on in the first attempt.

**callback**

In case the application logic requires a callback whenever a transmission succeeded or failed, the
`callback` parameter can be used. This parameter is not required, but offering it in the API adds
some flexibility to the application developer.

## File structure

Each Command Class should have following folders:

- `inc` for public headers
- `src` for private headers and source files.

## Version
The command class version must be set using REGISTER_CC_V5().

Example:
```c
REGISTER_CC_V5(COMMAND_CLASS_DOOR_LOCK, DOOR_LOCK_VERSION_V4, ...);
```
