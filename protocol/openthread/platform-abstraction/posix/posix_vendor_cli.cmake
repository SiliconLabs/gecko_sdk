#
#  Copyright (c) 2023, The OpenThread Authors.
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are met:
#  1. Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#  3. Neither the name of the copyright holder nor the
#     names of its contributors may be used to endorse or promote products
#     derived from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
#  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
#  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
#  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
#  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
#  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
#  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
#  POSSIBILITY OF SUCH DAMAGE.
#

include(${CMAKE_CURRENT_LIST_DIR}/posix_vendor_api.cmake)

set(CLI_SOURCES "")

option(SL_OT_ANTENNA_CLI "Enable support for antenna diversity cli commands" ON)
option(SL_OT_COEX_CLI    "Enable support for coexistence cli commands" ON)
option(SL_OT_TEST_CLI    "Enable support for test cli commands" OFF)

if(SL_OT_ANTENNA_CLI)
    list (APPEND CLI_SOURCES ${CLI_SRC_DIR}/antenna_diversity_cli.c)
    target_compile_definitions(ot-config INTERFACE "SL_OPENTHREAD_ANT_DIV_CLI_ENABLE=1")
endif()

if(SL_OT_COEX_CLI)
    list (APPEND CLI_SOURCES ${CLI_SRC_DIR}/coexistence_cli.c)
    target_compile_definitions(ot-config INTERFACE "SL_OPENTHREAD_COEX_CLI_ENABLE=1")
endif()

if(SL_OT_TEST_CLI)
    list (APPEND CLI_SOURCES ${CLI_SRC_DIR}/test_cli.c)
    target_compile_definitions(ot-config INTERFACE "SL_OPENTHREAD_TEST_CLI_ENABLE=1")
endif()

if(NOT CLI_SOURCES STREQUAL "")
    target_compile_definitions(ot-config INTERFACE "OPENTHREAD_CONFIG_CLI_MAX_USER_CMD_ENTRIES=2")

    add_library(ot-vendor-posix-cli
        ${CLI_SRC_DIR}/cli_utils.c
        ${POSIX_SRC_DIR}/posix_cli_user_commands.cpp
        ${CLI_SOURCES}
    )

    target_link_libraries(ot-vendor-posix-cli
        PUBLIC
            ot-vendor-posix-api
            openthread-cli-ftd
            ot-posix-config
            ot-config
    )

    target_compile_definitions(ot-vendor-posix-cli
        PRIVATE
            OPENTHREAD_FTD=1
    )

    target_include_directories(ot-vendor-posix-cli
        PRIVATE
            ${PAL_INC_DIR}
            ${CLI_INC_DIR}
            ${UTIL_INC_DIR}
    )

    set(OT_CLI_VENDOR_TARGET ot-vendor-posix-cli)
endif()
