################################################################################
# Antenna switching component for ABR initiator                                #
################################################################################

override INCLUDEPATHS += \
$(SDK_DIR)/app/bluetooth/common/abr_ans

override C_SRC += \
$(SDK_DIR)/app/bluetooth/common/abr_ans/abr_ans.c
