#pragma once

#include <stdint.h>

namespace XRender
{
    class XTime final
    {
    public:
	    static XTime& Time();
        XTime();
        void Update();
        const uint64_t& FrameCount() const;
        const float& Now() const;
        const float& Interval() const;
        const uint32_t& Fps() const;
        const uint64_t& Millisecs() const;
    private:
        uint64_t framecount;
        float time;
        float interval;
        int32_t fps;
        uint64_t millisecs;
        uint64_t prev_millisecs;
    };
}