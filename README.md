# Building C/C++ Barcode Reader with CMake

## Windows
### Installation
* [Visual Studio Community 2017](https://www.visualstudio.com/downloads/)
* [cmake-3.9.5-win64-x64.msi](https://cmake.org/files/v3.9/cmake-3.9.5-win64-x64.msi)
* [Dynamsoft Barcode Reader 5.2 for Windows](https://www.dynamsoft.com/Downloads/Dynamic-Barcode-Reader-Download.aspx)

### Steps
1. Copy **Barcode Reader 5.2\Components\C_C++\Lib\DBRx86.lib** and **Barcode Reader 5.2\Components\C_C++\Redist\DynamsoftBarcodeReaderx86.dll** to **platforms\win** folder.
2. Create a **build** folder:
    ```
    mkdir build
    cd build
    ```
3. Edit **CMakeLists.txt** to replace the installation path with yours:
    ```
    set(CMAKE_INSTALL_PREFIX "f:/barcodereader")
    ```
4. Generate project configuration files:
    ```
    cmake ..
    ```
5. Build and install the project:
    ```
    cmake --build . --target install
    ```
6. Run the app:
    ```
    cd f:\barcodereader\bin
    BarcodeReader.exe [barcode image file]
    ```

### Screenshot

![build barcode reader with cmake](images/screenshot.png)



## Reference
* https://cmake.org/cmake-tutorial/
* https://cmake.org/Wiki/CMake_Useful_Variables
* https://stackoverflow.com/questions/10671916/how-to-copy-dll-files-into-the-same-folder-as-the-executable-using-cmake