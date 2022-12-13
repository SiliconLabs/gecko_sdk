################################################################################
# MQTT mock component for testing                                              #
################################################################################

override INCLUDEPATHS += $(SDK_DIR)/app/bluetooth/common_host/mqtt_mock

override C_SRC += $(SDK_DIR)/app/bluetooth/common_host/mqtt_mock/mqtt_mock.c
