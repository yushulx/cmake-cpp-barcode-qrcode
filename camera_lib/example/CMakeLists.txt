cmake_minimum_required(VERSION 3.10)
project(camera_example)

if(WIN32)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/windows)
    file(GLOB DLL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../lib/windows/*.dll")
elseif(UNIX)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/linux)
endif()

# Create the executable
add_executable(camera_example main.cpp)
target_include_directories(camera_example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(camera_example camera_lib)

if(WIN32)
    add_custom_command(TARGET camera_example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:camera_lib> $<TARGET_FILE_DIR:camera_example>)

    # Copy the DLL files to the executable directory
    foreach(DLL_FILE ${DLL_FILES})
        add_custom_command(TARGET camera_example POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${DLL_FILE}
            $<TARGET_FILE_DIR:camera_example>)
    endforeach()
endif()

if(UNIX)
    add_custom_command(TARGET camera_example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:camera_lib> $<TARGET_FILE_DIR:camera_example>)
endif()