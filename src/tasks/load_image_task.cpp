#include "load_image_task.h"

#include <iostream>
#include <__msvc_ostream.hpp>

#include "../util/image_loader.hpp"

const ImageInfo& LoadImageTask::GetImageInfo() const
{
    return m_imageInfo;
}

void LoadImageTask::Task()
{
    UINT w, h;
    std::vector<BYTE> pixels;
    HRESULT hr = ImageLoader::LoadImageToPixels(m_fileName.c_str(), w, h, pixels);

    if (FAILED(hr))
    {
        std::cout << "LoadImageToPixels failed" << '\n';
        m_exitCode = TASK_ERROR;
    }
    else
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_imageInfo = ImageInfo(w, h, pixels);
    }

    ThreadedTask::Task();
}
