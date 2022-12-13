# Flex (RAIL) - Mode Switch

## Introduction

The `Mode Switch` example demonstrates an exchange of transmit and receive
operations between two (or more) nodes expanded by the Wi-SUN Mode Switching
features implemented in RAIL.

This application can be used for setting up a simple link test that uses Mode
Switch, where the nodes are listening except for the short periods where
packet transmission takes place. Also, this application can be used to learn
how the Mode Switch RAIL APIs work.

The available PHY switches for 915 MHz and 868 MHz are FSK to OFDM, and for
490 MHz FSK to FSK.

## Prerequisites

The Mode Switch example is supported only on the EFR32xG25 device generation.

## Getting Started

This example implements both the receiver (RX) and the transmitter
(TX) functionalities. The implementation is therefore symmetric, as both
nodes are capable of sending and receiving messages as well as initiating and
terminating the Mode Switch process.

Mode Switch is a feature defined in the Wi-SUN standard and implemented in
RAIL that can initiate automatic PHY changing. The radio configuration change
is realized as a channel change in RAIL. The `Mode Switch packet` defines the
channel to
which the device should switch (`Mode Switch channel`) to transmit
`normal packet`s until the end of the Mode Switch process. The channel and
the operational mode are defined in the `phyModeId`, which is part of the
`Mode Switch packet`. At the end of Mode Switch a similar packet to the
`normal packet` is transmitted that indicates the end of the procedure and
the devices switch back to the original `Base channel`.

In this document the use of `Mode Switch requester` and `Mode Switch accepter`
is implicit. These terms refer to the `Mode Switch packet` transmitter and
receiver devices, respectively.

----

Compile the project and download the application to two radio boards.

### Initialization Information

> Note: As the Mode Switch operation strongly depends on the radio
  configuration, it is recommended not to change it, otherwise the
  application can fail early during the initialization.

On startup the following or a similar message will be displayed:

```
Channel is set to 0
Found 9 channels
  Ch number:     0 phyModeId:   5 modulation: M_2FSK
  Ch number:     0 phyModeId:  21 modulation: M_2FSK
  Ch number: 20480 phyModeId:  32 modulation: M_OFDM
  Ch number: 20480 phyModeId:  33 modulation: M_OFDM
  Ch number: 20480 phyModeId:  34 modulation: M_OFDM
  Ch number: 20480 phyModeId:  35 modulation: M_OFDM
  Ch number: 20480 phyModeId:  36 modulation: M_OFDM
  Ch number: 20480 phyModeId:  37 modulation: M_OFDM
  Ch number: 20480 phyModeId:  38 modulation: M_OFDM
NOTE: Although multiple channel configs may be available,
      Config 0 is assumed for use.
IR calibration OK
Mode switch
> 
```

The welcome message informs the user of the available channel numbers, and the
associated `phyModeId` numbers and modulation type.

The devices start in receive state, listening on channel 0. This is the `Base
channel` after initialization.

#### Mode Switch Operation

> Note: Using the default radio configuration, Mode Switch can be requested
  only on channel 0 (the `Base channel`) to channel 20480 (the `Mode switch
  channel`).

You can trigger a `Mode Switch` process on `Mode Switch requester` node by
issuing the `trig_mode_switch` command. For successful calls it:

1. transmits a `Mode Switch packet` on the `Base channel`,
2. switches the active channel from the `Base channel` to the `Mode Switch channel`,
3. transmits a `normal packet` on the `Mode Switch channel`.

These steps will be printed out:

```
trig_mode_switch 32 0
Mode switch phy mode id is set to 32
Mode switch requested
Packet has been sent    // Step 1.
Channel is set to 20480 // Step 2.
Mode switch completed
Packet has been sent    // Step 3.
```

The second, optional, argument sets the time in seconds for how long the `Mode
Switch requester` should stay on the `Mode Switch channel`. If it is 0 or not
given, the `Mode Switch requester` stays on the new channel infinitely
(`Infinite Mode Switch`). Again, at the beginning of this period, a `normal
packet` is transmitted, then the device starts listening on the new channel.
Therefore this node is also able to receive `normal packets` on this channel.

When a Mode Switch process is ended, either by a configured timeout or the
`end_mode_switch` command, the following events should happen on the `Mode
Switch requester` node:

1. transmits a `normal packet` with a specific indicator on the `Mode Switch channel`,
2. switches the active channel from the `Base channel` to the `Mode Switch channel`.

The following messages will appear on the `Mode Switch requester` device when
the Mode Switch operation is terminated on it:

```
Packet has been sent // Step 1.
Channel is set to 0  // Step 2.
```

After that point, the device starts listening on the `Base channel`.

----

On the `Mode Switch accepter` node, the following messages are printed when
starting a Mode Switch process:

```
Channel is set to 20480
RAIL_EVENT_IEEE802154_MODESWITCH_START happened
Packet has been received on channel 20480:
0x0F, 0x16, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE
```

At the end of the Mode Switch process, the `Mode Switch accepter` switches back
to the `Base channel` by receiving a special formatted `normal packet` as shown
below:

```
Packet has been received on channel 20480:
0xF0, 0x16, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE
Channel is set to 0
Mode switch end, returned to the base channel
```

> Note: In `Infinite Mode Switch` both `Mode Switch requester` and `Mode
  Switch accepter` devices can terminate the Mode Switch operation. In that
  case the `Mode Switch accepter` transmits the special formatted `normal
  packet`, and the `Mode Switch requester` receives it.

