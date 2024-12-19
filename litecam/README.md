# LiteCam

LiteCam is a lightweight, cross-platform library for capturing RGB frames from cameras and displaying them. Designed with simplicity and ease of integration in mind, LiteCam supports Windows and Linux platforms.

## Features

- Capture RGB frames from video devices.
- Display live frames in a window.
- Draw contours and text directly on the displayed frames.
- Simple API for quick integration.

## Supported Platforms

- **Windows**: Uses Media Foundation for video capture.
- **Linux**: Uses Video4Linux (V4L2) and X11 for video capture and rendering.

## Requirements

- CMake

### Windows
- Visual Studio 2019 or later
- Media Foundation (included with Windows)

### Linux
- GCC or Clang
- Development libraries for:
  - Video4Linux2 (libv4l2)
  - X11 (libX11)

## Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/yushulx/cmake-cpp-barcode-qrcode-mrz.git
    cd litecam
    ```

2. Build the library:

    ```bash
    mkdir build && cd build
    cmake ..
    cmake --build .
    ```

3. Link the library to your project.

## Usage

### Basic Example

```cpp
#include "Camera.h"
#include "CameraPreview.h"

int main()
{
    Camera camera;
    if (!camera.Open(0)) {
        std::cerr << "Failed to open camera." << std::endl;
        return -1;
    }

    CameraWindow window(640, 480, "LiteCam Preview");
    if (!window.Create()) {
        std::cerr << "Failed to create window." << std::endl;
        return -1;
    }

    window.Show();

    while (window.WaitKey('q')) {
        FrameData frame = camera.CaptureFrame();
        if (frame.rgbData) {
            window.ShowFrame(frame.rgbData, frame.width, frame.height);
            camera.ReleaseFrame(frame);
        }
    }

    camera.Release();
    return 0;
}
```

### API Overview

#### Camera

- **`bool Open(int cameraIndex)`**: Opens the camera with the specified index.
- **`FrameData CaptureFrame()`**: Captures a single RGB frame.
- **`void ReleaseFrame(FrameData &frame)`**: Releases the memory allocated for a frame.
- **`void Release()`**: Closes the camera and releases resources.
- **`void saveFrameAsJPEG(const char *filename, const unsigned char *rgbData, int width, int height)`**: Saves the frame as a JPEG image.

#### CameraWindow

- **`bool Create()`**: Initializes and creates a window.
- **`void Show()`**: Displays the window.
- **`bool WaitKey(char key)`**: Waits for user input; returns `false` if the specified key is pressed or the window is closed.
- **`void ShowFrame(const unsigned char *rgbData, int width, int height)`**: Displays an RGB frame.
- **`void DrawContour(const std::vector<std::pair<int, int>> &points)`**: Draws contours on the frame.
- **`void DrawText(const std::string &text, int x, int y, int fontSize, const Color &color)`**: Draws text on the frame.


