#pragma once

#include <fstream>
#include <string>
#include <windows.h>

namespace IO
{
    inline std::wstring Open(const wchar_t* filter)
    {
        OPENFILENAME ofn;
        wchar_t buffer[MAX_PATH] = {0};
        HANDLE hf;

        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = nullptr;
        ofn.lpstrFile = buffer;
        ofn.nMaxFile = MAX_PATH;
        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = nullptr;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = nullptr;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (GetOpenFileName(&ofn)==TRUE)
        {
            return buffer;
        }

        return {};
    }

    inline std::wstring OpenJPG()
    {
        return Open(L"JPG files *.JPG\0");
    }

    inline void WriteBufferToFile(const std::string& filename, const std::string& buffer)
    {
        std::ofstream file(filename, std::ios::out | std::ios::binary);
        if (!file)
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        file.write(buffer.data(), static_cast<long long>(buffer.size()));
    }
}
