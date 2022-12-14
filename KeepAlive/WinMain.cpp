#include "pch.h"
#include <chrono>
using namespace std::chrono;

using namespace winrt;
using namespace Windows::Foundation;

IAsyncAction DoSomeWorkOnThreadPoolAsync()
{
    co_await winrt::resume_background(); // Return control; resume on thread pool.
    POINT mousePoseition = {};
    INPUT input = {};
    while (1)
    {
        GetCursorPos(&mousePoseition);
        input.mi.mouseData = 0;
        input.mi.time = 0;
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_MOVE ;
        input.mi.dx = 5;
        SendInput(1, &input, sizeof(INPUT));
        co_await 1s;
        input.mi.dx = -5;
        SendInput(1, &input, sizeof(INPUT));
        co_await 30s;
    }
    co_return ;
}

int __stdcall wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    init_apartment(apartment_type::single_threaded);
    DoSomeWorkOnThreadPoolAsync();
    ::MessageBoxW(::GetDesktopWindow(), L"Keep alive enabled", L"Keep alive enabled", MB_OK);
}

