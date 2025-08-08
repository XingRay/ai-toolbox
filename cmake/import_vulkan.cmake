# https://vulkan.org/
# https://vulkan.lunarg.com/
# https://vulkan.lunarg.com/sdk/home#windows

function(import_vulkan vulkan_install_dir)
    message("vulkan_INSTALL_DIR:${vulkan_INSTALL_DIR}")
    if (IS_DIRECTORY ${vulkan_INSTALL_DIR})
        set(Vulkan_sdk_dir ${vulkan_INSTALL_DIR})
    endif ()
    message("Vulkan_sdk_dir:${Vulkan_sdk_dir}")

    # 创建vulkan 导入库
    add_library(vulkan STATIC IMPORTED)

    message("vulkan include dir: ${Vulkan_sdk_dir}/Include")
    # 引入头文件方式 1
    target_include_directories(
            vulkan
            INTERFACE ${Vulkan_sdk_dir}/Include
    )

    set_target_properties(vulkan PROPERTIES
            IMPORTED_LOCATION "${Vulkan_sdk_dir}/Lib/vulkan-1.lib"
    )

endfunction()