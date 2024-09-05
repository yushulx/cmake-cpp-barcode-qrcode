# Desktop Passport MRZ Scanner for Windows and Linux
This C/C++ sample demonstrates how to implement **MRZ (Machine Readable Zone)** recognition using the Dynamsoft Capture Vision SDK.

## Prerequisites
- [CMake](https://cmake.org/download/)
- [OpenCV 4.5.0](https://opencv.org/releases/)
- [Dynamsoft Capture Vision Trial License](https://www.dynamsoft.com/customer/license/trialLicense/?product=dcv&package=cross-platform)


## Getting Started
1. Set the license key in `main.cxx`:

    ```cpp
    iRet = CLicenseManager::InitLicense("LICENSE-KEY", szErrorMsg, 256);
    ```

2. Build and run the application:

    ```
    mkdir build
    cd build
    cmake ..
    # For OpenCV
    # cmake -DCMAKE_GENERATOR_PLATFORM=x64 -DENABLE_OPENCV=TRUE ..
    cmake --build .
    ```
    
    
    
 ## Blog
 [Passport MRZ Recognition with Dynamsoft C++ OCR SDK](https://www.dynamsoft.com/codepool/passport-mrz-recognition-cpp-windows-linux.html)
