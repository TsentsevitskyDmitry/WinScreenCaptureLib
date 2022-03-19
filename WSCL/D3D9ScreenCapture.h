#pragma once

#include <d3d9.h>                 // DirectX 9 header
#pragma comment(lib, "d3d9.lib")  // link to DirectX 9 library

#include "IScreenCapture.h"
#define CAPTURE_DERECTX 0x0


namespace WSCL
{
    class D3D9ScreenCapture : public ScreenCapture
    {
    public:
        D3D9ScreenCapture(void* windowHandle);
        ~D3D9ScreenCapture() override;

        void get(cv::Mat &img) override;

    private:
        // d3d
        IDirect3DDevice9 *device;
        IDirect3DSurface9 *surface;
        D3DDISPLAYMODE mode;
        IDirect3D9 *d3d;
        BYTE* d3dImage;
    };
}
