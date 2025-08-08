#opencv
# https://opencv.org/
# https://github.com/opencv/opencv
function(import_opencv opencv_install_dir)
    message("import_opencv: opencv_install_dir:${opencv_install_dir}")
    set(OpenCV_DIR ${opencv_install_dir})
    find_package(OpenCV REQUIRED)
    message("OpenCV_FOUND:${OpenCV_FOUND}")
    message("OpenCV_INCLUDE_DIRS:${OpenCV_INCLUDE_DIRS}")
    message("OpenCV_LIBS:${OpenCV_LIBS}")
    if (NOT ${OpenCV_FOUND})
        message(FATAL_ERROR "OpenCV not found !")
    endif ()

    set(OpenCV_FOUND ${OpenCV_FOUND} PARENT_SCOPE)
    set(OpenCV_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS} PARENT_SCOPE)
    set(OpenCV_LIBS ${OpenCV_LIBS} PARENT_SCOPE)

endfunction()


# 自动复制 OpenCV DLL（Debug/Release 自动适配）
function(copy_opencv_dll target_name opencv_install_dir)
    message("copy_opencv_dll: target_name:${target_name} opencv_install_dir:${opencv_install_dir}")
    add_custom_command(TARGET ${target_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${opencv_install_dir}/../bin/$<IF:$<CONFIG:Debug>,opencv_world4120d.dll,opencv_world4120.dll>"
            "$<TARGET_FILE_DIR:${target_name}>/"
            COMMENT "Copying OpenCV DLL ($<CONFIG>) to executable directory"
    )
endfunction()