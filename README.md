# Building C/C++ Barcode Reader with CMake

## License
Get the [trial license](https://www.dynamsoft.com/CustomerPortal/Portal/Triallicense.aspx).

## Windows
### Installation
* [Visual Studio Community](https://www.visualstudio.com/downloads/)
* [cmake-3.9.5-win64-x64.msi](https://cmake.org/files/v3.9/cmake-3.9.5-win64-x64.msi)
* [Dynamsoft Barcode Reader 6.1](https://www.dynamsoft.com/Downloads/Dynamic-Barcode-Reader-Download.aspx).

### Steps
1. Copy **DBRx86.lib/DBRx64.lib** and **DynamsoftBarcodeReaderx86.dll/DynamsoftBarcodeReaderx64.dll** to **platforms\win** folder.
2. Create a **build** folder:

    ```
    mkdir build
    cd build
    ```

3. Generate project configuration files: 

    **Win32**
    ```bash
    cmake ..
    ```

    **Win64**
    ```bash
    cmake -G"Visual Studio 14 2015 Win64" ..
    ```
5. Build the project:

    ```
    cmake --build . 
    ```
6. Run the app:

    ```
    .\Debug\BarcodeReader.exe [barcode image file]
    ```

