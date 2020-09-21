#include "XTime.h"

#ifdef _MSC_VER
#include <sys/timeb.h>
#else
#include <sys/time.h>
#endif

uint64_t CurrentMillisecs()
{
#ifdef _MSC_VER
    _timeb timebuffer;
    _ftime_s(&timebuffer);
    return timebuffer.time * 1000 + timebuffer.millitm;
#else
#endif
    return 0;
}


XRender::XTime& XRender::XTime::Time()
{
    static XTime timer;
    return timer;
}

XRender::XTime::XTime():
framecount(0), time(0), interval(0), fps(0), millisecs(0), prev_millisecs(0)
{
}

void XRender::XTime::Update()
{
    millisecs = CurrentMillisecs();
    time = millisecs * 1.0f / 1000;
    interval = (millisecs - prev_millisecs) * 1.0f / 1000;
    fps = 1 / interval;
    prev_millisecs = millisecs;
    ++framecount;
}

const uint64_t& XRender::XTime::FrameCount() const
{
    return framecount;
}

const float& XRender::XTime::Now() const
{
    return time;
}

const float& XRender::XTime::Interval() const
{
    return interval;
}

const uint32_t& XRender::XTime::Fps() const
{
    return fps;
}

const uint64_t& XRender::XTime::Millisecs() const
{
    return millisecs;
}