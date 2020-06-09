#include "vec3.h"

#include <math.h>

vec3::vec3()
{
}

vec3::vec3(float X, float Y, float Z)
	:	x(X), y(Y), z(Z)
{
	
}

vec3::~vec3()
{
}

const vec3 vec3::operator=(const vec3 & v)	{
	x = v.x; y = v.y; z = v.z;
	return *this;
}

vec3 vec3::operator-(const vec3 & v) const
{
	return vec3(x - v.x, y - v.y, z - v.z);
}

vec3 vec3::operator/(float c) const
{
	return vec3(x/c, y/c, z/c);
}

vec3 vec3::operator^(const vec3 & v) const
{
	return vec3((y * v.z) - (z * v.y),
				(z * v.x) - (x * v.z),
				(x * v.y) - (y * v.x));
}

float vec3::operator*(const vec3 & v) const
{
	return (x * v.x) + (y * v.y) + (z * v.z);
}

vec3 vec3::operator-() const
{
	return vec3(-x,-y,-z);
}

float vec3::length() const
{
	return sqrtf((x*x) + (y*y));
}

void vec3::normalize()
{
	float l = length();

	x /= l;
	y /= l;
	z /= l;
}

vec3 vec3::normalized() const
{
	float l = length();
	return vec3(x/l,y/l,z/l);
}
