# Z-Wave Command Class Configurator

Some command classes require more advanced configuration parameters and for 
those an advanced configurator was created.

The advanced configurator will be executed for all projects (`slcp`) which 
contain a `configuration_file`  with the extension (`cc_config`)

## Specification

The `cc_config` file is a yaml file with a defined format per command class.
The basic format is

```yaml
<CC_1>:
    ...
<CC_2>:
    ...
<CC_n>:
    ...
```

Where CC_n, is the component (`slcc`) id.

Each command class defines it's properties based on the requirements for it.

## Command Classes - Specification

Below each Command Class properties are defined
Non mandatory fields are displayed within parentheses

### zw_cc_multi_channel_support

This section configures the generic type and specific type for each endpoint.

This configuration is only relevant for a multi channel device like a power strip or a sensor with
multiple sensors of the same type, for example two temperature sensors.

```yaml
zw_cc_multi_channel_support:
  endpoints:
    - endpoint: 1
      generic_type: <generic type for endpoint 1>
      specific_type: <specific type for endpoint 1>
    - endpoint: 2
      generic_type: <generic type for endpoint 2>
      specific_type: <specific type for endpoint 2>
    - endpoint: <N-127>
      generic_type: <generic type>
      specific_type: <specific type>
```

Please see PowerStrip.cc_config for an example.

### zw_cc_binary_switch

The Command Class Binary Switch advanced configurator is defined as follows:

```yaml
zw_cc_binary_switch:
  binary_switches:
    - endpoint: <Integer 0-255>
      ...
    - endpoint: <Integer 0-255>
```

### zw_cc_color_switch

The Command Class Color Switch advanced configurator is defined as follows:

```yaml
zw_cc_color_switch:
  colors:
    - id: <EColorComponents>
      (end_point: <Integer 0-255>)
      ...
    - id: <EColorComponents>
      (end_point: <Integer 0-255>)
```

### zw_cc_multilevel_switch_support

The Command Class Multilevel Switch Support advanced configurator is defined as 
follows:

```yaml
zw_cc_multilevel_switch_support:
  switches:
    - end_point: <Integer 0-255>
    ...
    - end_point: <Integer 0-255>
```

### zw_cc_multilevel_sensor

The Command Class Multilevel Sensor advanced configurator is defined as follows:

```yaml
zw_cc_multilevel_sensor:
  sensors:
    <sensor_instance>:
      name: <sensor_name_t>
      scales:
        - <SENSOR_SCALE_*>
        - <SENSOR_SCALE_*>
    ...
    <sensor_instance>:
      name: <sensor_name_t>
      scales:
        - <SENSOR_SCALE_*>
```

### zw_cc_multilevel_sensor

The Command Class Configuration configurator is defined as follows:

```yaml
zw_cc_configuration:
  configurations:
    - name: <String>
      number: <1-65535>
      file_id: <0-99>
      info: <String>
      size: <cc_config_parameter_size_t>
      format: <cc_config_parameter_format_t>
      min_value: <Integer - Range depends on size and format>
      max_value: <Integer - Range depends on size and format>
      default_value: <Integer - Range depends on size and format>
      altering_capabilities: <Bit>
      read_only: <Bit>
      advanced: <Bit>
    ...
    - name: <String>
      number: <1-65535>
      file_id: <0-99>
      info: <String>
      size: <cc_config_parameter_size_t>
      format: <cc_config_parameter_format_t>
      min_value: <Integer - Range depends on size and format>
      max_value: <Integer - Range depends on size and format>
      default_value: <Integer - Range depends on size and format>
      altering_capabilities: <Bit>
      read_only: <Bit>
      advanced: <Bit>
```

### zw_cc_door_lock

The Command Class Configuration configurator is defined as follows:

```yaml
zw_cc_configuration:
  configuration:
    operation_type: <cc_door_lock_operation_type_t>
    supported_inside_handles: <cc_door_lock_handle_t>
    supported_outside_handles: <cc_door_lock_handle_t>
    options_flags: <Integer 0-255>
    max_auto_relock_time: <Integer 0-65535>
    max_hold_and_release_time: <Integer 0-65535>
```

### zw_cc_notiifcation

The Command Class Notification configurator is defined as follows:

```yaml
zw_cc_notification:
  notifications:
    - type: <notification_type_t>
      (endpoint: <Integer 0-127>)
      agi_profile: <agi_profile_t>
      state_events:
        - <notification_event_state 1>
        - <notification_event_state 2>
        - <notification_event_state N>
    ...
    - type: <notification_type_t>
      (endpoint: <Integer 0-127>)
      agi_profile: <agi_profile_t>
      state_events:
        - <notification_event_state 1>
        - <notification_event_state 2>
        - <notification_event_state N>
```

### zw_cc_agi

The Command Class Association Group Information configurator is defined as follows

```yaml
zw_cc_association: 
  endpoints: 
    - endpoint: <Integer 0-127>
      groups: 
        - name: <String>
          profile_msb: <Integer>
          profile_lsb: <Integer>
          commands: 
            - command_class: <Integer>
              command: <Integer>

```
The endpoints have to be specified in ascending order.

### zw_cc_central_scene

The Command Class Central Scene configurator is defined as follows

```yaml
zw_cc_central_scene:
  central_scene:
    identical: <Integer 0-1 - Mandatory field only if all scenes are identical> 
    number_of_scenes: <1-255 - Mandatory field if and only if all scenes are identical>
    scenes:
      - scene: <Integer 0 - number_of_scenes>
        attributes:
          - attribute: CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_PRESSED_1_TIME_V2
          - attribute: CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_RELEASED_V2
          ...
      - scene: <Integer 0-127 First scene is mandatory. The rest of scenes are mandatory if and only if scenes are not identical>
        attributes:
          - attribute: CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_RELEASED_V2
          - attribute: CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_HELD_DOWN_V2
          ...
```
