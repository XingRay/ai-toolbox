project(test)

file(GLOB_RECURSE SRC_LIST
        src/*.cpp
        src/*.c++
        src/*.cxx
        src/*.c
)

add_executable(${PROJECT_NAME}
        ${SRC_LIST}
)

message("${PROJECT_NAME} link OpenCV_LIBS:${OpenCV_LIBS}")

if (NOT TARGET glm)
    message(FATAL_ERROR "glm is not a target !")
else ()
    message("glm is a target !")
endif ()

if (NOT TARGET ncnn)
    message(FATAL_ERROR "ncnn is not a target !")
else ()
    message("ncnn is a target !")
    get_target_property(ncnn_include ncnn INTERFACE_INCLUDE_DIRECTORIES)
    message("ncnn_include:${ncnn_include}")
endif ()

target_link_libraries(${PROJECT_NAME}
        PRIVATE lib_ai_toolbox
        PRIVATE ${OpenCV_LIBS}
        PRIVATE ncnn
        PRIVATE glfw
        PRIVATE glm
)


target_include_directories(${PROJECT_NAME}
        PRIVATE src
)

include(../cmake/import_opencv.cmake)
copy_opencv_dll(${PROJECT_NAME} ${opencv_INSTALL_DIR})

include(../cmake/utils.cmake)
copyDirToTargetDir("resource/spv")