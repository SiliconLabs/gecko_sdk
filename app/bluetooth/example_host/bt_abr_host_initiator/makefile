################################################################################
# General project settings                                                     #
################################################################################

PROJECTNAME = bt_abr_host_initiator
SDK_DIR = ../../../..
BGBUILD = $(SDK_DIR)/protocol/bluetooth/bin/gatt/bgbuild.py


################################################################################
# Components                                                                   #
#                                                                              #
# After setting up the toolchain, components can contribute to the project by  #
# appending items to the project variables like INCLUDEPATHS or C_SRC.         #
################################################################################

include $(SDK_DIR)/app/bluetooth/component_host/toolchain.mk
include $(SDK_DIR)/app/bluetooth/component_host/app_log.mk
include $(SDK_DIR)/app/bluetooth/component_host/app_assert.mk
include $(SDK_DIR)/app/bluetooth/component_host/app_signal.mk
include $(SDK_DIR)/app/bluetooth/component_host/ncp_host_nothread.mk
include $(SDK_DIR)/app/bluetooth/component_host/rtl_lib.mk
include $(SDK_DIR)/app/bluetooth/component_host/abr_cs_parser.mk
include $(SDK_DIR)/app/bluetooth/component_host/abr_initiator.mk
include $(SDK_DIR)/app/bluetooth/component_host/cjson.mk


################################################################################
# Include paths                                                                #
################################################################################

override INCLUDEPATHS += . \
$(SDK_DIR)/app/bluetooth/common_host/system \
$(SDK_DIR)/platform/common/inc \
$(SDK_DIR)/protocol/bluetooth/inc \
autogen


################################################################################
# Input files                                                                  #
################################################################################

override C_SRC += \
$(SDK_DIR)/app/bluetooth/common_host/system/system.c \
app.c \
main.c

PROJ_FILES += $(wildcard $(SDK_DIR)/protocol/bluetooth/bin/gatt/*)
PROJ_FILES += config/btconf/gatt_configuration.btconf

################################################################################
# Target rules                                                                 #
################################################################################

include $(SDK_DIR)/app/bluetooth/component_host/targets.mk
override CFLAGS += -DABR_FILE_LOG_ENABLED=1