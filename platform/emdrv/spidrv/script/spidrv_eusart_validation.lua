local spidrv = slc.component("spidrv_eusart")
local max_clkdiv = 256
local min_clkdiv = 1
for k, v in pairs(spidrv.instances) do 
    local instance = string.upper(k)
    local spidrv_config_prefix = "SL_SPIDRV_EUSART_" .. instance 
    local str_cs_port = spidrv_config_prefix .. "_CS_PORT"
    local str_cs_control = spidrv_config_prefix .. "_CS_CONTROL"
    local str_spi_bitrate = spidrv_config_prefix .. "_BITRATE"
    local str_spi_mode =  spidrv_config_prefix .. "_TYPE"
    local spi_mode = slc.config(str_spi_mode).value
    local spi_bitrate = tonumber(slc.config(str_spi_bitrate).value)
    local config_control = slc.config(str_cs_control)
    local config_cs = slc.config(str_cs_port)

    if slc.is_provided("device_series_2") then
        if spi_mode == "spidrvMaster" then
            if spi_bitrate > 20000000 then
                validation.warning(
                "Bitrate of SPI master mode must equal or lower than 20Mbps",
                validation.target_for_defines({str_spi_bitrate}),
                "Set bitrate equal or lower than 20Mbps",
                nil)
            end
        else
            if spi_bitrate > 10000000 then
                validation.warning(
                "Bitrate of SPI slave mode must equal or lower than 10Mbps",
                validation.target_for_defines({str_spi_bitrate}),
                "Set bitrate equal or lower than 10Mbps",
                nil)
            end
        end
    end
    
    if slc.is_selected("device_init_dpll") and slc.is_provided("device_series_2") then
        local ref_clock = slc.config("SL_DEVICE_INIT_DPLL_REFCLK")
        if ref_clock.value == "cmuSelect_HFXO" then
            if slc.is_provided("device_init_hfxo") then
                local dpll_freq_expect = tonumber(slc.config("SL_DEVICE_INIT_DPLL_FREQ").value)
                if dpll_freq_expect / spi_bitrate > max_clkdiv then
                    validation.warning(
                    "clkdiv is too high, need to be equal or smaller than 256",
                    validation.target_for_defines({str_spi_bitrate}),
                    "Set a higher bitrate or lower the reference clock dpll",
                    nil)
                elseif dpll_freq_expect / spi_bitrate < min_clkdiv then
                    validation.warning(
                    "clkdiv is too low, need to be equal or higher than 1",
                    validation.target_for_defines({str_spi_bitrate}),
                    "Set a lower bitrate or higher the reference clock dpll",
                    nil)
                else
                end
            end
        end
    else
        local hfxo_frequency = tonumber(slc.config("SL_DEVICE_INIT_HFXO_FREQ").value)
        if hfxo_frequency / spi_bitrate > max_clkdiv then
            validation.warning(
            "clkdiv is too high, need to be equal or smaller than 256",
            validation.target_for_defines({str_spi_bitrate}),
            "Set a higher bitrate or lower the reference clock hfxo",
            nil)
        elseif hfxo_frequency / spi_bitrate < min_clkdiv then
            validation.warning(
            "clkdiv is too low, need to be equal or higher than 1",
            validation.target_for_defines({str_spi_bitrate}),
            "Set a lower bitrate or higher the reference clock hfxo",
            nil)
        else
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