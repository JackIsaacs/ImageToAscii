#pragma once

#include <vector>
#include <wincodec.h>

namespace ImageLoader
{
    inline HRESULT LoadImageToPixels(const wchar_t* filename, UINT& width, UINT& height, std::vector<BYTE>& pixels)
    {
        CoInitialize(nullptr);

        IWICImagingFactory* factory = nullptr;
        IWICBitmapDecoder* decoder = nullptr;
        IWICBitmapFrameDecode* frame = nullptr;
        IWICFormatConverter* converter = nullptr;

        HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&factory));

        if (FAILED(hr))
        {
            return hr;
        }
        
        hr = factory->CreateDecoderFromFilename(filename, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);
        if (FAILED(hr))
        {
            factory->Release();
            return hr;
        }

        hr = decoder->GetFrame(0, &frame);
        if (FAILED(hr))
        {
            decoder->Release();
            factory->Release();
            return hr;
        }

        hr = factory->CreateFormatConverter(&converter);
        if (FAILED(hr))
        {
            frame->Release();
            decoder->Release();
            factory->Release();
            return hr;
        }

        hr = converter->Initialize(frame,
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            nullptr,
            0.f,
            WICBitmapPaletteTypeCustom);

        if (FAILED(hr))
        {
            converter->Release();
            frame->Release();
            decoder->Release();
            factory->Release();
            return hr;
        }

        UINT w, h;
        converter->GetSize(&w, &h);
        width = w;
        height = h;
        
        pixels.resize(w * h * 4);

        hr = converter->CopyPixels(nullptr, w * 4, static_cast<UINT>(pixels.size()), pixels.data());

        converter->Release();
        frame->Release();
        decoder->Release();
        factory->Release();
        CoUninitialize();

        return hr;
    }
}