cmake_minimum_required(VERSION 3.10)
project(camera_example)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
# Create the executable
add_executable(camera_example main.cpp)
target_include_directories(camera_example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(camera_example camera_lib)

add_custom_command(TARGET camera_example POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:camera_lib> $<TARGET_FILE_DIR:camera_example>)

# Find all DLL files in the specified directory
file(GLOB DLL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../lib/*.dll")

# Copy the DLL files to the executable directory
foreach(DLL_FILE ${DLL_FILES})
    add_custom_command(TARGET camera_example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DLL_FILE}
        $<TARGET_FILE_DIR:camera_example>)
endforeach()