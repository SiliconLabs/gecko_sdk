# Sensor PIR

The Z-Wave certified Sensor PIR application shows a presence/movement detector implementation for controlling other devices and for sending notifications.

| <!-- -->                  | <!-- -->                                  |
|---------------------------|-------------------------------------------|
| Role Type                 | Reporting Sleeping End device (RSS)       |
| Supporting Device Type    | Data reporting                            |
| Device Type               | Notification sensor                       |
| Generic Type              | Sensor Notification                       |
| Specific Type             | Notification Sensor                       |
| Requested security keys   | S2_UNAUTHENTICATED, and S2_AUTHENTICATED  |

Sensor PIR transmits the following notification types/events:

-   Home Security
    -   Motion detection (unknown location)

Sensor PIR supports the "push mode" only of Notification CC.

## Supported Command Classes

Sensor PIR implements mandatory and some optional command classes. The table below lists the supported Command Classes, their version, and their required Security class, if any.

| Command Class             | Version | Required Security Class        |
| ------------------------- |:-------:| ------------------------------ |
| Association               |    2    | Highest granted Security Class | 
| Association Group Info    |    3    | Highest granted Security Class |
| Battery                   |    1    | Highest granted Security Class |
| Device Reset Locally      |    1    | Highest granted Security Class |
| Firmware Update Meta Data |    5    | Highest granted Security Class |
| Indicator                 |    3    | Highest granted Security Class |
| Manufacturer Specific     |    2    | Highest Granted Security Class |
| Multi-Channel Association |    3    | Highest granted Security Class |
| Notification              |    8    | Highest granted Security Class |
| Powerlevel                |    1    | Highest granted Security Class |
| Security 2                |    1    | None                           |
| Supervision               |    1    | None                           |
| Transport Service         |    2    | None                           |
| Version                   |    3    | Highest granted Security Class |
| Wake Up                   |    2    | Highest granted Security Class |
| Z-Wave Plus Info          |    2    | None                           |

## Basic Command Class mapping

Basic Command Class is not mapped to any of the supported command classes

## Association Group configuration

Application Association Group configuration

<table>
<tr>
    <th>ID</th>
    <th>Name</th>
    <th>Node Count</th>
    <th>Description</th>
</tr><tr>
    <td>1</td>
    <td>Lifeline</td>
    <td>X</td>
    <td>
        <p>Supports the following command classes:</p>
        <ul>
            <li>Device Reset Locally: triggered upon reset.</li>
            <li>Battery: triggered upon low battery.</li>
            <li>
                Notification: triggered upon a movement detection (simulated by
                button BTN2). After a while, a cancel notification will be issued.
            </li>
            <li>Indicator Report: Triggered when LED1 changes state.</li>
        </ul>
    </td>
</tr><tr>
    <td>2</td>
    <td>Basic Set</td>
    <td>Y</td>
    <td>
        Upon a movement detection (simulated by button BTN2), nodes
        associated in this group will first receive a Basic Set with 0xFF (turn on)
        and after a while receive a Basic Set with 0x00 (turn off).
    </td>
</tr>
</table>

X: For Z-Wave node count is equal to 5 and for Z-Wave Long Range it is 1.
Y: For Z-Wave node count is equal to 5 and for Z-Wave Long Range it is 0.

## Usage of Buttons and LED Status

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
        Sends Wake Up Notification.
    </td>
</tr><tr>
    <td>BTN0</td>
    <td>Press</td>
    <td>Sends Battery Report (only if the device is not sleeping)</td>
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
</tr><tr>
    <td>BTN2</td>
    <td>Hold for at least 1 second and release</td>
    <td>Simulates a "Motion detected."</td>
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

This section will describe backward compatibility when upgrading the Switch On/Off application from one SDK to a newer version.

SDK 7.1x is the first SDK running on Z-Wave 700.
