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

import cmd
import logging
import sys
from typing import Optional

import btmesh.util
from bgapi.bglib import CommandFailedError
from bgapix.bglibx import (BGLibExt, BGLibExtSyncSignalException,
                           BGLibExtWaitEventError)
from bgapix.slstatus import SlStatus
from btmesh.db import ModelID
from btmesh.mdl import NamedModelID
from btmesh.util import BtmeshMulticastRetryParams, BtmeshRetryParams

from .btmesh import app_btmesh
from .cfg import app_cfg
from .cmd.conf import conf_cmd
from .cmd.dfu import dfu_cmd
from .cmd.dist import dist_cmd
from .cmd.group import group_cmd
from .cmd.node import node_cmd
from .cmd.prov import prov_cmd
from .cmd.proxy import proxy_cmd
from .cmd.reset import reset_cmd
from .cmd.scan import scan_cmd
from .db import BtmeshDfuAppDbLoadError, app_db
from .grpctrl import app_grctrl
from .ui import app_ui
from .util.argparsex import (ArgumentErrorExt, ArgumentHelpException,
                             ArgumentParserExt)

logger = logging.getLogger(__name__)

APP_COMMANDS = [
    reset_cmd,
    scan_cmd,
    prov_cmd,
    proxy_cmd,
    node_cmd,
    group_cmd,
    conf_cmd,
    dfu_cmd,
    dist_cmd,
]


class BtmeshDfuAppResetException(Exception):
    def __init__(self, boot_event, *args: object) -> None:
        super().__init__(*args)
        self.boot_event = boot_event


