#include "camera_lib.h"
#include <opencv2/opencv.hpp>

static cv::VideoCapture cap;

int open_camera(int camera_index)
{
    cap.open(camera_index);
    return cap.isOpened() ? 0 : -1;
}

void close_camera()
{
    if (cap.isOpened())
    {
        cap.release();
    }
}

ImageData get_frame()
{
    ImageData image = {0, 0, 0, PIXEL_FORMAT_BGR, nullptr};
    if (cap.isOpened())
    {
        cv::Mat frame;
        cap >> frame;
        if (!frame.empty())
        {
            image.width = frame.cols;
            image.height = frame.rows;
            image.stride = frame.step;
            image.pixel_format = frame.channels() == 3 ? PIXEL_FORMAT_BGR : PIXEL_FORMAT_GRAY;
            size_t data_size = frame.total() * frame.elemSize();
            image.data = new uint8_t[data_size];
            std::memcpy(image.data, frame.data, data_size);
        }
    }
    return image;
}

void release_image(ImageData *image)
{
    if (image->data)
    {
        delete[] image->data;
        image->data = nullptr;
    }
}

void display_image(const ImageData *image)
{
    if (image && image->data)
    {
        int type = image->pixel_format == PIXEL_FORMAT_BGR ? CV_8UC3 : CV_8UC1;
        cv::Mat frame(image->height, image->width, type, image->data, image->stride);
        cv::imshow("Frame", frame);
    }
}

void draw_line(ImageData *image, int x1, int y1, int x2, int y2, int thickness, int r, int g, int b)
{
    if (image && image->data)
    {
        int type = image->pixel_format == PIXEL_FORMAT_BGR ? CV_8UC3 : CV_8UC1;
        cv::Mat frame(image->height, image->width, type, image->data, image->stride);
        cv::line(frame, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(b, g, r), thickness);
        std::memcpy(image->data, frame.data, frame.total() * frame.elemSize());
    }
}

void draw_text(ImageData *image, const char *text, int x, int y, int font_scale, int thickness, int r, int g, int b)
{
    if (image && image->data)
    {
        int type = image->pixel_format == PIXEL_FORMAT_BGR ? CV_8UC3 : CV_8UC1;
        cv::Mat frame(image->height, image->width, type, image->data, image->stride);
        cv::putText(frame, text, cv::Point(x, y), cv::FONT_HERSHEY_SIMPLEX, font_scale, cv::Scalar(b, g, r), thickness);
        std::memcpy(image->data, frame.data, frame.total() * frame.elemSize());
    }
}

int wait_key(int delay)
{
    return cv::waitKey(delay);
}
