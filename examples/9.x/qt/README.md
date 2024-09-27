# Qt Desktop Barcode Reader
A desktop barcode reader app built with [Dynamsoft C++ Barcode SDK](https://www.dynamsoft.com/barcode-reader/overview/) and [Qt](https://www.qt.io/).

## Prerequisites
- Get a [trial license](https://www.dynamsoft.com/customer/license/trialLicense/?product=dcv&package=cross-platform) to make the barcode recognition work.
- Qt
  - [Windows](https://www.qt.io/download)
  - Linux
    
    ```bash
    sudo apt-get install qt5-default
    ```

## Getting Started

![Qt desktop barcode reader](https://www.dynamsoft.com/codepool/img/2021/08/barcode-scanner-webcam-qcamera.png)

- **Windows**

    1. Add `C:\Qt\5.15.2\mingw81_64\bin` and `C:\Qt\Tools\mingw1310_64\bin` to the system path.
    2. Create a system variable `Qt5_DIR` with the path `C:\Qt\5.15.2`.
    3. Build and run the Qt barcode reader:
    
        ```bash
        mkdir build
        cd build
        cmake -G "MinGW Makefiles" ..
        cmake --build .
        .\BarcodeReader.exe
        ```

- **Linux**
    1. Build and run the Qt barcode reader:
        ```bash
        mkdir build
        cd build
        cmake ..
        cmake --build .
        ./BarcodeReader
        ```
 
## Blog
- [How to Develop a Desktop GUI Barcode Reader with Qt and C/C++](https://www.dynamsoft.com/codepool/qt-desktop-barcode-reader.html)
- [How to Build a Desktop Barcode Scanner with Webcam Support Using Qt QCamera](https://www.dynamsoft.com/codepool/barcode-scanner-webcam-qt-qcamera.html)
