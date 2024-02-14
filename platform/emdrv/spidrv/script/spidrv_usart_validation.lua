local spidrv = slc.component("spidrv_usart")
local max_clkdiv = 256
local min_clkdiv = 1
for k, v in pairs(spidrv.instances) do 
    local instance = string.upper(k)
    local spidrv_config_prefix = "SL_SPIDRV_USART_" .. instance 
    local str_cs_port = spidrv_config_prefix .. "_CS_PORT"
    local str_cs_control = spidrv_config_prefix .. "_CS_CONTROL"
    local str_spi_bitrate = spidrv_config_prefix .. "_BITRATE"
    local str_spi_mode =  spidrv_config_prefix .. "_TYPE"
    local spi_mode = slc.config(str_spi_mode).value
    local spi_bitrate = tonumber(slc.config(str_spi_bitrate).value)
    local config_control = slc.config(str_cs_control)
    local config_cs = slc.config(str_cs_port)
    local freq = nil
    local selected_clkdiv = nil
    if slc.is_selected("device_init_dpll") and slc.is_provided("device_series_2") then
        if (slc.config("SL_DEVICE_INIT_DPLL_REFCLK")).value == "cmuSelect_HFXO" and slc.is_provided("device_init_hfxo") then
            freq = tonumber(slc.config("SL_DEVICE_INIT_DPLL_FREQ").value)
        end
        selected_clkdiv = freq / (2 * spi_bitrate)
        if selected_clkdiv > max_clkdiv then
            validation.warning(
                "clkdiv is too high, need to be equal or smaller than 256",
                validation.target_for_defines({str_spi_bitrate}),
                "Set a higher bitrate or lower the reference clock dpll",
                nil)
        elseif selected_clkdiv < min_clkdiv then
                validation.warning(
                "clkdiv is too low, need to be equal or higher than 1",
                validation.target_for_defines({str_spi_bitrate}),
                "Set a lower bitrate or higher the reference clock dpll",
                nil)
        end
    else
        freq = tonumber(slc.config("SL_DEVICE_INIT_HFXO_FREQ").value)
        selected_clkdiv = freq / (2 * spi_bitrate)
        if selected_clkdiv > max_clkdiv then
            validation.warning(
                "clkdiv is too high, need to be equal or smaller than 256",
                validation.target_for_defines({str_spi_bitrate}),
                "Set a higher bitrate or lower the reference clock hfxo",
                nil)
        elseif selected_clkdiv < min_clkdiv then
                validation.warning(
                "clkdiv is too low, need to be equal or higher than 1",
                validation.target_for_defines({str_spi_bitrate}),
                "Set a lower bitrate or higher the reference clock hfxo",
                nil)
        end
    end

    if spi_mode == "spidrvMaster" then
        if spi_bitrate > (freq / 2) then
            validation.warning(
            "Bitrate of SPI master mode must be equal or lower than half of the peripheral clock frequency",
            validation.target_for_defines({str_spi_bitrate}),
            "Set bitrate equal or lower than half of the peripheral clock frequency",
            nil)
        end
    else
        if slc.is_provided("device_generic_family_efr32xg22") or slc.is_provided("device_generic_family_efr32xg23") or slc.is_provided("device_generic_family_efr32xg24") then
            if spi_bitrate > (freq / 6) then
                validation.warning(
                "Bitrate of SPI slave mode must be equal or lower than one sixth of the peripheral clock frequency",
                validation.target_for_defines({str_spi_bitrate}),
                "Set bitrate equal or lower than one sixth of the peripheral clock frequency",
                nil)
            end
        else
            if spi_bitrate > (freq / 8) then
                validation.warning(
                "Bitrate of SPI slave mode must be equal or lower than one eighth of the peripheral clock frequency",
                validation.target_for_defines({str_spi_bitrate}),
                "Set bitrate equal or lower than one eighth of the peripheral clock frequency",
                nil)
            end
        end
    end

    if (config_control.value == "spidrvCsControlAuto") and config_cs == nil then
        local msg = instance .. " : SPIDRV is configured to control CS, but no CS pin is selected"
        validation.error(msg,
                        validation.target_for_defines({str_cs_port}),
                        "CS must be controlled by the application, or a CS pin must be configured",
                        nil)
    end
end