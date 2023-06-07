################################################################################
# General project settings                                                     #
################################################################################

PROJECTNAME = bt_host_cpc_hci_bridge
SDK_DIR = ../../../..


################################################################################
# Set this variable to the location of your CPC directory cloned from GitHub.  #
# Follow the instructions at https://github.com/SiliconLabs/cpc-daemon.        #
# If this variable is not set the installed cpcd will be linked instead.       #
################################################################################
CPC_DIR ?=


################################################################################
# Components                                                                   #
#                                                                              #
# After setting up the toolchain, components can contribute to the project by  #
# appending items to the project variables like INCLUDEPATHS or C_SRC.         #
################################################################################

include $(SDK_DIR)/app/bluetooth/component_host/toolchain.mk
include $(SDK_DIR)/app/bluetooth/component_host/app_log.mk

ifeq ($(OS), win)
  $(error The CPC-HCI bridge is not supported on Windows!)
endif
ifeq ($(UNAME), darwin)
  $(error The CPC-HCI bridge is not supported on macOS!)
endif


################################################################################
# Include paths                                                                #
################################################################################

override INCLUDEPATHS += . \
$(SDK_DIR)/platform/common/inc \
$(SDK_DIR)/protocol/bluetooth/bgstack/ll/utils/hci_packet/inc

ifneq ($(CPC_DIR), )
  override INCLUDEPATHS += ${CPC_DIR}/daemon/lib
endif


################################################################################
# Input files                                                                  #
################################################################################

override C_SRC += \
main.c

ifneq ($(CPC_DIR), )
  LIBS = $(CPC_DIR)/daemon/build/libcpc.so
else
  override LDFLAGS += -lcpc
  $(info CPC library dir in CPC_DIR is not set, linking with installed libcpc)
endif

# Some linux distros require this for PTY
override LDFLAGS += -lutil

################################################################################
# Target rules                                                                 #
################################################################################

include $(SDK_DIR)/app/bluetooth/component_host/targets.mk
