# Important Changes {#important-changes}

The changes described in this file will possibly break the build and/or functionality of an
existing application. The description serves the purpose of helping to fix the failing build.

# 7.20.0 {#section-7-20-0}

## ZAF Application Name
Storing the name of applications is now handled by the `zaf_appname` component.  
The name is stored as a string by default.
By installing an additional component, `zaf_appname_nvm`, the name can be saved
to the non-volatile memory as well.  
When multiple Z-Wave devices are connected, this feature can speed up the
process of identifying which application is flashed on each device.

## ZAF Job Helper
This module is no longer recommended to be used in new applications. The main
use case for this module was to transmit different frames for the same event.
The new applications should leverage the ZAF Transport Queue instead.
For applications that still wants to use this module it has been moved to its
own component: `zaf_job_helper.slcc`

## ZAF Transport module

ZW_TransportEndpoint was refactored and many of local data has been removed.
Functions `Transport_SendRequestEP()` and `Transport_SendResponseEP()`
were replaced with a common function `ZAF_Transmit()`
Type of `callback_function` in `ZAF_Transmit(buffer, len, txOptions, callback_function)`
is now `ZAF_TX_Callback_t`
Note that `ZAF_Transmit()` does not set `S2_TXOPTION_VERIFY_DELIVERY` by default,
as it was case with `Transport_SendRequestEP()`. Setting of this flag is possible in
`ZAF_Transmit()`, by enabling it in `TransmitSecurityOptions`.
It is not recommended to use this API directly, applications should use the ZAF 
Transport Queue to ensure that only one frame is sent from the application to 
the protocol at one time.

### ZAF_Transmit migrated to zaf_transport_tx
In order to ensure a single entry point for frames from the application to the 
protocol, ZAF_Transmit is not being called directly by Command Classes.

## ZAF Transport Queue
This module implements a transport queue in the application level. This queue
ensures that there is only a single entry point for a frame from the 
application. This adds a new feature to applications, the ability to "send and 
forget", which means the user only has to send to the queue, and the rest of the 
process is taken care of. i.e. Send Central Scene Notification and Send Basic 
Set in sequence. The queue size is configurable and it can bet set by 
`ZAF_TRANSPORT_CONFIG_QUEUE_SIZE`, the default is 2.


## ZAF TX Mutex removed
This module is used to ensure that a shared buffer frame was only used by one
module at the same time. It was very relevant for 500 series to reduce the RAM
usage as no stack was available for the tasks, however it became irrelevant for
700 series and forward. This module was only being used by the ZW Transport 
Multicast module at this point. The buffer was moved to the module itself and 
the TX Mutex module was removed, therefore the `ZAF_tx_mutex.h` no longer 
exists.

## Merge agi.c/h into CC_AssociationGroupInfo.c/h
The agi.c/h module does not exist anymore as the contents 
of the files have been merged into CC_AssociationGroupInfo. This should reduce some complexity
since data does not have to be passed between the different modules and reduce flash and ram consumption.

## ZAF Event Helper module removed
This modules was only used by the event distributor soc to enqueue events into 
the application event queue therefore this functionality was moved into the 
event distributor soc.

The interface changes are listed below:

| **Old name**                          |      | **New name**                                         |
|---------------------------------------|------|------------------------------------------------------|
| `ZAF_EventHelperInit`                 | `->` | Not needed anymore                                   |
| `ZAF_EventHelperIsInitialized`        | `->` | Not needed anymore                                   |
| `ZAF_EventHelperEventEnqueue`         | `->` | `zaf_event_distributor_enqueue_app_event`            |
| `ZAF_EventHelperEventEnqueueFromISR`  | `->` | `zaf_event_distributor_enqueue_app_event_from_isr`   |

The functions that still exist takes the same arguments as before. They are 
defined in `zaf_event_distributor_soc.h`

## Application name configurable
Each application's name is configurable. It can be changed by specifying the
configuration entry named `ZAF_APP_NAME` in the SLC project description.
The printing of the application's name, reset reason, and SDK version was moved to ZAF_PrintAppInfo().

## Eliminating the config_app.h files
config_app.h files were eliminated from sample applications, and the content of the headers 
were moved to the project source files. Exceptions to this are version numbers, previously stored in these files.
Version numbers have been moved to a configurable SLC component.
The APP_VERSION_MAJOR, APP_VERSION_MINOR, and APP_VERSION_PATCH numbers 
are now configurable via the zw_version component in the studio GUI. 
Users still get the original Silicon Labs version numbers by default, 
but it is also possible to change them as described above.

