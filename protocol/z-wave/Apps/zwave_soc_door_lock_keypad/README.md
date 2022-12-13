# Door Lock

The Z-Wave certified Door Lock application shows a lock implementation. It supports user codes to open a door and thereby eliminate the need for traditional keys. It is possible to both lock and unlock the door remotely through the Z-Wave protocol.

The Door Lock application is based on:

| <!-- -->                | <!-- -->                                                                |
| ----------------------- | ----------------------------------------------------------------------- |
| Role Type               | Listening Sleeping End device (LSS / FLiRS)                             |
| Supporting Device Type  | Actuator                                                                |
| Device Type             | Lock                                                                    |
| Generic Type            | Entry Control                                                           |
| Specific Type           | Door Lock                                                               |
| Requested security keys | S0 and S2_ACCESS<br>The Door Lock features depend on the security level |

The application will only work when securely added to a network by a controller supporting security.
The controller MUST support security S2_Access_Control or S0 in order to be able to control the door lock.

**Not** implemented Door lock functionality:

- Timed Operation mode
- Door Lock condition
- Inside Door Handle State
- Functionality handling Lock timeout
- Target mode
- Auto-Relock, Hold And Release, Block to Block, and Twist Assist

## Supported Command Classes

The Door Lock application implements mandatory and some optional command classes. The table below lists the supported Command Classes, their version, and their required Security class, if any.

| Command Class             | Version | Required Security Class |
| ------------------------- |:-------:| ----------------------- |
| Association               | 2       | S0 or Access Control    |
| Association Group Info    | 3       | S0 or Access Control    |
| Basic                     | 2       | S0 or Access Control    |
| Battery                   | 1       | S0 or Access Control    |
| Device Reset Locally      | 1       | S0 or Access Control    |
| Door Lock                 | 4       | S0 or Access Control    |
| Firmware Update Meta Data | 5       | S0 or Access Control    |
| Indicator                 | 3       | S0 or Access Control    |
| Manufacturer Specific     | 2       | S0 or Access Control    |
| Multi-Channel Association | 3       | S0 or Access Control    |
| Powerlevel                | 1       | S0 or Access Control    |
| Security 0                | 1       | None                    |
| Security 2                | 1       | None                    |
| Supervision               | 1       | None                    |
| Transport Service         | 2       | None                    |
| User Code                 | 1       | S0 or Access Control    |
| Version                   | 3       | S0 or Access Control    |
| Z-Wave Plus Info          | 2       | None                    |

## Basic Command Class mapping

The Basic Command Class is mapped according to the table below.


| Basic Command                       | Mapped Command                                     |
| ----------------------------------- | ---------------------------------------------------|
| Basic Set (Value)                   | Door Lock Operation Set (Door Lock Mode)           |
| Basic Report (Current Value = 0x00) | Door Lock Operation Report (Door Lock Mode = 0x00) |
| Basic Report (Current Value = 0xFF) | Door Lock Operation Set (Door Lock Mode)           |

## Association Groups

The table below shows the available association groups, including supported command classes for Z-Wave and Z-Wave Long Range respectively.

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
            <li>Battery: Triggered upon low battery.</li>
            <li>Door Lock: Triggered upon a change in door lock configuration.</li>
            <li>Door Lock: Triggered upon a change in door lock operation.</li>
            <li>Indicator Report: Triggered when LED1 changes state.</li>
            <li>User Code: Triggered when a user code record is modified.</li>
        </ul>
    </td>
</tr>
</table>

X: For Z-Wave node count is equal to 5 and for Z-Wave Long Range it is 1.

## Usage of Buttons and LED Status

The following buttons and LEDs are used.

<table>
<tr>
    <th>Button</th>
    <th>Action</th>
    <th>Description</th>
</tr><tr>
    <td>RST</td>
    <td>Press</td>
    <td>Resets the firmware of an application (like losing power). All volatile memory will be cleared.</td>
</tr><tr>
    <td>BTN0</td>
    <td>Button up/down</td>
    <td>
        If the outside door handle state is active:<br>
        Button down sets the outside door handle mode active.<br>
        Button up sets the outside door handle mode inactive.
    </td>
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
    <td>Button press</td>
    <td>Sends Battery Report.</td>
</tr><tr>
    <td>BTN3</td>
    <td>Button press</td>
    <td>
        Simulates entering a user code on a keypad.<br>
        The entered user code is hard-coded with the value of the default user code of the application. The default user code is 1234.<br>
        A valid user code entry (i.e., button press) toggles the Door Lock Mode between Secured and Unsecured.<br>
        If the user code for user ID 1 is changed to something else than the default user code, the Door Lock Mode can no longer be toggled by pressing this button.<br>
    </td>
</tr>
</table>

<table>
<tr>
    <th>LED</th>
    <th colspan="3">Description</th>
</tr><tr>
    <td>LED0</td>
    <td>Latch:</td>
    <td>Led on -> latch open [bit 0]</td>
    <td>Led off -> latch closed [bit 1]</td>
</tr><tr>
    <td>LED1</td>
    <td colspan="3">
        Blinks with 1 Hz when learn mode is active.<br>
        Used for Indicator Command Class.
    </td>
</tr><tr>
    <td>LED3</td>
    <td>Bolt:</td>
    <td>Led on -> bolt locked [bit 0]</td>
    <td>Led off -> bolt unlocked [bit 1]</td>
</tr>
</table>

## Firmware Update

This section will describe backward compatibility when upgrading the Door Lock application from one SDK to a newer version. 

SDK 7.1x is the first SDK running on Z-Wave 700.
