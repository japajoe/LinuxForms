#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <string>

namespace LinuxForms
{
    struct Vector2
    {
        float x;
        float y;
        Vector2(void);
        Vector2(float x, float y);
        float Cross(const Vector2 &other);
        float Dot(const Vector2 &other);
        float Magnitude();
        Vector2 Normalize();
	    std::string ToString();
	    static Vector2 Down();
	    static Vector2 Left();
	    static Vector2 One();
	    static Vector2 Right();
	    static Vector2 Up();
	    static Vector2 Zero();

        Vector2  operator + (const Vector2& rhs);
        Vector2  operator - (const Vector2& rhs);
        Vector2  operator * (const float& rhs);
        Vector2  operator / (const float& rhs);
        Vector2& operator += (const Vector2& rhs);
        Vector2& operator -= (const Vector2& rhs);
        Vector2& operator *= (const float& rhs);
        Vector2& operator /= (const float& rhs);
    };
}
#endif
