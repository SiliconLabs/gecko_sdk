################################################################################
# BT Mesh Remote Provisioner Component                                         #
################################################################################

include $(SDK_DIR)/app/btmesh/component_host/btmesh_prov.mk
include $(SDK_DIR)/app/bluetooth/component_host/app_timer.mk

override INCLUDEPATHS += \
$(SDK_DIR)/app/btmesh/common_host/btmesh_remote_prov

override C_SRC += \
$(SDK_DIR)/app/btmesh/common_host/btmesh_remote_prov/btmesh_remote_prov.c