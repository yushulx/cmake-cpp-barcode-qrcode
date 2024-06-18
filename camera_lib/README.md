# Slimmed Down OpenCV for Camera Applications
1. Download the OpenCV source code from the [OpenCV GitHub repository](https://github.com/opencv/opencv).
2. Open a terminal or command prompt, create a build directory, and navigate into it:
    
    ```bash
    mkdir build
    cd build
    ```
3. Run the following CMake command to configure the build, disabling unnecessary components:

    ```bash
    cmake -DBUILD_SHARED_LIBS=ON -DBUILD_opencv_world=OFF -DBUILD_opencv_apps=OFF -DBUILD_opencv_calib3d=OFF -DBUILD_opencv_dnn=OFF -DBUILD_opencv_features2d=OFF -DBUILD_opencv_flann=OFF -DBUILD_opencv_gapi=OFF -DBUILD_opencv_ml=OFF -DBUILD_opencv_objdetect=OFF -DBUILD_opencv_photo=OFF -DBUILD_opencv_stitching=OFF -DBUILD_opencv_video=OFF -DBUILD_TESTS=OFF -DBUILD_PERF_TESTS=OFF -DBUILD_EXAMPLES=OFF -DBUILD_DOCS=OFF ..
    ```

4. Build the OpenCV library:

    ```bash
    cmake --build . --config Release
    ```

5. Copy the library files `opencv_imgproc`, `opencv_core`, `opencv_imgcodecs`, `opencv_videoio`, and `opencv_highgui` to the `lib` directory.
6. Configure `src/CMakeLists.txt` to link against the OpenCV library.
    
    ```cmake
    if(WIN32)
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/windows)
        set(OPENCV_LIBS opencv_core480 opencv_highgui480 opencv_videoio480 opencv_imgproc480)
    elseif(UNIX)
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/linux)
        set(OPENCV_LIBS opencv_core opencv_highgui opencv_videoio opencv_imgproc)
    endif()
    ```
7. Build the camera application:

    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build . --config Release
    ```