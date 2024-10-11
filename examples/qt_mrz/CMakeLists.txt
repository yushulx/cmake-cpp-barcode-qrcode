cmake_minimum_required(VERSION 3.5)

project(MRZRecognizer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_HOST_WIN32)
    link_directories("${PROJECT_SOURCE_DIR}/platform/windows/lib/") 
elseif(CMAKE_HOST_UNIX)
    link_directories("${PROJECT_SOURCE_DIR}/platform/linux/")
endif()
include_directories("${PROJECT_SOURCE_DIR}/include/")

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5MultimediaWidgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        myvideosurface.h
        myvideosurface.cpp
        work.h
        work.cpp
        mrzinfo.h
        mrzinfo.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

if (CMAKE_HOST_WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::MultimediaWidgets "DynamsoftLabelRecognizerx64")    
elseif(CMAKE_HOST_UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::MultimediaWidgets "DynamsoftLabelRecognizer")
endif()

# Copy DLLs
if(CMAKE_HOST_WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/platform/windows/bin/"      
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

# Copy template
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/template/"      
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# Copy model files
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/model"      
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/model)
