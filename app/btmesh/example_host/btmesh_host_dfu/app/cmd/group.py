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

from typing import Dict, Iterable, Optional, Set, Tuple

from btmesh.db import ModelID
from btmesh.util import BtmeshRetryParams

from ..cfg import BtmeshDfuAppMdlProfile, app_cfg
from ..db import app_db
from ..grpctrl import app_grctrl
from ..ui import app_ui
from ..util.argparsex import ArgumentParserExt
from .cmd import BtmeshCmd


class BtmeshGroupCmd(BtmeshCmd):
    @property
    def parser(self) -> ArgumentParserExt:
        return self.group_parser

    @property
    def current_parser(self) -> Optional[ArgumentParserExt]:
        return getattr(self, "_current_parser", self.parser)

    def create_parser(self, subparsers) -> ArgumentParserExt:
        self.group_parser = subparsers.add_parser(
            "group",
            prog="group",
            help="Add, remove, update, rename and list app groups.",
            description="Add, remove, update and list app groups. "
            "App group update operation adds or removes models of node elements "
            "to or from existing app groups and modifies group address, appkey "
            "index and some publication parameters as well. "
            "App group contains node elements (unicast address) which contains "
            "specified models which shall subscribe or publish to the same "
            "group address with the same application key.",
            epilog=f"Many subcommand options of %(prog)s expects <mdlspec> and "
            f"<elemspec> type parameters. In order to avoid repetition and make "
            f"the argument help text shorter these are introduced in this epilog. "
            f"{app_ui.MDLSPEC_HELP} {app_ui.ELEMSPEC_HELP} {app_ui.NODESPEC_HELP}",
            exit_on_error_ext=False,
        )
        self.group_parser.set_defaults(group_subcmd=self.group_list_cmd)
        self.group_subparser = self.group_parser.add_subparsers(
            dest="group_subcmd_name",
            title="Subcommands",
            description="If no subcommand is provided then it defaults to 'list'.",
        )
        self.subparser_dict = dict(
            (
                self.create_group_add_parser(self.group_subparser),
                self.create_group_update_parser(self.group_subparser),
                self.create_group_list_parser(self.group_subparser),
                self.create_group_info_parser(self.group_subparser),
            )
        )
        return self.group_parser

    def add_pub_param_args(self, parser: ArgumentParserExt):
        parser.add_argument(
            "--pub-ttl",
            "-t",
            type=int,
            default=app_cfg.appgroup.pub_ttl_default,
            help="Publication Time-To-Live value of the app group. "
            "Valid publication TTL range is 0 or [2,127] and the special 255 value "
            "can be set to use default TTL of the node. (default: %(default)s)",
        )
        parser.add_argument(
            "--pub-cred",
            "-c",
            type=int,
            default=app_cfg.appgroup.pub_cred_default,
            help="Publication credentials of the app group. "
            "Friendship credential flag. If zero, publication is done using "
            "normal credentials. If one, it is done with friendship credentials, "
            "meaning only the friend can decrypt the published message and relay "
            "it forward using the normal credentials. The default value is 0. "
            "(default: %(default)s)",
        )
        parser.add_argument(
            "--pub-period",
            "-T",
            type=int,
            default=app_cfg.appgroup.pub_period_ms_default,
            help="Publication period in milliseconds of the app group."
            "Note that the resolution of the publication period is limited by "
            "the specification to 100ms up to a period of 6.3s, 1s up to a "
            "period of 63s, 10s up to a period of 630s, and 10 minutes above that."
            "Maximum period allowed is 630 minutes. (default: %(default)s)",
        )
        parser.add_argument(
            "--pub-tx-cnt",
            "-k",
            type=int,
            default=app_cfg.appgroup.pub_tx_cnt_default,
            help="Publication retransmission count of the app group. "
            "Valid values range from 0 to 7. (default: %(default)s)",
        )
        parser.add_argument(
            "--pub-tx-int",
            "-i",
            type=int,
            default=app_cfg.appgroup.pub_tx_int_ms_default,
            help="Publication retransmission interval in millisecond units of "
            "the app group. The range of value is 50 to 1600 ms, and the "
            "resolution of the value is 50 milliseconds. (default: %(default)s)",
        )

    def add_pub_addr_mdl_args(
        self, parser: ArgumentParserExt, support_remove_args=True
    ):
        parser.add_argument(
            "--pub-mdls",
            "-P",
            metavar="<mdlspec>",
            default=[],
            nargs="+",
            help="List of models which shall publish to the app group.",
        )
        parser.add_argument(
            "--pub-addrs",
            "-p",
            metavar="<elemspec>",
            default=[],
            nargs="+",
            help="List of element addresses where the specified models shall "
            "publish to app group. "
            "If the element address contains the subset of specified models "
            "then the publication is configured only for this subset based "
            "on the DCD unless --strict option is used.",
        )
        if support_remove_args:
            parser.add_argument(
                "--rm-pub-mdls",
                metavar="<mdlspec>",
                default=[],
                nargs="+",
                help="List of models which shall not publish to the app group "
                "any longer.",
            )
            parser.add_argument(
                "--rm-pub-addrs",
                metavar="<elemspec>",
                default=[],
                nargs="+",
                help="List of element addresses where the specified models shall "
                "not publish to app group any longer. "
                "If the element address contains the subset of specified models "
                "then the publication is configured only for this subset based "
                "on the DCD unless --strict option is used.",
            )

    def add_sub_addr_mdl_args(
        self, parser: ArgumentParserExt, support_remove_args=True
    ):
        parser.add_argument(
            "--sub-mdls",
            "-S",
            metavar="<mdlspec>",
            default=[],
            nargs="+",
            help="List of models which shall subscribe to the app group.",
        )
        parser.add_argument(
            "--sub-addrs",
            "-s",
            metavar="<elemspec>",
            default=[],
            nargs="+",
            help="List of element addresses where the specified models shall "
            "subscribe to app group. "
            "If the element address contains the subset of specified models "
            "then the subscription is configured only for this subset based "
            "on the DCD unless --strict option is used.",
        )
        if support_remove_args:
            parser.add_argument(
                "--rm-sub-mdls",
                metavar="<mdlspec>",
                default=[],
                nargs="+",
                help="List of models which shall not subscribe to the app group"
                "any longer.",
            )
            parser.add_argument(
                "--rm-sub-addrs",
                metavar="<elemspec>",
                default=[],
                nargs="+",
                help="List of element addresses where the specified models shall "
                "not subscribe to app group any longer. "
                "If the element address contains the subset of specified models "
                "then the subscription is configured only for this subset based "
                "on the DCD unless --strict option is used.",
            )

    def add_bind_addr_mdl_args(
        self, parser: ArgumentParserExt, support_remove_args=True
    ):
        parser.add_argument(
            "--bind-mdls",
            "-B",
            metavar="<mdlspec>",
            default=[],
            nargs="+",
            help="List of models which shall be bound to the app group.",
        )
        parser.add_argument(
            "--bind-addrs",
            "-b",
            metavar="<elemspec>",
            default=[],
            nargs="+",
            help="List of element addresses where the specified models shall "
            "be bound to app group. "
            "If the element address contains the subset of specified models "
            "then the appkey binding is configured only for this subset based "
            "on the DCD unless --strict option is used.",
        )
        if support_remove_args:
            parser.add_argument(
                "--rm-bind-mdls",
                metavar="<mdlspec>",
                default=[],
                nargs="+",
                help="List of models which shall not be bound to the app group "
                "any longer.",
            )
            parser.add_argument(
                "--rm-bind-addrs",
                metavar="<elemspec>",
                default=[],
                nargs="+",
                help="List of element addresses where the specified models shall "
                "not be bound to app group any longer."
                "If the element address contains the subset of specified models "
                "then the appkey binding is configured only for this subset based "
                "on the DCD unless --strict option is used.",
            )

    def add_mdl_profile_args(self, parser: ArgumentParserExt, support_remove_args=True):
        mdl_profile_choices = [mp.name for mp in app_cfg.appgroup.mdl_profiles]
        help_text = [
            "App group model profiles make it easier to provide publication, "
            "subscription and bind model parameters to app group commands. "
            "A model profile name refers to these model sets from the "
            "configuration file."
        ]
        for mp in app_cfg.appgroup.mdl_profiles:
            help_text.append(f"profile_{mp.name}: {mp.help}")
        parser.add_argument(
            "--profile",
            "-m",
            default=[],
            choices=mdl_profile_choices,
            nargs="+",
            help=" ".join(help_text),
        )
        if support_remove_args:
            parser.add_argument(
                "--rm-profile",
                default=[],
                choices=mdl_profile_choices,
                nargs="+",
                help=" ".join(help_text),
            )

    def add_group_addr_args(self, parser: ArgumentParserExt, update=False):
        GROUP_ADDR_UPDATE_WARN = "If group address is changed in an existing "
        "app group then it leads to the modification of the group address on "
        "each publication and subscription models of every publication and "
        "subscription element addresses of the app group."
        if update:
            group_addr_help_ext = f" {GROUP_ADDR_UPDATE_WARN}"
        else:
            group_addr_help_ext = ""
        parser.add_argument(
            "--group-addr",
            "-g",
            required=True,
            help=f"Group address of the app group. The selected publish models "
            f"are configured to publish to this address and the selected "
            f"subscription models are configured to subscribe to this address. "
            f"The group address can be specified as a binary (0b), octal(0o), "
            f"decimal, hex (0x) integer."
            f"{group_addr_help_ext}",
        )

    def add_appkey_index_args(self, parser: ArgumentParserExt, update=False):
        APPKEY_INDEX_UPDATE_WARN = "If appkey index is changed in an existing "
        "app group then it leads to the modification of the appkey bindings on "
        "each models of every element addresses of the app group which have "
        "appkey bindings."
        if update:
            appkey_index_help_ext = f" {APPKEY_INDEX_UPDATE_WARN}"
        else:
            appkey_index_help_ext = ""
        parser.add_argument(
            "--appkey-idx",
            "-a",
            type=int,
            required=True,
            help="Appkey index of the app group. The appkey index is bound to "
            "subscription and publish models and it used for publish messages."
            f"{appkey_index_help_ext}",
        )

    def add_auto_bind_args(self, parser: ArgumentParserExt):
        self.auto_bind_group = parser.add_mutually_exclusive_group()
        AUTO_BIND_BASE_HELP = (
            "Automatic binding or unbinding of an appkey to model of an element"
            "is {} in the app group when the publication or subscription is "
            "configured on the model. If it is not specified then the auto bind "
            "feature is turned {} by default (configuration option)."
        )
        onoff_text = "on" if app_cfg.appgroup.auto_bind_default else "off"
        AUTO_BIND_HELP = AUTO_BIND_BASE_HELP.format("enabled", onoff_text)
        NO_AUTO_BIND_HELP = AUTO_BIND_BASE_HELP.format("disabled", onoff_text)
        self.auto_bind_group.add_argument(
            "--auto-bind",
            dest="auto_bind",
            action="store_const",
            const=True,
            help=AUTO_BIND_HELP,
        )
        self.auto_bind_group.add_argument(
            "--no-auto-bind",
            dest="auto_bind",
            action="store_const",
            const=False,
            help=NO_AUTO_BIND_HELP,
        )

    def add_dcd_args(self, parser: ArgumentParserExt, support_remove_args=True):
        self.dcd_check_group = parser.add_mutually_exclusive_group()
        onoff_text = "on" if app_cfg.appgroup.dcd_check_default else "off"
        DCD_CHECK_DEFAULT = f"DCD check is turned {onoff_text} by default."
        self.dcd_check_group.add_argument(
            "--strict-dcd-check",
            dest="dcd_check",
            action="store_const",
            const=True,
            help=f"Strict DCD check raises an error when a model which shall be "
            f"configured (publication, subscription, binding) does not exist on "
            f"the specified element address based on the DCD. {DCD_CHECK_DEFAULT}",
        )
        self.dcd_check_group.add_argument(
            "--no-dcd-check",
            dest="dcd_check",
            action="store_const",
            const=False,
            help=f"No DCD check means that no error is raised during configuration "
            f"when the target model does not exist on the specified element "
            f"address based on the DCD. "
            f"No DCD check is useful when different kind of elements are "
            f"configured by the same command and DCD filtering is turned on "
            f"because it selects the proper subset of models for the specific "
            f"element addresses automatically. {DCD_CHECK_DEFAULT}",
        )
        parser.add_argument(
            "--skip-dcd-filter",
            action="store_true",
            help="The DCD filtering is used to filter out configuration operations "
            "(publication, subscription, binding) when the target model does not "
            "exist on the specified element address based on the DCD. "
            "The DCD filtering is useful when different kind of elements are "
            "configured by the same command and DCD check is turned off "
            "because it selects the proper subset of models for the specific "
            "element addresses automatically. If this options is present then "
            "DCD filtering is skipped.",
        )
        parser.add_argument(
            "--check-mdl-conf",
            action="store_true",
            help="If --check-mdl-conf is turned on then the add configuration "
            "operation (publication, subscription, unbinding) fails when the "
            "target model of the specified element address is already added "
            "to the app group. "
            "If --check-mdl-conf is turned on then the remove configuration "
            "operation (publication, subscription, unbinding) fails when the "
            "target model of the specified element address does not belong "
            "to the app group. "
            "If --check-mdl-conf is turned off then these operations are ignored. "
            "Note: --check-mdl-conf is stricter than the --strict-dcd-check "
            "because the former checks if the model exists and configured "
            "while the latter checks only whether the model exists or not.",
        )

    def add_group_basic_retry_args(self, parser: ArgumentParserExt):
        self.add_btmesh_basic_retry_args(
            parser,
            retry_max_default=app_cfg.conf.conf_retry_max_default,
            retry_interval_default=app_cfg.conf.conf_retry_interval_default,
            retry_interval_lpn_default=app_cfg.conf.conf_retry_interval_lpn_default,
            retry_max_help=(
                "Maximum number of additional Config messages which are sent "
                "until the corresponding status message is not received from "
                "the Configuration Server. "
                "(default: %(default)s)"
            ),
            retry_interval_help=(
                "Interval in seconds between Config messages when the "
                "corresponding status message is not received from the "
                "Configuration Server. "
                "(default: %(default)s)"
            ),
            retry_interval_lpn_help=(
                "Interval in seconds between Config messages when the "
                "corresponding status message is not received from the "
                "Configuration Server model of a Low Power Node. "
                "(default: %(default)s)"
            ),
        )

    def create_group_add_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "add"
        self.group_add_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="Create new app group.",
            description="Publication, subscription and bindings are configured "
            "on the specified models of element addresses. "
            "The configuration is performed based on the --group-addr and "
            "--appkey-idx parameters of the app group. The publication requires "
            "some additional parameters which can be specified as options.",
            exit_on_error_ext=False,
        )
        self.group_add_parser.set_defaults(group_subcmd=self.group_add_cmd)
        self.group_add_parser.add_argument(
            "--name",
            "-n",
            required=True,
            help="App group name. The app group name is unique identifier of "
            "an group.",
        )
        self.add_group_addr_args(self.group_add_parser)
        self.add_appkey_index_args(self.group_add_parser)
        self.add_pub_param_args(self.group_add_parser)
        self.add_pub_addr_mdl_args(self.group_add_parser, support_remove_args=False)
        self.add_sub_addr_mdl_args(self.group_add_parser, support_remove_args=False)
        self.add_bind_addr_mdl_args(self.group_add_parser, support_remove_args=False)
        self.add_mdl_profile_args(self.group_add_parser, support_remove_args=False)
        self.add_auto_bind_args(self.group_add_parser)
        self.add_dcd_args(self.group_add_parser, support_remove_args=False)
        self.add_group_basic_retry_args(self.group_add_parser)
        return SUBPARSER_NAME, self.group_add_parser

    def create_group_update_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "update"
        self.group_update_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="Update existing app group.",
            description="Publication, subscription and binding configuration "
            "can be added or removed from target models on specified element"
            "addresses. "
            "The configuration is performed based on the group address and "
            "application key belonging to the app group.",
            exit_on_error_ext=False,
        )
        self.group_update_parser.set_defaults(group_subcmd=self.group_update_cmd)
        self.group_update_parser.add_argument(
            "--name",
            "-n",
            metavar="<groupspec>",
            required=True,
            help=f"Specifies an existing app group which shall be updated. "
            f"The app group name is unique identifier of the group. "
            f"{app_ui.GROUPSPEC_HELP}",
        )
        self.add_pub_addr_mdl_args(self.group_update_parser, support_remove_args=True)
        self.add_sub_addr_mdl_args(self.group_update_parser, support_remove_args=True)
        self.add_bind_addr_mdl_args(self.group_update_parser, support_remove_args=True)
        self.add_mdl_profile_args(self.group_update_parser, support_remove_args=True)
        self.add_auto_bind_args(self.group_update_parser)
        self.add_dcd_args(self.group_update_parser, support_remove_args=True)
        self.add_group_basic_retry_args(self.group_update_parser)
        return SUBPARSER_NAME, self.group_update_parser

    def create_group_list_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "list"
        self.group_list_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="List app groups from application database.",
            description="List app groups from application database.",
            exit_on_error_ext=False,
        )
        self.group_list_parser.set_defaults(group_subcmd=self.group_list_cmd)
        self.add_column_args(
            self.group_list_parser,
            table_name="app group report",
            column_info_dict=app_ui.APP_GROUP_COLUMNS,
        )
        return SUBPARSER_NAME, self.group_list_parser

    def create_group_info_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "info"
        self.group_info_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="Provide information about selected app groups.",
            description="Provide information about selected app groups.",
            exit_on_error_ext=False,
        )
        self.group_info_parser.set_defaults(group_subcmd=self.group_info_cmd)
        self.add_app_group_pos_arg(
            self.group_info_parser,
            help=(
                "The %(metavar)s selects app groups which shall appear "
                "in %(prog)s report."
            ),
        )
        return SUBPARSER_NAME, self.group_info_parser

    def __call__(self, arg) -> bool:
        pargs = self.parser.parse_args(arg.split())
        self._current_parser = self.subparser_dict.get(
            pargs.group_subcmd_name, self.parser
        )
        pargs.group_subcmd(pargs)
        self._current_parser = self.parser
        return False

    def group_add_cmd(self, pargs):
        self.app_group_validate_elemspecs(
            pargs.pub_addrs, pargs.sub_addrs, pargs.bind_addrs
        )
        self.app_group_validate_mdlspecs(
            pargs.pub_mdls, pargs.sub_mdls, pargs.bind_mdls
        )
        # The retry_cmd_max and retry_cmd_interval are used only because the
        # other parameters are overwritten by the arguments of conf reset command
        retry_params_default = app_cfg.common.btmesh_retry_params_default
        retry_params = self.process_btmesh_retry_params(pargs, retry_params_default)
        # Model profile query should not fail because argparse makes sure that
        # a value from choices is selected and the choices are constructed
        # from configuration.
        mdl_profiles = [
            mp for mp in app_cfg.appgroup.mdl_profiles if mp.name in pargs.profile
        ]
        app_grctrl.add_app_group(
            name=pargs.name,
            group_addr=pargs.group_addr,
            appkey_index=pargs.appkey_idx,
            pub_ttl=pargs.pub_ttl,
            pub_credentials=pargs.pub_cred,
            pub_period_ms=pargs.pub_period,
            pub_retransmit_count=pargs.pub_tx_cnt,
            pub_retransmit_interval_ms=pargs.pub_tx_int,
        )
        auto_bind = pargs.auto_bind
        if auto_bind is None:
            auto_bind = app_cfg.appgroup.auto_bind_default
        dcd_check = pargs.dcd_check
        if dcd_check is None:
            dcd_check = app_cfg.appgroup.dcd_check_default
        self.app_group_add_addr_mdls(
            app_group_name=pargs.name,
            raw_pub_addrs=pargs.pub_addrs,
            raw_pub_mdls=pargs.pub_mdls,
            raw_sub_addrs=pargs.sub_addrs,
            raw_sub_mdls=pargs.sub_mdls,
            raw_bind_addrs=pargs.bind_addrs,
            raw_bind_mdls=pargs.bind_mdls,
            mdl_profiles=mdl_profiles,
            auto_bind=auto_bind,
            skip_dcd_filter=pargs.skip_dcd_filter,
            strict_dcd_check=dcd_check,
            retry_params=retry_params,
        )

    def group_update_cmd(self, pargs):
        self.app_group_validate_elemspecs(
            pargs.pub_addrs, pargs.sub_addrs, pargs.bind_addrs
        )
        self.app_group_validate_elemspecs(
            pargs.rm_pub_addrs, pargs.rm_sub_addrs, pargs.rm_bind_addrs
        )
        self.app_group_validate_mdlspecs(
            pargs.pub_mdls, pargs.sub_mdls, pargs.bind_mdls
        )
        self.app_group_validate_mdlspecs(
            pargs.rm_pub_mdls, pargs.rm_sub_mdls, pargs.rm_bind_mdls
        )
        # The retry_cmd_max and retry_cmd_interval are used only because the
        # other parameters are overwritten by the arguments of conf reset command
        retry_params_default = app_cfg.common.btmesh_retry_params_default
        retry_params = self.process_btmesh_retry_params(pargs, retry_params_default)
        # Model profile query should not fail because argparse makes sure that
        # a value from choices is selected and the choices are constructed
        # from configuration.
        mdl_profiles = [
            mp for mp in app_cfg.appgroup.mdl_profiles if mp.name in pargs.profile
        ]
        rm_mdl_profiles = [
            mp for mp in app_cfg.appgroup.mdl_profiles if mp.name in pargs.rm_profile
        ]
        auto_bind = pargs.auto_bind
        if auto_bind is None:
            auto_bind = app_cfg.appgroup.auto_bind_default
        dcd_check = pargs.dcd_check
        if dcd_check is None:
            dcd_check = app_cfg.appgroup.dcd_check_default
        # Process the remove operations first because the BT Mesh stack limits
        # the maximum app key bindings and subscription of models.
        # This way some extra space can be made free before additional app key
        # bindings and subscriptions.
        self.app_group_remove_addr_mdls(
            app_group_name=pargs.name,
            raw_pub_addrs=pargs.rm_pub_addrs,
            raw_pub_mdls=pargs.rm_pub_mdls,
            raw_sub_addrs=pargs.rm_sub_addrs,
            raw_sub_mdls=pargs.rm_sub_mdls,
            raw_bind_addrs=pargs.rm_bind_addrs,
            raw_bind_mdls=pargs.rm_bind_mdls,
            mdl_profiles=rm_mdl_profiles,
            auto_bind=auto_bind,
            skip_dcd_filter=pargs.skip_dcd_filter,
            strict_dcd_check=dcd_check,
            retry_params=retry_params,
        )
        self.app_group_add_addr_mdls(
            app_group_name=pargs.name,
            raw_pub_addrs=pargs.pub_addrs,
            raw_pub_mdls=pargs.pub_mdls,
            raw_sub_addrs=pargs.sub_addrs,
            raw_sub_mdls=pargs.sub_mdls,
            raw_bind_addrs=pargs.bind_addrs,
            raw_bind_mdls=pargs.bind_mdls,
            mdl_profiles=mdl_profiles,
            auto_bind=auto_bind,
            skip_dcd_filter=pargs.skip_dcd_filter,
            strict_dcd_check=dcd_check,
            retry_params=retry_params,
        )

    def group_list_cmd(self, pargs):
        columns = self.process_column_args(pargs, app_ui.APP_GROUP_COLUMNS)
        app_groups = app_db.get_app_group_list(order_property="name")
        app_ui.app_group_table_info(app_groups, columns)

    def group_info_cmd(self, pargs):
        all_app_groups = app_db.get_app_group_list(order_property="name")
        groupspec_list = pargs.groupspec
        selected_app_groups = self.parse_groupspecs(
            groupspec_list, all_app_groups, filter_duplicates=True
        )
        for app_group in selected_app_groups:
            app_ui.app_group_info(app_group)

    def app_group_validate_elemspecs(
        self, pub_elemspecs, sub_elemspecs, bind_elemspecs
    ):
        all_elemspecs = []
        all_elemspecs.extend(pub_elemspecs)
        all_elemspecs.extend(sub_elemspecs)
        all_elemspecs.extend(bind_elemspecs)
        node_list = app_db.btmesh_db.get_node_list(order_property="name")
        # The parse_elemspecs checks if the elemspec is valid and the
        # referenced element address exists at all
        self.parse_elemspecs(elemspecs=all_elemspecs, node_list=node_list)

    def app_group_validate_mdlspecs(self, pub_mdlspecs, sub_mdlspecs, bind_mdlspecs):
        all_mdlspecs = []
        all_mdlspecs.extend(pub_mdlspecs)
        all_mdlspecs.extend(sub_mdlspecs)
        all_mdlspecs.extend(bind_mdlspecs)
        # The parse_mdlspecs checks if the mdlspec is valid
        self.parse_mdlspecs(all_mdlspecs)

    def filter_addr_mdl_by_dcd(
        self,
        addr: int,
        mdls: Iterable[ModelID],
        strict: bool = False,
        retry_params: BtmeshRetryParams = None,
    ) -> Set[ModelID]:
        remote_node = app_db.get_remote_node_by_elem_addr(
            addr, retry_params=retry_params
        )
        elem_idx = remote_node.get_elem_index(addr)
        # If the DCD is not available then it is queried by remote node
        dcd = remote_node.dcd
        dcd_mdls_set = set(dcd.elements[elem_idx].models)
        mdls_set = set(mdls)
        final_mdls = mdls_set & dcd_mdls_set
        if strict and (final_mdls != mdls):
            miss_mdls = mdls_set - final_mdls
            miss_mdls_str = ", ".join(f"0x{mdl}" for mdl in miss_mdls)
            raise ValueError(
                f"Failed to create app group due to missing models "
                f"{miss_mdls_str} on 0x{addr:04X} element address."
            )
        return final_mdls

    def process_raw_addr_mdls(
        self,
        pub_addr_mdls_dict: Dict[int, Set[ModelID]],
        sub_addr_mdls_dict: Dict[int, Set[ModelID]],
        bind_addr_mdls_dict: Dict[int, Set[ModelID]],
        raw_pub_addrs: Iterable[str],
        raw_pub_mdls: Iterable[str],
        raw_sub_addrs: Iterable[str],
        raw_sub_mdls: Iterable[str],
        raw_bind_addrs: Iterable[str],
        raw_bind_mdls: Iterable[str],
        mdl_profiles: Iterable[BtmeshDfuAppMdlProfile],
        auto_bind: bool = True,
        skip_dcd_filter: bool = False,
        strict_dcd_check: bool = False,
        retry_params: BtmeshRetryParams = None,
    ):
        node_list = app_db.btmesh_db.get_node_list(order_property="name")
        bind_addrs = self.parse_elemspecs(elemspecs=raw_bind_addrs, node_list=node_list)
        pub_addrs = self.parse_elemspecs(elemspecs=raw_pub_addrs, node_list=node_list)
        sub_addrs = self.parse_elemspecs(elemspecs=raw_sub_addrs, node_list=node_list)
        if auto_bind:
            bind_addrs.extend(pub_addrs)
            bind_addrs.extend(sub_addrs)
        bind_addrs = set(bind_addrs)
        pub_addrs = set(pub_addrs)
        sub_addrs = set(sub_addrs)

        bind_mdls = set(self.parse_mdlspecs(raw_bind_mdls))
        pub_mdls = set(self.parse_mdlspecs(raw_pub_mdls))
        sub_mdls = set(self.parse_mdlspecs(raw_sub_mdls))
        if auto_bind:
            bind_mdls.update(pub_mdls)
            bind_mdls.update(sub_mdls)
        for mp in mdl_profiles:
            bind_mdls.update(mp.bind_mdls)
            pub_mdls.update(mp.pub_mdls)
            sub_mdls.update(mp.sub_mdls)

        for addr in pub_addrs:
            if skip_dcd_filter:
                pub_addr_mdls_dict[addr] = pub_mdls
            else:
                pub_addr_mdls_dict[addr] = self.filter_addr_mdl_by_dcd(
                    addr, pub_mdls, strict=strict_dcd_check, retry_params=retry_params
                )
        for addr in sub_addrs:
            if skip_dcd_filter:
                sub_addr_mdls_dict[addr] = sub_mdls
            else:
                sub_addr_mdls_dict[addr] = self.filter_addr_mdl_by_dcd(
                    addr, sub_mdls, strict=strict_dcd_check, retry_params=retry_params
                )
        # It is essential to process bind model filtering after publication and
        # subscription models because the auto bind feature may add additional
        # bind models which needs to be filtered as well.
        for addr in bind_addrs:
            if skip_dcd_filter:
                filtered_bind_addr = bind_mdls
            else:
                filtered_bind_addr = self.filter_addr_mdl_by_dcd(
                    addr, bind_mdls, strict=strict_dcd_check, retry_params=retry_params
                )
            if addr in bind_addr_mdls_dict:
                bind_addr_mdls_dict[addr].update(filtered_bind_addr)
            else:
                bind_addr_mdls_dict[addr] = set(filtered_bind_addr)

    def app_group_add_addr_mdls(
        self,
        app_group_name: str,
        raw_pub_addrs: Iterable[str],
        raw_pub_mdls: Iterable[str],
        raw_sub_addrs: Iterable[str],
        raw_sub_mdls: Iterable[str],
        raw_bind_addrs: Iterable[str],
        raw_bind_mdls: Iterable[str],
        mdl_profiles: Iterable[BtmeshDfuAppMdlProfile],
        auto_bind: bool = True,
        skip_dcd_filter: bool = False,
        strict_dcd_check: bool = False,
        retry_params: BtmeshRetryParams = None,
    ):
        bind_addr_mdls_dict: Dict[int, Set[ModelID]] = {}
        pub_addr_mdls_dict: Dict[int, Set[ModelID]] = {}
        sub_addr_mdls_dict: Dict[int, Set[ModelID]] = {}
        self.process_raw_addr_mdls(
            pub_addr_mdls_dict=pub_addr_mdls_dict,
            sub_addr_mdls_dict=sub_addr_mdls_dict,
            bind_addr_mdls_dict=bind_addr_mdls_dict,
            raw_pub_addrs=raw_pub_addrs,
            raw_pub_mdls=raw_pub_mdls,
            raw_sub_addrs=raw_sub_addrs,
            raw_sub_mdls=raw_sub_mdls,
            raw_bind_addrs=raw_bind_addrs,
            raw_bind_mdls=raw_bind_mdls,
            mdl_profiles=mdl_profiles,
            auto_bind=auto_bind,
            skip_dcd_filter=skip_dcd_filter,
            strict_dcd_check=strict_dcd_check,
            retry_params=retry_params,
        )
        for addr, mdls in bind_addr_mdls_dict.items():
            for mdl in mdls:
                try:
                    app_grctrl.add_bind_mdl(
                        app_group_name=app_group_name,
                        addr=addr,
                        mdl=mdl,
                        retry_params=retry_params,
                    )
                    app_ui.info(
                        f"App group {app_group_name} adds appkey binding to "
                        f"{mdl.pretty_name()} model on 0x{addr:04X} element address."
                    )
                except Exception as e:
                    app_ui.error(
                        f"App group {app_group_name} failed to bind appkey to "
                        f"{mdl.pretty_name()} model on 0x{addr:04X} element address. "
                        f"{str(e)}"
                    )
        for addr, mdls in pub_addr_mdls_dict.items():
            for mdl in mdls:
                try:
                    app_grctrl.add_pub_mdl(
                        app_group_name=app_group_name,
                        addr=addr,
                        mdl=mdl,
                        auto_bind=auto_bind,
                        retry_params=retry_params,
                    )
                    app_ui.info(
                        f"App group {app_group_name} adds publication to "
                        f"{mdl.pretty_name()} model on 0x{addr:04X} element address."
                    )
                except Exception as e:
                    app_ui.error(
                        f"App group {app_group_name} failed to add publication "
                        f"to {mdl.pretty_name()} model on 0x{addr:04X} element "
                        f"address. {str(e)}"
                    )
        for addr, mdls in sub_addr_mdls_dict.items():
            for mdl in mdls:
                try:
                    app_grctrl.add_sub_mdl(
                        app_group_name=app_group_name,
                        addr=addr,
                        mdl=mdl,
                        auto_bind=auto_bind,
                        retry_params=retry_params,
                    )
                    app_ui.info(
                        f"App group {app_group_name} adds subscription to "
                        f"{mdl.pretty_name()} model on 0x{addr:04X} element address."
                    )
                except Exception as e:
                    app_ui.error(
                        f"App group {app_group_name} failed to add subscription "
                        f"to {mdl.pretty_name()} model on 0x{addr:04X} element "
                        f"address. {str(e)}"
                    )

    def app_group_remove_addr_mdls(
        self,
        app_group_name: str,
        raw_pub_addrs: Iterable[str],
        raw_pub_mdls: Iterable[str],
        raw_sub_addrs: Iterable[str],
        raw_sub_mdls: Iterable[str],
        raw_bind_addrs: Iterable[str],
        raw_bind_mdls: Iterable[str],
        mdl_profiles: Iterable[BtmeshDfuAppMdlProfile],
        auto_bind: bool = True,
        skip_dcd_filter: bool = False,
        strict_dcd_check: bool = False,
        retry_params: BtmeshRetryParams = None,
    ):
        bind_addr_mdls_dict: Dict[int, Set[ModelID]] = {}
        pub_addr_mdls_dict: Dict[int, Set[ModelID]] = {}
        sub_addr_mdls_dict: Dict[int, Set[ModelID]] = {}
        self.process_raw_addr_mdls(
            pub_addr_mdls_dict=pub_addr_mdls_dict,
            sub_addr_mdls_dict=sub_addr_mdls_dict,
            bind_addr_mdls_dict=bind_addr_mdls_dict,
            raw_pub_addrs=raw_pub_addrs,
            raw_pub_mdls=raw_pub_mdls,
            raw_sub_addrs=raw_sub_addrs,
            raw_sub_mdls=raw_sub_mdls,
            raw_bind_addrs=raw_bind_addrs,
            raw_bind_mdls=raw_bind_mdls,
            mdl_profiles=mdl_profiles,
            auto_bind=auto_bind,
            skip_dcd_filter=skip_dcd_filter,
            strict_dcd_check=strict_dcd_check,
            retry_params=retry_params,
        )
        for addr, mdls in bind_addr_mdls_dict.items():
            for mdl in mdls:
                try:
                    app_grctrl.remove_bind_mdl(
                        app_group_name=app_group_name,
                        addr=addr,
                        mdl=mdl,
                        retry_params=retry_params,
                    )
                    app_ui.info(
                        f"App group {app_group_name} removes appkey binding to "
                        f"{mdl.pretty_name()} model on 0x{addr:04X} element address."
                    )
                except Exception as e:
                    app_ui.error(
                        f"App group {app_group_name} failed to unbind appkey to "
                        f"{mdl.pretty_name()} model on 0x{addr:04X} element address. "
                        f"{str(e)}"
                    )
        for addr, mdls in pub_addr_mdls_dict.items():
            for mdl in mdls:
                try:
                    app_grctrl.remove_pub_mdl(
                        app_group_name=app_group_name,
                        addr=addr,
                        mdl=mdl,
                        auto_unbind=auto_bind,
                        retry_params=retry_params,
                    )
                    app_ui.info(
                        f"App group {app_group_name} removes publication to "
                        f"{mdl.pretty_name()} model on 0x{addr:04X} element address."
                    )
                except Exception as e:
                    app_ui.error(
                        f"App group {app_group_name} failed to remove publication "
                        f"to {mdl.pretty_name()} model on 0x{addr:04X} element "
                        f"address. {str(e)}"
                    )
        for addr, mdls in sub_addr_mdls_dict.items():
            for mdl in mdls:
                try:
                    app_grctrl.remove_sub_mdl(
                        app_group_name=app_group_name,
                        addr=addr,
                        mdl=mdl,
                        auto_unbind=auto_bind,
                        retry_params=retry_params,
                    )
                    app_ui.info(
                        f"App group {app_group_name} removes subscription to "
                        f"{mdl.pretty_name()} model on 0x{addr:04X} element address."
                    )
                except Exception as e:
                    app_ui.error(
                        f"App group {app_group_name} failed to remove subscription "
                        f"to {mdl.pretty_name()} model on 0x{addr:04X} element "
                        f"address. {str(e)}"
                    )


group_cmd = BtmeshGroupCmd()
