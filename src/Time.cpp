#include "Time.h"

XRender::Time& XRender::Time::Timer()
{
    static Time timer;
    return timer;
}

XRender::Time::Time(): framecount(0)
{}


const long long& XRender::Time::GetFrameCount() const
{
    return framecount;
}

void XRender::Time::Update()
{
    ++framecount;
}