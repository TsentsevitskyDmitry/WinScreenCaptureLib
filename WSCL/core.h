#pragma once

#include <memory>

#include "D3D9ScreenCapture.h"


namespace WSCL
{
    enum class CaptureType
    {
        D3D9
    };

    std::unique_ptr<ScreenCapture> CreateCapture(CaptureType type, void* windowHandle)  __attribute__((unused));
    std::unique_ptr<ScreenCapture> CreateCapture(CaptureType type, void* windowHandle = nullptr)
    {
        switch (type)
        {
        case CaptureType::D3D9:
            return std::make_unique<D3D9ScreenCapture>(windowHandle);
        }
    }
}
