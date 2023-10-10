#!/usr/bin/env python3
"""
ESL AP Sample Application.
"""

# Copyright 2023 Silicon Laboratories Inc. www.silabs.com
#
# SPDX-License-Identifier: Zlib
#
# The licensor of this software is Silicon Laboratories Inc.
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

import os
import sys
import argparse
import socket
try:
    import serial.tools.list_ports
except ImportError:
    pass
from ap_cli import CliProcessor
from ap_core import AccessPoint
import ap_logger

os.chdir(os.path.dirname(__file__))

def get_device_list():
    """ Find Segger J-Link devices based on USB vendor ID. """
    if 'serial'  not in sys.modules:
        return []
    device_list = []
    for com in serial.tools.list_ports.comports():
        if com.vid == 0x1366:
            device_list.append(com.device)
    return device_list

def get_ap_config(conn):
    """ Convert conn parameter into access point config string """
    # Try to autodetect serial device if no input is provided
    if conn is None:
        devices = get_device_list()
        if len(devices) == 0:
            print("error: No serial device found."
                  " Please specify connection explicitly.")
            sys.exit(1)
        if len(devices) > 1:
            print(f"error: {len(devices)} serial devices found: {', '.join(devices)}."
                  f" Please specify connection explicitly.")
            sys.exit(1)
        conn = devices[0]
    try:
        # Check for a valid IPv4 address.
        socket.inet_aton(conn)
        return f"-connection ip -device {conn}"
    except OSError:
        # Assume serial port.
        return f"-connection serial -device {conn}"

def main():
    if sys.version_info[0] < 3 or (sys.version_info[0] == 3 and sys.version_info[1] < 8):
        raise Exception('Requires at least python 3.8.0')
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('conn', nargs='?', help='Serial or TCP connection parameter')
    parser.add_argument('-m', '--cmd', help='Start in command line (manual) mode instead of default ESL Profile (auto) mode', action='store_true')
    parser.add_argument('-d', '--demo', help='Start in manual mode with EFRConnect demo mode enabled', action='store_true')
    parser.add_argument('-r', '--stdout', help='Redirect logging output from default stderr to stdout', action='store_true')
    parser.add_argument('-u', '--unsecure', help='Disable encryption for NCP communication', action='store_true')
    parser.add_argument('-l', '--log', help='Logging level to start with - can be changed later with verbosity command', type=str.upper, choices=ap_logger.LEVELS.keys(), default='INFO')
    args = parser.parse_args()

    ap_logger.stdout = args.stdout
    ap_logger.setLogLevel(ap_logger.LEVELS[args.log])

    # Instantiate the ESL application
    access_point = AccessPoint(get_ap_config(args.conn), args.unsecure, args.cmd, args.demo)
    cli_processor = CliProcessor(access_point)
    access_point.cli_queue = cli_processor.queue
    try:
        cli_processor.loop()
    except KeyboardInterrupt:
        pass
    try:
        access_point.shutdown()
    except KeyboardInterrupt:
        pass # avoid crash in case of slow shutdown meets impatient user :)

# Script entry point.
if __name__ == "__main__":
    main()
