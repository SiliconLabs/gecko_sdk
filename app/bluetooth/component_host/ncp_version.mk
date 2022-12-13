################################################################################
# NCP version component                                                        #
################################################################################

override INCLUDEPATHS += $(SDK_DIR)/app/bluetooth/common_host/ncp_version

override C_SRC += $(SDK_DIR)/app/bluetooth/common_host/ncp_version/ncp_version.c

override CFLAGS += -DSL_CATALOG_NCP_VERSION_PRESENT
