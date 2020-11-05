#include "Mathf.h"
#include <math.h>

constexpr double Mathf::_PI;
constexpr float Mathf::Deg2Rad;
constexpr float Mathf::PI;
constexpr float Mathf::Rad2Deg;

float Mathf::Atan2(const float& x, const float& y)
{
    return atan2(x, y);
}

float Mathf::Abs(const float& f)
{
    if(f < 0.0f)
        return (f * -1.0f);
    return f;
}

float Mathf::Lerp(const float& a, const float& b, float t)
{
    t = Clamp(t, 0.0f, 1.0f);
    return a + ((b-a) * t);
}

float Mathf::InverseLerp(const float& a, const float& b, const float& value)
{
    return (value - a) / (b - a);
}

float Mathf::Min(const float& a, const float& b)
{
    if(a > b)
        return b;
    return a;
}

float Mathf::Max(const float& a, const float& b)
{
    if(a > b)
        return a;
    return b;
}

float Mathf::Asin(const float& x)
{
    return asin(x);
}

float Mathf::Sin(const float& x)
{
    return sinf(x);
}

float Mathf::Cos(const float& x)
{
    return cosf(x);
}

float Mathf::Acos(const float& x)
{
    return acos(x);
}

float Mathf::Sqrt(const float& x)
{
    return sqrt(x);
}

float Mathf::Clamp(float& value, const float& min, const float& max)
{
    if(value > max)
        value = max;
    if(value < min)
        value = min;
    return value;           
}