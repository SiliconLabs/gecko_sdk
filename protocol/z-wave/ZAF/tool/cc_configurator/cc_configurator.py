import os
import glob
import argparse
import yaml
import sys
import logging
from cc_base import cc_base, cc_data
from ccs import cc_multilevel_sensor
from typing import Any, List
from os import walk


def handle_templates(configuration: Any) -> List[cc_data]:
    """Handle all the templates

    Currently these templates are only command classes but this could be
    extended for other use cases

    Args:
        output_dir (str): The output directory for the auto generate files
        configuration (Any): The configuration (cc_config) file

    Returns:
        List[cc_data]: A list of Command Class data
    """
    command_classes = [
        cc_base('zw_cc_color_switch', [
            'cc_color_switch_config.c.jinja'], 'colors'),
        cc_base('zw_cc_binaryswitch', [
            'cc_binary_switch_config.c.jinja'], 'binary_switches'),
        cc_base('zw_cc_multilevel_switch_support', [
            'cc_multilevel_switch_support_config.c.jinja'], 'switches'),
        cc_multilevel_sensor(),
        cc_base('zw_cc_configuration', [
            'cc_configuration_config.c.jinja'], 'configurations'),
        cc_base('zw_cc_door_lock', [
            'cc_door_lock_config.h.jinja'], 'configuration'),
        cc_base('zw_cc_notification', [
            'cc_notification_config.c.jinja'], 'notifications'),
        cc_base('zw_cc_zwaveplusinfo', [
            'cc_zwaveplusinfo_config.c.jinja'], 'endpoints'),
        cc_base('zw_cc_agi', [
            'cc_agi_config.c.jinja'], 'endpoints'),
    ]
    current_dir = os.path.dirname(os.path.abspath(__file__))
    templates_dir = os.path.join(current_dir, "templates")

    ret = []
    for command_class in command_classes:
        if command_class.component in configuration:
            ret.extend(command_class.render(
                configuration, templates_dir))

    return ret


def generate(input_dir: str) -> List[cc_data]:
    """Finds all cc_config files and for each handle the templates

    Args:
        input_dir (str): _description_

    Returns:
        List[cc_data]: A list of Command Class data
    """
    ret = []
    for file in glob.glob(os.path.join(input_dir, "*.cc_config")):
        with open(file) as fd:
            configuration = yaml.load(fd, Loader=yaml.SafeLoader)

        ret += handle_templates(configuration)

    return ret


def take_action(files: List[cc_data], action: str, output_dir: str) -> int:
    """Take a given action

    Args:
        files (List[cc_data]): A list of Command Class data
        action (str): The action
        output_dir (str): Output directory

    Returns:
        int: Code used as exit code
    """
    ret = 0
    for file in files:
        file_path = os.path.join(output_dir, file.name)

        # Generate the cc config files
        if action == "generate":
            with open(file_path, 'w') as fd:
                fd.write(file.data)
        # Verify that files that are written match the expected content
        elif action == 'verify' and os.path.isfile(file_path):
            with open(file_path, 'r') as fd:
                written_data = fd.read()
                if written_data != file.data:
                    logging.error("{} does not match the expected content".format(
                        os.path.basename(file_path)
                    ))
                    ret = -1

    # Read files from disk and compare if they are needed
    # Read files from disk and compare if all generated files are present
    if action == 'verify':
        written_files = []
        for (_, __, filenames) in walk(output_dir):
            written_files.extend(filenames)

        set_written = set(written_files)
        set_generated = set([f.name for f in files])
        only_written = set_written.difference(set_generated)
        only_generated = set_generated.difference(set_written)

        for written in only_written:
            logging.error("{} is only written in disk but not generated".format(
                written
            ))
            ret = -1
        for generated in only_generated:
            logging.error("{} is not written in disk but is generated".format(
                generated
            ))
            ret = -1

    return ret


def main() -> None:
    parser = argparse.ArgumentParser(
        description='Z-Wave Command Class configuration to C converter.')
    parser.add_argument('-i', required=True,
                        help='Input directory containing .zw_cc_conf files')
    parser.add_argument(
        '-o', required=True, help='Output directory to populate with serialized content.')

    subparsers = parser.add_subparsers(
        help='Action to be taken', dest="action")
    subparsers.add_parser(
        'generate', help='Generate the files from the templates')
    subparsers.add_parser(
        'verify', help='Verify that the files generate match the templates')

    args = parser.parse_args()

    files = generate(args.i)

    ret = take_action(files, args.action, args.o)

    sys.exit(ret)


if __name__ == "__main__":
    main()
