cmake_minimum_required (VERSION 2.6)
project (BarcodeReader)
MESSAGE( STATUS "PROJECT_NAME: " ${PROJECT_NAME} )

# The version number.
set(BarcodeReader_VERSION_MAJOR 1)
set(BarcodeReader_VERSION_MINOR 0)

# Check platforms
if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
endif()

# Set RPATH
if(WINDOWS)
else()
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
    MESSAGE( STATUS "CMAKE_INSTALL_RPATH: " "${CMAKE_INSTALL_PREFIX}/lib" )
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

# Configure a header file to pass some of the CMake settings
# to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/BarcodeReaderConfig.h.in"
    "${PROJECT_BINARY_DIR}/BarcodeReaderConfig.h"
)

# Add search path for include and lib files
if(WINDOWS)
    link_directories("${PROJECT_SOURCE_DIR}/platforms/win") 
elseif(LINUX)
    link_directories("${PROJECT_SOURCE_DIR}/platforms/linux") 
elseif(MACOS)
    link_directories("${PROJECT_SOURCE_DIR}/platforms/macos") 
endif()
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/include")

# Add the executable
add_executable(BarcodeReader BarcodeReader.cxx)
if(WINDOWS)
    if(CMAKE_CL_64)
        target_link_libraries (BarcodeReader "DBRx64")
    else()
        target_link_libraries (BarcodeReader "DBRx86")
    endif()
else()
    target_link_libraries (BarcodeReader "DynamsoftBarcodeReader")
endif()

if(WINDOWS)
    # Copy DLL files to output directory
    if(CMAKE_CL_64)
        add_custom_command(TARGET BarcodeReader POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/platforms/win/DynamsoftBarcodeReaderx64.dll"              
        $<TARGET_FILE_DIR:BarcodeReader>)
    else()
        add_custom_command(TARGET BarcodeReader POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/platforms/win/DynamsoftBarcodeReaderx86.dll"              
        $<TARGET_FILE_DIR:BarcodeReader>)
    endif()
endif()

# Set installation directory
if(WINDOWS)
    set(CMAKE_INSTALL_PREFIX "e:/${PROJECT_NAME}")
    if(CMAKE_CL_64)
    install (FILES "${PROJECT_SOURCE_DIR}/platforms/win/DynamsoftBarcodeReaderx64.dll" DESTINATION bin)
    else()
    install (FILES "${PROJECT_SOURCE_DIR}/platforms/win/DynamsoftBarcodeReaderx86.dll" DESTINATION bin)
    endif()
elseif(LINUX)
    install (FILES "${PROJECT_SOURCE_DIR}/platforms/linux/libDynamsoftBarcodeReader.so" DESTINATION lib)
elseif(MACOS)
    install (FILES "${PROJECT_SOURCE_DIR}/platforms/macos/libDynamsoftBarcodeReader.dylib" DESTINATION lib)
endif()

install (TARGETS BarcodeReader DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/BarcodeReaderConfig.h" DESTINATION include)
install (DIRECTORY "${PROJECT_SOURCE_DIR}/include" DESTINATION include)

# Use CTest
include(CTest)
add_test (BarcodeReaderRuns BarcodeReader)
