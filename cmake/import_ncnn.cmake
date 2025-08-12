function(import_ncnn ncnn_install_dir)
    message("import_ncnn: ncnn_install_dir:${ncnn_install_dir}")
    set(ncnn_base_dir "")
    # 根据编译类型选择子路径
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(ncnn_base_dir "${ncnn_install_dir}/debug")
    else ()
        set(ncnn_base_dir "${ncnn_install_dir}/release")
    endif ()
    message("ncnn_base_dir:${ncnn_base_dir}")
    set(ncnn_DIR "${ncnn_base_dir}/lib/cmake/ncnn")
    message("ncnn_DIR:${ncnn_DIR}")
    find_package(ncnn)

    # 手动添加头文件路径
    if (NOT TARGET ncnn)
        message(FATAL_ERROR "import ncnn failed !")
    endif ()

    set_target_properties(ncnn PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${ncnn_base_dir}/include"
    )
    get_target_property(ncnn_include_dirs ncnn INTERFACE_INCLUDE_DIRECTORIES)
    message("ncnn_include_dirs:${ncnn_include_dirs}")

endfunction()