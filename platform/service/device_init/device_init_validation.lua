if slc.is_selected("device_init_lfrco") then
  local config_peripheral = slc.config("SL_DEVICE_INIT_LFRCO_PRECISION")

  if slc.is_provided("device_init_lfrco") and not slc.is_provided("device_init_hfxo") then
      if config_peripheral.value == "cmuPrecisionHigh" then
          validation.warning(
          "PRORTC peripheral is not available on the selected target",
          validation.target_for_defines({"SL_SLEEPTIMER_PERIPHERAL"}),
          nil,
          nil)
      end        
  end
end

if slc.is_selected("device_init_hfxo") and slc.is_provided("device_series_1") then
  local config_hfxo_autostart = slc.config("SL_DEVICE_INIT_HFXO_AUTOSTART")
  local config_hfxo_autoselect = slc.config("SL_DEVICE_INIT_HFXO_AUTOSELECT")

  if config_hfxo_autostart.value == "true" then
    validation.warning(
    "SL_DEVICE_INIT_HFXO_AUTOSTART configuration is now deprecated.",
    validation.target_for_defines({"SL_DEVICE_INIT_HFXO_AUTOSTART"}), 
    "To use the HFXO autostart feature, please call CMU_HFXOAutostartEnable() API directly in your application after clocks initialization. Note that this feature is incompatible with Power Manager and can only be used in applications that do not use Power Manager or a radio protocol stack.",
    nil)
  end

  if config_hfxo_autoselect.value == "true" then
    validation.warning(
    "SL_DEVICE_INIT_HFXO_AUTOSELECT configuration is now deprecated.",
    validation.target_for_defines({"SL_DEVICE_INIT_HFXO_AUTOSELECT"}), 
    "To use the HFXO autoselect feature, please call CMU_HFXOAutostartEnable() API directly in your application after clocks initialization. Note that this feature is incompatible with Power Manager and can only be used in applications that do not use Power Manager or a radio protocol stack.",
    nil)
  end
end

if slc.is_selected("device_init_dpll") and slc.is_provided("device_series_2") then
  local ref_clock = slc.config("SL_DEVICE_INIT_DPLL_REFCLK")

  if ref_clock.value == "cmuSelect_HFXO" then
    if slc.is_provided("device_init_hfxo") then
      local hfxo_freq = tonumber(slc.config("SL_DEVICE_INIT_HFXO_FREQ").value)
      local dpll_n = tonumber(slc.config("SL_DEVICE_INIT_DPLL_N").value)
      local dpll_m = tonumber(slc.config("SL_DEVICE_INIT_DPLL_M").value)
      local dpll_freq_expert = tonumber(slc.config("SL_DEVICE_INIT_DPLL_FREQ").value)

      -- check formula validation: dpll_freq = hfxo_freq * (N+1)/(M+1)
      local dpll_freq = hfxo_freq * (dpll_n + 1) / (dpll_m + 1)
      if dpll_freq ~= dpll_freq_expert then
        validation.warning(
        "Target frequency is not reacheable based on HFXO_FREQ",
        validation.target_for_defines({"SL_DEVICE_INIT_DPLL_FREQ"}),
        nil,
        nil)
      end
    else
      validation.warning(
      "HFXO is not initialized in this project",
      validation.target_for_defines({"SL_DEVICE_INIT_DPLL_REFCLK"}),
      "HFXO needs to be initialized",
      nil)
    end
  end
end