local changeset = {}

local old_config = slc.config('SL_PSA_ITS_SUPPORT_V3_DRIVER')

if slc.is_selected('psa_its') then
    if (old_config == nil) then
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
    end
end

return changeset