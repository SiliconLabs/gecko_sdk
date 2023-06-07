################################################################################
# ABR CS parser  component                                                     #
################################################################################

override INCLUDEPATHS += \
$(SDK_DIR)/app/bluetooth/common/abr_cs_parser \
$(SDK_DIR)/app/bluetooth/common/abr_cs_parser/config

override C_SRC += \
$(SDK_DIR)/app/bluetooth/common/abr_cs_parser/abr_cs_parser.c \
$(SDK_DIR)/app/bluetooth/common/abr_cs_parser/abr_file_log.c
