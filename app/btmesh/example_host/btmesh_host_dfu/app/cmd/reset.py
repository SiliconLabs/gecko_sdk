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

from typing import Optional

from ..btmesh import app_btmesh
from ..cfg import app_cfg
from ..db import app_db
from ..ui import app_ui
from ..util.argparsex import ArgumentParserExt
from .cmd import BtmeshCmd


class BtmeshResetCmd(BtmeshCmd):
    @property
    def parser(self) -> ArgumentParserExt:
        return self.reset_parser

    @property
    def current_parser(self) -> Optional[ArgumentParserExt]:
        return self.current_parser

    def create_parser(self, subparsers) -> ArgumentParserExt:
        self.reset_parser = subparsers.add_parser(
            "reset",
            prog="reset",
            help="Perform system or factory reset based on the type option.",
            description="Perform system or factory reset based on the type option.",
            exit_on_error_ext=False,
        )
        self.reset_parser.add_argument(
            "--type",
            choices=["system", "factory"],
            default="system",
            help="System or factory reset selection (default: %(default)s)",
        )
        return self.reset_parser

    def __call__(self, arg) -> bool:
        pargs = self.parser.parse_args(arg.split())
        if pargs.type == "factory":
            app_db.clear()
            app_db.save()
            app_btmesh.factory_reset(app_cfg.reset.factory_reset_delay_s)
            app_ui.info("Factory reset completed")
        else:
            app_btmesh.system_reset()
            app_ui.info("System reset completed")
        return False


reset_cmd = BtmeshResetCmd()