#pragma once

namespace cv
{
    class Mat;
}

namespace WSCL
{
    class ScreenCapture
    {
    public:
        ScreenCapture(void* windowHandle) {m_windowHandle = windowHandle;}
        virtual ~ScreenCapture() {}

        virtual void get(cv::Mat &img) = 0;

        virtual double bench();

    protected:
        void* m_windowHandle;
    };
}
