#pragma once

//std lib
#include <iostream>
#include <sstream>

class vec3;

class mat4x4
{
private://variables
	float mData[4][4];

public:
	mat4x4();
	mat4x4(float val);
	mat4x4( float a, float b, float c, float d,
			float e, float f, float g, float h,
			float i, float j, float k, float l,
			float m, float n, float o, float p );
	~mat4x4();

	static const unsigned int MatrixDimensions() { return 4; }	

	float *data() {
		return (float*)mData;
	}

	//use EITHER frustrum OR perspective
	void frustum(float left, float right, float bottom, float top, float cNear, float cFar);
	void perspective(float fovy, float aspectRatio, float cNear, float cFar);

	void lookAt( vec3 eye, vec3 at, const vec3 &up);
	void setToIdentity();

	//Operators
	friend std::ostream& operator<< (std::ostream&, const mat4x4&);
	float &operator () (unsigned int row, unsigned int col);

	mat4x4 operator = (mat4x4 m);
	mat4x4 operator * (float c);
	//class Vector4D operator * (Vector4D v);
	mat4x4 operator * (mat4x4 m);

	//Scaling
	void scale(float sX, float sY, float sZ);
	void scale(const vec3& v);

	//Rotation
	void rotate(float angle, const vec3 &v);
	void rotate(float angle, float x, float y, float z);

	//Translation
	void translate(float tX, float tY, float tZ);
	void translate(const vec3 &t);
	vec3 translation() const;
	void setTranslation(vec3 newTranslation);
};

inline std::ostream& operator<< (std::ostream& os, const mat4x4& m) {
	for (unsigned int i = 0; i < m.MatrixDimensions(); i++)
	{
		os << std::endl;
		for (unsigned int j = 0; j < m.MatrixDimensions(); j++)
		{
			os << m.mData[i][j] << " ";
		}
	}

	return os;
}