class BtmeshDfuAppExec(cmd.Cmd):

    APP_NAME = "BT Mesh Host DFU"
    intro = """
  ____ _______   __  __           _       _    _           _     _____   __
 |  _ \__   __| |  \/  |         | |     | |  | |         | |   |  __ \ / _|
 | |_) | | |    | \  / | ___  ___| |__   | |__| | ___  ___| |_  | |  | | |_ _   _
 |  _ <  | |    | |\/| |/ _ \/ __| '_ \  |  __  |/ _ \/ __| __| | |  | |  _| | | |
 | |_) | | |    | |  | |  __/\__ \ | | | | |  | | (_) \__ \ |_  | |__| | | | |_| |
 |____/  |_|    |_|  |_|\___||___/_| |_| |_|  |_|\___/|___/\__| |_____/|_|  \__,_|
 """
    prompt = ">>>"

    def __init__(self, completekey="tab", stdin=None, stdout=None):
        super().__init__(completekey, stdin, stdout)
        self.cmd_parser: Optional[ArgumentParserExt] = None
        self._subparsers = None
        self._interactive = None
        self._lib: Optional[BGLibExt] = None
        self.async_signal_proc_on = True
        self.cmd_active = False
        self.reset_cmd_active = False

    def handle_async_signal(self, event):
        if self.async_signal_proc_on:
            sys.exit(-1)

    def handle_sync_signal(self, event):
        raise BGLibExtSyncSignalException(event.signum)

    @property
    def subparsers(self):
        return self._subparsers

    @property
    def interactive(self):
        return self._interactive

    @interactive.setter
    def interactive(self, value):
        self._interactive = value

    @property
    def lib(self):
        return self._lib

    @lib.setter
    def lib(self, value):
        self._lib = value

    def build_cmd_parser(self) -> ArgumentParserExt:
        self.cmd_parser = ArgumentParserExt(exit_on_error_ext=False)
        self._subparsers = self.cmd_parser.add_subparsers(dest="command")
        for cmd in APP_COMMANDS:
            cmd.create_parser(self._subparsers)
        return self.cmd_parser

    def open(self, system_reset=False, factory_reset=False):
        if factory_reset:
            # Avoid loading the database from file in order to make the app robust.
            # Note: If database loading fails then it should be possible to drop
            # the problematic database before command execution.
            app_db.clear()
        else:
            try:
                app_db.load()
            except BtmeshDfuAppDbLoadError as e:
                app_ui.error(str(e))
        app_btmesh.setup(lib=self.lib, db=app_db.btmesh_db)
        app_btmesh.core.open()
        app_btmesh.core.subscribe(
            event_name="bglibx_evt_signal_async_received",
            handler=self.handle_async_signal,
        )
        app_btmesh.core.subscribe(
            event_name="bglibx_evt_signal_sync_received",
            handler=self.handle_sync_signal,
        )
        app_btmesh.core.subscribe(
            event_name="bt_evt_system_boot", handler=self.handle_system_boot
        )
        if factory_reset:
            app_ui.info("Factory reset...")
            app_btmesh.core.factory_reset(app_cfg.reset.factory_reset_delay_s)
            app_db.save()
        elif system_reset:
            # Optional system reset on the NCP device in order to move it into
            # known state because all bt and btmesh stack state machines are
            # reset to default state.
            app_btmesh.core.system_reset()
        app_grctrl.setup()
        app_btmesh.proxy.verify_active_connections()

    def handle_system_boot(self, boot_event):
        if self.cmd_active and not self.reset_cmd_active:
            raise BtmeshDfuAppResetException(boot_event)
        else:
            self.execute_boot_actions(boot_event)

    def execute_boot_actions(self, boot_event):
        app_btmesh.core.on_system_boot(boot_event)
        self.prov_init()

    def prov_init(self):
        # Initialize the node as provisioner to make sure the NCP device is
        # able to receive BT and BT Mesh stack commands.
        # The prov_init method does not raise any error when the BT Mesh stack
        # is already initialized.
        network_count = app_btmesh.prov.init()
        # Initialize BT Mesh Stack classes
        self.dfu_init()
        self.conf_init()
        # If there are no networks on the NCP node then one is created by default.
        # This scripts support one netkey and appkey only because it demonstrates
        # the firmware update and not the provisioner and configurator.
        if network_count == 0:
            if app_cfg.network.random_netkey:
                netkey = bytes()
            else:
                netkey = app_cfg.network.netkey
            if app_cfg.network.random_appkey:
                appkeys = [bytes()] * app_cfg.network.appkey_cnt
            else:
                appkeys = list(app_cfg.network.appkeys)
            app_btmesh.prov.create_network(
                netkey, appkeys, app_cfg.network._prov_node_name
            )
            # The Default TTL state is stored in NVM so local configuration
            # shall be performed once when the network is created.
            self.local_conf_default_ttl()
            # The Network Transmit state is stored in NVM so local configuration
            # shall be performed once when the network is created.
            self.local_conf_nettx()
            # The SAR Transmitter and Receiver states are stored in NVM so local
            # configuration shall be performed once when the network is created.
            self.local_conf_sar()
        # Configure local BT Mesh models
        self.local_conf_dfu()
        self.local_conf_ae()

    def dfu_init(self):
        dfu_clt_retry_params = BtmeshMulticastRetryParams(
            retry_max=app_cfg.dfu_clt.dfu_retry_max_default,
            retry_interval=app_cfg.dfu_clt.dfu_retry_interval_default,
            retry_cmd_max=app_cfg.common.retry_cmd_max_default,
            retry_cmd_interval=app_cfg.common.retry_cmd_interval_default,
            retry_interval_lpn=app_cfg.dfu_clt.dfu_retry_interval_lpn_default,
            multicast_threshold=app_cfg.dfu_clt.dfu_retry_multicast_threshold_default,
            auto_unicast=app_cfg.common.retry_auto_unicast_default,
        )
        dist_clt_retry_params = BtmeshMulticastRetryParams(
            retry_max=app_cfg.dist_clt.dist_retry_max_default,
            retry_interval=app_cfg.dist_clt.dist_retry_interval_default,
            retry_cmd_max=app_cfg.common.retry_cmd_max_default,
            retry_cmd_interval=app_cfg.common.retry_cmd_interval_default,
            retry_interval_lpn=app_cfg.dist_clt.dist_retry_interval_lpn_default,
            multicast_threshold=app_cfg.dist_clt.dist_retry_multicast_threshold_default,
            auto_unicast=app_cfg.common.retry_auto_unicast_default,
        )
        app_btmesh.mbt_clt.init(
            elem_index=app_cfg.mbt_clt.elem_index,
            max_servers=app_cfg.mbt_clt.max_servers,
            max_blocks=app_cfg.mbt_clt.max_blocks,
            max_chunks_per_block=app_cfg.mbt_clt.max_chunks_per_block,
            retry_params_default=dfu_clt_retry_params.to_base(),
        )
        app_btmesh.dfu_clt.init(
            elem_index=app_cfg.dfu_clt.elem_index,
            max_target_nodes=app_cfg.dfu_clt.max_target_nodes,
            retry_params_default=dfu_clt_retry_params,
        )
        app_btmesh.dist_clt.init(
            elem_index=app_cfg.dist_clt.elem_index,
            retry_params_default=dist_clt_retry_params,
        )

    def conf_init(self):
        app_btmesh.conf.sar_conf_svr_init()
        app_btmesh.conf.sar_conf_clt_init()
        app_btmesh.conf.silabs_conf_svr_init()
        app_btmesh.conf.silabs_conf_clt_init()
        conf_retry_params = BtmeshRetryParams(
            retry_max=app_cfg.conf.conf_retry_max_default,
            retry_interval=app_cfg.conf.conf_retry_interval_default,
            retry_interval_lpn=app_cfg.conf.conf_retry_interval_lpn_default,
            retry_cmd_max=app_cfg.common.retry_cmd_max_default,
            retry_cmd_interval=app_cfg.common.retry_cmd_interval_default,
        )
        silabs_conf_retry_params = BtmeshMulticastRetryParams(
            retry_max=app_cfg.conf.silabs_retry_max_default,
            retry_interval=app_cfg.conf.silabs_retry_interval_default,
            retry_interval_lpn=app_cfg.conf.silabs_retry_interval_lpn_default,
            retry_cmd_max=app_cfg.common.retry_cmd_max_default,
            retry_cmd_interval=app_cfg.common.retry_cmd_interval_default,
            multicast_threshold=app_cfg.conf.silabs_retry_multicast_threshold_default,
            auto_unicast=app_cfg.common.retry_auto_unicast_default,
        )
        reset_node_retry_params = BtmeshRetryParams(
            retry_max=app_cfg.conf.reset_node_retry_max_default,
            retry_interval=app_cfg.conf.reset_node_retry_interval_default,
            retry_interval_lpn=app_cfg.conf.reset_node_retry_interval_lpn_default,
            retry_cmd_max=app_cfg.common.retry_cmd_max_default,
            retry_cmd_interval=app_cfg.common.retry_cmd_interval_default,
        )
        app_btmesh.conf.set_conf_retry_params_default(conf_retry_params)
        app_btmesh.conf.set_silabs_retry_params_default(silabs_conf_retry_params)
        app_btmesh.conf.set_reset_node_retry_params_default(reset_node_retry_params)

    def local_conf_dfu(self):
        # Set appkey bindings to BLOB Transfer Client model
        elem_index = app_cfg.mbt_clt.elem_index
        mdl = ModelID(NamedModelID.BLOB_TRANSFER_CLIENT)
        appkey_idx_list = app_btmesh.conf.list_local_bindings(elem_index, mdl)
        if not appkey_idx_list:
            for appkey_index in range(app_cfg.network.appkey_cnt):
                app_btmesh.conf.bind_local_mdl(elem_index, mdl, appkey_index)
        # Set appkey bindings to Firmware Update Client model
        elem_index = app_cfg.dfu_clt.elem_index
        mdl = ModelID(NamedModelID.FIRMWARE_UPDATE_CLIENT)
        appkey_idx_list = app_btmesh.conf.list_local_bindings(elem_index, mdl)
        if not appkey_idx_list:
            for appkey_index in range(app_cfg.network.appkey_cnt):
                app_btmesh.conf.bind_local_mdl(elem_index, mdl, appkey_index)
        # Set appkey bindings to Firmware Distribution Client model
        elem_index = app_cfg.dist_clt.elem_index
        mdl = ModelID(NamedModelID.FIRMWARE_DISTRIBUTION_CLIENT)
        appkey_idx_list = app_btmesh.conf.list_local_bindings(elem_index, mdl)
        if not appkey_idx_list:
            for appkey_index in range(app_cfg.network.appkey_cnt):
                app_btmesh.conf.bind_local_mdl(elem_index, mdl, appkey_index)

    def local_conf_ae(self):
        if app_btmesh.conf.silabs_conf_support:
            elem_index = btmesh.util.PRIM_ELEM_INDEX
            mdls = [
                ModelID(NamedModelID.SILABS_CONFIGURATION_SERVER),
                ModelID(NamedModelID.SILABS_CONFIGURATION_CLIENT),
            ]
            for mdl in mdls:
                appkey_idx_list = app_btmesh.conf.list_local_bindings(elem_index, mdl)
                if not appkey_idx_list:
                    for appkey_index in range(app_cfg.network.appkey_cnt):
                        app_btmesh.conf.bind_local_mdl(elem_index, mdl, appkey_index)

    def local_conf_default_ttl(self):
        prov_node = app_db.btmesh_db.get_provisioner()
        if app_cfg.conf.auto_conf_default_ttl:
            default_ttl_status = app_btmesh.conf.set_default_ttl(
                prov_node, app_cfg.conf.default_ttl_default
            )
        else:
            default_ttl_status = app_btmesh.conf.get_default_ttl(prov_node)
        logger.info(f"Local Default TTL is {default_ttl_status.ttl}.")

    def local_conf_nettx(self):
        prov_node = app_db.btmesh_db.get_provisioner()
        if app_cfg.conf.auto_conf_network_tx:
            nettx_status = app_btmesh.conf.set_network_transmit(
                prov_node,
                app_cfg.conf.network_tx_count_default,
                app_cfg.conf.network_tx_interval_ms_default,
            )
        else:
            nettx_status = app_btmesh.conf.get_network_transmit(prov_node)
        logger.info(f"Local Network Transmit Count is {nettx_status.transmit_count}.")
        logger.info(
            f"Local Network Transmit Interval Step is "
            f"{nettx_status.transmit_interval_ms} ms."
        )

    def local_conf_sar(self):
        if hasattr(self.lib.btmesh, "sar_config_server"):
            prov_node = app_db.btmesh_db.get_provisioner()
            # The SAR transmitter and receiver configuration getter and setter
            # functions don't require initialization call and it is not mandatory
            # to have SAR Configuration Server in the Device Composition Data.
            # These are necessary only to handle SAR Config messages.
            if app_cfg.conf.auto_conf_sar or app_cfg.conf.auto_conf_sar_local:
                sar_tx_status = app_btmesh.conf.set_sar_transmitter(
                    prov_node,
                    app_cfg.conf.sar_tx_segment_interval_step_default,
                    app_cfg.conf.sar_tx_unicast_retrans_count_default,
                    app_cfg.conf.sar_tx_unicast_retrans_wo_progress_count_default,
                    app_cfg.conf.sar_tx_unicast_retrans_interval_step_default,
                    app_cfg.conf.sar_tx_unicast_retrans_interval_increment_default,
                    app_cfg.conf.sar_tx_multicast_retrans_count_default,
                    app_cfg.conf.sar_tx_multicast_retrans_interval_step_default,
                )
            else:
                sar_tx_status = app_btmesh.conf.get_sar_transmitter(prov_node)
            logger.info(
                f"Local SAR TX Segment Interval Step is "
                f"{sar_tx_status.segment_interval_step} ms."
            )
            logger.info(
                f"Local SAR TX Unicast Retransmissions Count is "
                f"{sar_tx_status.unicast_retrans_count} retransmissions."
            )
            logger.info(
                f"Local SAR TX Unicast Retransmissions Without Progress Count is "
                f"{sar_tx_status.unicast_retrans_wo_progress_count} retransmissions."
            )
            logger.info(
                f"Local SAR TX Unicast Retransmissions Interval Step is "
                f"{sar_tx_status.unicast_retrans_interval_step} ms."
            )
            logger.info(
                f"Local SAR TX Unicast Retransmissions Interval Increment is "
                f"{sar_tx_status.unicast_retrans_interval_increment} ms."
            )
            logger.info(
                f"Local SAR TX Multicast Retransmissions Count is "
                f"{sar_tx_status.multicast_retrans_count} retransmissions."
            )
            logger.info(
                f"Local SAR TX Multicast Retransmissions Interval Step is "
                f"{sar_tx_status.multicast_retrans_interval_step} ms."
            )
            if app_cfg.conf.auto_conf_sar or app_cfg.conf.auto_conf_sar_local:
                sar_rx_status = app_btmesh.conf.set_sar_receiver(
                    prov_node,
                    app_cfg.conf.sar_rx_segments_threshold_default,
                    app_cfg.conf.sar_rx_ack_delay_increment_default,
                    app_cfg.conf.sar_rx_discard_timeout_default,
                    app_cfg.conf.sar_rx_segment_interval_step_default,
                    app_cfg.conf.sar_rx_ack_retrans_count_default,
                )
            else:
                sar_rx_status = app_btmesh.conf.get_sar_receiver(prov_node)
            logger.info(
                f"Local SAR RX Segments Threshold is "
                f"{sar_rx_status.segments_threshold} segments."
            )
            logger.info(
                f"Local SAR RX Acknowledgment Delay Increment is "
                f"{sar_rx_status.ack_delay_increment} "
                f"({sar_rx_status.ack_delay_increment + 1.5} "
                f"segment transmission interval step)."
            )
            logger.info(
                f"Local SAR RX Discard Timeout is {sar_rx_status.discard_timeout} ms."
            )
            logger.info(
                f"Local SAR RX Receiver Segment Interval Step is "
                f"{sar_rx_status.segment_interval_step} ms."
            )
            logger.info(
                f"Local SAR RX Acknowledgment Retransmissions Count is "
                f"{sar_rx_status.ack_retrans_count} retransmissions."
            )

    def close(self):
        app_btmesh.core.close()

    def onecmd(self, line):
        self.async_signal_proc_on = False
        app_ui.log_user_input(line)
        exit_request = not self.interactive
        try:
            # Process the events which were accumulated before the command is
            # started to avoid interference with the new command execution.
            app_btmesh.core.wait(timeout=0.0, max_time=None)
            self.cmd_active = True
            exit_request = super().onecmd(line)
            app_db.save()
        except ArgumentHelpException as e:
            app_ui.info(e.message)
        except ArgumentErrorExt as e:
            app_ui.parser_error(e.parser, e.message)
        except CommandFailedError as e:
            status_name = SlStatus.get_name(e.errorcode)
            app_ui.error(str(e) + f" ({status_name})")
        except BGLibExtWaitEventError as e:
            app_ui.error("Command is aborted due to timeout.")
        except BGLibExtSyncSignalException as e:
            app_ui.info("Command is aborted by user.")
        except BtmeshDfuAppResetException as e:
            app_ui.info("Unexpected system reset.")
            self.execute_boot_actions(e.boot_event)
        except Exception as e:
            app_ui.error(str(e))
        finally:
            self.async_signal_proc_on = True
            self.cmd_active = False
            self.reset_cmd_active = False
        return exit_request

    def do_reset(self, arg):
        self.reset_cmd_active = True
        exit_request = reset_cmd(arg)
        return exit_request

    def help_reset(self):
        reset_cmd.help()

    def do_scan(self, arg):
        return scan_cmd(arg)

    def help_scan(self):
        scan_cmd.help()

    def do_prov(self, arg):
        return prov_cmd(arg)

    def help_prov(self):
        prov_cmd.help()

    def do_proxy(self, arg):
        return proxy_cmd(arg)

    def help_proxy(self):
        proxy_cmd.help()

    def do_node(self, arg):
        return node_cmd(arg)

    def help_node(self):
        node_cmd.help()

    def do_group(self, arg):
        return group_cmd(arg)

    def help_group(self):
        group_cmd.help()

    def do_conf(self, arg):
        return conf_cmd(arg)

    def help_conf(self):
        conf_cmd.help()

    def do_dfu(self, arg):
        return dfu_cmd(arg)

    def help_dfu(self):
        dfu_cmd.help()

    def do_dist(self, arg):
        return dist_cmd(arg)

    def help_dist(self):
        dist_cmd.help()

    def do_exit(self, arg):
        return True

    def help_exit(self):
        app_ui.info("The exit command terminates the application.")


app_exec = BtmeshDfuAppExec()
