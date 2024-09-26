cmake_minimum_required(VERSION 3.5)

project(BarcodeReader VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
endif()

if(WINDOWS)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        link_directories("${PROJECT_SOURCE_DIR}/../../../platforms/win/bin/") 
    else()
        link_directories("${PROJECT_SOURCE_DIR}/../../../platforms/win/lib/") 
    endif()
elseif(LINUX)
    if (CMAKE_SYSTEM_PROCESSOR STREQUAL x86_64)
        MESSAGE( STATUS "Link directory: ${PROJECT_SOURCE_DIR}/../../../platforms/linux/" )
        link_directories("${PROJECT_SOURCE_DIR}/../../../platforms/linux/")
    elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL armv7l OR ARM32_BUILD)
        MESSAGE( STATUS "Link directory: ${PROJECT_SOURCE_DIR}/../../../platforms/arm32/" )
        link_directories("${PROJECT_SOURCE_DIR}/../../../platforms/arm32/") 
    elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL aarch64) 
        MESSAGE( STATUS "Link directory: ${PROJECT_SOURCE_DIR}/../../../platforms/aarch64/" )
        link_directories("${PROJECT_SOURCE_DIR}/../../../platforms/aarch64/") 
    endif()
elseif(MACOS)
    MESSAGE( STATUS "Link directory: ${PROJECT_SOURCE_DIR}/../../../platforms/macos/" )
    link_directories("${PROJECT_SOURCE_DIR}/../../../platforms/macos/") 
endif()
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/../../../include/")

find_package(Qt5 COMPONENTS Widgets MultimediaWidgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        myvideosurface.h
        myvideosurface.cpp
        work.h
        work.cpp
        barcodeinfo.h
        barcodeinfo.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

if(WINDOWS)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries (${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::MultimediaWidgets "DynamsoftBarcodeReaderx64")
    else()
        if(CMAKE_CL_64)
            target_link_libraries (${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::MultimediaWidgets "DBRx64")
        else()
            target_link_libraries (${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::MultimediaWidgets "DBRx86")
        endif()
    endif()
else()
    target_link_libraries (${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::MultimediaWidgets "DynamsoftBarcodeReader" pthread)
endif()

if(CMAKE_HOST_WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/../../../platforms/win/bin/"     
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()