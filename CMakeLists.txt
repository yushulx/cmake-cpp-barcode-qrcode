cmake_minimum_required (VERSION 2.6)
project (BarcodeReader)
MESSAGE( STATUS "PROJECT_NAME: " ${PROJECT_NAME} )

# The version number.
set(BarcodeReader_VERSION_MAJOR 7)
set(BarcodeReader_VERSION_MINOR 4)

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
    link_directories("${PROJECT_SOURCE_DIR}/platforms/win/lib/") 
elseif(LINUX)
    link_directories("${PROJECT_SOURCE_DIR}/platforms/linux/") 
elseif(MACOS)
    link_directories("${PROJECT_SOURCE_DIR}/platforms/macos/") 
endif()
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/include/")

# Add the executable
add_executable(BarcodeReader BarcodeReader.cxx)
if(WINDOWS)
    if(CMAKE_CL_64)
        target_link_libraries (BarcodeReader "DBRx64")
    else()
        target_link_libraries (BarcodeReader "DBRx86")
    endif()
else()
    target_link_libraries (BarcodeReader "DynamsoftBarcodeReader" pthread)
endif()

if(WINDOWS)
    add_custom_command(TARGET BarcodeReader POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/platforms/win/bin/"      
        $<TARGET_FILE_DIR:BarcodeReader>)

endif()

# Set installation directory
if(WINDOWS)
    set(CMAKE_INSTALL_PREFIX "e:/${PROJECT_NAME}")
    install (DIRECTORY  "${PROJECT_SOURCE_DIR}/platforms/win/bin/" DESTINATION bin)
elseif(LINUX)
    install (DIRECTORY  "${PROJECT_SOURCE_DIR}/platforms/linux/" DESTINATION lib)
elseif(MACOS)
    install (DIRECTORY  "${PROJECT_SOURCE_DIR}/platforms/macos/" DESTINATION lib)
endif()

install (TARGETS BarcodeReader DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/BarcodeReaderConfig.h" DESTINATION include)
install (DIRECTORY "${PROJECT_SOURCE_DIR}/include/" DESTINATION include)

# Use CTest
include(CTest)
add_test (BarcodeReaderRuns BarcodeReader)
