--Validation script for Bootloader Image Parser with no encryption component

local has_parser_noenc = slc.is_selected("bootloader_image_parser_nonenc")

local btl_enforce_signed_upgrade = slc.config('BOOTLOADER_ENFORCE_SIGNED_UPGRADE')
local btl_enforce_encryption = slc.config('BOOTLOADER_ENFORCE_ENCRYPTED_UPGRADE')

if btl_enforce_encryption.value == "1" and has_parser_noenc then
    validation.error('Can not use parser without encryption support, since the bootloader is configured to enforce encrypted upgrade files',
	validation.target_for_defines({'BOOTLOADER_ENFORCE_ENCRYPTED_UPGRADE'}))
end
