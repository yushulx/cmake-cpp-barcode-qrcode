cmake_minimum_required(VERSION 3.0.0)

project(bridge VERSION 0.1.0)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    link_directories("${PROJECT_SOURCE_DIR}/../platforms/win/bin/") 
else()
    link_directories("${PROJECT_SOURCE_DIR}/../platforms/win/lib/") 
endif()

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/../include/")
add_library(bridge SHARED bridge.cpp)
target_link_libraries (${PROJECT_NAME} "DynamsoftLicensex64" "DynamsoftCaptureVisionRouterx64")

