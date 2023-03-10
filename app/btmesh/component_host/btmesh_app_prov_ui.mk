################################################################################
# BT Mesh Provisioner Application Component                                    #
################################################################################

include $(SDK_DIR)/app/btmesh/component_host/btmesh_app_prov.mk

# SL_CATALOG_APP_PROV_UI_PRESENT flag indicates host provisioner application component present
override CFLAGS += -D SL_CATALOG_APP_PROV_UI_PRESENT
# User input uses threading
override LDFLAGS += -pthread

override INCLUDEPATHS += \
$(SDK_DIR)/app/bluetooth/common_host/app_sleep \
$(SDK_DIR)/app/btmesh/common_host/btmesh_app_prov_ui

override C_SRC += \
$(SDK_DIR)/app/bluetooth/common_host/app_sleep/app_sleep.c \
$(SDK_DIR)/app/btmesh/common_host/btmesh_app_prov_ui/btmesh_app_prov_ui.c