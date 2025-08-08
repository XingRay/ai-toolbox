project(lib_ai_toolbox)


file(GLOB_RECURSE SRC_LIST
        *.cpp
        *.c++
        *.cxx
        *.c
)


add_library(${PROJECT_NAME} STATIC
        ${SRC_LIST}
)


target_link_libraries(${PROJECT_NAME}
        PUBLIC ${OpenCV_LIBS}
        PUBLIC ncnn
        PUBLIC vklite
)
