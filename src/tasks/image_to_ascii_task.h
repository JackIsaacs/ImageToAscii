#pragma once

#include <vector>

#include "threaded_task.h"
#include "../base_types.h"


class ImageToAsciiTask final : public ThreadedTask
{
public:
    ImageToAsciiTask(UINT width, const std::vector<BYTE>& pixels, float imagePower)
        : m_width(width),
          m_pixels(pixels),
          m_imagePower(imagePower)
    {
    }

    const std::string& GetOutputBuffer() const;

private:
    void Task() override;

    UINT m_width = 0;
    std::vector<BYTE> m_pixels;
    float m_imagePower = 1.f;

    std::string m_outputBuffer;
};
