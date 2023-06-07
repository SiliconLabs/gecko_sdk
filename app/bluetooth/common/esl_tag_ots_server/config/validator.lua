-- validation script for proper component configuration
local config_pdu = slc.config("ESL_TAG_OTS_TRANSFER_MAX_PDU_SIZE")
local config_sdu = slc.config("ESL_TAG_OTS_TRANSFER_MAX_SDU_SIZE")

if config_pdu ~= nil and config_sdu ~= nil then
  if autonumber_common.autonumber(config_pdu.value) > autonumber_common.autonumber(config_sdu.value) then
    validation.error(
      "The PDU value " .. config_pdu .. " shall be less than or equal to the SDU value: " .. config_sdu, 
      validation.target_for_defines({"ESL_TAG_OTS_TRANSFER_MAX_PDU_SIZE", "ESL_TAG_OTS_TRANSFER_MAX_SDU_SIZE"}),
      "Please set these values properly!",
      nil)
  end
end
