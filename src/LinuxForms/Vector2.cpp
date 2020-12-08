#include "Vector2.h"
#include <math.h>

LinuxForms::Vector2::Vector2(void)
{
	this->x = 0;
	this->y = 0;
}

LinuxForms::Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

float LinuxForms::Vector2::Cross(const Vector2 &other)
{
	return this->x * other.x + this->y * other.y;
}

float LinuxForms::Vector2::Dot(const Vector2 &other)
{
	return this->x * other.y - this->y * other.x;
}

float LinuxForms::Vector2::Magnitude()
{
	return sqrt(x * x + y * y);
}

LinuxForms::Vector2 LinuxForms::Vector2::Normalize()
{
	float r = 1 / Magnitude(); 
	return Vector2(x*r, y*r);
}

std::string LinuxForms::Vector2::ToString()
{
	return std::to_string(this->x) + "," + std::to_string(this->y);
}

LinuxForms::Vector2 LinuxForms::Vector2::operator + (const Vector2& rhs)
{
	return Vector2(this->x + rhs.x, this->y + rhs.y);
}

LinuxForms::Vector2 LinuxForms::Vector2::operator - (const Vector2& rhs) 
{
	return Vector2(this->x - rhs.x, this->y - rhs.y);
}

LinuxForms::Vector2 LinuxForms::Vector2::operator * (const float& rhs)
{
	return Vector2(this->x * rhs, this->y * rhs);
}

LinuxForms::Vector2 LinuxForms::Vector2::operator / (const float& rhs)
{
	return Vector2(this->x / rhs, this->y / rhs);
}

LinuxForms::Vector2 LinuxForms::Vector2::Down()
{
	return Vector2(0, -1);
}

LinuxForms::Vector2 LinuxForms::Vector2::Left()
{
	return Vector2(-1, 0);
}

LinuxForms::Vector2 LinuxForms::Vector2::One()
{
	return Vector2(1, 1);
}

LinuxForms::Vector2 LinuxForms::Vector2::Right()
{
	return Vector2(1, 0);
}

LinuxForms::Vector2 LinuxForms::Vector2::Up()
{
	return Vector2(0, 1);
}

LinuxForms::Vector2 LinuxForms::Vector2::Zero()
{
	return Vector2(0, 0);
}

LinuxForms::Vector2& LinuxForms::Vector2::operator += (const Vector2& rhs) 
{
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}

LinuxForms::Vector2& LinuxForms::Vector2::operator -= (const Vector2& rhs) 
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}

LinuxForms::Vector2& LinuxForms::Vector2::operator *= (const float& rhs)           
{
	this->x *= rhs; 
	this->y *= rhs;
	return *this;
}

LinuxForms::Vector2& LinuxForms::Vector2::operator /= (const float& rhs) 
{
	this->x /= rhs;
	this->y /= rhs;
	return *this;
}
