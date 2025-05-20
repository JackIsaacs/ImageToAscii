#include <iostream>

#include "tasks/load_image_threaded_task.h"
#include "util/image_manipulation.hpp"
#include "util/io.hpp"

int main(int argc, char* argv[])
{
    const auto filePath = IO::OpenJPG();
    std::wcout << filePath << "\n";

    LoadImageThreadedTask task(filePath);
    task.Start();

    while (true)
    {
        if (task.CanJoin())
        {
            std::cout << "LoadImageTask took " << task.GetDuration() << "s!" << "\n";
            break;
        }
    }

    auto image_info = task.GetImageInfo();
    std::cout << "width: " << image_info.w << " height: " << image_info.h << " pixel count: " << image_info.pixels.size() << "\n"; 
    
    auto buffer = ImageManipulation::PixelBufferToAscii(image_info.pixels, image_info.w, 2.f);
    IO::WriteBufferToFile("D://test.txt", buffer);
    
    return 0;
}
