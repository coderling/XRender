
//一些复杂的函数定义

#include <math.h>
#include "Vector3.h"
#include "MathUtil.h"

const Vector3 kZeroVector(0.0f, 0.0f, 0.0f);

//加上适当的2PI倍数，将角(弧)度限制在[-pi, pi]之间
float wrapPI(float theta)
{
    theta += kPI;
    theta -= floor(theta * k1Over2PI) * k2PI;
    theta -= kPI;
    return theta;
}


//Acos反三角，边界检测，是返回值在0-pi之间
float safeAcos(float x)
{
    if(x <= -1.0f)
    {
        return kPI;
    }

    if(x >= 1.0f)
    {
        return 0.0f;
    }

    return acos(x);
}