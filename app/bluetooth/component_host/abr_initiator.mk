################################################################################
# ABR initiator component                                                     #
################################################################################

override INCLUDEPATHS += \
$(SDK_DIR)/app/bluetooth/common/abr_initiator \
$(SDK_DIR)/app/bluetooth/common/abr_initiator/config

override C_SRC += \
$(SDK_DIR)/app/bluetooth/common/abr_initiator/abr_initiator.c \
$(SDK_DIR)/app/bluetooth/common/abr_initiator/abr_initiator_config.c \
$(SDK_DIR)/app/bluetooth/example_host/bt_abr_host_initiator/host_platform.c
