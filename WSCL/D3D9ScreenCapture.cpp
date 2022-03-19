#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include "D3D9ScreenCapture.h"
#define CAPTURE_DERECTX 0x0


namespace WSCL
{
    D3D9ScreenCapture::D3D9ScreenCapture(void *windowHandle)
        : ScreenCapture(windowHandle)
    {
        UINT adapter = D3DADAPTER_DEFAULT;
        D3DPRESENT_PARAMETERS parameters = {};
        D3DLOCKED_RECT rc;
        UINT pitch;

        // init D3D and get screen size
        d3d = Direct3DCreate9(D3D_SDK_VERSION);
        d3d->GetAdapterDisplayMode(adapter, &mode);

        parameters.Windowed = TRUE;
        parameters.BackBufferCount = 1;
        parameters.BackBufferHeight = mode.Height;
        parameters.BackBufferWidth = mode.Width;
        parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
        parameters.hDeviceWindow = nullptr;

        // create device & capture surface
        d3d->CreateDevice(adapter, D3DDEVTYPE_HAL, nullptr, D3DCREATE_HARDWARE_VERTEXPROCESSING , &parameters, &device);

        // device->GetDisplayMode(0,&mode);
        device->CreateOffscreenPlainSurface(mode.Width, mode.Height, D3DFMT_A8R8G8B8, D3DPOOL_SCRATCH, &surface, nullptr);

        // compute the required buffer size
        surface->LockRect(&rc, nullptr, 0);
        pitch = static_cast<UINT>(rc.Pitch);
        surface->UnlockRect();

        // allocate screenshots buffers
        d3dImage = new BYTE[pitch * mode.Height];
    }

    D3D9ScreenCapture::~D3D9ScreenCapture()
    {
        surface->Release();
        device->Release();
        d3d->Release();
        delete[] d3dImage;
    }

    void D3D9ScreenCapture::get(cv::Mat& img)
    {
        // get the data
        device->GetFrontBufferData(0, surface);
        // copy it into our buffers
        D3DLOCKED_RECT rc;
        //  surface->LockRect(&rc, nullptr, 0);
        surface->LockRect(&rc,nullptr,
                           D3DLOCK_NO_DIRTY_UPDATE|
                           D3DLOCK_NOSYSLOCK|D3DLOCK_READONLY);

        // CopyMemory(d3dImage, rc.pBits, rc.Pitch * mode.Height);
        surface->UnlockRect();

        // Convert to opencv
        img = cv::Mat(static_cast<int>(mode.Height), static_cast<int>(mode.Width), CV_8UC4, rc.pBits);
    }
}
