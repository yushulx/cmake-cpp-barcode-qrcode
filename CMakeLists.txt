cmake_minimum_required (VERSION 2.6)
project (BarcodeReader)
# The version number.
set (BarcodeReader_VERSION_MAJOR 1)
set (BarcodeReader_VERSION_MINOR 0)
# Check platforms
if (CMAKE_HOST_WIN32)
    set(WIN32 1)
endif()

# Configure a header file to pass some of the CMake settings
# to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/BarcodeReaderConfig.h.in"
    "${PROJECT_BINARY_DIR}/BarcodeReaderConfig.h"
)

# Add search path for include and lib files
if(WIN32)
    link_directories("${PROJECT_SOURCE_DIR}/platforms/win") 
endif()
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/include")

# Add the executable
add_executable(BarcodeReader BarcodeReader.cxx)
target_link_libraries (BarcodeReader "DBRx86")

if(WIN32)
    # Copy DLL files to output directory
    add_custom_command(TARGET BarcodeReader POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/platforms/win/DynamsoftBarcodeReaderx86.dll"              
    $<TARGET_FILE_DIR:BarcodeReader>)
endif()

# Set installation directory
if(WIN32)
    set(CMAKE_INSTALL_PREFIX "f:/barcodereader")
    install (FILES "${PROJECT_SOURCE_DIR}/platforms/win/DynamsoftBarcodeReaderx86.dll" DESTINATION bin)
endif()

install (TARGETS BarcodeReader DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/BarcodeReaderConfig.h" DESTINATION include)
install (DIRECTORY "${PROJECT_SOURCE_DIR}/include" DESTINATION include)

# Use CTest
include(CTest)
add_test (BarcodeReaderRuns BarcodeReader)
