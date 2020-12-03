#include "Mathf.h"
#include <math.h>
#include <stdexcept>      // std::invalid_argument

constexpr double LinuxForms::Mathf::_PI;
constexpr float LinuxForms::Mathf::Deg2Rad;
constexpr float LinuxForms::Mathf::PI;
constexpr float LinuxForms::Mathf::Rad2Deg;

float LinuxForms::Mathf::Atan2(const float& x, const float& y)
{
    return atan2(x, y);
}

float LinuxForms::Mathf::Abs(const float& f)
{
    if(f < 0.0f)
        return (f * -1.0f);
    return f;
}

float LinuxForms::Mathf::Lerp(const float& a, const float& b, float t)
{
    t = Clamp(t, 0.0f, 1.0f);
    return a + ((b-a) * t);
}

float LinuxForms::Mathf::InverseLerp(const float& a, const float& b, const float& value)
{
    return (value - a) / (b - a);
}

float LinuxForms::Mathf::Min(const float& a, const float& b)
{
    if(a > b)
        return b;
    return a;
}

float LinuxForms::Mathf::Max(const float& a, const float& b)
{
    if(a > b)
        return a;
    return b;
}

float LinuxForms::Mathf::Asin(const float& x)
{
    return asin(x);
}

float LinuxForms::Mathf::Sin(const float& x)
{
    return sinf(x);
}

float LinuxForms::Mathf::Cos(const float& x)
{
    return cosf(x);
}

float LinuxForms::Mathf::Acos(const float& x)
{
    return acos(x);
}

float LinuxForms::Mathf::Sqrt(const float& x)
{
    return sqrt(x);
}

float LinuxForms::Mathf::Clamp(float& value, const float& min, const float& max)
{
    if(value > max)
        value = max;
    if(value < min)
        value = min;
    return value;           
}

bool LinuxForms::Mathf::TryParseDouble(const std::string& t, double& v)
{
	try
	{
		v = std::stod(t);
		return true;
	}
	catch(const std::invalid_argument& ex)
	{
		return false;
	}
}

bool LinuxForms::Mathf::TryParseFloat(const std::string& t, float& v)
{
	try
	{
		v = std::stof(t);
		return true;
	}
	catch(const std::invalid_argument& ex)
	{
		return false;
	}
}

bool LinuxForms::Mathf::TryParseInt(const std::string& t, int& v)
{
	try
	{
		v = std::stoi(t);
		return true;
	}
	catch(const std::invalid_argument& ex)
	{
		return false;
	}	
}
