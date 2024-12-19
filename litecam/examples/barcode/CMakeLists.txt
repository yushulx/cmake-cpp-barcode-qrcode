cmake_minimum_required(VERSION 3.10)
project(BarcodeScanner)

if(WIN32)

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../dist/lib/windows/release ${CMAKE_CURRENT_SOURCE_DIR}/../../../examples/10.x/sdk/platforms/win/lib)
    else()
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../dist/lib/windows/debug ${CMAKE_CURRENT_SOURCE_DIR}/../../../examples/10.x/sdk/platforms/win/lib)
    endif()
    
    set(DBR_LIBS "DynamsoftCorex64" "DynamsoftLicensex64" "DynamsoftCaptureVisionRouterx64" "DynamsoftUtilityx64")
elseif(UNIX)
    SET(CMAKE_CXX_FLAGS "-std=c++11 -O3 -Wl,-rpath=$ORIGIN")
    SET(CMAKE_INSTALL_RPATH "$ORIGIN")
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../dist/lib/linux ${CMAKE_CURRENT_SOURCE_DIR}/../../../examples/10.x/sdk/platforms/linux)
    set(DBR_LIBS "DynamsoftCore" "DynamsoftLicense" "DynamsoftCaptureVisionRouter" "DynamsoftUtility" pthread)
endif()

# Create the executable
add_executable(BarcodeScanner main.cpp)
target_include_directories(BarcodeScanner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../dist/include ${CMAKE_CURRENT_SOURCE_DIR}/../../../examples/10.x/sdk/include)
target_link_libraries(BarcodeScanner litecam ${DBR_LIBS})

if(WIN32)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_custom_command(TARGET BarcodeScanner POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/../../dist/lib/windows/release   
        $<TARGET_FILE_DIR:BarcodeScanner>)
    else()
        add_custom_command(TARGET BarcodeScanner POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/../../dist/lib/windows/debug   
        $<TARGET_FILE_DIR:BarcodeScanner>)
    endif()

    add_custom_command(TARGET BarcodeScanner POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../examples/10.x/sdk/platforms/win/bin/      
    $<TARGET_FILE_DIR:BarcodeScanner>)
elseif(UNIX)
    add_custom_command(TARGET BarcodeScanner POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../examples/10.x/sdk/platforms/linux/      
    $<TARGET_FILE_DIR:BarcodeScanner>)
endif()

