# Building C/C++ Barcode Reader with CMake

## SDK Version
[v9.0](https://www.dynamsoft.com/barcode-reader/downloads)

## SDK Activation
Click [here](https://www.dynamsoft.com/customer/license/trialLicense/?product=dbr) to get a trial license.

## Supported Platforms
- Windows x86/x64
- Linux x64/ARM64
- macOS x64 
- Raspberry Pi ARMv7

## Setting License
Set the license key in `BarcodeReader.cxx`:

```cpp
DBR_InitLicense(license, errorMsgBuffer, 512);
```

## Windows
1. Create a **build** folder:
    ```
    mkdir build
    cd build
    ```
2. Configure and build the project:
    ```bash
    // x86
    cmake -DCMAKE_GENERATOR_PLATFORM=x86 ..

    // x64
    cmake -DCMAKE_GENERATOR_PLATFORM=x64 ..
    
    cmake --build . --config release
    ```

    For `MinGW`:
    
    ```bash
    cmake -G "MinGW Makefiles" ..
    ```
3. Run the app:
    ```
    .\Release\BarcodeReader.exe [image-file] [optional: license-file] [optional: template-file]
    ```

## Linux and Raspberry Pi OS
1. Install **CMake**:
    ```bash
    sudo apt-get install cmake
    ```
2. Create a **build** folder:
    ```
    mkdir build
    cd build
    ```
3. Configure and build the project:
    ```bash
    cmake ..
    # cmake -DARM32_BUILD=TRUE ..
    cmake --build . --config release 
    ```
4. Run the app:
    ```
    ./BarcodeReader [image-file] [optional: license-file] [optional: template-file]
    ```

## macOS 
1. Install **CMake**:
    ```bash
    brew install cmake
    ```
2. Create a **build** folder:

    ```
    mkdir build
    cd build
    ```

3. Configure and build the project:

    ```bash
    cmake ..
    cmake --build . --config release 
    ```

4. Run the app:

    ```
    ./BarcodeReader [image-file] [optional: license-file] [optional: template-file]
    ```

## Screenshot

![Raspberry Pi Barcode Reader](https://www.dynamsoft.com/codepool/img/2016/03/rpi_dbr_result.png)

## Reference
* https://cmake.org/cmake/help/latest/guide/tutorial/index.html
* https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/Useful-Variables
* https://stackoverflow.com/questions/10671916/how-to-copy-dll-files-into-the-same-folder-as-the-executable-using-cmake
* https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/RPATH-handling

## Blog
* [CMake: Build C++ Project for Windows, Linux and macOS](https://www.dynamsoft.com/codepool/cmake-cc-windows-linux-macos.html)
* [My First C/C++ App Built with CMake on Windows](https://www.dynamsoft.com/codepool/cc-barcode-app-cmake-windows.html)
