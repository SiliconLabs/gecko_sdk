# When and how to create a Multi Channel application

Creating a Multi Channel application might be relevant in several use cases.

Some use cases might be:
* A power strip where each outlet can be controlled individually
* Two or more identical sensors each reporting their value, for instance temperature. Multi Channel
  is a requirement when the sensors are of the same type.

## What to configure?
The following describes the minimum configuration that is required.

The Power Strip application shows an example of how the following can be configured and adds
application specific configuration on top as in Binary Switch CC, Multilevel Switch CC and
Notification CC.

### Multi Channel Command Class
The Multi Channel Command Class component must be installed in Simplicity Studio and comes with
some configuration parameters.

Example from Power Strip configuration:
```
zw_cc_multi_channel:
  endpoints:
    - endpoint: 1
      generic_type: GENERIC_TYPE_SWITCH_BINARY
      specific_type: SPECIFIC_TYPE_NOT_USED
    - endpoint: 2
      generic_type: GENERIC_TYPE_SWITCH_MULTILEVEL
      specific_type: SPECIFIC_TYPE_NOT_USED
```

### Z-Wave Plus Info Command Class
This configuration defines the icon types for each endpoint so that a controller would know
which icons to display in a mobile app.

Example from Power Strip configuration:
```
zw_cc_zwaveplusinfo:
  endpoints:
    - endpoint: 1
      installer_icon_type: ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH
      user_icon_type: ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH
    - endpoint: 2
      installer_icon_type: ICON_TYPE_GENERIC_LIGHT_DIMMER_SWITCH
      user_icon_type: ICON_TYPE_GENERIC_LIGHT_DIMMER_SWITCH
```

### Association Group Information Command Class
This configuration defines what the application will report unsolicited.

Endpoint specific configuration is not mandatory as all reporting can be done via Lifeline, but
configuring this for endpoints opens up for a more flexible installation at the end user.

In case of Power Strip, the application can transmit a Notification Report from each endpoint if
any nodes are associated in those association groups.

It's up to the application developer to decide on the level of flexibility.

Example from Power Strip configuration:
```
zw_cc_agi:
  endpoints:
    - endpoint: 1
      groups:
        - name: Alarm EP 1
          profile_msb: ASSOCIATION_GROUP_INFO_REPORT_PROFILE_NOTIFICATION
          profile_lsb: NOTIFICATION_REPORT_POWER_MANAGEMENT_V4
          commands:
            - command_class: COMMAND_CLASS_NOTIFICATION_V3
              command: NOTIFICATION_REPORT_V3
    - endpoint: 2
      groups:
        - name: Alarm EP 2
          profile_msb: ASSOCIATION_GROUP_INFO_REPORT_PROFILE_NOTIFICATION
          profile_lsb: NOTIFICATION_REPORT_POWER_MANAGEMENT_V4
          commands:
            - command_class: COMMAND_CLASS_NOTIFICATION_V3
              command: NOTIFICATION_REPORT_V3
```
