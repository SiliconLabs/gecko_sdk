local changeset = {}

local old_config_v1 = slc.config('SL_PSA_ITS_SUPPORT_V1_DRIVER')
local old_config_v2 = slc.config('SL_PSA_ITS_SUPPORT_V2_DRIVER')
local old_config_v3 = slc.config('SL_PSA_ITS_SUPPORT_V3_DRIVER')

if slc.is_selected('psa_its') then
    if (old_config_v3 == nil) then
        table.insert(changeset, {
            ['option'] = 'SL_PSA_ITS_SUPPORT_V1_DRIVER',
            ['value'] = '1'
        })
        table.insert(changeset, {
            ['option'] = 'SL_PSA_ITS_SUPPORT_V2_DRIVER',
            ['value'] = '1'
        })
        table.insert(changeset, {
            ['option'] = 'SL_PSA_ITS_SUPPORT_V3_DRIVER',
            ['value'] = '0'
        })
    else
        table.insert(changeset, {
            ['option'] = 'SL_PSA_ITS_SUPPORT_V1_DRIVER',
            ['value'] = old_config_v1.value
        })
        table.insert(changeset, {
            ['option'] = 'SL_PSA_ITS_SUPPORT_V2_DRIVER',
            ['value'] = old_config_v2.value
        })
        table.insert(changeset, {
            ['option'] = 'SL_PSA_ITS_SUPPORT_V3_DRIVER',
            ['value'] = old_config_v3.value
        })
    end
end

return changeset