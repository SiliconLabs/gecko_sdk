if slc.is_provided("micriumos_fs_storage_nor_driver_spi") and 
   slc.is_provided("hardware_board")
   if not slc.is_selected("brd4160a")
     validation.warning("The selected board may not have NOR over SPI",
                        validation.target_for_defines({"FS_STORAGE_NOR"}),
                        nil,
                        nil)
   end
end

if slc.is_provided("micriumos_fs_storage_nor_driver_quad_spi") and 
   slc.is_provided("hardware_board")
   if not slc.is_selected("brd2204a")
     validation.warning("The selected board may not have NOR over Quad SPI",
                        validation.target_for_defines({"FS_STORAGE_NOR"}),
                        nil,
                        nil)
   end
end