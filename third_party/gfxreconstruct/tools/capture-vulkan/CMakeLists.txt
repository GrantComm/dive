add_custom_target(gfxrecon-capture-vulkan.py ALL
                  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/gfxrecon-capture-vulkan.py
                  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/gfxrecon-capture-vulkan.py ${CMAKE_CURRENT_BINARY_DIR}/gfxrecon-capture-vulkan.py)

# GOOGLE: Add folder organization for windows build in dive.
if(MSVC)
    set_target_properties(gfxrecon-capture-vulkan.py PROPERTIES FOLDER "gfxreconstruct")
endif()
                  
install(FILES gfxrecon-capture-vulkan.py DESTINATION ${CMAKE_INSTALL_BINDIR} PERMISSIONS
        OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
