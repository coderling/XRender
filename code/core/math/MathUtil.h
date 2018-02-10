#pragma once

#include <math.h>

//PI相关常量
const float kPI = 3.14159265f;
const float k2PI = kPI * 2.0f;
const float kPIOver2 = kPI / 2.0f;
const float k1OverPI = 1.0f / kPI;
const float k1Over2PI = 1.0 / k2PI;

//将角度限制在[-pi, pi] 之间
extern float wrapPI(float theta);

//安全的反三角函数
extern float safeAcos(float x);

//计算角度的sin和cos值
inline void sinCos(float *returnSin, float *returnCos, float theta)
{
    //为了简单实用了标准三角函数，特定平台有优化的地方？？？
    *returnSin = sin(theta);
    *returnCos = cos(theta);
}