## Common hardware functions
Each application would implement each own `<App>_hw_init` function and have 
their own `<App>_hw.h` header. The applications that go to deep sleep also had
their own `<APP>_hw_deep_sleep_wakeup_handler` function. These two common 
functions have been consolidate in a `app_hw.h` as `app_hw_init` and 
`app_hw_deep_sleep_wakeup_handler`. `app_hw_init` MUST be implemented by the 
application while `app_hw_deep_sleep_wakeup_handler` should only be implemented
by applications that can go into deep sleep.

## Application's source code

Application's source codes were moved from \<application_name\>.c to app.c file. 
The app.h headers were also removed with the function `app_init()`. Because of this 
the function calls were removed from the main.c file.

## Board indicator moved into ZAF

Board indicator LED is initialized in ZAF_Init() and the default idle status is set also in it. 
`Board_IndicateStatus()` is available so it can be used freely in the code.

## Command Classes

### New version of Command Classes handlers

New macro `REGISTER_CC_V5()` has been created and can be used to initialize Command Classes.
This macro requires CC handler that takes only input and output structure as arguments.
See `CC_BinarySwitch_handler(cc_handler_input_t * input,  cc_handler_output_t * output)` as example.
This makes possible for CC to exit with status WORKING, without a need to pass duration parameter to Supervision CC,
or to call Supervision Report directly, as it was the case so far.

`REGISTER_CC_V5()` is supported in all Command Classes that support timed change, and their handlers were updated accordingly.
List of handlers compatible with `REGISTER_CC_V5()`:
 * CC_BinarySwitch_handler()
 * CC_ColorSwitch_handler()
 * CC_DoorLock_handler()
 * CC_MultilevelSwitch_handler()
 * CC_MultiChannel_handler()

### Folder structure and private/public headers
Some command classes have more than two source files and header files. This is 
because the command class contains a lot of logic therefore splitting into 
more than one source and one header file makes sense for readability.
In order to allow interaction between two source files, private header were 
introduced and to avoid confusion a new folder structure is used. The source 
files and private header are placed in `src` while the public headers are 
placed in `inc`.

All Command Classes have been structured to have `inc`, `src` and in some cases, `config` folder.
Header files located in `config` folder contain values configurable in Simplicity Studio.

### CC Basic

`CC_Basic_Set_handler()` was removed. This function is no longer required by
applications as ZAF handles Basic Command Class mapping (assuming all relevant
Command Classes implement a Basic Set mapper function).

### CC Central Scene
Configuration of Command Class Central Scene was migrated to Z-Wave Command Class
Configurator and must be configured in \<app\>.cc_config. More details can be found
[here](ZAF/tool/cc_configurator/README.md).


The configuration of cc_central_scene_get_supported_key_attributes was removed
from `zw_cc_central_scene` component. Values can either be set using Z-Wave Command Class
Configurator, or they are automatically calculated by Command Class.

- Function `cc_central_scene_set_configuration` was removed since this operation is only done internally in the Command Class.
- `cc_central_scene_get_supported_key_attributes` were made static as it is only used internally.
- `cc_central_scene_get_configuration` was removed as obsoleted. Slow refresh value
  is now used only internally in CC_CentralScene.c and can be accessed directly.
- Refactored function `CommandClassCentralSceneNotificationTransmit()`:
  - Renamed to `cc_central_scene_notification_tx()`
  - Removed `sourceEndpoint` argument. The function will always use `ROOT` as source endpoint.

### CC Door Lock
It is now the responsibility of the Command Class to ensure that the TSE actions are managed.
All TSE-related functionalities have been moved from the applications to the Door Lock CC.
This includes functions `cc_door_lock_handle_working_state()` and `CC_DoorLock_operation_report_notifyWorking()`

Hardware handling has been moved out of CC Door Lock, leaving the command class with the software logic only.

#### Supervision handling moved to CC
Handling of Supervision Get for Door Lock Operation Set has been moved from application
to Command Class.

Function `cc_supervision_get_received_handler` no longer needs to be implemented in the
app.

New `REGISTER_CC_V5` made it possible to remove `CmdClassSupervisionReportSend()` with status Working
and leave it to CC Supervision to handle the working case.

### CC Multi Channel
Configuration of Command Class Multi Channel (endpoints) was migrated to Z-Wave Command Class
Configurator and must be configured in \<app\>.cc_config. More details can be found
[here](ZAF/tool/cc_configurator/README.md).

Configuring whether endpoints are identical or not must be done in Studio.

As a result of the migration, Transport_AddEndpointSupport() was removed.

To comply with the naming scheme, the following two SLC components were renamed:
* zw_cc_multichannelcontrol -> zw_cc_multi_channel_control
* zw_cc_multichannelsupport -> zw_cc_multi_channel_support

