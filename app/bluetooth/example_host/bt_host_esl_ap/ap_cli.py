"""
ESL AP CLI.
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

import cmd
import queue
import re
import threading
import time
import struct
from datetime import datetime as dt
import ap_logger
from ap_core import AccessPoint
from ap_config import IOP_TEST, BLOCKING_WAIT_TIMEOUT
from ap_constants import LED_PATTERN_LENGTH, LED_DEFAULT_GAMUT, LED_DEFAULT_PATTERN, \
    LED_DEFAULT_PERIOD, LED_DEFAULT_DURATION, LED_DEFAULT_REPEATS, PA_INTERVAL_ABS_MIN, \
    PA_INTERVAL_ABS_MAX, PA_RESPONSE_SLOT_NUMBERS_MIN, PA_RESPONSE_SLOT_NUMBERS_MAX, \
    PA_RESPONSE_SLOT_SPACING_MIN, PA_RESPONSE_SLOT_SPACING_MAX, PA_RESPONSE_SLOT_DELAY_MIN, \
    PA_RESPONSE_SLOT_DELAY_MAX, PA_SUBEVENT_INTERVAL_MIN, PA_SUBEVENT_INTERVAL_MAX, \
    PA_SUBEVENT_MIN, PA_SUBEVENT_MAX, ADDRESS_TYPE_PUBLIC_ADDRESS, \
    ADDRESS_TYPE_STATIC_ADDRESS, ADDRESS_TYPE_RANDOM_RESOLVABLE_ADDRESS, \
    ADDRESS_TYPE_RANDOM_NONRESOLVABLE_ADDRESS, VALID_ESL_ID_NUMBER_REGEX, VALID_BD_ADDRESS_REGEX
from PIL import Image

def clamp(n, minn, maxn):
    return max(min(maxn, n), minn)

class CliProcessor(cmd.Cmd):
    """ CLI Processor """

    def __init__(self, ap: AccessPoint):
        super().__init__()
        self.queue = queue.Queue()
        self.ap = ap
        self.record_file = None

        # Logger
        self.log = ap_logger.getLogger("CLI")

        # LED control defaults
        self.led_pattern = bytearray(LED_DEFAULT_PATTERN)
        self.led_gamut = LED_DEFAULT_GAMUT
        self.led_period = bytearray(LED_DEFAULT_PERIOD)
        self.led_repeats = bytearray(LED_DEFAULT_DURATION)
        self.led_index = 0
        self.prompt = ''
        threading.Thread(target=self.poll_input, daemon=True).start()

    def poll_input(self):
        """ Provide input to the command queue from the stdin """
        while True:
            try:
                line = input(self.prompt)
            except EOFError:
                line = 'EOF'
            self.queue.put(line)

    def loop(self):
        """ Thread safe queue based version original command loop """
        self.preloop()
        stop = None
        while not stop:
            try:
                line = self.queue.get(timeout=BLOCKING_WAIT_TIMEOUT)
            except queue.Empty:
                continue
            line = self.precmd(line)
            stop = self.onecmd(line)
            stop = self.postcmd(stop, line)
        self.postloop()

    def do_demo(self, arg):
        """
        Start or stop advertising Dynamic GATT.

        usage: demo <on | off>
        parameters:
            <on>:      Start advertising Dynamic GATT.
            <off>:     Stop advertising Dynamic GATT.

        """
        arg_pat = r"(on|off)"
        if self.arg_check_ok(arg, arg_pat):
            arg_list = arg.split()
            if arg_list[0] == "on":
                self.ap.ap_adv_start()
            elif arg_list[0] == "off":
                self.ap.ap_adv_stop()
        else:
            self.do_help("demo")

    def do_scan(self, arg):
        """
        Start or stop scanning for advertising ESL devices.

        usage: scan <start [active] | stop>
        parameters:
            <start>:    Start scanning for advertising ESL devices.
            <stop>:     Stop scanning for advertising ESL devices.
            [active]:   Start active scan instead of default passive.

        """
        arg_pat = r"(start(\s+active)?|stop)"
        if self.arg_check_ok(arg, arg_pat):
            active_scan = False
            arg_list = arg.split()

            if arg_list[0] == "start":
                if len(arg_list) > 1:
                    active_scan = True
                self.ap.ap_scan(True, active_scan)
            elif arg_list[0] == "stop":
                self.ap.ap_scan(False, active_scan)
        else:
            self.do_help("scan")

    def do_connect(self, arg):
        """
        Connect to an ESL device with the specified address.

        usage: connect <bt_addr | esl_id [g=<group_id>]> [<address_type>]
        parameters:
            <bt_addr>:      Bluetooth address (e.g. 'AA:BB:CC:DD:EE:22') in case insensitive format.
            <esl_id>:       ESL ID of the tag.
            [g=<group_id>]: ESL group ID (optional for esl_id, only - default is group 0)
            [address_type]: ESL address type (optional), possible values:
                            - public :      Public device address (default)
                            - static :      Static device address
                            - rand_res :    Resolvable private random address
                            - rand_nonres : Non-resolvable private random address

        Notes: <esl_id> and <group_id> can be used instead of <bt_addr> if ESL is already configured.
               <address_type> will be taken into account only if the given <bt_addr> is unknown - otherwise
               the proper type reported by the remote device will be used.
               If the group ID is not given after the ESL ID then the default value group zero is used.
               This applies to many commands expecting the group ID as optional parameter.
               The auto-configuring uses the following schema for ESL
               addressing: (16 * number_of_already_synchronized_tags) + 1

        """
        arg_pat = r"((" + VALID_ESL_ID_NUMBER_REGEX + "(\s+g=\d+)?)|" + VALID_BD_ADDRESS_REGEX + ")(\s+(public|static|rand_res|rand_nonres))?"
        if self.arg_check_ok(arg, arg_pat):
            arg_list = arg.split()
            group_id = 0
            bt_addr = None
            esl_id = None
            address_type = None
            if arg_list[0].isnumeric():
                esl_id = int(arg_list[0])
                if len(arg_list) > 1:
                    if re.fullmatch(r"g=\d+", arg_list[1]) is not None:
                        group_id = int(arg_list[1][2:])
            else:
                bt_addr = arg_list[0].lower()

            if len(arg_list) > 1:
                if re.fullmatch(r"public", arg_list[-1]) is not None:
                    address_type = ADDRESS_TYPE_PUBLIC_ADDRESS
                elif re.fullmatch(r"static", arg_list[-1]) is not None:
                    address_type = ADDRESS_TYPE_STATIC_ADDRESS
                elif re.fullmatch(r"rand_res", arg_list[-1]) is not None:
                    address_type = ADDRESS_TYPE_RANDOM_RESOLVABLE_ADDRESS
                elif re.fullmatch(r"rand_nonres", arg_list[-1]) is not None:
                    address_type = ADDRESS_TYPE_RANDOM_NONRESOLVABLE_ADDRESS

            self.ap.ap_connect(esl_id, bt_addr, group_id, address_type)
        else:
            self.do_help("connect")

    def do_disconnect(self, arg):
        """
        Initiate the Periodic Advertisement Sync Transfer process then
        disconnect from an ESL device with the specified address.

        usage: disconnect [bt_addr | esl_id [g=<group_id>]]
        parameters:
            [bt_addr]:      Bluetooth address (e.g. 'AA:BB:CC:DD:EE:22') in case insensitive format.
            [esl_id]:       ESL ID of the tag.
            [g=<group_id>]: ESL group ID (optional for esl_id, only - default is group 0)

        Note: Should no address be given, then the default active connection will
              be closed if any.

        """
        arg_pat = r"((" + VALID_ESL_ID_NUMBER_REGEX + "(\s+g=\d+)?)|" + VALID_BD_ADDRESS_REGEX + ")?"
        if self.arg_check_ok(arg, arg_pat):
            arg_list = arg.split()
            group_id = 0
            bt_addr = None
            esl_id = None
            if len(arg_list):
                if arg_list[0].isnumeric():
                    esl_id = int(arg_list[0])
                    if len(arg_list) > 1:
                        if re.fullmatch(r"g=\d+", arg_list[1]) is not None:
                            group_id = int(arg_list[1][2:])
                else:
                    bt_addr = arg_list[0].lower()

            self.ap.ap_disconnect(esl_id, bt_addr, group_id)
        else:
            self.do_help("disconnect")

    def do_list(self, arg):
        """
        List tag information.

        usage: list <advertising, a> | <synchronized, s> | <usynchronized, u> | <connected, c> [verbose, v]
        parameters:
            <advertising, a>:    List advertising tag information
            <blocked, b>:        List blocked (advertising) tag information
            <connected, c>:      List connected tag information
            <synchronized, s>:   List synchronized tag information
            <unsynchronized, u>: List unsynchronized tag information
            [verbose, v]:        List more detailed information (optional)
            [g=<group_id>]:      ESL group ID filter (optional - default: all group)

        Examples: list a verbose
                  list synchronized v
        Note:     To reset the list of advertising and blocked lists you may want to issue a <scan start> command at any time.
        """
        arg_list = arg.split()
        param_list = []
        verbose = False
        arg_pat = r"((advertising|a)|(synchronized|s)|(unsynchronized|u)|(connected|c)|(blocked|b))(\s+(verbose|v))?(\s+g=\d+)?"
        commands = [c for c in re.split(r"[()|+?]", arg_pat) if c.strip() and c != "\\s"]
        group_id = None
        if self.arg_check_ok(arg, arg_pat):
            if any(x in arg_list for x in commands[10:12]):
                verbose = True
            # Advertising
            if any(x in arg_list for x in commands[0:2]):
                param_list.append(commands[0])
            # Synchronized
            if any(x in arg_list for x in commands[2:4]):
                param_list.append(commands[2])
            # Unsynchronized
            if any(x in arg_list for x in commands[4:6]):
                param_list.append(commands[4])
            # Connected
            if any(x in arg_list for x in commands[6:8]):
                param_list.append(commands[6])
            # Blocked
            if any(x in arg_list for x in commands[8:10]):
                param_list.append(commands[8])
            if m := re.search(r"g=\d+", arg):
               group_id = int(m.group(0)[2:])
            self.ap.ap_list(param_list, verbose, group_id)
        else:
            self.do_help("list")

    def do_led(self, arg):
        """
        Turn on / off or flash an LED utilizing the LED control command.

        usage: led <on | off | flash> <esl_id | all> [g=<group_id>] [default]
               [pattern=<bits>] [on_period=<int>] [off_period=<int>] [brightness=<int>]
               [color=<#RGB>] [repeats=<times>] | [duration=<sec>] [index=<index>]
               [[time=<hh:mm:ss>] [date=<DD-MM-YYYY>] [delay=<delay_ms>] | [absolute=<abs_time>]]
        parameters:
            on:                    Turn LED on
            off:                   Turn LED off
            flash:                 Flash led based on a bit pattern
            <esl_id>:              ESL ID of the tag
                                   Note: 'all' also can be used as a broadcast address (0xff)
            [g=<group_id>]:        ESL group ID (optional, default is group 0)
            [default]:             Restore the default flashing pattern built-in with AP
            [pattern=<bits>]:      A string containing either '1's or '0's, max length: 40
            [on_period=<int>]:     integer value from 1 to 255, meaning 'delay *2ms' for on state
                                   bits of the pattern. '0' is prohibited
            [off_period=<int>]:    Integer value from 1 to 255, meaning 'delay *2ms' for off state
                                   bits of the pattern. '0' is prohibited
            [brightness=<int>]:    4 step brightness from 0 to 3
            [color=<RGB>]:         Red, green and blue values - only applies to LED with sRGB type
            [repeats=<times>]:     How many times the pattern shall be repeated.
                                   Mutually exclusive with 'duration=' param. Value set [1-32767]
            [duration=<sec>]:      How many seconds the pattern shall be repeated.
                                   Mutually exclusive with 'repeats=' param. Value set [1-32767]
            [index=<index>]:       Index of the LED (optional, 0 by default)
            [time=<hh:mm:ss>]:     Execution time of the command in hour:min:sec format. (optional)
                                   Note: If <delay_ms> is specified then it is also added to the
                                   calculated value as an additional delay
            [date=<DD-MM-YYYY>]    Execution date of the command in day-month-year numeric format
                                   (optional to time, only)
            [delay=<delay_ms>]:    Delay in milliseconds (optional)
            [absolute=<abs_time>]: Execution time of the command in ESL
                                   Absolute Time epoch value. Mutually exclusive with other delays.

        Notes: Almost all of the optional led control parameters are "sticky", meaning that the last
               values are preserved by the AP internally and will be re-used next time, if the given
               parameter is omitted in the argument list. This doesn't applies on the delay, time
               and absolute parameters, though.
               The following shortcuts can also be used as keyword replacement:
               'd' for default, 'p' for 'pattern', 'on' for 'on_period', 'of' for 'off_period',
               'b' for 'brightness', 'c' for 'color', 'r' for 'repeat', 'dn' for 'duration', 'i' for
               'index', 't' for 'time', 'd' for date, 'dy' for 'delay' and 'a' for 'absolute'.

        """
        arg_pat = r"(^on|^off|^flash)\s+(all|\d+)\b\s*(g=\d+\b)?\s*(d(efault)?\b)?\s*(p(attern)?=[0-1]+\b)?\s*(on(_period)?=\d+\b)?\s*(of(f_period)?=\d+\b)?\s*(b(rightness)?=[0-3]\b)?\s*(c(olor)?=[0-3]{3}\b)?\s*((r(epeats)?|d(uratio)?n)=\d+\b)?\s*(i(ndex)?=\d{1,3}\b)?\s*(a(bsolute)?=\d+\b|(((t(ime)?=\d\d:\d\d:\d\d(\.\d{3})?(\s+d(ate)?=(0[1-9]|[12][0-9]|3[01])[- /.](0[1-9]|1[012])[- /.](20|21)[0-9]{2})?\b)?\s*(d(ela)?y=\d+\b)?)))?"
        group_id = 0
        now = dt.now()
        self.ap.absolute_now = self.ap.get_absolute_time(now)

        if self.arg_check_ok(arg, arg_pat):
            arg_list = []
            [arg_list.append(i) for i in re.search(arg_pat, arg).groups() if i is not None and i not in arg_list]
            esl_id = arg_list[1]
            index = self.led_index
            delay_ms = 0
            absolute_base = None
            repeat_field = bytearray(2)  # initialised to "LED Off"
            pattern = None
            period = self.led_period.copy()
            gamut = self.led_gamut
            input_error = False

            if arg_list[0] == "on":
                repeat_field[0] |= 1   # set the LSB to one for "LED on"
            elif arg_list[0] == "flash":
                pattern = self.led_pattern.copy()

            # Group id
            if len(arg_list) > 2 and re.fullmatch(r"g=\d+", arg_list[2]):
                group_id = int(arg_list[2][2:])

            for item in arg_list:
                # LED index
                if re.fullmatch(r"i(ndex)?=\d+", item) is not None:
                    index = int(re.findall(r"\d+", item)[0])
                # Brightness
                elif re.fullmatch(r"b(rightness)?=\d", item) is not None:
                    brightness = clamp(int(re.findall(r"\d", item)[0]), 0, 3)
                    gamut = ((int.from_bytes(gamut, byteorder="little") & 0x3f) | (brightness << 6)).to_bytes(1, "little")
                # Color
                elif re.fullmatch(r"c(olor)?=\d+", item) is not None:
                    text = bytearray(re.findall(r"\d+", item)[0],'utf-8')
                    r,g,b = struct.unpack('ccc', text)
                    color = (int(b) << 4) | (int(g) << 2) | int(r)
                    gamut = ((int.from_bytes(gamut, byteorder="little") & 0xc0) | color).to_bytes(1, "little")
                # Delay
                elif re.fullmatch(r"d(ela)?y=\d+", item) is not None:
                    delay_ms += int(re.findall(r"\d+", item)[0])
                    absolute_base = self.ap.absolute_now
                # Time
                elif re.fullmatch(r"t(ime)?=\d\d:\d\d:\d\d(\.\d{3})?(\s+d(ate)?=(0[1-9]|[12][0-9]|3[01])[- /.](0[1-9]|1[012])[- /.](20|21)[0-9]{2})?", item) is not None:
                    item = item.split("=", 2)
                    item[1] = item[1].split(" ", 1)[0]
                    date = None
                    d_msec=0
                    d_hour, d_min, d_sec = int(item[1][0:2]), int(item[1][3:5]), int(item[1][6:8])
                    if len(item[1]) > 9:
                        d_msec=int(item[1][9:12])
                    if len(item) > 2:
                        date = now
                        try:
                            date = date.replace(day=int(item[2][0:2]), month=int(item[2][3:5]), year=int(item[2][6:10]))
                        except:
                            self.log.error("Invalid date: " + item[2] + "!")
                            return
                    try:
                        delay_ms += self.ap.calculate_exec_time(now, d_hour, d_min, d_sec, d_msec, date)
                        absolute_base = self.ap.absolute_now
                    except:
                        self.log.error("Requested delay can't be set, command igored!")
                        return
                # Absolute time raw value
                elif re.fullmatch(r"a(bsolute)?=\d+", item) is not None:
                    absolute_base = int(re.findall(r"\d+", item)[0])
                    if absolute_base == 0:
                        delay_ms = None

            if pattern is not None:
                repeat_field = self.led_repeats
                for item in arg_list:
                    # Restore default
                    if re.fullmatch(r"d(efault)?\b", item) is not None:
                        pattern = bytearray(LED_DEFAULT_PATTERN)
                        gamut = LED_DEFAULT_GAMUT
                        period = bytearray(LED_DEFAULT_PERIOD)
                        repeat_field = bytearray(LED_DEFAULT_DURATION)
                    # LED pattern
                    elif re.fullmatch(r"p(attern)?=\d+", item) is not None:
                        bitstream = re.findall(r"\d+", item)[0]
                        if(len(bitstream) > LED_PATTERN_LENGTH * 8) or (bitstream.find("1") == -1 and not IOP_TEST):
                            self.log.error("Pattern length shall not exceed 40 bits and shall comprise of at least one bit set to 1.")
                            input_error = True
                        else:
                            pattern = bytearray(int(bitstream, 2).to_bytes(LED_PATTERN_LENGTH, "little")) # convert the string to binary
                    # Off_period
                    elif re.fullmatch(r"of(f_period)?=\d+", item) is not None:
                        off_period = int(re.findall(r"\d+", item)[0])
                        low_limit = 1 if not IOP_TEST else 0
                        if (off_period < low_limit or off_period > 255):
                            self.log.error("LED off period has to be between [1,255], aborting")
                            input_error = True
                        else:
                            period[0] = off_period
                    # On_period
                    elif re.fullmatch(r"on(_period)?=\d+", item) is not None:
                        on_period = int(re.findall(r"\d+", item)[0])
                        low_limit = 1 if not IOP_TEST else 0
                        if (on_period < low_limit or on_period > 255):
                            self.log.error("LED on period has to be between [1,255], aborting")
                            input_error = True
                        else:
                            period[1] = on_period
                    # Duration
                    elif re.fullmatch(r"d(uratio)?n=\d+", item) is not None:
                        duration = int(re.findall(r"\d+", item)[0])
                        if duration <= 0x7FFF: # only 15 bits long!
                            repeat_field = bytearray(int((duration << 1) | 1).to_bytes(2, "little"))
                        else:
                            self.log.warning("Duration field value of %u out of bounds, ignored!", duration)
                    # Repeats
                    elif re.fullmatch(r"r(epeats)?=\d+", item) is not None:
                        repeats = int(re.findall(r"\d+", item)[0])
                        if repeats <= 0x7FFF: # only 15 bits long!
                            repeat_field = bytearray(int((repeats << 1)).to_bytes(2, "little"))
                        else:
                            self.log.warning("Repeats field value of %u out of bounds, ignored!", repeats)

                self.led_pattern = pattern.copy()
                self.led_period = period.copy()
                self.led_repeats = repeat_field.copy()
                pattern += period
            elif IOP_TEST: # IOP tests requires the pattern and period fields to be able to set for On and Off commands too (off standard behavior!)
                pattern = self.led_pattern.copy()
                pattern += period
                input_error = True

            self.led_gamut = gamut
            self.led_index = index

            if not input_error or IOP_TEST: # allow erroneous values only in IOP_TEST mode!
                absolute_value = None

                if delay_ms is None:
                    absolute_value = absolute_base
                elif absolute_base is not None:
                    absolute_value = int(absolute_base + delay_ms) & 0xFFFFFFFF
                    if absolute_value == 0: # do not send any unsolicited delete on overflow!!
                        absolute_value += 1

                self.ap.ap_led(esl_id, group_id, repeat_field, index, absolute_value,
                               int.from_bytes(gamut, byteorder="little"), pattern)
            else:
                self.log.warning("Implausible input error, LED command ignored!")
        else:
            self.do_help("led")

    def do_config(self, arg):
        """
        Configure the writable mandatory GATT characteristics of the ESL tag.

        usage: config [full] [esl_id=<ui8>] [g=<ui7>] [sync_key]
               [response_key] [time | absolute=<ui32>]
        parameters:
            full:           Configure everything in one step.
            esl_id=<u8>:    New ESL ID of the connected tag.
            g=<u7>:         New ESL group ID (optional, default is group 0).
            sync_key:       Set current Access Point Sync Key Material.
            response_key:   Generate then set new Response Key Material.
            time:           Set current Absolute Time of the ESL Access Point.
            absolute=<u32>: Set custom Absolute Time value. Mutually exclusive
                            with the 'time' parameter.

        Notes: Either the keyword 'all' or at least one of the optional parameters
               shall be given.
               The following shortcuts can also be used as keyword replacement:
               'i' for 'esl_id', 'g' for 'group', 'sk' for 'sync_key', 'rk' for
               'response_key', 't' for 'time', 'a' for 'absolute'.
        """
        arg_pat = r"(\bfull\b)?(\s*(i|esl_id)=\b([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])\b)?(\s*(g|group)=\b([0-9]|[1-9][0-9]|1[01][0-9]|12[0-7])\b)?(\s*(sk\b|sync_key))?(\s*(rk\b|response_key))?(\s*((t\b|time)|(a|absolute)=\d+))?"
        commands = ["esl_id=", "i=", "group=", "g=", "sync_key", "sk", "response_key", "rk", "time", "t", "absolute=", "a="]
        params = {}
        arg_list = arg.split()

        if self.arg_check_ok(arg, arg_pat) and len(arg_list) !=0:
            for item in arg_list:
                # All
                if re.fullmatch(r"full", item) is not None:
                    params['full'] = True
                # ESL ID
                elif any(x in item for x in commands[0:2]):
                    params['esl_addr'] = int(re.findall(r"\d+", item)[0])
                # Group
                elif any(x in item for x in commands[2:4]):
                    params['group_id'] = int(re.findall(r"\d+", item)[0])
                # Sync Key
                elif any(x in item for x in commands[4:6]):
                    params['sync_key'] = True
                # Response Key
                elif any(x in item for x in commands[6:8]):
                    params['response_key'] = True
                # Time
                elif any(x in item for x in commands[8:10]):
                    params['time'] = True
                    break;
                # Raw Absolute Time value
                elif any(x in item for x in commands[10:12]):
                    params['absolute_time'] = int(re.findall(r"\d+", item)[0])
            self.ap.ap_config(params)
        else:
            self.do_help("config")

    def do_image_update(self, arg):
        """
        Update tag image.

        usage: image_update <image_index> <imagefile_path> [raw | display_index=<index>] [label=<text>] [cw | ccw | flip] [cropfit]
        parameters:
            image_index:           Image index to update.
            imagefile_path:        Path of the image file.
            raw:                   Upload raw image file without any conversion.
            display_index=<u8>:    Try auto-conversion image for this display.
            label=<char>:          Label to be upload.
            cw:                    Clockwise rotation.
            ccw:                   Counter clockwise rotation.
            flip:                  Horizontal flip of the image.
            cropfit:               Crop the image for the given display.

        Notes: The following shortcuts can also be used as keyword replacement:
               'r' for 'raw', 'd' for 'display_index', 'l' for 'label'
               To allow spaces or other special characters including some escape sequences
               in either the file name or the label, please put these strings into double quote
               Example: image_update 0 ./img2.png label=\"Line 1\\nLine 2\"\n"

        """

        arg_pat = r'(\b\d+)\s+([\w:.~\\/]+|"(.*?[^\\])?(\\\\)*")\s*(r(aw)?|d(isplay_index)?=\d+)?\s*(l(abel)?=(".*(?:\n.+)?"|\w+))?\s*(c[c]?w\b|flip\b)?\s*(cropfit)?'
        if self.arg_check_ok(arg, arg_pat):
            raw_img = False
            display_index = None
            label = None
            rotation = None
            cropfit = False
            arg_list = [i for i in re.search(arg_pat, arg).groups() if i is not None]
            image_index = int(arg_list[0])
            filename = arg_list[1].replace('"', '')
            if len(arg_list) >= 3:
                for item in arg_list:
                    # Raw image
                    if re.fullmatch(r"r(aw)?", item):
                        raw_img = True
                        break; # skip any other arguments if the input is raw image data
                    # Label
                    elif re.fullmatch(r'(l(abel)?=(".*(?:\n.+)?"|\w+))', item):
                        label = item[item.find("=")+1:].replace("\"", "").replace("\\\\", "\\").replace("\\n", "\n")
                    # Display index
                    elif re.fullmatch(r"d(isplay_index)?=\d+", item):
                        display_index = int(re.findall(r"\d+", item)[0])
                    # Rotation
                    elif re.fullmatch(r"cw", item):
                        rotation = Image.ROTATE_270
                    elif re.fullmatch(r"ccw", item):
                        rotation = Image.ROTATE_90
                    elif re.fullmatch(r"flip", item):
                        rotation = Image.ROTATE_180
                    # Cropfit
                    elif re.fullmatch(r"cropfit", item):
                        cropfit = True

            self.ap.ap_imageupdate(image_index, filename, True, raw_img, display_index, label, rotation, cropfit)
        else:
            self.do_help("image_update")

    def do_unassociate(self, arg):
        """
        Unassociate ESL(s) from AP.

        usage: unassociate <bt_addr | <esl_id | all [g=<group_id>]>
        parameters:
            <bt_addr>:      Bluetooth address in case insensitive format
            <esl_id>:       ESL ID of the tag.
            [g=<group_id>]: ESL group ID (optional for esl_id, only - default is group 0)
        Note: the keyword 'all' can be used as a substitute for the ESL broadcast address (0xff)
        """
        arg_pat = r"(((all|" + VALID_ESL_ID_NUMBER_REGEX + ")(\s+g=\d+)?)|" + VALID_BD_ADDRESS_REGEX + ")"
        arg_list = arg.split()
        group_id = 0
        address = None

        if self.arg_check_ok(arg, arg_pat):
            if len(arg_list) > 1:
                if re.fullmatch(r"g=\d+", arg_list[1]) is not None:
                    group_id = int(arg_list[1][2:])
            address = arg_list[0]
            self.ap.ap_unassociate(address, group_id)
        else:
            self.do_help("unassociate")

    def do_mode(self, arg):
        """
        Changes ESL Access Point operation mode.

        usage: mode <auto | manual>
        parameters:
            <auto>:   Switch to automatic mode
            <manual>: Switch to manual mode

        """
        auto_mode = None
        if arg == "auto":
            auto_mode = True
        elif arg == "manual":
            auto_mode = False
        else:
            self.do_help("mode")
        self.ap.ap_mode(auto_mode)

    def do_read_sensor(self, arg):
        """
        Read sensor information.

        usage: read_sensor <esl_id> <sensor_index> [g=<group_id>]
        parameters:
            <esl_id>:       ESL ID of the tag.
            <sensor_index>: Sensor index.
            [g=<group_id>]: ESL group ID (optional, default is group 0)
        """
        arg_list = arg.split()
        esl_id = sensor_idx = None
        group_id = 0

        if self.arg_check_ok(arg, r"\d+\s+\d+(\s+g=\d+)?"):
            esl_id = arg_list[0]
            sensor_idx = int(arg_list[1])

            if len(arg_list) > 2:
                if re.fullmatch(r"g=\d+", arg_list[2]) is not None:
                    group_id = int(arg_list[2][2:])

            # Check sensor index value
            if (sensor_idx < 0) or (sensor_idx > 255):
                self.log.warning("Sensor index must be between 0 and 255")
            else:
                self.ap.ap_read_sensor(esl_id, group_id, sensor_idx)
        else:
            self.do_help("read_sensor")

    def do_factory_reset(self, arg):
        """
        Execute factory reset on tag.

        usage: factory_reset <bt_addr | <esl_id | all [g=<group_id>]> [pawr]
        parameters:<bt_addr | <esl_id | all [g=<group_id>]>address in case insensitive format
            <esl_id>:       ESL ID of the tag.
            [g=<group_id>]: ESL group ID (optional for esl_id, only - default is group 0)
            [pawr]:         Force command through PAwR sync train even if the
                            addressed ESL is currently connected
        Note: the keyword 'all' can be used as a substitute for the ESL broadcast address (0xff)
        """
        arg_pat = r"(((all|" + VALID_ESL_ID_NUMBER_REGEX + ")(\s+g=\d+)?)|" + VALID_BD_ADDRESS_REGEX + ")(\s+pawr)?"
        arg_list = arg.split()
        group_id = 0
        address = None
        force_pawr = False

        if self.arg_check_ok(arg, arg_pat):
            address = arg_list[0]
            if len(arg_list) > 1:
                for item in arg_list:
                    if re.fullmatch(r"g=\d+", item) is not None:
                        group_id = int(arg_list[1][2:])
                    elif re.fullmatch(r"pawr", item) is not None:
                        force_pawr = True
            self.ap.ap_factory_reset(address, group_id, force_pawr)
        else:
            self.do_help("factory_reset")

    def do_delete_timed(self, arg):
        """
        Delete a delayed command of an ESL Tag peripheral with the selected index.

        usage: delete_timed <led | display> <esl_id | all > <index> [g=<group_id>]
        parameters:
            <led | display> ESL peripheral device type to delete command of
            <esl_id>:       ESL ID of the tag
                            Note: 'all' also can be used as a broadcast address (0xff)
            <index>:        Led / display device index
            [g=<group_id>]: ESL group ID (optional, default is group 0)
        """
        arg_pat = r"(^led|^display)\s+(all|([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5]))\b\s+\b([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])\b\s*(g=\d+\b)?"
        arg_list = arg.split()
        group_id = 0
        esl_id = None

        if self.arg_check_ok(arg, arg_pat):
            esl_id = int(arg_list[1])
            device_index = int(arg_list[2])

            if len(arg_list) > 3:
                if re.fullmatch(r"g=\d+", arg_list[3]) is not None:
                    group_id = int(arg_list[3][2:])
 
            if arg_list[0] == "led":
                self.ap.ap_led(esl_id, group_id, bytearray(2), device_index, 0)
            else:
                self.ap.ap_display_image(esl_id, group_id, 0, device_index, 0)
        else:
            self.do_help("delete_timed")

    def do_refresh_display(self, arg):
        """
        Refresh tag display.

        usage: refresh_display <esl_id | all> <display_id> [g=<group_id>]
        parameters:
            <esl_id>:       ESL ID of the tag.
                            Note: 'all' also can be used as a broadcast address (0xff)
            <display_id>:   Display index
            [g=<group_id>]: ESL group ID (optional, default is group 0)
        """
        arg_list = arg.split()
        esl_id = display_idx = None
        group_id = 0

        if self.arg_check_ok(arg, r"(all|\d+)\s+\d+(\s+g=\d+)?"):
            esl_id = arg_list[0]
            display_idx = int(arg_list[1])

            if len(arg_list) > 2:
                if re.fullmatch(r"g=\d+", arg_list[2]) is not None:
                    group_id = int(arg_list[2][2:])

            # Check display index value
            if (display_idx < 0) or (display_idx > 255):
                self.log.warning("Display index must be between 0 and 255")
            else:
                self.ap.ap_refresh_display(esl_id, group_id, display_idx)
        else:
            self.do_help("refresh_display")

    def do_display_image(self, arg):
        """
        Display tag image.

        usage: display_image <esl_id | all> <image_index> <display_idx> [g=<group_id>] [[time=<hh:mm:ss>] [date=<DD-MM-YYYY>] [delay=<delay_ms>] | [absolute=<abs_time>]]
        parameters:
            <esl_id>:              ESL ID of the tag.
                                   Note: 'all' also can be used as a broadcast address (0xff)
            <image_index>:         Image index
            <display_idx>:         Display index
            [g=<group_id>]:        ESL group ID (optional, default is group 0)
            [time=<hh:mm:ss>]:     Execution time of the command in hour:min:sec format. (optional)
                                   Note: If <delay_ms> is specified then it is also added to the
                                   calculated value as an additional delay.
            [date=<DD-MM-YYYY>]    Execution date of the command in day-month-year numeric format
                                   (optional to time, only)
            [delay=<delay_ms>]:    Delay in milliseconds (optional)
            [absolute=<abs_time>]: absolute=<uint32_t>: Execution time of the command in ESL Absolute Time epoch value.

        Note: The following shortcuts can also be used as keyword replacement:
              't' for 'time', 'd' for date, 'dy' for 'delay' and 'a' for 'absolute'.

        """
        arg_pat = r"(all|\d+)\s+(\d+\b)\s+(\d+\b)\s*(g=\d+\b)?\s*(a(bsolute)?=\d+\b|(((t(ime)?=\d\d:\d\d:\d\d(\.\d{3})?(\s+d(ate)?=(0[1-9]|[12][0-9]|3[01])[- /.](0[1-9]|1[012])[- /.](20|21)[0-9]{2})?\b)?\s*(d(ela)?y=\d+\b)?)))?"
        now = dt.now()
        self.ap.absolute_now = self.ap.get_absolute_time(now)
        esl_id = image_idx = display_idx = None
        group_id = delay_ms = 0
        absolute_base = None

        if self.arg_check_ok(arg, arg_pat):
            arg_list = arg.split()[0:3] # these are all mandatory parameters and can be the same value -> ensure not to filter them by the following command:
            [arg_list.append(i) for i in re.search(arg_pat, arg).groups() if i is not None and i not in arg_list]
            esl_id = arg_list[0]

            for item in arg_list:
                # Delay
                if re.fullmatch(r"d(ela)?y=\d+", item) is not None:
                    delay_ms += int(re.findall(r"\d+", item)[0])
                    absolute_base = self.ap.absolute_now
                # Time
                elif re.fullmatch(r"t(ime)?=\d\d:\d\d:\d\d(\.\d{3})?(\s+d(ate)?=(0[1-9]|[12][0-9]|3[01])[- /.](0[1-9]|1[012])[- /.](20|21)[0-9]{2})?", item) is not None:
                    item = item.split("=", 2)
                    item[1] = item[1].split(" ", 1)[0]
                    date = None
                    d_msec=0
                    d_hour, d_min, d_sec = int(item[1][0:2]), int(item[1][3:5]), int(item[1][6:8])
                    if len(item[1]) > 9:
                        d_msec=int(item[1][9:12])
                    if len(item) > 2:
                        date = now
                        try:
                            date = date.replace(day=int(item[2][0:2]), month=int(item[2][3:5]), year=int(item[2][6:10]))
                        except:
                            self.log.error("Invalid date: " + item[2] + "!")
                            return
                    try:
                        delay_ms += self.ap.calculate_exec_time(now, d_hour, d_min, d_sec, d_msec, date)
                        absolute_base = self.ap.absolute_now
                    except:
                        self.log.error("Requested delay can't be set, command ignored!")
                        return
                # Absolute time raw value
                elif re.fullmatch(r"a(bsolute)?=\d+", item) is not None:
                    absolute_base = int(re.findall(r"\d+", item)[0])
                    if absolute_base == 0:
                        delay_ms = None
                # Group id
                elif re.fullmatch(r"g=\d+", item) is not None:
                    group_id = int(item[2:])

            image_idx = int(arg_list[1])
            display_idx = int(arg_list[2])
            # Check display and image index values
            if (image_idx < 0) or (image_idx > 255):
                self.log.warning("Image index must be between 0 and 255")
            elif (display_idx < 0) or (display_idx > 255):
                self.log.warning("Display index must be between 0 and 255")
            else:
                absolute_value = None

                if delay_ms is None:
                    absolute_value = absolute_base
                elif absolute_base is not None:
                    absolute_value = int(absolute_base + delay_ms) & 0xFFFFFFFF
                    if absolute_value == 0: # do not send any unsolicited delete on overflow!!
                        absolute_value += 1

                self.ap.ap_display_image(esl_id, group_id, image_idx, display_idx, absolute_value)
        else:
            self.do_help("display_image")

    def do_ping(self, arg):
        """
        Send ESL ping command.

        usage: ping <esl_id | all> [g=<group_id>]
        parameters:
            <esl_id>:       ESL ID of the tag.
                            Note: 'all' also can be used as a broadcast address (0xff) if IOP_TEST config True
                            (Although it still makes no sense as broadcast messages doesn't solicit any
                            response by the specification!)
            [g=<group_id>]: ESL group ID (optional, default is group 0)
        """
        arg_list = arg.split()
        group_id = 0

        if self.arg_check_ok(arg, r"(all\b|\d+\b)(\s+g=\d+\b)?"):
            esl_id = arg_list[0]

            if len(arg_list) > 1:
                if re.fullmatch(r"g=\d+", arg_list[1]) is not None:
                    group_id = int(arg_list[1][2:])
            self.ap.ap_ping(esl_id, group_id)
        else:
            self.do_help("ping")

    def do_vendor_opcode(self, arg):
        """
        Send generic ESL vendor specific command.

        usage: vendor_opcode <esl_id | all> [g=<group_id>] [data]
        parameters:
            <esl_id>:       ESL ID of the tag.
                            Note: 'all' also can be used as a broadcast address (0xff) if IOP_TEST config True
                            (Although it still makes no sense as broadcast messages doesn't solicit any
                            response by the specification!)
            [g=<group_id>]: ESL group ID (optional, default is group 0)
            [data]:         ASCII hexadecimal data stream up to 16 bytes overall - an appropriate TLV to the
                            given length will be built automatically.

        Examples: vendor_opcode 0 g=1 - there will be no extra payload, the resulting ESL TLV is 0F00 for group 1
                  vendor_opcode 5 0x0002 - 2 byte payload, the resulting ESL TLV is 2F050002 for default group 0
                  vendor_opcode 1 12233 - 3 byte payload, the resulting ESL TLV is 3F01012233

        Please note that if the payload string has odd number of ASCII hex bytes, then a single leading zero will
        be added.
        """
        arg_list = arg.split()
        group_id = 0
        data = None

        if self.arg_check_ok(arg, r"(all\b|\d+\b)(\s+g=\d+\b)?\s*((0(?i)[x])?(?i)[0-9a-f]{1,32})?"):
            esl_id = arg_list[0]

            for item in arg_list[1:]:
                if re.fullmatch(r"g=\d+", item) is not None:
                    group_id = int(item[2:])
                elif re.fullmatch(r"((0(?i)[x])?(?i)[0-9a-f]{1,32})", item) is not None:
                    prefix_pos = item.casefold().find('x')
                    if prefix_pos == -1:
                      prefix_pos = 0
                    else:
                      prefix_pos += 1
                    payload = int(item, base=16)
                    length = (len(item[prefix_pos:]) + 1) // 2
                    data = payload.to_bytes(length, byteorder='big')
            self.ap.ap_vendor_opcode(esl_id, group_id, data)
        else:
            self.do_help("vendor_opcode")

    def do_service_reset(self, arg):
        """
        Send Service Reset command.

        usage: service_reset <esl_id | all> [g=<group_id>]
        parameters:
            <esl_id>:       ESL ID of the tag.
                            Note: 'all' also can be used as a broadcast address (0xff)
            [g=<group_id>]: ESL group ID (optional, default is group 0)
        """
        arg_list = arg.split()
        group_id = 0
        esl_id = None

        if self.arg_check_ok(arg, r"(all|\d+)(\s+g=\d+)?"):
            esl_id = arg_list[0]

            if len(arg_list) > 1:
                if re.fullmatch(r"g=\d+", arg_list[1]) is not None:
                    group_id = int(arg_list[1][2:])
            self.ap.ap_service_reset(esl_id, group_id)
        else:
            self.do_help("service_reset")

    def sync_config(self, arg_list=[]):
        """
        Overwrite default PAWR parameters. Some parameters have a resolution of 1.25msec or 0.125 msec
        If this requirement is not met, the nearest available value will be used
        """
        if arg_list is None:
            return
        if len(arg_list) <= 2:
            self.log.info("Current sync parameters:")
            params = self.ap.get_pawr_params()

            if len(arg_list) != 0:
                params[0] = arg_list[0]
                params[1] = arg_list[-1]

            self.log.print("Minimum Periodic Interval: " + str((1.25 * params[0])) + " ms (" + str(params[0]) + ")")
            self.log.print("Maximum Periodic Interval: " + str((1.25 * params[1])) + " ms (" + str(params[1]) + ")")
            self.log.print("Subevent Count:            " + str(params[2]))
            self.log.print("Subevent Interval:         " + str((1.25 * params[3])) + " ms (" + str(params[3]) + ")")
            self.log.print("Response Slot Delay:       " + str((1.25 * params[4])) + " ms (" + str(params[4]) + ")")
            self.log.print("Response Slot Duration:    " + str((0.125 * params[5])) + " ms (" + str(params[5]) + ")")
            self.log.print("Response Slot Count:       " + str(params[6]))
            return
        elif len(arg_list) < 7:
            self.log.error("One or more parameters missing!")
            return

        interval_min =          int(arg_list[0])
        interval_max =          int(arg_list[1])
        subevent_count =        int(arg_list[2])
        subevent_interval =     int(arg_list[3])
        response_slot_delay =   int(arg_list[4])
        response_slot_spacing = int(arg_list[5])
        response_slot_count =   int(arg_list[6])

        if (interval_min > interval_max):
            self.log.error("The maximum interval can't be less than the minimal!")
        elif (1.25 * interval_min < PA_INTERVAL_ABS_MIN) or (1.25 * interval_min > PA_INTERVAL_ABS_MAX) \
          or (1.25 * interval_max < PA_INTERVAL_ABS_MIN) or (1.25 * interval_max > PA_INTERVAL_ABS_MAX):
            self.log.error("Interval settings are out of bounds!")
        elif (subevent_count < PA_SUBEVENT_MIN) or (subevent_count > PA_SUBEVENT_MAX):
            self.log.error("The subevent count is out of bounds!")
        elif (subevent_interval < PA_SUBEVENT_INTERVAL_MIN) or (subevent_interval > PA_SUBEVENT_INTERVAL_MAX):
            self.log.error("The subevent interval is out of bounds!")
        elif (response_slot_delay < PA_RESPONSE_SLOT_DELAY_MIN) or (response_slot_delay > PA_RESPONSE_SLOT_DELAY_MAX):
            self.log.error("The response slot delay is out of bounds!")
        elif (response_slot_spacing < PA_RESPONSE_SLOT_SPACING_MIN) or(response_slot_spacing > PA_RESPONSE_SLOT_SPACING_MAX):
            self.log.error("The response slot spacing is out of bounds!")
        elif (response_slot_count < PA_RESPONSE_SLOT_NUMBERS_MIN) or (response_slot_count > PA_RESPONSE_SLOT_NUMBERS_MAX):
            self.log.error("The response slot count is out of bounds!")
        else:
            self.ap.set_pawr_interval([interval_min, interval_max])
            self.ap.pawr_configure(interval_min,
                                   interval_max,
                                   subevent_count,
                                   subevent_interval,
                                   response_slot_delay,
                                   response_slot_spacing,
                                   response_slot_count)

    def do_sync(self, arg):
        """
        Start / stop sending synchronization packets.

        usage: sync start [interval_min_ms] [interval_max_ms]
               sync stop
               sync config [ms] [<interval_min> <interval_max> <subevent_count>
                    <subevent_interval> <response_slot_delay>
                    <response_slot_spacing> <response_slot_count>]
        parameters:
            start:                 Start sending periodic synchronization packets
            stop:                  Stop sending periodic synchronization packets
            config:                Set PAWR parameters
            interval_min_ms:       Minimum periodic advertising interval in ms.
                                   Note: convenience option for 'start' command only!
            interval_max_ms:       Maximum periodic advertising interval in ms.
                                   Note: convenience option for 'start' command only!
            interval_min:          Minimum advertising interval in units of 1.25ms.
            interval_max:          Maximum advertising interval in units of 1.25ms.
            subevent_count:        Number of subevents
            subevent_interval:     Subevent interval in units of 1.25ms
            response_slot_delay:   Response slot delay in units of 1.25ms
            response_slot_spacing: Response slot spacing in units of 0.125ms
            response_slot_count:   Response slot count

        Notes: Using the optional 'ms' argument in the 'config' command allows you to
               specify timing parameters in milliseconds instead of their natural units,
               but this may introduce rounding errors. Please also note that with this
               option the fractional milliseconds can't be specified precisely.

        """
        start = False
        pa_interval = None

        if self.arg_check_ok(arg, r"stop|(start(\s+\d+\b){0,2})|(config\b(\s+ms)?((\s+\d+\b){7})?)"):
            arg_list = arg.split()
            if arg_list[0] == "config":
                if len(arg_list) > 1 and re.fullmatch(r"ms?", arg_list[1]) is not None:
                    self.log.warning("Parameters in milliseconds may result in inaccuracies due to rounding errors")
                    dividers = [1.25, 1.25, 1, 1.25, 1.25, 0.125, 1]
                    ms_values = [round(float(value) / div) for value, div in zip(arg_list[2:], dividers)]
                    self.sync_config(ms_values)
                else:
                    self.sync_config(arg_list[1:])
            else:
                if arg_list[0] == "start":
                    start = True
                    pa_interval = []

                    # There is one or two PA interval value from command line
                    if len(arg_list) > 1:
                        pa_interval.append(round(float(arg_list[1]) / 1.25))
                    if len(arg_list) > 2:
                        pa_interval.append(round(float(arg_list[2]) / 1.25))
                        if pa_interval[0] > pa_interval[1]:
                            self.log.error("Wrong periodic advertising interval values!" \
                                             " pa_interval_min: %d, pa_interval_max: %d",
                                             pa_interval[0], pa_interval[1])
                            return

                    if pa_interval:
                        # Check interval limits
                        for val in pa_interval:
                            if (val > PA_INTERVAL_ABS_MAX) or (val < PA_INTERVAL_ABS_MIN):
                                self.log.error("Wrong periodic advertising interval values!"
                                                 " Time range: 7.5 ms to 81.92 s")
                                return
                    self.log.info("Request Periodic Synchronization Transfer start as follows:")
                    self.sync_config(pa_interval)
                    if len(pa_interval) == 0:
                        pa_interval = None
                self.ap.ap_sync(start, pa_interval)
        else:
            self.do_help("sync")

    def do_set_rssi_threshold(self, arg):
        """
        Set RSSI filter threshold value.

        usage: set_rssi_threshold <rssi_value>
        Parameters:
            <rssi_value>: RSSI value.

        Note: Negative values are accepted, only!

        """
        if self.arg_check_ok(arg, r"-\d+"):
            self.ap.ap_set_rssi_threshold(int(arg))
        else:
            self.do_help("set_rssi_threshold")

    # AP scripting functionality

    def precmd(self, line):
        """ Optionaly log commands to record_file """
        if self.record_file and "script" and "record" not in line:
            print(line, file=self.record_file)
            self.record_file.flush()
        return line

    def do_script(self, arg):
        """
        Record or execute commands from an input file.

        usage: script <record> <filename> | <run> <filename> | <wait> <seconds>
        parameters:
            <record>:   Record commands to an output file <filename>
                        Note: If 'stop' given as a filename then recording of commands will stop.
            <run>:      Run commands from an input file <filename>
            <filename>: Filename to write / read AP commands
            <wait>:     Wait before running the next command
            <seconds>:  Wait interval in seconds

        Notes: Scripting is an experimental feature, only - it is lack of advanced
               features like programmed reactions to events or configuration dependent
               and / or conditional execution, etc.
               Recorded script files may contain script commands also, recursively.
               However, it is strongly advised to keep the recursion level low as possible.
               Use with care.

        """
        arg_pat = r"(record\s+((\w+[\w\.]*)|(stop)))|(run\s+\w+[\w\/\.:]*)|(wait\s+\d+)"
        if self.arg_check_ok(arg, arg_pat):
            arg_list = arg.split()

            if arg_list[0] == "record":
                self.record_commands(arg_list[1])
            elif arg_list[0] == "run":
                self.playback_commands(arg_list[1])
            elif arg_list[0] == "wait":
                self.ap_wait(arg_list[1])
        else:
            self.do_help("script")

    def do_update_complete(self, arg):
        """
        Send update complete command.

        usage: update_complete <bt_addr> | <esl_id [g=<group_id>]>
        parameters:
            <bt_addr>:      Bluetooth address in case insensitive format
            <esl_id>:       ESL ID of the tag.
            [g=<group_id>]: ESL group ID (optional for esl_id, only - default is group 0)

        Note: This command used only for testing purposes.
        """
        if IOP_TEST:
            arg_pat = r"((" + VALID_ESL_ID_NUMBER_REGEX + "(\s+g=\d+)?)|" + VALID_BD_ADDRESS_REGEX + ")"
            arg_list = arg.split()
            group_id = 0
            address = None

            if self.arg_check_ok(arg, arg_pat):
                address = arg_list[0]
                if len(arg_list) > 1:
                    if re.fullmatch(r"g=\d+", arg_list[1]) is not None:
                        group_id = int(arg_list[1][2:])
                self.ap.ap_update_complete(address, group_id)
            else:
                self.do_help("update_complete")
        else:
            self.log.warning("The update_complete command works only in IOP test mode!")

    def ap_wait(self, w_time):
        """
        Wait <w_time> seconds before running the next command

        Note: Pending commands continue to execute.
        """
        self.log.info("Waiting " + str(w_time) + " seconds")
        time.sleep(int(w_time))

    def playback_commands(self, fname):
        """ Playback commands from an input file """
        try:
            with open(fname) as f:
                self.log.info("Executing commands from file: " + fname)
                # Remove lines starting with '#' comment character
                command_list = [i for i in f.read().splitlines() if not i.startswith('#')]
                for line in command_list:
                    self.onecmd(line)
        except FileNotFoundError:
            self.log.warning("File not found: " + fname)

    def record_commands(self, fname):
        """ Record commands to a file """
        if fname != "stop":
            try:
                self.log.info("Recording commands to file: " + fname)
                self.record_file = open(fname, "w")
            except OSError:
                self.log.warning("Cannot open file: " + fname)
        else:
            if self.record_file:
                self.log.info("Recording of commands stopped")
                self.record_file.close()
                self.record_file = None
            else:
                self.log.info("There's no recording to stop!")

    def do_exit(self, arg):
        """ Exit from application

        Usage: exit

        """
        return True

    def emptyline(self):
        # Do nothing in case of empty command input
        pass

    def arg_check_ok(self, arg, pattern):
        """ Check command line arguments """
        return bool(re.fullmatch(pattern, arg) is not None)
