#include "cli_app.h"

#include "../tasks/image_to_ascii_task.h"
#include "../tasks/load_image_task.h"
#include "../util/image_manipulation.hpp"
#include "../util/io.hpp"

void CLIApp::Start() const
{
    const auto filePath = IO::OpenJPG();
    std::wcout << filePath << "\n";

    if (filePath.empty())
    {
        std::cout << "Filepath is empty" << "\n";
        return;
    }
    
    LoadImageTask loadImageTask(filePath);
    loadImageTask.Start();
    
    if (loadImageTask.WaitForThread() == TASK_ERROR)
    {
        return;
    }

    std::cout << "LoadImageTask took " << loadImageTask.GetDuration() << "s!" << "\n";
    
    auto image_info = loadImageTask.GetImageInfo();
    std::cout << "width: " << image_info.w << " height: " << image_info.h << " pixel count: " << image_info.pixels.size() << "\n";

    ImageToAsciiTask imageToAsciiTask(image_info.w, image_info.pixels, 1.0f);
    imageToAsciiTask.Start();
    
    if (imageToAsciiTask.WaitForThread() == TASK_ERROR)
    {
        return;
    }
    
    std::cout << "ImageToAsciiTask took " << imageToAsciiTask.GetDuration() << "s!" << "\n";

    IO::WriteBufferToFile("output\\output.txt", imageToAsciiTask.GetOutputBuffer());
}
