#pragma once

#include <iostream>

class vec3
{
public://variables

//three floats creating a 3d-vector
	float x, y, z;

public://functions 
	vec3();
	vec3(float X, float Y, float Z);
	~vec3();

	//static functions
	static const vec3 ZeroVector() { return vec3(0.f, 0.f, 0.f); }
	static const unsigned int VectorSize() { return 3; }

	//operators
	friend std::ostream& operator<< (std::ostream&, const vec3&);

	const vec3 operator = (const vec3& v);
	vec3 operator - (const vec3& v) const;
	vec3 operator / (float c) const;
	vec3 operator ^ (const vec3& v) const; // cross product
	float operator * (const vec3& v) const;	// dot product
	vec3 operator - () const;

	//functons
	float length() const;
	void normalize();
	vec3 normalized() const;
};

inline std::ostream& operator<< (std::ostream& os, const vec3& v) {
	os << "(" << v.x << "," << v.y << "," << v.z << ")";
	os << std::endl;

	return os;
}