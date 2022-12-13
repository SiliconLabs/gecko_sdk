# Flex (RAIL) - Simple TRX Multi-PHY

## Introduction

The Simple TRX Multi-PHY example demonstrates the usage of multiple PHYs
selectable by channels. By default, there are two channels, one sub-GHz and one 2.4
GHz. The programmed device can be used as an endpoint or as a relay node. An
endpoint node is able to receive/transmit packages on the selected channel,
while a relay node routes the received packages according to the direction
selected. Both transmission and reception can be controlled using serial
commands.

## Prerequisites

The Simple TRX Multi-PHY example is supported on all EFR32 generations and
families that have dual-band support.

## Getting Started

This example implements a three-node network that consists of 2 endpoints that
use different channels and a relay that routes the packets between them.
`Endpoint 0` is referred as the endpoint which uses the sub-GHz channel, while
`Endpoint 1` is referred as the endpoint which uses the 2.4 GHz channel.

----

Compile the project and download the application to three radio boards. For the
endpoint devices, you can also use the Simple TRX sample application. The
following example assumes that you use Simple TRX Multi-PHY for the endpoints.

----

On startup the application's name will be displayed:

```
> Simple TRX Multiphy
```

The devices start in endpoint mode, set one of them to relay mode.

```
> set_mode 1
Mode set to relay
```

By default, the endpoints use the 2.4 GHz channel (i.e., channel 0). With the
`set_active_channel` command on `Endpoint 1`, set the endpoint to use the
sub-GHz channel (i.e., channel 1).

```
> set_active_channel 1
Active channel is set to 1
```

With the `set_direction` command on the relay node, set the direction of the
packet routing. In the following case, the relay is going to listen at channel 1
and route the received packets at channel 0. Therefore, the node will relay from
`Endpoint 1` to `Endpoint 0`.

```
> set_direction 1
Direction set to ch1 -> ch0
```

On `Endpoint 1` node, request a transmission by issuing the `send` command. You
can also use the push buttons on the development kit.

```
> send
Send packet request on channel 1
> Packet has been sent on channel: 1
```

On the relay node, the following response will be printed out on packet
reception and packet routing:

```
> Packet has been received on channel 1: 0x0F, 0x16, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE,
Packet has been sent on channel 0
```

On `Endpoint 0` node, the relayed packet will be printed out:
```
> Packet has been received on channel 1: 0x0F, 0x16, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE,
```

----

## Peripherals

This example requires a `Simple Button` instance and two `Simple LED` instances
(`led0` and `led1`) installed in the Project's `Software Components` tab,
which is the default when creating this application for Silicon Labs radio boards.

The peripheral functions when the application is running on a
Silicon Labs development kit (that is, mainboard + radio board) are as follows.

- When the device is in endpoint mode, pressing the PB0/PB1 buttons on the
  development kit initiates packet transmission at the active channel.
- Toggles on LED0/LED1 indicate that a packet reception or transmission was
  successful at channel 0 and channel 1, respectively.

## What This Example Shouldn't Be Used For

It is not recommended to use this example in the following scenarios:

- Radio config validation: Since this application has strict limitations, if you
  have to evaluate a newly-generated radio configuration you might want to use
  the `RAIL - SoC RAILtest` example to validate your PHY(s) as an alternative.
- Radio range testing: Silicon Labs has a complete solution for testing the radio's
  performance if the two devices are placed far from each other. In such cases
  use the `RAIL - SoC Range Test` example application instead.

## Notes

> The application is designed so that it can be run on an OS. You can add
> any RTOS support for this application in the `Software Components` tab.
> Currently `MicriumOS` and `FreeRTOS` are supported.

> Due to the higher current consumption of the continuous radio usage
> (especially in RX Mode), it is not recommended to power the boards from a coin
> cell. Instead, a USB power bank can be used if portability is needed.

## Conclusion

The `RAIL - SoC Simple TRX Multi-PHY` example application serves as reference to
get started with RAIL Multi-PHY applications.It can be used on Silicon Labs development kits for a
quick test and parts of the code may be useful in your own application, but
it is not suitable as a basis for starting your project. We recommend using
`RAIL - SoC Empty` as your starting project instead.

## Resources

- [RAIL Tutorial
  Series](https://community.silabs.com/s/article/rail-tutorial-series?language=en_US):
  it is advised to read through the `Studio v5 series` first to familiarize yourself with the
  basics of packet transmission and reception

- [Introduction to Multi-PHY and
  Multiprotocol](https://community.silabs.com/s/article/rail-tutorial-introduction-to-multi-phy-and-multiprotocol?language=en_US):
  if you want to get started with RAIL Multi-PHY solutions

- [Multi-PHY usecases and
  examples](https://community.silabs.com/s/article/rail-tutorial-multi-phy-usecases-and-examples?language=en_US):
  if you want to see more Multy-PHY examples

## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via
[Silicon Labs
Community](https://community.silabs.com/s/topic/0TO1M000000qHaKWAU/proprietary?language=en_US).
