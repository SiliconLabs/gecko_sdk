################################################################################
# BT Mesh Remote Provisioner Application Component                             #
################################################################################

include $(SDK_DIR)/app/btmesh/component_host/btmesh_app_prov.mk

# SL_CATALOG_APP_PROV_CBP_PRESENT flag indicates CBP component is present
override CFLAGS += -D SL_CATALOG_APP_PROV_CBP_PRESENT

# OpenSSL-related includes

# OpenSSL headers
# OpenSSL is outside of GSDK. Therefore, add it directly as a compiler flag
# instead of adding it to INCLUDEPATHS.
ifeq ($(UNAME), darwin)
  override CFLAGS += -I/usr/local/opt/openssl/include
else
  override CFLAGS += -I/usr/include/openssl
endif

# OpenSSL libraries
ifeq ($(UNAME), darwin)
	override LDFLAGS += -L/usr/local/opt/openssl/lib
endif
override LDFLAGS += -lcrypto
ifeq ($(OS), win)
	#override LDFLAGS +=	-lws2_32
endif


override INCLUDEPATHS += \
$(SDK_DIR)/app/btmesh/common_host/btmesh_app_prov_cbp

override C_SRC += \
$(wildcard $(SDK_DIR)/app/btmesh/common_host/btmesh_app_prov_cbp/*.c)