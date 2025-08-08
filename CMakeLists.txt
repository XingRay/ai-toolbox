cmake_minimum_required(VERSION 3.31)
project(ai_toolbox)

set(CMAKE_CXX_STANDARD 23)

# 源码使用utf8编码
if (MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/source-charset:utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")
else ()
    add_compile_options(-finput-charset=UTF-8)
endif ()


set(ncnn_INSTALL_DIR "D:/develop/ncnn/master/install/windows/x64" CACHE STRING "ncnn install dir")
set(vulkan_INSTALL_DIR "D:/develop/vulkan/VulkanSDK/1.3.296.0" CACHE STRING "vulkan install dir")
set(Vklite_INSTALL_DIR "D:/code/git/github/vklite/build/dist/vklite/lib/cmake" CACHE STRING "vklite install dir")
set(glfw_INSTALL_DIR "D:/develop/opengl/glfw/glfw-3.4.bin.WIN64" CACHE STRING "glfw path")
set(opencv_INSTALL_DIR "D:/develop/opencv/4.12.0/opencv/build/x64/vc16/lib")
set(glm_INSTALL_DIR "D:/develop/opengl/glm/glm-1.0.1-light")

include(cmake/import_glfw.cmake)
import_glfw(${glfw_INSTALL_DIR})

include(cmake/import_ncnn.cmake)
import_ncnn(${ncnn_INSTALL_DIR})

include(cmake/import_opencv.cmake)
import_opencv(${opencv_INSTALL_DIR})

include(cmake/import_vulkan.cmake)
import_vulkan(${vulkan_INSTALL_DIR})

include(cmake/import_vklite.cmake)
import_vklite(${Vklite_INSTALL_DIR})

include(cmake/import_glm.cmake)
import_glm(${glm_INSTALL_DIR})

add_subdirectory(src)
add_subdirectory(test)