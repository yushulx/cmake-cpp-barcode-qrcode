cmake_minimum_required (VERSION 3.8)
project (main)
MESSAGE( STATUS "PROJECT_NAME: " ${PROJECT_NAME} )

# Check platforms
if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
endif()

# Set RPATH
SET(CMAKE_CXX_FLAGS "-std=c++11 -O3 -Wl,-rpath=$ORIGIN")
SET(CMAKE_INSTALL_RPATH "$ORIGIN")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Add search path for include and lib files
if(CMAKE_SYSTEM_PROCESSOR STREQUAL armv7l OR ARM32_BUILD)
    MESSAGE( STATUS "Link directory: ${PROJECT_SOURCE_DIR}/../../../platforms/arm32/" )
    link_directories("${PROJECT_SOURCE_DIR}/../../../platforms/arm32/") 
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL aarch64) 
    MESSAGE( STATUS "Link directory: ${PROJECT_SOURCE_DIR}/../../../platforms/aarch64/" )
    link_directories("${PROJECT_SOURCE_DIR}/../../../platforms/aarch64/") 
endif()
find_package(OpenCV REQUIRED)
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/../../../include/")

# Add the executable
add_executable(main ssd1306_i2c.c main.cxx)
target_link_libraries (main "DynamsoftBarcodeReader" pthread ${OpenCV_LIBS} wiringPi)

add_custom_command(TARGET main POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/../../../platforms/aarch64/"      
        $<TARGET_FILE_DIR:main>)

# Set installation directory
install (DIRECTORY  "${PROJECT_SOURCE_DIR}/../../../platforms/aarch64/" DESTINATION lib)
install (TARGETS main DESTINATION bin)
