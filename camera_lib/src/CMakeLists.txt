cmake_minimum_required(VERSION 3.10)
project(camera_lib)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
# Create the shared library
add_library(camera_lib SHARED camera_lib.cpp)
target_include_directories(camera_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(camera_lib opencv_core480 opencv_highgui480 opencv_videoio480 opencv_imgproc480)

if(MSVC)
    target_compile_definitions(camera_lib PRIVATE CAMERA_LIB_EXPORTS)
endif()