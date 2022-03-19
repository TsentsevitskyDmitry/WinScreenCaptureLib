#include <opencv2/core.hpp>
#include <chrono>

#include "ScreenCapture.h"


namespace WSCL
{
    double ScreenCapture::bench()
    {
        int N = 10;
        cv::Mat img;

        auto start = std::chrono::steady_clock::now();

        for(int i = 0; i < N; ++i)
            get(img);

        auto end = std::chrono::steady_clock::now();
        long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        return 1000.0 * N / static_cast<double>(ms);
    }
}
