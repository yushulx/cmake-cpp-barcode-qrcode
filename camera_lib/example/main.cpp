#include <iostream>
#include "camera_lib.h"

int main()
{
    if (open_camera(0) == 0)
    {
        std::cout << "Camera opened successfully." << std::endl;
        while (true)
        {
            ImageData frame = get_frame();
            if (frame.data)
            {
                draw_line(&frame, 50, 50, 200, 200, 2, 255, 0, 0);
                draw_line(&frame, 50, 200, 200, 50, 2, 0, 255, 0);
                draw_text(&frame, "Hello, OpenCV!", 50, 50, 1, 2, 0, 255, 0);

                display_image(&frame);
                if (wait_key(30) >= 0)
                { // Add a delay and check for key press
                    release_image(&frame);
                    break; // Exit the loop if any key is pressed
                }
                release_image(&frame);
            }
        }
        close_camera();
    }
    else
    {
        std::cerr << "Failed to open camera." << std::endl;
    }
    return 0;
}
