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
      (end_point: <Integer 0-255>)
      agi_prifile: <agi_profile_t>
      events:
        <notification_event_state>
        <notification_event_state>
        ...
      current_event: <notification_event_state>
      status: <NOTIFICATION_STATUS>
    ...
    - type: <notification_type_t>
      (end_point: <Integer 0-255>)
      agi_prifile: <agi_profile_t>
      events:
        <notification_event_state>
        <notification_event_state>
        ...
      current_event: <notification_event_state>
      status: <NOTIFICATION_STATUS>
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