### CC Notification
The source code in notification.c has been moved to CC_Notification.c and notification.c has been
removed.

Notification types have been moved into `cc_notification_types.h` and states/events have been
moved into `cc_notification_events.h`. This is done to prepare for automatic generation of
these two files based on the types and states/events defined in the Z-Wave specification.

CC_NOTIFICATION_MAX_EVENTS_PER_NOTIFICATION was removed as the number of configured events/states
can be derived from the CC configuration.

The CC configuration syntax was simplified to no longer require `state_event:` for each
state/event listed under `state_events:`. This is a breaking change and existing `cc_config`
files must be updated. More details can be found [here](ZAF/tool/cc_configurator/README.md).

Existing syntax:
```yaml
state_events:
  - state_event: NOTIFICATION_EVENT_POWER_MANAGEMENT_OVERLOADED_DETECTED
  - state_event: NOTIFICATION_EVENT_POWER_MANAGEMENT_LOAD_ERROR
```

New syntax:
```yaml
state_events:
  - NOTIFICATION_EVENT_POWER_MANAGEMENT_OVERLOADED_DETECTED
  - NOTIFICATION_EVENT_POWER_MANAGEMENT_LOAD_ERROR
```

### CC Wake Up
Applications that included the Command Class Wake Up had to call three functions
in response to the `EVENT_SYSTEM_LEARNMODE_FINISHED` event. These functions were
`CC_WakeUp_stayAwake10s`, `CC_WakeUp_AutoStayAwakeAfterInclusion` and 
`CC_WakeUp_startWakeUpNotificationTimer` if the inclusion state is not excluded.
Now this is handled by ZAF. This is done by implementing the weak function 
`zaf_learn_mode_finished`.

## Application Events Abstracted
Some sample applications contained events that contained hardware specific name.
Those names were based on how the Silicon Labs port would generate those events.

Many events had the BUTTON keyword and it was removed from event names so 
`EVENT_APP_BUTTON_<event>` becomes `EVENT_APP_<event>`. Below is the list 
of renamed events for each application that did **NOT** follow this pattern.

### zwave_soc_switch_on_off

| **Old name**                          |      | **New name**           |
|---------------------------------------|------|------------------------|
| `EVENT_APP_BUTTON_TOGGLE_SHORT_PRESS` | `->` | `EVENT_APP_TOGGLE_LED` |
| `EVENT_APP_BUTTON_TOGGLE_HOLD`        | `->` | `EVENT_APP_SEND_NIF`   |

### zwave_soc_key_fob

| **Old name**                                    |      | **New name**                               |
|-------------------------------------------------|------|--------------------------------------------|
| `EVENT_APP_BUTTON_UP_ASSOCIATION_GROUP_ADD`     | `->` | `EVENT_APP_ASSOCIATION_GROUP_ADD_START`    |
| `EVENT_APP_BUTTON_UP_ASSOCIATION_GROUP_REMOVE`  | `->` | `EVENT_APP_ASSOCIATION_GROUP_REMOVE_START` |

## New ZAF responsibilities
In order to make apps smaller and easier to start with, all implementation common to all apps,
and that does not require additional configuration from the user, has been moved to ZAF.

### Features moved out of apps to ZAF
All sample application would keep a local pointer to the `AppHandles` passed by 
the `ApplicationTask`. This parameter is already passed to ZAF in the `ZAF_Init`
therefore the Applications don't need to keep a local pointer anymore. They 
should use the functions from `ZAF_Common_interface.h` to retrieve the data 
needed from the `AppHandles`

They also had to call `zaf_event_distributor_init` in the `ApplicationTask`. 
This is not necessary anymore as this functions is called by ZAF in the 
`ZAF_Init`

The sample applications that support the CC Firmware Update also had to call
`cc_firmware_update_send_status_report` in `ApplicationTask` after `ZAF_Init`.
This is not needed anymore because the CC Firmware Update handles it internally.

### New weak function on EVENT_SYSTEM_LEARNMODE_FINISHED
A new weak function was introduced in ZAF, `zaf_learn_mode_finished`. This 
function can be used by Command Classes that need to execute an action in 
response to this event. Currently only the Command Class Wake Up utilizes this
functionality.

# 7.19.1 {#section-7-19-1}

## Command Classes

### CC Configuration
The YAML configuration of CC Configuration in \<app\>.cc_config now requires "number" and "file_id"
for each parameter. This requirement was added to allow addition/removal of parameters across
different application firmware versions. See MultilevelSensor.cc_config for an example.

