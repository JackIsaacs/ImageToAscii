#pragma once

#include <string>
#include <vector>

#include "threaded_task.h"
#include "../base_types.h"

struct ImageInfo
{
    ImageInfo() = default;

    ImageInfo(UINT w, UINT h, const std::vector<BYTE>& pixels)
        : w(w),
          h(h),
          pixels(pixels)
    {
    }

    UINT w,h = 0;
    std::vector<BYTE> pixels;
};

class LoadImageTask final : public ThreadedTask
{
public:
    explicit LoadImageTask(std::wstring fileName)
        : m_fileName(std::move(fileName))
    {
    }
    
    const ImageInfo& GetImageInfo() const;
    
private:
    void Task() override;
    
    std::wstring m_fileName;
    ImageInfo m_imageInfo = ImageInfo();
};
