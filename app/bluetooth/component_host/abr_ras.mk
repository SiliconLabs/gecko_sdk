################################################################################
# ABR RAS component                                                            #
################################################################################

override INCLUDEPATHS += \
$(SDK_DIR)/app/bluetooth/common/abr_ras

override C_SRC += \
$(SDK_DIR)/app/bluetooth/common/abr_ras/abr_ras.c
