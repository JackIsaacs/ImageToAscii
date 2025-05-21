#include "image_to_ascii_task.h"

#include "../util/image_manipulation.hpp"

const std::string& ImageToAsciiTask::GetOutputBuffer() const
{
    return m_outputBuffer;
}

void ImageToAsciiTask::Task()
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_outputBuffer = ImageManipulation::PixelBufferToAscii(m_pixels, m_width, m_imagePower);

        if (m_outputBuffer.empty())
        {
            std::cout << "ImageToAsciiTask failed" << '\n';
            m_exitCode = TASK_ERROR;
        }
    }
    
    ThreadedTask::Task();
}
