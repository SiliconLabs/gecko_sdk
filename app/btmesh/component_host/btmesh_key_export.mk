################################################################################
# BT Mesh Provisioner Application Component                                    #
################################################################################

include $(SDK_DIR)/app/bluetooth/component_host/app_log.mk
include $(SDK_DIR)/app/bluetooth/component_host/app_assert.mk

override INCLUDEPATHS += \
$(SDK_DIR)/app/btmesh/common_host/btmesh_key_export
override C_SRC += \
$(SDK_DIR)/app/btmesh/common_host/btmesh_key_export/btmesh_key_export.c 
