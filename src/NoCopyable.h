#pragma once

class NoCopyable
{
public:
    NoCopyable(const NoCopyable&) = delete;
    void operator=(const NoCopyable&) = delete;
    NoCopyable() = default;
    ~NoCopyable() = default;
};