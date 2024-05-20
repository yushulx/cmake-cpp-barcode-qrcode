# C/C++ Barcode Reader for Raspberry Pi 4
The sample demonstrates how to build a C/C++ barcode reader app on `Raspberry Pi 4`.

## Prerequisites
- [Raspberry Pi 4](https://category.yahboom.net/products/raspberry-pi-4b) (4GB model)
- [Raspberry Pi RGB Cooling HAT with adjustable fan and OLED display](https://category.yahboom.net/products/rgb-cooling-hat)
- [Micro-HDMI to HDMI cable](https://category.yahboom.net/products/micro-hdmi-to-hdmi-cable)
- [HDMI Female to HDMI Female Coupler Connector](https://www.amazon.com/dp/B06XR9PR5X/ref=vp_d_pb_TIER2_lp_B0789BGXXR_pd?_encoding=UTF8&pd_rd_i=B06XR9PR5X&pd_rd_w=HUIGS&pf_rd_p=b9c8a149-8025-4ee4-a81e-c3b28f174075&pf_rd_r=03c2b5a1-60ef-4151-a487-8da38dcb6eff&pd_rd_r=03c2b5a1-60ef-4151-a487-8da38dcb6eff&pd_rd_wg=Kf0ZM)
- USB Webcam


## Install OpenCV
1. Download OpenCV source code: https://github.com/opencv/opencv/releases
2. Install [required packages](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html): 

    ```bash
    sudo apt install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libjpeg-dev libpng-dev libtiff-dev
    ```
    
3. Build and install OpenCV:
 
    ```
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local -DOPENCV_GENERATE_PKGCONFIG=ON ..
    make -j4
    sudo make install
    ```

## Build and Run
1. Get a [30-day trial license](https://www.dynamsoft.com/customer/license/trialLicense/?product=dbr&source=github) of [Dynamsoft Barcode Reader](https://www.dynamsoft.com/barcode-reader/overview/) and update the following code in `main.cxx`:

    ```cpp
    iRet = reader.InitLicense("LICENSE-KEY");
    ```
    
2. Build and run the barcode reader app on `Raspberry Pi 4`:

    ```
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ./BarcodeReader
    ```
     
    ![Raspberry Pi barcode QR detection](https://www.dynamsoft.com/codepool/wp-content/uploads/2020/06/raspberry-pi-barcode-qr.png)
    
## App Auto Start
1. Create `/home/pi/autostart.sh`:
  
      ```
      #!/bin/sh
      /home/pi/raspberry-pi-cpp-barcode/build/BarcodeReader
      ```
      
2. Change the file permission:
  
      ```
      chmod a+x autostart.sh
      ```
    
3. Create `/home/pi/.config/autostart/autostart.desktop`:
  
      ```
      [Desktop Entry]
      Type=Application
      Exec=sh /home/pi/autostart.sh
      ```
 4. Reboot:
 
    ```
    sudo reboot
    ```
  
## Blog
[How to Build C/C++ Barcode Reader App on Raspberry Pi 4](https://www.dynamsoft.com/codepool/raspberry-pi-cpp-barcode-reader.html)
