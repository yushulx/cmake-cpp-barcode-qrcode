cmake_minimum_required(VERSION 3.10)
project(camera_lib)
# find_package(OpenCV REQUIRED)
# set(OpenCV_DIR "c:/opencv/sources") # Update this path to the location of your OpenCV source code

# set(OpenCV_MODULES_CORE ON)
# set(OpenCV_MODULES_IMGPROC ON)
# set(OpenCV_MODULES_HIGHGUI ON)
# set(OpenCV_MODULES_VIDEOIO ON)

add_subdirectory(src)
add_subdirectory(example)
