# Building C/C++ Barcode Reader with CMake

Version 8.0

## Requirements
- [Visual Studio](https://www.visualstudio.com/downloads/)
- [CMake](https://cmake.org/download/)
- [Dynamsoft Barcode Reader v8.0](https://www.dynamsoft.com/barcode-reader/downloads) (Windows x86/x64, Linux x64, macOS x64 and Raspberry Pi ARMv7)

## License
Get a [trial license](https://www.dynamsoft.com/customer/license/trialLicense) and set the license key in `BarcodeReader.cxx`:

```cpp
reader.InitLicense("LICENSE-KEY");
```

## Contact Us
https://www.dynamsoft.com/Company/Contact.aspx

## Windows
1. Copy `DBRx86.lib/DBRx64.lib` to `platforms\win\lib` and copy `DynamsoftBarcodeReaderx86.dll/DynamsoftBarcodeReaderx64.dll` to `platforms\win\bin` folder.
2. Create a **build** folder:
    ```
    mkdir build
    cd build
    ```
3. Configure and build the project:
    ```bash
    // x86
    cmake -DCMAKE_GENERATOR_PLATFORM=x86 ..

    // x64
    cmake -DCMAKE_GENERATOR_PLATFORM=x64 ..
    
    cmake --build . --config release
    ```
6. Run the app:
    ```
    Release\BarcodeReader [image-file] [optional: license-file] [optional: template-file]
    ```

## Linux and Raspberry Pi OS
1. Install **CMake**:
    ```bash
    sudo apt-get install cmake
    ```
2. Copy **libDynamsoftBarcodeReader.so** to **platforms\linux**.
3. Create a **build** folder:
    ```
    mkdir build
    cd build
    ```
4. Configure and build the project:
    ```bash
    cmake ..
    cmake --build . --config release 
    ```
5. Run the app:
    ```
    ./BarcodeReader [image-file] [optional: license-file] [optional: template-file]
    ```

## macOS
1. Install **CMake**:
    ```bash
    brew install cmake
    ```
2. Copy **libDynamsoftBarcodeReader.dylib** to **platforms\macos**.
3. Create a **build** folder:

    ```
    mkdir build
    cd build
    ```

4. Configure and build the project:

    ```bash
    cmake ..
    cmake --build . --config release 
    ```

5. Run the app:

    ```
    ./BarcodeReader [image-file] [optional: license-file] [optional: template-file]
    ```

## Screenshot

![Raspberry Pi Barcode Reader](https://www.codepool.biz/wp-content/uploads/2016/03/rpi_dbr_result.png)

## Reference
* https://cmake.org/cmake-tutorial/
* https://cmake.org/Wiki/CMake_Useful_Variables
* https://stackoverflow.com/questions/10671916/how-to-copy-dll-files-into-the-same-folder-as-the-executable-using-cmake
* https://cmake.org/Wiki/CMake_RPATH_handling

## Blog
* [CMake: Build C++ Project for Windows, Linux and macOS](http://www.codepool.biz/cmake-cc-windows-linux-macos.html)
* [My First C/C++ App Built with CMake on Windows](http://www.codepool.biz/cc-barcode-app-cmake-windows.html)
