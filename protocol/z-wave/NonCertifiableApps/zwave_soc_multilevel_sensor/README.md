# Multilevel Sensor

Shows the ability to advertise numerical sensor readings, such as temperature, and humidity. Multiple parameters can be set for the minimum and maximum values.

The Multilevel Sensor application is based on:

| <!-- -->                | <!-- -->                                  |
| :---------------------- | :---------------------------------------- |
| Role Type               | Reporting Sleeping End Device (RSS)       |
| Supporting Device Type  | Data reporting                            |
| Device Type             | Notification sensor                       |
| Generic Type            | Sensor Notification                       |
| Specific Type           | Notification Sensor                       |
| Requested security keys | S2\_UNAUTHENTICATED and S2\_AUTHENTICATED |

Multilevel Sensor transmits the following events:

- Environment monitoring
  - Temperature, and humidity measure

## Supported Command Classes

Multilevel Sensor implements mandatory and some optional command classes. The table below lists the supported Command Classes, their version, and their required Security class, if any.

| Command Class             | Version | Required Security Class        |
| :------------------------ | :-----: | :----------------------------- |
| Association               |    2    | Highest granted Security Class |
| Association Group Info    |    3    | Highest granted Security Class |
| Device Reset Locally      |    1    | Highest granted Security Class |
| Firmware Update Meta Data |    5    | Highest granted Security Class |
| Indicator                 |    3    | Highest granted Security Class |
| Manufacturer Specific     |    2    | Highest Granted Security Class |
| Multi-Channel Association |    3    | Highest granted Security Class |
| Powerlevel                |    1    | Highest granted Security Class |
| Security 2                |    1    | None                           |
| Supervision               |    1    | None                           |
| Transport Service         |    2    | None                           |
| Version                   |    3    | Highest granted Security Class |
| Wake Up                   |    2    | Highest granted Security Class |
| Z-Wave Plus Info          |    2    | None                           |
| Configuration             |    4    | Highest granted Security Class |
| Multilevel-Sensor         |   11    | Highest granted Security Class |

## Basic Command Class Mapping

Basic Command Class is not mapped to any of the supported command classes.

## Association Groups

The following table shows the available association groups.

<table>
<tr>
    <th>ID</th>
    <th>Name</th>
    <th>Node Count</th>
    <th>Description</th>
</tr><tr>
    <td>1</td>
    <td>Lifeline</td>
    <td>5</td>
    <td>
        <p>Supports the following command classes:</p>
        <ul>
            <li>Device Reset Locally: triggered upon reset.</li>
            <li>Indicator Report: Triggered when LED1 changes state.</li>
            <li>Configuring parameters: Minimum and maximum temperature levels can be set, errors can be detected if measured temperature is out of range</li>
            <li>Environmental measurements: Temperature and humidity values
can be read, triggered from other Z-Wave devices</li>
        </ul>
    </td>
</tr>
</table>

## Usage of Buttons and LED Status

The following LEDs and buttons shown in the next table below are used.

<table>
<tr>
    <th>Button</th>
    <th>Action</th>
    <th>Description</th>
</tr><tr>
    <td>RST</td>
    <td>Press</td>
    <td>
      Resets the firmware of an application (like losing power). All volatile memory will be cleared.<br>
    </td>
</tr><tr>
    <td>BTN0</td>
    <td>Press</td>
    <td>Sends Battery Report, temperature, and humidity data (only if the device is not sleeping)</td>
</tr><tr>
    <td rowspan="2">BTN1</td>
    <td>Press</td>
    <td>
        Enter "learn mode" (sending node info frame) to add/remove the device.<br>
        Removing the device from a network will reset it.
    </td>
</tr><tr>
    <td>Hold for at least 5 seconds and release</td>
    <td>Perform a reset to factory default operation of the device, and a Device Reset Locally Notification Command is sent via Lifeline.</td>
</tr>
</table>

<table>
<tr>
    <th>LED</th>
    <th>Description</th>
</tr><tr>
    <td>LED1</td>
    <td>
        Blinks with 1 Hz when learn mode is active.<br>
        Used for Indicator Command Class.
    </td>
</tr>
</table>

Note : BTN0 press works only on the 800 series and has no effect on the 700 series. This is due to the differences in the silicon. The BTN0 press is able to wake up the 800 series from EM4 mode where as this is not possible for the 700 series.

## Firmware Update

This section will describe backward compatibility when upgrading the MultilevelSensor application from one SDK to a newer version. 

SDK 7.1x is the first SDK running on Z-Wave 700.
