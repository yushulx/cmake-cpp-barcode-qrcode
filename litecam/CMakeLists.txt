cmake_minimum_required(VERSION 3.10)

# Project name and version
project(CameraProject VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define include directories
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Define source files for the Camera library
if (WIN32)
    set(LIBRARY_SOURCES
        src/CameraWindows.cpp
        src/CameraPreviewWindows.cpp
    )
elseif (UNIX AND NOT APPLE)
    set(LIBRARY_SOURCES
        src/CameraLinux.cpp
        src/CameraPreviewLinux.cpp
    )
elseif (APPLE)
    set(LIBRARY_SOURCES
        src/CameraMacOS.mm
        src/CameraPreviewMacOS.mm
    )
endif()

# Define source files for the executable
set(EXECUTABLE_SOURCES
    src/main.cpp
)

# Add the Camera shared library
add_library(Camera SHARED ${LIBRARY_SOURCES})

# Set include directories for the Camera library
target_include_directories(Camera PUBLIC ${INCLUDE_DIR})

# Define the CAMERA_EXPORTS macro for the shared library
target_compile_definitions(Camera PRIVATE CAMERA_EXPORTS)

# Platform-specific dependencies for the Camera library
if (UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    if (X11_FOUND)
        target_include_directories(Camera PUBLIC ${X11_INCLUDE_DIR})
        target_link_libraries(Camera PRIVATE ${X11_LIBRARIES} pthread)
    endif()
elseif (APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(AVFOUNDATION_LIBRARY AVFoundation)
    target_link_libraries(Camera PRIVATE ${AVFOUNDATION_LIBRARY})
elseif (WIN32)
    target_link_libraries(Camera PRIVATE ole32 uuid mfplat mf mfreadwrite mfuuid)
endif()

# Add the camera_capture executable
add_executable(camera_capture ${EXECUTABLE_SOURCES})

# Link the Camera library to the executable
target_link_libraries(camera_capture PRIVATE Camera)

# Include the shared library's headers in the executable
target_include_directories(camera_capture PRIVATE ${INCLUDE_DIR})
