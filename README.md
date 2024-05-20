# Building Barcode and QR Code Reader with C++ and CMake
This repository contains examples demonstrating how to utilize the **Dynamsoft Barcode Reader SDK** to build barcode and QR code detection applications with C++ and CMake on **Windows**, **Linux**, **macOS**, and **Raspberry Pi**.

## Prerequisites
- Obtain a [30-day free trial license](https://www.dynamsoft.com/customer/license/trialLicense/) for Dynamsoft Barcode Reader. Update the following code in `main.cxx`:

    ```cpp
    DBR_InitLicense(license, errorMsgBuffer, 512);
    ```

## Supported Platforms
- Windows x64
- Linux x64/ARM64/ARM32
- macOS x64 (Intel/Apple Silicon)

## How to Build a CMake Project

**Windows**

1. Create a **build** folder:
    
    ```bash
    mkdir build
    cd build
    ```

2. Configure and build the project:
    
    ```bash
    # x86
    cmake -DCMAKE_GENERATOR_PLATFORM=x86 ..

    # x64
    cmake -DCMAKE_GENERATOR_PLATFORM=x64 ..
    
    cmake --build . --config release
    ```

    For `MinGW`:
    
    ```bash
    cmake -G "MinGW Makefiles" ..
    ```

**Linux and Raspberry Pi OS**

1. Install **CMake**:
    
    ```bash
    sudo apt-get install cmake
    ```

2. Create a **build** folder:
    
    ```bash
    mkdir build
    cd build
    ```

3. Configure and build the project:
    ```bash
    cmake ..
    cmake --build . --config release 
    ```

**macOS**
 
1. Install **CMake**:
    
    ```bash
    brew install cmake
    ```

2. Create a **build** folder:

    ```bash
    mkdir build
    cd build
    ```

3. Configure and build the project:

    ```bash
    cmake ..
    cmake --build . --config release 
    ```

## Examples
- [Command Line](./examples/9.x/command_line)
    
    ```bash
    ./main [image-file] [optional: license-file] [optional: template-file]
    ```
        

## Screenshots    

![Raspberry Pi Barcode Reader](https://www.dynamsoft.com/codepool/img/2016/03/rpi_dbr_result.png)

## Blog
- [CMake: Build C++ Project for Windows, Linux and macOS](https://www.dynamsoft.com/codepool/cmake-cc-windows-linux-macos.html)
- [My First C/C++ App Built with CMake on Windows](https://www.dynamsoft.com/codepool/cc-barcode-app-cmake-windows.html)
- [How to Port Visual Studio C++ Project to Linux with CMake](https://www.dynamsoft.com/codepool/port-visual-studio-cpp-linux-cmake.html)
- [Transforming Raspberry Pi 4 into a Barcode Scanner with a C++ App, USB Camera, and OLED Display](https://www.dynamsoft.com/codepool/raspberry-pi-cpp-barcode-reader.html)