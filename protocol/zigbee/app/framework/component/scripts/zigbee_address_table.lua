local address_table_size = slc.config("EMBER_ADDRESS_TABLE_SIZE")
local af_plugin_address_table_size = slc.config("EMBER_AF_PLUGIN_ADDRESS_TABLE_SIZE")
local af_plugin_address_table_trust_center_cache_size = slc.config("EMBER_AF_PLUGIN_ADDRESS_TABLE_TRUST_CENTER_CACHE_SIZE")

if ( address_table_size ~= nil and af_plugin_address_table_size ~= nil and af_plugin_address_table_trust_center_cache_size ~= nil ) then
    if (tonumber(address_table_size.value) < tonumber(af_plugin_address_table_size.value) + tonumber(af_plugin_address_table_trust_center_cache_size.value)) then
        validation.error("Please ensure that EMBER_ADDRESS_TABLE_SIZE is greater than sum of (EMBER_AF_PLUGIN_ADDRESS_TABLE_SIZE + EMBER_AF_PLUGIN_ADDRESS_TABLE_TRUST_CENTER_CACHE_SIZE). ",
        validation.target_for_project(),
        nil,
        nil)
    end
end