#ifndef MATHF_HPP
#define MATHF_HPP

namespace LinuxForms
{
    class Mathf
    {
    public:
        static constexpr double _PI = 3.14159265359;
        static constexpr float Deg2Rad = (float)(_PI / 180.0);        
        static constexpr float PI = (float)_PI;
        static constexpr float Rad2Deg = (float)(180.0 / _PI);
        
        static float Atan2(const float& x, const float& y);
        static float Abs(const float& f);
        static float Lerp(const float& a, const float& b, float t);
        static float InverseLerp(const float& a, const float& b, const float& value);
        static float Min(const float& a, const float& b);
        static float Max(const float& a, const float& b);
        static float Slerp(const float& a, const float& b, const float& t);
        static float Asin(const float& x);
        static float Sin(const float& x);
        static float Cos(const float& x);
        static float Acos(const float& x);
        static float Sqrt(const float& x);
        static float Clamp(float& value, const float& min, const float& max);
    };
}
#endif