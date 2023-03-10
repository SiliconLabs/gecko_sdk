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

import configparser
import logging
import sys
from pathlib import Path

import bgapi

from bgapix.bglibx import BGLibExt

from .cfg import app_cfg
from .exec import app_exec
from .ui import app_ui
from .util.argparsex import (ArgumentErrorExt, ArgumentHelpException,
                             ArgumentParserExt)

BTMESH_HOST_DFU_FOLDER = Path(__file__).parent.parent.resolve()
LOG_FORMAT = "%(asctime)s.%(msecs)03d-%(levelname)s-%(name)s: %(message)s"


logger = logging.getLogger("app")


class BtmeshDfuCli:
    DEFAULT_CFG_FILE_NAME = Path("btmesh_host_dfu_cfg.ini")

    def __init__(self):
        self.default_cfg_file_path = BTMESH_HOST_DFU_FOLDER / self.DEFAULT_CFG_FILE_NAME
        self.startup_parser = self.build_startup_parser()
        # Setup logging and load the configuration file before other parsers
        # are built because those use app_cfg for default argument values.
        # The startup_parser does not add help command and therefore it is not
        # necessary to handle ArgumentHelpException.
        try:
            pargs = self.startup_parser.parse_known_args()[0]
        except ArgumentErrorExt as e:
            message_warn = (
                "The application is terminated due to failure of first phase "
                "(startup) argument parsing. Only the startup phase arguments "
                "are shown in the error message because further arguments depend "
                "on the configuration which is not loaded at this point."
            )
            message = f"{e.message}\n{message_warn}"
            self.startup_parser.error(message, force_exit=True)
        logging.basicConfig(
            filename="btmesh_host_dfu.log",
            level=pargs.log,
            format=LOG_FORMAT,
            datefmt="%Y-%m-%d %H:%M:%S",
        )
        logger.info(f"{app_exec.APP_NAME} application is started.")
        self.load_cfg(pargs.cfg)
        self.cmd_parser = app_exec.build_cmd_parser()
        self.cli_parser = self.build_cli_parser([self.startup_parser, self.cmd_parser])

    def build_startup_parser(self, parents=[]) -> ArgumentParserExt:
        startup_parser = ArgumentParserExt(
            parents=parents, add_help=False, exit_on_error_ext=False
        )
        startup_parser.add_argument(
            "--log",
            type=str.upper,
            choices=logging._nameToLevel.keys(),
            help="Log level",
            default=logging.INFO,
        )
        startup_parser.add_argument(
            "--cfg",
            type=Path,
            help="Path of configuration file. (default: %(default)s) "
            "Note: if the configuration file exists then it loads that otherwise "
            "it creates a new file with the default values.",
            default=str(self.default_cfg_file_path),
        )
        return startup_parser

    def build_cli_parser(self, parents=[]) -> ArgumentParserExt:
        cli_parser = ArgumentParserExt(
            parents=parents, add_help=False, exit_on_error_ext=False
        )
        cli_parser.add_argument(
            "-i",
            "--interactive",
            help="Starts an interactive session which processes user commands",
            action="store_true",
            default=False,
        )
        cli_parser.add_argument(
            "--system-reset",
            help="System reset is initiated after the connection is opened.",
            action="store_true",
            default=False,
        )
        cli_parser.add_argument(
            "--factory-reset",
            help="Factory reset performs btmesh node reset and bt nvm erase in "
            "order to remove mesh keys and other persistent data from NCP node. "
            "The local BT Mesh Host DFU persistent data is deleted as well. "
            "System reset is executed after the persistent data is deleted.",
            action="store_true",
            default=False,
        )
        # Connection shall be specified by USB or IP information.
        # These are mutually exclusive but it is mandatory to provide one.
        conn_group = cli_parser.add_mutually_exclusive_group(required=True)
        conn_group.add_argument(
            "--ip",
            help="IP address and port of the device to connect (format ip:port)",
            default=None,
        )
        conn_group.add_argument(
            "--usb",
            help="USB device file or COM port of the device to connect",
            default=None,
        )
        cli_parser.add_argument(
            "--xapi",
            dest="api_xmls",
            help="XML file paths for the API references, from the used SDKs",
            action="append",
        )
        return cli_parser

    def load_cfg(self, cfg_path: Path):
        try:
            if cfg_path.exists() and cfg_path.is_file():
                with cfg_path.open() as cfg_file:
                    app_cfg.load_cfg(cfg_file)
            else:
                if cfg_path == self.default_cfg_file_path:
                    with cfg_path.open("w") as cfg_file:
                        app_cfg.save_default_cfg_file(cfg_file)
                    with cfg_path.open() as cfg_file:
                        app_cfg.load_cfg(cfg_file)
                else:
                    self.cli_parser.error(
                        f"Cfg file ({cfg_path}) does not exist.", force_exit=True
                    )
        except configparser.Error as e:
            app_ui.error(f"Configuration parse error in {cfg_path}.")
            app_ui.error(e.message)
            sys.exit(-1)
        except ValueError as e:
            app_ui.error(f"Configuration conversion error in {cfg_path}.")
            app_ui.error(str(e))
            sys.exit(-1)

    def main(self):
        # Process command line arguments when called without parameters
        try:
            args = self.cli_parser.parse_args()
        except ArgumentHelpException as e:
            app_ui.info(e.message)
            sys.exit(0)
        except ArgumentErrorExt as e:
            self.cli_parser.error(e.message, force_exit=True)
        self.usb = args.usb
        if args.ip:
            ip_arg_split = args.ip.split(":")
            if len(ip_arg_split) != 2:
                self.cli_parser.error("Invalid IP argument format (IP:Port)")
            self.ip = ip_arg_split[0]
            self.port = ip_arg_split[1]
        else:
            self.ip = None

        if self.usb:
            connector = bgapi.SerialConnector(self.usb)
        elif self.ip and self.port:
            connector = bgapi.SocketConnector(self.ip, self.port)
        else:
            self.cli_parser.error("USB or IP connection data missing.", force_exit=True)
        app_exec.lib = BGLibExt(connector, args.api_xmls, response_timeout=5)
        app_exec.interactive = args.interactive
        app_exec.open(args.system_reset, args.factory_reset)
        command = args.command
        try:
            if command:
                idx = sys.argv.index(command)
                # The command shall be set to None before the onecmd call
                # otherwise it leads to infinite loop when exception occurs
                # in onecmd method
                command = None
                app_exec.onecmd(args.command + " " + " ".join(sys.argv[idx + 1 :]))
            if app_exec.interactive:
                app_exec.cmdloop()
        finally:
            # Close the connection under any circumstances
            app_exec.close()


app_cli = BtmeshDfuCli()
