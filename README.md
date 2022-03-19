# WinScreenCaptureLib
Windows Screen Capture Library

## Example
````cpp
#include <opencv2/highgui.hpp>
#include <iostream>

#include "WSCL/ScreenCapture.h"

int main()
{
    auto capture = WSCL::CreateCapture(WSCL::CaptureType::D3D9);

    double fps = capture->bench();
    std::cout << "fps: " << fps << std::endl;

    cv::Mat img;
    while(1)
    {
        capture->get(img);
        cv::imshow("screen", img);
        cv::waitKey(1);
    }
}

````
