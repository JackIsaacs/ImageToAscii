#pragma once
#include <string>

typedef unsigned int UINT;
typedef unsigned char BYTE;

namespace ImageManipulation
{
    inline char GetAsciiForPixel(BYTE r, BYTE g, BYTE b, BYTE a, float power = 1.0f)
    {
        const int sum = r + g + b + a;
        const float percent = pow(static_cast<float>(sum) / (255.0f * 4.0f), power);

        const std::string gradient = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:\",^`'.";
        const size_t index = static_cast<size_t>(percent * (gradient.size() - 1));
        char asciiChar = gradient[index];
    
        return asciiChar;
    }

    inline std::string PixelBufferToAscii(const std::vector<BYTE>& bytes, UINT imageWidth, float power = 1.f)
    {
        UINT stride = 4;
        const size_t pixelCount = bytes.size();
        if (pixelCount % 4 == 0)
        {
            stride = 4;
        }
        else if (pixelCount % 3 == 0)
        {
            stride = 3;
        }

        // How many strides it takes to cross the width of the image, so we can make a new line in the buffer
        const UINT imageStrideWidth = imageWidth * stride;

        std::string buffer;

        UINT currentStrideWidth = 0;
        for (UINT i = 0; i < bytes.size(); i += stride)
        {
            BYTE r = bytes[i];
            BYTE g = bytes[i + 1];
            BYTE b = bytes[i + 2];
            BYTE a = (stride == 4) ? bytes[i + 3] : 255;

            buffer += GetAsciiForPixel(r, g, b, a, power);

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
