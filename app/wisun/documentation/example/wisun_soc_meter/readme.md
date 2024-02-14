# Wi-SUN - SoC Meter

The Wi-SUN Meter sample application demonstrates the use of a UDP socket to emulate a metering-like application. The Meter sends sensor measurements (temperature and relative humidity from the SI7021 I2C sensor and dummy lux values) to a Collector device in the same Wi-SUN network.

## Getting Started

To get started with Wi-SUN and Simplicity Studio, see [QSG181: Wi-SUN SDK Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg181-wi-sun-sdk-quick-start-guide.pdf).

The Wi-SUN Meter sample application exposes a command-line interface to interact with the Wi-SUN stack. The goal of this procedure is to create the Wi-SUN network described in the following figure and have the Collector monitor the Meter.

![Collector/Meter Application Wi-SUN Network](readme_img1.png)

To get started with the example, follow the steps below:

* Flash the "Wi-SUN Border Router" demonstration to a first device and start the Border Router.
* Create and build the Meter project.
* Flash the Meter project to a second device.
* Create and build the Collector project.
* Flash the Collector project to a third device.
* Using Simplicity Studio, open consoles on both the Meter and Collector devices.
* Wait for the Collector and Meter to join the Wi-SUN Border Router network.

See the associated sections in [QSG181: Wi-SUN SDK Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg181-wi-sun-sdk-quick-start-guide.pdf) for step-by-step guidelines for each operation.

## Send Sensor Data to a Collector

The three Wi-SUN devices (Border Router, Meter, Collector) are now part of the same Wi-SUN network. See the *Wi-SUN - SoC Collector* readme to configure the Collector.

The connection between a Meter and the Collector starts with a registration request from the Collector.

    [Registration request from fd2a:6e01:9bfc:990c:20d:6fff:fe20:bd45]

After receiving a registration request, the Meter device sends groups of measurement data to the Collector periodically.
When the Meter sends sensor data to the Collector, a message is output in the console, as follows.

    [fd2a:6e01:9bfc:990c:20d:6fff:fe20:bd45: Measurement packet has been sent (80 bytes)]

The time between the cycles can be configured in FFN mode. In LFN device mode, the schedule time is different based on the selected LFN profile. Measurement and sending schedule can be further customized with callback functions.

The Collector can stop monitoring a Meter with a remove request.

    [Remove request from fd2a:6e01:9bfc:990c:20d:6fff:fe20:bd45]
    [Collector has been removed: fd2a:6e01:9bfc:990c:20d:6fff:fe20:bd45]

Meter devices can respond to async requests.

    [Async request from fd2a:6e01:9bfc:990c:20d:6fff:fe20:bd45]

## Troubleshooting

Before programming the radio board mounted on the WSTK, ensure the power supply switch is in the AEM position (right side), as shown.

![Radio Board Power Supply Switch](readme_img0.png)

## Resources

* [Wi-SUN Stack API documentation](https://docs.silabs.com/wisun/latest)
* [AN1330: Wi-SUN Mesh Network Performance](https://www.silabs.com/documents/public/application-notes/an1330-wi-sun-network-performance.pdf)
* [AN1332: Wi-SUN Network Setup and Configuration](https://www.silabs.com/documents/public/application-notes/an1332-wi-sun-network-configuration.pdf)
* [AN1364: Wi-SUN Network Performance Measurement Application](https://www.silabs.com/documents/public/application-notes/an1364-wi-sun-network-performance-measurement-app.pdf)
* [QSG181: Wi-SUN Quick-Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg181-wi-sun-sdk-quick-start-guide.pdf)
* [UG495: Wi-SUN Developer's Guide](https://www.silabs.com/documents/public/user-guides/ug495-wi-sun-developers-guide.pdf)

## Report Bugs & Get Support

You are always encouraged and welcome to ask any questions or report any issues you found to us via [Silicon Labs Community](https://community.silabs.com/s/topic/0TO1M000000qHc6WAE/wisun).
