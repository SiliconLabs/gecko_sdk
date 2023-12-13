"""
ESL Access Point logger class.
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
import logging
import threading
try:
    import colorlog
except ImportError:
    pass
from functools import partial, partialmethod

LEVELS = {'NOTSET': logging.NOTSET,
          'TRACE': logging.DEBUG - 5,
          'DEBUG': logging.DEBUG,
          'INFO' : logging.INFO,
          'WARNING' : logging.WARNING,
          'ERROR': logging.ERROR,
          'CRITICAL': logging.CRITICAL}

COLORS = {'NOTSET': 'light_purple',
          'TRACE': 'light_blue',
          'DEBUG' : 'light_black',
          'INFO' : 'light_green',
          'WARNING' : 'light_yellow',
          'ERROR': 'light_red',
          'CRITICAL': 'bold_red'}

stdout = False
level = logging.INFO
lock = threading.Lock()

_logger_list = {}

def log(*args, _half_indent_log :bool=False, **kwargs):
    ''' Print with 1 tab + 1 whitespace indentation '''
    args = [arg.replace('\n', '\n\t ') if isinstance(arg, str) else arg for arg in args]
    with lock:
        print('\t' if not _half_indent_log else 3*' ', *args, file=sys.stdout if stdout else sys.stderr, **kwargs)

class StreamHandler(logging.StreamHandler):
    def __init__(self):
        super().__init__(stream=sys.stdout if stdout else sys.stderr)
        self.fmt = '\r%(asctime)s.%(msecs)03d: %(name)-3s - %(levelname)-8s - %(message)s'
        self.fmt_date = '%d/%b %H:%M:%S'
        if 'colorlog' in sys.modules and os.isatty(2):
            cformat = '%(log_color)s' + self.fmt
            self.formatter = colorlog.ColoredFormatter(cformat, self.fmt_date, log_colors=COLORS)
        else:
            self.formatter = logging.Formatter(self.fmt, self.fmt_date)
        self.setFormatter(self.formatter)
        self.setLevel(logging.NOTSET)

def getLogger(name="AP "):
    logger = logging.Logger(name)
    c_handler = StreamHandler()
    logger.propagate = True
    logger.addHandler(c_handler)
    logger.setLevel(level)
    _logger_list[name] = logger
    return _logger_list[name]

def setLogLevel(new_level: LEVELS):
    global level
    global _logger_list
    level = new_level
    if level != logging.NOTSET:
        basic_level = logging.CRITICAL
    else:
        basic_level = level
    logging.basicConfig(force=True, level=basic_level, datefmt='%d/%b %H:%M:%S', format='\r%(asctime)s.%(msecs)03d: %(name)-3.3s - %(levelname)-8s - %(message)s')
    logging.disable(logging.NOTSET)
    for logger in _logger_list:
        logging.Logger(logger).setLevel(level)

def logLevelName():
    return logging.getLevelName(level)

def logLevel():
    return level

def addLogLevel(value, name):
    """
    Extend logging levels of Python's built-in logging facility with custom `name`.

    This `name` will be added with lower case as an attribute of the `logging` module using the given trace `value`.
    This method will raise an `AttributeError` if the given level name already exists in the logging module.

    """
    attribute = name.lower()

    if hasattr(logging.getLoggerClass(), attribute) or hasattr(logging, attribute):
        raise AttributeError(f"The level name '{attribute}' is already defined in logger facility!")
    else:
        setattr(logging.getLoggerClass(), attribute, partialmethod(logging.getLoggerClass().log, value))
        setattr(logging, attribute, partial(logging.log, value))
        setattr(logging, name, value)
        logging.addLevelName(value, name)