----

The `info` command provides information on the device's operational mode such
as:

- `MCU Id`: the device's unique ID
- `Current channel`: the channel the device is currently listening on
- `Base channel`: the `Base channel` the device returns to when ending a Mode Switch process
- `PHY mode id`: the active `phyModeId`
- `PHY modulation`: the modulation type of the `Mode switch channel`
- `Ms state`: the Mode Switch state of the application
- `Fw RX Packet`: status of whether the received packets are printed out on the
  Serial interface

The two most important Mode Switch states are:

- `MS_IDLE`: indicates that the device is currently not in a Mode Switch
  process.
- `MS_ON_NEW_PHY`: indicates that the devices is currently in a Mode Switch
  process.

#### Normal Packet Transmission

Issue the `send` command on any node to request a `normal packet`
transmission on the `Current channel`:

```
send
> Send packet request
> Packet has been sent
```

On the receiver node the following response will be printed out on a `normal
packet` reception:

```
Packet has been received on channel <Current channel>:
0x0F, 0x16, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 
```

If the reception is disabled, although the nodes remain in RX state, the
received `normal` packet's will not be printed out but the LED0 toggles
indicating valid packet has been received.

The nodes will automatically switch back to RX mode either after a successful
or faulty reception or a transmission.

The reception can be disabled by the `receive` command.

```
receive 0
> Received packets: OFF
```

Receive mode can be enabled again by the same command:

```
receive 1
> Received packets: ON
```

> Note: Initiating or ending Mode Switch is still possible with a disabled
  reception state.

> Note: Issue the `info` command to see the current reception state.

> Note: Regardless of the specified `phyModeId`, the current version of this
  application always transmits a `normal packet` with the Rate field set to
  `0` (MCS0) on the OFDM channels. This means that, using the default radio
  configuration, the nodes might negotiate to communicate with different
  `phyModeId` (i.e., the `Mode Switch packet` is formatted correctly) during 
  the Mode Switch process, but the `normal packet` is always transmitted with the
  `phyModeId` = 32 configuration.

#### Changing Channels

The available channel list appears on starting the application. However,
you can print it again any time by issuing the `get_available_channels` command.

To switch channel without Mode Switching use the `set_channel` command:

```
set_channel 20480
```

Using the default radio configuration, you can switch between the FSK (0) and
OFDM (20480) channels. This command does not change the Mode Switch mode but
selects the first available `phyModeId` of the channel.

#### Notes

- Only one Mode Switch operation can be active at the same time on a device.
  That is, if the device is in a Mode Switch process, the `trig_mode_switch`
  command returns with an error.
- The application always transmits `normal` OFDM packets with MCS0. This means
  that the last 4 bits of the `phyModeId` are not active. Although the `Mode
  Switch start/end` packets are formatted correctly, the `Rate` field in the
  `standard` packets' PHR is not changed in the current version of the
  application. Despite 7 different OFDM configurations
  being available for the same channel, there is no difference when transmitting `normal`
  packets on the OFDM channel using different `phyModeId`s.
- You can't initiate a Mode Switch process if the `Current channel` is the same
as the one you want to change to.

## Peripherals

This example requires a `Simple Button` instance and two `Simple LED` instances
(`led0` and `led1`) installed in the Component Editor,
which is the default when creating this application for Silicon Labs radio boards.

The peripheral functions when the application is running on a
Silicon Labs development kit (that is, mainboard + radio board) are as follows.

- Pressing the PB0button on the development kit initiates packet
  transmission, just like the `send` CLI command.
- Pressing the PB1 button on the development kit requests mode switch
  operation, just like the `trig_mode_switch` CLI command, reusing the latest
  arguments it was issued.
- Toggles on LED0 indicate that a `normal packet` reception on the RX node was
  successful.
- Toggles on LED1 indicate that a `normal packet` transmission on the TX node
  was successful.

## What This Example Shouldn't Be Used For

It is not recommended to use this example in the following scenarios:

- Radio config validation: Since this application has strict limitations, if you
  have to evaluate a newly-generated radio configuration you might want to use the
  `Flex (RAIL) - RAILtest` example to validate your PHY(s) as an alternative.
- Radio range testing: Silicon Labs has a complete solution for testing the radio's
  performance if the two devices are placed far from each other. In such cases use
  the `Flex (RAIL) - Range Test` example application instead.

## Notes

> Due to the higher current consumption of the continuous radio usage
> (especially in RX Mode), it is not recommended to power the boards from a coin
> cell. Instead, a USB power bank can be used if portability is needed.

## Conclusion

The `Flex (RAIL) - Mode Switch` example application serves as reference
for how Wi-SUN mode switch packet exchange works in a real-life
RAIL implementation. It can be used on Silicon Labs development kits for a
quick link test and parts of the code may be useful in your own application, but
it is not suitable as a basis for starting your project. 
Use `Flex (RAIL) - Empty
Example` as your starting project instead.

## Resources

- [RAIL Tutorial
  Series](https://community.silabs.com/s/article/rail-tutorial-series?language=en_US):
  It is advised to read through the `Studio v5 series` first to familiarize 
  yourself with the
  basics of packet transmission and reception.

## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via
[Silicon Labs
Community](https://community.silabs.com/s/topic/0TO1M000000qHaKWAU/proprietary?language=en_US).
