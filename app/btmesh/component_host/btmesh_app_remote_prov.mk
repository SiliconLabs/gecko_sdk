################################################################################
# BT Mesh Remote Provisioner Application Component                             #
################################################################################

include $(SDK_DIR)/app/btmesh/component_host/btmesh_remote_prov.mk
include $(SDK_DIR)/app/btmesh/component_host/btmesh_app_prov.mk

# SL_CATALOG_APP_REMOTE_PROV_PRESENT flag indicates remote provisioner application \
  component present,
override CFLAGS += -D SL_CATALOG_APP_REMOTE_PROV_PRESENT

override INCLUDEPATHS += \
$(SDK_DIR)/app/btmesh/common_host/btmesh_app_remote_prov

override C_SRC += \
$(SDK_DIR)/app/btmesh/common_host/btmesh_app_remote_prov/btmesh_app_remote_prov.c