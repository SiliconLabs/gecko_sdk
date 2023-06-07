################################################################################
# BT Mesh Provisioner Application Component                                    #
################################################################################

include $(SDK_DIR)/app/bluetooth/component_host/app_log.mk
include $(SDK_DIR)/app/bluetooth/component_host/app_assert.mk
include $(SDK_DIR)/app/btmesh/component_host/btmesh_prov.mk
include $(SDK_DIR)/app/btmesh/component_host/btmesh_conf.mk
include $(SDK_DIR)/app/btmesh/component_host/btmesh_key_export.mk
include $(SDK_DIR)/app/bluetooth/component_host/app_timer.mk

# SL_CATALOG_APP_PROV_PRESENT flag indicates host provisioner application component present
override CFLAGS += -D SL_CATALOG_APP_PROV_PRESENT

override INCLUDEPATHS += \
$(SDK_DIR)/app/btmesh/common_host/btmesh_app_prov

override C_SRC += \
$(SDK_DIR)/app/btmesh/common_host/btmesh_app_prov/btmesh_app_prov.c
