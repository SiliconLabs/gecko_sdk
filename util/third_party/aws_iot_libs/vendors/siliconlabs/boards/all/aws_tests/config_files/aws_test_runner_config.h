/*
 * FreeRTOS V1.1.4
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

#ifndef AWS_TEST_RUNNER_CONFIG_H
#define AWS_TEST_RUNNER_CONFIG_H

#include "stdint.h"

/* Uncomment this line if you want to run DQP_FR tests only. */
/* #define testrunnerAFQP_ENABLED */

#define testrunnerUNSUPPORTED    0

/* Uncomment this line to specify the delay (in milliseconds) to add before
 * starting the tests execution on device.
 * This is useful if the device takes some time after flashing to appear
 * on the serial port of the host machine OS. The serial console is used
 * by IDT to detect state of test execution on device. Therefore, the delay
 * value can be configured to ensure that the device (after flashing) is
 * available on host machine before it starts executing tests so that IDT
 * can detect when tests start execution on device through the serial console.
 */

#define AWS_TEST_RUNNER_DELAY_MS                         10

/* enable CLI support */
#define AWS_TEST_RUNNER_ENABLE_CLI_INPUT                 0

/* Universal Configurator will enable the required tests during generation. */
#define testrunnerFULL_WIFI_ENABLED                      0
#define testrunnerFULL_TASKPOOL_ENABLED                  0
#define testrunnerFULL_WIFI_PROVISIONING_ENABLED         0
#define testrunnerFULL_TCP_ENABLED                       0
#define testrunnerFULL_GGD_ENABLED                       0
#define testrunnerFULL_GGD_HELPER_ENABLED                0
#define testrunnerFULL_SHADOW_ENABLED                    0
#define testrunnerFULL_SHADOWv4_ENABLED                  0
#define testrunnerFULL_MQTTv4_ENABLED                    0
#define testrunnerFULL_MQTT_STRESS_TEST_ENABLED          0
#define testrunnerFULL_MQTT_AGENT_ENABLED                0
#define testrunnerFULL_MQTT_ALPN_ENABLED                 0
#define testrunnerFULL_OTA_CBOR_ENABLED                  0
#define testrunnerFULL_OTA_AGENT_ENABLED                 0
#define testrunnerFULL_OTA_PAL_ENABLED                   0
#define testrunnerFULL_PKCS11_ENABLED                    0
#define testrunnerFULL_PKCS11_MODEL_ENABLED              0
#define testrunnerFULL_CRYPTO_ENABLED                    0
#define testrunnerFULL_TLS_ENABLED                       0
#define testrunnerFULL_DEFENDER_ENABLED                  0
#define testrunnerFULL_POSIX_ENABLED                     0
#define testrunnerUTIL_PLATFORM_CLOCK_ENABLED            0
#define testrunnerUTIL_PLATFORM_THREADS_ENABLED          0
#define testrunnerFULL_BLE_ENABLED                       0
#define testrunnerFULL_BLE_STRESS_TEST_ENABLED           0
#define testrunnerFULL_BLE_KPI_TEST_ENABLED              0
#define testrunnerFULL_BLE_INTEGRATION_TEST_ENABLED      0
#define testrunnerFULL_BLE_END_TO_END_TEST_ENABLED       0
#define testrunnerFULL_FREERTOS_TCP_ENABLED              0
#define testrunnerFULL_SERIALIZER_ENABLED                0
#define testrunnerFULL_HTTPS_CLIENT_ENABLED              0
#define testrunnerFULL_COMMON_IO_ENABLED                 0
#define testrunnerFULL_CORE_MQTT_ENABLED                 0
#define testrunnerFULL_CORE_MQTT_AWS_IOT_ENABLED         0
#define testrunnerFULL_CORE_HTTP_ENABLED                 0
#define testrunnerFULL_CORE_HTTP_AWS_IOT_ENABLED         0
#define testrunnerFULL_CLI_ENABLED                       0
#define testrunnerFULL_DEVICE_SHADOW_ENABLED             0

/* make char type compatible with int8_t */
#define int8_t char

#endif /* AWS_TEST_RUNNER_CONFIG_H */
