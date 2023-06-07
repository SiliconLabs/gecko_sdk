# Connect: NCP Example

## Introduction

The Connect NCP project implements a Co-Processor Communication secondary
implementation of the Connect API. It can be used with the CPC daemon, the
Connect host library, and example applications.

## Prerequisites

To use this application, you will need:

- [CPC daemon](https://github.com/SiliconLabs/cpc-daemon)
- [Connect Host Library](https://github.com/SiliconLabs/Connect-NCP-Host)
- A Connect NCP application, like [the example in the above
  repo](https://github.com/SiliconLabs/Connect-NCP-Host/tree/master/app) 

Note that other NCP applications could be used as well, without changing the *CPC
daemon* and the *Connect Host Library*.

*Connect NCP* can be customized, but generally the only modifications needed are
the PHY configuration and the pin configuration.

## Usage

The example NCP application provides the same functionality as *Connect - SoC
Sink*, so it can be used with *Connect - SoC Sensor* devices.

## Detailed documentation

For further details, review the documentation and readme of the above github
projects and [UG435.08 - Network Co-Processor Applications with Silicon Labs
Connect v3.x](https://www.silabs.com/documents/public/user-guides/ug435-08-network-co-processor-applications-connect-v3x.pdf)

## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via
[Silicon Labs
Community](https://community.silabs.com/s/topic/0TO1M000000qHaKWAU/proprietary?language=en_US).
