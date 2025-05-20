#include "load_image_threaded_task.h"

#include "../util/image_loader.hpp"

const ImageInfo& LoadImageThreadedTask::GetImageInfo() const
{
    return m_imageInfo;
}

void LoadImageThreadedTask::Task()
{
    UINT w, h;
    std::vector<BYTE> pixels;
    ImageLoader::LoadImageToPixels(m_fileName.c_str(), w, h, pixels);

    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_imageInfo = ImageInfo(w, h, pixels);
    }

    ThreadedTask::Task();
}
