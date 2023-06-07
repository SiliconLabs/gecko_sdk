
local hfxo_sleepy_crystal_support = slc.config("SL_HFXO_MANAGER_SLEEPY_CRYSTAL_SUPPORT")
local sysrtc_present = slc.is_provided("device_has_sysrtc")

if hfxo_sleepy_crystal_support.value == "1" and slc.is_provided("power_manager_deepsleep_blocking_hfxo_restore") and not sysrtc_present then
  validation.error(
    "component power_manager_deepsleep_blocking_hfxo_restore is incompatible with this feature",
    validation.target_for_defines({"SL_HFXO_MANAGER_SLEEPY_CRYSTAL_SUPPORT"}),
    nil,
    nil)
end