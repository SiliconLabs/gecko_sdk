################################################################################
# BT Mesh Provisioner Application Component                                    #
################################################################################

include $(SDK_DIR)/app/btmesh/component_host/btmesh_app_prov_ui.mk
include $(SDK_DIR)/app/btmesh/component_host/btmesh_app_remote_prov.mk

override INCLUDEPATHS += \
$(SDK_DIR)/app/btmesh/common_host/btmesh_app_remote_prov_ui

override C_SRC += \
$(SDK_DIR)/app/btmesh/common_host/btmesh_app_remote_prov_ui/btmesh_app_remote_prov_ui.c