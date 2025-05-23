#pragma once

#include <string>
#include <iostream>

#include "../base_types.h"

namespace ImageManipulation
{
    inline char GetAsciiForPixel(const std::vector<BYTE>& pixelColors, float power = 1.0f)
    {
        int sum = 0;
        for (const BYTE pixelColor : pixelColors)
        {
            sum += pixelColor;
        }
        
        const float percent = pow(static_cast<float>(sum) / (255.0f * static_cast<float>(pixelColors.size())), power);

        const std::string gradient = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~i!lI;:\",^`'.";
        const size_t index = static_cast<size_t>(percent * (gradient.size() - 1));
        const char asciiChar = gradient[index];
    
        return asciiChar;
    }

    inline std::string PixelBufferToAscii(const std::vector<BYTE>& bytes, UINT imageWidth, float power = 1.f)
    {
        UINT stride = 4;
        const size_t pixelCount = bytes.size();
        for (UINT potentialStride = 4; potentialStride > 0; --potentialStride)
        {
            if (pixelCount % potentialStride == 0)
            {
                stride = potentialStride;
                break;
            }
        }

        if (stride == 0)
        {
            return {};
        }

        // How many strides it takes to cross the width of the image, so we can make a new line in the buffer
        const UINT imageStrideWidth = imageWidth * stride;

        std::string buffer;

        UINT currentStrideWidth = 0;
        for (UINT i = 0; i < bytes.size(); i += stride)
        {
            std::vector<BYTE> pixelColors;
            pixelColors.reserve(stride);
            
            for (UINT strideIdx = 0; strideIdx < stride; ++strideIdx)
            {
                pixelColors.push_back(bytes[i + strideIdx]);
            }

            buffer += GetAsciiForPixel(pixelColors, power);

            currentStrideWidth += stride;
            if (currentStrideWidth >= imageStrideWidth)
            {
                buffer += "\n";
                currentStrideWidth = 0;
            }
        }

        return buffer;
    }
}
