#pragma once

#include <string>
#include <vector>

#include "threaded_task.h"

typedef unsigned int UINT;
typedef unsigned char BYTE;

struct ImageInfo
{
    ImageInfo() = default;

    ImageInfo(UINT w, UINT h, const std::vector<BYTE>& pixels)
        : w(w),
          h(h),
          pixels(pixels)
    {
    }

    UINT w,h;
    std::vector<BYTE> pixels;
};

class LoadImageThreadedTask final : public ThreadedTask
{
public:
    explicit LoadImageThreadedTask(std::wstring m_file_name)
        : m_fileName(std::move(m_file_name))
    {
    }
    
    const ImageInfo& GetImageInfo() const;
    
private:
    void Task() override;
    
    std::wstring m_fileName;
    ImageInfo m_imageInfo = ImageInfo();
};