The output array generated in cc_configuration_config.c is now sorted by "number". The
Z-Wave Command Class Configurator (Z3C) will automatically sort the items, but in case a previously
auto-generated file is manually modified, make sure that the array stays sorted by "number".
The sorting is not required as of this release, but will be required later as it opens for some
flash usage optimizations in CC_Configuration.c.

### CC Central Scene

`cc_central_scene_properties` was renamed to `cc_central_scene_identical`. If you used this variable in your code, please change any occurrences of it to the new name.

# Important Changes in 7.19.0 {#section-7-19-0}

In general, these changes are designed to allow the user to configure their projects in the Simplicity Studio Component Editor,
rather than by updating code or header files. A new Z-Wave Command Class Configurator has been added to Simplicity Studio
to accommodate the more advanced Z-Wave command classes that require complex configurations. More details can be found [here](ZAF/tool/cc_configurator/README.md).

In order to make applications smaller and easier to start with, all implementation that was common to all applications
and that did not require additional configuration from the user has been moved to the Z-Wave Application Framework (ZAF).

## Configurable Parameters Have Been Moved from config_app.h

A number of parameters, previously located in `config_app.h`, that were mandatory for application configuration
now can be configured using the Simplicity Studio GUI and are moved out of this header file.
This makes it easier to set up all mandatory configurations at the moment when the new project is created in Studio.

