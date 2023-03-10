-- Provisionee validation script

local oob_enable = slc.config('SL_BTMESH_PROVISIONEE_OOB_ENABLE_CFG_VAL')

local no_oob = slc.config('SL_BTMESH_PROVISIONEE_AUTH_NO_OOB_CFG_VAL').value == "1"
local static_oob = slc.config('SL_BTMESH_PROVISIONEE_AUTH_STATIC_OOB_CFG_VAL').value == "1"
local output_oob = slc.config('SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_CFG_VAL').value == "1"
local input_oob = slc.config('SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_CFG_VAL').value == "1"

local output_blink = slc.config('SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_BLINK_CFG_VAL').value == "1"
local output_beep = slc.config('SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_BEEP_CFG_VAL').value == "1"
local output_vibrate = slc.config('SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_VIBRATE_CFG_VAL').value == "1"
local output_numeric = slc.config('SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_NUMERIC_CFG_VAL').value == "1"
local output_alpha = slc.config('SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_ALPHA_CFG_VAL').value == "1"

local input_push = slc.config('SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_PUSH_CFG_VAL').value == "1"
local input_twist = slc.config('SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_TWIST_CFG_VAL').value == "1"
local input_numeric = slc.config('SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_NUMERIC_CFG_VAL').value == "1"
local input_alpha = slc.config('SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_ALPHA_CFG_VAL').value == "1"

if oob_enable.value == "1" then
  if not (no_oob or static_oob or output_oob or input_oob) then
    validation.error(
      'No authentication method enabled',
      validation.target_for_defines({ oob_enable.id }),
      'Enable at least one authentication method (No OOB, Static OOB, Output OOB, Input OOB) or disable OOB')
  end
  if output_oob and
      not (output_blink or output_beep or output_vibrate or output_numeric or output_alpha) then
    validation.error(
      'No output method enabled',
      validation.target_for_defines({ oob_enable.id }),
      'Enable at least one output method or disable Output OOB'
    )
  end
  if input_oob and not (input_push or input_twist or input_numeric or input_alpha) then
    validation.error(
      'No input method enabled',
      validation.target_for_defines({ oob_enable.id }),
      'Enable at least one input method or disable Input OOB'
    )
  end
end
