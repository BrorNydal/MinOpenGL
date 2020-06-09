#pragma once

#include <iostream>
#include <vector>

//custom
#include "Vertex.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

//custom math
#include "vec2.h"
#include "vec3.h"
#include "mat4x4.h"

class Object
{
private:
	vec3 mPosition;
	mat4x4 mTransformationMatrix;

public:
	Object();
	~Object();

	virtual void initialize();
	virtual void draw();

	//transformation
	void rotate(float angle, vec3 axis);
	void rotate(float angle, float x, float y, float z);

	void translate(vec3 translation);
	void translate(float x, float y, float z);

	//getters and setters
	mat4x4 getTransformationMatrix() const { return mTransformationMatrix;				   }
	vec3   getPosition()			 const { return mTransformationMatrix.translation();   }
	void   setPosition(vec3 newPos)		   { mTransformationMatrix.setTranslation(newPos); }

protected:
	IndexBuffer mIndexBuffer;
	VertexArray mVertexArray;
	VertexBuffer mVertexBuffer;

	std::vector<Vertex> mVertices;
	std::vector<unsigned int> mIndices;
};

