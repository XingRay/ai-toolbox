function(import_ncnn ncnn_install_dir)
    message("import_ncnn: ncnn_install_dir:${ncnn_install_dir}")

    # 根据编译类型选择子路径
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(ncnn_DIR "${ncnn_install_dir}/debug/lib/cmake/ncnn")
    else ()
        set(ncnn_DIR "${ncnn_install_dir}/release/lib/cmake/ncnn")
    endif ()

    find_package(ncnn)
endfunction()