See [Command Classes](#cc-id) for more details about specific command class configuration.

### Role Type and Device Type

`APP_ROLE_TYPE` was moved to `zaf_config_role_type.h`.
`DEVICE_OPTION_MASK` was renamed to `ZAF_CONFIG_DEVICE_OPTION_MASK` and it was also
moved to `zaf_config_role_type.h`.
Both defines are automatically set by `role_type` components for end devices.

Generic and Specific type can be configured in the GUI:
- `GENERIC_TYPE` was renamed to `ZAF_CONFIG_GENERIC_TYPE`
- `SPECIFIC_TYPE` was renamed to `ZAF_CONFIG_SPECIFIC_TYPE`

They are moved to `zaf_config.h` and can be configured in the "Z-Wave ZAF Component" component.

### Requested Security Keys

The configuration of security keys to request from the controller, previously defined as
`REQUESTED_SECURITY_KEYS`, was moved from config_app.h to `zaf_config.h`.
Instead of using `REQUESTED_SECURITY_KEYS`, it is now possible to select any combination of keys in "Z-Wave ZAF Component":

- `ZAF_CONFIG_REQUEST_KEY_S0`
- `ZAF_CONFIG_REQUEST_KEY_S2_UNAUTHENTICATED`
- `ZAF_CONFIG_REQUEST_KEY_S2_AUTHENTICATED`
- `ZAF_CONFIG_REQUEST_KEY_S2_ACCESS`

### Number of End Points

The configuration of number of end points, previously defined as `NUMBER_OF_ENDPOINTS`,
was renamed to `ZAF_CONFIG_NUMBER_OF_END_POINTS` and moved  to `zaf_config.h`.

## Application Initialization 

`ZAF_setApplicationData()` was removed. The parameters of this function must instead be passed to `ZAF_Init()`.

For Serial API specifically, `SetTaskHandle()` (and `GetTaskHandle()`) was introduced and must be used
instead of `ZAF_setApplicationData()`. `ZAF_setAppProtocolConfig()` must be used instead of `ZAF_Init()` to set
the protocol configuration.

`ZAF_setAppHandle()` was moved to `ZAF_Init()` and no longer has to be invoked from the application.

### ZAF_ApplicationEvents.h

Application events like `EAPPLICATIONEVENT_APP` were moved to `ZAF_ApplicationEvents.h` as they are all
the same for most apps. Additional events can be added to the file if desired.

### ZAF_Init()

The parameters of `ZAF_Init()` have changed. See the description of `ZAF_Init()` for information
about which parameters it takes.

`ZAF_Init()` MUST be invoked from the task function passed to `ZW_ApplicationRegisterTask()`.
For the Z-Wave apps included in the SDK, this function is named `ApplicationTask()`.

### AssociationInitEndpointSupport()

In a previous release, the need for `AssociationInitEndpointSupport()` was removed as ZAF takes care
of the association root group mapping. The function was kept for backwards capability, but is now
removed.

### Initialization of Command Classes

Command Classes manage their own initialization and so the application no longer needs to do it.
Each Command Class uses `REGISTER_CC_V4()` to register its init and reset functions.
This ensures that the initialization and reset are performed by ZAF.

### Read/Write to NVM

The functions used to read/write from Non-Volatile Memory `zpal_nvm_read(handle, key, object, object_size)`
and `zpal_nvm_write(handle, key, object, object_size)` are replaced by `ZAF_nvm_app_read(key, object, object_size)`
and `ZAF_nvm_app_write(key, object, object_size)`. The new functions work without needing a pointer to 
the file system as an input. The application file system must be opened by calling `ZAF_nvm_app_init()`
at initialization so it is avaliable to be used by `ZAF_nvm_app_read()` and `ZAF_nvm_app_write()`.

ZAF filesystem can be used with `ZAF_nvm` module. `ZAF_FILE_ID_BASE` was removed. Now ZAF file IDs start from 0.

### Removed LED_RGB and Timer Components

Timer components were used to control `RGB_LED`, but these components are replaced by the Silicon Labs component "SL_SIMPLE_RGB_PWM_LED". 
After this release these components are no longer available.

The following functions were removed from *platform/SiliconLabs/AppsHW/inc/board.h*:

- `Board_RgbLedInitPwmTimer()`
- `Board_RgbLedEnablePwm()`
- `Board_RgbLedDisablePwm()`
- `Board_RgbLedSetPwm()`

## New ZAF Responsibilities

In order to make applications smaller and easier to start with, all implementation that was common to all applications
and that did not require additional configuration from the user has been moved to ZAF.

### Features Moved Out of Apps to ZAF

#### Learn Mode

ZAF is now responsible for the handling of Learn Mode.

#### Device Reset Local

ZAF is also responsible for handling the device reset using the "NVM SOC" component.

#### Removed State Machine from Applications

All sample applications had a state machine implemented into them. It is no longer needed, making 
the applications simpler and allowing more responsibility to be given to ZAF.
Applications can still implement a state machine if the use case requires but our sample applications
use cases do not require state machines.

#### Stay Awake

An application no longer has to pass a stay awake function to ZAF as the stay awake functionality
is now handled by ZAF. The callback parameter was removed from `ZAF_Init()` and from
`Transport_OnApplicationInitSW()`.

Also, `EZWAVERECEIVETYPE_NODE_UPDATE` and `EZWAVERECEIVETYPE_STAY_AWAKE` need not trigger a call
to a stay awake function as this is now handled inside ZAF.

ZAF will determine the stay awake time from the role type and from whether CC Wake Up is linked or
not.

`ZAF_FLiRS_StayAwake()` and `CC_WakeUp_stayAwakeIfActive()` must no longer be used and are replaced by
`zaf_stay_awake()`.

### Event Distributor

All sample applications implemented their own event distributor component. However, it was the same
between all sample applications, with the only difference being if the application allowed for pooling
or full event driven. This logic has been moved into ZAF in the component event distributor and the 
logic has not changed.

Two types of distributor have been implemented: NCP and SOC

#### NCP

This is the event distributor used in Serial API and it is the event distributor that should be
used in all applications that run the host in a separated chip.

#### SOC

This is the event distributor used in all other sample applications and it should be used in all
applications that run controller and host on the same chip.

#### NVM SOC

All SOC sample applications use this component as it contains all the NVM logic expected to be 
common among them. It is responsible for resetting the APP NVM, Load Default Configuration and 
Setting Default Configuration. It contains handlers that can be used for custom behaviors in
the application level.

### AppPowerDownCallBack

This function replaces the ZAF Power Module Wrapper for more optimized code. Instead of registering a callback
which was called as the last step just before the chip entered deep sleep hibernate, a new weakly-defined function 
`ZW_AppPowerDownCallBack` is provided. 

### ZAF Power Module Wrapper - Deprecated

The ZAF Power Module Wrapper is no longer supported. It was responsible for registering functions that would
be called as the last step just before the chip enters deep sleep hibernate. 

It is important to highlight that the protocol still supports the `EZWAVECOMMANDTYPE_PM_SET_POWERDOWN_CALLBACK`
for registering such callbacks at run time. However, we recommend that the weakly-defined function 
`ZW_AppPowerDownCallBack` is used instead. Since the DeepSleepTimer is no longer using the protocol
command, we reduced the `MAX_POWERDOWN_CALLBACKS` from 4 to 3.

## Components Renamed

The following component IDs were renamed in order to comply with the snake case naming convention

- `zw_cc_centralscene` renamed to `zw_cc_central_scene`
- `zw_cc_colorswitch` renamed to `zw_cc_color_switch` 
- `zw_cc_doorlock` renamed to `zw_cc_door_lock` 
- `zw_cc_multilevelsensor` renamed to `zw_cc_multilevel_sensor` 
- `zw_cc_multilevelswitchsupport` renamed to `zw_cc_multilevel_switch_support`

## Command Classes {#cc-id}

### Z-Wave Command Class Configurator

An advanced configuration was introduced in order to accommodate the more advanced z-wave command
classes that require complex configurations. More details can be found [here](ZAF/tool/cc_configurator/README.md)

### Command Class List Generator

An application no longer needs to pass the Command Classes lists to the protocol and ZAF. ZAF
has new components that are capable of generating these lists from the linked command classes.
For end points a new macro was introduced:

```c
#define ZAF_CC_REGISTER_CONFIG(cc, config, index)
```

This macro needs to be called for each element in a configuration array that contains
endpoints. For example:

```c
static cc_multilevel_switch_t s_switches[] = {
  {
    .endpoint = 2,
  },
  {
    .endpoint = 1,
  },
};

...

ZAF_CC_REGISTER_CONFIG(COMMAND_CLASS_SWITCH_MULTILEVEL, &s_switches[0], 0);
ZAF_CC_REGISTER_CONFIG(COMMAND_CLASS_SWITCH_MULTILEVEL, &s_switches[1], 1);
```

This is automatically handled in the command classes provided in the SDK but command
classes not from the SDK need to follow this standard. This requirement is similar to the
`REGISTER_CC`.

### I/O Interface for CCs

Some Command Classes have a new level of abstraction, the I/O interface. This interface has the 
functions used to read, write, and sometimes migrate the data. This level of abstraction allows the 
user to disable and enable data persistency seamlessly.

CCs that support this interface:

- Battery
- Central Scene
- Color Switch
- Configuration
- Door Lock
- Multilevel Switch
- Notification
- User Code

### CC Association

The `AssociationInit()` function was removed and the initialization performed by this function was split into two 
separate functions: `init()` and `reset()`. These two functions are now passed as callbacks to the `REGISTER_CC_V4` macro.
This ensures that the initialization and reset are performed by ZAF, instead of the user code.

`MAX_ASSOCIATION_GROUPS` and `MAX_ASSOCIATION_IN_GROUP` have been moved from `config_app.h` to `cc_association_config.h`
and renamed to `CC_ASSOCIATION_MAX_GROUPS_PER_ENDPOINT` and `CC_ASSOCIATION_MAX_NODES_IN_GROUP` respectively.
These values can be set in Simplicity Studio in the "Association Command Class" module.

### CC AGI

The Association Group Information Command Class has been removed from the `config_app.h` header and implemented in the config generator and the application slcp files.
This refactoring enables the user to easily configure the device's group and node information in the Simplicity Studio GUI instead of a source file.
All the command classes, utilities, applications, and tests have been refactored to use the automatically-generated headers containing the AGI group and node
configuration. The names of the defines have also been refactored to make them easy to understand.

The `AGI_ResourceGroupSetup` function has been deprecated. In addition, the association group information has been moved from the `config_app.h` header to the `cc_config` yaml file.
Redundant duplication of the root device groups is removed.
In order to define the device groups and endpoints, developers have to add / modify the zw_cc_association section in the respective app cc_config file. Developers can look at at WallController, SensorPIR, or PowerStrip applications as a starting point for defining their own groups and endpoints. The configurator will use this information to generate the agi groups and tables in the cc_association_config.c source file for the specific application.

### CC Basic

Basic Get mapping is now done automatically by ZAF. It does require relevant command classes to
implement a certain function. See [How to implement a new command class](ZAF/doc/content/how-to-implement-a-new-command-class.md) for more information.

True Status was removed from CC Basic as True Status must be handled by the command class mapped to Basic Set.

As a result of the above changes, the following functions were removed from CC Basic:

1. CC_Basic_report_stx()
2. CC_Basic_prepare_zaf_tse_data()
3. CC_Basic_report_notifyWorking()
4. CC_Basic_GetCurrentValue_handler()
5. CC_Basic_GetTargetValue_handler()
6. CC_Basic_GetDuration_handler()

Additionally, a Supervision flag was added to CC_Basic_Set_tx() making it possible for the
application to decide whether Supervision must be used or not for the given transmission of Basic
Set. The use of Supervision was previously hardcoded in CC_BasicController.c.

### CC Binary Switch

The Binary Switch command class was rewritten to use ZAF Actuator and take care of reporting the
true status so that the application does not have to.

The configuration of this CC must be done in the `*.cc_config` file. Example for root device:
```
zw_cc_binaryswitch:
  binary_switches:
    - endpoint: 0
```
See PowerStrip.cc_config for an example of endpoints.

### CC Central Scene

Three Central Scene config APIs were moved from the application to the Command Class:

- `cc_central_scene_set_configuration` (used to be `setAppCentralSceneConfiguration`)
- `cc_central_scene_get_configuration` (used to be `getAppCentralSceneConfiguration`)
- `cc_central_scene_get_supported_key_attributes` (used to be `getAppCentralSceneReportData`)

The configuration of `cc_central_scene_get_supported_key_attributes` can be done from the Simplicity Studio GUI in the "zw_cc_central_scene" component.

Non-Volatile Memory can be used to store the configuration values by installing the "zw_cc_central_scene_nvm" component.

### CC Color Switch

The Command Class Color Switch was refactored to no longer require initialization on the application
level. The initialization is now handled internally by ZAF on `ZAF_Init`.

The color configuration is now also handled by the Command Class and not the application. 
The configuration is available using the `Z-Wave Command Class Configurator`. The array of 
all colors supported by the application is no longer needed since it is created by the Command Class 
based on the configuration.

The functionality that each color component had in its callback function has been removed. Now
all color components call the `cc_color_switch_cb` with the color component as parameter.
In the `CC_ColorSwitch_Init` one of the parameters was a callback function. This function is now a weak
function defined in the command class `cc_color_switch_refresh_cb`.

### CC Door Lock

The Door Lock Command Class has been refactored so that all logic related to the Command Class is handled 
internally by it. The Command Class had five extern functions that had to be implemented by the application. 
`CC_DoorLock_OperationSet_handler`, `CC_DoorLock_OperationGet_handler`, `CC_DoorLock_ConfigurationSet_handler`, `CC_DoorLock_ConfigurationGet_handler` and 
`CC_DoorLock_CapabilitiesGet_handler`. These functions are now implemented inside the command class 
and six new functions were created:

- `CC_DoorLock_Toggle` to toggle the door lock mode.
- `cc_door_lock_latch_status_handler` to be called when the latch status changes (HW specific function). 
- `cc_door_lock_bolt_status_handler` to be called when the bolt status changes (HW specific function).
- `CC_DoorLock_update` to set door conditions (LED) from door handle mode and state.
- `CC_DoorLock_SetOutsideDoorHandleState` to set the Outside Door Handle State for a specific handle.
- `CC_DoorLock_ClearOutsideDoorHandleState` to clear the Outside Door Handle State for a specific handle.

The configuration is now also handled by the Command Class and not the application. The configuration is available 
using the `Z-Wave Command Class Configurator`.

All type redefinitions and function redefinitions kept for backwards compatibility were removed.

The Door Lock data is now owned by the Command Class and not the application. In our sample
application the data was stored in `FILE_ID_APPLICATIONDATA` and code to migrate this information
from the application into the command class was added with this assumption. If an application is storing
this information in another file ID, the define `DOOR_LOCK_DATA_LEGACY_FILE_ID` in `cc_door_lock_nvm.c` 
needs to be changed to match this other file ID

### CC Firmware Update Metadata

`APP_FIRMWARE_ID`, previously defined in `config_app.h`, has been obsoleted, as well as function `handleFirmWareIdGet()`.
Instead, firmware ID (16 bit) is hard-coded in ota_util.c to consist of product type ID LSB and product
ID LSB.

### CC Indicator

`CC_Indicator_Init()` was removed and, as a replacement for the callback parameter, a weakly-
defined function was added: `cc_indicator_handler()`. This function should be defined
by the platform-specific code to override the weakly-defined function.

If an existing function was previously passed to `CC_Indicator_Init()`, simply rename that
function to `cc_indicator_handler()`.

### CC Manufacturer Specific

CC Manufacturer Specific was changed so that all applications can be built without this CC. This
was done to enable building an even smaller application for updating Secure Element.

As a result, the following files are removed from the SDK:

- CC_ManufacturerSpecific.h
- CC_ManufacturerSpecific_config.c
- CC_ManufacturerSpecific_config.h

This includes following functions:

- `CC_ManufacturerSpecific_ManufacturerSpecificGet_handler()`
- `CC_ManufacturerSpecific_DeviceSpecificGet_handler()`

`APP_MANUFACTURER_ID`, `APP_PRODUCT_ID` and `PRODUCT_TYPE_ID` have been moved to `zaf_config.h`
and renamed to `ZAF_CONFIG_MANUFACTURER_ID`,`ZAF_CONFIG_PRODUCT_ID`, and `ZAF_CONFIG_PRODUCT_TYPE_ID`, respectively.

Manufacturer ID, product type ID, and product ID must be set in Simplicity Studio in the Software
Components tab.

Device Specific Report contains the chip serial number per default as this is what Silicon Labs
recommends. If anything else is desired, CC_ManufacturerSpecific.c can be altered.

### CC Multilevel Sensor

The sensor configuration is now also handled by the Command Class and not the application. 
The configuration is available using the `Z-Wave Command Class Configurator`.
The `sensor_interface_t` and `cc_configuration_t` in the application are no longer needed.

In `sensor_interface_t` three callbacks are now weak functions in the Command Class:  
`cc_multilevel_sensor_{{sensor_instance}}_interface_init`, `cc_multilevel_sensor_{{sensor_instance}}_interface_deinit` 
and `cc_multilevel_sensor_{{sensor_instance}}_interface_read_value`. The functions' behavior and parameters 
were not changed so renaming them should be enough.

In the `cc_configuration_init` function one of the parameters was the `cc_configuration_io_interface_t`, 
which defined two callback functions for reading and writing. These functions are now two weak functions 
defined inside the Command Class: `cc_configuration_io_write` and `cc_configuration_io_read`. 
The functions' behavior and parameters were not changed so renaming them should be enough.

### CC Multilevel Switch

The Command Class Multilevel Switch was refactored to no longer require initialization on the application
level. The initialization is now handled internally by ZAF on `ZAF_Init`.

The switch configuration is now also handled by the Command Class and not the application. 
The configuration is available using the `Z-Wave Command Class Configurator`. The array of 
all switches supported by the application is no longer needed since it is created by the Command Class 
based on the configuration.

In the `cc_multilevel_switch_init` one of the parameters was a callback function. This function is now a weak
function defined in the command class `cc_multilevel_switch_support_cb`.

### CC Notification

The Command Class Notification was refactored to no longer require initialization on the application
level. The initialization is now handled internally by ZAF on `ZAF_Init` and `ZAF_Reset`.
`MAX_NOTIFICATION` define was removed from `config_app.h` and moved to `cc_notification_config.h`
This value can be configured in the Simplicity Studio GUI.

- Functions `NotificationEventTrigger()` and `UnsolicitedNotificationAction()` have been merged into a single function named `CC_Notification_TriggerAndTransmit()`.
- Notification CC now handles triggering of TSE by itself.
- Configuration of CC Notification is now handled by the `Z-Wave Command Class Configurator` and functions
`AddNotification()` and `DefaultNotificationStatus()` have been obsoleted.
- Polling mode has been removed.

  - Implementation of deprecated polling mode has been removed from CC Notification.
  - This includes removing enum NOTIFICATION_STATUS_SET. Since poll mode is not supported anymore, notification status is the same for all commands.
  - CC Notification now supports push mode only.

### CC Supervision

The Command Class Supervision is refactored to no longer require initialization on the application
level. The initialization is now handled internally by ZAF on `ZAF_Init`.

The status updates can be enabled/disabled in the Simplicity Studio GUI.

The `cc_supervision_get_received_handler(...)` and `cc_supervision_report_recived_handler(...)` handler callbacks defined in `cc_supervision_handlers.h` have a dummy weakly-defined implementation and can be redefined by the applications.

### CC User Code

The User Code Command Class has been refactored so that all logic related to the Command Class is handled 
internally by it. The Command Class had four extern functions that had to be implemented by the application. 
`CC_UserCode_Set_handler`, `CC_UserCode_getId_handler`, `CC_UserCode_Report_handler` and 
`CC_UserCode_UsersNumberReport_handler`. These functions are now implemented inside the command class 
and two new functions were created: 

- `CC_UserCode_reset_data` to reset all the data persisted by the 
command class. 
- `CC_UserCode_Validate` that contains all the validation logic.

Two configuration parameters related to this Command Class that belonged in the application now belong in the Command Class: `CC_USER_CODE_MAX_IDS` (formerly known as `USER_ID_MAX`)
and `CC_USER_CODE_DEFAULT` (formerly known as `DEFAULT_USERCODE`).

### CC Wake Up

The Command Class Wake Up was refactored to no longer require initialization on the application
level. The initialization is now handled internally by ZAF on `ZAF_Init`.

The `CC_WakeUp_setConfiguration()` API was removed from the applications. These parameters can be configured in the Simplicity Studio GUI under the Wake Up Command Class's component.

### CC Z-Wave Plus Info

The icon types for the root device and optionally for the endpoints is now configurable. The configuration
is handled by the Command Class.

The user icon type and installer icon type for the root device are defined in ZAF config and can be configured in Simplicity Studio.

If an application supports Command Class Multi Channel, the icon types of an endpoint must be configured in the app.cc_config file. See the configuration of Power Strip for an example.

## 7.18.x and Previous Releases

See the corresponding release notes.
