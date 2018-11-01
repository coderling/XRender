/*
 * File: RMath.h
 * File Created: Wednesday, 31st October 2018 2:00:06 am
 * Author: coderling (coderling@gmail.com)
 */

#pragma once

typedef unsigned char UInt8;

inline float Lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

inline int Lerp(int a, int b, float t)
{
    return a + (b - a) * t + 0.5;
}

inline UInt8 Lerp(UInt8 a, UInt8 b, float t)
{
    return a + (b - a) * t + 0.5;
}