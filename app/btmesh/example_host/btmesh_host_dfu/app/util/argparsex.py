# Copyright 2022 Silicon Laboratories Inc. www.silabs.com
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

import argparse
import io
import sys


class ArgumentParserExt(argparse.ArgumentParser):
    def __init__(
        self,
        prog=None,
        usage=None,
        description=None,
        epilog=None,
        parents=[],
        formatter_class=argparse.HelpFormatter,
        prefix_chars="-",
        fromfile_prefix_chars=None,
        argument_default=None,
        conflict_handler="error",
        add_help=True,
        allow_abbrev=True,
        help_as_exception=True,
        exit_on_error_ext=True,
    ):
        if add_help and help_as_exception:
            # The help command exits the application in argparse.ArgumentParser.
            # This might be problematic in case of an interactive application
            # where argparse is used to process command parameters in a command
            # loop because the application shall run after printing help message.
            # If help_as_exception is set to True then ArgumentParserExt raises
            # an exception when -h or --help option is found.
            # This means that the argparse.ArgumentParser add_help shall be set
            # to False when help_as_exception specified.
            add_help = False
        elif not add_help:
            help_as_exception = False
        super().__init__(
            prog,
            usage,
            description,
            epilog,
            parents,
            formatter_class,
            prefix_chars,
            fromfile_prefix_chars,
            argument_default,
            conflict_handler,
            add_help,
            allow_abbrev,
        )
        self.exit_on_error_ext = exit_on_error_ext
        if help_as_exception:
            self.add_argument(
                "--help",
                "-h",
                action=HelpActionExt,
                help="Show this help message and exit",
            )

    # The exit_on_error feature was added in Python 3.9 but this script needs to
    # support Python 3.7 so it can implement this feature by subclassing the
    # ArgumentParser class as it is recommended in the Python 3.7 documentation.
    # The Python 3.9 argparse exit_on_error feature is different a bit because
    # it throws ArgumentError with action parameter which is not available in
    # the error function so ArgumentError can't be raised so different parameter
    # and exception (exit_on_error_ext and ArgumentErrorExt) is used.
    # The Python 3.9 argparse exit_on_error feature is True by default so
    # it does not interfere with this code.
    def error(self, message, force_exit=False):
        if self.exit_on_error_ext or force_exit:
            super().error(message)
        else:
            raise ArgumentErrorExt(self, message)

    def print_error(self, message, file=None):
        if file is None:
            file = sys.stdout
        message = f"prog: {self.prog}, message: {message}"
        self._print_message(message + "\n", file=file)


class ArgumentErrorExt(Exception):
    def __init__(self, parser, message, *args):
        super().__init__(*args)
        self.parser = parser
        self.message = message


class ArgumentHelpException(Exception):
    def __init__(self, message, *args):
        super().__init__(*args)
        self.message = message


class HelpActionExt(argparse.Action):
    def __init__(
        self,
        option_strings,
        dest=argparse.SUPPRESS,
        default=argparse.SUPPRESS,
        help=None,
    ):
        super().__init__(
            option_strings=option_strings,
            dest=dest,
            default=default,
            nargs=0,
            help=help,
        )

    def __call__(self, parser, namespace, values, option_string=None):
        sio = io.StringIO()
        parser.print_help(sio)
        message = sio.getvalue().strip()
        raise ArgumentHelpException(message)
