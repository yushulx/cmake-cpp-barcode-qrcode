#ifndef CAMERA_LIB_H
#define CAMERA_LIB_H

#ifdef _WIN32
#ifdef CAMERA_LIB_EXPORTS
#define CAMERA_LIB_API __declspec(dllexport)
#else
#define CAMERA_LIB_API __declspec(dllimport)
#endif
#else
#define CAMERA_LIB_API
#endif

#include <cstdint>

enum PixelFormat
{
    PIXEL_FORMAT_BGR,
    PIXEL_FORMAT_GRAY
};

extern "C"
{
    typedef struct
    {
        int width;
        int height;
        int stride;
        PixelFormat pixel_format;
        uint8_t *data;
    } ImageData;

    CAMERA_LIB_API int open_camera(int camera_index);
    CAMERA_LIB_API void close_camera();
    CAMERA_LIB_API ImageData get_frame();
    CAMERA_LIB_API void release_image(ImageData *image);
    CAMERA_LIB_API void display_image(const char *name, const ImageData *image);
    CAMERA_LIB_API void draw_line(ImageData *image, int x1, int y1, int x2, int y2, int thickness, int r, int g, int b);
    CAMERA_LIB_API void draw_text(ImageData *image, const char *text, int x, int y, int font_scale, int thickness, int r, int g, int b);
    CAMERA_LIB_API int wait_key(int delay);
}

#endif // CAMERA_LIB_H
