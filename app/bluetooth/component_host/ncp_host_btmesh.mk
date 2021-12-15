################################################################################
# NCP host component with threading for Bluetooth Mesh                         #
################################################################################

include $(SDK_DIR)/app/bluetooth/component_host/ncp_host_bt.mk

override C_SRC += \
$(SDK_DIR)/protocol/bluetooth/src/sl_btmesh_ncp_host.c \
$(SDK_DIR)/protocol/bluetooth/src/sl_btmesh_ncp_host_api.c

# Let common code know to build BTMESH specific sources.
override CFLAGS += -DBTMESH
