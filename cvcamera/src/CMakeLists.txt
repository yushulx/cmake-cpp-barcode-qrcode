cmake_minimum_required(VERSION 3.10)
project(camera_lib)

# Set the library path based on the operating system
if(WIN32)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/windows)
    set(OPENCV_LIBS opencv_core480 opencv_highgui480 opencv_videoio480 opencv_imgproc480)
elseif(UNIX)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/linux)
    set(OPENCV_LIBS opencv_core opencv_highgui opencv_videoio opencv_imgproc)
endif()

# Create the shared library
add_library(camera_lib SHARED camera_lib.cpp)
target_include_directories(camera_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(camera_lib ${OPENCV_LIBS})

if(MSVC)
    target_compile_definitions(camera_lib PRIVATE CAMERA_LIB_EXPORTS)
endif()