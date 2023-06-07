# RAIL - NCP Simple TRX with CPC Support (VCOM)

## Introduction

This network coprocessor (NCP) application demonstrates the simplest exchange of
transmit and receive operation between two nodes implemented in RAIL. The
application supports communication with the [Co-Processor Communication
Daemon](https://github.com/SiliconLabs/cpc-daemon) over a UART interface.

## Prerequisites

The NCP Simple TRX with CPC Support example is supported on all EFR32
generations and families that support proprietary software except EFR32xG21
devices.

## Getting Started

This example shows the usage of the NCP Simple TRX application for sending and
receiving packets. For the demonstration, another device is required. We suggest
using our `RAIL - SoC Simple TRX` example.

The host system is required to run the [Co-Processor Communication
Daemon](https://github.com/SiliconLabs/cpc-daemon) application. We recommend our
CPC to serial example application to act as a bridge between the daemon and the
serial port. You can find it in your SDK folder under
*/app/flex/example/example_host/rail_host_simple_rail_to_serial*.

Compile the projects and download them to your radio boards. Open a serial
terminal on the SoC device. Connect the NCP application to the host side, launch
CPCd, and start the provided host application:

```
cpcd -c cpcd.conf --bind ecdh
rail_host_cpc_to_serial
```

The serial name of the NCP device will be printed:

```
Name of secondary pty side is </dev/pts/1>
```

On the host side, open a serial port on this address.

```
minicom --device /dev/pts/1 -H
```

The devices start in receive state. On the SoC device, issue the `send` command
to request packet transmission:

```
send
> Send packet request
> Packet has been sent
```

On the NCP side, the printing of the received packets is enabled by default and
can be toggled by sending `0` or `0x00` in the CPC channel. The following
response will be received in the CPC channel on packet reception:

```
0f 16 11 22 33 44 55 66 77 88 99 aa bb cc dd ee
```

If the reception is enabled, the device will automatically switch back to RX mode
either after a successful or faulty reception or a transmission.

To send packets from the NCP device, send `1` or `0x01` in the CPC channel. On
the SoC device, the packet will be printed on reception:

```
> Packet has been received: 0x0F, 0x16, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 
```

## Peripherals

This example requires a `Simple Button` instance and at least one `Simple LED`
instance (with `led0` being mandatory and `led1` being optional) installed in
the Project's `Software Components` window, which is the default creating this
application for Silicon Labs radio boards.

Below we discuss these peripheral functions when the application is running on a
Silicon Labs development kit (E.g., mainboard + radio board).

- Pressing the PB0/PB1 push buttons on the development kit initiates packet
  transmission, just like sending `1` or `0x01` in the CPC channel.
- Toggles on LED0 indicate that a packet reception on the RX node was
  successful.
- Toggles on LED1 indicate that a packet transmission on the TX node was
  successful.

## What This Example Shouldn't Be Used For

In the following scenarios, it is not advised to use this example:

- Radio config validation: since this application has strict limitations, if you
  have to evaluate a newly generated radio configuration, you might want to use
  `RAIL - SoC RAILtest` example to validate your PHY(s) as an alternative.
- Radio range testing: we have a complete solution for testing the radio's
  performance if the two devices are placed far from each other. In such cases, use
  the `RAIL - SoC Range Test` example application instead.

## Notes

> The application is designed in a way, that it can be run on an OS. You can add
> any RTOS support for this application in the `Software Components` window.
> Currently `MicriumOS` and `FreeRTOS` are supported.

> Due to the higher current consumption of the continuous radio usage
> (especially in RX Mode), it is not recommended to power the boards from a coin
> cell. Instead, an USB power bank can be used if portability is needed.

## Conclusion

The `RAIL - NCP Simple TRX with CPC Support (VCOM)` example application provides
a practical reference for understanding the fundamentals of proprietary packet
exchange implemented in RAIL, while also serving as a useful starting point for
working with CPC alongside RAIL. Apart from using it on Silicon Labs example
kits for a quick link test, there is little use of starting your application
from this example; rather you might reuse some part of the implementation of
this code by copying into your project. We recommend to use `RAIL - SoC Empty`
as a starting project instead.

## Resources

- [RAIL Tutorial
  Series](https://community.silabs.com/s/article/rail-tutorial-series?language=en_US):
  it is advised to read through the `Studio v5 series` first to familiarize the
  basics of packet transmission and reception
- [AN1351]((https://www.silabs.com/documents/public/application-notes/an1351-using-co-processor-communication_daemon.pdf)):
Using the Co-Processor Communication Daemon (CPCd)

## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via
[Silicon Labs
Community](https://community.silabs.com/s/topic/0TO1M000000qHaKWAU/proprietary?language=en_US).
